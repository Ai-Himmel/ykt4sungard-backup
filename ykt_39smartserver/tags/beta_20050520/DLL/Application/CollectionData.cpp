// CollectionData.cpp: implementation of the CCollectionData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "CollectionData.h"
#include "SRCTable.h"
#include "JZSRCTable.h"
#include "SmartTask.h"
#include "SingInServer.h"
#include "CheckBlackVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long iCount = 0 ;
DWORD dwLastTime = 0 ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCollectionData::CCollectionData()
{
	m_bMarkCheck = true ;
	m_strTaskCode = "01";
}

CCollectionData::~CCollectionData()
{

}

long CCollectionData::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	pDocEx->pChildDoc[pDocEx->nPortNo]->m_dwLastTick = GetTickCount();
	pDocEx->pChildDoc[0]->m_dwTryCount = GetTickCount();

	MakeBuf_CollectData(pDocEx->pDeviceInfo, pBuffer);
	return RET_OK;
}

//*----------------------------------------------------------------------------
//*函数: long ProcessRequest()
//*功能: 处理具体的业务请求
//*参数: 无
//*返回: 见系统返回值说明
//*说明: 
//*----------------------------------------------------------------------------
long CCollectionData::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int nIndex = m_pDocEx->nPortNo ;
	long nRet = RET_NG;


	//接收成功统计
	InterlockedExchangeAdd((LONG*)&gSendRecv, (LONG)(GetTickCount()- pDocEx->pChildDoc[pDocEx->nPortNo]->m_dwLastTick));
	InterlockedIncrement((LONG*)&gTrySendRecv);

	switch(GetMachineType(m_pDocEx->pChildDoc[nIndex]))
	{
	case MACHINE_TYPE_5301://服务器
		nRet = LPort_Process(pDocEx,pTask,pBuffer);
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
		{
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			/*for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");*/
#endif
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("机器%d申请签到!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_DealTypeData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	case MACHINE_TYPE_0121://计时宝
		{
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");
#endif
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("机器%d申请签到!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_IdentifyData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	case MACHINE_TYPE_0224://挂失机
		{
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");
#endif
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("机器%d申请签到!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_GSJData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	default:
		break;
	}

	return nRet;
}

//*----------------------------------------------------------------------------
//*函数: long LPort_DataProcess(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer)
//*功能: 处理具体的业务请求
//*参数: 无
//*返回: 见系统返回值说明
//*说明: 
//*----------------------------------------------------------------------------
long CCollectionData::LPort_Process(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer)
{
//	printf("处理LPORT%.8X数据\n",pDocEx->pChildDoc[0]->m_nAuthID);
	unsigned char ucRawData[256];
	int nTotalPortNo, nPortNo;
	
	memset(ucRawData, 0, sizeof(ucRawData));

	memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
#ifdef __DEBUG_OUTPUT__
	for(int i=0; i< 256; i++)
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");
#endif

	int nTempLen = pBuffer->nCmdSize ;
	unsigned char sTempData[256];
	memcpy(sTempData, pBuffer->pBuffer, 256);

	//不等于端口总数
	if( ucRawData[2] != pDocEx->pChildDoc[pDocEx->nPortNo]->m_nPortCount )
	{
		CString strString;

		strString.Format("收集LPort数据时, 返回的端口总数与数据库端口总数不相等. 返回的端口数为:%d, 档案表为:%d! 您的LPort参数设置不正确, 请重新校对LPort的参数", 
			ucRawData[2], pDocEx->pChildDoc[0]->m_nPortCount);
		ReportLog(pDocEx, pTask, RET_SYSERROR, "实时收数", strString.GetBuffer(0) );

		if( !ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) )
		{
			printf("1---实时收集LPORT数据时,返回的端口总数不等于参数内的端口总数\n");
			ReportLog(pDocEx, pTask, RET_SYSERROR, "实时收数", "收集LPort数据时, 由于返回的端口总数不相等, 复位时出错!");
		}

		return RET_SYSERROR;
	}
/*	LportState(pDocEx,pTask,pBuffer,ucRawData);
	if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		InterlockedIncrement((LONG*)&gNotFound);
		//Sleep(50);
		return RET_NG;
	}*/

	nTotalPortNo = ucRawData[2];
	nPortNo = ucRawData[3+nTotalPortNo];

	//端口数不对, 复位
	if( nPortNo > nTotalPortNo )
	{
		printf("1---实时收集LPORT数据时,返回的端口总数不等于参数内的端口总数\n");
		ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer);
		return RET_SYSERROR;
	}

	nPortNo = GetPos(pDocEx, nPortNo);

	pBuffer->nCmdSize = nTempLen;
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(pBuffer->pBuffer, sTempData, 256);

	long nRet = RET_NG ;
	switch(GetMacDataType(pBuffer))
	{
	case MACDATA_TYPE_JY://为交易类型数据
		{
		int nType = MACHINE_TYPE_5301 ;

		if( nPortNo < 0 )
		{
			char szDataReg[32];
			sprintf(szDataReg, "%.2X%.2X%.2X%.2X", ucRawData[5+nTotalPortNo],ucRawData[6+nTotalPortNo],ucRawData[7+nTotalPortNo],ucRawData[8+nTotalPortNo]);
			if( nPortNo < 0 )
			{
				//是否在本服务器内
				int iPos = GetPos(pDocEx, szDataReg);
				if( iPos > 0 )
				{
					nPortNo = iPos;
				}
				else
				{
					TSSmartDoc doc;

					//档案表中有数据
					if( FindMachine(szDataReg, &doc) )
						nType = GetMachineType(&doc);
				}
			}
		}
		nType = GetMachineType(pDocEx->pChildDoc[nPortNo]);

		switch( nType) 
		{
		case MACHINE_TYPE_5301://服务器
		case MACHINE_TYPE_0201://增值机
		case MACHINE_TYPE_0226://收费机
		case MACHINE_TYPE_0228://车载机
		case MACHINE_TYPE_0230://管理机
		case MACHINE_TYPE_0232://上机上网机
		case MACHINE_TYPE_0234://淋浴管理机
		case MACHINE_TYPE_0240://售票机
		case MACHINE_TYPE_0130://身份识别机
		case MACHINE_TYPE_0140://检票机
			nRet = Process_DealTypeData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		case MACHINE_TYPE_0121://计时宝
			nRet = Process_IdentifyData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		case MACHINE_TYPE_0224://挂失机
			nRet = Process_GSJData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		default:
			break;
		}
		}
		break;
	case MACDATA_TYPE_ZZ://为扎帐数据
		nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],pDocEx->nPortNo);
		break;
	case MACDATA_TYPE_BZ://为补助数据
		nRet = Process_AssisData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	default:
		break;
	}
		LportState(pDocEx,pTask,pBuffer,ucRawData);
	/*if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		InterlockedIncrement((LONG*)&gNotFound);
		Sleep(50);
		//printf("处理LPORT%.8X状态返回\n",pDocEx->pChildDoc[0]->m_nAuthID);

		return RET_NG;
	}*/
	Sleep(100);
	return nRet;
}

bool CCollectionData::ConfirmJZData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, 
								    unsigned char *ucFlowNo,int nPortNo,int nRetryNo)
{
	if( !strcmp(pDocEx->pChildDoc[0]->m_szMacCode, "5301") )
	{
		return ConfirmData(pDocEx, pTask, pBuffer, ucFlowNo, nPortNo, nRetryNo);
	}
	else
	{
		for(int i=0; i<nRetryNo; i++)
		{
			MakeBuf_ConfirmStateData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
			if( SendRequest(pDocEx->pChildDoc[nPortNo], pBuffer) == RET_OK )
			{
				//做标记成功，退出
				if( UnMakeDeviceBuffer(pBuffer) == RET_OK && 
					pBuffer->pBuffer[2]==0x00 ) 
				{
					return true;
				}
			}
			else
			{
				printf("做结帐数据标志失败!\n");
				Sleep(30);
			}
		}
	}

	return false;
}

