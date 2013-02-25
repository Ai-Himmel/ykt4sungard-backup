#ifndef _KSCARDTYPE_H_
#define _KSCARDTYPE_H_
#include <wtypes.h>
#include <string>
#include <strstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "ksdevice.h"
#include "kscard_imp.h"
#include "kslicense.h"
#include "logfile.h"
typedef struct
{
	// ���ṹ���Զ���
	size_t offset;
	size_t length;
	int type;
	int unused;
	int rw;
	// CPU ���ṹʹ��
	int adfid;
	// CPU �б�ʾ �ļ����� , mifare ���б�ʾ������ 
	int fid; 
	//int sectno;
	// mifare card ���ṹʹ�� 
	int blockno; // 0 0 0 0 1 1 1 1
}EF_FIELD;

typedef enum {FT_INT8=1,FT_INT16,FT_INT24,FT_INT32,FT_INT48,FT_BCD,FT_BCD_LPAD20,FT_BCD_LAPDZERO,FT_ANSI,FT_UCS2,
// ��λ��ǰ������
	FT_LT_INT16,FT_LT_INT24,FT_LT_INT32,FT_HEX_DATE,FT_HEX_TIME,FT_HEX_STR, FT_COMPACT_DATE, FT_STUEMPNO, FT_SUBSIDYBAL, FT_TOTALAMT} FIELD_TYPE;

typedef enum {FRR_NULL=0,FRR_FREE,FRR_MAC,FRR_EXTAUTH_MAC,FRR_ENCRYPT,FRR_ENCRYPT_MAC,
	FRR_REC_FREE,FRR_REC_MAC,FRR_EXTAUTH} FILE_RIGHT_READ;
typedef enum {FRW_NULL=0,FRW_MAC,FRW_EXTAUTH_MAC,FRW_MAC_DIRECT,FRW_ENCRYPT,FRW_ENCRYPT_MAC} FILE_RIGHT_WRITE;
typedef enum {RCT_CPU,RCT_MF1,RCT_ALL}READCARD_TYPE;

//�ļ���Ȩ��
//FRR_NULL  ����ʹ��read��ʽ��
//FRR_FREE  ���ɶ�
//FRR_MAC   ����ʹ��MAC��
//FRR_EXTAUTH_MAC ������ʹ���ⲿ��֤����ʹ��MAC��
//�ļ�дȨ��
//FRW_NULL  ����ʹ��write��ʽд
//FRW_FREE  ����д
//FRW_MAC   ����ʹ��MACд
//FRW_EXTAUTH_MAC ������ʹ���ⲿ��֤����ʹ��MAC��
//FRW_MAC_DIRECT  д��ʱ����Ҫ��ȡԭ����
typedef enum {RW_RW,RW_R,RW_W} RW_RIGHT;

typedef struct 
{
	std::set<int>	FieldSet;
	std::set<int>	ReadFieldSet;
	std::set<int>    WriteFieldSet;
	int			FileSize;
	int			ReadRight;
	int			WriteRight;
	byte		ReadBuf[128];
	byte		WriteBuf[128];
}EFBUF;


#ifdef USE_CASE_TYPE_CLASS
#undef USE_CASE_TYPE_CLASS
#endif
#define USE_CASE_TYPE_CLASS 1

#define SET_ERR(message) do \
{ std::ostringstream oss;oss<<message;SetLastErrMsg(oss.str().c_str(),__FILE__,__LINE__);}while(0)

/////////////////////////////////////////////////////////////////////////////
// Ϊÿ���͵Ŀ���ţ����Ϊ unsigned int ���ͣ���һ�ֽڱ�ʾ���࣬�����ֽڱ�ʾ��ͬ�汾
// ��һ�ֽ�˵����
// 0x01 - CPU ��
// 0x02 - M1 ��
// 0x03 - PSAM ��
// 0x04 - ��Կ��
// 0x05 - RFSIM/RFUIM ��
// ���п�����˵����
// =================================================
// 0x0100 - ��׼��CPU��
// 0x0101 - ��׼��CPU�� 7+1 ��
// 0x0102 - �ƽ�ְCPU��
// 0x0103 - ��ݸ��ݸ��CPU��
// =================================================
// 0x0200 - ��׼��M1��
// 0x0201 - ���ݴ�ѧ�ǰ�M1��
// =================================================
// 0x0300 - ��׼��PSAM��
// 0x0301 - �ƶ���׼PSAM��
// 0x0302 - ��ݸ��ݸ��PSAM��
// =================================================
// 0x0400 - ��׼����Կ��
// 0x0409 - ͨ��ˮ�ز�����
// =================================================
// 0x0501 - ���ݴ�ѧ���ƶ��ֻ���
// 0x0502 - �������´�ѧ�����ֻ���
// 0x0503 - �й��ƶ����ű�׼�ֻ���
// 0x0504 - �Ϻ����ż��Ź淶�ֻ���(���ͨ)

