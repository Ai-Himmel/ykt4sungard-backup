/*	By Y.Suzuki 1996/10/21	*/
/* Original File : jun\usr2:\src\ichou\define\scn_def.h */
/*--------------------------------------------------------------------*/
/* プロジェクト : KIRI/MILAN	                                      */
/* ファイル名   : scn_def.h                                           */
/* 作成者       : S.Kawasaki                                          */
/* 日  付       : 94.3.14                                             */
/* 概  要       : V53                                                 */
/*              : スキャナー用定義					                  */
/* 参照			:									                  */
/* 修正履歴     : 1996/05/29  モーター速度テーブル拡張                */
/*--------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#ifndef scn_def_h
	#define	scn_def_h
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  10,Mar,1994
*        TYPE:  DEFINE
* VAR TO HOLD:	struct MOTOR_TABLE_t SCN_ThroughUpTable：スルーアップ用
*				struct MOTOR_TABLE_t SCN_ThroughDownTable ：スルーダウン用
* DESCRIPTION:  モーター・スルーアップ／ダウン用構造体
*********************************************************************************************/

/*	ICHOUでFBS用にモーターテーブル拡張に伴って、モーターテーブル配列の数を
**	SCN_MOTOR_TABLE_MAXで定義する
**	※注意	従来のSCN_MOTOR_TABLE_MAXは各モードでのパルスレート配列数を定義していたが、
**			ICHOUでは名前を変更して、これをSCN_MOTOR_RATE_MAXとして定義する
**		1996/06/20 s.takeuchi
*/

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_H)
#define	SCN_MOTOR_TABLE_MAX		14	/* モーターテーブル配列の数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define	SCN_MOTOR_TABLE_MAX		11	/* モーターテーブル配列の数 */
#endif

#define	SCN_MOTOR_RATE_MAX		25	/* モーターテーブル：パルスレート配列の数 */

/*	ICHOU削除  1996/10/18 s.takeuchi
** #define	SCN_MOTOR_SPEED_INITIAL	0
** #define	SCN_MOTOR_SPEED_TOP		4
** #define	SCN_MOTOR_SPEED_LOW		8
*/

struct MOTOR_t {
	UWORD	PPS;			/** モーター駆動用周波数を設定 		*/
	UWORD	Step;			/** 同一周波数発生ステップ数を設定 	*/
	UBYTE	CurrentPower;	/** モーターへ流す電流の％			*/
};

struct SCN_MOTOR_TABLE_t {
	struct MOTOR_t ThroughUpDownTable[SCN_MOTOR_RATE_MAX];	/* ICHOUで名前を変更 */
	UBYTE ExciteMethod;		/* 励磁方式 */
	UBYTE InitialSpeed;		/* 初期速度 */
	UBYTE TopSpeed;			/* 最高速度 */
	UBYTE LowSpeed;			/* 最終速度 */
};

