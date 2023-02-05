#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>

#include "automatchpreset.h"
#include "soundfx.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent, QWebSocket& ws, SoundFx& sfx);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_connected();
    void on_disconnected();
    void on_binaryMessageReceived(QByteArray);
    void onWsError(QAbstractSocket::SocketError error);

private:
    QWebSocket& m_ws;
    SoundFx& m_sfx;
    Ui::LoginWindow *ui;
    bool gotServerInfo = false;
    bool gotProxyLineInfo = false;
    QVector<AutomatchPreset> automatchPresets;

};
#endif // LOGINWINDOW_H
