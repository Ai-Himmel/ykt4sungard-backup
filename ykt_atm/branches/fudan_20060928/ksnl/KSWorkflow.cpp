#include "stdafx.h"
#include "ksnl.h"
#include <exception>
#include ".\ksworkflow.h"
#include "KSInputDialog.h"
#include "KSNLDlg.h"
#include "KSCardManager.h"
#include "DRTPHelper.h"
#include "ksutil.h"

#define KS_BANK_TX_CODE			900077

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

// Write water packet cardtype to log file!
int WriteLogFile(char BeginCardType, char EndCardType, 
				 double BeginBalance, double EndBalance, 
				 int ErrCode, const char *ErrMsg)
{
	CStdioFile sfLogFile;
	CString strAppPath = "";
	CString strWriteFile = "";
	char cAppPath[512] = "";
	int nFilePathLength = 0;
	BOOL bResult;
	static int s_nCount = 0;
	nFilePathLength = GetFullPathName("LogFile.txt", 512, cAppPath, NULL);
	if ('\0' == cAppPath[0])
	{
		return -1;				// 文件夹路径长度过长	 
	}
	strAppPath.Format("%s", cAppPath);
	bResult = sfLogFile.Open(strAppPath, CFile::modeWrite | CFile::modeCreate 
			 | CFile::modeNoTruncate | CFile::typeText);
	if (!bResult)
	{
		return -2;				// 文件不能打开
	}
	CTime CurrentTime = CTime::GetCurrentTime();
	strWriteFile.Format("[%04d-%02d-%02d %02d:%02d:%02d] 写卡类型:%d -- 读卡类型:%d -- 写卡余额:%4.4f -- 读卡余额:%4.4f -- 错误代码:%d -- 错误信息:%s\n", 
						CurrentTime.GetYear(),CurrentTime.GetMonth(), CurrentTime.GetDay(), CurrentTime.GetHour(), 
						CurrentTime.GetMinute(), CurrentTime.GetSecond(), BeginCardType, EndCardType, BeginBalance, EndBalance, ErrCode, ErrMsg);
	sfLogFile.SeekToEnd();
	sfLogFile.WriteString(strWriteFile);
	sfLogFile.Close();
	return 0;
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
// 补助金的编写
//////////////////////////////////////////////////////////////////////////
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
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                    // 读卡失败
	}
	dlg->SetLimtText(1);
	if(dlg->InputPassword("请输入校园卡密码",passwd,10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中，请不要移动校园卡",1);
	if(card.TestCardExists(5))
	{
//		dlg->ShowTipMessage("未放卡",5);			  
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
		drtp->AddField(F_SCLOSE_EMP,"240104");				// 交易码
		drtp->AddField(F_LVOL0,cardinfo.cardid);			// 交易卡号
		drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd);	// 密码
		drtp->AddField(F_DAMT0,cardinfo.balance);			//入卡值
		drtp->AddField(F_LVOL1,cardinfo.tx_cnt);			//累计交易次数
		drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);// 系统编号					//设备ＩＤ
		drtp->AddField(F_SCUST_NO,"system");				//操作员
		dlg->ShowTipMessage("正在处理交易，请不要移动校园卡...",1);
		SetStopKey(false);
		if(drtp->SendRequest(3000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
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
			dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			
			goto L_END;
		}
	}
	dlg->ShowTipMessage("交易完成！",1);
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
// 退出
//////////////////////////////////////////////////////////////////////////
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
// 查询补贴
//////////////////////////////////////////////////////////////////////////
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	dlg->SetLimtText(1);
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
			dlg->ShowTipMessage("没有补贴领取的记录!", 2);
		ret = RET_WF_SUCCESSED;
	}
	else
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
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
// 查询水量
//////////////////////////////////////////////////////////////////////////
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
	dlg->AddListColumns("剩余水量", 70);
	dlg->ShowTipMessage("请放校园卡...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR; 
	}
	SetStopKey(false);
	ret = card.ReadCardInfo(&cardinfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	ret = SMT_ReadWaterPackInfo(&water);
	if (ret)
	{
		dlg->ShowTipMessage("读取水控钱包信息失败", 1);
		goto L_END;
	}
	waterRemain.Format("剩余水量: %d 升", water.remain);
	dlg->AddMessageLine(waterRemain);
	dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
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
// CKSQueryTransferAccoutsWorkFlow (查询转帐明细)
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

//////////////////////////////////////////////////////////////////////////
// 功能编号: 240201
// 功能名称: 查询转帐明细
// 功能描述: 查询用户历史购水明细，最近10条
// 界面输入: 交易码(sclose_emp), 交易卡号(lvol0), 密码(semp_pwd)
// 界面输出: 购水冲值流水号(lvo10), 客户号(lvo11), 交易卡号(lvo12)
//			 购水日期(sdate0, 8字符), 购水时间(stime0, 6字符), 购买水量(lvol3)
//////////////////////////////////////////////////////////////////////////
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
	dlg->AddListColumns("购水冲值流水号", 120);
	dlg->AddListColumns("客户号", 80);
	dlg->AddListColumns("交易卡号", 70);
	dlg->AddListColumns("购水日期", 90);
	dlg->AddListColumns("购水时间", 70);
	dlg->AddListColumns("购买水量(吨)", 120);

	dlg->ShowTipMessage("请放校园卡...", 0);
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", passwd, 10) != 0)
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请等待", 1);
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
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(2);
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
			CString cardWaterNo;                  // 购水冲值流水号
			cardWaterNo.Format("%d", pData->lvol0);
			CString userNo;						  // 客户号
			userNo.Format("%d", pData->lvol1);
			CString cardNo;					      // 交易卡号
			cardNo.Format("%d", pData->lvol2);
			CString txtdate = ParseDateString(pData->sdate0);
			CString txtime = ParseTimeString(pData->stime0);
			CString waterVolumn;
			waterVolumn.Format("%d", D2I(pData->lvol3/1000));
			dlg->AddToListInfo(cardWaterNo, userNo, cardNo, txtdate, txtime, waterVolumn);
			retCount++;
			// 只显示10条出来
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
			dlg->ShowTipMessage("没有转帐的记录!", 2);
		}
		ret = RET_WF_SUCCESSED;
	}
	/*
	else
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
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
// CKSWaterPacketTransferWorkFlow (水控钱包转帐)
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

//////////////////////////////////////////////////////////////////////////
// 功能编号: 240202
// 功能名称: 水控钱包转帐
// 功能描述: 用户通过圈存机从大钱包中购水, 然后写入到水控钱包中
// 业务逻辑: 1.	检查用户卡状态，检查卡余额
//			 2.	从用户帐户中扣除购水金额
//           3.	生成购水消费流水
//           4.	生成购水充值流水
//           5.	如果失败需要生成补写卡流水，见相关功能
// 相关功能: 如果写卡失败发起转帐失败交易, 交易码240111
// 界面输入: 交易码(sclose_emp), 交易卡号(lvol0), 密码(semp_pwd), 卡交易次数(lvol3)
//			 入卡值(damt0), 购水量(lv0l1), 终端号(sname)，卡中剩余水量(lvol2)
// 界面输出: 消费流水号(lvo10), 购水冲值流水号(lvo11), 出卡值(damt0)
//			 水量(lvol2), 返回信息(vsmess)
//////////////////////////////////////////////////////////////////////////
int CKSWaterPacketTransferWorkFlow::DoWork()
{
	CString password;
/*	CString inputValue = _T("");*/
	CString waterVolumn;
	CString tipMsg;
	CDRTPHelper *drtp = NULL;
	CDRTPHelper *response = NULL;
	KS_CARD_INFO cardInfo;
	KS_CARD_INFO tempCardInfo;			// 新添加的临时卡信息
	int ret;
	int iCount = 0;
	int hasMore = 0;
	double balance = 0;
	char cCardType = NULL;				// 新添加卡类型需要读文本时候判断
	WATER_PACK_INFO water, tempWater;	
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardInfo, 0, sizeof(cardInfo));
	memset(&tempCardInfo, 0, sizeof(tempCardInfo));
	memset(&tempWater, 0, sizeof(tempWater));
	memset(&water, 0, sizeof(water));
	SetStopKey(false);
	dlg->ShowTipMessage("请放校园卡...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	// 读取卡信息
	ret = ReadCard(&card, &cardInfo);
//	ret = card.ReadCardInfo(&cardInfo, CKSCardManager::ciBalance, 5);
	if (ret)
	{
		if (RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);					// 修改过
		}
		goto L_END;
	}
	balance = cardInfo.balance;
	ret = SMT_ReadWaterPackInfo(&water);
	if (ret)
	{
		dlg->ShowTipMessage("读取水控钱包信息失败", 1);
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);			
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(0);
	if (dlg->InputQuery("请输入水量 单位:吨", "", waterVolumn, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);		
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
		// 建立drtp传输参数
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
		// 发送请求
		if (drtp->SendRequest(3000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		// 提取返回记录
		if (drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK *pData = drtp->GetNextRecord();
			tipMsg.Format("正在写卡, 请不要移动校园卡...", 1);
			dlg->ShowTipMessage(tipMsg, 0);
			// 写卡(大钱包中减钱), 这里有个出卡值
			ret = DoTransferValue(&card, &cardInfo, pData);				
			// 大钱包中扣款出现问题的情况, 写卡失败发送信息, 失败标志为0
			if (RET_WF_ERROR == ret)
			{
				// 补写流水
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
					tipMsg = "写卡失败请到管理中心处理!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}
			// 超时
			if (RET_WF_TIMEOUT == ret)
			{
				goto L_END;
			}
			memset(&water, 0, sizeof(water));
			// 后面还会有一个在小钱包里面增加水量的操作, 也应该有个报错信息, 失败标志为1
			// 读取水控钱包失败, 函数没有封装，可能有点问题
			if (SMT_ReadWaterPackInfo(&water) != 0)
			{
				tipMsg = "读取卡失败";
				dlg->AddMessageLine(tipMsg);
				dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
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
					tipMsg = "写卡失败请到管理中心处理!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
					dlg->DisplayMessage(1);
				}
				ret = RET_WF_ERROR;
				goto L_END;
			}

			if (RET_WF_TIMEOUT == ret)
			{
				goto L_END;
			}
			// 写卡成功
			cardInfo.tx_cnt++;
			cardInfo.balance = pData->damt0;
			//water.remain /= 1000;
			hasMore = pData->damt0;
			int volumnInL = strtoul((LPSTR)(LPCSTR)waterVolumn,NULL,10) * 1000;
			SetStopKey(false);
			dlg->ClearMessageLine();
			tipMsg.Format("购水水量:%d升\n剩余水量:%d升\n 消费%0.2f元 剩余%0.2f元", 
				volumnInL, water.remain, (balance - cardInfo.balance), cardInfo.balance);
			dlg->ShowTipMessage(tipMsg);
			break;
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
			dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(3);
			goto L_END;
		}
	}// end while
	dlg->ShowTipMessage("交易完成!", 1);
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

// 大钱包入账
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
		// 写卡
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
		dlg->AddMessageLine("写卡失败, 请重新放校园卡!");
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

// 小钱包进水
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
		dlg->AddMessageLine("写卡失败, 请重新放校园卡!");
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// 功能编号: 240203
// 功能名称: 将卡做成定点的水控卡
// 功能描述: 用户通过圈存机从大钱包中购水, 然后写入到水控钱包中
// 业务逻辑: 1.	用户输入密码
//			 2. 用户输入水表号
//           3.	向后台发起交易, 发送卡的定点水表号
// 界面输入: 交易码(sclose_emp), 交易卡号(lvol0), 密码(semp_pwd), 水表号(lvol1)
//////////////////////////////////////////////////////////////////////////
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
	dlg->ShowTipMessage("请放校园卡...", 0);
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	// 如果是第一张没有做成定点卡的卡.
	if (SMT_ReadWaterPackInfo(&tempWater) == 0)
	{
		water.remain = tempWater.remain;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园密码", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);		
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputQuery("请输入水表号", "", inputWaterTermId, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	SetStopKey(false);
	if (card.TestCardExists(5))
	{
  	//	dlg->ShowTipMessage("未放卡", 5);       
		ret = RET_WF_ERROR;
		goto L_END;
	}
	water.cardtype = WATER_FIXED_CARD;
	water.termid = atoi((LPCTSTR)inputWaterTermId);
	// 新加入的一句话, 重写卡的剩余金额
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
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(2);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// 新加入的检测返回的值是否正确
	if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		ret = RET_WF_ERROR;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);			
		ret = RET_WF_ERROR;
		goto L_END;
	}
	if (SMT_InitWaterInfo(&water) != 0)
	{
		dlg->ShowTipMessage("写定点卡失败, 请重新操作");
		goto L_END;
	}
	dlg->ShowTipMessage("定点卡申请成功!", 1);
	ret = RET_WF_SUCCESSED;
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// 定点卡的取消
//////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////
// 功能编号: 240204
// 功能名称: 定点卡取消
// 功能描述: 取消卡与水表的绑定
// 界面输入: 交易代码(sclose_emp, 240204), 交易卡号(lvol0), 密码(semp_pwd)
//////////////////////////////////////////////////////////////////////////
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
	dlg->ShowTipMessage("请放校园卡...", 0);
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;		
	}
	
	if (SMT_ReadWaterPackInfo(&water) != 0)
	{
		dlg->ShowTipMessage("读卡失败, 请重新操作!");
		goto L_END;
	}
	water.cardtype = WATER_COMMON_CARD;
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入密码", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请等待...", 1);
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
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(2);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// 新加入的检测返回的值是否正确
	if(drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		ret = RET_WF_ERROR;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);				
		ret = RET_WF_ERROR;
		goto L_END;
	}
	if (SMT_WriteWaterPackInfo(&water) != 0)
	{
		dlg->ShowTipMessage("写定点卡失败, 请重新操作");
		goto L_END;
	}
	dlg->ShowTipMessage("定点卡取消成功!", 2);	
	return RET_WF_SUCCESSED;
