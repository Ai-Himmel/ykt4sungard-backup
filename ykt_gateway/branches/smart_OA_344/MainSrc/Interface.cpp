#include "stdafx.h"
#include "public.h"
#include "interface.h"

CInterface::CInterface()
{
	m_nPort		=0;
	m_drtpno	=0;	
	m_mainfunc	=0;
	m_bConnectStatus=false;
	for( int i=0; i<NHANDLECOUNT; i++ )
	{
		m_handler[i].handler=NULL;
		m_handler[i].bStatus=false;	
	}

	memset(m_szHost,   0,sizeof m_szHost);
	memset(m_szText,   0,sizeof m_szText);
	memset(m_cPackPath,0,sizeof m_cPackPath);
	strcpy(m_cPackPath,m_Data.GetCurPath());
	strcat(m_cPackPath,"\\cpack.dat");
}

CInterface::~CInterface()
{
	SMT_ClosePackHandle();
}

/*=================================================================
* Function ID :  SMT_InterfaceInit
* Input       :  char* szAddr int nPort
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  初始化系统接口，该函数在系统中只能调用一次
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_InterfaceInit(char* szAddr, int nPort )
{
	m_nPort = nPort;
	strcpy(m_szHost,szAddr);
	
	if(!BCCCLTInit(1))
	{
		return false;
	}
	if((m_drtpno=AddDrtpNode(m_szHost,m_nPort)) < 0)
	{
		return false;
	}
	//打开调试日志
	if( g_IniFilePara.bWriteDebugLog )
	{
		SetDebugSwitch(true);
	}
	if(!XPackInit(1))
	{
		return false;
	}
	for( int i=0; i<NHANDLECOUNT; i++ )
	{
		m_handler[i].handler = NewXpackHandle(m_cPackPath);	
		if( m_handler[i].handler==NULL )
		{
			SMT_ClosePackHandle();
			return false;
		}
	}
	m_handler[0].bStatus=true;
	m_bConnectStatus=true;
	return true;
}

/*=================================================================
* Function ID :  SMT_GetXDHandle
* Input       :  从cPack句柄中获取一个有效的句柄
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : 成功返回句柄  失败返回空
* Description :  
* Notice	  :
*=================================================================*/
XDHANDLE CInterface::SMT_GetXDHandle()
{
	int i=0;
	XDHANDLE nHandle=NULL;

	g_CriticalSectionLock.Lock();
	while( i<10 )
	{
		for( int i=0; i<NHANDLECOUNT; i++ )
		{
			if( !m_handler[i].bStatus&&m_handler[i].handler!=NULL )
			{
				m_handler[i].bStatus=true;				
				g_CriticalSectionLock.Unlock();
				return m_handler[i].handler;
			}
		}
		i++;
		Sleep(20);
	}
	g_CriticalSectionLock.Unlock();
	return nHandle;
}

/*=================================================================
* Function ID :  SMT_GetXDHandleRecorder
* Input       :  从cPack句柄中获取一个有效的句柄
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : 成功返回句柄  失败返回空
* Description :  
* Notice	  :
*=================================================================*/
XDHANDLE CInterface::SMT_GetXDHandleRecorder()
{
	m_handler[1].bStatus=true;
	return m_handler[1].handler;
}

/*=================================================================
* Function ID :  SMT_SetXDHandleFree
* Input       :  从cPack句柄中获取一个有效的句柄
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : 成功返回句柄  失败返回空
* Description :  
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_SetXDHandleFree(XDHANDLE nHandle)
{
	g_CriticalSectionLock.Lock();
	for( int i=0; i<NHANDLECOUNT; i++ )
	{
		if( (DWORD)m_handler[i].handler==(DWORD)nHandle )
		{		
			m_handler[i].bStatus=false;			
			break;
		}
	}
	g_CriticalSectionLock.Unlock();
	return true;
}

/*=================================================================
* Function ID :  SMT_ReConnect
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  若中断后新连接
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_ReConnect(int nPostion)
{
	m_handler[nPostion].bStatus=false;
	if( m_handler[nPostion].handler!=NULL )
	{
		if( !DeleteXpackHandle(m_handler[nPostion].handler) )
		{
			m_handler[nPostion].handler=NULL;
			return false;
		}
		m_handler[nPostion].handler=NULL;		
	}
	if( (m_handler[nPostion].handler=NewXpackHandle(m_cPackPath))==NULL )
	{
		return false;
	}
	return true;
}
XDHANDLE CInterface::SMT_GetHandle(int nPosition)
{
	g_CriticalSectionLock.Lock();
	ASSERT(m_handler[nPosition].bStatus==false);
	m_handler[nPosition].bStatus = true;
	g_CriticalSectionLock.Unlock();
	return m_handler[nPosition].handler;
}
/*=================================================================
* Function ID :  ClosePackHandle
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  释放打包区
* Notice	   :  
*
*=================================================================*/
bool CInterface::SMT_ClosePackHandle()
{
	bool bFlag=true;
	for( int i=0; i<NHANDLECOUNT; i++ )
	{
		m_handler[i].bStatus=false;
		if( m_handler[i].handler!=NULL )
		{
			if( !DeleteXpackHandle(m_handler[i].handler) )
			{
				Sleep(50);
				DeleteXpackHandle(m_handler[i].handler);				
				bFlag=false;			
			}
			m_handler[i].handler=NULL;
		}		
	}
	return bFlag;
}

/*=================================================================
* Function ID :  PackInit
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  向包中压数据前应先调用该方法
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_PackInit(XDHANDLE nHandle)
{
	return ResetPackHandle(nHandle);
}

/*=================================================================
* Function ID :  SetRequestFunID
* Input       :  int nFunId 业务的功能号
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  将功能号打入包中
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_SetRequestFunID(XDHANDLE nHandle,int nFunId)
{
	return SetRequestType(nHandle,nFunId);
}

/*=================================================================
* Function ID :  SetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为整数
*					
*=================================================================*/
bool CInterface::SMT_SetValue(XDHANDLE nHandle,int nRow,char * FieldName,int Value)
{
	return SetIntFieldByName(nHandle,nRow,FieldName,Value);	
}

/*=================================================================
* Function ID :  SetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为浮点型
*					
*=================================================================*/
bool CInterface::SMT_SetValue(XDHANDLE nHandle,int nRow,char * FieldName,double Value)
{	
	return SetDoubleFieldByName(nHandle,nRow,FieldName,Value);
}

/*=================================================================
* Function ID :  SetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为字符
*					
*=================================================================*/
bool CInterface::SMT_SetValue(XDHANDLE nHandle,int nRow,char * FieldName,char* Value)
{	
	return SetStringFieldByName(nHandle,nRow,FieldName,Value);	
}

/*=================================================================
* Function ID :  GetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为整数
*					
*=================================================================*/
bool CInterface::SMT_GetValue(XDHANDLE nHandle,int nRow,char * FieldName,int *Value)
{
	return GetIntFieldByName(nHandle,nRow,FieldName,Value);	
}

/*=================================================================
* Function ID :  SMT_GetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为浮点型
*					
*=================================================================*/
bool CInterface::SMT_GetValue(XDHANDLE nHandle,int nRow,char * FieldName,double *Value)
{	
	return GetDoubleFieldByName(nHandle,nRow,FieldName,Value);
}

/*=================================================================
* Function ID :  SMT_GetValue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	  :  值为字符
*					
*=================================================================*/
bool CInterface::SMT_GetValue(XDHANDLE nHandle,int nRow,char * FieldName,char* Value,int ValueSize)
{		
	return GetStringFieldByName(nHandle,nRow,FieldName,Value,ValueSize);	
}

/*=================================================================
* Function ID :  SendData
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  返回true 表示成功  false表示失败
* Description :  打包
* Notice	   :  值为字符
*					
*=================================================================*/
bool CInterface::SMT_SendAndRecvData(int nPostion,XDHANDLE& nHandle,DWORD TimeOut,int*errcode,char* errmsg)
{	
	try
	{
		if( nHandle == NULL )
		{
			SMT_ReConnect(nPostion);
			nHandle = SMT_GetHandle(nPostion);
			return false;
		}
		if( !CallRequest(nHandle,m_drtpno,0,m_mainfunc,TimeOut,errcode,errmsg) )
		{
			SMT_ReConnect(nPostion);
			nHandle = SMT_GetHandle(nPostion);
			m_bConnectStatus=false;
			return false;
		}
		if( !m_bConnectStatus ) m_bConnectStatus=true;
		return true;
	}
	catch (...)
	{
		strcpy(errmsg,"调用金仕达CallRequest()时抛异常!!");
		return false;
	}
}

/*=================================================================
* Function ID :  RecvStatus
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  0成功 非0失败
* Description :  
* Notice	   :  得到金仕达返回数据时的状态
*=================================================================*/
int CInterface::SMT_RecvStatus( XDHANDLE nHandle)
{	
	int errcode=0;

	if(!GetRetCode(nHandle,&errcode) )
	{		
		return 1;
	}
	return errcode;
}

/*=================================================================
* Function ID :  GetRowCount
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  0成功 非0失败
* Description :  
* Notice	  :  获取一个包中的行数
*=================================================================*/
bool CInterface::SMT_GetRowCount(XDHANDLE nHandle,int *row)
{
	return GetRecordCount(nHandle,row);	
}

/*=================================================================
* Function ID :  PackIsEof
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  是否还有后续包
*=================================================================*/
bool CInterface::SMT_PackIsEof(XDHANDLE nHandle)
{
	return HaveNextPack(nHandle);	
}

/*=================================================================
* Function ID :  GetNextpack
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  得到下一包
*=================================================================*/
bool CInterface::SMT_NextPack(XDHANDLE nHandle,DWORD TimeOut,int *errcode,char* errmsg)
{
	return CallNext(nHandle,TimeOut,errcode,errmsg);
}

/*=================================================================
* Function ID :  GetSysTask
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  从金仕达获取任务
*=================================================================*/
bool CInterface::SMT_GetSysTask()
{
	int			i=0,j=0;
	DWORD		nStartTime=GetTickCount();
	DWORD		nTaskTime=GetTickCount();
	DWORD		nLastCollectTime = GetTickCount();
	DWORD		nCurrTime = GetTickCount();
	SMARTPOS	cPos;
	char		ucRegNo[9];
	char		szMsg[64];
	list<CSocketSmart>::iterator	SocketSmart;

	memset(&cPos,0,sizeof cPos);
	g_nTotalCount=g_VSmartPos.size();
	if( g_IniFilePara.lGetTaskWaitTime<500)
	{
		g_IniFilePara.lGetTaskWaitTime=500;
	}
	g_nMsgID=1;
	
	while( g_StartFlag )
	{
		nCurrTime = GetTickCount();
		if(nCurrTime-nLastCollectTime>g_IniFilePara.lCollForceTime*60*1000) // 5 分钟
		{
			if(nCurrTime - nLastCollectTime > (g_IniFilePara.lCollForceTime+g_IniFilePara.lCollForceLastTime)*60*1000)
			{
				nLastCollectTime = nCurrTime;
				m_pDlg->AddString("强制采集流水！");
			}
		}
		else
		{
#if 0
			for( j=0; j<g_nTotalCount; j++ )
			{
				//水控设备不进行黑名单校对
				if( !memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_0243,2) ||
					!memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_0244,2) ||
					!memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_5302,2) ||
					!memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_0245,2) ||
					!memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_5301,2) ||
					!memcmp(g_VSmartPos[j].ucpMachineCode,MACHINE_TYPE_0121,2) 
					)
				{
					continue;
				}
				SMT_GetDeviceBlackCardTask(g_VSmartPos[j]);	//获取黑名单任务
				if( !g_StartFlag) break;	
				if( GetTickCount()-nStartTime>20*60*1000)	//每20分钟上传一次设备状态到金仕达
				{
					m_pDlg->WriteLog("开始向金仕达上传设备状态");
					SMT_UpDeviceStatus();
					nStartTime=GetTickCount();
				}
				Sleep(50);
				SMT_ReportTaskResult();		//将任务结果送给金仕达			
			}
#else
			for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
			{
				for(i = 0;i < SocketSmart->m_nTotalPos;++i)
				{
					if( !memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0243,2) ||
						!memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0244,2) ||
						!memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_5302,2) ||
						!memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0245,2) ||
						!memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_5301,2) ||
						!memcmp(SocketSmart->m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0121,2) 
						)
					{
						continue;
					}
					if(SocketSmart->m_SmartPos[i].nCommunicationStatus == 0xFF) // 设备不通
						continue;
					SMT_GetDeviceBlackCardTask(SocketSmart->m_SmartPos[i]);	//获取黑名单任务
					if( !g_StartFlag) break;	
					if( GetTickCount()-nStartTime>20*60*1000)	//每20分钟上传一次设备状态到金仕达
					{
						m_pDlg->WriteLog("开始向金仕达上传设备状态");
						SMT_UpDeviceStatus();
						nStartTime=GetTickCount();
					}
					Sleep(50);
					SMT_ReportTaskResult();		//将任务结果送给金仕达		
				}
			}
