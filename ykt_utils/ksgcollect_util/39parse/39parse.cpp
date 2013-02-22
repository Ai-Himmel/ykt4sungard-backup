// 39parse.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "../ksgcollect/parsedef.h"

#define PARSER_API __stdcall
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

unsigned long convertToint(char *pstr)
{
	int i = 0;
	unsigned long ret = 0;
	int len = strlen(pstr); 
	int c;
	while(i<len -1)
	{
		if (pstr[i] >= 'A' && pstr[i] <= 'F')
			c = pstr[i] - 'A' + 10;
		else if (pstr[i] >= '0' && pstr[i] <= '9')
			c = pstr[i] - '0';
		else
			return -1;

		ret = (ret + c) * 16;
		i++;
	}
	if (pstr[i] >= 'A' && pstr[i] <= 'F')
		c = pstr[i] - 'A' + 10;
	else if (pstr[i] >= '0' && pstr[i] <= '9')
		c = pstr[i] - '0';
	else
		return -1;
	return ret + c;
}


char *phdHead = "三九流水文件";
PARSER_API int parse_head(char *head)
{	
	if (strncmp(head,phdHead,strlen(phdHead)) != 0)
		return -1;
	return 0;
}


PARSER_API int parse_line(char *line,TRADE_SERIAL &tradeSerial)
{
	memset(&tradeSerial,0,sizeof(tradeSerial));
	int i = 0;
	int index = 0;
	char buf[20];
	char *p = line;
	while (*p != '>')
		p++;
	p++;

	//终端号
	while(i<11)
	{
		if(*p != ' ')
			buf[index++] = *p;
		p++;
		i++;
	}
	buf[index] = 0;
	if(strncmp(buf,"FFFFFFFF",8) == 0)  //已经完成
		return 1;

	sprintf(tradeSerial.device_id,"%s",buf);

	i = 0;
	while(i<7)
	{
		p++;
		i++;
	}
	
	i = 0;
	index = 0;
	while(i<5)   //流水号
	{
		if (*p != ' ')
			buf[index++] = *p;
		p++;
		i++;
	}
	buf[index] = 0;
	tradeSerial.serial_no = convertToint(buf);

	p++;
	i = 0;
	index = 0;
	while(i< 8) //卡号
	{
		if (*p != ' ')
			buf[index++] = *p;
		p++;
		i++;
	}
	buf[index]=0;
	tradeSerial.card_no = convertToint(buf);
	
	p++;

	buf[2]=0;
	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_date,"%0.2d",convertToint(buf));  //年

	p++;

	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_date+2,"%0.2d",convertToint(buf)); //月

	p++;

	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_date+4,"%0.2d",convertToint(buf)); //日

	p++;

	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_time,"%0.2d",convertToint(buf));  //时

	p++;

	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_time+2,"%0.2d",convertToint(buf)); //分

	p++;

	buf[0] = *p++;
	buf[1] = *p++;
	sprintf(tradeSerial.tx_time+4,"%0.2d",convertToint(buf)); //秒

	p++;

	i = 0;
	index = 0;
	while(i< 5)  
	{
		if (*p != ' ')
			buf[index++] = *p;
		p++;
		i++;
	}
	buf[index]=0;
	tradeSerial.trade_count = convertToint(buf); //卡流水
	
	p++;
	buf[6] = 0;
	buf[4] = *p++;
	buf[5] = *p++;
	p++;
	buf[2] = *p++;
	buf[3] = *p++;
	p++;
	buf[0] = *p++;
	buf[1] = *p++;
	tradeSerial.in_balance = convertToint(buf); //入卡金额

	p++;
	buf[4] = *p++;
	buf[5] = *p++;
	p++;
	buf[2] = *p++;
	buf[3] = *p++;
	p++;
	buf[0] = *p++;
	buf[1] = *p++;
	tradeSerial.out_balance = convertToint(buf); //出卡金额
	
	tradeSerial.trade_fee = tradeSerial.in_balance - tradeSerial.out_balance; 
	p++;
	buf[2] = 0;
	buf[0] = *p++;
	buf[1] = *p++;
	tradeSerial.tx_mark = convertToint(buf);//交易标志
/*
	char serialArr[12][13];
	memset(serialArr,0,sizeof(serialArr));

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
*/
	return 0;
}
