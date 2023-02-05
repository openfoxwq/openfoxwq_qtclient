#include "matchroomtab.h"
#include "ui_roomtab.h"

#include <QFileDialog>

#include "timeddecisiondialog.h"
#include "proto/ws.pb.h"

MatchRoomTab::MatchRoomTab(QWidget *parent, QNetworkAccessManager& nam, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelUtils, int64_t selfPlayerId, const openfoxwq::MatchStartEvent& matchStartEvent) :
    RoomTab(parent, nam, ws, sfx, modelUtils),
    m_selfPlayerId(selfPlayerId),
    m_matchStartEvent(matchStartEvent)
{
    m_roomId.set_id_1(m_matchStartEvent.room_id_1());
    m_roomId.set_id_2(m_matchStartEvent.room_id_2());
    m_roomId.set_id_3(m_matchStartEvent.room_id_3());
    m_roomId.set_id_4(m_matchStartEvent.room_id_4());

    connect(&m_syncTimer, &QTimer::timeout, this, &MatchRoomTab::on_syncTimer);
    m_syncTimer.setSingleShot(false);

    connect(&m_listParticipantsTimer, &QTimer::timeout, this, &MatchRoomTab::on_listParticipantsTimer);
    m_listParticipantsTimer.setSingleShot(false);
    m_listParticipantsTimer.start(10000);

    ui->board->setInteractive(false);
    ui->matchCard->setMatch(m_matchStartEvent, m_modelUtils);
    ui->matchCard->setSfx(&m_sfx);
    ui->msgList->addItem("Welcome to match room " + QString("%1|%2").arg(m_roomId.id_2()).arg(m_roomId.id_3()));

    ui->participantsTable->setColumnWidth(0, 150);
    ui->participantsTable->setColumnWidth(1, 60);
    ui->participantsTable->setColumnWidth(2, 80);
    ui->participantsTable->setColumnWidth(3, 80);

    openfoxwq::MatchSettings settings;
    settings.set_handicap(0); // TODO need to gather from match start event info
    settings.set_chinese_rules(m_matchStartEvent.automatch_preset().chinese_rules());
    settings.set_main_time_sec(m_matchStartEvent.match_info().main_time_sec());
    settings.set_byoyomi_periods(m_matchStartEvent.match_info().byoyomi_periods());
    settings.set_byoyomi_time_sec(m_matchStartEvent.match_info().byoyomi_time_sec());

    for (int i = 0; i < m_matchStartEvent.players_size(); ++i) {
        const auto& player = m_matchStartEvent.players(i);
        if (!player.has_avatar_url()) continue;
        QNetworkRequest req(QUrl(QString::fromStdString(player.avatar_url())));
        if (player.player_id() == m_matchStartEvent.match_info().player_id_white()) {
            m_whiteAvatarReply = m_nam.get(req);
            connect(m_whiteAvatarReply, &QNetworkReply::finished, this, &MatchRoomTab::onWhiteAvatarDownloaded);
        } else if (player.player_id() == m_matchStartEvent.match_info().player_id_black()) {
            m_blackAvatarReply = m_nam.get(req);
            connect(m_blackAvatarReply, &QNetworkReply::finished, this, &MatchRoomTab::onBlackAvatarDownloaded);
        }
    }

    updateSettings(settings);

    m_myTurn = (m_settings.handicap() > 1 && (m_selfPlayerId == m_matchStartEvent.match_info().player_id_white())) ||
        (m_settings.handicap() <= 1 && (m_selfPlayerId == m_matchStartEvent.match_info().player_id_black()));
    m_moveNum = 0;
    ui->passButton->setEnabled(m_myTurn);

    if (m_settings.handicap() > 1) {
        ui->matchCard->setWhiteTimerPaused(false);
    } else {
        ui->matchCard->setBlackTimerPaused(false);
    }

    connect(ui->board, &BoardWidget::pointClicked, this, &MatchRoomTab::on_pointClicked);
    ui->board->setInteractive(true);

    on_listParticipantsTimer();
}

MatchRoomTab::~MatchRoomTab() {
    if (m_whiteAvatarReply)
        delete m_whiteAvatarReply;
    if (m_blackAvatarReply)
        delete m_blackAvatarReply;
}

