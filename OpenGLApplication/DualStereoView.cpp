// DualStereoView.cpp : implementation of the DualStereoView class
//
#include "DualStereoView.h"
#include "MatrixMath.h"


DualStereoView::DualStereoView()
{
}

void DualStereoView::SetupDualWindow()
{
	leftStereoView.windowOffsetX = 0;
	leftStereoView.windowOffsetY = 0;
	leftStereoView.windowWidth = windowWidth/2;
	leftStereoView.windowHeight = windowHeight;
	
	rightStereoView.windowOffsetX = windowWidth/2;
	rightStereoView.windowOffsetY = 0;
	rightStereoView.windowWidth = windowWidth/2;
	rightStereoView.windowHeight = windowHeight;
}

void DualStereoView::SetupView()
{	
	SetupDualWindow();
	leftStereoView.SetupView();
	rightStereoView.SetupView();
}

void DualStereoView::SetupScene()
{
	rightStereoView.SetupScene();
	leftStereoView.SetupScene();
}

void DualStereoView::RenderLeftView()
{
	leftStereoView.RenderStereoView();	
}

void DualStereoView::RenderRightView()
{
	rightStereoView.RenderStereoView();
}

void DualStereoView::RenderStereoView()
{
	glDrawBuffer(GL_BACK_LEFT);                              //draw into back left buffer
	glPushMatrix();
	{
		ResetLeftView();
		RenderLeftView();
	}
	glPopMatrix();
	
	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	glPushMatrix();
	{
		ResetRightView();
		RenderRightView();
	}
}


void DualStereoView::DoOpenGLResize(int nWidth, int nHeight)
{
	rightStereoView.DoOpenGLResize(nWidth/2, nHeight);
	leftStereoView.DoOpenGLResize(nWidth/2, nHeight);
}

void DualStereoView::SetRenderer(BaseAssetRenderer &newInstance)
{
	rightStereoView.SetRenderer(newInstance);
	leftStereoView.SetRenderer(newInstance);
}