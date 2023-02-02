#ifndef PLAYERINFODIALOG_H
#define PLAYERINFODIALOG_H

#include <QDialog>

#include <modelutils.h>
#include <proto/common.pb.h>
#include <proto/play.pb.h>

namespace Ui {
class PlayerInfoDialog;
}

class PlayerInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerInfoDialog(QWidget *parent, const openfoxwq::GetPlayerInfoResponse& playerInfo, const ModelUtils& modelUtils);
    ~PlayerInfoDialog();

signals:
    void roomClicked(const openfoxwq::RoomId& id);

private slots:
    void on_closeButton_clicked();
    void on_currentRoomsTable_cellDoubleClicked(int row, int column);

private:
    Ui::PlayerInfoDialog *ui;
    QVector<openfoxwq::RoomId> m_roomIds;
};

#endif // PLAYERINFODIALOG_H
