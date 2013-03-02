/* ----------------------------------------------------------
 * 程序名称：bank_gd.cpp
 * 创建日期：2007-08-2 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：广州大学城中国银行和工商银行的头文件定义
 * ----------------------------------------------------------
 * 修改日期: 2008-03-26
 * 修改人员: 李翔
 * 修改描述: 新增云南信用合作社结构定义
 * 版本信息: 
 * 备注信息: 
 * ----------------------------------------------------------*/


#ifndef	__BANK_GD_H__
#define	__BANK_GD_H__

#include "tcp.h"
#include "bank.h"

#pragma once

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

/******************************云南信用合作社********************************
* 文件内容: 新增圈存数据结构定义说明
* 文件名:	Bank_gd.h
* 说明:		实现云南信用合作社
* 创建:		李翔
* 时间:		2008-03-26
* 修改原因: 增加云南信用合作社圈存报文结构说明
* 报文结构: 1. 报文头
*			2. 报文类型标识
*			3. 位图
*			4. 报文域
*****************************************************************************/

/*****************************************************************************
/* 函数宏定义
*****************************************************************************/
// 组合报文校验宏
#define  PACKETSTR(packet_str, des_str, split_vl) \
		{ \
			if (strlen(des_str)) { strcat(packet_str, des_str); strcat(packet_str, split_vl); } \
		}		

/*****************************************************************************
/* 报文头
*****************************************************************************/
typedef struct  
{
	char	packet_head_length[2];					//报文头长度: 8bit的二进制数, 该域值为46
	char	head_flag[2];							//头标识: 8bit的二进制数, 第一位0表示生产报文, 1表示测试报文, 后7位0000001
	char	packet_length[5];						//报文总长度: 4位定长的数字字符
	char	dest_id[12];							//目的ID: 11位定长数字字符数据, 本行填写01999999999
	char	src_id[12];								//源ID: 11位定长数字字符数据
	char	reserve_1[4];							//保留位: 24bit的二进制数, 对于节点发起的请求报文，该域的值为0
	char    batch_no[2];							//批次号: 8bit的二进制数, 0
	char	trade_info[9];							//交易信息: 8位字母和特殊数字字符
	char	user_info[2];							//用户信息: 该域为8bit的二进制数
	char	reject_code[6];							//拒绝码: 入网机构发来的报文中存在语法错误时,此时本域的第1位为0或1, 为0表示报文头域出错,
													//为1表示报文体域出错; 2-4 位表示出错的域；第5位表示错误的类型. 由于处理中心的原因导致报文被拒绝，
													//此时本域的第1位为2, 2-5 位表示错误的类型. 产生报文的时候为:"00000"
}BANK_YNXH_TRADE_STRUCT_HEAD;

/*****************************************************************************
/* 报文类型标识
*****************************************************************************/
#define		BANK_YNXH_TRADE_CODE_QUERYBALANCE		"0200"		//查询余额
#define		BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE	"0210"		//查询余额
#define		BANK_YNXH_TRADE_CODE_TRANS				"0200"		//转账请求
#define		BANK_YNXH_TRADE_CODE_ANS_TRANS			"0210"		//转账应答
#define		BANK_YNXH_TRADE_CODE_DETRANS			"0420"		//冲正请求
#define		BANK_YNXH_TRADE_CODE_ANS_DETRANS		"0430"		//冲正应答
#define		BANK_YNXH_TRADE_CODE_COMPARE			"0520"		//对账请求
#define		BANK_YNXH_TRADE_CODE_ANS_COMPARE			"0530"		//对账应答

/*****************************************************************************
/* 位图:
/* (1) 位图区可以包含两个位图也可以包含三个位图.
/* (2) 位图个数的选择根据交易类型而定: 位图一定义域2到域64, 位图二定义域66到
/*     域128, 位图三定义域130到域192
/* (3) 64字节+64字节+64字节
*****************************************************************************/

