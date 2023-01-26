#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QWebSocket>
#include <QProgressDialog>

#include <boardwidget.h>
#include <matchtab.h>
#include <broadcastroommodel.h>
#include <playermodel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, QWebSocket* ws = nullptr);
    ~MainWindow();

private slots:
    void on_ws_disconnected();
    void on_ws_msg(QString);

    void on_roomTable_doubleClicked(const QModelIndex &index);
    void on_mainTabs_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    QWebSocket *ws;
    const ModelUtils m_modelUtils;
    QProgressDialog progressDialog;
    BroadcastRoomModel m_roomModel;
    PlayerModel m_playerModel;
    QMap<int, MatchTab*> m_activeRooms;

    int initialRoomPages = 0;
    int lastRoomPage = 0;
    int initialPlayerPages = 0;
    int lastPlayerPage = 0;
};

#endif // MAINWINDOW_H
