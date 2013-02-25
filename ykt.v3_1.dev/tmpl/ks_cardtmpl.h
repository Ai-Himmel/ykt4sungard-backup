#ifndef _KS_CARDTMPL_H_
#define _KS_CARDTMPL_H_

#include "kscardtype.h"
class ks_cardtmpl : public ks_cardtype_base
{
public:
	ks_cardtmpl();
	virtual ~ks_cardtmpl();
///////////////////////////////////////////////////////////////////////////////
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	virtual char* GetErrMsgByErrCode( int nErrCode,char *sErrInfo);
	virtual int  SetFieldVal(int FieldID,const char *fieldval);
	virtual int  GetFieldVal(int FieldID,char *fieldval);
	virtual int testCardExists(char *szCardPhyID);
	virtual int  SelectADF ();
	virtual int  VerifyPin (const char* sPin);
	virtual int  ReadCard ();
	virtual int  WriteCard ();
	virtual int  InitUserCard (const char *sShowCardNo);
	virtual int  LoadKeysFromKeyCard (const char *sKeyCardPwd);
	virtual int  IsLoadKeys ();
	virtual int  IsLoadCloneKeys ();
	virtual int  LoadKeys4Clone (const char sKeyCardPin[7]);
	virtual int  CloneKeyCard (const char sCloneCardPin[7]);
	virtual int  PublishKeyCard (unsigned char* sMasterKey,const char* sPin);
	virtual int  RecycleKeyCard ();
	virtual int  RestoreFactorySettings ();
	virtual int  SaveKeys ();
	virtual int  VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass);
	virtual int  CommInit (const char *svrip,int svrport,int svrfunc);
	virtual int  AddMoney(ST_TRANSPACK *transpack);
	virtual int  PayMoney(ST_TRANSPACK *transpack);
	virtual int  ExtAuth(const char *cardphyid,int keyidx);
	virtual int  Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,
		unsigned char *ucRespData,unsigned char &ucRespLen);
	virtual int  Adpu4Hex(const char *szCmd,unsigned char ucSendLen,
		unsigned char *ucRespData,unsigned char &ucRespLen);
	virtual int ReadRecordFile(int SFI,unsigned char *ucData,int idx = 1,int len = 0);
	virtual int ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx = 1,int len = 0);
	virtual int InitForTrans(ST_TRANSPACK *trans,int trans_type);

///////////////////////////////////////////////////////////////////////////////
	virtual int water_publishcard(int watertype,ks_water_pack_t *pack);
	virtual int water_recyclecard(int watertype);
	virtual int water_readmoney(int watertype,ks_water_pack_t *pack);
	virtual int water_writemoney(int watertype,ks_water_pack_t *pack);
	virtual int water_publishparamcard(int watertype,ks_water_param_t *param);
	virtual int water_recycleparamcard(int watertype);
	virtual int water_read_paramcard(int watertype,ks_water_param_t *param);
	virtual int water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	virtual int water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);

};

#endif // _KS_CARDTMPL_H_
