#ifndef	__BANK_NYYH_H__
#define	__BANK_NYYH_H__

#include "tcp.h"
//#include "mac.h"
//#include "transinfo.h"

#define BANK_NYYH 4
//���������ɣ�09�������в��ţ�058��4λ˳��ţ����ѧУһ���һ��������Խ�˳���д��
//����Ҫά��˳��ŵ�ʹ�����������������ṩһ����һ�Σ����Ƿ�һ��һ����
#define BATCH_NO		"09*****0580001"	//�������
#define UNIT_NAME		"fudan university"	//��λ����
#define UNIT_ACCOUNT	"987564343"			//��λ�ʺ�

#define	SCHOOL_CODE				"XYK00008"		//ԺУ���룭�����ж����
#define	STATIC_KEY					"87906576"		//���нӿڵľ�̬��Կ���������ṩ��

#define	BANK_TRADE_CODE_LEN 		2			//���ж˽��״��볤��
#define	LEN_MAC				8			//mac�ֶγ���
#define	BANK_IP				"10.83.28.17"		//����ǰ�û�IP��ַ
#define BANK_PORT			3501			//����ǰ�û�����˿�
#define BANK_DELAY_TIME			3000			//�������з������ݰ��ĳ�ʱʱ�䣭��λΪ����
#define	UNQUE_KEY_TYPE			"trans"			//����Ψһ�����ŵĺ����ĵ�һ�����������������ڲ�ͬϵͳ
#define WORKSTATION_NO			167			//����վ��ʵ����װʱ���䣬��ʱ��167
#define	AGRICULTURE_BANK_CODE		1			//Ӧ����Ҫ����д�ⲿϵͳ��𣬱�ʶũҵ����
#define	AUTO_TRANS			1			//�Զ�ת��
#define	SELF_TRANS			2			//����ת��
#define	SCHOOL_ACCOUNT_NO		"9876543210"		//ѧУһ��ͨ��ũ�п������ʺ�
#define	TRANS_INI_FILE 			"./trans.ini"		//ini�ļ�


 /////////////////////////// inter return value      ///////////////////////////////


 /////////////////////////// bank return value      ///////////////////////////////
#define	RET_BANK_OK			"00"		//�ɹ�
#define	RET_BANK_LOST			"01"		//��ʧ
#define	RET_BANK_ERRSTAT		"02"		//�ʻ�״̬����
#define	RET_BANK_NOBAL		"03"		//����
#define	RET_BANK_OTHER		"04"		//��������
#define	RET_BANK_PASSERR		"05"		//�������


 /////////////////////////// ���н��״���  ///////////////////////////////
 #define	TRADE_BANK_LOGIN		"31"		//ǩ��
 #define	TRADE_BANK_LOGOUT	"32"		//ǩ��
 #define	TRADE_BANK_TRANS		"01"		//ת��
 #define	TRADE_BANK_DETRANS	"11"		//ת�˳���
 #define	TRADE_BANK_QUERY		"05" 	//��ѯ���
 #define	TRADE_BANK_COMP		"33"		//����
 #define	TRADE_BANK_FEE		"02"		//�ɷ�
 #define	TRADE_BANK_DEFEE		"12"		//�ɷѳ���
 #define	TRADE_BANK_CHGKEY	"34"		//��Կ����
 #define	TRADE_BANK_CHECKLINE	"35"		//��·����
 #define	TRADE_BANK_BALANCE	"36"		//����
 #define	TRADE_BANK_RETURN	"37"		//�������

