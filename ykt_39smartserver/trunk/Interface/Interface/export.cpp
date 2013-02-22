 
#include "stdafx.h"
#include "export.h"
#include "interface.h"
#include "ConnectPool.h"
#include "SystemInfo.h"
#include "tool.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HANDLE hNotify = NULL;
HANDLE hNewHandle = NULL ;

//int    nReload = 0;

//初始化接口层
long __stdcall InitChannels(int nServer, int nFunc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	printf("调用金仕达提供的函数DRTPInitialize,请等待------!!!!\n");
	DRTPInitialize();
	printf("成功调用DRTPInitialize()\n");
	iServerNo = nServer ;
	iFunc = nFunc;
	nReload = 0;
	
	return RET_OK;
}

//销毁接口层
long __stdcall DestoryChannels()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DisConnect();
	CloseNotify();

	DRTPUninitialize();

	return RET_OK;
}

//连接到服务器
long __stdcall ConnectToCenter(char *pszHost, int nPort, int nEncode)
{
    
	//return RET_OK;//debug20050401
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int nConnectNumber = GetPrivateProfileInt("INTERFACE", "CONNECTNUM", 15, szINIFile);

	if( nConnectNumber <= 0 || nConnectNumber >= 100 )
		nConnectNumber = 15 ;
	
	if( !ConnectPool.Initialized(nConnectNumber, pszHost, nPort, nEncode) )
	{
		WriteLog("三九前置与金仕达主动连接连接通讯平台%s:%d失败!\n", pszHost, nPort);
		return RET_SYSERROR;
	}

	WriteLog("三九前置与金仕达主动连接通讯平台%s:%d成功!...服务号:%d....主功能号:%d\n", pszHost, nPort, iServerNo, iFunc);

	if( SmartRegister() != RET_OK )
	{
		WriteLog("三九前置与金仕达注册失败! 系统将不能正常运行, 请联系系统管理员!!!\n");
		return RET_SYSERROR;
	}

	if( SmartSignIn() != RET_OK )
	{
		WriteLog("三九前置机与金仕达签到失败! 系统将不能正常运行, 请联系系统管理员!!!\n");
		return RET_SYSERROR;
	}

	return RET_OK;
}

//关闭连接
long __stdcall DisConnect()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SmartSignOut();
	ConnectPool.DestroyPool();

	return 0L;
}

//初始化本地通知
long __stdcall CreateNotify(char *pszBind, int nPort)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
#if __DEBUG_INTERFACE__
	hNotify = DRTPConnect(pszBind, (WORD)nPort, (WORD)0);
#else
	hNotify = (HANDLE)0x9001;
#endif

	if( hNotify == NULL )
	{                       
		WriteLog("三九前置与金仕达被动连接通讯平台%s:%d失败!(CreateNotify)\n", pszBind, nPort);
		return RET_NG;
	}
	WriteLog("三九前置与金仕达被动连接通讯平台%s:%d成功!...服务号:%d....主功能号:%d.....(CreateNotify)\n", pszBind, nPort, iServerNo, iFunc);
	return RET_OK;
}

//关闭本地通知
long __stdcall CloseNotify()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if( hNotify != NULL )
	{
#if __DEBUG_INTERFACE__
		DRTPClose(hNotify);
		WriteLog("三九前置与金仕达关闭通讯平台连接!(CloseNotify)");
#endif
		hNotify = NULL ;
	}
	return 0L;
}

//发送通知数据
long __stdcall SendDataPro(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if __DEBUG_INTERFACE__
	if( DRTPSend(hNotify, nDest, nFunc, pszData, nLen, nPriority, bRouter) )
	{
		return RET_OK;
	}
	else
	{
		char szText[1024];
		DRTPGetLastError(hNotify, szText, 1024);
		
//		if( !strcmp(szText, "10054") )
		{
			ConnectPool.ReConnect(hNotify);
//			if( DRTPSend(hNotify, nDest, nFunc, pszData, nLen, nPriority, bRouter) )
//			{
//				return RET_OK;
//			}
		}
	}
	return RET_NG;
#else
	return RET_OK;
#endif
}

//接收通知数据
long __stdcall RecvDataPro(char *pszBuffer, int nLen, int nTimeOut)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if __DEBUG_INTERFACE__
	ZeroMemory(pszBuffer, nLen);
	long iResult = DRTPReceive(hNotify, pszBuffer, nLen, nTimeOut);
	if( iResult <= 0 )
	{
		char  szText[1024];
		DRTPGetLastError(hNotify, szText, 1024);

//		if( iResult == -1 )
		{
			ConnectPool.ReConnect(hNotify);
			iResult = DRTPReceive(hNotify, pszBuffer, nLen, nTimeOut);
			if( iResult > 0 )
			{
				//WriteLog("三九前置与金仕达重连后接收数据成功(RecvDataPro)\n");
				return iResult;
			}
		}
		return RET_NG;
	}
	//WriteLog("三九前置接收金仕达数据成功\n");
	return iResult;
#else
	printf("----------RecvDataPro未执行任何动作------------\n");
	return nLen;
#endif
}

//发送数据
long __stdcall SendData(HANDLE& hHandle, int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if __DEBUG_INTERFACE__
	if( DRTPSend(hHandle, nDest, nFunc, pszData, nLen, nPriority, bRouter) )
	{
		WriteLog("三九前置向金仕达发送数据成功(SendData)\n");
		return RET_OK;
	}
	else
	{
		char szText[1024];
		DRTPGetLastError(hHandle, szText, 1024);

//		if( !strcmp(szText, "10054") )
		{
			ConnectPool.ReConnect(hHandle);
//			if( DRTPSend(hHandle, nDest, nFunc, pszData, nLen, nPriority, bRouter) )
//			{
//				WriteLog("三九前置重连金仕达后发送数据成功(SendData),发送内容:%s\n",pszData);
//				return RET_OK;
//			}
		}
	}
	return RET_NG;
#else
	return RET_OK;
#endif
}


