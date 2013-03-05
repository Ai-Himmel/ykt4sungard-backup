/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdmrxpix.c                                                            */
/*  作成者       :                                                                       */
/*  日  付       : 1999/10/06                                                            */
/*  概  要       : 画データ受信処理                                                      */
/*  修正履歴     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1997/10/27 */
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\fcm_pro.h"		/* 1996/02/13 Y.M */
#include "\src\atlanta\define\syst30.h"		/* 1996/02/13 Y.M */
#include "\src\atlanta\define\man_pro.h"		/* 1996/03/11 Y.M */
#include "\src\atlanta\define\cmn_pro.h"		/* by H.Kubo 1997/07/07 */
#include "\src\atlanta\define\uni_pro.h"		/* by H.Kubo 1997/07/07 */
#include "\src\memsw\define\mems_pro.h"		/* by H.Kubo 1997/07/07 */

#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h" /* Added by H.Kubo 1997/06/26 for MEM_DMAEndStatus */
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\define\mem_def.h"

#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\mem_data.h"


#include "\src\atlanta\define\mnt_sw.h"

#if defined (KEISATSU) /* 警察FAX 05/06/20 石橋正和 */
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\define\s1_def.h"
#endif

void  FskHighSpeedOpen(UBYTE type, UBYTE speed); /* for local use. */
UBYTE DecideStoreCode(UBYTE item);	/* Add By O.Kimoto 1998/05/20 */

extern UDWORD	ebr_cnt;	/**	ＥＣＭバッファ読み出しバイト数	*/

extern CONST UBYTE	TCF_DEBUG;

/*#if (PRO_MODEM == R288F)*/ /* added by H.Kubo 1997/12/18 */
/* POPLAR_H では、コードサイズを小さくする最適化コンパイルをしますが、
** そのままだと大量のスタックを消費します。そこで以下の #pragma によって
** 関数先頭での不要なレジスタ待避をさけます。
** (SuperH RISC engine ファミリ C コンパイラ編 2-34 参照)
** 1997/12/18 H.Kubo 
*/
#pragma noregalloc(MDM_RxEcmControlTask,MDM_RxDeviceControlTask)
/*#endif*/ /* (PRO_MODEM == R288F) */

UBYTE DebugStripePattern1 = 0;
UBYTE DebugStripePattern2 = 0;
UBYTE DebugStripePattern3 = 0;
UBYTE DebugStripePattern4 = 0;
UBYTE DebugStripePattern5 = 0;
UBYTE DebugStripePattern6 = 0;



/*************************************************************************
	module		:[高低速識別]
	function	:[
		1.上位より指定されたモデムスピードでモデムオープンする．
		2.タイマタスクを６秒／３０秒それぞれ起動する
		3.フラグ／トレーニング検出タスクを起動、又はフレーム／トレーニング検出タスクを起動する
		4.トレーニングを検出した時、オープン処理を行う
		5.ＦＳＫ受信時は、オープン処理を行わない
	]
	return		:[
		FSK_RECEIVE:	ＦＳＫ受信
		TRN_RECEIVE:	高速信号受信
		TIME_OVER:		Ｔ２タイムオーバ他
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/25]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		MDM_FskHighSpeedCheck(
UBYTE	speed,		/*	モデムタイプ／スピード	*/
UBYTE	ecm_type,
UBYTE	turn_arround)	/** V.34モード時、Ｖ．８に戻るかどうか **/
{
	struct Timer10msData_t	TimerT2;
	struct Timer10msData_t	Timer30sec;

	UBYTE	phase;			/* 高低速識別状態 */
	UBYTE	timeoverflg;	/* Ｔ２タイムオーバフラグ */
	UBYTE	rtn;			/* 戻り値設定 */
	UBYTE	rtnmsg;			/* フラグ／フレーム／トレーニング／その他詳細 */
	UBYTE	retry_cnt;		/* 高低速識別試行カウンタ */
	UBYTE	rcv_fcf;
	UBYTE	tmp_wpt;

	phase = PHASE_FLAG_DETECT;
	timeoverflg = 0;
	rtn = 0;
	rtnmsg = 0;
	retry_cnt = 0;
	ModemWaitStatus = 0;
	tmp_wpt = 0;

	/* 1996/10/31 Y.Murata
	 * Inceasing Drop Out Recovery Time during V17/V29/
	*/
	/* debug */
	if (MDM_DropOutRecovryV17V29) {
		MDM_DropOutRecovryV17V29 = 0;
	}

	if (TCF_DEBUG & 0x10) {
		DspRamAccessWriteMethod1(0x0271, 0x7F, 0x00);
		DspRamAccessWriteMethod1(0x0270, 0xFF, 0x00);
	}

	/* 現状、モデムステータスを監視するタスクの直前に以下のコードを置いておくと間に合わないため */
	/* 取あえず、ここに置いておきます。                                                         */
	CMN_DisableInterrupt();
	MDM_CtsTurnOffCheckFlag = TRUE;
	MDM_CtsTurnOffFlag = 0;
	dbg_old_cts_status = (UBYTE)(inp(MDM_REG_0F_PORT) & IO_BIT_CTS);
	ModemWaitStatus = 0;	/* 上でもしているが安全のためここでも行う 1997/02/03 Y.Murata */
	ModemStatusFlag = 0;	/**	モデムステータス割り込み監視フラグクリア	*/
	ModemInterruptFlag = 0;	/**	モデム割り込み発生フラグ初期化	*/ /* 1997/02/02 Y.Murata */
	CMN_EnableInterrupt();

	/*--------------------------*/
	/* 海外認可共通対応         */
	/* FOREIGN_APPROVAL No.1-4  */
	/*--------------------------*/
	/* 高低速識別で何も受信しない時は、Ｔ２タイムオーバーで切る
	*/
	if (CHK_ForeignApprovalDEU()) {
		if (CHK_UNI_ECM_RxTM_OutEvade() == 0) {
			retry_cnt = 3;
			timeoverflg = YES;
		}
	}

	/*----------------------*/
	/*	モデムタイプ設定	*/
	/*----------------------*/
	ModemTypeSet(speed);	/**	モデムタイプ／スピード設定	*/

	PixRxSpeed = ModemBlock.Speed;	/* For TimeOver ECM	*/

	if (ModemBlock.Type == TYPE_V34) {	/** For Debug **/
		ModemBlock.Training = TRAINING_SHORT;	/**	ショートトレーニング設定	*/
	}
	else if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
		/* R288F モデムでは、CTC/CTR の後、引き続き 14.4K で通信する場合、ショートで受けると
		** 全フレームエラーが発生するので変更。
		** 古い村田機は CTC/CTR 後に PIX をショートトレーニングで送ってくるが、
		** CTC/CTR 後は V17 の 14.4K で PIX を再送することはないので、 問題にはならない。
		** by H.Kubo 1998/09/24 */

		if ((RxFCF == CTC_F) && (speed == BPS14400_V17)) { /* V17 14.4k ロングトレーニングをショートで受けると全フレームエラーになるので。 */
			ModemBlock.Training = TRAINING_LONG;	/**	ロングトレーニング設定	*/ 
		}
		else {
			ModemBlock.Training = TRAINING_SHORT;	/**	ショートトレーニング設定	*/
		}
	}
	else {	/**	その他の時	*/
		ModemBlock.Training = TRAINING_LONG;	/**	ロングトレーニング設定	*/
	}
	ModemBlock.RxCheck = CHECK_OFF;

	FskHighSpeedOpen(ecm_type, speed);
	if (SYS_V34ProcedureExecuting() == 0) {	/* V34でない */	/* 1997/01/31 Y.Murata */
		if (CHK_HIGH_MODE_CATCH()) {	/* 高速のみまつ */
			/* Nothing */
		}
		else {
			MDM_FilterSet(FSK_PIX_FILTER);
		}
	}

	/*--------------------------------------------------------------------------------------*/
	/*	フレーム検出／トレーニング検出する間およびフレーム受信試行回数が３回以内の間ループ	*/
	/*--------------------------------------------------------------------------------------*/
	while (1) {	/**	フレーム検出／トレーニング検出する間およびフレーム受信試行回数が３回以内の間ループ	*/

		/*----------------------------------*/
		/*	モデムステータス監視タスク起動	*/
		/*----------------------------------*/
		tskno_ModemStatusCheck = 0xffff;
		ModemWaitStatus = PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_TRDETON;	/**	モデムステータスシーケンス信号検出に設定	*/
		cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task);	/**	モデムステータス監視タスク起動	*/

		/*--------------------------------------*/
		/*	Ｔ２タイマ設定	タイマタスク起動	*/
		/*--------------------------------------*/
		TimerT2.Time = (T2_TIME/10);
		TimerT2.SendMBX = mbxno.MDM_Task;
		TimerT2.ReturnValue = MSG_T2_TIME_OVER;
		timerID_TimerT2 = 0xff;
		CMN_MultiTimer10msStart(&timerID_TimerT2, &TimerT2);	/**	Ｔ２タイマ起動	*/
		/*--------------------------------------*/
		/*	３０秒タイマ設定　タイマタスク起動	*/
		/*--------------------------------------*/
		Timer30sec.Time = (FRAME_CONTROL_TIMER/10);
		Timer30sec.SendMBX = mbxno.MDM_Task;
		Timer30sec.ReturnValue = MSG_30SEC_TIME_OVER;
		timerID_Timer30sec = 0xff; /* Chnaged by H.Kubo 1997/07/15 */
		CMN_MultiTimer10msStart(&timerID_Timer30sec, &Timer30sec);	/**	３０秒タイマ起動	*/
		/*------------------------------------------------------------------*/
		/*	フレーム検出／トレーニング検出／その他エラー検出するまでループ	*/
		/*------------------------------------------------------------------*/
		while (2) {	/**	フレーム検出／トレーニング検出／その他エラー検出するまでループ	*/

			if (phase == PHASE_FLAG_DETECT) {	/**	フラグ検出状態の時	*/
				/*------------------------------*/
				/*	トレーニング／フラグ検出	*/
				/*------------------------------*/
				HighSpeedCheckFlag = 1;		/* 1997/01/28 Y.Murata */
				rtn = RxPixFlagAndHighSpeedDetect();	/**	トレーニング／フラグ検出処理	*/
				HighSpeedCheckFlag = 0;		/* 1997/01/28 Y.Murata */

				if (rtn == MSG_FLAG_DETECT) {	/**	フラグ検出時	*/
					if (!(SYS_V34ProcedureExecuting())) {	/** 従来のプロトコルならば **/
						/*----------------------*/
						/*	タイマタスク終了	*/
						/*----------------------*/
						if (timerID_TimerT2 != 0xff) {
							CMN_MultiTimer10msStop(&timerID_TimerT2);	/**	タイマ終了処理	*/
						}
						/*--------------------------*/
						/*	３０秒タイマタスク終了	*/
						/*--------------------------*/
						if (timerID_Timer30sec != 0xff) {
							CMN_MultiTimer10msStop(&timerID_Timer30sec);	/**	３０秒タイマ終了処理	*/
						}
						/*--------------------------*/
						/*	フラグ検出タスク終了	*/
						/*--------------------------*/
						if (tskno_FlagDetect != 0xffff) {
							del_tsk(&tskno_FlagDetect);	/**	フラグ検出タスク終了	*/
						}
						/*----------------------------------*/
						/*	モデムステータス監視タスク終了	*/
						/*----------------------------------*/
						ModemWaitStatus = 0;	/**	モデムステータス待ち状態クリア	*/
						if (tskno_ModemStatusCheck != 0xffff) {
							del_tsk(&tskno_ModemStatusCheck);	/**	モデムステータス監視タスク終了	*/
						}
						ModemStatusFlag = 0;	/**	モデムステータス割り込み監視フラグクリア	*/

						RxEcmClose();	/**	ＥＣＭ受信モデムクローズ	*/
						HighSpeedCheckFlag = 1;
						EchoFrameRcvFlag = 0;
						rtn = MDM_ReceiveCommand(TIME_OVER_6SEC);
						HighSpeedCheckFlag = 0;
						if ((rtn == FSK_ERROR) && (EchoFrameRcvFlag == 1)) {
							EchoFrameRcvFlag = 0;
							/* 再度、高速信号を取りに行く */
							ModemTypeSet(speed);	/**	モデムタイプ／スピード設定	*/
							phase = PHASE_FLAG_DETECT;	/**	フラグ検出フェーズセット	*/
							FskHighSpeedOpen(ecm_type, speed);
							rtnmsg = FLAG_TIME_OVER;
							break; /* while (2) */
						}
						else {
							rtnmsg = FRAME_DETECT;
							break;  /* while (2) */
						}
					}
					else /* if (SYS_V34ProcedureExecuting()) */ { 
						phase = PHASE_FRAME_DETECT;	/**	フレーム受信フェーズセット	*/
						SaveT30TimingData(SYS_T30_START_TIME);	/* 1996/02/13 Y.M */
					}
				}
				else if (rtn == MSG_ENABLE_MODEM_STATUS) {	/**	トレーニング検出時	*/
					if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信の時	*/
						/*------------------------------*/
						/*	高速Ｇ３モードで再オープン	*/
						/*------------------------------*/
						CMN_DisableInterrupt();	/**	割り込み禁止	*/
						ModemRxStatus = 0xff;
						SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);	/**	モデムコントロール領域初期化	*/
						MDM_SetIO(POS_HDLC,OFF);
						ModemBlock.Mode = MODE_RX_G3;		/**	交信モード設定	*/

						/* Added by H.Kubo 1997/10/09
						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
						*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
						SelectDreqDirection(RX_DMA);
#else
						SetModemDMA_DirectionRx();
#endif
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
						DMA_RestartDMAU(DMA_CH_RX,   DMA_IO_TO_MEMORY, MDM_ModemDmaSize,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/**	Ｖ５３ＤＭＡ起動*//** 256 Bytes **/
#else
						DMA_RestartDMAU(DMA_CH_RX,   DMA_IO_TO_MEMORY, MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/**	Ｖ５３ＤＭＡ起動*//** 256 Bytes **/
#endif
						CMN_EnableInterrupt();	/**	割り込み許可	*/
					}
					rtnmsg = HIGH_SPEED_RECEIVE;	/**	戻り値トレーニング検出設定	*/
					break;  /* while (2) */
				}
				else {	/**	タイムオーバ時	*/
					rtnmsg = FLAG_TIME_OVER;	/**	戻り値フラグタイムオーバ設定	*/
					break;  /* while (2) */
				}
			}
			else {	/* if (phase == PHASE_FRAME_DETECT || phase == PHASE_MULTI_FRAME_DETECT) */
				  /**	フレーム受信（マルチフレーム受信）状態の時	*/
				/*--------------------------*/
				/*	フレーム／高速信号監視	*/
				/*--------------------------*/
				rtn = RxPixFrameAndHighSpeedDetect();	/**	フレーム／高速信号監視	*/
				if (rtn == MSG_FRAME_DETECT) {	/**	フレーム検出時	*/
					ModemRxStatus |= (UBYTE)(1<<ModemControl.ReadPoint);

					/*
					** R288F VERSION 24P以上の場合
					** added by H.Kubo 1998/10/09
					*/
					if (MDM_ModemBuffer[ModemControl.ReadPoint][MDM_RxSize[ModemControl.ReadPoint]] != 0x7E) {
						MDM_RxSize[ModemControl.ReadPoint]++; /* 受信データの最後がフラグでなかったら、フラグの分を先に補正しておく。 */
					}

					MDM_RxSize[ModemControl.ReadPoint] -= 3;	/* Change 2 to 3 By O.K Feb.17,1996 */
					if (MDM_ModemBuffer[ModemControl.ReadPoint][1] == 0x13) {			/**	最終フレーム受信時	*/
						rcv_fcf = MDM_ModemBuffer[ModemControl.ReadPoint][2];			/**	ＦＣＦフレーム獲得	*/
						if ((rcv_fcf & ~X_BIT) == CRP_F) {	/**	ＣＲＰ受信時	*/
							rtnmsg = FRAME_DETECT;
							rtn = FSK_RECEIVE;
							break;  /* while (2) */
						}
						else if (rcv_fcf == EchoFCF) {
							phase = PHASE_FLAG_DETECT;
							FskHighSpeedOpen(ecm_type, speed);
							continue;  /* while (2) */
						}
						else {	/**	その他（正常）フレームを受信時	*/
							rtnmsg = FRAME_DETECT;	/**	戻り値フレーム受信完了セット	*/
							rtn = FSK_RECEIVE;
							break;  /* while (2) */
						}
					}
					else {	/**	非最終フレーム受信時	*/
						phase = PHASE_MULTI_FRAME_DETECT;	/**	マルチフレーム受信フェーズへ	*/
						NextMdmBufReadPointSetExtRom();
					}
				}
				else if (rtn == MSG_ENABLE_MODEM_STATUS) {	/**	トレーニング検出時	*/
					if (RxECM_Mode == ECM_OFF) {	/**	Ｇ３受信の時	*/
						/*------------------------------*/
						/*	高速Ｇ３モードで再オープン	*/
						/*------------------------------*/
						CMN_DisableInterrupt();	/**	割り込み禁止	*/
						ModemRxStatus = 0xff;
						SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);	/**	モデムコントロール領域初期化	*/
						MDM_SetIO(POS_HDLC,OFF);
						ModemBlock.Mode = MODE_RX_G3;		/**	交信モード設定	*/

						/* Added by H.Kubo 1997/10/09
						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
						*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
						SelectDreqDirection(RX_DMA);
#else
						SetModemDMA_DirectionRx();
#endif

#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
						DMA_RestartDMAU(DMA_CH_RX,   DMA_IO_TO_MEMORY,  MDM_ModemDmaSize, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/**	ＤＭＡ起動*/
#else
						DMA_RestartDMAU(DMA_CH_RX,   DMA_IO_TO_MEMORY,  MODEM_DMA_SIZE, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/**	ＤＭＡ起動*/
#endif
						CMN_EnableInterrupt();	/**	割り込み許可	*/
					}
					rtnmsg = HIGH_SPEED_RECEIVE;	/**	高速信号受信セット	*/
					break;  /* while (2) */
				}
				else if (rtn == MSG_T2_TIME_OVER) {	/**	Ｔ２／Ｔ４タイムオーバ時	*/
					if (timeoverflg == YES) {	/**	Ｔ２／Ｔ４タイムオーバ済みの時	*/
						rtnmsg = FLAG_TIME_OVER;	/**	戻り値フラグタイムオーバ設定	*/
						break;  /* while (2) */
					}
					timeoverflg = YES;	/**	再度トレーニング／フレーム検出へ	*/
					/*----------------------*/
					/*	タイマタスク終了	*/
					/*----------------------*/
						if (timerID_TimerT2 != 0xff) {
							CMN_MultiTimer10msStop(&timerID_TimerT2);	/**	タイマ終了処理	*/
						}
					/*--------------------------------------*/
					/*	Ｔ２タイマ設定	タイマタスク起動	*/
					/*--------------------------------------*/
					TimerT2.Time = (T2_TIME/10);
					TimerT2.SendMBX = mbxno.MDM_Task;
					TimerT2.ReturnValue = MSG_T2_TIME_OVER;
					timerID_TimerT2 = 0xff;
					CMN_MultiTimer10msStart(&timerID_TimerT2,  &TimerT2);	/**	Ｔ２タイマ起動	*/
				}
				else if (rtn == MSG_30SEC_TIME_OVER) {	/**	３０秒タイムオーバ時（データ無しの時）	*/
					rtnmsg = TIME_OVER_30SEC;	/**	戻り値３０秒タイムオーバ設定	*/
					break;  /* while (2) */
				}
			}
		}  /* end of while (2) */

		/*----------------------*/
		/*	タイマタスク終了	*/
		/*----------------------*/
		if (timerID_TimerT2 != 0xff) {
			CMN_MultiTimer10msStop(&timerID_TimerT2);	/**	タイマ終了処理	*/
		}
		/*--------------------------*/
		/*	３０秒タイマタスク終了	*/
		/*--------------------------*/
		if (timerID_Timer30sec != 0xff) {
			CMN_MultiTimer10msStop(&timerID_Timer30sec);	/**	３０秒タイマ終了処理	*/
		}
		/*--------------------------*/
		/*	フラグ検出タスク終了	*/
		/*--------------------------*/
		if (tskno_FlagDetect != 0xffff) {
			del_tsk(&tskno_FlagDetect);	/**	フラグ検出タスク終了	*/
		}
		/*----------------------------------*/
		/*	モデムステータス監視タスク終了	*/
		/*----------------------------------*/
		ModemWaitStatus = 0;	/**	モデムステータス待ち状態クリア	*/
		if (tskno_ModemStatusCheck != 0xffff) {
			del_tsk(&tskno_ModemStatusCheck);	/**	モデムステータス監視タスク終了	*/
		}
		ModemStatusFlag = 0;	/**	モデムステータス割り込み監視フラグクリア	*/
		/*------------------------------------------------------*/
		/*	フラグ／フレーム／トレーニング／タイマ監視結果処理	*/
		/*------------------------------------------------------*/
		if (rtnmsg == FRAME_DETECT) {	/**	フレーム検出時	*/
			RxEcmClose();	/**	ＥＣＭ受信モデムクローズ	*/

			MDM_NewT30Status = MODE_RX_FSK;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

			if (SYS_V34ProcedureExecuting()) {	/* add if 1997/01/23 Y.Murata */
				SaveReceivedT30Data();	/* 1996/02/13 Y.M */
				SaveT30TimingData(SYS_T30_END_TIME);	/* 1996/02/13 Y.M */

				/* コントロールチャンネル中のＦＥＤ　ＯＦＦを検出したかどうかをチェックし（フレーム取りこぼしの可能性がある）
				** その場合は、
				**         桐＋   ＝ ＣＣ＿ＲＥＴＲＡＩＮ
				**         その他 ＝ ＦＳＫ＿ＥＲＲＯＲ
				** となるようにする。
				** By O.Kimoto 1996/09/13
				*/
				if (MDM_FedOffFlag == 1) {		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */
					MDM_FedOffFlag = 0;
					FskHighSpeedOpen(ecm_type, speed);
					phase = PHASE_FLAG_DETECT;	/**	フラグ検出フェーズセット	*/
				}
				else {
					rtn = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信セット	*/
					break;  /* while (1) */
				}
			}
			else {	/* V34でない 1997/01/25 Y.M */
				/* Nothing 命令受信でrtnにﾘﾀｰﾝ値が入っている */
				break;  /* while (1) */
			}

		}
		else if (rtnmsg == HIGH_SPEED_RECEIVE) {	/**	トレーニング検出時	*/
			if (ModemBlock.Type == TYPE_V34) {
				if (turn_arround) {
					RxEcmClose();	/**	ＥＣＭ受信モデムクローズ	*/
				}
				rtn = TURN_OFF_RECEIVE;
			}
			else {
				rtn = TRN_RECEIVE;	/**	戻り値高速信号受信セット	*/
			}
			break;  /* while (1) */
		}
		else {	/**	その他のエラー時	*/
			RxEcmClose();	/**	ＥＣＭ受信モデムクローズ	*/
			if (RxECM_Mode == ECM_ON) {	/**	ＥＣＭ受信時	*/
				retry_cnt++;	/**	フレーム受信試行カウンタを更新	*/
				if (retry_cnt >= 3) {	/**	フレーム受信試行カウンタが３回目の時	*/
					rtn = TIME_OVER;	/**	戻り値エラーセット	*/
					break;  /* while (1) */
				}
				else {
					FskHighSpeedOpen(ecm_type, speed);
					phase = PHASE_FLAG_DETECT;	/**	フラグ検出フェーズセット	*/
				}
			}
			else {
				rtn = TIME_OVER;	/**	戻り値エラーセット	*/
				break;  /* while (1) */
			}
		}
	}  /* end of while (1) */


	return (rtn);
}