//确认数据数据流程
bool CCollectionData::ConfirmData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, 
								    unsigned char *ucFlowNo,int nPortNo,int nRetryNo)
{
	DWORD dwTick = GetTickCount();

	for(int i=0; i<nRetryNo; i++)
	{
		MakeBuf_ConfirmData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
		
		if( SendRequest(pDocEx->pChildDoc[nPortNo], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK ) 
			{
				//if(pBuffer->pBuffer[1] == pDocEx->pChildDoc[nPortNo]->m_nMachineNo)
				{
					//做标记成功，退出
					if(pBuffer->pBuffer[2]==0x00)
					{
						//接收成功统计
						InterlockedExchangeAdd((LONG*)&gMark, (LONG)(GetTickCount()-dwTick));
						InterlockedIncrement((LONG*)&gTryMark);
						return true;
					}
				}
			}
			else
			{
				printf("做交易数据标志不成功!\n");
				Sleep(1000);
			}
		}
		else
		{
			Sleep(1000);
		}
	}

	ReportLog(pDocEx->pChildDoc[nPortNo], pTask, RET_SYSERROR, "实时收数", "做标记失败!");

	return false;
}

//处理服务器状态
// 返回false 代表不需要进一步处理
// 返回true  代表需要进一步处理
bool CCollectionData::LportState(TSSmartDocEx *pDocEx, TSSmartTask *pTask, 
								    TSCmdBuffer *pBuffer,unsigned char *ucRawData)
{
	CString strText = "";
	int nTotalNo;
	bool bFlag1,bFlag2;

	bFlag1 = false;
	bFlag2 = false;

	nTotalNo = ucRawData[2];

	//服务器有数据
	if( ucRawData[1] != 0x0a ) 
		bFlag1 = true; 
	
	for(int i=0;i<nTotalNo; i++ ) 
	{
		switch(ucRawData[3+i])
		{
		case 0x0a://端口无数据
			break;
		case 0x0b://终端注册号不符合
			strText.Format("端口%d注册号不符合", i+1);
			printf("!!!!设备%s,端口号%d注册号不符\n",pDocEx->pChildDoc[0]->m_szDeviceID, i+1);
			bFlag2 = false;
			break;
		case 0x0c://终端设备无响应
			break;
		case 0x0d://申请签到
			{
			printf("-----设备%sPort=%d申请签到\n", pDocEx->pChildDoc[0]->m_szDeviceID, i+1);			
			strText.Format("端口%d申请签到!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));

			CSingInServer  SingIn;
			SingIn.SignInProcess(pDocEx, pBuffer, i+1, pTask);
			bFlag2 = true;
			}
			break;
		case 0x0e://黑名单有效期过期
  	      printf("!!!!黑名单有效期过期\n");
    		break;
		case 0xFF://未接终端
			break;
		default://其他状态不考虑
			strText.Format("端口%d状态未定义!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_SYSERROR, "实时收数", strText.GetBuffer(0));
			break;
		}
	}

	if(bFlag2 == true)
		return false;

	return bFlag1;
}

//处理支付交易类型终端设备数据
long CCollectionData::Process_DealTypeData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData, int nPortNo)
{
	CSmartSRCSFTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];
	printf("nPortNo = %d 交易流水=%d\n",nPortNo,nFlowNo);
	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("端口%d非法!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	int nType = 0x01 ;
	if( !strcmp(pDocEx->pChildDoc[nPortNo]->m_szMacCode, "0201") )
	{
		if( ucRawData[25] == 0x30 )
			nType = 0x07 ;
		else
			nType = 0x06 ;
	}

	char szStatus[64];
	long nTick = GetTickCount();

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "保存成功!");
	}
	else
	{
		printf("!!!!传递交易数据给金仕达失败,重复收集此数!!!!\n");
		strcpy(szStatus, "保存失败!没有做标记!重复收集此数!");
	}

	WriteLog("消费流水号%d, 开始收数时间点:%ld, 收数时间(毫秒):%d, 保存时间(毫秒):%d, 本笔总耗费时间(毫秒):%d. 状态:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);
		
	return RET_OK;
}

