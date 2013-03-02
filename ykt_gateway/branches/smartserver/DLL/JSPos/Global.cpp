
#include "stdafx.h"
#include "global.h"

#pragma comment(lib, "SmartTerminal.lib")
#pragma comment(lib, "Smart_userdes.lib")

//////////////////////////////////////////////////////////////////////////////////////////
//////////////定义服务提供的API接口.....开始
//////////////////////////////////////////////////////////////////////////////////////////
lpfnGetDBHandle	            GetDBHandle = NULL ;
lpfnFreeDBHandle            FreeDBHandle = NULL ;
lpfnExecuteQuery			ExecuteQuery = NULL ;
lpfnCloseRecHandle			CloseRecHandle = NULL ;
lpfnIsOpen					IsOpen = NULL ;
lpfnIsBOF					IsBOF = NULL ;
lpfnIsEOF					IsEOF = NULL ;
lpfnMoveFirst				MoveFirst = NULL ;
lpfnMoveLast				MoveLast = NULL ;
lpfnMoveNext				MoveNext = NULL ;
lpfnMovePrev				MovePrev = NULL ;
lpfnGetFieldCount			GetFieldCount = NULL ;
lpfnGetRecordCount			GetRecordCount = NULL ;
lpfnGetFieldName			GetFieldName = NULL ;
lpfnGetFieldStringValue		GetFieldStringValue = NULL ;
lpfnGetFieldStringValueEx	GetFieldStringValueEx = NULL ;
lpfnGetFieldLongValue		GetFieldLongValue = NULL ;
lpfnGetFieldLongValueEx		GetFieldLongValueEx = NULL ;
lpfnGetFieldFloatValue		GetFieldFloatValue = NULL ;
lpfnGetFieldFloatValueEx	GetFieldFloatValueEx = NULL ;
lpfnGetFieldDoubleValue		GetFieldDoubleValue = NULL ;
lpfnGetFieldDoubleValueEx	GetFieldDoubleValueEx = NULL ;
lpfnLocate					Locate = NULL ;
lpfnExecuteSQL				ExecuteSQL = NULL ;
lpfnSendRequest             SendRequest = NULL ;
lpfnBroadData               BroadData = NULL ;
lpfnAddNewSmartDoc          AddNewSmartDoc = NULL ;
lpfnDelSmartDoc             DelSmartDoc = NULL ;
lpfnBroadMessage            BroadMessage = NULL ;
lpfnBroadcastPro			BroadcastPro = NULL;
lpfnSendData				SendDataEx = NULL;
lpfnRecvData				RecvDataEx = NULL;
lpfnOutputRealData			OutputRealData = NULL;
lpfnGetParam				GetParameter = NULL;
lpfnReportTaskResult		ReportTaskResult = NULL;
//////////////////////////////////////////////////////////////////////////////////////////
//////////////定义服务提供的API接口..... 结束
//////////////////////////////////////////////////////////////////////////////////////////

unsigned int m_crctab[256]=
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

