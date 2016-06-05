#include "desktoprecorderdemo.h"
#include "ui_desktoprecorderdemo.h"

DesktopRecorderDemo::DesktopRecorderDemo( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::DesktopRecorderDemo ) {
    ui->setupUi( this );

    ui->stopBn->hide();

    connect( ui->startBn, SIGNAL( clicked( bool ) ), SLOT( onStartStop() ) );
    connect( ui->stopBn, SIGNAL( clicked( bool ) ), SLOT( onStartStop() ) );
    connect( ui->captureCursorChkBox, SIGNAL( clicked( bool ) ), &m_recorder, SLOT( enableCursorCapture( bool ) ) );

    connect( &m_recorder, SIGNAL( frameAvailable( QImage ) ), SLOT( onFrameAvailable( QImage ) ) );
}

DesktopRecorderDemo::~DesktopRecorderDemo() {
    delete ui;
}

void DesktopRecorderDemo::onStartStop() {
    ui->startBn->isVisible() ? m_recorder.start() : m_recorder.stop();

    ui->startBn->setVisible( !ui->startBn->isVisible() );
    ui->stopBn->setVisible( !ui->stopBn->isVisible() );
}

void DesktopRecorderDemo::onFrameAvailable( const QImage& img ) {
    ui->viewLbl->setPixmap( QPixmap::fromImage( img ).scaled( ui->viewLbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
}
