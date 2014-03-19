// ChildView.h : interface of the CChildView class
//


#pragma once

//#include "ChildView.h"

// CChildView window
class CBaseStereoView
{

public:

// Attributes
public:

// Operations
public:
// Overrides
// Overrides
protected:
	virtual void SetupView() = 0;
	//	Main OpenGL functions.
	virtual void DoStereo() = 0;
	virtual void InitScene() = 0;
	virtual void RenderScene() = 0;
	// Generated message map functions
protected:
	int viewWidth;
	int viewHeight;
	float depthZ;                                      //depth of the object drawing
	double fovy;                                          //field of view in y-axis
	double aspect;  //screen aspect ratio
	double nearZ;                                        //near clipping plane
	double farZ;                                        //far clipping plane
	double screenZ;                                     //screen projection plane
	double IOD;


};

