// kscard.cpp : Defines the initialization routines for the DLL.
#ifndef __KSCARD_IMP_H
#define __KSCARD_IMP_H
#pragma warning(disable:4786) 

#include <Windows.h>

#define IN 
#define OUT
#define FIELDMAXNUM			100
//注:CF=CARDFIELD
//卡公共信息
#define CF_START			1		//开始号
#define CF_CARDNO			2		//交易卡号
#define CF_SHOWCARDNO		3		//显示卡号
#define CF_FEETYPE			4		//收费类别
#define CF_SUBSIDYNO		5		//补助批次号
#define CF_CARDVERNO		6		//卡版本号
#define CF_CARDSTATUS		7		//卡状态0 正常1-锁定2冻结卡3-挂失卡4_注销卡5过期卡
#define CF_STARTDATE		8		//启用日期
#define CF_EXPIREDATE		9		//过期日期
#define CF_PUBLISHID		10		//发行方标识
#define CF_CARDTYPE			11		//卡类别
#define CF_APPTYPE			12		//应用类型 
#define CF_CARDSTRUCTVER	13		//卡结构版本
//持卡人信息
#define CF_SCHOOLCODE		20		//校区代码
#define CF_CUSTID			21		//客户号
#define CF_CUSTTYPE			22		//客户类别
#define CF_STUEMPNO			23		//学工号
#define CF_NAME				24		//姓名
#define CF_SEX				25		//性别
#define CF_DEPTCODE			26		//部门代码
#define CF_IDNO				27		//证件号码
#define CF_IDTYPE			28		//证件类型
//银行卡号
#define CF_BANKCARDNO		30		//银行卡号
//交易明细
#define CF_TRANSDTL_BEGIN	31
#define CF_CARDCNT			31		//卡交易次数(最后一次交易)
#define CF_TRANSAMT			32      //交易金额(最后一次交易)
#define CF_TRANSTYPE		33		//交易类型(最后一次交易)
#define CF_TERMID			34      //交易终端机编号(最后一次交易)
#define CF_TRANSDATE		35		//交易日期(最后一次交易)
#define CF_TRANSTIME		36		//交易时间(最后一次交易)
#define CF_TRANSDTL_END		36

#define CF_DAYSUMAMT		37		//当日累计交易金额
//交易参数
#define CF_SINGLEMAXAMT		41		//单次消费限额
#define CF_DAYMAXAMT		42		//日消费累计限额
//卡余额			
#define CF_CARDBAL			50		//卡余额
//卡密码
#define CF_CARDPWD			51		//卡密码
//流水信息
#define CF_DPSCNT			64		//充值交易次数
#define CF_PAYCNT			65		//消费交易次数


#define CF_END				99		//结束标志
#define LEN_CARDNO			10
#define LEN_SHOWCARDNO		10
#define LEN_CARDSTATUS		1
#define LEN_PUBLISHID		2
#define LEN_CARDTYPE		1
#define LEN_FEETYPE			1
#define LEN_STARTDATE		4
#define LEN_EXPIREDATE		4
#define LEN_SUBSIDYNO		4
#define LEN_CARDVERNO		7
#define LEN_DEVICEID		6
#define LEN_CARDSTUCTVER	1
#define LEN_CARDSN			8
#define LEN_OPERNO			10 //操作员号

#define LEN_CUSTID			4		
#define LEN_CUSTTYPE		1
#define LEN_STUEMPNO		20		
#define LEN_SEX				1
#define LEN_NAME			32		
#define LEN_DEPTCODE		20		
#define LEN_IDNO			32		
#define LEN_IDTYPE			28		
#pragma pack(1)	
typedef struct {
 	byte	ucCardNo[10];	//PSAM序列号
	byte	ucCardVerNo;	//PSAM版本号
	byte	ucCardType;		//密钥卡类型
	byte    ucCmdVerNo;		//指令集版本
	byte	ucFCI[1];		//发卡方自定义FCI数据
}ST_PSAMCARD15;

typedef struct {
 	byte	ucKeyIndex;	//消费密钥索引号
	byte	ucPublishID[8];	//发行方ID		
	byte	ucUserID[8];	//使用方ID
	byte    ucStartDate[4];	//启用日期
	byte	ucExpireDate[4];//有效日期
}ST_PSAMCARD17;
typedef struct {
	char sCardNo[21];		//PSAM卡号
	size_t nCardType;		//PSAM卡类型
	size_t nCardVer;		//卡版本
	char sTermID[13];	//终端编号
	size_t nTermSeqno;		//终端交易序号
	size_t nKeyIndex;		//密钥索引号
	char sStartDate[9];	//启用日期
	char sExpireDate[9];//有效日期
	char sPublishID[17];	//发行方标识
	char sUserID[17];	//使用方标识
}ST_PSAMCARD;

