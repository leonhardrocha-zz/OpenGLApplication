#include "OpenGLQtApp.h"
#include "AssetWindow.h"
#include "SingleFace.h"


#include <QtQuick/qquickview.h>
#include <QtWidgets/QApplication>
//
//// Program's main entry point
//DWORD WINAPI StartThread(PVOID lpParam)
//{
//	QWidget* parent = static_cast<QWidget*>(lpParam);
//    SingleFace app(parent, 0);
//	return app.Run();
//}


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

	
    QSurfaceFormat format;
    format.setSamples(4);
	AssetWindow window;
	window.setFormat(format);
    window.resize(640, 480);
	window.show();

	QQuickView *view = new QQuickView(&window);
	QWidget *oglContainer = QWidget::createWindowContainer(view);
	oglContainer->setMinimumSize(640,480);
	oglContainer->setMaximumSize(1280,960);
	oglContainer->setFocusPolicy(Qt::TabFocus);	 
	
	QMainWindow mainWindow;
	mainWindow.menuBar()->addMenu("&File")->addAction("&Exit", &app, SLOT(quit()));
	QWidget viewWidget(&mainWindow);
	QVBoxLayout hbox(&viewWidget);
	hbox.addWidget(oglContainer);
	
	QWidget *trackerWidget = new QWidget();
    mainWindow.setDockNestingEnabled(true);
	mainWindow.setMenuWidget(trackerWidget);

    window.setAnimating(true);
	/*auto hFaceTrackingThread = CreateThread(NULL, 0, StartThread, (PVOID)trackerWidget, 0, 0);	
*/
	SingleFace tracker(trackerWidget, 0);
	
	auto requiredSize = mbstowcs( NULL, argv[0], 0) + 1;
	wchar_t* lpCmdLine = new wchar_t[requiredSize];
	mbstowcs(lpCmdLine, argv[0], requiredSize);
	tracker.InitInstanceInHostWindow((PWSTR) lpCmdLine, argc);
	
	auto status = app.exec();

	delete oglContainer;
	delete view;
	delete trackerWidget;
    return status;
}