//处理身份认证类型终端设备数据
long CCollectionData::Process_IdentifyData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	CSmartSRCJSBTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString  strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("端口%d非法!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x02, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("!!!!传递交易数据给金仕达失败,重复收集此数!!!!\n");
	}

	return RET_OK;
}

//处理挂失类型终端设备原始凭证数据
//目前不出理该机型情况，最后所有业务完成后在处理该机型情况
long CCollectionData::Process_GSJData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData, int nPortNo)
{
	CSmartSRCGSJTable  SRCTable;
	CString  cs;

	unsigned char ucFlowNo[32];
	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];

	//CRC检测
	if( !CRCValid(ucRawData) )
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		ConfirmLost(nPortNo, ucRawData, 0xFF);
		return RET_DATACRC_ERROR;
	}

	//修改个人密码
	if( ucRawData[25] == 0xFD )
	{
		if( !ModifyPassword(pTask, pDocEx->pChildDoc[nPortNo], ucRawData) )
		{
			return RET_SYSERROR;
		}
		else
		{	
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_OK;
		}
	}
	//挂失申请 or 解挂申请
	else if( ucRawData[25] == 0xFC || ucRawData[25] == 0xFB )
	{
		//密码变为明文
		unsigned char AccountNum[17];
		int nType;

		if(ucRawData[25] == 0xFC)
			nType = 0x81;
		else
			nType = 0x82;

		char  szStuNo[22];
		memset(szStuNo, 0, sizeof(szStuNo));
		sprintf(szStuNo,"%.2X%.2X%.2X%.2X%.2X",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);
	
		memset(AccountNum,'0',17);
		
		unsigned char Password[17];
		memset(Password, 0, sizeof(Password));
		memcpy(Password,ucRawData+13,8);

		unsigned char c_key[32];
		memset(c_key,'9',16);

		unsigned char PlainPin[32];
		memset(PlainPin,0,32);
		
		//密码明文 PlainPin
		Smart_CardDes(AccountNum,c_key,PlainPin,Password,'d');

		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);

		TSGSJRecord  Data;
		memset(&Data, 0, sizeof(Data));

		int t = 0 ;
		for(int k=0; k<20; k++)
		{
			if( szStuNo[k] != 'F' )
				Data.szShowID[t++] = szStuNo[k];
		}

		sprintf(Data.szDeviceID, "%.2X.2X.2X.2X", ucRawData[0], ucRawData[1], ucRawData[2],ucRawData[3]);

		strcpy(Data.szDeviceID, pDocEx->pChildDoc[nPortNo]->m_szDeviceID);
		//strcpy(Data.szPassword, (char*)PlainPin);
		sprintf(Data.szPassword,"%.2X%.2X%.2X",ucRawData[13],ucRawData[14],ucRawData[15]);
		sprintf(Data.szCRC, "%.2X%.2X", ucRawData[26], ucRawData[27]);
		Data.nCardID = ucRawData[6]*256+ucRawData[7];
		sprintf(Data.szSerial,"%d", ucRawData[4]);
		
		printf("终端设备ID号:%.2X%.2X%.2X%.2X\n",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
		printf("通讯版本号:%.2X\n",ucRawData[4]);
		printf("数据启动原因:%.2X\n",ucRawData[5]);
		printf("交易流水号:%.2X%.2X\n",ucRawData[6],ucRawData[7]);
		printf("显示卡号:%.2X%.2X%.2X%.2X%.2X\n",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);
		printf("个人密码:%.2X%.2X%.2X\n",ucRawData[13],ucRawData[14],ucRawData[15]);
		printf("保留:%.2X%.2X%.2X\n",ucRawData[16],ucRawData[17],ucRawData[18]);
		printf("时间:%.2d%.2d%.2d%.2d%.2d%.2d\n",ucRawData[19],ucRawData[20],ucRawData[21],
			                                     ucRawData[22],ucRawData[23],ucRawData[24]);
		if(ucRawData[25] == 0xFC)
		{
			printf("------挂失申请: 学号:%s, 密码:%s. \n", Data.szShowID, Data.szPassword);
			

		}
		else
			printf("------解挂申请: 学号:%s, 密码:%s. \n", Data.szShowID, Data.szPassword);

		if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, (unsigned char*)&Data, sizeof(Data)) != RET_OK )
		{
			printf("金仕达返回不同意\n");
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			return RET_SYSERROR;
		}
		else
		{
			printf("金仕达返回同意\n");
			ConfirmLost(nPortNo, ucRawData, 0x00);
		}
	}
	else
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	//	ConfirmLost(nPortNo, ucRawData, 0xff);
	}

	return RET_OK;
}