/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  23,Mar,1994
*        TYPE:  DEFINE
* VAR TO HOLD:	unsigned char SCN_DocumentStatus
* DESCRIPTION:  原稿搬送路の原稿ステータス
*********************************************************************************************/
#define	SCN_DOC_NO_DOCUMENT		0					/** 原稿が無い状態 */
#define	SCN_DOC_DS1_ON			1					/** 原稿無し状態に原稿がセットされた */
#define	SCN_DOC_MOVE_TO_READY	2					/** 原稿を待機位置に移動中  (ICHOUでは制御変更) */
#define	SCN_DOC_READY			3					/** 原稿が待機位置にある */
#define	SCN_DOC_MOVE_TO_DS2		4					/** 原稿を待機位置からＤＳ２に移動中 */
#define	SCN_DOC_DS2_ON			5					/** 原稿がＤＳ２に到達した */
#define	SCN_DOC_READY_TO_SCAN	6					/** 原稿が読み取り位置に到達した */
#define	SCN_DOC_IN_SCANNING		7					/** 原稿読み取り中 */
#define	SCN_DOC_DS3_ON			8					/** 原稿の先端がＤＳ３に到達した */
#define	SCN_DOC_DS2_OFF			9					/** 原稿の後端がＤＳ２を通過した */
#define	SCN_DOC_END_OF_SCAN		10					/** 原稿の後端が読み取り位置を通過した */
#define	SCN_DOC_EXITING			11					/** 原稿排出中 */
#define	SCN_DOC_END_OF_EXITING	12					/** 原稿を排出した */
#define	SCN_DOC_FEED_READY		13
#define	SCN_DOC_FEED_OUT		14					/** 停止キーによる原稿排出 */
#define	SCN_DOC_ADF_1ST_PAGE	15					/** ADF原稿の1ページ目を繰込み中 (ICHOU用) */
#define	SCN_DOC_MOTOR_LIFE_TEST			100			/** トルク・リミッター寿命テスト 7/19/1994 */
#define	SCN_DOC_FEED_DS3ON_WAIT			120			/**  ＤＳ３ＯＮ待ち 						*/
#define	SCN_DOC_FEED_DS2OFF_WAIT		121			/**  ＤＳ２ＯＦＦ待ち 						*/
#define	SCN_DOC_FEED_DS2ON_WAIT			122			/**  ＤＳ２ＯＮ待ち							*/
#define	SCN_DOC_FEED_DS3OFF_WAIT		123			/**  ＤＳ３ＯＦＦ待ち						*/
#define	SCN_DOC_STAMP_TEST_FEED_READY	150			/** スタンプ・テスト時の待機位置から最初のスタンプ位置への移動 */
#define	SCN_DOC_STAMP_TEST_ON_GOING		151			/** スタンプ・テスト実行中 Aug.22,1994 */
#define	SCN_DOC_STAMP_TEST_STOP			152			/** スタンプ・テスト停止要求 Aug.23,1994 */
#define	SCN_DOC_STAMP_TEST_ERROR		153			/** スタンプテストエラー */
#define	SCN_DOC_GEAR_BACK_LASH			200			/** ピックアップローラーの上昇(Gear Back Lash) */
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  23,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿搬送路の各ステップ数（２４００ｐｐｓ時）
*********************************************************************************************/
#define	SCN_STEP_DS1_AND_SEPERATE		375			/** 374.58step(114.41ms) */
#define	SCN_STEP_SEPERATE_AND_FEED		988			/** 987.63step(411.51ms) */
#define	SCN_STEP_FEED_AND_DS2			422			/** 421.57step(175.65ms) */
#define	SCN_STEP_DS2_AND_READ_POINT		835 /* +150	*/ /** 834.17step(347.57ms) May.26,1994 */
#define	SCN_STEP_READ_POINT_AND_DS3		650			/** 649.92step(270.80ms) */
#define	SCN_STEP_DS3_AND_EXIT			237			/** 236.22step(98.43ms)  */
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  31,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用割り込み禁止／許可
*********************************************************************************************/
#define	SCN_DISABLE					0
#define	SCN_ENABLE					1
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  31,Mar,1994
*        TYPE:  DEFINE
* VAR TO HOLD:	unsined char SCN_MotorSpeedControl;
* DESCRIPTION:  スキャナー・モーター速度制御用
*********************************************************************************************/
#define	SCN_MOTOR_SPEED_UP			0		/** モーター速度スルー・アップ 	*/
#define	SCN_MOTOR_SPEED_DOWN		1		/** モーター速度スルー・ダウン 	*/
#define	SCN_MOTOR_SPEED_CONSTANS	2		/** モーター速度定速			*/
#define	SCN_MOTOR_SPEED_ADJUST		3		/** モーター速度の整合中		*/	/* ICHOU追加 */
#define	SCN_MOTOR_SPEED_STOP		4		/** モーター停止中				*/
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Apr. 4,1994
*        TYPE:  DEFINE
* DESCRIPTION:  ブザー周波数設定の定義
*				SCN_SetBuzzerFrequency()の引き数として使用する事
*					周波数　＝　23.4325/2*(設定値+1)
*********************************************************************************************/
#define	SCN_BUZZER_11700HZ				0
#define	SCN_BUZZER_5850HZ				1
#define	SCN_BUZZER_3900HZ				2
#define	SCN_BUZZER_2920HZ				3
#define	SCN_BUZZER_2340HZ				4
#define	SCN_BUZZER_1950HZ				5
#define	SCN_BUZZER_1670HZ				6
#define	SCN_BUZZER_1460HZ				7
#define	SCN_BUZZER_1300HZ				8
#define	SCN_BUZZER_1170HZ				9
#define	SCN_BUZZER_1060HZ				10
#define	SCN_BUZZER_970HZ				11
#define	SCN_BUZZER_901HZ				12
#define	SCN_BUZZER_836HZ				13
#define	SCN_BUZZER_781HZ				14
#define	SCN_BUZZER_732HZ				15
#define	SCN_BUZZER_689HZ				16
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Apr. 4,1994
*        TYPE:  DEFINE
* DESCRIPTION:  モーター電流のパワー設定の定義
*				SCN_SetMotorCurrent()の引き数として使用する事
*********************************************************************************************/
#define	SCN_CURRENT_POWER_100 			0
#define	SCN_CURRENT_POWER_60  			1
#define	SCN_CURRENT_POWER_20  			2
#define	SCN_CURRENT_POWER_0   			3
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー副走査のモード
* VAR TO HOLD:  unsigned char SCN_VerticalMode = 0;
*
*	値はモーターテーブルSCN_MotorTable[]の順番に対応させること
*	追加する時はSCN_MOTOR_TABLE_MAXの値を合わせること
*********************************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_H)
#define		SCN_NORMAL				 0
#define		SCN_FINE				 1
#define		SCN_SFINE				 2
#define		SCN_DOC_IN				 3
#define		SCN_DOC_OUT				 4
#define		SCN_GEAR_BACKLASH		 5
#define		SCN_NORMAL_FEED			 6
#define		SCN_FINE_FEED			 7
#define		SCN_SFINE_FEED			 8
#define		SCN_NORMAL_FBS			 9	/* FBS:ノーマル読取り用 */
#define		SCN_FINE_FBS			10	/* FBS:ファイン読取り用 */
#define		SCN_SFINE_FBS			11	/* FBS:Ｓファイン読取り用 */
#define		SCN_MOVE_MIRROR			12	/* FBS:ミラー移動用(高速) */
#define		SCN_MOVE_MIRROR_SLOW	13	/* FBS:ミラー移動用(低速の一定速) */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define		SCN_NORMAL				 0
#define		SCN_FINE				 1
#define		SCN_SFINE				 2
#define		SCN_DOC_IN				 3
#define		SCN_DOC_OUT				 4
#define		SCN_GEAR_BACKLASH		 5
#define		SCN_NORMAL_FEED			 6
#define		SCN_FINE_FEED			 7
#define		SCN_SFINE_FEED			 8
#define		SCN_EFINE				 9
#define		SCN_EFINE_FEED			10
#endif