#endif
		}
		if( GetTickCount()-nStartTime>20*60*1000)	//每20分钟上传一次设备状态到金仕达
		{		
			m_pDlg->WriteLog("开始向金仕达上传设备状态");
			SMT_UpDeviceStatus();
			nStartTime=GetTickCount();
			Sleep(10000);
		}
		Sleep(2000);
		i=0;
		while( i++<3 )
		{
			if( !g_StartFlag)	break;
			SMT_ReportTaskResult();		//将任务结果送给金仕达		
			Sleep(g_IniFilePara.lGetTaskWaitTime*2);
		}
		if(g_IniFilePara.bWaterMode)
		{
			SMT_GetDeviceTask("");
		}
		else 
		{
			//if(GetTickCount()-nTaskTime>60*1000)
			nTaskTime = GetTickCount();
			memset(ucRegNo,0,sizeof ucRegNo);
			//m_pDlg->AddString("开始向金仕达获取设备任务");
#if 0
			if(GetTickCount()-nTaskTime>60*1000)
			{
				j = 0;
				for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
				{
					// 服务器
					if(SocketSmart->m_TaskCount > SocketSmart->m_nTotalPos*2)
					{
						continue;
					}
					else
					{
						if(SocketSmart->m_nTotalPos==0)
							continue;
						
						for(i = 0;i < SocketSmart->m_nTotalPos;++i)
						{
							// 设备不通
							if(SocketSmart->m_SmartPos[i].nCommunicationStatus == 0xFF)
								continue;
							m_Data.BcdToAsc(SocketSmart->m_SmartPos[i].ucRegNo,4,(unsigned char*)ucRegNo);
							SMT_GetDeviceTask(ucRegNo);
							j++;
						}
					}
				}
			}
#else
			for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
			{
				// 服务器
				if(SocketSmart->m_TaskCount > SocketSmart->m_nTotalPos*2)
				{
					continue;
				}
				else
				{
					if(SocketSmart->m_nTotalPos==0)
						continue;
					
					for(i = 0;i < SocketSmart->m_nTotalPos;++i)
					{
						// 设备不通
						//if(SocketSmart->m_SmartPos[i].nCommunicationStatus == 0xFF)
						//	continue;
						// 如果设备上传获取有任务，本次再次从后台获取任务
						if(SocketSmart->m_SmartPos[i].nHasTask==1)
						{
							m_Data.BcdToAsc(SocketSmart->m_SmartPos[i].ucRegNo,4,(unsigned char*)ucRegNo);
							if(SMT_GetDeviceTask(ucRegNo))
							{
								SocketSmart->m_SmartPos[i].dLastTaskTickCount = GetTickCount();
								SocketSmart->m_SmartPos[i].nHasTask=1;
								j++;
							}
							else
							{
								SocketSmart->m_SmartPos[i].nHasTask=0;
							}
						}
						else if(GetTickCount()-SocketSmart->m_SmartPos[i].dLastTaskTickCount>=60*1000)
						{
							m_Data.BcdToAsc(SocketSmart->m_SmartPos[i].ucRegNo,4,(unsigned char*)ucRegNo);
							if(SMT_GetDeviceTask(ucRegNo))
							{
								SocketSmart->m_SmartPos[i].nHasTask=1;
								j++;
							}
							SocketSmart->m_SmartPos[i].dLastTaskTickCount = GetTickCount();
						}
					}
				}
			}
#endif
			sprintf(szMsg,"开始向金仕达获取设备任务完成，共[%d]",j);
			m_pDlg->AddString(szMsg);
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_ReportTaskResult
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  true 有 false无
* Description :  
* Notice	  :  向金仕达报告任务结果
*=================================================================*/
bool CInterface::SMT_ReportTaskResult()
{
	DWORD	nTimeOut=20000;
	int		nErrCode=0,nRow=0,nRowTotal=0;
	char	sErrMsg[128],sValue[128];
	char	sDeviceID[20];
	int		nValue=0;
	long	nFunID=0;
	SMARTTASKRESULT mTaskResult;
	
	memset(sValue,		0,sizeof sValue);
	memset(sErrMsg,		0,sizeof sErrMsg);
	memset(sDeviceID,   0,sizeof sDeviceID);
	memset(&mTaskResult,0,sizeof mTaskResult);

	//获取任务结果
	while( m_pDlg->SMT_GetOneTaskResult(&mTaskResult) )
	{		
		if( mTaskResult.nAcction==SMT_SMARTFRONTDELBLACKLIST||
			mTaskResult.nAcction==SMT_SMARTFRONTADDBLACKLIST
		  )
		{
			byte sStr[128],CRC[10];
			int nLen=0;
			memset(CRC,0,sizeof CRC);
			memset(sStr,0,sizeof sStr);
			sprintf((char*)sStr,"%ld%s",mTaskResult.Pos.nMemo,(char*)mTaskResult.Pos.sMemo);			
			nLen=strlen((char*)sStr);
			memcpy(sStr+nLen,mTaskResult.Pos.ucSndData,2);
			if( m_Data.CRC_CCITT(nLen+2,sStr,CRC) )
			{
				return false;
			}
		}

		if( !g_StartFlag)							break;
		if( m_handler[0].handler==NULL)				return false;	
		//初始化cPack包
		if( !SMT_PackInit(m_handler[0].handler) )	return false;	
		//设置功能号		
		if( mTaskResult.nAcction==SMT_SMARTFRONTADDBLACKLIST||
			mTaskResult.nAcction==SMT_SMARTFRONTDELBLACKLIST
		  )
		{
			nFunID=SMT_SMARTFRONTSETBLACKCARD;
		}
		else
		{
			nFunID=SMT_SMARTFRONTSETTASKRESULT;
		}
		if( !SMT_SetRequestFunID(m_handler[0].handler,nFunID) )	
		{
			return false;
		}
		
		SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);		//前置机注册号
		SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);					//动态密钥	
		SMT_SetValue(m_handler[0].handler,0,"lvol1",(int)mTaskResult.Pos.nMessageID);			//消息ID号
		if( mTaskResult.ResultStatus )
		{
			SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)0);								//返回码
			SMT_SetValue(m_handler[0].handler,0,"vsmess","成功"); // 成功信息
		}
		else
		{
			if( mTaskResult.nTaskResultStatus==0 ) mTaskResult.nTaskResultStatus=6;
			SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)mTaskResult.nTaskResultStatus);				//返回码
			SMT_SetValue(m_handler[0].handler,0,"vsmess",mTaskResult.ucErrMsg);	//返回错误信息
		}
		//对相应的功能号的响应数据进行打包
		switch( mTaskResult.nAcction )
		{
			case SMT_SMARTFRONTADDBLACKLIST://增加黑名单
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //设备ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				memset(sValue,0,sizeof sValue);
				strcpy(sValue,(char*)mTaskResult.Pos.sMemo);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);//版本
				sprintf(sErrMsg,"[返回] 增加黑名单 金仕达任务 设备ID->%.8X 版本->%s 卡号->%ld MsgID->%ld",
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTDELBLACKLIST://删除黑名单
				memset(sValue,0,sizeof sValue);
				strcpy(sValue,(char*)mTaskResult.Pos.sMemo);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);	//版本
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //设备ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				sprintf(sErrMsg,"[返回] 删除黑名单 金仕达任务 设备ID->%.8X 版本->%s 卡号->%ld MsgID->%ld",								
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTGETTIMEWHITELISTVER: // 下载白名单机版本
				memset(sValue,0,sizeof sValue);
				strncpy(sValue,(char*)mTaskResult.Pos.sMemo,12);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);	//版本
				SMT_SetValue(m_handler[0].handler,0,"lvol3",(int)mTaskResult.Pos.nMemo); // 卡号
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //设备ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				sprintf(sErrMsg,"[返回] 白名单 金仕达任务 设备ID->%.8X 版本->%s 卡号->%ld MsgID->%ld",								
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTUPMAINPARA:	//上传设备主参数
				break;
			case SMT_SMARTFRONTGETCLOCK:	//上传时钟
				memset(sValue,0,sizeof sValue);
				sprintf(sValue,"%02ld%02ld%02ld%02ld%02ld%02ld",
					mTaskResult.Pos.ucRecData[0],
					mTaskResult.Pos.ucRecData[1],
					mTaskResult.Pos.ucRecData[2],
					mTaskResult.Pos.ucRecData[3],
					mTaskResult.Pos.ucRecData[4],
					mTaskResult.Pos.ucRecData[5]);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);
				break;
			case SMT_SMARTFRONTMANAGERATE: //下传管理费比率
				nValue=(int)mTaskResult.Pos.ucSndData[0];
				SMT_SetValue(m_handler[0].handler,0,"lvol6",nValue);
				break;
			default:
				break;
		}
		for( int i=0;i<3; i++ )
		{
			if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
			{
				sprintf(m_szText,"..............ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
				m_pDlg->AddString(m_szText);
				m_pDlg->WriteLog(sErrMsg);
				Sleep(100);
				continue;
			}
			if( SMT_RecvStatus(m_handler[0].handler) )				
			{
				Sleep(100);
				continue;
			}
			if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) ) 
			{
				Sleep(100);
				continue;
			}
			break;
		}
		Sleep(50);
	}
	return true;
}

/*=================================================================
* Function ID :  GetSysTask
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  true 有 false无
* Description :  
* Notice	  :  从金仕达获取黑名单任务
*=================================================================*/
bool CInterface::SMT_GetDeviceBlackCardTask(SMARTPOS cPos)
{
	DWORD	nTimeOut=1000;	//超时时间
	int		nErrCode=0;		//错误代码
	int		nRow=0,nRowTotal=0;
	char	sErrMsg[128];	
	byte	CRC[5],sStr[128];
	int		nTaskID=0;
	int		nCardNo=0;
	int     nFlag=0;	
	char	cDeviceID[19];
	byte	ucID[10];
	int 	nFunTaskID=0;
	int		nDeviceFlag=0;
	bool	bFlag=false;
	int		nValue=0;
	char	sValue[128];
	SMARTCOMMPACK mPack;
	static  DWORD nStartTime=GetTickCount();

	memset(cDeviceID, 0,sizeof cDeviceID);
	memset(&mPack,    0,sizeof mPack  );
	memset(sErrMsg,   0,sizeof sErrMsg);
	memset(sValue,    0,sizeof sValue);
	memset(CRC,       0,sizeof CRC   );
	memset(sStr,	  0,sizeof sStr);
	memset(ucID,      0,sizeof ucID);
	
	if( m_handler[0].handler==NULL)
	{
		return false;
	}
	
	if( !m_handler[0].bStatus) m_handler[0].bStatus=true;
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTGETBLACKCARD) )	
	{
		return false;
	}
	
	m_Data.BcdToAsc(cPos.ucpIDNo,4,(byte*)cDeviceID);
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(m_handler[0].handler,0,"scert_no",cDeviceID);							//物理ID号
	SMT_SetValue(m_handler[0].handler,0,"lvol1",(long)1);								//获取黑名单条数
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"前置通讯向金仕达请求任务时,金仕达服务可能已经断开[ ret=%ld,sErrmsg=%s]",nErrCode,sErrMsg);
		m_pDlg->AddString(m_szText);
		m_pDlg->WriteLog(m_szText);
		Sleep(2000);
		return false;
	}
	
	if( SMT_RecvStatus(m_handler[0].handler) )				return false;	
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) ) return false;
	if( nRowTotal<=0 )
	{
		if( GetTickCount()-nStartTime>5*1000 )
		{
			m_pDlg->AddString("前置通讯向金仕达请求黑名单任务时,金仕达告之没有任务......");
			nStartTime=GetTickCount();
		}
		return false;
	}
	else
	{
		//0：添加1：删除
		SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nFlag);				//增删标志	
		SMT_GetValue(m_handler[0].handler,nRow,"scert_no",cDeviceID,sizeof(cDeviceID));
		nValue=0;
		memset(sValue,0,sizeof sValue);
		SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nValue); //卡号
		SMT_GetValue(m_handler[0].handler,nRow,"sname",sValue,sizeof(sValue)); //版本
		m_Data.trim(sValue);
		m_Data.trim(cDeviceID);
		sprintf(sErrMsg,"前置获取到金仕达黑名单任务[功能号->%ld 设备ID->%s 卡号->%ld 版本->%s MsgID->%ld]",
			SMT_SMARTFRONTGETBLACKCARD,
			cDeviceID,
			nValue,
			sValue,
			cPos.nMessageID);
		//判断是否同一设备
		m_Data.AscToBcd((byte*)cDeviceID,8,ucID);
		if( memcmp(cPos.ucpIDNo,ucID,4) ) //add by dj 20071009 不是该设备的名单不处理
		{
			return false; //得到的不是同一设备的名单
		}
		m_pDlg->AddString(sErrMsg);
	}
	memset(cDeviceID,0,sizeof cDeviceID);
	memset(sValue,   0,sizeof sValue);
		
	SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nValue);						//卡号
	SMT_GetValue(m_handler[0].handler,nRow,"sname",sValue,sizeof(sValue));			//版本
	SMT_GetValue(m_handler[0].handler,nRow,"scert_no",cDeviceID,sizeof(cDeviceID)); //设备ID	
	m_Data.trim(sValue);
	mPack.nMemo=nValue;				//卡号
	memcpy(mPack.sMemo,sValue,12);  //版本
	m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
	//计算CRC
	sprintf((char*)sStr,"%ld%s",mPack.nMemo,(char*)mPack.sMemo);			
	m_Data.CRC_CCITT(strlen((char*)sStr),sStr,mPack.ucSndData);	
	mPack.nSndDataLen=4;
	mPack.nMessageID=cPos.nMessageID;
	switch(nFlag)
	{
		case 0:	//增加黑名单						
			mPack.nAcction=SMT_SMARTFRONTADDBLACKLIST;
			mPack.nTaskCode=SMT_SMARTFRONTADDBLACKLIST;			
			mPack.nFlag=1;
			mPack.ucCmd=0xA4;			
			sprintf(sErrMsg,"[获取] 增加黑名单 金仕达任务 设备ID->%s 版本->%s 卡号->%ld MsgID->%ld ",
				cDeviceID,
				mPack.sMemo,
				nValue,
				mPack.nMessageID);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,cDeviceID);
			bFlag=false;
			break;
		case 1:	//删除黑名单
			mPack.nAcction=SMT_SMARTFRONTDELBLACKLIST;
			mPack.nTaskCode=SMT_SMARTFRONTDELBLACKLIST;			
			mPack.nFlag=1;
			mPack.ucCmd=0xA5;
			sprintf(sErrMsg,"[获取] 删除黑名单 金仕达任务 设备ID->%s 版本->%s 卡号->%ld MsgID->%ld ",cDeviceID,mPack.sMemo,nValue,mPack.nMessageID);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,cDeviceID);	
			bFlag=false;
			break;
		default:
			return false;	
	}
	//向链路中插入任务
	for( int nTry=0; nTry<3; nTry++)
	{
		if( SMT_InsertTaskToLink(mPack,bFlag) ) 
		{
			break;	 
		}
		Sleep(50);
	}
	return true;
}

