#if !define(_ks_ctcardtype_h_)
#define _ks_ctcardtype_h_

#include "kscardtype.h"
#include "ks_cardtype.h"
#include <vector>

#pragma pack(1)	

typedef struct
{
	byte reserve1[16];
	byte reserve2[16];
	byte issuedate[4];
	byte validdate[4];
	byte startdate[4];
	byte ver;
	byte reserve3[2];
	byte crc8;
}INDEXINFO;

typedef struct
{
byte balance[4];
byte balance_crc[4];
byte balance2[4];
byte reserve1[4];
byte backup[16];
byte depositBal[4];
byte depositBal_crc[4];
byte totalDepMoney[4];
byte totalDepCnt[3];
byte crc8;
}PACKAGEINFO;

typedef struct 
{
byte card_no[3];
byte fee_type;
byte expired_date[3];
byte show_card_no[5];
byte reserve1[4];
byte pin[3];
byte limit_once[2];
byte limit_day[3];
byte reserve2[7];
byte crc8;
byte reserve3[16];
}PERINFO;

typedef struct
{
byte stuempNo[20];
byte cust_name[8];
byte duty_code[4];
byte dept_code[10];
byte id_code[4];
byte sex;
byte reserve1;
}PUBLICINFO;

typedef struct
{
byte id_no[20];
byte id_type;
byte bank_card_no[10];
byte reserve1;
byte custid[4];
byte custtype;
byte reserve2[11];
}PUBLICINFO2;

typedef struct 
{
byte recidx;
byte paycnt[2];
byte transflag;
//byte monthticket[2];
byte lockcnt[2];
byte cardstatus;
byte blkver[6];
byte dpscnt[2];
byte crc8;
byte reserve2[16];
byte reserve3[16];
}TRANSINFO;

typedef struct {
	int depositBal;
	int totalDepMoney;
	int totalDepCnt;
	byte crc8;
}DEPOSITINFO;

typedef struct {
byte transdate;
byte transtime[3];
byte cardbefbal[4];
byte amount[3];
byte transflag;
byte termno[4];
}TRANSDTL;

#pragma pack()

typedef struct {
	int has_read;
	KS_MF_KEYTYPE key_type;
	byte key[6];
	byte block_buffer[MF_MAX_BLOCK_SIZE];
	byte write_buffer[MF_MAX_BLOCK_SIZE];
	byte newKeyA[6];
	byte newKeyB[6];
	byte keyFlag;
}mf_sect_t;

typedef struct {
	byte orignCtrlBit[4];
	byte newCtrlBit[4];
	int writeKey;
	int readKey;
	int incKey;
	int decKey;
}mf_ctrlbit_t;

typedef struct {
	byte transdate[4];
	int cardbefbal;
	int amount;
	byte transtype;
	byte deviceid[4];
}trans_record_t;

#define CF_RECORDINDEX 92
#define CF_TRANSFLAG 93

// 初始化时控制位 KEYA，KEYB 可读可写，KEYB可更改密钥
#define MF1_INIT_CTRLBIT		"\x7F\x07\x88\x00"
// 初始化时控制位 KEYA只读，KEYB 可读可写，KEYB可更改密钥
#define MF1_KEYA_RO_CTRLBIT		"\x78\x77\x88\x00"
// 初始化时控制位 KEYA，KEYB 可读可写，KEYA可更改密钥
#define MF1_ORIGIN_CTRLBIT		"\xFF\x07\x80\x69"


//class ks_mfcard_type : public ks_cardtype_base
class ks_ctcardtype : public CCardType
{

private:
	ks_card_info_t m_cardinfo;
	ks_card_info_t *m_mfcard;
	int m_isLoadKey;
	int m_mainPackSect;
	int m_secdPackSect;
	KS_MF_KEYTYPE m_initKeyType;			//出厂初始化时，使用登录的密钥， 0 表示 keya , 1 表示 keyb
	byte m_initLoginKey[6];					//出厂密钥，{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
	unsigned char m_mainkey[8];
	char strUserCode_[13];
	int ctAppID_;
	char presentCardPhyNo_[17];
	mf_sect_t m_cardSect[MF_MAX_SECTNO];
	mf_ctrlbit_t m_ctrlBit[MF_MAX_SECTNO];
	int m_lastLoginSect;
	int m_lastLoginKeyType;
	int m_keyAlg;
	int m_cardVer;
	int m_lastRecIdx;

	static const int RECORD_SECTNO = 0x99;

