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
	MakeBuf_CollectData(pDocEx->pDeviceInfo, pBuffer);

	pDocEx->pChildDoc[0]->m_dwTryCount = GetTickCount();

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
#ifdef __DEBUG_OUTPUT__
/*			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");*/
#endif
			unsigned char ucRawData[256];
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
	printf("bbbbb\n");

	unsigned char ucRawData[256];
	int nTotalPortNo=24, nPortNo=0;
	
	memset(ucRawData, 0, sizeof(ucRawData));

	memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
#ifdef __DEBUG_OUTPUT__
/*	for(int i=0; i< 256; i++)
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");*/
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
			ReportLog(pDocEx, pTask, RET_SYSERROR, "实时收数", "收集LPort数据时, 由于返回的端口总数不相等, 复位时出错!");
		}

		return RET_SYSERROR;
	}

	if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		return RET_NG;
	}

	nTotalPortNo = ucRawData[2];
	nPortNo = ucRawData[3+nTotalPortNo];

	//端口数不对, 复位
	if( nPortNo > nTotalPortNo )
	{
		ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer);
		return RET_SYSERROR;
	}

	nPortNo = GetPos(pDocEx, nPortNo);

	pBuffer->nCmdSize = nTempLen;
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(pBuffer->pBuffer, sTempData, 256);

	long nRet = RET_NG ;
	switch(GetMacDataType(pBuffer)) //GetMacDataType(pBuffer))
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
					nPortNo = 0 ;
					/*
					TSSmartDoc doc;

					//档案表中有数据
					if( FindMachine(szDataReg, &doc) )
						nType = GetMachineType(&doc);
						*/
				}
			}
		}

		switch(GetMachineType(pDocEx->pChildDoc[nPortNo])) 
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
		nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	case MACDATA_TYPE_BZ://为补助数据
		nPortNo = 0;
		nRet = Process_AssisData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	default:
		break;
	}

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
				Sleep(1000);
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
						return true;
					}
				}
			}
			else
			{
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
#if 0
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));
			ModifyRegisterEx(pDocEx, pBuffer, i+1);		
#endif
			bFlag2 = false;
			break;
		case 0x0c://终端设备无响应
			break;
		case 0x0d://申请签到
			printf("Port=%d, 申请签到!\n", i+1);
#if 0
			printf("AuthID=%d, Port=%d, The SingIn Server!\n", pDocEx->pChildDoc[0]->m_nAuthID, i+1);			strText.Format("端口%d申请签到!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "实时收数", strText.GetBuffer(0));

			CSingInServer  SingIn;
			SingIn.SignInProcess(pDocEx, pBuffer, i+1, pTask);*/
			bFlag2 = true;
#endif
			break;
		case 0x0e://黑名单有效期过期
			printf("黑名单有效期过期...........\n");
#if 0
			CCheckBlackVersion  Check;
			int nTemp = pDocEx->nPortNo ;
			pDocEx->nPortNo = GetPos(pDocEx, i+1);
			if( Check.ProcessCheck(pDocEx, pTask, pBuffer) != RET_OK )
			{
				pDocEx->nPortNo  = nTemp ;
				if(bFlag2 == false)
					bFlag2 = true;
			}
			else
				pDocEx->nPortNo  = nTemp ;
#endif
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
//	CSmartSRCSFTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
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

	int nType = 0x01 ;
	if( !strcmp(pDocEx->pChildDoc[nPortNo]->m_szMacCode, "0201") )
	{
		static bool bFound = true;
		if( bFound )
			nType = 0x07 ;
		else
			nType = 0x06 ;

		bFound = !bFound;
	/*	if( ucRawData[25] == 0x30 )
			nType = 0x07 ;
		else
			nType = 0x06 ;*/
	}

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		//strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
	}
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

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x02, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

	//	strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
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

