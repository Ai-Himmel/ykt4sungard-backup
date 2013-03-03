/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_fsk.c                                                 */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ＦＳＫ送受信関連処理                                      */
/*  修正履歴     :                                                           */
/*	keyword      :[MDM]                                                      */
/*	machine      :[SH7043,                                                   */
/*	language     :[MS-C(Ver.6.0)]                                            */
/*---------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1997/10/08 */

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h" /* Added by H.Kubo 1997/07/08 */
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */

/********
** define
********/
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#include "\src\atlanta\define\mnt_sw.h" /* aded by H.Kubo 1999/06/10 */
#include "\src\atlanta\ext_v\bkupram.h" /* aded by H.Kubo 1999/06/10 */

/*************************************************************************
	module		:[ＦＳＫ送信モデムオープン]
	function	:[
		1.ＨＤＬＣ送信モードでモデムを設定する
		2.ＦＳＫ送信フレーム監視タスク起動
		3.プリアンブル送出時間ウェイトする
	]
	return		:[なし]
	common		:[
		ModemControl
		ModemBlock
		ModemWork[]
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxFskOpen(void)
{
	UWORD	tmout;

	/**********************************
	** モデムコントロールブロック初期化
	**********************************/
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);
#if (PRO_CLASS1 == ENABLE)/* Added by H.Kubo 1998/03/04 */
	MDM_ModemBufferFirstPoint = 0; /* FSK の処理ではモデムバッファの位置が固定。*/
#endif

	/******************************
	** 交信モードを送信ＦＳＫに設定
	******************************/
	ModemBlock.Mode = MODE_TX_FSK;

	ModemInterruptFlag = 0;	/*	モデム割り込み完了フラグ初期化	*/

	/* モデムステータス設定 ＨＤＬＣモード
	**                      フラグ送出中
	**                      単独コマンド／レスポンス
	**                      送信モード
	**/
	ModemControl.Status = STAT_FRSTON + STAT_HDLCMOD + STAT_REQRES + STAT_TXMOD;

	/*	モデム出力　ＨＤＬＣモード
	**　　　　　　　フラグ送出ＯＮ
	*/

	ModemConfig(WRITE_MODE);

	MDM_SetIO(POS_NSIE,ON);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */

	/*	ＦＳＫ送信フレーム監視タスク起動	*/
	tskno_TxFskControl = 0xffff;
	cre_tsk(&tskno_TxFskControl, TSK_MDM_TXFSKFRAMECONTROLTASK, 0);

	if (!(SYS_V34ProcedureExecuting())) {
		/*	プリアンブル送出時間設定	*/
		if (ModemBlock.Type == TYPE_FSK) {	/**	ＦＳＫの時	*/
			if (ShorteningPreambleFlag == 1) {	/**	後手順短縮ハンドシェーク有効の時	*/
				tmout = CHK_UNI_PostMsgPreambleTime(); /* CHK_PostMsgPreambleTime => CHK_UNI_PostMsgPreambleTime by H.Kubo 1997/07/08 */
			}
#if defined (KEISATSU) /* 警察FAX 05/07/25 石橋正和 */
			else if (FCM_S1_Preamble3S == TRUE) {
				tmout = 3000;
			}
#endif
			else {
				tmout = 1000;	/**	１０００ｍｓ設定	*/
			}
		}
		else {	/**	高速の時	*/
			switch (ModemBlock.Speed) {	/**	送信スピード	*/
			case SPEED_2400:	/**	２４００ｂｐｓの時	*/
				tmout = 150;	/**	１５０ｍｓ設定	*/
				break;
			case SPEED_9600:	/**	９６００ｂｐｓの時	*/
			case SPEED_14400:	/**	１４４００ｂｐｓの時	*/
				tmout = 1000;	/**	１０００ｍｓ設定	*/
				break;
			default:			/**	その他の時	*/
				tmout = 0;		/**	０ｍｓ設定	*/
				break;
			}
		}
		wai_tsk(tmout/10);	/**	フラグ送出タスクウェイト	*/
	}
	else {
		/**	Ｖ．３４はフラグ送出のタイマーは必要ありません。	*/

		/* Ported from Clover by H.Kubo 1998/02/03 */
		/* 1997/10/07 Y.Murata
		 * 受信ﾚﾍﾞﾙが-39dBmで遅延がない時にﾘﾄﾚｰﾝが発生する
		 * ２発目のﾎﾟｽﾄﾒｯｾｰｼﾞとﾘﾄﾚｰﾝがかぶってしまう時がある。
		 * かぶらないようにFSKの頭にﾌﾟﾘｱﾝﾌﾞﾙをつけてずらす対策です。
		*/
		tmout = CHK_V34_PreambleTime();
		if (tmout) {
			wai_tsk(tmout);
			MDM_CheckCcRetrain();
		}
	}
}


