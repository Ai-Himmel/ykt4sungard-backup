// CollectionData.h: interface for the CCollectionData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLECTIONDATA_H__E49844D7_87D1_40B2_8B63_669A135E8B79__INCLUDED_)
#define AFX_COLLECTIONDATA_H__E49844D7_87D1_40B2_8B63_669A135E8B79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCollectionData : public COperator
{
protected:
	long LPort_Process(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer);
	bool LportState(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData);

	long Process_DealTypeData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);
	long Process_IdentifyData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);
	long Process_GSJData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo);
	long Process_StateData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *Buffer,int nPortNo);
	long Process_AssisData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo);
	bool ConfirmData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucFlowNo,int nPortNo,int nRetryNo);
	bool ConfirmJZData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucFlowNo,int nPortNo,int nRetryNo);

	long InsertTask(TSSmartDoc *pDoc, long nTry, char *TaskCode);
	bool ConfirmLost(int nPortNo, unsigned char *ucRawData, unsigned char flag);
	bool FindMachine(char *szDataReg, TSSmartDoc *pDoc);
	bool AddNewMachine(int nPort, char *type, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, char *szDataReg, TSSmartDoc *pDoc);
	bool GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc);
	bool PostBlackCard(int nflag, long nDatabase, long nCardID);
	bool ReadJZRecord(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

protected:
	bool OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark);
	void OnCRCError();

public:
	CCollectionData();
	virtual ~CCollectionData();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

};

#endif // !defined(AFX_COLLECTIONDATA_H__E49844D7_87D1_40B2_8B63_669A135E8B79__INCLUDED_)
