/************************************************************************
*	System		: POPLAR
*	File Name	: ALRPTBL.C
*	Author		: Y.Suzuki
*	Date		: 1998/1/20
*	Description	:フラッシュＲＯＭから拡張ＲＯＭ内のモジュールを参照するため
*				拡張ＲＯＭのコールされるモジュールのアドレスを固定する
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\cph_def.h"
#else
#include "\src\atlanta\scd\define\cph_def.h"
#endif

/* スクランブル */
/*void AlirooScramble (struct CipherTbl_t *)*/
extern CONST void (*CONST alrscramble_adr_tbl)(struct CipherTbl_t *);
/* デスクランブル */
/*void AlirooDescramble (struct CipherTbl_t *)*/
extern CONST void (*CONST alrdescramble_adr_tbl)(struct CipherTbl_t *);
