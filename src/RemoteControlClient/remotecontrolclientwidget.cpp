#include "remotecontrolclientwidget.h"
#include "ui_remotecontrolclientwidget.h"

#include <shareddefs.h>

#include <QTimer>

static const int CONNECTION_RETRY_TIME_OUT_MSEC = 2 * 1000; // 2 секунды

RemoteControlClientWidget::RemoteControlClientWidget( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::RemoteControlClientWidget ),
    m_connected( false ) {
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
}

RemoteControlClientWidget::~RemoteControlClientWidget() {
    delete ui;
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
    Q_UNUSED( realSize )

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
