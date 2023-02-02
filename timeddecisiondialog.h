#ifndef TIMEDDECISIONDIALOG_H
#define TIMEDDECISIONDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class TimedDecisionDialog;
}

class TimedDecisionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimedDecisionDialog(QWidget *parent, QString title, QString mainText, QString infoText, int timeSec);
    ~TimedDecisionDialog();

private slots:
    void on_acceptButton_clicked();
    void on_refuseButton_clicked();
    void on_timer();

private:
    Ui::TimedDecisionDialog *ui;
    QTimer m_timer;
};

#endif // TIMEDDECISIONDIALOG_H
