/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_cd.h
 * �������ڣ�2010-10-26
 * �������ߣ�xlh
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ɵ罨�нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------*/

#define _CI_DEGUG_DES_
#ifndef	__BANK_BCC_CD_H__
#define	__BANK_BCC_CD_H__
#define REQ_PACK_LEN 157
#define ANS_PACK_LEN 56

#define REV_REQ_PACK_LEN 107
#define REV_ANS_PACK_LEN 40

#define REGISTRATION_CODE      	 "100001"     //ǩ��ǩ��
#define SIGNED_CODE   		        "100002"     //ǩԼ
#define BATCHSIGNE_CODE   		 "100003"     //����ǩԼ
#define SIGNED_RESULTS_CODE   	 "100004"    //ǩԼ���
#define TRANS_CODE   		        "100005"     //Ȧ�潻��
#define REV_TRANS_CODE   	        "100006"     //Ȧ�潻�׳���
#define DOWNLOAD_TRANS_CODE    "100007"    //���׼�¼����

#pragma pack(1)
typedef struct{
	char Txcode[6];				// ������
	char TxDate[8];				// ��������
	char TxTime[8];				// ����ʱ��
	char Operator[12];			//����Ա
	char Checker[12];		      		 //  ����Ա
	char TxChannel[4];			// ���𷽱�ʾ(ѧУ����)
	char TxOrgNo[9];				// ���֤��
	char  BankSerial[16];			// ������ˮ��
	char Serial[16];				// ��������ˮ
	char FileNames[50];                 //�ļ�����
	char RespCode[5];                    //��Ӧ��
	char RespMess[64];                  //��Ӧ��Ϣ
}PACKHEAD;

typedef struct{
	char SignInOut[1];				// ǩ��ǩ�˱�־1,0
}SignInOut_body_REQ;
typedef struct{
	PACKHEAD head;                              //��ͷ
	SignInOut_body_REQ body;				
}SignInOut_REQ;

typedef struct{	                         
	char Func[1];						//���ܺ�
	char SchoolCard[32];				//У԰һ��ͨ����
	char  SchoolName[40];                    //һ��ͨ����
	char SchoolNo[18];				//һ��ͨ���֤��
	char BankCard[32];				// ���п�����
}ToRegister_body_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	ToRegister_body_REQ body;			// ���п�����
}ToRegister_REQ;


typedef struct{
	char SchoolCard[32];				// һ��ͨ����
	char SchoolName[10];				//һ��ͨ����
	char SchoolNo[18];				//һ��ͨ���֤��
	char RopAmt[20];					// Ȧ����
	char BankCard[32];				// ���п�����
}TRANS_body_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	TRANS_body_REQ body;
}TRANS_REQ;

typedef struct{
	char Counts[16];				// ����
}BatchRegister_body_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	BatchRegister_body_REQ body;
}BatchRegister_REQ;

typedef struct{
	char RegisterDate[8];				// ����ǩԼ����
	char OldTransBankId[16];                //ԭѧУҵ����ˮ��
}BatchRegisterResult_body_REQ;
typedef struct{
	PACKHEAD head;                              //��ͷ
	BatchRegisterResult_body_REQ body;
}BatchRegisterResult_REQ;

typedef struct{
	char Counts[16];              			  //����
}BatchRegisterResult_body_ANS;

typedef struct{
	PACKHEAD head;                              //��ͷ
	BatchRegisterResult_body_ANS body;   			 
}BatchRegisterResult_ANS;

typedef struct{
	char OldTxdate[8];				// ԭ��������
	char OldTransBankId[16];			//ԭѧУҵ����ˮ��
	char OldRopAmt[20];				//ԭȦ����
}REVTRANS_body_REQ;
typedef struct{
	PACKHEAD head;                              //��ͷ
	REVTRANS_body_REQ body;
}REVTRANS_REQ;

typedef struct{
	char CompareDate[8];				// ��������
}ListDown_body_REQ;
typedef struct{
	PACKHEAD head;                              //��ͷ
	ListDown_body_REQ body;
}ListDown_REQ;

typedef struct{
	char CompareDate[8];				// ��������
	char AnsNumSuc[8];                        //�ɹ�
	char AnsNumFal[8];                        //ʧ��
	char RopeCntAmt[20];                     //�ܽ��
}ListDown_body_ans;
typedef struct{
	PACKHEAD head;                              //��ͷ
	ListDown_body_ans body;
}ListDown_ans;

#pragma pack()

#endif

