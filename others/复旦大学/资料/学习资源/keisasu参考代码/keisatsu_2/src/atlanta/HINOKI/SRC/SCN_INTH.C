/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_int.c
 *	Create:	Mon Dec 29 11:30:38 1997	by	ishiyama
 *	Description:
 *		Scanner Interrupt and Interrupt Control Routines
 *	Change Log:
 *		\prj\eva\src\scn\scn_int.cからコピーし、HINOKI用にメンテしました  1998/09/26 by T.Soneoka
 *		
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"	/* テスト by Y.Kano 2004/02/24 */

void	DisableIntScannerTimer(void)
{
	EnableScannerInt = FALSE;
}
	
/*
 *	Name:	Scanner Interrupt
 *	Create:	Wed Jan 28 12:07:46 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	ScannerInt(void);
 *	Description:
 *		スキャナ割込み処理(2.5msec 間隔)
 *		2.5msec 間隔処理
 *			Scan:
 *				読取り中で、ScanBuf が書込み可のとき、
 *				VerticalMode に依存した読取りタイミングでスキャン
 *		5msec 間隔処理
 *			Motor Control:
 *				原稿移動
 *				原稿送り量カウントアップ
 *				送信モータステータスを更新(Through Up/Down Stop etc.)
 *			Document Sensor
 *				DS1,DS2,DSB4 を監視し、各ステータスを更新
 *				原稿位置のステータスを更新
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScannerInt(void)
{
	UWORD	Status;
	
	CheckScanLineInt = TRUE;
	if (!EnableScannerInt) {
		return;							/* スキャナ割込み禁止 */
	}

	/****************************************************
	 * 読み取り開始時に、モータの起動タイミングを探し、 *
	 * ５ｍｓのタイミングを作成しなおします             *
	 * （モータのクロックはＳＰＩＮＴと別に走っている） *
	 * ＳＩＮＴが落ちているときのみモータ起動します     *
	 * スキャンのタイミングを２．５ｍｓずらして読みます *
	 ****************************************************/
	if (IsScanOpen) {
		if ((!NowScanning) 
		&& 	(QueryDocScannable())) {
			Status = InputWORD(GA_INT_STA);
/* ステータスの受領は0x00で行なうようにします。1999/01/27 by T.Soneoka */
#if (0)
**			OutputWORD(GA_INT_REC, Status);	/* 割込み受領 */
**
**			if (Status & IO_BIT_PBRDY) {
**				/* Printer Buffer Ready 割込み */
**				PrinterPbreadyInt();
**			}
**			if (Status & IO_BIT_CI_INT) {
**				NCU_CI_Interrupt();				/* CI検出割込み処理 */
**			}
#else
			OutputWORD(GA_INT_REC, 0x00);	/* 割込み受領 */
#endif
			if (!(Status & IO_BTT_SINT)) {
				/* 並河からの依頼 ＳＦＩＮＥだけ、ＳＣＡＮするタイミングを２．５ｍｓずらす 1998/12/10 by T.Soneoka */
				if (CurrentPage->Mode == SYS_SFINE) {
					DelayScan = 1;
				} else {
					DelayScan = 0;
				}
				NowScanning = TRUE;
				Make5msTiming4Scan = TRUE;
				Make10msTiming4Scan = 4;
			} else {
				Make5msTiming4Scan = FALSE;
				Make10msTiming4Scan = 0;
			}
		}
	} else {
		NowScanning = FALSE;
	}
	
