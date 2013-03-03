/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WRD3.C
*	Author		: 桑原美紀
*	Date		: 1996/11/05
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: リスト用固定文字列（写像領域３)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h" /* T.Nose 1996/07/04 */
#include "\src\atlanta\define\wording.h"

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/03 */
	#pragma section LST_WRD0	/* セクション名の指定 LST_WRD0 */
#endif

/* ポプラＢでＲＯＭ容量がなくなったので、日本だけは第３ワーディングをリンクしません by K.Watanabe 1997/12/10 */
#if (PRO_PANEL == ANK)
 #if defined(JPN)
/* 何もソースがないとコンパイルエラーとなるための対応 */
CONST UBYTE	LST_DUMMY_WORD3[] = "\0";
 #else
#include LST_WORDING_3
 #endif
#else
#include LST_WORDING_3
#endif

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/03 */
	#pragma section
#endif
