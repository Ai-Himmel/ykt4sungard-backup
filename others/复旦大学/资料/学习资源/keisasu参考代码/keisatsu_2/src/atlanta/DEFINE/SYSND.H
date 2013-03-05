#ifndef sysnd_h
	#define sysnd_h

#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\syswarp.h"

/************************************************************************
 * ナンバーディスプレイ機能データ										*
 * extern struct SYS_NumberDisplayTable SYB_NumberDisplay				*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
struct SYS_NumberDisplayTable {
	UBYTE Dial[SYS_DIRECT_DIAL_MAX];		/* ダイヤル番号				*/
	UBYTE Name[SYS_DIAL_NAME_MAX];			/* 相手先名					*/
	struct SYS_SubDialData_t WarpData;		/* 受信原稿転送データ 		*/
	
	UBYTE Reserve1;							/* 予約１					*/
	UBYTE Reserve2;							/* 予約２					*/
	UBYTE Reserve3;							/* 予約３					*/
	UBYTE Reserve4;							/* 予約４					*/
};

/************************************************************************
 * ナンバーディスプレイ対応接続機										*
 * extern UBYTE SYB_NumberDisplayTel									*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define ND_NO_CONNECTING			0x00	/* 未接続					*/
/*#define ND_TEL1_CONNECTING			0x01	/* ＮＤ対応ＴＥＬ１接続		*/
#define ND_TEL2_CONNECTING			0x01	/* ＮＤ対応ＴＥＬ２接続		*/


/************************************************************************
 * ナンバーディスプレイ機能の着信履歴データ								*
 * extern struct SYS_NumberDisplayJournalTable SYB_NumberDisplayJournal	*
 * 1998/08/18															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_NumberDisplayJournalTable {
	UBYTE Status;							/* 使用/未使用				*/
	UDWORD CalledTime;		/* 着信時間 */
							/* 1992年1月1日0時0分0秒からの蓄積秒数 */
	UBYTE Dial[SYS_DIRECT_DIAL_MAX];		/* ダイヤル番号				*/
	UBYTE Name[SYS_DIAL_NAME_MAX];			/* 相手先名					*/
	UBYTE Reason;							/* 非通知理由				*/
	UBYTE Note;								/* 備考						*/
	UBYTE InformationRxError;				/* 情報受信のエラー状態 	*/ /* by H.Kubo 1998/10/21 */
	UBYTE Reserve1;							/* 予約１					*/ 
	UBYTE Reserve2;							/* 予約２					*/
	UBYTE Reserve3;							/* 予約３					*/
	UBYTE Reserve4;							/* 予約４					*/
};

/*-----------------------------------------------------------------------
** SYB_NumberDisplayJournal.Status
** 使用/未使用
** 1998/09/30
** 吉川弘康
*/
#define SYS_ND_EMPTY			0				/* 未使用 */
#define SYS_ND_SET				1				/* 使用済み */
#define SYS_ND_WRITING			0x80			/* 書き込み中 by H.Kubo 1998/10/16 */
#define SYS_ND_MODIFYING		0x40			/* 修正中 by H.Kubo 1998/10/20 */

/*-----------------------------------------------------------------------
** SYB_NumberDisplayJournal.Reason
** 発信電話番号非通知理由
** 1998/09/09
** 吉川弘康
*/
#define SYS_ND_NONE			0xFF			/* 発信電話番号通知済み／初期値 */
#define SYS_ND_REJECTION	'P'				/* ユーザ拒否 『非通知』表示 */
#define SYS_ND_NONE_AREA	'O'				/* サービスサービス不可 『表示圏外』表示 */
#define SYS_ND_PUBLIC_TEL	'C'				/* 公衆電話 『公衆電話』表示 */
#define SYS_ND_COLLISION	'S'				/* サービス競合 『表示圏外』表示 */
#define SYS_ND_F_NET		0xFD			/* F 網からの無鳴動着信 by H.Kubo 1998/10/20 */
#define SYS_ND_V23_RX_ERROR	0xFE			/* V23 受信失敗で発信者番号不明 by H.Kubo 1998/10/20 */

/*-----------------------------------------------------------------------
** SYB_NumberDisplayJournal.Note
** 備考
** Bit毎に定義して使用する
** 1998/09/25
** 吉川弘康
*/
#define SYS_ND_FAX			0x01			/* FAX受信に移行した */



/*-----------------------------------------------------------------------
** SYS_ND_CurrentJournalPoint
** 現在の通信のナンバーディスプレイ着信履歴上での位置
** 1998/10/16
** 久保博
*/
/* 0  ～ SYS_ND_JRNL_MAX はナンバーディスプレイ情報がある事を示す。履歴位置も同時に示す。 */
#define	SYS_ND_NO_JOURNAL		0xff


