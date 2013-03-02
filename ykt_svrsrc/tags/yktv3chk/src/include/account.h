#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#define MAXNUM_ACC 	10

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	int  iTradeNo;				//������
	int  iTermID;				//�ն˱��
	int  iSerialNo;				//��̨������ˮ��
	int  iSubIndex;				//����ˮ����ʼֵ iSubIndex = 0 ����ʼ��ˮ��Ϊ 1
	int  iMainDevId;				//�ն��豸ID
	int  iTxFlag;				//���ױ�־0-��������,1-��������, 2-��ֵ����
	int  iCardNo;				//����
	int  iDevId;
	int  iTxCnt;				//��ǰ�ۼƿ��н��״���
	int  iFeeType;				//�շ�����
	int  iOnlineFlag;			//������־
	int  iUseCardFlag;			//�п�����/�޿����ױ�־��1Ϊ�п�,����Ϊ�޿�
	int  iCalAftBalflag;		//�Ƿ�������ֵ��־
	int  iBefBalFlag;			//�Ƿ��н���ǰ�����
	double  dInCardBala;				//����ǰ�����
	double  dOutCardBala;				//���׺����
	int  iShopID;				//�̻���
	char sTxDate[9];			//�������ڣ���ʽΪyyyymmdd
	char sTxTime[7];			//����ʱ�䣬��ʽΪhhmmss
	char sTxCollectDate[9];		//�ɼ����ڣ���ʽΪyyyymmdd
	char sTxCollectTime[7];		//�ɼ�ʱ�䣬��ʽΪhhmmss
	char sTxAccDate[9];			//�������ڣ���ʽΪyyyymmdd
	char sTxAccTime[7];			//����ʱ�䣬��ʽΪhhmmss
	char sOperCode[9];			//����Ա��
	char sChkOper[9];			//���˲���Ա��

	int  iOutTxTypeCnt;			//����շ���Ŀ����
	char sArrInActno[MAXNUM_ACC][17];			//�˺�,16λ
	int  iArrInFeeSwitch[MAXNUM_ACC];		//�������λΪԪ
	double  dArrInAmt[MAXNUM_ACC];				//���뷢�����λΪԪ
	int  iArrOutTxType[MAXNUM_ACC];			//��������
	double dArrOutAmt[MAXNUM_ACC];			//����������λΪԪ
	char sArrOutTxName[MAXNUM_ACC][61];		//����������Ӧ�Ľ�������
	void *pVoidPointer;			//������ָ��,��Ϊ�������ݿ�
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
