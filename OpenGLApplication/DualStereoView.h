#ifndef _DUAL_STEREO_VIEW_H_
#define _DUAL_STEREO_VIEW_H_

#include "BaseAssetRenderer.h"
#include "StereoView.h"
#include "BaseStereoView.h"
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

// ToeInStereoView window

class DualStereoView : public StereoView
{
public:
	//	Constructor / Destructor.
	DualStereoView();
	virtual ~DualStereoView() {};

	virtual void SetupView();
	virtual void SetupDualWindow();
	virtual void SetupScene();

	float VirtualPlanePosition[3];
// Overrides
protected:
	//	Main OpenGL functions.
	virtual void RenderStereoView();
	virtual void RenderLeftView();
	virtual void RenderRightView();
	virtual void DoOpenGLResize(int nWidth, int nHeight);
	StereoView rightStereoView;
	StereoView leftStereoView;
	void SetRenderer(BaseAssetRenderer &newInstance);
};

#endif
