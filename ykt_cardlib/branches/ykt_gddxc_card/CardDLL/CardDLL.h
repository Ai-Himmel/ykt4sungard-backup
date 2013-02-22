//ʹ��Ԥ����ָ�֤ͷ�ļ�ֻ�ܱ�����һ��
#ifndef __CardDLL_H__
#define __CardDLL_H__

//��Ԥ����ָ��ʹC�����ܱ�C++����ֱ�ӵ���
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CARDDLL_EXPORTS
#define CARDDLL_EXPORTS
#endif

#include "carddll_def.h"

//ʮ�����ַ���ת��ΪBCD�ַ���
int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);

//BCD�ַ���ת��Ϊʮ�����ַ���
int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);

//���ö�ȡ����������
void __stdcall SetCardSectLength(const int card_sect_length);

//�򿪴���
int __stdcall ConnectMF(int,int);

//�رմ���
int __stdcall CloseMF(void);

//����������
int __stdcall ControlBuzzer();

//���߿�����
int __stdcall HaltCard(void);
//��д����Ȩ
int __stdcall ReaderAuthor(unsigned char *);

//�����������к�
int __stdcall RequestCard(char *,char *);

//���п�
int __stdcall PublishCard(TPublishCard *pc);

//������Ϣ
int __stdcall ReadCardInfo(TPublishCard *pc);

//���û���Ǯ����Ϣ
int __stdcall ReadPacketInfo(LOOPPURSEINFO *LoopPurseInfo);

//���¿���Ϣ
int __stdcall UpdateCardInfo(TPublishCard *CardInfo);

//�����׿���
int __stdcall ReadCardNO(int CardNo[1]);

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

//��̬��2008�汾��ֲ����
int __stdcall ReadCardLockFlag(int* lock_flag);
int __stdcall SetCardLockFlag(int lock_flag);


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
int __stdcall SMT_ChangeShowCardNo(unsigned char ucShowCardNo[5]);
int __stdcall SMT_ReadShowCardNo(unsigned char ucShowCardNo[5]);                                                  // (ʹ�õ�)
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
int __stdcall SMT_PacketSetMoney2(int nPacketNo, int nMoney, int nCnt);												//V3�汾��ֲ
int __stdcall SMT_PacketReset(int nPacketNo);
int __stdcall SMT_UpdateMoneyAndTxCnt(int packet_no, int money, int cnt, int batch_no);																		// (ʹ�ù�)	
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
int __stdcall SMT_ReadAreaCode(unsigned char area_code[3]);
int __stdcall SMT_WriteAreaCode(unsigned char area_code[3]);
int __stdcall SMT_ReadCutId(unsigned long *cut_id);
int __stdcall SMT_WriteAppendCardInfo(int cut_id, 
									  BYTE certificate_type[3],
									  BYTE people[3], 
									  BYTE nationality[4],	   
									  BYTE open_card_flag[2],
									  BYTE card_version[2]);
int __stdcall SMT_ReadAppendCardInfo(int *cut_id, 
									 BYTE certificate_type[3],
									 BYTE people[3],
									 BYTE nationality[4],	   
									 BYTE open_card_flag[2],
									 BYTE card_version[2]);
int __stdcall SMT_WritePwdOpenFlag(BYTE open_flag[2]);
int __stdcall SMT_ReadPwdOpenFlag(BYTE open_flag[2]);
int __stdcall SMT_WriteRegisterCardFlag(unsigned char card_flag[11]);
int __stdcall SMT_ReadRegisterCardFlag(unsigned char card_flag[11]);
int __stdcall SMT_WriteSerRegisterFlag(unsigned char ser_flag[11]);
int __stdcall SMT_ReadSerRegisterFlag(unsigned char ser_flag[11]);
int __stdcall SMT_WriteSubsidy(int money, int batch_no);
int __stdcall SMT_ReadSubsidy(int *batch_no);
int __stdcall SMT_UpdateSubsidy(int batch_no);
int __stdcall SMT_WriteCardTypeAndShopId(int card_type, 
										 int shop_id);
