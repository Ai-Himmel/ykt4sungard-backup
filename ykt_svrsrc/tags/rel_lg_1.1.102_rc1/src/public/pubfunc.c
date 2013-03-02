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
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <syslog.h>
#include <signal.h>
#include <assert.h>
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "d3des.h"
#include "Base64.h"
#include "mac.h"
#include "md5.h"

char FileName[256];
int LineNo;

//�������뺯��,����numλС��
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
// ��������ת��Ϊ����
int D2I(double value)
{
	return (int) D4U5( value,0);
}
//���ȽϺ���,ֻ�Ƚ�С����ǰ2λ
int amtcmp(double amt1,double amt2)
{
	long long lAmt1=D4U5(amt1*100,2);
	long long lAmt2=D4U5(amt2*100,2);
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
//ȥ��ǰ��ո�,����ӽ�����,len������ʹ����str�Ļ���������
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
char *getsysdatetime(char *v_datetime)
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
//�������ܣ����ݴ���ʱ����룬�õ�����ʱ��֮ǰ��ʱ��
//���룺cur_time  char[7] ����ʱ���ʽΪ��hhmmss
//���룺second    int	   ʱ����		��λΪ��
//�����pre_time  char[7] ��cur_time֮ǰsecond���ʱ�䣬��ʽΪhhmmss

int GetPreTime(char *cur_time,int second,char *pre_time)
{
	int i=0;
	int ch=0;
	int iCurHour=0;
	int iCurMin=0;
	int iCurSec=0;
	char tmp[3]="";
	time_t t;
	struct tm *ptm;

	for (i=0;i<6;i++)
	{
		ch=cur_time[i];
		if(!isdigit(ch))
			return E_TIME_FMT;
	}
	time(&t);
	ptm = localtime(&t);
	memcpy(tmp,cur_time,2);
	iCurHour=atoi(tmp);
	memcpy(tmp,cur_time+2,2);
	iCurMin=atoi(tmp);
	memcpy(tmp,cur_time+4,2);
	iCurSec=atoi(tmp);

	ptm->tm_hour=iCurHour;
	ptm->tm_min=iCurMin;
	ptm->tm_sec=iCurSec;

	t=mktime(ptm);
	t-=second;
	ptm = localtime(&t);
	sprintf(pre_time,"%02d%02d%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
	return 0;
}
//�������ܣ����ݴ���ʱ����룬�õ�����ʱ��֮ǰ��ʱ��
//���룺cur_time  char[7] ����ʱ���ʽΪ��hhmmss
//���룺second    int	   ʱ����		��λΪ��
//�����pre_time  char[7] ��cur_time֮��second���ʱ�䣬��ʽΪhhmmss

int GetNextTime(char *cur_time,int second,char *next_time)
{
	int i=0;
	int ch=0;
	int iCurHour=0;
	int iCurMin=0;
	int iCurSec=0;
	char tmp[3]="";
	time_t t;
	struct tm *ptm;

	for (i=0;i<6;i++)
	{
		ch=cur_time[i];
		if(!isdigit(ch))
			return E_TIME_FMT;
	}
	time(&t);
	ptm = localtime(&t);
	memcpy(tmp,cur_time,2);
	iCurHour=atoi(tmp);
	memcpy(tmp,cur_time+2,2);
	iCurMin=atoi(tmp);
	memcpy(tmp,cur_time+4,2);
	iCurSec=atoi(tmp);

	ptm->tm_hour=iCurHour;
	ptm->tm_min=iCurMin;
	ptm->tm_sec=iCurSec;

	t=mktime(ptm);
	t+=second;
	ptm = localtime(&t);
	sprintf(next_time,"%02d%02d%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
	return 0;
}

//�������ܣ�������������ʱ�䣬�õ���������ʱ��֮��ļ��ʱ��
//���룺tim1  char[15] ����ʱ���ʽΪ��yyyymmddhhmmss
//���룺tim2  char[15] ����ʱ���ʽΪ��yyyymmddhhmmss
//�����second   double*	   ʱ����		��λΪ��

int DiffTime(char time1[],char time2[],double* second)
{
	int i=0;
	int iYear=0;
	int iMon=0;
	int iDay=0;
	int iHour=0;
	int iMin=0;
	int iSec=0;
	char tmp[5]="";
	int ch=0;
	time_t t1;
	time_t t2;
	struct tm tm_t;

	memset(&t1,0,sizeof(time_t));
	memset(&t2,0,sizeof(time_t));
	memset(&tm_t,0,sizeof(struct tm));

	for (i=0;i<14;i++)
	{
		ch=time1[i];
		if(!isdigit(ch))
			return E_DATE_FMT;
	}
	for (i=0;i<14;i++)
	{
		ch=time2[i];
		if(!isdigit(ch))
			return E_DATE_FMT;
	}

	memcpy(tmp,time1,4);
	iYear=atoi(tmp);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,time1+4,2);
	iMon=atoi(tmp);
	memcpy(tmp,time1+6,2);
	iDay=atoi(tmp);
	memcpy(tmp,time1+8,2);
	iHour=atoi(tmp);
	memcpy(tmp,time1+10,2);
	iMin=atoi(tmp);
	memcpy(tmp,time1+12,2);
	iSec=atoi(tmp);

	memset(&tm_t,0,sizeof(struct tm));
	tm_t.tm_year=iYear-1900;
	tm_t.tm_mon=iMon-1;
	tm_t.tm_mday=iDay;
	tm_t.tm_hour=iHour;
	tm_t.tm_min=iMin;
	tm_t.tm_sec=iSec;
	t1=mktime(&tm_t);
	memcpy(tmp,time2,4);
	iYear=atoi(tmp);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,time2+4,2);
	iMon=atoi(tmp);
	memcpy(tmp,time2+6,2);
	iDay=atoi(tmp);
	memcpy(tmp,time2+8,2);
	iHour=atoi(tmp);
	memcpy(tmp,time2+10,2);
	iMin=atoi(tmp);
	memcpy(tmp,time2+12,2);
	iSec=atoi(tmp);

	memset(&tm_t,0,sizeof(struct tm));
	tm_t.tm_year=iYear-1900;
	tm_t.tm_mon=iMon-1;
	tm_t.tm_mday=iDay;
	tm_t.tm_hour=iHour;
	tm_t.tm_min=iMin;
	tm_t.tm_sec=iSec;
	t2=mktime(&tm_t);
	*second=difftime(t1,t2);
	return 0;
}
//�����ַ������ڼ���õ�1900��ʼ����
int datetime2second(char *datetime,char *fmt,double *second)
{
	int i=0;
	int iYear=0;
	int iMon=0;
	int iDay=0;
	int iHour=0;
	int iMin=0;
	int iSec=0;
	int ch=0;
	time_t t;
	struct tm tm_t;
	char tmp[5]="";
	char szFmt[100]="";

	strncpy(szFmt, fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);
	if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0)
	{
		for (i=0;i<14;i++)
		{
			ch=datetime[i];
			if(!isdigit(ch))
				return E_DATE_FMT;
		}
		memcpy(tmp,datetime,4);
		iYear=atoi(tmp);
		memset(tmp,0,sizeof(tmp));
		memcpy(tmp,datetime+4,2);
		iMon=atoi(tmp);
		memcpy(tmp,datetime+6,2);
		iDay=atoi(tmp);
		memcpy(tmp,datetime+8,2);
		iHour=atoi(tmp);
		memcpy(tmp,datetime+10,2);
		iMin=atoi(tmp);
		memcpy(tmp,datetime+12,2);
		iSec=atoi(tmp);
	}
	else if (strcmp(szFmt, "YYYYMMDD") == 0)
	{
		for (i=0;i<8;i++)
		{
			ch=datetime[i];
			if(!isdigit(ch))
				return E_DATE_FMT;
		}
		memcpy(tmp,datetime,4);
		iYear=atoi(tmp);
		memset(tmp,0,sizeof(tmp));
		memcpy(tmp,datetime+4,2);
		iMon=atoi(tmp);
		memcpy(tmp,datetime+6,2);
		iDay=atoi(tmp);
		iHour=0;
		iMin=0;
		iSec=0;
	}
	memset(&tm_t,0,sizeof(struct tm));
	tm_t.tm_year=iYear-1900;
	tm_t.tm_mon=iMon-1;
	tm_t.tm_mday=iDay;
	tm_t.tm_hour=iHour;
	tm_t.tm_min=iMin;
	tm_t.tm_sec=iSec;
	t=mktime(&tm_t);
	*second=t;
	return 0;
}
//������õ��ַ�������
int second2datetime(double second,char *datetime,char *fmt)
{
	time_t t;
	struct tm *ptm;
	char szFmt[100]="";

	strncpy(szFmt, fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);

	t=second;
	ptm = localtime(&t);
	if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0)
	{
		strftime(datetime, 15, "%Y%m%d%H%M%S", ptm);
	}
	else	if (strcmp(szFmt, "YYYYMMDD") == 0)
	{
		strftime(datetime, 9, "%Y%m%d", ptm);
	}
	else
		return E_DATE_FMT;
	return 0;
}

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

