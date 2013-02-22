/* ----------------------------------------------------------
 * 程序名称：bank_gd.cpp
 * 创建日期：2007-08-2 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：广州大学城中国银行和工商银行的头文件定义
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#ifndef	__BANK_GD_H__
#define	__BANK_GD_H__

#include "tcp.h"

#pragma once

#define		BANK_ZGYH							3
#define		BANK_JSYH							2
#define		BANK_GSYH							1

//**********中国银行的交易代码********//
#define		BANK_ZGYH_TRADE_CODE_TRANS			"DXRB"		//转账
#define		BANK_ZGYH_TRADE_CODE_DETRANS		"DXRV"		//冲正
//**********工商银行的交易代码*******//

#define		BANK_GSYH_TRADE_CODE_LOGIN			"31"		//签到
#define		BANK_GSYH_TRADE_CODE_LOGOUT		"32"		//签退
#define		BANK_GSYH_TRADE_CODE_COMPARE		"33"		//对帐
#define		BANK_GSYH_TRADE_CODE_TRANS			"1 "		//转账
#define		BANK_GSYH_TRADE_CODE_DETRANS		"2 "		//冲正
#define		BANK_GSYH_TRADE_CODE_FEE			"02"		//转账
#define		BANK_GSYH_TRADE_CODE_DEFEE			"12"		//冲正
#define		BANK_GSYH_TRADE_CODE_QUERYBALANCE	"5 "		//查询余额

//******************************************************************//

#define		BANK_GSYH_PINKEY_SYN_STR	"12345678"	//银行PIN密钥同步指示串
#define		BANK_GSYH_MACKEY_SYN_STR	"12345678"	//银行MAC密钥同步指示串




#define BANK_ZGYH_MERCH_NO "gzschool"
#define BANK_GSYH_ZONE_NO_GZ	"3602"
#define BANK_GSYH_ZONE_NO_ZH	"2002"
#define BANK_GSYH_TYPE_SCHOOL	"11"
#define BANK_GSYH_MERCH_NO "73213"

#pragma pack(1)
//报头
typedef struct  
{
	char	Ret[4];					//返回码; 非0000为不成功
	char	TranCode[4];			//交易码; DXRB:转账,DXRV:冲正
	char	BrnId[7];				//网点号; 空格
	char	TmlId[2];				//终端号; 空格
	char	TelId[2];				//柜员号; 空格
	char	Filer1[3];				//预留项;
	char	Mchno_len;				//固定值; 0x08
	char	Merch_no[8];			//单位编码;  必填
	char	Mch_name[24];			//单位名称;空格
	char	Errcd[7];				//错误代码;
	char	ErrMsg[60];				//错误信息;
	char	LocalNo[20];			//本地流水号;
	char	BankNo[8];				//银行流水号;
	char	Filer2[50];				//预留;

}BANK_ZGYH_TRADE_STRUCT_HEAD;

//--------------------
//转账请求
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//校园卡帐号
	char	BankCard[30];			//银行卡号
	char	CardType;				//卡类型；C信用卡,D借记卡
	char	TranMoney[13];			//交易金额
	char	PinBlock[16];			//预留
	char	TpkUdlmk[16];			//预留
}BANK_ZGYH_TRADE_STRUCT_TRANS_REQ;

//转账应答
typedef struct  
{	
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//校园卡帐号
	char	BankCard[30];			//银行卡号
	char	CardType;				//卡类型；C信用卡,D借记卡
	char	TranMoney[13];			//交易金额
	char	PinBlock[16];			//预留
	char	TpkUdlmk[16];			//预留
	char	XykSqh[7];				//信用卡授权号
	char	LocalNo[20];			//本地流水号
}BANK_ZGYH_TRADE_STRUCT_TRANS_ANS;

//冲正请求
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//校园卡帐号
	char	BankCard[30];			//银行卡号
	char	CardType;				//卡类型；C信用卡,D借记卡
	char	TranMoney[13];			//交易金额
	char	PinBlock[16];			//预留
	char	TpkUdlmk[16];			//预留
	char	XykSqh[7];				//信用卡授权号
	char	OldLocalNo[20];			//原本地流水号

}BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ;

//冲正应答
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//校园卡帐号
	char	BankCard[30];			//银行卡号
	char	CardType;				//卡类型；C信用卡,D借记卡
	char	TranMoney[13];			//交易金额
	char	PinBlock[16];			//预留
	char	TpkUdlmk[16];			//预留
	char	XykSqh[7];				//信用卡授权号
	char	OldLocalNo[20];			//原商户流水号

}BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS;
///////////////////////////工商银行接口结构///////////////////////////////



#pragma pack(1)

