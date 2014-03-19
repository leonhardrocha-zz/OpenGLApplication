#ifndef OPENGLQTAPP_H
#define OPENGLQTAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_openglqtapp.h"

class OpenGLQtApp : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLQtApp(QWidget *parent = 0);
	~OpenGLQtApp();

private:
	Ui::OpenGLQtAppClass ui;
};

#endif // OPENGLQTAPP_H
