/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : cpu_def.h                                                 */
/*  作成者       : 小谷正樹                                                  */
/*  日  付       : 97.06.10                                                  */
/*  概  要       : SH7043 機種別CPU初期設定定義ファイル                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\cpu_def.h"
#else

#ifndef	CPU_DEF_H
	#define	CPU_DEF_H	1

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\define\popb_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました 1999/05/13 */
	#include "\src\atlanta\poplr_bn\define\popb_cpu.h"
#endif
#if defined(POPLAR_L)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_l\define\popl_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_N)	/** ＰＯＰＬＡＲ＿Ｎタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_n\define\popn_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_H)	/** ＰＯＰＬＡＲ＿Ｈタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_h\define\poph_cpu.h"	/* Add By O.Kimoto 1997/06/13 */
#endif
#if defined(ANZU_L)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzu_cpu.h"	/* By M.Kotani 97/06/10 */
#endif
#if defined(ANZU_V)		/** ＡＮＺＵ＿Ｖタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzu_cpu.h"	/* By M.Kotani 98/01/08 */
#endif
#if defined(SAKAKI)		/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\sakaki\define\saki_cpu.h"	/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(POPLAR_F)	/** Ｌ４００後継タイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_f\define\popf_cpu.h"
#endif

#endif

#endif
