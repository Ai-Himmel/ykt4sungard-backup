/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_cd.h
 * �������ڣ�2010-10-26
 * �������ߣ�xlh
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ɵ罨�нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------*/


#ifndef	__BANK_CCB_CD_H__
#define	__BANK_CCB_CD_H__

#define REGISTRATION_CODE      	 "100001"     //ǩ��ǩ��
#define SIGNED_CODE   		        "100002"     //ǩԼ
#define BATCHSIGNE_CODE   		 "100003"     //����ǩԼ
#define SIGNED_RESULTS_CODE   	 "100004"    //ǩԼ���
#define TRANS_CODE   		        "100005"     //Ȧ�潻��
#define REV_TRANS_CODE   	        "100006"     //Ȧ�潻�׳���
#define DOWNLOAD_TRANS_CODE    "100007"    //���׼�¼����

#pragma pack(1)
typedef struct{
       char  packlen[5];				// ���ĳ���
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
	PACKHEAD head;                              //��ͷ
	char SignInOut[1];				// ǩ��ǩ�˱�־1,0
}SignInOut_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	char Func[1];						//���ܺ�
	char SchoolCard[32];				//У԰һ��ͨ����
	char  SchoolName[40];                    //һ��ͨ����
	char SchoolNo[18];				//һ��ͨ���֤��
	char BankCard[32];				// ���п�����
}ToRegister_REQ;


typedef struct{
	PACKHEAD head;                              //��ͷ
	char SchoolCard[32];				// һ��ͨ����
	char SchoolName[10];				//һ��ͨ����
	char SchoolNo[18];				//һ��ͨ���֤��
	char RopAmt[20];					// Ȧ����
	char BankCard[32];				// ���п�����
}TRANS_REQ;


typedef struct{
	PACKHEAD head;                              //��ͷ
	char Counts[16];				// ����
}BatchRegister_REQ;


typedef struct{
	PACKHEAD head;                              //��ͷ
	char RegisterDate[8];				// ����ǩԼ����
	char OldTransBankId[16];                //ԭѧУҵ����ˮ��
}BatchRegisterResult_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	char Counts[16];              			  //����
}BatchRegisterResult_ANS;

typedef struct{
	PACKHEAD head;                              //��ͷ
	char OldTxdate[8];				// ԭ��������
	char OldTransBankId[16];			//ԭѧУҵ����ˮ��
	char OldRopAmt[20];				//ԭȦ����
}REVTRANS_REQ;

typedef struct{
	PACKHEAD head;                              //��ͷ
	char CompareDate[8];				// ��������
}ListDown_REQ;
typedef struct{
	PACKHEAD head;                              //��ͷ
	char CompareDate[8];				// ��������
	char AnsNumSuc[8];                        //�ɹ�
	char AnsNumFal[8];                        //ʧ��
	char RopeCntAmt[20];                     //�ܽ��
}ListDown_ans;

#pragma pack()
#endif

