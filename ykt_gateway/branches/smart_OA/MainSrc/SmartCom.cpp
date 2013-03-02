#include "stdafx.h"
#include "SmartCommunication.h"
#include "SmartCommunicationDlg.h"
#include "Smart.h"
#include "readfile.h"
#include "SmartCom.h"

CComSmart::CComSmart()
{
	m_handle=NULL;
}
CComSmart::~CComSmart()
{
	Close();
}

/*=================================================================
* Function ID :  ClearComm
* Input       :  DWORD dwMask
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  ����¼�
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_handle, dwMask) )
	{
		sprintf(m_szErrorText,"PurgeComm()����[%ld]!", GetLastError());
		return false;		
	}
	return true;
}

/*=================================================================
* Function ID :  SetEventMask
* Input       :  DWORD dwMask
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  �����¼�
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_handle, dwMask) )
	{
		sprintf(m_szErrorText,"SetCommMask()����[%ld]!", GetLastError());
		return false;		
	}
	return true;
}

/*=================================================================
* Function ID :  SetTimeOut
* Input       :  DWORD dwReadTimeOut, DWORD dwWriteTimeOut
* Output      :  
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  ���ó�ʱʱ��
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
{
	COMMTIMEOUTS   CommTimeOut;
	
	ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));
	
	CommTimeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOut.ReadTotalTimeoutConstant = 0;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;
	
	CommTimeOut.WriteTotalTimeoutMultiplier = 5;
	CommTimeOut.WriteTotalTimeoutConstant = 50;
	
	if( !SetCommTimeouts(m_handle, &CommTimeOut) )
	{
		sprintf(m_szErrorText,"SetCommTimeouts()����[%ld]!", GetLastError());
		return false;		
	}
	return true;	
}

/*=================================================================
* Function ID :  GetEventMask
* Input       :  void
* Output      :  DWORD& dwMask
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  ���ó�ʱʱ��
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_handle, &dwMask) )
	{
		sprintf(m_szErrorText,"GetEventMask()����[%ld]!", GetLastError());
		return false;		
	}
	return true;	
}

/*=================================================================
* Function ID :  SetState
* Input       :  int nBaud, char cParity, int nDataBit, int nStopBit
* Output      : 
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  ���ô�������
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
{
	TCHAR  szDCB[64];
	DCB    dcb;
	
	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	wsprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);
	
	if( !BuildCommDCB(szDCB, &dcb) )
	{
		sprintf(m_szErrorText,"BuildCommDCB()����[%ld]!", GetLastError());
		return false;		
	}	
	if( !SetCommState(m_handle, &dcb) )
	{
		sprintf(m_szErrorText,"SetCommState()����[%ld]!", GetLastError());
		return false;		
	}
	return true;
}

/*=================================================================
* Function ID :  GetState
* Input       :  DCB *pDCB
* Output      : 
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  �õ�����״̬
* Notice	  :  
*=================================================================*/
bool CComSmart::GetState(DCB *pDCB)
{
	if( !GetCommState(m_handle, pDCB) )
	{
		sprintf(m_szErrorText,"GetCommState()����[%ld]!", GetLastError());
		return false;		
	}
	return true;
}

