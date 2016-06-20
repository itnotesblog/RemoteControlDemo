#include "remotecontrolclientwidget.h"
#include "ui_remotecontrolclientwidget.h"

#include <shareddefs.h>

#include <QMouseEvent>
#include <QWheelEvent>

static const int CONNECTION_RETRY_TIME_OUT_MSEC = 2 * 1000; // 2 секунды
static const int MOUSE_FPS = 10;

RemoteControlClientWidget::RemoteControlClientWidget( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::RemoteControlClientWidget ),
    m_connected( false ),
    m_mouseMoved( false ) {
    ui->setupUi( this );

    ui->stopBn->hide();

    connect( ui->startBn, SIGNAL( clicked( bool ) ), SLOT( onStartStop() ) );
    connect( ui->stopBn, SIGNAL( clicked( bool ) ), SLOT( onStartStop() ) );

    connect( &m_peer, SIGNAL( connectedToServer() ), SLOT( onConnectedToServer() ) );
    connect( &m_peer, SIGNAL( disconnectedFromServer() ), SLOT( onDisconnectedFromServer() ) );
    connect(
        &m_peer,
        SIGNAL( serverError( const QAbstractSocket::SocketError& ) ),
        SLOT( onServerError( const QAbstractSocket::SocketError& ) )
    );

    m_peer.attachSlot( FRAME_AVAILABLE_SIG, this, SLOT( onFrameAvailable( QByteArray, QSize ) ) );
    m_peer.attachSignal( ui->captureCursorChkBox, SIGNAL( clicked( bool ) ), ENABLE_CURSOR_CAPTURE_SIG );

    setMouseTracking( true );
    ui->viewLbl->setMouseTracking( true );

    connect( &m_mouseMoveTimer, SIGNAL( timeout() ), SLOT( onMouseMoveTimeOut() ) );
    m_mouseMoveTimer.start( 1000 / MOUSE_FPS );
}

RemoteControlClientWidget::~RemoteControlClientWidget() {
    delete ui;
}

void RemoteControlClientWidget::mouseMoveEvent( QMouseEvent* e ) {
    if( m_connected ) {
        auto pos = toRealPos( e->pos() );
        m_mouseMoved = ( m_mousePos != pos );
        m_mousePos = pos;
    }
}

void RemoteControlClientWidget::mousePressEvent( QMouseEvent* e ) {
    if( m_connected ) {
        m_mousePos = toRealPos( e->pos() );
        m_peer.call( MOUSE_PRESS_SIG, m_mousePos, e->button() );
    }
}

void RemoteControlClientWidget::mouseReleaseEvent( QMouseEvent* e ) {
    if( m_connected ) {
        m_mousePos = toRealPos( e->pos() );
        m_peer.call( MOUSE_RELEASE_SIG, m_mousePos, e->button() );
    }
}

void RemoteControlClientWidget::wheelEvent( QWheelEvent* e ) {
    if( m_connected ) {
        m_peer.call( MOUSE_WHEEL_SIG, e->delta() );
    }
}

QPoint RemoteControlClientWidget::toRealPos( const QPoint& mousePos ) {
    auto realPos = ui->viewLbl->mapFromParent( mousePos );

    if( ui->viewLbl->pixmap() ) {
        auto viewRect = ui->viewLbl->rect();
        auto imgRect =  ui->viewLbl->pixmap()->rect();

        auto xOffset = ( viewRect.width() - imgRect.width() ) / 2;
        auto yOffset = ( viewRect.height() - imgRect.height() ) / 2;

        realPos = QPoint( realPos.x() - xOffset,  realPos.y() - yOffset );

        if( realPos.x() < 0 )  realPos.setX( 0 );
        if( realPos.y() < 0 )  realPos.setY( 0 );

        if( imgRect.width() != 0 ) {
            auto ratio = m_realFrameSize.width() / static_cast< double >( imgRect.width() );
            realPos.setX( realPos.x() * ratio );
            realPos.setY( realPos.y() * ratio );

            if( m_realFrameSize.width() < realPos.x() )  realPos.setX( m_realFrameSize.width() );
            if( m_realFrameSize.height() < realPos.y() )  realPos.setY( m_realFrameSize.height() );
        }
    }

    return realPos;
}

void RemoteControlClientWidget::onStartStop() {
    if( ui->startBn->isVisible() ) {
        refreshConnection();
    } else {
        m_peer.disconnectServer();
        m_connected = false;
    }

    ui->startBn->setVisible( !ui->startBn->isVisible() );
    ui->stopBn->setVisible( !ui->stopBn->isVisible() );
    ui->ipEd->setEnabled( !ui->stopBn->isVisible() );
}

void RemoteControlClientWidget::onFrameAvailable( const QByteArray& imgData, const QSize& realSize ) {
    m_realFrameSize = realSize;

    auto img = QImage::fromData( qUncompress( imgData ), "JPG" );
    ui->viewLbl->setPixmap( QPixmap::fromImage( img ).scaled( ui->viewLbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
}

void RemoteControlClientWidget::onConnectedToServer() {
    qDebug() << "Connected to server";
    m_connected = true;

    ui->startBn->setVisible( false );
    ui->stopBn->setVisible( true );
    ui->ipEd->setEnabled( false );

    m_peer.call( ENABLE_CURSOR_CAPTURE_SIG, ui->captureCursorChkBox->isChecked() );
}

void RemoteControlClientWidget::onDisconnectedFromServer() {
    qDebug() << "Disconnected from server";
    m_connected = false;
}

void RemoteControlClientWidget::onServerError( const QAbstractSocket::SocketError& error ) {
    qDebug() << "Server error:" << QString::number( error, 16 );
    m_connected = false;
    if( ui->stopBn->isVisible() ) {
        QTimer::singleShot( CONNECTION_RETRY_TIME_OUT_MSEC, this, SLOT( refreshConnection() ) );
    }
}

void RemoteControlClientWidget::refreshConnection() {
    if( !m_connected ) {
        m_peer.connect( ui->ipEd->text(), PORT );
    }
}

void RemoteControlClientWidget::onMouseMoveTimeOut() {
    if( m_mouseMoved ) {
        m_peer.call( MOUSE_MOVE_SIG, m_mousePos );
        m_mouseMoved = false;
    }
}
