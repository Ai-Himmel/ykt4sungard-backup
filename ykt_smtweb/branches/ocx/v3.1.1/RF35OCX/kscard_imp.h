// kscard.cpp : Defines the initialization routines for the DLL.
#ifndef __KSCARD_IMP_H
#define __KSCARD_IMP_H
#pragma warning(disable:4786) 

#include <Windows.h>

#define IN 
#define OUT
#define FIELDMAXNUM			100
//ע:CF=CARDFIELD
//��������Ϣ
#define CF_START			1		//��ʼ��
#define CF_CARDNO			2		//���׿���
#define CF_SHOWCARDNO		3		//��ʾ����
#define CF_FEETYPE			4		//�շ���𣨿������
#define CF_SUBSIDYNO		5		//�������κ�
#define CF_CARDVERNO		6		//���汾��
#define CF_CARDSTATUS		7		//��״̬0 ����1-����2���Ῠ3-��ʧ��4_ע����5���ڿ�
#define CF_STARTDATE		8		//��������
#define CF_EXPIREDATE		9		//��������
#define CF_PUBLISHID		10		//���з���ʶ
#define CF_CARDTYPE			11		//�����
#define CF_APPTYPE			12		//Ӧ������ 
#define CF_CARDSTRUCTVER	13		//���ṹ�汾��Ӧ�ð汾��
// ��ݸ��ݸ�˿�
#define CF_CITYCODE         14      //���д���
#define CF_INDUSTRYCODE     15      //��ҵ����
#define CF_INTERACTFLAG     16      //������ͨ��ʶ
#define CF_SUBFEETYPE       17      //�������
#define CF_APPSERIALNO      18      //Ӧ�����к�
//�ֿ�����Ϣ
#define CF_SCHOOLCODE		20		//У������
#define CF_CUSTID			21		//�ͻ���
#define CF_CUSTTYPE			22		//�ͻ����
#define CF_STUEMPNO			23		//ѧ����
#define CF_NAME				24		//����
#define CF_SEX				25		//�Ա�
#define CF_DEPTCODE			26		//���Ŵ���
#define CF_IDNO				27		//֤������
#define CF_IDTYPE			28		//֤������
//���п���
#define CF_BANKCARDNO		30		//���п���


#define CF_LOCKTERMID       34      //��������ʱ�ն˻���
#define CF_LOCKTRANSDATE    35      //������������
#define CF_LOCKTRANSTIME    36      //��������ʱ��

#define CF_DAYSUMAMT		37		//�����ۼƽ��׽��
#define CF_LOCKCARDCNT		38		//��������ʱ���״���
//���ײ���
#define CF_SINGLEMAXAMT		41		//���������޶�
#define CF_DAYMAXAMT		42		//�������ۼ��޶�
//������ϸ
#define CF_TRANSDTL_BEGIN	44
#define CF_CARDCNT			44		//�����״���(���һ�ν���)
#define CF_TRANSAMT			45      //���׽��(���һ�ν���)
#define CF_TRANSTYPE		46		//��������(���һ�ν���)
#define CF_TERMID			47      //�����ն˻����(���һ�ν���)
#define CF_TRANSDATE		48		//��������(���һ�ν���)
#define CF_TRANSTIME		49		//����ʱ��(���һ�ν���)
#define CF_TRANSDTL_END		49

//�����			
#define CF_CARDBAL			50		//�����
//������
#define CF_CARDPWD			51		//������
//��ˮ��Ϣ
#define CF_DPSCNT			64		//��ֵ���״���
#define CF_PAYCNT			65		//���ѽ��״���

#define CF_NORMALLYOPEN     80      //��������־
#define CF_END				99		//������־
#define LEN_CARDNO			10
#define LEN_SHOWCARDNO		10
#define LEN_CARDSTATUS		1
#define LEN_PUBLISHID		2
#define LEN_CARDTYPE		1
#define LEN_FEETYPE			1
#define LEN_STARTDATE		4
#define LEN_EXPIREDATE		4
#define LEN_SUBSIDYNO		4
#define LEN_CARDVERNO		7
#define LEN_DEVICEID		6
#define LEN_CARDSTUCTVER	1
#define LEN_CARDSN			8
#define LEN_OPERNO			10 //����Ա��

