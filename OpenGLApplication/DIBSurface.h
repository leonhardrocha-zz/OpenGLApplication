//	DIBSurface.h
//	Copyright (C) Dave Kerr
//
//	This is an abstaction of a DIB surface.

#pragma once

#include <atlimage.h>

class CDIBSurface
{
public:
	CDIBSurface();
	virtual ~CDIBSurface();

	//	Creation/Destruction
	virtual bool	Create(int nWidth, int nHeight, int nBitCount = 24, void* pData = NULL);
	virtual void	Destroy(bool bHDC = true, bool bHBMP = true);

	//	Image Functions
	void			CreateImage(CImage& image);

	//	Palette / Pixel format
	void			SetPalette(CPalette* pPal);
	virtual bool	SetPixelFormat(int nBitCount);

	//	Diagnostics
	bool			IsValid();

	//	Device context
	CDC*			GetDC() {return m_pDC;}

	//	Drawing
	virtual void	SetPixel(int x, int y, COLORREF cl);
	virtual void	Draw(CDC* pTargetDC, int x, int y);
	virtual void	Draw(HDC hDC, int x, int y);
	virtual void	DrawMapped(CDC* pTargetDC, int x, int y, int cx, int cy);
	virtual void	Erase(COLORREF clColour);

	//	Accessors
	int				GetWidth() const {return m_szDIB.cx;}
	int				GetHeight() const {return m_szDIB.cy;}
	int				GetBitCount() const {return (int)m_byBitCount;}
	void*			GetData() {return m_pBits;}

protected:
	//	Member data
	CSize			m_szDIB;
	CDC*			m_pDC;
	HBITMAP			m_hBmp;
	HBITMAP			m_hBmpOld;
	void*			m_pBits;
	BYTE			m_byBitCount;	//	8,16,24 supported.
};