/*************************************************************************
	module		:[ＦＳＫ送信モデムライト]
	function	:[
		1.送出バッファのアドレスと送出データ数をバッファ管理テーブルに登録する
		2.エコー対策の為、最終フレームをセーブ
		3.モデムがアイドル状態の時、送信ＤＭＡ起動
		4.モデム書き込み位置が最終のとき、先頭に設定
	]
	return		:[なし]
	common		:[
		ModemControl
		EchoLastFCF
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxFskWrite(
UBYTE  *buffer,	/*	送信バッファポインタ	*/
UWORD count)	/*	送信データカウント	*/
{
	/*	フレーム書き込みモデムバッファ獲得処理	*/
	ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/

	/*	送信フレーム登録	*/
	MDMWPNT.TopAddress = buffer;	/**	モデムバッファ書き込み位置にバッファポインタを登録	*/
	MDMWPNT.DataCount = count;	/**	モデムバッファ書き込み位置にデータカウントを登録	*/

	/*	最終フレーム判断	*/
	if ((buffer[1] & LAST_FRAME) && (ServiceFuncTx == FALSE)){	/**	最終フレーム送出時処理	*/
		ModemControl.Status |= STAT_EMPTYPT;	/**	モデムステータス、最終フレーム登録完了	*/

		/*--------------------------*/
		/* 海外認可共通対応         */
		/* FOREIGN_APPROVAL No.1-6  */
		/*--------------------------*/
		/* 自機がだしたＤＩＳに対してＤＩＳを受信した場合、フェーズＥにいく
		*/
		if (CHK_ForeignApprovalDEU()) {
		}
		else {
			EchoFCF = *(buffer + 2);	/**	エコー対策用に最終フレームＦＣＦをセーブ	*/
		}
	}

	/*	モデムバッファ書き込み位置更新処理	*/
	NextMdmBufWritePointSetExtRom();

	/*	送信ＤＭＡ起動開始メッセージ送信
	**	MSG_TX_FSK_START:	ＦＳＫ送信フレーム監視タスクへ
	*/
	CMN_DisableInterrupt();
	if (!(ModemControl.Status & STAT_ACT)) {	/**	モデムがＩＤＬＥ状態の時	*/
		ModemControl.Status |= STAT_ACT;	/**	モデムステータスをＡＣＴＩＶＥに設定	*/
		CMN_EnableInterrupt();
		ModemMessage.Message = MSG_TX_FSK_START;
		snd_msg(mbxno.MDM_Task, &ModemMessage);	/**	送信ＤＭＡ起動メッセージ送信	*/
	}
	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[ＦＳＫ送信モデムスタート]
	function	:[
		1.現在のモデムバッファ読み出し位置のアドレスと転送バイト数で送信ＤＭＡを起動する
	]
	return		:[なし]
	common		:[
		ModemContol
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxFskStart(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	UBYTE debug;
	UBYTE data;

	/*	モデムＤＭＡ設定	*/
	CMN_DisableInterrupt();
	MDM_SetIO(POS_TEOF,OFF);	/** モデムにＴＥＯＦをリセットする。 **/
	MDM_LastData = ON;
	CMN_EnableInterrupt();

	/* コントロールチャンネルリトレインが実行されている可能性があるので
	** ここで、念のため ＣＴＳをチェックし、ＣＴＳがＯＦＦの時はＯＮするまで
	** Ｗａｉｔする（For Debug  By O.Kimoto 1996/05/10
	*/
	MDM_CheckCcRetrain();

	ModemWriteDMA_Data.Channel		= DMA_CH_TX;
	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	絶対アドレスに変換	*/

	/** ＨＤＬＣモード時は最後の１バイトはＤＭＡ＿ＴＣ監視タスク内で出力します **/
	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount - 1; /* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta*/
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);
	/* Added by H.Kubo 1997/10/08
	**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	DMA_RequestEnable(ModemWriteDMA_Data.Channel); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */

	/*	モデムステータス設定　フラグ送出ＯＦＦ
	**	　　　　　　　　　　　モデムデバイスアクティブ
	**　　　　　　　　　　　　ＦＣＳ割り込み
	*/
	ModemControl.Status &= STAT_FRSTOFF;	/**	フラグ送出ＯＦＦ	*/
	ModemControl.Status |= STAT_ACT + STAT_ALSENT;

	debug = 0;
	if (debug) {
		if (ModemInterruptFlag) {
			data = 0;
		}
	}
}


/*************************************************************************
	module		:[ＦＳＫ送信モデムクローズ]
	function	:[
		1.全フレーム送信完了メッセージを受信する
		2.ＦＳＫ送信フレーム監視タスクを終了する
		3.モデム割り込み監視タスク終了する
		3.ＤＭＡ転送終了
		4.モデムコンフィグ再設定
	]
	return		:[なし]
	common		:[
		ModemMessage
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxFskClose(void)
{
	MESSAGE_t	*MDM_Msg;
	/* Ｖ．３４通信で、かつ、Ｔ．３０ＰｈａｓｅＢ１の途中でリトレインがかかると
	** ここでループすることがあるので、モデムがアボートしている場合には、
	** メッセージを待たずに処理を継続します。  尚、その後の処理はＦＣＭ側で
	** 対応しています。
	** BY O.Kimoto 1996/10/25
	*/
	if (SYS_V34ProcedureExecuting()) {
		if (MDM_ClearToSendAbort != TRUE) {
			/*	メッセージ受信処理
			**	1.MSG_TX_COMPLETE:	ＦＳＫ送信フレームコントロールタスクより( MDM_TxFskFrameControlTask() )
			*/
			do {
				rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/*	全送信完了メッセージ受信	*/
			} while (!(MDM_Msg->Message == MSG_TX_COMPLETE));
		}
	}
	else {
		/*	メッセージ受信処理
		**	1.MSG_TX_COMPLETE:	ＦＳＫ送信フレームコントロールタスクより( MDM_TxFskFrameControlTask() )
		*/
		do {
			rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/*	全送信完了メッセージ受信	*/
		} while (!(MDM_Msg->Message == MSG_TX_COMPLETE));
	}

	/**	モデムバッファ－＞モデムＤＭＡ終了	*/
	DMA_RequestMask(DMA_CH_TX); /* Modified by H. Kubo for POPLAR_H, 1997/06/17 */

	/**	モデムクローズ処理	*/
	MDM_SetIO(POS_NSIE,OFF);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */

	if (!(SYS_V34ProcedureExecuting())) {
		MDM_SetIO(POS_RTS,OFF);

		if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 1997/01/31 Y.Murata */
			/* Nothing */
		}
		else {
			wai_tsk(3);		/* V21H -> V29 Mode Spike Noise wait */
		}
	}

	MDM_InitialConfig();

	/**	送信フレーム監視タスク終了	*/
	if (tskno_TxFskControl != 0xffff) {
		del_tsk(&tskno_TxFskControl);
	}

	/*	モデムバッファセマフォリセット	*/
	ResetModemBufferSem();
}


