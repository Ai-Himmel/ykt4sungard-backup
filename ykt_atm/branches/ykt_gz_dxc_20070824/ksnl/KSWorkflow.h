#include "afxwin.h"
#ifndef _KSWORKFLOW_H_
#define _KSWORKFLOW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <map>
#include <vector>
#include "KSCardManager.h"
#include "DRTPHelper.h"
#include <math.h>

#define RET_WF_TIMEOUT -2
#define RET_WF_ERROR -1
#define RET_WF_EXIT_APP -3
#define RET_WF_SUCCESSED 0

/************************************************************************/
/* 工作流定义接口                                                       */
/************************************************************************/
class CKSWorkflowThread;
class CKSNLDlg;

class CKSWorkflow
{
private:
	friend class CKSWorkflowThread;
	bool m_isTerminated;
	bool m_stopKey;
	HANDLE m_mutex;
	DWORD m_lastKeyCode;
	CKSWorkflowThread* m_workThread;
	CDialog * m_mainDlg;
protected:
	virtual int DoWork()
	{
		return RET_WF_SUCCESSED;
	}
	CDialog * GetMainWnd()
	{
		return (CDialog*)AfxGetMainWnd();
		//return m_mainDlg;
	}
public:
	CString m_key;
	CString m_funcText;
	int m_posX;
	int m_posY;
	int m_menuid;
public:
	CKSWorkflow(CDialog * dlg);
	virtual ~CKSWorkflow(void);
	virtual CString GetWorkflowID() = 0;
	virtual int OnFormKeyDown(UINT nChar, UINT nFlags);
	bool IsTerminate()
	{
		return m_isTerminated;
	}
	inline void SetStopKey(bool bStop = true)
	{
		if(WaitForSingleObject(m_mutex,1000)== WAIT_TIMEOUT)
			return;
		ResetEvent(m_mutex);
		m_stopKey = bStop;
		m_lastKeyCode = -1;
		SetEvent(m_mutex);
	}
	inline bool IsStopKey()
	{
		if(WaitForSingleObject(m_mutex,1000) == WAIT_TIMEOUT)
			return false;
		return m_stopKey;
	}
	inline void SetKeyCode(DWORD key)
	{
		if(WaitForSingleObject(m_mutex,1000) == WAIT_TIMEOUT)
			return;
		ResetEvent(m_mutex);
		if(!m_stopKey)
			m_lastKeyCode = key;
		SetEvent(m_mutex);
	}
	DWORD GetLastKeyCode();
	int Work();
	int D2I(double value);
};

class CKSWorkflowThread : public CWinThread
{
	 DECLARE_DYNCREATE(CKSWorkflowThread)
private:
	int m_workResult;
public:
	CKSWorkflow * m_workflow;
	CKSWorkflowThread();
	virtual ~CKSWorkflowThread();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	
	inline int GetWorkResult()
	{
		return m_workResult;
	}
	DECLARE_MESSAGE_MAP()
};
/************************************************************************/
/* 工作流管理器                                                         */
/************************************************************************/
template <class Workflow,class WFIDKey = CString>
class CKSWorkflowManager
{
public:
	typedef Workflow *  WorkflowPtr;
	typedef std::map<WFIDKey,WorkflowPtr> workflow_map;
	typedef std::pair<WFIDKey,WorkflowPtr> workflow_map_pair;
private:
	workflow_map m_workflowMap;
public:
	CKSWorkflowManager()
	{
		m_workflowMap.clear();
	}
	~CKSWorkflowManager()
	{
	}
    /** 
     * 清除所有工作流
     * 
     */
	void Clear()
	{
		workflow_map::iterator iter;
		for (iter = m_workflowMap.begin();iter != m_workflowMap.end();++iter)
		{
			delete iter->second;
		}
		m_workflowMap.clear();
	}
    /** 
     * 增加工作流类
     * 
     * @param wf - 工作流类
     * 
     * @return - 返回自己实例的引用
     */
	CKSWorkflowManager& AddWorkflow(WorkflowPtr wf)
	{
		workflow_map_pair wfpair(wf->GetWorkflowID(),wf);
		m_workflowMap.insert(wfpair);
		return (*this);
	}
    /** 
     * 查找工作流
     * 
     * @param key - 工作流标志 
     * 
     * @return - 工作流类
     */
	WorkflowPtr FindWorkflow(WFIDKey key)
	{
		workflow_map::iterator iter;
		iter = m_workflowMap.find(key);
//		AfxMessageBox(key);
		if(m_workflowMap.end() == iter)
		{
			return NULL;
		}
		return iter->second;
	}
	
