#include "rank.h"

Rank::Rank() {
    m_value = 18;
    m_type = "K";
}

Rank::Rank(int value, QString type) : m_value(value), m_type(type) {}

Rank Rank::ofString(QString s) {
    s.replace("RANK_", "");
    return Rank(s.chopped(1).toInt(), s.right(1));
}
