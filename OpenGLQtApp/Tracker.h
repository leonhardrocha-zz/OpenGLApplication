#include "SingleFace.h"
#include "qwinhost.h"

class  Tracker : public QWinHost, public SingleFace
{
public:
	Tracker::Tracker(QWidget *parent = NULL, Qt::WindowFlags f = 0)
        : SingleFace()
	{
		setFocusPolicy(Qt::StrongFocus);
	};
};