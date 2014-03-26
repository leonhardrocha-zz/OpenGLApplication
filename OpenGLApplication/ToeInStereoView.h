#ifndef _TOEIN_STEREO_VIEW_H_
#define _TOEIN_STEREO_VIEW_H_

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

// CToeInStereoView window

class CToeInStereoView : public CBaseStereoView
{

public:
	//	Constructor / Destructor.
	CToeInStereoView();
	virtual ~CToeInStereoView() {};
// Overrides
protected:
	//	Main OpenGL functions.
	virtual void SetupView();
	virtual void SetupWindow();
	virtual void SetupScene();
	virtual void RenderScene();
	virtual void RenderStereoView();
	virtual void RenderLeftView();
	virtual void RenderRightView();
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);
protected:
	float CameraPosition[3];
	float LookAtPosition[3];
	float LightPosition[3];
};

#endif