/*************************************************************************
	module		:[ＦＳＫ送信フレーム監視タスク]
	function	:[
		1.モデム割り込み監視タスクを起動する
		2.通信タスクより、送出開始メッセージ受信する
		3.モデムＶ５３ＤＭＡを起動する
		4.ＦＳＫ送出監視用にタイマタスクを起動する（ＧＡＬＡＸＹの時、ＦＣＳ割り込みがかからないことがあったので）
		5.モデム割り込み監視タスク／タイマタスクより、フレーム送出完了メッセージを待つ
		6.モデムバッファ読み出し位置を更新／モデムバッファ資源解放
		7.フレーム間フラグ送出処理
		8.次フレーム送信処理
		9.終結フラグ送出処理
		10.全フレーム送信完了メッセージ送信
	]
	return		:[なし]
	common		:[
		ModemControl
		ModemMessage
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_TxFskFrameControlTask(void)
{
	MESSAGE_t	*MDM_Msg;
	struct	Timer10msData_t FskTimer;
	UWORD	fsktime;
	UWORD	flagtime;

	/**	モデム割り込み監視タスク起動	*/
	tskno_ModemInterrupt = 0xffff;
	cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);

	/*	メッセージ受信処理
	**	MSG_TX_FSK_START	:	通信タスクより
	*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);
	} while (!(MDM_Msg->Message == MSG_TX_FSK_START));

	/**	ＦＳＫ送信モデムスタート（モデムＤＭＡ起動）	*/
	TxFskStart();

	/*	ＦＳＫ送出ＭＡＸ時間設定処理（１０ｍｓタイマ用に設定含む）
	** 23byte+2byte(FCS)->667ms    690ms
	** 23+5->740ms TimerTask
	*/
	fsktime = SetFskTime(MDMRPNT.DataCount);

	/*	タイマタスク起動	*/
	FskTimer.Time = (fsktime/10);	/**	ＦＳＫ送出ＭＡＸ時間設定	*/
	FskTimer.SendMBX = mbxno.MDM_TaskSub;	/**	メッセージ受信、メイルボックス設定	*/
	FskTimer.ReturnValue = MSG_FSK_TIME_OVER;	/**	戻り値設定	*/
	timerID_FcsDetectTimer = 0xFF;
	CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &FskTimer); /* タイマ起動 */

	while (1) {	/**	最終フレーム送出するまで、フレーム監視実行	*/
		/*	メッセージ待ち処理（ＦＳＫ送出完了待ち）
		**	１．モデム割り込み監視タスクより（ＦＳＫ送出完了）
		**	２．タイマタスクより（ＦＳＫ送出時間オーバ）
		*/
		do {
			rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);
		} while (!((MDM_Msg->Message == MSG_TXFRAME_END) ||
		           (MDM_Msg->Message == MSG_FSK_TIME_OVER)));

		/**	ＦＳＫ送出監視タイマタスク終了	*/
		if (timerID_FcsDetectTimer != 0xFF) {
			CMN_MultiTimer10msStop(&timerID_FcsDetectTimer);
		}

		/*	モデム割り込み監視タスク終了	*/
		if (tskno_ModemInterrupt != 0xffff) {
			del_tsk(&tskno_ModemInterrupt);
		}

		/**	モデムバッファ資源解放（今、送出完了したモデムバッファを解放します）*/
		ModemBufferSigSem(ModemControl.ReadPoint);

		/**	モデムバッファ読み出し位置更新処理	*/
		NextMdmBufReadPointSetExtRom();

		/**	ストップ処理	*/
		if (SYS_FaxComStopSwitch() == 1) {
			break;
		}

		/**	次フレーム送信処理	*/
		if (ModemControl.WritePoint != ModemControl.ReadPoint) {
			/**	フレーム間フラグ送出処理	*/
			if (!(SYS_V34ProcedureExecuting())) {
				flagtime = SetFskTime(FLAG_DATA);	/*	現在１バイト	*/
				wai_tsk(flagtime/10);
			}

			/**	モデム割り込み監視タスク起動	*/
			tskno_ModemInterrupt = 0xffff;
			cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);

			/*	モデムＤＭＡ再起動処理	*/
			CMN_DisableInterrupt();
			MDM_SetIO(POS_TEOF,OFF);	/** モデムにＴＥＯＦをリセットする。 **/
			MDM_LastData = ON;
			CMN_EnableInterrupt();

			/** ＨＤＬＣモード時は最後の１バイトはＤＭＡ＿ＴＣ内で出力します。 **/
			/* 1st argument MASTER_DMAU of DMA_RestartDMAU() is deleted by H. Kubo 1997/06/24 */
			DMA_RestartDMAU( DMA_CH_TX, DMA_MEMORY_TO_IO, MDMRPNT.DataCount - 1, (UDWORD)MDMRPNT.TopAddress);

			/*	モデムステータス設定　フラグ送出ＯＦＦ
			**	　　　　　　　　　　　モデムデバイスアクティブ
			**　　　　　　　　　　　　ＦＣＳ割り込み
			*/
			ModemControl.Status &= STAT_FRSTOFF;	/**	フラグ送出ＯＦＦ	*/
			ModemControl.Status |= STAT_ACT + STAT_ALSENT;
				/**	モデムステータスをＡＣＴＩＶＥに設定	*/
				/**	モデムステータスをＦＣＳ送出割り込みに設定	*/

			/**	ＦＳＫ送出ＭＡＸ時間設定処理（１０ｍｓタイマ用に設定含む）	*/
			fsktime = SetFskTime(MDMRPNT.DataCount);

			/*	タイマタスク起動	*/
			FskTimer.Time = (fsktime/10);	/**	ＦＳＫ送出ＭＡＸ時間設定	*/
			FskTimer.SendMBX = mbxno.MDM_TaskSub;	/**	メッセージ受信、メイルボックス設定	*/
			FskTimer.ReturnValue = MSG_FSK_TIME_OVER;	/**	戻り値設定	*/
			timerID_FcsDetectTimer = 0xFF;
			CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &FskTimer); /* タイマ起動 */
		}
		/**	次登録フレーム無し処理	*/
		else {
			ModemControl.Status &= ~STAT_ACT;
			if (ModemControl.Status & STAT_EMPTYPT) {	/**	最終フレーム送出時	*/
				break;	/**	終結フラグ送出処理へ	*/
			}
			else {	/**	未登録状態の時	*/

				ServiceFuncTx = FALSE;

				do {
					rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	登録完了メッセージ待ち	*/
				} while (!(MDM_Msg->Message == MSG_TX_FSK_START));

				/**	モデム割り込み監視タスク起動	*/
				tskno_ModemInterrupt = 0xffff;
				cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);

				/**	ＦＳＫ送信モデムスタート（Ｖ５３モデムＤＭＡ起動）	*/
				TxFskStart();

				/**	ＦＳＫ送出ＭＡＸ時間設定処理（１０ｍｓタイマ用に設定含む）	*/
				fsktime = SetFskTime(MDMRPNT.DataCount);

				/*	タイマタスク起動	*/
				FskTimer.Time = (fsktime/10);	/**	ＦＳＫ送出ＭＡＸ時間設定	*/
				FskTimer.SendMBX = mbxno.MDM_TaskSub;	/**	メッセージ受信、メイルボックス設定	*/
				FskTimer.ReturnValue = MSG_FSK_TIME_OVER;	/**	戻り値設定	*/
				timerID_FcsDetectTimer = 0xFF;
				CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &FskTimer); /* タイマ起動 */
			}
		}
	}
	/**	終結フラグ送出処理	*/
	/* 追加 By O.K Feb.26,1996 */
	if (!(SYS_V34ProcedureExecuting())) {
		if ((CHK_TerminateFlag()-1) < 3) {	/* 1996/10/17 Y.Murata */
			wai_tsk(60/10);	/* 2byte Flag->53.33ms */
		}
		else{
			wai_tsk((UWORD)(80+(((CHK_TerminateFlag()-1)-3)*30))/10);
		}
	}
	/*	モデム割り込み監視タスク終了	*/
	if (tskno_ModemInterrupt != 0xffff) {
		del_tsk(&tskno_ModemInterrupt);
	}

	/**	ＦＳＫ送出監視タイマタスク終了	*/
	if (timerID_FcsDetectTimer != 0xFF) {
		CMN_MultiTimer10msStop(&timerID_FcsDetectTimer);
	}

	/*	メッセージ送信処理
	**	MSG_TX_COMPLETE:	通信タスクへ（MDM_TxFskClose())
	*/
	ModemMessage.Message = MSG_TX_COMPLETE;
	snd_msg(mbxno.MDM_Task, &ModemMessage);
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[ＦＳＫ送信フレーム監視タスク]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_TxFskFrameControlExit(void)
{
	/*	モデム割り込み監視タスク終了	*/
	if (tskno_ModemInterrupt != 0xffff) {
		del_tsk(&tskno_ModemInterrupt);
	}

	/**	ＦＳＫ送出監視タイマタスク終了	*/
	if (timerID_FcsDetectTimer != 0xFF) {
		CMN_MultiTimer10msStop(&timerID_FcsDetectTimer);
	}

	/* 自タスクの終了 */
	exi_tsk();
}

/*************************************************************************
	module		:[ＦＳＫ受信モデムオープン]
	function	:[
		1.ＦＳＫ受信モードでモデムを設定する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemBlock
		ModemRxStatus
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/10]
	author		:[曽根岡拓]
*************************************************************************/
void 	RxFskOpen(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	/*
	** R288F VERSION 24P以降の場合
	** by H.Kubo 1998/11/05
	*/
	UBYTE i;
	
	/**	モデムバッファ読み出し位置初期化	*/
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), ( char )0x00);
#if (PRO_CLASS1 == ENABLE)/* Added by H.Kubo 1998/03/04 */
	MDM_ModemBufferFirstPoint = 0; /* FSK の処理ではモデムバッファの先頭位置が固定。*/
