#ifndef	__BANK_H__
#define	__BANK_H__

#ifdef __cplusplus
extern "C" {
#endif
 /////////////////////////���������ݿ�/////////////////////////////////////
#define MAX_RANGE 20
#define MAX_BANK 5
#define	TRANS_INI_FILE 			"./trans.ini"		//ini�ļ�

typedef struct
{
   char szBankIP[20];  // ���ж˵�ip��ַ
   int  iBankPort;         // ���ж˵Ķ˿ں�
   int  iBankTimeout;    // ���ж˵����ӳ�ʱʱ��
   int  iBankID;		//���б�ʶ�ţ���Ҫ���̨�����ֵ䱣��һ��
   char  szBankCardRange[MAX_RANGE][20];  // ���п��ŷ�Χ
   int	  iAuthMode;		//��֤��ʽ���������п����뻹��У԰������
   char  szBankAccountNO[17];

} ST_BANK;  

typedef struct
{
	int 	DRTP_BRANCH;
	int 	BCC_BASEFUNCNO;
	int 	TIMEOUT;
	char COMPACC_TIME[2+1];
	int	LOGIN_MODE;
	int	AUTH_MODE;
	int 	LOG_MODE;
	char	DRTP_IP[20];
	int	DRTP_PORT;	
	int 	BankCount;
	int	cur_bankid;
	char SERV_TIME[20];
	ST_BANK	BankUnit[MAX_BANK];
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
	char		AccountPwd[6];		//semp_pwd		//У԰�˻�����
	char		AccountNewPwd[6];	//semp_pwd2		//У԰�˻�������
	char		BankCardPwd[16];		//sstation0		//�����˻�����
	char		BankCardNewPwd[16];	//sstation1		//�����˻�������
	char		TerminalId[10];		//sorder2		//�ն˱��
}INNER_TRANS_REQUEST;

#define	INNER_TRANS_PACKLEN	sizeof(INNER_TRANS_REQUEST)


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


#ifdef __cplusplus
}
#endif

#endif

