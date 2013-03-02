// ConnectPool.h: interface for the CConnectPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTPOOL_H__D06CFBFB_CE1F_4043_BFDA_EF44CB138B4F__INCLUDED_)
#define AFX_CONNECTPOOL_H__D06CFBFB_CE1F_4043_BFDA_EF44CB138B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Afxmt.h"
//***************************************************************************
//*类名: CConnectPool
//*功能: 中间层连接管理池
//***************************************************************************
class CConnectPool  
{
	//状态
	enum 
	{
		DRTP_CLOSE,
		DRTP_CONNECT,
		DRTP_ALLOC,
		DRTP_FREE
	};

	//连接Session
	struct CNode
	{
		HANDLE	         hHandle;
		long             nStatus;
		CCriticalSection hSection;
	};

private:
	CConnectPool(const CConnectPool& pool);
	CConnectPool& operator=(const CConnectPool& pool);

protected:
	//公用的连接管理
	CNode                   m_Node[128];
	char					m_szHost[80];
	int						m_nPort;
	int						m_nEncode;
    int                     m_nConnectNo; //当前连接的数量
	CCriticalSection        m_hSection;

	
public:
	CConnectPool();
	virtual ~CConnectPool();

	bool Initialized(long nConnect, char *pszHost, int nPort, int nEncode);

	void DestroyPool();
	bool ReConnect();
	bool ReConnect(HANDLE& hHandle);

	HANDLE& AllocEx(BOOL bMonitor=FALSE);
	HANDLE& Alloc(int nTime=2);
	void Free(HANDLE hHandle);

	//保留未用
	static CConnectPool& ConnectPool()
	{
		static CConnectPool pool;
		return pool;
	}
};

extern CConnectPool ConnectPool;
#endif // !defined(AFX_CONNECTPOOL_H__D06CFBFB_CE1F_4043_BFDA_EF44CB138B4F__INCLUDED_)
