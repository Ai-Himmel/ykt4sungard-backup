// JZHistoryData.cpp: implementation of the CJZHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "JZHistoryData.h"
#include "JZSRCTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJZHistoryData::CJZHistoryData()
{
	m_strTaskCode = "16";
	m_bMarkCheck = true;
}

CJZHistoryData::~CJZHistoryData()
{

}

long CJZHistoryData::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	unsigned char  buffer[32];
	int i = 0 ;

	Trim(pTask->szMemo);

	if( !strcmp(pTask->szMemo, "") )
	{
		i = pDocEx->pChildDoc[pDocEx->nPortNo]->m_wStateNo; 
	}
	else
	{
		int iEnd = -2 ;
		GetNumberRange(pTask->szMemo, i, iEnd);
		if( i <= -2 ||  iEnd < 0 )
		{
			CString strText;
			strText.Format("历史任务非法! MEMO字段为:%s", pTask->szMemo);
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_SYSERROR, "历史任务", strText.GetBuffer(0));
			return RET_SYSERROR;
		}
	}

	memset(buffer, 0, sizeof(buffer));

	buffer[0] = i / 256;
	buffer[1] = i % 256;

	MakeBuf_CollectStateDataBySerial(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, buffer);

	pBuffer->nTimeOut1 = 1500;
	pBuffer->nTimeOut2 = 1000;

	if( pDocEx->pChildDoc[pDocEx->nPortNo]->m_nParentID > 0 )
		return RET_ERRORCALL;
	
	return RET_OK;
}

long CJZHistoryData::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int nIndex = m_pDocEx->nPortNo ;
	unsigned char ucRawData[256];

	if( pBuffer != NULL )
		memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	return StateDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
}

long CJZHistoryData::StateDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData, int nPort)
{
	CSmartJZSRCTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	bool bBool = true;

	int iBegin=-2, iEnd = -2;
	GetNumberRange(pTask->szMemo, iBegin, iEnd);

	//终端无反应时的处理
	if( pBuffer == NULL )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x09, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "历史扎帐任务", "金仕达中间传输层无反应!");
		}

		char szTemp[18];
		strString.Format("AuthNo=%d, 收%d的历史扎帐数据时, 终端无反应!!", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, iBegin);

		printf("%s\n", strString);

		if( iBegin == iEnd )
		{
			pDoc->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			if( iBegin == 65535 )
				iBegin = 0 ;
			else
				iBegin++;
			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "历史扎帐任务", "终端无反应或网络异常!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	//没有数据
	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "历史扎帐任务", "金仕达中间传输层无反应!");
		}

		strString.Format("AuthNo=%d, 无对应的序号为%d的历史扎帐数据!!", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, 
			iBegin);

		printf("%s\n", strString);

		if( iBegin == iEnd )
		{
			pDoc->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			if( iBegin == 65535 )
				iBegin = 0 ;
			else
				iBegin++;

			char szTemp[18];
			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}

		ReportLog(pDoc, pTask, RET_OK, "历史扎帐任务", "");

		return RET_OK;
	}

	//CRC检测
	if( !CRCValid(ucRawData, 36) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "历史扎帐任务", "CRC校验错!");	
	}

	ucFlowNo[0] = ucRawData[8]; 
	ucFlowNo[1] = ucRawData[9];

	nFlowNo = ucRawData[6]*256+ucRawData[7];

	//数据上传的流水与期望流水号相等
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x23, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史扎帐任务", "金仕达中间传输层无反应!");
		}

		printf("AuthNo=%d, 收扎帐历史数: 从%d收到%d, 期望值:%d, 实际收到:%d\n", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, 
			iBegin, iEnd, iBegin, nFlowNo);

		if( iBegin == iEnd )
		{
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			if( iBegin == 65535 ) 
				iBegin = 0 ;
			else
				iBegin++;

			char szTemp[18];

			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
	}
	//流水号与期望值不符合
	else 
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x23, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史扎帐任务", "金仕达中间传输层无反应!");
		}

		printf("AuthNo=%d, 收扎帐历史数: 从%d收到%d, 期望值:%d, 实际收到:%d\n", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, 
			iBegin, iEnd, iBegin, nFlowNo);

		if( iBegin == iEnd )
		{
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			if( iBegin == 65535 ) iBegin = 0 ;
			else iBegin++;

			char szTemp[18];

			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
	}

	return RET_OK;
}

void CJZHistoryData::OnCRCError()
{
	ReportLog(m_pDocEx->pChildDoc[m_nIndex], m_pTask, RET_DATACRC_ERROR, "历史扎帐任务", "收集历史扎帐数据时CRC错");
	ClearPortData(m_pDocEx->pChildDoc[m_nIndex], m_pBuffer, m_nIndex);
}
