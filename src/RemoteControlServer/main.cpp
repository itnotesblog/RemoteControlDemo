#include <QApplication>

#include "remotecontrolserver.h"

int main( int argc, char* argv[] ) {
    QApplication a( argc, argv );

    RemoteControlServer server;
    if( !server.start() ) {
        qDebug() << "Server failed to start";
        return 1;
    }

    qDebug() << "Server started";

    return a.exec();
}
