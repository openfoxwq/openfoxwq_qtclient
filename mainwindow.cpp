#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QMessageBox>

#include <rank.h>
#include <getinitdatamsg.h>
#include <boardwidget.h>
#include <matchcardwidget.h>
#include <matchtab.h>
#include <enterroommsg.h>
#include <leaveroommsg.h>

#include <proto/common.pb.h>

MainWindow::MainWindow(QWidget *parent, QWebSocket *ws) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ws(ws),
    m_roomModel(this, m_modelUtils),
    m_playerModel(this, m_modelUtils)
{
    ui->setupUi(this);

    // Setup broadcast room table
    ui->roomTable->setModel(&m_roomModel);
    ui->roomTable->setItemDelegateForColumn(3, new RightDecoratorStyledItemDelegate);

    ui->roomTable->setColumnWidth(0, 60);
    ui->roomTable->setColumnWidth(2, 60);
    ui->roomTable->setColumnWidth(3, 200);
    ui->roomTable->setColumnWidth(4, 40);
    ui->roomTable->setColumnWidth(5, 200);

    // Setup player table
    ui->playerTable->setModel(&m_playerModel);

    ui->playerTable->setColumnWidth(0, 150);
    ui->playerTable->setColumnWidth(1, 60);
    ui->playerTable->setColumnWidth(2, 80);
    ui->playerTable->setColumnWidth(3, 80);

    // Listen to ws events
    connect(ws, &QWebSocket::disconnected, this, &MainWindow::on_ws_disconnected);
    connect(ws, &QWebSocket::textMessageReceived, this, &MainWindow::on_ws_msg);

    // Show loading progress dialog
    progressDialog.setMinimum(0);
    progressDialog.setAutoReset(false);
    progressDialog.setAutoClose(false);
    progressDialog.setModal(true);
    progressDialog.setCancelButton(nullptr);
    progressDialog.setLabelText("Loading game list...");
    progressDialog.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog.show();

    // Send request to get initial data
    QJsonObject req;
    GetInitDataMsg msg;
    msg.write(req);
    ws->sendTextMessage(QJsonDocument(req).toJson(QJsonDocument::JsonFormat::Compact));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ws_disconnected() {
    qDebug() << "WebSocket disconnected";
    QMessageBox msgBox;
    msgBox.setText("Disconnected from server");
    msgBox.exec();
    close();
}

void MainWindow::on_ws_msg(QString data) {
    // qDebug() << "ws: raw=" << data;

    QJsonParseError err;
    auto msg = QJsonDocument::fromJson(data.toLocal8Bit(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "ws: json parse error: " << err.errorString();
        return;
    }

    auto typ = msg["type"].toString();
    if (typ == "ListPlayersResponse") {
        initialPlayerPages = msg["msg"]["pageCount"].toString().toInt();
        lastPlayerPage = msg["msg"]["pageIndex"].toString().toInt();
        qDebug() << "ListPlayersResponse: " << lastPlayerPage+1 << "/" << initialPlayerPages;
        int numPlayers = msg["msg"]["players"].toArray().size();
        for (int i = 0; i < numPlayers; ++i) {
            Player player {
                .id = msg["msg"]["players"][i]["playerId"].toString().toInt(),
                .name = msg["msg"]["players"][i]["name"].toString(),
                .nameNative = msg["msg"]["players"][i]["nameNative"].toString(),
                .country = msg["msg"]["players"][i]["country"].toString(),
                .rank = Rank::ofString(msg["msg"]["players"][i]["rank"].toString()),
                .rankedResults = PlayerResults {
                    .wins = msg["msg"]["players"][i]["rankedWins"].toString().toInt(),
                    .losses = msg["msg"]["players"][i]["rankedLosses"].toString().toInt(),
                    .draws = 0,
                },
                .currentResults = PlayerResults { .wins=0, .losses=0, .draws=0 },
                .totalResults = PlayerResults { .wins=0, .losses=0, .draws=0 },
            };
            m_playerModel.update(player);
        }
        // TODO: update onlineCount with last page
        // ui->onlineCountLabel->setText(QString("Online: %1").arg(onlineCount));
    } else if (typ == "ListRoomsResponse") {
        initialRoomPages = msg["msg"]["pageCount"].toString().toInt();
        lastRoomPage = msg["msg"]["pageIndex"].toString().toInt();
        const int numRooms = msg["msg"]["roomInfo"].toArray().size();
        qDebug() << "ListRoomsResponse: " << lastRoomPage+1 << "/" << initialRoomPages << ": " << numRooms;
        for (int i = 0; i < numRooms; ++i) {
            BroadcastRoom room {
                .id = msg["msg"]["roomInfo"][i]["roomId"].toString().toInt(),
                .type = msg["msg"]["roomInfo"][i]["roomType"].toString(),
                .online = msg["msg"]["roomInfo"][i]["onlineCount"].toString().toInt(),
                .whitePlayer = BroadcastRoomPlayerInfo {
                     .id = msg["msg"]["roomInfo"][i]["playerIdWhite"].toString().toInt(),
                     .name = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["name"].toString(),
                     .nameNative = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["nameAlt"].toString(),
                     .rank = Rank::ofString(msg["msg"]["roomInfo"][i]["playerInfoWhite"]["rank"].toString()),
                     .country = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["country"].toString(),
                },
                .blackPlayer = BroadcastRoomPlayerInfo {
                     .id = msg["msg"]["roomInfo"][i]["playerIdBlack"].toString().toInt(),
                     .name = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["name"].toString(),
                     .nameNative = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["nameAlt"].toString(),
                     .rank = Rank::ofString(msg["msg"]["roomInfo"][i]["playerInfoBlack"]["rank"].toString()),
                     .country = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["country"].toString(),
                },
                .state = msg["msg"]["roomInfo"][i]["roomState"].toString(),
                .broadcastInfo = msg["msg"]["roomInfo"][i]["broadcaster"].toString(),
            };
            m_roomModel.update(room);
        }
    } else if (typ == "RoomConfigEvent") {
        const int roomId = msg["msg"]["roomId"].toString().toInt();
        if (msg["msg"].toObject().contains("config")) {
            BroadcastRoomConfig roomConfig;
            roomConfig.playerIdBlack = msg["msg"]["playerIdBlack"].toString().toInt();
            roomConfig.playerIdWhite = msg["msg"]["playerIdWhite"].toString().toInt();
            roomConfig.playerIdFirst = msg["msg"]["config"]["playerIdFirst"].toString().toInt();
            roomConfig.playerIdSecond = msg["msg"]["config"]["playerIdSecond"].toString().toInt();
            roomConfig.chineseRules = msg["msg"]["config"]["chineseRules"].toBool();
            roomConfig.handicap = msg["msg"]["config"]["handicap"].toString().toInt();
            roomConfig.mainTime = msg["msg"]["config"]["mainTimeSec"].toString().toInt();
            roomConfig.byoyomiTime = msg["msg"]["config"]["byoyomiTimeSec"].toString().toInt();
            roomConfig.byoyomiPeriods = msg["msg"]["config"]["byoyomiPeriods"].toString().toInt();
            roomConfig.boardSize = msg["msg"]["config"]["boardSize"].toString().toInt();
            auto it = m_activeRooms.find(roomId);
            if (it != m_activeRooms.end()) {
                it.value()->updateRoomConfig(roomConfig);
            }
        }
    } else if (typ == "RoomStateEvent") {
        const int roomId = msg["msg"]["roomId"].toString().toInt();
        BroadcastRoomState roomState {
            .moveCount = msg["msg"]["state"]["moveCount"].toString().toInt(),
        };
        auto encodedMoves = msg["msg"]["state"]["encodedMoves"].toArray();
        for (int i = 0; i < encodedMoves.size(); ++i) {
            roomState.encodedMoves.push_back(encodedMoves[i].toString().toInt());
        }
        if (encodedMoves.size() > 0)
            qDebug() << "initial moves: " << encodedMoves.size();
        auto it = m_activeRooms.find(roomId);
        if (it != m_activeRooms.end()) {
            it.value()->updateRoomState(roomState);
        }
    } else if (typ == "RoomMoveEvent") {
        const int roomId = msg["msg"]["roomId"].toString().toInt();
        const int playerId    = msg["msg"]["playerId"].toString().toInt();
        const int encodedMove = msg["msg"]["encodedMove"].toString().toInt();
        const int moveNumber  = msg["msg"]["moveNumber"].toString().toInt();
        const int timeLeft    = msg["msg"]["timeLeft"].toString().toInt();

        auto it = m_activeRooms.find(roomId);
        if (it != m_activeRooms.end()) {
            it.value()->updateMove(playerId, encodedMove, moveNumber, timeLeft);
        }
    } else if (typ == "RoomGameResultEvent") {
        const int roomId = msg["msg"]["roomId"].toString().toInt();
        const QString winner = msg["msg"]["winner"].toString();
        const int scoreLead = msg["msg"]["scoreLead"].toString().toInt();

        auto it = m_activeRooms.find(roomId);
        if (it != m_activeRooms.end()) {
            it.value()->gameResult(winner, scoreLead);
        }

    } else if (typ == "RoomTimeControlEvent") {
        const int roomId = msg["msg"]["roomId"].toString().toInt();
        const int playerId      = msg["msg"]["playerId"].toString().toInt();
        const int currentPeriod = msg["msg"]["currentPeriod"].toString().toInt();
        const int timeLeft      = msg["msg"]["timeLeft"].toString().toInt();

        auto it = m_activeRooms.find(roomId);
        if (it != m_activeRooms.end()) {
            it.value()->updateTimeControl(playerId, currentPeriod, timeLeft);
        }
    } else if (typ == "PlayerStateEvent") {
        const int onlineCount = msg["msg"]["onlineCount"].toString().toInt();
        ui->onlineCountLabel->setText(QString("Online: %1").arg(onlineCount));
    } else {
        qDebug() << "ws: unhandled message type: " << typ;
    }

    progressDialog.setMaximum(initialPlayerPages+initialRoomPages);
    progressDialog.setValue(lastPlayerPage+lastRoomPage);
    if (initialPlayerPages > 0 && lastPlayerPage+1 == initialPlayerPages && initialRoomPages > 0 && lastRoomPage+1 == initialRoomPages) {
        progressDialog.close();
    }
}

void MainWindow::on_roomTable_doubleClicked(const QModelIndex &index)
{
    BroadcastRoom room = m_roomModel.getRoom(index.row());
    MatchTab *matchTab = new MatchTab(ui->mainTabs, room, m_modelUtils);

    Player blackPlayer = m_playerModel.getPlayerById(room.blackPlayer.id);
    Player whitePlayer = m_playerModel.getPlayerById(room.whitePlayer.id);
    qDebug() << "entering room " << room.id;
    qDebug() << "    BroadcastRoomInfo.player_id_black: " << room.blackPlayer.id;

    ui->mainTabs->addTab(matchTab, QString("%1: Room %2").arg(room.type.replace("RT_", "")).arg(room.id));
    ui->mainTabs->setCurrentWidget(matchTab);
    m_activeRooms[room.id] = matchTab;

    QJsonObject req;
    EnterRoomMsg msg(room.id);
    msg.write(req);
    ws->sendTextMessage(QJsonDocument(req).toJson(QJsonDocument::JsonFormat::Compact));
}

void MainWindow::on_mainTabs_tabCloseRequested(int index)
{
    if (index == 0) {
        QMessageBox msgBox;
        msgBox.setText("You cannot close the lobby tab.");
        msgBox.exec();
        return;
    }

    BroadcastRoom room = static_cast<MatchTab*>(ui->mainTabs->widget(index))->getRoom();
    ui->mainTabs->removeTab(index);
    m_activeRooms.remove(room.id);

    QJsonObject req;
    LeaveRoomMsg msg(room.id);
    msg.write(req);
    ws->sendTextMessage(QJsonDocument(req).toJson(QJsonDocument::JsonFormat::Compact));
}