/////////////////////////////////////////////////////////////////////////////
typedef struct
{
	byte MK[17];	//������Կ
	byte DPK1[17];	//����1
	byte DPK2[17];	//����2
	byte DLK1[17];  //Ȧ��1
	byte DLK2[17];  //Ȧ��2
	byte DTAC[17];	//�ڲ���ԿTAC
	byte DACK[17];	//�ⲿ��֤
	byte DUK[17];   //PIN����
	byte DRPK[17];	//PIN��װ
	byte DAMK[17];	//ά����Կ
	byte DACK1[17];	//�ⲿ��֤1
	byte DACK2[17];	//�ⲿ��֤2
	byte DACK3[17];	//�ⲿ��֤3
	byte LDACK[17];	//СǮ���ⲿ��֤��Կ
	byte LDAMK[17];	//СǮ��ά����Կ
	int  bLoad;
}CARDKEYS;

class ks_psamcard_base;

class KSLogTrace
{
private:
public:
	KSLogTrace();
	virtual ~KSLogTrace();
	void PushErrMsg(const char *msg);
	void PopErrMsg(std::string &msg);
};

class ks_cardtype_base
{
public:
	char m_szCardUID[17];
	char m_appSerialNo[33];
	char m_szRandomNum[17];
	char m_currentADF[128];
	char m_ADFData[256];
	KS_CARD_TYPE m_defaultCardType;
private:
	int m_cardTypeNo;
protected:
	ks_device_op_t *m_Reader;
	ks_reader_dev_t *m_ReaderPara;
	ks_device_op_t *m_KeyReader;
	ks_reader_dev_t *m_KeyReaderPara;
	std::string m_sDefaultPin;
	ks_psamcard_base *m_PSAMCardType;
	CARDKEYS  m_CardKeys;
	CARDKEYS  m_CloneKeys;
	int m_CardTypeCode;
	

