/************************************************************************
*	System		: POPLAR
*	File Name	: MEMERTBL.H
*	Author		: Y.Suzuki
*	Date		: 1997/4/1
*	Description	:“à‘ •”‚q‚n‚l‚©‚çŠO•”‚q‚n‚l“à‚Ìƒ‚ƒWƒ…[ƒ‹‚ğQÆ‚·‚é‚½‚ß
*				 ŠO•”‚q‚n‚l‚ÌŒÅ’èƒAƒhƒŒƒX‚ÅƒR[ƒ‹‚·‚é‚½‚ß
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"

#if (PRO_CPU_VERSION == SH7043_A)
/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚Í“à‘ ‚b‚o‚t‚Ìƒ}ƒXƒNƒvƒƒOƒ‰ƒ€‚ª•ÏX‚É‚È‚è‚Ü‚·B
** ‚»‚ê‚É”º‚¢A“à‘ ‚q‚n‚l‚©‚çŠO•”‚q‚n‚l^‚q‚`‚l‚ğƒAƒNƒZƒX‚·‚éŠÔÚQÆƒ|ƒCƒ“ƒ^[‚ÍA
** ˆêŒÂŠ‚É‚Ü‚Æ‚ß‚Ü‚µ‚½B
** By O.Kimoto 1998/09/11
*/
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#else

/* memread.c */
/* UWORD MEM_ReadGetNextBlockNoExtRom(UWORD);*/
extern CONST UWORD (* CONST mem_read_get_next_blk_no_exttbl)(UWORD);

/* UBYTE *MEM_CalculateSoftAddressExtRom(UWORD) */
extern CONST UBYTE  * (* CONST mem_calculate_softaddr_exttbl)(UWORD);

/* memwrite.c */
/* UWORD MEM_WriteGetNextBlockNoExtRom(struct MEM_ExecData_t *);*/
extern CONST UWORD (* CONST mem_write_get_nextblk_no_exttbl)(struct MEM_ExecData_t *);

#endif