/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  May.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:
*********************************************************************************************/
#define		SCN_SCAN_1METER_LINES		3937	/* Normal 1meter のライン数*/
												/* Fine  :SCN_SCAN_MAX_LINE*2 = 7874lines = 1meter */
												/* Sfine :SCN_SCAN_MAX_LINE*4 = 15748lines= 1meter */
/********************************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Apr. 20,1994
*        TYPE:  DEFINE
* DESCRIPTION:
*********************************************************************************************************/
#define	FROM_SCN_SUB_TASK				1
	#define	SCN_DMA_WRITE_MEMORY_OVER	1 /* SCN_DMA_WriteTask() 			ＤＲＡＭオーバー			*/
	#define SCN_DMA_STOP_REQUEST		2 /* SCN_DMA_WriteTask() 			蓄積停止要求				*/
	#define	CDC_ENCODE_OK				3 /* CDC_EncodePageTask() 			符号化蓄積正常終了			*/
	#define	CDC_MAX_LINE_OVER			4 /* CDC_EncodePageTask() 			最大原稿長エラー			*/
	#define	SCN_SCANNER_COVER_OPEN		5 /* SCN_WatchDocumentCoverTask() 	スキャナー・カバー・エラー 	*/
	#define	SCN_DOC_FEED_ERROR			6 /* SCN_WatchDocumentFeedTask() 	原稿繰り込み不良 		   	*/
	#define	SCN_DOC_EXIT_OK				7 /* SCN_WatchDocumentExitTask()  	原稿排出正常終了 			*/
	#define	SCN_GEAR_BACK_LASH_OK		8 /* SCN_WatchGearBackLashTask()    ギア・バック・ラッシュ終了  */
	#define	SCN_SCANNER_MIRROR_ERROR	9 /* SCN_WatchDocumentMirrorTask()  ミラーキャリッジエラー監視タスク */
	#define	SCN_PAGE_COUNT_ERROR		10 /* 枚数指定エラー(SCN_Task内で使用) */
	#define SCN_DOC_PAGE_COUNT			11 /* 原稿排出ページカウント */
	#define SCN_PRINTER_COVER_OPEN		12 /* プリンタカバー開 */
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Apr. 20,1994
*        TYPE:  DEFINE
* DESCRIPTION:
*********************************************************************************************/
	#define	SCN_OPEN_OK					0  /* スキャナーオープン正常終了 */
	#define	SCN_OPEN_ERROR				-1 /* スキャナーオープン異常終了 */
