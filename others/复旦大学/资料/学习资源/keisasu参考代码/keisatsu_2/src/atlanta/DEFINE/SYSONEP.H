/* Oct.3,1995 By S.K */
#ifndef sysonep_h
	#define sysonep_h

#include	"\src\atlanta\define\sysonet.h"

/************************************************************************
 * ワンタッチダイヤルポインタ											*
 * struct SYS_OnetouchPointerData_t			    						*
 * 1993/12/28															*
 * 田中伸一　															*
 ***********************************************************************/

struct SYS_OnetouchPointerData_t {
	UBYTE *StatusPointer;	/* 登録状態ポインタ */
	union {
		struct SYS_SpeedDialData_t *Onetouch;	/* ワンタッチ構造体ポインタ */
		struct SYS_ProgramDialData_t *Program;	/* プログラム構造体ポインタ */
	} DialData;
};
#endif

