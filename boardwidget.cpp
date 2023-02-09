#include "boardwidget.h"
#include "ui_boardwidget.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>

static openfoxwq::Color nextCol(openfoxwq::Color cur) {
    switch (cur) {
    case openfoxwq::Color::COL_NONE: return openfoxwq::Color::COL_NONE;
    case openfoxwq::Color::COL_BLACK: return openfoxwq::Color::COL_WHITE;
    case openfoxwq::Color::COL_WHITE: return openfoxwq::Color::COL_BLACK;
    }
}

BoardWidget::BoardWidget(QWidget *parent, int boardSize) : QWidget(parent),
    ui(new Ui::BoardWidget),
    m_boardSize(boardSize)
{
    ui->setupUi(this);

    setStyleSheet("{ background-image: url(:/assets/badukpan4_mirrored.png) }");

    setMinimumSize(m_boardSize * kMaxCellSize / 8, m_boardSize * kMaxCellSize / 8);
    setMaximumSize(m_boardSize * kMaxCellSize, m_boardSize * kMaxCellSize);

    pointButtons.resize(m_boardSize);

    for (int i = 0; i < m_boardSize; ++i) {
        pointButtons[i].resize(m_boardSize);
        for (int j = 0; j < m_boardSize; ++j) {
            BoardButton *btn = new BoardButton(this);
            btn->setState(openfoxwq::Color::COL_NONE);
            btn->setIconSize(QSize(cellSize(), cellSize()));
            const auto [x,y] = BoardButton::pointCoord(i,j, cellSize());
            btn->setGeometry(x-halfCellSize(), y-halfCellSize(), cellSize(), cellSize());
            btn->setHoveredColor(Qt::black);

            connect(btn, &BoardButton::pressed, this, [=](){ emit pointClicked(i, j, nextCol(m_lastState)); });
            connect(btn, &BoardButton::pointHover, this, [=]() {
                pointButtons[i][j]->setHoveredColor(m_lastState == openfoxwq::Color::COL_BLACK ? Qt::white : Qt::black);
            });

            pointButtons[i][j] = btn;
        }
    }
}

BoardWidget::~BoardWidget() {
    delete ui;
}

int BoardWidget::cellSize() const {
    return std::min(width(), height()) / m_boardSize;
}

int BoardWidget::halfCellSize() const {
    return cellSize()/2;
}

QSize BoardWidget::sizeHint() const {
    return QSize(m_boardSize * kMaxCellSize, m_boardSize * kMaxCellSize);
}

void BoardWidget::resizeEvent(QResizeEvent *) {
    if (width() != height()) {
        const int newSize = std::min(width(), height());
        resize(newSize, newSize);
    }
    for (int i = 0; i < m_boardSize; ++i) {
        for (int j = 0; j < m_boardSize; ++j) {
            const auto [x,y] = BoardButton::pointCoord(i,j, cellSize());
            pointButtons[i][j]->setGeometry(x-halfCellSize(), y-halfCellSize(), cellSize(), cellSize());
        }
    }
}

void BoardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawBoardLines(p);
}

openfoxwq::Color BoardWidget::turn() const {
    return nextCol(m_lastState);
}

void BoardWidget::toggleTurn() {
    m_lastState = nextCol(m_lastState);
}

QPair<int, int> BoardWidget::lastPoint() const {
    return m_lastPoint;
}

openfoxwq::Color BoardWidget::getExtendedState(int r, int c, const QMap<Point, openfoxwq::Color> &additionalPoints) {
    auto it = additionalPoints.find({r,c});
    if (it != additionalPoints.end())
        return it.value();
    return pointButtons[r][c]->getState();
}

void BoardWidget::collectGroup(openfoxwq::Color col, int r, int c, Group &group, PointSet& used, const QMap<Point, openfoxwq::Color> &additionalPoints) {
    if (0 <= r && r < m_boardSize && 0 <= c && c < m_boardSize && getExtendedState(r, c, additionalPoints) == col && !used.contains({r,c})) {
        used.insert({r, c});
        group.push_back({r,c});
        collectGroup(col, r+1, c, group, used, additionalPoints);
        collectGroup(col, r-1, c, group, used, additionalPoints);
        collectGroup(col, r, c+1, group, used, additionalPoints);
        collectGroup(col, r, c-1, group, used, additionalPoints);
    }
}

QMap<openfoxwq::Color, QVector<BoardWidget::Group>> BoardWidget::computeDeadGroups(const QMap<Point, openfoxwq::Color> &additionalPoints) {
    QMap<openfoxwq::Color, QVector<Group>> deadGroups;
    PointSet used;
    for (int i = 0; i < m_boardSize; ++i) {
        for (int j = 0; j < m_boardSize; ++j) {
            openfoxwq::Color col = getExtendedState(i, j, additionalPoints);
            if (col != openfoxwq::Color::COL_NONE && !used.contains({i,j})) {
                Group group;
                collectGroup(col, i, j, group, used, additionalPoints);

                bool hasLiberties = false;
                for (const auto &[r,c] : qAsConst(group)) {
                    for (int dr = -1; dr <= 1 && !hasLiberties; ++dr) {
                        for (int dc = -1; dc <= 1 && !hasLiberties; ++dc) {
                            if ((dr == 0) == (dc == 0)) continue;
                            const int nr = r + dr;
                            const int nc = c + dc;
                            if (0 <= nr && nr < m_boardSize && 0 <= nc && nc < m_boardSize && getExtendedState(nr, nc, additionalPoints) == openfoxwq::Color::COL_NONE) {
                                hasLiberties = true;
                                break;
                            }
                        }
                    }
                    if (hasLiberties) break;
                }
                if (!hasLiberties) {
                    deadGroups[col].append(group);
                }
            }
        }
    }
    return deadGroups;
}

