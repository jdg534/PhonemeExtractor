#ifndef WAVEFORMDISPLAYWIDGET_H
#define WAVEFORMDISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class WaveformDisplayWidget;
}

class WaveformDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaveformDisplayWidget(QWidget *parent = 0);
    ~WaveformDisplayWidget();

private:
    Ui::WaveformDisplayWidget *ui;
};

#endif // WAVEFORMDISPLAYWIDGET_H
