/*--------------------------------------------------------------------*/
/* プロジェクト : POPLAR/ANZU_L	                                      */
/* ファイル名   : ini_tbl.c                                           */
/* 作成者       : T.Nose                                              */
/* 日  付       : 1997/08/18                                          */
/* 概  要       : 各モデル共通ファイル                                */
/* 参照			:									                  */
/* 修正履歴     : 各モデル別に実ファイルをインクルードします。        */
/*--------------------------------------------------------------------*/

#if defined (POPLAR_B)
 #include "\src\atlanta\poplar_b\def_v\ini_tbl.c"
#endif
#if defined (POPLR_BN)
 #include "\src\atlanta\poplr_bn\def_v\ini_tbl.c"
#endif
#if defined (POPLAR_L)
 #include "\src\atlanta\poplar_l\def_v\ini_tbl.c"
#endif
#if defined (POPLAR_N)
 #include "\src\atlanta\poplar_n\def_v\ini_tbl.c"
#endif
#if defined (POPLAR_H)
 #include "\src\atlanta\poplar_h\def_v\ini_tbl.c"
#endif
#if defined (ANZU_L)
 #include "\src\atlanta\anzu_l\def_v\ini_tbl.c"
#endif
#if defined (ANZU_V)
/* ANZU_VをInternetFAXﾓﾃﾞﾙに使用します。　by Y.Tanimoto 1998/03/13
** #include "\src\atlanta\anzu_l\def_v\ini_tbl.c" 
*/
 #include "\src\atlanta\anzu_v\def_v\ini_tbl.c"
#endif

#if defined (SAKAKI)
 #include "\src\atlanta\sakaki\def_v\ini_tbl.c"
#endif

#if defined(HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) /* HINOKI2 2001/11/13 T.Takagi */
/* HINOKI By O.Kimoto 1998/09/04 */
 #include "\src\atlanta\hinoki\def_v\ini_tbl.c"
#endif

#if defined(SATSUKI2)
/* HINOKI By O.Kimoto 1998/09/04 */
 #include "\src\atlanta\satsuki2\def_v\ini_tbl.c"
#endif

#if defined(STOCKHM2)
 #include "\src\atlanta\STOCKHM2\def_v\ini_tbl.c"
#endif

#if defined (POPLAR_F)
 #include "\src\atlanta\poplar_f\def_v\ini_tbl.c"
#endif

