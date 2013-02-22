 // Interface.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "export.h"
#include "Interface.h"
#include "LocalBlack.h"
#include "ConnectPool.h"
#include "SystemInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"..\\lib\\DRTPApi.lib") 
#pragma message("Automatically linking with DRTPApi.dll")

int  iMServerNo;
int  iMFunc;
long iSmartKey;
char sSmartKey[48];
int  iServerNo;
int  iFunc;
TSSmartDoc *gpSmartDoc = NULL;
long gnDocCount = 0 ;
int  gTick = 1000*60*10;
//int  gTick = 10000;
TSSystemParam  GlobalParam;
bool bSmartSign = false;
CLock  OutLock;
CLock  InLock;
CTestData  TestData;
char  szLogPath[256];
char  szINIFile[256];
int nReload;


unsigned int crctab[256]=
{
 0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,
 0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,0xE1CE,0xF1EF,
 0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,
 0x9339,0x8318,0xB37B,0xA35A,0xD3BD,0xC39C,0xF3FF,0xE3DE,
 0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,
 0xA56A,0xB54B,0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,
 0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
 0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,
 0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,0x2802,0x3823,
 0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,
 0x5AF5,0x4AD4,0x7AB7,0x6A96,0x1A71,0x0A50,0x3A33,0x2A12,
 0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,
 0x6CA6,0x7C87,0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,
 0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
 0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,
 0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,0x9F59,0x8F78,
 0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,
 0x1080,0x00A1,0x30C2,0x20E3,0x5004,0x4025,0x7046,0x6067,
 0x83B9,0x9398,0xA3FB,0xB3DA,0xC33D,0xD31C,0xE37F,0xF35E,
 0x02B1,0x1290,0x22F3,0x32D2,0x4235,0x5214,0x6277,0x7256,
 0xB5EA,0xA5CB,0x95A8,0x8589,0xF56E,0xE54F,0xD52C,0xC50D,
 0x34E2,0x24C3,0x14A0,0x0481,0x7466,0x6447,0x5424,0x4405,
 0xA7DB,0xB7FA,0x8799,0x97B8,0xE75F,0xF77E,0xC71D,0xD73C,
 0x26D3,0x36F2,0x0691,0x16B0,0x6657,0x7676,0x4615,0x5634,
 0xD94C,0xC96D,0xF90E,0xE92F,0x99C8,0x89E9,0xB98A,0xA9AB,
 0x5844,0x4865,0x7806,0x6827,0x18C0,0x08E1,0x3882,0x28A3,
 0xCB7D,0xDB5C,0xEB3F,0xFB1E,0x8BF9,0x9BD8,0xABBB,0xBB9A,
 0x4A75,0x5A54,0x6A37,0x7A16,0x0AF1,0x1AD0,0x2AB3,0x3A92,
 0xFD2E,0xED0F,0xDD6C,0xCD4D,0xBDAA,0xAD8B,0x9DE8,0x8DC9,
 0x7C26,0x6C07,0x5C64,0x4C45,0x3CA2,0x2C83,0x1CE0,0x0CC1,
 0xEF1F,0xFF3E,0xCF5D,0xDF7C,0xAF9B,0xBFBA,0x8FD9,0x9FF8,
 0x6E17,0x7E36,0x4E55,0x5E74,0x2E93,0x3EB2,0x0ED1,0x1EF0
}; 

/************ calc_crc16 ���*************/

void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}

int  calc_crc16(unsigned char len,unsigned char *in,unsigned char *out)
{
	unsigned char i;
	unsigned short crc;		
	crc=0xc78c;
	for(i=0;i<len;in++,i++)
	{
		crcupdata(*in,&crc,crctab);
	}	
    out[0]=(unsigned char)(crc>>8);
	out[1]=(unsigned char)crc;
	
	return 1;
}
/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp

BEGIN_MESSAGE_MAP(CInterfaceApp, CWinApp)
	//{{AFX_MSG_MAP(CInterfaceApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp construction

CInterfaceApp::CInterfaceApp()
{
	gpSmartDoc = NULL;
	gnDocCount = 0 ;
	iServerNo = 0 ;
	iFunc = 9991;
	iSmartKey = 0 ;
	gTick = 600000;

	iMServerNo = 0;
	iMFunc = 9990;


	ZeroMemory(sSmartKey, sizeof(sSmartKey));
	ZeroMemory(&GlobalParam, sizeof(GlobalParam));

	TCHAR szPath[MAX_PATH];

	GetCurPath(szPath);
	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		sprintf(szLogPath, "%�ӿ���־", szPath);
		sprintf(szINIFile, "%sSmartServer.ini", szPath);
	}
	else
	{
		sprintf(szLogPath, "%s\\�ӿ���־", szPath);
		sprintf(szINIFile, "%s\\SmartServer.ini", szPath);
	}

	CreateDirectory(szLogPath, NULL);
	nReload = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInterfaceApp object

CInterfaceApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp initialization
BOOL CInterfaceApp::InitInstance()
{
	return TRUE;
}

//ǩ��
long CInterfaceApp::SignOutDoc(TSSmartDoc *pDoc)
{
	//return RET_OK;
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(ST_CPACK));

	rpack.head.RequestType = 930055; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);		//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_SDATE0, pDoc->m_szDeviceID);	//�ն��豸ID

	char buffer[10960];
	int  nLen = sizeof(buffer);
	char omsg[256];

	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		//printf("SignOutDoc\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			memset(buffer, 0, sizeof(buffer));
			nLen = sizeof(buffer);
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						ConnectPool.Free(hHandle);
						WriteLog("�豸:%sǩ���ɹ�!\n", pDoc->m_szDeviceID);
						return RET_OK;
					}
					else
					{
						printf("%s\n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	WriteLog("�豸:%sǩ��ʧ��!\n", pDoc->m_szDeviceID);

	return RET_SYSERROR;
}

//ǩ��
long CInterfaceApp::SignInDoc(TSSmartDoc *pDoc)
{

	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(ST_CPACK));

	rpack.head.RequestType = 930054; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_SDATE1, pDoc->m_szDeviceID);		//�ն��豸ID

	char buffer[10960];
	int  nLen = sizeof(buffer);
	char omsg[256];
	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
//		printf("SignInDoc\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						strcpy(pDoc->m_szTableName, apack.pack.scust_limit);
						pDoc->m_nStartuse = 1;
						ConnectPool.Free(hHandle);
						WriteLog("��̨�����豸:%sǩ��!\n", pDoc->m_szDeviceID);
						return RET_OK;
					}
					else
					{
						printf("%s\n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	WriteLog("�豸:%sǩ��ʧ��!\n", pDoc->m_szDeviceID);

	return RET_SYSERROR;
}

long CInterfaceApp::SmartSignOut()
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(ST_CPACK));

	rpack.head.RequestType = 930053; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ

	char buffer[10960];
	int  nLen = sizeof(buffer);
	char omsg[256];

	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			memset(buffer, 0, sizeof(buffer));
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						WriteLog("����ǰ������˴�ǩ���ɹ�!\n");
						ConnectPool.Free(hHandle);
						return RET_OK;
					}
					else
					{
						WriteLog("����ǰ������˴�ǩ��ʧ��,���˴ﷵ�ش���:%s\n", apack.pack.vsmess);
						printf("%s\n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	return RET_SYSERROR;
}

long CInterfaceApp::SmartSignIn()
{
	ST_CPACK rpack;
	CSystemInfo info;

	memset(&rpack, 0, sizeof(ST_CPACK));

	rpack.head.RequestType = 930052; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT, sSmartKey);			//��̬��Կ

	WriteLog("����ǰ�û�����˴�ǰ������ǩ��! IP:%s, MAC=%s, ע���=%d, ��̬��Կ=%s\n", info.szIP, info.szMAC, iSmartKey, sSmartKey);

	char buffer[10960];
	int  nLen = sizeof(buffer);
	char omsg[256];

	HANDLE& hHandle = ConnectPool.Alloc();
	
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
					if( !apack.head.retCode )
					{
						strncpy(sSmartKey, apack.pack.scust_limit2, sizeof(sSmartKey));
						strcpy(GlobalParam.szParameter1, apack.pack.snote);
						strcpy(GlobalParam.szParameter2, apack.pack.scert_addr);
						strcpy(GlobalParam.szParameter3, apack.pack.semail2);
						strcpy(GlobalParam.szParameter4, apack.pack.semail);
						strcpy(GlobalParam.szParameter5, apack.pack.saddr);
						ConnectPool.Free(hHandle);

						printf("ǰ�òɼ�������ǩ��: �豸��Ȩ��Կ%s.\n", GlobalParam.szParameter2);
						printf("ǰ�òɼ�������ǩ��: �������汾%s.\n", GlobalParam.szParameter3);
						printf("ǰ�òɼ�������ǩ��: ��������Ч��%s.\n", GlobalParam.szParameter4);
						printf("ǰ�òɼ�������ǩ��: ����ʱ��%s.\n", GlobalParam.szParameter1);
						
						WriteLog("����ǰ������˴�ǩ���ɹ�: �豸��Ȩ��Կ%s.\n", GlobalParam.szParameter2);
						WriteLog("����ǰ������˴�ǩ���ɹ�: �������汾%s.\n", GlobalParam.szParameter3);
						WriteLog("����ǰ������˴�ǩ���ɹ�: ��������Ч��%s.\n", GlobalParam.szParameter4);
						WriteLog("����ǰ������˴�ǩ���ɹ�: ����ʱ��%s.\n", GlobalParam.szParameter1);
						
						return RET_OK;
					}
					else
					{
						WriteLog("ǰ�û�����˴�ǩ��ʧ��! ���˴ﷵ�ش������:%s\n", apack.pack.vsmess);
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
//  Function:   CheckSmartRegister
//
//  Synopsis:   ǰ�û�ע��
//
//  Arguments:  ��
//				
//				
//  History:    ZhangWei   Created
//
//  Notes:
//----------------------------------------------------------------------------
bool CInterfaceApp::CheckSmartRegister()
{
	char szValue[256];

	memset(szValue, 0, sizeof(szValue));
	int nRegister = GetPrivateProfileString("REGISTER", "REGISTER", "0", szValue, 256, szINIFile);
	if( nRegister <= 0 || strcmp(szValue, "1") )
	{
		iSmartKey = 0 ;
		memset(sSmartKey, 0, sizeof(sSmartKey));
		return false;
	}
	else
	{
		GetPrivateProfileString("REGISTER", "KEY", "", sSmartKey, 64, szINIFile);
		iSmartKey = GetPrivateProfileInt("REGISTER", "REGISTERNO", 0, szINIFile);
		if( iSmartKey <= 0 || strlen(sSmartKey) <= 0 ) 
			return false;
		return true;
	}
}

//----------------------------------------------------------------------------
//
//  Function:   SmartRegister
//
//  Synopsis:   ǰ�û�ע��
//
//  Arguments:  ��
//				
//				
//  History:    ZhangWei   Created
//
//  Notes:
//----------------------------------------------------------------------------
long CInterfaceApp::SmartRegister()
{
	if( CheckSmartRegister() )
	{
		return RET_OK;
	}

	CSystemInfo info;

	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(ST_CPACK));

	rpack.head.RequestType = 930051; 
	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	SetValue(&rpack.head,&rpack.pack, F_SCUST_AUTH2, "SMART999");	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT, info.szIP);//info.szIP
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, info.szMAC);	//mac address	
	WriteLog("����ǰ�û�����˴�����ע��! �������IP:%s, MAC=%s.\n", info.szIP, info.szMAC);
	char buffer[10960];
	int  nLen = sizeof(buffer);
	char omsg[256];

	HANDLE& hHandle = ConnectPool.Alloc();
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
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						WritePrivateProfileString("REGISTER", "REGISTERNO", GetValue(apack.pack.lcert_code), szINIFile);
						WritePrivateProfileString("REGISTER", "KEY", apack.pack.scust_limit, szINIFile);
						WritePrivateProfileString("REGISTER", "REGISTER", "1", szINIFile);

						iSmartKey = apack.pack.lcert_code;
						strncpy(sSmartKey, apack.pack.scust_limit, sizeof(sSmartKey));
						WriteLog("����ǰ�û�����˴�ע��ɹ�! ע���:%d, ��Կ:%s\n", apack.pack.lcert_code, apack.pack.scust_limit);
						printf("����ǰ�û�����˴�ע��ɹ�! ע���:%d, ��Կ:%s\n", apack.pack.lcert_code, apack.pack.scust_limit);
						ConnectPool.Free(hHandle);
						return RET_OK;
					}
					else
					{
						printf("%s\n", apack.pack.vsmess);
						WriteLog("����ǰ�û�����˴�ע��ʧ�� ���ս��˴���Ϣ:%s! \n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	WriteLog("����ǰ�û�����˴�ע��ʧ��! \n");

	ConnectPool.Free(hHandle);

	return RET_SYSERROR;
}

//----------------------------------------------------------------------------
//
//  Function:   MakeFirstTaskPlan
//
//  Synopsis:   ���������, ת�����ڲ��õ������
//
//  Arguments:  pTaskPlan   -- �����ڲ��õ������
//				pPacket     -- ���˴������
//  History:    2004-09-21  ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
bool CInterfaceApp::MakeFirstTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow)
{

	bool bResult = true ;
	int iCount   = 0 ;
	
	WriteLog("-------MakeFirstTaskPlan----------[%ld]\n",pPacket->pack.lvol2);
	if( pPacket->pack.lvol2 == 930057 )	
	{
		pTaskPlan->nTaskPlanID	= GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle	=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTime  = 5 ;              //�����೤ʱ�䣨���ӣ�
		pTaskPlan->nRepeatTimes = 1;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��	
		WriteLog("��ʼ��������ط��Ͱ�����:���ܺ�[ %ld]\n",930057);		
		for(int p=0; p< gnDocCount; p++)
		{
			//�ն�
			if( gpSmartDoc[p].m_nParentID )
			{
				pTaskPlan->pTask[pTaskPlan->nTask].nTaskID	   = GetTickCount();
				pTaskPlan->pTask[pTaskPlan->nTask].nTaskPlanID =pTaskPlan->nTaskPlanID; 
				pTaskPlan->pTask[pTaskPlan->nTask].nAuthID     = gpSmartDoc[p].m_nAuthID ;
				strcpy(pTaskPlan->pTask[pTaskPlan->nTask].szDeviceID, gpSmartDoc[p].m_szDeviceID);
				strcpy(pTaskPlan->pTask[pTaskPlan->nTask].szTaskCode,"74");
				pTaskPlan->pTask[pTaskPlan->nTask].nPriority	= 6;					
				pTaskPlan->pTask[pTaskPlan->nTask].nFunc=930057;
				pTaskPlan->nTask++;									
				WriteLog("�����������:�豸ID[ %s ]\n",gpSmartDoc[p].m_szDeviceID);
			}
			//wenjian comment below line
			//Sleep(2); //Ϊ�ú���:GetTickCount();
		}		
		if( pTaskPlan->nTask > 0 )	iCount = 1 ;
		WriteLog("������������������:�ܹ�[ %ld]���� iCount=%ld\n",p,iCount);
	}
	//�ն�״̬
	else if( pPacket->pack.lvol2 == 930058 )	
	{
		pTaskPlan->nTaskPlanID	= GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle	=0;                //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);    //��ʼ����ʱ��
		pTaskPlan->nRepeatTime  = 5 ;              //�����೤ʱ�䣨���ӣ�
		pTaskPlan->nRepeatTimes = 1;               //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);     //����ƻ���ʱ��	
		for(int p=0; p< gnDocCount; p++)
		{			
			//�ն�(ֱ����PC�������豸:��,LPORT,��̫����ʱ��)
			if( !gpSmartDoc[p].m_nParentID )
			{
				pTaskPlan->pTask[pTaskPlan->nTask].nTaskID	   = GetTickCount();
				pTaskPlan->pTask[pTaskPlan->nTask].nTaskPlanID = pTaskPlan->nTaskPlanID; 
				pTaskPlan->pTask[pTaskPlan->nTask].nAuthID     = gpSmartDoc[p].m_nAuthID ;
				strcpy(pTaskPlan->pTask[pTaskPlan->nTask].szDeviceID, gpSmartDoc[p].m_szDeviceID);
				strcpy(pTaskPlan->pTask[pTaskPlan->nTask].szTaskCode,"75");
				pTaskPlan->pTask[pTaskPlan->nTask].nPriority	= 6;					
				pTaskPlan->pTask[pTaskPlan->nTask].nFunc=930058;
				pTaskPlan->nTask++;				
				Sleep(1); 
				WriteLog("ȡ�ն�״̬����:�豸ID[ %s ]\n",gpSmartDoc[p].m_szDeviceID);
			}
		}		
		if( pTaskPlan->nTask > 0 )	iCount = 1 ;
	}
	//----�㲥������
	else if( pPacket->pack.lvol2 == 930005 )
	{
		WriteLog("���˴��´�㲥����������: �豸%s, ���ܺ�:%d, ����:%d.......\n", "00000000", pPacket->pack.lvol2, pPacket->pack.lvol0);
		AnswerResult(pPacket->pack.lvol2, pPacket->pack.lvol1, 0, "�յ��㲥��Ϣ!");

		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTime = 5 ;              //�����೤ʱ�䣨���ӣ�
		pTaskPlan->nRepeatTimes = 1;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��
		pTaskPlan->nTask = 0 ;

		int p=0;
		char tmp[20];
		memset(tmp, 0x00, sizeof tmp);
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

				sprintf(pTaskPlan->pTask[p].szMemo,"%08ld",pPacket->pack.lvol0);
				memcpy(pTaskPlan->pTask[p].szMemo+8,pPacket->pack.sserial0,12);
				p++;
				pTaskPlan->nTask++;				
			}
			//wenjian comment below line
			//Sleep(3);
		}
		if( pTaskPlan->nTask > 0 )	iCount = 1 ;
	}
	//�������ѱ�ż��汾
	else if( pPacket->pack.lvol2 == 930011 )
	{
		TSSmartDoc *pDoc = CheckDeviceID(pPacket->pack.sdate0);
		if( pDoc == NULL )
		{
			WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....û�д��豸!\n", pPacket->pack.sdate0, pPacket->head.RequestType);
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "û�д��豸!");
			return false;
		}

		if( strlen(pPacket->pack.sserial2) != 12 )
		{
			WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....�������Ϸ�!\n", pDoc->m_szDeviceID, pPacket->head.RequestType);
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "�������Ϸ�!");
			return false;
		}

		long nAuthID = pDoc->m_nAuthID;
		WriteLog("���˴��´�����: �豸%s, ���ܺ�:%d...\n", pDoc->m_szDeviceID, pPacket->head.RequestType);

		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTimes = 1 ;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��

		pTaskPlan->nTask = 1 ;
		pTaskPlan->pTask[0].nTaskID = GetTickCount();
		pTaskPlan->pTask[0].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[0].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[0].szDeviceID, pDoc->m_szDeviceID);      
		strcpy(pTaskPlan->pTask[0].szTaskCode,"104");
		pTaskPlan->pTask[0].nPriority = 6;
		pTaskPlan->pTask[0].nFunc = 930011; 
		sprintf(pTaskPlan->pTask[0].szSystemNO, "%d", pPacket->pack.lvol1);

		TSAttachData *pData = &m_SAttachData;
		if( pData == NULL )
		{
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "ϵͳ����!");
			return false;
		}

		int *pNo = new int[nRow];
		if( pNo == NULL )
		{
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "ϵͳ����!");
			delete pData;
			return false;
		}

		ZeroMemory(pData, sizeof(TSAttachData));
		ZeroMemory(pNo, sizeof(int)*nRow);

		pData->pData = (void*)pNo;
		pTaskPlan->pTask[0].pData = (char*)pData;

		pData->nCount = nRow;
		strncpy(pData->szValue, pPacket->pack.sserial2,12);

		for(int i=0; i< nRow; i++)
		{
			if( !i )
			{
				pNo[i] = pPacket->pack.lvol4;
			}
			else
			{
				pNo[i] = pArray[i-1].lvol4;
			}
		}
		iCount = 1 ;
	}
	//�������ѿ�ݱ��
	else if( pPacket->pack.lvol2 == 930012 )
	{
		TSSmartDoc *pDoc = CheckDeviceID(pPacket->pack.sdate0);
		if( pDoc == NULL )
		{
			WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....û�д��豸!\n", pPacket->pack.sdate0, pPacket->head.RequestType);
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "û�д��豸!");
			return false;
		}

		long nAuthID = pDoc->m_nAuthID;
		WriteLog("���˴��´�����: �豸%s, ���ܺ�:%d...\n", pDoc->m_szDeviceID, pPacket->head.RequestType);

		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTimes = 1 ;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��

		pTaskPlan->nTask = 1 ;
		pTaskPlan->pTask[0].nTaskID = GetTickCount();
		pTaskPlan->pTask[0].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[0].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[0].szDeviceID, pDoc->m_szDeviceID);      
		strcpy(pTaskPlan->pTask[0].szTaskCode,"105");
		pTaskPlan->pTask[0].nPriority = 6;
		pTaskPlan->pTask[0].nFunc = 930012; 
		sprintf(pTaskPlan->pTask[0].szSystemNO, "%d", pPacket->pack.lvol1);
		strcpy(pTaskPlan->pTask[0].szMemo, 	pPacket->pack.saddr);//modified by lina 20050318

		iCount = 1 ;
	}
	//��������ʱ��β���
	else if( pPacket->pack.lvol2 == 930013 )
	{
		TSSmartDoc *pDoc = CheckDeviceID(pPacket->pack.sdate0);
		if( pDoc == NULL )
		{
			WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....û�д��豸!\n", pPacket->pack.sdate0, pPacket->head.RequestType);
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "û�д��豸!");
			return false;
		}

		long nAuthID = pDoc->m_nAuthID;
		WriteLog("���˴��´�����: �豸%s, ���ܺ�:%d...\n", pDoc->m_szDeviceID, pPacket->head.RequestType);

		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTimes = 1 ;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��

		pTaskPlan->nTask = 1 ;
		pTaskPlan->pTask[0].nTaskID = GetTickCount();
		pTaskPlan->pTask[0].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[0].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[0].szDeviceID, pDoc->m_szDeviceID);      
		strcpy(pTaskPlan->pTask[0].szTaskCode,"107");
		pTaskPlan->pTask[0].nPriority = 6;
		pTaskPlan->pTask[0].nFunc = 930013; 
		sprintf(pTaskPlan->pTask[0].szSystemNO, "%d", pPacket->pack.lvol1);

		TSAttachData *pData = &m_SAttachData;
		if( pData == NULL )
		{
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "ϵͳ����!");
			return false;
		}

		TSXFTimePara *pNo = new TSXFTimePara[nRow];
		if( pNo == NULL )
		{
			AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "ϵͳ����!");
			delete pData;
			return false;
		}

		ZeroMemory(pData, sizeof(TSAttachData));
		ZeroMemory(pNo, sizeof(TSXFTimePara)*nRow);

		pData->pData = (void*)pNo;
		pTaskPlan->pTask[0].pData = (char*)pData;
		pData->nCount = nRow;

		for(int i=0; i< nRow; i++)
		{
			if( !i )
			{
				strncpy(pNo[i].szBeginTime, pPacket->pack.sopen_emp, 5);
				strncpy(pNo[i].szEndTime, pPacket->pack.sclose_emp, 5);
				strncpy(pNo[i].szClass, pPacket->pack.snote2, 64);
				pNo[i].nTimes = pPacket->pack.lvol5;
				pNo[i].nMoney = pPacket->pack.lvol4;
			}
			else
			{
				strncpy(pNo[i].szBeginTime, pArray[i-1].sopen_emp, 5);
				strncpy(pNo[i].szEndTime, pArray[i-1].sclose_emp, 5);
				strncpy(pNo[i].szClass, pArray[i-1].snote2, 64);
				pNo[i].nTimes = pArray[i-1].lvol5;
				pNo[i].nMoney = pArray[i-1].lvol4;
			}

			if( strlen(pNo[i].szBeginTime) != 5 || strlen(pNo[i].szEndTime) != 5 || 
				pNo[i].nTimes < 0 )
			{
				delete [] pNo;
				pData->pData = NULL;
				pTaskPlan->pTask[0].pData = NULL;
				WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....�������Ϸ�!\n", pDoc->m_szDeviceID, pPacket->head.RequestType);
				AnswerResultError(pPacket->pack.lvol2, pPacket->pack.lvol1, -1, "�������Ϸ�!");
				return false;
			}
		}
		iCount = 1 ;
	}
	//�㲥������
	else if( pPacket->pack.lvol2 == 930118 )
	{

		WriteLog("���˴��´�㲥����������: �豸%s, ���ܺ�:%d, ����:%d.......\n", "00000000", pPacket->pack.lvol2, pPacket->pack.lvol3);
		AnswerResult(pPacket->pack.lvol2, pPacket->pack.lvol1, 0, "�յ��㲥��Ϣ!");
		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTime = 5 ;              //�����೤ʱ�䣨���ӣ�
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
				strcpy(pTaskPlan->pTask[p].szTaskCode,"135");
				pTaskPlan->pTask[p].nPriority = 9;
				pTaskPlan->pTask[p].nFunc = 930118;
				sprintf(pTaskPlan->pTask[p].szSystemNO, "%d", pPacket->pack.lvol1);
				BYTE hex[10],*pt=NULL;
				memset(hex, 0x00, sizeof hex );
				SVC_DSP_2_HEX((unsigned char*)pPacket->pack.sserial0,hex,6);
				pt = (BYTE*)&pPacket->pack.lvol3;
				pTaskPlan->pTask[p].szMemo[0]=*(pt+2);
				pTaskPlan->pTask[p].szMemo[1]=*(pt+1);
				pTaskPlan->pTask[p].szMemo[2]=*(pt+0);
				memcpy(&pTaskPlan->pTask[p].szMemo[3],hex,6);				
				WriteLog("�㲥������(%d). �汾=%s. ����=%ld\n", pPacket->pack.lvol2, pPacket->pack.sserial0,pPacket->pack.lvol3 );
				p++;
				pTaskPlan->nTask++;			
			}
			//wenjian comment below line
			//Sleep(3);
		}
		if( pTaskPlan->nTask > 0 )
		{
			iCount = 1 ;
		}
	}
	//�������ܰ�
	else
	{
		pTaskPlan->nTaskPlanID = GetTickCount()-5;
		sprintf(pTaskPlan->szTaskName,"���ܺ�:%d", pPacket->head.RequestType); //����ƻ�����
		pTaskPlan->nTaskCycle=0;                  //����ƻ�ִ������
		GetCurDateTime(pTaskPlan->szBeginTime);   //��ʼ����ʱ��
		pTaskPlan->nRepeatTime = 1 ;              //�����೤ʱ�䣨���ӣ�
		pTaskPlan->nRepeatTimes = 1 ;             //�ظ�����
		GetCurDateTime(pTaskPlan->szTaskTime);    //����ƻ���ʱ��
		pTaskPlan->nTask = 0 ;

		WriteLog("���˴��´�����: �豸%s, ���ܺ�:%d...\n", pPacket->pack.sdate0, pPacket->pack.lvol2);

		if( !strcmp(pPacket->pack.sdate0, ALLDEVICE) )
		{
			for(int i=0; i< gnDocCount; i++)
			{
				if( FillTask(gpSmartDoc[i].m_szDeviceID, pTaskPlan, pPacket->pack.lvol2, &pPacket->pack) )
					iCount++;
				//wenjian  comment below line
				//Sleep(2);
			}
		}
		else
		{
			for(int i=0; i< nRow; i++)
			{
				if( !i )
				{
					if( FillTask(pPacket->pack.sdate0, pTaskPlan, pPacket->pack.lvol2, &pPacket->pack) )
						iCount ++;
				}
				else
				{
					if( FillTask(pArray[i-1].sdate0, pTaskPlan, pPacket->pack.lvol2, &pArray[i-1]) )
						iCount ++;
				}
				//wenjian comment below line
				//Sleep(2);
			}
		}
	}
	
	WriteLog("------End Make First Task Plan----- iCount = %d\n",iCount);
	return (iCount<=0?false:true);
}

