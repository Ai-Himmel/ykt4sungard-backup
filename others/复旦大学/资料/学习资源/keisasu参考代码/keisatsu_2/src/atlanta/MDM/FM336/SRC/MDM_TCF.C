/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_tcf.c                                                 */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ＴＣＦ送受信関連処理                                      */
/*  修正履歴     :                                                           */
/*	keyword			:[MDM]                                                   */
/*	machine			:[SH7043,V53]                                            */
/*	language		:[MS-C(Ver.6.0)]                                         */
/*---------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"	/* Add for EQM By O.K Feb.22,1996 */
#include "\src\atlanta\sh7043\define\def_mbxn.h"	/* Add for EQM By O.K Feb.22,1996 */
#include "\src\atlanta\define\fcm_def.h"		/* 1997/06/23 H. Kubo */
#include "\src\atlanta\define\param.h"		/* 1997/01/09 Y.Murata */
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1997/10/08 */
#include "\src\atlanta\define\mnt_sw.h" /* 1999/09/15 by K.Okada */

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"		/* 1996/10/23 Y.M */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\fcm_data.h"		/* Add for EQM By O.K Feb.22,1996 */
#include "\src\atlanta\ext_v\bkupram.h"		/* 1996/07/17 Y.Murata */

UWORD	tcf_cnt = 0;
UWORD	DBG_EqmAraBias = 0;	/* For Debug by O.Kimoto 1996/04/09 */

/*************************************************************************
	module		:[トレーニング送信]
	function	:[
		1.　送信速度に応じて、ゼロ送出バイト数を設定、送出する
	]
	return		:[なし]
	common		:[
		ModemControl
		MDM_ModemBuffer
		ModemBlock
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_TransmitTCF(UBYTE ){}]
	date		:[1993/12/07]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_TransmitTCF(
		UBYTE speed)	/*	モデムタイプ・スピード	*/
{
	UWORD	tran_cnt;	/*	全送出データ数	*/
	UWORD	w_cnt;	/*	書き込みデータ数	*/
	UWORD	time;	/*	トレーニング送出時間	*/
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
	BOOL brts; /* RTSを送出するか */
	
	brts = TRUE;
#endif

	InitializeModemWork();

	time = TRAINING_TIME;	/**	トレーニング送出時間設定	*/
	ModemTypeSet(speed);	/**	モデムタイプ、速度設定	*/
	ModemBlock.Training = TRAINING_LONG;	/**	ロングトレーニング設定	*/
	ModemBlock.Mode = MODE_TX_TCF;	/**	交信モードを送信Ｇ３に設定	*/

	tran_cnt = SetTransmitCount(time);	/**	ゼロ送出バイト数設定　*/

	/* 1997/01/30 Y.Murata */
	MDM_SetIO(POS_STRN,OFF);

	TxG3_Open();	/**	トレーニング送信モデムオープン	*/

	MDM_NewT30Status = MODE_TX_TCF;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
	do {
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
		w_cnt = GetCount(tran_cnt, MDM_ModemDmaSize);	/**	書き込みデータ数設定	*//** 256 Bytes **/
		if (tran_cnt <= MDM_ModemDmaSize) {	/**	最終データ書き込み時	*//** 256 Bytes **/
			ModemBlock.Chain = SET_COMPL; /* 送信データセット完了		*/
		}
#else
		w_cnt = GetCount(tran_cnt, MODEM_DMA_SIZE);	/**	書き込みデータ数設定	*//** 256 Bytes **/
		if (tran_cnt <= MODEM_DMA_SIZE) {	/**	最終データ書き込み時	*//** 256 Bytes **/
			ModemBlock.Chain = SET_COMPL; /* 送信データセット完了		*/
		}
#endif
		/*------------------------------------------*/
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		/*------------------------------------------*/
		while (ModemControl.UsedCount == MODEM_BUFFER_MAX) {	/**	モデムバッファ使用本数が８本の時	*/
			wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
		}
		
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
		if ((FCM_S1_Scramble == TRUE) && (DBG_G3_TCF_OriginalPosition == 0)) {
			TxG3_WriteWithRTS_Sent(&ModemZeroBuffer[0], w_cnt, brts);	/**	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録）	*/
			brts = FALSE;
		}
		else {
			TxG3_Write(&ModemZeroBuffer[0], w_cnt);	/**	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録）	*/
		}
#else
		TxG3_Write(&ModemZeroBuffer[0], w_cnt);	/**	Ｇ３送信モデムライト（送出モデムバッファ先頭アドレス／データ数登録）	*/
#endif
		
		tran_cnt = tran_cnt-w_cnt;	/**	送出バイト数更新	*/
	} while (tran_cnt);	/**	送出バイト数が０になるまで	*/
	TxG3_Close();	/**	トレーニング送信モデムクローズ	*/
}


