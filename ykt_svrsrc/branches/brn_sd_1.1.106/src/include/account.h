#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#define MAXNUM_ACC 	30

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int  iTradeNo;				//交易码
	int  iSerialNo;				//后台主机流水号
	int  iDevId;					//终端设备ID
	int  iMainDevId;				//终端机构ID
	int  iTxFlag;					//交易标志0-正常交易,1-冲正交易, 2-负值交易
	int  iCardNo;					//卡号
	int  iTxCnt;					//当前累计卡中交易次数
	int  iFeeType;				//收费类型
	int  iUseCardFlag;			//有卡交易/无卡交易标志，1为有卡,其他为无卡
	double  dInCardBala;			//入卡值,如果入卡值为-1，则说明为空，以分为单位
	double  dOutCardBala;	    	   	//出卡值,如果出卡值为-1，则说明为空，以分为单位
	char sTxDate[11];				//交易日期，格式为yyyymmdd
	char sTxTime[9];				//交易时间，格式为hhmmss
	char sTxCollectDate[11];		//采集日期，格式为yyyymmdd
	char sTxCollectTime[9];		//采集时间，格式为hhmmss
	char sTxAccDate[11];			//记账日期，格式为yyyymmdd
	char sTxAccTime[9];			//记账时间，格式为hhmmss
	char sMdeOper[9];			//录入操作员,8位
	char sChkOper[9];			//复核操作员,8位
	char sTalOper[9];				//入账操作员,8位
	char sArrInActno[MAXNUM_ACC][17];	//账号,16位
	int 	iArrInFeeSwitch[MAXNUM_ACC / 2];		//发生额，单位为元
	double dArrInAmt[MAXNUM_ACC / 2];		//输入发生额，单位为元
	int 	iOutTxTypeCnt;						//输出收费条目总数
	int  iArrOutTxType[MAXNUM_ACC / 2];		//交易类型
	double dArrOutAmt[MAXNUM_ACC / 2];		//输出发生额，单位为元
	char    sArrOutTxName[MAXNUM_ACC / 2][61];	//输出发生额对应的交易名称
	void *pVoidPointer;			//无类型指针,作为备用数据块
	int iSubIndex;				//子流水号起始值 iSubIndex = 0 则起始流水号为 1
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
