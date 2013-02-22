/* ----------------------------------------------------------
 * �������ƣ�bank_icbc_nj.h
 * �������ڣ�2007-08-2 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��Ͼ��������нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#ifndef	__BANK_ICBC_NJ_H__
#define	__BANK_ICBC_NJ_H__

#include "tcp.h"

#pragma once

#define		BANK_ZGYH							3
#define		BANK_JSYH							2
#define		BANK_GSYH							1

//**********�������еĽ��״���*******//
/*
. ���������
  -----------------------------------
  1. ����--"test"    ����ͨѶ
  2. Ȧ��--"circle"  ������ת��
  3. �ɷ�--"pay"     ����
  4. ��ѯ--"query"   ��ѯ�����ʻ����
  5. ǩ��--"login"
  6. ǩ��--"logout"
  7. ����--"passwd"  ��������
  8. ����--"diff"		
  -----------------------------------
*/
#define	BANK_GSYH_TRADE_CODE_LOGIN		"login"		//ǩ��
#define	BANK_GSYH_TRADE_CODE_LOGOUT		"logout"		//ǩ��
#define	BANK_GSYH_TRADE_CODE_COMPARE		"diff"		//����
#define	BANK_GSYH_TRADE_CODE_TRANS		"circle"		//ת��
#define	BANK_GSYH_TRADE_CODE_DETRANS		"detrans"		//����
#define	BANK_GSYH_TRADE_CODE_FEE			"pay"		//ת��
#define	BANK_GSYH_TRADE_CODE_DEFEE		"de_pay"		//����
#define	BANK_GSYH_TRADE_CODE_QUERYBALANCE	"query"		//��ѯ���
const char BANK_ICBC_TRANSCODE_RELATION_QRY[] ="askrel";	//��ѯ���п���Ӧ��ϵ
const char BANK_ICBC_TRANSCODE_RELATION_ADD[]="addnew";	//������п���Ӧ��ϵ
const char BANK_ICBC_TRANSCODE_RELATION_DEL[]="delete";	//ɾ�����п���Ӧ��ϵ

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
///////////////////////////�������нӿڽṹ///////////////////////////////
#pragma pack(1)
typedef struct 
{
    char  MsgLength[4];       // ���ݰ����ܳ��ȣ�ʮ�����ַ�����ʾ "0256"
    char  TradeType[6];       // ������� ���嶨�����

    char  Sender[7];	      // ���ͷ� ���嶨�����
    char  Receiver[7];	      // ���շ� ���嶨�����

    char  PINKeySynFlag[16];  // ����������� ���ڽ�������
    char  MACKeySynFlag[16];  // У������     ����У�鱨�ģ�����ʱ����   ȫ0
    char  MAC[8];             // У��         �������ĵ�У�飬����ʱ���� ȫ0 
} MSG_HEAD;

typedef struct 
{
    char  ReturnCode[4];      // ���ؽ���� ���嶨�����
    char  Message[24];	      // ���ش�������
	
    char  TradeTime[14];      // ����ʱ�䣬YYYYMMDDHHMMSS ������ʱ����
    char  SchoolTransSeq[16]; // ѧУ������ˮ�� 8λ
    char  BankTransSeq[16];   // ���н�����ˮ��

    char  CampusCard[20];     // У԰������ 5λ����
    char  BankAccNO[20];      // �����ʺ�     ���ܺ��ַ�'|'
    char  StudentName[20];    // ѧ������     ���ܺ��ַ�'|'
    char  StudentID[18];      // ѧ�����֤�� ���ܺ��ַ�'|'

    char  Amount[12];         // ���׽��  �����֣��Ҷ���
    char  Balance[12];        // ���п������֣��Ҷ���
    char  BankCardPwd[16];    // ���п����� ����ܴ�� ����������룬��0

    char  reserve[0];         // �����ֶ� ;) �Ѵ���256�ֽڣ��ʲ���Ҫ�ˣ�
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

