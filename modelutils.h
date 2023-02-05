#ifndef MODELUTILS_H
#define MODELUTILS_H

#include <QString>
#include <QMap>
#include <QIcon>
#include <QStandardItem>
#include <QStyledItemDelegate>

#include <proto/common.pb.h>

class RightDecoratorStyledItemDelegate : public QStyledItemDelegate {
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
};

class ModelUtils
{
public:
    ModelUtils();

    QStandardItem* alignedString(QString s, Qt::Alignment, QString tooltip = "", QBrush fg = Qt::transparent) const;
    QStandardItem* nickWithFlag(openfoxwq::Country country, QString nick, Qt::Alignment alignment, QString tooltip = "", QBrush fg = Qt::transparent) const;
    QIcon flagForCountry(openfoxwq::Country country) const;

    static QString colorString(openfoxwq::Color color);
    static QString colorShortString(openfoxwq::Color color);
    static QString countryString(openfoxwq::Country country);
    static QString rankString(openfoxwq::Rank rank);
    static QPair<QString, QString> rankNumberTypeString(openfoxwq::Rank rank);
    static QBrush colorForRank(openfoxwq::Rank rank);
    static QString broadcastTypeString(openfoxwq::BroadcastInfo_BroadcastType broadcastType);
    static QString broadcastStateString(openfoxwq::BroadcastInfo_BroadcastState broadcastState);
    static QString roomIdString(openfoxwq::RoomId roomId);
    static QString formatScoreLead(int scoreLead);
    static QPair<QString, bool> formatGameResult(openfoxwq::Color winner, int64_t scoreLead);


private:
    QMap<openfoxwq::Country, QIcon> m_countryFlags;
    QIcon m_unknownCountryFlag;
};

#endif // MODELUTILS_H
