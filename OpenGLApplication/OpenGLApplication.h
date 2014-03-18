// OpenGLApplication.h : main header file for the OpenGLApplication application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLApplicationApp:
// See OpenGLApplication.cpp for the implementation of this class
//

class COpenGLApplicationApp : public CWinApp
{
public:
	COpenGLApplicationApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLApplicationApp theApp;