L_END:
	if (drtp)
		delete drtp;
	card.CloseCOM();
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// 电控转帐
//////////////////////////////////////////////////////////////////////////
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
	CDRTPHelper *response = NULL;      // 补充流水
	KS_CARD_INFO cardinfo;
	int ret;
	int iCount = 0;
	int hasMore = 0;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));
	SetStopKey(false);	
	dlg->ShowTipMessage("请放校园卡...", 0);
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;	
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", password, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);			
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputQuery("请输入宿舍号", "", mateRoomNo, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	// 判断宿舍号是否符合规范
	cMateRoom = mateRoomNo.GetAt(0);
	if (mateRoomNo.GetLength() != 6 || (cMateRoom != '9' && cMateRoom != '8'))
	{
		dlg->ShowTipMessage("输入的宿舍号不对, 请重新操作", 5);
		ret = RET_WF_ERROR;
		goto L_END;		
	}
	//////////////////////////////////////////////////////////////////////////
	dlg->ShowTipMessage("交易处理中，请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{
	//	dlg->ShowTipMessage("未放卡", 5);				
		ret = RET_WF_ERROR;
		goto L_END;
	}
// 	if (dlg->InputQuery("请输入购电金额", "", eleValue, 10) != 0)
// 	{
// 		ret = RET_WF_TIMEOUT;
// 		goto L_END;
// 	}
// 	dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
// 	if (card.TestCardExists(5))
// 	{
// 		dlg->ShowTipMessage("未放卡", 5);
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
// 		drtp->AddField(F_DAMT0, cardinfo.balance);      // 入卡值
// 		drtp->AddField(F_LVOL1, cardinfo.tx_cnt);		// 累计交易次数
//		drtp->AddField(F_LVOL2, (LPSTR)(LPCTSTR)eleValue); // 购电金额
		drtp->AddField(F_SNAME, (LPSTR)(LPCSTR)dlg->GetConfig()->m_systemNo); // 系统编号
		drtp->AddField(F_SNAME2, (LPSTR)(LPCSTR)mateRoomNo); // 宿舍号
		dlg->ShowTipMessage("正在读取宿舍信息, 请等待...", 1);		
		SetStopKey(false);
		if (drtp->SendRequest(10000))
		{
			dlg->ClearMessageLine();
			dlg->AddMessageLine(drtp->GetErrMsg().c_str());
			dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(2);
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
			dlg->AddMessageLine("按[确认]下一步, 按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
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
		if (dlg->InputQuery("请输入购电金额", "", eleValue, 10) != 0)
		{
			ret = RET_WF_TIMEOUT;
			goto L_END;
		}
		dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
		if (card.TestCardExists(5))
		{
		//	dlg->ShowTipMessage("未放卡", 5);			
			ret = RET_WF_ERROR;
			goto L_END;
		}
		drtp->Reset();
		drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
		drtp->AddField(F_SCLOSE_EMP, "240206");
		drtp->AddField(F_LVOL0, cardinfo.cardid);
		drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)password);
		drtp->AddField(F_DAMT0, cardinfo.balance);							  // 入卡值
		drtp->AddField(F_LVOL3, cardinfo.tx_cnt);							  // 累计交易次数
		drtp->AddField(F_DAMT1, (LPSTR)(LPCTSTR)eleValue);					  // 购电金额
		drtp->AddField(F_SNAME, (LPSTR)(LPCSTR)dlg->GetConfig()->m_systemNo); // 系统编号
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
			dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
			dlg->DisplayMessage(2);
			goto L_END;
		}
		if (drtp->HasMoreRecord())
		{
			iCount++;
			ST_PACK *pData = drtp->GetNextRecord();
			tipMsg.Format("正在写卡, 请不要移动校园卡...");
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
					tipMsg = "写卡失败请到管理中心处理!";
					dlg->AddMessageLine(tipMsg);
					dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
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
			SetStopKey(false);						/*新添加的*/
			tipMsg.Format("您购电的金额为%s元", (LPSTR)(LPCSTR)eleValue);
			dlg->AddMessageLine(tipMsg);
			tipMsg.Format("您购买的电量为%.2lf度",pData->damt1);
			dlg->AddMessageLine(tipMsg);
// 			tipMsg.Format("按[退出]返回");
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
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(3);
			goto L_END;		
		}
	}
	dlg->ShowTipMessage("交易完成!", 1);
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
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, (int)rec->damt0 * 100); // 出卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡");
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// 查询电控转帐明细
//////////////////////////////////////////////////////////////////////////
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
	dlg->AddListColumns("电控冲值流水号", 120);
	dlg->AddListColumns("客户号", 80);
	dlg->AddListColumns("交易卡号", 70);
	dlg->AddListColumns("购电日期", 90);
	dlg->AddListColumns("购电时间", 70);
	dlg->AddListColumns("金额", 70);
	dlg->AddListColumns("购电量 (度)", 80);
	dlg->AddListColumns("宿舍号", 70);
	dlg->ShowTipMessage("请放校园卡...", 0);
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
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", passwd, 10) != 0)
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
	dlg->ShowTipMessage("交易处理中, 请等待", 1);
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
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(2);
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
			CString cardEleNo;                  // 电控充值流水号
			cardEleNo.Format("%d", pData->lvol0);
			CString userNo;						  // 客户号
			userNo.Format("%d", pData->lvol1);
			CString cardNo;					      // 交易卡号
			cardNo.Format("%d", pData->lvol2);
			CString txtdate = ParseDateString(pData->sdate0);	// 购电日期
			CString txtime = ParseTimeString(pData->stime0);    // 购电时间
			moneyValue.Format("%0.2f", pData->damt0);
			CString eleVolumn; // 购电量
			eleVolumn.Format("%0.2f", pData->damt1);
			CString mateRoomNo;
			mateRoomNo.Format("%s", pData->sname);
			dlg->AddToListInfo(cardEleNo, userNo, cardNo, txtdate, txtime, moneyValue, eleVolumn, mateRoomNo);
			retCount++;
			// 只显示10条出来
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
			dlg->ShowTipMessage("没有转帐的记录!");
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

