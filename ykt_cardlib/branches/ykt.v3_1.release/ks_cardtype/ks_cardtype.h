#ifndef KS_CARDTYPE_H_
#define KS_CARDTYPE_H_
#include <vector>
#include <set>
#include <map>
#include <strstream>
#include "log.h"
using namespace std;

#include "ksdevice.h"
#include "kscard_imp.h"


#define MONEY_SFID 0x99


#pragma pack(1)
typedef struct  {
	byte transDate[4];
	byte transTime[3];
	byte transType;
	byte termNO[6];
	byte termSeqno[4];
	byte befBalance[4];
	byte transAmt[3];
	byte manageFee[3];
	byte payCardCnt[2];
	byte extraDepositFee[4];
	byte dailySumFee[3];
	byte shopId[2];
	byte reserve;
}PAYDTL_FILE;
#pragma pack()

#define FIELD_UNUSED 1
#define FIELD_USED 0

//#define KS_DACK "\x20\x10\x01\x01\x20\x10\x12\x31\xab\xcd\xef\xff\xfe\xdc\xba\x00"
class  CCardType : public ks_cardtype_base
{
protected:
	int m_CardBal;
	int m_PayCnt;
	int m_DpsCnt;
	int m_ReadFileLen;
	int m_WriteFileLen;
	int CalcDepositMac4Sam(ST_TRANSPACK *transpack,char *sMac);
private:
	PAYDTL_FILE m_lastPayDTL;
	int CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac);
	int DoAdpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen,KS_CARD_TYPE CardType);
	void fillPayDTL(ST_TRANSPACK * trans,PAYDTL_FILE * pay);
	void dealDailySumPay(PAYDTL_FILE * oldpay,PAYDTL_FILE * newpay);
	int dealPostPaidPreProcess(ST_TRANSPACK * trans,PAYDTL_FILE * pay);
	ks_reader_dev_t m_keycardPara;
	KS_CARD_TYPE m_keycardType;
	int doInitNewPsam();
	int doInitOldPsam();
	int doCheckPurchaseTAC(ST_TRANSPACK *transpack);
protected:
	virtual int checkCardType(int ct);
	static char szHexKSCCK[];
	virtual int doSuccessRequestCard();
	virtual int doRequestKeyCard(char *sCardPhyID);
public:
	unsigned char m_TempBuff[32];
	CCardType();
	char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	int IsLoadKeys();
	int IsLoadCloneKeys();
	int LoadKeys4Clone(const char sKeyCardPin[7]);
	int CloneKeyCard(const char sCloneCardPin[7]);
	int PublishKeyCard(unsigned char* sMasterKey,const char* sPin);
	int RecycleKeyCard();
	int CommInit(const char *svrip,int svrport,int svrfunc);
	int SaveKeys();
	//int PublishPSAMCard(ST_PSAMCARD* PSAMCard);
	//int RecyclePSAMCard();
	//int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	//virtual int ReadPSAMTermno(char *termno);
	virtual int SelectADF();
	virtual int VerifyPin(const char* sPin=NULL);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual int GetDpsCnt();
	virtual int GetPayCnt();
	virtual int GetBalance();
	virtual int testCardExists(char *szCardPhyID);
	int GetRandomNum(byte *uRandomNum);
	unsigned char* PbocDiverKey( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );
	int CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey);
	int EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);
	virtual int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
	virtual int CalcSafeMac4Sam(const char *szCmdbuf,char *szMac);
	virtual int CalcSafeMac(const char* szCmdBuf,char *szMac);
	int FormatCard();
	virtual int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	virtual int ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes);
	virtual int UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	virtual int ReadRecordFile(int SFI,unsigned char *ucData,int idx = 1,int len = 0);
	virtual int ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx = 1,int len = 0);
	int VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass);
	int ReadCard();
	int WriteCard();
	int SetFieldVal(int FieldID,const char *fieldval);
	int GetFieldVal(int FieldID,char *fieldval);
	virtual int CalcMacOnline(ST_TRANSPACK *transpack,char *sMac);
	virtual int AddMoney(ST_TRANSPACK *transpack);
	virtual int PayMoney(ST_TRANSPACK *payment);
	int CalcExtAuthEncrypt4Sam(const char *szCardNo,int keyidx,const char *szCmdbuf,char *szEncrypt);
	int ExecExtAuthCmd(const unsigned char ucExtAuthKey[16],int nKeyIndex=0);
	int ExtAuth(const char *cardphyid,int keyidx);
	int Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	int Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	// int  Adpu4HexSAM(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	//int PublishPSAMCard(ST_PSAMCARD* PSAMCard);
	int InitForTrans(ST_TRANSPACK *trans,int trans_type);
	virtual int DebitForTrans(ST_TRANSPACK *trans);
	virtual int GrayDebitUnlock(ST_TRANSPACK *transpack);
	virtual int GrayUnlock(ST_TRANSPACK *transpack);
	virtual int CAPPUpdate(ST_TRANSPACK *transpack);
	virtual int CAPPDebit(ST_TRANSPACK *transpack);
	virtual int PostPaidUpdate(ST_TRANSPACK *transpack);
	virtual int PostPaidDebit(ST_TRANSPACK *transpack);
	virtual int InitCardTypeDLL();
	virtual int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac=NULL,unsigned char *sTac=NULL);
};

#endif // KS_CARDTYPE_H_

