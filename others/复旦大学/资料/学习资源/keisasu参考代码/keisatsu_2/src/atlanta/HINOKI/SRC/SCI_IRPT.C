/*----------------------------------------------------------------------*/
/* プロジェクト : HINOKI                                                */
/* ファイル名   : SCI_IRPT.C                                            */
/* 作成者名     : 平尾 英典                                             */
/* 日  付       : 1999/01/09                                            */
/* 概  要       : ＳＣＩの割込み関数                                    */
/* 修正履歴     :                                                       */
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\define\cl1_def.h"
#include "\src\atlanta\define\cl1_mpsc.h"
#include "\src\atlanta\define\cl1_pro.h"
#endif
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\ext_v\sci_dat.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\mntsw_g.h"
#include "\src\atlanta\ext_v\bkupram.h"

/*************************************************************************
	module		:[受信エラー(ORER, FER, PER)による割り込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void SciErInt(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)

	RsDriver.sci_ssr = Input(SCI_SSR1);
	
	if (SciError & SSR_PER) {
		RsError = RS_PARITY_ERROR; 	/* Set Parity Error */
	}
	else if (SciError & SSR_ORER) {
		RsError = RS_OVERRUN_ERROR;	/* Set RxOverRun Error */
	}
	else {
		RsError = RS_FRAMING_ERROR; /* Set Framing Error */
	}
	
	/* SSRのORER, PER, FERビットを0にクリア */
	/* Output(SCI_SSR1, (RsDriver.sci_ssr & ~(SSR_ORER | SSR_PER | SSR_FER))); 割り込みエントリーでやってる */
	
	/* 割込み監視タスクに対して受信エラーのイベント発生を通知 */
	RsEventFlag |= EFLG_MPSC_ERR;
	idet_evt(EVT_RSCONTROL);
#endif
}