//----------------------------------------------------------------------------
//
//  Function:   MakeNextTaskPlan
//
//  Synopsis:   ���������, ת�����ڲ��õ������
//
//  Arguments:  pTaskPlan   -- �����ڲ��õ������
//				pPacket     -- ���˴������
//  History:    2004-09-21  ZhangWei   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
bool CInterfaceApp::MakeNextTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow)
{
	return true;
}

//----------------------------------------------------------------------------
//
//  Function:   ConvertError
//
//  Synopsis:   û�����ݻ�Ӳ������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertError(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{
	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930098; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.userdata = 0;
	pPacket->head.retCode = 0;     /* ���ش���*/

	if( nType == 0x09 )
	{
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�޼�¼������");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "10");	//����
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�ն��޷�Ӧ");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "-6");	//����
	}

	pPacket->head.RequestType = 930098; 
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);		//��ϢID

	return RET_OK;
}


//----------------------------------------------------------------------------
//
//  Function:   ConvertDealData
//
//  Synopsis:   ��Ӳ��������ת��Ϊ��������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertDealData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{

	TSSFTable	table;	
	ZeroMemory(&table, sizeof(table));

	printf("===========���ѽ�������================================\n");

	sprintf(table.sAuthData,"%.2X%.2X%.2X%.2X", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
	sprintf(table.sCommVer,"%d",ucRawData[4]);	

	printf("ע �� ��: %s\n", table.sAuthData);
	printf("ͨ�Ű汾: %s\n", table.sCommVer);	
	
	//��Ŀ�շ�	
	BYTE str=ucRawData[4];
	if( str==0x81 )
	{
		table.sWalletcode[0]='0';		
		printf("��ĿǮ����:%s\n",      table.sWalletcode);
		sprintf(table.sCommStart, "%d",ucRawData[5]);		
		printf("��Ŀ����ԭ��:%s\n",    table.sCommStart);
	}
	else //��������
	{
		sprintf(table.sWalletcode , "%d", ucRawData[5]>>4); 		
		printf("����Ǯ����:%s\n",table.sWalletcode);
		sprintf(table.sCommStart, "%d",ucRawData[5]&0x0F);		
		printf("��������ԭ��:%s\n",table.sCommStart);
	}

	table.nCardID = ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10];	
	printf("���׿���:%ld\n", table.nCardID);
    table.nInvoiceNo = ucRawData[6]*256+ucRawData[7];		
	printf("������ˮ��:%.5d\n",table.nInvoiceNo);

	sprintf(table.sCRCData,"%.2X%.2X",ucRawData[26],ucRawData[27]);
	printf("CRC:%s\n",table.sCRCData);

	if( ucRawData[12] >= 100 || ucRawData[13] >= 100 || 
		ucRawData[14] >= 100 || ucRawData[15] >= 100 ||
		ucRawData[16] >= 100 
	  )
	{
		sprintf(table.sDealDateTime, "%02d%02d%02d %02d%02d%02d", 00, 1, 1, 1,1,1);
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n", 00, 1, 1, 1,1,1);

	}
	else
	{
		sprintf(table.sDealDateTime,"%02d%02d%02d %02d%02d%02d",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]); 
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]);
	}
	table.nTimes = ucRawData[17]*256+ucRawData[18]; 	
	printf("��Ƭ�ۼ�ʹ�ô���:%d\n",table.nTimes); 

	table.nInMoney = ucRawData[19]+ucRawData[20]*256+ucRawData[21]*65536;	
	printf("�뿨���(��):%d\n", table.nInMoney); 

	table.nOutMoney = ucRawData[22]+ucRawData[23]*256+ucRawData[24]*65536;	
	printf("�������(��):%d\n", table.nOutMoney);

	sprintf(table.sDealCode1, "%d",ucRawData[25]);
	printf("���ױ��:%02x\n",ucRawData[25]); 


	//У��CRC
	BYTE crc[3];	
	memset(crc, 0x00, sizeof crc );
	calc_crc16(26,ucRawData,crc);
	if( (crc[0] != ucRawData[26]) || (crc[1] != ucRawData[27]) )
	{
		printf(".......................���ѽ��������ϴ�ʱ,У��CRC��\n");
		return RET_DATACRC_ERROR;
	}

	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930031; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;
	
	if( nType == 0x21 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");	//����
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(table.nInvoiceNo));	//������ˮ��
	}
	
	char *p = GetValue(table.nInvoiceNo);
	
	CString strTime = table.sDealDateTime;
	
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, table.sAuthData);			//�ն��豸ID
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(table.nCardID));		//���׿���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, table.sWalletcode);			//Ǯ����
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE, strTime.Left(6).GetBuffer(0));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, strTime.Right(6).GetBuffer(0));		//����ʱ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(table.nTimes));							//�ۼ�ʹ�ô���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(table.nInMoney-table.nOutMoney));			//�������ѽ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(table.nInMoney));							//�뿨���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(table.nOutMoney));						//�������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, table.sDealCode1);						//���ױ��
	
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, table.sCommVer);						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, table.sCommStart);					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, table.sCRCData);				//CRC
	return RET_OK;
}

//----------------------------------------------------------------------------
//
//  Function:   ConvertDealData1
//
//  Synopsis:   ��Ӳ��������ת��Ϊ�ֽ��ֵ����
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertDealData1(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{
	if( ++(pDoc->m_wFlowNo) > 65535 )
		pDoc->m_wFlowNo=0 ;

	pDoc->m_nDealCount++;
	pDoc->m_nInMoney += 100 ;
	pDoc->m_nOutMoney = pDoc->m_nInMoney + 100 ;

	TSSFTable   table;
	ZeroMemory(&table, sizeof(table));


	printf("==========��ֵ����==================================\n");

	sprintf(table.sAuthData,"%.2X%.2X%.2X%.2X", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
	printf("ע���:%s\n", table.sAuthData);

	sprintf(table.sCommVer,"%d",ucRawData[4]);
	printf("ͨ�Ű汾:%s\n",table.sCommVer);

	//sprintf(table.sWalletcode , "%d", ucRawData[5]);//ucRawData[5]>>4); 
	sprintf(table.sWalletcode , "%d", ucRawData[5]>>4); 
	printf("Ǯ����:%s\n",table.sWalletcode);

	sprintf(table.sCommStart, "%d",ucRawData[5]&0x0F);
	printf("����ԭ��:%s\n",table.sCommStart);

	table.nCardID = ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10];
	printf("���׿���:%d\n", table.nCardID);

    table.nInvoiceNo = ucRawData[6]*256+ucRawData[7];
	printf("������ˮ��:%.5d\n", table.nInvoiceNo);

	if( ucRawData[12] >= 100 || ucRawData[13] >= 100 || 
		ucRawData[14] >= 100 || ucRawData[15] >= 100  || ucRawData[16] >= 100 )
	{
		sprintf(table.sDealDateTime, "%02d%02d%02d %02d%02d%02d", 00, 1, 1, 1,1,1);
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n", 00, 1, 1, 1,1,1);
	}
	else
	{
		sprintf(table.sDealDateTime,"%02d%02d%02d %02d%02d%02d",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]); 
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]);
	}

	table.nTimes = ucRawData[17]*256+ucRawData[18]; 
	printf("��Ƭ�ۼ�ʹ�ô���:%d\n",table.nTimes); 

	table.nInMoney = ucRawData[19]+ucRawData[20]*256+ucRawData[21]*65536;
	printf("�뿨���(��):%d\n", table.nInMoney); 

	table.nOutMoney = ucRawData[22]+ucRawData[23]*256+ucRawData[24]*65536;
	printf("�������(��):%d\n",table.nOutMoney);

	sprintf(table.sDealCode1, "%d",ucRawData[25]);
	printf("���ױ��:%s\n",table.sDealCode1); 

	sprintf(table.sCRCData,"%.2X%.2X",ucRawData[26],ucRawData[27]);
	printf("CRC:%s\n",table.sCRCData);


	//У��CRC
	BYTE crc[3];
	memset(crc, 0x00, sizeof crc );
	calc_crc16(26,ucRawData,crc);
	if( (crc[0] != ucRawData[26]) || (crc[1] != ucRawData[27]) )
	{
		printf("...........................��ֵ���������ϴ�ʱ,У��CRC��\n");
		return RET_DATACRC_ERROR;
	}

	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930034; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	if( nType == 0x26 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");	//����
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(table.nInvoiceNo));	//������ˮ��
	}

	CString strTime = table.sDealDateTime;
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, table.sAuthData);			//�ն��豸ID
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(table.nCardID));	//���׿���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, table.sWalletcode);			//Ǯ����
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE, strTime.Left(6).GetBuffer(0));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, strTime.Right(6).GetBuffer(0));		//����ʱ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(table.nTimes));								//�ۼ�ʹ�ô���

	char  szSub[256];
	sprintf(szSub, "%d", table.nOutMoney-table.nInMoney);
	printf("���γ�ֵ���:%s....\n", szSub);

	SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, szSub);			//�������ѽ��

	SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(table.nInMoney));							//�뿨���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(table.nOutMoney));							//�������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, table.sDealCode1);						//���ױ��

	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, table.sCommVer);						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, table.sCommStart);					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, table.sCRCData);				//CRC

	return RET_OK;
}


//----------------------------------------------------------------------------
//
//  Function:   ConvertDealData1
//
//  Synopsis:   ��Ӳ��������ת��Ϊ�ֽ��ֵ���������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertDealData2(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{
	TSSFTable   table;
	ZeroMemory(&table, sizeof(table));

	printf("==========��ֵ���������==================================\n");

	sprintf(table.sAuthData,"%.2X%.2X%.2X%.2X", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
	printf("ע���:%s\n", table.sAuthData);

	sprintf(table.sCommVer,"%d",ucRawData[4]);
	printf("ͨ�Ű汾:%s\n",table.sCommVer);

	sprintf(table.sCommStart, "%d",ucRawData[5]&0x0F);
	printf("����ԭ��:%.2X\n",table.sCommStart);

	table.nCardID = ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10];
	printf("���׿���:%d\n", table.nCardID);

    table.nInvoiceNo = ucRawData[6]*256+ucRawData[7];
	printf("������ˮ��:%.5d\n", table.nInvoiceNo);

	if( ucRawData[12] >= 100 || ucRawData[16] >= 100 || 
		ucRawData[13] >= 100 || ucRawData[14] >= 100  || ucRawData[15] >= 100 )
	{
		sprintf(table.sDealDateTime, "%02d%02d%02d %02d%02d%02d", 00, 1, 1, 1,1,1);
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d \n", 00, 1, 1, 1,1,1);
	}
	else
	{
		sprintf(table.sDealDateTime,"%02d%02d%02d %02d%02d%02d",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]); 
		printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n",ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]);
	}

	table.nTimes = ucRawData[17]*256+ucRawData[18]; 
	printf("��Ƭ�ۼ�ʹ�ô���:%d\n",table.nTimes); 

	table.nInMoney = ucRawData[19]+ucRawData[20]*256+ucRawData[21]*65536;
	printf("�뿨���(��):%d\n",table.nInMoney); 

	table.nOutMoney = ucRawData[22]+ucRawData[23]*256+ucRawData[24]*65536;
	printf("����ѽ��(��):%d\n",table.nOutMoney);

	sprintf(table.sDealCode1, "%d",ucRawData[25]);
	printf("���ױ��:%s\n",table.sDealCode1); 

	sprintf(table.sCRCData,"%.2X%.2X",ucRawData[26],ucRawData[27]);
	printf("CRC:%s\n",table.sCRCData);

	//У��CRC
	BYTE crc[3];
	memset(crc, 0x00, sizeof crc );
	calc_crc16(26,ucRawData,crc);
	if( (crc[0] != ucRawData[26]) || (crc[1] != ucRawData[27]) )
	{
		return RET_DATACRC_ERROR;
	}
	
	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930036; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	if( nType == 0x27 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");	//����
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(table.nInvoiceNo));	//������ˮ��
	}

	CString strTime = table.sDealDateTime;
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, table.sAuthData);			//�ն��豸ID
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nInvoiceNo));	//������ˮ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(table.nCardID));	//���׿���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, table.sWalletcode);			//Ǯ����
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE, strTime.Left(6).GetBuffer(0));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, strTime.Right(6).GetBuffer(0));		//����ʱ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(table.nTimes));					//�ۼ�ʹ�ô���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(table.nOutMoney));			//�������ѽ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(table.nInMoney));				//�뿨���
	//delete by lina 20050404SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(0));							//�������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(table.nInMoney));							//�������

	SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, table.sDealCode1);				//���ױ��

	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, table.sCommVer);						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, table.sCommStart);					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, table.sCRCData);				//CRC

	return RET_OK;
}


