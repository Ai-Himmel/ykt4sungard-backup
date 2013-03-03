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

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#else
#include "\src\atlanta\scd\define\scd.h"
#endif

/* メモリ送信時主走査のソフト縮小 */
void RedLineIntRom(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE /* 縮小パターン */);

/* ＨＦＩＮＥからのモード変更による主走査のソフト縮小 */
/* void RedLine50IntRom(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE @* 縮小パターン *@);*/

/* ソフトコーデック使用 メモリエンコード */
UBYTE Mem_EncodeIntRom(struct CdcBlk_t *,					/* ソフトコーデックパラメータ */
				struct WorkBuf_t *,							/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *);						/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 Ｇ３エンコード */
void G3_EncodeIntRom(struct CdcBlk_t *,						/* ソフトコーデックパラメータ */
				struct WorkBuf_t *,							/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *);						/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 ＥＣＭエンコード */
void Ecm_EncodeIntRom(struct CdcBlk_t *,					/* ソフトコーデックパラメータ */
					struct WorkBuf_t *,						/* 符号化ラインバッファのポインタ */
					struct WorkBuf_t *);					/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 メモリデコード */
BYTE Mem_DecodeIntRom(struct CdcBlk_t *,					/* ソフトコーデックパラメータ */
			     	 struct WorkBuf_t *,					/* 符号化ラインバッファのポインタ */
			         struct WorkBuf_t *);					/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 モデムデコード */
BYTE Mdm_DecodeIntRom(struct CdcBlk_t *,					/* ソフトコーデックパラメータ */
				 struct WorkBuf_t *,						/* 符号化ラインバッファのポインタ */
				 struct WorkBuf_t *);						/* 参照ラインバッファのポインタ */

/* ソフトコーデック使用 ＥＣＭデコード */
BYTE Ecm_DecodeIntRom(struct CdcBlk_t *,					/* ソフトコーデックパラメータ */
				struct WorkBuf_t *,							/* 符号化ラインバッファのポインタ */
				struct WorkBuf_t *);						/* 参照ラインバッファのポインタ */

/* モデムバッファにＲＴＣ書き込み */
void WriteRtcToMdmIntRom(struct CdcBlk_t *);

/* ＥＣＭバッファにＲＴＣ書き込み */
void WriteRtcToEcmIntRom(struct CdcBlk_t *);

/* メモリにＲＴＣ書き込み */
UBYTE WriteRtcToMemIntRom(struct CdcBlk_t *);

/* ＲＬバッファ初期化 */
void RlBufInitIntRom(UWORD);

/* 縮小初期化 */
void SetSkipIntRom(UWORD, struct reduction_t *);

/* RUN_LENGTHデータの格納する */
void PutRLIntRom(struct WorkBuf_t *, UWORD, UBYTE);

/* RUN_LENGTHデータの取り出す */
UWORD GetRLIntRom(struct WorkBuf_t *);

/* 1ライン分のイメージをＲＬに変換する */
void Img2RlIntRom(UBYTE *, struct WorkBuf_t *, UBYTE);

/* ＥＣＭバッファライト */
void EcmWriteIntRom(struct Buf_p_t *,UBYTE ,UWORD);

/* メモリライト */
UBYTE MemWriteIntRom(struct Buf_p_t *,UBYTE,UWORD);

/* メモリリード */
WORD MemReadIntRom(struct Buf_p_t *,UBYTE);

/* イメージＲＬ変換 By Y.Suzuki 1998/01/27 */
void SCD1LineRlToImgIntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);

/* ＲＬイメージ変換 By Y.Suzuki 1998/01/27 */
void SCD1LineImgToRlIntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);

/* イメージＲＬ変換(SAKAKI) By H.Yoshikawa 1998/10/21  */
void SCD1LineRlToImg1IntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);
