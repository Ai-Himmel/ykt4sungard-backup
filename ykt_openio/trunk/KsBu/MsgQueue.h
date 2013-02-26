/********************************************************************
	created:	2007/10/08
	created:	8:10:2007   23:57
	filename: 	D:\proj\ksbass\testsmq\MsgQueue.h
	file path:	D:\proj\ksbass\testsmq
	file base:	MsgQueue
	file ext:	h
	author:		CHENYH
	
	purpose:	采用共享内存方式仿真的双向消息队列，用于两个本机进程间的消息交换
				
				每对消息队列需要的共享内存空间为：(9K+sizeof(int)*2)*100*2=1.8MBytes
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
   //int   tmp_ritem;  // 为了检查错误的地方（在LINUX的地方）


   char  *pMQFName;  // 本MQ组的命名，全机器唯一

	int	m_iID;
	char	*ptr0;		// Base ptr of SHM_MQ

	void	*s_ptr;
	void  *r_ptr;
	int   m_openmode; // MQ Open Mode
	int	m_chkusec;	// recv. check interval in us for usleep
	
   CBUSem s_sempid;  // 用于send方(生产者)的信号灯ID，WIN(用ReleaseSemaphore)，其他用+1调用sempop
   CBUSem r_sempid;  // 用于recv方(消费者)的信号灯ID，WIN(用WaitForSingleObject)，其他用-1调用sempop

public:
	void Exit();
	bool Open(int omode, int uscheck=1000);
	static int GetSize();
	void Init(char *baseptr, int iID, char *pname);
	int GetOpenMode();
	int GetMQID();
	bool IsOpened();

	// 函数名: Recv
	// 编程  : 陈永华 2007-10-9 10:59:46
	// 描述  : 从MQ中读取消息
	// 返回  : int >0: 成功接收的数据长度；-1:Error & Closed ; -10: nDesignedSize<0
	// 参数  : char *vptr [OUT]: 接收缓存，缓存长度不能小于MAXMSGQLEN (9216)
	// 参数  : int nDesignedSize [IN]: 期望接收长度
	// 参数  : int timeout [IN]: 等待时间，毫秒计
	// 参数  : int type=0 [IN]: 保留
	int Recv(char *vptr, int nDesignedSize, int timeout,int type=0);


	// 函数名: Send
	// 编程  : 陈永华 2007-10-9 11:11:49
	// 描述  : 向MQ发送消息
	// 返回  : int >=0: 成功发送；-1:Closed; -2: nDesignedSize过大(超过9216); 0: nDesignedSize=0 无效调用
	// 参数  : char *ptr [IN]: 待发送消息数据
	// 参数  : int nDesignedSize [IN]: 发送消息数据长度
	// 参数  : int type=0  [IN]: 保留
	int Send(char *ptr, int nDesignedSize,int type=0);


	// 函数名: Open
	// 编程  : 陈永华 2007-10-9 10:00:29
	// 描述  : 打开MQ，注意当omode为OM_OPEN模式下，应该有另外的进程以OM_CREATE打开了。
	//			因此，本MQ使用的时候，必须有另外的机制协调双方的执行次序。
	// 返回  : bool 打开是否成功
	// 参数  : const char *name [IN]: MQ的全局名称(len<200)，要以一个文件路径的方式定义且该文件存放路径必须已经创建并有写权限
	// 参数  : int omode [IN]: MQ打开方式：只能为OM_CREATE或OM_OPEN，注意当omode为OM_OPEN模式下，应该有另外的进程以OM_CREATE打开了。

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
