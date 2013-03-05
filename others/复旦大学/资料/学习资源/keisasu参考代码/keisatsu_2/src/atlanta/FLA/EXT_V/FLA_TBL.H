/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  1997/04/23
*        FILE NAME:  fla_tbl.h
*       Task ID No:  Not Valid
*      DESCRIPTION:  ÇqÇnÇlÅQÇlÇ`ÇoÉeÅ[ÉuÉãíËã`
*        REFERENCE:
************************************************************************/
#include "\src\atlanta\define\product.h"

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  97/04/23
*             TYPE:
*      VAR TO HOLD:
*      DESCRIPTION:  ÇqÇnÇlÅQÇlÇ`ÇoÉeÅ[ÉuÉã
************************************************************************/
extern CONST struct ROM_MAP_t SYS_RomMap[];

extern CONST UBYTE Title_Msg[];
extern CONST UBYTE OK_Msg[];
extern CONST UBYTE RomSum_Msg[];
extern CONST UBYTE NG_AutoSelect_Msg[];
extern CONST UBYTE NG_ChipErase_Msg[];
extern CONST UBYTE NG_SectorErase_Msg[];
extern CONST UBYTE NG_Program_Msg[];
extern CONST UBYTE NG_SumCheck_Msg[];
extern CONST UBYTE NG_TimeOver_Msg[];
extern CONST UBYTE Erasing_msg[];
extern CONST UBYTE SectorNumber_msg[19][21];
#if 0
//extern CONST UBYTE	DEBUG_FlashCheck;
//extern CONST UBYTE CheckTitle_Msg[];
//extern CONST UBYTE CheckNG_Msg[];
//extern CONST UBYTE CheckErr_Msg[];
//extern CONST UBYTE CheckCnt_Msg[];
#endif
extern CONST UBYTE Flash_Dummy[];
