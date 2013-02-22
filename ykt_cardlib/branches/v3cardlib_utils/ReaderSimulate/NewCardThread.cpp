// NewCardThread.cpp : implementation file
//
#include "stdafx.h"
#include "NewCardThread.h"
#include "ReadCardInfoDlg.h"
#include "kscard_imp.h"
#include "KsCardInterFace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread


CNewCardThread::~CNewCardThread()
{
}

BOOL CNewCardThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here

    m_LogFile = NULL;// ������ʼ��
    memset(m_CardID, 0, sizeof(m_CardID)); // ������ʼ��
    m_Lasttime = 0;// ������ʼ��

    // �ж��Ƿ���ҪдLOG�ļ�
	int logstatus = ((CReadCardInfoDlg*)m_pMainWnd)->m_logstatus;
	if(logstatus != 0)
    {
        // ��ȡ���̿�ִ���ļ���·��
        char strLogFilePath[256];
        DWORD ret = GetModuleFileName(NULL,strLogFilePath,sizeof(strLogFilePath));
        if(ret != 0)
        {
            // ��·�� xxx.exe �ĳ� xxx.log
            char* pDot = strrchr(strLogFilePath,'.');
            if(pDot != NULL)
            {
                *pDot = NULL;
                strncat(strLogFilePath, ".log", sizeof(strLogFilePath));
                m_LogFile = fopen(strLogFilePath, "a");//��Log�ļ���׷������
            }
        }
    }

	return TRUE;
}

int CNewCardThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	////////////////////////////////////////////////////
	// �ر�LOG �ļ�
	if(m_LogFile != NULL)
	{
	    fclose(m_LogFile);
	    m_LogFile = NULL;
	}

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CNewCardThread, CWinThread)
	//{{AFX_MSG_MAP(CNewCardThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Log ����
// fmt �� ��ʽ���ַ��� �� "Hello %d %s", 123, "string"
// ����ֵ��д����ֽ���������������ʱ�䲿�֣�
INT CNewCardThread::WriteLog(char* fmt, ...)
{
    if( m_LogFile == NULL) // LOG �ļ�û�д�
        return 0;

    time_t nowTime; // ȡϵͳ��ǰʱ��
    time(&nowTime);

    struct tm *p= localtime(&nowTime);// ת��ʱ���ʽ

    fprintf(m_LogFile, "[%d-%d-%d %d:%d:%d]" ,
            (1900+p->tm_year),p->tm_mon, p->tm_mday,
            p->tm_hour, p->tm_min, p->tm_sec);

    // ����ɱ������Ϣ����
	va_list args;
	int n;
	va_start(args, fmt);
	n = vfprintf(m_LogFile, fmt, args);
	va_end(args);

	fflush(m_LogFile);

	return n; // ����д����ֽ���
}

