/*
 *	@(#)%W%
 *	FileName:	scanner.h
 *	Create:	Thu Nov 13 15:14:21 1997	by	ishiyama
 *	Description:
 *		Scanner Devices & Funcions Header
 *	Change Log:
 *		\src\eva\incからスキャナ関係のデファインをとってきて一つにまとめました  1998/09/26 by T.Soneoka
 */
#ifndef SCANNER_H
	#define SCANNER_H

/*
 * モータ制御関係
 */
#define TX_MOTOR_TABLE_MAX	9

struct ThroughUpDown {
	UWORD	ClockStep;					/* モーター駆動用周波数 | ステップ数 */
	UBYTE	TransSteps;					/* Through Up/Down Table pointer 更新ステップ数 */
	UBYTE	MoveLines;					/* SFine 換算で 5msec あたり何ライン分動くか */
};

struct MotorCtrl {
	struct ThroughUpDown CONST	*SpeedTable;
	UWORD	Attribute;					/* 連続,同期,正転/逆転,励磁方式 */
	UWORD	ExtendAttribute;			/* マイクロステップ,フラットトルク,etc. */
};

typedef CONST struct ThroughUpDown *ConstThroughUpDownPtr;

/* スキャナー・モーター速度制御命令 */
#define MOTOR_SPEED_UP		0			/* Speed Up or Through Up */
#define MOTOR_SPEED_DOWN	1			/* Speed Down or Throuhg Down */

/* for Tx Motor Table Access */
#define TX_MOTOR_CLOCK_200HZ	0
#define TX_MOTOR_CLOCK_400HZ	1
#define TX_MOTOR_CLOCK_800HZ	2
#define TX_MOTOR_CLOCK_1600HZ	3
#define TX_MOTOR_CLOCK_3200HZ	4
#define TX_MOTOR_CLOCK_6400HZ	5

/* Tx Motor Mode for ScanTimingTable[], TxMotorTable[] */
#define	TX_MOTOR_NORMAL_SCAN	0
#define	TX_MOTOR_FINE_SCAN		1
#define TX_MOTOR_SFINE_SCAN		2
#define TX_MOTOR_FINE1_2_SCAN	3
#define TX_MOTOR_SFINE1_2_SCAN	4
#define TX_MOTOR_DOC_IN			5
#define TX_MOTOR_DOC_OUT		6
#define TX_MOTOR_MOVE_TO_SCAN	7

/* Feeder Mode */
#define FEEDER_NORMAL_SCAN		0		/* Normal で読取り,読取り終了で停止 */
#define	FEEDER_FINE_SCAN		1		/* Fine で読取り,読取り終了で停止 */
#define FEEDER_SFINE_SCAN		2		/* SFine で読取り,読取り終了で停止 */
#define FEEDER_FINE1_2_SCAN		3		/* Fine 副操作1/2縮小で読取り,読取り終了で停止 */
#define FEEDER_SFINE1_2_SCAN	4		/* SFine 副操作1/2縮小で読取り,読取り終了で停止 */
#define FEEDER_DOC_IN			5		/* 原稿を待機位置まで搬送して停止 */
#define FEEDER_DOC_OUT			6		/* 全原稿排出 */
#define FEEDER_MOVE_TO_SCAN		7		/* 原稿を待機位置から読み取り位置まで搬送して停止 */

#define	DOC_POS_NO_DOCUMENT			0	/* 原稿が無い状態 */
#define	DOC_POS_MOVE_TO_DS2			1	/* DS2 に移動中 */
#define DOC_POS_MOVE_TO_READY		2	/* 待機位置に移動中 */
#define DOC_POS_MOVE_TO_SCAN		3	/* 読取り位置に移動中 */
#define	DOC_POS_SCANNING			4	/* 読取り可能 */
#define	DOC_POS_SCAN_FEEDOUT		5	/* DS２ OFF & 読取り可能 */
#define	DOC_POS_MOVE_TO_PUSH_STAMP	6	/* スタンプ押下位置へ移動中（済みスタンプＯｎ時のみの遷移） */
#define	DOC_POS_FEED_OUT			7	/* 排出中 */

/*
 *	Document関係
 */
