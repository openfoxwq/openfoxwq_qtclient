#include "broadcastroommodel.h"

BroadcastRoomModel::BroadcastRoomModel(QObject *parent, ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"Room", "Type", "Online", "W", "", "B", "State", "Broadcaster"});
}

void BroadcastRoomModel::update(BroadcastRoom room) {
    constexpr int rankOffset = 8;
    QList<QStandardItem*> row {
        m_modelUtils.alignedString(QString::number(room.id), Qt::AlignCenter),
        m_modelUtils.alignedString(room.type.toLower(), Qt::AlignCenter),
        m_modelUtils.alignedString(QString::number(room.online), Qt::AlignCenter),
        m_modelUtils.nickWithFlag(room.whitePlayer.country, room.whitePlayer.name + QString("%1").arg(room.whitePlayer.rank, rankOffset), Qt::AlignRight, room.whitePlayer.nameNative, room.type == "RT_END" ? Qt::transparent : ModelUtils::colorForRank(room.whitePlayer.rank)),
        m_modelUtils.alignedString(" vs ", Qt::AlignCenter, "", Qt::darkYellow),
        m_modelUtils.nickWithFlag(room.blackPlayer.country, QString(" %1").arg(room.blackPlayer.rank, -rankOffset) + room.blackPlayer.name, Qt::AlignLeft, room.blackPlayer.nameNative, room.type == "RT_END" ? Qt::transparent : ModelUtils::colorForRank(room.blackPlayer.rank)),
        m_modelUtils.alignedString(room.state.toLower(), Qt::AlignCenter),
        m_modelUtils.alignedString(room.broadcastInfo, Qt::AlignLeft),
    };

    auto it = m_roomIndex.find(room.id);
    if (it != m_roomIndex.end()) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(*it, c, row.at(c));
        }
    } else {
        m_roomIndex[room.id] = size();
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
    m_roomIndex[row.first()->text().toInt()] = *it;
    m_roomIndex.remove(id);
}

int BroadcastRoomModel::size() const { return m_roomIndex.size(); }
