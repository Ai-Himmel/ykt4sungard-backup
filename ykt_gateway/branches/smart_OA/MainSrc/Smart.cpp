// Smart.cpp: implementation of the CSmart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmartCommunication.h"
#include "SmartCommunicationDlg.h"
#include "readfile.h"
#include "Smart.h"

CSmart::CSmart()
{	
	m_IpPar.bConnect = false;
	m_pDialog    =NULL;
	m_MacNum	 =0;			//����������		
	m_nMaxMacNo  =0;
	m_nTotalPos	 =0;			//����Ŀǰ�����ն��豸������	
	m_nWriteBytes=0;		    //���͵��˿����ݳ���
	m_nReadBytes =0;			//���ն˿����ݳ���
	m_nPortTotal =0;			//�������Ķ˿�����
	m_nTaskPoint =0;			//����ָ��
	m_nInsertTaskPoint	 =0;
	m_nPostion			 =0;
	m_nQueryFailCount    =0;
	m_nTaskResultStatus  =0;
	nCommunicationStatus =0;	//������ͨѶ״̬		
	memset(&m_STaskArr,  0x00,sizeof m_STaskArr);
	memset(m_regno,      0x00,sizeof m_regno);			//������ע���
	memset(m_IDNo,       0x00,sizeof m_IDNo);			//����ID��
	memset(m_MacCode,    0x00,sizeof m_MacCode);		 //���ʹ���(����)	
	memset(&m_ReadOver,  0x00,sizeof m_ReadOver);
	memset(&m_WriteOver, 0x00,sizeof m_WriteOver);
	memset(m_SmartPos,   0x00,sizeof m_SmartPos);	
	memset(m_szErrorText,0x00,sizeof m_szErrorText);	//����ͨѶʱ�Ĵ�����Ϣ		
	memset(m_SmartPos,   0x00,sizeof m_SmartPos);
	memset(&m_STaskArr,   0x00,sizeof m_STaskArr);
	memset(m_sCurDate,	 0x00,sizeof m_sCurDate);
}

CSmart::~CSmart()
{
	
}

/*=================================================================
* Function ID :  ValidateData
* Input       :  BYTE* Data,int DataLen
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�յ���������Ч  false��ʾ��Ч
* Description :  ����յ���������������Ч��
* Notice	  :  
*					
*=================================================================*/
char* CSmart::GetStatusErrMsg(BYTE StatusCode)
{
	static char ucErrMsg[128];
	memset(ucErrMsg,0x00,sizeof ucErrMsg);

	switch( StatusCode)
	{
		case 0x01:
			sprintf(ucErrMsg,"��д������ʧ��[������%02X]",StatusCode);
			break;
		case 0x02:
			sprintf(ucErrMsg,"ʱ�Ӵ���[������%02X]",StatusCode);
			break;
		case 0x03:
			sprintf(ucErrMsg,"FLASH����ʧ��[������%02X]",StatusCode);
			break;
		case 0x04:
			sprintf(ucErrMsg,"������[������%02X]",StatusCode);
			break;
		case 0x05:
			sprintf(ucErrMsg,"��ˮ�Ŵ�[������%02X]",StatusCode);
			break;
		case 0x06:
			sprintf(ucErrMsg,"�ɹ�ȷ��[������%02X]",StatusCode);
			break;
		case 0x07:
			sprintf(ucErrMsg,"��������[������%02X]",StatusCode);
			break;
		case 0x08:
			sprintf(ucErrMsg,"�޴�����/�������������[������%02X]",StatusCode);
			break;
		case 0x09:
			sprintf(ucErrMsg,"�ظ�����[������%02X]",StatusCode);
			break;
		case 0x0A:
			sprintf(ucErrMsg,"�޼�¼[������%02X]",StatusCode);
			break;
		case 0x0B:
			sprintf(ucErrMsg,"��Ȩ�Ŵ���[������%02X]",StatusCode);
			break;
		case 0x0C:
			sprintf(ucErrMsg,"�ն��豸����Ӧ[������%02X]",StatusCode);
			break;
		case 0x0D:
			sprintf(ucErrMsg,"����ǩ��[������%02X]",StatusCode);
			break;
		case 0x0E:
			sprintf(ucErrMsg,"�������汾����[������%02X]",StatusCode);
			break;
		case 0x11:
			sprintf(ucErrMsg,"��δ�ϴ�����[������%02X]",StatusCode);
			break;
		case 0x15:
			sprintf(ucErrMsg,"���ɹ���ȷ��[������%02X]",StatusCode);
			break;
		case 0x16:
			sprintf(ucErrMsg,"�Ѿ����ʵ���ˮ������[������%02X]",StatusCode);
			break;
		case 0x17:
			sprintf(ucErrMsg,"�н��ʼ�¼δ�ϴ�[������%02X]",StatusCode);
			break;
		case 0x18:
			sprintf(ucErrMsg,"δ��Ȩ,�޷�ǩ��[������%02X]",StatusCode);
			break;			
		case 0x1D:
			sprintf(ucErrMsg,"�޷��������ͨѶ[������%02X]",StatusCode);
			break;	
		case 0xFF:
			sprintf(ucErrMsg,"�˶˿�δ���ն�[������%02X]",StatusCode);
			break;
		default:
			sprintf(ucErrMsg,"�޷��жϵĴ���[������%02X]",StatusCode);
			break;			
	}
	return ucErrMsg;
}

/*=================================================================
* Function ID :  CreateRecordPath
* Input       :  
* Output      :  
* Author      :  
* Date        :  2006  2
* Return	  :  �ɹ� true ʧ�� false
* Description :  �����ն����ͱ����Ŀ¼
* Notice	  :  
*					
*=================================================================*/
bool CSmart::CreateRecordPath()
{
	char  CreatePath[256],cyear[16];
	CData mData;
	
	memset(cyear,0x00,sizeof cyear);
	memset(CreatePath,  0x00,sizeof CreatePath);
	memset(m_CreatePath,0x00,sizeof m_CreatePath);
	memcpy(cyear,mData.GetSysTime(),6);
	
	sprintf(CreatePath,"%s\\Log\\%s\\%s",mData.GetCurPath(),cyear,m_IpPar.cIPAddress);
	strcpy(m_CreatePath,CreatePath);
	if( CreateDirectory(CreatePath,NULL) >0 )
	{
		return true;	 
	}
	else return false;
}

/*=================================================================
* Function ID :  WriteLog
* Input       :  char* msg
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  
* Description :  д��־
* Notice	  :  
*					
*=================================================================*/
void CSmart::WriteLog(char* msg)
{	
	m_Log.WriteDeviceLog(m_CreatePath,m_IDNo,msg);
}

/*=================================================================
* Function ID :  WriteTradeDeal
* Input       :  char* Data
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  
* Description :  д������ϸ��¼
* Notice	  :  
*=================================================================*/
bool CSmart::WriteTradeDeal(char* Data)
{	
	return m_Log.WriteDeviceData(m_CreatePath,m_IDNo,Data);
}

/*=================================================================
* Function ID :  ValidateData
* Input       :  BYTE* Data,int DataLen
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�յ���������Ч  false��ʾ��Ч
* Description :  ����յ���������������Ч��
* Notice	  :  
*=================================================================*/
bool CSmart::ValidateData(BYTE* Data,int DataLen)
{	
	byte	out[6];
	char	str[1024];
	byte	temp[1024];

	memset(temp,0x00,sizeof temp);
	memset(str, 0x00, sizeof str);
	memset(out, 0x00, sizeof out);

	//����һ���ֽ��Ƿ�Ϊ0xC2
	if( Data[0]!=0xC2 )
	{
		if( Data[0]==0x00 ) return false;
		sprintf(m_szErrorText,"�յ����ݵĵ�һ���ֽڷǷ�[%s]!",(char*)m_Data.BcdToAsc(Data,DataLen,temp));
		//m_pDialog->AddString(str,true);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		Sleep(50);
		return false;
	}
	
	//������һ���ֽ��Ƿ�Ϊ0xC3
	if( Data[DataLen-1]!=0xC3 )
	{
		sprintf(m_szErrorText,"�յ����ݵ�β�ֽڷǷ�[%s]!",(char*)m_Data.BcdToAsc(Data,DataLen,temp));
		//m_pDialog->AddString(str,true);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		Sleep(50);
		return false;
	}	
	//У��CRC
	if( m_Data.CRC_CCITT((BYTE)DataLen-1,Data,out) )
	{
		sprintf(m_szErrorText,"CRCУ��ʧ��[%s]!",(char*)m_Data.BcdToAsc(Data,DataLen,temp));	
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		//m_pDialog->AddString(str,true);
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		return false;
	}
	
	if( !memcmp(m_MacCode,MACHINE_TYPE_5301,2) )
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �������ݰ�[%s,��ʱ:%ld ����]!",
			m_Data.HexToInt((BYTE*)m_regno,4),
			m_IpPar.cIPAddress,
			GetTickCount()-m_nStartTime);
	}
	else
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �������ݰ�[%s,��ʱ:%ld ����]!",
			m_Data.HexToInt(m_SmartPos[m_SmartPosPostion].ucRegNo,4),
			m_IpPar.cIPAddress,
			GetTickCount()-m_nStartTime-15);
	}
	if( !m_pDialog->m_check_depart.GetCheck() )
	{
		m_pDialog->AddString(m_szErrorText);
	}
	return true;
}

/*=============================================================
* Function ID :  DealWithRecvData
* Input       :  SMARTCOMMPACK* Doc, BYTE* RecvData
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�յ���������Ч  false��ʾ��Ч
* Description :  �����յ�������
* Notice	  :  
*=================================================================*/
bool CSmart::DealWithRecvData(SMARTCOMMPACK* Doc, BYTE* RecvData)
{
	char  str[128];

	memset(str,0x00,sizeof str);

	if( RecvData[2]!=0x00 )
	{
		m_nTaskResultStatus=RecvData[2];
		sprintf(m_szErrorText,"�ն˵ķ���״̬:%02X",RecvData[2]);		
		return false;
	}
	else
	{
		//�յ�����Ч���ݳ���
		Doc->nRecDataLen=RecvData[3];
		//�յ�����Ч����
		if( Doc->nRecDataLen )
		{		
			memcpy(Doc->ucRecData,RecvData+4,Doc->nRecDataLen);
		}
	}
	return true;
}

