#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent, const ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"Nick", "Rank", "W", "L", "Status"});
}

static QString statusString(const openfoxwq::PlayerInfo& player) {
    switch (player.status()) {
    case openfoxwq::PlayerStatus::PSTATUS_IDLE:
        return (player.accepting_matches() ? "Idle" : "Decline");
    case openfoxwq::PlayerStatus::PSTATUS_MATCH:
        return "Match";
    case openfoxwq::PlayerStatus::PSTATUS_WATCH:
        return "Watch";
    }
}

static QBrush statusColor(const openfoxwq::PlayerInfo& player) {
    switch (player.status()) {
    case openfoxwq::PlayerStatus::PSTATUS_IDLE:
        return (player.accepting_matches() ? Qt::darkGreen : Qt::gray);
    case openfoxwq::PlayerStatus::PSTATUS_MATCH:
        return Qt::darkMagenta;
    case openfoxwq::PlayerStatus::PSTATUS_WATCH:
        return Qt::darkYellow;
    }
}

void PlayerModel::update(const openfoxwq::PlayerInfo& updatedPlayer) {
    // Update internal data
    int index = 0;
    auto it = m_playerIndex.find(updatedPlayer.player_id());
    if (it != m_playerIndex.end()) {
        index = *it;
        m_players[index].MergeFrom(updatedPlayer);
    } else {
        index = size();
        m_playerIndex[updatedPlayer.player_id()] = index;
        m_players.append(updatedPlayer);
    }

    // Update model data
    const openfoxwq::PlayerInfo& player = m_players[index];
    QList<QStandardItem*> row {
        m_modelUtils.nickWithFlag(player.country(), QString::fromStdString(player.name()), Qt::AlignLeft, QString::fromStdString(player.name_native()), ModelUtils::colorForRank(player.rank())),
        m_modelUtils.alignedString(ModelUtils::rankString(player.rank()), Qt::AlignCenter, "", ModelUtils::colorForRank(player.rank())),
        m_modelUtils.alignedString(QString::number(player.ranked_wins()), Qt::AlignCenter),
        m_modelUtils.alignedString(QString::number(player.ranked_losses()), Qt::AlignCenter),
        m_modelUtils.alignedString(statusString(player), Qt::AlignLeft, "", statusColor(player)),
    };
    for (int c = 0; c < columnCount(); ++c) {
        setItem(index, c, row.at(c));
    }
}

bool PlayerModel::contains(PlayerId id) const {
    return m_playerIndex.contains(id);
}

void PlayerModel::remove(PlayerId id) {
    auto it = m_playerIndex.find(id);
    if (it == m_playerIndex.end()) {
        return;
    }

    const int index = *it;
    const int lastIndex = m_players.size()-1;
    auto row = takeRow(lastIndex);
    if (index < lastIndex) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(index, c, row.at(c));
        }
        m_players[index] = m_players[lastIndex];
        m_playerIndex[m_players[index].player_id()] = index;
    }

    m_players.pop_back();
    m_playerIndex.remove(id);
}

int PlayerModel::size() const { return m_players.size(); }

const openfoxwq::PlayerInfo& PlayerModel::getPlayerById(PlayerId id) const {
    return m_players[m_playerIndex[id]];
}

const openfoxwq::PlayerInfo& PlayerModel::getPlayer(int index) const {
    return m_players[index];
}
