#include "timecontrolwidget.h"
#include "ui_timecontrolwidget.h"

TimeControlWidget::TimeControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeControlWidget)
{
    ui->setupUi(this);

    connect(&m_timer, &QTimer::timeout, this, &TimeControlWidget::on_tick);

    m_timer.setSingleShot(false);
    m_timer.setInterval(1000);
    m_timer.start();
}

TimeControlWidget::~TimeControlWidget()
{
    delete ui;
}

void TimeControlWidget::setTime(int t) {
    m_curTime = t;
    updateDisplayTime();
}

void TimeControlWidget::updateDisplayTime() {
    int t = m_curTime;
    const int h = t/3600;
    t%=3600;
    const int m = t/60;
    t%=60;
    const int s = t;

    ui->hour1Number->display(h/10);
    ui->hour2Number->display(h%10);
    ui->min1Number->display(m/10);
    ui->min2Number->display(m%10);
    ui->sec1Number->display(s/10);
    ui->sec2Number->display(s%10);
}

void TimeControlWidget::setPaused(bool value) {
    m_paused = value;
    if (m_paused) m_timer.stop();
    else m_timer.start();
}

void TimeControlWidget::setByoyomi(bool) {
    setPaused(true);
}

void TimeControlWidget::on_tick() {
    if (m_curTime > 0) {
        m_curTime--;
        updateDisplayTime();
    }
}
