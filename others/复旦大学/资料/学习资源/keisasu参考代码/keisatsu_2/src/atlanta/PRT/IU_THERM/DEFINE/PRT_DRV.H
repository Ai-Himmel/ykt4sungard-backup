/*
 *	@(#)$Id: PRT_DRV.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/prt_drv.h
 *	Create:	Fri Mar 13 15:52:57 1998	by	ishiyama
 *	Description:
 *		ミノルタ SP-322 Printer & Thermal Transfer Printer Driver
 *	Change Log:
 *		
 */
#ifndef	PRT_DRV_H
	#define	PRT_DRV_H

#include "\src\atlanta\prt\iu_therm\define\prtqueue.h"

struct PrinterCommandResponse {
	UBYTE	Command;
	UBYTE	Response;
};

/*
 * コマンド・テーブルとステータス・バッファ上のインデックス
 *		PrinterCommand[xxxx]
 *		PrinterStatus[xxxx]
 */
/* ステータス要求コマンド */
#define	PRTCOM_STANDARD_STAT		0
#define	PRT_STATUS_0				0
#define	PRTCOM_OPERATER_CALL_STAT	1
#define	PRT_STATUS_1				1
#define	PRTCOM_SERVICE_CALL_STAT	2
#define	PRT_STATUS_2				2
#define	PRTCOM_JAM_STAT				3
#define	PRT_STATUS_3				3
#define	PRTCOM_RESEND_PAGE_STAT		4
#define	PRT_STATUS_4				4
#define	PRTCOM_CASSETTE_STAT		5
#define	PRT_STATUS_5				5
#define	PRTCOM_MP_TRAY_STAT			6
#define	PRT_STATUS_6				6
#define	PRTCOM_MP_TRAY_LENGTH_STAT	7
#define	PRT_STATUS_7 				7
#define	PRTCOM_EXIT_PAGE_STAT		8
#define	PRT_STATUS_9				8
#define	PRTCOM_SELECTED_PAPER_STAT	9
#define	PRT_STATUS_10				9
#define	PRTCOM_TONER_STAT			10
#define	PRT_STATUS_15				10
#define	PRTCOM_CASSETTE_SET_STAT	11
#define	PRT_STATUS_18				11
#define	PRTCOM_EXIST_PAPER_STAT		12
#define	PRT_STATUS_21				12
#define	PRTCOM_VERSION_STAT			13
#define	PRT_STATUS_30				13
#define	PRTCOM_BIAS_STAT			14
#define	PRT_STATUS_31				14

/* 実行コマンド */
#define	PRTCOM_SET_PAUSE				15 /* 返送ステータス０ */
#define	PRTCOM_RELEASE_PAUSE			16 /* 返送ステータス０ */
#define	PRTCOM_SELECT_CASSETTE			17 /* 返送ステータス０ */
#define	PRTCOM_SELECT_MP_TRAY			18 /* 返送ステータス０ */
#define	PRTCOM_RESET_MISPRINT			19 /* 返送ステータス０ */
#define	PRTCOM_RESET_NOCLEAN_MISPRINT	20 /* 返送ステータス０ */
#define	PRTCOM_FAN_MOTOR_ON				21 /* 返送ステータス０ */
#define	PRTCOM_FAN_MOTOR_OFF			22 /* 返送ステータス０ */

/* 拡張実行コマンド ２バイトコード */
#define	PRTCOM_SET_TRANS_CURRENT		23 /* 返送ステータス０ */
#define PRTPARAM_CURRENT_20		0
#define PRTPARAM_CURRENT_19		4
#define PRTPARAM_CURRENT_18		8
#define PRTPARAM_CURRENT_17		12
#define PRTPARAM_CURRENT_16		16
#define PRTPARAM_CURRENT_15		20
#define PRTPARAM_CURRENT_14		24
#define PRTPARAM_CURRENT_13		28
#define PRTPARAM_CURRENT_12		32
#define PRTPARAM_CURRENT_11		36
#define PRTPARAM_CURRENT_10		40
#define PRTPARAM_CURRENT_9		44
#define PRTPARAM_CURRENT_8		48
#define PRTPARAM_CURRENT_7		52
#define PRTPARAM_CURRENT_6		56
#define PRTPARAM_CURRENT_5		60

#define	PRTCOM_SET_TRAY_LENGTH			24 /* 返送ステータス０ */
#define	PRTCOM_SET_BIAS					25 /* 返送ステータス０ */
#define	PRTCOM_SET_DPI					26 /* 返送ステータス０ */

