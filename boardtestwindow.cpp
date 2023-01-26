#include "boardtestwindow.h"
#include "ui_boardtestwindow.h"

#include <QDebug>

BoardTestWindow::BoardTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardTestWindow)
{
    ui->setupUi(this);

    connect(ui->board, &BoardWidget::pointClicked, this, [=](int r, int c) {
        ui->board->movePiece(r, c, m_curState);
        m_curState = m_curState == PointState::kBlack ? PointState::kWhite : PointState::kBlack;
    });

    ui->board->setSound(true);
}

BoardTestWindow::~BoardTestWindow()
{
    delete ui;
}
