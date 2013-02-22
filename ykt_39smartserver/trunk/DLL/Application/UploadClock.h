// UploadClock.h: interface for the CUploadClock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPLOADCLOCK_H__AF621178_DEC8_4464_90C2_37419692156D__INCLUDED_)
#define AFX_UPLOADCLOCK_H__AF621178_DEC8_4464_90C2_37419692156D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CUploadClock
//*功能: 上传时钟
//*******************************************************************************
class CUploadClock : public COperator  
{
public:
	CUploadClock();
	virtual ~CUploadClock();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

#endif // !defined(AFX_UPLOADCLOCK_H__AF621178_DEC8_4464_90C2_37419692156D__INCLUDED_)
