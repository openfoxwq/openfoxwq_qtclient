#include "broadcastroommodel.h"

#include <stringutils.h>

BroadcastRoomModel::BroadcastRoomModel(QObject *parent, const ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"Room", "Type", "Online", "W", "", "B", "State", "Broadcaster"});
}

void BroadcastRoomModel::update(BroadcastRoom room) {
    constexpr int rankOffset = 8;
    QList<QStandardItem*> row;
    if (room.state == "RS_END") {
        row.append({
            m_modelUtils.alignedString(QString::number(room.id), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(StringUtils::toTitle(room.type.replace("RT_", "")), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(QString::number(room.online), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.nickWithFlag(room.whitePlayer.country, room.whitePlayer.name + QString("%1").arg(room.whitePlayer.rank.toString(), rankOffset), Qt::AlignRight, room.whitePlayer.nameNative, Qt::gray),
            m_modelUtils.alignedString(" vs ", Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.nickWithFlag(room.blackPlayer.country, QString(" %1").arg(room.blackPlayer.rank.toString(), -rankOffset) + room.blackPlayer.name, Qt::AlignLeft, room.blackPlayer.nameNative, Qt::gray),
            m_modelUtils.alignedString(StringUtils::toTitle(room.state.replace("RS_", "")), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(room.broadcastInfo, Qt::AlignLeft, "", Qt::gray),
        });
    } else {
        row.append({
            m_modelUtils.alignedString(QString::number(room.id), Qt::AlignCenter),
            m_modelUtils.alignedString(StringUtils::toTitle(room.type.replace("RT_", "")), Qt::AlignCenter),
            m_modelUtils.alignedString(QString::number(room.online), Qt::AlignCenter),
            m_modelUtils.nickWithFlag(room.whitePlayer.country, room.whitePlayer.name + QString("%1").arg(room.whitePlayer.rank.toString(), rankOffset), Qt::AlignRight, room.whitePlayer.nameNative, ModelUtils::colorForRank(room.whitePlayer.rank)),
            m_modelUtils.alignedString(" vs ", Qt::AlignCenter, "", Qt::darkYellow),
            m_modelUtils.nickWithFlag(room.blackPlayer.country, QString(" %1").arg(room.blackPlayer.rank.toString(), -rankOffset) + room.blackPlayer.name, Qt::AlignLeft, room.blackPlayer.nameNative, ModelUtils::colorForRank(room.blackPlayer.rank)),
            m_modelUtils.alignedString(StringUtils::toTitle(room.state.replace("RS_", "")), Qt::AlignCenter),
            m_modelUtils.alignedString(room.broadcastInfo, Qt::AlignLeft),
        });
    }

    auto it = m_roomIndex.find(room.id);
    if (it != m_roomIndex.end()) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(*it, c, row.at(c));
        }
        m_rooms[*it] = room;
    } else {
        m_roomIndex[room.id] = size();
        m_rooms.append(room);
        appendRow(row);
    }
}

bool BroadcastRoomModel::contains(int id) const {
    return m_roomIndex.contains(id);
}

void BroadcastRoomModel::remove(int id) {
    auto it = m_roomIndex.find(id);
    if (it == m_roomIndex.end()) {
        return;
    }

    auto row = takeRow(size()-1);
    for (int c = 0; c < columnCount(); ++c) {
        setItem(*it, c, row.at(c));
    }
    m_rooms[*it] = m_rooms.last();
    m_rooms.pop_back();
    m_roomIndex[row.first()->text().toInt()] = *it;
    m_roomIndex.remove(id);
}

int BroadcastRoomModel::size() const { return m_rooms.size(); }

const BroadcastRoom& BroadcastRoomModel::getRoomById(int id) const {
    return m_rooms[m_roomIndex[id]];
}

const BroadcastRoom& BroadcastRoomModel::getRoom(int index) const {
    return m_rooms[index];
}