/* 拡張通信コマンド */
#define	PRTCOM_INITIALIZE				27 /* 返送ステータス０ */


/*
 *	Printer Status Definition
 */

#define	PRT_STATUS_MAX	15	/* ミノルタ */
#define	PRT_STATUS_DATA	0xFF

/* ステータス０ 基本ステータス */
#define	PRT_S0_CALL				0x02	/* オペレータコール/サービスコール */
#define	PRT_S0_PAUSE_DIAG		0x04	/* 休止状態／低温待機状態 */
#define	PRT_S0_WAIT				0x08	/* プリンタウォームアップ中 */
#define	PRT_S0_MISPRINT			0x10	/* プリントデータ再送要求 */
#define	PRT_S0_PAPER_DELIVERY	0x20    /* 用紙が給紙されて排出されるまで */
#define	PRT_S0_START_REQUEST	0x40    /* /PRINT信号受取可能 */

/* ステータス１ オペレータコールステータス */
#define	PRT_S1_COVER_OPEN	0x04		/* カバーオープン */
#define	PRT_S1_JAM			0x08		/* ジャムが生じたとき */
#define	PRT_S1_NO_PAPER		0x10		/* 選択されている給紙モードに対するカセットに紙なし */

/* ステータス２ サービスコールステータス */
/*  サービスコール情報 電源OFF時のみクリアされる */
#define	PRT_S2_FAN_ALARM			0x02 /* ファンモータの異常 */
#define	PRT_S2_ROS_MOTOR_ABNORMAL	0x10 /* スキャナモータの異常 */
#define	PRT_S2_LASER_ABNORMAL		0x20 /* レーザー異常 */
#define	PRT_S2_HIGH_TEMP			0x40 /* 定着器の異常温度検出 */

/* ステータス３ ジャム及びサイズエラーステータス */
#define	PRT_S3_MISS_FEED_JAM		0x02 /* 給紙時のJAM */
#define	PRT_S3_REG_JAM				0x04 /* 排出 - 給紙間のJAM */
#define	PRT_S3_EXIT_JAM				0x08 /* 排出時のJAM */
#define	PRT_S3_NOTEQUAL_PAPERSIZE	0x10 /* 紙サイズ不一致 */

/* ステータス４ 再送枚数要求ステータス */
#define	PRT_S4_RETRANSMIT_REQ_1		0x02 /* 再送要求枚数 1ページ */
#define	PRT_S4_RETRANSMIT_REQ_2		0x04 /* 再送要求枚数 2ページ */

/* ステータス５ 下給紙トレイの用紙サイズコード */
#define	PRT_S_PAPER_SIZE_TEST_DATA	0x7E /* ビット１～６で用紙サイズを表す */
#define	PAPER_A4_PORTRATE			0x02 /* A4縦 */
#define	PAPER_LETTER_PORTRATE		0x08 /* LETTER縦 */
#define	PAPER_NO_CASSETTE			0x00 /* 無し */

/* ステータス６ ＭＰトレイの用紙サイズコード */


/* ステータス７ ＭＰトレイの用紙長コード */
/****************************************************************************/
/* ビット１をＬＳＢとする０～６３の数値で用紙長を表す                       */
/* 		用紙長コード＝用紙長（ｍｍ）÷４－２８								*/
/*	０：不定																*/
/* 		通紙した用紙が１１６±８ｍｍ未満の時０								*/
/*６３：不定である事を示す													*/
/****************************************************************************/

/* ステータス８ 記述無し */

/* ステータス９ 排紙枚数情報ステータス */
/* ビット１をＬＳＢとする０～６３の数値で用紙長を表す */
#define	NUMBER_OF_PAGES_PRINTED	0x3E	/* ０～６３までの数値 */

/* ステータス１０ 給紙部選択ステータス */
#define	PRT_S10_MP_TRAY		0x04		/* 給紙トレイがＭＰトレイ */
#define	PRT_S10_CASSETTE	0x40		/* 給紙トレイが下段カセット */

/* ステータス１１ 記述無し */
/* ステータス１２ 記述無し */
/* ステータス１３ 記述無し */
/* ステータス１４ 記述無し */

/* ステータス１５ トナー情報ステータス */
#define	PRT_S15_TONER_WARNING	0x04    /* EPカートリッジのトナー量が残り少ない */

/* ステータス１６ 記述無し */
/* ステータス１７ 記述無し */

