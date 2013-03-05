/* copy 1996/12/25 */
/* Original File : jun\usr1:\src\rice\v53\kiri\src\scn_int.c */
/***********************************************************************
*               BY:  S.Kawasaki
*             DATE:  Mar.14,1993
*        FILE NAME:  scn_sub.c
*      DESCRIPTION:	 桐スキャナー割り込み用モジュール
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*	   MODULE NAME:	UWORD	near DS2_Int(void)
*					UWORD	near IDP_Int(void)
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysscan.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\idp301.h"
#include "\src\atlanta\define\mntsw_c.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\ext_v\man_data.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mnt_pro.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\idp_pro.h"

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == R288F) */
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

/* UWORD	DebugLineInt = 0; */
/* UWORD	DebugPreLineInt = 0; */
UWORD	ORG_SENSTP_Status = 0;	/* ICHOUの読み取り中のDS2バウンス対策  1997/04/06 */

#if defined(POPLAR_L)
/* ＤＳ２チャタリング確認 T.Nose 1998/02/27 */
#include "\src\atlanta\poplar_l\define\poplport.h"
#include "\src\atlanta\define\mntsw_g.h"
#include "\src\atlanta\ext_v\sys_port.h"
static UWORD DEBUG_ScanLineCount = 0;
#endif

/* STx debug T.Nose 2000/2/11 */
UBYTE DEBUG_ScanTx = 0;

/** Module Header For CIM-E ********************************************
		module		:	[ＤＳ２割り込み処理関数 IRQ4]
		function	:	[
						ステータス・ポート：Ｃ２０７０５Ｈ
							IO_BIT_SCANEND_INT		0x0001:読み取り終了割り込み要求
							IO_BIT_SCANSTART_INT	0x0002:読み取り開始割り込み要求
							IO_BIT_DS2OFF_INT		0x0004:ＤＳ２　ＯＦＦ割り込み要求
							IO_BIT_DS2ON_INT		0x0008:ＤＳ２　ＯＮ割り込み要求
							0x0010:未使用
							0x0020:未使用
							0x0040:未使用
							0x0080:未使用
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[
			割込みエントリーのコードサイズを一定にするため void型 に変更
		]
		machine		:	[SH7043]
  		language	:	[SHC]
 		keyword		:	[INT]
     	date		:	[94/3/23]
 		author		:	[川崎真史]
************************************************************************/
static UWORD	SCN_LastStep = 0;
static UWORD	pps = 0;
static UWORD	step = 0;
static UWORD	DEBUG_SCNCount1 = 0;

void	DS2_Int(void)
{
	UBYTE int_status = 0; /** 割り込み要因待避用ＲＡＭ */

	int_status = inp(INTST0_PORT); /** ＤＳ２割り込みのステータスを読み込む */

	/** 読み取り終了割り込み */
	if ((int_status & IO_BIT_SCANEND_INT)&&(SCN_DS2INTR_Status & IO_BIT_SCAN_END_INT_ENABLE)) {
		if (SCN_DocumentStatus == SCN_DOC_DS2_OFF) { /** 原稿後端検出直後である。 */
			/* スキャナー送信以外の原稿蓄積で済みスタンプＯＮの場合この当たりで
			** スタンプの操作を入れる必要有り！！！！！
			*/

			/*--------------------------------------------------------------------------------------------------*/
			/* ＤＳ２ＯＮの割り込みはチャタリングを防止する為に、ＤＳ２　ＯＮ割り込み直後に禁止に設定している。 */
			/* そのため、原稿を読み終わるまでに、次原稿の先端が、ＤＳ２をＯＮにした場合、ＤＳ２の割り込みが禁止 */
			/* になっているため、ＤＳ２の割り込みがＧ／Ａより発生せず、結果的に繰り込み不良となる。             */
			/* この繰り込み不良を防止するため、ＤＳ２の割り込み禁止の解除を原稿の後端検出直後に入れる。         */
			/* 但し、原稿の後端検出までにＤＳ２がＯＮになる場合は、この場所から移動する必要有り。7/19/1994      */
			/*--------------------------------------------------------------------------------------------------*/

			/* 原稿排出時、モーターが回りっぱなしになる件 1997/12/22 T.Nose */
			if (DS1()) { /* 次の原稿があれば */
				SCN_SetDS2_ON_Int(SCN_ENABLE);		/** ＤＳ２　ＯＮ割り込み許可 */
			}
			else {
				SCN_SetDS2_ON_Int(SCN_DISABLE);		/** ＤＳ２　ＯＮ割り込み禁止 */
			}

			SCN_SetScanEndInt(SCN_DISABLE);
			SCN_SetSoftCTSCAN( SCN_DISABLE );	/** CTSCAN OFF  */

			/*----------------------------------------------------------*/
			/** 原稿排出後の読み取り先端がずれる件の対応 Aug.14,1994  **/
			/*----------------------------------------------------------*/
			SCN_SetStartSoftScan(SCN_DISABLE);	/** ソフト・スキャン停止 */

			SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;	/** 原稿の後端が読み取り位置を通過した */

			/* メモリー送信原稿後端縮む件
			** T.Nose 1997/10/31
			*/
			DEBUG_DocumentScanning = 0;

			SCN_EndScanLine = SCN_ReadMotorPulseCounter();
			/*------------------------------------------------------------------------------------------------*/
			/* 原稿蓄積時、最速で読み取りを行う為、読み取り終了後にモーターを停止させる必要があるかをチェック */
			/* します。停止させる条件は次の通りです。                                                         */
			/*  １．スタンプ設定がＯＮ                                                                        */
			/*	２．モード変更有り                                                                            */
			/*	３．次原稿が無い                                                                              */
			/* 	４．上記１、２、３は原稿蓄積のみチェックする。                                                */
			/*------------------------------------------------------------------------------------------------*/
			SCN_CheckMotorStop(); /** 原稿読み取り終了後にモーターを停止する必要が有るかをセット */
			if (!SCN_CheckMotorStopAfterScan()) { /** モーター停止要求がなければ */
				/** モーター制御用変数のセットが必要？？？ */
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;	/* いちょうで必要  竹内 Oct.17.1995 */
			}
			else { /** モーター停止要求がある */
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
				SCN_LastStep = 0; /** 読み取り終了後の移動距離クリア */
			}

			/**原稿後端が５３ラインに満たない時のダミーイベントを発生(５３ラインのＤＭＡ終了が発生しないから） */
			idet_evt(EVT_CDC0_DMA0_END);
			return;
		}
	}
	/** 読み取り開始割り込み */
	else if ((int_status & IO_BIT_SCANSTART_INT) && (SCN_DS2INTR_Status & IO_BIT_SCAN_START_INT_ENABLE) &&
			(SCN_DocumentStatus != SCN_DOC_FEED_OUT) &&					/* 原稿排出中でない */
#if (0)	/* DS3がないので、ここでスタンプ位置検出するために削除  1996/07/16 s.takeuchi */
//			(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_FEED_READY) &&	/* スタンプ・テスト用のフィードでない */
#endif
			(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_ON_GOING) &&		/* スタンプ・テスト実行中でない */
			(SCN_DocumentStatus != SCN_DOC_FEED_DS2ON_WAIT) &&
			(SCN_DocumentStatus != SCN_DOC_FEED_DS2OFF_WAIT) &&
			/* DS3はないので削除 (SCN_DocumentStatus != SCN_DOC_FEED_DS3ON_WAIT) &&		1996/07/16 s.takeuchi */
			(SCN_DocumentStatus != SCN_DOC_FEED_DS3OFF_WAIT)) {

		/**	スタンプテストタスクでの繰込み中の場合は、スキャンスタート割り込みを禁止して、
		**	モーターを減速させる (すぐにreturnする)
		**		ICHOUにはDS3がないので、この条件と処理を追加  1996/07/16 s.takeuchi
		*/
		if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_FEED_READY) {
			SCN_SetScanStartInt( SCN_DISABLE );
			SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_OUT_OK;
			/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
			/* SCN_AdjustMotorSpeed();  モーター割り込みでする  1996/10/28 */
			/* return (0); */
			return;
		}

		DebugLineInt = 0; /* TBD May.23,1994 */
		DebugPreLineInt = 0; /* TBD May.23,1994 */

		/* メモリー送信原稿が縮む件 1997/10/17 T.Nose */
		DEBUG_SaveLineInt = 0;
		DEBUG_SCNCount = 0;
		DEBUG_SCNCount1 = 0;

		/*-------------------------------------------------------------------------
		** 読み取り中なのになぜかモータが停止している不具合対策
		** 1997/05/10 H.Yoshikawa
		*/
		SCN_INT_Counter = 0;

		SCN_FeedErrorCheckStep = 0;

		/* Oct.15,1994 モーター脱調対策 */
		/* SCN_LatchMotorSpeedAndInterval(); */ 	/** モーター速度変更間隔、速度初期ラッチ */

		SCN_SetMotorSpeedIntervalInt(SCN_ENABLE); 	/** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */

		/*---------------------------------------------------------------*/
		/** 読み取り開始につき、読み取りラインの割り込みを初期化します。 */
		/** Aug.20,1994                                                  */
		/*---------------------------------------------------------------*/
		SCN_SpeedCheckPoint = 0;					/** ライン割り込み数管理テーブルのポインターを初期化 */
		SCN_SetLineStep(SCN_SpeedCheckLine[0]);		/** イニシャルのライン割り込み数をＧ／Ａにセット */
		SCN_SetLineInt(SCN_ENABLE);					/** ライン割り込みを許可 */

		/** 最高速ならCTSCANをONする */
		if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
			if (SCN_Control.UseType != IDP_SCANNER_TX) {
				SCN_SetSoftCTSCAN( SCN_ENABLE );
			}
			else {
#if (PRO_CCD == DPI200)	/**add By T.Yamaguchi and M.Kotani 1997/11/16*/
				if (SCN_ModeSw == SYS_SFINE)  {
					SCN_SetSoftCTSCAN( SCN_ENABLE );
				}
#else
				/* スキャナ送信でも、15.4l/mmでスキャンする時はCTSCANを立てる */
				if ((SCN_ModeSw != SYS_NORMAL) && (SCN_ModeSw != SYS_FINE))  {
					SCN_SetSoftCTSCAN( SCN_ENABLE );
				}
#endif
			}
		}

		/*----------------------------------------------------------*/
		/** 原稿排出後の読み取り先端がずれる件の対応 Aug.14,1994  **/
		/*----------------------------------------------------------*/
		SCN_SetStartSoftScan(SCN_ENABLE); 			/** ソフト・スキャン開始 */

		SCN_SetScanStartInt(SCN_DISABLE); 			/** 読み取り先端割り込み禁止 */
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {		/** ADF読み取りの場合(ICHOUではこの場合だけ) */
			SCN_SetDS2_OFF_Int(SCN_ENABLE);			/** ＤＳ２　ＯＦＦ割り込み許可 */
		}
