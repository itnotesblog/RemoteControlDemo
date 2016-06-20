#ifndef REMOTECONTROLSERVER_H
#define REMOTECONTROLSERVER_H

#include <QObject>
#include <QxtRPCPeer>
#include <desktoprecorder.h>

class RemoteControlServer : public QObject {
    Q_OBJECT
public:
    explicit RemoteControlServer( QObject* parent = 0 );

    bool start();

private slots:
    void onClientConnected( quint64 clientID );
    void onClientDisconnected( quint64 clientID );

    void onEnableCursorCapture( quint64, bool enabled );
    void onMouseMoveRequest( quint64, const QPoint& pos );
    void onMousePressRequest( quint64, const QPoint& pos, int mouseBtn );
    void onMouseReleaseRequest( quint64, const QPoint& pos, int mouseBtn );
    void onMouseWheelRequest( quint64, int delta );

    void onFrameAvailable( const QImage& frame );

private:
    QxtRPCPeer m_peer;
    ITNotes::DesktopRecorder m_recorder;

};

#endif // REMOTECONTROLSERVER_H