/*************************************************************************
	module		:[Ｇ３送信モデムスタート]
	function	:[
		1.モデム内部コントロールの読みだし位置に示される、バッファアドレスとデータ数で
		, モデムＤＭＡ設定する
		2.モデムＤＭＡマスク解除する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far TxTcfStart(void){}]
	date		:[1993/12/21]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  TxTcfStart(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	/*--------------------------*/
	/*	   モデムＤＭＡ設定	    */
	/*--------------------------*/
	ModemControl.Status |= (STAT_ACT + STAT_FRSTON);
	ModemWriteDMA_Data.Channel		= DMA_CH_TX;

	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	絶対アドレスに変換	*/

	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount; /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

	/*------------------------------*/
	/*	オートイニシャライズ許可	*/
	/*------------------------------*/
	DMA_AutoInitializeEnable(ModemWriteDMA_Data.Channel);	/** DMAU AutoInitializeMode Enable */

	/* Added by H.Kubo 1997/10/08
	**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	/*----------------------------------*/
	/*	モデムＶ５３ＤＭＡマスク解除	*/
	/*----------------------------------*/
	DMA_RequestEnable(ModemWriteDMA_Data.Channel);
}


/*************************************************************************
	module		:[トレーニング受信]
	function	:[
		1.
	]
	return		:[
		OK:	トレーニング受信良好
		NG:	フォールバック必要
	]
	common		:[]
	condition	:[]
	comment		:[
		Feb.06.1995  竹内
		ＥＹＥ－Ｑの値をＴ．３０バッファにセットする処理を
		フェーズＢから移動
	]
	date		:[1994/01/17]
	update		:[1996/03/01]
	author		:[曽根岡拓、木元修]
*************************************************************************/
UBYTE		MDM_ReceiveTCF(
		UBYTE speed)	/*	モデムタイプ・スピード	*/
{
	MESSAGE_t	*MDM_Msg;

	struct	Timer10msData_t TimerEYE_Q;
	struct	Timer10msData_t TimerTCF;
	struct	Timer10msData_t TimerTCF_End;
	struct	Timer10msData_t TimerTCF_ReadTime;

	UWORD	cnt;
	UWORD	tcf_time;
	UWORD	tcf_cnt_init;
	UBYTE	tcf_flg;
	UBYTE	eye_q_ok;
	UBYTE	rtn;
	UBYTE	*rd_bytepnt;	/**	モデムバッファリードポインタ	*/
	UBYTE	correct_readpoint;

	UBYTE	eyeq_buf[6];	/* ＥＹＥ－Ｑ用バッファ *//* 4->6 1997/01/28 */

	eye_q_ok = 0;
	tcf_flg = 0;
	BackUpEYE_Slice = 0;	/* 1996/10/25 Y.M */
	correct_readpoint = 1;

	InitializeModemWork();
	ModemTypeSet( speed );	/**	モデムタイプ設定	*/

	ModemBlock.Training = TRAINING_LONG;
	ModemBlock.Mode = MODE_RX_TCF;	/**	交信モード設定	*/ /* add 1996/10/18 Y.Murata */

	tcf_time = CHK_UNI_TCF_CheckTime();	/**	ゼロチェック時間設定	*/ /* Modified by H.Kubo 1997/07/08 */

	if (tcf_time == 0) {
		tcf_time = 100;
	}

	tcf_cnt_init = SetTransmitCount( tcf_time );	/**	ゼロチェックサイズ設定	*/
	tcf_cnt = tcf_cnt_init;

	RxG3_Open();
	MDM_NewT30Status = MODE_RX_TCF;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

	/** Advice for Rockwell by O.Kimoto 1997/01/28 */
	MDM_SetIO( POS_STRN, OFF );


	/**	トレーニング検出処理	*/
	if ( CheckTraining( 3500 ) == NO ) {
		RxG3_Close();
		return ( NG );
	}
	ModemWaitStatus = 0;

#if 0
/* 1997/01/08 Y.Murata
*  ＡＮＺＵ仕様で、Ｖ１７ー１４０００の受信ができない、EYEﾊﾟﾀｰﾝがみだれるため
*  トレーニングでは、RTDIS対策及びＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策
*  は、行いません。（桐＋では大丈夫だったが、なぜかアンズではダメだった）
*
*	if (!(SYS_V34ProcedureExecuting())) {
*		if (((inp(MDM_REG_0A_PORT) & IO_BIT_PNSUC) == IO_BIT_PNSUC)
*			&& ((inp(MDM_REG_0F_PORT) & IO_BIT_RLSD) == IO_BIT_RLSD)) {
*			MDM_SetIO(POS_RTDIS,ON);
*			MDM_PixStartFlag = 1;
*			MDM_AlreadyRtdisSetFlag = 1;
*		}
*		else {
*			MDM_PixStartFlag = 1;
*			MDM_AlreadyRtdisSetFlag = 0;
*		}
*	}
*/
#endif

	/* 受信データ転送中	*/
	if (CheckRLSD(3000) == NO) {
		RxG3_Close();
		return (NG);
	}
	ModemWaitStatus = 0;

	/* ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ by O.Kimoto 1997/01/28 */
	if (ModemBlock.Type	== TYPE_V17) {	/**	モデムタイプ　Ｖ１７設定	*/
		MDM_SetIO(POS_STRN,ON);
		/*MDM_SetIO(POS_EQFZ,ON); 1997/01/28 Y.M */
	}

	/* ＥＱＭ値リードタスク起動 1996/10/23 Y.Murata */
	MDM_RlsdTurnOffCheckFlag = TRUE;
	MDM_RlsdTurnOnFlag = 0;
	tskno_EyeQualityMonitor = 0xffff;
	cre_tsk(&tskno_EyeQualityMonitor,TSK_MDM_READEQMVALUETASK,0);

	/**	１秒タイマ設定タイマタスク起動（ＥＹＥ　Ｑｕａｌｉｔｙ用）	*/
	TimerEYE_Q.Time = (EYE_Q_TIME/10);
	TimerEYE_Q.SendMBX = mbxno.MDM_Task;
	TimerEYE_Q.ReturnValue = MSG_EYE_Q_TIME;
	tskno_TimerEYE_Q = 0xffff;
	cre_tsk(&tskno_TimerEYE_Q, TSK_CMN_MAN_TIMER10MSTASK, &TimerEYE_Q);

	/**	１．５秒タイマ設定タイマタスク起動（ＴＣＦ時間用）	*/
	TimerTCF.Time = (TCF_TIME/10);
	TimerTCF.SendMBX = mbxno.MDM_Task;
	TimerTCF.ReturnValue = MSG_TCF_TIME;
	tskno_TimerTCF = 0xffff;
	cre_tsk(&tskno_TimerTCF, TSK_CMN_MAN_TIMER10MSTASK, &TimerTCF);

	/**	２．０秒タイマ設定タイマタスク起動（ＴＣＦ　ＥＮＤ時間）	*/
	TimerTCF_End.Time = (TCF_END_TIME/10);
	TimerTCF_End.SendMBX = mbxno.MDM_Task;
	TimerTCF_End.ReturnValue = MSG_TCF_END_TIME;
	tskno_TimerTCF_End = 0xffff;
	cre_tsk(&tskno_TimerTCF_End, TSK_CMN_MAN_TIMER10MSTASK, &TimerTCF_End);

	/**	１０ｍｓタイマ設定タイマタスク起動	*/
	TimerTCF_ReadTime.Time = (TCF_READ_TIME/10);
	TimerTCF_ReadTime.SendMBX = mbxno.MDM_Task;
	TimerTCF_ReadTime.ReturnValue = MSG_TCF_READ_TIME;
	tskno_TimerTCF_ReadTime = 0xffff;
	cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &TimerTCF_ReadTime);
	while (1) {

		/**	メッセージ受信処理
		 *	1.MSG_EYE_Q_TIME:	タイマタスクより
		 *	2.MSG_TCF_TIME:		タイマタスクより
		 *	3.MSG_TCF_END:		タイマタスクより
		 *	4.MSG_TCF_READ_TIME	タイマタスクより
		 */
		do {
			rcv_msg(mbxno.MDM_Task, &MDM_Msg);
		} while (!((MDM_Msg->Message == MSG_EYE_Q_TIME) ||
		           (MDM_Msg->Message == MSG_TCF_TIME) ||
		           (MDM_Msg->Message == MSG_TCF_END_TIME) ||
		           (MDM_Msg->Message == MSG_TCF_READ_TIME) ||
		           (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS)));

		/*	トレーニング　ゼロチェック処理	*/
		if (MDM_Msg->Message == MSG_TCF_READ_TIME) {	/**	１０ｍｓタイムアップ時	*/
			if (tskno_TimerTCF_ReadTime != 0xffff) {
				del_tsk(&tskno_TimerTCF_ReadTime);	/**	１０ｍｓタイムアップタイマタスク終了	*/
			}
			/* ICHOU修正 by T.Soneoka 1997/01/28 */
			/* モデムリードするときに既にモデムバッファ８本分以上ライトされていることがある為
			** そのときは、リードポイントをライトポイントの次に再セットする
			** リードポイント補正は一回だけ行う
			*/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
			if ((ModemControl.UsedCount >= (UBYTE) (MODEM_BUFFER_MAX - MDM_ModemBufferFirstPoint)) && (correct_readpoint)) {
#else
			if ((ModemControl.UsedCount >= MODEM_BUFFER_MAX) && (correct_readpoint)) {
#endif
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (ModemControl.WritePoint == (MODEM_BUFFER_MAX-1)) {
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
					ModemControl.ReadPoint = MDM_ModemBufferFirstPoint;
#else
					ModemControl.ReadPoint = 0;
#endif
				}
				else {
					ModemControl.ReadPoint = (UBYTE)(ModemControl.WritePoint + 1);
				}
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			correct_readpoint = 0;

			if (RxG3_Read() == RCV_BLOCK){	/**	モデムバッファ読み出し／１ブロック受信完了時	*/
				rd_bytepnt = &MDM_ModemBuffer[ModemControl.ReadPoint][0];	/**	読みだしバッファ先頭アドレス取得	*/
				NextMdmBufReadPointSetExtRom();

#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
				for (cnt = 0; cnt < MDM_ModemDmaSize; cnt++) {/** 256 Bytes **/
#else
				for (cnt = 0; cnt < MODEM_DMA_SIZE; cnt++) {/** 256 Bytes **/
#endif
					if (*rd_bytepnt++ == 0x00) {	/**	バッファが０の時	*/
						if (--tcf_cnt == 0) {	/**	０チェックカウンタ減算／０チェックカウンタが０の時	*/
							tcf_flg = 1;	/**	０チェック終了フラグセット	*/

							/* 1997/10/23 Y.Murata
							 * イコライザーホールドはゼロチェックとＥＹＥＱチェックがＯＫになってからします。
							 * 先にＥＹＥＱチェックがＯＫになりゼロチェックが終わってない時にイコライザーをホールドすると
							 * ゼロチェック時にゴミが入ってしまいます。
							*/
							if (eye_q_ok) {
								EqualizerHoldOn();
							}

							break;
						}
					}
					else {	/**	バッファが０以外の時	*/
						tcf_cnt = tcf_cnt_init;
					}
				}
			}
			else {	/**	ストップＳｗ処理	*/
				break;
			}
			/*	次ブロック受信処理	*/
			if (tcf_flg != 1) {	/**	０チェック継続する時	*/
				/*	１０ｍｓタイマ設定タイマタスク起動	*/
				tskno_TimerTCF_ReadTime = 0xffff;
				cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &TimerTCF_ReadTime);	/**	１０ｍｓタイマ設定タイマタスク起動	*/
			}
			continue;
		}
		/*	ＥＹＥ＿Ｑチェック処理	*/
		else if (MDM_Msg->Message == MSG_EYE_Q_TIME) {	/**	１秒タイムアップ時	*/
			if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
				if (CHK_V17EqualizerHold()) {	/* 1997/02/05 Y.M */
					EqualizerHoldOn();	/**	イコライザホールド設定	*/
				}
			}
			if (CheckSlice(speed) == YES) {
				eye_q_ok = 1;	/**	ＥＹＥチェックフラグ設定	*/

				/* 1997/02/25 Y.Murata
				 * 良好なＥＹＥＱ値が確定してから、ＰＩＸの頭まで
				 * イコライザーをホールドします。
				 * Ｖ２９の７２００ｂｐｓのＥＹＥ発散対策。
				*/
				/* 1997/10/23 Y.Murata
				 * イコライザーホールドはゼロチェックとＥＹＥＱチェックがＯＫになってからします。
				 * 先にＥＹＥＱチェックがＯＫになりゼロチェックが終わってない時にイコライザーをホールドすると
				 * ゼロチェック時にゴミが入ってしまいます。
				 *EqualizerHoldOn();
				*/
				if (tcf_flg) {
					EqualizerHoldOn();
				}
			}
			continue;
		}
		/*	ＲＬＳＤ　ＯＦＦ検出開始設定	*/
		else if (MDM_Msg->Message == MSG_TCF_TIME) {	/**	１．５秒タイムアップ時	*/

			/*	モデムステータス監視タスク起動	*/
			tskno_ModemStatusCheck = 0xffff;
			ModemStatusFlag = 0;
			ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_RLSDOFF);	/**	ＲＬＳＤ　ＯＦＦチェック設定	*/
			cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task);	/**	モデムステータス監視タスク起動	*/
		}

		/*	ＲＬＳＤ　ＯＦＦ検出時	*/
		else if (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) {	/**	ＲＬＳＤ　ＯＦＦ検出時	*/
			/*	バッファにトレーニングデータが残っている時（念のため）	*/
			break;
		}

		/*	（ＴＣＦ　ＥＮＤ時間）トレーニング監視終了時間	*/
		else {	/**	２秒タイムタップ時	*/
			break;
		}
	}
	if (eye_q_ok && tcf_flg) {
		rtn = OK;
	}
	else {
		rtn = NG;
	}
	if (tskno_TimerTCF_ReadTime != 0xffff) {
		del_tsk(&tskno_TimerTCF_ReadTime);
	}

	/**	１秒タイマ設定タイマタスク終了	*/
	if (tskno_TimerEYE_Q != 0xffff) {
		del_tsk(&tskno_TimerEYE_Q);
	}

	/**	１．５秒タイマ設定タイマタスク終了（ＴＣＦ時間用）	*/
	if (tskno_TimerTCF != 0xffff) {
		del_tsk(&tskno_TimerTCF);
	}

	/**	２．０秒タイマ設定タイマタスク終了（ＴＣＦ　ＥＮＤ時間）	*/
	if (tskno_TimerTCF_End != 0xffff) {
		del_tsk(&tskno_TimerTCF_End);
	}

	/**	モデムステータス監視タスク	*/
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck);
	}
	ModemStatusFlag = 0;

	/* ＥＱＭ値リードタスク 1996/10/23 Y.Murata */
	MDM_RlsdTurnOffCheckFlag = FALSE;
	if (tskno_EyeQualityMonitor != 0xffff) {
		del_tsk(&tskno_EyeQualityMonitor);
	}

	/* ＴＣＦモデムクローズ処理	*/
	RxG3_Close();

	eyeq_buf[0] = (UBYTE)(SYS_EyeQ_Level & 0x00FF);
	eyeq_buf[1] = (UBYTE)((SYS_EyeQ_Level & 0xFF00) >> 8);