//处理扎帐纪录
long CCollectionData::Process_StateData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	//CString strText;
	OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256);
	//printf("nPortNo = %d 扎帐流水=%d\n",nPortNo,ucRawData[6]*256+ucRawData[7]);
	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	
	for(int i=0; i<3; i++)
	{
		if( GetMachineType(m_pDocEx->pChildDoc[m_pDocEx->nPortNo]) == MACHINE_TYPE_5301)
			MakeBuf_ConfirmData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
		else
			MakeBuf_ConfirmStateData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
			
			/*printf("%.2X%.2X%.2X%.2X%.2X%.2X%.2X\n",pBuffer->pBuffer[0],
				pBuffer->pBuffer[1],
				pBuffer->pBuffer[2],
				pBuffer->pBuffer[3],
				pBuffer->pBuffer[4],
				pBuffer->pBuffer[5],
				pBuffer->pBuffer[6]);*/
			if( SendRequest(pDocEx->pChildDoc[nPortNo], pBuffer) == RET_OK )
			{
				//做标记成功，退出
				if( UnMakeDeviceBuffer(pBuffer) == RET_OK && 
					pBuffer->pBuffer[2]==0x00 ) 
				{
					return true;
				}
			}
			else
			{
				//printf("做扎帐记录失败\n");
				Sleep(100);
			}
	}
	return RET_OK;
	
	CSmartJZSRCTable  SRCTable;
	//unsigned char ucFlowNo[2];
	//int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("端口%d非法!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	char szStatus[64];
	long nTick = GetTickCount();
	//modified by lina 20050403
	//CRC检测
	OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256);
	if(nFlowNo == 0xFFFF)
		pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
	else
		pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;
		
	ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
	/*if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;
		
		ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
		//ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "保存成功!");

	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
		strcpy(szStatus, "保存失败!没有做标记!重复收集此数!");
	}*/

	WriteLog("扎帐流水号%d, 开始收数时间点:%ld, 收数时间(毫秒):%d, 保存时间(毫秒):%s, 本笔总耗费时间(毫秒):%d. 状态:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);

	return RET_OK;
}

