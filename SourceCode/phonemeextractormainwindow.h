#ifndef PHONEMEEXTRACTORMAINWINDOW_H
#define PHONEMEEXTRACTORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PhonemeExtractorMainWindow;
}

class PhonemeExtractorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhonemeExtractorMainWindow(QWidget *parent = 0);
    ~PhonemeExtractorMainWindow();

private:
    Ui::PhonemeExtractorMainWindow *ui;
};

#endif // PHONEMEEXTRACTORMAINWINDOW_H
