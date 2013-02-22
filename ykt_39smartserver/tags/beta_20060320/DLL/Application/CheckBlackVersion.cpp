// CheckBlackVersion.cpp: implementation of the CCheckBlackVersion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "CheckBlackVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char CCheckBlackVersion::sBlockVersion[32];   //黑名单的最新版本
char CCheckBlackVersion::sBlockExpire[32];    //黑名单有效期
int  CCheckBlackVersion::nBlackExpire;
int  CCheckBlackVersion::nBlackCount = 0 ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckBlackVersion::CCheckBlackVersion()
{

}

CCheckBlackVersion::~CCheckBlackVersion()
{

}

bool bReadParam = false;

long CCheckBlackVersion::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}


long CCheckBlackVersion::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long	card=0,nTry=0;
	int		flag=0;
	BYTE CardNo[20],Ver[20],Exp[20],buffer[50],*pt=NULL;
	TSResultData  data;
	int iResult=RET_OK;
	ZeroMemory(&data, sizeof(data));
	memset(CardNo, 0x00, sizeof CardNo);
	memset(Ver,    0x00, sizeof Ver   );
	memset(Exp,    0x00, sizeof Exp   );
	memset(buffer, 0x00, sizeof buffer);

	memcpy(buffer,pTask->szMemo,8);
	card=atol((char*)buffer);
	pt=(BYTE*)&card;
	CardNo[0]=*(pt+2);
	CardNo[1]=*(pt+1);
	CardNo[2]=*(pt+0);

	if( pTask->szMemo[45] == '1' ) //下传黑名单
	{
		SVC_DSP_2_HEX((unsigned char *)pTask->szMemo+8,Ver,6); //版本
		SVC_DSP_2_HEX((unsigned char *)pTask->szMemo+20,Exp,6); //有效期
		MakeBuf_DownBlackCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, CardNo);
		for( nTry=0; nTry<3; nTry++)
		{
			if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
			{
				if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				{
					WriteLog("下传黑名单成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, card);										
					ReportLog(pDocEx, pTask, RET_OK, "下传黑名单成功!", "");
					GetResultMessage(RET_OK, data.sMsg);
					ReportTaskResult(pTask, RET_OK, &data);
					flag = 1;
					Sleep(200);
					break;
				}
			}
		}	
		if( !flag )
		{
			GetResultMessage(iResult, data.sMsg);
			ReportTaskResult(pTask, iResult, &data);
			return iResult;
		}

		//更改版本号
		MakeBuf_SetBlackVersion(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, Ver);
		pBuffer->nTimeOut1 = 1000;
		pBuffer->nTimeOut2 = 1000;
		for( nTry=0; nTry<3; nTry++)
		{
			if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
			{
				if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				{
					WriteLog("更改黑名单版本号成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, card);																
					ReportLog(pDocEx, pTask, RET_OK, "下传黑名单成功!", "");
					GetResultMessage(RET_OK, data.sMsg);
					ReportTaskResult(pTask, RET_OK, &data);
					return RET_OK;
				}
			}
		}	
	}
	else if( pTask->szMemo[45] == '2' ) //删除黑名单
	{
		SVC_DSP_2_HEX((unsigned char *)pTask->szMemo+8,Ver,6); //版本
		MakeBuf_DelOneBlackCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, CardNo);
		for( nTry=0; nTry<3; nTry++)
		{
			if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
			{
				if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				{
					WriteLog("删除黑名单成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, card);																
					ReportLog(pDocEx, pTask, RET_OK, "删除黑名单成功!", "");
					GetResultMessage(RET_OK, data.sMsg);
					ReportTaskResult(pTask, RET_OK, &data);
					flag = 1;
					Sleep(200);
					break;
				}
			}
		}	
		if( !flag )
		{
			GetResultMessage(iResult, data.sMsg);
			ReportTaskResult(pTask, iResult, &data);
			return iResult;
		}

		//更改版本号
		MakeBuf_SetBlackVersion(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, Ver);
		pBuffer->nTimeOut1 = 1000;
		pBuffer->nTimeOut2 = 1000;
		for( nTry=0; nTry<3; nTry++)
		{
			if( SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) == RET_OK )
			{
				if( UnMakeDeviceBufferEx(pBuffer) == RET_OK )
				{
					WriteLog("更改黑名单版本号成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, card);																
					ReportLog(pDocEx, pTask, RET_OK, "更改删除黑名单版本成功!", "");
					GetResultMessage(RET_OK, data.sMsg);
					ReportTaskResult(pTask, RET_OK, &data);
					return RET_OK;
				}
			}
		}	
	}
	else if( pTask->szMemo[45] == '3' ) //广播黑名单
	{
		BYTE Buf[128];
		memset(Buf, 0x00, sizeof Buf );
		SVC_DSP_2_HEX((unsigned char *)pTask->szMemo+8,Ver,6); //版本
		pBuffer->nCmdSize=MakeBuf_BoardBlackNo(Buf,Ver,CardNo);
		memcpy(pBuffer->pBuffer,Buf,pBuffer->nCmdSize);
		pBuffer->nTimeOut1=1000;
		pBuffer->nTimeOut2=1000;
		for( nTry=0; nTry<3; nTry++)
		{
			if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
			{
				if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				{
					WriteLog("广播黑名单成功: 设备:%s, 卡号:%d.............................", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, card);																
					ReportLog(pDocEx, pTask, RET_OK, "广播黑名单成功!", "");
					GetResultMessage(RET_OK, data.sMsg);
					ReportTaskResult(pTask, RET_OK, &data);
					return RET_OK;
				}
			}
		}
	}
	ReportLog(pDocEx, pTask, iResult, "黑名单操作失败........................", "");
	GetResultMessage(iResult, data.sMsg);
	ReportTaskResult(pTask, iResult, &data);
	return RET_OK;
}