//	printf("The 挂失类型终端设备原始凭证数据: Port:%d......\n", nPortNo);

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

		memset(AccountNum,'0',17);
		sprintf((char *)AccountNum,"%.2X%.2X%.2X%.2X%.2X",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);

		unsigned char Password[17];
		memset(Password, 0, sizeof(Password));
		memcpy(Password,ucRawData+13,3);//add by lina 20050308
		/*memcpy(Password,ucRawData+13,8);
		
		unsigned char c_key[32];
		memset(c_key,'9',16);
		*/
		unsigned char PlainPin[32];
		memset(PlainPin,0,32);
		
		//密码明文 PlainPin
		//Smart_CardDes(AccountNum,c_key,PlainPin,Password,'d');
        */ //DELETE BY LINA 20050308
		TSGSJRecord  Data;
		
		SVC_HEX_2_DSP(Password,PlainPin,3);//add by lina 20040305	
		
		memset(&Data, 0, sizeof(Data));
		Data.nCardID = 0;
		strcpy(Data.szDeviceID, pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID);
		strcpy(Data.szPassword, (char*)PlainPin);
		strcpy(Data.szSerial, "");
		strcpy(Data.szShowID, (char*)AccountNum);
		WriteLog("向金仕达申请TSGJRecord信息为 szDeviceID=%s nCardID=%d szShowID=%s nFlag=%d szPassword=%s szSerial=%s szCRC=%s",
			Data.szDeviceID,Data.nCardID,Data.szShowID,Data.nFlag,Data.szPassword,Data.szSerial,Data.szCRC);
		if( ReadCardGSInfo(nType, &Data) != RET_OK )
		{
			printf("输入显示卡号:%s  输入密码:%s  数据库密码不相同!!\n", AccountNum, PlainPin);
			WriteLog("输入显示卡号:%s  输入密码:%s  数据库密码不相同!!\n", AccountNum, PlainPin);
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			
			return false ;
		}

		printf("输入显示卡号:%s  输入密码:%s  数据库密码:%s\n", AccountNum, PlainPin, Data.szPassword);
		WriteLog("输入显示卡号:%s  输入密码:%s  数据库密码:%s\n", AccountNum, PlainPin, Data.szPassword);

		
		memset(&Data, 0, sizeof(Data));

		strcpy(Data.szDeviceID, pDocEx->pChildDoc[nPortNo]->m_szDeviceID);
		strcpy(Data.szPassword, (char*)PlainPin);
		strcpy(Data.szShowID, (char*)AccountNum);
		sprintf(Data.szCRC, "%.2X%.2X", ucRawData[26],ucRawData[27]);

		if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, (unsigned char*)&Data, sizeof(Data)) != RET_OK )
		{
			WriteLog("密码比对正确,但金仕达不允许做挂失解挂动作");
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_SYSERROR;
		}
		else
		{
			WriteLog("密码比对正确,金仕达允许做挂失解挂动作");
			ConfirmLost(nPortNo, ucRawData, 0x00);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_OK;
		}
	}
	else
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	//	ConfirmLost(nPortNo, ucRawData, 0xff);
		printf("未知的数据类型!\n");
	}

	return RET_OK;
}