/*------------------------------------*/
/* スキャナードライバー・制御テーブル */
/*------------------------------------*/
struct SCN_Control_def_t {
	/* オープンパラメータ */
	UBYTE UseType;           /* 00 : 動作種別(idp_def.h参照)    */
	UBYTE DocumentDensity;   /* 01 : 原稿濃度(sysdoc.h参照)     */
	UBYTE DocumentMode;      /* 02 : 原稿密度(sysdoc.h参照)     */
	UBYTE DocumentSize;      /* 03 : 原稿サイズ(sysdoc.h参照)   */
	UWORD ScanReduction;     /* 04 : スキャナ縮小率(26/32=81.25) */
	UWORD ScanPage;	         /* 05 : 読み取り中ページ（読取り開始でカウント） */
};

#define	SCN_SPEED_CHECK_NOT_NEED 	5


/*	励磁方式
**	※1-2相を指定すると、SCN_MotorTableのStepの2倍した値がG/Aへセットされる
**		unsigned char ExciteMethod;
**		1996/06/11 s.takeuchi
*/
#define	SCN_MOTOR_2_EXCITE		0x00
#define	SCN_MOTOR_1_2_EXCITE	0x80

/* 読取り原稿サイズ */
struct	ScanDocSizeTable_t {
	WORD	Width;		/* 幅(mm) */
	WORD	Length;		/* 長さ(line) */
	UBYTE	IsFullScan;	/* 全画素読み取り */
};


/*	読み取り種別(コピー/送信)
**		コピー原稿の場合は先端印字余白分だけ余計に送るため
**		1996/07/17 s.takeuchi
*/
#define	SCAN_FOR_TX			0		/* 送信原稿の読み取り */
#define	SCAN_FOR_COPY		1		/* コピー原稿の読み取り */

#if (0)	/* ROMテーブル(scn_tbl.c)にする  1996/11/13 */
/*	ADF用の済みスタンプ位置用のステップ(SFine)
**		1996/07/16 s.takeuchi
*/
#define	ADF_DS2ON_TO_STAMP		977		/* DS2ON～済みスタンプ位置 (38.91+24.54 mm) */
#define	ADF_DOC_EDGE_TO_STAMP	308		/* 原稿端からの済みスタンプ押下位置 (20 mm) */

/*	FBS用のモーター移動ステップ(SFine)
**		step = 距離(mm) × 15.4(l/mm)
**		1996/07/02 s.takeuchi
*/
/* 正確な位置合せ用  ※マージン:なし */
#define	FBS_STEP_HS_TO_READY		577		/* ホームセンサ～待機位置 (7.5+30 mm) */
#define	FBS_STEP_HS_TO_FBS_TOP		115		/* ホームセンサ～FBS読取り開始位置 (7.5 mm) */
#define	FBS_STEP_HS_TO_FBS_END		6583	/* ホームセンサ～FBS読取り終了位置 (7.5+420 mm) */
#define	FBS_STEP_HS_TO_LAMP_CHK		92		/* ホームセンサ～ランプチェック位置 (6 mm) */
#define	FBS_STEP_ES_TO_ADF			261		/* エンドセンサ～ADF読取り位置 (17 mm) */
/* ミラーのエラー検出用  ※マージン:10mm(154step) */
#define	FBS_STEP_MAXIMUM			8023	/* FBS上の最大可動ステップ (6+490+15 mm) */
#define	FBS_STEP_HS_ON_PERIOD		269		/* ホームセンサON期間 (7.5 mm) */
#define	FBS_STEP_HS_TO_ES			7384	/* ホームセンサ～エンドセンサ (7.5+420+42 mm) */
#define	FBS_STEP_ES_ON_PERIOD		323		/* エンドセンサON期間 (11 mm) */
#endif