/*=================================================================
* Function ID :  GetSysTask
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  true 有 false无
* Description :  
* Notice	  :  从金仕达获取任务
*=================================================================*/
bool CInterface::SMT_GetDeviceTask(const char *regno)
{
	DWORD	nTimeOut=1000;	//超时时间
	int		nErrCode=0;		//错误代码
	int		nRow=0,nRowTotal=0;
	char	sErrMsg[128];	
	byte	CRC[5],sStr[128];
	int		nTaskID=0;
	int		nCardNo=0;
	int     nFlag=0,i=0,j=0;	
	char	cDeviceID[19];
	int 	nFunTaskID=0;
	int		nDeviceFlag=0;
	bool	bFlag=false;
	int		nValue=0;
	char	sValue[256];
	SMARTCOMMPACK mPack;
	static  DWORD nStartTime=GetTickCount();

	memset(cDeviceID, 0,sizeof cDeviceID);		
	memset(&mPack,    0,sizeof mPack  );
	memset(sErrMsg,   0,sizeof sErrMsg);
	memset(sValue,    0,sizeof sValue);
	memset(CRC,       0,sizeof CRC   );
	memset(sStr,	  0,sizeof sStr);
	
	if( m_handler[0].handler==NULL)
	{
		return false;
	}
	
	if( !m_handler[0].bStatus) m_handler[0].bStatus=true;
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTGETTASK) )	
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(m_handler[0].handler,0,"sdate0",(char*)regno);  // 物理设备ID
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"前置通讯向金仕达请求任务时,金仕达服务可能已经断开[ ret=%ld,sErrmsg=%s]",nErrCode,sErrMsg);
		m_pDlg->AddString(m_szText);
		m_pDlg->WriteLog(m_szText);
		Sleep(2000);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )				return false;	
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) ) return false;
	//得到任务ID号 nTaskID
	SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nTaskID);
	SMT_GetValue(m_handler[0].handler,nRow,"lvol1",&mPack.nMessageID); //消息ID号
	SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
	if( mPack.nMessageID<=0 )
	{
		if( GetTickCount()-nStartTime>5*1000 )
		{		
			m_pDlg->AddString("前置通讯向金仕达请求任务时,金仕达告之没有任务......");
			nStartTime=GetTickCount();
		}
		//Sleep(1000);
		return false;
	}
	else
	{
		nValue=0;
		memset(sValue,0,sizeof sValue);
		SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nValue); //卡号
		SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue)); //版本
		m_Data.trim(sValue);
		m_Data.trim(cDeviceID);
		sprintf(sErrMsg,"前置获取到金仕达任务[功能号->%ld 设备ID->%s 卡号->%ld 版本->%s 消息ID->%ld]",
			nTaskID,
			cDeviceID,
			nValue,
			sValue,
			mPack.nMessageID);
		//m_pDlg->AddString(sErrMsg);		
	}
	//根据功能进行处理
	switch(nTaskID)
	{
		case SMT_SMARTFRONTASSISTANTLISTLOAD:	//wlport补助名单下传
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			//卡号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol10",&nValue);
			mPack.ucSndData[0]=nValue>>16;
			mPack.ucSndData[1]=nValue>>8;
			mPack.ucSndData[2]=nValue;
			//发放批次
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[3]=nValue>>8;
			mPack.ucSndData[4]=nValue;			
			//补助金额
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			//补助标志
			if( nValue>=0 )	
			{
				mPack.ucSndData[5]=nValue;
				mPack.ucSndData[6]=nValue>>8;
				mPack.ucSndData[7]=0;
			}
			else
			{
				nValue=0-nValue;
				mPack.ucSndData[5]=nValue;
				mPack.ucSndData[6]=nValue>>8;
				mPack.ucSndData[7]=1;
			}
			mPack.nSndDataLen=8;			
			mPack.nFlag		=1;
			mPack.ucCmd		=0x0C;
			mPack.nAcction	=SMT_SMARTFRONTASSISTANTLISTLOAD;
			mPack.nTaskCode	=SMT_SMARTFRONTASSISTANTLISTLOAD;			
			break;
		case SMT_SMARTFRONTSETCLOCK:	//下传时钟
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nSndDataLen=0;
			mPack.nAcction=SMT_SMARTFRONTSETCLOCK;
			mPack.nTaskCode=SMT_SETCLOCK;
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			break;
		case SMT_SMARTFRONTGETCLOCK:		//上传时钟
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nSndDataLen= 0;
			mPack.nAcction   = SMT_SMARTFRONTGETCLOCK;
			mPack.nTaskCode  = SMT_GETCLOCK;			
			mPack.nFlag		 = nDeviceFlag;
			mPack.nFlag		 = 1;
			break;
		case SMT_SMARTFRONTMANAGERATE:		//下传管理费比率
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[0]=nValue;
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[1]=nValue;
			mPack.nSndDataLen=2;
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag		=1;
			mPack.ucCmd		=0x73;
			mPack.nAcction	=SMT_SMARTFRONTMANAGERATE;
			mPack.nTaskCode	=SMT_SMARTFRONTMANAGERATE;			
			break;	
		case SMT_SMARTFRONTPWDMONEY:		//下传密码启用金额(大金额)
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nValue);
			mPack.ucSndData[0]=nValue;
			mPack.ucSndData[1]=nValue>>8;
			mPack.ucSndData[2]=nValue>>16;
			mPack.nSndDataLen =3;
			mPack.nAcction=SMT_SMARTFRONTPWDMONEY;
			mPack.nTaskCode=SMT_SMARTFRONTPWDMONEY;			
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			mPack.ucCmd=0xCA;
			break;
		case SMT_SMARTFRONTDAYMONEY:		//日累计消费限额
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nValue);
			mPack.ucSndData[0]=nValue;
			mPack.ucSndData[1]=nValue>>8;
			mPack.ucSndData[2]=nValue>>16;
			mPack.nSndDataLen=3;
			mPack.nAcction=SMT_SMARTFRONTDAYMONEY;
			mPack.nTaskCode=SMT_SMARTFRONTDAYMONEY;			
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			mPack.ucCmd=0x70;
			//mPack.ucCmd = 0xCA;
			break;
		case SMT_SMARTFRONTMANAGEPWD:		//设置终端管理员密码
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,6,mPack.ucSndData);
			mPack.nSndDataLen=3;
			mPack.nAcction=SMT_SMARTFRONTMANAGEPWD;
			mPack.nTaskCode=SMT_SMARTFRONTMANAGEPWD;			
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			mPack.ucCmd=0xD6;
			break;
		case SMT_SMARTFRONTSALEHISTROY:		//采集消费历史数据
		case SMT_SMARTFRONTADDHISTROY:		//采集充值历史数据
		case SMT_SMARTFRONTTIMEHISTROY:		//采集计时历史数据
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));			
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);  //开始流水号
			mPack.ucSndData[0]=nValue>>8;
			mPack.ucSndData[1]=nValue;
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);  //结束流水号
			mPack.ucSndData[2]=nValue>>8;
			mPack.ucSndData[3]=nValue;
			mPack.nSndDataLen=4;
			mPack.nAcction =SMT_GETHISTORYDATA;
			mPack.nTaskCode=SMT_GETHISTORYDATA;			
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			mPack.ucCmd=0xBB;
			if( nTaskID==SMT_SMARTFRONTTIMEHISTROY)
			{
				SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);  //流水号
				mPack.ucSndData[0]=nValue>>8;
				mPack.ucSndData[1]=nValue;
				mPack.ucSndData[2]=mPack.ucSndData[0];
				mPack.ucSndData[3]=mPack.ucSndData[1];
			}
			break;
		case SMT_SMARTFRONTADDBLACKLIST:	//增加黑名单
			return true;
		case SMT_SMARTFRONTDELBLACKLIST:	//删除黑名单
			return true;		
		case SMT_SMARTFRONTBROADBLACK:		//广播黑名单
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nCardNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);
			SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			if( nFlag == 1 )
			{
				g_CSmartBlackMemoryOper.SMT_DeleteBlackCard(nCardNo); //删除
				//用于广播收费机使用
				mPack.nAcction=SMT_SMARTFRONTBROADBLACK;
				mPack.nTaskCode=SMT_SMARTFRONTBROADBLACK;
				mPack.ucCmd=0xBE;
				mPack.nSndDataLen=9;
				mPack.ucSndData[0]=nCardNo>>16;
				mPack.ucSndData[1]=nCardNo>>8;
				mPack.ucSndData[2]=nCardNo;
				m_Data.AscToBcd((byte*)sValue,12,mPack.ucSndData+3);
				bFlag=true;
				mPack.nFlag=nFlag;
			}
			else if( nFlag==0   )
			{
				g_CSmartBlackMemoryOper.SMT_InsertBlackCard(nCardNo); //挂失	
				//用于广播收费机使用
				mPack.nAcction=SMT_SMARTFRONTBROADBLACK;
				mPack.nTaskCode=SMT_SMARTFRONTBROADBLACK;
				mPack.ucCmd=0xBE;
				mPack.nSndDataLen=9;
				mPack.ucSndData[0]=nCardNo>>16;
				mPack.ucSndData[1]=nCardNo>>8;
				mPack.ucSndData[2]=nCardNo;
				m_Data.AscToBcd((byte*)sValue,12,mPack.ucSndData+3);
				bFlag=true;
				mPack.nFlag=nFlag;
			}
			//插入广播任务的结果
			SMARTTASKRESULT mTaskResult;
			memset(&mTaskResult,0,sizeof mTaskResult);			
			mTaskResult.ResultStatus     = true;	
			mTaskResult.nAcction	     = mPack.nAcction;
			mTaskResult.nTaskResultStatus= 0;			
			memcpy(&mTaskResult.Pos,&mPack,sizeof(SMARTCOMMPACK));
			m_pDlg->SMT_InsertOneTaskResult(mTaskResult);
			break;
		case SMT_SMARTFRONTOPENORCLOSE: //常开或常关
			//设备ID
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); 
			//开关标志 0-常开1-常关2-恢复正常
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nAcction=SMT_SMARTFRONTOPENORCLOSE;
			mPack.nSndDataLen=0;			//没有数据体
			mPack.nFlag=1;
			if( nFlag==0 )					//常开
			{
				mPack.nTaskCode=SMT_OPENCTRL;
			}
			else if( nFlag==1||nFlag==2 )	//常关、恢复正常
			{
				mPack.nTaskCode=SMT_CLOSECTRL;
			}
			break;
		case SMT_SMARTFRONTCARDTYPE:		//设置终端扩展卡类
			{
				char sBuffer[512];
				memset(sBuffer,0,sizeof sBuffer);	
				memset(cDeviceID,0,sizeof cDeviceID);
				SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
				SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
				SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
				m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
				SMT_GetValue(m_handler[0].handler,nRow,"vsvarstr0",sBuffer,sizeof(sBuffer));				
				mPack.nAcction =SMT_SMARTFRONTCARDTYPE;
				mPack.nTaskCode=SMT_SMARTFRONTCARDTYPE;					
				mPack.nFlag=1;
				mPack.ucCmd=0x67;
				if( !SMT_GetDeviceCardType(&mPack,sBuffer) ) return false; //失败
			}
			break;
		case SMT_SMARTFRONTGETRATE:		//获取设备费率
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nAcction=SMT_SMARTFRONTGETRATE;
			mPack.nTaskCode=nFunTaskID;
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			if( !SMT_GetDeviceOneRate(&mPack) ) return false; //失败
			break;
		case SMT_SMARTFRONTWARNMONEY:	//下传报警金额
			{
				int	nMoney=0;
				memset(cDeviceID,0,sizeof cDeviceID);
				SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
				SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
				SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nMoney);  //金额
				SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);  //方式	
				mPack.nAcction=SMT_SMARTFRONTWARNMONEY;
				mPack.ucSndData[0]=nMoney;
				mPack.ucSndData[1]=nMoney>>8;
				mPack.nSndDataLen=2;
				mPack.nFlag      =1;
				mPack.nTaskCode=SMT_SETWARMMONEY;
				if( nFlag==1 ) { bFlag=true; }//广播
				else {bFlag=false;m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);}
			}
			break;
		case SMT_SMARTFRONTGETMAINPARA:		//前置获取金仕达设备主参数
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);		
			//密码开关
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[0]=nValue;
			//收费方式
			SMT_GetValue(m_handler[0].handler,nRow,"lvol12",&nValue);
			mPack.ucSndData[1]=nValue;
			//卡片最大使用次数
			SMT_GetValue(m_handler[0].handler,nRow,"lvol7",&nValue);
			mPack.ucSndData[2]=nValue>>8;
			mPack.ucSndData[3]=nValue;
			//允许卡消费类别 2
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbankname",sValue,sizeof(sValue)); 
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,4,mPack.ucSndData+4);
			//钱包存款最高限额 3 
			SMT_GetValue(m_handler[0].handler,nRow,"lvol8",&nValue);
			mPack.ucSndData[6]=nValue;
			mPack.ucSndData[7]=nValue>>8;
			mPack.ucSndData[8]=nValue>>16;
			//每次存取款限额 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol11",&nValue);
			mPack.ucSndData[9]=nValue;
			mPack.ucSndData[10]=nValue>>8;
			mPack.ucSndData[11]=nValue>>16;
			//钱包余款最低限额 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol9",&nValue);
			mPack.ucSndData[12]=nValue;
			mPack.ucSndData[13]=nValue>>8;
			mPack.ucSndData[14]=nValue>>16;
			//定值收费使用定值额 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol10",&nValue);
			mPack.ucSndData[15]=nValue;
			mPack.ucSndData[16]=nValue>>8;
			mPack.ucSndData[17]=nValue>>16;
			//增强开关(消费类型) 1 scurrency_type2
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"scurrency_type2",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			mPack.ucSndData[18]=atol(sValue);
			//通信波特率  1	 
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[19]=nValue;
			//钱包属性(代码)  1
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbranch_code0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			mPack.ucSndData[20]=atol(sValue);
			//个人密码密钥 4
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd2",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,8,mPack.ucSndData+21);
			//系统密码 4
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue+4,4,mPack.ucSndData+25);
			//机器使用卡型(卡结构) 
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbank_pwd",sValue,sizeof(sValue));
			mPack.ucSndData[27]=atol(sValue);
			mPack.nSndDataLen=28;
			mPack.nTaskCode	=SMT_SMARTFRONTGETMAINPARA;
			mPack.nAcction	=SMT_SMARTFRONTGETMAINPARA;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			break;
		//计时类下传主参数
		case SMT_SMARTFRONTGETTIMEMAINPARA:
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);		
			//密码开关			
			mPack.ucSndData[0]=0x01;
			//工作模式
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			mPack.ucSndData[1]=nValue;
			//开启时间1
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[2]=nValue;
			//开启时间2
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[3]=nValue;
			//允许卡类
			mPack.ucSndData[4]=0xFF;
			mPack.ucSndData[5]=0xFF;
			//通道模式
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus0",sValue,sizeof(sValue));
			mPack.ucSndData[6]=atol(sValue);
			//存储方式
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus1",sValue,sizeof(sValue));
			mPack.ucSndData[7]=atol(sValue);
			//感应头
			mPack.ucSndData[8]=0x01;
			//保留三个
			mPack.ucSndData[9] =0x00;
			mPack.ucSndData[10]=0x00;
			mPack.ucSndData[11]=0x00;
			//系统管理员密码
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd",sValue,sizeof(sValue));
			m_Data.AscToBcd((byte*)sValue,6,mPack.ucSndData+12);
			//保留
			mPack.ucSndData[15]=0x00;
			mPack.ucSndData[16]=0x00;
			mPack.ucSndData[17]=0x00;
			//显示
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus2",sValue,sizeof(sValue));
			mPack.ucSndData[18]=atol(sValue);
			//波特率
			SMT_GetValue(m_handler[0].handler,nRow,"lvol7",&nValue);
			mPack.ucSndData[19]=nValue;
			mPack.ucSndData[20]=0x00;
			mPack.ucSndData[21]=0x00;
			mPack.ucSndData[22]=0x00;
			mPack.ucSndData[23]=0x00;
			mPack.ucSndData[24]=0x00;
			mPack.ucSndData[25]=0x00;
			mPack.ucSndData[26]=0x00;
			//卡型参数
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lserial0",sValue,sizeof(sValue));
			mPack.ucSndData[27]=atol(sValue);
			mPack.nSndDataLen=28;
			mPack.nTaskCode	=SMT_SMARTFRONTGETMAINPARA;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEMAINPARA;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			break;
		case SMT_SMARTFRONTGETTIMESEGMENT: //计时宝时间段
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			//星期
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			mPack.ucSndData[0]=nValue;
			//时间段条数
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[1]=nValue;
			//第1个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"saddr",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+2);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[2]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[3]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[4]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[5]=atol((char*)CRC);
			}			
			//第2个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"saddr2",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+10);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[10]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[11]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[12]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[13]=atol((char*)CRC);
			}			
			//第3个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sall_name",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+18);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[18]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[19]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[20]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[21]=atol((char*)CRC);
			}			
			//第4个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sall_name",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+26);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[26]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[27]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[28]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[29]=atol((char*)CRC);
			}			
			//第5个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"snote",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+34);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[34]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[35]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[36]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[37]=atol((char*)CRC);
			}
			//第6个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"snote2",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+42);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[42]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[43]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[44]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[45]=atol((char*)CRC);
			}			
			//第7个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"scert_addr",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+50);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[50]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[51]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[52]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[53]=atol((char*)CRC);
			}			
			//第8个时间段	
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbankname",sValue,sizeof(sValue));
			if( strlen(sValue)>0 )
			{
				m_Data.AscToBcd((byte*)sValue,16,mPack.ucSndData+58);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue,2);
				mPack.ucSndData[58]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2,2);
				mPack.ucSndData[59]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+4,2);
				mPack.ucSndData[60]=atol((char*)CRC);
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+6,2);
				mPack.ucSndData[61]=atol((char*)CRC);
			}						
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.nSndDataLen=8*nValue;
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMESEGMENT;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMESEGMENT;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			mPack.ucCmd		=0xB3;
			break;
		case SMT_SMARTFRONTGETTIMEHOLIDAY: //计时设备节假日
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			//节假日
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[0]=nValue;
			
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"vsvarstr0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			nValue=strlen(sValue);
			for( i=0; i<nValue; i++)
			{			
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2*i,2);
				mPack.ucSndData[1+i]=atol((char*)CRC);
			}		
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.nSndDataLen=2*nValue;
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMEHOLIDAY;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEHOLIDAY;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			mPack.ucCmd		=0xB2;
			break;	
		case SMT_SMARTFRONTGETTIMEWHITEVER:	//计时设备白名单版本
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,12,mPack.ucSndData);
			mPack.nSndDataLen=6;
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMEWHITEVER;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEWHITEVER;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			mPack.ucCmd		=0xAE;
			break;
		case SMT_SMARTFRONTGETTIMEWHITELIST: //下传/删除白名单
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			mPack.ucSndData[0]=0x01;
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue); // 卡号
			mPack.nMemo = nValue; // 保存卡号
			memcpy(mPack.ucSndData+1,m_Data.IntToHex(nValue,sValue)+1,3);

			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			if( nValue==0)
			{
				mPack.nSndDataLen=4;
				mPack.ucCmd		=0xAB; // 下传卡号
			}
			else if( nValue==1)
			{
				mPack.nSndDataLen=4;  // 删除卡号
				mPack.ucCmd		=0xAC;
			}
			else if( nValue==2)
			{
				mPack.nSndDataLen=0;
				mPack.ucCmd		=0xAD; // 删除所有白名单
			}
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMEWHITELIST;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEWHITELIST;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;			
			break;			
		case SMT_SMARTFRONTGETTIMEWHITELISTVER: //下传卡号及版本
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	

			mPack.ucSndData[0]=0x01;
			//卡号
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			memcpy(mPack.ucSndData+1,m_Data.IntToHex(nValue,sValue)+1,3);
			mPack.nMemo = nValue;
			//版本
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue)-1);
			m_Data.AscToBcd((byte*)sValue,12,mPack.ucSndData+4);
			memcpy(mPack.sMemo,sValue,12);

			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			if( nValue==0)  //增加
			{
				mPack.nSndDataLen=4+6;
				mPack.ucCmd		=0xAB;
			}
			else if( nValue==1) //删除
			{
				mPack.nSndDataLen=4+6;
				mPack.ucCmd		=0xAC;
			}
			else if( nValue==2)
			{
				mPack.nSndDataLen=0;
				mPack.ucCmd		=0xAD;
			}
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMEWHITELISTVER;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEWHITELISTVER;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;			
			break;
		case SMT_SMARTFRONTGETTIMESWITCH:	//开关控制
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);				
			
			//标导
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			if( nValue==1 )		  mPack.ucCmd=0x9B;		//开
			else if( nValue==2 )  mPack.ucCmd=0x9C;		//关
			else if( nValue==2 )  mPack.ucCmd=0x9D;		//正常
			else return false;
			mPack.nSndDataLen=0;
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMESWITCH;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMESWITCH;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			break;
		case SMT_SMARTFRONTGETEATNUM:	//前置获取餐次数时间 add by dj 20080520
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //设备ID号
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //设备标识
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //功能号
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			
			memset(sValue, 0,sizeof sValue);
			memset(sErrMsg,0,sizeof sErrMsg);	
			memset(sStr,   0,sizeof sStr);
			SMT_GetValue(m_handler[0].handler,nRow,"vsvarstr0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			mPack.nSndDataLen=strlen(sValue)/2;
			j=0;
			for( i=0; i<mPack.nSndDataLen; i++ )
			{
				memset(CRC,0,sizeof CRC);
				memcpy(CRC,sValue+2*i,2);
				if( i%4==0 ) //餐次编号
				{
					sStr[j]=j;
					j++;
				}
				sStr[j]=atoi((char*)CRC); //转换为16进制
				j++;
			}
			mPack.nSndDataLen=1+mPack.nSndDataLen+mPack.nSndDataLen/4;
			mPack.ucSndData[0]=mPack.nSndDataLen/5;
			memcpy(mPack.ucSndData+1,sStr,mPack.nSndDataLen-1);
			mPack.ucCmd		=0x4E;
			mPack.nTaskCode	=SMT_SMARTFRONTGETEATNUM;
			mPack.nAcction	=SMT_SMARTFRONTGETEATNUM;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			break;
		case SMT_SMARTFRONTDOWNGETASSIT: //获取补助名单
			SMT_GetAllInitAssistantList(true,mPack.nMessageID);
			return true;
		default:
			return false;
	}
	//向链路中插入任务
	for( int nTry=0; nTry<3; nTry++)
	{
		if( SMT_InsertTaskToLink(mPack,bFlag) ) 
		{
			break;
		}
		Sleep(50);
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_InsertTaskToLink
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  将任务插入到相应链路
*=================================================================*/
bool CInterface::SMT_InsertTaskToLink(SMARTCOMMPACK mPack,bool bFlag)
{
	int i=0;
	list<CSocketSmart>::iterator	SocketSmart;
	
	//若链路为空,则直接返回
	if( g_LTcpsmart.empty() )	return false;
	if( !bFlag ) //只对传入的设备ID号进行任务增加
	{
		for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
		{
			//指针为空，则直接返回失败
			if( SocketSmart==g_LTcpsmart.end()) continue;
			//服务器 add by dj 20080801
			if( !memcmp(SocketSmart->m_IDNo,mPack.ucpIDNo,4) )
			{
				mPack.nConnectPortNo = 0;								//所连端口号
				mPack.ucMacNo        = SocketSmart->m_MacNum;			//机号
				memcpy(mPack.ucpMachineCode,SocketSmart->m_MacCode,2);	//机型代码
				memcpy(mPack.ucRegNo,SocketSmart->m_regno,4);			//注册号
				mPack.level = 0;
				//压入到任务池中
				if( SocketSmart->InsertTask(&mPack) ) return true;
				else return false;
			}
			//2.检查该服务是否有子设备,若没有,则找下一个服务
			if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) continue;
			for(i=0; i<SocketSmart->m_nTotalPos; i++)
			{
				//把任务落实到具体的POS终端上
				if( !memcmp(SocketSmart->m_SmartPos[i].ucpIDNo,mPack.ucpIDNo,4))
				{
					mPack.nConnectPortNo = SocketSmart->m_SmartPos[i].nPort;		//所连端口号
					mPack.ucMacNo        = SocketSmart->m_SmartPos[i].ucMacNo;		//机号
					memcpy(mPack.ucpMachineCode,SocketSmart->m_SmartPos[i].ucpMachineCode,2); //机型代码
					memcpy(mPack.ucRegNo,SocketSmart->m_SmartPos[i].ucRegNo,4);		//注册号
					// add by tc 20091009 , 判读如果是下级设备,设置上级ID
					if(memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_5301,2)==0)
					{
						mPack.level = 1;
						mPack.level_array[0] = SocketSmart->m_MacNum; // 上级设备机号
						mPack.level_array[1] = SocketSmart->m_SmartPos[i].nConnectPort; // 设备使用的服务器端口号
					}
					else
						mPack.level = 0;
					
					//压入到任务池中
					if( SocketSmart->InsertTask(&mPack) ) return true;
					else return false;
				}
			}
		}
	}
	else //对所有设备进行
	{
		for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
		{
			//指针为空，则直接返回失败
			if( SocketSmart==g_LTcpsmart.end())	continue;
			//2.检查该服务是否有子设备,若没有,则找下一个服务
			if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) continue;
			
			if( mPack.nAcction==SMT_SMARTFRONTBROADBLACK )
			{
				//表示不是水控设备
				if( memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_0245,2)&& 
					memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_0244,2) )
				{
					//若为广播名单则只对收费机进行
					if( mPack.nAcction==SMT_SMARTFRONTBROADBLACK) //广播黑名单
					{
						mPack.ucMacNo = 0xFF;					
						SocketSmart->InsertTask(&mPack);
					}
					continue;
				}
				continue;
			}
			for(i=0; i<SocketSmart->m_nTotalPos; i++)
			{
				mPack.nConnectPortNo = SocketSmart->m_SmartPos[i].nPort;					//所连端口号
				mPack.ucMacNo        = SocketSmart->m_SmartPos[i].ucMacNo;					//机号
				memcpy(mPack.ucpMachineCode,SocketSmart->m_SmartPos[i].ucpMachineCode,2);	//机型代码
				memcpy(mPack.ucRegNo,SocketSmart->m_SmartPos[i].ucRegNo,4);					//注册号
				memcpy(mPack.ucpIDNo,SocketSmart->m_SmartPos[i].ucpIDNo,4);					//ID号
				// add by tc 20091009 , 判读如果是下级设备,设置上级ID
				if(memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_5301,2)==0)
				{
					mPack.level = 1;
					mPack.level_array[0] = SocketSmart->m_MacNum; // 上级设备机号
					mPack.level_array[1] = SocketSmart->m_SmartPos[i].nConnectPort; // 设备使用的服务器端口号
				}
				else
					mPack.level = 0;
				//压入到任务池中
				SocketSmart->InsertTask(&mPack);
			}
		}
	}
	return true;	
}

