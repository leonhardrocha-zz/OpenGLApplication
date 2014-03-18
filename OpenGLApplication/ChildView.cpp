// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "OpenGLApplication.h"
#include "ChildView.h"
#include "GL\glut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	SetupScene();
}

CChildView::~CChildView()
{
	FinishScene();
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLView)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::SetupScene()
{
	//	Clear the buffers.
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//	Set up some nice attributes for drawing the grid.
	glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5f);
	glPopAttrib();
}

void CChildView::RenderScene()
{
	//	Look at the middle of the scene.
	glLoadIdentity();
	gluLookAt(-10, 10, 10, 0, 0, 0, 0, 1, 0);

	//	Create the grid.

    glBegin(GL_LINES);
	
	for (int i = -10; i <= 10; i++)
    {
		glColor4f(0.2f, 0.2f, 0.2f, 0.8f);
        glVertex3f((float)i, 0, -10);
        glVertex3f((float)i, 0, 10);
        glVertex3f(-10, 0, (float)i);
        glVertex3f(10, 0, (float)i);
	}
	
	glEnd();

	//	Create the axies.
	glBegin(GL_LINES);

		glColor4f(1, 0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(3, 0, 0);
		glColor4f(0, 1, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 3, 0);
		glColor4f(0, 0, 1, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 3);

	glEnd();
	glFlush();
}

void CChildView::DoOpenGLDraw()
{
	RenderScene();	
}

void CChildView::FinishScene()
{


}


void CChildView::DoOpenGLResize(int nWidth, int nHeight)
{
	//	Create the viewport.
	glViewport(0, 0, nWidth, nHeight);

	//	Load the identity projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Create a perspective viewport transformation.
	gluPerspective(45.0f, (float)nWidth / (float)nHeight, 0.1f, 100.0f);

	//	Go back to the modelview matrix.
	glMatrixMode(GL_MODELVIEW);
}

