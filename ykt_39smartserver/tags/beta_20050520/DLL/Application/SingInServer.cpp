// SingInServer.cpp: implementation of the CSingInServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "SingInServer.h"
#include "SmartTask.h"
#include "CheckBlackVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSingInServer::CSingInServer()
{
	m_strTaskCode = "12";
	m_bMachineNo = false ;
	m_bMarkCheck = false;
}

CSingInServer::~CSingInServer()
{

}

long CSingInServer::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return MakeBuf_GetBlackVersion(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer);
}

long CSingInServer::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	bool          bResult = false;
	CTime		  tm;
	int			  E_number;
	unsigned char Clock[7];
	unsigned char Plain[256],ID[4];
	printf("处理终端%.8X签到任务\n",pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
	m_nIndex = pDocEx->nPortNo;
	//由于需要金仕达确认是否可以签到,故将签到任务提前到前面
	
	E_number = 1;
	//printf("------下传时钟--------");
	for(int i=0; i<3; i++)
	{
		tm=CTime::GetCurrentTime();
		Clock[0] = tm.GetYear()-2000;	Clock[1] = tm.GetMonth();	Clock[2] = tm.GetDay();
		Clock[3] = tm.GetHour();	Clock[4] = tm.GetMinute();	Clock[5] = tm.GetSecond();
		Clock[6] = tm.GetDayOfWeek();

		MakeBuf_SetClock(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer,Clock);
		pBuffer->nTimeOut1 = 1000 ;
		pBuffer->nTimeOut2 = 1000;
		if(SendRequest(pDocEx->pChildDoc[m_nIndex], pBuffer) == RET_OK )
		{
			if(UnMakeDeviceBuffer(pBuffer) == RET_OK)
			{		
				printf("-----下传终端%.8X时钟成功!\n",pDocEx->pChildDoc[m_nIndex]->m_nAuthID);
				bResult = true;
				break;
			}
		}
		else
			Sleep(400);
	}
	
	if( !bResult )
	{
		printf("-----!!!!下传终端%.8X时钟失败!\n",pDocEx->pChildDoc[m_nIndex]->m_nAuthID);
		ReportLog(pDocEx->pChildDoc[m_nIndex], pTask, RET_CLOCK_ERROR, "终端机签到", "终端机签到 ---校对时钟失败!");
		pDocEx->pChildDoc[pDocEx->nPortNo]->m_nSignIn = RET_CLOCK_ERROR ;
		return RET_CLOCK_ERROR;
	}
	Sleep(500);
	char szKeyBuf[256];

	memset(Plain, 0, sizeof(Plain));
	memset(szKeyBuf, 0, sizeof(szKeyBuf));

	GetAuthKey(szKeyBuf);

	SVC_DSP_2_HEX((unsigned char *)szKeyBuf, Plain, strlen(szKeyBuf)/2);
//	printf("------设置授权信息------------");
	//设置授权信息
	bResult = false;
	for(i=0; i<3; i++)
	{
		SVC_DSP_2_HEX((unsigned char *)pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, ID, 4);
		//modified by lina 20050308 SmartEncrypt(E_number,ID,Plain); 
		MakeBuf_SetWorkingKey(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo,pBuffer,Plain,E_number);
		pBuffer->nTimeOut1 = 1000 ;
		pBuffer->nTimeOut2 = 1000;
		if(SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) == RET_OK )
		{
			if(UnMakeDeviceBuffer(pBuffer) == RET_OK )
			{
				printf("-----设置终端%.8X授权信息成功!\n",pDocEx->pChildDoc[m_nIndex]->m_nAuthID);
				bResult = true;
				break;
			}
		}	
		else
			Sleep(300);
	}

	if( !bResult )
	{
		printf("-----!!!!设置终端%.8X授权信息失败!\n",pDocEx->pChildDoc[m_nIndex]->m_nAuthID);
		ReportLog(pDocEx->pChildDoc[m_nIndex], pTask, RET_NOT_AUTH, "终端机签到", "终端机签到 ---设置授权信息失败!");
		pDocEx->pChildDoc[pDocEx->nPortNo]->m_nSignIn = RET_NOT_AUTH ;
		return RET_NOT_AUTH;
	}
	if(SignIn(pDocEx->pChildDoc[pDocEx->nPortNo]) != RET_OK)
	{
		printf("!!!!后台不允许签到\n");
		return  RET_ERROR_AUTH;//                  25      //25:后台不允许签到;
	}
	
	Sleep(500);
	//printf("------设置消费开关----------");//
	bResult = false;
	for(i=0; i<3; i++)
	{
		MakeBuf_SetComsumeFlag(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, 1);
		pBuffer->nTimeOut1 = 1000 ;
		pBuffer->nTimeOut2 = 1000;
		if( SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) == RET_OK )
		{
		    if( UnMakeDeviceBuffer(pBuffer) == RET_OK )
			{
				//printf("成功!\n");
				bResult = true;
				break;
			}
		}
		else
		   Sleep(300);
	}

	if( !bResult )
	{
		printf("----!!!!设备%.8X签到失败!\n",pDocEx->pChildDoc[m_nIndex]->m_nAuthID);
		ReportLog(pDocEx->pChildDoc[m_nIndex], pTask, RET_REQU_SIGNIN, "终端机签到", "终端机签到--设置消费开关失败!");
		pDocEx->pChildDoc[pDocEx->nPortNo]->m_nSignIn = RET_REQU_SIGNIN ;
		return RET_REQU_SIGNIN;
	}

	//if( SignIn && pDocEx->pChildDoc[pDocEx->nPortNo]->m_nSignIn != 1)
	//	SignIn(pDocEx->pChildDoc[pDocEx->nPortNo]);

	pDocEx->pChildDoc[pDocEx->nPortNo]->m_nSignIn = 1 ;
	GetCurDateTime(pDocEx->pChildDoc[pDocEx->nPortNo]->m_szSignInTime);
	printf("-----%.8X签到成功!\n",pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
	ReportLog(pDocEx->pChildDoc[m_nIndex], pTask, RET_OK, "终端机签到", "终端机签到成功!");
	Sleep(500);

	return RET_OK;
}

