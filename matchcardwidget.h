#ifndef MATCHCARDWIDGET_H
#define MATCHCARDWIDGET_H

#include <QWidget>
#include <ui_matchcardwidget.h>

class MatchCardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatchCardWidget(QWidget *parent = nullptr);

signals:

private:
    Ui::MatchCardWidget *ui;

};

#endif // MATCHCARDWIDGET_H
