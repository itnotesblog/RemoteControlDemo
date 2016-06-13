#include "desktoprecorder.h"

#include <QImage>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>

#include <QDebug>

#ifdef Q_OS_LINUX
#   include <X11/extensions/Xfixes.h>
#   include <QX11Info>
#elif defined Q_OS_WIN32
#   include <Windows.h>
#endif

namespace ITNotes {

DesktopRecorder::DesktopRecorder( QObject* parent ) : QObject( parent ), m_cursorCaptureEnabled( false ) {
    connect( &m_timer, SIGNAL( timeout() ), SLOT( onTimeOut() ) );
}

QImage DesktopRecorder::makeScreenShot() const {
    auto desktop = QApplication::desktop();
    auto geom = desktop->screenGeometry();
    auto pix = QPixmap::grabWindow( desktop->winId(), geom.x(), geom.y(), geom.width(), geom.height() );

    if( m_cursorCaptureEnabled ) {
        auto cursor = captureCursor();

        if( !cursor.img.isNull() ) {
            QPainter p;
            p.begin( &pix );
            p.drawImage( cursor.pos, cursor.img );
            p.end();
        }
    }

    return pix.toImage();
}

#ifdef Q_OS_LINUX
Cursor DesktopRecorder::captureCursor() const {
    Cursor cursor;

    if( auto curImage = XFixesGetCursorImage( QX11Info::display() ) ) {
        cursor.buffer.resize( curImage->width * curImage->height );
        for( int i = 0; i < cursor.buffer.size(); ++i ) {
            cursor.buffer[ i ] = curImage->pixels[ i ] & 0xffffffff;
        }
        cursor.img = QImage(
            reinterpret_cast< const uchar* >( cursor.buffer.data() ),
            curImage->width,
            curImage->height,
            QImage::Format_ARGB32_Premultiplied
        );
        cursor.pos = QCursor::pos() - QPoint( curImage->xhot, curImage->yhot );
        XFree( curImage );
    }

    return cursor;
}
#elif defined Q_OS_WIN32
QPixmap bottomPart( const QPixmap& pixmap ) {
    QSize size( pixmap.width(), pixmap.height() / 2 );
    return pixmap.copy( QRect( QPoint( 0, size.height() ), size ) );
}

Cursor DesktopRecorder::captureCursor() const {
    Cursor cursor;

    CURSORINFO cursorInfo = { 0 };
    cursorInfo.cbSize = sizeof(cursorInfo);

    if( GetCursorInfo( &cursorInfo ) ) {
        ICONINFO ii = { 0 };
        if( GetIconInfo( cursorInfo.hCursor, &ii ) ) {
            cursor.pos = QCursor::pos() - QPoint( ii.xHotspot, ii.yHotspot );

            DIBSECTION dsBitmap;
            DIBSECTION dsMask;
            if( GetObject( ii.hbmColor, sizeof( DIBSECTION ), &dsBitmap ) ) {
                cursor.img = QPixmap::fromWinHBITMAP( ii.hbmColor, QPixmap::PremultipliedAlpha ).toImage();
            } else if(  GetObject( ii.hbmMask, sizeof( DIBSECTION ), &dsMask ) ) {
                auto pMask = QPixmap::fromWinHBITMAP( ii.hbmMask, QPixmap::Alpha );

                cursor.img = QImage( pMask.width(), pMask.height() / 2, QImage::Format_ARGB4444_Premultiplied );
                cursor.img.fill( Qt::black );
                QPainter p;
                p.begin( &cursor.img );
                p.setCompositionMode( QPainter::CompositionMode_DestinationIn );
                p.drawPixmap( 0, 0, bottomPart( pMask ) );
                p.end();
            }

            DeleteObject( ii.hbmColor );
            DeleteObject( ii.hbmMask );
        }
    }

    return cursor;
}
#endif

void DesktopRecorder::start( uint fps ) {
    if( fps < MIN_FPS || MAX_FPS < fps ) {
        fps = DEFAULT_FPS;
    }
    m_timer.start( 1000 / fps );
}

void DesktopRecorder::stop() {
    m_timer.stop();
}

void DesktopRecorder::enableCursorCapture( bool enabled ) {
    m_cursorCaptureEnabled = enabled;
}

void DesktopRecorder::onTimeOut() {
    emit frameAvailable( makeScreenShot() );
}

}