	typedef enum { TRANS_BEGIN = 1, TRANS_END = 2 };
	typedef enum { TRANS_CONSUME = 0x01, TRANS_DEPOSIT = 0x88 , TRANS_LOCK = 0x99 };
	typedef enum { KEYRIGHT_READ = 1,KEYRIGHT_WRITE, KEYRIGHT_INC, KEYRIGHT_DEC };

	int m_packageSect; // 钱包扇区号
	int m_packageIdxSect; // 钱包参数扇区号
	int m_recordSectBegin; // 卡流水开始扇区号
	/////////////////////////////////////////////////////
	int CalcCardKeyB(int sectno,mf_sect_t *sect);
	int CalcCardKeyA(int sectno,mf_sect_t *sect);
	void CopySectKey(mf_sect_t *dest,const mf_sect_t *src,int t);
	int GetCurrentDateTime(char *datetime);
	void GetTransferDatetime(char *datetime);
	int LoginCardSect(int sectno,int kt = KEYRIGHT_WRITE);
	int MFTransaction(ST_TRANSPACK *transpack,int transtype);
	int MFTransCheck(TRANSINFO &info,int balance);
	int MFTransProcess(ST_TRANSPACK *transpack,int transtype,TRANSINFO &info);
	int m_maxSectNo;
	int m_minSectNo;
	char m_initSectMap[MF_MAX_SECTNO];
	char m_recycleSectMap[MF_MAX_SECTNO];
	unsigned char CalcCRC8(const unsigned char *data,int len);
	int CheckCRC8(const unsigned char *data,int len,unsigned char crc8);
	int CalcKeyFromSAM(int keytype,int keyidx,unsigned char *cipherData);
	int initAllCardDef();
	int testLoadKey();
	int calcDepositeKeyFromSvr(unsigned char *sCphier);
	int calcDepositeKeyLocal(unsigned char *sCphier);
	int checkPackageBuffer(const unsigned char *buffer);
	int GetBalance(int &balance);
	int GetTransRecord(int recordidx,trans_record_t &rec);
	int GetTransRecordBuffer(int recordidx,unsigned char *buffer);
	int UpdateTransRecord(int recordidx,trans_record_t &rec);
	int UnpackTransInfo(const unsigned char *buffer,TRANSINFO &info);
	int PackTransInfo(const TRANSINFO &info,unsigned char *buffer);
	void PackDepositInfo(const DEPOSITINFO &info,unsigned char *buffer);
	void UnpackDepositInfo(const unsigned char *buffer,DEPOSITINFO &info);
	void Money2String(int money,char *str);
	void String2Money(const char *str,int& money);
	int MFReadCard(int blockno,unsigned char *buffer);
	int MFWriteCard(int blockno,const unsigned char *buffer);
	int GetLastRecord();
	void ConvertTransDatetime(const char *sysDatetime,char *transDatetime);
	void GetLastTransDate(const char *day,char *date);
protected:
	virtual int checkCardType(int ct);
public:
	ks_ctcardtype();
	virtual ~ks_ctcardtype(){}
	///////////////////////////////////
public:
	virtual int OpenPort();
	void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	void SetMifare1Key(const char *sCipherKey);
	int RequestCard(char* szCardPhyID=NULL);
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	virtual int VerifyPin(const char* sPin=NULL);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual int SetKeyCard(ks_cardtype_base *c);
	int GetDpsCnt();
	int GetPayCnt();
	int GetRandomNum(byte *uRandomNum);
	virtual int testCardExists(char *szCardPhyID);
	int CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey);
	int EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);
	int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
	int CalcSafeMac4Sam(const char *szCmdbuf,char *szMac);
	int CalcSafeMac(const char* szCmdBuf,char *szMac);
	int FormatCard();
	int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes);
	int UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass);
	int SelectADF();

	int ReadCard();
	int WriteCard();
	int SetFieldVal(int FieldID,const char *fieldval);
	int GetFieldVal(int FieldID,char *fieldval);
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);

	int  AddMoney(ST_TRANSPACK *transpack);
	int  PayMoney(ST_TRANSPACK *transpack);
	int  ExtAuth(const char *cardphyid,int keyidx);
	int  Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	int  Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	int	 AuthDLL(const char *key,int flag);
	int InitForTrans(ST_TRANSPACK *trans,int trans_type);
	int GetMifare1WorkKey();
	virtual int InitCardTypeDLL();
	virtual int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac);

};


#endif // _ks_ctcardtype_h_
