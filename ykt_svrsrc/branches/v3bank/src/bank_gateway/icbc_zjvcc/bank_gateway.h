#ifndef __BANK_GATEWAY_H_
#define __BANK_GATEWAY_H_

#define HEAD_LEN        		8
#define TRADECODE_LEN   	4

#define    TRADE_CHK_NOCARD	"2010"
#define    TRADE_PAY_NOCARD	"2020"
#define	TRADE_REV_NOCARD	"2030"
#define	TRADE_BIND			"2040"
#define 	BANKCODE            		"00"
#define 	SCHOOLCODE_AHUT	"10360"						// 安徽工大学校代码
#define XML_HEAD				"<?xml version='1.0' encoding='GBK'?>"

typedef struct
{
	char SchoolCode[8];
	char TrType[3];
	char CusName[64];
	char IcCard[32];
	char ReMark[100];
}INFO_BIND;

typedef struct
{
	char SchoolCode[8];
	char CusName[64];
	double IcCardBal;
	double ICCardNotWrt;
	char ReMark[100];
	char Refno[15];
}INFO_TRADE;

typedef struct
{
    char drtp_ip[20];
    int drtp_port;
    int main_funcno;
    int drtp_timeout;
    int bank_lisnport;
    int bank_timeout;
    int term_id;
}CONFIG_PARA;

#define  E_TRANS_NONSUPPORT        108116	//此功能暂不被支持

#endif