/*************************************************************************
	module		:[高低速識別用フラグ・高速信号検出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/27]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE  RxPixFlagAndHighSpeedDetect(void)
{
	MESSAGE_t	*MDM_Msg;

	/*--------------------------*/
	/*	フラグ検出タスク起動	*/
	/*--------------------------*/
	tskno_FlagDetect = 0xffff;
	cre_tsk(&tskno_FlagDetect, TSK_MDM_FLAGDETECTTASK, &mbxno.MDM_Task);	/**	フラグ検出タスク起動	*/

	/*--------------------------------------------------------------*/
	/*	メッセージ受信処理											*/
	/*	1.MSG_FLAG_DETECT:			フラグ監視タスクより			*/
	/*	2.MSG_T2_TIME_OVER:			タイマタスクより				*/
	/*	3.MSG_30SEC_TIME_OVER:		タイマタスクより				*/
	/*	4.MSG_ENABLE_MODEM_STATUS:	モデムステータス監視タスクより	*/
	/*--------------------------------------------------------------*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
	} while (!((MDM_Msg->Message == MSG_FLAG_DETECT) ||
	           (MDM_Msg->Message == MSG_T2_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_30SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS)));

	/*--------------------------*/
	/*	フラグ検出タスク終了	*/
	/*--------------------------*/
	if (tskno_FlagDetect != 0xffff) {
		del_tsk(&tskno_FlagDetect);	/**	フラグ検出タスク終了	*/
	}
	return ((UBYTE)MDM_Msg->Message);	/**	戻り値設定	*/
}


/*************************************************************************
	module		:[高低速識別用フレーム・高速信号検出タスク]
	function	:[
		1.高低速識別フェーズが受信アイドル／最初のフレーム検出中の時、
		フラグ検出及び高速信号待ちを実行する
		2.高低速識別フェーズがマルチフレーム検出中は、フレーム検出実行
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/27]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	RxPixFrameAndHighSpeedDetect(void)
{
	MESSAGE_t	*MDM_Msg;

	/*--------------------------*/
	/*	ＦＣＳ検出タスク起動	*/
	/*--------------------------*/
	tskno_FcsDetect = 0xffff;
	cre_tsk(&tskno_FcsDetect, TSK_MDM_FCSDETECTTASK, &mbxno.MDM_Task);	/**	ＦＣＳ検出タスク起動	*/

	/*--------------------------------------------------------------*/
	/*	メッセージ受信処理											*/
	/*	1.MSG_DMA_STOP:				受信ＤＭＡ転送終了監視タスク	*/
	/*	2.MSG_T2_TIME_OVER:			タイマタスクより				*/
	/*	3.MSG_30SEC_TIME_OVER:		タイマタスクより				*/
	/*	4.MSG_ENABLE_MODEM_STATUS:	モデムステータス監視タスクより	*/
	/*--------------------------------------------------------------*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
	} while (!((MDM_Msg->Message == MSG_DMA_STOP) ||
	           (MDM_Msg->Message == MSG_T2_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_30SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) ||
	           (MDM_Msg->Message == MSG_FRAME_DETECT)));
	if (tskno_FcsDetect != 0xffff) {
		del_tsk(&tskno_FcsDetect);	/**	ＦＣＳ検出タスク終了	*/
	}
	return ((UBYTE)MDM_Msg->Message);
}


/*************************************************************************
	module		:[ＰＩＸ受信]
	function	:[
		1.
	]
	return		:[
		受信結果(MDM_RxPix()ﾘﾀｰﾝ値)
		RX_CONTINUE					0
		RX_PAGE_END					1
		RX_BLOCK_END				2
		RX_STOPPED					3
		RX_MEM_OVER					4
		RX_CARRIER_DOWN				5
		RX_ERROR					6
		RX_TMOUT					7
		RX_STUP_ERR					8
		RX_PRT_ERR					9
		RX_CONTI_ERR				10
		RX_OVER	        			11
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/25]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE  MDM_RxPix(UBYTE	ecm_type, UBYTE	pm_type)
{
	UWORD	i;
	UBYTE	rtn;
	UWORD	result;
	struct	MEM_IndexData_t	index_data;

	result = 0;

	/*
	** 受信３Ｍオーバチェック処理追加
	** 1999/02/02 by T.Soneoka
	** ported by H.Kubo 1999/09/14
	*/
	Rx3mErrorLine = DECODE_MAX_LINE;
	if (CHK_PrintRx3mOver()) {
		switch (SYS_DocBlock.Src.Mode) {	/**	蓄積モード	*/
		case SYS_NORMAL:					/**	普通	*/
			Rx3mErrorLine = DECODE_3M_NORM;
			break;
		case SYS_FINE:						/**	高画質	*/
		case SYS_GRAY16:					/**	16階調	*/
		case SYS_GRAY16_SEP:				/**	16階調像域分離	*/
		case SYS_GRAY32:					/**	32階調	*/
		case SYS_GRAY32_SEP:				/**	32階調像域分離	*/
		case SYS_GRAY64:					/**	64階調	*/
		case SYS_GRAY64_SEP:				/**	64階調像域分離	*/
			Rx3mErrorLine = DECODE_3M_FINE;
			break;
		case SYS_SFINE:						/**	超高画質	*/
		case SYS_HFINE:						/**	超高画質	*/
			Rx3mErrorLine = DECODE_3M_SFINE;
			break;
		}
	}

	/*==========================================================================*/
	/*	MDM_PhaseC_Status 	フェーズＣステータス初期化は通信の最初で行います  	*/
	/*==========================================================================*/
	BreakEcmTaskFlag = YES;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/

	MDM_RlsdTurnOffCheckFlag = TRUE;	/**  By O.K Feb.05,1996 **/
	MDM_RlsdTurnOnCheckFlag = TRUE;		/* Add for EQM By O.K Feb.22,1996 */
	MDM_RlsdTurnOffFlag = 0;
	MDM_RlsdTurnOnFlag = 0;

	if (!(SYS_V34ProcedureExecuting())) {
		/* 1997/05/09 Y.Murata
		 * Ｒ．３．３対策 RLSDが誤動作すればRTDISのｾｯﾄﾀｲﾐﾝｸﾞが狂いR.3.3が発生するため100msのﾁｬﾀを見る
		*/
		MDM_PixStartFlag = 1;
		MDM_AlreadyRtdisSetFlag = 0;
	}
	else {
		/* ロックウエルモデム不具合
		 * 1997/09/09 Y.Murata
		 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
		 *  受信できないことがある」
		 * ひらたくいえば、モデムが発散します。
		 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
		*/
		MDM_PixStartFlag = 1;
		MDM_AlreadyRtdisSetFlag = 0;
	}

	/*--------------------------------------------------*/
	/*	各受信オープン／タスク起動／受信クローズ処理	*/
	/*--------------------------------------------------*/
	switch (pm_type) { /* switch is added by H.Kubo 1997/07/15, ported from ORANGE\src\mdmrxpix.c */
	case RX_MEMORY:
		if (ecm_type == ECM_OFF) {	/**	Ｇ３受信時	*/
			BreakRxTaskCompleteFlag = NO;

			/*----------------------------------*/
			/*	デコードＤＭＡ監視タスク起動	*/
			/*----------------------------------*/
			DMA0_TC3Flag = 0;
			tskno_DecodeDMA_End = 0xffff;
			cre_tsk(&tskno_DecodeDMA_End, TSK_MDM_DECODEDMA_TC_DETECTTASK, 0);	/**	デコードＤＭＡ監視タスク起動	*/

			/*------------------------------*/
			/*	メモリライトパラメータ設定	*/
			/*------------------------------*/
			RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
			RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
			RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
			RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);	/* Add By O.Kimoto 1998/05/20 */

			RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;/* For F_CODE 1997/01/13  By T.Yamaguchi */
			RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
			RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
			/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/

			/*------------------------------*/
			/*	メモリライトオープン処理	*/
			/*------------------------------*/
			if (SYS_RxPrintFileItem != 0) {	/** 中継指示受信、中継局同時プリントありならデュアルオープンする */
				index_data.No   = SYS_RxPrintFileNo;
				index_data.Page = SYS_RxPrintFilePage;
				index_data.Item = SYS_RxPrintFileItem;
				index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
				result = MEM_DualOpen(&RxMemoryStoreData,
									  &index_data,
									  &MDM_MemoryExecData);	/**	メモリデュアルライトオープン	*/
			}
			else {
				result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData);	/**	メモリライトオープン	*/
			}
			if (result != MEM_OK) {	/**	メモリライトオープン失敗の時	*/
	
				if (result == MEM_INDEX_CONFLICT) {
					SYS_FaxComIndexConflictStatus = 1;
				}
				else {
					SYS_FaxComIndexConflictStatus = 0;
				}
				tskno_RxDeviceWriteControl = 0xffff;
				tskno_RxPixControl = 0xffff;
				BreakEcmTaskFlag = YES;
				MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
				return (RX_MEM_OVER);	/**	メモリオーバセット	*/
			}
			else { /* by H.Kubo 1998/11/11 */
				IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
			}
			/*------------------------------*/
			/*	メモリライト監視タスク起動	*/
			/*------------------------------*/
			tskno_RxDeviceWriteControl = 0xffff;
			cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	メモリライト監視タスク起動	*/
	
			/*--------------------------------------*/
			/*	受信１ページ符号変換タスク起動処理	*/
			/*--------------------------------------*/
			tskno_RxPixControl = 0xffff;
			cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
			CommunicateType = RX_G3_MEM;
			MDM_NewT30Status = MODE_RX_G3;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

			rtn = G3_Rx();	/**	Ｇ３受信	*/
		}
		/*--------------------------*/
		/*	メモリＥＣＭ受信処理	*/
		/*--------------------------*/
		else {	/**	ＥＣＭ受信時	*/
			BreakEcmTaskFlag = NO;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
			CommunicateType = RX_ECM_MEM;
	
			/*--------------------------------------*/
			/*	ＥＣＭコントロールタスク起動処理	*/;
			/*--------------------------------------*/
			for (i = 0; i < ECM_STATUS_MAX; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
				MDM_EcmStatus[i] = 0xff;
			}
			if (MDM_RTC_SeparateFlag == 0) {	/**	ＥＣＭ受信フレーム間またがりフラグが０の時	*/
				if (CodecPageStatus == CDC_READY) {	/**	１つ前の送信がブロックエンドで終了した時以外	*/
					BreakRxTaskCompleteFlag = NO;
					tskno_RxEcmControl = 0xffff;
					cre_tsk(&tskno_RxEcmControl, TSK_MDM_RXECMCONTROLTASK, 0);	/**	ＥＣＭ受信コントロールタスク起動	*/
				}
				/*------------------------------------------------------------------
				**   ＥＣＭ受信中ループ対策
				**   MDM_RxPix()でMDM_RXECMCONTROLTASKをクリエイトし、その後のsnd_msgでのループをなくす
				**   snd_msgする前にMDM_ResetCounterを500（５秒間）にセットします
				**   snd_msg完了する間、タイマ割り込み内で上記変数をデクリメントし、0になったときリセットします
				**   96.2.13		by T.Soneoka
				**   Portded from ORANGE by H.Kubo 1997/09/08 
				------------------------------------------------------------------*/
				MDM_ResetCounter = 500;
				ModemMessage.Message = MSG_RX_DECODE_START;
				snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);	/**	デコード開始メッセージ送信	*/
				MDM_ResetCounter = 0;
			}
			
			MDM_RTC_SeparateFlag = 0;	/**	ＥＣＭ受信フレームまたがりフラグを０に設定	*/
			MDM_NewT30Status = MODE_RX_ECM;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
			rtn = EcmRx();	/**	ＥＣＭ受信	*/
		}
		break;
	case RX_BKUPRAM:	/* ●ICHOU追加 高速ＲＤＳ データライト by T.Soneoka 1996/06/18 */
		/* 1998/03/27 by T.Soneoka 初期化不良不具合 */
		for (i = 0; i < ECM_STATUS_MAX; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
			MDM_EcmStatus[i] = 0xff;
		}
		CommunicateType = RX_ECM_BKUPRAM;
		BreakRxTaskCompleteFlag = YES;	/* 子タスクを全く起動しないので最初からＹＥＳにする */
		EcmRx();
		rtn = RX_PAGE_END;
		break;
	case RX_PRINTER:
