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
			return 0;		// �ɹ�����һ��
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

char *phdHead = "����        ���        ���׶�      ����       ʱ��      Ǯ����ˮ�� POS��ˮ��   ԭPOS��ˮ��    ����Ա��    �ն����к�  ��������  ��Ʒ���     Ǯ�������� ��¼����    ����ģʽ";

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
	// ����
	strncpy(temp,input_date,4);
	local_tm.tm_year = atoi(temp) - 1900;
	memset(temp,0,sizeof temp);
	strncpy(temp,input_date+5,2);
	local_tm.tm_mon = atoi(temp) - 1;
	memset(temp,0,sizeof temp);
	strncpy(temp,input_date+8,2);
	local_tm.tm_mday = atoi(temp);

	// ʱ��
	memset(temp,0,sizeof temp);
	strncpy(temp,input_time,2);
	local_tm.tm_hour = atoi(temp);
	strncpy(temp,input_time+3,2);
	local_tm.tm_min = atoi(temp);
	strncpy(temp,input_time+6,2);
	local_tm.tm_sec = atoi(temp);

	// ���ڸ�ʽ���Ϸ�
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
	ret = -(short)i;					//�޸Ĵ���Ϊ��ֵ
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
	if(stricmp(serialArr[2],"�ۿ�") == 0)
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
	tradeSerial.card_no = atoi(serialArr[0]); // ����
	if(tradeSerial.card_no <= 0)
	{
		// ��Ч��¼
		return -1;
	}
	tradeSerial.out_balance = atoi(serialArr[1]); // ���
	tradeSerial.trade_fee = atoi(serialArr[2]); // ���׽��
	if(do_parse_date_time(serialArr[3],serialArr[4],tx_date,tradeSerial.tx_time))
	{
		// ���ڸ�ʽ��Ч
		return -1;
	}
	memcpy(tradeSerial.tx_date,tx_date+2,6);
	tradeSerial.trade_count = atoi(serialArr[5]); // ���״���
	if(tradeSerial.trade_count <= 0) // ��Ч��¼
		return -1;

	tradeSerial.serial_no = atoi(serialArr[6]); //��ˮ��
	// �豸����ID
	EncodeHDPhyId(serialArr[9],tradeSerial.device_id);
	// 
	tradeSerial.manage_fee = do_get_mange_fee(serialArr[10]); // �����
	if(tradeSerial.manage_fee != 0)
		printf("manage_fee[%d]\n",tradeSerial.manage_fee);
	trade_type = atoi(serialArr[13]);
	if((trade_type & 0x0F) == 0x01 ) // ����
	{
		tradeSerial.trade_fee = -tradeSerial.trade_fee;
		tradeSerial.in_balance = tradeSerial.out_balance + tradeSerial.trade_fee;
		tradeSerial.tx_mark = 153;
	}
	else if((trade_type & 0x0F) == 0x02) // ����
	{
		tradeSerial.trade_fee = -tradeSerial.trade_fee;
		tradeSerial.in_balance = tradeSerial.out_balance + tradeSerial.trade_fee;
		tradeSerial.tx_mark = 254;
	}
	else
		return -1; // ����������ˮ,Ҳ���ǳ���
	
	trade_type &= 0xF0;
	if((trade_type & 0x40) == 0)
	{
		// �ڿ�����
		tradeSerial.tx_mark = 0;
	}
	else if((trade_type & 0x20) != 0)
	{
		// ��;������¼
		tradeSerial.tx_mark = 2;
	}
	return 0;
}