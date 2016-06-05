#ifndef DESKTOPRECORDERDEMO_H
#define DESKTOPRECORDERDEMO_H

#include <QWidget>

#include <desktoprecorder.h>

namespace Ui {
class DesktopRecorderDemo;
}

class DesktopRecorderDemo : public QWidget {
    Q_OBJECT

public:
    explicit DesktopRecorderDemo( QWidget* parent = 0 );
    ~DesktopRecorderDemo();

private slots:
    void onStartStop();
    void onFrameAvailable( const QImage& img );

private:
    Ui::DesktopRecorderDemo* ui;

    ITNotes::DesktopRecorder m_recorder;
};

#endif // DESKTOPRECORDERDEMO_H
