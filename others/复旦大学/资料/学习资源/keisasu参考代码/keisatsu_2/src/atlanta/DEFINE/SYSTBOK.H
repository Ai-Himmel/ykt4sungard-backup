/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\systbok.h */
#ifndef systbok_h
	#define systbok_h

#include	"\src\atlanta\define\sysmax.h"

/***********************************************************************
*          BY:   K.Watanabe ( JCS )
*        DATE:   1993/04/08
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:   struct SYS_TelephoneBookData_t SYB_TelephoneBookData[SYS_TELBOOK_MAX]
* DESCRIPTION:   電話帳機能用データバッファ
************************************************************************/
struct SYS_TelephoneBookData_t {
	UBYTE	Status;						/* 入力データ種別 */
	UWORD	DataNumber;					/* 入力データ配列番号 */
	UBYTE	Name[SYS_DIAL_NAME_MAX];	/* 入力データ相手先名 */
};

#endif