//----------------------------------------------------------------------------
//
//  Function:   ConvertIdentifyData
//
//  Synopsis:   ��Ӳ��������ת��Ϊ��ʱ������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertIdentifyData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{
	TSJSBTable   table;
	BYTE   str=0x00;
	ZeroMemory(&table, sizeof(table));

	printf("===========��ʱ������================================\n");

	sprintf(table.sAuthData,"%.2X%.2X%.2X%.2X",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); 
	printf("ע���:%.2X%.2X%.2X%.2X\n",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); 

	sprintf(table.sCommVer,"%.2X",ucRawData[4]); 
	printf("ͨ�Ű汾:%.2X\n",ucRawData[4]); 

	sprintf(table.sCommStart,"%.2X",ucRawData[5]); 
	printf("����ԭ��:%.2X\n",ucRawData[5]); 

	table.nInvoiceNo = ucRawData[6]*256+ucRawData[7];	 
	printf("������ˮ��:%.5d\n",ucRawData[6]*256+ucRawData[7]);	 

	table.nICCardCode = ucRawData[22];
	printf("���ʹ���:%d\n",ucRawData[22]);

	table.nWorkMode = ucRawData[20];
	printf("����ģʽ����:%d\n",ucRawData[20]);

	if( table.nICCardCode == 0 )
	{
		table.nCardID = ucRawData[9]*256*256*256+ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12];		
	}
	else if( table.nICCardCode == 100 )
	{
		if( table.nWorkMode == 4 )
			table.nCardID = 0 ;
		else
			table.nCardID = ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12];
	}
	else if( table.nICCardCode == 101 )
	{
		table.nCardID = ucRawData[11]*256+ucRawData[12];	 
	}
	else
	{
		table.nCardID = 0 ;
	}

	//printf("����:%02X%02X%02X%02X\n",ucRawData[12],ucRawData[11],ucRawData[10],ucRawData[9]);	
	printf("����:%ld\n",table.nCardID);	

	if( table.nWorkMode == 4 && (table.nICCardCode == 100 || table.nICCardCode == 101 ) )
	{
		sprintf(table.sShowCardNo,"%.2X%.2X%.2X%.2X%.2X",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); 
		printf("��ʾ����:%.2X%.2X%.2X%.2X%.2X\n",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); 
	}

	sprintf(table.sDealDateTime,"%02d%02d%02d %02d%02d%02d",ucRawData[13]+2000,ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18]); 
	printf("����ʱ��:%02d%02d%02d %02d%02d%02d\n",ucRawData[13]+2000,ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18]); 
	CString strTime = table.sDealDateTime;

	table.nTimerType = ucRawData[21];
	printf("��������:%d\n",ucRawData[21]); 

	table.nICCardCode = ucRawData[22]; 
	printf("���ʹ���:%d\n",table.nICCardCode); 

	table.nInductorNo = ucRawData[23]; 
	printf("��Ӧͷ���:%d\n",ucRawData[23]); 

	table.nDutyFlag = ucRawData[24]; 
	printf("���°���:%02X\n",ucRawData[24]); 

	if( table.nDutyFlag > 9 )
	{
		table.nDutyFlag = 0 ;
	}
	table.sDealCode1[0] = ucRawData[25]; 
	printf("���ױ�ʶ:%02x\n",(BYTE)table.sDealCode1[0]); 	

	sprintf(table.sCRCData,"%X%X",ucRawData[26],ucRawData[27]); 	
	printf("У����:%s\n",table.sCRCData); 


	//У��CRC
	BYTE crc[3];
	memset(crc, 0x00, sizeof crc );
	calc_crc16(26,ucRawData,crc);
	if( (crc[0] != ucRawData[26]) || (crc[1] != ucRawData[27]) )
	{
		return RET_DATACRC_ERROR;
	}

	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930098; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ	
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);		//��ϢID
	SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�ռ�ʱ�����ɹ�");	//��������Ϣ
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");	//����

	SetValue(&pPacket->head,&pPacket->pack, F_SDATE0, table.sAuthData);				//�ն��豸ID	
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL3, GetValue(table.nInvoiceNo));	//������ˮ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(table.nICCardCode));	//���ʹ���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, GetValue(table.nWorkMode));	//����ģʽ����	
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(table.nCardID));		//���׿���
	SetValue(&pPacket->head,&pPacket->pack, F_SSTATION0, table.sShowCardNo);		//��ʾ����
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, strTime.Left(8).GetBuffer(0));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, strTime.Right(6).GetBuffer(0));		//����ʱ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(table.nTimerType));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(table.nInductorNo));		//��Ӧͷ���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(table.nDutyFlag));		//���°��ʶ
	str = (BYTE)table.sDealCode1[0];
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(str));		//���ױ�ʶ
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, table.sCommVer);		//ͨ�Ű汾��
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, table.sCommStart);		//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, table.sCRCData);		//CRCУ��

	return RET_OK;
}

//----------------------------------------------------------------------------
//
//  Function:   ConvertStateData
//
//  Synopsis:   ��Ӳ��������ת��Ϊ��������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertStateData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{

#if 1
	if( ++(pDoc->m_nBeginInvoice) > 65535 )
		pDoc->m_nBeginInvoice=0 ;

	TSSetlment   m_SRC;
	int  reason=0,ver=0;

	ZeroMemory(&m_SRC, sizeof(m_SRC));

	if( ++(pDoc->m_nBeginInvoice) > 65535 )
		pDoc->m_nBeginInvoice=0 ;

	printf("==============��������===================================\n");

	sprintf(m_SRC.sMachineID, "%.2X%.2X%.2X%.2X",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); 
	printf("ע���:%s\n",m_SRC.sMachineID); 
	ver=ucRawData[4];  //�汾
	reason=ucRawData[5];//ԭ��
	m_SRC.nSettleInvoice = ucRawData[6]*256+ucRawData[7]; 
	printf("������ˮ:%d\n",  m_SRC.nSettleInvoice); 

	if( !IsValidDateTime(&ucRawData[8])  )
	{
		GetCurDateTimeEx(m_SRC.sSettleTime);
	}
	else
	{
		sprintf(m_SRC.sSettleTime, "%02d%02d%02d %02d%02d%02d",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12],ucRawData[13]);  
	}

	printf("����ʱ��:%s\n", m_SRC.sSettleTime);

	m_SRC.nBeginInvoice = ucRawData[14]*256+ucRawData[15]; 
	printf("��ʼ��ˮ��:%d\n",m_SRC.nBeginInvoice); 

	m_SRC.nEndInvoice = ucRawData[16]*256+ucRawData[17]; 
	printf("������ˮ��:%d\n",m_SRC.nEndInvoice); 

	m_SRC.nDealCount = ucRawData[18]*256+ucRawData[19]; 
	printf("���������ܱ���:%d\n",m_SRC.nDealCount); 

	m_SRC.nDealAmount = ucRawData[20]+ucRawData[21]*256+ucRawData[22]*65536; 
	printf("���������ܽ��:%d\n",m_SRC.nDealAmount); 

	m_SRC.nCancelCount = ucRawData[23]*256+ucRawData[24];
	printf("���������ܱ���:%d\n",m_SRC.nCancelCount);  

	m_SRC.nCancelAmount = ucRawData[25]+ucRawData[26]*256+ucRawData[27]*65536 ;
	printf("���������ܽ��:%d\n",m_SRC.nCancelAmount); 

	m_SRC.nExcepCount = ucRawData[28]*256+ucRawData[29] ;
	printf("�쳣�����ܱ���%d\n",m_SRC.nExcepCount); 

	m_SRC.nExcepACount = ucRawData[30]+ucRawData[31]*256+ucRawData[32]*65536 ;
	printf("�쳣�����ܽ��%d\n",m_SRC.nExcepACount); 

	m_SRC.nOtherCount = ucRawData[33]*256+ucRawData[34] ;
	printf("���������ܱ���:%d\n",m_SRC.nOtherCount); 

	m_SRC.nOuterkeeper = ucRawData[35];
	printf("���ʱ��:%.2X\n",m_SRC.nOuterkeeper);

	sprintf(m_SRC.sCRCData,"%.2X%.2X",ucRawData[36],ucRawData[37]);
	printf("CRC:%s\n",m_SRC.sCRCData);

	//У��CRC
	BYTE crc[3];
	memset(crc, 0x00, sizeof crc );
	calc_crc16(36,ucRawData,crc);
	if( (crc[0] != ucRawData[36]) || (crc[1] != ucRawData[37]) )
	{
		return RET_DATACRC_ERROR;
	}
	
	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930035; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	if( nType == 0x23 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(RET_OK));	//����

		SetValue(&pPacket->head,&pPacket->pack, F_SDATE0, m_SRC.sMachineID);			//�ն��豸ID		
		SetValue(&pPacket->head,&pPacket->pack, F_LSERIAL0, GetValue(m_SRC.nSettleInvoice));	//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_SNAME, m_SRC.sSettleTime);			//������ֹʱ��		
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(m_SRC.nBeginInvoice));	//��ʼ�ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, GetValue(m_SRC.nEndInvoice));	//�����ն˽�����ˮ��		
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(m_SRC.nDealCount));		//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(m_SRC.nDealAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(m_SRC.nCancelCount));	//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(m_SRC.nCancelAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(m_SRC.nExcepCount));	//�쳣�����ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, GetValue(m_SRC.nExcepACount));	//�쳣�����ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LSAFE_LEVEL, GetValue(m_SRC.nOtherCount));	//������¼�ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LSAFE_LEVEL2, GetValue(m_SRC.nOuterkeeper));	//���ʱ�־

	
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(RET_OK));	//����

		SetValue(&pPacket->head,&pPacket->pack, F_SDATE0, m_SRC.sMachineID);			//�ն��豸ID		
		SetValue(&pPacket->head,&pPacket->pack, F_LSERIAL0, GetValue(m_SRC.nSettleInvoice));	//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_SNAME, m_SRC.sSettleTime);			//������ֹʱ��		
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(m_SRC.nBeginInvoice));	//��ʼ�ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, GetValue(m_SRC.nEndInvoice));	//�����ն˽�����ˮ��		
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(m_SRC.nDealCount));		//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(m_SRC.nDealAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(m_SRC.nCancelCount));	//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(m_SRC.nCancelAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(m_SRC.nExcepCount));	//�쳣�����ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, GetValue(m_SRC.nExcepACount));	//�쳣�����ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LSAFE_LEVEL, GetValue(m_SRC.nOtherCount));	//������¼�ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LSAFE_LEVEL2, GetValue(m_SRC.nOuterkeeper));	//���ʱ�־

	}
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE,GetValue(ver));						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, GetValue(reason));					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, m_SRC.sCRCData);				//CRC

	return RET_OK;
#else
	if( ++(pDoc->m_nBeginInvoice) > 65535 )
		pDoc->m_nBeginInvoice=0 ;

	TSSetlment   m_SRC;
	ZeroMemory(&m_SRC, sizeof(m_SRC));

	printf("==============��������===================================\n");

	sprintf(m_SRC.sMachineID, "%.2X%.2X%.2X%.2X",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); 
	printf("ע���:%s\n",m_SRC.sMachineID); 

	m_SRC.nSettleInvoice = ucRawData[6]*256+ucRawData[7]; 
	printf("������ˮ:%d\n",  m_SRC.nSettleInvoice); 

	if( !IsValidDateTime(&ucRawData[8])  )
	{
		GetCurDateTimeEx(m_SRC.sSettleTime);
	}
	else
	{
		sprintf(m_SRC.sSettleTime, "%02d%02d%02d %02d%02d%02d",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12],ucRawData[13]);  
	}

	printf("����ʱ��:%s\n", m_SRC.sSettleTime);

	m_SRC.nBeginInvoice = ucRawData[14]*256+ucRawData[15]; 
	printf("��ʼ��ˮ��:%d\n",m_SRC.nBeginInvoice); 

	m_SRC.nEndInvoice = ucRawData[16]*256+ucRawData[17]; 
	printf("������ˮ��:%d\n",m_SRC.nEndInvoice); 

	m_SRC.nDealCount = ucRawData[18]*256+ucRawData[19]; 
	printf("���������ܱ���:%d\n",m_SRC.nDealCount); 

	m_SRC.nDealAmount = ucRawData[20]+ucRawData[21]*256+ucRawData[22]*65536; 
	printf("���������ܽ��:%d\n",m_SRC.nDealAmount); 

	m_SRC.nCancelCount = ucRawData[23]*256+ucRawData[24];
	printf("���������ܱ���:%d\n",m_SRC.nCancelCount);  

	m_SRC.nCancelAmount = ucRawData[25]+ucRawData[26]*256+ucRawData[27]*65536 ;
	printf("���������ܽ��:%d\n",m_SRC.nCancelAmount); 

	m_SRC.nExcepCount = ucRawData[28]*256+ucRawData[29] ;
	printf("�쳣�����ܱ���%d\n",m_SRC.nExcepCount); 

	m_SRC.nExcepACount = ucRawData[30]+ucRawData[31]*256+ucRawData[32]*65536 ;
	printf("�쳣�����ܽ��%d\n",m_SRC.nExcepACount); 

	m_SRC.nOtherCount = ucRawData[33]*256+ucRawData[34] ;
	printf("���������ܱ���:%d\n",m_SRC.nOtherCount); 

	m_SRC.nOuterkeeper = ucRawData[35];
	printf("���ʱ��:%.2X\n",m_SRC.nOuterkeeper);

	sprintf(m_SRC.sCRCData,"%.2X%.2X",ucRawData[36],ucRawData[37]);
	printf("CRC:%s\n",m_SRC.sCRCData);

	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930035; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	if( nType == 0x23 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(RET_OK));	//����
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL3, GetValue(m_SRC.nDealAmount));	//���������ܽ��

		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, m_SRC.sMachineID);			//�ն��豸ID
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL0, GetValue(m_SRC.nSettleInvoice));	//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_SSERIAL0, m_SRC.sSettleTime);			//������ֹʱ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(m_SRC.nBeginInvoice));	//��ʼ�ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, GetValue(m_SRC.nEndInvoice));	//�����ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL2, GetValue(m_SRC.nDealCount));		//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(m_SRC.nCancelCount));	//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, GetValue(m_SRC.nCancelAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(m_SRC.nExcepCount));	//�쳣�����ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(m_SRC.nExcepACount));	//�쳣�����ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(m_SRC.nOtherCount));	//������¼�ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(m_SRC.nOuterkeeper));	//���ʱ�־
	//	SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, GetValue(ucRawData[35]));			//���ױ��
	}
	else
	{
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(m_SRC.nDealAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, m_SRC.sMachineID);			//�ն��豸ID
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL0, GetValue(m_SRC.nSettleInvoice));	//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_SSERIAL0, m_SRC.sSettleTime);			//������ֹʱ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, GetValue(m_SRC.nBeginInvoice));	//��ʼ�ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL2, GetValue(m_SRC.nEndInvoice));	//�����ն˽�����ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL3, GetValue(m_SRC.nDealCount));		//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(m_SRC.nCancelCount));	//���������ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, GetValue(m_SRC.nCancelAmount));	//���������ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(m_SRC.nExcepCount));	//�쳣�����ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(m_SRC.nExcepACount));	//�쳣�����ܽ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(m_SRC.nOtherCount));	//������¼�ܱ���
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(m_SRC.nOuterkeeper));	//���ʱ�־
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, GetValue(ucRawData[35]));			//���ױ��
	}

	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, "0");						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, "0");					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, m_SRC.sCRCData);				//CRC

	return RET_OK;
#endif
}

//----------------------------------------------------------------------------
//
//  Function:   ConvertAssisData
//
//  Synopsis:   ��Ӳ��������ת��Ϊ��������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertAssisData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{

	if( ++(pDoc->m_wStateNo) > 65535 )	pDoc->m_wStateNo=0 ;

	pDoc->m_nDealCount++;
	pDoc->m_nInMoney  -= 1 ;
	pDoc->m_nOutMoney  = pDoc->m_nInMoney+1;


	TSBZTable  table;
	memset(&table, 0x00, sizeof(table));

	printf("============��������=====================================\n");

	sprintf(table.sAuthData,"%.2X%.2X%.2X%.2X",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
	printf("ע���:%s", table.sAuthData);

	sprintf(table.sCommVer, "%d",ucRawData[4]);
	printf("ͨ�Ű汾:%s\n", table.sCommVer);

	sprintf(table.sCommStart, "%d",ucRawData[5]);
	printf("����ԭ��:%s\n", table.sCommStart);

	sprintf(table.sMachineCode, "%.2X%.2X",ucRawData[6],ucRawData[7]);
	printf("���ʹ���:%s\n", table.sMachineCode);

	table.nInvoiceNo = ucRawData[8]*256+ucRawData[9];
	printf("������ˮ��:%d\n",table.nInvoiceNo);

	sprintf(table.sDealDateTime, "%02d%02d%02d %02d%02d%02d",ucRawData[10],ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15]);
	printf("����ʱ��:%s\n", table.sDealDateTime);

	sprintf(table.sUseCard, "%.2X",ucRawData[16]);
	printf("���ʹ���:%s\n",table.sUseCard);

	table.nICCardCode = ucRawData[17];
	printf("����:%d\n", table.nICCardCode);

	sprintf(table.sShowCardNo, "%.2X%.2X%.2X%.2X%.2X",ucRawData[18],ucRawData[19],ucRawData[20],ucRawData[21],ucRawData[22]);
	printf("��ʾ����:%s\n", table.sShowCardNo);

	table.nCardID = ucRawData[23]*256*256+ucRawData[24]*256+ucRawData[25];
	printf("���׿���:%d\n",table.nCardID);

	table.nTimes = ucRawData[26]*256+ucRawData[27];
	printf("��Ƭʹ����ˮ:%d\n", table.nTimes);

	sprintf(table.sWalletCode, "%d",ucRawData[28] & 0x0F);
	printf("Ǯ�����Դ���:%s\n", table.sWalletCode);

	int flag = ucRawData[28] & 0xF0;

	table.nInMoney = ucRawData[29]+ucRawData[30]*256;
	printf("���׽��:%d\n", table.nInMoney);
	table.nOutMoney = ucRawData[31]+ucRawData[32]*256+ucRawData[33]*65536;
	printf("Ǯ�����:%d\n", table.nOutMoney);

	if( !flag )
	{
		table.nInMoney = table.nInMoney + table.nOutMoney;
	}
	else
	{
		table.nInMoney = table.nOutMoney - table.nInMoney;
	}

	printf("�������:%d\n",table.nInMoney);

	table.nBatch = ucRawData[34]*256+ucRawData[35];
	printf("�������κ�:%d\n", table.nBatch);

	sprintf(table.sDealCode1, "%d",ucRawData[36]);
	printf("���ױ��:%s\n",table.sDealCode1);

	sprintf(table.sCRCData,"%.2X%.2X",ucRawData[37],ucRawData[38]);
	printf("CRC:%s\n",table.sCRCData);

	//У��CRC
	BYTE crc[3];
	memset(crc, 0x00, sizeof crc );
	calc_crc16(37,ucRawData,crc);
	if( (crc[0] != ucRawData[36]) || (crc[1] != ucRawData[37]) )
	{
		return RET_DATACRC_ERROR;
	}
	
	memset(pPacket, 0, sizeof(ST_CPACK));
	pPacket->head.RequestType = 930033; 
	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode  = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	CString strTime = table.sDealDateTime;
	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, table.sAuthData);			//�ն��豸ID
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(table.nInvoiceNo));	//������ˮ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(table.nCardID));	//���׿���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL6, table.sWalletCode);			//Ǯ����
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE, strTime.Left(6).GetBuffer(0));		//��������
	SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, strTime.Right(6).GetBuffer(0));		//����ʱ��
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL7, GetValue(table.nTimes));								//�ۼ�ʹ�ô���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL8, GetValue(table.nOutMoney-table.nInMoney));			//�������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL9, GetValue(table.nInMoney));							//�뿨���
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL10, GetValue(table.nOutMoney));							//�������
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL11, GetValue(table.nBatch));							//���κ�
	SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, table.sDealCode1);						//���ױ��
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, table.sCommVer);						//ͨ�Ű汾
	SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, table.sCommStart);					//����ԭ��
	SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, table.sCRCData);				//CRC

	if( nType == 0x24 )
	{
		pPacket->head.RequestType = 930098; 
		SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
		SetValue(&pPacket->head,&pPacket->pack, F_VSMESS, "�����ɹ�");	//��������Ϣ
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");	//����
	}

	return RET_OK;
}

