#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDebug>
#include <QStyledItemDelegate>

#include <getinitdatamsg.h>
#include <boardwidget.h>
#include <matchcardwidget.h>
#include <matchtab.h>


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
    ui->roomTable->setColumnWidth(3, 150);
    ui->roomTable->setColumnWidth(4, 40);
    ui->roomTable->setColumnWidth(5, 150);

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
}

void MainWindow::on_ws_msg(QString data) {
    qDebug() << "ws: raw=" << data;

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
        int numPlayers = msg["msg"]["players"].toArray().size();
        for (int i = 0; i < numPlayers; ++i) {
            Player player {
                .id = msg["msg"]["players"][i]["playerId"].toString().toInt(),
                .name = msg["msg"]["players"][i]["name"].toString(),
                .nameNative = msg["msg"]["players"][i]["nameNative"].toString(),
                .country = msg["msg"]["players"][i]["country"].toString(),
                .rank = msg["msg"]["players"][i]["rank"].toString().replace("RANK_", ""),
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
    } else if (typ == "ListRoomsResponse") {
        initialRoomPages = msg["msg"]["pageCount"].toString().toInt();
        lastRoomPage = msg["msg"]["pageIndex"].toString().toInt();
        const int numRooms = msg["msg"]["roomInfo"].toArray().size();
        for (int i = 0; i < numRooms; ++i) {
            BroadcastRoom room {
                .id = msg["msg"]["roomInfo"][i]["roomId"].toString().toInt(),
                .type = msg["msg"]["roomInfo"][i]["roomType"].toString().replace("RT_", ""),
                .online = msg["msg"]["roomInfo"][i]["onlineCount"].toString().toInt(),
                .whitePlayer = BroadcastRoomPlayerInfo {
                     .id = msg["msg"]["roomInfo"][i]["playerIdWhite"].toString().toInt(),
                     .name = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["name"].toString(),
                     .nameNative = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["nameAlt"].toString(),
                     .rank = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["rank"].toString().replace("RANK_", ""),
                     .country = msg["msg"]["roomInfo"][i]["playerInfoWhite"]["country"].toString(),
                },
                .blackPlayer = BroadcastRoomPlayerInfo {
                     .id = msg["msg"]["roomInfo"][i]["playerIdBlack"].toString().toInt(),
                     .name = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["name"].toString(),
                     .nameNative = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["nameAlt"].toString(),
                     .rank = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["rank"].toString().replace("RANK_", ""),
                     .country = msg["msg"]["roomInfo"][i]["playerInfoBlack"]["country"].toString(),
                },
                .state = msg["msg"]["roomInfo"][i]["roomState"].toString().replace("RS_", ""),
                .broadcastInfo = msg["msg"]["roomInfo"][i]["broadcaster"].toString(),
            };
            m_roomModel.update(room);
        }
    } else {
        qDebug() << "ws: unhandled message type: " << typ;
    }


    progressDialog.setMaximum(initialPlayerPages+initialRoomPages);
    progressDialog.setValue(lastPlayerPage+lastRoomPage);
    if (initialPlayerPages > 0 && lastPlayerPage+1 == initialPlayerPages && initialRoomPages > 0 && lastRoomPage+1 == initialRoomPages) {
        progressDialog.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    // BoardWidget *board = new BoardWidget(ui->mainTabs, 19);
    // connect(board, &BoardWidget::pointClicked, this, [=](int r, int c) {
    //     board->setPoint(r, c, BoardWidget::PointState::kBlack);
    // });

    // MatchCardWidget *matchCard = new MatchCardWidget(ui->mainTabs);

    // QHBoxLayout *mainLayout = new QHBoxLayout();
    // mainLayout->addWidget(board);
    // mainLayout->addStretch();
    // mainLayout->addLayout(matchCard);

    MatchTab *matchTab = new MatchTab(ui->mainTabs);
    ui->mainTabs->addTab(matchTab, "Match: Room 42|10");
}