//////////////////////////////////////////////////////////////////////////
// 更新卡信息
//////////////////////////////////////////////////////////////////////////
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
	CString strDealLineDate = "";
	CString strName = "";
	CString strLibraryNo = "";
	CString strIdentifyNo = "";
	CString strSexNo = "";
	CString strCardNo = "";
	CString strShowCardNo = "";
	CString strCertificateNo = "";
	CString strDepartmentNo = "";
	CString strCardType = "";
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
	dlg->SetLimtText(1);
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
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
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
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
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
		dlg->ShowTipMessage(    tipMsg,0);
		ret = DoModifyCardInfo(&card,&cardinfo,pData, &updateCardInfo);  
		//////////////////////////////////////////////////////////////////////////
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
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);	
		goto L_END;
	}
	dlg->ShowTipMessage("    交易完成！",1);
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

//////////////////////////////////////////////////////////////////////////
// 查询补写卡信息
//////////////////////////////////////////////////////////////////////////
CKQueryMendCardWorkflow::CKQueryMendCardWorkflow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "QueryMendCard";
}

CKQueryMendCardWorkflow::~CKQueryMendCardWorkflow(void)
{
	//
}

int CKQueryMendCardWorkflow::DoWork()
{
	CString passwd;
	CString tipMsg("");
	CString tipCardInfoMsg("");
	CDRTPHelper * drtp = NULL;
	KS_CARD_INFO cardinfo;
	TPublishCard updateCardInfo;
	int recCount = 0;
	
	CString strTradeNo = "";
	CString strCutid = "";
	CString strName = "";
	CString strSexNo = "";
	CString strStuempNo = "";
	CString strCardid = "";
	CString strDealDate = "";
	CString strBalance = "";
	
	int ret;
	int hasMore = 0;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();  // Get a active main window of the application
	memset(&cardinfo, 0, sizeof(cardinfo));
	memset(&updateCardInfo, 0, sizeof(updateCardInfo));

	dlg->ClearAllColumns();
	dlg->AddListColumns("交易码", 80);
	dlg->AddListColumns("客户号", 80);
	dlg->AddListColumns("姓名", 80);
	dlg->AddListColumns("性别", 40);
	dlg->AddListColumns("学工号", 80);
	dlg->AddListColumns("交易卡号", 80);
	dlg->AddListColumns("有效截止日期", 100);
	dlg->AddListColumns("可用余额", 80);

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
	
	ret = card.ReadCardInformation(cardinfo.cardid, &updateCardInfo);
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                    // 读卡失败
	}

	if(card.TestCardExists(5))
	{			  
		ret = RET_WF_ERROR;
		goto L_END;
	}
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();

	hasMore = 0;
	drtp->Reset();
	if(drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240108");									// 交易码							
	drtp->AddField(F_LVOL1, cardinfo.cardid);								// 交易卡号
	drtp->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);			// 学工号
	drtp->AddField(F_SNAME, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);	// 系统编号				
	dlg->ShowTipMessage("正在处理交易，请不要移动校园卡...",1);

	if(drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}
	else
	{
		while (drtp->HasMoreRecord())
		{
			SetStopKey(false);
			ST_PACK *pData = drtp->GetNextRecord();
			strTradeNo.Format("%d", pData->lvol2);
			strCutid.Format("%d", pData->lvol3);
			strName.Format("%s", pData->sname);
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
			strStuempNo.Format("%s", pData->scust_auth);
			strCardid.Format("%d", pData->lvol0);
			strDealDate.Format("%s", pData->sdate0);
			strBalance.Format("%.2f", pData->damt1);
			dlg->AddToListInfo(strTradeNo, strCutid, strName, strSexNo, strStuempNo, strCardid, strDealDate, strBalance);	
			recCount++;
			if (recCount > 10)
				break;
		}
		
		if (recCount > 0)
			dlg->ShowListInfo(25);
		else
			dlg->ShowTipMessage("没有补写卡信息记录");
	}
	ret = RET_WF_SUCCESSED;
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