	std::vector<Workflow*> GetAllWorkflows()
	{
		std::vector<Workflow*> result;
		workflow_map::iterator iter;
		for (iter = m_workflowMap.begin();iter != m_workflowMap.end();++iter)
		{
			result.push_back(iter->second);
		}
		return result;
	}

};
/************************************************************************/
/* 补助领取工作流定义                                                   */
/************************************************************************/
class CKSSubsidyWorkFlow : public CKSWorkflow
{
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
	int DoSubsidy(CKSCardManager* manager,KS_CARD_INFO *cardinfo,
		const ST_PACK *rec);
public:
	CKSSubsidyWorkFlow(CDialog * dlg);
	virtual ~CKSSubsidyWorkFlow(void);
	virtual CString GetWorkflowID();
	virtual int OnFormKeyDown(UINT nChar, UINT nFlags);
};

/************************************************************************/
/* 返回工作流		                                                    */
/************************************************************************/
class CKSExitWorkFlow : public CKSWorkflow
{
protected:
	virtual int DoWork();
public:
	CKSExitWorkFlow(CDialog * dlg);
	virtual ~CKSExitWorkFlow(void);
	virtual CString GetWorkflowID();
	virtual int OnFormKeyDown(UINT nChar, UINT nFlags);
};
/************************************************************************/
/* 返回工作流		                                                    */
/************************************************************************/
//! 查询补贴信息工作流
/*!
 * \class CKSQuerySubsidyWorkflow
 * 查询补贴信息
 * \sa CKSWorkflow
 */
class CKSQuerySubsidyWorkflow : public CKSWorkflow
{
protected:
	virtual int DoWork();
public:
	CKSQuerySubsidyWorkflow(CDialog* dlg);
	virtual ~CKSQuerySubsidyWorkflow(void);
	virtual CString GetWorkflowID();
};

/************************************************************************/
/* 查询水量                                                             */
/************************************************************************/
class  CKSQueryWaterVolumnWorkFlow : public CKSWorkflow
{
public:
	CKSQueryWaterVolumnWorkFlow(CDialog *dlg);
	virtual ~CKSQueryWaterVolumnWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
private:
};

#endif // _KSWORKFLOW_H_


/************************************************************************/
/* 查询转帐明细                                                         */
/************************************************************************/
class CKSQueryTransferAccoutsWorkFlow : public CKSWorkflow
{
public:
	CKSQueryTransferAccoutsWorkFlow(CDialog *dlg);
	virtual ~CKSQueryTransferAccoutsWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
};

/************************************************************************/
/* 水控钱包转帐                                                         */
/************************************************************************/
class CKSWaterPacketTransferWorkFlow : public CKSWorkflow
{
public:
	CKSWaterPacketTransferWorkFlow(CDialog *dlg);
	virtual	~CKSWaterPacketTransferWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int DoTransferValue(CKSCardManager* manager, KS_CARD_INFO *cardinfo, const ST_PACK *rec);
	int DoTransferWater(CKSCardManager* manager, WATER_PACK_INFO *water);
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
	int ReadWaterCard(double *balance);
};