//----------------------------------------------------------------------------
//
//  Function:   ConvertGSJData
//
//  Synopsis:   ��Ӳ��������ת��Ϊ��ʧ������
//
//  Arguments:  pPacket   -- ���ؽ��˴��
//				ucRawData -- ���ϵ�����
//				nDataLen  -- ���ϵ����ݳ���
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
long CInterfaceApp::ConvertGSJData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen)
{
	TSGSJRecord *pRecord = (TSGSJRecord*)ucRawData;
	

	

	memset(pPacket, 0, sizeof(ST_CPACK));

	pPacket->head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	pPacket->head.nextflag = 0;    /* �Ƿ����������*/
	pPacket->head.recCount = 1;    /* �����ļ�¼��*/
	pPacket->head.retCode = 0;     /* ���ش���*/
	pPacket->head.userdata = 0;

	SetValue(&pPacket->head,&pPacket->pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&pPacket->head,&pPacket->pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&pPacket->head,&pPacket->pack, F_SDATE1, pDoc->m_szDeviceID);		//�ն��豸ID

	if( nType == 0x81 )
	{
		WriteLog("�����ʧ");
		WriteLog("����%s",pRecord->szShowID);
		WriteLog("����%s",pRecord->szPassword);
		
		pPacket->head.RequestType = 930040; 
		SetValue(&pPacket->head,&pPacket->pack, F_SSTATION0, pRecord->szShowID);			//ѧ����
		SetValue(&pPacket->head,&pPacket->pack, F_SSTOCK_CODE, pRecord->szPassword);		//������
		SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, pRecord->szCRC);				//CRC
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(pRecord->nCardID));					//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, pRecord->szSerial);		//ͨ�Ű汾��
	}
	else if( nType == 0x82 )
	{
		pPacket->head.RequestType = 930041; 
		SetValue(&pPacket->head,&pPacket->pack, F_SSTATION0, pRecord->szShowID);			//ѧ����
		SetValue(&pPacket->head,&pPacket->pack, F_SSTOCK_CODE, pRecord->szPassword);		//������
		SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, pRecord->szCRC);				//CRC
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, GetValue(pRecord->nCardID));					//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, pRecord->szSerial);		//ͨ�Ű汾��
	}
	else 
	{
		WriteLog("�޸�����----------");
		WriteLog("��ʾ����%s",pRecord->szShowID);
		WriteLog("���׿���%d",pRecord->nCardID); 
		WriteLog("����%s",pRecord->szPassword);
		pPacket->head.RequestType = 930045; 

		SetValue(&pPacket->head,&pPacket->pack, F_SSTOCK_CODE2, pRecord->szPassword);
		SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE, "00");			//ͨ�Ű汾
		SetValue(&pPacket->head,&pPacket->pack, F_LBANK_ACC_TYPE2, "00");			//����ԭ��
		SetValue(&pPacket->head,&pPacket->pack, F_SBANK_CODE2, pRecord->szCRC);		//CRC
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL12, "153");					//���ױ��

		SetValue(&pPacket->head,&pPacket->pack, F_LVOL4, "0");							//������ˮ��
		SetValue(&pPacket->head,&pPacket->pack, F_LVOL5, GetValue(pRecord->nCardID));	//���׿���
		SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE, "");						//��������
		SetValue(&pPacket->head,&pPacket->pack, F_SPOST_CODE2, "");						//����ʱ��
		SetValue(&pPacket->head,&pPacket->pack, F_SSTATION0, pRecord->szShowID);		//��ʾ����
	}

	return RET_OK;
}

//��long��תΪ�ַ���, �����ڶ��̻߳���
char* GetValue(long iValue)
{
	static CLock lock;
	static char strString[64];

	lock.Lock();
	sprintf(strString,"%d", iValue);
	lock.Unlock();

	return strString;
}

//����CPacket����ֵ, Դ�ļ������ڽ��˴��ṩ��DEMO
void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data)
{
	long lv;
	double dv;
#define PC(a)	{ SetParmBit(head,ids);strncpy((char *)pack->a,data,sizeof(pack->a));pack->a[sizeof(pack->a)-1]=0;}//CHAR[]
#define PI(a)	{ SetParmBit(head,ids);lv=atol(data);memcpy(&pack->a,&lv,sizeof(pack->a));}//INT
#define PD(a)	{ SetParmBit(head,ids);dv=atof(data);memcpy(&pack->a,&dv,sizeof(pack->a));}//LONG

	switch(ids)
	{                                
	case F_SCUST_NO:                     
		PC(scust_no);                
		break;                       
	case F_SCUST_NO2:                    
		PC(scust_no2);               
		break;                       
	case F_SHOLDER_AC_NO:                
		PC(sholder_ac_no);           
		break;                       
	case F_SHOLDER_AC_NO2:               
		PC(sholder_ac_no2);          
		break;                       
	case F_SHOLDER_TYPE:                 
		PC(sholder_type);            
		break;                       
	case F_SHOLDER_TYPE2:                
		PC(sholder_type2);           
		break;                       
	case F_SNAME:                        
		PC(sname);                   
		break;                       
	case F_SNAME2:                       
		PC(sname2);                  
		break;                       
	case F_SALL_NAME:                    
		PC(sall_name);               
		break;                       
	case F_SMARKET_CODE:                 
		PC(smarket_code);            
		break;                       
	case F_SMARKET_CODE2:                
		PC(smarket_code2);           
		break;                       
	case F_SDATE0:                       
		PC(sdate0);                  
		break;                       
	case F_SDATE1:                       
		PC(sdate1);                  
		break;                       
	case F_SDATE2:                       
		PC(sdate2);                  
		break;                       
	case F_SDATE3:                       
		PC(sdate3);                  
		break;                       
	case F_STIME0:                       
		PC(stime0);                  
		break;                       
	case F_STIME1:                       
		PC(stime1);                  
		break;                       
	case F_STIME2:                       
		PC(stime2);                  
		break;                       
	case F_STIME3:                       
		PC(stime3);                  
		break;                       
	case F_LVOL0:                        
		PI(lvol0);                   
		break;                       
	case F_LVOL1:                        
		PI(lvol1);                   
		break;                       
	case F_LVOL2:                        
		PI(lvol2);                   
		break;                       
	case F_LVOL3:                        
		PI(lvol3);                   
		break;                       
	case F_LVOL4:                        
		PI(lvol4);                   
		break;                       
	case F_LVOL5:                        
		PI(lvol5);                   
		break;                       
	case F_LVOL6:                        
		PI(lvol6);                   
		break;                       
	case F_LVOL7:                        
		PI(lvol7);                   
		break;                       
	case F_LVOL8:                        
		PI(lvol8);                   
		break;                       
	case F_LVOL9:                        
		PI(lvol9);                   
		break;                       
	case F_LVOL10:                       
		PI(lvol10);                  
		break;                       
	case F_LVOL11:                       
		PI(lvol11);                  
		break;                       
	case F_LVOL12:                       
		PI(lvol12);                  
		break;                       
	case F_DAMT0:                        
		PD(damt0);                   
		break;                       
	case F_DAMT1:                        
		PD(damt1);                   
		break;                       
	case F_DAMT2:                        
		PD(damt2);                   
		break;                       
	case F_DAMT3:                        
		PD(damt3);                   
		break;                       
	case F_DAMT4:                        
		PD(damt4);                   
		break;                       
	case F_DAMT5:                        
		PD(damt5);                   
		break;                       
	case F_DAMT6:                        
		PD(damt6);                   
		break;                       
	case F_DAMT7:                        
		PD(damt7);                   
		break;                       
	case F_DAMT8:                        
		PD(damt8);                   
		break;                       
	case F_DAMT9:                        
		PD(damt9);                   
		break;                       
	case F_DAMT10:                       
		PD(damt10);                  
		break;                       
	case F_DAMT11:                       
		PD(damt11);                  
		break;                       
	case F_DAMT12:                       
		PD(damt12);                  
		break;                       
	case F_DAMT13:                       
		PD(damt13);                  
		break;                       
	case F_DAMT14:                       
		PD(damt14);                  
		break;                       
	case F_DAMT15:                       
		PD(damt15);                  
		break;                       
	case F_DAMT16:                       
		PD(damt16);                  
		break;                       
	case F_DAMT17:                       
		PD(damt17);                  
		break;                       
	case F_DAMT18:                       
		PD(damt18);                  
		break;                       
	case F_DAMT19:                       
		PD(damt19);                  
		break;                       
	case F_DAMT20:                       
		PD(damt20);                  
		break;                       
	case F_DAMT21:                       
		PD(damt21);                  
		break;                       
	case F_DAMT22:                       
		PD(damt22);                  
		break;                       
	case F_DAMT23:                       
		PD(damt23);                  
		break;                       
	case F_DAMT24:                       
		PD(damt24);                  
		break;                       
	case F_DAMT25:                       
		PD(damt25);                  
		break;                       
	case F_DAMT26:                       
		PD(damt26);                  
		break;                       
	case F_DAMT27:                       
		PD(damt27);                  
		break;                       
	case F_DAMT28:                       
		PD(damt28);                  
		break;                       
	case F_DAMT29:                       
		PD(damt29);                  
		break;                       
	case F_DAMT30:                       
		PD(damt30);                  
		break;                       
	case F_DAMT31:                       
		PD(damt31);                  
		break;                       
	case F_DAMT32:                       
		PD(damt32);                  
		break;                       
	case F_DAMT33:                       
		PD(damt33);                  
		break;                       
	case F_SSTOCK_CODE:                  
		PC(sstock_code);             
		break;                       
	case F_SSTOCK_CODE2:                 
		PC(sstock_code2);            
		break;                       
	case F_SCUST_TYPE:                   
		PC(scust_type);              
		break;                       
	case F_SCUST_TYPE2:                  
		PC(scust_type2);             
		break;                       
	case F_SSTAT_TYPE:                   
		PC(sstat_type);              
		break;                       
	case F_SSTAT_TYPE2:                  
		PC(sstat_type2);             
		break;                       
	case F_SROOM_NO:                     
		PC(sroom_no);                
		break;                       
	case F_SROOM_NO2:                    
		PC(sroom_no2);               
		break;                       
	case F_SOPEN_EMP:                    
		PC(sopen_emp);               
		break;                       
	case F_SCLOSE_EMP:                   
		PC(sclose_emp);              
		break;                       
	case F_SCHANGE_EMP:                  
		PC(schange_emp);             
		break;                       
	case F_SCHECK_EMP:                   
		PC(scheck_emp);              
		break;                       
	case F_SEMP:                         
		PC(semp);                    
		break;                       
	case F_SNATION_CODE:                 
		PC(snation_code);            
		break;                       
	case F_LCERT_CODE:                   
		PI(lcert_code);              
		break;                       
	case F_STX_PWD:                      
		PC(stx_pwd);                 
		break;                       
	case F_STX_PWD2:                     
		PC(stx_pwd2);                
		break;                       
	case F_SWITHDRAW_PWD:                
		PC(swithdraw_pwd);           
		break;                       
	case F_SWITHDRAW_PWD2:               
		PC(swithdraw_pwd2);          
		break;                       
	case F_SEMP_PWD:                     
		PC(semp_pwd);                
		break;                       
	case F_SEMP_PWD2:                    
		PC(semp_pwd2);               
		break;                       
	case F_SBANK_PWD:                    
		PC(sbank_pwd);               
		break;                       
	case F_SBANK_PWD2:                   
		PC(sbank_pwd2);              
		break;                       
	case F_SCUST_AUTH:                   
		PC(scust_auth);              
		break;                       
	case F_SCUST_AUTH2:                  
		PC(scust_auth2);             
		break;                       
	case F_SCUST_LIMIT:                  
		PC(scust_limit);             
		break;                       
	case F_SCUST_LIMIT2:                 
		PC(scust_limit2);            
		break;                       
	case F_LSAFE_LEVEL:                  
		PI(lsafe_level);             
		break;                       
	case F_LSAFE_LEVEL2:                 
		PI(lsafe_level2);            
		break;                       
	case F_SPOST_CODE:                   
		PC(spost_code);              
		break;                       
	case F_SPOST_CODE2:                  
		PC(spost_code2);             
		break;                       
	case F_SPHONE:                       
		PC(sphone);                  
		break;                       
	case F_SPHONE2:                      
		PC(sphone2);                 
		break;                       
	case F_SPHONE3:                      
		PC(sphone3);                 
		break;                       
	case F_SPAGER:                       
		PC(spager);                  
		break;                       
	case F_SEMAIL:                       
		PC(semail);                  
		break;                       
	case F_SEMAIL2:                      
		PC(semail2);                 
		break;                       
	case F_SNOTE:                        
		PC(snote);                   
		break;                       
	case F_SNOTE2:                       
		PC(snote2);                  
		break;                       
	case F_SCERT_NO:                     
		PC(scert_no);                
		break;                       
	case F_SCERT_NO2:                    
		PC(scert_no2);               
		break;                       
	case F_SCERT_ADDR:                   
		PC(scert_addr);              
		break;                       
	case F_SSTATUS0:                     
		PC(sstatus0);                
		break;                       
	case F_SSTATUS1:                     
		PC(sstatus1);                
		break;                       
	case F_SSTATUS2:                     
		PC(sstatus2);                
		break;                       
	case F_SSTATUS3:                     
		PC(sstatus3);                
		break;                       
	case F_SSTATUS4:                     
		PC(sstatus4);                
		break;                       
	case F_LWITHDRAW_FLAG:               
		PI(lwithdraw_flag);          
		break;                       
	case F_SADDR:                        
		PC(saddr);                   
		break;                       
	case F_SADDR2:                       
		PC(saddr2);                  
		break;                       
	case F_SSERIAL0:                     
		PC(sserial0);                
		break;                       
	case F_SSERIAL1:                     
		PC(sserial1);                
		break;                       
	case F_SSERIAL2:                     
		PC(sserial2);                
		break;                       
	case F_SSERIAL3:                     
		PC(sserial3);                
		break;                       
	case F_SSERIAL4:                     
		PC(sserial4);                
		break;                       
	case F_SCURRENCY_TYPE:               
		PC(scurrency_type);          
		break;                       
	case F_SCURRENCY_TYPE2:              
		PC(scurrency_type2);         
		break;                       
	case F_SBRANCH_CODE0:                
		PC(sbranch_code0);           
		break;                       
	case F_SBRANCH_CODE1:                
		PC(sbranch_code1);           
		break;                       
	case F_SBRANCH_CODE2:                
		PC(sbranch_code2);           
		break;                       
	case F_USSET0:                       
		PC(usset0);                  
		break;                       
	case F_USSET1:                       
		PC(usset1);                  
		break;                       
	case F_USSET2:                       
		PC(usset2);                  
		break;                       
	case F_USSET3:                       
		PC(usset3);                  
		break;                       
	case F_USSET4:                       
		PC(usset4);                  
		break;                       
	case F_USSET5:                       
		PC(usset5);                  
		break;                       
	case F_USSET6:                       
		PC(usset6);                  
		break;                       
	case F_SSTATION0:                    
		PC(sstation0);               
		break;                       
	case F_SSTATION1:                    
		PC(sstation1);               
		break;                       
	case F_SBANK_ACC:                    
		PC(sbank_acc);               
		break;                       
	case F_SBANK_ACC2:                   
		PC(sbank_acc2);              
		break;                       
	case F_LBANK_ACC_TYPE:               
		PI(lbank_acc_type);          
		break;                       
	case F_LBANK_ACC_TYPE2:              
		PI(lbank_acc_type2);         
		break;                       
	case F_SMAIN_FLAG:                   
		PC(smain_flag);              
		break;                       
	case F_SMAIN_FLAG2:                  
		PC(smain_flag2);             
		break;                       
	case F_SBANK_CODE:                   
		PC(sbank_code);              
		break;                       
	case F_SBANK_CODE2:                  
		PC(sbank_code2);             
		break;                       
	case F_SEMP_NO:                      
		PC(semp_no);                 
		break;                       
	case F_SEMP_NO2:                     
		PC(semp_no2);                
		break;                       
	case F_DRATE0:                       
		PD(drate0);                  
		break;                       
	case F_DRATE1:                       
		PD(drate1);                  
		break;                       
	case F_LSERIAL0:                     
		PI(lserial0);                
		break;                       
	case F_LSERIAL1:                     
		PI(lserial1);                
		break;                       
	case F_SBANKNAME:                    
		PC(sbankname);               
		break;                       
	case F_SBANKNAME2:                   
		PC(sbankname2);              
		break;                       
	case F_SCARD0:                       
		PC(scard0);                  
		break;                       
	case F_SCARD1:                       
		PC(scard1);                  
		break;                       
	case F_SORDER0:                      
		PC(sorder0);                 
		break;                       
	case F_SORDER1:                      
		PC(sorder1);                 
		break;                       
	case F_SORDER2:                      
		PC(sorder2);                 
		break;                       
	case F_VSMESS:                       
		PC(vsmess);                  
		break;       
	case F_SCUSTTYPES:
		PC(scusttypes);
		break;
	case F_SSECTYPES:
		PC(ssectypes);
		break;
	case F_VSVARSTR0:                    
		PC(vsvarstr0);               
		break;                       
	case F_VSVARSTR1:                    
		PC(vsvarstr1);               
		break;                       
	case F_VSVARSTR2:                    
		PC(vsvarstr2);               
		break;                       
	case F_VSVARSTR3:                    
		PC(vsvarstr3);               
		break;                       
	default:
		printf("not existed parameter=%d....\n",ids);
		break;
	}                                
}  

//�Ƿ�Ϊ�Ƿ�������ʱ��(�����ж�)
bool IsValidDateTime(unsigned char *pDateTime)
{
	if( pDateTime[0] > 100 || 
	   pDateTime[1] >= 13 || pDateTime[1] == 0 || 
	   pDateTime[2] > 31 || pDateTime[2] == 0 ||
	   pDateTime[3] > 24 || 
	   pDateTime[4] > 60 ||  
	   pDateTime[5] > 60 )
	{
		return false;
	}
	return true;
}

//�õ���ǰʱ��YYYY-MM-DD HH:MI24:SS
void GetCurDateTime(char *pszDateTime)
{
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);

	sprintf(pszDateTime, "%04d-%02d-%02d %02d:%02d:%02d", 
		SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
}

//�õ���ǰʱ��
void GetCurDateTimeEx(char *pszDateTime)
{
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);

	sprintf(pszDateTime, "%02d%02d%02d %02d%02d%02d", 
		SysTime.wYear-2000,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
}

//�õ�16���Ƶ���ֵ
long GetHexNumber(char cChar)
{
	if( cChar >= '0' && cChar <= '9' )
		return (cChar - '0');
	else if( cChar >= 'a' && cChar <= 'f' )
		return (cChar-'a') + 10 ;
	else if( cChar >= 'A' && cChar <= 'F' )
		return (cChar-'A') + 10 ;
	else
		return 0;
}

//��16���Ƶ���ֵת��һ��10���Ƶ�long
long ConvertID(char *pHexID)
{
	long nValue = 0 ;
	long len = strlen(pHexID);
	for(int i=0; i<len; i++)
	{
		nValue = nValue + (GetHexNumber(pHexID[i]) * (long)pow(16, len-i-1));
	}
	return nValue;
}

//���Դ�ӡ���(������printf)
void DebugPrint(const char *format, ...)
{
	TCHAR sBuffer[1024];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	printf("%s", sBuffer);
}

