// TSmartDoc.h: interface for the TSmartDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTDOC_H__D4E03CF2_4639_4025_83D7_A05D5459F962__INCLUDED_)
#define AFX_TSMARTDOC_H__D4E03CF2_4639_4025_83D7_A05D5459F962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TSmartTask.h"
#include "TCmdBuffer.h"

class TSmartDriverThread;
class TSmartServer;

//IO������־
enum IO_Operator
{ 
	IO_Send_Request,
	IO_Send_Completed,
	IO_Recv_Request,
	IO_Recv_Completed,
	IO_Unknow
};

//�����ݱ�־
enum IO_Read_Flag
{
	IO_Read_UNKNOW,   //δ֪
	IO_Read_C2,       //������ʼ��
	IO_Read_C3        //���Ľ�����
};

//��ǰ�豸�Ĳ���״̬
enum
{
	IO_Status_Unknow,        //δ֪
	IO_Status_Free,          //����
//	IO_Stauts_Open,			 //���豸
	IO_Status_Pause,         //��ͣ
	IO_Status_Execute,       //��ִ������
	IO_Status_ExecuteCall,   //��ִ��ҵ���
	IO_Status_ExecuteApi,    //��ִ��ҵ����������е�API
	IO_Status_Finished       //ִ�����
};


struct TSTaskStack
{
	TSmartTaskObj *pTaskObj;		//ָ��ǰ������
	long nIndex;
};

//*---------------------------------------------------------------------------
//*����: TSmartDocObj
//*����: �����豸������(����)
//*---------------------------------------------------------------------------
class TSmartDocObj : public TSSmartDoc, TThread
{
protected:
	char            m_sBuffer[256];

	HANDLE          m_hExecute;
	HANDLE          m_hEvent;
	bool            m_bOpen;

	long            m_nRecvTimeOut;

	DWORD			m_nReadBytes;
	DWORD			m_nWriteBytes;

	TSDeviceInfo    m_DeviceInfo;

	long            m_nTerminate;

	long            m_nIndex;
	TSmartTaskObj  *m_pTaskObj;		//ָ��ǰ������

	long            m_nRealIndex;
	TSmartTaskObj  *m_pRealTaskObj;		//ָ��ǰ������

	OVERLAPPED		m_ReadOver;
	OVERLAPPED		m_WriteOver;

	TSmartServer   *m_pServer;

	TStack              m_Stack;		//�����ջ
	TCmdBuffer          m_CmdBuffer;

	long                m_IOStatus;
	TLock               m_StatusLock;

	bool                m_bPause;
	TLock               m_PauseLock;

	TList               m_ChildDoc;
	TLock               m_EventLock;

	//�������Ϳ��ƽ����
	TSmartDocObj		*m_pBus;
	TLock               m_BusLock;
	TLock               m_TaskLock;
	TLock               m_ExecLock;
	bool                m_bShare;		//�Ƿ���������
	long				m_nBusNo;		//���豸�������ϵĵڼ����豸(0..255)
	long				m_nTotal;		//�豸����
	long				m_nBusTask;
	HANDLE				m_hShare;		//�¼�����
	long				iStack;
	TSmartTaskObj		m_CurTaskObj;
protected:
	virtual long WaitingWrite(DWORD dwTimeOut) = 0 ;
	virtual long WaitingRead(DWORD dwTimeOut) = 0 ;

	virtual long ExecuteTask(TSmartTaskObj *pObj, long nIndex);

	void Run();

	virtual long ProcessRequest(bool bBroad=false, TCmdBuffer *pCmdBuffer=NULL);
	virtual long RecvCmdBuffer(TCmdBuffer *pCmdBuffer);
	virtual long SendCmdBuffer(TCmdBuffer *pCmdBuffer);
	virtual void TaskFinished(long nResult);
	virtual long SendRecv(TCmdBuffer *pCmdBuffer, long nSleep);

	virtual void WaitBusResource();
	virtual void FreeBusResource();	
	

public:	static void ConvertToDevice(TSSmartDoc *pDoc, TSDeviceInfo *pDeviceInfo);

public:
	TSmartDocObj();
	TSmartDocObj(const TSSmartDoc *pDoc);
	virtual ~TSmartDocObj();	
	long DebugSendRequest(TCmdBuffer *pCmdBuffer);

	void LockBus();
	void UnLockBus();
	void SetFirstShare();
	void SetShare(TSmartDocObj& Obj);

	void SetOpenFlag(bool bBool);

	void ClearChildDoc();
	void Clear();
	void AssignBy(const TSSmartDoc *pSmartDoc);
	void Release();

	void Push();
	void Pause();
	void Continue();
	void Stop();

	void Start();

	void GetInfo(long nAuthNo, TSDocInfo *pDocInfo);

	long GetChildDocCount() ;

	bool Execute(TSmartTaskObj *pObj, long nIndex);

	bool IsEnable() const { return m_bEnable; }
	bool Enable(long nAuthID, bool bEnable);

	bool GetPause();
	void SetPause(bool bBool);

	bool HaveHistoryTask();
	bool IsBus() const ;
	bool IsOpen() const ;
	bool IsExecuted() ;
	bool IsWaitExecute();
	bool IsParent() const { return m_nParentID>0?false:true; }

	DWORD GetReadBytes() const { return m_nReadBytes; }
	DWORD GetWriteBytes() const { return m_nWriteBytes; }