static TSResultMsg  ResultMsg[] = 
{
     RET_DATAVALUE_ERROR    ,"数据长度参数值太大或等于负值,",
     RET_RECV_ERROR         ,"接收数据错（链路没有打开即通讯）",
     RET_SEND_ERROR         ,"发送数据错（链路没有打开即通讯）",
     RET_RECV_TIMEOUT       ,"接收数据超时;",
     RET_ADDR_ERROR         ,"返回地址不匹配",
     RET_TERME_NOANSWER     ,"终端无反应",
     RET_COMMONU_ERROR      ,"串口打开/关闭错",
     RET_DATALENGTH_ERROR   ,"返回数据长度错误",
     RET_DATACRC_ERROR      ,"数据校验错",
     RET_PARAMETER_ERROR1   ,"传入参数错",
     RET_RECV_C1_TIMEOUT    ,"C1 Timeout",
     RET_RECV_C2_TIMEOUT    ,"C2 Timeout",
     RET_OK                 ,"成功",
     RET_NG                 ,"失败/错误/没有数据",
     RET_TIMEOUT            ,"超时",
     RET_TERMINATE          ,"中断操作",
     RET_SYSERROR           ,"系统错误",
     RET_DBBUSY             ,"数据库资源分配完",
     RET_DBQUERYERROR       ,"数据库查询错误",
     RET_DBEXECERROR        ,"数据库DDL错误",
     RET_NOTSUPPORT         ,"不支持的硬件类型",
     RET_VALIDPACKET        ,"非法的数据包",
     RET_VALIDMARK          ,"MARK值错",
     RET_VALIDMACNO         ,"机号错",
	 RET_TASKWHERE_ERROR    ,"设备条件不满足", 
     RET_CARD_INVALID       ,"1:非法卡",
     RET_CLOCK_ERROR        ,"2:时钟错",
     RET_MONEY_FORMAT_ERROR ,"3:钱包格式错",
     RET_DATA_FULL          ,"4:数据满",
     RET_SEQNUM_ERROR       ,"5:流水号错",
     RET_PARAMETER_ERROR2   ,"7:传入参数错",
     RET_COMMAND_ERROR      ,"8:无此命令或命令无法此时使用",
     RET_REMARK_ERROR       ,"9:重复打标记",
     RET_NO_RECORD          ,"10:无记录或数据",
     RET_AUTHNO_ERROR       ,"11:授权号不符",
     RET_REQU_SIGNIN        ,"13:申请签到",
     RET_BLACKLIST_ERROR    ,"14:黑名单有效期过期",
     RET_CARD_MONEY_ENOUGH  ,"15:卡内金额不足",
     RET_RECORD_NO_COLLECT  ,"17:还有记录未收集",
     RET_CARD_DEGREE_ERROR  ,"18:卡使用次数超限",
     RET_CARD_EXPECT_ERROR  ,"19:卡片已过有效期",
     RET_CARD_MONEY_LARGE   ,"20:卡片金额太大",
     RET_CARD_SEQOVER       ,"22:已结帐的交易流水已被覆盖(无法复核)",
     RET_ACCREC_NOTUP       ,"23:还有结账记录未上传",
     RET_NOT_AUTH           ,"24:设备未授权无法签到",
     RET_CONTINUE           ,"没有第一个请求包, 继续执行",
     RET_BROADCAST          ,"有第一个请求包, 但不要读设备的返回信息",
     RET_ERRORCALL          ,"对设备操作失败后, 仍调用业务层处理", 
};

TCHAR szErrorLogPath[MAX_PATH];
TCHAR szDataLogPath[MAX_PATH];
TCHAR szOperPath[MAX_PATH];

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

int GetBinaryValue(char *pszString)
{
	char  szNew[256];
	int nValue = 0 ;
	int nLen = strlen(pszString);

	memset(szNew, 0, sizeof(szNew));
	for(int i=nLen-1; i>=0; i--)
		szNew[nLen-i-1] = pszString[i];

	for(i=0; i<nLen; i++)
	{
		if( szNew[i] != '0' )
			nValue = nValue + (int)pow(2, nLen-1-i);
	}

	return nValue;
}

//*=================================================================================
//*原型: void GetResultMessage(long nRet, char *pszString)
//*功能: 得到返回值的信息
//*参数: 略
//*返回: 无
//*说明: 全局函数. (采用顺序查找,效率非常低. 以后有时间再优化.)
//*=================================================================================
void GetResultMessage(long nRet, char *pszString)
{
	for(long i=0; i< sizeof(ResultMsg)/sizeof(TSResultMsg); i++)
	{
		if( ResultMsg[i].nResult == nRet )
		{
			strcpy(pszString, ResultMsg[i].pszMessage);
			return;
		}
	}

	strcpy(pszString, "未知的错误消息代码!");
}

void ReportLog(long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	
	wsprintf(szFileName, "%s\\%s.log", szTemp, "ERROR");

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szLog[4096];
		if( nRet == RET_OK )
		{
			wsprintf(szLog, "%02d:%02d:%02d [任务<%s>] [执行结果(%d):成功!] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, pszString);
		}
		else
		{
			TCHAR  szTemp[256];

			memset(szTemp, 0, sizeof(szTemp));
			GetResultMessage(nRet, szTemp);

			wsprintf(szLog, "%02d:%02d:%02d [任务<%s>] [执行结果(%d):失败! 出错信息:%s] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, szTemp, pszString);
		}

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);

		//BroadMessage(szLog, lstrlen(szLog));
	}
}


