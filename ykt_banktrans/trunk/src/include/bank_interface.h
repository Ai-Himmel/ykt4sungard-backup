#ifndef	__BANK_INTERFACE_H__
#define	__BANK_INTERFACE_H__#include "cpack.h"#include "bupub.h"
//#ifdef __cplusplus
//extern "C" {
//#endif#define TRADE_TRANS			240001	//自助转帐#define	TRADE_REVERSE			240002 //银行卡转账功能冲正

///////////////////////////////int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);
//#ifdef __cplusplus
//}
//#endif

#endif

