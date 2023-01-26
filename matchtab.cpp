#include "matchtab.h"
#include "ui_matchtab.h"

#include <QDebug>
#include <QMessageBox>
#include <boardwidget.h>
#include <stringutils.h>

inline void updateIfNotEmpty(int &dst, const int &src) {
    if (src != 0)
        dst = src;
}

inline QPair<int, int> decodeMove(int mv) {
    return {
        ((mv>>5) & (0x20-1)) ,
        (mv & (0x20-1)),
    };
}

MatchTab::MatchTab(QWidget *parent, BroadcastRoom room, const ModelUtils& modelUtils) :
    QWidget(parent),
    ui(new Ui::MatchTab),
    m_room(room),
    m_modelUtils(modelUtils)
{
    ui->setupUi(this);
    ui->board->setStyleSheet("background-image: url(:/assets/badukpan4_mirrored.png)");

    ui->matchCard->setRoom(m_room, m_modelUtils);
}

MatchTab::~MatchTab() {
    delete ui;
}

void MatchTab::updateRoomConfig(BroadcastRoomConfig config) {
    m_roomConfig = config;

    ui->matchCard->setHandicap(m_roomConfig.handicap, m_roomConfig.chineseRules);
    ui->matchCard->setMainTime(m_roomConfig.mainTime);
    ui->matchCard->setBlackTime(config.mainTime);
    ui->matchCard->setBlackTimerPaused(true);
    ui->matchCard->setWhiteTime(config.mainTime);
    ui->matchCard->setWhiteTimerPaused(true);
    ui->matchCard->setByoyomi(m_roomConfig.byoyomiPeriods, m_roomConfig.byoyomiTime);
    ui->matchCard->setBlackCaptures(0);
    ui->matchCard->setWhiteCaptures(0);
}

void MatchTab::updateRoomState(BroadcastRoomState state) {
    ui->board->setSound(false);
    PointState curCol = PointState::kBlack;
    if (m_roomConfig.handicap > 1) {
        switch (m_roomConfig.handicap) {
        case 2:
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            break;
        case 3:
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(3,3,PointState::kBlack);
            break;
        case 4:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            break;
        case 5:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            ui->board->movePiece(9,9,PointState::kBlack);
            break;
        case 6:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            ui->board->movePiece(9,3,PointState::kBlack);
            ui->board->movePiece(9,15,PointState::kBlack);
            break;
        case 7:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            ui->board->movePiece(9,3,PointState::kBlack);
            ui->board->movePiece(9,15,PointState::kBlack);
            ui->board->movePiece(9,9,PointState::kBlack);
            break;
        case 8:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            ui->board->movePiece(9,3,PointState::kBlack);
            ui->board->movePiece(9,15,PointState::kBlack);
            ui->board->movePiece(3,9,PointState::kBlack);
            ui->board->movePiece(15,9,PointState::kBlack);
            break;
        case 9:
            ui->board->movePiece(3,3,PointState::kBlack);
            ui->board->movePiece(3,15,PointState::kBlack);
            ui->board->movePiece(15,3,PointState::kBlack);
            ui->board->movePiece(15,15,PointState::kBlack);
            ui->board->movePiece(9,3,PointState::kBlack);
            ui->board->movePiece(9,15,PointState::kBlack);
            ui->board->movePiece(3,9,PointState::kBlack);
            ui->board->movePiece(15,9,PointState::kBlack);
            ui->board->movePiece(9,9,PointState::kBlack);
            break;
        }
        curCol = PointState::kWhite;
    }
    for (const int mv : qAsConst(state.encodedMoves)) {
        const auto [r, c] = decodeMove(mv);
        ui->board->movePiece(r, c, curCol);
        curCol = (curCol == PointState::kBlack) ? PointState::kWhite : PointState::kBlack;
    }
    ui->board->setSound(true);
    if (curCol == PointState::kBlack) {
        ui->matchCard->setBlackTimerPaused(false);
    } else {
        ui->matchCard->setWhiteTimerPaused(false);
    }
}

void MatchTab::updateMove(int playerId, int encodedMove, int /* moveNumber */, int timeLeft) {
    const auto [r, c] = decodeMove(encodedMove);
    if (playerId == m_roomConfig.playerIdBlack) {
        ui->board->movePiece(r, c, PointState::kBlack);
        ui->matchCard->setBlackTime(timeLeft>>2);
        ui->matchCard->setBlackTimerPaused(true);
        ui->matchCard->setWhiteTimerPaused(false);
    } else if (playerId == m_roomConfig.playerIdWhite) {
        ui->board->movePiece(r, c, PointState::kWhite);
        ui->matchCard->setWhiteTime(timeLeft>>2);
        ui->matchCard->setWhiteTimerPaused(true);
        ui->matchCard->setBlackTimerPaused(false);
    } else {
        qDebug() << "player id doesn't match room players in config";
    }
}

void MatchTab::updateTimeControl(int playerId, int currentPeriod, int timeLeft) {
    if (playerId == m_roomConfig.playerIdBlack) {
        ui->matchCard->setBlackInByoyomi();
        ui->matchCard->setBlackPeriodsLeft(currentPeriod);
        ui->matchCard->setBlackTime(timeLeft);
    } else if (playerId == m_roomConfig.playerIdWhite) {
        ui->matchCard->setWhiteInByoyomi();
        ui->matchCard->setWhitePeriodsLeft(currentPeriod);
        ui->matchCard->setWhiteTime(timeLeft);
    } else {
        qDebug() << "player id doesn't match room players in config";
    }
}

static QString formatScoreLead(int scoreLead) {
    const int i = scoreLead / 100;
    int f = scoreLead % 100;
    if (f%10 == 0) f/=10;
    if (f == 0) return QString::number(i);
    else return QString("%1.%2").arg(i).arg(f);
}

void MatchTab::gameResult(QString winner, int scoreLead) {
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
    } else {
        reason = formatScoreLead(scoreLead);
    }

    msgBox.setText(QString("%1 wins by %2").arg(StringUtils::toTitle(winner.replace("COL_", "")), reason));
    msgBox.exec();
}

