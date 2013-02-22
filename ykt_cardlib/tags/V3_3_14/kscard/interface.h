#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include "ksdevice.h"
#include "ksenc.h"
#include "kscardtype.h"

int load_interface_layer(const char *path);
int free_interface_layer();
/*
extern ks_device_op_t g_PSAMReader;
extern ks_device_op_t g_MainReader;
extern ks_device_op_t g_SecondReader;
extern ks_reader_dev_t g_ReaderPara;



extern int g_ReaderCount;

#define USE_CASE_TYPE_CLASS 1

#if USE_CASE_TYPE_CLASS==0
extern ks_cardtype_op_t g_CardType;
#else
extern ks_cardtype_base *g_CardType;
#endif

*/

extern ks_card_info_t g_cardinfo;

class ks_cardtype_dummy : public ks_cardtype_base
{
public:
	ks_cardtype_dummy():ks_cardtype_base(""){}
	virtual ~ks_cardtype_dummy(){};
public:
	virtual int  SetFieldReadMode (int fieldid)
	{
		return 0;
	}
	virtual int  SetFieldWriteMode (int fieldid)
	{
		return 0;
	}
	virtual int  SetFieldAllMode (int fieldid)
	{
		return 0;
	}
	virtual void  ClearFieldReadMode (int fieldid)
	{
		return;
	}
	virtual void  ClearFieldWriteMode (int fieldid)
	{
		return;
	}
	virtual void  ClearFieldAllMode (int fieldid)
	{
		return;
	}
	virtual void  ClearAllFieldReadMode ()
	{
		return;
	}
	virtual void  ClearAllFieldWriteMode ()
	{
		return;
	}
	virtual void  ClearAllFieldAllMode ()
	{
		return;
	}
	virtual int  SetFieldVal (int FieldID,const char *fieldval)
	{
		return 0;
	}
	virtual int  GetFieldVal (int FieldID,char *fieldval)
	{
		return 0;
	}
	virtual int  RequestCard (char *szCardPhyID)
	{
		return 0;
	}
	virtual int  SelectADF ()
	{
		return 0;
	}
	virtual int  VerifyPin (const char* sPin)
	{
		return 0;
	}
	virtual int  ReadCard ()
	{
		return 0;
	}
	virtual int  WriteCard ()
	{
		return 0;
	}
	virtual int  InitUserCard (const char *sShowCardNo)
	{
		return 0;
	}
	virtual int  LoadKeysFromKeyCard (const char *sKeyCardPwd)
	{
		return 0;
	}
	virtual int  IsLoadKeys ()
	{
		return 0;
	}
	virtual int  IsLoadCloneKeys ()
	{
		return 0;
	}
	virtual int  LoadKeys4Clone (const char sKeyCardPin[7])
	{
		return 0;
	}
	virtual int  CloneKeyCard (const char sCloneCardPin[7])
	{
		return 0;
	}
	virtual int  OpenPort (int port,int band)
	{
		return 0;
	}
	virtual int  PublishKeyCard (unsigned char* sMasterKey,const char* sPin)
	{
		return 0;
	}
	virtual int  RecycleKeyCard ()
	{
		return 0;
	}
	virtual int  PublishPSAMCard (ST_PSAMCARD* PSAMCard)
	{
		return 0;
	}
	virtual int  RecyclePSAMCard ()
	{
		return 0;
	}
	virtual int  RestoreFactorySettings ()
	{
		return 0;
	}
	virtual int  ReadPSAMTermno (char *termno)
	{
		return 0;
	}
	virtual int  SaveKeys ()
	{
		return 0;
	}
	virtual int  CommInit (const char *svrip,int svrport,int svrfunc)
	{
		return 0;
	}

};

class ks_psamcard_dummy : public ks_psamcard_base
{
public:
	ks_psamcard_dummy()
	{
	}
	virtual ~ks_psamcard_dummy()
	{
	}
	virtual int InitDll(ks_cardlib_license *lic)
	{
		return 0;
	}
	virtual int PublishPSAMCard(ST_PSAMCARD* PSAMCard)
	{
		return KS_NOTSUPPORT;
	}
	virtual int RecyclePSAMCard()
	{
		return KS_NOTSUPPORT;
	}
	virtual int ReadPSAMCard(ST_PSAMCARD* PSAMCard)
	{
		return KS_NOTSUPPORT;
	}
	virtual int ResetPSAM()
	{
		return KS_NOTSUPPORT;
	}
	virtual int ReadPSAMTermno(char *sTermno)
	{
		strcpy(sTermno,"FFFFFFFFFFFF");
		return 0;
	}
	virtual int CalcSafeMac(const char *cmd,int len,char *sMac)
	{
		return KS_NOTSUPPORT;
	}
	virtual int CalcDepositMac(ST_TRANSPACK *transpack)
	{
		return KS_NOTSUPPORT;
	}
	virtual int CalcConsumeMac(ST_TRANSPACK *transpack)
	{
		return KS_NOTSUPPORT;
	}
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo)
	{
		return "";
	}
	virtual int CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac)
	{
		return KS_NOTSUPPORT;
	}
	virtual int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
	{
		return KS_NOTSUPPORT;
	}
	virtual int CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt)
	{
		return KS_NOTSUPPORT;
	}
	virtual int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
	{
		return KS_NOTSUPPORT;
	}
	virtual int CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac)
	{
		return KS_NOTSUPPORT;
	}
	virtual int Adpu4HexSAM(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
	{
		return KS_NOTSUPPORT;
	}
	virtual int Adpu4SAM(const unsigned char *uCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
	{
		return KS_NOTSUPPORT;
	}
};
#endif // _INTERFACE_H_
