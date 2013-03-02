#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#define MAXNUM_ACC 	10

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	int  iTradeNo;				//交易码
	int  iTermID;				//终端编号
	int  iSerialNo;				//后台主机流水号
	int  iSubIndex;				//子流水号起始值 iSubIndex = 0 则起始流水号为 1
	int  iMainDevId;				//终端设备ID
	int  iTxFlag;				//交易标志0-正常交易,1-冲正交易, 2-负值交易
	int  iCardNo;				//卡号
	int  iDevId;
	int  iTxCnt;				//当前累计卡中交易次数
	int  iFeeType;				//收费类型
	int  iOnlineFlag;			//联机标志
	int  iUseCardFlag;			//有卡交易/无卡交易标志，1为有卡,其他为无卡
	int  iCalAftBalflag;		//是否计算出卡值标志
	int  iBefBalFlag;			//是否有交易前卡余额
	double  dInCardBala;				//交易前卡余额
	double  dOutCardBala;				//交易后卡余额
	int  iShopID;				//商户号
	char sTxDate[9];			//交易日期，格式为yyyymmdd
	char sTxTime[7];			//交易时间，格式为hhmmss
	char sTxCollectDate[9];		//采集日期，格式为yyyymmdd
	char sTxCollectTime[7];		//采集时间，格式为hhmmss
	char sTxAccDate[9];			//记账日期，格式为yyyymmdd
	char sTxAccTime[7];			//记账时间，格式为hhmmss
	char sOperCode[9];			//操作员号
	char sChkOper[9];			//复核操作员号

	int  iOutTxTypeCnt;			//输出收费条目总数
	char sArrInActno[MAXNUM_ACC][17];			//账号,16位
	int  iArrInFeeSwitch[MAXNUM_ACC];		//发生额，单位为元
	double  dArrInAmt[MAXNUM_ACC];				//输入发生额，单位为元
	int  iArrOutTxType[MAXNUM_ACC];			//交易类型
	double dArrOutAmt[MAXNUM_ACC];			//输出发生额，单位为元
	char sArrOutTxName[MAXNUM_ACC][61];		//输出发生额对应的交易名称
	void *pVoidPointer;			//无类型指针,作为备用数据块
}InAcc;

int AccountProcess (InAcc * inacc);

// 正常交易
#define ACC_TYPE_NORMAL       0
// 冲正交易
#define ACC_TYPE_RUSH	     1
// 透支交易
#define ACC_TYPE_OVERDRAFT  2

#ifdef __cplusplus
}
#endif

#endif
