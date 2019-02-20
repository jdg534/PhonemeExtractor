#include "WaveformDisplayWidget.h"
#include "ui_WaveformDisplayWidget.h"

WaveformDisplayWidget::WaveformDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveformDisplayWidget)
{
    ui->setupUi(this);
}

WaveformDisplayWidget::~WaveformDisplayWidget()
{
    delete ui;
}
