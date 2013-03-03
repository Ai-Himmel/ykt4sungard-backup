/************************************************************************
*	System		: POPLAR_F
*	File Name	: MDMERTBL.C
*	Author		: 
*	Date		: 1999/10/06
*	Description	:“à‘ ‚q‚n‚l‚©‚çŠO•”‚q‚n‚l“à‚Ìƒ‚ƒWƒ…[ƒ‹‚ğQÆ‚·‚é‚½‚ß
*				 “à‘ ‚q‚n‚l‚©‚çŒÅ’èƒAƒhƒŒƒX‚ÅƒR[ƒ‹‚·‚é‚½‚ß
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\mdm\fm336\define\mdmerpro.h"

#if (PRO_CPU_VERSION == SH7043_R)	/* 2001/12/21 T.Takagi */
/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚Í“à‘ ‚b‚o‚t‚Ìƒ}ƒXƒNƒvƒƒOƒ‰ƒ€‚ª•ÏX‚É‚È‚è‚Ü‚·B
** ‚»‚ê‚É”º‚¢A“à‘ ‚q‚n‚l‚©‚çŠO•”‚q‚n‚l^‚q‚`‚l‚ğƒAƒNƒZƒX‚·‚éŠÔÚQÆƒ|ƒCƒ“ƒ^[‚ÍA
** ˆêŒÂŠ‚É‚Ü‚Æ‚ß‚Ü‚µ‚½B
** By O.Kimoto 1998/09/11
*/

#pragma section MDMMTBL /* locate section name "CMDMMTBL" */
/* mdm_g3.c */
CONST UBYTE (* CONST rx_g3_read_ext_tbl)(void) = (UBYTE (*)())RxG3_ReadExtRom;

/* mdm_sub.c */
CONST void (* CONST next_mdmbuf_wp_set_ext_tbl)(void) = (void (*)())NextMdmBufWritePointSetExtRom;

CONST UBYTE (* CONST check_ecm_status_ext_tbl)(UWORD) = (UBYTE (*)(UWORD))CheckEcmStatusExtRom;

CONST void (* CONST next_mdmbuf_rp_set_ext_tbl)(void) = (void (*)())NextMdmBufReadPointSetExtRom;

#pragma section /* locate section name "CMDMMTBL" */

#endif