#else
		SCN_SetDS2_OFF_Int(SCN_ENABLE);				/** ＤＳ２　ＯＦＦ割り込み許可 */
#endif
		SCN_StartMotorPulseCounter();				/** 読み取りラインカウンター起動 */
		SCN_DocumentStatus = SCN_DOC_IN_SCANNING;	/** 原稿ステータスを読み取り中にセット */

		/* メモリー送信原稿後端縮む件
		** T.Nose 1997/10/31
		*/
		DEBUG_DocumentScanning = 1;

#if (PRO_FBS == ENABLE)
		/** FBS読取りの場合は、ミラー状態を読み取り中にする */
		if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_TOP) {
			SCN_MirrorCarriageStatus = MIRROR_FBS_SCANNING;
		}
#endif

		/* ICHOUの読み取り中のDS2バウンス対策  1997/04/05 */
		SCN_DS2_BouncePoint = 0;	/** 初期化する */

		/** ICHOU FCOT用のプリント起動指示 */	/* 1996/12/12 */
		SYS_FCOT_PrintStartRequest = TRUE;
		idet_evt( EVT_FCOT_PRINT_START );

		/* 読取りページのカウント T.Nose 1997/09/20 */
		SCN_Control.ScanPage++;

#if defined(POPLAR_L)
		/* ＤＳ２チャタリング確認 T.Nose 1998/02/27 */
		DEBUG_ScanLineCount = 0;

/*		SYS_COM_PortStatus |= IO_BIT_SELMEL;
**		outpw(COM_PORT,SYS_COM_PortStatus);By Y.Suzuki 1998/03/02 */
		SYS_ETC_PortStatus |= IO_BIT_EXDMAC_RES;
		outpw(ETC_PORT,SYS_ETC_PortStatus);
#endif
		return;
	}
	/** ＤＳ２ＯＦＦ割り込み(ホームセンサＯＮ割り込み) */
	else if ((int_status & IO_BIT_DS2OFF_INT) && (SCN_DS2INTR_Status & IO_BIT_DS2_OFF_INT_ENABLE)) {

#if (PRO_FBS == ENABLE)
		if (SCN_MotorDriveMode == SCN_FBS) {	/** FBS:ミラー動作 */
			/**	ミラーがホームセンサへ移動中にホームセンサがONした場合は、モーターを停止する
			**		モーター速度、変更間隔などをセットする
			**		スルーダウンにセットする
			**		HS-ON割込みを禁止して、モーター割込みを許可する
			*/
			if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_HS) {
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
				SCN_AdjustMotorSpeed();
				/* SCN_SetMotorSpeed();  1996/10/17 */
				SCN_LatchMotorSpeedAndInterval();
				SCN_SetMotorSpeedIntervalInt( SCN_ENABLE );
				SCN_SetStartSoftScan( SCN_DISABLE );

				SCN_SetHS_ON_Int( SCN_DISABLE );

				inp( INTST1_PORT );		/* モーター割込み要因をクリアする  1996/10/17 */
			}

			/** ミラー駆動状態でのHS-ON割り込みの処理をここで終わるためreturnする */
			return;
		}
