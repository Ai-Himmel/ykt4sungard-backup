#include "stdafx.h"
#include "ksnl.h"
#include <exception>
#include ".\ksworkflow.h"
#include "KSInputDialog.h"
#include "KSNLDlg.h"
#include "KSCardManager.h"
#include "DRTPHelper.h"

#define KS_BANK_TX_CODE 900077

using namespace std;
//////////////////////////////////////////////////////////////////////////
// global function
CString ParseDateString(const CString & ordDate)
{
	if(ordDate.GetLength() < 8)
	{
		return "";
	}
	CString result;
	result.Format("%s-%s-%s",ordDate.Mid(0,4),ordDate.Mid(4,2),ordDate.Mid(6,2));
	return result;
}
CString ParseTimeString(const CString & ordTime)
{
	if(ordTime.GetLength() < 6)
	{
		return "";
	}
	CString result;
	result.Format("%s:%s:%s",ordTime.Mid(0,2),ordTime.Mid(2,2),ordTime.Mid(4,2));
	return result;
}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE (CKSWorkflowThread,CWinThread)
CKSWorkflowThread::CKSWorkflowThread()
:CWinThread(),m_workflow(NULL)
{
	this->m_bAutoDelete = TRUE;
}
CKSWorkflowThread::~CKSWorkflowThread()
{
	
}
int CKSWorkflowThread::Run()
{
	m_workResult = m_workflow->DoWork();
	m_workflow->m_isTerminated = TRUE;
	return CWinThread::Run();
}
BOOL CKSWorkflowThread::InitInstance()
{
	return TRUE;
}
int CKSWorkflowThread::ExitInstance()
{
	return 0;
}
BEGIN_MESSAGE_MAP(CKSWorkflowThread, CWinThread)
	//{{AFX_MSG_MAP(CNewCardThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CKSWorkflow
CKSWorkflow::CKSWorkflow(CDialog * dlg):
m_key(""),m_funcText(""),m_posX(0),m_posY(0),m_isTerminated(FALSE)
,m_stopKey(FALSE),m_lastKeyCode(-1),m_workThread(NULL),m_mainDlg(dlg),m_mutex(NULL)
{
	/*
	int s = rand();
	CString mutexStr;
	mutexStr.Format("ks-workflow-mutex-%s-%.06d",(LPCTSTR)m_key,s);
	m_mutex = CreateEvent(NULL,TRUE,TRUE,mutexStr);
	if(!m_mutex || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		throw exception("����������ʧ��");
	}
	*/
}

CKSWorkflow::~CKSWorkflow(void)
{
	if(m_mutex)
	{
		CloseHandle(m_mutex);
		m_mutex = FALSE;
	}
	if(m_workThread)
	{
		m_workThread->ExitInstance();
		delete m_workThread;
	}
}

int CKSWorkflow::OnFormKeyDown(UINT nChar, UINT nFlags)
{
	SetKeyCode(nChar);
	return 1;
}

int CKSWorkflow::Work()
{
	m_isTerminated = FALSE;
	int ret = 0;
	/*
	//m_workThread = new CKSWorkflowThread();
	m_workThread = (CKSWorkflowThread*)AfxBeginThread(RUNTIME_CLASS(CKSWorkflowThread)
		,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
	m_workThread->m_workflow = this;
	m_workThread->ResumeThread();
	*/
	ret = DoWork();
	m_isTerminated = TRUE;
	return ret;
}
DWORD CKSWorkflow::GetLastKeyCode()
{
	if(WaitForSingleObject(m_mutex,1000) == WAIT_TIMEOUT)
		return -1;
	UINT flag;
	flag = PM_REMOVE |PM_NOYIELD;
	MSG msg;
	m_lastKeyCode = -1;
	
	if(::PeekMessage(&msg,AfxGetMainWnd()->GetSafeHwnd(),WM_KEYFIRST,WM_KEYLAST,flag))
	{
		if(WM_KEYDOWN == msg.message || WM_SYSKEYDOWN == msg.message)
		{
			if(!m_stopKey)
			{
				m_lastKeyCode = msg.wParam;
			}
		}
	}
	return m_lastKeyCode;
}

int CKSWorkflow::D2I(double value)
{
	double smaller = floor(value);
	double bigger = ceil(value);
	return (int)(((bigger - value) > (value - smaller)) ? smaller : bigger);
} 

//////////////////////////////////////////////////////////////////////////
// CKSWorkflowManager

