/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\kobe\anzu\scdc\define\scdcpro.h */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdblk.h"
#include "\src\atlanta\define\mem_def.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdptbl.h"		/*	By Y.Suzuki 1997/03/18	*/
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\scdptbl.h"		/*	By Y.Suzuki 1997/03/18	*/
#endif


/*----------------------------------------------*/
/*	ソフトコーデック関連の関数プロトタイプ宣言	*/
/*							95/11/27 Y.Suzuki	*/
/*----------------------------------------------*/
/*--------------------------*/
/*	メモリ送信 MDMSFGTX.C	*/
/*--------------------------*/
UBYTE SCDC_G3_MemTx(void);
void SetFill(struct CdcBlk_t *);
/*void GoSoftCodec(void);** デバック用サブルーチン */

/*-----------------------*/
/* Modules of scd_redc.c */
/*-----------------------*/
/* 線密度モードパラメータ変換 */
UBYTE ModePara(UBYTE);

/* モード変更による縮小時、副走査スキップモード獲得 */
UBYTE GetModeSkip(UBYTE,UBYTE);

/* 縮小パターンセット */
UBYTE SetReduce(UBYTE src_size, UBYTE dst_size);

/* メモリ送信時主走査のソフト縮小 */
/* void RedLine(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE @* 縮小パターン *@);*/
#define	RedLine	(*red_line_ext_tbl)

/* ＨＦＩＮＥからのモード変更による主走査のソフト縮小 */
/*void RedLine50(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE @* 縮小パターン *@);*/
#define	RedLine50	(*red_line50_ext_tbl)

/* Ｒ１２からの縮小 */
void RedLineR12ToR8(struct CdcBlk_t *,struct WorkBuf_t *,UBYTE);

/* 縮小初期化 */
/* void SetSkip(UWORD, struct reduction_t *);*/
#define	SetSkip	(*setskip_ref_tbl)

/* 送信原稿サイズ縮小にて生ずる副走査の間引き処理 */
UBYTE Skip(struct reduction_t *);

/* メンテナンスＳＷーＦをＳＣＤ用ＳＷにコピーする  */
void CopyFromMantSwF(void);

/* ＳＣＤ用ＳＷをメンテナンスＳＷーＦへコピーする  */
void CopyToMantSwF(void);

/*-----------------------*/
/* Modules of scdrxpix.c */
/*-----------------------*/
/* ＰＩＸ受信 */
UBYTE	SCDC_RxPix(UBYTE,UBYTE);

/* ＥＣＭ受信 */
UBYTE	SCDC_EcmRx(void);

/* ＥＣＭ受信コントロールタスク */
void		SCDC_RxEcmControlTask(void);

/* 受信タスク強制終了 */
void		SCDC_BreakRxTask(void);

UBYTE CRC_CheckRisc(UBYTE *,	/*	フレームポインタ	*/
					UWORD  ,	/*	純フレームレングス	*/
					UWORD);		/*	ＦＣＳ情報	*/


/*----------------------*/
/* Modules of scdtx.c */
/*----------------------*/
/* ソフトコーデックＥＣＭバッファへ符号化タスク */
void SCDC_MTxCodeConvertTask(void);

void SCD_TxTTI_OnScanTx(void);
void SCD_CheckDirectTx(void);
void WriteRtcToEcmByte(struct CdcBlk_t *);/*By Y.Suzuki 1998/05/21*/
/*-----------------------*/
/* Modules of scdtxdbg.c */
/*-----------------------*/
/* デバック用メインルーチン */
void GoSoftCodec(void);

/*----------------------------*/
/*	キャラクタ送信 MDMCHTX.C  */
/*----------------------------*/
/* ＥＣＭキャラクタ送信 */
void SF_ECM_CharTx(struct CdcBlk_t *,
				   struct WorkBuf_t *,
				   struct WorkBuf_t *);

/*void SCD_CTxCodeConvertPageTask(void);*/

/*-----------------------*/
/* Modules of scdmgrx.c */
/*-----------------------*/
/* Ｇ３メモリ受信 */
UBYTE SCDC_G3_MemRx(void);