/*************************************************************************
	module		:[受信データフル(RDRF)による割り込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void SciRxInt(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	/* 受信データを読み出す */
	RsData = Input(SCI_RDR1);
	RsDriver.sci_ssr = Input(SCI_SSR1);
	Output(SCI_SSR1, RsDriver.sci_ssr & (~SSR_RDRF));	/* RDRFビットリセット */
	
	/* 受信モード */
	if (RsDevice.mode == 'r') {
		if ((RsDriver.status == WAKEUP)	/* 一番最初のデータ待ち */
		 || (RsDriver.status == SEND_XON)) {	/* Xonを送出し受信を再開 */
			/* 一番最初のキャラクタを読み出し、受信用バッファに入れる */
			/* 受信データをバッファにセーブする */
			*(RsRxBuffer.rsbuf[RsRxBuffer.benqp].bufp + RsRxIntCount) = RsData;
			
			/* 受信バッファ内のデータサイズをインクリメントする */
			RsRxBuffer.rsbuf[RsRxBuffer.benqp].datasize = 1 + RsRxIntCount;
			
			/* DMAによる受信を起動する */
			/* BufTop+1のアドレス、BufSize-1の転送バイト数 */
			RxAddress = (UDWORD)(RsRxBuffer.rsbuf[RsRxBuffer.benqp].bufp + 1 + RsRxIntCount);
#if (PRO_MODEM == R288F) /* DMA 終了タイマ時間を決めるのに、DMA 転送回数を使うので記憶するようにします。By H.Kubo 1998/04/02 */
			RsDriver.dma_count = 0;
			RsDriver.dma_count_save = 0;
			
			CL1_RsRxBufferSize = RSBUFSIZE;
			RsStartDMA('r', RxAddress, CL1_RsRxBufferSize - RsRxIntCount - 1);
#else
			RsStartDMA('r', RxAddress, RSBUFSIZE - RsRxIntCount - 1);
#endif
			RsRxIntCount = 0;
			RsDataOld = 0;
			
			if (RsDriver.status == WAKEUP) {	/* 一番最初のデータ待ち */
				/* 一番最初のキャラクタを受信したイベント発生を通知する */
				RsEventFlag |= EFLG_FIRST_RCV;
				idet_evt(EVT_RSCONTROL);
			}
			RsDriver.status = RUN;
		}
		else if (RsDriver.status == OVER_RUN) {	/* 受信バッファフル */
			/* ここに入ってきてはダメ */
			/* RsRead()の中でXOFFを送信する */
		}
		else {
			if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x02) {	/* ＤＭＡ／ＤＴＣをスイッチで切り替える by H.Hirao 1999/01/23 */
				INT_DMA_RsTxRx();	/* ＤＴＣ終了割り込み */
			}
		}
	}
	/* 送信モード */
	else if (RsDevice.mode == 'w') {
#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1998/03/18 */
#else
		/* 受信データをバッファにセーブする */
		*(&RsDmaBuf[RSNBUFFS][0] + RsRxBuffer.currentp) = RsData;
		/* 受信バッファのポインタを進める */
		if (++RsRxBuffer.currentp >= RSNBUFFS * RSBUFSIZE) {
			RsRxBuffer.currentp = 0;
		}
#endif
		/* XOFF受信 */
		if (RsData == XOFF){
			RsDriver.xflow = XOFF;
			RsDevice.timecount = 0;	/* Xoff期間を測定 */
			CL1InactTimeCount = 0;
		}
		/* XON受信 */
		else if ((RsData == XON) && (RsDriver.xflow == XOFF)) {
			RsDriver.xflow = XON;
			RsDevice.timecount = 0;	/* Xoff期間の測定解除	*/
			CL1InactTimeCount = 0;
			/* 割込み監視タスクに対して "XON_RCV" のイベント発生を通知	*/
			RsEventFlag |= EFLG_XON_RCV;
			idet_evt(EVT_RSCONTROL);
		}
		/* その他 */
		else {
			/* コマンドアボート処理 */
			if ((RsDevice.phase == 'a') || (RsDevice.phase == 'd')) {
				if (CL1RcvAbortChar == 0) {
					RsEventFlag |= EFLG_ABORT_CHAR;
					idet_evt(EVT_RSCONTROL);
				}
			}
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/03/16 */
			else if ((RsDriver.status == UNDER_RUN) && (RsRxIntCount < RSBUFSIZE)) {
				/* FRH に対する応答の後、次の FRM が来るのが早いと取り逃がすことがあるので、
				** 送信バッファが空になってからリードモードでオープンするまでは割り込みで読み続ける。
				** ちなみに、RsClose の後に同じような処理はあるが、 RsClose が呼ばれるまでに受信したものも
				** 取り込むために、あえてこのようにした。
				*/
				UBYTE rs_read_count;
				
				if (RsRxIntCount < RSBUFSIZE-2) {
					RsRxIntBuf[RsRxIntCount] = RsData;
					RsDmaBuf[RSNBUFFS][RsRxIntCount++] = RsData;
					if ((RsData == CR)
					 || ((RsDataOld == DLE) && (RsData == ETX))) {
						/* コマンドを受信したことを通知する */
						RsEventFlag |= EFLG_CMD_RCVED;
						idet_evt(EVT_RSCONTROL);
					}
					RsDataOld = RsData;
				}
				/* 次のデータが受信されていたら、続けてバッファに読み込む */
				/* Atlanta では次の割り込みまでに最大 555us あく可能性があるのに対して、 RS-232C からは
				** 19200bps の設定で最速 400us で 1byte 送られてくるので、割り込み処理で連続して読むと
				** 最悪の場合、読みこぼす。そのため、一度の割り込みでもう一回読む処理を加えておく。
				*/
				
				for (rs_read_count = 5; rs_read_count > 0; rs_read_count--) {
					TxRx_ST = Input(SCI_SSR1); /* 受信バッファの状態を調べる */
					
					RsDriver.sci_ssr = (UBYTE)TxRx_ST;
					
					if (RsDriver.sci_ssr & (SSR_PER | SSR_ORER)) {
						if (RsDriver.sci_ssr & SSR_PER) {
							RsError = RS_PARITY_ERROR;	/* Set Parity Error */
						}
						else if (RsDriver.sci_ssr & SSR_ORER) {
							RsError = RS_OVERRUN_ERROR;	/* Set RxOverRun Error */
						}
						
						Output(SCI_SSR1, (RsDriver.sci_ssr & ~(SSR_ORER | SSR_PER | SSR_FER)));
						
						/* 割込み監視タスクに対して受信エラーのイベント発生を通知	*/
						RsEventFlag |= EFLG_MPSC_ERR;
						idet_evt(EVT_RSCONTROL);
					}
					
					if (TxRx_ST & 0x40 ) { /* 受信バッファにデータはあるか？*/
						RsData = Input(SCI_RDR1);
						/* XOFF受信 */
						if (RsData == XOFF){
							RsDriver.xflow = XOFF;
							RsDevice.timecount = 0;	/* Xoff期間を測定	*/
							CL1InactTimeCount = 0;
						}
						/* XON受信 */
						else if ((RsData == XON) && (RsDriver.xflow == XOFF)) {
							RsDriver.xflow = XON;
							RsDevice.timecount = 0;	/* Xoff期間の測定解除	*/
							CL1InactTimeCount = 0;
							/* 割込み監視タスクに対して "XON_RCV" のイベント発生を通知	*/
							RsEventFlag |= EFLG_XON_RCV;
							idet_evt(EVT_RSCONTROL);
						}
						if (RsRxIntCount < RSBUFSIZE-2) {
							RsRxIntBuf[RsRxIntCount] = RsData;
							RsDmaBuf[RSNBUFFS][RsRxIntCount++] = RsData;
							if ((RsData == CR)
							 || ((RsDataOld == DLE) && (RsData == ETX))) {
								/* コマンドを受信したことを通知する	*/
								RsEventFlag |= EFLG_CMD_RCVED;
								idet_evt(EVT_RSCONTROL);
							}
							RsDataOld = RsData;
						}
					}
					else {
						RsDriver.sci_scr |= SCR_RIE;
						Output(SCI_SCR1, RsDriver.sci_scr);	/* もう一度 Rx 割り込みを許可します。*/
							break;
					}
				} /* for loop */
			}
#endif /* (PRO_MODEM == R288F) */
			else {
				/* ローカルプリントのデータ受信中にRS232Cエラー	*/
				/* が発生しOKのレスポンスを送信する時にAllSent	*/
				/* 割込みが入らなくなる対策						*/
				/* ※ レスポンス送信中、この後に送られてくる	*/
				/*    XOFF/XONは無視される						*/
				RsDriver.sci_scr &= (~(SCR_RE | SCR_RIE));
				Output(SCI_SCR1, RsDriver.sci_scr);
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/03/16 */
				RsRxIntCount = 0; /* ここに来たら、送信モードで受信したデータを破棄します。*/
#endif
			}
		}
	}
	/** テスト・モード */
	else if (RsDevice.mode == 't'){
		/* 受信データをバッファにセーブする */
		*(&RsDmaBuf[RSNBUFFS][0] + RsRxBuffer.currentp) = RsData;
		/* 受信バッファのポインタを進める */
		if (++RsRxBuffer.currentp >= RSNBUFFS*RSBUFSIZE) {
			RsRxBuffer.currentp = 0;
		}

		/** EMI測定のRS232C送信(0x01) or RS232C受信モード(0x02) */
		if ((RsTestMode == 0x01) || (RsTestMode == 0x02)) {
			/* テスト回数をインクリメントする */
			RsTestCount++;
			if (RsData == 0x0c) { 	/* FormFeed(0x0c:CTRL+L) */
				/* テスト終了を上位に通知する */
				RsDevice.status = RS_CLOSE;
				/* 全ての割込みをマスクする */
				RsDriver.sci_scr &= (~(SCR_TIE | SCR_RIE | SCR_TEIE));
				Output(SCI_SCR1, RsDriver.sci_scr);
			}
			else {
				/** 受信キャラクタは読み捨てる */
			}
		}
		else {	/* 通常の折り返しテスト・モード	*/
			if (RsData != RsTestChar) {		/* 受信キャラクタ != テスト・キャラクタ */
				/** テスト・エラーを上位に通知する */
				RsDevice.status = RS_ERR;
				/** 全ての割込みをマスクする */
				RsDriver.sci_scr &= (~(SCR_TIE | SCR_RIE | SCR_TEIE));
				Output(SCI_SCR1, RsDriver.sci_scr);
			}
			else { /** 受信データ = 送信データ */
				/** テスト回数をインクリメントする */
				RsTestCount++;
				if (RsTestCount >= RS_TEST_TIMES) {		/* 100回テストを実行したなら */
					/** テスト正常終了を上位に通知する */
					RsDevice.status = RS_CLOSE;
					/** 全ての割込みをマスクする */
					RsDriver.sci_scr &= (~(SCR_TIE | SCR_RIE | SCR_TEIE));
					Output(SCI_SCR1, RsDriver.sci_scr);
				}
			}
		}
	}
	/* AllSent割込み、及び、送信DMA終了割込み(UNDER_RUN)でRsDevice.modeを	*/
	/* RSIDLEに変更して'w'クローズから'r'オープンするまでの間、割込みで		*/
	/* データを受信します													*/
	else {	/* add 96.02.29 */
		if (RsRxIntCount < RSBUFSIZE-2) {
			RsRxIntBuf[RsRxIntCount] = RsData;
			RsDmaBuf[RSNBUFFS][RsRxIntCount++] = RsData;
			if ((RsData == CR)
			 || ((RsDataOld == DLE) && (RsData == ETX))) {
				/**	コマンドを受信したことを通知する	*/
				RsEventFlag |= EFLG_CMD_RCVED;
				/* 受信モードにして、イベントを発行しないと、コマンドが処理されない by H.Hirao 1999/05/15 */
				RsDevice.mode = 'r';	/* added by H.Hirao 1999/05/15 */
				idet_evt(EVT_RSCONTROL);
			}
			RsDataOld = RsData;
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/03/20 */
			/* 最初の受信割り込みのみ許可のモードでここに来る場合があるので、次の受信のためにもう一度 Rx 割り込みを許可します。*/
			RsDriver.sci_scr |= SCR_RIE;
			Output(SCI_SCR1, RsDriver.sci_scr);	/* もう一度 Rx 割り込みを許可します。*/
#endif /* (PRO_MODEM == R288F) */
		}
	}	/* 96.02.29 */

	if ((RsDevice.mode == 't') && (RsTestMode != 0x02) && (RsTestMode != 0x04)) {
		/* 折り返しテストを送受信とも割り込みで行う場合
		** 送信割り込みと受信割り込みが同時に起きるときがある為
		*/
		TxRx_ST = Input(SCI_SSR1); /* 受信バッファの状態を調べる */
		RsDriver.sci_ssr = (UBYTE)TxRx_ST;
		if (TxRx_ST & 0x80) {
			RsIntStatus = MPSC_TXRDY_INT;
		}
	}
