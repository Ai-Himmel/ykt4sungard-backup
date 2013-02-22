// Operator.cpp: implementation of the COperator class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Application.h"
#include "Operator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static COperator::TSMacTypeArray  MacTypeArray[] =
{
	MACHINE_TYPE_5301, "5301", "������", 
	MACHINE_TYPE_0201, "0201", "��ֵ��", 
	MACHINE_TYPE_0226, "0226", "�շѻ�", 
	MACHINE_TYPE_0228, "0228", "���ػ�", 
	MACHINE_TYPE_0230, "0230", "�����", 
	MACHINE_TYPE_0232, "0232", "�ϻ�������", 
	MACHINE_TYPE_0234, "0234", "��ԡ�����", 
	MACHINE_TYPE_0240, "0240", "��Ʊ��", 
	MACHINE_TYPE_0130, "0130", "���ʶ���", 
	MACHINE_TYPE_0140, "0140", "��Ʊ��", 
	MACHINE_TYPE_0121, "0121", "��ʱ��", 
	MACHINE_TYPE_0224, "0224", "��ʧ��", 
	MACHINE_TYPE_UNKNOW, "UNKNOW", "δ֪�Ļ���" 
};

static COperator::TSMacDataTypeArray  MacDataArray[] = 
{
	MACDATA_TYPE_JY,  0x01,  "Ϊ������������",
	MACDATA_TYPE_ZZ,  0x17,  "Ϊ��������",
	MACDATA_TYPE_BZ,  0x1b,  "Ϊ��������",
	MACDATA_TYPE_UNKNOW,  0x00,  "δ֪����������"
};

CString  COperator::m_strAccTime = "";		//��ʱ����ʱ��
CString  COperator::m_strBlackVer = "";     //�������汾
CString  COperator::m_strRight = "";        //��Ȩ��
bool     COperator::m_bReadPara = false;    //�Ѷ��������־
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
COperator::COperator()
{
	m_bMachineNo = true ;
	m_bMarkCheck = false;
	m_strTaskCode = "" ;

	m_pDocEx = NULL ;
	m_pBuffer = NULL ;
	m_pTask = NULL ;

	m_pDoc = NULL ;
	m_nIndex = -1;
	m_nPort  = -1;
}

COperator::~COperator()
{

}

void COperator::InitInstance()
{
	EnterCriticalSection(&Lock);

	if( !m_bReadPara )
	{
		ReadSmartSetup();
	}

	LeaveCriticalSection(&Lock);
}

void COperator::ExitInstance()
{

}

//����Smart_Setup���еĲ���
bool COperator::ReadSmartSetup()
{
	TSSystemParam  Parameter;

	if( GetParameter(0, &Parameter) == RET_OK )
	{
		m_strAccTime = Parameter.szParameter1 ;
		m_strRight = Parameter.szParameter2 ;
		m_strBlackVer = Parameter.szParameter3 ;
		m_bReadPara = true ;
	}
	else
		m_bReadPara = false;

	return m_bReadPara;


}

