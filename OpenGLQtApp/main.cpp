#include "stdafx.h"
#include "OpenGLQtApp.h"
#include <QtWidgets/QApplication>

#include "window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    Window window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();

	OpenGLQtApp glApp(&window);
    return app.exec();
}
