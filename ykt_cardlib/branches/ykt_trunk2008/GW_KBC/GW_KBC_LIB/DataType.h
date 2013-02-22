#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_
#pragma once

#include "kbclt.h"

static char g_msg[1024] = "";		// 注意尽量给出缓存为 >=1024字节
static KBDCHandle g_gw_handle = NULL;		// KBDC全局句柄
static bool g_handle_flag = false;	// KBDC全局句柄标志

#pragma pack(1)
typedef struct _CheckBillSerial 
{
	int 	 serial_no;			//网络收费交易流水号
	int 	 customer_id;		//客户标识
	int	 	 card_id;			//交易卡号
	char 	 operate_date[11];	//发生日期
	char     operate_time[9];	//发生时间
	int      serial_state;      //流水状态，2表示入账成功(成功消费)，1表示//未有入账（超时情况记录）
	double   trade_fee;			//交易金额
	double   in_fee;			//入卡值
	double   out_fee;			//出卡值
	int	     device_id;			//交易发生设备ID号
	int      sys_id;			//外部系统标识，转账成功为0，不成功为1001(超
								//时记录)
	char     cut_name[61];		//客户名称
	char     stuemp_no[21];		//学工号
} CheckBillSerial;

typedef struct _CardInfo 
{
	int 	 card_id;			//交易卡号
	int 	 customer_id;		//客户号
	char     physical_no[9];	//物理卡号
	char     state_id[5];		//卡状态
	char     password[33];		//卡密码
} CardInfo;

typedef struct _CutInfo 
{
	int 	 customer_id;				//客户号
	char 	 cut_name[21];				//客户名称
	char     classdept_no[11];			//部门编号
	char     class_no[11];				//班级编号
	char     classdept_name[151];		//联系人部门或者班级名称
	char     stuemp_no[21];				//学工号
} CutInfo;
typedef struct _DataInfo              
{
	int      cut_id;                //客户ID号      
	char	 cut_name[21];			//客户名称
	char     class_no[11];			//班级
	char     classdept_no[11];		//部门编号
	char 	 classdept_name[151];	//联系人部门或者班级名称
	char     password[33];			//卡密码, 暂时作为保留字段
	char     state_id[5];			//卡状态, 保留字段
	char     stuemp_no[21];			//学工号
} DataInfo;

typedef struct _DataInfoEx              
{
	int      cut_id;                //客户ID号
	int		 card_id;				//交易卡号
	int		 cut_type;				//客户类别代码
	char     cut_type_name[21];		//客户类别名称
	char	 cut_name[21];			//客户名称
	char     sex[2];				//性别
	char     class_no[11];			//班级
	char     classdept_no[11];		//部门编号
	char 	 classdept_name[151];	//联系人部门或者班级名称
	char     password[33];			//卡密码, 暂时作为保留字段
	char     state_id[5];			//卡状态, 保留字段
	char     stuemp_no[21];			//学工号
	char     physical_no[9];		//物理卡号
} DataInfoEx;

typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						//用户卡使用权限类型（1--254）
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				//职务代码
	unsigned char ucCertificateNo[21];		//证件号码
	unsigned char ucDepartmentNo[11];		//部门编号
	unsigned char ucIdentifyNo[5];			//身份代码
	unsigned char ucSexNo[2];				//性别代码
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					//卡密码
	unsigned char ucLibraryNo[21];			//图书证号
	int Money;								//金额（分）
	unsigned char isFormat;					//是否格式化第一扇区
}TPublishCard;
#pragma pack()

#endif