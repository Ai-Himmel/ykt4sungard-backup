/**********************************************************************************************************************
	@(#)$Id: s1_data.c,v 1.7 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/13
	Author        : 石橋正和
	Description   : S1関係データ
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"

#pragma section S1_REG

volatile UBYTE S1_REG_Reset;				/* 000 リセット */
volatile UBYTE S1_REG_IntReqest;			/* 001 割り込みリクエスト */
volatile UBYTE S1_REG_IntMask;				/* 002 割り込みマスク */
volatile UBYTE S1_REG_IntClear;				/* 003 割り込みクリア */
volatile UBYTE S1_REG_DTC_Enable;			/* 004 DTCイネーブル */
volatile UBYTE S1_REG_DTC_Clear;			/* 005 DTCクリア */
volatile UBYTE S1_REG_DTC_Mode;				/* 006 モード切換え */
volatile UBYTE S1_REG_007;					/* 007 空き */
volatile UBYTE S1_REG_MDM_ControlCommand;	/* 008 (モデム)制御コマンド */
volatile UBYTE S1_REG_MDM_ControlStatus;	/* 009 (モデム)制御ステータス */
volatile UBYTE S1_REG_00A;					/* 00A (Reserved) */
volatile UBYTE S1_REG_MDM_TCF_Clear;		/* 00B (モデム)TCFクリア */
volatile UBYTE S1_REG_MDM_TCF_Detect;		/* 00C (モデム)TCF検出 */
volatile UBYTE S1_REG_MDM_ConfigureS1;		/* 00D (モデム)S1設定 */
volatile UBYTE S1_REG_MDM_BypassS1;			/* 00E (モデム)S1バイパス */
volatile UBYTE S1_REG_00F;					/* 00F 空き */
volatile UBYTE S1_REG_SCI_Data;				/* 010 (SCI)シリアルデータ */
volatile UBYTE S1_REG_FPGA_Version;			/* 011 (SCI)FPGAバージョン */
volatile UBYTE S1_REG_SCI_RxControl;		/* 012 (SCI)受信制御 */
volatile UBYTE S1_REG_SCI_RxStatus;			/* 013 (SCI)受信ステータス */
volatile UBYTE S1_REG_SCI_TxControl;		/* 014 (SCI)送信制御 */
volatile UBYTE S1_REG_SCI_TxStatus;			/* 015 (SCI)送信ステータス */
volatile UBYTE S1_REG_SCI_IntDTC_Enable;	/* 016 (SCI)割込み&DTCイネーブル */
volatile UBYTE S1_REG_SCI_IntRequest;		/* 017 (SCI)割込み要因 */
volatile UBYTE S1_REG_018;					/* 018 空き */
volatile UBYTE S1_REG_019;					/* 019 空き */
volatile UBYTE S1_REG_01A;					/* 01A 空き */
volatile UBYTE S1_REG_01B;					/* 01B 空き */
volatile UBYTE S1_REG_01C;					/* 01C 空き */
volatile UBYTE S1_REG_01D;					/* 01D 空き */
volatile UBYTE S1_REG_01E;					/* 01E 空き */
volatile UBYTE S1_REG_01F;					/* 01F 空き */
volatile UBYTE S1_REG_HDLC_SelectCRC;		/* 020 (HDLC)CRC選択 */
volatile UBYTE S1_REG_HDLC_TransMode;		/* 021 (HDLC)転送モード */
volatile UBYTE S1_REG_HDLC_RxStatus0;		/* 022 (HDLC)受信ステータス0 */
volatile UBYTE S1_REG_HDLC_RxStatus1;		/* 023 (HDLC)受信ステータス1 */
volatile UBYTE S1_REG_HDLC_RxControl;		/* 024 (HDLC)受信制御 */
volatile UBYTE S1_REG_HDLC_RxIntPermit;		/* 025 (HDLC)受信割込み許可 */
volatile UBYTE S1_REG_HDLC_TxStatus;		/* 026 (HDLC)送信ステータス */
volatile UBYTE S1_REG_027;					/* 027 (Reserved) */
volatile UBYTE S1_REG_HDLC_TxControl;		/* 028 (HDLC)送信制御 */
volatile UBYTE S1_REG_HDLC_TxIntPermit;		/* 029 (HDLC)送信割込み許可 */
volatile UBYTE S1_REG_HDLC_Data;			/* 02A (HDLC)シリアルデータ */
volatile UBYTE S1_REG_HDLC_TxMode;			/* 02B (HDLC)送信モード */
volatile UBYTE S1_REG_HDLC_Request;			/* 02C (HDLC)リクエスト */
volatile UBYTE S1_REG_HDLC_Mask;			/* 02D (HDLC)マスク */

#pragma section

/*************************************************
	タスクID
*************************************************/
UWORD tskno_S1_ReceiveTCF_Data;