	char  m_szAppPath[256];
	std::vector<EF_FIELD>  m_FieldVect;
	std::map<int,EFBUF>	m_EFMap;
	ks_cardlib_license *m_license;
	virtual int checkCardType(int ct);
	virtual int doRequestCard(char *szCardPhyID,KS_CARD_TYPE &t);
	virtual int doSuccessRequestCard();
	virtual void resetAll();
	virtual int selectADFBySFI(const char *SFI,int force = 0);
	virtual int selectADFByName(const char *ADFName,int force = 0);
public:
	ks_cardtype_base(const char *p);
	virtual ~ks_cardtype_base();
	inline void set_cardtype_name(const char *p) { strcpy(cardtype_name,p); }
	inline void set_license(ks_cardlib_license *lcs) { m_license = lcs; }
	unsigned char cardtype_buff[32];
	char version[32];
	char cardtype_name[32];
	char m_ErrMsg[512];
	/*
	0 ����
	1 Ȧ��
	2 ����
	3 ��������
	4 ��������
	5 �󸶷�
	*/
	typedef enum { TRNS_TYPE_PURCHASE = 1, TRNS_TYPE_LOAD = 0,TRNS_TYPE_GRAYLOCK = 2,
		TRNS_TYPE_GRAYUNLOCK = 3 ,TRNS_TYPE_CAPP_PURCHASE = 4, TRNS_TYPE_POSTPAID = 5} CARDTYPE_TRNS_TYPE;
	typedef enum { CS_NORMAL = 0, CS_LOCK = 1, CS_FROZEN, CS_LOSS, CS_CANCEL, CS_EXPIRED } CARDSTATUS_TYPE;
	typedef enum { RT_USERCARD = 0,RT_PSAM , RT_KEYCARD } READER_TYPE;
public:
	void SetAppPath(const char *path);
	virtual void SetLogTrace(KS_Log_Tracer *tracer);
	virtual void SetLastErrMsg(const char* errmsg,const char *file = __FILE__,int line= __LINE__);
	virtual char*  GetLastErrMsg (char *errmsg);
	virtual void  Attach (ks_device_op_t *device,ks_reader_dev_t *reader,READER_TYPE t);
	ks_device_op_t * GetDevice(READER_TYPE t);
	ks_reader_dev_t *GetDevicePara(READER_TYPE t);
	// �ú������ڴ򿪴��ں��ɿ�ܵ���
	virtual int  OpenPort ();
	virtual int SetFieldReadMode(int fieldid);
	virtual int SetFieldWriteMode(int fieldid);
	virtual int SetFieldAllMode(int fieldid);
	virtual void ClearFieldReadMode(int fieldid);
	virtual void ClearFieldWriteMode(int fieldid);
	//������ֶ�����ģʽ
	virtual void ClearFieldAllMode(int fieldID);
	virtual void ClearAllFieldReadMode();
	virtual void ClearAllFieldWriteMode();
	virtual void ClearAllFieldAllMode();
	inline virtual int ReadRecordFile(byte ucSFI,byte ucRecordNo,byte ucLength,byte *ucData);
	int getCardTypeCode() const { return m_CardTypeCode; }
	void SetCardTypeNo(int no) { this->m_cardTypeNo = no; }
	int GetCardTypeNo() { return this->m_cardTypeNo; }
	virtual int SetKeyCard(ks_cardtype_base *c);
	ks_psamcard_base * GetPSAMCardType() const { return this->m_PSAMCardType; }
	void SetPSAMCardType(ks_psamcard_base *p) { m_PSAMCardType = p; }
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt) = 0;
	virtual int InitCardTypeDLL() {return 0;}
	virtual void SetMifare1Key(const char *sCipherKey){};
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo) = 0;
	virtual int  SetFieldVal (int FieldID,const char *fieldval) = 0;
	virtual int  GetFieldVal (int FieldID,char *fieldval) = 0;
	/*!
	 \brief Ѱ������
	 \param szCardPhyID - ���ؿ�����ID��
	 \return ���� 0 ��ʾѰ���ɹ���-1 ��ʾδѰ����������0 ��ʾѰ���������ǲ�֧��
	*/
	int  RequestCard (char *szCardPhyID=NULL);
	/*!
	 \brief �ڶ���Ѱ��ʱ����ʹ����������жϿ�Ƭ�Ƿ����
	 \return ���� 0 ��ʾ�����ڣ�-1��ʾ������������Ҫ����Ѱ��
	*/
	virtual int testCardExists(char *szCardPhyID) = 0;
	virtual int  CheckSupportCard(const char *szCardPhyID,KS_CARD_TYPE ct);
	virtual unsigned int RequestCardType(){ return 0; }
	virtual int  SelectADF () = 0;
	virtual int  VerifyPin (const char* sPin) = 0;
	virtual int  ReadCard () = 0;
	virtual int  ReadCard(int ReadType){return ReadCard();}
	virtual int  WriteCard () = 0;
	virtual int  InitUserCard (const char *sShowCardNo) = 0;
	virtual int  LoadKeysFromKeyCard (const char *sKeyCardPwd) = 0;
	virtual int  IsLoadKeys () = 0;
	virtual int  IsLoadCloneKeys () = 0;
	virtual int  LoadKeys4Clone (const char sKeyCardPin[7]) = 0;
	virtual int  CloneKeyCard (const char sCloneCardPin[7]) = 0;
	virtual int  PublishKeyCard (unsigned char* sMasterKey,const char* sPin) = 0;
	virtual int  RecycleKeyCard () = 0;
	//virtual int  PublishPSAMCard (ST_PSAMCARD* PSAMCard) = 0;
	//virtual int  RecyclePSAMCard () = 0;
	virtual int  RestoreFactorySettings () = 0;
	//virtual int  ReadPSAMTermno (char *termno) = 0;
	virtual int  SaveKeys () = 0;
	virtual int  VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass) = 0;
	virtual int  CommInit (const char *svrip,int svrport,int svrfunc) = 0;
	virtual int  AddMoney(ST_TRANSPACK *transpack) = 0;
	virtual int  PayMoney(ST_TRANSPACK *transpack) = 0;
	virtual int  ExtAuth(const char *cardphyid,int keyidx) = 0;
	//virtual int  ReadPSAMCard(ST_PSAMCARD* PSAMCard) = 0;
	virtual int  Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) = 0;
	virtual int  Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) = 0;
	//virtual int  Adpu4HexSAM(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) = 0;
	//virtual int  ResetPSAM() = 0;
	virtual int ReadRecordFile(int SFI,unsigned char *ucData,int idx = 1,int len = 0) = 0;
	virtual int ReadRecordFile4Mac(int SFI,unsigned char *ucData,int idx = 1,int len = 0) = 0;
	virtual int	 AuthDLL(const char *key,int flag);
	// 0 - ��ʾ֧�� �� 1 - ��ʾ��ֵ 
	virtual int InitForTrans(ST_TRANSPACK *trans,int trans_type) = 0;
	virtual int DebitForTrans(ST_TRANSPACK *trans) = 0;
	virtual int water_publishcard(int watertype,ks_water_pack_t *pack);
	virtual int water_recyclecard(int watertype);
	virtual int water_readmoney(int watertype,ks_water_pack_t *pack);
	virtual int water_writemoney(int watertype,ks_water_pack_t *pack);
	virtual int water_publishparamcard(int watertype,ks_water_param_t *param);
	virtual int water_recycleparamcard(int watertype);
	virtual int water_read_paramcard(int watertype,ks_water_param_t *param);
	virtual int water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	virtual int water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate);
	virtual void DumpSectData(int watertype);
	virtual int GrayLock(ST_TRANSPACK *transpack);
	virtual int GrayDebitUnlock(ST_TRANSPACK *transpack);
	virtual int GrayUnlock(ST_TRANSPACK *transpack);
	virtual int CAPPUpdate(ST_TRANSPACK *transpack);
	virtual int CAPPDebit(ST_TRANSPACK *transpack);
	virtual int PostPaidUpdate(ST_TRANSPACK *transpack);
	virtual int PostPaidDebit(ST_TRANSPACK *transpack);
	virtual int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac=NULL,unsigned char *sTac=NULL);
	virtual int doSubRequestCard(char *szCardPhyID)
	{
		return KS_NOTSUPPORT;
	}

	virtual int  PublishOperCard(const char * BatchNo, const char * BatchSeqNo, const char *ExpDate, const char *OperAcc, const char *OperName, const char *OperPwd, const char *StationNo){return -1;}
};

