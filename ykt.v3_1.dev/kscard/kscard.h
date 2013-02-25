// kscard.cpp : Defines the initialization routines for the DLL.
#ifndef __KSCARD_H
#define __KSCARD_H
#pragma warning(disable:4786) 
#include "kscard_imp.h"
#include <map>
#include <vector>
#include <string>
#include <windows.h>
#include "kslicense.h"

#include "cardtypemanager.h"

//extern HANDLE g_nHandle;

using namespace std;

enum VALTYPE {VT_UNDEF,VT_BIN,VT_BCD,VT_ASC};
typedef struct 
{
	int  nFieldID;			//字段ID
	int  nFieldOffset;		//字段对在文件中的偏移地址
	int  nFieldSize;		//字段长度
	char szFieldName[32];	//字段名称
	byte ucFieldVal[32];	//字段在卡中存储的值
	VALTYPE nFieldValType;		//字段存储类型
}CARDFIELD;

class CKsCard
{
public:
	CKsCard();
	unsigned long m_uCardSNo;
	ST_BASEINFO   m_ReadBaseInfo;
	ST_PERSONINFO m_ReadPersonInfo;
	ST_TRANSPARA  m_ReadTransPara;
	ST_TRANSDTL   m_ReadTransdtl;
	ST_BASEINFO   m_WriteBaseInfo;
	ST_PERSONINFO m_WritePersonInfo;
	ST_TRANSPARA  m_WriteTransPara;
	map<int,string> mapReadFieldVal,mapWriteFieldVal;
//	int nSingleMaxAmt;
//	int nDayMaxAmt;
	int nCardBalance;
	int nCardDptCnt;
	int nCardPayCnt;
	int nCardSsdCnt;
	char sReadCardPwd[64],sWriteCardPwd[64];
	int SMT_MAC_UpdateBinaryFile( byte ucSFI,byte ucOffset,byte ucLength,byte *ccAppSerailNo,byte *ucData);
	//读记录文件//1字节SFI，1字节记录号 1字节长度
	int InitField();	
	void Clear();
	int ReadRecordFile(byte ucSFI,byte ucRecordNo,byte ucLength,byte *ucData);
	int ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	//int MacReadBinaryFile(byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData);
	int MacReadBinaryFile(const char *sCardPhyID,byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData);
	int ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int ChangePin( char* coldPin, char* cnewPin);
	int VerifyPin( char* cPin);
	int SelectPacketOneDir(byte *ucRes);
	int SelectSchoolPacketDir(byte *ucRes);
	int SelectBankDir(byte *ucRes);
	int SelectMFDir(byte *ucRes);
	int SelectBaseFile(byte *ucRes);
	int SelectPersonFile(byte *ucRes);
	int SelectTransParaFile(byte *ucRes);
	int ReadBalance(int& cardbalance);
//	int ReadTrandtl(int num);
	int WriteCard(const char *sCardPhyID);
	int ReadPayCnt(int& cardpaycnt,int& cardbalance);
	int ReadDptCnt(int& carddptcnt,int& cardbalance);
	int ReadSsdCnt(int& cardssdcnt);
};

//2.结构体===================================================
typedef struct SCardTableIndex
{
	int		nIndexNo; //索引号
	char	sIndexName[64]; //索引所对应名称函义
	char	sIndexValue[64];//索引所对应的值
	bool	bStatus;		//表示是否已经读取 true 已读  false 未读
}ST_CARDTABLEINDEX;

//主密钥
typedef struct SCardMainKey
{
	byte MK[17];	//种子密钥
	byte DPK1[17];	//消费1
	byte DPK2[17];	//消费2
	byte DLK1[17];  //圈存1
	byte DLK2[17];  //圈存2
	byte DTAC[17];	//内部密钥TAC
	byte DACK[17];	//外部认证0
	byte DUK[17];   //PIN解锁
	byte DRPK[17];	//PIN重装
	byte DAMK[17];	//维护密钥
	byte DACK1[17];	//外部认证1
	byte DACK2[17];	//外部认证2
	byte DACK3[17];	//外部认证3
	byte LDACK[17];	//小钱包外部认证密钥
	byte LDAMK[17];	//小钱包维护密钥
	int  bLoad;
}ST_CARDMAINKEY;

