#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QStandardItemModel>
#include <QObject>

#include <rank.h>
#include <modelutils.h>

struct PlayerResults {
    int wins = 0;
    int losses = 0;
    int draws = 0;
};

struct Player {
    int id;
    QString name;
    QString nameNative;
    QString country;
    Rank rank;
    PlayerResults rankedResults;
    PlayerResults currentResults;
    PlayerResults totalResults;
};

class PlayerModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit PlayerModel(QObject *parent, const ModelUtils& modelUtils);

    void update(Player);
    bool contains(int id) const;
    void remove(int id);
    int size() const;

    const Player& getPlayerById(int id) const;
    const Player& getPlayer(int id) const;

private:
    const ModelUtils& m_modelUtils;
    QVector<Player> m_players;
    QMap<int, int> m_playerIndex; // playerId -> row
};

#endif // PLAYERMODEL_H