//接收数据
long __stdcall RecvData(HANDLE& hHandle, char *pszBuffer, int nLen, int nTimeOut)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if __DEBUG_INTERFACE__
	ZeroMemory(pszBuffer, nLen);
	long iResult = DRTPReceive(hHandle, pszBuffer, nLen, nTimeOut);
	if( iResult <= 0 )
	{			
		char  szText[1024];
		DRTPGetLastError(hHandle, szText, 1024);
		WriteLog("调用金仕达接收数据失败函数[DRTPReceive()] 返回值iResult= %ld::DRTPGetLastError返回内容:%s\n....................\n",iResult,szText);				
		WriteLog("再向金仕达接收一次...................");		
		ConnectPool.ReConnect(hHandle);
		iResult = DRTPReceive(hHandle, pszBuffer, nLen, nTimeOut);
		if( iResult > 0 )
		{
			//WriteLog("三九前置再次重连金仕达后接收数据成功(RecvData),接收内容:%s\n",pszBuffer);
			return iResult;
		}		
		WriteLog("三九前置接收金仕达数据失败(RecvData),DRTPGetLastError返回内容:%s\n",szText);
		return RET_NG;
	}
	//WriteLog("三九前置接收金仕达数据成功(RecvData),接收内容:%s\n",pszBuffer);
	return iResult;
#else
	return nLen;
#endif
}

//----------------------------------------------------------------------------
//
//  Function:   SendTick
//
//  Synopsis:   发心跳包
//
//  Arguments:  none
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall SendTick()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ST_CPACK rpack;
	unsigned char szBuffer[10960];
	int  nLen = sizeof(szBuffer);

	memset(&rpack, 0, sizeof(rpack));
	memset(szBuffer, 0, sizeof(szBuffer));

	rpack.head.RequestType = 930099; 
	rpack.head.firstflag = 1;   /* 是否第一个请求（首包请求）*/
	rpack.head.nextflag = 0;    /* 是否后续包请求*/
	rpack.head.recCount = 1;    /* 本包的记录数*/
	rpack.head.retCode = 0;     /* 返回代码*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);

	char omsg[256];
	if( EncodeBuf(&rpack, szBuffer, &nLen, omsg) )
	{
		if( SendDataPro(iServerNo, iFunc, (char*)szBuffer, nLen, 1, FALSE) == RET_OK )
		{			
			//WriteTickLog("发心跳包成功! 服务号:%d, 子功能号:%d\n", iServerNo, iFunc);
			return RET_OK;
		}
	}

	WriteTickLog("发送心跳包失败! 请检查金仕达中间层!! 服务号:%d, 子功能号:%d", iServerNo, iFunc);

	return RET_SYSERROR;
}

long __stdcall GetTickNumber()
{
	return gTick;
}

//发设备心跳  (不用!!!! 20050305)
long __stdcall SendDocTick(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ST_CPACK rpack;
	unsigned char szBuffer[8192];
	int  nLen = sizeof(szBuffer);

	memset(&rpack, 0, sizeof(rpack));
	memset(szBuffer, 0, sizeof(szBuffer));

	rpack.head.RequestType = 930099; 
	rpack.head.firstflag = 1;   /* 是否第一个请求（首包请求）*/
	rpack.head.nextflag = 0;    /* 是否后续包请求*/
	rpack.head.recCount = 1;    /* 本包的记录数*/
	rpack.head.retCode = 0;     /* 返回代码*/
	rpack.head.userdata = 0;

	char szDateTime[24];
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	sprintf(szDateTime, "%02d%02d%02d%02d%02d%02d", 
		SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);
	SetValue(&rpack.head,&rpack.pack, F_SDATE0, pDoc->m_szDeviceID);
	SetValue(&rpack.head,&rpack.pack, F_SHOLDER_AC_NO, szDateTime);
	SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pDoc->m_sDownBlackTime);

	SetValue(&rpack.head,&rpack.pack, F_DAMT0, "0");
	SetValue(&rpack.head,&rpack.pack, F_DAMT1, "0");
	SetValue(&rpack.head,&rpack.pack, F_DAMT2, "0");

	char omsg[256];
	if( EncodeBuf(&rpack, szBuffer, &nLen, omsg) )
	{
		WriteTickLog("发送设备心跳包! 设备ID=%s", pDoc->m_szDeviceID);
		return SendDataPro(iServerNo, iFunc, (char*)szBuffer, nLen, 1, FALSE);
	}

	return RET_SYSERROR;
}

//----------------------------------------------------------------------------
//
//  Function:   ReadSmartDocList
//
//  Synopsis:   读入设备档案表
//
//  Arguments:  pSmartDoc -- 设备档案表
//				nRecCount -- 记录数
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall ReadSmartDocList(TSSmartDoc *pSmartDoc, long *nRecCount)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ST_CPACK rpack;
	ST_CPACK apack;
	ST_PACK  apackarray[60];
	char buffer[20960];

	WriteLog("三九前置向金仕达调用功能号%d, 申请获取全部设备档案表\n", 930037);

	long k = 0 ;
	bool bEnd = false;
	int  nlen = 0 ;
	int  nRow = 0 ;
	int  nfirst = 1 ;
	int  nLen = sizeof(buffer);
	char omsg[256];
	ST_PACK *pPacket = NULL;

	HANDLE& hHandle = ConnectPool.Alloc();

