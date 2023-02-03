#include "roomtab.h"
#include "ui_roomtab.h"

#include <QDebug>
#include <QMessageBox>

#include <boardwidget.h>
#include <stringutils.h>
#include <proto/ws.pb.h>

RoomTab::RoomTab(QWidget *parent, QWebSocket& ws, SoundFx& sfx, const ModelUtils& modelUtils) :
    QWidget(parent)
    , ui(new Ui::RoomTab)
    , m_ws(ws)
    , m_sfx(sfx)
    , m_modelUtils(modelUtils) {
    ui->setupUi(this);
    ui->splitter_2->setStretchFactor(0, 1000);
    ui->splitter_2->setStretchFactor(1, 0);
}

RoomTab::~RoomTab() {
    delete ui;
}

void RoomTab::updateSettings(const openfoxwq::MatchSettings &settings) {
    m_settings = settings;

    ui->matchCard->setHandicap(m_settings.handicap(), m_settings.chinese_rules());
    ui->matchCard->setMainTime(m_settings.main_time_sec());

    ui->matchCard->setBlackTime(m_settings.main_time_sec());
    ui->matchCard->setBlackTimerPaused(true);
    ui->matchCard->setBlackPeriodsLeft(m_settings.byoyomi_periods());
    ui->matchCard->setBlackCaptures(0);

    ui->matchCard->setWhiteTime(m_settings.main_time_sec());
    ui->matchCard->setWhiteTimerPaused(true);
    ui->matchCard->setWhitePeriodsLeft(m_settings.byoyomi_periods());
    ui->matchCard->setWhiteCaptures(0);

    ui->matchCard->setByoyomi(m_settings.byoyomi_periods(), m_settings.byoyomi_time_sec());
}

void RoomTab::putHandicapStones() {
    switch (m_settings.handicap()) {
    case 2:
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        break;
    case 3:
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        break;
    case 4:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        break;
    case 5:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,9,openfoxwq::Color::COL_BLACK);
        break;
    case 6:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,15,openfoxwq::Color::COL_BLACK);
        break;
    case 7:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,9,openfoxwq::Color::COL_BLACK);
        break;
    case 8:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,9,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,9,openfoxwq::Color::COL_BLACK);
        break;
    case 9:
        ui->board->movePiece(3,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,3,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,15,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(3,9,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(15,9,openfoxwq::Color::COL_BLACK);
        ui->board->movePiece(9,9,openfoxwq::Color::COL_BLACK);
        break;
    }
}

void RoomTab::updateGameResult(openfoxwq::Color winner, int64_t scoreLead) {
    QString resultStr = QString("%1+ %2").arg(ModelUtils::colorShortString(winner), ModelUtils::formatScoreLead(scoreLead));
    ui->msgList->addItem(QString("Game Result: %1").arg(resultStr));

    QMessageBox msgBox;
    msgBox.setWindowTitle("Result");

    ui->matchCard->setBlackPeriodsLeft(1);
    ui->matchCard->setBlackTime(0);
    ui->matchCard->setWhitePeriodsLeft(1);
    ui->matchCard->setWhiteTime(0);

    QString reason;
    if (scoreLead == -1) {
        reason = "resignation";
    } else if (scoreLead == -2) {
        reason = "timeout";
    } else if (scoreLead == -3) {
        reason = "forfeit";
    } else {
        reason = ModelUtils::formatScoreLead(scoreLead);
    }

    msgBox.setText(QString("%1 wins by %2").arg(ModelUtils::colorString(winner), reason));
    msgBox.exec();
}

QPair<int, int> RoomTab::decodeMove(int mv) {
    return {
        ((mv>>5) & 0x1F),
        (mv & 0x1F),
    };
}


