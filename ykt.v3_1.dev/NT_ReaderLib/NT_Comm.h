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
#define		MOC_ERROR_CARD_SELECT	0x81		//ѡ��ʧ��

#define     PORT_NOTOPEN_ERROR		-1	 //�˿�δ��
#define     PORT_OPEN_ERROR			-2	 //�˿ڴ�ʧ��
#define		SEND_DATA_ERROR			-3   //���ݷ��ʹ�
#define		RECV_DATA_ERROR			-4   //�������ݴ���
#define		SELECT_CARD_ERROR		-5   //ѡ�񿨴���



//*---------------------------------------------------------------------------
//*����: CComSmart
//*����: ����ͨѶ��
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
	//! ��ô��ھ��
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
