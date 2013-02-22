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
	// ���У԰���������״̬
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
	// ��У԰��
	dlg->ShowTipMessage("���У԰��...", 0);
	CKSCardManager card(dlg->GetConfig(),
		(LPSTR)(LPCTSTR)dlg->GetConfig()->m_workKey,this);
	if (card.OpenCOM() != 0)
	{
		dlg->ShowTipMessage(card.GetErrMsg());
		return RET_WF_ERROR;
	}
	// ��ȡ����Ϣ
	ret = card.ReadCard(&cardinfo,CKSCardManager::ciCardId|CKSCardManager::ciPhyId);
	if (ret)
	{
		if (RET_WF_ERROR == ret)
		{
			dlg->ShowTipMessage(card.GetErrMsg(), 1);					// �޸Ĺ�
		}
		return card.GetErrNo();
	}
	ret = dlg->InputPassword("������У԰������",pswd,10);
	if(ret)
	{
		return RET_WF_ERROR;
	}
	// TODO : ��ȡ������
	SetStopKey(true);
	dlg->AddMessageLine("��ˢ���п�...",dlg->GetMaxLineNo()+1,3);
	dlg->DisplayMessage(3);
	ret = bankreader.open();
	if(ret)
	{
		dlg->ShowTipMessage("��������ʼ��ʧ��!");
		return RET_WF_ERROR;
	}
	ret = bankreader.ReadBankCard(15,bankno);
	if(ret)
	{
		dlg->ShowTipMessage("�����п���Ϣʧ��");
		return RET_WF_ERROR;
	}
	bankreader.close();

	SetStopKey(false);
	dlg->AddMessageLine("������ͨ��,����[ȷ��]...",dlg->GetMaxLineNo(), 2);
	// TDO : �����ͨ
	ret = advanstacard.open();
	if(ret)
	{
		dlg->AddMessageLine("��ʼ�����ͨ������ʧ��.", dlg->GetMaxLineNo() + 1, 0);
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
		DEBUG_LOG(("һ��ͨ��������[%u]���ͨ����[%u]",phyid,purch.dwPhysicalID));
		dlg->ShowTipMessage("У԰�������ͨ������ͬһ�ſ�!");
		return RET_WF_ERROR;
	}
	SetStopKey(false);
	sprintf(temp,"�������ͨ��ǰ����� %.2fԪ",D4U5(purch.dwBalance / 100.0,2));
	dlg->AddMessageLine(temp,dlg->GetMaxLineNo()+1,1);
	dlg->AddMessageLine("�����밴[ȷ��]��...",dlg->GetMaxLineNo()+2,0);
	if(dlg->Confirm(10) != IDOK)
	{
		return RET_WF_TIMEOUT;
	}

	retries = 3;
	while(retries-->0)
	{
		if(dlg->InputQuery("������ת�˽��(Ԫ)","",str,10))
		{
			return RET_WF_TIMEOUT;
		}
		trade_money = atoi((LPCTSTR)str);
		if(trade_money <= 0)
		{
			dlg->ShowTipMessage("��������Ч,����������...",3);
			continue;
		}
		// TODO : �������ͨ��ֵ�޶���ж�
		break;
	}
	if(retries == 0)
	{
		return RET_WF_ERROR;
	}
	dlg->ShowTipMessage("���ڴ�����,�벻Ҫ�ƶ���Ƭ...",15);
	// ��ʼ�����̨����
	CDRTPHelper *drtp;
	drtp = dlg->GetConfig()->CreateDrtpHelper();

	drtp->SetRequestHeader(900077,1);
	drtp->AddField(F_SCLOSE_EMP,"242002"); // ���ͨ
	drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // �ն˺�
	memset(temp,0,sizeof temp);
	GetCurrentDatetime(temp);
	drtp->AddField(F_SDATE0,temp,8); // ����ʱ��
	drtp->AddField(F_STIME0,temp+8,6);
	sprintf(temp,"%d",cardinfo.cardid);
	drtp->AddField(F_SSERIAL0,temp); // ���׿���
	drtp->AddField(F_SCUST_AUTH,bankno); // ���п���
	sprintf(temp,"%d",trade_money*100); // ת�˽��,��
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
			dlg->AddMessageLine("���ͨδ����,���鲢��[ȷ��]",dlg->GetMaxLineNo()+1,1);
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
			dlg->ShowTipMessage("��ʹ�õĲ���ͬһ�����ͨ��!");
			ret = RET_WF_ERROR;
		}
		else if((ret = DoSendRequest(drtp)))
		{
			DEBUG_LOG(("У԰��[%d]���ͨת��ʧ��!",cardinfo.cardid));
		}