/*	FBS用のモーター駆動経路の状態
**		unsigned char	SCN_MotorDriveMode;
**		1996/06/10 s.takeuchi
** 使わない(SCN_ADF/SCN_FBSを使う:sysscan.h参照)
** #define	SWM_ADF_DRIVE				0		@* ADF部を駆動 *@
** #define	SWM_MIRROR_DRIVE			1		@* ミラーキャリッジを駆動 *@
*/

/*	FBS用のミラーキャリッジの状態
**		unsigned char	SCN_MirrorCarriageStatus;
**		1996/06/24 s.takeuchi
*/
#define	MIRROR_POWER_ON			  0xFF		/* 電源ON直後で初期化が必要 */
#define	MIRROR_READY				 0		/* 待機位置(サイズ検出位置)で停止中 */
#define	MIRROR_MOVE_TO_ADF			 1		/* ADF読取り位置へ移動中 */
#define	MIRROR_ADF_READY			 2		/* ADF読取り位置で停止中 */
#define	MIRROR_MOVE_TO_HS			 3		/* ホームセンサ(HS)へ移動中 */
#define	MIRROR_HS_ON				 4		/* ホームセンサ(HS)上で停止中 */
#define	MIRROR_MOVE_FROM_HS			 5		/* ホームセンサ(HS)上から移動中 */
#define	MIRROR_MOVE_TO_READY		 6		/* 待機位置へ移動中 */
#define	MIRROR_MOVE_TO_FBS_TOP		 7		/* FBS読取り先端へ移動中 */
#define	MIRROR_FBS_SCANNING			 8		/* FBS読取り中 */
#define	MIRROR_MOVE_TO_FBS_END		 9		/* FBS読取り後端へ移動中 */
#define	MIRROR_FBS_END_STOP			10		/* FBS読取り後端で停止中 */
#define	MIRROR_ES_ON				11		/* エンドセンサ(ES)上で停止中 */
#define	MIRROR_FREEZE				12		/* 輸送用の固定位置で停止中(動作禁止) */
#define MIRROR_MOVE_FBS_END_TO_ADF	13		/* FBS読取り終了位置からADF読み取り位置へ移動中 */
#define	MIRROR_MOVE_TO_N_STEP		14		/* ホームセンサからN step移動中 */
#define	MIRROR_MOVE_TO_N_STEP_WAIT	15		/* ホームセンサからN step停止待ち */
#define	MIRROR_MOVE_ABORT			16		/* 動作中断での停止待ち */	/* 停止処理  1997/04/21 */
#define	MIRROR_MOVE_ABORT_STOP		17		/* 動作中断での停止中 */	/* 停止処理  1997/04/21 */

#define MIRROR_MOVE_OPEN			100		/* FBSカバーを開いているところ FBS DVT */
#define MIRROR_MOVE_CLOSE			101		/* FBSカバーを閉じているところ FBS DVT */

/*	FBS用のミラーキャリッジ移動タスクへの動作指定
**		unsigned char	SCN_MirrorTaskControl;
**		1996/06/25 s.takeuchi
*/
#define	MIRROR_TASK_INITIALIZE		0		/* 電源ON時の初期化(待機位置へ) */
#define	MIRROR_TASK_TO_READY		1		/* 読み取り後の初期化(待機位置へ) */
#define	MIRROR_TASK_TO_ADF			2		/* ADF読取り位置へ */
#define	MIRROR_TASK_TO_FBS			3		/* FBS待機位置(HS上)へ */
#define	MIRROR_TASK_FCOT_READY		4		/* FCOTコピー用待機位置へ */
#define	MIRROR_TASK_TRANSPORT		5		/* 輸送用の固定位置へ */
#define MIRROR_TASK_CCD_ADJUST		6		/* CCD調整位置へ */
#define MIRROR_TASK_FBS_END_TO_ADF	7		/* FBS読取り終了位置からADF読み取り位置へ */
#define MIRROR_TASK_TO_ADF_READY	8		/* ADF読取り待機位置への初期化 */
#define MIRROR_TASK_TO_FBS_READY	9		/* FBS読取り待機位置への初期化 */