/*=================================================================
* Function ID :  SMT_UpDeviceStatus
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  上传设备状态到金仕达
*=================================================================*/
bool CInterface::SMT_UpDeviceStatus()
{
	DWORD	nTimeOut=1000;
	int		nErrCode=0,nRow=0,nRowTotal=0,nRegNo=0,i=0,nCount=0;	
	char	vsmess[256],buffer[250*10],sErrMsg[128];
	char	vsvarstr0[256],vsvarstr1[256],vsvarstr2[256],vsvarstr3[256];		
	list<CSocketSmart>::iterator SocketSmart;

	memset(sErrMsg,  0,sizeof sErrMsg);
	memset(vsmess,   0,sizeof vsmess);
	memset(vsvarstr0,0,sizeof vsvarstr0);
	memset(vsvarstr1,0,sizeof vsvarstr1);
	memset(vsvarstr2,0,sizeof vsvarstr2);	
	memset(vsvarstr3,0,sizeof vsvarstr3);
	memset(buffer,   0,sizeof buffer   );

	if( m_handler[0].handler==NULL)
	{
		m_pDlg->WriteLog("向金仕达上传设备状态时,连接句柄无效,停止上传");
		return false;
	}
	for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
	{		
		if( SocketSmart==g_LTcpsmart.end()) return false;
		if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) 
		{
			memset(sErrMsg,0,sizeof sErrMsg);
			sprintf(sErrMsg,"链路IP=%s,没有子设备或子设备大于256[%ld],该链路不上传",SocketSmart->m_IpPar.cIPAddress,SocketSmart->m_nTotalPos);
			m_pDlg->WriteLog(sErrMsg);
			continue;
		}
		for(i=0; i<SocketSmart->m_nTotalPos; i++)
		{
			sprintf(buffer+strlen(buffer),"%.8X%02X",
				m_Data.HexToInt(SocketSmart->m_SmartPos[i].ucpIDNo,4),
				SocketSmart->m_SmartPos[i].nCommunicationStatus);
			nCount+=10;
			if( m_handler[0].handler==NULL)	return false;			
			if( nCount>=250*5)
			{
				memcpy(vsmess,buffer,250);
				memcpy(vsvarstr0,buffer+250,250);
				memcpy(vsvarstr1,buffer+250+250,250);
				memcpy(vsvarstr2,buffer+250+250+250,250);
				memcpy(vsvarstr3,buffer+250+250+250+250,250);
				//初始化cPack包
				if( !SMT_PackInit(m_handler[0].handler) ) return false;
				//设置功能号
				if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTSENDTICK) )	return false;
				
				SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
				SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥	
				SMT_SetValue(m_handler[0].handler,0,"sphone3",(char*)m_Data.GetSysTime());			//前置时间				
				SMT_SetValue(m_handler[0].handler,0,"lvol1",1);								//设备ID是指设备物理ID
				SMT_SetValue(m_handler[0].handler,0,"vsmess",vsmess);								//设备ID与状态	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr0",vsvarstr0);							//设备ID与状态	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr1",vsvarstr1);							//设备ID与状态	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr2",vsvarstr2);							//设备ID与状态	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr3",vsvarstr3);							//设备ID与状态

				if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
				{
					return false;
				}
				if( SMT_RecvStatus(m_handler[0].handler) )  return false;
				memset(vsmess,   0,sizeof vsmess);
				memset(vsvarstr0,0,sizeof vsvarstr0);
				memset(vsvarstr1,0,sizeof vsvarstr1);
				memset(vsvarstr2,0,sizeof vsvarstr2);	
				memset(vsvarstr3,0,sizeof vsvarstr3);
				memset(buffer,   0,sizeof buffer   );
				Sleep(250);
			}
		}
	}
	if( strlen(buffer)>0 )
	{
		if( m_handler[0].handler==NULL)			 return false;
		//初始化cPack包
		if( !SMT_PackInit(m_handler[0].handler) ) return false;
		//设置功能号
		if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTSENDTICK) )	return false;
		if( nCount>250)
		{
			nCount-=250;
			memcpy(vsmess,buffer,250);
		} else strcpy(vsmess,buffer);
		if( nCount>250)
		{
			nCount-=250;
			memcpy(vsvarstr0,buffer+250,250);
		}else strcpy(vsvarstr0,buffer+250);
		if( nCount>250)
		{
			nCount-=250;
			memcpy(vsvarstr1,buffer+250+250,250);
		}else strcpy(vsvarstr1,buffer+250+250);
		if( nCount>250)
		{
			nCount-=250;
			memcpy(vsvarstr2,buffer+250+250+250,250);
		}else strcpy(vsvarstr2,buffer+250+250+250);
		if( nCount>250)
		{
			nCount-=250;
			memcpy(vsvarstr3,buffer+250+250+250+250,250);
		}else strcpy(vsvarstr3,buffer+250+250+250+250);
		SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
		SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥	
		SMT_SetValue(m_handler[0].handler,0,"sphone3",(char*)m_Data.GetSysTime());			//前置时间
		SMT_SetValue(m_handler[0].handler,0,"lvol1",1);								//设备ID是指设备物理ID
		SMT_SetValue(m_handler[0].handler,0,"vsmess",vsmess);	//设备ID与状态	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr0",vsvarstr0);	//设备ID与状态	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr1",vsvarstr1);	//设备ID与状态	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr2",vsvarstr2);	//设备ID与状态	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr3",vsvarstr3);	//设备ID与状态				
		if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
		{					
			return false;
		}
		if( SMT_RecvStatus(m_handler[0].handler) )  return false;
	}
	return true;	
}

