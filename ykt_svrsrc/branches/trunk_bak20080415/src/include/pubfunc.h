#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <syslog.h>

#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "account.h"

#ifndef  __PUBFUNC_H_
#define  __PUBFUNC_H_
//#ifdef __cplusplus
//extern "C" {
//#endif

void getpos(char *v_filename,int v_lineno);
void errlog(int level,char *fmt,...);
extern char gszExeName[128];
extern int  giLogClass;

#define des2src(des,src)  	strncpy(des,src,sizeof(des)-1),ntrim(des,sizeof(des))

int amtcmp(double amt1,double amt2);

/*
 *
            writelog  level  定义    闻剑

LOG_EMERG   指定紧急消息（LOG_EMERG）。这些消息并非分发给所有用户。可以将 LOG_EMERG 优先级消息记录到单独文件备查。
LOG_ALERT   指定重要的消息（LOG_ALERT），如严重的硬件错误。这些消息分发给所有用户。
LOG_CRIT    指定不列为错误的关键消息（LOG_CRIT），如不适当的登录尝试。LOG_CRIT 和较高优先级消息会发送到系统控制台。
LOG_ERR     指定表示错误情况的消息（LOG_ERR），例如失败的磁盘写入。
LOG_WARNING 指定反常但可恢复的情况的消息（LOG_WARNING）。
LOG_NOTICE  指定重要的信息性消息（LOG_NOTICE）。没有指定优先级的消息会映射为此优先级的消息。
LOG_INFO    指定信息性消息（LOG_INFO）。这些消息可以废弃，但它们在分析系统是很有用。
LOG_DEBUG   指定调试消息（LOG_DEBUG）。这些消息可以废弃。

 *
 */

#define writelog getpos(__FILE__,__LINE__),errlog

//trim: trim string left space and right space
char *trim(char *str);
//ltrim: trim string left space
char *ltrim(char *str);
//rtrim: trim string right space
char *rtrim(char *str);
char *ntrim(char *str,int len);
//getsystime,out date format:yyyymmdd
char* getsysdate(char *v_date);

//getsystime, out time format:hhmmss
char* getsystime(char *v_time);

//getsysdatetime, out time format:yyyymmddhhmmss
char* getsysdatetime(char v_time[15]);
//getdatetime, out time format:yyyy-mm-dd hh:mm:ss
char *getdatetime(char v_datetime[20]);
char *getsystimestamp(char *v_timestamp);
//函数功能：根据传入时间和秒，得到传入时间之前的时间
//输入：cur_time  char[7] 传入时间格式为：hhmmss
//输入：second    int	   时间间隔		单位为秒
//输出：pre_time  char[7] 距cur_time之前second秒的时间，格式为hhmmss
int GetPreTime(char cur_time[7],int second,char pre_time[7]);
//函数功能：根据传入时间和秒，得到传入时间之前的时间
//输入：cur_time  char[7] 传入时间格式为：hhmmss
//输入：second    int	   时间间隔		单位为秒
//输出：next_time  char[7] 距cur_time之后second秒的时间，格式为hhmmss
int GetNextTime(char cur_time[7],int second,char next_time[7]);

//函数功能：根据两个传入时间，得到两个传入时间之间的间隔时间
//输入：tim1  char[15] 传入时间格式为：yyyymmddhhmmss
//输入：tim2  char[15] 传入时间格式为：yyyymmddhhmmss
//输出：second   double*	   时间间隔		单位为秒

int DiffTime(char time1[],char time2[],double* second);
//	getdbtime,out date format:yyyy-mm-dd
//	var length: v_date[11];
char *getdbdate(char *date);
//	getdbtime,out date format:hh.mm.ss
//	var length: v_time[16];
char *getdbtime(char *v_time);
//	getdbtimestamp,out date format:yyyy-mm-dd-hh.mm.ss
//	var length: v_timestamp[27];
char *getdbtimestamp(char *v_timestamp);

int UssetConvert(int nType,char *usset,char *menuset,int nUssetSize,int nMenusetSize);
//int getNewVocNo(int iType,char *sVocNo);
//int getNewActNo(char *sNewActno);
//int IsActnoInvalid(char *actno);