#if __DEBUG_INTERFACE__
//#if 0
	while( !bEnd )
	{
		if( k >= MAX_SMART_DOC )
		{
			ConnectPool.Free(hHandle);
			WriteLog("设备档案数量大于%d, 请检查设备档案参数表!!!!\n", MAX_SMART_DOC);
			break;
		}

		memset(&rpack, 0, sizeof(rpack));

		rpack.head.RequestType = 930037; 
		rpack.head.recCount = 1;    /* 本包的记录数*/
		rpack.head.retCode = 0;     /* 返回代码*/
		rpack.head.userdata = 0;

		if( nfirst )
		{
			rpack.head.firstflag = 1;   /* 是否第一个请求（首包请求）*/
			rpack.head.nextflag = 0;    /* 是否后续包请求*/
			nfirst = 0 ;
		}
		else
		{
			rpack.head.firstflag = 0;   /* 是否第一个请求（首包请求）*/
			rpack.head.nextflag = 1;    /* 是否后续包请求*/
			memcpy(&rpack.head.hook,&apack.head.hook,sizeof(rpack.head.hook));
			rpack.head.hook.queuetype=apack.head.hook.queuetype;
		}

		SetValue(&rpack.head,&rpack.pack, F_SDATE1, "00000000");
		SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//前置机注册号
		SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//动态密钥

		nLen = sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));

		if( !EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) )
		{
			ConnectPool.Free(hHandle);
			WriteLog("执行功能号930037读入设备档案表时,运行EncodeBuf失败\n");
			return RET_SYSERROR;
		}
	//	printf("执行功能号930037读入设备档案表\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) != RET_OK )
		{
			ConnectPool.Free(hHandle);
			WriteLog("执行功能号930037读入设备档案表时,运行SendData失败\n");
			return RET_SYSERROR;
		}

		memset(buffer, 0, sizeof(buffer));

		nLen = sizeof(buffer);
		nlen = RecvData(hHandle, buffer, nLen, 10000);
		if( nlen <= 0 )
		{
			ConnectPool.Free(hHandle);
			WriteLog("执行功能号930037读入设备档案表时,运行RecvData失败\n");
			return RET_SYSERROR;
		}

		BOOL bRet=DecodeBufWithArray((unsigned char*)buffer,nlen,&apack,apackarray,&nRow,omsg);
		if( !bRet || apack.head.retCode )
		{
			ConnectPool.Free(hHandle);
			WriteLog("执行功能号930037读入设备档案表时,运行DecodeBufWithArray,返回无数据,失败!\n");
			return RET_SYSERROR;
		}

		WriteLog("执行功能号930037读入设备档案表时,得到设备数量为:%d,设备参数为:\n",nRow);

		for(int i=0; i< nRow; i++)
		{
			if( i == 0 ) pPacket = &apack.pack;
			else  pPacket = &apackarray[i-1];

			strcpy(pSmartDoc[k].m_szMacCode, pPacket->semp);		//终端机型号代码
			strcpy(pSmartDoc[k].m_szMacCard, pPacket->sholder_type);//可用IC卡卡型
			strcpy(pSmartDoc[k].m_szMacModle, pPacket->semp);		//终端机型号
			strcpy(pSmartDoc[k].m_szMacType, pPacket->semp);		//机型名称
			strcpy(pSmartDoc[k].m_szDeviceID, pPacket->sdate1);	//设备ID
			strcpy(pSmartDoc[k].m_szRegister, pPacket->sdate2);	//注册号
			pSmartDoc[k].m_nAuthID=ConvertID(pSmartDoc[k].m_szDeviceID);//授权号
			pSmartDoc[k].m_nMachineNo=pPacket->lvol4;			//机号	
			strcpy(pSmartDoc[k].m_szVersion, pPacket->sdate3);	//设备版本号
			strcpy(pSmartDoc[k].m_szPassword, "000000");			//系统员密码
			strcpy(pSmartDoc[k].m_szOprPasswd, "000000");			//管理员密码
			pSmartDoc[k].m_nPwdswitch=-1;							//密码开关
			strcpy(pSmartDoc[k].m_sClockVer, pPacket->stime0);	  //父设备
			
			strcpy(pSmartDoc[k].m_szOrgid, "001");				  //所属的组织代码
			pSmartDoc[k].m_nPortCount=pPacket->lvol5;			  //服务器端口总数
			pSmartDoc[k].m_nSMTPort=pPacket->lvol6;				  //服务器端口号
			strcpy(pSmartDoc[k].m_szPort, pPacket->sbank_code);	  //通讯端口
			pSmartDoc[k].m_nBaudRate=pPacket->lvol9;			  //波特率
			pSmartDoc[k].m_nCommMode=pPacket->lvol8;			  //链路模式
			strcpy(pSmartDoc[k].m_szAddr, pPacket->sstation0);    //通讯地址
			pSmartDoc[k].m_nStatus=pPacket->lvol7;                //设备状态, 下面定义为:

			pSmartDoc[k].m_nConnType = pPacket->lvol10;			  //通讯方式
			strcpy(pSmartDoc[k].m_szClass, pPacket->snote2);	  //卡类				  //

			pSmartDoc[k].m_wFlowNo=pPacket->lvol11+1;			  //期望流水号 modified
			pSmartDoc[k].m_wLastInvoiceNo=pPacket->lvol11;        //终端交易流水号期末值
			pSmartDoc[k].m_wStateNo=pPacket->lvol12;
			pSmartDoc[k].m_nFlow=1;									//序号
			pSmartDoc[k].m_nBeginInvoice=0;							//扎帐的开始流水
			pSmartDoc[k].m_wSettleinvoice=0;						//扎帐流水号期末值
			pSmartDoc[k].m_wEndInvoice=0;							//扎帐的结束流水号
			strcpy(pSmartDoc[k].m_sBlackExpire, pPacket->sserial0);   //黑名单的有效期
			strcpy(pSmartDoc[k].m_sDownBlackTime, pPacket->sserial1); //黑名单下传时间期末值
			pSmartDoc[k].m_nStartuse=0;								  //签到结果

			pSmartDoc[k].m_nCardID = 12;
			pSmartDoc[k].m_nDealCount = 10;
			pSmartDoc[k].m_nInMoney = 100000;
			pSmartDoc[k].m_nOutMoney = pSmartDoc[k].m_nInMoney; 
			pSmartDoc[k].m_nBeginInvoice = 0 ;
			pSmartDoc[k].m_wFlowNo  = 0 ;
			pSmartDoc[k].m_wStateNo = 0 ;
/*
			WriteLog("终端机型号代码=%s,可用IC卡卡型=%s, 终端机型号=%s, 机型名称=%s\n "
				"设备ID=%s, 注册号=%s, 机号=%d, 设备版本号=%s, 系统员密码=%s, 管理员密码=%s\n"
				"密码开关=%d, 服务器端口总数=%d, 服务器端口号=%d, 通讯端口=%s, 波特率=%d\n"
				"链路模式=%d,通讯地址=%s, 设备状态=%d, 交易流水号期末值=%d, 黑名单的有效期=%s, 黑名单版本=%s, 通讯方式=%d,卡类=%s, 父设备:%s\n",
				pPacket->semp, pPacket->sholder_type, pPacket->semp, pPacket->semp,
				pPacket->sdate1, pPacket->sdate2, pPacket->lvol4, pPacket->sdate3, "000000", "000000", 
				pSmartDoc[k].m_nPwdswitch, pPacket->lvol5, pPacket->lvol6, pPacket->sbank_code, pPacket->lvol9, 
				pPacket->lvol8, pPacket->sstation0, pPacket->lvol7, pPacket->lvol11, pPacket->sserial0, pPacket->sserial1, 
				pPacket->lvol10, pPacket->snote2, pPacket->stime0);
*/

			if( !theApp.CheckSmartDocValid(&pSmartDoc[k]) )
			{
				WriteLog("无效设备!!!\n");
				ZeroMemory(&pSmartDoc[k], sizeof(TSSmartDoc));
			}
			else
			{
				WriteLog("有效设备!ID号=%s, 注册号=%s, 机号=%d, 网络类型:%d..父设备代码=%s\n", 
						  pSmartDoc[k].m_szDeviceID, pSmartDoc[k].m_szRegister, 
						  pSmartDoc[k].m_nMachineNo, pSmartDoc[k].m_nCommMode, pSmartDoc[k].m_sClockVer);
				k++;
			}
		}
		if( apack.head.nextflag == 0 )
			bEnd = true ;
	}