/*
	����: ѹ���˵������ܼ���:�����ݿ���VarChar(800)���ֶ�ѹ����������CPack��usset3[100]������
	ǰ�᣺���ȴ���ַ�������Ϊ0��1�����
	������CPack�������ַ����鳤��Ϊ100�������ݿ��������ַ�����Ϊ800���ú������Խ�800���ַ�ѹ��Ϊ100����Ҳ���Խ�100���ַ���ѹΪ800��
	����: ���մ�Ǯ�򴦵õ�
	����: int       	0���ɹ��� -1��ʧ��
	����: int nType       	1����ѹ100to800�� 2��ѹ��800to100
	����: char *usset      	����С���ַ�����char usset[nUssetSize]
	����: char *menuset    	���ȴ���ַ�����char menuset[nMenusetSize]
	����: int nUssetSize    usset�ĳ���
	����: int nMenusetSize  menuset�ĳ���
*/
int UssetConvert(int nType,char *usset,char *menuset,int nUssetSize,int nMenusetSize)
{
	int i,j;
	unsigned char nTmpByte;
	switch (nType)
	{
		case 1:
		{
			//convert usset to menuset
			memset(menuset,'0',nMenusetSize);
			j = 0;
			for (i = 0; i< nUssetSize; i++)
			{
				for (nTmpByte = 0x80; nTmpByte != 0 && (j < nMenusetSize); nTmpByte >>=1,j++)
				{
					if (usset[i] & nTmpByte)
					{
						menuset[j] = '1';
					}

				}
			}
			break;
		}
		case 2:
		{
			//convert menuset to usset
			int nOffset,nBit;
			memset(usset,0,nUssetSize);
			for (i = 0; i < nMenusetSize && i/8+1 <= nUssetSize; i++)
			{
				if (menuset[i] != '0')
				{
					nTmpByte = 0x80;
					nOffset = i/8;
					nBit = i%8;
					nTmpByte >>=nBit;
					usset[nOffset] |= nTmpByte;
				}
			}
			break;
		}
		default:
			return -1;
	}

	return 0;
}

