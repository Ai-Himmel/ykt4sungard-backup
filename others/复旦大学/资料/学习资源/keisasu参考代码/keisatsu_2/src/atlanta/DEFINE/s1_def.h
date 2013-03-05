/**********************************************************************************************************************
	@(#)$Id: s1_def.h,v 1.9 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/08
	Author        : 石橋正和
	Description   : S1関係定義
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#ifndef s1_def_h
	#define s1_def_h

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_def.h"

/*********************************************************************
	レジスタビットアサイン
*********************************************************************/
/* 000 リセット */
#define S1_REG_BIT_RST						0x01	/* RST ソフトウェアリセット */
#define S1_REG_BIT_HRST						0x02	/* HRST ハードウェアリセット */

/* 001 割込みリクエスト */
#define S1_REG_BIT_IRRX_HDLC				0x01	/* HDLC部で受信割込み */
#define S1_REG_BIT_IRTX_HDLC				0x02	/* HDLC部で送信割込み */
#define S1_REG_BIT_IRRX_SCI					0x04	/* SCI部で受信割込み */
#define S1_REG_BIT_IRTX_SCI					0x08	/* SCI部で送信割込み */
#define S1_REG_BIT_IRQ						0x80	/* 割込み端子の状態 */

/* 002 割込み要求マスク */
#define S1_REG_BIT_IMSK						0x80	/* 割込み要求マスク */

/* 003 割込み要求クリア */
#define S1_REG_BIT_ICLR						0x80	/* 割込み要求クリア */

/* 004 DTCイネーブル */
#define S1_REG_BIT_DTCRX_HDLC				0x01	/* HDLC部受信によるDTC要求許可 */
#define S1_REG_BIT_DTCTX_HDLC				0x02	/* HDLC部送信によるDTC要求許可 */
#define S1_REG_BIT_DTCRX_SCI				0x04	/* SCI部受信によるDTC要求許可 */
#define S1_REG_BIT_DTCTX_SCI				0x08	/* SCI部送信によるDTC要求許可 */

/* 005 DTCクリア */
#define S1_REG_BIT_DTCCLR					0x80	/* DTC要求解除 */

/* 006 モード選択 */
#define S1_REG_BIT_MODE						0x01	/* モード */

/* 008 制御コマンド */
#define S1_REG_BIT_RSF						0x01	/* RSF */
#define S1_REG_BIT_ENRSF					0x10	/* ENRSF */
#define S1_REG_BIT_ENCDM					0x20	/* ENCDM */

/* 009 制御ステータス */
#define S1_REG_BIT_STAT_RSF					0x01	/* RSFの状態 */
#define S1_REG_BIT_STAT_CSF					0x02	/* CSFの状態 */
#define S1_REG_BIT_STAT_CDF					0x04	/* CDFの状態 */

/* 00B TCFクリア */
#define S1_REG_BIT_TCFCLR1					0x01	/* TCFクリア1 */
#define S1_REG_BIT_TCFCLR2					0x02	/* TCFクリア2 */

/* 00C TCF検出 */
#define S1_REG_BIT_TCFDET1					0x01	/* TCF検出1 */
#define S1_REG_BIT_TCFDET2					0x02	/* TCF検出2 */

/* 00D S1設定 */
#define S1_REG_BIT_SC1						0x01	/* 0:スクランブラON 1:スクランブラOFF */
#define S1_REG_BIT_SC2						0x02	/* 0:共通モード 1:専用モード */

/* 00E S1バイパス */
#define S1_REG_BIT_BYPASS					0x01	/* S1をバイパスする */

/* 012 受信制御 */
#define S1_REG_BIT_SCI_RX_STCLR				0x01	/* 受信ステイタスクリア */
#define S1_REG_BIT_SCI_RX_FIFOCLR			0x04	/* 受信FIFOクリア */
#define S1_REG_BIT_SCI_RXEN					0x80	/* 受信許可 */

/* 013 受信ステータス */
#define S1_REG_BIT_SCI_RXRDY				0x01	/* 受信データあり */
#define S1_REG_BIT_SCI_OVE					0x02	/* オーバーランエラー */

/* 014 送信制御 */
#define S1_REG_BIT_SCI_TX_STCCLR			0x01	/* TxEND, UNEクリア */
#define S1_REG_BIT_SCI_UNEND				0x02	/* アンダーラン発生 */
#define S1_REG_BIT_SCI_TXEN					0x80	/* 送信許可 */

/* 015 送信ステータス */
#define S1_REG_BIT_SCI_TXRDY				0x01	/* 送信データ書き込み可 */
#define S1_REG_BIT_SCI_UNE					0x02	/* アンダーランエラー発生 */
#define S1_REG_BIT_SCI_TXEND				0x04	/* 送信データなし */

