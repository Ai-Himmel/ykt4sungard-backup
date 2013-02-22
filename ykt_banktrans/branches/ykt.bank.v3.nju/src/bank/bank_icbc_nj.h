/* ----------------------------------------------------------
 * 程序名称：bank_icbc_nj.h
 * 创建日期：2007-08-2 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：南京工商银行接口的头文件定义
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#ifndef	__BANK_ICBC_NJ_H__
#define	__BANK_ICBC_NJ_H__

#include "tcp.h"

#pragma once

#define		BANK_ZGYH							3
#define		BANK_JSYH							2
#define		BANK_GSYH							1

//**********工商银行的交易代码*******//
/*
. 交易类别定义
  -----------------------------------
  1. 测试--"test"    测试通讯
  2. 圈存--"circle"  即卡卡转账
  3. 缴费--"pay"     保留
  4. 查询--"query"   查询银行帐户余额
  5. 签到--"login"
  6. 签退--"logout"
  7. 换密--"passwd"  交换密码
  8. 对帐--"diff"		
  -----------------------------------
*/
#define	BANK_GSYH_TRADE_CODE_LOGIN		"login"		//签到
#define	BANK_GSYH_TRADE_CODE_LOGOUT		"logout"		//签退
#define	BANK_GSYH_TRADE_CODE_COMPARE		"diff"		//对帐
#define	BANK_GSYH_TRADE_CODE_TRANS		"circle"		//转账
#define	BANK_GSYH_TRADE_CODE_DETRANS		"detrans"		//冲正
#define	BANK_GSYH_TRADE_CODE_FEE			"pay"		//转账
#define	BANK_GSYH_TRADE_CODE_DEFEE		"de_pay"		//冲正
#define	BANK_GSYH_TRADE_CODE_QUERYBALANCE	"query"		//查询余额
const char BANK_ICBC_TRANSCODE_RELATION_QRY[] ="askrel";	//查询银行卡对应关系
const char BANK_ICBC_TRANSCODE_RELATION_ADD[]="addnew";	//添加银行卡对应关系
const char BANK_ICBC_TRANSCODE_RELATION_DEL[]="delete";	//删除银行卡对应关系

//******************************************************************//
/*
#define BANK_ZGYH_MERCH_NO "gzschool"
#define BANK_GSYH_ZONE_NO_GZ	"3602"
#define BANK_GSYH_ZONE_NO_ZH	"2002"
#define BANK_GSYH_TYPE_SCHOOL	"11"
#define BANK_GSYH_MERCH_NO "73213"
*/
const char  BANK_ICBC_RECEIVER[] = "njicbc";
const char  BANK_ICBC_SENDER[] = "nju";

#define BANK_GSYH_RECEIVER		"njicbc"
#define BANK_GSYH_SENDER   		"nju"

#pragma pack(1)
///////////////////////////工商银行接口结构///////////////////////////////
#pragma pack(1)
typedef struct 
{
    char  MsgLength[4];       // 数据包的总长度，十进制字符串表示 "0256"
    char  TradeType[6];       // 交易类别 具体定义见下

    char  Sender[7];	      // 发送方 具体定义见下
    char  Receiver[7];	      // 接收方 具体定义见下

    char  PINKeySynFlag[16];  // 密码加密密码 用于交换密码
    char  MACKeySynFlag[16];  // 校验密码     用于校验报文，先暂时不做   全0
    char  MAC[8];             // 校验         整个报文的校验，先暂时不做 全0 
} MSG_HEAD;

typedef struct 
{
    char  ReturnCode[4];      // 返回结果码 具体定义见下
    char  Message[24];	      // 返回代码描述
	
    char  TradeTime[14];      // 交易时间，YYYYMMDDHHMMSS 年月日时分秒
    char  SchoolTransSeq[16]; // 学校交易流水号 8位
    char  BankTransSeq[16];   // 银行交易流水号

    char  CampusCard[20];     // 校园卡卡号 5位数字
    char  BankAccNO[20];      // 银行帐号     不能含字符'|'
    char  StudentName[20];    // 学生姓名     不能含字符'|'
    char  StudentID[18];      // 学生身份证号 不能含字符'|'

    char  Amount[12];         // 交易金额  （到分）右对齐
    char  Balance[12];        // 银行卡余额（到分）右对齐
    char  BankCardPwd[16];    // 银行卡密码 需加密存放 如果不传密码，填0

    char  reserve[0];         // 备用字段 ;) 已凑足256字节，故不需要了！
} MSG_BODY;

typedef struct
{
	MSG_HEAD head;
	MSG_BODY body;
}MSG;

#pragma pack()


#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__


struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};

#pragma pack()
#endif