/*=================================================================
* Function ID :  Smt_QueryDeviceStatus
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  �ɼ���¼
* Notice	  :  
*=================================================================*/
bool CSmart::Smt_QueryDeviceStatus()
{
	int 	SendLen=0,i=0;
	long    nMaxTimeOut=0,nMinTimeOut=0;
	byte	OutData[1024],ucSndData[128];
	int		nMaxMacNo=0,nMinMacNo=0;

	memset(ucSndData,0,sizeof ucSndData);	
	memset(OutData,  0,sizeof OutData  );
		
	//�õ��ȴ�ʱ��
	if( m_nTotalPos<2 )
	{
		if( m_SmartPos[0].nCommunicationStatus!=0x0A )
		{
			m_SmartPos[0].nCommunicationStatus=0x0C;
		}
		nMaxTimeOut=m_SmartPos[0].ucMacNo*QUERYWAITFORTIMEBASE;
		if( nMaxTimeOut<60*QUERYWAITFORTIMEBASE )
		{
			nMaxTimeOut=60*QUERYWAITFORTIMEBASE;
		}
		nMinTimeOut=nMaxTimeOut;
		m_nMaxMacNo=m_SmartPos[0].ucMacNo;
	}
	else
	{
		nMaxMacNo=m_SmartPos[0].ucMacNo;
		nMinMacNo=m_SmartPos[0].ucMacNo;
		if( m_SmartPos[0].nCommunicationStatus!=0x0A )
		{
			m_SmartPos[0].nCommunicationStatus=0x0C;
		}		
		for(  i=1; i<m_nTotalPos; i++)
		{
			if( m_SmartPos[i].nCommunicationStatus!=0x0A )
			{		
				m_SmartPos[i].nCommunicationStatus=0x0C;
			}
			if( m_SmartPos[i].ucMacNo>nMaxMacNo)
			{
				nMaxMacNo=m_SmartPos[i].ucMacNo;
			}
			if( m_SmartPos[i].ucMacNo<nMinMacNo)
			{
				nMinMacNo=m_SmartPos[i].ucMacNo;
			}
		}
		m_nMaxMacNo=nMaxMacNo;
		nMaxTimeOut=nMaxMacNo*QUERYWAITFORTIMEBASE;
		nMinTimeOut=nMinMacNo*QUERYWAITFORTIMEBASE;
		if( nMaxTimeOut<60*QUERYWAITFORTIMEBASE ) nMaxTimeOut=60*QUERYWAITFORTIMEBASE;
		if( nMinTimeOut<60*QUERYWAITFORTIMEBASE ) nMinTimeOut=60*QUERYWAITFORTIMEBASE;
	}
	m_nStartTime=GetTickCount();
	SendLen=7;
	memcpy(OutData,"\xC0\x00\xF1\x00\x3F\xE6\xC1",SendLen); //��ѯ�豸״̬���ݰ�
	if( !PostSend((char*)OutData,SendLen,nMaxTimeOut))	return false;
	if( nMaxTimeOut<200) nMaxTimeOut=200;
	Sleep(nMaxTimeOut+55);
	if( !RecvQueryData(OutData,&SendLen,nMaxTimeOut) ) 
	{
		m_nQueryFailCount++;
		sprintf(m_szErrorText,"δ�յ��ն�-->%08X �������ݰ�(��ѯ״̬)[%s,��ʱ:%ld ����]!",		
			m_Data.HexToInt((byte*)m_IDNo,4),
			m_IpPar.cIPAddress,
			GetTickCount()-m_nStartTime);
		if( !m_pDialog->m_check_depart.GetCheck() )
		{
			m_pDialog->AddString(m_szErrorText);
		}
		Sleep(50);
		//���Ӳ�ѯ�涨����û���յ����ݰ�,˵�������Ѿ��Ͽ�,������
		if( m_nQueryFailCount>20 ) 
		{
			ReConnect();
			Sleep(1000);
			m_nQueryFailCount=0;
		}
		return false;
	}
	m_nQueryFailCount=0;

#if 0
	//��������Ļ�ϴ�ӡ��ѯ�����豸״̬
	memset(m_szErrorText,0,sizeof m_szErrorText);
	m_Data.BcdToAsc(OutData,SendLen,(byte*)m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
#endif
	sprintf(m_szErrorText,"���յ��ն�-->%08X �������ݰ�(��ѯ״̬)[ %s,��ʱ:%ld ���� %03ld<->%03ld ]",
		m_Data.HexToInt((byte*)m_IDNo,4),	
		m_IpPar.cIPAddress,
		GetTickCount()-m_nStartTime,
		m_nTotalPos,
		SendLen/3);
	if( !m_pDialog->m_check_depart.GetCheck() )	
	{
		m_pDialog->AddString(m_szErrorText);
	}
	for( int j=0; j<SendLen; j++ )
	{		
		if( (int)OutData[j]==(int)0xC2)
		{
			for( i=0; i<m_nTotalPos; i++)
			{
				if( (int)m_SmartPos[i].ucMacNo==(int)OutData[j+1] )
				{
					m_SmartPosPostion=i;
					m_SmartPos[i].nCommunicationStatus=(int)OutData[j+2];  //״̬
					if( (int)OutData[j+2]==(int)0x1B )						//��������
					{
						if(SMT_ListRequestConfirm(i) )
						{
							m_SmartPos[i].nCommunicationStatus=0x1F;
							break;
						}
					}
					break;
				}
			}
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_ListRequestConfirm
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  
* Description :  ��������ȷ��
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_ListRequestConfirm(int nPostion)
{
	byte OutData[512];
	
	memset(OutData,0,sizeof OutData);
	
	for( int i=0; i<2; i++ )
	{	
		memset(OutData,0,sizeof OutData);
		if( !PostSend((char*)m_SmartPos[nPostion].ucSendData,m_SmartPos[nPostion].nSndLen, SMT_WAITFORTIME2) )
		{
			return false;
		}
		Sleep(2*SMT_WAITFORTIME1);
		if( !PostRecv((char*)OutData, sizeof(OutData)/2, SMT_WAITFORTIME2) )
		{
			Sleep(50);
			continue;
		}
		//������ݰ��������Ժ���Ч��
		if( !ValidateData(OutData,m_nReadBytes) )
		{
			continue;
		}
		//������ݰ��Ļ����Ƿ���ȷ
		if( OutData[1] != m_SmartPos[nPostion].ucMacNo)
		{
			continue;
		}
		//����յ������ݰ��������峤��Ϊ��,��ʾ�յ��Ĳ��������
		if( OutData[3]==0x00 ) 
		{
			Sleep(50);
			continue;
		}
		return SMT_RequestConsume(OutData+4,nPostion);
	}
	return false;
}


/*=================================================================
* Function ID :  SMT_ContinueCollectData
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  �ɼ���¼
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_ContinueCollectData( int nPostion)
{
	int  i=0,nLen=0;
	byte OutData[512];

	memset(OutData,0,sizeof OutData);
	
	//ˮ�صĲ������ɼ�
	if( !memcmp(MACHINE_TYPE_0244,m_SmartPos[nPostion].ucpMachineCode,2)||
		!memcmp(MACHINE_TYPE_0245,m_SmartPos[nPostion].ucpMachineCode,2) )
	{
		return false;
	}
	Sleep(80);
	for( i=0; i<10; i++ )
	{
		memset(OutData,0,sizeof OutData);
		nLen=m_SmartPos[nPostion].nSndLen;
		memcpy(OutData,m_SmartPos[nPostion].ucSendData,nLen);		
		if( !PostSend((char*)OutData, nLen, SMT_WAITFORTIME2) )
		{
			return ReConnect();
		}
		Sleep(SMT_WAITFORTIME1*1.5);	
		memset(OutData,0,sizeof OutData);
		if( !PostRecv((char*)OutData, sizeof(OutData)/2, SMT_WAITFORTIME2*3) )
		{
			Sleep(100);
			continue;
		}
		//������ݰ��������Ժ���Ч��
		if( !ValidateData(OutData,m_nReadBytes) )
		{
			return false;
		}
		if( OutData[2]!=0x00 ) return false;
		memset(m_ucReadBytes,0x00,sizeof m_ucReadBytes);
		if( OutData[3] < 28 )  return false;
		if( !SMT_RequestUpConsumeRecord( OutData+4,OutData[3],nPostion) )
		{
			return false;
		}
	}
	return true;	
}

/*=================================================================
* Function ID :  Smt_CollectDataProcess
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  �ɼ���¼
* Notice	  :  
*=================================================================*/
bool CSmart::Smt_CollectDataProcess()
{
	return Smt_ShowerDataProcess();
}

/*=================================================================
* Function ID :  Smt_WLportDataProcess
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  WLPORT���ݲɼ�
* Notice	  :  
*=================================================================*/	
bool CSmart::Smt_WLportDataProcess()
{
	bool   result=false;
	int		i=0,nSleep=0;
	BYTE	OutData[1024];
	SMARTCOMMPACK Doc;
	
	memset(&Doc,0,sizeof Doc);
	memset(OutData,0,sizeof OutData);

	SMT_VerifyClock();//��ʱУ��ʱ��	
	for( i=0; i<m_nTotalPos; i++)//��ѯ����״̬
	{
		if( !memcmp(MACHINE_TYPE_0244,m_MacCode,2) || !memcmp(MACHINE_TYPE_0245,m_MacCode,2) )
		{
			if( QUERYWAY )	//�豸״̬Ϊ����������ʹ�á��豸��ͨ���豸������
			{
				if( m_SmartPos[i].nCommunicationStatus==0x0A ||
					m_SmartPos[i].nCommunicationStatus==0x1F ||
					m_SmartPos[i].nCommunicationStatus==0x0C  )
				{
					continue;
				}
			}
		}
		memset(OutData,0x00,sizeof OutData);
		if( !g_StartFlag )		break;		//�յ�ֹͣ����
		m_nStartTime  = GetTickCount();
		m_nActionTime = GetTickCount();		//���豸ͨѶ�Ҳ������ݿ���ʼʱ��		
		m_SmartPosPostion = i;
		if( !PostSend((char*)m_SmartPos[i].ucSendData, m_SmartPos[i].nSndLen, SMT_WAITFORTIME2) )
		{
			m_pDialog->AddString(m_szErrorText);
			if( nCommunicationStatus!=0xFF)
			{
				nCommunicationStatus=0xFF;	//��ʾ����������ͨѶ
			}
			if( m_SmartPos[i].nCommunicationStatus!=0xFF )
			{
				m_SmartPos[i].nCommunicationStatus=0xFF;
			}
			m_SmartPos[i].nNotCommCount++;
			//���粻ͨ������������
			return SMT_ReConnectServer();
		}
		if( memcmp(MACHINE_TYPE_0244,m_SmartPos[i].ucpMachineCode,2)&&
			memcmp(MACHINE_TYPE_0245,m_SmartPos[i].ucpMachineCode,2) )
		{
			if( m_nTotalPos<=1 )	  Sleep(150);
			else if( m_nTotalPos==2 ) Sleep(75);
			else if( m_nTotalPos==3 ) Sleep(50);
			else					  Sleep(SMT_WAITFORTIME1);			
		}
		else
		{
			Sleep(SMT_WAITFORTIME1);
		}		
		if( !PostRecv((char*)OutData, sizeof(OutData)/2, SMT_WAITFORTIME2) )
		{
			sprintf(m_szErrorText,"δ�յ��ն�-->%.8X ����-%03ld �������ݰ�[%s ��ʱ: %ld ����]",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),(int)m_SmartPos[i].ucMacNo,m_IpPar.cIPAddress,GetTickCount()-m_nActionTime);
			if( g_IniFilePara.bWriteDebugLog )		m_pDialog->AddString(m_szErrorText);
			if( g_IniFilePara.bWriteDebugLog )		WriteLog(m_szErrorText);
			//��ʾ�÷������µĸ��ն˻�����ͨѶ
			if( m_SmartPos[i].nCommunicationStatus!=0xFF)
			{
				m_SmartPos[i].nCommunicationStatus=0xFF;
			}
			m_SmartPos[i].nNotCommCount++;
			if( m_SmartPos[i].nNotCommCount-MNCONTINUETIMES>0 )
			{
				m_SmartPos[i].nNotCommCount=0;
				SMT_ProcessMACError(i);//���û���
			}
			continue;
		}
		m_SmartPos[i].nNotCommCount=0;
		//������ݰ��������Ժ���Ч��
		if( !ValidateData(OutData,m_nReadBytes) )
		{
			continue;
		}
		//������ݰ��Ļ����Ƿ���ȷ
		if( OutData[1] != m_SmartPos[i].ucMacNo)
		{
			sprintf(m_szErrorText,"���յ��ն�-->%.8X ����-%03ld �������ݰ�,���Ų���(�յ�����->%ld)[%s ��ʱ: %ld ����]",
				m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),
				(int)m_SmartPos[i].ucMacNo,
				OutData[1],
				m_IpPar.cIPAddress,
				GetTickCount()-m_nActionTime);
			m_pDialog->AddString(m_szErrorText);
			if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
			continue;
		}
		//���ݰ��е�״̬������Ӧ�����ݴ���
		switch(m_SmartPos[i].nCommunicationStatus=OutData[2] )
		{
			case 0x00:		//�ϴ����׼�¼			
				memset(m_ucReadBytes,0x00,sizeof m_ucReadBytes);
				if( OutData[3] < 28 ) break; //���ݳ��Ȳ���ȷ,�򲻴���
				SMT_RequestUpConsumeRecord( OutData+4,OutData[3],m_SmartPosPostion);
				SMT_ContinueCollectData(i);
				break;
			case 0x79: //������¼
				memset(m_ucReadBytes,0x00,sizeof m_ucReadBytes);
				if( OutData[3] < 35 ) break; //���ݳ��Ȳ���ȷ,�򲻴���
				SMT_RequestUpAssistanRecord( OutData+4,OutData[3],m_SmartPosPostion);				
				break;
			case 0x0D:		//ǩ��(�¹�����Կ)
				SMT_RequestLogin(OutData+4,m_SmartPosPostion);
				break;
			case 0x1B:
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0226,2) ) //�շѻ������첹��
				{
					SMT_RequestAssistant(OutData+4,m_SmartPosPostion);//������������ȷ��
				}
				else
				{
					SMT_RequestConsume(OutData+4,m_SmartPosPostion);//��ԡ��������ȷ��
				}
				break;
			case 0x0B:		//��Ȩ�Ŵ�
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld,��Ȩ�Ŵ�..........",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),m_SmartPos[i].nCommunicationStatus);
				WriteLog(m_szErrorText);
				m_pDialog->AddString(m_szErrorText);	
				SMT_ProcessIDError(m_SmartPosPostion);
				break;
			case 0x30:		//��ֵ�ܶ�����ȷ��, add by dj 20080402
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SETADDTOTALMONEY;
					Doc.nTaskCode=SMT_SETADDTOTALMONEY;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);
					result=SMT_RequestAddMoney(m_SmartPos[i]);
					SMT_InsertTaskResult(Doc,result);
				}
				break;				
			case 0x18://������ֵ��Ȩ��ȷ��	add by dj 20080708
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);

					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);			
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDAUTHTRUE;
					Doc.nTaskCode=SMT_SMARTFRONTADDAUTHTRUE;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);					
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddAuthTrue(m_SmartPos[i]));
				}
				break;
			case 0x10:		//������ֵ����
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDREQUEST;
					Doc.nTaskCode=SMT_SMARTFRONTADDREQUEST;

					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);					
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddRequest(m_SmartPos[i]));
				}
				break;
			case 0x12:		//������ֵ����
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDREQUESTCANCEL;
					Doc.nTaskCode=SMT_SMARTFRONTADDREQUESTCANCEL;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddRequestCancel(m_SmartPos[i]));
				}
				break;
			case 0x0A:
			case 0x1F:	//��ԡ�豸����
			case 0x1E:	//��¼��
			case 0x1D:	//�޷���
				break;
			case 0x1C:	//ú������
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld,ȼ������..........",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),m_SmartPos[i].nCommunicationStatus);
				m_pDialog->AddString(m_szErrorText);
				break;
			case 0x17://���ʼ�¼����,���ϴ�
				SMT_SettleAccount(m_SmartPosPostion);	//���ʼ�¼ȷ��
				break;
			default:
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld..........",
					m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),
					m_SmartPos[i].nCommunicationStatus);
				WriteLog(m_szErrorText);
				m_pDialog->AddString(m_szErrorText);
				break;
		}
	}
	return true;
}

