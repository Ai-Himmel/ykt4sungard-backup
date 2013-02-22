//ʹ��Ԥ����ָ�֤ͷ�ļ�ֻ�ܱ�����һ��
#ifndef __CardDLL_H__
#define __CardDLL_H__

//��Ԥ����ָ��ʹC�����ܱ�C++����ֱ�ӵ���
#ifdef __cplusplus
extern "C" {
#endif


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

typedef struct
{
		DWORD RemainMoney;			// ����Ǯ�����
		WORD DealTimes;				// �û���������ˮ��
		BYTE DealYear;				// ��������
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// �ۼƽ��״���(��ǰʱ�����)
		BYTE DealTimes_CurDay;		// �ۼƽ��״���(������)
} LOOPPURSEINFO ,*LPLOOPPURSEINFO;

typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5

// ������COMM.H�����ݽṹ
// #define	STX1	0xC0
// #define	ETX1	0xC1
// #define	STX2	0xC2
// #define	ETX2	0xC3
// //----------------------------
// int ErrorCode;
// BYTE Dll_RetData[500];
// int Dll_CommByte;
// int Dll_bps = 19200;
// BYTE Dll_MacNo;
// COMMTIMEOUTS CommTimeOuts;
// unsigned char subkey[17][49];

// ������COMM.H�����ݽṹ

#pragma pack()

static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

//ʮ�����ַ���ת��ΪBCD�ַ���
int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);

//BCD�ַ���ת��Ϊʮ�����ַ���
int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);

//�򿪴���
int __stdcall ConnectMF(int,int);

//�رմ���
int __stdcall CloseMF(void);

//��д����Ȩ
int __stdcall ReaderAuthor(unsigned char *);

//�����������к�
int __stdcall RequestCard(char *,char *);

//���п�
int __stdcall PublishCard(TPublishCard *pc);

//������Ϣ
int __stdcall RedCardInfo(TPublishCard *pc);

//���û���Ǯ����Ϣ
int __stdcall ReadPacketInfo(LOOPPURSEINFO *LoopPurseInfo);

//���¿���Ϣ
int __stdcall UpdateCardInfo(TPublishCard *CardInfo);

//�����׿���
int __stdcall ReadCardNO(char *pCardNo);

int __stdcall WriteCardPwd(unsigned char pwd[6]);
int __stdcall ReadCardPwd(unsigned char pwd[6]);
int __stdcall Load_Dll();
int __stdcall GetLastErrMsg(int ecode[1],char *errmsg);

// ����Ǯ����� 
int __stdcall ReadBalance(int nPacketNo,int nBalance[1],int nCnt[1]);

// ��ȡ�����к�
int __stdcall ReadSerial(unsigned char *serial);

// �����´�½�������Ķ�������
int __stdcall Load_WorkKey(char *ascWorkKey);

//////////////////////////////////////////////////////////////////////////
// ����ӵĲ���, ������SMARTCOM411DXQ
// int SMT_Philips_Packet_Proc(int flag,int Sector,int BlockNo,int Money,unsigned char *BlockBuf);        // (�˺���δ��ʹ�õ�, ����SMARTCOM411DXQ�ӿ�ʵ����)
// int SMT_Copy_DataBlock(int Sector,int souBlock,int desBlock,unsigned char *BlockBuf);			      // (�˺���δ��ʹ�õ�, ����SMARTCOM411DXQ�ӿ�ʵ����)
extern int nAutoFlag;
int __stdcall SMT_JudgeAutoFlag();
int __stdcall SMT_AutoDll(unsigned char *ucWorkingKey);                                                                                
int __stdcall SMT_CreateGreyCard(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8]);           // (�˺���δ��ʹ�õ�)
int __stdcall SMT_WriteCardStateInfo(unsigned char ucShowCardNo[5], int nDealCardNo[1], 
									 unsigned char ucDeadLineDate[3], unsigned char ucCardRightType[1]);            // (ʹ�õ�)
int __stdcall SMT_ReadCardStateInfo(unsigned char ucShowCardNo[5],
								    int nDealCardNo[1],
								    unsigned char ucDeadLineDate[3],
								    unsigned char ucCardRightType[1]);												// (ʹ�õ�)                                                                    
int __stdcall SMT_ChangeShowCardNo(unsigned char ucShowCardNo[5]);                                                  // (ʹ�õ�)
int __stdcall SMT_ChangeDeadLineDate(unsigned char ucDeadLineDate[3]);                                              // (ʹ�õ�)
int __stdcall SMT_ChangeDealCardNo(int nDealCardNo);
int __stdcall SMT_ChangeCardRightType (unsigned char ucCardRightType[1]);                                           // (ʹ�õ�)
int __stdcall SMT_WritePersonalInfo(unsigned char ucName[8],
									unsigned char ucDutyNo[4],
									unsigned char ucCertificateNo[20],
									unsigned char ucDepartmentNo[10],
									unsigned char ucIdentifyNo[4],
									unsigned char ucSexNo[1],
									unsigned char ucCardNo[20]);                                                    // (ʹ�õ�)
