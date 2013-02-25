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
#include <sys/stat.h>
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
//#include "rijndael-api-fst.h"
#include "rijndael.h"

char FileName[256];
int LineNo;

void set_4byte_int(unsigned char  *value_str,int num) {
    value_str[0]=(num>>24)&0xFF;
    value_str[1]=(num>>16)&0xFF;
    value_str[2]=(num>>8)&0xFF;
    value_str[3]=num&0xFF;
}
char* get_random(char *randomstr) {
    int i,j=0;
    unsigned char ucRandom[5]= {0};
    char szRandom[9]= {0};
    //根据时钟产生种子
    static int first=1;
    if(first) {
        srand((unsigned )time( NULL ));
        first=0;
    }
    int randomno=rand();
    set_4byte_int(ucRandom,randomno);
    sprintf(szRandom,"%02X",ucRandom[0]);
    sprintf(szRandom+2,"%02X",ucRandom[1]);
    sprintf(szRandom+4,"%02X",ucRandom[2]);
    sprintf(szRandom+6,"%02X",ucRandom[3]);
    if(randomstr)
        strcpy(randomstr,szRandom);
    return szRandom;
}
int get_int_random() {
    //根据时钟产生种子
    static int first=1;
    if(first) {
        srand((unsigned )time( NULL ));
        first=0;
    }
    return rand();
}

//四舍五入函数,保留num位小数
double D4U5(double value,int num) {

    int sign=1;
    long long i=0;
    double k=1.0;

    for(i=0; i<num+1; i++)
        k=10.0*k;
    if(value<0) {
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
int D2I(double value) {
    return (int) D4U5( value,0);
}
//金额比较函数,只比较小数点前2位
int amtcmp(double amt1,double amt2) {
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

void toupper_word(char word[]) {
    char ch;
    int len = 0;
    int i = 0;

    len = strlen(word);
    for (i = 0; i < len; i++) {
        ch = toupper(word[i]);
        word[i] = ch;
    }
}
void tolower_word(char word[]) {
    char ch;
    int len = 0;
    int i = 0;

    len = strlen(word);
    for (i = 0; i < len; i++) {
        ch = tolower(word[i]);
        word[i] = ch;
    }
}
char *trim(char *str) {
    char *p1 = str;
    char *p2;

    if (str == NULL)
        return NULL;
    p2 = str + strlen(str) - 1;
    if(p2<str)
        return str;
    while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
        p1++;
    while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r') {
        *p2 = 0;
        p2--;
        if(p2<p1)
            break;
    }
    if(p1!=str)
        strcpy(str, p1);
    return str;
}
char *ltrim(char *str) {
    char *p1 = str;

    if (str == NULL)
        return NULL;
    while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
        p1++;
    if(p1!=str)
        strcpy(str, p1);
    return str;
}
char *rtrim(char *str) {
    char *p2;

    if (str == NULL)
        return NULL;
    p2 = str + strlen(str) - 1;
    if(p2<str)
        return str;
    while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r') {
        *p2 = 0;
        p2--;
        if(p2<str)
            break;
    }
    return str;
}
//去掉前后空格,并添加结束符,len必须是使用是str的缓冲区长度
char *ntrim(char *str,int len) {
    char *p1 = str;
    char *p2 = NULL;

    if (str == NULL)
        return NULL;
    p2 = str + len - 1;
    *p2=0;
    p2 = str + strlen(str) - 1;
    if(p2<str)
        return str;
    while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r') {
        p1++;
    }
    while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r') {
        *p2 = 0;
        p2--;
        if(p2<p1)
            break;
    }
    if(p1!=str)
        strcpy(str, p1);
    return str;
}

