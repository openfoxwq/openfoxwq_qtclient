#include "playermodel.h"

#include <QDebug>

PlayerModel::PlayerModel(QObject *parent, const ModelUtils& modelUtils) :
    QStandardItemModel(parent),
    m_modelUtils(modelUtils)
{
    setHorizontalHeaderLabels({"", "Username", "Rank", "W", "L", "Status"});
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
    updateRow(index, m_players[index]);
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

void PlayerModel::sortSpecial() {
    static QMap<openfoxwq::Flair, int> flairPriority = {
        {openfoxwq::Flair::FLAIR_GOLD_CROWN, 1},
        {openfoxwq::Flair::FLAIR_SILVER_CROWN, 2},
        {openfoxwq::Flair::FLAIR_PRO, 3},
        {openfoxwq::Flair::FLAIR_ELITE_AMATEUR, 4},
        {openfoxwq::Flair::FLAIR_TOP_AMATEUR, 5},
        {openfoxwq::Flair::FLAIR_NONE, 1<<20},
    };
    std::sort(m_players.begin(), m_players.end(), [](const openfoxwq::PlayerInfo& p1, const openfoxwq::PlayerInfo& p2) {
        auto p1Rank = p1.rank();
        auto p2Rank = p2.rank();
        if (p1Rank >= openfoxwq::Rank::RANK_1P) p1Rank = openfoxwq::Rank::RANK_9D;
        if (p2Rank >= openfoxwq::Rank::RANK_1P) p2Rank = openfoxwq::Rank::RANK_9D;

        if (p1Rank != p2Rank) {
            return p1Rank > p2Rank;
        }
        if (p1.flair() != p2.flair()) {
            return flairPriority[p1.flair()] < flairPriority[p2.flair()];
        }
        if (p1.flair() == openfoxwq::Flair::FLAIR_PRO && p1.rank() != p2.rank()) {
            return p1.rank() > p2.rank();
        }
        if (p1.amateur_6d() != p2.amateur_6d()) {
            return p1.amateur_6d() && !p2.amateur_6d();
        }
        if (p1.membership_type() != p2.membership_type()) {
            return p1.membership_type() > p2.membership_type();
        }
        return p1.player_id() < p2.player_id();
    });
    for (int i = 0; i < m_players.size(); ++i) {
        m_playerIndex[m_players[i].player_id()] = i;
        updateRow(i, m_players[i]);
    }
}

void PlayerModel::updateRow(int index, const openfoxwq::PlayerInfo& player) {
    setItem(index, 0, m_modelUtils.flair(player));
    setItem(index, 1, m_modelUtils.nickWithFlag(player.country(), QString::fromStdString(player.name()), Qt::AlignLeft, QString::fromStdString(player.name_native()), ModelUtils::colorForRank(player.rank())));
    setItem(index, 2, m_modelUtils.alignedString(ModelUtils::rankString(player.rank()), Qt::AlignCenter, "", ModelUtils::colorForRank(player.rank())));
    setItem(index, 3, m_modelUtils.alignedString(QString::number(player.ranked_wins()), Qt::AlignCenter));
    setItem(index, 4, m_modelUtils.alignedString(QString::number(player.ranked_losses()), Qt::AlignCenter));
    setItem(index, 5, m_modelUtils.alignedString(statusString(player), Qt::AlignLeft, "", statusColor(player)));
}
