#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QMessageBox>

#include <boardwidget.h>
#include <matchcardwidget.h>
#include <roomtab.h>
#include <playerinfodialog.h>
#include <timeddecisiondialog.h>

#include <google/protobuf/text_format.h>
#include <proto/common.pb.h>
#include <proto/nav.pb.h>
#include <proto/broadcast.pb.h>
#include <proto/play.pb.h>
#include <proto/ws.pb.h>

MainWindow::MainWindow(QWidget *parent, QWebSocket& ws, SoundFx& sfx, int64_t myPlayerId, QVector<AutomatchPreset> automatchPresets) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ws(ws),
    m_sfx(sfx),
    m_myPlayerId(myPlayerId),
    m_automatchPresets(automatchPresets),
    m_broadcastModel(this, m_modelUtils),
    m_playerModel(this, m_modelUtils)
{
    ui->setupUi(this);

    // Setup broadcast table
    ui->broadcastTable->setModel(&m_broadcastModel);
    ui->broadcastTable->setItemDelegateForColumn(3, new RightDecoratorStyledItemDelegate);

    ui->broadcastTable->setColumnWidth(0, 60);
    ui->broadcastTable->setColumnWidth(2, 60);
    ui->broadcastTable->setColumnWidth(3, 200);
    ui->broadcastTable->setColumnWidth(4, 40);
    ui->broadcastTable->setColumnWidth(5, 200);

    // Setup player table
    ui->playerTable->setModel(&m_playerModel);

    ui->playerTable->setColumnWidth(0, 150);
    ui->playerTable->setColumnWidth(1, 60);
    ui->playerTable->setColumnWidth(2, 80);
    ui->playerTable->setColumnWidth(3, 80);

    ui->splitter->setStretchFactor(0, 4);
    ui->splitter->setStretchFactor(1, 1);

    // Add automatch presets
    int presetIndex = 0;
    for (const auto &preset : qAsConst(m_automatchPresets)) {
        ui->automatchPresetComboBox->addItem(preset.nameEng());
        ui->automatchPresetComboBox->setItemData(presetIndex++, QVariant(preset.id()));
        qDebug() << "automatch preset: " << preset.id() << " " << preset.nameEng();
    }

    // Listen to ws events
    connect(&m_ws, &QWebSocket::disconnected, this, &MainWindow::on_disconnected);
    connect(&m_ws, &QWebSocket::binaryMessageReceived, this, &MainWindow::on_binaryMessageReceived);

    // Show loading progress dialog
    progressDialog.setMinimum(0);
    progressDialog.setAutoReset(false);
    progressDialog.setAutoClose(false);
    progressDialog.setModal(true);
    progressDialog.setCancelButton(nullptr);
    progressDialog.setLabelText("Loading broadcast and player lists...");
    progressDialog.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog.show();

    // Send request to get initial data
    openfoxwq::WsRequest req;
    req.mutable_getinitdata();
    ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_disconnected() {
    qDebug() << "WebSocket disconnected";
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText("Disconnected from server");
    msgBox.setModal(true);
    msgBox.exec();
    close();
}

void MainWindow::on_binaryMessageReceived(QByteArray data) {
    openfoxwq::WsResponse resp;
    if (!resp.ParseFromArray(data.data(), data.size())) {
        qDebug() << "ws: error parsing response";
        exit(1);
    }

    // std::string debugStr;
    // google::protobuf::TextFormat::PrintToString(resp, &debugStr);
    // qDebug() << "ws resp: " << QString::fromStdString(debugStr);

    switch (resp.resp_case()) {
    // ================================================================================
    // List responses
    case openfoxwq::WsResponse::kListPlayers:
        initialPlayerPages = resp.listplayers().page_count();
        lastPlayerPage = resp.listplayers().page_index();
        qDebug() << "ListPlayersResponse: " << lastPlayerPage+1 << "/" << initialPlayerPages;
        for (int i = 0; i < resp.listplayers().players_size(); ++i) {
            m_playerModel.update(resp.listplayers().players(i));
        }
        if (resp.listplayers().has_online_count()) {
            ui->onlineCountLabel->setText(QString("Online: %1").arg(resp.listplayers().online_count()));
        }
        break;
    case openfoxwq::WsResponse::kListBroadcasts:
        initialBroadcastPages = resp.listbroadcasts().page_count();
        lastBroadcastPage = resp.listbroadcasts().page_index();
        qDebug() << "ListBroadcastsResponse: " << lastBroadcastPage+1 << "/" << initialBroadcastPages;
        for (int i = 0; i < resp.listbroadcasts().broadcasts_size(); ++i) {
            m_broadcastModel.update(resp.listbroadcasts().broadcasts(i));
        }
        break;
    case openfoxwq::WsResponse::kListRoomParticipants:
        if (auto roomId = resp.listroomparticipants().id().id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_roomParticipants(resp.listroomparticipants());
        }
        break;

    // ================================================================================
    // Broadcast events
    case openfoxwq::WsResponse::kBroadcastSettingEvent:
        if (auto it = m_activeBroadcastRooms.find(resp.broadcastsettingevent().broadcast_id()); it != m_activeBroadcastRooms.end()) {
            it.value()->on_settingsEvent(resp.broadcastsettingevent());
        }
        break;
    case openfoxwq::WsResponse::kBroadcastStateEvent:
        if (auto it = m_activeBroadcastRooms.find(resp.broadcaststateevent().broadcast_id()); it != m_activeBroadcastRooms.end()) {
            it.value()->on_stateEvent(resp.broadcaststateevent());
        }
        break;
    case openfoxwq::WsResponse::kBroadcastMoveEvent:
        if (auto it = m_activeBroadcastRooms.find(resp.broadcastmoveevent().broadcast_id()); it != m_activeBroadcastRooms.end()) {
            it.value()->on_moveEvent(resp.broadcastmoveevent());
        }
        break;
    case openfoxwq::WsResponse::kBroadcastGameResultEvent:
        if (auto it = m_activeBroadcastRooms.find(resp.broadcastgameresultevent().broadcast_id()); it != m_activeBroadcastRooms.end()) {
            it.value()->on_gameResultEvent(resp.broadcastgameresultevent());
        }
        break;
    case openfoxwq::WsResponse::kBroadcastTimeControlEvent:
        if (auto it = m_activeBroadcastRooms.find(resp.broadcasttimecontrolevent().broadcast_id()); it != m_activeBroadcastRooms.end()) {
            it.value()->on_timeControlEvent(resp.broadcasttimecontrolevent());
        }
        break;

    // ================================================================================
    // Player events
    case openfoxwq::WsResponse::kPlayerOnlineCountEvent:
        ui->onlineCountLabel->setText(QString("Online: %1").arg(resp.playeronlinecountevent().online_count()));
        break;
    case openfoxwq::WsResponse::kPlayerOnlineEvent:
        ui->onlineCountLabel->setText(QString("Online: %1").arg(resp.playeronlineevent().online_count()));
        m_playerModel.update(resp.playeronlineevent().player_info());
        break;
    case openfoxwq::WsResponse::kPlayerOfflineEvent:
        ui->onlineCountLabel->setText(QString("Online: %1").arg(resp.playerofflineevent().online_count()));
        m_playerModel.remove(resp.playerofflineevent().player_id());
        break;
    case openfoxwq::WsResponse::kPlayerStateEvent:
        ui->onlineCountLabel->setText(QString("Online: %1").arg(resp.playerstateevent().online_count()));
        m_playerModel.update(resp.playerstateevent().player_info());
        break;

    // ================================================================================
    case openfoxwq::WsResponse::kGetPlayerInfo:
        if (resp.getplayerinfo().error_code() != 0) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Info");
            msgBox.setText("User not found.");
            msgBox.setModal(true);
            msgBox.exec();
        } else {
            // TODO update player model if player is resident and is lacking the info
            PlayerInfoDialog dlg(this, resp.getplayerinfo(), m_modelUtils);
            connect(&dlg, &PlayerInfoDialog::roomClicked, this, &MainWindow::on_roomDoubleClicked);
            dlg.exec();
        }
        break;
    case openfoxwq::WsResponse::kGetAutomatchStats:
        if (resp.getautomatchstats().error_code() == 0) {
            for (int i = 0; i < ui->automatchPresetComboBox->count(); ++i) {
                const int presetId = ui->automatchPresetComboBox->itemData(i).toInt();
                int64_t count = 0;
                if (resp.getautomatchstats().population().contains(presetId)) {
                    count = resp.getautomatchstats().population().at(presetId);
                }
                ui->automatchPresetComboBox->setItemText(i, ui->automatchPresetComboBox->itemText(i) + " (" + QString::number(count) + ")");
            }
        }
        break;

    // ================================================================================
    // Match events
    case openfoxwq::WsResponse::kMatchStartEvent:
    {
        ui->automatchButton->setChecked(false);
        MatchRoomTab *matchRoomTab = new MatchRoomTab(ui->mainTabs, m_ws, m_sfx, m_modelUtils, m_myPlayerId, resp.matchstartevent());

        const auto roomId = matchRoomTab->roomId();
        qDebug() << "Match starts: " << ModelUtils::roomIdString(roomId);

        ui->mainTabs->addTab(matchRoomTab, QString("Match: Room %1|%2").arg(roomId.id_2()).arg(roomId.id_3()));
        ui->mainTabs->setCurrentWidget(matchRoomTab);
        m_activeMatchRooms[roomId.id_2()] = matchRoomTab;

        openfoxwq::WsRequest req;
        *req.mutable_enterroom()->mutable_room_id() = roomId;
        m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
        break;
    }
    case openfoxwq::WsResponse::kEnterRoom:
        if (auto roomId = resp.enterroom().room_id().id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_matchStart();
        }
        break;
    case openfoxwq::WsResponse::kNextMoveEvent:
        if (auto roomId = resp.nextmoveevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_nextMoveEvent(resp.nextmoveevent().event());
        }
        break;
    case openfoxwq::WsResponse::kPassEvent:
        if (auto roomId = resp.passevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_pass(resp.passevent().event());
        }
        break;
    case openfoxwq::WsResponse::kCountdownEvent:
        if (auto roomId = resp.countdownevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_countdown(resp.countdownevent().event());
        }
        break;
    case openfoxwq::WsResponse::kResumeCountdownEvent:
        if (auto roomId = resp.resumecountdownevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_resumeCountdown(resp.resumecountdownevent().event());
        }
        break;
    case openfoxwq::WsResponse::kCountingDecision:
        if (auto roomId = resp.countingdecision().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_countingDecision(resp.countingdecision().decision());
        }
        break;
    case openfoxwq::WsResponse::kCountingEvent:
        if (auto roomId = resp.countingevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_countingEvent(resp.countingevent().event());
        }
        break;
    case openfoxwq::WsResponse::kGameResultEvent:
        if (auto roomId = resp.gameresultevent().room_id_2(); m_activeMatchRooms.contains(roomId)) {
            m_activeMatchRooms[roomId]->on_gameResultEvent(resp.gameresultevent().event());
        }
        break;
    default:
        break;
    }

    if (progressDialog.isVisible()) {
        progressDialog.setMaximum(initialPlayerPages+initialBroadcastPages);
        progressDialog.setValue(lastPlayerPage+lastBroadcastPage);
        if (initialPlayerPages > 0 && lastPlayerPage+1 == initialPlayerPages && initialBroadcastPages > 0 && lastBroadcastPage+1 == initialBroadcastPages) {
            progressDialog.close();
        }
    }
}

