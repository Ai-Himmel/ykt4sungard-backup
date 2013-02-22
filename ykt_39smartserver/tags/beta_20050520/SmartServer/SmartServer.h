////////////////////////////////////////////////////////////////////////////////////////
////  三九前置采集服务器.  广东三九智慧电子信息产业有限公司版权所有. 
////////////////////////////////////////////////////////////////////////////////////////
////文件名称: SmartServer.h
////文件说明: 
////         定义全局变量与函数. 定义异常基类/注册表类/Lock类/线程基类.
////
////程序设计: ZhangWei (gozw)
////日期时间: 2004-03-15
////备注说明: 
////          SmartServer工程中的公共单元
////
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __H_SMART_SERVER_H__
#define __H_SMART_SERVER_H__

#pragma once

const int nOutListenPort = 8902 ;
const int nOutBoardPort = 8901 ;
const int nMaxOutNumber = 32 ;
const int nTimeOutItem = 2048 ; 
const int nAPITimeOut = 10000;

const LPCTSTR LOG_FILE_NAME = _T("smart.log");
const LPCTSTR SERVICE_TITLE = _T("三九智慧一卡通");
const LPCTSTR SHUTDOWN_NAME = _T("_SMART_CARD_SHUTDOWN_");

const LPCTSTR REGKEY_DBMAX      = _T("DB_CONNECT");
const LPCTSTR REGKEY_DBPASS     = _T("DB_PASS");
const LPCTSTR REGKEY_DBSERVER   = _T("DB_SERVER");
const LPCTSTR REGKEY_DBUSER     = _T("DB_USER");
const LPCTSTR REGKEY_OUTPORT    = _T("OUT_PORT");
const LPCTSTR REGKEY_MAXOUT     = _T("MAX_OUT");
const LPCTSTR REGKEY_LOGNAME    = _T("LOGNAME");
const LPCTSTR REGKEY_MIN_WORKTHREAD  = _T("MinWorkThread");
const LPCTSTR REGKEY_MAX_WORKTHREAD  = _T("MaxWorkThread");
const LPCTSTR REGKEY_START_WORKTHREAD= _T("StartWorkThread");
const LPCTSTR REGKEY_MODULE = _T("SmartModule");
const LPCTSTR REGKEY_TASKMODULE = _T("TaskModule");

const long MAX_QUEUE_SIZE = 1000 ;

//定义数据库类型
enum 
{
	DB_TYPE_ORACLE,
	DB_TYPE_SQLSERVER,
	DB_TYPE_ACCESS,
	DB_TYPE_FOXPRO,
	DB_TYPE_INFORMIX
};

//******************************************************************************
//*名称: TRegKey
//*功能: 注册表操作封装类(来自MFC源码)
//******************************************************************************
class TRegKey
{
public:
	TRegKey();
	~TRegKey();

public:
	operator HKEY() const;
	HKEY m_hKey;

public:
	LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName);
	LONG QueryValue(DWORD& dwValue, LPCTSTR lpszValueName);
	LONG QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount);
	LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	LONG Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		REGSAM samDesired = KEY_ALL_ACCESS,
		LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		LPDWORD lpdwDisposition = NULL);
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,
		REGSAM samDesired = KEY_ALL_ACCESS);
	LONG Close();
	HKEY Detach();
	void Attach(HKEY hKey);
	LONG DeleteSubKey(LPCTSTR lpszSubKey);
	LONG RecurseDeleteKey(LPCTSTR lpszKey);
	LONG DeleteValue(LPCTSTR lpszValue);
};

//******************************************************************************
//*名称: TException
//*功能: 异常基类
//******************************************************************************
class TException
{
protected:
	TCHAR   m_szErrorText[256];
	DWORD   m_dwErrorCode;

protected:
	virtual void GetErrorText(DWORD dwCode, LPTSTR pszBuffer, DWORD dwBufferSize);

public:
	TException();
	TException(DWORD dwSysErrorCode);
	TException(LPCTSTR pszErrorText);
	TException(LPCTSTR pszErrorText, DWORD dwSysErrorCode);
	TException(DWORD nErrorCode, LPCTSTR pszError);