//处理补助纪录
long CCollectionData::Process_AssisData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData, int nPortNo)
{
	CSmartSRCBZTable  SRCTable;
	unsigned char ucFlowNo[2];
//	unsigned char out[32];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[8]; 
	ucFlowNo[1] = ucRawData[9];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	char szStatus[64];
	long nTick = GetTickCount();

	if( OutputRealData(pTask, pDocEx->pChildDoc[0], 0x04, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "保存成功!");
	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
		strcpy(szStatus, "保存失败!没有做标记!重复收集此数!");
	}

	WriteLog("补助流水号%d, 开始收数时间点:%ld, 收数时间(毫秒):%d, 保存时间(毫秒):%s, 本笔总耗费时间(毫秒):%d. 状态:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);

	return RET_OK;
}

//新增加一条任务
long CCollectionData::InsertTask(TSSmartDoc *pDoc, long nTry, char *TaskCode)
{
	CSmartTask Task;
//	Task.SetMemo(nNumber);
	Task.SetTask("收历史数", "", 0, nTry);
	Task.AddAuthID(pDoc->m_nAuthID, TaskCode);

	if( !Task.Write() )
	{
		ReportLog(pDoc, m_pTask, RET_DBQUERYERROR, "实时收数", "新增收历史数任务失败!");
		return RET_DBQUERYERROR;
	}
	else
	{
		printf("\n收数时, 新增收历史数任务成功!..............\n\n");
		ReportLog(pDoc, m_pTask, RET_OK, "实时收数", "新增收历史数任务成功!");
		TerminateTask(2);
		return RET_OK;
	}
}

//MARK值错
bool CCollectionData::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	CString strText;

	switch(nMark)
	{
	case 0x0b: //授权号不对
		strText.Format("实时收集时返回mark=注册号不对! 数据为:%s. 正在更改注册号!", pBuffer->pBuffer, pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, RET_SYSERROR, "实时收数", strText.GetBuffer(0));
		return ModifyRegister(pDoc, pBuffer);
		break;
	case 0x05: //
		break;
	default:
		printf("1---实时收集LPORT数据时,返回的状态值不对!!!!\n");
		ResetDevice(pDoc, pBuffer);
		break;
	}
	return true;
}

