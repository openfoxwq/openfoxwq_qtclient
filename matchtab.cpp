#include "matchtab.h"

MatchTab::MatchTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchTab)
{
    ui->setupUi(this);

    m_boardWidget = new BoardWidget(parent);
    m_matchCardWidget = new MatchCardWidget(parent);

    ui->board = m_boardWidget;
    ui->matchCard = m_matchCardWidget;
}