#if (PRO_PRINTER_RX == ENABLE) /* Ported for HINOKI2 by T.Takagi 2002/01/07 */
		/*--------------------------*/
		/*	Ｇ３／ＥＣＭ受信処理	*/
		/*--------------------------*/
		if (ecm_type == ECM_OFF) {	/**	Ｇ３受信時	*/
#if (PRO_PRINT_TYPE == THERMAL)
			PRT_StartPrint();	/* ＦＣＭモジュールより移動してきました by T.Soneoka 1998/12/3 */
#endif
			/*
			** added by H.Hirao 1998/10/28
			*/
			/*----------------------------------*/
			/*	デコードＤＭＡ監視タスク起動	*/
			/*----------------------------------*/
			DMA0_TC3Flag = 0;
			tskno_DecodeDMA_End = 0xffff;
			cre_tsk(&tskno_DecodeDMA_End, TSK_MDM_DECODEDMA_TC_DETECTTASK, 0);	/**	デコードＤＭＡ監視タスク起動	*/

			BreakRxTaskCompleteFlag = NO;
			/*------------------------------------------*/
			/*	プリンタ受信１ページ符号変換タスク起動	*/
			/*------------------------------------------*/
			tskno_RxPixControl = 0xffff;
			cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
			CommunicateType = RX_G3_PRT;
			rtn = G3_Rx();	/**	Ｇ３受信	*/
		}
		else {						/**	ＥＣＭ受信時	*/
			CommunicateType = RX_ECM_PRT;
			BreakEcmTaskFlag = NO;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
			/*--------------------------------------*/
			/*	ＥＣＭコントロールタスク起動処理	*/
			/*--------------------------------------*/
			for (i = 0; i < 32; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
				MDM_EcmStatus[i] = 0xff;
			}
			
			if (MDM_RTC_SeparateFlag == 0) {
				if (CodecPageStatus == CDC_READY) {	/**	１つ前の送信がブロックエンドで終了した時以外	*/
#if (PRO_PRINT_TYPE == THERMAL)
					PRT_StartPrint();	/* ＦＣＭモジュールより移動してきました by T.Soneoka 1998/12/3 */
#endif
					BreakRxTaskCompleteFlag = NO;
					cre_tsk(&tskno_RxEcmControl, TSK_MDM_RXECMCONTROLTASK, 0);
				}
				/*------------------------------------------------------------------
				** ＥＣＭ受信中ループ対策
				** MDM_RxPix()でMDM_RXECMCONTROLTASKをクリエイトし、その後のsnd_msgでのループをなくす
				** snd_msgする前にMDM_ResetCounterを500（５秒間）にセットします
				** snd_msg完了する間、タイマ割り込み内で上記変数をデクリメントし、0になったときリセットします
				** 96.2.13		by T.Soneoka
				** Ported from ORANGE
				------------------------------------------------------------------*/
				MDM_ResetCounter = 500;
				ModemMessage.Message = MSG_RX_DECODE_START;
				snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);
				MDM_ResetCounter = 0;
			}
			MDM_RTC_SeparateFlag = 0;
			rtn = EcmRx();	/**	ＥＣＭ受信	*/
		}
#endif /* (PRO_PRINTER_RX == ENABLE) */
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/12 K.Kawata*//* 2002/10/24 By M.Maeda */
/* Ｇ３／ＥＣＭ受信処理 */
		if (ecm_type == ECM_OFF) {	/* Ｇ３受信時 */
			/*----------------------------------*/
			/*	デコードＤＭＡ監視タスク起動	*/
			/*----------------------------------*/
			DMA0_TC3Flag = 0;
			tskno_DecodeDMA_End = 0xffff;
			cre_tsk(&tskno_DecodeDMA_End, TSK_MDM_DECODEDMA_TC_DETECTTASK, 0);	/**	デコードＤＭＡ監視タスク起動	*/
			BreakRxTaskCompleteFlag = NO;
			/*------------------------------------------*/
			/*	プリンタ受信１ページ符号変換タスク起動	*/
			/*------------------------------------------*/
			tskno_RxPixControl = 0xffff;
			cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXDECODEPAGETASK, 0);	/* プリンタ受信１ページ符号変換タスク起動 */
			CommunicateType = RX_G3_PRT;
			rtn = G3_Rx();	/**	Ｇ３受信	*/
		}
		else {						/**	ＥＣＭ受信時	*/
			CommunicateType = RX_ECM_PRT;
			BreakEcmTaskFlag = NO;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
/* ＥＣＭコントロールタスク起動処理 */
			for (i = 0; i < 32; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
				MDM_EcmStatus[i] = 0xff;
			}
			
			if (MDM_RTC_SeparateFlag == 0) {
				if (CodecPageStatus == CDC_READY) {	/**	１つ前の送信がブロックエンドで終了した時以外	*/
					BreakRxTaskCompleteFlag = NO;
					cre_tsk(&tskno_RxEcmControl, TSK_MDM_RXECMCONTROLTASK, 0);
				}
				/*------------------------------------------------------------------
				** ＥＣＭ受信中ループ対策
				** MDM_RxPix()でMDM_RXECMCONTROLTASKをクリエイトし、その後のsnd_msgでのループをなくす
				** snd_msgする前にMDM_ResetCounterを500（５秒間）にセットします
				** snd_msg完了する間、タイマ割り込み内で上記変数をデクリメントし、0になったときリセットします
				** 96.2.13		by T.Soneoka
				** Ported from ORANGE
				------------------------------------------------------------------*/
				MDM_ResetCounter = 500;
				ModemMessage.Message = MSG_RX_DECODE_START;
				snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);
				MDM_ResetCounter = 0;
			}
			MDM_RTC_SeparateFlag = 0;
			rtn = EcmRx();	/**	ＥＣＭ受信	*/
		}
#endif	/* PRO_PRINT_TYPE == THERMAL_TRANS */
		break;
	default:
		;	/* Error. argument pm_type carries ilegal value. */
	}

	MDM_RlsdTurnOffCheckFlag = FALSE;	/**  By O.K Feb.05,1996 **/

	if (!(SYS_V34ProcedureExecuting())) {
		MDM_SetIO(POS_RTDIS,OFF);
		MDM_PixStartFlag = 0;
		MDM_AlreadyRtdisSetFlag = 0;

		/* 以下はＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策です。
		** By O.Kimoto 1996/12/18
		*/
		DspRamAccessWriteMethod1(0x4803,0x10,0xEF);

		/* 1997/02/05 Y.Murata
		 * トレイン・オン・データクリア
		 */
		/*MDM_SetIO(POS_TOD, OFF); 1997/02/06 Y.M */

	}
	else {
		/* ロックウエルモデム不具合
		 * 1997/09/09 Y.Murata
		 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
		 *  受信できないことがある」
		 * ひらたくいえば、モデムが発散します。
		 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
		*/

		MDM_PixStartFlag = 0;
		MDM_AlreadyRtdisSetFlag = 0;

		/*
		** R288F VERSION 24P以上の場合
		*/
		MDM_SetIO(POS_PCOFF, OFF); /* R4.2 対策。速やかに Control Channel へ抜けるため。 by H.Kubo 1998/11/14 */
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		MDM_SetIO(POS_FCCR_FM336, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
	}
	else {
		MDM_SetIO(POS_FECSQ, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
	}
#else
		MDM_SetIO(POS_FECSQ, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
#endif

#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) /* For DEBUG by O.kimoto 1998/12/01 */ /* ported for HINOKI2 2001/11/13 T.Takagi */
		MDM_NewT30Status = MODE_PC_OFF;	/* Add by O.Kimoto 1998/12/01 */
#endif

	}
	return (rtn);
}


/*************************************************************************
	module		:[メモリＧ３受信]
	function	:[
		1.

	]
	return		:[
		RX_PAGE_END		1
		RX_STOPPED		3
		RX_MEM_OVER		4
		RX_CARRIER_DOWN	5
		RX_ERROR		6
		RX_STUP_ERR		8
		RX_CONTI_ERR	11
		RX_OVER	        12
	]
	common		:[]
	condition	:[]
	comment		:[
	キャリア断判定ブロック数（１ｂｌｏｃｋ＝２５６ｂｙｔｅ）
	＝（３００ｂｙｔｅ／ｓ（２４００ｂｐｓ時）×キャリア断判定時間（ｓ）×通信速度倍（１．．．６）
	　／２５６ｂｙｔｅ／ｂｌｏｃｋ）＋１
	よって キャリア断時間５秒で換算すると以下の通り
	２４００　ｂｐｓ－＞６　ブロック
	４８００　ｂｐｓ－＞１２ブロック
	７２００　ｂｐｓ－＞１８ブロック
	９６００　ｂｐｓ－＞２４ブロック
	１２０００ｂｐｓ－＞３０ブロック
	１４４００ｂｐｓ－＞３６ブロック
	尚、キャリア断時間の変更はＮＯ＿ＣＡＲＲＹ＿ＭＡＸＴＩＭＥを変更するだけ
	現在５秒に設定
	]
	date		:[1993/12/28]
	author		:[曽根岡拓]
*************************************************************************/
#define MSG_DECODE_TIME_OVER	90
UBYTE		G3_Rx(void)
{
	MESSAGE_t	*MDM_Msg;
	struct Timer10msData_t DecodeTimer;
	struct DMA_Data_t CodecRxDMA;
	UWORD	err_rate;
	UWORD	no_carry_cnt;
	UWORD 	ecm_buffer_block; /* added by H.Kubo 1998/01/23 */
	UBYTE	rtn;
	UBYTE	page_loop;
	UWORD	current_total_line;
	UBYTE	loop_flg;
	UBYTE		*ebf_base_rp;	/*	ＥＣＭバッファ先頭読み出しポインタ	*/
	UBYTE	debugsw;	/*	このデバッグSwは残しておいたほうが、後々便利です	*/
	UWORD	mdm_debugmsg;	/* for ＣＩＬ */

	mdm_debugmsg = 0;	/* for ＣＩＬ */
	debugsw = 0;	/*	このデバッグSwは残しておいたほうが、後々便利です	*/
	ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	ebf_base_rp = (UBYTE *) &EcmBuffer[0][0];	/**	ＥＣＭバッファ読み出し先頭アドレス設定	*/
	no_carry_cnt = 0;	/**	キャリア断カウンタ初期化	*/
	MDM_RxTotalLine = 0;	/**	１ページトータルライン数初期化	*/
	MDM_RxErrorTotalLine = 0;	/**	１ページエラーライン数初期化	*/
	MDM_EncodeLine = 0;
	MDM_NoCarryOrErrorCount = 0;
	MDM_CurrentTotalErrorLine = 0;
	MDM_CurrentDecodeLine = 0;
	MDM_CurrentDecodeErrorLine = 0;

	/*--------------------------*/
	/*	ＭＡＸキャリア断設定	*/
	/*--------------------------*/
	CarryDownBlock = (UWORD)(300 * (UWORD)(CHK_NoCarryOrErrorLineTime()));
	CarryDownBlock = (CarryDownBlock*(ModemBlock.Speed+1))/256;
	CarryDownBlock++;	/* 切り上げ処理 */

	/*----------------------*/
	/*	エラー判定基準7定	*/
	/*----------------------*/
	err_rate = CHK_RTN_TxRate();	/*	エラー判定基準設定	*/

	/*----------------------*/
	/* ＣＩＬ付加の処理     */
	/*----------------------*/
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* DISABLEだとコンパイル通らないため、条件コンパイル追加 2001/12/21 T.Takagi */
	if (CMN_CheckCILEnable()) {	/* 下のifと同義なのでコードの無駄 */
		if (CHK_UNI_CILPrintOn()) {
			/** 受信１ページ符号変換タスクより ＣＩＬ作成完了を待ちます */
			while (1) {	/* ＣＩＬ付加デコード終了するまで待つ */
				rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	デコード開始メッセージ受信	*/
				mdm_debugmsg = (UWORD)MDM_Msg->Message;
				if (mdm_debugmsg == MSG_CIL_COMPLETE) {
					break;
				}
			}
		}
	}
#endif
	/*----------------------*/
	/*	先頭ダミー無視処理	*/
	/*----------------------*/
	MDM_G3DummyDataDetecting = 1;	/* ダミーデータ無視処理中 1997/12/25 */
	loop_flg = 1;	/**	ループ制御フラグ１に設定	*/
	while (loop_flg) {	/**	ＥＯＬ検出／キャリア断するまでループ	*/
		rtn = RxG3_Read();	/**	受信データリード	*/
		if (rtn == RCV_BLOCK) {	/**	受信データ有り	*/
			if (DetectEOL(&MDM_ModemBuffer[ModemControl.ReadPoint][0]) == 0) {	/**	ＥＯＬ検出処理で、ＥＯＬ検出時	*/
				no_carry_cnt = 0;	/**	キャリア未検出カウンタクリア	*/
				break;
			}
			else {	/**	ＥＯＬ未検出時	*/
				no_carry_cnt++;	/**	キャリア未検出カウンタ更新	*/
				if (no_carry_cnt >= CarryDownBlock) {	/**	キャリア断カウンタを越えた時	*/
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					return (RX_CARRIER_DOWN);	/**	キャリア断設定、関数抜ける	*/
				}
			}
			NextMdmBufReadPointSetExtRom();
		}
		else if (rtn == RCV_STOP) {	/**	ストップＳｗ検出時	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			return (RX_STOPPED);	/**	ストップＳｗ、関数抜ける	*/
		}
		else {	/**	受信データ無し	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			return (RX_CARRIER_DOWN);	/**	キャリア断設定、関数抜ける	*/
		}
	}
	MDM_G3DummyDataDetecting = 0;	/* ダミーデータ無視処理中 1997/12/25 */

	MDM_LineDecodeStartTimer = SYS_GeneralTimer;

	/*------------------------------*/
	/*	イコライザーホールド処理	*/
	/*------------------------------*/
	if (CHK_V17EqualizerHold()) {	/**	イコライザホールドのメモリスイッチが有効の時	*/
		if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
			EqualizerHoldOn();	/**	イコライザホールドに設定	*/
		}
	}

	/*----------------------*/
	/*	タイマタスク起動	*/
	/*----------------------*/
#if (PRO_PRINTER_RX == ENABLE) || (PRO_PRINT_TYPE == THERMAL_TRANS) /* for HINOKI2 2002/01/07 T.Takagi */
	if (RxPmType != RX_PRINTER) {	/**	プリンタ受信	*/
		DecodeTimer.Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
	}
	else {
		DecodeTimer.Time = 13000/10; /* 13 秒 by H.Kubo 1999/03/31 */
	}
#else
	DecodeTimer.Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
#endif
	DecodeTimer.SendMBX = mbxno.MDM_RxEcmControlTask;	/**	メッセージ受信、メイルボックス設定	*/
	DecodeTimer.ReturnValue = MSG_DECODE_TIME_OVER;	/**	戻り値設定	*/
	tskno_DecodeTimer = 0xffff;
	cre_tsk(&tskno_DecodeTimer, TSK_CMN_MAN_TIMER10MSTASK, &DecodeTimer);	/**	タイマタスク起動	*/

	/*------------------------------------------------------*/
	/*	ＥＣＭバッファからモデムバッファにプログラム転送	*/
	/*------------------------------------------------------*/
	if (debugsw == 1) {	/*	このデバッグルーチンは残しておいたほうが、後々便利です	*/
		if (ebr_cnt < 0x10000) {
			MemoryMove((UBYTE  *)(ebf_base_rp+ebr_cnt),
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
	      (UBYTE  *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], MDM_ModemDmaSize);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*//** 256 Bytes **/
			ebr_cnt += MDM_ModemDmaSize;	/** 256 Bytes or lower **/
#else
	      (UBYTE  *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], MODEM_DMA_SIZE);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*//** 256 Bytes **/
			ebr_cnt += MODEM_DMA_SIZE;	/** 256 Bytes **/
#endif
		}
	}