/////////////////////////////////////////////////////////////////////////////
// ����ID�Ŀ��Ƿ���ָ����ʱ�����ڶ�������ֹ�ظ�����
// strCardID�� ��������ID
// dwInterval�� ��Сʱ��������λ����
// ����ֵ��TRUE  ָ�����ʱ����û�ж����ÿ�,�������
//         FALSE ָ�����ʱ������ÿ�,�������ظ�����
BOOL CNewCardThread::CheckCardLastRequestTime(char* phyid, DWORD dwInterval)
{
    WriteLog("CheckCardLastRequestTime:����=%s ʱ����=%d\n", phyid, dwInterval);

    if(dwInterval == 0)
        return TRUE; // dwInterval Ϊ 0 ������飬Ĭ��û�ж����ÿ�

    DWORD current_time = GetTickCount(); // ��ȡϵͳ������ĺ�����

    if(strncmp(m_CardID, phyid, sizeof(m_CardID)) == 0) // ���ζ���ID���ϴ���ͬ
    {
        if(current_time - m_Lasttime > dwInterval*1000) //  �����������ʱ�䳬�����ʱ��Ҫ��, �����ٶ�
        {
            m_Lasttime = current_time; // ���±���������ʱ��
            WriteLog("CheckCardLastRequestTime: ����[%s]�����ϴζ���ʱ���ѹ�[%d]��,�����ٶ�\n", phyid, dwInterval);
            return TRUE;
        }
        else
        {
            // ָ��ʱ�����ڶ����ÿ�,�������ٶ�
            WriteLog("CheckCardLastRequestTime: �ÿ�[%s] [%d]������������,�������ٶ�\n", phyid, dwInterval);
            return FALSE;
        }
    }
    else
    {
        // �ϴζ��Ĳ��Ǹ�ID�Ŀ�����¼����ID,��¼������ʱ��,�������
        WriteLog("CheckCardLastRequestTime: �ϴζ���[%s]���Ǹÿ�[%s]���������\n", m_CardID, phyid);
        strncpy(m_CardID, phyid, sizeof(m_CardID)); // ��¼��ID
        m_Lasttime = current_time; // ��¼������ʱ��
        return TRUE;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread message handlers

int CNewCardThread::DoInit()
{
	int ret = -1;
	char phyid[30] = "";
//	char stuemp_no[21] = "";
	int _Mode = ((CReadCardInfoDlg*)m_pMainWnd)->m_nInvokeMode;
	int t_card_flag = ((CReadCardInfoDlg*)m_pMainWnd)->m_card_flag;
	int checkCard = ((CReadCardInfoDlg*)m_pMainWnd)->m_checkCardOnline;

	//if (KS_Halt() != 0) { return 0; }


    DWORD dwInterval = ((CReadCardInfoDlg*)m_pMainWnd)->m_minimum_Interval;

	// ��ȡ��Ȩ��

	if (CARDFLAG_PHYSICALID == t_card_flag)
	{
		ret = KS_RequestCard(phyid);
		if (ret)
		{
			Sleep(500);
			return 0;
		}

		if(CheckCardLastRequestTime(phyid, dwInterval) == FALSE) // �����������ֹ�ظ�����
		{
			Sleep(300);
			return 0;
		}

		((CReadCardInfoDlg*)m_pMainWnd)->SimulateKeyPress(phyid);
	}
	else
	{
		TPublishCard CI;
		char *temp;
		char fldname[64]={0};
		char fldvalue[256]={0};
		int cardno;
		memset(&CI, 0, sizeof(CI));
		if(KS_RequestCard(phyid))
		{
			Sleep(300);
			return 0;
		}

		if(CheckCardLastRequestTime(phyid, dwInterval) == FALSE) // �����������ֹ�ظ�����
		{
			Sleep(300);
			return 0;
		}

		//ks_clearallfieldreadmode();

		if(CARDFLAG_SHOWID == t_card_flag)
		{
			strcpy(fldname,"SHOWCARDNO");
			KS_SetReadFieldName(fldname);
			temp = CI.ShowCardNo;
			if(checkCard)
			{
				KS_SetReadFieldName("CARDNO");
			}
		}
		else if(CARDFLAG_DEALID == t_card_flag)
		{
			strcpy(fldname,"CARDNO");
			KS_SetReadFieldName(fldname);
			temp = CI.CardNo;
		}
		else if(CARDFLAG_SEPID == t_card_flag)
		{
			strcpy(fldname,"STUEMPNO");
			KS_SetReadFieldName(fldname);
			temp = CI.StuempNo;
			if(checkCard)
			{
				KS_SetReadFieldName("CARDNO");
			}
		}
		else if(CARDFLAG_CUTID == t_card_flag)
		{
			strcpy(fldname,"CUSTID");
			KS_SetReadFieldName(fldname);
			temp = CI.CustId;
			if(checkCard)
			{
				KS_SetReadFieldName("CARDNO");
			}
		}
		else
		{
			KS_Halt();
			Sleep(1000);
			return 0;
		}

		ret = KS_ReadCard();
		if (ret)
		{
			Sleep(500);
			return 0;
		}
		KS_GetFieldVal(fldname,temp);
		if(checkCard)
		{
			if(strcmp(fldname,"CARDNO")!=0)
			{
				KS_GetFieldVal("CARDNO",fldvalue);
			}
			else
			{
				strcpy(fldvalue,temp);
			}
			cardno = atoi(fldvalue);
			char statuscode=0;
			char szStatusInfo[256];
			if(KS_GetCardStatus(cardno,&statuscode,szStatusInfo))
			{
				KS_Beep();
				KS_Beep();
				KS_Beep();
				Sleep(1000);
				return 0;
			}
			if(statuscode != 0)
			{
				KS_BeepErr();
				Sleep(1000);
				return 0;
			}
		}

		((CReadCardInfoDlg*)m_pMainWnd)->SimulateKeyPress(CI, t_card_flag);
	}
	Sleep(1000);
	return 0;
}

CNewCardThread::CNewCardThread(CWnd *pWnd)
{
	pre_card_id = 0;
	m_pMainWnd = pWnd;
}

int CNewCardThread::Run()
{
	while (!m_terminate)
	{
		if (DoInit() != 0)
		{
			::AfxMessageBox("����ʧ��");
			break;
		}
	}
	if (m_pMainWnd)
	{
		m_pMainWnd->PostMessage(WM_INIT_THREAD_TERM, 0, 0);
	}
	Reset();
	KS_Halt();
	return CWinThread::Run();
}

void CNewCardThread::Reset()
{
	pre_card_id = 0;
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_index = 0;
	return ;
}