/* debug 比較したﾃｰﾌﾞﾙ値の載せる */
	eyeq_buf[2] = (UBYTE)(BackUpEYE_Slice & 0x00FF);		/* add 1996/10/25 Y.M */
	eyeq_buf[3] = (UBYTE)((BackUpEYE_Slice & 0xFF00) >> 8);	/* add 1996/10/25 Y.M */
/* debug receiveLevel */
	eyeq_buf[4] = (UBYTE)(MDM_V21MeasureReceiveLevel & 0x00FF);		/* add 1997/01/28 Y.M */
	eyeq_buf[5] = (UBYTE)((MDM_V21MeasureReceiveLevel & 0xFF00) >> 8);	/* add 1997/01/28 Y.M */

	SaveT30Data(SYS_T30_RX_TCF, &eyeq_buf[0], 6);	/* 2->4->6 1997/01/28 1996/10/25 Y.M */
	SaveT30TimingData(SYS_T30_END_TIME);

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* 防災FAX対応 by Y.Kano 2004/08/19 */
	if (CHK_DisasterPreventionFaxEnable()) {
		rtn = OK;
	}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

#if 0
/* 1997/01/08 Y.Murata
*  ＡＮＺＵ仕様で、Ｖ１７ー１４０００の受信ができない、EYEﾊﾟﾀｰﾝがみだれるため
*  トレーニングでは、RTDIS対策及びＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策
*  は、行いません。（桐＋では大丈夫だったが、なぜかアンズではダメだった）
*
*	if (!(SYS_V34ProcedureExecuting())) {
*		MDM_SetIO(POS_RTDIS,OFF);
*		MDM_PixStartFlag = 0;
*		MDM_AlreadyRtdisSetFlag = 0;
*
*		* 以下はＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策です。
*		** By O.Kimoto 1996/12/18
*		*
*		DspRamAccessWriteMethod1(0x4803,0x10,0xEF);
*	}
*/
#endif
	return (rtn);
}