char *getsysdate(char *date) {
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
char *getsystime(char *v_time) {
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

int getweekday() {
    time_t t;
    struct tm *ptm;
    static char szTime[10] = "";

    time(&t);
    ptm = localtime(&t);

    strftime(szTime, 2, "%u", ptm);
    return atoi(szTime);

}

char *getsysdatetime(char v_datetime[15]) {
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
char *getfmtsysdatetime(char v_datetime[20]) {
    time_t t;
    struct tm *ptm;
    static char szDatetime[20] = "";

    time(&t);
    ptm = localtime(&t);

    strftime(szDatetime, 20, "%Y-%m-%d %H:%M:%S", ptm);
    if (v_datetime)
        strcpy(v_datetime, szDatetime);
    return szDatetime;
}

char *getsystimestamp(char *v_timestamp) {
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

char *getdbdate(char *date) {
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
char *getdbtime(char *v_time) {
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
char *getdbtimestamp(char *v_timestamp) {
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
char *getdatetime(char v_datetime[20]) {
    time_t t;
    struct tm *ptm;
    static char szDatetime[20] = "";

    time(&t);
    ptm = localtime(&t);

    strftime(szDatetime,20, "%Y-%m-%d %H:%M:%S", ptm);
    if (v_datetime)
        strcpy(v_datetime, szDatetime);
    return szDatetime;
}
//函数功能：根据传入时间和秒，得到传入时间之前的时间
//输入：cur_time  char[7] 传入时间格式为：hhmmss
//输入：second    int	   时间间隔		单位为秒
//输出：pre_time  char[7] 距cur_time之前second秒的时间，格式为hhmmss

int GetPreTime(char cur_time[7],int second,char pre_time[7]) {
    int i=0;
    int ch=0;
    int iCurHour=0;
    int iCurMin=0;
    int iCurSec=0;
    char tmp[3]="";
    time_t t;
    struct tm *ptm;

    for (i=0; i<6; i++) {
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
//函数功能：根据传入时间和秒，得到传入时间之前的时间
//输入：cur_time  char[7] 传入时间格式为：hhmmss
//输入：second    int	   时间间隔		单位为秒
//输出：pre_time  char[7] 距cur_time之后second秒的时间，格式为hhmmss

int GetNextTime(char cur_time[7],int second,char next_time[7]) {
    int i=0;
    int ch=0;
    int iCurHour=0;
    int iCurMin=0;
    int iCurSec=0;
    char tmp[3]="";
    time_t t;
    struct tm *ptm;

    for (i=0; i<6; i++) {
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

//函数功能：根据两个传入时间，得到两个传入时间之间的间隔时间
//输入：tim1  char[15] 传入时间格式为：yyyymmddhhmmss
//输入：tim2  char[15] 传入时间格式为：yyyymmddhhmmss
//输出：second   double*	   时间间隔		单位为秒

int DiffTime(char time1[],char time2[],double* second) {
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

    for (i=0; i<14; i++) {
        ch=time1[i];
        if(!isdigit(ch))
            return E_DATE_FMT;
    }
    for (i=0; i<14; i++) {
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

int DiffDay(char day1[9],char day2[9],int *days) {
#define SECONDS_PER_DAY (60 * 60 * 24)
    char time1[15];
    char time2[15];
    double second = 0.0;
    int ret;
    sprintf(time1,"%s000000",day1);
    sprintf(time2,"%s000000",day2);

    ret = DiffTime(time1,time2,&second);
    if(ret)
        return ret;

    *days = D2I(second) / SECONDS_PER_DAY;
    return 0;
}

//根据字符串日期计算得到1900开始的秒
int datetime2second(const char *datetime,char *fmt,double *second) {
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
    if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0) {
        for (i=0; i<14; i++) {
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
    } else if (strcmp(szFmt, "YYYYMMDD") == 0) {
        for (i=0; i<8; i++) {
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
//根据秒得到字符串日期
int second2datetime(double second,char *datetime,char *fmt) {
    time_t t;
    struct tm *ptm;
    char szFmt[100]="";

    strncpy(szFmt, fmt, sizeof(szFmt) - 1);
    toupper_word(szFmt);

    t=second;
    ptm = localtime(&t);
    if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0) {
        strftime(datetime, 15, "%Y%m%d%H%M%S", ptm);
    } else if (strcmp(szFmt, "YYYYMMDD") == 0) {
        strftime(datetime, 9, "%Y%m%d", ptm);
    } else
        return E_DATE_FMT;
    return 0;
}

void getpos(char *v_filename, int v_lineno) {
    strcpy(FileName, v_filename);
    LineNo = v_lineno;
}
void errlog(int level, char *fmt, ...) {
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
	功能: 压缩菜单、功能集合:将数据库中VarChar(800)的字段压缩到可以让CPack中usset3[100]来传输
	前提：长度大的字符串必须为0或1的组合
	描述：CPack中最大的字符数组长度为100，而数据库中最大的字符长度为800，该函数可以将800个字符压缩为100个，也可以将100个字符解压为800个
	作者: 耿刚从钱彬处得到
	返回: int       	0：成功； -1：失败
	参数: int nType       	1：解压100to800； 2：压缩800to100
	参数: char *usset      	长度小的字符串，char usset[nUssetSize]
	参数: char *menuset    	长度大的字符串，char menuset[nMenusetSize]
	参数: int nUssetSize    usset的长度
	参数: int nMenusetSize  menuset的长度
*/
int UssetConvert(int nType,char *usset,char *menuset,int nUssetSize,int nMenusetSize) {
    int i,j;
    unsigned char nTmpByte;
    switch (nType) {
    case 1: {
        //convert usset to menuset
        memset(menuset,'0',nMenusetSize);
        j = 0;
        for (i = 0; i< nUssetSize; i++) {
            for (nTmpByte = 0x80; nTmpByte != 0 && (j < nMenusetSize); nTmpByte >>=1,j++) {
                if (usset[i] & nTmpByte) {
                    menuset[j] = '1';
                }

            }
        }
        break;
    }
    case 2: {
        //convert menuset to usset
        int nOffset,nBit;
        memset(usset,0,nUssetSize);
        for (i = 0; i < nMenusetSize && i/8+1 <= nUssetSize; i++) {
            if (menuset[i] != '0') {
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

//程序功能，将型如yyyymmddhhmmss的时间戳格式为yyyy-mm-dd hh:mm:ss
//参数：char *origin:原始字符串
//          char *timestamp:db2格式的字符串
//返回：成功为0

int ConvertDate(char *origin, char *timestamp) {
    int i, j;

    for (i = 0, j = 0;; i++, j++) {
        if (i == 4 || i == 7)
            timestamp[i++] = BAR;

        if (i == 10)
            timestamp[i++] = ' ';

        if (i == 13 || i == 16)
            timestamp[i++] = COLON;
        if (i == 19) {
            timestamp[i] = '\0';
            break;
        }
        timestamp[i] = origin[j];
    }

    return 0;
}

//author:xunzhang huang
//date:2004-08-30 17：11
//flag==0 yyyy-mm-dd  -->>  yyyymmdd
//flag==1 yyyymmdd    -->>  yyyy-mm-dd
int ConvertDateLen(char *out, const char *in, int flag) {
    char *p = (char*)in;
    char tmp_out[9] = "";
    char *q = tmp_out;
    if (flag != 0 && flag != 1) {
        return -1;
    }
    if (0 == flag) {
        if (strlen(in) != 10) {
            return -1;
        }

        while (*p != '-') {
            *q++ = *p++;
        }
        p++;
        while (*p != '-') {
            *q++ = *p++;
        }
        p++;
        while (*p != '\0') {
            *q++ = *p++;
        }
        *q = '\0';
        return 0;
    }
    return 0;
}

/**
功能: 加密、解密要传输的密码
前提：
描述：利用DES算法，来加密、解密密码
作者: 黄勋章
返回: int  0：成功； -1：失败
参数: int flag  	0 : 加密,clearpwd->secretpwd;
						1 : 解密,secretpwd->clearpwd
参数: char *key,字符串,种子,应尽量使其为16位
参数:	char *clearpwd,字符串,明文,加密前的数据
参数：char *secretpwd,字符串,密文,加密后的数据
*/

int EncodePwd(char *key, char *clearpwd, char *secretpwd, int flag) {
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
    if (flag == 0) {
        strncpy((char*)k, key,8);
        strncpy((char*)clear, clearpwd,8);
        deskey(k, 0);
        Ddes(clear, secret);

        for(i=0; i<8; i++) {
            snprintf(&secretpwd[2*i],3,"%02X",secret[i]);
        }
        return 0;
    }
    if (flag == 1) {
        strncpy((char*)cipher,secretpwd,16);
        for(i=0; i<8; i++) {
            memcpy(tmp,&cipher[2*i],2);
            ul=strtoul(tmp,NULL,16);
            secret[i]=ul;
        }
        strncpy((char*)k, key,8);
        deskey(k, 1);
        Ddes(secret, clear);
        strncpy(clearpwd,(char*)clear,8);
        return 0;
    }
    return -1;
}

int GetInitKey(char *s_init_key, char *key) {
    char k[17] = "";
    char plain[17] = "";

    memset(k,0,sizeof(k));
    memset(plain,0,sizeof(plain));

    strncpy(k, key,8);
    memcpy(plain,getsystimestamp(NULL)+12,8);
    EncodePwd(k, plain, s_init_key, 0);

    return 0;
}
int GetDynaKey(char *Dyna_Key) {
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
	功能: 检查传递来的初始密钥是否正确
	前提：子系统标志已取得，初始密钥已取得
	描述：种子是key即为产生初始密钥时的种子,由程序员指定
	作者: 黄勋章
	返回: 成功为0,不成功非0
	参数:	char *s_init_key,初始密钥,初始密钥定为16位
	参数: int sysid,子系统标志
	参数:	char *key ,先前的种子
*/
int CheckInitKey(char *s_init_key, int sysid, char *key) {
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
    strcpy(k, key);				//key 为密钥，和加密时必须一样

    sprintf(clear, "%d", sysid);	//sysid +"aaaaaa..." 为明文
    length = strlen(clear);
    for (a = length; a < 16; a++) {
        clear[a] = 'a';
    }
    clear[16] = '\0';

    EncodePwd(k, clear, init, 0);	//重新编码

    int ret;

    ret = strcmp(init, s_init_key);	//比较参数和得到的密钥是否一致

    return ret;
}

/**
	功能: 利用子系统标志和设备标志产生读卡密钥
	前提：子系统标志已取得，设备标志已取得
	描述：种子由程序员指定,明文为子系统标志＋设备标志并取其前16个字节
	作者: 黄勋章
	返回: 成功为0
	参数:	char *read_card_key,存放结果读卡密钥,至少17个字节
	参数: int sysid,子系统标志
	参数：int deviceid ,设备标志
	参数:	char key ,种子,程序员指定
*/
int GetReadCardKey(int deviceid, int sysid, char *read_card_key, char *key) {
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
    strcpy(k, key);				//key由程序员确定，尽量为16位

    sprintf(clear, "%d%d", sysid, deviceid);	//subsytem_id + deviceid + "aaaa..."共16位为明文

    length = strlen(clear);
    if (length < 16) {
        for (a = length; a < 16; a++) {
            clear[a] = 'a';
        }
    }
    clear[16] = '\0';

    EncodePwd(k, clear, init, 0);

    strcpy(read_card_key, init);

    return 0;
}
int IsInvalidDateTime(char *sdatetime,  char *fmt) {
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
    if (strncmp(szFmt, "YYYYMMDD", 8) == 0) {
        for (i = 0; i < 8; i++) {
            ch=szDatetime[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "date[%s]", szDatetime);
                return E_DATE_FMT;
            }
        }
//		memcpy(year, szDate, 4);
        memcpy(mon, szDatetime + 4, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
        memcpy(day, szDatetime + 6, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
    } else if (strncmp(szFmt, "YYMMDD", 6) == 0) {
        for (i = 0; i < 6; i++) {
            ch=szDatetime[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "date[%s]", szDatetime);
                return E_DATE_FMT;
            }
        }
        memcpy(mon, szDatetime + 2, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
        memcpy(day, szDatetime + 4, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
    } else if(!strncmp(szFmt,"MMDD",4)) {
        for(i = 0; i < 4; ++i) {
            ch = szDatetime[i];
            if(!isdigit(ch)) {
                writelog(LOG_ERR,"date[%s]",szDatetime);
                return E_DATE_FMT;
            }
        }
        memcpy(mon, szDatetime, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
        memcpy(day, szDatetime + 2, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "date[%s]", szDatetime);
            return E_DATE_FMT;
        }
    } else	if(strncmp(szFmt, "HHMMSS", 6) == 0) {
        for (i = 0; i < 6; i++) {
            ch=szDatetime[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "time[%s]", szDatetime);
                return E_TIME_FMT;
            }
        }
        memcpy(hour, szDatetime, 2);
        data = atoi(hour);
        if (data > 23) {
            writelog(LOG_ERR, "time[%s]", szDatetime);
            return E_TIME_FMT;
        }
        memcpy(min, szDatetime + 2, 2);
        data = atoi(min);
        if (data > 59) {
            writelog(LOG_ERR, "time[%s]", szDatetime);
            return E_TIME_FMT;
        }
        memcpy(sec, szDatetime + 4, 2);
        data = atoi(sec);
        if (data > 59) {
            writelog(LOG_ERR, "time[%s]", szDatetime);
            return E_TIME_FMT;
        }
    }

    else {
        writelog(LOG_ERR, "datetime[%s]", szDatetime);
        return E_DATE_FMT;
    }
    return 0;
}

int str2dbdate(char *new_date, char *old_date, char *old_fmt) {
    int i = 0;
    int data = 0;
    int ch=0;
    char szDate[9] = "";
    char szFmt[20] = "";
    char year[5] = "";
    char mon[3] = "";
    char day[3] = "";

    if (!strlen(old_date)) {
        return 0;
    }
    strncpy(szDate, old_date, sizeof(szDate) - 1);
    strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
    toupper_word(szFmt);
    if (strncmp(szFmt, "YYYYMMDD", 8) == 0) {
        for (i = 0; i < 8; i++) {
            ch=szDate[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "date[%s]", szDate);
                return E_DATE_FMT;
            }
        }
        memcpy(year, szDate, 4);
        memcpy(mon, szDate + 4, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "date[%s]", szDate);
            return E_DATE_FMT;
        }
        memcpy(day, szDate + 6, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "date[%s]", szDate);
            return E_DATE_FMT;
        }
        sprintf(new_date, "%s-%s-%s", year, mon, day);
    } else if (strncmp(szFmt, "YYMMDD", 6) == 0) {
        for (i = 0; i < 6; i++) {
            ch=szDate[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "date[%s]", szDate);
                return E_DATE_FMT;
            }
        }
        memcpy(year, "20", 2);
        memcpy(year + 2, szDate, 2);
        memcpy(mon, szDate + 2, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "date[%s]", szDate);
            return E_DATE_FMT;
        }
        memcpy(day, szDate + 4, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "date[%s]", szDate);
            return E_DATE_FMT;
        }
        sprintf(new_date, "%s-%s-%s", year, mon, day);
    } else {
        writelog(LOG_ERR, "date[%s]", szDate);
        return E_DATE_FMT;
    }
    return 0;
}
int str2dbtime(char *new_time, char *old_time, char *old_fmt) {
    int i = 0;
    int data = 0;
    int ch=0;
    char szTime[7] = "";
    char szFmt[20] = "";
    char hour[3] = "";
    char min[3] = "";
    char sec[3] = "";

    if (!strlen(old_time)) {
        return 0;
    }
    strncpy(szTime, old_time, sizeof(szTime) - 1);
    strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
    toupper_word(szFmt);
    if (strncmp(szFmt, "HHMMSS", 6) == 0) {
        for (i = 0; i < 6; i++) {
            ch=szTime[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "time[%s]", szTime);
                return E_TIME_FMT;
            }
        }
        memcpy(hour, szTime, 2);
        data = atoi(hour);
        if (data > 23) {
            writelog(LOG_ERR, "time[%s]", szTime);
            return E_TIME_FMT;
        }
        memcpy(min, szTime + 2, 2);
        data = atoi(min);
        if (data > 59) {
            writelog(LOG_ERR, "time[%s]", szTime);
            return E_TIME_FMT;
        }
        memcpy(sec, szTime + 4, 2);
        data = atoi(sec);
        if (data > 59) {
            writelog(LOG_ERR, "time[%s]", szTime);
            return E_TIME_FMT;
        }
        sprintf(new_time, "%s:%s:%s", hour, min, sec);
    } else {
        writelog(LOG_ERR, "time[%s]", szTime);
        return E_TIME_FMT;
    }
    return 0;
}
int str2dbtimestamp(char *new_timestamp, char *old_timestamp, char *old_fmt) {
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

    if (!strlen(old_timestamp)) {
        return 0;
    }
    strncpy(szTimestamp, old_timestamp, sizeof(szTimestamp) - 1);
    strncpy(szFmt, old_fmt, sizeof(szFmt) - 1);
    toupper_word(szFmt);
    if (strcmp(szFmt, "YYYYMMDD") == 0) {
        for (i = 0; i < 8; i++) {
            ch=szTimestamp[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
                return E_DATE_FMT;
            }
        }
        memcpy(year, szTimestamp, 4);
        memcpy(mon, szTimestamp + 4, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_DATE_FMT;
        }
        memcpy(day, szTimestamp + 6, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_DATE_FMT;
        }
        sprintf(new_timestamp, "%s-%s-%s-00.00.00.000000", year, mon, day);
    } else if (strcmp(szFmt, "YYYYMMDDHHMMSS") == 0) {
        for (i = 0; i < 14; i++) {
            ch=szTimestamp[i];
            if (!isdigit(ch)) {
                writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
                return E_DATE_FMT;
            }
        }
        memcpy(year, szTimestamp, 4);
        memcpy(mon, szTimestamp + 4, 2);
        data = atoi(mon);
        if (data > 12) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_DATE_FMT;
        }
        memcpy(day, szTimestamp + 6, 2);
        data = atoi(day);
        if (data > 31) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_DATE_FMT;
        }
        memcpy(hour, szTimestamp+8, 2);
        data = atoi(hour);
        if (data > 23) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_TIME_FMT;
        }
        memcpy(min, szTimestamp + 10, 2);
        data = atoi(min);
        if (data > 59) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_TIME_FMT;
        }
        memcpy(sec, szTimestamp + 12, 2);
        data = atoi(sec);
        if (data > 59) {
            writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
            return E_TIME_FMT;
        }
        sprintf(new_timestamp, "%s-%s-%s-%s.%s.%s.000000", year, mon, day,hour, min, sec);
    } else {
        writelog(LOG_ERR, "timestamp[%s]", szTimestamp);
        return E_DATE_FMT;
    }
    return 0;
}
int GetXmlValue(char value[], int size, char *key, char *buf) {
    char keybegin[50] = "";
    char keyend[50] = "";
    char *pBegin = NULL;
    char *pEnd = NULL;
    int len = 0;

    sprintf(keybegin, "<%s>", key);
    sprintf(keyend, "</%s>", key);
    pBegin = strstr(buf, keybegin);
    if (!pBegin) {
        return E_XML_KEY_NOTFOUND;
    }
    pBegin += strlen(keybegin);
    pEnd = strstr(pBegin, keyend);
    if (!pEnd) {
        return E_XML_KEY_NOTFOUND;
    }
    len = pEnd - pBegin;
    if (len >= size) {
        len = size - 1;
    }
    strncpy(value, pBegin, len);
    value[len] = 0;
    return 0;
}
void AddXmlItemStr(char *buf, char *key, char *value) {
    char tmp[1024] = "";

    snprintf(tmp, sizeof(tmp), "<%s>%s</%s>", key, value, key);
    strcat(buf, tmp);
}
void AddXmlItemInt(char *buf, char *key, int value) {
    char tmp[1024] = "";

    snprintf(tmp, sizeof(tmp), "<%s>%d</%s>", key, value, key);
    strcat(buf, tmp);
}
void AddXmlItemDbl(char *buf, char *key, double value) {
    char tmp[1024] = "";

    snprintf(tmp, sizeof(tmp), "<%s>%.lf</%s>", key, value, key);
    strcat(buf, tmp);
}

//	生成显示卡号
int GetNewShowCardNo(char *sNewCardno,int iCustType,int iCardId) {
    int i=0;
    int key=0;
    int sum=0;
    int check[9]= {7,9,10,5, 8,4,2,1, 6};
    sprintf(sNewCardno,"%02d%07d",iCustType,iCardId);
    for(i=0; i<9; i++)
        sum+=((sNewCardno[i]-'0')*check[i]);
    key=sum%11%10;
    sNewCardno[9]=key+'0';
    sNewCardno[10]=0;
    return 0;
}
//校验卡号是否有效
int IsShowCardNoInvalid(char *sCardno) {
    int i=0;
    int sum=0;
    int key=0;
    int check[9]= {7,9,10,5, 8,4,2,1, 6};
    for(i=0; i<9; i++)
        sum+=((sCardno[i]-'0')*check[i]);
    key=sum%11%10;
    if(key==(sCardno[9]-'0'))
        return 0;
    else
        return E_CARDNO_INVALID;
}

/******************************************************************
	功能:	根据输入数据结构，将该数据结构的后8个字段进行mac计算
	作者:	韩海东
	描数:	需要访问共享内存，读取银行返回的16个字节的密码字段，从中解析出
			银行返回的mac动态密钥，使用其中的动态mac密钥进行计算mac
	输入:	char* in--------输入数据结
	输出:	char* out-------输出的8个字节的mac校验断
	返回值:	0成功，其他错误

********************************************************************/
int generate_mac(char *buf, int len, char *mac) {
    key_t key;
    int shmid = 0;
    char *shm;
    char buffer[100];
    char mac_key[16];

    key = ftok(".", 0);
    shmid = shmget(key, SEGSIZE, IPC_CREAT | 0666);

    if (-1 == shmid) {
        writelog(LOG_ERR, "Apply share memory error,error code=[%d]", shmid);
        return E_CREATE_SHARE_MEMORY;
    }
    shm = (char *) shmat(shmid, 0, 0);
    if ((int) shm == -1) {
        writelog(LOG_ERR, "Post share memory error,error code=[%d]", shm);
        return E_JOIN_SHARE_MEMORY;
    }
    if (shm[0] != 1) {
        writelog(LOG_ERR, "System not login to bank!mackey is novalid");
        return E_LOGINTOBANK_NO;
    }
    if (shm[1] != 1) {
        writelog(LOG_ERR, "System login to bank error!mackey is novalid");
        return E_LOGINTOBANK_FAIL;
    }
    memcpy(buffer, shm + 2 + 8 + 8, 8);
    _DES((unsigned char*)STATIC_KEY, (unsigned char*)buffer, (unsigned char*)mac_key);
    //writelog(LOG_ERR, "dynamic mackey=[%s]",mac_key);
    ANSIX99(mac_key, buf, len - 8, mac);

    return 0;
}

int	check_mac(char* buf,int len) {

    key_t key;
    int ret=0;
    int shmid=0;
    char *shm;
    char buffer[100];
    char mac_key[16];
    char mac[16];
    key=ftok(".",0);
    shmid=shmget(key,SEGSIZE,IPC_CREAT|0666);

    if(-1==shmid) {
        writelog(LOG_ERR,"Apply share memory error,error code=[%d]",shmid);
        return 	E_CREATE_SHARE_MEMORY;
    }
    shm=(char*)shmat(shmid,0,0);
    if((int)shm==-1) {
        writelog(LOG_ERR,"Post share memory error,error code=[%d]",shm);
        return 	E_JOIN_SHARE_MEMORY;
    }
    if(shm[0]!=1) {
        writelog(LOG_ERR,"System not login to bank!mackey is novalid");
        return	E_LOGINTOBANK_NO;
    }
    if(shm[1]!=1) {
        writelog(LOG_ERR,"System login to bank error!mackey is novalid");
        return	E_LOGINTOBANK_FAIL;
    }
    memcpy(buffer,shm+2+ 8 + 8,8);
    _DES((unsigned char*)STATIC_KEY,(unsigned char*)buffer,(unsigned char*)mac_key);
    ANSIX99(mac_key,buf,len-8,mac);
    ret=memcmp(mac,buf+len-8,8);
    if(ret) {
        writelog(LOG_DEBUG,"Mac vertify fail,source_mac=[%s],true_mac[%s]",buf+len-8,mac);
        return	E_MAC_FAIL;
    }
    return 0;
}
int GetValueFromFmtBuf(char* buf, char *separator,int pos,char *value) {
    int len=0;
    int cur_pos=1;
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

    while(phead<=pend) {
        while((' '==*phead)||('\t'==*phead)) {
            if(phead>=pend) {
                return -1;
            }
            phead++;
        }
        ptail=strchr(phead,chSep);
        if(NULL==ptail) {
            if(pos!=cur_pos)
                return -1;
            //		strncpy(value,phead,pend-phead+1);
            //		value[pend-phead+1]=0;
            strcpy(value,phead);
            break;
        } else {
            if(cur_pos<pos) {
                phead=ptail+1;
                cur_pos++;
                continue;
            } else {
                strncpy(value,phead,ptail-phead);
                value[ptail-phead]=0;
                break;
            }
        }
    }
    len=strlen(value)-1;
    for(; len>=0; len--) {
        if(' '==value[len]||'\t'==value[len])
            value[len]=0;
    }
    return 0;
}
int SpanOfDate(const char *start,const char *end) {
    assert(start != NULL && end != NULL);
    char starttime[15] = "";
    char endtime[15] =  "";
    int ret = 0;
    double spansecs = 0;
    memset(starttime,0,sizeof(starttime));
    memset(endtime,0,sizeof(endtime));
    // 假设使用2004 与2005 两个年份做计算
    ret = strncmp(start,end,4) ;
    if( ret > 0 ) {
        strcpy(starttime,"2004");
        strcpy(endtime,"2005");
    } else if( 0 == ret ) {
        return 0;
    } else {
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
    if(ret) {
        writelog(LOG_DEBUG,"difftime error code [%d]",ret);
        return -1;
    }
    writelog(LOG_DEBUG,"difftime value[%d]",(int)spansecs);
    ret = (int)spansecs / (3600 * 24) + 1;
    return ret;
}

int GetNextDay(const char start[9],int span,char next[9]) {
    char tmp[5] = "";
    time_t t;
    struct tm *ptm;
    int ch;
    int i;
    for(i = 0; i < 8; ++i) {
        ch = start[i];
        if(!isdigit(ch) ) {
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

int OffsetDatetime(const char begin_dt[15],int second,char end_dt[15]) {
    char tmp[5] = "";
    time_t t;
    struct tm *ptm;
    int ch;
    int i;
    for(i = 0; i < 14; ++i) {
        ch = begin_dt[i];
        if(!isdigit(ch) ) {
            return E_DATE_FMT;
        }
    }
    time(&t);
    ptm = localtime(&t);
    memcpy(tmp,begin_dt,4);
    ptm->tm_year = atoi(tmp) - 1900;
    memset(tmp,0,sizeof tmp);
    memcpy(tmp,begin_dt+4,2);
    ptm->tm_mon = atoi(tmp) - 1;
    memcpy(tmp,begin_dt+6,2);
    ptm->tm_mday = atoi(tmp);
    memset(tmp,0,sizeof tmp);
    memcpy(tmp,begin_dt+8,2);
    ptm->tm_hour=atoi(tmp);
    memcpy(tmp,begin_dt+10,2);
    ptm->tm_min=atoi(tmp);
    memcpy(tmp,begin_dt+12,2);
    ptm->tm_sec=atoi(tmp);


    t = mktime(ptm);
    t += second;
    ptm = localtime(&t);
    if(ptm)
        sprintf(end_dt,"%.04d%.02d%.02d%.02d%.02d%.02d",
                ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour
                ,ptm->tm_min,ptm->tm_sec);
    else
        return -1;
    return 0;
}

int DecodeHDPhyId(const char* encoded,char * text) {
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
int EncodeHDPhyId(const char* text,char * encodeId) {
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

void CalcMD5(unsigned char* buf,unsigned int len,unsigned char md5[16]) {
    MD5_CTX ctx;
    memset(&ctx,0,sizeof ctx);
    MD5Init(&ctx);
    MD5Update(&ctx,buf,len);
    MD5Final(md5,&ctx);
}

int CheckUserPswd(const char* input_pwd,const char* db_pwd) {
    char key[32+1]="";
    char pwd[32+1]="";
    char account_pwd[6+1]="";

    strcpy(key,STATIC_SEED_KEY);
    des2src(account_pwd,input_pwd);
    EncodePwd(key,account_pwd,pwd, 0);
    //判断卡密码是否正确
    return memcmp(pwd,db_pwd,sizeof(pwd));
}

void RealSleep(int secs) {
    do {
        secs = sleep(secs);
    } while(secs > 0);
}

void  InitDaemonProcess() {
    signal(SIGHUP,  SIG_IGN) ;
    signal(SIGINT,  SIG_IGN) ;
    signal(SIGQUIT, SIG_IGN) ;
    signal(SIGTERM, SIG_IGN) ;
    signal(SIGCLD,  SIG_IGN) ;
    signal(SIGPIPE, SIG_IGN) ;
}

int StartAsDaemon() {
    pid_t pid;
    int i;
    //int status;
    // 第一个子进程
    pid = fork();
    if( pid > 0 ) {
        // 父进程
        //wait(&status);
        return pid;
    }
    if( pid < 0 ) {
        return -1;
    }
    // 成为领头进程
    setsid();
    signal(SIGCHLD,SIG_IGN);
    // 第二个子进程
    pid = fork();
    if( pid > 0 ) {
        exit(0);
    }
    if( pid < 0 ) {
        printf("创建子进程失败\n");
        exit(1);
    }
    chdir("/");
    umask(0);
    return 0;
}
int time_probe_now(time_probe_t *probe) {
    int ret;
    memset(probe,0,sizeof(time_probe_t));
    probe->current_id = getpid();
    ret = gettimeofday(&probe->start_stamp,NULL);
    return ret;
}

int time_probe_finish(time_probe_t *probe) {
    int ret;
    pid_t curr;
    curr = getpid();
    if(probe->current_id != curr)
        return -1;
    ret = gettimeofday(&probe->time_stamp,NULL);
    if(ret)
        return ret;
    return 0;
}

void time_probe_print(const time_probe_t *probe,const char *msg) {
    if(!msg)
        writelog(LOG_INFO,"time estimated [%lu.%.06lu]"
                 ,probe->time_stamp.tv_sec -probe->start_stamp.tv_sec
                 ,probe->time_stamp.tv_usec -probe->start_stamp.tv_usec);
    else
        writelog(LOG_INFO,"[%s] time estimated [%lu.%.06lu]",msg
                 ,probe->time_stamp.tv_sec -probe->start_stamp.tv_sec
                 ,probe->time_stamp.tv_usec -probe->start_stamp.tv_usec);
}

static void get_identify_lock_file_path(const char *uni_identify,char *lock_file) {
    sprintf(lock_file,"/tmp/%s.lock",uni_identify);
}

int startup_lock_file(const char *uni_identify) {
    FILE *lock_file;
    int ret;
    char lock_file_name[4096] = "";
    get_identify_lock_file_path(uni_identify,lock_file_name);
    if((lock_file = fopen(lock_file_name,"w")) == NULL) {
        return -1;
    }
    ret=lockf(fileno(lock_file),F_TEST,0L);
    if(ret) {
        fclose(lock_file);
        return -2;
    }
    ret = lockf( fileno(lock_file),F_LOCK,0L);
    if(ret) {
        fclose(lock_file);
        return -3;
    }
    return 0;
}

int test_process_lock_file(const char *uni_identify) {
    FILE *lock_file;
    int ret;
    char lock_file_name[4096] = "";
    get_identify_lock_file_path(uni_identify,lock_file_name);
    if((lock_file = fopen(lock_file_name,"w")) == NULL) {
        // 打开文件失败
        return -1;
    }
    ret=lockf(fileno(lock_file),F_TEST,0L);
    if(ret) {
        // 程序已经运行
        fclose(lock_file);
        return 0;
    }
    fclose(lock_file);
    // 程序未运行
    return 1;
}

int is_validate_sexno(char sexno) {
    switch(sexno) {
    case '1':
    case '2':
        return 0;
    default:
        return -1;
    }
}
//规则如下： 当发卡人在系统中的证件类别为身份证并有身份证号时，卡密码取身份证的后六位数字（例如...987654321则为654321；...98765432X则为765432），否则都为“888888”。
int get_init_passwd_by_man_id(const char *man_id,char *passwd) {
    int len;
    int k;
    //trim(man_id);
    len=strlen(man_id);
    switch(len) {
    case 15:
        strncpy(passwd,&man_id[len-6],6);
        break;
    case 18:
        strncpy(passwd,&man_id[len-7],6);
        break;
    default:
        strcpy(passwd,DEFAULT_CUST_PWD);
        break;
    }
    passwd[6]=0;
    //检查是否有非数字字符,如果有非法字符，则取默认密码
    for(int k=0; k<6; k++) {
        if(passwd[k]>'9'||passwd[k]<'0') {
            strcpy(passwd,DEFAULT_CUST_PWD);
            break;
        }
    }
    return 0;
}

//规则如下： 当发卡人在系统中的证件类别为身份证并有身份证号时，卡密码取身份证的后六位数字（例如...987654321则为654321；...98765432X则为765432），否则都为“888888”。
/*
int get_init_passwd_by_man_id(const char *man_id,char *passwd)
{
	int len;
	int k;
	char idno[61]={0};

	des2src(idno,man_id);
	len=strlen(idno);
	if(len<6)
	{
		strcpy(passwd,DEFAULT_CUST_PWD);
		return 0;
	}
	if((idno[len-1]>'9')||(idno[len-1]<'0'))
	{
		idno[len-1]='0';
	}
	strncpy(passwd,&idno[len-6],6);
	passwd[6]=0;
	//检查是否有非数字字符,如果有非法字符，则取默认密码
	for(int k=0;k<6;k++)
	{
		if(passwd[k]>'9'||passwd[k]<'0')
		{
			strcpy(passwd,DEFAULT_CUST_PWD);
			break;
		}
	}
	return 0;
}
*/
void gen_session_id(char *session,int len) {
    const char session_tbl[] = {'1','2','3','4','5','6','7','8','9','0',
                                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                                'r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H',
                                'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y',
                                'Z','-','=','~','+'
                               };
    int idx,i;
    double tbl_len = sizeof(session_tbl);
    srand((unsigned)time(NULL));
    for(i = 0; i < len; ++i) {
        idx = (tbl_len * rand()/(RAND_MAX+1.0));
        session[i] = session_tbl[idx];
    }
}

my_string_t alloc_mystring() {
#define MY_STRING_DEFUALT_LEN 512
    my_string_t str;
    str.data = (char*)malloc(MY_STRING_DEFUALT_LEN);
    str.size = MY_STRING_DEFUALT_LEN;
    str.length = 0;
    return str;
}

void free_mystring(my_string_t *str) {
    if(str->size > 0 && str->data) {
        free(str->data);
        str->length =0;
        str->size = 0;
    }
}

void resize_mystring(my_string_t *str,int newsize) {
    str->data = (char*)realloc(str->data,newsize);
    str->size = newsize;
}

int read_file_line(my_string_t *str,FILE *fp) {
    int c;
    while(1) {
        c = fgetc(fp);
        //printf(" character[%d]\n",c);
        switch(c) {
        case 255:
        case -1:
            if(feof(fp))
                return 1;
            return -1;
        case '\r':
            break;
        case '\n':
            // 读取成功一行, 增加结束符
            str->data[str->length] = '\0';
            return 0;
        case '\\':
            // 换行后读取下一行
            break;
        default:
            if(str->length >= (str->size-1))
                resize_mystring(str,str->size + MY_STRING_DEFUALT_LEN);
            str->data[str->length++] = c;
            break;
        }
    }
    return 1;
}

int trim_line(my_string_t *str) {
    int pos;
    if(str->length == 0)
        return 0;
    for(pos=0; pos < str->length; ++pos)
        if(str->data[pos] == ' ' || str->data[pos] == '\t')
            continue;
        else
            break;
    int left;
    for(left=str->length - 1; left > pos; --left)
        if(str->data[left] == ' ' || str->data[left] == '\t')
            continue;
        else
            break;
    str->length = left+1;
    return pos;
}

void lowercase_my_string(my_string_t *str) {
    int i;
    for(i = 0; i < str->length; ++i) {
        if(str->data[i] >= 'A' && str->data[i] <= 'Z')
            str->data[i] += 0x20;
    }
}
//根据起始日期和间隔天数,计算间隔天数之后的日期
int calcEndDate(const char *begindate,int days,char *enddate) {
    int ret=0;
    double second = 0;

    ret=datetime2second(begindate, "YYYYMMDD", &second);
    if(ret)
        return ret;
    second += days * 24 * 60 * 60;
    ret=second2datetime(second,enddate, "YYYYMMDD");
    if(ret)
        return ret;
    return 0;
}
void getNextShowCardNo(char *curshowcardno,int nextcnt,char *nextshowcardno) {
    char tmp[20]="";
    int len=strlen(curshowcardno);
    double curno=atof(curshowcardno);
    double nextno=curno+nextcnt;
    sprintf(tmp,"%.lf",nextno);
    int curnolen=strlen(tmp);
    int i=0;
    for(i=0; i<len-curnolen; i++)
        nextshowcardno[i]='0';
    strcpy(&(nextshowcardno[i]),tmp);
}
//typedef unsigned short uint16;

static const unsigned int  crc16_tab[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

static uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len) {
    uint16 crc;
    unsigned char b, da;
    uint16 charcnt;

    crc = 0;
    charcnt = 0;
    while (len--) {
        da = (unsigned char)(crc / 256); /* 以8位二进制数的形式暂存CRC的高8位 */
        crc *=256;						 /* 左移8位，相当于CRC的低8位乘以 */
        b = pBuf[charcnt];				 // 新移进来的字节值
        crc ^= crc16_tab[da ^ b];		 /* 高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */
        charcnt++;
    }
    return crc;
}

static RIJNDAEL_KS ks;
int decrypt_elec_card_pwd(int cut_id,const char seedkey[32],const char mpwd[64],char pwd[8]) {
#if 0
    char temp[17],temp1[17],buf[17];
    char encrypt_seed[65];
    unsigned char ivec[16]="";
    unsigned char radom_seed[4];
    //keyInstance key_inst;
    //cipherInstance cipher_inst;
    int i,ret;
    static const int max_pwd_len = 8;


    //memset(&key_inst,0,sizeof key_inst);
    //memset(&cipher_inst,0,sizeof cipher_inst);
    //printf("cut_id[%d],seedkey[%s],mpwd[%s]\n",cut_id,seedkey,mpwd);

    // 读取随机种子
    memcpy(temp,mpwd,8);
    memset(temp1,0,sizeof temp1);
    for(i = 0; i < 8; i+=2) {
        memcpy(temp1,temp+i,2);
        radom_seed[i/2] = (unsigned char)strtoul(temp1,NULL,16);
    }

    //printf("radom_seed[%s]\n",radom_seed);
    // 计算种子密钥
    memset(encrypt_seed,0,sizeof encrypt_seed);
    for(i = 0; i < 32; ++i)
        encrypt_seed[i] = seedkey[i] ^ radom_seed[i%4];
    CalcMD5((unsigned char*)encrypt_seed,32,(unsigned char*)temp);
    memset(encrypt_seed,0,sizeof encrypt_seed);
    for(i = 0; i < 16 ; ++i)
        sprintf(encrypt_seed+i*2,"%02X",(unsigned char)temp[i]);

    //printf("encrypt_seed[%s]\n",encrypt_seed);

    rijndael_init((unsigned char*)encrypt_seed, 16, &ks);

    memset(temp1,0,sizeof temp1);
    memset(temp,0,sizeof temp);
    for(i = 0; i < 32; i+=2) {
        memcpy(temp1,mpwd+12+i,2);
        temp[i/2] = (unsigned char)strtoul(temp1,NULL,16);
    }
    memset(ivec,0,sizeof(ivec));

    //printf("temp[%s]\n",temp);

    ret = rijndael_cbcdecode((unsigned char*)temp, (unsigned char*)temp1,ivec,&ks);			//解密
    if(ret)
        return ret;
    /*
    // 解密
    if(makeKey(&key_inst,DIR_DECRYPT,128,(char*)encrypt_seed)==FALSE)
    {
    	return -1;
    }
    if(cipherInit(&cipher_inst,MODE_CBC,NULL)==FALSE)
    {
    	return -1;
    }

    memset(temp1,0,sizeof temp1);
    memset(temp,0,sizeof temp);
    for(i = 0;i < 32; i+=2)
    {
    	memcpy(temp1,mpwd+12+i,2);
    	temp[i/2] = (unsigned char)strtoul(temp1,NULL,16);
    }
    memset(temp1,0,sizeof temp1);
    len = blockDecrypt(&cipher_inst,&key_inst,(BYTE*)temp,16*8,(BYTE*)temp1);

    */
    for(i=0; i < max_pwd_len; ++i)
        buf[i] = temp1[i] ^ radom_seed[i%4];

    //printf("before trim buf[%s],len[%d]\n",buf,strlen(buf));
    trim(buf);
    //printf("after trim buf[%s],len[%d]\n",buf,strlen(buf));
    // 计算密码
    sprintf(temp,"%08X",cut_id);
    for(i = 0; i < max_pwd_len; ++i)
        temp1[i] = temp1[i] ^ temp[i];
    // CRC 校验
    uint16 crc = GenerateCRC16((unsigned char*)temp1,max_pwd_len);
    memset(temp,0,sizeof temp);
    sprintf(temp,"%04X",crc);
    if(strncmp(temp,mpwd+8,4)) {
        return -2;
    }

    memcpy(pwd,buf,max_pwd_len);
    //printf("pwd[%s],len[%d]\n",pwd,strlen(pwd));
    //memcpy(pwd,temp1,max_pwd_len);
#endif
    return 0;
}

int encrypt_elec_card_pwd(int cut_id,const char seedkey[32],const char pwd[8],char mpwd[64]) {
#if 0
    static const int max_pwd_len = 8;
    //keyInstance key_inst;
    //cipherInstance cipher_inst;
    unsigned char ivec[16]="";
    unsigned char buf[16] = "";
    char temp[16] = "";
    char temp2[16] = "";
    char pwd_str[max_pwd_len*2+1] = "";
    unsigned char decrypt_buf[16] = "";
    char encrypt_seedkey[64] = "";
    unsigned char decrypt_str[64] = "";
    time_t radom_seed = time(NULL);
    int ret,i,j,pwd_len;
    //memset(&key_inst,0,sizeof key_inst);
    //memset(&cipher_inst,0,sizeof cipher_inst);

    for(i = 0; i < max_pwd_len; ++i) {
        switch(pwd[i]) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '\'':
        case '"':
        case '%':
        case '_':
            return -2;
        default:
            break;
        }
    }
    pwd_len = strlen(pwd);
    if(pwd_len > max_pwd_len)
        return -3;
    // 取4位随机种子
    srand((unsigned int)radom_seed);
    for(i = 0; i < 4; ++i)
        buf[i] = (unsigned char)(rand() % 0xFF);

    // 密码不足8位右补空格

    memcpy(pwd_str,pwd,pwd_len);
    //printf("test1[%s]\n",pwd_str);
    for(i=pwd_len; i < max_pwd_len; ++i)
        pwd_str[pwd_len] = ' ';
    for(i=0; i < max_pwd_len; ++i)
        pwd_str[i] ^= buf[i%4];
    //printf("test2[%s]\n",pwd_str);
    // 加密的密钥
    for(i = 0; i < max_pwd_len; ++i)
        pwd_str[max_pwd_len+i] = pwd_str[i] | (!temp[i]);
    memcpy(pwd_str+max_pwd_len,pwd_str,max_pwd_len);
    pwd_str[16] = '\0';
    //printf("test3[%s]\n",pwd_str);
    // 计算种子密钥
    memset(encrypt_seedkey,0,sizeof encrypt_seedkey);
    for(i = 0; i < 32 ; ++i)
        encrypt_seedkey[i] = seedkey[i] ^ buf[i%4];

    //printf("test4[%s]\n",encrypt_seedkey);
    CalcMD5((unsigned char*)encrypt_seedkey,32,(unsigned char*)temp);
    memset(encrypt_seedkey,0,sizeof encrypt_seedkey);
    for(i = 0,j = 0; i < 16; ++i)
        j += sprintf(encrypt_seedkey+j,"%02X",(unsigned char)temp[i]);
    //printf("test5[%s]\n",encrypt_seedkey);
    rijndael_init((unsigned char*)encrypt_seedkey, 16, &ks);

    // 计算CRC
    sprintf(temp,"%08X",cut_id);
    memset(temp2,0,sizeof temp2);
    for(i = 0; i < max_pwd_len; ++i)
        temp2[i] = pwd_str[i] ^ temp[i];
    uint16 crc = GenerateCRC16((unsigned char *)temp2,max_pwd_len);
    sprintf(temp,"%04X",crc);
    memcpy(buf+4,temp,4);
    //printf("test6[%s]\n",pwd_str);
    memset(ivec,0,sizeof(ivec));
    ret= rijndael_cbcencode((unsigned char*)pwd_str, decrypt_str,ivec,&ks);			//加密
    if(ret)
        return ret;
    //printf("test7[%s]\n",decrypt_str);
    // 8 个字符种子
    for(i = 0; i < 4; ++i)
        sprintf(mpwd+i*2,"%02X",(unsigned char)buf[i]);
    // 4 个字符CRC
    //printf("test8[%s]\n",mpwd);
    memcpy(mpwd+8,temp,4);
    //printf("test10[%s]\n",mpwd);
    // 8 个字符密码
    for(i = 0; i < 16; ++i)
        sprintf(mpwd+12+i*2,"%02X",decrypt_str[i]);
    //printf("test11[%s]\n",mpwd);
#endif
    return 0;
    /*

    // 进行加密
    if(makeKey(&key_inst,DIR_ENCRYPT,128,encrypt_seedkey)==FALSE)
    {
    	return -1;
    }
    if(cipherInit(&cipher_inst,MODE_CBC,NULL)==FALSE)
    {
    	return -1;
    }
    len = blockEncrypt(&cipher_inst,&key_inst,(unsigned char*)pwd_str,16*8,decrypt_str);
    if(len == 16*8)
    {
    	// 8 个字符种子
    	for(i = 0;i < 4; ++i)
    		sprintf(mpwd+i*2,"%02X",(unsigned char)buf[i]);
    	// 4 个字符CRC
    	memcpy(mpwd+8,temp,4);
    	// 8 个字符密码
    	for(i = 0;i < 16;++i)
    		sprintf(mpwd+12+i*2,"%02X",decrypt_str[i]);
    	//mpwd[28] = '\0';
    	return 0;
    }
    */
}
void str2hex(char *str,int len,char *hex) {
    int i;
    char temp[3];
    memset(temp,0,sizeof temp);
    for(i = 0; i < len; i+=2) {
        memcpy(temp,str+i,2);
        hex[i/2] = strtoul(temp,NULL,16);
    }
}

int str2bcd(char *str,int len,char *bcd) {
    int i;
    for(i = 0; i < len; i+=2) {
        if(str[i] < '0' || str[i] >'9')
            return E_INPUT_DATA_INVAILD;
        if(str[i+1] < '0' || str[i+1] >'9')
            return E_INPUT_DATA_INVAILD;

        bcd[i/2] = (str[i] - '0') << 4;
        bcd[i/2] += (str[i+1] - '0');
    }
    return 0;

}

char *replace(char *source,char *sub,char *rep) {
    char   *result;
    /*pc1   是复制到结果result的扫描指针*/
    /*pc2   是扫描 source 的辅助指针*/
    /*pc3   寻找子串时,为检查变化中的source是否与子串相等,是指向sub的扫描指针 */
    /*找到匹配后,为了复制到结果串,是指向rep的扫描指针*/
    char   *pc1,   *pc2,   *pc3;
    int   isource,   isub,   irep;
    isub   =  strlen(sub);     /*对比字符串的长度*/
    irep   =  strlen(rep);     /*替换字符串的长度*/
    isource=  strlen(source);  /*源字符串的长度*/
    if(NULL == *sub)
        return strdup(source);
    /*申请结果串需要的空间*/
    result   = (char *)malloc(( (irep > isub) ? (float)strlen(source) / isub* irep+ 1:isource ) * sizeof(char));
    pc1   =   result; /*为pc1依次复制结果串的每个字节作准备*/
    while(*source   !=   NULL) {
        /*为检查source与sub是否相等作准备,为pc2,pc3 赋初值*/
        pc2   =   source;
        pc3   =   sub;
        /* 出循环的（任一）条件是：
                 *   *pc2  不等于 *pc3  （与子串不相等）
                 *   pc2   到源串结尾
                 *   pc3   到源串结尾  （此时,检查了全部子串,source处与sub相等）
                 *****************************************************/
        while(*pc2   ==   *pc3   &&   *pc3   !=   NULL   &&   *pc2   !=   NULL)
            pc2++,   pc3++;
        /* 如果找到了子串,进行以下处理工作*/
        if(NULL   ==   *pc3) {
            pc3   =   rep;
            /*将替代串追加到结果串*/
            while(*pc3   !=   NULL)
                *pc1++   =   *pc3++;
            pc2--;
            source   =   pc2;
            /*     检查 source与sub相等的循环结束后，
                        * pc2 对应的位置是在 sub 中串结束符处。该是源串中下一个位置。
                        * 将  source 指向其前面一个字符。
                        ***************************************************/
        } else /*如果没找到子串,下面复制source所指的字节到结果串*/
            *pc1++ = *source;
        source++; /* 将source向后移一个字符*/
    }
    *pc1   =   NULL;
    return   result;
}