//�����ܣ�������yyyymmddhhmmss��ʱ�����ʽΪyyyy-mm-dd hh:mm:ss
//������char *origin:ԭʼ�ַ���
//          char *timestamp:db2��ʽ���ַ���
//���أ��ɹ�Ϊ0

int ConvertDate(char *origin, char *timestamp)
{
	int i, j;

	for (i = 0, j = 0;; i++, j++)
	{
		if (i == 4 || i == 7)
			timestamp[i++] = BAR;

		if (i == 10)
			timestamp[i++] = ' ';

		if (i == 13 || i == 16)
			timestamp[i++] = COLON;
		if (i == 19)
		{
			timestamp[i] = '\0';
			break;
		}
		timestamp[i] = origin[j];
	}

	return 0;
}

//author:xunzhang huang
//date:2004-08-30 17��11
//flag==0 yyyy-mm-dd  -->>  yyyymmdd
//flag==1 yyyymmdd    -->>  yyyy-mm-dd
int ConvertDateLen(char *out, const char *in, int flag)
{
	char *p = in;
	char tmp_out[9] = "";
	char *q = tmp_out;
	if (flag != 0 && flag != 1)
	{
		return -1;
	}
	if (0 == flag)
	{
		if (strlen(in) != 10)
		{
			return -1;
		}

		while (*p != '-')
		{
			*q++ = *p++;
		}
		p++;
		while (*p != '-')
		{
			*q++ = *p++;
		}
		p++;
		while (*p != '\0')
		{
			*q++ = *p++;
		}
		*q = '\0';
		return 0;
	}
	return 0;
}

 /**
	����: ���ܡ�����Ҫ���������
	ǰ�᣺
	����������DES�㷨�������ܡ���������
	����: ��ѫ��
	����: int  0���ɹ��� -1��ʧ��
	����: int flag  	0 : ����,clearpwd->secretpwd;
							1 : ����,secretpwd->clearpwd
	����: char *key,�ַ���,����,Ӧ����ʹ��Ϊ16λ
	����:	char *clearpwd,�ַ���,����,����ǰ������
	������char *secretpwd,�ַ���,����,���ܺ������
*/

int EncodePwd(char *key, char *clearpwd, char *secretpwd, int flag)
{
	int 	i=0;
	char tmp[3] = "";
	unsigned long ul=0;
	unsigned char k[17] = "";
	unsigned char clear[17] = "";
	unsigned char secret[17] = "";
	unsigned char cipher[17] = "";

	memset(tmp,0,sizeof(tmp));
	memset(k,0,sizeof(k));
	memset(clear,0,sizeof(clear));
	memset(secret,0,sizeof(secret));
	memset(cipher,0,sizeof(cipher));
	if (flag == 0)
	{
		strncpy(k, key,8);
		strncpy(clear, clearpwd,8);
		deskey(k, 0);
		Ddes(clear, secret);

		for(i=0;i<8;i++)
		{
			snprintf(&secretpwd[2*i],3,"%02X",secret[i]);
		}
		return 0;
	}
	if (flag == 1)
	{
		strncpy(cipher,secretpwd,16);
		for(i=0;i<8;i++)
		{
			memcpy(tmp,&cipher[2*i],2);
			ul=strtoul(tmp,NULL,16);
			secret[i]=ul;
		}
		strncpy(k, key,8);
		deskey(k, 1);
		Ddes(secret, clear);
		strncpy(clearpwd,clear,8);
		return 0;
	}
	return -1;
}