/* 016 割込み、DTCイネーブル */
#define S1_REG_BIT_SCI_RXRDYIE				0x01	/* RxRDYによる割込み許可 */
#define S1_REG_BIT_SCI_OVEIE				0x02	/* OVEによる割込み許可 */
#define S1_REG_BIT_SCI_RXRDYDTCE			0x08	/* RxRDYによるDTC許可 */
#define S1_REG_BIT_SCI_TXRDYIE				0x10	/* TxRDYによる割込み許可 */
#define S1_REG_BIT_SCI_UNEIE				0x20	/* UNEによる割込み許可 */
#define S1_REG_BIT_SCI_TXENDIE				0x40	/* TxENDによる割込み許可 */
#define S1_REG_BIT_SCI_TXRDYDTCE			0x80	/* TxRDYによるDTC許可 */

/* 017 割込み要求 */
#define S1_REG_BIT_SCI_RXRDYRQ				0x01	/* RxRDYによる割込み要求 */
#define S1_REG_BIT_SCI_OVERQ				0x02	/* OVEによる割込み要求 */
#define S1_REG_BIT_SCI_TXRDYRQ				0x10	/* TxRDYによる割込み要求 */
#define S1_REG_BIT_SCI_UNERQ				0x20	/* UNEによる割込み要求 */
#define S1_REG_BIT_SCI_TXENDRQ				0x40	/* TxENDによる割込み要求 */



/* 022 受信ステータスレジスタ0(RxSR0) */
#define S1_REG_BIT_HDLC_RXRDY				0x01
#define S1_REG_BIT_HDLC_DIDL				0x02
#define S1_REG_BIT_HDLC_RXIDL				0x04
#define S1_REG_BIT_HDLC_CRC					0x08
#define S1_REG_BIT_HDLC_OER					0x10
#define S1_REG_BIT_HDLC_SFER				0x20
#define S1_REG_BIT_HDLC_EOF					0x40
#define S1_REG_BIT_HDLC_ADET				0x80

/* 023 受信ステータスレジスタ1(RxSR1) */
#define S1_REG_BIT_HDLC_RBL0				0x01
#define S1_REG_BIT_HDLC_RBL1				0x02
#define S1_REG_BIT_HDLC_RBL2				0x04

/* 024 受信制御レジスタ(RxCR) */
#define S1_REG_BIT_HDLC_STC					0x01
#define S1_REG_BIT_HDLC_RXE					0x80

/* 025 受信割込み許可レジスタ(RxIER) */
#define S1_REG_BIT_HDLC_RXRDYIE				0x01
#define S1_REG_BIT_HDLC_DIDLIE				0x02
#define S1_REG_BIT_HDLC_ERRIE				0x04
#define S1_REG_BIT_HDLC_ENDIE				0x08
#define S1_REG_BIT_HDLC_RXDI				0x80

/* 026 送信ステータスレジスタ(TxSR) */
#define S1_REG_BIT_HDLC_TXRDY				0x01
#define S1_REG_BIT_HDLC_TXU					0x02
#define S1_REG_BIT_HDLC_TXEMP				0x04
#define S1_REG_BIT_HDLC_TXEND				0x08

/* 028 送信制御レジスタ(TxCR) */
#define S1_REG_BIT_HDLC_TXLAST				0x01
#define S1_REG_BIT_HDLC_SA					0x04
#define S1_REG_BIT_HDLC_TXRST				0x08
#define S1_REG_BIT_HDLC_IDLS				0x10
#define S1_REG_BIT_HDLC_SB					0x20
#define S1_REG_BIT_HDLC_SH					0x40
#define S1_REG_BIT_HDLC_TXE					0x80

/* 029 送信割込み許可レジスタ(TxIER) */
#define S1_REG_BIT_HDLC_TXRDYIE				0x01
#define S1_REG_BIT_HDLC_TXUIE				0x02
#define S1_REG_BIT_HDLC_TXENDIE				0x08
#define S1_REG_BIT_HDLC_TXDI				0x80

/* 02B 送信モードレジスタ */
#define S1_REG_BIT_HDLC_TXLASTEND			0x01
#define S1_REG_BIT_HDLC_TXUEND				0x02
#define S1_REG_BIT_HDLC_NRZIM				0x10

/* 02C リクエストレジスタ(REQR) */
#define S1_REG_BIT_HDLC_IRX					0x01
#define S1_REG_BIT_HDLC_ITX					0x02
#define S1_REG_BIT_HDLC_RXDRQ				0x40
#define S1_REG_BIT_HDLC_TXDRQ				0x80

/* 02D マスクレジスタ(MASKR) */
#define S1_REG_BIT_HDLC_MRX					0x01
#define S1_REG_BIT_HDLC_MTX					0x02
#define S1_REG_BIT_HDLC_MRXDRQ				0x40
#define S1_REG_BIT_HDLC_MTXDRQ				0x80



/*********************************************************************
	DTC要求種別(S1_EnableDTC_Request()の引数に用いる)
*********************************************************************/
#define S1_DTC_NONE				0 /* なし */
#define S1_DTC_RX_HDLC			1 /* HDLC受信 */
#define S1_DTC_TX_HDLC			2 /* HDLC送信 */
#define S1_DTC_RX_SCI			3 /* SCI受信 */
#define S1_DTC_TX_SCI			4 /* SCI送信 */

/*********************************************************************
	S1使用時の最速ボーレート
*********************************************************************/
#define S1_BAUD_RATE_MAX		BPS9600_V29

#endif
