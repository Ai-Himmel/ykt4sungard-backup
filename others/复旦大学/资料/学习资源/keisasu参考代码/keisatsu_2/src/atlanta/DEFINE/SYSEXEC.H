/* By Y.Suzuki 1996/10/16 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysexec.h */
#ifndef sysexec_h
	#define sysexec_h

#include "\src\atlanta\define\sysdial.h"

/************************************************************************
 * 発信スケジューラ														*
 * struct SYS_ExecQueueData_t SYB_ExecQueue[SYS_EXEC_QUEUE_MAX]			*
 * sysexec.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_ExecQueueData_t {
	UBYTE Status;				/* 使用状況 */
	UBYTE Kind;					/* 予約種別 */
	union {
		UBYTE Command;			/* 通信予約番号 */
								/* SYB_CommandFile[]の配列オフセット値 */
		UBYTE Batch;			/* 一括送信番号 */
								/* SYB_BatchTxFile[]の配列オフセット値 */
		UBYTE ContPolling;		/* 連続ポーリング番号（←本当は不必要?)*/
	} Number;
	UBYTE RedialCount;			/* リダイヤル回数 */
	UBYTE RedialTime;			/* リダイヤル間隔 */
	UBYTE Mode;					/**通信モード */	/**杏“送信証”に使用 ( Mode, StartTime, TotalTime)*/
								/**最終のモードを記憶 */	/**By H.Hirao Apr.23,1996 */
/* 1997/05/09  By T.Yamaguchi UBYTE → UWORD */
/*	UBYTE Page;					/@ 通信ページ */
	UBYTE Option;				/* 付加機能 */
	UDWORD StartTime;			/* 通信開始時間 */
								/* 1992年1月1日0時0分0秒からの蓄積秒数 */
	UWORD Page;					/* 通信ページ */
	UWORD TotalTime;			/* 通信時間(秒) */
	UWORD Result;				/* 通信結果 */
								/* Bit11 Bit10 */
								/* 0	 0		:正常終了 */
								/* 0	 1		:送信ｴﾗｰ｢T.x.x｣ */
								/* 1	 0		:受信ｴﾗｰ｢R.x.x｣ */
								/* 1	 1		:ﾀﾞｲﾔﾙｴﾗｰ｢D.x.x｣ */
								/* Bit0-Bit3	:エラーコード1桁目 */
								/* Bit4-Bit7	:エラーコード2桁目 */
	struct SYS_ExecDialData_t	ExecDial;
								/* 電話番号 */
	UBYTE ErrorPage[SYS_ERROR_PAGE];
								/* 画質不良ページ */
								/* 1Bitが1ページに対応 */
								/* ErrorPage[0]LSB:1ページ目 */
	UBYTE StackNumber;			/* 回線番号 (DPR Driver's StackNumber + 1) */
};

/************************************************************************
 * 発信スケジューラの使用状況											*
 * struct SYS_ExecQueueData_t.Status									*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_EXEC_EMPTY				0	/* 未使用 */
#define SYS_EXEC_WAITING			1	/* ダイヤル待ち状態 */
#define SYS_EXEC_EXECUTE			2	/* 実行中 */
#define SYS_EXEC_FORWARD_WAITING	3	/* 転送ダイヤル待ち状態中 */
#define SYS_EXEC_FORWARD_EXECUTE	4	/* 転送実行中 */
#define SYS_EXEC_ERASED				5	/* 取消 */
#define SYS_EXEC_OK					6	/* 正常終了 */
#define SYS_EXEC_ERROR				7	/* エラー終了 */
#define SYS_EXEC_PRINT				8	/* 通信結果ﾌﾟﾘﾝﾄ */

/************************************************************************
 * 発信スケジューラの予約種別											*
 * struct SYS_ExecQueueData_t.Kind										*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_COMMAND_TRX				0	/* 通信予約による送受信 */
#define SYS_BATCH_TX				1	/* 一括送信             */
#define SYS_CONTINUOUS_POLLING		2	/* 連続ポーリング       */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
#define SYS_INF_MAIL_NO_CMD			3	/* メールコマンドなし	*/
#define SYS_INF_MAIL_TX_CMD			4	/* メール送信コマンド	*/
#define SYS_INF_MAIL_RX_CMD			5	/* メール受信コマンド	*/
#endif

/************************************************************************
 * 発信スケジューラの付加機能											*
 * struct SYS_ExecQueueData_t.Option									*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_COVER_PAGE	0x01	/* ｶﾊﾞｰﾍﾟｰｼﾞ送信済み */
								/* SYB_CommandFile[i].TitleMessageが
								 * -1でない場合に有効
								 */
#define SYS_PARTNER_NOT_RCR		0x02	/* 相手機に、受領証送信能力がないとき、
										  送信証をプリントする場合にセットする	96/06/20 BY T.Yamaguchi */
#define SYS_V34_STUP_RECOVER	0x04	/* V34ｽﾀｰﾄｱｯﾌﾟ時にｱﾎﾞｰﾄしたことを示す */
										/* 今の所、ｷｰﾌﾟ 1996/09/04 Y.Murata */
#define SYS_EXT_LINE_TX			0x10	/* 拡張回線での送信時にセットする。By T.Soneoka 1998/02/04 */
#define SYS_PSTN_ACCESS_ENABLE	0x80	/* 内線設定において、発呼時 PSTN Access Numberを発呼する必要が有るときにセットする。By O.Kimoto 1996/12/26 */

#endif
