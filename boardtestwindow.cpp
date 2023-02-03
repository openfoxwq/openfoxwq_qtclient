#include "boardtestwindow.h"
#include "ui_boardtestwindow.h"

#include <QDebug>

BoardTestWindow::BoardTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardTestWindow)
{
    ui->setupUi(this);

    connect(ui->board, &BoardWidget::pointClicked, this, [=](int r, int c, openfoxwq::Color state) {
        ui->board->movePiece(r, c, state);
    });

    ui->board->movePiece(0,0,openfoxwq::Color::COL_BLACK);
    ui->board->movePiece(18,18,openfoxwq::Color::COL_WHITE);
}

BoardTestWindow::~BoardTestWindow()
{
    delete ui;
}
