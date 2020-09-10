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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qaz
{
public:
    QWidget *centralwidget;
    QPushButton *return_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qaz)
    {
        if (qaz->objectName().isEmpty())
            qaz->setObjectName(QStringLiteral("qaz"));
        qaz->resize(800, 600);
        centralwidget = new QWidget(qaz);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        return_2 = new QPushButton(centralwidget);
        return_2->setObjectName(QStringLiteral("return_2"));
        return_2->setGeometry(QRect(260, 260, 131, 61));
        qaz->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qaz);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        qaz->setMenuBar(menubar);
        statusbar = new QStatusBar(qaz);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        qaz->setStatusBar(statusbar);

        retranslateUi(qaz);

        QMetaObject::connectSlotsByName(qaz);
    } // setupUi

    void retranslateUi(QMainWindow *qaz)
    {
        qaz->setWindowTitle(QApplication::translate("qaz", "MainWindow", Q_NULLPTR));
        return_2->setText(QApplication::translate("qaz", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qaz: public Ui_qaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QAZ_H