#if 1
		else if((ret = advanstacard.Increment(trade_money*100,temp,&purch_inc))==0)
#else
		else if(0)
#endif
		{
			// ��������ɹ�д��
			int serial_no;
			if(drtp->HasMoreRecord())
			{
				ST_PACK *data = drtp->GetNextRecord();
				serial_no = data->lvol1;
			}
			sprintf(temp,"��ֵ�ɹ�,�������ͨ���Ϊ %.02fԪ",D4U5(purch_inc.dwSithBalance/100.0,2));
			dlg->ShowTipMessage(temp,7);
			sprintf(temp,"���ͨ��ֵ�ɹ�,У԰����[%d]����[%d],���[%d],��ˮ��[%d]",
				cardinfo.cardid,purch_inc.dwPhysicalID,purch_inc.dwSithBalance,serial_no);
			DEBUG_LOG((temp));
			ret = RET_WF_SUCCESSED;
		}
		else
		{
			dlg->ShowTipMessage("д���ͨʧ��,ϵͳ�Զ�������...",1);
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
				drtp->AddField(F_LVOL1,serial_no); // ��ˮ��
				drtp->AddField(F_SDATE0,logic_date); // ��������
				drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // �ն˺�
				retries = 5;
				while(retries-->0)
				{
					ret = DoSendRequest(drtp);
					if(ret)
					{
						dlg->ShowTipMessage("ϵͳ���ڴ���ҵ��,���Ժ�...",0);
						Sleep(200);
						continue;
					}
					sprintf(temp,"У԰����[%d],���ͨ��ֵ��ˮ[%d]�ɹ�����",cardinfo.cardid,serial_no);
					DEBUG_LOG((temp));
					dlg->ShowTipMessage("ϵͳ�����ɹ�",3);
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
		sprintf(temp,"���ش���:%d:%s",drtp->GetReturnCode(),drtp->GetReturnMsg().c_str());
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
		dlg->ShowTipMessage("��ʼ��������ʧ��!",4);
		return RET_WF_ERROR;
	}
	dlg->ShowTipMessage("��ˢ���п�...",1);
	ret = bankreader.ReadBankCard(15,bankno);
	if(ret)
	{
		dlg->ShowTipMessage("���п���ȡ����!");
		return RET_WF_ERROR;
	}
	dlg->m_sizeFlag = 4;
	if(dlg->InputPassword("���������Ǯ������",pswd,15))
	{
		dlg->m_sizeFlag = 6;
		dlg->ShowTipMessage("�������",4);
		return RET_WF_ERROR;
	}
	dlg->m_sizeFlag = 6;
	retries = 3;
	while(retries-->0)
	{
		if(dlg->InputQuery("������ת�˽��(Ԫ)","",str,10))
		{
			return RET_WF_ERROR;
		}
		trade_money = atoi((LPCTSTR)str);
		if(trade_money <= 0)
		{
			dlg->ShowTipMessage("����������,����������...",3);
			Sleep(1000);
			continue;
		}
		break;
	}
	if(retries <= 0)
		return RET_WF_ERROR;
	CDRTPHelper *drtp = dlg->GetConfig()->CreateDrtpHelper();
	drtp->SetRequestHeader(900077,1);
	drtp->AddField(F_SCLOSE_EMP,"242001"); // ����Ǯ��
	drtp->AddField(F_SORDER2,dlg->GetConfig()->m_systemNo); // �ն˺�
	memset(temp,0,sizeof temp);
	GetCurrentDatetime(temp);
	drtp->AddField(F_SDATE0,temp,8); // ����ʱ��
	drtp->AddField(F_STIME0,temp+8,6);
	drtp->AddField(F_SCUST_AUTH,bankno); // ���п���
	sprintf(temp,"%d",trade_money*100); // ת�˽��,��
	drtp->AddField(F_SORDER0,temp);
	drtp->AddField(F_SEMP_PWD,(LPCTSTR)pswd); // ����Ǯ������
	if((ret = DoSendRequest(drtp)))
	{
		DEBUG_LOG(("���п�[%s]����Ǯ��ת��ʧ��!",bankno));
	}
	else
	{
		if(drtp->HasMoreRecord())
		{
			ST_PACK *data = drtp->GetNextRecord();
			sprintf(temp,"ת�˳ɹ�,������Ǯ���˻����Ϊ %.02fԪ",D4U5(atoi(data->sserial1),2));
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
		sprintf(temp,"���ش���:%d:%s",drtp->GetReturnCode(),drtp->GetReturnMsg().c_str());
		dlg->ShowTipMessage(temp,5);
		return RET_WF_ERROR;
	}
	return 0;
}