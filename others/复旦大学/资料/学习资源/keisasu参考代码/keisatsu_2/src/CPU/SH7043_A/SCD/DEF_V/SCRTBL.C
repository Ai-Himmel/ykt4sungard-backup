/************************************************************************
*	System		: POPLAR
*	File Name	: ALRTBL.C
*	Author		: Y.Suzuki
*	Date		: 1997/12/3
*	Description	:Šg’£‚q‚n‚l‚©‚çŠO•”‚q‚n‚l“à‚Ìƒ‚ƒWƒ…[ƒ‹‚ğQÆ‚·‚é‚½‚ß
*				Šg’£‚q‚n‚lã‚ÌŒÅ’èƒAƒhƒŒƒX‚ÅƒR[ƒ‹‚·‚é
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
/* ƒƒ‚ƒŠŠÖ˜A */
UBYTE MEM_CheckStoreCode(struct MEM_IndexData_t *);
UBYTE MEM_CheckStoreMode(struct MEM_IndexData_t *);
UBYTE MEM_CheckStoreSize(struct MEM_IndexData_t *);
UWORD MEM_CheckStoreLineCount(struct MEM_IndexData_t *);
UWORD MEM_CountTotalPage(UBYTE, UWORD, UBYTE);
UWORD MEM_ReadOpen(struct MEM_IndexData_t *, struct MEM_ExecData_t *);
UWORD MEM_WriteOpen(struct MEM_StoreData_t *, struct MEM_ExecData_t *);
void MEM_WriteClose(struct MEM_ExecData_t *, UWORD);
UBYTE MEM_ClearPage(struct MEM_IndexData_t *);

/* ƒŠƒXƒg */
void	LST_SetCipher_Image(UBYTE line, UBYTE *dest);