typedef struct SuperCardKey
{
	byte DPK1[16];  //消费1
	byte DPK2[16];  //消费2
	byte DPK3[16];  //消费3
	byte DLK1[16];  //圈存1
	byte DLK2[16];  //圈存2
	byte DLK3[16];  //圈存3
	byte DTAC1[16]; //TAC1
	byte DTAC2[16]; //TAC2
	byte DTAC3[16]; //TAC3
	byte DUK[16];   //PIN解锁
	byte DRPK[16];  //PIN重装
	byte DAMK[16];  //维护
	byte DACK[16];  //主控
	byte NPK1[16];  //内部认证主密钥
	byte EPK1[16];  //外部认证主密钥1
	byte EPK2[16];  //外部认证主密钥2
	byte EPK3[16];  //外部认证主密钥3
	byte EPK4[16];  //外部认证主密钥4
}ST_SUPERCARDKEY;
//保存写卡索引及值
typedef struct SWriteCardInfo
{
	int  nIndex; //索引号	
	byte sValues[128]; //值
}ST_WRITECARDINFO;

//保存读卡索引及卡值
typedef struct SReadCardInfo
{
	int  nIndex; //索引号	
	byte sValues[128]; //值
}ST_READCARDINFO;


//公共基本信息
typedef struct SPublicInfo_15
{
	char	sAppSerial[21]; //应用序列号(交易卡号)
	char	sShowCard[11];  //显示卡号
	int		nCardStatus;	//卡状态
	char	sBlkVer[15];	//黑名单版本
	char	sDeivceID[13];	//设备ID号
	int		nFeeType;		//卡收费类别
	int     nCardType;		//卡类别
	int		nCardVer;		//卡结构版本 
	char	sStartDate[9];  //启用日期
	char	sValidDate[9];	//有效日期
	int		nSubsidyBatchNo;//补助批次号
	int		nPublishID;		//发行方标识
} ST_PUBLICINFO_15;


//持卡人基本信息
typedef struct SPersonalInfo_16
{
	int		nCustType;		//客户类型
	int		nCustID;		//客户号
	char	sStuEmpNo[21];	//学工号
	char	sName[31];		//姓名
	char	sDeptCode[21];	//部门代码
	char	sIDNo[33];		//证件号码
	int		nIDType;		//证件类型
	int		nSex;			//性别		1-男2-女
} ST_PERSONALINFO_16;

//交易规则文件
typedef struct STradeRule_12
{
	int		nOnceLimitMoney;	//单限
	int		nDaySaleLimitMoney; //日限
	int		nDetailMax;			//明细最大值
} ST_TRADERULE_12;

typedef struct SPublishUserCardInfo
{
	char	sBankNo[21];
	ST_PUBLICINFO_15	sTrFile15;
	ST_PERSONALINFO_16 sTrFile16;
	ST_TRADERULE_12		sTrFile12;
} ST_PUBLISHUSERCARDINFO;


/*
int ks_resetpro(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
说明：卡上电复位函数,仅针对于TYPE A 卡
调用：int ICDev ---- dc_init 函数返回的端口标识符
unsigned char *rlen ---- 返回复位信息的长度
unsigned char * rbuff ---- 存放返回的复位信息
返回： <0 错误。其绝对值为错误号
=0 成功。
举例：st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
//卡复位
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff);

int __stdcall ks_setcpupara4sam(int SAMID);
/*
__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
说明：应用协议数据单元信息交换函数。该函数已封装T=CL操作
调用：int ICDev ----dc_init 函数返回的端口标识符
unsigned char slen ---- 发送的信息长度
unsigned char * sbuff ---- 存放要发送的信息
unsigned char *rlen ---- 返回信息的长度
unsigned char * rbuff ---- 存放返回的信息
unsigned char tt---- 延迟时间，单位为：10ms
*/
//CPU卡直通指令
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendDatalen, 
						 unsigned char* sRespData,unsigned char &nRespDatalen );

