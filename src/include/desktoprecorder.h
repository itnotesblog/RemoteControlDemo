#ifndef DESKTOPRECORDER_H
#define DESKTOPRECORDER_H

#include "desktoprecorder_global.h"

#include <QObject>
#include <QTimer>
#include <QImage>

namespace ITNotes {

static const uint MIN_FPS = 1;
static const uint MAX_FPS = 100;
static const uint DEFAULT_FPS = 30;

struct Cursor {
    QImage img;
    QPoint pos;
};

class DESKTOPRECORDERSHARED_EXPORT DesktopRecorder : public QObject {
    Q_OBJECT

public:
    explicit DesktopRecorder( QObject* parent = 0 );

    QImage makeScreenShot() const;
    Cursor captureCursor() const;

signals:
    void frameAvailable( const QImage& frame );

public slots:
    void start( uint fps = DEFAULT_FPS );
    void stop();
    void enableCursorCapture( bool enabled = true );

private slots:
    void onTimeOut();

private:
    QTimer m_timer;
    bool m_cursorCaptureEnabled;
};

}

#endif // DESKTOPRECORDER_H