/*	FBS用のミラーキャリッジ移動タスク SCN_MirrorMoveTask() の動作結果
**	ミラーキャリッジ移動結果 SCN_MirrorMoveStatus
**		1996/06/25 s.takeuchi
*/
#define	MIRROR_MOVE_OK				0		/* ミラー移動 正常終了 */
#define	MIRROR_MOVE_ERROR			1		/* ミラー移動 エラーで終了 */
#define	MIRROR_MOVE_LAMP_ERROR		2		/* ミラー移動 ランプ異常で終了 */

/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 */
#define MIRROR_MOVE_FAILURE			3
/* RXIL瞬断対策 T.Nose 1998/03/05 */
#define MIRROR_MOVE_RXIL_ABORT		4

/*	FBS用の10ms割込みでのエンドセンサ監視の状態
**		unsigned char	SCN_WatchEndSensorStatus;
**		1996/06/24 s.takeuchi
*/
#define	WATCH_ES_DISABLE			0		/* エンドセンサ監視は無効 */
#define	WATCH_ES_ON					1		/* エンドセンサONを監視中 */
#define	WATCH_ES_OFF				2		/* エンドセンサOFFを監視中 */

/*	ADF読み取りでのモーター停止制御用の状態
**		unsigned char	SCN_ADF_MotorStopRequest;
**		1996/10/28 s.takeuchi
*/
#define	ADF_MOTOR_NO_STOP			0		/* 正常動作中 */
#define	ADF_MOTOR_FEED_ERROR		1		/* フィードエラー */
#define	ADF_MOTOR_COVER_OPEN		2		/* ADFカバーオープン */
#define	ADF_MOTOR_DOC_OUT_OK		3		/* 排出正常終了 */
#define	ADF_MOTOR_GEAR_BACKLASH_END	4		/* ピックアップローラー上昇終了 */
#define	ADF_MOTOR_STOP_REQUEST		5		/* 停止キー押下 */
#define	ADF_MOTOR_MEMORY_OVER		6		/* メモリオーバー */
#define	ADF_MOTOR_MAXLINE_OVER		7		/* 最大ラインオーバー CDC_EncodePageTask() */
#define ADF_MOTOR_DOC_READY_OK		8		/* ＤＳ１ＯＮ原稿繰り込み終了 ANZU_Lのみ */
#define ADF_MOTOR_DOC_ELIMINATED	9		/* 原稿引き抜き T.Nose 1997/10/24 ANZU_Lのみ */

/*	ミラーキャリッジの待機位置
**		UBYTE SCN_MirrorReadyPosition
**		1997/05/28 T.Nose
*/
#define READY_POSITION_FBS			0		/* 待機位置 FBS 読取り位置 */
#define READY_POSITION_ADF			1		/* 待機位置 ADF 読取り位置 */

/* 各モードでの読取りのモータースピード(単位:pps)、励磁方式 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_H)
#define SCN_NORMAL_PPS				(2273) /* 2相 */
#define SCN_FINE_PPS				(1137) /* 2相 */
#define SCN_S_HFINE_PPS				(568)  /* 2相 */
#define SCN_NORMAL_EXCITE			SCN_MOTOR_2_EXCITE
#define SCN_FINE_EXCITE				SCN_MOTOR_2_EXCITE
#define SCN_S_HFINE_EXCITE			SCN_MOTOR_2_EXCITE
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
#define SCN_NORMAL_PPS				(2330) /* 2相 */
#define SCN_FINE_GRAY_PPS			(1165) /* 2相 */
#define SCN_S_HFINE_PPS				(1165) /* 1-2相 */
#define SCN_NORMAL_EXCITE			SCN_MOTOR_2_EXCITE
#define SCN_FINE_EXCITE				SCN_MOTOR_2_EXCITE
#define SCN_S_HFINE_EXCITE			SCN_MOTOR_1_2_EXCITE
#endif

/* 原稿種類 */
#define SCN_MEMCOPY_DOC	0	/* コピー         */
#define SCN_MEMTX_DOC	1	/* メモリー送信   */
#define SCN_SCNTX_DOC	2	/* スキャナー送信 */


#endif
