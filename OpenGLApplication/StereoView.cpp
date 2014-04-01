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
	windowOffsetX = 0;
	windowOffsetY = 0;
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void StereoView::SetupView()
{
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
    leftCam.modeltranslation = (float)IOD/2;

    rightCam.topfrustum = top;
    rightCam.bottomfrustum = -top;
    rightCam.leftfrustum = -right - frustumshift;
    rightCam.rightfrustum = right - frustumshift;
    rightCam.modeltranslation = -(float)IOD/2;

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
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{		
		glFrustum(leftCam.leftfrustum, leftCam.rightfrustum,     //set left view frustum
            leftCam.bottomfrustum, leftCam.topfrustum,
            nearZ, farZ);
		//translate to cancel parallax
		glTranslatef(leftCam.modeltranslation - CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);
		//glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);			
			RenderScene();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void StereoView::RenderRightView()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{		
		glFrustum(rightCam.leftfrustum, rightCam.rightfrustum,     //set left view frustum
            rightCam.bottomfrustum, rightCam.topfrustum,
            nearZ, farZ);
		//translate to cancel parallax
		glTranslatef(rightCam.modeltranslation - CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);
		//glTranslatef(LookAtPosition[0], LookAtPosition[1], LookAtPosition[2]);                        //translate to screenplane	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLightfv(GL_LIGHT0, GL_POSITION,  LightPosition);
			RenderScene();
		}
		glPopMatrix();
	}
	glPopMatrix();
}


void StereoView::RenderStereoView()						
{
	ResetLeftView();
	RenderLeftView();
	
	ResetRightView();
	RenderRightView();
}

void StereoView::ResetLeftView()
{
	glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
	glViewport (windowOffsetX, windowOffsetY, windowWidth/2, windowHeight);	 //sets drawing viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                        //reset projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix
}

void StereoView::ResetRightView()
{
	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	glViewport (windowOffsetX + windowWidth/2, windowOffsetY, windowWidth/2, windowHeight);	 //sets drawing viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                        //reset projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                        //reset modelview matrix                                //reset modelview matrix
}

void StereoView::DoOpenGLDraw()
{
	RenderStereoView();
}

void  StereoView::RenderScene()
{
	//Put render implementation on assetRenderer derived class
	if (assetRenderer != NULL)
	{
		assetRenderer->Render();
	}	
}

void StereoView::DoOpenGLResize(int nWidth, int nHeight)
{
	windowWidth = nWidth;
	windowHeight = nHeight;
	RenderStereoView();
}

void StereoView::SetRenderer(BaseAssetRenderer &newInstance)
{
	assetRenderer = &newInstance;
}