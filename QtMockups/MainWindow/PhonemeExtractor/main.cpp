#include "phonemeextractormainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhonemeExtractorMainWindow w;
    w.show();

    return a.exec();
}
