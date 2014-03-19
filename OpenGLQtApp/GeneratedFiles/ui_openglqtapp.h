/********************************************************************************
** Form generated from reading UI file 'openglqtapp.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLQTAPP_H
#define UI_OPENGLQTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLQtAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLQtAppClass)
    {
        if (OpenGLQtAppClass->objectName().isEmpty())
            OpenGLQtAppClass->setObjectName(QStringLiteral("OpenGLQtAppClass"));
        OpenGLQtAppClass->resize(600, 400);
        menuBar = new QMenuBar(OpenGLQtAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        OpenGLQtAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLQtAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenGLQtAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OpenGLQtAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OpenGLQtAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OpenGLQtAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenGLQtAppClass->setStatusBar(statusBar);

        retranslateUi(OpenGLQtAppClass);

        QMetaObject::connectSlotsByName(OpenGLQtAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenGLQtAppClass)
    {
        OpenGLQtAppClass->setWindowTitle(QApplication::translate("OpenGLQtAppClass", "OpenGLQtApp", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenGLQtAppClass: public Ui_OpenGLQtAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLQTAPP_H
