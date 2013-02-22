 
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

//��ʼ���ӿڲ�
long __stdcall InitChannels(int nServer, int nFunc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	printf("���ý��˴��ṩ�ĺ���DRTPInitialize,��ȴ�------!!!!\n");
	DRTPInitialize();
	printf("�ɹ�����DRTPInitialize()\n");
	iServerNo = nServer ;
	iFunc = nFunc;
	nReload = 0;
	
	return RET_OK;
}

//���ٽӿڲ�
long __stdcall DestoryChannels()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DisConnect();
	CloseNotify();

	DRTPUninitialize();

	return RET_OK;
}

//���ӵ�������
long __stdcall ConnectToCenter(char *pszHost, int nPort, int nEncode)
{
    
	//return RET_OK;//debug20050401
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int nConnectNumber = GetPrivateProfileInt("INTERFACE", "CONNECTNUM", 15, szINIFile);

	if( nConnectNumber <= 0 || nConnectNumber >= 100 )
		nConnectNumber = 15 ;
	
	if( !ConnectPool.Initialized(nConnectNumber, pszHost, nPort, nEncode) )
	{
		WriteLog("����ǰ������˴�������������ͨѶƽ̨%s:%dʧ��!\n", pszHost, nPort);
		return RET_SYSERROR;
	}

	WriteLog("����ǰ������˴���������ͨѶƽ̨%s:%d�ɹ�!...�����:%d....�����ܺ�:%d\n", pszHost, nPort, iServerNo, iFunc);

	if( SmartRegister() != RET_OK )
	{
		WriteLog("����ǰ������˴�ע��ʧ��! ϵͳ��������������, ����ϵϵͳ����Ա!!!\n");
		return RET_SYSERROR;
	}

	if( SmartSignIn() != RET_OK )
	{
		WriteLog("����ǰ�û�����˴�ǩ��ʧ��! ϵͳ��������������, ����ϵϵͳ����Ա!!!\n");
		return RET_SYSERROR;
	}

	return RET_OK;
}

//�ر�����
long __stdcall DisConnect()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SmartSignOut();
	ConnectPool.DestroyPool();

	return 0L;
}

//��ʼ������֪ͨ
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
		WriteLog("����ǰ������˴ﱻ������ͨѶƽ̨%s:%dʧ��!(CreateNotify)\n", pszBind, nPort);
		return RET_NG;
	}
	WriteLog("����ǰ������˴ﱻ������ͨѶƽ̨%s:%d�ɹ�!...�����:%d....�����ܺ�:%d.....(CreateNotify)\n", pszBind, nPort, iServerNo, iFunc);
	return RET_OK;
}

//�رձ���֪ͨ
long __stdcall CloseNotify()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if( hNotify != NULL )
	{
#if __DEBUG_INTERFACE__
		DRTPClose(hNotify);
		WriteLog("����ǰ������˴�ر�ͨѶƽ̨����!(CloseNotify)");
#endif
		hNotify = NULL ;
	}
	return 0L;
}

//����֪ͨ����
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

//����֪ͨ����
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
				//WriteLog("����ǰ������˴�������������ݳɹ�(RecvDataPro)\n");
				return iResult;
			}
		}
		return RET_NG;
	}
	//WriteLog("����ǰ�ý��ս��˴����ݳɹ�\n");
	return iResult;
#else
	printf("----------RecvDataProδִ���κζ���------------\n");
	return nLen;
#endif
}

//��������
long __stdcall SendData(HANDLE& hHandle, int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if __DEBUG_INTERFACE__
	if( DRTPSend(hHandle, nDest, nFunc, pszData, nLen, nPriority, bRouter) )
	{
		WriteLog("����ǰ������˴﷢�����ݳɹ�(SendData)\n");
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
//				WriteLog("����ǰ���������˴�������ݳɹ�(SendData),��������:%s\n",pszData);
//				return RET_OK;
//			}
		}
	}
	return RET_NG;
#else
	return RET_OK;
#endif
}


