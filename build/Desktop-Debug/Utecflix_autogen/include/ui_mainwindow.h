/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Search;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QListView *resultsListView;
    QWidget *Liked;
    QListView *likedListView;
    QWidget *WatchLater;
    QListView *watchLaterListView;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 10, 781, 521));
        Search = new QWidget();
        Search->setObjectName("Search");
        searchLineEdit = new QLineEdit(Search);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setGeometry(QRect(10, 10, 391, 34));
        searchButton = new QPushButton(Search);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(410, 10, 94, 36));
        resultsListView = new QListView(Search);
        resultsListView->setObjectName("resultsListView");
        resultsListView->setGeometry(QRect(10, 50, 391, 431));
        resultsListView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tabWidget->addTab(Search, QString());
        Liked = new QWidget();
        Liked->setObjectName("Liked");
        likedListView = new QListView(Liked);
        likedListView->setObjectName("likedListView");
        likedListView->setGeometry(QRect(10, 10, 391, 471));
        likedListView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tabWidget->addTab(Liked, QString());
        WatchLater = new QWidget();
        WatchLater->setObjectName("WatchLater");
        watchLaterListView = new QListView(WatchLater);
        watchLaterListView->setObjectName("watchLaterListView");
        watchLaterListView->setGeometry(QRect(10, 10, 391, 471));
        watchLaterListView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tabWidget->addTab(WatchLater, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 32));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Search), QCoreApplication::translate("MainWindow", "Search", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Liked), QCoreApplication::translate("MainWindow", "Liked", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(WatchLater), QCoreApplication::translate("MainWindow", "WatchLater", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