void CSingInServer::OnPacketError(long nResult)
{
	unsigned char BlackVersion[6];
	unsigned char Hex[64];

	memset(Hex, 0, sizeof(Hex));
	SVC_DSP_2_HEX((BYTE*)m_strBlackVer.GetBuffer(0), Hex, 6);

	for(int i=0; i<3; i++)
	{
		MakeBuf_GetBlackVersion(&m_pDocEx->pChildDoc[m_nIndex]->DeviceInfo, m_pBuffer);
		if(SendRequest(m_pDocEx->pChildDoc[m_nIndex], m_pBuffer) == RET_OK )
		{
			if(UnMakeDeviceBuffer(m_pBuffer) == RET_OK)
			{
				memset(BlackVersion, m_pBuffer->pBuffer[4],6);
			
				if( !memcmp(Hex, BlackVersion, 6) )
				{
					break;
				}
				else
				{
					ReportLog(m_pDoc, m_pTask, RET_SYSERROR, "终端机签到", "签到时黑名单版本不一致!");
					break;
				}
			}
		}
	}
}


//签到时处理请求
long CSingInServer::SignInProcess(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long nPort, TSSmartTask *pTask)
{
	long  nAuthID = 0 ;
	
	int n = pDocEx->nPortNo ;
	
	TSDeviceInfo  DevInfo;
	ZeroMemory(&DevInfo, sizeof(DevInfo));


	if( pDocEx->nChildDoc > 1 )
	{
	
		for(int i=1; i< pDocEx->nChildDoc; i++)
		{
		
			if( pDocEx->pChildDoc[i]->m_nParentID > 0 && 
				pDocEx->pChildDoc[i]->m_nSMTPort == nPort && 
				(pDocEx->pChildDoc[i]->m_nStatus == 0 || pDocEx->pChildDoc[i]->m_nStatus == 1) )
			{
				n = i ;
        		memcpy(&DevInfo, &pDocEx->pChildDoc[i]->DeviceInfo, sizeof(DevInfo));
				break;
				
			}
		}
	}
	else
	{
		memcpy(&DevInfo, &pDocEx->pChildDoc[n]->DeviceInfo, sizeof(DevInfo));
		DevInfo.nLevel = 0 ;
		DevInfo.sLevelArray[1] = (unsigned char)nPort;
	}

	CCheckBlackVersion  Check;
	int nTemp = pDocEx->nPortNo ;
	pDocEx->nPortNo = n;
	if( Check.SignInDown(pDocEx->pChildDoc[n], pBuffer) != RET_OK )
	{
		pDocEx->nPortNo  = nTemp ;
		pDocEx->pChildDoc[n]->m_nSignIn = RET_BLACKLIST_ERROR ;
		return RET_BLACKLIST_ERROR;
	}
	
	if( ProcessData(pDocEx, pTask, pBuffer) != RET_OK )
	{
		//printf("签到不成功!\n");
		pDocEx->nPortNo  = nTemp ;
		pDocEx->pChildDoc[n]->m_nSignIn = RET_BLACKLIST_ERROR ;
		return RET_BLACKLIST_ERROR;
	}

	if( SignIn && pDocEx->pChildDoc[n]->m_nSignIn != 1 )
	{
		SignIn(pDocEx->pChildDoc[n]);
	}

	GetCurDateTime(pDocEx->pChildDoc[n]->m_szSignInTime);
	pDocEx->pChildDoc[n]->m_nSignIn = 1 ;
	pDocEx->nPortNo  = nTemp ;

	Sleep(500);

	return RET_OK;
}

////生成签到任务
bool CSingInServer::InsertTask(TSSmartDoc *pDoc)
{
	CSmartTask Task;

	Task.SetTask("终端机签到", "", 0, 1);
	Task.AddAuthID(pDoc->m_nAuthID, "12");

	if( !Task.Write() )
	{
		ReportLog(pDoc, m_pTask, RET_DBEXECERROR, "终端机签到", "新增签到任务失败!");
		return false;
	}
	else
	{
		ReportLog(pDoc, m_pTask, RET_OK, "终端机签到", "新增签到任务成功!");
		return true;
	}
}

