#ifndef BROADCASTROOMMODEL_H
#define BROADCASTROOMMODEL_H

#include <QStandardItemModel>
#include <QObject>

#include <modelutils.h>

struct BroadcastRoomPlayerInfo {
    int id;
    QString name;
    QString nameNative;
    QString rank;
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
    explicit BroadcastRoomModel(QObject *parent, ModelUtils& modelUtils);

    void update(BroadcastRoom);
    bool contains(int id) const;
    void remove(int id);
    int size() const;

private:
    ModelUtils& m_modelUtils;
    QMap<int, int> m_roomIndex; // roomId -> row
};

#endif // BROADCASTROOMMODEL_H