//д������־
void WriteTickLog(const char *format, ...)
{
	char  szFile[MAX_PATH];
	char  sBuffer[1024],szTemp[MAX_PATH];
	va_list ptr;
	SYSTEMTIME  SysTime;

	memset(szFile, 0x00, sizeof szFile);
	memset(sBuffer,0x00,sizeof sBuffer);
	memset(szTemp, 0x00,sizeof szTemp);
	
	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	
	sprintf(szFile, "%s\\������־.log", szTemp);

	FILE *fp = NULL ;
	if( (fp=fopen(szFile, "a+")) != NULL )
	{
		TCHAR  szLog[512];

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d:%04d %s", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond, SysTime.wMilliseconds, 
			sBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

//д��־(ÿ��һ����־�ļ�)
void WriteLog(const char *format, ...)
{
    TCHAR		szFile[MAX_PATH];
	TCHAR		sBuffer[1024],szTemp[MAX_PATH];
	va_list		ptr;
	SYSTEMTIME  SysTime;

	memset(szFile, 0x00, sizeof szFile);
	memset(sBuffer,0x00,sizeof sBuffer);
	memset(szTemp, 0x00,sizeof szTemp);
	
	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);
	
	if( strlen(sBuffer) < 128 )
		printf("%s", sBuffer);

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	sprintf(szFile, "%s\\�ӿ���־.log", szTemp);

	FILE *fp = NULL ;
	if( (fp=fopen(szFile, "a+")) != NULL )
	{
		TCHAR  szLog[512];

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d %s", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,sBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

//�˳�CWinApp
int CInterfaceApp::ExitInstance() 
{
	//ɾ���ڴ��б�����豸��Ϣ
	if( gpSmartDoc != NULL )
	{
		delete [] gpSmartDoc;
		gpSmartDoc = NULL ;
	}
	gnDocCount = 0 ;

	return CWinApp::ExitInstance();
}

//930021�����˴����ݰ�ת��Ϊ�豸��
bool CInterfaceApp::FillSmartDoc(ST_PACK *pPacket)
{
	TSSmartDoc  doc;
	
	ZeroMemory(&doc, sizeof(doc));

	printf("------�����豸ID=%s--------\n",pPacket->sdate0);
	printf("------�����豸����=%d------\n",pPacket->lvol4);
	printf("------���յ�ַ=%s----------\n",pPacket->sstation0);
	printf("------���ջ��ʹ���=%s------\n",pPacket->semp);
	printf("------�����豸ע���=%s-----\n",pPacket->sdate2);

	strcpy(doc.m_szMacCode, pPacket->semp);			//�ն˻��ͺŴ���
	strcpy(doc.m_szMacCard, pPacket->sholder_type);//����IC������
	strcpy(doc.m_szMacModle, pPacket->semp);		//�ն˻��ͺ�
	strcpy(doc.m_szMacType, pPacket->semp);			//��������
	strcpy(doc.m_szDeviceID, pPacket->sdate0);		//�豸ID
	strcpy(doc.m_szRegister, pPacket->sdate2);		//ע���
	doc.m_nAuthID=ConvertID(doc.m_szDeviceID);		//��Ȩ��
	doc.m_nMachineNo=pPacket->lvol4;				//����	
	strcpy(doc.m_szVersion, pPacket->sdate3);		//�豸�汾��
	strcpy(doc.m_szPassword, "000000");				//ϵͳԱ����
	strcpy(doc.m_szOprPasswd, "000000");			//����Ա����
	doc.m_nPwdswitch=-1;							//���뿪��

	if( strlen(pPacket->stime0) != 8 )
	{
		printf("�Ƿ����豸!\n");
		strcpy(doc.m_sClockVer, "");
	}
	else
		strcpy(doc.m_sClockVer, pPacket->stime0);

	strcpy(doc.m_szOrgid, "001");					//��������֯����
	doc.m_nPortCount=pPacket->lvol5;				//�������˿�����
	printf("------�������˿�����%d-----\n",pPacket->lvol5);
	doc.m_nSMTPort=pPacket->lvol6;				  //�������˿ں�
	printf("------�������˿ں�%d-----\n",pPacket->lvol6);
	strcpy(doc.m_szPort, pPacket->sbank_code);	  //ͨѶ�˿�
	printf("------ͨѶ�˿�%s-----\n",pPacket->sbank_code);
	doc.m_nBaudRate=pPacket->lvol9;			  //������
	doc.m_nCommMode=pPacket->lvol8;			  //��·ģʽ
	printf("------��·ģʽ%d-----\n",pPacket->lvol8);

	strcpy(doc.m_szAddr, pPacket->sstation0);    //ͨѶ��ַ
	doc.m_nStatus=pPacket->lvol7;                //�豸״̬, ���涨��Ϊ:
	printf("------�豸״̬%d-----\n",pPacket->lvol7);
	doc.m_nConnType = pPacket->lvol10;			  //ͨѶ��ʽ
	strcpy(doc.m_szClass, pPacket->snote2);	  //����				  //

	doc.m_wFlowNo=pPacket->lvol11+1;			  //������ˮ�� modified
	doc.m_wLastInvoiceNo=pPacket->lvol11;        //�ն˽�����ˮ����ĩֵ
	doc.m_wStateNo=pPacket->lvol12;
	doc.m_nFlow=1;									//���
	doc.m_nBeginInvoice=0;							//���ʵĿ�ʼ��ˮ
	doc.m_wSettleinvoice=0;							//������ˮ����ĩֵ
	doc.m_wEndInvoice=0;							//���ʵĽ�����ˮ��
	strcpy(doc.m_sBlackExpire, pPacket->sserial0);  //����������Ч��
	strcpy(doc.m_sDownBlackTime, pPacket->sserial1); //�������´�ʱ����ĩֵ
	doc.m_nStartuse=0;								 //ǩ�����

	if( !CheckSmartDocValid(&doc) )
	{
		printf("CheckSmartDocValid !!!!!\n");
		return false;
	}
	WriteLog("�ն˻��ͺŴ���=%s,����IC������=%s, �ն˻��ͺ�=%s, ��������=%s, "
		"�豸ID=%s, ע���=%s, ����=%d, �豸�汾��=%s, ϵͳԱ����=%s, ����Ա����=%s,"
		"���뿪��=%d, �������˿�����=%d, �������˿ں�=%d, ͨѶ�˿�=%s, ������=%d,"
		"��·ģʽ=%d,ͨѶ��ַ=%s, �豸״̬=%d, ������ˮ����ĩֵ=%d, ����������Ч��=%s, �������汾=%s, ͨѶ��ʽ=%d,����=%s, ���豸:%s\n",
		pPacket->semp, pPacket->sholder_type, pPacket->semp, pPacket->semp,
		pPacket->sdate0, pPacket->sdate2, pPacket->lvol4, pPacket->sdate3, "000000", "000000", 
		doc.m_nPwdswitch, pPacket->lvol5, pPacket->lvol6, pPacket->sbank_code, pPacket->lvol9, 
		pPacket->lvol8, pPacket->sstation0, pPacket->lvol7, pPacket->lvol11, pPacket->sserial0, pPacket->sserial1, 
		pPacket->lvol10, pPacket->snote2, pPacket->stime0);

	printf("�����豸(ID=%s, ע���:%s, ����=%d, ��������:%d..���豸:%s...\n", 
		doc.m_szDeviceID, doc.m_szRegister, 
		doc.m_nMachineNo, doc.m_nCommMode, pPacket->stime0);
//	ReadSmartDocList(TSSmartDoc *pSmartDoc,long *nRecount);
	nReload = 1;
	return true;
}

TSSmartDoc* CInterfaceApp::CheckDeviceID(char *pDeviceID)
{
	for(long i=0; i< gnDocCount; i++)
	{
		if( !strcmp(gpSmartDoc[i].m_szDeviceID, pDeviceID) )
			return &gpSmartDoc[i];
	}
	return NULL;
}

void CInterfaceApp::SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
		hex[i]=hex[i]<<4;
		hex[i]+=(((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10)&0x0f);
	}
}

void CInterfaceApp::SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count)
{
	int i;
	char ch;
	for(i=0;i<count;i++)
	{
		ch=(hex[i]&0xf0)>>4;
		dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
		ch=hex[i]&0x0f;
		dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
	}
}

bool CInterfaceApp::FillTask(char *pDeviceID, TSSmartTaskPlan *pTaskPlan, unsigned int nRequest, ST_PACK *pPacket)
{
	WriteLog("-------FillTask----------\n");

	TSSmartDoc *pDoc = CheckDeviceID(pDeviceID);

	if( pDoc == NULL)
	{
		char szText[256];
		sprintf(szText, "û�д��豸:%s!", pDeviceID);
		AnswerResultError(nRequest, pPacket->lvol1, -1, szText);
		WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.  .....û�д��豸!\n", pDeviceID, nRequest);
		printf("------�޴��豸------\n");
		return false;
	}

	long nAuthID = pDoc->m_nAuthID;

	WriteLog("���˴��´�����:  �豸%s, ���ܺ�:%d.\n", pDeviceID, nRequest);

	bool bResult = true;
	int i = pTaskPlan->nTask;

	sprintf(pTaskPlan->pTask[i].szSystemNO, "%d", pPacket->lvol1);
	pTaskPlan->pTask[i].nFunc = nRequest;

	switch(nRequest)
	{

	case 930020:
		if( strcmp(pDoc->m_szMacCode, "5301") )
		{
			AnswerResultError(pPacket->lvol2, pPacket->lvol1, -1, "ֻ��LPort�豸���д˹���!");
			return false;
		}
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"148");           
		pTaskPlan->pTask[i].nPriority = 9;
		m_SSystemParam.nParameter1 = pPacket->lvol4;	//��ˮ��	
		m_SSystemParam.nParameter4 = pPacket->lvol5;	//����
		m_SSystemParam.nParameter2 = pPacket->lvol6;	//��������
		m_SSystemParam.nParameter3 = pPacket->lvol7;	//�������
		m_SSystemParam.szParameter2[0]='0';
		m_SSystemParam.szParameter2[1]=pPacket->sstatus0[0];	//��������
		strcpy(m_SSystemParam.szParameter3, pPacket->scurrency_type);	//������־
		strcpy(m_SSystemParam.szParameter4, pPacket->sdate1);	//��ֹ����		
		pTaskPlan->pTask[i].pData = (char*)&m_SSystemParam;	
		pTaskPlan->nTask++;
		WriteLog("���˴��´�����(930020): �豸%s, ���ܺ�:%d...\n", pDoc->m_szDeviceID, nRequest);
		break;	

	case 930001: //�´��豸ʱ��
		if( strlen(pPacket->sserial0) == 12 )
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();           
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"101");           
			pTaskPlan->pTask[i].nPriority = 5;                      
			strcpy(pTaskPlan->pTask[i].szMemo, pPacket->sserial0);  
			pTaskPlan->nTask++;
			WriteLog("�´��豸ʱ��(%d). �ն��豸ID=%s.  ʱ��=%s.\n", nRequest, pDeviceID, pPacket->sserial0);
		}
		else
		{
			bResult = false;
			WriteLog("�´��豸ʱ��(%d). �ն��豸ID=%s.  ʱ��=%s......�������Ϸ�!\n", nRequest, pDeviceID, pPacket->sserial0);
			AnswerResultError(nRequest, pPacket->lvol1, -1, "�������Ϸ�!");
		}
		break;
	case 930002: //�ϴ��豸ʱ��
		{
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"03");           
		pTaskPlan->pTask[i].nPriority = 5;
		pTaskPlan->nTask++;
		WriteLog("�ϴ��豸ʱ��(%d). �ն��豸ID=%s.  \n", nRequest, pDeviceID);
		}
		break;
	case 930006: //�´����ѱ���
		{
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"120");           
		pTaskPlan->pTask[i].nPriority = 5;
		sprintf(pTaskPlan->pTask[i].szMemo, "%d %d", pPacket->lvol6, pPacket->lvol5);		
		WriteLog("�´����ѱ���(%d). �ն��豸ID=%s. [%d]  [%d]\n", nRequest, pDeviceID, pPacket->lvol6, pPacket->lvol5);
		TSAttachData *pHead = &m_SAttachData;
		pHead->nValue = pPacket->lvol5 ; //(������)
		pHead->nCount = pPacket->lvol6 ; //����
		pTaskPlan->pTask[i].pData = (char*)pHead;
		pTaskPlan->nTask++;
		}
		break;
	case 930007: //�´��豸������
		{
		if( atoi(pPacket->sbank_pwd) != 0x65 && 
			atoi(pPacket->sbank_pwd) != 0x64 && 
			atoi(pPacket->sbank_pwd) != 0x00 )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "�������Ϸ�!");
			return false;
		}

		if( strlen(pPacket->sbankname) < 4 )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "����������Ϸ�!");
			return false;
		}

		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"80");
		pTaskPlan->pTask[i].nPriority = 3;

		TSAttachData *pHead = &m_SAttachData;
		if( pHead == NULL )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "ǰ�òɼ�������ϵͳ����!");
			WriteLog("�´��豸������(%d). �ն��豸ID=%s. �ڴ治��, ���ܷ����µ�����!\n", nRequest, pDeviceID);
			return false;
		}

		TSResultData  *pData = new TSResultData;
		if( pData == NULL )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "ǰ�òɼ�������ϵͳ����!");
			WriteLog("�´��豸������(%d). �ն��豸ID=%s. �ڴ治��, ���ܷ����µ�����!\n", nRequest, pDeviceID);