#endif	/* (PRO_FBS == ENABLE) */

		if (SCN_DocumentStatus == SCN_DOC_IN_SCANNING) {
			SCN_SetDS2_OFF_Int(SCN_DISABLE);		/** ＤＳ２　ＯＦＦ割り込み禁止 */
			SCN_SetScanEndInt(SCN_ENABLE); 			/** ＤＳ２からスキャン開始位置までのライン割り込みセット */
			SCN_DocumentStatus = SCN_DOC_DS2_OFF; 	/** 原稿ステータス変更 */

			/* ICHOUの読み取り中のDS2バウンス対策  1997/04/05 */
			SCN_DS2_BouncePoint = SCN_ReadMotorPulseCounter();	/** DS2OFF位置を記憶する */
		}
		else if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_ON_GOING) { /** スタンプテスト実行中 */
			SCN_DocumentStatus = SCN_DOC_STAMP_TEST_STOP; /** スタンプテスト停止要求 */
			SCN_SetDS2_OFF_Int(SCN_DISABLE);		/** ＤＳ２　ＯＦＦ割り込み禁止 */
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_DS2OFF_WAIT) { /**  原稿排出テスト用　ＤＳ２ＯＦＦ待ち */
			SCN_FeedErrorCheckStep = 0;
			SCN_SetDS2_OFF_Int(SCN_DISABLE);				/** ＤＳ２　ＯＦＦ割り込み禁止 */
			if (DS1()) {	/** 次原稿あり */
				SCN_DocumentStatus = SCN_DOC_FEED_DS2ON_WAIT;	/** 次原稿のＤＳ２ＯＮ待ち */
				/*	DS2のチャタリング防止  1996/10/30
				**	SCN_SetDS2_ON_Int(SCN_ENABLE);
				*/
			}
			else {			/** 次原稿なし */
				/*	DS3はないので、この状態(SCN_DOC_FEED_DS3OFF_WAIT)の意味は「原稿排出完了待ち」となる
				**	この状態の時は、モータ割り込みで排出完了ステップ分送った後、減速して停止する
				**		1996/07/15 s.takeuchi
				*/
				SCN_DocumentStatus = SCN_DOC_FEED_DS3OFF_WAIT;	/** 次原稿のDS3 OFF待ち */
			}
		}
		/* DS3はないので削除  1996/07/15 s.takeuchi */
	}
	/**	ＤＳ２ＯＮ割り込み(ホームセンサＯＦＦ割り込み) */
	else if ((int_status & IO_BIT_DS2ON_INT) && (SCN_DS2INTR_Status & IO_BIT_DS2_ON_INT_ENABLE)) {
		if (SCN_DocumentStatus == SCN_DOC_ADF_1ST_PAGE) {	/** ADF原稿の1ページ目の繰り込み中 */
			/**	ADFの1ページ目の繰込み中(モーターテーブルがSCN_xxx_FEED)なら、
			**	モーター速度整合指示する
			*/	/* ICHOUの繰り込み制御変更のため  1996/10/04 s.takeuchi */
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_ADJUST;
			SCN_AdjustMotorSpeed();
			SCN_FeedErrorCheckStep = 0;
			SCN_DocumentStatus = SCN_DOC_READY;
			SCN_SetDS2_ON_Int( SCN_DISABLE );	/** DS2 ON割り込み禁止 */
			SCN_SetScanStartInt( SCN_ENABLE );	/** 読み取り先端割り込み許可 */
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_DS2ON_WAIT) {
			SCN_FeedErrorCheckStep = 0;
			SCN_SetDS2_ON_Int(SCN_DISABLE);				/** ＤＳ２　ＯＮ割り込み禁止 */
			/*	DS2のチャタリング防止  1996/10/30
			**	SCN_SetDS2_OFF_Int(SCN_ENABLE);
			*/
			SCN_DocumentStatus = SCN_DOC_FEED_DS2OFF_WAIT;	/** DS2 OFF待ち */
			idet_evt(EVT_DOC_PAGE_COUNT); /* 排出ページ数カウントアップ指示 T.Nose 1997/05/29 */
		}
		/* ICHOUにはDS3がないので、ここの条件と処理を追加  1996/07/16 s.takeuchi */
		else if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_FEED_READY) {
			/**	DS2ON割り込みを禁止し、スキャンスタート割り込みを許可する */
			SCN_SetDS2_ON_Int( SCN_DISABLE );
			SCN_SetScanStartInt( SCN_ENABLE );
		}
#if (PRO_DOC_IN == ENABLE)
		else if (SCN_DocumentStatus == SCN_DOC_MOVE_TO_READY) { /** 原稿繰り込み中なら */
			SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_READY_OK; /* 繰り込みを止める */
			SCN_SetDS2_ON_Int( SCN_DISABLE ); /* DS2 ON 割込み禁止 */
			SCN_SetScanStartInt( SCN_ENABLE );
		}
#endif
		else {	/* SCN_DOC_READY */
#if (PRO_FBS == ENABLE)
			/**	ミラーがADF読取り位置で、ADFを駆動中の場合は、
			**	ADF読取り中なので、従来の処理をする
			*/
			if ((SCN_MirrorCarriageStatus == MIRROR_ADF_READY)
			&&	(SCN_MotorDriveMode == SCN_ADF)) {		/* ADF読取り中 */
				if ((SCN_DocumentStatus != SCN_DOC_FEED_OUT)
				&&	(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_FEED_READY)
				&&	(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_ON_GOING)) {
					SCN_SetDS2_ON_Int(SCN_DISABLE);			/** ＤＳ２　ＯＮ割り込み禁止 */
					SCN_SetScanStartInt(SCN_ENABLE);		/** 読み取り先端割り込み許可 */
				}
			}
			/**	ミラーがホームセンサから「FBS原稿先端へ移動中」にホームセンサがOFFした場合は、
			**	スルーアップしてFBS原稿の読取り開始待ちにする
			**		モーター速度、変更間隔などをセットして、G/Aの割込み間隔を初期ラッチで初期化
			**		モーターパルスカウンタを０クリアして、カウントを開始する
			**		HS-OFF割込みを禁止して、スキャンスタート割込みとモーター割込みを許可する
			*/	/* ICHOU用  1996/06/27 s.takeuchi */
			else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_TOP) {
				SCN_SetMotorSpeed();
				SCN_LatchMotorSpeedAndInterval();
				SCN_MirrorMotorPulseCount = 0;

				SCN_SetHS_OFF_Int( SCN_DISABLE );
				SCN_SetScanStartInt( SCN_ENABLE );
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;		/* モーター加速 */
			}
			/**	ミラーがホームセンサから「待機位置へ移動中」にホームセンサがOFFした場合は、
			**	そのまま一定速度で待機位置まで移動する
			**		モーター速度、変更間隔などをセットして、G/Aの割込み間隔を初期ラッチで初期化
			**		モーターパルスカウンタを０クリアして、カウントを開始する
			**		HS-OFF割込みを禁止して、モーター割込みを許可する
			*/	/* ICHOU用  1996/06/27 s.takeuchi */
			else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_READY) {
				/* SCN_SetMotorSpeedIntervalInt( SCN_ENABLE );  元から許可のため不要 1996/08/29 */
				SCN_LatchMotorSpeedAndInterval();
				SCN_MirrorMotorPulseCount = 0;

				SCN_SetHS_OFF_Int( SCN_DISABLE );
				/* SCN_SetMotorSpeedIntervalInt( SCN_ENABLE );  元から許可のため不要 1996/08/29 */
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_CONSTANS;  途中では変えない 1996/08/29 */
			}
			/**	ミラーが「ホームセンサからN step移動中」なら
			**	モーター割り込みステップに指定ステップを書き込み初期ラッチする
			*/	/* ICHOU用  1997/02/15 s.takeuchi */
			else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_N_STEP) {
				inp( INTST1_PORT );		/* モーター割り込み要因をクリアする */
				SCN_N_StepRemain = SCN_StepFromHS_Off;	/* 輸送モード停止位置がずれるため  1997/06/05 */
				SCN_SetHS_OFF_Int( SCN_DISABLE );
				SCN_LatchMotorSpeedAndInterval();
				SCN_MirrorMotorPulseCount = 0;
			}
#else /* (PRO_FBS == ENABLE) */
			if ((SCN_DocumentStatus != SCN_DOC_FEED_OUT)
			&&	(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_FEED_READY)
			&&	(SCN_DocumentStatus != SCN_DOC_STAMP_TEST_ON_GOING)) {
				SCN_SetDS2_ON_Int(SCN_DISABLE);			/** ＤＳ２　ＯＮ割り込み禁止 */
				SCN_SetScanStartInt(SCN_ENABLE);		/** 読み取り先端割り込み許可 */
			}
#endif /* (PRO_FBS == DISABLE) */
		}
	}
	return;
}


