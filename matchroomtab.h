#ifndef MATCHROOMTAB_H
#define MATCHROOMTAB_H

#include <QNetworkReply>
#include <QSettings>

#include "roomtab.h"
#include "proto/play.pb.h"

class MatchRoomTab : public RoomTab
{
    Q_OBJECT

public:
    explicit MatchRoomTab(QWidget *parent, QNetworkAccessManager& nam, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelUtils, int64_t selfPlayerId, const openfoxwq::MatchStartEvent& matchStartEvent);
    ~MatchRoomTab();

    openfoxwq::RoomId roomId() const { return m_roomId; }

    void on_matchStart();
    void on_nextMoveEvent(const openfoxwq::NextMoveEvent& event);
    void on_pass(const openfoxwq::PassEvent& event);
    void on_countdown(const openfoxwq::CountdownEvent& event);
    void on_resumeCountdown(const openfoxwq::ResumeCountdownEvent& event);
    void on_countingDecision(const openfoxwq::CountingDecision& decision);
    void on_countingEvent(const openfoxwq::CountingEvent& event);
    void on_gameResultEvent(const openfoxwq::GameResultEvent& event);
    void on_roomParticipants(const openfoxwq::ListRoomParticipantsResponse& resp);

    bool leaveRoom() override;

protected slots:
    void on_passButton_clicked() override;
    void on_aiRefereeButton_clicked() override;
    void on_requestCountingButton_clicked() override;
    void on_resignButton_clicked() override;
    void on_saveSgfButton_clicked() override;

private slots:
    void on_pointClicked(int r, int c, openfoxwq::Color state);
    void on_syncTimer();
    void on_listParticipantsTimer();
    void onWhiteAvatarDownloaded();
    void onBlackAvatarDownloaded();

private:
    QSettings m_sysSettings;
    QTimer m_syncTimer;
    QTimer m_listParticipantsTimer;
    const int64_t m_selfPlayerId;
    const openfoxwq::MatchStartEvent m_matchStartEvent;
    openfoxwq::RoomId m_roomId;
    QNetworkReply *m_whiteAvatarReply = nullptr;
    QNetworkReply *m_blackAvatarReply = nullptr;
    bool m_myTurn;
    int m_moveNum;
    bool m_whiteInByoyomi = false, m_blackInByoyomi = false;
    openfoxwq::CountingStage m_curStage = openfoxwq::CountingStage::STAGE_UNKNOWN;
    std::chrono::steady_clock::time_point m_startedTs;
    QDateTime m_sgfDateTime;
    QString m_sgfHeader;
    QString m_sgfMoves;
    bool m_hasResult = false;

    void updatePlayerTime(openfoxwq::Color color, int mainTimeLeft);
    void toggleTurn();
};

#endif // MATCHROOMTAB_H
