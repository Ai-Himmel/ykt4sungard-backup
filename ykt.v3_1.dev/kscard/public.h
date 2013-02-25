#ifndef  __PBULIC__H
#define  __PBULIC__H

//1.========================================安全算法===============
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );

/*=================================================================
* Function ID : YCT_VerifyPurchaseMac1
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
unsigned char *sKey,			//16字节的消费主密钥
unsigned char *sRandom,			//消费初始化成功返回的4字节伪随机数
unsigned long lCardInvoiceNo,	//消费初始化返回2字节的脱机交易序号				
unsigned long lPurchMoney,		//需要消费的金额	
unsigned char *TerminalNo,      //终端号			
* Output      : void
unsigned char *sMac1
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 计算消费MAC1
*=================================================================*/
unsigned long YCT_VerifyPurchaseMac1( 
									 unsigned char *sAppNo,
									 unsigned char *sKey,
									 unsigned char *sRandom,
									 unsigned long lCardInvoiceNo,
									 unsigned long lPurchMoney,
									 unsigned char *TerminalNo,
									 unsigned char *sMac1);

/*=================================================================
* Function ID : YCT_VerifyLoadMac1
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
				unsigned char *sKey,			//16字节的圈存主密钥
				unsigned char *sRandom,			//圈存初始化成功返回的4字节伪随机数
				unsigned long lCardInvoiceNo,	//圈存初始化成功返回的2字节的交易序号
				unsigned long lCardBal,			//圈存初始化成功返回的钱包交易前余额
				unsigned long lAddMoney,		//需要充值的金额
				unsigned char *TerminalNo,		//6字节的终端机编号
				unsigned cha  *sMac1			//圈存初始化成功返回的4字节MAC1
* Output      : void
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 校验圈存初始化时卡返回的MAC1，用于认证用户卡的合法性
*=================================================================*/
unsigned long YCT_VerifyLoadMac1( unsigned char *sAppNo,
								 unsigned char *sKey,
								 unsigned char *sRandom,
								 unsigned long lCardInvoiceNo,
								 unsigned long lCardBal,
								 unsigned long lAddMoney,
								 unsigned char *TerminalNo,
								 unsigned char *sMac1);
/*=================================================================
* Function ID : YCT_CalLoadMac2
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
				unsigned char *sKey,			//16字节的圈存主密钥
				unsigned char *sRandom,			//圈存初始化成功返回的4字节伪随机数
				unsigned long lCardInvoiceNo,	//圈存初始化成功返回的2字节的交易序号			
				unsigned long lAddMoney,		//需要充值的金额
				unsigned char *TerminalNo,		//6字节的终端机编号
				unsigned char *sDate,			//4字节交易日期(YYYYMMDD)
				unsigned char *sTime			//3字节交易时间(HHMMSS)
* Output      : unsigned char *sMac2			//4字节的MAC2
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 计算圈存MAC2
*=================================================================*/
unsigned long YCT_CalLoadMac2( unsigned char *sAppNo,
							  unsigned char *sKey,
							  unsigned char *sRandom,
							  unsigned long lCardInvoiceNo,
							  unsigned long lAddMoney,
							  unsigned char *TerminalNo,
							  unsigned char *sDate,
							  unsigned char *sTime,
							  unsigned char *sMac2);

//安全报文MAC
unsigned char* CalSecure_MAC(
							 unsigned char *key,
							 unsigned char *random, 
							 int len,
							 unsigned char *input_data,
							 unsigned char *out_data);

//2.结构体===================================================
typedef struct sCardTableIndex
{
	int		nIndexNo; //索引号
	char	sIndexName[64]; //索引所对应名称函义
	char	sIndexValue[64];//索引所对应的值
	bool	bStatus;		//表示是否已经读取 true 已读  false 未读
}ST_SCARD_TABLE_INDEX;

//主密钥
typedef struct sCardMainKey
{
	byte DPK1[17]; //消费
	byte DPK2[17]; //消费
	byte DLK[17];  //圈存
	byte DTAC1[17];//TAC
	byte DTAC2[17]; //TAC
	byte DUK[17];   //PIN解锁
	byte DRPK[17]; //PIN重装
	byte DAMK[17];//维护
	byte DACK[17];//主控
	bool bLoad;
}ST_SCARD_MAIN_KEY;

//保存写卡索引及值
typedef struct sWriteCardInfo
{
	int  nIndex; //索引号	
	byte sValues[128]; //值
}ST_SWRITECARDINFO;

//保存读卡索引及卡值
typedef struct sReadCardInfo
{
	int  nIndex; //索引号	
	byte sValues[128]; //值
}ST_SREADCARDINFO;

//公共基本信息
typedef struct sPublicInfo_15
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
} ST_SPUBLICINFO_15;


//持卡人基本信息
typedef struct sPersonalInfo_16
{
	int		nCustType;		//客户类型
	int		nCustID;		//客户号
	char	sStuEmpNo[21];	//学工号
	char	sName[31];		//姓名
	char	sDeptCode[21];	//部门代码
	char	sIDNo[33];		//证件号码
	int		nIDType;		//证件类型
	int		nSex;			//性别		1-男2-女
} ST_SPERSONALINFO_16;

//交易规则文件
typedef struct sTradeRule_12
{
	int		nOnceLimitMoney;	//单限
	int		nDaySaleLimitMoney; //日限
	int		nDetailMax;			//明细最大值
} ST_STRADERULE_12;

typedef struct sPublishUserCardInfo
{
	char	sBankNo[21];
	ST_SPUBLICINFO_15	sTrFile15;
	ST_SPERSONALINFO_16 sTrFile16;
	sTradeRule_12		sTrFile12;
} ST_SPUBLISHUSERCARDINFO;


#endif