//			delete pHead;
			return false;
		}

		ZeroMemory(pHead, sizeof(TSAttachData));
		ZeroMemory(pData, sizeof(TSResultData));

		pHead->pData = (void*)pData;
		pTaskPlan->pTask[0].pData = (char*)pHead;
		pHead->nCount = 1;

		strncpy(pData->sValue1, pPacket->sdate0, 8);		//�ն��豸ID
		pData->nValue1 = pPacket->lvol3;					//����
		strncpy(pData->sValue2, pPacket->sdate2, 8);			//ע���
		pData->nValue2 = pPacket->lvol5;			//lvol5  ������ 
		strcpy(pData->sValue3, pPacket->semp_pwd);	//sopen_emp ϵͳԱ���� 
		strcpy(pData->sValue4, pPacket->semp_pwd2);	//sclose_emp ����Ա����
		pData->nValue3 = pPacket->lvol6;					//lvol6 ���뿪��
		strcpy(pData->sValue5, pPacket->sbank_pwd);	//scurrency_type ��Ƭ�ṹ 
		pData->nValue4 = pPacket->lvol7;					//lvol7 �������ʹ�ô���
		pData->nValue5 = pPacket->lvol8;					//lvol8 Ǯ����ߴ���޶�
		pData->nValue6 = pPacket->lvol9;					//lvol9 Ǯ�����ʣ����޶�
		pData->nValue7 = pPacket->lvol10;					//lvol10 ��ֵ�շѷ�ʽʹ�õĶ�ֵ��
		strcpy(pData->sValue6, pPacket->sbranch_code0);	    //sbranch_code0 Ǯ������ 
		pData->nValue8 = pPacket->lvol11;					//lvol11 ÿ�ν�����߶�
		strncpy(pData->sValue7, pPacket->sbankname,64);		//sbankname �ն˻������û������
		strncpy(pData->sValue8, pPacket->scurrency_type2,2);  //scurrency_type2 �շѻ���ǿ���ܿ���
		pData->nValue9 = pPacket->lvol12;					  //lvol11 ÿ�ν�����߶�

		pTaskPlan->nTask++;

		WriteLog("�´��豸������(%d). �ն��豸ID=%s\n", nRequest, pPacket->sdate0);
		WriteLog("����=%d\n", pPacket->lvol3);
		WriteLog("ע���=%s\n", pPacket->sdate2);
		WriteLog("������=%d\n", pPacket->lvol5);
		WriteLog("ϵͳԱ����=%s\n", pPacket->semp_pwd);
		WriteLog("����Ա����=%s\n", pPacket->semp_pwd2);
		WriteLog("���뿪��=%d\n", pPacket->lvol6);
		WriteLog("��Ƭ�ṹ=%s\n", pPacket->sbank_pwd);
		WriteLog("�������ʹ�ô���=%d\n", pPacket->lvol7);
		WriteLog("Ǯ����ߴ���޶�=%d\n", pPacket->lvol8);
		WriteLog("Ǯ�����ʣ����޶�=%d\n", pPacket->lvol9);
		WriteLog("��ֵ�շѷ�ʽʹ�õĶ�ֵ��=%d\n", pPacket->lvol10);
		WriteLog("Ǯ������=%s\n", pPacket->sbranch_code0);
		WriteLog("ÿ�ν�����߶�=%d\n", pPacket->lvol11);
		WriteLog("�ն˻������û������=%s\n", pPacket->sbankname);
		WriteLog("�շѻ���ǿ���ܿ���=%s\n", pPacket->scurrency_type2);
		WriteLog("�շѷ�ʽ=%d\n\n", pPacket->lvol12);
		}
		break;
	case 930008: //�ϴ��豸������
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"81");           
		pTaskPlan->pTask[i].nPriority = 4;
		pTaskPlan->nTask++;
		WriteLog("�ϴ��豸������(%d). �ն��豸ID=%s \n", nRequest, pDeviceID);
		break;
	case 930009: //���ò�������
		if( strcmp(pDoc->m_szMacCode, "5301") )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "ֻ��LPort�豸���д˹���!");
			bResult = false ;
		}
		else
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"62");           
			pTaskPlan->pTask[i].nPriority = 5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
			pTaskPlan->nTask++;
			WriteLog("���ò�������(%d). �ն��豸ID=%s. [%d]\n", nRequest, pDeviceID, pPacket->lvol4);
		}
		break;
	case 930010: //�´���������޶�
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"102");           
		pTaskPlan->pTask[i].nPriority = 5;
		sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
		pTaskPlan->nTask++;
		WriteLog("�´���������޶�(%d). �ն��豸ID=%s. [%d]\n", nRequest, pDeviceID, pPacket->lvol4);
		break;
	case 930011: //�������ѱ�ż��汾
		break;
	case 930012: //�������ѿ�ݱ��
		break;
	case 930013: //��������ʱ��β���
		break;
	case 930014: //����״̬����\����״̬����\ȡ����������ָ�����
		{
		WriteLog("����״̬����...(%d). �ն��豸ID=%s. [%d]\n", 
			nRequest, pDeviceID, pPacket->lvol4);
		if( pPacket->lvol4 == 0 )
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"110");           
			pTaskPlan->pTask[i].nPriority = 8;
			pTaskPlan->nTask++;
		}
		else if( pPacket->lvol4 == 1 )
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"111");           
			pTaskPlan->pTask[i].nPriority = 9;
			pTaskPlan->nTask++;
		}
		else if( pPacket->lvol4 == 2 )
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"112");           
			pTaskPlan->pTask[i].nPriority = 4;
			pTaskPlan->nTask++;
		}
		else
		{
			printf("���ܺ�%d�Ĳ������Ϸ�!\n", 930014);
			AnswerResultError(nRequest, pPacket->lvol1, -1, "�������Ϸ�!");
			bResult = false ;
		}
		}
		break;
	case 930015: //�豸����
		break;
	case 930017: //�ɼ�����������ˮ����ʷ��
	case 930016: //�ɼ�������ˮ����ʷ��
	case 930018: //�ɼ��ֽ��ֵ��ˮ����ʷ��
	case 930022: //�ɼ��ֽ��ֵ�������ˮ����ʷ��
		if( nRequest == 930017 )	//�ɼ�����������ˮ����ʷ��
		{
			if( strcmp(pDoc->m_szMacCode, "5301") )
			{
				AnswerResultError(nRequest, pPacket->lvol1, -1, "ֻ��LPort�豸���д˹���!");
				bResult = false ;
				return bResult;
			}
		}
		else
		{
			if( !strcmp(pDoc->m_szMacCode, "5301") )
			{
				AnswerResultError(nRequest, pPacket->lvol1, -1, "LPort�豸�޴˹���!");
				bResult = false ;
				return bResult;
			}
		}
		pTaskPlan->nRepeatTimes = 0 ;
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"09");           
		pTaskPlan->pTask[i].nPriority = 6;
		sprintf(pTaskPlan->pTask[i].szMemo, "%d:%d", pPacket->lvol5, pPacket->lvol6);
		pTaskPlan->nTask++;
		WriteLog("�ɼ���ˮ����ʷ��...(%d). �ն��豸ID=%s. [%d--%d]....MSGID=%d..FUNCTION=%d.....\n", nRequest, pDeviceID, pPacket->lvol5, pPacket->lvol6, pPacket->lvol1, pPacket->lvol4);
		break;
	case 930019: //�ɼ��豸������ˮ����ʷ��
		pTaskPlan->nRepeatTimes = 1 ;
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"16");           
		pTaskPlan->pTask[i].nPriority = 6;
		sprintf(pTaskPlan->pTask[i].szMemo, "%d:%d", pPacket->lvol5, pPacket->lvol6);
		pTaskPlan->nTask++;
		WriteLog("�ɼ��豸������ˮ����ʷ��...(%d). �ն��豸ID=%s. [%d--%d]\n", nRequest, pDeviceID, pPacket->lvol5, pPacket->lvol6);
		break;
	case 930038: //�޸��豸ע���
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"38");           
		pTaskPlan->pTask[i].nPriority = 6;
		sprintf(pTaskPlan->pTask[i].szMemo, "%s", pPacket->sdate2);
		pTaskPlan->nTask++;
		WriteLog("�޸��豸ע���...(%d). �ն��豸ID=%s. [%s]\n", nRequest, pDeviceID, pPacket->sdate2);
		break;
	case 930056: //�´��豸��ز���
		gTick = pPacket->lvol4*1000;
		WriteLog("�´��豸�������:%d\n", gTick/1000);
		printf("�´��豸�������:%d\n", gTick/1000);
		bResult = false ;
		break;
	case 930060: //�豸ǩ��ǩ��
		if( !strcmp(pDoc->m_szMacCode, "5301") )
		{
			AnswerResultError(nRequest, pPacket->lvol1, -1, "LPort�豸����ǩ��ǩ��!");
			bResult = false ;
		}
		else
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"130");           
			pTaskPlan->pTask[i].nPriority = 3;//5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
			pTaskPlan->nTask++;
			WriteLog("�豸ǩ��ǩ��(%d). �ն��豸ID=%s. [%d]\n", nRequest, pDeviceID, pPacket->lvol4);
		}
		break;
	case 930061://����ÿ��������ѽ��
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"131");           
			pTaskPlan->pTask[i].nPriority = 5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
			pTaskPlan->nTask++;
			WriteLog("����ÿ���ۼ������޶�(%d). �ն��豸ID=%s. ���=[%d]\n", nRequest, pDeviceID, pPacket->lvol4);
			break;
	case 930062://1.24.	��ʼ��LPORT�˿ڲ���
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"132");           
			pTaskPlan->pTask[i].nPriority = 5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
			pTaskPlan->nTask++;
			WriteLog("��ʼ��LPORT�˿ڲ���(%d). �ն��豸ID=%s. �˿ں�=[%d]\n", nRequest, pDeviceID, pPacket->lvol4);
			break;
	case 930063://1.25.	�����ն˹���Ա����
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"133");           
			pTaskPlan->pTask[i].nPriority = 5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%s", pPacket->semp_pwd);
			pTaskPlan->nTask++;
			WriteLog("�����ն˹���Ա����(%d). �ն��豸ID=%s. ����=[%s]\n", nRequest, pDeviceID, pPacket->semp_pwd);
			break;
	case 930064://��ȡlportָ���˿ڵ��豸����
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"134");           
			pTaskPlan->pTask[i].nPriority = 5;
			sprintf(pTaskPlan->pTask[i].szMemo, "%d", pPacket->lvol4);
			pTaskPlan->nTask++;
			WriteLog("��ȡlportָ���˿ڵ��豸����(%d). �ն��豸ID=%s. �˿ں�=[%d]\n", nRequest, pDeviceID, pPacket->lvol4);

		break;
	case 930099: //�豸�������
		//gTick = pPacket->lvol4;
		printf("-------�豸�������\n");
		bResult = false ;
		break;
	case 930117: //��ʱ���´�/ɾ��������
		{
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"136");           
		pTaskPlan->pTask[i].nPriority = 5;

		TSAttachData *pHead = &m_SAttachData;
		pHead->nValue = pPacket->lvol5 ; //��־		
		sprintf(pHead->szValue,"%ld",pPacket->lvol3); //����
		pTaskPlan->pTask[i].pData = (char*)pHead;
		pTaskPlan->nTask++;
		WriteLog("��ʱ���´�/ɾ��������(%d). �汾=%s. ����=%s\n", nRequest,pTaskPlan->pTask[i].szMemo , pHead->szValue);
		}
		break;
	case 930121: //��ʱ���´�/ɾ�����������汾
		{
			pTaskPlan->pTask[i].nTaskID = GetTickCount();
			pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
			pTaskPlan->pTask[i].nAuthID = nAuthID;                  
			strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
			strcpy(pTaskPlan->pTask[i].szTaskCode,"72");           
			pTaskPlan->pTask[i].nPriority = 5;
			
			TSAttachData *pHead = &m_SAttachData;
			pHead->nValue = pPacket->lvol5 ; //��־		
			sprintf(pHead->szValue,"%ld",pPacket->lvol3); //����
			memcpy(&pHead->szValue[50],pPacket->sserial0,12);
			pTaskPlan->pTask[i].pData = (char*)pHead;
			pTaskPlan->nTask++;
			WriteLog("��ʱ���´�/ɾ��������(%d). �汾=%s. ����=%s\n", nRequest,pPacket->sserial0 , pHead->szValue);
		}
		break;		
	case 930201: //�´���ʱ�������°���������
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"73");           
		pTaskPlan->pTask[i].nPriority = 8;
		strcpy(pTaskPlan->pTask[i].szMemo, pDeviceID); 		
		pTaskPlan->nTask++;
		WriteLog("�´���ʱ�������°���������%ld\n", nRequest);
		break;		
	case 930114: //�ϴ���ʱ���汾
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"137");           
		pTaskPlan->pTask[i].nPriority = 5;
		pTaskPlan->nTask++;
		WriteLog("�ϴ���ʱ���汾\n", nRequest);
		break;
	case 930113: //�´���ʱ���汾
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"138");           
		pTaskPlan->pTask[i].nPriority = 5;
		strcpy(pTaskPlan->pTask[i].szMemo,pPacket->sserial0);
		pTaskPlan->nTask++;
		WriteLog("�´���ʱ���汾\n", nRequest);
		break;

	case 930110://�ϴ���ʱ���ڼ���
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"139");           
		pTaskPlan->pTask[i].nPriority = 5;
		pTaskPlan->nTask++;
		WriteLog("�ϴ���ʱ���ڼ���");
		break;

	case 930109: //�´���ʱ���ڼ���
		{
		BYTE buffer[100],buf[10];
		int count=0,m_int=0;

		memset(buffer, 0x00, sizeof buffer );
		memset(buf,    0x00, sizeof buf );

		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"140");           
		pTaskPlan->pTask[i].nPriority = 5;
		TSAttachData *pHead = &m_SAttachData;		
		pHead->nCount = pPacket->lvol5 ; //����
		count = 4*pHead->nCount;
		memcpy(buffer,pPacket->vsvarstr0,count);
		count = pHead->nCount*2;		
		for(int kk=0; kk<count; kk++)
		{
			memset(buf,    0x00, sizeof buf );
			memcpy(buf,buffer+2*kk,2);
			m_int=atol((char*)buf);
			pHead->szValue[kk]=m_int;
		}
		pTaskPlan->pTask[i].pData = (char*)pHead;
		pTaskPlan->nTask++;
		WriteLog("�´���ʱ���ڼ���(%d).����=%ld,value=%s\n", nRequest,pHead->nCount , buffer);
		}
		break;
	case 930106:  //�ϴ���ʱ��ʱ���	
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"141");           
		pTaskPlan->pTask[i].nPriority = 5;
		//����
		sprintf(pTaskPlan->pTask[i].szMemo,"%ld",pPacket->lvol3);
		pTaskPlan->nTask++;
		WriteLog("�ϴ���ʱ��ʱ���(%d). ����=%s\n", nRequest,pTaskPlan->pTask[i].szMemo );
		break;
	case 930105: //�´���ʱ��ʱ���
		{
		char buf[80];
		int	 start_h=0,start_m=0,end_h=0,end_m=0;
		memset(buf, 0x00, sizeof buf );

		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"142");           
		pTaskPlan->pTask[i].nPriority = 5;

		TSAttachData *pHead = &m_SAttachData;		
		pHead->nCount = pPacket->lvol3; //����
		pHead->nValue = pPacket->lvol5; //����
		if( strlen(pPacket->saddr) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->saddr,(BYTE*)pHead->szValue+0,8);			//1
			memcpy(buf,pPacket->saddr,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr+6,2);
			end_m=atol(buf);
			pHead->szValue[0]=start_h;
			pHead->szValue[1]=start_m;
			pHead->szValue[2]=end_h;
			pHead->szValue[3]=end_m;
		}
		if( strlen(pPacket->saddr2) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->saddr2,(BYTE*)pHead->szValue+8,8);		//2
			memcpy(buf,pPacket->saddr2,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr2+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr2+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->saddr2+6,2);
			end_m=atol(buf);
			pHead->szValue[8]=start_h;
			pHead->szValue[9]=start_m;
			pHead->szValue[10]=end_h;
			pHead->szValue[11]=end_m;
		}
		if( strlen(pPacket->sall_name) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->sall_name,(BYTE*)pHead->szValue+16,8);	//3
			memcpy(buf,pPacket->sall_name,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sall_name+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sall_name+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sall_name+6,2);
			end_m=atol(buf);
			pHead->szValue[16]=start_h;
			pHead->szValue[17]=start_m;
			pHead->szValue[18]=end_h;
			pHead->szValue[19]=end_m;

		}
		if( strlen(pPacket->snote) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->snote,(BYTE*)pHead->szValue+24,8);		//4
			memcpy(buf,pPacket->snote,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote+6,2);
			end_m=atol(buf);
			pHead->szValue[24]=start_h;
			pHead->szValue[25]=start_m;
			pHead->szValue[26]=end_h;
			pHead->szValue[27]=end_m;
		}
		if( strlen(pPacket->snote2) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->snote2,(BYTE*)pHead->szValue+32,8);		//5
			memcpy(buf,pPacket->snote2,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote2+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote2+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->snote2+6,2);
			end_m=atol(buf);
			pHead->szValue[32]=start_h;
			pHead->szValue[33]=start_m;
			pHead->szValue[34]=end_h;
			pHead->szValue[35]=end_m;
		}
		if( strlen(pPacket->scert_addr) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->scert_addr,(BYTE*)pHead->szValue+40,8);	//6
			memcpy(buf,pPacket->scert_addr,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->scert_addr+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->scert_addr+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->scert_addr+6,2);
			end_m=atol(buf);
			pHead->szValue[40]=start_h;
			pHead->szValue[41]=start_m;
			pHead->szValue[42]=end_h;
			pHead->szValue[43]=end_m;
		}
		if( strlen(pPacket->sbankname) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->sbankname,(BYTE*)pHead->szValue+48,8);	//7
			memcpy(buf,pPacket->sbankname,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname+6,2);
			end_m=atol(buf);
			pHead->szValue[48]=start_h;
			pHead->szValue[49]=start_m;
			pHead->szValue[50]=end_h;
			pHead->szValue[51]=end_m;

		}
		if( strlen(pPacket->sbankname2) > 0 )
		{
			SVC_DSP_2_HEX((BYTE*)pPacket->sbankname2,(BYTE*)pHead->szValue+56,8);	//8		
			memcpy(buf,pPacket->sbankname2,2);
			start_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname2+2,2);
			start_m=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname2+4,2);
			end_h=atol(buf);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pPacket->sbankname2+6,2);
			end_m=atol(buf);
			pHead->szValue[56]=start_h;
			pHead->szValue[57]=start_m;
			pHead->szValue[58]=end_h;
			pHead->szValue[59]=end_m;
		}
		pTaskPlan->pTask[i].pData = (char*)pHead;
		pTaskPlan->nTask++;
		WriteLog("�´���ʱ��ʱ���(%d). ����=%ld. ����=%ld\n", nRequest,pHead->nCount , pHead->nValue);
		}
		break;
	case 930120: //�Ž�����		
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"143");           
		pTaskPlan->pTask[i].nPriority = 5;

		sprintf(pTaskPlan->pTask[i].szMemo,"%ld",pPacket->lvol3); //��ʶ
		pTaskPlan->nTask++;
		WriteLog("�Ž�����(%d). ��ʶ=%ld\n", nRequest,pPacket->lvol3);
		break;
	case 930102: //��ʱ����ʷ��ˮ��
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"145");           
		pTaskPlan->pTask[i].nPriority = 5;
		sprintf(pTaskPlan->pTask[i].szMemo,"%ld",    pPacket->lvol3); //��ʼ��ˮ
		pTaskPlan->nTask++;
		WriteLog("��ʱ����ʷ��ˮ(%d). ��ʼ��ˮ=%ld ������ˮ=%ld\n", nRequest,pPacket->lvol3,pPacket->lvol4);
		break;

	case 930103: //�´���ʱ���豸������
		{
		BYTE  buf[20],*pt=NULL;
		unsigned long l=0;
		memset(buf, 0x00,sizeof buf);

		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"144");
		pTaskPlan->pTask[i].nPriority = 3;

		//���뿪��
		pTaskPlan->pTask[i].szMemo[0] = 0x01;

		l = pPacket->lvol3;
		pt = (BYTE*)&l;
		pTaskPlan->pTask[i].szMemo[1] = *(pt+0); //����ģʽ

		l = pPacket->lvol5;
		pt = (BYTE*)&l;
		pTaskPlan->pTask[i].szMemo[2] = *(pt+0); //����ʱ��1

		pt = (BYTE*)&pPacket->lvol6; 
		pTaskPlan->pTask[i].szMemo[3] = *(pt+0); //����ʱ��2

		pTaskPlan->pTask[i].szMemo[4] =(BYTE)0xff;   //��������
		pTaskPlan->pTask[i].szMemo[5] = (BYTE)0xff; 

		l = atol(pPacket->sstatus0);
		pt = (BYTE*)&l;
		pTaskPlan->pTask[i].szMemo[6] = *(pt+0); //ͨ��ģʽ

		l=atol(pPacket->sstatus1); 
		pt = (BYTE*)&l; 
		pTaskPlan->pTask[i].szMemo[7] = *(pt+0); //�洢		
		pTaskPlan->pTask[i].szMemo[8] = 0x01; //��Ӧͷ

		//��������
		pTaskPlan->pTask[i].szMemo[9] =  0x00;
		pTaskPlan->pTask[i].szMemo[10] = 0x00;
		pTaskPlan->pTask[i].szMemo[11] = 0x00;
		SVC_DSP_2_HEX((unsigned char *)pPacket->semp_pwd,buf,3); //ϵͳ����Ա����
		pTaskPlan->pTask[i].szMemo[12]=buf[0];
		pTaskPlan->pTask[i].szMemo[13]=buf[1];
		pTaskPlan->pTask[i].szMemo[14]=buf[2];
		
		pTaskPlan->pTask[i].szMemo[15]=0x00;
		pTaskPlan->pTask[i].szMemo[16]=0x00;

		
		pTaskPlan->pTask[i].szMemo[17] = 0x00; //V10�û�������/Ǯ������

		l = atol(pPacket->sstatus2); //(LED��ʾ0/Һ��LCD��ʾ1)(����)
		pt=(BYTE*)&l;
		pTaskPlan->pTask[i].szMemo[18] = *(pt+0); 

		l = pPacket->lvol7; //������
		pt=(BYTE*)&l;
		pTaskPlan->pTask[i].szMemo[19] = *(pt+0); 
		pTaskPlan->pTask[i].szMemo[20]=0x00;
		pTaskPlan->pTask[i].szMemo[21]=0x00;
		pTaskPlan->pTask[i].szMemo[22]=0x00;
		pTaskPlan->pTask[i].szMemo[23]=0x00;
		pTaskPlan->pTask[i].szMemo[24]=0x00;
		pTaskPlan->pTask[i].szMemo[25]=0x00;
		pTaskPlan->pTask[i].szMemo[26]=0x00;
		pt=(BYTE*)&pPacket->lserial0;//����ʹ�ÿ��Ͳ���
		pTaskPlan->pTask[i].szMemo[27] = *(pt+0); 
		pTaskPlan->nTask++;		
		}
		break;
	case 930104: //�ϴ���ʱ���豸������
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"146");           
		pTaskPlan->pTask[i].nPriority = 9;
		pTaskPlan->nTask++;
		WriteLog("�ϴ��豸������(%d). �ն��豸ID=%s \n", nRequest, pDeviceID);
		break;

	case 930003:	//�´�������
	case 930004:	//ɾ��������
	case 930005:	//�㲥������
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"70");           
		pTaskPlan->pTask[i].nPriority = 9;
		sprintf(pTaskPlan->pTask[i].szMemo,"%08ld",pPacket->lvol0);
		memcpy(pTaskPlan->pTask[i].szMemo+8,pPacket->sserial0,12);

		if( nRequest == 930003 )
		{
			printf("�´�������,�ն�ID[%s],����[%ld],�汾[%s].............\n",pDeviceID,pPacket->lvol0,pPacket->sserial0);
			pTaskPlan->pTask[i].szMemo[45]='1';
			memcpy(pTaskPlan->pTask[i].szMemo+20,pPacket->sserial1,12);		
		}
		else if(nRequest == 930004 )
		{
			pTaskPlan->pTask[i].szMemo[45]='2';
			printf("ɾ��������,�ն�ID[%s],����[%ld],�汾[%s].............\n",pDeviceID,pPacket->lvol0,pPacket->sserial0);
		}		
		else if(nRequest == 930005 )
		{
			char tmp[10];
			sprintf(tmp,"%ld",	pPacket->lvol4);
			pTaskPlan->pTask[i].szMemo[45]='3';
			pTaskPlan->pTask[i].szMemo[46]=tmp[0];	//��ɾ����־
			printf("�㲥������,�ն�ID[%s],����[%ld],�汾[%s].............\n",pDeviceID,pPacket->lvol0,pPacket->sserial0);
		}		
		pTaskPlan->nTask++;		
		break;
	case 930021:
		if( !PacketToSmartDoc(pPacket) )
		{
			strcpy(pTaskPlan->pTask[i].szMemo,"0930021"); //������Ч
		}
		else
		{
			strcpy(pTaskPlan->pTask[i].szMemo,"1930021"); //������Ч
		}
		pTaskPlan->pTask[i].pData=(char*)&m_SSmartDoc;
		pTaskPlan->nTask++;		
		break;
	case 930065: //�ϴ���������
		pTaskPlan->pTask[i].nTaskID = GetTickCount();
		pTaskPlan->pTask[i].nTaskPlanID=pTaskPlan->nTaskPlanID; 
		pTaskPlan->pTask[i].nAuthID = nAuthID;                  
		strcpy(pTaskPlan->pTask[i].szDeviceID, pDeviceID);      
		strcpy(pTaskPlan->pTask[i].szTaskCode,"61");           
		pTaskPlan->pTask[i].nPriority = 8;
		sprintf(pTaskPlan->pTask[i].szMemo,"%ld",pPacket->lvol5);  
		pTaskPlan->nTask++;
		WriteLog("�ϴ���������%ld\n", nRequest);
		break;
	default:
		WriteLog("��֧�ֵĹ��ܺ�.......(%d). �ն��豸ID=%s....\n", nRequest, pDeviceID);
		printf("��֧�ֵĹ��ܺ�.......(%d). �ն��豸ID=%s....\n", nRequest, pDeviceID);
		AnswerResultError(nRequest, pPacket->lvol1, -1, "��֧�ֵĹ��ܺ�");
		bResult = false ;		
		break;
	}
	return bResult;
}


//930021�����˴����ݰ�ת��Ϊ�豸��
bool CInterfaceApp::PacketToSmartDoc(ST_PACK *pPacket)
{
	memset(&m_SSmartDoc, 0x00, sizeof m_SSmartDoc );
	printf("------�����豸ID=%s--------\n",pPacket->sdate0);
	printf("------�����豸����=%d------\n",pPacket->lvol4);
	printf("------���յ�ַ=%s----------\n",pPacket->sstation0);
	printf("------���ջ��ʹ���=%s------\n",pPacket->semp);
	printf("------�����豸ע���=%s-----\n",pPacket->sdate2);

	strcpy(m_SSmartDoc.m_szMacCode, pPacket->semp);			//�ն˻��ͺŴ���
	strcpy(m_SSmartDoc.m_szMacCard, pPacket->sholder_type);//����IC������
	strcpy(m_SSmartDoc.m_szMacModle, pPacket->semp);		//�ն˻��ͺ�
	strcpy(m_SSmartDoc.m_szMacType, pPacket->semp);			//��������
	strcpy(m_SSmartDoc.m_szDeviceID, pPacket->sdate0);		//�豸ID
	strcpy(m_SSmartDoc.m_szRegister, pPacket->sdate2);		//ע���
	m_SSmartDoc.m_nAuthID=ConvertID(m_SSmartDoc.m_szDeviceID);		//��Ȩ��
	m_SSmartDoc.m_nMachineNo=pPacket->lvol4;				//����	
	strcpy(m_SSmartDoc.m_szVersion, pPacket->sdate3);		//�豸�汾��
	strcpy(m_SSmartDoc.m_szPassword, "000000");				//ϵͳԱ����
	strcpy(m_SSmartDoc.m_szOprPasswd, "000000");			//����Ա����
	m_SSmartDoc.m_nPwdswitch=-1;							//���뿪��

	if( strlen(pPacket->stime0) != 8 )
	{
		printf("�Ƿ����豸!\n");
		strcpy(m_SSmartDoc.m_sClockVer, "");
	}
	else
		strcpy(m_SSmartDoc.m_sClockVer, pPacket->stime0);

	strcpy(m_SSmartDoc.m_szOrgid, "001");					//��������֯����
	m_SSmartDoc.m_nPortCount=pPacket->lvol5;				//�������˿�����
	printf("------�������˿�����%d-----\n",pPacket->lvol5);
	m_SSmartDoc.m_nSMTPort=pPacket->lvol6;				  //�������˿ں�
	printf("------�������˿ں�%d-----\n",pPacket->lvol6);
	strcpy(m_SSmartDoc.m_szPort, pPacket->sbank_code);	  //ͨѶ�˿�
	printf("------ͨѶ�˿�%s-----\n",pPacket->sbank_code);
	m_SSmartDoc.m_nBaudRate=pPacket->lvol9;			  //������
	m_SSmartDoc.m_nCommMode=pPacket->lvol8;			  //��·ģʽ
	printf("------��·ģʽ%d-----\n",pPacket->lvol8);

	strcpy(m_SSmartDoc.m_szAddr, pPacket->sstation0);    //ͨѶ��ַ
	m_SSmartDoc.m_nStatus=pPacket->lvol7;                //�豸״̬, ���涨��Ϊ:
	printf("------�豸״̬%d-----\n",pPacket->lvol7);
	m_SSmartDoc.m_nConnType = pPacket->lvol10;			  //ͨѶ��ʽ
	strcpy(m_SSmartDoc.m_szClass, pPacket->snote2);	  //����				  //

	m_SSmartDoc.m_wFlowNo=pPacket->lvol11+1;			  //������ˮ�� modified
	m_SSmartDoc.m_wLastInvoiceNo=pPacket->lvol11;        //�ն˽�����ˮ����ĩֵ
	m_SSmartDoc.m_wStateNo=pPacket->lvol12;
	m_SSmartDoc.m_nFlow=1;									//���
	m_SSmartDoc.m_nBeginInvoice=0;							//���ʵĿ�ʼ��ˮ
	m_SSmartDoc.m_wSettleinvoice=0;							//������ˮ����ĩֵ
	m_SSmartDoc.m_wEndInvoice=0;							//���ʵĽ�����ˮ��
	strcpy(m_SSmartDoc.m_sBlackExpire, pPacket->sserial0);  //����������Ч��
	strcpy(m_SSmartDoc.m_sDownBlackTime, pPacket->sserial1); //�������´�ʱ����ĩֵ
	m_SSmartDoc.m_nStartuse=0;								 //ǩ�����

	if( !CheckSmartDocValid(&m_SSmartDoc) )
	{
		printf("CheckSmartDocValid !!!!!\n");
		return false;
	}
	WriteLog("�ն˻��ͺŴ���=%s,����IC������=%s, �ն˻��ͺ�=%s, ��������=%s, "
		"�豸ID=%s, ע���=%s, ����=%d, �豸�汾��=%s, ϵͳԱ����=%s, ����Ա����=%s,"
		"���뿪��=%d, �������˿�����=%d, �������˿ں�=%d, ͨѶ�˿�=%s, ������=%d,"
		"��·ģʽ=%d,ͨѶ��ַ=%s, �豸״̬=%d, ������ˮ����ĩֵ=%d, ����������Ч��=%s, �������汾=%s, ͨѶ��ʽ=%d,����=%s, ���豸:%s\n",
		pPacket->semp, pPacket->sholder_type, pPacket->semp, pPacket->semp,
		pPacket->sdate0, pPacket->sdate2, pPacket->lvol4, pPacket->sdate3, "000000", "000000", 
		m_SSmartDoc.m_nPwdswitch, pPacket->lvol5, pPacket->lvol6, pPacket->sbank_code, pPacket->lvol9, 
		pPacket->lvol8, pPacket->sstation0, pPacket->lvol7, pPacket->lvol11, pPacket->sserial0, pPacket->sserial1, 
		pPacket->lvol10, pPacket->snote2, pPacket->stime0);

	printf("�����豸(ID=%s, ע���:%s, ����=%d, ��������:%d..���豸:%s...\n", 
		m_SSmartDoc.m_szDeviceID, m_SSmartDoc.m_szRegister, 
		m_SSmartDoc.m_nMachineNo, m_SSmartDoc.m_nCommMode, pPacket->stime0);
	return true;
}


