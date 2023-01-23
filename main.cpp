#include "loginwindow.h"

#include <QApplication>
#include <QWebSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("github.com/ale64bit");
    a.setApplicationName("openfoxwq");

    QWebSocket *ws = new QWebSocket;

    LoginWindow w(nullptr, ws);
    w.show();
    return a.exec();
}
