#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent, const ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"Nick", "Rank", "W", "L"});
}

void PlayerModel::update(Player player) {
    QList<QStandardItem*> row {
        m_modelUtils.nickWithFlag(player.country, player.name, Qt::AlignLeft, player.nameNative, ModelUtils::colorForRank(player.rank)),
        m_modelUtils.alignedString(player.rank.toString(), Qt::AlignCenter, "", ModelUtils::colorForRank(player.rank)),
        m_modelUtils.alignedString(QString::number(player.rankedResults.wins), Qt::AlignCenter),
        m_modelUtils.alignedString(QString::number(player.rankedResults.losses), Qt::AlignCenter),
    };

    auto it = m_playerIndex.find(player.id);
    if (it != m_playerIndex.end()) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(*it, c, row.at(c));
        }
        m_players[*it] = player;
    } else {
        m_playerIndex[player.id] = size();
        m_players.append(player);
        appendRow(row);
    }
}

bool PlayerModel::contains(int id) const {
    return m_playerIndex.contains(id);
}

void PlayerModel::remove(int id) {
    auto it = m_playerIndex.find(id);
    if (it == m_playerIndex.end()) {
        return;
    }

    auto row = takeRow(size()-1);
    for (int c = 0; c < columnCount(); ++c) {
        setItem(*it, c, row.at(c));
    }
    m_players[*it] = m_players.last();
    m_players.pop_back();
    m_playerIndex[row.first()->text().toInt()] = *it;
    m_playerIndex.remove(id);
}

int PlayerModel::size() const { return m_players.size(); }

const Player& PlayerModel::getPlayerById(int id) const {
    return m_players[m_playerIndex[id]];
}

const Player& PlayerModel::getPlayer(int index) const {
    return m_players[index];
}
