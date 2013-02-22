#if !defined(_ks_cpumf_cardtype_)
#define _ks_cpumf_cardtype_

#include "kscardtype.h"
#include "ks_cardtype.h"

class ks_cpumf_cardtype : public CCardType
{
private:
	int m_nReadCardType;
	ks_cardtype_base * m_childct;
	int load_mfcard_type();
	HMODULE mf_cardtype_handle;
protected:
	virtual int checkCardType(int ct);
public:
	ks_cpumf_cardtype();
	virtual ~ks_cpumf_cardtype();
	///////////////////////////////////
public:
	//char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo=NULL);
	//void SetLastErrMsg(const char *errmsg);
	//char* GetLastErrMsg(char *errmsg=NULL);
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	void Attach(ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t);
	
	/*
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	int IsLoadKeys();
	int IsLoadCloneKeys();
	int LoadKeys4Clone(const char sKeyCardPin[7]);
	int CloneKeyCard(const char sCloneCardPin[7]);
	int PublishKeyCard(unsigned char* sMasterKey,const char* sPin);
	int RecycleKeyCard();
	int CommInit(const char *svrip,int svrport,int svrfunc);
	int SaveKeys();
	int PublishPSAMCard(ST_PSAMCARD* PSAMCard);
	int RecyclePSAMCard();
	int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ReadPSAMTermno(char *termno);
	virtual int SelectADF();
	virtual int VerifyPin(const char* sPin=NULL);
	*/
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual void SetMifare1Key(const char *sCipherKey);
	int Mifare1ReadCard();
	int Mifare1GetFieldVal(int FieldID,char *fieldval);
	int InitCardTypeDLL();
	/*
	int GetDpsCnt();
	int GetPayCnt();
	int GetBalance();
	int GetRandomNum(byte *uRandomNum);
	unsigned char* PbocDiverKey( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );
	int CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey);
	int EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);
	int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
	int CalcSafeMac4Sam(const char sCardPhyID[17],const char *szCmdbuf,char *szMac);
	int CalcSafeMac(const char* szCmdBuf,char *szMac);
	*/
	/*
	int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes);
	int UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int FormatCard();
	*/

	int water_publishcard(int watertype,ks_water_pack_t *pack);
	int water_recyclecard(int watertype);
	int water_readmoney(int watertype,ks_water_pack_t *pack);
	int water_writemoney(int watertype,ks_water_pack_t *pack);
	int water_publishparamcard(int watertype,ks_water_param_t *param);
	int water_recycleparamcard(int watertype);
	int water_read_paramcard(int watertype,ks_water_param_t *param);
	int water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	int water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	void DumpSectData(int watertype);
	int SetFieldReadMode(int fieldid);
	//清除所有字段的读模式
	void ClearAllFieldReadMode();
	//清除该字段读模式
	void ClearFieldReadMode(int fieldID);
	int SetFieldWriteMode(int fieldid);
	//设置该字段读写模式
	int SetFieldAllMode(int fieldID);
	//清除该字段写模式
	void ClearFieldWriteMode(int fieldID);
	//清除该字段所有模式
	void ClearFieldAllMode(int fieldID);
	//清除所有字段的写模式
	void ClearAllFieldWriteMode();
	//清除所有字段的读写模式
	void ClearAllFieldAllMode();
	int ReadCard();
	int ReadCard(int ReadType);
	int WriteCard();
	
	int SetFieldVal(int FieldID,const char *fieldval);
	int GetFieldVal(int FieldID,char *fieldval);
	//int GetMifare1WorkKeyFromSvr();
	/*
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);
	int  AddMoney(ST_TRANSPACK *transpack);
	int  PayMoney(ST_TRANSPACK *transpack);
	int  ExtAuth(const char *cardphyid,int keyidx);
	int  Adpu(unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	int  Adpu4Hex(char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	int	 AuthDLL(const char *key,int flag);
	int InitForTrans(ST_TRANSPACK *trans,int trans_type);
	*/
};

#endif // _ks_cpumf_cardtype_