/*************************************************************************
	module		:[トレーニング検出]
	function	:[
		1.指定時間、ＴＲＤＥＴを検出する

	]
	return		:[
		YES:	トレーニング検出
		NO:		タイムオーバ
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/18]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		CheckTraining(UWORD	timer)
{

	MESSAGE_t	*MDM_Msg;
	struct	Timer10msData_t TimerTrainingDetect;
	UBYTE	rtn;

	UBYTE timerID_TimerTrainingDetect;

	/* モデムステータス監視タスク起動	*/
	tskno_ModemStatusCheck = 0xffff;
	CMN_DisableInterrupt();		/* 1997/02/03 Y.Murata */
	ModemStatusFlag = 0;
	ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_TRDETON);	/**	ＴＲＤＥＴチェック指定	*/
	CMN_EnableInterrupt();		/* 1997/02/03 Y.Murata */

	cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task);	/**	モデムステータス監視タスク起動	*/

	/* トレーニング検出タイマ起動	*/
	TimerTrainingDetect.Time = (timer/10);
	TimerTrainingDetect.SendMBX = mbxno.MDM_Task;
	TimerTrainingDetect.ReturnValue = MSG_TRAINING_DETECT_END_TIME;
	timerID_TimerTrainingDetect = 0xff; /* Changed by H.Kubo 1997/07/17 */
	CMN_MultiTimer10msStart(&timerID_TimerTrainingDetect, &TimerTrainingDetect);	/**	タイマ起動	*/

	/*	メッセージ受信
	 *	1.MSG_ENABLE_MODEM_STATUS:	モデムステータス監視タスクより
	 *	2.MSG_TRAINING_DETECT_END:	タイマタスクより
	 */
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);
	} while (!((MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) ||
	           (MDM_Msg->Message == MSG_TRAINING_DETECT_END_TIME)));

	ModemWaitStatus = 0;

	/**	戻り値設定	*/
	if (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) {	/**	メッセージ受信内容がトレーニング検出時	*/
		/* Murata M700 からの V27ter 2400bps 受信では PNSUC が立って処理がここまで来た後、
		** 再び PNDET が立って RLSD が立たない。仕方が無いのでここで RTDIS を立てて
		** トレーニング受信状態にならないようにします。
		** by H.Kubo 1999/03/15 */
		/* 20P でやると後で DSP RAM をアクセスするときに MEACC が落ちるのを待ってループするので、
		** 26P 以降だけの処理とします。 by H.Kubo 1999/04/13 */
		if (SYS_ModemVersion >= MDM_L6713_26P) {
			if (ModemBlock.Config == BPS2400_V27) {
				MDM_SetIO(POS_RTDIS, ON); /* トレーニング状態になることを禁止します。 */
			}
		}
		rtn = YES;
	}
	else{
		rtn = NO;
	}

	/**	モデムステータス監視タスク終了	*/
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck);
	}
	ModemStatusFlag = 0;

	/**	タイマ終了	*/
	if (timerID_TimerTrainingDetect != 0xff) {
		CMN_MultiTimer10msStop(&timerID_TimerTrainingDetect);
	}
	return (rtn);
}


