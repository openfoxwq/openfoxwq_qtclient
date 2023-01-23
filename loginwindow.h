#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr, QWebSocket *ws = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_ws_connected();
    void on_ws_disconnected();
    void on_ws_msg(QString);

private:
    QWebSocket *ws;
    Ui::LoginWindow *ui;
    bool gotServerInfo = false;
    bool gotProxyLineInfo = false;
};
#endif // LOGINWINDOW_H
