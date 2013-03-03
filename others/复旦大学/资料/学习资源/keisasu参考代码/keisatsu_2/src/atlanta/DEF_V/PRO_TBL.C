/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/KOBE                                                  */
/*  ファイル名   : PRO_DEF.H                                                 */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/11/12                                                */
/*  概  要       : オプションボード機能スペック定義ファイル                  */
/*               :                                                           */
/*  修正履歴     : Atlantaへ移植 By M.Kotani 97/03/24                        */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include  "\src\atlanta\define\product.h"


#if (PRO_KEYPANEL == PANEL_POPLAR_B)
 #include "\src\atlanta\poplar_b\def_v\pro_tbl.c"
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
 #if defined(POPLAR_F)
	 #include "\src\atlanta\poplar_f\def_v\pro_tbl.c"
 #else
	 #include "\src\atlanta\poplar_l\def_v\pro_tbl.c"
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #include "\src\atlanta\anzu_l\def_v\pro_tbl.c"
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
 #include "\src\atlanta\poplar_h\def_v\pro_tbl.c"
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
 #include "\src\atlanta\sakaki\def_v\pro_tbl.c"
	/*---------------------------------------------------------------------
	** SAKAKIでは、PRO_MULTI_LINE は DISEBLE なのでこのファイルは使用しません
	** 1998/06/06 H.Yoshikawa
	*/
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI)	/* For HINOKI By O.Kimoto 1998/09/07 */
  #include "\src\atlanta\hinoki\def_v\pro_tbl.c"
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* For SATSUKI2 by Y.Kano 2003/07/11 */
 #if defined(STOCKHM2)
  #include "\src\atlanta\STOCKHM2\def_v\pro_tbl.c"
 #else
  #include "\src\atlanta\satsuki2\def_v\pro_tbl.c"
 #endif
#endif