CString CKQueryMendCardWorkflow::GetWorkflowID()
{
	return m_key;
}

int CKQueryMendCardWorkflow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
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

//////////////////////////////////////////////////////////////////////////
// 补写卡信息
//////////////////////////////////////////////////////////////////////////
CKMendCardWorkflow::CKMendCardWorkflow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "MendCard";
}

CKMendCardWorkflow::~CKMendCardWorkflow(void)
{
	//
}

int CKMendCardWorkflow::DoWork()
{
	char str_physical_no[9] = "";
	CString passwd("");
	CString tipMsg("");
	CString tipCardInfoMsg("");
	CDRTPHelper * drtp = NULL;
	CDRTPHelper * response = NULL;
	KS_CARD_INFO cardinfo;
	int mend_card_function_no = 847119;
	int ret = 0;
	int hasMore = 0;
	double pre_card_money = 0;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();  // Get a active main window of the application
	memset(&cardinfo, 0, sizeof(cardinfo));
	dlg->ShowTipMessage("请放校园卡...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	if (card.OpenCOM() != 0)
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
	
	ret = ReadSerial(cardinfo.phyid);
	if (ret)
	{
		ret = RET_WF_ERROR;
		goto L_END;	
	}

	HexToAscii(cardinfo.phyid, 4, str_physical_no);

	if (card.TestCardExists(5))
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
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}

	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240109");											// 交易码
	drtp->AddField(F_SBANK_ACC, str_physical_no);									// 物理卡号
	drtp->AddField(F_LVOL0, cardinfo.cardid);										// 交易卡号
	drtp->AddField(F_LVOL8, cardinfo.tx_cnt);										// 累计交易次数
	drtp->AddField(F_DAMT1, cardinfo.balance);										// 入卡值
	drtp->AddField(F_SCUST_LIMIT, "system");										// 操作员
	drtp->AddField(F_LVOL6, 0);														// 工作站ID号
	drtp->AddField(F_LVOL7, atoi((LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo));	// 设备系统编号				
	pre_card_money = cardinfo.balance;
	
	SetStopKey(false);
	
	if (drtp->SendRequest(3000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str());
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(3);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	if (drtp->HasMoreRecord())
	{
		ST_PACK * pData = drtp->GetNextRecord();
		tipMsg.Format("正在写卡，请不要移动校园卡...");
		dlg->ShowTipMessage(tipMsg, 0);
		ret = DoMend(&card, &cardinfo, pData);	
		if (RET_WF_ERROR == ret)
		{
			SetStopKey(false);
			dlg->ClearMessageLine();
			tipMsg = "写卡失败请重处理或到管理中心处理";
			dlg->AddMessageLine(tipMsg);
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(1);
			goto L_END;
		}
		else if (RET_WF_TIMEOUT == ret)
		{
			goto L_END;
		}
		response->Reset();
		response->Connect();
		response->SetRequestHeader(KS_BANK_TX_CODE,1);
		response->AddField(F_SCLOSE_EMP,"240110");											// 交易码
		response->AddField(F_LVOL0, cardinfo.cardid);										// 交易卡号	
		response->AddField(F_LSERIAL0, mend_card_function_no);
		if (response->SendRequest(3000))
 		{
			SetStopKey(false);
			dlg->ClearMessageLine();
			tipMsg = "确认交易失败请到管理中心处理";
			dlg->AddMessageLine(tipMsg);
			dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
			dlg->DisplayMessage(1);
			ret = RET_WF_ERROR;
			goto L_END;
		}
		else
		{
			SetStopKey(false);
			cardinfo.balance = pData->damt2;
			cardinfo.tx_cnt++;
			dlg->ClearMessageLine();
			tipMsg.Format("您补写前卡的金额为%.2lf元", pre_card_money);
			dlg->AddMessageLine(tipMsg, dlg->GetMaxLineNo() + 2, 0);
			tipMsg.Format("您补写后卡金额为%.2lf元", pData->damt2);
			dlg->AddMessageLine(tipMsg, dlg->GetMaxLineNo() + 2, 0);
			dlg->DisplayMessage(3);
		}		
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str());
		dlg->AddMessageLine("按[退出]返回", dlg->GetMaxLineNo() + 2, -6);
		dlg->DisplayMessage(3);	
		goto L_END;
	}

	SetStopKey(false);
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

CString CKMendCardWorkflow::GetWorkflowID()
{
	return m_key;
}

int CKMendCardWorkflow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
{
	int ret = manager->ReadCardInfo(cardinfo,
		CKSCardManager::ciCardId|CKSCardManager::ciBalance, 20);
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

int CKMendCardWorkflow::DoMend(CKSCardManager *manager,
							   KS_CARD_INFO *cardinfo, 
							   const ST_PACK *rec
							   )
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, (int)rec->damt2 * 100); // 出卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡");
		dlg->AddMessageLine("按[退出]返回",dlg->GetMaxLineNo()+2,-6);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// 查询网络收费帐户信息
//////////////////////////////////////////////////////////////////////////
CKQueryNetChargeWorkFlow::CKQueryNetChargeWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "QueryNetCharge";
}

CKQueryNetChargeWorkFlow::~CKQueryNetChargeWorkFlow(void)
{
	//
}

int CKQueryNetChargeWorkFlow::DoWork()
{
	CString strTipMsg = "";
	CDRTPHelper * drtp = NULL;
	CKSNLDlg* dlg = (CKSNLDlg*)GetMainWnd();
	KS_CARD_INFO cardinfo;
	TPublishCard updateCardInfo;
	int ret = RET_WF_ERROR;
	int recCount = 0;
	CString passwd = "";
	CString cardidstr = "";
	double dRemainBalance = 0.0;
	double dOweBalance = 0.0;
	memset(&cardinfo, 0, sizeof(cardinfo));
	memset(&updateCardInfo, 0, sizeof(updateCardInfo));
	
	dlg->ShowTipMessage("请放校园卡...",0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}

	SetStopKey(false);
	ret = card.ReadCardInfo(&cardinfo, CKSCardManager::ciCardId, 5);
	if (ret)
	{
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		goto L_END;
	}
	
	ret = card.ReadCardInformation(cardinfo.cardid, &updateCardInfo);
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                    
	}

	dlg->SetLimtText(1);
	if(dlg->InputPassword("请输入校园卡密码", passwd, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

/*
	if (card.TestCardExists(5))
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
*/
	
	dlg->ShowTipMessage("交易处理中,请等待...",1);
	cardidstr.Format("%d", cardinfo.cardid);
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
	drtp->AddField(F_SCLOSE_EMP,"240111");					
	drtp->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);			// 学工号
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)passwd);		
	drtp->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);

	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;		
	}
	
	if (drtp->SendRequest(5000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	if (drtp->HasMoreRecord())
	{
		ST_PACK *pData = drtp->GetNextRecord();	
		SetStopKey(false);
		dlg->ClearMessageLine();
		strTipMsg.Format("您的网络帐户余额为:%0.2lf", pData->damt0);
		dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(10);
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;		
	}

	dlg->ShowTipMessage("交易完成!", 0);
	ret = RET_WF_SUCCESSED;	
L_END:
	if(drtp)
		delete drtp;
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

CString CKQueryNetChargeWorkFlow::GetWorkflowID()
{
	return m_key;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 功能编号: 240112
// 功能名称: 网络收费
// 功能描述: 用户通过圈存机从大钱包扣费转钱到网络收费系统中, 完成网络上网扣费
// 业务逻辑: 1.	用户在界面输入密码, 输入卡金额.
//           2. 密码和金额传到后台，后台检查用户卡状态，卡余额，失败返回，否则发起一笔未入账交易1
//			 3.	后台将计算后的出卡值传给前台，前台写卡，写卡失败报错，否则向后台发起交易2
//           4.	后台向第三方发起充值交易，如果网络联接失败不入账，否则入账(超时也要入账)
//           5.	后台返回结果给界面，界面展示返回信息
// 相关功能: 
// 备注:	 此处添加一个写死的机房标识(现在仅仅只有一个机房, 此功能扩容时增加)
// 界面输入: 交易码(sclose_emp), 交易卡号(lvol0), 密码(semp_pwd)
//			 学工号(scust_auth), 入卡值(damt1), 网络转账费用(damt0), 终端号(sname)
// 界面输出: 网络收费帐户余额(damt0)
//////////////////////////////////////////////////////////////////////////////////////////////////

CKNetChargeTransferWorkFlow::CKNetChargeTransferWorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "NetCharge";
}

CKNetChargeTransferWorkFlow::~CKNetChargeTransferWorkFlow()
{
	//
}

CString CKNetChargeTransferWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKNetChargeTransferWorkFlow::DoWork()
{
	CString strPassword = "";
	CString strTipMsg("");
	CString strBalance = "";
	CString strMateRoomNo= "";
	CString cardidstr = "";
	CDRTPHelper *drtp = NULL;
	CDRTPHelper *response = NULL;
	KS_CARD_INFO cardinfo;
	TPublishCard updateCardInfo;
	int ret;
	int nCount = 0;
	int serial_no = 0;
	int error_code = 0;
	double card_balance = 0;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));
	memset(&updateCardInfo, 0, sizeof(updateCardInfo));

	dlg->ShowTipMessage("本功能仅限邯郸校区校内5号楼\n东区学生公寓13-16楼\n\n\n请放校园卡...", 0);
	SetStopKey(false);
	CKSCardManager card(dlg->GetConfig(), (LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	ret = ReadCard(&card, &cardinfo);
	if (ret == RET_WF_ERROR)
	{
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		return RET_WF_ERROR;
	}
	
	// 读取学工号
	ret = card.ReadCardInformation(cardinfo.cardid, &updateCardInfo);
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                   
	}

	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", strPassword, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	/*
	dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{			
		ret = RET_WF_ERROR;
		goto L_END;
	}
	*/

	dlg->SetLimtText(0);
	if (dlg->InputQuery("请输入转帐金额", "", strBalance, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	cardidstr.Format("%d", cardinfo.cardid);
	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	
	if (card.TestCardExists(5))
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}

	card_balance = cardinfo.balance;
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
//	while (true)
//	{
	SetStopKey(true);
	drtp->Reset();
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	// 后台验证卡，并且检测连接到对方数据库是否正常
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240113");
	drtp->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);	// 学工号
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)strPassword);
	drtp->AddField(F_DAMT1, cardinfo.balance);
	drtp->AddField(F_DAMT0, (LPSTR)(LPCTSTR)strBalance);
	drtp->AddField(F_LVOL3, cardinfo.tx_cnt);
	response->AddField(F_SDATE0, "cr010101");
	drtp->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);

	SetStopKey(false);
	if (drtp->SendRequest(5000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		goto L_END;
	}	
	
	if (drtp->HasMoreRecord())
	{
		ST_PACK *pData = drtp->GetNextRecord();
		strTipMsg.Format("正在写卡, 请不要移动校园卡...");
		dlg->ShowTipMessage(strTipMsg, 0);
		serial_no = pData->lvol0;
		
		ret = DoTransfer(&card, &cardinfo, pData);
		if (ret == RET_WF_ERROR)											// 写卡失败就不管了, 返回写卡失败，请重新交易
		{
			SetStopKey(false);
			strTipMsg.Format("写卡失败, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}	

		if (ret == RET_WF_TIMEOUT)
		{
			SetStopKey(false);
			strTipMsg.Format("等待放卡超时, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;		
	}
	
	if (drtp)
	{
		delete drtp;
		drtp = NULL;
	}

	SetStopKey(true);
	response->Reset();
	
	if (response->Connect())
	{
		error_code = WriteBackMoney(&card, &cardinfo, card_balance);	// 写回功能, 出现扣款失败需要将卡金额写回
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), error_code, card_balance, 0.0, 108203, response->GetErrMsg().c_str());
		dlg->ShowTipMessage(response->GetErrMsg().c_str());
		goto L_END;
	}
	
	response->SetRequestHeader(KS_BANK_TX_CODE, 1);
	response->AddField(F_SCLOSE_EMP, "240112");						    // 发起转账交易
	response->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	response->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);	// 学工号
	response->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)strPassword);
	response->AddField(F_DAMT1, cardinfo.balance);
	response->AddField(F_DAMT0, (LPSTR)(LPCTSTR)strBalance);
	response->AddField(F_LVOL3, cardinfo.tx_cnt);
	response->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);
	response->AddField(F_SDATE0, "cr010101");
