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

char CCheckBlackVersion::sBlockVersion[32];   //�����������°汾
char CCheckBlackVersion::sBlockExpire[32];    //��������Ч��
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
	int iVer = 0 ;
	int n = pDocEx->nPortNo ;

	//�㲥��������ķ��ش���
	if( strcmp(pTask->szMemo, "")  )
	{
		int iNo = atoi(pTask->szMemo);

		//ɾ��ָ���ĺ�����
		if( iNo < 0 ) 
		{
			bool bResult= false;
			unsigned char buffer[32];

			memset(buffer, 0, sizeof(buffer));
			iNo = 0-iNo;
			buffer[0] = (iNo / 256 /256) % 256 ;
			buffer[1] = (iNo / 256) % 256 ;
			buffer[2] = iNo % 256 ;
			
			for(long k=0; k<pDocEx->nChildDoc; k++)
			{
				printf("------�㲥ɾ��������-----\n");
				TSSmartDoc *pDoc = pDocEx->pChildDoc[k];
				if( !strcmp(pDoc->m_szMacCode, "5301") )
					continue;

				MakeBuf_DelOneBlackCardNo(&pDoc->DeviceInfo, pBuffer, buffer);
				for(long nTry=0; nTry<3; nTry++)
				{
					if( SendRequest(pDoc, pBuffer) == RET_OK )
					{
						if( UnMakeDeviceBufferEx(pBuffer) == RET_OK )
						{
							WriteLog("�㲥ɾ���������ɹ�: �豸:%s, ����:%d......", pDoc->m_szDeviceID, iNo);
							printf("�㲥ɾ���������ɹ�: �豸:%s, ����:%d......\n", pDoc->m_szDeviceID, iNo);
							bResult = true ;
							break;
						}
					}
				}
				
				
			}
			
			ReportLog(pDocEx, pTask, RET_OK, "�㲥ɾ��������", "ɾ���������ɹ�");
		}
		else if( iNo > 0 )
		{
			printf("------�㲥���Ӻ�����------%d\n",iNo);
			unsigned char buffer[8];
			unsigned char version[6];
			bool bResult= false;

			memset(buffer, 0, sizeof(buffer));
			memset(version, 0xFF, sizeof(version));

			buffer[0] =  (iNo / 256 /256) % 256 ;
			buffer[1] =  (iNo / 256) % 256 ;
			buffer[2] =  iNo % 256 ;

		
			TSSmartDoc *pDoc = pDocEx->pChildDoc[0];
			pBuffer->nCmdSize = MakeBuf_BoardBlackNo(pBuffer->pBuffer, (unsigned char*)version, buffer);
			SendRequest(pDoc, pBuffer);
			printf("�㲥���Ӻ������ɹ�: �豸:%s�����е��豸, ����:%d\n", pDoc->m_szDeviceID, iNo);
			ReportLog(pDocEx, pTask, RET_OK, "�㲥������", "");
		}
	}
	//�´�ָ���ĺ�����
	else
	{
		//printf("-----��ʼִ��930003 930004����------!\n ");
		TSSmartDoc *pDoc = pDocEx->pChildDoc[pDocEx->nPortNo];
		//Lport֮����豸û�к�����, ���´�
		if( !strcmp(pDoc->m_szMacCode, "5301") || !strcmp(pDoc->m_szMacCode, "0420") || 
			!strcmp(pDoc->m_szMacCode, "0228") || !strcmp(pDoc->m_szMacCode, "1053") || 
			pDoc->m_nStatus == 9 )
		{
			TSResultData  data;
			ZeroMemory(&data, sizeof(data));

			ReportLog(pDocEx, pTask, RET_TASKWHERE_ERROR, "�´�ָ���ĺ�����", "");
			GetResultMessage(RET_TASKWHERE_ERROR, data.sMsg);
			ReportTaskResult(pTask, RET_TASKWHERE_ERROR, &data);
			return RET_TASKWHERE_ERROR;
		}

		TSAttachData *pHead = (TSAttachData*)pTask->pData;
		TSBlackCard *pArray = (TSBlackCard*)pHead->pData;

		TSSystemParam Parameter;
		TSResultData  data;

		ZeroMemory(&data, sizeof(data));
		//memset(&Parameter, 0, sizeof(Parameter));

		//GetParameter(0, &Parameter);

		//int iResult = strcmp(pDoc->m_sDownBlackTime, Parameter.szParameter3);
		int iResult;
		
		unsigned char szBuffer[256];
		int nCardID = 0 ;
		char  szVersion[24];
		char  szExpire[24];

		memset(szBuffer, 0, sizeof(szBuffer));
		memset(szVersion, 0, sizeof(szVersion));
		memset(szExpire, 0, sizeof(szExpire));

		//�´�������
		for(int i=0; i< pHead->nCount && i < 50 ; i++)
		{
			if(pHead->nValue ==1)
				printf("ɾ��������%d\n",pArray[i].nCardID);
			else
				printf("���Ӻ�����%d\n",pArray[i].nCardID);
			nCardID = pArray[i].nCardID ;


			szBuffer[0] = (nCardID/256/256)%256;
			szBuffer[1] = (nCardID/256)%256;
			szBuffer[2] = nCardID%256;
			strcpy(szVersion, pArray[i].sVersion);
			strcpy(szExpire, pArray[i].sValid);

			WriteLog("�豸:%s�´�����: %d, �汾:%s, ��Ч��:%s.......\n", pDoc->m_szDeviceID,nCardID, szVersion, szExpire);
			if( pHead->nValue == 1 ) 
				MakeBuf_DelOneBlackCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, szBuffer);
			else
				MakeBuf_DownBlackCardNo(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, szBuffer);

			pBuffer->nTimeOut1 = 1000;
			pBuffer->nTimeOut2 = 1000;

			iResult = RET_OK ;

			for(int k=0; k<3; k++)
			{
				if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
				{
					iResult = UnMakeDeviceBufferEx(pBuffer);
					if( iResult == RET_OK )
					{
						break;
					}
				}
				else
				{
					Sleep(300);
				}
			}
		}
		if( iResult != RET_OK )
		{
			delete pHead;
			delete pArray;
			
			ReportLog(pDocEx, pTask, iResult, "�´�ָ���ĺ�����", "");
			GetResultMessage(iResult, data.sMsg);
			ReportTaskResult(pTask, iResult, &data);
			return iResult;
		}
		Sleep(500);

		//�´��������汾��
		if( strcmp(szVersion,"") )
		{
			char sTmp[3];

			memset(szBuffer, 0, sizeof(szBuffer));
			int cccc;
			for(int k=0; k<6; k++)
			{
				sTmp[0] = szVersion[k*2];
				sTmp[1] = szVersion[k*2+1];
				sTmp[2] = '\0';
				cccc = atoi(sTmp);
				szBuffer[k] = (cccc / 10) * 16 + (cccc - (cccc / 10)*10);;
			}
			printf("----�´��������汾%.2X%.2X%.2X%.2X%.2X%.2X-----",szBuffer[0],
					szBuffer[1],szBuffer[2],szBuffer[3],szBuffer[4],szBuffer[5]);
			MakeBuf_SetBlackVersion(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, szBuffer);
			pBuffer->nTimeOut1 = 1000;
			pBuffer->nTimeOut2 = 1000;

			for(int iTick = 0 ; iTick < 3 ; iTick++)
			{
				if( (iResult=SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer)) == RET_OK )
				{
					if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
					{
						break;
					}					
				}
				else
				{
					Sleep(300);
				}
			}

			if( iResult != RET_OK )
			{
				delete pHead;
				delete pArray;
				printf("ʧ��!\n");
				ReportLog(pDocEx, pTask, iResult, "�´��������汾��ʧ��", "");
				GetResultMessage(iResult, data.sMsg);
				ReportTaskResult(pTask, iResult, &data);
				return iResult;
			}
		}
		 
		delete pHead;
		delete pArray;
		ReportLog(pDocEx, pTask, RET_OK, "�´��������ɹ�!", "");
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);
	}

	return RET_OK;
}

