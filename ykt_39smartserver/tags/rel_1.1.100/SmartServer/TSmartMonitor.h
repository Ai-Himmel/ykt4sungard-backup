// TSmartMonitor.h: interface for the TSmartMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTMONITOR_H__BD48BF20_CFA5_4F47_A208_599035E33A52__INCLUDED_)
#define AFX_TSMARTMONITOR_H__BD48BF20_CFA5_4F47_A208_599035E33A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TSmartServer ;

//************************************************************************************
//*名称: TSmartMonitor  
//*功能: 服务器监控线程类
//************************************************************************************
class TSmartMonitor : public TThread
{
protected:
	TSmartServer  *m_pServer;

protected:
	void Run();

public:
	TSmartMonitor();
	virtual ~TSmartMonitor();

	void Initialized(TSmartServer *pServer);
};

#endif // !defined(AFX_TSMARTMONITOR_H__BD48BF20_CFA5_4F47_A208_599035E33A52__INCLUDED_)
