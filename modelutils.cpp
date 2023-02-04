#include "modelutils.h"

void RightDecoratorStyledItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const {
    QStyledItemDelegate::initStyleOption(option, index);
    option->decorationPosition = QStyleOptionViewItem::Right;
    option->displayAlignment = Qt::AlignVCenter | Qt::AlignRight;
}

ModelUtils::ModelUtils() : m_unknownCountryFlag(":/assets/flag-small/aq.png")
{
    m_countryFlags[openfoxwq::Country::ALBANIA] = QIcon(":/assets/flag-small/al.png");
    m_countryFlags[openfoxwq::Country::BELARUS] = QIcon(":/assets/flag-small/by.png");
    m_countryFlags[openfoxwq::Country::BULGARIA] = QIcon(":/assets/flag-small/bg.png");
    m_countryFlags[openfoxwq::Country::CANADA] = QIcon(":/assets/flag-small/ca.png");
    m_countryFlags[openfoxwq::Country::CHILE] = QIcon(":/assets/flag-small/cl.png");
    m_countryFlags[openfoxwq::Country::CHINA] = QIcon(":/assets/flag-small/cn.png");
    m_countryFlags[openfoxwq::Country::FRANCE] = QIcon(":/assets/flag-small/fr.png");
    m_countryFlags[openfoxwq::Country::GERMANY] = QIcon(":/assets/flag-small/de.png");
    m_countryFlags[openfoxwq::Country::GREECE] = QIcon(":/assets/flag-small/gr.png");
    m_countryFlags[openfoxwq::Country::HONGKONG] = QIcon(":/assets/flag-small/hk.png");
    m_countryFlags[openfoxwq::Country::HUNGARY] = QIcon(":/assets/flag-small/hu.png");
    m_countryFlags[openfoxwq::Country::ITALY] = QIcon(":/assets/flag-small/it.png");
    m_countryFlags[openfoxwq::Country::JAPAN] = QIcon(":/assets/flag-small/jp.png");
    m_countryFlags[openfoxwq::Country::KOREA] = QIcon(":/assets/flag-small/kr.png");
    m_countryFlags[openfoxwq::Country::MACAU] = QIcon(":/assets/flag-small/mo.png");
    m_countryFlags[openfoxwq::Country::NETHERLANDS] = QIcon(":/assets/flag-small/nl.png");
    m_countryFlags[openfoxwq::Country::NEWZEALAND] = QIcon(":/assets/flag-small/nz.png");
    m_countryFlags[openfoxwq::Country::PHILIPPINES] = QIcon(":/assets/flag-small/ph.png");
    m_countryFlags[openfoxwq::Country::PORTUGAL] = QIcon(":/assets/flag-small/pt.png");
    m_countryFlags[openfoxwq::Country::RUSSIA] = QIcon(":/assets/flag-small/ru.png");
    m_countryFlags[openfoxwq::Country::SINGAPORE] = QIcon(":/assets/flag-small/sg.png");
    m_countryFlags[openfoxwq::Country::SOUTHAFRICA] = QIcon(":/assets/flag-small/za.png");
    m_countryFlags[openfoxwq::Country::SWEDEN] = QIcon(":/assets/flag-small/se.png");
    m_countryFlags[openfoxwq::Country::TAIWAN] = QIcon(":/assets/flag-small/tw.png");
    m_countryFlags[openfoxwq::Country::THAILAND] = QIcon(":/assets/flag-small/th.png");
    m_countryFlags[openfoxwq::Country::UKRAINE] = QIcon(":/assets/flag-small/ua.png");
    m_countryFlags[openfoxwq::Country::UK] = QIcon(":/assets/flag-small/uk.png");
    m_countryFlags[openfoxwq::Country::USA] = QIcon(":/assets/flag-small/us.png");
}

