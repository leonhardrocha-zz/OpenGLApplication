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
	LookAtPosition[2] = 0;
	LightPosition[0] = 0;
	LightPosition[1] = 0;
	LightPosition[2] = 0;

	SetupDualWindow();
	leftStereoView.SetupView();
	rightStereoView.SetupView();
	
	leftStereoView.CameraPosition[2] = 3;
	rightStereoView.CameraPosition[2] = 3;
	
	leftStereoView.LookAtPosition[0] = -cos(30*PI/180.0);
	leftStereoView.LookAtPosition[2] = -sin(30*PI/180.0);
	rightStereoView.LookAtPosition[0] = cos(30*PI/180.0);
	rightStereoView.LookAtPosition[2] = -sin(30*PI/180.0);

}

void ToeInStereoView::RenderLeftView()
{
	leftStereoView.ResetLeftView();
	leftStereoView.RenderLeftView();

	leftStereoView.ResetRightView();
	leftStereoView.RenderRightView();
}

void ToeInStereoView::RenderRightView()
{	
	rightStereoView.ResetLeftView();
	rightStereoView.RenderLeftView();
	
	rightStereoView.ResetRightView();
	rightStereoView.RenderRightView();
}