typedef struct {
	 byte ucCardNo[LEN_CARDNO];			//交易卡号
	 byte ucShowCardNo[LEN_SHOWCARDNO];	//显示卡号
	 byte ucCardStatus;	//卡状态0 正常
	 byte ucCardVerNo[LEN_CARDVERNO];	//卡黑名单版本号
	 byte ucDeviceID[LEN_DEVICEID];		//设备ID
	 byte ucFeeType;		//收费类别
	 byte ucCardStructVer;//卡结构版本
	 byte ucStartDate[LEN_STARTDATE];	//启用日期
	 byte ucExpireDate[LEN_EXPIREDATE];	//过期日期
	 byte ucSubsidyno[4];			//补助批次号
	 byte ucPublishID[2];		//发行方标识
	 byte ucCardType;		//卡类别
	 byte reserve[5];		//保留
}ST_BASEINFO;
typedef struct {
	 byte ucName[LEN_NAME];				//姓名
	 byte ucIDNo[LEN_IDNO];				//证件号码
	 byte ucIDType;			//证件类型
	 byte ucSex;				//性别
	 byte ucStuempNo[LEN_STUEMPNO];		//学工号
	 byte ucDeptCode[LEN_DEPTCODE];		//部门代码
	 byte ucCustType;		//客户类别
	 byte ucCustID[4];			//客户号
}ST_PERSONINFO;
typedef struct {
	byte ucSingleMaxAmt[3];
	byte ucDayMaxAmt[3];
}ST_TRANSPARA;
typedef struct {
	byte ucCardCnt[2];		//卡交易序号
	byte ucLimit[3];		//透支限额
	byte ucTransAmt[4];		//交易金额
	byte ucTransType;		//交易类型
	byte ucTermID[6];		//终端编号
	byte ucTransDate[4];	//交易日期
	byte ucTransTime[3];	//交易时间
}ST_TRANSDTL;

typedef struct {
	int recordno;		//记录号
	int exist;			//如果记录存在，则为1，否则为0
	char transdate[9];	//交易日期(YYYYMMDD)
	char transtime[7];	//交易时间(HHMMSS)
	int paycnt;			//消费次数
	int cardbefbal;		//交易前余额
	int transamt;		//交易金额(包含搭伙费)
	int otherfee;		//搭伙费
	int extamt;			//补写金额(加钱为正减钱为负)
	int shopid;			//商户号
	char termno[13];	//终端机编号(PSAM卡中的终端号)
	int termsno;		//终端交易序号(计算TAC用)
}ST_PAYDTL;
//消费明细结构

// 交易结构
typedef struct {
	int     nTermID;		//设备终端编号
	int		nCardNo;		// 交易卡号	
	char	sCardPhyID[17];	// 卡序列号
	size_t  nDpsCardCnt;	// 交易前卡充值次
	size_t  nPayCardCnt;	//交易前消费次数
	size_t  nSubsidyNo;		//补助批次号
	int		nBefBalance;	// 交易前卡余额，单位分
	int		nAftBalance;	// 交易后卡余额，单位分
	int		nTransAmt;		// 充值金额，单位分
	char	sTransDate[9];	// 交易日期
	char	sTransTime[7];	// 交易时间
	char  	sTermno[13];	// PSAM卡终端号
	size_t  nTermSeqno;		// 终端交易序列号
	char    sRandom[9];		//随机数
	char	sOperCode[9];	//操作员代码
	size_t	nFundType;		// 充值类型 1 现金，2 支票 3 经费本 4 其他
	char	sVoucherNo[31];	// 充值票据号
	int     nTransType;		//交易类型 0-充值 1扣款
	int     nPayCode;		//支付代码
	int		nPayType;		//支付类型,消费类使用
	///////////////以下为输出值//////////////////////////////
	char	sRefNo[17];		//交易参考号
	char    sMac[9];		//MAC
	size_t	nHostSeqno;		//交易主机流水号
	int		nErrCode;		//错误码
	char	sErrMsg[256];	//错误信息
}ST_TRANSPACK;

#pragma pack()
//设置错误信息
int __stdcall ks_init();
void __stdcall ks_setlasterr(char *errmsg,int errcode=-1);
//读取动态库错误信息
char* __stdcall ks_geterrmsg(char *errmsg);

