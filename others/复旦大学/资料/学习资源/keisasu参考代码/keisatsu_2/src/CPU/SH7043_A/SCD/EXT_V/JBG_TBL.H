#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#endif

/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/22
*        FILE NAME:  jbg_tbl.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  T.82(JBIG) ämó¶êÑíËRom√∞ÃﬁŸíËã`
*        REFERENCE:
************************************************************************/
extern CONST UWORD JBG_LszTable[JBG_MAX_ST];
extern CONST UWORD JBG_NlpsTable[JBG_MAX_ST];
extern CONST UWORD JBG_NmpsTable[JBG_MAX_ST];
extern CONST UWORD JBG_SwitchTable[JBG_MAX_ST];
