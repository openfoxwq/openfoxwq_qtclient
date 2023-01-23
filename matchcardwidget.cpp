#include "matchcardwidget.h"

MatchCardWidget::MatchCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchCardWidget)
{
    ui->setupUi(this);
}
