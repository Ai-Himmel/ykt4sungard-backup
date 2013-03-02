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
			strText.Format("��ʷ����Ƿ�! MEMO�ֶ�Ϊ:%s", pTask->szMemo);
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_SYSERROR, "��ʷ����", strText.GetBuffer(0));
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

	//�ն��޷�Ӧʱ�Ĵ���
	if( pBuffer == NULL )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x09, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		char szTemp[18];
		strString.Format("AuthNo=%d, ��%d����ʷ��������ʱ, �ն��޷�Ӧ!!", 
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
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "��ʷ��������", "�ն��޷�Ӧ�������쳣!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	//û������
	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		strString.Format("AuthNo=%d, �޶�Ӧ�����Ϊ%d����ʷ��������!!", 
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

		ReportLog(pDoc, pTask, RET_OK, "��ʷ��������", "");

		return RET_OK;
	}

	//CRC���
	if( !CRCValid(ucRawData, 36) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "��ʷ��������", "CRCУ���!");	
	}

	ucFlowNo[0] = ucRawData[8]; 
	ucFlowNo[1] = ucRawData[9];

	nFlowNo = ucRawData[6]*256+ucRawData[7];

	//�����ϴ�����ˮ��������ˮ�����
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x23, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		printf("AuthNo=%d, ��������ʷ��: ��%d�յ�%d, ����ֵ:%d, ʵ���յ�:%d\n", 
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
	//��ˮ��������ֵ������
	else 
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x23, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		printf("AuthNo=%d, ��������ʷ��: ��%d�յ�%d, ����ֵ:%d, ʵ���յ�:%d\n", 
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
	ReportLog(m_pDocEx->pChildDoc[m_nIndex], m_pTask, RET_DATACRC_ERROR, "��ʷ��������", "�ռ���ʷ��������ʱCRC��");
	ClearPortData(m_pDocEx->pChildDoc[m_nIndex], m_pBuffer, m_nIndex);
}