/*************************************************************************
	module		:[ＲＬＳＤチェック]
	function	:[
		1.
	]
	return		:[
		YES:	RLSD ON検出
		NO:		タイムオーバ
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/18]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE		CheckRLSD(
		UWORD	timer)			/*	ＴＣＦ受信時間	*/
{
	MESSAGE_t	*MDM_Msg;

	struct	Timer10msData_t TimerRLSD_Detect;

	UBYTE timerID_TimerRLSD_Detect;
	UBYTE	rtn;

	/*	モデムステータス監視タスク起動	*/
	tskno_ModemStatusCheck = 0xffff;
	CMN_DisableInterrupt();		/* 1997/02/03 Y.Murata */
	ModemStatusFlag = 0;
	ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT+PHS_STAT_CHECK_RLSDON);	/**	ＲＬＳＤチェック指定	*/
	CMN_EnableInterrupt();		/* 1997/02/03 Y.Murata */
	cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task);	/**	モデムステータス監視タスク起動	*/

	/*	ＲＬＳＤ検出タイマ起動	*/
	TimerRLSD_Detect.Time = (timer/10);
	TimerRLSD_Detect.SendMBX = mbxno.MDM_Task;
	TimerRLSD_Detect.ReturnValue = MSG_TRAINING_DETECT_END_TIME;
	tskno_TimerRLSD_Detect = 0xff;
	CMN_MultiTimer10msStart(&timerID_TimerRLSD_Detect, &TimerRLSD_Detect);	/**	タイマ起動	*/

	/*	メッセージ受信
	 *	1.MSG_ENABLE_MODEM_STATUS:		モデムステータス監視タスクより
	 *	2.MSG_TRAINING_DETECT_END_TIME:	タイマタスクより
	 */
	do {
		rcv_msg( mbxno.MDM_Task, &MDM_Msg );
	} while (!((MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) ||
	           (MDM_Msg->Message == MSG_TRAINING_DETECT_END_TIME)));

	ModemWaitStatus = 0;

	/**	戻り値設定	*/
	if (MDM_Msg->Message == MSG_ENABLE_MODEM_STATUS) {	/**	メッセージ受信内容がトレーニング検出時	*/
		rtn = YES;
	}
	else{
		rtn = NO;
	}

	/**	モデムステータス監視タスク終了	*/
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck);
	}
	ModemStatusFlag = 0;

	/**	タイマタスク終了	*/
	if (timerID_TimerRLSD_Detect != 0xff) {
		CMN_MultiTimer10msStop(&timerID_TimerRLSD_Detect);
	}
	return (rtn);
}


