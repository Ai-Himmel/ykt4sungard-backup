/* ----------------------------------------------------------
 * �������ƣ�bank_gd.cpp
 * �������ڣ�2007-08-2 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ݴ�ѧ���й����к͹������е�ͷ�ļ�����
 * ----------------------------------------------------------
 * �޸�����: 2008-03-26
 * �޸���Ա: ����
 * �޸�����: �����������ú�����ṹ����
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
 * ----------------------------------------------------------*/


#ifndef	__BANK_GD_H__
#define	__BANK_GD_H__

#include "tcp.h"
#include "bank.h"

#pragma once

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

/******************************�������ú�����********************************
* �ļ�����: ����Ȧ�����ݽṹ����˵��
* �ļ���:	Bank_gd.h
* ˵��:		ʵ���������ú�����
* ����:		����
* ʱ��:		2008-03-26
* �޸�ԭ��: �����������ú�����Ȧ�汨�Ľṹ˵��
* ���Ľṹ: 1. ����ͷ
*			2. �������ͱ�ʶ
*			3. λͼ
*			4. ������
*****************************************************************************/

/*****************************************************************************
/* �����궨��
*****************************************************************************/
// ��ϱ���У���
#define  PACKETSTR(packet_str, des_str, split_vl) \
		{ \
			if (strlen(des_str)) { strcat(packet_str, des_str); strcat(packet_str, split_vl); } \
		}		

/*****************************************************************************
/* ����ͷ
*****************************************************************************/
typedef struct  
{
	char	packet_head_length[2];					//����ͷ����: 8bit�Ķ�������, ����ֵΪ46
	char	head_flag[2];							//ͷ��ʶ: 8bit�Ķ�������, ��һλ0��ʾ��������, 1��ʾ���Ա���, ��7λ0000001
	char	packet_length[5];						//�����ܳ���: 4λ�����������ַ�
	char	dest_id[12];							//Ŀ��ID: 11λ���������ַ�����, ������д01999999999
	char	src_id[12];								//ԴID: 11λ���������ַ�����
	char	reserve_1[4];							//����λ: 24bit�Ķ�������, ���ڽڵ㷢��������ģ������ֵΪ0
	char    batch_no[2];							//���κ�: 8bit�Ķ�������, 0
	char	trade_info[9];							//������Ϣ: 8λ��ĸ�����������ַ�
	char	user_info[2];							//�û���Ϣ: ����Ϊ8bit�Ķ�������
	char	reject_code[6];							//�ܾ���: �������������ı����д����﷨����ʱ,��ʱ����ĵ�1λΪ0��1, Ϊ0��ʾ����ͷ�����,
													//Ϊ1��ʾ�����������; 2-4 λ��ʾ������򣻵�5λ��ʾ���������. ���ڴ������ĵ�ԭ���±��ı��ܾ���
													//��ʱ����ĵ�1λΪ2, 2-5 λ��ʾ���������. �������ĵ�ʱ��Ϊ:"00000"
}BANK_YNXH_TRADE_STRUCT_HEAD;

/*****************************************************************************
/* �������ͱ�ʶ
*****************************************************************************/
#define		BANK_YNXH_TRADE_CODE_QUERYBALANCE		"0200"		//��ѯ���
#define		BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE	"0210"		//��ѯ���
#define		BANK_YNXH_TRADE_CODE_TRANS				"0200"		//ת������
#define		BANK_YNXH_TRADE_CODE_ANS_TRANS			"0210"		//ת��Ӧ��
#define		BANK_YNXH_TRADE_CODE_DETRANS			"0420"		//��������
#define		BANK_YNXH_TRADE_CODE_ANS_DETRANS		"0430"		//����Ӧ��
#define		BANK_YNXH_TRADE_CODE_COMPARE			"0520"		//��������
#define		BANK_YNXH_TRADE_CODE_ANS_COMPARE			"0530"		//����Ӧ��

/*****************************************************************************
/* λͼ:
/* (1) λͼ�����԰�������λͼҲ���԰�������λͼ.
/* (2) λͼ������ѡ����ݽ������Ͷ���: λͼһ������2����64, λͼ��������66��
/*     ��128, λͼ��������130����192
/* (3) 64�ֽ�+64�ֽ�+64�ֽ�
*****************************************************************************/

