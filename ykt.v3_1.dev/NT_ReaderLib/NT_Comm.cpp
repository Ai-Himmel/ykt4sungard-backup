//#include "stdafx.h"
#include "NT_Comm.h"
#include <exception>

CComSmart::CComSmart() {
    m_handle=INVALID_HANDLE_VALUE;
    m_bComStatus=false;
}
CComSmart::~CComSmart() {
    Close();
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
bool CComSmart::ClearComm(DWORD dwMask) {
    if( !PurgeComm(m_handle, dwMask) ) {

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
bool CComSmart::SetEventMask(DWORD dwMask) {
    if( !SetCommMask(m_handle, dwMask) ) {

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
bool CComSmart::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut) {
    COMMTIMEOUTS   CommTimeOut;

    ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));

    CommTimeOut.ReadIntervalTimeout = 0;
    CommTimeOut.ReadTotalTimeoutConstant = dwReadTimeOut;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;

    CommTimeOut.WriteTotalTimeoutMultiplier = 0;
    CommTimeOut.WriteTotalTimeoutConstant = dwWriteTimeOut;

    if( !SetCommTimeouts(m_handle, &CommTimeOut) ) {

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
bool CComSmart::GetEventMask(DWORD& dwMask) {
    if( !GetCommMask(m_handle, &dwMask) ) {
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
bool CComSmart::SetState(int nBaud, char cParity, int nDataBit, int nStopBit) {
    TCHAR  szDCB[64];
    DCB    dcb;

    ZeroMemory(&dcb, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);
    sprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);

    if( !BuildCommDCB(szDCB, &dcb) ) {
        return false;
    }
    if( !SetCommState(m_handle, &dcb) ) {
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
bool CComSmart::GetState(DCB *pDCB) {
    if( !GetCommState(m_handle, pDCB) ) {
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
bool CComSmart::ClearError() {
    if( !PurgeComm(m_handle, PURGE_TXCLEAR|PURGE_RXCLEAR) ) {
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
bool CComSmart::Open(char *sCom, int nBaudRate) {
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
                   FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
                   0);
    if( m_handle == INVALID_HANDLE_VALUE ) {
        return false;
    }
    if(!SetState(nBaudRate, 'N', 8, 1)) {
        Close();
        m_bComStatus=false;
        return false;
    }
    m_bComStatus=true;
    strcpy(m_sCom,sCom);
    SetupComm(m_handle,4096,4096);
    SetTimeOut(3000, 0);

    SetCommMask(m_handle, EV_ERR);
    PurgeComm( m_handle, PURGE_TXABORT | PURGE_RXABORT |
               PURGE_TXCLEAR | PURGE_RXCLEAR );


    memset(&m_readOverlapped,0,sizeof m_readOverlapped);
    memset(&m_writeOverlapped,0,sizeof m_writeOverlapped);
    m_readOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    m_writeOverlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    return true;
}
//! 获得串口句炳
HANDLE CComSmart::GetHandle() {
    return m_handle;
}

bool CComSmart::IsOpen() {
    return m_handle!=INVALID_HANDLE_VALUE;
}
void CComSmart::Attach(HANDLE hComm) {
    Close();
    m_handle = hComm;
}
HANDLE CComSmart::Detach() {
    HANDLE hrVal = m_handle;
    m_handle = INVALID_HANDLE_VALUE;
    return hrVal;
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
void CComSmart::Close() {
    if( m_handle != INVALID_HANDLE_VALUE ) {
        ClearError();
        ClearCommBreak(m_handle);
        CloseHandle(m_handle);
        CloseHandle(m_readOverlapped.hEvent);
        CloseHandle(m_writeOverlapped.hEvent);
        m_handle = INVALID_HANDLE_VALUE;
    }
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
bool CComSmart::PostSend(unsigned char *pszBuffer, int nBufferSize, long nTimeOut) {

    BOOL ret;
    DWORD bytesWrite;
    ret = WriteFile(m_handle,pszBuffer,nBufferSize,&bytesWrite,&m_writeOverlapped);
    if(!ret) {
        if(GetLastError() != ERROR_IO_PENDING)
            return false;
    }
    ret = GetOverlappedResult(m_handle,&m_writeOverlapped,&bytesWrite,TRUE);
    if( nBufferSize != bytesWrite)
        return false;
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
bool CComSmart::PostRecv(unsigned char *ppszBuffer, int nBufferSize, long nTimeOut) {
    assert(ppszBuffer!=NULL);
    char pszBuffer[1024];
    int nReadBytes=0;
    DWORD nResult=0;
    DWORD nStartTime=GetTickCount();

    memset(pszBuffer,0,sizeof pszBuffer);

    m_nRecvLen=0;

    while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut && m_nRecvLen < nBufferSize) {
        nResult = InWaiting();
        if(nResult == 0) continue;
        nResult = min(nResult,nBufferSize-m_nRecvLen);
        if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes)) {
            if(nReadBytes>0) m_nRecvLen += nReadBytes;
            if(m_nRecvLen>=3) break;
        }
    }
    if(pszBuffer[0] != 0x02)
        return false;
    if( m_nRecvLen<3 ) return false; //超时
    int datalen=pszBuffer[1]*256+pszBuffer[2];
    if( m_nRecvLen>=3+datalen+2 ) { //数据已经收完
        memcpy(ppszBuffer,pszBuffer+1,datalen+2);
        return true;
    }
    if(datalen + 5 > nBufferSize)
        return false;

    int nPack=3+datalen+2-m_nRecvLen;
    while( (long)(GetTickCount()-nStartTime)<(long)nTimeOut ) {
        nResult = InWaiting();
        nResult = min(nResult,nBufferSize-m_nRecvLen);
        if(Read((unsigned char*)pszBuffer+m_nRecvLen,nResult,nReadBytes)) {
            if(nReadBytes>0) {
                m_nRecvLen += nReadBytes;
                nPack -= nReadBytes;
            }
            if(nPack<=0) break;
        }
    }
    if( nPack>0 ) return false;
    memcpy(ppszBuffer,pszBuffer+1,datalen+2);
    return true;
}
bool CComSmart::Read(unsigned char *buffer, int bufMaxSize,int &bufRecv) {
    ResetEvent(m_readOverlapped.hEvent);
    DWORD bytesRead,flags;
    BOOL ret;
    COMSTAT stat;

    ret = ReadFile(m_handle,buffer,bufMaxSize,&bytesRead,&m_readOverlapped);
    if(!ret) {
        if(GetLastError() != ERROR_IO_PENDING)
            return false;
    }

    GetOverlappedResult(m_handle,&m_readOverlapped,&bytesRead,TRUE);
    if(bytesRead == 0)
        return false;
    bufRecv = bytesRead;
    return true;
}

size_t CComSmart::InWaiting() {
    DWORD flags = 0;
    COMSTAT stat;
    memset(&stat,0,sizeof stat);
    if(!ClearCommError(m_handle,&flags,&stat)) {
        throw std::exception();
    }
    return stat.cbInQue;
}