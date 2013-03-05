/************************************************************************
*	System		: POPLAR_F
*	File Name	: MDMERPRO.C
*	Author		: 
*	Date		: 1999/10/06
*	Description	:“à‘ •”‚q‚n‚l‚©‚çŠO•”‚q‚n‚l“à‚Ìƒ‚ƒWƒ…[ƒ‹‚ğQÆ‚·‚é‚½‚ß
*				 ŠO•”‚q‚n‚l‚ÌŒÅ’èƒAƒhƒŒƒX‚ÅƒR[ƒ‹‚·‚é‚½‚ß
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"

/* mdm_g3.c */
UBYTE	RxG3_ReadExtRom(void);

/* mdm_sub.c */
void	NextMdmBufWritePointSetExtRom(void);
UBYTE	CheckEcmStatusExtRom(UWORD);	/*	ƒtƒŒ[ƒ€”Ô†i‚O`‚Q‚T‚Tj	*/
void	NextMdmBufReadPointSetExtRom(void);

