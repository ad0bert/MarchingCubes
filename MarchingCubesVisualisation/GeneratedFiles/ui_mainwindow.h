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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
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
#include "tetrahedron.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionSave_STL;
    QAction *actionSaveAsStl;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *headerPath;
    QPushButton *selectHeaderBtn;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *imagePath;
    QPushButton *selectImageBtn;
    QPushButton *generateObjectBtn;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    Tetrahedron *widget;
    QSlider *thresholdSlider;
    QSlider *isolevelSlider;
    QMenuBar *menuBar;
    QMenu *menuMarchingCubes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(891, 605);
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
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        headerPath = new QLineEdit(layoutWidget);
        headerPath->setObjectName(QStringLiteral("headerPath"));

        horizontalLayout->addWidget(headerPath);

        selectHeaderBtn = new QPushButton(layoutWidget);
        selectHeaderBtn->setObjectName(QStringLiteral("selectHeaderBtn"));

        horizontalLayout->addWidget(selectHeaderBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        imagePath = new QLineEdit(layoutWidget);
        imagePath->setObjectName(QStringLiteral("imagePath"));

        horizontalLayout_2->addWidget(imagePath);

        selectImageBtn = new QPushButton(layoutWidget);
        selectImageBtn->setObjectName(QStringLiteral("selectImageBtn"));

        horizontalLayout_2->addWidget(selectImageBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        generateObjectBtn = new QPushButton(layoutWidget);
        generateObjectBtn->setObjectName(QStringLiteral("generateObjectBtn"));

        verticalLayout_2->addWidget(generateObjectBtn);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new Tetrahedron(layoutWidget1);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);

        thresholdSlider = new QSlider(layoutWidget1);
        thresholdSlider->setObjectName(QStringLiteral("thresholdSlider"));
        thresholdSlider->setMinimum(2);
        thresholdSlider->setMaximum(50);
        thresholdSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(thresholdSlider);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        isolevelSlider = new QSlider(centralWidget);
        isolevelSlider->setObjectName(QStringLiteral("isolevelSlider"));
        isolevelSlider->setMaximum(255);
        isolevelSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(isolevelSlider, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 21));
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
        menuMarchingCubes->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
