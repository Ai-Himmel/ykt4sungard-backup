#include "StdAfx.h"
#include "wf_gzdxc.h"
#include "ksnl.h"
#include <exception>
#include ".\ksworkflow.h"
#include "KSInputDialog.h"
#include "KSNLDlg.h"
#include "KSCardManager.h"
#include "DRTPHelper.h"
#include "ksutil.h"
#include "bankreader.h"
#include "AdvanstaCard.h"
#include "logfile.h"


CGZYCTTransWorkFlow::CGZYCTTransWorkFlow(CDialog *dlg)
:CKSWorkflow(dlg)
{
	m_key = _T("GZYCTTransfer");
}
CGZYCTTransWorkFlow::~CGZYCTTransWorkFlow()
{
	// empty
}
CString CGZYCTTransWorkFlow::GetWorkflowID()
{
	return m_key;
}
int CGZYCTTransWorkFlow::DoWork()
{
	// 检查校园卡与磁条卡状态
	int ret;
	KS_CARD_INFO cardinfo;
	KSBankReader bankreader;
	KSAdvanstaCard advanstacard;
	char bankno[30] = "";
	char temp[128] = "";
	int retries,trade_money;
	CString str,pswd;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	memset(&cardinfo, 0, sizeof(cardinfo));
	SetStopKey(false);
	// 读校园卡
	dlg->ShowTipMessage("请放校园卡...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	// 读取卡信息
	ret = card.ReadCard(&cardinfo,CKSCardManager::ciCardId|CKSCardManager::ciPhyId);
	if (ret)
	{
		if (RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);					// 修改过
		}
		return card.GetErrNo();
	}
	ret = dlg->InputPassword("请输入校园卡密码",pswd,10);
	if(ret)
	{
		return RET_WF_ERROR;
	}
	// TODO : 读取磁条卡
	SetStopKey(true);
	dlg->AddMessageLine("请刷银行卡...",dlg->GetMaxLineNo()+1,3);
	dlg->DisplayMessage(3);
	ret = bankreader.open();
	if(ret)
	{
		dlg->ShowTipMessage("读卡器初始化失败!");
		return RET_WF_ERROR;
	}
	ret = bankreader.ReadBankCard(15,bankno);
	if(ret)
	{
		dlg->ShowTipMessage("读银行卡信息失败");
		return RET_WF_ERROR;
	}
	bankreader.close();

	SetStopKey(false);
	dlg->AddMessageLine("请放羊城通卡,并按[确定]...",dlg->GetMaxLineNo(), 2);
	// TDO : 读羊城通
	ret = advanstacard.open();
	if(ret)
	{
		dlg->AddMessageLine("初始化羊城通读卡器失败.", dlg->GetMaxLineNo() + 1, 0);
		dlg->AddMessageLine(advanstacard.GetErrMsg(),dlg->GetMaxLineNo() + 3, 0);
		dlg->DisplayMessage(10);	
		return RET_WF_ERROR;
	}
	if(dlg->Confirm(9) != IDOK)
	{
		return RET_WF_TIMEOUT;
	}
	SetStopKey(true);
	PURCHSEARCH purch;
	memset(&purch,0,sizeof purch);
	ret = advanstacard.ReadBalance(&purch);
	if(ret)
	{
		dlg->ShowTipMessage(advanstacard.GetErrMsg(),5);
		return RET_WF_ERROR;
	}
	//strncpy(temp,(char *)cardinfo.phyid,8);
	UINT phyid = ConvertPhyCardId((const char *)cardinfo.phyid);
	if(purch.dwPhysicalID != phyid)
	{
		DEBUG_LOG(("一卡通中物理卡号[%u]羊城通卡号[%u]",phyid,purch.dwPhysicalID));
		dlg->ShowTipMessage("校园卡与羊城通卡不是同一张卡!");
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	sprintf(temp,"您的羊城通当前余额是 %.2f元",D4U5(purch.dwBalance / 100.0,2));
	dlg->AddMessageLine(temp,dlg->GetMaxLineNo()+1,1);
	dlg->AddMessageLine("继续请按[确定]键...",dlg->GetMaxLineNo()+2,0);
	if(dlg->Confirm(10) != IDOK)
	{
		return RET_WF_TIMEOUT;
	}

	retries = 3;
	while(retries-->0)
	{
		if(dlg->InputQuery("请输入转账金额(元)","",str,10))
		{
			return RET_WF_TIMEOUT;
		}
		trade_money = atoi((LPCTSTR)str);
		if(trade_money <= 0)
		{
			dlg->ShowTipMessage("输入金额有效,请重新输入...",3);
			continue;
		}
		// TODO : 增加羊城通充值限额的判断
		break;
	}
	if(retries == 0)
	{
		return RET_WF_ERROR;
	}
	dlg->ShowTipMessage("正在处理交易,请不要移动卡片...",15);
	// 开始处理后台请求
	CDRTPHelper *drtp;
	drtp = dlg->GetConfig()->CreateDrtpHelper();

	drtp->SetRequestHeader(900077,1);
	drtp->AddField(F_SCLOSE_EMP,"242002"); // 羊城通
	drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // 终端号
	memset(temp,0,sizeof temp);
	GetCurrentDatetime(temp);
	drtp->AddField(F_SDATE0,temp,8); // 日期时间
	drtp->AddField(F_STIME0,temp+8,6);
	sprintf(temp,"%d",cardinfo.cardid);
	drtp->AddField(F_SSERIAL0,temp); // 交易卡号
	drtp->AddField(F_SCUST_AUTH,bankno); // 银行卡号
	sprintf(temp,"%d",trade_money*100); // 转账金额,分
	drtp->AddField(F_SORDER0,temp);
	drtp->AddField(F_SEMP_PWD,(LPCTSTR)pswd);
	
	PURCHSEARCH purch_again;
	retries = 3;
	while(retries-->0)
	{
		memset(&purch_again,0,sizeof purch_again);
		ret = advanstacard.ReadBalance(&purch_again);
		if(ret)
		{
			dlg->AddMessageLine("羊城通未放置,请检查并按[确定]",dlg->GetMaxLineNo()+1,1);
			if(dlg->Confirm(5) == IDOK)
				break;
			continue;
		}
		break;
	}
	if(retries >0 )
	{
		PURCHASEINCREASE purch_inc;			
		memset(&purch_inc,0,sizeof purch_inc);
		if(purch_again.dwPhysicalID != purch.dwPhysicalID)
		{
			dlg->ShowTipMessage("您使用的不是同一张羊城通卡!");
			ret = RET_WF_ERROR;
		}
		else if((ret = DoSendRequest(drtp)))
		{
			DEBUG_LOG(("校园卡[%d]羊城通转账失败!",cardinfo.cardid));
		}
#if 1
		else if((ret = advanstacard.Increment(trade_money*100,temp,&purch_inc))==0)
#else
		else if(0)
#endif
		{
			// 发送请求成功写卡
			int serial_no;
			if(drtp->HasMoreRecord())
			{
				ST_PACK *data = drtp->GetNextRecord();
				serial_no = data->lvol1;
			}
			sprintf(temp,"充值成功,您的羊城通余额为 %.02f元",D4U5(purch_inc.dwSithBalance/100.0,2));
			dlg->ShowTipMessage(temp,7);
			sprintf(temp,"羊城通充值成功,校园卡号[%d]卡号[%d],余额[%d],流水号[%d]",
				cardinfo.cardid,purch_inc.dwPhysicalID,purch_inc.dwSithBalance,serial_no);
			DEBUG_LOG((temp));
			ret = RET_WF_SUCCESSED;
		}
		else
		{
			dlg->ShowTipMessage("写羊城通失败,系统自动冲正中...",1);
			int serial_no;
			char logic_date[9] = "";
			if(drtp->HasMoreRecord())
			{
				ST_PACK *data = drtp->GetNextRecord();
				serial_no = data->lvol1;
				strncpy(logic_date,data->sdate0,8);
				drtp->Reset();
				drtp->SetRequestHeader(900077,1);
				drtp->AddField(F_SCLOSE_EMP,"240003");
				drtp->AddField(F_LVOL1,serial_no); // 流水号
				drtp->AddField(F_SDATE0,logic_date); // 记账日期
				drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // 终端号
				retries = 5;
				while(retries-->0)
				{
					ret = DoSendRequest(drtp);
					if(ret)
					{
						dlg->ShowTipMessage("系统正在处理业务,请稍候...",0);
						Sleep(200);
						continue;
					}
					sprintf(temp,"校园卡号[%d],羊城通充值流水[%d]成功冲正",cardinfo.cardid,serial_no);
					DEBUG_LOG((temp));
					dlg->ShowTipMessage("系统冲正成功",3);
					break;
				}
				if(retries <= 0)
				{
					ret = RET_WF_ERROR;
				}
			}
			else
			{
				ret = RET_WF_ERROR;
			}
			
		}
	}
	else
	{
		ret = RET_WF_ERROR;
	}
	delete drtp;
	return ret;
}

int CGZYCTTransWorkFlow::DoSendRequest(CDRTPHelper *drtp)
{
	char temp[256] = "";
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();

	if(drtp->Connect())
	{
		return RET_WF_ERROR;	
	}
	if(drtp->SendRequest(5000))
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str(),5);
		return RET_WF_ERROR;
	}
	if(drtp->GetReturnCode())
	{
		sprintf(temp,"返回错误:%d:%s",drtp->GetReturnCode(),drtp->GetReturnMsg().c_str());
		dlg->ShowTipMessage(temp,5);
		return RET_WF_ERROR;
	}
	return 0;
}



