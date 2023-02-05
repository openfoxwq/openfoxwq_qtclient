#ifndef ROOMTAB_H
#define ROOMTAB_H

#include <chrono>

#include <QNetworkAccessManager>
#include <QWebSocket>
#include <QWidget>
#include <QTimer>

#include <modelutils.h>
#include <soundfx.h>
#include <broadcastmodel.h>
#include <proto/common.pb.h>

namespace Ui {
class RoomTab;
}

class RoomTab : public QWidget
{
    Q_OBJECT

public:
    explicit RoomTab(QWidget *parent, QNetworkAccessManager& nam, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelUtils);
    virtual ~RoomTab();

    virtual bool leaveRoom() = 0;

protected:
    Ui::RoomTab *ui;
    QNetworkAccessManager& m_nam;
    QWebSocket& m_ws;
    SoundFx& m_sfx;
    const ModelUtils& m_modelUtils;
    openfoxwq::MatchSettings m_settings;

    void updateSettings(const openfoxwq::MatchSettings& settings);
    void updateGameResult(openfoxwq::Color winner, int64_t scoreLead);
    void putHandicapStones();

    static QPair<int, int> decodeMove(int move);

protected slots:
    virtual void on_passButton_clicked() {}
    virtual void on_aiRefereeButton_clicked() {}
    virtual void on_requestCountingButton_clicked() {}
    virtual void on_resignButton_clicked() {}
    virtual void on_saveSgfButton_clicked() {}
};

#endif // ROOMTAB_H