#endif
}

/*************************************************************************
	module		:[送信データエンプティによる割り込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void SciTxInt(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	/** 受信モード */
	if (RsDevice.mode == 'r') {
		/**	ここに来ることはない	*/
		if (RsDriver.status == SEND_XON) {	/**	Xon送出要求	*/
		}
	}
	/** 送信モード */
	else if (RsDevice.mode == 'w') {
		/**	ＤＭＡで送信しているのでここに来ることはない	*/
/* #if (0) */
		if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x02) {	/* ＤＭＡ／ＤＴＣをスイッチで切り替える by H.Hirao 1999/01/23 */
			if (IsManualTXI) {
				IsManualTXI = 0;
				DMA_RequestMask(RsDMA_Data.Channel);
				Output(SCI_SSR1, (Input(SCI_SSR1) & (~SSR_TDRE)));
				RsDriver.sci_scr |= SCR_TEIE;
				Output(SCI_SCR1, RsDriver.sci_scr);
				DMA_RequestEnable(RsDMA_Data.Channel);
			}
			else {
				INT_DMA_RsTxRx();	/* ＤＴＣ終了割り込み */
			}
		}
		else {	/* ＤＭＡの場合のパス */
			/* DMA_RequestMask(RsDMA_Data.Channel); */ /* by H.Hirao 1999/02/18 */
			Output(SCI_SSR1, (Input(SCI_SSR1) & (~SSR_TDRE)));
			RsDriver.sci_scr |= SCR_TEIE;
			Output(SCI_SCR1, RsDriver.sci_scr);
			DMA_RequestEnable(RsDMA_Data.Channel);
		}
