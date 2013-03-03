/**********************************************************************************************************************
	@(#)$Id: s1_tcf.c,v 1.8 2005/11/17 01:42:02 mi93007 Exp $
	Create        : 2005/06/13
	Author        : 石橋正和
	Description   : S1 TCF処理
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\s1_data.h"

#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"

#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

#include "\src\atlanta\hinoki\define\hino_tib.h"

/**************************************************************************************************/
/**
	@brief		S1経由トレーニング受信をするか否か
	
	@li			
	@param		
	@return		TRUE:	S1経由でトレーニングを行う
				FALSE:	S1は使用しない
	@note		
	@date		2005/06/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL S1_CheckScramblePossibility(
						UBYTE rate) /* ボーレート */
{
	BOOL ret;
	
	switch (rate) {
	case BPS9600_V17:
	case BPS7200_V17:
	case BPS9600_V29:
	case BPS7200_V29:
	case BPS4800_V27:
	case BPS2400_V27:
		ret = TRUE;
		break;
	default:
		ret = FALSE;
		break;
	}
	
	return ret;
}

BOOL S1_ReceivingTCF_Data;

/**************************************************************************************************/
/**
	@brief		トレーニング受信
	
	@li			
	@param		
	@return		OK:	トレーニング受信良好
				NG:	フォールバック必要
	@note		
	@date		2005/06/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_ReceiveTCF(
				UBYTE speed,		/* モデムタイプ・スピード */
				BOOL bbypass,		/* S1バイパスしているか否か */
				BOOL* pbscrambled)	/* スクランブルデータか否か(出力) */
{
	MESSAGE_t* pmdm_msg;

	struct Timer10msData_t timer_eye_q;
	struct Timer10msData_t timer_tcf;
	struct Timer10msData_t timer_tcf_end;
	struct Timer10msData_t timer_tcf_read_time;

	UWORD tcf_time;
	UBYTE tcf_flg;
	UBYTE eye_q_ok;
	UBYTE rtn;

	UBYTE	eyeq_buf[6];	/* EYE-Q用バッファ */

	UWORD tcf_chk_total;	/* 連続してこの回数0が続いたらTCFチェックOK */
	UWORD tcf_chk_num1;		/* TCFフラグ1の0検出回数 */
	UWORD tcf_chk_num2;		/* TCFフラグ2の0検出回数 */
	UBYTE flag1;			/* TCFチェックフラグ1 */
	UBYTE flag2;			/* TCFチェックフラグ2 */
	
	BOOL bs1_on;			/* S1が有効か否か */
	
	BackUpEYE_Slice = 0;	/* 1996/10/25 Y.M */

	InitializeModemWork();
	ModemTypeSet(speed); /** モデムタイプ設定 */

	ModemBlock.Training = TRAINING_LONG;
	ModemBlock.Mode = MODE_RX_TCF; /* 交信モード設定 */ /* add 1996/10/18 Y.Murata */

	RxG3_Open();
	MDM_NewT30Status = MODE_RX_TCF;	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */

	MDM_SetIO(POS_STRN, OFF); /** Advice for Rockwell by O.Kimoto 1997/01/28 */

	/**	トレーニング検出処理	*/
	if (CheckTraining(3500) == NO) {
		RxG3_Close();
		return NG;
	}
	ModemWaitStatus = 0;

	/* 受信データ転送中	*/
	if (CheckRLSD(3000) == NO) {
		RxG3_Close();
		return NG;
	}

	ModemWaitStatus = 0;

	/* ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ by O.Kimoto 1997/01/28 */
	if (ModemBlock.Type	== TYPE_V17) { /* モデムタイプ V17設定 */
		MDM_SetIO(POS_STRN,ON);
	}

	/* EQMリードタスク起動 1996/10/23 Y.Murata */
	MDM_RlsdTurnOffCheckFlag = TRUE;
	MDM_RlsdTurnOnFlag = 0;
	tskno_EyeQualityMonitor = 0xffff;
	cre_tsk(&tskno_EyeQualityMonitor,TSK_MDM_READEQMVALUETASK,0);

	/* 1秒タイマ設定タイマタスク起動(EYE Quality用) */
	timer_eye_q.Time = (EYE_Q_TIME/10);
	timer_eye_q.SendMBX = mbxno.MDM_Task;
	timer_eye_q.ReturnValue = MSG_EYE_Q_TIME;
	tskno_TimerEYE_Q = 0xFFFF;
	cre_tsk(&tskno_TimerEYE_Q, TSK_CMN_MAN_TIMER10MSTASK, &timer_eye_q);

	/* 1.5秒タイマ設定タイマタスク起動(TCF時間用) */
	timer_tcf.Time = (TCF_TIME/10);
	timer_tcf.SendMBX = mbxno.MDM_Task;
	timer_tcf.ReturnValue = MSG_TCF_TIME;
	tskno_TimerTCF = 0xffff;
	cre_tsk(&tskno_TimerTCF, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf);

	/* 2.0秒タイマ設定タイマタスク起動(TCF END時間) */
	timer_tcf_end.Time = (TCF_END_TIME/10);
	timer_tcf_end.SendMBX = mbxno.MDM_Task;
	timer_tcf_end.ReturnValue = MSG_TCF_END_TIME;
	tskno_TimerTCF_End = 0xffff;
	cre_tsk(&tskno_TimerTCF_End, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_end);

	/* 10msタイマ設定タイマタスク起動 */
	timer_tcf_read_time.Time = (TCF_READ_TIME/10);
	timer_tcf_read_time.SendMBX = mbxno.MDM_Task;
	timer_tcf_read_time.ReturnValue = MSG_TCF_READ_TIME;
	tskno_TimerTCF_ReadTime = 0xffff;
	cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_read_time);
	
	tcf_time = CHK_UNI_TCF_CheckTime(); /* ゼロチェック時間設定 */
	if (tcf_time == 0) {
		tcf_time = 100;
	}
	tcf_chk_total = tcf_time / TCF_READ_TIME;
	tcf_chk_num1 = 0;
	tcf_chk_num2 = 0;
	tcf_flg = 0;
	*pbscrambled = FALSE;
	eye_q_ok = 0;
	
	bs1_on = S1_GetScrambleAvailable();
	
	S1_ReceivingTCF_Data = TRUE;
	tskno_S1_ReceiveTCF_Data = 0xFFFF;
	cre_tsk(&tskno_S1_ReceiveTCF_Data, TSK_S1_RECEIVETCF_DATATASK, 0); /* TCFデータ受信タスク起動 */
	
	S1_TCF_Clear(); /* TCFチェックフラグクリア */
	
	while (1) {
		rcv_msg(mbxno.MDM_Task, &pmdm_msg);
		
		switch (pmdm_msg->Message) {
		case MSG_TCF_READ_TIME: /* トレーニング ゼロチェック処理(10msタイムアップ時) */
			if (tskno_TimerTCF_ReadTime != 0xFFFF) {
				del_tsk(&tskno_TimerTCF_ReadTime); /* 10msタイムアップタイマタスク終了 */
			}
			
			S1_TCF_Detect(&flag1, &flag2); /* TCFチェックフラグ検出 */
			S1_TCF_Clear(); /* TCFチェックフラグクリア */
			
			if ((bs1_on == TRUE) && (bbypass == FALSE)) { /* S1が有効の場合 */
				if (flag1 == 0) {
					tcf_chk_num1++;
					if (tcf_chk_num1 == tcf_chk_total) { /* 指定期間0のみを検出 */
						tcf_flg = 1; /* 0チェック終了フラグセット */
						if (eye_q_ok) {
							EqualizerHoldOn();
						}
					}
				}
				else {
					tcf_chk_num1 = 0;
				}
			}
			if (flag2 == 0) {
				tcf_chk_num2++;
				if (tcf_chk_num2 == tcf_chk_total) { /* 指定期間0のみを検出 */
					*pbscrambled = TRUE; /* スクランブル */
					tcf_flg = 1; /* 0チェック終了フラグセット */
					if (eye_q_ok) {
						EqualizerHoldOn();
					}
				}
			}
			else {
				tcf_chk_num2 = 0;
			}
			
			if (tcf_flg != 1) { /* 0チェック継続する時 */
				tskno_TimerTCF_ReadTime = 0xffff;
				cre_tsk(&tskno_TimerTCF_ReadTime, TSK_CMN_MAN_TIMER10MSTASK, &timer_tcf_read_time); /* 10msタイマ設定タイマタスク起動 */
			}
			break;
		case MSG_EYE_Q_TIME: /* EYE_Qチェック処理(1秒タイムアップ時) */
			if (ModemBlock.Type == TYPE_V17) { /* モデムタイプがV17の時 */
				if (CHK_V17EqualizerHold()) {
					EqualizerHoldOn(); /* イコライザホールド設定 */
				}
			}
			if (CheckSlice(speed) == YES) {
				eye_q_ok = 1; /* ＥＹＥチェックフラグ設定 */
				if (tcf_flg) {
					EqualizerHoldOn();
				}
			}
			break;
		case MSG_TCF_TIME: /* RLSD OFF検出開始設定(1.5秒タイムアップ時) */
			S1_ReceivingTCF_Data = FALSE;
			
			/*	モデムステータス監視タスク起動	*/
			tskno_ModemStatusCheck = 0xffff;
			ModemStatusFlag = 0;
			ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_RLSDOFF); /* RLSD OFFチェック設定 */
			cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_Task); /** モデムステータス監視タスク起動 */
			break;
		case MSG_ENABLE_MODEM_STATUS: /* RLSD OFF検出時 */
			/* バッファにトレーニングデータが残っている時(念のため) */
			goto END;
		case MSG_TCF_END_TIME: /* トレーニング監視終了時間(TCF END 2秒タイムアップ時) */
			goto END;
		default:
			break;
		}
	}
	
