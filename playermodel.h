#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QStandardItemModel>
#include <QObject>

#include <modelutils.h>
#include <proto/common.pb.h>

class PlayerModel : public QStandardItemModel
{
    Q_OBJECT

public:
    using PlayerId = int64_t;

    explicit PlayerModel(QObject *parent, const ModelUtils& modelUtils);

    void update(const openfoxwq::PlayerInfo&);
    bool contains(PlayerId) const;
    void remove(PlayerId);
    int size() const;

    const openfoxwq::PlayerInfo& getPlayerById(PlayerId id) const;
    const openfoxwq::PlayerInfo& getPlayer(int id) const;

private:
    const ModelUtils& m_modelUtils;
    QVector<openfoxwq::PlayerInfo> m_players;
    QMap<PlayerId, int> m_playerIndex;
};

#endif // PLAYERMODEL_H
