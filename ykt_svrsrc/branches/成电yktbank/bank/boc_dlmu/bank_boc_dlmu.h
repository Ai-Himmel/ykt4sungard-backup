/* ----------------------------------------------------------
 * 程序名称：bank_boc_dl.h
 * 创建日期：2010-07-22
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：大连海事大学中国银行的头文件定义
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/
#ifndef	__BANK_BOC_DL_H__
#define	__BANK_BOC_DL_H__
#include "tcp_update.h"
#pragma once
#define		BANK_ZGYH							3
#define		BANK_JSYH							2
#define		BANK_GSYH							1
///////////////////////////中国银行接口结构///////////////////////////////
#define BANK_ZGYH_TRADE_CODE_QUERY_REQ 		"0100"
#define BANK_ZGYH_TRADE_CODE_QUERY_ANS 		"0110"
#define BANK_ZGYH_EXEC_CODE_QUERY_REQ 		"310000"
#define BANK_ZGYH_TRADE_CODE_TRANS_REQ 		"0200"
#define BANK_ZGYH_TRADE_CODE_TRANS_ANS 		"0210"
#define BANK_ZGYH_EXEC_CODE_TRANS_REQ 		"000000"
#define BANK_ZGYH_TRADE_CODE_DETRANS_REQ 	"0400"
#define BANK_ZGYH_TRADE_CODE_DETRANS_ANS 	"0410"
#define BANK_ZGYH_EXEC_CODE_DETRANS_REQ 	"020000"
#define BANK_ZGYH_MERCH_NO 					"104210282200001"
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

typedef struct tagzgyh_err_code {
 const char *ErrMsg;
 char ErrCode[3];
} zgyh_err_code;

static zgyh_err_code BOC_ERR_CODE[] = {
//共75个错误码
	{"交易成功/Normal OK","00"},
	{"请与银行联系/Refer to Card Issuer","01"},
	{"无效商户/Invalid Merchant","03"},
	{"不批准交易/Do Not Honour","05"},
	{"银行卡余额不足/Bank balance insufficient","07"},
	{"请与银行联系/Honour with I.D. Only","08"},
	{"无效交易/Invalid Message","12"},
	{"无效金额/Invalid Dollar Amount","13"},
	{"无效卡号/Invalid Card Number","14"},
	{"无此发卡行","15"},
	{"请重做交易","19"},
	{"不做任何处理/No Action Taken","21"},
	{"无此交易/Record Not Found in File","25"},
	{"重复交易/Duplicate Record on File","26"},
	{"交易无法处理/Record or File Locked","28"},
	{"File Update Denied","29"},
	{"格式错误/Format Error","30"},
	{"过期卡/Card Expired","33"},
	{"有作弊嫌疑(没收卡)","34"},
	{"联系保安(没收卡)","35"},
	{"联系卡中心(没收卡)","37"},
	{"PIN输入超次（没收卡）/Capture Card - PIN Retries Exceeded","38"},
	{"无此账户/No Credit Account","39"},
	{"非法功能/Invalid Function","40"},
	{"挂失卡(没收卡)/Lost Card","41"},
	{"被窃卡(没收卡)/Card is Hot/Stolen","43"},
	{"余额不足/Insufficient Funds","51"},
	{"过期卡/Card Expired - Do not pickup","54"},
	{"银行卡密码错/Invalid PIN - Retry","55"},
	{"无此卡记录/Card Holder not on File","56"},
	{"非法交易/Transaction not allowed for Card","57"},
	{"有作弊嫌疑","59"},
	{"请与银行联系","60"},
	{"超出取款限额/Exceeds Withdrawal Limit","61"},
	{"受限制卡/Restricted Card","62"},
	{"违反安全保密规定/Invalid MAC","63"},
	{"无效原金额/Invalid Original Amount","64"},
	{"取款次数超过次数/Number of Withdrawals Exceeded","65"},
	{"没收卡/Force Capture of Card","67"},
	{"银行卡密码输入超过次数/PIN Retries exceeded","75"},
	{"结算不平/Invalid Business Date","77"},
	{"止付卡/Deactivated Card","78"},
	{"非法帐户/Invalid Account","79"},
	{"交易拒绝/Transaction Denied","80"},
	{"卡已作废/Cancelled Card","81"},
	{"联网暂断,重做交易/Issuer Down","84"},
	{"PIN密钥同步错/PIN Key Sync Error","87"},
	{"MAC密钥同步错/MAC Key Sync Error","88"},
	{"主机轧帐稍候工作/Cutoff in Progress","90"},
	{"交易超时/Message Timed Out","91"},
	{"重做交易或电话授权/Issuer Not Found","92"},
	{"重复交易/Possible Duplicated Transaction ","94"},
	{"结算不平,上送交易","95"},
	{"系统异常/System malfunction","96"},
	{"终端号错误/Invalid ATM/POS IDs","97"},
	{"暂与发卡行失去联络/SW couldn’t get reply from IS","98"},
	{"PIN格式错/PIN Block Error","99"},
	{"不匹配的交易/Unmatched Transaction","N0"},
	{"Valid Unmatched Transaction","N1"},
	{"有效期错/Expiry Date does not Match with Database","Q2"},
	{"无效卡校验/Invalid Card Verification Value (CVV)","SK"},
	{"脱机批准（用于EMV脱机交易时使用的值）","Y1"},
	{"（保留在EMV脱机交易使用的值）","Y2"},
	{"无法联机，脱机批准（用于EMV脱机交易使用的值，暂不使用。本规范规定一旦发起了联机请求，就不允许再进行脱机批准流程）","Y3"},
	{"请先签到","Z1"},
	{"积分不够","Z2"},
	{"分期期数错","Z3"},
	{"分期计划错","Z4"},
	{"请联系收单行手工退货","Z5"},
	{"无效交易币种","Z6"},
	{"上批未结，请先结完上批","Z7"},
	{"不支持该卡种","Z8"},
	{"银联EMV卡完成交易请使用预授权完成通知交易重新上送","Z9"},
	{"根据银联规定，完成通知交易不能撤消","ZA"},
	{"请使用与预授权交易同一类型终端做完成交易","ZB"},
	{"请用刷卡方式进行交易","ZC"}
};

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
    char msgtyp[4];	    // 交易类型
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
