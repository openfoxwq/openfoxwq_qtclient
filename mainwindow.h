#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSettings>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QWebSocket>
#include <QProgressDialog>

#include <automatchpreset.h>
#include <boardwidget.h>
#include <broadcastroomtab.h>
#include <matchroomtab.h>
#include <broadcastmodel.h>
#include <playermodel.h>
#include <soundfx.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, QNetworkAccessManager& nam, QWebSocket& ws, SoundFx& sfx, int64_t myPlayerId, QVector<AutomatchPreset> automatchPresets);
    ~MainWindow();

    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_disconnected();
    void on_binaryMessageReceived(QByteArray);
    void on_broadcastTable_doubleClicked(const QModelIndex &index);
    void on_mainTabs_tabCloseRequested(int index);
    void on_findUserButton_clicked();
    void on_findUserEdit_returnPressed();
    void on_playerTable_doubleClicked(const QModelIndex &index);
    void on_roomDoubleClicked(const openfoxwq::RoomId& id);
    void on_automatchButton_toggled(bool checked);

    void on_soundButton_toggled(bool checked);

    void on_volumeSlider_valueChanged(int value);

    void on_myProfileButton_clicked();

    void on_voiceLangComboBox_currentIndexChanged(int index);

    void on_automatchPresetComboBox_currentIndexChanged(int index);
    void onModelSortTimeout();

private:
    Ui::MainWindow *ui;
    QSettings m_settings;
    QNetworkAccessManager& m_nam;
    QWebSocket& m_ws;
    SoundFx& m_sfx;
    const int64_t m_myPlayerId;
    QVector<AutomatchPreset> m_automatchPresets;
    const ModelUtils m_modelUtils;
    QProgressDialog progressDialog;
    BroadcastModel m_broadcastModel;
    PlayerModel m_playerModel;
    QMap<int, BroadcastRoomTab*> m_activeBroadcastRooms;
    QMap<int, MatchRoomTab*> m_activeMatchRooms;
    const QString m_automatchPresetSettingKey;
    QTimer m_modelSortTimer;

    int initialBroadcastPages = 0;
    int lastBroadcastPage = 0;
    int initialPlayerPages = 0;
    int lastPlayerPage = 0;
};

#endif // MAINWINDOW_H