/*=================================================================
* Function ID :  Smt_ShowerDataProcess
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  ��ԡ��¼�ռ�
* Notice	  :  
*=================================================================*/	
bool CSmart::Smt_ShowerDataProcess()
{		
	bool   result=false;
	int		i=0,nSleep=0;
	BYTE	OutData[1024];
	SMARTCOMMPACK Doc;
	
	memset(&Doc,0,sizeof Doc);
	memset(OutData,0,sizeof OutData);

	//�Բ�ѯ�豸��ʽ���ն˽��з���
	if( !memcmp(MACHINE_TYPE_0244,m_MacCode,2)||!memcmp(MACHINE_TYPE_0245,m_MacCode,2) )
	{	
		if( QUERYWAY)	Smt_QueryDeviceStatus();
	}	
	SMT_VerifyClock();//��ʱУ��ʱ��	
	for( i=0; i<m_nTotalPos; i++)//��ѯ����״̬
	{
		if( !memcmp(MACHINE_TYPE_0244,m_MacCode,2) || !memcmp(MACHINE_TYPE_0245,m_MacCode,2) )
		{
			if( QUERYWAY )	//�豸״̬Ϊ����������ʹ�á��豸��ͨ���豸������
			{
				if( m_SmartPos[i].nCommunicationStatus==0x0A ||
					m_SmartPos[i].nCommunicationStatus==0x1F ||
					m_SmartPos[i].nCommunicationStatus==0x0C  )
				{
					continue;
				}
			}
		}
		memset(OutData,0x00,sizeof OutData);
		if( !g_StartFlag )		break;		//�յ�ֹͣ����
		m_nStartTime  = GetTickCount();
		m_nActionTime = GetTickCount();		//���豸ͨѶ�Ҳ������ݿ���ʼʱ��		
		m_SmartPosPostion = i;
		if( !PostSend((char*)m_SmartPos[i].ucSendData, m_SmartPos[i].nSndLen, SMT_WAITFORTIME2) )
		{
			m_pDialog->AddString(m_szErrorText);
			if( nCommunicationStatus!=0xFF)
			{
				nCommunicationStatus=0xFF;	//��ʾ����������ͨѶ
			}
			if( m_SmartPos[i].nCommunicationStatus!=0xFF )
			{
				m_SmartPos[i].nCommunicationStatus=0xFF;
			}
			m_SmartPos[i].nNotCommCount++;
			//���粻ͨ������������
			return SMT_ReConnectServer();
		}
		if( memcmp(MACHINE_TYPE_0244,m_SmartPos[i].ucpMachineCode,2)&&
			memcmp(MACHINE_TYPE_0245,m_SmartPos[i].ucpMachineCode,2) )
		{
			if( m_nTotalPos<=1 )	  Sleep(150);
			else if( m_nTotalPos==2 ) Sleep(75);
			else if( m_nTotalPos==3 ) Sleep(50);
			else					  Sleep(SMT_WAITFORTIME1);			
		}
		else
		{
			Sleep(SMT_WAITFORTIME1);
		}		
		if( !PostRecv((char*)OutData, sizeof(OutData)/2, SMT_WAITFORTIME2) )
		{
			sprintf(m_szErrorText,"δ�յ��ն�-->%.8X ����-%03ld �������ݰ�[%s ��ʱ: %ld ����]",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),(int)m_SmartPos[i].ucMacNo,m_IpPar.cIPAddress,GetTickCount()-m_nActionTime);
			if( g_IniFilePara.bWriteDebugLog )		m_pDialog->AddString(m_szErrorText);
			if( g_IniFilePara.bWriteDebugLog )		WriteLog(m_szErrorText);
			//��ʾ�÷������µĸ��ն˻�����ͨѶ
			if( m_SmartPos[i].nCommunicationStatus!=0xFF)
			{
				m_SmartPos[i].nCommunicationStatus=0xFF;
			}
			m_SmartPos[i].nNotCommCount++;
			if( m_SmartPos[i].nNotCommCount-MNCONTINUETIMES>0 )
			{
				m_SmartPos[i].nNotCommCount=0;
				SMT_ProcessMACError(i);//���û���
			}
			continue;
		}
		m_SmartPos[i].nNotCommCount=0;
		//������ݰ��������Ժ���Ч��
		if( !ValidateData(OutData,m_nReadBytes) )
		{
			continue;
		}
		//������ݰ��Ļ����Ƿ���ȷ
		if( OutData[1] != m_SmartPos[i].ucMacNo)
		{
			sprintf(m_szErrorText,"���յ��ն�-->%.8X ����-%03ld �������ݰ�,���Ų���(�յ�����->%ld)[%s ��ʱ: %ld ����]",
				m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),
				(int)m_SmartPos[i].ucMacNo,
				OutData[1],
				m_IpPar.cIPAddress,
				GetTickCount()-m_nActionTime);
			m_pDialog->AddString(m_szErrorText);
			if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
			continue;
		}
		//���ݰ��е�״̬������Ӧ�����ݴ���
		switch(m_SmartPos[i].nCommunicationStatus=OutData[2] )
		{
			case 0x00:		//�ϴ����׼�¼			
				memset(m_ucReadBytes,0x00,sizeof m_ucReadBytes);
				if( OutData[3] < 28 ) break; //���ݳ��Ȳ���ȷ,�򲻴���
				SMT_RequestUpConsumeRecord( OutData+4,OutData[3],m_SmartPosPostion);
				SMT_ContinueCollectData(i);
				break;
			case 0x79: //������¼
				memset(m_ucReadBytes,0x00,sizeof m_ucReadBytes);
				if( OutData[3] < 35 ) break; //���ݳ��Ȳ���ȷ,�򲻴���
				SMT_RequestUpAssistanRecord( OutData+4,OutData[3],m_SmartPosPostion);				
				break;
			case 0x0D:		//ǩ��(�¹�����Կ)
				SMT_RequestLogin(OutData+4,m_SmartPosPostion);
				break;
			case 0x1B:
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0226,2) ) //�շѻ������첹��
				{
					SMT_RequestAssistant(OutData+4,m_SmartPosPostion);//������������ȷ��
				}
				else
				{
					SMT_RequestConsume(OutData+4,m_SmartPosPostion);//��ԡ��������ȷ��
				}
				break;
			case 0x0B:		//��Ȩ�Ŵ�
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld,��Ȩ�Ŵ�..........",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),m_SmartPos[i].nCommunicationStatus);
				WriteLog(m_szErrorText);
				m_pDialog->AddString(m_szErrorText);	
				SMT_ProcessIDError(m_SmartPosPostion);
				break;
			case 0x30:		//��ֵ�ܶ�����ȷ��, add by dj 20080402
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SETADDTOTALMONEY;
					Doc.nTaskCode=SMT_SETADDTOTALMONEY;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);
					result=SMT_RequestAddMoney(m_SmartPos[i]);
					SMT_InsertTaskResult(Doc,result);
				}
				break;				
			case 0x18://������ֵ��Ȩ��ȷ��	add by dj 20080708
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);

					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);			
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDAUTHTRUE;
					Doc.nTaskCode=SMT_SMARTFRONTADDAUTHTRUE;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);					
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddAuthTrue(m_SmartPos[i]));
				}
				break;
			case 0x10:		//������ֵ����
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDREQUEST;
					Doc.nTaskCode=SMT_SMARTFRONTADDREQUEST;

					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);					
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddRequest(m_SmartPos[i]));
				}
				break;
			case 0x12:		//������ֵ����
				if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0201,2) )
				{
					memset(&Doc,0,sizeof Doc);
					memcpy(m_SmartPos[i].ucSendData,OutData+4,OutData[3]);
					Doc.nFlag	 =1;
					Doc.nAcction =SMT_SMARTFRONTADDREQUESTCANCEL;
					Doc.nTaskCode=SMT_SMARTFRONTADDREQUESTCANCEL;
					memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
					memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
					memcpy(Doc.ucpMachineCode,m_SmartPos[i].ucpMachineCode,2);
					SMT_InsertTaskResult(Doc,SMT_SmartFrontAddRequestCancel(m_SmartPos[i]));
				}
				break;
			case 0x0A:
			case 0x1F:	//��ԡ�豸����
			case 0x1E:	//��¼��
			case 0x1D:	//�޷���
				break;
			case 0x1C:	//ú������
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld,ȼ������..........",m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),m_SmartPos[i].nCommunicationStatus);
				m_pDialog->AddString(m_szErrorText);
				break;
			case 0x17://���ʼ�¼����,���ϴ�
				SMT_SettleAccount(m_SmartPosPostion);	//���ʼ�¼ȷ��
				break;
			default:
				sprintf(m_szErrorText,"�յ��豸[%.8X]���ص�״̬��:%ld..........",
					m_Data.HexToInt(m_SmartPos[i].ucpIDNo,4),
					m_SmartPos[i].nCommunicationStatus);
				WriteLog(m_szErrorText);
				m_pDialog->AddString(m_szErrorText);
				break;
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_RequestAssistant
* Input       :  BYTE *RespData,int nPosition
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �շѻ��豸��������
* Notice	   :  
*				
*=================================================================*/
bool CSmart::SMT_RequestAssistant( BYTE *RespData,int nPosition)
{		
	sprintf(m_szErrorText,"���յ��ն�-->%.8X CardNo-->%ld �շѻ���������ȷ������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3));
	m_pDialog->AddString(m_szErrorText);	
	
	//���ÿ��Ƿ�Ϊ��Ч
	if( SMT_CheckCardWhetherAssistant(RespData,nPosition) )
	{		
		sprintf(m_szErrorText,"��ȷ���ն�-->%.8X CardNo-->%ld ���κ�-->%ld �ز�������,�����첹��",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3),m_Data.HexToInt(RespData+3,2));
	}
	else
	{	
		sprintf(m_szErrorText,"��ȷ���ն�-->%.8X CardNo-->%ld ���κ�-->%ld �ز�������,�����첹��",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3),m_Data.HexToInt(RespData+3,2));
		SMT_AssistantListCofirm(nPosition, 0,0,0);
	}
	m_pDialog->AddString(m_szErrorText);
	if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);	
	return true;	
}

/*=================================================================
* Function ID  :  SMT_RequestAddMoney
* Input        :  
* Output       :  void
* Author       :  
* Date         :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description  :  ��ȡ��ֵ�ܶ�
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_RequestAddMoney( SMARTPOS sPos)	
{	
	int				nMoney=0;
	int				nSysBatchNo=0;
	char			sBuf[20];
	SMARTCOMMPACK	Doc;

	memset(&Doc,0,sizeof Doc);
	memset(sBuf,0,sizeof sBuf);
	
	sprintf(m_szErrorText,"�豸-->%08X��ʼ����˴������ֵ���",m_Data.HexToInt(sPos.ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	//����˴��ȡ�ÿ�Ƭ�Ĳ������
	if( !g_CInterface.SMT_RequestAddMoney(sPos.ucpIDNo,&nMoney,&nSysBatchNo))
	{
		sprintf(m_szErrorText,"�豸-->%08X����˴������ֵ���ʧ��(%s)",m_Data.HexToInt(sPos.ucpIDNo,4),g_CInterface.m_szText);
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		return false;
	}

	m_Data.IntToHex(nMoney,sBuf);
	Doc.ucSndData[0]=sBuf[3];
	Doc.ucSndData[1]=sBuf[2];
	Doc.ucSndData[2]=sBuf[1];
	Doc.nFlag		=1;	
	Doc.nSndDataLen	=3;
	Doc.nAcction	=SMT_SETADDTOTALMONEY;
	Doc.nTaskCode	=SMT_SETADDTOTALMONEY;
	Doc.ucMacNo		=sPos.ucMacNo;
	memcpy(Doc.ucpIDNo,sPos.ucpIDNo,4);
	memcpy(Doc.ucRegNo,sPos.ucRegNo,4);
	memcpy(Doc.ucpMachineCode,sPos.ucpMachineCode,2);	
	if( !SMT_SetAddTotalMoney(&Doc) )
	{
		sprintf(m_szErrorText,"�豸-->%08X���ó�ֵ���ʧ��(���->%ld��)",m_Data.HexToInt(sPos.ucpIDNo,4),nMoney);
	}
	else
	{
		sprintf(m_szErrorText,"�豸-->%08X���ó�ֵ���ɹ�(���->%ld��)",m_Data.HexToInt(sPos.ucpIDNo,4),nMoney);
	}	
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	return true;
}


/*=================================================================
* Function ID  :  SMT_SmartFrontAddAuthTrue
* Input        :  
* Output       :  void
* Author       :  
* Date         :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description  :  ������ֵ��Ȩ��ȷ��
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_SmartFrontAddAuthTrue( SMARTPOS sPos)	
{		
	char			sBuf[20];
	SMARTCOMMPACK	Doc;

	memset(&Doc,0,sizeof Doc);
	memset(sBuf,0,sizeof sBuf);
	
	sprintf(m_szErrorText,"�豸-->%08X��ʼ����˴�������Ȩ��ȷ��",m_Data.HexToInt(sPos.ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	
	if( !g_CInterface.SMT_SmartFrontAddAuthTrue(sPos.ucpIDNo,sPos.ucSendData) )
	{
		sprintf(m_szErrorText,"�豸-->%08X����˴�������Ȩ��ȷ��ʧ��(%s)",m_Data.HexToInt(sPos.ucpIDNo,4),g_CInterface.m_szText);
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		Doc.ucSndData[0]=0x00;
	}
	else
	{
		Doc.ucSndData[0]=0x01;
	}

	//���׿���	
	Doc.ucCmd		=0x9F;
	Doc.nFlag		=1;	
	Doc.nSndDataLen	=1;
	Doc.nAcction	=SMT_SMARTFRONTADDAUTHTRUE;
	Doc.nTaskCode	=SMT_SMARTFRONTADDAUTHTRUE;
	Doc.ucMacNo		=sPos.ucMacNo;
	memcpy(Doc.ucpIDNo,sPos.ucpIDNo,4);
	memcpy(Doc.ucRegNo,sPos.ucRegNo,4);
	memcpy(Doc.ucpMachineCode,sPos.ucpMachineCode,2);
	if( !SMT_ExecuteCmd411(&Doc) )
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն�ȷ����Ȩ��ʧ��",m_Data.HexToInt(sPos.ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		return false;
	}
	else
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն�ȷ����Ȩ���ɹ�",m_Data.HexToInt(sPos.ucpIDNo,4));
	}	
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	return true;
}

/*=================================================================
* Function ID  :  SMT_SmartFrontAddRequest
* Input        :  
* Output       :  void
* Author       :  
* Date         :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description  :  ������ֵ����
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_SmartFrontAddRequest( SMARTPOS sPos)	
{		
	char			sBuf[20];
	SMARTCOMMPACK	Doc;

	memset(&Doc,0,sizeof Doc);
	memset(sBuf,0,sizeof sBuf);
	
	sprintf(m_szErrorText,"�豸-->%08X��ʼ����˴������ֵ����",m_Data.HexToInt(sPos.ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	
	if( !g_CInterface.SMT_SmartFrontAddRequest(sPos.ucpIDNo,sPos.ucSendData) )
	{
		sprintf(m_szErrorText,"�豸-->%08X����˴������ֵ����ʧ��(%s)",m_Data.HexToInt(sPos.ucpIDNo,4),g_CInterface.m_szText);
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		Doc.ucSndData[0]=0x01;
	}
	else
	{
		Doc.ucSndData[0]=0x00;
	}
	//���׿���,�������
	memcpy(Doc.ucSndData+1,sPos.ucSendData,6);
	Doc.ucCmd		=0x40;
	Doc.nFlag		=1;
	Doc.nSndDataLen	=7;
	Doc.nAcction	=SMT_SMARTFRONTADDREQUEST;
	Doc.nTaskCode	=SMT_SMARTFRONTADDREQUEST;
	Doc.ucMacNo		=sPos.ucMacNo;
	memcpy(Doc.ucpIDNo,sPos.ucpIDNo,4);
	memcpy(Doc.ucRegNo,sPos.ucRegNo,4);
	memcpy(Doc.ucpMachineCode,sPos.ucpMachineCode,2);
	if( !SMT_ExecuteCmd411(&Doc) )	
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն˳�ֵ����ʧ��",m_Data.HexToInt(sPos.ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		return false;
	}
	else
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն˳�ֵ����ɹ�",m_Data.HexToInt(sPos.ucpIDNo,4));
	}
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	return true;
}

/*=================================================================
* Function ID  :  SMT_SmartFrontAddRequestCancel
* Input        :  
* Output       :  void
* Author       :  
* Date         :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description  :  ������ֵ����
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_SmartFrontAddRequestCancel( SMARTPOS sPos)	
{		
	char			sBuf[20];
	SMARTCOMMPACK	Doc;

	memset(&Doc,0,sizeof Doc);
	memset(sBuf,0,sizeof sBuf);
	
	sprintf(m_szErrorText,"�豸-->%08X��ʼ����˴�������ֵ����",m_Data.HexToInt(sPos.ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	
	if( !g_CInterface.SMT_SmartFrontAddRequestCancel(sPos.ucpIDNo,sPos.ucSendData) )
	{
		sprintf(m_szErrorText,"�豸-->%08X����˴�������ֵ����ʧ��(%s)",m_Data.HexToInt(sPos.ucpIDNo,4),g_CInterface.m_szText);
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		Doc.ucSndData[0]=0x01;
	}
	else
	{
		Doc.ucSndData[0]=0x00;
	}

	//���׿��� �������
	memcpy(Doc.ucSndData+1,sPos.ucSendData,6);
	Doc.ucCmd		=0x40;
	Doc.nFlag		=1;	
	Doc.nSndDataLen	=7;
	Doc.nAcction	=SMT_SMARTFRONTADDREQUESTCANCEL;
	Doc.nTaskCode	=SMT_SMARTFRONTADDREQUESTCANCEL;
	Doc.ucMacNo		=sPos.ucMacNo;
	memcpy(Doc.ucpIDNo,sPos.ucpIDNo,4);
	memcpy(Doc.ucRegNo,sPos.ucRegNo,4);
	memcpy(Doc.ucpMachineCode,sPos.ucpMachineCode,2);

	if( !SMT_ExecuteCmd411(&Doc) )
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն�������ֵ����ʧ��",m_Data.HexToInt(sPos.ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		return false;
	}
	else
	{
		sprintf(m_szErrorText,"�豸-->%08X���ն�������ֵ�����ɹ�",m_Data.HexToInt(sPos.ucpIDNo,4));
	}
	m_pDialog->AddString(m_szErrorText);
	WriteLog(m_szErrorText);
	return true;
}

/*=================================================================
* Function ID  :  SMT_CheckCardWhetherAssistant
* Input        :  BYTE *cCardNo
* Output       :  void
* Author       :  
* Date         :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description  :  ����Ƿ�����첹��
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_CheckCardWhetherAssistant(BYTE *cCardNo,int nPosition)	
{	
	bool bRet=false;
	byte buffer[128];
	int nCardNo,nBatchNo=0,nMoney=0;
	int nSysBatchNo=0;

	memset(buffer,0,sizeof buffer);
	//1.���ÿ�Ƭ�Ƿ������첹��
	memcpy(buffer,cCardNo,5);
	memcpy(buffer+5,m_SmartPos[nPosition].ucpIDNo,4);
	nCardNo=m_Data.HexToInt(buffer,3);
	nBatchNo=m_Data.HexToInt(buffer+3,2);
	bRet=SMT_CheckWhetherAssistantCard(nCardNo,nBatchNo);	
#if 1
	if( !bRet ) return bRet;
	//����˴��ȡ�ÿ�Ƭ�Ĳ������
	bRet=g_CInterface.SMT_CheckWhetherAssistant(buffer,&nMoney,&nSysBatchNo);
	if( !bRet ) return bRet;
	if( nBatchNo>=nSysBatchNo )  //�������κŴ��ڵ��ڽ��˴��̨�����κ�
	{
		return false;
	}
#else //test 20080130
	nMoney     =0;
	nSysBatchNo=nBatchNo;
	nSysBatchNo++;
#endif
	//���ն�ȷ���Ƿ�����첹��
	return SMT_AssistantListCofirm(nPosition,nCardNo,nSysBatchNo,nMoney);	
}

/*=================================================================
* Function ID :  SMT_AssistantListCofirm
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����ȷ��
* Notice	   :  ��������ȷ��
*					
////�Ӽ�Ǯ���(0---�ӣ�1---��)
*=================================================================*/
bool CSmart::SMT_AssistantListCofirm(int nPosition, int nCardNo,int nBatchNo,int nMoney)
{		
	byte			ucCRC[5],sStr[20];
	char			sBuffer[128];
	byte			sType=0,sData[64],OutData[128];
	char			sMoney[30];
	SMARTCOMMPACK	Doc;
			
	memset(sBuffer,0,sizeof sBuffer);
	memset(OutData,0,sizeof OutData);
	memset(sData,  0,sizeof sData);
	memset(ucCRC,  0,sizeof ucCRC);
	memset(sStr,   0,sizeof sStr);
	memset(&Doc,   0,sizeof Doc);
	memset(sMoney, 0,sizeof sMoney);
	
	if( nMoney>=0 )
	{
		sType=0x00;
	}
	else
	{
		sType=0x01;
		sprintf(sMoney,"%ld",nMoney);
		nMoney=atol(sMoney+1);
	}

	Doc.nFlag      =0x01;
	Doc.ucCmd      =0x7A;		
	Doc.nSndDataLen=0x0F;
	memset(sBuffer,0,sizeof sBuffer);
	memcpy(sData,m_Data.IntToHex(nCardNo,sBuffer)+1,3);		//����
	memset(sBuffer,0,sizeof sBuffer);
	memcpy(sData+3,m_Data.IntToHex(nBatchNo,sBuffer)+2,2);	//���κ�
	memset(sBuffer,0,sizeof sBuffer);
	memcpy(sStr,m_Data.IntToHex(nMoney,sBuffer),4);			//�������
	sData[5]=sStr[3];
	sData[6]=sStr[2];
	sData[7]=sType;
	m_Data.CRC_CCITT(8,sData,ucCRC);
	sData[8]=ucCRC[0];
	sData[9]=ucCRC[1];
	memset(sStr,0,sizeof sStr);
	for( int i=0; i<5; i++ )
	{
		sStr[i]=0xFF-sData[3+i];
	}
	memcpy(sData+10,sStr,5);
	Doc.ucMacNo = m_SmartPos[nPosition].ucMacNo;
	memcpy(Doc.ucSndData,sData,Doc.nSndDataLen);
	memcpy(Doc.ucRegNo,  m_SmartPos[nPosition].ucRegNo,4);
	memcpy(Doc.ucpIDNo,  m_SmartPos[nPosition].ucpIDNo,4);
	if( nCardNo==0&&nBatchNo==0&&nMoney==0 )
	{
		memset(Doc.ucSndData,0,sizeof Doc.ucSndData);
		Doc.nSndDataLen =0x01;
		Doc.ucSndData[0]=0x01;
	}
	int SendLen=m_Data.BuildData( Doc.ucMacNo,Doc.nFlag,Doc.ucpIDNo, Doc.ucCmd,Doc.nSndDataLen,Doc.ucSndData,OutData,0,NULL);
	return PostSend((char*)OutData, SendLen, 1000);	
}