/* Attribute */
struct ScanPageAtr {
	BOOL	Object;						/* 実体あり? TURE:割当てあり FALSE:割当てなし */
	BYTE	Code;						/* 符合化方式:*_CODE(doc.h) */
	BYTE	Mode;						/* 読取りモード:SYS_NORMAL...(doc.h) */
	BYTE	Size;						/* サイズ:DOC_*_SIZE(doc.h) */
	BYTE	Density;					/* Density:*_DENSITY(doc.h) */
	UBYTE	VerticalMode;				/* 副操作モード:TX_MOTOR_*_SCAN(scn_tbl.h) */
	UBYTE	HolzReduction;				/* スキャナ主走査縮小率 1..1/256 */
	UBYTE	VertReduction;				/* スキャナ副操作縮小率 (IP_SUBM_*(lc82103.h)) */
	UBYTE	Position;					/* Document Current Position DOC_POS_* */
	UWORD	StepsFromDs1On;				/* DS1 ON からの移動ステップ数(SFINE 換算) */
	UWORD	StepsFromDs2On;				/* DS2 ON からの移動ステップ数(SFINE 換算) */
	UWORD	StepsFromDs2Off;			/* DS2 OFF からの移動ステップ数(SFINE 換算) */
	UWORD	Ds2ToScanSteps;				/* DS2 ON から読取り開始までのステップ数(SFINE 換算) */
	UWORD	Ds2ToScanEndSteps;			/* DS2 OFF から読取り終了までのステップ数(SFINE 換算) */
};


/* EXTERN BYTE	ScannerMode; */
#define SCANNER_NEUTRAL_MODE	0
#define SCANNER_DOC_IN_MODE		1
#define SCANNER_DOC_OUT_MODE	2
#define SCANNER_DOC_SCAN_MODE	3
#define SCANNER_PICKUP_MODE		4
#define SCANNER_STAMP_MODE		5
#define SCANNER_COPY_MODE		6

/* EXTERN BYTE	ScannerCopyMode; */
#define SCANNER_COPY_REALTIME	1
#define SCANNER_COPY_NONSORT	2

/* EXTERN UWORD	ScannerError; */
/* Scanner で、解除出来るもののみ記憶 */
#define SCANNER_MAX_LINE	(0x0001 << 0) /* 最大読み取りライン・オーバー */
#define SCANNER_FEED_ERROR	(0x0001 << 1) /* 原稿滑り */
#define SCANNER_LAMP_ERROR	(0x0001 << 2) /* ランプエラー */
#define SCANNER_COVER_OPEN	(0x0001 << 3) /* カバーオープン・エラー */

#define FEED_ERROR_1M	15400
#define FEED_ERROR_3_6M	55440

/*
 * Event関係
 */
/* for Sensor */
#define SCN_EVT_DS1_ON			(0x01 << 0)
#define SCN_EVT_DS1_OFF			(0x01 << 1)
#define SCN_EVT_DS2_ON			(0x01 << 2)
#define SCN_EVT_DS2_OFF			(0x01 << 3)
#define SCN_EVT_INTERLOCK_ON	(0x01 << 4)
#define SCN_EVT_INTERLOCK_OFF	(0x01 << 5)

/* for Doc In */
#define SCN_EVT_DOCIN_SET_OK		(0x01 << 0)
#define SCN_EVT_DOCIN_NO_DOC		(0x01 << 1)
#define SCN_EVT_DOCIN_FEED_ERROR	(0x01 << 2)
#define SCN_EVT_DOCIN_COVER_OPEN	(0x01 << 3)

/* for Doc Out */
#define SCN_EVT_DOCOUT_EXIT_OK		(0x01 << 0)
#define SCN_EVT_DOCOUT_FEED_ERROR	(0x01 << 1)
#define SCN_EVT_DOCOUT_COVER_OPEN	(0x01 << 2)

/* for Doc Store */
#define SCN_EVT_DOCSTORE_FEED_ERROR		(0x01 << 2)
#define SCN_EVT_DOCSTORE_COVER_OPEN		(0x01 << 3)
#define SCN_EVT_DOCSTORE_MAXLINE_OVER	(0x01 << 4)
#define SCN_EVT_DOCSTORE_PUSH_STAMP		(0x01 << 5)
#define SCN_EVT_DOCSTORE_DOC_END		(0x01 << 6)

/* for Pickup Roller Lift up */
#define SCN_EVT_DOCPICKUP_OK			(0x01 << 0)
#define SCN_EVT_DOCPICKUP_COVER_OPEN	(0x01 << 1)

