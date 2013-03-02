#ifndef __SMARTCOM_H_
#define __SMARTCOM_H_

#include "smartcommunicationdlg.h"
#include "TThread.h"
#include "data.h"


//*---------------------------------------------------------------------------
//*名称: CComSmart
//*功能: 串口通讯类
//*---------------------------------------------------------------------------
class CComSmart : public CSmart
{
protected:
	HANDLE   m_handle;		
protected:
	bool ClearComm(DWORD dwMask);
	bool SetEventMask(DWORD dwMask);
	bool SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut);
	bool GetEventMask(DWORD& dwMask);
	bool SetState(int nBaud, char cParity, int nDataBit, int nStopBit);
	bool GetState(DCB *pDCB);
	bool ClearError();	
public:
	CComSmart();
	~CComSmart();
	bool Open();
	void Close();	
	bool ReConnect();
	bool PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	bool PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);    
	bool WaitRecv(int WaitTime);
	bool RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut);
};
#endif