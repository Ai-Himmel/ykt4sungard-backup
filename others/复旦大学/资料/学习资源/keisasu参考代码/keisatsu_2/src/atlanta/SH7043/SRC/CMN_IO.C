/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_IO.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_io.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\sh7043\define\io_pro.h"

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\src\popb_io.c"
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplr_bn\src\popb_io.c"
#endif
#if defined(POPLAR_L)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_l\src\popl_io.c"
#endif
#if defined(POPLAR_N)	/** ＰＯＰＬＡＲ＿Ｎタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_n\src\popn_io.c"
#endif
#if defined(POPLAR_H)	/** ＰＯＰＬＡＲ＿Ｈタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_h\src\poph_io.c"
#endif
#if defined(ANZU_L)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\src\anzu_io.c"
#endif
#if defined(ANZU_V) /** ＡＮＺＵ＿Ｖタイプは機種別ディレクトリに移動しました */
					/* 1998/04/14 Eguchi */
	#include "\src\atlanta\anzu_v\src\anzv_io.c"
#endif
#if defined(SAKAKI)	/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\sakaki\src\saki_io.c"		/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (KEISATSU)	/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */ /* HINOKI2 2001/11/13 T.Takagi */
	#include "\src\atlanta\hinoki\src\hino_io.c"		/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(POPLAR_F)	/** Ｌ４００後継タイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_f\src\popf_io.c"
#endif
#if defined(SATSUKI2)
	#include "\src\atlanta\satsuki2\src\sats_io.c"		/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(STOCKHM2)
	#include "\src\atlanta\stockhm2\src\lvnd_io.c"		/* By H.Yoshikawa 1998/05/07 */
#endif

/*機種共通のみ*/
/*************************************************************************
	module		:[ＣＳ３空間のウェイトコントロールレジスタをリードする]
	function	:[	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[引数は0から15まで]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/17]
	author		:[小谷正樹]
*************************************************************************/
UWORD CMN_CheckSH_WCR1_CS3(void)
{
	UWORD wcr1;

	wcr1 = SH__WCR1;				/**I/O Read*/
	wcr1 >>= (UWORD)12;				/**12ビットシフト*/
	wcr1 &= 0x000F;					/**上位クリア*/
	return(wcr1);
}


/*************************************************************************
	module		:[ＣＳ３空間のウェイトコントロールレジスタを変更する]
	function	:[	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[引数は0から15まで]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/17]
	author		:[小谷正樹]
*************************************************************************/
void CMN_SetSH_WCR1_CS3(UWORD wait)
{
	UWORD wcr1;

	wcr1 = SH__WCR1;				/**I/O Read*/
	wcr1 &= 0x0FFF;					/**最上位クリア*/
	wcr1 |= (UWORD)(wait << 12);	/**12ビットシフト*/
	SH__WCR1 = wcr1;
}
