/* ----------------------------------------------------------
 * �������ƣ�bank_boc_dl.h
 * �������ڣ�2010-07-22
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��������´�ѧ�й����е�ͷ�ļ�����
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/
#ifndef	__BANK_BOC_DL_H__
#define	__BANK_BOC_DL_H__
#include "tcp_update.h"
#pragma once
#define		BANK_ZGYH							3
#define		BANK_JSYH							2
#define		BANK_GSYH							1
///////////////////////////�й����нӿڽṹ///////////////////////////////
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
//��75��������
	{"���׳ɹ�/Normal OK","00"},
	{"����������ϵ/Refer to Card Issuer","01"},
	{"��Ч�̻�/Invalid Merchant","03"},
	{"����׼����/Do Not Honour","05"},
	{"���п�����/Bank balance insufficient","07"},
	{"����������ϵ/Honour with I.D. Only","08"},
	{"��Ч����/Invalid Message","12"},
	{"��Ч���/Invalid Dollar Amount","13"},
	{"��Ч����/Invalid Card Number","14"},
	{"�޴˷�����","15"},
	{"����������","19"},
	{"�����κδ���/No Action Taken","21"},
	{"�޴˽���/Record Not Found in File","25"},
	{"�ظ�����/Duplicate Record on File","26"},
	{"�����޷�����/Record or File Locked","28"},
	{"File Update Denied","29"},
	{"��ʽ����/Format Error","30"},
	{"���ڿ�/Card Expired","33"},
	{"����������(û�տ�)","34"},
	{"��ϵ����(û�տ�)","35"},
	{"��ϵ������(û�տ�)","37"},
	{"PIN���볬�Σ�û�տ���/Capture Card - PIN Retries Exceeded","38"},
	{"�޴��˻�/No Credit Account","39"},
	{"�Ƿ�����/Invalid Function","40"},
	{"��ʧ��(û�տ�)/Lost Card","41"},
	{"���Կ�(û�տ�)/Card is Hot/Stolen","43"},
	{"����/Insufficient Funds","51"},
	{"���ڿ�/Card Expired - Do not pickup","54"},
	{"���п������/Invalid PIN - Retry","55"},
	{"�޴˿���¼/Card Holder not on File","56"},
	{"�Ƿ�����/Transaction not allowed for Card","57"},
	{"����������","59"},
	{"����������ϵ","60"},
	{"����ȡ���޶�/Exceeds Withdrawal Limit","61"},
	{"�����ƿ�/Restricted Card","62"},
	{"Υ����ȫ���ܹ涨/Invalid MAC","63"},
	{"��Чԭ���/Invalid Original Amount","64"},
	{"ȡ�������������/Number of Withdrawals Exceeded","65"},
	{"û�տ�/Force Capture of Card","67"},
	{"���п��������볬������/PIN Retries exceeded","75"},
	{"���㲻ƽ/Invalid Business Date","77"},
	{"ֹ����/Deactivated Card","78"},
	{"�Ƿ��ʻ�/Invalid Account","79"},
	{"���׾ܾ�/Transaction Denied","80"},
	{"��������/Cancelled Card","81"},
	{"�����ݶ�,��������/Issuer Down","84"},
	{"PIN��Կͬ����/PIN Key Sync Error","87"},
	{"MAC��Կͬ����/MAC Key Sync Error","88"},
	{"���������Ժ���/Cutoff in Progress","90"},
	{"���׳�ʱ/Message Timed Out","91"},
	{"�������׻�绰��Ȩ/Issuer Not Found","92"},
	{"�ظ�����/Possible Duplicated Transaction ","94"},
	{"���㲻ƽ,���ͽ���","95"},
	{"ϵͳ�쳣/System malfunction","96"},
	{"�ն˺Ŵ���/Invalid ATM/POS IDs","97"},
	{"���뷢����ʧȥ����/SW couldn��t get reply from IS","98"},
	{"PIN��ʽ��/PIN Block Error","99"},
	{"��ƥ��Ľ���/Unmatched Transaction","N0"},
	{"Valid Unmatched Transaction","N1"},
	{"��Ч�ڴ�/Expiry Date does not Match with Database","Q2"},
	{"��Ч��У��/Invalid Card Verification Value (CVV)","SK"},
	{"�ѻ���׼������EMV�ѻ�����ʱʹ�õ�ֵ��","Y1"},
	{"��������EMV�ѻ�����ʹ�õ�ֵ��","Y2"},
	{"�޷��������ѻ���׼������EMV�ѻ�����ʹ�õ�ֵ���ݲ�ʹ�á����淶�涨һ���������������󣬾Ͳ������ٽ����ѻ���׼���̣�","Y3"},
	{"����ǩ��","Z1"},
	{"���ֲ���","Z2"},
	{"����������","Z3"},
	{"���ڼƻ���","Z4"},
	{"����ϵ�յ����ֹ��˻�","Z5"},
	{"��Ч���ױ���","Z6"},
	{"����δ�ᣬ���Ƚ�������","Z7"},
	{"��֧�ָÿ���","Z8"},
	{"����EMV����ɽ�����ʹ��Ԥ��Ȩ���֪ͨ������������","Z9"},
	{"���������涨�����֪ͨ���ײ��ܳ���","ZA"},
	{"��ʹ����Ԥ��Ȩ����ͬһ�����ն�����ɽ���","ZB"},
	{"����ˢ����ʽ���н���","ZC"}
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
    char msgtyp[4];	    // ��������
    char msg[MAXBUFSIZE];   //����    ������
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
