#include "StdAfx.h"
#include "ksutil.h"
#include <assert.h>

void HexToAscii(BYTE * hexValue,int len,char * asciiValue)
{
	int i,j;
	assert(hexValue != NULL);
	assert(asciiValue != NULL);
	for(i = 0,j = 0;i < len;i++)
	{
		j += sprintf(asciiValue+j,"%02X",hexValue[i]);
	}
}

double D4U5(double value,int precision)
{
	//四舍五入函数,保留num位小数
	char format_str[20] = "";
	char value_str[40] = "";
	sprintf(format_str, "%%20.%df", precision);
	sprintf(value_str, format_str, value);
	return atof(value_str);
}

void GetCurrentDatetime(char datetime[15])
{
	time_t curr;
	struct tm curr_tm;
	time(&curr);
	curr_tm = *localtime(&curr);
	sprintf(datetime,"%.04d%.02d%.02d%.02d%.02d%.02d",curr_tm.tm_year+1900
		,curr_tm.tm_mon+1,curr_tm.tm_mday,curr_tm.tm_hour
		,curr_tm.tm_min,curr_tm.tm_sec);

}

unsigned long ConvertPhyCardId(const char phyid[9])
{
	char temp[9] = "";
	int i;
	for (i = 0;i < 4;++i)
	{
		memcpy(temp+(3-i)*2,phyid+i*2,2);
	}
	return strtoul(temp,NULL,16);
}