int GetInitKey(char *s_init_key, char *key)
{
	char k[17] = "";
	char plain[17] = "";

	memset(k,0,sizeof(k));
	memset(plain,0,sizeof(plain));

	strncpy(k, key,8);
	memcpy(plain,getsystimestamp(NULL)+12,8);
	EncodePwd(k, plain, s_init_key, 0);

	return 0;
}
int GetDynaKey(char *Dyna_Key)
{
	char dyna[17] = "";
	char key[9] = "";

	memset(dyna,0,sizeof(dyna));
	memset(key,0,sizeof(key));

	memcpy(key,getsystimestamp(NULL)+12,8);
	EncodePwd(key, key, dyna, 0);
	strcpy(Dyna_Key, dyna);

	return 0;
}

/**
	����: ��鴫�����ĳ�ʼ��Կ�Ƿ���ȷ
	ǰ�᣺��ϵͳ��־��ȡ�ã���ʼ��Կ��ȡ��
	������������key��Ϊ������ʼ��Կʱ������,�ɳ���Աָ��
	����: ��ѫ��
	����: �ɹ�Ϊ0,���ɹ���0
	����:	char *s_init_key,��ʼ��Կ,��ʼ��Կ��Ϊ16λ
	����: int subsystem_id,��ϵͳ��־
	����:	char *key ,��ǰ������
*/
int CheckInitKey(char *s_init_key, int subsystem_id, char *key)
{
	char tmp1[50] = "";
	char k[17] = "";
	char tmp2[50] = "";
	char clear[17] = "";
	char tmp3[50] = "";
	char init[21] = "";
	int length = 0;
	int a;

	tmp1[0] = 'a';
	tmp2[0] = 'a';
	tmp3[0] = 'a';
	strcpy(k, key);				//key Ϊ��Կ���ͼ���ʱ����һ��

	sprintf(clear, "%d", subsystem_id);	//subsystem_id +"aaaaaa..." Ϊ����
	length = strlen(clear);
	for (a = length; a < 16; a++)
	{
		clear[a] = 'a';
	}
	clear[16] = '\0';

	EncodePwd(k, clear, init, 0);	//���±���

	int ret;

	ret = strcmp(init, s_init_key);	//�Ƚϲ����͵õ�����Կ�Ƿ�һ��

	return ret;
}

