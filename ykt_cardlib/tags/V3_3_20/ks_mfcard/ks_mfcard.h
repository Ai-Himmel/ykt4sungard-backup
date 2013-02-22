#if !define(_ks_mfcard_h_)
#define _ks_mfcard_h_

#include "kscardtype.h"
#include "ks_cardtype.h"
#include <vector>

#pragma pack(1)	

typedef struct 
{
byte card_no[3];
byte fee_type;
byte expired_date[3];
byte show_card_no[5];
byte card_status;
byte reserve1[3];
byte pin[3];
byte limit_once[2];
byte limit_day[3];
byte reserve2[7];
byte crc;
byte bank_card_no[10];
byte reserve3[6];
}PERINFO;

typedef struct
{
byte cust_name[8];
byte duty_code[4];
byte id_card[20];
byte dept_code[10];
byte id_code[4];
byte sex;
byte reserve1;
}PUBLICINFO;

typedef struct 
{
byte reserve1[16];
byte stuemp_no[20];
byte reserve2[12];
}IDINFO;

typedef struct
{
byte balance[3];
byte total_count[2];
byte tx_date[3];
byte tx_time[2];
byte total_per_day[3];
byte subsidy_no[2];
byte crc;
byte reserve1[16];
byte reserve2[16];
}PACKAGEINFO;

typedef struct
{
byte package1_flag;
byte package1_sectno;
byte package2_flag;
byte package2_sectno;
byte package3_flag;
byte package3_sectno;
byte package4_flag;
byte package4_sectno;
byte reserve1[8];
byte reserve2[16];
byte black_flag;
byte black_ver[6];
byte reserve3[9];
}PACKAGEIDXINFO;
#pragma pack()

typedef struct {
	int has_read;
	KS_MF_KEYTYPE key_type;
	byte key[6];
	byte block_buffer[MF_MAX_BLOCK_SIZE];
	byte write_buffer[MF_MAX_BLOCK_SIZE];
}mf_sect_t;

#define CF_BLACKFLAG  91

// 初始化时控制位 KEYA，KEYB 可读可写，KEYB可更改密钥
#define MF1_INIT_CTRLBIT		"\x7F\x07\x88\x00"
// 初始化时控制位 KEYA只读，KEYB 可读可写，KEYB可更改密钥
#define MF1_KEYA_RO_CTRLBIT		"\x78\x77\x88\x00"
// 初始化时控制位 KEYA，KEYB 可读可写，KEYA可更改密钥
#define MF1_ORIGIN_CTRLBIT		"\xFF\x07\x80\x69"

//class ks_mfcard_type : public ks_cardtype_base
class ks_mfcard_type : public CCardType
{

private:
	enum { 
		KA_1ST = 0, // 第一个版本
		KA_PSAM = 1, // PSAM 卡
		KA_CMCC = 2, // 移动规范时使用的方法
		KA_SHU = 3 , // 上海大学版本
	};
	ks_card_info_t m_cardinfo;
	ks_card_info_t *m_mfcard;
	int m_isLoadKey;
	int m_mainPackSect;
	int m_secdPackSect;						// 小钱包扇区号
	int m_offlinewater;						// 脱机水控扇区号
	KS_MF_KEYTYPE m_initKeyType;			//出厂初始化时，使用登录的密钥， 0 表示 keya , 1 表示 keyb
	byte m_initLoginKey[6];					//出厂密钥，{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
	int m_lldfSect;							//深圳领路达方水控扇区号，0xFF 表示不支持
	unsigned char m_lldfKey[6];				//深圳领路达方水控扇密钥
	unsigned char m_mainkey[8];
	byte m_offlinewaterkey[8];				
	byte m_OriginPhyNo[4];
	byte m_presentPhyNo[4];
	mf_sect_t m_cardSect[MF_MAX_SECTNO];
	char strEnterpriceCode_[20];
	int enterpriceAppID_;
	int m_lastLoginSect;
	int m_keyAlg;
	int m_cardVer;
	int m_keyType;
	int CalcMFSectKey(int sectno,mf_sect_t *sect);
	int CalcCardKeyA(int sectno,mf_sect_t *sect);
	int GetCurrentDateTime(char *datetime);
	int LoginCardSect(int sectno);
	int MFTransaction(ST_TRANSPACK *transpack,int transtype);
	int m_maxSectNo;
	int m_minSectNo;
	char m_initSectMap[MF_MAX_SECTNO];
	char m_recycleSectMap[MF_MAX_SECTNO];
	
