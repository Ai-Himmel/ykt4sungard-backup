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

    m_LogFile = NULL;// 变量初始化
    memset(m_CardID, 0, sizeof(m_CardID)); // 变量初始化
    m_Lasttime = 0;// 变量初始化

    // 判断是否需要写LOG文件
	int logstatus = ((CReadCardInfoDlg*)m_pMainWnd)->m_logstatus;
	if(logstatus != 0)
    {
        // 获取进程可执行文件的路径
        char strLogFilePath[256];
        DWORD ret = GetModuleFileName(NULL,strLogFilePath,sizeof(strLogFilePath));
        if(ret != 0)
        {
            // 将路径 xxx.exe 改成 xxx.log
            char* pDot = strrchr(strLogFilePath,'.');
            if(pDot != NULL)
            {
                *pDot = NULL;
                strncat(strLogFilePath, ".log", sizeof(strLogFilePath));
                m_LogFile = fopen(strLogFilePath, "a");//打开Log文件，追加内容
            }
        }
    }

	return TRUE;
}

int CNewCardThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	////////////////////////////////////////////////////
	// 关闭LOG 文件
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
// Log 函数
// fmt ： 格式化字符串 如 "Hello %d %s", 123, "string"
// 返回值：写入的字节数（不包含日期时间部分）
INT CNewCardThread::WriteLog(char* fmt, ...)
{
    if( m_LogFile == NULL) // LOG 文件没有打开
        return 0;

    time_t nowTime; // 取系统当前时间
    time(&nowTime);

    struct tm *p= localtime(&nowTime);// 转换时间格式

    fprintf(m_LogFile, "[%d-%d-%d %d:%d:%d]" ,
            (1900+p->tm_year),p->tm_mon, p->tm_mday,
            p->tm_hour, p->tm_min, p->tm_sec);

    // 输出可变参数消息内容
	va_list args;
	int n;
	va_start(args, fmt);
	n = vfprintf(m_LogFile, fmt, args);
	va_end(args);

	fflush(m_LogFile);

	return n; // 返回写入的字节数
}

/////////////////////////////////////////////////////////////////////////////
// 检查该ID的卡是否在指定的时间间隔内读过，禁止重复读卡
// strCardID： 卡的物理ID
// dwInterval： 最小时间间隔，单位：秒
// 返回值：TRUE  指定间隔时间内没有读过该卡,容许读卡
//         FALSE 指定间隔时间读过该卡,不容许重复读卡
BOOL CNewCardThread::CheckCardLastRequestTime(char* phyid, DWORD dwInterval)
{
    WriteLog("CheckCardLastRequestTime:卡号=%s 时间间隔=%d\n", phyid, dwInterval);

    if(dwInterval == 0)
        return TRUE; // dwInterval 为 0 不做检查，默认没有读过该卡

    DWORD current_time = GetTickCount(); // 获取系统启动后的毫秒数

    if(strncmp(m_CardID, phyid, sizeof(m_CardID)) == 0) // 本次读卡ID与上次相同
    {
        if(current_time - m_Lasttime > dwInterval*1000) //  本卡读卡间隔时间超过间隔时间要求, 容许再读
        {
            m_Lasttime = current_time; // 更新本卡最后读卡时间
            WriteLog("CheckCardLastRequestTime: 本卡[%s]距离上次读卡时间已过[%d]秒,容许再读\n", phyid, dwInterval);
            return TRUE;
        }
        else
        {
            // 指定时间间隔内读过该卡,不容许再读
            WriteLog("CheckCardLastRequestTime: 该卡[%s] [%d]秒内曾经读过,不容许再读\n", phyid, dwInterval);
            return FALSE;
        }
    }
    else
    {
        // 上次读的不是该ID的卡，记录卡的ID,记录最后读卡时间,容许读卡
        WriteLog("CheckCardLastRequestTime: 上次读卡[%s]不是该卡[%s]，容许读卡\n", m_CardID, phyid);
        strncpy(m_CardID, phyid, sizeof(m_CardID)); // 记录卡ID
        m_Lasttime = current_time; // 记录最后读卡时间
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

	// 读取授权卡

	if (CARDFLAG_PHYSICALID == t_card_flag)
	{
		ret = KS_RequestCard(phyid);
		if (ret)
		{
			Sleep(500);
			return 0;
		}

		if(CheckCardLastRequestTime(phyid, dwInterval) == FALSE) // 最近读过，禁止重复读卡
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

		if(CheckCardLastRequestTime(phyid, dwInterval) == FALSE) // 最近读过，禁止重复读卡
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
			::AfxMessageBox("读卡失败");
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
