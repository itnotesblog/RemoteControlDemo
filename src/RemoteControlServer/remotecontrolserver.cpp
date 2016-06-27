#include "remotecontrolserver.h"

#include <shareddefs.h>

#include <QBuffer>
#include <QCursor>
#include <QKeyEvent>
#include <QEvent>

#include <QDesktopWidget>

#include <string>

#ifdef Q_OS_LINUX
#   include <X11/extensions/XTest.h>
#elif defined Q_OS_WIN32
#   include <Windows.h>
#endif

static const QSize SCALED_FRAME_SIZE = QSize( 900, 550 );

RemoteControlServer::RemoteControlServer( QObject* parent ) : QObject( parent ) {
    connect( &m_peer, SIGNAL( clientConnected( quint64 ) ), SLOT( onClientConnected( quint64 ) ) );
    connect( &m_peer, SIGNAL( clientDisconnected( quint64 ) ), SLOT( onClientDisconnected( quint64 ) ) );

    connect( &m_recorder, SIGNAL( frameAvailable( QImage ) ), SLOT( onFrameAvailable( QImage ) ) );
    m_peer.attachSlot( ENABLE_CURSOR_CAPTURE_SIG, this, SLOT( onEnableCursorCapture( quint64, bool ) ) );
    m_peer.attachSlot( MOUSE_MOVE_SIG, this, SLOT( onMouseMoveRequest( quint64, QPoint ) ) );
    m_peer.attachSlot( MOUSE_PRESS_SIG, this, SLOT( onMousePressRequest( quint64, QPoint, int ) ) );
    m_peer.attachSlot( MOUSE_RELEASE_SIG, this, SLOT( onMouseReleaseRequest( quint64, QPoint, int ) ) );
    m_peer.attachSlot( MOUSE_WHEEL_SIG, this, SLOT( onMouseWheelRequest( quint64, int ) ) );
    m_peer.attachSlot( KEY_PRESS_SIG, this, SLOT( onKeyPressRequest( quint64, int, QString ) ) );
    m_peer.attachSlot( KEY_RELEASE_SIG, this, SLOT( onKeyReleaseRequest( quint64, int, QString ) ) );
}

bool RemoteControlServer::start() {
    return m_peer.listen( QHostAddress::Any, PORT );
}

void RemoteControlServer::onClientConnected( quint64 clientID ) {
    qDebug() << "Client connected:" << clientID;
    m_recorder.start( 10 );
}

void RemoteControlServer::onClientDisconnected( quint64 clientID ) {
    qDebug() << "Client disconnected:" << clientID;
    m_recorder.stop();
}

void RemoteControlServer::onEnableCursorCapture( quint64, bool enabled ) {
    m_recorder.enableCursorCapture( enabled );
}

void RemoteControlServer::onMouseMoveRequest( quint64, const QPoint& pos ) {
    QCursor::setPos( pos );
}

#ifdef Q_OS_LINUX
void onMouseAction( const QPoint& pos, Bool pressed, uint mouseBtn ) {
    QCursor::setPos( pos );

    Display* display = XOpenDisplay( nullptr );
    if( display == nullptr ) {
        return;
    }

    uint btn = 0;
    switch( mouseBtn ) {
    case Qt::LeftButton:
        btn = Button1;
        break;
    case Qt::RightButton:
        btn = Button3;
        break;
    case Qt::MiddleButton:
        btn = Button2;
        break;
    }

    XTestFakeButtonEvent( display, btn, pressed, CurrentTime );

    XFlush( display );
    XCloseDisplay( display );
}

void RemoteControlServer::onMousePressRequest( quint64, const QPoint& pos, int mouseBtn ) {
    onMouseAction( pos, True, mouseBtn );
}

void RemoteControlServer::onMouseReleaseRequest( quint64, const QPoint& pos, int mouseBtn ) {
    onMouseAction( pos, False, mouseBtn );
}

void RemoteControlServer::onMouseWheelRequest( quint64, int delta ) {
    Display* display = XOpenDisplay( nullptr );
    if( display == nullptr ) {
        return;
    }

    auto btn = ( 0 <= delta ) ? Button4 : Button5;

    XTestFakeButtonEvent( display, btn, True, 0 );
    XTestFakeButtonEvent( display, btn, False, 0 );

    XFlush( display );
    XCloseDisplay( display );
}

void onKeyAction( bool pressed, int keyCode, const QString& text ) {
    // TODO: Not implemented yet
}

#elif defined Q_OS_WIN32
void onMouseAction( const QPoint& pos, int flags ) {
    QCursor::setPos( pos );

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.dwFlags = flags;
    SendInput( 1, &input, sizeof( input ) );
}

void RemoteControlServer::onMousePressRequest( quint64, const QPoint& pos, int mouseBtn ) {
    int flags = MOUSEEVENTF_ABSOLUTE;
    switch ( mouseBtn ) {
    case Qt::LeftButton:
        flags |= MOUSEEVENTF_LEFTDOWN;
        break;
    case Qt::RightButton:
        flags |= MOUSEEVENTF_RIGHTDOWN;
        break;
    case Qt::MiddleButton:
        flags |= MOUSEEVENTF_MIDDLEDOWN;
        break;
    default:
        return;
    }
    onMouseAction( pos, flags );
}

void RemoteControlServer::onMouseReleaseRequest( quint64, const QPoint& pos, int mouseBtn ) {
    int flags = MOUSEEVENTF_ABSOLUTE;
    switch ( mouseBtn ) {
    case Qt::LeftButton:
        flags |= MOUSEEVENTF_LEFTUP;
        break;
    case Qt::RightButton:
        flags |= MOUSEEVENTF_RIGHTUP;
        break;
    case Qt::MiddleButton:
        flags |= MOUSEEVENTF_MIDDLEUP;
        break;
    default:
        return;
    }
    onMouseAction( pos, flags );
}

void RemoteControlServer::onMouseWheelRequest( quint64, int delta ) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = delta;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput( 1, &input, sizeof( input ) );
}

void onKeyAction( bool pressed, int keyCode, const QString& text ) {
    static KeyMapper keyMapper;

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;
    input.ki.time = 0;
    input.ki.dwExtraInfo = static_cast< ULONG_PTR >( 0 );
    if( ( input.ki.wVk = keyMapper.findNativeVirtualKeyCode( Qt::Key( keyCode ) ) ) != 0 ) {
        input.ki.wScan = 0;
    } else if( !text.isEmpty() ) {
        input.ki.dwFlags |= KEYEVENTF_UNICODE;
        input.ki.wScan = static_cast< WORD >( text.at( 0 ).unicode() );
    }

    SendInput( 1, &input, sizeof( input ) );
}
#endif

void RemoteControlServer::onKeyPressRequest( quint64, int keyCode, const QString& text ) {
    onKeyAction( true, keyCode, text );
}

void RemoteControlServer::onKeyReleaseRequest( quint64, int keyCode, const QString& text ) {
    onKeyAction( false, keyCode, text );
}

void RemoteControlServer::onFrameAvailable( const QImage& frame ) {
    QByteArray ba;
    QBuffer buffer( &ba );
    frame.scaled( SCALED_FRAME_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation ).save( &buffer, "JPG" );

    m_peer.call( FRAME_AVAILABLE_SIG, qCompress( ba, 9 ), frame.size() );
}
