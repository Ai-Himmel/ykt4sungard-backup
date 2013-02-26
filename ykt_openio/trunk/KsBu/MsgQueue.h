/********************************************************************
	created:	2007/10/08
	created:	8:10:2007   23:57
	filename: 	D:\proj\ksbass\testsmq\MsgQueue.h
	file path:	D:\proj\ksbass\testsmq
	file base:	MsgQueue
	file ext:	h
	author:		CHENYH
	
	purpose:	���ù����ڴ淽ʽ�����˫����Ϣ���У����������������̼����Ϣ����
				
				ÿ����Ϣ������Ҫ�Ĺ����ڴ�ռ�Ϊ��(9K+sizeof(int)*2)*100*2=1.8MBytes
*********************************************************************/
// MsgQueue.h: interface for the CMsgQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGQUEUE_H__7806C645_D9C6_42BB_821C_79F4936668B2__INCLUDED_)
#define AFX_MSGQUEUE_H__7806C645_D9C6_42BB_821C_79F4936668B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SHM_MQ		// declare MQ with Share Memory

#include "BUShm.h"
#include "BUSem.h"

#ifndef MAXMSGQLEN
#define MAXMSGQLEN	9214 //8192+extra head   9K-sizeof(unsigned short)
#endif

#ifdef OM_INVALID
#error Confused 'MsgQueue.h' included!
#endif
#define OM_INVALID	-1
#define OM_CREATE		0
#define OM_OPEN		1

#ifndef MAX_QUEUES
#define MAX_QUEUES	10	// max containing queues
#endif

class CMsgQueue  
{
private:
   //int   tmp_ritem;  // Ϊ�˼�����ĵط�����LINUX�ĵط���


   char  *pMQFName;  // ��MQ���������ȫ����Ψһ

	int	m_iID;
	char	*ptr0;		// Base ptr of SHM_MQ

	void	*s_ptr;
	void  *r_ptr;
	int   m_openmode; // MQ Open Mode
	int	m_chkusec;	// recv. check interval in us for usleep
	
   CBUSem s_sempid;  // ����send��(������)���źŵ�ID��WIN(��ReleaseSemaphore)��������+1����sempop
   CBUSem r_sempid;  // ����recv��(������)���źŵ�ID��WIN(��WaitForSingleObject)��������-1����sempop

public:
	void Exit();
	bool Open(int omode, int uscheck=1000);
	static int GetSize();
	void Init(char *baseptr, int iID, char *pname);
	int GetOpenMode();
	int GetMQID();
	bool IsOpened();

	// ������: Recv
	// ���  : ������ 2007-10-9 10:59:46
	// ����  : ��MQ�ж�ȡ��Ϣ
	// ����  : int >0: �ɹ����յ����ݳ��ȣ�-1:Error & Closed ; -10: nDesignedSize<0
	// ����  : char *vptr [OUT]: ���ջ��棬���泤�Ȳ���С��MAXMSGQLEN (9216)
	// ����  : int nDesignedSize [IN]: �������ճ���
	// ����  : int timeout [IN]: �ȴ�ʱ�䣬�����
	// ����  : int type=0 [IN]: ����
	int Recv(char *vptr, int nDesignedSize, int timeout,int type=0);


	// ������: Send
	// ���  : ������ 2007-10-9 11:11:49
	// ����  : ��MQ������Ϣ
	// ����  : int >=0: �ɹ����ͣ�-1:Closed; -2: nDesignedSize����(����9216); 0: nDesignedSize=0 ��Ч����
	// ����  : char *ptr [IN]: ��������Ϣ����
	// ����  : int nDesignedSize [IN]: ������Ϣ���ݳ���
	// ����  : int type=0  [IN]: ����
	int Send(char *ptr, int nDesignedSize,int type=0);


	// ������: Open
	// ���  : ������ 2007-10-9 10:00:29
	// ����  : ��MQ��ע�⵱omodeΪOM_OPENģʽ�£�Ӧ��������Ľ�����OM_CREATE���ˡ�
	//			��ˣ���MQʹ�õ�ʱ�򣬱���������Ļ���Э��˫����ִ�д���
	// ����  : bool ���Ƿ�ɹ�
	// ����  : const char *name [IN]: MQ��ȫ������(len<200)��Ҫ��һ���ļ�·���ķ�ʽ�����Ҹ��ļ����·�������Ѿ���������дȨ��
	// ����  : int omode [IN]: MQ�򿪷�ʽ��ֻ��ΪOM_CREATE��OM_OPEN��ע�⵱omodeΪOM_OPENģʽ�£�Ӧ��������Ľ�����OM_CREATE���ˡ�

	void Close();
	CMsgQueue();
	virtual ~CMsgQueue();

	void myusleep(unsigned int useconds);

private:
	static int GetSHMSize();
};

class CMQFactory  
{
private:
   CBUShm m_bushm;
   int m_nMQs;
   CMsgQueue *m_pMQ;
   char m_Name[200];
   
public:
   CMsgQueue * GetMQ(int mqid);
   void Destroy();
   bool New(const char *name, int count);
   CMQFactory();
   virtual ~CMQFactory();
   
};


#endif // !defined(AFX_MSGQUEUE_H__7806C645_D9C6_42BB_821C_79F4936668B2__INCLUDED_)
