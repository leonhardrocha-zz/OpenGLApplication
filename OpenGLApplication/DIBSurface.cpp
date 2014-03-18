#include "stdafx.h"
#include "DIBSurface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDIBSurface::CDIBSurface()
{
	m_pDC = NULL;
	m_pBits = NULL;
	m_hBmp = NULL;
	m_hBmpOld = NULL;
	m_byBitCount = 0;
}

CDIBSurface::~CDIBSurface()
{
	if(m_pDC)
		delete m_pDC;
}

bool CDIBSurface::Create(int nWidth, int nHeight, int nBitCount, void* pData)
{
	//	We must have a size of at least 1 by 1
	if(!nWidth || !nHeight)
		return false;

	ASSERT((nBitCount == 8) || (nBitCount == 16) || (nBitCount == 24));
	m_byBitCount = (BYTE)nBitCount;

	//	If we have objects, destroy them
	if(m_hBmp != NULL)
		Destroy(false, true);

	//	Set the size
	m_szDIB.cx = nWidth;
	m_szDIB.cy = nHeight;
	
	//	Create a BITMAPINFOHEADER structure to describe the DIB.
	BITMAPINFOHEADER BIH ;
	int iSize = sizeof(BITMAPINFOHEADER) ;
	memset(&BIH, 0, iSize);
	
	//	Now fill in the header info. 
	BIH.biSize = iSize;
	BIH.biWidth = nWidth;
	BIH.biHeight = nHeight;
	BIH.biPlanes = 1;
	BIH.biBitCount = nBitCount;
	BIH.biCompression = BI_RGB;

	//	Create a new device context (if needed)
	if(m_pDC == NULL)
	{
		m_pDC = new CDC;
		if(m_pDC->CreateCompatibleDC(NULL) == FALSE)
		{
			TRACE("(CDIBSurface) failed to create a DC.\n");
			return false;
		}
	}
	// Create the DIB section.
	m_hBmp = CreateDIBSection(	m_pDC->GetSafeHdc(),
								(BITMAPINFO*) &BIH,
								DIB_RGB_COLORS,
								&m_pBits,
								NULL,
								0);

    ASSERT(m_hBmp);
    ASSERT(m_pBits);

	//	Set the bits, just copy the old ones.
	if(pData != NULL)
	{
		int nSize = nWidth*nHeight*3;
		BYTE* ptrSource = (BYTE*)pData;
		BYTE* ptrDest = (BYTE*)m_pBits;
		while(nSize--)
			*ptrDest++ = *ptrSource++;
	}

    // Select the new bitmap into the buffer DC.
    if(m_hBmp)
        m_hBmpOld = (HBITMAP)::SelectObject(m_pDC->GetSafeHdc(), m_hBmp);

	return true;
}

void CDIBSurface::Destroy(bool bHDC, bool bHBMP)
{
	//	Totally destroy our device context.
	if(m_pDC && bHDC)
	{	m_pDC->DeleteDC();
		delete m_pDC;
		m_pDC = NULL;
	}

	//	Delete our bitmap.
	if(bHBMP)
		DeleteObject(m_hBmp);
}

void CDIBSurface::Draw(CDC* pTargetDC, int x, int y)
{
	//	Blit it.
	if(m_pDC->GetMapMode() == MM_TEXT)
		pTargetDC->BitBlt(x, y, m_szDIB.cx, m_szDIB.cy, m_pDC, 0, 0, SRCCOPY);
	else
	{
		CRect rc(0, 0, abs(m_szDIB.cx), abs(m_szDIB.cy));
		m_pDC->DPtoLP(rc);
		pTargetDC->BitBlt(x, y, 100, 100, m_pDC, 0, 0, SRCCOPY);
	}
}

void CDIBSurface::Draw(HDC hDC, int x, int y)
{
	::BitBlt(hDC, x, y, m_szDIB.cx, m_szDIB.cy, m_pDC->GetSafeHdc(), 0, 0, SRCCOPY);
}

void CDIBSurface::DrawMapped(CDC* pDC, int x, int y, int cx, int cy)
{
	CRect rc(x, y, cx, cy);
	m_pDC->DPtoLP(rc);
	pDC->BitBlt(x, y, rc.Width(), rc.Height(), m_pDC, 0, 0, SRCCOPY);

}
void CDIBSurface::Erase(COLORREF clColour)
{
	ASSERT(IsValid());

	//	Roio
	
	if(m_pDC->GetMapMode() == MM_TEXT)
		m_pDC->FillSolidRect(0, 0, m_szDIB.cx, m_szDIB.cy, clColour);
	else
	{
		CRect rc(0, 0, abs(m_szDIB.cx), abs(m_szDIB.cy));
		m_pDC->DPtoLP(rc);
		m_pDC->FillSolidRect(rc, clColour);
	}
}

void CDIBSurface::SetPixel(int x, int y, COLORREF cl)
{
	ASSERT(IsValid());

	m_pDC->SetPixel(x, y, cl);
}

void CDIBSurface::SetPalette(CPalette* pPal)
{
	ASSERT(pPal);

    //	Get the colors from the palette.
    int iColors = 0;
    pPal->GetObject(sizeof(iColors), &iColors);
    ASSERT(iColors > 0);
    PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
    pPal->GetPaletteEntries(0, iColors, pPE);

    // Build a table of RGBQUADS.
    RGBQUAD* pRGB = new RGBQUAD[iColors];
    ASSERT(pRGB);
    for (int i = 0; i < iColors; i++) {
        pRGB[i].rgbRed = pPE[i].peRed;
        pRGB[i].rgbGreen = pPE[i].peGreen;
        pRGB[i].rgbBlue = pPE[i].peBlue;
        pRGB[i].rgbReserved = 0;
    }
    
    ::SetDIBColorTable(m_pDC->GetSafeHdc(),
                       0, iColors,
                       pRGB);

    delete [] pRGB;
    delete [] pPE;

}

bool CDIBSurface::SetPixelFormat(int nBitCount)
{
	//	The default pixel format: single buffer, openGL-supporting, 
	//	hardware-accelerated, RGBA-mode format. 
	PIXELFORMATDESCRIPTOR pfd ;
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR) ;
	pfd.nVersion = 1 ;
	pfd.dwFlags = PFD_DRAW_TO_BITMAP | // replaces PFD_DRAW_TO_WINDOW
				  PFD_SUPPORT_OPENGL |
				  PFD_SUPPORT_GDI;
	pfd.iPixelType = PFD_TYPE_RGBA; 
	pfd.cColorBits = nBitCount;
	pfd.cDepthBits = 32 ;
	pfd.iLayerType = PFD_MAIN_PLANE; 


	int nPixelFormat = 0;

	if(0 == (nPixelFormat = ::ChoosePixelFormat(m_pDC->m_hDC, &pfd)))
	{
		TRACE("(CDIBSurface) ChoosePixelFormat failed.\n");
		return false;
	}

	if(!::SetPixelFormat(m_pDC->m_hDC, nPixelFormat, &pfd))
	{
		TRACE("(CDIBSurface) SetPixelFormat failed, &d.\n", GetLastError());
		return false;
	}

	return true;
}

bool CDIBSurface::IsValid()
{
	if(!m_hBmp || !m_pDC) return false;
	return true;
}

void CDIBSurface::CreateImage(CImage& image)
{
	//	Simply attach the handle to the bitmap.
	image.Attach(m_hBmp);
}