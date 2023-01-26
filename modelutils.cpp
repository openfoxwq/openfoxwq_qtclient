#include "modelutils.h"

void RightDecoratorStyledItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const {
    QStyledItemDelegate::initStyleOption(option, index);
    option->decorationPosition = QStyleOptionViewItem::Right;
    option->displayAlignment = Qt::AlignVCenter | Qt::AlignRight;
}

ModelUtils::ModelUtils()
{
    m_countryFlags[""] = QIcon(":/assets/flag-small/aq.png");

    m_countryFlags["ALBANIA"] = QIcon(":/assets/flag-small/al.png");
    m_countryFlags["CANADA"] = QIcon(":/assets/flag-small/ca.png");
    m_countryFlags["CHILE"] = QIcon(":/assets/flag-small/cl.png");
    m_countryFlags["CHINA"] = QIcon(":/assets/flag-small/cn.png");
    m_countryFlags["FRANCE"] = QIcon(":/assets/flag-small/fr.png");
    m_countryFlags["GERMANY"] = QIcon(":/assets/flag-small/de.png");
    m_countryFlags["HONGKONG"] = QIcon(":/assets/flag-small/hk.png");
    m_countryFlags["ITALY"] = QIcon(":/assets/flag-small/it.png");
    m_countryFlags["JAPAN"] = QIcon(":/assets/flag-small/jp.png");
    m_countryFlags["KOREA"] = QIcon(":/assets/flag-small/kr.png");
    m_countryFlags["MACAU"] = QIcon(":/assets/flag-small/mo.png");
    m_countryFlags["NETHERLANDS"] = QIcon(":/assets/flag-small/nl.png");
    m_countryFlags["PHILIPPINES"] = QIcon(":/assets/flag-small/ph.png");
    m_countryFlags["RUSSIA"] = QIcon(":/assets/flag-small/ru.png");
    m_countryFlags["SINGAPORE"] = QIcon(":/assets/flag-small/sg.png");
    m_countryFlags["SOUTHAFRICA"] = QIcon(":/assets/flag-small/za.png");
    m_countryFlags["SWEDEN"] = QIcon(":/assets/flag-small/se.png");
    m_countryFlags["TAIWAN"] = QIcon(":/assets/flag-small/tw.png");
    m_countryFlags["UKRAINE"] = QIcon(":/assets/flag-small/ua.png");
    m_countryFlags["USA"] = QIcon(":/assets/flag-small/us.png");
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

QStandardItem* ModelUtils::nickWithFlag(QString country, QString nick, Qt::Alignment alignment, QString tooltip, QBrush fg) const {
    QStandardItem *ret = new QStandardItem(flagForCountry(country), nick);
    ret->setTextAlignment(Qt::AlignVCenter | alignment);
    ret->setToolTip(tooltip);
    if (fg != Qt::transparent) {
        ret->setForeground(fg);
    }
    return ret;
}

QIcon ModelUtils::flagForCountry(QString country) const {
    auto it = m_countryFlags.find(country);
    if (it != m_countryFlags.end()) {
        return *it;
    }
    return m_countryFlags[""];
}

QBrush ModelUtils::colorForRank(Rank rank) {
    if (rank.isPro()) return QColor(11, 106, 214, 255);
    if (rank.isDan()) return QColor(204, 78, 80, 255);
    if (rank.isKyu() && rank.getValue() > 9) return Qt::gray;
    return Qt::transparent;
}