/**
	����: ������ϵͳ��־���豸��־����������Կ
	ǰ�᣺��ϵͳ��־��ȡ�ã��豸��־��ȡ��
	�����������ɳ���Աָ��,����Ϊ��ϵͳ��־���豸��־��ȡ��ǰ16���ֽ�
	����: ��ѫ��
	����: �ɹ�Ϊ0
	����:	char *read_card_key,��Ž��������Կ,����17���ֽ�
	����: int subsystem_id,��ϵͳ��־
	������int device_id ,�豸��־
	����:	char key ,����,����Աָ��
*/
int GetReadCardKey(int device_id, int subsystem_id, char *read_card_key, char *key)
{
	char tmp1[50] = "";
	char k[17] = "";
	char tmp2[50] = "";
	char clear[17] = "";
	char tmp3[50] = "";
	char init[21] = "";
	char tmp4[50] = "";
	int length = 0;
	int a;

	tmp1[0] = 'a';
	tmp2[0] = 'a';
	tmp3[0] = 'a';
	tmp4[0] = 'a';
	strcpy(k, key);				//key�ɳ���Աȷ��������Ϊ16λ

	sprintf(clear, "%d%d", subsystem_id, device_id);	//subsytem_id + device_id + "aaaa..."��16λΪ����

	length = strlen(clear);
	if (length < 16)
	{
		for (a = length; a < 16; a++)
		{
			clear[a] = 'a';
		}
	}
	clear[16] = '\0';

	EncodePwd(k, clear, init, 0);

	strcpy(read_card_key, init);

	return 0;
}
int IsInvalidDateTime(char *sdatetime,  char *fmt)
{
	int i = 0;
	int data = 0;
	int ch=0;
	char szDatetime[30] = "";
	char szFmt[20] = "";
//	char year[5] = "";
	char mon[3] = "";
	char day[3] = "";
	char hour[3] = "";
	char min[3] = "";
	char sec[3] = "";

	strncpy(szDatetime, sdatetime, sizeof(szDatetime) - 1);
	strncpy(szFmt, fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);
	if (strncmp(szFmt, "YYYYMMDD", 8) == 0)
	{
		for (i = 0; i < 8; i++)
		{
			ch=szDatetime[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "date[%s]", szDatetime);
				return E_DATE_FMT;
			}
		}
//		memcpy(year, szDate, 4);
		memcpy(mon, szDatetime + 4, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
		memcpy(day, szDatetime + 6, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
	}
	else if (strncmp(szFmt, "YYMMDD", 6) == 0)
	{
		for (i = 0; i < 6; i++)
		{
			ch=szDatetime[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "date[%s]", szDatetime);
				return E_DATE_FMT;
			}
		}
		memcpy(mon, szDatetime + 2, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
		memcpy(day, szDatetime + 4, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
	}
	else if(!strncmp(szFmt,"MMDD",4))
	{
		for(i = 0;i < 4;++i)
		{
			ch = szDatetime[i];
			if(!isdigit(ch))
			{
				writelog(LOG_ERR,"date[%s]",szDatetime);
				return E_DATE_FMT;
			}
		}
		memcpy(mon, szDatetime, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
		memcpy(day, szDatetime + 2, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "date[%s]", szDatetime);
			return E_DATE_FMT;
		}
	}
	else	if(strncmp(szFmt, "HHMMSS", 6) == 0)
	{
		for (i = 0; i < 6; i++)
		{
			ch=szDatetime[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "time[%s]", szDatetime);
				return E_TIME_FMT;
			}
		}
		memcpy(hour, szDatetime, 2);
		data = atoi(hour);
		if (data > 23)
		{
			writelog(LOG_ERR, "time[%s]", szDatetime);
			return E_TIME_FMT;
		}
		memcpy(min, szDatetime + 2, 2);
		data = atoi(min);
		if (data > 59)
		{
			writelog(LOG_ERR, "time[%s]", szDatetime);
			return E_TIME_FMT;
		}
		memcpy(sec, szDatetime + 4, 2);
		data = atoi(sec);
		if (data > 59)
		{
			writelog(LOG_ERR, "time[%s]", szDatetime);
			return E_TIME_FMT;
		}
	}

	else
	{
		writelog(LOG_ERR, "datetime[%s]", szDatetime);
		return E_DATE_FMT;
	}
	return 0;
}

int str2dbdate(char *new_date, char *old_date, char *old_fmt)
{
	int i = 0;
	int data = 0;
	int ch=0;
	char szDate[9] = "";
	char szFmt[20] = "";
	char year[5] = "";
	char mon[3] = "";
	char day[3] = "";

	if (!strlen(old_date))
	{
		return 0;
	}
	strncpy(szDate, old_date, sizeof(szDate) - 1);
	strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);
	if (strncmp(szFmt, "YYYYMMDD", 8) == 0)
	{
		for (i = 0; i < 8; i++)
		{
			ch=szDate[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "date[%s]", szDate);
				return E_DATE_FMT;
			}
		}
		memcpy(year, szDate, 4);
		memcpy(mon, szDate + 4, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "date[%s]", szDate);
			return E_DATE_FMT;
		}
		memcpy(day, szDate + 6, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "date[%s]", szDate);
			return E_DATE_FMT;
		}
		sprintf(new_date, "%s-%s-%s", year, mon, day);
	}
	else if (strncmp(szFmt, "YYMMDD", 6) == 0)
	{
		for (i = 0; i < 6; i++)
		{
			ch=szDate[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "date[%s]", szDate);
				return E_DATE_FMT;
			}
		}
		memcpy(year, "20", 2);
		memcpy(year + 2, szDate, 2);
		memcpy(mon, szDate + 2, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "date[%s]", szDate);
			return E_DATE_FMT;
		}
		memcpy(day, szDate + 4, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "date[%s]", szDate);
			return E_DATE_FMT;
		}
		sprintf(new_date, "%s-%s-%s", year, mon, day);
	}
	else
	{
		writelog(LOG_ERR, "date[%s]", szDate);
		return E_DATE_FMT;
	}
	return 0;
}
int str2dbtime(char *new_time, char *old_time, char *old_fmt)
{
	int i = 0;
	int data = 0;
	int ch=0;
	char szTime[7] = "";
	char szFmt[20] = "";
	char hour[3] = "";
	char min[3] = "";
	char sec[3] = "";

	if (!strlen(old_time))
	{
		return 0;
	}
	strncpy(szTime, old_time, sizeof(szTime) - 1);
	strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);
	if (strncmp(szFmt, "HHMMSS", 6) == 0)
	{
		for (i = 0; i < 6; i++)
		{
			ch=szTime[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "time[%s]", szTime);
				return E_TIME_FMT;
			}
		}
		memcpy(hour, szTime, 2);
		data = atoi(hour);
		if (data > 23)
		{
			writelog(LOG_ERR, "time[%s]", szTime);
			return E_TIME_FMT;
		}
		memcpy(min, szTime + 2, 2);
		data = atoi(min);
		if (data > 59)
		{
			writelog(LOG_ERR, "time[%s]", szTime);
			return E_TIME_FMT;
		}
		memcpy(sec, szTime + 4, 2);
		data = atoi(sec);
		if (data > 59)
		{
			writelog(LOG_ERR, "time[%s]", szTime);
			return E_TIME_FMT;
		}
		sprintf(new_time, "%s:%s:%s", hour, min, sec);
	}
	else
	{
		writelog(LOG_ERR, "time[%s]", szTime);
		return E_TIME_FMT;
	}
	return 0;
}
int str2dbtimestamp(char *new_timestamp, char *old_timestamp, char *old_fmt)
{
	int i = 0;
	int data = 0;
	int ch=0;
	char szTimestamp[50] = "";
	char szFmt[20] = "";
	char year[5] = "";
	char mon[3] = "";
	char day[3] = "";
	char hour[3] = "";
	char min[3] = "";
	char sec[3] = "";

	if (!strlen(old_timestamp))
	{
		return 0;
	}
	strncpy(szTimestamp, old_timestamp, sizeof(szTimestamp) - 1);
	strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
	toupper_word(szFmt);
	if (strcmp(szFmt, "YYYYMMDD") == 0)
	{
		for (i = 0; i < 8; i++)
		{
			ch=szTimestamp[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
				return E_DATE_FMT;
			}
		}
		memcpy(year, szTimestamp, 4);
		memcpy(mon, szTimestamp + 4, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_DATE_FMT;
		}
		memcpy(day, szTimestamp + 6, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_DATE_FMT;
		}
		sprintf(new_timestamp, "%s-%s-%s-00.00.00.000000", year, mon, day);
	}
	else if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0)
	{
		for (i = 0; i < 14; i++)
		{
			ch=szTimestamp[i];
			if (!isdigit(ch))
			{
				writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
				return E_DATE_FMT;
			}
		}
		memcpy(year, szTimestamp, 4);
		memcpy(mon, szTimestamp + 4, 2);
		data = atoi(mon);
		if (data > 12)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_DATE_FMT;
		}
		memcpy(day, szTimestamp + 6, 2);
		data = atoi(day);
		if (data > 31)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_DATE_FMT;
		}
		memcpy(hour, szTimestamp+8, 2);
		data = atoi(hour);
		if (data > 23)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_TIME_FMT;
		}
		memcpy(min, szTimestamp + 10, 2);
		data = atoi(min);
		if (data > 59)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_TIME_FMT;
		}
		memcpy(sec, szTimestamp + 12, 2);
		data = atoi(sec);
		if (data > 59)
		{
			writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
			return E_TIME_FMT;
		}
		sprintf(new_timestamp, "%s-%s-%s-%s.%s.%s.000000", year, mon, day,hour, min, sec);
	}
	else
	{
		writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
		return E_DATE_FMT;
	}
	return 0;
}
int GetXmlValue(char value[], int size, char *key, char *buf)
{
	char keybegin[50] = "";
	char keyend[50] = "";
	char *pBegin = NULL;
	char *pEnd = NULL;
	int len = 0;

	sprintf(keybegin, "<%s>", key);
	sprintf(keyend, "</%s>", key);
	pBegin = strstr(buf, keybegin);
	if (!pBegin)
	{
		return E_XML_KEY_NOTFOUND;
	}
	pBegin += strlen(keybegin);
	pEnd = strstr(pBegin, keyend);
	if (!pEnd)
	{
		return E_XML_KEY_NOTFOUND;
	}
	len = pEnd - pBegin;
	if (len >= size)
	{
		len = size - 1;
	}
	strncpy(value, pBegin, len);
	value[len] = 0;
	return 0;
}
void AddXmlItemStr(char *buf, char *key, char *value)
{
	char tmp[1024] = "";

	snprintf(tmp, sizeof(tmp), "<%s>%s</%s>", key, value, key);
	strcat(buf, tmp);
}
void AddXmlItemInt(char *buf, char *key, int value)
{
	char tmp[1024] = "";

	snprintf(tmp, sizeof(tmp), "<%s>%d</%s>", key, value, key);
	strcat(buf, tmp);
}
void AddXmlItemDbl(char *buf, char *key, double value)
{
	char tmp[1024] = "";

	snprintf(tmp, sizeof(tmp), "<%s>%.lf</%s>", key, value, key);
	strcat(buf, tmp);
}