#if (PRO_CPU == SH7043) && (PRO_EXT_DMAC == ENABLE) && (PRO_COM_CODEC_TYPE != SOFTWARE) /* Added by H.Kubo 1997/11/11 */
/* 条件を復活させました。HINOKI2ではelseを通ります。2002/02/12 T.Takagi */
#if (MODEM_DMA_SIZE > ECM_BUFFER_LENGTH)
#error "ECM_BUFFER_LENGTH is smaller than MODEM_DMA_SIZE. This progam may fail."
#endif /* (MODEM_DMA_SIZE > ECM_BUFFER_LENGTH) */

	/*------------------------------------------------------*/
	/*	モデムバッファからＥＣＭバッファにプログラム転送	*/
	/*------------------------------------------------------*/
	/* POPLAR_H では、外付けの DMAC uPD71021 を使って通信コーデックに
	** 受信データを転送します。外付けの DMAC のアドレスピンは 24bit のため、
	** DRAM 領域にしかアクセスできません。そのため、モデムバッファに受けた
	** データをＥＣＭバッファに転送してから通信コーデックへ送るようにします。
	*/
 #if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
	MemoryMove((UBYTE *)&EcmBuffer[ModemControl.ReadPoint][0], (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MDM_ModemDmaSize);
 #else
	MemoryMove((UBYTE *)&EcmBuffer[ModemControl.ReadPoint][0], (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MODEM_DMA_SIZE);
 #endif
	CodecRxDMA.SrcAddress	= (UDWORD)&EcmBuffer[ModemControl.ReadPoint][0];	/*	絶対アドレスに変換	*/

/* #if (0) */  /* thonda */	/* 条件を復活させました。2002/02/12 T.Takagi */
#else /* (PRO_COM_CODEC_TYPE != SOFTWARE) && (PRO_EXT_DMAC == ENABLE) && (PRO_CPU == SH7043)  */
	/*CodecRxDMA.StartAddress	= DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.ReadPoint][0]);	*/ /*	絶対アドレスに変換	*/
	CodecRxDMA.SrcAddress	= (UDWORD)&MDM_ModemBuffer[ModemControl.ReadPoint][0];	/*	絶対アドレスに変換	*/
#endif /* (PRO_COM_CODEC_TYPE != SOFTWARE) && (PRO_EXT_DMAC == ENABLE) && (PRO_CPU == SH7043)  */
/* #endif */

	/*------------------------------------------*/
	/*	通信コーデック復号化Ｖ５３ＤＭＡセット	*/
	/*------------------------------------------*/
	/* CodecRxDMA.Item			= MASTER_DMAU; */ /* Commented out by H. Kubo for POPLAR_H. 1997/06/23 */
	CodecRxDMA.Channel		= DMA_CH_DEC;

	/* CodecRxDMA.Counter		= (MODEM_DMA_SIZE/2)-1;*/	/** 256 Bytes **/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
	CodecRxDMA.Counter		= (MDM_ModemDmaSize/2); /** 256 Bytes **//* Modified by H. Kubo for new DMA routine 1997/06/25 */
#else
	CodecRxDMA.Counter		= (MODEM_DMA_SIZE/2); /** 256 Bytes **//* Modified by H. Kubo for new DMA routine 1997/06/25 */
#endif
	CodecRxDMA.Unit			= DMA_WORD_TRANSFER;
	CodecRxDMA.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&CodecRxDMA);
	DMA_RequestEnable(CodecRxDMA.Channel);	 /**	通信コーデック復号化Ｖ５３ＤＭＡ起動	*/


#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* by H.Kubo 1999/03/20 *//* By M.Maeda 2002/10/24 */
	/**	ＤＭＡ転送完了監視タスク起動	*/
	/* SAKAKI プリンタ受信で受信画が壊れる対策。モデムバッファを監視します。
	** by H.Kubo 1999/03/20
	*/
	if (RxPmType == RX_PRINTER) {	/**	プリンタ受信	*/
		tskno_RxDMA_TC_Detect = 0xffff;
		cre_tsk(&tskno_RxDMA_TC_Detect, TSK_MDM_RXDMA_TC_DETECTTASK, 0);
	}
	/* EcmBuffer 管理変数初期化 */
	EcmBufferBaseWritePoint = (UDWORD) &EcmBuffer[0][0]; /* EcmBuffer に溜まって、 Codec への DMA 転送待ちをしているデータの最下位アドレス */
	EncodeDataCount = 0;	/* /* EcmBuffer に溜まって、 Codec への DMA 転送待ちをしているデータのバイト数 */
#endif


	/*----------------------------------*/
	/*	モデムバッファ読み出し位置更新	*/
	/*----------------------------------*/
	NextMdmBufReadPointSetExtRom();
	page_loop = 1;	/**	ループ制御フラグ１に設定	*/
	while (page_loop) {	/**	１ページ受信完了／デコードエラー／その他エラーするまでループ	*/
		/*--------------------------------------*/
		/*	メッセージ受信待ち					*/
		/*	1.デコードＤＭＡ終了割り込みより	*/
		/*	2.１ページ符号変換タスクより		*/
		/*	3.受信デバイス監視タスクより		*/
		/*--------------------------------------*/
		do {
			rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	メッセージ受信待ち	*/
		} while (!((MDM_Msg->Message == MSG_FROM_DECODEDMA_TC_TASK) ||
		           (MDM_Msg->Message == MSG_FROM_CODE_CONVERT_TASK) ||
		           (MDM_Msg->Message == MSG_DECODE_TIME_OVER) ||
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* by H.Kubo 1999/03/20 *//* By M.Maeda 2002/10/24 */
				   (MDM_Msg->Message == MSG_DMA_STOP) ||				 /* モデムバッファ一本受信完了 */
#endif
	           (MDM_Msg->Message == MSG_FROM_DEVICE_CONTROL_TASK)));
#if (PRO_PRINTER_RX == ENABLE) || (PRO_PRINT_TYPE == THERMAL_TRANS)	/* ported for HINOKI2 2002/01/07 T.Takagi */
		if ((MDM_Msg->Message == MSG_DECODE_TIME_OVER) && (RxPmType == RX_PRINTER)) {	/**	プリンタ受信でコーデック異常	*/
			CodecPageStatus = CDC_DECODE_ERROR; /* デコードエラーにして強制的に終了させます。 */
		}
		else
#endif
		if (MDM_Msg->Message == MSG_DECODE_TIME_OVER) {
			if (CheckCodec(COMMUNICATION_CODEC)) { /* Changed for new CheckCodec function by H.Kubo 1997/06/30 */
				MDM_RxTotalLine = DecodeLine(COMMUNICATION_CODEC);	/**	デコードライン更新	*/
				MDM_RxErrorTotalLine = ErrorLine(COMMUNICATION_CODEC);	/**	エラーライン数獲得	*/
				MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
#if (PRO_PRINTER_RX == ENABLE) /* added By H.Hirao 1998/10/28 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
				if (CommunicateType == RX_G3_MEM) {
					if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
						SaveReturnAddressAndJumpBegin();
					}
				}
				else{
					if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
						SaveReturnAddressAndJumpBegin();
					}
				}
#else
	#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*//* By M.Maeda 2002/10/24 */
				if (CommunicateType == RX_G3_MEM) {
					if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
						SaveReturnAddressAndJumpBegin();
					}
				}
				else{
					if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
						SaveReturnAddressAndJumpBegin();
					}
				}
	#else
				if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
					SaveReturnAddressAndJumpBegin();
				}
	#endif
#endif
			}
			if (tskno_RxPixControl != 0xffff) {
				del_tsk(&tskno_RxPixControl);
			}
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/20 */
			/* ported for HINOKI2 2002/01/07 T.Takagi */
			if (tskno_CDC_PRxDMA_Task != 0xFFFF) {
				del_tsk(&tskno_CDC_PRxDMA_Task);
			}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*//* 2002/10/24 By M.Maeda */
			if (tskno_CDC_PRxDMA_Task != 0xFFFF) {
				del_tsk(&tskno_CDC_PRxDMA_Task);
			}
#endif
			tskno_RxPixControl = 0xffff;
			CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
			CodecRestartFlag = 0; /* Move Here By M.Kotani 1997/03/22 */
#if (PRO_PRINTER_RX == ENABLE) /* added By H.Hirao 1998/10/28 */
			/* ported for HINOKI2 2002/01/07 T.Takagi */
			if (CommunicateType == RX_G3_MEM) {
				cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
			}
			else {
				cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
			}
#else
	#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 199/2/12 K.Kawata*//* By M.Maeda 2002/10/24 */
			if (CommunicateType == RX_G3_MEM) {
				cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
			}
			else {
				cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXDECODEPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
			}
			/**	ＤＭＡ転送完了監視タスク起動	*/
			/* SAKAKI プリンタ受信で受信画が壊れる対策。モデムバッファを監視します。
			** by H.Kubo 1999/03/20
			*/
			if (tskno_RxDMA_TC_Detect != 0xffff) {
				del_tsk(&tskno_RxDMA_TC_Detect);
			}
			if (tskno_RxDMA_TC_Detect == 0xffff) {
				cre_tsk(&tskno_RxDMA_TC_Detect, TSK_MDM_RXDMA_TC_DETECTTASK, 0);
			}
	#else
			cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
	#endif
#endif
			while (!CodecRestartFlag) {
				wai_tsk(1);
			}
		}
		if (tskno_DecodeTimer != 0xffff) {
			del_tsk(&tskno_DecodeTimer);
		}

		/* 1997/01/30 Y.Murata
		 * キャリア断の検出
		*/
		/* current_total_line = DecodeLine();	/**	デコードライン更新	*/
		current_total_line = DecodeLine(COMMUNICATION_CODEC);	/**	デコードライン更新	*//* Changed by H.Kubo 1997/06/30 */
		if (MDM_RxTotalLine == current_total_line) {	/*	デコードラインが更新されていない時	*/
			no_carry_cnt++;		/**	キャリア未検出カウンタ更新	*/
			MDM_NoCarryOrErrorCount++;	/**	キャリア未検出カウンタ更新	*/
			if (no_carry_cnt>=CarryDownBlock) {	/**	キャリア断カウンタを越えた時	*/
				MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
				rtn = RX_CARRIER_DOWN;	/**	戻り値キャリア断設定	*/
				break;
			}
		}
		else {	/**	デコードラインが更新されている時	*/
			MDM_LineDecodeStartTimer = SYS_GeneralTimer;
			no_carry_cnt = 0;	/**	キャリア未検出カウンタ初期化	*/
			MDM_CurrentDecodeLine = (current_total_line - MDM_RxTotalLine);	/* 現在ﾃﾞｺｰﾄﾞしたﾗｲﾝ数 */
			MDM_RxTotalLine = current_total_line;	/**	１ページ受信トータルライン数更新	*/
			MDM_CurrentTotalErrorLine = ErrorLine(COMMUNICATION_CODEC);	/**	エラーライン数獲得	*/ /*Changed by H.Kubo 1997/06/30 */
			if (MDM_RxErrorTotalLine == MDM_CurrentTotalErrorLine) {	/* ｴﾗｰﾗｲﾝがなし */
				MDM_NoCarryOrErrorCount = 0;
			}
			else {	/* ｴﾗｰﾗｲﾝがあった */
				MDM_CurrentDecodeErrorLine = (MDM_CurrentTotalErrorLine - MDM_RxErrorTotalLine);	/* 現在ﾃﾞｺｰﾄﾞしたｴﾗｰﾗｲﾝ数 */
				MDM_RxErrorTotalLine = MDM_CurrentTotalErrorLine;	/* ｴﾗｰﾗｲﾝ更新 */
				if (MDM_CurrentDecodeLine == MDM_CurrentDecodeErrorLine) {	/* ﾃﾞｺｰﾄﾞしたﾗｲﾝがすべてｴﾗｰだった */
					MDM_NoCarryOrErrorCount++;
				}
			}
		}
		if (MDM_CarryDownErrorOrTotalLine()) {
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_CARRIER_DOWN;	/**	戻り値キャリア断設定	*/
			break;
		}

		/*
		** 受信３Ｍオーバチェック処理追加
		** 1999/02/02 by T.Soneoka
		** ported by H.Kubo 1999/09/14
		*/
		if (MDM_RxTotalLine >= Rx3mErrorLine) {
			CodecPageStatus = CDC_PAGE_SEPARATE;	/* 最大デコードライン数に達した */
		}


#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* by H.Kubo 1999/03/20 *//* 2002/09/18 By M.Maeda */
		/* SAKAKI プリンタ受信で受信画が壊れる対策。記録紙の準備ができる前に
		** モデムバッファ溢れが起こるので、モデムバッファの空きが少なくなったら
		** モデムバッファに溜まった受信データを ECM バッファに待避します。
		** プリンタ受信のない機種では必要ないでしょう。また、 POPLAR_H の
		**  ECM バッファの使い方とは共存できないので注意してください。
		** by H.Kubo 1999/03/20
		*/
		if (MDM_Msg->Message == MSG_DMA_STOP) { /* モデムバッファ一本受信完了 */
			/* モデムバッファ受信完了監視タスク削除 */
			if (tskno_RxDMA_TC_Detect != 0xffff) {
				del_tsk(&tskno_RxDMA_TC_Detect);
			}
			/* モデムバッファ受信完了監視タスク再起動 */
			/**	ＤＭＡ転送完了監視タスク起動	*/
			cre_tsk(&tskno_RxDMA_TC_Detect, TSK_MDM_RXDMA_TC_DETECTTASK, 0);
			if (MDM_G3RxModemBufferToEcmBuffer()) {		 /* モデムバッファから ECM バッファへ待避 */
				continue; /* added by H.Kubo 1999/03/24 */
			}
		}
		else if (MDM_Msg->Message == MSG_FROM_DECODEDMA_TC_TASK) { /* コーデックへのＤＭＡ転送終了 */
			if (RxPmType == RX_PRINTER) {
				if ((CodecPageStatus == CDC_CONTINUE) || (CodecPageStatus == CDC_READY)) {	/**	 デコード継続中の時	*/
					if (MDM_G3RxNextDmaFromEcmBuffer()) {
						MDM_G3Rx_CreateDecodeTimer(&DecodeTimer); /* added by H.Kubo 1999/03/31 */
						continue; /* まだ DMA が終了していないか次の DMA 転送もECM バッファからなので、モデムバッファはチェックせずに済ませる。 */
					}
					/* デバッグ用にここにも入れます。 by H.Kubo 1999/03/30 */
					if (MDM_G3RxModemBufferToEcmBuffer()) {		 /* モデムバッファから ECM バッファへ待避 */
						MDM_G3Rx_CreateDecodeTimer(&DecodeTimer); /* added by H.Kubo 1999/03/31 */
						continue; /* added by H.Kubo 1999/03/24 */
					}
				}
			}
		}
#endif

		switch (CodecPageStatus) {	/**	デコード終了状態	*/
		case CDC_CONTINUE:	/**	デコード継続中の時	*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* ここにきても、デコード用 DMA がまだ動いている場合がある。by H.Kubo 1999/03/24 *//* By M.Maeda 2002/10/24 */
			if (RxPmType == RX_PRINTER) { /* プリンタ受信のみとします。 by H.Kubo 1999/03/30 */
				DMA_RequestMask(DMA_CH_DEC);	/* Memory to CODEC の DMA を停止 */
				if (DMA_CheckDMA_Counter(DMA_CH_DEC) > 0) {
					DMA_Continue(DMA_CH_DEC);
					continue;
				}
			}
#endif
			rtn = RxG3_Read();	/**	受信データリード	*/
			if (rtn == RCV_BLOCK) {	/**	受信データ有り	*/
				/*----------------------*/
				/*	タイマタスク起動	*/
				/*----------------------*/
#if (PRO_PRINTER_RX == ENABLE) || (PRO_PRINT_TYPE == THERMAL_TRANS) /* for HINOKI2 2002/01/07 T.Takagi */
				if (RxPmType != RX_PRINTER) {	/**	プリンタ受信	*/
					DecodeTimer.Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
				}
				else {
					DecodeTimer.Time = 13000/10; /* 13 秒 by H.Kubo 1999/03/31 */
				}
#else
				DecodeTimer.Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
#endif
				DecodeTimer.SendMBX = mbxno.MDM_RxEcmControlTask;	/**	メッセージ受信、メイルボックス設定	*/
				DecodeTimer.ReturnValue = MSG_DECODE_TIME_OVER;	/**	戻り値設定	*/
				tskno_DecodeTimer = 0xffff;
				cre_tsk(&tskno_DecodeTimer, TSK_CMN_MAN_TIMER10MSTASK, &DecodeTimer);	/**	タイマタスク起動	*/

				/*------------------------------------------------------*/
				/*	ＥＣＭバッファからモデムバッファにプログラム転送	*/
				/*------------------------------------------------------*/
				if (debugsw == 1) {	/*	このデバッグルーチンは残しておいたほうが、後々便利です	*/
					if (ebr_cnt < 0x10000) {
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
						MemoryMove((UBYTE  *)(ebf_base_rp+ebr_cnt),
						           (UBYTE  *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], MDM_ModemDmaSize);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*//** 256 Bytes **/
						ebr_cnt += MODEM_DMA_SIZE;	/** 256 Bytes **/
#else
						MemoryMove((UBYTE  *)(ebf_base_rp+ebr_cnt),
						           (UBYTE  *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], MODEM_DMA_SIZE);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*//** 256 Bytes **/
						ebr_cnt += MODEM_DMA_SIZE;	/** 256 Bytes **/
#endif
					}
				}
				/* 1st argument CodecRxDMA.Item of the following three lines are deleted by H.Kubo 1997/06/24 */

#if (PRO_CPU == SH7043) && (PRO_EXT_DMAC == ENABLE) && (PRO_COM_CODEC_TYPE != SOFTWARE) /* Added by H.Kubo 1997/11/11 */
/* 条件を復活させました。HINOKI2ではelseを通ります。2002/02/12 T.Takagi */
#if (MODEM_DMA_SIZE > ECM_BUFFER_LENGTH)
#error "ECM_BUFFER_LENGTH is smaller than MODEM_DMA_SIZE. This progam may fail."
#endif /* (MODEM_DMA_SIZE > ECM_BUFFER_LENGTH) */

			/*------------------------------------------------------*/
			/*	モデムバッファからＥＣＭバッファにプログラム転送	*/
			/*------------------------------------------------------*/
			/* POPLAR_H では、外付けの DMAC uPD71021 を使って通信コーデックに
			** 受信データを転送します。外付けの DMAC のアドレスピンは 24bit のため、
			** DRAM 領域にしかアクセスできません。そのため、モデムバッファに受けた
			** データをＥＣＭバッファに転送してから通信コーデックへ送るようにします。
			*/

 #if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
				MemoryMove((UBYTE *)&EcmBuffer[ModemControl.ReadPoint][0], (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MDM_ModemDmaSize);
 #else
				MemoryMove((UBYTE *)&EcmBuffer[ModemControl.ReadPoint][0], (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MODEM_DMA_SIZE);
 #endif
				DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)&EcmBuffer[ModemControl.ReadPoint][0]);

/* #if (0) */  /* thonda */ /* 条件を復活させました。2002/02/12 T.Takagi */
#else /* (PRO_COM_CODEC_TYPE != SOFTWARE) && (PRO_EXT_DMAC == ENABLE) && (PRO_CPU == SH7043)  */
				DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)&MDM_ModemBuffer[ModemControl.ReadPoint][0]);
#endif /* (PRO_COM_CODEC_TYPE != SOFTWARE) && (PRO_EXT_DMAC == ENABLE) && (PRO_CPU == SH7043)  */
/* #endif */

				/*DMA_SetDMA_BaseCurrentCounter(CodecRxDMA.Channel, (MODEM_DMA_SIZE/2)-1);*/	/** 256 Bytes **/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
				DMA_SetDMA_Counter(CodecRxDMA.Channel, (MDM_ModemDmaSize/2));	/** 256 Bytes **//* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta*/
#else
				DMA_SetDMA_Counter(CodecRxDMA.Channel, (MODEM_DMA_SIZE/2));	/** 256 Bytes **//* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta*/
#endif
				DMA_RequestEnable(CodecRxDMA.Channel);	/**	通信コーデック復号化Ｖ５３ＤＭＡ起動	*/
				NextMdmBufReadPointSetExtRom();
			}
			else if (rtn == RCV_STOP) {	/**	ストップＳｗ有効	*/
				MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
				rtn = RX_STOPPED;	/**	戻り値ストップＳｗ設定	*/
				page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			}
			else {	/**	受信データ無し	*/
				MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
				rtn = RX_CARRIER_DOWN;	/**	戻り値キャリア断設定	*/
				page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			}
			break;
		case CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			if (err_rate <= (UWORD)(((UDWORD)(MDM_RxErrorTotalLine)*100)/((UDWORD)MDM_RxTotalLine))) {	/**	エラーライン数が基準値以上の時	*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
				if (CHK_DisasterPreventionFaxEnable()) {
					/* 防災FAXはエラーライン数はチェックしない */
					rtn = RX_PAGE_END;	/**	戻り値１ページ受信終了設定	*/
				}
				else {
				 	/** 画品質不良の場合 */
					rtn = RX_ERROR;	/**	戻り値受信エラー設定	*/
				}
#else
		 	/** 画品質不良の場合 */
				rtn = RX_ERROR;	/**	戻り値受信エラー設定	*/
