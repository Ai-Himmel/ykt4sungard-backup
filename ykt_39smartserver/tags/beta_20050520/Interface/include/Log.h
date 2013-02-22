//////////////////////////////////////////////////////////////////////
//
//	��д������Ⱥ
//	���ڣ�20011102
//	���ã����ڼ�¼��־����������Ŀ¼���ļ�������׺��
//			���������ð��������������ļ�
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_LOG_H__EE35ED0B_CD12_4704_9A22_B71DCD127584__INCLUDED_)
#define AFX_LOG_H__EE35ED0B_CD12_4704_9A22_B71DCD127584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef TLOG_EXPORTS
#define TLOG_API __declspec(dllexport)
#else
#define TLOG_API __declspec(dllimport)
#endif


const	int		LOG_FILEBLOCK		= 10240;	//	�ļ��ı��Сʱÿ����ӵĳ��ȣ���λ���ֽ�
const	int		LOG_MAXLINE		= 10240;	//	ÿ����־����󳤶�(���ڳ������ƣ����ô���32767)

const	int		LOG_APPMAXNAME		= 21;		//	Ӧ�õ����Ƶĳ���
const	int		LOG_APPMAXCOUNT		= 20;		//	Ӧ�õĸ���
const	int		LOG_MAXPACKHINT		= 51;		//	���ݰ�����ʾ�ĳ���
const	int		LOG_APPWRITE		= 1;		//	д��Ӧ��
const	int		LOG_APPREAD		= 0;		//	д��Ӧ��

const	int		LOG_APPSYSID					= 0;
const	char		LOG_APPSYSNAME[LOG_APPMAXNAME]	= "��־ϵͳ��־";
const	int		LOG_APPPACKID					= 1;
const	char		LOG_APPPACKNAME[LOG_APPMAXNAME] = "CPACK����־";
const	int		LOG_APPDATAID					= 11;
const	char		LOG_APPDATANAME[LOG_APPMAXNAME]	= "��־ϵͳ������־";

const	int		LOG_SIZEOFSHORT		= sizeof(short);//	
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


#pragma pack (push, log_head)
#pragma pack (1)

typedef struct st_LogFileInfo
{
	WORD	wVer;						//	�ļ��汾��100����1.00
	short	nAppCount;					//	����ļ��е�Ӧ�����ĸ���
	char	szCompany[12];				//	Kingstar
	char	szProduct[12];				//	.klg file
	char	szPassword[12];				//	�������ݵ����롣
	DWORD	dwHeadLen;					//	�ļ�ͷ�ĳ��ȣ�����Ӧ��������������
	DWORD	dwValidLen;					//	�ļ����õĳ��ȣ�
	DWORD	dwTotalLen;					//	�ļ�ռ�ÿռ���ֽ�
	DWORD	dwRecordCount;				//	�ļ��еļ�¼��
	DWORD	dwPackCount;				//	���ݰ�����
}ST_LOGFILEINFO;

typedef struct st_LogFileApp
{
	short	nAppID;						//	Ӧ�õ�ID��
	char	szAppName[LOG_APPMAXNAME];	//	Ӧ�õ�����
	short	nReserve;					//��Ӧ�õı�����
}ST_LOGFILEAPP;

typedef struct st_LogHead
{
	ST_LOGFILEINFO		stInfo;
	ST_LOGFILEAPP		stApp[LOG_APPMAXCOUNT];
}ST_LOGHEAD;

#pragma pack (pop , log_head)

class TLOG_API CKSTime
{
private:
	//CCriticalSection m_csTime;
	void *m_pCSTime;

	unsigned long m_LastTick;

	int m_Year;
	int m_Month;
	int m_Day;
	int m_WeekDay;

	int m_Hour;
	int m_Minute;
	int m_Second;
	int m_MSecond;

	void ReflushTime();   

public:
	CKSTime();
	virtual ~CKSTime();

	CKSTime *GetCurrentTime();
	int GetYear();    // { return m_Year; }
	int GetMonth();   // { return m_Month; }
	int GetDay();     // { return m_Day; }
	int GetHour();    // { return m_Hour; }
	int GetMinute();  //{ return m_Minute; } 
	int GetSecond();  // { return m_Second; }
	int GetDayOfWeek(); // { return m_WeekDay}
};

TLOG_API CKSTime *GetKSTime();

class TLOG_API CLog  //: public CObject
{
public:
	BOOL	GetLog(DWORD dwIndex, short* pnAppID, char *pszDate, char* pszPackHint, char *pszLog, short *pnLogLen);
	BOOL	GetNextPack(DWORD* pdwOffset, char* pszPackHint, char* pszDate, char *pszLog, short* pnLogLen);
	BOOL	GetNextLog(DWORD* pdwOffset, short* pnAppID, char* pszDate, char *pszLog, short* pnLogLen);	
	BOOL	WritePack(void *pBuf, int nBufLen, LPCSTR pszPackHint="CPACK���ݰ�");

	BOOL	WriteData(void *pBuf, int nBufLen);
	BOOL	WriteRawLog(short nAppID, void *pBuf, int nBufLen);
	BOOL	FlushSaveFileHead();

	void	CloseLogFile();
	BOOL	OpenLogFile(const char *szFileName=NULL);   //NULL or "" for Read Log File
	BOOL	GetFileInfo(ST_LOGHEAD* pFileHead);

	BOOL	AddAppName(short nAppID, LPCSTR pszAppName);

	CString	GetFileName();
	BOOL	SetFileMode(char* pszFilePath="Log", char* pszFileHead="", char* pszFileExt=".klg", 
						DWORD dwFileOpt=LOG_FILEYEAR|LOG_FILEMONTH|LOG_FILEDAY,
						int nFileHoldCount=30
						);

	void	DeleteOutOfDateFiles(int nFileHoldCount);

	BOOL	WriteLog(short nAppID, char* pMsg,...);
	
	BOOL	EnableWrite(short nAppID, BOOL bWrite=TRUE);
	
	CLog();
	virtual ~CLog();

protected:
	BOOL	ReadFileHead();
	BOOL	SaveFileHead(BOOL bForceSave=FALSE);
	BOOL	OpenFile();
	BOOL	ResizeFile();
	BOOL	Crypt(char* pszOld, int nLen, char* pszPassword);
	BOOL	WriteToFile(short nAppID, void* pBuf, short nBufSize);
	
	void	trim(char* str);
	void	AddSlash(LPSTR path);
	BOOL	GetFullPath(char* pcPath, int nSize);
	void	MakePath(LPSTR path);
	
	void	CheckFileName();

protected:
	int	m_nOpenMode;
	void	Init();
	void	CloseFile();
	HANDLE	m_hSemaphore;	

	DWORD	m_dwFileOpt;
	char	m_szLogFile[MAX_PATH];
	char	m_szFilePath[MAX_PATH];
	char	m_szFileHead[50];
	char	m_szFileDate[11];
	char	m_szFileExt[20];

	int	m_nFileHoldCount;

	FILE*	m_fp;
	//CKSTime  m_cTime;	
	
	ST_LOGHEAD			m_stHead;	
};

#endif // !defined(AFX_LOG_H__EE35ED0B_CD12_4704_9A22_B71DCD127584__INCLUDED_)
