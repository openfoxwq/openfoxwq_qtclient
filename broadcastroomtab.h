#ifndef BROADCASTROOMTAB_H
#define BROADCASTROOMTAB_H

#include "roomtab.h"
#include "soundfx.h"
#include "modelutils.h"
#include "proto/broadcast.pb.h"

class BroadcastRoomTab : public RoomTab
{
    Q_OBJECT

public:
    explicit BroadcastRoomTab(QWidget *parent, QNetworkAccessManager& nam, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelutils, const openfoxwq::BroadcastInfo& broadcast);

    bool leaveRoom() override;

public slots:
    void on_settingsEvent(const openfoxwq::BroadcastSettingEvent& settings);
    void on_stateEvent(const openfoxwq::BroadcastStateEvent& event);
    void on_moveEvent(const openfoxwq::BroadcastMoveEvent& event);
    void on_timeControlEvent(const openfoxwq::BroadcastTimeControlEvent& event);
    void on_gameResultEvent(const openfoxwq::BroadcastGameResultEvent& event);

private:
    const openfoxwq::BroadcastInfo m_broadcast;
};

#endif // BROADCASTROOMTAB_H
