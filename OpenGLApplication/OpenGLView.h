//  OpenGLView.h
//	Copyright (C) Dave Kerr
//
//	Derive your View from OpenGL and you get full access to OpenGL.

#include "OpenGLSurface.h"

class COpenGLView : public CView
{      
	DECLARE_DYNCREATE(COpenGLView)

protected:

	//	Constructor / Descructor.
	COpenGLView() {}
	virtual ~COpenGLView() {}     

protected:
	virtual void OnDraw(CDC* pDC);      
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy() {}		//	Without this we get a run time error in non doc/view apps.

	//	Debug functions.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	//	This is the main function you must override - do all OpenGL
	//	drawing in it.
	virtual void DoOpenGLDraw() {}

	//	Do all OpenGL resizing and projections etc in this function.
	virtual void DoOpenGLResize(int nWidth, int nHeight) {}

protected:

	//	This is the main part of the view - the OpenGL surface we actually draw to.
	COpenGLSurface m_openGLSurface;

	//	Generated message map functions.
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	
	DECLARE_MESSAGE_MAP()
};