/*=================================================================
* Function ID :  ClearError
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  ������ڴ���
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::ClearError()
{
	if( !PurgeComm(m_handle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
		sprintf(m_szErrorText,"PurgeComm()����[%ld]!", GetLastError());
		return false;		
	}
	return true;
}

/*=================================================================
* Function ID :  Open
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  �򿪴���
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::Open()
{
	char  szFileName[MAX_PATH];	
	BYTE  str[60];
	
	memset(str,0x00,sizeof str);
	memset(szFileName,0x00,sizeof szFileName);
	
	m_IpPar.bConnect=false;
	
	sprintf(szFileName, "%s", m_IpPar.cIPAddress);
	m_handle = CreateFile(
		szFileName, 
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		0);
	if( m_handle == INVALID_HANDLE_VALUE )
	{
		sprintf(m_szErrorText,"��COM��ʧ��!", GetLastError());
		m_IpPar.bConnect=false;	
		return false;
	}	
	if(!SetState(m_IpPar.nPortNo, 'N', 8, 1))	
	{
		Close();
		m_IpPar.bConnect=false;	
		return false;
	}		
	
	SetTimeOut(10, 0);	
	m_ReadOver.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	m_nReadBytes			= 0 ;
	m_nWriteBytes			= 0 ;	
	m_ReadOver.Internal		= 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset		= 0 ;
	m_ReadOver.OffsetHigh	= 0 ;
	
	ResetEvent(m_ReadOver.hEvent);
	
	m_WriteOver.Internal	= 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset		= 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);
	
	m_IpPar.bConnect=true;	
	sprintf(m_szErrorText,"�����豸[ %s ]�򿪳ɹ�! ����:%s, ������:%ld\n", m_Data.BcdToAsc((BYTE*)m_regno,4,str), m_IpPar.cIPAddress, m_IpPar.nPortNo);
	m_pDialog->AddString(m_szErrorText);
	return true;
}

/*=================================================================
* Function ID :  Close
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  �رմ���
* Notice	  :  
*			  :	 
*					
*=================================================================*/
void CComSmart::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}
	
	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}
	
	if( m_handle != INVALID_HANDLE_VALUE )
	{
		ClearError();
		ClearCommBreak(m_handle);
		CloseHandle(m_handle);
		m_handle = INVALID_HANDLE_VALUE;
	}	
	m_IpPar.bConnect = false ;	
}

/*=================================================================
* Function ID :  PostSend
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE �ɹ�  FALSE ʧ��
* Description :  �����˷�������
* Notice	  :  pszBuffer ���͵�����   nBuffersize ���͵����ݳ��� 
*			  :	 nTimeOut �ȴ�ʱ��
*					
*=================================================================*/
bool CComSmart::PostSend(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	m_nWriteBytes = 0 ;
	
	ResetEvent(m_WriteOver.hEvent);
	
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	
	DWORD nResult = WriteFile(m_handle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, &m_WriteOver);
	if( !m_nWriteBytes )
	{
		if( GetLastError() != ERROR_IO_PENDING )
		{
			sprintf(m_szErrorText,"�򴮿�д���ݴ���[%ld]!", GetLastError());
			if( !ReConnect() ) return false;
			else return true;
		}
		else
		{
			if( WaitForSingleObject(m_WriteOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"�򴮿�д���ݴ���,��ʱ[%ld]!", GetLastError());
				return false;
			}
			
			m_nWriteBytes = 0 ;
			if( !GetOverlappedResult(m_handle, &m_WriteOver, &m_nWriteBytes, TRUE) )
			{
				DWORD dwLastError = GetLastError() ;
				if( dwLastError != ERROR_IO_INCOMPLETE )
				{
					sprintf(m_szErrorText,"�򴮿�д���ݴ���,��ʱ[%ld]!", GetLastError());
					return false;
				}
			}
		}
	}	
	return true;
}