#define LEN_CUSTID			4		
#define LEN_CUSTTYPE		1
#define LEN_STUEMPNO		20		
#define LEN_SEX				1
#define LEN_NAME			32		
#define LEN_DEPTCODE		20		
#define LEN_IDNO			32		
#define LEN_IDTYPE			28		
#pragma pack(1)	
typedef struct {
 	byte	ucCardNo[10];	//PSAM���к�
	byte	ucCardVerNo;	//PSAM�汾��
	byte	ucCardType;		//��Կ������
	byte    ucCmdVerNo;		//ָ��汾
	byte	ucFCI[1];		//�������Զ���FCI����
}ST_PSAMCARD15;

typedef struct {
 	byte	ucKeyIndex;	//������Կ������
	byte	ucPublishID[8];	//���з�ID		
	byte	ucUserID[8];	//ʹ�÷�ID
	byte    ucStartDate[4];	//��������
	byte	ucExpireDate[4];//��Ч����
}ST_PSAMCARD17;
typedef struct {
	char sCardNo[21];		//PSAM����
	size_t nCardType;		//PSAM������
	size_t nCardVer;		//���汾
	char sTermID[13];	//�ն˱��
	size_t nTermSeqno;		//�ն˽������
	size_t nKeyIndex;		//��Կ������
	char sStartDate[9];	//��������
	char sExpireDate[9];//��Ч����
	char sPublishID[17];	//���з���ʶ
	char sUserID[17];	//ʹ�÷���ʶ
}ST_PSAMCARD;

typedef struct {
	 byte ucCardNo[LEN_CARDNO];			//���׿���
	 byte ucShowCardNo[LEN_SHOWCARDNO];	//��ʾ����
	 byte ucCardStatus;	//��״̬0 ����
	 byte ucCardVerNo[LEN_CARDVERNO];	//���������汾��
	 byte ucDeviceID[LEN_DEVICEID];		//�豸ID
	 byte ucFeeType;		//�շ����
	 byte ucCardStructVer;//���ṹ�汾
	 byte ucStartDate[LEN_STARTDATE];	//��������
	 byte ucExpireDate[LEN_EXPIREDATE];	//��������
	 byte ucSubsidyno[4];			//�������κ�
	 byte ucPublishID[2];		//���з���ʶ
	 byte ucCardType;		//�����
	 byte reserve[5];		//����
}ST_BASEINFO;
typedef struct {
	 byte ucName[LEN_NAME];				//����
	 byte ucIDNo[LEN_IDNO];				//֤������
	 byte ucIDType;			//֤������
	 byte ucSex;				//�Ա�
	 byte ucStuempNo[LEN_STUEMPNO];		//ѧ����
	 byte ucDeptCode[LEN_DEPTCODE];		//���Ŵ���
	 byte ucCustType;		//�ͻ����
	 byte ucCustID[4];			//�ͻ���
}ST_PERSONINFO;
typedef struct {
	byte ucSingleMaxAmt[3];
	byte ucDayMaxAmt[3];
}ST_TRANSPARA;
typedef struct {
	byte ucCardCnt[2];		//���������
	byte ucLimit[3];		//͸֧�޶�
	byte ucTransAmt[4];		//���׽��
	byte ucTransType;		//��������
	byte ucTermID[6];		//�ն˱��
	byte ucTransDate[4];	//��������
	byte ucTransTime[3];	//����ʱ��
}ST_TRANSDTL;

typedef struct {
	int recordno;		//��¼��
	int exist;			//�����¼���ڣ���Ϊ1������Ϊ0
	char transdate[9];	//��������(YYYYMMDD)
	char transtime[7];	//����ʱ��(HHMMSS)
	int paycnt;			//���Ѵ���
	int cardbefbal;		//����ǰ���
	int transamt;		//���׽��(��������)
	int otherfee;		//����
	int extamt;			//��д���(��ǮΪ����ǮΪ��)
	int shopid;			//�̻���
	char termno[13];	//�ն˻����(PSAM���е��ն˺�)
	int termsno;		//�ն˽������(����TAC��)
}ST_PAYDTL;
//������ϸ�ṹ

