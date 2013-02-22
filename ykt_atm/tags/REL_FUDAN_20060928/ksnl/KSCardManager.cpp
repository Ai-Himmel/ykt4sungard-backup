#include "stdafx.h"
#include ".\kscardmanager.h"
#include "KSConfig.h"
#include "KSWorkflow.h"

//////////////////////////////////////////////////////////////////////////
// KSCardCom ����
static HINSTANCE gsKSComHandle = NULL;

DEF_KSFUNC(Load_Dll);
DEF_KSFUNC(Load_WorkKey);
DEF_KSFUNC(PacketAddMoney);
DEF_KSFUNC(PacketDecMoney);
DEF_KSFUNC(PacketSetMoney);
DEF_KSFUNC(ReadBalance);
DEF_KSFUNC(ReadCardNo);
DEF_KSFUNC(SetBlackCardFlag);
DEF_KSFUNC(ComInit);
DEF_KSFUNC(COMClose);
DEF_KSFUNC(ReadSerial);
DEF_KSFUNC(SetNormalFlag);
DEF_KSFUNC(ChangePassWord);
DEF_KSFUNC(UpdateCardInfo);
DEF_KSFUNC(ReadInfoFromCard);

//////////////////////////////////////////////////////////////////////////
// �����������Ϣ����

static struct {
    int errcode;
	const char * errmsg;
}gs_errMap[] = {
	{ERR_LOADKSCOM_DLL,"����KS��̬��ʧ��"},
	{ERR_READCARDID,"��ȡ����ʧ��"},
	{ERR_READBALANCE,"��ȡ�����ʧ��"},
	{ERR_CARD_NOT_CONSIST,"���Ų�һ��"},
	{ERR_LOAD_FUNC,"������ں���ʧ��"},
	{ERR_SUCCEEDED,"�ɹ�"},
	{ERR_OPEN_COM,"�򿪴���ʧ��"},
	{ERR_CLOSE_COM,"�رմ���ʧ��"},
	{ERR_COM_NOT_OPEN,"����δ��"},
	{ERR_CARD_NOT_EXIST,"δ�ſ�"},
	{ERR_PACKAGE_SET_MONEY,"д�����ʧ��"},
	{ERR_USER_CANCEL,"�û�ȡ��"},
	{ERR_MODIFY_CARD, "���¿���Ϣʧ��"},
	{ERR_READ_CARDINFO, "��ȡ����Ϣʧ��"},
	{-1,NULL}
};

//////////////////////////////////////////////////////////////////////////
// CKSCardManager static member
int CKSCardManager::ciCardId = 0x01;
int CKSCardManager::ciPhyId = 0x02;
int CKSCardManager::ciPswd = 0x04;
int CKSCardManager::ciBalance = 0x08;
int CKSCardManager::ciAllInfo = 0x0F;

bool CKSCardManager::ms_isComOpen = false;
CEvent CKSCardManager::ms_testCardEvent;
CEvent CKSCardManager::ms_cancelEvent;
const int CKSCardManager::ms_globalPackageNo = 1;

//////////////////////////////////////////////////////////////////////////
// 
#if 1
#define TEST_COM_OPEN \
	if(!CKSCardManager::ms_isComOpen) { this->m_errno = ERR_COM_NOT_OPEN;return -1;}
#else
#define TEST_COM_OPEN
#endif

//////////////////////////////////////////////////////////////////////////
// CKSCardManager ����
CKSCardManager::CKSCardManager(CKSConfig * config,const char* workKey,CKSWorkflow * workflow)
:m_config(config),m_errno(ERR_SUCCEEDED),m_workflow(workflow)
{
	strncpy(m_workKey,workKey,sizeof m_workKey);
	if(LoadKSCom())
	{
		AfxMessageBox("����KSComʧ��");
	}
}

CKSCardManager::~CKSCardManager(void)
{
	ReleaseKSCom();
}