/*=================================================================
* Function ID :  PostRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE �ɹ�  FALSE ʧ��
* Description :  �ӷ���˽�������
* Notice	  :  pszBuffer ������յ�����   nBuffersize ���������� 
*			  :	 nTimeOut �ȴ�ʱ��
*					
*=================================================================*/
bool CComSmart::PostRecv(char *pszBuffer, int nBufferSize, long nTimeOut)
{
		
	m_ReadOver.Offset     = 0 ;
	m_ReadOver.OffsetHigh = 0 ;	
	m_nReadBytes		  = 0 ;		
	ResetEvent(m_ReadOver.hEvent);	
	if( !WaitRecv(nTimeOut) ) return false;
	DWORD nResult = ReadFile(m_handle, pszBuffer, (DWORD)nBufferSize, &m_nReadBytes, &m_ReadOver);
	if( !nResult )
	{		
		if( GetLastError() != WSA_IO_PENDING )
		{
			sprintf(m_szErrorText,"�������ݴ���[%ld]!", WSAGetLastError());
			return false;
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"�������ݴ���[%ld]!", WSAGetLastError());
				return false;				
			}			
			m_nReadBytes = 0 ;
			if( !GetOverlappedResult(m_handle, &m_ReadOver, &m_nReadBytes, TRUE) )
			{
				DWORD nLastError = GetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{					
					sprintf(m_szErrorText,"�ȴ��������ݴ���[%ld]!", nLastError);
					return false;
				}
			}
		}
	}	

	//add by dengjun 20060905		
	int nTry=0,ret=0;
	unsigned long mnReadBytes=0;
	//�����ݻ�δ������ʱ,�������
	if( m_nReadBytes < (DWORD)(7+(BYTE)pszBuffer[3]) ) 
	{	
		while( true )
		{	
			if( nTry>=100 ) 
			{
				sprintf(m_szErrorText,"�������ݳ�ʱ[%ld]!", WSAGetLastError());
				return false;
			}
			Sleep(5);			
			if( ReadFile(m_handle, pszBuffer+m_nReadBytes, (DWORD)nBufferSize, &mnReadBytes, &m_ReadOver) <=0 )			
			{
				Sleep(5);
				nTry++;				
				mnReadBytes=0;
				continue;
			}
			if( mnReadBytes>0) m_nReadBytes+=mnReadBytes;		
			mnReadBytes=0;
			if( m_nReadBytes >= (DWORD)(7+(BYTE)pszBuffer[3]) ) 
			{
				m_nReadBytes = (DWORD)(7+(BYTE)pszBuffer[3]);
				return true; //�յ����������ݰ�
			}
			nTry++;			
		}
	}	
	m_nReadBytes = (DWORD)(7+(BYTE)pszBuffer[3]);
    return true;
}


/*=================================================================
* Function ID :  WaitRecv
* Input       :  int WaitTime
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE �ɹ�  FALSE ʧ��
* Description :  ��WaitTimeʱ����,�ȴ�COM�˿��Ƿ�������
* Notice	  :  
*			  :	 WaitTime �ȴ�ʱ��
*					
*=================================================================*/
bool CComSmart::WaitRecv(int WaitTime)
{
#if 0
	struct timeval TimeOutVal;
	fd_set readfds;	
	int    nResult=0;	
	
	WaitTime=350;
	memset(&TimeOutVal,0x00,sizeof TimeOutVal);
	TimeOutVal.tv_sec =WaitTime/1000;
	TimeOutVal.tv_usec=WaitTime%1000;	
	FD_ZERO(&readfds);
	FD_SET((int)m_handle,&readfds);
	
	if( (nResult=select(((int)m_handle)+1,&readfds,NULL,NULL,&TimeOutVal))<1 )
	{
		if( nResult == 0 )
		{			
			sprintf(m_szErrorText,"�ն��豸[ %08X ]��ʱδ��Ӧ!",m_Data.HexToInt((BYTE*)m_regno,4));			
		}
		else
		{
			sprintf(m_szErrorText,"�ȴ���������ʱ����select!");						
		}		
		m_pDialog->AddString(m_szErrorText);
		return false;		
	}
	return true;		
#else
	return true;
#endif

}


/*=================================================================
* Function ID :  ReConnect
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  �������ӷ���
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::ReConnect()
{	
	Close();	
	if( !Open() )
	{
		sprintf(m_szErrorText,"�������ӷ���ʧ��[%s]",m_IpPar.cIPAddress);
		return false;
	}
	sprintf(m_szErrorText,"�������ӷ���ɹ�[%s]!!",m_IpPar.cIPAddress);
	m_pDialog->AddString(m_szErrorText);
	return true;
}



bool CComSmart::RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut)
{
	return true;
}


