#if (0)
**/*
** *	メッセージ関係
** */
**/* from Main Task */
**#define	MSG_SCAN			1			/* 原稿蓄積開始命令 */
**#define	MSG_SHADING_INIT	2			/* シェーディング取り込み命令 */
**#define	MSG_FEED_OUT		3			/* 原稿排出命令 */
**#define	MSG_STAMP_TEST		4			/* StampTest開始命令 */
**#define	MSG_NSORT_SCAN		5			/* Non-Sort Copy Scan開始命令 */
**#define	MSG_REALTIME_COPY	6			/* RealTime Copy Scan開始命令 */
**
**
**/* from Scanner Sensor Task */
**#define MSG_DS1_ON				1		/* DS1 ON */
**#define MSG_DS1_OFF				2		/* DS1 OFF */
**#define MSG_DS2_ON				3		/* DS2 ON */
**#define MSG_DS2_OFF				4		/* DS2 OFF */
**#define MSG_SCANNER_COVER_OPEN	5		/* スキャナー・カバー・オープン */
**#define MSG_SCANNER_COVER_CLOSE	6		/* スキャナー・カバー・クローズ */
#endif

/*	From Document In Task */
#define FROM_DOCIN_TASK				0
	#define MSG_DOCIN_SETUP			1		/* 待機位置にセット完了 */
	#define MSG_DOCIN_NOTHING		2		/* 原稿が引き抜かれた */
	#define MSG_DOCIN_ERROR			3		/* 繰り込み不良 */
	#define MSG_DOCIN_LAMP_ERROR	4		/* ランプ・エラー */
	#define MSG_DOCIN_COVER_OPEN	5		/* スキャナー・カバー・オープン */

/* From Document Out Task */
#define FROM_DOCOUT_TASK			1
	#define MSG_DOCOUT_EXIT			1		/* 排出完了 */
	#define MSG_DOCOUT_FEED_ERROR	2		/* 排出不良時のエラー処理 */
	#define MSG_DOCOUT_COVER_OPEN	3		/* カバーオープン時の処理 */

/* From Document Store Task */
#define FROM_WATCH_DOC_FEED_TASK	2
	#define MSG_DOCSTORE_OK				1	/* １ページ蓄積完了 */
	#define MSG_DOCSTORE_MEMORY_OVER	2	/* メモリオーバー */
	#define MSG_DOCSTORE_STOPSW_ON		3	/* ストップスイッチによる停止 */
	#define MSG_DOCSTORE_FEED_ERROR		4	/* フィードエラー */
	#define MSG_DOCSTORE_COVER_OPEN		5	/* カバーオープン */
	#define MSG_DOCSTORE_MAXLINE_OVER	6	/* 最長原稿長を越えた */
	#define MSG_DOCSTORE_LAMP_ERROR		7	/* ランプ・エラー */
	#define MSG_DOCSTORE_SEPARATEPAGE	8	/* 分割ﾍﾟｰｼﾞ */
	#define MSG_DOCSTORE_CANCEL			9   /* 原稿蓄積キャンセル for スキャン優先処理 */

#if (0)
**/* From Shading Task */
**#define MSG_SHADE_OK			1		/* 正常終了 */
**#define MSG_SHADE_STOPSW_ON		2		/* 蓄積停止処理 */
**#define MSG_SHADE_MAXLINE_OVER	3		/* 最大読取り長を越えた */
**#define MSG_SHADE_DOC_ERROR		4		/* 原稿セットエラー */
**#define MSG_SHADE_NO_DOCUMENT	5		/* 原稿無し */
**#define MSG_SHADE_COVER_OPEN	6		/* スキャナー・カバー・オープン */
**#define MSG_SHADE_LAMP_ERROR	7		/* ランプ・エラー */
#endif

/* From Document pickup roller Pickup Task */
#define MSG_DOCPICKUP_OK			1	/* 正常終了 */
#define MSG_DOCPICKUP_COVER_OPEN	2	/* Cover Open */

/* ガンマ補正ＭＡＸ */
#define GAMMA_DATA_MAX	17
#define DENSITY_REVISE_TABLE_MAX	9
#define DENSITY	3

#define SCANNER_POWER	(0x01 << 0)
#define PRINTER_POWER	(0x01 << 1)

#define SCANBUF_COL	256
#define SCANBUF_ROW	16

#define SCANPAGE_COL	256
#if (0)
** /* 読み取り用ページメモリをＢ４ノーマル１枚からＢ４ファイン１枚に変更します。 By O.Kimoto 1999/01/09 */
** #define SCANPAGE_ROW	1540	/* 暫定 B4 364mm->400msとして400×3,85=1540 */
#else
#define SCANPAGE_ROW	2888
#endif