//��������
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
		WriteLog("���ý��˴��������ʧ�ܺ���[DRTPReceive()] ����ֵiResult= %ld::DRTPGetLastError��������:%s\n....................\n",iResult,szText);				
		WriteLog("������˴����һ��...................");		
		ConnectPool.ReConnect(hHandle);
		iResult = DRTPReceive(hHandle, pszBuffer, nLen, nTimeOut);
		if( iResult > 0 )
		{
			//WriteLog("����ǰ���ٴ��������˴��������ݳɹ�(RecvData),��������:%s\n",pszBuffer);
			return iResult;
		}		
		WriteLog("����ǰ�ý��ս��˴�����ʧ��(RecvData),DRTPGetLastError��������:%s\n",szText);
		return RET_NG;
	}
	//WriteLog("����ǰ�ý��ս��˴����ݳɹ�(RecvData),��������:%s\n",pszBuffer);
	return iResult;
#else
	return nLen;
#endif
}

//----------------------------------------------------------------------------
//
//  Function:   SendTick
//
//  Synopsis:   ��������
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
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);

	char omsg[256];
	if( EncodeBuf(&rpack, szBuffer, &nLen, omsg) )
	{
		if( SendDataPro(iServerNo, iFunc, (char*)szBuffer, nLen, 1, FALSE) == RET_OK )
		{			
			//WriteTickLog("���������ɹ�! �����:%d, �ӹ��ܺ�:%d\n", iServerNo, iFunc);
			return RET_OK;
		}
	}

	WriteTickLog("����������ʧ��! ������˴��м��!! �����:%d, �ӹ��ܺ�:%d", iServerNo, iFunc);

	return RET_SYSERROR;
}

long __stdcall GetTickNumber()
{
	return gTick;
}

//���豸����  (����!!!! 20050305)
long __stdcall SendDocTick(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ST_CPACK rpack;
	unsigned char szBuffer[8192];
	int  nLen = sizeof(szBuffer);

	memset(&rpack, 0, sizeof(rpack));
	memset(szBuffer, 0, sizeof(szBuffer));

	rpack.head.RequestType = 930099; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
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
		WriteTickLog("�����豸������! �豸ID=%s", pDoc->m_szDeviceID);
		return SendDataPro(iServerNo, iFunc, (char*)szBuffer, nLen, 1, FALSE);
	}

	return RET_SYSERROR;
}

