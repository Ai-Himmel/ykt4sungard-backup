// FG_DIB.cpp: implementation of the CFG_DIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FG_DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFG_DIB::CFG_DIB()
{
	m_hBitmap = NULL;
	m_hPalette = NULL;
	m_Dest.x = 0;
	m_Dest.y = 0;
	m_DestSize.cx = 0;
	m_DestSize.cy = 0;
	m_Src.x = 0;
	m_Src.y = 0;
	m_SrcSize.cx = 0;
	m_SrcSize.cy = 0;
	m_lpDIBits = NULL;
	InitDestroy();
}

CFG_DIB::CFG_DIB(int width, int height, int nBitCounts)
{
	m_hBitmap = NULL;
	m_hPalette = NULL;
	m_Dest.x = 0;
	m_Dest.y = 0;
	m_DestSize.cx = 0;
	m_DestSize.cy = 0;
	m_Src.x = 0;
	m_Src.y = 0;
	m_SrcSize.cx = 0;
	m_SrcSize.cy = 0;
	InitDestroy();
	ComputePaletteSize(nBitCounts);					//为BITMAPINFOHEADER结构申请空间。
	if(m_lpBMPHdr)
		delete [] m_lpBMPHdr;
	m_lpBMPHdr = (LPBITMAPINFOHEADER)new 
		char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorEntries];
	m_lpBMPHdr->biSize = sizeof(BITMAPINFOHEADER);	//以下是为BITMAPINFOHEADER结构赋值
	m_lpBMPHdr->biWidth = width;
	m_lpBMPHdr->biHeight = height;
	m_lpBMPHdr->biPlanes = 1;
	m_lpBMPHdr->biBitCount = nBitCounts;
	m_lpBMPHdr->biCompression = BI_RGB;
	m_lpBMPHdr->biSizeImage = 0;
	m_lpBMPHdr->biXPelsPerMeter = 0;
	m_lpBMPHdr->biYPelsPerMeter = 0;
	m_lpBMPHdr->biClrUsed = m_nColorEntries;
	m_lpBMPHdr->biClrImportant = m_nColorEntries;
	ComputeImage();
	memset(m_lpvColorTable, 0, sizeof(RGBQUAD) * m_nColorEntries);
	// m_lpDIBits = NULL;  
}

CFG_DIB::~CFG_DIB()
{
	ReleaseMemBlock();
	InitDestroy();
}

void CFG_DIB::InitDestroy()
{
	m_Dest.x = 0;
	m_Dest.y = 0;
	m_DestSize.cx = 0;
	m_DestSize.cy = 0;
	m_Src.x = 0;
	m_Src.y = 0;
	m_SrcSize.cx = 0;
	m_SrcSize.cy = 0;
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	if(m_hBitmap != NULL) ::DeleteObject(m_hBitmap);
	m_lpBMPHdr = NULL;
	m_lpDIBits = NULL;
	m_lpvColorTable = NULL;
	m_nColorEntries = 0;
	m_dwImageSize = 0;
	m_hBitmap = NULL;
	m_hPalette = NULL;
}

void CFG_DIB::ComputePaletteSize(int nBitCounts)
{
	if((m_lpBMPHdr == NULL) || (m_lpBMPHdr->biClrUsed == 0)) {
		switch(nBitCounts) {
			case 1:
				m_nColorEntries = 2;
				break;
			case 4:
				m_nColorEntries = 16;
				break;
			case 8:
				m_nColorEntries = 256;
				break;
			case 16:
			case 24:
			case 32:
				m_nColorEntries = 0;
				break;
			default:
				ASSERT(FALSE);
		}
	}
	else {
		m_nColorEntries = m_lpBMPHdr->biClrUsed;
	}
	ASSERT((m_nColorEntries >= 0) && (m_nColorEntries <= 256));
}


