#include "loginwindow.h"
#include "boardtestwindow.h"
#include "soundfx.h"

#include <QApplication>
#include <QWebSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("github.com/openfoxwq");
    a.setApplicationName("openfoxwq");

    // BoardTestWindow w(nullptr);
    // w.show();

    QWebSocket *ws = new QWebSocket;
    SoundFx soundFx(QLocale::Language::English);

    LoginWindow w(nullptr, *ws, soundFx);
    w.show();

    return a.exec();
}
