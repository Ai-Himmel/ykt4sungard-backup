// ConnectPool.cpp: implementation of the CConnectPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"
#include "ConnectPool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CConnectPool ConnectPool;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConnectPool::CConnectPool()
{
	strcpy(m_szHost, "");
	m_nPort = 0 ;
	m_nEncode = 0 ;
	for(int i=0;i<128;i++)
	{
		m_Node[i].hHandle = NULL;
		m_Node[i].nStatus = DRTP_CLOSE;
	}
}

CConnectPool::~CConnectPool()
{
	DestroyPool();
}

//*********************************************************************
//*名称: bool CConnectPool::Initialized(long nConnect, char *pszHost, int nPort, int nEncode)
//*功能: 初始化监控连接. 
//*入口: pszHost  ---  主机地址IP
//*      nPort    ---  SOCKET端口
//*      nEncode  ---  EndCode码
//*      nConnect ---  连接数量
//*返回: 成功与否
//*日期: 2004-10-15  zhangwei
//*********************************************************************
bool CConnectPool::Initialized(long nConnect, char *pszHost, int nPort, int nEncode)
{
	strcpy(m_szHost, pszHost);
	m_nPort = nPort;
	m_nEncode = nEncode;
	m_nConnectNo = nConnect;
	printf("------开始准备与金仕达通信平台建立连接------\n");
	for(int i=0; i<nConnect; i++)
	{
		printf("三九前置程序与金仕达通信平台建立第%d个连接------n",i+1);
		m_Node[i].hHandle = DRTPConnect(pszHost, (WORD)nPort, (WORD)nEncode);
		if( m_Node[i].hHandle == NULL )
		{
			printf("失败!\n");
			printf("前置程序无法正常运行,请联系 系统管理员!!!!!\n");
			DestroyPool();
			return false;
		}
		else
		{
			printf("成功!\n");
			m_Node[i].nStatus = DRTP_FREE ;
		}
	}

	return true;
}



//*********************************************************************
//*名称: void CConnectPool::DestroyPool()
//*功能: 销毁连接池
//*入口: 无
//*返回: 无
//*日期: 2004-10-15  zhangwei
//*说明: 退出时操作
//*********************************************************************
void CConnectPool::DestroyPool()
{
	//for(;;)
	//{
		//printf("尝试断开与金仕达通信平台的连接-------\n");
		m_hSection.Lock();
		for(int i=0;i<m_nConnectNo;i++)
		{
			//m_Node[i].hSection.Lock();
			if(m_Node[i].hHandle  !=  NULL )
					DRTPClose(m_Node[i].hHandle);
			//m_Node[i].hSection.Unlock();
		}
		m_hSection.Unlock();
	//}
}

//*********************************************************************
//*名称: bool CConnectPool::ReConnect(HANDLE& hHandle)
//*功能: 对指定的连接重连
//*入口: 无
//*返回: 成功与否
//*日期: 2004-10-15  zhangwei
//*说明: 当网络断开时重连, 但是重连后没有重新签到!!!
//*********************************************************************
bool CConnectPool::ReConnect(HANDLE& hHandle)
{
	if( hHandle == NULL )
		return false;

	HANDLE hOld = hHandle;

	//重连
	hHandle = DRTPConnect(m_szHost, (WORD)m_nPort, (WORD)m_nEncode);
	
	if( hHandle == NULL )
	{
		hHandle = hOld;
		WriteLog("自动重连接失败!!!!.\n");
		return false;
	}
	else
	{
		//关闭旧句柄
		if( hOld != NULL )
		{
			DRTPClose(hOld);
		}
	}

	return true;
}

//*********************************************************************
//*名称: bool CConnectPool::ReConnect()
//*功能: 断开重连
//*入口: 无
//*返回: 成功与否
//*日期: 2004-10-15  zhangwei
//*说明: 当网络断开时重连, 但是重连后没有重新签到!!!
//*********************************************************************
bool CConnectPool::ReConnect()
{
	printf("----三九前置尝试重连金仕达通信平台----\n");
	m_hSection.Lock();
	for(int i=0; i<m_nConnectNo; i++)
	{
		//m_Node[i].hSection.Lock();
		if( m_Node[i].hHandle != NULL )
		{
				DRTPClose(m_Node[i].hHandle);
				m_Node[i].hHandle = NULL ;
		
				m_Node[i].hHandle = DRTPConnect(m_szHost, (WORD)m_nPort, (WORD)m_nEncode);
				if( m_Node[i].hHandle == NULL )
				{
					m_Node[i].nStatus = DRTP_CLOSE;
					printf("尝试重连失败!\n");
					//m_Node[i].hSection.Unlock();
					m_hSection.Unlock();
					return false;
				}
			}
	}
	m_hSection.Unlock();

	return true;
}

//*********************************************************************
//*名称: HANDLE CConnectPool::Alloc(int nTime)
//*功能: 从连接管理池中分配一个连接
//*入口: nTime -- 失败重试次数
//*返回: 连接句柄
//*日期: 2004-10-15  zhangwei
//*说明: 无
//*********************************************************************
HANDLE CConnectPool::Alloc(int nTime)
{
	m_hSection.Lock();
	for(int i=0;i<m_nConnectNo;i++)
	{
		//m_Node[i].hSection.Lock();
		if(m_Node[i].hHandle != NULL && m_Node[i].nStatus == DRTP_FREE)
		{
			m_Node[i].nStatus = DRTP_ALLOC;
			//m_Node[i].hSection.Unlock();
			m_hSection.Unlock();
			return m_Node[i].hHandle;
		}
		//m_Node[i].hSection.Lock();

	}
	m_hSection.Unlock();
	return NULL;
}

//*********************************************************************
//*名称: HANDLE CConnectPool::AllocEx(BOOL bMonitor)
//*功能: 从连接管理池中分配一个连接
//*入口: bMonitor -- TRUE: 是从监控连接中分配，FALSE:从公共连接中分配
//*返回: 连接句柄
//*日期: 2004-10-15  zhangwei
//*说明: 无
//*********************************************************************
HANDLE CConnectPool::AllocEx(BOOL bMonitor)
{
	return NULL;
}

//*********************************************************************
//*名称: void CConnectPool::Free(HANDLE hHandle)
//*功能: 释放一个连接到连接管理池
//*入口: hHandle -- 连接句柄
//*返回: 无
//*日期: 2004-10-15  zhangwei
//*说明: 无
//*********************************************************************
void CConnectPool::Free(HANDLE hHandle)
{
	m_hSection.Lock();
	for(int i=0; i< 128; i++)
	{
		//m_Node[i].hSection.Lock();
		if( m_Node[i].hHandle != NULL && m_Node[i].hHandle == hHandle )
		{
			m_Node[i].nStatus  = DRTP_FREE;
			//m_Node[i].hSection.Unlock();
			m_hSection.Unlock();
			return;
		}
		//m_Node[i].hSection.Unlock();
	}
	m_hSection.Unlock();

}