// ���׽ṹ
typedef struct {
	int     nTermID;		//�豸�ն˱��
	int		nCardNo;		// ���׿���	
	char	sCardPhyID[17];	// �����к�
	size_t  nDpsCardCnt;	// ����ǰ����ֵ��
	size_t  nPayCardCnt;	//����ǰ���Ѵ���
	size_t  nSubsidyNo;		//�������κ�
	int		nBefBalance;	// ����ǰ������λ��
	int		nAftBalance;	// ���׺�����λ��
	int		nTransAmt;		// ��ֵ����λ��
	char	sTransDate[9];	// ��������
	char	sTransTime[7];	// ����ʱ��
	char  	sTermno[13];	// PSAM���ն˺�
	size_t  nTermSeqno;		// �ն˽������к�
	char    sRandom[9];		//�����
	char	sOperCode[9];	//����Ա����
	size_t	nFundType;		//��ֵ���� 1 �ֽ�2 ֧Ʊ 3 ���ѱ� 4 ����
	char	sVoucherNo[24];	//��ֵƱ�ݺ�
	char	sCardPwd[7];	//������
	int     nTransType;		//�������� 0-��ֵ 1�ۿ�
	int     nPayCode;		//֧������
	int		nPayType;		//֧������,������ʹ��
	///////////////����Ϊ���ֵ//////////////////////////////
	char	sRefNo[15];		//���ײο���
	char 	cRetryFlag;		//���Ա�־,������Ա�־��Ϊ0�����������
	char    cGetProveFlag;	//��Ҫȡ����ȷ�ϱ�־
	char    sMac[9];		//MAC
	size_t	nHostSeqno;		//����������ˮ��
	int		nErrCode;		//������
	char	sErrMsg[256];	//������Ϣ
}ST_TRANSPACK;

#pragma pack()
//���ô�����Ϣ
int __stdcall ks_init();
void __stdcall ks_setlasterr(char *errmsg,int errcode=-1);
//��ȡ��̬�������Ϣ
char* __stdcall ks_geterrmsg(char *errmsg);

void __stdcall ks_getversioninfo(char *version,char *builddate,char *desc);

//ȡһ��ͨ������ʱ��
int  __stdcall ks_getsvrdatetime(char *svr_date,char *svr_time);

int __stdcall ks_licence(const char *lisence,const char *pwd);

/*int  dc_init(int port,long baud);
�� �ܣ���ʼ��ͨѶ��
�� ����port��ȡֵΪ0��19ʱ����ʾ����1��20��Ϊ100ʱ����ʾUSB��ͨѶ����ʱ��������Ч��
baud��ΪͨѶ������9600��115200
�� �أ��ɹ��򷵻ش��ڱ�ʶ��>0��ʧ�ܷ��ظ�ֵ������������
����int icdev;
icdev=dc_init(0,9600);//��ʼ������1��������9600*/
int __stdcall ks_openport(int port,int band);
/* int dc_exit(int icdev);
�� �ܣ��رն˿�
�� ����icdev��ͨѶ�豸��ʶ��
�� �أ��ɹ�����0
����dc_exit(icdev);*/
int __stdcall ks_closeport();
/* int ks_beep(unsigned int _Msec);
�� �ܣ�����
unsigned int _Msec������ʱ�䣬��λ��10����
�� �أ��ɹ��򷵻� 0
����int st;
st=ks_beep(10);            ����100����*/
void __stdcall ks_beep();
void __stdcall ks_beeperr();
int __stdcall GetRandomNum(byte *uRandomNum,char *sRandomNum);

/*
˵�������ö�д����Ҫ����һ�ֿ���������д���ϵ�ȱʡ��ʱ���Ƕ�TYPEA������
	����˵����HANDLE icdev dc_init���ص��豸��������
	cardtype����Ϊ'A'��ʱ���ʾ���ö�д����'B'��ʾ��TYPE B����
		���أ��ɹ��򷵻� 0��
		
			����:
			int st;
			st= ks_setcardtype ('B');//���ö�TYPE B������
*/
int __stdcall ks_setcardtype(int cardtype);
/*int ks_halt();
  �� �ܣ���ֹ�Ըÿ�����
  �� ����icdev��ͨѶ�豸��ʶ��
 �� �أ��ɹ��򷵻�0
 ����st=dc_halt(icdev);
 ˵����ʹ��dc_card()����ʱ���и�_Mode���������_Mode=0���ڶԿ����в�����Ϻ�ִ��ks_halt();��ÿ�����HALTģʽ�������ѿ��ƿ���Ӧ���ٽ�������Ѱ�����ſ���
*/
//SAM
int __stdcall  ks_halt();