/*
__int16 dc_cpuapdu(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)

说明：CPU卡APDU（应用协议数据单元）信息交换函数。该函数封装了T=0和T=1操作 

调用：int ICDev ----dc_init 函数返回的端口标识符

unsigned char *slen ---- 发送的信息长度

unsigned char * sbuff ---- 存放要发送的信息

unsigned char *rlen ---- 返回信息的长度

unsigned char * rbuff ---- 存放返回的信息

返回： <0 错误。其绝对值为错误号

=0 成功。
*/
int __stdcall ks_cpuapdu4hex(const char *szCmd,unsigned char nCmdlen,unsigned char* ucRespData,unsigned char &nRespDatalen );

//SAM卡直通指令
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendDatalen, 
							 unsigned char* sRespData,unsigned char &nRespDatalen );

/*函数功能：
由一卡通系统人员输入16字节的根密钥，系统自动产生
消费密钥分散因子1、消费密钥分散因子2、
圈存密钥分散因子1、
TAC密钥分散因子1、TAC密钥分散因子2、
PIN解锁分散因子、
重装PIN分散因子、
维护密钥分散因子、
应用主控密钥分散因子共9条分散因子。
函数原型：int ks_KeyCard_Publish( char* sMasterKey, char* sPin )
入口参数：
char* sMasterKey  -16字节的根（主）密钥 （0~9 a~f A~F） 
char* sPin          -6个数字字符的个人密码
出口参数：
无
函数返回： 
0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_publishkeycard(unsigned char* sMasterKey, char* sPin );
/*	函数功能：
在认证PIN通过后，才可以根据相应序号获取相应的应用密钥，序号对应关系如下：
1--消费密钥1
2--消费密钥2
3--圈存密钥
4--TAC密钥1
5--TAC密钥2
6--PIN解锁密钥
7--重装PIN密钥
8--维护密钥
9--主控密钥
函数原型：int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
入口参数：
int    nKeySerial  -密钥序号
char* sPin          -6个数字字符的个人密码
出口参数：
char* sKey  	  -16字密钥
函数返回： 
0 --成功，其它值-错误(PBOC错误码)
可以将密钥获取后存于数据库中（最好加密钥保存)
*/
//回收密钥卡
int __stdcall ks_recyclekeycard();
//int __stdcall ks_getkey(int nKeySerial,char* sPin, char* sKey);
/*
用户发卡
函数原型：int ks_Make_card_UserCard(ST_SPUBLISHUSERCARDINFO sCardInfo)
入口参数：
ST_SPUBLISHUSERCARDINFO sCardInfo		
出口参数：
无
函数返回： 
0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_makeusercard(ST_PUBLISHUSERCARDINFO sCardInfo);
/*
用户卡洗卡
函数原型：int ks_init_card_UserCard(ST_SCARD_MAIN_KEY sStrKey,
char *sAppid,
char  *sShowCard,
int nWalletDetailCount)
入口参数：
char * sAppid	-卡片用户序列号 (20个字符)
char*sShowCard	-显示卡号  (10个字符)
int nWalletDetailCount -钱包明细最大值
出口参数：
无
函数返回:
0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_initcard4user(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount);
/*
1.4.1.2.	PSAM卡洗卡
函数原型：int ks_init_card_PSAMCard(char *sAppid,
char *  sTerminalNo)
入口参数：
char *  sAppid- PSAM序列号
char *  sTerminalNo -终端机编号
出口参数：
无
函数返回： 
0 --成功，其它值-错误(PBOC错误码)
待处理的问题：3条密钥(消费、维护、主控，通过结构体ST_SCARD_MAIN_KEY传入）
*/
int __stdcall ks_initcard4psam(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo);

//充值初始化
int  __stdcall ks_addmoney(ST_TRANSPACK *deposit);
int __stdcall ks_cpuapdu4sam_hex(const char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen );
//通过后台计算MAC
int __stdcall  ks_calctransmac(ST_TRANSPACK *transpack,char *sMac);
//消费
int  __stdcall ks_purchase(ST_TRANSPACK *transpack);

int __stdcall ks_format_mfcard(const char *sCardPhyID,const char *sShowCardNo);
int __stdcall ks_external_auth(const char *phyno);
//////////////////////////////////////////////////////////////////////////
// mifare 卡相关函数
int ks_mf_login_card(int sectno);


/////////////////////////////////////////////////////////
extern ks_cardlib_license g_license;
#endif