long CCheckBlackVersion::ProcessCheck(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	int nDatabase = 0 ;

	GetParam(nDatabase);
	long nResult = CheckBlackExpire(nDatabase, pDocEx, pBuffer, n);
	ReportLog(pDocEx, pTask, nResult, "��������У��У��", "");

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

//���غ�����
long CCheckBlackVersion::DownCardID(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int n, long nRec, char* strLastVer, long& nCardID)
{
	return RET_OK;
}

//У�Ժ���������Ч��
long CCheckBlackVersion::CheckBlackExpire(long nDatabase, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long n)
{
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

//�����Ƿ�ɹ�
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
		sprintf(pszDateTime, "%02d%02d%02d", 
			SysTime.wYear, SysTime.wMonth, SysTime.wDay);
	}

	return ;
}

long CCheckBlackVersion::OpenQuery(long nDatabase, CString strSQL)
{
	return 0;
}

long CCheckBlackVersion::SignInDown(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	//Lport֮����豸û�к�����, ���´�
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
	printf("----�ȽϽ��˴ﴫ�ݲ���----\n");
    printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[0],Parameter.szParameter3[0]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[1],Parameter.szParameter3[1]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[2],Parameter.szParameter3[2]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[3],Parameter.szParameter3[3]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[4],Parameter.szParameter3[4]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[5],Parameter.szParameter3[5]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[6],Parameter.szParameter3[6]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[7],Parameter.szParameter3[7]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[8],Parameter.szParameter3[8]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[9],Parameter.szParameter3[9]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[10],Parameter.szParameter3[10]);
	printf("�ն��豸�������汾%c  ϵͳ�������汾%c\n",pDoc->m_sDownBlackTime[11],Parameter.szParameter3[11]);
 
    /*
	if(pDoc->m_sDownBlackTime[0] < '0' || pDoc->m_sDownBlackTime[0] > '9')
			memcpy(pDoc->m_sDownBlackTime,Parameter.szParameter3,12);
	
	
	//add by lina 20050513
	if( (pDoc->m_sDownBlackTime[0] == Parameter.szParameter3[0]) &&
		(pDoc->m_sDownBlackTime[1] == Parameter.szParameter3[1]) &&
		(pDoc->m_sDownBlackTime[2] == Parameter.szParameter3[2]) &&
		(pDoc->m_sDownBlackTime[3] == Parameter.szParameter3[3]) &&
		(pDoc->m_sDownBlackTime[4] == Parameter.szParameter3[4]) &&
		(pDoc->m_sDownBlackTime[5] == Parameter.szParameter3[5]) 
	)
	{
		
		Sleep(200);
		return RET_OK;
	}

	int iResult = strcmp(pDoc->m_sDownBlackTime, Parameter.szParameter3);
	//������û�仯
	if( iResult >= 0 )
	{
		Sleep(200);
		return RET_OK;
	}
	*/
	//printf("-----�����ն˻�������-----\n");
	SYSTEMTIME   SysTime;
	char  szFileName[256];
	TSBlackCard  CardResult;

	ZeroMemory(&CardResult, sizeof(CardResult));
	ZeroMemory(&SysTime, sizeof(SysTime));

	GetLocalTime(&SysTime);

	sprintf(szFileName, "%s\\%s_%04d%02d%02d%02d%02d%02d.blk",
		szTempPath, pDoc->m_szDeviceID, SysTime.wYear, SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

	if( DownloadBlackCard(pDoc, 0, szFileName) != RET_OK )
	{
		//Sleep(1000);
		//if(DownloadBlackCard(pDoc,0,szFileName) != RET_OK)
		//{
		
			OutputBlackCard(pDoc, RET_SYSERROR, &CardResult);
			Sleep(200);
			return RET_OK;//debug lina 20050311RET_SYSERROR;
		//}
	}

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "r")) == NULL )
	{
		Sleep(200);
		return RET_OK;
	}

	//�õ����д���ĺ�����
	TSBlackCard  Card[80];
	int  nCount = 0 ;
	int  k = 0 ;
	bool bEnd = false; 

	ZeroMemory(&Card, sizeof(Card));

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

			//�´�������
			for(int i=0; i<= k; i++)
			{
				nCardID = Card[i].nCardID ;

				szBuffer[i*3] = (nCardID/256/256)%256;
				szBuffer[i*3+1] = (nCardID/256)%256;
				szBuffer[i*3+2] = nCardID%256;

				strcpy(szVersion, Card[i].sVersion);
				strcpy(szExpire, Card[i].sValid);

				WriteLog("�´�����: %d, �汾:%s, ��Ч��:%s.......\n", nCardID, szVersion, szExpire);
			}
			
			for( i=0;i<=k;i++)
			{
				MakeBuf_DownBlackCardNo(&pDoc->DeviceInfo, pBuffer, &szBuffer[i*3]);

				pBuffer->nTimeOut1 = 1000;
				pBuffer->nTimeOut2 = 1000;
				 iResult = RET_OK ;
				for(int j=0; j<3; j++)
				{
					if( (iResult=SendRequest(pDoc, pBuffer)) == RET_OK )
					{
						iResult = UnMakeDeviceBufferEx(pBuffer);
						if( iResult == RET_OK )
						{
							break;
						}
					}
					else
					{
						Sleep(1000);
					}
				}
			}
			if( iResult != RET_OK )
			{
				OutputBlackCard(pDoc, RET_SYSERROR, &CardResult);
				fclose(fp);
				return iResult;
			}
			/*
            pDoc->m_sDownBlackTime[0] = Parameter.szParameter3[0];
		    pDoc->m_sDownBlackTime[1] = Parameter.szParameter3[1];
		    pDoc->m_sDownBlackTime[2] = Parameter.szParameter3[2];
		    pDoc->m_sDownBlackTime[3] = Parameter.szParameter3[3];
		    pDoc->m_sDownBlackTime[4] = Parameter.szParameter3[4];
		    pDoc->m_sDownBlackTime[5] = Parameter.szParameter3[5];
			pDoc->m_sDownBlackTime[6] = Parameter.szParameter3[6];
		    pDoc->m_sDownBlackTime[7] = Parameter.szParameter3[7];
		    pDoc->m_sDownBlackTime[8] = Parameter.szParameter3[8];
		    pDoc->m_sDownBlackTime[9] = Parameter.szParameter3[9];
		    pDoc->m_sDownBlackTime[10] = Parameter.szParameter3[10];
		    pDoc->m_sDownBlackTime[11] = Parameter.szParameter3[11];
			//�´��������汾��
			if( strcmp(szVersion,"") )
			{
				char sTmp[3];
				int   cccc;
				memset(szBuffer, 0, sizeof(szBuffer));

				for(int j=0; j<6; j++)
				{
					sTmp[0] = szVersion[j*2];
					sTmp[1] = szVersion[j*2+1];
					sTmp[2] = '\0';
					cccc = atoi(sTmp);
					szBuffer[j] = (cccc / 10) * 16 + (cccc - (cccc / 10)*10);
				
					//szBuffer[j] = atoi(sTmp) ;
				}
				printf("----�´��������汾%.2X%.2X%.2X%.2X%.2X%.2X----\n",szBuffer[0],
					szBuffer[1],szBuffer[2],szBuffer[3],szBuffer[4],szBuffer[5]);	
				MakeBuf_SetBlackVersion(&pDoc->DeviceInfo, pBuffer, szBuffer);
				pBuffer->nTimeOut1 = 1000;
				pBuffer->nTimeOut2 = 1000;

				for(int iTick = 0 ; iTick < 3 ; iTick++)
				{
					if( (iResult=SendRequest(pDoc, pBuffer)) == RET_OK )
					{
						if( (iResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
						{
							break;
						}					
					}
					else
					{
						Sleep(1000);
					}	
				}

				if( iResult != RET_OK )
				{
					OutputBlackCard(pDoc, RET_SYSERROR, &CardResult);
					fclose(fp);
					return iResult;
				}
				strcpy(CardResult.sVersion, szVersion);
			}*/

			k = 0 ;
			ZeroMemory(&Card, sizeof(Card));
		}

		k++;
		if( bEnd ) break;
	}

	fclose(fp);
	OutputBlackCard(pDoc, RET_OK, &CardResult);
	Sleep(200);
	return RET_OK;
}

