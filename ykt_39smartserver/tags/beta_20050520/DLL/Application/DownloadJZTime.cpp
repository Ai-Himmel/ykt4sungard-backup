// DownloadJZTime.cpp: implementation of the CDownloadJZTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "DownloadJZTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDownloadJZTime::CDownloadJZTime()
{
	m_strTaskCode = "18";
	m_bMachineNo = true ;
	m_bMarkCheck = false ;
	m_strAccTime = "" ;
}

CDownloadJZTime::~CDownloadJZTime()
{

}

long CDownloadJZTime::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int No;                 //扎帐时间个数
	unsigned char Hex[256]; //对应扎帐时间 长度No*2 时分
	unsigned char Tmp[32]; //对应扎帐时间 长度No*2 时分

	memset(Hex, 0, sizeof(Hex));

	m_strAccTime = "" ;
	No = m_strAccTime.GetLength();
	if( No <= 0 )
	{
		ReadSmartSetup();
		No = m_strAccTime.GetLength();
		if( No <= 0 )
		{
			ReportLog(pDocEx, pTask, RET_PARAMETER_ERROR1, "下传定时扎帐时间", "数据库中<无定时扎帐时间>的参数.表smart_setup!");
			return RET_PARAMETER_ERROR1;
		}
	}

	CString strMid = "" ;
	int k=0;

	No = m_strAccTime.GetLength()/4;
	if( No > 10 ) No = 10 ;

	for(int i=0; i< m_strAccTime.GetLength()/4 && i<10; i++)
	{
		memset(Tmp, 0, 32);

////SVC_DSP_2_HEX((BYTE*)strMid.GetBuffer(0), Tmp, 2);
		strMid = m_strAccTime.Mid(i*4,2);
		Hex[k++] = atoi(strMid);

		strMid = m_strAccTime.Mid(i*4+2,2);
		Hex[k++] = atoi(strMid);
	}

	strncpy(pTask->szMemo, m_strAccTime.GetBuffer(0), 20);

	return MakeBuf_SetStateTimeTable(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, No, Hex);
}

long CDownloadJZTime::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int nMark = pBuffer->pBuffer[2];
	if( nMark != 0X00  )
	{
		CString strText;

		strText.Format("下传定时扎帐时间%s失败!", pTask->szMemo);
		ReportLog(pDocEx, pTask, nMark, "下传定时扎帐时间", strText.GetBuffer(0));
		return nMark;
	}
	else
	{
		ReportLog(pDocEx, pTask, RET_OK, "下传定时扎帐时间", "下传定时扎帐时间成功");
		return RET_OK;
	}
}