/** Module Header For CIM-E ********************************************
		module		:	[ＩＤＰ割り込み処理関数 INT 2]
		function	:	[
						ステータス・ポート：４０８Ｈ
							0x0001:未使用
							0x0002:未使用
							IO_BIT_LACT		0x0004:０：保存ライン、１：縮小ライン
							0x0008:未使用
							0x0010:未使用
							0x0020:未使用
							0x0040:未使用
							0x0080:未使用
						]
  		return		:	[
  						０：イベントの発生無し
  						１：イベントの発生有り
  						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/23]
 		author		:	[川崎真史]
************************************************************************/
UWORD	IDP_Int(void)
{
	UBYTE int_status = 0;

	int_status = inp(RED_PORT); /** IDP割り込みのステータスを読み込む */

	if (int_status & IO_BIT_LACT) { /** 縮小ラインであれば */
		/** ＩＤＰでの縮小をするのであれば縮小率を再度設定する必要有り */
	}
	return (0);
}
/** Module Header For CIM-E ********************************************
		module		:	[スキャナー割り込み処理関数 INT XX]
		function	:	[
						ステータス・ポート：４０６Ｈ
							IO_BIT_LINE_INT		0x0001:ライン割り込み要求
							IO_BIT_MOTOR_INT	0x0002:モーター割り込み要求
							0x0004:未使用
							0x0008:未使用
							0x0010:未使用
							0x0020:未使用
							0x0040:未使用
							0x0080:未使用
						]
  		return		:	[
  						０：イベントの発生無し
  						１：イベントの発生有り
  						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/23]
 		author		:	[川崎真史]
************************************************************************/
UWORD	SCN_Int( void )
{
	UBYTE int_status;
	UWORD	DebugSCN_Int = 0;

	int_status = inp(INTST1_PORT);

	if ((SCN_DocumentStatus == SCN_DOC_IN_SCANNING) ||		/** 原稿SCANNINGなら */
		(SCN_DocumentStatus == SCN_DOC_DS2_OFF)) {			/* 原稿読取り中でDS2 OFF検出直後なら*/
		/** 先ず原稿のステータス SCN_DocumentStatusをチェック */

		DebugLineInt = SCN_ReadMotorPulseCounter();
		if (DebugLineInt < DEBUG_SaveLineInt) {
			DEBUG_SCNCount++;
		}
		DEBUG_SaveLineInt = DebugLineInt;
		if (DEBUG_SCNCount1 == 1) {
			if (SCN_ReadMotorPulseCounter() > 600) {
				SCN_SetSoftCTSCAN( SCN_DISABLE );	/** CTSCAN OFF */
			}
		}

		/*-------------------------------------------------------------------------
		** 読み取り中なのになぜかモータが停止している不具合対策
		** 1997/05/10 H.Yoshikawa
		*/
		SCN_INT_Counter = DebugLineInt;

		/* ICHOUの読み取り中のDS2バウンス対策  1997/04/05 */
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {
#endif
			if ((SCN_DS2_BounceMaxStep != 0)
			 && (SCN_DS2_BouncePoint != 0)) {	/** ADF読み取り中にDS2OFF割り込みがあった */
				if (SCN_DS2_BouncePoint+SCN_DS2_BounceMaxStep <= SCN_ReadMotorPulseCounter()) {	/** 収束した */
					if (DS2()) {	/** DS2がONしている */
						/** バウンス発生とみなして読み取り中に戻す */
						SCN_DocumentStatus = SCN_DOC_IN_SCANNING;

						/** DS2OFF割り込み待ちに戻す */
						SCN_SetScanEndInt( SCN_DISABLE );
						SCN_SetDS2_OFF_Int( SCN_ENABLE );

						/** 本来のSCANENDステップ(レジスタ)を一時記憶しておく */
						ORG_SENSTP_Status = SCN_SENSTP_Status;

						/**	SCANENDカウンタを止めるために一旦0をセットする(要因は残る) */
						SCN_SetScanEndStep( 0 );

						/** 再度SCANENDカウンタに本来の値をセットし初期ラッチする */
						SCN_SetScanEndStep( ORG_SENSTP_Status / 10 );

						/** バウンスの発生を保守スイッチに立てる */
						SYB_MaintenanceSwitch[MNT_SW_C6] |= DS2_BOUNCE_DETECT;
					}
					SCN_DS2_BouncePoint = 0;	/** 初期化する */
				}
			}
#if (PRO_FBS == ENABLE)
		}
#endif

	}

	/*-----------------------------------------------------------------------------------*/
	/*  デバッグ用に一時的に入れます。 Nov.10,1994                                       */
	/*  次の３行分                                                                       */
	/*-----------------------------------------------------------------------------------*/
	if ((int_status & IO_BIT_LINE_INT) && !(SCN_SCCNT_Status & IO_BIT_LINE_INT_ENABLE)) {
		DebugSCN_Int++;
	}
	/*--------------------------------*/
	/* ライン割り込み要求に対する処理 */
	/*--------------------------------*/
	if ((int_status & IO_BIT_LINE_INT) && (SCN_SCCNT_Status & IO_BIT_LINE_INT_ENABLE)) {

		/** 先ず原稿のステータス SCN_DocumentStatusをチェック */
		if ((SCN_DocumentStatus == SCN_DOC_IN_SCANNING) ||		/** 原稿SCANNINGなら */
			(SCN_DocumentStatus == SCN_DOC_DS2_OFF)) {			/* 原稿読取り中でDS2 OFF検出直後なら*/

			if ((DebugLineInt - DebugPreLineInt) >= 53 ) {
				DebugPreLineInt = DebugLineInt;
			}
			else {
				DebugPreLineInt = DebugLineInt;
			}

			if (SCN_SpeedCheckPoint != SCN_SPEED_CHECK_NOT_NEED) { /** エンコードが終了していない。 */

				/*-----------------------------------------------------------------------------------*/
				/*  デバッグ用に一時的に入れます。 Nov.10,1994                                       */
				/*  次の３行分                                                                       */
				/*-----------------------------------------------------------------------------------*/
				if ((SCN_SpeedCheckPoint == 0) && ((SCN_Debug53Lines-DebugLineInt) <= 30)) {
					DebugSCN_Int++;
				}

				SCN_SpeedCheckPoint++; /** ライン割り込み数管理テーブルのポインターを更新 */

				/*---------------------------------------------------------------------------*/
				/** 原稿のステータス次第で、３２Ｋのバッファの状態を確認（エンコード中か？） */
				/*---------------------------------------------------------------------------*/
				if (CDC_ImageBufferStatus[0] == CDC_NOT_ACCESS) { /** Ａ面、Ｂ面共にエンコード終了 */
					/*-----------------------------------------------------------------------------------*/
					/*  デバッグ用に一時的に入れます。 Nov.10,1994                                       */
					/*  次の３行分                                                                       */
					/*-----------------------------------------------------------------------------------*/
					SCN_SetLineStep(3);	/** ４ライン割り込み数をＧ／Ａにセット */

					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP; /** 従い、モーターのスピードの変更無し */
					SCN_SpeedCheckPoint = SCN_SPEED_CHECK_NOT_NEED; /* エンコードが終了。 */

					/* STx debug T.Nose 2000/2/11 */
					DEBUG_ScanTx = 0;

					/*---------------------------------------*/
					/** モーターの速度を最適な値にセットする */
					/** Aug.22,1994                          */
					/*---------------------------------------*/
					SCN_AdjustMotorSpeed();
					return(0);	/** モーターの割り込みがあっても処理する必要無し*/
				}
				else { /** Ａ面又はＢ面がエンコード中 */
					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN; /** 減速指示 */
					SYB_MaintenanceSwitch[MNT_SW_C3] |= 0x80;
					/*---------------------------------------*/
					/** モーターの速度を最適な値にセットする */
					/*---------------------------------------*/
					SCN_AdjustMotorSpeed();

					/* STx debug T.Nose 2000/2/11 */
					if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
						DEBUG_ScanTx = 1;
					}

					/*  Nov.14,1994 SCN_SetLineInt(SCN_DISABLE);	*//** ライン割り込みをDISABLE Nov.9,1994 */
					SCN_SetLineStep(SCN_SpeedCheckLine[SCN_SpeedCheckPoint]);	/** ライン割り込み数をＧ／Ａにセット */
					SCN_SetLineInt(SCN_ENABLE);					/** ライン割り込みを許可 */
					return(0);
				}
			}
		}
	}
	else {		/* モーター割込みでも、読取り中でエンコードが遅れた時に読取りを止めるため */

		/** 先ず原稿のステータス SCN_DocumentStatusをチェック */
		if ((SCN_DocumentStatus == SCN_DOC_IN_SCANNING) ||	/** 原稿SCANNINGなら */
			(SCN_DocumentStatus == SCN_DOC_DS2_OFF)) {		/* 原稿読取り中でDS2 OFF検出直後なら*/


			if ((DebugLineInt - DebugPreLineInt) > 50) {
				DEBUG_SCNCount++;
			}
			if (SCN_SpeedCheckPoint != SCN_SPEED_CHECK_NOT_NEED) { /** エンコードが終了していない。 */
				if ((DebugLineInt - DebugPreLineInt) > (SCN_SpeedCheckLine[SCN_SpeedCheckPoint]+5)) {
					DebugPreLineInt = DebugLineInt;

#if (PRO_FBS == ENABLE)		/* ICHOU用 */
					/*	読み取り中のモーター割込みでは、下のモーター割り込み処理を通らないので
					**	FBSのミラーの移動量はここでカウントする  1996/09/09
					*/
					/** ミラーキャリッジ駆動の場合、モーターの移動量をカウントする */
					if (SCN_MotorDriveMode == SCN_FBS) {
						SCN_MirrorMotorPulseCount += SCN_MotorIntStep;
					}
#endif

					/*---------------------------------------------------------------------------*/
					/** 原稿のステータス次第で、３２Ｋのバッファの状態を確認（エンコード中か？） */
					/*---------------------------------------------------------------------------*/
					if (CDC_ImageBufferStatus[0] == CDC_NOT_ACCESS) { /** Ａ面、Ｂ面共にエンコード終了 */
						/*-----------------------------------------------------------------------------------*/
						/*  デバッグ用に一時的に入れます。 Nov.10,1994                                       */
						/*  次の３行分                                                                       */
						/*-----------------------------------------------------------------------------------*/
						SCN_SetLineStep(3);	/** ４ライン割り込み数をＧ／Ａにセット */

						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP; /** 従い、モーターのスピードの変更無し */
						SCN_SpeedCheckPoint = SCN_SPEED_CHECK_NOT_NEED; /* エンコードが終了。 */
						/*---------------------------------------*/
						/** モーターの速度を最適な値にセットする */
						/** Aug.22,1994                          */
						/*---------------------------------------*/
						SCN_AdjustMotorSpeed();
						return(0);	/** モーターの割り込みがあっても処理する必要無し*/
					}
					else { /** Ａ面又はＢ面がエンコード中 */
						/*	LineIntと同じように、スルーダウン後停止するように変更  1996/10/28
						**	SCN_StopMotor();
						**	SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
						*/
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN; /** 減速指示 */

						SCN_SetSoftCTSCAN( SCN_DISABLE );	/** CTSCAN OFF */
						return(0);
					}
				}
				else {
				/*	DebugPreLineInt = DebugLineInt; */
				}
			}
			else {
				DebugPreLineInt = DebugLineInt;
			}
		}
	}


	 /** モーター速度変更割り込み発生 */
	if ((int_status & IO_BIT_MOTOR_INT) && (SCN_MTCNT_Status & IO_BIT_MOTOR_INT_ENABLE)) {

#if (PRO_FBS == ENABLE)		/* ICHOU用 */

		if (SCN_MotorDriveMode == SCN_FBS) {	/** ミラーキャリッジ駆動の場合 */

			/** モーターの移動量をカウントする */
			SCN_MirrorMotorPulseCount += SCN_MotorIntStep;

			if (SCN_MirrorMoveStatus == MIRROR_MOVE_OK) {	/** ミラー正常動作中 */
				/*
				**	FBS原稿読取りで動作中のモーター割込みに対する処理
				**	ミラー移動タスクで動作中のモーター割込みに対する処理
				*/
				if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_TOP) {	/** HSからFBS原稿先端への移動中 */

					/**	HS-ON区間のステップ以上送ったのに、まだホームセンサがONなら
					**	ミラーエラーとして、スルーダウン→停止する
					*/
					if ((SCN_MirrorMotorPulseCount > FBS_STEP_HS_ON_PERIOD) && HS()) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
						SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
						/*	ミラーエラーの状況:
						**		TxモーターがFBS側で回っていない
						**		ホームセンサが死んでる
						**		センサのブレードが破損
						*/
						SYB_MaintenanceSwitch[MNT_SW_C5] = 1;	/* エラーコードをセット */
					}

					/** モーター速度を合わせる */
					SCN_AdjustMotorSpeed();
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_FBS_SCANNING) {	/** FBS読取り中 */
					/**	FBSの1ページのエンコードが終了していたら、
					**	FBS読取りは終了して、ミラーは空送り状態にする
					**	(符号化タスクでSCN_DocumentStatusがSCN_DOC_END_OF_SCANになる)
					*/
					if (SCN_DocumentStatus == SCN_DOC_END_OF_SCAN) {
						SCN_SetSoftCTSCAN( SCN_DISABLE );
						SCN_SetStartSoftScan( SCN_DISABLE );
						SCN_EndScanLine = SCN_ReadMotorPulseCounter();

						SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_FBS_END;
					}

					/** モーター速度を合わせる */
					SCN_AdjustMotorSpeed();
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_FBS_END) {	/** 読取り後の空送り中 */
					/* モーターステップがFBS最大原稿長に達していたら
					** 減速指示
					*/
					if (SCN_MirrorMotorPulseCount >= FBS_STEP_HS_TO_FBS_END) {
						/* モーター速度が最終速度に達していなければ引き続き減速指示 */
						if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_CONSTANS) {
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
						}
					}
					/** モーター速度を合わせる */
					SCN_AdjustMotorSpeed();
					if (SCN_MotorTablePoint == SCN_MotorPointer->LowSpeed) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_CONSTANS;
					}
					/* エンドセンサＯＦＦ監視状態なら、ＦＢＳシェーディング位置へ移動中なので
					** この割り込みで停止して、ＦＢＳシェーディング位置で待機中とする
					*/
					if (SCN_WatchEndSensorStatus == WATCH_ES_OFF) {
						SCN_StopMotor();
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
						SCN_MirrorCarriageStatus = MIRROR_FBS_END_STOP;
					}
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_HS) {	/** HS上(FBS待機位置)へ移動中 */
					SCN_AdjustMotorSpeed();	/** モーター速度を合わせる */

					/**	FBSの最大稼働step以上送ったのに、まだホームセンサに達しない場合は
					**	ミラーエラーとして、スルーダウン→停止する
					*/
					if (SCN_MirrorMotorPulseCount > FBS_STEP_MAXIMUM) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
						SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
						/*	ミラーエラーの状況:
						**		TxモーターがFBS側で回っていない
						**		ホームセンサが死んでる
						**		センサのブレードが破損
						*/
						SYB_MaintenanceSwitch[MNT_SW_C5] = 2;	/* エラーコードをセット */
					}

					/** モーター停止時にホームセンサONなら、ホームセンサ上で停止中とする */
					if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
						/* プリンタカバーが開いているときはＨＳを見ない T.Nose */
						if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
						 && (SCN_MirrorMoveStatus != MIRROR_MOVE_RXIL_ABORT)) {	/* RXIL瞬断対策 T.Nose 1998/03/04 */
							if (HS()) {
								SCN_MirrorCarriageStatus = MIRROR_HS_ON;
							}
							else {
								SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
								/*	ミラーエラーの状況:
								**		ホームセンサが死んでる
								**		停止時にホームセンサを通り越した
								*/
								SYB_MaintenanceSwitch[MNT_SW_C5] = 3;	/* エラーコードをセット */
							}
						}
					}
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_READY) {	/** 待機位置へ移動中 */
					/**	モーターステップがHS-ONからの待機位置に達していたら
					**	スルーダウンで停止する
					*/
					if (SCN_MirrorMotorPulseCount >= FBS_STEP_HS_TO_READY) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
					}

					/** モーター速度を合わせ、止まれば待機位置で停止中とする */
					SCN_AdjustMotorSpeed();
					if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
						SCN_MirrorCarriageStatus = MIRROR_READY;
					}
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_ADF) {		/** ADF読取り位置へ */
					/** モーター速度を合わせる */
					SCN_AdjustMotorSpeed();
					if (SCN_MotorTablePoint == SCN_MotorPointer->LowSpeed) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_CONSTANS;
					}

					/**	エンドセンサ監視状態が無効なら、ADF読取り位置へ移動中なので
					**	この割り込みで停止して、ADF読取り位置で待機中とする
					**	(エンドセンサを越えるまでは10ms割込みで制御する)
					*/
					if (SCN_WatchEndSensorStatus == WATCH_ES_DISABLE) {
						SCN_StopMotor();
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
						SCN_MirrorCarriageStatus = MIRROR_ADF_READY;
					}
					/**	HS～ESのステップ以上送ったのに、まだエンドセンサがONしないなら
					**	ミラーエラーとして、スルーダウン→停止する
					*/
					else if ((SCN_WatchEndSensorStatus == WATCH_ES_ON)
					&&	(SCN_MirrorMotorPulseCount > FBS_STEP_HS_TO_ES)) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
						SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
						/*	ミラーエラーの状況:
						**		TxモーターがFBS側で回っていない
						**		エンドセンサが死んでる
						**		センサのブレードが破損
						*/
						SYB_MaintenanceSwitch[MNT_SW_C5] = 4;	/* エラーコードをセット */
					}
					/**	ES-ON区間のステップ以上送ったのに、まだエンドセンサがONなら
					**	ミラーエラーとして、スルーダウン→停止する
					*/
					else if ((SCN_WatchEndSensorStatus == WATCH_ES_OFF)
					&&	(SCN_MirrorMotorPulseCount > FBS_STEP_ES_ON_PERIOD)) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
						SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
						/*	ミラーエラーの状況:
						**		エンドセンサ上でモーターが動かなくなった
						*/
						SYB_MaintenanceSwitch[MNT_SW_C5] = 5;	/* エラーコードをセット */
					}
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_N_STEP) {	/** N step移動中 */
					/* if (SCN_StepFromHS_Off < 0x2000/2) @  1997/06/05 */
					if (SCN_N_StepRemain < 0x2000/2) {
						/** モーター割り込みの最大値ステップ/2より少なければ
						**	そのステップ数を割り込みステップとしてセットして
						**	停止待ちにする(次のモーター割り込みで停止する)
						*/
						/* SCN_SetMotorIntStep( SCN_StepFromHS_Off, SCN_MotorPointer->ExciteMethod );  1997/06/05 */
						SCN_SetMotorIntStep( SCN_N_StepRemain, SCN_MotorPointer->ExciteMethod );
						SCN_LatchMotorSpeedAndInterval();
						SCN_MirrorCarriageStatus = MIRROR_MOVE_TO_N_STEP_WAIT;
					}
					else {
						/**	まわしたステップを残りステップから引く */
						/* SCN_StepFromHS_Off -= SCN_MotorIntStep;  1997/06/05 */
						SCN_N_StepRemain -= SCN_MotorIntStep;
					}
				}
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_TO_N_STEP_WAIT) {	/** N step停止待ち */
					SCN_StopMotor();
					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
					SCN_MirrorCarriageStatus = MIRROR_FREEZE;	/* 停止 */
				}
				/* 正規の動作で停止させるため追加  1997/04/21 */
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_ABORT) {	/** 中断停止待ち */
					/** モーター速度を合わせ、止まれば停止中とする */
					SCN_AdjustMotorSpeed();
					if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
						SCN_MirrorCarriageStatus = MIRROR_MOVE_ABORT_STOP;	/* 停止 */
					}
				}
				/* ミラーキャリッジ待機位置切り替え可能仕様 */
				else if (SCN_MirrorCarriageStatus == MIRROR_MOVE_FBS_END_TO_ADF) { /* FBS読取り終了位置からADF読み取り位置へ移動中 */
					if (SCN_WatchEndSensorStatus == WATCH_ES_DISABLE) {
						SCN_StopMotor();
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
						SCN_MirrorCarriageStatus = MIRROR_ADF_READY;
					}
					else if (SCN_WatchEndSensorStatus == WATCH_ES_OFF) {
						if (SCN_MirrorMotorPulseCount > FBS_STEP_ES_ON_PERIOD) {
							SCN_StopMotor();
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							SCN_MirrorMoveStatus = MIRROR_MOVE_ERROR;
							/*	ミラーエラーの状況:
							**		エンドセンサ上でモーターが動かなくなった
							*/
							SYB_MaintenanceSwitch[MNT_SW_C5] = 9;	/* エラーコードをセット */
						}
					}
				}
				/* ＦＢＳカバー開閉ＤＶＴ */
				else if ((SCN_MirrorCarriageStatus == MIRROR_MOVE_OPEN)
				 || (SCN_MirrorCarriageStatus == MIRROR_MOVE_CLOSE)) {
					if (SCN_MirrorMotorPulseCount >= SCN_DocExitTopSpeedCount) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
					}
					SCN_AdjustMotorSpeed();
					if ((SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP)
					 && (SCN_MirrorCarriageStatus == MIRROR_MOVE_OPEN)) {
						SCN_MotorCurrentStopCounter = 0; /* 開いて止まった時は励磁を止めない */
					}
				}
			}
			else {		/** ミラー動作 異常時 */
				/** モーター速度を合わせる(止まるまで減速するだけ) */
				SCN_AdjustMotorSpeed();
			}

			/** モーターが停止すると、ミラーキャリッジ動作終了のイベントを発行する */
			if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
				SCN_IsMirrorMoveEnd = TRUE;
				return ( EVT_MIRROR_MOVE_END );
			}

			/** ミラー駆動状態での処理をここで終わるためreturnする */
			return (0);
		}
