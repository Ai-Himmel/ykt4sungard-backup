// KSLog.h: interface for the CKSLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSLOG_H__51F97791_06F7_4493_8A76_BFCD4A134393__INCLUDED_)
#define AFX_KSLOG_H__51F97791_06F7_4493_8A76_BFCD4A134393__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef _MT
#include "mutex.h"
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

const	int		LOG_FILEBLOCK		= 10240;	//	�ļ��ı��Сʱÿ����ӵĳ��ȣ���λ���ֽ�
const	int		LOG_MAXLINE		= 10240;	//	ÿ����־����󳤶�(���ڳ������ƣ����ô���32767)

const	int		LOG_APPMAXNAME		= 21;		//	Ӧ�õ����Ƶĳ���
const	int		LOG_APPMAXCOUNT		= 20;		//	Ӧ�õĸ���
const	int		LOG_MAXPACKHINT		= 51;		//	���ݰ�����ʾ�ĳ���

/* ****** Updated by CHENYH at 2004-3-30 16:46:49 ****** 
const	int		LOG_APPWRITE		= 1;		//	д��Ӧ��
const	int		LOG_APPREAD		= 0;		//	д��Ӧ��
*/
#define LOG_APPWRITE 1
#define LOG_APPREAD  0

const	int		LOG_APPSYSID		= 0;
const	char		LOG_APPSYSNAME[LOG_APPMAXNAME]	= "��־ϵͳ��־";
/* ****** Updated by CHENYH at 2004-3-15 19:59:09 ****** 
const	int		LOG_APPPACKID7					= 1;
const	char		*LOG_APPPACKNAME7[LOG_APPMAXNAME] = "CPACK����־";
*/
const	int		LOG_APPPACKID	   = 12;
const	char		LOG_APPPACKNAME[LOG_APPMAXNAME]  = "CPACKC����־";
const	int		LOG_APPDATAID		= 11;
const	char		LOG_APPDATANAME[LOG_APPMAXNAME]	= "��־ϵͳ������־";

const	int		LOG_SIZEOFSHORT	= sizeof(short);//	
const	int		LOG_SIZEOFDATE		= 18;			//	��¼ʱ���ִ��ĳ���
const	int		LOG_SIZEOFLOGHEAD	= (LOG_SIZEOFDATE + LOG_SIZEOFSHORT);

const	char		COMPANYNAME[12]		= "Kingstar";		//	��˾����
const	char		PRODUCTNAME[12]		= "Log file";		//	��Ʒ����
const	char		CRYPTPASSWORD[12]	= "wuzhouqun";		//	

const	int		LOG_FILEYEAR		= 0x4;
const	int		LOG_FILEMONTH		= 0x2;
const	int		LOG_FILEDAY		= 0x1;

const	int		LOG_OPENNODEFINE	= 0;
const	int		LOG_OPENFORWRITE	= 1;
const	int		LOG_OPENFORREAD		= 2;

/* ���´����������ֽڶ���ʹ�õ� */
   /* ���´����������ֽڶ���ʹ�õ� */
#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif


typedef struct _ST_LOGFILEINFO
{
	unsigned short	wVer;						//	�ļ��汾��100����1.00
	short	nAppCount;					//	����ļ��е�Ӧ�����ĸ���
	char	szCompany[12];				//	Kingstar
	char	szProduct[12];				//	.klg file
	char	szPassword[12];				//	�������ݵ����롣
	unsigned int	dwHeadLen;					//	�ļ�ͷ�ĳ��ȣ�����Ӧ��������������
	unsigned int	dwValidLen;					//	�ļ����õĳ��ȣ�
	unsigned int	dwTotalLen;					//	�ļ�ռ�ÿռ���ֽ�
	unsigned int	dwRecordCount;				//	�ļ��еļ�¼��
	unsigned int	dwPackCount;				//	���ݰ�����
} __PACKED__ ST_LOGFILEINFO;

typedef struct _ST_LOGFILEAPP
{
	short	nAppID;						//	Ӧ�õ�ID��
	char	szAppName[LOG_APPMAXNAME];	//	Ӧ�õ�����
	short	nReserve;					//��Ӧ�õı�����
} __PACKED__ ST_LOGFILEAPP;

typedef struct _ST_LOGHEAD
{
	ST_LOGFILEINFO		stInfo;
	ST_LOGFILEAPP		stApp[LOG_APPMAXCOUNT];
} __PACKED__ ST_LOGHEAD;


#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__



class CKSLog  
{
private:
	int	m_nOpenMode;

#ifdef _MT
	CMUTEX m_mutex;
#endif

	unsigned int	m_dwFileOpt;
	char	m_szLogFile[MAX_PATH];
	char	m_szFilePath[MAX_PATH];
	char	m_szFileHead[50];
	char	m_szFileDate[12];
	char	m_szFileExt[20];

	FILE*	m_fp;
	
	ST_LOGHEAD	m_stHead;	

public:

private:
	void ReverseLogHead(ST_LOGHEAD *head);
	void reverse(void *data,int len);
	bool WriteToFile(short nAppID, void* pBuf, short nBufLen);
	void CheckFileName();
	void CloseFile();
	bool ReadFileHead();
	bool ResizeFile();
	bool OpenFile();
	bool Crypt(char* pszOld, int nLen, char* pszPassword);
	bool SaveFileHead(bool bForceSave=false);
	void Init();

public:
	int RemoveOverdueKLogFile(int overdue=10);
	bool FlushToKLogFile();
	bool WriteData(void *pBuf, int nBufLen);
	bool WriteRawLog(short nAppID, void *pBuf, int nBufLen);
	bool WritePack(void *pBuf, int nBufLen, char * pszPackHint);
	bool WriteLog(short nAppID, char* pMsg, ...);
	void CloseLogFile();
	bool OpenLogFile(const char *szFileName=NULL);
	bool AddAppName(short nAppID,const char *pszAppName);
	bool SetFileMode(char* pszFilePath="Log", char* pszFileHead="", char* pszFileExt=".klg",unsigned int dwFileOpt=LOG_FILEYEAR|LOG_FILEMONTH|LOG_FILEDAY);
	CKSLog();
	virtual ~CKSLog();

};

#endif // !defined(AFX_KSLOG_H__51F97791_06F7_4493_8A76_BFCD4A134393__INCLUDED_)