// ������ı�д
//////////////////////////////////////////////////////////////////////////
// CKSSubsidyWorkflow
CKSSubsidyWorkFlow::CKSSubsidyWorkFlow(CDialog * dlg):
	CKSWorkflow(dlg)
{
	// do nothing
	m_key = "subsidy";
}
CKSSubsidyWorkFlow::~CKSSubsidyWorkFlow()
{
	// 
}
int CKSSubsidyWorkFlow::DoWork()
{
	
	CString passwd;
	CString tipMsg("");
	CDRTPHelper * drtp = NULL;
	CDRTPHelper * response = NULL;
	KS_CARD_INFO cardinfo;
	int ret;
	int iCount = 0;
	int hasMore = 0;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();  // Get a active main window of the application
	memset(&cardinfo,0,sizeof cardinfo);
	SetStopKey(false);

	
	dlg->ShowTipMessage("���У԰��...",0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	
	if(card.OpenCOM()!=0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	
	SetStopKey(false);
	ret = ReadCard(&card,&cardinfo);                    
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg());
		}
		goto L_END;                                    // ����ʧ��
	}
	dlg->SetLimtText(1);
	if(dlg->InputPassword("������У԰������",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״����У��벻Ҫ�ƶ�У԰��",1);
	if(card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�",5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
	while(true)
	{
		hasMore = 0;
		SetStopKey(true);
		drtp->Reset();
		if(drtp->Connect())
		{
			dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
			goto L_END;
		}
		drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
		drtp->AddField(F_SCLOSE_EMP,"240104");				// ������
		drtp->AddField(F_LVOL0,cardinfo.cardid);			// ���׿���
		drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// ����
		drtp->AddField(F_DAMT0,cardinfo.balance);			//�뿨ֵ
		drtp->AddField(F_LVOL1,cardinfo.tx_cnt);			//�ۼƽ��״���
		drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// ϵͳ���					//�豸�ɣ�
		drtp->AddField(F_SCUST_NO,"system");				//����Ա
		dlg->ShowTipMessage("���ڴ����ף��벻Ҫ�ƶ�У԰��...",1);
		SetStopKey(false);
		if(drtp->SendRequest(3000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		if(drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK * pData = drtp->GetNextRecord();
			tipMsg.Format("%s ��� %.02f Ԫ��\n����д�����벻Ҫ�ƶ�У԰��..."
						  ,pData->semail,pData->damt1);
			hasMore = pData->lvol2;
			dlg->ShowTipMessage(tipMsg,0);
			ret = DoSubsidy(&card,&cardinfo,pData);                       /////////////////////
			if(RET_WF_ERROR == ret)
			{
				SetStopKey(true);
				response->Reset();
				response->Connect();
				response->SetRequestHeader(900077,1);
				response->AddField(F_SCLOSE_EMP,"240107");
				int serialno = atoi(pData->sserial1);
				response->AddField(F_LVOL1,serialno);
				if(response->SendRequest(3000))
				{
					dlg->ShowTipMessage(response->GetReturnMsg().c_str(),3);
				}
				else
				{
					SetStopKey(false);
					dlg->ClearMessageLine();
					tipMsg = "д��ʧ���뵽�������Ĵ���!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}
			else if(RET_WF_TIMEOUT == ret)
			{
				goto L_END;
			}
			cardinfo.balance = pData->damt2;
			cardinfo.tx_cnt++;
			dlg->ClearMessageLine();
			if(hasMore)
			{
				tipMsg.Format("���� %s ",pData->semail);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("��� %0.2f Ԫ����ȡ",pData->damt1);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("�����в���δ��ȡ");
				dlg->AddMessageLine(tipMsg,dlg->GetMaxLineNo()+2);
				tipMsg.Format("��[ȷ��]������ȡ����[�˳�]����");
				dlg->AddMessageLine(tipMsg,dlg->GetMaxLineNo()+1,-6);
				// dlg->DisplayMessage(10);
				if(dlg->Confirm(10) != IDOK)
				{
					ret = RET_WF_TIMEOUT;
					goto L_END;
				}
			}
			else
			{
				tipMsg.Format("���� %s ",pData->semail);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("��� %0.2f Ԫ����ȡ",pData->damt1);
				dlg->AddMessageLine(tipMsg);
				dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
				dlg->DisplayMessage(3);
				break;
			}
		}
		else
		{
			//û�в���
			dlg->ClearMessageLine();
			ret = drtp->GetReturnCode();
			if(ret != ERR_NOT_LOGIN)
				ret = RET_WF_TIMEOUT;
			dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			
			goto L_END;
		}
	}
	dlg->ShowTipMessage("������ɣ�",2);
	ret = RET_WF_SUCCESSED;
L_END:
	if(drtp)
		delete drtp;
	if(response)
		delete response;
	card.CloseCOM();
	//CDRTPHelper::UninitDrtp();
	SetStopKey(false);
	return ret;
}

CString CKSSubsidyWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKSSubsidyWorkFlow::OnFormKeyDown(UINT nChar, UINT nFlags)
{
	if(IsTerminate())
	{
		return 0;
	}
	return CKSWorkflow::OnFormKeyDown(nChar,nFlags);
}

int CKSSubsidyWorkFlow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
{
	int ret = manager->ReadCardInfo(cardinfo,
		CKSCardManager::ciCardId|CKSCardManager::ciBalance,20);
	if(ret)
	{
		ret = manager->GetErrNo();
		if(ERR_USER_CANCEL == ret)
		{
			return RET_WF_TIMEOUT;
		}
		return RET_WF_ERROR;
	}
	return RET_WF_SUCCESSED;
}

int CKSSubsidyWorkFlow::DoSubsidy(CKSCardManager* manager,
								  KS_CARD_INFO *cardinfo,const ST_PACK *rec)
{
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while(--retries>=0)
	{
		// ��⿨
		if(manager->TestCardExists(5))
		{
			continue;
		}
		// д��
		ret = manager->SetMoney(cardinfo->cardid,(int)(rec->damt2 * 100));
		if(!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if(manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("д��ʧ�ܣ������·�У԰����");
		dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// CKSExitWorkFlow
CKSExitWorkFlow::CKSExitWorkFlow(CDialog *dlg)
:CKSWorkflow(dlg)
{
	m_key = "exit";
}
CKSExitWorkFlow::~CKSExitWorkFlow()
{
	// 
}
int CKSExitWorkFlow::DoWork()
{
	return RET_WF_EXIT_APP;
}
CString CKSExitWorkFlow::GetWorkflowID()
{
	return m_key;
}
int CKSExitWorkFlow::OnFormKeyDown(UINT nChar, UINT nFlags)
{
	return 0;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// CKSQuerySubsidyWorkflow
CKSQuerySubsidyWorkflow::CKSQuerySubsidyWorkflow(CDialog * dlg)
:CKSWorkflow(dlg)
{
	//
	m_key = _T("qrysubsidy");
}
CKSQuerySubsidyWorkflow::~CKSQuerySubsidyWorkflow()
{
	// 
}
CString CKSQuerySubsidyWorkflow::GetWorkflowID()
{
	return m_key;
}
int CKSQuerySubsidyWorkflow::DoWork()
{
	CDRTPHelper * drtp = NULL;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardinfo;
	int ret = RET_WF_ERROR;
	int recCount;
	CString passwd;
	CString cardidstr;
	memset(&cardinfo,0,sizeof(cardinfo));

	dlg->ClearAllColumns();
	dlg->AddListColumns("ժҪ",200);
	dlg->AddListColumns("���׿���",70);
	dlg->AddListColumns("��ȡ����",90);
	dlg->AddListColumns("��ȡʱ��",70);
	dlg->AddListColumns("���",75);
	dlg->AddListColumns("״̬",80);
	

	dlg->ShowTipMessage("���У԰��...",0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);

	if(card.OpenCOM()!=0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardinfo,CKSCardManager::ciCardId,5);
	if(ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;
	}
	dlg->SetLimtText(1);
	if(dlg->InputPassword("������У԰������",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����,��ȴ�...",1);
	cardidstr.Format("%d",cardinfo.cardid);//33396);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240103");	// ������
	drtp->AddField(F_SSERIAL0,(LPSTR)(LPCTSTR)cardidstr);	// ���׿���
	drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// ����
	drtp->AddField(F_SORDER2,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// ϵͳ��� �豸�ɣ�
	drtp->AddField(F_SCUST_NO,"system");			//����Ա
	if(drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	if(!drtp->SendRequest(3000))
	{
		recCount = 0;
		while(drtp->HasMoreRecord())
		{
			ST_PACK * pData = drtp->GetNextRecord();
			CString money;
			money.Format("%.2fԪ",pData->damt0);
			CString status = (pData->sstatus1[0] == '2')? "δ��ȡ":"����ȡ";
			CString cardno;
			cardno.Format("%d",pData->lvol3);
			CString txdate = ParseDateString(pData->sdate1);
			CString txtime = ParseTimeString(pData->stime1);
			dlg->AddToListInfo(pData->semail,cardno,txdate,txtime,
				(LPCTSTR)money,(LPCTSTR)status);
			recCount++;
			// ֻ��ʾ10��
			if(recCount > 10) break;
		}
		if(recCount > 0)
			dlg->ShowListInfo(25);
		else
			dlg->ShowTipMessage("û�в�����ȡ�ļ�¼!");
		ret = RET_WF_SUCCESSED;
	}
	else
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
	}
	
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// CKSQueryWaterVolumnWorkflow (��ѯˮ��)
CKSQueryWaterVolumnWorkFlow::CKSQueryWaterVolumnWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = _T("qrywatervol");
}

CKSQueryWaterVolumnWorkFlow::~CKSQueryWaterVolumnWorkFlow()
{

}

CString CKSQueryWaterVolumnWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKSQueryWaterVolumnWorkFlow::DoWork()
{
	CDRTPHelper *drtp = NULL;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardinfo;
	WATER_PACK_INFO water;
	memset(&water, 0, sizeof(water));
	int ret = RET_WF_ERROR;
	int recCount = 0;
	CString cardidstr;
	CString waterRemain;
	memset(&cardinfo, 0, sizeof(cardinfo));

	dlg->ClearAllColumns();
	dlg->AddListColumns("ʣ��ˮ��", 70);
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR; 
	}
//	SetStopKey(false);
	ret = card.ReadCardInfo(&cardinfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;
	}
	ret = SMT_ReadWaterPackInfo(&water);
	if (ret)
	{
		dlg->ShowTipMessage("��ȡˮ��Ǯ����Ϣʧ��");
		goto L_END;
	}
	waterRemain.Format("ʣ��ˮ��: %d ��", water.remain);
	dlg->AddMessageLine(waterRemain);
	dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
	dlg->DisplayMessage(3);
	return RET_WF_SUCCESSED;
L_END:
	if (drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// CKSQueryTransferAccoutsWorkFlow (��ѯת����ϸ)
CKSQueryTransferAccoutsWorkFlow::CKSQueryTransferAccoutsWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = _T("qryTrfAct");
}

CKSQueryTransferAccoutsWorkFlow::~CKSQueryTransferAccoutsWorkFlow()
{

}

CString CKSQueryTransferAccoutsWorkFlow::GetWorkflowID()
{
	return m_key;
}

// ���ܱ��: 240201
// ��������: ��ѯת����ϸ
// ��������: ��ѯ�û���ʷ��ˮ��ϸ�����10��
// ��������: ������(sclose_emp), ���׿���(lvol0), ����(semp_pwd)
// �������: ��ˮ��ֵ��ˮ��(lvo10), �ͻ���(lvo11), ���׿���(lvo12)
//			 ��ˮ����(sdate0, 8�ַ�), ��ˮʱ��(stime0, 6�ַ�), ����ˮ��(lvol3)
int CKSQueryTransferAccoutsWorkFlow::DoWork()
{
	CDRTPHelper *drtp = NULL;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardInfo;
	int ret = RET_WF_ERROR;
	int retCount;
	CString passwd;
	CString cardidstr;
	memset(&cardInfo, 0, sizeof(cardInfo));

	dlg->ClearAllColumns();
	dlg->AddListColumns("��ˮ��ֵ��ˮ��", 120);
	dlg->AddListColumns("�ͻ���", 80);
	dlg->AddListColumns("���׿���", 70);
	dlg->AddListColumns("��ˮ����", 90);
	dlg->AddListColumns("��ˮʱ��", 70);
	dlg->AddListColumns("����ˮ��(��)", 120);

	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(), (LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);

	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("������У԰������", passwd, 10) != 0)
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, ��ȴ�", 1);
	cardidstr.Format("%d", cardInfo.cardid);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240201");
	drtp->AddField(F_LVOL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)passwd);
	drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	if (drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	else if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		goto L_END;
	}
	else
	{
		retCount = 0;
		while (drtp->HasMoreRecord())
		{
			ST_PACK *pData = drtp->GetNextRecord();
			CString cardWaterNo;                  // ��ˮ��ֵ��ˮ��
			cardWaterNo.Format("%d", pData->lvol0);
			CString userNo;						  // �ͻ���
			userNo.Format("%d", pData->lvol1);
			CString cardNo;					      // ���׿���
			cardNo.Format("%d", pData->lvol2);
			CString txtdate = ParseDateString(pData->sdate0);
			CString txtime = ParseTimeString(pData->stime0);
			CString waterVolumn;
			waterVolumn.Format("%d", D2I(pData->lvol3/1000));
			dlg->AddToListInfo(cardWaterNo, userNo, cardNo, txtdate, txtime, waterVolumn);
			retCount++;
			// ֻ��ʾ10������
			if (retCount > 10)
			{
				break;
			}
		}
		if (retCount > 0)
		{
			dlg->ShowListInfo(25);
		}
		else
		{
			dlg->ShowTipMessage("û��ת�ʵļ�¼!");
		}
		ret = RET_WF_SUCCESSED;
	}
	/*
	else
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		ret = RET_WF_TIMEOUT;
	}
	*/
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// CKSWaterPacketTransferWorkFlow (ˮ��Ǯ��ת��)
CKSWaterPacketTransferWorkFlow::CKSWaterPacketTransferWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = _T("waterpacketrf");
}

CKSWaterPacketTransferWorkFlow::~CKSWaterPacketTransferWorkFlow()
{

}

CString CKSWaterPacketTransferWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKSWaterPacketTransferWorkFlow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
{
	int ret = manager->ReadCardInfo(cardinfo,
		CKSCardManager::ciCardId | CKSCardManager::ciBalance, 20);
	if(ret)
	{
		ret = manager->GetErrNo();
		if(ERR_USER_CANCEL == ret)
		{
			return RET_WF_TIMEOUT;
		}
		return RET_WF_ERROR;
	}
	return RET_WF_SUCCESSED;
}

// ���ܱ��: 240202
// ��������: ˮ��Ǯ��ת��
// ��������: �û�ͨ��Ȧ����Ӵ�Ǯ���й�ˮ, Ȼ��д�뵽ˮ��Ǯ����
// ҵ���߼�: 1.	����û���״̬����鿨���
//			 2.	���û��ʻ��п۳���ˮ���
//           3.	���ɹ�ˮ������ˮ
//           4.	���ɹ�ˮ��ֵ��ˮ
//           5.	���ʧ����Ҫ���ɲ�д����ˮ������ع���
// ��ع���: ���д��ʧ�ܷ���ת��ʧ�ܽ���, ������240111
// ��������: ������(sclose_emp), ���׿���(lvol0), ����(semp_pwd), �����״���(lvol3)
//			 �뿨ֵ(damt0), ��ˮ��(lv0l1), �ն˺�(sname)������ʣ��ˮ��(lvol2)
// �������: ������ˮ��(lvo10), ��ˮ��ֵ��ˮ��(lvo11), ����ֵ(damt0)
//			 ˮ��(lvol2), ������Ϣ(vsmess)
int CKSWaterPacketTransferWorkFlow::DoWork()
{
	CString password;
/*	CString inputValue = _T("");*/
	CString waterVolumn;
	CString tipMsg;
	CDRTPHelper *drtp = NULL;
	CDRTPHelper *response = NULL;
	KS_CARD_INFO cardInfo;
	int ret;
	int iCount = 0;
	int hasMore = 0;
	double balance = 0;
	WATER_PACK_INFO water, tempWater;	
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardInfo, 0, sizeof(cardInfo));
	memset(&tempWater, 0, sizeof(tempWater));
	memset(&water, 0, sizeof(water));
	SetStopKey(false);
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	// ��ȡ����Ϣ
	ret = ReadCard(&card, &cardInfo);
//	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciBalance, 5);
	if (ret)
	{
		if (RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg());
		}
		goto L_END;
	}
	balance = cardInfo.balance;
	ret = SMT_ReadWaterPackInfo(&water);
	if (ret)
	{
		dlg->ShowTipMessage("��ȡˮ��Ǯ����Ϣʧ��");
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("������У԰������", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״����У� �벻Ҫ�ƶ�У԰��", 1);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(0);
	if (dlg->InputQuery("������ˮ�� ��λ:��", "", waterVolumn, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, �벻Ҫ�ƶ�У԰��", 1);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}	
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
	while (true)
	{
		hasMore = 0;
		SetStopKey(true);
		drtp->Reset();
		if (drtp->Connect())
		{
			dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
			goto L_END;
		}
		// ����drtp�������
		drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
		drtp->AddField(F_SCLOSE_EMP, "240202");
		drtp->AddField(F_LVOL0, cardInfo.cardid);
		drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
		drtp->AddField(F_LVOL3, cardInfo.tx_cnt);
		drtp->AddField(F_DAMT0, cardInfo.balance);
		drtp->AddField(F_LVOL1, (LPSTR)(LPCTSTR)waterVolumn);
		drtp->AddField(F_SNAME, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);
		drtp->AddField(F_LVOL2, water.remain);
		SetStopKey(false);
		// ��������
		if (drtp->SendRequest(3000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		// ��ȡ���ؼ�¼
		if (drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK *pData = drtp->GetNextRecord();
			tipMsg.Format("����д��, �벻Ҫ�ƶ�У԰��...", 1);
			dlg->ShowTipMessage(tipMsg, 0);
			// д��(��Ǯ���м�Ǯ), �����и�����ֵ
			ret = DoTransferValue(&card, &cardInfo, pData);				
			// ��Ǯ���пۿ������������, д��ʧ�ܷ�����Ϣ, ʧ�ܱ�־Ϊ0
			if (RET_WF_ERROR == ret)
			{
				// ��д��ˮ
				SetStopKey(true);
				response->Reset();
				response->Connect();
				response->SetRequestHeader(KS_BANK_TX_CODE, 1);
				response->AddField(F_SCLOSE_EMP, 240111);
				response->AddField(F_LVOL1, pData->lvol0);
				response->AddField(F_LVOL2, pData->lvol1);
				response->AddField(F_LVOL3, 0);
				if (response->SendRequest(3000))
				{
					dlg->ShowTipMessage(response->GetReturnMsg().c_str(), 3);
				}
				else
				{
					SetStopKey(false);
					dlg->ClearMessageLine();
					tipMsg = "д��ʧ���뵽�������Ĵ���!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}
			// ��ʱ
			if (RET_WF_TIMEOUT == ret)
			{
				goto L_END;
			}
			memset(&water, 0, sizeof(water));
			// ���滹����һ����СǮ����������ˮ���Ĳ���, ҲӦ���и�������Ϣ, ʧ�ܱ�־Ϊ1
			// ��ȡˮ��Ǯ��ʧ��, ����û�з�װ�������е�����
			if (SMT_ReadWaterPackInfo(&water) != 0)
			{
				tipMsg = "��ȡ��ʧ��";
				dlg->AddMessageLine(tipMsg);
				dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
				dlg->DisplayMessage(1);
				ret = RET_WF_ERROR;
				goto L_END;
			}
			water.remain = pData->lvol2;
			ret = DoTransferWater(&card, &water);
			if (RET_WF_ERROR == ret)
			{
				SetStopKey(true);
				response->Reset();
				response->Connect();
				response->SetRequestHeader(KS_BANK_TX_CODE, 1);
				response->AddField(F_SCLOSE_EMP, 240111);
				response->AddField(F_LVOL1, pData->lvol0);
				response->AddField(F_LVOL2, pData->lvol1);
				response->AddField(F_LVOL3, 1);
				if (response->SendRequest(3000))
				{
					dlg->ShowTipMessage(response->GetReturnMsg().c_str(), 3);
				}
				else
				{
					SetStopKey(false);
					dlg->ClearMessageLine();
					tipMsg = "д��ʧ���뵽�������Ĵ���!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}

			if (RET_WF_TIMEOUT == ret)
			{
				goto L_END;
			}
			// д���ɹ�
			SetStopKey(false);
			cardInfo.tx_cnt++;
			cardInfo.balance = pData->damt0;
			water.remain /= 1000;
			hasMore = pData->damt0;
			dlg->ClearMessageLine();
			tipMsg.Format("ת��ˮˮ��:%s�� ʣ��ˮ��:%d��\n ����%0.2fԪ ʣ��%0.2f", (LPSTR)(LPCSTR)waterVolumn, water.remain, (balance - cardInfo.balance), cardInfo.balance);
			dlg->ShowTipMessage(tipMsg);
			//dlg->AddMessageLine();
			//dlg->ShowTipMessage(pData->vsmess);
// 			tipMsg.Format("��[�˳�]����");
// 			dlg->AddMessageLine(tipMsg,dlg->GetMaxLineNo()+1,-6);
			dlg->DisplayMessage(10);
			break;
// 			if(dlg->Confirm(10) != IDOK)
// 			{
// 				ret = RET_WF_TIMEOUT;
// 				goto L_END;
// 			}
		}
		else
		{
			dlg->ClearMessageLine();
			ret = drtp->GetReturnCode();
			if (ret != ERR_NOT_LOGIN)
			{
				ret = RET_WF_TIMEOUT;
			}
			dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			goto L_END;
		}
	}// end while
	dlg->ShowTipMessage("�������!", 2);
	ret = RET_WF_SUCCESSED;
L_END:
	if(drtp)
		delete drtp;
	if(response)
		delete response;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

// ��Ǯ������
int CKSWaterPacketTransferWorkFlow::DoTransferValue(CKSCardManager* manager, KS_CARD_INFO *cardinfo, const ST_PACK *rec)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		if (manager->TestCardExists(5))
		{
			continue;
		}
		// д��
// 		CString cs;
/*		cs.Format("%d[%.2lf]", D2I(rec->damt0 * 100), rec->damt0);*/

		ret = manager->SetMoney(cardinfo->cardid, D2I(rec->damt0 * 100));
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("д��ʧ��, �����·�У԰��!");
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

// СǮ����ˮ
int CKSWaterPacketTransferWorkFlow::DoTransferWater(CKSCardManager* manager, WATER_PACK_INFO *water)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = SMT_WriteWaterPackInfo(water);
		if (!ret)
		{
			return	RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;	
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("д��ʧ��, �����·�У԰��!");
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

// ���ܱ��: 240203
// ��������: �������ɶ����ˮ�ؿ�
// ��������: �û�ͨ��Ȧ����Ӵ�Ǯ���й�ˮ, Ȼ��д�뵽ˮ��Ǯ����
// ҵ���߼�: 1.	�û���������
//			 2. �û�����ˮ���
//           3.	���̨������, ���Ϳ��Ķ���ˮ���
// ��������: ������(sclose_emp), ���׿���(lvol0), ����(semp_pwd), ˮ���(lvol1)

//////////////////////////////////////////////////////////////////////////
// ���ɶ��㿨
CKSInitCardWorkFlow::CKSInitCardWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = _T("InitCard");
}

CKSInitCardWorkFlow::~CKSInitCardWorkFlow()
{

}

CString CKSInitCardWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKSInitCardWorkFlow::DoWork()
{
	CDRTPHelper *drtp = NULL;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardInfo;
	WATER_PACK_INFO water, tempWater;
	CString inputWaterTermId;
	int ret = RET_WF_ERROR;
//	int retCount;
	CString password;
	memset(&cardInfo, 0, sizeof(cardInfo));
	memset(&water, 0, sizeof(water));
	memset(&tempWater, 0, sizeof(tempWater));
	SetStopKey(false);
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(), 
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;
	}
	// ����ǵ�һ��û�����ɶ��㿨�Ŀ�.
	if (SMT_ReadWaterPackInfo(&tempWater) == 0)
	{
		water.remain = tempWater.remain;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("������У԰����", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, �벻Ҫ�ƶ�У԰��", 1);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputQuery("������ˮ���", "", inputWaterTermId, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, �벻Ҫ�ƶ�У԰��", 1);
	SetStopKey(false);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	water.cardtype = WATER_FIXED_CARD;
	water.termid = atoi((LPCTSTR)inputWaterTermId);
	// �¼����һ�仰, ��д����ʣ����
	water.remain = tempWater.remain;
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240203");
	drtp->AddField(F_LVOL0, cardInfo.cardid);
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
	drtp->AddField(F_LVOL1, water.termid);
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	if (drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// �¼���ļ�ⷵ�ص�ֵ�Ƿ���ȷ
	if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		ret = RET_WF_ERROR;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	if (SMT_InitWaterInfo(&water) != 0)
	{
		dlg->ShowTipMessage("д���㿨ʧ��, �����²���");
		goto L_END;
	}
	dlg->ShowTipMessage("���㿨����ɹ�!", 2);
	ret = RET_WF_SUCCESSED;
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// ���㿨��ȡ��
CKSCancelTermCardWorkFlow::CKSCancelTermCardWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = _T("cancel");
}

CKSCancelTermCardWorkFlow::~CKSCancelTermCardWorkFlow()
{

}

CString CKSCancelTermCardWorkFlow::GetWorkflowID()
{
	return m_key;
}

// ���ܱ��: 240204
// ��������: ���㿨ȡ��
// ��������: ȡ������ˮ��İ�
// ��������: ���״���(sclose_emp, 240204), ���׿���(lvol0), ����(semp_pwd)
int CKSCancelTermCardWorkFlow::DoWork()
{
	CDRTPHelper *drtp = NULL;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	WATER_PACK_INFO water;
	KS_CARD_INFO cardInfo;
//	int retCount;
	CString password;
	int ret = RET_WF_ERROR;
	memset(&water, 0, sizeof(water));
	memset(&cardInfo, 0, sizeof(cardInfo));
	SetStopKey(false);
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(), 
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;		
	}
	
	if (SMT_ReadWaterPackInfo(&water) != 0)
	{
		dlg->ShowTipMessage("����ʧ��, �����²���!");
		goto L_END;
	}
	water.cardtype = WATER_COMMON_CARD;
	dlg->SetLimtText(1);
	if (dlg->InputPassword("����������", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, ��ȴ�...", 1);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240204");
	drtp->AddField(F_LVOL0, cardInfo.cardid);
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;		
	}
	if (drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// �¼���ļ�ⷵ�ص�ֵ�Ƿ���ȷ
	if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		ret = RET_WF_ERROR;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	if (SMT_WriteWaterPackInfo(&water) != 0)
	{
		dlg->ShowTipMessage("д���㿨ʧ��, �����²���");
		goto L_END;
	}
	dlg->ShowTipMessage("���㿨ȡ���ɹ�!", 2);	
	return RET_WF_SUCCESSED;
L_END:
	if (drtp)
		delete drtp;
	card.CloseCOM();
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// ���ת��
CKSElePacketTransferWorkFLow::CKSElePacketTransferWorkFLow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "ElePackTrf";
}

CKSElePacketTransferWorkFLow::~CKSElePacketTransferWorkFLow()
{
	//	
}

CString CKSElePacketTransferWorkFLow::GetWorkflowID()
{
	return m_key;
}

int CKSElePacketTransferWorkFLow::DoWork()
{
	CString password;
	CString tipMsg("");
	CString eleValue;
	CString mateRoomNo;
	char cMateRoom = NULL;
	CDRTPHelper *drtp = NULL;
	CDRTPHelper *response = NULL;      // ������ˮ
	KS_CARD_INFO cardinfo;
	int ret;
	int iCount = 0;
	int hasMore = 0;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));
	SetStopKey(false);	
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(), 
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = ReadCard(&card, &cardinfo);
	if (ret == RET_WF_ERROR)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;	
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("������У԰������", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("���״����У� �벻Ҫ�ƶ�У԰��", 1);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputQuery("�����������", "", mateRoomNo, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// �ж�������Ƿ���Ϲ淶
	cMateRoom = mateRoomNo.GetAt(0);
	if (mateRoomNo.GetLength() != 6 || (cMateRoom != '9' && cMateRoom != '8'))
	{
		dlg->ShowTipMessage("���������Ų���, �����²���", 5);
		ret = RET_WF_ERROR;
		goto L_END;		
	}
	//////////////////////////////////////////////////////////////////////////
	dlg->ShowTipMessage("���״����У��벻Ҫ�ƶ�У԰��", 1);
	if (card.TestCardExists(5))
	{
		dlg->ShowTipMessage("δ�ſ�", 5);
		ret = RET_WF_ERROR;
		goto L_END;
	}
// 	if (dlg->InputQuery("�����빺����", "", eleValue, 10) != 0)
// 	{
// 		ret = RET_WF_TIMEOUT;
// 		goto L_END;
// 	}
// 	dlg->ShowTipMessage("���״����У� �벻Ҫ�ƶ�У԰��", 1);
// 	if (card.TestCardExists(5))
// 	{
// 		dlg->ShowTipMessage("δ�ſ�", 5);
// 		ret = RET_WF_ERROR;
// 		goto L_END;
// 	}
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
	while (true)
	{
		hasMore = 0;
		SetStopKey(true);
		drtp->Reset();
		if (drtp->Connect())
		{
			dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
			goto L_END;
		}
		drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
		drtp->AddField(F_SCLOSE_EMP, "240208");
// 		drtp->AddField(F_LVOL0, cardinfo.cardid);
// 		drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
// 		drtp->AddField(F_DAMT0, cardinfo.balance);      // �뿨ֵ
// 		drtp->AddField(F_LVOL1, cardinfo.tx_cnt);		// �ۼƽ��״���
//		drtp->AddField(F_LVOL2, (LPSTR)(LPCTSTR)eleValue); // ������
		drtp->AddField(F_SNAME, (LPSTR)(LPCSTR)dlg->GetConfig()->m_systemNo); // ϵͳ���
		drtp->AddField(F_SNAME2, (LPSTR)(LPCSTR)mateRoomNo); // �����
		dlg->ShowTipMessage("���ڶ�ȡ������Ϣ, ��ȴ�...", 1);		
		SetStopKey(false);
		if (drtp->SendRequest(10000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			goto L_END;		
		}
		if(drtp->GetReturnCode())
		{
			dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
			ret = RET_WF_ERROR;
			goto L_END;
		}
		if(drtp->HasMoreRecord())
		{
			ST_PACK *pData = drtp->GetNextRecord();
			//AfxMessageBox(pData->vsmess);
			//dlg->ShowTipMessage(pData->vsmess);
			dlg->AddMessageLine(pData->vsmess);
			dlg->AddMessageLine("��[ȷ��]��һ��, ��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
			if(dlg->Confirm(10) != IDOK)
			{
				ret = RET_WF_TIMEOUT;
				goto L_END;
			}
		}
		else
		{
			ret= RET_WF_ERROR;
			goto L_END;
		}
//////////////////////////////////////////////////////////////////////////
		if (dlg->InputQuery("�����빺����", "", eleValue, 10) != 0)
		{
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		dlg->ShowTipMessage("���״����У� �벻Ҫ�ƶ�У԰��", 1);
		if (card.TestCardExists(5))
		{
			dlg->ShowTipMessage("δ�ſ�", 5);
			ret = RET_WF_ERROR;
			goto L_END;
		}
		drtp->Reset();
		drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
		drtp->AddField(F_SCLOSE_EMP, "240206");
		drtp->AddField(F_LVOL0, cardinfo.cardid);
		drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
		drtp->AddField(F_DAMT0, cardinfo.balance);							  // �뿨ֵ
		drtp->AddField(F_LVOL3, cardinfo.tx_cnt);							  // �ۼƽ��״���
		drtp->AddField(F_DAMT1, (LPSTR)(LPCTSTR)eleValue);					  // ������
		drtp->AddField(F_SNAME, (LPSTR)(LPCSTR)dlg->GetConfig()->m_systemNo); // ϵͳ���
		drtp->AddField(F_SNAME2, (LPSTR)(LPCSTR)mateRoomNo);
		if (drtp->Connect())
		{
			dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
			goto L_END;
		}
		if (drtp->SendRequest(3000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			goto L_END;
		}
		if (drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK *pData = drtp->GetNextRecord();
			tipMsg.Format("����д��, �벻Ҫ�ƶ�У԰��...");
			dlg->ShowTipMessage(tipMsg, 0);
			ret = DoTransfer(&card, &cardinfo, pData);
			if (ret == RET_WF_ERROR)
			{
				SetStopKey(true);
				response->Reset();
				response->Connect();
				response->SetRequestHeader(KS_BANK_TX_CODE, 1);
				response->AddField(F_SCLOSE_EMP, "240206");
				int serialNo = atoi(pData->sserial1);
				response->AddField(F_LVOL1, serialNo);
				if (response->SendRequest(3000))
				{
					dlg->ShowTipMessage(response->GetReturnMsg().c_str(),3);
				}
				else
				{
					SetStopKey(false);
					dlg->ClearMessageLine();
					tipMsg = "д��ʧ���뵽�������Ĵ���!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}
			
			if (ret == RET_WF_TIMEOUT)
			{
				goto L_END;
			}
			cardinfo.balance = pData->damt0;
			cardinfo.tx_cnt++;
			dlg->ClearMessageLine();
			tipMsg.Format("��ת���Ľ��Ϊ", (LPSTR)(LPCSTR)eleValue);
			dlg->AddMessageLine(tipMsg);
// 			tipMsg.Format("��[�˳�]����");
// 			dlg->AddMessageLine(tipMsg,dlg->GetMaxLineNo()+1,-6);
			dlg->DisplayMessage(3);
			break;
		}
		else
		{
			dlg->ClearMessageLine();
			ret = drtp->GetReturnCode();
			if(ret != ERR_NOT_LOGIN)
				ret = RET_WF_TIMEOUT;
			dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
			dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			goto L_END;		
		}
	}
	dlg->ShowTipMessage("�������!", 2);
	ret = RET_WF_SUCCESSED;
L_END:
	if (drtp) {delete drtp;}
	if (response) {delete response;}
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

int CKSElePacketTransferWorkFLow::ReadCard(CKSCardManager *manager, KS_CARD_INFO *cardinfo)
{
	int ret = manager->ReadCardInfo(cardinfo, CKSCardManager::ciCardId | CKSCardManager::ciBalance, 20);
	if (ret)
	{
		ret = manager->GetErrNo();
		if (ret == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		return RET_WF_ERROR;
	}
	return RET_WF_SUCCESSED;
}

int CKSElePacketTransferWorkFLow::DoTransfer(CKSCardManager *manager,
							KS_CARD_INFO *cardinfo, const ST_PACK *rec)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// ��⿨
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, (int)rec->damt0 * 100); // ����ֵ
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("д��ʧ�ܣ����ط�У԰��");
		dlg->AddMessageLine("��[�˳�]����",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// ��ѯ���ת����ϸ
CKSQueryEleTransferAccoutsWorkFlow::CKSQueryEleTransferAccoutsWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "ElePackAccTrf";
}

CKSQueryEleTransferAccoutsWorkFlow::~CKSQueryEleTransferAccoutsWorkFlow()
{
	//
}

CString CKSQueryEleTransferAccoutsWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKSQueryEleTransferAccoutsWorkFlow::DoWork()
{
	CDRTPHelper *drtp = NULL;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardInfo;
	int ret = RET_WF_ERROR;
	int retCount;
	CString passwd;
	CString cardidstr;
	CString moneyValue;
	memset(&cardInfo, 0, sizeof(cardInfo));

	dlg->ClearAllColumns();
	dlg->AddListColumns("��س�ֵ��ˮ��", 120);
	dlg->AddListColumns("�ͻ���", 80);
	dlg->AddListColumns("���׿���", 70);
	dlg->AddListColumns("��������", 90);
	dlg->AddListColumns("����ʱ��", 70);
	dlg->AddListColumns("���", 70);
	dlg->AddListColumns("������ (��)", 80);
	dlg->AddListColumns("�����", 70);
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(), (LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);

	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("������У԰������", passwd, 10) != 0)
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->ShowTipMessage("���״�����, ��ȴ�", 1);
	cardidstr.Format("%d", cardInfo.cardid);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240207");
	drtp->AddField(F_LVOL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)passwd);
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	if (drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("��[�˳�]����", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	else if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		goto L_END;
	}
	else
	{
		retCount = 0;
		while (drtp->HasMoreRecord())
		{
			ST_PACK *pData = drtp->GetNextRecord();
			CString cardEleNo;                  // ��س�ֵ��ˮ��
			cardEleNo.Format("%d", pData->lvol0);
			CString userNo;						  // �ͻ���
			userNo.Format("%d", pData->lvol1);
			CString cardNo;					      // ���׿���
			cardNo.Format("%d", pData->lvol2);
			CString txtdate = ParseDateString(pData->sdate0);	// ��������
			CString txtime = ParseTimeString(pData->stime0);    // ����ʱ��
			moneyValue.Format("%0.2f", D2I(pData->damt0));
			CString eleVolumn; // ������
			eleVolumn.Format("%0.2f", D2I(pData->damt1));
			CString mateRoomNo;
			mateRoomNo.Format("%s", pData->sname);
			dlg->AddToListInfo(cardEleNo, userNo, cardNo, txtdate, txtime, moneyValue, eleVolumn, mateRoomNo);
			retCount++;
			// ֻ��ʾ10������
			if (retCount > 10)
			{
				break;
			}
		}
		if (retCount > 0)
		{
			dlg->ShowListInfo(25);
		}
		else
		{
			dlg->ShowTipMessage("û��ת�ʵļ�¼!");
		}
		ret = RET_WF_SUCCESSED;
	}
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}