DWORD CKSCardManager::GetLastKey()
{
	if(m_workflow)
	{
		return m_workflow->GetLastKeyCode();
	}
	return -1;
}
int CKSCardManager::ReadCardInfo(KS_CARD_INFO * cardinfo,int ciBit,int timeout/*=-1*/)
{
	TEST_COM_OPEN;
	if(TestCardExists(timeout))
	{
		return -1;
	}
	KS_CARD_INFO tmp;
	memcpy(&tmp,cardinfo,sizeof tmp);
	int buf1[1],buf2[1];
	if(ciBit & ciCardId)
	{
		if(ReadCardNo(buf1) != 0)
		{
			m_errno = ERR_READCARDID;
			return -1;
		}
		tmp.cardid = buf1[0];
	}
	if(ciBit & ciBalance)
	{
		if(ReadBalance(1,buf1,buf2)!=0)
		{
			m_errno = ERR_READBALANCE;
			return -1;
		}
		tmp.balance = (double)buf1[0] / 100;
		tmp.tx_cnt = buf2[0];
		
	}
	m_errno = ERR_SUCCEEDED;
	memcpy(cardinfo,&tmp,sizeof(KS_CARD_INFO));
	return 0;
}
int CKSCardManager::AddMoney(int cardid,int money)
{
	TEST_COM_OPEN;
	if(TestCardExists(10))
	{
		return -1;
	}
	KS_CARD_INFO cardinfo;
	memset(&cardinfo,0,sizeof cardinfo);
	if(ReadCardInfo(&cardinfo,ciCardId) != 0)
	{
		return -1;
	}
	if(cardinfo.cardid != cardid)
	{
		m_errno = ERR_CARD_NOT_CONSIST;
		return -1;
	}
	if(money > 0)
	{
		if(PacketAddMoney(ms_globalPackageNo,money) != 0)
		{
			m_errno = ERR_PACKAGE_ADD_MONEY;
			return -1;
		}
	}
	else if(money < 0)
	{
		if(PacketDecMoney(ms_globalPackageNo,abs(money)) != 0)
		{
			m_errno = ERR_PACKAGE_DEC_MONEY;
			return -1;
		}
	}
	return 0;
}
int CKSCardManager::SetMoney(int cardid,int money)
{
	TEST_COM_OPEN;
	if(TestCardExists(10))
	{
		return -1;
	}
	KS_CARD_INFO cardinfo;
	memset(&cardinfo,0,sizeof cardinfo);
	if(ReadCardInfo(&cardinfo,ciCardId) != 0)
	{
		return -1;
	}
	if(cardinfo.cardid != cardid)
	{
		m_errno = ERR_CARD_NOT_CONSIST;
		return -1;
	}
	if(PacketSetMoney(ms_globalPackageNo,money) != 0)
	{
		m_errno = ERR_PACKAGE_SET_MONEY;
		return -1;
	}
	return 0;
}
// ���¿���Ϣ
int CKSCardManager::ModifyCardInfo(int cardid, TPublishCard *pc)
{
	TEST_COM_OPEN;
	if (TestCardExists(10))
	{
		return -1;
	}
	KS_CARD_INFO cardinfo;
	memset(&cardinfo,0,sizeof cardinfo);
	if (ReadCardInfo(&cardinfo, ciCardId))
	{
		return -1;
	}
	if (cardinfo.cardid != cardid)
	{
		m_errno = ERR_CARD_NOT_CONSIST;
		return -1;	
	}
	if (UpdateCardInfo(pc))
	{
		m_errno = ERR_MODIFY_CARD;
		return -1;
	}
	return 0;
}

// ��ȡ����Ϣ
int CKSCardManager::ReadCardInformation(int cardid, TPublishCard *pc)
{
	TEST_COM_OPEN;
	if (TestCardExists(10))
	{
		return -1;
	}
	KS_CARD_INFO cardinfo;
	memset(&cardinfo,0,sizeof cardinfo);
	if (ReadCardInfo(&cardinfo, ciCardId))
	{
		return -1;
	}
	if (cardinfo.cardid != cardid)
	{
		m_errno = ERR_CARD_NOT_CONSIST;
		return -1;	
	}
	if (ReadInfoFromCard(pc))
	{
		m_errno = ERR_READ_CARDINFO;
		return -1;
	}
	return 0;
}

