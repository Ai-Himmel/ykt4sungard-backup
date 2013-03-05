/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                              */
/*  ファイル名   : DEFV_STK.C                                                 */
/*  作成者       : 野瀬                                                       */
/*  日  付       : 96.10.12                                                   */
/*  概  要       : スタック領域の確保                                         */
/*  コメント     : スタックサイズは合計１６Ｋバイトとっています。             */
/*                 サイズを変更する場合、ロケートアドレス・初期化開始アドレス */
/*                 も変更して下さい。                                         */
/*  修正履歴     :                                                            */
/*----------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\defv_stk.c"
#else
#include "\src\atlanta\sh7043\define\def_mon.h"

#pragma section STACK /* ロケート時のセクション名 "BSTACK" */
	UDWORD large_stack_area[LARGE_STACK_MAX][LARGE_STACK/4];
	UDWORD small_stack_area[SMALL_STACK_MAX][SMALL_STACK/4];
#pragma section

#endif