long CInterfaceApp::AnswerSmartDocSuccess(int iFunction, int iMsg, int iResult, char *pszDeviceID)
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(rpack));

	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/	
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	rpack.head.RequestType = 930098; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_LVOL1, GetValue(iMsg));				//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_LVOL2, GetValue(iFunction));		//���ܺ�
	SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(iResult));			//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_VSMESS, "�ɹ�");					//��������Ϣ
	SetValue(&rpack.head,&rpack.pack, F_SDATE0, pszDeviceID);				//�豸ID

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));

	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		printf("AnswerSmartDocSuccess\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
			// modified by lina 2005042 int nlen = RecvData(hHandle, buffer, nLen, 0);
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						ConnectPool.Free(hHandle);
						return RET_OK;
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	return RET_SYSERROR;
}


long CInterfaceApp::AnswerResult(int iFunction, int iMsg, int iResult, char *pszMsg)
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(rpack));

	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	rpack.head.RequestType = 930098; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_LVOL1, GetValue(iMsg));				//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_LVOL2, GetValue(iFunction));		//���ܺ�
	SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(iResult));			//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_VSMESS, pszMsg);					//��������Ϣ

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));

	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		printf("AnswerResult\n");
		if (SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK)
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
		}
	}
	ConnectPool.Free(hHandle);
	return RET_OK;
}

long CInterfaceApp::AnswerResultError(int iFunction, int iMsg, int iResult, char *pszMsg)
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(rpack));

	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag = 0;    /* �Ƿ����������*/
	rpack.head.recCount = 1;    /* �����ļ�¼��*/
	rpack.head.retCode = 0;     /* ���ش���*/
	rpack.head.userdata = 0;

	rpack.head.RequestType = 930098; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_LVOL1, GetValue(iMsg));				//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_LVOL2, GetValue(iFunction));			//���ܺ�
	SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(iResult));			//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_VSMESS, pszMsg);					//��������Ϣ

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));

	HANDLE& hHandle = ConnectPool.Alloc();

	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		printf("AnswerResultError\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
//modified by lina 20050402			int nlen = RecvData(hHandle, buffer, nLen, 0);
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						ConnectPool.Free(hHandle);
						return RET_OK;
					}
					else
					{
						printf("%s\n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	return RET_SYSERROR;
}

long CInterfaceApp::ReportResult(TSSmartTask *pTask, long iResult, TSResultData *pData)
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(rpack));

	rpack.head.firstflag = 1;   /* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag  = 0;    /* �Ƿ����������*/
	rpack.head.recCount  = 1;    /* �����ļ�¼��*/
	rpack.head.retCode   = 0;     /* ���ش���*/
	rpack.head.userdata  = 0;

	rpack.head.RequestType = 930098; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_LVOL1, pTask->szSystemNO);			//��ϢID
	SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(iResult));			//���
	SetValue(&rpack.head,&rpack.pack, F_VSMESS, pData->sMsg);				//��������Ϣ

	switch(pTask->nFunc)
	{
	case 930001://�´��豸ʱ��
		WriteLog("�豸:%s, ���ذ�(930098),�´��豸ʱ��.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930002://�ϴ��豸ʱ��
		WriteLog("�豸:%s, ���ذ�(930098),�ϴ��豸ʱ��.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pData->sValue1);
		break;
	case 930003://�´���������ָ���豸��
		{	
			char buf[30];
			SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pTask->szMemo,8);
			SetValue(&rpack.head,&rpack.pack, F_LVOL0, GetValue(atol(buf)));
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pTask->szMemo+8,12);
			SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, buf);
			WriteLog("�豸:%s, ���ذ�(930098),�´���������ָ���豸��.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
			//printf("�豸:%s, ���ذ�(930098),�´���������ָ���豸��.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		}
		break;
	case 930004://ɾ����������ָ���豸��
		{
			char buf[30];
			SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pTask->szMemo,8);
			SetValue(&rpack.head,&rpack.pack, F_LVOL0, GetValue(atol(buf)));
			memset(buf, 0x00, sizeof buf );
			memcpy(buf,pTask->szMemo+8,12);
			SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, buf);
			WriteLog("�豸:%s, ���ذ�(930098),ɾ����������ָ���豸��.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
			//printf("�豸:%s, ���ذ�(930098),ɾ����������ָ���豸��.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		}
		break;
	case 930005://�㲥������
		SetValue(&rpack.head,&rpack.pack, F_LVOL0, GetValue(pData->nValue1));
		SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pData->sValue1);
		WriteLog("�豸:%s, ���ذ�(930098),�㲥������.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		break;
	case 930006://�´����ѱ���
		{
		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead == NULL )
		{
			return RET_OK;
		}
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);
		SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue(pHead->nValue));
		WriteLog("�豸:%s, ���ذ�(930098),�´����ѱ���.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		}
		break;
	case 930007://�´��豸������
		{
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);
		WriteLog("�豸:%s, ���ذ�(930098),�´��豸������.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead )
		{
			TSResultData *pArray = (TSResultData*)pHead->pData;
			if( pArray != NULL )	
			{
				/*
				delete pArray;
				pArray=NULL;
				*/
			}
			if( pHead != NULL )
			{
				/*
				delete pHead;
				pHead=NULL;
				*/
			}
			pTask->pData = NULL;
		}
		}	
		break;
	case 930008://�ϴ��豸������
		{
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pData->sValue1);	//�ն��豸ID
		SetValue(&rpack.head,&rpack.pack, F_LVOL3, GetValue(pData->nValue1));	//����	
		SetValue(&rpack.head,&rpack.pack, F_SDATE2, pData->sValue2);	//ע���
		SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue(pData->nValue2));	//lvol5  ������ 
		SetValue(&rpack.head,&rpack.pack, F_SEMP_PWD, pData->sValue3);	//sopen_emp ϵͳԱ���� 
		SetValue(&rpack.head,&rpack.pack, F_SEMP_PWD2, pData->sValue4);	//sclose_emp ����Ա����
		SetValue(&rpack.head,&rpack.pack, F_LVOL6, GetValue(pData->nValue3));	//lvol6 ���뿪��
		SetValue(&rpack.head,&rpack.pack, F_SBANK_PWD, pData->sValue5);	//scurrency_type ��Ƭ�ṹ 
		SetValue(&rpack.head,&rpack.pack, F_LVOL7, GetValue(pData->nValue4));	//lvol7 �������ʹ�ô���
		SetValue(&rpack.head,&rpack.pack, F_LVOL8, GetValue(pData->nValue5));	//lvol8 Ǯ����ߴ���޶�
		SetValue(&rpack.head,&rpack.pack, F_LVOL9, GetValue(pData->nValue6));	//lvol9 Ǯ�����ʣ����޶�
		SetValue(&rpack.head,&rpack.pack, F_LVOL10, GetValue(pData->nValue7));	//lvol10 ��ֵ�շѷ�ʽʹ�õĶ�ֵ��
		SetValue(&rpack.head,&rpack.pack, F_SBRANCH_CODE0, pData->sValue6);	//sbranch_code0 Ǯ������ 
		SetValue(&rpack.head,&rpack.pack, F_LVOL11, GetValue(pData->nValue8));	//lvol11 ÿ�ν�����߶�
		SetValue(&rpack.head,&rpack.pack, F_SBANKNAME, pData->sValue7);	//sbankname �ն˻������û������
		SetValue(&rpack.head,&rpack.pack, F_SCURRENCY_TYPE2, pData->sValue8);	//scurrency_type2 �շѻ���ǿ���ܿ���
		SetValue(&rpack.head,&rpack.pack, F_LVOL12, GetValue(pData->nValue9));	//�շѷ�ʽ

		WriteLog("�ϴ��豸������. �ն��豸ID=%s\n", pData->sValue1);
		WriteLog("����=%d\n", pData->nValue1);
		WriteLog("ע���=%s\n", pData->sValue2);
		WriteLog("������=%d\n", pData->nValue2);
		WriteLog("ϵͳԱ����=%s\n", pData->sValue3);
		WriteLog("����Ա����=%s\n", pData->sValue4);
		WriteLog("���뿪��=%d\n", pData->nValue3);
		WriteLog("��Ƭ�ṹ=%s\n", pData->sValue5);
		WriteLog("�������ʹ�ô���=%d\n", pData->nValue4);
		WriteLog("Ǯ����ߴ���޶�=%d\n", pData->nValue5);
		WriteLog("Ǯ�����ʣ����޶�=%d\n", pData->nValue6);
		WriteLog("��ֵ�շѷ�ʽʹ�õĶ�ֵ��=%d\n", pData->nValue7);
		WriteLog("Ǯ������=%s\n", pData->sValue6);
		WriteLog("ÿ�ν�����߶�=%d\n", pData->nValue8);
		WriteLog("�ն˻������û������=%s\n", pData->sValue7);
		WriteLog("�շѻ���ǿ���ܿ���=%s\n\n", pData->sValue8);
		WriteLog("�շѷ�ʽ=%d\n\n", pData->nValue9);

		WriteLog("�豸:%s, ���ذ�(930098),�ϴ��豸������.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		}
		break;
	case 930009://���ò�������
		WriteLog("�豸:%s, ���ذ�(930098),���ò�������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930010://�´���������޶�
		WriteLog("�豸:%s, ���ذ�(930098),�´���������޶�.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		break;
	case 930011://�������ѱ�ż��汾
		{
		WriteLog("�豸:%s, ���ذ�(930098),�������ѱ�ż��汾....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		
		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead )
		{
			int *pArray = (int*)pHead->pData;
			/*
			if( pArray != NULL )
			delete [] pArray;
			if( pHead != NULL )	
			delete pHead;
			*/
			pArray=NULL;
			pHead=NULL;
			pTask->pData = NULL;
		}
		}
		break;
	case 930012://�������ѿ�ݱ��
		{
		WriteLog("�豸:%s, ���ذ�(930098),�������ѿ�ݱ��.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		printf("�豸:%s, ���ذ�(930098),�������ѿ�ݱ��.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead )
		{
			int *pArray = (int*)pHead->pData;
			/*
			if( pArray != NULL )
				delete [] pArray; 
			if( pHead != NULL )	
				delete pHead;
			*/
			pArray=NULL;
			pHead=NULL;
			pTask->pData = NULL;
		}
		}
		break;
	case 930013://��������ʱ��β���
		{
		WriteLog("�豸:%s, ���ذ�(930098),��������ʱ��β���.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead )
		{
			TSXFTimePara *pArray = (TSXFTimePara*)pHead->pData;
			/*
			if( pArray != NULL )
				delete [] pArray; 
			if( pHead != NULL )	
				delete pHead;
			*/
			pArray=NULL;
			pHead=NULL;
			pTask->pData = NULL;

		}
		}
		break;
	case 930014://����״̬����\����״̬����\ȡ����������ָ�����
		WriteLog("�豸:%s, ���ذ�(930098),����״̬����.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		break;
	case 930015://�豸����
		WriteLog("�豸:%s, ���ذ�(930098),�豸����.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		break;
#if 0
	case 930020://�´�������������
		{
		WriteLog("�豸:%s, ���ذ�(930098),�´�������������.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);

		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		if( pHead == NULL )
			return RET_OK;

		TSBZDataList *pArray = (TSBZDataList*)pHead->pData;
	///	SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);	//�ն��豸ID
	///	SetValue(&rpack.head,&rpack.pack, F_LVOL0, GetValue(pArray[pHead->nCount-1].nCardID));	//����	
		/*
		if( pArray != NULL )
			delete [] pArray;
		if( pHead != NULL )	
			delete pHead;
		*/
		pArray=NULL;
		pHead=NULL;

		pTask->pData = NULL;

		}
		break;
#endif
	case 930056://�´��豸��ز���
		WriteLog("�豸:%s, ���ذ�(930056),�´��豸��ز���.....������:%d, ��Ϣ:%s..\n", pTask->szDeviceID, iResult, pData->sMsg);
		break;
	case 930060://�豸ǩ��ǩ��
		WriteLog("�豸:%s, ���ذ�(930060),�����豸ǩ��ǩ��.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930061://����ÿ����������޶�
		WriteLog("�豸:%s,���ذ�(930061),����ÿ���ۼ������޶�....���ش���:%d,��Ϣ:%s\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930062:
		WriteLog("�豸:%s,���ذ�(930062),��ʼ��LPORT�˿ڲ���....���ش���:%d,��Ϣ:%s\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930063:
		WriteLog("�豸:%s,���ذ�(930063),�����ն˹���Ա����....���ش���:%d,��Ϣ:%s\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930064:
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pData->sValue1);	//sdate0�ն��豸ID
		SetValue(&rpack.head,&rpack.pack, F_LVOL3, GetValue(pData->nValue1));	//lvol3����	
		SetValue(&rpack.head,&rpack.pack, F_SEMP, pData->sValue2);	//semp����
		SetValue(&rpack.head,&rpack.pack, F_SDATE3, pData->sValue3);	//sdate3 ����汾 
		SetValue(&rpack.head,&rpack.pack, F_SDATE2, pData->sValue4);	//sdate2ע��� 
		WriteLog("�豸:%s,���ذ�(930064),��ȡlportָ���˿ڵ��豸����....���ش���:%d,��Ϣ:%s\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	//dengjun
	case 930117:
		WriteLog("�豸:%s, ���ذ�(930098),�´�/ɾ��������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;		
	case 930118:
		WriteLog("�豸:%s, ���ذ�(930098),�㲥������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930121:
		{
			char cardno[10];
			TSAttachData *pHead = &m_SAttachData;			
			memset(cardno, 0x00, sizeof cardno);
			memcpy(cardno,pHead->szValue,10);		
			SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pHead->szValue+50);
			SetValue(&rpack.head,&rpack.pack, F_LVOL3, cardno);
			WriteLog("�豸:%s, ���ذ�(930098),�´�/ɾ�����������汾.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
			break;
		}	
	case 930201: //�´���ʱ�������°���������
		WriteLog("�豸:%s, ���ذ�(930098),�´���ʱ�������°���������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;		
	case 930114://�ϴ�����汾
		WriteLog("�豸:%s, ���ذ�(930114),�ϴ�����汾.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pData->ssValue1);
		break;
	case 930110://�ϴ��ڼ���		
		{
		char tmp[100],i=0;
		memset(tmp, 0x00,sizeof tmp );
		for(i=0; i<pData->nValue1*2; i++)
		{
			sprintf(tmp+2*i,"%02ld",pData->ssValue1[i]);
		}		
		WriteLog("�豸:%s, ���ذ�(930110),�ϴ��ڼ���.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue((int)pData->nValue1));		
		SetValue(&rpack.head,&rpack.pack, F_VSVARSTR0, tmp);		
		}
		break;
	case 930106://�ϴ�ʱ���
		{
			char  tmp[129],buf[100];
			memset(tmp, 0x00, sizeof tmp );
			memset(buf, 0x00, sizeof buf );

			WriteLog("�豸:%s, ���ذ�(930106),�ϴ�ʱ���.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
			SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue(pData->nValue1));		//����
			if( pData->nValue1 == 1 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,8);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
			}
			else if( pData->nValue1 == 2 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,16);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);				
			}
			else if( pData->nValue1 == 3 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,24);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
			}
			else if( pData->nValue1 == 4 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,32);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[48],pData->ssValue1[49],pData->ssValue1[50],pData->ssValue1[51]);
				memcpy(tmp+48,buf,8);				
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE, tmp+48);
			}
			else if( pData->nValue1 == 5 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,40);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[48],pData->ssValue1[49],pData->ssValue1[50],pData->ssValue1[51]);
				memcpy(tmp+48,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[64],pData->ssValue1[65],pData->ssValue1[66],pData->ssValue1[67]);
				memcpy(tmp+64,buf,8);				
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE, tmp+48);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE2, tmp+64);
			}
			else if( pData->nValue1 == 6 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,48);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[48],pData->ssValue1[49],pData->ssValue1[50],pData->ssValue1[51]);
				memcpy(tmp+48,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[64],pData->ssValue1[65],pData->ssValue1[66],pData->ssValue1[67]);
				memcpy(tmp+64,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[80],pData->ssValue1[81],pData->ssValue1[82],pData->ssValue1[83]);
				memcpy(tmp+80,buf,8);				

				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE, tmp+48);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE2, tmp+64);
				SetValue(&rpack.head,&rpack.pack, F_SCERT_ADDR, tmp+80);
			}
			else if( pData->nValue1 == 7 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,56);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[48],pData->ssValue1[49],pData->ssValue1[50],pData->ssValue1[51]);
				memcpy(tmp+48,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[64],pData->ssValue1[65],pData->ssValue1[66],pData->ssValue1[67]);
				memcpy(tmp+64,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[80],pData->ssValue1[81],pData->ssValue1[82],pData->ssValue1[83]);
				memcpy(tmp+80,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[96],pData->ssValue1[97],pData->ssValue1[98],pData->ssValue1[99]);
				memcpy(tmp+96,buf,8);				

				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE, tmp+48);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE2, tmp+64);
				SetValue(&rpack.head,&rpack.pack, F_SCERT_ADDR, tmp+80);
				SetValue(&rpack.head,&rpack.pack, F_SBANKNAME, tmp+96);
			}
			else if( pData->nValue1 == 8 )
			{				
				SVC_HEX_2_DSP((BYTE*)pData->ssValue1,(BYTE*)tmp,64);			
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
				memcpy(tmp,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[8],pData->ssValue1[9],pData->ssValue1[10],pData->ssValue1[11]);
				memcpy(tmp+16,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[24],pData->ssValue1[25],pData->ssValue1[26],pData->ssValue1[27]);
				memcpy(tmp+32,buf,8);
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[48],pData->ssValue1[49],pData->ssValue1[50],pData->ssValue1[51]);
				memcpy(tmp+48,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[64],pData->ssValue1[65],pData->ssValue1[66],pData->ssValue1[67]);
				memcpy(tmp+64,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[80],pData->ssValue1[81],pData->ssValue1[82],pData->ssValue1[83]);
				memcpy(tmp+80,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[96],pData->ssValue1[97],pData->ssValue1[98],pData->ssValue1[99]);
				memcpy(tmp+96,buf,8);				
				sprintf(buf,"%02ld%02ld%02ld%02ld",pData->ssValue1[112],pData->ssValue1[113],pData->ssValue1[114],pData->ssValue1[115]);
				memcpy(tmp+112,buf,8);				
				SetValue(&rpack.head,&rpack.pack, F_SADDR, tmp+0);		
				SetValue(&rpack.head,&rpack.pack, F_SADDR2, tmp+16);
				SetValue(&rpack.head,&rpack.pack, F_SALL_NAME, tmp+32);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE, tmp+48);
				SetValue(&rpack.head,&rpack.pack, F_SNOTE2, tmp+64);
				SetValue(&rpack.head,&rpack.pack, F_SCERT_ADDR, tmp+80);
				SetValue(&rpack.head,&rpack.pack, F_SBANKNAME, tmp+96);
				SetValue(&rpack.head,&rpack.pack, F_SBANKNAME2, tmp+112);
			}
		}
		break;
	case 930102: //��ʱ����ʷ��ˮ		
		ConvertIdentifyData(0x22, pTask, NULL, &rpack, (BYTE*)pData->ssValue1, pData->nValue1);		
		break;
	case 930104://�ϴ���ʱ��������
		{
			char ucRegNo[9];
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			SetValue(&rpack.head,&rpack.pack, F_SDATE0, pData->sValue1);  //�豸ID
			//SetValue(&rpack.head,&rpack.pack, F_LVOL4, &pData->ssValue1[4]);//����			
			sprintf(ucRegNo,"%02X%02X%02X%02X",pData->ssValue1[0],pData->ssValue1[1],pData->ssValue1[2],pData->ssValue1[3]);
			SetValue(&rpack.head,&rpack.pack, F_SDATE1, (char*)ucRegNo);  //ע���
			//SetValue(&rpack.head,&rpack.pack, F_LVOL5, &pData->ssValue1[5]);//���뿪��
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[6]);
			SetValue(&rpack.head,&rpack.pack, F_LVOL3, ucRegNo);//����ģʽ
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[7]);
			SetValue(&rpack.head,&rpack.pack, F_LVOL5, ucRegNo);//����ʱ��1
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[8]);
			SetValue(&rpack.head,&rpack.pack, F_LVOL6, ucRegNo);//����ʱ��2			
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%02X%02X",pData->ssValue1[9],pData->ssValue1[10]);
			//SetValue(&rpack.head,&rpack.pack, F_SCURRENCY_TYPE, (char*)ucRegNo);//��������
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[11]);
			SetValue(&rpack.head,&rpack.pack, F_SSTATUS0, ucRegNo);//ͨ��ģʽ
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[12]);
			SetValue(&rpack.head,&rpack.pack, F_SSTATUS1, ucRegNo);//�洢ģʽ
			//SetValue(&rpack.head,&rpack.pack, F_LVOL9, &pData->ssValue1[13]);//��Ӧͷ��Ŀ
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%02X%02X%02X",pData->ssValue1[17],pData->ssValue1[18],pData->ssValue1[19]);
			SetValue(&rpack.head,&rpack.pack, F_SEMP_PWD, ucRegNo);//ϵͳԱ����
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			//sprintf(ucRegNo,"%02X%02X",pData->ssValue1[20],pData->ssValue1[21]);
			//SetValue(&rpack.head,&rpack.pack, F_SEMP_PWD2, ucRegNo);//��λ����
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[23]);
			SetValue(&rpack.head,&rpack.pack, F_SSTATUS2, ucRegNo);//��ʾ
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%ld",pData->ssValue1[24]);
			SetValue(&rpack.head,&rpack.pack, F_LVOL7, ucRegNo);//������
			memset(ucRegNo, 0x00, sizeof ucRegNo );
			sprintf(ucRegNo,"%02X",pData->ssValue1[32]);			
			SetValue(&rpack.head,&rpack.pack, F_LSERIAL0, GetValue((int)pData->ssValue1[32]));//����
		}
		WriteLog("�豸:%s, ���ذ�(930104),�ϴ���ʱ��������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);
		break;
	case 930105:
		{
			BYTE buffer[100];
			memset(buffer, 0x00, sizeof buffer );
			memcpy(buffer,pData->ssValue1,pData->nValue1);
		}
		break;
	case 930020://���Ӳ�������
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);		
		WriteLog("�豸:%s, ���ذ�(930020),���Ӳ�������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);		
		break;
	case 930065://�ϴ���������
		{
		int m_i=0;
		char tmp[20];
		memset(tmp, 0x00, sizeof tmp );
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);		
		sprintf(tmp,"%02x%02x%02x",pTask->szMemo[0],pTask->szMemo[1],pTask->szMemo[2]);
		SetValue(&rpack.head,&rpack.pack, F_LVOL7,tmp);	//����
		m_i=pTask->szMemo[3]*256+pTask->szMemo[4];
		SetValue(&rpack.head,&rpack.pack, F_LVOL6, GetValue(m_i));	//���κ�
		m_i=pTask->szMemo[5]+pTask->szMemo[6]*256;
		SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue(m_i));	//���
		WriteLog("�豸:%s, ���ذ�(930020),�ϴ���������.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);		
		break;
		}
	case 930021://�޸��豸�����������豸
		SetValue(&rpack.head,&rpack.pack, F_SDATE0, pTask->szDeviceID);		
		WriteLog("�豸:%s, ���ذ�(930021),�޸��豸�����������豸.....������:%d, ��Ϣ:%s..\n",pTask->szDeviceID,  iResult, pData->sMsg);		
		break;

	default:
		break;
	}
	
	
	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));

	HANDLE& hHandle = ConnectPool.Alloc();
	//printf("-----------rpack->id=%d\n",rpack.pack.lvol1);
	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		//printf("-----ReportResult----------\n");
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			nLen = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
//modified by lina 20050402			int nlen = RecvData(hHandle, buffer, nLen, 0);
			int nlen = RecvData(hHandle, buffer, nLen, 10000);
			if( nlen > 0 )
			{
				ST_CPACK apack;
				memset(&apack, 0x00, sizeof(ST_CPACK));
				if( DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg) )
				{
					if( !apack.head.retCode )
					{
						ConnectPool.Free(hHandle);
						return RET_OK;
					}
					else
					{
						printf("%s\n", apack.pack.vsmess);
					}
				}
			}
		}
	}

	ConnectPool.Free(hHandle);

	return RET_SYSERROR;
}