int CKSCardManager::LoadKSComDLL()
{
	gsKSComHandle = LoadLibrary(m_config->m_KSComDLLPath);
	if(NULL == gsKSComHandle)
	{
		m_errno = ERR_LOADKSCOM_DLL;
		return -1;
	}
	m_errno = ERR_LOAD_FUNC;
	LOAD_KSFUNC(gsKSComHandle,Load_Dll);
	LOAD_KSFUNC(gsKSComHandle,Load_WorkKey);
	LOAD_KSFUNC(gsKSComHandle,PacketAddMoney);
	LOAD_KSFUNC(gsKSComHandle,PacketDecMoney);
	LOAD_KSFUNC(gsKSComHandle,ReadBalance);
	LOAD_KSFUNC(gsKSComHandle,ReadCardNo);
	LOAD_KSFUNC(gsKSComHandle,SetBlackCardFlag);
	LOAD_KSFUNC(gsKSComHandle,ComInit);
	LOAD_KSFUNC(gsKSComHandle,COMClose);
	LOAD_KSFUNC(gsKSComHandle,SetNormalFlag);
	LOAD_KSFUNC(gsKSComHandle,ChangePassWord);
	LOAD_KSFUNC(gsKSComHandle,ReadSerial);
	LOAD_KSFUNC(gsKSComHandle,PacketSetMoney);
	LOAD_KSFUNC(gsKSComHandle,UpdateCardInfo);
	LOAD_KSFUNC(gsKSComHandle,ReadInfoFromCard);
	m_errno = ERR_SUCCEEDED;
	return 0;
}

int CKSCardManager::LoadKSCom()
{
	int ret = LoadKSComDLL();
	if(ret!=0)
	{
		return ret;
	}
	if(Load_WorkKey(m_workKey) != 0)
	{
		m_errno = ERR_SETWORKKEY;
		return -1;
	}
	return 0;
}

int CKSCardManager::ReleaseKSCom()
{
	if(gsKSComHandle != NULL)
	{
		FreeLibrary(gsKSComHandle);
		gsKSComHandle = NULL;
	}
	return 0;
}

CString CKSCardManager::GetErrMsg()
{
	int i = 0;
	while(gs_errMap[i].errcode != -1)
	{
		if(gs_errMap[i].errcode == m_errno)
		{
			return CString(gs_errMap[i].errmsg);
		}
		i++;
	}
	return "";
}

int CKSCardManager::OpenCOM()
{
	if(!ms_isComOpen)
	{
		if(ComInit((LPSTR)(LPCTSTR)m_config->m_RFComPort,0) != 0)
		{
			m_errno = ERR_OPEN_COM;
			return -1;
		}
		ms_isComOpen = true;
	}
	return 0;
}

int CKSCardManager::CloseCOM()
{
	if(ms_isComOpen)
	{
		COMClose();
		ms_isComOpen = false;
	}
	return 0;
}
bool CKSCardManager::IsCOMOpen()
{
	return ms_isComOpen;
}

int CKSCardManager::TestCardExists(int timeout)
{
	TEST_COM_OPEN;
	DWORD key;
	m_timeout = timeout;
	CWinThread * pThread = AfxBeginThread(CKSCardManager::TestCardThread
		,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);
	ms_testCardEvent.ResetEvent();
	ms_cancelEvent.ResetEvent();
	pThread->ResumeThread();
	while(1)
	{
		key = m_workflow->GetLastKeyCode();
		if(VK_ESCAPE == key)
		{
			ms_cancelEvent.SetEvent();
			while(WaitForSingleObject(ms_testCardEvent,1000) == WAIT_OBJECT_0)
			{
				goto L_END;
			}
		}
		// �������
		if(WaitForSingleObject(ms_testCardEvent,0) == WAIT_OBJECT_0)
		{
			if(!m_errno)
				return 0;
			else
				return -1;
		}
	}
L_END:
	return -1;
}

UINT CKSCardManager::TestCardThread( LPVOID pParam )
{
	CKSCardManager * manager = (CKSCardManager*)pParam;
	int tick = manager->m_timeout * 2; // 500 * m_timeout * 2 ms
	int i;
	unsigned char serial[20] = "";
	do 
	{
		memset(serial,0,sizeof serial);
		manager->m_errno = ERR_CARD_NOT_EXIST;
		
		if(!ReadSerial(serial)) //&& strlen((char*)serial) == 8)
		{	
			manager->m_errno = ERR_SUCCEEDED;
			break;
		}
		
		i = 0;
		// �ȴ� 500 ms
		while(i < 500)
		{
			if(WaitForSingleObject(ms_cancelEvent,0) == WAIT_OBJECT_0)
			{
				// ��������Ѿ���ȡ���˳�
				// TRACE0(_T("exits all"));
				goto L_END;
			}
			Sleep(10);
			i += 10;
		}	
	} while(--tick > 0);
L_END:
	//m_errno = ERR_CARD_NOT_EXIST;
	ms_testCardEvent.SetEvent();
	AfxEndThread(0);
	return 0;
}