#endif

	/*	モデム受信ステータス初期化	*/
	ModemRxStatus = 0xff;

	/**	モデムタイプ、速度設定	*/
	if (!(SYS_V34ProcedureExecuting())) {
		ModemTypeSet(BPS300_V21);	/**	ＦＳＫモードに設定	*/
	}

	/*	モデムステータス設定　ＨＤＬＣモード
	**　　　　　　　　　　　　単独コマンド／レスポンス
	**　　　　　　　　　　　　フラグ検出
	*/
	ModemControl.Status = STAT_HDLCMOD + STAT_REQRES;

	/*	交信モードを受信ＦＳＫに設定	*/
	ModemInterruptFlag = 0;
	ModemBlock.Mode = MODE_RX_FSK;

/* test 1997/03/31 Y.M */
	if (MDM_GetIO(POS_SYNCD)) {
		MDM_SetIO(POS_SYNCD, OFF);
	}

	/**	モデムコンフィグレーション実行	*/
	ModemConfig(READ_MODE);

/* test 1997/03/31 Y.M */
	if (MDM_GetIO(POS_SYNCD)) {
		MDM_SetIO(POS_SYNCD, OFF);
	}


#if (0) /* (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P)  */ /* by H.Kubo 1998/11/05 */ /* Deleted by H.Kubo 1998/11/12 */
** 	/* ポストメッセージ受信の最初に出る PE, FE は R4.2 に関係ないので消します。  by H.Kubo 1998/11/12 */
** 	/* R4.2 対策(試験中)。  PIX 受信後、コントロールチャンネル確立するまで FE ビットが立ちっぱなしのときがある */
** 	if (MDM_DmaStart == MDM_DMA_MASK) {
** 		CMN_DisableInterrupt();
**  		IsRlsdAndRdbfOn = 0;
** 		CMN_EnableInterrupt();
** 	}
** 	if (MDM_GetIO(POS_FE) || MDM_GetIO(POS_PE)) {
** 		for (i = 0; (i < 16) && (MDM_GetIO(POS_FE) || MDM_GetIO(POS_PE)); i++) {
** 			(void) MDM_GetIO(POS_RBUFFER);
** 		}
** 		MDM_SetIO(POS_FE, OFF);
** 		MDM_SetIO(POS_PE, OFF);
** 	}
** 	MDM_SetIO(POS_OE, OFF);
#endif

#if (0) /* HINOKI2' QATでの不具合。FM336でSuperG3のSTX受信で約10%の確立でR.4.2エラーになる。他の機種と合わせます。O.Oshima 2004/05/06 */
#if defined (HINOKI) || defined (HINOKI2) /* || defined (SATSUKI2) STXのSuperG3の受信不可のため削除 O.Oshima 2003/10/29 *//* 一時的なDebugの為です。 by O.Kimoto 1998/11/11 */ /* ported for HINOKI2 2001/11/12 T.Takagi */
//		MDM_SetIO(POS_RDBIE,ON);	/** PNSUC Access By O.Kimoto 1996/05/13 **/
#endif
#endif

	MDM_SetIO(POS_NSIE,ON);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */

/* test 1997/03/31 Y.M */
	if (MDM_GetIO(POS_SYNCD)) {
		MDM_SetIO(POS_SYNCD, OFF);
	}

	ModemWriteDMA_Data.Channel		= DMA_CH_RX;
	ModemWriteDMA_Data.DstAddress	= (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0];	/*	絶対アドレスに変換	*/
	ModemWriteDMA_Data.SrcAddress = ModemWriteDMA_Data.DstAddress; /* SrcAddress is used in DMA_SetupDMAU() */
	ModemWriteDMA_Data.Counter		= RX_FSK_HDLC_LENGTH; /* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta.*/
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_IO_TO_MEMORY;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

#if defined(POPLAR_F)
	DMA_RequestEnableSub(DMA_CH_RX);
#endif

#ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	if (MDM_DmaStart == MDM_DMA_MASK) {
		CMN_DisableInterrupt();
		MDM_SetIO(POS_RDBIE,ON);
		MDM_DmaStart = MDM_DMA_READY;

 		/*
 		** R288F VERSION 22P以降の場合
 		** by H.Kubo 1998/10/17
 		*/
 		IsRlsdAndRdbfOn = 0;

		CMN_EnableInterrupt();
	}
	else {
		outp(0,0);	/* ここにきたらダメ */
	}
#else
	if (MDM_DmaStart == MDM_DMA_MASK) {	/** 不正割り込み対策 By O.K Feb.14,1996 **/
		CMN_DisableInterrupt();
		MDM_SetIO(POS_RDBIE,ON);
		MDM_DmaStart = MDM_DMA_READY;

 		/*
 		** R288F VERSION 22P以降の場合
 		** by H.Kubo 1998/10/17
 		*/
 		IsRlsdAndRdbfOn = 0;

		CMN_EnableInterrupt();
	}
#endif
}


/*************************************************************************
	module		:[ＦＳＫ受信モデムクローズ]
	function	:[
		1.ＤＭＡ終了処理
		2.モデムコンフィグレーション再設定
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/10]
	author		:[曽根岡拓]
*************************************************************************/
void 	RxFskClose(void)
{
	UBYTE count;

	ModemBlock.Mode = 0;	/* 1997/02/10 Y.Murata */

	/**	モデム－＞モデムバッファＤＭＡ終了	*/
	DMA_RequestMask(DMA_CH_RX); /* Modified by H. Kubo for POPLAR_H, 1997/06/17 */

	/** ＤＭＡ起動処理 By O.K Jan.26,1996 **/
	MDM_SetIO(POS_RDBIE,OFF);
	MDM_DmaStart = MDM_DMA_MASK;

	MDM_SetIO(POS_NSIE,OFF);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */

	/* 以下のコードはＲｏｃｋｗｅｌｌのソースより移植 By O.K Feb.17,1996 */
	for( count=0; count<16; count++ ) {
		(void)inp(MDM_REG_00_PORT);
	}

	/* 1997/02/10 Y.Murata
	 *
	 *
	*/
	if (SYS_V34ProcedureExecuting() == 0) {
		count = 0;

#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
		if (MDM_GetIO(POS_SYNCD)) {
			do {
				wai_tsk(1);
				count++;
				if (count > 10) {
					break;
				}
			} while (MDM_GetIO(POS_SYNCD));
		}
#else
#if defined (KEISATSU) /* 警察FAX 05/11/17 石橋正和 */
		if (MDM_GetIO(POS_SYNCD) || MDM_GetIO(POS_RLSD)) {
#else
		if (MDM_GetIO(POS_SYNCD)) {
#endif
			do {
				wai_oneshot(1);
				count++;
				if (count > 100) {
					break;
				}
#if defined (KEISATSU) /* 警察FAX 05/11/17 石橋正和 */
			} while (MDM_GetIO(POS_SYNCD) || MDM_GetIO(POS_RLSD));
#else
			} while (MDM_GetIO(POS_SYNCD));
#endif
		}
#endif
		else {
			wai_tsk(1);
		}
	}

	/**	モデムクローズ処理	*/
	MDM_InitialConfig();
}