long CCheckBlackVersion::ProcessCheck(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	if(pTask==NULL)
		return -1;
	if(pDocEx==NULL)
		return -1;
	if(pBuffer==NULL)
		return -1;
	int n = pDocEx->nPortNo ;
	int nDatabase = 0 ;

	GetParam(nDatabase);
	long nResult = CheckBlackExpire(nDatabase, pDocEx, pBuffer, n);
	ReportLog(pDocEx, pTask, nResult, "黑名单有校期校对", "");

	return nResult;
}

long CCheckBlackVersion::GetParam(long nDatabase)
{
	memset(sBlockVersion, 0, sizeof(sBlockVersion));
	memset(sBlockExpire, 0, sizeof(sBlockExpire));

	TSSystemParam Parameter;
	if( GetParameter(0, &Parameter) == RET_OK )
	{
		nBlackExpire = Parameter.nParameter4;
		strcpy(sBlockExpire, Parameter.szParameter4);
		strcpy(sBlockVersion, Parameter.szParameter3);
	}
	else
	{
		nBlackExpire = -1;
		strcpy(sBlockExpire, "990101010101");
		GetNowTime(sBlockVersion, false);
	}
	return RET_OK;
}

//下载黑名单
long CCheckBlackVersion::DownCardID(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int n, long nRec, char* strLastVer, long& nCardID)
{
	return RET_OK;
}

//校对黑名单的有效期
long CCheckBlackVersion::CheckBlackExpire(long nDatabase, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long n)
{
	if(pDocEx==NULL)
	{
		return -1;
	}
	if(pBuffer==NULL)
	{
		return -1;
	}

	char  sNow[24];
	char  sTemp[32];
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	char *pExpire = pDoc->m_sBlackExpire;

	GetNowTime(sNow, false);

	if( strcmp(pExpire, sNow) > 0 ) 
	{
		return RET_OK;
	}

	memset(sTemp, 0, sizeof(sTemp));

	if( nBlackExpire == -1 )
	{
		strcpy(sTemp, sBlockExpire);
	}
	else
	{
		 strcpy(sTemp, sBlockExpire);
	}

	char sTmp[3];
	char sBuffer[32];

	memset(sBuffer, 0, sizeof(sBuffer));

	for(int i=0; i<6; i++)
	{
		memset(sTmp, 0, sizeof(sTmp));

		sTmp[0] = sTemp[i*2];
		sTmp[1] = sTemp[i*2+1]; 
		sBuffer[i] = atoi(sTmp);
	}

	bool bResult = false;

	for(i=0; i<3; i++)
	{
		MakeBuf_SetBlackUsefulLife(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, (unsigned char*)sBuffer);
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBufferEx(pBuffer) == RET_OK )
			{
				bResult = true;
				break;
			}
		}
	}

	if( !bResult )
	{
		return RET_SYSERROR;
	}
	return RET_OK;
}

