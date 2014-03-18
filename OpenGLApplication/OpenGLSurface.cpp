// OGLSurface.cpp
// Created by Dave Kerr, 20/04/2002 21:46:24

#include "stdafx.h"
#include "OpenGLSurface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool COpenGLSurface::Create(int nWidth, int nHeight, int nBitCount)
{
	if(!CDIBSurface::Create(nWidth, nHeight, nBitCount))
	{
		TRACE("(COpenGLSurface) Couldn't create: the DIBSurface failed to create.\n");
		return false;
	}

	SetPixelFormat(nBitCount);

	//	Now create our render context.
	if(m_hRenderContext == NULL)
		m_hRenderContext = wglCreateContext(m_pDC->GetSafeHdc());

	//	Finally, we make our render context current.
	MakeCurrent();

	return true;
}

void COpenGLSurface::Destroy()
{
	//	It's the same as the DIB surface destroy, but we have to destroy a render
	//	context.
	CDIBSurface::Destroy();
	wglDeleteContext(m_hRenderContext);
	wglMakeCurrent(NULL, NULL);
}

void COpenGLSurface::MakeCurrent()
{
	//	Make this surface current.
	if(wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRenderContext) != TRUE)
	{
		ASSERT(0);
	}
}