#else
	k = 0 ;
/***********************************************************************************************************************************************************/
// 以下为加入调试信息
/***********************************************************************************************************************************************************/
    int iTick = 0 ;
	char  sTempNo[32];
	char  sIP[32];
	char  szParent[32] = "" ;
	int iMacNo = 1;
	int nPort = 10001;

	strcpy(sIP, "10.83.28.40");

	for(int j=k; j<2; j++)
	{
		sprintf(sTempNo, "0000%04d", j+100);

		//模拟LPort
		if( iTick == 0 || iTick == 15 )
		{
			strcpy(pSmartDoc[k].m_szMacCode, "5301");		//终端机型号代码
			strcpy(pSmartDoc[k].m_szMacModle, "5301");		//终端机型号
			strcpy(pSmartDoc[k].m_szMacType, "5301");		//机型名称
			strcpy(pSmartDoc[k].m_szDeviceID, "0000918F");	//设备ID
			strcpy(pSmartDoc[k].m_szRegister, "0000918F");	//注册号
			pSmartDoc[k].m_nAuthID=ConvertID(pSmartDoc[k].m_szDeviceID);//授权号
			pSmartDoc[k].m_nMachineNo=1;			//机号	
			strcpy(pSmartDoc[k].m_szAddr, sIP);    //通讯地址
			pSmartDoc[k].m_nPortCount=16;			  //服务器端口总数
			sprintf(pSmartDoc[k].m_szPort, "%d", nPort); //nPort++);	  //通讯端口
			strcpy(pSmartDoc[k].m_sClockVer, "");	  //父设备

			iMacNo=1;
			strcpy(szParent, pSmartDoc[k].m_szDeviceID);
			pSmartDoc[k].m_nSMTPort=0;				  //服务器端口号
		}
		else
		{
			//if( iTick == 0 || iTick == 6 || iTick == 8 || iTick == 10 )
			//{
				strcpy(pSmartDoc[k].m_szMacCode, "0226");		//终端机型号代码
				strcpy(pSmartDoc[k].m_szMacCard, "64");//可用IC卡卡型
				strcpy(pSmartDoc[k].m_szMacModle, "0226");		//终端机型号
				strcpy(pSmartDoc[k].m_szMacType, "0226");		//机型名称
			//}
			/*else
			{
				strcpy(pSmartDoc[k].m_szMacCode, "0201");		//终端机型号代码
				strcpy(pSmartDoc[k].m_szMacCard, "64");//可用IC卡卡型
				strcpy(pSmartDoc[k].m_szMacModle, "0201");		//终端机型号
				strcpy(pSmartDoc[k].m_szMacType, "0201");		//机型名称
			}*/

			strcpy(pSmartDoc[k].m_szDeviceID, "00008B1a");	//设备ID
			strcpy(pSmartDoc[k].m_szRegister, "00008B1a");	//注册号
			pSmartDoc[k].m_nAuthID=0x00008B1a;//ConvertID(pSmartDoc[k].m_szDeviceID);//授权号
			pSmartDoc[k].m_nMachineNo=1;//++iMacNo;			//机号	
			pSmartDoc[k].m_nPortCount=16;			  //服务器端口总数
			strcpy(pSmartDoc[k].m_szAddr, sIP);    //通讯地址
			strcpy(pSmartDoc[k].m_sClockVer, szParent);	  //父设备
			pSmartDoc[k].m_nSMTPort=2; //iMacNo;				  //服务器端口号
		}

		if( iTick >= 15 )
			iTick = 0 ;
		else
			iTick++;

		strcpy(pSmartDoc[k].m_szMacCard, "64");//可用IC卡卡型
		strcpy(pSmartDoc[k].m_szVersion, "");	//设备版本号
		strcpy(pSmartDoc[k].m_szPassword, "000000");			//系统员密码
		strcpy(pSmartDoc[k].m_szOprPasswd, "000000");			//管理员密码
		pSmartDoc[k].m_nPwdswitch=-1;							//密码开关
		strcpy(pSmartDoc[k].m_szOrgid, "001");				  //所属的组织代码
		pSmartDoc[k].m_nBaudRate=19200;			  //波特率
		pSmartDoc[k].m_nCommMode=3;			  //链路模式
		pSmartDoc[k].m_nStatus=0;                //设备状态, 下面定义为:
		pSmartDoc[k].m_nConnType = 1;			  //通讯方式
		strcpy(pSmartDoc[k].m_szClass, "FFFFFFFFFF");	  //卡类				  //
		pSmartDoc[k].m_wFlowNo=0;			  //期望流水号 modified
		pSmartDoc[k].m_wLastInvoiceNo=0;        //终端交易流水号期末值
		pSmartDoc[k].m_wStateNo=0;
		pSmartDoc[k].m_nFlow=1;									//序号
		pSmartDoc[k].m_nBeginInvoice=0;							//扎帐的开始流水
		pSmartDoc[k].m_wSettleinvoice=0;						//扎帐流水号期末值
		pSmartDoc[k].m_wEndInvoice=0;							//扎帐的结束流水号
		strcpy(pSmartDoc[k].m_sBlackExpire, "991231010101");   //黑名单的有效期
		strcpy(pSmartDoc[k].m_sDownBlackTime, "991231010101"); //黑名单下传时间期末值
		pSmartDoc[k].m_nStartuse=0;								  //签到结果

		printf("有设备(ID=%s, 注册号:%s, 机号=%d, 网络类型:%d..父设备:%s...\n", 
			pSmartDoc[k].m_szDeviceID, pSmartDoc[k].m_szRegister, 
			pSmartDoc[k].m_nMachineNo, pSmartDoc[k].m_nCommMode, pSmartDoc[k].m_sClockVer);
		k++;
	}
