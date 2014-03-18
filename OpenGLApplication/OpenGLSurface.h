//	OpenGLSurface.h
//	Copyright (C) Dave Kerr
//
//	The OpenGLSurface is a drawing surface for OpenGL.

#pragma once

#include "DIBSurface.h"

class COpenGLSurface : public CDIBSurface  
{
public:
	COpenGLSurface() : m_hRenderContext(NULL) {}
	virtual ~COpenGLSurface() {}

	//	Creation / destruction
	virtual bool	Create(int nWidth, int nHeight, int nBitCount);
	virtual void	Destroy();

	//	Render Contexts
	virtual void	MakeCurrent();
	static void		MakeNoneCurrent() {wglMakeCurrent(NULL, NULL);}

protected:
	HGLRC			m_hRenderContext;
};
