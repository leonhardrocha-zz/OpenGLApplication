// ChildView.h : interface of the CChildView class
//


#pragma once

#include "ModelView.h"
#include "BaseStereoView.h"

// CChildView window

class CToeInStereoView : public CModelView, CBaseStereoView
{

public:
	//	Constructor / Destructor.
	CToeInStereoView();
	virtual ~CToeInStereoView() {};


// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void SetupView();
	//	Main OpenGL functions.
	virtual void InitScene();
	virtual void RenderScene();
	virtual void RenderLeftView();
	virtual void RenderRightView();
	virtual void DoStereo();                                 //intraocular distance
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