/*************************************************************************
	module		:[フレーム受信コントロールタスク]
	function	:[
		1.Ｔ２／Ｔ４タイマタスク起動処理
		2.３０秒タイマタスク起動処理
		3.フラグ検出処理
		4.フレーム検出処理
		5.メッセージ送信
		6.ＦＳＫ受信モデムクローズ
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		MDM_ModemBuffer
		ModemMessage
	]
	condition	:[]
	comment		:[
		95/6/17 リコーからのポストメッセージが受信できない
			プリアンブルのフラグがフラグ共有されたＦＳＫが送出される
			フラグ共有 01111110111111001111110....
			                  ~<-　0共有
			このようなプリアンブルが送出されるとＳ／Ｐのリセットが正しくできず
			ＦＳＫのデータの前にゴミデータがのってくる
			処理＞フラグを検出してから１００ｍｓ経過した時点で、ＳＩＯのリセットをおこなう
	]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_RxFskFrameControlTask(UWORD *timer)	/*	フレーム監視用タイマ値	*/
{
	struct	Timer10msData_t Timer3sec;
	struct	Timer10msData_t Timer30sec;

	UBYTE	phase;	/**	タスク遷移状態	*/
	UBYTE	timeoverflg;	/**	タイムオーバフラグ	*/
	UBYTE	rtn;
	UBYTE	rtnmsg;	/**	メッセージ送信設定用	*/
	UBYTE	i;

	timeoverflg = 0;	/**	Ｔ２／Ｔ４タイムオーバフラグ初期化	*/
	phase = PHASE_FLAG_DETECT;

	tskno_RxFlagDetect = 0xffff;
	tskno_RxFcsDetect = 0xffff;

	/**	３０秒タイマタスク起動処理	*/
	/* tskno_Timer30sec = 0xffff; */
	timerID_Timer30sec = 0xff; /* Changed by H.Kubo 1997/07/15 */
	if (RxECM_PixTimeoutFlag == 0) {
		Timer30sec.Time = (FRAME_CONTROL_TIMER/10);	/**	３０秒タイマ値設定	*/
		Timer30sec.SendMBX = mbxno.MDM_TaskSub;	/**	３０秒タイマ、メイルボックス設定	*/
		Timer30sec.ReturnValue = MSG_30SEC_TIME_OVER;	/**	戻り値設定	*/
		CMN_MultiTimer10msStart(&timerID_Timer30sec, &Timer30sec); /* Changed by H.Kubo 1997/07/16 */
		/* cre_tsk(&tskno_Timer30sec, TSK_CMN_MAN_TIMER10MSTASK, &Timer30sec); */
	}

	/**	ＤＭＡ転送完了監視タスク起動	*/
	tskno_RxDMA_TC_Detect = 0xffff;
	cre_tsk(&tskno_RxDMA_TC_Detect, TSK_MDM_RXDMA_TC_DETECTTASK, 0);

	/*	タイマタスク起動処理
	**	命令受信：３秒
	**	応答受信：３秒（自動）
	**	　　　　：４．５秒（手動）
	*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
	if (CHK_DisasterPreventionFaxEnable()) {
		if ((CHK_LongPreamble())) {	/**	ロングプリアンブル対応	*/
			Timer3sec.Time = (10000/10);	/**	１０秒設定	*/
		}
		else {
			Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
		}
	}
	else {
		Timer3sec.Time = (*timer);	/**	Ｔ２／Ｔ４タイマ値設定	*/
	}
#else
	Timer3sec.Time = (*timer);	/**	Ｔ２／Ｔ４タイマ値設定	*/
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

#if defined (KEISATSU) /* 警察FAX 05/09/12 石橋正和 */
	if (FCM_S1_Preamble3S == TRUE) {
		Timer3sec.Time = (10000/10); /* 10s */
	}