#endif
			}
			else {
				rtn = RX_PAGE_END;	/**	戻り値１ページ受信終了設定	*/
			}
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		case CDC_STOPPED:	/**	デコード強制終了時	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STOPPED;	/**	戻り値ストップＳｗ設定	*/
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		case CDC_DECODE_ERROR:	/**	デコードエラー（復帰不可能）発生時	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_ERROR;	/**	戻り値受信エラー設定	*/
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		case CDC_PAGE_SEPARATE:	/**	最大デコードライン数に達した時	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_OVER;	/**	戻り値最大受信長オーバ設定	*/
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		case CDC_CONTI_ERROR:
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_CONTI_ERR;
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
#if (PRO_PRINTER_RX == ENABLE)		/* Takeuchi	 Nov.15.1994 */
		/* ported for HINOKI2 2002/01/07 T.Takagi */
		case CDC_PRINTER_ERROR:
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_PRT_ERR;
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*//* By M.Maeda 2002/10/24 */
		case CDC_PRINTER_ERROR:
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_PRT_ERR;
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* SAKAKI プリンタ受信対策 by H.Kubo 1999/03/20 *//* 2002/09/18 By M.Maeda */
		case CDC_READY:
			MDM_G3Rx_CreateDecodeTimer(&DecodeTimer); /* added by H.Kubo 1999/03/31 */
			break; /* 何もしないで続ける */
#endif
		case CDC_MEM_OVER:	/**	メモリオーバ時	*/
		default:
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_MEM_OVER;	/**	戻り値メモリオーバ設定	*/
			page_loop = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		}
	}
	return (rtn);
}


/*************************************************************************
	module		:[ＥＣＭ受信]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_PhaseC_Status
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/28]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		EcmRx(void)
{
	UBYTE	retry_cnt;	/**	モデムリードリトライカウンタ	*/
	UBYTE	mdm_cnt_save;	/**	ショートフレーム対策用モデム書き込み位置保存	*/
	UBYTE	short_flg;	/**	ショートフレーム対策用ショートフレーム受信有無フラグ	*/
	UBYTE	rtn;
	UBYTE	loop_flg;
	UBYTE	hold_flg;
	UBYTE	dust_data;
	volatile UWORD rx_frame_num;
#if defined (KEISATSU) /* 警察FAX 05/09/01 石橋正和 */
	UWORD ecm_size;
#endif
	
	rx_frame_num = 0;
	
	short_flg = 0;	/**	ショートフレームフラグ初期化	*/

	
	if (CHK_UNI_ECM_RxTM_OutEvade()) { /* CHK_ECM_RxTM_OutEvade => CHK_UNI_ECM_RxTM_OutEvade  by H.Kubo 1997/07/08 */
		retry_cnt = 3;
	}
	else {
		retry_cnt = 0;
	}

	/*--------------------------*/
	/* 海外認可共通対応         */
	/* FOREIGN_APPROVAL No.1-4  */
	/*--------------------------*/
	/* ドイツ申請時、キャリア断の時、６±１秒で回線断させるため
	*/
	if (CHK_ForeignApprovalDEU()) {
		if (CHK_UNI_ECM_RxTM_OutEvade() == 0) {
			retry_cnt = 3;
		}
	}

	mdm_cnt_save = 0;	/**	ショートフレーム対策用モデム書き込み位置初期化	*/
	MDM_EcmFrameNumber = 0;	/**	ＥＣＭフレームナンバー初期化	*/

	hold_flg = 0;

	/* Ｖ．３４モード時、ＥＱＭ値を読み出すためにタスクを生成します。 */
	if (SYS_V34ProcedureExecuting()) {
		tskno_EyeQualityMonitor = 0xffff;
		cre_tsk(&tskno_EyeQualityMonitor,TSK_MDM_READEQMVALUETASK,0);
	}

#if defined (KEISATSU) /* 警察FAX 05/09/01 石橋正和 */
	if (FCM_S1_Scramble == TRUE) {
		ecm_size = FcomEcmSize + 4;
	}
	else {
		ecm_size = FcomEcmSize + 7;
	}
#endif
	
	loop_flg = 1;	/**	ループ制御フラグ１に設定	*/
	while (loop_flg) {/**	１ブロック受信するまでループ	*/
		rtn = RxEcmRead();	/**	受信ＥＣＭリード	*/
		if (rtn == RCV_BLOCK) {	/**	受信フレーム有り	*/
			/*------------------------------*/
			/*	イコライザーホールド処理	*/
			/*------------------------------*/
			if (hold_flg == 0) {
				if (CHK_V17EqualizerHold()) {	/**	イコライザホールドのメモリスイッチが有効の時	*/
					if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
						EqualizerHoldOn();	/**	イコライザホールドに設定	*/
					}
				}
				hold_flg = 1;
			}
			switch (MDM_ModemBuffer[ModemControl.ReadPoint][FCF_FLD]) {	/**	受信フレームのＦＣＦフィールドを見る	*/
			/*--------------------------*/
			/*	ＦＣＤフレーム受信処理	*/
			/*--------------------------*/
			case HDLC_FCD:	/**	ＦＣＤフレーム受信の時	*/
				MDM_EcmFrameNumber = MDM_ModemBuffer[ModemControl.ReadPoint][FIF_FLD];	/**	ＥＣＭフレームナンバをセット	*/
				/*----------------------*/
				/* ショートフレーム処理	*/
				/*----------------------*/
#if defined (KEISATSU) /* 警察FAX 05/09/01 石橋正和 */
				if (MDM_RxSize[ModemControl.ReadPoint] != ecm_size) {
#else
/**	アドレス＋コントロール＋ＦＣＤ＋フレームＮｏ＋ＦＩＦ（２５６／６４）＋ＦＣＳ（２バイト）＋フラグ *//**  By O.K Jan.23,1996 **/
				if (MDM_RxSize[ModemControl.ReadPoint] != (FcomEcmSize+7)) {
#endif
					short_flg = 1;	/**	ショートフレーム受信フラグセット	*/
					MemoryMove((UBYTE *)FaxComTxFrame, (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MODEM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
					break;
				}
				short_flg = 0;	/**	ショートフレーム受信フラグ初期化	*/
				/*-------------------------------------------------------*/
				/*	モデムバッファからＥＣＭバッファにプログラム転送処理 */
				/*-------------------------------------------------------*/
				MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0],(UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD], (UWORD)ECM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
				/*------------------------------------------*/
				/*	ＥＣＭバッファフレームステータス有効	*/
				/*------------------------------------------*/
				EnableEcmStatus(MDM_EcmFrameNumber);	/**	ＥＣＭバッファフレームステータス有効	*/
				break;
			/*----------------------*/
			/*	ＲＣＰフレーム受信	*/
			/*----------------------*/
			case HDLC_RCP:	/**	ＲＣＰフレーム受信の時	*/
				loop_flg = 0;	/**	ループ制御フラグ０に設定	*/

				/*-------------------------------------*/
				/*	最終フレームがショートフレームの時 */
				/*-------------------------------------*/
				if (short_flg == 1) {	/**	ショートフレーム受信済み	*/
					MDM_EcmFrameNumber = FaxComTxFrame[FIF_FLD];
					/*-------------------------------------------------------*/
					/*	モデムバッファからＥＣＭバッファにプログラム転送処理 */
					/*-------------------------------------------------------*/
/*
** インデック潰す件、ＥＣＭバッファへの転送バイト数が間違っています
** ショートフレームの場合でも、２５６分固定でＥＣＭバッファに転送します
** 1998/03/31 by T.Soneoka
*/
#if (0)
//#if (0) /* 念のためRxFrameLengthが変な値でもＤＲＡＭを壊さないようにします */
////					MemoryMove(&EcmBuffer[MDM_EcmFrameNumber][0],&FaxComTxFrame[FDF_FLD], (RxFrameLength-2));	/**	ショートフレーム保存	*/
//#endif					
//					if (RxFrameLength <= (FcomEcmSize+7)) {
//						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
//#if (0)	/* 1998/03/24 調査終了 */
////						if (debug_swap) {	/* ＪＢＩＧ調査 Ｓｗａｐ処理 1998/03/23 by T.Soneoka */
////							MemoryMoveSwap((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (WORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
////						else {
////							MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
//#endif
//					}
//					else {
//						RxFrameLength = FcomEcmSize+7;
//						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
//#if (0)	/* 1998/03/24 調査終了 */
////						if (debug_swap) {	/* ＪＢＩＧ調査 Ｓｗａｐ処理 1998/03/23 by T.Soneoka */
////							MemoryMoveSwap((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (WORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
////						else {
////							MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
//#endif
//					}
#else
					MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)ECM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
#endif
					/*------------------------------------------*/
					/*	ＥＣＭバッファフレームステータス有効	*/
					/*------------------------------------------*/
					EnableEcmStatus(MDM_EcmFrameNumber);	/**	ＥＣＭバッファフレームステータス有効	*/
				}

				/* 1997/01/16 Y.Murata
				 * V17以下の時はRCP受信してるからRLSDのﾀｰﾝOFFをみなくてもよい
				 * RTDIS対策でRLSDの動作がおかしくなったらいややし、
				 * モデムを信用しない。TX側さつきでECMｎ時１発目のﾎﾟｽﾄﾒｯｾｰｼﾞをたまに取り逃がす
				 * その時RLSDのﾀｰﾝOFFが遅い
				*/
				if (SYS_V34ProcedureExecuting()) {
					/** プライマリーチャンネル終了処理（暫定） By O.K Feb.03,1996 **/
					CMN_DisableInterrupt();
					if ((!MDM_RlsdTurnOffFlag)&&(!MDM_FedOffFlag)) {
						wai_evt(EVT_MDM_TURNOFF);
					}
					MDM_RlsdTurnOffFlag = 0;
					CMN_EnableInterrupt();
				}
				DMA_RequestMask(DMA_CH_RX);
				while (inp(MDM_REG_0C_PORT) & IO_BIT_RXFNE) {
					dust_data = inp(MDM_REG_00_PORT);
				}

				rtn = MDM_PhaseC_Status;	/*	今現在のデーコード状態を返す	*/
				break;
			/*--------------------------*/
			/*	不当フレーム受信処理	*/
			/*--------------------------*/
			default:	/**	不当フレーム受信処理	*/
				break;
			}
			/*--------------------------------------*/
			/*	モデムバッファ読み出し位置更新処理	*/
			/*--------------------------------------*/
			NextMdmBufReadPointSetExtRom();
		}
		/*------------------------------*/
		/* タイムアウト時（６秒）処理	*/
		/*	現在３回で１８秒			*/
		/*------------------------------*/
		else if (rtn == RCV_TMOUT) {	/**	タイムアウト時	*/
			if (retry_cnt++ >= 3) {	/**	３回目のタイムアウト時	*/
				rtn = RX_TMOUT;	/**	戻り値タイムアウト設定	*/
				loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
			}
		}
		else if (rtn == RCV_STOP) {	/**	ストップＳｗ	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STOPPED;	/**	戻り値ストップＳｗ設定	*/
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
		}
		/** ポストメッセージ全く取れず対策（暫定） By O.K Feb.06,1996 **/
		else if (rtn == RCV_TURNOFF) {
#if 0	/* RNR-RRになる 1996/06/07 Y.Murata */
//			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/ /* 1996/06/05 Y.Murata */
//			rtn = RX_PAGE_END;
#endif
			rtn = RX_CONTINUE;
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		}
		else {	/**	その他の時	*/
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STUP_ERR;	/**	戻り値セットアップエラー設定	*/
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		}
		
		rx_frame_num++;
	}
	return(rtn);
}


/*************************************************************************
	module		:[ＥＣＭ受信コントロールタスク]
	function	:[
		1.ＥＣＭ受信したフレームをフレーム番号０から順次デコードを実行する
		2.受信フレームが無い場合１００ｍｓタスクウェイトをおき、
		　再度受信フレームがないかどうかチェックする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/22]
	author		:[曽根岡拓]
*************************************************************************/
void			MDM_RxEcmControlTask(void)
{
	MESSAGE_t	*MDM_Msg;

	UBYTE	TempLastFrameBuf[2]; /* JBIGループ不具合 RNR-RRでT.4.1 R.5.1で回線断 2000/12/20 by T.Soneoka *//* from nagano\fm336 2001/01/05 Y.M */

	UBYTE	page_loop;
	UWORD	result;
	struct DMA_Data_t CodecRxDMA;
	struct	MEM_IndexData_t	index_data;
	UBYTE	buf1;
	UBYTE	buf2;
	UBYTE	first_block;
	UWORD	mdm_debugmsg;	/* for ＣＩＬ */
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/10/27 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
	UBYTE	debug; /* For Printer Rx 1999/1/7 by T.Soneoka */
	debug = 0;
#endif

	mdm_debugmsg = 0;	/* for ＣＩＬ */
	first_block = 1;	/* JBIG追加   by T.Soneoka 1997/12/17 */
	IsDetLastFrameEndMaker = 0;	/*  追加 by T.Soneoka 1998/03/02 */
	IsDetEndMaker = 0;	/*  追加 by T.Soneoka 1998/03/02 */
	MDM_ForcedDecodeStart = 0;	/*  追加 by T.Soneoka 1998/03/02 */
	result = 0;
	DecodeEcmFrameNum = 0;
	CodecPageStatus = CDC_CONTINUE;	/**	符号変換終了ステータスを初期化	*/
	MDM_PhaseC_Status = RX_CONTINUE;
	MDM_RxTotalLine = 0;	/**	１ページトータルライン数初期化	*/
	MDM_RxErrorTotalLine = 0;	/**	１ページエラーライン数初期化	*/
	MDM_EncodeLine = 0;

	/*------------------------------*/
	/*	デコード開始メッセージ受信	*/
	/*------------------------------*/
	while (1) {
		rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	デコード開始メッセージ受信	*/
		if (MDM_Msg->Message == MSG_RX_DECODE_START) {
			break;
		}
	}
	/*------------------------------*/
	/*	Decode Detect Task Create	*/
	/*------------------------------*/
	DMA0_TC3Flag = 0;
	tskno_DecodeDMA_End = 0xffff;
	cre_tsk(&tskno_DecodeDMA_End, TSK_MDM_DECODEDMA_TC_DETECTTASK, 0);	/**	エンコードＶ５３ＤＭＡ終了監視タスク起動	*/

/*
** ＪＢＩＧ受信・ＴＰＯｎモードの場合は蓄積符号をＭＭＲにする対応 1998/05/01 by T.Soneoka
** ＭＮ８６０６４で符号変換コマンドＪＢＩＧ－＞ＭＧ３の場合、ＴＰ Ｏｆｆモードではループする
*/
	if (SYS_DocBlock.Src.Code != SYS_JBIG_CODE) {	/** 符号がＪＢＩＧの場合	*/
		if (CommunicateType == RX_ECM_MEM) {	/**	ＥＣＭメモリ受信の場合	*/
			/*------------------------------*/
			/*	メモリライトパラメータ設定	*/
			/*------------------------------*/
			RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
			RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
			RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
			/* RxMemoryStoreData.Code = CMNPRO_AvailableRxCodingMethod(); */
			/* RxMemoryStoreData.Code = AvailableRxCodingMethod; */ /* Changed for POPLAR_H by H.Kubo 1997/07/11 */

			RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);	/* Add By O.Kimoto 1998/05/20 */

			RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
			RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
			/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
			RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

			/*------------------------------*/
			/*	メモリライトオープン処理	*/
			/*------------------------------*/
			/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/10/14 Y.Suzuki */
			if (SYS_RxPrintFileItem != 0) {
				index_data.No   = SYS_RxPrintFileNo;
				index_data.Page = SYS_RxPrintFilePage;
				index_data.Item = SYS_RxPrintFileItem;
				index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
				result = MEM_DualOpen(&RxMemoryStoreData,
									  &index_data,
									  &MDM_MemoryExecData);
			}
			else {
				result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData);
			}
			if (result != MEM_OK) {
				if (result == MEM_INDEX_CONFLICT) {
					SYS_FaxComIndexConflictStatus = 1;
				}
				else {
					SYS_FaxComIndexConflictStatus = 0;
				}
				tskno_RxDeviceWriteControl = 0xffff;
				tskno_RxPixControl = 0xffff;
				BreakEcmTaskFlag = YES;
				MDM_BreakRxTask();		/**	受信子タスク終了処理	*/
				MDM_PhaseC_Status = RX_MEM_OVER;	/**	受信セットアップエラーセット	*/
				exi_tsk();	/**	自タスク終了処理	*/
			}
			else { /* by H.Kubo 1998/11/11 */
				IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
			}
		}

		/*----------------------*/
		/*	エンコード監視起動	*/
		/*----------------------*/
	#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/10/27 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
		if (CommunicateType == RX_ECM_MEM) {	/* ＥＣＭメモリ受信の場合 */
			tskno_RxDeviceWriteControl = 0xffff;
			cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
		}
	#else
	  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/12 K.Kawata*//* By M.Maeda 2002/10/24 */
		if (CommunicateType == RX_ECM_MEM) {	/* ＥＣＭメモリ受信の場合 */
			tskno_RxDeviceWriteControl = 0xffff;
			cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
		}
	  #else
		tskno_RxDeviceWriteControl = 0xffff;
		cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
	  #endif
	#endif
		/*--------------------------------------*/
		/*	受信１ページ符号変換タスク起動処理	*/
		/*--------------------------------------*/
		tskno_RxPixControl = 0xffff;
	#if (PRO_PRINTER_RX == ENABLE) /* Ported from ORANGE by H.Kubo 997/08/12 */
		/* ported for HINOKI2 2002/01/07 T.Takagi */
		if (CommunicateType == RX_ECM_MEM) {	/**	ＥＣＭメモリ受信の場合	*/
			cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
		}
		else {									/**	ＥＣＭプリンタ受信の場合	*/
			cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
		}
	#else /* (PRO_PRINTER_RX == ENABLE) */
	  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/12 K.Kawata*//* By M.Maeda 2002/10/24 */
		if (CommunicateType == RX_ECM_MEM) {
			cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
		}
		else {
			cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXDECODEPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
		}
	  #else
		cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
	  #endif
	#endif
		/*----------------------*/
		/* ＣＩＬ付加の処理     */
		/*----------------------*/
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* DISABLEだとコンパイル通らないため、条件コンパイル追加 2001/12/21 T.Takagi */
		if (CMN_CheckCILEnable()) {
			if (CHK_UNI_CILPrintOn()) {
				/** 受信１ページ符号変換タスクより ＣＩＬ作成完了を待ちます */
				while (1) {	/* ＣＩＬ付加デコード終了するまで待つ */
					rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	デコード開始メッセージ受信	*/
					mdm_debugmsg = (UWORD)MDM_Msg->Message;
					if (mdm_debugmsg == MSG_CIL_COMPLETE) {
						break;
					}
				}
			}
		}
