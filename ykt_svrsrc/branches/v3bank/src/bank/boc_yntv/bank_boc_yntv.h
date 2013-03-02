/* ----------------------------------------------------------
 * �������ƣ�bank_boc_yntv.h
 * �������ڣ�2011-01-12
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ϵ���й����нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------*/


#ifndef	__BANK_BOC_YNTV_H__
#define	__BANK_BOC_YNTV_H__

#define QUERY_BALA			"05"						//��ѯ�����ʻ����
#define TRANS_CODE   		"01"						//ת�ˣ�Ȧ�棩
#define REV_TRANS_CODE   	"11"						//ת�ˣ�Ȧ�棩����
#define QUERY_BIND			"21"						//ǩԼ��ѯ
#define BIND_BANK			"22"						//ǩԼ
#define UN_BIND_BANK		"23"						//��Լ
#define BANK_SIGN_IN		"31"						// ������ǩ��

#define SCHOOLCODE	"0003"						// ����ұ��ר��ѧУ����

typedef struct _msgbody 
{
	char		TradeCode[2];			//���״��룺������(������)
	char		RetCode[2];				//���׽����������
	char		TradeDate[8];			//��������	 YYYYMMDD
	char		TradeTime[6];			//����ʱ��	 HHMMSS
	char		CustAccountNo[10];		//У԰���ʺţ��󲹿ո�
	char		BankCardNo[20];			//���п���,	 �󲹿ո�
	char		BankPWD[16];			//���п����룬�󲹿ո�
	char		TransMoney[9];			//ת�˽�  �Է�Ϊ��λ��ǰ��0
	char		Balance[9];				//��ǿ����Է�Ϊ��λ��ǰ��0
	char		CustSn[8];				//У԰����ˮ�ţ� �󲹿ո�
	char		BankSn[8];				//������ˮ�ţ�	�󲹿ո�
	char		IdentityCode[20];	//֤�����룬�󲹿ո�һ��Ϊ���֤��
	char		Name[30];			//�������󲹿ո�
	char		CustNo[20];			//ԺУ���룬�󲹿ո�
}MEGBODY;

typedef struct _errdef
{
char errcode[4];
char errmsg[64];
}ERRDEF;

#endif

