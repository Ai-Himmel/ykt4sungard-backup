#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H
//////////////////////////////////////////////////////////////////////////
// ���� cardman dll
// typedef void (CALLBACK * LPProcessCallBack)(int step);
// typedef void (* LPGetBlockData)(int sect,int block,BYTE buf[16]
// 							   ,BYTE key[6],long flag);
// 
// typedef int (CALLBACK *LPInitNewCard) (int * err_code,const char *showcardno
// 									   ,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPReadCardMainKey) (BYTE * main_key
// 										   ,short wantflag,short * readflag);
// typedef int (CALLBACK *LPRefineCard) (int * err_code,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPOpenCOM) (int port,long band);
// typedef int (CALLBACK *LPCloseCOM) ();

// typedef int (CALLBACK *LPNewAuthCard)(BYTE main_key[8],short pri_sect
// 								   ,short pri_block,short pri_startpos
// 								   ,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
// typedef int (CALLBACK *LPReadCardBlock)(int startSect,int endSect,
// 										short block,LPGetBlockData lpFunc);
// typedef int (CALLBACK *LPSetCardMainKey)(BYTE key[8]);

//���п��ṹ����
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
//////////////////////////////////////////////////////////////////////////
typedef void (CALLBACK * LPProcessCallBack)(int step);
typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf,BYTE *key,long flag);
typedef int (CALLBACK* LPReadCardMainKey)(BYTE * main_key, short wantFlag, short * readFlag); 
typedef int (CALLBACK* LPInitNewCard)(int * err_code, const char* showcardno, LPProcessCallBack lpCallBack);
typedef int (CALLBACK* LPConnectMF)(int,int);
typedef int (CALLBACK* LPCloseMF)();
typedef int (CALLBACK* LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
typedef int (CALLBACK* LPSMT_AutoDll)(unsigned char *ucWorkingKey);
typedef int (CALLBACK* LPReadCardBlock)(int startSect,int endSect,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPRefineCard)(int *err_code, LPProcessCallBack lpFunc);
typedef int (CALLBACK *LPResetNewAuthCard)(int * err_code,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPSMT_CheckForCard)(void);
typedef int (CALLBACK* LPReadAuthCardBlock)(int startSect,int endSect,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPInitNewAuthCard)(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack);
typedef int (CALLBACK* LPPublishAuthCard)(TPublishCard *pc);
typedef int (CALLBACK* LPReadAuthCardInfo)(TPublishCard *pc);
typedef int (CALLBACK* LPSMT_ReadAuthorWorkKeyAndFlag)(BYTE auth_work_key[8], BYTE *flag);
typedef int (CALLBACK* LPSMT_ReadAuthBlackNameListVersion)(int *nflag, char *sVersion);
typedef int (CALLBACK* LPSMT_ModifyDeadLineDateAndFlag)(BYTE DeadLineDate[8], BYTE flag);
//////////////////////////////////////////////////////////////////////////

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
extern LPReadCardMainKey ReadCardMainKey;
extern LPInitNewCard InitNewCard;
extern LPConnectMF ConnectMF;
extern LPCloseMF CloseMF;
extern LPReadCardPhyID ReadCardPhyID;
extern LPSMT_AutoDll SMT_AutoDll;
extern LPReadCardBlock ReadCardBlock;
extern LPRefineCard RefineCard;
// extern LPInitNewCard		InitNewCard;
// extern LPReadCardMainKey	ReadCardMainKey;
// extern LPRefineCard			RefineCard;
// extern LPOpenCOM			OpenCOM;
// extern LPCloseCOM			CloseCOM;
extern LPResetNewAuthCard	ResetNewAuthCard;
extern LPSMT_CheckForCard	SMT_CheckForCard;
extern LPReadAuthCardBlock  ReadAuthCardBlock;
extern LPInitNewAuthCard	InitNewAuthCard;
extern LPPublishAuthCard	PublishAuthCard;
extern LPReadAuthCardInfo	ReadAuthCardInfo;
// extern LPNewAuthCard		NewAuthCard;
// extern LPReadCardPhyID		ReadCardPhyID;
// extern LPReadCardBlock		ReadCardBlock;
// extern LPSetCardMainKey		SetCardMainKey;
extern LPSMT_ReadAuthorWorkKeyAndFlag SMT_ReadAuthorWorkKeyAndFlag;
extern LPSMT_ReadAuthBlackNameListVersion SMT_ReadAuthBlackNameListVersion;
extern LPSMT_ModifyDeadLineDateAndFlag SMT_ModifyDeadLineDateAndFlag;
#endif // _CARDMAN_UTIL_H