/*=================================================================
* Function ID :  SMT_GetAllInitAssistantList
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  获取所有补助名单
*=================================================================*/
bool CInterface::SMT_GetAllInitAssistantList(bool bAnswer,long nReMessageID)
{	
	int		nTimeOut=5000;
	int		nErrCode=0;
	char	sErrMsg[256];
	int		nRowTotal=0,nBatchVer=0;
	int		row_count=0,row=0;
	int		total_rows=0;
	int		errcode=0,nMessageID=0;
	char	cValue[1024];
	byte	ucValue[1024];
	int		nValue=0,nOffSet=0;
	
	memset(cValue, 0,sizeof cValue);
	memset(ucValue,0,sizeof ucValue);	
	memset(sErrMsg,0,sizeof sErrMsg);	
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTDOWNALLASSIT) )
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥

	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )
	{
		return false;
	}
	SMT_GetValue(m_handler[0].handler,0,"lvol1",&nMessageID); //消息ID号
	memset(g_SaveAssistantList,0,sizeof g_SaveAssistantList);
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;
		row = 0;
		while(row < row_count)
		{
			nOffSet=1178*total_rows;
			//批次号版本
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol1",&nBatchVer);
			if( nBatchVer>g_nSaveAssistantVer)
			{
				g_nSaveAssistantVer=nBatchVer;
			}			
			//位图第1部分			
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第2部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第3部分
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);			
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第4部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第5部分
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset4",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第6部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset5",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第7部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset6",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第8部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"scusttypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第9部分
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"ssectypes",cValue,sizeof(cValue));
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第10部分
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"vsmess",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);	
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第11部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第12部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第13部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第14部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);			
			row++;
			total_rows++;
		}
		if(!SMT_PackIsEof(m_handler[0].handler ))	break; //表示已经到包的尾部
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);

	
	//表示不需要应答 //返回响应包 add by dj 20080409
	if( !bAnswer ) return true;
	Sleep(100);	
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTSETTASKRESULT) )
	{
		return false;
	}
		
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(m_handler[0].handler,0,"lvol1",(int)nReMessageID);		//消息ID号
	SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)0);				//返回码	
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )
	{
		return false;
	}
	return true;
}


/*=================================================================
* Function ID :  GetAllInitBlackList
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  获取所有黑名单
*=================================================================*/
bool CInterface::SMT_GetAllInitBlackList(int FunId)
{	
	int		nTimeOut=30000;
	int		nErrCode=0;
	char	sErrMsg[256];
	int		nRowTotal=0;
	int		row_count=0,row=0;
	int		total_rows=0;
	int		errcode=0;
	char	cValue[1024];
	byte	ucValue[1024];
	int		nValue=0,nOffSet=0;
	
	memset(cValue, 0,sizeof cValue);
	memset(ucValue,0,sizeof ucValue);	
	memset(sErrMsg,0,sizeof sErrMsg);	
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号

	if( !SMT_SetRequestFunID(m_handler[0].handler,FunId) )
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);			//动态密钥

	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )
	{
		return false;
	}
	
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;		
		row = 0;
		while(row < row_count)
		{
			nOffSet=1178*total_rows;
			
			//位图第1部分			
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第2部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第3部分
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);			
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第4部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第5部分
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset4",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第6部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset5",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第7部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset6",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第8部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"scusttypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第9部分
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"ssectypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第10部分
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"vsmess",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//位图第11部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第12部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第13部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//位图第14部分
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			row++;
			total_rows++;
		}
		if(!SMT_PackIsEof(m_handler[0].handler ))	break; //表示已经到包的尾部
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);
	return true;
}

/*=================================================================
* Function ID :  GetAllDeviceInfo
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  前置启动时获取所有设备档案信息
*=================================================================*/
bool CInterface::SMT_GetAllDeviceInfo()
{
	int			nTimeOut=5000;
	int			nErrCode=0;
	char		sErrMsg[256];
	int			nRowTotal=0;
	SMARTPOS	cPos;
	
	memset(&cPos,  0,sizeof cPos);
	memset(sErrMsg,0,sizeof sErrMsg);
	g_VSmartPos.clear();
	g_nMsgID=-999999;

	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )									return false;
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTALLDEVICE) )	return false;
	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);		//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(m_handler[0].handler,0,"sdate1","00000000");						//ID
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )				return false;

	int		row_count=0,row=0;
	int		total_rows=0;
	int		errcode=0;
	char	cValue[256];
	int		nValue=0;

	memset(cValue,0,sizeof cValue);
	
	// 下载收有设备
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;		
		row = 0;
		while(row < row_count)
		{
			memset(&cPos,  0,sizeof cPos);
			//设备ID号
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucpIDNo);
			
			//设备注册号
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucRegNo);

			//机号
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol4",&nValue);
			cPos.ucMacNo=(int)nValue;

			//机型代码
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"semp",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,4,cPos.ucpMachineCode);

			//通讯IP地址
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sstation0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy(cPos.cIP,cValue);

			//通讯端口
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sbank_code",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			cPos.nPort=atol(cValue);
			
			//设备版本号			
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucDeviceVer,cValue);

			//卡片结构
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sholder_type",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucCardType,cValue);
			
			//卡类
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"snote2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucCardclass,cValue);
			
			//服务器端口总数
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol5",&nValue); 			
			cPos.nServerPortTotal=nValue;
			
			//设备所接端口
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol6",&nValue); 			
			cPos.nConnectPort=nValue;

			//上级设备ID
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"stime0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucServerDeviceID);
			
			//设备状态
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol7",&nValue); 			
			cPos.nCommunicationStatus=nValue;

			//链路模式
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol8",&nValue);
			cPos.nLinkMode=nValue;

			//数据通讯方式
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol10",&nValue);
			cPos.nDataComWay=nValue;

			//黑名单版本有效期
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sserial0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucBlackCardExp,cValue);

			//黑名单版本
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sserial1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucBlackCardVer,cValue);

			//期末流水号
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol11",&nValue);
			cPos.nInvoiceNoLast=nValue;
			cPos.nMessageID=g_nMsgID++;
			g_VSmartPos.push_back(cPos);
			row++;
			total_rows++;
		}
		
		if(!SMT_PackIsEof(m_handler[0].handler))	break; //表示已经到包的尾部
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);
	return true;
}


/*=================================================================
* Function ID :  SMT_GetDeviceCardType
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  将卡类转换
*=================================================================*/
bool CInterface::SMT_GetDeviceCardType(SMARTCOMMPACK *Task,char* ucData)
{
	
	  int  i=0,j=0;
	  int  nContent=0;
	  byte Buffer[512],cMid[128];
	  int  nCardype[512];
	  int  nLen=0;
	  int  nDatalen=0;

	  memset(nCardype,	0,sizeof nCardype);	  	  
	  memset(Buffer,	0,sizeof Buffer);
	  memset(cMid,		0,sizeof cMid);
	  
	  nCardype[0]=0x00;
	  nCardype[1]=0x00;
	  j=253;
	  while( true )
	  {
		nCardype[2+i++]=ucData[j--]-0x30;
		if( j<0 )break;
	  }
	  //32字节的位图
	  for( i=0; i<32; i++ )
	  {
		  nContent=0;
		  for( j=0; j<8; j++ )
		  {
			  if( j==0&&nCardype[i*8+j] ) nContent+=128;
			  if( j==1&&nCardype[i*8+j] ) nContent+=64;
			  if( j==2&&nCardype[i*8+j] ) nContent+=32;
			  if( j==3&&nCardype[i*8+j] ) nContent+=16;
			  if( j==4&&nCardype[i*8+j] ) nContent+=8;
			  if( j==5&&nCardype[i*8+j] ) nContent+=4;
			  if( j==6&&nCardype[i*8+j] ) nContent+=2;
			  if( j==7&&nCardype[i*8+j] ) nContent+=1;
		  }
		  Buffer[i]=nContent;
	  }	  
	  memcpy(Task->ucSndData,Buffer,32);
	  Task->nSndDataLen=32;	  
	  return true;
}