long CInterfaceApp::OutputResultBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard)
{
	
	ST_CPACK rpack;

	memset(&rpack,0x00,sizeof(rpack));

	//���ͼ��������	
	if( !memcmp(pCard->sValid,"930057",6) )
	{
		WriteLog("��������������ݰ������˴�......[%s]\n",pCard->sValid);
		return SendDeviceTick(pDoc);
	}

	//���ͼ��������	
	if( !memcmp(pCard->sValid,"930058",6) )
	{
		WriteLog("����˴﷢���ն�״̬......[%s]\n",pCard->sValid);
		return SendDeviceStatus(pDoc, nFlag, pCard);		
	}	
	
	memset(&rpack, 0, sizeof(rpack));
	rpack.head.firstflag = 1;		/* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag  = 0;		/* �Ƿ����������*/
	rpack.head.recCount  = 1;		/* �����ļ�¼��*/
	rpack.head.retCode   = 0;		/* ���ش���*/
	rpack.head.userdata  = 0;

	rpack.head.RequestType = 930046; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_SDATE1, pDoc->m_szDeviceID);
	SetValue(&rpack.head,&rpack.pack, F_SSERIAL0, pCard->sVersion);

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));

	HANDLE& hHandle = ConnectPool.Alloc();
	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			//����add by dengjun 20051108
			memset(buffer, 0, sizeof(buffer));
			nLen = sizeof(buffer);	
			RecvData(hHandle, buffer, nLen, 10000);			
			ConnectPool.Free(hHandle);
			return RET_OK;
		}
	}
	ConnectPool.Free(hHandle);
	return RET_SYSERROR;
}


long CInterfaceApp::SendDeviceStatus(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard)
{
	
	ST_CPACK rpack;	
	char tmp[30];

	memset(tmp,    0x00, sizeof tmp);
	memset(&rpack, 0x00, sizeof(rpack));


	rpack.head.firstflag = 1;		/* �Ƿ��һ�������װ�����*/
	rpack.head.nextflag  = 0;		/* �Ƿ����������*/
	rpack.head.recCount  = 1;		/* �����ļ�¼��*/
	rpack.head.retCode   = 0;		/* ���ش���*/
	rpack.head.userdata  = 0;
	
	rpack.head.RequestType = 930058; 
	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE,   GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_SDATE0,       pDoc->m_szDeviceID);
	SetValue(&rpack.head,&rpack.pack, F_LVOL3,        GetValue(pCard->nCardID));	//�ն��豸״̬
	SetValue(&rpack.head,&rpack.pack, F_LVOL5,        GetValue(pCard->nFlag));	    //�˿�����	
	if( pCard->nFlag > 0 )		//ֻ�е��˿���������0ʱ,�����¼��ĸ��ն�״̬
	{
		memcpy(tmp,pCard->sVersion,pCard->nFlag);
	}
	SetValue(&rpack.head,&rpack.pack, F_SBANKNAME, tmp);
	
	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];
	
	memset(buffer, 0, sizeof(buffer));
	
	HANDLE& hHandle = ConnectPool.Alloc();
	if( EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
	{
		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) == RET_OK ) 
		{
			//����add by dengjun 20051108
			memset(buffer, 0, sizeof(buffer));
			nLen = sizeof(buffer);	
			RecvData(hHandle, buffer, nLen, 10000);			
			ConnectPool.Free(hHandle);
			return RET_OK;
		}
	}
	ConnectPool.Free(hHandle);
	return RET_SYSERROR;
}


long CInterfaceApp::DownloadBlackList(TSSmartDoc *pDoc, int nType, char *pszFileName)
{
	ST_CPACK rpack;
	char buffer[1024];
	int  nLen = sizeof(buffer);
	char omsg[256];
	int  kkkk=0;
	BOOL bEnd = FALSE ;
	ST_CPACK apack;
	ST_PACK  apackarray[60];

	int nRow   = 0 ;
	int ifirst = 1 ;

	memset(&rpack, 0x00, sizeof( ST_CPACK));
	memset(&apack, 0x00, sizeof( ST_CPACK));
	
	FILE *fp = fopen(pszFileName, "wb");
	if( fp == NULL )
	{
		printf("�������������������������ļ�ʧ��...................\n");
		return RET_SYSERROR;
	}

	HANDLE& hHandle = ConnectPool.Alloc(4);	
	
	printf("����HADLE=%ld\n",hHandle);
	while( !bEnd )
	{
		kkkk += 1;
		//printf("����930039����%d��\n",kkkk);
		memset(&rpack, 0, sizeof(rpack));
		rpack.head.firstflag = ifirst;   
		
		if( ifirst )
		{
			rpack.head.nextflag = 0; 
			rpack.head.recCount = 1;
			ifirst = 0 ;
		}
		else
		{
			rpack.head.nextflag = 1;
			memcpy(&rpack.head.hook,&apack.head.hook,sizeof(rpack.head.hook));
			rpack.head.hook.queuetype=apack.head.hook.queuetype;
		}

		//��ʱ��
		if( nType == 3 )
		{
			rpack.head.RequestType = 930202; 			
			SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(0));			//���
		}
		else
		{
			rpack.head.RequestType = 930039; 
			SetValue(&rpack.head,&rpack.pack, F_LVOL4, GetValue(nType));			//���
		}		
		SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
		SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ		
		SetValue(&rpack.head,&rpack.pack, F_SDATE2, pDoc->m_szDeviceID);		//ID

		memset(buffer, 0, sizeof(buffer));
		
		if( !EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
		{
			ConnectPool.Free(hHandle);
			fclose(fp);
			printf("���ӽ��˴����ӳ�ʧ��........................\n");
			return RET_SYSERROR;
		}

		if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) != RET_OK ) 
		{
			ConnectPool.Free(hHandle);
			fclose(fp);
			printf("����˴﷢������ʧ��........................\n");
			return RET_SYSERROR;
		}
L1:
		nLen = sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));		
		//int nlen = RecvData(hHandle, buffer, nLen, 1000);
		//update by dengjun by 20051110 ���ڽ��˴������Ҫ�ϳ���ʱ����ܷ������ݰ�(Ӧ��������Ҫ���Ϊ30��)
		int nlen = RecvData(hHandle, buffer, nLen, 30000); 
		if( nlen <= 0 )
		{
			if( nRow > 0 )
			{
				printf("ֻ���յ����˴ﷵ�صĲ�����������,�Խ������ص��ն�....................\n");
				break;
			}
			else
			{
				ConnectPool.Free(hHandle);
				fclose(fp);				
				//Ϊ�˷�ֹ���������Զ���ɹ�,���������Զ�޷�ǩ����һ����.
				printf("������������ʱ,û���յ����˴ﷵ������,ֱ��ǩ��........................\n");
				return RET_OK;
			}
		}

		BOOL bRet=DecodeBufWithArray((unsigned char*)buffer,nlen,&apack,apackarray,&nRow,omsg);
		//printf("apack.head.RequestType = %d apack->head->nextflag=%d,apack->head->recCount=%d\n",apack.head.RequestType,apack.head.nextflag,apack.head.recCount);
		
		if( nType == 3 )	//��ʱ��
		{
			if(apack.head.RequestType != 930202) goto L1;
		}
		else 
		{	
			if(apack.head.RequestType != 930039) goto L1;
		}
		
		if( !bRet || apack.head.retCode )
		{
			ConnectPool.Free(hHandle);
			fclose(fp);
			printf("���˴ﷵ�صĽ���������[%ld]........................\n",apack.head.retCode);
			return RET_SYSERROR;
		}

		TSBlackCard  card;
		if( nType == 3 ) //��ʱ��
		{
			printf("���յ�%d����ʱ������!\n", nRow);
		}
		else
		{
			printf("���յ�%d��������!\n", nRow);
		}		

		for(int i=0; i< nRow; i++)
		{
			ZeroMemory(&card, sizeof(card));
			if( !i )
			{
				card.nCardID = apack.pack.lvol0; 
				card.nFlag   = apack.pack.lvol4;
				strcpy(card.sVersion, apack.pack.sserial0);
			}
			else
			{
				card.nCardID = apackarray[i-1].lvol0;
				card.nFlag   = apackarray[i-1].lvol4;
				strcpy(card.sVersion, apackarray[i-1].sserial0);
			}

			if( fwrite(&card, sizeof(card), 1, fp) != 1 )
			{
				printf("write file error ..............................\n");
			}
		}
		if( apack.head.nextflag == 0 )	bEnd = true ;
	}
	ConnectPool.Free(hHandle);
	fclose(fp);
	return RET_OK;
}

long CInterfaceApp::ReadGSCardInfo(int nflag, TSGSJRecord *pRecord)
{
	ST_CPACK rpack;

	memset(&rpack, 0, sizeof(rpack));

	rpack.head.firstflag = 1;   
	rpack.head.nextflag = 0;    
	rpack.head.recCount = 1;    
	rpack.head.retCode = 0;  
	rpack.head.userdata = 0;

	if( nflag == 0x81 )
	{
		rpack.head.RequestType = 930040; 

	}
	else if( nflag == 0x82 )
	{
		rpack.head.RequestType = 930041; 
	}
	else 
	{
		rpack.head.RequestType = 930042; 
	}

	SetValue(&rpack.head,&rpack.pack, F_LCERT_CODE, GetValue(iSmartKey));	//ǰ�û�ע���
	SetValue(&rpack.head,&rpack.pack, F_SCUST_LIMIT2, sSmartKey);			//��̬��Կ
	SetValue(&rpack.head,&rpack.pack, F_LVOL5, GetValue(pRecord->nCardID));	//���׿���
	SetValue(&rpack.head,&rpack.pack, F_SSTOCK_CODE, pRecord->szPassword);	//����
	SetValue(&rpack.head,&rpack.pack, F_SSTATION0, pRecord->szShowID);	//��ʾ����

	char buffer[8192];
	int  nLen = sizeof(buffer);
	char omsg[256];

	memset(buffer, 0, sizeof(buffer));
	if( !EncodeBuf(&rpack, (unsigned char*)buffer, &nLen, omsg) ) 
		return RET_SYSERROR;

	HANDLE& hHandle = ConnectPool.Alloc();

	if( SendData(hHandle, iServerNo, iFunc, (char*)buffer, nLen, 1, FALSE) != RET_OK ) 
	{
		ConnectPool.Free(hHandle);
		return RET_SYSERROR;
	}

	ST_CPACK apack;

	memset(buffer, 0, sizeof(buffer));
	nLen = sizeof(buffer);
	//modifed lina 20050402	int nlen = RecvData(hHandle, buffer, nLen, 0);
	int nlen = RecvData(hHandle, buffer, nLen, 10000);
	if( nlen <= 0 )
	{
		ConnectPool.Free(hHandle);
		return RET_SYSERROR;
	}

	BOOL bRet=DecodeBuf((unsigned char*)buffer,nlen,&apack,omsg);
	if( !bRet || apack.head.retCode )
	{
		ConnectPool.Free(hHandle);
		return RET_NG;
	}

	if( rpack.head.RequestType == 930042 ) 
	{
		strcpy(pRecord->szSerial, apack.pack.scert_no);
	}

	ConnectPool.Free(hHandle);

	return RET_OK;
}

//����豸�����Ƿ�Ϸ�
bool CInterfaceApp::CheckSmartDocValid(TSSmartDoc *pDoc)
{
	//�豸ID, ע���, ����, �˿ں�
	if( strlen(pDoc->m_szDeviceID) != 8 || 
		strlen(pDoc->m_szRegister) != 8 || 
		pDoc->m_nMachineNo < 0 || pDoc->m_nMachineNo > 255 || 
		pDoc->m_nPortCount < 0 || pDoc->m_nPortCount > 24 )
	{
		printf("pDoc->m_szDeviceID = %s \n",pDoc->m_szDeviceID);
		printf("pDoc->m_szRegister = %s \n",pDoc->m_szRegister);
		return false;
	}

	//if( strcmp(pDoc->m_szMacCard, "64") &&  
	//	strcmp(pDoc->m_szMacCard, "65") && 
	//	strcmp(pDoc->m_szMacCard, "00") )
	//{
	//	return false;
	//}

	if( pDoc->m_nCommMode != 1 && pDoc->m_nCommMode != 2 && pDoc->m_nCommMode != 3 )
	{
		return false;
	}

	return true;
}


bool CInterfaceApp::CheckSmartDocValid(TSSmartDoc *pDoc, long k, long j)
{
	if( !CheckSmartDocValid(&pDoc[j]) )
		return false;

	if( j <= 0 ) return true;

	bool bBool = false ;
	bool bIP   = false;

	for(long i=0; i<k; i++)
	{
		if( i != j )
		{
			if( !strcmp(pDoc[i].m_szDeviceID, pDoc[j].m_szDeviceID) || 
				pDoc[i].m_nAuthID == pDoc[j].m_nAuthID ) 
			{
				return false;
			}

			//IP��˿ڲ�����ͬ
			if( !strcmp(pDoc[i].m_szAddr, pDoc[j].m_szAddr) && !strcmp(pDoc[i].m_szPort, pDoc[j].m_szPort) ) 
			{
				bIP = true;
			}

			//�Ƿ���ڸ��豸
			if( !strcmp(pDoc[i].m_szDeviceID, pDoc[j].m_sClockVer) )
				bBool = true;
		}
	}

	if( !bBool )
	{
		if( !strcmp(pDoc[j].m_sClockVer, "" ) )
		{
			bBool = true;
		}
		//�����LPort, �����豸������, ��ʱ��ΪLportΪֱ����ʽ
		else if( !strcmp(pDoc[j].m_szMacCode, "5301") )
		{
			strcpy(pDoc[j].m_sClockVer, "");
			bBool = true;
		}
	}

	return bBool;
}

void GetCurPath(LPTSTR pszDir)
{
	HANDLE  hHandle = GetCurrentProcess();
	GetModuleFileName(NULL, pszDir, MAX_PATH);
	for(int i=lstrlen(pszDir)-1; i>=0 ; i--)
	{
		if( pszDir[i] == '\\' )
		{
			pszDir[i] = 0;
			break;
		}
	}
}