/*************************************************************************
	module		:[スライスレベルチェック]
	function	:[
		1.
	]
	return		:[
		OK
		NG
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/18]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE	CheckSlice(UBYTE lowrate)
{
	UWORD		 	eye_slice;
	UBYTE	slice_no;
	UBYTE	column;
	UBYTE	country;
	UBYTE	dummy;

	eye_slice = 0;
	slice_no = 0;
	column = 0;

	country = 0;	/* 0 = JPN By O.Kimoto 1997/09/10 */

	if (CHK_EYE_Q_CheckAvailable()) {
		/*-------------------------------*/
		/** EYEQとスライス値を比較します */
		/*-------------------------------*/
		/* V33は、なくなるので無視します */
		/*------------------------------------*/
		/* ●メモリスイッチの設定             */
		/*                                    */
		/*   厳しい←                 →緩い  */
		/*    high  0     0     1     1       */
		/*    Low   0     1     0     1       */
		/*                                    */
		/* ●EYE_Qスライス値（テーブルＮｏ）  */
		/*          0     1     3     4       */
		/*------------------------------------*/
		switch(lowrate){
		case BPS2400_V27:
			slice_no = CHK_EYE_Q_Slice24();
			column = 7;
			break;
		case BPS4800_V27:
			slice_no = CHK_EYE_Q_Slice48();
			column = 6;
			break;
		case BPS7200_V29:
			slice_no = CHK_EYE_Q_Slice72();
			column = 5;
			break;
		case BPS9600_V29:
			slice_no = CHK_EYE_Q_Slice96();
			column = 4;
			break;
		case BPS7200_V17:
			slice_no = CHK_EYE_Q_Slice72();
			column = 3;
			break;
		case BPS9600_V17:
			slice_no = CHK_EYE_Q_Slice96();
			column = 2;
			break;
		case BPS12000_V17:
			slice_no = CHK_EYE_Q_Slice120();
			column = 1;
			break;
		case BPS14400_V17:
			slice_no = CHK_EYE_Q_Slice144();
			column = 0;
			break;
		default:
			break;
		}

		/*---------------------------------------------*/
		/** スライス値に対応するテーブル位置を決めます */
		/*---------------------------------------------*/
		switch (slice_no) {
		case 0:
			slice_no = 0;
			break;
		case 1:
			slice_no = 1;
			break;
		case 2:
			slice_no = 3;
			break;
		case 3:
			slice_no = 4;
			break;
		default:
			slice_no = 2;		/* 通常EYEスライス値=２ */
			break;
		}
		if (CHK_EYE_Q_SliceAvailable()) {
			/* Nothing */
		}
		else {
			slice_no = 2;		/* 通常EYEスライス値=２ */
		}
		/*-----------------------*/
		/** スライス値を決めます */
		/*-----------------------*/
		/*eye_slice = EyeSliceTable[column][slice_no]; 199701/09 Y.Murata 国別対応 */
		eye_slice = EyeSliceTable[country][column][slice_no];

		BackUpEYE_Slice = eye_slice;

		if (BackUpEYE_Slice == 0) {
			dummy = 1;
		}
		
		SYS_EyeQ_Level = MDM_RxTcfEyeAverage;

		if (MDM_RxTcfEyeAverage <= eye_slice) {
			return (YES);
		}
		else {
			return (NO);
		}
	}
	else {
		SYS_EyeQ_Level = MDM_RxTcfEyeAverage;
		return (YES);
	}
}