#endif

	gnDocCount = k;
	gpSmartDoc = new TSSmartDoc[gnDocCount];
	if( gpSmartDoc == NULL )
	{
		printf("内存不足.....\n");
		gnDocCount = 0 ;
		ConnectPool.Free(hHandle);
		return RET_SYSERROR;
	}

	long iCount = 0 ;
	memcpy(gpSmartDoc,pSmartDoc,sizeof(TSSmartDoc)*k); 
	memset(pSmartDoc, 0, sizeof(TSSmartDoc)*k);

	for(int i=0; i< k; i++)
	{
		if( theApp.CheckSmartDocValid(gpSmartDoc, k, i) )
		{
			memcpy(&pSmartDoc[iCount++], &gpSmartDoc[i], sizeof(TSSmartDoc));
		}
	}

	memset(gpSmartDoc, 0, sizeof(TSSmartDoc)*k);
	gnDocCount = 0 ;
	k = iCount;

	ConnectPool.Free(hHandle);

	WriteLog("有效设备总数量:%d...........\n", k);

	*nRecCount = k;
	long nKCount = 0 ;
	for(i=0; i<k; i++)
	{
		if( strcmp(pSmartDoc[i].m_sClockVer, "") )
		{
			for(int j=0; j<k; j++)
			{
				if( !strcmp(pSmartDoc[j].m_szDeviceID, pSmartDoc[i].m_sClockVer) && i != j )
				{
					pSmartDoc[i].m_nParentID = pSmartDoc[j].m_nAuthID ;
					pSmartDoc[i].m_nLevel    = 1;
					pSmartDoc[i].m_szLevelArray[0] = (char)pSmartDoc[j].m_nMachineNo;
					pSmartDoc[i].m_szLevelArray[1] = (char)pSmartDoc[i].m_nSMTPort;
					printf("父设备%s\n",pSmartDoc[j].m_szDeviceID);
					printf("------pSmartDoc[i].m_szDeviceID = %s \n",pSmartDoc[i].m_szDeviceID);
					printf("------pSmartDoc[i].m_szLevelArray=%d\n",pSmartDoc[j].m_nMachineNo);
					printf("------pSmartDoc[i].m_szLevelArray=%d\n",pSmartDoc[i].m_nSMTPort);					
					break;
				}
			}
		}
		else
		{
			pSmartDoc[i].m_nLevel=0;
		}
	}

	gnDocCount = k;
	memcpy(gpSmartDoc,pSmartDoc,sizeof(TSSmartDoc)*k); 

	return RET_OK;
}


long __stdcall ReReloadSmartDocList()
{
	 AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(nReload == 1)
	{
		
		//ReadSmartDocList(pSmartDoc,nRecCount);
		nReload =0;
		return 1;
	}

	return RET_OK;
}

