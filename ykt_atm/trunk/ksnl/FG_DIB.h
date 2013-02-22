// FG_DIB.h: interface for the CFG_DIB class.
//by forevergis 2003.4.16
//forevergis@sina.com.cn
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FG_DIB_H__873E62A0_D6E8_4151_9F0F_815768446735__INCLUDED_)
#define AFX_FG_DIB_H__873E62A0_D6E8_4151_9F0F_815768446735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFG_DIB : public CObject  
{
public:
	//默认构造函数
	CFG_DIB();
	//构造函数,根据图象宽和高,以及记录每个象素所需字节数来初始化
	CFG_DIB(int width, int height, int nBitCounts);
	virtual ~CFG_DIB();

public:
	HBITMAP m_hBitmap;
	LPBYTE m_lpDIBits;					//DIB位的起始位置
	LPBITMAPINFOHEADER m_lpBMPHdr;		//BITMAPINFOHEADER信息
	LPVOID m_lpvColorTable;				//颜色表信息
	HPALETTE m_hPalette;				//条调色板

private:
	DWORD m_dwImageSize;				//非BITMAPINFOHEADER或BITMAPFILEHEADER的位
	int m_nColorEntries;				//颜色表项的个数
	void ReleaseMemBlock();

//显示参数
public:
	CPoint m_Dest;						//目的矩形域的左上角坐标
	CSize m_DestSize;					//显示矩形的宽度和高度
	CPoint m_Src;						//原矩形左下角坐标
	CSize m_SrcSize;					//原矩形宽度和高度

public:
	void InitDestroy();							//初始化变量
	void ComputePaletteSize(int nBitCounts);	//计算调色板大小
	void ComputeImage();						//计算图象大小

	//从BMP文件中读入DIB信息
	BOOL ReadFile(CFile* pFile);
	//从BMP文件中读入DIB信息,与ReadFile不同的是使用CreateSection创建位图位
	BOOL ReadSection(CFile* pFile, CDC* pDC = NULL);
	//将DIB写入文件，保存成BMP图片格式
	BOOL WriteFile(CFile* pFile);
	//创建新的位图文件，根据参数width,height,nBitCounts分配内存空间
	BOOL NewFile(int width, int height, int nBitCounts);
	//关闭位图文件
	BOOL CloseFile();

	//显示位图
	BOOL Display(CDC* pDC);

	HBITMAP CreateBitmap(CDC* pDC);				//用DIB创建DDB
	HBITMAP CreateSection(CDC* pDC = NULL);		//创建位图位数据，即象素数据
	//如果DIB没有颜色表，可以用逻辑调色板
	BOOL SetLogPalette(CDC* pDC);
	//如果DIB有颜色表，可以创建系统调色板
	BOOL SetWinPalette();
	//把DIB对象的逻辑调色板选进设备环境里，然后实现调色板
	UINT UseLogPalette(CDC* pDC);

	//得到BitmapInfoHeader的大小，包含颜色表数据
	int GetHeaderSize()
	{
		return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorEntries;
	}
	//得到图像的高度
	int GetHeight()
	{
		if(m_lpBMPHdr == NULL) return 0;
		return m_lpBMPHdr->biHeight;
	}
	//得到图像的宽度
	int GetWidth()
	{
		if(m_lpBMPHdr == NULL) return 0;
		return m_lpBMPHdr->biWidth;
	}
	//得到图像的大小
	int GetImageSize()
	{
		return m_dwImageSize;
	}
	long GetLineBit();		//得到一行的象素数
};

#endif // !defined(AFX_FG_DIB_H__873E62A0_D6E8_4151_9F0F_815768446735__INCLUDED_)