//*=================================================================================
//*原型: void DebugPrint(const char *format, ...)
//*功能: 打印调试信息
//*参数: 
//*      format, 格式串信息
//*返回: 
//*      无
//*====================================================================================
void DebugPrint(const char *format, ...)
{
	TCHAR sBuffer[256];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	FILE *fp = NULL ;
	if( (fp=fopen(DEBUG_LOG, "a+")) != NULL )
	{
		TCHAR  szLog[512];
		SYSTEMTIME  SysTime;

		GetLocalTime(&SysTime);

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d:%06d %s\n", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			SysTime.wMilliseconds, sBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

//*=============================================================================================
//*原型: void ReportLog(TSSmartDocEx *pDocEx, const char *format, ...)
//*功能: 日志信息保存
//*参数: 
//*      pDoc  -- 设备信息
//*      pTask -- 设备任务
//*      
//*返回: 
//*      无
//*=============================================================================================
void ReportLog(TSSmartDoc *pDoc, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;
	TCHAR  szLog[4096];

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szOperPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	wsprintf(szFileName, "%s\\%s.log", 
		szTemp, pDoc->m_szDeviceID);

	if( nRet == RET_OK )
	{
		wsprintf(szLog, "%02d:%02d:%02d [设备ID<%s> 通讯地址<%s> 端口号<%d> 任务<%s>] [执行结果(%d):成功!] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc->m_szDeviceID, pDoc->m_szAddr, pDoc->m_nSMTPort, pszTask, nRet, pszString);
	}
	else
	{
		TCHAR  szTemp[256];

		memset(szTemp, 0, sizeof(szTemp));
		GetResultMessage(nRet, szTemp);

		wsprintf(szLog, "%02d:%02d:%02d [设备ID<%s> 通讯地址<%s> 端口号<%d> 任务<%s>] [执行结果(%d):失败! 出错信息:%s] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc->m_szDeviceID, pDoc->m_szAddr, pDoc->m_nSMTPort, pszTask, nRet, szTemp, pszString);
	}

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

void ReportLog(TSSmartDocEx *pDocEx, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, nRet, pszTask, pszString);
}

void WriteLogEx(TSSmartDocEx *pDocEx, const char *format, ...)
{
	TCHAR sBuffer[384];
	va_list ptr;
	TCHAR  szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szOperPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	
	wsprintf(szFileName, "%s\\%s.log",szTemp,pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID);

	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szLog[512];

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d:%06d %s\n", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			SysTime.wMilliseconds, sBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);

		//BroadMessage(szLog, lstrlen(szLog));
	}
}

//*=================================================================================
//*原型: void WriteLog(const char *format, ...)
//*功能: 写系统日志
//*参数: 
//*      format, 格式串信息
//*返回: 
//*      无
//*====================================================================================
void WriteLog(const char *format, ...)
{
	TCHAR sBuffer[256];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(sBuffer, format, ptr);
	va_end(ptr);

	FILE *fp = NULL ;
	if( (fp=fopen("App.log", "a+")) != NULL )
	{
		TCHAR  szLog[512];
		SYSTEMTIME  SysTime;

		GetLocalTime(&SysTime);

		wsprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d:%06d %s\n", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			SysTime.wMilliseconds, sBuffer);

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);

		//BroadMessage(szLog, lstrlen(szLog));
	}
}

void GetCurDateTime(char *pszDateTime)
{
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);

	sprintf(pszDateTime, "%04d-%02d-%02d %02d:%02d:%02d", 
		SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
}


void m_crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}

int m_calc_crc16(unsigned char len,unsigned char *in,unsigned char *out)
{
	unsigned char i;
	unsigned short crc;	
	int stat;
	stat=0;
	crc=0xc78c;
	for(i=0;i<len;in++,i++)
	{
		m_crcupdata(*in,&crc,m_crctab);
	}	
    out[0]=(unsigned char)(crc>>8);
	out[1]=(unsigned char)crc;
//	if(crc)
		stat=1;
	return(stat);
}

/***************************************************************************
  SUPPOSE dsp CONTAINS THE ASSCII ARRAY "12345F" AND WE EXECUTE THIS FUNCTION
  THEN THE ARRAY  AT hex WILL CONTAIN 12H,34H, 5FH
     	ASC->Hex
****************************************************************************/
void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
		hex[i]=hex[i]<<4;
		hex[i]+=(((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10)&0x0f);
	}
}