//----------------------------------------------------------------------------
//
//  Function:   ReadSmartTaskPlan
//
//  Synopsis:   得到金仕达主动发出的任务
//
//  Arguments:  pTaskPlan -- 任务计划内容
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall ReadSmartTaskPlan(TSSmartTaskPlan *pTaskPlan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//设备心跳监控任务 add by dengjun date 20051116	
	static int	  flag =0;
	static DWORD  StartTime       = GetTickCount();
	static DWORD  StartTimeStatus = GetTickCount();
	static DWORD  TIMESENDTICK    = 600*1000;
	static DWORD  TIMESENDSTATUS  = 10*1000;
	static char   cSysDate[30];

	bool bResult = false;	
	char buffer[10240];
	char cGetDate[20];
	char msg[256];
	int  nLen = sizeof(buffer);
	char omsg[256];
	bool bEnd = false ;
	Tool	cTool;
	
	ST_CPACK apack;
	ST_PACK  apackarray[60];
	int nRow = 0 ;
	int nlen = 0 ;	
	DWORD endTime      =GetTickCount()-StartTime;
	DWORD endTimeStuats=GetTickCount()-StartTimeStatus;
	
	memset(msg,     0x00,sizeof msg);
	memset(cGetDate,0x00,sizeof cGetDate);	
	memcpy(cGetDate,cTool.GetSysTime(),8);

	//第一次运行时,需要从配置文件中获取心跳时间间隔
	if( !flag )
	{		
		char  szDir[MAX_PATH];
		char  strServerINI[MAX_PATH];

		memset(szDir,  0x00,sizeof szDir);
		memset(&apack, 0x00,sizeof(apack));
		memset(strServerINI,0x00,sizeof strServerINI);
		
		flag = 1;
		WriteLog("从配置文件中获取相关心跳时间\n");
		GetCurPath(szDir);
		sprintf(strServerINI, "%s\\SmartServer.ini", szDir);		

		//心跳时间(默认10分钟)
		TIMESENDTICK = GetPrivateProfileInt("SYSTEM", "TICKTIME", 600, strServerINI);
		TIMESENDTICK = 1000*TIMESENDTICK;		

		//终端状态时间(默认为10秒)
		TIMESENDSTATUS = GetPrivateProfileInt("SYSTEM", "STATUSTIME", 30, strServerINI);
		TIMESENDSTATUS = 1000*TIMESENDSTATUS;		
		WriteLog("ReadSmartTaskPlan()心跳时间[%ld毫秒],发送终端状态时间[%ld毫秒],[%s]\n",TIMESENDTICK,TIMESENDSTATUS,strServerINI);
		memset(cSysDate,0x00,sizeof cSysDate);
		memcpy(cSysDate,cTool.GetSysTime(),8);		
	}
		
	//sprintf(msg,"--->向金仕达获取任务()心跳时间差[%ld],心跳时间[%ld毫秒],状态时间差[%ld],终端状态时间[%ld毫秒]\n",endTime,TIMESENDTICK,endTimeStuats,TIMESENDSTATUS);
	//WriteLog(msg);
	
	ZeroMemory(pTaskPlan, sizeof(TSSmartTaskPlan));
	pTaskPlan->nRepeatTime  = 1 ;   //持续多长时间（分钟）
	pTaskPlan->nRepeatTimes = 1;    //重复次数
	
	memset(omsg,      0x00, sizeof omsg  );
	memset(buffer,    0x00, sizeof buffer);
	memset(&apack,    0x00, sizeof apack );
	memset(apackarray,0x00, sizeof apackarray);
	
	bEnd = false;
	while( !bEnd )
	{
		nLen = sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));		
		nlen = RecvDataPro(buffer, nLen,10000);
		if( nlen <= 0 )
		{
			strcpy(msg,"向金仕达获取任务时,未收到响应数据.\n");
			WriteLog(msg);				
			return RET_SYSERROR;
		}		
		nRow = 0 ;
		memset(&apack, 0, sizeof(apack));
		memset(apackarray, 0, sizeof(apackarray));
		BOOL bRet=DecodeBufWithArray((BYTE*)buffer,nlen,&apack,apackarray,&nRow,omsg);	
		if(bRet == FALSE)
		{
			sprintf(msg,"应答数据包报文错误Ret=%d\n", bRet);
			WriteLog(msg);						
			return RET_SYSERROR;
		}
		if(apack.head.retCode)
		{			
			sprintf(msg,"金仕达后台业务处理失败,返回码retcode=%d,返回信息[%s]\n",apack.head.retCode,apack.pack.vsmess);
			WriteLog(msg);			
			return RET_SYSERROR;//XXX为相应的错误码,也可以直接 return  0;
		}
		if( apack.pack.lvol1<=0 )
		{	
			WriteLog("金仕达没有任务下达!!!\n");			
			// add by dengjun 20051117 心跳任务//当没有任务且已经到了发送心跳的时间则发送心跳			
			if( endTime >= TIMESENDTICK )
			{
				WriteLog("由于已经到发送心跳包时间,且金仕达没有任务,开始发送终端心跳包............\n");
				memset(&apack,     0x00, sizeof apack    );
				memset(pTaskPlan, 0x00, sizeof TSSmartTaskPlan);
				StartTime			   = GetTickCount();		
				apack.pack.lvol2       = 930057;
				apack.pack.lvol1       = StartTime;
				apack.head.RequestType = 930057;		
				nRow=1;
				pTaskPlan->nTask	   = 0;
				//2005-12-20 modified by wenjian 
				bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);						
				return (bResult?RET_OK:RET_SYSERROR);				
			}		
			// add by dengjun 20060111 取设备状态
			if( endTimeStuats >= TIMESENDSTATUS)
			{
				//WriteLog("由于已经到发送取终端状态的时间,且金仕达没有任务,开始发送终端数据包............\n");
				memset(&apack,     0x00, sizeof apack    );
				memset(pTaskPlan, 0x00, sizeof TSSmartTaskPlan);

				StartTimeStatus		   = GetTickCount();		
				apack.pack.lvol2       = 930058;
				apack.pack.lvol1       = StartTimeStatus;
				apack.head.RequestType = 930058;		
				nRow=1;
				pTaskPlan->nTask	   = 0;				
				bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);						
				return (bResult?RET_OK:RET_SYSERROR);
			}	
			//则凌晨,初始化LPORT			
			if( memcmp(cSysDate,cGetDate,8) )
			{
				memcpy(cSysDate,cTool.GetSysTime(),8);				
				memset(&apack,    0x00, sizeof apack    );
				memset(pTaskPlan, 0x00, sizeof TSSmartTaskPlan);
				StartTime			   = GetTickCount();		
				apack.pack.lvol2       = 999999;
				apack.pack.lvol1       = StartTime;
				apack.head.RequestType = 999999;		
				nRow=1;
				pTaskPlan->nTask	   = 0;				
				bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);						
				return (bResult?RET_OK:RET_SYSERROR);				
			}
			return RET_NOTASK;		//金仕达没有任务下达
		}
		//有任务
		if( apack.head.firstflag == 1 )
		{
			bResult = theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);
		}
		else
		{	
			bResult = theApp.MakeNextTaskPlan(pTaskPlan, &apack, apackarray, nRow);
		}
		if( !apack.head.nextflag )	bEnd = true ;
	}
	
	// add by dengjun 20051117 心跳任务	
	if( endTime >= TIMESENDTICK )
	{
		WriteLog("由于已经到发送心跳包时间,收到金仕达任务,开始发送终端心跳包,与心跳任务一起处理............\n");
		memset(&apack, 0x00,sizeof(apack));		
		StartTime			   = GetTickCount();		
		apack.pack.lvol2       = 930057;
		apack.pack.lvol1       = StartTime;
		apack.head.RequestType = 930057;
		nRow=1;
		bResult = theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);						
	}

	//取终端设备状态 // add by dengjun 20060111 取设备状态
	if( endTimeStuats >= TIMESENDSTATUS)
	{
		//WriteLog("由于已经到发送取终端状态时间,且金仕达没有任务,开始发送终端状态数据包,与心跳任务一起处理............\n");
		memset(&apack,     0x00, sizeof apack);		
		memset(pTaskPlan,  0x00, sizeof TSSmartTaskPlan);
		StartTimeStatus		   = GetTickCount();		
		apack.pack.lvol2       = 930058;
		apack.pack.lvol1       = StartTimeStatus;
		apack.head.RequestType = 930058;		
		nRow=1;
		bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);								
	}				
	//由于LPORT运行一整天，有时可能通讯不上，则凌晨,初始化LPORT			
	if( memcmp(cSysDate,cGetDate,8) )
	{
		memcpy(cSysDate,cTool.GetSysTime(),8);		
		memset(&apack,     0x00, sizeof apack);
		memset(pTaskPlan,  0x00, sizeof TSSmartTaskPlan);		
		apack.pack.lvol2       = 999999;
		apack.pack.lvol1       = GetTickCount();
		apack.head.RequestType = 999999;		
		nRow=1;		
		bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);	
	}
	return (bResult?RET_OK:RET_SYSERROR);
}