int __stdcall SMT_ReadPersonalInfo(unsigned char ucName[8],
								   unsigned char ucDutyNo[4],
								   unsigned char ucCertificateNo[20],
								   unsigned char ucDepartmentNo[10],
								   unsigned char ucIdentifyNo[4],
								   unsigned char ucSexNo[1],
								   unsigned char ucCardNo[20]);                                                     // (ʹ�õ�)
int __stdcall SMT_ChangeName(unsigned char ucName[8]);                                                              // (ʹ�õ�)
int __stdcall SMT_ChangeDutyNo(unsigned char ucDutyNo[4]);                                                          // (ʹ�õ�)
int __stdcall SMT_ChangeCerificateNo (unsigned char ucCertificateNo[20]);                                           // (ʹ�õ�)                
int __stdcall SMT_ChangeDepartmentNo(unsigned char ucDepartmentNo[10]);                                             // (ʹ�õ�)
int __stdcall SMT_ChangeIdentifyNo (unsigned char ucIdentifyNo[4]);                                                 // (ʹ�ù�)
int __stdcall SMT_ChangeSexNo (unsigned char ucSexNo[1]);                                                           // (ʹ�ù�)
int __stdcall SMT_ChangeCardNo(unsigned char ucCardNo[20]);                                                         // (ʹ�ù�)
int __stdcall SMT_WritePersonalPassword(unsigned char PersonalPsd[3]);                                              // (ʹ�ù�)
int __stdcall SMT_ReadPersonalPassword(unsigned char PersonalPsd[3]);                                               // (ʹ�ù�)
int __stdcall SMT_WriteLibraryNo(unsigned char ucLibraryNo[13]);                                                    // (ʹ�ù�)
int __stdcall SMT_ReadLibraryNo(unsigned char ucLibraryNo[13]);                                                     // (ʹ�ù�)
int __stdcall SMT_WriteBankCardNo(unsigned char ucBankCardNo[10]);                                                  // (ʹ�ù�)
int __stdcall SMT_ReadBankCardNo(unsigned char  ucBankCardNo[10]);                                                  // (ʹ�ù�)
int __stdcall SMT_ReadPacketInfo(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo);                                      // (ʹ�ù�)
int __stdcall SMT_PacketAddMomey(int nPacketNo,int nMoney);															// (ʹ�ù�)			
int __stdcall SMT_PacketDelMomey(int nPacketNo,int nMoney);															// (ʹ�ù�)	
int __stdcall SMT_PacketSetMoney(int nPacketNo,int nMoney);															// (ʹ�ù�)
int __stdcall SMT_PacketReset(int nPacketNo);																		// (ʹ�ù�)	
int __stdcall SMT_WriteAssistInfo (int nBatchNo[1],int nMoney[1]);												    // (δ��ʹ�ù�)
int __stdcall SMT_ReadAssisInfo(int nBatchNo[1],int nMoney[1],
								unsigned char ucBatchTime[5], unsigned char ucMacNo[4]);							// (δ��ʹ�ù�)							
int __stdcall SMT_SetBlackCardFlag();																                // (ʹ�ù�)
int __stdcall SMT_SetNormalFlag();																				    // (ʹ�ù�) 	
int __stdcall SMT_SetNormalFlagByBlkVerion(char *blkversion);														// (ʹ�ù�)			
int __stdcall SMT_ClearCard();																					    // (ʹ�ù�)
int __stdcall SMT_ReadAuthCardFlag(short * flag);																	// (ʹ�ù�)	 						
int __stdcall SMT_ReadAuthCard2(unsigned char ucWorkKey[8],short * flag);											// (ʹ�ù�)
int __stdcall SMT_ReadAuthCard(unsigned char ucWorkKey[8]);														    // (ʹ�ù�)		
int __stdcall SMT_ResetCard();																					    // (ʹ�ù�)			 	
int __stdcall SMT_ResetPacketInfo(int nPacketNo);																	// (ʹ�ù�)	
int __stdcall SMT_GetPacketInfo(int nPacketNo, MONEY_PACK_INFO *pPackInfo);										    // (ʹ�ù�)
int __stdcall SMT_SetPacketInfo(int nPacketNo,MONEY_PACK_INFO *pPackInfo);										    // (ʹ�ù�)		
int __stdcall SMT_SetTxCnt(int nPacketNo,int tx_cnt);																// (ʹ�ù�)			
int __stdcall SMT_ReadBlackNameListVersion(int *flag,char *version);                                                // (ʹ�ù�) 
int __stdcall SMT_ReadWaterPackInfo(WATER_PACK_INFO* info);
int __stdcall SMT_WriteWaterPackInfo(WATER_PACK_INFO* info);
int __stdcall SMT_WaterSetCapability(int value);
int __stdcall SMT_InitWaterInfo(const WATER_PACK_INFO* info);
int __stdcall SMT_WaterNewAuthCard();
void GetIniFile(char *FilePathBuf);

#ifdef __cplusplus
}
#endif

#endif
