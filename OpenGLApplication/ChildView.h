// ChildView.h : interface of the CChildView class
//


#pragma once

#include "OpenGLView.h"

// CChildView window

class CChildView : public COpenGLView
{

public:

	//	Constructor / Destructor.
	CChildView();
	virtual ~CChildView();

// Attributes
public:

// Operations
public:
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//	Main OpenGL functions.
	virtual void SetupScene();
	virtual void RenderScene();
	virtual void FinishScene();
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

