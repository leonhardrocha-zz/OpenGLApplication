// ToeInStereoView.cpp : implementation of the StereoView class
//
#include "StereoView.h"

#define DTR 0.0174532925

struct camera
{
    GLdouble leftfrustum;
    GLdouble rightfrustum;
    GLdouble bottomfrustum;
    GLdouble topfrustum;
    GLfloat modeltranslation;
} leftCam, rightCam;


StereoView::StereoView()
{
}


void StereoView::SetupWindow()
{
	windowWidth = 1024;
	windowHeight = 768;
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void StereoView::SetupView()
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

	double top = nearZ*tan(DTR*fovy/2);                    //sets top of frustum based on fovy and near clipping plane
    double right = aspect*top;                             //sets right of frustum based on aspect ratio
    double frustumshift = (IOD/2)*nearZ/LookAtPosition[2];

    leftCam.topfrustum = top;
    leftCam.bottomfrustum = -top;
    leftCam.leftfrustum = -right + frustumshift;
    leftCam.rightfrustum = right + frustumshift;
    leftCam.modeltranslation = IOD/2;

    rightCam.topfrustum = top;
    rightCam.bottomfrustum = -top;
    rightCam.leftfrustum = -right - frustumshift;
    rightCam.rightfrustum = right - frustumshift;
    rightCam.modeltranslation = -IOD/2;

	glDrawBuffer(GL_BACK);                                   //draw into both back buffers
	glViewport (0, 0, windowWidth, windowHeight);				 //sets drawing viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(fovy, aspect, nearZ, farZ);               //sets frustum using gluPerspective
}

void StereoView::SetupScene()
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

void StereoView::RenderLeftView()
{
	glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
	glViewport (0, 0, windowWidth/2, windowHeight);	 //sets drawing viewport

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                        //reset projection matrix
	glFrustum(leftCam.leftfrustum, leftCam.rightfrustum,     //set left view frustum
            leftCam.bottomfrustum, leftCam.topfrustum,
            nearZ, farZ);
	//translate to cancel parallax
	glTranslatef(leftCam.modeltranslation - CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix
	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
		glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);
		RenderScene();
	}
	glPopMatrix();
}

void StereoView::RenderRightView()
{
	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	glViewport (windowWidth/2-1, 0, windowWidth/2, windowHeight);	 //sets drawing viewport

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                        //reset projection matrix
	glFrustum(rightCam.leftfrustum, rightCam.rightfrustum,     //set left view frustum
            rightCam.bottomfrustum, rightCam.topfrustum,
            nearZ, farZ);
	//translate to cancel parallax
	glTranslatef(rightCam.modeltranslation - CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix
	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
		glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);                        //translate to screenplane	
		RenderScene();
	}
	glPopMatrix();
}


void StereoView::RenderStereoView()							//toed-in stereo
{
	RenderLeftView();
	
	RenderRightView();
}


void StereoView::DoOpenGLDraw()
{
	RenderStereoView();
}

void  StereoView::RenderScene()
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

void StereoView::DoOpenGLResize(int nWidth, int nHeight)
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