//���нӿ����ݽṹ
 typedef struct
{
//								  CPACK�ֶ�		����
//----------------------------------------------------------------------
	char		TradeCode[2];		//scust_type	���״��룺  ������
	char		RetCode[2];			//scust_type2	���׽����  ������
	char		TradeDate[8];		//sdate0		��������	 YYYYMMDD
	char		TradeTime[6];		//semp			����ʱ��	 HHMMSS
	char		CustAccountNo[10];	//sorder0		У԰���ʺţ��󲹿ո�
	char		BankCardNo[20];		//scust_auth	���п���,	 �󲹿ո�
	char		MercAccount[10];		//sorder1		�̻���	Ȧ��ʱΪѧУ�̻��ţ��ɷѻ�����ʱ
								//Ϊ���̻����̻���
	char		TransMoney[9];		//sorder2		ת�˽�  �Է�Ϊ��λ��ǰ���ո�
	char		Balance[9];			//scust_no		��ǿ����Է�Ϊ��λ��ǰ���ո�
	char		BankCardPwd[16];	//sstation0		���п�����
	char		CustSn[8];			//sdate1		У԰����ˮ�ţ� �󲹿ո�
	char		BankSn[20];			//scust_auth2	������ˮ�ţ�	�󲹿ո�
	char		CustNo[16];			//sstation1		ѧУ���ţ�		�󲹿ո�
	char		AutoFlag;			//sstatus0		�Զ�ת�˱�־,'0':������'1':�Զ�
	char		MAC[8];				//sdate2		У��
}BANK_TRANS_REQUEST;


#define BANK_TRANS_PACKLEN	sizeof(BANK_TRANS_REQUEST)

struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};

/*
typedef struct
{
	char		TradeCode[2];		//���״���
	char 	GDCAccount[10];		//У԰���ʺţ�	�󲹿ո�
	char		BankCard[20];		//���п����룬	�󲹿ո�
	char		LocalSn[8];			//У԰����ˮ�ţ�	�󲹿ո�
	char		BankSn[20];			//���з���ˮ�ţ�	�󲹿ո�
	char		TransMomoy[9];	//���׽�		ǰ���㣬�Է�Ϊ��λ
	char 	LineChange[2];	//'\r\n'
}BANK_COMPARE_RECODE;
*/

typedef struct
{
	 char rmb_batch_no[14];//�������
	 char rmb_start_seq[6];//��000000
	 char rmb_acc_status;//����״̬����0��
	 char rmb_chk_status;//���״̬����2��
	 char rmb_total_amount[13];//�ܽ��(11λ����2λС������С����)
	 char rmb_total_num[6];//�ܱ���
	 char rmb_enter_amount[13];//���ʽ��(11λ����2λС������С����)
	 char rmb_enter_num[6];//���ʱ���
	 char rmb_unit_name[40];//��λ����
	 char rmb_unit_account[20];//��λ�ʺ�
	 char rmb_apply_date[8];//�����������ڣ��������ڣ�
	 char rmb_send_date[8];//�ϴ����ڣ��������ڣ�
}BANK_TRANSFER_HEAD;

typedef struct
{
  	 char rmb_batch_no1[14];         //�������
        char rmb_seq_no[6];                     //��¼��ţ���1�ۼƣ�
        char rmb_acc_status1;           //����״̬����0��
        char rmb_tran_kind;             //�������ࣨ1.�ֽ�֧Ʊ��2.����ƾ֤��3.�Ż㡢4.��Ʊ��5.��Ʊ��
        char rmb_cust_name[40];         //�ʻ�����
        char rmb_acc_no[19];                    //�ʺ�
        char rmb_cb_cr;                 //�����־����0��
        char rmb_tran_amt[13];                  //���׽��
        char rmb_cur_code[3];                   //���֣�0��2λ���ִ��룩
        char rmb_host_no[8];                    //��Ʊ�ţ���00000000��
        char rmb_ret_code[4];                   //���ʽ������"    "��
        char rmb_acc_date[8];                   //�������ڣ���00000000��
        char rmb_host_no1[9];                   //������ˮ�ţ���000000000��
        char rmb_open_branch[7];        //���������ţ���0000000��
 	 char rmb_vcho_kind[2];                  //ƾ֤���ࣨ��"  "��
        char rmb_vcho_bat_no[2];        //ƾ֤���κţ���00��
        char rmb_vcho_no[9];                    //ƾ֤�ţ���ҵ��Ҫ��
        char rmb_memo[22];              //ժҪ/��;
        char rmb_tran_info[200];                //������Ϣ
}BANK_TRANSFER_RECORD;




#endif