int __stdcall SMT_ReadCardTypeAndShopId(int *card_type, 
										int *shop_id);
int __stdcall SMT_GZWriteWaterPacket(
									 const double price1,
									 const double price2,
									 const double price3,
									 const double balance
									 );
int __stdcall SMT_GZReadWaterPacket(
									double *price1,
									double *price2,
									double *price3,
									double *balance
									);
void GetIniFile(char *FilePathBuf);
void GetIniFileFromDll(char *FilePathBuf);

//	��ʼ�����������е��ú���
#define E_COM_NOT_OPEN 10001
#define E_COM_NOT_CLOSE 10002

#define E_READ_CARD_ID_ERROR 10005
#define E_GEN_CARD_KEY_A_ERROR 10006
#define E_GEN_CARD_KEY_B_ERROR 10007

#define E_READ_CARD_ERROR 10010
#define E_CARD_LOGIN_ERROR 10011
#define E_MAIN_KEY_ERROR 10012
#define E_CARD_WRITE_ERROR 10020

#define E_INVALID_CARD 10030
#define E_CARD_FLAG_ERROR 10040	

/*
typedef struct _tagCardKeyData
{
	long flag;
	BYTE key[7];
} CardKeyData,* PCardKeyData;
*/
// 0����KEYA, 1����KEYB
#define CARD_KEY_A 0
#define CARD_KEY_B 1
#define CARD_KEY_C 1
typedef struct _tagCardKeyData
{
	long flag;
	BYTE key[2][7];
	BYTE ctrl_bit[5];
} CardKeyData,* PCardKeyData;

typedef int (*PWriteDataFunc)(long sect,CardKeyData * keya 
							  ,CardKeyData * keyb ,BYTE * card_type
							  ,CardKeyData * login_key);

typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf
							   ,BYTE *key,long flag);
// �ص�����
typedef void (CALLBACK * LPProcessCallBack)(int step);

int __stdcall InitNewCard(int * err_code, const char* showcardno, LPProcessCallBack lpCallBack);
int __stdcall ReadCardMainKey(BYTE * main_key, short wantFlag, short * readFlag);
int __stdcall ReadCardPhyID(BYTE card_id[4],BYTE card_type[2]);
int __stdcall RefineCard(int *err_code,LPProcessCallBack lpFunc);
int __stdcall ReadCardBlock(int startSect,int endSect,short block,LPGetBlockData lpFunc);
int __stdcall ResetMainKey();
int __stdcall SetCardMainKey(BYTE main_key[8]);
int __stdcall ResetAuthCard(int * err_code,LPProcessCallBack lpCallBack);
static int WriteCardData(long sect,long block,BYTE * buf);

