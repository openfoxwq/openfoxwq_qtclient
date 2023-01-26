#ifndef MATCHTAB_H
#define MATCHTAB_H

#include <QWidget>

#include <modelutils.h>
#include <broadcastroommodel.h>

namespace Ui {
class MatchTab;
}

struct BroadcastRoomConfig {
    int playerIdBlack = 0;
    int playerIdWhite = 0;
    int playerIdFirst = 0;
    int playerIdSecond = 0;
    int handicap = 0;
    bool chineseRules = false;
    int mainTime = 0;
    int byoyomiTime = 0;
    int byoyomiPeriods = 0;
    int boardSize = 0;
};

struct BroadcastRoomState {
    QVector<int> encodedMoves;
    int moveCount;
};

class MatchTab : public QWidget
{
    Q_OBJECT

public:
    explicit MatchTab(QWidget *parent, BroadcastRoom room, const ModelUtils& modelUtils);
    ~MatchTab();

    BroadcastRoom getRoom() const { return m_room; }
    void updateRoomConfig(BroadcastRoomConfig);
    void updateRoomState(BroadcastRoomState);
    void updateMove(int playerId, int encodedMove, int moveNumber, int timeLeft);
    void updateTimeControl(int playerId, int currentPeriod, int timeLeft);
    void gameResult(QString winner, int scoreLead);

private:
    Ui::MatchTab *ui;
    BroadcastRoom m_room;
    const ModelUtils& m_modelUtils;

    BroadcastRoomConfig m_roomConfig;
};

#endif // MATCHTAB_H
