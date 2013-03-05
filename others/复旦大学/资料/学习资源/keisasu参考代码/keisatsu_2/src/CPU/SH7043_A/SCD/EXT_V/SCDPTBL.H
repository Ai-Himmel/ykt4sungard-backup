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
#include "\src\cpu\sh7043_a\scd\define\scdirpro.h"
#else
#include "\src\atlanta\scd\define\scdirpro.h"
#endif

/* #pragma section SCDPRGTBL locate section name "CSCDPRGTBL" */
/* メモリ送信時主走査のソフト縮小 */
extern CONST void (* CONST red_line_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE);

/* ＨＦＩＮＥからのモード変更による主走査のソフト縮小 */
/*extern CONST void (* CONST red_line50_ext_tbl)(void);*/

/* ソフトコーデック使用 メモリエンコード */
extern CONST UBYTE (* CONST mem_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ソフトコーデック使用 Ｇ３エンコード */
extern CONST void (* CONST g3_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ソフトコーデック使用 ＥＣＭエンコード */
extern CONST void (* CONST ecm_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ソフトコーデック使用 メモリデコード */
extern CONST BYTE (* CONST mem_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ソフトコーデック使用 モデムデコード */
extern CONST BYTE (* CONST mdm_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ソフトコーデック使用 ＥＣＭデコード */
extern CONST BYTE (* CONST ecm_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *);

/* ＲＬバッファ初期化(メモリ送信用) */
extern CONST void (* CONST rlbufinit_ref_tbl)(UWORD);

/* モデムバッファにＲＴＣ書き込み */
extern CONST void (* CONST writertcmdm_ref_tbl)(struct CdcBlk_t *);

/* ＥＣＭバッファにＲＴＣ書き込み */
extern CONST void (* CONST writertcecm_ref_tbl)(struct CdcBlk_t *);

/* メモリにＲＴＣ書き込み */
extern CONST UBYTE (* CONST writertcmem_ref_tbl)(struct CdcBlk_t *);

/* 縮小初期化 */
extern CONST void (* CONST setskip_ref_tbl)(UWORD, struct reduction_t *);

/* RUN_LENGTHデータの格納する */
extern CONST void (*CONST putrl_ref_tbl)(struct WorkBuf_t *,UWORD ,UBYTE);

/* RUN_LENGTHデータの取り出す */
extern CONST UWORD (*CONST getrl_ref_tbl)(struct WorkBuf_t *);

/* 1ライン分のイメージをＲＬに変換する */
extern CONST void (*CONST img2rl_ref_tbl)(UBYTE *,struct WorkBuf_t *,UBYTE);

/* ＥＣＭバッファライト */
extern CONST void (*CONST ecmwrite_ref_tbl)(struct Buf_p_t *,UBYTE,UWORD);

/* メモリリード */
extern CONST WORD (*CONST memread_ref_tbl)(struct Buf_p_t *,UBYTE);

/* メモリライト */
extern CONST UBYTE (*CONST memwrite_ref_tbl)(struct Buf_p_t *,UBYTE,UWORD);

/* #if (PRO_CIPHER == ENABLE) */
/* イメージＲＬ変換 */
extern CONST void (*CONST scd_rl_to_img_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);
/* ＲＬイメージ変換 */
extern CONST void (*CONST scd_img_to_rl_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);
/* イメージＲＬ変換(SAKAKI) */
extern CONST void (*CONST scd_rl_to_img1_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);
/* #endif *//* PRO_CIPHER */
/* #pragma section locate section name "CSCDPRGTBL" */
