#ifndef _ks_cqzy_cardtype_h_
#define _ks_cqzy_cardtype_h_

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

class ks_cqzy_cardtype : public CCardType
{
private:
	static const int s_mf_max_sect = 16;
	int m_nReadCardType;
    //int m_hd_water_sect;
    //int m_xt_water_sect;
	int m_secdPackSect;

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
	int LoginCardSect(int sectno);
	//int m_hd_param_sect;
    unsigned char m_mainkey[8];
 //   unsigned char m_hd_mainkey[8];
	//unsigned char m_hd_paramkeya[6];
	//unsigned char m_hd_paramkeyb[6];
	//unsigned char m_xt_param_keya[6];
	//int m_xt_water_max_money;
    char m_serial_no[21];
    unsigned char m_mf_serialno[8];
	int doInitUserCard(const char *sShowCardNo);
	int initCPUCard(const char *sShowCardNo);
	int doRestoreUsetCard();
	virtual int InitCardTypeDLL();
	int doRequestMFCard(char *szPhyno);
	static unsigned char DACK1[];
public:
	ks_cqzy_cardtype();
	virtual ~ks_cqzy_cardtype();
	///////////////////////////////////
public:

	int InitUserCard(const char *sShowCardNo);
	int RestoreFactorySettings();


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

	///  ¿­Â·Ë®¿Ø
	int szroad_water_publishcard(ks_water_pack_t *pack);
	int szroad_water_recyclecard();
	int szroad_water_readmoney(ks_water_pack_t *pack);
	int szroad_water_writemoney(ks_water_pack_t *pack);

};



#endif // _ks_cqzy_cardtype_h_