//in  : 	origin,datetime,format:yyyymmddhhmmss
//out :	timestamp,format:yyyy-mm-dd hh:mm:ss
int ConvertDate(char *origin,char *timestamp);
//author:xunzhang huang
//date:2004-08-30 17：11
//flag==0 yyyy-mm-dd  -->>  yyyymmdd
//flag==1 yyyymmdd    -->>  yyyy-mm-dd
int ConvertDateLen(char *out, const char *in, int flag);

//flag=0,Encode,	clearpwd to secretpwd,	min length of secretpwd is 29
//flag=1,Decode,	secretpwd to clearpwd,	min length of secretpwd is 29

int EncodePwd(char *key,char *clearpwd,char *secretpwd,int flag);

int GetInitKey(char *s_init_key,char *key);

int GetDynaKey(char *Dyna_Key);

int CheckInitKey(char *s_init_key,int subsystem_id,char *key);

int GetReadCardKey(int device_id,int subsystem_id,char *read_card_key,char *key);


int dateConvert(char *str, char *buf);

//函数功能	: 根据格式转换为ｄｂ２类型日期
//输入		:   old_date  char[11]　　日期
//输入		:   old_fmt 	 常量字符串　日期格式描述，现在格式为:"YYMMDD","YYYYMMDD"
//输出		:   new_date  char[11]　DB2 日期　yyyy-mm-dd
//返回值	:   0	 --成功
//返回值	:  非０--相应的错误码
int str2dbdate(char *new_date,char *old_date,char *old_fmt);

//函数功能	: 根据格式转换为ｄｂ２类型时间
//输入		:   old_time  char[11]　　时间
//输入		:   old_fmt 	 常量字符串　时间格式描述，现在格式为:"HHMMSS"
//输出		:   new_time  char[11]　DB2 时间　hh:mm:ss
//返回值	:   0	 --成功
//返回值	:  非０--相应的错误码

int str2dbtime(char *new_time,char *old_time,char *old_fmt);
int str2dbtimestamp(char *new_timestamp,char *old_timestamp,char *old_fmt);
int IsInvalidDateTime(char *sdatetime,  char *fmt);
int datetime2second(char *datetime,char *fmt,double *second);
int second2datetime(double second,char *datetime,char *fmt);
int GetXmlValue(char value[],int size,char *key,char *buf);
void  AddXmlItemDbl(char *buf,char *key,double value);
void  AddXmlItemInt(char *buf,char *key,int value);
void  AddXmlItemStr(char *buf,char *key,char *value);
//生成显示卡号
int GetNewShowCardNo(char *sNewCardno,int iCustType,int iCardId);
//校验显示卡号是否有效
int IsShowCardNoInvalid(char *sCardno);
//四舍五入函数,保留num位小数
double D4U5(double value,int num);
int D2I(double value);

//韩海东添加，计算mac的方法
int	generate_mac(char* buf,int len,char* mac);

int	check_mac(char* buf,int len);

int GetValueFromFmtBuf(char* buf, char *separator,int pos,char *value);

int SpanOfDate(const char *start,const char *end);
int GetNextDay(const char start[9],int span,char next[9]);
int OffsetDatetime(const char begin_dt[13],int second,char end_dt[13]);

int DecodeHDPhyId(const char* encoded,char * text);
int EncodeHDPhyId(const char* text,char * encodeId);
int CheckPwdChar(const char* pwd,char newpwd[7]);
void CalcMD5(unsigned char* buf,unsigned int len,unsigned char md5[16]);
unsigned long  CardPhyIdHex2Dec(const char* phyid);

int CheckUserPswd(const char* input_pwd,const char* db_pwd);

void RealSleep(int secs);

void  InitDaemonProcess();
int StartAsDaemon();

int CheckCardStatus(char state[5]);

//////////////////////////////////////////
// 性能测试功能函数
typedef struct {
	pid_t current_id;
	struct timeval time_stamp;
	struct timeval start_stamp;
}time_probe_t;

int time_probe_now(time_probe_t *probe);
int time_probe_finish(time_probe_t *probe);
void time_probe_print(const time_probe_t *probe,const char *msg);

int startup_lock_file(const char *uni_identify);
int test_process_lock_file(const char *uni_identify);

int is_validate_sexno(char sexno);
int get_init_passwd_by_man_id(char *man_id,char *passwd);
#define  unlike_tbl_id(idval)  ((idval) > 0 ?  0 : 1)

//#ifdef __cplusplus
//}
//#endif
#endif
