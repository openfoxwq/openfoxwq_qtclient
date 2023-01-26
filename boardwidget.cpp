#include "boardwidget.h"
#include "ui_boardwidget.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>

BoardWidget::BoardWidget(QWidget *parent, int boardSize) : QWidget(parent),
    ui(new Ui::BoardWidget),
    boardSize(boardSize)
{
    ui->setupUi(this);

    placeStoneSound.setSource(QUrl::fromLocalFile(":/assets/stone.wav"));
    captureSound.setSource(QUrl::fromLocalFile(":/assets/capture0.wav"));

    setStyleSheet("{ background-image: url(:/assets/badukpan4_mirrored.png) }");

    pointButtons.resize(boardSize);

    for (int i = 0; i < boardSize; ++i) {
        pointButtons[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j) {
            BoardButton *btn = new BoardButton(this);
            btn->setState(PointState::kEmpty);
            btn->setIconSize(QSize(BoardButton::kCellSize, BoardButton::kCellSize));
            const auto [x,y] = BoardButton::pointCoord(i,j);
            btn->setGeometry(x-BoardButton::kCellHalfSize, y-BoardButton::kCellHalfSize, BoardButton::kCellSize, BoardButton::kCellSize);
            btn->setHoveredColor(Qt::black);

            connect(btn, &BoardButton::pressed, this, [=](){ emit pointClicked(i, j); });
            connect(btn, &BoardButton::pointHover, this, [=]() {
                pointButtons[i][j]->setHoveredColor(m_lastState == PointState::kBlack ? Qt::white : Qt::black);
            });

            pointButtons[i][j] = btn;
        }
    }
}

BoardWidget::~BoardWidget() {
    delete ui;
}

void BoardWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawBoardLines(p);
}

PointState BoardWidget::getExtendedState(int r, int c, const QMap<Point, PointState> &additionalPoints) {
    auto it = additionalPoints.find({r,c});
    if (it != additionalPoints.end())
        return it.value();
    return pointButtons[r][c]->getState();
}

void BoardWidget::collectGroup(PointState col, int r, int c, Group &group, PointSet& used, const QMap<Point, PointState> &additionalPoints) {
    if (0 <= r && r < boardSize && 0 <= c && c < boardSize && getExtendedState(r, c, additionalPoints) == col && !used.contains({r,c})) {
        used.insert({r, c});
        group.push_back({r,c});
        collectGroup(col, r+1, c, group, used, additionalPoints);
        collectGroup(col, r-1, c, group, used, additionalPoints);
        collectGroup(col, r, c+1, group, used, additionalPoints);
        collectGroup(col, r, c-1, group, used, additionalPoints);
    }
}

QMap<PointState, QVector<BoardWidget::Group>> BoardWidget::computeDeadGroups(const QMap<Point, PointState> &additionalPoints) {
    QMap<PointState, QVector<Group>> deadGroups;
    PointSet used;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            PointState col = getExtendedState(i, j, additionalPoints);
            if (col != PointState::kEmpty && !used.contains({i,j})) {
                Group group;
                collectGroup(col, i, j, group, used, additionalPoints);

                bool hasLiberties = false;
                for (const auto &[r,c] : qAsConst(group)) {
                    for (int dr = -1; dr <= 1 && !hasLiberties; ++dr) {
                        for (int dc = -1; dc <= 1 && !hasLiberties; ++dc) {
                            if ((dr == 0) == (dc == 0)) continue;
                            const int nr = r + dr;
                            const int nc = c + dc;
                            if (0 <= nr && nr < boardSize && 0 <= nc && nc < boardSize && getExtendedState(nr, nc, additionalPoints) == PointState::kEmpty) {
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

bool BoardWidget::movePiece(int r, int c, PointState state) {
    if (state == PointState::kEmpty || pointButtons[r][c]->getState() != PointState::kEmpty) {
        return false;
    }

    QMap<Point, PointState> additionalPoints;
    additionalPoints[{r,c}] = state;
    const auto deadGroups = computeDeadGroups(additionalPoints);

    // Check suicide
    const bool hasBlackDeadGroups = !deadGroups[PointState::kBlack].isEmpty();
    const bool hasWhiteDeadGroups = !deadGroups[PointState::kWhite].isEmpty();
    if (state == PointState::kBlack && hasBlackDeadGroups && !hasWhiteDeadGroups)
        return false;
    if (state == PointState::kWhite && hasWhiteDeadGroups && !hasBlackDeadGroups)
        return false;

    // Make the move
    const bool hasCaptures = hasBlackDeadGroups || hasWhiteDeadGroups;

    if (m_soundEnabled) {
        if (hasCaptures) captureSound.play();
        else placeStoneSound.play();
    }

    pointButtons[r][c]->setState(state);
    const QVector<Group> &capturedGroups = deadGroups[state == PointState::kBlack ? PointState::kWhite : PointState::kBlack];
    for (const auto &group : qAsConst(capturedGroups)) {
        for (const auto &[i, j] : qAsConst(group)) {
            pointButtons[i][j]->setState(PointState::kEmpty);
        }
    }

    // Update last point annotations
    m_lastState = state;
    const auto & [lr, lc] = m_lastPoint;
    if (lr != -1) {
        pointButtons[lr][lc]->clearAnnotation();
    }
    m_lastPoint = {r, c};
    pointButtons[r][c]->setAnnotation(Annotation{
        AnnotationType::kQuarterTriangle,
        state == PointState::kBlack ? Qt::white : Qt::black,
        "",
    });
    return true;
}

void BoardWidget::setAnnotation(int r, int c, Annotation annotation) {
    pointButtons[r][c]->setAnnotation(annotation);
}

PointState BoardWidget::getPoint(int r, int c) const {
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

void BoardWidget::drawBoardLines(QPainter& p) {
    p.setPen(Qt::black);

    // Horizontal lines
    for (int i = 0; i < boardSize; i++) {
        const auto [x1, y1] = BoardButton::pointCoord(i, 0);
        const auto [x2, y2] = BoardButton::pointCoord(i, boardSize-1);
        p.drawLine(x1,y1,x2,y2);
    }

    // Vertical lines
    for (int i = 0; i < boardSize; i++) {
        const auto [x1, y1] = BoardButton::pointCoord(0, i);
        const auto [x2, y2] = BoardButton::pointCoord(boardSize-1, i);
        p.drawLine(x1,y1,x2,y2);
    }

    // External rectangle
    {
        const auto offset = 1;
        const auto [x1, y1] = BoardButton::pointCoord(0, 0);
        const auto size = (boardSize-1) * BoardButton::kCellSize + 2*offset;
        p.drawRect(x1-offset,y1-offset,size,size);
    }

    // Star points
    {
        p.setBrush(Qt::black);
        for (auto i : {4, 10, 16}) {
            for (auto j : {4, 10, 16}) {
                const auto [x, y] = BoardButton::pointCoord(i-1, j-1);
                p.drawEllipse(QPoint(x, y), BoardButton::kStarPointSize, BoardButton::kStarPointSize);
            }
        }
    }
}

void BoardWidget::setSound(bool value) {
    m_soundEnabled = value;
}

void BoardWidget::clearAnnotations() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            pointButtons[i][j]->clearAnnotation();
        }
    }
}