/* #endif */
	}
	/** テスト・モード */
	else if (RsDevice.mode  == 't') {
		/** テスト・キャラクタを送信する */
		Output(SCI_TDR1, RsTestChar);
		/* added by H.Hirao 1999/02/09 */
		RsDriver.sci_ssr = (Input(SCI_SSR1) & (~SSR_TDRE));
		Output(SCI_SSR1, RsDriver.sci_ssr);
		/* EMI測定のRS232C送信モード(0x01) */
		if (RsTestMode == 0x01) {
			/** テスト回数をインクリメントする */
			RsTestCount++;
 		}
	}
#endif
}

/*************************************************************************
	module		:[送信終了（ＴＥＮＤ）による割り込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void SciTeInt(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	RsDriver.sci_ssr = Input(SCI_SSR1);
	RsDriver.sci_scr &= (~SCR_TE);	/* added by H.Hirao 1999/02/19 */
	RsDriver.sci_scr &= (~SCR_TIE);	/* added by H.Hirao 1999/02/19 */
	RsDriver.sci_scr &= (~SCR_TEIE);	/* added by H.Hirao 1999/02/19 */
	if (RsAllSent) {
		if (RsDriver.sci_ssr & SSR_TEND) {	/* 全データ送出完了 */
			RsDriver.sci_scr &= (~SCR_TE);
			/* Output(SCI_SCR1, RsDriver.sci_scr);	@* 送信動作を禁止 割り込みエントリーでやってる by H.Hirao 1999/01/27 */
			RsDriver.sci_scr &= (~SCR_TIE);
			/* Output(SCI_SCR1, RsDriver.sci_scr);	割り込みエントリーでやってる by H.Hirao 1999/01/27 */

			RsAllSent = 0;
			SH__IPRB &= (~IRQ7_LEVEL);	/* CTS割り込み(IRQ7)マスク */	/* by H.Hirao 1999/03/17 */
			CmtCtsIntDisable();	/* adde by H.Hirao 1999/03/17 */
			RsDriver.sci_scr &= (~SCR_TEIE);
			/* Output(SCI_SCR1, RsDriver.sci_scr);	/* 送信終了(TEI)割り込み要求を禁止 割り込みエントリーでやってる by H.Hirao 1999/01/27 */
			
			RsEventFlag = 0;	/* 1996/03/27 */
			RsDevice.mode = RSIDLE;	/* 必ずいる */
			RsDevice.status = RS_CLOSE;

			RsRxIntCount = 0;
			RsDataOld = 0;

			/* 送信完了待ちでsleepしているタスクをwakeupする */
			CL1_AllSentComplete = 1;	/* 1997/02/19 MPSC割り込み不良対策 */
			idet_evt(EVT_CL1WAKEUP);
		}
	}
