/************************************************************************
*	System		: POPLAR
*	File Name	: SCD_TBL.H
*	Author		: Y.Suzuki
*	Date		: 1997/3/7
*	Description	:ソフトコーデックテーブル外部参照用
*	Maintenance	:SCD_DATA.H から分離
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
/*-------------------------------*/
/*  ＭＨエンコードテーブル（白） */
/*-------------------------------*/
extern	MH_EC_TABLE_t	MH_EC_WhiteTableMain[];	/* Internal */

/*-------------------------------*/
/*  ＭＨエンコードテーブル（黒） */
/*-------------------------------*/
extern	MH_EC_TABLE_t	MH_EC_BlackTableMain[];	/* Internal */

/*-------------------------------*/
/* ＭＲエンコードテーブル        */
/*-------------------------------*/
extern	MR_EC_TABLE_t	MR_EC_TableMain[];	/* Internal */

/*------------------------------*/
/* ＭＨデコードテーブル１（白） */
/* -----------------------------*/
extern	MH_DC_TABLE1_t	MH_DC_WhiteTableMain[];	/* Internal */

/*------------------------------*/
/* ＭＨデコードテーブル１（黒） */
/* -----------------------------*/
extern	MH_DC_TABLE1_t	MH_DC_BlackTableMain[];	/* Internal */

/*------------------------------*/
/* ＭＨデコードテーブル２(共通) */
/*------------------------------*/
extern	MH_DC_TABLE2_t	MH_DC_TableSub[];	/* Internal */

/*------------------------------*/
/* ＭＲデコードテーブル         */
/*------------------------------*/
extern	MR_DC_TABLE_t	MR_DC_TableMain[];	/* Internal */

#if (PRO_CPU_VERSION == SH7043_R)
/* 新ﾏｽｸ変更 追加 ﾎﾟｲﾝﾀの写像 */
extern UDWORD SCD_MEM_BLOCK_SIZE_I;
#endif
