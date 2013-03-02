/* ----------------------------------------------------------
 * �������ƣ�bank_gd.cpp
 * �������ڣ�2007-08-2 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ݴ�ѧ���й����к͹������е�ͷ�ļ�����
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#ifndef	__BANK_GD_H__
#define	__BANK_GD_H__

#include "tcp.h"

#pragma once

#define		BANK_ZGYH							3
#define		BANK_GSYH							1

//**********�й����еĽ��״���********//
#define		BANK_ZGYH_TRADE_CODE_TRANS			"DXRB"		//ת��
#define		BANK_ZGYH_TRADE_CODE_DETRANS		"DXRV"		//����
//**********�������еĽ��״���*******//

#define		BANK_GSYH_TRADE_CODE_LOGIN			"31"		//ǩ��
#define		BANK_GSYH_TRADE_CODE_LOGOUT		"32"		//ǩ��
#define		BANK_GSYH_TRADE_CODE_COMPARE		"33"		//����
#define		BANK_GSYH_TRADE_CODE_TRANS			"1 "		//ת��
#define		BANK_GSYH_TRADE_CODE_DETRANS		"2 "		//����
#define		BANK_GSYH_TRADE_CODE_FEE			"02"		//ת��
#define		BANK_GSYH_TRADE_CODE_DEFEE			"12"		//����
#define		BANK_GSYH_TRADE_CODE_QUERYBALANCE	"5 "		//��ѯ���

//******************************************************************//

#define		BANK_GSYH_PINKEY_SYN_STR	"12345678"	//����PIN��Կͬ��ָʾ��
#define		BANK_GSYH_MACKEY_SYN_STR	"12345678"	//����MAC��Կͬ��ָʾ��




#define BANK_ZGYH_MERCH_NO "gzschool"
#define BANK_GSYH_ZONE_NO_GZ	"3602"
#define BANK_GSYH_ZONE_NO_ZH	"2002"
#define BANK_GSYH_TYPE_SCHOOL	"11"
#define BANK_GSYH_MERCH_NO "73213"

#pragma pack(1)
//��ͷ
typedef struct  
{
	char	Ret[4];					//������; ��0000Ϊ���ɹ�
	char	TranCode[4];			//������; DXRB:ת��,DXRV:����
	char	BrnId[7];				//�����; �ո�
	char	TmlId[2];				//�ն˺�; �ո�
	char	TelId[2];				//��Ա��; �ո�
	char	Filer1[3];				//Ԥ����;
	char	Mchno_len;				//�̶�ֵ; 0x08
	char	Merch_no[8];			//��λ����;  ����
	char	Mch_name[24];			//��λ����;�ո�
	char	Errcd[7];				//�������;
	char	ErrMsg[60];				//������Ϣ;
	char	LocalNo[20];			//������ˮ��;
	char	BankNo[8];				//������ˮ��;
	char	Filer2[50];				//Ԥ��;

}BANK_ZGYH_TRADE_STRUCT_HEAD;

//--------------------
//ת������
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//У԰���ʺ�
	char	BankCard[30];			//���п���
	char	CardType;				//�����ͣ�C���ÿ�,D��ǿ�
	char	TranMoney[13];			//���׽��
	char	PinBlock[16];			//Ԥ��
	char	TpkUdlmk[16];			//Ԥ��
}BANK_ZGYH_TRADE_STRUCT_TRANS_REQ;

//ת��Ӧ��
typedef struct  
{	
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//У԰���ʺ�
	char	BankCard[30];			//���п���
	char	CardType;				//�����ͣ�C���ÿ�,D��ǿ�
	char	TranMoney[13];			//���׽��
	char	PinBlock[16];			//Ԥ��
	char	TpkUdlmk[16];			//Ԥ��
	char	XykSqh[7];				//���ÿ���Ȩ��
	char	LocalNo[20];			//������ˮ��
}BANK_ZGYH_TRADE_STRUCT_TRANS_ANS;

//��������
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//У԰���ʺ�
	char	BankCard[30];			//���п���
	char	CardType;				//�����ͣ�C���ÿ�,D��ǿ�
	char	TranMoney[13];			//���׽��
	char	PinBlock[16];			//Ԥ��
	char	TpkUdlmk[16];			//Ԥ��
	char	XykSqh[7];				//���ÿ���Ȩ��
	char	OldLocalNo[20];			//ԭ������ˮ��

}BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ;

//����Ӧ��
typedef struct  
{
	BANK_ZGYH_TRADE_STRUCT_HEAD head;
	char	GDCAccount[30];			//У԰���ʺ�
	char	BankCard[30];			//���п���
	char	CardType;				//�����ͣ�C���ÿ�,D��ǿ�
	char	TranMoney[13];			//���׽��
	char	PinBlock[16];			//Ԥ��
	char	TpkUdlmk[16];			//Ԥ��
	char	XykSqh[7];				//���ÿ���Ȩ��
	char	OldLocalNo[20];			//ԭ�̻���ˮ��

}BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS;
///////////////////////////�������нӿڽṹ///////////////////////////////



