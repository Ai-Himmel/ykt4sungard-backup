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

#include "bank.h"

#ifndef	__transinfo_h__
#define	__transinfo_h__
//////////////////////////// constant defined ///////////////////////////////
#ifndef	NULL
#define	NULL	0
#endif

#ifdef __cplusplus
extern "C" {
#endif


 /////////////////////////// �ڲ����״���  ///////////////////////////////
#define TRADE_INNER_QUERYBANK		240007	//��ѯ���п�
#define TRADE_INNER_TRANS			240001	//����ת��
#define TRADE_INNER_AUTOTRANS		240002	//����ת��
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

#define TRADE_INNER_QUERYWATER	240201	//ˮ��ת����ϸ��ѯ
#define TRADE_INNER_BUYWATER		240202	//ˮ��ת��
#define TRADE_INNER_BIND_METER	240203	//��ˮ��
#define TRADE_INNER_UNBIND_METER	240204   //ȡ��ˮ���
#define TRADE_INNER_WATER_WFAIL	240111	//ˮ��ת��д��ʧ��

#define TRADE_INNER_POWER_TRANS	240206	//���ת��
#define TRADE_INNER_POWER_QUERY	240207	//���ת�˲�ѯ
#define TRADE_INNER_POWER_WFAIL	240209	//���ת��ʧ��
#define TRADE_INNER_POWER_QUERY_DORM 240208 //���ת��������Ϣ��ѯ


 /////////////////////////////////////////////////////////////////////////////

 #define	PIN_TYPE_GDC					0x01	//����У԰������
 #define	PIN_TYPE_BC					0x02	//�������п�����
 #define	PIN_TYPE_BOTH					0x04	//����У԰��+���п�����

 #define	TRANSFER_MODE_SINGLE_GDC	0x01	//single card (  )
 #define	TRANSFER_MODE_SINGLE_BC		0x02	//single card ( BC )
 #define	TRANSFER_MODE_DUAL			0x04	//dual card

/////////////////////////////////////////////////////////////////////////////

//������������״̬
#define	TRADECORE_STATE_STOP				0
#define	TRADECORE_STATE_INITRUN			1
#define	TRADECORE_STATE_PRERUN			2
#define	TRADECORE_STATE_RUNNING			3
#define	TRADECORE_STATE_PRESTOP			4

//���������
#define	TRADECORE_TASK_NONE				0	//û������
#define	TRADECORE_TASK_TRANS				1	//����ת��	require bank
#define	TRADECORE_TASK_AGENTFEE			2	//���շ�	require bank
#define	TRADECORE_TASK_QUERYBANKBALANCE 3	//��ѯ���п����	require bank
#define	TRADECORE_TASK_QUERYCARDBALANCE  4	//��ѯУ԰�����
#define	TRADECORE_TASK_CHGCARDPWD		5	//�޸�У԰������
#define	TRADECORE_TASK_BUILDRELATION	6	//������Ӧ��ϵ		may require bank
#define	TRADECORE_TASK_CANCELRELATION	7	//ȡ����Ӧ��ϵ		may require bank
#define	TRADECORE_TASK_DETRANS			8	//����ת�ʳ���		require bank
#define	TRADECORE_TASK_AUTOTRANS		9	//�Զ�ת��require bank
#define	TRADECORE_TASK_CARDLOST			10	//��ʧ
#define	TRADECORE_TASK_CARDUNLOST		11	//���
#define	TRADECORE_TASK_BANKLOST			12	//���п���ʧ

//��������ִ�в���
#define	TRADECORE_STEP_QUERYCARD		1		//��ѯУ԰��
#define	TRADECORE_STEP_BANKTRANS		2		//����ת��
#define	TRADECORE_STEP_BANKDETRANS		3		//���г���
#define	TRADECORE_STEP_CARDACC			4		//����
#define	TRADECORE_STEP_NOTIFYPOS		5		//֪ͨPOS
#define	TRADECORE_STEP_CHGPWD			6		//У԰��������
#define	TRADECORE_STEP_QUERYBANKBALANCE	7		//��ѯ���п����
#define	TRADECORE_STEP_BANKAGENTFEE		8		//���շ�
#define	TRADECORE_STEP_CARDLOST			9		//У԰����ʧ
#define	TRADECORE_STEP_CARDUNLOST		10		//У԰�����
#define	TRADECORE_STEP_BANKLOST			11		//���п���ʧ
//�������༰���״���
#define	TRADE_CODE_POSLOGIN		801	//pos��½
#define	TRADE_CODE_NOSYNCNOTIFY	803	//��ͬ��֪ͨ
#define	TRADE_CODE_POSTRANS		201	//����ת��
#define	TRADE_CODE_POSCHARGE	203	//���շ�
#define	TRADE_CODE_QUERYBANK	351	//��ѯ���п����
#define	TRADE_CODE_QUERYCARD	353	//��ѯУ԰�����
#define	TRADE_CODE_CARDLOST		357	//У԰����ʧ
#define	TRADE_CODE_CHANGEPASS	355	//У԰����������
#define	TRADE_CODE_CARDUNLOST	359	//У԰�������ʧ
#define	TRADE_CODE_CREATECORR	321	//POS���ɶ�Ӧ��ϵ
#define	TRADE_CODE_DELCORR		323	//posɾ����Ӧ��ϵ
#define	TRADE_CODE_AUTOTRANS	205	//�Զ�ת��


//////////////////////////״̬����////////////////////////////////////////
// ������е�½״̬������Ҫ���״̬�ĵط����øúꡣ����б�Ҫ�������ź�������
#define BANK_LOGIN	(shm[1]==1)

// �������ͨ��״̬������Ҫ���״̬�ĵط����øúꡣ����б�Ҫ�������ź�������
#define BANK_CONNECT	(shm[3]==1)

// !!! ��ȡ����������ʱ��һ��Ҫ��ȡ�ź��� p(semid); operations...; v(semid)


 /////////////////////////���������ݿ�/////////////////////////////////////

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

//POSת��
int Pos_Transfer(INNER_TRANS_REQUEST * pNode);

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

/****************************************************
���ж˽��״�����
lq, 20050310���Ƶ�bank.hȥ������bu��ش�������
****************************************************/
#ifdef __cplusplus
	}
#endif

 ////////////////////////////////////////////////////////////////////////////

 #endif