/*=================================================================
* Function ID :  SMT_GetDeviceOneTask
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  从金仕达获取设备的费率
*=================================================================*/
bool CInterface::SMT_GetDeviceOneRate(SMARTCOMMPACK *Task)
{
	int			nTimeOut=5000;
	int			nErrCode=0;
	char		sErrMsg[256];
	char		cDeviceID[10];
	int			nRowTotal=0;
	byte		sCardKind[33];
	SMARTCOMMPACK mPack;

	memset(&mPack,	 0,sizeof mPack);
	memset(cDeviceID,0,sizeof cDeviceID);
	memset(sErrMsg,  0,sizeof sErrMsg);
	memset(sCardKind,0,sizeof sCardKind);
	
	memcpy(mPack.ucpIDNo,Task->ucpIDNo,4);
	mPack.nTaskCode=SMT_SETCARDTYPE;
	mPack.nFlag=1;
	mPack.nSndDataLen=32;

	m_Data.BcdToAsc(Task->ucpIDNo,4,(byte*)cDeviceID);
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,Task->nTaskCode) )	
	{
		return false;
	}	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);	//动态密钥
	SMT_SetValue(m_handler[0].handler,0,"sdate0",cDeviceID);			//ID
	SMT_SetValue(m_handler[0].handler,0,"lvol0",Task->nFlag);			//设备标识	
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )				return false;

	int		row_count=0,row=0;
	int		total_rows=0;
	int		errcode=0;
	char	cValue[256];
	int		nValue=0;
	int		nLen=0;
	int		nMode=0;	//计费器工作模式
	
	memset(cValue,0,sizeof cValue);
	Task->nSndDataLen=0;
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;		
		row = 0;
		while(row<row_count)
		{
			//费率
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"scust_limit",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			nLen=strlen(cValue);
			m_Data.AscToBcd((byte*)cValue,nLen,Task->ucSndData+Task->nSndDataLen);
			//费率个数
			SMT_GetValue(m_handler[0].handler,row,"lvol1",&nValue); 
			Task->nSndDataLen+=nValue*3;
			//卡类			
			SMT_GetValue(m_handler[0].handler,row,"lvol0",&nValue);
			m_Data.SetCardKind(sCardKind,nValue);
			//计费器工作模式
			if( nMode<=0 )	SMT_GetValue(m_handler[0].handler,row,"lvol2",&nMode); 			
			row++;
			total_rows++;
		}
		if(!SMT_PackIsEof(m_handler[0].handler))	break; //表示已经到包的尾部
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);
	
	//向链路中插入设置卡类的任务
	memcpy(mPack.ucSndData,sCardKind,mPack.nSndDataLen);
	memcpy(mPack.ucpIDNo,Task->ucpIDNo,4);	
	mPack.nAcction=SMT_SMARTFRONTGETRATE;
	SMT_InsertTaskToLink(mPack);
	//向链路中插入工作模式的任务
	memset(&mPack,0,sizeof mPack);
	mPack.nFlag=1;
	mPack.nTaskCode=SMT_SETPOSPLACE;
	mPack.nAcction=SMT_SMARTFRONTGETRATE;
	mPack.nSndDataLen=1;
	memcpy(mPack.ucpIDNo,Task->ucpIDNo,4);
	if( nMode==2 )
	{
		mPack.ucSndData[0]=0x00;
		SMT_InsertTaskToLink(mPack);	
	}
	else if( nMode==1 ) 
	{
		mPack.ucSndData[0]=0xFF;
		SMT_InsertTaskToLink(mPack);
	}
	Task->nTaskCode=SMT_SETFEERATE;
	Task->nFlag=1;
	return true;
}

/*==========================================================
* Function ID :  SMT_SmartRegister
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  前置注册
*=================================================================*/
bool CInterface::SMT_SmartRegister(DWORD nTimeOut)
{
	int		nErrCode=0;
	int		nRow=0,nRowTotal=0;
	char	sErrMsg[128];
	int		nRegNo=0;	
	CSystemInfo info;

	memset(sErrMsg, 0,sizeof sErrMsg);
	//从配置文件中检查是否已经注册
	GetPrivateProfileString("SMARTFRONTREG", "REGISTER", "0",sErrMsg,sizeof(sErrMsg),g_PathIniFileName);
	if( sErrMsg[0]=='1' ) return true;

	memset(sErrMsg, 0,sizeof sErrMsg);
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )				return false;
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTREGISTER) )	return false;
	SMT_SetValue(m_handler[0].handler,0,"scust_auth2","SMART999");		//前置机名称
	SMT_SetValue(m_handler[0].handler,0,"scust_limit",info.szIP);		//前置网卡IP地址
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",info.szMAC);		//前置网卡物理地址
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}

	if( SMT_RecvStatus(m_handler[0].handler) )	return false;
	memset(g_IniFilePara.sKey, 0,sizeof g_IniFilePara.sKey);
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) ) return false;
	SMT_GetValue(m_handler[0].handler,nRow,"lcert_code",&g_IniFilePara.lFrontRegNo);
	SMT_GetValue(m_handler[0].handler,nRow,"scust_limit",g_IniFilePara.sKey,sizeof(g_IniFilePara.sKey));	

	sprintf(sErrMsg,"%ld",g_IniFilePara.lFrontRegNo);
	WritePrivateProfileString("SMARTFRONTREG", "REGNO",		sErrMsg,		g_PathIniFileName);
	WritePrivateProfileString("SMARTFRONTREG", "KEY",		g_IniFilePara.sKey,	g_PathIniFileName);
	WritePrivateProfileString("SMARTFRONTREG", "REGISTER",  "1",			g_PathIniFileName);
	return true;
}

/*=================================================================
* Function ID :  SmartFrontLogin
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  前置签到
*=================================================================*/
bool CInterface::SMT_SmartFrontLogin(DWORD nTimeOut)
{
	int		nErrCode=0;
	char	sErrMsg[128];
	int		nRowTotal=0;
	char	buffer[64];

	memset(buffer, 0,sizeof buffer);
	memset(sErrMsg,0,sizeof sErrMsg);

	//前置注册
	if( !SMT_SmartRegister(nTimeOut) )										return false;	
	//初始化cPack包
	if( !SMT_PackInit(m_handler[0].handler) )								return false;
	//设置功能号
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTLOGIN) )	return false;	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(m_handler[0].handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )								return false;	
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) )					return false;
	memset(g_sWorkKey,0,sizeof g_sWorkKey);
	SMT_GetValue(m_handler[0].handler,0,"scert_addr",buffer,sizeof(buffer));			//工作密钥
	SMT_GetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey,sizeof(g_IniFilePara.sKey));//动态密钥
	SMT_GetValue(m_handler[0].handler,0,"lvol0",&g_nWalletNo);							//钱包号	
	m_Data.AscToBcd((byte*)buffer,strlen(buffer),(byte*)g_sWorkKey);	
	return true;
}

/*=================================================================
* Function ID :  SMT_TimeRecordAnalysis
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  计时记录分析
*=================================================================*/
bool CInterface::SMT_TimeRecordAnalysis(XDHANDLE& nHandler,int nTimeOut,int *nErrCode,char* sErrMsg,char* ssData,STRSALERECORD &StrDeal)
{
	byte		  sBuffer[256],sStr[256];
	char		  sData[256],sMsg[256];	
	char		  sMachineCode[5];		
	int			  nDataType=0,nLen=0;
	char		  sDateStr[9];
	
	memset(sMsg,    0,sizeof sMsg);
	memset(sStr,    0,sizeof sStr);
	memset(sData,   0,sizeof sData);	
	memset(sStr,	0,sizeof sStr);
	memset(sBuffer,	0,sizeof sBuffer);
	memset(&StrDeal,0,sizeof StrDeal);
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//得到数据类型
	nDataType   = atol(m_Data.GetColValues(sData));

	//数据体
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//数据体压缩
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//注册号
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//通信版本
	StrDeal.lVer=sBuffer[4];	
	//启动原因
	StrDeal.lStartReason=sBuffer[5];
	//交易流水号
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//卡型代码
	StrDeal.nICCardCode=(long)sBuffer[22];
	//工作模式
	StrDeal.nWorkMode=(long)sBuffer[20];
	//交易卡号
	if( StrDeal.nICCardCode==0)
	{
		StrDeal.lCardID=m_Data.HexToInt(sBuffer+9,4);	
	}
	else if( StrDeal.nICCardCode==100)
	{
		if( StrDeal.nWorkMode==4)
		{
			StrDeal.lCardID=0;
		}
		else
			StrDeal.lCardID=m_Data.HexToInt(sBuffer+10,3);
	}
	else if( StrDeal.nICCardCode==101)
	{
		StrDeal.lCardID=m_Data.HexToInt(sBuffer+11,2);	
	}
	else
		StrDeal.lCardID=0;
	//显示卡号
	if( StrDeal.nWorkMode == 4 && (StrDeal.nICCardCode == 100 || StrDeal.nICCardCode == 101 ) )
	{
		m_Data.BcdToAsc(sBuffer+8,5,(byte*)StrDeal.sShowCardNo);
	}
	//交易日期
	sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[13],sBuffer[14],sBuffer[15]);
	//交易时间
	sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[16],sBuffer[17],sBuffer[18]);
	//考勤类型
	StrDeal.nTimerType=sBuffer[21];
	//感应头编号
	StrDeal.nInductorNo=sBuffer[23];
	//上下班标志
	StrDeal.nDutyFlag=sBuffer[24];
	if( StrDeal.nDutyFlag>9) StrDeal.nDutyFlag=0;
	//交易标记
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[26],sBuffer[27]);
	//功能号
	if( nDataType==RECORDDATATYPE_HISTROY )
	{
		StrDeal.nFunctionID=SMT_SMARTFRONTSETTASKRESULT; //历史数据
	}
	else
	{
		StrDeal.nFunctionID=SMT_SMARTFRONTUPTIMEDATA;
	}
	//交易类型
	strcpy(StrDeal.sSaleType,"计时");
	//初始化cPack包
	if( !SMT_PackInit(nHandler) )								return false;
	//设置功能号
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
		
	SMT_SetValue(nHandler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);						//前置机注册号
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//动态密钥
	SMT_SetValue(nHandler,0,"sdate0",StrDeal.sRegNo);				//终端设备ID
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lInvoiceNo);			//交易流水号
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.nICCardCode);			//卡型代码
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.nWorkMode);				//工作模式代码
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lCardID);				//交易卡号
	SMT_SetValue(nHandler,0,"sstation0",StrDeal.sShowCardNo);		//显示卡号	
	sprintf(sDateStr,"20%s",StrDeal.sDate);
	SMT_SetValue(nHandler,0,"sdate1",sDateStr);				//交易日期
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//交易时间	
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.nTimerType);			//考勤类型
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.nInductorNo);			//感应头
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.nDutyFlag);			//下班标志
	SMT_SetValue(nHandler,0,"lvol11",StrDeal.lDealCode);			//交易标识	
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.lBatchNo);		//通讯版本
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//启动原因
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC	
	
	sprintf(sMsg,"上传记录到金仕达[终端号->%s 流水号->%05ld 交易卡号->%07ld 时间->%s%s %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lCardID,
		StrDeal.sDate,
		StrDeal.sTime,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		sprintf(sMsg," 失败,金仕达服务已经断开(%ld,%s)",nErrCode,sErrMsg);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if(SMT_RecvStatus(nHandler) )
	{
		sprintf(sMsg," 失败,金仕达服务已经断开(%ld,%s)",nErrCode,sErrMsg);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," 成功");
	m_pDlg->AddString(sMsg);
	if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sMsg);	
	return true;
}

/*=================================================================
* Function ID :  SMT_SaleRecordAnalysis
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  消费记录分析
*=================================================================*/
bool CInterface::SMT_SaleRecordAnalysis(char* ssData,STRSALERECORD &StrDeal)
{
	byte		  sBuffer[256],sStr[256];
	char		  sData[256];
	char		  sMachineCode[5];	
	DWORD		  nTime=0;
	int			  nDataType=0,nLen=0;
	
	memset(sStr,    0,sizeof sStr);
	memset(sData,   0,sizeof sData);	
	memset(sStr,	0,sizeof sStr);
	memset(sBuffer,	0,sizeof sBuffer);
	memset(&StrDeal,0,sizeof StrDeal);
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//得到数据类型
	nDataType   = atol(m_Data.GetColValues(sData));

	//数据体
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//数据体压缩
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//注册号
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//通信版本
	StrDeal.lVer=sBuffer[4];
	//钱包号
	StrDeal.lWalletcode=sBuffer[5]>>4;
	//启动原因
	StrDeal.lStartReason=sBuffer[5]&0x0F;
	//交易流水号
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//交易卡号
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//交易日期和时间 若时间全为FF则填0
	if( memcmp(sBuffer+11,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//日期
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
		//时间
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	}
	else
	{
		//日期
		strcpy(StrDeal.sDate,"00000000");
		//时间
		strcpy(StrDeal.sTime,"000000");
	}	
	//卡使用次数
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//入卡金额
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//出卡金额
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//交易标记
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[26],sBuffer[27]);

	//交易金额计算
	if( !memcmp(MACHINE_TYPE_0201,sMachineCode,2))//充值金额
	{
		if( StrDeal.lDealCode==0x30 )	//现金充值管理费
		{
			StrDeal.lTransMoney	=StrDeal.lOutMoney;
			StrDeal.lOutMoney	=StrDeal.lInMoney;			
			StrDeal.nFunctionID=SMT_SMARTFRONTMAGMONEY;
			//交易类型
			strcpy(StrDeal.sSaleType,"管理");
		}
		else //充值金额
		{
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			StrDeal.nFunctionID=SMT_SMARTFRONTADDMONEY;
			//交易类型
			strcpy(StrDeal.sSaleType,"充值");
		}
	}
	else //收费数据
	{
		//交易类型
		strcpy(StrDeal.sSaleType,"消费");
		//记录体中有搭伙费 此时时间为4字节
		if( StrDeal.lVer==0x82||StrDeal.lVer==0x83 )
		{
			nTime=m_Data.HexToInt(sBuffer+11,4);
			//日期
			sprintf(StrDeal.sDate,"%02ld%02ld%02ld",(nTime>>26)&0x3F,(nTime>>22)&0x0F,(nTime>>17)&0x1F);
			//时间
			sprintf(StrDeal.sTime,"%02ld%02ld%02ld",(nTime>>12)&0x1F,(nTime>>6)&0x3F,(nTime>>0)&0x3F);			
			//搭伙费
			StrDeal.lRateMoney=sBuffer[15]+sBuffer[16]*256;
			//交易金额(包括搭伙费)
			StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
			//交易类型
			strcpy(StrDeal.sSaleType,"搭伙");
		}
		else
		{
			StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
		}
		//
		if( StrDeal.lDealCode==0xFA||StrDeal.lDealCode==0xF0) //淋浴充值
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTCHANGEMONEY;
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			//交易类型
			strcpy(StrDeal.sSaleType,"充值");
		}
		else
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;
		}
	}
	return true;
}