QStandardItem* ModelUtils::alignedString(QString s, Qt::Alignment alignment, QString tooltip, QBrush fg) const {
    QStandardItem *ret = new QStandardItem(s);
    ret->setTextAlignment(Qt::AlignVCenter | alignment);
    ret->setToolTip(tooltip);
    if (fg != Qt::transparent) {
        ret->setForeground(fg);
    }
    return ret;
}

QStandardItem* ModelUtils::nickWithFlag(openfoxwq::Country country, QString nick, Qt::Alignment alignment, QString tooltip, QBrush fg) const {
    QStandardItem *ret = new QStandardItem(flagForCountry(country), nick);
    ret->setTextAlignment(Qt::AlignVCenter | alignment);
    ret->setToolTip(tooltip);
    if (fg != Qt::transparent) {
        ret->setForeground(fg);
    }
    return ret;
}

QIcon ModelUtils::flagForCountry(openfoxwq::Country country) const {
    auto it = m_countryFlags.find(country);
    if (it != m_countryFlags.end()) {
        return *it;
    }
    return m_unknownCountryFlag;
}

QString ModelUtils::colorString(openfoxwq::Color col) {
    switch(col) {
    case openfoxwq::Color::COL_NONE: return "Unknown";
    case openfoxwq::Color::COL_BLACK: return "Black";
    case openfoxwq::Color::COL_WHITE: return "White";
    }
}


QString ModelUtils::colorShortString(openfoxwq::Color color) {
    switch (color) {
    case openfoxwq::Color::COL_NONE: return "?";
    case openfoxwq::Color::COL_BLACK: return "B";
    case openfoxwq::Color::COL_WHITE: return "W";
    }
}

QString ModelUtils::countryString(openfoxwq::Country country) {
    switch (country) {
    case openfoxwq::Country::UNKNOWN: return "?";
    case openfoxwq::Country::ALBANIA: return "Albania";
    case openfoxwq::Country::BELARUS: return "Belarus";
    case openfoxwq::Country::CANADA: return "Canada";
    case openfoxwq::Country::CHILE: return "Chile";
    case openfoxwq::Country::CHINA: return "China";
    case openfoxwq::Country::FRANCE: return "France";
    case openfoxwq::Country::GERMANY: return "Germany";
    case openfoxwq::Country::GREECE: return "Greece";
    case openfoxwq::Country::HONGKONG: return "Hong Kong";
    case openfoxwq::Country::HUNGARY: return "Hungary";
    case openfoxwq::Country::ITALY: return "Italy";
    case openfoxwq::Country::JAPAN: return "Japan";
    case openfoxwq::Country::KOREA: return "South Korea";
    case openfoxwq::Country::MACAU: return "Macau";
    case openfoxwq::Country::NETHERLANDS: return "Netherlands";
    case openfoxwq::Country::NEWZEALAND: return "New Zealand";
    case openfoxwq::Country::PHILIPPINES: return "Philippines";
    case openfoxwq::Country::RUSSIA: return "Russia";
    case openfoxwq::Country::SINGAPORE: return "Singapore";
    case openfoxwq::Country::SOUTHAFRICA: return "South Africa";
    case openfoxwq::Country::SWEDEN: return "Sweden";
    case openfoxwq::Country::TAIWAN: return "Taiwan";
    case openfoxwq::Country::THAILAND: return "Thailand";
    case openfoxwq::Country::UKRAINE: return "Ukraine";
    case openfoxwq::Country::UK: return "United Kingdom";
    case openfoxwq::Country::USA: return "United States";
    }
}

