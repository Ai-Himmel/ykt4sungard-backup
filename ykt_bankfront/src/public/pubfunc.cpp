#define ADDEDSIZE 7
#define BAR '-'
#define COLON ':'

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/types.h>
#include <syslog.h>
#include <signal.h>
#include <assert.h>
#include "pubfunc.h"
#include "d3des.h"
#include "mac.h"
#include "md5.h"

char FileName[256];
int LineNo;

//四舍五入函数,保留num位小数
double D4U5(double value,int num)
{

	int sign=1;
	long long i=0;
	double k=1.0;

	for(i=0;i<num+1;i++)
		k=10.0*k;
	if(value<0)
	{
		sign=-1;
		value=-value;
	}
	value=value*k + 5;
	i=value;
	i -= i % 10;
	value=i/k;
	return value*sign;
	
}
// 将浮点数转换为整型
int D2I(double value)
{
	return (int) D4U5( value,0);
}
//金额比较函数,只比较小数点前2位
int amtcmp(double amt1,double amt2)
{
	long long lAmt1=D4U5(amt1*100,0);
	long long lAmt2=D4U5(amt2*100,0);
	long long lAmt=lAmt1-lAmt2;
	if(0==lAmt)
		return 0;
	else if(lAmt<0)
		return -1;
	else
		return   1;
}

void toupper_word(char word[])
{
	char ch;
	int len = 0;
	int i = 0;

	len = strlen(word);
	for (i = 0; i < len; i++)
	{
		ch = toupper(word[i]);
		word[i] = ch;
	}
}
void tolower_word(char word[])
{
	char ch;
	int len = 0;
	int i = 0;

	len = strlen(word);
	for (i = 0; i < len; i++)
	{
		ch = tolower(word[i]);
		word[i] = ch;
	}
}
char *trim(char *str)
{
	char *p1 = str;
	char *p2;

	if (str == NULL)
		return NULL;
	p2 = str + strlen(str) - 1;
	if(p2<str)
		return str;
	while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
		p1++;
	while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r')
	{
		*p2 = 0;
		p2--;
		if(p2<p1)
			break;
	}
	if(p1!=str)
		strcpy(str, p1);
	return str;
}
char *ltrim(char *str)
{
	char *p1 = str;

	if (str == NULL)
		return NULL;
	while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
		p1++;
	if(p1!=str)
		strcpy(str, p1);
	return str;
}
char *rtrim(char *str)
{
	char *p2;

	if (str == NULL)
		return NULL;
	p2 = str + strlen(str) - 1;
	if(p2<str)
		return str;
	while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r')
	{
		*p2 = 0;
		p2--;
		if(p2<str)
			break;
	}
	return str;
}
//去掉前后空格,并添加结束符,len必须是使用是str的缓冲区长度
char *ntrim(char *str,int len)
{
	char *p1 = str;
	char *p2 = NULL;

	if (str == NULL)
		return NULL;
	p2 = str + len - 1;
	if(p2<str)
		return str;
	*p2=0;
	p2--;
	while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
	{
		p1++;
	}
	while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r')
	{
		*p2 = 0;
		p2--;
		if(p2<p1)
			break;
	}
	if(p1!=str)
		strcpy(str, p1);
	return str;
}

char *getsysdate(char *date)
{
	time_t t;
	struct tm *ptm;
	static char szDate[11] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDate, 9, "%Y%m%d", ptm);
	if (date)
		strcpy(date, szDate);
	return szDate;
}
char *getsystime(char *v_time)
{
	time_t t;
	struct tm *ptm;
	static char szTime[10] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szTime, 7, "%H%M%S", ptm);
	if (v_time)
		strcpy(v_time, szTime);
	return szTime;
}
char *getsysdatetime(char v_datetime[15])
{
	time_t t;
	struct tm *ptm;
	static char szDatetime[16] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDatetime, 15, "%Y%m%d%H%M%S", ptm);
	if (v_datetime)
		strcpy(v_datetime, szDatetime);
	return szDatetime;
}
char *getsystimestamp(char *v_timestamp)
{
	static char szSysTimestamp[28] = "";
	time_t t;
	struct timeval tv;
	struct timezone tz;
	struct tm *ptm;

	char systime[20] = "";

	gettimeofday(&tv, &tz);
	t=tv.tv_sec;
	ptm=localtime(&t);
	strftime(systime,15,"%Y%m%d%H%M%S",ptm);
	sprintf(szSysTimestamp, "%s%06d", systime, tv.tv_usec);
	if (v_timestamp)
		strcpy(v_timestamp, szSysTimestamp);
	return szSysTimestamp;
}

char *getdbdate(char *date)
{
	time_t t;
	struct tm *ptm;
	static char szDate[12] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDate, 11, "%Y-%m-%d", ptm);
	if (date)
		strcpy(date, szDate);
	return szDate;
}
char *getdbtime(char *v_time)
{
	time_t t;
	struct tm *ptm;
	static char szTime[10] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szTime, 9, "%H.%M.%S", ptm);
	if (v_time)
		strcpy(v_time, szTime);
	return szTime;
}
char *getdbtimestamp(char *v_timestamp)
{
	static char szTimestamp[28] = "";
	time_t t;
	struct timeval tv;
	struct timezone tz;
	struct tm *ptm;
	char systime[20] = "";

	gettimeofday(&tv, &tz);
	t=tv.tv_sec;
	ptm=localtime(&t);
	strftime(systime,20,"%Y-%m-%d-%H.%M.%S",ptm);
	sprintf(szTimestamp, "%s.%06d", systime, tv.tv_usec);
	if (v_timestamp)
		strcpy(v_timestamp, szTimestamp);
	return szTimestamp;
}
//函数功能：根据传入时间和秒，得到传入时间之前的时间
//输入：cur_time  char[7] 传入时间格式为：hhmmss
//输入：second    int	   时间间隔		单位为秒
//输出：pre_time  char[7] 距cur_time之后second秒的时间，格式为hhmmss

void getpos(char *v_filename, int v_lineno)
{
	strcpy(FileName, v_filename);
	LineNo = v_lineno;
}
void errlog(int level, char *fmt, ...)
{
	va_list args;
	char msg[4096] = "";
	char head[256] = "";
	char body[3840] = "";

	va_start(args, fmt);
	vsprintf(body, fmt, args);
	va_end(args);

	sprintf(head, "F[%s]L[%d]", FileName, LineNo);
	strcpy(msg, head);
	strcat(msg, body);
	syslog(level, msg);
}