DECL_DLLFUNC(int,register_cardtype_op,(ks_cardtype_base *&op));

//////////////////////////////////////////////////////////////////////////////////
class ks_psamcard_base
{
public:
	char m_currentADF[128];
	char m_ADFData[256];
	static const char MF_SFI[];
protected:
	ks_cardlib_license *m_license;
	const ks_device_op_t *m_Reader;
	ks_reader_dev_t *m_ReaderPara;
	ks_reader_dev_t m_Para;
	char  m_szAppPath[256];
	char m_ErrMsg[512];
	CARDKEYS  m_CardKeys;
	int m_PowerOn;
	int m_PSAMSlot;
	virtual void resetAll();
public:
	virtual int selectADFBySFI(const char *SFI,int force = 0);
	virtual int selectADFByName(const char *ADFName,int force = 0);
	ks_psamcard_base();
	virtual ~ks_psamcard_base();
	virtual void SetLogTrace(KS_Log_Tracer *tracer);
	void setLicense(ks_cardlib_license *lic);
	void setCardKeys(CARDKEYS &keys);
	virtual void Attach(const ks_device_op_t *reader,const ks_reader_dev_t * para);
	void SetAppPath(const char *path);
	virtual void SetLastErrMsg(const char* errmsg,const char *file = __FILE__,int line= __LINE__);
	virtual char*  GetLastErrMsg (char *errmsg);
	virtual void SetSAMPara(const ks_reader_dev_t *para);
	virtual int InitDll(ks_cardlib_license *lic) = 0;
	virtual int PublishPSAMCard(ST_PSAMCARD* PSAMCard) = 0;
	virtual int RecyclePSAMCard() = 0;
	virtual int ReadPSAMCard(ST_PSAMCARD* PSAMCard) = 0;
	virtual int ResetPSAM();
	virtual int ReadPSAMTermno(char *sTermno) = 0;
	virtual int CalcSafeMac(const char *cmd,int len,char *sMac) = 0;
	virtual int CalcDepositMac(ST_TRANSPACK *transpack) = 0;
	virtual int CalcConsumeMac(ST_TRANSPACK *transpack) = 0;
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo) = 0;
	virtual int CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac) = 0;
	virtual int CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac) = 0;
	virtual int CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt) = 0;
	virtual int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) = 0;
	virtual int CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac) = 0;
	virtual int Adpu4HexSAM(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
	virtual int Adpu4SAM(const unsigned char *uCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen);
};

DECL_DLLFUNC(int,register_sam_op,(ks_psamcard_base *&sam));

#endif // _KSCARDTYPE_H_