/*************************************************************************
	module		:[ＥＱＭ読み出しタスク（Ｖ．３４のみ有効）]
	function	:[
		1.プライマリーチャンネルに入った後ＲＬＳＤがＯＮするのを待ちます。
		2.７００ボー時間さらに待ちます。
		3.ＥＱＭの値（アドレス：２０Ｃ、メソッド：４）を読み出します。
		4.上位から殺されるのを待ちます。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_ReadEqmValueTask(void){}]
	date		:[1996/02/22]
	author		:[木元修]
*************************************************************************/
void  MDM_ReadEqmValueTask(void)
{
	UWORD	wait_time;
	UWORD	change_line;

	if (SYS_V34ProcedureExecuting()) {	/* add if() 1997/02/08 Y.Murata */
		CMN_DisableInterrupt();
		if (MDM_RlsdTurnOnFlag == 0) {
			wai_evt(EVT_MDM_TURNON);
		}
		MDM_RlsdTurnOnFlag = 0;
		CMN_EnableInterrupt();
	}

	/*----------------------------------------------------------*/
	/* EYE-QはTCF受信開始後(RLSD ON後)、約700ボー時間で安定する */
	/*   V17    14400bps  (700/2400ﾎﾞｰ) = 292ms                 */
	/*   V17    12000bps  (700/2400ﾎﾞｰ) = 292ms                 */
	/*   V17     9600bps  (700/2400ﾎﾞｰ) = 292ms                 */
	/*   V29     9600bps  (700/2400ﾎﾞｰ) = 292ms                 */
	/*   V29     7200bps  (700/2400ﾎﾞｰ) = 292ms                 */
	/*   V27ter  4800bps  (700/1600ﾎﾞｰ) = 438ms                 */
	/*   V27ter  2400bps  (700/1200ﾎﾞｰ) = 583ms                 */
	/*----------------------------------------------------------*/
	
	if (SYS_V34ProcedureExecuting()) {
		switch (V34BaudDataRate) {
		case SYMBOL_2400:
			wait_time = 292;	/* 700/2400*1000(ms) */
			break;
		case SYMBOL_2800:
			wait_time = 250;	/* 700/2800*1000(ms) */
			break;
		case SYMBOL_3000:
			wait_time = 233;	/* 700/3000*1000(ms) */
			break;
		case SYMBOL_3200:
			wait_time = 219;	/* 700/3200*1000(ms) */
			break;
		case SYMBOL_3429:
			wait_time = 204;	/* 700/3429*1000(ms) */
			break;
		default:
			wait_time = 292;	/* 700/2400*1000(ms) */
			break;
		}

		/* Ported from \src\nagano\mdm\r288r\src\mdm_tcf.c by H.Hirao 1999/09/11 */
		/* 1999/08/29 Y.Murata
		 * 全フレームエラー等が発生して受信側から速度を下げようとしてもさがらない。
		 * ここでのウエイトを増やせば、ちゃんと速度を落とす。
		 * ５００ｍｓ、６００ｍｓのウエイトで各シンボルレートともＯＫとなった。
		 * ３４２９では、２５０ｍｓ以上のウエイトでＯＫとなったが、２４００では３００ｍｓのウエイトでもＮＧだった。
		 * 各シンボルレートとも５００ｍｓのウイエトとします。
		*/
		wait_time = 500;

	}
	else {
		switch (ModemBlock.Type) {
		case TYPE_V17:
		case TYPE_V29:
			wait_time = 292;	/* 700/2400*1000(ms) */
			break;
		case TYPE_V27:
			if (ModemBlock.Speed == SPEED_4800) {
				wait_time = 438;	/* 700/1600*1000(ms) */
			}
			else {
				wait_time = 583;	/* 700/1200*1000(ms) */
			}
			break;
		default:
			wait_time = 292;	/* 700/2400*1000(ms) */
			break;
		}
	}

	wai_tsk((UWORD)(wait_time/10));


/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/04 **/
/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/17 **/

#if 0	/* 1996/08/26 Y.Murata */
//	/* ﾒﾓﾘSWがたっている時か、相手がﾑﾗﾀ機ならPPh 1996/08/03 Y.M */
//	if ((CHK_V34ForcedPPh()) || (MakerCodeRxFlag == 1)) {	/* 1996/07/17 Y.M */
//		MDM_SetForcedPPh();
//	}
#endif
#if 0	/* 移動 1996/08/28 Y.Murata */
//	/* ﾒﾓﾘSWがたっている時のみ強制PPhｽﾀｰﾄ 1996/08/26 Y.M */
//	if (CHK_V34ForcedPPh()) {
//		MDM_SetForcedPPh();
//	}
#endif

	/* 1996/05/16 Y.Murata
	 * 前のページでエラーフレームが１０％あれば通信速度を受信局より下げる
	*/
	if (SYS_V34ProcedureExecuting()) {	/* add if 1996/10/23 Y.Murata */
	/*--------*/
	/* Ｖ３４ */
	/*--------*/
		if (CHK_V34RxDataRateChange() != 0) {	/* UNIQ D2:4 */
			if (FCM_SavedRxErrorFrameLine != 0) {
				if (CHK_V34RxDataRateChangeType() != 0) {	/* UNIQ D2:5 */
					change_line = (UWORD)(FCM_SavedRxPartialFrameLine / (UWORD)10);
					if (change_line < FCM_SavedRxErrorFrameLine) {

						FCM_DataRateChangExecute = FCM_ChangeDataRate(RxBaudRate);	/* 1996/09/10 Y.M */
					}
				}
				else {
					change_line = (UWORD)(FCM_SavedRxTotalFrameLine / (UWORD)10);
					if (change_line < FCM_SavedRxErrorFrameLine) {

						FCM_DataRateChangExecute = FCM_ChangeDataRate(RxBaudRate);	/* 1996/09/10 Y.M */
					}
				}
			}
			else {	/* エラーラインなし */
				if (FCM_SavedRxNonErrContinuePage >= 2) {	/* ２ページ以上エラーなしなら */
					FCM_SavedRxNonErrContinuePage = 0;

					if (CHK_V34RxDataRateUp()) {	/* add if 1996/09/11 Y.Murata */
						FCM_DataRateChangExecute = FCM_ChangeDataRateUp(RxBaudRate);	/* 1996/09/10 Y.M */
					}
					else {
						FCM_DataRateChangExecute = 0;
					}
				}
			}
		}

		if (FCM_DataRateChangExecute == 1) {	/* 1996/08/28 Y.Murata */
			FCM_DataRateChangExecute = 0;
		}
		else {
			/* ﾒﾓﾘSWがたっている時か、相手がﾑﾗﾀ機ならPPh 1996/08/28 Y.M */
			if ((CHK_V34ForcedPPh()) || (MakerCodeRxFlag == 1)) {
				MDM_SetForcedPPh();
			}
		}

		MDM_EQM_Value = MDM_GetEyeQualityMonitor();

		MDM_GetEQMAveraging();

		wai_tsk(0xffff);
	}
	else {
	/*--------*/
	/* Ｔ３０ */
	/*--------*/
		if (ModemBlock.Mode == MODE_RX_TCF) {	/**	交信モード設定	*/
			FCM_EQM_MonitorPoint = 0;
			MDM_RxTcfEyeAverage = 0;
			while (1) {
				if (MDM_GetIO(POS_RLSD)) {
					MDM_EQM_Value = MDM_GetEyeQualityMonitor();
					DBG_EqmAraBias = DspRamAccessReadMethod2(0x2A4,0x2A5);	/* For Debug by O.Kimoto 1996/04/09 */
					MDM_GetEQMAveraging();

					DammyDataforMurata2 = DspRamAccessReadMethod3(0xA29);	/* F69 */

					if (FCM_EQM_MonitorPoint < sizeof(FCM_EQM_MonitorBuf)) {
						FCM_EQM_MonitorBuf[FCM_EQM_MonitorPoint] = MDM_EQM_Value;
						FCM_EQM_MonitorPoint++;
					}

					if (MDM_RxTcfEyeAverage) {
						MDM_RxTcfEyeAverage = ((MDM_RxTcfEyeAverage + MDM_EQM_Value)/2);
					}
					else {
						MDM_RxTcfEyeAverage = MDM_EQM_Value;
					}

					wai_tsk(1);		/* 10ms */
				}
				else {
					wai_tsk(1);		/* 10ms */
				}
			}
		}
		else {
			wai_tsk(0xFFFF);
		}
	}
}