/* ステータス１８ 給紙部装着ステータス */
#define	PRT_S18_CASSETTE	0x40		/* 下段給紙機構が装備されている */
#define	PRT_S18_MP_TRAY	0x04		/* 常に "1" */

/* ステータス１９記述無し */
/* ステータス２０記述無し */

/* ステータス２１給紙部 紙有無状態ステータス */
#define	PRT_S21_CASSETTE	0x40		/* 下段トレイに用紙あり */
#define	PRT_S21_MP_TRAY	0x04		/* ＭＰトレイに用紙あり */

/* ステータス２２ 記述無し */
/* ステータス２３ 記述無し */
/* ステータス２４ 記述無し */
/* ステータス２５ 記述無し */
/* ステータス２６ 記述無し */
/* ステータス２７ 記述無し */
/* ステータス２８ 記述無し */
/* ステータス２９ 記述無し */

/* ステータス３０ M/Cバージョンステータス */
/* ビット１をＬＳＢとする０～６３の数値で用紙長を表す */
#define	MC_VERSION	0x3E				/* ０～６３までの数値 */

/* ステータス３１バイアス調整ステータス */
/* ビット１をＬＳＢとする０～６３の数値で表す */
/* 設定される範囲は２～７ */
#define	PRT_S23_LD_VERY_LIGHT	0x02    /* 印字濃度 非常に薄い */
#define	PRT_S23_LD_LIGHT		0x03    /* 印字濃度 薄い */
#define	PRT_S23_LD_LITTLE_LIGHT	0x04    /* 印字濃度 やや薄い */
#define	PRT_S23_LD_NORMAL		0x05    /* 印字濃度 標準 */
#define	PRT_S23_LD_LITTLE_DARK	0x06    /* 印字濃度 やや濃い */
#define	PRT_S23_LD_DARK			0x07    /* 印字濃度 濃い */

/* エラーステータス */
#define	PRT_ERROR_STATUS_DATA		0x80	/* エラーステータスの際はこのbitが立つ */
#define	PRT_ERROR_CHECK_DATA		0x40	/* エラービット以外のマスク */
#define	PRT_ERROR_PARITY_ERROR	0x40    /* パリティーエラー */

#define	PARITY_BIT	0x01				/* Odd Parity */


/*
 *	Cassette Attibute
 */
struct	CassetteAttribute {
	UBYTE	PaperSize;					/* PAPER_SIZE_* (see prt_drv.h) */
	UWORD	Margin;						/* Print Margin 23.1line/mm あたりのライン数*/
};



/*
 * カセットの選択
 */
#define NUMBER_OF_CASSETTE	2
#define	PRT_MP_TRAY		0
#define	PRT_CASSETTE	1

/*
 *	記録紙のサイズ別インデックス
 */
#define PAPER_SIZE_NONE		0
#define	PAPER_SIZE_A4		1
#define PAPER_SIZE_LETTER	2
#define PAPER_SIZE_LEGAL	3
#define PAPER_SIZE_F4		4
#define PAPER_SIZE_B4		5

/*
 *	記録紙選択時の評価値
 */
#define	PAPER_EVAL_OK	1
#define PAPER_EVAL_NG	0

/*
 *	記録紙選択時の評価の重み付け
 */
#define PAPER_SELECT_1PAGE		10000
#define PAPER_SELECT_MARGIN2	1000
#define PAPER_SELECT_WIDTH		100
#define PAPER_SELECT_LENGTH		10
#define PAPER_SELECT_CASSETTE	1

/*
 * パリティ
 */
#define	ODD_PARITY		0
#define	EVEN_PARITY		1

/*
 * プリンタ・エラー
 */
#define	PRT_ERROR_NO_PAPER			0x0001
#define	PRT_ERROR_JAM				0x0002
#define	PRT_ERROR_CUT_ERROR			0x0004
#define	PRT_ERROR_COVER_OPEN		0x0008
#define PRT_ERROR_HIGH_TEMP			0x0010
#define PRT_ERROR_3M_OVER			0x0020
#define PRT_ERROR_INITIALIZE		0x8000
/*
 *	for Rx Motor Control
 */
/*
 *	Rx Motor Mode
 */
#define RX_MOTOR_TABLE_MAX	6

#define RX_MOTOR_NORMAL			0
#define RX_MOTOR_FINE			1
#define RX_MOTOR_SFINE			2
#define	RX_MOTOR_FORWARD		3
#define RX_MOTOR_BACKWARD		4

/*
 *	Paper Attribute
 */