void MatchRoomTab::on_matchStart() {
    m_sfx.startToPlay();
    m_startedTs = std::chrono::steady_clock::now();
    qDebug() << ModelUtils::roomIdString(m_roomId) << ": match started";
    m_syncTimer.start(3000);

    ui->board->setInteractive(true);
    ui->resignButton->setEnabled(true);
    ui->requestCountingButton->setEnabled(true);
    // ui->aiRefereeButton->setEnabled(true);

    m_sgfDateTime = QDateTime::currentDateTime();
    m_sgfHeader += ";GM[1]FF[4]";
    m_sgfHeader += "AP[openfoxwq]";
    m_sgfHeader += QString("SZ[%1]").arg(ui->board->boardSize());
    m_sgfHeader += "GN[]";
    m_sgfHeader += QString("DT[%1]").arg(m_sgfDateTime.toString("yyyy-MM-dd")); // TODO set correctly
    for (int i = 0; i < m_matchStartEvent.players_size(); ++i) {
        const auto& player = m_matchStartEvent.players(i);
        if (player.player_id() == m_matchStartEvent.match_info().player_id_black()) {
            m_sgfHeader += QString("PB[%1]").arg(QString::fromStdString(player.name()));
            m_sgfHeader += QString("BR[%1]").arg(ModelUtils::rankString(player.rank()));
        } else if (player.player_id() == m_matchStartEvent.match_info().player_id_white()) {
            m_sgfHeader += QString("PW[%1]").arg(QString::fromStdString(player.name()));
            m_sgfHeader += QString("WR[%1]").arg(ModelUtils::rankString(player.rank()));
        }
    }
    if (m_settings.chinese_rules()) {
        m_sgfHeader += "RU[Chinese]";
    } else {
        m_sgfHeader += "RU[Japanese]";
    }
    if (m_settings.handicap() == 0) {
        m_sgfHeader += "HA[0]";
        if (m_settings.chinese_rules()) {
            m_sgfHeader += "KM[7.5]";
        } else {
            m_sgfHeader += "KM[6.5]";
        }
    } else if (m_settings.handicap() == 1) {
        m_sgfHeader += "HA[0]";
        m_sgfHeader += "KM[0.5]";
    } else {
        m_sgfHeader += QString("HA[%1]").arg(m_settings.handicap());
        m_sgfHeader += "KM[0.5]";
    }
    m_sgfHeader += QString("TM[%1]").arg(m_settings.main_time_sec());
    m_sgfHeader += QString("TC[%1]").arg(m_settings.byoyomi_periods());
    m_sgfHeader += QString("TT[%1]").arg(m_settings.byoyomi_time_sec());
}

void MatchRoomTab::on_nextMoveEvent(const openfoxwq::NextMoveEvent& event) {
    if (event.last_turn().move_count() > m_moveNum) {
        int captures = 0;
        ui->board->movePiece(event.y(), event.x(), event.col(), &captures);

        if (captures == 0) m_sfx.playStone();
        else if (captures == 1) m_sfx.playStoneCaptureOne();
        else if (captures <= 6) m_sfx.playStoneCaptureSome();
        else m_sfx.playStoneCaptureMany();

        toggleTurn();
    }
    updatePlayerTime(event.col(), event.time_state().main_time_left_sec());
    m_sgfMoves += QString(";%1[%2%3]")
            .arg(ModelUtils::colorShortString(event.col()))
            .arg(char('a' + event.x()))
            .arg(char('a' + event.y()));
}

void MatchRoomTab::on_pass(const openfoxwq::PassEvent& event) {
    const openfoxwq::Color turn = ui->board->turn();
    if (event.last_turn().move_count() > m_moveNum) {
        ui->board->toggleTurn();
        toggleTurn();
    }
    updatePlayerTime(turn, event.time_state().main_time_left_sec());
    m_sgfMoves += QString(";%1[]").arg(ModelUtils::colorShortString(turn));
}