long __stdcall ReReadSmartTaskPlan(TSSmartTaskPlan *pTaskPlan)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	pTaskPlan->nTaskPlanID = GetTickCount()-5;	
	sprintf(pTaskPlan->szTaskName,"功能号:%d", 100); //任务计划名称
	pTaskPlan->nTaskCycle=0;                  //任务计划执行周期
	GetCurDateTime(pTaskPlan->szBeginTime);   //开始日期时间
	pTaskPlan->nRepeatTime = 1 ;              //持续多长时间（分钟）
	pTaskPlan->nRepeatTimes = 1;             //重复次数
	GetCurDateTime(pTaskPlan->szTaskTime);    //任务计划的时间
	pTaskPlan->nTask = 0 ;

	int p=0;
	for(int i=0; i< gnDocCount; i++)
	{
		if( !gpSmartDoc[i].m_nParentID )
		{
			pTaskPlan->pTask[p].nTaskID = GetTickCount();
			pTaskPlan->pTask[p].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[p].nAuthID = gpSmartDoc[i].m_nAuthID ;
			strcpy(pTaskPlan->pTask[p].szDeviceID, gpSmartDoc[i].m_szDeviceID);
			strcpy(pTaskPlan->pTask[p].szTaskCode,"70");
			pTaskPlan->pTask[p].nPriority = 9;
			pTaskPlan->pTask[p].nFunc = 930005;
				
		    //if( pPacket->pack.lvol4 ) 
			sprintf(pTaskPlan->pTask[p].szMemo, "%d", 1);
			//	else
			//		sprintf(pTaskPlan->pTask[p].szMemo, "%d", pPacket->pack.lvol0);
				p++;
				pTaskPlan->nTask++;
			//	WriteLog("!!!广播黑名单....设备:%s.....卡号:%d....\n", gpSmartDoc[i].m_szDeviceID, pPacket->pack.lvol0);
		}
	//wenjian comment below line
	//	Sleep(3);
	}

	//if( pTaskPlan->nTask > 0 )
	//	iCount = 1 ;
	return RET_OK;
}


//----------------------------------------------------------------------------
//
//  Function:   ReportFinished
//
//  Synopsis:   将任务执行结果发给金仕达传输层
//
//  Arguments:  pTaskPlan -- 任务计划内容
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall ReportFinished(TSSmartTaskPlan *pTaskPlan)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_OK;
}

//----------------------------------------------------------------------------
//
//  Function:   OutputRealData
//
//  Synopsis:   将硬件数据流转换为接口数据并发给金仕达传输层
//
//  Arguments:  nType     -- 数据类型
//				ucRawData -- 收上的数据
//				nDataLen  -- 收上的数据长度
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall OutputRealData(TSSmartTask *pTask, TSSmartDoc *pDoc, int nType, unsigned char *ucRawData, int nDataLen)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	long iResult = RET_OK;
	ST_CPACK    rpack;

	switch(nType)
	{
		case 0x01:	//收费机
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddSFCount(1);
			break;
		case 248: //上海理工转帐机
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);			
			rpack.head.RequestType = 930030; //应答码
			break;
		case 0x21:  //收费机(历史)
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //应答码		
			break;
		case 0x02:	//计时宝
			iResult = theApp.ConvertIdentifyData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930101; 
			break;
		case 0x22:  //计时宝(历史)
			iResult = theApp.ConvertIdentifyData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		case 0x03:  //扎帐	
		case 0x23:  //扎帐(历史)
			iResult = theApp.ConvertStateData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddJZCount(1);
			break;
		case 0x04:  //补助		
			iResult = theApp.ConvertAssisData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddBZCount(1);
			break;
		case 0x24:  //补助(历史)
			iResult = theApp.ConvertAssisData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //应答码		
			break;			
		case 0x05:  //挂失
			break;
		case 0x06:  //增值机	
			iResult = theApp.ConvertDealData1(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddCZCount(1);
			break;
		case 0x26:  //增值机(历史)
			iResult = theApp.ConvertDealData1(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //应答码		
			break;
		case 0x07:  //增值机管理费	
		case 0x27:  //增值机管理费(历史)	
			iResult = theApp.ConvertDealData2(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddCZCount(1);
			break; 
		case 0x08:	//终端无反应
		case 0x09:	//无对应序号的数
			iResult = theApp.ConvertError(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		case 0x81:  //挂失
		case 0x82:  //解挂
		case 0x83:  //修改密码
			iResult = theApp.ConvertGSJData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		default:
			printf("未知的数据类型!.............\n");
			break;
	}

	//经过很运行,发现系统经常被送上来异常数据,都是无效数据,
	if( iResult == RET_DATACRC_ERROR )
	{
		return RET_OK;
	}

	if( iResult != RET_OK ) 
	{
		WriteLog("将硬件数据流转换为接口数据并发给金仕达传输层....失败!.......\n");
		return RET_SYSERROR;
	}

	if( !pDoc->m_nStartuse && strcmp(pDoc->m_szMacType, "5301") && 
		( nType == 0x01 || nType == 0x02 || nType == 0x03 || nType == 0x04 || nType == 0x06 )  )
	{
		//theApp.SignIn(pDoc);
		//pDoc->m_nStartuse = 1 ;
	}

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];
	HANDLE& hHandle = ConnectPool.Alloc(); //hNewHandle;

	DWORD nTick1 = GetTickCount();

	memset(buffer, 0x00, sizeof buffer );
	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				memset(&apack, 0, sizeof(apack));
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{					
					printf("apack.head.retCode=%d\n",apack.head.retCode);
					printf("发送RequestType = %d 接收RequestType=%d",rpack.head.RequestType,apack.head.RequestType);
					if(!apack.head.retCode)
					{
						ConnectPool.Free(hHandle);

						WriteLog("功能号=%d, 保存数据到金仕达成功!消息=%s 耗费时间(毫秒)%d...\n", apack.head.RequestType,apack.pack.vsmess, GetTickCount()-nTick1 );
						return RET_OK;
					}
					else
					{
						WriteLog("保存数据到金仕达失败! 金仕达返回错误:功能号=%d, 返回码=%d, 消息=%s! 耗费时间(毫秒)%d...\n", 
							apack.head.RequestType, apack.head.retCode, apack.pack.vsmess, GetTickCount() - nTick1 );
					}
				}
			}
		}
	}
	ConnectPool.Free(hHandle);
	return RET_SYSERROR;
}

//----------------------------------------------------------------------------
//
//  Function:   GetParam
//
//  Synopsis:   得到系统参数
//
//  Arguments:  nType   -- 参数类型
//				pParam  -- 返回的参数
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall GetParam(int nType, TSSystemParam *pParam)
{
	switch(nType)
	{
	case 0:   //所有参数
		memcpy(pParam,&GlobalParam, sizeof(TSSystemParam));
		pParam->nParameter4 = -1;
		break;
	case 1:  //读卡的信息
		break;
	case 2:  //
		break;
	case 3:
		break;
	default:
		break;
	}
	return RET_OK;
}

//终端机签到
long __stdcall SignIn(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SignInDoc(pDoc);
}

//终端机签出
long __stdcall SignOut(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SignOutDoc(pDoc);
}