/*-----------------------*/
/* Modules of scdmerx.c */
/*-----------------------*/
/* ＥＣＭメモリ受信 */
void SCDC_EcmDecodeTask(void);
void SCD_CheckDirectRx(void);

/*-----------------------*/
/* Modules of scdtxpix.c */
/*-----------------------*/
/* ソフトコーデック使用 送信ＰＩＸ */
UBYTE	SCDC_TxPix(UBYTE,UBYTE);

/* ソフトコーデック使用ＥＣＭ送信 */
UBYTE SCDC_EcmTx(void);

/* 送信コントロールタスク強制終了処理 */
void	SCDC_BreakTxTask(void);

/*-----------------------*/
/* Modules of encode.c   */
/*-----------------------*/
/* ソフトコーデック使用 メモリエンコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//UBYTE Mem_EncodeIntRom(struct CdcBlk_t *enc,				/* ソフトコーデックパラメータ */
//				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
//				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */
#endif
#define Mem_Encode	(*mem_encode_ext_tbl)

/* ＭＨデータの書き込み（メモリエンコード用） */
UBYTE Mem_RLToMHWrite(UWORD rl,						/* ＭＨエンコードのRUNLENGTH */
					struct CdcBlk_t *point,			/* ソフトコーデックパラメータ */
					UBYTE a_color);					/* ＭＨエンコードのCOLOR */
/* ＥＯＬデータの書き込み （メモリエンコード用）*/
UBYTE Mem_EOLWrite(UWORD eol,						/* ＥＯＬモード*/
					struct CdcBlk_t *point,			/* ソフトコーデックパラメータ */
					UBYTE a_color);					/* ＭＨエンコードのCOLOR */
/* ＭＲデータの書き込み （メモリエンコード用）*/
UBYTE Mem_MRDataWrite(UBYTE code,					/* ＭＲモード*/
					struct CdcBlk_t *point);			/* ソフトコーデックパラメータ */

/* ソフトコーデック使用 Ｇ３エンコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//void G3_EncodeIntRom(struct CdcBlk_t *enc,					/* ソフトコーデックパラメータ */
//				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
//				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */
#endif
#define G3_Encode	(*g3_encode_ext_tbl)

/* ＭＨデータの書き込み（Ｇ３エンコード用） */
void G3_RLToMHWrite(UWORD rl,						/* ＭＨエンコードのRUNLENGTH */
					struct CdcBlk_t *point,	        /* ソフトコーデックパラメータ */
					UBYTE a_color);				    /* ＭＨエンコードのCOLOR */
/* ＥＯＬデータの書き込み （Ｇ３エンコード用）*/
void G3_EOLWrite(UWORD eol,							/* ＥＯＬモード*/
				struct CdcBlk_t *point,				/* ソフトコーデックパラメータ */
				UBYTE a_color);						/* ＭＨエンコードのCOLOR */
/* ＭＲデータの書き込み （Ｇ３エンコード用）*/
void G3_MRDataWrite(UBYTE code,				/* ＭＲモード*/
					struct CdcBlk_t *point);			/* ソフトコーデックパラメータ */
/* ソフトコーデック使用 ＥＣＭエンコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//void Ecm_EncodeIntRom(struct CdcBlk_t *enc,					/* ソフトコーデックパラメータ */
//					struct WorkBuf_t *a_buf,			/* 符号化ラインバッファのポインタ */
//					struct WorkBuf_t *b_buf);			/* 参照ラインバッファのポインタ */
#endif
#define Ecm_Encode	(*ecm_encode_ext_tbl)

/* ＭＨデータの書き込み（ＥＣＭエンコード用） */
void Ecm_RLToMHWrite(UWORD rl,						/* ＭＨエンコードのRUNLENGTH */
					 struct CdcBlk_t *point,			/* ソフトコーデックパラメータ */
					 UBYTE a_color);				/* ＭＨエンコードのCOLOR */