/* CAR 設定と履歴記憶用 by H.Kubo 1998/10/12 */
#define SYS_ND_CAR_PATTERN_MAX			30 /* 16 => 30 by H.Kubo 1998/10/15 */
#define	SYS_ND_CAR_MIN_ON_TIME			0
#define	SYS_ND_CAR_MAX_ON_TIME			1
#define	SYS_ND_CAR_MIN_OFF_TIME			2
#define	SYS_ND_CAR_MAX_OFF_TIME			3
#define	SYS_ND_CAR_MIN_ON_OFF_TIME		4
#define	SYS_ND_CAR_MAX_ON_OFF_TIME		5
#define SYS_ND_CAR_COUNTER_THRESHOLD	6

 /* CAR 検出アルゴリズムの選択 */
#define SYS_ND_CAR_MODE					7
	#define	SYS_ND_CAR_DETECT_STRICT		0x01	/* CAR 検出は、 ON 時間 OFF 時間 の長さだけで判断 */
	#define SYS_ND_CAR_PATTERN_TRAIN		0x02	/* CAR パターンを学習 */
	#define	SYS_ND_DETECT_ONLY_CAR			0x04	/* CAR のみ検出。呼出音(IR)は無視。*/
	#define	SYS_ND_CAR_DETECT_QUICKLY		0x08	/* 短い CI を検出したら CAR とみなす。 Quick&Dirty な処理。*/
	#define	SYS_ND_EXIT_AFTER_RX_RESPONSE	0x10	/* 受信完了信号を出したら、次の IR 一波目の検出をせずに ND の処理を抜ける。 */
	#define	SYS_ND_IGNORE_OH2_IN_CAR		0x20	/* 外付け電話で ND 受信処理をする設定で、 CAR 検出時に OH2 を無視する */ 
	#define	SYS_ND_DETECT_DSE_V23_RX		0x40	/* V23 受信中に極反を検出する */
	#define	SYS_ND_SKIP_V23_TONE_DETEDCT	0x80	/* 1 なら V23 トーン検出をしない。 */

#define SYS_ND_CAR_IR_MARK_THRESHOLD	8			/* CAR と IR を区別するマークの時間長の閾値 */

#define SYS_ND_CAR_ACCEPTABLE_ERROR		9			/* 厳しい CAR 検出アルゴリズムで受理できるエラー数 */

#define SYS_ND_LAST_NCU_ND_STATUS		10

#define SYS_ND_CURRENT_NCU_ND_STATUS	11

 /* 一番最近の CAR 検査で NG となった理由 */
#define SYS_ND_CAR_DETECTION_REPORT		12
	#define	SYS_ND_CAR_MIN_ON_BIT			0x01
	#define	SYS_ND_CAR_MAX_ON_BIT			0x02
	#define	SYS_ND_CAR_MIN_OFF_BIT			0x04
	#define	SYS_ND_CAR_MAX_OFF_BIT			0x08
	#define	SYS_ND_CAR_MIN_ON_OFF_BIT		0x10
	#define	SYS_ND_CAR_MAX_ON_OFF_BIT		0x20
	#define	SYS_ND_CAR_COUNT_BIT			0x40

#define SYS_ND_CAR_COUNT_REPORT			13

#define SYS_ND_IR_STOP_DETECTION_TIMER	14
#define SYS_ND_CI_COUNTER_THRESHOLD		15 			/* 「CAR の CI らしきもの」と判断する CI の回数の閾値 */
#define SYS_ND_OH_TO_V23_RX_TIMER		16 			/* 外付け ND 電話の一次応答後、  V23 受信を起動するまでのタイマー */
#define SYS_ND_CAR_TIMEUP_TIMER			17 			/* 外付け ND 電話の一次応答が無かった場合、 IR 検出へ移行するタイマー */

#define	SYS_ND_MODEM_DIALIN_MODE		18
	#define	SYS_ND_DIALIN_TEL_EXCLUSIVE		0x01		/* モデムダィヤルインで TEL1 鳴動中に TEL2 を上げた時の動作 */
	#define	SYS_ND_SWITCH_TO_NORMAL_DIALIN	0x02		/* モデムダィヤルイン待ちで IR 検出時、ダイヤルイン着信するか added by H.Kubo 1998/11/27 */
#define	SYS_ND_NCU_CONTROL_MODE			19				/* added by H.Kubo 1998/11/28 */
	#define	SYS_ND_ACK_WITH_OFF_HOOK		0x01		/* V23 受信中に受話器が上げられた時、受信完了応答を出すかどうか by H.Kubo 1998/11/26 */
	#define	SYS_ND_SILENT_WHILE_IR_DETECT	0x02		/* 受信完了応答後に来た CI 列が IR か CAR か判別できるまで無鳴動。 by H.Kubo 1998/11/27 */
	#define	SYS_ND_COUNT_HEARABLE_IR		0x04		/* 聞こえる IR を計数する by H.Kubo 1998/11/28 */
	#define	SYS_ND_SUPPLY_FIRST_IR			0x08		/* ナンバーディスプレイ着信後の無鳴動着信時、最初の IR を TEL2 に与える by H.Kubo 1998/11/28 */
	#define	SYS_ND_FNET_CALL_MEMORIZE		0x10		/* F網無鳴動着信を着信履歴に載せる by H.Kubo 1998/11/28 */
#define SYS_ND_CAR_HISTORY_START		20
#endif