/************************************************************************/
/* 定点卡申请                                                           */
/************************************************************************/
class CKSInitCardWorkFlow : public CKSWorkflow
{
public:
	CKSInitCardWorkFlow(CDialog *dlg);
	~CKSInitCardWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
};

/************************************************************************/
/* 定点卡取消                                                           */
/************************************************************************/
class CKSCancelTermCardWorkFlow : public CKSWorkflow
{
public:
	CKSCancelTermCardWorkFlow(CDialog *dlg);
	~CKSCancelTermCardWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
};
/************************************************************************/
/* 电控转帐                                                             */
/************************************************************************/
class CKSElePacketTransferWorkFLow : public CKSWorkflow
{
public:
	CKSElePacketTransferWorkFLow(CDialog *dlg);
	~CKSElePacketTransferWorkFLow();
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
	int DoTransfer(CKSCardManager *manager, KS_CARD_INFO *cardinfo, const ST_PACK *rec);
};

/************************************************************************/
/* 查询电控转帐明细                                                     */
/************************************************************************/
class CKSQueryEleTransferAccoutsWorkFlow : public CKSWorkflow
{
public:
	CKSQueryEleTransferAccoutsWorkFlow(CDialog *dlg);
	virtual ~CKSQueryEleTransferAccoutsWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
};

/************************************************************************/
/* 查询网络收费                                                         */
/************************************************************************/
class CKQueryNetChargeWorkFlow : public CKSWorkflow
{
public:
	CKQueryNetChargeWorkFlow(CDialog *dlg);
	~CKQueryNetChargeWorkFlow();
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
};

/************************************************************************/
/* 网络收费                                                             */
/************************************************************************/
class CKNetChargeTransferWorkFlow : public CKSWorkflow
{
public:
	CKNetChargeTransferWorkFlow(CDialog *dlg);
	~CKNetChargeTransferWorkFlow();
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager *manager, KS_CARD_INFO *cardinfo);
	int DoTransfer(CKSCardManager *manager, KS_CARD_INFO *cardinfo, const ST_PACK *rec);
};

/************************************************************************/
/* 更新卡信息                                                           */
/************************************************************************/
//! 更新卡信息工作流
/*!
 * \class CKModifyCardInfoWorkflow
 * 更新卡信息
 * \sa CKSWorkflow
 */
class CKModifyCardInfoWorkflow : public CKSWorkflow
{
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
	int DoModifyCardInfo(CKSCardManager* manager,
						 KS_CARD_INFO *cardinfo, 
						 const ST_PACK *rec, 
						 TPublishCard *pc);
public:
	CKModifyCardInfoWorkflow(CDialog *dlg);
	virtual ~CKModifyCardInfoWorkflow(void);
	virtual CString GetWorkflowID();
};

/************************************************************************/
/* 查询补写卡信息                                                       */
/************************************************************************/
class CKQueryMendCardWorkflow : public CKSWorkflow
{
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
public:
	CKQueryMendCardWorkflow(CDialog *dlg);
	virtual ~CKQueryMendCardWorkflow(void);
	virtual CString GetWorkflowID();
};

/************************************************************************/
/* 补写卡信息                                                           */
/************************************************************************/
class CKMendCardWorkflow : public CKSWorkflow
{
protected:
	virtual int DoWork();
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
	int DoMend(CKSCardManager *manager, KS_CARD_INFO *cardinfo, 
			   const ST_PACK *rec);
public:
	CKMendCardWorkflow(CDialog *dlg);
	virtual ~CKMendCardWorkflow(void);
	virtual CString GetWorkflowID();
};

/************************************************************************/
/* 手机充值																*/
/************************************************************************/
class CKSMobileTransWorkFlow : public CKSWorkflow
{
public:
	CKSMobileTransWorkFlow(CDialog *dlg);
	virtual	~CKSMobileTransWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int DoTransferValue(CKSCardManager* manager, KS_CARD_INFO *cardinfo, const ST_PACK *rec);
	int ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo);
};
