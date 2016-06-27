#ifndef REMOTECONTROLCLIENTWIDGET_H
#define REMOTECONTROLCLIENTWIDGET_H

#include <QWidget>
#include <QxtRPCPeer>
#include <QTimer>

namespace Ui {
class RemoteControlClientWidget;
}

class RemoteControlClientWidget : public QWidget {
    Q_OBJECT

public:
    explicit RemoteControlClientWidget( QWidget* parent = 0 );
    ~RemoteControlClientWidget();

private:
    void mouseMoveEvent( QMouseEvent* e );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e );
    void wheelEvent( QWheelEvent* e );

    void keyPressEvent( QKeyEvent* e );
    void keyReleaseEvent( QKeyEvent* e );

    QPoint toRealPos( const QPoint& mousePos );

private slots:
    void onStartStop();
    void onFrameAvailable( const QByteArray& imgData, const QSize& realSize );

    void onConnectedToServer();
    void onDisconnectedFromServer();
    void onServerError( const QAbstractSocket::SocketError& error );
    void refreshConnection();

    void onMouseMoveTimeOut();

private:
    Ui::RemoteControlClientWidget* ui;

    QxtRPCPeer m_peer;
    bool m_connected;

    QSize m_realFrameSize;

    QPoint m_mousePos;
    bool m_mouseMoved;
    QTimer m_mouseMoveTimer;
};

#endif // REMOTECONTROLCLIENTWIDGET_H