#endif
}

/*************************************************************************
	module		:[RS232C CTS割込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void IntSciCTS(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
 #if (0)
**	if (RsDevice.mode == 'w') {
**		RsDriver.cts = CTS_OFF;
**		RsEventFlag |= EFLG_CTS_RCV;
**		idet_evt(EVT_RSCONTROL);
**	}
 #else
	if ((RsDevice.mode == 'w') && (RsDevice.phase == 'd')) {	/* added by H.Hirao 1999/05/17 */
 #if (1)	/* 0 -> 1 changed by H.Hirao 1999/05/14 */
		if (!RsAllSent) {	/* added by H.Hirao 1999/05/14 */
			RsMaskDMA();
			RsDriver.cts = CTS_ON;
			SH__IPRB &= (~IRQ7_LEVEL);	/* CTS割り込み(IRQ7)マスク by H.Hirao 1999/05/14 */
			PFC__PDCRH2 &= ~PDCRH2_PD23MD_IRQ7;		/* ＩＲＱ７ -> 入力ポート added by H.Hirao 1999/05/14 */
			CmtCtsIntEnable();
		}
 #else
		/* by H.Hirao 1999/03/30 */
		RsDriver.cts = CTS_OFF;
		RsEventFlag |= EFLG_CTS_RCV;
		SH__IPRB &= (~IRQ7_LEVEL);	/* CTS割り込み(IRQ7)マスク */
		PFC__PDCRH2 &= ~PDCRH2_PD23MD_IRQ7;		/* ＩＲＱ７ -> 入力ポート */
		CmtCtsIntEnable();
		idet_evt(EVT_RSCONTROL);
 #endif
	}
 #endif
#endif
}