/*=================================================================
* Function ID :  SMT_AssitantRecordAnalysis
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  补助记录分析
*=================================================================*/
bool CInterface::SMT_AssitantRecordAnalysis(char* ssData,STRSALERECORD &StrDeal)
{
	byte		  sBuffer[256],sStr[256];
	char		  sData[256];	
	char		  sMachineCode[5];		
	int			  nDataType=0,nLen=0;
	
	memset(sStr,    0,sizeof sStr);
	memset(sData,   0,sizeof sData);	
	memset(sStr,	0,sizeof sStr);
	memset(sBuffer,	0,sizeof sBuffer);
	memset(&StrDeal,0,sizeof StrDeal);
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//得到数据类型
	nDataType   = atol(m_Data.GetColValues(sData));

	//数据体
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//数据体压缩
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//注册号
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//通信版本
	StrDeal.lVer=sBuffer[4];
	//钱包号
	StrDeal.lWalletcode=sBuffer[26]&0x0F;
	//补助标志
	StrDeal.sAssitFlag=sBuffer[26];
	//启动原因
	StrDeal.lStartReason=sBuffer[5];
	//交易流水号
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//交易日期和时间 若时间全为FF则填0
	if( memcmp(sBuffer+8,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//日期
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[8],sBuffer[9],sBuffer[10]);
		//时间
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
	}
	else
	{
		//日期
		strcpy(StrDeal.sDate,"00000000");
		//时间
		strcpy(StrDeal.sTime,"000000");
	}	
	//交易卡号
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+21,3);
	//卡使用次数
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+24,2);
	//出卡金额
	sStr[2]=sBuffer[29];
	sStr[1]=sBuffer[30];
	sStr[0]=sBuffer[31];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//交易金额
	sStr[1]=sBuffer[27];
	sStr[0]=sBuffer[28];
	StrDeal.lTransMoney=m_Data.HexToInt(sStr,2);
	if( (sBuffer[26]&0x20)==0x00 ) //负补助
	{
		//入卡金额
		StrDeal.lInMoney=StrDeal.lOutMoney+StrDeal.lTransMoney;
		//交易金额
		StrDeal.lTransMoney=0-StrDeal.lTransMoney;
	}
	else
	{
		//入卡金额
		StrDeal.lInMoney=StrDeal.lOutMoney-StrDeal.lTransMoney;
	}
	//批号
	StrDeal.lBatchNo=m_Data.HexToInt(sBuffer+32,2);	
	//交易标记
	StrDeal.lDealCode=sBuffer[34];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[35],sBuffer[36]);
	//功能号
	StrDeal.nFunctionID=SMT_SMARTFRONTUPASSISDATA;
	//交易类型
	strcpy(StrDeal.sSaleType,"补助");
	return true;
}


/*=================================================================
* Function ID :  SMT_SaleRecordAnalysis_SongJiang
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  消费记录分析(松江大学城)
*=================================================================*/
bool CInterface::SMT_SaleRecordAnalysis_SongJiang(char* ssData,STRSALERECORD &StrDeal)
{
	byte		  sBuffer[256],sStr[256];
	char		  sData[256];	
	char		  sMachineCode[5];	
	DWORD		  nTime=0;
	int			  nDataType=0,nLen=0;
	
	memset(sStr,    0,sizeof sStr);
	memset(sData,   0,sizeof sData);	
	memset(sStr,	0,sizeof sStr);
	memset(sBuffer,	0,sizeof sBuffer);
	memset(&StrDeal,0,sizeof StrDeal);
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//得到数据类型
	nDataType   = atol(m_Data.GetColValues(sData));

	//数据体
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//数据体压缩
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//注册号
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//通信版本
	StrDeal.lVer=sBuffer[4];
	//钱包号
	StrDeal.lWalletcode=sBuffer[5]>>4;
	//启动原因
	StrDeal.lStartReason=sBuffer[5]&0x0F;
	//交易流水号
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//交易卡号
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//交易日期和时间 若时间全为FF则填0
	if( memcmp(sBuffer+11,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//日期
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
		//时间
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	}
	else
	{
		//日期
		strcpy(StrDeal.sDate,"00000000");
		//时间
		strcpy(StrDeal.sTime,"000000");
	}	
	//卡使用次数
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//入卡金额
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//出卡金额
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//交易标记
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[29],sBuffer[30]);

	//交易金额计算
	if( !memcmp(MACHINE_TYPE_0201,sMachineCode,2))
	{
		StrDeal.lOperatorID=m_Data.HexToInt(sBuffer+26,3);	
		if( StrDeal.lDealCode==0x30 )	//充值管理费记录
		{
			StrDeal.lTransMoney	=StrDeal.lOutMoney;
			StrDeal.lOutMoney	=StrDeal.lInMoney;			
			StrDeal.nFunctionID=SMT_SMARTFRONTMAGMONEY;
			//交易类型
			strcpy(StrDeal.sSaleType,"管理");
		}
		else //充值金额记录
		{
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			StrDeal.nFunctionID=SMT_SMARTFRONTADDMONEY;
			//交易类型smar
			strcpy(StrDeal.sSaleType,"充值");
		}
	}
	else //收费数据
	{
		//交易类型
		strcpy(StrDeal.sSaleType,"消费");
		//管理费
		sStr[2]=sBuffer[26];
		sStr[1]=sBuffer[27];
		sStr[0]=sBuffer[28];
		StrDeal.lRateMoney=m_Data.HexToInt(sStr,3);
		//交易金额(包括搭伙费)
		StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
		if( StrDeal.lDealCode==0xFA||StrDeal.lDealCode==0xF0) //淋浴冲正
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTCHANGEMONEY;
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			//交易类型
			strcpy(StrDeal.sSaleType,"充值");
		}
		else if( StrDeal.lDealCode==0xFE ) //消费冲正
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;
			StrDeal.lRateMoney=0-StrDeal.lRateMoney;
			//交易类型
			strcpy(StrDeal.sSaleType,"消费冲正");
		}
		else
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_SaleRecordAnalysis_GuangZhou
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  消费记录分析(广州大学城)
*=================================================================*/
bool CInterface::SMT_SaleRecordAnalysis_GuangZhou(XDHANDLE nHandler,int nTimeOut,int *nErrCode,char* sErrMsg,char* ssData,STRSALERECORD &StrDeal)
{
	byte		  sBuffer[256],sStr[256];
	char		  sData[256];	
	char		  sMachineCode[5],sMsg[256];	
	DWORD		  nTime=0;
	int			  nDataType=0,nLen=0;
	
	memset(sStr,    0,sizeof sStr);
	memset(sMsg,    0,sizeof sMsg);
	memset(sData,   0,sizeof sData);	
	memset(sStr,	0,sizeof sStr);
	memset(sBuffer,	0,sizeof sBuffer);
	memset(&StrDeal,0,sizeof StrDeal);
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//得到数据类型
	nDataType   = atol(m_Data.GetColValues(sData));

	//数据体
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//数据体压缩
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//注册号
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//通信版本
	StrDeal.lVer=sBuffer[4];
	//钱包号
	StrDeal.lWalletcode=0;
	//启动原因
	StrDeal.lStartReason=0;
	//餐次号
	StrDeal.nEatNum=sBuffer[5];
	//交易流水号
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//交易卡号
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//交易日期和时间
	//日期
	sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
	//时间
	sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	sprintf(StrDeal.sDealTime,"20%02ld-%02ld-%02ld %02ld:%02ld:%02ld",sBuffer[11],sBuffer[12],sBuffer[13],sBuffer[14],sBuffer[15],sBuffer[16]);
	
	//卡使用次数
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//入卡金额
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//出卡金额
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//交易标记
	StrDeal.lDealCode=sBuffer[25];	
	//商户编号  26 27
	sprintf(StrDeal.sShopID,"%02X%02X",sBuffer[26],sBuffer[27]);
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[28],sBuffer[29]);	
	//交易类型
	strcpy(StrDeal.sSaleType,"消费");
	//交易金额
	StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
	StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;

	SMT_SetValue(nHandler,0,"lvol1",StrDeal.lRateMoney);			//搭伙费
	SMT_SetValue(nHandler,0,"lcert_code",12);						//前置机注册号
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//动态密钥
	SMT_SetValue(nHandler,0,"sdate1",StrDeal.sRegNo);				//终端设备ID
	SMT_SetValue(nHandler,0,"lvol4",StrDeal.lInvoiceNo);			//交易流水号
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.lCardID);				//交易卡号
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.lWalletcode);			//交易钱包号
	SMT_SetValue(nHandler,0,"spost_code",StrDeal.sDate);			//交易日期
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//交易时间
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lTimes);				//卡片交易次数	
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.lTransMoney);			//交易金额
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.lInMoney);				//入卡值
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.lOutMoney);			//出卡值
	SMT_SetValue(nHandler,0,"lvol12",StrDeal.lDealCode);			//交易标识
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.sShopID);		//商户号
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//启动原因
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lOperatorID);			//操作员卡号
	
	//初始化cPack包
	if( !SMT_PackInit(nHandler) )								return false;
	//设置功能号
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
	sprintf(sMsg,"上传记录到金仕达[终端号->%s 流水号->%05ld 交易卡号->%ld 交易时间->%s 标识->%02X %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lCardID,
		StrDeal.sDealTime,
		StrDeal.lDealCode,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		strcat(sMsg," 失败,金仕达服务已经断开");
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if(SMT_RecvStatus(nHandler) )
	{
		strcat(sMsg," 失败,金仕达服务已经断开");
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," 成功");
	m_pDlg->AddString(sMsg);
	if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sMsg);	
	return true;
}

/*=================================================================
* Function ID :  SMT_UpDealRecord
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  上传交易数据
*=================================================================*/
bool CInterface::SMT_UpDealRecord(XDHANDLE& nHandler,char* ssData,int nTimeOut,int *nErrCode,char* sErrMsg)
{		
	char		  sMsg[1024],sData[256],sTemp[128];	
	char		  sMachineCode[5];	
	byte		  ucMacCode[3];
	DWORD		  nTime=0;
	int			  nDataType=0;
	STRSALERECORD StrDeal;
	int			  iRetCode=0;
	
	memset(sData,   0,sizeof sData);
	memset(sMsg,	0,sizeof sMsg);	
	memset(ucMacCode,0,sizeof ucMacCode);
	memset(&StrDeal,0,sizeof StrDeal);	
	memset(sMachineCode, 0,sizeof sMachineCode);

	strcpy(sData,ssData);
	//去掉记录中的日期
	m_Data.GetColValues(sData);
	//得机型代码
	strcpy(sMachineCode,m_Data.GetColValues(sData));	
	//得到数据类型
	nDataType=atol(m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,ucMacCode);
	//补助记录
	if( nDataType==ASSISTANTDATATYPE_FACE )
	{
		SMT_AssitantRecordAnalysis(ssData,StrDeal);		
		sprintf(sMsg,"补助标志->%02X 补助金额->%ld 入卡值->%ld 出卡值->%ld",
			(int)StrDeal.sAssitFlag,StrDeal.lTransMoney,StrDeal.lInMoney,StrDeal.lOutMoney);
		m_pDlg->WriteLog(sMsg);	
	}	//计时数据 20080506
	else if( nDataType==TIMEDATATYPE_FACE||(nDataType==RECORDDATATYPE_HISTROY&&!memcmp(ucMacCode,MACHINE_TYPE_0121,2)) ) 
	{

		return SMT_TimeRecordAnalysis(nHandler,nTimeOut,nErrCode,sErrMsg,ssData,StrDeal);
	}
	else //消费/充值记录
	{
		if( strlen(sData)>=63 )			//松江大学城 31字节+1字节回车
		{
			SMT_SaleRecordAnalysis_SongJiang(ssData,StrDeal);
		}
		else if( strlen(sData)>=61 )	//广州大学城 30字节+1字节回车
		{
			return SMT_SaleRecordAnalysis_GuangZhou(nHandler,nTimeOut,nErrCode,sErrMsg,ssData,StrDeal);	
		}
		else
		{
			SMT_SaleRecordAnalysis(ssData,StrDeal);
		}
	}
	
	//初始化cPack包
	if( !SMT_PackInit(nHandler) )								return false;
	//设置功能号
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
	
	SMT_SetValue(nHandler,0,"lvol1",StrDeal.lRateMoney);			//搭伙费
	SMT_SetValue(nHandler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//动态密钥
	SMT_SetValue(nHandler,0,"sdate1",StrDeal.sRegNo);				//终端设备ID
	SMT_SetValue(nHandler,0,"lvol4",StrDeal.lInvoiceNo);			//交易流水号
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.lCardID);				//交易卡号
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.lWalletcode);			//交易钱包号
	SMT_SetValue(nHandler,0,"spost_code",StrDeal.sDate);			//交易日期
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//交易时间
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lTimes);				//卡片交易次数
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.lTransMoney);			//交易金额
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.lInMoney);				//入卡值
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.lOutMoney);			//出卡值
	SMT_SetValue(nHandler,0,"lvol12",StrDeal.lDealCode);			//交易标识
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.lBatchNo);		//通讯版本
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//启动原因
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lOperatorID);			//操作员卡号
	
	sprintf(sMsg,"上传记录到金仕达[终端号->%s 流水号->%05ld 交易金额->%-8ld 标识->%02X %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lTransMoney,
		StrDeal.lDealCode,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		sprintf(sTemp," 失败,金仕达服务已经断开,ret[%d]",*nErrCode);
		strcat(sMsg,sTemp);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if((iRetCode=SMT_RecvStatus(nHandler))!=0)
	{
		sprintf(sTemp," 失败,金仕达服务已经断开,ret[%d]",iRetCode);
		strcat(sMsg,sTemp);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," 成功");
	m_pDlg->AddString(sMsg);
	if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sMsg);	
	return true;
}

