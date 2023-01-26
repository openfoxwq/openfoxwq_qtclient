#include "matchcardwidget.h"
#include "ui_matchcardwidget.h"

#include <QDebug>

MatchCardWidget::MatchCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchCardWidget)
{
    ui->setupUi(this);
}

MatchCardWidget::~MatchCardWidget() {
    delete ui;
}

void MatchCardWidget::setRoom(BroadcastRoom room, const ModelUtils& modelUtils) {
    // White player
    QIcon whiteFlag = modelUtils.flagForCountry(room.whitePlayer.country);
    ui->whiteNickLabel->setText(room.whitePlayer.name + " " + room.whitePlayer.rank.toString());
    ui->whiteFlag->setPixmap(whiteFlag.pixmap(whiteFlag.actualSize(QSize(32,32))));
    // Black player
    QIcon blackFlag = modelUtils.flagForCountry(room.blackPlayer.country);
    ui->blackNickLabel->setText(room.blackPlayer.rank.toString() + " " + room.blackPlayer.name);
    ui->blackFlag->setPixmap(blackFlag.pixmap(blackFlag.actualSize(QSize(32,32))));
}

static QString formatMainTime(int t) {
    QString ret;
    if (t >= 60*60) {
        ret += QString("%1 h ").arg(t / (60*60));
        t %= 60*60;
    }
    if (t >= 60) {
        ret += QString("%1 min ").arg(t / (60));
        t %= 60;
    }

    if (t > 0) {
        ret += QString("%s sec").arg(t);
    }
    return ret;
}

void MatchCardWidget::setMainTime(int t) {
    ui->mainTimeLabel->setText(formatMainTime(t));
}

void MatchCardWidget::setByoyomi(int p, int t) {
    ui->byoyomiLabel->setText(QString("%1x %2 sec").arg(p).arg(t));
}

void MatchCardWidget::setHandicap(int h, bool chineseRules) {
    if (h == 0) {
        ui->komiLabel->setText(chineseRules ? "7.5" : "6.5");
    } else {
        ui->komiLabel->setText("0.5");
    }
}

void MatchCardWidget::setBlackTime(int t) {
    ui->blackClockWidget->setTime(t);
}

void MatchCardWidget::setBlackTimerPaused(bool value) {
    ui->blackClockWidget->setPaused(value);
}

void MatchCardWidget::setBlackInByoyomi() {
    ui->blackClockWidget->setByoyomi(true);
}

void MatchCardWidget::setBlackPeriodsLeft(int p) {
    ui->blackByoyomiLabel->setText(QString("%1x").arg(p));
}

void MatchCardWidget::setBlackCaptures(int c) {
    ui->blackCapturesLabel->setText(QString::number(c));
}

void MatchCardWidget::setWhiteTime(int t) {
    ui->whiteClockWidget->setTime(t);
}

void MatchCardWidget::setWhiteTimerPaused(bool value) {
    ui->whiteClockWidget->setPaused(value);
}

void MatchCardWidget::setWhiteInByoyomi() {
    ui->whiteClockWidget->setByoyomi(true);
}

void MatchCardWidget::setWhitePeriodsLeft(int p) {
    ui->whiteByoyomiLabel->setText(QString("%1x").arg(p));
}

void MatchCardWidget::setWhiteCaptures(int c) {
    ui->whiteCapturesLabel->setText(QString::number(c));
}
