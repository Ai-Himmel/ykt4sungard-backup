/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WRD3.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤ用固定文字列（写像領域３)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\wording.h"

#if (PRO_CPU == SH7043)
	#pragma section OPR_WRD0	/* セクション名の指定 COPR_WRD0 */
#endif

/* 日本でもダミーの第３ワーディングをリンクするように変更したが、ポプラでＲＯＭ容量がなくなったので、もとに戻します */
#if defined(JPN)	/* by K.Watanabe 1997/12/10 */
/* 何もソースがないとコンパイルエラーとなるための対応 */
CONST UBYTE	OPR_DUMMY_WORD3[] = "\0";
#else
#include D2W_WORDING_3
#endif

#if (PRO_CPU == SH7043)
	#pragma section
#endif
