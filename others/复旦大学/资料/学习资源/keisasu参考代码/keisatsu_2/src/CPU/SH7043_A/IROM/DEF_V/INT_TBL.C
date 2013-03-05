/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : INT_TBL.C                                                */
/*  作成者       : 小谷正樹                                                 */
/*  日  付       : 97.06.13                                                 */
/*  概  要       : 機種共通割り込み処理関数                                 */
/*               : 先頭アドレステーブル                                     */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\def_v\popb_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplr_bn\def_v\popb_int.c"
#endif
#if defined(POPLAR_L)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_l\def_v\popl_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined(POPLAR_N)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_n\def_v\popn_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined(POPLAR_H)	/** ＰＯＰＬＡＲ＿Ｈタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_h\def_v\poph_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined(ANZU_L) || defined (ANZU_V)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\def_v\anzu_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined(SAKAKI)	/* 1998/10/09 H.Yoshikawa */
	#include "\src\atlanta\sakaki\def_v\saki_int.c"
#endif
#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) /* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
	#include "\src\atlanta\hinoki\def_v\hino_int.c"
#endif
#if defined(SATSUKI2)
	#include "\src\atlanta\satsuki2\def_v\sats_int.c"
#endif
#if defined(STOCKHM2)
	#include "\src\atlanta\stockhm2\def_v\lvnd_int.c"
#endif
