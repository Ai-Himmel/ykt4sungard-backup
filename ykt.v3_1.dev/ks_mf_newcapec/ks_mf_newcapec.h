#ifndef _ks_mf_newcapec_h_
#define _ks_mf_newcapec_h_

#include "kscardtype.h"
#include "ks_cardtype.h"
#include <vector>

#pragma pack(1)	

typedef struct
{
	byte carduse;				//卡用途
	byte account[3];			//帐号
	byte deptcode;				//单位标示 
	byte cardbatchno;			//卡批次号
	byte cardseqno[2];			//卡批次序号
	byte cardpwd[3];			//个人密码
	byte errcnt;				//错误计数
	byte station;				//工作站编码
	byte reserve[2];			//保留
	byte crc;					//CRC(8)校验

}OPERBLK1;

typedef struct
{
	byte cardstatus;			//卡状态：F1-正常，F3-挂失
	byte expiredate[2];			//消费失效期
	byte rights;				//权限
	char name[10];				//姓名
	byte reserve;				//保留
	byte crc;					//CRC(8)校验

}OPERBLK2;

typedef struct 
{
byte factory[16];			//厂商代码
byte carduse;				//卡用途：9
byte cardver;				//卡版本：1<<4
byte cardno[3];				//卡号
byte deptcode;				//单位标示 
byte cardbatchno;			//卡批次号
byte cardseqno[2];			//卡批次序号
byte sex;					//性别：1-女，2-男
byte publishdate[2];		//发卡日期，7位-年，4位-月，5位-日
byte reserve1;				//保留
byte nationcode;			//民族代码
byte cardtype;				//卡类别
byte crc1;					//CRC(8)校验
byte cardstatus;			//卡状态：F1-正常，F3-挂失
byte tradequota[2];			//餐消费限额，填0
byte tradepin[3];			//个人消费密码
byte blackver[6];			//黑名单版本
byte expiredate[2];			//消费失效期
byte reserve2;				//保留
byte crc2;					//CRC(8)校验
}PERINFO;		

typedef struct
{
byte custname[16];			//姓名
byte stuempno[10];			//学工号
byte idno[9];				//身份证18位
byte libno[13];				//图书证条码
}PUBLICINFO;

typedef struct
{
byte balance[3];				//卡余额
byte subsidyamt_totalamt[6];	//3-5补助（高2位给总额） 和 6-8总额：充值+，提现-	
byte tradecnt[2];				//交易次数
byte reserve[2];				//宏冲日期，保留
byte subsidyno;					//补助
byte meal;						//餐别
byte crc1;
byte reserve1[16];				//备份区
byte rwtest[5];					//读写性能测试块
byte today;						//本日
byte dayamt[3];					//日消费累计
byte mealamt[3];				//餐消费累计
byte reserve2[4];
}PACKAGEINFO;

typedef struct
{
int apptype;			//应用类型
int feetype;			//收费类别
int custtype;			//客户类别
int custid;				//客户号
int idtype;				//证件类型
int dpscnt;				//充值交易次数
int transdate;			//交易日期(最后一次交易)
int daymaxamt;			//日消费累计限额
int publishid;			//发行方标志
int showcardno;			//显示卡号
int subsidyno;			//补助批次号
int cardstruct;			//卡结构版本（应用版本）
int schoolcode;			//校区代码

}T_NEWCAPEC_CARD;


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

class ks_mf_newcapec_type : public CCardType
{

private:
	enum { 
		KA_1ST = 0, // 第一个版本
		KA_PSAM = 1 // PSAM 卡
	};
	static FILE * ks_mf_newcapec_type::g_dump_file;
	ks_card_info_t m_cardinfo;
	ks_card_info_t *m_mfcard;
	int m_isLoadKey;
	int m_mainPackSect;
	int m_secdPackSect;						// 小钱包扇区号
	KS_MF_KEYTYPE m_initKeyType;			//出厂初始化时，使用登录的密钥， 0 表示 keya , 1 表示 keyb
	byte m_initLoginKey[6];					//出厂密钥，{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
	
	unsigned char m_mainkey[8];
	
	byte m_OriginPhyNo[4];
	byte m_presentPhyNo[4];
	mf_sect_t m_cardSect[MF_MAX_SECTNO];
	
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
	
	void DumpCardBlockData(int sect,int block,BYTE *buf);
	int CalcKeyFromSAMKeyA(unsigned char *cipherData);
	int CalcKeyFromSAMKeyB(unsigned char *cipherData);
	int initAllCardDef();
	
	int testLoadKey();

	int encryptKeyA(unsigned char *key,unsigned char *sCipher);
	int encryptKeyB(unsigned char *key,unsigned char *sCipher);
	int iPsamPowerOnCnt;
	int NewAuthCard_Init_Sect(unsigned char PhyNo[4]);

	int ReadNewcapecInfoFromDB(byte* buffer);
	int WriteNewcapecInfoIntoDB(byte* buffer);

protected:
	virtual int checkCardType(int ct);
	virtual int doSuccessRequestCard();
	virtual int doSubRequestCard(char *szCardPhyID);
public:
	ks_mf_newcapec_type();
	virtual ~ks_mf_newcapec_type();

	///////////////////////////////////
public:
	void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	void SetMifare1Key(const char *sCipherKey);
	int LoadKeysFromKeyCard(const char *sKeyCardPwd);
	virtual int  PublishKeyCard (unsigned char* sMasterKey,const char* sPin);
	virtual int  RecycleKeyCard();
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int  PublishOperCard(const char * BatchNo, const char * BatchSeqNo, const char *ExpDate, const char *OperAcc, const char *OperName, const char *OperPwd, const char *StationNo);
	virtual int RestoreFactorySettings();
	virtual int SetKeyCard(ks_cardtype_base *c);
	
	virtual int testCardExists(char *szCardPhyID);
	int IsLoadKeys();
	int SaveKeys();
	int LoadKeys4Clone(const char sKeyCardPin[7]);
	int IsLoadCloneKeys();
	int CloneKeyCard(const char sCloneCardPin[7]);
	int ReadCard();
	int WriteCard();
	int SetFieldVal(int FieldID,const char *fieldval);
	int GetFieldVal(int FieldID,char *fieldval);
	virtual char * GetErrMsgByErrCode( int nErrCode,char *sErrInfo);

	int  AddMoney(ST_TRANSPACK *transpack);
	int  PayMoney(ST_TRANSPACK *transpack);
	
	int	 AuthDLL(const char *key,int flag);
	
	int GetMifare1WorkKey();
	virtual int InitForTrans(ST_TRANSPACK *trans,int trans_type);
	
	virtual int InitCardTypeDLL();
	virtual int GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac);

};

#endif