//	������ʾ����
int GetNewShowCardNo(char *sNewCardno,int iCustType,int iCardId)
{
	int i=0;
	int key=0;
	int sum=0;
	int check[9]={7,9,10,5, 8,4,2,1, 6};
	sprintf(sNewCardno,"%02d%07d",iCustType,iCardId);
	for(i=0;i<9;i++)
		sum+=((sNewCardno[i]-'0')*check[i]);
	key=sum%11%10;
	sNewCardno[9]=key+'0';
	sNewCardno[10]=0;
	return 0;
}
//У�鿨���Ƿ���Ч
int IsShowCardNoInvalid(char *sCardno)
{
	int i=0;
	int sum=0;
	int key=0;
	int check[9]={7,9,10,5, 8,4,2,1, 6};
	for(i=0;i<9;i++)
			sum+=((sCardno[i]-'0')*check[i]);
	key=sum%11%10;
	if(key==(sCardno[9]-'0'))
		return 0;
	else
		return E_CARDNO_INVALID;
}

/******************************************************************
	����:	�����������ݽṹ���������ݽṹ�ĺ�8���ֶν���mac����
	����:	������
	����:	��Ҫ���ʹ����ڴ棬��ȡ���з��ص�16���ֽڵ������ֶΣ����н�����
			���з��ص�mac��̬��Կ��ʹ�����еĶ�̬mac��Կ���м���mac
	����:	char* in--------�������ݽ�
	���:	char* out-------�����8���ֽڵ�macУ���
	����ֵ:	0�ɹ�����������

********************************************************************/
int generate_mac(char *buf, int len, char *mac)
{
	key_t key;
	int shmid = 0;
	char *shm;
	char buffer[100];
	char mac_key[16];

	key = ftok(".", 0);
	shmid = shmget(key, SEGSIZE, IPC_CREAT | 0666);

	if (-1 == shmid)
	{
		writelog(LOG_ERR, "Apply share memory error,error code=[%d]", shmid);
		return E_CREATE_SHARE_MEMORY;
	}
	shm = (char *) shmat(shmid, 0, 0);
	if ((int) shm == -1)
	{
		writelog(LOG_ERR, "Post share memory error,error code=[%d]", shm);
		return E_JOIN_SHARE_MEMORY;
	}
	if (shm[0] != 1)
	{
		writelog(LOG_ERR, "System not login to bank!mackey is novalid");
		return E_LOGINTOBANK_NO;
	}
	if (shm[1] != 1)
	{
		writelog(LOG_ERR, "System login to bank error!mackey is novalid");
		return E_LOGINTOBANK_FAIL;
	}
	memcpy(buffer, shm + 2 + 8 + 8, 8);
	_DES(STATIC_KEY, buffer, mac_key);
	//writelog(LOG_ERR, "dynamic mackey=[%s]",mac_key);
	ANSIX99(mac_key, buf, len - 8, mac);

	return 0;
}