/*=================================================================
* Function ID :  SMT_SettleAccount
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  �ϴ����ʼ����ʼ�¼ȷ��
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_SettleAccount( int nPosition)
{
	SMARTCOMMPACK Doc;

	memset(&Doc,0,sizeof Doc);

	sprintf(m_szErrorText,"�ն�-> %08X �����ϴ���������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);

	//�ϴ�����
	Doc.nFlag		=1;
	Doc.ucCmd		=0x8C;
	Doc.nSndDataLen	=0;
	Doc.ucMacNo		=m_SmartPos[nPosition].ucMacNo;
	memcpy(Doc.ucpIDNo,m_SmartPos[nPosition].ucpIDNo,4);
	memcpy(Doc.ucRegNo,m_SmartPos[nPosition].ucRegNo,4);
	memcpy(Doc.ucpMachineCode,m_SmartPos[nPosition].ucpMachineCode,2);	
	if( !SMT_ExecuteCmd411(&Doc) ) return false;
	Sleep(250);
	//ȷ�Ͻ���
	Doc.ucCmd=0x8B;
	memcpy(Doc.ucSndData,Doc.ucRecData+6,2);
	Doc.nSndDataLen=2;
	return SMT_ExecuteCmd411(&Doc);
}

/*=================================================================
* Function ID :  SMT_ReConnectServer
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɼ��ɹ�  false��ʾʧ��
* Description :  ������
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_ReConnectServer()
{
	Close();
	Sleep(300);
	if( !Open() )
	{
		WriteLog(m_szErrorText);
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		return false;
	}
	WriteLog(m_szErrorText);
	memset(m_szErrorText,0x00,sizeof m_szErrorText);
	return true;
}

/*=================================================================
* Function ID :  GetDeviceInfo
* Input       :  char *cDeviceID 4�ֽ�
* Output      :  int *nPosition
* Author      :  DengJun
* Date        :  2006 5  30
* Return	  :  true/false
* Description :  
* Notice	  :  �����豸ID���Ҹ��豸�����豸�����е�λ��
*					
*=================================================================*/
bool CSmart::GetDeviceInfo(char *cDeviceID,int *nPosition)
{
	int i=0;
	if( !memcmp(cDeviceID,m_IDNo,4) )
	{
		*nPosition=0;
		return false;
	}
	for( i=0; i<m_nTotalPos; i++ )
	{
		if( !memcmp(m_SmartPos[i].ucpIDNo,cDeviceID,4) )
		{
			*nPosition = i;
			return true;
		}
	}
	*nPosition=0;
	return false;
}