//	response->AddField(F_SDATE0, (LPSTR)(LPCTSTR)dlg->GetConfig()->croom_id);
	response->AddField(F_LVOL0, serial_no);							// 流水号
	
	if (response->SendRequest(5000))
	{	
		dlg->ClearMessageLine();
		dlg->AddMessageLine(response->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), 0, 0.0, 0.0, 108204, response->GetErrMsg().c_str());
		goto L_END;
	}
	
	if (response->HasMoreRecord())
	{
		ST_PACK *pRespData = response->GetNextRecord();
		cardinfo.balance = pRespData->damt0;
		dlg->ClearMessageLine();
		SetStopKey(false);
		if (1001 == pRespData->lvol11)
		{
			strTipMsg.Format("网络收费转帐超时, 请到网络收费中心处理");	// 超时但是已经入账
		}
		else
		{
			strTipMsg.Format("您的收费金额为%s元", (LPSTR)(LPCTSTR)strBalance);
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			strTipMsg.Format("您的网络帐户余额为%0.2lf元", cardinfo.balance);
		}
		dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 3, 0);
		dlg->DisplayMessage(10);	
	}
	else
	{
		SetStopKey(false);
		dlg->ClearMessageLine();
		error_code = WriteBackMoney(&card, &cardinfo, card_balance);			// 写回功能, 出现扣款失败需要将卡金额写回
		ret = response->GetReturnCode();
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), error_code, card_balance, 0.0, ret, response->GetErrMsg().c_str());
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(response->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;
	}	
		
