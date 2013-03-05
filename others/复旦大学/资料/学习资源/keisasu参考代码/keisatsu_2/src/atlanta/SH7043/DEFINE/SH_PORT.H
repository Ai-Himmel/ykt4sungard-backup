/*--------------------------------------------------------------------*/
/* プロジェクト : POPLAR/ANZU_L										  */
/* ファイル名	: SH_port.h											  */
/* 作成者		: 野瀬敏弘											  */
/* 日  付		: 1996/10/15										  */
/* 概  要		: I/Oポート定義										  */
/* 修正履歴		:													  */
/*--------------------------------------------------------------------*/
/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#else

#ifndef SH_PORT_H
	#define	SH_PORT_H	1

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\define\popbport.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました 1999/05/13 by T.Soneoka */
	#include "\src\atlanta\poplr_bn\define\popbport.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_L)	/** ＰＯＰＬＡＲ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_l\define\poplport.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_N)	/** ＰＯＰＬＡＲ＿Ｎタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_n\define\popnport.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_H)	/** ＰＯＰＬＡＲ＿Ｈタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_h\define\pophport.h"	/* Add By O.Kimoto 1997/06/13 */
#endif
#if defined(ANZU_L)	/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzuport.h"	/* By M.Kotani 97/06/10 */
#endif
#if defined(ANZU_V)	/** ＡＮＺＵ＿Ｖタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzuport.h"	/* By M.Kotani 98/01/08 */
#endif
#if defined(SAKAKI)	/** ＳＡＫＡＫＩタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\sakaki\define\sakiport.h"	/* By H.Yoshikawa 1998/05/07 */
#endif
#if defined(POPLAR_F)	/** Ｌ４００後継タイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_f\define\popfport.h"
#endif

#endif

#endif
