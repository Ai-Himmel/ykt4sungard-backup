// HistoryData.h: interface for the CHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYDATA_H__4862C801_D8F6_4A4C_87E2_958A69B38539__INCLUDED_)
#define AFX_HISTORYDATA_H__4862C801_D8F6_4A4C_87E2_958A69B38539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CHistoryData
//*功能: 收历史数
//*******************************************************************************
class CHistoryData : public COperator 
{
protected:
	long LportDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);
	long DealDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);
	long IdentifyDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);

protected:
	bool OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark);
	void OnCRCError();

public:
	CHistoryData();
	virtual ~CHistoryData();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//	static void GetNumberRange(char *pszBuffer, int& iBegin, int& iEnd);
};

#endif // !defined(AFX_HISTORYDATA_H__4862C801_D8F6_4A4C_87E2_958A69B38539__INCLUDED_)
