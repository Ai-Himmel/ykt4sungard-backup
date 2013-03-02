/* ----------------------------------------------------------
 * 程序名称：bank_boc_yntv.h
 * 创建日期：2011-01-12
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：云南电大中国银行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef	__BANK_BOC_YNTV_H__
#define	__BANK_BOC_YNTV_H__

#define QUERY_BALA			"05"						//查询银行帐户余额
#define TRANS_CODE   		"01"						//转账（圈存）
#define REV_TRANS_CODE   	"11"						//转账（圈存）冲正
#define QUERY_BIND			"21"						//签约查询
#define BIND_BANK			"22"						//签约
#define UN_BIND_BANK		"23"						//解约
#define BANK_SIGN_IN		"31"						// 向银行签到

#define SCHOOLCODE	"0003"						// 昆明冶金专科学校代码

typedef struct _msgbody 
{
	char		TradeCode[2];			//交易代码：见下文(不加密)
	char		RetCode[2];				//交易结果：见下文
	char		TradeDate[8];			//交易日期	 YYYYMMDD
	char		TradeTime[6];			//交易时间	 HHMMSS
	char		CustAccountNo[10];		//校园卡帐号，后补空格
	char		BankCardNo[20];			//银行卡号,	 后补空格
	char		BankPWD[16];			//银行卡密码，后补空格
	char		TransMoney[9];			//转账金额，  以分为单位，前补0
	char		Balance[9];				//借记卡余额，以分为单位，前补0
	char		CustSn[8];				//校园端流水号， 后补空格
	char		BankSn[8];				//银行流水号，	后补空格
	char		IdentityCode[20];	//证件号码，后补空格，一般为身份证号
	char		Name[30];			//姓名，后补空格
	char		CustNo[20];			//院校代码，后补空格
}MEGBODY;

typedef struct _errdef
{
char errcode[4];
char errmsg[64];
}ERRDEF;

#endif

