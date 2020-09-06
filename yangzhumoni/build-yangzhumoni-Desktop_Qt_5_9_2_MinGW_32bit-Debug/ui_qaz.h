/********************************************************************************
** Form generated from reading UI file 'qaz.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QAZ_H
#define UI_QAZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qaz
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qaz)
    {
        if (qaz->objectName().isEmpty())
            qaz->setObjectName(QStringLiteral("qaz"));
        qaz->resize(800, 600);
        menubar = new QMenuBar(qaz);
        menubar->setObjectName(QStringLiteral("menubar"));
        qaz->setMenuBar(menubar);
        centralwidget = new QWidget(qaz);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qaz->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(qaz);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        qaz->setStatusBar(statusbar);

        retranslateUi(qaz);

        QMetaObject::connectSlotsByName(qaz);
    } // setupUi

    void retranslateUi(QMainWindow *qaz)
    {
        qaz->setWindowTitle(QApplication::translate("qaz", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qaz: public Ui_qaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QAZ_H
