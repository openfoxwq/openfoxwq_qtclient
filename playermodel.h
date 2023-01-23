#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QStandardItemModel>
#include <QObject>

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
    QString rank;
    PlayerResults rankedResults;
    PlayerResults currentResults;
    PlayerResults totalResults;
};

class PlayerModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent, ModelUtils& modelUtils);

    void update(Player);
    bool contains(int id) const;
    void remove(int id);
    int size() const;

private:
    ModelUtils& m_modelUtils;
    QMap<int, int> m_playerIndex; // playerId -> row
};

#endif // PLAYERMODEL_H