/*************************************************************************
	module		:[CMT割込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/03/16]
	author		:[平尾 英典]
*************************************************************************/
void CmtCtsInt(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
 #if (0)
**	CmtCtsIntDisable();
**	if (RsDevice.mode == 'w') {
**		PFC__PDCRH2 &= ~PDCRH2_PD23MD_IRQ7;		/* ＩＲＱ７ -> 入力ポート */
**		if ((inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS) && (RsDriver.cts == CTS_OFF)) {
**			RsMaskDMA();
**			RsDriver.cts = CTS_ON;
**		}
**		PFC__PDCRH2 |= PDCRH2_PD23MD_IRQ7;		/* 入力ポート -> ＩＲＱ７ */
**	}
**	CmtCtsIntEnable();
 #else
	CmtCtsIntDisable();
  #if (1)	/* 0 -> 1 changed by H.Hirao 1999/05/14 */
	if (!RsAllSent) {
		if (RsDevice.mode == 'w') {
			if (RsDriver.cts == CTS_ON) {
				PFC__PDCRH2 &= ~PDCRH2_PD23MD_IRQ7;		/* ＩＲＱ７ -> 入力ポート */
				if (inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS) {
					RsDriver.cts = CTS_OFF;
					RsEventFlag |= EFLG_CTS_RCV;
					idet_evt(EVT_RSCONTROL);
					PFC__PDCRH2 |= PDCRH2_PD23MD_IRQ7;		/* 入力ポート -> ＩＲＱ７ */
					SH__IPRB &= ~IRQ7_LEVEL;
				}
				else {
					CmtCtsIntEnable();
				}
				/* PFC__PDCRH2 |= PDCRH2_PD23MD_IRQ7;		@* 入力ポート -> ＩＲＱ７ comment by H.Hirao 1999/05/14 */
			}
			else {
				/* CmtCtsIntEnable(); comment by H.Hirao 1999/05/14 */
			}
		}
		else {
			/* CmtCtsIntEnable(); comment by H.Hirao 1999/05/14 */
		}
	}
  #else
	/* by H.Hirao 1999/03/30 */
	if (RsDevice.mode == 'w') {
		if (RsDriver.cts == CTS_OFF) {
			if (!(inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS)) {
				RsMaskDMA();
				RsDriver.cts = CTS_ON;
				PFC__PDCRH2 |= PDCRH2_PD23MD_IRQ7;		/* 入力ポート -> ＩＲＱ７ */
				SH__IPRB |= IRQ7_LEVEL;
			}
			else {
				CmtCtsIntEnable();
			}
		}
		else {
			CmtCtsIntDisable();
		}
	}
	else {
		CmtCtsIntDisable();
	}
  #endif
 #endif
#endif
}

/*************************************************************************
	module		:[CMT割込み許可]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/03/17]
	author		:[平尾 英典]
*************************************************************************/
void CmtCtsIntEnable(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	CMT__CMCSR0 = 0x40;	/* ＣＭＴ割り込み許可 */
	CMT__CMCOR0 = 0x300;
	CMT__CMSTR |= 0x01;	/* カウンタスタート */
	SH__IPRG |= CMT0_LEVEL;	/* ＣＭＴ０割り込み許可 */
#endif
}

/*************************************************************************
	module		:[CMT割込み禁止]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/03/17]
	author		:[平尾 英典]
*************************************************************************/
void CmtCtsIntDisable(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	SH__IPRG &= ~CMT0_LEVEL;	/* ＣＭＴ０割り込みマスク */
	CMT__CMSTR &= ~0x01;	/* ＣＭＣＮＴ０のカウンタ動作停止 */
	CMT__CMCSR0 &= ~0x40;	/* コンペアマッチ割り込み禁止 */
#endif
}

/*************************************************************************
	module		:[RS232C CTS 監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CL1]
	date		:[1999/01/09]
	author		:[平尾 英典]
*************************************************************************/
void CL1_WatchCTS_Task(void)
{
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	while (1) {
		if (RsDevice.mode == 'w') {
			/* if ((inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS) && (RsDriver.cts == CTS_ON)) { */
			if ((!(inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS)) && (RsDriver.cts == CTS_ON)) {
				RsDriver.cts = CTS_OFF;
				RsEventFlag |= EFLG_CTS_RCV;
				idet_evt(EVT_RSCONTROL);
			}
			/* else if ((!(inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS)) && (RsDriver.cts == CTS_OFF)) { */
			else if ((inpw(IO_PDDRH_PORT) & IO_BIT_RS_CTS) && (RsDriver.cts == CTS_OFF)) {
				RsMaskDMA();
				RsDriver.cts = CTS_ON;
			}
			else {
				wai_tsk(1);
			}
		}
		else {
			wai_tsk(1);
		}
	}
#endif
	wai_tsk(0xffff);
}
