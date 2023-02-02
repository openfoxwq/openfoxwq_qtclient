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

void MatchCardWidget::setSfx(SoundFx *sfx) {
    m_sfx = sfx;
    ui->blackClockWidget->setSfx(sfx);
    ui->whiteClockWidget->setSfx(sfx);
}

void MatchCardWidget::setBroadcast(const openfoxwq::BroadcastInfo& room, const ModelUtils& modelUtils) {
    // White player
    QIcon whiteFlag = modelUtils.flagForCountry(room.player_info_white().country());
    ui->whiteNickLabel->setText(QString::fromStdString(room.player_info_white().name()) + " " + ModelUtils::rankString(room.player_info_white().rank()));
    ui->whiteFlag->setPixmap(whiteFlag.pixmap(whiteFlag.actualSize(QSize(32,32))));
    // Black player
    QIcon blackFlag = modelUtils.flagForCountry(room.player_info_black().country());
    ui->blackNickLabel->setText(QString::fromStdString(room.player_info_black().name()) + " " + ModelUtils::rankString(room.player_info_black().rank()));
    ui->blackFlag->setPixmap(blackFlag.pixmap(blackFlag.actualSize(QSize(32,32))));
}

void MatchCardWidget::setMatch(const openfoxwq::MatchStartEvent& matchStartEvent, const ModelUtils& modelUtils) {
    for (int i = 0; i < matchStartEvent.players_size(); ++i) {
        const auto& player = matchStartEvent.players(i);
        if (player.player_id() == matchStartEvent.match_info().player_id_black()) {
            QIcon blackFlag = modelUtils.flagForCountry(player.country());
            ui->blackNickLabel->setText(QString::fromStdString(player.name()) + " " + ModelUtils::rankString(player.rank()));
            ui->blackFlag->setPixmap(blackFlag.pixmap(blackFlag.actualSize(QSize(32,32))));
        } else if (player.player_id() == matchStartEvent.match_info().player_id_white()) {
            QIcon whiteFlag = modelUtils.flagForCountry(player.country());
            ui->whiteNickLabel->setText(QString::fromStdString(player.name()) + " " + ModelUtils::rankString(player.rank()));
            ui->whiteFlag->setPixmap(whiteFlag.pixmap(whiteFlag.actualSize(QSize(32,32))));
        }
    }
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
    switch (h) {
    case 0:
        ui->komiLabel->setText(chineseRules ? "7.5" : "6.5");
        break;
    case 1:
        ui->komiLabel->setText("0.5");
        break;
    default:
        ui->komiLabel->setText(QString::number(h) + " handicaps");
        break;
    }
}

void MatchCardWidget::setBlackTime(int t) {
    ui->blackClockWidget->setTime(t);
}

void MatchCardWidget::setBlackTimerPaused(bool value) {
    ui->blackClockWidget->setPaused(value);
}


void MatchCardWidget::setBlackPeriodsLeft(int p) {
    ui->blackByoyomiLabel->setText(QString("%1x").arg(p));
}

void MatchCardWidget::setBlackCaptures(int c) {
    ui->blackCapturesLabel->setText(QString::number(c));
}

void MatchCardWidget::setBlackCountdown(bool value) {
    ui->blackClockWidget->setCountdown(value);
}

void MatchCardWidget::setWhiteTime(int t) {
    ui->whiteClockWidget->setTime(t);
}

void MatchCardWidget::setWhiteTimerPaused(bool value) {
    ui->whiteClockWidget->setPaused(value);
}

void MatchCardWidget::setWhitePeriodsLeft(int p) {
    ui->whiteByoyomiLabel->setText(QString("%1x").arg(p));
}

void MatchCardWidget::setWhiteCaptures(int c) {
    ui->whiteCapturesLabel->setText(QString::number(c));
}

void MatchCardWidget::setWhiteCountdown(bool value) {
    ui->whiteClockWidget->setCountdown(value);
}