#endif	/* (PRO_FBS == ENABLE) */

		/** モーターの移動量をカウントする */
		SCN_FeedErrorCheckStep += SCN_MotorIntStep;

#if defined(POPLAR_L)
		/* ＤＳ２チャタリング確認 T.Nose 1998/02/27 */
		if (SCN_DocumentStatus == SCN_DOC_IN_SCANNING) {
			DEBUG_ScanLineCount += SCN_MotorIntStep;;
			if (DEBUG_ScanLineCount >= (UWORD)(SYB_MaintenanceSwitch[MNT_SW_G1] * 40)){
/*				SYS_COM_PortStatus &= ~IO_BIT_SELMEL;
**				outpw(COM_PORT,SYS_COM_PortStatus);By Y.Suzuki 1998/03/02 */
				SYS_ETC_PortStatus &= ~IO_BIT_EXDMAC_RES;
				outpw(ETC_PORT,SYS_ETC_PortStatus);
			}
		}
#endif

		/** ADFモータの停止要求があれば、完全に止まるまで減速して、
		**	停止後、発生したスキャナエラーのイベントをreturnする
		**	(モーターが完全に止まるまで、上位を待たせるため  1996/10/28)
		*/
		if (SCN_ADF_MotorStopRequest != ADF_MOTOR_NO_STOP) {
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;	/* ADF停止要求時はここで減速指定する  1996/11/15 */
			SCN_AdjustMotorSpeed();

			if (SCN_MotorSpeedControl == SCN_MOTOR_SPEED_STOP) {
/*
** スキャナ送信終了後、必ず、CodecPageStatus = CDC_DOC_ERRORがセットされてしまいます
** POPLAR_Hはスキャナ送信の後、受領証を取りにいくパスで問題になるので
** ここでは繰り込み不良の場合のみセットするように変更します
** POPLAR_H以外は、受領証のパスはソフトコーデックでカバーしていますが気持ち悪いのでおおもとを修正します
** by T.Soneoka 1998/01/22
*/
#if (0)
//				if (SCN_Control.UseType == IDP_SCANNER_TX) {
//					CodecPageStatus = CDC_DOC_ERROR;	/* STx符号化タスクを止めるため  1996/11/29 */
//				}
#endif
				switch (SCN_ADF_MotorStopRequest) {
				case	ADF_MOTOR_FEED_ERROR:			/* 繰り込み不良 */
					/* 上での処理をここにもってきました by T.Soneoka 1998/01/22 */
					if (SCN_Control.UseType == IDP_SCANNER_TX) {
						CodecPageStatus = CDC_DOC_ERROR;	/* STx符号化タスクを止めるため  1996/11/29 */
					}
					return (EVT_SCN_FEED_ERROR);
					break;
				case	ADF_MOTOR_COVER_OPEN:			/* ADFカバーオープン */
					return (EVT_SCN_COVER_OPEN);
					break;
				case	ADF_MOTOR_DOC_OUT_OK:			/* 原稿排出正常終了 */
					return (EVT_SCN_DOC_OUT_OK);
					break;
#if (PRO_DOC_IN == ENABLE)
				case	ADF_MOTOR_DOC_READY_OK:			/* 原稿繰り込み正常終了 */
					return(EVT_SCN_DOCUMENT_SET_OK);
					break;
				case	ADF_MOTOR_DOC_ELIMINATED:		/* 原稿繰り込み中の引き抜き T.Nose 1997/10/24 */
					return(EVT_SCN_NO_DOC);
					break;
#endif
				}
			}
			return (0);
		}

