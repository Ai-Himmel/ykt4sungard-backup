// UploadClock.cpp: implementation of the CUploadClock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "UploadClock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUploadClock::CUploadClock()
{
	m_strTaskCode = "03";
}

CUploadClock::~CUploadClock()
{

}

long CUploadClock::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return MakeBuf_GetClock(pDocEx->pDeviceInfo,pBuffer);
}

long CUploadClock::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	long nResult = UnMakeDeviceBuffer(pBuffer);
	if( nResult == RET_OK )
	{
		int nMark = pBuffer->pBuffer[2];
		if( nMark != 0x00 )
			nResult = nMark; 
	}

	if( nResult == RET_OK )
	{
		unsigned char *ucData = &pBuffer->pBuffer[4];
		sprintf(data.sValue1, "%02d%02d%02d%02d%02d%02d", 
			ucData[0], ucData[1], ucData[2], 
			ucData[3], ucData[4], ucData[5]);
	}

	ReportLog(pDocEx, pTask, nResult, "恢复正常运行状态", "");
	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, nResult, &data);

	return nResult;
}