void CFG_DIB::ComputeImage()
{
	if(m_lpBMPHdr->biSize != sizeof(BITMAPINFOHEADER)) {
		TRACE("Not a valid Windows bitmap -- probably an OS/2 bitmap\n");
		throw new CNotSupportedException;
	}
	m_dwImageSize = m_lpBMPHdr->biSizeImage;
	if(m_dwImageSize == 0) {
		DWORD dwBytes = ((DWORD) m_lpBMPHdr->biWidth * m_lpBMPHdr->biBitCount) / 32;
		if(((DWORD) m_lpBMPHdr->biWidth * m_lpBMPHdr->biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		//没被压缩
		m_dwImageSize = dwBytes * m_lpBMPHdr->biHeight; 
	}
	m_lpvColorTable = (LPBYTE) m_lpBMPHdr + sizeof(BITMAPINFOHEADER);
}

HBITMAP CFG_DIB::CreateBitmap(CDC* pDC)
{
	if (m_dwImageSize == 0) return NULL;
    HBITMAP hBitmap = ::CreateDIBitmap(pDC->GetSafeHdc(),
		m_lpBMPHdr, CBM_INIT, m_lpDIBits, 
		(LPBITMAPINFO) m_lpBMPHdr, DIB_RGB_COLORS);
    ASSERT(hBitmap != NULL);
    return hBitmap;
}
HBITMAP CFG_DIB::CreateSection(CDC* pDC)
{
	if(m_lpBMPHdr == NULL) return NULL;
	if(m_lpDIBits != NULL) return NULL;					//图像不存在
	m_hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(),
		(LPBITMAPINFO)m_lpBMPHdr, DIB_RGB_COLORS,
		(LPVOID*)&m_lpDIBits, NULL, 0);
	ASSERT(m_lpDIBits != NULL);
	return m_hBitmap;
}

BOOL CFG_DIB::SetWinPalette()
{
	if(m_nColorEntries == 0) return FALSE;
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	TRACE("CDib::MakePalette --	m_nColorEntries = %d\n", m_nColorEntries);
	LPLOGPALETTE pLogPal = 
		(LPLOGPALETTE) new char[2 * sizeof(WORD) +
		m_nColorEntries * sizeof(PALETTEENTRY)];
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorEntries;
	LPRGBQUAD pDibRGBquad = (LPRGBQUAD) m_lpvColorTable;
	for(int i = 0; i < m_nColorEntries; i++) {
		pLogPal->palPalEntry[i].peRed = 
				pDibRGBquad->rgbRed;
		pLogPal->palPalEntry[i].peGreen =
				pDibRGBquad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = 
				pDibRGBquad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		pDibRGBquad++;
	}
	m_hPalette = ::CreatePalette(pLogPal);
	delete []pLogPal;
	pLogPal = NULL;
	return TRUE;
}

BOOL CFG_DIB::SetLogPalette(CDC* pDC)
{
	//如果DIB没有颜色表，可以用逻辑调色板
	if(m_nColorEntries != 0) return FALSE;
	m_hPalette = ::CreateHalftonePalette(pDC->GetSafeHdc());
	return TRUE;
}

UINT CFG_DIB::UseLogPalette(CDC* pDC)
{
	if(m_hPalette == NULL) return 0;
	HDC hdc = pDC->GetSafeHdc();
	::SelectPalette(hdc, m_hPalette,FALSE);		//Windows作为前台调色板来实现该调色板
	return ::RealizePalette(hdc);
}

BOOL CFG_DIB::NewFile(int width, int height, int nBitCounts)
{
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	if(m_hBitmap != NULL) ::DeleteObject(m_hBitmap);
	m_hBitmap = NULL;
	m_hPalette = NULL;
	m_Dest.x = 0;
	m_Dest.y = 0;
	m_DestSize.cx = 0;
	m_DestSize.cy = 0;
	m_Src.x = 0;
	m_Src.y = 0;
	m_SrcSize.cx = 0;
	m_SrcSize.cy = 0;
	ReleaseMemBlock();
	InitDestroy();
	ComputePaletteSize(nBitCounts);					//为BITMAPINFOHEADER结构申请空间。
	m_lpBMPHdr = (LPBITMAPINFOHEADER)new 
		char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorEntries];
	m_lpBMPHdr->biSize = sizeof(BITMAPINFOHEADER);	//以下是为BITMAPINFOHEADER结构赋值
	m_lpBMPHdr->biWidth = width;
	m_lpBMPHdr->biHeight = height;
	m_lpBMPHdr->biPlanes = 1;
	m_lpBMPHdr->biBitCount = nBitCounts;
	m_lpBMPHdr->biCompression = BI_RGB;
	m_lpBMPHdr->biSizeImage = 0;
	m_lpBMPHdr->biXPelsPerMeter = 0;
	m_lpBMPHdr->biYPelsPerMeter = 0;
	m_lpBMPHdr->biClrUsed = m_nColorEntries;
	m_lpBMPHdr->biClrImportant = m_nColorEntries;
	ComputeImage();
	memset(m_lpvColorTable, 0, sizeof(RGBQUAD) * m_nColorEntries);
	m_lpDIBits = (LPBYTE) new char[m_dwImageSize];

	memset(m_lpDIBits, 0, m_dwImageSize);

	return TRUE;
}