void MainWindow::on_broadcastTable_doubleClicked(const QModelIndex &index)
{
    const openfoxwq::BroadcastInfo& broadcastInfo = m_broadcastModel.getBroadcast(index.row());
    BroadcastRoomTab *broadcastRoomTab = new BroadcastRoomTab(ui->mainTabs, m_ws, m_sfx, m_modelUtils, broadcastInfo);

    ui->mainTabs->addTab(broadcastRoomTab, QString("%1: Room %2").arg(ModelUtils::broadcastTypeString(broadcastInfo.type())).arg(broadcastInfo.id()));
    ui->mainTabs->setCurrentWidget(broadcastRoomTab);
    m_activeBroadcastRooms[broadcastInfo.id()] = broadcastRoomTab;

    openfoxwq::WsRequest req;
    req.mutable_enterroom()->set_broadcast_id(broadcastInfo.id());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MainWindow::on_mainTabs_tabCloseRequested(int index)
{
    if (index == 0) {
        QMessageBox msgBox;
        msgBox.setText("You cannot close the lobby tab.");
        msgBox.exec();
        return;
    }

    RoomTab* roomTab = static_cast<RoomTab*>(ui->mainTabs->widget(index));
    if (roomTab->leaveRoom()) {
        ui->mainTabs->removeTab(index);
    }
}

void MainWindow::on_findUserButton_clicked()
{
    openfoxwq::WsRequest req;
    req.mutable_getplayerinfo()->set_name(ui->findUserEdit->text().toStdString());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}


void MainWindow::on_findUserEdit_returnPressed()
{
    openfoxwq::WsRequest req;
    req.mutable_getplayerinfo()->set_name(ui->findUserEdit->text().toStdString());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MainWindow::on_playerTable_doubleClicked(const QModelIndex &index)
{
    const openfoxwq::PlayerInfo& player = m_playerModel.getPlayer(index.row());

    openfoxwq::WsRequest req;
    req.mutable_getplayerinfo()->set_id(player.player_id());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MainWindow::on_roomDoubleClicked(const openfoxwq::RoomId& id) {
    openfoxwq::WsRequest req;
    *req.mutable_enterroom()->mutable_room_id() = id;
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MainWindow::on_automatchButton_toggled(bool checked)
{
    openfoxwq::WsRequest req;
    if (checked) {
        const auto presetId = ui->automatchPresetComboBox->currentData().toInt();
        req.mutable_startautomatch()->set_preset_id(presetId);
        ui->automatchButton->setText("Stop Automatch");
    } else {
        req.mutable_stopautomatch();
        ui->automatchButton->setText("Start Automatch");
    }
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

