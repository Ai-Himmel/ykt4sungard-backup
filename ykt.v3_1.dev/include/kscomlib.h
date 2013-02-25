#ifndef _KSCOMLIB_H_
#define _KSCOMLIB_H_
#include <windows.h>

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
public:
	CComSmart();
	virtual ~CComSmart();
	bool Open(char *sCom, int nBaudRate);
	void Close();
	bool Write(const unsigned char *buffer, int bufSize);
	bool Read(unsigned char *buffer, int bufMaxSize,int &bufRecv);
	virtual bool PostSend(const unsigned char *lpBuffer, int nBufSize, long nTimeOut);
	virtual bool PostRecv(unsigned char *lpBuffer, int nBufSize, long nTimeOut);	
	size_t InWaiting();
	inline HANDLE handle() const { return m_handle; }
	virtual int SendCommand(const unsigned char *cmd,int cmdlen,unsigned char *recv,int *recvlen,long nTimeOut=1000);
};


#endif // _KSCOMLIB_H_