/*****************************************************************************
/* ��������=����ͷ+��������(��������+λͼ+������)
*****************************************************************************/
typedef struct  
{
	BANK_YNXH_TRADE_STRUCT_HEAD head;	//����ͷ
	char	msg_type[5];				//��Ϣ����: �ͱ������ͱ�ʶͬ
	char	bit[17];					//λͼ: 128λ, 16����������16���ֽ�
	char	main_account[22];			//���ʺ�: 2 ���ֽڵĳ���ֵ+���19 ���ֽڣ������ַ��������˺�
	char	trade_deal_code[7];			//���״�����: 6λ���������ַ�
	char    trade_deal_time[11];		//���״���ʱ��: 10λ���ַ�
	char    system_id[7];				//ϵͳ���ٺ�: 6λ���ַ�
	char    accept_card_time[7];		//�ܿ������ڵ�ʱ��(hhmmss), 6λ���ַ�
	char    accept_card_date[5];		//�ܿ������ڵ�����(MMDD), 4λ���ַ�
	char    shop_type[5];				//�̻�����: 4�ֽ�
	char    service_input_code[4];		//�������뷽ʽ��: 3�ֽ�
	char    service_terms_code[3];		//����������: 2�ֽ�
	char    proxy_node_code[14];		//����ڵ����: 2���ֽڵĳ���ֵ+���11���ֽڵĴ��������ʶ��
	char    send_node_code[14];			//���ͽڵ����: 2���ֽڵĳ���ֵ+���11���ֽڵĴ��������ʶ��
	char    second_mag_tune[40];		//�ڶ��ŵ�����: 2���ֽ�+37���ֽ�
	char    third_mag_tune[108];		//�����ŵ�����: 3���ֽڵĳ���ֵ+���104���ֽ�(�ַ�)�ĵ����ŵ�����
	char    check_code[13];				//�����ο���
	char    device_phy[9];				//�ܿ����ն˱�ʶ��: 8�ֽڵ�����ID�Ż����������ִ�
	char    mark[16];					//�ܿ�����ʶ: 15�ֽ�
	char    address[41];				//�ܿ�����ַ����: 40�ֽ�
	char    append_data[516];			//��������: 3���ֽڵĳ���ֵ�����512���ֽ�
	char    trade_money_code[4];		//���׻��Ҵ���: 3�ֽڳ���
	char    personal_mark[9];			//���˱�ʶ������: 64bit
	char    defalut_area[34];			//�Զ�����: 3���ֽڵĳ���ֵ�����30���ֽ�(��ĸ�����ֺ������ַ�)������
	char    accept_node_code[14];		//���ܽڵ��ʶ��: 2���ֽڵĳ���ֵ+���11���ֽڵĽ��սڵ��ʶ��, ��У԰һ��ͨ�����У������ֵΪ01999999999
	char    packet_identity_code[9];	//���ļ�����: 64bit
	char    answser_code[3];			//Ӧ����: 2�ֽ�
	char    cur_balance[44];			//ʵ�����: 3���ֽڵĳ���ֵ�����40���ֽ�(��ĸ�������ַ�)��ʵ�����
	char    liquidate_date[5];			//��������: ͨ�������ڽ��ж���
	char 	trade_money[13];			//���׽��: 12�ֽ�
	char    inital_data[43];			//ԭʼ����: �����������õ�ԭʼ���ݼ�¼
	char    liq_cur_code[4];			//������Ҵ���: 4�ֽ�
	char    net_info_code[4];			//������Ϣ����: 4�ֽ�
	char    append_trade_info[104];		//���ӽ�����Ϣ: 3���ֽڵĳ���ֵ+���100���ֽ�(�����ļ�)
	char    transfer_count[11];			//ת�ʱ���: 10�ֽ�
	char    security_info_control[17];	//��ȫ��Ϣ����: 16�ֽ�
	char    card_id[31];				//���׿���: 2�ֽ� + 28�ֽ���󳤶�
	char    liq_money[13];				//������: 12�ֽ�
}BANK_YNXH_TRADE_STRUCT_PACKET;

struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};

/******************************������ũҵ����********************************
* �ļ�����: ����Ȧ�����ݽṹ����˵��
* �ļ���:	Bank_gd.h
* ˵��:		ʵ������ũ�����ݽṹ
* ����:		����
* ʱ��:		2008-04-26
* �޸�ԭ��: 
* ���Ľṹ: 1. ����ͷ
*			2. ������
*****************************************************************************/

/*****************************************************************************
/* ����ͷ
*****************************************************************************/
typedef struct  
{
	char	bank_version[2];					// �汾��Ϣ��
	char    packet_length[5];						// ���ݰ���С
	char    lanuch_mark[2];						// ���𷽱�ʶ
	char    algorithm[1];						// �����㷨
	char	secret_seg[16];						// ��Կ�ֶ�
	char	mac_check[8];						// MACУ��
	char	trade_type[4];						// ��������
	char    trade_date[8];						// ��������
	char    trade_time[6];						// ����ʱ��
	char    packet_count[5];					// �����¼��
	char 	trade_serial[20];					// ������ˮ��
	char    device_id[8];						// �豸��
	char    success_flag[1];					// �ɹ���ʶ
	char    error_code[4];						// ������
	char    follow_flag[1];						// ������ʶ
	char	packet_id[5];						// �����
	char	request_type[2];					// ��������
	char    channel_id[8];						// ��������ID
}BANK_YNNH_TRADE_STRUCT_HEAD;


typedef struct
{
	BANK_YNNH_TRADE_STRUCT_HEAD ynnh_head;		// ũ�б�ʶͷ
	char	bank_account[20];					// ���п���
	char	bank_pin[16];						// ���п�����
	char    trade_money[14];					// ���׽��
	char    trans_serail[20];					// ��������ˮ��
	char    account_money[14];					// �˻����
	char    remain_money[14];					// �������
	char    card_id[12];						// ���׿���
}BANK_YNNH_TRADE_STRUCT_PACKET;

#pragma pack()
#endif

