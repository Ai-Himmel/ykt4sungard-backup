#ifndef	__BANK_H__

#define	__BANK_H__



//#ifdef __cplusplus

//extern "C" {

//#endif



 /*****************************************************************************

 ��������˵��(����Packet_Buf_Transform����)

 *****************************************************************************/

#define		BANK_TRADE_CODE_QUERYBALANCE	1		//��ѯ���

#define		BANK_TRADE_CODE_TRANS		2			//ת��

#define		BANK_TRADE_CODE_DETRANS		3			//����

#define		BANK_TRADE_CODE_COMPARE		4			//����

 

 /*****************************************************************************

  �������

 *****************************************************************************/

#define		BANK_ZGYH							3

#define		BANK_GSYH							1

#define		BANK_YNXH							4

#define		BANK_YNNH							5



 /////////////////////////���������ݿ�/////////////////////////////////////

#define MAX_RANGE 20

#define MAX_BANK 5

#define	TRANS_INI_FILE 			"./trans.ini"		//ini�ļ�

#define SPLIT_VL				"|"

#define PACKET_TO_BUF			0					// packet to buf

#define BUF_TO_PACKET			1					// buf to packet



typedef struct

{

   char szBankIP[20];  // ���ж˵�ip��ַ

   int  iBankPort;         // ���ж˵Ķ˿ں�

   int  iBankTimeout;    // ���ж˵����ӳ�ʱʱ��

   int  iBankID;		//���б�ʶ�ţ���Ҫ���̨�����ֵ䱣��һ��

   char  szBankCardRange[MAX_RANGE][20];  // ���п��ŷ�Χ

   int	  iAuthMode;		//��֤��ʽ���������п����뻹��У԰������

   char  szBankAccountNO[17];

   char compare_time[6]; // ���ж���ʱ��

   char sendcompreq_time[6]; // �����ж˷�����������ʱ��

   int compare_flag;	// ���е��ն��˱�־, 0��ʶδ��ʼ����, 1��ʶ�Ѿ�����˵��ն���, 2��ʶ����Ҫ���˵�����

   int sendcompreq_flag;	// ���������ʶ0������, 1��ʶ�Ѿ�����������

   int compare_count;		// ����Ч������ļ��Ĵ���

   char comp_file_path[256]; // �����ļ�·��

} ST_BANK;  



typedef struct

{

	int 	DRTP_BRANCH;

	int 	BCC_BASEFUNCNO;

	int 	TIMEOUT;

	char COMPACC_TIME[2+1];

	char SENDCOMPREQ_TIME[2 + 1];		// �е�������Ҫ�Զ����ļ���������

	int	LOGIN_MODE;

	int	AUTH_MODE;

	int 	LOG_MODE;

	char	DRTP_IP[20];

	int	DRTP_PORT;	

	int 	BankCount;

	int	cur_bankid;

	char SERV_TIME[20];

	ST_BANK	BankUnit[MAX_BANK];

	int trans_money;

}ST_BANK_CONFIG;



//extern ST_BANK  g_BankIni;  //���е�������Ϣ 

extern ST_BANK_CONFIG g_Bank;





typedef struct

{

	char		TradeCode[6];		//sclose_emp	//���״���

	char		TransMoney[9];		//sorder0		//���׽��

	char		ExtraMoney[9];		//sorder1		//���ӽ��׽��

	char		AccountMoney[11];	//sserial1		//У԰���ʻ����

	int		SendNo;				//lvol0			//������ˮ��

	int 		RecvNo;				//lvol1			//���ܷ���ˮ��

	char		TradeDate[8];		//sdate0			//��������	 YYYYMMDD

	char		TradeTime[6];		//stime0			//����ʱ��	 HHMMSS

	char		BankDate[8];			//sdate1			//���д�������

	char		BankTime[6];			//stime1			//���д���ʱ��

	char		Balance[9];			//scust_no		//���п����

	char		RetCode[6];			//schange_emp	//���׽��

	char		CardNo[12];			//sserial0		//У԰������

	int		Notecase;			//lvol2			//У԰����ӦǮ����

	char		BankCardNo[20];		//scust_auth		//���п���

	char		MngFeeFlag;			//sstatus1		//�����ѱ�־

	char		AccountPwd[9];		//semp_pwd		//У԰�˻�����

	char		AccountNewPwd[9];	//semp_pwd2		//У԰�˻�������

	char		BankCardPwd[16];		//sstation0		//�����˻�����

	char		BankCardNewPwd[16];	//sstation1		//�����˻�������

	char		TerminalId[10];		//sorder2		//�ն˱��

	char	 	Reserve1[256]; 	//vsvarstr0         //����MAC����Կ, ���Ȳ�����, �512�ֽ�	

	char	 	Reserve2[256]; 	//vsvarstr1 	

	char		Reserve3[256]; 	//vsvarstr2

	char	 	SencodMagTune[38]; //sbank_acc 	//�ڶ��ŵ�����

	char		ThirdMagTune[105]; //scusttypes		//�����ŵ�����

}INNER_TRANS_REQUEST;