int	check_mac(char* buf,int len)
{

	key_t key;
	int ret=0;
	int shmid=0;
	char *shm;
	char buffer[100];
	char mac_key[16];
	char mac[16];
	key=ftok(".",0);
	shmid=shmget(key,SEGSIZE,IPC_CREAT|0666);

	if(-1==shmid)
	{
		writelog(LOG_ERR,"Apply share memory error,error code=[%d]",shmid);
		return 	E_CREATE_SHARE_MEMORY;
	}
	shm=(char*)shmat(shmid,0,0);
	if((int)shm==-1)
	{
		writelog(LOG_ERR,"Post share memory error,error code=[%d]",shm);
		return 	E_JOIN_SHARE_MEMORY;
	}
	if(shm[0]!=1)
	{
		writelog(LOG_ERR,"System not login to bank!mackey is novalid");
		return	E_LOGINTOBANK_NO;
	}
	if(shm[1]!=1)
	{
		writelog(LOG_ERR,"System login to bank error!mackey is novalid");
		return	E_LOGINTOBANK_FAIL;
	}
	memcpy(buffer,shm+2+ 8 + 8,8);
	_DES(STATIC_KEY,buffer,mac_key);
	ANSIX99(mac_key,buf,len-8,mac);
	ret=memcmp(mac,buf+len-8,8);
	if(ret)
	{
		writelog(LOG_DEBUG,"Mac vertify fail,source_mac=[%s],true_mac[%s]",buf+len-8,mac);
		return	E_MAC_FAIL;
	}
	return 0;
}
int GetValueFromFmtBuf(char* buf, char *separator,int pos,char *value)
{
	int len=0;
	int cur_pos=0;
	char *phead=buf;
	char *ptail=NULL;
	char chSep=0;
	char *pend=0;

	if(NULL==buf)
	   return -1;
	if(NULL==separator)
	   return -1;
	len=strlen(buf);
	if(0==len)
	   return -1;
	pend=buf+len-1;
	chSep=*separator;
	while(phead<=pend)
	{
		while((' '==*phead)||('\t'==*phead))
		{
			if(phead>=pend)
			{
				return -1;
			}
			phead++;
		}
		ptail=strchr(phead,chSep);
		if(ptail==NULL)
		{
			ptail=pend;
		}
		cur_pos++;
		if(cur_pos==pos)
		{
			if(ptail<phead)
			{
				return -1;
			}
			if(ptail==pend)
			{
					strncpy(value,phead,ptail-phead+1);
					value[ptail-phead+1]=0;
			}
			else
			{
					strncpy(value,phead,ptail-phead);
					value[ptail-phead]=0;
			}
			len=strlen(value)-1;
			for(;len>=0;len--)
			{
				if(' '==value[len]||'\t'==value[len])
					value[len]=0;
			}
			return 0;
		}
		else
		{
			phead=ptail+1;
		}
	}
	return -1;
}
int SpanOfDate(const char *start,const char *end)
{
	assert(start != NULL && end != NULL);
	char starttime[15] = "";
	char endtime[15] =  "";
	int ret = 0;
	double spansecs = 0;
	memset(starttime,0,sizeof(starttime));
	memset(endtime,0,sizeof(endtime));
	// ����ʹ��2004 ��2005 �������������
	ret = strncmp(start,end,4) ;
	if( ret > 0 )
	{
		strcpy(starttime,"2004");
		strcpy(endtime,"2005");
	}
	else if( 0 == ret )
	{
		return 0;
	}
	else
	{
		strcpy(starttime,"2004");
		strcpy(endtime,"2004");
	}
	strncat(starttime,start,4);
	strncat(endtime,end,4);
	strcpy(starttime+8,"000001");
	strcpy(endtime+8,"000001");
#ifdef DEBUG
	writelog(LOG_DEBUG,"new convert date[%s] - [%s]",starttime,endtime);
#endif
	ret = DiffTime(endtime,starttime,&spansecs);
	if(ret)
	{
		writelog(LOG_DEBUG,"difftime error code [%d]",ret);
		return -1;
	}
	writelog(LOG_DEBUG,"difftime value[%d]",(int)spansecs);
	ret = (int)spansecs / (3600 * 24) + 1;
	return ret;
}

