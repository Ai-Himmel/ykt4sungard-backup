#ifndef _ks_mf_newcapec_h_
#define _ks_mf_newcapec_h_

#include "kscardtype.h"
#include "ks_cardtype.h"
#include <vector>

#pragma pack(1)	

typedef struct
{
	byte carduse;				//����;
	byte account[3];			//�ʺ�
	byte deptcode;				//��λ��ʾ 
	byte cardbatchno;			//�����κ�
	byte cardseqno[2];			//���������
	byte cardpwd[3];			//��������
	byte errcnt;				//�������
	byte station;				//����վ����
	byte reserve[2];			//����
	byte crc;					//CRC(8)У��

}OPERBLK1;

typedef struct
{
	byte cardstatus;			//��״̬��F1-������F3-��ʧ
	byte expiredate[2];			//����ʧЧ��
	byte rights;				//Ȩ��
	char name[10];				//����
	byte reserve;				//����
	byte crc;					//CRC(8)У��

}OPERBLK2;

typedef struct 
{
byte factory[16];			//���̴���
byte carduse;				//����;��9
byte cardver;				//���汾��1<<4
byte cardno[3];				//����
byte deptcode;				//��λ��ʾ 
byte cardbatchno;			//�����κ�
byte cardseqno[2];			//���������
byte sex;					//�Ա�1-Ů��2-��
byte publishdate[2];		//�������ڣ�7λ-�꣬4λ-�£�5λ-��
byte reserve1;				//����
byte nationcode;			//�������
byte cardtype;				//�����
byte crc1;					//CRC(8)У��
byte cardstatus;			//��״̬��F1-������F3-��ʧ
byte tradequota[2];			//�������޶��0
byte tradepin[3];			//������������
byte blackver[6];			//�������汾
byte expiredate[2];			//����ʧЧ��
byte reserve2;				//����
byte crc2;					//CRC(8)У��
}PERINFO;		

typedef struct
{
byte custname[16];			//����
byte stuempno[10];			//ѧ����
byte idno[9];				//���֤18λ
byte libno[13];				//ͼ��֤����
}PUBLICINFO;

typedef struct
{
byte balance[3];				//�����
byte subsidyamt_totalamt[6];	//3-5��������2λ���ܶ �� 6-8�ܶ��ֵ+������-	
byte tradecnt[2];				//���״���
byte reserve[2];				//������ڣ�����
byte subsidyno;					//����
byte meal;						//�ͱ�
byte crc1;
byte reserve1[16];				//������
byte rwtest[5];					//��д���ܲ��Կ�
byte today;						//����
byte dayamt[3];					//�������ۼ�
byte mealamt[3];				//�������ۼ�
byte reserve2[4];
}PACKAGEINFO;

typedef struct
{
int apptype;			//Ӧ������
int feetype;			//�շ����
int custtype;			//�ͻ����
int custid;				//�ͻ���
int idtype;				//֤������
int dpscnt;				//��ֵ���״���
int transdate;			//��������(���һ�ν���)
int daymaxamt;			//�������ۼ��޶�
int publishid;			//���з���־
int showcardno;			//��ʾ����
int subsidyno;			//�������κ�
int cardstruct;			//���ṹ�汾��Ӧ�ð汾��
int schoolcode;			//У������

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

// ��ʼ��ʱ����λ KEYA��KEYB �ɶ���д��KEYB�ɸ�����Կ
#define MF1_INIT_CTRLBIT		"\x7F\x07\x88\x00"
// ��ʼ��ʱ����λ KEYAֻ����KEYB �ɶ���д��KEYB�ɸ�����Կ
#define MF1_KEYA_RO_CTRLBIT		"\x78\x77\x88\x00"
// ��ʼ��ʱ����λ KEYA��KEYB �ɶ���д��KEYA�ɸ�����Կ
#define MF1_ORIGIN_CTRLBIT		"\xFF\x07\x80\x69"

class ks_mf_newcapec_type : public CCardType
{

private:
	enum { 
		KA_1ST = 0, // ��һ���汾
		KA_PSAM = 1 // PSAM ��
	};
	static FILE * ks_mf_newcapec_type::g_dump_file;
	ks_card_info_t m_cardinfo;
	ks_card_info_t *m_mfcard;
	int m_isLoadKey;
	int m_mainPackSect;
	int m_secdPackSect;						// СǮ��������
	KS_MF_KEYTYPE m_initKeyType;			//������ʼ��ʱ��ʹ�õ�¼����Կ�� 0 ��ʾ keya , 1 ��ʾ keyb
	byte m_initLoginKey[6];					//������Կ��{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
	
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