//----------------------------------------------------------------------------
//
//  Function:   ReadSmartDocList
//
//  Synopsis:   �����豸������
//
//  Arguments:  pSmartDoc -- �豸������
//				nRecCount -- ��¼��
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

	WriteLog("����ǰ������˴���ù��ܺ�%d, �����ȡȫ���豸������\n", 930037);

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
			WriteLog("�豸������������%d, �����豸����������!!!!\n", MAX_SMART_DOC);
			break;
		}

		memset(&rpack, 0, sizeof(rpack));

		rpack.head.RequestType = 930037; 
		rpack.head.recCount = 1;    /* �����ļ�¼��*/
		rpack.head.retCode = 0;     /* ���ش���*/
		rpack.head.userdata = 0;

		if( nfirst )
		{
			rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
			rpack.head.nextflag = 0;    /* �Ƿ����������*/
			nfirst = 0 ;
		}
		else
		{
			rpack.head.firstflag = 0;   /* �Ƿ��һ�������װ�����*/
			rpack.head.nextflag = 1;    /* �Ƿ����������*/
			memcpy(&rpack.head.hook,&apack.head.hook,sizeof(rpack.head.hook));
			rpack.head.hook.queuetype=apack.head.hook.queuetype;
		}

		SetValue(&rpack.head,&rpack.pack, F_SDATE1, "00000000");
		SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ

		nLen = sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));

		if( !EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) )
		{
			ConnectPool.Free(hHandle);
			WriteLog("ִ�й��ܺ�930037�����豸������ʱ,����EncodeBufʧ��\n");
			return RET_SYSERROR;
		}
	//	printf("ִ�й��ܺ�930037�����豸������\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) != RET_OK )
		{
			ConnectPool.Free(hHandle);
			WriteLog("ִ�й��ܺ�930037�����豸������ʱ,����SendDataʧ��\n");
			return RET_SYSERROR;
		}

		memset(buffer, 0, sizeof(buffer));

		nLen = sizeof(buffer);
		nlen = RecvData(hHandle, buffer, nLen, 10000);
		if( nlen <= 0 )
		{
			ConnectPool.Free(hHandle);
			WriteLog("ִ�й��ܺ�930037�����豸������ʱ,����RecvDataʧ��\n");
			return RET_SYSERROR;
		}

		BOOL bRet=DecodeBufWithArray((unsigned char*)buffer,nlen,&apack,apackarray,&nRow,omsg);
		if( !bRet || apack.head.retCode )
		{
			ConnectPool.Free(hHandle);
			WriteLog("ִ�й��ܺ�930037�����豸������ʱ,����DecodeBufWithArray,����������,ʧ��!\n");
			return RET_SYSERROR;
		}

		WriteLog("ִ�й��ܺ�930037�����豸������ʱ,�õ��豸����Ϊ:%d,�豸����Ϊ:\n",nRow);

		for(int i=0; i< nRow; i++)
		{
			if( i == 0 ) pPacket = &apack.pack;
			else  pPacket = &apackarray[i-1];

			strcpy(pSmartDoc[k].m_szMacCode, pPacket->semp);		//�ն˻��ͺŴ���
			strcpy(pSmartDoc[k].m_szMacCard, pPacket->sholder_type);//����IC������
			strcpy(pSmartDoc[k].m_szMacModle, pPacket->semp);		//�ն˻��ͺ�
			strcpy(pSmartDoc[k].m_szMacType, pPacket->semp);		//��������
			strcpy(pSmartDoc[k].m_szDeviceID, pPacket->sdate1);	//�豸ID
			strcpy(pSmartDoc[k].m_szRegister, pPacket->sdate2);	//ע���
			pSmartDoc[k].m_nAuthID=ConvertID(pSmartDoc[k].m_szDeviceID);//��Ȩ��
			pSmartDoc[k].m_nMachineNo=pPacket->lvol4;			//����	
			strcpy(pSmartDoc[k].m_szVersion, pPacket->sdate3);	//�豸�汾��
			strcpy(pSmartDoc[k].m_szPassword, "000000");			//ϵͳԱ����
			strcpy(pSmartDoc[k].m_szOprPasswd, "000000");			//����Ա����
			pSmartDoc[k].m_nPwdswitch=-1;							//���뿪��
			strcpy(pSmartDoc[k].m_sClockVer, pPacket->stime0);	  //���豸
			
			strcpy(pSmartDoc[k].m_szOrgid, "001");				  //��������֯����
			pSmartDoc[k].m_nPortCount=pPacket->lvol5;			  //�������˿�����
			pSmartDoc[k].m_nSMTPort=pPacket->lvol6;				  //�������˿ں�
			strcpy(pSmartDoc[k].m_szPort, pPacket->sbank_code);	  //ͨѶ�˿�
			pSmartDoc[k].m_nBaudRate=pPacket->lvol9;			  //������
			pSmartDoc[k].m_nCommMode=pPacket->lvol8;			  //��·ģʽ
			strcpy(pSmartDoc[k].m_szAddr, pPacket->sstation0);    //ͨѶ��ַ
			pSmartDoc[k].m_nStatus=pPacket->lvol7;                //�豸״̬, ���涨��Ϊ:

			pSmartDoc[k].m_nConnType = pPacket->lvol10;			  //ͨѶ��ʽ
			strcpy(pSmartDoc[k].m_szClass, pPacket->snote2);	  //����				  //

			pSmartDoc[k].m_wFlowNo=pPacket->lvol11+1;			  //������ˮ�� modified
			pSmartDoc[k].m_wLastInvoiceNo=pPacket->lvol11;        //�ն˽�����ˮ����ĩֵ
			pSmartDoc[k].m_wStateNo=pPacket->lvol12;
			pSmartDoc[k].m_nFlow=1;									//���
			pSmartDoc[k].m_nBeginInvoice=0;							//���ʵĿ�ʼ��ˮ
			pSmartDoc[k].m_wSettleinvoice=0;						//������ˮ����ĩֵ
			pSmartDoc[k].m_wEndInvoice=0;							//���ʵĽ�����ˮ��
			strcpy(pSmartDoc[k].m_sBlackExpire, pPacket->sserial0);   //����������Ч��
			strcpy(pSmartDoc[k].m_sDownBlackTime, pPacket->sserial1); //�������´�ʱ����ĩֵ
			pSmartDoc[k].m_nStartuse=0;								  //ǩ�����

			pSmartDoc[k].m_nCardID = 12;
			pSmartDoc[k].m_nDealCount = 10;
			pSmartDoc[k].m_nInMoney = 100000;
			pSmartDoc[k].m_nOutMoney = pSmartDoc[k].m_nInMoney; 
			pSmartDoc[k].m_nBeginInvoice = 0 ;
			pSmartDoc[k].m_wFlowNo  = 0 ;
			pSmartDoc[k].m_wStateNo = 0 ;
/*
			WriteLog("�ն˻��ͺŴ���=%s,����IC������=%s, �ն˻��ͺ�=%s, ��������=%s\n "
				"�豸ID=%s, ע���=%s, ����=%d, �豸�汾��=%s, ϵͳԱ����=%s, ����Ա����=%s\n"
				"���뿪��=%d, �������˿�����=%d, �������˿ں�=%d, ͨѶ�˿�=%s, ������=%d\n"
				"��·ģʽ=%d,ͨѶ��ַ=%s, �豸״̬=%d, ������ˮ����ĩֵ=%d, ����������Ч��=%s, �������汾=%s, ͨѶ��ʽ=%d,����=%s, ���豸:%s\n",
				pPacket->semp, pPacket->sholder_type, pPacket->semp, pPacket->semp,
				pPacket->sdate1, pPacket->sdate2, pPacket->lvol4, pPacket->sdate3, "000000", "000000", 
				pSmartDoc[k].m_nPwdswitch, pPacket->lvol5, pPacket->lvol6, pPacket->sbank_code, pPacket->lvol9, 
				pPacket->lvol8, pPacket->sstation0, pPacket->lvol7, pPacket->lvol11, pPacket->sserial0, pPacket->sserial1, 
				pPacket->lvol10, pPacket->snote2, pPacket->stime0);
*/

			if( !theApp.CheckSmartDocValid(&pSmartDoc[k]) )
			{
				WriteLog("��Ч�豸!!!\n");
				ZeroMemory(&pSmartDoc[k], sizeof(TSSmartDoc));
			}
			else
			{
				WriteLog("��Ч�豸!ID��=%s, ע���=%s, ����=%d, ��������:%d..���豸����=%s\n", 
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
// ����Ϊ���������Ϣ
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

		//ģ��LPort
		if( iTick == 0 || iTick == 15 )
		{
			strcpy(pSmartDoc[k].m_szMacCode, "5301");		//�ն˻��ͺŴ���
			strcpy(pSmartDoc[k].m_szMacModle, "5301");		//�ն˻��ͺ�
			strcpy(pSmartDoc[k].m_szMacType, "5301");		//��������
			strcpy(pSmartDoc[k].m_szDeviceID, "0000918F");	//�豸ID
			strcpy(pSmartDoc[k].m_szRegister, "0000918F");	//ע���
			pSmartDoc[k].m_nAuthID=ConvertID(pSmartDoc[k].m_szDeviceID);//��Ȩ��
			pSmartDoc[k].m_nMachineNo=1;			//����	
			strcpy(pSmartDoc[k].m_szAddr, sIP);    //ͨѶ��ַ
			pSmartDoc[k].m_nPortCount=16;			  //�������˿�����
			sprintf(pSmartDoc[k].m_szPort, "%d", nPort); //nPort++);	  //ͨѶ�˿�
			strcpy(pSmartDoc[k].m_sClockVer, "");	  //���豸

			iMacNo=1;
			strcpy(szParent, pSmartDoc[k].m_szDeviceID);
			pSmartDoc[k].m_nSMTPort=0;				  //�������˿ں�
		}
		else
		{
			//if( iTick == 0 || iTick == 6 || iTick == 8 || iTick == 10 )
			//{
				strcpy(pSmartDoc[k].m_szMacCode, "0226");		//�ն˻��ͺŴ���
				strcpy(pSmartDoc[k].m_szMacCard, "64");//����IC������
				strcpy(pSmartDoc[k].m_szMacModle, "0226");		//�ն˻��ͺ�
				strcpy(pSmartDoc[k].m_szMacType, "0226");		//��������
			//}
			/*else
			{
				strcpy(pSmartDoc[k].m_szMacCode, "0201");		//�ն˻��ͺŴ���
				strcpy(pSmartDoc[k].m_szMacCard, "64");//����IC������
				strcpy(pSmartDoc[k].m_szMacModle, "0201");		//�ն˻��ͺ�
				strcpy(pSmartDoc[k].m_szMacType, "0201");		//��������
			}*/

			strcpy(pSmartDoc[k].m_szDeviceID, "00008B1a");	//�豸ID
			strcpy(pSmartDoc[k].m_szRegister, "00008B1a");	//ע���
			pSmartDoc[k].m_nAuthID=0x00008B1a;//ConvertID(pSmartDoc[k].m_szDeviceID);//��Ȩ��
			pSmartDoc[k].m_nMachineNo=1;//++iMacNo;			//����	
			pSmartDoc[k].m_nPortCount=16;			  //�������˿�����
			strcpy(pSmartDoc[k].m_szAddr, sIP);    //ͨѶ��ַ
			strcpy(pSmartDoc[k].m_sClockVer, szParent);	  //���豸
			pSmartDoc[k].m_nSMTPort=2; //iMacNo;				  //�������˿ں�
		}

		if( iTick >= 15 )
			iTick = 0 ;
		else
			iTick++;

		strcpy(pSmartDoc[k].m_szMacCard, "64");//����IC������
		strcpy(pSmartDoc[k].m_szVersion, "");	//�豸�汾��
		strcpy(pSmartDoc[k].m_szPassword, "000000");			//ϵͳԱ����
		strcpy(pSmartDoc[k].m_szOprPasswd, "000000");			//����Ա����
		pSmartDoc[k].m_nPwdswitch=-1;							//���뿪��
		strcpy(pSmartDoc[k].m_szOrgid, "001");				  //��������֯����
		pSmartDoc[k].m_nBaudRate=19200;			  //������
		pSmartDoc[k].m_nCommMode=3;			  //��·ģʽ
		pSmartDoc[k].m_nStatus=0;                //�豸״̬, ���涨��Ϊ:
		pSmartDoc[k].m_nConnType = 1;			  //ͨѶ��ʽ
		strcpy(pSmartDoc[k].m_szClass, "FFFFFFFFFF");	  //����				  //
		pSmartDoc[k].m_wFlowNo=0;			  //������ˮ�� modified
		pSmartDoc[k].m_wLastInvoiceNo=0;        //�ն˽�����ˮ����ĩֵ
		pSmartDoc[k].m_wStateNo=0;
		pSmartDoc[k].m_nFlow=1;									//���
		pSmartDoc[k].m_nBeginInvoice=0;							//���ʵĿ�ʼ��ˮ
		pSmartDoc[k].m_wSettleinvoice=0;						//������ˮ����ĩֵ
		pSmartDoc[k].m_wEndInvoice=0;							//���ʵĽ�����ˮ��
		strcpy(pSmartDoc[k].m_sBlackExpire, "991231010101");   //����������Ч��
		strcpy(pSmartDoc[k].m_sDownBlackTime, "991231010101"); //�������´�ʱ����ĩֵ
		pSmartDoc[k].m_nStartuse=0;								  //ǩ�����

		printf("���豸(ID=%s, ע���:%s, ����=%d, ��������:%d..���豸:%s...\n", 
			pSmartDoc[k].m_szDeviceID, pSmartDoc[k].m_szRegister, 
			pSmartDoc[k].m_nMachineNo, pSmartDoc[k].m_nCommMode, pSmartDoc[k].m_sClockVer);
		k++;
	}
#endif

	gnDocCount = k;
	gpSmartDoc = new TSSmartDoc[gnDocCount];
	if( gpSmartDoc == NULL )
	{
		printf("�ڴ治��.....\n");
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

	WriteLog("��Ч�豸������:%d...........\n", k);

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
					printf("���豸%s\n",pSmartDoc[j].m_szDeviceID);
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
//  Synopsis:   �õ����˴���������������
//
//  Arguments:  pTaskPlan -- ����ƻ�����
//
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall ReadSmartTaskPlan(TSSmartTaskPlan *pTaskPlan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//�豸����������� add by dengjun date 20051116	
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

	//��һ������ʱ,��Ҫ�������ļ��л�ȡ����ʱ����
	if( !flag )
	{		
		char  szDir[MAX_PATH];
		char  strServerINI[MAX_PATH];

		memset(szDir,  0x00,sizeof szDir);
		memset(&apack, 0x00,sizeof(apack));
		memset(strServerINI,0x00,sizeof strServerINI);
		
		flag = 1;
		WriteLog("�������ļ��л�ȡ�������ʱ��\n");
		GetCurPath(szDir);
		sprintf(strServerINI, "%s\\SmartServer.ini", szDir);		

		//����ʱ��(Ĭ��10����)
		TIMESENDTICK = GetPrivateProfileInt("SYSTEM", "TICKTIME", 600, strServerINI);
		TIMESENDTICK = 1000*TIMESENDTICK;		

		//�ն�״̬ʱ��(Ĭ��Ϊ10��)
		TIMESENDSTATUS = GetPrivateProfileInt("SYSTEM", "STATUSTIME", 30, strServerINI);
		TIMESENDSTATUS = 1000*TIMESENDSTATUS;		
		WriteLog("ReadSmartTaskPlan()����ʱ��[%ld����],�����ն�״̬ʱ��[%ld����],[%s]\n",TIMESENDTICK,TIMESENDSTATUS,strServerINI);
		memset(cSysDate,0x00,sizeof cSysDate);
		memcpy(cSysDate,cTool.GetSysTime(),8);		
	}
		
	//sprintf(msg,"--->����˴��ȡ����()����ʱ���[%ld],����ʱ��[%ld����],״̬ʱ���[%ld],�ն�״̬ʱ��[%ld����]\n",endTime,TIMESENDTICK,endTimeStuats,TIMESENDSTATUS);
	//WriteLog(msg);
	
	ZeroMemory(pTaskPlan, sizeof(TSSmartTaskPlan));
	pTaskPlan->nRepeatTime  = 1 ;   //�����೤ʱ�䣨���ӣ�
	pTaskPlan->nRepeatTimes = 1;    //�ظ�����
	
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
			strcpy(msg,"����˴��ȡ����ʱ,δ�յ���Ӧ����.\n");
			WriteLog(msg);				
			return RET_SYSERROR;
		}		
		nRow = 0 ;
		memset(&apack, 0, sizeof(apack));
		memset(apackarray, 0, sizeof(apackarray));
		BOOL bRet=DecodeBufWithArray((BYTE*)buffer,nlen,&apack,apackarray,&nRow,omsg);	
		if(bRet == FALSE)
		{
			sprintf(msg,"Ӧ�����ݰ����Ĵ���Ret=%d\n", bRet);
			WriteLog(msg);						
			return RET_SYSERROR;
		}
		if(apack.head.retCode)
		{			
			sprintf(msg,"���˴��̨ҵ����ʧ��,������retcode=%d,������Ϣ[%s]\n",apack.head.retCode,apack.pack.vsmess);
			WriteLog(msg);			
			return RET_SYSERROR;//XXXΪ��Ӧ�Ĵ�����,Ҳ����ֱ�� return  0;
		}
		if( apack.pack.lvol1<=0 )
		{	
			WriteLog("���˴�û�������´�!!!\n");			
			// add by dengjun 20051117 ��������//��û���������Ѿ����˷���������ʱ����������			
			if( endTime >= TIMESENDTICK )
			{
				WriteLog("�����Ѿ�������������ʱ��,�ҽ��˴�û������,��ʼ�����ն�������............\n");
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
			// add by dengjun 20060111 ȡ�豸״̬
			if( endTimeStuats >= TIMESENDSTATUS)
			{
				//WriteLog("�����Ѿ�������ȡ�ն�״̬��ʱ��,�ҽ��˴�û������,��ʼ�����ն����ݰ�............\n");
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
			//���賿,��ʼ��LPORT			
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
			return RET_NOTASK;		//���˴�û�������´�
		}
		//������
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
	
	// add by dengjun 20051117 ��������	
	if( endTime >= TIMESENDTICK )
	{
		WriteLog("�����Ѿ�������������ʱ��,�յ����˴�����,��ʼ�����ն�������,����������һ����............\n");
		memset(&apack, 0x00,sizeof(apack));		
		StartTime			   = GetTickCount();		
		apack.pack.lvol2       = 930057;
		apack.pack.lvol1       = StartTime;
		apack.head.RequestType = 930057;
		nRow=1;
		bResult = theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);						
	}

	//ȡ�ն��豸״̬ // add by dengjun 20060111 ȡ�豸״̬
	if( endTimeStuats >= TIMESENDSTATUS)
	{
		//WriteLog("�����Ѿ�������ȡ�ն�״̬ʱ��,�ҽ��˴�û������,��ʼ�����ն�״̬���ݰ�,����������һ����............\n");
		memset(&apack,     0x00, sizeof apack);		
		memset(pTaskPlan,  0x00, sizeof TSSmartTaskPlan);
		StartTimeStatus		   = GetTickCount();		
		apack.pack.lvol2       = 930058;
		apack.pack.lvol1       = StartTimeStatus;
		apack.head.RequestType = 930058;		
		nRow=1;
		bResult=theApp.MakeFirstTaskPlan(pTaskPlan, &apack, apackarray, nRow);								
	}				
	//����LPORT����һ���죬��ʱ����ͨѶ���ϣ����賿,��ʼ��LPORT			
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
	sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", 100); //����ƻ�����
	pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
	GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
	pTaskPlan->nRepeatTime = 1 ;              //�����೤ʱ�䣨���ӣ�
	pTaskPlan->nRepeatTimes = 1;             //�ظ�����
	GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��
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
			//	WriteLog("!!!�㲥������....�豸:%s.....����:%d....\n", gpSmartDoc[i].m_szDeviceID, pPacket->pack.lvol0);
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
//  Synopsis:   ������ִ�н���������˴ﴫ���
//
//  Arguments:  pTaskPlan -- ����ƻ�����
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
//  Synopsis:   ��Ӳ��������ת��Ϊ�ӿ����ݲ��������˴ﴫ���
//
//  Arguments:  nType     -- ��������
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
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
		case 0x01:	//�շѻ�
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddSFCount(1);
			break;
		case 248: //�Ϻ���ת�ʻ�
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);			
			rpack.head.RequestType = 930030; //Ӧ����
			break;
		case 0x21:  //�շѻ�(��ʷ)
			iResult = theApp.ConvertDealData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //Ӧ����		
			break;
		case 0x02:	//��ʱ��
			iResult = theApp.ConvertIdentifyData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930101; 
			break;
		case 0x22:  //��ʱ��(��ʷ)
			iResult = theApp.ConvertIdentifyData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		case 0x03:  //����	
		case 0x23:  //����(��ʷ)
			iResult = theApp.ConvertStateData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddJZCount(1);
			break;
		case 0x04:  //����		
			iResult = theApp.ConvertAssisData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddBZCount(1);
			break;
		case 0x24:  //����(��ʷ)
			iResult = theApp.ConvertAssisData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //Ӧ����		
			break;			
		case 0x05:  //��ʧ
			break;
		case 0x06:  //��ֵ��	
			iResult = theApp.ConvertDealData1(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddCZCount(1);
			break;
		case 0x26:  //��ֵ��(��ʷ)
			iResult = theApp.ConvertDealData1(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			rpack.head.RequestType = 930098; //Ӧ����		
			break;
		case 0x07:  //��ֵ�������	
		case 0x27:  //��ֵ�������(��ʷ)	
			iResult = theApp.ConvertDealData2(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			TestData.AddCZCount(1);
			break; 
		case 0x08:	//�ն��޷�Ӧ
		case 0x09:	//�޶�Ӧ��ŵ���
			iResult = theApp.ConvertError(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		case 0x81:  //��ʧ
		case 0x82:  //���
		case 0x83:  //�޸�����
			iResult = theApp.ConvertGSJData(nType, pTask, pDoc, &rpack, ucRawData, nDataLen);
			break;
		default:
			printf("δ֪����������!.............\n");
			break;
	}

	//����������,����ϵͳ�������������쳣����,������Ч����,
	if( iResult == RET_DATACRC_ERROR )
	{
		return RET_OK;
	}

	if( iResult != RET_OK ) 
	{
		WriteLog("��Ӳ��������ת��Ϊ�ӿ����ݲ��������˴ﴫ���....ʧ��!.......\n");
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
					printf("����RequestType = %d ����RequestType=%d",rpack.head.RequestType,apack.head.RequestType);
					if(!apack.head.retCode)
					{
						ConnectPool.Free(hHandle);

						WriteLog("���ܺ�=%d, �������ݵ����˴�ɹ�!��Ϣ=%s �ķ�ʱ��(����)%d...\n", apack.head.RequestType,apack.pack.vsmess, GetTickCount()-nTick1 );
						return RET_OK;
					}
					else
					{
						WriteLog("�������ݵ����˴�ʧ��! ���˴ﷵ�ش���:���ܺ�=%d, ������=%d, ��Ϣ=%s! �ķ�ʱ��(����)%d...\n", 
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
//  Synopsis:   �õ�ϵͳ����
//
//  Arguments:  nType   -- ��������
//				pParam  -- ���صĲ���
//  History:    2004-09-20   ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long __stdcall GetParam(int nType, TSSystemParam *pParam)
{
	switch(nType)
	{
	case 0:   //���в���
		memcpy(pParam,&GlobalParam, sizeof(TSSystemParam));
		pParam->nParameter4 = -1;
		break;
	case 1:  //��������Ϣ
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

//�ն˻�ǩ��
long __stdcall SignIn(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SignInDoc(pDoc);
}

//�ն˻�ǩ��
long __stdcall SignOut(TSSmartDoc *pDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SignOutDoc(pDoc);
}

//ǰ�û�ǩ��
long __stdcall SmartSignOut()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

/*	if( gpSmartDoc != NULL )
	{
		for(long i=0; i< gnDocCount; i++)
		{
			if( strcmp(gpSmartDoc[i].m_szMacCode, "5301") )
			{
				WriteLog("ǰ�û�ǩ��!%s\n", gpSmartDoc[i].m_szDeviceID);
				SignOut(&gpSmartDoc[i]);
			}
		}
	}
*/
	WriteLog("ǰ�û�ǩ��!\n");

	return theApp.SmartSignOut();
}

//ǰ�û�ǩ��
long __stdcall SmartSignIn()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SmartSignIn();
}

//ǰ�û�ע��
long __stdcall SmartRegister()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SmartRegister();
}

//�����صĽ��
long __stdcall ReportTaskResult(TSSmartTask *pTask, long iResult, TSResultData *pData)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.ReportResult(pTask, iResult, pData);
}

//----------------------------------------------------------------------------
//
//  Function:   ReadCardGSInfo
//
//  Synopsis:   ��֤��ʧ����ҡ��޸������ҵ�������
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
//  Synopsis:   ���豸����
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
	rpack.head.firstflag   = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag    = 0;    /* �Ƿ����������*/
	rpack.head.recCount    = 1;    /* �����ļ�¼��*/
	rpack.head.retCode     = 0;     /* ���ش���*/
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

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));  //ǰ��ע��ID
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);
	SetValue(&rpack.head,&rpack.pack, F_SDATE1, pDoc->m_szDeviceID);	  //�豸ID
	SetValue(&rpack.head,&rpack.pack, F_SPHONE3, szDateTime);		     //����ʱ��
	SetValue(&rpack.head,&rpack.pack, F_DAMT0, GetValue(5));//GetValue(info.nDiskFreeSpace/info.nDiskTotalSpace*100) );//Ӳ�����ðٷֱ�
	SetValue(&rpack.head,&rpack.pack, F_DAMT1, GetValue(3));//GetValue(info.nUserMemory/info.nMemoryTotal*100));	//�ڴ����ðٷֱ�
	SetValue(&rpack.head,&rpack.pack, F_DAMT2, GetValue(2));//GetValue(100-info.nCPU));//CPU���ðٷֱ�
	SetValue(&rpack.head,&rpack.pack, F_LVOL2, GetValue(pDoc->m_nStatus)); //�豸״̬		
	SetValue(&rpack.head,&rpack.pack, F_SSERIAL4, pDoc->m_szTableName); //�������汾
	SetValue(&rpack.head,&rpack.pack, F_SHOLDER_AC_NO2, pDoc->m_sDownBlackTime);//�豸��ǰʱ��
	SetValue(&rpack.head,&rpack.pack, F_DAMT3, GetValue(1)); //1δ�ϴ���ˮ����

//WriteLog("SendDeviceTick() pack finished\n");
//WriteLog("�豸:%s,ʱ��:%s::�汾%s::�ն�״̬:%ld\n",pDoc->m_szDeviceID,pDoc->m_sDownBlackTime,pDoc->m_szTableName,pDoc->m_nStatus);

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
		//WriteLog("-----�����豸���������ID[ %s ]---------------\n",pDoc->m_szDeviceID);		
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
						//WriteTickLog("�����豸����������ɹ�! �����:%d, �ӹ��ܺ�:%d, , �豸ID=%s", iServerNo, iFunc, pDoc->m_szDeviceID);						
						return RET_OK;
					}
					else
					{
						WriteTickLog("�����豸���������ʧ��! �豸ID=%s, �����豸���������ʱ����:%s\n", pDoc->m_szDeviceID, apack.pack.vsmess);
					}
				}
				else
					printf("DecodeBuf error");
			}
			else
				printf("debug   ��������ʧ��\n");
		}
	}

	ConnectPool.Free(hHandle);
	WriteLog("�����豸���������ʧ��! �����:%d, �ӹ��ܺ�:%d, �豸ID=%s", iServerNo, iFunc, pDoc->m_szDeviceID);
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