void MatchRoomTab::updatePlayerTime(openfoxwq::Color color, int mainTimeLeft) {
    const auto byoyomiTime = m_matchStartEvent.match_info().byoyomi_time_sec();
    switch (color) {
    case openfoxwq::Color::COL_BLACK:
        ui->matchCard->setBlackTime(m_blackInByoyomi ? byoyomiTime : mainTimeLeft);
        ui->matchCard->setBlackTimerPaused(true);
        ui->matchCard->setWhiteTimerPaused(false);
        break;
    case openfoxwq::Color::COL_WHITE:
        ui->matchCard->setWhiteTime(m_whiteInByoyomi ? byoyomiTime : mainTimeLeft);
        ui->matchCard->setWhiteTimerPaused(true);
        ui->matchCard->setBlackTimerPaused(false);
        break;
    case openfoxwq::Color::COL_NONE:
        break;
    }
}

void MatchRoomTab::on_countdown(const openfoxwq::CountdownEvent& event) {
    if (event.byoyomi_periods_left() == m_matchStartEvent.match_info().byoyomi_periods()) {
        m_sfx.byoyomiStarts();
    } else if (event.byoyomi_periods_left() == 2) {
        m_sfx.twoByoyomiLeft();
    } else if (event.byoyomi_periods_left() == 1) {
        m_sfx.lastByoyomi();
    }

    const auto byoyomiTime = m_matchStartEvent.match_info().byoyomi_time_sec();
    switch (ui->board->turn()) {
    case openfoxwq::Color::COL_BLACK:
        m_blackInByoyomi = true;
        ui->matchCard->setBlackCountdown(true);
        ui->matchCard->setBlackTime(byoyomiTime);
        ui->matchCard->setBlackPeriodsLeft(event.byoyomi_periods_left());
        break;
    case openfoxwq::Color::COL_WHITE:
        m_whiteInByoyomi = true;
        ui->matchCard->setWhiteCountdown(true);
        ui->matchCard->setWhiteTime(byoyomiTime);
        ui->matchCard->setWhitePeriodsLeft(event.byoyomi_periods_left());
        break;
    default:
        break;
    }
}

void MatchRoomTab::on_resumeCountdown(const openfoxwq::ResumeCountdownEvent& event) {
    if (event.countdown().player_id() == m_matchStartEvent.match_info().player_id_black()) {
        ui->matchCard->setBlackTimerPaused(false);
    } else if (event.countdown().player_id() == m_matchStartEvent.match_info().player_id_white()) {
        ui->matchCard->setWhiteTimerPaused(false);
    }
    // TODO: use event info to set adjusted timer
    m_curStage = openfoxwq::CountingStage::STAGE_UNKNOWN;
}

void MatchRoomTab::on_countingDecision(const openfoxwq::CountingDecision& decision) {
    if (m_curStage == openfoxwq::CountingStage::STAGE_AGREE_TO_COUNT && decision.stage() == openfoxwq::CountingStage::STAGE_AGREE_TO_COUNT ) {
        if (decision.agree()) {
            m_curStage = openfoxwq::CountingStage::STAGE_AGREE_WITH_COUNT_RESULT;
        } else {
            ui->msgList->addItem("One of the players refused to count.");
        }
    } else if (m_curStage == openfoxwq::CountingStage::STAGE_AGREE_WITH_COUNT_RESULT && decision.stage() == openfoxwq::CountingStage::STAGE_AGREE_WITH_COUNT_RESULT) {
        if (decision.agree()) {
            // ???
        } else {
            ui->msgList->addItem("One of the players disagreed with the count result.");
        }
    }
}