unsigned char CCheckBlackVersion::GetInt(unsigned char *pszString, int Len)
{
   char  sBuffer[8];

   memset(sBuffer, 0, sizeof(sBuffer));
   for(int i=0; i<Len&&i<8; i++)
   {
	   sBuffer[i] = pszString[i];
   }

   return (unsigned char)atoi(sBuffer);
}

//操作是否成功
long CCheckBlackVersion::UnMakeDeviceBufferEx(TSCmdBuffer *pBuffer)
{
	long nResult = UnMakeDeviceBuffer(pBuffer);
	if( nResult == RET_OK )
	{
		int nMark = pBuffer->pBuffer[2];
		if( nMark != 0x00 )
			nResult = nMark; 
		else
			nResult = RET_OK;
	}
	return nResult;
}


CString CCheckBlackVersion::GetSmartCardSQL(CString strDate1, CString strDate2)
{
	CString strSQL;
	return strSQL;
}

void CCheckBlackVersion::GetNowTime(char *pszDateTime, bool bBool)
{
	SYSTEMTIME   SysTime;

	ZeroMemory(&SysTime, sizeof(SysTime));
	GetLocalTime(&SysTime);

	if( !bBool )
	{
		sprintf(pszDateTime, "%02d%02d%02d%02d%02d%02d",
				SysTime.wYear, SysTime.wMonth, SysTime.wDay,
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	}
	else
	{
		sprintf(pszDateTime, "%02d%02d%02d", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
	}

	return ;
}

long CCheckBlackVersion::OpenQuery(long nDatabase, CString strSQL)
{
	return 0;
}


long CCheckBlackVersion::SignInDown(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	int		totalblack=1,ret=0;
	if(pDoc==NULL)		return -1;
	if(pBuffer==NULL)	return -1;

	//Lport之类的设备没有黑名单, 不下传
	if( !strcmp(pDoc->m_szMacCode, "5301") || !strcmp(pDoc->m_szMacCode, "0420") || 
		!strcmp(pDoc->m_szMacCode, "0228") || !strcmp(pDoc->m_szMacCode, "1053") || 
		pDoc->m_nStatus == 9 )
	{
		return RET_OK;
	}

	TSSystemParam Parameter;
	TSResultData  data;
	int iResult;
	ZeroMemory(&data, sizeof(data));
	memset(&Parameter, 0, sizeof(Parameter));

	GetParameter(0, &Parameter);
	printf("----比较金仕达传递参数----\n");
    printf("===================终端设备黑名单版本%c%c%c%c%c%c%c%c%c%c%c%c\n",	
															pDoc->m_sDownBlackTime[0],
															pDoc->m_sDownBlackTime[1],
															pDoc->m_sDownBlackTime[2],
															pDoc->m_sDownBlackTime[3],
															pDoc->m_sDownBlackTime[4],
															pDoc->m_sDownBlackTime[5],
															pDoc->m_sDownBlackTime[6],
															pDoc->m_sDownBlackTime[7],
															pDoc->m_sDownBlackTime[8],
															pDoc->m_sDownBlackTime[9],
															pDoc->m_sDownBlackTime[10],															
															pDoc->m_sDownBlackTime[11]);

	printf("系统黑名单版本c%c%c%c%c%c%c%c%c%c%c%c\n",	Parameter.szParameter3[0],
														Parameter.szParameter3[1],
														Parameter.szParameter3[2],
														Parameter.szParameter3[3],
														Parameter.szParameter3[4],
														Parameter.szParameter3[5],
														Parameter.szParameter3[6],
														Parameter.szParameter3[7],
														Parameter.szParameter3[8],
														Parameter.szParameter3[9],
														Parameter.szParameter3[10],
														Parameter.szParameter3[11]);
 	
	SYSTEMTIME   SysTime;
	char  szFileName[256];
	int	  flag =0;
	TSBlackCard  CardResult;

	memset(&CardResult,0x00, sizeof(CardResult));
	ZeroMemory(&SysTime, sizeof(SysTime));

	strcpy(CardResult.sVersion,"000000000000");
	GetLocalTime(&SysTime);
	sprintf(szFileName, "%s\\%s.blk",
		szTempPath, pDoc->m_szDeviceID);
	
	if( (ret=DownloadBlackCard(pDoc, 0, szFileName)) != RET_OK )
	{
		OutputBlackCard(pDoc, ret, &CardResult);
		Sleep(200);
		printf("从金仕达下载批量黑名单失败.................................\n");
		return ret;
	}
	Sleep(500);

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "rb")) == NULL )
	{
		Sleep(200);
		printf("打开下载后的批量黑名单文件失败.................................\n");
		return RET_OK;
	}

	//得到所有传入的黑名单
	TSBlackCard  Card[80];
	int  nCount = 0 ;
	int  k = 0 ;
	bool bEnd = false; 

	ZeroMemory(&Card, sizeof(Card));
	flag = 0;
	while( !feof(fp) )
	{
		if( fread(&Card[k], sizeof(TSBlackCard), 1, fp) <= 0 )
		{
			bEnd = true;
			if( k > 0 ) k -= 1;
		}
		if( bEnd || k >= 50 )
		{
			unsigned char szBuffer[256];
			int nCardID = 0 ;
			char  szVersion[24];
			char  szExpire[24];

			memset(szBuffer, 0, sizeof(szBuffer));
			memset(szVersion, 0, sizeof(szVersion));
			memset(szExpire, 0, sizeof(szExpire));

			//下传黑名单
			for(int i=0; i<= k; i++)
			{
				nCardID = Card[i].nCardID ;
				szBuffer[i*3]   = (nCardID/256/256)%256;
				szBuffer[i*3+1] = (nCardID/256)%256;
				szBuffer[i*3+2] = nCardID%256;
				strcpy(szVersion, Card[i].sVersion);
				strcpy(szExpire, Card[i].sValid);
			}
			
			for( i=0;i<=k;i++)
			{	
				//表示一条黑名单都没有，直接返回成功
				if( Card[i].nCardID<=0 && k<=0 )
				{					
					OutputBlackCard(pDoc, RET_OK, &CardResult);	
					fclose(fp);
					Sleep(200);
					return RET_OK;					
				}
				//如果版本号为空或卡号为0,则不需要下载
				if( !strlen(Card[i].sVersion)||Card[i].nCardID<=0)
				{
					continue;
				}
				//解挂卡
				if( Card[i].nFlag == 1 )  MakeBuf_DelOneBlackCardNo(&pDoc->DeviceInfo, pBuffer, &szBuffer[i*3]);
				else 					  MakeBuf_DownBlackCardNo(&pDoc->DeviceInfo, pBuffer, &szBuffer[i*3]);				
				pBuffer->nTimeOut1 = 1000;
				pBuffer->nTimeOut2 = 1000;
				 iResult = RET_OK ;
				for( int j=0; j<3; j++ )
				{
					if( (iResult=SendRequest(pDoc, pBuffer)) == RET_OK )
					{
						iResult = UnMakeDeviceBufferEx(pBuffer);
						if( iResult == RET_OK )
						{
							BYTE Ver[7];
							memset(Ver, 0x00, sizeof Ver );
							SVC_DSP_2_HEX((BYTE*)Card[i].sVersion,Ver,6);
							//只有前面的下载和修改黑名单版本都成功，则才改版本号，否则只下载黑名单，不改版本
							if( flag == 0 )
							{
								//修改版本号
								for( int kl=0; kl<3; kl++ )
								{		
									iResult = MakeBuf_SetBlackVersion(&pDoc->DeviceInfo,pBuffer,Ver );
									if( (iResult=SendRequest(pDoc, pBuffer)) == RET_OK )
									{
										iResult = UnMakeDeviceBufferEx(pBuffer);
										if( iResult == RET_OK )
										{		
											CardResult.nCardID=Card[i].nCardID;
											CardResult.nFlag=Card[i].nFlag;
											strcpy((char*)CardResult.sValid,(char*)Card[i].sValid);
											strcpy((char*)CardResult.sVersion,(char*)Card[i].sVersion);																					
											if( Card[i].nFlag == 1 )
											{
												printf("第 %ld 条,下传解挂卡号为[ %ld ],版本为[%s],机器ID[%s] 成功........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->m_szDeviceID);
											}
											else
											{
												printf("第 %ld 条,下传黑名卡号为[ %ld ],版本为[%s],机器ID[%s] 成功........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->m_szDeviceID);
											}
											//每50条记录给金仕回版本号且前面的下载均要成功，否则下面的不改版本号
											if( (totalblack%50==0) && (flag==0) ) 
											{											
												OutputBlackCard(pDoc, RET_OK, &CardResult);
											}
											break;
										}				
									}
								}
							}
							if( iResult !=RET_OK) flag = 1;
							if( flag == 1 )
							{
								if( Card[i].nFlag == 1 )
								{
									printf("第 %ld 条,下传解挂卡号为[ %ld ],版本为[%s],机器ID[%s] 成功[版本未改]........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->m_szDeviceID);
								}
								else
								{
									printf("第 %ld 条,下传黑名卡号为[ %ld ],版本为[%s],机器ID[%s] 成功[版本未改]........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->m_szDeviceID);
								}
							}						
							break;
						}
					}
					else
					{
						Sleep(500);
					}
				}
			}
			if( iResult != RET_OK )
			{
				OutputBlackCard(pDoc, RET_SYSERROR, &CardResult);
				fclose(fp);
				return iResult;
			}
			k = 0 ;
			ZeroMemory(&Card, sizeof(Card));
		}
		k++;
		if( bEnd ) break;
	}

	fclose(fp);
	printf("\n.............黑名单卡及解挂卡已经全部下载成功.................!!!!\n\n");
	OutputBlackCard(pDoc, RET_OK, &CardResult);	
	Sleep(200);
	return RET_OK;
}


long CCheckBlackVersion::ProcessDataJSB(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	BYTE  CardNo[6],*pt=NULL;
	BYTE  date1[20];
	BYTE  date2[20];	
	char  tmp[10];
	int	  count=0,flag=0,nTry=0;	
	long  iResult=0;
	TSResultData  data;
	unsigned long  cardno=0;

	memset(date2,  0x00, sizeof date2 );	
	memset(CardNo, 0x00, sizeof CardNo);
	memset(&data,  0x00, sizeof(TSResultData));
	memset(date1,  0x00, sizeof date1 );
	memset(tmp,    0x00, sizeof tmp   );

	TSAttachData *pHead = (TSAttachData*)pTask->pData ;
	count = pHead->nCount;  //条数
	flag  = pHead->nValue;  //标识
	memcpy(tmp,  pHead->szValue, 7);
	memcpy(date1,&pHead->szValue[50],12);
	cardno = atol(tmp);
	pt = (BYTE*)&cardno;
	CardNo[0]= *(pt+2);
	CardNo[1]= *(pt+1);
	CardNo[2]= *(pt+0);	
	
	if( flag == 0 ) //下传一条白名单
	{		
		iResult =MakeBuf_DownWhiteCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer,10,(BYTE*)CardNo);	
	}
	else if( flag == 1 ) //删除一条白名单
	{
		iResult =MakeBuf_DelWhiteCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, CardNo);	
	}
	else if( flag == 2 ) //删除所有白名单
	{
		iResult =MakeBuf_DelAllWhiteCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer);
	}
	pBuffer->nTimeOut1 = 1000;
	pBuffer->nTimeOut2 = 1000;
	
	//连续2次
	for( nTry=0; nTry<2; nTry++)
	{
		if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
		{
			if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
			{
				WriteLog("下传/删除/删除所有白名单成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, cardno);																
				ReportLog(pDocEx, pTask, RET_OK, "下传/删除白名单成功!", "");				
				Sleep(500);
				break;
			}
		}
		else
		{
			Sleep(500);
		}
	}	

	//1.若是删除所有白名单,直接返回,不需要更改版本
	//2.若是操作白名单不成功时,也直接返回不需要再改版本
	if( (iResult !=RET_OK) || (flag == 2) )	
	{
		GetResultMessage(iResult, data.sMsg);								
		ReportTaskResult(pTask, iResult, &data);
		return iResult;
	}

	//更改版本		
	SVC_DSP_2_HEX((BYTE*)date1,date2,6);	
	MakeBuf_SetWhiteVersion(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer,date2);
	pBuffer->nTimeOut1 = 1000;
	pBuffer->nTimeOut2 = 1000;
	
	//连续2次
	for( nTry=0; nTry<2; nTry++)
	{
		if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
		{			
			if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
			{
				WriteLog("更改下传/删除白名单版本成功: 设备:%s, 卡号:%d......", pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID, cardno);
				ReportLog(pDocEx, pTask, RET_OK, "更改下传/删除白名单版本成功!", "");
				GetResultMessage(RET_OK, data.sMsg);								
				ReportTaskResult(pTask, iResult, &data);
				return iResult;
			}
		}
		else
		{
			Sleep(500);
		}		
	}		
	ReportLog(pDocEx, pTask, iResult, "更改下传/删除白名单版本失败........................", "");
	GetResultMessage(iResult, data.sMsg);
	ReportTaskResult(pTask, iResult, &data);	
	return RET_OK;
}


//获取计时宝批量下传白名单的任务
//如果获取成功,则主动向金仕达要需要下载的白名单及版本
//如果不成功,则直接返回失败.
long CCheckBlackVersion::ProcessDataJSBTask(TSSmartDocEx *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	long iResult=RET_OK;

	//向金仕达回复该任务已经收到
	memset(&data, 0x00, sizeof(data));	
	if(pDoc->pChildDoc[pDoc->nPortNo]==NULL)
	{
		iResult=RET_PARAMETER_ERROR1;
		ReportLog(pDoc, pTask, iResult, "接收下传批量白名单任务失败", "");
		GetResultMessage(iResult, data.sMsg);
		ReportTaskResult(pTask, iResult, &data);	
		return RET_OK;		
	}		
	else
	{
		//回930201的任务
		iResult=RET_OK;
		ReportLog(pDoc, pTask, iResult, "接收下传批量白名单任务成功", "");
		GetResultMessage(iResult, data.sMsg);
		ReportTaskResult(pTask, iResult, &data);	
		Sleep(100);	
	}

	/*========开始主动向金仕达要计时宝白名单=========*/
	printf("三九前置开始向金仕达要[ 设备:%s ]计时宝白名单\n",pDoc->pChildDoc[pDoc->nPortNo]->m_szDeviceID);

	int	  totalblack=1;	
	char  szFileName[256],m_szDeviceID[15];
	int	  flag =0;
	TSBlackCard  CardResult;
	SYSTEMTIME   SysTime;
	
	memset(m_szDeviceID, 0x00, sizeof m_szDeviceID);
	memset(&CardResult,  0x00, sizeof(CardResult));
	memset(&SysTime,     0x00, sizeof(SysTime));
	
	strcpy(CardResult.sVersion,"000000000000");
	GetLocalTime(&SysTime);

	//由于设备ID是唯一的,为了不产生太多的文件占用空间,决定一个设备不管在任何时间只产生一个文件
	//故去掉文件名后的日期时间
	sprintf(szFileName, "%s\\%s.jsb",szTempPath, pTask->szMemo);	
	//值3不能改变,否则影响接收白名单
	if( (iResult=DownloadBlackCard(pDoc->pChildDoc[pDoc->nPortNo], 3, szFileName)) != RET_OK )
	{
		OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], iResult, &CardResult);
		Sleep(200);
		return iResult;
	}	
	//由于文件大时,下面立即打开文件,经常返回失败,故延时一下.
	Sleep(500);

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "rb")) == NULL )
	{
		printf("打开已经下载成功的白名单文件失败..........\n");
		return RET_OK;
	}

	//得到所有传入的白名单
	TSBlackCard  Card[80];
	int  nCount = 0 ;
	int  k      = 0 ;
	bool bEnd = false; 

	ZeroMemory(&Card, sizeof(Card));
	flag = 0;
	while( !feof(fp) )
	{
		if( fread(&Card[k], sizeof(TSBlackCard), 1, fp) <= 0 )
		{
			bEnd = true;
			if( k > 0 ) k -= 1;
		}
		if( bEnd || k >= 50 )
		{
			unsigned char szBuffer[256];
			int   nCardID = 0 ;
			char  szVersion[24];
			char  szExpire[24];

			memset(szBuffer,  0, sizeof(szBuffer));
			memset(szVersion, 0, sizeof(szVersion));
			memset(szExpire,  0, sizeof(szExpire));

			//下传白名单
			for(int i=0; i<= k; i++)
			{
				nCardID = Card[i].nCardID ;
				szBuffer[i*3]   = (nCardID/256/256)%256;
				szBuffer[i*3+1] = (nCardID/256)%256;
				szBuffer[i*3+2] = nCardID%256;
				strcpy(szVersion, Card[i].sVersion);
				strcpy(szExpire, Card[i].sValid);
			}
			
			for( i=0;i<=k;i++)
			{	
				//表示一条计时宝白名单都没有，直接返回成功
				if( Card[i].nCardID<=0 && k<=0 )
				{					
					OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], RET_OK, &CardResult);	
					fclose(fp);
					Sleep(200);
					return RET_OK;					
				}
				//如果版本号为空或卡号为0,则不需要下载
				if( !strlen(Card[i].sVersion)||Card[i].nCardID<=0)
				{
					continue;
				}
				//解挂卡				
				if( Card[i].nFlag == 1 )  MakeBuf_DelWhiteCardNo(&pDoc->pChildDoc[pDoc->nPortNo]->DeviceInfo, pBuffer, &szBuffer[i*3]);				    
				else 					  MakeBuf_DownWhiteCardNo(&pDoc->pChildDoc[pDoc->nPortNo]->DeviceInfo, pBuffer,10,&szBuffer[i*3]);									
				pBuffer->nTimeOut1 = 1000;
				pBuffer->nTimeOut2 = 1000;
				iResult = RET_OK ;
				for( int j=0; j<3; j++ )
				{
					if( (iResult=SendRequest(pDoc->pChildDoc[pDoc->nPortNo], pBuffer)) == RET_OK )
					{
						iResult = UnMakeDeviceBufferEx(pBuffer);
						if( iResult == RET_OK )
						{
							BYTE Ver[7];
							memset(Ver, 0x00, sizeof Ver );
							SVC_DSP_2_HEX((BYTE*)Card[i].sVersion,Ver,6);
							//只有前面的下载和修改黑名单版本都成功，则才改版本号，否则只能下载黑名单，不改版本
							if( flag == 0 )
							{
								//修改版本号
								for( int kl=0; kl<3; kl++ )
								{		
									iResult = MakeBuf_SetWhiteVersion(&pDoc->pChildDoc[pDoc->nPortNo]->DeviceInfo,pBuffer,Ver );									
									if( (iResult=SendRequest(pDoc->pChildDoc[pDoc->nPortNo], pBuffer)) == RET_OK )
									{
										iResult = UnMakeDeviceBufferEx(pBuffer);
										if( iResult == RET_OK )
										{		
											CardResult.nCardID=Card[i].nCardID;
											CardResult.nFlag=Card[i].nFlag;
											strcpy((char*)CardResult.sValid,(char*)Card[i].sValid);
											strcpy((char*)CardResult.sVersion,(char*)Card[i].sVersion);																					
											if( Card[i].nFlag == 1 )
											{
												printf("第 %ld 条,下传删除白名单卡号为[ %ld ],版本为[%s],机器ID[%s] 成功........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->pChildDoc[pDoc->nPortNo]->m_szDeviceID);
											}
											else
											{
												printf("第 %ld 条,下传白名单卡号为[ %ld ],版本为[%s],机器ID[%s] 成功........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->pChildDoc[pDoc->nPortNo]->m_szDeviceID);
											}
											//每50条记录给金仕回版本号且前面的下载均要成功，否则下面的不改版本号
											if( (totalblack%50==0) && (flag==0) ) 
											{											
												OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], RET_OK, &CardResult);
											}
											break;
										}				
									}
								}
							}
							if( iResult !=RET_OK) flag = 1;
							if( flag == 1 )
							{
								if( Card[i].nFlag == 1 )
								{
									printf("第 %ld 条,下传删除白名单卡号为[ %ld ],版本为[%s],机器ID[%s] 成功[版本未改]........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->pChildDoc[pDoc->nPortNo]->m_szDeviceID);
								}
								else
								{
									printf("第 %ld 条,下传白名单卡号为[ %ld ],版本为[%s],机器ID[%s] 成功[版本未改]........\n",totalblack++,Card[i].nCardID,Card[i].sVersion,pDoc->pChildDoc[pDoc->nPortNo]->m_szDeviceID);
								}
							}						
							break;
						}
					}
					else
					{
						Sleep(500);
					}
				}
			}
			if( iResult != RET_OK )
			{
				OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], iResult, &CardResult);
				fclose(fp);
				return iResult;
			}
			k = 0 ;
			ZeroMemory(&Card, sizeof(Card));
		}
		k++;
		if( bEnd ) break;
	}
	fclose(fp);
	printf("\n.............计时宝下传/删除白名单卡已经全部完成.................!!!!\n\n");
	OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], RET_OK, &CardResult);	
	Sleep(200);
	return RET_OK;	
}