#endif
	
	Timer3sec.SendMBX = mbxno.MDM_TaskSub;	/**	Ｔ２／Ｔ４タイマ、メイルボックス設定	*/
	Timer3sec.ReturnValue = MSG_3SEC_TIME_OVER;	/**	戻り値設定	*/
	timerID_Timer3sec = 0xff; /* Changed by H.Kubo 1997/07/16 */
	CMN_MultiTimer10msStart(&timerID_Timer3sec, &Timer3sec); /* Changed by H.Kubo 1997/07/16 */

	/* コントロールチャンネル　リトレイン検出タスク起動
	** By O.Kimoto 1996/05/16
	*/
	tskno_CcRetrainDetect = 0xffff;
	cre_tsk(&tskno_CcRetrainDetect, TSK_MDM_CCRETRAINDETECTTASK, &mbxno.MDM_TaskSub);

	/** フレーム検出処理ループ */
	while (1) {

		/**	フラグ検出処理	*/
		if (phase == PHASE_FLAG_DETECT) {

			/**	フラグ検出	*/
			rtnmsg = RxFskFlagDetect();

			/**	フラグ検出時	*/
			if (rtnmsg == MSG_FLAG_DETECT) {
				phase = PHASE_FRAME_DETECT;
				SaveT30TimingData(SYS_T30_START_TIME);

				if (RxECM_PixTimeoutFlag == 0) {

					/**	タイマタスク終了処理	*/
					if (timerID_Timer3sec != 0xff) {
						CMN_MultiTimer10msStop(&timerID_Timer3sec);
					}

					/**	タイマタスク再起動処理	*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
					if (CHK_DisasterPreventionFaxEnable()) {
						if ((CHK_LongPreamble())) {	/**	ロングプリアンブル対応	*/
							Timer3sec.Time = (10000/10);	/**	１０秒設定	*/
						}
						else {
							Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
						}
					}
					else {
						Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
					}
#else
					if (!(CHK_LongPreamble())) {	/**	ロングプリアンブル対応	*/
						Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
					}
					else {
						Timer3sec.Time = (10000/10);	/**	１０秒設定	*/
					}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

#if defined (KEISATSU) /* 警察FAX 05/09/12 石橋正和 */
					if (FCM_S1_Preamble3S == TRUE) {
						Timer3sec.Time = (10000/10); /* 10s */
					}
#endif

					Timer3sec.SendMBX = mbxno.MDM_TaskSub;	/**	Ｔ２／Ｔ４タイマ、メイルボックス設定	*/
					Timer3sec.ReturnValue = MSG_3SEC_TIME_OVER;	/**	戻り値設定	*/
					timerID_Timer3sec = 0xff; /* Changed by H.Kubo 1997/07/16 */
					CMN_MultiTimer10msStart(&timerID_Timer3sec, &Timer3sec); /* Changed by H.Kubo 1997/07/16 */
				}
			}
			/** コントロールチャンネル　リトレイン検出時 */
			else if (rtnmsg == MSG_CC_RETRAIN_DETECT) {
				rtn = CC_RETRAIN_DETECT;
				break;
			}
			/**	タイムオーバ時	*/
			else {
				rtn = FLAG_TIME_OVER;
				break;
			}
		}
		/**	フレーム検出処理	*/
		else {
			/**	フレーム検出	*/
			rtnmsg = RxFskFrameDetect();

			/**	フレーム検出時	*/
			if (rtnmsg == MSG_FRAME_DETECT) {

				/*
				** R288F VERSION 22P以降の場合
				** 空のモデムバッファに対応
				** by H.Kubo 1998/10/19
				*/
				if (MDM_RxSize[ModemControl.ReadPoint] <= 1) {
				}
				else
				if ((MDM_ModemBuffer[ModemControl.ReadPoint][2] & ~X_BIT) == CRP_F) {
					rtn = CRP_RECEIVE;
					break;
				}
				ModemRxStatus |= (UBYTE)(1<<ModemControl.ReadPoint);

				/*
				** R288F VERSION 22P以降の場合
				** 空のモデムバッファに対応
				** by H.Kubo 1998/10/19
				*/
				if (MDM_RxSize[ModemControl.ReadPoint] <= 1) {
					NextMdmBufReadPointSetExtRom();
				}
				else
				/**	非最終フレーム受信時	*/
				if (MDM_ModemBuffer[ModemControl.ReadPoint][1] == 0x03) {
					phase = PHASE_MULTI_FRAME_DETECT;
					NextMdmBufReadPointSetExtRom();
				}

				/**	最終フレーム受信時	*/
				else if (MDM_ModemBuffer[ModemControl.ReadPoint][1] == 0x13) {
					rtn = FRAME_DETECT;	/**	フレーム受信完了	*/
					/* DMA_RequestMask(MASTER_DMAU, DMA_CH_RX);	*/ /** ゴミデータを受信し続ける対策 By O.K Jan.26,1996 **/
					DMA_RequestMask(DMA_CH_RX);	/** ゴミデータを受信し続ける対策 By O.K Jan.26,1996 **/
					break;
				}
			}
			/**	３秒タイムオーバ時	*/
			else if (rtnmsg == MSG_3SEC_TIME_OVER) {
				if (timeoverflg == YES) {
					rtn = FLAG_TIME_OVER;
					MDM_FskFcsTimeOutFlag = 1;		/* debug 1997/02/08 Y.M */
					break;
				}
				timeoverflg = YES;	/**	再度フレーム検出へ	*/

				/* Ported from Clover by H.Kubo 1998/02/03 */
				/* 1997/10/07 Y.Murata
				 * 受信ﾚﾍﾞﾙが-39dBmで遅延がない時にﾘﾄﾚｰﾝが発生する
				 * ２発目のﾎﾟｽﾄﾒｯｾｰｼﾞとﾘﾄﾚｰﾝがかぶってしまう時がある。
				 * その後、ﾌﾗｸﾞ誤検出して３秒の遅延時間がはたらいて、結果ﾎﾟｽﾄﾒｯｾｰｼﾞが
				 * ６秒後にでてしまう。この３秒の遅延を行うかをどうかのＳＷです。
				*/
				if (SYS_V34ProcedureExecuting()) {
					if (MDM_V34_CC_RetrainTimeCutFlag == 1) {
						rtn = FLAG_TIME_OVER;
						MDM_FskFcsTimeOutFlag = 1;		/* debug 1997/02/08 Y.M */
						break;
					}
				}

				/* 1999/08/07
				 * フレーム受信の最初のタイムアップがきた時に、１フレームも受信していない時はすぐ抜けます。
				 * 
				*/
				for (i = 0; i < MODEM_BUFFER_MAX; i++) {
					if (MDM_RxSize[i]) {
						break;
					}
				}
				if (i >= MODEM_BUFFER_MAX) {
					rtn = FLAG_TIME_OVER;
					MDM_FskFcsTimeOutFlag = 1;
					break;
				}

				/**	タイマタスク終了処理	*/
				if (timerID_Timer3sec != 0xff) {
					CMN_MultiTimer10msStop(&timerID_Timer3sec);
				}

				/**	タイマタスク再起動処理	*/
#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
				if (CHK_DisasterPreventionFaxEnable()) {
					if ((CHK_LongPreamble())) {	/**	ロングプリアンブル対応	*/
						Timer3sec.Time = (10000/10);	/**	１０秒設定	*/
					}
					else {
						Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
					}
				}
				else {
					Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
				}
#else
				Timer3sec.Time = (3300/10);	/**	Ｔ２／Ｔ４タイマ値設定	*/
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

				Timer3sec.SendMBX = mbxno.MDM_TaskSub;	/**	Ｔ２／Ｔ４タイマ、メイルボックス設定	*/
				Timer3sec.ReturnValue = MSG_3SEC_TIME_OVER;	/**	戻り値設定	*/
				timerID_Timer3sec = 0xff; /* Changed by H.Kubo 1997/07/16 */
				CMN_MultiTimer10msStart(&timerID_Timer3sec, &Timer3sec); /* Changed by H.Kubo 1997/07/16 */
			}
			/**	３０秒タイムオーバ時（データ無しの時）	*/
			else if (rtnmsg == MSG_30SEC_TIME_OVER) {
				rtn = TIME_OVER_30SEC;
				break;
			}
			/** コントロールチャンネル　リトレイン検出時 */
			else if (rtnmsg == MSG_CC_RETRAIN_DETECT) {
				rtn = CC_RETRAIN_DETECT;
				break;
			}
			/**	ＤＭＡバッファオーバの時（ごみが続いた時）	*/
			else {
				if (timeoverflg == YES) {	/**	Ｔ２／Ｔ４タイムオーバ済みの時	*/
					rtn = RECEIVE_OVER;
					break;
				}
				else {	/**	Ｔ２／Ｔ４タイム内の時	*/
					phase = PHASE_FLAG_DETECT;	/**	再度フラグ検出処理へ	*/
				}
			}
		}
	}
	/**	ＦＣＳ検出タスク終了	*/
	if (tskno_RxFcsDetect != 0xffff) {
		del_tsk(&tskno_RxFcsDetect);
	}

	/**	フラグ検出タスク終了	*/
	if (tskno_RxFlagDetect != 0xffff) {
		del_tsk(&tskno_RxFlagDetect);
	}

	/*	ＤＭＡ転送完了監視タスク終了	*/
	if (tskno_RxDMA_TC_Detect != 0xffff) {
		del_tsk(&tskno_RxDMA_TC_Detect);	/**	ＤＭＡ転送完了監視タスク終了	*/
	}

	/*	タイマタスク終了	*/
	if (timerID_Timer3sec != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer3sec);
	}

	/*	３０秒タイマタスク終了	*/
	if (timerID_Timer30sec != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer30sec);
	}
	/* コントロールチャンネル　リトレイン検出タスク終了
	** By O.Kimoto 1996/05/16
	*/
	if (tskno_CcRetrainDetect != 0xffff) {
		del_tsk(&tskno_CcRetrainDetect);		/** コントロールチャンネル　リトレイン検出タスク終了処理	*/
	}

	/**	戻り値設定処理	*/
	switch (rtn) {
	case FRAME_DETECT:
		SaveReceivedT30Data();
		SaveT30TimingData(SYS_T30_END_TIME);

		/* コントロールチャンネル中のＦＥＤ　ＯＦＦを検出したかどうかをチェックし（フレーム取りこぼしの可能性がある）
		** その場合は、
		**         桐＋   ＝ ＣＣ＿ＲＥＴＲＡＩＮ
		**         その他 ＝ ＦＳＫ＿ＥＲＲＯＲ
		** となるようにする。
		** By O.Kimoto 1996/09/13
		*/
		if (MDM_FedOffFlag == 1) {		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */
			FrameDetectMessage.Message = MSG_CC_RETRAIN_DETECT;
			MDM_FedOffFlag = 0;
		}
		else {
			FrameDetectMessage.Message = MSG_FSK_RECEIVE;
		}

		MDM_NewT30Status = MODE_RX_FSK;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
		break;
	case CRP_RECEIVE:
		SaveReceivedT30Data();
		SaveT30TimingData(SYS_T30_END_TIME);
		FrameDetectMessage.Message = MSG_FSK_ERROR;
		MDM_NewT30Status = MODE_RX_FSK;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
		break;
	case CC_RETRAIN_DETECT:
		FrameDetectMessage.Message = MSG_CC_RETRAIN_DETECT;
		MDM_NewT30Status = MODE_CC_RETRAIN;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
		break;
	default:
		FrameDetectMessage.Message = MSG_FSK_ERROR;
		MDM_NewT30Status = 0;	/* R288F Internal Monitor By O.Kimoto 1996/06/14 */
		break;
	}

	/**	メッセージ送信	*/
