#ifndef _TOEIN_STEREO_VIEW_H_
#define _TOEIN_STEREO_VIEW_H_

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
#include "BaseStereoView.h"

// CToeInStereoView window

class CToeInStereoView : public CBaseStereoView
{

public:
	//	Constructor / Destructor.
	CToeInStereoView();
	virtual ~CToeInStereoView() {};


// Overrides
protected:
	virtual void SetupView();
	//	Main OpenGL functions.
	virtual void SetupScene();
	virtual void RenderScene();
	virtual void RenderStereoView();
	virtual void RenderLeftView();
	virtual void RenderRightView();
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);
protected:
};

#endif