/*
int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
�� �ܣ�Ѱ�����ܷ����ڹ���������ĳ�ſ������к�(�ú���������dc_request,dc_anticoll,dc_select�����幦��)						
						�� ����icdev��ͨѶ�豸��ʶ��						
						_Mode��Ѱ��ģʽmode_card						
						_Snr�����صĿ����к�						
						�� �أ��ɹ��򷵻� 0						
						����int st;
*/


int __stdcall ks_reset(int msec);

//Ѱ��
//int __stdcall ks_card(unsigned long *_Snr);

int __stdcall ks_card(char *sCardPhyID);
// 
int __stdcall ks_mf_card(char *sCardPhyID);
/*
1.5.1.	���ÿ�����������
 	����ԭ�ͣ�int ks_setfield(int mode,int mask)
 	��ڲ�����
int  mode - ����/д��ģʽ��1��ʾ�ȶ���д��2��ʾ��д��� 2��д���
int  mask - ��/д������Ӧ��������������������������
 	���ڲ�����
	��
 	�������أ� 
0 --�ɹ����������������*/
//���ø��ֶζ�ģʽ
void __stdcall ks_setfieldreadmode(int fieldID);
//���ø��ֶ�дģʽ
void __stdcall ks_setfieldwritemode(int fieldID);
//���ø��ֶζ�дģʽ
void __stdcall ks_setfieldallmode(int fieldID);
//������ֶζ�ģʽ
void __stdcall ks_clearfieldreadmode(int fieldID);
//������ֶ�дģʽ
void __stdcall ks_clearfieldwritemode(int fieldID);
//������ֶ�����ģʽ
void __stdcall ks_clearfieldallmode(int fieldID);
//��������ֶεĶ�ģʽ
void __stdcall ks_clearallfieldreadmode();
//��������ֶε�дģʽ
void __stdcall ks_clearallfieldwritemode();
//��������ֶεĶ�дģʽ
void __stdcall ks_clearallfieldallmode();

int __stdcall ks_getfieldval(int fieldID,char *fieldval);
/*1.5.6.	����д�ֶ�����
����ԭ�ͣ�int ks_set_card_data(int mask,const char *data)
��ڲ�����
int mask - ��/д��������Ӧ��������������������	
int data - ������ֵ
���ڲ�����
��
�������أ� 
0 --�ɹ����������������*/
int __stdcall ks_setfieldval(int fieldID,const char *fieldval);
/*1.5.4.	��ȡ����Ϣ
	����ԭ�ͣ�int ks_read_card()
	��ڲ�����
	��
	���ڲ�����
	��
	�������أ� 
	0 --�ɹ����������������*/
int __stdcall ks_readcard();

//����7+1��,��cpu����cardtype=0,��mifare1����cardtype=1,ȫ����cardtype=2
int __stdcall ks_readcard2(int cardtype);
/*1.5.7.	д����Ϣ
����ԭ�ͣ�int ks_write_card ()
��ڲ�����
��
���ڲ�����
��
�������أ� 
0 --�ɹ����������������*/
int __stdcall ks_writecard (const char *sCardPhyID=NULL);
/*1.5.8.	��֤����
����ԭ�ͣ�int ks_verify_pin(char pin[7])
��ڲ�����
char pin[7]  -6�������ַ��ĸ���PIN
���ڲ�����
��
�������أ� 
0 --�ɹ����������������
*/
//�޸Ŀ�״̬
//state  0-���� 1���� 2���� 3��ʧ 4ע�� 5����
int __stdcall ks_modifystatus(int state);
//�޸�����
int __stdcall ks_modifypasswd(const char oldpwd[7],const char newpwd[7]);
//��������
int __stdcall ks_resetpasswd(const char *cardphyid,const char newpwd[7]);
//��֤����

