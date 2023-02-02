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
}

BoardTestWindow::~BoardTestWindow()
{
    delete ui;
}