#if defined (KEISATSU) /* 警察FAX 05/09/16 石橋正和 */
	FrameDetectMessage.Item = FROM_MDM_RXFSKFRAMECONTROLTASK;
#endif
	snd_msg(mbxno.MDM_Task, &FrameDetectMessage);
	wai_tsk(0xffff);
}

/*************************************************************************
	module		:[フレーム受信コントロールタスク子タスク終了ルーチン]
	function	:[
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_RxFskFrameControlExit(void)
{
	/**	ＦＣＳ検出タスク終了	*/
	if (tskno_RxFcsDetect != 0xffff) {
		del_tsk(&tskno_RxFcsDetect);
	}

	/**	フラグ検出タスク終了	*/
	if (tskno_RxFlagDetect != 0xffff) {
		del_tsk(&tskno_RxFlagDetect);
	}

	/*	タイマタスク終了	*/
	if (timerID_Timer3sec != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer3sec);
	}

	/*	３０秒タイマタスク終了	*/
	if (timerID_Timer30sec != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer30sec);
	}
	/*	ＤＭＡ転送完了監視タスク終了	*/
	if (tskno_RxDMA_TC_Detect != 0xffff) {
		del_tsk(&tskno_RxDMA_TC_Detect);	/**	ＤＭＡ転送完了監視タスク終了	*/
	}

	/* 1997/02/25 Y.Murata
	 * コントロールチャンネル　リトレイン検出タスク終了
	*/
	if (tskno_CcRetrainDetect != 0xffff) {
		del_tsk(&tskno_CcRetrainDetect);		/** コントロールチャンネル　リトレイン検出タスク終了処理	*/
	}

	/* 自タスクの終了 */
	exi_tsk();
}

/*************************************************************************
	module		:[ＦＳＫ受信フラグ検出]
	function	:[
		1.フラグ検出タスク起動
		2.メッセージ受信処理
		3.フラグ検出タスク終了
	]
	return		:[
		MSG_FLAG_DETECT:		フラグ検出タスクより
		MSG_3SEC_TIME_OVER:		タイマタスクより
		MSG_30SEC_TIME_OVER:	タイマタスクより
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[
		フレーム受信コントロールタスク
	]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	RxFskFlagDetect(void)
{
	MESSAGE_t	*MDM_Msg;

	/*	フラグ検出タスク起動	*/
	tskno_RxFlagDetect = 0xffff;
	cre_tsk(&tskno_RxFlagDetect, TSK_MDM_FLAGDETECTTASK, &mbxno.MDM_TaskSub);

	/*	メッセージ受信処理
	** 1.MSG_FLAG_DETECT:		フラグ検出タスクより
	** 2.MSG_3SEC_TIME_OVER:	タイマタスクより
	** 3.MSG_30SEC_TIME_OVER:	タイマタスクより
	** 4.MSG_CC_RETRAIN_DETECT:	コントロールチャンネル　リトレイン検出タスクより
	*/
	do {
		rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);
	} while (!((MDM_Msg->Message == MSG_FLAG_DETECT) ||
	           (MDM_Msg->Message == MSG_3SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_30SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));	/* CC Retrain By O.Kimoto 1996/05/16 */

	/*	フラグ検出タスク終了	*/
	if (tskno_RxFlagDetect != 0xffff) {
		del_tsk(&tskno_RxFlagDetect);
	}

	/*	戻り値設定	*/
	return((UBYTE)MDM_Msg->Message);
}


/*************************************************************************
	module		:[フラグ検出タスク]
	function	:[
		1.モデム割り込みより、フラグ検出イベント待ち
		2.フレーム受信コントロールタスクへ、メッセージ送信
	]
	return		:[
		なし
	]
	common		:[
		ModemMessage
		ModemControl
		ModemInterruptFlag
		HighSpeedCheckFlag
	]
	condition	:[]
	comment		:[
		フラグ検出タスク
	]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_FlagDetectTask(UWORD *mbx_no)
{
	UWORD	v21filter_on_cnt;
	UWORD	v21filter_off_cnt;
	UBYTE	v21_filter_on;

	CMN_DisableInterrupt();	/**	割り込み禁止	*/ /* 1997/02/03 Y.Murata */
	ModemControl.Status &= ~STAT_FCSDET;
	ModemControl.Status |= STAT_FLGDET;
	ModemInterruptFlag = 0;	/**	モデム割り込みフラグ初期化	*/ /* 1997/02/03 Y.Murata */
	CMN_EnableInterrupt();	/**	割り込み許可	*/ /* 1997/02/03 Y.Murata */

	if ((SYS_V34ProcedureExecuting() == 0) && (HighSpeedCheckFlag == 1)) {
		v21filter_on_cnt = 0;
		v21filter_off_cnt = 0;
		v21_filter_on = 0;
		while (1) {
			/* フィルター */
			v21_filter_on = MDM_GetIO(POS_TONEB);

			if (v21_filter_on) {
				v21filter_on_cnt++;
				v21filter_off_cnt = 0;
			}
			else {
				v21filter_off_cnt++;
				if (v21filter_off_cnt > 3) {
					v21filter_on_cnt = 0;
				}
			}

/*
** [FX Able3121からV17で複数ページ受信したとき、高低速識別で、高速信号がきているのに、
** 低速信号と認識し通信エラーとなる不具合(FM336モデムの機種は対象。R288Fモデムの機種では発生していない。)]
**
** TONE Bフィルタはなぜかここにくる前(無音期間やEPトーン中も)から反応したままとなっているため、
** CFRとPIX間の無音期間が短いと、110ms以上反応したままとなり、低速信号のフラグ検知のパスを通ってしまう。
** Able3121はCFRと1枚目PIXの間の無音期間は400ms以上あるが、CFRと2枚目PIXの間の無音期間は75ms程度と短い。
** Paris同士ではCFRとPIXの間は550ms以上あいているため問題ない。ちなみに、V17通信ではEPトーンを高速信号と
** 誤検出しているものと思われるが結果的にOKなので、対策しない。
** 対策としては、低速信号のプリアンブル1秒なので、閾値時間を伸ばすだけ。
** 
** 2000/12/29 by K.Okada -> 2001/01/05 Y.Murata
*/
#if 0
**			if (v21filter_on_cnt > 10) {		/* 100ms以上 */
**				break;
**			}
#endif
			if (v21filter_on_cnt > 30) {		/* 300ms以上 */
				break;
			}
			wai_tsk(1);		/* 10ms */
		}
	}
	else {

		/*	イベント待ち処理
		**	EVT_RX_FLG_DETECT:	モデム割り込み監視タスクより
		*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		if (ModemInterruptFlag == 0) {	/**	モデム割り込み未発生の時	*/
			wai_evt(EVT_RX_FLG_DETECT);	/**	モデム割り込み待ち	*/
		}
		ModemInterruptFlag = 0;	/**	モデム割り込みフラグ初期化	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/
	}

	/*	メッセージ送信処理
	** 1.MSG_FLAG_DETECT:	フレーム受信コントロールタスクへ
	*/
	FlagDetectMessage.Message = MSG_FLAG_DETECT;
	snd_msg(*mbx_no, &FlagDetectMessage);

	/*	自タスク無限待ち	*/
	wai_tsk(0xffff);

}