void __stdcall ks_getversioninfo(char *version,char *builddate,char *desc);

int __stdcall ks_licence(const char *lisence,const char *pwd);

/*int  dc_init(int port,long baud);
功 能：初始化通讯口
参 数：port：取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
baud：为通讯波特率9600～115200
返 回：成功则返回串口标识符>0，失败返回负值，见错误代码表
例：int icdev;
icdev=dc_init(0,9600);//初始化串口1，波特率9600*/
int __stdcall ks_openport(int port,int band);
/* int dc_exit(int icdev);
功 能：关闭端口
参 数：icdev：通讯设备标识符
返 回：成功返回0
例：dc_exit(icdev);*/
int __stdcall ks_closeport();
/* int ks_beep(unsigned int _Msec);
功 能：蜂鸣
unsigned int _Msec：蜂鸣时间，单位是10毫秒
返 回：成功则返回 0
例：int st;
st=ks_beep(10);            鸣叫100毫秒*/
void __stdcall ks_beep();
int __stdcall GetRandomNum(byte *uRandomNum,char *sRandomNum);

/*
说明：设置读写器将要对哪一种卡操作，读写器上电缺省的时候是对TYPEA操作。
	参数说明：HANDLE icdev dc_init返回的设备描述符；
	cardtype：当为'A'的时候表示设置读写器，'B'表示对TYPE B操作
		返回：成功则返回 0；
		
			举例:
			int st;
			st= ks_setcardtype ('B');//设置对TYPE B卡操作
*/
int __stdcall ks_setcardtype(int cardtype);
/*int ks_halt();
  功 能：中止对该卡操作
  参 数：icdev：通讯设备标识符
 返 回：成功则返回0
 例：st=dc_halt(icdev);
 说明：使用dc_card()函数时，有个_Mode参数，如果_Mode=0则在对卡进行操作完毕后，执行ks_halt();则该卡进入HALT模式，则必须把卡移开感应区再进来才能寻得这张卡。
*/
//SAM
int __stdcall  ks_halt();

/*
int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
功 能：寻卡，能返回在工作区域内某张卡的序列号(该函数包含了dc_request,dc_anticoll,dc_select的整体功能)						
						参 数：icdev：通讯设备标识符						
						_Mode：寻卡模式mode_card						
						_Snr：返回的卡序列号						
						返 回：成功则返回 0						
						例：int st;
*/


int __stdcall ks_reset(int msec);

//寻卡
//int __stdcall ks_card(unsigned long *_Snr);

int __stdcall ks_card(char *sCardPhyID);
// 
int __stdcall ks_mf_card(char *sCardPhyID);
/*
1.5.1.	设置卡操作控制码
 	函数原型：int ks_setfield(int mode,int mask)
 	入口参数：
int  mode - 读卡/写卡模式，1表示先读后写，2表示先写后读 2先写后读
int  mask - 读/写操作对应卡属性索引，见卡属性索引表
 	出口参数：
	无
 	函数返回： 
0 --成功，其它见错误码表*/
//设置该字段读模式
void __stdcall ks_setfieldreadmode(int fieldID);
//设置该字段写模式
void __stdcall ks_setfieldwritemode(int fieldID);
//设置该字段读写模式
void __stdcall ks_setfieldallmode(int fieldID);
//清除该字段读模式
void __stdcall ks_clearfieldreadmode(int fieldID);
//清除该字段写模式
void __stdcall ks_clearfieldwritemode(int fieldID);
//清除该字段所有模式
void __stdcall ks_clearfieldallmode(int fieldID);
//清除所有字段的读模式
void __stdcall ks_clearallfieldreadmode();
//清除所有字段的写模式
void __stdcall ks_clearallfieldwritemode();
//清除所有字段的读写模式
void __stdcall ks_clearallfieldallmode();

int __stdcall ks_getfieldval(int fieldID,char *fieldval);
/*1.5.6.	设置写字段数据
函数原型：int ks_set_card_data(int mask,const char *data)
入口参数：
int mask - 读/写卡操作对应卡属性索引，见索引表	
int data - 卡属性值
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_setfieldval(int fieldID,const char *fieldval);
/*1.5.4.	读取卡信息
	函数原型：int ks_read_card()
	入口参数：
	无
	出口参数：
	无
	函数返回： 
	0 --成功，其它见错误码表*/
int __stdcall ks_readcard();

