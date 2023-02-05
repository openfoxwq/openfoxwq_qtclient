#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QProgressDialog>
#include <QMessageBox>

#include <google/protobuf/text_format.h>
#include <mainwindow.h>
#include <proto/ws.pb.h>

QSettings settings;

LoginWindow::LoginWindow(QWidget *parent, QWebSocket& ws, SoundFx& sfx)
    : QMainWindow(parent)
    , m_ws(ws)
    , m_sfx(sfx)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->usernameEdit->setText(settings.value("username", "").toString());
    ui->passwordEdit->setText(settings.value("password", "").toString());

    connect(&ws, &QWebSocket::connected, this, &LoginWindow::on_connected);
    connect(&ws, &QWebSocket::disconnected, this, &LoginWindow::on_disconnected);
    connect(&ws, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &LoginWindow::onWsError);

    m_ws.open(QUrl("ws://localhost:8999/"));

    setDisabled(true);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    openfoxwq::WsRequest req;
    openfoxwq::WsLoginRequest* loginReq = req.mutable_login();
    loginReq->set_username(ui->usernameEdit->text().toStdString());
    loginReq->set_password(ui->passwordEdit->text().toStdString());

    m_ws.sendBinaryMessage(QByteArray::fromStdString(req.SerializeAsString()));

    setDisabled(true);
}

void LoginWindow::on_connected() {
    qDebug() << "WebSocket connected";
    ui->connectingLabel->hide();
    connect(&m_ws, &QWebSocket::binaryMessageReceived, this, &LoginWindow::on_binaryMessageReceived);
}

void LoginWindow::on_disconnected() {
    qDebug() << "WebSocket disconnected";
}

void LoginWindow::onWsError(QAbstractSocket::SocketError /* error */) {
    qDebug() << "ws error: " << m_ws.errorString();
    QMessageBox::critical(this, "Error", "Failed to connect to local openfoxwq websocket server.\nIs it running?");
    exit(1);
}

void LoginWindow::on_binaryMessageReceived(QByteArray data) {
    openfoxwq::WsResponse resp;
    if (!resp.ParseFromArray(data.data(), data.size())) {
        qDebug() << "ws: error parsing response";
        exit(1);
    }

    std::string debugStr;
    google::protobuf::TextFormat::PrintToString(resp, &debugStr);
    qDebug() << "ws resp: " << QString::fromStdString(debugStr);

    bool updated = false;
    switch (resp.resp_case()) {
    case openfoxwq::WsResponse::kNavInfo:
        ui->proxyLineComboBox->clear();
        for (int i = 0; i < resp.navinfo().line_info_size(); ++i) {
            ui->proxyLineComboBox->addItem(QString::fromStdString(resp.navinfo().line_info(i).name()));
        }
        if (!gotProxyLineInfo) {
            gotProxyLineInfo = true;
            updated = true;
        }
        if (resp.navinfo().has_game_presets_json()) {
            automatchPresets.clear();
            auto json = QJsonDocument::fromJson(QByteArray::fromStdString(resp.navinfo().game_presets_json()));
            auto fieldInfo = json["FieldInfo"].toArray();
            for (int i = 0; i < fieldInfo.size(); ++i) {
                AutomatchPreset preset;
                preset.read(fieldInfo[i].toObject());
                automatchPresets.push_back(preset);
            }
        }
        break;
    case openfoxwq::WsResponse::kServerInfo:
        ui->serverNameComboBox->clear();
        ui->serverNameComboBox->addItem(QString::fromStdString(resp.serverinfo().name_loc().at(4)));
        if (!gotServerInfo) {
            gotServerInfo = true;
            updated = true;
        }
        break;
    case openfoxwq::WsResponse::kLogin:
        if (resp.login().has_player_id() && resp.login().player_id() != 0) {
            if (ui->rememberPasswordCheckBox->isChecked()) {
                settings.setValue("username", ui->usernameEdit->text());
                settings.setValue("password", ui->passwordEdit->text());
            }

            MainWindow* mainWindow = new MainWindow(nullptr, m_ws, m_sfx, resp.login().player_id(), automatchPresets);
            mainWindow->showMaximized();

            hide();
            disconnect(&m_ws, &QWebSocket::connected, this, &LoginWindow::on_connected);
            disconnect(&m_ws, &QWebSocket::disconnected, this, &LoginWindow::on_disconnected);
            disconnect(&m_ws, &QWebSocket::binaryMessageReceived, this, &LoginWindow::on_binaryMessageReceived);
        } else {
            QMessageBox msgBox;
            msgBox.setModal(true);
            msgBox.setText("Login failed. Check your username and password.");
            msgBox.exec();
        }
        setDisabled(false);
        break;
    default:
        break;
    }

    if (updated && gotProxyLineInfo && gotServerInfo) {
        setDisabled(false);
    }
}
