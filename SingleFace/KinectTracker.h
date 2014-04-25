#include "ITracker.h"
#include "SingleFace.h";

class KinectTracker :  public ITracker
{	
public:
	
	KinectTracker::KinectTracker () 
	{
		tracker.InitInstance();
	}

	virtual void PaintEvent(void *message) 
	{	
		MSG* msg = reinterpret_cast<MSG*>(message);
		if (msg != NULL)
		{
			tracker.WndProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
		}
	}

private:
	SingleFace tracker;
};
