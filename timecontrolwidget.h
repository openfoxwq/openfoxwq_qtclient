#ifndef TIMECONTROLWIDGET_H
#define TIMECONTROLWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class TimeControlWidget;
}

class TimeControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeControlWidget(QWidget *parent = nullptr);
    ~TimeControlWidget();

    void setTime(int s);
    void setPaused(bool value);
    void setByoyomi(bool value);

private slots:
    void on_tick();

private:
    Ui::TimeControlWidget *ui;
    int m_curTime;
    bool m_paused = false;
    QTimer m_timer;

    void updateDisplayTime();
};

#endif // TIMECONTROLWIDGET_H
