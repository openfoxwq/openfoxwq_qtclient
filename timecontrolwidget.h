#ifndef TIMECONTROLWIDGET_H
#define TIMECONTROLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <soundfx.h>

namespace Ui {
class TimeControlWidget;
}

class TimeControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeControlWidget(QWidget *parent = nullptr);
    ~TimeControlWidget();

    void setSfx(SoundFx *sfx) { m_sfx = sfx; }
    void setCountdown(bool value) { m_countdown = value; }
    void setTime(int s);
    void setPaused(bool value);
    void setHideHours(bool value);

private slots:
    void on_tick();

private:
    Ui::TimeControlWidget *ui;
    SoundFx* m_sfx;
    int m_curTime;
    bool m_paused = false;
    bool m_countdown = false;
    QTimer m_timer;

    void updateDisplayTime();
};

#endif // TIMECONTROLWIDGET_H
