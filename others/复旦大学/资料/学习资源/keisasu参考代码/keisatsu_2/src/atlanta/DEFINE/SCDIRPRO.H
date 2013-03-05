/************************************************************************
*	System		: POPLAR
*	File Name	: SCDIRPRO.C
*	Author		: Y.Suzuki
*	Date		: 1997/3/7
*	Description	:外部ＲＯＭから内蔵ＲＯＭ内のモジュールを参照するため
*				外部ＲＯＭから固定アドレスでコールするため
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\scd\define\scd.h"

/* メモリ送信時主走査のソフト縮小 */
void RedLineIntRom(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE /* 縮小パターン */);

/* ＨＦＩＮＥからのモード変更による主走査のソフト縮小 */
void RedLine50_IntRom(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE /* 縮小パターン */);

/* ソフトコーデック使用 メモリエンコード */
UBYTE Mem_EncodeIntRom(struct CdcBlk_t *enc,				/* ソフトコーデックパラメータ */
				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 Ｇ３エンコード */
void G3_EncodeIntRom(struct CdcBlk_t *enc,					/* ソフトコーデックパラメータ */
				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 ＥＣＭエンコード */
void Ecm_EncodeIntRom(struct CdcBlk_t *enc,					/* ソフトコーデックパラメータ */
					struct WorkBuf_t *a_buf,			/* 符号化ラインバッファのポインタ */
					struct WorkBuf_t *b_buf);			/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 メモリデコード */
BYTE Mem_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
			     	 struct WorkBuf_t *a_buf,			/* 符号化ラインバッファのポインタ */
			         struct WorkBuf_t *b_buf);		/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 モデムデコード */
BYTE Mdm_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
				 struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
				 struct WorkBuf_t *b_buf);			/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 ＥＣＭデコード */
BYTE Ecm_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */

