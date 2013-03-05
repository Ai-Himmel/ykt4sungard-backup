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
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#else
#include "\src\atlanta\scd\define\scdirpro.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#endif

#pragma section SCDMTBL /* locate section name "CSCDMTBL" */
/* メモリ送信時主走査のソフト縮小 */
CONST void (* CONST red_line_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *) =
			(void (*)(struct CdcBlk_t *,struct WorkBuf_t *))RedLineIntRom;

/* ＨＦＩＮＥからのモード変更による主走査のソフト縮小 */
/* CONST void (* CONST red_line50_ext_tbl)() = (void (*)())RedLine50IntRom; */

/* ソフトコーデック使用 メモリエンコード */
CONST UBYTE (* CONST mem_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (UBYTE (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))Mem_EncodeIntRom;

/* ソフトコーデック使用 Ｇ３エンコード */
CONST void (* CONST g3_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (void (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))G3_EncodeIntRom;

/* ソフトコーデック使用 ＥＣＭエンコード */
CONST void (* CONST ecm_encode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (void (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))Ecm_EncodeIntRom;

/* ソフトコーデック使用 メモリデコード */
CONST BYTE (* CONST mem_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (BYTE (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))Mem_DecodeIntRom;

/* ソフトコーデック使用 モデムデコード */
CONST BYTE (* CONST mdm_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (BYTE (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))Mdm_DecodeIntRom;

/* ソフトコーデック使用 ＥＣＭデコード */
CONST BYTE (* CONST ecm_decode_ext_tbl)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *)
	= (BYTE (*)(struct CdcBlk_t *,struct WorkBuf_t *,struct WorkBuf_t *))Ecm_DecodeIntRom;

/* ＲＬバッファ初期化(メモリ送信用) */
CONST void (* CONST rlbufinit_ref_tbl)(UWORD) = (void (*)(UWORD))RlBufInitIntRom;
/*void RlBufInit(UWORD);*/

/* モデムバッファにＲＴＣ書き込み */
/*void WriteRtcToMdm(struct CdcBlk_t *);*/
CONST void (* CONST writertcmdm_ref_tbl)(struct CdcBlk_t *) = (void (*)(struct CdcBlk_t *))WriteRtcToMdmIntRom;

/* ＥＣＭバッファにＲＴＣ書き込み */
/* void WriteRtcToEcm(struct CdcBlk_t *)*/
CONST void (* CONST writertcecm_ref_tbl)(struct CdcBlk_t *) = (void (*)(struct CdcBlk_t *))WriteRtcToEcmIntRom;

/* メモリにＲＴＣ書き込み */
/*UBYTE WriteRtcToMem(struct CdcBlk_t *)*/
/*CONST UBYTE (* CONST writertcmem_ref_tbl)(struct CdcBlk_t *) =
			(void (*)(struct CdcBlk_t *))WriteRtcToMemIntRom;By Y.Suzuki 1998/02/18 */
CONST UBYTE (* CONST writertcmem_ref_tbl)(struct CdcBlk_t *) = (UBYTE (*)(struct CdcBlk_t *))WriteRtcToMemIntRom;

/* 縮小初期化 */
/*void SetSkip(UWORD, struct reduction_t *);*/
/*CONST void (* CONST setskip_ref_tbl)(UWORD, struct reduction_t *) =
			(UBYTE (*)(UWORD, struct reduction_t *))SetSkipIntRom;By Y.Suzuki 1998/02/18*/
CONST void (* CONST setskip_ref_tbl)(UWORD, struct reduction_t *) = (void (*)(UWORD, struct reduction_t *))SetSkipIntRom;

/* RUN_LENGTHデータの格納する */
/*void PutRL(struct WorkBuf_t *point,	UWORD rl,UBYTE a_color);*/
CONST void (*CONST putrl_ref_tbl)(struct WorkBuf_t *,UWORD ,UBYTE) = (void (*)(struct WorkBuf_t *,UWORD ,UBYTE))PutRLIntRom;

/* RUN_LENGTHデータの取り出す */
/*UWORD GetRL(struct WorkBuf_t *);*/
CONST UWORD (*CONST getrl_ref_tbl)(struct WorkBuf_t *) = (UWORD (*)(struct WorkBuf_t *))GetRLIntRom;

/* 1ライン分のイメージをＲＬに変換する */
/*void Img2Rl(UBYTE *, struct WorkBuf_t *, UBYTE);*/
CONST void (*CONST img2rl_ref_tbl)(UBYTE *,struct WorkBuf_t *,UBYTE) =
			(void (*)(UBYTE *,struct WorkBuf_t *,UBYTE))Img2RlIntRom;

/* ＥＣＭバッファライト */
/*void  EcmWrite(struct Buf_p_t *,UBYTE,UWORD);*/
CONST void (*CONST ecmwrite_ref_tbl)(struct Buf_p_t *,UBYTE,UWORD) =
			(void (*)(struct Buf_p_t *,UBYTE,UWORD))EcmWriteIntRom;

/* メモリリード */
/*WORD MemRead(struct Buf_p_t *,UBYTE);*/
CONST WORD (*CONST memread_ref_tbl)(struct Buf_p_t *,UBYTE) = (WORD (*)(struct Buf_p_t *,UBYTE))MemReadIntRom;

/* メモリライト */
/*UBYTE MemWrite(struct Buf_p_t *,UBYTE,UWORD);*/
CONST UBYTE (*CONST memwrite_ref_tbl)(struct Buf_p_t *,UBYTE,UWORD) =
			(UBYTE (*)(struct Buf_p_t *,UBYTE,UWORD))MemWriteIntRom;

/* イメージＲＬ変換 */
/*void SCD1LineRlToImgIntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD)*/
CONST void (*CONST scd_rl_to_img_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD) =
			(void (*)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD))SCD1LineRlToImgIntRom;

/* ＲＬイメージ変換 */
/*CONST void SCD1LineImgToRlIntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD)*/
CONST void (*CONST scd_img_to_rl_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD) =
			(void (*)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD))SCD1LineImgToRlIntRom;

/* イメージＲＬ変換(SAKAKIで使用）1998/10/21 H.Yoshikawa */
/*void SCD1LineRlToImg1IntRom(struct WorkBuf_t *,struct CdcBlk_t *,UWORD)*/
CONST void (*CONST scd_rl_to_img1_tbl)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD) =
			(void (*)(struct WorkBuf_t *,struct CdcBlk_t *,UWORD))SCD1LineRlToImg1IntRom;

#pragma section /* locate section name "CSCDMTBL" */


#if (PRO_CPU_VERSION == SH7043_R)
/*********************************************/
/* 外ＲＯＭに配置するＲＬバッファのポインタ  */
/*********************************************/
#pragma section RLBUFP /* locate section name "CRLBUFP" */
CONST UBYTE (*CONST RL_Buffer_pc) = &RL_Buffer[0];
#pragma section

/***************************************/
/* 内蔵ＲＡＭに配置するポインタの写像  */
/***************************************/
#pragma section RLBUFPIMG /* locate section name "BRLBUFPIMG" */
UBYTE *RL_Buffer_p;
#pragma section
#endif
