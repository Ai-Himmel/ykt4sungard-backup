#include "stdafx.h"
#include "SmartTerminal.h"

int nAllocateMemoryFlag = 0;

/*********************初始化业务对接参数*********************/
/* 作者：   李呐
*  日期：   2004年1月6日
*  用途：   读取终端设备参数表中的基本信息参数，传递给通信层
**************************************************************/
int _stdcall Ini_SmartDocPar(DWORD *dwTotalNo,TSSmartDoc **p)
{
	if(nAllocateMemoryFlag != 0) //是否已经分配过
		return RET_ERROR;
	*dwTotalNo = 2;
	if(*dwTotalNo <= 0)   //没有终端设备信息
		return RET_ERROR;
	//分配内存
	*p = new TSSmartDoc[*dwTotalNo];
	if(*p == NULL)
		return RET_ERROR;
	//基本信息
	nAllocateMemoryFlag = 1;
	(*p)[0].m_dwLength  = sizeof(TSSmartDoc);
	(*p)[0].m_bNetPar   = true;              //星型结构
	(*p)[0].m_ucTotalNo = 2;                 //该结构下有两台机（包括服务器)
	(*p)[0].m_ucNo      = 0;				  //当前通讯端口为服务器	
	(*p)[0].m_wNoReponseTime =0;			  //无响应次数为0
	//通信参数
	(*p)[0].m_CommunicationInfo.dwLength = sizeof(CommunicationProperty);
	(*p)[0].m_CommunicationInfo.ucMode   = TCPIP; 
	(*p)[0].m_CommunicationInfo.bStyle   = false;//被动方式
	(*p)[0].m_CommunicationInfo.bNetFlag = true;//联网
	(*p)[0].m_CommunicationInfo.bServerOrClient = true;//服务器
	sprintf((*p)[0].m_CommunicationInfo.cServerIpAddr,"%s","192.168.0.34");
	(*p)[0].m_CommunicationInfo.wServerPortNo = 10001;
	//任务参数
	(*p)[0].m_TaskInfo.dwLength = sizeof(TaskProperty);
	(*p)[0].m_TaskInfo.wIDNo    = 0; //纪录收集
	(*p)[0].m_TaskInfo.ucMode   = 0; //默认任务
	(*p)[0].m_TaskInfo.ucCommandTotalNo = 1;
	(*p)[0].m_TaskInfo.ucCommandCurrentNo = 0;
	(*p)[0].m_TaskInfo.ucCommandArray[0]  = 0x03;
	//终端参数
	//0---服务器
	(*p)[0].m_TerminalInfo[0].dwLength  = sizeof(TerminalProperty);
	(*p)[0].m_TerminalInfo[0].dwMainKey = 0;
	(*p)[0].m_TerminalInfo[0].ucState   = 1; //生产态
	(*p)[0].m_TerminalInfo[0].ucIDNo[0] = 0x00;//ID号
	(*p)[0].m_TerminalInfo[0].ucIDNo[1] = 0x00;
	(*p)[0].m_TerminalInfo[0].ucIDNo[2] = 0x45;
	(*p)[0].m_TerminalInfo[0].ucIDNo[3] = 0x9B;
	(*p)[0].m_TerminalInfo[0].ucMacNo   = 1;//机号
	(*p)[0].m_TerminalInfo[0].ucRegNo[0]= 0x00;//注册号
	(*p)[0].m_TerminalInfo[0].ucRegNo[1]= 0x00;
	(*p)[0].m_TerminalInfo[0].ucRegNo[2]= 0x45;
	(*p)[0].m_TerminalInfo[0].ucRegNo[3]= 0x9B;
	(*p)[0].m_TerminalInfo[0].ucType[0] = 53;//机类型
	(*p)[0].m_TerminalInfo[0].ucType[1] = 1;
	(*p)[0].m_TerminalInfo[0].ucProgVer[0]= 04;//程序版本
	(*p)[0].m_TerminalInfo[0].ucProgVer[1]= 01;
	(*p)[0].m_TerminalInfo[0].ucProgVer[2]= 02;
	(*p)[0].m_TerminalInfo[0].ucProgVer[3]= 10;
	(*p)[0].m_TerminalInfo[0].wEDFlowNo   = 0;//期望交易流水号
	(*p)[0].m_TerminalInfo[0].wECFlowNo   = 0;//期望扎帐流水号
	//1端口---收费机
	(*p)[0].m_TerminalInfo[1].dwLength  = sizeof(TerminalProperty);
	(*p)[0].m_TerminalInfo[1].dwMainKey = 1;
	(*p)[0].m_TerminalInfo[1].ucState   = 1; //生产态
	(*p)[0].m_TerminalInfo[1].ucIDNo[0] = 0x00;//ID号
	(*p)[0].m_TerminalInfo[1].ucIDNo[1] = 0x00;
	(*p)[0].m_TerminalInfo[1].ucIDNo[2] = 0x33;
	(*p)[0].m_TerminalInfo[1].ucIDNo[3] = 0x06;
	(*p)[0].m_TerminalInfo[1].ucMacNo   = 1;//机号
	(*p)[0].m_TerminalInfo[1].ucRegNo[0]= 0x00;//注册号
	(*p)[0].m_TerminalInfo[1].ucRegNo[1]= 0x00;
	(*p)[0].m_TerminalInfo[1].ucRegNo[2]= 0x33;
	(*p)[0].m_TerminalInfo[1].ucRegNo[3]= 0x06;
	(*p)[0].m_TerminalInfo[1].ucType[0] = 02;//机类型
	(*p)[0].m_TerminalInfo[1].ucType[1] = 26;
	(*p)[0].m_TerminalInfo[1].ucProgVer[0]= 03;//程序版本
	(*p)[0].m_TerminalInfo[1].ucProgVer[1]= 12;
	(*p)[0].m_TerminalInfo[1].ucProgVer[2]= 28;
	(*p)[0].m_TerminalInfo[1].ucProgVer[3]= 10;
	(*p)[0].m_TerminalInfo[1].wEDFlowNo   = 11;//期望交易流水号
	(*p)[0].m_TerminalInfo[1].wECFlowNo   = 0;//期望扎帐流水号

	//基本信息
	(*p)[1].m_dwLength  = sizeof(TSSmartDoc);
	(*p)[1].m_bNetPar   = true;              //星型结构
	(*p)[1].m_ucTotalNo = 2;                 //该结构下有两台机（包括服务器)
	(*p)[1].m_ucNo      = 0;				  //当前通讯端口为服务器	
	(*p)[1].m_wNoReponseTime =0;			  //无响应次数为0
	//通信参数
	(*p)[1].m_CommunicationInfo.dwLength = sizeof(CommunicationProperty);
	(*p)[1].m_CommunicationInfo.ucMode   = TCPIP; 
	(*p)[1].m_CommunicationInfo.bStyle   = false;//被动方式
	(*p)[1].m_CommunicationInfo.bNetFlag = true;//联网
	(*p)[1].m_CommunicationInfo.bServerOrClient = true;//服务器
	sprintf((*p)[1].m_CommunicationInfo.cServerIpAddr,"%s","192.168.0.35");
	(*p)[1].m_CommunicationInfo.wServerPortNo = 10001;
	//任务参数
	(*p)[1].m_TaskInfo.dwLength = sizeof(TaskProperty);
	(*p)[1].m_TaskInfo.wIDNo    = 0; //纪录收集
	(*p)[1].m_TaskInfo.ucMode   = 0; //默认任务
	(*p)[1].m_TaskInfo.ucCommandTotalNo = 1;
	(*p)[1].m_TaskInfo.ucCommandCurrentNo = 0;
	(*p)[1].m_TaskInfo.ucCommandArray[0]  = 0x03;
	//终端参数
	//0---服务器
	(*p)[1].m_TerminalInfo[0].dwLength  = sizeof(TerminalProperty);
	(*p)[1].m_TerminalInfo[0].dwMainKey = 0;
	(*p)[1].m_TerminalInfo[0].ucState   = 1; //生产态
	(*p)[1].m_TerminalInfo[0].ucIDNo[0] = 0x00;//ID号
	(*p)[1].m_TerminalInfo[0].ucIDNo[1] = 0x00;
	(*p)[1].m_TerminalInfo[0].ucIDNo[2] = 0x46;
	(*p)[1].m_TerminalInfo[0].ucIDNo[3] = 0xBA;
	(*p)[1].m_TerminalInfo[0].ucMacNo   = 1;//机号
	(*p)[1].m_TerminalInfo[0].ucRegNo[0]= 0x00;//注册号
	(*p)[1].m_TerminalInfo[0].ucRegNo[1]= 0x00;
	(*p)[1].m_TerminalInfo[0].ucRegNo[2]= 0x46;
	(*p)[1].m_TerminalInfo[0].ucRegNo[3]= 0xBA;
	(*p)[1].m_TerminalInfo[0].ucType[0] = 53;//机类型
	(*p)[1].m_TerminalInfo[0].ucType[1] = 1;
	(*p)[1].m_TerminalInfo[0].ucProgVer[0]= 04;//程序版本
	(*p)[1].m_TerminalInfo[0].ucProgVer[1]= 01;
	(*p)[1].m_TerminalInfo[0].ucProgVer[2]= 02;
	(*p)[1].m_TerminalInfo[0].ucProgVer[3]= 10;
	(*p)[1].m_TerminalInfo[0].wEDFlowNo   = 0;//期望交易流水号
	(*p)[1].m_TerminalInfo[0].wECFlowNo   = 0;//期望扎帐流水号
	//1端口---收费机
	(*p)[1].m_TerminalInfo[1].dwLength  = sizeof(TerminalProperty);
	(*p)[1].m_TerminalInfo[1].dwMainKey = 1;
	(*p)[1].m_TerminalInfo[1].ucState   = 1; //生产态
	(*p)[1].m_TerminalInfo[1].ucIDNo[0] = 0x00;//ID号
	(*p)[1].m_TerminalInfo[1].ucIDNo[1] = 0x00;
	(*p)[1].m_TerminalInfo[1].ucIDNo[2] = 0x48;
	(*p)[1].m_TerminalInfo[1].ucIDNo[3] = 0x18;
	(*p)[1].m_TerminalInfo[1].ucMacNo   = 1;//机号
	(*p)[1].m_TerminalInfo[1].ucRegNo[0]= 0x00;//注册号
	(*p)[1].m_TerminalInfo[1].ucRegNo[1]= 0x00;
	(*p)[1].m_TerminalInfo[1].ucRegNo[2]= 0x48;
	(*p)[1].m_TerminalInfo[1].ucRegNo[3]= 0x18;
	(*p)[1].m_TerminalInfo[1].ucType[0] = 02;//机类型
	(*p)[1].m_TerminalInfo[1].ucType[1] = 26;
	(*p)[1].m_TerminalInfo[1].ucProgVer[0]= 03;//程序版本
	(*p)[1].m_TerminalInfo[1].ucProgVer[1]= 12;
	(*p)[1].m_TerminalInfo[1].ucProgVer[2]= 28;
	(*p)[1].m_TerminalInfo[1].ucProgVer[3]= 10;
	(*p)[1].m_TerminalInfo[1].wEDFlowNo   = 0;//期望交易流水号
	(*p)[1].m_TerminalInfo[1].wECFlowNo   = 0;//期望扎帐流水号

	for(int i=3;i<25;i++)
	{
		(*p)[0].m_TerminalInfo[i].dwLength = sizeof(TerminalProperty);
		(*p)[0].m_TerminalInfo[i].dwMainKey = 0;
		(*p)[0].m_TerminalInfo[i].ucState = 0;
	}

	/*
	for(int i=2;i<25;i++)
	{
		p[0].m_TerminalInfo[i].dwLength   = sizeof(TerminalProperty);
		p[0].m_TerminalInfo[i].dwMainKey  = 0;
		p[0].m_TerminalInfo[i].ucRunFlag    = 3;
	}*/
		
	return RET_OK;
}

