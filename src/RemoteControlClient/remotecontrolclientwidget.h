#ifndef REMOTECONTROLCLIENTWIDGET_H
#define REMOTECONTROLCLIENTWIDGET_H

#include <QWidget>
#include <QxtRPCPeer>

namespace Ui {
class RemoteControlClientWidget;
}

class RemoteControlClientWidget : public QWidget {
    Q_OBJECT

public:
    explicit RemoteControlClientWidget( QWidget* parent = 0 );
    ~RemoteControlClientWidget();

private slots:
    void onStartStop();
    void onFrameAvailable( const QByteArray& imgData, const QSize& realSize );

    void onConnectedToServer();
    void onDisconnectedFromServer();
    void onServerError( const QAbstractSocket::SocketError& error );
    void refreshConnection();

private:
    Ui::RemoteControlClientWidget* ui;

    QxtRPCPeer m_peer;

    bool m_connected;
};

#endif // REMOTECONTROLCLIENTWIDGET_H
