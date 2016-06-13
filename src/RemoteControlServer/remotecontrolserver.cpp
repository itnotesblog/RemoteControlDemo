#include "remotecontrolserver.h"

#include <shareddefs.h>

#include <QBuffer>

RemoteControlServer::RemoteControlServer( QObject* parent ) : QObject( parent ) {
    connect( &m_peer, SIGNAL( clientConnected( quint64 ) ), SLOT( onClientConnected( quint64 ) ) );
    connect( &m_peer, SIGNAL( clientDisconnected( quint64 ) ), SLOT( onClientDisconnected( quint64 ) ) );

    connect( &m_recorder, SIGNAL( frameAvailable( QImage ) ), SLOT( onFrameAvailable( QImage ) ) );
    m_peer.attachSlot( ENABLE_CURSOR_CAPTURE_SIG, this, SLOT( onEnableCursorCapture( quint64, bool ) ) );
}

bool RemoteControlServer::start() {
    return m_peer.listen( QHostAddress::Any, PORT );
}

void RemoteControlServer::onClientConnected( quint64 clientID ) {
    qDebug() << "Client connected:" << clientID;
    m_recorder.start();
}

void RemoteControlServer::onClientDisconnected( quint64 clientID ) {
    qDebug() << "Client disconnected:" << clientID;
    m_recorder.stop();
}

void RemoteControlServer::onEnableCursorCapture( quint64, bool enabled ) {
    m_recorder.enableCursorCapture( enabled );
}

void RemoteControlServer::onFrameAvailable( const QImage& frame ) {
    QByteArray ba;
    QBuffer buffer( &ba );
    frame.save( &buffer, "JPG" );

    m_peer.call( FRAME_AVAILABLE_SIG, ba );
}