BOOL CFG_DIB::CloseFile()
{
	m_Dest.x = 0;
	m_Dest.y = 0;
	m_DestSize.cx = 0;
	m_DestSize.cy = 0;
	m_Src.x = 0;
	m_Src.y = 0;
	m_SrcSize.cx = 0;
	m_SrcSize.cy = 0;
	ReleaseMemBlock();
	InitDestroy();
	return TRUE;
}

BOOL CFG_DIB::WriteFile(CFile* pFile)
{
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	int sizeHdr = sizeof(BITMAPINFOHEADER) + 
				sizeof(RGBQUAD) * m_nColorEntries;
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = 
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorEntries;	
	try {
		pFile->Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		pFile->Write((LPVOID) m_lpBMPHdr,  sizeHdr);
		pFile->Write((LPVOID) m_lpDIBits, m_dwImageSize);
	}
	catch(CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}
	return TRUE;
}

BOOL CFG_DIB::ReadFile(CFile* pFile)
{
	ReleaseMemBlock();
	InitDestroy();
	int counts, size;
	BITMAPFILEHEADER bmfh;
	try {
		counts = pFile->Read((LPVOID) &bmfh, 
					sizeof(BITMAPFILEHEADER));
		if(counts != sizeof(BITMAPFILEHEADER)) {
			throw new CFileException;
		}
		if(bmfh.bfType != 0x4d42) {
			throw new CNotSupportedException;
		}
		size = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_lpBMPHdr = (LPBITMAPINFOHEADER) new char[size];
		// BITMAPINFOHEADER和颜色表
		counts = pFile->Read(m_lpBMPHdr, size); 
		ComputeImage();
		ComputePaletteSize(m_lpBMPHdr->biBitCount);
		SetWinPalette();
		m_lpDIBits = (LPBYTE) new char[m_dwImageSize];
		counts = pFile->Read(m_lpDIBits, m_dwImageSize); 
	}
	catch(CException* pe) {
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CFG_DIB::ReadSection(CFile* pFile, CDC* pDC)
{
	ReleaseMemBlock();
	InitDestroy();
	int counts, size;
	BITMAPFILEHEADER bmfh;
	try {
		counts = pFile->Read((LPVOID) &bmfh, 
					sizeof(BITMAPFILEHEADER));
		if(counts != sizeof(BITMAPFILEHEADER)) {
			throw new CFileException;
		}
		if(bmfh.bfType != 0x4d42) {
			throw new CNotSupportedException;
		}
		size = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_lpBMPHdr = (LPBITMAPINFOHEADER) new char[size];
		//BITMAPINFOHEADER和颜色表
		counts = pFile->Read(m_lpBMPHdr, size); 
		if(m_lpBMPHdr->biCompression != BI_RGB) {
			throw new CNotSupportedException;
		}
		ComputeImage();
		ComputePaletteSize(m_lpBMPHdr->biBitCount);
		SetWinPalette();
		UseLogPalette(pDC);
		m_hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), 
			(LPBITMAPINFO) m_lpBMPHdr, DIB_RGB_COLORS,
			(LPVOID*) &m_lpDIBits, NULL, 0);
		ASSERT(m_lpDIBits != NULL);
		counts = pFile->Read(m_lpDIBits, m_dwImageSize); // 图像
	}
	catch(CException* pe) {
		AfxMessageBox("ReadSection error");
		pe->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CFG_DIB::Display(CDC* pDC)
{
	if(m_lpBMPHdr == NULL) return FALSE;
	if(m_hPalette != NULL) {
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	::StretchDIBits(pDC->GetSafeHdc(), m_Dest.x, m_Dest.y,
								m_DestSize.cx, m_DestSize.cy,
								m_Src.x, m_Src.y,
								m_SrcSize.cx, m_SrcSize.cy,
								m_lpDIBits, (LPBITMAPINFO) m_lpBMPHdr, 
								DIB_RGB_COLORS, SRCCOPY);
	return TRUE;
}

long CFG_DIB::GetLineBit()
{
	long dwBytes = ((long)m_lpBMPHdr->biWidth * m_lpBMPHdr->biBitCount) / 32;
	if(((long)m_lpBMPHdr->biWidth * m_lpBMPHdr->biBitCount) % 32) 
	{
		dwBytes++;
	}
	dwBytes *= 4;

	return dwBytes;
}

void CFG_DIB::ReleaseMemBlock()
{
	if(m_lpBMPHdr)
	{
		delete [] m_lpBMPHdr;
		m_lpBMPHdr = NULL;
	}
	if(m_lpDIBits)
	{
		delete [] m_lpDIBits;
		m_lpDIBits = NULL;
	}
	
}