	static FILE * ks_mfcard_type::g_dump_file;
	void DumpCardBlockData(int sect,int block,BYTE *buf);
	void Caloffwaterkey(byte *serialno,int sectno,byte *mkey,byte *keya);
	int CalcKeyFromSAMKeyA(unsigned char *cipherData);
	int CalcKeyFromSAMKeyB(unsigned char *cipherData);
	int CalcKeyFromSAMKeyACMCC(unsigned char *cipherData);
	int CalcKeyFromSAMKeyBCMCC(unsigned char *cipherData);
	int initAllCardDef();
	void GenHdWaterParamKeyA(byte keyA[6]);
	void GenLegacyWaterKeyA(byte keyA[6]);
	void GenLegacyWaterCtlBlock(byte ctldata[16]);
	int LoginLegacyWaterCardSect(int sectno,bool bPublish=true);
	int LoginHDWaterParamCardSect(int sectno,bool bPublish=true);
	int testLoadKey();
	int calcCMCCMainKey(unsigned char *key);
	int encryptKeyA(unsigned char *key,unsigned char *sCipher);
	int encryptKeyB(unsigned char *key,unsigned char *sCipher);
	int iPsamPowerOnCnt;
	int do_hd_water_publishcard(ks_water_pack_t *pack);
	int hd_water_login_fix(ks_water_pack_t *pack);
protected:
	virtual int checkCardType(int ct);
	virtual int doSuccessRequestCard();
	virtual int doSubRequestCard(char *szCardPhyID);
public:
	ks_mfcard_type();
	virtual ~ks_mfcard_type(){}
	///////////////////////////////////
public:
	//char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo=NULL);
	//void SetLastErrMsg(const char *errmsg);
	//char* GetLastErrMsg(char *errmsg=NULL);
	//void Attach(ks_device_op_t *device,ks_reader_dev_t *reader);
	//int AttachDecard(ks_device_op_t *device,ks_reader_dev_t *reader);
	void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	void SetMifare1Key(const char *sCipherKey);
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	virtual int  PublishKeyCard (unsigned char* sMasterKey,const char* sPin);
	virtual int VerifyPin(const char* sPin=NULL);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual int SetKeyCard(ks_cardtype_base *c);
	int GetDpsCnt();
	int GetPayCnt();
	int GetBalance();
	int GetRandomNum(byte *uRandomNum);
	virtual int testCardExists(char *szCardPhyID);
	unsigned char* PbocDiverKey( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );
	int CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey);
	int EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);
	int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
	int CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac);
	int CalcSafeMac(const char* szCmdBuf,char *szMac);
	int FormatCard();
	int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes);
	int UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass);
	/*
	int SetFieldReadMode(int fieldid);
	int SetFieldWriteMode(int fieldid);
	//设置该字段读写模式
	int SetFieldAllMode(int fieldID);
	//清除该字段读模式
	void ClearFieldReadMode(int fieldID);
	//清除该字段写模式
	void ClearFieldWriteMode(int fieldID);
	//清除该字段所有模式
	void ClearFieldAllMode(int fieldID);
	//清除所有字段的读模式
	void ClearAllFieldReadMode();
	//清除所有字段的写模式
	void ClearAllFieldWriteMode();
	//清除所有字段的读写模式
	void ClearAllFieldAllMode();
	*/
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
	int water_publishcard(int watertype,ks_water_pack_t *pack);
	int water_recyclecard(int watertype);
	int water_readmoney(int watertype,ks_water_pack_t *pack);
	int water_writemoney(int watertype,ks_water_pack_t *pack);
	int water_publishparamcard(int watertype,ks_water_param_t *param);
	int water_recycleparamcard(int watertype);
	int water_read_paramcard(int watertype,ks_water_param_t *param);
	int water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	int water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	/// 联机通用水控
	int legacy_water_publishcard(ks_water_pack_t *pack);
	int legacy_water_recyclecard();
	int legacy_water_readmoney(ks_water_pack_t *pack);
	int legacy_water_writemoney(ks_water_pack_t *pack);
	// 汇多脱机水控
	int hd_water_publishcard(ks_water_pack_t *pack);
	int hd_water_recyclecard();
	int hd_water_readmoney(ks_water_pack_t *pack);
	int hd_water_writemoney(ks_water_pack_t *pack);
	///  深圳领路达方水控
	int lldf_water_publishcard(ks_water_pack_t *pack);
	int lldf_water_recyclecard();
	int lldf_water_readmoney(ks_water_pack_t *pack);
	int lldf_water_writemoney(ks_water_pack_t *pack);
	//////////////////////////////////////////////////////////////
	void DumpSectData(int watertype);
	virtual int InitCardTypeDLL();
	virtual int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac);
	virtual int SelectADF();

};


#endif // _ks_mfcard_h_
