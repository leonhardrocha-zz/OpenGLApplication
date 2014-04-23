#include <QWidget>
#include <QEvent>
#include <QPaintEngine>
#include <SingleFace.h>
#include "MyDock.h"


class  TrackerDock :  public MyDock
{
public:
	MyTracker tracker;

	TrackerDock::TrackerDock(const QString &colorName, QWidget *parent, Qt::WindowFlags flags) : MyDock(colorName, parent, flags)
	{
		RenderFlags(QWidget::DrawChildren | QWidget::IgnoreMask);
		setAttribute(Qt::WA_NativeWindow);
		tracker.InitInstance();
	}

	virtual bool nativeEvent(const QByteArray& eventType, void * message, long *result)
	{	
		tracker.PaintEvent(message);
		return true;
	}

};