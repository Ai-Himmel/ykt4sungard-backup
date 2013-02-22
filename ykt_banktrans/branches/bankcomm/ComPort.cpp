// ComPort.cpp : 实现文件
//

#include "stdafx.h"
#include "ComPort.h"
//#include <string>

//using namespace std;


namespace LsComm{

// CComPort

CComPort::CComPort()
: m_bIsOpen(false),m_dataParse()
{
	this->m_pfnOnReceiveData = NULL;
	this->m_pfnOnPrintData = NULL;
	this->m_pPort = NULL;
	this->m_pReadThread = NULL;
	::ZeroMemory(&this->m_WriteOverlapped,sizeof(this->m_WriteOverlapped));
    this->m_hWriteEvent = NULL;
	this->m_bIsOpen = false;	

	memset(m_log_path,0,sizeof(m_log_path));	
}

CComPort::~CComPort()
{	
	if(this->m_pPort)
	{
		if(this->m_pPort->IsOpen())
		{
		   this->Close(); 
		}
	}

	if(this->m_pPort)
	{
	   delete this->m_pPort; 
	   this->m_pPort = NULL;
	}
}


// CComPort 成员函数

// //当前串口是否打开
bool CComPort::IsOpen(void)
{
	return this->m_bIsOpen;
}

bool CComPort::Open(int nPort, DWORD dwBaud, Parity parity, BYTE DataBits, 
            StopBits stopbits,FlowControl fc)
{   
	//1.初始化日志文件
	sprintf(m_log_path, "%slogs\\", m_module_path);
	int ret = GetFileAttributes(m_log_path);
	if ( ret == INVALID_FILE_ATTRIBUTES )
	{
		if (!CreateDirectory(m_log_path, NULL))
			return false;
	}
	// 打开日志文件
	if (m_dataParse.m_logWriter.openlog(m_log_path))
		return false;

	//2.新建串口
	if(this->m_pPort)
		delete this->m_pPort; 
	this->m_pPort = new CSerialPort();
    this->m_bIsOpen = false;

    
	//3.转换参数,打开串口
	int index;
	index=parity-CComPort::EvenParity;
	CSerialPort::Parity spParity=(CSerialPort::Parity)(CSerialPort::EvenParity+index);
	index=stopbits-CComPort::OneStopBit;
	CSerialPort::StopBits spStopbits=(CSerialPort::StopBits)(CSerialPort::OneStopBit+index);
    index=fc-CComPort::NoFlowControl;
	CSerialPort::FlowControl spFC=(CSerialPort::FlowControl)(CSerialPort::NoFlowControl+index) ;
   
	try     
	{
		this->m_pPort->Open(nPort,dwBaud,spParity,DataBits,spStopbits,spFC,true); 
	}
	catch(CSerialException* pE)
	{
	   //AfxMessageBox(pE->GetErrorMessage());
		m_dataParse.m_logWriter.writelog("打开串口:com%d失败",nPort);
		pE->Delete();
	    return false;
	}

	//it is important!!
	COMMTIMEOUTS timeouts;
	this->m_pPort->GetTimeouts(timeouts);
    timeouts.ReadIntervalTimeout=500;
	//timeouts.WriteTotalTimeoutConstant = 1000;
	this->m_pPort->SetTimeouts(timeouts);

	//this->m_pPort->Purge(PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	this->m_pPort->Purge( PURGE_TXCLEAR | PURGE_RXCLEAR);
	this->m_pPort->Setup(4096,4096);      

	this->m_CurPortNum = nPort;
  	//4.创建关闭事件
	this->m_hCloseEvent = CreateEvent(NULL,true,false,NULL);
	if(this->m_hCloseEvent==NULL)
	{
	   return false;
	}
	//5.创建线程类
	this->m_pReadThread = new CReadComThread();
	this->m_pReadThread->BandSerialPort(this); 
	this->m_pReadThread->Create();
	this->m_pReadThread->Resume(); 

	this->m_hWriteEvent = ::CreateEvent(NULL,true,false,NULL);
    if(this->m_hCloseEvent==NULL)
		return false;
    this->m_WriteOverlapped.hEvent = this->m_hWriteEvent;
	
	//6.记录日志	
	m_dataParse.m_logWriter.writelog("打开串口:com%d成功",nPort);

	this->m_bIsOpen = true;
	return true;
}

void CComPort::Close()
{
	//1.串口
	if(this->m_pPort==NULL)
		return;
	if(!this->m_pPort->IsOpen())
		return;

	m_dataParse.m_logWriter.writelog("已删除串口:com%d",m_CurPortNum);
    //2.事件
	::SetEvent(this->m_hCloseEvent);//通知关闭系统
    Sleep(1000);
	//3.结束读线程
	try
	{
      this->m_pReadThread->Terminate();   
      delete this->m_pReadThread;
      this->m_pReadThread = NULL;
	}
	catch(char e[150])
	{
		::AfxMessageBox(e); 
	}
   
   //4.结束关闭线程
   ::CloseHandle(this->m_hCloseEvent); 
   this->m_pPort->Close();
   
   //5.结束写事件
   if(this->m_hWriteEvent)
   {
	   ::CloseHandle(this->m_hWriteEvent);
	   this->m_hWriteEvent = NULL;
   }
   //6.释放串口对象
	if(this->m_pPort)
	{
		delete this->m_pPort;
	    this->m_pPort = NULL;
	}
}

void CComPort::SetModulePath(char *path)
{
	this->m_module_path = path;
}
void CComPort::ReceiveData(void* pBuf,DWORD InBufferCount)
{
   if(this->m_pfnOnReceiveData)
		this->m_pfnOnReceiveData(this->m_pSender,pBuf,InBufferCount); 
}

void CComPort::SetReceiveFunc(FOnReceiveData pfnOnReceiveData,LPVOID pSender)
{
   this->m_pfnOnReceiveData = pfnOnReceiveData;
   this->m_pSender = pSender;
}

void CComPort::PrintData(void *pBuf,DWORD InBufferCount)
{
	if (this->m_pfnOnPrintData)
		this->m_pfnOnPrintData(this->m_pPrintSender,pBuf,InBufferCount);
}

void CComPort::SetPrintFunc(FOnReceiveData pfnOnPrintData,LPVOID pSender)
{
	this->m_pfnOnPrintData = pfnOnPrintData;
	this->m_pPrintSender = pSender;
}


DWORD CComPort::Output(void* pBuf,DWORD Count)
{   
    DWORD dwWriteBytes=0;
	
	this->m_pPort->Write(pBuf,Count,this->m_WriteOverlapped);
	if(WaitForSingleObject(this->m_WriteOverlapped.hEvent,INFINITE)==WAIT_OBJECT_0)
	{
		this->m_pPort->GetOverlappedResult(this->m_WriteOverlapped,dwWriteBytes,false);
	}
	
	return dwWriteBytes;
}


