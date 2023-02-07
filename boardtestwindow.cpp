#include "boardtestwindow.h"
#include "ui_boardtestwindow.h"

#include <QDebug>

BoardTestWindow::BoardTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardTestWindow)
{
    ui->setupUi(this);

    connect(ui->board, &BoardWidget::pointClicked, this, [=](int r, int c, openfoxwq::Color state) {
        // static int mov = 1;
        ui->board->movePiece(r, c, state);
        // ui->board->setAnnotation(r, c, Annotation{AnnotationType::kText, Qt::white, QString::number(mov)});
        // ++mov;
    });
    ui->board->movePiece(0, 0, openfoxwq::Color::COL_BLACK);
    ui->board->setAnnotation(0, 0, Annotation{AnnotationType::kCircle, Qt::white, ""});
    ui->board->movePiece(1, 1, openfoxwq::Color::COL_WHITE);
    ui->board->setAnnotation(1, 1, Annotation{AnnotationType::kSquare, Qt::black, ""});
    ui->board->movePiece(2, 2, openfoxwq::Color::COL_BLACK);
    ui->board->setAnnotation(2, 2, Annotation{AnnotationType::kCross, Qt::white, ""});
    ui->board->movePiece(4, 4, openfoxwq::Color::COL_WHITE);
    ui->board->setAnnotation(4, 4, Annotation{AnnotationType::kTriangle, Qt::black, ""});

    for (int i = 0; i < 19; ++i) {
        ui->board->movePiece(18, i, i%2==0 ? openfoxwq::Color::COL_WHITE : openfoxwq::Color::COL_BLACK);
        ui->board->setAnnotation(18, i, Annotation{AnnotationType::kText, i%2==0 ? Qt::black : Qt::white, QString::number(i)});
    }
}

BoardTestWindow::~BoardTestWindow()
{
    delete ui;
}