	virtual ~TException() { };

	LPCTSTR GetText() const { return m_szErrorText; }
	DWORD GetCode() const { return m_dwErrorCode; }

	virtual void ReportError(LPCTSTR pszErrorText = _T(""));

	static void ReportUnknowError();
};

//******************************************************************************
//*名称: TLock
//*功能: WIN32简易锁类
//******************************************************************************
class TLock
{
protected:
	CRITICAL_SECTION   m_Lock;

public:
	TLock()
	{
		InitializeCriticalSection(&m_Lock);
	}

	virtual ~TLock()
	{
		DeleteCriticalSection(&m_Lock);
	}

	void Lock()
	{
		EnterCriticalSection(&m_Lock);
	}

	void Unlock()
	{
		LeaveCriticalSection(&m_Lock);
	}
};

//******************************************************************************
//*名称: TThread
//*功能: WIN32线程基类
//******************************************************************************
class TThread
{
protected:
	BOOL	m_bShutdown;
	BOOL	m_bSuspend;
	HANDLE	m_hThread;
	DWORD	m_dwThreadID;
	BOOL	m_bStart;

protected:
	virtual void Run() = 0 ;

	virtual void OnShutdown();
	virtual void OnStart();

public:
	TThread();
	virtual ~TThread();

	virtual void Start();
	virtual void Shutdown();

	void Terminate(DWORD dwExitCode=0);
	BOOL WaitFor(DWORD dwTimeOut=INFINITE);

	void Suspend();
	void Resume();

	BOOL WaitForQuit();

	BOOL IsStart() const { return m_bStart; }
	BOOL IsShutdown() const { return m_bShutdown; }
	BOOL IsSuspend() const { return m_bSuspend; }
	HANDLE GetHandle() const { return m_hThread; }

	static unsigned int __stdcall ThreadProc(LPVOID lpvoid);
};

//******************************************************************************
//*名称: TCOMSocketLibrary
//*功能: WIN32下COM及Winsock环境初始化
//******************************************************************************
class TCOMSocketLibrary
{
public:
	TCOMSocketLibrary()
	{
		HRESULT hr = ::CoInitialize(NULL);
		if( FAILED(hr) )
		{
			throw TException("CoInitialize error!");
		}

		WSADATA wsaData;
		if( WSAStartup(MAKEWORD(2,2), &wsaData) )
		{
			CoUninitialize();
			throw TException(WSAGetLastError());
		}
	}

	virtual ~TCOMSocketLibrary()
	{
		OleUninitialize();
		CoUninitialize();
		WSACleanup();
	}
};

const LONG  InitAllocLength  = 20;

enum TEListDuplicates
{
    dupIgnore,
    dupAccept,
    dupError
};

//******************************************************************************
//*名称: TList
//*功能: 定义TList类
//******************************************************************************
class TList
{
private:
    bool m_bSorted;
    TEListDuplicates m_eDuplicates;

    void InsertItem(long nIndex, void * P);

    void ExchangeItems(long nIndex1, long nIndex2);
    void QuickSort(long nL, long nR);

protected :
     struct pPointer{
       void *P ;
     };
     long m_nCount;
     long m_AllocLength;
     void ** m_Pointer ;
     virtual void AllocBuffer(long lCount) ;
     virtual void AllocNewBuffer(long NewCount) ;
     virtual long ExtendLength() ;
     virtual void init() ;
     virtual void Release() ;
     virtual void Release(void ** P) ;

protected:
     virtual void Destroy(void * P);
     virtual long CompareValue(void *pItem1, void *pItem2);

public :
     TList();
     virtual ~TList();

     virtual long Add(void * P) ;
     virtual void Clear(void);
     long         GetCount(){return m_nCount;};
     virtual void Delete(long Index);
     virtual void Insert(long nIndex,void * P);
     long         IndexOf(void * pItem);
     virtual void Remove(void * pItem);

public:
     void * operator[](long nIndex) const ;
     TList& operator=(TList & sSrcList);

