#include "YCTReaderInterface.h"
#include <Windows.h>
#include <assert.h>
#include "kscard.h"
#include <exception>

extern   CYCTReaderInterface m_Reader;

CComSmart::CComSmart()
{
	m_handle=NULL;
	m_bComStatus=false;
}
CComSmart::~CComSmart()
{
	//Close();
}

/*=================================================================
* Function ID :  ClearComm
* Input       :  DWORD dwMask
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  清除事件
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_handle, dwMask) )
	{

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
* Description :  设置事件
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_handle, dwMask) )
	{

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
* Description :  设置超时时间
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
* Description :  设置超时时间
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_handle, &dwMask) )
	{

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
* Description :  设置串口属性
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
	sprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);
	
	if( !BuildCommDCB(szDCB, &dcb) )
	{
		return false;		
	}	
	if( !SetCommState(m_handle, &dcb) )
	{
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
* Description :  得到串口状态
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::GetState(DCB *pDCB)
{
	if( !GetCommState(m_handle, pDCB) )
	{
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
* Description :  清除串口错误
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::ClearError()
{
	if( !PurgeComm(m_handle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
//		sprintf(m_szErrorText,"PurgeComm()出错[%ld]!", GetLastError());
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
* Description :  打开串口
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::Open(char *sCom, int nBaudRate)
{
	/*
	char  szFileName[MAX_PATH];	
	BYTE  str[60];
	
	memset(str,0x00,sizeof str);
	memset(szFileName,0x00,sizeof szFileName);

	m_handle = CreateFile(
		sCom, 
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		NULL,
		0);
	if( m_handle == INVALID_HANDLE_VALUE )
	{
		return false;
	}	
	if(!SetState(nBaudRate, 'N', 8, 1))	
	{
		Close();
		m_bComStatus=false;
		return false;
	}		
	g_nHandle=m_handle;	
	SetTimeOut(10, 0);	
	m_bComStatus=true;
	strcpy(m_sCom,sCom);
	return true;
	*/
	throw std::exception("illege call");
	return false;
}

/*=================================================================
* Function ID :  Close
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  关闭串口
* Notice	  :  
*			  :	 
*					
*=================================================================*/
void CComSmart::Close()
{
	/*
	if( m_handle != INVALID_HANDLE_VALUE )
	{
		ClearError();
		ClearCommBreak(m_handle);
		CloseHandle(m_handle);
		m_handle = INVALID_HANDLE_VALUE;
		g_nHandle=m_handle;
	}
	*/
	throw std::exception("illege call");
}


/*=================================================================
* Function ID :  PostSend
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  向服务端发送数据
* Notice	  :  pszBuffer 发送的数据   nBuffersize 发送的数据长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CComSmart::PostSend(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	assert(pszBuffer!=NULL);

	unsigned long m_nWriteBytes = 0 ;	
	
	DWORD nResult = WriteFile(m_handle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, NULL);
	if( !m_nWriteBytes) return false;	
	return true;
}


/*=================================================================
* Function ID :  PostRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  从服务端接收数据
* Notice	  :  pszBuffer 保存接收的数据   nBuffersize 缓冲区长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CComSmart::PostRecv(char *ppszBuffer, int nBufferSize, long nTimeOut)
{		
	assert(ppszBuffer!=NULL);
	char pszBuffer[1024];
	unsigned long nReadBytes=0;
	DWORD nResult=0;
	DWORD nStartTime=GetTickCount();
	
	memset(pszBuffer,0,sizeof pszBuffer);
	
	m_nRecvLen=0;
	while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut )
	{
		Sleep(1);	
		if( ReadFile(m_handle, pszBuffer+m_nRecvLen, (DWORD)nBufferSize, &nReadBytes, NULL) )
		{
			if( nReadBytes>0 ) m_nRecvLen+=nReadBytes;			
			if( m_nRecvLen>=2 ) break;
		}
	}
	if( m_nRecvLen<2 ) return false; //超时
	if( m_nRecvLen>=pszBuffer[1]+2 ) //数据已经收完
	{
		memcpy(ppszBuffer,pszBuffer,pszBuffer[1]+2);
		return true;
	}
	
	int nPack=0;	
	nPack=pszBuffer[1];
	nPack=nPack+2-m_nRecvLen;
	while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut )
	{
		Sleep(10);	
		if( ReadFile(m_handle, pszBuffer+m_nRecvLen, (DWORD)nBufferSize, &nReadBytes, NULL) )
		{
			if( nReadBytes>0 ) 
			{
				m_nRecvLen+=nReadBytes;			
				nPack-=nReadBytes;
			}
			if( nPack<=0 ) break;
		}
	}
	if( nPack>0 ) return false;
	memcpy(ppszBuffer,pszBuffer,pszBuffer[1]+2);
    return true;
}


//打开串口
bool __stdcall APP_CPU_Open(char *sCom, int nBaudRate)
{	 
	return m_Reader.CPU_Open( sCom,nBaudRate);
}

//关闭串口
void __stdcall APP_CPU_Close()
{
	m_Reader.CPU_Close();
}

//上电
bool __stdcall APP_CPU_PowerOn()
{
	return m_Reader.CPU_PowerOn();
}

//下电
bool __stdcall APP_CPU_PowerOff()
{
	return m_Reader.CPU_PowerOff();
}

//寻卡
bool __stdcall APP_CPU_RequestCard()
{
	return m_Reader.CPU_RequestCard();
}

//寻卡
bool __stdcall APP_CPU_SelectCard(char sType,char* sSerialNo)
{
	return m_Reader.CPU_SelectCard(sType,sSerialNo);
}

//CPU卡直通指令
int __stdcall APP_CPU_APDU_Cmd( unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen )
{
	return m_Reader.CPU_APDU_Cmd( sSendData, nSendDatalen, sRespData,nRespDatalen );
}

//下电
bool __stdcall APP_SAM_PowerOff()
{
	return m_Reader.SAM_PowerOff();
}

//上电
bool __stdcall APP_SAM_PowerOn()
{
	return m_Reader.SAM_PowerOn();
}

//SAM卡直通指令
int __stdcall APP_SAM_APDU_Cmd(int nSamSlot, unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen )
{
	return m_Reader.SAM_APDU_Cmd(nSamSlot,sSendData, nSendDatalen, sRespData,nRespDatalen );
}
//错误信息
char* __stdcall APP_CPU_GetErrorCode(char *sMsg)
{
	return m_Reader.CPU_GetErrorCode(sMsg);
}

unsigned char * __stdcall APP_AscToBcd(unsigned char* ascbuf, int ascbuf_len, unsigned char* bcdbuf)
{
	return m_Reader.AscToBcd(ascbuf,ascbuf_len,bcdbuf);
}

unsigned char * __stdcall APP_BcdToAsc(unsigned char* bcdbuf, int bcdbuf_len, unsigned char* ascbuf)
{
	return m_Reader.BcdToAsc(bcdbuf,bcdbuf_len,ascbuf);
}

char* __stdcall APP_trim(char* str)
{
	return m_Reader.trim(str);
}