void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count)
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

void SmartEncrypt(unsigned char E_number,unsigned char *ID,unsigned char *Plain)
{
	
}

byte* DoubleStrToHex(unsigned char *str,unsigned char *hex)
{
	int  nCount=0;
	int  i=0;
	byte sHex[512];
	char sBuf[10];

	memset(sHex,0,sizeof sHex);
	memset(sBuf,0,sizeof sBuf);

	nCount=strlen((char*)str)/2;
	for( i=0; i<nCount;i++)
	{
		memset(sBuf,0,sizeof sBuf);
		sBuf[0]=str[2*i];
		sBuf[1]=str[2*i+1];
		sHex[i]=(byte)atol(sBuf);
	}
	memcpy(hex,sHex,nCount);
	return hex;
}


byte* SetClassToHex(unsigned char *str,unsigned char *hex)
{
	int  nCount=0;
	int  i=0;
	byte sHex[512],sTemp[512];
	char sBuf[100],sstr[256];
	
	memset(sHex, 0,sizeof sHex);
	memset(sBuf, 0,sizeof sBuf);
	memset(sTemp,0,sizeof sTemp);
	memset(sstr, '0',sizeof sstr);
	
	nCount=strlen((char*)str);
	memcpy(sHex,str,nCount);
	
	for( i=0;i<nCount; i++ )
	{
		if( sHex[i]=='0' )
		{
			strcat((char*)sTemp,"0000");
		}
		else if( sHex[i]=='1' )
		{
			strcat((char*)sTemp,"0001");
		}
		else if( sHex[i]=='2' )
		{
			strcat((char*)sTemp,"0010");
		}
		else if( sHex[i]=='3' )
		{
			strcat((char*)sTemp,"0011");
		}
		else if( sHex[i]=='4' )
		{
			strcat((char*)sTemp,"0100");
		}
		else if( sHex[i]=='5' )
		{
			strcat((char*)sTemp,"0101");
		}
		else if( sHex[i]=='6' )
		{
			strcat((char*)sTemp,"0110");
		}
		else if( sHex[i]=='7' )
		{
			strcat((char*)sTemp,"0111");
		}
		else if( sHex[i]=='8' )
		{
			strcat((char*)sTemp,"1000");
		}
		else if( sHex[i]=='9' )
		{
			strcat((char*)sTemp,"1001");
		}
		else if( sHex[i]=='A'||sHex[i]=='a' )
		{
			strcat((char*)sTemp,"1010");
		}
		else if( sHex[i]=='B'||sHex[i]=='b' )
		{
			strcat((char*)sTemp,"1011");
		}
		else if( sHex[i]=='C'||sHex[i]=='c' )
		{
			strcat((char*)sTemp,"1100");
		}
		else if( sHex[i]=='D'||sHex[i]=='d' )
		{
			strcat((char*)sTemp,"1101");
		}
		else if( sHex[i]=='E'||sHex[i]=='e' )
		{
			strcat((char*)sTemp,"1110");
		}
		else if( sHex[i]=='F'||sHex[i]=='f' )
		{
			strcat((char*)sTemp,"1111");
		}
	}
	memcpy(sTemp+strlen((char*)sTemp),sstr,256-strlen((char*)sTemp));
	memset(sHex,0,sizeof sHex);
	for( i=0; i<256; i++ )
	{
		sHex[255-i]=sTemp[i];
	}
	memset(sTemp,0,sizeof sTemp);	
	int nHex1=0,nHex2=0;
	for( i=0; i<32; i++ )
	{
		memset(sBuf,0,sizeof sBuf);	
		nHex1=(sHex[8*i+0]-0x30)*8+(sHex[8*i+1]-0x30)*4+(sHex[8*i+2]-0x30)*2+(sHex[8*i+3]-0x30);
		nHex2=(sHex[8*i+4]-0x30)*8+(sHex[8*i+5]-0x30)*4+(sHex[8*i+6]-0x30)*2+(sHex[8*i+7]-0x30);
		sTemp[i]=nHex1*16;
		sTemp[i]+=nHex2;
	}
	memcpy(hex,sTemp,32);
	return hex;
}