#if (PRO_DOC_IN == ENABLE)
		if (SCN_DocumentStatus == SCN_DOC_MOVE_TO_READY) { /* 待機位置へ原稿繰り込み中 */
			if (TXIL()) {	/** ADFカバーオープン */
				SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
				return (0);
			}
			if (!DS1()) {	/** 原稿が引き抜かれた */
				SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_ELIMINATED;
				return (0);
			}
			if (SCN_FeedErrorCheckStep > SCN_DS1_TO_READY_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
			}
			SCN_AdjustMotorSpeed();
		}
#else
		if (SCN_DocumentStatus == SCN_DOC_ADF_1ST_PAGE) {	/** 1ページ目の原稿繰り込み中(DS1→DS2)なら */
			if (TXIL()) {	/** ADFカバーオープン */
				SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				return (0);
			}
#if (PRO_FBS == ENABLE) || (PRO_UPPER_COVER == ENABLE)	/* 1998/01/19  By T.Yamaguchi */
			if (SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_BOOK_OPEN)) {	/** FBSカバーオープン(APS) */
				SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
				return (0);
			}
#endif
			if (!DS1()) {	/** 原稿が引き抜かれた */
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				return (0);
			}
			if (SCN_FeedErrorCheckStep > SCN_DS1_TO_DS2_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				/* 一ヶ所で行う  1996/11/29
				*	if (SCN_Control.UseType == IDP_SCANNER_TX) {
				*		CodecPageStatus = CDC_DOC_ERROR;
				*	}
				*/
			}
			SCN_AdjustMotorSpeed();
		}
