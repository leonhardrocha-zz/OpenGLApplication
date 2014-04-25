#ifndef _TRACKER_DOCK_H
#define _TRACKER_DOCK_H

#include <QWidget>
#include <QEvent>
#include <QPaintEngine>
#include <QThread>
#include "MyDock.h"
#include "ITracker.h"

typedef std::pair<ITracker&,void*> TrackerEvent;

class  TrackerDock :  public MyDock
{
public:

	TrackerDock::TrackerDock(ITracker& tracker, const QString &dockName, QWidget *parent, Qt::WindowFlags flags) : MyDock(dockName, parent, flags), m_Tracker(tracker)
	{
		RenderFlags(QWidget::DrawChildren | QWidget::IgnoreMask);
		setAttribute(Qt::WA_NativeWindow);


		//setAttribute(Qt::WA_PaintOnScreen);	
	}
	virtual bool nativeEvent(const QByteArray& eventType, void * message, long *result)
	{	
		m_Tracker.PaintEvent(message);
		return true;
	}

	ITracker& m_Tracker;
};

#endif