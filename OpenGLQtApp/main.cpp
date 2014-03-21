#include "OpenGLQtApp.h"
#include "OpenGLWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(4);

    OpenGLWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}