//对于7+1卡,读cpu区域cardtype=0,读mifare1区域cardtype=1,全部读cardtype=2
int __stdcall ks_readcard2(int cardtype);
/*1.5.7.	写卡信息
函数原型：int ks_write_card ()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_writecard (const char *sCardPhyID=NULL);
/*1.5.8.	验证口令
函数原型：int ks_verify_pin(char pin[7])
入口参数：
char pin[7]  -6个数字字符的个人PIN
出口参数：
无
函数返回： 
0 --成功，其它见错误码表
*/
//修改卡状态
//state  0-正常 1锁定 2冻结 3挂失 4注销 5过期
int __stdcall ks_modifystatus(int state);
//修改密码
int __stdcall ks_modifypasswd(const char oldpwd[7],const char newpwd[7]);
//重置密码
int __stdcall ks_resetpasswd(const char *cardphyid,const char newpwd[7]);
//验证密码

//验证口令
int __stdcall ks_verifypin(char pin[7]);
/*1.5.10.	应用锁定
函数原型：int ks_lockapp()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_lockapp();
/*1.5.11.	应用解锁
函数原型：int ks_unlock_application()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_unlockapp();
//通讯初始化
int __stdcall ks_comminit(const char *svrip,int svrport,int svrfunc);
//终端签到
int __stdcall ks_login(int termid,int& shopid,char shopname[61]);
// 充值
int __stdcall ks_deposit(ST_TRANSPACK *transpack,int must_online);
// 扣款
int __stdcall ks_payment(ST_TRANSPACK *transpack,int must_online);
//消费冲正（按交易参考号）
int  __stdcall ks_pay_reverse(ST_TRANSPACK *payment,int must_online);
//int  __stdcall ks_deposit_init(IN int Termid,IN int nTransAmt,OUT int& nCardBal,OUT int& nCardCnt,OUT char *sRandomNum,OUT char sMac1);

//int  __stdcall ks_deposit_init(IN int Termid,IN int nTransAmt,char *deposit_data);

//int  __stdcall ks_deposit_end(char *sTransDate,char *sTransTime,char *sMac2);
//设置卡余额
int  __stdcall  ks_setcardbal(ST_TRANSPACK *transpack);
//计算MAC
int __stdcall ks_calcmac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,unsigned char *uMacData,int iMacDataLen,unsigned char *uMac);
int __stdcall ks_calcsafemac(const char* szCmdBuf,char *szMac);
int __stdcall CalcDF03SafeMac4Sam(const char *szCardNo,const char *szCmdbuf,char *szMac);
//加密母密钥函数
int __stdcall ks_encryptkey(unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen);


//检查是否密钥已经加载
//返回值0- 未加载1加载

int __stdcall ks_checkloadkeys();

//装载密钥
int __stdcall ks_loadcardkeys(char *sKeyCardPwd);

//卸载密钥
void __stdcall ks_unloadcardkeys();
//用户卡初始化
int __stdcall ks_publishusercard(const char *sCardPhyID,const char *szShowCardNo);
//回收用户卡,重写显示卡号
//useflag 为1时表示取传入的显示卡号 为0时如果卡内显示卡号为空，则取输入的，否则取卡内的。
int __stdcall ks_recycleusercard(int nUseFlag,const char *szCardShowNo);

int __stdcall ks_refineusercard(int nUseFlag,const char *szCardShowNo);

//PSAM卡函数
/*
int ks_setcpu4sam(int SAMID);
说明：设置要操作的SAM卡座 

unsigned char SAMID --- 设置要操作的卡座号,0x0c为大卡座，1、 2、 3 各为SAM1 SAM2 SAM3 

返回：<0 错误。其绝对值为错误号

=0 成功
*/
int __stdcall ks_setcpupara4sam(int SAMID);

//PSAM卡上电复位
int __stdcall ks_samcpureset();
//PSAM卡上电复位同上带参数
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff);
//发行PSAMK卡
int __stdcall ks_publishpsamcard(ST_PSAMCARD* PSAMCard);
int __stdcall ks_recyclepsamcard();
int __stdcall ks_readpsamcard(ST_PSAMCARD* PSAMCard);
//读取PSAM 卡终端编号
int __stdcall ks_readpsamtermno(char *termno,int need_request=0);
//读取终端交易序号
int __stdcall ks_readpsamtermseqno(int& termseqno,int need_request=0);
//密码校验
int __stdcall ks_verifypasswd(const char *sCardPhyID,const char *cardpasswd,int& iIsPass);
//检查是否克隆密钥已经加载
//返回值0- 未加载1加载
int __stdcall ks_checkloadclonekeys();
//装载密钥给克隆卡使用
int __stdcall ks_loadkeys4clone(const char sKeyCardPin[7]);
//克隆密钥卡
int __stdcall ks_clonekeycard(const char sCloneCardPin[7]);
//保存密钥卡到数据库
int __stdcall ks_savekeys();
//读消费明细流水
int ks_readpaydtl(int recordno,ST_PAYDTL *paydtl);
//设置MF1卡工作密钥
int __stdcall ks_setmifare1key(const char sWorkKey[17]);

