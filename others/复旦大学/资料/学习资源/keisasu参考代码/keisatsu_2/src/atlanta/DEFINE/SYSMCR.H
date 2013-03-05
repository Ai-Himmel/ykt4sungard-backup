/*****************************************************:
 * SYSMCR.H
 * キーマクロ用コマンドデータ
 * 1998/06/17 M.Kuwahara 
 ******************************************************/
#ifndef	SYSMCR_H
 #define	SYSMCRL_H	1

#include	"\src\atlanta\define\sysmax.h"

struct SYS_KeyMacroTable {
	 UBYTE Step[SYS_KEYMACRO_STEP_MAX];		/* ステップ格納バッファ		*/
	 UBYTE Title[SYS_KEYMACRO_TITLE_MAX];	/* タイトルバッファ		*/
};

#endif
