/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblDirection;
    QGraphicsView *imgBackground;
    QLabel *imgCar;
    QLabel *imgRaceTrack;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(959, 660);
        QIcon icon;
        icon.addFile(QStringLiteral(":/rc-car/img/car.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblDirection = new QLabel(centralWidget);
        lblDirection->setObjectName(QStringLiteral("lblDirection"));
        lblDirection->setGeometry(QRect(20, -10, 931, 51));
        QFont font;
        font.setPointSize(18);
        lblDirection->setFont(font);
        lblDirection->setAlignment(Qt::AlignCenter);
        imgBackground = new QGraphicsView(centralWidget);
        imgBackground->setObjectName(QStringLiteral("imgBackground"));
        imgBackground->setGeometry(QRect(15, 41, 931, 561));
        imgCar = new QLabel(centralWidget);
        imgCar->setObjectName(QStringLiteral("imgCar"));
        imgCar->setGeometry(QRect(620, 160, 81, 71));
        imgCar->setTextFormat(Qt::PlainText);
        imgCar->setPixmap(QPixmap(QString::fromUtf8(":/rc-car/img/car.png")));
        imgCar->setScaledContents(true);
        imgRaceTrack = new QLabel(centralWidget);
        imgRaceTrack->setObjectName(QStringLiteral("imgRaceTrack"));
        imgRaceTrack->setGeometry(QRect(20, 50, 921, 541));
        imgRaceTrack->setPixmap(QPixmap(QString::fromUtf8(":/rc-car/img/satview.png")));
        imgRaceTrack->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        lblDirection->raise();
        imgBackground->raise();
        imgRaceTrack->raise();
        imgCar->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 959, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RC Controller Demo", 0));
        lblDirection->setText(QApplication::translate("MainWindow", "---", 0));
        imgCar->setText(QString());
        imgRaceTrack->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