void MatchRoomTab::on_countingEvent(const openfoxwq::CountingEvent& event) {
    if (event.stage() == openfoxwq::CountingStage::STAGE_AGREE_TO_COUNT) {
        TimedDecisionDialog dlg(this, "Info", "Your opponent requests automatic counting.", "Do you want to proceed?", event.time_left());
        openfoxwq::WsRequest req;
        auto countingDecision = req.mutable_countingdecision();
        countingDecision->set_room_id_2(m_roomId.id_2());
        auto decision = countingDecision->mutable_decision();
        decision->set_stage(event.stage());
        if (dlg.exec() == QDialog::Accepted) {
            decision->set_agree(true);
            m_curStage = openfoxwq::CountingStage::STAGE_AGREE_TO_COUNT;
        } else {
            decision->set_agree(false);
        }
        m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
    } else if (event.stage() == openfoxwq::CountingStage::STAGE_AGREE_WITH_COUNT_RESULT) {
        for (int i = 0; i < ui->board->boardSize(); ++i) {
            for (int j = 0; j < ui->board->boardSize(); ++j) {
                switch (event.ownership()[i*ui->board->boardSize() + j]) {
                case '0':
                    ui->board->setAnnotation(i, j, Annotation{AnnotationType::kNone});
                    break;
                case '1':
                    ui->board->setAnnotation(i, j, Annotation{AnnotationType::kSmallSquare, Qt::black});
                    break;
                case '2':
                    ui->board->setAnnotation(i, j, Annotation{AnnotationType::kSmallSquare, Qt::white});
                    break;
                }
            }
        }

        QString resultStr = QString("%1+ %2").arg(ModelUtils::colorShortString(event.winner())).arg(event.score_lead());
        TimedDecisionDialog dlg(this, "Info", QString("Result: %1").arg(resultStr), "Do you accept the result?", event.time_left());
        openfoxwq::WsRequest req;
        auto countingDecision = req.mutable_countingdecision();
        countingDecision->set_room_id_2(m_roomId.id_2());
        auto decision = countingDecision->mutable_decision();
        decision->set_stage(event.stage());
        if (dlg.exec() == QDialog::Accepted) {
            decision->set_agree(true);
            m_curStage = openfoxwq::CountingStage::STAGE_AGREE_WITH_COUNT_RESULT;
        } else {
            decision->set_agree(false);
        }
        m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));

        ui->board->clearAnnotations();
    }
}

void MatchRoomTab::on_gameResultEvent(const openfoxwq::GameResultEvent& event) {
    const openfoxwq::Color myColor = m_selfPlayerId == m_matchStartEvent.match_info().player_id_black()
            ? openfoxwq::Color::COL_BLACK
            : openfoxwq::Color::COL_WHITE;
    if (event.winner() == myColor) {
        m_sfx.winBell();
    }
    updateGameResult(event.winner(), event.score_lead());
    m_syncTimer.stop();

    ui->board->setInteractive(false);
    ui->passButton->setDisabled(true);
    ui->aiRefereeButton->setDisabled(true);
    ui->requestCountingButton->setDisabled(true);
    ui->resignButton->setDisabled(true);

    const auto [result, hasWinner] = ModelUtils::formatGameResult(event.winner(), event.score_lead());
    m_sgfHeader += QString("RE[%1]").arg(result);
}

void MatchRoomTab::on_roomParticipants(const openfoxwq::ListRoomParticipantsResponse &resp) {
    if (resp.error_code() != 0) {
        return;
    }
    ui->participantsTable->clearContents();
    ui->participantsTable->setSortingEnabled(false);
    ui->participantsTable->setRowCount(resp.participant_count());
    for (int i = 0; i < resp.participant_count(); ++i) {
        // user, rank, wins, losses
        const auto &participant = resp.participants(i);
        ui->participantsTable->setItem(i, 0, new QTableWidgetItem(m_modelUtils.flagForCountry(participant.country()), QString::fromStdString(participant.name())));
        ui->participantsTable->setItem(i, 1, new QTableWidgetItem(ModelUtils::rankString(participant.rank())));
        ui->participantsTable->setItem(i, 2, new QTableWidgetItem(QString::number(participant.wins())));
        ui->participantsTable->setItem(i, 3, new QTableWidgetItem(QString::number(participant.losses())));
    }
    ui->participantsTable->setSortingEnabled(true);
}

