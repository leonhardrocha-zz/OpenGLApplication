#ifndef OPENGLQTAPP_H
#define OPENGLQTAPP_H
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include "ui_openglqtapp.h"
#include "GLWidget.h"

class OpenGLQtApp : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLQtApp(QWidget *parent = 0);
	~OpenGLQtApp();
protected:
    GLWidget *glWidget;

	void keyPressEvent(QKeyEvent *event);
private:
	Ui::OpenGLQtAppClass ui;
};

#endif // OPENGLQTAPP_H
