// ToeInStereoView.cpp : implementation of the ToeInStereoView class
//
#include "ToeInStereoView.h"
#include <cmath>
#define PI 3.14159265
ToeInStereoView::ToeInStereoView()
{
}

void ToeInStereoView::SetupView()
{
	fovy = 45;                                          //field of view in y-axis
	aspect = double(windowWidth)/double(windowHeight);		//screen aspect ratio
	nearZ = 0.1;                                        //near clipping plane
	farZ = 10.0;                                        //far clipping plane
	IOD = 0.1;
	
	CameraPosition[0] = 0;
	CameraPosition[1] = 0;
	CameraPosition[2] = 3;
	LookAtPosition[0] = 0;
	LookAtPosition[1] = 0;
	LookAtPosition[2] = -1;
	LightPosition[0] = 0;
	LightPosition[1] = 0;
	LightPosition[2] = 0;

	SetupDualWindow();
	leftStereoView.SetupView();
	rightStereoView.SetupView();

	CameraRotationAngle = 30.0;
	CameraRotationShift[0] = LookAtPosition[0] * sin(CameraRotationAngle*PI/180);
	CameraRotationShift[1] = LookAtPosition[1] * sin(CameraRotationAngle*PI/180);
	CameraRotationShift[2] = LookAtPosition[2] * sin(CameraRotationAngle*PI/180);

}

void ToeInStereoView::RenderLeftView()
{
	leftStereoView.ResetLeftView();
	/*glMatrixMode(GL_PROJECTION);
	gluLookAt(CameraPosition[0], CameraPosition[1], CameraPosition[2], 
			  leftStereoView.LookAtPosition[0],leftStereoView.LookAtPosition[1],leftStereoView.LookAtPosition[2],
			  0,1,0);*/
			
	glRotatef(-CameraRotationAngle, 0.0, 1.0, 0.0);
	//glTranslatef(-CameraRotationShift[0], -CameraRotationShift[1], -CameraRotationShift[2]);

	leftStereoView.RenderLeftView();

	leftStereoView.ResetRightView();
	/*glMatrixMode(GL_PROJECTION);
	gluLookAt(CameraPosition[0], CameraPosition[1], CameraPosition[2], 
			  leftStereoView.LookAtPosition[0],leftStereoView.LookAtPosition[1],leftStereoView.LookAtPosition[2],
			  0,1,0);*/
			
	glRotatef(-CameraRotationAngle, 0.0, 1.0, 0.0);
	//glTranslatef(-CameraRotationShift[0], -CameraRotationShift[1], -CameraRotationShift[2]);

	leftStereoView.RenderRightView();
}

void ToeInStereoView::RenderRightView()
{	
	rightStereoView.ResetLeftView();

	glRotatef(CameraRotationAngle, 0.0, 1.0, 0.0);
	//glTranslatef(CameraRotationShift[0], CameraRotationShift[1], CameraRotationShift[2]);

	rightStereoView.RenderLeftView();
	
	rightStereoView.ResetRightView();

	glRotatef(CameraRotationAngle, 0.0, 1.0, 0.0);
	//glTranslatef(CameraRotationShift[0], CameraRotationShift[1], CameraRotationShift[2]);

	rightStereoView.RenderRightView();
}