bool CSingInServer::GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc)
{
	return true;
}

long CSingInServer::ProcessSingIn(TSDeviceInfo *pDevInfo, TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	bool          bResult = false;
	CTime		  tm;
	int			  E_number;
	unsigned char Clock[7];
	unsigned char Plain[256],ID[4];
	
	E_number = 1;

	//下传时钟
	for(int i=0; i<3; i++)
	{
		tm=CTime::GetCurrentTime();

		Clock[0] = tm.GetYear()-2000;	Clock[1] = tm.GetMonth();	Clock[2] = tm.GetDay();
		Clock[3] = tm.GetHour();	Clock[4] = tm.GetMinute();	Clock[5] = tm.GetSecond();
		Clock[6] = tm.GetDayOfWeek();

		MakeBuf_SetClock(pDevInfo, pBuffer, Clock);
		pBuffer->nTimeOut1 = 300;//1000 ;
		pBuffer->nTimeOut2 = 1000;
		if(SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if(UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2])
			{		
				bResult = true;
				break;
			}
			/*else
			{
				Sleep(200);
			}*/
		}
		else
		{
			Sleep(200);
		}
	}

	if( !bResult )
	{
		printf("终端机签到--校对时钟失败!.\n");
		ReportLog(pDoc, m_pTask, RET_CLOCK_ERROR, "终端机签到", "终端机签到--校对时钟失败!");
		return RET_CLOCK_ERROR;
	}

	char szKeyBuf[256];

	memset(Plain, 0, sizeof(Plain));
	memset(szKeyBuf, 0, sizeof(szKeyBuf));

	GetAuthKey(szKeyBuf);

	SVC_DSP_2_HEX((unsigned char *)szKeyBuf, Plain, strlen(szKeyBuf)/2);
    //trcpy((char*)Plain, "9942CCCF0B333300A5");
	//Sleep(1000);

	//设置授权信息
	bResult = false;
	for(i=0; i<3; i++)
	{
		SVC_DSP_2_HEX((unsigned char *)pDoc->m_szDeviceID, ID, 4);
		//modified by lina 20050308 SmartEncrypt(E_number,ID,Plain); 
		MakeBuf_SetWorkingKey(pDevInfo, pBuffer, Plain, E_number);

		pBuffer->nTimeOut1 = 300 ;
		pBuffer->nTimeOut2 = 1000;
		//bResult = true;//debug 20050311
		if(SendRequest(pDoc, pBuffer) == RET_OK )
		{
			if(UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] )
			{
				bResult = true;
				break;
			}
			/*else
			{
				Sleep(1000);
			}*/
		}
		else
		{
			Sleep(300);
		}
	}

	if( !bResult )
	{
		printf("终端机签到--设置授权信息失败!.\n");
		ReportLog(pDoc, m_pTask, RET_NOT_AUTH, "终端机签到", "终端机签到--设置授权信息失败!");
		return RET_NOT_AUTH;
	}

	//设置消费开关
	bResult = false;
	for(i=0; i<3; i++)
	{
		MakeBuf_SetComsumeFlag(pDevInfo, pBuffer, 1);
		pBuffer->nTimeOut1 = 300;//1000 ;
		pBuffer->nTimeOut2 = 1000;
		if( SendRequest(pDoc, pBuffer) == RET_OK )
		{
			//debug 20050311
		//	ReportLog(pDoc, m_pTask, RET_REQU_SIGNIN, "终端机签到", "RETOK!");

			if( UnMakeDeviceBuffer(pBuffer) == RET_OK&& !pBuffer->pBuffer[2] )
			{
				bResult = true;
				break;
			}
			/*else
			{
				
				Sleep(1000);
			}*/
		}
		else
		{
			//ReportLog(pDoc, m_pTask, RET_REQU_SIGNIN,"终端机签到", "RETOK113!");

			Sleep(200);
		}
	}

	if( !bResult )
	{
		printf("终端机签到失败!\n");
		ReportLog(pDoc, m_pTask, RET_REQU_SIGNIN, "终端机签到", "终端机签到--设置消费开关失败!");
		return RET_REQU_SIGNIN;
	}

	if( SignIn && pDoc->m_nSignIn != 1 )
	{
		SignIn(pDoc);
	}

	pDoc->m_nSignIn = 1 ;
	GetCurDateTime(pDoc->m_szSignInTime);

	ReportLog(pDoc, m_pTask, RET_OK, "终端机签到", "");

	return RET_OK;
}

bool CSingInServer::GetAuthKey(char *pszString)
{
	TSSystemParam  Parameter;

	ZeroMemory(&Parameter, sizeof(Parameter));
	if( GetParameter(0, &Parameter) == RET_OK )
	{
		strcpy(pszString, Parameter.szParameter2);
	}
	else
		strcpy(pszString, "9942CCCF0B333300A5");

	return true;
}
