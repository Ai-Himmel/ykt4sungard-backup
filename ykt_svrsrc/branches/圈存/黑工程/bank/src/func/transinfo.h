/* ----------------------------------------------------------
 * �������ƣ�transinfo.h
 * �������ڣ�2004-08-24
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�����ת��ͷ�ļ�
 * ----------------------------------------------------------
 * �޸�����: 2004-09-09
 * �޸���Ա: ������
 * �޸�����: ͳһ�淶����
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ
 * ----------------------------------------------------------
 * �޸�����: 2005-03-10
 * �޸���Ա: ����
 * �޸�����: ��������ͨ�Ų����Ƶ�bank.h������bu������룬��bankguard����
 * �汾��Ϣ��1.0.1.1
 * ��ע��Ϣ
 * ----------------------------------------------------------*/


#ifndef	__transinfo_h__
#define	__transinfo_h__
#include "bank.h"

//////////////////////////// constant defined ///////////////////////////////
#ifndef	NULL
#define	NULL	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

//Ȧ���õ���ȫ�������ļ�����
extern int DRTP_BRANCH;
extern int BCC_BASEFUNCNO;
extern int TIMEOUT;
extern char  COMPACC_TIME[2+1];
extern int	 LOGIN_MODE;
extern int  AUTH_MODE;
extern char	DRTP_IP[20];
extern int		DRTP_PORT;	

 /////////////////////////// �ڲ����״���  ///////////////////////////////
#define TRADE_INNER_CHKPWD		240000	//����У��
#define TRADE_INNER_QUERYBANK		240007	//��ѯ���п�
#define TRADE_INNER_TRANS			240001	//����ת��
#define TRADE_INNER_AUTOTRANS		240002	//����ת��
#define TRADE_INNER_ELEC			242001 //����Ǯ��ת��
#define	TRADE_INNER_YCT				242002 //���ͨת��
#define	TRADE_INNER_TRANS_REVERSE	240003 //���п�ת�˹��ܳ���
#define TRADE_INNER_FEE			240005	//�ɷ�
#define TRADE_INNER_ADDRELATION	240008	//���Ӷ�Ӧ��ϵ
#define TRADE_INNER_DELRELATION	240009 	//5��ɾ����Ӧ��ϵ
#define TRADE_INNER_POSLOGIN		240101 	//6����½
#define TRADE_INNER_QUERYINNER	240102 	//7����ѯУ԰��
#define TRADE_INNER_CHANGEPWD	930003 	//8���޸���������
#define TRADE_INNER_LOST			930001 	//9��У԰����ʧ
#define TRADE_INNER_UNLOST		930002 	//10��У԰�����
#define TRADE_INNER_QUERYSERIAL	240106	//��ѯת����ˮ
#define TRADE_INNER_LOGIN			241031	//ǰ�û�������ǩ��
#define TRADE_INNER_DETRANS		241011	//ת�ʳ���
#define TRADE_INNER_WRITEERRCARD 240107	//д��ʧ�ܸ��¿�״̬
#define TRADE_INNER_QUERYSUBSIDY	240103	//��ѯ����
#define TRADE_INNER_GETSUBSIDY	240104	//��ȡ����
#define TRADE_INNER_UPDATE_CARDINFO 240105	//���¿���Ϣ
#define TRADE_INNER_TRANSFER_WFAIL	240111	//ת��д��ʧ��
#define TRADE_INNER_QUERYWATER	240201	//ˮ��ת����ϸ��ѯ
#define TRADE_INNER_BUYWATER		240202	//ˮ��ת��
#define TRADE_INNER_DEVBEATE	240108  //Ȧ�������
 #define TRADE_INNER_UPDATECOMSUMELIMIT 846320 //�޸������޶�


//////////////////////////״̬����////////////////////////////////////////
// ������е�½״̬������Ҫ���״̬�ĵط����øúꡣ����б�Ҫ�������ź�������
#define BANK_LOGIN	(shm[1]==1)

// �������ͨ��״̬������Ҫ���״̬�ĵط����øúꡣ����б�Ҫ�������ź�������
#define BANK_CONNECT	(shm[3]==1)

// !!! ��ȡ����������ʱ��һ��Ҫ��ȡ�ź��� p(semid); operations...; v(semid)


 /////////////////////////���������ݿ�/////////////////////////////////////

/****************************************************
У԰�˽��״�����
****************************************************/

//POS��½	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode);

//��ѯУ԰�����
int Pos_QuerySchool(INNER_TRANS_REQUEST * pNode);

//��ѯ���п����
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode);

//�޸�У԰������
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode);

//��ʧУ԰��
int Pos_LostCard(INNER_TRANS_REQUEST * pNode);

//���У԰��
int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode);

// ת�˳���
int Pos_Bank_Reverse(INNER_TRANS_REQUEST *pNode);
//POSת��
int Pos_Transfer(INNER_TRANS_REQUEST * pNode,int txcode,int checkpwd);

//POS�ɷ�
int Pos_Fee(INNER_TRANS_REQUEST * pNode);

//���Ӷ�Ӧ��ϵ
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode);

//ɾ����Ӧ��ϵ
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode);

//����ʧ�ܽ��г��������������ˮ
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no);

//Ȧ���д��ʧ�ܳ���(ʵ�ʲ���������ֻ�Ǹ�д��״̬)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode);
int VerifyCardPwd(int cardno,char *cardpwd, char *szMsg);
//���ʹ���
//int Do_Compare(BANK_TRANS_REQUEST *pBankTrans );

//ũ�еĶ��ʹ��̣������ͽ��ױ�
int Do_Compare_file();

//�ֶ��Ķ��ʺ�����Ӧ��ʹ�õ�
int Do_Compare_file_shoudong();


//��������
//int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans);
int SetHeadCol(ST_CPACK *in_cpack, ...);
int device_login_yes_or_no(int device_id);
int device_login_yes_or_noEx(int device_id, char *szMsg);
int verify_card_password(int card_id,char *stuemp_no,int cut_id,char *password);
int verify_card_passwordEx(int card_id,char *stuemp_no,int cut_id,char *password, char *szMsg);
int verify_sch_bank_relationship(int cut_id,int card_id,char *stuemp_no,int area_id,char *bankcard_no);
int Is_out_of_service();
int do_update_device_state(INNER_TRANS_REQUEST * pNode);int Get_cut_name_and_id(int card_id,char *cut_name,char *id,char *stuempno);int do_updateconsumelimit(ST_PACK *in_pack);
/****************************************************
���ж˽��״�����
lq, 20050310���Ƶ�bank.hȥ������bu��ش�������
****************************************************/
#ifdef __cplusplus
	}
#endif

 ////////////////////////////////////////////////////////////////////////////

 #endif