//心跳
long CCheckBlackVersion::ProcessDataTick(TSSmartDocEx *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long iResult=RET_OK;
	int	 i=0;
	TSBlackCard  CardResult;
	BYTE m_clock[29],m_ver[29];	
	
	memset(m_clock,0x00, sizeof m_clock);
	memset(m_ver,  0x00, sizeof m_ver  );
	memset(&CardResult, 0x00, sizeof(CardResult));	

	memcpy(CardResult.sValid,"930057",6);
	pDoc->pChildDoc[pDoc->nPortNo]->m_nStatus=0x01;	

	if(pDoc->pChildDoc[pDoc->nPortNo]==NULL)
	{		
		OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], RET_AUTHNO_ERROR, &CardResult);
		ReportLog(pDoc, pTask, iResult, "终端心跳监控取参数---->终端设备为空,该终端无法监控", "");
		WriteLog("终端心跳监控取参数---->终端设备为空,该终端无法监控");
		return RET_OK;		
	}		

	//时钟	
	iResult=MakeBuf_GetClock(&pDoc->pChildDoc[pDoc->nPortNo]->DeviceInfo, pBuffer); 
	pBuffer->nTimeOut1	=1000;
	pBuffer->nTimeOut2	=1000;	
	for( i=0; i<2; i++)
	{	
		if( (iResult=SendRequest(pDoc->pChildDoc[pDoc->nPortNo], pBuffer)) == RET_OK )
		{
			iResult = UnMakeDeviceBufferEx(pBuffer);
			if( iResult == RET_OK )
			{
				m_clock[0]='2';
				m_clock[1]='0';
				sprintf((char*)m_clock+2,"%02ld%02ld%02ld%02ld%02ld%02ld",				
							(unsigned char*)pBuffer->pBuffer[4],
							(unsigned char*)pBuffer->pBuffer[5],
							(unsigned char*)pBuffer->pBuffer[6],
							(unsigned char*)pBuffer->pBuffer[7],
							(unsigned char*)pBuffer->pBuffer[8],
							(unsigned char*)pBuffer->pBuffer[9]);

				pDoc->pChildDoc[pDoc->nPortNo]->m_nStatus=0x00;
				//ReportLog(pDoc, pTask, iResult, "终端心跳监控取参数---->取时钟成功", (char*)m_clock);
				break;
			}
			else
			{
				//0--正常,  1 -- 网络不通或终端无反应
				pDoc->pChildDoc[pDoc->nPortNo]->m_nStatus=0x01;
				ReportLog(pDoc, pTask, iResult, "终端心跳监控取参数---->取时钟失败", (char*)m_clock);				
			}
		}
		else
		{
			Sleep(300);
		}
	}
	//WriteLog("终端心跳监控取参数---->取时钟成功[%s]",m_clock);;

	//黑名单版本
	iResult=MakeBuf_GetBlackVersion(&pDoc->pChildDoc[pDoc->nPortNo]->DeviceInfo, pBuffer); 
	pBuffer->nTimeOut1	=1000;
	pBuffer->nTimeOut2	=1000;		
	for( i=0; i<2; i++ )
	{	
		if( (iResult=SendRequest(pDoc->pChildDoc[pDoc->nPortNo], pBuffer)) == RET_OK )
		{
			iResult = UnMakeDeviceBufferEx(pBuffer);
			if( iResult == RET_OK )
			{
				SVC_HEX_2_DSP((unsigned char*)pBuffer->pBuffer+4,m_ver,6);	
				//ReportLog(pDoc, pTask, iResult, "终端心跳监控取参数---->取黑名单版本成功", (char*)m_ver);
				break;
			}
			else
			{
				ReportLog(pDoc, pTask, iResult, "终端心跳监控取参数---->取黑名单版本失败", (char*)m_ver);
			}
		}	
		else
		{
			Sleep(300);
		}
	}

	//WriteLog("终端心跳监控取参数---->取版本成功[%s]",m_ver);
	memcpy(pDoc->pChildDoc[pDoc->nPortNo]->m_szTableName,m_ver,12);
	memcpy(pDoc->pChildDoc[pDoc->nPortNo]->m_sDownBlackTime,m_clock,14);

	OutputBlackCard(pDoc->pChildDoc[pDoc->nPortNo], iResult, &CardResult);			
	WriteLog("终端心跳监控取参数---->心跳取终端黑名单版本[ %s ]和时钟[ %s ].............................\n",m_ver,m_clock);
	ReportLog(pDoc, pTask, iResult, (char*)m_clock, (char*)m_ver);
	return RET_OK;	
}