#endif
		/*------------------------------------------*/
		/*	通信コーデック復号化Ｖ５３ＤＭＡセット	*/
		/*------------------------------------------*/
		CodecRxDMA.Channel		= DMA_CH_DEC;
		CodecRxDMA.SrcAddress	= (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
		CodecRxDMA.Counter		= (CODEC_DMA_SIZE/2); /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
		CodecRxDMA.Unit			= DMA_WORD_TRANSFER;
		CodecRxDMA.Direction	= DMA_MEMORY_TO_IO;
		DMA_SetupDMAU(&CodecRxDMA);
		
	}
	page_loop = 1;	/**	１ページデコード終了フラグ設定	*/
	
	while (page_loop) {	/**	１ページデコードするまでループ	*/
#if (PRO_PRINTER_RX == ENABLE)
		if (debug) {
			while (1) {
				if (FaxComPhaseStatus == FAX_RX_PH_D) {
					break;
				}
				wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
			}
		}
#endif
		/*------------------------------*/
		/*	ＥＣＭフレーム受信待ち処理	*/
		/*------------------------------*/
		if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) {	/** 符号がＪＢＩＧの場合	*/

			/***************************************************
			** ＮＥＷＬＥＮ検出遅れ対策 1998/02/19 by T.Soneoka 
			*/
			while (1) {
				if ((CheckEcmStatusExtRom(DecodeEcmFrameNum) == 1) /**	ＥＣＭフレームステータスが無効の時	*/
				&& (!MDM_ForcedDecodeStart)) {	/*  追加 by T.Soneoka 1998/03/02 */
					wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
					if (CodecPageStatus != CDC_CONTINUE) {
						break;
					}
				}
				else {
					break;
				}
			}

			if (CodecPageStatus == CDC_CONTINUE) {
				/*
				** ＪＢＩＧ受信・ＴＰＯｎモードの場合は蓄積符号をＭＭＲにする対応 1998/05/01 by T.Soneoka
				** 理由）ＭＮ８６０６４で符号変換コマンドＪＢＩＧ－＞ＭＧ３の場合、ＴＰ Ｏｆｆモードではループする為
				** 以下の受信タスク起動を関数にしてまとめたいけど、時間がいないのでこのままとします
				*/
				/* 符号JBIGの場合は、BIHセットの為、0ブロック目0フレーム目のみメモリ受信符号変換タスクにメッセージを送ります */
				if ((first_block == 1)
				&&  (DecodeEcmFrameNum == 0)		/* JBIG追加 by T.Soneoka 1997/12/17 */
				&& (SYS_DocBlock.Src.Code == SYS_JBIG_CODE)) {
					MDM_JBG_ReadBIH();
					/*------------------------------*/
					/*	メモリライトパラメータ設定	*/
					/*------------------------------*/
 #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/10/28 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
 					if (CommunicateType == RX_ECM_MEM) {	/** ＥＣＭメモリ受信の場合 */
 						RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
						RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
						RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
						RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);
						if ((CDC_JBG_BIH.Options & JBG_BIT_TPBON) 	/* TP Onか？ */
						&& (RxMemoryStoreData.Code == (UBYTE)SYS_MG3_CODE)) {
							RxMemoryStoreData.Code = (UBYTE) ( ( CHK_UNI_StoredMethodMMR()) ? SYS_MMR_CODE : SYS_MR_CODE);
						}

						RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
						RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
						/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
  /* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
						RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;
  /* #endif */

						/*------------------------------*/
						/*	メモリライトオープン処理	*/
						/*------------------------------*/
						/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/10/14 Y.Suzuki */
						if (SYS_RxPrintFileItem != 0) {
							index_data.No   = SYS_RxPrintFileNo;
							index_data.Page = SYS_RxPrintFilePage;
							index_data.Item = SYS_RxPrintFileItem;
  /* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */ /* Ported from ORANGE by H.Kubo 1997/07/15 */
							index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
  /* #endif */
							result = MEM_DualOpen(&RxMemoryStoreData, &index_data, &MDM_MemoryExecData);
						}
						else {
							result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData);
						}
#if 0 /* changed by H.Kubo 1998.11/11 */
						IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/15 by T.Soneoka */
#endif
						if (result != MEM_OK) {
							if (result == MEM_INDEX_CONFLICT) {
								SYS_FaxComIndexConflictStatus = 1;
							}
							else {
								SYS_FaxComIndexConflictStatus = 0;
							}
							tskno_RxDeviceWriteControl = 0xffff;
							tskno_RxPixControl = 0xffff;
							BreakEcmTaskFlag = YES;
							MDM_BreakRxTask();		/**	受信子タスク終了処理	*/
							MDM_PhaseC_Status = RX_MEM_OVER;	/**	受信セットアップエラーセット	*/
							exi_tsk();	/**	自タスク終了処理	*/
						}
						else { /* by H.Kubo 1998/11/11 */
							IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
						}
						/*----------------------*/
						/*	エンコード監視起動	*/
						/*----------------------*/
						tskno_RxDeviceWriteControl = 0xffff;
						cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
					}
 #else /*           ↑プリンタ受信有り   ↓プリンタ受信無し by H.Hirao 1998/10/28 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
   #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*//* By M.Maeda 2002/10/24 */
 					if (CommunicateType == RX_ECM_MEM) {	/** ＥＣＭメモリ受信の場合 */
 						RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
						RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
						RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
						RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);
						if ((CDC_JBG_BIH.Options & JBG_BIT_TPBON) 	/* TP Onか？ */
						&& (RxMemoryStoreData.Code == (UBYTE)SYS_MG3_CODE)) {
							RxMemoryStoreData.Code = (UBYTE) ( ( CHK_UNI_StoredMethodMMR()) ? SYS_MMR_CODE : SYS_MR_CODE);
						}

						RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
						RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
						/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
    /* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
						RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;
    /* #endif */

						/*------------------------------*/
						/*	メモリライトオープン処理	*/
						/*------------------------------*/
						/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/10/14 Y.Suzuki */
						if (SYS_RxPrintFileItem != 0) {
							index_data.No   = SYS_RxPrintFileNo;
							index_data.Page = SYS_RxPrintFilePage;
							index_data.Item = SYS_RxPrintFileItem;
    /* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */ /* Ported from ORANGE by H.Kubo 1997/07/15 */
							index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
    /* #endif */
							result = MEM_DualOpen(&RxMemoryStoreData, &index_data, &MDM_MemoryExecData);
						}
						else {
							result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData);
						}
#if 0 /* changed by H.Kubo 1998.11/11 */
						IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/15 by T.Soneoka */
#endif
						if (result != MEM_OK) {
							if (result == MEM_INDEX_CONFLICT) {
								SYS_FaxComIndexConflictStatus = 1;
							}
							else {
								SYS_FaxComIndexConflictStatus = 0;
							}
							tskno_RxDeviceWriteControl = 0xffff;
							tskno_RxPixControl = 0xffff;
							BreakEcmTaskFlag = YES;
							MDM_BreakRxTask();		/**	受信子タスク終了処理	*/
							MDM_PhaseC_Status = RX_MEM_OVER;	/**	受信セットアップエラーセット	*/
							exi_tsk();	/**	自タスク終了処理	*/
						}
						else { /* by H.Kubo 1998/11/11 */
							IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
						}
						/*----------------------*/
						/*	エンコード監視起動	*/
						/*----------------------*/
						tskno_RxDeviceWriteControl = 0xffff;
						cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
					}
 #else
					RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
					RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
					RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
					RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);	/* Add By O.Kimoto 1998/05/20 */

					if ((CDC_JBG_BIH.Options & JBG_BIT_TPBON) 	/* TP Onか？ */
					&& (RxMemoryStoreData.Code == (UBYTE)SYS_MG3_CODE)) {
						RxMemoryStoreData.Code = (UBYTE) ( ( CHK_UNI_StoredMethodMMR()) ? SYS_MMR_CODE : SYS_MR_CODE);
					}

					RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
					RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
					/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
					RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

					/*------------------------------*/
					/*	メモリライトオープン処理	*/
					/*------------------------------*/
					/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/10/14 Y.Suzuki */
					if (SYS_RxPrintFileItem != 0) {
						index_data.No   = SYS_RxPrintFileNo;
						index_data.Page = SYS_RxPrintFilePage;
						index_data.Item = SYS_RxPrintFileItem;
						index_data.BoxNumber = SYS_RxPrintFileBoxNumber;

						result = MEM_DualOpen(&RxMemoryStoreData,
											  &index_data,
											  &MDM_MemoryExecData);
					}
					else {
						/* Modified by H.Kubo 1997/06/26 for Atlanta */
						/* result = DPR_MEM_WriteOpen(&RxMemoryStoreData, &MemoryExecData); */
						result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData);
					}
					if (result != MEM_OK) {
						if (result == MEM_INDEX_CONFLICT) {
							SYS_FaxComIndexConflictStatus = 1;
						}
						else {
							SYS_FaxComIndexConflictStatus = 0;
						}
						tskno_RxDeviceWriteControl = 0xffff;
						tskno_RxPixControl = 0xffff;
						BreakEcmTaskFlag = YES;
						MDM_BreakRxTask();		/**	受信子タスク終了処理	*/
						MDM_PhaseC_Status = RX_MEM_OVER;	/**	受信セットアップエラーセット	*/
						exi_tsk();	/**	自タスク終了処理	*/
					}
					else { /* by H.Kubo 1998/11/11 */
						IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
					}

					/*----------------------*/
					/*	エンコード監視起動	*/
					/*----------------------*/
					tskno_RxDeviceWriteControl = 0xffff;
					cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
 #endif
 #endif /* (PRO_PRINTER_RX == ENABLE) added by H.Hirao 1998/10/28 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
					/*--------------------------------------*/
					/*	受信１ページ符号変換タスク起動処理	*/
					/*--------------------------------------*/
					tskno_RxPixControl = 0xffff;
				#if (PRO_PRINTER_RX == ENABLE) /* Ported from ORANGE by H.Kubo 997/08/12 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
					if (CommunicateType == RX_ECM_MEM) {	/**	ＥＣＭメモリ受信の場合	*/
						cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
					}
					else {									/**	ＥＣＭプリンタ受信の場合	*/
						cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
					}
				#else /* (PRO_PRINTER_RX == ENABLE) */
				  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 199/2/12 K.Kawata*/
					if (CommunicateType == RX_ECM_MEM) {
						cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
					}
					else {
						cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXDECODEPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
					}
				  #else
					cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/
				  #endif
				#endif
					/*----------------------*/
					/* ＣＩＬ付加の処理     */
					/*----------------------*/ /* DATE_SET_RXDOC */
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* DISABLEだとコンパイル通らないため、条件コンパイル追加 2001/12/21 T.Takagi */
					if (CMN_CheckCILEnable()) {
						if (CHK_UNI_CILPrintOn()) {
							/** 受信１ページ符号変換タスクより ＣＩＬ作成完了を待ちます */
							while (1) {	/* ＣＩＬ付加デコード終了するまで待つ */
								rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	デコード開始メッセージ受信	*/
								mdm_debugmsg = (UWORD)MDM_Msg->Message;
								if (mdm_debugmsg == MSG_CIL_COMPLETE) {
									break;
								}
							}
						}
					}
#endif
					/*------------------------------------------*/
					/*	通信コーデック復号化Ｖ５３ＤＭＡセット	*/
					/*------------------------------------------*/
					CodecRxDMA.Channel		= DMA_CH_DEC;
					CodecRxDMA.SrcAddress	= (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
					CodecRxDMA.Counter		= (CODEC_DMA_SIZE/2); /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
					CodecRxDMA.Unit			= DMA_WORD_TRANSFER;
					CodecRxDMA.Direction	= DMA_MEMORY_TO_IO;
					DMA_SetupDMAU(&CodecRxDMA);

					/* メモリ受信１ページ符号変換タスクにBIHがセットでき、符号変換可能なことを通知します */
					ModemMessage.Message = MSG_CODE_CONVERT_START;
					snd_msg(mbxno.CDC_Task, &ModemMessage);
				}

				if (MDM_ForcedDecodeStart) {
					DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*(DecodeEcmFrameNum-1))+254));
					DMA_SetDMA_Counter(CodecRxDMA.Channel, 1);
					DMA_RequestEnable(CodecRxDMA.Channel);
				}
				else {
					/* 一つ前のブロックの最終フレームの最後２バイトがＦＦ、０２のとき */
					if (IsDetLastFrameEndMaker) {
						IsDetLastFrameEndMaker = 0;
						IsDetEndMaker = 0;
#if (0) /* 全機種有効 2001/01/05 by K.Okada *//* from nagano\fm336 2001/01/05 Y.M */
						DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*255)+254));
#else /* PARISで確認中 2000/12/23 by K.Okada */ /* 全機種有効 2001/01/05 by K.Okada */
						/*
						** JBIGループ不具合 RNR-RRでT.4.1 R.5.1で回線断 2000/12/20 by T.Soneoka
						** 一つ前のブロックの最終フレームの最後２バイトがＦＦ、０２のときの場合、待避したデータを転送しないと、
						** 次のブロックでつぶされている可能性がある
						*/
						DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)TempLastFrameBuf);
#endif
						DMA_SetDMA_Counter(CodecRxDMA.Channel, 1);

						/* 全機種有効 2001/01/05 by K.Okada *//* from nagano\fm336 2001/01/05 Y.M */
						/* PARISで確認中 2000/12/22 by K.Okada */
						/*
						** JBIGループ不具合 RNR-RRでT.4.1 R.5.1で回線断 2000/12/20 by T.Soneoka
						*/
						DMA_RequestEnable(CodecRxDMA.Channel);

						DebugStripePattern5++;
						rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);
					}
					buf1 = EcmBuffer[DecodeEcmFrameNum][254];
					buf2 = EcmBuffer[DecodeEcmFrameNum][255];
					if (((buf1 == (UBYTE)0xff) && (buf2 == (UBYTE)0x02))	/**	ＥＣＭバッファの最終データが（ＦＦ、０２）のストライプ終了のとき	*/
					||  ((buf1 == (UBYTE)0xff) && (buf2 == (UBYTE)0x03))	/**	ＥＣＭバッファの最終データが（ＦＦ、０３）のストライプ終了のとき	*/
					||  ((buf1 == (UBYTE)0x02) && (buf2 == (UBYTE)0xff))	/**	ＥＣＭバッファの最終データが（０２、ＦＦ）のストライプ終了のとき	*/
					||  ((buf1 == (UBYTE)0x03) && (buf2 == (UBYTE)0xff))) {	/**	ＥＣＭバッファの最終データが（０３、ＦＦ）のストライプ終了のとき	*/
						if (DecodeEcmFrameNum == 255) {	/**	ＥＣＭフレームが最終フレームの場合	*/

							IsDetLastFrameEndMaker = 1;		/**	最終フレームに終端マーカ検出	*/

							/* 全機種有効 2001/01/05 by K.Okada *//* from nagano\fm336 2001/01/05 Y.M */
							/* PARISで確認中 2000/12/22 by K.Okada */
							/*
							** JBIGループ不具合 RNR-RRでT.4.1 R.5.1で回線断 2000/12/20 by T.Soneoka
							** 一つ前のブロックの最終フレームの最後２バイトがＦＦ、０２のときの場合、待避したデータを転送しないと、
							** 次のブロックでつぶされている可能性がある
							*/
							TempLastFrameBuf[0] = buf1;
							TempLastFrameBuf[1] = buf2;

							DebugStripePattern4++;

						}
						if (IsDetEndMaker) {	/* バッファ先頭２バイト前から２５６バイト転送 */
							DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)-2));
							DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2));
							DebugStripePattern2++;
						}
						else {	/* バッファ先頭から２５４バイト転送 */
							DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)));
							DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2)-1);
							DebugStripePattern1++;
						}
						IsDetEndMaker = 1;
					}
					else {	/* 未検出の場合 */
						if (IsDetEndMaker) {	/* バッファ先頭２バイト前から２５８バイト転送 */
							DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)-2));
							DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2)+1);
							DebugStripePattern3++;
						}
						else {	/* バッファ先頭から２５６バイト転送 */
							DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)));
							DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2));
						}
						IsDetEndMaker = 0;
					}
					DMA_RequestEnable(CodecRxDMA.Channel);
				}
				rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);
			}
		}
		else { 		/*++++ if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) に対する else. +++*/
			while (CheckEcmStatusExtRom(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
				wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
				if (CodecPageStatus != CDC_CONTINUE) {
					break;
				}
			}
			if (CodecPageStatus == CDC_CONTINUE) {
				DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)));
				DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2)); /* Modified by H. Kubo 1997/06/25 for DMA routine of Atlanta */
				DMA_RequestEnable(CodecRxDMA.Channel);
			}
			do {
				rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);
			} while (!((MDM_Msg->Message == MSG_FROM_DECODEDMA_TC_TASK) ||
			           (MDM_Msg->Message == MSG_FROM_CODE_CONVERT_TASK) ||
			           (MDM_Msg->Message == MSG_FROM_DEVICE_CONTROL_TASK)));
		}

		/*
		** 受信３Ｍオーバチェック処理追加
		** 1999/02/02 by T.Soneoka
		** ported by H.Kubo 1999/09/14
		*/
		MDM_RxTotalLine = DecodeLine(COMMUNICATION_CODEC);
		if (MDM_RxTotalLine >= Rx3mErrorLine) {
			CodecPageStatus = CDC_PAGE_SEPARATE;	/* 最大デコードライン数に達した */
		}

		switch (CodecPageStatus) {	/**	受信１ページ符号変換タスク状態	*/
		case	CDC_CONTINUE:	/**	デコード継続	*/
			DecodeEcmFrameNum++;	/**	ＥＣＭフレーム数更新	*/
			if (DecodeEcmFrameNum >= ECM_BUFFER_MAX) {	/**	ＥＣＭバッファオーバー時	*/
#if defined(SIRAKABA)
				/*
				** [受信時のコーデック、DMA転送状態表示用]
				** 1.コーデック割込み要因	: DebugC0_STIR
				** 2.デコードライン数		: DebugDecodeLine
				** 3.エンコードライン数		: DebugEncodeLine
				** 4.ECMブロックエンド回数	: DebugBlockEnd
				** 5.最終ECMブロックでの256バイト転送回数 : DecodeEcmFrameNum
				** 6.MD9806DMA転送カウンタ値(decode): DebugDMACNTR3
				** 7.MD9806DMA転送カウンタ値(encode): DebugDMACNTR2
				**
				** for debug 1999/05/14 by K.Okada
				*/
				DebugBlockEnd++;
#endif
				MDM_RxTotalLine = DecodeLine(COMMUNICATION_CODEC); /* Added argument COMMUNICATION_CODEC by H.Kubo 1997/06/30 */
				MDM_RxErrorTotalLine = ErrorLine(COMMUNICATION_CODEC);	/**	エラーライン数獲得	*/ /* Added argument COMMUNICATION_CODEC by H.Kubo 1997/06/30 */
				MDM_PhaseC_Status = RX_BLOCK_END;	/**	ブロックエンド設定	*/
				do {
					rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);	/**	デコード開始メッセージ受信	*/
					if (MDM_Msg->Message == MSG_FORCED_DECODE_START) {
						IsDetLastFrameEndMaker = 0;
						IsDetEndMaker = 0;
						MDM_ForcedDecodeStart = 0;
						DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)+254));
						DMA_SetDMA_Counter(CodecRxDMA.Channel, 1);
						DMA_RequestEnable(CodecRxDMA.Channel);
						DebugStripePattern6++;

					}
				} while (!((MDM_Msg->Message == MSG_RX_DECODE_START) ||
				           (MDM_Msg->Message == MSG_FROM_CODE_CONVERT_TASK) ||
				           (MDM_Msg->Message == MSG_FROM_DEVICE_CONTROL_TASK)));
				switch (CodecPageStatus) {
				case	CDC_RTC_DET:
					BreakEcmTaskFlag = YES;
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					MDM_PhaseC_Status = RX_PAGE_END;
					page_loop = 0;
					break;
				case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
					BreakEcmTaskFlag = YES;
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					MDM_PhaseC_Status = RX_ERROR;
					page_loop = 0;
					break;
				case	CDC_MEM_OVER:
					BreakEcmTaskFlag = YES;
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					MDM_PhaseC_Status = RX_MEM_OVER;	/**	メモリオーバセット	*/
					page_loop = 0;
					break;
#if (PRO_PRINTER_RX == ENABLE)		/* Takeuchi	 Nov.15.1994 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
				case	CDC_PRINTER_ERROR:
					BreakEcmTaskFlag = YES;
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
					page_loop = 0;
					break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*//* By M.Maeda 2002/10/24 */
				case	CDC_PRINTER_ERROR:
					BreakEcmTaskFlag = YES;
					MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
					MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
					page_loop = 0;
					break;
#endif
				default:
					MDM_PhaseC_Status = RX_CONTINUE;
					DecodeEcmFrameNum = 0;	/**	ＥＣＭフレームナンバ初期化	*/
					first_block = 0;	/* JBIG追加   by T.Soneoka 1997/12/17 */
					break;
				}
			}
			break;
		case	CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_PAGE_END;
			page_loop = 0;
			break;
		case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_ERROR;
			page_loop = 0;
			break;
		case	CDC_STOPPED:	/**	強制終了発生時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_STOPPED;
			page_loop = 0;
			break;
		case	CDC_PAGE_SEPARATE:	/**	最大受信原稿長制限オーバ処理	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_OVER;
			page_loop = 0;
			break;
#if (PRO_PRINTER_RX == ENABLE)		/* Takeuchi	 Nov.15.1994 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
		case	CDC_PRINTER_ERROR:
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
			page_loop = 0;
			break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*//* By M.Maeda 2002/10/24 */
		case	CDC_PRINTER_ERROR:
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
			page_loop = 0;
			break;
