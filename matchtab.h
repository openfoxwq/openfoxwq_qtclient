#ifndef MATCHTAB_H
#define MATCHTAB_H

#include <QWidget>

#include <boardwidget.h>
#include <matchcardwidget.h>
#include <ui_matchtab.h>

class MatchTab : public QWidget
{
    Q_OBJECT
public:
    explicit MatchTab(QWidget *parent = nullptr);

signals:

private:
    Ui::MatchTab *ui;
    BoardWidget* m_boardWidget;
    MatchCardWidget *m_matchCardWidget;
};

#endif // MATCHTAB_H
