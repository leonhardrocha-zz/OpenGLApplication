#include "stdafx.h"
#include "openglqtapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLQtApp w;
	w.show();
	return a.exec();
}
