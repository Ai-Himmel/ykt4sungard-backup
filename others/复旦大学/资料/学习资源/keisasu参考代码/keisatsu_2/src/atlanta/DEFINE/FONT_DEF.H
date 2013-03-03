/************************************************************************
*	System		: POPLAR_B
*	File Name	: FONT_DEF.H
*	Author		: 渡辺一章
*	Date		: 1997/04/09
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: フォント構造体定義
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef FONT_DEF_H
	#define FONT_DEF_H	1

#include	"\src\atlanta\define\product.h"

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/04/09
*             TYPE:  struct
*      VAR TO HOLD:  
*      DESCRIPTION:  漢字フォント構造体定義（ＪＩＳ第２水準）
************************************************************************/
struct KanjiFontTableData_t {
	UWORD	Code;			/* JISコード				*/
	UBYTE	FontData[32];	/* 漢字フォント定義データ	*/
};

#define	KANJI2_NONE			0xFF	/* 該当する漢字コードがなかった	*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/27 */
#if (PRO_KANJI2_TYPE == KANJI2_27)
#define	KANJI2_TABLE_MAX	30		/* 漢字定義数					*/
#elif (PRO_KANJI2_TYPE == KANJI2_28) /* 2002/09/27 By M.Maeda */
#define	KANJI2_TABLE_MAX	31		/* 漢字定義数					*/
#elif (PRO_KANJI2_TYPE == KANJI2_29) /* 2002/10/11 By M.Maeda */
#define	KANJI2_TABLE_MAX	32		/* 漢字定義数					*/

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#elif (PRO_KANJI2_TYPE == KANJI2_30) /* 2003/07/09 By M.Maeda */
#define	KANJI2_TABLE_MAX	33		/* 漢字定義数					*/

#else
#define	KANJI2_TABLE_MAX	29		/* 漢字定義数					*/
#endif
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
#if (PRO_KANJI2_TYPE == KANJI2_27)
#define	KANJI2_TABLE_MAX	27		/* 漢字定義数					*/
#elif (PRO_KANJI2_TYPE == KANJI2_28) /* 2002/09/27 By M.Maeda */
#define	KANJI2_TABLE_MAX	28		/* 漢字定義数					*/
#elif (PRO_KANJI2_TYPE == KANJI2_29) /* 2002/10/11 By M.Maeda */
#define	KANJI2_TABLE_MAX	29		/* 漢字定義数					*/

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#elif (PRO_KANJI2_TYPE == KANJI2_30) /* 2003/07/09 By M.Maeda */
#define	KANJI2_TABLE_MAX	30		/* 漢字定義数					*/

#else
#define	KANJI2_TABLE_MAX	26		/* 漢字定義数					*/
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#endif
