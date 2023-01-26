#ifndef BROADCASTROOMMODEL_H
#define BROADCASTROOMMODEL_H

#include <QStandardItemModel>
#include <QObject>

#include <rank.h>
#include <modelutils.h>

struct BroadcastRoomPlayerInfo {
    int id;
    QString name;
    QString nameNative;
    Rank rank;
    QString country;
};

struct BroadcastRoom {
    int id;
    QString type;
    int online;
    BroadcastRoomPlayerInfo whitePlayer;
    BroadcastRoomPlayerInfo blackPlayer;
    QString state;
    QString broadcastInfo;
};

class BroadcastRoomModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit BroadcastRoomModel(QObject *parent, const ModelUtils& modelUtils);

    void update(BroadcastRoom);
    bool contains(int id) const;
    void remove(int id);
    int size() const;

    const BroadcastRoom& getRoomById(int id) const;
    const BroadcastRoom& getRoom(int index) const;

private:
    const ModelUtils& m_modelUtils;
    QVector<BroadcastRoom> m_rooms;
    QMap<int, int> m_roomIndex; // roomId -> row
};

#endif // BROADCASTROOMMODEL_H