#define	INNER_TRANS_PACKLEN	sizeof(INNER_TRANS_REQUEST)



// �����ļ����ݽṹ

typedef struct

{

	char		file_name[6];			// �ļ���

	char 		date[9];				// ����	

	char 		time[7];				// ʱ��

	char 		file_path[256];			// �ļ�·��, �����ļ���

	int 		flag;					// ���˱�ʶ, 0��ʶδ�ж��˳ɹ�, 1��ʾ���˳ɹ�

	int 		bank_id;				// ��������ID��

}BANK_COMPARE_FILE;					



// �����ļ�����

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


typedef struct
{
	char transtype;		//��������
	char stuempno[31];	//ѧ��
	char custname[31];	//����
	char idno[31];		//���֤��
	char bankcardno[21];//���п���
	int  retcode;		//������
	char retmsg[256];	//������

}tagBankCardRelation;


// �ļ�Ч�����ݽṹ(������Ҫ�ļ�Ч���������Ҫ�õ��˽ṹ)

typedef struct

{

	char liq_money[13];				// ������

	char trade_deal_time[11];		// ���״���ʱ��

	char system_id[7];				// ϵͳ���ٺ�

	char shop_type[5];				// �̻�����

	char service_terms_code[3];		// ������������

	char proxy_node_code[14];		// ����ڵ����

	char send_node_code[14];		// ���ͽڵ����

	char answser_code[3];			// Ӧ����

	char device_phy[9];				// �ܿ����ն˱�ʶ��

	char mark[16];					// �ܿ�����ʶ

	char append_trade_info[104];	// ���ӽ�����Ϣ(�ź��ļ���)

	char transfer_count[11];		// ת�ʱ���

	char packet_identity_code[9];	// ʶ����

	char file_path_name[256];		// �ļ�·��

}BANK_FILE_ADJUST;





/////////////////////////////ISO8583FIELDS///////////////////////////////////

typedef struct ISO8583 

{ 

	int bit_flag; 			/*����������0 -- string, 1 -- int, 2 -- binary*/ 

	char *data_name; 		/*����*/ 

	int length; 			/*�����򳤶�*/ 

	int length_in_byte;		/*ʵ�ʳ��ȣ�����Ǳ䳤��*/ 

	int variable_flag; 		/*�Ƿ�䳤��־0���� 2��2λ�䳤, 3��3λ�䳤*/ 

	int datatyp; 			/*0 -- string, 1 -- int, 2 -- binary*/ 

	char *data; 			/*��ž���ֵ*/ 

	int attribute; 			/*����*/ 

} ISO8583; 