/*=================================================================
* Function ID :  SMT_CheckWhetherAssistant
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  确认是否可领补助
*=================================================================*/
bool CInterface::SMT_CheckWhetherAssistant(byte *ucData,int *nMoney,int *nBatch)
{
	int			nErrCode=0;
	char		sErrMsg[128];
	int			nRowTotal=0;
	byte		buffer[64],sID[20];
	XDHANDLE	Handler=NULL;

	memset(sID,    0,sizeof sID);
	memset(buffer, 0,sizeof buffer);
	memset(sErrMsg,0,sizeof sErrMsg);

	memcpy(buffer,ucData,10);
	m_Data.BcdToAsc(buffer+5,4,sID);
	//获取句柄	
	if( (Handler=SMT_GetXDHandle())==NULL ) return false;
	//初始化cPack包
	if( !SMT_PackInit(Handler) )							
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTWHETHERASSIT) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(Handler,0,"lvol5",m_Data.HexToInt(buffer,3));				//卡号
	SMT_SetValue(Handler,0,"lvol3",m_Data.HexToInt(buffer+3,2));			//批次号
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//设备ID号
	SMT_SetValue(Handler,0,"lvol4",0);										//POS流水号
	SMT_SetValue(Handler,0,"lvol9",0);										//入卡值
	SMT_SetValue(Handler,0,"lvol6",0);										//钱包号
	SMT_SetValue(Handler,0,"lvol7",0);										//钱包流水号
	
	if( !SMT_SendAndRecvData(0,Handler,10000,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		SMT_SetXDHandleFree(Handler);
		return false;
	}	
	if( SMT_RecvStatus(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;	
	}
	if( !SMT_GetRowCount(Handler,&nRowTotal) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}	
	SMT_GetValue(Handler,0,"lvol9",&nRowTotal);			//金额
	*nMoney=nRowTotal;
	SMT_GetValue(Handler,0,"lvol3",&nRowTotal);			//批号
	*nBatch=nRowTotal;
	SMT_SetXDHandleFree(Handler);
	return true;
}

/*=================================================================
* Function ID :  SMT_RequestAddMoney
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  申请该设备的充值金额
*=================================================================*/
bool CInterface::SMT_RequestAddMoney(byte *ucDevice,int *nMoney,int *nBatch)
{
	int		nErrCode=0;
	char	sErrMsg[128];
	int		nRowTotal=0;
	byte	buffer[64],sID[20];
	XDHANDLE Handler=NULL;

	memset(sID,    0,sizeof sID);
	memset(buffer, 0,sizeof buffer);
	memset(sErrMsg,0,sizeof sErrMsg);

	memcpy(sID,ucDevice,4);
	//获取句柄	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"获取句柄无效");
		return false;
	}
	//初始化cPack包
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"初始化cPack包失败");
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(Handler,SMT_SETADDTOTALMONEY) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	m_Data.BcdToAsc(sID,4,sID);
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//设备ID号	
	if( !SMT_SendAndRecvData(0,Handler,10000,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	if( SMT_RecvStatus(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	if( !SMT_GetRowCount(Handler,&nRowTotal) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_GetValue(Handler,0,"lvol1",&nRowTotal);			//金额
	*nMoney=nRowTotal;
	SMT_GetValue(Handler,0,"lvol0",&nRowTotal);			//批号
	*nBatch=nRowTotal;
	SMT_SetXDHandleFree(Handler);
	return true;
}

/*=================================================================
* Function ID :  SMT_SmartFrontAddAuthTrue
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  联机充值授权卡确认
*=================================================================*/
bool CInterface::SMT_SmartFrontAddAuthTrue(byte *ucDevice, byte *ucData)
{
	int		nErrCode=0;
	char	sErrMsg[128];
	byte	sID[20];
	byte	ucCardID[20];
	long	nCardNo=0;
	XDHANDLE Handler=NULL;

	memset(sID,    0,sizeof sID);
	memset(sErrMsg,0,sizeof sErrMsg);
	memset(ucCardID,0,sizeof ucCardID);

	memcpy(sID,ucDevice,4);
	nCardNo=m_Data.HexToInt(ucData,3);
	m_Data.BcdToAsc(ucData+3,4,ucCardID);
	//获取句柄	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"获取句柄无效");
		return false;
	}
	//初始化cPack包
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"初始化cPack包失败");
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDAUTHTRUE) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	m_Data.BcdToAsc(sID,4,sID);
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//设备ID号	
	SMT_SetValue(Handler,0,"sdate0",(char*)ucCardID);						//物理卡号
	SMT_SetValue(Handler,0,"lvol5",(long)nCardNo);							//交易卡号	

	if( !SMT_SendAndRecvData(0,Handler,10000,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	if( SMT_RecvStatus(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetXDHandleFree(Handler);
	return true;
}

/*=================================================================
* Function ID :  SMT_SmartFrontAddRequest
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  联机充值请求
*=================================================================*/
bool CInterface::SMT_SmartFrontAddRequest(byte *ucDevice, byte *ucData)
{
	int		 nErrCode=0;
	char	 sErrMsg[128];
	byte	 sID[20],str[20];	
	int		 nRowTotal=0;
	XDHANDLE Handler=NULL;
	STRSALERECORD  StrRecod;

	memset(sID,     0,sizeof sID);
	memset(str,     0,sizeof str);
	memset(sErrMsg, 0,sizeof sErrMsg);	
	memset(&StrRecod,0,sizeof StrRecod);
	
	m_Data.BcdToAsc(ucDevice,4,(byte*)StrRecod.sRegNo);//设备ID
	StrRecod.lCardID=m_Data.HexToInt(ucData,3); //交易卡号
	StrRecod.lWalletcode=m_Data.HexToInt(ucData+3,1); //钱包号
	StrRecod.lTimes=m_Data.HexToInt(ucData+4,2);		//钱包流水号
	str[0]=ucData[8];
	str[1]=ucData[7];
	str[2]=ucData[6];
	StrRecod.lTransMoney=m_Data.HexToInt(str,3);		//交易金额
	str[0]=ucData[11];
	str[1]=ucData[10];
	str[2]=ucData[8];
	StrRecod.lInMoney=m_Data.HexToInt(str,3);		//入卡值
	StrRecod.lInvoiceNo=m_Data.HexToInt(ucData+12,2); //流水号
	//日期
	sprintf(StrRecod.sDate,"%02ld%02ld%02ld",ucData[14],ucData[14],ucData[16]);
	//时间
	sprintf(StrRecod.sTime,"%02ld%02ld%02ld",ucData[17],ucData[18],ucData[19]);
	//操作员卡号
	StrRecod.lOperatorID=m_Data.HexToInt(ucData+20,3);
	//交易标志
	StrRecod.lDealCode=ucData[23];
	
	
	//获取句柄	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"获取句柄无效");
		return false;
	}
	//初始化cPack包
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"初始化cPack包失败");
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDREQUEST) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(Handler,0,"sdate1",(char*)StrRecod.sRegNo);				//设备ID号		
	SMT_SetValue(Handler,0,"lvol5",(long)StrRecod.lCardID);					//交易卡号
	SMT_SetValue(Handler,0,"lvol6",(long)StrRecod.lWalletcode);				//钱包号
	SMT_SetValue(Handler,0,"lvol7",(long)StrRecod.lTimes);					//钱包流水号
	SMT_SetValue(Handler,0,"lvol8",(long)StrRecod.lTransMoney);				//交易金额
	SMT_SetValue(Handler,0,"lvol9",(long)StrRecod.lInMoney);				//入卡金额
	SMT_SetValue(Handler,0,"lvol4",(long)StrRecod.lInvoiceNo);				//POS流水号
	SMT_SetValue(Handler,0,"spost_code",(char*)StrRecod.sDate);				//发生日期
	SMT_SetValue(Handler,0,"spost_code2",(char*)StrRecod.sTime);			//发生时间
	SMT_SetValue(Handler,0,"lvol3",(long)StrRecod.lOperatorID);				//授权卡号
	SMT_SetValue(Handler,0,"lvol12",(long)StrRecod.lDealCode);				//标志
	if( !SMT_SendAndRecvData(0,Handler,10000,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	if( SMT_RecvStatus(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}

	if( !SMT_GetRowCount(Handler,&nRowTotal) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	memset(str,0,sizeof str);	
	SMT_GetValue(Handler,0,"lvol5",&nRowTotal);			//卡号
	m_Data.IntToHex(nRowTotal,(char*)str);
	memcpy(ucData,str+1,3);
	SMT_GetValue(Handler,0,"lvol10",&nRowTotal);		//出卡值	
	memset(str,0,sizeof str);
	m_Data.IntToHex(nRowTotal,(char*)str);
	ucData[3]=str[3];
	ucData[4]=str[2];
	ucData[5]=str[1];
	SMT_SetXDHandleFree(Handler);
	return true;
}

/*=================================================================
* Function ID :  SMT_SmartFrontAddRequestCancel
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true 有 false无
* Description :  
* Notice	   :  联机充值冲正
*=================================================================*/
bool CInterface::SMT_SmartFrontAddRequestCancel(byte *ucDevice, byte *ucData)
{
	int		 nErrCode=0;
	char	 sErrMsg[128];
	byte	 sID[20],str[20];	
	int		 nRowTotal=0;
	XDHANDLE Handler=NULL;
	STRSALERECORD  StrRecod;
	
	memset(sID,      0,sizeof sID);
	memset(str,      0,sizeof str);
	memset(sErrMsg,  0,sizeof sErrMsg);	
	memset(&StrRecod,0,sizeof StrRecod);	
	
	m_Data.BcdToAsc(ucDevice,4,(byte*)StrRecod.sRegNo);  //设备ID
	StrRecod.lCardID    =m_Data.HexToInt(ucData,3);      //交易卡号
	StrRecod.lWalletcode=m_Data.HexToInt(ucData+3,1);    //钱包号
	StrRecod.lInvoiceNo =m_Data.HexToInt(ucData+4,2);    //POS流水号
	StrRecod.lBatchNo   =m_Data.HexToInt(ucData+6,2);    //原POS流水号
	//日期
	sprintf(StrRecod.sDate,"%02ld%02ld%02ld",ucData[8],ucData[9],ucData[10]);
	//时间
	sprintf(StrRecod.sTime,"%02ld%02ld%02ld",ucData[11],ucData[12],ucData[13]);	
	
	//获取句柄	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"获取句柄无效");
		return false;
	}
	//初始化cPack包
	if( !SMT_PackInit(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"初始化cPack包失败");
		return false;
	}
	//设置功能号
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDREQUESTCANCEL) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//前置机注册号
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//动态密钥
	SMT_SetValue(Handler,0,"sdate1",(char*)StrRecod.sRegNo);				//设备ID号		
	SMT_SetValue(Handler,0,"lvol5",(long)StrRecod.lCardID);					//交易卡号
	SMT_SetValue(Handler,0,"lvol6",(long)StrRecod.lWalletcode);				//钱包号
	SMT_SetValue(Handler,0,"lvol4",(long)StrRecod.lInvoiceNo);				//POS流水号
	SMT_SetValue(Handler,0,"lvol3",(long)StrRecod.lBatchNo);				//原POS流水号	
	SMT_SetValue(Handler,0,"spost_code",(char*)StrRecod.sDate);				//发生日期
	SMT_SetValue(Handler,0,"spost_code2",(char*)StrRecod.sTime);			//发生时间
	if( !SMT_SendAndRecvData(0,Handler,10000,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	if( SMT_RecvStatus(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	
	if( !SMT_GetRowCount(Handler,&nRowTotal) )
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	memset(str,0,sizeof str);	
	SMT_GetValue(Handler,0,"lvol5",&nRowTotal);			//卡号
	m_Data.IntToHex(nRowTotal,(char*)str);
	memcpy(ucData,str+1,3);
	SMT_GetValue(Handler,0,"lvol10",&nRowTotal);		//出卡值	
	memset(str,0,sizeof str);
	m_Data.IntToHex(nRowTotal,(char*)str);
	ucData[3]=str[3];
	ucData[4]=str[2];
	ucData[5]=str[1];
	SMT_SetXDHandleFree(Handler);
	return true;
}