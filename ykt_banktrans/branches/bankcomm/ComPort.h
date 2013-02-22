/*************************************************************************************************
*                        
*        模块名称:多线程串口通讯类(MultiThread Com class)        
*        编制人(author): liu_sir    
*        创建日期(date): 2003.4.20 -4.30
*        修改日前      : 2004.6.01 -6.14       
*        当前版本(Version) :v1.2 
*        主要类说明(Main class):
*             CComPort 串口类  内聚合一个CSerialPort类用于串口的操作
*                      接收模式说明(Receive Mode):*   	          
*		                 .AutoReceiveBySignal,   //信号自动接收
*                        
*                     推荐使用:1或3
*		     CReadComThread 串口读线程类  和CComPort关联起来进行操作
*       
*
***************************************************************************************************/
#pragma once
//接收函数
#ifndef COMPORT_H
#define COMPORT_H

typedef void (* FOnReceiveData)(LPVOID,void*,DWORD);

#include "serialport.h"
#include "DataParse.h"
#include "time.h"

// CComPort 命令目标
namespace LsComm{

class CReadComThread;

class CComPort 
{
public:
	enum FlowControl
	{
		NoFlowControl,
		CtsRtsFlowControl,
		CtsDtrFlowControl,
		DsrRtsFlowControl,
		DsrDtrFlowControl,
		XonXoffFlowControl
	};

	enum Parity
	{    
		EvenParity,
		MarkParity,
		NoParity,
		OddParity,
		SpaceParity
	};

	enum StopBits
	{
		OneStopBit,
		OnePointFiveStopBits,
		TwoStopBits
	};

	CComPort();
	virtual ~CComPort();


	  //1.打开,关闭串口函数
	bool Open(int nPort,DWORD dwBaud = 9600, Parity parity = NoParity, BYTE DataBits = 8, 
		  StopBits stopbits = OneStopBit, FlowControl fc = NoFlowControl);
    void Close();

    //2.设置接收函数
	void SetReceiveFunc(FOnReceiveData pfnOnReceiveData,LPVOID pSender);
	void SetPrintFunc(FOnReceiveData pfnPrintData,LPVOID pSender);
	void SetModulePath(char *path);

	//3.获取自身参数
	int GetCurPortNum() { return this->m_CurPortNum;  }
	CSerialPort* GetSerialPort(); 
	HANDLE GetCloseHandle();


    //4.(线程类)通知接收处理函数     
	void ReceiveData(void* pBuf,DWORD InBufferCount);//线程调用的接收函数
	void PrintData(void *pBuf,DWORD InBufferCount);
	DWORD Output(void* pBuf,DWORD Count);

protected:
	CSerialPort* m_pPort;                           //内含串口类
	CReadComThread* m_pReadThread;                  //读串口线程 

	LPVOID m_pSender;                               //保存的父窗体指针
	LPVOID m_pPrintSender;
	int m_CurPortNum;                               //当前串口号 
    FOnReceiveData m_pfnOnReceiveData;              //接收信号函数
	FOnReceiveData m_pfnOnPrintData;

	HANDLE         m_hWriteEvent;                    //写事件
	OVERLAPPED     m_WriteOverlapped;                //写重叠结构

private:
    HANDLE m_hCloseEvent; //E: A event handle to close thread  //Chinese:结束线程事件
	char *m_module_path;
	char m_log_path[MAX_PATH];

public:
	// //当前串口是否打开
	bool IsOpen(void);	
	
	DataParse	m_dataParse;
protected:
	// 当前串口是否打开
	bool m_bIsOpen;
};

//DWORD WINAPI ThreadFunc(LPVOID  lpParam ); //线程调用函数 

class CReadComThread
{
public:
    /*1.构造与系构函数
	*/
	CReadComThread();
    virtual ~CReadComThread();          
    
	/* 2.创建,结束,复位 
	*/
    void Create();                         //创建线程
    void Terminate();                      //结束线程
    void Resume();                         //复位 
	bool IsTerminated()	{return this->m_IsTerminated; }
     
	/*3.绑定串口,异步读取
	*/
	void BandSerialPort(CComPort* pPort);  //绑定串口
	DWORD ReadInput(void* pBuf,DWORD Count,DWORD dwMilliseconds);//异步读取输入

	friend DWORD WINAPI ThreadFunc(LPVOID  lpParam ); 
protected:
	DWORD dwThreadId;//线程号  
    bool IsClose;
    /*4.设置异步读取事件,异步中断事件以及处理事件
	*/
	bool SetReadEvent(OVERLAPPED& overlapped);//设置启动读事件
	bool HandleReadEvent(OVERLAPPED& overlapped);//处理读事件
    bool HandleData(); //处理读取数据

    void Execute(void);                    //线程执行
   
private:
	HANDLE m_hThread;           //线程句柄
	CComPort* m_pPort;          //关联串口指针
	
    byte  m_InputBuffer[2048];  //接收缓冲区
//	byte  m_pBuffer[2048];            //实际的内存 
	char  m_SendBuf[2048];
	DWORD m_InBufferCount;      //接收个数 

	OVERLAPPED m_ReadOverlapped;     //读取重叠结构
    
	bool m_IsTerminated;            //是否结束线程 
	time_t pre_time;
//	static int s_num ;
};

}

#endif