 CSerialPort* CComPort::GetSerialPort() 
{ 
	ASSERT(m_pPort);
	return m_pPort;
}
HANDLE CComPort::GetCloseHandle()
{ 
	ASSERT(this->m_hCloseEvent);
	return this->m_hCloseEvent;
}

//CReadComThread

CReadComThread::CReadComThread()
{
	this->m_hThread = NULL;
	this->m_pPort = NULL;
	this->IsClose =false;
	::ZeroMemory(&this->m_ReadOverlapped,sizeof(this->m_ReadOverlapped));
	pre_time = 0;
	memset(this->m_InputBuffer,0,2048); 
}

CReadComThread::~CReadComThread()
{
	this->m_hThread = NULL;
}


// CReadComThread 成员函数
bool CReadComThread::SetReadEvent(OVERLAPPED& overlapped)
{
 BeginSet:
	memset(this->m_InputBuffer,0,2048);
	if(this->m_pPort->GetSerialPort()->Read(this->m_InputBuffer,2048,overlapped,&this->m_InBufferCount))
	{
	   if(!this->HandleData())
		   return  false;
	   ::ResetEvent(this->m_ReadOverlapped.hEvent);  
	   goto BeginSet;
	}
    DWORD error=::GetLastError();
	if(error==ERROR_IO_PENDING)
	{ return true; }
	else
	{ return false; }

}

//int CReadComThread::s_num = 0;
bool CReadComThread::HandleData() //处理读取数据
{
   if(this->m_InBufferCount>0)
   {	
	   time_t now;	   
	   /*///////////////////* 报文01
	   if(s_num == 0)
	   {
		   char *pstr = "01127";
		   m_InBufferCount = 5;
		   memset(m_InputBuffer,0,sizeof(m_InputBuffer));
		   m_InputBuffer[0] = 0x02;
		   m_InputBuffer[1] = (int)(m_InBufferCount / 1000) << 4 | (int)(m_InBufferCount % 1000) / 100;
		   m_InputBuffer[2] = (int)((m_InBufferCount %100) / 10) << 4 |(int)((m_InBufferCount % 100) % 10);
		   memcpy(m_InputBuffer+3,pstr,5);
		   m_InputBuffer[m_InBufferCount+3] = ETX;
		   unsigned char lrc;
		   int i;
		   for(lrc=0,i=1; i<m_InBufferCount+4; i++)
			   lrc ^= m_InputBuffer[i];
		   m_InputBuffer[m_InBufferCount+4] = lrc;
		   m_InBufferCount += 5;
	   }
	   
	   ////////////////////////////////

	   //////////////报文03
	   if (s_num == 1)
	   {
		   char *pstr = "03127";
		   m_InBufferCount = 62;
		   m_InputBuffer[0] = 0x02;
		   m_InputBuffer[1] = (int)(m_InBufferCount / 1000) << 4 | (int)(m_InBufferCount % 1000) / 100;
		   m_InputBuffer[2] = (int)((m_InBufferCount %100) / 10) << 4 |(int)((m_InBufferCount % 100) % 10);
		   memcpy(m_InputBuffer+3,pstr,5); 
		   m_InputBuffer[m_InBufferCount+3] = ETX;
		   pstr = "13";
		   memcpy(m_InputBuffer+8,pstr,4);
		   pstr = "10000";
		   memcpy(m_InputBuffer+19,pstr,5);
		   pstr = "1111";
		   memcpy(m_InputBuffer+25,pstr,4);
		   pstr = "150";
		   memcpy(m_InputBuffer+31,pstr,3);
		   pstr = "22";
		   memcpy(m_InputBuffer+41,pstr,2);
		   pstr = "111111111111111111";
		   memcpy(m_InputBuffer+46,pstr,19);
		   unsigned char lrc;
		   int i;
		   for(lrc=0,i=1; i<m_InBufferCount+4; i++)
			   lrc ^= m_InputBuffer[i];
		   m_InputBuffer[m_InBufferCount+4] = lrc;
		   m_InBufferCount += 5;
	   }
		
	   /////////////////报文02
	   if (s_num == 2)
	   {
		   char *pstr = "0212700";
		   m_InBufferCount = 7;
		   m_InputBuffer[0] = 0x02;
		   m_InputBuffer[1] = (int)(m_InBufferCount / 1000) << 4 | (int)(m_InBufferCount % 1000) / 100;
		   m_InputBuffer[2] = (int)((m_InBufferCount %100) / 10) << 4 |(int)((m_InBufferCount % 100) % 10);
		   memcpy(m_InputBuffer+3,pstr,7); 
		   m_InputBuffer[m_InBufferCount+3] = ETX;
		   unsigned char lrc;
		   int i;
		   for(lrc=0,i=1; i<m_InBufferCount+4; i++)
			   lrc ^= m_InputBuffer[i];
		   m_InputBuffer[m_InBufferCount+4] = lrc;
		   m_InBufferCount += 5;
	   }
		*////////////////////
		
	   this->m_pPort->ReceiveData(this->m_InputBuffer,this->m_InBufferCount);   
/*
	   char str[256]="";
	   int j = 0;
	   memcpy(str,m_InputBuffer,m_InBufferCount);
	   for(int i=0,j=0;i<(int)m_InBufferCount;i++)
	   {
		   j += sprintf(str+j,"%.02X ",m_InputBuffer[i]);
	   }	  
	   if(j > 255)
		   str[255] = 0;
	   m_pPort->m_dataParse.m_logWriter.writelog(str);
//	   now = time(NULL);
//	   if(pre_time != 0 && (now - pre_time) > TIMEOUT)  //超时
//	   {
//		   goto L_RET1;
//	   }
*/
	  //解析收到的报文
	   int ret = m_pPort->m_dataParse.Recv((char*)m_InputBuffer,m_InBufferCount);
	   if( ret == -1)  //数据不正确
	   {
		   m_pPort->m_dataParse.m_logWriter.writelog("bad diagram");
		   goto L_RET1;
	   }
//	   if(ret == -2)   //记录本次时间
//	   {
//			pre_time = time(NULL);
//			return true;
//	   }
	   else
	   {
		   int bufLen;
		   if(m_pPort->m_dataParse.GetResponse() != 0)  ///与后台交互
			   goto L_RET1;

		   //组织发送报文
		   m_pPort->m_dataParse.Send(m_SendBuf,bufLen);
		   /*///////// 测试
		   string c;
		   byte a[256]="\0";
		   char b[4]="\0";
		   memcpy(a,m_SendBuf,bufLen);
		   for(int i=0;i<(int)bufLen;i++)
		   {
			   ::sprintf(b,"%2.2X",a[i]);
			   c+=b;
			   c+=" ";
		   }
		    m_pPort->m_dataParse.m_logWriter.writelog("发送[%s]",c.c_str());
		///////////////////////*/
		   //向串口发送数据
		   m_pPort->Output(m_SendBuf,bufLen);		
		   
		   //在界面上显示发送的字符
		   m_pPort->PrintData(m_SendBuf,bufLen);
	   }      
   }

L_RET1:
//	s_num++;
  // if(s_num >= 3)
	//   s_num = 0;
//	pre_time = 0;
	m_pPort->m_dataParse.Flush();
	return true;
}


bool CReadComThread::HandleReadEvent(OVERLAPPED& overlapped)
{
	if(this->m_pPort->GetSerialPort()->GetOverlappedResult(overlapped,this->m_InBufferCount,false))
	{
	   return this->HandleData();
	}

	DWORD dwError = ::GetLastError();
	if(dwError==ERROR_INVALID_HANDLE)
		return false;
	else
		return true;
}


void CReadComThread::Execute()
{
	DWORD dwMask=0;
	HANDLE WaitHandles[2]; //监听事件数组
	DWORD dwSignaledHandle;
	//DWORD dwStoredFlags = EV_ERR | EV_RLSD | EV_RING;
	DWORD dwStoredFlags = EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING |\
		EV_RLSD | EV_RXCHAR | EV_RXFLAG | EV_TXEMPTY ;

	WaitHandles[0] = this->m_pPort->GetCloseHandle();
	WaitHandles[1] = this->m_ReadOverlapped.hEvent;

	this->m_pPort->GetSerialPort()->SetMask(dwStoredFlags); 

	//设置读事件
	if(!SetReadEvent(this->m_ReadOverlapped))
		goto EndThread;

	//设置comEvent
	for(;;)
	{
		dwSignaledHandle=::WaitForMultipleObjects(2,WaitHandles,false,INFINITE);
		switch(dwSignaledHandle)
		{
		case WAIT_OBJECT_0:
			goto EndThread; 
			break;

		case WAIT_OBJECT_0+1:
			if(!this->HandleReadEvent(this->m_ReadOverlapped))
				goto EndThread;
			if(!this->SetReadEvent(this->m_ReadOverlapped))
				goto EndThread;
			break;

		default:
			//goto EndThread;
			break;
		}


	}

EndThread:
	this->m_pPort->GetSerialPort()->Purge(PURGE_RXABORT | PURGE_RXCLEAR);  
	::CloseHandle(this->m_ReadOverlapped.hEvent);

	return ;   

}


DWORD WINAPI ThreadFunc(LPVOID  lpParam ) 
{ 
    CReadComThread* pThread =(CReadComThread*)lpParam;
	ASSERT(pThread);
	pThread->m_IsTerminated = false;
    pThread->Execute(); 
	pThread->m_IsTerminated = true;
	return 0;
} 

void CReadComThread::Create()
{
    m_hThread = CreateThread( 
        NULL,                        // no security attributes 
        0,                           // use default stack size  
        ThreadFunc,                  // thread function 
        this,                // argument to thread function 
        CREATE_SUSPENDED,           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
	::SetThreadPriority(m_hThread,THREAD_PRIORITY_HIGHEST); 
    
}

void CReadComThread::Terminate()
{
   char szMsg[80];
   if (m_hThread == NULL) 
   {
      wsprintf( szMsg, "CreateThread failed." ); 
	  ::MessageBox(NULL,szMsg,"ok",0);
   }
   else 
   {
      if(!this->IsTerminated())
	  {
	     Sleep(1000);
	  }
	  if(!this->IsTerminated())
	  {
         Sleep(1000);
         //::TerminateThread(m_hThread,0);
	  }
      CloseHandle( m_hThread );
   }
}

void CReadComThread::Resume()
{
   ResumeThread(this->m_hThread); 
}

void CReadComThread::BandSerialPort(CComPort* pPort)
{
	ASSERT(pPort);
	this->m_pPort = pPort;
	//创建异步读取事件
     
	this->m_ReadOverlapped.hEvent =::CreateEvent(NULL,true,false,NULL);	
	ASSERT(this->m_ReadOverlapped.hEvent);  
	
}

DWORD CReadComThread::ReadInput(void* pBuf,DWORD Count,DWORD dwMilliseconds)
{
	DWORD dwRead=0;
	if(!this->m_pPort->GetSerialPort()->Read(pBuf,Count,this->m_ReadOverlapped,&dwRead))
	{
		if(WaitForSingleObject(this->m_ReadOverlapped.hEvent,dwMilliseconds)==WAIT_OBJECT_0)
		{
		    this->m_pPort->GetSerialPort()->GetOverlappedResult(this->m_ReadOverlapped,dwRead,false);
		}
	}

	return dwRead;   
   
}

}
