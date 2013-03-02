/* ----------------------------------------------------------
 * 程序名称：bank_ccb_nm.h
 * 创建日期：2009-08-10
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：内蒙财经建行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef	__BANK_BCC_NM_H__
#define	__BANK_BCC_NM_H__

#define REQ_PACK_LEN 157
#define ANS_PACK_LEN 56

#define REV_REQ_PACK_LEN 107
#define REV_ANS_PACK_LEN 40

#define TRANS_CODE   		"1001"
#define REV_TRANS_CODE   	"1002"

/*
#pragma pack(1)

typedef struct{
	char packlen[4];				// 报文长度
	char transcode[4];				// 交易码 1001
	char transdate[8];				// 交易日期
	char refno[14];					// 一卡通交易参考号
	char stuempno[32];				// 学工号
	char name[32];					// 姓名
	char idcardno[18];				// 身份证号
	char bankno[32];				// 银行卡号
	char tradeamt[17];				// 交易金额
}TRANS_REQ;

typedef struct{
	char packlen[4];				// 报文长度
	char bankdate[8];				// 银行业务日期
	char bankserial[8];			// 银行流水号
	char rescode[6];				// 响应码
	char resmsg[34];				// 响应消息
}TRANS_ANS;

typedef struct{
	char packlen[4];				// 报文长度
	char transcode[4];				// 交易码 1001
	char transdate[8];				// 交易日期
	char refno[14];					// 一卡通交易参考号
	char stuempno[32];				// 学工号
	char bankno[32];				// 银行卡号
	char tradeamt[17];				// 交易金额
}REVERSE_REQ;

typedef struct{
	char packlen[4];				// 报文长度
	char rescode[6];				// 响应码
	char resmsg[34];				// 响应消息
}REVERSE_ANS;

#pragma pack()
*/

#endif