//��֤����
int __stdcall ks_verifypin(char pin[7]);
/*1.5.10.	Ӧ������
����ԭ�ͣ�int ks_lockapp()
��ڲ�����
��
���ڲ�����
��
�������أ� 
0 --�ɹ����������������*/
int __stdcall ks_lockapp();
/*1.5.11.	Ӧ�ý���
����ԭ�ͣ�int ks_unlock_application()
��ڲ�����
��
���ڲ�����
��
�������أ� 
0 --�ɹ����������������*/
int __stdcall ks_unlockapp();
//ͨѶ��ʼ��
int __stdcall ks_comminit(const char *svrip,int svrport,int svrfunc);
//�ն�ǩ��
int __stdcall ks_login(int termid,int& shopid,char shopname[61]);
//�����豸����Աǩ��
int __stdcall ks_usersignin(const char *user,const char* userpwd);
// ��ֵ
int __stdcall ks_deposit(ST_TRANSPACK *transpack,int must_online);
// �ۿ�
int __stdcall ks_payment(ST_TRANSPACK *transpack,int must_online);
//���ѳ����������ײο��ţ�
int  __stdcall ks_pay_reverse(ST_TRANSPACK *payment,int must_online);
//int  __stdcall ks_deposit_init(IN int Termid,IN int nTransAmt,OUT int& nCardBal,OUT int& nCardCnt,OUT char *sRandomNum,OUT char sMac1);

//int  __stdcall ks_deposit_init(IN int Termid,IN int nTransAmt,char *deposit_data);

//int  __stdcall ks_deposit_end(char *sTransDate,char *sTransTime,char *sMac2);
//���ÿ����
int  __stdcall  ks_setcardbal(ST_TRANSPACK *transpack);
//����MAC
int __stdcall ks_calcmac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
int __stdcall ks_calcsafemac(const char* szCmdBuf,char *szMac);
int __stdcall CalcDF03SafeMac4Sam(const char *szCardNo,const char *szCmdbuf,char *szMac);
//����ĸ��Կ����
int __stdcall ks_encryptkey(unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);


//����Ƿ���Կ�Ѿ�����
//����ֵ0- δ����1����

int __stdcall ks_checkloadkeys();

//װ����Կ
int __stdcall ks_loadcardkeys(const char *sKeyCardPwd);

//ж����Կ
void __stdcall ks_unloadcardkeys();
//�û�����ʼ��
int __stdcall ks_publishusercard(const char *sCardPhyID,const char *szShowCardNo);
//�����û���,��д��ʾ����
//useflag Ϊ1ʱ��ʾȡ�������ʾ���� Ϊ0ʱ���������ʾ����Ϊ�գ���ȡ����ģ�����ȡ���ڵġ�
int __stdcall ks_recycleusercard();

int __stdcall ks_refineusercard(int nUseFlag,const char *szCardShowNo);

//PSAM������
/*
int ks_setcpu4sam(int SAMID);
˵��������Ҫ������SAM���� 

unsigned char SAMID --- ����Ҫ�����Ŀ�����,1�� 2�� 3 ��ΪSAM1(����) SAM2 SAM3 

���أ�<0 ���������ֵΪ�����

=0 �ɹ�
*/
int __stdcall ks_setcpupara4sam(int SAMID);

//PSAM���ϵ縴λ
int __stdcall ks_samcpureset();
//PSAM���ϵ縴λͬ�ϴ�����
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff);
//����PSAMK��
int __stdcall ks_publishpsamcard(ST_PSAMCARD* PSAMCard);
int __stdcall ks_recyclepsamcard();
int __stdcall ks_readpsamcard(ST_PSAMCARD* PSAMCard);
//��ȡPSAM ���ն˱��
int __stdcall ks_readpsamtermno(char *termno,int need_request=0);
//��ȡ�ն˽������
int __stdcall ks_readpsamtermseqno(int& termseqno,int need_request=0);
//����У��
int __stdcall ks_verifypasswd(const char *sCardPhyID,const char *cardpasswd,int& iIsPass);
//����Ƿ��¡��Կ�Ѿ�����
//����ֵ0- δ����1����
int __stdcall ks_checkloadclonekeys();
//װ����Կ����¡��ʹ��
int __stdcall ks_loadkeys4clone(const char sKeyCardPin[7]);
//��¡��Կ��
int __stdcall ks_clonekeycard(const char sCloneCardPin[7]);
//������Կ�������ݿ�
int __stdcall ks_savekeys();
//��������ϸ��ˮ
int ks_readpaydtl(int recordno,ST_PAYDTL *paydtl);
//����MF1��������Կ
int __stdcall ks_setmifare1key(const char sWorkKey[17]);

