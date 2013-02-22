#ifndef _KSCOMDEF_H_
#define _KSCOMDEF_H_

#pragma pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char CardNo[8];				//�û������׿���
	unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
	int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
	unsigned char ucName[9];				//����
	unsigned char ucDutyNo[9];				//ְ�����
	unsigned char ucCertificateNo[21];		//֤������
	unsigned char ucDepartmentNo[11];		//���ű��
	unsigned char ucIdentifyNo[5];			//��ݴ���
	unsigned char ucSexNo[2];				//�Ա����
	unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
	unsigned char ucPwd[6];					//������
	unsigned char ucLibraryNo[21];			//ͼ��֤��
	int Money;								//���֣�
	unsigned char isFormat;					//�Ƿ��ʽ����һ����
}TPublishCard;
#pragma pack()

#define DCLR_KSFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_KSFUNC(name) \
	LP##name name = NULL;	\

#define LOAD_KSFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
	return -1;

DCLR_KSFUNC(int,Load_Dll,());
DCLR_KSFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_KSFUNC(int,PacketAddMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,PacketDecMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,ReadBalance,(int nPacketNo,int nBalance[1],int nCnt[1]));
DCLR_KSFUNC(int,ReadCardNo,(int nCardNo[1]));
DCLR_KSFUNC(int,SetBlackCardFlag,());
DCLR_KSFUNC(int,ComInit,(char *_ComType,int _Syn));
DCLR_KSFUNC(int,COMClose,());
DCLR_KSFUNC(int,ReadSerial,(unsigned char* serial));
DCLR_KSFUNC(int,SetNormalFlag,());
DCLR_KSFUNC(int,ChangePassWord,(unsigned char * newpwd));
DCLR_KSFUNC(int,UpdateCardInfo,(TPublishCard *CardInfo));
DCLR_KSFUNC(int,ReadInfoFromCard,(TPublishCard *pc));

#endif