/* ＥＯＬデータの書き込み （ＥＣＭエンコード用）*/
void Ecm_EOLWrite(UWORD eol,						/* ＥＯＬモード*/
				struct CdcBlk_t *point,				/* ソフトコーデックパラメータ */
				UBYTE a_color);						/* ＭＨエンコードのCOLOR */
/* ＭＲデータの書き込み （ＥＣＭエンコード用）*/
void Ecm_MRDataWrite(UBYTE code,					/* ＭＲモード*/
                         struct CdcBlk_t *point);		/* ソフトコーデックパラメータ */
/* RUN_LENGTHデータの取り出す */
/*UWORD GetRL(struct WorkBuf_t *gp);*/
#define GetRL	(*getrl_ref_tbl)

/*-----------------------*/
/* Modules of decode.c   */
/*-----------------------*/
/* ソフトコーデック使用 メモリデコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//BYTE Mem_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
//			     	 struct WorkBuf_t *a_buf,			/* 符号化ラインバッファのポインタ */
//			         struct WorkBuf_t *b_buf);		/* 参照ラインバッファのポインタ */
#endif
#define Mem_Decode	(*mem_decode_ext_tbl)

/* ＭＨデータをRUNLENGTHに展開（メモリデコード用） */
WORD Mem_MHDataToRL(struct CdcBlk_t *mp,				/* ソフトコーデックパラメータ */
                         UBYTE a_color);			/* ＭＨデコードのCOLOR */

/* ＭＲデータをＭＲモードに展開（メモリデコード用） */
BYTE  Mem_MRDataToMode(struct CdcBlk_t *mrp);			/* ソフトコーデックパラメータ */

/* ＥＯＬ検索処理 （メモリデコード用）*/
UBYTE  Mem_DetectEOL(struct CdcBlk_t *dp);			/* ソフトコーデックパラメータ */

/* RTC/EOLB DETECT */
UBYTE Mem_DetectRTC(struct CdcBlk_t *dp);

/* ソフトコーデック使用 モデムデコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//BYTE Mdm_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
//				 struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
//				 struct WorkBuf_t *b_buf);			/* 参照ラインバッファのポインタ */
#endif
#define Mdm_Decode	(*mdm_decode_ext_tbl)

/* ＭＨデータをRUNLENGTHに展開（モデムデコード用） */
WORD Mdm_MHDataToRL(struct CdcBlk_t *mp,				/* ソフトコーデックパラメータ */
					 UBYTE a_color);				/* ＭＨデコードのCOLOR */

/* ＭＲデータをＭＲモードに展開（モデムデコード用） */
BYTE  Mdm_MRDataToMode(struct CdcBlk_t *mrp);			/* ソフトコーデックパラメータ */

/* ＥＯＬ検索処理 （モデムデコード用）*/
UBYTE  Mdm_DetectEOL(struct CdcBlk_t *dp);			/* ソフトコーデックパラメータ */

/* RTC/EOLB DETECT */
UBYTE Mdm_DetectRTC(struct CdcBlk_t *dp);

/* ソフトコーデック使用 ＥＣＭデコード */
#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//BYTE Ecm_DecodeIntRom(struct CdcBlk_t *dec,					/* ソフトコーデックパラメータ */
//				struct WorkBuf_t *a_buf,				/* 符号化ラインバッファのポインタ */
//				struct WorkBuf_t *b_buf);				/* 参照ラインバッファのポインタ */
#endif
#define Ecm_Decode (*ecm_decode_ext_tbl)

/* ＭＨデータをRUNLENGTHに展開（ＥＣＭデコード用） */
WORD Ecm_MHDataToRL(struct CdcBlk_t *mp,				/* ソフトコーデックパラメータ */
					UBYTE a_color);					/* ＭＨデコードのCOLOR */

/* ＭＲデータをＭＲモードに展開（ＥＣＭデコード用） */
BYTE  Ecm_MRDataToMode(struct CdcBlk_t *mrp);			/* ソフトコーデックパラメータ */

/* ＥＯＬ検索処理 （ＥＣＭデコード用）*/
UBYTE  Ecm_DetectEOL(struct CdcBlk_t *dp);			/* ソフトコーデックパラメータ */

