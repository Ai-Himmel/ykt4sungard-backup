#ifndef	__BANK_INTERFACE_H__
#define	__BANK_INTERFACE_H__#include "cpack.h"#include "bupub.h"
//#ifdef __cplusplus
//extern "C" {
//#endif#define 	TRADE_TRANS			240001		//自助转帐#define	TRADE_REVERSE			240002		 //银行卡转账功能冲正#define    BANK_QUERYBALA			240003		// 查询银行卡余额#define 	BANK_BIND				240004		//银行卡绑定#define 	BANK_UNBIND			240005		//银行卡解除绑定typedef struct{	char transtype;		//交易类型	char stuempno[31];	//学号	char custname[31];	//姓名	char idno[31];		//身份证号	char bankcardno[21];//银行卡号	int  retcode;		//返回码	char retmsg[256];	//错误码}BankCardRelation;
///////////////////////////////int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Bind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_UnBind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Querybind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_SignIn(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Checkacc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);
//#ifdef __cplusplus
//}
//#endif

#endif