/*=================================================================
* Function ID :  SMT_RequestLogin
* Input       :  BYTE *RespData,int nPosition
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��ԡ�豸ǩ��
* Notice	  :  nPosition  ��ʾ����LPORT�Ķ˿ں�,
*					
*=================================================================*/
bool CSmart::SMT_RequestLogin( BYTE *RespData,int nPosition)
{		
	long	SendLen=0;
	long    nTimeOut=150;
	int		Level=0;
	BYTE	ucTemp[20];
	char	sStr[128];
	int		nTry=0;
	SMARTCOMMPACK	Doc;
	
	memset(sStr,0,sizeof sStr);
	memset(&Doc,  0x00,sizeof Doc);
	memset(ucTemp,0x00,sizeof ucTemp);	
	if( !memcmp(MACHINE_TYPE_0244,m_MacCode,2) ||!memcmp(MACHINE_TYPE_0245,m_MacCode,2) )
	{
		sprintf(m_szErrorText,"�յ���ԡ�ն�-->%.8X ǩ������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		memcpy(Doc.ucpIDNo,m_SmartPos[nPosition].ucpIDNo,4);
		memcpy(Doc.ucRegNo,m_SmartPos[nPosition].ucRegNo,4);
		memcpy(Doc.ucpMachineCode,m_SmartPos[nPosition].ucpMachineCode,2);
		Doc.ucMacNo=m_SmartPos[nPosition].ucMacNo;
		memcpy(Doc.ucSndData,g_sWorkKey,8);
		Doc.ucSndData[8]=g_nWalletNo;
		Doc.nFlag      = 1;
		Doc.nSndDataLen= 9;
		if( !SMT_SetWorkKey(&Doc) ) return false;
	}
	else
	{
		Doc.nFlag=1;
		sprintf(m_szErrorText,"�յ��շ��ն�-->%.8X ǩ������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);	
		//У��ʱ��
		memset(m_szErrorText,0x00,sizeof m_szErrorText);
		memset(Doc.ucSndData,0,sizeof Doc.ucSndData);		
		memcpy(Doc.ucpIDNo,m_SmartPos[nPosition].ucpIDNo,4);
		memcpy(Doc.ucRegNo,m_SmartPos[nPosition].ucRegNo,4);
		memcpy(Doc.ucpMachineCode,m_SmartPos[nPosition].ucpMachineCode,2);
		Doc.ucMacNo=m_SmartPos[nPosition].ucMacNo;
		for( nTry=0;nTry<3;nTry++)
		{		
			if( !SMT_SetClock(&Doc) ) {Sleep(2000);continue;}	
			break;
		}
		if( nTry==3) return false;

		sprintf(m_szErrorText,"�ն�-->%08X ǩ��[����ʱ��]�ɹ�",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);		
		//���ù�����Կ
		Sleep(2000);
		memset(Doc.ucSndData,0,sizeof Doc.ucSndData);
		memcpy(Doc.ucSndData,g_sWorkKey,8);		
		Doc.nSndDataLen=8;
		for( nTry=0;nTry<3;nTry++)
		{
			if( !SMT_SetWorkKey(&Doc) ) {Sleep(2000);continue;}		
			break;
		}
		if( nTry==3) return false;
		
		sprintf(m_szErrorText,"�ն�-->%08X ǩ��[��Ȩ]�ɹ�",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		Sleep(1000);
		//�������ѿ���
		memset(Doc.ucSndData,0,sizeof Doc.ucSndData);
		Doc.ucSndData[0]= 0x01;
		Doc.nSndDataLen = 1;
		for( nTry=0;nTry<3;nTry++)
		{		
			if( !SMT_SetOpenSaleCtrl(&Doc) ) {Sleep(500);continue;}
			break;
		}
		if( nTry==3) 
		{
			strcpy(sStr,m_szErrorText);
			sprintf(m_szErrorText,"�ն�-->%08X ǩ��ʧ��[%s]",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),sStr);
			m_pDialog->AddString(m_szErrorText);
			return false;
		}
	}
	sprintf(m_szErrorText,"�ն�-->%08X ǩ���ɹ�",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4));
	m_pDialog->AddString(m_szErrorText);	
	Sleep(150);
	return true;
}

/*=================================================================
* Function ID :  SMT_SetOpenSaleCtrl
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �����ѿ���
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetOpenSaleCtrl(SMARTCOMMPACK* Doc)
{
	long	SendLen=0;
	long    nTimeOut=2000;
	BYTE	commision[7],OutData[256],InData[256];
	int		Level=0;
	BYTE	Level_Array[4];
	char	str[128];
	int	    nWeek=0;	
	int		nTry=0;
	bool	bol=false;
	
	memset(str,		   0x00,sizeof str   );
	memset(InData,     0x00,sizeof InData);
	memset(OutData,    0x00,sizeof OutData);
	memset(commision,  0x00,sizeof commision);
	memset(Level_Array,0x00,sizeof Level_Array);	
	
	BYTE ucCommandByte = 0x9F;		
	memcpy(commision,Doc->ucRegNo,4);
	
	sprintf(str,"�ն�[%08X]��ʼ�������ѿ���....",m_Data.HexToInt(commision,4));	
	m_pDialog->AddString(str);
	
	Level = 0;			
	memcpy(InData,Doc->ucSndData,Doc->nSndDataLen);
	SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,Doc->nSndDataLen,InData,OutData,Level, Level_Array);
	if( !PostSend((char*)OutData, SendLen, nTimeOut) )
	{
		return false;
	}	
	memset(OutData,0x00,sizeof OutData);
	Sleep(350);
	if( !PostRecv((char*)OutData, 128, nTimeOut) )
	{
		return false;
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{		
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}	
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}	
	return true;
}

/*=================================================================
* Function ID :  SMT_RequestConsume
* Input       :  BYTE *RespData,int nPosition
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��ԡ�豸��������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_RequestConsume( BYTE *RespData,int nPosition)
{		
	int				nTry=1;
	BYTE			ucTmp[30];
	SMARTCOMMPACK	Doc;
	
	memset(&Doc, 0x00,sizeof Doc);
	memset(ucTmp,0x00,sizeof ucTmp);		
	
	sprintf(m_szErrorText,"���յ��ն�-->%.8X CardNo-->%ld ��ԡ���ѽ�������ȷ������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3));
	m_pDialog->AddString(m_szErrorText);	
	
	//���ÿ��Ƿ�Ϊ��Ч
	if( SMT_CheckCardNoAvailability(RespData) )
	{
		ucTmp[0]=0x00;
		sprintf(m_szErrorText,"��ȷ���ն�-->%.8X CardNo-->%ld ����ԡ��������,��������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3));
	}
	else
	{
		ucTmp[0]=0x01;
		sprintf(m_szErrorText,"��ȷ���ն�-->%.8X CardNo-->%ld ����ԡ��������,����������",m_Data.HexToInt(m_SmartPos[nPosition].ucpIDNo,4),m_Data.HexToInt(RespData,3));		
	}
	if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	for( int i=0; i<nTry; i++ )
	{	
		Doc.ucCmd		=0x9F;
		Doc.nFlag		=1;
		Doc.ucMacNo		=m_SmartPos[nPosition].ucMacNo;
		Doc.ucSndData[0]=ucTmp[0];	//�Ƿ������ 0x00 ��  0x01����
		Doc.nSndDataLen	=7;
		memcpy(Doc.ucpIDNo,m_SmartPos[nPosition].ucpIDNo,4);
		memcpy(Doc.ucRegNo,m_SmartPos[nPosition].ucRegNo,4);	
		memcpy(Doc.ucSndData+1,m_Data.GetSysTimeHex(),6);
		if( SMT_ExecuteCmd411(&Doc) ) return true;
		Sleep(50);
	}
	return false;
}

/*=================================================================
* Function ID :  SMT_RequestUpConsumeRecord
* Input       :  BYTE *RespData,int nPostion
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ������ԡ�豸�ϴ��ļ�¼
* Notice	  : 
*=================================================================*/
bool CSmart::SMT_RequestUpConsumeRecord( BYTE *RespData,int nRespDataLen,int nPostion)
{		
	char			sBuffer[256];
	char			sStr[128];
	BYTE			ucFlow[2];
	int				nTry=0;	
	SMARTCOMMPACK	Doc;
	
	memset(sBuffer,	   0x00,sizeof sBuffer);
	memset(ucFlow,	   0x00,sizeof ucFlow);	
	memset(&Doc,	   0x00,sizeof Doc);
	memset(sStr,	   0x00,sizeof sStr);

	m_nStartTime  = GetTickCount();

	//add by dj 20080506
	if( !memcmp(MACHINE_TYPE_0121,m_SmartPos[nPostion].ucpMachineCode,2) ) //��ʱ����
	{
		sprintf(sBuffer,"%04X,%02ld,%s",m_Data.HexToInt(m_SmartPos[nPostion].ucpMachineCode,2),TIMEDATATYPE_FACE,(char*)m_Data.BcdToAsc(RespData,nRespDataLen,(byte*)sStr));		
	}
	else //�Ʒ�����
	{
		sprintf(sBuffer,"%04X,%02ld,%s",m_Data.HexToInt(m_SmartPos[nPostion].ucpMachineCode,2),RECORDDATATYPE_FACE,(char*)m_Data.BcdToAsc(RespData,nRespDataLen,(byte*)sStr));
	}
	
	//д��־���ݲ��ɹ�,��ȷ�ϼ�¼
	if( !WriteTradeDeal(sBuffer) ) return false;	
	//��ˮ��
	memcpy(ucFlow,RespData+6,2);
	sprintf(m_szErrorText,"���յ��ն�-->%.8X ��ˮ��-->%ld ���׼�¼[%s]",m_Data.HexToInt(m_SmartPos[nPostion].ucpIDNo,4),m_Data.HexToInt(ucFlow,2),m_IpPar.cIPAddress);
	m_pDialog->AddString(m_szErrorText);
	if( !memcmp(MACHINE_TYPE_0121,m_SmartPos[nPostion].ucpMachineCode,2) ) //��ʱ����
	{
		
		Doc.ucSndData[0]   = 0x20;
		Doc.ucSndData[1]   = 0xd0;
		Doc.ucSndData[2]   = 0x10;
		Doc.nSndDataLen	= 5;
		memcpy(Doc.ucSndData+3,ucFlow,2);
	}
	else
	{
		Doc.nSndDataLen	= 2;
		memcpy(Doc.ucSndData,ucFlow,2);
	}

	Doc.ucMacNo		= m_SmartPos[nPostion].ucMacNo;	
	memcpy(Doc.ucRegNo,m_SmartPos[nPostion].ucRegNo,4);
	memcpy(Doc.ucpIDNo,m_SmartPos[nPostion].ucpIDNo,4);	

	for( int i=0; i<6; i++ )
	{
		if( SMT_ConfirmData( &Doc) ) return true;
	}
	return false;
}


/*=================================================================
* Function ID :  SMT_RequestUpAssistanRecord
* Input       :  BYTE *RespData,int nPostion
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ������¼
* Notice	  : 
*=================================================================*/
bool CSmart::SMT_RequestUpAssistanRecord( BYTE *sRespData,int nRespDataLen,int nPostion)
{		
	char			sBuffer[256];
	char			sStr[256];
	BYTE			ucFlow[2];
	byte			RespData[256];
	int				nTry=0;	
	int				nInvoiceNo=0;
	SMARTCOMMPACK	Doc;
	
	memset(sBuffer,	   0x00,sizeof sBuffer);
	memset(ucFlow,	   0x00,sizeof ucFlow);	
	memset(RespData,   0x00,sizeof RespData);
	memset(&Doc,	   0x00,sizeof Doc);
	memset(sStr,	   0x00,sizeof sStr);

	memcpy(RespData,sRespData,35);
	m_nStartTime  = GetTickCount();
	
	//��ȡ��ˮ��
	if( !m_Log.SMT_GetLastInvoiceNo((char*)m_SmartPos[nPostion].ucpIDNo, &nInvoiceNo ) )
	{
		sprintf(m_szErrorText,"���յ��ն�-->%.8X �ϴ�������¼,��ȡ��ˮ��ʧ��",m_Data.HexToInt(m_SmartPos[nPostion].ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
		Sleep(1000);
		return false;
	}

	memset(sBuffer,0,sizeof sBuffer);
	memcpy(ucFlow,m_Data.IntToHex(nInvoiceNo,sBuffer)+2,2);
	RespData[6]=ucFlow[0];
	RespData[7]=ucFlow[1];
	
	//д��־���ݲ��ɹ�,��ȷ�ϼ�¼
	sprintf(sBuffer,"%04X,%02ld,%s",m_Data.HexToInt(m_SmartPos[nPostion].ucpMachineCode,2),ASSISTANTDATATYPE_FACE,(char*)m_Data.BcdToAsc(RespData,35,(byte*)sStr));
	if( !WriteTradeDeal(sBuffer) ) return false;	
	sprintf(m_szErrorText,"���յ��ն�-->%.8X ��ˮ��->%ld �ϴ�������¼[%s]",m_Data.HexToInt(m_SmartPos[nPostion].ucpIDNo,4),m_Data.HexToInt(ucFlow,2),m_IpPar.cIPAddress);
	m_pDialog->AddString(m_szErrorText);

	Doc.nSndDataLen	= 0x00;
	Doc.nFlag		= 0x01;
	Doc.ucCmd		= 0x04;
	Doc.ucMacNo		= m_SmartPos[nPostion].ucMacNo;	
	memcpy(Doc.ucRegNo,m_SmartPos[nPostion].ucRegNo,4);
	memcpy(Doc.ucpIDNo,m_SmartPos[nPostion].ucpIDNo,4);	
	memcpy(Doc.ucpMachineCode,m_SmartPos[nPostion].ucpMachineCode,2);
	return SMT_ExecuteCmd411(&Doc);
}

/*=================================================================
* Function ID :  SMT_CheckCardNoAvailability
* Input       :  BYTE *cCardNo
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ��Ч  false��ʾ��Ч
* Description :		��鿨����Ч��
* Notice	   : 
*					
*=================================================================*/
bool CSmart::SMT_CheckCardNoAvailability(BYTE *cCardNo)	
{	
	if( g_CSmartBlackMemoryOper.SMT_CheckBlackCard(m_Data.HexToInt(cCardNo,3)) )
	{
		return false;
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_ConfirmData
* Input       :  int nPosition,int nFlowNo
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��¼ȷ��
* Notice	  :  nPosition  ��ʾ����LPORT�Ķ˿ں�,nFlowNo��ˮ��
*=================================================================*/
bool CSmart::SMT_ConfirmData(SMARTCOMMPACK* Doc)	
{	
	long	SendLen=0;	
	BYTE	OutData[256];
	BYTE    ucCommandByte=0x04;

	memset(OutData,0x00,sizeof OutData);	

	SendLen=m_Data.BuildData( Doc->ucMacNo,1,Doc->ucRegNo, ucCommandByte,Doc->nSndDataLen,Doc->ucSndData,OutData,0, NULL);
	if( !PostSend((char*)OutData, SendLen, SMT_WAITFORTIME2) )
	{
		sprintf(m_szErrorText,"*********************����ȷ������ʧ��[%.8X]",m_Data.HexToInt(Doc->ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);			
		return false;
	}

	memset(OutData,0x00,sizeof OutData);
	Sleep(4*(SMT_WAITFORTIME1+SMT_WAITFORTIME2));
	if( !PostRecv((char*)OutData, 128, 5*(SMT_WAITFORTIME2+SMT_WAITFORTIME1)) )
	{
		sprintf(m_szErrorText,"*********************δ�յ�ȷ������ʧ��[%.8X]",m_Data.HexToInt(Doc->ucpIDNo,4));
		m_pDialog->AddString(m_szErrorText);
		return false;
	}

	if( !ValidateData(OutData,m_nReadBytes) )
	{			
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		m_pDialog->AddString(m_szErrorText);
		return false;
	}

	if( OutData[2] != 0x00 )
	{
		sprintf(m_szErrorText,"�յ�ȷ������״̬��:%s,%02X",GetStatusErrMsg(OutData[2]),OutData[2]);
		m_pDialog->AddString(m_szErrorText);		
		return false;
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_GetClock
* Input       :  int nPosition 
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ȡʱ��
* Notice	   :  nPosition  ��ʾ����LPORT�Ķ˿ں�
*					
*=================================================================*/
bool CSmart::SMT_GetClock(SMARTCOMMPACK* Doc)				//ȡ�ն˻�ʱ��
{		
	long	SendLen=0;
	long    nTimeOut=500;
	BYTE	commision[7],OutData[256],InData[256];
	int		Level=0;
	BYTE	Level_Array[4];
	char	str[128];
	
	memset(str,		   0x00,sizeof str   );
	memset(InData,     0x00,sizeof InData);
	memset(OutData,    0x00,sizeof OutData);
	memset(commision,  0x00,sizeof commision);
	memset(Level_Array,0x00,sizeof Level_Array);

	sprintf(m_szErrorText,"��ʼȡ�ն˻�ʱ��[����:%ld ע���:%s]",Doc->ucMacNo,m_Data.BcdToAsc(Doc->ucRegNo,4,commision));
	if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
	
	BYTE ucCommandByte = 0xAA;		
	if( !memcmp(m_MacCode,MACHINE_TYPE_5301,2))  //W_LPORT
	{	
		Level_Array[0]=m_MacNum;
		Level_Array[1]=(char)Doc->nConnectPortNo;
		Level = 1;	
		memcpy(commision,Doc->ucRegNo,4);	
		SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,0,InData,OutData,Level, Level_Array);
		if( !PostSend((char*)OutData, SendLen, nTimeOut) )
		{
			return false;
		}	
		memset(OutData,0x00,sizeof OutData);
		Sleep(120);
		if( !PostRecv((char*)OutData, 128, nTimeOut) )
		{
			return false;
		}
	}
	else  //Z_LPORT��������V22�շѻ���V23�շѻ�
	{
		Level = 0;	
		memcpy(commision,Doc->ucRegNo,4);	
		SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,0,InData,OutData,Level, Level_Array);
		if( !PostSend((char*)OutData, SendLen, nTimeOut) )
		{
			return false;
		}
		memset(OutData,0x00,sizeof OutData);
		Sleep(35);
		if( !PostRecv((char*)OutData, 128, nTimeOut) )
		{
			return false;
		}
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_ProcessMACError
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  
* Notice	   :  ������Ŵ�
*					
*=================================================================*/
bool CSmart::SMT_ProcessMACError(int nPostion)
{
	SMARTCOMMPACK Doc;

	memset(&Doc,0,sizeof Doc);

	//���û���
	Doc.nFlag		=1;
	Doc.ucCmd		=0xE3;
	Doc.nSndDataLen	=1;
	Doc.ucMacNo     =0xFF;
	memcpy(Doc.ucpIDNo,m_SmartPos[nPostion].ucpIDNo,4);
	memcpy(Doc.ucRegNo,m_SmartPos[nPostion].ucRegNo,4);
	memcpy(Doc.ucpMachineCode,m_SmartPos[nPostion].ucpMachineCode,2);
	Doc.ucSndData[0]=m_SmartPos[nPostion].ucMacNo;
	return SMT_ExecuteCmd411(&Doc);
}

/*=================================================================
* Function ID :  SMT_GetDeviceID
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �õ��豸ID��
* Notice	   :  nPosition  ��ʾ����LPORT�Ķ˿ں�
*					
*=================================================================*/
bool CSmart::SMT_ProcessIDError(int nPostion)
{
	SMARTCOMMPACK Doc;

	memset(&Doc,0,sizeof Doc);

	//��ID��
	Doc.nFlag		=0;
	Doc.ucCmd		=0xE1;
	Doc.nSndDataLen	=0;
	memcpy(Doc.ucpIDNo,m_SmartPos[nPostion].ucpIDNo,4);
	memcpy(Doc.ucRegNo,m_SmartPos[nPostion].ucRegNo,4);
	memcpy(Doc.ucpMachineCode,m_SmartPos[nPostion].ucpMachineCode,2);
	if( !SMT_GetDeviceID(&Doc) ) return false;
	if( memcmp(Doc.ucRecData,Doc.ucpIDNo,4) )
	{
		sprintf(m_szErrorText,"����Ϊ%ld[%s]���豸���е�ID[%.8X]���������ID[%.8X]��һ��,����ID��",
			Doc.ucMacNo,m_IpPar.cIPAddress,m_Data.HexToInt(Doc.ucpIDNo,4),m_Data.HexToInt(Doc.ucRecData,4));
		m_pDialog->AddString(m_szErrorText);
		WriteLog(m_szErrorText);
	}
	//����ID��
	Doc.nFlag		= 0;
	Doc.nSndDataLen	= 4;
	Doc.ucCmd		= 0xE0;
	memcpy(Doc.ucSndData,Doc.ucpIDNo,4);	
	return SMT_SetDeviceID(&Doc);
}

/*=================================================================
* Function ID :  SMT_GetDeviceID
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �õ��豸ID��
* Notice	   :  nPosition  ��ʾ����LPORT�Ķ˿ں�
*					
*=================================================================*/
bool CSmart::SMT_GetDeviceID(SMARTCOMMPACK* Doc)
{		
	long	SendLen=0;
	long    nTimeOut=200;
	BYTE	OutData[256];
	char	str[128];
	
	memset(str,		   0x00,sizeof str   );
	memset(OutData,    0x00,sizeof OutData);
	
	SendLen=m_Data.BuildData( Doc->ucMacNo,Doc->nFlag,Doc->ucpIDNo, 
		Doc->ucCmd,Doc->nSndDataLen,Doc->ucSndData,OutData,0, NULL);
	if( !PostSend((char*)OutData, SendLen, nTimeOut) )	return false;	
	Sleep(50);
	if( !PostRecv((char*)OutData, 128, nTimeOut) )
	{
		return false;
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{		
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}		
	return true;		
}

/*=================================================================
* Function ID :  SMT_SetDeviceID
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����ID��
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetDeviceID(SMARTCOMMPACK* Doc)
{
	long	SendLen=0;
	long    nTimeOut=200;
	BYTE	OutData[256];
	
	memset(OutData,    0x00,sizeof OutData);
	SendLen=m_Data.BuildData( Doc->ucMacNo,Doc->nFlag,Doc->ucpIDNo, 
		Doc->ucCmd,Doc->nSndDataLen	,Doc->ucSndData,OutData,0, NULL);
	if( !PostSend((char*)OutData, SendLen, nTimeOut) )
	{
		return false;
	}
	memset(OutData,0x00,sizeof OutData);
	Sleep(50);
	if( !PostRecv((char*)OutData, 128, nTimeOut) )
	{
		return false;
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}		
	return true;		
}

/*=================================================================
* Function ID :  SMT_Login
* Input       :  SMARTCOMMPACK* Doc
* Output      :  SMARTCOMMPACK* Doc
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ն�ǩ��
* Notice	   :  
*
*=================================================================*/
bool CSmart::SMT_Login(SMARTCOMMPACK* Doc)			
{
	long	SendLen=0;
	long    nTimeOut=500;
	BYTE	commision[7],OutData[256],InData[256];
	int		Level=0;
	BYTE	Level_Array[4];
	char	str[128];
	
	memset(str,		   0x00,sizeof str   );
	memset(InData,     0x00,sizeof InData);
	memset(OutData,    0x00,sizeof OutData);
	memset(commision,  0x00,sizeof commision);
	memset(Level_Array,0x00,sizeof Level_Array);		

	BYTE ucCommandByte = 0x9F;		
	memcpy(commision,Doc->ucRegNo,4);	
	memcpy(InData,Doc->ucSndData,Doc->nSndDataLen);

	if( !memcmp(m_MacCode,MACHINE_TYPE_5301,2))  //W_LPORT
	{	
		Level_Array[0]=m_MacNum;
		Level_Array[1]=(char)Doc->nConnectPortNo;
		Level = 1;			
		SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,Doc->nSndDataLen,InData,OutData,Level, Level_Array);
		if( !PostSend((char*)OutData, SendLen, nTimeOut) )
		{
			return false;
		}	
		memset(OutData,0x00,sizeof OutData);
		Sleep(200);
		if( !PostRecv((char*)OutData, 128, nTimeOut) )
		{
			return false;
		}
	}
	else  //J_LPORT��������V22�շѻ���V23�շѻ�
	{
		Level = 0;			
		SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,Doc->nSndDataLen,InData,OutData,Level, Level_Array);
		if( !PostSend((char*)OutData, SendLen, nTimeOut) )
		{
			return false;
		}	
		memset(OutData,0x00,sizeof OutData);
		Sleep(55);
		if( !PostRecv((char*)OutData, 128, nTimeOut) )
		{
			return false;
		}
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{		
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}	
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}		
	return true;		
}


/*=================================================================
* Function ID :  SMT_VerifyClock
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��ʱУ��ʱ��
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_VerifyClock()
{
	SMARTCOMMPACK	Doc;
	memset(&Doc,0,sizeof Doc);

	if( !strlen((char*)m_sCurDate) )  memcpy(m_sCurDate,m_Data.GetSysTime(),8);
	if( !memcmp(m_sCurDate,m_Data.GetSysTime(),8) ) return true;
	memcpy(m_sCurDate,m_Data.GetSysTime(),8);
	for( int i=0;i<m_nTotalPos; i++ )
	{
		//ˮ���豸��У��ʱ��
		if( !memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0244,2)||
			!memcmp(m_SmartPos[i].ucpMachineCode,MACHINE_TYPE_0245,2) )
		{
			continue;
		}
		memcpy(Doc.ucpIDNo,m_SmartPos[i].ucpIDNo,4);
		memcpy(Doc.ucRegNo,m_SmartPos[i].ucRegNo,4);
		Doc.ucMacNo=m_SmartPos[i].ucMacNo;
		Doc.nFlag=1;
		SMT_SetClock(&Doc);
		Sleep(250);
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_GetClock
* Input       :  int nPosition 
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����ʱ��
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetClock(SMARTCOMMPACK* Doc)				//�����ն˻�ʱ��
{		
	long	SendLen=0;
	long    nTimeOut=2000;
	BYTE	commision[7],OutData[256],InData[256];
	int		Level=0;
	BYTE	Level_Array[4];
	char	str[80],ucMid[3];
	int	    nWeek=0;	
	int		nTry=0;
	bool	bol=false;

	memset(str,		   0x00,sizeof str   );
	memset(InData,     0x00,sizeof InData);
	memset(OutData,    0x00,sizeof OutData);
	memset(commision,  0x00,sizeof commision);
	memset(Level_Array,0x00,sizeof Level_Array);	
	memset(str,	 0x00,sizeof str  );
	memset(ucMid,0x00,sizeof ucMid);
	
	memcpy(str,m_Data.GetSysTime()+2,12); //ʱ��YYMMDDHHSSMM	
	nWeek=m_Data.GetWeek(); //����
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str,2);
	Doc->ucSndData[0]=atol(ucMid);
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str+2,2);	
	Doc->ucSndData[1]=atol(ucMid);
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str+4,2);	
	Doc->ucSndData[2]=atol(ucMid);
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str+6,2);	
	Doc->ucSndData[3]=atol(ucMid);
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str+8,2);	
	Doc->ucSndData[4]=atol(ucMid);
	memset(ucMid,0x00,sizeof ucMid);
	memcpy(ucMid,str+10,2);	
	Doc->ucSndData[5]=atol(ucMid);
	Doc->ucSndData[6]=nWeek;
	Doc->nSndDataLen = 7;				
	
	BYTE ucCommandByte = 0xA9;		
	memcpy(commision,Doc->ucRegNo,4);	

	sprintf(str,"�ն�[%.8X]��ʼ����ʱ��....",m_Data.HexToInt(commision,4));	
	m_pDialog->AddString(str);
	
	Level = 0;			
	memcpy(InData,Doc->ucSndData,Doc->nSndDataLen);
	SendLen=m_Data.BuildData( Doc->ucMacNo,1,commision, ucCommandByte,Doc->nSndDataLen,InData,OutData,Level, Level_Array);
	if( !PostSend((char*)OutData, SendLen, nTimeOut) )
	{
		return false;
	}	
	memset(OutData,0x00,sizeof OutData);
	Sleep(250);
	if( !PostRecv((char*)OutData, 128, nTimeOut) )
	{
		return false;
	}
	if( !ValidateData(OutData,m_nReadBytes) )
	{		
		return false;
	}
	if( OutData[2] != 0x00 )
	{
		strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
		return false;
	}	
	if( !DealWithRecvData(Doc, OutData) )
	{
		return false;
	}	
	return true;		
}


/*=================================================================
* Function ID :  SMT_GetHistoryData
* Input       :  SMARTCOMMPACK CommPack
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ɼ���ʷ����
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_GetHistoryData(SMARTCOMMPACK* CommPack)	
{	
	long	SendLen=0;
	long    nTimeOut=50;
	BYTE	commision[7],OutData[256],InData[256];
	char	str[128],sTmp[256];
	int		nStartInvoice=0,nEndInvoice=0;
	BYTE	ucCommandByte = 0xBB;		
	char	sBuffer[256];
	int		nMessageID=CommPack->nMessageID;
	bool	bFlag=false;

	memset(sTmp,       0x00,sizeof sTmp);
	memset(str,		   0x00,sizeof str   );
	memset(InData,     0x00,sizeof InData);
	memset(OutData,    0x00,sizeof OutData);
	memset(commision,  0x00,sizeof commision);
	memset(sBuffer,    0x00,sizeof sBuffer);
	
	m_nTaskResultStatus=0x0C;
	memcpy(commision,CommPack->ucRegNo,4);
	nStartInvoice=m_Data.HexToInt(CommPack->ucSndData,2);
	nEndInvoice=m_Data.HexToInt(CommPack->ucSndData+2,2);
	for( int i=nStartInvoice; i<=nEndInvoice; i++ )
	{
		if( !g_StartFlag ) break;
		memset(InData,0,sizeof InData);	
		memset(OutData,0x00,sizeof OutData);
		InData[0]=i>>8;
		InData[1]=i;
		CommPack->nSndDataLen=2;
		SendLen=m_Data.BuildData( CommPack->ucMacNo,1,commision, ucCommandByte,CommPack->nSndDataLen,
			InData,OutData,0, NULL);
		if( !(bFlag=PostSend((char*)OutData, SendLen, nTimeOut)) )
		{
			m_nTaskResultStatus=0x0C;
			return bFlag;
		}	
		memset(OutData,0x00,sizeof OutData);
		Sleep(80);
		if( !(bFlag=PostRecv((char*)OutData, 128, nTimeOut)) )
		{
			if( i>0 ) i--;
			continue;
		}
		if( !(bFlag=ValidateData(OutData,m_nReadBytes)) )
		{
			continue;
		}
		if( OutData[2] != 0x00 )
		{
			m_nTaskResultStatus=OutData[2];
			strcpy(m_szErrorText,GetStatusErrMsg(OutData[2]));
			continue;
		}
		memset(str, 0,sizeof str);
		memset(sTmp,0,sizeof sTmp);
		sprintf(sBuffer,"%04X,%02ld,%s",m_Data.HexToInt(CommPack->ucpMachineCode,2),RECORDDATATYPE_HISTROY,(char*)m_Data.BcdToAsc(OutData+4,28,(byte*)sTmp));		
		if( !(bFlag=WriteTradeDeal(sBuffer)) )
		{
			if( i>0 ) i--;
			continue;
		}
		sprintf(m_szErrorText,"�ն�-->%08X �ɼ���ʷ��ˮ��Ϊ %ld �ɹ�",m_Data.HexToInt(commision,4),i);
		m_pDialog->AddString(m_szErrorText);
	}
	return bFlag;
}

/*=================================================================
* Function ID :  Run
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  ��ѭ��,�����������,��û������,���Ͳɼ���������
* Notice	  :  
*=================================================================*/
void CSmart::Run()
{	
	char			cMsg[256];
	bool			result=false;		
	SMARTCOMMPACK	Doc;
	DWORD			nTimeSleep=0;
	int				nTry=0;

	memset(&Doc,0x00, sizeof Doc);
	memset(cMsg,0x00,sizeof cMsg);
	memset(m_szErrorText,0,sizeof m_szErrorText);

	try
	{
		nTry=3;		
		m_nContinueTime=GetTickCount();		//��ȡ����ʱ��	
		CreateRecordPath();					//����д��־��·��
		memset(m_szErrorText,0,sizeof m_szErrorText);
		//��ʾ����·����ʱ�����ӷ����豸δ�ɹ�����Ҫ��������
		Open();
		Smt_CollectDataInit();
		while( !m_IpPar.bConnect )
		{
			if( !g_StartFlag ) break; ;	//�յ�ֹͣ����
			ReConnect();
			if( (GetTickCount()-m_nContinueTime)>60*nTimeSleep )
			{
				WriteLog(m_szErrorText);
				m_nContinueTime=GetTickCount();
			}
			WriteLog(m_szErrorText);
			Sleep(nTimeSleep);
		}
		result=false;
		m_nWaitRecvTime=10;		
		while( !IsShutdown() )
		{
			m_nTaskResultStatus=6;
			memset(&Doc,0x00, sizeof Doc);			
			if( nTry<4 )
			{
				GetTask(&Doc);//��ȡ����			
				nTry++;
			}
			else
			{
				Doc.nTaskCode=SMT_COLLECTDATA;
				nTry=0;
			}
			if( !g_StartFlag )		break ;				//�յ�ֹͣ����
			m_nStartTime=GetTickCount();
			//��������Ŵ�����Ӧ������
			switch( Doc.nTaskCode)
			{
				case SMT_COLLECTDATA:
					Smt_CollectDataProcess();			//�ɼ�����
					continue;
				case SMT_SMARTFRONTBROADBLACK:			//�㲥������
					//SMT_BroadCastBlackCard(&Doc);					
					result=true;
					break;
				case SMT_SMARTFRONTDELBLACKLIST:		//ɾ��������
					result=SMT_DelBlackCard(&Doc);
					break;
				case SMT_SMARTFRONTADDBLACKLIST:		//���Ӻ�����
					result=SMT_SetBlackCard(&Doc);
					break;
				case SMT_GETHISTORYDATA:
					result=SMT_GetHistoryData(&Doc);	//ȡ��ʷ��ˮ	
					break;
				case SMT_SETWORKSECRET:
					result=SMT_SetWorkKey(&Doc);		//���ù�����Կ��Ǯ����
					break;
				case SMT_SETCARDTYPE:					//���ÿ���
					result=SMT_SetCardType(&Doc);
					break;
				case SMT_GETCARDTYPE:					//�ϴ�����
					result=SMT_GetCardType(&Doc);
					break;
				case SMT_SETFEERATE:
					result=SMT_SetFreeRate(&Doc);		//���ù�������
					break;
				case SMT_GETFEERATE:
					result=SMT_GetFreeRate(&Doc);		//��ȡ��������
					break;
				case SMT_SETWHITECARD:
					result=SMT_SetWhiteCard(&Doc);		//����һ��������
					break;
				case SMT_DELWHITECARD:
					result=SMT_DelWhiteCard(&Doc);		//ɾ��һ��������
					break;
				case SMT_CONFIRMWHITECARD:
					result=SMT_ConfirmWhiteCard(&Doc);	//�ж�һ��������
					break;
				case SMT_DELALLWHITECARD:
					result=SMT_DelAllWhiteCard(&Doc);	//ɾ�����а�����
					break;
				case SMT_SETWARMMONEY:					//���ñ������
					result=SMT_SetWarmMoney(&Doc);
					break;
				case SMT_GETWARMMONEY:					//�ϴ��������
					result=SMT_GetWarmMoney(&Doc);
					break;
				case SMT_SETPOSPLACE:
					result=SMT_SetPosPlace(&Doc);		//�´��Ʒ����ص�
					break;
				case SMT_GETPOSPLACE:
					result=SMT_GetPosPlace(&Doc);		//�ϴ��Ʒ����ص�
					break;					
				case SMT_GETCLOCK:						//��ȡʱ��
					result=SMT_GetClock(&Doc);
					break;
				case SMT_OPENCTRL:
					result=SMT_OpenCtrl(&Doc);			//��ˮ
					break;
				case SMT_CLOSECTRL:
					result=SMT_CloseCtrl(&Doc);			//��ˮ
					break;
				case SMT_SETCLOCK:						//����ʱ��
					result=SMT_SetClock(&Doc);
					break;					
				case SMT_SMARTFRONTGETMAINPARA:			//�´�������
					result=SMT_SetMainPara(&Doc);
					break;
				case SMT_SMARTFRONTCARDTYPE:			//������չ����
					result=SMT_SetCardtypeCon(&Doc);
					break;
				case SMT_SMARTFRONTMANAGERATE:			//�´�����ѱ���
				case SMT_SMARTFRONTPWDMONEY:			//�´��������ý��
				case SMT_SMARTFRONTDAYMONEY:			//���ۼ������޶�
				case SMT_SMARTFRONTMANAGEPWD:			//�����ն˹���Ա����
				case SMT_SMARTFRONTGETTIMESEGMENT:		//ʱ���
				case SMT_SMARTFRONTGETTIMEHOLIDAY:		//�ڼ���
				case SMT_SMARTFRONTGETTIMEWHITEVER:		//�´���ʱ�������汾
				case SMT_SMARTFRONTGETTIMEWHITELIST:	//�´�/ɾ��������/���а�����
				case SMT_SMARTFRONTGETTIMESWITCH:		//�������,�ָ�����
				case SMT_SMARTFRONTGETEATNUM:			//��ʱ���
					result=SMT_ExecuteCmd411(&Doc);
					break;
				case SMT_SMARTFRONTGETTIMEWHITELISTVER: //�´�/ɾ�����������汾
					result=SMT_SetWhiteListAndVer(&Doc);
					break;
				default:
					Smt_CollectDataProcess();
					continue;
			}
			SMT_InsertTaskResult(Doc,result);
		}
	}
	catch (...)
	{		
		sprintf(m_szErrorText,"�߳��쳣--------->�����ն�-->%08X[ %s ]�Ѿ��˳��߳�!",m_Data.HexToInt((BYTE*)m_regno,4),m_IpPar.cIPAddress);
		WriteLog(m_szErrorText);		
		m_pDialog->AddString(m_szErrorText);	
		MessageBox(NULL,m_szErrorText,m_szErrorText,MB_OK);		
	}
	Close();
	OnShutdown();
	sprintf(m_szErrorText,"�߳�����------�����ն�-->%08X[ %s ]�Ѿ��˳�!",m_Data.HexToInt((BYTE*)m_regno,4),m_IpPar.cIPAddress);
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	m_hThread=NULL;
	m_pDialog->WriteLog(m_szErrorText);	
	return ;
}

/*=================================================================
* Function ID :  SMT_BroadCastBlackCard
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �㲥������
* Notice	  :  
*					
*=================================================================*/
bool CSmart::SMT_BroadCastBlackCard(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"�Է������㲥������[ IP=%s]",m_IpPar.cIPAddress);	
	m_pDialog->AddString(m_szErrorText);
	if( Doc->nFlag==1 ) return true; //ɾ������Ҫ�´���
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetBlackCard
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����һ��������
* Notice	  :  
*					
*=================================================================*/
bool CSmart::SMT_SetBlackCard(SMARTCOMMPACK* Doc)
{
	byte			sVer[30],sStr[128],CRC[5];
	int				nLen=0;
	SMARTCOMMPACK	cDoc;
	
	memset(CRC,  0,sizeof CRC);
	memset(sStr, 0,sizeof sStr);
	memset(sVer, 0,sizeof sVer);
	memset(&cDoc,0,sizeof cDoc);

	Doc->nRecDataLen=0;
	memcpy(&cDoc,Doc,sizeof(cDoc));

	//�Ƚ�CRC�Ƿ���ȷ
	sprintf((char*)sStr,"%ld%s",Doc->nMemo,(char*)Doc->sMemo);			
	nLen=strlen((char*)sStr);
	memcpy(sStr+nLen,Doc->ucSndData,2);
	if( m_Data.CRC_CCITT(nLen+2,sStr,CRC) )
	{
		return false;
	}

	//���ӿ���
	cDoc.nSndDataLen = 0x04;
	cDoc.ucSndData[0]= 0x01;
	cDoc.ucSndData[1]= cDoc.nMemo>>16;
	cDoc.ucSndData[2]= cDoc.nMemo>>8;
	cDoc.ucSndData[3]= cDoc.nMemo;
	cDoc.ucCmd       = 0xA4;
	cDoc.nRecDataLen = 0;
	if( !SMT_ExecuteCmd411(&cDoc)||cDoc.nRecDataLen!=1 )
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´����Ӻ�����ʧ��1[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
			m_Data.HexToInt(cDoc.ucpIDNo,4),
			cDoc.nMemo,
			cDoc.sMemo,
			m_IpPar.cIPAddress,
			cDoc.nMessageID,
			m_nTaskResultStatus);
		m_pDialog->AddString(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		return false;
	}

	Sleep(50);
	memset(sVer,		  0,sizeof sVer);
	memset(cDoc.ucSndData,0,sizeof cDoc.ucSndData);	
	//�°汾
	cDoc.nRecDataLen = 0x00;
	cDoc.nSndDataLen = 0x06;
	cDoc.ucCmd		 = 0xA7;
	memcpy(cDoc.ucSndData,m_Data.AscToBcd(cDoc.sMemo,12,sVer),6);	
	if( !SMT_ExecuteCmd411(&cDoc)||cDoc.nRecDataLen)
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´����Ӻ�����ʧ��2[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
			m_Data.HexToInt(cDoc.ucpIDNo,4),
			cDoc.nMemo,
			cDoc.sMemo,
			m_IpPar.cIPAddress,
			cDoc.nMessageID,
			m_nTaskResultStatus);

		m_pDialog->AddString(m_szErrorText);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		return false;
	}

	//�����汾��
	Sleep(50);
	memset(sVer,		  0,sizeof sVer);
	memset(cDoc.ucSndData,0,sizeof cDoc.ucSndData);	
	cDoc.nSndDataLen = 0x00;
	cDoc.ucCmd		 = 0xA8;
	cDoc.nRecDataLen = 0x00;
	cDoc.nFlag		 = 1;
	if( !SMT_ExecuteCmd411(&cDoc))
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´�ɾ��������ʧ��3[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
		m_Data.HexToInt(cDoc.ucpIDNo,4),
		cDoc.nMemo,
		cDoc.sMemo,
		m_IpPar.cIPAddress,
		cDoc.nMessageID,
		m_nTaskResultStatus);
		m_pDialog->AddString(m_szErrorText);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		return false;
	}
	//�Ƚϰ汾�Ƿ�һ��
	memset(sVer,0,sizeof sVer);
	m_Data.BcdToAsc(cDoc.ucRecData,6,sVer);
	if( memcmp(sVer,Doc->sMemo,12) ) return false;
	
	sprintf(m_szErrorText,"���յ��ն�-->%08X �´����Ӻ������ɹ�[����=%ld �汾=%s IP=%s, %ld]",
		m_Data.HexToInt(cDoc.ucpIDNo,4),
		cDoc.nMemo,
		cDoc.sMemo,
		m_IpPar.cIPAddress,
		cDoc.nMessageID);
	m_pDialog->AddString(m_szErrorText);
	if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
	memcpy(m_SmartPos[m_SmartPosPostion].ucBlackCardVer,Doc->sMemo,12);
	return true;
}

/*=================================================================
* Function ID :  SMT_DelBlackCard
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ɾ��һ��������
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_DelBlackCard(SMARTCOMMPACK* Doc)
{
	byte			sVer[30],sStr[128],CRC[5];
	int				nLen=0;
	SMARTCOMMPACK	cDoc;
	bool			bFlag=false;
	
	memset(CRC,  0,sizeof CRC );
	memset(sStr, 0,sizeof sStr);
	memset(sVer, 0,sizeof sVer);
	memset(&cDoc,0,sizeof cDoc);

	Doc->nRecDataLen=0;
	memcpy(&cDoc,Doc,sizeof(cDoc));	

	//�Ƚ�CRC�Ƿ���ȷ,������ȷ˵���յ��������Ѿ��ң���Ҫ�ӵ�
	sprintf((char*)sStr,"%ld%s",Doc->nMemo,(char*)Doc->sMemo);			
	nLen=strlen((char*)sStr);
	memcpy(sStr+nLen,Doc->ucSndData,2);
	if( m_Data.CRC_CCITT(nLen+2,sStr,CRC) )
	{
		return false;
	}
	
	cDoc.ucCmd		  = 0xA5;
	cDoc.nSndDataLen  = 0x04;
	cDoc.ucSndData[0] = 0x01;
	cDoc.ucSndData[1] = cDoc.nMemo>>16;
	cDoc.ucSndData[2] = cDoc.nMemo>>8;
	cDoc.ucSndData[3] = cDoc.nMemo;
	cDoc.nRecDataLen  = 0x00;
	if( !(bFlag=SMT_ExecuteCmd411(&cDoc))||cDoc.nRecDataLen!=1 )
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´�ɾ��������ʧ��1[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
		m_Data.HexToInt(cDoc.ucpIDNo,4),
		cDoc.nMemo,
		cDoc.sMemo,
		m_IpPar.cIPAddress,
		cDoc.nMessageID,
		m_nTaskResultStatus);
		m_pDialog->AddString(m_szErrorText);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		return false;
	}

	Sleep(50);
	memset(sVer,		  0,sizeof sVer);
	memset(cDoc.ucSndData,0,sizeof cDoc.ucSndData);	
	//�°汾
	cDoc.nSndDataLen = 0x06;
	cDoc.ucCmd		 = 0xA7;
	cDoc.nRecDataLen = 0x00;
	memcpy(cDoc.ucSndData,m_Data.AscToBcd(Doc->sMemo,12,sVer),6);	
	if( !SMT_ExecuteCmd411(&cDoc)||cDoc.nRecDataLen )
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´�ɾ��������ʧ��2[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
		m_Data.HexToInt(cDoc.ucpIDNo,4),
		cDoc.nMemo,
		cDoc.sMemo,
		m_IpPar.cIPAddress,
		cDoc.nMessageID,
		m_nTaskResultStatus);
		m_pDialog->AddString(m_szErrorText);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		return false;
	}
	//�����汾��
	Sleep(50);
	memset(sVer,		  0,sizeof sVer);
	memset(cDoc.ucSndData,0,sizeof cDoc.ucSndData);
	cDoc.nSndDataLen = 0x00;
	cDoc.ucCmd		 = 0xA8;
	cDoc.nRecDataLen = 0x00;
	cDoc.nFlag		 = 1;
	if( !SMT_ExecuteCmd411(&cDoc))
	{
		sprintf(m_szErrorText,"���յ��ն�-->%08X �´�ɾ��������ʧ��3[����=%ld �汾=%s IP=%s, %ld ״̬->%ld]",
		m_Data.HexToInt(cDoc.ucpIDNo,4),
		cDoc.nMemo,
		cDoc.sMemo,
		m_IpPar.cIPAddress,
		cDoc.nMessageID,
		m_nTaskResultStatus);
		m_pDialog->AddString(m_szErrorText);
		if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
		if( !m_nTaskResultStatus) m_nTaskResultStatus=0x0C;
		return false;
	}
	//�Ƚϰ汾�Ƿ�һ��
	memset(sVer,0,sizeof sVer);
	m_Data.BcdToAsc(cDoc.ucRecData,6,sVer);
	if( memcmp(sVer,Doc->sMemo,12) ) return false;
	
	sprintf(m_szErrorText,"���յ��ն�-->%08X �´�ɾ���������ɹ�[����=%ld �汾=%s IP=%s, %ld]",
			m_Data.HexToInt(cDoc.ucpIDNo,4),
			cDoc.nMemo,
			cDoc.sMemo,m_IpPar.cIPAddress,
			cDoc.nMessageID);
			m_pDialog->AddString(m_szErrorText);	
	memcpy(m_SmartPos[m_SmartPosPostion].ucBlackCardVer,Doc->sMemo,12);	
	if( g_IniFilePara.bWriteDebugLog ) WriteLog(m_szErrorText);
	return true;
}

//��������list
bool CSmart::SMT_InsertTaskResult(SMARTCOMMPACK Doc,bool bStatus)
{
	byte			Outdata[128];
	SMARTTASKRESULT mTaskResult;

	memset(Outdata,     0,sizeof Outdata);
	memset(&mTaskResult,0,sizeof mTaskResult);

	//���ڴ����ҵ���������� add by dj 20070924
	g_CriticalSectionLock.Lock();
	for( int i=0; i<NTASKNUM; i++ )
	{
		if( Doc.nMessageID==m_STaskArr.CommPack[i].nMessageID )
		{
			memset(&m_STaskArr.CommPack[i],0x00,sizeof(m_STaskArr.CommPack[i]));
			m_STaskArr.CommPack[i].bExecute=false;
			break;
		}
	}
	g_CriticalSectionLock.Unlock();
	
	if( !bStatus ) //���غ�����ʧ�ܵĽ������Ҫ�ϴ������˴�,ֱ�ӷ���
	{
		if( Doc.nAcction==SMT_SMARTFRONTDELBLACKLIST||Doc.nAcction==SMT_SMARTFRONTADDBLACKLIST)
		{
			return true;
		}	
	}
	mTaskResult.nAcction=Doc.nAcction;
	mTaskResult.ResultStatus=bStatus;
	mTaskResult.nTaskResultStatus=m_nTaskResultStatus;
	memcpy(&mTaskResult.Pos,&Doc,sizeof(SMARTCOMMPACK));
	strcpy((char*)mTaskResult.ucIP,m_IpPar.cIPAddress);	
	m_pDialog->SMT_InsertOneTaskResult(mTaskResult);	
	switch(m_nTaskResultStatus)
	{
		case 0x17:		//���ʼ�¼ȷ��
			SMT_SettleAccount(m_SmartPosPostion);	
			break;
		case 0x0D:		//ǩ��(�¹�����Կ)
			SMT_RequestLogin(Outdata,m_SmartPosPostion);
			break;
		case 0x1B:		//��ԡ��������ȷ��
			SMT_RequestConsume(Outdata,m_SmartPosPostion);
			break;
		default:
			break;
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_ProcessDeviceRegNoErr
* Input       :  int NetWorkType,int nPostion
* Output      :  void
* Author      :  
* Date        :  2006  10
* Return	  :  
* Description :  �����ն��޷�Ӧ�����
* Notice	  :  ��NetWorkTypeΪֱ��ʱ��nPostion��0
*                ��NetWorkTypeΪ����ʱ��nPostion����豸�����豸�����е�λ��
*				 ��NetWorkTypeΪ����ʱ��nPostion����豸�����豸�����е�λ��
#define	LINE_TYPE   1	//ֱ����
#define STAR_TTYPE  2	//����
#define BUS_TYPE    3	//������
*=================================================================*/
bool CSmart::SMT_ProcessDeviceRegNoErr(int NetWorkType,int nPostion)
{
	char msg[256];			
	BYTE ucID[16],ucRegNo[16];
	SMARTCOMMPACK Doc;
		
	memset(msg,		0x00,sizeof msg);
	memset(ucID,	0x00,sizeof ucID);
	memset(&Doc,	0x00,sizeof Doc);
	memset(ucRegNo,	0x00,sizeof ucRegNo);

	//��ȡ�ն�ע���[�ϴ�������,ǰ4�ֽ�Ϊע���]
	Doc.ucCmd  =0xB8;	
	Doc.nFlag  =0;
	Doc.nSndDataLen=0;		
	if( NetWorkType == LINE_TYPE &&!memcmp(m_MacCode,MACHINE_TYPE_5301,2) )  //ֱ��
	{
		Doc.ucCmd  =0xF0;	
	}
	if( !SMT_ExecuteCmd411(&Doc) ) return false; 	
	if( NetWorkType		 == LINE_TYPE )
	{
		if( !memcmp(m_MacCode,MACHINE_TYPE_5301,2) )
		{
			if( memcmp(m_regno,Doc.ucRecData+4,4) )
			{
				memcpy(m_regno,Doc.ucRecData+4,4);
			}			
		}
		else
		{		
			if( memcmp(m_regno,Doc.ucRecData,4) )
			{
				memcpy(m_regno,Doc.ucRecData,4);
			}
		}
	}
	else if( NetWorkType == BUS_TYPE  )
	{
		if( memcmp(m_SmartPos[nPostion].ucRegNo,Doc.ucRecData,4) )
		{		
			memcpy(m_SmartPos[nPostion].ucRegNo,Doc.ucRecData,4);
		}
	}
	else if( NetWorkType == STAR_TYPE )
	{
		if( memcmp(m_SmartPos[nPostion].ucRegNo,Doc.ucRecData,4) )
		{		
			//�޸��ڴ���ͨѶ��ע���
			memcpy(m_SmartPos[nPostion].ucRegNo,Doc.ucRecData,4);
		}
		//�޸ĸ��豸���ڶ˿ڵ�ע���
		Doc.ucCmd   =0x11;	
		Doc.ucMacNo	=m_MacNum;
		memcpy(Doc.ucpIDNo,m_IDNo,4);		
		memcpy(Doc.ucRegNo,m_regno,4);
		Doc.nSndDataLen =6;	
		Doc.ucSndData[0]=m_SmartPos[nPostion].nPort;
		Doc.ucSndData[1]=m_SmartPos[nPostion].ucMacNo;
		memcpy(Doc.ucSndData+2,m_SmartPos[nPostion].ucRegNo,4);		
		if( !SMT_ExecuteCmd411(&Doc) ) return false; 
	}
	return true;
}


/*=================================================================
* Function ID :  SMT_SetCardtype
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ÿ���
* Notice	  :  
*					
*=================================================================*/
bool CSmart::SMT_SetCardtypeCon(SMARTCOMMPACK* Doc)	
{
	byte           sStr[128];
	SMARTCOMMPACK  cDoc;

	for( int i=0; i<3; i++ )
	{	
		memset(sStr,0,sizeof sStr);
		memset(&cDoc,0,sizeof cDoc);
		memcpy(&cDoc,Doc,sizeof(SMARTCOMMPACK));
		cDoc.ucCmd=0xBF;
		cDoc.nSndDataLen=0;
		if( !SMT_ExecuteCmd411(&cDoc) ) continue;
		Sleep(100);
		memcpy(sStr,cDoc.ucRecData+5,28);
		memcpy(sStr+4,Doc->ucSndData+30,2);
		cDoc.ucCmd=0xB7;
		memcpy(cDoc.ucSndData,sStr,28);
		cDoc.nSndDataLen=28;
		if( !SMT_ExecuteCmd411(&cDoc) )continue;
		Sleep(2000);
		break;
	}
	if( i==3 ) return false;	
	Doc->nSndDataLen=30;
	return SMT_ExecuteCmd411(Doc);
}	
/*=================================================================
* Function ID :  SMT_SetWhiteListAndVer
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �´����������汾
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_SetWhiteListAndVer(SMARTCOMMPACK *Doc)
{
	byte ucSnd[128];

	memset(ucSnd,0,sizeof ucSnd);

	if( Doc->ucCmd==0xAD ) 
	{
		return SMT_ExecuteCmd411(Doc); // ɾ�����а�����
	}
	else
	{
		memcpy(ucSnd,Doc->ucSndData+4,6);
		Doc->nSndDataLen=4;
		if( !SMT_ExecuteCmd411(Doc) ) //�´�����
		{
			return false;
		}
		Sleep(80);
		memcpy(Doc->ucSndData,ucSnd,6);
		Doc->ucCmd=0xAE;
		SMT_ExecuteCmd411(Doc); //�´��汾
		return true;
	}
}

/*=================================================================
* Function ID :  SMT_ExecuteCmd411
* Input       :  SMARTCOMMPACK* Doc
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ִ��411����
* Notice	  :  
*=================================================================*/
bool CSmart::SMT_ExecuteCmd411(SMARTCOMMPACK* Doc)		
{
	long	SendLen =0;
	long    nTimeOut=1000;
	BYTE	OutData[512];
	bool	bResult=false;
	long	nSleep=SMT_WAITFORTIME3;

	memset(OutData,0,sizeof OutData);

	for( int i=0; i<3; i++ )
	{
		memset(OutData,0,sizeof OutData);
		m_nTaskResultStatus	= 6;
		bResult				= false;
		SendLen=m_Data.BuildData( Doc->ucMacNo,Doc->nFlag,Doc->ucpIDNo, Doc->ucCmd,Doc->nSndDataLen,Doc->ucSndData,OutData,0,NULL);
		if( !(bResult=PostSend((char*)OutData, SendLen, nTimeOut)) ) 
		{
			WriteLog(m_szErrorText);
			return false;
		}
		if(      Doc->ucCmd==0xA5)	Sleep(nSleep);
		else if( Doc->ucCmd==0xA4)  Sleep(nSleep);
		else if( Doc->ucCmd==0xA7)  Sleep(nSleep);
		else if( Doc->ucCmd==0xA8)  Sleep(nSleep);
		else if( Doc->ucCmd==0x7A)  Sleep(1000);
		else if( Doc->ucCmd==0xB7)  Sleep(450);
		else if( Doc->ucCmd==0x67)  Sleep(2000);
		else if( Doc->ucCmd==0x04)  {Sleep(nSleep);nTimeOut=200;}
		else						Sleep(1000);

		//��������
		memset(OutData,0x00,sizeof OutData);			
		if( !(bResult=PostRecv((char*)OutData, 500, nTimeOut)) ) 
		{
			WriteLog(m_szErrorText);
			m_nTaskResultStatus=6;
			Sleep(150);
			nSleep+=200;
			continue;
		}
		//������ݵ���Ч��
		if( !(bResult=ValidateData(OutData,m_nReadBytes)) ) 
		{
			Sleep(50);
			continue;
		}
		if( Doc->ucMacNo!=OutData[1] )
		{
			//����������
			if( Doc->ucCmd==0xA5||Doc->ucCmd==0xA4)
			{
				return false;
			}
			bResult=false;
			if( Doc->ucMacNo!=0x00&&Doc->ucMacNo!=0xFF ) 
			{
				return false;
			}
		}
		//��������
		bResult=DealWithRecvData(Doc, OutData);
		return bResult;
	}
	return bResult;
}

/*=================================================================
* Function ID :  InsertTask
* Input       :  SMARTCOMMPACK *Task
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ� false ʧ��
* Description :  ���������ѹ��һ������
* Notice	  :  
*=================================================================*/
bool CSmart::InsertTask(SMARTCOMMPACK *cTask)
{
	int	i=0;
	int nCount=0;
	ASSERT(cTask!=NULL);

	g_CriticalSectionLock.Lock();
	for( i=0; i<NTASKNUM; i++ ) //��闣���Ƿ��Ѿ����ڸ����񣬴����򲻲���
	{
		if( m_STaskArr.CommPack[i].nMessageID==cTask->nMessageID )
		{
			g_CriticalSectionLock.Unlock();
			return true;
		}
	}
	if( m_nInsertTaskPoint>=NTASKNUM )
	{
		m_nInsertTaskPoint=0;
	}
	nCount=m_nInsertTaskPoint;
	while( m_nInsertTaskPoint<NTASKNUM )
	{
		if( !m_STaskArr.CommPack[m_nInsertTaskPoint].bExecute ) //��ʾ�Ѿ�ִ�е�����
		{
			memcpy(&m_STaskArr.CommPack[m_nInsertTaskPoint],cTask,sizeof(SMARTCOMMPACK));
			m_STaskArr.CommPack[m_nInsertTaskPoint].bExecute=true;
			m_STaskArr.bHaveFlag							=true;			
			m_nInsertTaskPoint++;
			g_CriticalSectionLock.Unlock();
			Sleep(5);
			return true;
		}
		m_nInsertTaskPoint++;
	}
	m_nInsertTaskPoint=0;
	//��ʾ���е��ϰ벿��Ҳ��Ҫ����Ƿ��пյط����Բ�������
	if( nCount!=0 )
	{
		while( m_nInsertTaskPoint<NTASKNUM )
		{
			if( !m_STaskArr.CommPack[m_nInsertTaskPoint].bExecute ) //��ʾ�Ѿ�ִ�е�����
			{
				memcpy(&m_STaskArr.CommPack[m_nInsertTaskPoint],cTask,sizeof(SMARTCOMMPACK));
				m_STaskArr.CommPack[m_nInsertTaskPoint].bExecute=true;
				m_STaskArr.bHaveFlag							=true;
				m_nInsertTaskPoint++;
				g_CriticalSectionLock.Unlock();
				Sleep(5);
				return true;
			}
			m_nInsertTaskPoint++;
		}
	}
	g_CriticalSectionLock.Unlock();
	return false;
}

/*=================================================================
* Function ID :  GetTask
* Input       :  SMARTCOMMPACK *Task
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ� false ʧ��
* Description :  �������б��л�ȡһ������
* Notice	  :  
*					
*=================================================================*/
bool CSmart::GetTask(SMARTCOMMPACK *cTask)
{	
	ASSERT(cTask!=NULL);

	int		nTry=0,i=0;
	
	g_CriticalSectionLock.Lock();
	if( m_nTaskPoint>=NTASKNUM )
	{
		m_nTaskPoint=0;
		memcpy(cTask,&m_STaskArr.CommPack[NTASKNUM-1],sizeof(SMARTCOMMPACK));
	}
	else
	{
		while( m_nTaskPoint<NTASKNUM )
		{
			memcpy(cTask,&m_STaskArr.CommPack[m_nTaskPoint++],sizeof(SMARTCOMMPACK));
			if( cTask->nTaskCode!=0 ) 
			{
				break;	//��ʾ�Ѿ�ȡ������
			}
		}
	}
	if( cTask->nTaskCode==0 ) cTask->nTaskCode=SMT_COLLECTDATA;
	g_CriticalSectionLock.Unlock();
	return true;

}

/*=================================================================
* Function ID :  Smt_CollectDataInit
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  
* Notice	  :  
*					
*=================================================================*/
bool CSmart::Smt_CollectDataInit()
{
	byte ucCommandByte=0x03;
	for( int i=0; i<m_nTotalPos; i++)
	{
		m_SmartPos[i].nSndLen=0;
		memset(m_SmartPos[i].ucSendData,0,sizeof m_SmartPos[i].ucSendData);
		m_SmartPos[i].nSndLen=m_Data.BuildData( m_SmartPos[i].ucMacNo,1,m_SmartPos[i].ucpIDNo, ucCommandByte,0,NULL,m_SmartPos[i].ucSendData,0,NULL);

		//��Ϊˮ���豸����ı����
		if( !memcmp(MACHINE_TYPE_0244,m_SmartPos[i].ucpMachineCode,2)||
			!memcmp(MACHINE_TYPE_0245,m_SmartPos[i].ucpMachineCode,2) )
		{
			memcpy(m_MacCode,m_SmartPos[i].ucpMachineCode,2);
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_OpenCtrl
* Input       :  int nPosition 
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ȡʱ��
* Notice	   :  nPosition  ��ʾ����LPORT�Ķ˿ں�
*					
*=================================================================*/
bool CSmart::SMT_OpenCtrl(SMARTCOMMPACK* Doc)				//
{		
	Doc->ucCmd=0x82;
	if( Doc->ucMacNo==0x00 )
	{
		sprintf(m_szErrorText,"��ʼ�㲥��ˮ[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);
	}
	else
	{
		sprintf(m_szErrorText,"��ʼ�Ի���= %ld IP=%s ���豸���п�ˮ............",Doc->ucMacNo,m_IpPar.cIPAddress);
	}
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	return SMT_ExecuteCmd411(Doc);
}


/*=================================================================
* Function ID :  SMT_CloseCtrl
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ��ˮ
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_CloseCtrl(SMARTCOMMPACK* Doc)				//
{		
	Doc->ucCmd=0x83;
	if( Doc->ucMacNo==0x00 )
	{
		sprintf(m_szErrorText,"��ʼ�㲥��ˮ[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);
	}
	else
	{
		sprintf(m_szErrorText,"��ʼ�Ի���= %ld IP=%s ���豸���й�ˮ............",Doc->ucMacNo,m_IpPar.cIPAddress);
	}
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetWorkKey
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ù�����Կ��Ǯ����
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetWorkKey(SMARTCOMMPACK* Doc)				//
{	
	Doc->ucCmd=0x8F;
	if( !SMT_ExecuteCmd411(Doc) )
	{
		sprintf(m_szErrorText,"���ù�����Կ��Ǯ����ʧ��[����=%ld IP=%s,RetCode=%ld]............",Doc->ucMacNo,m_IpPar.cIPAddress,m_nTaskResultStatus);	
		if( g_IniFilePara.bWriteDebugLog )  WriteLog(m_szErrorText);
		m_pDialog->AddString(m_szErrorText);		
		return false;
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_SetCardType
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ÿ���
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetCardType(SMARTCOMMPACK* Doc)				//
{	
	sprintf(m_szErrorText,"�ն��豸[ %.08X ]��ʼ���üƷ�������[����=%ld IP=%s]",
		m_Data.HexToInt(Doc->ucpIDNo,4),
		Doc->ucMacNo,
		m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x90;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_GetCardType
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ϴ�����
* Notice	   :  
*
*=================================================================*/
bool CSmart::SMT_GetCardType(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼ�ϴ�����[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x91;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetFreeRate
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ù�������
* Notice	   :  
*=================================================================*/
bool CSmart::SMT_SetFreeRate(SMARTCOMMPACK* Doc)				//
{	
	sprintf(m_szErrorText,"�ն��豸[ %.08X ]��ʼ���üƷ�����������[����=%ld IP=%s]",
		m_Data.HexToInt(Doc->ucpIDNo,4),
		Doc->ucMacNo,
		m_IpPar.cIPAddress);		
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x92;
	
	byte ucSndData[512];
	int nPackCount=0,nSndLen=0,nLen=0;
	memset(ucSndData,0,sizeof ucSndData);

	nPackCount=Doc->nSndDataLen/100;
	if( Doc->nSndDataLen/100 )	nPackCount++;	
	nSndLen=Doc->nSndDataLen;
	nLen=nSndLen;
	memcpy(ucSndData,Doc->ucSndData,nSndLen);
	for( int i=0; i<nPackCount; i++ )
	{
		memset(Doc->ucSndData,0,sizeof Doc->ucSndData);
		Doc->ucSndData[0]=nSndLen>>8;
		Doc->ucSndData[1]=nSndLen;
		if( nLen>100 )
		{
			memcpy(Doc->ucSndData+2,ucSndData+100*i,100);	
			nLen-=100;
			Doc->nSndDataLen=100;
		}
		else
		{
			memcpy(Doc->ucSndData+2,ucSndData+100*i,nLen);	
			Doc->nSndDataLen=nLen;
		}
		Doc->nSndDataLen+=2;
		if( !SMT_ExecuteCmd411(Doc) )
		{
			return false;
		}
	}
	return true;
}

/*=================================================================
* Function ID :  SMT_SetAddTotalMoney
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ó�ֵ�����ܳ�ֵ��
* Notice	   :  
*=================================================================*/
bool CSmart::SMT_SetAddTotalMoney(SMARTCOMMPACK* Doc)
{	
	sprintf(m_szErrorText,"�ն��豸[ %.08X ]��ʼ���ó�ֵ�ܶ�[����=%ld IP=%s]",
		m_Data.HexToInt(Doc->ucpIDNo,4),
		Doc->ucMacNo,
		m_IpPar.cIPAddress);		
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x90;	
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_GetFreeRate
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ϴ���������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_GetFreeRate(SMARTCOMMPACK* Doc)				//
{	
	sprintf(m_szErrorText,"��ʼ�ϴ���������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x93;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetWhiteCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����һ��������
* Notice	   :  
*=================================================================*/
bool CSmart::SMT_SetWhiteCard(SMARTCOMMPACK* Doc)
{	
	sprintf(m_szErrorText,"��ʼ����һ��������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0xAB;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_DelWhiteCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ɾ��һ��������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_DelWhiteCard(SMARTCOMMPACK* Doc)
{	
	sprintf(m_szErrorText,"��ʼɾ��һ��������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0xAC;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_ConfirmWhiteCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ж�һ��������
* Notice	   :  
*=================================================================*/
bool CSmart::SMT_ConfirmWhiteCard(SMARTCOMMPACK* Doc)
{	
	sprintf(m_szErrorText,"��ʼ�ж�һ��������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x95;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_DelAllWhiteCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ɾ�����а�����
* Notice	   :  
*=================================================================*/
bool CSmart::SMT_DelAllWhiteCard(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼɾ�����а�����[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0xAD;
	return SMT_ExecuteCmd411(Doc);	
}

/*=================================================================
* Function ID :  SMT_SetPosPlace
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���üƷ����ص�
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetPosPlace(SMARTCOMMPACK* Doc)
{
	bool bol=false;
	Doc->ucCmd=0x98;
	if( (bol=SMT_ExecuteCmd411(Doc)) )
	{
		sprintf(m_szErrorText,"�ն��豸[ %.08X ]���üƷ����ص�ɹ�[����=%ld IP=%s]",
			m_Data.HexToInt(Doc->ucpIDNo,4),
			Doc->ucMacNo,
			m_IpPar.cIPAddress);	
	}
	else
	{
		sprintf(m_szErrorText,"�ն��豸[ %.08X ]��ʼ���üƷ����ص�ʧ��[����=%ld IP=%s]",
			m_Data.HexToInt(Doc->ucpIDNo,4),
			Doc->ucMacNo,
			m_IpPar.cIPAddress);		
	}
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	return bol;
}

/*=================================================================
* Function ID :  SMT_GetPosPlace
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ϴ��Ʒ����ص�
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_GetPosPlace(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼ�ϴ��Ʒ����ص�[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x99;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetWarmMoney
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ���ñ������
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_SetWarmMoney(SMARTCOMMPACK* Doc)
{
	bool bol=false;

	Doc->ucCmd=0x9A;
	if( (bol=SMT_ExecuteCmd411(Doc)) )
	{
		sprintf(m_szErrorText,"�ն��豸[ %.08X ]���üƷ����������ɹ�[����=%ld IP=%s]",
			m_Data.HexToInt(Doc->ucpIDNo,4),
			Doc->ucMacNo,
			m_IpPar.cIPAddress);		
	}
	else
	{
		sprintf(m_szErrorText,"�ն��豸[ %.08X ]���üƷ����������ʧ��[����=%ld IP=%s]",
			m_Data.HexToInt(Doc->ucpIDNo,4),
			Doc->ucMacNo,
			m_IpPar.cIPAddress);
	}
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	return bol;
}

/*=================================================================
* Function ID :  SMT_GetWarmMoney
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ϴ��������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_GetWarmMoney(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼ�ϴ��������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0x9B;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_SetMainPara
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  ����������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_SetMainPara(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼ�����շѻ�������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0xB7;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_GetMainPara
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ�ɹ�  false��ʾʧ��
* Description :  �ϴ��ն�������
* Notice	   :  
*					
*=================================================================*/
bool CSmart::SMT_GetMainPara(SMARTCOMMPACK* Doc)
{
	sprintf(m_szErrorText,"��ʼ�ϴ��շѻ�������[����=%ld IP=%s]............",Doc->ucMacNo,m_IpPar.cIPAddress);	
	WriteLog(m_szErrorText);
	m_pDialog->AddString(m_szErrorText);
	Doc->ucCmd=0xBF;
	return SMT_ExecuteCmd411(Doc);
}

/*=================================================================
* Function ID :  SMT_CheckWhetherAssistantCard
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	   :  ����true ��ʾ��������  false��ʾ�ǲ�������
* Description :  
* Notice	   : 
*=================================================================*/
bool CSmart::SMT_CheckWhetherAssistantCard(int nCardNo,int nBatchNo)
{
	int nPostion,nMod=0;

	if( nBatchNo>=g_nSaveAssistantVer)	return false; //����ǰ���κŴ��ڻ����ϵͳ������κ�,������
	if( nCardNo>SAVEBLACKLISTTOTAL )	return false; //���Ŵ���SAVEBLACKLISTTOTAL(1����)
	if( nCardNo<=0 )					return false; //����С�ڵ���0
	
	nPostion=nCardNo/8;								//�õ��ÿ��ڲ�������������λ�õ��ĸ��ֽ�
	nMod    =nCardNo%8;								//�ڸ��ֽڵ�λͼ
	
	if( nPostion==0 )
	{
		if( (g_SaveAssistantList[nPostion]>>(8-nMod))&0x01 )
		{
			return true;
		}
	}
	else
	{
		if( nMod==0 )
		{
			nPostion--;
			if( g_SaveAssistantList[nPostion]&0x01 )
			{
				return true;
			}
		}
		else
		{
			if( (g_SaveAssistantList[nPostion]>>(8-nMod))&0x01 )
			{
				return true;
			}
		}
	}
	return false;
}