#define	SCN_OPEN_OK					0  /* スキャナーオープン正常終了 */
#define	SCN_OPEN_ERROR				-1 /* スキャナーオープン異常終了 */

#define REDUCTION_NO			0
#define REDUCTION_B4_A4			1

#define REDUCTION_POS_MAX		32

/*
** 原稿蓄積中にクラッチがＯＦＦしてしまう不具合
** ４分では短すぎる、３０分見るようにする
** また、スキャナモータの割り込みも１０ｍｓになっているので変更
** 1999/02/10 by T.Soneoka
*/
#if (0)
**	#define STOP_EXCITE_COUNT		(1000/5)		/* １０００ｍｓ励磁 */
**	#define STOP_EXCITE_COUNT_SCAN	(60*4*1000/5)	/* ４分励磁 */
#else
	#define STOP_EXCITE_COUNT		(1000/10)		/* １０００ｍｓ励磁 */
	#define STOP_EXCITE_COUNT_SCAN	(60*30*1000/10)	/* ３０分励磁 */
#endif
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#define NO_FEED_CHECK	0
#define FEED_CHECK		1

/* SCN_TBL.Cから移動してきました  1999/02/24 by T.Soneoka */
/*
 *	HINOKI ADF原稿搬送距離
 *
 *	DS1    SeparateRoller   DS2        READ       Stamp     ExitRoller      EXIT
 *	 *           *           *           *          *           *             *
 *	 |<-170step->|<-402step->|<-167step->|<-146step->|<-169step->|<-462step->|
 *     11.02mm      26.13mm     10.85mm     9.50mm      11.00mm     30mm
 *                              DS2 Off READ
 *                           |<---->|    |
 *                             5mm
*/
#define FROM_DS1_TO_SPR		170
#define FROM_SPR_TO_DS2		402
#define FROM_DS2_TO_RED		168	/* 167->168 */
#define FROM_RED_TO_STP		146
#define FROM_STP_TO_EXR		169	/* 169->170 */
#define FROM_EXR_TO_EXI		462

#define FROM_DS2_TO_READY	62	/* 4mm */
/*
** ＨＩＮＯＫＩ ＣＳ機とＳＡＫＵＲＡを合わせ込んだ
** （ＳＡＫＵＲＡは原稿端３ｍｍ切り捨て）
**  1999/02/23 by T.Soneoka
*/
#if (0)
**	#define FROM_DS2_TO_SCNEND	62	/* 4mm */
#else
#if (0) /* 1999/03/01 by T.Soneoka */
**	#define FROM_DS2_TO_SCNEND	31	/* 2mm */
#else
	#define FROM_DS2_TO_SCNEND	46	/* 3mm */
#endif
#endif
#define FROM_DS2_TO_STAMP	80

#define STAMP_INTERVAL		770 /* 50mm */

#if defined(HINOKI2) || defined(HINOKI3) || defined(KEISATSU)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
#define FILTER_THOUGH	(UWORD)0		/* スルー */
#define FILTER1_HALF	(UWORD)1		/* 強調フィルタ1、×0.5 */
#define FILTER1_1		(UWORD)2		/* 強調フィルタ1、×1.0 */
#define FILTER1_2		(UWORD)3		/* 強調フィルタ1、×2.0 */
#define FILTER1_3		(UWORD)4		/* 強調フィルタ1、×3.0 */
#define FILTER1_4		(UWORD)5		/* 強調フィルタ1、×4.0 */
#define FILTER2_1		(UWORD)6		/* 強調フィルタ2、×1.0 */
#define FILTER2_2		(UWORD)7		/* 強調フィルタ2、×2.0 */
#define FILTER_AVERAGE	(UWORD)8		/* 平滑 */
#define FILTER0_0		(UWORD)9		/* 強調フィルタ使用しない by Y.kano 2004/01/28 */

#define SCN_SD_BLACK		0x01		/* LC821033仕様につき追加 by Y.Kano 2003/11/27 */
#define SCN_SD_WHITE		0x00		/* LC821033仕様につき追加 by Y.Kano 2003/11/27 */

#define SCN_WHITE_THRESHOLD	0x18		/* 白シェーディングデータ孤立点除去閾値 by Y.Kano 2004/01/19 */
#define SCN_BLACK_THRESHOLD	0x10		/* 黒シェーディングデータ孤立点除去閾値 by Y.Kano 2004/01/19 */
#endif

#endif	/* SCANNER_H */
