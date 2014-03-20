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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLQtAppClass
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLQtAppClass)
    {
        if (OpenGLQtAppClass->objectName().isEmpty())
            OpenGLQtAppClass->setObjectName(QStringLiteral("OpenGLQtAppClass"));
        OpenGLQtAppClass->resize(600, 400);
        centralwidget = new QWidget(OpenGLQtAppClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        horizontalLayout_2->addLayout(horizontalLayout);

        xSlider = new QSlider(centralwidget);
        xSlider->setObjectName(QStringLiteral("xSlider"));
        xSlider->setMaximum(5760);
        xSlider->setSingleStep(16);
        xSlider->setPageStep(160);
        xSlider->setOrientation(Qt::Vertical);
        xSlider->setTickPosition(QSlider::NoTicks);

        horizontalLayout_2->addWidget(xSlider);

        ySlider = new QSlider(centralwidget);
        ySlider->setObjectName(QStringLiteral("ySlider"));
        ySlider->setMaximum(5760);
        ySlider->setSingleStep(16);
        ySlider->setPageStep(160);
        ySlider->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(ySlider);

        zSlider = new QSlider(centralwidget);
        zSlider->setObjectName(QStringLiteral("zSlider"));
        zSlider->setMaximum(5760);
        zSlider->setSingleStep(16);
        zSlider->setPageStep(160);
        zSlider->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(zSlider);

        OpenGLQtAppClass->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(OpenGLQtAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        OpenGLQtAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLQtAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenGLQtAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
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