END:
	if (eye_q_ok && tcf_flg) {
		
		
		
		/* 暫定対策 */
		if (*pbscrambled == TRUE) {
			if (tcf_chk_num1 > (tcf_chk_num2 - 5)) {
				*pbscrambled = FALSE;
			}
		}
		
		
		
		rtn = OK;
	}
	else {
		rtn = NG;
	}
	if (tskno_TimerTCF_ReadTime != 0xffff) {
		del_tsk(&tskno_TimerTCF_ReadTime);
	}
	if (tskno_TimerEYE_Q != 0xffff) {
		del_tsk(&tskno_TimerEYE_Q); /* 1秒タイマ設定タイマタスク終了 */
	}
	if (tskno_TimerTCF != 0xffff) {
		del_tsk(&tskno_TimerTCF); /* 1.5秒タイマ設定タイマタスク終了(TCF時間用) */
	}
	if (tskno_TimerTCF_End != 0xffff) {
		del_tsk(&tskno_TimerTCF_End); /* 2.0秒タイマ設定タイマタスク終了(TCF END時間) */
	}
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck); /* モデムステータス監視タスク */
	}
	ModemStatusFlag = 0;
	
	MDM_RlsdTurnOffCheckFlag = FALSE;
	if (tskno_EyeQualityMonitor != 0xffff) {
		del_tsk(&tskno_EyeQualityMonitor); /* EQM値リードタスク 1996/10/23 Y.Murata */
	}

	RxG3_Close(); /* TCFモデムクローズ処理	*/

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

	return (rtn);
}

/**************************************************************************************************/
/**
	@brief		TCFデータ受信タスク
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/08/23 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_ReceiveTCF_DataTask(void)
{
	UBYTE correct_readpoint;
	
	correct_readpoint = 1;
	
	while (1) {
		if ((ModemControl.UsedCount >= MODEM_BUFFER_MAX) && (correct_readpoint)) {
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			if (ModemControl.WritePoint == (MODEM_BUFFER_MAX-1)) {
				ModemControl.ReadPoint = 0;
			}
			else {
				ModemControl.ReadPoint = (UBYTE)(ModemControl.WritePoint + 1);
			}
			CMN_EnableInterrupt();	/**	割り込み許可	*/
		}
		correct_readpoint = 0;
		
		if (RxG3_Read() == RCV_BLOCK){	/**	モデムバッファ読み出し／１ブロック受信完了時	*/
			NextMdmBufReadPointSetExtRom();
		}
		else {	/**	ストップＳｗ処理	*/
			break;
		}
		
		if (S1_ReceivingTCF_Data == FALSE) {
			break;
		}
	}
	
	exi_tsk();
}

