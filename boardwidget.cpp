#include "boardwidget.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>

constexpr int kCellSize = 52;
constexpr int kCellHalfSize = kCellSize / 2;
constexpr int kStarPointSize = kCellSize / 10;

inline QPair<int,int> pointCoord(int r, int c) {
    return {
        kCellSize*c+kCellHalfSize,
        kCellSize*r+kCellHalfSize,
    };
}

BoardWidget::BoardWidget(QWidget *parent, int boardSize) : QWidget(parent),
    ui(new Ui::BoardWidget),
    boardSize(boardSize),
    blackStone(":/assets/blackStone.png"),
    whiteStone(":/assets/whiteStone.png"),
    placeStone(":/assets/stone.wav")
{
    ui->setupUi(this);

    pointState.resize(boardSize);
    pointButtons.resize(boardSize);

    for (int i = 0; i < boardSize; ++i) {
        pointState[i].resize(boardSize);
        pointButtons[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j) {
            QPushButton *btn = new QPushButton(this); // TODO move to subclass of QPushButton
            btn->setStyleSheet(QString("QPushButton {border: 0px;}"));
            btn->setFlat(true);
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setContentsMargins(0,0,0,0);
            btn->setIconSize(QSize(kCellSize, kCellSize));
            const auto [x,y] = pointCoord(i,j);
            btn->setGeometry(x-kCellHalfSize, y-kCellHalfSize, kCellSize, kCellSize);
            connect(btn, &QPushButton::pressed, this, [=](){ emit pointClicked(i, j); });

            pointState[i][j] = PointState::kEmpty;
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

void BoardWidget::setPoint(int r, int c, PointState state) {
    // if (pointState[r][c] == PointState::kEmpty && state != PointState::kEmpty) {
    //     placeStone.play();
    // }
    pointState[r][c] = state;
    switch (state) {
    case PointState::kEmpty:
        pointButtons[r][c]->setIcon(QIcon());
    case PointState::kBlack:
        pointButtons[r][c]->setIcon(blackStone);
    case PointState::kWhite:
        pointButtons[r][c]->setIcon(whiteStone);
    }
}

BoardWidget::PointState BoardWidget::getPoint(int r, int c) const {
    return pointState[r][c];
}

void BoardWidget::drawBoardLines(QPainter& p) {

    p.setPen(Qt::black);

    // Horizontal lines
    for (int i = 0; i < boardSize; i++) {
        const auto [x1, y1] = pointCoord(i, 0);
        const auto [x2, y2] = pointCoord(i, boardSize-1);
        p.drawLine(x1,y1,x2,y2);
    }

    // Vertical lines
    for (int i = 0; i < boardSize; i++) {
        const auto [x1, y1] = pointCoord(0, i);
        const auto [x2, y2] = pointCoord(boardSize-1, i);
        p.drawLine(x1,y1,x2,y2);
    }

    // External rectangle
    {
        const auto offset = 1;
        const auto [x1, y1] = pointCoord(0, 0);
        const auto size = (boardSize-1) * kCellSize + 2*offset;
        p.drawRect(x1-offset,y1-offset,size,size);
    }

    // Star points
    {
        p.setBrush(Qt::black);
        for (auto i : {4, 10, 16}) {
            for (auto j : {4, 10, 16}) {
                const auto [x, y] = pointCoord(i-1, j-1);
                p.drawEllipse(QPoint(x, y), kStarPointSize, kStarPointSize);
            }
        }
    }
}

