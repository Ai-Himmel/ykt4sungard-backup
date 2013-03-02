// DownloadJZTime.h: interface for the CDownloadJZTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADJZTIME_H__5748E54E_006D_40A8_9709_1C8ADDB5258E__INCLUDED_)
#define AFX_DOWNLOADJZTIME_H__5748E54E_006D_40A8_9709_1C8ADDB5258E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CDownloadJZTime
//*功能: 下传定时扎帐时间
//*******************************************************************************
class CDownloadJZTime : public COperator  
{
public:
	CDownloadJZTime();
	virtual ~CDownloadJZTime();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

#endif // !defined(AFX_DOWNLOADJZTIME_H__5748E54E_006D_40A8_9709_1C8ADDB5258E__INCLUDED_)
