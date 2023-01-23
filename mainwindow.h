#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QWebSocket>
#include <QProgressDialog>

#include <boardwidget.h>
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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QWebSocket *ws;
    ModelUtils m_modelUtils;
    QProgressDialog progressDialog;
    BroadcastRoomModel m_roomModel;
    PlayerModel m_playerModel;

    int initialRoomPages = 0;
    int lastRoomPage = 0;
    int initialPlayerPages = 0;
    int lastPlayerPage = 0;
};

#endif // MAINWINDOW_H