ISO8583 Tbl8583[128] = 
{ 
/* FLD 1 */ {0,"BIT MAP,EXTENDED ", 8, 0, 0, 2, NULL,0}, 
/* FLD 2 */ {0,"RIMARY ACCOUNT NUMBER ", 30, 0, 2, 0, NULL,0}, 
/* FLD 3 */ {0,"ROCESSING CODE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 4 */ {0,"AMOUNT, TRANSACTION ", 12, 0, 0, 1, NULL,0}, 
/* FLD 5 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 6 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 7 */ {0,"TRANSACTION DATE AND TIME ", 10, 0, 0, 0, NULL,0}, 
/* FLD 8 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 9 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 10 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 11 */ {0,"SYSTEM TRACE AUDIT NUMBER ", 20, 0, 0, 1, NULL,0}, 
/* FLD 12 */ {0,"TIME, LOCAL TRANSACTION ", 6, 0, 0, 0, NULL,0}, 
/* FLD 13 */ {0,"DATE, LOCAL TRANSACTION ", 8, 0, 0, 0, NULL,0}, 
/* FLD 14 */ {0,"DATE, EXPIRATION ", 4, 0, 0, 0, NULL,0}, 
/* FLD 15 */ {0,"DATE, SETTLEMENT ", 4, 0, 0, 0, NULL,0}, 
/* FLD 16 */ {0,"NO USE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 17 */ {0,"DATE, CAPTURE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 18 */ {0,"MERCHANT'S TYPE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 19 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 20 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 21 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 22 */ {0,"OINT OF SERVICE ENTRY MODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 23 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 24 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 25 */ {0,"OINT OF SERVICE CONDITION CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 26 */ {0,"NO USE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 27 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 28 */ {0,"field27 ", 9, 0, 0, 0, NULL,0}, 
/* FLD 29 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 30 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 31 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 32 */ {0,"ACQUIRER INSTITUTION ID. CODE ", 6, 0, 2, 0, NULL,0}, 
/* FLD 33 */ {0,"FORWARDING INSTITUTION ID. CODE ", 11, 0, 2, 0, NULL,0}, 
/* FLD 34 */ {0,"NO USE ", 28, 0, 2, 0, NULL,0}, 
/* FLD 35 */ {0,"TRACK 2 DATA ", 37, 0, 2, 0, NULL,0}, 
/* FLD 36 */ {0,"TRACK 3 DATA ",104, 0, 3, 0, NULL,0}, 
/* FLD 37 */ {0,"RETRIEVAL REFERENCE NUMBER ", 20, 0, 0, 0, NULL,0}, 
/* FLD 38 */ {0,"AUTH. IDENTIFICATION RESPONSE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 39 */ {0,"RESPONSE CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 40 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 41 */ {0,"CARD ACCEPTOR TERMINAL ID. ", 8, 0, 0, 0, NULL,0}, 
/* FLD 42 */ {0,"CARD ACCEPTOR IDENTIFICATION CODE ", 15, 0, 0, 0, NULL,0}, 
/* FLD 43 */ {0,"CARD ACCEPTOR NAME LOCATION ", 40, 0, 0, 0, NULL,0}, 
/* FLD 44 */ {0,"ADDITIONAL RESPONSE DATA ", 25, 0, 2, 0, NULL,0}, 
/* FLD 45 */ {0,"NO USE ", 76, 0, 2, 0, NULL,0}, 
/* FLD 46 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 47 */ {0,"field47 ",999, 0, 3, 0, NULL,0}, 
/* FLD 48 */ {0,"ADDITIONAL DATA --- PRIVATE ",999, 0, 3, 0, NULL,0}, 
/* FLD 49 */ {0,"CURRENCY CODE,TRANSACTION ", 3, 0, 0, 0, NULL,0}, 
/* FLD 50 */ {0,"CURRENCY CODE,SETTLEMENT ", 3, 0, 0, 0, NULL,0}, 
/* FLD 51 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 52 */ {0,"ERSONAL IDENTIFICATION NUMBER DATA ", 8, 0, 0, 2, NULL,0}, 
/* FLD 53 */ {0,"SECURITY RELATED CONTROL INformATION", 16, 0, 0, 0, NULL,0}, 
/* FLD 54 */ {0,"ADDITIONAL AMOUNTS ",120, 0, 3, 0, NULL,0}, 
/* FLD 55 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 56 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 57 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 58 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 59 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 60 */ {0,"NO USE ", 5, 0, 3, 0, NULL,0}, 
/* FLD 61 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 62 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 63 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 64 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
/* FLD 65 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 66 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 67 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 68 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 69 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 70 */ {0,"SYSTEM MANAGEMENT INformATION CODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 71 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 72 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 73 */ {0,"NO USE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 74 */ {0,"NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 75 */ {0,"REVERSAL NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 76 */ {0,"NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 77 */ {0,"REVERSAL NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 78 */ {0,"NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 79 */ {0,"REVERSAL NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 80 */ {0,"NUMBER OF INQUIRS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 81 */ {0,"AUTHORIZATION NUMBER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 82 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 83 */ {0,"CREDITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 84 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 85 */ {0,"DEBITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 86 */ {0,"AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 87 */ {0,"REVERSAL AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 88 */ {0,"AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 89 */ {0,"REVERSAL AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 90 */ {0,"ORIGINAL DATA ELEMENTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 91 */ {0,"FILE UPDATE CODE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 92 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 93 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 94 */ {0,"SERVICE INDICATOR ", 7, 0, 0, 0, NULL,0}, 
/* FLD 95 */ {0,"REPLACEMENT AMOUNTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 96 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 97 */ {0,"AMOUNT OF NET SETTLEMENT ", 16, 0, 0, 0, NULL,0}, 
/* FLD 98 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 99 */ {0,"SETTLEMENT INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 100 */ {0,"RECVEING INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 101 */ {0,"FILENAME ", 17, 0, 2, 0, NULL,0}, 
/* FLD 102 */ {0,"ACCOUNT IDENTIFICATION1 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 103 */ {0,"ACCOUNT IDENTIFICATION2 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 104 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 105 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 106 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 107 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 108 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 109 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 110 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 111 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 112 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 113 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 114 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 115 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 116 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 117 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 118 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 119 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 120 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 121 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 122 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 123 */ {0,"NEW PIN DATA ", 8, 0, 3, 2, NULL,0}, 
/* FLD 124 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 125 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 126 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 127 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 128 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
}; 


extern ISO8583 Tbl8583[128];



/////////////////////////////���´�½Լ���Ĵ�����///////////////////////////////////



//���ն�Լ���Ĵ����룬������ظ��´�½���ն˱���Ϊ���µĴ�����

//����Ȧ����޷����룬�����Ҫ������Ը����´�½����������ļ�

#define  E_TRANS_BANKCARD_LOST         	108001	//���п���ʧ

#define  E_TRANS_BANKACC_STATERR        108002	//�����ʻ�״̬����

#define  E_TRANS_BANKACC_NOMONEY        108003	//���п�����

#define  E_TRANS_BANKCARD_PWDERR        108005	//���п��������

#define  E_TRANS_SCHCARD_LOST         	108101	//У԰����ʧ

#define  E_TRANS_SCHCARD_FREEZE         108102	//У԰������

#define  E_TRANS_SCHCARD_UNLOSTING      108103	//�ֿ����Ѿ�Ϊ���״̬

#define  E_TRANS_SCHCARD_LOSTING        108104	//�ֿ����Ѿ�Ϊ��ʧ״̬

#define  E_TRANS_SCHACC_NOEXIT         	108105	//��У԰���ʻ�������

#define  E_TRANS_SCHACC_DESTORY         108106	//�ֿ����Ѿ�����

#define  E_TRANS_RELATION_ERR         	108107	//��Ӧ��ϵ����

#define  E_TRANS_SCHCARD_PWDERR         108108	//У԰�������

#define  E_TRANS_TRANSMONEY_OUTRANGE    108109	//ת�ʽ�����Χ

#define  E_TRANS_ACCMONEY_OUTRANGE      108110	//У԰��������Χ

#define  E_TRANS_BANK_NODECIDE         	108111	//����δ������

#define  E_TRANS_BANK_NOANSWER         	108112	//���г�ʱ����Ӧ��

#define  E_TRANS_BANK_NETERR         	108113	//�����������

#define  E_TRANS_BANK_SERVICE_NOEXIT    108114	//����û������

#define  E_TRANS_RELATION_NOEXIT        108115	//û�ж�Ӧ��ϵ

#define  E_TRANS_FUNC_NONSUPPORT        108116	//�˹����ݲ���֧��

#define  E_TRANS_BANK_RECVERR         	108117	//���з������ݴ���

#define  E_TRANS_SCHOOL_NETERR         	108118	//У԰���������

#define  E_TRANS_INNER_TIMEOUT         	108119	//�ڲ���ʱ

#define  E_TRANS_TERM_NOLOGIN         	108120	//�ն�δ��½

#define  E_TRANS_SCHCARD_TWICE		108121	//�ͻ��ж��ſ�

#define  E_TRANS_SCHCARD_WFAIL	108122	// У԰��д��ʧ��

#define  E_DB_SUBSYSPARAMS_D               108123	//��ϵͳ������ɾ������

#define  E_DB_SUBSYSPARAMS_I                108124	//��ϵͳ������������

#define  E_DB_SUBSYSPARAMS_N               108125	//��ϵͳ�������ѯ����޼�¼

#define  E_DB_SUBSYSPARAMS_R               108126	//��ϵͳ�������ȡ����

#define  E_DB_SUBSYSPARAMS_E               108127	//��ϵͳ�������Ѵ���

#define  E_TRANS_BANK_FUNC_NONSUPPORT	108128	//ָ�����в�֧�ָù���

#define  E_TRANS_BANK_CARD_NONSUPPORT	108129	//ת��ϵͳĿǰ��֧���������п�

#define  E_TRANS_UNKNOW_ERROR         	109000	//����δ֪����



////////////////////////////�����нӿڵĳ���ԭ��///////////////////////////////////////////

int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance);

int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no);

int Bank_Undo(INNER_TRANS_REQUEST * pNode);

int Bank_CheckLine();

int Bank_SignIn(INNER_TRANS_REQUEST *pNode);

int Bank_SignOut();

int Bank_AdjustCompareFile(INNER_TRANS_REQUEST *pNode, ST_BANK *bank, void *var_object1, void * var_object2, void *var_object3);

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet);





//#ifdef __cplusplus

//}

//#endif



#endif