typedef struct  
{
	char    RetCode[2] ;		//交易返回码;
   	char    ZoneNo[5]  ;            //地区编号;广州:3602,珠海:2002;
	char    BusiType[9];            //交易类型;11:校园卡
	char    TranCode[2];		//交易类型;1:转帐,2:取消,3:余额查询
	char    TranFlag[1];            //交易标志;0:正交易,1:反交易
	char	BankCardNo[30];			//银行卡号;借方帐号，清算时为学校帐号
	char	TranMoney[10];			//交易金额;
	char	MoneyType[3];			//货币种类;001:人民币
	char    TranDate[8];           //交易日期;YYYY-MM-DD
	char    TranTime[6];			//交易时间;HHMMSS
	char	PwdFlag[1];				//密码检查标志;0:不检查,1:检查
	char	PwdType[1];				//密码(类型)标志,0:明文,1:密文
	char	BankCardPwd[8];			//密码
	char	LocalSn[8];			//本地交易流水号;
	char	LocalDetranSn[8];		//冲正时填入的原转帐交易流水号
	char	BankSn[8];			//银行流水号
	char	MercAccount[5];			//圈存时为中山大学商户号,清算时为商户的商户号
	char	MercAccountCode[2];		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
	char	GDCAccount[10];			//校园卡号;
	char	PosNo[5];				//圈存机号;
	char	AgentPercent[9];		//清算时的代理提成百分比
	char	AgentType[2];			//业务种类,01:圈存,02:消费;
	char	Filter[64];				//空格补位

}BANK_GSYH_TRADE_STRUCT;
#pragma pack()
/*
//请求
typedef struct  
{
	char	TradeCode[2];	//交易代码,参见宏定义.
	char	RetCode[2];		//交易结果,
	char	TradeDate[8];					//交易日期	YYYYMMDD
	char	TradeTime[8];					//交易时间	HHMMSS
	char	CustAccountNo[10];				//校园卡帐号，后补空格
	char	BankCardNo[20];					//银行卡号,后补空格
	char	TransMoney[9];					//转账金额，xxxxxx.xx格式，前补空格
	char	Balance[9];						//余额，	xxxxxx.xx格式，前补空格
	char	BankCardPwd[16];				//银行卡密码
	char	CustSn[8];						//校园端流水号
	char	BankSn[8];						//银行流水号
	char	CustNo[16];						//学校代号，后补空格
	char	AutoFlag;						//自动转账标志,'0':自助，'1':自动
	char	PINKeySynFlag[16];				//密码同步标志
	char	MACKeySynFlag[16];				//校验同步标志
	char	MAC[8];							//校验
}

//================以下部分 WangYanBin 2002.8.18 为中山大学而作个性化改动===================
  中山大学接口数据说明:
    1.仅有一个结构,兼容全部交易,全部为文本结构(ASCII码)
	2.金额右靠前补零,其余项目左靠又补空格
	3.交易返回码说明:-------------------------
	                 | 00 | 成功             |
					 | 01 | 账户挂失         |
					 | 02 | 账户错           |
					 | 03 | 余额不足         |
					 | 04 | 账户密码错误     |
					 | 98 | 处理超时         |
					 | 99 | 其他错误         |
					 -------------------------

	响应
typedef struct {
	char	TradeCode[2];	//交易代码,参见宏定义.
	char	RetCode[2];		//交易结果,
	char	TradeDate[8];					//交易日期	YYYYMMDD
	char	TradeTime[8];					//交易时间	HHMMSS
	char	CustAccountNo[10];				//校园卡帐号，后补空格
	char	BankCardNo[20];					//银行卡号,后补空格
	char	TransMoney[9];					//转账金额，xxxxxx.xx格式，前补空格
	char	Balance[9];						//余额，	xxxxxx.xx格式，前补空格
	char	BankCardPwd[16];				//银行卡密码
	char	CustSn[8];						//校园端流水号
	char	BankSn[8];						//银行流水号
	char	CustNo[16];						//学校代号，后补空格
	char	AutoFlag;						//自动转账标志,'0':自助，'1':自动
	char	PINKeySynFlag[16];				//密码同步标志
	char	MACKeySynFlag[16];				//校验同步标志
	char	MAC[8];							//校验
	}
	*/


///////////////////////////建设银行接口结构///////////////////////////////

#define BANK_JSYH_TRADE_CODE_TRANS_REQ 		"0200"
#define BANK_JSYH_TRADE_CODE_TRANS_ANS 		"0210"
#define BANK_JSYH_TRADE_CODE_DETRANS_REQ 	"0400"
#define BANK_JSYH_TRADE_CODE_DETRANS_ANS 	"0410"

#define BANK_JSYH_MERCH_NO "334014"

/* message size */
#define  STAND    0   
//#define	 MAXMSGSIZE  2560
/* transaction type */
#define  BANK_QUERY_REQ            0
#define  BANK_QUERY_RSP           (BANK_QUERY_REQ + 1)
#define  BANK_TRANS_REQ            2
#define  BANK_TRANS_RSP           (BANK_TRANS_REQ + 1)
#define  BANK_DETRANS_REQ        4
#define  BANK_DETRANS_RSP       (BANK_DETRANS_REQ + 1)

#define  TRANS_TYPE 8
#define  transTypeSize 4
#define  SHM_TXNDSC_IDX 0x00
#define  MAXBUFSIZE 2500
//#define  8583_

#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif

typedef struct
{
	char length[4];
    char pkgtyp[1];         //报文种类 0为8583包，1为非8583包
    char msgtyp[4];	    // 
    char prccde[6];	    		//	880108  488833 488833
    char acqInstID[8];      //4446301 收单机构号统一定为8位,不足后补空格
    char termID[8];	    //	COLLEGE2
    char trcno[6];          //我的流水号   不足6位前补0
    char custyp[2];         //OV 帐户种类
    char cusidt[25];        //校园卡卡号   不足后补空格
    char apcode[2];         //01       01_RB,03_AC
    char srvuID[8];	    //44630021	公司代码
    char rspcde[2];	    //	00
    char pkgseq[2];         //01      报文序号 
    char filler[6];         //null    附加域  
    char msgLen[4];         //包长度  不足4位前补0
    char msg[MAXBUFSIZE];   //包体    数据区
}H_MSG8583;


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