/* 1998/12/10 by T.Soneoka */
/* ＳＦＩＮＥ ２００ｐｐｓ １－２相で動作させる場合
** 停止する際に、常に２相で終了するようにします
** このため、モータの制御を１０ｍｓに変更します
** ５ｍｓ制御をしていて、１相で停止した場合、
**  次にモータを１－２相で回した場合、２相から始まってしまい
**	ＨＩＮＯＫＩの場合、２相でＳＣＡＮすると絵がかなり悪くなってしまいます
** （モータとかＧ／Ａの相性があるみたいです）
** そこで、１０ｍｓ制御にして、常に２相で終了するようにしてやります
*/
#if (0)
**	/**********************************************************************
**	 * 5msec 間隔処理
**	 **********************************************************************/
**	if (Make5msTiming4Scan) {
**		MakeSensorEvents();				/* Sensor のステータスを更新 */
**		Make5msTiming4Scan = FALSE;		/* 5msec Timing を作成 */
**		if (QueryDocMoveNow()) {
**			IntTxMotor();				/*	Motor Control */
**			UpdateDocPosition();		/*  原稿位置のステータスを更新 */
**		} else {
**			CurrentDownTxMotor();
**		}
**	} else {
**		Make5msTiming4Scan = TRUE;		/* 5msec Timing を作成 */
**	}
#else
	/**********************************************************************
	 * 10msec 間隔処理
	 **********************************************************************/
	if (Make10msTiming4Scan == 4) {
		MakeSensorEvents();				/* Sensor のステータスを更新 */
		if (QueryDocMoveNow()) {
			IntTxMotor();				/*	Motor Control */
			UpdateDocPosition();		/*  原稿位置のステータスを更新 */
		} else {
			CurrentDownTxMotor();
		}
	}
	Make10msTiming4Scan--;
	if (!Make10msTiming4Scan) {
		Make10msTiming4Scan = 4;
	}
#endif
	/**********************************************************************
	 * 2.5msec 間隔処理
	 **********************************************************************/
	/*  Scan: */
	/*  VerticalMode に依存した読取りタイミングでスキャン */
	if (QueryScanNow()) {
		ScanExecFlagOn();
		CountUpScanBufIndex();
#if (0)	/* プリントのタイミングをずらすテスト by Y.kano 2004/02/24 */
		if (PrinterUseMode == PRINT_SCOPY) {
			/* モードがＦｉｎｅとＳｆｉｎｅのときのみ行います 1999/1/21 by T.Soneoka */
			if ((CurrentPage->VerticalMode == TX_MOTOR_FINE_SCAN) ||
		    	(CurrentPage->VerticalMode == TX_MOTOR_SFINE_SCAN)) {
				IntTimerCounter |= 0x00000001;
			}
		}
		else {
			/* プリントするタイミングのときのみずらします */
			if (IntTimerCounter & 0x00000001) {
				/* ＳＣＡＮ時とプリントを同時に行わないようにします 1998/12/21 by T.Soneoka */
#if (0)
**			if (GaTphStatus & TPH_SYNC) {
**				IntTimerCounter |= 0x00000001;
**			} else {
**				IntTimerCounter &= (~0x00000001);
**			}
#else
				/* モードがＦｉｎｅとＳｆｉｎｅのときのみ行います 1999/1/21 by T.Soneoka */
				if ((CurrentPage->VerticalMode == TX_MOTOR_FINE_SCAN) ||
			    	(CurrentPage->VerticalMode == TX_MOTOR_SFINE_SCAN)) {
#if (0) /* 無駄な処理をやめます */
**				if (GaTphStatus & TPH_SYNC) {
**					PrintSkipFlag = FALSE;
**				} else {
**					IntTimerCounter &= (~0x00000001);
**					PrintSkipFlag = TRUE;
**				}
#else
					if (!(GaTphStatus & TPH_SYNC)) {
						IntTimerCounter &= (~0x00000001);
					}
#endif
				}
#endif
			}
		}
#else
		/* プリントするタイミングのときのみずらします */
		if (IntTimerCounter & 0x00000001) {
				/* ＳＣＡＮ時とプリントを同時に行わないようにします 1998/12/21 by T.Soneoka */
#if (0)
**			if (GaTphStatus & TPH_SYNC) {
**				IntTimerCounter |= 0x00000001;
**			} else {
**				IntTimerCounter &= (~0x00000001);
**			}
#else
			/* モードがＦｉｎｅとＳｆｉｎｅのときのみ行います 1999/1/21 by T.Soneoka */
			if ((CurrentPage->VerticalMode == TX_MOTOR_FINE_SCAN) ||
		    	(CurrentPage->VerticalMode == TX_MOTOR_SFINE_SCAN)) {
#if (0) /* 無駄な処理をやめます */
**				if (GaTphStatus & TPH_SYNC) {
**					PrintSkipFlag = FALSE;
**				} else {
**					IntTimerCounter &= (~0x00000001);
**					PrintSkipFlag = TRUE;
**				}
#else
				if (!(GaTphStatus & TPH_SYNC)) {
					IntTimerCounter &= (~0x00000001);
				}
#endif
			}
#endif
		}
#endif

	} else {
		ScanExecFlagOff();
	}

	/* Event の発生 */
	MakeScannerEvents();
}