/*****************************************************************************
/* 整个报文=报文头+报文内容(交易类型+位图+报文域)
*****************************************************************************/
typedef struct  
{
	BANK_YNXH_TRADE_STRUCT_HEAD head;	//报文头
	char	msg_type[5];				//消息类型: 和报文类型标识同
	char	bit[17];					//位图: 128位, 16进制数据是16个字节
	char	main_account[22];			//主帐号: 2 个字节的长度值+最大19 个字节（数字字符）的主账号
	char	trade_deal_code[7];			//交易处理码: 6位定长数字字符
	char    trade_deal_time[11];		//交易传输时间: 10位数字符
	char    system_id[7];				//系统跟踪号: 6位数字符
	char    accept_card_time[7];		//受卡方所在地时间(hhmmss), 6位数字符
	char    accept_card_date[5];		//受卡方所在地日期(MMDD), 4位数字符
	char    shop_type[5];				//商户类型: 4字节
	char    service_input_code[4];		//服务输入方式码: 3字节
	char    service_terms_code[3];		//服务条件码: 2字节
	char    proxy_node_code[14];		//代理节点代码: 2个字节的长度值+最大11个字节的代理机构标识码
	char    send_node_code[14];			//发送节点代码: 2个字节的长度值+最大11个字节的代理机构标识码
	char    second_mag_tune[40];		//第二磁道数据: 2个字节+37个字节
	char    third_mag_tune[108];		//第三磁道数据: 3个字节的长度值+最大104个字节(字符)的第三磁道数据
	char    check_code[13];				//检索参考号
	char    device_phy[9];				//受卡机终端标识码: 8字节的物理ID号或者其他数字串
	char    mark[16];					//受卡方标识: 15字节
	char    address[41];				//受卡方地址名称: 40字节
	char    append_data[516];			//附加数据: 3个字节的长度值＋最大512个字节
	char    trade_money_code[4];		//交易货币代码: 3字节长度
	char    personal_mark[9];			//个人标识码数据: 64bit
	char    defalut_area[34];			//自定义域: 3个字节的长度值＋最大30个字节(字母、数字和特殊字符)的数据
	char    accept_node_code[14];		//接受节点标识码: 2个字节的长度值+最大11个字节的接收节点标识码, 在校园一卡通交易中，该域的值为01999999999
	char    packet_identity_code[9];	//报文鉴别码: 64bit
	char    answser_code[3];			//应答码: 2字节
	char    cur_balance[44];			//实际余额: 3个字节的长度值＋最大40个字节(字母、数字字符)的实际余额
	char    liquidate_date[5];			//清算日期: 通过该日期进行对帐
	char 	trade_money[13];			//交易金额: 12字节
	char    inital_data[43];			//原始数据: 冲正交易所用的原始数据记录
	char    liq_cur_code[4];			//清算货币代码: 4字节
	char    net_info_code[4];			//网络信息代码: 4字节
	char    append_trade_info[104];		//附加交易信息: 3个字节的长度值+最大100个字节(对账文件)
	char    transfer_count[11];			//转帐笔数: 10字节
	char    security_info_control[17];	//安全信息控制: 16字节
	char    card_id[31];				//交易卡号: 2字节 + 28字节最大长度
	char    liq_money[13];				//清算金额: 12字节
}BANK_YNXH_TRADE_STRUCT_PACKET;

struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};

/******************************云南信农业银行********************************
* 文件内容: 新增圈存数据结构定义说明
* 文件名:	Bank_gd.h
* 说明:		实现云南农行数据结构
* 创建:		李翔
* 时间:		2008-04-26
* 修改原因: 
* 报文结构: 1. 报文头
*			2. 报文体
*****************************************************************************/

/*****************************************************************************
/* 报文头
*****************************************************************************/
typedef struct  
{
	char	bank_version[2];					// 版本信息号
	char    packet_length[5];						// 数据包大小
	char    lanuch_mark[2];						// 发起方标识
	char    algorithm[1];						// 加密算法
	char	secret_seg[16];						// 密钥字段
	char	mac_check[8];						// MAC校验
	char	trade_type[4];						// 交易类型
	char    trade_date[8];						// 交易日期
	char    trade_time[6];						// 交易时间
	char    packet_count[5];					// 包体记录数
	char 	trade_serial[20];					// 交易流水号
	char    device_id[8];						// 设备号
	char    success_flag[1];					// 成功标识
	char    error_code[4];						// 错误码
	char    follow_flag[1];						// 后续标识
	char	packet_id[5];						// 包编号
	char	request_type[2];					// 请求类型
	char    channel_id[8];						// 渠道请求ID
}BANK_YNNH_TRADE_STRUCT_HEAD;


typedef struct
{
	BANK_YNNH_TRADE_STRUCT_HEAD ynnh_head;		// 农行标识头
	char	bank_account[20];					// 银行卡号
	char	bank_pin[16];						// 银行卡密码
	char    trade_money[14];					// 交易金额
	char    trans_serail[20];					// 被冲正流水号
	char    account_money[14];					// 账户余额
	char    remain_money[14];					// 可用余额
	char    card_id[12];						// 交易卡号
}BANK_YNNH_TRADE_STRUCT_PACKET;

#pragma pack()
#endif

