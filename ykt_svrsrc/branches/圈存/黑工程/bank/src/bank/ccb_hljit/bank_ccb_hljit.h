/* ----------------------------------------------------------
 * 程序名称：bank_ccb_hljit.h
 * 创建日期：2011-07-30
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：黑工程建行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef	__BANK_CCB_HLJIT_H__
#define	__BANK_CCB_HLJIT_H__

#define QUERY_BALA			"05"						//查询银行帐户余额
#define TRANS_CODE   			"07"						//充值记帐
#define REV_TRANS_CODE   		"02"						//充值撤销


#define SCHOOLCODE_HLJIT		"HRBXYZ-HLJIT"			// 黑工程学校代码
#define HLJIT_MSG_LEN		472						//定长报文的总长度
#define HLJIT_TRADE_SUCC		"000000"					// 交易成功代码

#endif

