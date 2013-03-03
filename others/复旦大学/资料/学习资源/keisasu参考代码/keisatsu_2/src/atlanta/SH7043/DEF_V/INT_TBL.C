/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : INT_TBL.C                                                */
/*  作成者       : 小谷正樹                                                 */
/*  日  付       : 97.06.13                                                 */
/*  概  要       : 機種共通割り込み処理関数                                 */
/*               : 先頭アドレステーブル                                     */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\int_tbl.c"
#else

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
#if defined(ANZU_L)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\def_v\anzu_int.c"	/* By M.Kotani 97/06/16 */
#endif
#if defined (ANZU_V)		/** ＡＮＺＵ＿Ｖタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_v\def_v\anzv_int.c"	/* By Y.Tanimoto 98/03/10 */
#endif
#if defined (SAKAKI)		/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\sakaki\def_v\saki_int.c"	/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(POPLAR_F)	/** Ｌ４００後継タイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_f\def_v\popf_int.c"
#endif

#endif

