#pragma once

class ITracker
{
public:
	virtual void PaintEvent(void *message)=0;
};