QString ModelUtils::rankString(openfoxwq::Rank rank) {
    switch (rank) {
    // DDK
    case openfoxwq::Rank::RANK_18K: return "18K";
    case openfoxwq::Rank::RANK_17K: return "17K";
    case openfoxwq::Rank::RANK_16K: return "16K";
    case openfoxwq::Rank::RANK_15K: return "15K";
    case openfoxwq::Rank::RANK_14K: return "14K";
    case openfoxwq::Rank::RANK_13K: return "13K";
    case openfoxwq::Rank::RANK_12K: return "12K";
    case openfoxwq::Rank::RANK_11K: return "11K";
    case openfoxwq::Rank::RANK_10K: return "10K";
    // SDK
    case openfoxwq::Rank::RANK_9K: return "9K";
    case openfoxwq::Rank::RANK_8K: return "8K";
    case openfoxwq::Rank::RANK_7K: return "7K";
    case openfoxwq::Rank::RANK_6K: return "6K";
    case openfoxwq::Rank::RANK_5K: return "5K";
    case openfoxwq::Rank::RANK_4K: return "4K";
    case openfoxwq::Rank::RANK_3K: return "3K";
    case openfoxwq::Rank::RANK_2K: return "2K";
    case openfoxwq::Rank::RANK_1K: return "1K";
    // DAN
    case openfoxwq::Rank::RANK_1D: return "1D";
    case openfoxwq::Rank::RANK_2D: return "2D";
    case openfoxwq::Rank::RANK_3D: return "3D";
    case openfoxwq::Rank::RANK_4D: return "4D";
    case openfoxwq::Rank::RANK_5D: return "5D";
    case openfoxwq::Rank::RANK_6D: return "6D";
    case openfoxwq::Rank::RANK_7D: return "7D";
    case openfoxwq::Rank::RANK_8D: return "8D";
    case openfoxwq::Rank::RANK_9D: return "9D";
    case openfoxwq::Rank::RANK_10D: return "10D";
    // PRO
    case openfoxwq::Rank::RANK_1P: return "1P";
    case openfoxwq::Rank::RANK_2P: return "2P";
    case openfoxwq::Rank::RANK_3P: return "3P";
    case openfoxwq::Rank::RANK_4P: return "4P";
    case openfoxwq::Rank::RANK_5P: return "5P";
    case openfoxwq::Rank::RANK_6P: return "6P";
    case openfoxwq::Rank::RANK_7P: return "7P";
    case openfoxwq::Rank::RANK_8P: return "8P";
    case openfoxwq::Rank::RANK_9P: return "9P";
    case openfoxwq::Rank::RANK_10P: return "10P";
    }
}

QPair<QString, QString> ModelUtils::rankNumberTypeString(openfoxwq::Rank rank) {
    switch (rank) {
    // DDK
    case openfoxwq::Rank::RANK_18K: return {"18", "Kyu"};
    case openfoxwq::Rank::RANK_17K: return {"17", "Kyu"};
    case openfoxwq::Rank::RANK_16K: return {"16", "Kyu"};
    case openfoxwq::Rank::RANK_15K: return {"15", "Kyu"};
    case openfoxwq::Rank::RANK_14K: return {"14", "Kyu"};
    case openfoxwq::Rank::RANK_13K: return {"13", "Kyu"};
    case openfoxwq::Rank::RANK_12K: return {"12", "Kyu"};
    case openfoxwq::Rank::RANK_11K: return {"11", "Kyu"};
    case openfoxwq::Rank::RANK_10K: return {"10", "Kyu"};
    // SDK
    case openfoxwq::Rank::RANK_9K: return {"9", "Kyu"};
    case openfoxwq::Rank::RANK_8K: return {"8", "Kyu"};
    case openfoxwq::Rank::RANK_7K: return {"7", "Kyu"};
    case openfoxwq::Rank::RANK_6K: return {"6", "Kyu"};
    case openfoxwq::Rank::RANK_5K: return {"5", "Kyu"};
    case openfoxwq::Rank::RANK_4K: return {"4", "Kyu"};
    case openfoxwq::Rank::RANK_3K: return {"3", "Kyu"};
    case openfoxwq::Rank::RANK_2K: return {"2", "Kyu"};
    case openfoxwq::Rank::RANK_1K: return {"1", "Kyu"};
    // DAN
    case openfoxwq::Rank::RANK_1D: return   {"1", "Dan"};
    case openfoxwq::Rank::RANK_2D: return   {"2", "Dan"};
    case openfoxwq::Rank::RANK_3D: return   {"3", "Dan"};
    case openfoxwq::Rank::RANK_4D: return   {"4", "Dan"};
    case openfoxwq::Rank::RANK_5D: return   {"5", "Dan"};
    case openfoxwq::Rank::RANK_6D: return   {"6", "Dan"};
    case openfoxwq::Rank::RANK_7D: return   {"7", "Dan"};
    case openfoxwq::Rank::RANK_8D: return   {"8", "Dan"};
    case openfoxwq::Rank::RANK_9D: return   {"9", "Dan"};
    case openfoxwq::Rank::RANK_10D: return {"10", "Dan"};
    // PRO
    case openfoxwq::Rank::RANK_1P: return   {"1", "Pro"};
    case openfoxwq::Rank::RANK_2P: return   {"2", "Pro"};
    case openfoxwq::Rank::RANK_3P: return   {"3", "Pro"};
    case openfoxwq::Rank::RANK_4P: return   {"4", "Pro"};
    case openfoxwq::Rank::RANK_5P: return   {"5", "Pro"};
    case openfoxwq::Rank::RANK_6P: return   {"6", "Pro"};
    case openfoxwq::Rank::RANK_7P: return   {"7", "Pro"};
    case openfoxwq::Rank::RANK_8P: return   {"8", "Pro"};
    case openfoxwq::Rank::RANK_9P: return   {"9", "Pro"};
    case openfoxwq::Rank::RANK_10P: return {"10", "Pro"};
    }
}

