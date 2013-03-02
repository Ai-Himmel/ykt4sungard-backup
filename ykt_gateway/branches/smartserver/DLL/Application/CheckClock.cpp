// CheckClock.cpp: implementation of the CCheckClock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "CheckClock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckClock::CCheckClock()
{
	m_strTaskCode = "05";
	m_bMachineNo = true;
	m_bMarkCheck = true;
}

CCheckClock::~CCheckClock()
{

}

long CCheckClock::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CTime  tm=CTime::GetCurrentTime();
	unsigned char Buffer[32];
	Buffer[0] = tm.GetYear();
	Buffer[1] = tm.GetMonth();
	Buffer[2] = tm.GetDay();
	Buffer[3] = tm.GetHour();
	Buffer[4] = tm.GetMinute();
	Buffer[5] = tm.GetSecond();
	Buffer[6] = tm.GetDayOfWeek();

	return MakeBuf_SetClock(pDocEx->pDeviceInfo, pBuffer,Buffer);
}

long CCheckClock::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
//	TerminateTask();
	ReportLog(pDocEx->pChildDoc[m_nIndex], pTask, RET_OK, "校对时钟", "");
	return RET_OK;
}

bool CCheckClock::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	switch(nMark)
	{
	case 0x05:
		TerminateTask();
		ReportLog(pDoc, pTask, nMark, "校对时钟", "返回授权号错误");
		break;
	default:
		TerminateTask();
		ReportLog(pDoc, pTask, nMark, "校对时钟", "返回Mark错误");
		break;
	}
	return true;
}

