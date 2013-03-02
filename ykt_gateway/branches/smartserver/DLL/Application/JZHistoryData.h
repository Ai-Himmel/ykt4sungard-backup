// JZHistoryData.h: interface for the CJZHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JZHISTORYDATA_H__CBD9AE6B_B17A_4EF6_93C1_AD494A967043__INCLUDED_)
#define AFX_JZHISTORYDATA_H__CBD9AE6B_B17A_4EF6_93C1_AD494A967043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CJZHistoryData
//*功能: 收集历史扎帐数据
//*******************************************************************************
class CJZHistoryData  : public COperator 
{
protected:
	long StateDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);

protected:
	void OnCRCError();

public:
	CJZHistoryData();
	virtual ~CJZHistoryData();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

#endif // !defined(AFX_JZHISTORYDATA_H__CBD9AE6B_B17A_4EF6_93C1_AD494A967043__INCLUDED_)