#endif
		case	CDC_MEM_OVER:
		default:
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_MEM_OVER;	/**	メモリオーバセット	*/
			page_loop = 0;
			break;
		}
	}
	exi_tsk();	/**	自タスク終了処理	*/
}


#if defined (SIRAKABA)	/* ECMバッファ -> CDC -> DRAMパスチェック用 */
/*************************************************************************
	module		:[]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1995/05/14]
	author		:[K.Okada]
*************************************************************************/
void			RxDMA_TransferTest(void)
{
	MESSAGE_t	*MDM_Msg;

	UWORD	i;
	UBYTE	page_loop;
	UWORD	result;
	UWORD *start_address;
	UWORD *mmr_data;
	struct DMA_Data_t CodecRxDMA;
	struct	MEM_IndexData_t	index_data;

	InitializeFaxCom();
	MDM_ModemInitialize();

	result = 0;
	CodecPageStatus = CDC_CONTINUE;	/**	符号変換終了ステータスを初期化	*/
	MDM_EncodeLine = 0;
	BreakRxTaskCompleteFlag = NO;
	IsMemoryToCOMCDC_XferDone = NO;
	FcomEcmSize = ECM_256_OCT;
	CommunicateType = RX_ECM_MEM;
	BreakEcmTaskFlag = NO;
	SetClear((UBYTE *)&EcmBuffer[0][0], 0xFFFF, 0x00);
	SetClear((UBYTE *)&MEM_StoreArea[0], 0xFFFF, 0x00);
	start_address = (UWORD *)&EcmBuffer[0][0];
	mmr_data = (UWORD *)&EcmBufferData[0];



	/* 変数セット */
	SYS_DocBlock.Index.No = 0;
	SYS_DocBlock.Index.Page = 1;
	SYS_DocBlock.Index.Item = SYS_MEM_RX_FILE;
	SYS_DocBlock.Src.Mode = (UBYTE)SYB_ModeSw;
	SYS_DocBlock.Src.Size = SYS_DOCUMENT_A4_SIZE;
	SYS_DocBlock.Src.Code = SYS_MMR_CODE;
	SYS_DocBlock.Index.BoxNumber = MEM_IGNORE_BOX_NUMBER;

	/* ECMバッファにデータ貼り付け */
	for (i = 0; i < (ECM_BUFFER_DATA_SIZE/2); i++) {
		*start_address++ = *mmr_data++;
	}

	/*------------------------------*/
	/*	Decode Detect Task Create	*/
	/*------------------------------*/
	DMA0_TC3Flag = 0;
	tskno_DecodeDMA_End = 0xffff;
	cre_tsk(&tskno_DecodeDMA_End, TSK_MDM_DECODEDMA_TC_DETECTTASK, 0);	/**	エンコードＶ５３ＤＭＡ終了監視タスク起動	*/

	/*------------------------------*/
	/*	メモリライトパラメータ設定	*/
	/*------------------------------*/
	RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
	RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
	RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;

	RxMemoryStoreData.Code = DecideStoreCode(RxMemoryStoreData.Item);	/* Add By O.Kimoto 1998/05/20 */
	RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
	RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
	/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
	RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

	/*------------------------------*/
	/*	メモリライトオープン処理	*/
	/*------------------------------*/
	result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MDM_MemoryExecData, MEM_DISABLE_REQUIRE);
	if (result != MEM_OK) {
		if (result == MEM_INDEX_CONFLICT) {
			SYS_FaxComIndexConflictStatus = 1;
		}
		else {
			SYS_FaxComIndexConflictStatus = 0;
		}
		tskno_RxDeviceWriteControl = 0xffff;
		tskno_RxPixControl = 0xffff;
		BreakEcmTaskFlag = YES;
		MDM_BreakRxTask();		/**	受信子タスク終了処理	*/
		exi_tsk();	/**	自タスク終了処理	*/
	}
	else { /* by H.Kubo 1998/11/11 */
		IsMemoryOpen = 1;	/* メモリオープン済みにセット 1998/05/18 by T.Soneoka */ /* moved from above by H.Kubo 1998/11/11 */
	}

	/*----------------------*/
	/*	エンコード監視起動	*/
	/*----------------------*/
	tskno_RxDeviceWriteControl = 0xffff;
	cre_tsk(&tskno_RxDeviceWriteControl, TSK_MDM_RXDEVICECONTROLTASK, 0);	/**	受信デバイス監視タスク（エンコード監視）起動	*/
	
	/*--------------------------------------*/
	/*	受信１ページ符号変換タスク起動処理	*/
	/*--------------------------------------*/
	tskno_RxPixControl = 0xffff;
	cre_tsk(&tskno_RxPixControl, TSK_CDC_MRXCODECONVERTPAGETASK, 0);	/**	メモリ受信１ページ符号変換タスク起動	*/

	/*------------------------------------------*/
	/*	通信コーデック復号化Ｖ５３ＤＭＡセット	*/
	/*------------------------------------------*/
	CodecRxDMA.Channel		= DMA_CH_DEC;
	CodecRxDMA.SrcAddress	= (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
	CodecRxDMA.Counter		= (CODEC_DMA_SIZE/2); /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
	CodecRxDMA.Unit			= DMA_WORD_TRANSFER;
	CodecRxDMA.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&CodecRxDMA);
		
	page_loop = 1;	/**	１ページデコード終了フラグ設定	*/
	
	while (page_loop) {	/**	１ページデコードするまでループ	*/
		wai_tsk(1);
		/*------------------------------*/
		/*	ＥＣＭフレーム受信待ち処理	*/
		/*------------------------------*/
		if (CodecPageStatus == CDC_CONTINUE) {
			DMA_SetDMA_Address(CodecRxDMA.Channel, CodecRxDMA.Direction, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+(CODEC_DMA_SIZE*DecodeEcmFrameNum)));
			DMA_SetDMA_Counter(CodecRxDMA.Channel, (FcomEcmSize/2)); /* Modified by H. Kubo 1997/06/25 for DMA routine of Atlanta */
			DMA_RequestEnable(CodecRxDMA.Channel);

		}
		do {
			rcv_msg(mbxno.MDM_RxEcmControlTask, &MDM_Msg);
		} while (!((MDM_Msg->Message == MSG_FROM_DECODEDMA_TC_TASK) ||
		           (MDM_Msg->Message == MSG_FROM_CODE_CONVERT_TASK) ||
		           (MDM_Msg->Message == MSG_FROM_DEVICE_CONTROL_TASK)));

		switch (CodecPageStatus) {	/**	受信１ページ符号変換タスク状態	*/
		case	CDC_CONTINUE:	/**	デコード継続	*/
			DecodeEcmFrameNum++;	/**	ＥＣＭフレーム数更新	*/
			if (DecodeEcmFrameNum >= ECM_BUFFER_MAX) {	/**	ＥＣＭバッファオーバー時	*/
				DebugBlockEnd++;
				DecodeEcmFrameNum = 0;	/**	ＥＣＭフレームナンバ初期化	*/
			}
			break;
		case	CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MEM_ClearAll();
			page_loop = 0;
			break;
		case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MEM_ClearAll();
			page_loop = 0;
			break;
		case	CDC_STOPPED:	/**	強制終了発生時	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MEM_ClearAll();
			page_loop = 0;
			break;
		case	CDC_PAGE_SEPARATE:	/**	最大受信原稿長制限オーバ処理	*/
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MEM_ClearAll();
			page_loop = 0;
			break;
		case	CDC_MEM_OVER:
		default:
			BreakEcmTaskFlag = YES;
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			MEM_ClearAll();
			page_loop = 0;
			break;
		}
	}
}
#endif



/*************************************************************************
	module		:[ＥＣＭ部分ページ受信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		MDM_RxEcmPartialPage(void)
{
	UBYTE	MDM_EcmFrameNumber;	/**	ＥＣＭフィールドナンバー　０～２５５	*/
	UBYTE	retry_cnt;	/**	モデムリードリトライカウンタ	*/
	UBYTE	mdm_cnt_save;	/**	ショートフレーム対策用モデム書き込み位置保存	*/
	UBYTE	short_flg;	/**	ショートフレーム対策用ショートフレーム受信有無フラグ	*/
	UBYTE	rtn;
	UBYTE	loop_flg;
	UBYTE	hold_flg;
	UBYTE	dust_data;	/**  By O.K Feb.05,1996 **/

	short_flg = 0;	/**	ショートフレームフラグ初期化	*/
	retry_cnt = 0;	/**	リードリトライカウンタ初期化	*/
	mdm_cnt_save = 0;	/**	ショートフレーム対策用モデム書き込み位置初期化	*/
	hold_flg = 0;

	if (CHK_UNI_ECM_RxTM_OutEvade()) {	/* 1997/05/28  By T.Yamaguchi */
		retry_cnt = 3;
	}
	else {
		retry_cnt = 0;
	}

	/*--------------------------*/
	/* 海外認可共通対応         */
	/* FOREIGN_APPROVAL No.1-4  */
	/*--------------------------*/
	/* ドイツ申請時、キャリア断の時、６±１秒で回線断させるため
	*/
	if (CHK_ForeignApprovalDEU()) {
		if (CHK_UNI_ECM_RxTM_OutEvade() == 0) {
			retry_cnt = 3;
		}
	}

	MDM_RlsdTurnOffCheckFlag = TRUE;	/**  By O.K Feb.05,1996 **/
	MDM_RlsdTurnOffFlag = 0;			/* 1997/01/16 Y.Murata */

	MDM_NewT30Status = MODE_RX_ECM;	/* R288F Internal Monitor By O.Kimoto 1996/05/28 */

	if (!(SYS_V34ProcedureExecuting())) {
		/* 1997/05/09 Y.Murata -> 1997/08/28 部分ﾍﾟｰｼﾞの時も同じようにせなあかんのにぬけていた。
		 * Ｒ．３．３対策 RLSDが誤動作すればRTDISのｾｯﾄﾀｲﾐﾝｸﾞが狂いR.3.3が発生するため100msのチャタを見る
		*/
		MDM_PixStartFlag = 1;
		MDM_AlreadyRtdisSetFlag = 0;
	}
	else {
		/* ロックウエルモデム不具合
		 * 1997/09/09 Y.Murata
		 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
		 *  受信できないことがある」
		 * ひらたくいえば、モデムが発散します。
		 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
		*/
		MDM_PixStartFlag = 1;
		MDM_AlreadyRtdisSetFlag = 0;
	}

	/* Ｖ．３４モード時、ＥＱＭ値を読み出すためにタスクを生成します。 */
	if (SYS_V34ProcedureExecuting()) {
		tskno_EyeQualityMonitor = 0xffff;
		cre_tsk(&tskno_EyeQualityMonitor,TSK_MDM_READEQMVALUETASK,0);
	}

	loop_flg = 1;
	while (loop_flg) {
		/*--------------------------*/
		/**	該当モデムバッファ有効	*/
		/*--------------------------*/
		rtn = RxEcmRead();	/**	受信ＥＣＭリード	*/
		if (rtn == RCV_BLOCK) {
			/*------------------------------*/
			/*	イコライザーホールド処理	*/
			/*------------------------------*/
			if (hold_flg == 0) {
				if (CHK_V17EqualizerHold()) {	/**	イコライザホールドのメモリスイッチが有効の時	*/
					if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
						EqualizerHoldOn();	/**	イコライザホールドに設定	*/
					}
				}
				hold_flg = 1;
			}
			switch (MDM_ModemBuffer[ModemControl.ReadPoint][FCF_FLD]) {
			/*--------------------------*/
			/**	ＦＣＤフレーム受信処理	*/
			/*--------------------------*/
			case HDLC_FCD:
				MDM_EcmFrameNumber = MDM_ModemBuffer[ModemControl.ReadPoint][FIF_FLD];
				/*-----------------------*/
				/** ショートフレーム対策 */
				/*-----------------------*/
/**	アドレス＋コントロール＋ＦＣＤ＋フレームＮｏ＋ＦＩＦ（２５６／６４）＋ＦＣＳ（２バイト）＋フラグ *//**  By O.K Jan.23,1996 **/
				if (MDM_RxSize[ModemControl.ReadPoint] != (FcomEcmSize+7)) {
					short_flg = 1;	/**	ショートフレーム受信フラグセット	*/
					MemoryMove((UBYTE *)FaxComTxFrame, (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MODEM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
					break;
				}
				short_flg = 0;	/**	ショートフレーム受信フラグ初期化	*/
				/*-------------------------------------------------------*/
				/** モデムバッファからＥＣＭバッファにプログラム転送処理 */
				/*-------------------------------------------------------*/
				MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD], (UWORD)ECM_BUFFER_LENGTH);	/**	ショートフレーム保存 */
				/*------------------------------------------*/
				/**	ＥＣＭバッファフレームステータス有効	*/
				/*------------------------------------------*/
				EnableEcmStatus(MDM_EcmFrameNumber);
				break;
			/*----------------------*/
			/**	ＲＣＰフレーム受信	*/
			/*----------------------*/
			case HDLC_RCP:
				loop_flg = 0;

#if 0 /* Deleted by H.Kubo 1998/01/22   村田さん情報: これは 高速Eye発散対策だった*/
@@				if (!(SYS_V34ProcedureExecuting())) {
@@					CMN_DisableInterrupt();
@@					MDM_SetIO(POS_RTDIS,OFF);
@@					CMN_DisableInterrupt();
@@				}
#endif /* 0 */
				/*-----------------------*/
				/** ショートフレーム対策 */
				/*-----------------------*/
				if (short_flg == 1){	/**	ショートフレーム受信済み	*/
					MDM_EcmFrameNumber = FaxComTxFrame[FIF_FLD];
					/*-------------------------------------------------------*/
					/*	モデムバッファからＥＣＭバッファにプログラム転送処理 */
					/*-------------------------------------------------------*/
/*
** インデック潰す件、ＥＣＭバッファへの転送バイト数が間違っています
** ショートフレームの場合でも、２５６分固定でＥＣＭバッファに転送します
** 1998/03/31 by T.Soneoka
*/
#if (0)
//#if (0) /* 念のためRxFrameLengthが変な値でもＤＲＡＭを壊さないようにします */
////					MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
//#endif					
//					if (RxFrameLength <= (FcomEcmSize+7)) {
//						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
//#if (0)	/* 1998/03/24 調査終了 */
////						if (debug_swap) {
////							MemoryMoveSwap((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (WORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
////						else {
////							MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
//#endif
//					}
//					else {
//						RxFrameLength = FcomEcmSize+7;
//#if (0)	/* 転送バイト数のセットがおかしい（多すぎる）、この為メモリインデックスを壊すおそれある 1998/03/31 by T.Soneoka */
////						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
//#else
//						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-7));	/**	ショートフレーム保存	*/
//#endif
//#if (0)	/* 1998/03/24 調査終了 */
////						if (debug_swap) {
////							MemoryMoveSwap((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (WORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
////						else {
////							MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)(RxFrameLength-2));	/**	ショートフレーム保存	*/
////						}
//#endif
//					}
#else
					MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)ECM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
#endif
					/*------------------------------------------*/
					/*	ＥＣＭバッファフレームステータス有効	*/
					/*------------------------------------------*/
					EnableEcmStatus(MDM_EcmFrameNumber);	/**	ＥＣＭバッファフレームステータス有効	*/
				}

				/* 1997/01/16 Y.Murata
				 * V17以下の時はRCP受信してるからRLSDのﾀｰﾝOFFをみなくてもよい
				 * RTDIS対策でRLSDの動作がおかしくなったらいややし、
				 * モデムを信用しない。TX側さつきでECMｎ時１発目のﾎﾟｽﾄﾒｯｾｰｼﾞをたまに取り逃がす
				 * その時RLSDのﾀｰﾝOFFが遅い
				*/
				if (SYS_V34ProcedureExecuting()) {
					/** プライマリーチャンネル終了処理（暫定） By O.K Feb.03,1996 **/
					CMN_DisableInterrupt();
					if ((!MDM_RlsdTurnOffFlag)&&(!MDM_FedOffFlag)) {
						wai_evt(EVT_MDM_TURNOFF);
					}
					MDM_RlsdTurnOffFlag = 0;
					CMN_EnableInterrupt();
				}
				DMA_RequestMask(DMA_CH_RX); /* first argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/23 */
				while (inp(MDM_REG_0C_PORT) & IO_BIT_RXFNE) {
					dust_data = inp(MDM_REG_00_PORT);
				}

				rtn = MDM_PhaseC_Status;	/*	今現在のデーコード状態を返す	*/
				break;
			/*--------------------------*/
			/**	不当フレーム受信処理	*/
			/*--------------------------*/
			default:
				break;
			}
			/*--------------------------------------*/
			/**	モデムバッファ読み出し位置更新処理	*/
			/*--------------------------------------*/
			NextMdmBufReadPointSetExtRom();
		}
		/*------------------------------*/
		/** タイムアウト時（６秒）処理	*/
		/*	現在３回で１８秒			*/
		/*------------------------------*/
		else if (rtn == RCV_TMOUT) {
			if (retry_cnt++ >= 3) {	/**	３回目のタイムアウト時	*/
				rtn = RX_TMOUT;
				loop_flg = 0;
			}
		}
		/*----------------------*/
		/*	ストップＳｗ検出	*/
		/*----------------------*/
		else if (rtn == RCV_STOP) {
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STOPPED;
			loop_flg = 0;
		}
		/*----------------------*/
		/*	ターンＯＦＦ検出	*/
		/*----------------------*/	/* 1996/02/08 Y.M */
		/** ポストメッセージ全く取れず対策（暫定） By O.K Feb.06,1996 **/
		else if (rtn == RCV_TURNOFF) {
#if 0	/* RNR-RRになる 1996/06/07 Y.Murata */
//			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/ /* 1996/06/05 Y.Murata */
//			rtn = RX_PAGE_END;
#endif
			rtn = RX_CONTINUE;
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
		}
		/*--------------------------*/
		/*	デコードオープンエラー	*/
		/*--------------------------*/
		else {
			MDM_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STUP_ERR;
			loop_flg = 0;
		}
	}

	MDM_RlsdTurnOffCheckFlag = FALSE;	/**  By O.K Feb.05,1996 **/

	if (!(SYS_V34ProcedureExecuting())) {
		MDM_SetIO(POS_RTDIS,OFF);
		MDM_PixStartFlag = 0;
		MDM_AlreadyRtdisSetFlag = 0;
	}
	else {
		/* ロックウエルモデム不具合
		 * 1997/09/09 Y.Murata
		 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
		 *  受信できないことがある」
		 * ひらたくいえば、モデムが発散します。
		 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
		*/
		MDM_PixStartFlag = 0;
		MDM_AlreadyRtdisSetFlag = 0;

		/*
		** R288F VERSION 24P以上の場合
		*/
		MDM_SetIO(POS_PCOFF, OFF); /* R4.2 対策。速やかに Control Channel へ抜けるため。 by H.Kubo 1998/11/14 */
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		MDM_SetIO(POS_FCCR_FM336, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
	}
	else {
		MDM_SetIO(POS_FECSQ, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
	}
#else
		MDM_SetIO(POS_FECSQ, ON); /* FCCR (Force Control Channel Recient) ON. added by H.Kubo 1998/11/14 */
#endif
#if defined(HINOKI)	|| defined(HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)/* For DEBUG by O.kimoto 1998/12/01 */ /* ported for HINOKI2 2001/11/13 T.Takagi */
		MDM_NewT30Status = MODE_PC_OFF;	/* Add by O.Kimoto 1998/12/01 */
#endif

	}
	return
	 (rtn);
}


