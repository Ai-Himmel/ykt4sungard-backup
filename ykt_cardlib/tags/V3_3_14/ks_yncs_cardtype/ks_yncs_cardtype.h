#if !define(_ks_yncs_cardtype_h_)
#define _ks_yncs_cardtype_h_

#include "kscardtype.h"
#include "ks_cardtype.h"


typedef enum {KR_READ=1,KR_WRITE=2,KR_INC=4,KR_DEC=8,KR_WRITEKEY=16} MF_KEY_RIGHT;

typedef struct _tagMFCardKey {
	uint8 key[6];
	KS_MF_KEYTYPE keytype;
}ks_mf_cardkey_t;

typedef struct {
	ks_mf_cardkey_t keys[2];
	uint8 ctrlbit[4];
	MF_KEY_RIGHT keya_right;
	MF_KEY_RIGHT keyb_right;
	KS_MF_KEYTYPE initkey;
}ks_mf_init_cardkey_t;

class ks_yncs_cardtype : public CCardType
{
private:
	static const int s_mf_max_sect = 16;
	int m_nReadCardType;
    int m_hd_water_sect;
    int m_xt_water_sect;
    //int m_isLoadKey;
    int m_lastLoginSect;
	int m_is_params_load;
	int m_max_sectno;
	int m_min_sectno;
    ks_card_info_t m_cardinfo;
    ks_card_info_t *m_mfcard;
	ks_cardtype_base * m_childct;
	ks_mf_cardkey_t m_cardkey[s_mf_max_sect];
	int load_mfcard_type();
	HMODULE mf_cardtype_handle;
    int encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
    int dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
    int encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
    int CalcCardKeyA(int sectno,unsigned char *key);
    int CalcCardKeyB(int sectno,unsigned char *key);
    void gen_hd_water_keya(int sectno,unsigned char *serialno,unsigned char *keya);
    int gen_user_card_keyA(unsigned char *key,unsigned char *text,unsigned char *keyA);
    int gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB);
	int loginCard(int sectno);
	int m_hd_param_sect;
    unsigned char m_mainkey[8];
    unsigned char m_hd_mainkey[8];
	unsigned char m_hd_paramkeya[6];
	unsigned char m_hd_paramkeyb[6];
	unsigned char m_xt_param_keya[6];
	int m_xt_water_max_money;
    char m_serial_no[21];
    unsigned char m_mf_serialno[8];
	int doInitUserCard(const char *sShowCardNo);
	int initCPUCard(const char *sShowCardNo);
	int doRestoreUsetCard();
	virtual int InitCardTypeDLL();
	int doRequestMFCard(char *szPhyno);
	static unsigned char DACK1[];
public:
	ks_yncs_cardtype();
	virtual ~ks_yncs_cardtype();
	///////////////////////////////////
public:
	//char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo=NULL);
	//void SetLastErrMsg(const char *errmsg);
	//char* GetLastErrMsg(char *errmsg=NULL);
	//void Attach(ks_device_op_t *device,ks_reader_dev_t *reader);
	//int AttachDecard(ks_device_op_t *device,ks_reader_dev_t *reader);
	/*
	int RequestCard(char* szCardPhyID=NULL);
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
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	void SetMifare1Key(const char *sCipherKey);
	int Mifare1ReadCard();
	int Mifare1GetFieldVal(int FieldID,char *fieldval);
	*/
	int InitUserCard(const char *sShowCardNo);
	int RestoreFactorySettings();
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
	*/

	
    /*
	int FormatCard();
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
	
    */
	virtual int checkCardType(int ct);
	int	 AuthDLL(const char *key,int flag);
	virtual int  ExtAuth(const char *cardphyid,int keyidx);

	int water_publishcard(int watertype,ks_water_pack_t *pack);
	int water_recyclecard(int watertype);
	int water_readmoney(int watertype,ks_water_pack_t *pack);
	int water_writemoney(int watertype,ks_water_pack_t *pack);
	int water_publishparamcard(int watertype,ks_water_param_t *param);
	int water_recycleparamcard(int watertype);
	int water_read_paramcard(int watertype,ks_water_param_t *param);

private:
	int xt_water_recycleparamcard();
	int xt_water_publishparamcard(ks_water_param_t *param);
	int do_xt_water_initcard(ks_water_param_t *param);
	int do_xt_water_paramcard(ks_water_param_t *param);
	int do_format_xt_paramcard(ks_water_param_t *param);
	int xt_water_publishcard(ks_water_pack_t *pack);
	int xt_water_writemoney(ks_water_pack_t *pack);
	int xt_water_readmoney(ks_water_pack_t *pack);
	int xt_water_recyclecard();
	int hd_water_publishparamcard(ks_water_param_t *param);
	int hd_water_recyclecard();
	int hd_water_publishcard(ks_water_pack_t *pack);
	int hd_water_writemoney(ks_water_pack_t *pack);
	int hd_water_login_fix(ks_water_pack_t *pack);
	int hd_water_readmoney(ks_water_pack_t *pack);
	int hd_water_recycleparamcard();

	int hd_water_readparamcard(int watertype,ks_water_param_t *param);
	int xt_water_readparamcard(int watertype,ks_water_param_t *param);
};



#endif // _ks_yncs_cardtype_h_