	HANDLE GetReadHandle() const { return m_ReadOver.hEvent; }
	HANDLE GetWriteHandle() const { return m_WriteOver.hEvent; }

	void SetIOStatus(long nStatus);
	long GetIOStatus();

	bool AddToTaskStack(TSmartTaskObj *pObj, long nIndex);
	

	long GetPriority();
	bool IsChildDoc(long nAuthID);
	void StopChildDoc(long nAuthID);
	void SetChildDocStatus(long nAuthID, long nStatus);

	void SetServer(TSmartServer *pServer) { m_pServer = pServer; }

	void Reset();
	void DestoryStack();

	int CreateDocArray(TSSmartDocEx *pDocEx);

	long SendRequest(TCmdBuffer *pCmdBuffer);
	void OpenDevice();
	long AddOrUpdateDoc(TSmartTaskObj *pObj,long nIndex);
	void SetReadOver(OVERLAPPED *pOver);
	void SetWriteOver(OVERLAPPED *pOver);

	virtual void AddChildDoc(TSSmartDoc *pSmartDoc);

	virtual void ReadEmptyBuffer() { };

	virtual void Open() = 0 ;
	virtual void Close() = 0 ;

	virtual long PostSend(char *lpBuffer, int nBufSize, long nTimeOut) = 0 ;
	virtual long PostRecv(char *lpBuffer, int nBufSize, long nTimeOut) = 0 ;
	virtual long WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut) = 0 ;

	virtual HANDLE GetHandle() const = 0 ;
	virtual void SetHandle(HANDLE hHandle) = 0 ;

	friend class TSmartServer;
};

//*---------------------------------------------------------------------------
//*����: TSocketSmartDocObj
//*����: �����豸������(TCP/IPЭ��)
//*---------------------------------------------------------------------------
class TSocketSmartDocObj : public TSmartDocObj
{
protected:
	SOCKET   m_hSocket;

protected:
	void Create(int nAf, int nType, int nProtocol);
	void Bind(char *pszAddress, int nPort);
	void Listen(int nQueue);
	void Connect(char* pszAddress, int nPort, long dwTimeOut);

	long Write(char *pszBuffer, long nBufferSize, long nTimeOut);
	long Read(char *pszBuffer, long nBufferSize, long nTimeOut);

	long WriteTo(char *pszBuffer, long nBufferSize, const SOCKADDR_IN *psockAddr, long nTimeOut);
	long ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut);

	long WaitingWrite(DWORD dwTimeOut);
	long WaitingRead(DWORD dwTimeOut);

public:
	TSocketSmartDocObj();
	virtual ~TSocketSmartDocObj();

	void ReadEmptyBuffer();

	void Open();
	void Close();

	long PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	long PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);
    long WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut);

	HANDLE GetHandle() const { return (HANDLE)m_hSocket; }
	void SetHandle(HANDLE hHandle) { m_hSocket = (SOCKET)hHandle;}

};

//*---------------------------------------------------------------------------
//*����: TSocketSmartDocObj
//*����: �����豸������(����)
//*---------------------------------------------------------------------------
class TCOMSmartDocObj : public TSmartDocObj
{
protected:
	HANDLE  m_hHandle;

protected:
	void ClearComm(DWORD dwMask);
	void SetEventMask(DWORD dwMask);
	void SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut);
	void GetEventMask(DWORD& dwMask);
	void SetState(int nBaud, char cParity, int nDataBit, int nStopBit);
	void GetState(DCB *pDCB);
	void ClearError();

	long Read(char *pszBuffer, long nBufferSize, long nTimeOut);
	long Write(char *pszBuffer, long nBufferSize, long nTimeOut);

	long WaitingWrite(DWORD dwTimeOut);
	long WaitingRead(DWORD dwTimeOut);

public:
	TCOMSmartDocObj();
	virtual ~TCOMSmartDocObj();

	void Open();
	void Close();
	bool Reset();

	long PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	long PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);
    long WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut);

	HANDLE GetHandle() const { return m_hHandle; }
	void SetHandle(HANDLE hHandle) { m_hHandle = hHandle;}
};


//*---------------------------------------------------------------------------
//*����: TModemSmartDocObj
//*����: �����豸������(Modem)
//*---------------------------------------------------------------------------
class TModemSmartDocObj : public TSmartDocObj
{
protected:
	HANDLE  m_hHandle;

protected:
	void ClearComm(DWORD dwMask);
	void SetEventMask(DWORD dwMask);
	void SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut);
	void GetEventMask(DWORD& dwMask);
	void SetState(int nBaud, char cParity, int nDataBit, int nStopBit);
	void GetState(DCB *pDCB);
	void ClearError();

	long Read(char *pszBuffer, long nBufferSize, long nTimeOut);
	long Write(char *pszBuffer, long nBufferSize, long nTimeOut);

	long WaitingWrite(DWORD dwTimeOut);
	long WaitingRead(DWORD dwTimeOut);

	void DialCall();
	void Hangup();

public:
	TModemSmartDocObj();
	virtual ~TModemSmartDocObj();

	void Open();
	void Close();
	bool Reset();

	long PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	long PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);
    long WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut);

	HANDLE GetHandle() const { return m_hHandle; }
	void SetHandle(HANDLE hHandle) { m_hHandle = hHandle; }
};

#endif // !defined(AFX_TSMARTDOC_H__D4E03CF2_4639_4025_83D7_A05D5459F962__INCLUDED_)
