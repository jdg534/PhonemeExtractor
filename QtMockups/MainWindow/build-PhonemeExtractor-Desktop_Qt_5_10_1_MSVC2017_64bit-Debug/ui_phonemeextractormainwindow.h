/********************************************************************************
** Form generated from reading UI file 'phonemeextractormainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHONEMEEXTRACTORMAINWINDOW_H
#define UI_PHONEMEEXTRACTORMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PhonemeExtractorMainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_MainWaveForm;
    QVBoxLayout *verticalLayout;
    QWidget *mainWaveformWidget;
    QGroupBox *groupBox_mainWaveFormControls;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_mainWaveFormPlay;
    QPushButton *pushButton_mainWaveFormPause;
    QPushButton *pushButton_mainWaveFormStop;
    QPushButton *pushButton_mainWaveformTargetSelection;
    QGroupBox *groupBox_extraction;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_currentSelection;
    QVBoxLayout *verticalLayout_2;
    QWidget *target_waveformWidget;
    QGroupBox *groupBox_mainWaveFormControls_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_targetPlay;
    QPushButton *pushButton_mainWaveFormPause_2;
    QPushButton *pushButton_mainWaveFormStop_2;
    QPushButton *pushButton_targetSectionPreviewSpectrum;
    QTableWidget *tableWidget_identifiedPhonemes;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PhonemeExtractorMainWindow)
    {
        if (PhonemeExtractorMainWindow->objectName().isEmpty())
            PhonemeExtractorMainWindow->setObjectName(QStringLiteral("PhonemeExtractorMainWindow"));
        PhonemeExtractorMainWindow->resize(733, 569);
        actionNew = new QAction(PhonemeExtractorMainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(PhonemeExtractorMainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(PhonemeExtractorMainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(PhonemeExtractorMainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        centralWidget = new QWidget(PhonemeExtractorMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_MainWaveForm = new QGroupBox(centralWidget);
        groupBox_MainWaveForm->setObjectName(QStringLiteral("groupBox_MainWaveForm"));
        verticalLayout = new QVBoxLayout(groupBox_MainWaveForm);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mainWaveformWidget = new QWidget(groupBox_MainWaveForm);
        mainWaveformWidget->setObjectName(QStringLiteral("mainWaveformWidget"));
        mainWaveformWidget->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(mainWaveformWidget);

        groupBox_mainWaveFormControls = new QGroupBox(groupBox_MainWaveForm);
        groupBox_mainWaveFormControls->setObjectName(QStringLiteral("groupBox_mainWaveFormControls"));
        horizontalLayout = new QHBoxLayout(groupBox_mainWaveFormControls);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_mainWaveFormPlay = new QPushButton(groupBox_mainWaveFormControls);
        pushButton_mainWaveFormPlay->setObjectName(QStringLiteral("pushButton_mainWaveFormPlay"));

        horizontalLayout->addWidget(pushButton_mainWaveFormPlay);

        pushButton_mainWaveFormPause = new QPushButton(groupBox_mainWaveFormControls);
        pushButton_mainWaveFormPause->setObjectName(QStringLiteral("pushButton_mainWaveFormPause"));

        horizontalLayout->addWidget(pushButton_mainWaveFormPause);

        pushButton_mainWaveFormStop = new QPushButton(groupBox_mainWaveFormControls);
        pushButton_mainWaveFormStop->setObjectName(QStringLiteral("pushButton_mainWaveFormStop"));

        horizontalLayout->addWidget(pushButton_mainWaveFormStop);

        pushButton_mainWaveformTargetSelection = new QPushButton(groupBox_mainWaveFormControls);
        pushButton_mainWaveformTargetSelection->setObjectName(QStringLiteral("pushButton_mainWaveformTargetSelection"));

        horizontalLayout->addWidget(pushButton_mainWaveformTargetSelection);


        verticalLayout->addWidget(groupBox_mainWaveFormControls);


        verticalLayout_3->addWidget(groupBox_MainWaveForm);

        groupBox_extraction = new QGroupBox(centralWidget);
        groupBox_extraction->setObjectName(QStringLiteral("groupBox_extraction"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_extraction);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_currentSelection = new QGroupBox(groupBox_extraction);
        groupBox_currentSelection->setObjectName(QStringLiteral("groupBox_currentSelection"));
        verticalLayout_2 = new QVBoxLayout(groupBox_currentSelection);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        target_waveformWidget = new QWidget(groupBox_currentSelection);
        target_waveformWidget->setObjectName(QStringLiteral("target_waveformWidget"));
        target_waveformWidget->setMinimumSize(QSize(0, 100));

        verticalLayout_2->addWidget(target_waveformWidget);

        groupBox_mainWaveFormControls_2 = new QGroupBox(groupBox_currentSelection);
        groupBox_mainWaveFormControls_2->setObjectName(QStringLiteral("groupBox_mainWaveFormControls_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_mainWaveFormControls_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_targetPlay = new QPushButton(groupBox_mainWaveFormControls_2);
        pushButton_targetPlay->setObjectName(QStringLiteral("pushButton_targetPlay"));

        horizontalLayout_2->addWidget(pushButton_targetPlay);

        pushButton_mainWaveFormPause_2 = new QPushButton(groupBox_mainWaveFormControls_2);
        pushButton_mainWaveFormPause_2->setObjectName(QStringLiteral("pushButton_mainWaveFormPause_2"));

        horizontalLayout_2->addWidget(pushButton_mainWaveFormPause_2);

        pushButton_mainWaveFormStop_2 = new QPushButton(groupBox_mainWaveFormControls_2);
        pushButton_mainWaveFormStop_2->setObjectName(QStringLiteral("pushButton_mainWaveFormStop_2"));

        horizontalLayout_2->addWidget(pushButton_mainWaveFormStop_2);

        pushButton_targetSectionPreviewSpectrum = new QPushButton(groupBox_mainWaveFormControls_2);
        pushButton_targetSectionPreviewSpectrum->setObjectName(QStringLiteral("pushButton_targetSectionPreviewSpectrum"));

        horizontalLayout_2->addWidget(pushButton_targetSectionPreviewSpectrum);


        verticalLayout_2->addWidget(groupBox_mainWaveFormControls_2);


        horizontalLayout_3->addWidget(groupBox_currentSelection);

        tableWidget_identifiedPhonemes = new QTableWidget(groupBox_extraction);
        if (tableWidget_identifiedPhonemes->columnCount() < 3)
            tableWidget_identifiedPhonemes->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_identifiedPhonemes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_identifiedPhonemes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_identifiedPhonemes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_identifiedPhonemes->setObjectName(QStringLiteral("tableWidget_identifiedPhonemes"));
        tableWidget_identifiedPhonemes->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout_3->addWidget(tableWidget_identifiedPhonemes);


        verticalLayout_3->addWidget(groupBox_extraction);

        PhonemeExtractorMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PhonemeExtractorMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 733, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PhonemeExtractorMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PhonemeExtractorMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PhonemeExtractorMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PhonemeExtractorMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PhonemeExtractorMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);

        retranslateUi(PhonemeExtractorMainWindow);

        QMetaObject::connectSlotsByName(PhonemeExtractorMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PhonemeExtractorMainWindow)
    {
        PhonemeExtractorMainWindow->setWindowTitle(QApplication::translate("PhonemeExtractorMainWindow", "Phoneme Extractor", nullptr));
        actionNew->setText(QApplication::translate("PhonemeExtractorMainWindow", "New", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("PhonemeExtractorMainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("PhonemeExtractorMainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("PhonemeExtractorMainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("PhonemeExtractorMainWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("PhonemeExtractorMainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_As->setText(QApplication::translate("PhonemeExtractorMainWindow", "Save As", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_As->setShortcut(QApplication::translate("PhonemeExtractorMainWindow", "Ctrl+Alt+S", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_MainWaveForm->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "Main Wave Form", nullptr));
        groupBox_mainWaveFormControls->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "Controls", nullptr));
        pushButton_mainWaveFormPlay->setText(QApplication::translate("PhonemeExtractorMainWindow", "Play", nullptr));
        pushButton_mainWaveFormPause->setText(QApplication::translate("PhonemeExtractorMainWindow", "Pause", nullptr));
        pushButton_mainWaveFormStop->setText(QApplication::translate("PhonemeExtractorMainWindow", "Stop", nullptr));
        pushButton_mainWaveformTargetSelection->setText(QApplication::translate("PhonemeExtractorMainWindow", "Target Selection", nullptr));
        groupBox_extraction->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "Extraction", nullptr));
        groupBox_currentSelection->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "Current Selection", nullptr));
        groupBox_mainWaveFormControls_2->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "Controls", nullptr));
        pushButton_targetPlay->setText(QApplication::translate("PhonemeExtractorMainWindow", "Play", nullptr));
        pushButton_mainWaveFormPause_2->setText(QApplication::translate("PhonemeExtractorMainWindow", "Pause", nullptr));
        pushButton_mainWaveFormStop_2->setText(QApplication::translate("PhonemeExtractorMainWindow", "Stop", nullptr));
        pushButton_targetSectionPreviewSpectrum->setText(QApplication::translate("PhonemeExtractorMainWindow", "Preview Spectrum", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_identifiedPhonemes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PhonemeExtractorMainWindow", "Phonetic Symbol", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_identifiedPhonemes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PhonemeExtractorMainWindow", "Start Point", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_identifiedPhonemes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PhonemeExtractorMainWindow", "End Point", nullptr));
        menuFile->setTitle(QApplication::translate("PhonemeExtractorMainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PhonemeExtractorMainWindow: public Ui_PhonemeExtractorMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHONEMEEXTRACTORMAINWINDOW_H
