#ifndef BROADCASTMODEL_H
#define BROADCASTMODEL_H

#include <QStandardItemModel>
#include <QObject>

#include <modelutils.h>
#include <proto/common.pb.h>


class BroadcastModel : public QStandardItemModel
{
    Q_OBJECT
public:
    using BroadcastId = int64_t;

    explicit BroadcastModel(QObject *parent, const ModelUtils& modelUtils);

    void update(const openfoxwq::BroadcastInfo&);
    bool contains(BroadcastId) const;
    void remove(BroadcastId);
    int size() const;
    void sortSpecial();

    const openfoxwq::BroadcastInfo& getBroadcastById(BroadcastId id) const;
    const openfoxwq::BroadcastInfo& getBroadcast(int index) const;

private:
    const ModelUtils& m_modelUtils;
    QVector<openfoxwq::BroadcastInfo> m_broadcasts;
    QMap<BroadcastId, int> m_broadcastIndex;

    void updateRow(int index, const openfoxwq::BroadcastInfo& broadcast);
};

#endif // BROADCASTMODEL_H
