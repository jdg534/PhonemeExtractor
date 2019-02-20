#include "WaveformDisplayWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaveformDisplayWidget w;
    w.show();

    return a.exec();
}