// ��ʼ���󸶷�
int __stdcall ks_init_postpaid(ST_TRANSPACK *transpack,int must_online);
// �󸶷ѿۿ�
int __stdcall ks_postpaid(ST_TRANSPACK *transpack,int must_online);
//������ֵ��ʼ��
int  __stdcall ks_rechangeinit(ST_TRANSPACK *rechange);
//����������ֵ
int  __stdcall ks_rechange(ST_TRANSPACK *rechange);
//֧����ʼ��
int  __stdcall ks_payinit(ST_TRANSPACK *payment,int online);
//��ʽ֧��
int  __stdcall ks_pay(ST_TRANSPACK *payment);
//��������;�ο�ʱ�����û�û�����·ſ�����Ҫ���ñ��������º�̨��¼Ϊд��ʧ��
int  __stdcall ks_dotransunprove(ST_TRANSPACK *transpack);
//��������;�ο�ʱ�����û�û�����·ſ�����Ҫ���ñ�����ȡ������֤
//transflag1-��ֵ 2���� cardcnt ����ǰ���ѻ��ֵ����
int __stdcall ks_gettransprove(int transflag,short cardcnt);
//���ѳ���
int  __stdcall ks_paycancel(ST_TRANSPACK *payment);

int __stdcall ks_getcardstatus(int cardno,char *statuscode,char *statusinfo);
//////////////////////////////////////////////////////////////////////////
// ���ڿ�·��ع���
#pragma pack(1)
typedef struct {
	int money; // �������
	int pre_money; // �ϴ����Ѷ�
	char add_time[15]; // �ϴγ�ֵʱ��
	int add_count; // ��ֵ����
}sr_water_pack_t;

typedef struct {
	int cardno; // ���׿���
	int cardtype; // �����
	int custno; // �ͻ���
}sr_water_info_t;

#pragma pack()

int __stdcall ks_sr_publishcard(sr_water_info_t *info);
int __stdcall ks_sr_recyclecard();
int __stdcall ks_sr_readmoney(sr_water_pack_t *pack);
int __stdcall ks_sr_setmoeny(int money,int cnt);

//////////////////////////////////////////////////////////////////////////
// һ��ͨˮ����ؽӿڶ���
#pragma pack(1)
typedef struct {
	int cardno; // ���׿���
	int custno; // �ͻ���
	int cardtype; // �ͻ����
	char expiredtime[9]; // ��Ч��
	int lockflag; // ������־��00 ������FF����
}ks_water_info_t;

typedef struct {
	int cardno; // ���׿���
	int custno; // �ͻ���
	int cardtype; // �ͻ����
	char expireddate[9]; // ��Ч��
	int lockflag; // ������־��00 ������FF����
	//////////////////////////////////////////////////////////////////////////
	// Ǯ����Ϣ
	int money; // �����
	int totalmoney; // ��ֵ�ܽ��
	char addtime[15]; // ��ֵʱ��
	int addcount; // ��ֵ����
	// ˮ��1
	int price1;
	// ˮ��2
	int price2;
	// ˮ��3
	int price3;
}ks_water_pack_t;

typedef struct {
	char workkey[17];			// ������Կ
	int minmoney;				// ��Ǯ��Ԥ�����
	int maxmoney;				// ��Ǯ���������
	int unit;					// �Ʒѵ�λ����/��)
	int transmoney;				// ����ת�˵�λ
	int unitmoney;				// ����
	int priceindex;				// ˮ������
	int watersect;				// ˮ��Ǯ��������
	int cardflag;				// ��������־
	int termid;					// �ն˺�
}ks_water_param_t;