static QChar col2char(openfoxwq::Color col) {
    switch (col) {
    case openfoxwq::Color::COL_NONE: return '0';
    case openfoxwq::Color::COL_BLACK: return '1';
    case openfoxwq::Color::COL_WHITE: return '2';
    }
}

bool BoardWidget::movePiece(int r, int c, openfoxwq::Color state, int *captureCount) {
    if (state == openfoxwq::Color::COL_NONE || pointButtons[r][c]->getState() != openfoxwq::Color::COL_NONE) {
        return false;
    }

    QMap<Point, openfoxwq::Color> additionalPoints;
    additionalPoints[{r,c}] = state;
    const auto deadGroups = computeDeadGroups(additionalPoints);

    // Check suicide
    const bool hasBlackDeadGroups = !deadGroups[openfoxwq::Color::COL_BLACK].isEmpty();
    const bool hasWhiteDeadGroups = !deadGroups[openfoxwq::Color::COL_WHITE].isEmpty();
    if (state == openfoxwq::Color::COL_BLACK && hasBlackDeadGroups && !hasWhiteDeadGroups)
        return false;
    if (state == openfoxwq::Color::COL_WHITE && hasWhiteDeadGroups && !hasBlackDeadGroups)
        return false;

    const QVector<Group> &capturedGroups = deadGroups[state == openfoxwq::Color::COL_BLACK ? openfoxwq::Color::COL_WHITE : openfoxwq::Color::COL_BLACK];

    // Check previous positions
    QString stateKey(m_boardSize * m_boardSize, col2char(openfoxwq::Color::COL_NONE));
    for (int i = 0; i < m_boardSize; ++i) {
        for (int j = 0; j < m_boardSize; ++j) {
            stateKey[i*m_boardSize+j] = col2char(pointButtons[i][j]->getState());
        }
    }
    stateKey[r*m_boardSize+c] = col2char(state);
    for (const auto &group : qAsConst(capturedGroups)) {
        for (const auto &[i, j] : qAsConst(group)) {
            stateKey[i*m_boardSize + j] = col2char(openfoxwq::Color::COL_NONE);
        }
    }
    if (m_previousPositions.contains(stateKey)) {
        return false;
    }
    m_previousPositions.insert(stateKey);

    // Count captures if requested
    if (captureCount != nullptr) {
        *captureCount = 0;
        for (const auto &group : qAsConst(capturedGroups)) {
            *captureCount += group.size();
        }
    }

    // Make the move
    pointButtons[r][c]->setState(state);
    for (const auto &group : qAsConst(capturedGroups)) {
        for (const auto &[i, j] : qAsConst(group)) {
            pointButtons[i][j]->setState(openfoxwq::Color::COL_NONE);
        }
    }

    // Update last point annotations
    m_lastState = state;
    m_lastPoint = {r, c};
    return true;
}

void BoardWidget::setAnnotation(int r, int c, Annotation annotation) {
    pointButtons[r][c]->setAnnotation(annotation);
}

openfoxwq::Color BoardWidget::getPoint(int r, int c) const {
    return pointButtons[r][c]->getState();
}

bool BoardWidget::interactive() const
{
    return m_interactive;
}

void BoardWidget::setInteractive(bool newInteractive)
{
    m_interactive = newInteractive;
}

void BoardWidget::toggleInteractive() {
    m_interactive = !m_interactive;
}

void BoardWidget::drawBoardLines(QPainter& p) {
    p.setPen(Qt::black);

    const int cellSize = std::min(width(), height()) / m_boardSize;
    const int starPointSize = cellSize / 10;

    // Horizontal lines
    for (int i = 0; i < m_boardSize; i++) {
        const auto [x1, y1] = BoardButton::pointCoord(i, 0, cellSize);
        const auto [x2, y2] = BoardButton::pointCoord(i, m_boardSize-1, cellSize);
        p.drawLine(x1,y1,x2,y2);
    }

    // Vertical lines
    for (int i = 0; i < m_boardSize; i++) {
        const auto [x1, y1] = BoardButton::pointCoord(0, i, cellSize);
        const auto [x2, y2] = BoardButton::pointCoord(m_boardSize-1, i, cellSize);
        p.drawLine(x1,y1,x2,y2);
    }

    // External rectangle
    {
        const auto offset = 1;
        const auto [x1, y1] = BoardButton::pointCoord(0, 0, cellSize);
        const auto size = (m_boardSize-1) * cellSize + 2*offset;
        p.drawRect(x1-offset,y1-offset,size,size);
    }

    // Star points
    {
        p.setBrush(Qt::black);
        for (auto i : {4, 10, 16}) {
            for (auto j : {4, 10, 16}) {
                const auto [x, y] = BoardButton::pointCoord(i-1, j-1, cellSize);
                p.drawEllipse(QPoint(x, y), starPointSize, starPointSize);
            }
        }
    }
}

void BoardWidget::clearAnnotations() {
    for (int i = 0; i < m_boardSize; ++i) {
        for (int j = 0; j < m_boardSize; ++j) {
            pointButtons[i][j]->clearAnnotation();
        }
    }
}
