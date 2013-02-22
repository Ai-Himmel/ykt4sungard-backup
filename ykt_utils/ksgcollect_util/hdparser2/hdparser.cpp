// hdparser.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../ksgcollect/parsedef.h"
#include <time.h>

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

static int getWordsFromLine(char *line,char words[30][20])
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
				if(i >= 29)
					return 0;
				j = 0;
			}
			break;
		default:
			if(j >= 19)
				return -1;
			words[i][j++] = *pc;
			break;
		}
		pc++;
		
	}
}

char *phdHead = "卡号        余额        交易额      日期       时间      钱包流水号 POS流水号   原POS流水号    操作员号    终端序列号  附加数据  商品编号     钱包索引号 记录类型    消费模式";

HDPARSER_API int parse_head(char *head)
{	
	if (strncmp(head,phdHead,strlen(phdHead)) != 0)
		return -1;
	return 0;
}

static int do_parse_date_time(const char *input_date,const char *input_time,char output_date[9],char output_time[7])
{
	_tzset();
	char temp[5] = "";
	struct tm local_tm;
	time_t curr_time;
	memset(&local_tm,0,sizeof local_tm);
	// 日期
	strncpy(temp,input_date,4);
	local_tm.tm_year = atoi(temp) - 1900;
	memset(temp,0,sizeof temp);
	strncpy(temp,input_date+5,2);
	local_tm.tm_mon = atoi(temp) - 1;
	memset(temp,0,sizeof temp);
	strncpy(temp,input_date+8,2);
	local_tm.tm_mday = atoi(temp);

	// 时间
	memset(temp,0,sizeof temp);
	strncpy(temp,input_time,2);
	local_tm.tm_hour = atoi(temp);
	strncpy(temp,input_time+3,2);
	local_tm.tm_min = atoi(temp);
	strncpy(temp,input_time+6,2);
	local_tm.tm_sec = atoi(temp);

	// 日期格式不合法
	curr_time = mktime(&local_tm);
	if((long)curr_time == -1)
		return -1;

	strftime(output_date,9,"%Y%m%d",&local_tm);
	strftime(output_time,7,"%H%M%S",&local_tm);
	return 0;

}
static int EncodeHDPhyId(const char* text,char * encodeId)
{
	int i = 0;
	int j = 0;
	char temp[3] = "";
	strncpy(encodeId,text,4);
	strncpy(temp,text+4,2);
	i = atoi(temp);
	if(i < 0 || i >15)
		return -1;
	strncpy(temp,text+6,2);
	j = atoi(temp);
	if(j < 0 || j > 15)
		return -1;
	sprintf(encodeId+4,"%x%x",i,j);
	strncat(encodeId+6,text+8,2);
	encodeId[9] = '\0';
	return 0;

}

static int do_get_mange_fee(const char *value)
{
	int i;
	short ret;
	i = atoi(value);
	ret = -(short)i;					//修改搭伙费为正值
	return ret;
}

HDPARSER_API int parse_line(char *line,TRADE_SERIAL &tradeSerial)
{
	char serialArr[30][20];
	int trade_type;
	char tx_date[9] = "";

	memset(serialArr,0,sizeof(serialArr));
	
	getWordsFromLine(line,serialArr);
	/*
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
	*/
	tradeSerial.card_no = atoi(serialArr[0]); // 卡号
	if(tradeSerial.card_no <= 0)
	{
		// 无效记录
		return -1;
	}
	tradeSerial.out_balance = atoi(serialArr[1]); // 余额
	tradeSerial.trade_fee = atoi(serialArr[2]); // 交易金额
	if(do_parse_date_time(serialArr[3],serialArr[4],tx_date,tradeSerial.tx_time))
	{
		// 日期格式无效
		return -1;
	}
	memcpy(tradeSerial.tx_date,tx_date+2,6);
	tradeSerial.trade_count = atoi(serialArr[5]); // 交易次数
	if(tradeSerial.trade_count <= 0) // 无效记录
		return -1;

	tradeSerial.serial_no = atoi(serialArr[6]); //流水号
	// 设备物理ID
	EncodeHDPhyId(serialArr[9],tradeSerial.device_id);
	// 
	tradeSerial.manage_fee = do_get_mange_fee(serialArr[10]); // 管理费
	if(tradeSerial.manage_fee != 0)
		printf("manage_fee[%d]\n",tradeSerial.manage_fee);
	trade_type = atoi(serialArr[13]);
	if((trade_type & 0x0F) == 0x01 ) // 消费
	{
		tradeSerial.trade_fee = -tradeSerial.trade_fee;
		tradeSerial.in_balance = tradeSerial.out_balance + tradeSerial.trade_fee;
		tradeSerial.tx_mark = 153;
	}
	else if((trade_type & 0x0F) == 0x02) // 撤消
	{
		tradeSerial.trade_fee = -tradeSerial.trade_fee;
		tradeSerial.in_balance = tradeSerial.out_balance + tradeSerial.trade_fee;
		tradeSerial.tx_mark = 254;
	}
	else
		return -1; // 不是消费流水,也不是撤消
	
	trade_type &= 0xF0;
	if((trade_type & 0x40) == 0)
	{
		// 黑卡交易
		tradeSerial.tx_mark = 0;
	}
	else if((trade_type & 0x20) != 0)
	{
		// 中途拨卡记录
		tradeSerial.tx_mark = 2;
	}
	return 0;
}