void CCollectionData::OnCRCError()
{
	ReportLog(m_pDocEx, m_pTask, RET_SYSERROR, "实时收数", "实时收集时CRC错!");
	ClearPortData(m_pDocEx->pChildDoc[m_pDocEx->nPortNo], m_pBuffer, m_pDocEx->nPortNo);
}


bool CCollectionData::ConfirmLost(int nPortNo, unsigned char *ucRawData, unsigned char flag)
{
	unsigned char Buffer[32];

	Buffer[0] = ucRawData[6];
	Buffer[1] = ucRawData[7];
	Buffer[2] = flag;

	TSSmartDoc *pDoc = m_pDocEx->pChildDoc[nPortNo];

	for(int i=0; i<3; i++)
	{
		MakeBuf_ConfirmLost(&pDoc->DeviceInfo, m_pBuffer, Buffer);
		m_pBuffer->nTimeOut1 = 1500 ;
		m_pBuffer->nTimeOut2 = 200 ;
		if(SendRequest(pDoc, m_pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(m_pBuffer) == RET_OK && m_pBuffer->pBuffer[2]==0x00 )
			{
				return true;
			}
		}
		else
		{
			Sleep(100);
		}
	}

	return false;
}

//查找注册号对应的设备
bool CCollectionData::FindMachine(char *szDataReg, TSSmartDoc *pDoc)
{
	return true;
}

//新增一台设备
bool CCollectionData::AddNewMachine(int nPort, char *type, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, char *szDataReg, TSSmartDoc *pDoc)
{
	unsigned char szID[32];
	long nAuthID= 0;

	memset(szID, 0, sizeof(szID));

	bool bFound = false ;
	for( int p =0; p < 3; p++ )
	{
		MakeBuf_GetPortPar(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, nPort);
		if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
			{
				bFound = true;
				SVC_HEX_2_DSP(&pBuffer->pBuffer[4], szID, 4);
				break;
			}
		}
	}

	if( !bFound )
		return false;

	int nNo = pBuffer->pBuffer[8];
	strcpy(pDoc->m_szRegister, szDataReg);



	GetSmartDocInfo(szDataReg, pDoc);
	pDoc->m_nLevel = 1;
	pDoc->m_szLevelArray[0] = (char)pDocEx->pChildDoc[0]->m_nMachineNo;
	pDoc->m_szLevelArray[1] = nPort;

	AddNewSmartDoc(pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDoc);

	return true;
}

bool CCollectionData::GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc)
{
	

	return true;
}

//挂失/解挂时黑名单处理
bool CCollectionData::PostBlackCard(int nflag, long nDatabase, long nCardID)
{
	return true;
}

//上传一条扎帐记录
bool CCollectionData::ReadJZRecord(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	bool bResult = false ;

	MakeBuf_CollectStateData(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer);

	for(int i=0; i< 3; i++)
	{
		if(SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && pBuffer->pBuffer[2]==0x00 )
			{
				bResult = true ;
				break;
			}
		}
	}

	return bResult;
}