     void *Get(long nIndex);
     void *Last();

public:
    void Exchange(long nIndex1, long nIndex2);

    bool FindValue(void *P, long & nIndex);
    long IndexOfValue(void *pItem);

    void SetDuplicates(TEListDuplicates duplicates)
    { m_eDuplicates = duplicates; }
    TEListDuplicates GetDuplicates()
    { return m_eDuplicates; }

    void Sort();
    void SetSorted(bool bSorted);
    bool GetSorted()
    { return m_bSorted; }
};

//************************************************************************************
//*名称: TStackNode
//*功能: 栈结构(适用于多线程环境下)
//************************************************************************************
class TStack
{
	friend class TSmartDocObj;

public:
	class TStackNode
	{
	public:
		TStackNode  *m_pNext;
		void        *m_pData;

	public:
		TStackNode(void *pData, TStackNode  *pNext)
		{
			m_pNext = pNext ;
			m_pData = pData ;
		}

		virtual ~TStackNode()
		{

		}

	};

protected:
	TLock    m_lock;
	int      m_nMaxPos;
	int      m_nCurPos;

	TStackNode  *m_pHead;

public:
	TStack();
	virtual ~TStack();

	void* Pop();
	long Push(void *pData);

	bool IsEmpty() ;
	bool IsFull() ;

	void Release();
};

//************************************************************************************
//*名称: TQueue
//*功能: 队列(没有使用)
//************************************************************************************
class TQueue
{
public:
	class TQueueNode
	{
	public:
		void       *pData;
		TQueueNode *pNext;
		TQueueNode *pPrve;

	public:
		TQueueNode()
		{
			pData = NULL ;
			pNext = NULL ;
			pPrve = NULL ;
		}

		virtual ~TQueueNode() { }
	};

public:
	TQueueNode   *pHead;
	TQueueNode   *pTail;
	TLock         lock;
	long          nCount;

public:
	TQueue();
	virtual ~TQueue();

	void Release();

	void* Get();
	long Put(void *pvoid);

	bool IsEmpty() ;
	bool IsFull() ;
};

inline void TList::init()
{
    m_Pointer = NULL ;
    m_nCount = 0 ;
    m_AllocLength = 0 ;
}

typedef long (*lpfnSendMsg)(char *lpBuffer, long nLength);

class TServer;

TServer* GetServer();
void DelServer(TServer *pServer);

extern void WriteLog(LPCTSTR pszLogText);
extern void DebugPrint(const char *format, ...);
extern void ReportError(const char *format, ...);
extern void GetCurDateTime(char *pszDateTime);
extern void ReportLog(const char *format, ...);
extern void GetResultMessage(long nRet, char *pszString);
extern void WriteTaskLog(LPCTSTR pszLogText);

extern bool bDebug;
extern bool bServer;

extern TCHAR  szLogDir[MAX_PATH];

extern TSSmartFunction  SmartFunction;
extern int              nSmartTimeOut;
extern TSSmartTimeOut   SmartTimeOut[nTimeOutItem];
extern TQueue           TaskQueue;
extern TSSmartProtocol  SmartProtocol;

extern lpfnGetSmartProtocolRule  GetSmartProtocolRule;
extern lpfnVerifyBufferValid     VerifyBufferValid;
extern lpfnSendMsg               SendMsg;

extern void GetCurPath(LPTSTR pszDir);
extern long FindString(LPCTSTR pszString, LPCTSTR pszSubString);

extern long RSReleaseSmartDoc(TSSmartDoc *pSmartDoc);
extern long RSReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount);
extern long RSSmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
extern long RSCreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);


int _stdcall MakeBuf_SetComsumeFlag(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char Flag);/// 功能：设置消费功能开启或关闭/// 参数：///    Flag --- 1 开启///    Flag --- 0 关闭

#endif //SmartServer.cpp