/* By Y.Suzuki 1996/10/15 */
/*  Original File : jun\usr2:\src\kobe\anzu\define\sysspeed.h */
#ifndef sysdiali_h
	#define sysdiali_h

#include "\src\atlanta\define\sysmax.h"
/************************************************************************
 * ダイヤルイン															*
 * struct SYS_DialinData_t SYB_Dialin										*
 * sysdiali.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_DialinData_t {
	UBYTE FaxNumber[SYS_DIALIN_MAX];	/* FAX用番号4桁 */
	UBYTE Tel1Number[SYS_DIALIN_MAX];	/* TEL1用番号4桁 */
	UBYTE Tel2Number[SYS_DIALIN_MAX];	/* TEL2用番号4桁 */
	UBYTE BellTime;						/* 呼出ベル時間 */
};

#endif
