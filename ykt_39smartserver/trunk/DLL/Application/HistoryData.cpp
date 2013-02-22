// HistoryData.cpp: implementation of the CHistoryData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "HistoryData.h"

#include "SRCTable.h"
#include "JZSRCTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHistoryData::CHistoryData()
{
	m_strTaskCode = "09";
	m_bMarkCheck = false;
}

CHistoryData::~CHistoryData()
{

}

long CHistoryData::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	unsigned char  buffer[100],*pt=NULL;
	int i = 0 ;

	Trim( pTask->szMemo );

	if( !strcmp(pTask->szMemo, "") )
	{
		i = pDocEx->pChildDoc[pDocEx->nPortNo]->m_wFlowNo; 
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

	memset(buffer, 0x00, sizeof(buffer));

	pt =(BYTE*)&i;
	buffer[0]=*(pt+1);
	buffer[1]=*(pt+0);
	MakeBuf_CollectDataBySerialNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, buffer);

	//memset(buffer, 0x00, sizeof(buffer));
	//pBuffer->nBufferSize=pBuffer->nCmdSize;
	//SVC_HEX_2_DSP(pBuffer->pBuffer,buffer,pBuffer->nCmdSize);
	//printf("................%s\n",buffer);

	if( pDocEx->pChildDoc[pDocEx->nPortNo]->m_nParentID > 0 )
	{
		return RET_ERRORCALL;
	}

	return RET_OK;
}

long CHistoryData::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int nIndex = m_pDocEx->nPortNo ;
	long nRet = RET_NG;
	unsigned char ucRawData[256];

	memset(ucRawData, 0x00, sizeof ucRawData );

	if( pBuffer != NULL )
	{
		memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);
	}

	switch(GetMachineType(m_pDocEx->pChildDoc[nIndex]))
	{
		case MACHINE_TYPE_5301://������
			nRet = LportDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0201://��ֵ��
		case MACHINE_TYPE_0226://�շѻ�
		case MACHINE_TYPE_0228://���ػ�
		case MACHINE_TYPE_0230://�����
		case MACHINE_TYPE_0232://�ϻ�������
		case MACHINE_TYPE_0234://��ԡ�����
		case MACHINE_TYPE_0240://��Ʊ��
		case MACHINE_TYPE_0130://���ʶ���
		case MACHINE_TYPE_0140://��Ʊ��
		case MACHINE_TYPE_0248://�Ϻ���ת�ʻ�
			nRet = DealDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0121://��ʱ��
			nRet = IdentifyDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0224://��ʧ��
			break;
		default:
			break;
	}
	return nRet;
}

long CHistoryData::LportDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo)
{
	CSmartSRCBZTable  SRCTable;
	unsigned char ucRawData[256];
	int  nFlowNo;

	int iBegin=-2, iEnd = -2;
	GetNumberRange(pTask->szMemo, iBegin, iEnd);

	if( pBuffer == NULL )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		strString.Format("�����Ϊ%d������ʱ, �ն��޷�Ӧ!!", pDoc->m_wAfterFlowNo);
		ReportLog(pDoc, pTask, RET_DBQUERYERROR, "��ʷ����", strString.GetBuffer(0));

		if( OutputRealData(pTask, pDoc, 0x09, (unsigned char*)pDoc->m_szDeviceID, pDoc->m_wAfterFlowNo) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

		strString.Format("��%d����ʷ����ʱ, �ն��޷�Ӧ!!", iBegin);
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
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "��ʷ����", "�ն��޷�Ӧ�������쳣!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

		strString.Format("�޶�Ӧ�����Ϊ%d������!!", iBegin);

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

		ReportLog(pDoc, pTask, RET_OK, "��ʷ����", "");
		return RET_OK;
	}

	//CRC���
	if( !CRCValid(&ucRawData[8], 29) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "��ʷ����", "CRCУ���!");	
	}

	nFlowNo = ucRawData[8]*256+ucRawData[9];
	if( 1) //nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x24, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		printf("AuthNo = %d, ����ʷ������: ��%d�յ�%d, ����ֵ:%d, ʵ���յ�:%d\n", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, 
			iBegin, iEnd, iBegin, nFlowNo);

		if( iBegin == iEnd )
		{
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			char szTemp[18];

			if( iBegin == 65535 )
				iBegin = 0 ;
			else
				iBegin++;

			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
	}

	return RET_OK;
}

