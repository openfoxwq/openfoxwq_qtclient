#ifndef MODELUTILS_H
#define MODELUTILS_H

#include <QString>
#include <QMap>
#include <QIcon>
#include <QStandardItem>
#include <QStyledItemDelegate>

#include <rank.h>

class RightDecoratorStyledItemDelegate : public QStyledItemDelegate {
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
};

class ModelUtils
{
public:
    ModelUtils();

    QStandardItem* alignedString(QString s, Qt::Alignment, QString tooltip = "", QBrush fg = Qt::transparent) const;
    QStandardItem* nickWithFlag(QString country, QString nick, Qt::Alignment alignment, QString tooltip = "", QBrush fg = Qt::transparent) const;
    QIcon flagForCountry(QString country) const;

    static QBrush colorForRank(Rank rank);

private:
    QMap<QString, QIcon> m_countryFlags;
};

#endif // MODELUTILS_H