int _stdcall ReleaseSmartDocPar(TSSmartDoc **p)
{
	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;
	delete [](*p);
	nAllocateMemoryFlag = 0;
	*p = NULL;
	return RET_OK;
}


int _stdcall BuildTaskBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuf,unsigned char *Data,int nLen)
{
	unsigned char  ucCommand,level_Array[256],Buffer[256];
	int  level,len,retLen,addr,no;

	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;
	
	no = pDoc->m_TaskInfo.ucCommandCurrentNo;

	ucCommand = pDoc->m_TaskInfo.ucCommandArray[no];
	
	//对于星型网络结构
	if(pDoc->m_bNetPar == true)
	{
		if(pDoc->m_ucNo != 0) //当前运行端口不为0
		{
			level = 1;
			level_Array[0] = pDoc->m_TerminalInfo[0].ucMacNo;    //服务器机号
			level_Array[1] = pDoc->m_ucNo;
			if( pDoc->m_CommunicationInfo.ucMode == TCPIP || //TCPIP
				pDoc->m_CommunicationInfo.ucMode == SERIAL   //串口
			  )    
			{
				pBuf->wWaitTime1  = (WORD)(500*1.5);
				pBuf->wWaitTime2  = (WORD)(1000*1.5);
			}
			else 
			{
				pBuf->wWaitTime1 = (WORD)(500*2.5);
				pBuf->wWaitTime2 = (WORD)(1000*2.5);
			}
		}
		else //直接对服务器操作
		{
			level = 0;
			if( pDoc->m_CommunicationInfo.ucMode == TCPIP || //TCPIP
				pDoc->m_CommunicationInfo.ucMode == SERIAL   //串口
			  )    
			{
				pBuf->wWaitTime1 = (WORD)(200*1.0);
				pBuf->wWaitTime2 = (WORD)(1000*1.0);
			}
			else 
			{
				pBuf->wWaitTime1 = (WORD)(200*2.0);
				pBuf->wWaitTime2 = (WORD)(1000*2.0);
			}	
		}
	}
	
	no = pDoc->m_ucNo;
//	char ucTemp[256];
	//sprintf(ucTemp,"ucCommand = %.2X",ucCommand);
	//AfxMessageBox(ucTemp);
	switch(ucCommand)
	{
	case 0x03://数据收集
		len = 4;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		break;
	case 0x04://数据做标记
		len = 9;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		Buffer[4] = 0x20;
		Buffer[5] = 0xd0;
		Buffer[6] = 0x10;
		memcpy(Buffer+7,Data,nLen);
		break;
	case 0xBB://收集历史数据 --- 交易
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	case 0xDE://收集历史数据 --- 补助
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	case 0x8A://收集历史数据 --- 扎帐
		len = 6;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[no].ucRegNo,4);
		memcpy(Buffer+4,Data,nLen);
		break;
	default:
		len = 4;
		ucCommand = 0x03;
		addr = pDoc->m_TerminalInfo[no].ucMacNo;
		memcpy(Buffer,pDoc->m_TerminalInfo[pDoc->m_ucNo].ucRegNo,4);
		break;
	}
	retLen         = PubCommands(addr,ucCommand,len,Buffer,level,level_Array);
	pBuf->ucMode   = 0;   //数据发送
	pBuf->wLength  = retLen;
	memcpy(pBuf->ucBuffer,Buffer,retLen);
	return RET_OK;
}



//数据解包工作
int _stdcall UpPacketBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer)
{
	WORD wTaskID;
	if(nAllocateMemoryFlag != 1)
		return RET_ERROR;

	wTaskID = pDoc->m_TaskInfo.wIDNo;
	if(wTaskID == 0) //数据收集与数据确认
	{
		switch(pDoc->m_TaskInfo.ucCommandArray[0]) //数据收集
		{
		case 0x03://数据收集
			CollectRawDataProcess(pDoc,pBuffer); //原始数据收集
			break;
		case 0x04://数据确认
			ConfirmRawDataProcess(pDoc,pBuffer);
			//Sleep(500);
			break;
		default:
			CollectRawDataProcess(pDoc,pBuffer);
			break;
		}
	}
	if(wTaskID == 1) //收集历史数据交易
		CollectHistoryDealData_Process(pDoc,pBuffer);
	if(wTaskID == 2) //收集历史数据扎帐
		CollectHistoryCheckInData_Process(pDoc,pBuffer);

	return RET_OK;
}