//处理扎帐纪录
long CCollectionData::Process_StateData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	CSmartJZSRCTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
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

	//CRC检测
	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
		//ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
	}

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

	if( OutputRealData(pTask, pDocEx->pChildDoc[0], 0x04, ucRawData, 256) == RET_OK )
	{
		//数据确认流程,不成功重试3次
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

	//	strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("保存失败, 没有做标记, 重复收集此数!!!!\n");
	}

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
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase > 0 )
	{
		CString strSQL;

		strSQL.Format("select * from smart_machine where smt_regno='%s' order by smt_status", 
			szDataReg);

		long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
		if( nRec > 0 )
		{
			if( MoveFirst(nRec) == RET_OK )
			{
				ZeroMemory(pDoc, sizeof(TSSmartDoc));

				GetFieldLongValueEx(nRec, "smt_authno", &pDoc->m_nAuthID);
				GetFieldStringValueEx(nRec, "smt_machineid", pDoc->m_szDeviceID);
				GetFieldStringValueEx(nRec, "smt_regno", pDoc->m_szRegister);
				GetFieldStringValueEx(nRec, "smt_machinecode", pDoc->m_szMacCode);

				CloseRecHandle(nRec);
				FreeDBHandle(nDatabase);

				return true;
			}
			CloseRecHandle(nRec);
		}
		FreeDBHandle(nDatabase);
	}
	return false;
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

	CString strSQL;
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
	{
		return false;
	}

	strSQL = "select SMART_MACHINE_SEQUENCE.nextval as seq from dual";
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	GetFieldLongValueEx(nRec, "seq", &nAuthID);
	CloseRecHandle(nRec);

	strSQL.Format("INSERT INTO SMART_MACHINE("
		"SMT_AUTHNO, SMT_MACHINEID, SMT_MACHINENO, "
		"SMT_PARENT_ID, SMT_PORTNO, SMT_COMADDR,"
		"SMT_IPADDR, SMT_MACHINECODE, SMT_STATUS, "
		"SMT_CHANGEDATE, SMT_COMMODE,smt_regno) VALUES(%d, '%s', %d, "
		"%d, %d, "
		"'%s', '%s', '%s', 0, "
		"SYSDATE, 3,'%s')", 
		nAuthID, szID, nNo, 
		pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDocEx->pChildDoc[0]->m_szPort,
		pDocEx->pChildDoc[0]->m_szAddr, type, szDataReg);
	if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
	{
		printf("%s\n", strSQL.GetBuffer(0));
		FreeDBHandle(nDatabase);
		return false;
	}

	strSQL.Format("INSERT INTO SMART_COMMREC(SMT_AUTHNO , SMT_LASTINVOICENO, SMT_DAILYCODE, SMT_DAILYNO) VALUES(%d, 0, 'M', 0)", nAuthID);
	if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	FreeDBHandle(nDatabase);

	GetSmartDocInfo(szDataReg, pDoc);
	pDoc->m_nLevel = 1;
	pDoc->m_szLevelArray[0] = (char)pDocEx->pChildDoc[0]->m_nMachineNo;
	pDoc->m_szLevelArray[1] = nPort;

	AddNewSmartDoc(pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDoc);

	return true;
}

