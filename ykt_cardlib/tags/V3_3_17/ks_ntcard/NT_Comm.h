// NT_Comm.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(NT_COMM_H)
#define NT_COMM_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>


#define		PICC_REQALL 0x52 
#define		PICC_REQSTD 0x26
#define		MOC_ERROR_CARD_SELECT	0x81		//选择卡失败

#define     PORT_NOTOPEN_ERROR		-1	 //端口未打开
#define     PORT_OPEN_ERROR			-2	 //端口打开失败
#define		SEND_DATA_ERROR			-3   //数据发送错
#define		RECV_DATA_ERROR			-4   //接收数据错误
#define		SELECT_CARD_ERROR		-5   //选择卡错误



//*---------------------------------------------------------------------------
//*名称: CComSmart
//*功能: 串口通讯类
//*---------------------------------------------------------------------------
class CComSmart
{
public:
	bool	m_bComStatus;
	char	m_sCom[10];
	long	m_nRecvLen;
protected:
	HANDLE   m_handle;		
	OVERLAPPED m_readOverlapped;
	OVERLAPPED m_writeOverlapped;
protected:
	bool ClearComm(DWORD dwMask);
	bool SetEventMask(DWORD dwMask);
	bool SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut);
	bool GetEventMask(DWORD& dwMask);
	bool SetState(int nBaud, char cParity, int nDataBit, int nStopBit);
	bool GetState(DCB *pDCB);
	bool ClearError();
	bool Read(unsigned char *buffer, int bufMaxSize,int &bufRecv);
public:
	CComSmart();
	virtual ~CComSmart();
	//! 获得串口句炳
	HANDLE GetHandle();
	bool IsOpen();
	void Attach(HANDLE hComm);
	HANDLE Detach();
	bool Open(char *sCom, int nBaudRate);
	void Close();		
	bool PostSend(unsigned char *lpBuffer, int nBufSize, long nTimeOut);
	bool PostRecv(unsigned char *lpBuffer, int nBufSize, long nTimeOut);	
	size_t InWaiting();
};

#endif
