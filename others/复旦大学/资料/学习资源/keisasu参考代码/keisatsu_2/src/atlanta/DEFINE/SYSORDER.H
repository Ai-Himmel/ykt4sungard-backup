#ifndef sysorder_h
	#define sysorder_h

#include "\src\atlanta\define\sysmax.h"

/************************************************************************
 * 消耗品発注データ														*
 * struct SYS_ConsumerOrderData_t SYB_ConsumerOrder						*
 * 1997/09/18															*
 * 橘正樹																*
 ************************************************************************/
#define	SYS_ORDER_CODE_MAX	11
#define	SYS_ORDER_NAME_MAX	31
#define	SYS_ORDER_DIAL_MAX	21
#define	SYS_ORDER_SERIAL_MAX	19
#define	SYS_ORDER_DIAL2_MAX		15		/* orderbythonda1998/11/11 */

/************************************************************************
 * 消耗品発注データ														*
 * struct SYS_ConsumerOrderData_t SYB_ConsumerOrder						*
 * 1997/09/18															*
 * 橘正樹																*
 ************************************************************************/
struct SYS_ConsumerOrderData_t {
	UBYTE	ToCustomerCode[SYS_ORDER_CODE_MAX];		/* 発注先 得意先コード	*/
	UBYTE	ToCompany[SYS_ORDER_NAME_MAX];			/* 発注先 社名			*/
	UBYTE	FromCustomerCode[SYS_ORDER_CODE_MAX];	/* 発注元 得意先コード	*/
	UBYTE	FromCompany[SYS_ORDER_NAME_MAX];		/* 発注元 社名			*/
	UBYTE	FromSection[SYS_ORDER_NAME_MAX];		/* 発注元 部課名		*/
	UBYTE	FromTelNumber[SYS_ORDER_DIAL_MAX];		/* 発注元 ＴＥＬ		*/
	UBYTE	SerialNumber[SYS_ORDER_SERIAL_MAX];		/* シリアル番号			*/
	UDWORD	InstallDate;							/* 設置日				*/
};

/************************************************************************
 * 消耗品発注品目														*
 * 1998/01/31															*
 * 橘正樹																*
 ************************************************************************/
#define	SYS_ORDER_ITEM_TONER	0x01
#define	SYS_ORDER_ITEM_DRUM		0x02

#endif