//前置机签出
long __stdcall SmartSignOut()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

/*	if( gpSmartDoc != NULL )
	{
		for(long i=0; i< gnDocCount; i++)
		{
			if( strcmp(gpSmartDoc[i].m_szMacCode, "5301") )
			{
				WriteLog("前置机签出!%s\n", gpSmartDoc[i].m_szDeviceID);
				SignOut(&gpSmartDoc[i]);
			}
		}
	}
*/
	WriteLog("前置机签出!\n");

	return theApp.SmartSignOut();
}

//前置机签到
long __stdcall SmartSignIn()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SmartSignIn();
}

//前置机注册
long __stdcall SmartRegister()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SmartRegister();
}

//处理返回的结果
long __stdcall ReportTaskResult(TSSmartTask *pTask, long iResult, TSResultData *pData)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.ReportResult(pTask, iResult, pData);
}

//----------------------------------------------------------------------------
//
//  Function:   ReadCardGSInfo
//
//  Synopsis:   验证挂失、解挂、修改密码等业务的密码
//
//  Arguments:  none
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall ReadCardGSInfo(int nflag, TSGSJRecord *pRecord)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.ReadGSCardInfo(nflag, pRecord);
}

//----------------------------------------------------------------------------
//
//  Function:   SendDeviceTick
//
//  Synopsis:   发设备心跳
//
//  Arguments:  none
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall SendDeviceTick(TSSmartDoc *pDoc)
{

//WriteLog("In SendDeviceTick()\n");

    AFX_MANAGE_STATE(AfxGetStaticModuleState());		

	pDoc->m_dwDBTick = GetTickCount();
	ST_CPACK rpack;
	unsigned char szBuffer[8192];
	int  nLen = sizeof(szBuffer);

	memset(&rpack,   0, sizeof(rpack));
	memset(szBuffer, 0, sizeof(szBuffer));

	rpack.head.RequestType = 930057; 
	rpack.head.firstflag   = 1;   /* 是否第一个请求（首包请求）*/
	rpack.head.nextflag    = 0;    /* 是否后续包请求*/
	rpack.head.recCount    = 1;    /* 本包的记录数*/
	rpack.head.retCode     = 0;     /* 返回代码*/
	rpack.head.userdata    = 0;

	char szDateTime[24];
	SYSTEMTIME  SysTime;
	CSystemInfo info;
	memset(&SysTime,  0x00,sizeof SysTime);
	memset(szDateTime,0x00,sizeof szDateTime);
	
	GetLocalTime(&SysTime);
	sprintf(szDateTime, "%04ld%02ld%02ld%02ld%02ld%02ld", 
		SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

//WriteLog("SendDeviceTick() systime=%s\n",szDateTime);

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));  //前置注册ID
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);
	SetValue(&rpack.head,&rpack.pack, F_SDATE1, pDoc->m_szDeviceID);	  //设备ID
	SetValue(&rpack.head,&rpack.pack, F_SPHONE3, szDateTime);		     //心跳时间
	SetValue(&rpack.head,&rpack.pack, F_DAMT0, GetValue(5));//GetValue(info.nDiskFreeSpace/info.nDiskTotalSpace*100) );//硬盘利用百分比
	SetValue(&rpack.head,&rpack.pack, F_DAMT1, GetValue(3));//GetValue(info.nUserMemory/info.nMemoryTotal*100));	//内存利用百分比
	SetValue(&rpack.head,&rpack.pack, F_DAMT2, GetValue(2));//GetValue(100-info.nCPU));//CPU利用百分比
	SetValue(&rpack.head,&rpack.pack, F_LVOL2, GetValue(pDoc->m_nStatus)); //设备状态		
	SetValue(&rpack.head,&rpack.pack, F_SSERIAL4, pDoc->m_szTableName); //黑名单版本
	SetValue(&rpack.head,&rpack.pack, F_SHOLDER_AC_NO2, pDoc->m_sDownBlackTime);//设备当前时间
	SetValue(&rpack.head,&rpack.pack, F_DAMT3, GetValue(1)); //1未上传流水数量

//WriteLog("SendDeviceTick() pack finished\n");
//WriteLog("设备:%s,时钟:%s::版本%s::终端状态:%ld\n",pDoc->m_szDeviceID,pDoc->m_sDownBlackTime,pDoc->m_szTableName,pDoc->m_nStatus);

	HANDLE& hHandle = ConnectPool.Alloc();
	if (hHandle== NULL)	
	{
//WriteLog("SendDeviceTick() HANDLE& hHandle = ConnectPool.Alloc() NULL\n");
		return RET_OK;
	}
	char omsg[2048];
	memset(omsg,0x00,sizeof omsg);

	if( EncodeBuf(&rpack, szBuffer, &nLen, omsg) )
	{
		//WriteLog("-----发送设备监控心跳包ID[ %s ]---------------\n",pDoc->m_szDeviceID);		
		if( SendData(hHandle, iServerNo, iFunc, (char*)szBuffer, nLen, 1, FALSE) == RET_OK )
		{
			nLen = sizeof(szBuffer);
			memset(szBuffer, 0, sizeof(szBuffer));
			int nlen = RecvData(hHandle, (char*)szBuffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				memset(&apack, 0, sizeof(apack));
				if( DecodeBuf((unsigned char*)szBuffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						ConnectPool.Free(hHandle);
						//WriteTickLog("发送设备监控心跳包成功! 服务号:%d, 子功能号:%d, , 设备ID=%s", iServerNo, iFunc, pDoc->m_szDeviceID);						
						return RET_OK;
					}
					else
					{
						WriteTickLog("发送设备监控心跳包失败! 设备ID=%s, 发送设备监控心跳包时返回:%s\n", pDoc->m_szDeviceID, apack.pack.vsmess);
					}
				}
				else
					printf("DecodeBuf error");
			}
			else
				printf("debug   接收数据失败\n");
		}
	}

	ConnectPool.Free(hHandle);
	WriteLog("发送设备监控心跳包失败! 服务号:%d, 子功能号:%d, 设备ID=%s", iServerNo, iFunc, pDoc->m_szDeviceID);
	return RET_OK;
}

long __stdcall DownloadBlackCard(TSSmartDoc *pDoc, int nFlag, char *pszFileName)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.DownloadBlackList(pDoc, nFlag, pszFileName);
}

long __stdcall OutputBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.OutputResultBlackCard(pDoc, nFlag, pCard);
}
