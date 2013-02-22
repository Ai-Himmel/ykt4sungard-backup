#ifndef _KS_DONGGUAN_PSAM_H_
#define _KS_DONGGUAN_PSAM_H_

#include "kscardtype.h"

class DGPSAM : public ks_psamcard_base
{
public:
	DGPSAM();
	virtual ~DGPSAM();
	virtual int InitDll(ks_cardlib_license *lic);
	virtual int PublishPSAMCard(ST_PSAMCARD* PSAMCard);
	virtual int RecyclePSAMCard();
	virtual int ReadPSAMCard(ST_PSAMCARD* PSAMCard);
	virtual int ResetPSAM();
	virtual int ReadPSAMTermno(char *sTermno);
	virtual int CalcSafeMac(const char *cmd,int len,char *sMac);
	virtual int CalcDepositMac(ST_TRANSPACK *transpack);
	virtual int CalcConsumeMac(ST_TRANSPACK *transpack);
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);
	virtual int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
	virtual int CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac);
	virtual int CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt);
	virtual int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	virtual int CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac);
};

#endif // _KS_DONGGUAN_PSAM_H_
