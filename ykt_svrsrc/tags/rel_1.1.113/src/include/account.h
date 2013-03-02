#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#define MAXNUM_ACC 	30

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int  iTradeNo;				//������
	int  iSerialNo;				//��̨������ˮ��
	int  iDevId;					//�ն��豸ID
	int  iMainDevId;				//�ն˻���ID
	int  iTxFlag;					//���ױ�־0-��������,1-��������, 2-��ֵ����
	int  iCardNo;					//����
	int  iTxCnt;					//��ǰ�ۼƿ��н��״���
	int  iFeeType;				//�շ�����
	int  iUseCardFlag;			//�п�����/�޿����ױ�־��1Ϊ�п�,����Ϊ�޿�
	double  dInCardBala;			//�뿨ֵ,����뿨ֵΪ-1����˵��Ϊ�գ��Է�Ϊ��λ
	double  dOutCardBala;	    	   	//����ֵ,�������ֵΪ-1����˵��Ϊ�գ��Է�Ϊ��λ
	char sTxDate[11];				//�������ڣ���ʽΪyyyymmdd
	char sTxTime[9];				//����ʱ�䣬��ʽΪhhmmss
	char sTxCollectDate[11];		//�ɼ����ڣ���ʽΪyyyymmdd
	char sTxCollectTime[9];		//�ɼ�ʱ�䣬��ʽΪhhmmss
	char sTxAccDate[11];			//�������ڣ���ʽΪyyyymmdd
	char sTxAccTime[9];			//����ʱ�䣬��ʽΪhhmmss
	char sMdeOper[9];			//¼�����Ա,8λ
	char sChkOper[9];			//���˲���Ա,8λ
	char sTalOper[9];				//���˲���Ա,8λ
	char sArrInActno[MAXNUM_ACC][17];	//�˺�,16λ
	int 	iArrInFeeSwitch[MAXNUM_ACC / 2];		//�������λΪԪ
	double dArrInAmt[MAXNUM_ACC / 2];		//���뷢�����λΪԪ
	int 	iOutTxTypeCnt;						//����շ���Ŀ����
	int  iArrOutTxType[MAXNUM_ACC / 2];		//��������
	double dArrOutAmt[MAXNUM_ACC / 2];		//����������λΪԪ
	char    sArrOutTxName[MAXNUM_ACC / 2][61];	//����������Ӧ�Ľ�������
	void *pVoidPointer;			//������ָ��,��Ϊ�������ݿ�
	int iSubIndex;				//����ˮ����ʼֵ iSubIndex = 0 ����ʼ��ˮ��Ϊ 1
}InAcc;

int AccountProcess (InAcc * inacc);

// ��������
#define ACC_TYPE_NORMAL       0
// ��������
#define ACC_TYPE_RUSH	     1
// ͸֧����
#define ACC_TYPE_OVERDRAFT  2

#ifdef __cplusplus
}
#endif

#endif
