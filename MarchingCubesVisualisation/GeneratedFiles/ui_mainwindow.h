/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Visualisation.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionSave_STL;
    QAction *actionSaveAsStl;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSlider *isolevelSlider;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLineEdit *headerPath;
    QPushButton *selectHeaderBtn;
    QLineEdit *imagePath;
    QPushButton *selectImageBtn;
    QPushButton *generateObjectBtn;
    QCheckBox *enableWiring;
    QCheckBox *enableSlicing;
    QSlider *slicerSlider;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    Visualisation *widget;
    QSlider *thresholdSlider;
    QMenuBar *menuBar;
    QMenu *menuMarchingCubes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1170, 598);
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionSave_STL = new QAction(MainWindow);
        actionSave_STL->setObjectName(QStringLiteral("actionSave_STL"));
        actionSaveAsStl = new QAction(MainWindow);
        actionSaveAsStl->setObjectName(QStringLiteral("actionSaveAsStl"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        isolevelSlider = new QSlider(centralWidget);
        isolevelSlider->setObjectName(QStringLiteral("isolevelSlider"));
        isolevelSlider->setMaximum(255);
        isolevelSlider->setValue(200);
        isolevelSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(isolevelSlider, 0, 1, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setLayoutDirection(Qt::LeftToRight);
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        headerPath = new QLineEdit(layoutWidget);
        headerPath->setObjectName(QStringLiteral("headerPath"));
        headerPath->setMinimumSize(QSize(420, 0));
        headerPath->setMaximumSize(QSize(16777215, 16777215));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, headerPath);

        selectHeaderBtn = new QPushButton(layoutWidget);
        selectHeaderBtn->setObjectName(QStringLiteral("selectHeaderBtn"));
        selectHeaderBtn->setMinimumSize(QSize(100, 0));
        selectHeaderBtn->setMaximumSize(QSize(100, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, selectHeaderBtn);

        imagePath = new QLineEdit(layoutWidget);
        imagePath->setObjectName(QStringLiteral("imagePath"));
        imagePath->setMinimumSize(QSize(420, 0));
        imagePath->setMaximumSize(QSize(16777215, 16777215));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, imagePath);

        selectImageBtn = new QPushButton(layoutWidget);
        selectImageBtn->setObjectName(QStringLiteral("selectImageBtn"));
        selectImageBtn->setMinimumSize(QSize(100, 0));
        selectImageBtn->setMaximumSize(QSize(100, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, selectImageBtn);

        generateObjectBtn = new QPushButton(layoutWidget);
        generateObjectBtn->setObjectName(QStringLiteral("generateObjectBtn"));
        generateObjectBtn->setMaximumSize(QSize(100, 16777215));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, generateObjectBtn);

        enableWiring = new QCheckBox(layoutWidget);
        enableWiring->setObjectName(QStringLiteral("enableWiring"));
        enableWiring->setEnabled(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, enableWiring);

        enableSlicing = new QCheckBox(layoutWidget);
        enableSlicing->setObjectName(QStringLiteral("enableSlicing"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, enableSlicing);

        slicerSlider = new QSlider(layoutWidget);
        slicerSlider->setObjectName(QStringLiteral("slicerSlider"));
        slicerSlider->setEnabled(false);
        slicerSlider->setMinimumSize(QSize(420, 0));
        slicerSlider->setMaximum(1);
        slicerSlider->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, slicerSlider);


        verticalLayout_2->addLayout(formLayout_2);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new Visualisation(layoutWidget1);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(500, 500));
        isolevelSlider->raise();

        verticalLayout->addWidget(widget);

        thresholdSlider = new QSlider(layoutWidget1);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setMinimum(1);
        thresholdSlider->setMaximum(10);
        thresholdSlider->setPageStep(2);
        thresholdSlider->setValue(3);
        thresholdSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(thresholdSlider);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1170, 21));
        menuMarchingCubes = new QMenu(menuBar);
        menuMarchingCubes->setObjectName(QStringLiteral("menuMarchingCubes"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMarchingCubes->menuAction());
        menuMarchingCubes->addAction(actionSaveAsStl);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open File", 0));
        actionSave_STL->setText(QApplication::translate("MainWindow", "Export as .stl...", 0));
        actionSaveAsStl->setText(QApplication::translate("MainWindow", "Export as .STL ", 0));
        selectHeaderBtn->setText(QApplication::translate("MainWindow", "Select Header", 0));
        selectImageBtn->setText(QApplication::translate("MainWindow", "Select Image", 0));
        generateObjectBtn->setText(QApplication::translate("MainWindow", "Generate View", 0));
        enableWiring->setText(QApplication::translate("MainWindow", "Enable Wiring", 0));
        enableSlicing->setText(QApplication::translate("MainWindow", "Enable Slicing", 0));
        menuMarchingCubes->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
