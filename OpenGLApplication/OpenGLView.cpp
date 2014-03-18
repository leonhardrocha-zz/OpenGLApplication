//  OGLView.cpp
//  Created by Dave Kerr, 20/04/2002 22:44:15

#include "stdafx.h"
#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void COpenGLView::OnDraw(CDC* pDC)
{
	//	Do any opengl drawing.
	DoOpenGLDraw();

	//	Now blit the lot into the DC.
	m_openGLSurface.Draw(pDC, 0, 0);
}

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	//	The DIB Surface handles erasing the background.
	return TRUE;
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	//	If size is silly (x=0 || y=0) don't create.
	if(cx == 0 || cy == 0)
		return;
	
	//	Recreate our DIB surface using the correct size.
	m_openGLSurface.Create(cx, cy, 24);

	//	Call the override - this'll handle the viewport projection.
	DoOpenGLResize(cx, cy);

	//	Now we must redraw.
	Invalidate();
}

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();

	//	Destroy the surface.
	m_openGLSurface.Destroy();	
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if(cs.style&CS_PARENTDC)
		cs.style -= CS_PARENTDC;	
	
	return CView::PreCreateWindow(cs);
}