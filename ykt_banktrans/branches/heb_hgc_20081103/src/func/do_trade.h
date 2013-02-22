/* ----------------------------------------------------------
 * 程序名称：do_trade.h
 * 创建日期：2007-08-09
 * 程序作者：李翔
 * 版本信息：1.0.0.0
 * 程序功能：圈存功能头文件, 所有圈存功能函数声明在此
 * ----------------------------------------------------------*/

#ifndef	__do_trade_h__
#define	__do_trade_h__

//////////////////////////// constant defined ///////////////////////////////
#ifndef	NULL
#define	NULL	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

int do_buy_water(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_query_water(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_mobile_transfer(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_write_card_fail(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);


#ifdef __cplusplus
	}
#endif

#endif
 ////////////////////////////////////////////////////////////////////////////

