#ifndef _YUCHUANDEF_H_
#define _YUCHUANDEF_H_

#include "ksglobal.h"

#pragma pack(1)
typedef struct 	
{	
	unsigned char Start_Time; 				// 记费总时间		
	unsigned char Use_Uint;   				// 计费单位		
	unsigned char Time_Money; 				// 收费金额		
}One_Rate;

typedef struct 
{	
	unsigned char fee_count; 				// 费率个数		
	One_Rate  N_Rate[3]; 				// 多个费率组 ,目前有效3级
}Multilevel_Rate;
	
typedef struct 
{
	unsigned char  System_Flag;				//系统工作模式（实时0x11/常开0x22/维护0x33）
	unsigned char  Use_Mode;				//扣费工作模式（计量0x44/计时0x55）
	unsigned char  PassWordRead[8];				//用户卡密码1
	unsigned char  PassWordWrite[8];			//用户卡密码2
	unsigned char  Use_Sector;				//用户卡使用的钱包
	unsigned char  En_Card_Type[4];				//允许使用的卡类	
	Multilevel_Rate Rate[20];            		//单次多阶费率模式（目前支持20类）
}JS_FEE_RATE;

typedef struct                                  		//记录指针结构体
{
	unsigned  char  Record_Flag ;				//存储状态（正常0x00/满0x33）
	unsigned  long 	Record_All_Number ;			//设备总存储条数
	unsigned  long  Record_Get_Number ;			//已采集总条数
	unsigned  long  Record_Save_Number ;			//已记录总条数
	unsigned  char  Reserved;				//保留（0x00）
}JS_REC_INFO;

typedef struct                                  		//消费记录结构体
{
	unsigned long Record_Number;				//记录号
	unsigned long User_NO;					//用户卡流水号
	unsigned long User_Card_Value;				//用户卡卡余额
	unsigned long User_Used_Value;				//用户卡消费额
	unsigned long Used_Address;				//用户卡交易设备号
	unsigned long Used_Times;				//用户卡交易次数
	unsigned char Used_purse;				//用户卡钱包号
	unsigned char Used_Time[6];				//消费时间
	unsigned char DEV_UID[4];				//设备的物理ID（全球唯一）
	unsigned char Used_Flag;				//记录状态字（正常记录0x00）
}JS_RECORD;

#pragma pack()


DCLR_DLLFUNC(HANDLE, OpenCommAuto,(int CommPort,int BaudVal));
DCLR_DLLFUNC(int,CloseComm,(HANDLE icdev));
DCLR_DLLFUNC(int,JS_GET_RECORD,(HANDLE icdev,int Node_Addr,unsigned long REC_Number,unsigned long Device_UID,unsigned char *Woke_Flag,JS_RECORD &Record,int COM_time));
DCLR_DLLFUNC(int,JS_GET_APPOINTED_RECORD,(HANDLE icdev,int Node_Addr,unsigned long REC_Number,unsigned long Device_UID,JS_RECORD &Record,int COM_time));
DCLR_DLLFUNC(int,JS_SET_Black_Version,(HANDLE icdev,int Node_Addr,unsigned char *ver_data,unsigned long Device_UID,int COM_Time));
DCLR_DLLFUNC(int,JS_GET_Black_Version,(HANDLE icdev,int Node_Addr,unsigned char *ver_data,unsigned long Device_UID,int COM_Time));
DCLR_DLLFUNC(int,JS_SET_Black,(HANDLE icdev,int Node_Addr,unsigned long Device_UID,unsigned char *Black_Data,int COM_Time));
DCLR_DLLFUNC(int,JS_GetNodeTime,(HANDLE icdev,int Node_Addr,unsigned char *datetime,int COM_Times));
DCLR_DLLFUNC(int,JS_SET_ONE_Black,(HANDLE icdev,int Node_Addr,unsigned long Black_Card_Number,unsigned long Device_UID,unsigned char *Black_Data,int COM_Time));


#define DAS_OK				 0					//数据接收正常
#define write_PASS			 0					//下载程序成功
#define Comm_Init_Err		-1					//串口初始化错误
#define CommPort_Err		-2					//端口错误
#define Chksum_Err			-3					//通讯数据效验错误
#define Rev_Data_Err		-4					//接收数据失败
#define TIME_OUT_Err		-5					//通讯超时错误
#define Para_Err			-6					//参数错误
#define Send_Data_Err		-7					//发送数据失败
#define Get_status_Err		-9					//接收状态位错误
#define No_Data_Return		-11					//没有数据返回
#define No_BIN_Files		-21					//没有数据返回
#define Read_Files_ERR		-22					//没有数据返回
#define CRC_ERR				-26					//CRC效验错误
#define Rev_LEN_Err			-27					//接收长度溢出
#define Password_Err		-28					//授权密码错误
#define Password_Para_Err   -29					//密码格式错误
#define Encrypt_Err			-30					//数据加密错误
#define Wrong_DEV_Err		9					//设备物理ID号不符
#define No_Record_Err		0x11				//没有流水

#endif //_YUCHUANDEF_H_