//////////////////////////////////////////////////////////////
// ����ԭ����ˮ�ز�����ģ��
/******************************************************/
// ���ʽṹ
/******************************************************/
typedef struct  
{
	BYTE time_ladder[1];				// ʱ�����
	BYTE deduct_time[1];				// �۷ѵĵ�λʱ�䣬����Ϊ��λ
	BYTE deduct_fee[1];					// �۷ѵĵ�λ���Է�Ϊ��λ
}FEE_RATE;

/******************************************************/
// ��ǰȨ�޵ķ��ʸ���
/******************************************************/
typedef struct
{
	short right_flag;					// Ȩ�ޱ�־, 1��, 0�ر�
	short right_num;					// ���뵱ǰȨ���µķ��ʸ���
	FEE_RATE fee_rate[5];				// �������Ϊ5��, ��ʵ��һЩû���õ�
}FEE_RIGHT_NO;

/*******************************************************/
// ���ʿ��ṹ˵��
/*******************************************************/
typedef struct  
{
	BYTE water_card_flag[5];			// ˮ�ؿ���־
	char packet_num;					// ˮ��Ǯ����
	BYTE main_work_key[9];				// ��������Կ(����)
	BYTE packet_work_key[9];			// СǮ��������Կ(����)
	BYTE work_mode;						// ����ģʽ
	int water_packet_limit;				// ˮ��Ǯ���޶�
	int transfer_limit;					// ˮ��ת���޶�
	BYTE data_length[3];				// ���ݳ���
	BYTE check_crc[2];					// Ч���ֽ�
	FEE_RIGHT_NO fee_right_num[256];	// ���÷��ʵĸ���
}FEE_RATE_CARD_INFO;


#pragma pack()

#define KS_SZROAD_WATER 1		// ��·ˮ��
#define KS_YNCS_XT_WATER 2		// �ƽ�ְˮ��
#define KS_HD_WATER 3			// ����ѻ�ˮ��
#define KS_LEGACY_WATER 4		// ͨ�����
#define KS_SZLLDF_WATER 5       // �������£�������·�﷽ˮ��

int __stdcall ks_water_publishcard(int watertype,ks_water_pack_t *pack);
int __stdcall ks_water_recyclecard(int watertype);
int __stdcall ks_water_readmoney(int watertype,ks_water_pack_t *pack);
int __stdcall ks_water_writemoney(int watertype,ks_water_pack_t *pack);


/**
 \brief ����ˮ�ز�����
 \param watertype - ˮ�س�������
 \param param - ������ʹ�õĲ���ֵ
 
 1. ���������
    unsigned char workkey[8];	// ������Կ�� ��д 0x01,0x02,0x03,0x04,0x05,0x06
	int minmoney;				// Ԥ�����,  ��ˮ�������ʹ�ã���ʾԤ����ˮ������λΪ�֣� ��ˮ����0
	int maxmoney;				// ��Ǯ��������ޣ� ��ʹ��
	int unit;					// �Ʒѵ�λ����/��) ����ʹ��
	int transmoney;				// ����ת�˵�λ   �� ��ˮ�������ʹ�ã���ʾÿ��ת�˵�ˮ������λΪ�֣���ˮ����0
	int unitmoney;				// ����   �� ��ˮ����ˮ��ͨ�ã���ʾÿ��ˮ�۸񣬵�λΪ ��/��
	int priceindex;				// ˮ������ �� ��ʹ��
	int watersect;				// ˮ��Ǯ����� �� ��ˮ����ˮ��ͨ�ã���ʾ�û���ʹ�õĿ�ţ���Ҫ��Ϊһ��ͨȫ�ֲ�����������
	int cardflag;				// ��������־�� 0 ��ʾ��������1 ��ʾ���㿨����Ϊ���㿨ʱǰ�����в�������ʹ��
	int termid;					// �ն˺ţ���ˮ����ˮ��ͨ�ò������� 1
 */
int __stdcall ks_water_publishparamcard(int watertype,ks_water_param_t *param);
int __stdcall ks_water_recycleparamcard(int watertype);
int __stdcall ks_water_readparamcard(int watertype,ks_water_param_t *param);
int __stdcall ks_water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO *fee_rate);
int __stdcall ks_water_read_legacycard(int watertype,FEE_RATE_CARD_INFO *fee_rate);
int __stdcall ks_water_dump_legacycarddata(int watertype);
#endif
