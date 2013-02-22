/*************************************************************************************************
*                        
*        ģ������:���̴߳���ͨѶ��(MultiThread Com class)        
*        ������(author): liu_sir    
*        ��������(date): 2003.4.20 -4.30
*        �޸���ǰ      : 2004.6.01 -6.14       
*        ��ǰ�汾(Version) :v1.2 
*        ��Ҫ��˵��(Main class):
*             CComPort ������  �ھۺ�һ��CSerialPort�����ڴ��ڵĲ���
*                      ����ģʽ˵��(Receive Mode):*   	          
*		                 .AutoReceiveBySignal,   //�ź��Զ�����
*                        
*                     �Ƽ�ʹ��:1��3
*		     CReadComThread ���ڶ��߳���  ��CComPort�����������в���
*       
*
***************************************************************************************************/
#pragma once
//���պ���
#ifndef COMPORT_H
#define COMPORT_H

typedef void (* FOnReceiveData)(LPVOID,void*,DWORD);

#include "serialport.h"
#include "DataParse.h"
#include "time.h"

// CComPort ����Ŀ��
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


	  //1.��,�رմ��ں���
	bool Open(int nPort,DWORD dwBaud = 9600, Parity parity = NoParity, BYTE DataBits = 8, 
		  StopBits stopbits = OneStopBit, FlowControl fc = NoFlowControl);
    void Close();

    //2.���ý��պ���
	void SetReceiveFunc(FOnReceiveData pfnOnReceiveData,LPVOID pSender);
	void SetPrintFunc(FOnReceiveData pfnPrintData,LPVOID pSender);
	void SetModulePath(char *path);

	//3.��ȡ�������
	int GetCurPortNum() { return this->m_CurPortNum;  }
	CSerialPort* GetSerialPort(); 
	HANDLE GetCloseHandle();


    //4.(�߳���)֪ͨ���մ�����     
	void ReceiveData(void* pBuf,DWORD InBufferCount);//�̵߳��õĽ��պ���
	void PrintData(void *pBuf,DWORD InBufferCount);
	DWORD Output(void* pBuf,DWORD Count);

protected:
	CSerialPort* m_pPort;                           //�ں�������
	CReadComThread* m_pReadThread;                  //�������߳� 

	LPVOID m_pSender;                               //����ĸ�����ָ��
	LPVOID m_pPrintSender;
	int m_CurPortNum;                               //��ǰ���ں� 
    FOnReceiveData m_pfnOnReceiveData;              //�����źź���
	FOnReceiveData m_pfnOnPrintData;

	HANDLE         m_hWriteEvent;                    //д�¼�
	OVERLAPPED     m_WriteOverlapped;                //д�ص��ṹ

private:
    HANDLE m_hCloseEvent; //E: A event handle to close thread  //Chinese:�����߳��¼�
	char *m_module_path;
	char m_log_path[MAX_PATH];

public:
	// //��ǰ�����Ƿ��
	bool IsOpen(void);	
	
	DataParse	m_dataParse;
protected:
	// ��ǰ�����Ƿ��
	bool m_bIsOpen;
};

//DWORD WINAPI ThreadFunc(LPVOID  lpParam ); //�̵߳��ú��� 

class CReadComThread
{
public:
    /*1.������ϵ������
	*/
	CReadComThread();
    virtual ~CReadComThread();          
    
	/* 2.����,����,��λ 
	*/
    void Create();                         //�����߳�
    void Terminate();                      //�����߳�
    void Resume();                         //��λ 
	bool IsTerminated()	{return this->m_IsTerminated; }
     
	/*3.�󶨴���,�첽��ȡ
	*/
	void BandSerialPort(CComPort* pPort);  //�󶨴���
	DWORD ReadInput(void* pBuf,DWORD Count,DWORD dwMilliseconds);//�첽��ȡ����

	friend DWORD WINAPI ThreadFunc(LPVOID  lpParam ); 
protected:
	DWORD dwThreadId;//�̺߳�  
    bool IsClose;
    /*4.�����첽��ȡ�¼�,�첽�ж��¼��Լ������¼�
	*/
	bool SetReadEvent(OVERLAPPED& overlapped);//�����������¼�
	bool HandleReadEvent(OVERLAPPED& overlapped);//������¼�
    bool HandleData(); //�����ȡ����

    void Execute(void);                    //�߳�ִ��
   
private:
	HANDLE m_hThread;           //�߳̾��
	CComPort* m_pPort;          //��������ָ��
	
    byte  m_InputBuffer[2048];  //���ջ�����
//	byte  m_pBuffer[2048];            //ʵ�ʵ��ڴ� 
	char  m_SendBuf[2048];
	DWORD m_InBufferCount;      //���ո��� 

	OVERLAPPED m_ReadOverlapped;     //��ȡ�ص��ṹ
    
	bool m_IsTerminated;            //�Ƿ�����߳� 
	time_t pre_time;
//	static int s_num ;
};

}

#endif