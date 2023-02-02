#include "broadcastmodel.h"

#include <stringutils.h>

BroadcastModel::BroadcastModel(QObject *parent, const ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"Room", "Type", "Online", "W", "", "B", "State", "Broadcaster"});
}

void BroadcastModel::update(const openfoxwq::BroadcastInfo& broadcast) {
    constexpr int rankOffset = 8;
    QList<QStandardItem*> row;
    if (broadcast.state() == openfoxwq::BroadcastInfo_BroadcastState_RS_END) {
        row.append({
            m_modelUtils.alignedString(QString::number(broadcast.id()), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(ModelUtils::broadcastTypeString(broadcast.type()), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(QString::number(broadcast.online_count()), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.nickWithFlag(
                       broadcast.player_info_white().country(),
                       QString::fromStdString(broadcast.player_info_white().name())
                       + QString("%1").arg(ModelUtils::rankString(broadcast.player_info_white().rank()), rankOffset),
                       Qt::AlignRight,
                       QString::fromStdString(broadcast.player_info_white().name_alt()),
                       Qt::gray),
            m_modelUtils.alignedString(" vs ", Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.nickWithFlag(
                       broadcast.player_info_black().country(),
                       QString(" %1").arg(ModelUtils::rankString(broadcast.player_info_black().rank()), -rankOffset)
                       + QString::fromStdString(broadcast.player_info_black().name()),
                       Qt::AlignLeft,
                       QString::fromStdString(broadcast.player_info_black().name_alt()),
                       Qt::gray),
            m_modelUtils.alignedString(ModelUtils::broadcastStateString(broadcast.state()), Qt::AlignCenter, "", Qt::gray),
            m_modelUtils.alignedString(QString::fromStdString(broadcast.broadcaster()), Qt::AlignLeft, "", Qt::gray),
        });
    } else {
        row.append({
            m_modelUtils.alignedString(QString::number(broadcast.id()), Qt::AlignCenter),
            m_modelUtils.alignedString(ModelUtils::broadcastTypeString(broadcast.type()), Qt::AlignCenter),
            m_modelUtils.alignedString(QString::number(broadcast.online_count()), Qt::AlignCenter),
            m_modelUtils.nickWithFlag(
                       broadcast.player_info_white().country(),
                       QString::fromStdString(broadcast.player_info_white().name())
                       + QString("%1").arg(ModelUtils::rankString(broadcast.player_info_white().rank()), rankOffset),
                       Qt::AlignRight,
                       QString::fromStdString(broadcast.player_info_white().name_alt()),
                       ModelUtils::colorForRank(broadcast.player_info_white().rank())),
            m_modelUtils.alignedString(" vs ", Qt::AlignCenter, "", Qt::darkYellow),
            m_modelUtils.nickWithFlag(
                       broadcast.player_info_black().country(),
                       QString(" %1").arg(ModelUtils::rankString(broadcast.player_info_black().rank()), -rankOffset)
                       + QString::fromStdString(broadcast.player_info_black().name()),
                       Qt::AlignLeft,
                       QString::fromStdString(broadcast.player_info_black().name_alt()),
                       ModelUtils::colorForRank(broadcast.player_info_black().rank())),
            m_modelUtils.alignedString(ModelUtils::broadcastStateString(broadcast.state()), Qt::AlignCenter),
            m_modelUtils.alignedString(QString::fromStdString(broadcast.broadcaster()), Qt::AlignLeft),
        });
    }

    auto it = m_broadcastIndex.find(broadcast.id());
    if (it != m_broadcastIndex.end()) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(*it, c, row.at(c));
        }
        m_broadcasts[*it] = broadcast;
    } else {
        m_broadcastIndex[broadcast.id()] = size();
        m_broadcasts.append(broadcast);
        appendRow(row);
    }
}

bool BroadcastModel::contains(BroadcastId id) const {
    return m_broadcastIndex.contains(id);
}

void BroadcastModel::remove(BroadcastId id) {
    auto it = m_broadcastIndex.find(id);
    if (it == m_broadcastIndex.end()) {
        return;
    }

    auto row = takeRow(size()-1);
    for (int c = 0; c < columnCount(); ++c) {
        setItem(*it, c, row.at(c));
    }
    m_broadcasts[*it] = m_broadcasts.last();
    m_broadcasts.pop_back();
    m_broadcastIndex[row.first()->text().toInt()] = *it;
    m_broadcastIndex.remove(id);
}

int BroadcastModel::size() const { return m_broadcasts.size(); }

const openfoxwq::BroadcastInfo& BroadcastModel::getBroadcastById(BroadcastId id) const {
    return m_broadcasts[m_broadcastIndex[id]];
}

const openfoxwq::BroadcastInfo& BroadcastModel::getBroadcast(int index) const {
    return m_broadcasts[index];
}