/*************************************************************************
	module		:[ＦＳＫ受信フレーム検出]
	function	:[
		1.ＤＭＡ転送完了監視タスク起動
		2.ＦＣＳ検出タスク起動
		3.メッセージ受信実行
		4.ＤＭＡ転送完了監視タスク終了
		5.ＦＣＳ検出タスク終了
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[]
	comment		:[
		フレーム受信コントロールタスク
	]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	RxFskFrameDetect(void)
{
	MESSAGE_t	*MDM_Msg;

	/**	ＦＣＳ検出タスク起動	*/
	tskno_RxFcsDetect = 0xffff;
	cre_tsk(&tskno_RxFcsDetect, TSK_MDM_FCSDETECTTASK, &mbxno.MDM_TaskSub);

	/*	メッセージ受信
	** 1.MSG_DMA_STOP:			ＤＭＡ転送終了監視タスクより
	** 2.MSG_FRAME_DETECT:		フレーム検出より
	** 3.MSG_3SEC_TIME_OVER:	タイマタスクより
	** 4.MSG_30SEC_TIME_OVER:	タイマタスクより
	** 5.MSG_CC_RETRAIN_DETECT:	コントロールチャンネル　リトレイン検出タスクより
	*/
	do {
		rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);
	} while (!((MDM_Msg->Message == MSG_DMA_STOP) ||
	           (MDM_Msg->Message == MSG_FRAME_DETECT) ||
	           (MDM_Msg->Message == MSG_3SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_MUTE_ON_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_30SEC_TIME_OVER) ||
	           (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));	/* CC Retrain By O.Kimoto 1996/05/16 */

	/**	ＦＣＳ検出タスク終了	*/
	if (tskno_RxFcsDetect != 0xffff) {
		del_tsk(&tskno_RxFcsDetect);
	}

	/**	戻り値設定	*/
	return((UBYTE)MDM_Msg->Message);
}


/*************************************************************************
	module		:[ＦＣＳ検出タスク]
	function	:[
		1.該当フレーム受信待ち処理
		2.フレーム受信コントロールタスクへ、メッセージ送信
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemRxStatus
		ModemMessage
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_FcsDetectTask(UWORD *mbx_no)
{
	UBYTE	wrkmsk;
	UWORD	tmout;

	/**	読み出しフレームＢＩＴ設定	*/
	wrkmsk = (UBYTE)(1<<ModemControl.ReadPoint);

	/**	該当フレーム受信待ち処理	*/
	tmout = RX_FRAME_WAIT;
	while (ModemRxStatus & wrkmsk) {
		wai_tsk(tmout/10);
	}

	/*	メッセージ送信処理
	** 1.MSG_FRAME_DETECT:	フレーム受信コントロールタスクへ
	*/
	FcsDetectMessage.Message = MSG_FRAME_DETECT;
	snd_msg(*mbx_no, &FcsDetectMessage);

	/**	自タスク無限待ち	*/
	wai_tsk(0xffff);
}

/*************************************************************************
	module		:[ＦＳＫ送出時間設定]
	function	:[
		1.引き数のデータ量を送出するのにかかる（ＦＳＫ送信３００ｂｐｓ）時間を設定する
		2.１の位は切り上げ処理を行う（１０ｍｓタイマ用）
	]
	return		:[
		送出時間(ms)
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[曽根岡拓]
*************************************************************************/
UWORD	SetFskTime(UWORD	datacnt)
{
	UWORD	fsktime;

	/*	送出時間設定／小数点以下切り上げ
	**	送出バイト数		実測値
	**	３　ｂｙｔｅ		147 -168ms  -> 198ms
	**	３５ｂｙｔｅ		1157-1187ms -> 1200ms
	**	(1200-198)/(35-3)=31.3 1200-(31.3*35)=104
	*/
	fsktime = (datacnt*313)/10 + 104;

	return(fsktime);
}



/*************************************************************************
	module		:[コントロールチャンネル　リトレイン検出タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void 	MDM_CcRetrainDetectTask(UWORD *){}]
	date		:[1996/05/16]
	author		:[木元修]
*************************************************************************/
void 	MDM_CcRetrainDetectTask(UWORD *mbx_no)
{
	MESSAGE_t MDM_Msg;

	/*	イベント待ち処理 */
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	if (ControlChannelRetrainFlag == 0) {	/**	モデム割り込み未発生の時	*/
		wai_evt(EVT_MDM_CC_RETRAIN);	/**	モデム割り込み待ち	*/
	}
	ControlChannelRetrainFlag = 0;	/**	モデム割り込みフラグ初期化	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/*	メッセージ送信処理(フレーム受信コントロールタスクへ) */
	MDM_Msg.Message = MSG_CC_RETRAIN_DETECT;
	snd_msg(*mbx_no, &MDM_Msg);

	/*	自タスク無限待ち	*/
	wai_tsk(0xffff);
}




/*************************************************************************
	module		:[コンロトールチャンネルリトレーン待ち]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void  MDM_CheckCcRetrain(void){}]
	date		:[1996/09/20]
	author		:[木元修]
*************************************************************************/
void  MDM_CheckCcRetrain(void)
{
	UWORD	timer30sec;
	
	timer30sec = 0;
	MDM_CarrierDropoutFlag = 0;
	MDM_CarrierDropoutTimer = 0;

	if (SYS_V34ProcedureExecuting()) {	/** Ｖ．３４ばらば */
		while(!(MDM_GetIO(POS_CTS) & (MDM_GetIO(POS_SECRXB) == 0x84))) {	/**	ＣＴＳビットがＯＦＦの時	*/
			wai_tsk(10/10); /** １０ｍｓウエイトします。 */
			timer30sec ++;

			if (MDM_RetrainFirstCCTrainFlag == 1) {
				MDM_RetrainFirstCCTrainFlag = 0;
				timer30sec = 0;
			}

			if (ControlChannelRetrainFlag == 1) {
				ControlChannelRetrainFlag = 0;
				timer30sec = 0;
			}
			
			if ((timer30sec >= 30000/10) 
				|| ( MDM_FedOffFlag == 0x01)
				|| ( MDM_FedOffFlag == 0x02)) {
				MDM_ClearToSendAbort = TRUE;
				MDM_CarrierDropoutFlag = 0xff;
				break;
			}
		}
	}
}


