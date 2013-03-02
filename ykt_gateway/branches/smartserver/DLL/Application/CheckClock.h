// CheckClock.h: interface for the CCheckClock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKCLOCK_H__A7F73C10_148E_4034_B690_4B1B91CDBF19__INCLUDED_)
#define AFX_CHECKCLOCK_H__A7F73C10_148E_4034_B690_4B1B91CDBF19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CCheckClock
//*功能: 校验时钟
//*******************************************************************************
class CCheckClock : public COperator
{
protected:
	bool OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark);

public:
	CCheckClock();
	virtual ~CCheckClock();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

#endif // !defined(AFX_CHECKCLOCK_H__A7F73C10_148E_4034_B690_4B1B91CDBF19__INCLUDED_)