/*
 *	Name:	Query Scan Now
 *	Create:	Wed Jan 28 15:34:10 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		BOOL	QueryScanNow(void);
 *	Description:
 *		送信モードから読取るべきタイミングかどうかを判断して返す
 *	Return Value:
 *		TURE:	読取る
 *		FALSE:	今回はパス。なんにもしない。
 *	Change Log:
 *		
 */
BOOL	QueryScanNow(void)
{
	BOOL	ScanNow;

	ScanNow = FALSE;
#if (0) /* 1998/12/10 by T.Soneoka */
**	if (QueryScanning()) {				/* 読取り動作中 */
#endif
#if (0)
**		if (QueryDocScannable()) {		/* 原稿が読取り可能 */
#else
		if (RequestScan) {		/* 原稿が読取り可能 */
#endif
			if (DelayScan) {
				DelayScan--;
			} else {
#if (0) /* モータ起動時に判断しているため、削除します 1998/12/10 by T.Soneoka */
**				if (EnableToWriteScanBuf()) { /* Scanner Buffer に書込める */
#endif
					if (ScanTimingBase > 0) { /* 排出中などじゃない */
						ScanTimingBase--;
						if (ScanTimingBase == 0) {
							switch (QueryReduction()) {
							case REDUCTION_B4_A4:
								ScanNow = FALSE;
								if (ScanReductionTimingTableB4toA4 & (0x00000001 << ReductionPos)) {
									ScanNow = TRUE;
								}
								ScanTimingBase = ScanTimingTable[CurrentPage->VerticalMode];
								ReductionPos++;
								if (ReductionPos >= REDUCTION_POS_MAX) {
									ReductionPos = 0;
								}
								break;
							case REDUCTION_NO:
							default:
								ScanTimingBase = ScanTimingTable[CurrentPage->VerticalMode];
								ScanNow = TRUE;
								break;
							}
						}
					}
#if (0)
**				}
#endif
			}
		}
#if (0)
**	}
#endif
	return	ScanNow;
}


/*
 *	Name:	Make Scanner Events
 *	Create:	Mon Feb 16 17:21:22 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	MakeScannerEvents();
 *	Description:
 *		スキャナ割込みからイベントを発生する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	MakeScannerEvents(void)
{
	UBYTE evt_no;

	ScannerEventStatus = 0;
	evt_no = 0;

	switch (ScannerMode) {
	case SCANNER_NEUTRAL_MODE:
		/* 読み取り中にスキャナーカバーを開けると、「カバーオープン」になる。（これは正しい）
		** しかし、チャタリングの監視タイミングの関係で、読み取りタスクが検出するよりも、
		** センタータスクの方がスキャナーイニシャルを呼んでしまう。結果として、このScannerModeがSCANNER_NEUTRAL_MODEに
		** 書き換えられてしまい、読み取りタスクの方では、カバー開きがみれない（ループする。）
		** よって、ここでも、スキャナーカバーのみチェックします。
		** To 曽根岡殿チェックよろしく！
		** by O.Kimoto 1999/01/09
		*/
		if (!QueryCloseInterLock4Scan()) {
			ScannerEventStatus |= SCN_EVT_DOCIN_COVER_OPEN;
			evt_no = EVT_SCN_DOC;
		}
		break;
	case SCANNER_DOC_IN_MODE:
		if (!QueryCloseInterLock4Scan()) {
			ScannerEventStatus |= SCN_EVT_DOCIN_COVER_OPEN;
			evt_no = EVT_SCN_DOC;
		}
		else {
			switch (QueryDocPosition()) {
			case DOC_POS_NO_DOCUMENT:
				ScannerEventStatus |= SCN_EVT_DOCIN_NO_DOC;
				evt_no = EVT_SCN_DOC;
				break;
			case DOC_POS_MOVE_TO_DS2:
				if (!QueryDs1On()) {
					ScannerEventStatus |= SCN_EVT_DOCIN_NO_DOC;
					evt_no = EVT_SCN_DOC;
				}
				else if (CurrentPage->StepsFromDs1On > MoveToDs2ErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCIN_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_MOVE_TO_READY:
				if (CurrentPage->StepsFromDs2On > Ds2OnToOffErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCOUT_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_MOVE_TO_SCAN:
				ScannerEventStatus |= SCN_EVT_DOCIN_SET_OK;
				evt_no = EVT_SCN_DOC;
				break;
			case DOC_POS_SCANNING:
			case DOC_POS_SCAN_FEEDOUT:
			case DOC_POS_MOVE_TO_PUSH_STAMP:
			case DOC_POS_FEED_OUT:
			default:
				break;
			}
		}
		if (evt_no) {
#if (0) /* 1998/12/04 by T.Soneoka */
**			StopTxMotor();
#else
			EnableIntTxMotor = FALSE;
#endif
		}
		break;
	case SCANNER_DOC_OUT_MODE:
		if (!QueryCloseInterLock4Scan()) {
			ScannerEventStatus |= SCN_EVT_DOCOUT_COVER_OPEN;
			evt_no = EVT_SCN_DOC;
		} else {
			switch (QueryDocPosition()) {
			case DOC_POS_NO_DOCUMENT:
				ScannerEventStatus |= SCN_EVT_DOCOUT_EXIT_OK;
				evt_no = EVT_SCN_DOC;
				break;
			case DOC_POS_MOVE_TO_DS2:
				if (CurrentPage->StepsFromDs1On > MoveToDs2ErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCOUT_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_MOVE_TO_READY:
			case DOC_POS_MOVE_TO_SCAN:
			case DOC_POS_SCANNING:
				if (CurrentPage->StepsFromDs2On > Ds2OnToOffErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCOUT_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_SCAN_FEEDOUT:
			case DOC_POS_MOVE_TO_PUSH_STAMP:
			case DOC_POS_FEED_OUT:
			default:
				break;
			}
		}
		if (evt_no) {
#if (0) /* 1998/12/04 by T.Soneoka */
**			StopTxMotor();
#else
			EnableIntTxMotor = FALSE;
#endif
		}
		break;
	case SCANNER_DOC_SCAN_MODE:
	case SCANNER_COPY_MODE:
		if (!QueryCloseInterLock4Scan()) {
			ScannerEventStatus |= SCN_EVT_DOCSTORE_COVER_OPEN;
			evt_no = EVT_SCN_DOC;
		} else {
			switch (QueryDocPosition()) {
			case DOC_POS_NO_DOCUMENT:
				/*
				** スキャナ送信にて、FCMがMPSを送出した後、原稿を引き抜いた場合
				** CurrentPage.PositionがDOC_POS_NO_DOCUMENTのままループしてしまう
				** 現状このSCANNER_DOC_SCAN_MODEでDOC_POS_NO_DOCUMENTになることはない
				** Added 2 line 1999/01/12 by T.Soneoka
				*/
				ScannerEventStatus |= SCN_EVT_DOCSTORE_FEED_ERROR;
				evt_no = EVT_SCN_DOC;
				break;
			case DOC_POS_MOVE_TO_DS2:
				if (CurrentPage->StepsFromDs1On > MoveToDs2ErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCSTORE_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_MOVE_TO_READY:
			case DOC_POS_MOVE_TO_SCAN:
				/* スキャナー送信時、原稿引き抜きが正確に見れないため、
				** ここでDs1を監視し、DS1=OFFが検出された場合は、
				** 繰り込みエラーとします。
				** by O.Kimoto 1999/01/11
				*/
				if (!QueryDs1On()) {
					ScannerEventStatus |= SCN_EVT_DOCSTORE_FEED_ERROR;
					evt_no = EVT_SCN_DOC;
				}
				/* Breakはあえていれていません。
				** 下記処理を継続して監視します。
				** by O.Kimoto 1999/01/11
				*/
			case DOC_POS_SCANNING:
				if (CurrentPage->StepsFromDs2On > Ds2OnToOffErrorSteps) {
					ScannerEventStatus |= SCN_EVT_DOCSTORE_MAXLINE_OVER;
					evt_no = EVT_SCN_DOC;
				}
				break;
			case DOC_POS_SCAN_FEEDOUT:
				break;
#if (PRO_STAMP == ENABLE)
			case DOC_POS_MOVE_TO_PUSH_STAMP:
				break;
#endif
			case DOC_POS_FEED_OUT:
#if (0)
**#if (0) /* 済みスタンプ押すときも押さないときもイベントを発行して、モータを一旦停止させます 1998/11/17 by T.Soneoka */
****				if (EnableExecStamp && EnablePushStampEvent) {
**#else
**				if ((EnablePushStampEvent)
**				&&  (SCN_DocumentChanged)) {
**#endif
**					EnablePushStampEvent = FALSE;
**					ExecutePushStamp = TRUE;
**					evt_no = EVT_SCN_STAMP;
**				}
#endif
				break;
			default:
				break;
			}
		}
		/* 1998/11/17 by T.Soneoka */
		if ((EnablePushStampEvent)
		&&  (SCN_DocumentChanged)) {
			EnablePushStampEvent = FALSE;
			ExecutePushStamp = TRUE;
			evt_no = EVT_SCN_STAMP;
		}
		if (evt_no) {
#if (0) /* 1998/12/04 by T.Soneoka */
**			StopTxMotor();
#else
			EnableIntTxMotor = FALSE;
#endif
		}
		break;
#if (PRO_STAMP == ENABLE)
	case SCANNER_STAMP_MODE:
		switch (QueryDocPosition()) {
		case DOC_POS_NO_DOCUMENT:
		case DOC_POS_MOVE_TO_DS2:
			break;
		case DOC_POS_MOVE_TO_READY:
		case DOC_POS_MOVE_TO_SCAN:
		case DOC_POS_SCANNING:
		case DOC_POS_SCAN_FEEDOUT:
		case DOC_POS_MOVE_TO_PUSH_STAMP:
		case DOC_POS_FEED_OUT:
			if (CurrentPage->StepsFromDs2On > (StampTestSteps*StampCount)) {
				if (EnablePushStampEvent) {
					EnablePushStampEvent = FALSE;
					ExecutePushStamp = TRUE;
					evt_no = EVT_SCN_STAMP;
				}
			}
			break;
		default:
			break;
		}
		if (evt_no) {
#if (0) /* 1998/12/04 by T.Soneoka */
**			StopTxMotor();
#else
			EnableIntTxMotor = FALSE;
#endif
		}
		break;
#endif
	default:
		break;
	}

#if (0) /* 1998/11/17 by T.Soneoka */
**	if ((ScannerEventStatus != 0) {
#else
	if (evt_no) {
#endif
		idet_evt(evt_no);
	}
}

/*
 *	Name:	Make Sensor Events
 *	Create:	Fri Feb 20 10:41:43 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	MakeSensorEvents(void);
 *	Description:
 *		Sensor のステータスを更新し、
 *		状態変化があれば、イベントを起こす
 *		ただし、イベントは Scanner が NEUTRAL のときのみ発行。
 *		他は、各モードのタスクで処理。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	MakeSensorEvents(void)
{
	Ds1Changed();
	Ds2Changed();
	DsB4Changed();
	InterLock4ScanChanged();
#if (0)	/* ＨＩＮＯＫＩはイベント発行しないようにした  1998/09/28 by T.Soneoka */
**	UBYTE	Flag;						/* Event Flag */
**
**	Flag = 0;							/* Event Flag 初期化 */
**
**	/*
**	 *	Update Sensor Status
**	 */
**	if (Ds1Changed()) {
**		if (QueryDs1On()) {
**			Flag |= EVT_DS1_ON;
**		} else {
**			Flag |= EVT_DS1_OFF;
**		}
**	}
**	Ds2Changed();						/* No events. Status update only. */
**	DsB4Changed();						/* No events. Status update only. */
**	if (InterLock4ScanChanged()) {	
**		if (QueryCloseInterLock4Scan()) {
**			Flag |= EVT_INTERLOCK_ON;
**		} else {
**			Flag |= EVT_INTERLOCK_OFF;
**		}
**	}
**
**	/*
**	 *	Fire Events
**	 */
**	if (ScannerMode == SCANNER_NEUTRAL_MODE) {
**		if (Flag != 0) {
**			IrptDetectEvent(EvtNo.ScannerSensor, Flag);
**		}
**	}
#endif
}



/* scn_int.c end */
