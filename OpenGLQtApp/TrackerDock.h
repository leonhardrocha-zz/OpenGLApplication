#include <QWidget>
#include <QEvent>
#include <QPaintEngine>
#include <QThread>
#include "SingleFace.h"
#include "MyDock.h"

typedef std::pair<MyTracker&,void*> TrackerEvent;

class  TrackerDock :  public MyDock
{
public:

	TrackerDock::TrackerDock(const QString &colorName, QWidget *parent, Qt::WindowFlags flags) : MyDock(colorName, parent, flags)
	{
		RenderFlags(QWidget::DrawChildren | QWidget::IgnoreMask);
		setAttribute(Qt::WA_NativeWindow);
		//setAttribute(Qt::WA_PaintOnScreen);
	
		tracker.InitInstance();
	}
	virtual bool nativeEvent(const QByteArray& eventType, void * message, long *result)
	{	
		tracker.PaintEvent(message);
		return true;
	}

	MyTracker tracker;
};