void MatchRoomTab::on_listParticipantsTimer() {
    openfoxwq::WsRequest req;
    openfoxwq::ListRoomParticipantsRequest *listReq = req.mutable_listroomparticipants();
    *listReq->mutable_id() = m_roomId;
    listReq->set_player_id_1(m_matchStartEvent.players(0).player_id());
    listReq->set_player_id_2(m_matchStartEvent.players(1).player_id());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MatchRoomTab::on_syncTimer() {
    openfoxwq::WsRequest req;

    auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_startedTs).count();

    auto *syncReq = req.mutable_syncmatchtime();
    syncReq->set_room_id_2(m_matchStartEvent.room_id_2());
    syncReq->set_ts(ts);

    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MatchRoomTab::on_pointClicked(int r, int c, openfoxwq::Color state) {
    if (!m_myTurn || m_curStage != openfoxwq::CountingStage::STAGE_UNKNOWN) {
        return;
    }

    int captures = 0;
    if (ui->board->movePiece(r, c, state, &captures)) {

        if (captures == 0) m_sfx.playStone();
        else if (captures == 1) m_sfx.playStoneCaptureOne();
        else if (captures <= 6) m_sfx.playStoneCaptureSome();
        else m_sfx.playStoneCaptureMany();

        openfoxwq::WsRequest req;
        auto moveReq = req.mutable_move();

        moveReq->set_room_id_2(m_matchStartEvent.room_id_2());

        auto move = moveReq->mutable_move();
        move->set_x(c);
        move->set_y(r);
        move->set_col(state);
        move->mutable_last_turn()->set_move_count(m_moveNum);

        m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));

        toggleTurn();
    }
}

bool MatchRoomTab::leaveRoom() {
    openfoxwq::WsRequest req;
    *req.mutable_leaveroom()->mutable_room_id() = m_roomId;
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
    return true;
}

void MatchRoomTab::on_passButton_clicked() {
    if (m_myTurn && m_curStage == openfoxwq::CountingStage::STAGE_UNKNOWN) {
        openfoxwq::WsRequest req;
        auto* wspass = req.mutable_pass();
        wspass->set_room_id_2(m_roomId.id_2());
        wspass->mutable_pass();
        auto* pass = wspass->mutable_pass();
        pass->mutable_last_turn()->set_move_count(m_moveNum);
        m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
    }
}

void MatchRoomTab::on_aiRefereeButton_clicked() {
    // TODO send pass
    qDebug() << "AI referee: not implemented";
}

void MatchRoomTab::on_requestCountingButton_clicked() {
    openfoxwq::WsRequest req;
    auto* requestCounting = req.mutable_requestcounting();
    requestCounting->set_room_id_2(m_roomId.id_2());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));

    ui->msgList->addItem("Automatic counting requested.");
    m_curStage = openfoxwq::CountingStage::STAGE_AGREE_TO_COUNT;
    ui->matchCard->setBlackTimerPaused(true);
    ui->matchCard->setWhiteTimerPaused(true);
}

void MatchRoomTab::on_resignButton_clicked() {
    openfoxwq::WsRequest req;
    auto* resign = req.mutable_resign();
    resign->set_room_id_2(m_roomId.id_2());
    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));
}

void MatchRoomTab::on_saveSgfButton_clicked() {
    QString defaultName = QString("%1_%2 - %3 vs %4.sgf").arg(
            m_sgfDateTime.toString("yyyy.MM.dd"),
            m_sgfDateTime.toString("hh.mm.ss"),
            QString::fromStdString(m_matchStartEvent.players(0).name()),
            QString::fromStdString(m_matchStartEvent.players(1).name()));
    auto sgfFileName = QFileDialog::getSaveFileName(this, "Save Game", defaultName, "Smart Game Format (*.sgf)");
    QFile file(sgfFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << "(" << m_sgfHeader << m_sgfMoves << ")";
    file.close();
}

void MatchRoomTab::toggleTurn() {
    m_myTurn = !m_myTurn;
    m_moveNum++;
    ui->passButton->setEnabled(m_myTurn);
}

void MatchRoomTab::onWhiteAvatarDownloaded() {
    QPixmap pixmap;
    pixmap.loadFromData(m_whiteAvatarReply->readAll());
    ui->matchCard->setWhiteAvatar(pixmap);
}

void MatchRoomTab::onBlackAvatarDownloaded() {
    QPixmap pixmap;
    pixmap.loadFromData(m_blackAvatarReply->readAll());
    ui->matchCard->setBlackAvatar(pixmap);
}
