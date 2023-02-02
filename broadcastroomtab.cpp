#include "broadcastroomtab.h"

#include "ui_roomtab.h"
#include "proto/ws.pb.h"

BroadcastRoomTab::BroadcastRoomTab(QWidget *parent, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelUtils, const openfoxwq::BroadcastInfo& broadcastInfo)
    : RoomTab(parent, ws, sfx, modelUtils), m_broadcast(broadcastInfo)
{
    ui->matchCard->setBroadcast(m_broadcast, m_modelUtils);
    ui->msgList->addItem("Welcome to broadcast room " + QString::number(m_broadcast.id()));
    ui->saveSgfButton->setDisabled(true);
}

void BroadcastRoomTab::on_settingsEvent(const openfoxwq::BroadcastSettingEvent &event) {
    if (event.has_match_settings()) {
        updateSettings(event.match_settings());
    }
}

void BroadcastRoomTab::on_stateEvent(const openfoxwq::BroadcastStateEvent& event) {
    openfoxwq::Color curCol = openfoxwq::Color::COL_BLACK;
    if (m_settings.handicap() > 1) {
        putHandicapStones();
        curCol = openfoxwq::Color::COL_WHITE;
    }
    for (int i = 0; i < event.state().encoded_moves_size(); ++i) {
        const auto [r, c] = decodeMove(event.state().encoded_moves(i));
        ui->board->movePiece(r, c, curCol);
        curCol = (curCol == openfoxwq::Color::COL_BLACK) ? openfoxwq::Color::COL_WHITE : openfoxwq::Color::COL_BLACK;
    }
    if (curCol == openfoxwq::Color::COL_BLACK) {
        ui->matchCard->setBlackTimerPaused(false);
    } else {
        ui->matchCard->setWhiteTimerPaused(false);
    }
}

void BroadcastRoomTab::on_moveEvent(const openfoxwq::BroadcastMoveEvent& event) {
    const auto [r, c] = decodeMove(event.encoded_move());
    if (event.player_id() == m_broadcast.player_id_black()) {
        ui->board->movePiece(r, c, openfoxwq::Color::COL_BLACK);
        m_sfx.playStone();
        ui->matchCard->setBlackTime(event.time_left()>>2);
        ui->matchCard->setBlackTimerPaused(true);
        ui->matchCard->setWhiteTimerPaused(false);
    } else if (event.player_id() == m_broadcast.player_id_white()) {
        ui->board->movePiece(r, c, openfoxwq::Color::COL_WHITE);
        m_sfx.playStone();
        ui->matchCard->setWhiteTime(event.time_left()>>2);
        ui->matchCard->setWhiteTimerPaused(true);
        ui->matchCard->setBlackTimerPaused(false);
    } else {
        qDebug() << "player id doesn't match broadcast players in config";
    }
}

void BroadcastRoomTab::on_timeControlEvent(const openfoxwq::BroadcastTimeControlEvent& event) {
    if (event.player_id() == m_broadcast.player_id_black()) {
        ui->matchCard->setBlackTimerPaused(true);
        ui->matchCard->setBlackPeriodsLeft(event.current_period());
        ui->matchCard->setBlackTime(event.time_left());
    } else if (event.player_id() == m_broadcast.player_id_white()) {
        ui->matchCard->setWhiteTimerPaused(true);
        ui->matchCard->setWhitePeriodsLeft(event.current_period());
        ui->matchCard->setWhiteTime(event.time_left());
    } else {
        qDebug() << "player id doesn't match broadcast players in config";
    }
}

void BroadcastRoomTab::on_gameResultEvent(const openfoxwq::BroadcastGameResultEvent& event) {
    updateGameResult(event.winner(), event.score_lead());
}

bool BroadcastRoomTab::leaveRoom() {
    openfoxwq::WsRequest req;
    req.mutable_leaveroom()->set_broadcast_id(m_broadcast.id());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
    return true;
}