#endif /* (PRO_DOC_IN == DISABLE) */
		else if (SCN_DocumentStatus == SCN_DOC_EXITING) { /** (読み取り後の)原稿排出中なら */
			/* ICHOUにはDS3がないので、排出不良検出などの処理を変更  1996/09/20 s.takeuchi */

			/**	最高速でまわしてる状態で、DS1とDS2のどちらにも原稿がない状態になったときに
			**	次のモーター割り込みでスルーダウンして停止させると、原稿が排出できる
			**		ICHOUではDS3がなく、更に待機状態では繰込まないため  1996/07/18 s.takeuchi
			*/
			if (!DS1() && !DS2()) {
				if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
					if (SCN_DocExitTopSpeedCount <= 0) {
						SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_OUT_OK;
						/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
						return (0);
					}
					else {
						/* SCN_DocExitTopSpeedCount--; */
						SCN_DocExitTopSpeedCount -= SCN_MotorIntStep;
					}
				}
			}
			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_GEAR_BACK_LASH) { /** Gear Back Lash */
			SCN_StopMotor();
			SCN_DocumentStatus = SCN_DOC_NO_DOCUMENT;
			return (EVT_SCN_GEAR_BACK_LASH_END);
		}
		else if (SCN_DocumentStatus == SCN_DOC_END_OF_SCAN) { /** Last Exit */
			if (!SCN_CheckMotorStopAfterScan()) { /** モーター停止要求がなければ */
			}
			else { /** モーターの停止要求が有る */
				if (SCN_MotorTablePoint == SCN_MotorPointer->LowSpeed) { /** 最終速度の設定なら */
					/** モータ速度とスタンプ位置までのステップを設定する */
					pps = SCN_MotorPointer->ThroughUpDownTable[SCN_MotorTablePoint].PPS;
					step = ADF_READ_POINT_TO_STAMP - ADF_DOC_EDGE_TO_STAMP - SCN_LastStep;
					SCN_SetMotorPulseRate( pps );
					SCN_SetMotorIntStep( step, SCN_MotorPointer->ExciteMethod );

					SCN_LatchMotorSpeedAndInterval(); /** モーター速度変更間隔、速度初期ラッチ */

					++SCN_MotorTablePoint; /** モーターテーブルを減速 */
				}
				else {
					/** 読み取り終了後の原稿の移動距離を加算 */
					SCN_LastStep += SCN_MotorIntStep;
					/*---------------------------------------*/
					/** モーターの速度を最適な値にセットする */
					/*---------------------------------------*/
					SCN_AdjustMotorSpeed();
				}
			}
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_READY) {
			/*---------------------------------------*/
			/** モーターの速度を最適な値にセットする */
			/*---------------------------------------*/
			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_READY) { /** Last Exit */
			/** モーターステップ数とDS2からREAD POINTまでの繰り込み不良検出ステップを比較 */
			if (SCN_FeedErrorCheckStep > SCN_DS2_TO_READ_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				/* 一ヶ所で行う  1996/11/29
				*	if ( SCN_Control.UseType == IDP_SCANNER_TX ) {
				*		CodecPageStatus = CDC_DOC_ERROR;
				*	}
				*/
				return (0);
			}

			/**	読取りフィード用のモーターテーブル(SCN_xxx_FEED)で最終速度なら、
			**	読取り用のモーターテーブルに切替えて最高速とし、スルーアップを指定する
			**		ICHOUの繰り込み制御変更のため  1996/10/04 s.takeuchi
			*/
			if (SCN_MotorTablePoint == SCN_MotorPointer->LowSpeed) {
				switch (SCN_VerticalMode) {
				case	SCN_NORMAL_FEED:
					SCN_VerticalMode = SCN_NORMAL;
					break;
				case	SCN_FINE_FEED:
					SCN_VerticalMode = SCN_FINE;
					break;
				case	SCN_SFINE_FEED:
					SCN_VerticalMode = SCN_SFINE;
					break;
				}
				SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];
				SCN_MotorTablePoint = SCN_MotorPointer->TopSpeed;
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;
			}
			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_OUT) { /** (停止キーなどでの)原稿排出中なら */
			/** モーターステップ数と読み取り終了後から排出までの繰り込み不良検出ステップを比較 */
			if (SCN_FeedErrorCheckStep > SCN_FEED_OUT_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				/* 一ヶ所で行う  1996/11/29
				*	if ( SCN_Control.UseType == IDP_SCANNER_TX ) {
				*		CodecPageStatus = CDC_DOC_ERROR;
				*	}
				*/
				return (0);
			}

			/* ICHOUではDS3がないので、処理を変更  1996/07/18 s.takeuchi */

			/**	最高速でまわしてる状態で、DS1とDS2のどちらにも原稿がない状態になったときに
			**	次のモーター割り込みでスルーダウンして停止させると、原稿が排出できる
			**		ICHOUではDS3がなく、更に待機状態では繰込まないため  1996/07/18 s.takeuchi
			*/
			if (!DS1() && !DS2()) {
				if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
					if (SCN_DocExitTopSpeedCount <= 0) {
						SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_OUT_OK;
						/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
						return (0);
					}
					else {
/*						SCN_DocExitTopSpeedCount--; */
						SCN_DocExitTopSpeedCount -= SCN_MotorIntStep;
					}
				}
			}
			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_FEED_READY) { /** スタンプ・テスト用の原稿繰り込み中 */
			/** モーターステップ数と読み取り終了後から排出までの繰り込み不良検出ステップを比較 */
			if (SCN_FeedErrorCheckStep > SCN_FEED_OUT_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				return (0);
			}

			/*	ICHOUにはDS3がないので、DS2割込みでスタンプ位置を検出しモーターを減速させる
			**	ここでは、停止するまでモータースピードを合わせるだけ  1996/07/16 s.takeuchi
			**	スタンプ位置に達していたら、ここは通らない  1996/10/28
			*/
			SCN_AdjustMotorSpeed();
		}
		else if ((SCN_DocumentStatus == SCN_DOC_STAMP_TEST_ON_GOING)	/* スタンプ・テスト中なら */
		||		 (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_STOP)) {		/* スタンプ・テスト停止要求がある */
			if (TXIL()) {	/** ADFカバーオープン */
				SCN_DocumentStatus = SCN_DOC_STAMP_TEST_ERROR; /** スタンプテストエラー */
			}
			SCN_StopMotor();
			return (EVT_SCN_DOC_OUT_OK);
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_DS2ON_WAIT) {
			/** モーターステップ数とDS1からDS2までの繰り込み不良検出ステップを比較 */
			if (SCN_FeedErrorCheckStep > SCN_DS1_TO_READY_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				return (0);
			}

			/** DS2のチャタリング防止  1996/10/30 */
			if (!(SCN_DS2INTR_Status & IO_BIT_DS2_ON_INT_ENABLE)
			&&	(SCN_FeedErrorCheckStep > 100)) {	/** DS2OFFの後、100ステップ以上送った */
				SCN_SetDS2_ON_Int( SCN_ENABLE );		/** ＤＳ２　ＯＮ割り込み許可 */
			}

			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_DS2OFF_WAIT) {
			/** モーターステップ数とDS2ONがOFFになるまでの繰り込み不良検出ステップを比較 */
			if (SCN_FeedErrorCheckStep > SCN_DS2_ON_TO_OFF_ERROR_STEPS) {
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
				return (0);
			}

			/** DS2のチャタリング防止  1996/10/30 */
			if (!(SCN_DS2INTR_Status & IO_BIT_DS2_OFF_INT_ENABLE)
			&&	(SCN_FeedErrorCheckStep > 100)) {	/** DS2OFFの後、100ステップ以上送った */
				SCN_SetDS2_OFF_Int( SCN_ENABLE );		/** ＤＳ２　ＯＮ割り込み許可 */
			}

			SCN_AdjustMotorSpeed();
		}
		else if (SCN_DocumentStatus == SCN_DOC_FEED_DS3OFF_WAIT) { /** 原稿排出テスト用の原稿移動中(DS2->DS3) */
			/*	ICHOUではDS3はないので、排出不良は検出できない。
			**	この状態(SCN_DOC_FEED_DS3OFF_WAIT)の意味は「原稿排出完了待ち」となり
			**	モーター割り込みで、排出完了ステップ分送るようにする(排出できたものとする)
			**		1996/07/15 s.takeuchi
			*/

			/*	DS3はないので、繰込み不良は見られないので削除  1996/07/16 s.takeuchi
			**	ここ(SCN_DOC_FEED_DS3OFF_WAIT)は排出完了待ちだけなので、DS1/DS2を見ずに空回しする
			*/

			if (SCN_MotorTablePoint == SCN_MotorPointer->TopSpeed) {
				if (SCN_DocExitTopSpeedCount <= 0) {
					SCN_ADF_MotorStopRequest = ADF_MOTOR_DOC_OUT_OK;
					/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
					return (0);
				}
				else {
					SCN_DocExitTopSpeedCount -= SCN_MotorIntStep;
				}
			}
			SCN_AdjustMotorSpeed();
		}
		/*----------------------------------------*/
		/* トルク・リミッター寿命テスト 7/19/1994 */
		/*----------------------------------------*/
		else if (SCN_DocumentStatus == SCN_DOC_MOTOR_LIFE_TEST) { /** トルク・リミッター寿命テスト */
			SCN_AdjustMotorSpeed();
		}
		else { /** 原稿読み取り中 */
			/*------------------------------------------------------------------*/
			/* モーターのステップ数を加算しスキャナーの繰り込み不良を検出する。 */
			/*------------------------------------------------------------------*/
			/* ICHOUではDS3は見ないため削除  1996/06/04 s.takeuchi */
			/*---------------------------------------*/
			/** モーターの速度を最適な値にセットする */
			/*---------------------------------------*/
			SCN_AdjustMotorSpeed();
		}
	}

	return (0);

}


/******************************************************************************
	module		:[ギアバックラッシュタスクタイムアウト処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[１０ｍｓ割り込みから呼ばれる]
	machine		:[SH(SH7034/SH704X)]
	language	:[SHC(V.3.0C)]
	keyword		:[SCN]
	date		:[1997/08/12]
	author		:[野瀬敏弘]
******************************************************************************/
void SCN_GearBacklashTimeOutCheck(void)
{
	CMN_DisableInterrupt();
	if (GearBackLashTimer != 0) {
		GearBackLashTimer--;			/* タイマーを減算 */
		if (GearBackLashTimer == 0) {
			GearBackLashTimeout = TRUE;	/* タイムアウト発生をセット */
			det_evt(EVT_SCN_GEAR_BACK_LASH_END);	/* 終了イベントを発行 */
			SYB_MaintenanceSwitch[MNT_SW_C6] |= GEAR_BACKLASH_TIMEOUT;	/* 保守スイッチＣ６－６を立てる */
		}
	}
	CMN_EnableInterrupt();
}