int GetNextDay(const char *start,int span,char *next)
{
	char tmp[5] = "";
	time_t t;
	struct tm *ptm;
	int ch;
	int i;
	for(i = 0;i < 8;++i)
	{
		ch = start[i];
		if(!isdigit(ch) )
		{
			return E_DATE_FMT;
		}
	}
	time(&t);
	ptm = localtime(&t);
	memcpy(tmp,start,4);
	ptm->tm_year = atoi(tmp) - 1900;
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,start+4,2);
	ptm->tm_mon = atoi(tmp) - 1;
	memcpy(tmp,start+6,2);
	ptm->tm_mday = atoi(tmp);

	t = mktime(ptm);
	t += 3600 * 24 * span;
	ptm = localtime(&t);
	sprintf(next,"%.04d%.02d%.02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);

	return 0;
}
int DecodeHDPhyId(const char* encoded,char * text)
{
	int i = 0;
	char temp[2] = "";
	strncpy(text,encoded,4);
	temp[0] = encoded[4];
	i = strtoul(temp,NULL,16);
	if(i < 0)
		return -1;
	sprintf(text+4,"%.02d",i);
	temp[0] = encoded[5];
	i = strtoul(temp,NULL,16);
	if(i < 0)
		return -1;
	sprintf(text+6,"%.02d",i);
	strncat(text+8,encoded+6,2);
	text[10] = '\0';
	return 0;
	
}
int EncodeHDPhyId(const char* text,char * encodeId)
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

void CalcMD5(unsigned char* buf,unsigned int len,unsigned char md5[16])
{
	MD5_CTX ctx;
	memset(&ctx,0,sizeof ctx);
	MD5Init(&ctx);
	MD5Update(&ctx,buf,len);
	MD5Final(md5,&ctx);
}

int CheckUserPswd(const char* input_pwd,const char* db_pwd)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

	strcpy(key,STATIC_SEED_KEY);
	des2src(account_pwd,input_pwd);
	EncodePwd(key,account_pwd,pwd, 0);
	//�жϿ������Ƿ���ȷ
	return memcmp(pwd,db_pwd,sizeof(pwd));
}

void RealSleep(int secs)
{
	do
	{
		secs = sleep(secs);
	}while(secs > 0);
}

void  InitDaemonProcess()
{
	signal(SIGHUP,  SIG_IGN) ;
	signal(SIGINT,  SIG_IGN) ;
	signal(SIGQUIT, SIG_IGN) ;
	signal(SIGTERM, SIG_IGN) ;
	signal(SIGCLD,  SIG_IGN) ;
	signal(SIGPIPE, SIG_IGN) ;
}

int StartAsDaemon()
{
	pid_t pid;
	//int status;
	// ��һ���ӽ��� 
	pid = fork();
	if( pid > 0 )
	{
		// ������
		//wait(&status);
		return pid;
	}
	if( pid < 0 )
	{
	    return -1;
	}
	// ��Ϊ��ͷ����
	setsid();
	// �ڶ����ӽ���
	pid = fork();
	if( pid > 0 )
	{
	    exit(0);
	}
	if( pid < 0 )
	{
		printf("�����ӽ���ʧ��\n");
		exit(1);
	}
	umask(0);
	return 0;
}

