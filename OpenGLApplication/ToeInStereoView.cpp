// BaseStereoView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "OpenGLApplication.h"
#include "ToeInStereoView.h"
#include "GL\glu.h"
#include "GL\glut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBaseStereoView
BEGIN_MESSAGE_MAP(CToeInStereoView, CModelView)
END_MESSAGE_MAP()

CToeInStereoView::CToeInStereoView()
{
	SetupView();

	InitScene();
}

BOOL CToeInStereoView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


void CToeInStereoView::SetupView()
{
	depthZ = 10.0f;                                     //depth of the object drawing
	fovy = 45;                                          //field of view in y-axis
	viewWidth = 1024;
	viewHeight = 512;
	aspect = double(viewWidth)/double(viewHeight);		//screen aspect ratio
	nearZ = 3.0;                                        //near clipping plane
	farZ = 30.0;                                        //far clipping plane
	screenZ = 10.0;                                     //screen projection plane
	IOD = 0.5;
}

void CToeInStereoView::InitScene()
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

	glViewport (0, 0, viewWidth, viewHeight);				 //sets drawing viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, nearZ, farZ);               //sets frustum using gluPerspective
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	glDrawBuffer(GL_BACK);                                   //draw into both back buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      //clear color and depth buffers
}

void CToeInStereoView::RenderLeftView()
{
	glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
	glViewport (0, 0, viewWidth/2, viewHeight);	 //sets drawing viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix

	gluLookAt(-IOD/2,                                      //set camera position  x=-IOD/2	
			0.0,                                           //                     y=0.0
			0.0,                                           //                     z=0.0
			0.0,                                           //set camera "look at" x=0.0
			0.0,                                           //                     y=0.0
			screenZ,                                       //                     z=screenplane
			0.0,                                           //set camera up vector x=0.0
			1.0,                                           //                     y=1.0
			0.0);                                          //                     z=0.0
  
	glPushMatrix();
	{
		glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
		RenderScene();
	}
	glPopMatrix();
}

void CToeInStereoView::RenderRightView()
{
	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	glViewport (viewWidth/2-1, 0, viewWidth/2, viewHeight);	 //sets drawing viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix

	gluLookAt(IOD/2,									   //set camera position  x=+IOD/2
			0.0,                                           //                     y=0.0
			0.0,                                           //                     z=0.0
			0.0,                                           //set camera "look at" x=0.0
			0.0,                                           //                     y=0.0
			screenZ,                                       //                     z=screenplane
			0.0,                                           //set camera up vector x=0.0
			1.0,                                           //                     y=1.0
			0.0);                                          //                     z=0.0

	glPushMatrix();
	{
		glTranslatef(0.0, 0.0, depthZ);                        //translate to screenplane
		RenderScene();
	}
	glPopMatrix();
}


void CToeInStereoView::DoStereo()							//toed-in stereo
{
	RenderLeftView();
	
	RenderRightView();
 
    glFlush();
}


void CToeInStereoView::DoOpenGLDraw()
{
	DoStereo();
}

void  CToeInStereoView::RenderScene()
{
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
}

void CToeInStereoView::DoOpenGLResize(int nWidth, int nHeight)
{
	//	Create the viewport.
	glViewport(0, 0, nWidth, nHeight);

	//	Load the identity projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Create a perspective viewport transformation.
	gluPerspective(fovy, aspect, nearZ, farZ);

	//	Go back to the modelview matrix.
	glMatrixMode(GL_MODELVIEW);
}