//��ʷ�����շ�����
long CHistoryData::DealDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNo)
{
	unsigned char ucRawData[256];
	int nFlowNo;
	CSmartSRCSFTable  SRCTable;

	int iBegin=-2, iEnd = -2;
	GetNumberRange(pTask->szMemo, iBegin, iEnd);

	nPortNo = pDocEx->nPortNo;

	if( pBuffer == NULL )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x09, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

		char szTemp[18];
		strString.Format("��%d����ʷ����ʱ, �ն��޷�Ӧ!!", iBegin);
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
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "��ʷ����", "�ն��޷�Ӧ�������쳣!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);
	printf(" �ռ���ʷ���� %.2X%.2X%.2X%.2X%.2X\n",pBuffer->pBuffer[0],
											      pBuffer->pBuffer[1],
												  pBuffer->pBuffer[2],
												  pBuffer->pBuffer[3],
												  pBuffer->pBuffer[4]);

 	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}


		strString.Format("�޶�Ӧ�����Ϊ%d������!!", iBegin);
		
		printf("%s\n", strString);
		/* deleter by lina 20050404
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
		}*/
		//add by lina 20050405
		pDoc->m_nFlowFlag = 0 ;
		TerminateTask();
		ReportLog(pDoc, pTask, RET_OK, "��ʷ����", "");

		return RET_OK;
	}
	//add by lina 20050404
	/*else
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		TerminateTask();
		pDoc->m_nFlowFlag = 0 ;
		ReportLog(pDoc,pTask,RET_OK,"��ʷ����","");
	}*/


	int nMarkType = 0x21 ;
	if( !strcmp(pDocEx->pChildDoc[nPortNo]->m_szMacCode, "0201") )
	{
		if( ucRawData[25] == 0x30 )
			nMarkType = 0x27 ;
		else
			nMarkType = 0x26 ;
	}

	//CRC���
	if( !CRCValid(ucRawData) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "��ʷ����", "CRCУ���!");	
	}

	nFlowNo = ucRawData[6]*256+ucRawData[7];
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], nMarkType, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		printf("AuthNo = %d, ����ʷ��: ��%d�յ�%d, ����ֵ:%d, ʵ���յ�:%d\n", 
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID, 
			iBegin, iEnd, iBegin, nFlowNo);

		if( iBegin == iEnd )
		{
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			char szTemp[18];

			if( iBegin == 65535 )
				iBegin = 0 ;
			else
				iBegin++;

			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
	}
	else
	{
		char szTemp[256];
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], nMarkType, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ��������", "���˴��м䴫����޷�Ӧ!");
		}

		if( iBegin == iEnd )
		{
			pDocEx->pChildDoc[pDocEx->nPortNo]->m_nFlowFlag = 0 ;
			TerminateTask();
		}
		else
		{
			if( iBegin == 65535 ) iBegin = 0 ;
			else iBegin++;

			sprintf(szTemp, "%d:%d", iBegin, iEnd);
			strcpy(pTask->szMemo, szTemp);
		}
	}

	return RET_OK;
}

long CHistoryData::IdentifyDataProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer,unsigned char *RawData,int nPortNoc)
{
	unsigned char ucRawData[256];
	int nPortNo,nFlowNo;
	CSmartSRCJSBTable  SRCTable;

	nPortNo = pDocEx->nPortNo;

	int iBegin=-2, iEnd = -2;
	GetNumberRange(pTask->szMemo, iBegin, iEnd);

	if( pBuffer == NULL )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x09, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

		char szTemp[18];
		strString.Format("AuthNo = %d, �����Ϊ%d������ʱ�ն��޷�Ӧ", 
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

		ReportLog(pDoc, pTask, RET_OK, "��ʷ����", "");

		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	printf("History, IdentifyDataProcess.............\n");

	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		long nDatabase = GetDBHandle(DATABASE_NORMAL);

		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

		char szTemp[18];
		strString.Format("�޶�Ӧ�����Ϊ%d������!!", iBegin);

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

		ReportLog(pDoc, pTask, RET_OK, "��ʷ����", "");

		return RET_OK;
	}

	//CRC���
	if( !CRCValid(ucRawData) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "��ʷ����", "CRCУ���!");	
	}

	nFlowNo = ucRawData[6]*256+ucRawData[7];
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x22, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

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
	else
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x22, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "��ʷ����", "���˴��м䴫����޷�Ӧ!");
		}

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


//MARKֵ��
bool CHistoryData::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	CString strString;
	switch(nMark)
	{
	case 0x0b: //��Ȩ�Ų���
		strString.Format("��ʷ�ռ�ʱ��Ȩ�Ų���! ����Ϊ:%s", pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, nMark, "��ʷ����", strString.GetBuffer(0));
		ModifyRegister(pDoc, pBuffer);
		break;
	case 0x05: //
		strString.Format("��ʷ�ռ�ʱMark����! ��ˮ�Ŵ�:%s", pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, nMark, "��ʷ����", strString.GetBuffer(0));
		TerminateTask();
		break;
	default:
		ReportLog(pDoc, pTask, nMark, "��ʷ����", "��ʷ�ռ�ʱMark����!");
		printf("3---��ʷ�ռ�ʱMark����!\n");
		ResetDevice(pDoc, pBuffer);
		break;
	}
	return true;
}

void CHistoryData::OnCRCError()
{

}