void COperator::WriteFile(char *pszFileName, char *pBuffer)
{
	FILE *fp;
	if( (fp=fopen(pszFileName, "a+")) != NULL )
	{
		TCHAR  szLog[512];
		SYSTEMTIME  SysTime;

		GetLocalTime(&SysTime);

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d %s\n", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

//дϵͳ�쳣��־
void COperator::WriteError(char *pszDeviceID, const char *format, ...)
{
	TCHAR   sBuffer[256];
	TCHAR   szFileName[MAX_PATH];
	va_list ptr;
	CTime   t = CTime::GetCurrentTime();

	wsprintf(szFileName, "%s\\%04d%02d%02d_%s.txt", szErrorLogPath, 
		t.GetYear(), t.GetMonth(), t.GetDay(), pszDeviceID);

	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	WriteFile(szFileName, sBuffer);
	//BroadMessage(sBuffer, strlen(sBuffer));

	printf("%s\n", sBuffer);
}

//������������
long COperator::ProcessRequest(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	m_pBuffer = pBuffer;
	m_pTask = pTask;
	m_pDocEx = pDocEx;
	m_nIndex = pDocEx->nPortNo;
	m_nPort = m_nIndex ;
	m_pDoc = pDocEx->pChildDoc[m_nPort];

	//����ʷ��ʱ, �ն˿����޷�Ӧ, pBufferΪ��, ֱ�Ӵ���
	if( pBuffer == NULL )
	{
		if( !IsSupportMacType() )
		{
			OnMacTypeError();
			return RET_NOTSUPPORT;
		}
		else
			return ProcessData(pDocEx, pTask, pBuffer);
	}

	//�Ƿ�Ϊ�Ϸ��������
	long nRet = UnMakeDeviceBuffer(pBuffer) ;
	if( nRet != RET_OK )
	{
		OnPacketError(nRet);
//		return RET_VALIDPACKET;
	}

	char ucRawData[256];
	char sTemp[128];
	int nLen = 0;

	memset(ucRawData, 0, sizeof(ucRawData));
	sprintf(ucRawData, "%d&", pDocEx->pChildDoc[m_nIndex]->m_nAuthID);

	//������
	if( pDocEx->pChildDoc[m_nIndex]->m_nParentID == 0 && !strcmp(pDocEx->pChildDoc[m_nIndex]->m_szMacCode, "5301") )
	{
		//MARKֵ���
		if( nRet == RET_OK )
		{
			if( pBuffer->pBuffer[2] == 0x00 )
			{
				sprintf(sTemp, "%d&", 0);
			}
			else
			{
				sprintf(sTemp, "%d&", pBuffer->pBuffer[2]);
			}
		}
		else
		{
			sprintf(sTemp, "%d&", nRet);
		}
		strcat(ucRawData, sTemp);

		nLen = strlen(ucRawData);
		memcpy(ucRawData+nLen, &pBuffer->pBuffer[4], pBuffer->pBuffer[6]+3);
		nLen += pBuffer->pBuffer[3];
	}
	else
	{
		//MARKֵ���
		if( nRet == RET_OK )
		{
			if( pBuffer->pBuffer[2] == 0x00 )
			{
				sprintf(sTemp, "%d", 0);
			}
			else
			{
				sprintf(sTemp, "%d", pBuffer->pBuffer[2]);
			}
		}
		else
		{
			sprintf(sTemp, "%d", nRet);
		}
		strcat(ucRawData, sTemp);
		nLen = strlen(ucRawData);
	}

	BroadcastPro(PACKET_CMD_1001, pDocEx->pChildDoc[m_nIndex], 
		ucRawData, nLen);

	if( nRet != RET_OK )
 		return RET_VALIDPACKET;

	//�Ƿ�֧�ֱ��豸����
	if( !IsSupportMacType() )
	{
		OnMacTypeError();
		return RET_NOTSUPPORT;
	}

	//���ż��
	if( m_bMachineNo )
	{
		if( !CheckMachineNo(pDocEx, pBuffer) )
		{
			OnMachineNoError(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer->pBuffer[1]);
			return RET_VALIDMACNO;
		}
	}

	//���markֵ
	if( m_bMarkCheck )
	{
		int nMark = pBuffer->pBuffer[2];

		if( !CheckMarkValue(nMark) )
		{
			bool bResult = OnMarkValueError(m_pDocEx->pChildDoc[m_nIndex], m_pTask, m_pBuffer, nMark);
			if( pDocEx->nChildDoc <= 1 )
			{
				strcpy(m_pDocEx->pDeviceInfo->sRegNo, m_pDocEx->pChildDoc[m_nIndex]->m_szRegister);
			}

			if( !bResult )
				return RET_NG;
		}
	}

	return ProcessData(pDocEx, pTask, pBuffer);
}

//�Ƿ�Ϊ��ͬ���������
CString COperator::GetTaskCode() const
{
	return m_strTaskCode;
}

//�б������Ƿ����
bool COperator::IsEqual(CString strTaskCode) const
{
	return m_strTaskCode==strTaskCode?true:false;
}

bool COperator::IsSupportMacType()
{
	return true;
}

//CRC���
bool COperator::CRCValid(BYTE *pszByte, int nPos)
{
	unsigned char out[3];
	calc_crc16(nPos, pszByte, out);
	if( pszByte[nPos] == out[0] && pszByte[nPos+1] == out[1] )
		return true;
	else
	{
		OnCRCError();
		return false;
	}
}

bool COperator::CheckMarkValue(int nMark)
{
	return (nMark==0x00?true:false);
}

//������ݰ�
bool COperator::CheckPacket(TSCmdBuffer *pBuffer)
{
	long nResult = UnMakeDeviceBuffer(pBuffer) ;
	if( nResult == RET_OK ) 
		return true;
	else
	{
		OnPacketError(nResult);
		return false;
	}
}

//��ⷵ������������Ƿ����
bool COperator::CheckMachineNo(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer)
{
	int nNo = pDocEx->nPortNo ;
	if( pBuffer->pBuffer[1] == pDocEx->pChildDoc[nNo]->m_nMachineNo )
		return true;
	else
	{
		return false;
	}
}

//�õ����ʹ���
MachineType COperator::GetMachineType(TSSmartDoc *pSmartDoc)
{
	int i=0;

	while( MacTypeArray[i].nType != MACHINE_TYPE_UNKNOW )
	{
		if( !strcmp(pSmartDoc->m_szMacCode, MacTypeArray[i].pCode) )
			return MacTypeArray[i].nType;
		i++;
	}

	return MACHINE_TYPE_UNKNOW;
}

//�õ���������
MacDataType COperator::GetMacDataType(TSCmdBuffer *pBuffer)
{
	unsigned char ucRawData[256];

	memset(ucRawData, 0, sizeof(ucRawData));

#ifdef __DEBUG_OUTPUT__
/*	for(int k=0; k< 256; k++)
	{
		printf("%02X ", pBuffer->pBuffer[k]);
	}
	printf("\n");*/
#endif

	memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
	int nTotalPortNo = ucRawData[2];

	int i=0;
	while( MacDataArray[i].nType != MACDATA_TYPE_UNKNOW )
	{
		if( ucRawData[4+nTotalPortNo] == MacDataArray[i].nCode ) 
			return MacDataArray[i].nType;
		i++;
	}

	return MACDATA_TYPE_UNKNOW;
}


//��λ�豸
bool COperator::ResetDevice(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	bool bRet = false;

	switch( GetMachineType(pDoc) )
	{
	case MACHINE_TYPE_5301:
		{
			for(int i=0; i<3; i++)
			{
				MakeBuf_RemoteReset(&pDoc->DeviceInfo, pBuffer);
				if(SendRequest(pDoc, pBuffer) == RET_OK )
				{	
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK ) 
					{
						bRet = true;
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return bRet;
}

//�޸�ע���
bool COperator::ModifyRegister(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	unsigned char newRegNo[4];
	bool bRet = false;

	unsigned char sID[256];

	memset(sID, 0, sizeof(sID));
	SVC_DSP_2_HEX((BYTE*)pDoc->m_szDeviceID, sID, 4);
	sID[4] = pDoc->DeviceInfo.nAddr;

	MakeBuf_SetAddr(&pDoc->DeviceInfo, pBuffer, sID);
	for(int k=0; k<3; k++)
	{
		if( SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				bRet = true;
				break;
			}
		}
	}

#if 0 
	MakeBuf_GetID(&pDoc->DeviceInfo, pBuffer);
	for(int k=0; k<3; k++)
	{
		if(SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				unsigned char szTemp[256];
				unsigned char *pHardBuffer = pBuffer->pBuffer+4;

				memset(szTemp, 0, sizeof(szTemp));
				SVC_HEX_2_DSP(pHardBuffer, szTemp, 4);

				if( strcmp(pDoc->m_szDeviceID, ( char*)szTemp) )
				{
					printf("�豸ID��ͬ, ���ܸ���ע���!\n");
					return false;
				}
				else
				{
					//strcpy(pDoc->m_szDeviceID, ( char*)szTemp);
					bRet = true;
					break;
				}
			}
		}
	}
#endif

	if( !bRet )
	{
		printf("�豸ID��ͬ, ���ܸ���ע���!\n");
		return false;
	}

	bRet = false;
	MakeBuf_Debug_GetMainPar(&pDoc->DeviceInfo, pBuffer);
	for(k=0; k<3; k++)
	{
		if( SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				char szReg[32];
				memset(szReg, 0, sizeof(szReg));

				if( !strcmp(pDoc->m_szMacCode, "5301") || pDoc->m_nParentID > 0 )
					SVC_HEX_2_DSP(pBuffer->pBuffer+8, (unsigned char*)szReg, 4);
				else
					SVC_HEX_2_DSP(pBuffer->pBuffer+4, (unsigned char*)szReg, 4);

				strcpy(pDoc->m_szRegister, ( char*)szReg);
				strcpy(pDoc->DeviceInfo.sRegNo, ( char*)szReg);

				printf("��������ʹ�õ�ע���........%s...!\n", ( char*)szReg);

				bRet = true;
				break;
			}
		}
	}

	if( !bRet )
	{
		return false;
	}

	bRet = false;
	switch( GetMachineType(pDoc) )
	{
	case MACHINE_TYPE_5301:
		{
			for(int i=0;i<3;i++)
			{
				SVC_DSP_2_HEX((unsigned char *)pDoc->m_szRegister, newRegNo, 4);
				MakeBuf_SetLportNewRegNo(&pDoc->DeviceInfo, pBuffer, newRegNo);
				if(SendRequest(pDoc, pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
					{
						bRet = true;
						break;
					}
				}
			}
		}
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
		{
			//��ѯ�ն�
			CString strSQL;
			strSQL.Format("SELECT * FROM Smart_Machine WHERE SMT_Authno = %d", pDoc->m_nAuthID);
			unsigned char sBuffer[256];
			char sValue[256];
	
		//	GetFieldStringValueEx(nRec, "Smt_RegNo", (char*)sValue);
		//	SVC_DSP_2_HEX(sValue, sBuffer, 4);

			for(int i=0;i<3;i++)
			{
				MakeBuf_SetRegNo(&pDoc->DeviceInfo, pBuffer, sBuffer);
				if(SendRequest(pDoc, pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
					{
						strcpy(pDoc->m_szRegister, ( char*)sValue);
						strcpy(pDoc->DeviceInfo.sRegNo, ( char*)sValue);
						//bRet = true;
						printf("����ע���Ϊ........%s...!\n", ( char*)sValue);
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return bRet;
}

//�޸�ע���
bool COperator::ModifyRegisterEx(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int nPort)
{
	bool bRet = false;
	unsigned char Buffer[256];

	switch(GetMachineType(pDocEx->pChildDoc[pDocEx->nPortNo]) )
	{
	case MACHINE_TYPE_5301:
		{
			TSDeviceInfo  Info;

			bool bFound = false;
			unsigned char  sPortID[16];
			memset(sPortID, 0, sizeof(sPortID));

			for( int p=0; p<3; p++)
			{
				MakeBuf_SearchPort(&pDocEx->pChildDoc[0]->DeviceInfo, pBuffer, nPort);
				if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
					{
						bFound = true;
						break;
					}
				}
			}

			if( !bFound )
			{
				printf("�����˿�%dʧ��! �����޸Ķ˿�ע���!\n", nPort);
				return false;
			}

			bFound = false ;

			for( p =0; p < 3; p++ )
			{
				MakeBuf_GetPortPar(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, nPort);
				if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
					{
						bFound = true;
						SVC_HEX_2_DSP(&pBuffer->pBuffer[4], sPortID, 4);
						break;
					}
				}
			}

			if( !bFound )
			{
				printf("�õ��˿�%d���豸ʧ��! �����޸Ķ˿�ע���!\n", nPort);
				return false;
			}

			//ƥ��ԭ���˿ڵ�Ӳ��
			int nIndex = GetPos(pDocEx, nPort);
			if( nIndex <= 0 )
			{
				printf("�˿�%d��Ӳ���䶯! �豸��������û�д��ն˼�¼! �豸ID:%s\n", nPort, sPortID);
/*				MakeBuf_ClearPortData(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, nPort);
				if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
					{
						return true;
					}
				}*/
				return false;
			}

			//�Ƚ��豸ID
			if( strcmp((char*)sPortID, pDocEx->pChildDoc[nIndex]->m_szDeviceID) )
			{
				printf("�˿�%d���豸�Ѹ���, ���Ҷ˿�%d���µ�����豸!\n", nPort, nPort);
				nIndex = GetPosEx(pDocEx, (char*)sPortID);
				if( nIndex <= 0 )
				{
					printf("�˿�%d(�豸ID:%s) ���ն��豸%s���豸ID��ͬ, �����޸Ķ˿�ע���!\n", 
						nPort, sPortID, pDocEx->pChildDoc[nIndex]->m_szRegister);
					return false;
				}
			}

/*			if( pBuffer->pBuffer[8] != pDocEx->pChildDoc[nIndex]->DeviceInfo.nAddr )
			{
				printf("�˿�%d(����:%d) ���ն��豸%s(����:%d)�Ļ��Ų�ͬ, �����޸Ķ˿�ע���!\n", nPort, pBuffer->pBuffer[8] ,
					pDocEx->pChildDoc[nIndex]->m_szRegister, pDocEx->pChildDoc[nIndex]->DeviceInfo.nAddr);
				return false;
			}
*/
			printf("�˿�:%d, �˿��豸ID��:%s ,���ն��豸ID��ͬ, ׼���޸Ķ˿�ע���Ϊ:%s!\n", nPort, sPortID, pDocEx->pChildDoc[nIndex]->m_szRegister);

			memcpy(&Info, &pDocEx->pChildDoc[nIndex]->DeviceInfo, sizeof(Info));

			//����Lport�������ö˿�ע���
			for( int n=0; n<3; n++)
			{
				SVC_DSP_2_HEX((unsigned char *)pDocEx->pChildDoc[nIndex]->m_szRegister, Buffer, 4);
				MakeBuf_SetPortRegNoAndMacNo(
					pDocEx->pDeviceInfo, pBuffer, nPort, Buffer, pDocEx->pChildDoc[nIndex]->DeviceInfo.nAddr);
				if ( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
				{
					if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
					{
						CString strText;

						strText.Format("�˿�%dע�����ʵ��ע��Ų���! �޸Ķ˿�%dע��ųɹ�!", nPort, nPort); 
						ReportLog(pDocEx, NULL, RET_OK, "ʵʱ�ռ�", strText.GetBuffer(0)); 
						printf("%s\n", strText.GetBuffer(0));
						bRet = true;
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}

	return bRet;
}


//����˿�����
bool COperator::ClearPortData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer, int nPortNo)
{
	bool bRet = false;

	switch( GetMachineType(pDoc) )
	{
	case MACHINE_TYPE_5301:
		{
			for(int i=0; i<3; i++)
			{
				MakeBuf_ClearPortData(&pDoc->DeviceInfo, pBuffer, nPortNo);
				if(SendRequest(pDoc, pBuffer) == RET_OK )
				{	
					if( UnMakeDeviceBuffer(pBuffer) != RET_OK ) 
					{
						bRet = true;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return bRet;
}

void COperator::OnPacketError(long nResult)
{
	char  szString[128];
	sprintf(szString, "CRC��! �������%d", nResult);
	ReportLog(m_pDocEx->pChildDoc[m_pDocEx->nPortNo], m_pTask, RET_SYSERROR, "ʵʱ�ռ�", szString);
}

void COperator::OnMacTypeError()
{

}

//���Ŵ���
void COperator::OnMachineNoError(TSSmartDoc *pDoc, int nNo)
{
	ReportLog(pDoc, m_pTask, RET_SYSERROR, "ʵʱ�ռ�", "���ػ��Ų���!");

	CString sSQL;
	sSQL.Format("UPDATE smart_machine SET smt_machineno=%d WHERE smt_authno=%ld", nNo, pDoc->m_nAuthID);
	return ;
}

void COperator::OnCRCError()
{

}

//MARKֵ��
bool COperator::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	return true;
}

//��Ȩ�Ų�����
void COperator::OnAuthNoError(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	switch(GetMachineType(pDoc))
	{
	case MACHINE_TYPE_5301:
		ReportException("�ռ�LPort����ʱ, ������Ȩ�Ų��� ��������Ϊ:", pBuffer->pBuffer, pBuffer->pBuffer[3]+7);
		if( !ModifyRegister(pDoc, pBuffer) )
			WriteLog("�ռ�LPort:%d����ʱ, ������Ȩ�Ų���, �޸�LPortע���ʱ����!", pDoc->m_nAuthID);
		break;
	default:
		break;
	}
}

void COperator::ReportException(CString strText, BYTE *pszByte, int nLen)
{
     CString strData = "" ;
	 CString strTmp;

	 for(int i=0; i< nLen; i++)
	 {
		strTmp.Format("%.2X", pszByte[i]);
 		strData += strTmp;
	 }
	 WriteLog(strText, strData);
}

void COperator::TerminateTask(int nFlag)
{
	m_pDoc->m_nTerminate = nFlag ;
	printf("The COperator::TerminateTask(%d) is call......................\n", nFlag);
}

//�޸�����
bool COperator::ModifyPassword(TSSmartTask *pTask, TSSmartDoc *pDoc, unsigned char *ucRawData)
{
	int cardid = ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10]; //���׿���
	unsigned char OldPassWord[17];
	unsigned char NewPassWord[17];

	memset(OldPassWord, 0, sizeof(OldPassWord));
	memset(NewPassWord, 0, sizeof(NewPassWord));

	TSGSJRecord  Data;
	char cCardSerialNo[256];//�����к�

	memset(cCardSerialNo, 0, sizeof(cCardSerialNo));
	memset(&Data, 0, sizeof(Data));
	Data.nCardID = cardid;
	if( ReadCardGSInfo(0x83, &Data) != RET_OK )
	{
		printf("�޸�����ʱ���ܶ�����Ϣ!\n");
		WriteLog("�޸�����ʱ����˴�ͨѶ,��ȡ�����к�ʧ��"); //add by lina 20040308
		return false ;
	}
	else
	{
		sprintf(cCardSerialNo, "%10u", HexToDWORD(Data.szSerial));
	//	strcpy(cCardSerialNo, "3100000114");
	//printf(cCardSerialNo, "%10u", HexToDWORD("A2E7BE57"));
		WriteLog("�����к�%s",cCardSerialNo);
	}
	
	//printf("�޸�����ʱ���뿨����Ϣ, ����:%d, ��������к�:%s.............\n", cardid, cCardSerialNo);
	WriteLog("�޸�����ʱ���뿨����Ϣ, ����:%d, ��������к�:%s.............\n", cardid, cCardSerialNo);

	DWORD nSerial = atol(cCardSerialNo);

	//������  
	OldPassWord[0] = ucRawData[17]; //^ ((unsigned char)(nSerial%256));
	OldPassWord[1] = ucRawData[18];// ^ ((unsigned char)(nSerial/256%256));
	OldPassWord[2] = ucRawData[19];// ^ ((unsigned char)(nSerial/65536%256));
	
	CString strCS1;
	strCS1.Format("%.2X%.2X%.2X",OldPassWord[0],OldPassWord[1],OldPassWord[2]);

	//������
	NewPassWord[0] = ucRawData[20];// ^ ((unsigned char)(nSerial%256));
	NewPassWord[1] = ucRawData[21];// ^ ((unsigned char)(nSerial/256%256));
	NewPassWord[2] = ucRawData[22];// ^ ((unsigned char)(nSerial/65536%256));

	CString strCS2;
	strCS2.Format("%.2X%.2X%.2X",NewPassWord[0],NewPassWord[1],NewPassWord[2]);

	//printf("�޸�����, ����:%d..������:%s, ������:%s............\n", cardid, strCS1.GetBuffer(0), strCS2.GetBuffer(0));
	WriteLog("�޸�����, ����:%d..������:%s, ������:%s\n", cardid, strCS1.GetBuffer(0), strCS2.GetBuffer(0));
	memset(&Data, 0, sizeof(Data));

	Data.nCardID = cardid;
	strcpy(Data.szDeviceID, pDoc->m_szDeviceID);
	strcpy(Data.szPassword, strCS2.GetBuffer(0));
	sprintf(Data.szCRC, "%.2X%.2X", ucRawData[26],ucRawData[27]);

	return OutputRealData(pTask, pDoc, 0x83, (unsigned char*)&Data, sizeof(Data))==RET_OK?true:false;
}

//��֧��2��
int COperator::GetPos(TSSmartDocEx *pDocEx, long nPort)
{
	if( nPort == 0 )
		return nPort;

	if( pDocEx != NULL )
	{
		for(int i=0; i< pDocEx->nChildDoc; i++)
		{
			if( pDocEx->pChildDoc[i]->m_nParentID > 0 && 
				pDocEx->pChildDoc[i]->m_nSMTPort == nPort && 
				pDocEx->pChildDoc[i]->m_nStatus != 9 ) 
			{
				return i;
			}
		}
	}
	return -1;
}

int COperator::GetPos(TSSmartDocEx *pDocEx, char *pszReg)
{
	if( pDocEx != NULL )
	{
		for(int i=0; i< pDocEx->nChildDoc; i++)
		{
			if( pDocEx->pChildDoc[i]->m_nParentID > 0 && 
				pDocEx->pChildDoc[i]->m_nStatus != 9 && 
				!strcmp(pDocEx->pChildDoc[i]->m_szRegister, pszReg) )
			{
				return i;
			}
		}
	}

	return -1;
}	

int COperator::GetPosEx(TSSmartDocEx *pDocEx, char *pszID)
{
	if( pDocEx != NULL )
	{
		for(int i=0; i< pDocEx->nChildDoc; i++)
		{
			if( pDocEx->pChildDoc[i]->m_nSMTPort > 0 && 
				pDocEx->pChildDoc[i]->m_nStatus != 9 && 
				!strcmp(pDocEx->pChildDoc[i]->m_szDeviceID, pszID) )
			{
				return i;
			}
		}
	}

	return -1;
}	

//���豸�������е�ע��Ÿ��Ķ˿ڼ��ն˵�ע���
bool COperator::ModifyDocRegister(TSSmartDocEx *pDocEx, TSSmartDoc *pDoc, TSCmdBuffer *pBuffer, int nPort, char *szOldReg)
{
	unsigned char newRegNo[4];
	char  szNewReg[32];
	bool bRet = false;

	strcpy(szNewReg, pDoc->DeviceInfo.sRegNo);
	strcpy(pDoc->DeviceInfo.sRegNo, szOldReg);

	unsigned char sID[256];

	memset(sID, 0, sizeof(sID));
	SVC_DSP_2_HEX((BYTE*)pDoc->m_szDeviceID, sID, 4);
	sID[4] = pDoc->DeviceInfo.nAddr;

	MakeBuf_SetAddr(&pDoc->DeviceInfo, pBuffer, sID);
	for(int k=0; k<3; k++)
	{
		if( SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				bRet = true;
				break;
			}
		}
		else
		{
			Sleep(200);
		}
	}

	if( !bRet )
	{
		strcpy(pDoc->DeviceInfo.sRegNo, szNewReg);
		return false;
	}

#if 0	
	MakeBuf_GetID(&pDoc->DeviceInfo, pBuffer);
	for(int k=0; k<3; k++)
	{
		if(SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				unsigned char szTemp[256];
				unsigned char *pHardBuffer = pBuffer->pBuffer+4;

				memset(szTemp, 0, sizeof(szTemp));
				SVC_HEX_2_DSP(pHardBuffer, szTemp, 4);

				if( strcmp(pDoc->m_szDeviceID, ( char*)szTemp) )
				{
					printf("�豸ID��ͬ, ���ܸ���ע���!\n");
					strcpy(pDoc->DeviceInfo.sRegNo, szNewReg);
					return false;
				}
				else
				{
					bRet = true;
					break;
				}
			}
		}
		else
		{
			Sleep(1000);
		}
	}
#endif 

/*	MakeBuf_SearchPort(&pDocEx->pChildDoc[0]->DeviceInfo, pBuffer, nPort);
	if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
	{
		UnMakeDeviceBuffer(pBuffer);
	}
*/
	bRet = false ;
	for( k =0; k < 3; k++ )
	{
		MakeBuf_GetPortPar(&pDocEx->pChildDoc[0]->DeviceInfo, pBuffer, nPort);
		if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
			{
				unsigned char sPortID[16];
				memset(sPortID, 0, sizeof(sPortID));

				SVC_HEX_2_DSP(&pBuffer->pBuffer[4], sPortID, 4);

			//	strcpy(pDoc->DeviceInfo.sRegNo, (char*)sPortID);
				bRet = true;
				break;
			}
		}
		else
		{
			Sleep(1000);
		}
	}

	if( !bRet )
	{
		strcpy(pDoc->DeviceInfo.sRegNo, szNewReg);
		return bRet;
	}

	int nOldAdd = pDoc->DeviceInfo.nAddr;
	pDoc->DeviceInfo.nAddr = pBuffer->pBuffer[8];

	bRet = false;
	SVC_DSP_2_HEX((unsigned char*)pDoc->m_szRegister, newRegNo, 4);
	MakeBuf_SetRegNo(&pDoc->DeviceInfo, pBuffer, newRegNo);

	for(k=0; k<3; k++)
	{
		if( SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				printf("�޸�ע��ųɹ�!\n");
				bRet = true;
				break;
			}
		}
		else
		{
			Sleep(1000);
		}
	}

	if( !bRet )
	{
		strcpy(pDoc->DeviceInfo.sRegNo, szNewReg);
		pDoc->DeviceInfo.nAddr = nOldAdd;
		return bRet;
	}

	bRet = false;
	for(int i=0;i<3;i++)
	{
		MakeBuf_SetPortRegNoAndMacNo(
			pDocEx->pDeviceInfo, pBuffer, nPort, newRegNo, nOldAdd);
		if(SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				bRet = true;
				break;
			}
		}
	}
	return bRet;
}