bool CCollectionData::GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc)
{
	char sSQL[1600];
	char sWhere[256];

	//得到数据库句柄
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
		return false;

	memset(sSQL, 0, sizeof(sSQL));
	sprintf(sWhere, " A.SMT_REGNO = '%s' ", pszRegNo);

	//打开终端记录表
	strcpy(sSQL, "SELECT A.SMT_AUTHNO , A.SMT_MACHINEID, A.SMT_MACHINENO, A.SMT_ORG_ID, A.SMT_LOCATIONCODE, ");
	strcat(sSQL, "   A.SMT_PARENT_ID, A.SMT_PORTNO, A.SMT_COMADDR, A.SMT_IPADDR, A.SMT_IPADDRDES, ");
	strcat(sSQL, "   A.SMT_BAUDRATE, A.SMT_MACHINEVER, A.SMT_PROGRAMVER, A.SMT_MACHINECODE, A.SMT_STATUS, ");
	strcat(sSQL, "   A.SMT_CHANGEDATE, A.SMT_COMMODE, A.SMT_COLLECTWAY, A.SMT_ONNET, A.SMT_ONLINE,");
	strcat(sSQL, "   A.SMT_Level, A.smt_levelarray, A.SMT_STATIONIP, A.SMT_DAILYCODE, A.SMT_DAILYNO, A.SMT_REGNO, A.SMT_SYSPWD,");
	strcat(sSQL, "   A.SMT_USECARD, A.SMT_CLASS, A.SMT_PORTCOUNT, ");
	strcat(sSQL, "   B.SMT_LASTINVOICENO, to_char(B.SMT_LASTDEALDATETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_LASTDEALDATETIME ,");
	strcat(sSQL, "   B.SMT_BEGININVOICE, B.SMT_SETTLEINVOICE, to_char(B.SMT_SETTLETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_SETTLETIME , ");
	strcat(sSQL, "   B.SMT_ENDINVOICE, B.SMT_BLACKEXPIRE, to_char(B.SMT_DOWNBLACKTIME, 'yyyymmdd hh24:mm:ss') as SMT_DOWNBLACKTIME , ");
	strcat(sSQL, "   B.SMT_STARTUSE, B.SMT_LOSTDEAL, B.SMT_LOSTSETTLEMENT, B.SMT_BLACKLISTVER, B.SMT_CLOCKVER, ");
	strcat(sSQL, "   B.SMT_NUMBERVER, to_char(B.SMT_COMMDATETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_COMMDATETIME ");
	strcat(sSQL, "FROM ");
	strcat(sSQL, "   SMART_MACHINE A, Smart_CommRec B ");
	strcat(sSQL, "WHERE ");
	strcat(sSQL, "   A.SMT_AUTHNO = B.SMT_AUTHNO(+) AND ") ;
	strcat(sSQL, sWhere);

	long nRec = ExecuteQuery(nDatabase, sSQL);
	if( nRec <= 0 )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	long nResult = MoveFirst(nRec) ;
	if( nResult != RET_OK )
	{
		CloseRecHandle(nRec);
		FreeDBHandle(nDatabase);
		return false;
	}

	while( IsEOF(nRec) == RET_NG )
	{
		GetFieldStringValueEx(nRec, "SMT_MACHINECODE", pDoc->m_szMacCode);	//终端机型号代码
		GetFieldStringValueEx(nRec, "SMT_CLASS", pDoc->m_szMacCard);		//可用IC卡卡型

		GetFieldLongValueEx(nRec, "SMT_AUTHNO", &pDoc->m_nAuthID);			//授权号
		GetFieldStringValueEx(nRec, "SMT_MACHINEID", pDoc->m_szDeviceID);	//设备ID
		GetFieldStringValueEx(nRec, "SMT_REGNO", pDoc->m_szRegister);		//注册号
		GetFieldLongValueEx(nRec, "SMT_MACHINENO", &pDoc->m_nMachineNo);	//机号
		GetFieldStringValueEx(nRec, "SMT_MACHINEVER", pDoc->m_szVersion);	//设备版本号
		GetFieldStringValueEx(nRec, "SMT_PROGRAMVER", pDoc->m_szProgramver);//分控器版本号
		GetFieldStringValueEx(nRec, "SMT_SYSPWD", pDoc->m_szPassword);		//系统员密码
		GetFieldStringValueEx(nRec, "SMT_OPRPWD", pDoc->m_szOprPasswd);		//管理员密码
		GetFieldLongValueEx(nRec, "SMT_PWDSwitch", (long*)&pDoc->m_nPwdswitch);	//密码开关

		GetFieldLongValueEx(nRec, "SMT_PARENT_ID", &pDoc->m_nParentID);		//终端机型号代码

		GetFieldLongValueEx(nRec, "SMT_PORTCOUNT", (long*)&pDoc->m_nPortCount);		//服务器端口总数
		GetFieldLongValueEx(nRec, "SMT_PORTNO", (long*)&pDoc->m_nSMTPort);		//服务器端口号

		GetFieldStringValueEx(nRec, "SMT_COMADDR", pDoc->m_szPort);			//通讯端口
		GetFieldLongValueEx(nRec, "SMT_BAUDRATE", &pDoc->m_nBaudRate);		//波特率
		GetFieldLongValueEx(nRec, "SMT_COLLECTWAY", &pDoc->m_nConnType);	//通讯方式
		GetFieldLongValueEx(nRec, "SMT_COMMODE", &pDoc->m_nCommMode);		//链路模式
		GetFieldStringValueEx(nRec, "SMT_IPADDR", pDoc->m_szAddr);			//通讯地址
		GetFieldLongValueEx(nRec, "SMT_ONNET", &pDoc->m_nOnNet);			//是否在网
		GetFieldLongValueEx(nRec, "SMT_ONLINE", &pDoc->m_nOnline);			//是否联机交易
 		GetFieldLongValueEx(nRec, "SMT_Level", (long*)&pDoc->m_nLevel);			//设备级数
		GetFieldStringValueEx(nRec, "SMT_LevelArray", pDoc->m_szLevelArray);//级联参数
		GetFieldLongValueEx(nRec, "SMT_STATUS", (long*)&pDoc->m_nStatus);	//设备状态
		
		GetFieldLongValueEx(nRec, "SMT_LASTINVOICENO", (long*)&pDoc->m_wFlowNo);	//期望流水号
		GetFieldLongValueEx(nRec, "SMT_LASTINVOICENO", (long*)&pDoc->m_wLastInvoiceNo);	//终端交易流水号期末值
 		GetFieldStringValueEx(nRec, "SMT_LASTDEALDATETIME", pDoc->m_sLastDealTime);	//终端交易时间期末值

		GetFieldLongValueEx(nRec, "SMT_BEGININVOICE", (long*)&pDoc->m_nBeginInvoice);	//扎帐的开始流水
		GetFieldLongValueEx(nRec, "SMT_SETTLEINVOICE", (long*)&pDoc->m_wSettleinvoice);	//扎帐流水号期末值
		GetFieldStringValueEx(nRec, "SMT_DOWNBLACKTIME", pDoc->m_sSettleTime);			//扎帐时间期末值
		GetFieldLongValueEx(nRec, "SMT_ENDINVOICE", (long*)&pDoc->m_wEndInvoice);	//扎帐的结束流水号
		
		GetFieldStringValueEx(nRec, "SMT_BLACKEXPIRE", pDoc->m_sBlackExpire);	//黑名单的有效期
		GetFieldStringValueEx(nRec, "SMT_DOWNBLACKTIME", pDoc->m_sDownBlackTime);	//黑名单下传时间期末值
		GetFieldLongValueEx(nRec, "SMT_STARTUSE", (long*)&pDoc->m_nStartuse);	//签到结果
		GetFieldLongValueEx(nRec, "SMT_LOSTDEAL", (long*)&pDoc->m_nLostDeal);	//交易数据丢失笔数
		GetFieldLongValueEx(nRec, "SMT_LOSTSETTLEMENT", (long*)&pDoc->m_nLostSettle);//扎帐数据丢失的笔数

		GetFieldStringValueEx(nRec, "SMT_BLACKLISTVER", pDoc->m_sBlackListVer);	//黑名单版本号
		GetFieldStringValueEx(nRec, "SMT_CLOCKVER", pDoc->m_sClockVer);	//时间单版本号
		GetFieldStringValueEx(nRec, "SMT_NUMBERVER", pDoc->m_sNumberVer);	//编号式收费机消费编号版本
		GetFieldStringValueEx(nRec, "SMT_COMMDATETIME", pDoc->m_sCommDateTime);	//最后一次收集数据的日期时间

		break;
	}

	CloseRecHandle(nRec);
	FreeDBHandle(nDatabase);

	return true;
}

//挂失/解挂时黑名单处理
bool CCollectionData::PostBlackCard(int nflag, long nDatabase, long nCardID)
{
	CSmartTask Task;
	char szText[32];
	char szBeginTime[24];

	GetCurDateTime(szBeginTime);

	if(!nflag) 
	{
		sprintf(szText,"%d", nCardID);
		Task.SetTask("挂失黑名单广播", szBeginTime, 0, 1);
	}
	else
	{
		sprintf(szText,"-%d", nCardID);
		Task.SetTask("解挂黑名单广播", szBeginTime, 0, 1);
	}

//	Task.SetMemo(szText);

	CString strSQL;
	strSQL = "SELECT SMT_AUTHNO FROM SMART_MACHINE WHERE SMT_STATUS IN(0,1) AND SMT_MACHINECODE <> '5301' ORDER BY SMT_AUTHNO ";
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 ) 
		return false;

	long nAuthno=0;
	while( IsEOF(nRec) == RET_NG )
	{
		if( GetFieldLongValueEx(nRec, "SMT_AUTHNO", &nAuthno) == RET_OK )
		{
			Task.AddAuthID(nAuthno, "70");
		}
		MoveNext(nRec);
	}
	CloseRecHandle(nRec);

	return Task.Write();
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
