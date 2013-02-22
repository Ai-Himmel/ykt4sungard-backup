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
		throw exception("创建工作流失败");
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
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo,0,sizeof cardinfo);
	SetStopKey(false);
	/*
	// dlg->ShowTipMessage("测试内容，大段内容测试，说明大段内容测试，说明没有可以做的测试内容，\n\n\n大段内容测试\n\n\n\t按［确定］按［取消]",10);
	
	dlg->AddMessageLine("测试内容，大段内容测试，说明大段内容测试，说明没有可以做的测试内容",2,2);
	dlg->AddMessageLine("大段内容测试",4,-1);
	dlg->AddMessageLine("按［确定］按［取消]",6,-8);
	if (dlg->DisplayMessage(5) != IDOK)
	{
		dlg->ShowTipMessage("交易取消",3);
		return RET_WF_TIMEOUT;
	}

	dlg->AddMessageLine("没有可以做的测试内容",2,2);
	dlg->AddMessageLine("大段内容测试",4,-1);
	dlg->AddMessageLine("按［确定］按［取消]",6,-8);
	dlg->DisplayMessage(10);
	return RET_WF_ERROR;
	*/
	
	dlg->ShowTipMessage("请放校园卡...",0);
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
		goto L_END;
	}
	if(dlg->InputPassword("请输入校园卡密码",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中，请不要移动校园卡",1);
	if(card.TestCardExists(5))
	{
		dlg->ShowTipMessage("未放卡",5);
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
			dlg->ShowTipMessage(drtp->GetErrMsg());
			goto L_END;
		}
		drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
		drtp->AddField(F_SCLOSE_EMP,"240104");	// 交易码
		drtp->AddField(F_LVOL0,cardinfo.cardid);	// 交易卡号
		drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// 密码
		drtp->AddField(F_DAMT0,cardinfo.balance);		//入卡值
		drtp->AddField(F_LVOL1,cardinfo.tx_cnt);		//累计交易次数
		drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// 系统编号					//设备ＩＤ
		drtp->AddField(F_SCUST_NO,"system");			//操作员
		dlg->ShowTipMessage("正在处理交易，请不要移动校园卡...",1);
		SetStopKey(false);
		if(drtp->SendRequest(15))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg());
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		if(drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK * pData = drtp->GetNextRecord();
			tipMsg.Format("%s 金额 %.02f 元。\n正在写卡，请不要移动校园卡..."
						  ,pData->semail,pData->damt1);
			hasMore = pData->lvol2;
			dlg->ShowTipMessage(tipMsg,0);
			ret = DoSubsidy(&card,&cardinfo,pData);
			if(RET_WF_ERROR == ret)
			{
				SetStopKey(true);
				response->Reset();
				response->Connect();
				response->SetRequestHeader(900077,1);
				response->AddField(F_SCLOSE_EMP,"240107");
				int serialno = atoi(pData->sserial1);
				response->AddField(F_LVOL1,serialno);
				if(response->SendRequest(10))
				{
					dlg->ShowTipMessage(response->GetReturnMsg(),3);
				}
				else
				{
					SetStopKey(false);
					dlg->ClearMessageLine();
					tipMsg = "写卡失败请到管理中心处理!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
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
				tipMsg.Format("补贴 %s ",pData->semail);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("金额 %0.2f 元已领取",pData->damt1);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("您还有补贴未领取");
				dlg->AddMessageLine(tipMsg,dlg->GetMaxLineNo()+2);
				tipMsg.Format("按[确定]继续领取，按[退出]返回");
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
				tipMsg.Format("补贴 %s ",pData->semail);
				dlg->AddMessageLine(tipMsg);
				tipMsg.Format("金额 %0.2f 元已领取",pData->damt1);
				dlg->AddMessageLine(tipMsg);
				dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
				dlg->DisplayMessage(3);
				break;
			}
		}
		else
		{
			//没有补助
			dlg->ClearMessageLine();
			ret = drtp->GetReturnCode();
			if(ret != ERR_NOT_LOGIN)
				ret = RET_WF_TIMEOUT;
			dlg->AddMessageLine(drtp->GetReturnMsg());
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			
			goto L_END;
		}
	}
	dlg->ShowTipMessage("交易完成！",2);
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
		// 检测卡
		if(manager->TestCardExists(5))
		{
			continue;
		}
		// 写卡, 加入四舍五入的函数, 不要强转int类型
//		ret = manager->SetMoney(cardinfo->cardid,(int)(rec->damt2 * 100));
		ret = manager->SetMoney(cardinfo->cardid,D2I(rec->damt2 * 100));
		if(!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if(manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重新放校园卡！");
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
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
	dlg->AddListColumns("摘要",200);
	dlg->AddListColumns("交易卡号",70);
	dlg->AddListColumns("领取日期",90);
	dlg->AddListColumns("领取时间",70);
	dlg->AddListColumns("金额",75);
	dlg->AddListColumns("状态",80);
	

	dlg->ShowTipMessage("请放校园卡...",0);
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
	if(dlg->InputPassword("请输入校园卡密码",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中,请等待...",1);
	cardidstr.Format("%d",cardinfo.cardid);//33396);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240103");	// 交易码
	drtp->AddField(F_SSERIAL0,(LPSTR)(LPCTSTR)cardidstr);	// 交易卡号
	drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// 密码
	drtp->AddField(F_SORDER2,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// 系统编号 设备ＩＤ
	drtp->AddField(F_SCUST_NO,"system");			//操作员
	if(drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg());
		goto L_END;
	}
	if(!drtp->SendRequest(10))
	{
		recCount = 0;
		while(drtp->HasMoreRecord())
		{
			ST_PACK * pData = drtp->GetNextRecord();
			CString money;
			money.Format("%.2f元",pData->damt0);
			CString status = (pData->sstatus1[0] == '2')? "未领取":"已领取";
			CString cardno;
			cardno.Format("%d",pData->lvol3);
			CString txdate = ParseDateString(pData->sdate1);
			CString txtime = ParseTimeString(pData->stime1);
			dlg->AddToListInfo(pData->semail,cardno,txdate,txtime,
				(LPCTSTR)money,(LPCTSTR)status);
			recCount++;
			// 只显示10条
			if(recCount > 10) break;
		}
		if(recCount > 0)
			dlg->ShowListInfo(25);
		else
			dlg->ShowTipMessage("没有补贴领取的记录!");
		ret = RET_WF_SUCCESSED;
	}
	else
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
	}
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	return ret;
}

// 更新卡信息
//////////////////////////////////////////////////////////////////////////
// CKModifyCardInfoWorkflow
CKModifyCardInfoWorkflow::CKModifyCardInfoWorkflow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "ModifyCardInfo";
}

CKModifyCardInfoWorkflow::~CKModifyCardInfoWorkflow(void)
{
	//
}

int CKModifyCardInfoWorkflow::DoWork()
{
	CString passwd;
	CString tipMsg("");
	CString tipCardInfoMsg("");
	CDRTPHelper * drtp = NULL;
	CDRTPHelper * response = NULL;
	KS_CARD_INFO cardinfo;
	TPublishCard updateCardInfo;
	//////////////////////////////////////////////////////////////////////////
	CString strDealLineDate;
	CString strName;
	CString strLibraryNo;
	CString strIdentifyNo;
	CString strSexNo;
	CString strCardNo;
	CString strShowCardNo;
	CString strCertificateNo;
	CString strDepartmentNo;
	CString strCardType;
	//////////////////////////////////////////////////////////////////////////
	int ret;
//	int iCount = 0;
	int hasMore = 0;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();  // Get a active main window of the application
	memset(&cardinfo, 0, sizeof cardinfo);
	memset(&updateCardInfo, 0, sizeof(TPublishCard));
	dlg->ShowTipMessage("请放校园卡...",0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if(card.OpenCOM()!=0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	
	SetStopKey(false);
	ret = ReadCard(&card, &cardinfo);                    
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                    // 读卡失败
	}
	if(dlg->InputPassword("请输入校园卡密码",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中，请不要移动校园卡",1);
	if(card.TestCardExists(5))
	{			  
		ret = RET_WF_ERROR;
		goto L_END;
	}
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
	
	hasMore = 0;
	SetStopKey(true);
	drtp->Reset();
	if(drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg());
		goto L_END;
	}
	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240105");				// 交易码
	drtp->AddField(F_LVOL0,cardinfo.cardid);			// 交易卡号
	drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// 密码
//	drtp->AddField(F_DAMT0,cardinfo.balance);			//入卡值
//	drtp->AddField(F_LVOL1,cardinfo.tx_cnt);			//累计交易次数
	drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// 系统编号					//设备ＩＤ
//	drtp->AddField(F_SCUST_NO,"system");				//操作员
	dlg->ShowTipMessage("正在处理交易，请不要移动校园卡...",1);
	SetStopKey(false);
	if(drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	if(drtp->HasMoreRecord())
	{
	//	iCount++;
		ST_PACK * pData = drtp->GetNextRecord();
	//	dlg->ShowTipMessage("正在读卡，请不要移动校园卡",1);
		if(card.TestCardExists(5))
		{			  
			ret = RET_WF_ERROR;
			goto L_END;
		}
		card.ReadCardInformation(cardinfo.cardid, &updateCardInfo);
		////////////////////////////////////////////////////////////////////////////
		strDealLineDate.Format("    截止日期%s", pData->sdate0);
		strName.Format("    姓名%s", pData->sname);
		strLibraryNo.Format("%s", pData->sname2);
		strIdentifyNo.Format("%s", pData->scust_auth2);
		if (pData->scust_type[0] == '0')
		{
			strSexNo.Format("男");
		}
		else if (pData->scust_type[0] == '1')
		{
			strSexNo.Format("女");
		}
		else
		{
			strSexNo.Format("无");
		}
		strCardNo.Format("    学工号%s", pData->scust_limit);
		strShowCardNo.Format("显示卡号 %s", pData->scust_no);
		strCertificateNo.Format("%s", pData->scust_auth);
		strDepartmentNo.Format("%s", pData->sserial0, 10);
		strCardType.Format("    卡类型%s", pData->sbankname);
		tipCardInfoMsg.Format("%s\n%s", strName, strCardNo);
		// 显示出需要更新的数据项........................
		dlg->AddMessageLineEx(strCardType, dlg->GetMaxLineNo() + 1, 0, dlg->AT_LEFT);
		dlg->AddMessageLineEx(strDealLineDate, dlg->GetMaxLineNo() + 1, 0, dlg->AT_LEFT);
		dlg->AddMessageLineEx(strName, dlg->GetMaxLineNo() + 1, 0, dlg->AT_LEFT);
		dlg->AddMessageLineEx(strCardNo, dlg->GetMaxLineNo() + 1, 0, dlg->AT_LEFT);
		tipMsg.Format("按[确定]继续更新, 按[退出]返回");
		dlg->AddMessageLineEx(tipMsg, dlg->GetMaxLineNo() + 3, -6, dlg->AT_LEFT);
		if (dlg->Confirm(10) != IDOK)
		{
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		///////////////////////////////////////////////////////////////////////////
		memcpy(updateCardInfo.DeadLineDate, pData->sdate0, 9);			// 截止日期
		updateCardInfo.CardRightType = pData->lvol5;					// 卡类型
		//............. 测试
		//tipMsg.Format("%d", updateCardInfo.CardRightType);
		//AfxMessageBox(tipMsg);
		//.............
		memcpy(updateCardInfo.ucName, pData->sname, 8);					// 姓名
		memcpy(updateCardInfo.ucLibraryNo, pData->sname2, 20);			// 图书证号
		memcpy(updateCardInfo.ucIdentifyNo, pData->scust_auth2, 4);		// 身份证号
		memcpy(updateCardInfo.ucSexNo, pData->scust_type, 1);			// 性别
		memcpy(updateCardInfo.ucCardNo, pData->scust_limit, 20);		// 学工号
		memcpy(updateCardInfo.ShowCardNo, pData->scust_no, 10);			// 显示卡号
		memcpy(updateCardInfo.ucCertificateNo, pData->scust_auth, 20);	// 证件号码
		memcpy(updateCardInfo.ucDepartmentNo, pData->sserial0, 10);		// 部门编号
		////////////////////////////////////////////////////////////////////////////            
		tipMsg.Format("正在写卡，请不要移动校园卡...");
		dlg->ShowTipMessage(tipMsg,0);
		ret = DoModifyCardInfo(&card,&cardinfo,pData, &updateCardInfo);  
		//////////////////////////////////////////////////////////////////////////
// 		if(RET_WF_ERROR == ret)
// 		{
// 			SetStopKey(true);
// 			response->Reset();
// 			response->Connect();
// 			response->SetRequestHeader(900077,1);
// 			response->AddField(F_SCLOSE_EMP,"240107");
// 			int serialno = atoi(pData->sserial1);
// 			response->AddField(F_LVOL1,serialno);
// 			if(response->SendRequest(3000))
// 			{
// 				dlg->ShowTipMessage(response->GetReturnMsg(),3);
// 			}
// 			else
// 			{
// 				SetStopKey(false);
// 				dlg->ClearMessageLine();
// 				tipMsg = "写卡失败请到管理中心处理!";
// 				dlg->AddMessageLine(tipMsg);
// 				dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
// 				dlg->DisplayMessage(1);
// 			}
// 			ret = RET_WF_ERROR;
// 			goto L_END;
// 		}
		if (RET_WF_TIMEOUT == ret)
		{
			goto L_END;
		}
		SetStopKey(false);
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);	
		goto L_END;
	}
	dlg->ShowTipMessage("交易完成！",1);
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

CString CKModifyCardInfoWorkflow::GetWorkflowID()
{
	return m_key;
}

int CKModifyCardInfoWorkflow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
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

int CKModifyCardInfoWorkflow::DoModifyCardInfo(
								  CKSCardManager* manager,
								  KS_CARD_INFO *cardinfo, 
								  const ST_PACK *rec, 
								  TPublishCard *pc
								  )
{
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while(--retries>=0)
	{
		// 检测卡
		if(manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->ModifyCardInfo(cardinfo->cardid, pc);
		if(!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if(manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重新放校园卡！");
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}