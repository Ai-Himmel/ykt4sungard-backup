#ifndef _KS_CMCC_CARDTYPE_H_
#define _KS_CMCC_CARDTYPE_H_

#include <vector>
#include <set>
#include <map>
#include "kscardtype.h"
#include "..\\ks_cardtype\\ks_cardtype.h"

#define CF_APPID 90 // 子应用索引号
//#define CF_APPTYPE 91 // 子应用类型
#define CF_APPLOCKFLAG 92 // 子应用锁定标志
#define CF_ENTERPRICECODE 93 // 企业ID号

class ks_cmcc_cardtype:public CCardType
{
private:
	//char strAppSerialNo_[17];
	unsigned char appSerialNo_[8];
	unsigned char enterpriceCode_[30];
	char strEnterpriceCode_[13];
	char mfCardLibName_[256];
	int enterpriceAppID_;
	int loadKeyVer_;
	int purchaseKeyVer_;
	//int lastCardType_;
	HMODULE mf_cardtype_handle;
	ks_cardtype_base * m_childct;
	int createSubApp();
	int CalcSafeMacWithKey(const unsigned char *key,const char* uCmd,int nCmdLen,char *szMac);
	int hasCreateSubApp(bool &create);
	int delSubApp();
	int CalcDepositMac4Sam(ST_TRANSPACK *transpack,char *sMac);
	int CompareMac1(unsigned char *key,ST_TRANSPACK *transpack,char *sMac1);
	int readCardInfo();
	int CalcMacData(unsigned char *key,unsigned char *seed3rd,char *data,char *mac);
	int CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac);
	int initDef();
	int load_mfcard_type();
	int DoRequestCard(char* szCardPhyID,KS_CARD_TYPE &t);
protected:
	virtual int checkCardType(int ct);
	virtual int doRequestCard(char *szCardPhyID,KS_CARD_TYPE &t);
	virtual int doSuccessRequestCard();
public:
	ks_cmcc_cardtype();
	~ks_cmcc_cardtype();
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	void Attach(ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t);

	virtual int SelectADF();
	int UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKey[16]);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual int WriteCard();
	virtual int InitCardTypeDLL();
	virtual int CalcSafeMac4Sam(const char *szCmdbuf,char *szMac);
	int AddMoney(ST_TRANSPACK *deposit);
	int PayMoney(ST_TRANSPACK *payment);
	virtual int GetDpsCnt();
	virtual int GetPayCnt();
	virtual int GetBalance();
	virtual int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);
	virtual int InitForTrans(ST_TRANSPACK *trans,int trans_type);
	virtual int UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int CalcMacOnline(ST_TRANSPACK *transpack,char *sMac);
	int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac);
	
	/////////////////////////////////////////////////////////////
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	void SetMifare1Key(const char *sCipherKey);

	int water_publishcard(int watertype,ks_water_pack_t *pack);
	int water_recyclecard(int watertype);
	int water_readmoney(int watertype,ks_water_pack_t *pack);
	int water_writemoney(int watertype,ks_water_pack_t *pack);
	int water_publishparamcard(int watertype,ks_water_param_t *param);
	int water_recycleparamcard(int watertype);
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
	
	int SetFieldVal(int FieldID,const char *fieldval);
	int GetFieldVal(int FieldID,char *fieldval);
};

#endif // _KS_CMCC_CARDTYPE_H_