//		break;
//	}
	dlg->ShowTipMessage("交易完成!", 0);
	ret = RET_WF_SUCCESSED;
L_END:
	if (drtp) 
	{
		delete drtp;
		drtp = NULL;
	}
	
	if (response) 
	{
		delete response;
		response = NULL;
	}
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

int CKNetChargeTransferWorkFlow::ReadCard(CKSCardManager *manager, KS_CARD_INFO *cardinfo)
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

int CKNetChargeTransferWorkFlow::DoTransfer(CKSCardManager *manager,
							KS_CARD_INFO *cardinfo, const ST_PACK *rec)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, D2I(rec->damt1 * 100)); // 出卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡", dlg->GetMaxLineNo() + 3, 0);
//		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 2,-6);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

int CKNetChargeTransferWorkFlow::WriteBackMoney(CKSCardManager *manager,
							KS_CARD_INFO *cardinfo, double money)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, money * 100); // 入卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡", dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;			
}





//////////////////////////////////////////////////////////////////////////////////////////////////
// 功能编号: 240112
// 功能名称: 网络收费2
// 功能描述: 用户通过圈存机从大钱包扣费转钱到网络收费系统中, 完成网络上网扣费
// 业务逻辑: 1.	用户在界面输入密码, 输入卡金额.
//           2. 密码和金额传到后台，后台检查用户卡状态，卡余额，失败返回，否则发起一笔未入账交易1
//			 3.	后台将计算后的出卡值传给前台，前台写卡，写卡失败报错，否则向后台发起交易2
//           4.	后台向第三方发起充值交易，如果网络联接失败不入账，否则入账(超时也要入账)
//           5.	后台返回结果给界面，界面展示返回信息
// 相关功能: 
// 备注:	 此处添加一个写死的机房标识(现在仅仅只有一个机房, 此功能扩容时增加)
// 界面输入: 交易码(sclose_emp), 交易卡号(lvol0), 密码(semp_pwd)
//			 学工号(scust_auth), 入卡值(damt1), 网络转账费用(damt0), 终端号(sname)
// 界面输出: 网络收费帐户余额(damt0)
//////////////////////////////////////////////////////////////////////////////////////////////////

