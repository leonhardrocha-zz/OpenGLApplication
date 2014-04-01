// ToeInStereoView.cpp : implementation of the ToeInStereoView class
//
#include "ToeInStereoView.h"

ToeInStereoView::ToeInStereoView()
{
}

void ToeInStereoView::SetupWindow()
{
	windowWidth = 1024;
	windowHeight = 768;
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ToeInStereoView::SetupView()
{
	SetupWindow();

	fovy = 45;                                          //field of view in y-axis
	aspect = double(windowWidth)/double(windowHeight);		//screen aspect ratio
	nearZ = 0.1;                                        //near clipping plane
	farZ = 10.0;                                        //far clipping plane
	IOD = 0.1;
	
	CameraPosition[0] = 0;
	CameraPosition[1] = 0;
	CameraPosition[2] = 1;
	LookAtPosition[0] = 0;
	LookAtPosition[1] = 0;
	LookAtPosition[2] = -1;
	LightPosition[0] = 0;
	LightPosition[1] = 0;
	LightPosition[2] = 0;

	glDrawBuffer(GL_BACK);                                   //draw into both back buffers
	glViewport (0, 0, windowWidth, windowHeight);				 //sets drawing viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, nearZ, farZ);               //sets frustum using gluPerspective
}

void ToeInStereoView::SetupScene()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	float lightDif[3] = {0.8f, 0.8f, 0.8f};
	float lightAmb[3] = {0.1f, 0.1f, 0.1f};
	float lightSpec[3] = {0.1f, 0.1f, 0.1f};
	glEnable(GL_LIGHT0);		
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDif);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
	glLightfv(GL_LIGHT0, GL_SPECULAR,  lightSpec);
	glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void ToeInStereoView::RenderLeftView()
{
	gluLookAt(CameraPosition[0]-IOD/2,                                      //set camera position  x=-IOD/2	
			CameraPosition[1],                                           //                     y=0.0
			CameraPosition[2],                                           //                     z=0.0
			LookAtPosition[0],                                           //set camera "look at" x=0.0
			LookAtPosition[1],                                           //                     y=0.0
			LookAtPosition[2],                                       //                     z=screenplane
			0.0,                                           //set camera up vector x=0.0
			1.0,                                           //                     y=1.0
			0.0);                                          //                     z=0.0
  
	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
		glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);
		RenderScene();
	}
	glPopMatrix();
}

void ToeInStereoView::RenderRightView()
{
	gluLookAt(CameraPosition[0]+IOD/2,									   //set camera position  x=+IOD/2
			CameraPosition[1],                                           //                     y=0.0
			CameraPosition[2],                                           //                     z=0.0
			LookAtPosition[0],                                           //set camera "look at" x=0.0
			LookAtPosition[1],                                           //                     y=0.0
			LookAtPosition[2],                                       //                     z=screenplane
			0.0,                                           //set camera up vector x=0.0
			1.0,                                           //                     y=1.0
			0.0);                                          //                     z=0.0

	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
		glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);                        //translate to screenplane	
		RenderScene();
	}
	glPopMatrix();
}


void ToeInStereoView::RenderStereoView()							//toed-in stereo
{
	glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
	glViewport (0, 0, windowWidth/2, windowHeight);	 //sets drawing viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix
	
	RenderLeftView();
	
	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	glViewport (windowWidth/2-1, 0, windowWidth/2, windowHeight);	 //sets drawing viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix
	
	RenderRightView();
}


void ToeInStereoView::DoOpenGLDraw()
{
	RenderStereoView();
}

void  ToeInStereoView::RenderScene()
{
	//Put render implementation on derived class

	//	//	Create the grid.

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

void ToeInStereoView::DoOpenGLResize(int nWidth, int nHeight)
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
