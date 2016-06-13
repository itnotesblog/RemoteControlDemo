#include "remotecontrolclientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteControlClientWidget w;
    w.show();

    return a.exec();
}
