/* ----------------------------------------------------------
 * �������ƣ�do_trade.h
 * �������ڣ�2007-08-09
 * �������ߣ�����
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�Ȧ�湦��ͷ�ļ�, ����Ȧ�湦�ܺ��������ڴ�
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