#pragma pack(1)

typedef struct  
{
	char    RetCode[2] ;		//���׷�����;
   	char    ZoneNo[5]  ;            //�������;����:3602,�麣:2002;
	char    BusiType[9];            //��������;11:У԰��
	char    TranCode[2];		//��������;1:ת��,2:ȡ��,3:����ѯ
	char    TranFlag[1];            //���ױ�־;0:������,1:������
	char	BankCardNo[30];			//���п���;�跽�ʺţ�����ʱΪѧУ�ʺ�
	char	TranMoney[10];			//���׽��;
	char	MoneyType[3];			//��������;001:�����
	char    TranDate[8];           //��������;YYYY-MM-DD
	char    TranTime[6];			//����ʱ��;HHMMSS
	char	PwdFlag[1];				//�������־;0:�����,1:���
	char	PwdType[1];				//����(����)��־,0:����,1:����
	char	BankCardPwd[8];			//����
	char	LocalSn[8];			//���ؽ�����ˮ��;
	char	LocalDetranSn[8];		//����ʱ�����ԭת�ʽ�����ˮ��
	char	BankSn[8];			//������ˮ��
	char	MercAccount[5];			//Ȧ��ʱΪ��ɽ��ѧ�̻���,����ʱΪ�̻����̻���
	char	MercAccountCode[2];		//�����ţ�ָ�̻����ж�������ʺ�ʱ�����ֶ�ָʾ����һ���ʺţ��ȹ̶�Ϊ01;
	char	GDCAccount[10];			//У԰����;
	char	PosNo[5];				//Ȧ�����;
	char	AgentPercent[9];		//����ʱ�Ĵ�����ɰٷֱ�
	char	AgentType[2];			//ҵ������,01:Ȧ��,02:����;
	char	Filter[64];				//�ո�λ

}BANK_GSYH_TRADE_STRUCT;
#pragma pack()
/*
//����
typedef struct  
{
	char	TradeCode[2];	//���״���,�μ��궨��.
	char	RetCode[2];		//���׽��,
	char	TradeDate[8];					//��������	YYYYMMDD
	char	TradeTime[8];					//����ʱ��	HHMMSS
	char	CustAccountNo[10];				//У԰���ʺţ��󲹿ո�
	char	BankCardNo[20];					//���п���,�󲹿ո�
	char	TransMoney[9];					//ת�˽�xxxxxx.xx��ʽ��ǰ���ո�
	char	Balance[9];						//��	xxxxxx.xx��ʽ��ǰ���ո�
	char	BankCardPwd[16];				//���п�����
	char	CustSn[8];						//У԰����ˮ��
	char	BankSn[8];						//������ˮ��
	char	CustNo[16];						//ѧУ���ţ��󲹿ո�
	char	AutoFlag;						//�Զ�ת�˱�־,'0':������'1':�Զ�
	char	PINKeySynFlag[16];				//����ͬ����־
	char	MACKeySynFlag[16];				//У��ͬ����־
	char	MAC[8];							//У��
}

//================���²��� WangYanBin 2002.8.18 Ϊ��ɽ��ѧ�������Ի��Ķ�===================
  ��ɽ��ѧ�ӿ�����˵��:
    1.����һ���ṹ,����ȫ������,ȫ��Ϊ�ı��ṹ(ASCII��)
	2.����ҿ�ǰ����,������Ŀ���ֲ��ո�
	3.���׷�����˵��:-------------------------
	                 | 00 | �ɹ�             |
					 | 01 | �˻���ʧ         |
					 | 02 | �˻���           |
					 | 03 | ����         |
					 | 04 | �˻��������     |
					 | 98 | ����ʱ         |
					 | 99 | ��������         |
					 -------------------------

	��Ӧ
typedef struct {
	char	TradeCode[2];	//���״���,�μ��궨��.
	char	RetCode[2];		//���׽��,
	char	TradeDate[8];					//��������	YYYYMMDD
	char	TradeTime[8];					//����ʱ��	HHMMSS
	char	CustAccountNo[10];				//У԰���ʺţ��󲹿ո�
	char	BankCardNo[20];					//���п���,�󲹿ո�
	char	TransMoney[9];					//ת�˽�xxxxxx.xx��ʽ��ǰ���ո�
	char	Balance[9];						//��	xxxxxx.xx��ʽ��ǰ���ո�
	char	BankCardPwd[16];				//���п�����
	char	CustSn[8];						//У԰����ˮ��
	char	BankSn[8];						//������ˮ��
	char	CustNo[16];						//ѧУ���ţ��󲹿ո�
	char	AutoFlag;						//�Զ�ת�˱�־,'0':������'1':�Զ�
	char	PINKeySynFlag[16];				//����ͬ����־
	char	MACKeySynFlag[16];				//У��ͬ����־
	char	MAC[8];							//У��
	}
	*/

struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};


#pragma pack()
#endif

