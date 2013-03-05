/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L                                               */
/*モジュ-ル名 : SH_SYS.H                                                    */
/*作成者名 	  : 野瀬                                                        */
/*日  付   	  : 96.10.11                                                    */
/*概  要   	  : SH7043                                                      */
/*  		    割込みコントローラ                  			            */
/*  		    バスステートコントローラ                  			        */
/*  		    内蔵ＤＭＡＣ                                                */
/*              外付けＤＭＡＣ                                              */
/*修正履歴 :                                                                */
/*--------------------------------------------------------------------------*/
/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\sh_sys.h"
#else

#ifndef	SH_SYS_H
	#define	SH_SYS_H	1

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\define\popb_sys.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました 1999/05/13 by T.Soneoka */
	#include "\src\atlanta\poplr_bn\define\popb_sys.h"
#endif
#if defined(POPLAR_L)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_l\define\popl_sys.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_N)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_n\define\popn_sys.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_H)	/** ＰＯＰＬＡＲ＿Ｈタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_h\define\poph_sys.h"	/* Add By O.Kimoto 1997/06/13 */
#endif
#if defined(ANZU_L)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzu_sys.h"	/* By M.Kotani 97/06/10 */
#endif
#if defined(ANZU_V)		/** ＡＮＺＵ＿Ｖタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_v\define\anzv_sys.h"	/* By M.Kotani 98/01/08 */
#endif
#if defined(SAKAKI)		/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\sakaki\define\saki_sys.h"	/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(POPLAR_F)	/** Ｌ４００後継タイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_f\define\popf_sys.h"
#endif

#endif

#endif