CKNetChargeTransfer2WorkFlow::CKNetChargeTransfer2WorkFlow(CDialog *dlg) : CKSWorkflow(dlg)
{
	m_key = "NetCharge2";
}

CKNetChargeTransfer2WorkFlow::~CKNetChargeTransfer2WorkFlow()
{
	//
}

CString CKNetChargeTransfer2WorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKNetChargeTransfer2WorkFlow::DoWork()
{
	CString strPassword = "";
	CString strTipMsg("");
	CString strBalance = "";
	CString strMateRoomNo= "";
	CString cardidstr = "";
	CDRTPHelper *drtp = NULL;
	CDRTPHelper *response = NULL;
	KS_CARD_INFO cardinfo;
	TPublishCard updateCardInfo;
	int ret;
	int nCount = 0;
	int serial_no = 0;
	int error_code = 0;
	double card_balance = 0;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));
	memset(&updateCardInfo, 0, sizeof(updateCardInfo));

//	dlg->ShowTipMessage("本功能仅限邯郸校区校内5号楼\n东区学生公寓13-16楼\n\n\n请放校园卡...", 0);
	SetStopKey(false);
	CKSCardManager card(dlg->GetConfig(), (LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	ret = ReadCard(&card, &cardinfo);
	if (ret == RET_WF_ERROR)
	{
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		return RET_WF_ERROR;
	}
	
	// 读取学工号
	ret = card.ReadCardInformation(cardinfo.cardid, &updateCardInfo);
	if(ret)
	{
		if(RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);
		}
		goto L_END;                                   
	}

	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", strPassword, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	/*
	dlg->ShowTipMessage("交易处理中， 请不要移动校园卡", 1);
	if (card.TestCardExists(5))
	{			
		ret = RET_WF_ERROR;
		goto L_END;
	}
	*/

	dlg->SetLimtText(0);
	if (dlg->InputQuery("请输入转帐金额", "", strBalance, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	cardidstr.Format("%d", cardinfo.cardid);
	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	
	if (card.TestCardExists(5))
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}

	card_balance = cardinfo.balance;
	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();
	response = dlg->GetConfig()->CreateDrtpHelper();
//	while (true)
//	{
	SetStopKey(true);
	drtp->Reset();
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	// 后台验证卡，并且检测连接到对方数据库是否正常
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
	drtp->AddField(F_SCLOSE_EMP, "240113");
	drtp->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);	// 学工号
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)strPassword);
	drtp->AddField(F_DAMT1, cardinfo.balance);
	drtp->AddField(F_DAMT0, (LPSTR)(LPCTSTR)strBalance);
	drtp->AddField(F_LVOL3, cardinfo.tx_cnt);
	response->AddField(F_SDATE0, "cr010102");
	drtp->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);

	SetStopKey(false);
	if (drtp->SendRequest(5000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		goto L_END;
	}	
	
	if (drtp->HasMoreRecord())
	{
		ST_PACK *pData = drtp->GetNextRecord();
		strTipMsg.Format("正在写卡, 请不要移动校园卡...");
		dlg->ShowTipMessage(strTipMsg, 0);
		serial_no = pData->lvol0;
		
		ret = DoTransfer(&card, &cardinfo, pData);
		if (ret == RET_WF_ERROR)											// 写卡失败就不管了, 返回写卡失败，请重新交易
		{
			SetStopKey(false);
			strTipMsg.Format("写卡失败, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}	

		if (ret == RET_WF_TIMEOUT)
		{
			SetStopKey(false);
			strTipMsg.Format("等待放卡超时, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;		
	}
	
	if (drtp)
	{
		delete drtp;
		drtp = NULL;
	}

	SetStopKey(true);
	response->Reset();
	
	if (response->Connect())
	{
		error_code = WriteBackMoney(&card, &cardinfo, card_balance);	// 写回功能, 出现扣款失败需要将卡金额写回
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), error_code, card_balance, 0.0, 108203, response->GetErrMsg().c_str());
		dlg->ShowTipMessage(response->GetErrMsg().c_str());
		goto L_END;
	}
	
	response->SetRequestHeader(KS_BANK_TX_CODE, 1);
	response->AddField(F_SCLOSE_EMP, "240112");						    // 发起转账交易
	response->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	response->AddField(F_SCUST_AUTH, (char*)updateCardInfo.ucCardNo);	// 学工号
	response->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)strPassword);
	response->AddField(F_DAMT1, cardinfo.balance);
	response->AddField(F_DAMT0, (LPSTR)(LPCTSTR)strBalance);
	response->AddField(F_LVOL3, cardinfo.tx_cnt);
	response->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);
	response->AddField(F_SDATE0, "cr010102");
//	response->AddField(F_SDATE0, (LPSTR)(LPCTSTR)dlg->GetConfig()->croom_id);
	response->AddField(F_LVOL0, serial_no);							// 流水号
	
	if (response->SendRequest(5000))
	{	
		dlg->ClearMessageLine();
		dlg->AddMessageLine(response->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), 0, 0.0, 0.0, 108204, response->GetErrMsg().c_str());
		goto L_END;
	}
	
	if (response->HasMoreRecord())
	{
		ST_PACK *pRespData = response->GetNextRecord();
		cardinfo.balance = pRespData->damt0;
		dlg->ClearMessageLine();
		SetStopKey(false);
		if (1001 == pRespData->lvol11)
		{
			strTipMsg.Format("网络收费转帐超时, 请到网络收费中心处理");	// 超时但是已经入账
		}
		else
		{
			strTipMsg.Format("您的收费金额为%s元", (LPSTR)(LPCTSTR)strBalance);
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			strTipMsg.Format("您的网络帐户余额为%0.2lf元", cardinfo.balance);
		}
		dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 3, 0);
		dlg->DisplayMessage(10);	
	}
	else
	{
		SetStopKey(false);
		dlg->ClearMessageLine();
		error_code = WriteBackMoney(&card, &cardinfo, card_balance);			// 写回功能, 出现扣款失败需要将卡金额写回
		ret = response->GetReturnCode();
		WriteLogFile(atoi((LPSTR)(LPCTSTR)cardidstr), error_code, card_balance, 0.0, ret, response->GetErrMsg().c_str());
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(response->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;
	}	
		
//		break;
//	}
	dlg->ShowTipMessage("交易完成!", 0);
	ret = RET_WF_SUCCESSED;
L_END:
	if (drtp) 
	{
		delete drtp;
		drtp = NULL;
	}
	
	if (response) 
	{
		delete response;
		response = NULL;
	}
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

int CKNetChargeTransfer2WorkFlow::ReadCard(CKSCardManager *manager, KS_CARD_INFO *cardinfo)
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

int CKNetChargeTransfer2WorkFlow::DoTransfer(CKSCardManager *manager,
							KS_CARD_INFO *cardinfo, const ST_PACK *rec)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, D2I(rec->damt1 * 100)); // 出卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡", dlg->GetMaxLineNo() + 3, 0);
