/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                              */
/*  ファイル名   : DMA_TBL.C                                                  */
/*  作成者       : 野瀬                                                       */
/*  日  付       : 96.12.17                                                   */
/*  概  要       : ＤＴＣレジスタ情報のベクタテーブル                         */
/*  コメント     : ベクターテーブルの先頭アドレスはＨ’４００固定             */
/*  修正履歴     :                                                            */
/*----------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

#pragma section DTCVEC /* locate section name "CDTCVEC" */
const UWORD DMA_DTC_Vector[] = {
	(UWORD)0x0000,	/* ベクタアドレス H'400-H'401 TGI4A */
	(UWORD)0x0000,	/* ベクタアドレス H'402-H'403 TGI4B */
	(UWORD)0x0000,	/* ベクタアドレス H'404-H'405 TGI4C */
	(UWORD)0x0000,	/* ベクタアドレス H'406-H'407 TGI4D */
	(UWORD)0x0000,	/* ベクタアドレス H'408-H'409 TGI4V */
	(UWORD)0x0000,	/* ベクタアドレス H'40A-H'40B TGI3A */
	(UWORD)0x0000,	/* ベクタアドレス H'40C-H'40D TGI3B */
	(UWORD)0x0000,	/* ベクタアドレス H'40E-H'40F TGI3C */
	(UWORD)0x0000,	/* ベクタアドレス H'410-H'411 TGI3D */
	(UWORD)0x0000,	/* ベクタアドレス H'412-H'413 TGI2A */
	(UWORD)0x0000,	/* ベクタアドレス H'414-H'415 TGI2B */
	(UWORD)0x0000,	/* ベクタアドレス H'416-H'417 TGI1A */
	(UWORD)0x0000,	/* ベクタアドレス H'418-H'419 TGI1B */
	(UWORD)0x0000,	/* ベクタアドレス H'41A-H'41B TGI0A */
	(UWORD)0x0000,	/* ベクタアドレス H'41C-H'41D TGI0B */
	(UWORD)0x0000,	/* ベクタアドレス H'41E-H'41F TGI0C */
	(UWORD)0x0000,	/* ベクタアドレス H'420-H'421 TGI0D */
	(UWORD)0x0000,	/* ベクタアドレス H'422-H'423 ADI   */
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	(UWORD)0x01C0,	/* ベクタアドレス H'424-H'425 IRQ0  */	/* 未使用 */
	(UWORD)0x01D0,	/* ベクタアドレス H'426-H'427 IRQ1  */	/* 未使用 */
	(UWORD)0x01E0,	/* ベクタアドレス H'428-H'429 IRQ2  */	/* 未使用 */
	(UWORD)0x01F0,	/* ベクタアドレス H'42A-H'42B IRQ3  */	/* 未使用 */
	(UWORD)0x0200,	/* ベクタアドレス H'42C-H'42D IRQ4  */
	(UWORD)0x0210,	/* ベクタアドレス H'42E-H'42F IRQ5  */
	(UWORD)0x0220,	/* ベクタアドレス H'430-H'431 IRQ6  ANZU_L RS232C */ /* Changed by H.Kubo 1998/07/15 */
	(UWORD)0x0230,	/* ベクタアドレス H'432-H'433 IRQ7  */
#else
	(UWORD)0x0000,	/* ベクタアドレス H'424-H'425 IRQ0  */
	(UWORD)0x0000,	/* ベクタアドレス H'426-H'427 IRQ1  */
	(UWORD)0x0000,	/* ベクタアドレス H'428-H'429 IRQ2  */
	(UWORD)0x0000,	/* ベクタアドレス H'42A-H'42B IRQ3  */
	(UWORD)0x0000,	/* ベクタアドレス H'42C-H'42D IRQ4  */
	(UWORD)0x0000,	/* ベクタアドレス H'42E-H'42F IRQ5  */
/*	(UWORD)0x0000,	/@ ベクタアドレス H'430-H'431 IRQ6  ANZU_L RS232C */
	(UWORD)0x01B0,	/* ベクタアドレス H'430-H'431 IRQ6  */
	(UWORD)0x0000,	/* ベクタアドレス H'432-H'433 IRQ7  */
#endif
	(UWORD)0x0000,	/* ベクタアドレス H'434-H'435 CMI0  */
	(UWORD)0x0000,	/* ベクタアドレス H'436-H'437 CMI1  */
	(UWORD)0x0000,	/* ベクタアドレス H'438-H'439 RXI0  */
	(UWORD)0x0000,	/* ベクタアドレス H'43A-H'43B TXI0  */
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)	/* changed by H.Hirao 1999/01/25 */
	(UWORD)0x0240,	/* ベクタアドレス H'43C-H'43D RXI1  */
	(UWORD)0x0250,	/* ベクタアドレス H'43E-H'43F TXI1  */
#else
	(UWORD)0x0000,	/* ベクタアドレス H'43C-H'43D RXI1  */
	(UWORD)0x0000,	/* ベクタアドレス H'43E-H'43F TXI1  */
#endif
	(UWORD)0x0000,	/* ベクタアドレス H'440-H'441 CMI   */
	(UWORD)0x0010,	/* ベクタアドレス H'442-H'443 ソフトウェア */
	(UWORD)0x0020,	/* ベクタアドレス H'444-H'445 ソフトウェア */
	(UWORD)0x0030	/* ベクタアドレス H'446-H'447 ソフトウェア */
};
#pragma section
