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
			strText.Format("历史任务非法! MEMO字段为:%s", pTask->szMemo);
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_SYSERROR, "历史任务", strText.GetBuffer(0));
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
		case MACHINE_TYPE_5301://服务器
			nRet = LportDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0201://增值机
		case MACHINE_TYPE_0226://收费机
		case MACHINE_TYPE_0228://车载机
		case MACHINE_TYPE_0230://管理机
		case MACHINE_TYPE_0232://上机上网机
		case MACHINE_TYPE_0234://淋浴管理机
		case MACHINE_TYPE_0240://售票机
		case MACHINE_TYPE_0130://身份识别机
		case MACHINE_TYPE_0140://检票机
		case MACHINE_TYPE_0248://上海理工转帐机
			nRet = DealDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0121://计时宝
			nRet = IdentifyDataProcess(pDocEx,pTask,pBuffer, ucRawData, nIndex);
			break;
		case MACHINE_TYPE_0224://挂失机
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

		strString.Format("收序号为%d的数据时, 终端无反应!!", pDoc->m_wAfterFlowNo);
		ReportLog(pDoc, pTask, RET_DBQUERYERROR, "历史任务", strString.GetBuffer(0));

		if( OutputRealData(pTask, pDoc, 0x09, (unsigned char*)pDoc->m_szDeviceID, pDoc->m_wAfterFlowNo) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}

		strString.Format("收%d的历史数据时, 终端无反应!!", iBegin);
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
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "历史任务", "终端无反应或网络异常!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);

	if( pBuffer->pBuffer[3] == 0x00 )
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		CString strString;

		if( OutputRealData(pTask, pDoc, 0x08, (unsigned char*)pDoc->m_szDeviceID, iBegin) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}

		strString.Format("无对应的序号为%d的数据!!", iBegin);

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

		ReportLog(pDoc, pTask, RET_OK, "历史任务", "");
		return RET_OK;
	}

	//CRC检测
	if( !CRCValid(&ucRawData[8], 29) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "历史任务", "CRC校验错!");	
	}

	nFlowNo = ucRawData[8]*256+ucRawData[9];
	if( 1) //nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x24, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史补助任务", "金仕达中间传输层无反应!");
		}

		printf("AuthNo = %d, 收历史补助数: 从%d收到%d, 期望值:%d, 实际收到:%d\n", 
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

//历史交易收费数据
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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}

		char szTemp[18];
		strString.Format("收%d的历史数据时, 终端无反应!!", iBegin);
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
		ReportLog(pDoc, pTask, RET_TERME_NOANSWER, "历史任务", "终端无反应或网络异常!");
		return RET_OK;
	}

	memcpy(ucRawData,&pBuffer->pBuffer[4],pBuffer->pBuffer[3]);
	printf(" 收集历史数据 %.2X%.2X%.2X%.2X%.2X\n",pBuffer->pBuffer[0],
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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}


		strString.Format("无对应的序号为%d的数据!!", iBegin);
		
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
		ReportLog(pDoc, pTask, RET_OK, "历史任务", "");

		return RET_OK;
	}
	//add by lina 20050404
	/*else
	{
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		TerminateTask();
		pDoc->m_nFlowFlag = 0 ;
		ReportLog(pDoc,pTask,RET_OK,"历史数据","");
	}*/


	int nMarkType = 0x21 ;
	if( !strcmp(pDocEx->pChildDoc[nPortNo]->m_szMacCode, "0201") )
	{
		if( ucRawData[25] == 0x30 )
			nMarkType = 0x27 ;
		else
			nMarkType = 0x26 ;
	}

	//CRC检测
	if( !CRCValid(ucRawData) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "历史任务", "CRC校验错!");	
	}

	nFlowNo = ucRawData[6]*256+ucRawData[7];
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], nMarkType, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史交易任务", "金仕达中间传输层无反应!");
		}

		printf("AuthNo = %d, 收历史数: 从%d收到%d, 期望值:%d, 实际收到:%d\n", 
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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史交易任务", "金仕达中间传输层无反应!");
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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}

		char szTemp[18];
		strString.Format("AuthNo = %d, 收序号为%d的数据时终端无反应", 
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

		ReportLog(pDoc, pTask, RET_OK, "历史任务", "");

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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
		}

		char szTemp[18];
		strString.Format("无对应的序号为%d的数据!!", iBegin);

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

		ReportLog(pDoc, pTask, RET_OK, "历史任务", "");

		return RET_OK;
	}

	//CRC检测
	if( !CRCValid(ucRawData) )
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "历史任务", "CRC校验错!");	
	}

	nFlowNo = ucRawData[6]*256+ucRawData[7];
	if( nFlowNo == iBegin )
	{
		if( OutputRealData(pTask, pDocEx->pChildDoc[pDocEx->nPortNo], 0x22, (unsigned char*)ucRawData, 256) != RET_OK )
		{
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
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
			ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, RET_TERME_NOANSWER, "历史任务", "金仕达中间传输层无反应!");
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


//MARK值错
bool CHistoryData::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	CString strString;
	switch(nMark)
	{
	case 0x0b: //授权号不对
		strString.Format("历史收集时授权号不对! 数据为:%s", pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, nMark, "历史任务", strString.GetBuffer(0));
		ModifyRegister(pDoc, pBuffer);
		break;
	case 0x05: //
		strString.Format("历史收集时Mark不对! 流水号错:%s", pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, nMark, "历史任务", strString.GetBuffer(0));
		TerminateTask();
		break;
	default:
		ReportLog(pDoc, pTask, nMark, "历史任务", "历史收集时Mark不对!");
		printf("3---历史收集时Mark不对!\n");
		ResetDevice(pDoc, pBuffer);
		break;
	}
	return true;
}

void CHistoryData::OnCRCError()
{

}