/*************************************************************************
	module		:[受信デバイス監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/02]
	author		:[曽根岡拓]
*************************************************************************/
void			MDM_RxDeviceControlTask(void)
{
	/*----------------------*/
	/*	メモリライト処理	*/
	/*----------------------*/
	if (MEM_BLOCK_OVER == MEM_Write(MEM_MODEM, &MDM_MemoryExecData)) {	/**	メモリオーバ時	*/
								/*  ~~~~~~~~~~ Taken from ORANGE\src\mdmrxpix.c */
		CodecPageStatus = CDC_MEM_OVER;
		MemWriteMessage.Message = MSG_FROM_DEVICE_CONTROL_TASK;
		snd_msg(mbxno.MDM_RxEcmControlTask, &MemWriteMessage);
	}
	wai_tsk(0xffff);
}

/*************************************************************************
	module		:[ＰＩＸ受信クローズ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/25]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_RxPixClose(UBYTE	ecm_type)
{
	switch ( ecm_type ) {
	case ECM_OFF:
		RxG3_Close();
		break;
	case ECM_ON:
		RxEcmClose();
		break;
	}
	
	/* Add for EQM By O.K Feb.22,1996 */
	if ( SYS_V34ProcedureExecuting()) {
		if ( tskno_EyeQualityMonitor != 0xffff ) {
			del_tsk( &tskno_EyeQualityMonitor );
		}
	}
	else {
		if ( TCF_DEBUG & 0x08 ) {
			if ( SYS_ModemVersion == MDM_L6713_13P ) {
				/* 1996/10/31 Y.Murata
				 * Inceasing Drop Out Recovery Time during V17/V29/
				*/
				DspRamAccessWriteMethod3(0x0C04, 0x0000, 0xFF00);
			}
		}	/* end of debug */
	}
}


/*************************************************************************
	module		:[ＣＲＣチェック]
	function	:[
		1.
	]
	return		:[
		OK:		ＣＲＣチェックＯＫ
		NG:		ＣＲＣチェックＮＧ
	]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UBYTE near CRC_Check(UBYTE *,UWORD ,UWORD *){}]
	date		:[1994/01/13]
	update		:[1995/12/15]
	author		:[曽根岡拓、木元修]
*************************************************************************/
UBYTE  CRC_Check(
UBYTE *bfp,	/*	フレームポインタ	*/
UWORD  len,	/*	純フレームレングス	*/
UWORD  *fcs_dat)	/*	ＦＣＳ情報	*/
{
	UWORD	chk_rslt;

	chk_rslt = 0;

	chk_rslt = crc(len, bfp);
	if (chk_rslt != *fcs_dat) {
		return (NG);
	}
	return (OK);
}


/*************************************************************************
	module		:[受信タスク強制終了]
	function	:[
		1.ＥＣＭ受信タスクの中からコーデックアボードコマンドを呼ぶことで
		　ＥＣＭ受信タスクで自タスク終了する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/25]
	author		:[曽根岡拓]
*************************************************************************/
void			MDM_BreakRxTask(void)
{
	CMN_DisableInterrupt();
	if (BreakRxTaskCompleteFlag == YES) {
		CMN_EnableInterrupt();
		return;
	}
	else {
		BreakRxTaskCompleteFlag = YES;
	}
	CMN_EnableInterrupt();

	MDM_RxTotalLine = DecodeLine(COMMUNICATION_CODEC); /* argument COMMUNICATION_CODEC is added by H. Kubo 1997/06/30 */
	MDM_RxErrorTotalLine = ErrorLine(COMMUNICATION_CODEC);	/**	エラーライン数獲得	*//* argument COMMUNICATION_CODEC is added by H. Kubo 1997/06/30 */
	if (SYS_RxTotalPage < MDM_ERR_LINE_DATA_MAX) {
		MDM_RxTotalLineSave[SYS_RxTotalPage] = MDM_RxTotalLine;
		MDM_RxErrorTotalLineSave[SYS_RxTotalPage] = MDM_RxErrorTotalLine;
	}

	switch (CommunicateType) {
	case	RX_G3_MEM:
	case	RX_ECM_MEM:
		MEM_DMAEndStatus |= MEM_RX_PAGE_END;	/**Taken from \src\atlanta\mdm\orange\mdmrxpix.c */
		det_evt(EVT_DMA_COMCDC_DRAM); /* 通信コーデック=>DRAM を待つイベントをすべて Ready. By H.Kubo 1998/11/07 */
		if (IsMemoryOpen) {	/* メモリオープン済みにセット 1998/05/15 by T.Soneoka */
			/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/9/28 Y.Suzuki */
			if (SYS_RxPrintFileItem != 0) {
				MEM_DualClose(&MDM_MemoryExecData, MDM_EncodeLine); /* Modified by H.Kubo 1997/06/26 */
			}
			else {
				if (SYS_FaxComIndexConflictStatus == 0) {	/* 1997/01/10 Y.Murata */
					MEM_WriteClose(&MDM_MemoryExecData, MDM_EncodeLine); /* Modified by H. Kubo 1997/06/26 */
				}
			}
		}
		IsMemoryOpen = 0;	/* メモリオープン済みにクリア 1998/05/15 by T.Soneoka */
		if (tskno_RxDeviceWriteControl != 0xffff) {
			del_tsk(&tskno_RxDeviceWriteControl);
		}
		DMA_RequestMask(DMA_CH_ENC); /* 1st argument MASTER_DMAU was deleted by H. Kubo for POPLAR_H. 1997/06/23 */

		break;
	case	RX_G3_PRT:
	case	RX_ECM_PRT:
		break;
	}
	/*------------------------------------------*/
	/*	メモリ受信１ページ符号変換タスク終了	*/
	/*------------------------------------------*/
	if (tskno_RxPixControl != 0xffff) {
		/*------------------------------*/
		/*	通信コーデックを開放する	*/
		/*------------------------------*/
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/10/27 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
		if ((CommunicateType == RX_G3_MEM) || (CommunicateType == RX_ECM_MEM)) {
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
				SaveReturnAddressAndJumpBegin();
			}
		}
		else {
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
				SaveReturnAddressAndJumpBegin();
			}
		}
#else
  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*//* By M.Maeda 2002/10/24 */
		if ((CommunicateType == RX_G3_MEM) || (CommunicateType == RX_ECM_MEM)) {
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
				SaveReturnAddressAndJumpBegin();
			}
		}
		else {
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
				SaveReturnAddressAndJumpBegin();
			}
		}
		/**	ＤＭＡ転送完了監視タスク起動	*/
		/* SAKAKI プリンタ受信で受信画が壊れる対策。モデムバッファを監視するタスクです。
		** by H.Kubo 1999/03/20
		*/
		if (tskno_RxDMA_TC_Detect != 0xffff) {
			del_tsk(&tskno_RxDMA_TC_Detect);
		}
  #else
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) { /* argument COMMUNICATION_CODEC is added by H. Kubo 1997/06/30 */
			SaveReturnAddressAndJumpBegin();
		}
  #endif
#endif
		del_tsk(&tskno_RxPixControl);
	}
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/17 */ /* ported for HINOKI2 2002/01/07 T.Takagi */
	if (tskno_CDC_PRxDMA_Task != 0xFFFF) {
		del_tsk(&tskno_CDC_PRxDMA_Task);
	}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/18 K.Kawata*//* By M.Maeda 2002/10/24 */
	if (tskno_CDC_PRxDMA_Task != 0xFFFF) {
		del_tsk(&tskno_CDC_PRxDMA_Task);
	}
#endif
	if (tskno_DecodeDMA_End != 0xffff) {
		del_tsk(&tskno_DecodeDMA_End);
	}
	DMA_RequestMask(DMA_CH_DEC); /* 1st argument MASTER_DMAU was deleted by H.Kubo for POPLAR_H 1997/06/23 */
	switch (CommunicateType) {
	case	RX_ECM_MEM:
	case	RX_ECM_PRT:
		if (BreakEcmTaskFlag != YES) {
			if (tskno_RxEcmControl != 0xffff) {
				del_tsk(&tskno_RxEcmControl);
			}
		}
		break;
	default:
		break;
	}

#if defined(POPLAR_F)
	BackUpCodecPageStatus = CodecPageStatus;	/* for debug */
#endif

	CodecPageStatus = CDC_READY;
	BreakRxTaskCompleteFlag = YES;
}


/*************************************************************************
	module		:[高低速識別時の高速オープン]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/23]
	author		:[村田]
*************************************************************************/
void  FskHighSpeedOpen(UBYTE type, UBYTE speed)
{
	if (type == ECM_OFF) {
		ModemBlock.Mode = MODE_RX_ECM;	/**	交信モード設定	*/ /* add 1996/10/18 Y.Murata */
		RxG3_Open();
#if defined (KEISATSU)
		if (FCM_S1_Scramble == FALSE) { /* スクランブル通信でない場合 */
			MDM_SetIO(POS_HDLC,ON);		/* add 1997/01/23 Y.Murata */
		}
#else
		MDM_SetIO(POS_HDLC,ON);		/* add 1997/01/23 Y.Murata */
#endif
	}
	else {
		RxEcmOpen();
	}

	/* ロックウエルモデム不具合
	 * 1997/09/09 Y.Murata
	 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
	 *  受信できないことがある」
	 * ひらたくいえば、モデムが発散します。
	 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
	*/
	/* ０で有効です */
	if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
		if (ModemBlock.Type == TYPE_V17) {
			/* ｱﾄﾞﾚｽ$B0Fと$A0Fを4000h->4000h */
			/* 設定ﾀｲﾐﾝｸﾞ１ */
			/* 同じ値だから何もしない */
		}
		else if (ModemBlock.Type == TYPE_V29) {
			/* ｱﾄﾞﾚｽ$B0Fと$A0Fを80h->400h */
			/* 設定ﾀｲﾐﾝｸﾞ１ */
			DspRamAccessWriteMethod3(0xA0F, 0x0400, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
			DspRamAccessWriteMethod3(0xB0F, 0x0400, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
		}
		else {
			/* それ以外の時は何もしない */
		}
	}
}


/*************************************************************************
	module		:[キャリア断の検出]
	function	:[
		1.実際に回線断がおこっていてもモデムからモデムバッファにデータが送られている
		  ゴミデータであるのでデーコードできず(EOL検出できず）エラーとなるのだが
		  ゴミデータの中にEOLがある時があるのでその場合、デコードできてしまうので
		  ループしてしまう。
		  そこで、
		  デコードできないブロックおよび、デコードできてもエラーラインしかないブロックが
		  一定以上連続したらキャリア断とする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/30]
	author		:[村田]
*************************************************************************/
UWORD  MDM_CarryDownErrorOrTotalLine(void)
{
	UWORD	no_carry_or_err_block;
	UWORD	time;

	if (CHK_ForeignApprovalDEU()) {
		/*--------------------------*/
		/* 海外認可共通対応         */
		/* FOREIGN_APPROVAL No.1-11 */
		/*--------------------------*/
		/* 受信時、１ラインの送信時間が４．９秒以下の場合は、正しくデータを受信しなければならない。
		 * １３．１秒以上の場合は、フェーズＥへ移行しなければならない。
		*/
		time = (UWORD)(SYS_GeneralTimer - MDM_LineDecodeStartTimer);
		if (time > 900) {	/* 9sec */
			FaxCompatibleErrorCode = MDM_CARRY_DOWN_DEU;
			return(1);
		}
	}

	no_carry_or_err_block = CarryDownBlock;
	if (MDM_NoCarryOrErrorCount > no_carry_or_err_block) {
		FaxCompatibleErrorCode = MDM_NON_ECM_MODE_CARRY_DOWN_1;
		return(1);
	}

	/* 超保険 */
	if (MDM_RxErrorTotalLine > 2000) {
		FaxCompatibleErrorCode = MDM_NON_ECM_MODE_CARRY_DOWN_2;
		return(1);
	}
	else {
		return(0);
	}
}




/*************************************************************************
	module		:[符号変換モード決定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[MDM]
	ProtoType	:[UBYTE DecideStoreCode(void){}]
	date		:[1998/05/20]
	author		:[木元  修]
*************************************************************************/
UBYTE DecideStoreCode(UBYTE item)
{
	UBYTE code;

	code = (UBYTE)SYS_MG3_CODE;

#if (PRO_ROTATE == ENABLE)
	if (DPR_CheckRotateBoardExist() == TRUE) {	/* 回転ボードが接続されている時 */
		code = (UBYTE) ( ( CHK_UNI_StoredMethodMMR()) ? SYS_MMR_CODE : SYS_MR_CODE);
	}
	else {
		code = (UBYTE)(CHK_UNI_NewRxStoredMethod());
	}
#else
	code = (UBYTE)(CHK_UNI_NewRxStoredMethod());
#endif
	return((UBYTE)code);
}

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* SAKAKI プリンタ受信対策 by H.Kubo 1999/03/20 *//* 2002/09/18 By M.Maeda */
/*************************************************************************
	module		:[G3 受信用デコードタイマー起動処理]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[Sh704x]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[UBYTE DecideStoreCode(void){}]
	date		:[1999/03/31]
	author		:[久保博]
*************************************************************************/
void MDM_G3Rx_CreateDecodeTimer(struct Timer10msData_t * timer_ptr)
{
#if (PRO_PRINTER_RX == ENABLE) || (PRO_PRINT_TYPE == THERMAL_TRANS) /* by H.Kubo 1999/03/30 */
	if (RxPmType != RX_PRINTER) {	/**	プリンタ受信	*/
		timer_ptr->Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
	}
	else {
		timer_ptr->Time = 13000/10; /* 13 秒 by H.Kubo 1999/03/31 */
	}
#else
	timer_ptr->Time = 1000/10; /* 100mS->1000mS By kotani 1997/03/22 */
#endif
	timer_ptr->SendMBX = mbxno.MDM_RxEcmControlTask;	/**	メッセージ受信、メイルボックス設定	*/
	timer_ptr->ReturnValue = MSG_DECODE_TIME_OVER;	/**	戻り値設定	*/
	tskno_DecodeTimer = 0xffff;
	cre_tsk(&tskno_DecodeTimer, TSK_CMN_MAN_TIMER10MSTASK, timer_ptr);	/**	タイマタスク起動	*/
}
#endif
