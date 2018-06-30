#include "phonemeextractormainwindow.h"
#include "ui_phonemeextractormainwindow.h"

PhonemeExtractorMainWindow::PhonemeExtractorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhonemeExtractorMainWindow)
{
    ui->setupUi(this);
}

PhonemeExtractorMainWindow::~PhonemeExtractorMainWindow()
{
    delete ui;
}