//////////////////////////////////////////////////////////////////////////
// 深圳凯路相关功能
#pragma pack(1)
typedef struct {
	int money; // 卡上余额
	int pre_money; // 上次消费额
	char add_time[15]; // 上次充值时间
	int add_count; // 充值次数
}sr_water_pack_t;

typedef struct {
	int cardno; // 交易卡号
	int cardtype; // 卡类别
	int custno; // 客户号
}sr_water_info_t;

#pragma pack()

int __stdcall ks_sr_publishcard(sr_water_info_t *info);
int __stdcall ks_sr_recyclecard();
int __stdcall ks_sr_readmoney(sr_water_pack_t *pack);
int __stdcall ks_sr_setmoeny(int money,int cnt);

//////////////////////////////////////////////////////////////////////////
// 一卡通水控相关接口定义
#pragma pack(1)
typedef struct {
	int cardno; // 交易卡号
	int custno; // 客户号
	int cardtype; // 客户类别
	char expiredtime[9]; // 有效期
	int lockflag; // 锁定标志，00 锁定，FF可用
}ks_water_info_t;

typedef struct {
	int cardno; // 交易卡号
	int custno; // 客户号
	int cardtype; // 客户类别
	char expireddate[9]; // 有效期
	int lockflag; // 锁定标志，00 锁定，FF可用
	//////////////////////////////////////////////////////////////////////////
	// 钱包信息
	int money; // 卡余额
	int totalmoney; // 充值总金额
	char addtime[15]; // 充值时间
	int addcount; // 充值次数
	// 水价1
	int price1;
	// 水价2
	int price2;
	// 水价3
	int price3;
}ks_water_pack_t;

typedef struct {
	unsigned char workkey[8];	// 种子密钥
	int minmoney;				// 卡钱包预警金额
	int maxmoney;				// 卡钱包金额上限
	int unit;					// 计费单位（秒/升)
	int transmoney;				// 单次转账单位
	int unitmoney;				// 单价
	int priceindex;				// 水价索引
	int watersect;				// 水控钱包扇区号
	int cardflag;				// 参数卡标志
	int termid;					// 终端号
}ks_water_param_t;

#pragma pack()

#define KS_SZROAD_WATER 1 // 凯路水控
#define KS_YNCS_XT_WATER 2 // 云交职水控
#define KS_HD_WATER 3 // 汇多脱机水控

int __stdcall ks_water_publishcard(int watertype,ks_water_pack_t *pack);
int __stdcall ks_water_recyclecard(int watertype);
int __stdcall ks_water_readmoney(int watertype,ks_water_pack_t *pack);
int __stdcall ks_water_writemoney(int watertype,ks_water_pack_t *pack);
/**
 \brief 发行水控参数卡
 \param watertype - 水控厂商类型
 \param param - 参数卡使用的参数值
 
 1. 新天参数卡
    unsigned char workkey[8];	// 种子密钥， 填写 0x01,0x02,0x03,0x04,0x05,0x06
	int minmoney;				// 预警金额,  冷水表参数卡使用，表示预警的水量，单位为吨， 热水表填0
	int maxmoney;				// 卡钱包金额上限， 不使用
	int unit;					// 计费单位（秒/升) ，不使用
	int transmoney;				// 单次转账单位   ， 冷水表参数卡使用，表示每次转账的水量，单位为吨；热水表填0
	int unitmoney;				// 单价   ， 冷水表、热水表通用，表示每吨水价格，单位为 分/吨
	int priceindex;				// 水价索引 ， 不使用
	int watersect;				// 水控钱包块号 ， 冷水表、热水表通用，表示用户卡使用的块号，需要作为一卡通全局参数进行设置
	int cardflag;				// 参数卡标志， 0 表示参数卡；1 表示清零卡，当为清零卡时前面所有参数都不使用
	int termid;					// 终端号，冷水表、热水表通用参数，填 1
 */
int __stdcall ks_water_publishparamcard(int watertype,ks_water_param_t *param);
int __stdcall ks_water_recycleparamcard(int watertype);

#endif