//////////////////////////////////////////////////////////////////////////
// �Ϻ���ˮ��ҵ����
void GenerateKeyA(BYTE Srn[4], BYTE KeyA[6]);
int __stdcall SMT_ClearWaterCard();
int __stdcall RefineWaterCard(int *err_code, LPProcessCallBack lpFunc);
int __stdcall SMT_WriteWaterCardFlag(BYTE water_card_flag[4]);
int __stdcall InitNewCollectionCard(int *err_code, LPProcessCallBack lpCallBack);
int __stdcall ReadWaterCardBlock(int startSect, int endSect, short block, LPGetBlockData lpFunc);
int Login_Collect_Card(int sector);
int __stdcall WaterTransferSmallPacket(int BigPacketNo, int SmallPacketNo, int nMoney);
int __stdcall ReadCollectCardInfo(FEE_RATE_CARD_INFO *fee_rate_card_info);
int __stdcall SMT_ClearCollectCardData();
int __stdcall SMT_ReadWaterCardFlag(BYTE WaterCardFlag[4]);
int __stdcall SMT_InitNewCard4GDDXC(int * err_code,LPProcessCallBack lpCallBack);
int __stdcall SMT_FormatCard4GZDXC(int CleanWaterFlag);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �Ϻ���ѧҵ����
int __stdcall InitNewAuthCard(BYTE main_key[8], int flag, LPProcessCallBack lpCallBack);
int __stdcall ResetNewAuthCard(int * err_code, LPProcessCallBack lpCallBack);
int __stdcall PublishAuthCard(TPublishCard *pc);
int __stdcall SMT_LoginWorkKeySector(BYTE pri_key_a[6], BYTE pri_key_b[6], short *pri_sect, short *pri_block);
int __stdcall SMT_WriteAuthorNo(unsigned char ucAuthorId[10]);
int __stdcall SMT_WriteAuthPersonalPassword(unsigned char ucAuthPersonalPsd[3]);
int __stdcall SMT_ReadAuthCardStateInfo(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1]);
int __stdcall ReadAuthCardInfo(TPublishCard *pc);
int __stdcall ReadAuthCardBlock(int startSect, int endSect, short block, LPGetBlockData lpFunc);
int __stdcall SMT_SetAuthNormalFlagByBlkVerion(char *auth_black_version);
int __stdcall SMT_ReadAuthBlackNameListVersion(int *nflag, char *sVersion);
int __stdcall SMT_ReadAuthPersonalInfo(unsigned char ucName[8],
									   unsigned char ucDutyNo[4],
									   unsigned char ucCertificateNo[20],
									   unsigned char ucDepartmentNo[10],
									   unsigned char ucIdentifyNo[4],
									   unsigned char ucSexNo[1],
									   unsigned char ucCardNo[20]);
int __stdcall SMT_ReadAuthPersonalPassword(unsigned char PersonalPsd[6]);
int __stdcall SMT_ReadAuthorNo(unsigned char ucAuthorId[10]);
int __stdcall SMT_ClearAuthCard();
int __stdcall SMT_WriteAuthCardStateInfo(unsigned char ucShowCardNo[5], 
										 int nDealCardNo[1], 
										 unsigned char ucDeadLineDate[3], 
										 unsigned char ucCardRightType[1]);
int __stdcall SMT_WriteAuthPersonalInfo(unsigned char ucName[8],
										unsigned char ucDutyNo[4],
										unsigned char ucCertificateNo[20],
										unsigned char ucDepartmentNo[10],
										unsigned char ucIdentifyNo[4],
										unsigned char ucSexNo[1],
										unsigned char ucCardNo[20]);
int __stdcall WriteAuthCardPwd(unsigned char ucAuthoPwd[6]);
int __stdcall SMT_InitAuthBlackCardFlag();
int __stdcall SMT_ReadAuthorWorkKeyAndFlag(BYTE auth_work_key[8], BYTE *flag);
int __stdcall SMT_ModifyDeadLineDateAndFlag(BYTE DeadLineDate[8], BYTE flag);

void __stdcall GZ_SetWaterCardType(int t);


int __stdcall SMT_ReadWaterPackInfo2(WATER_PACK_INFO3* info);
int __stdcall SMT_WriteWaterPackInfo2(WATER_PACK_INFO3* info);
int __stdcall SMT_TransWaterPacket(int main_money,WATER_PACK_INFO3* info);
int __stdcall XT2JD_Card();
int __stdcall JD2XT_Card();
int __stdcall SMT_TransWaterPacket_XT(int main_money,WATER_PACK_INFO3* info);
int __stdcall SMT_ReadWaterPackInfo_XT(WATER_PACK_INFO3* info);
int __stdcall SMT_WriteWaterPackInfo_XT(WATER_PACK_INFO3* info);

void __stdcall YKT_get_version(char ver[512]);

#ifdef __cplusplus
}
#endif

#endif