struct PaperAtr {
	BYTE	Mode;						/* 読取りモード:SYS_NORMAL...(doc.h) */
	BYTE	Size;						/* サイズ:DOC_*_SIZE(doc.h) */
	UBYTE	VerticalMode;				/* 副操作モード:RX_MOTOR_* */
	UBYTE	HolzReduction;				/* プリント主走査縮小率 */
	UBYTE	VertReduction;				/* プリント副操作縮小率 */
	BYTE	RewriteCount;				/* 同じイメージを何度書くか(Normal ２度書き) */
	UBYTE	Position;					/* Paper Current Position PAPER_POS_* */
	UBYTE	Route;						/* 搬送ルート 1998/11/11 by T.Soneoka */
	BYTE	Phase;						/* Print Phase */
	WORD	TopMargin;					/* 先端余白 */
	WORD	BottomMargin;					/* 後端余白 */
	WORD	StepsFromDocSet;			/* 記録紙セットからのステップ数	*/
	WORD	StepsFeedOut;				/* 記録紙排出ステップ数	*/
	WORD	BackWardStepsFromFeedOut;	/* 排出完了からの引き戻しステップ数 */
	WORD	StepsFromPs2On;				/* ＰＳ２がＯｎしてからのステップ数 */
/* WORDでは３ｍプリント長制限がみれません  1999/02/02 by T.Soneoka */
#if (0)
**	WORD	StepsFromPrinting;			/* 記録待機位置からのステップ数	*/
#else
	DWORD	StepsFromPrinting;			/* 記録待機位置からのステップ数	*/
#endif
	WORD	StepsToCutPosFromPlaten;	/* プラテンローラからカット位置までのステップ数	*/
};
#define	PAPER_POS_NO_PAPER					0	/* 記録紙が無い状態 */
#define	PAPER_POS_MOVE_TO_MINI_DOC_EXIT		1	/* イニシャルカット位置に移動中 */
#define PAPER_POS_FEED_OUT					2	/* 排出中 */
#define PAPER_POS_MOVE_TO_PS2				3	/* ＰＳ２センサが切れるまで引き戻し */
#define PAPER_POS_MOVE_TO_READY				4	/* 待機位置に移動中 */
#define PAPER_POS_MOVE_TO_PRINTING			5	/* 記録位置に移動中 */
#define	PAPER_POS_PRINTING					6	/* 記録可能 */
#define	PAPER_POS_MOVE_TO_CUT				7	/* 記録紙カット位置に移動中 */
#define PAPER_POS_PRINTING_TO_FEED_OUT		8	/* 記録位置から記録紙排出中 */

#define PAPER_PHASE_FEED	0			/* Feed Phase */
#define PAPER_PHASE_READY	1			/* Print Ready */
#define PAPER_PHASE_PRINT	2			/* Print Phase */

#define ROUTE_NONE				0
#define ROUTE_PRINTING_TO_READY	1

struct PrintPageObject_t {
	UBYTE	Status;						/* PRINT_PHASE_* */
	struct PrintPageQElement	PageQ;	/* Saved Print Page Queue Element */
};

/* Print Page Object Status */
#define PRINT_PHASE_NOT_USE			0	/* オブジェクト未使用 */
#define PRINT_PHASE_WAIT_READY		1	/* Printer Ready 待ち */
#define PRINT_PHASE_WAIT_DMA_START	2	/* DMA 開始待ち */
#define PRINT_PHASE_WAIT_TOD		3	/* TOD 待ち */
#define PRINT_PHASE_WAIT_DMA_END	4	/* DMA 終了待ち */
#define PRINT_PHASE_WAIT_EXIT		5	/* 排出チェックタイミング待ち */


/* for Analog Function Checker */
#define PRINTER_TEST_MODE_NON		0	/* 通常モード、テストモードではない */
#define PRINTER_TEST_MODE_MOTOR		1	/* 受信モーター連続回転 */
#define PRINTER_TEST_MODE_THERMAL	2	/* サーマルヘッドテスト */


/* ＲＬからイメージに展開する時に使用するバッファ By O.Kimoto 1998/09/24 */
#define	PRINT_IMAGE_BUF_LINE		32	/* Change 20 to 32 by O.Kimoto 1998/11/6 */
#define PRINT_IMAGE_BUF_SIZE		256

#define PRT_BUF_WRITE_COUNT		(PRINT_IMAGE_BUF_LINE - 2)

#define PRINT_TIMING_MIN		19
#define PRINT_TIMING_MAX		0


#endif /* PRT_DRV_H */
