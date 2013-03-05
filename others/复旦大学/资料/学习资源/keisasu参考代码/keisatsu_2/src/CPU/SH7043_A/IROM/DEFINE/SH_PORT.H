/*--------------------------------------------------------------------*/
/* プロジェクト : POPLAR/ANZU_L										  */
/* ファイル名	: SH_port.h											  */
/* 作成者		: 野瀬敏弘											  */
/* 日  付		: 1996/10/15										  */
/* 概  要		: I/Oポート定義										  */
/* 修正履歴		:													  */
/*--------------------------------------------------------------------*/
#ifndef SH_PORT2_H
	#define	SH_PORT2_H	1

#if defined(POPLAR_B)	/** ＰＯＰＬＡＲ＿Ｂタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplar_b\define\popbport.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLR_BN)	/** ＰＯＰＬＡＲ＿ＢＮタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\poplr_bn\define\popbport.h"
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
	#include "\src\atlanta\sakaki\define\sakiport.h"	/* By H.Yoshikawa 1998/10/09 */
#endif
#if defined(HINOKI)	|| defined(HINOKI2) || defined(HINOKI3) || defined(KEISATSU) /* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
	#include "\src\atlanta\hinoki\define\hinoport.h"
#endif
#if defined(SATSUKI2)
	#include "\src\atlanta\satsuki2\define\satsport.h"
#endif
#if defined(STOCKHM2)
	#include "\src\atlanta\stockhm2\define\lvndport.h"
#endif

#endif
