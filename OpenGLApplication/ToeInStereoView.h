// ChildView.h : interface of the CChildView class
//


#pragma once

#include "OpenGLView.h"
#include "BaseStereoView.h"

// CChildView window

class CToeInStereoView : public COpenGLView, CBaseStereoView
{

public:
	//	Constructor / Destructor.
	CToeInStereoView();
	virtual ~CToeInStereoView() {};


// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//	Main OpenGL functions.
	virtual void SetupScene();
	virtual void RenderScene();
	virtual void DoStereo();                                 //intraocular distance
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

