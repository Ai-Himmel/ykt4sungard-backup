/****************************************************************************
*
*文件(File):         in_call.h
*
*修改(Modify):       2011/7/20 14:05:06
*
*作者(Author):       USER
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011/7/20 14:05:06           USER 
----------------------------------------------------------------------------
****************************************************************************/


#ifndef   in_call_h_2011_07_20_17_05_06_INCLUDED
#define   in_call_h_2011_07_20_17_05_06_INCLUDED
#include "api.h"
/*****wifi*******/
#include "WiFi/WiFi.h"
#include "WiFi/NaNoWiFiConst.h"
#include "WiFi/WiFiPubFuncs.h"
#include <unistd.h>
/***************/
typedef struct
{
	//unsigned char phyNo[8];	//物理卡号
	//unsigned char time[16];		//考勤时间
	//unsigned char cum_money[8];	//消费金额
	//unsigned char cum_date[8];		//消费日期
	//unsigned char cum_time[6];		//消费时间
	unsigned char num[6];	//学号
	unsigned char count[8];		//吃饭次数
//	unsigned char cum_date[8];		//消费日期
//	unsigned char cum_time[6];		//消费时间
}USER_INFO;	//用户数据结构
#define	NUM_OF_FUDAN	301

#define DATA_TABLE_NUM	1	//数据库表数量
#define ATTENDANCE_INDEX	0	//数据库表索引号（考勤数据库表）

#define	MAX_SEND_BUFFER	1000	//WIFI传送每次最多发送的数据字节数

#define	READ_CARD_SECOND	10	//读卡秒数
//EEPROM
#define EEPROM_OFFSET_SERVERIPADD	0	//EEPROM需要的偏移量的起始位置（服务器IP）（共16字节）
//#define EEPROM_OFFSET_WIFI_HANDLE	16	//用于wifi连接的句柄的起始位置（共2字节）
#define EEPROM_OFFSET_MAIN_KEY		18	//授权卡的主密钥起始位置（共8字节）
#define EEPROM_OFFSET_ADM_PSD		26	//管理员密码起始位置（共9字节）
#define EEPROM_OFFSET_ADM_CTRL		35	//管理员密码控制位（初始密码）起始位置（共1字节）
#define EEPROM_OFFSET_SERVERPORT	36	//服务器端口号起始位置（共8字节）
#define EEPROM_OFFSET_SERVERSSID	44	//服务器SSID起始位置（共16字节）
#define EEPROM_OFFSET_SEVPASSWORD	60	//服务器密码起始位置（共16字节）
//USB通信

/****************主函数***********************/
void main_task();		//主菜单
void debugFun(char* debugStr);	//debug函数
void adminPsd_init();	//管理员密码初始化
/****************主菜单功能***********************/
void workAttendance_task();	//考勤打卡
void consumption_task();	//消费
void funSet_task();			//机器设置菜单
void vstDatabase_task();	//数据查询菜单
void dataUpload_task();		//数据传输菜单
void discernID_task();		//身份识别菜单
void setAdmPsd_task();		//设置管理员密码
/****************数据传输菜单功能*****************/
void usb_upload_menu();		//usb数据上传菜单
void wifi_upload_menu();	//wifi数据上传菜单
void wifiInit_open();		//开机初始化WIFI
void db_to_str(unsigned char* buf, int bufMax, int cnt);	//数据库记录转字符串
/****************机器设置菜单功能*****************/
int setTime();				//时间设置
int setDate();				//日期设置
void Set_Auto_Poweroff();	//自动关机时间设置
void setBacklight();		//背光灯时间设置
void setKeybeeper();		//按键音设置
void getAuthorize();		//获取授权卡
char adminPassword();		//输入管理员密码
int	input_password(char *pPrompt,char *dBuf);	//密码输入
/****************数据查询功能*****************/
void db_check();			//检查数据库
void db_init_menu();		//初始化数据库（菜单调用）
void del_Allrecords();		//删除所有记录
void check_recordsCnt();	//查询已经记录的条数
void check_dbCapcity();		//检查可用容量
/****************EEPROM读写*******************/
char eeprom_read(unsigned char* readBuffer, unsigned short sizeLen, int romOffset);	//eeprom读
char eeprom_write(unsigned char* writeBuffer, unsigned short sizeLen, int romOffset);	//eeprom写
void shortTochar(unsigned short* sh, unsigned char* st);	//short转char数组
void charToshort(unsigned short* sh, unsigned char* s);	//char数组转short
/****************m1卡读写*****************/
char readM1Card(char (*card_r)());	//读M1卡框架
char readAuthorizeCard();		//读授权卡
//char workAttendance_xian() ;		//考勤记录(西科大)
//char workAttendanceTemp();		//考勤记录（大连海事临时版）
//char workAttendance_Dalian();		//考勤记录（大连海事）
char discernID();			//身份识别
void CalKeyA(unsigned char* ucSerialNo,unsigned char* ucWorkKey,unsigned char* ucKeyA);	//计算KEYA密钥
void	warning_beep();				//蜂鸣器
int calkeyAfromPSAM(char* keya, const char* phyNo);		//PSAM卡取keya
void discernID_Fudan();		//复旦自助餐识别身份
char discID_fudan();	//复旦自助餐识别身份
/********cpu卡消费***********/
int get_4byte_int(unsigned char *value_str);
void set_4byte_int(unsigned char *value_str,int num);
 void mydec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr);	//解压
 void myhex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int* iDecBUfLen);	//压缩
#if 0
char consumpionNM();		//内医消费
int	input_money(int line,int maxNum,int minNum,int minValue,int maxValue, char *pPrompt,int *retValue, char* dBuf)	;	//消费金额的输入
int myatomon(char* str);		//字符串转整数
char cpucardCum_neiyi(int money, int* leftMoney);	//内蒙古医科大学消费
 char cpuCard_init(unsigned char* phn);		//cpu卡初始化

 #endif
/*********************************************/
#endif   /*in_call_h_2011_07_20_17_05_06_INCLUDED*/
 
