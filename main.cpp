#include "loginwindow.h"
#include "boardtestwindow.h"
#include "soundfx.h"

#include <QApplication>
#include <QWebSocket>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("github.com/openfoxwq");
    a.setApplicationName("openfoxwq");

    // BoardTestWindow w(nullptr);
    // w.show();

    QNetworkAccessManager nam;
    QWebSocket ws;
    SoundFx soundFx(QLocale::Language::English);

    LoginWindow w(nullptr, nam, ws, soundFx);
    w.show();

    return a.exec();
}
