#ifndef _WF_GZDXC_H_
#define _WF_GZDXC_H_

#pragma  once
#include "KSWorkflow.h"
#include "bankreader.h"
#include "KSCardManager.h"
#include "AdvanstaCard.h"

/************************************************************************/
/* �������ͨ��ֵ                                                       */
/************************************************************************/
class CGZYCTTransWorkFlow : public CKSWorkflow
{
public:
	CGZYCTTransWorkFlow(CDialog *dlg);
	virtual ~CGZYCTTransWorkFlow(void);
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int DoSendRequest(CDRTPHelper *drtp);
};

/************************************************************************/
/* ����Ǯ��ת��                                                         */
/************************************************************************/
class CGZElecTransWorkFlow : public CKSWorkflow
{
public:
	CGZElecTransWorkFlow(CDialog *dlg);
	virtual ~CGZElecTransWorkFlow();
	virtual CString GetWorkflowID();
protected:
	virtual int DoWork();
	int DoSendRequest(CDRTPHelper *drtp);
};
#endif // _WF_GZDXC_H_