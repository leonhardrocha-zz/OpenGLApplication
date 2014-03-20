#include "stdafx.h"
#include "OpenGLQtApp.h"
#include "OpenGLWindow.h"
#include <QtWidgets/QApplication>

#include "window.h"

int main2(int argc, char *argv[])
{
	QApplication app(argc, argv);
    OpenGLQtApp window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();

	
    return app.exec();
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(4);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}