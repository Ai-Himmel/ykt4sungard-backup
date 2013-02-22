// hdparser.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../ksgcollect/parsedef.h"

#define HDPARSER_API __stdcall

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

char *errLine = "校验失败，记录无效！";
int checkLine(char *line)
{
	if (strcmp(line,errLine) == 0)
		return -1;
	return 0;
}

static int getWordsFromLine(char *line,char words[12][13])
{
	int i = 0 ,j = 0;
	char *pc = line ;
	while (*pc)
	{
		switch(*pc)
		{
		case '\r':
			break;
		case '\n':
			return 0;		// 成功解析一行
		case '\t':
		case ' ':
			if (*(pc+1) != ' ' && *(pc+1) != '\t')
			{
				i++;
				j = 0;
			}
			break;
		default:
			words[i][j++] = *pc;
			break;
		}
		pc++;
		
	}
}

char *phdHead = "设备号	流水号	交易类型	卡号	入卡值	交易额	出卡值	计数器	交易时间	管理费	标志";

HDPARSER_API int parse_head(char *head)
{	
	if (strncmp(head,phdHead,strlen(phdHead)) != 0)
		return -1;
	return 0;
}


HDPARSER_API int parse_line(char *line,TRADE_SERIAL &tradeSerial)
{
	char serialArr[12][13];
	memset(serialArr,0,sizeof(serialArr));
	
	if(checkLine(line))
		return -1;

	getWordsFromLine(line,serialArr);
	
	strcpy(tradeSerial.device_id,serialArr[0]);
	tradeSerial.serial_no = atoi(serialArr[1]);
	if(stricmp(serialArr[2],"扣款") == 0)
		tradeSerial.serial_type = COSUMER_TYPE;
	else 
		tradeSerial.serial_type = DEPOSIT_TYPE;
	tradeSerial.card_no = atoi(serialArr[3]);
	tradeSerial.in_balance = atoi(serialArr[4]);
	tradeSerial.trade_fee = atoi(serialArr[5]);
	tradeSerial.out_balance = atoi(serialArr[6]);
	tradeSerial.trade_count = atoi(serialArr[7]);
	strcpy(tradeSerial.tx_date,serialArr[8]);
	strcpy(tradeSerial.tx_time,serialArr[9]);
	tradeSerial.manage_fee = atoi(serialArr[10]);
	tradeSerial.tx_mark = atoi(serialArr[11]);

	return 0;
}