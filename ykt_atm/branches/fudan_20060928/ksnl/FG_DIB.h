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
	//Ĭ�Ϲ��캯��
	CFG_DIB();
	//���캯��,����ͼ���͸�,�Լ���¼ÿ�����������ֽ�������ʼ��
	CFG_DIB(int width, int height, int nBitCounts);
	virtual ~CFG_DIB();

public:
	HBITMAP m_hBitmap;
	LPBYTE m_lpDIBits;					//DIBλ����ʼλ��
	LPBITMAPINFOHEADER m_lpBMPHdr;		//BITMAPINFOHEADER��Ϣ
	LPVOID m_lpvColorTable;				//��ɫ����Ϣ
	HPALETTE m_hPalette;				//����ɫ��

private:
	DWORD m_dwImageSize;				//��BITMAPINFOHEADER��BITMAPFILEHEADER��λ
	int m_nColorEntries;				//��ɫ����ĸ���
	void ReleaseMemBlock();

//��ʾ����
public:
	CPoint m_Dest;						//Ŀ�ľ���������Ͻ�����
	CSize m_DestSize;					//��ʾ���εĿ�Ⱥ͸߶�
	CPoint m_Src;						//ԭ�������½�����
	CSize m_SrcSize;					//ԭ���ο�Ⱥ͸߶�

public:
	void InitDestroy();							//��ʼ������
	void ComputePaletteSize(int nBitCounts);	//�����ɫ���С
	void ComputeImage();						//����ͼ���С

	//��BMP�ļ��ж���DIB��Ϣ
	BOOL ReadFile(CFile* pFile);
	//��BMP�ļ��ж���DIB��Ϣ,��ReadFile��ͬ����ʹ��CreateSection����λͼλ
	BOOL ReadSection(CFile* pFile, CDC* pDC = NULL);
	//��DIBд���ļ��������BMPͼƬ��ʽ
	BOOL WriteFile(CFile* pFile);
	//�����µ�λͼ�ļ������ݲ���width,height,nBitCounts�����ڴ�ռ�
	BOOL NewFile(int width, int height, int nBitCounts);
	//�ر�λͼ�ļ�
	BOOL CloseFile();

	//��ʾλͼ
	BOOL Display(CDC* pDC);

	HBITMAP CreateBitmap(CDC* pDC);				//��DIB����DDB
	HBITMAP CreateSection(CDC* pDC = NULL);		//����λͼλ���ݣ�����������
	//���DIBû����ɫ���������߼���ɫ��
	BOOL SetLogPalette(CDC* pDC);
	//���DIB����ɫ�����Դ���ϵͳ��ɫ��
	BOOL SetWinPalette();
	//��DIB������߼���ɫ��ѡ���豸�����Ȼ��ʵ�ֵ�ɫ��
	UINT UseLogPalette(CDC* pDC);

	//�õ�BitmapInfoHeader�Ĵ�С��������ɫ������
	int GetHeaderSize()
	{
		return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorEntries;
	}
	//�õ�ͼ��ĸ߶�
	int GetHeight()
	{
		if(m_lpBMPHdr == NULL) return 0;
		return m_lpBMPHdr->biHeight;
	}
	//�õ�ͼ��Ŀ��
	int GetWidth()
	{
		if(m_lpBMPHdr == NULL) return 0;
		return m_lpBMPHdr->biWidth;
	}
	//�õ�ͼ��Ĵ�С
	int GetImageSize()
	{
		return m_dwImageSize;
	}
	long GetLineBit();		//�õ�һ�е�������
};

#endif // !defined(AFX_FG_DIB_H__873E62A0_D6E8_4151_9F0F_815768446735__INCLUDED_)