/* RTC/EOLB DETECT */
UBYTE Ecm_DetectRTC(struct CdcBlk_t *dp);

/* ＥＯＬ検索処理 (SUB）*/
WORD  ScdcCheckEOL(UBYTE decdata,					/* １バイトＭＨデコードデータ　*/
					UBYTE *ptnp);					/* 前回検出の連続０の個数 */

/* RUN_LENGTHデータの格納する */
void PutRL(struct WorkBuf_t *point,UWORD rl,UBYTE a_color);
#define PutRL	(*putrl_ref_tbl)

/* 連続Ｖ０RUN_LENGTHデータの格納する */
void PutV0(struct ScdcWorkData_t *point,
			struct WorkBuf_t *ap,
			struct WorkBuf_t *bp);

/*-----------------------*/
/* Modules of scd_cntl.c */
/*-----------------------*/
/* ソフトエンコードで使用するローカル変数の初期化 */
void SoftEncodeInitial(struct CdcBlk_t *);

/* ソフトデコードで使用するローカル変数の初期化 */
void SoftDecodeInitial(struct CdcBlk_t *);

/* ＲＬバッファ初期化(メモリ送信用) */
/* void EncRlBufInit(UWORD);*/

/* ＲＬバッファ初期化(メモリ受信用) */
/* void DecRlBufInit(UWORD);*/

/* ＲＬバッファ初期化 */
/* void RlBufInit(UWORD);*/
#define RlBufInit	(*rlbufinit_ref_tbl)

/* 1ライン分のイメージをＲＬに変換する */
/*void Img2Rl(UBYTE *, struct WorkBuf_t *, UBYTE);* A4_SIZE or B4_SIZE or A3_SIZE */
#define Img2Rl	(*img2rl_ref_tbl)

void SCD_MemoryMove(UBYTE	*,UBYTE	*,UWORD);

/* モデムライト */
void MdmWrite(struct Buf_p_t *,
				UBYTE,	/* 書き込みビット数 */
				UWORD			/* 書き込みデータ ２バイト*/);

/* モデムリード */
WORD MdmRead(struct Buf_p_t *,
				UBYTE	/* 読み出しビット数最大１６ビット */);

/* メモリライト */
/*UBYTE MemWrite(struct Buf_p_t *,UBYTE,UWORD);*/
#define MemWrite	(*memwrite_ref_tbl)

/* メモリリード */
/*WORD MemRead(struct Buf_p_t *,UBYTE)*/
#define MemRead	(*memread_ref_tbl)

/* ＥＣＭバッファライト */
/*void  EcmWrite(struct Buf_p_t *,UBYTE,UWORD);*/
#define EcmWrite	(*ecmwrite_ref_tbl)

/* ＥＣＭバッファリード */
WORD  EcmRead(struct Buf_p_t *,UBYTE	);

/* モデムバッファにＲＴＣ書き込み */
/* void WriteRtcToMdm(struct CdcBlk_t *);*/
#define WriteRtcToMdm	(*writertcmdm_ref_tbl)

/* ＥＣＭバッファにＲＴＣ書き込み */
/* void WriteRtcToEcm(struct CdcBlk_t *);*/
#define WriteRtcToEcm	(*writertcecm_ref_tbl)

/* メモリにＲＴＣ書き込み */
/* UBYTE WriteRtcToMem(struct CdcBlk_t *);*/
#define WriteRtcToMem	(*writertcmem_ref_tbl)

/* malloc の使用する領域(FREEPTR)をクリアする */
void _init_freeptr(void);

/* #if (PRO_CIPHER == ENABLE) */
/* 内蔵ＲＯＭ使用高速版 */
#define	Fast1LineRlToImg	(*scd_rl_to_img_tbl)
#define	Fast1LineImgToRl	(*scd_img_to_rl_tbl)
#define	Fast1LineRlToImg1	(*scd_rl_to_img1_tbl)	/* 1998/10/21 H.Yoshikawa */
/* #endif *//* PRO_CIPHER */


