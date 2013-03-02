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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��ʼ��ϵͳ�ӿڣ��ú�����ϵͳ��ֻ�ܵ���һ��
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
	//�򿪵�����־
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
* Input       :  ��cPack����л�ȡһ����Ч�ľ��
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : �ɹ����ؾ��  ʧ�ܷ��ؿ�
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
* Input       :  ��cPack����л�ȡһ����Ч�ľ��
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : �ɹ����ؾ��  ʧ�ܷ��ؿ�
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
* Input       :  ��cPack����л�ȡһ����Ч�ľ��
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  : �ɹ����ؾ��  ʧ�ܷ��ؿ�
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���жϺ�������
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ͷŴ����
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �����ѹ����ǰӦ�ȵ��ø÷���
* Notice	   :  
*					
*=================================================================*/
bool CInterface::SMT_PackInit(XDHANDLE nHandle)
{
	return ResetPackHandle(nHandle);
}

/*=================================================================
* Function ID :  SetRequestFunID
* Input       :  int nFunId ҵ��Ĺ��ܺ�
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �����ܺŴ������
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ����
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ������
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ�ַ�
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ����
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ������
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
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	  :  ֵΪ�ַ�
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
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���
* Notice	   :  ֵΪ�ַ�
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
		strcpy(errmsg,"���ý��˴�CallRequest()ʱ���쳣!!");
		return false;
	}
}

/*=================================================================
* Function ID :  RecvStatus
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  0�ɹ� ��0ʧ��
* Description :  
* Notice	   :  �õ����˴ﷵ������ʱ��״̬
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
* Return	  :  0�ɹ� ��0ʧ��
* Description :  
* Notice	  :  ��ȡһ�����е�����
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �Ƿ��к�����
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �õ���һ��
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �ӽ��˴��ȡ����
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
		if(nCurrTime-nLastCollectTime>g_IniFilePara.lCollForceTime*60*1000) // 5 ����
		{
			if(nCurrTime - nLastCollectTime > (g_IniFilePara.lCollForceTime+g_IniFilePara.lCollForceLastTime)*60*1000)
			{
				nLastCollectTime = nCurrTime;
				m_pDlg->AddString("ǿ�Ʋɼ���ˮ��");
			}
		}
		else
		{
#if 0
			for( j=0; j<g_nTotalCount; j++ )
			{
				//ˮ���豸�����к�����У��
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
				SMT_GetDeviceBlackCardTask(g_VSmartPos[j]);	//��ȡ����������
				if( !g_StartFlag) break;	
				if( GetTickCount()-nStartTime>20*60*1000)	//ÿ20�����ϴ�һ���豸״̬�����˴�
				{
					m_pDlg->WriteLog("��ʼ����˴��ϴ��豸״̬");
					SMT_UpDeviceStatus();
					nStartTime=GetTickCount();
				}
				Sleep(50);
				SMT_ReportTaskResult();		//���������͸����˴�			
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
					if(SocketSmart->m_SmartPos[i].nCommunicationStatus == 0xFF) // �豸��ͨ
						continue;
					SMT_GetDeviceBlackCardTask(SocketSmart->m_SmartPos[i]);	//��ȡ����������
					if( !g_StartFlag) break;	
					if( GetTickCount()-nStartTime>20*60*1000)	//ÿ20�����ϴ�һ���豸״̬�����˴�
					{
						m_pDlg->WriteLog("��ʼ����˴��ϴ��豸״̬");
						SMT_UpDeviceStatus();
						nStartTime=GetTickCount();
					}
					Sleep(50);
					SMT_ReportTaskResult();		//���������͸����˴�		
				}
			}
#endif
		}
		if( GetTickCount()-nStartTime>20*60*1000)	//ÿ20�����ϴ�һ���豸״̬�����˴�
		{		
			m_pDlg->WriteLog("��ʼ����˴��ϴ��豸״̬");
			SMT_UpDeviceStatus();
			nStartTime=GetTickCount();
			Sleep(10000);
		}
		Sleep(2000);
		i=0;
		while( i++<3 )
		{
			if( !g_StartFlag)	break;
			SMT_ReportTaskResult();		//���������͸����˴�		
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
			//m_pDlg->AddString("��ʼ����˴��ȡ�豸����");
#if 0
			if(GetTickCount()-nTaskTime>60*1000)
			{
				j = 0;
				for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
				{
					// ������
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
							// �豸��ͨ
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
				// ������
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
						// �豸��ͨ
						//if(SocketSmart->m_SmartPos[i].nCommunicationStatus == 0xFF)
						//	continue;
						// ����豸�ϴ���ȡ�����񣬱����ٴδӺ�̨��ȡ����
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
			sprintf(szMsg,"��ʼ����˴��ȡ�豸������ɣ���[%d]",j);
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
* Return	  :  true �� false��
* Description :  
* Notice	  :  ����˴ﱨ��������
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

	//��ȡ������
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
		//��ʼ��cPack��
		if( !SMT_PackInit(m_handler[0].handler) )	return false;	
		//���ù��ܺ�		
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
		
		SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);		//ǰ�û�ע���
		SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);					//��̬��Կ	
		SMT_SetValue(m_handler[0].handler,0,"lvol1",(int)mTaskResult.Pos.nMessageID);			//��ϢID��
		if( mTaskResult.ResultStatus )
		{
			SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)0);								//������
			SMT_SetValue(m_handler[0].handler,0,"vsmess","�ɹ�"); // �ɹ���Ϣ
		}
		else
		{
			if( mTaskResult.nTaskResultStatus==0 ) mTaskResult.nTaskResultStatus=6;
			SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)mTaskResult.nTaskResultStatus);				//������
			SMT_SetValue(m_handler[0].handler,0,"vsmess",mTaskResult.ucErrMsg);	//���ش�����Ϣ
		}
		//����Ӧ�Ĺ��ܺŵ���Ӧ���ݽ��д��
		switch( mTaskResult.nAcction )
		{
			case SMT_SMARTFRONTADDBLACKLIST://���Ӻ�����
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //�豸ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				memset(sValue,0,sizeof sValue);
				strcpy(sValue,(char*)mTaskResult.Pos.sMemo);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);//�汾
				sprintf(sErrMsg,"[����] ���Ӻ����� ���˴����� �豸ID->%.8X �汾->%s ����->%ld MsgID->%ld",
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTDELBLACKLIST://ɾ��������
				memset(sValue,0,sizeof sValue);
				strcpy(sValue,(char*)mTaskResult.Pos.sMemo);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);	//�汾
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //�豸ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				sprintf(sErrMsg,"[����] ɾ�������� ���˴����� �豸ID->%.8X �汾->%s ����->%ld MsgID->%ld",								
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTGETTIMEWHITELISTVER: // ���ذ��������汾
				memset(sValue,0,sizeof sValue);
				strncpy(sValue,(char*)mTaskResult.Pos.sMemo,12);
				SMT_SetValue(m_handler[0].handler,0,"sserial0",sValue);	//�汾
				SMT_SetValue(m_handler[0].handler,0,"lvol3",(int)mTaskResult.Pos.nMemo); // ����
				m_Data.BcdToAsc(mTaskResult.Pos.ucpIDNo,4,(byte*)sDeviceID); //�豸ID
				SMT_SetValue(m_handler[0].handler,0,"scert_no",sDeviceID);	
				sprintf(sErrMsg,"[����] ������ ���˴����� �豸ID->%.8X �汾->%s ����->%ld MsgID->%ld",								
					m_Data.HexToInt(mTaskResult.Pos.ucpIDNo,4),					
					mTaskResult.Pos.sMemo,
					mTaskResult.Pos.nMemo,
					mTaskResult.Pos.nMessageID);
				if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,sDeviceID);
				break;
			case SMT_SMARTFRONTUPMAINPARA:	//�ϴ��豸������
				break;
			case SMT_SMARTFRONTGETCLOCK:	//�ϴ�ʱ��
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
			case SMT_SMARTFRONTMANAGERATE: //�´�����ѱ���
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
* Return	  :  true �� false��
* Description :  
* Notice	  :  �ӽ��˴��ȡ����������
*=================================================================*/
bool CInterface::SMT_GetDeviceBlackCardTask(SMARTPOS cPos)
{
	DWORD	nTimeOut=1000;	//��ʱʱ��
	int		nErrCode=0;		//�������
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
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTGETBLACKCARD) )	
	{
		return false;
	}
	
	m_Data.BcdToAsc(cPos.ucpIDNo,4,(byte*)cDeviceID);
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(m_handler[0].handler,0,"scert_no",cDeviceID);							//����ID��
	SMT_SetValue(m_handler[0].handler,0,"lvol1",(long)1);								//��ȡ����������
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ǰ��ͨѶ����˴���������ʱ,���˴��������Ѿ��Ͽ�[ ret=%ld,sErrmsg=%s]",nErrCode,sErrMsg);
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
			m_pDlg->AddString("ǰ��ͨѶ����˴��������������ʱ,���˴��֮û������......");
			nStartTime=GetTickCount();
		}
		return false;
	}
	else
	{
		//0�����1��ɾ��
		SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nFlag);				//��ɾ��־	
		SMT_GetValue(m_handler[0].handler,nRow,"scert_no",cDeviceID,sizeof(cDeviceID));
		nValue=0;
		memset(sValue,0,sizeof sValue);
		SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nValue); //����
		SMT_GetValue(m_handler[0].handler,nRow,"sname",sValue,sizeof(sValue)); //�汾
		m_Data.trim(sValue);
		m_Data.trim(cDeviceID);
		sprintf(sErrMsg,"ǰ�û�ȡ�����˴����������[���ܺ�->%ld �豸ID->%s ����->%ld �汾->%s MsgID->%ld]",
			SMT_SMARTFRONTGETBLACKCARD,
			cDeviceID,
			nValue,
			sValue,
			cPos.nMessageID);
		//�ж��Ƿ�ͬһ�豸
		m_Data.AscToBcd((byte*)cDeviceID,8,ucID);
		if( memcmp(cPos.ucpIDNo,ucID,4) ) //add by dj 20071009 ���Ǹ��豸������������
		{
			return false; //�õ��Ĳ���ͬһ�豸������
		}
		m_pDlg->AddString(sErrMsg);
	}
	memset(cDeviceID,0,sizeof cDeviceID);
	memset(sValue,   0,sizeof sValue);
		
	SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nValue);						//����
	SMT_GetValue(m_handler[0].handler,nRow,"sname",sValue,sizeof(sValue));			//�汾
	SMT_GetValue(m_handler[0].handler,nRow,"scert_no",cDeviceID,sizeof(cDeviceID)); //�豸ID	
	m_Data.trim(sValue);
	mPack.nMemo=nValue;				//����
	memcpy(mPack.sMemo,sValue,12);  //�汾
	m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
	//����CRC
	sprintf((char*)sStr,"%ld%s",mPack.nMemo,(char*)mPack.sMemo);			
	m_Data.CRC_CCITT(strlen((char*)sStr),sStr,mPack.ucSndData);	
	mPack.nSndDataLen=4;
	mPack.nMessageID=cPos.nMessageID;
	switch(nFlag)
	{
		case 0:	//���Ӻ�����						
			mPack.nAcction=SMT_SMARTFRONTADDBLACKLIST;
			mPack.nTaskCode=SMT_SMARTFRONTADDBLACKLIST;			
			mPack.nFlag=1;
			mPack.ucCmd=0xA4;			
			sprintf(sErrMsg,"[��ȡ] ���Ӻ����� ���˴����� �豸ID->%s �汾->%s ����->%ld MsgID->%ld ",
				cDeviceID,
				mPack.sMemo,
				nValue,
				mPack.nMessageID);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,cDeviceID);
			bFlag=false;
			break;
		case 1:	//ɾ��������
			mPack.nAcction=SMT_SMARTFRONTDELBLACKLIST;
			mPack.nTaskCode=SMT_SMARTFRONTDELBLACKLIST;			
			mPack.nFlag=1;
			mPack.ucCmd=0xA5;
			sprintf(sErrMsg,"[��ȡ] ɾ�������� ���˴����� �豸ID->%s �汾->%s ����->%ld MsgID->%ld ",cDeviceID,mPack.sMemo,nValue,mPack.nMessageID);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(sErrMsg,cDeviceID);	
			bFlag=false;
			break;
		default:
			return false;	
	}
	//����·�в�������
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
* Return	  :  true �� false��
* Description :  
* Notice	  :  �ӽ��˴��ȡ����
*=================================================================*/
bool CInterface::SMT_GetDeviceTask(const char *regno)
{
	DWORD	nTimeOut=1000;	//��ʱʱ��
	int		nErrCode=0;		//�������
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
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTGETTASK) )	
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(m_handler[0].handler,0,"sdate0",(char*)regno);  // �����豸ID
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ǰ��ͨѶ����˴���������ʱ,���˴��������Ѿ��Ͽ�[ ret=%ld,sErrmsg=%s]",nErrCode,sErrMsg);
		m_pDlg->AddString(m_szText);
		m_pDlg->WriteLog(m_szText);
		Sleep(2000);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )				return false;	
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) ) return false;
	//�õ�����ID�� nTaskID
	SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nTaskID);
	SMT_GetValue(m_handler[0].handler,nRow,"lvol1",&mPack.nMessageID); //��ϢID��
	SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
	if( mPack.nMessageID<=0 )
	{
		if( GetTickCount()-nStartTime>5*1000 )
		{		
			m_pDlg->AddString("ǰ��ͨѶ����˴���������ʱ,���˴��֮û������......");
			nStartTime=GetTickCount();
		}
		//Sleep(1000);
		return false;
	}
	else
	{
		nValue=0;
		memset(sValue,0,sizeof sValue);
		SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nValue); //����
		SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue)); //�汾
		m_Data.trim(sValue);
		m_Data.trim(cDeviceID);
		sprintf(sErrMsg,"ǰ�û�ȡ�����˴�����[���ܺ�->%ld �豸ID->%s ����->%ld �汾->%s ��ϢID->%ld]",
			nTaskID,
			cDeviceID,
			nValue,
			sValue,
			mPack.nMessageID);
		//m_pDlg->AddString(sErrMsg);		
	}
	//���ݹ��ܽ��д���
	switch(nTaskID)
	{
		case SMT_SMARTFRONTASSISTANTLISTLOAD:	//wlport���������´�
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			//����
			SMT_GetValue(m_handler[0].handler,nRow,"lvol10",&nValue);
			mPack.ucSndData[0]=nValue>>16;
			mPack.ucSndData[1]=nValue>>8;
			mPack.ucSndData[2]=nValue;
			//��������
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[3]=nValue>>8;
			mPack.ucSndData[4]=nValue;			
			//�������
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			//������־
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
		case SMT_SMARTFRONTSETCLOCK:	//�´�ʱ��
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nSndDataLen=0;
			mPack.nAcction=SMT_SMARTFRONTSETCLOCK;
			mPack.nTaskCode=SMT_SETCLOCK;
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			break;
		case SMT_SMARTFRONTGETCLOCK:		//�ϴ�ʱ��
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nSndDataLen= 0;
			mPack.nAcction   = SMT_SMARTFRONTGETCLOCK;
			mPack.nTaskCode  = SMT_GETCLOCK;			
			mPack.nFlag		 = nDeviceFlag;
			mPack.nFlag		 = 1;
			break;
		case SMT_SMARTFRONTMANAGERATE:		//�´�����ѱ���
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
		case SMT_SMARTFRONTPWDMONEY:		//�´��������ý��(����)
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
		case SMT_SMARTFRONTDAYMONEY:		//���ۼ������޶�
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
		case SMT_SMARTFRONTMANAGEPWD:		//�����ն˹���Ա����
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
		case SMT_SMARTFRONTSALEHISTROY:		//�ɼ�������ʷ����
		case SMT_SMARTFRONTADDHISTROY:		//�ɼ���ֵ��ʷ����
		case SMT_SMARTFRONTTIMEHISTROY:		//�ɼ���ʱ��ʷ����
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));			
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);  //��ʼ��ˮ��
			mPack.ucSndData[0]=nValue>>8;
			mPack.ucSndData[1]=nValue;
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);  //������ˮ��
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
				SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);  //��ˮ��
				mPack.ucSndData[0]=nValue>>8;
				mPack.ucSndData[1]=nValue;
				mPack.ucSndData[2]=mPack.ucSndData[0];
				mPack.ucSndData[3]=mPack.ucSndData[1];
			}
			break;
		case SMT_SMARTFRONTADDBLACKLIST:	//���Ӻ�����
			return true;
		case SMT_SMARTFRONTDELBLACKLIST:	//ɾ��������
			return true;		
		case SMT_SMARTFRONTBROADBLACK:		//�㲥������
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nCardNo);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);
			SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			if( nFlag == 1 )
			{
				g_CSmartBlackMemoryOper.SMT_DeleteBlackCard(nCardNo); //ɾ��
				//���ڹ㲥�շѻ�ʹ��
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
				g_CSmartBlackMemoryOper.SMT_InsertBlackCard(nCardNo); //��ʧ	
				//���ڹ㲥�շѻ�ʹ��
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
			//����㲥����Ľ��
			SMARTTASKRESULT mTaskResult;
			memset(&mTaskResult,0,sizeof mTaskResult);			
			mTaskResult.ResultStatus     = true;	
			mTaskResult.nAcction	     = mPack.nAcction;
			mTaskResult.nTaskResultStatus= 0;			
			memcpy(&mTaskResult.Pos,&mPack,sizeof(SMARTCOMMPACK));
			m_pDlg->SMT_InsertOneTaskResult(mTaskResult);
			break;
		case SMT_SMARTFRONTOPENORCLOSE: //�����򳣹�
			//�豸ID
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); 
			//���ر�־ 0-����1-����2-�ָ�����
			SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nAcction=SMT_SMARTFRONTOPENORCLOSE;
			mPack.nSndDataLen=0;			//û��������
			mPack.nFlag=1;
			if( nFlag==0 )					//����
			{
				mPack.nTaskCode=SMT_OPENCTRL;
			}
			else if( nFlag==1||nFlag==2 )	//���ء��ָ�����
			{
				mPack.nTaskCode=SMT_CLOSECTRL;
			}
			break;
		case SMT_SMARTFRONTCARDTYPE:		//�����ն���չ����
			{
				char sBuffer[512];
				memset(sBuffer,0,sizeof sBuffer);	
				memset(cDeviceID,0,sizeof cDeviceID);
				SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
				SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
				SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
				m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
				SMT_GetValue(m_handler[0].handler,nRow,"vsvarstr0",sBuffer,sizeof(sBuffer));				
				mPack.nAcction =SMT_SMARTFRONTCARDTYPE;
				mPack.nTaskCode=SMT_SMARTFRONTCARDTYPE;					
				mPack.nFlag=1;
				mPack.ucCmd=0x67;
				if( !SMT_GetDeviceCardType(&mPack,sBuffer) ) return false; //ʧ��
			}
			break;
		case SMT_SMARTFRONTGETRATE:		//��ȡ�豸����
			memset(cDeviceID,0,sizeof cDeviceID);
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);
			mPack.nAcction=SMT_SMARTFRONTGETRATE;
			mPack.nTaskCode=nFunTaskID;
			mPack.nFlag=nDeviceFlag;
			mPack.nFlag=1;
			if( !SMT_GetDeviceOneRate(&mPack) ) return false; //ʧ��
			break;
		case SMT_SMARTFRONTWARNMONEY:	//�´��������
			{
				int	nMoney=0;
				memset(cDeviceID,0,sizeof cDeviceID);
				SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID));
				SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
				SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nMoney);  //���
				SMT_GetValue(m_handler[0].handler,nRow,"lvol4",&nFlag);  //��ʽ	
				mPack.nAcction=SMT_SMARTFRONTWARNMONEY;
				mPack.ucSndData[0]=nMoney;
				mPack.ucSndData[1]=nMoney>>8;
				mPack.nSndDataLen=2;
				mPack.nFlag      =1;
				mPack.nTaskCode=SMT_SETWARMMONEY;
				if( nFlag==1 ) { bFlag=true; }//�㲥
				else {bFlag=false;m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);}
			}
			break;
		case SMT_SMARTFRONTGETMAINPARA:		//ǰ�û�ȡ���˴��豸������
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);		
			//���뿪��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[0]=nValue;
			//�շѷ�ʽ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol12",&nValue);
			mPack.ucSndData[1]=nValue;
			//��Ƭ���ʹ�ô���
			SMT_GetValue(m_handler[0].handler,nRow,"lvol7",&nValue);
			mPack.ucSndData[2]=nValue>>8;
			mPack.ucSndData[3]=nValue;
			//����������� 2
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbankname",sValue,sizeof(sValue)); 
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,4,mPack.ucSndData+4);
			//Ǯ���������޶� 3 
			SMT_GetValue(m_handler[0].handler,nRow,"lvol8",&nValue);
			mPack.ucSndData[6]=nValue;
			mPack.ucSndData[7]=nValue>>8;
			mPack.ucSndData[8]=nValue>>16;
			//ÿ�δ�ȡ���޶� 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol11",&nValue);
			mPack.ucSndData[9]=nValue;
			mPack.ucSndData[10]=nValue>>8;
			mPack.ucSndData[11]=nValue>>16;
			//Ǯ���������޶� 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol9",&nValue);
			mPack.ucSndData[12]=nValue;
			mPack.ucSndData[13]=nValue>>8;
			mPack.ucSndData[14]=nValue>>16;
			//��ֵ�շ�ʹ�ö�ֵ�� 3
			SMT_GetValue(m_handler[0].handler,nRow,"lvol10",&nValue);
			mPack.ucSndData[15]=nValue;
			mPack.ucSndData[16]=nValue>>8;
			mPack.ucSndData[17]=nValue>>16;
			//��ǿ����(��������) 1 scurrency_type2
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"scurrency_type2",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			mPack.ucSndData[18]=atol(sValue);
			//ͨ�Ų�����  1	 
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[19]=nValue;
			//Ǯ������(����)  1
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sbranch_code0",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			mPack.ucSndData[20]=atol(sValue);
			//����������Կ 4
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd2",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue,8,mPack.ucSndData+21);
			//ϵͳ���� 4
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd",sValue,sizeof(sValue));
			m_Data.trim(sValue);
			m_Data.AscToBcd((byte*)sValue+4,4,mPack.ucSndData+25);
			//����ʹ�ÿ���(���ṹ) 
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
		//��ʱ���´�������
		case SMT_SMARTFRONTGETTIMEMAINPARA:
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);		
			//���뿪��			
			mPack.ucSndData[0]=0x01;
			//����ģʽ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			mPack.ucSndData[1]=nValue;
			//����ʱ��1
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[2]=nValue;
			//����ʱ��2
			SMT_GetValue(m_handler[0].handler,nRow,"lvol6",&nValue);
			mPack.ucSndData[3]=nValue;
			//������
			mPack.ucSndData[4]=0xFF;
			mPack.ucSndData[5]=0xFF;
			//ͨ��ģʽ
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus0",sValue,sizeof(sValue));
			mPack.ucSndData[6]=atol(sValue);
			//�洢��ʽ
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus1",sValue,sizeof(sValue));
			mPack.ucSndData[7]=atol(sValue);
			//��Ӧͷ
			mPack.ucSndData[8]=0x01;
			//��������
			mPack.ucSndData[9] =0x00;
			mPack.ucSndData[10]=0x00;
			mPack.ucSndData[11]=0x00;
			//ϵͳ����Ա����
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"semp_pwd",sValue,sizeof(sValue));
			m_Data.AscToBcd((byte*)sValue,6,mPack.ucSndData+12);
			//����
			mPack.ucSndData[15]=0x00;
			mPack.ucSndData[16]=0x00;
			mPack.ucSndData[17]=0x00;
			//��ʾ
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sstatus2",sValue,sizeof(sValue));
			mPack.ucSndData[18]=atol(sValue);
			//������
			SMT_GetValue(m_handler[0].handler,nRow,"lvol7",&nValue);
			mPack.ucSndData[19]=nValue;
			mPack.ucSndData[20]=0x00;
			mPack.ucSndData[21]=0x00;
			mPack.ucSndData[22]=0x00;
			mPack.ucSndData[23]=0x00;
			mPack.ucSndData[24]=0x00;
			mPack.ucSndData[25]=0x00;
			mPack.ucSndData[26]=0x00;
			//���Ͳ���
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
		case SMT_SMARTFRONTGETTIMESEGMENT: //��ʱ��ʱ���
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			//����
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			mPack.ucSndData[0]=nValue;
			//ʱ�������
			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			mPack.ucSndData[1]=nValue;
			//��1��ʱ���	
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
			//��2��ʱ���	
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
			//��3��ʱ���	
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
			//��4��ʱ���	
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
			//��5��ʱ���	
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
			//��6��ʱ���	
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
			//��7��ʱ���	
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
			//��8��ʱ���	
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
		case SMT_SMARTFRONTGETTIMEHOLIDAY: //��ʱ�豸�ڼ���
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			//�ڼ���
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
		case SMT_SMARTFRONTGETTIMEWHITEVER:	//��ʱ�豸�������汾
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
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
		case SMT_SMARTFRONTGETTIMEWHITELIST: //�´�/ɾ��������
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	
			
			mPack.ucSndData[0]=0x01;
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue); // ����
			mPack.nMemo = nValue; // ���濨��
			memcpy(mPack.ucSndData+1,m_Data.IntToHex(nValue,sValue)+1,3);

			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			if( nValue==0)
			{
				mPack.nSndDataLen=4;
				mPack.ucCmd		=0xAB; // �´�����
			}
			else if( nValue==1)
			{
				mPack.nSndDataLen=4;  // ɾ������
				mPack.ucCmd		=0xAC;
			}
			else if( nValue==2)
			{
				mPack.nSndDataLen=0;
				mPack.ucCmd		=0xAD; // ɾ�����а�����
			}
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMEWHITELIST;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMEWHITELIST;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;			
			break;			
		case SMT_SMARTFRONTGETTIMEWHITELISTVER: //�´����ż��汾
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);	

			mPack.ucSndData[0]=0x01;
			//����
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			memcpy(mPack.ucSndData+1,m_Data.IntToHex(nValue,sValue)+1,3);
			mPack.nMemo = nValue;
			//�汾
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"sserial0",sValue,sizeof(sValue)-1);
			m_Data.AscToBcd((byte*)sValue,12,mPack.ucSndData+4);
			memcpy(mPack.sMemo,sValue,12);

			SMT_GetValue(m_handler[0].handler,nRow,"lvol5",&nValue);
			if( nValue==0)  //����
			{
				mPack.nSndDataLen=4+6;
				mPack.ucCmd		=0xAB;
			}
			else if( nValue==1) //ɾ��
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
		case SMT_SMARTFRONTGETTIMESWITCH:	//���ؿ���
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
			m_Data.AscToBcd((byte*)cDeviceID,8,mPack.ucpIDNo);				
			
			//�굼
			memset(sValue,0,sizeof sValue);
			SMT_GetValue(m_handler[0].handler,nRow,"lvol3",&nValue);
			if( nValue==1 )		  mPack.ucCmd=0x9B;		//��
			else if( nValue==2 )  mPack.ucCmd=0x9C;		//��
			else if( nValue==2 )  mPack.ucCmd=0x9D;		//����
			else return false;
			mPack.nSndDataLen=0;
			mPack.nTaskCode	=SMT_SMARTFRONTGETTIMESWITCH;
			mPack.nAcction	=SMT_SMARTFRONTGETTIMESWITCH;
			mPack.nTaskCode	=nFunTaskID;
			mPack.nFlag		=nDeviceFlag;
			mPack.nFlag		=1;
			break;
		case SMT_SMARTFRONTGETEATNUM:	//ǰ�û�ȡ�ʹ���ʱ�� add by dj 20080520
			SMT_GetValue(m_handler[0].handler,nRow,"sdate0",cDeviceID,sizeof(cDeviceID)); //�豸ID��
			SMT_GetValue(m_handler[0].handler,nRow,"lvol0",&nDeviceFlag); //�豸��ʶ
			SMT_GetValue(m_handler[0].handler,nRow,"lvol2",&nFunTaskID);  //���ܺ�
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
				if( i%4==0 ) //�ʹα��
				{
					sStr[j]=j;
					j++;
				}
				sStr[j]=atoi((char*)CRC); //ת��Ϊ16����
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
		case SMT_SMARTFRONTDOWNGETASSIT: //��ȡ��������
			SMT_GetAllInitAssistantList(true,mPack.nMessageID);
			return true;
		default:
			return false;
	}
	//����·�в�������
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ��������뵽��Ӧ��·
*=================================================================*/
bool CInterface::SMT_InsertTaskToLink(SMARTCOMMPACK mPack,bool bFlag)
{
	int i=0;
	list<CSocketSmart>::iterator	SocketSmart;
	
	//����·Ϊ��,��ֱ�ӷ���
	if( g_LTcpsmart.empty() )	return false;
	if( !bFlag ) //ֻ�Դ�����豸ID�Ž�����������
	{
		for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
		{
			//ָ��Ϊ�գ���ֱ�ӷ���ʧ��
			if( SocketSmart==g_LTcpsmart.end()) continue;
			//������ add by dj 20080801
			if( !memcmp(SocketSmart->m_IDNo,mPack.ucpIDNo,4) )
			{
				mPack.nConnectPortNo = 0;								//�����˿ں�
				mPack.ucMacNo        = SocketSmart->m_MacNum;			//����
				memcpy(mPack.ucpMachineCode,SocketSmart->m_MacCode,2);	//���ʹ���
				memcpy(mPack.ucRegNo,SocketSmart->m_regno,4);			//ע���
				mPack.level = 0;
				//ѹ�뵽�������
				if( SocketSmart->InsertTask(&mPack) ) return true;
				else return false;
			}
			//2.���÷����Ƿ������豸,��û��,������һ������
			if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) continue;
			for(i=0; i<SocketSmart->m_nTotalPos; i++)
			{
				//��������ʵ�������POS�ն���
				if( !memcmp(SocketSmart->m_SmartPos[i].ucpIDNo,mPack.ucpIDNo,4))
				{
					mPack.nConnectPortNo = SocketSmart->m_SmartPos[i].nPort;		//�����˿ں�
					mPack.ucMacNo        = SocketSmart->m_SmartPos[i].ucMacNo;		//����
					memcpy(mPack.ucpMachineCode,SocketSmart->m_SmartPos[i].ucpMachineCode,2); //���ʹ���
					memcpy(mPack.ucRegNo,SocketSmart->m_SmartPos[i].ucRegNo,4);		//ע���
					// add by tc 20091009 , �ж�������¼��豸,�����ϼ�ID
					if(memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_5301,2)==0)
					{
						mPack.level = 1;
						mPack.level_array[0] = SocketSmart->m_MacNum; // �ϼ��豸����
						mPack.level_array[1] = SocketSmart->m_SmartPos[i].nConnectPort; // �豸ʹ�õķ������˿ں�
					}
					else
						mPack.level = 0;
					
					//ѹ�뵽�������
					if( SocketSmart->InsertTask(&mPack) ) return true;
					else return false;
				}
			}
		}
	}
	else //�������豸����
	{
		for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
		{
			//ָ��Ϊ�գ���ֱ�ӷ���ʧ��
			if( SocketSmart==g_LTcpsmart.end())	continue;
			//2.���÷����Ƿ������豸,��û��,������һ������
			if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) continue;
			
			if( mPack.nAcction==SMT_SMARTFRONTBROADBLACK )
			{
				//��ʾ����ˮ���豸
				if( memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_0245,2)&& 
					memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_0244,2) )
				{
					//��Ϊ�㲥������ֻ���շѻ�����
					if( mPack.nAcction==SMT_SMARTFRONTBROADBLACK) //�㲥������
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
				mPack.nConnectPortNo = SocketSmart->m_SmartPos[i].nPort;					//�����˿ں�
				mPack.ucMacNo        = SocketSmart->m_SmartPos[i].ucMacNo;					//����
				memcpy(mPack.ucpMachineCode,SocketSmart->m_SmartPos[i].ucpMachineCode,2);	//���ʹ���
				memcpy(mPack.ucRegNo,SocketSmart->m_SmartPos[i].ucRegNo,4);					//ע���
				memcpy(mPack.ucpIDNo,SocketSmart->m_SmartPos[i].ucpIDNo,4);					//ID��
				// add by tc 20091009 , �ж�������¼��豸,�����ϼ�ID
				if(memcmp(SocketSmart->m_MacCode,MACHINE_TYPE_5301,2)==0)
				{
					mPack.level = 1;
					mPack.level_array[0] = SocketSmart->m_MacNum; // �ϼ��豸����
					mPack.level_array[1] = SocketSmart->m_SmartPos[i].nConnectPort; // �豸ʹ�õķ������˿ں�
				}
				else
					mPack.level = 0;
				//ѹ�뵽�������
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �ϴ��豸״̬�����˴�
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
		m_pDlg->WriteLog("����˴��ϴ��豸״̬ʱ,���Ӿ����Ч,ֹͣ�ϴ�");
		return false;
	}
	for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
	{		
		if( SocketSmart==g_LTcpsmart.end()) return false;
		if( !SocketSmart->m_nTotalPos||SocketSmart->m_nTotalPos>=MAX_POSNO ) 
		{
			memset(sErrMsg,0,sizeof sErrMsg);
			sprintf(sErrMsg,"��·IP=%s,û�����豸�����豸����256[%ld],����·���ϴ�",SocketSmart->m_IpPar.cIPAddress,SocketSmart->m_nTotalPos);
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
				//��ʼ��cPack��
				if( !SMT_PackInit(m_handler[0].handler) ) return false;
				//���ù��ܺ�
				if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTSENDTICK) )	return false;
				
				SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
				SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ	
				SMT_SetValue(m_handler[0].handler,0,"sphone3",(char*)m_Data.GetSysTime());			//ǰ��ʱ��				
				SMT_SetValue(m_handler[0].handler,0,"lvol1",1);								//�豸ID��ָ�豸����ID
				SMT_SetValue(m_handler[0].handler,0,"vsmess",vsmess);								//�豸ID��״̬	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr0",vsvarstr0);							//�豸ID��״̬	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr1",vsvarstr1);							//�豸ID��״̬	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr2",vsvarstr2);							//�豸ID��״̬	
				SMT_SetValue(m_handler[0].handler,0,"vsvarstr3",vsvarstr3);							//�豸ID��״̬

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
		//��ʼ��cPack��
		if( !SMT_PackInit(m_handler[0].handler) ) return false;
		//���ù��ܺ�
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
		SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
		SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ	
		SMT_SetValue(m_handler[0].handler,0,"sphone3",(char*)m_Data.GetSysTime());			//ǰ��ʱ��
		SMT_SetValue(m_handler[0].handler,0,"lvol1",1);								//�豸ID��ָ�豸����ID
		SMT_SetValue(m_handler[0].handler,0,"vsmess",vsmess);	//�豸ID��״̬	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr0",vsvarstr0);	//�豸ID��״̬	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr1",vsvarstr1);	//�豸ID��״̬	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr2",vsvarstr2);	//�豸ID��״̬	
		SMT_SetValue(m_handler[0].handler,0,"vsvarstr3",vsvarstr3);	//�豸ID��״̬				
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ��ȡ���в�������
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
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTDOWNALLASSIT) )
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ

	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )
	{
		return false;
	}
	SMT_GetValue(m_handler[0].handler,0,"lvol1",&nMessageID); //��ϢID��
	memset(g_SaveAssistantList,0,sizeof g_SaveAssistantList);
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;
		row = 0;
		while(row < row_count)
		{
			nOffSet=1178*total_rows;
			//���κŰ汾
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol1",&nBatchVer);
			if( nBatchVer>g_nSaveAssistantVer)
			{
				g_nSaveAssistantVer=nBatchVer;
			}			
			//λͼ��1����			
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��2����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��3����
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);			
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��4����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��5����
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset4",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��6����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset5",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��7����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset6",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��8����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"scusttypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��9����
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"ssectypes",cValue,sizeof(cValue));
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��10����
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"vsmess",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);	
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��11����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��12����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��13����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveAssistantList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��14����
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
		if(!SMT_PackIsEof(m_handler[0].handler ))	break; //��ʾ�Ѿ�������β��
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);

	
	//��ʾ����ҪӦ�� //������Ӧ�� add by dj 20080409
	if( !bAnswer ) return true;
	Sleep(100);	
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTSETTASKRESULT) )
	{
		return false;
	}
		
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(m_handler[0].handler,0,"lvol1",(int)nReMessageID);		//��ϢID��
	SMT_SetValue(m_handler[0].handler,0,"lvol4",(int)0);				//������	
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ��ȡ���к�����
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
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�

	if( !SMT_SetRequestFunID(m_handler[0].handler,FunId) )
	{
		return false;
	}
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);			//��̬��Կ

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
			
			//λͼ��1����			
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��2����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��3����
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);			
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��4����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��5����
			memset(cValue, 0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset4",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��6����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset5",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��7����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"usset6",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue+2,98*2,ucValue);
			m_Data.AscToBcd((byte*)ucValue,98,ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49,ucValue,49);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��8����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"scusttypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��9����
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"ssectypes",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,200,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100,ucValue,100);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��10����
			memset(ucValue,0,sizeof ucValue);
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"vsmess",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);	
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);
			
			//λͼ��11����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��12����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��13����
			memset(cValue,0,sizeof cValue);
			memset(ucValue,0,sizeof ucValue);
			SMT_GetValue(m_handler[0].handler,row,"vsvarstr2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,254,(byte*)ucValue);
			memcpy(g_SaveBlackList+nOffSet+49+49+49+49+49+49+49+100+100+127+127+127,ucValue,127);
			if( g_IniFilePara.bWriteDebugLog ) m_pDlg->WriteLog(cValue);

			//λͼ��14����
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
		if(!SMT_PackIsEof(m_handler[0].handler ))	break; //��ʾ�Ѿ�������β��
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ǰ������ʱ��ȡ�����豸������Ϣ
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

	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )									return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTALLDEVICE) )	return false;
	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);		//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);				//��̬��Կ
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
	
	// ���������豸
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;		
		row = 0;
		while(row < row_count)
		{
			memset(&cPos,  0,sizeof cPos);
			//�豸ID��
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucpIDNo);
			
			//�豸ע���
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucRegNo);

			//����
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol4",&nValue);
			cPos.ucMacNo=(int)nValue;

			//���ʹ���
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"semp",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,4,cPos.ucpMachineCode);

			//ͨѶIP��ַ
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sstation0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy(cPos.cIP,cValue);

			//ͨѶ�˿�
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sbank_code",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			cPos.nPort=atol(cValue);
			
			//�豸�汾��			
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sdate3",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucDeviceVer,cValue);

			//��Ƭ�ṹ
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sholder_type",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucCardType,cValue);
			
			//����
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"snote2",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucCardclass,cValue);
			
			//�������˿�����
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol5",&nValue); 			
			cPos.nServerPortTotal=nValue;
			
			//�豸���Ӷ˿�
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol6",&nValue); 			
			cPos.nConnectPort=nValue;

			//�ϼ��豸ID
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"stime0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			m_Data.AscToBcd((byte*)cValue,8,cPos.ucServerDeviceID);
			
			//�豸״̬
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol7",&nValue); 			
			cPos.nCommunicationStatus=nValue;

			//��·ģʽ
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol8",&nValue);
			cPos.nLinkMode=nValue;

			//����ͨѶ��ʽ
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol10",&nValue);
			cPos.nDataComWay=nValue;

			//�������汾��Ч��
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sserial0",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucBlackCardExp,cValue);

			//�������汾
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"sserial1",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			strcpy((char*)cPos.ucBlackCardVer,cValue);

			//��ĩ��ˮ��
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"lvol11",&nValue);
			cPos.nInvoiceNoLast=nValue;
			cPos.nMessageID=g_nMsgID++;
			g_VSmartPos.push_back(cPos);
			row++;
			total_rows++;
		}
		
		if(!SMT_PackIsEof(m_handler[0].handler))	break; //��ʾ�Ѿ�������β��
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������ת��
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
	  //32�ֽڵ�λͼ
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �ӽ��˴��ȡ�豸�ķ���
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
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )
	{
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,Task->nTaskCode) )	
	{
		return false;
	}	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey);	//��̬��Կ
	SMT_SetValue(m_handler[0].handler,0,"sdate0",cDeviceID);			//ID
	SMT_SetValue(m_handler[0].handler,0,"lvol0",Task->nFlag);			//�豸��ʶ	
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
	int		nMode=0;	//�Ʒ�������ģʽ
	
	memset(cValue,0,sizeof cValue);
	Task->nSndDataLen=0;
	do
	{
		if(!SMT_GetRowCount(m_handler[0].handler,&row_count))	return false;		
		row = 0;
		while(row<row_count)
		{
			//����
			memset(cValue,0,sizeof cValue);
			SMT_GetValue(m_handler[0].handler,row,"scust_limit",cValue,sizeof(cValue)); 
			m_Data.trim(cValue);
			nLen=strlen(cValue);
			m_Data.AscToBcd((byte*)cValue,nLen,Task->ucSndData+Task->nSndDataLen);
			//���ʸ���
			SMT_GetValue(m_handler[0].handler,row,"lvol1",&nValue); 
			Task->nSndDataLen+=nValue*3;
			//����			
			SMT_GetValue(m_handler[0].handler,row,"lvol0",&nValue);
			m_Data.SetCardKind(sCardKind,nValue);
			//�Ʒ�������ģʽ
			if( nMode<=0 )	SMT_GetValue(m_handler[0].handler,row,"lvol2",&nMode); 			
			row++;
			total_rows++;
		}
		if(!SMT_PackIsEof(m_handler[0].handler))	break; //��ʾ�Ѿ�������β��
		if(!SMT_NextPack(m_handler[0].handler,5000,&errcode,sErrMsg))
		{
			sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
			return false;
		}
	}while(true);
	
	//����·�в������ÿ��������
	memcpy(mPack.ucSndData,sCardKind,mPack.nSndDataLen);
	memcpy(mPack.ucpIDNo,Task->ucpIDNo,4);	
	mPack.nAcction=SMT_SMARTFRONTGETRATE;
	SMT_InsertTaskToLink(mPack);
	//����·�в��빤��ģʽ������
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ǰ��ע��
*=================================================================*/
bool CInterface::SMT_SmartRegister(DWORD nTimeOut)
{
	int		nErrCode=0;
	int		nRow=0,nRowTotal=0;
	char	sErrMsg[128];
	int		nRegNo=0;	
	CSystemInfo info;

	memset(sErrMsg, 0,sizeof sErrMsg);
	//�������ļ��м���Ƿ��Ѿ�ע��
	GetPrivateProfileString("SMARTFRONTREG", "REGISTER", "0",sErrMsg,sizeof(sErrMsg),g_PathIniFileName);
	if( sErrMsg[0]=='1' ) return true;

	memset(sErrMsg, 0,sizeof sErrMsg);
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )				return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTREGISTER) )	return false;
	SMT_SetValue(m_handler[0].handler,0,"scust_auth2","SMART999");		//ǰ�û�����
	SMT_SetValue(m_handler[0].handler,0,"scust_limit",info.szIP);		//ǰ������IP��ַ
	SMT_SetValue(m_handler[0].handler,0,"scust_limit2",info.szMAC);		//ǰ�����������ַ
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ǰ��ǩ��
*=================================================================*/
bool CInterface::SMT_SmartFrontLogin(DWORD nTimeOut)
{
	int		nErrCode=0;
	char	sErrMsg[128];
	int		nRowTotal=0;
	char	buffer[64];

	memset(buffer, 0,sizeof buffer);
	memset(sErrMsg,0,sizeof sErrMsg);

	//ǰ��ע��
	if( !SMT_SmartRegister(nTimeOut) )										return false;	
	//��ʼ��cPack��
	if( !SMT_PackInit(m_handler[0].handler) )								return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(m_handler[0].handler,SMT_SMARTFRONTLOGIN) )	return false;	
	SMT_SetValue(m_handler[0].handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(m_handler[0].handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	if( !SMT_SendAndRecvData(0,m_handler[0].handler,nTimeOut,&nErrCode,sErrMsg) )
	{
		sprintf(m_szText,"ret=%ld,sErrmsg=%s",nErrCode,sErrMsg);
		return false;
	}
	if( SMT_RecvStatus(m_handler[0].handler) )								return false;	
	if( !SMT_GetRowCount(m_handler[0].handler,&nRowTotal) )					return false;
	memset(g_sWorkKey,0,sizeof g_sWorkKey);
	SMT_GetValue(m_handler[0].handler,0,"scert_addr",buffer,sizeof(buffer));			//������Կ
	SMT_GetValue(m_handler[0].handler,0,"scust_limit2",g_IniFilePara.sKey,sizeof(g_IniFilePara.sKey));//��̬��Կ
	SMT_GetValue(m_handler[0].handler,0,"lvol0",&g_nWalletNo);							//Ǯ����	
	m_Data.AscToBcd((byte*)buffer,strlen(buffer),(byte*)g_sWorkKey);	
	return true;
}

/*=================================================================
* Function ID :  SMT_TimeRecordAnalysis
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true �� false��
* Description :  
* Notice	   :  ��ʱ��¼����
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//�õ���������
	nDataType   = atol(m_Data.GetColValues(sData));

	//������
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//������ѹ��
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//ע���
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//ͨ�Ű汾
	StrDeal.lVer=sBuffer[4];	
	//����ԭ��
	StrDeal.lStartReason=sBuffer[5];
	//������ˮ��
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//���ʹ���
	StrDeal.nICCardCode=(long)sBuffer[22];
	//����ģʽ
	StrDeal.nWorkMode=(long)sBuffer[20];
	//���׿���
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
	//��ʾ����
	if( StrDeal.nWorkMode == 4 && (StrDeal.nICCardCode == 100 || StrDeal.nICCardCode == 101 ) )
	{
		m_Data.BcdToAsc(sBuffer+8,5,(byte*)StrDeal.sShowCardNo);
	}
	//��������
	sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[13],sBuffer[14],sBuffer[15]);
	//����ʱ��
	sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[16],sBuffer[17],sBuffer[18]);
	//��������
	StrDeal.nTimerType=sBuffer[21];
	//��Ӧͷ���
	StrDeal.nInductorNo=sBuffer[23];
	//���°��־
	StrDeal.nDutyFlag=sBuffer[24];
	if( StrDeal.nDutyFlag>9) StrDeal.nDutyFlag=0;
	//���ױ��
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[26],sBuffer[27]);
	//���ܺ�
	if( nDataType==RECORDDATATYPE_HISTROY )
	{
		StrDeal.nFunctionID=SMT_SMARTFRONTSETTASKRESULT; //��ʷ����
	}
	else
	{
		StrDeal.nFunctionID=SMT_SMARTFRONTUPTIMEDATA;
	}
	//��������
	strcpy(StrDeal.sSaleType,"��ʱ");
	//��ʼ��cPack��
	if( !SMT_PackInit(nHandler) )								return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
		
	SMT_SetValue(nHandler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);						//ǰ�û�ע���
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//��̬��Կ
	SMT_SetValue(nHandler,0,"sdate0",StrDeal.sRegNo);				//�ն��豸ID
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lInvoiceNo);			//������ˮ��
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.nICCardCode);			//���ʹ���
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.nWorkMode);				//����ģʽ����
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lCardID);				//���׿���
	SMT_SetValue(nHandler,0,"sstation0",StrDeal.sShowCardNo);		//��ʾ����	
	sprintf(sDateStr,"20%s",StrDeal.sDate);
	SMT_SetValue(nHandler,0,"sdate1",sDateStr);				//��������
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//����ʱ��	
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.nTimerType);			//��������
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.nInductorNo);			//��Ӧͷ
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.nDutyFlag);			//�°��־
	SMT_SetValue(nHandler,0,"lvol11",StrDeal.lDealCode);			//���ױ�ʶ	
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.lBatchNo);		//ͨѶ�汾
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//����ԭ��
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC	
	
	sprintf(sMsg,"�ϴ���¼�����˴�[�ն˺�->%s ��ˮ��->%05ld ���׿���->%07ld ʱ��->%s%s %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lCardID,
		StrDeal.sDate,
		StrDeal.sTime,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		sprintf(sMsg," ʧ��,���˴�����Ѿ��Ͽ�(%ld,%s)",nErrCode,sErrMsg);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if(SMT_RecvStatus(nHandler) )
	{
		sprintf(sMsg," ʧ��,���˴�����Ѿ��Ͽ�(%ld,%s)",nErrCode,sErrMsg);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," �ɹ�");
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ���Ѽ�¼����
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//�õ���������
	nDataType   = atol(m_Data.GetColValues(sData));

	//������
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//������ѹ��
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//ע���
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//ͨ�Ű汾
	StrDeal.lVer=sBuffer[4];
	//Ǯ����
	StrDeal.lWalletcode=sBuffer[5]>>4;
	//����ԭ��
	StrDeal.lStartReason=sBuffer[5]&0x0F;
	//������ˮ��
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//���׿���
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//�������ں�ʱ�� ��ʱ��ȫΪFF����0
	if( memcmp(sBuffer+11,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//����
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
		//ʱ��
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	}
	else
	{
		//����
		strcpy(StrDeal.sDate,"00000000");
		//ʱ��
		strcpy(StrDeal.sTime,"000000");
	}	
	//��ʹ�ô���
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//�뿨���
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//�������
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//���ױ��
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[26],sBuffer[27]);

	//���׽�����
	if( !memcmp(MACHINE_TYPE_0201,sMachineCode,2))//��ֵ���
	{
		if( StrDeal.lDealCode==0x30 )	//�ֽ��ֵ�����
		{
			StrDeal.lTransMoney	=StrDeal.lOutMoney;
			StrDeal.lOutMoney	=StrDeal.lInMoney;			
			StrDeal.nFunctionID=SMT_SMARTFRONTMAGMONEY;
			//��������
			strcpy(StrDeal.sSaleType,"����");
		}
		else //��ֵ���
		{
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			StrDeal.nFunctionID=SMT_SMARTFRONTADDMONEY;
			//��������
			strcpy(StrDeal.sSaleType,"��ֵ");
		}
	}
	else //�շ�����
	{
		//��������
		strcpy(StrDeal.sSaleType,"����");
		//��¼�����д��� ��ʱʱ��Ϊ4�ֽ�
		if( StrDeal.lVer==0x82||StrDeal.lVer==0x83 )
		{
			nTime=m_Data.HexToInt(sBuffer+11,4);
			//����
			sprintf(StrDeal.sDate,"%02ld%02ld%02ld",(nTime>>26)&0x3F,(nTime>>22)&0x0F,(nTime>>17)&0x1F);
			//ʱ��
			sprintf(StrDeal.sTime,"%02ld%02ld%02ld",(nTime>>12)&0x1F,(nTime>>6)&0x3F,(nTime>>0)&0x3F);			
			//����
			StrDeal.lRateMoney=sBuffer[15]+sBuffer[16]*256;
			//���׽��(��������)
			StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
			//��������
			strcpy(StrDeal.sSaleType,"���");
		}
		else
		{
			StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
		}
		//
		if( StrDeal.lDealCode==0xFA||StrDeal.lDealCode==0xF0) //��ԡ��ֵ
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTCHANGEMONEY;
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			//��������
			strcpy(StrDeal.sSaleType,"��ֵ");
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������¼����
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//�õ���������
	nDataType   = atol(m_Data.GetColValues(sData));

	//������
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//������ѹ��
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//ע���
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//ͨ�Ű汾
	StrDeal.lVer=sBuffer[4];
	//Ǯ����
	StrDeal.lWalletcode=sBuffer[26]&0x0F;
	//������־
	StrDeal.sAssitFlag=sBuffer[26];
	//����ԭ��
	StrDeal.lStartReason=sBuffer[5];
	//������ˮ��
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//�������ں�ʱ�� ��ʱ��ȫΪFF����0
	if( memcmp(sBuffer+8,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//����
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[8],sBuffer[9],sBuffer[10]);
		//ʱ��
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
	}
	else
	{
		//����
		strcpy(StrDeal.sDate,"00000000");
		//ʱ��
		strcpy(StrDeal.sTime,"000000");
	}	
	//���׿���
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+21,3);
	//��ʹ�ô���
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+24,2);
	//�������
	sStr[2]=sBuffer[29];
	sStr[1]=sBuffer[30];
	sStr[0]=sBuffer[31];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//���׽��
	sStr[1]=sBuffer[27];
	sStr[0]=sBuffer[28];
	StrDeal.lTransMoney=m_Data.HexToInt(sStr,2);
	if( (sBuffer[26]&0x20)==0x00 ) //������
	{
		//�뿨���
		StrDeal.lInMoney=StrDeal.lOutMoney+StrDeal.lTransMoney;
		//���׽��
		StrDeal.lTransMoney=0-StrDeal.lTransMoney;
	}
	else
	{
		//�뿨���
		StrDeal.lInMoney=StrDeal.lOutMoney-StrDeal.lTransMoney;
	}
	//����
	StrDeal.lBatchNo=m_Data.HexToInt(sBuffer+32,2);	
	//���ױ��
	StrDeal.lDealCode=sBuffer[34];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[35],sBuffer[36]);
	//���ܺ�
	StrDeal.nFunctionID=SMT_SMARTFRONTUPASSISDATA;
	//��������
	strcpy(StrDeal.sSaleType,"����");
	return true;
}


/*=================================================================
* Function ID :  SMT_SaleRecordAnalysis_SongJiang
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  true �� false��
* Description :  
* Notice	   :  ���Ѽ�¼����(�ɽ���ѧ��)
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//�õ���������
	nDataType   = atol(m_Data.GetColValues(sData));

	//������
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//������ѹ��
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//ע���
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//ͨ�Ű汾
	StrDeal.lVer=sBuffer[4];
	//Ǯ����
	StrDeal.lWalletcode=sBuffer[5]>>4;
	//����ԭ��
	StrDeal.lStartReason=sBuffer[5]&0x0F;
	//������ˮ��
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//���׿���
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//�������ں�ʱ�� ��ʱ��ȫΪFF����0
	if( memcmp(sBuffer+11,"\xFF\xFF\xFF\xFF\xFF\xFF",6) )
	{	
		//����
		sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
		//ʱ��
		sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	}
	else
	{
		//����
		strcpy(StrDeal.sDate,"00000000");
		//ʱ��
		strcpy(StrDeal.sTime,"000000");
	}	
	//��ʹ�ô���
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//�뿨���
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//�������
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//���ױ��
	StrDeal.lDealCode=sBuffer[25];
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[29],sBuffer[30]);

	//���׽�����
	if( !memcmp(MACHINE_TYPE_0201,sMachineCode,2))
	{
		StrDeal.lOperatorID=m_Data.HexToInt(sBuffer+26,3);	
		if( StrDeal.lDealCode==0x30 )	//��ֵ����Ѽ�¼
		{
			StrDeal.lTransMoney	=StrDeal.lOutMoney;
			StrDeal.lOutMoney	=StrDeal.lInMoney;			
			StrDeal.nFunctionID=SMT_SMARTFRONTMAGMONEY;
			//��������
			strcpy(StrDeal.sSaleType,"����");
		}
		else //��ֵ����¼
		{
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			StrDeal.nFunctionID=SMT_SMARTFRONTADDMONEY;
			//��������smar
			strcpy(StrDeal.sSaleType,"��ֵ");
		}
	}
	else //�շ�����
	{
		//��������
		strcpy(StrDeal.sSaleType,"����");
		//�����
		sStr[2]=sBuffer[26];
		sStr[1]=sBuffer[27];
		sStr[0]=sBuffer[28];
		StrDeal.lRateMoney=m_Data.HexToInt(sStr,3);
		//���׽��(��������)
		StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
		if( StrDeal.lDealCode==0xFA||StrDeal.lDealCode==0xF0) //��ԡ����
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTCHANGEMONEY;
			StrDeal.lTransMoney=StrDeal.lOutMoney-StrDeal.lInMoney;
			//��������
			strcpy(StrDeal.sSaleType,"��ֵ");
		}
		else if( StrDeal.lDealCode==0xFE ) //���ѳ���
		{
			StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;
			StrDeal.lRateMoney=0-StrDeal.lRateMoney;
			//��������
			strcpy(StrDeal.sSaleType,"���ѳ���");
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ���Ѽ�¼����(���ݴ�ѧ��)
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,(byte*)sMachineCode);
	//�õ���������
	nDataType   = atol(m_Data.GetColValues(sData));

	//������
	strcpy((char*)sStr,m_Data.GetColValues(sData));	
	nLen=strlen((char*)sStr);
	if( nLen%2) nLen--;
	//������ѹ��
	memset(sBuffer,0,sizeof sBuffer);
	m_Data.AscToBcd(sStr,nLen,sBuffer);
	//ע���
	m_Data.BcdToAsc(sBuffer,4,(byte*)StrDeal.sRegNo);
	//ͨ�Ű汾
	StrDeal.lVer=sBuffer[4];
	//Ǯ����
	StrDeal.lWalletcode=0;
	//����ԭ��
	StrDeal.lStartReason=0;
	//�ʹκ�
	StrDeal.nEatNum=sBuffer[5];
	//������ˮ��
	StrDeal.lInvoiceNo=m_Data.HexToInt(sBuffer+6,2);
	//���׿���
	StrDeal.lCardID=m_Data.HexToInt(sBuffer+8,3);

	//�������ں�ʱ��
	//����
	sprintf(StrDeal.sDate,"%02ld%02ld%02ld",sBuffer[11],sBuffer[12],sBuffer[13]);
	//ʱ��
	sprintf(StrDeal.sTime,"%02ld%02ld%02ld",sBuffer[14],sBuffer[15],sBuffer[16]);	
	sprintf(StrDeal.sDealTime,"20%02ld-%02ld-%02ld %02ld:%02ld:%02ld",sBuffer[11],sBuffer[12],sBuffer[13],sBuffer[14],sBuffer[15],sBuffer[16]);
	
	//��ʹ�ô���
	StrDeal.lTimes=m_Data.HexToInt(sBuffer+17,2);
	//�뿨���
	sStr[2]=sBuffer[19];
	sStr[1]=sBuffer[20];
	sStr[0]=sBuffer[21];
	StrDeal.lInMoney=m_Data.HexToInt(sStr,3);
	//�������
	sStr[2]=sBuffer[22];
	sStr[1]=sBuffer[23];
	sStr[0]=sBuffer[24];
	StrDeal.lOutMoney=m_Data.HexToInt(sStr,3);
	//���ױ��
	StrDeal.lDealCode=sBuffer[25];	
	//�̻����  26 27
	sprintf(StrDeal.sShopID,"%02X%02X",sBuffer[26],sBuffer[27]);
	//CRC
	sprintf(StrDeal.sCrc,"%02X%02X",sBuffer[28],sBuffer[29]);	
	//��������
	strcpy(StrDeal.sSaleType,"����");
	//���׽��
	StrDeal.lTransMoney=StrDeal.lInMoney-StrDeal.lOutMoney;
	StrDeal.nFunctionID=SMT_SMARTFRONTUPDEALDATA;

	SMT_SetValue(nHandler,0,"lvol1",StrDeal.lRateMoney);			//����
	SMT_SetValue(nHandler,0,"lcert_code",12);						//ǰ�û�ע���
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//��̬��Կ
	SMT_SetValue(nHandler,0,"sdate1",StrDeal.sRegNo);				//�ն��豸ID
	SMT_SetValue(nHandler,0,"lvol4",StrDeal.lInvoiceNo);			//������ˮ��
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.lCardID);				//���׿���
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.lWalletcode);			//����Ǯ����
	SMT_SetValue(nHandler,0,"spost_code",StrDeal.sDate);			//��������
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//����ʱ��
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lTimes);				//��Ƭ���״���	
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.lTransMoney);			//���׽��
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.lInMoney);				//�뿨ֵ
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.lOutMoney);			//����ֵ
	SMT_SetValue(nHandler,0,"lvol12",StrDeal.lDealCode);			//���ױ�ʶ
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.sShopID);		//�̻���
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//����ԭ��
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lOperatorID);			//����Ա����
	
	//��ʼ��cPack��
	if( !SMT_PackInit(nHandler) )								return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
	sprintf(sMsg,"�ϴ���¼�����˴�[�ն˺�->%s ��ˮ��->%05ld ���׿���->%ld ����ʱ��->%s ��ʶ->%02X %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lCardID,
		StrDeal.sDealTime,
		StrDeal.lDealCode,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		strcat(sMsg," ʧ��,���˴�����Ѿ��Ͽ�");
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if(SMT_RecvStatus(nHandler) )
	{
		strcat(sMsg," ʧ��,���˴�����Ѿ��Ͽ�");
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," �ɹ�");
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  �ϴ���������
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
	//ȥ����¼�е�����
	m_Data.GetColValues(sData);
	//�û��ʹ���
	strcpy(sMachineCode,m_Data.GetColValues(sData));	
	//�õ���������
	nDataType=atol(m_Data.GetColValues(sData));
	m_Data.AscToBcd((byte*)sMachineCode,4,ucMacCode);
	//������¼
	if( nDataType==ASSISTANTDATATYPE_FACE )
	{
		SMT_AssitantRecordAnalysis(ssData,StrDeal);		
		sprintf(sMsg,"������־->%02X �������->%ld �뿨ֵ->%ld ����ֵ->%ld",
			(int)StrDeal.sAssitFlag,StrDeal.lTransMoney,StrDeal.lInMoney,StrDeal.lOutMoney);
		m_pDlg->WriteLog(sMsg);	
	}	//��ʱ���� 20080506
	else if( nDataType==TIMEDATATYPE_FACE||(nDataType==RECORDDATATYPE_HISTROY&&!memcmp(ucMacCode,MACHINE_TYPE_0121,2)) ) 
	{

		return SMT_TimeRecordAnalysis(nHandler,nTimeOut,nErrCode,sErrMsg,ssData,StrDeal);
	}
	else //����/��ֵ��¼
	{
		if( strlen(sData)>=63 )			//�ɽ���ѧ�� 31�ֽ�+1�ֽڻس�
		{
			SMT_SaleRecordAnalysis_SongJiang(ssData,StrDeal);
		}
		else if( strlen(sData)>=61 )	//���ݴ�ѧ�� 30�ֽ�+1�ֽڻس�
		{
			return SMT_SaleRecordAnalysis_GuangZhou(nHandler,nTimeOut,nErrCode,sErrMsg,ssData,StrDeal);	
		}
		else
		{
			SMT_SaleRecordAnalysis(ssData,StrDeal);
		}
	}
	
	//��ʼ��cPack��
	if( !SMT_PackInit(nHandler) )								return false;
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(nHandler,StrDeal.nFunctionID) )	return false;
	
	SMT_SetValue(nHandler,0,"lvol1",StrDeal.lRateMoney);			//����
	SMT_SetValue(nHandler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(nHandler,0,"scust_limit2",g_IniFilePara.sKey);		//��̬��Կ
	SMT_SetValue(nHandler,0,"sdate1",StrDeal.sRegNo);				//�ն��豸ID
	SMT_SetValue(nHandler,0,"lvol4",StrDeal.lInvoiceNo);			//������ˮ��
	SMT_SetValue(nHandler,0,"lvol5",StrDeal.lCardID);				//���׿���
	SMT_SetValue(nHandler,0,"lvol6",StrDeal.lWalletcode);			//����Ǯ����
	SMT_SetValue(nHandler,0,"spost_code",StrDeal.sDate);			//��������
	SMT_SetValue(nHandler,0,"spost_code2",StrDeal.sTime);			//����ʱ��
	SMT_SetValue(nHandler,0,"lvol7",StrDeal.lTimes);				//��Ƭ���״���
	SMT_SetValue(nHandler,0,"lvol8",StrDeal.lTransMoney);			//���׽��
	SMT_SetValue(nHandler,0,"lvol9",StrDeal.lInMoney);				//�뿨ֵ
	SMT_SetValue(nHandler,0,"lvol10",StrDeal.lOutMoney);			//����ֵ
	SMT_SetValue(nHandler,0,"lvol12",StrDeal.lDealCode);			//���ױ�ʶ
	SMT_SetValue(nHandler,0,"lbank_acc_type",StrDeal.lBatchNo);		//ͨѶ�汾
	SMT_SetValue(nHandler,0,"lbank_acc_type2",StrDeal.lStartReason);//����ԭ��
	SMT_SetValue(nHandler,0,"sbank_code2",StrDeal.sCrc);			//CRC
	SMT_SetValue(nHandler,0,"lvol3",StrDeal.lOperatorID);			//����Ա����
	
	sprintf(sMsg,"�ϴ���¼�����˴�[�ն˺�->%s ��ˮ��->%05ld ���׽��->%-8ld ��ʶ->%02X %s]",
		StrDeal.sRegNo,
		StrDeal.lInvoiceNo,
		StrDeal.lTransMoney,
		StrDeal.lDealCode,
		StrDeal.sSaleType);
	if( !SMT_SendAndRecvData(1,nHandler,nTimeOut,nErrCode,sErrMsg) )
	{
		sprintf(sTemp," ʧ��,���˴�����Ѿ��Ͽ�,ret[%d]",*nErrCode);
		strcat(sMsg,sTemp);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		Sleep(1000);
		return false;
	}
	if((iRetCode=SMT_RecvStatus(nHandler))!=0)
	{
		sprintf(sTemp," ʧ��,���˴�����Ѿ��Ͽ�,ret[%d]",iRetCode);
		strcat(sMsg,sTemp);
		m_pDlg->AddString(sMsg);
		m_pDlg->WriteLog(sMsg);
		return false;
	}
	strcat(sMsg," �ɹ�");
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ȷ���Ƿ���첹��
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
	//��ȡ���	
	if( (Handler=SMT_GetXDHandle())==NULL ) return false;
	//��ʼ��cPack��
	if( !SMT_PackInit(Handler) )							
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTWHETHERASSIT) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(Handler,0,"lvol5",m_Data.HexToInt(buffer,3));				//����
	SMT_SetValue(Handler,0,"lvol3",m_Data.HexToInt(buffer+3,2));			//���κ�
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//�豸ID��
	SMT_SetValue(Handler,0,"lvol4",0);										//POS��ˮ��
	SMT_SetValue(Handler,0,"lvol9",0);										//�뿨ֵ
	SMT_SetValue(Handler,0,"lvol6",0);										//Ǯ����
	SMT_SetValue(Handler,0,"lvol7",0);										//Ǯ����ˮ��
	
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
	SMT_GetValue(Handler,0,"lvol9",&nRowTotal);			//���
	*nMoney=nRowTotal;
	SMT_GetValue(Handler,0,"lvol3",&nRowTotal);			//����
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������豸�ĳ�ֵ���
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
	//��ȡ���	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"��ȡ�����Ч");
		return false;
	}
	//��ʼ��cPack��
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"��ʼ��cPack��ʧ��");
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(Handler,SMT_SETADDTOTALMONEY) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	m_Data.BcdToAsc(sID,4,sID);
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//�豸ID��	
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
	SMT_GetValue(Handler,0,"lvol1",&nRowTotal);			//���
	*nMoney=nRowTotal;
	SMT_GetValue(Handler,0,"lvol0",&nRowTotal);			//����
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������ֵ��Ȩ��ȷ��
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
	//��ȡ���	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"��ȡ�����Ч");
		return false;
	}
	//��ʼ��cPack��
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"��ʼ��cPack��ʧ��");
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDAUTHTRUE) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	m_Data.BcdToAsc(sID,4,sID);
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(Handler,0,"sdate1",(char*)sID);							//�豸ID��	
	SMT_SetValue(Handler,0,"sdate0",(char*)ucCardID);						//������
	SMT_SetValue(Handler,0,"lvol5",(long)nCardNo);							//���׿���	

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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������ֵ����
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
	
	m_Data.BcdToAsc(ucDevice,4,(byte*)StrRecod.sRegNo);//�豸ID
	StrRecod.lCardID=m_Data.HexToInt(ucData,3); //���׿���
	StrRecod.lWalletcode=m_Data.HexToInt(ucData+3,1); //Ǯ����
	StrRecod.lTimes=m_Data.HexToInt(ucData+4,2);		//Ǯ����ˮ��
	str[0]=ucData[8];
	str[1]=ucData[7];
	str[2]=ucData[6];
	StrRecod.lTransMoney=m_Data.HexToInt(str,3);		//���׽��
	str[0]=ucData[11];
	str[1]=ucData[10];
	str[2]=ucData[8];
	StrRecod.lInMoney=m_Data.HexToInt(str,3);		//�뿨ֵ
	StrRecod.lInvoiceNo=m_Data.HexToInt(ucData+12,2); //��ˮ��
	//����
	sprintf(StrRecod.sDate,"%02ld%02ld%02ld",ucData[14],ucData[14],ucData[16]);
	//ʱ��
	sprintf(StrRecod.sTime,"%02ld%02ld%02ld",ucData[17],ucData[18],ucData[19]);
	//����Ա����
	StrRecod.lOperatorID=m_Data.HexToInt(ucData+20,3);
	//���ױ�־
	StrRecod.lDealCode=ucData[23];
	
	
	//��ȡ���	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"��ȡ�����Ч");
		return false;
	}
	//��ʼ��cPack��
	if( !SMT_PackInit(Handler) )	
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"��ʼ��cPack��ʧ��");
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDREQUEST) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(Handler,0,"sdate1",(char*)StrRecod.sRegNo);				//�豸ID��		
	SMT_SetValue(Handler,0,"lvol5",(long)StrRecod.lCardID);					//���׿���
	SMT_SetValue(Handler,0,"lvol6",(long)StrRecod.lWalletcode);				//Ǯ����
	SMT_SetValue(Handler,0,"lvol7",(long)StrRecod.lTimes);					//Ǯ����ˮ��
	SMT_SetValue(Handler,0,"lvol8",(long)StrRecod.lTransMoney);				//���׽��
	SMT_SetValue(Handler,0,"lvol9",(long)StrRecod.lInMoney);				//�뿨���
	SMT_SetValue(Handler,0,"lvol4",(long)StrRecod.lInvoiceNo);				//POS��ˮ��
	SMT_SetValue(Handler,0,"spost_code",(char*)StrRecod.sDate);				//��������
	SMT_SetValue(Handler,0,"spost_code2",(char*)StrRecod.sTime);			//����ʱ��
	SMT_SetValue(Handler,0,"lvol3",(long)StrRecod.lOperatorID);				//��Ȩ����
	SMT_SetValue(Handler,0,"lvol12",(long)StrRecod.lDealCode);				//��־
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
	SMT_GetValue(Handler,0,"lvol5",&nRowTotal);			//����
	m_Data.IntToHex(nRowTotal,(char*)str);
	memcpy(ucData,str+1,3);
	SMT_GetValue(Handler,0,"lvol10",&nRowTotal);		//����ֵ	
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
* Return	   :  true �� false��
* Description :  
* Notice	   :  ������ֵ����
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
	
	m_Data.BcdToAsc(ucDevice,4,(byte*)StrRecod.sRegNo);  //�豸ID
	StrRecod.lCardID    =m_Data.HexToInt(ucData,3);      //���׿���
	StrRecod.lWalletcode=m_Data.HexToInt(ucData+3,1);    //Ǯ����
	StrRecod.lInvoiceNo =m_Data.HexToInt(ucData+4,2);    //POS��ˮ��
	StrRecod.lBatchNo   =m_Data.HexToInt(ucData+6,2);    //ԭPOS��ˮ��
	//����
	sprintf(StrRecod.sDate,"%02ld%02ld%02ld",ucData[8],ucData[9],ucData[10]);
	//ʱ��
	sprintf(StrRecod.sTime,"%02ld%02ld%02ld",ucData[11],ucData[12],ucData[13]);	
	
	//��ȡ���	
	if( (Handler=SMT_GetXDHandle())==NULL ) 
	{
		strcpy(m_szText,"��ȡ�����Ч");
		return false;
	}
	//��ʼ��cPack��
	if( !SMT_PackInit(Handler) )
	{
		SMT_SetXDHandleFree(Handler);
		strcpy(m_szText,"��ʼ��cPack��ʧ��");
		return false;
	}
	//���ù��ܺ�
	if( !SMT_SetRequestFunID(Handler,SMT_SMARTFRONTADDREQUESTCANCEL) )	
	{
		SMT_SetXDHandleFree(Handler);
		return false;
	}
	SMT_SetValue(Handler,0,"lcert_code",(long)g_IniFilePara.lFrontRegNo);	//ǰ�û�ע���
	SMT_SetValue(Handler,0,"scust_limit",g_IniFilePara.sKey);				//��̬��Կ
	SMT_SetValue(Handler,0,"sdate1",(char*)StrRecod.sRegNo);				//�豸ID��		
	SMT_SetValue(Handler,0,"lvol5",(long)StrRecod.lCardID);					//���׿���
	SMT_SetValue(Handler,0,"lvol6",(long)StrRecod.lWalletcode);				//Ǯ����
	SMT_SetValue(Handler,0,"lvol4",(long)StrRecod.lInvoiceNo);				//POS��ˮ��
	SMT_SetValue(Handler,0,"lvol3",(long)StrRecod.lBatchNo);				//ԭPOS��ˮ��	
	SMT_SetValue(Handler,0,"spost_code",(char*)StrRecod.sDate);				//��������
	SMT_SetValue(Handler,0,"spost_code2",(char*)StrRecod.sTime);			//����ʱ��
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
	SMT_GetValue(Handler,0,"lvol5",&nRowTotal);			//����
	m_Data.IntToHex(nRowTotal,(char*)str);
	memcpy(ucData,str+1,3);
	SMT_GetValue(Handler,0,"lvol10",&nRowTotal);		//����ֵ	
	memset(str,0,sizeof str);
	m_Data.IntToHex(nRowTotal,(char*)str);
	ucData[3]=str[3];
	ucData[4]=str[2];
	ucData[5]=str[1];
	SMT_SetXDHandleFree(Handler);
	return true;
}