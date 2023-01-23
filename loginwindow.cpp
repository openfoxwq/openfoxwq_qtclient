#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QProgressDialog>
#include <QMessageBox>

#include <loginmsg.h>
#include <mainwindow.h>

QSettings settings;

LoginWindow::LoginWindow(QWidget *parent, QWebSocket *ws)
    : QMainWindow(parent)
    , ws(ws)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->usernameEdit->setText(settings.value("username", "").toString());
    ui->passwordEdit->setText(settings.value("password", "").toString());

    connect(ws, &QWebSocket::connected, this, &LoginWindow::on_ws_connected);
    connect(ws, &QWebSocket::disconnected, this, &LoginWindow::on_ws_disconnected);

    ws->open(QUrl("ws://localhost:8999/"));

    setDisabled(true);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QJsonObject req;
    LoginMsg msg(ui->usernameEdit->text(), ui->passwordEdit->text());
    msg.write(req);
    ws->sendTextMessage(QJsonDocument(req).toJson(QJsonDocument::JsonFormat::Compact));

    setDisabled(true);
}

void LoginWindow::on_ws_connected() {
    qDebug() << "WebSocket connected";
    connect(ws, &QWebSocket::textMessageReceived, this, &LoginWindow::on_ws_msg);
}

void LoginWindow::on_ws_disconnected() {
    qDebug() << "WebSocket disconnected";
}

void LoginWindow::on_ws_msg(QString data) {
    qDebug() << "ws: raw=" << data;
    QJsonParseError err;
    auto msg = QJsonDocument::fromJson(data.toLocal8Bit(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "ws: json parse error: " << err.errorString();
        return;
    }

    bool updated = false;
    auto typ = msg["type"].toString();
    if (typ == "GetNavInfoResponse") {
        auto proxyLines = msg["msg"]["lineInfo"];
        auto n = proxyLines.toArray().size();
        ui->proxyLineComboBox->clear();
        for (int i = 0; i < n; ++i) {
            ui->proxyLineComboBox->insertItem(i, proxyLines[i]["name"].toString());
        }
        if (!gotProxyLineInfo) {
            gotProxyLineInfo = true;
            updated = true;
        }
    } else if (typ == "LobbySvrInfo") {
        auto serverName = msg["msg"]["nameLoc"]["4"].toString();
        ui->serverNameComboBox->clear();
        ui->serverNameComboBox->insertItem(0, serverName);
        if (!gotServerInfo) {
            gotServerInfo = true;
            updated = true;
        }
    } else if (typ == "LoginResponse") {
        qDebug() << msg["msg"];
        auto playerId = msg["msg"]["playerId"].toString();
        if (playerId == "0") {
            QMessageBox msgBox;
            msgBox.setModal(true);
            msgBox.setText("Login failed. Check your username and password.");
            msgBox.exec();
        } else {
            if (ui->rememberPasswordCheckBox->isChecked()) {
                settings.setValue("username", ui->usernameEdit->text());
                settings.setValue("password", ui->passwordEdit->text());
            }

            MainWindow* mainWindow = new MainWindow(nullptr, ws);
            mainWindow->showMaximized();

            hide();
            disconnect(ws, &QWebSocket::connected, this, &LoginWindow::on_ws_connected);
            disconnect(ws, &QWebSocket::disconnected, this, &LoginWindow::on_ws_disconnected);
            disconnect(ws, &QWebSocket::textMessageReceived, this, &LoginWindow::on_ws_msg);
        }
        setDisabled(false);
    } else {
        qDebug() << "ws: unhandled message type: " << typ;
    }

    if (updated && gotProxyLineInfo && gotServerInfo) {
        setDisabled(false);
    }
}
