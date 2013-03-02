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
#define BANK_ZGYH_MERCH_NO "334014"
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