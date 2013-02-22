#ifndef _KSCOMDEF_H_
#define _KSCOMDEF_H_

// ˮ��Ǯ�������Ϣ
#pragma pack(1)
typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

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

// ����־
#define WATER_AUTH_CARD 1                  // ��Ȩ��
#define WATER_COMMON_CARD 2				   // ͨ�ÿ�
#define WATER_CLEAR_CARD 3				   // ���㿨
#define WATER_NEW_CARD 4                   //  	
#define WATER_FIXED_CARD 5                 // ���㿨

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
DCLR_KSFUNC(int,SMT_PacketAddMomey,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,SMT_PacketDelMomey,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,ReadBalance,(int nPacketNo,int nBalance[1],int nCnt[1]));
DCLR_KSFUNC(int,ReadCardNO,(int nCardNo[1]));
DCLR_KSFUNC(int,SMT_SetBlackCardFlag,());
DCLR_KSFUNC(int,ConnectMF,(int port, int baud));
DCLR_KSFUNC(int,CloseMF,());
DCLR_KSFUNC(int,ReadSerial,(unsigned char* serial));
DCLR_KSFUNC(int,SMT_SetNormalFlag,());
DCLR_KSFUNC(int,SMT_WritePersonalPassword,(unsigned char newpwd[3]));
DCLR_KSFUNC(int,SMT_ReadWaterPackInfo,(WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_WriteWaterPackInfo,(WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_InitWaterInfo,(const WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_WaterNewAuthCard,());
DCLR_KSFUNC(int,UpdateCardInfo,(TPublishCard *CardInfo));
DCLR_KSFUNC(int,ReadInfoFromCard,(TPublishCard *pc));

#endif