/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TBL.H
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票関係固定ﾃﾞｰﾀ
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_TBL_H
	#define	LST_TBL_H	1

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"

#if (PRO_MODEM == R288F)
	#if defined(HINOKI3)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
	#endif
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#endif

extern CONST UBYTE Disp_IndexTable[];
extern CONST UBYTE Disp_FATArea[];
extern CONST UBYTE Disp_TopEmptyBlock[];
extern CONST UBYTE Disp_TotalStoreBlockCounter[];
extern CONST UBYTE Disp_EndBlock[];
#if ( PRO_MAKER == FX )
extern CONST UBYTE Disp_MultiProgramOpenIndexNo[];	/*FXのみ*/
#endif

/***********************************************************************
*	半角フォント
************************************************************************/
extern CONST UBYTE ByteFont[256][16];
extern CONST UBYTE IBM_FONT[];
#if (0)
extern CONST BYTE WEEKS[];
extern CONST BYTE ASC_1[];
extern CONST BYTE ASC_2[];
extern CONST BYTE ASC_3[];
extern CONST BYTE ASC_4[];
extern CONST BYTE ASC_5[];
extern CONST BYTE ASC_6[];
extern CONST BYTE ASC_7[];
#endif

/***********************************************************************
*	T30モニタデータ
************************************************************************/
extern CONST UBYTE P_Frm_N_Name[LST_FRAME_N_MAX][8];	/*通常ﾌﾚｰﾑ ﾒｲ*/
extern CONST UBYTE P_Frm_N_Cd[];						/*通常ﾌﾚｰﾑ ｺｰﾄﾞ*/
extern CONST UBYTE P_Frm_N_Msk[];						/*ﾌﾚｰﾑﾏｽｸ*/

#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/* 1996/12/17 Y.Murata *//* 1998/09/17 By M.Kuwahara */
extern CONST UBYTE P_Frm_S_Name[6][4];
#else
extern CONST UBYTE P_Frm_S_Name[2][4];
#endif
#if ( (PRO_MULTI_LINE == ENABLE)	|| (PRO_MODEM == R288F)) /* 1996/12/17 Y.Murata */ /* R288F is added by H.Kubo 1998/02/17 */
extern CONST UBYTE P_Sym_Rate[6][5];
extern CONST UBYTE P_Data_Rate[9][4];
extern CONST UBYTE MonitorHead[66];
 #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) /* For DEBUG by O.Kimoto 1998/12/01 */ /* HINOKI2 2001/11/13 T.Takagi */
extern CONST UBYTE T30Message[MODE_NULL+1][7];
 #else
extern CONST UBYTE T30Message[12][7];
 #endif
#endif

/***********************************************************************
*	網掛けフォント
************************************************************************/
extern CONST UBYTE PrintMeshData[];

/***********************************************************************
*	フォントを横に２倍するためのデータ
************************************************************************/
extern CONST UBYTE TwiceData[16];

/***********************************************************************
* 機器設定リスト用定義 	　97/06/27	by M.Kuwahara
***********************************************************************/
extern CONST UBYTE List_ParameterTable[];
extern CONST UBYTE List_ParameterTable_Category2[];	/* F-101専用 リストテーブル 1997/12/25 Y.Matsukuma */

/***********************************************************************
* 消耗品発注票モデル名変換用定義 	　97/09/19	by M.Kuwahara
***********************************************************************/
extern CONST struct LST_ModelChange_t	LST_ModelChangeTable[];

#if (PRO_SGP_TEST_ROM == ENABLE)
/****************************************************
 ** シンガポール市場調査レポート By S. Wang 98/07/25
 ****************************************************/
extern CONST UBYTE SgpReportHead[80];
extern CONST UBYTE SgpReportMaker[15][12];
#endif

 #if defined(US1)
/***********************************************************************
* 消耗品発注票発注先データ			orderbythonda1998/11/11
***********************************************************************/
extern CONST UBYTE DistributorName[];
extern CONST UBYTE ToCompanyFaxNumber[];
extern CONST UBYTE ToCompanyTelNumber[];
 #endif

#endif
