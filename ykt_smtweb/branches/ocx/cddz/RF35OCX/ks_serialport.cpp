#include "ks_serialport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

KS_SerialPort::KS_SerialPort(int portno,int baud)
:portno_(portno),baud_(baud),com_handle_(INVALID_HANDLE_VALUE)
{
}

KS_SerialPort::~KS_SerialPort()
{
	close();
}
int KS_SerialPort::open()
{
	char tmp[20];
	if(com_handle_ != INVALID_HANDLE_VALUE)
		return 0;

	sprintf(tmp,"COM%d",portno_);
	com_handle_=CreateFile(tmp,//COM1口
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //重叠方式
		NULL);
	if(com_handle_==INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	SetupComm(com_handle_,100,100); //输入缓冲区和输出缓冲区的大小都是100

	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。


	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(com_handle_,&TimeOuts); //设置超时

	DCB dcb;
	GetCommState(com_handle_,&dcb);
	dcb.BaudRate=baud_; //波特率为9600
	dcb.ByteSize=8; //每个字节有8位
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=ONESTOPBIT; //两个停止位
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;

	SetCommState(com_handle_,&dcb);

	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout        = MAXDWORD; 
	timeouts.ReadTotalTimeoutMultiplier    = 0;
	timeouts.ReadTotalTimeoutConstant    = 0;
	timeouts.WriteTotalTimeoutMultiplier    = 0;
	timeouts.WriteTotalTimeoutConstant    = 0;

	if (!SetCommTimeouts(com_handle_, &timeouts))
	{
		return -1;
	}

	PurgeComm(com_handle_,PURGE_TXCLEAR|PURGE_RXCLEAR);
	return 0;
}

void KS_SerialPort::close()
{
	if(com_handle_ != INVALID_HANDLE_VALUE)
	{
		CloseHandle(com_handle_);
		com_handle_ = INVALID_HANDLE_VALUE;
	}
}

int KS_SerialPort::do_read(unsigned char *buf,size_t maxlen,size_t timeout,OVERLAPPED &m_ov)
{
	BOOL  bSuccess;
	DWORD result = 0,
		readbytes   = 0, // num read bytes
		mask   = 0,
		recved; // a 32-bit variable that receives a mask 
	DWORD dwMaxWait;
	// Specify here the event to be enabled

	recved = 0;
	dwMaxWait = timeout * 1000;

	bSuccess = ReadFile(com_handle_, // handle of file to read 
		buf,  // address of buffer that receives data 
		maxlen,    // number of bytes to read 
		&readbytes,  // address of number of bytes read 
		&m_ov); // address of structure for data 

	bSuccess = SetCommMask(com_handle_, EV_RXCHAR);

	if ( ! bSuccess )
	{
		// Handle the error.
		return(-1);
	}


	// WaitForSingleObject

	bSuccess = WaitCommEvent(com_handle_, &mask, &m_ov);
	if ( ! bSuccess )
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
			result = WaitForSingleObject(m_ov.hEvent, dwMaxWait);  //wait dwMaxWait
			// milli seconds before returning
			if ( result == WAIT_OBJECT_0)
			{
				bSuccess = GetOverlappedResult(com_handle_, &m_ov, &readbytes, TRUE);
				if ( bSuccess )
				{
					return readbytes;
				}
				
			}

		}
	}
	return(-1);
}

int KS_SerialPort::read(unsigned char *buf,size_t maxlen,size_t timeout)
{
	if(com_handle_ == INVALID_HANDLE_VALUE)
		return -1;
	BOOL  bSuccess;
	DWORD result = 0,
		readbytes   = 0, // num read bytes
		mask   = 0,
		recved; // a 32-bit variable that receives a mask 
	DWORD dwMaxWait;
	// indicating the type of event that occurred
	OVERLAPPED m_ov;
	memset(&m_ov,0,sizeof m_ov);

	

	if ( maxlen < 1 ) return(0);

	// create event for overlapped I/O

	m_ov.hEvent = CreateEvent(NULL,   // pointer to security attributes 
		TRUE,   // flag for manual-reset event 
		FALSE,  // flag for initial state 
		"");    // pointer to event-object name 

	if ( m_ov.hEvent == INVALID_HANDLE_VALUE )
	{
		// Handle the error
		return(-1);
	}
	recved = do_read(buf,maxlen,timeout,m_ov);
	CloseHandle(m_ov.hEvent);
	return recved;
}

int KS_SerialPort::write(const unsigned char *buf,size_t buflen,size_t timeout)
{
	if(com_handle_ == INVALID_HANDLE_VALUE)
		return -1;

	OVERLAPPED m_osWrite;
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);


	DWORD dwBytesWrite=buflen;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(com_handle_,&dwErrorFlags,&ComStat);

	bWriteStat=WriteFile(com_handle_,buf,dwBytesWrite,& dwBytesWrite,&m_osWrite);
	if(!bWriteStat)
	{
		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent,timeout*1000);
		}
	}
	return 0;

}