QBrush ModelUtils::colorForRank(openfoxwq::Rank rank) {
    if (rank >= openfoxwq::Rank::RANK_1P) return QColor(11, 106, 214, 255);
    if (rank >= openfoxwq::Rank::RANK_1D) return QColor(204, 78, 80, 255);
    if (rank <= openfoxwq::Rank::RANK_10K) return Qt::gray;
    return Qt::transparent;
}

QString ModelUtils::broadcastTypeString(openfoxwq::BroadcastInfo_BroadcastType broadcastType) {
    switch (broadcastType) {
    case openfoxwq::BroadcastInfo_BroadcastType_RT_UNKNOWN: return "Unknown";
    case openfoxwq::BroadcastInfo_BroadcastType_RT_MATCH: return "Match";
    case openfoxwq::BroadcastInfo_BroadcastType_RT_BROADCAST: return "Broadcast";
    case openfoxwq::BroadcastInfo_BroadcastType_RT_COMMENTARY: return "Commentary";
    case openfoxwq::BroadcastInfo_BroadcastType_RT_CHAMPIONSHIP: return "Championship";
    }
}

QString ModelUtils::broadcastStateString(openfoxwq::BroadcastInfo_BroadcastState broadcastState) {
    switch (broadcastState) {
    case openfoxwq::BroadcastInfo_BroadcastState_RS_UNKNOWN: return "Unknown";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_OPENING: return "Opening";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_1PERIOD: return "1. Period";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_MIDDLEGAME: return "Middlegame";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_ENDGAME: return "Endgame";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_END: return "End";
    case openfoxwq::BroadcastInfo_BroadcastState_RS_REVIEW: return "Review";
    }
}

QString ModelUtils::roomIdString(openfoxwq::RoomId roomId) {
    return QString("%1 | %2 | %3 | %4")
            .arg(roomId.id_1())
            .arg(roomId.id_2())
            .arg(roomId.id_3())
            .arg(roomId.id_4());
}

QString ModelUtils::formatScoreLead(int scoreLead) {
    const int i = scoreLead / 100;
    int f = scoreLead % 100;
    if (f%10 == 0) f/=10;
    if (f == 0) return QString::number(i);
    else return QString("%1.%2").arg(i).arg(f);
}