//		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 2,-6);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}

int CKNetChargeTransfer2WorkFlow::WriteBackMoney(CKSCardManager *manager,
							KS_CARD_INFO *cardinfo, double money)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, money * 100); // 入卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡", dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;			
}












//////////////////////////////////////////////////////////////////////////
// 剩余搭伙费清算收费
//////////////////////////////////////////////////////////////////////////
CKRemainBoardReckonWorkFlow::CKRemainBoardReckonWorkFlow(CDialog * dlg):
	CKSWorkflow(dlg)
{
	m_key = "board_reckon";
}

CKRemainBoardReckonWorkFlow::~CKRemainBoardReckonWorkFlow()
{
	// 
}

int CKRemainBoardReckonWorkFlow::DoWork()
{
	
	CString strPassword = "";
	CString strTipMsg("");
	CString strBalance = "";
	CString cardidstr = "";
	CString cs = "";
	CDRTPHelper *drtp = NULL;
	KS_CARD_INFO cardinfo;
	int ret;
	int nCount = 0;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));

	dlg->ShowTipMessage("请放校园卡...\n", 0);
	SetStopKey(false);
	CKSCardManager card(dlg->GetConfig(), (LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey, this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}

	ret = ReadCard(&card, &cardinfo);
	if (ret == RET_WF_ERROR)
	{
		dlg->ShowTipMessage(card.GetErrMsg(), 1);
		return RET_WF_ERROR;
	}

	dlg->SetLimtText(1);
	if (dlg->InputPassword("请输入校园卡密码", strPassword, 10) != 0)
	{
		ret = RET_WF_TIMEOUT;
		goto L_END;
	}

	dlg->ShowTipMessage("交易处理中, 请不要移动校园卡", 1);
	
	if (card.TestCardExists(5))
	{
		ret = RET_WF_ERROR;
		goto L_END;
	}
	
	cardidstr.Format("%d",cardinfo.cardid);

	ret = RET_WF_ERROR;
	drtp = dlg->GetConfig()->CreateDrtpHelper();

	SetStopKey(true);
	drtp->Reset();
	if (drtp->Connect())
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str());
		goto L_END;
	}
	
	drtp->SetRequestHeader(KS_BANK_TX_CODE, 1);
//	drtp->SetRequestHeader(249999, 1);
	drtp->AddField(F_SCLOSE_EMP, "240116");
	drtp->AddField(F_SSERIAL0, (LPSTR)(LPCTSTR)cardidstr);
	drtp->AddField(F_SEMP_PWD, (LPSTR)(LPCTSTR)strPassword);
	drtp->AddField(F_DAMT0, cardinfo.balance);
	drtp->AddField(F_LVOL3, cardinfo.tx_cnt);
	drtp->AddField(F_SORDER2, (LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);
	
	SetStopKey(false);
	if (drtp->SendRequest(5000))
	{
		dlg->ClearMessageLine();
		dlg->AddMessageLine(drtp->GetErrMsg().c_str(), dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(2);
		goto L_END;
	}	
	
	if (drtp->GetReturnCode())
	{
		dlg->ShowTipMessage(drtp->GetReturnMsg().c_str());
		ret = RET_WF_ERROR;
		goto L_END;
	}

	if (drtp->HasMoreRecord())
	{
		ST_PACK *pData = drtp->GetNextRecord();
		strTipMsg.Format("正在写卡, 请不要移动校园卡...");
		dlg->ShowTipMessage(strTipMsg, 0);
		
		ret = DoWriteCard(&card, &cardinfo, pData);
		if (ret == RET_WF_ERROR)
		{
			SetStopKey(false);
			strTipMsg.Format("写卡失败, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}	

		if (ret == RET_WF_TIMEOUT)
		{
			SetStopKey(false);
			strTipMsg.Format("等待放卡超时, 请重新进行交易");
			dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 2, 0);
			goto L_END;
		}

		dlg->AddMessageLine("搭伙费余额清算完毕", dlg->GetMaxLineNo() + 2, 0);
		strTipMsg.Format("您的当前卡余额为:%0.2lf元", pData->damt0);
		dlg->AddMessageLine(strTipMsg, dlg->GetMaxLineNo() + 1, 0);
		dlg->AddMessageLine("请按[退出]返回", dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(10);
	}
	else
	{
		dlg->ClearMessageLine();
		ret = drtp->GetReturnCode();
		if(ret != ERR_NOT_LOGIN)
			ret = RET_WF_TIMEOUT;
		dlg->AddMessageLine(drtp->GetReturnMsg().c_str(), dlg->GetMaxLineNo() + 2, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(3);
		goto L_END;		
	}

	dlg->ShowTipMessage("交易完成!", 0);
	ret = RET_WF_SUCCESSED;
L_END:
	if (drtp) {delete drtp;}
	card.CloseCOM();
	SetStopKey(false);
	return ret;
}

CString CKRemainBoardReckonWorkFlow::GetWorkflowID()
{
	return m_key;
}

int CKRemainBoardReckonWorkFlow::ReadCard(CKSCardManager* manager,KS_CARD_INFO *cardinfo)
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

int CKRemainBoardReckonWorkFlow::DoWriteCard(CKSCardManager* manager,
								  KS_CARD_INFO *cardinfo,const ST_PACK *rec)
{
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	int ret;
	int retries = 3;
	while (--retries >= 0)
	{
		// 检测卡
		if (manager->TestCardExists(5))
		{
			continue;
		}
		ret = manager->SetMoney(cardinfo->cardid, rec->damt0 * 100); // 出卡值
		if (!ret)
		{
			return RET_WF_SUCCESSED;
		}
		if (manager->GetErrNo() == ERR_USER_CANCEL)
		{
			return RET_WF_TIMEOUT;
		}
		
		dlg->ClearMessageLine();
		dlg->AddMessageLine("写卡失败，请重放校园卡", dlg->GetMaxLineNo() + 3, 0);
		dlg->AddMessageLine("请按[退出]返回",dlg->GetMaxLineNo() + 4, 0);
		dlg->DisplayMessage(1);
	}
	return RET_WF_ERROR;
}