CGZElecTransWorkFlow::CGZElecTransWorkFlow(CDialog *dlg)
:CKSWorkflow(dlg)
{
	//
	m_key = _T("GZELECTransfer");
}
CGZElecTransWorkFlow::~CGZElecTransWorkFlow()
{
	//
}
CString CGZElecTransWorkFlow::GetWorkflowID()
{
	return m_key;
}
int CGZElecTransWorkFlow::DoWork()
{
	int ret,retries,trade_money;
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();
	KSBankReader bankreader;
	char bankno[30] = "";
	char temp[128] = "";
	CString str,pswd;
	ret = bankreader.open();
	if(ret)
	{
		dlg->ShowTipMessage("初始化读卡器失败!",4);
		return RET_WF_ERROR;
	}
	dlg->ShowTipMessage("请刷银行卡...",1);
	ret = bankreader.ReadBankCard(15,bankno);
	if(ret)
	{
		dlg->ShowTipMessage("银行卡读取错误!");
		return RET_WF_ERROR;
	}
	dlg->m_sizeFlag = 4;
	if(dlg->InputPassword("请输入电子钱包密码",pswd,15))
	{
		dlg->m_sizeFlag = 6;
		dlg->ShowTipMessage("输入错误",4);
		return RET_WF_ERROR;
	}
	dlg->m_sizeFlag = 6;
	retries = 3;
	while(retries-->0)
	{
		if(dlg->InputQuery("请输入转账金额(元)","",str,10))
		{
			return RET_WF_ERROR;
		}
		trade_money = atoi((LPCTSTR)str);
		if(trade_money <= 0)
		{
			dlg->ShowTipMessage("输入金额有误,请重新输入...",3);
			Sleep(1000);
			continue;
		}
		break;
	}
	if(retries <= 0)
		return RET_WF_ERROR;
	CDRTPHelper *drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(900077,1);
	drtp->AddField(F_SCLOSE_EMP,"242001"); // 电子钱包
	drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // 终端号
	memset(temp,0,sizeof temp);
	GetCurrentDatetime(temp);
	drtp->AddField(F_SDATE0,temp,8); // 日期时间
	drtp->AddField(F_STIME0,temp+8,6);
	drtp->AddField(F_SCUST_AUTH,bankno); // 银行卡号
	sprintf(temp,"%d",trade_money*100); // 转账金额,分
	drtp->AddField(F_SORDER0,temp);
	drtp->AddField(F_SEMP_PWD,(LPCTSTR)pswd); // 电子钱包密码
	if((ret = DoSendRequest(drtp)))
	{
		DEBUG_LOG(("银行卡[%s]电子钱包转账失败!",bankno));
	}
	else
	{
		if(drtp->HasMoreRecord())
		{
			ST_PACK *data = drtp->GetNextRecord();
			sprintf(temp,"转账成功,您电子钱包账户余额为 %.02f元",D4U5(atoi(data->sserial1),2));
		}
		dlg->ShowTipMessage(temp,10);
		ret = RET_WF_SUCCESSED;
	}
	return ret;
}
int CGZElecTransWorkFlow::DoSendRequest(CDRTPHelper *drtp)
{
	char temp[256] = "";
	CKSNLDlg *dlg = (CKSNLDlg*)GetMainWnd();

	if(drtp->Connect())
	{
		return RET_WF_ERROR;	
	}
	if(drtp->SendRequest(5000))
	{
		dlg->ShowTipMessage(drtp->GetErrMsg().c_str(),5);
		return RET_WF_ERROR;
	}
	if(drtp->GetReturnCode())
	{
		sprintf(temp,"返回错误:%d:%s",drtp->GetReturnCode(),drtp->GetReturnMsg().c_str());
		dlg->ShowTipMessage(temp,5);
		return RET_WF_ERROR;
	}
	return 0;
}