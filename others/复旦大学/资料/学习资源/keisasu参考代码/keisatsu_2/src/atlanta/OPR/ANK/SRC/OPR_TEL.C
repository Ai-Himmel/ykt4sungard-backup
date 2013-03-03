/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_TEL.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 多機能電話オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_b.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysscan.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\dpr_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#endif

#if (PRO_CL1_TELFAX_LAN == ENABLE)		/* S.Fukui Jun 19,1998 */
#include	"\src\atlanta\define\cl1_def.h"
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_PRINTER_RX == ENABLE)
#include	"\src\atlanta\define\man_pro.h"	/* added by H.Hirao 1998/03/10 */
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/28 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#include	"\src\memsw\define\mem_sw_g.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\man_data.h"		/* 警察FAX DVT Added by SMuratec K.W.Q 2005/11/14 */
/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#include	"\src\atlanta\define\sysnd.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\ext_v\ncu_data.h"

/* 警察FAX DVT_ID58 Added by SMuratec 夏 2005/12/07 */
#include	"\src\atlanta\define\sys_line.h"
#endif 		/* End of (defined (KEISATSU)) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/07 */
struct	DialingData_t	TEL_ManualTxNumber;
#endif		/* End of (defined (KEISATSU)) */

/* Prototype
void	TelOperation(UBYTE, UBYTE);
void	TelOperationInitial(void)
UBYTE	CheckTelephoneStatus(void);
UBYTE	CheckLineStatus(void);
void	HookKeySet(void);
void	HoldKeySet(void);
void	SpeedTelOperation(void);
UBYTE	SpeedOperationSelect(void);
void	ManualTRxOperation(void);
void	OnetouchDialStart(UBYTE);
void	SpeedDialStart(UBYTE);
void	RedialStart(void);
void	DialMarkStart(UBYTE);
void	DirectDialStart(UBYTE key);
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	TelPinNumberInput(UBYTE *);
#endif
void	SetDialingBuffer(void);
UBYTE	CheckDialingEnable(UBYTE);
void	DisplayNCUStatus(void);
void	DisplayTelNumber(void);
void	SpeakerVolumeAdjust(void);
void	DisplayMonitorSpeakerVolume(void);
void	ChangePanelBusy(void);
*/

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
UBYTE UAE_PIN_FirstSharpCode = 0;/* UAE ARAMCO PIN By O.Kimoto 1997/04/16 */
UWORD UAE_PIN_1stSharpPosition = 0;	/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
UWORD UAE_PIN_2ndSharpPosition = 0;	/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
UWORD UAE_PIN_CopiedSrcBufferPosition = 0;	/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
UBYTE CHK_UNI_AramcoPinNotMasking(void);	/* UAE ARAMCO By O.Kimoto 1997/06/04 */
UWORD UAE_PIN_RoundFlag = 0;	/* UAE ARAMCO By O.Kimoto 1997/06/04 */
#endif
/*************************************************************************
	module		:[電話オペレーション]
	function	:[
		1.電話中のオペレーション
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		DialingNumberの説明
		,	DialingNumber.Buffer[80]	:電話番号入力バッファ
		,		これはループバッファとなっている。DIALING_NUMBER_MAXの位置に
		,		データが入力されているどうかにより１周したかどうかがわかる。
		,	DialingNumber.ReadPointer	:ダイヤルし終わった位置
		,	DialingNumber.WritePointer	:入力位置
		,
		DialingNumberの図による説明
		, |DialingNumber.ReadPointer=2 ここまではすでに発呼した。
		, |        |DialingNumber.WritePointer=11 入力中の位置。
		, |        |
		0123456789012345678901234567890123456789～
		075-643-778                                 <- 入力バッファ
		,          -                                <- カーソル
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/17]
	author		:[江口]
*************************************************************************/
void TelOperation(UBYTE key_code,	/* キーコード */
				  UBYTE key_type)	/* キータイプ */
{
	UBYTE	is_key_request;	/* キー入力を行うかパスするか (0:パス 1:行う) */
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_opr_protect;	/* オペレーションプロテクト状態解除済み：１、解除していない：０ */
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	number;
#endif
	UWORD	number;
	UBYTE	telbook_wait_hook;
#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
	UBYTE	bak_mode;
	UBYTE	last_key;		/* 前回キー入力値 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /*（ダイヤル中のトーンキーが V650と同じくなります）Added by SMuratec L.Z.W 2003/10/21 */
	UBYTE	ast_count;				/* '*'チェック用 */	/* 2001/05/10 K.Sasaki */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/25 */
	UBYTE	dial_number[2];
#endif		/* End of (defined (KEISATSU)) */

	/*-----------*/
	/** 初期設定 */
	/*-----------*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;	/* 電話中表示用（電話あげた時点でＯＮする） */
	TelOperationInitial();	/* ダイアルバッファ・オペレーションバッファのクリア処理 */
	telbook_wait_hook = 0;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /*（ダイヤル中のトーンキーが V650と同じくなります）Added by SMuratec L.Z.W 2003/10/21 */
	ast_count = 0;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/* キーデータの引き継ぎ */
	is_key_request = FALSE;
	key = key_code;
	keytype = key_type;

#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
#if (0)
//#if (PRO_FBS == ENABLE)
//	if (SYB_MaintenanceSwitch[MNT_SW_B4] & FBS_REALTIME_TX) {	/* ＦＢＳからのリアルタイム送信可能な時 */
//		last_key = key;	/* 前回キー入力値の退避（ＦＢＳからのスキャナ送信時に使用） */
//	}
//#endif
#endif

	last_key = key;	/* 前回キー入力値の退避 */
#endif

	/* オペレーションプロテクト状態のチェック */
	is_opr_protect = FALSE;
	if (CHK_OperationProtect()) {	/* オペレーションプロテクトがＯＮの時 */
		is_opr_protect = TRUE;
	}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
	/* ＴＥＬオペレーションに入った時は、ファクスモードにします */
	if (bak_mode = CHK_ReadyModeCopy()) {
		CopyFaxKeyOperation();
	}
#endif

	while (1) {
		if (is_key_request) {	/** キー取り込み要求あり */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_OPERATE;	/** オペ終了 */

#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
			if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
 #if (0)
 //				/* メインにコピーモード表示用のメッセージを送信 */
 //				OperationMessageToMain.Message = MSG_DISPLAY_IDLE;
 //				snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
 //				MainTaskExecWait();
 #endif
				/* 原稿蓄積中の表示を行います */
				UpdateLCD();
			}
			else {						/* 電話（ファクスモード）の時 */
				if (CheckExceptCopyDocStore()) {	/* コピー原稿以外の蓄積の時 */
					/* 原稿蓄積中の表示を行います */
					UpdateLCD();
				}
				else {
					/* 電話中の表示を行います */
					DisplayNCUStatus();
				}
			}
#else
 #if (PRO_DISPLAY_TEL_TO_IDLE == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
				/* 電話中の表示を行います */
				DisplayNCUStatus();
			}
			else {
				/* 待機中の表示を行います */
				UpdateLCD();
			}
 #else
			/* 電話中の表示を行います */
			DisplayNCUStatus();
 #endif
#endif

			/** キー取り込み */
#if defined (KEISATSU)		/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/14 */
		if (AttributeTimeoutCheck) {
			OPR_GetKey( KEY_WAIT_ONE_MINUTE );
		}
		else {
			OPR_GetKey(KEY_WAIT_FOREVER);
		}
#else
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
			if ( IsCopyReserved && IsScanReserved ) {
				OPR_GetKey(KEY_WAIT_2_SECOND);
			}
			else {
				OPR_GetKey(KEY_WAIT_FOREVER);
			}
#else /* (PRO_PAPER_TYPE != CUT_PAPER) || !defined(STOCKHM2) */
			OPR_GetKey(KEY_WAIT_FOREVER);
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
#endif		/* End of (defined (KEISATSU)) */

			key = GetInputKeyCode();
			keytype = GetInputKeyType();

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/25 */
			if (IsDocumentSet) {
				IsDocumentSet = FALSE;
			}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_OPERATE;	/** オペ中 */

			if (is_opr_protect) {	/* プロテクト状態が解除されていない時 */
				if (OperationProtectReset(keytype) == NG) {	/* プロテクトが解除されなかった時 */
					continue;
				}
				else {										/* プロテクトが解除された時 */
					is_opr_protect = FALSE;
				}
			}

			/* 現在の状態より押されたキーが有効かどうかをチェックします */
			CheckOperationValid(&keytype);

#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
			if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
				/* CopyOperation()では、コピーモード専用の処理しか行っていないので、それ以外はメインで処理を行います */
				if (CopyOperation(key, keytype, last_key) == TRUE) {	/* 既に処理をおこなった場合 */
					keytype = NO_EFFECT;	/* メインでは処理は行いません */

					/* 電話（ファクスモード）に変更されていれば、表示制御用の処理をします */
					ChangePanelBusy();
				}
			}
#endif
		}
		is_key_request = TRUE;

		/* 回線回りの状態の取り出し */
		TelControl.NcuStatus = CheckLineStatus();
		if ((TelControl.NcuStatus != OPR_NCU_IDLE) && (telbook_wait_hook)) {
			telbook_wait_hook = 0;
		}

		/* ＰＩＮアクセスモードを獲得 */
#if (PRO_PIN_ACCESS == ENABLE)
		TelControl.PinAccessMode = CHK_PIN_AccessMode();
#else
		TelControl.PinAccessMode = PIN_ACCESS_OFF;
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/31 */
		if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE) {
			if (keytype != NO_EFFECT && keytype != KEY_TIME_UP) {
#if 0 /* 警察FAX DVT_ID37 Deleted by SMuratec 李 2005/11/14 */
@@				keytype = ERROR_OPERATION;	/* メインでは処理は行いません */
#else
				NackBuzzer();
				continue;
#endif
			}
		}
#endif		/* End of (defined (KEISATSU)) */

		switch (keytype) {
		case HOOK:					/* フックキーの処理 */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/21 */
			if (CheckFaxComExecute()) {					/*	通信中	*/
				NackBuzzer();
				break;
			}

			if (CMN_CheckHDSTOnSTD() || CMN_CheckHDSTOnEXT()) {
				NackBuzzer();
				break;
			}

			if (!CheckIsKanyuLine()) {					/*	警電受話中（警電優先受信）,警電側無効 */
				if (CheckKeidenRxPriorityON() &&
					(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {
					NackBuzzer();
					break;
				}
			}

			switch (TelControl.NcuStatus) {
			case OPR_HOOKKEY_OFFHOOK:
			case OPR_TEL1_HOOK_OFFHOOK:
			case OPR_TEL2_HOOK_OFFHOOK:
				if (SYS_DialingNumber.WritePointer != SYS_DialingNumber.ReadPointer) {
					SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
				}
				else {
					HookKeySet();
				}
				break;
			case OPR_TEL1_OFFHOOK:
				if (CheckIsKanyuLine()) {
					if (SYS_CalledLineNumber == SYS_EXT_LINE_IN_CI) {
						SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_LINE;
						AttributeTimeoutCheck = 1;

						NCU_HdstShift();
						UpdateRxModeDisplay();	/* 自動受信ＬＥＤ Add by SMuratec 夏 2005/07/01 */

						TelOperationInitial();	/* ダイアルバッファ・オペレーションバッファのクリア処理 */

						HookKeySet();
						UpdateLCD();
						
						break;
					}
					else {
						NackBuzzer();
					}
				}
				else {
					HookKeySet();
				}
				break;
			case OPR_TEL2_OFFHOOK:
				if (CheckIsKanyuLine()) {
					HookKeySet();
				}
				else {
					if (SYS_CalledLineNumber == SYS_STD_LINE_IN_CI) {
						SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_LINE;
						AttributeTimeoutCheck = 1;
						HookKeySet();

						NCU_HdstShift();
						UpdateRxModeDisplay();	/* 自動受信ＬＥＤ Add by SMuratec 夏 2005/07/01 */

						TelOperationInitial();	/* ダイアルバッファ・オペレーションバッファのクリア処理 */

						HookKeySet();
						UpdateLCD();
						break;
					}
					else {
						NackBuzzer();
					}
				}
				break;
			case OPR_TEL1_TEL2_OFFHOOK:
				NackBuzzer();
				break;
			}

			break;
#else
			switch (TelControl.NcuStatus) {
			case OPR_TEL1_OFFHOOK:
				if (SYS_DialingNumber.ReadPointer == SYS_DialingNumber.WritePointer) {
					HookKeySet();
				}
				else {
					NackBuzzer();
				}
				break;
			case OPR_HOOKKEY_OFFHOOK:
				HookKeySet();
				break;
			default:
#if defined(POPLAR_F)
#else
				NackBuzzer();
#endif
				break;
			}
			break;
#endif		/* End of (defined (KEISATSU)) */
			
		case HOLD:					/* 保留キ-の処理 */
#if defined(KEISATSU) /* 警察FAX DVT Modify by SMuratec 夏 2005/12/07 */
			NackBuzzer();
#else
			switch (TelControl.NcuStatus) {
			case OPR_TEL1_OFFHOOK:
			case OPR_LINEHOLDTEL1UP:
				if (SYS_DialingNumber.ReadPointer == SYS_DialingNumber.WritePointer) {	/* ダイアル完了 */
					HoldKeySet();
				}
				else {
					NackBuzzer();
				}
				break;
			default:
				NackBuzzer();
				break;
			}
#endif
			break;

#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
		case COPY_FAX:				/* コピー／ファクスキーの処理 */
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
			default:
				CopyFaxKeyOperation();

				/* コピーモードに変更されていれば、表示制御用の処理をします */
				ChangePanelBusy();
				break;
			}
			break;
#else
		case COPY:					/* コピーキーの処理 */
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
			default:
				CopyKeyOperation();
				break;
			}
			break;
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/25 */
		case COMM_REPORT:			/* 通信証キー				*/
			SetCheckConfirmReport(); /* (一時の通信証の設定になります) Modify by SMuratec L.Z.W 2003/10/09 */
			break;
		
		/* Added by SMuratec L.Z.W 2003/08/04 */	
		case CMD_LIST:				/* Ｐ通信管理				*/
			PrintJournalList();
			break;
			
		/* Added by SMuratec L.Z.W 2003/08/04 */
		case TCH_LIST:				/* Ｐワンタッチリスト		*/
			PrintOneTouchList();
			break;
			
		/* Added by SMuratec L.Z.W 2003/08/04 */
		case SPD_LIST:				/* Ｐ短縮リスト			    */
			PrintSpeedDialList();
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 音量調整キーも機能キーと同様の処理を行う。by Y.Kano 2003/09/20 */
		case VOLUME:				/* 音量調整キー */
		case LEFT_ARROW:			/* 左矢印キー by Y.Kano 2003/10/16 */
#endif
		case FUNCTION:				/* 機能／右矢印キーの処理 */
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
#if (0)
** /* HINOKIはVolumeはメカボリュームなので、フック中でも、従来のファンクションを起動します。
** 			case OPR_HOOKKEY_OFFHOOK:
** #if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1999/01/06 */
** 				NackBuzzer();
** #else
** 				SpeakerVolumeAdjust();
** #endif
#else
   #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/10/17 */
			case OPR_HOOKKEY_OFFHOOK:
				SpeakerVolumeAdjust();
				break;
			case OPR_TEL1_OFFHOOK:		/* 付属ＴＥＬの追加 by Y.Kano 2003/10/17 */
				if (keytype == VOLUME) {	/* 音量調整キーのみ有効 */
					VolumeKeyOperation();	/* 音量調整処理 */
				}
				else if (keytype == FUNCTION) {
					FunctionOperation();
					if (SpecialCommandValue.Page != 0) {	/* 枚数指定オペレーションが実行された場合 */
						/** コマンドオペレーションを実行する */
						CommandOperation(OPR_NO_KEY, NO_EFFECT);
					}
				}
				
   #if (PRO_DISPLAY_TEL_TO_IDLE == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
				else if (keytype == LEFT_ARROW) {
					if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PANEL_BUSY;
					}
					else {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
					}
				}
   #endif
				else {
					NackBuzzer();
				}
				break;
   #elif (PRO_KEYPANEL != PANEL_HINOKI)	/* Add By H.Fujimura 1999/01/06 */
			case OPR_HOOKKEY_OFFHOOK:
				SpeakerVolumeAdjust();
				break;
   #endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
			default:
				FunctionOperation();
				if (SpecialCommandValue.Page != 0) {	/* 枚数指定オペレーションが実行された場合 */
					/** コマンドオペレーションを実行する */
					CommandOperation(OPR_NO_KEY, NO_EFFECT);
				}
				break;
			}
			break;

#if (PRO_FBS == ENABLE)
		case NEXT_DOC:				/* 次原稿キー */
			if (CheckExceptCopyDocStore()) {	/* コピー原稿以外の蓄積の時 */
				BookNextDocumentSet(key, FALSE);
			}
			else {
				switch (TelControl.NcuStatus) {
				case OPR_HOOKKEY_OFFHOOK:
 #if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1999/01/06 */
					NackBuzzer();
 #else
					SpeakerVolumeAdjust();
 #endif
					break;
				case OPR_TEL2_OFFHOOK:
					CommandOperation(key, keytype);
					break;
				default:
					NackBuzzer();
					break;
				}
			}
			break;
#else
 #if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* 削除 by Y.Kano 2003/10/16 */
		case LEFT_ARROW:			/* 左矢印キー */
   #if (PRO_DISPLAY_TEL_TO_IDLE == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PANEL_BUSY;
			}
			else {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
			}
			break;
   #endif
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/23 */
			switch (TelControl.NcuStatus & OPR_HOOKKEY_OFFHOOK) {
#else /* !defined (KEISATSU) */
			switch (TelControl.NcuStatus) {
#endif /* defined (KEISATSU) */
			case OPR_HOOKKEY_OFFHOOK:
 #if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1999/01/06 */ /* Add by Y.Kano 2003/07/11 */
				NackBuzzer();
 #else
				SpeakerVolumeAdjust();
 #endif
				break;
			default:
				NackBuzzer();
				break;
			}
			break;
 #endif	/* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
#endif

		case REVIEW:			 	/* 通信確認キー */
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
			default:
#if (PRO_KEYPANEL == PANEL_SATSUKI2)/* (F250には送信証のキーがあるのでこの機能(通信証)は必要有りません。) Modify by SMuratec L.Z.W 2003/11/25 */
				ConfirmClearCommandOperation();
#elif(PRO_KEYPANEL == PANEL_STOCKHM2) /* QAT : 電話を上げる時、通信確認キーを押すの対応 SMuratec C.P 2004/11/01 */
				ConfirmClearResultCommand();
#else
				ReviewCommandOperation();
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
				break;
			}
			break;

		case STOP:					/* ストップキー */
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
			case OPR_HOOKKEY_OFFHOOK:
#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
 #if (0)	/* ポプラＢだけは、イチョウに合わせてフックキーはフックキーでしかＯＦＦ出来ないようにします */
 //				if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
 //					StopKeyOperation();
 //				}
 //				else {						/* ファクスモードの時 */
 //					HookKeySet();
 //				}
 #endif
				StopKeyOperation();
#else

 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
				/* フック中にストップキー入力があっても、フックキー処理は行いません。
				** フックの解除はあくまでもフックキーのみとします。
				** POPLAR_Lがフックの解除がストップキーで行えますが、既量産機種でもあり、
				** マニュアルやＯＥＭとの関係もあるので、ＨＩＮＯＫＩと分けておきます。
				** 今後はフックの解除はフックキーしかできないように統一しましょう！！
				** by O.Kimoto 1999/02/01
				*/
				StopKeyOperation();
 #else
				HookKeySet();
 #endif
#endif
				break;
			default:
				StopKeyOperation();
				break;
			}
#if defined (KEISATSU)		/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/14 */
			if (AttributeTimeoutCheck &&
				(!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) && 
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) &&
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK))) {

				SetKeisatsuSettings();
				AttributeTimeoutCheck = 0;
				NCU_HdstShift();
 #if 0	/* 警察FAX DVT Deleted by SMuratec 夏 2005/12/17 */
				UpdateLCD();
 #endif
			}

#endif		/* End of (defined (KEISATSU)) */
			break;

		case START:					/* スタートキー */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/12 */
			/* 警察FAX DVT_ID58 Added by SMuratec 夏 2005/12/07 
			** 秘話機能では外付電話を先に上げるの場合、
			** パネルでテンキー、ワンタッチキー、短縮キー、Startキーなど無効になる
			*/
			if ((((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_EXT) && CheckIsKanyuLine()) ||
				(((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_EXT) && !CheckIsKanyuLine())){
				NackBuzzer();
				break;
			}
			
			if (CheckIsKanyuLine()){					/*	警電受話中（警電優先受信）,加入側無効 */
				if (CheckKeidenRxPriorityON() &&
					(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {
					NackBuzzer();
					break;
				}
			}
			else {									/*	指令モート,警電側無効 */
				if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
					NackBuzzer();
					break;
				}
			}
			
  #if 0 /* 通信起動によって不具合現象の対応 警察FAX Modified by SMuratec L.Z.W 2005/09/16 */
**			if (CheckFaxComExecute()) {					/*	通信中	*/
  #else
   #if (0)		/* 警察FAX DVT_ID43 Modify by SMuratec K.W.Q 2005/11/15 */
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {					/*	通信中	*/
   #else
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) ||
  				/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
  				IsSHIREIKido ||
				(FaxComCompleted == FALSE)) {										/*	通信中	*/
   #endif
  #endif
				NackBuzzer();
				break;
			}

			if (CheckIsKanyuLine()) {
				SYS_InternalLineNumber = SYS_STD_LINE_COM;

				FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
				
				if (CheckIsScrambleOFF() || (CMN_CheckScrambleSwOn() == FALSE)) {
					FCM_ExecutingS1Info.Available = FALSE;
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
				else {
					FCM_ExecutingS1Info.Available = TRUE;
					
					if (CheckIsSenyou()) {
						FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
					}
					else {
						FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
					}
				}

				switch (TelControl.NcuStatus & (OPR_HOOKKEY_OFFHOOK | OPR_TEL1_OFFHOOK)) {
				case OPR_HOOKKEY_OFFHOOK:
					ManualTRxOperation();
					break;
				case OPR_TEL1_OFFHOOK:
					if (CMN_CheckHDSTOnSTD()) {
						ManualTRxOperation();
					}
					else {
						NackBuzzer();
					}
					break;
				default:
					NackBuzzer();
					break;
				}
			}
			else {
				SYS_InternalLineNumber = SYS_EXT_LINE_COM;

				if (CheckIsKobetsuMode()) {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;
				}
				else {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
					if (SYB_ModeSw == SYS_SFINE) {
						SYB_ModeSw = SYS_FINE;
						ModeLedOn();
					}
				}

				if (CheckIsScrambleOFF() || (CMN_CheckScrambleSwOn() == FALSE)) {
					FCM_ExecutingS1Info.Available = FALSE;
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
				else {
					FCM_ExecutingS1Info.Available = TRUE;
					
					if (CheckIsSenyou()) {
						FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
					}
					else {
						FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
					}
				}
				switch (TelControl.NcuStatus & (OPR_HOOKKEY_OFFHOOK | OPR_TEL2_OFFHOOK)) {
				case OPR_HOOKKEY_OFFHOOK:
					ManualTRxOperation();
					break;
				case OPR_TEL2_OFFHOOK:
					if (CMN_CheckHDSTOnEXT()) {
						ManualTRxOperation();
					}
					else{
						NackBuzzer();
					}
					break;
				default:
					NackBuzzer();
					break;
				}
			}
			break;
#else
			switch (TelControl.NcuStatus) {
			case OPR_TEL1_OFFHOOK:
			case OPR_HOOKKEY_OFFHOOK:
				ManualTRxOperation();
				break;
			case OPR_TEL2_OFFHOOK:
				if (CHK_UNI_TEL2_AvailableStartKey()) {	/* ＴＥＬ２からの手動送受信が可能な時 */
					ManualTRxOperation();
				}
				else {
					NackBuzzer();
				}
				break;
			default:
				NackBuzzer();
				break;
			}
			break;
#endif		/* End of (defined (KEISATSU)) */

		case REDIAL:				/* リダイヤルキー	*/
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
			if (CMN_CheckAramcoModel() == 1) {	/* UAE ARAMCO PIN By O.Kimoto 1997/04/16 */
				NackBuzzer();
				break;
			}
#endif
		case NUMBER:				/* 数字キー			*/
		case AST:					/* アスタリスクキー	*//*PIN注意*/
		case SHARP:					/* シャープキー		*/
		case ONETOUCH:				/* ワンタッチキー	*/
		case SPEED:					/* 短縮キー			*/
		case DIALMARK:				/* ダイヤル記号キー	*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/23 */
			/* 警察FAX DVT_ID58 Added by SMuratec 夏 2005/12/07 
			** 秘話機能では外付電話を先に上げるの場合、
			** パネルでテンキー、ワンタッチキー、短縮キー、Startキーなど無効になる
			*/
			if ((((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_EXT) && CheckIsKanyuLine()) ||
				(((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_EXT) && !CheckIsKanyuLine())){
				NackBuzzer();
				break;
			}
			
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
				NackBuzzer();
				break;
			}

			if (CheckIsKanyuLine()){					/*	警電受話中（警電優先受信）,加入側無効 */
				if (CheckKeidenRxPriorityON() &&
					(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {
					NackBuzzer();
					break;
				}
			}
			else {									/*	指令モート,警電側無効 */
				if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
					NackBuzzer();
					break;
				}
			}
			
			switch (TelControl.NcuStatus) {
			case OPR_TEL1_OFFHOOK:
				if (!CMN_CheckHDSTOnSTD()) {
					NackBuzzer();
					continue;
				}
				break;
			case OPR_TEL2_OFFHOOK:
				if (!CMN_CheckHDSTOnEXT()) {
					NackBuzzer();
					continue;
				}
				break;
			case OPR_TEL1_TEL2_OFFHOOK:
			/*	if ((!CMN_CheckHDSTOnSTD()) || (!CMN_CheckHDSTOnEXT())) { */
				if ((!CMN_CheckHDSTOnSTD()) && (!CMN_CheckHDSTOnEXT())) {	/* 修正 by SMuratec 夏 2005/09/15 */

					NackBuzzer();
					continue;
				}
				break;
			default:
				break;
			}

#endif		/* End of (defined (KEISATSU)) */
#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE:					/* トーンキー		*/	/* 追加 97/11/13 T.Fukumoto */
#endif
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH:					/* フラッシュキー	*/
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
		case MERCURY:				/* マーキュリーキー	*/
#endif
#if defined(DEU)
		case GROUND:				/* GROUNDキー	*/
#endif
			switch (TelControl.NcuStatus) {
			case OPR_LINE_HOLD:
			case OPR_LINEHOLDTEL1UP:
				NackBuzzer();
				break;
#if !defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/12 */
			case OPR_TEL2_OFFHOOK:
				CommandOperation(key, keytype);
				break;
#endif		/* End of (defined (KEISATSU)) */
			default:
				switch (keytype) {
				case NUMBER:	/* 数字０ー９キーの場合 */
				case AST:		/* アスタリスクキーの場合 */
				case SHARP:		/* シャープキーの場合 */
/* 警察FAX DVT Added by SMuratec 夏 2005/12/20 
** 指令信号OFF処理期間、警電側パネルで特番キーの押下が禁止する
*/
#if defined(KEISATSU)
					if (FaxComCompleted == FALSE){
						NackBuzzer();
						break;
					}
  					/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
  					if (IsSHIREIKido) {
						NackBuzzer();
						break;
					}
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /*（ダイヤル中のトーンキーが V650と同じくなります）Added by SMuratec L.Z.W 2003/10/21 */
					CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
					if (((ast_count == 0) && (key == TEN_AST_KEY))		/* 初回のアスタリスク */
					 && (CHK_MultiPhoneType(0) != LINE_TYPE_TONE)) {			/* パルス回線 */
							TelControl.Buffer[0] = '-';
							TelControl.Buffer[1] = '!';
							ast_count = 1;
					}
					else { /* シャープまたは数字 */
						/* そのままダイアルバッファにセットする */
						TelControl.Buffer[0] = key;
					}

					/** 電話番号をダイアルバッファにセットする */
					SetDialingBuffer();
#else
					DirectDialStart(key);

 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/25 */
  #if 0 /* 通信起動によって不具合現象の対応 警察FAX Modified by SMuratec L.Z.W 2005/09/16 */
  **				if ((!CheckFaxComExecute()) && CheckRemoteTransfer(key)) {
  #else
   #if (0)		/* 警察FAX DVT_ID43 Modify by SMuratec K.W.Q 2005/11/15 */
  					if ((!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) && CheckRemoteTransfer(key)) {
   #else
    /* 警察FAX DVT Modify by SMuratec 夏 2005/12/20 
    ** 無用の判断条件を削除する。
    */
    #if 0	
    
					if ((!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) &&
						(FaxComCompleted == TRUE) &&
						CheckRemoteTransfer(key)) {
	#else
					if (CheckRemoteTransfer(key)) {
	#endif
   #endif
  #endif
						if ((CMN_CheckMultiLineReceiveEnable() == TRUE) && (CTRY_NonePaperRx() != 0)) {	/** 代行受信可能 */
  #if (PRO_DEPART_NEW_LIST == ENABLE)  /* Added By S.Fukui Dec.4,1997 */
									if (CHK_DepartmentON()
									 && CHK_UNI_ManualRxTimeManage()) {
										if ( DepartmentCodeOperation() == NG ) {
											return;
										}
									}
  #endif
							OperationMessageToMain.Message = MSG_MANUAL_RX;
							snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
							MainTaskExecWait();
						}
					}
 #endif		/* End of (defined (KEISATSU)) */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
					break;
				case ONETOUCH:	/* ワンタッチキーの場合 */
					OnetouchDialStart(key);	/* ワンタッチダイアル発呼 */
					break;
				case SPEED:		/* 短縮キーの場合 */
					SpeedTelOperation();
					break;
				case REDIAL:	/* リダイアルキーの場合 */
					RedialStart();	/* リダイアル発呼 */
					break;
				case DIALMARK:	/* ダイアル記号キーの場合	*/
#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
				case TONE:		/* トーンキーの場合 		*/	/* 追加 97/11/13 T.Fukumoto */
#endif

					DialMarkStart(TONE_MARK);	/* シグナルチェンジ */
					break;
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
				case FLASH:		/* フラッシュキーの場合 */
					DialMarkStart(FLASH_MARK);	/* フラッシュ記号をセット */
					break;
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
				case MERCURY:	/* マーキュリーキーの場合 */
					if (SYS_DialingNumber.Buffer[0] == NULL && SYB_MercuryDialBuffer[0] != NULL) {
						DialMarkStart(MERCURY_MARK);
					}
					else {
						NackBuzzer();
					}
					break;
#endif
#if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
				case GROUND:
					if(CHK_UNI_GroundkeyCheck()){
						DialMarkStart(PAUSE_MARK);
					}else{
						NackBuzzer();
					}
					break;
#endif
				default:
					break;
				}
				break;
			}
			break;

		/* ＴＥＬ２使用中に送信予約が可能な時のために、以下のキーを追加しました（電話中は無関係です） */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/01 */
		case PROGRAM:		/* プログラムワンタッチキー	*/
			switch (key){
			case ONETOUCH_27_KEY:			/* 警電/加入 */	/* ワンタッチ２７キー		*/
				if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) ||
					(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) ||
					(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK)) {
					NackBuzzer();
					break;
				}
				KeidenKeyOperation();
				if (CheckTelephoneUsing()) {
					TelOperationInitial();	/* ダイアルバッファ・オペレーションバッファのクリア処理 */
					break;
				}
				else {
					return;
				}

				break;
			case ONETOUCH_28_KEY:			/* 一斉/個別 */	/* ワンタッチ２８キー		*/
				IsseiKeyOpration();
				break;
			case ONETOUCH_29_KEY:			/* スクランブル */	/* ワンタッチ２９キー		*/
				ScramblerKeyOpration();
				break;
			case ONETOUCH_30_KEY:			/* 共通/専用 */	/* ワンタッチ３０キー		*/
				KyotsuKeyOpration();
				break;
			default:
				NackBuzzer();
				break;
			}
			UpdateLCD();
			
			break;
#else
		case PROGRAM:				/* プログラムキー	*/
#endif		/* End of (defined (KEISATSU)) */
		case GROUP:					/* グループキー		*/
		case BROADCAST:				/* 同報キー			*/
		case SPECIAL:				/* 応用通信キー		*/
		
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/11 */
			NackBuzzer();
			break;
#else
			switch (TelControl.NcuStatus) {
			case OPR_TEL2_OFFHOOK:
				CommandOperation(key, keytype);
				break;
			default:
				NackBuzzer();
				break;
			}
			break;
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_FBS == ENABLE)
		case BOOK_DOC_SIZE:			/* ブック原稿サイズキー */
			if (SYB_MaintenanceSwitch[MNT_SW_B4] & FBS_REALTIME_TX) {	/* ＦＢＳからのリアルタイム送信可能な時 */
				BookDocumentSizeSet(OPR_TEL_OPE, last_key);
			}
			else {
				NackBuzzer();
			}
			break;
#endif

		case SINGLE:
			SingleKeyOperation(key);
			break;

		case NO_EFFECT:
			if (key == OPR_TELBOOK_TEL) {
				/*--------------*/
				/* 電話帳発呼	*/
				/*--------------*/
				/* このパスを通るのはコマンドオペレーションで電話帳オペレーションを行い、
				** 原稿無し等で  送信できず電話発呼に変更する場合のみである
				*/
				if (TelControl.NcuStatus == OPR_NCU_IDLE) {	/* 電話は全てオンフック */
					HookKeySet();
					telbook_wait_hook = 1;
				}
				number = (UWORD)SYB_TelephoneBookData[GetTelBookDataPoint()][OPR_TELBOOK_DATANUMBER];
				if (number < SYS_ONETOUCH_MAX) {
					OnetouchDialStart(CMN_OffsetToOnetouchCode((UBYTE)number));
				}
				else {
					number -= SYS_ONETOUCH_MAX;
					SpeedDialStart((UBYTE)number);
				}
			}
			break;

		case ERROR_OPERATION:	/* 現在の状態では無効なキー */
			NackBuzzer();
			break;

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
		case KEY_TIME_UP:	/* 現在の状態では無効なキー */
			if ( IsCopyReserved && IsScanReserved ) {
				break;
			}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if defined (KEISATSU)		/* 警察FAX DVT Modify by SMuratec K.W.Q 2005/11/14 */
		case KEY_TIME_UP:	/* 現在の状態では無効なキー */
			if (AttributeTimeoutCheck &&
				(!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) && 
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) &&
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK))) {

				SetKeisatsuSettings();
				AttributeTimeoutCheck = 0;
				NCU_HdstShift();
#if 0	/* 警察FAX DVT Deleted by SMuratec 夏 2005/12/17 */
				UpdateLCD();
#endif
			}
			break;
#endif		/* End of (defined (KEISATSU)) */

		default:
			NackBuzzer();
			break;
		}

		if (CheckChildErrorDisplayReq() == TRUE) {	/* エラー等のチャイルド表示要求がある時 */
			DisplayChildError();	/* チャイルド表示実行 */
		}

		/* メモリーオーバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER_OPR) {
			MemoryOverOperation();
		}

		/* ジャムリカバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR) {
			JamRecoverOperation(SCN_ADF);
		}

		/* ＦＢＳ読み取り中断リカバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR) {
			JamRecoverOperation(SCN_FBS);
		}

#if (PRO_FBS == ENABLE)
		/* 次原稿蓄積確認処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR) {
			NextDocStoreOperation();
		}
#endif

#if (PRO_CIPHER == ENABLE)
		/* 復号化時キー間違い処理 */
		if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_WRONG_KEY_ERROR) {
			DifferentKeyOperation();
		}

		/** 受信暗号化原稿消去確認処理 by K.Watanabe 1998/07/08 */
		if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_FIRST_PAGE) {
			EraseRxCipherDocOperation();
		}
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
		if ( IsCopyReserved && IsScanReserved ) {
			if	( !QueryDs1On() /* 原稿がない */
				 || ( !QueryDocPosition() )
				 || (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)
				 || (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
				) {
				IsScanReserved = FALSE;
			}
			else if ( (OPR_Buf.CopyCtrl.NumberInputFlag == 0) ) {/* リアルタイムコピー */
				if ( !(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
				 	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
				 	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_INK)
				 	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM)
				 	 && !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)
					) { 
					IsScanReserved = FALSE;
					MultiCopyOperation();
				}
			}
			else if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
				IsScanReserved = FALSE;
				MultiCopyOperation();
			}
		}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

		/* 電話中に他のオペレーションを実行し、その間に電話が下がっていたら終了する */
		if ((telbook_wait_hook == 0) && (CheckTelephoneStatus() == OPR_END)) {
#if (PRO_FBS == ENABLE)
			if (SYB_MaintenanceSwitch[MNT_SW_B4] & FBS_REALTIME_TX) {	/* ＦＢＳからのリアルタイム送信可能な時 */
				if (IsBookDocSizeSet) {	/* 手動送信用のブック原稿サイズが設定されている時 */
					IsBookDocSizeSet = FALSE;	/* ブック原稿サイズを未設定に初期化 */
				}
			}
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/09 */
			/* モードを元に戻します */
			if (bak_mode != CHK_ReadyModeCopy()) {	/* 現在のモードと、電話状態になる前のモードが違う時 */
				CopyFaxKeyOperation();
			}
#endif
			return;
		}
		
		/* 1回線外付電話を上げて、呼出対応付属電話切替 警察FAX Added start by SMuratec 夏 2005/09/15 */
		switch (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & (SYS_STD_LINE_IN_RECEIVE | SYS_EXT_LINE_IN_RECEIVE)) {
		case SYS_STD_LINE_IN_RECEIVE:
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
				
				AttributeTimeoutCheck = 1;
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_LINE;
			}
			break;
		case SYS_EXT_LINE_IN_RECEIVE:
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {

				AttributeTimeoutCheck = 1;
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_LINE;
			}
			break;
		case (SYS_STD_LINE_IN_RECEIVE | SYS_EXT_LINE_IN_RECEIVE):
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
				
				AttributeTimeoutCheck = 1;
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_LINE;
			}
			else if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {

				AttributeTimeoutCheck = 1;
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_LINE;
			}
			break;
		default:
			break;
		}
		/* 警察FAX Added end */

	}
}

/*************************************************************************
	module		:[電話オペレーション初期化処理]
	function	:[
		1.電話番号入力用バッファのクリアを行う
	]
	return		:[]
	common		:[
				SYS_DialingNumber
				]
	condition	:[]
	comment		:[Ｈ８から流用]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/17]
	author		:[江口]
*************************************************************************/
void TelOperationInitial(void)
{
	/************************/
	/* バッファのクリア処理 */
	/************************/
	/* ダイヤルバッファのストラクトの初期化 */
#if defined(KEISATSU)	/* 警察FAX DVT_ID34 Modify by SMuratec 夏 2005/11/10 */	
	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
		CMN_MemorySet(SYS_DialingNumber.Buffer, DIALING_NUMBER_MAX, 0);
		SYS_DialingNumber.ReadPointer = SYS_DialingNumber.WritePointer = 0;
	}
#else	
	CMN_MemorySet(SYS_DialingNumber.Buffer, DIALING_NUMBER_MAX, 0);
	SYS_DialingNumber.ReadPointer = SYS_DialingNumber.WritePointer = 0;
#endif
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/23 */
	CMN_MemorySet(TEL_ManualTxNumber.Buffer, DIALING_NUMBER_MAX, 0);
	TEL_ManualTxNumber.ReadPointer = TEL_ManualTxNumber.WritePointer = 0;
#endif		/* End of (defined (KEISATSU)) */

	/* オペレーションバッファのストラクトの初期化 */
	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, 0);
	CMN_MemorySet(TelControl.SpeedBuffer, 5, 0);		/* 短縮番号入力バッファ */
	TelControl.SpeedPosition = 0;						/* 短縮番号入力桁数 */
	TelControl.NcuStatus = CheckLineStatus();			/* 回線回りの状態 */
#if (PRO_PIN_ACCESS == ENABLE)
	TelControl.PinAccessMode = CHK_PIN_AccessMode();	/* ＰＩＮアクセスモード */
#else
	TelControl.PinAccessMode = PIN_ACCESS_OFF;
#endif
	TelControl.PinNumberDialFlag = 0;					/* ＰＩＮ番号送出済みフラグ */
	CMN_MemorySetNULL(TelControl.AfterPinDialDisplayBuffer, OPR_DISPLAY_MAX, ' ');

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
	if (CMN_CheckAramcoModel() == 1) {
		UAE_PIN_FirstSharpCode = 0;			/* UAE ARAMCO PIN By O.Kimoto 1997/04/16 */
		UAE_PIN_1stSharpPosition = 0xffff;	/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
		UAE_PIN_2ndSharpPosition = 0xffff;	/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
		UAE_PIN_CopiedSrcBufferPosition = 0;/* UAE ARAMCO PIN By O.Kimoto 1997/05/21 */
		UAE_PIN_RoundFlag = 0;				/* UAE ARAMCO PIN By O.Kimoto 1997/06/04 */
	}
#endif
}

/*************************************************************************
	module		:[電話の状態を調べる]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
UBYTE CheckTelephoneStatus(void)
{
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/12 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) && CheckIsKanyuLine()) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && !(CheckIsKanyuLine()))) {

 #if 0	 /* 警察FAX DVT Modify by SMuratec 夏 2005/12/17 */
		return (OPR_CONTINUE);
 #else
		if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) == 0){
			return (OPR_CONTINUE);
		}
		else{
			if ((Hangup_Line & SYS_TWICE_LINE_HANGUP) == SYS_TWICE_LINE_HANGUP){
				return (OPR_END);
			}
			else if (((Hangup_Line & SYS_LINE_KANYU_HANGUP) && !CheckIsKanyuLine())||
		  		((Hangup_Line & SYS_LINE_KEIDEN_HANGUP) && CheckIsKanyuLine())){
				return (OPR_CONTINUE);
			}
			else{
				return (OPR_END);
			}
		}
 #endif
	}
	else {
		CursorOff();
		TelOperationInitial();
		return (OPR_END);
	}
#else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_TELEPHONE) { /** 電話状態 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) { /** フックキーオフフック */
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			HookLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK)) {
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			HookLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return (OPR_CONTINUE);
	}
	else {	/**電話オペレーション終了(電話が下げられた)*/
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		HookLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		CursorOff();
		TelOperationInitial();
		return (OPR_END);
	}
#endif		/* End of (defined (KEISATSU)) */
}

/************************************************************************
	module		:[回線回りの状態を取り出す]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/28]
	author		:[江口]
************************************************************************/
UBYTE CheckLineStatus(void)
{
	UWORD	ncu_status;

	ncu_status = SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & (SYS_TEL1_OFF_HOOK     |
															  SYS_TEL2_OFF_HOOK     |
															  SYS_HOOK_KEY_OFF_HOOK |
															  SYS_LINE_HOLD);

#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/23 */
	if (ncu_status == 0) {							/* 待機状態 */
		/* コマンドオペレーションで電話帳オペレーションを行い、記録紙なしで電話発呼にいくときしかあり得ない */
		return (OPR_NCU_IDLE);
	}
	else if (ncu_status == SYS_TEL1_OFF_HOOK) {		/* ＴＥＬ１オフフック */
		return (OPR_TEL1_OFFHOOK);
	}
	else if (ncu_status == SYS_TEL2_OFF_HOOK) {		/* ＴＥＬ２オフフック */
		return (OPR_TEL2_OFFHOOK);
	}
	else if (ncu_status == SYS_HOOK_KEY_OFF_HOOK) {	/* フックキーオフフック */
			return (OPR_HOOKKEY_OFFHOOK);
	}
	else if (ncu_status == (SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK)) {
			return (OPR_TEL1_TEL2_OFFHOOK);
	}
	else if (ncu_status == (SYS_TEL1_OFF_HOOK | SYS_HOOK_KEY_OFF_HOOK)) {
			return (OPR_TEL1_HOOK_OFFHOOK);
	}
	else if (ncu_status == (SYS_TEL2_OFF_HOOK | SYS_HOOK_KEY_OFF_HOOK)) {
			return (OPR_TEL2_HOOK_OFFHOOK);
	}
	else if (ncu_status == SYS_LINE_HOLD) {			/* 回線保留中 */
		return (OPR_LINE_HOLD);
	}
	else if (ncu_status == (SYS_TEL1_OFF_HOOK | SYS_LINE_HOLD)) {	/* ＴＥＬ１オフフックで回線保留中 */
		return (OPR_LINEHOLDTEL1UP);
	}
#else
	if (ncu_status == 0) {							/* 待機状態 */
		/* コマンドオペレーションで電話帳オペレーションを行い、記録紙なしで電話発呼にいくときしかあり得ない */
		return (OPR_NCU_IDLE);
	}
	else if (ncu_status == SYS_TEL1_OFF_HOOK) {		/* ＴＥＬ１オフフック */
		return (OPR_TEL1_OFFHOOK);
	}
	else if (ncu_status == SYS_TEL2_OFF_HOOK) {		/* ＴＥＬ２オフフック */
		if (CHK_UNI_TEL2_TEL1Action()) {	/* ＴＥＬ２をＴＥＬ１と同じ動作をさせる時 */
			return (OPR_TEL1_OFFHOOK);
		}
		else {								/* ＴＥＬ１とＴＥＬ２で別々の動作をさせる時 */
			return (OPR_TEL2_OFFHOOK);
		}
	}
	else if (ncu_status == SYS_HOOK_KEY_OFF_HOOK) {	/* フックキーオフフック */
			return (OPR_HOOKKEY_OFFHOOK);
	}
	else if (ncu_status == SYS_LINE_HOLD) {			/* 回線保留中 */
		return (OPR_LINE_HOLD);
	}
	else if (ncu_status == (SYS_TEL1_OFF_HOOK | SYS_LINE_HOLD)) {	/* ＴＥＬ１オフフックで回線保留中 */
		return (OPR_LINEHOLDTEL1UP);
	}
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	/*
	** ＴＥＬ２保留中を保留キー入力で解除できない 
	** ＨＩＮＯＫＩのＮＣＵは、ＴＥＬ１、ＴＥＬ２のＯＨが区別できるので、
	** ＴＥＬ２をＴＥＬ１と同じ動作をさせる時は、ＴＥＬ２オフフックで回線保留中の場合、
	** ＴＥＬ１オフフックで回線保留中の場合と同じ返り値とする by H.Hirao 1999/03/25
	*/
	else if (ncu_status == (SYS_TEL2_OFF_HOOK | SYS_LINE_HOLD)) {	/* ＴＥＬ２オフフックで回線保留中 */
		if (CHK_UNI_TEL2_TEL1Action()) {	/* ＴＥＬ２をＴＥＬ１と同じ動作をさせる時 */
			return (OPR_LINEHOLDTEL1UP);
		}
		else {								/* ＴＥＬ１とＴＥＬ２で別々の動作をさせる時 */
			return (OPR_LINEHOLDTEL1UP);	/* ここには来ない */
		}
	}
#endif
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[フックキーセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void HookKeySet(void)
{
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/29 */
	if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
		if (SYS_HookKeyFlagBk == 0) {
			SYS_HookKeyFlagBk = 1;
		}
	}
	else {
		if (SYS_HookKeyInputFlag == 0) {
			SYS_HookKeyInputFlag = 1;
		}
	}
#else /* !defined (KEISATSU) */
	if (SYS_HookKeyInputFlag == 0) {
		SYS_HookKeyInputFlag = 1;
	}
#endif /* defined (KEISATSU) */
}

/*************************************************************************
	module		:[保留キーセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void HoldKeySet(void)
{
	if (SYS_HoldKeyInputFlag == 0) {
		SYS_HoldKeyInputFlag = 1;
	}
}

/*************************************************************************
	module		:[短縮オペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void SpeedTelOperation(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	number;
#endif
	UWORD	number;
	UWORD	speed;

	/** 短縮番号の入力等を行う。*/
	switch (SpeedOperationSelect()) {
	case 0: /** 終了 */
		return;

	case 1: /** 短縮発呼実行 */

		speed = CMN_ASC_ToUnsignedInt(&TelControl.SpeedBuffer[1], SPEED_FIGURE_MAX);
		CMN_MemorySet(TelControl.SpeedBuffer, 5, NULL);
		TelControl.SpeedPosition = 0;

		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮 */
			if (speed < OPR_SPEED_DIAL_MIN || speed > SYS_SPEED_DIAL_MAX) {/** 正しくない */
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
				NackBuzzer();
				return; /** 終了 */
			}
			/*短縮番号：入力は１から、内部処理は０から*/
			speed -= OPR_SPEED_DIAL_MIN;
		}
		else{			/* 任意短縮の時 */
			if ( speed > OPR_OPTIONAL_SPEED_MAX) {	/** 正しくない */
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
				NackBuzzer();
				return; /** 終了 */
			}
			speed = (UWORD)SetOptionalSpeedStatus(speed);
		}
		SpeedDialStart((UBYTE)speed); /* 発呼処理 */
		break;

	case 2: /** 電話帳オペレーション実行 */
		if (TelephoneBookOperation(OPR_TEL_OPE) == TELBOOK_TEL) { /** 電話帳発呼 */
			number = (UWORD)SYB_TelephoneBookData[GetTelBookDataPoint()][OPR_TELBOOK_DATANUMBER];
			if (number < SYS_ONETOUCH_MAX) {	/** ワンタッチの場合 */
				/** ワンタッチダイアル発呼 */
				OnetouchDialStart(CMN_OffsetToOnetouchCode((UBYTE)number));
			}
			else {								/** 短縮の場合 */
				/** 短縮発呼 */
				number -= SYS_ONETOUCH_MAX;
				SpeedDialStart((UBYTE)number);
			}
		}
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[短縮オペレーション選択]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
UBYTE SpeedOperationSelect(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/** 短縮入力バッファをクリア */
	CMN_MemorySet(TelControl.SpeedBuffer, 5, NULL);
	TelControl.SpeedPosition = 0;

	/** 短縮記号を先頭にセット */
	TelControl.SpeedBuffer[TelControl.SpeedPosition++] = OPR_SPEED_MARK;

	while (1) {
		/**表示処理 */
		DisplayNCUStatus();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {/** 取り込んだキ処理 */

		case NUMBER: /** 数字：０ー９*/
			TelControl.SpeedBuffer[TelControl.SpeedPosition++] = key;
			if (TelControl.SpeedPosition > SPEED_FIGURE_MAX) {	/** 短縮の桁数分入力された */
				/** 終了:短縮ダイアル発呼 */
				return (1);
			}
			break;

		case SPEED: /** 短縮キー */
			if (TelControl.SpeedPosition == 1 && TelControl.SpeedBuffer[0] == OPR_SPEED_MARK) {
				/** ２回連続短縮キーが入力された*/
				CMN_MemorySet(TelControl.SpeedBuffer, 5, NULL);
				TelControl.SpeedPosition = 0;
				/** 終了：電話帳オペレーション */
				return (2);
			}
			else {
				/** 短縮番号入力中に短縮キーがおされた場合、もう一度最初から短縮番号を入力し直す */
				CMN_MemorySet(TelControl.SpeedBuffer, 5, NULL);
				TelControl.SpeedPosition = 0;
				TelControl.SpeedBuffer[TelControl.SpeedPosition++] = OPR_SPEED_MARK;
			}
			break;

		case STOP:	/** ストップ */
		case KEY_TIME_UP:/** タイムアップ */
			/** 短縮入力終了 */
			CMN_MemorySet(TelControl.SpeedBuffer, 5, NULL);
			TelControl.SpeedPosition = 0;
			return (0);

		case HOOK: /** フックキー */
			/** フック状態をセット */
			HookKeySet();
			/** 終了 */
			return (0);
			/* 短縮バッファはクリアしない *//*表示がちらつく可能性あり */

		case CLEAR:
			TelControl.SpeedPosition--;
			TelControl.SpeedBuffer[TelControl.SpeedPosition] = NULL;
			if (TelControl.SpeedPosition == 0 && TelControl.SpeedBuffer[0] == NULL) { /** 全て消去した */
				/** 終了 */
				return (0);
			}
			break;

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}

#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/12 */
	if (!((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) && CheckIsKanyuLine()) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && !(CheckIsKanyuLine())))) {
		
		return (0);
	}
#else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_TELEPHONE)) { /** 受話器下がり */
			/* 短縮バッファはクリアしない *//*表示がちらつく可能性あり */
			return (0);
		}
#endif		/* End of (defined (KEISATSU)) */
	}
}

/*************************************************************************
	module		:[手動送受信オペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口,渡辺一章]
*************************************************************************/
void ManualTRxOperation(void)
{
	if (SYS_DialingNumber.ReadPointer != SYS_DialingNumber.WritePointer) {	/** ダイアル未完了 */
		/** スタートキー無効：終了 */
		NackBuzzer();
		return;
	}

	if (CMN_CheckFeederCommandEmpty() == FALSE) {	/** スキャナ予約コマンドあり */
		/** スタートキー無効：終了 */
		NackBuzzer();
		return;
	}

#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/04/17 */
	/* 暗号化・復号化実行中の、手動送受信は禁止します（ソフトコーデックの関係で正しく動作できない為） */
	if (CheckCipherExecuting() == TRUE) {	/* スクランブル中・デスクランブル中の時 */
		NackBuzzer();
		return;
	}
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正 Added by SMuratec 李 2004/11/10 for Tx Motor */
#if 0 /* QAT修正:プリンタ中と予約中に強制受信させる事 by SMuratec 李 2004/11/16 */
**	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY
**		|| IsScanReserved) {
**		IsScanTx = TRUE;
**	}
#endif
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
 
	/* ＡＤＦ（ＦＢＳ）に原稿がセットされている場合は、手動送信を行います */
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/25 */
	if ((CheckScanStartEnable(OPR_DOC_SET_CHK_MANUAL_TRX) == OPR_SCAN_ENABLE) 	/** スキャン可能 */
	 || (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT))					/** プリヒート中 */
#else
	if (CheckScanStartEnable(OPR_DOC_SET_CHK_MANUAL_TRX) == OPR_SCAN_ENABLE) 	/** スキャン可能 */
#endif
	{

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正 Added by SMuratec 李 2004/11/10 for Tx Motor */
#if 0 /* QAT修正:プリンタ中と予約中に強制受信させる事 by SMuratec 李 2004/11/16 */
**		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY
**			|| IsScanReserved) {
**			NackBuzzer();
**			return;
**		}
#endif
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
 
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/25 */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
			/* プリヒート中のときは手動送信不可 */
			if (CMN_CheckDocumentOnFeeder() == TRUE) {
				NackBuzzer();
				return;
			}
			else {
				/* 手動受信を実行 */
				OperationMessageToMain.Message = MSG_MANUAL_RX;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				return;
			}
		}
#endif

 #if (PRO_DEPART_NEW_LIST == ENABLE)  /* Added By S.Fukui Dec.4,1997 */
		if (CHK_DepartmentON()
		 && CHK_UNI_ManualTxTimeManage()) {
			if ( DepartmentCodeOperation() == NG ) {
				return;
			}
		}
 #endif
		/** 手動送信を実行 */

		OperationMessageToMain.Message = MSG_MANUAL_TX;
		snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
		MainTaskExecWait();
	}
	/* ＡＤＦ（ＦＢＳ）に原稿がセットされていない場合は、手動受信を行います */
	else {																		/** スキャン不可能 */
#if (PRO_MULTI_LINE == DISABLE)
 #if(PRO_CODEC_NUMBER == CDC_SINGLE)	/* デュアル・トリプル動作の制限対策 1997/11/03 Y.Matsukuma */
		if ((CMN_CheckMultiLineReceiveEnable() == TRUE) 
			&& (CTRY_NonePaperRx() != 0) 
			&& (OPR_ChildErrorFlag != PRINTER_IN_USE_ERROR)) {
 #else
  #if (PRO_PRINTER_RX == ENABLE)
		if (((CMN_CheckMultiLineReceiveEnable() == TRUE) && (CTRY_NonePaperRx() != 0))
		  || QueryPRxEnable()) {	/** 代行受信可能 または、プリンタ受信可能 */
  #else
/*		if ((CMN_CheckMemoryReceiveEnable() == TRUE) && (CTRY_NonePaperRx() != 0)) {	**/ /** 代行受信可能 */
		if ((CMN_CheckMultiLineReceiveEnable() == TRUE) && (CTRY_NonePaperRx() != 0)) {	/** 代行受信可能 */
  #endif
 #endif
			/** 手動受信を実行 */

#if (PRO_DEPART_NEW_LIST == ENABLE)  /* Added By S.Fukui Dec.4,1997 */
			if (CHK_DepartmentON()
			 && CHK_UNI_ManualRxTimeManage()) {
				if ( DepartmentCodeOperation() == NG ) {
					return;
				}
			}
#endif
 #if (PRO_CL1_TELFAX_LAN == ENABLE)	/* S.Fukui Jun 19,1998 */
	/*　着信条件の仕様変更　*/ 
			switch ( CL1_CheckReceiveByFaxOrPC() ) {
			case PC_RECEIVE_OK:
				OperationMessageToMain.Message = MSG_CLASS1_MANUAL_RX;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				break;
			case NO_RECEIVING:
				ChildDisplayStringLow(D2W_PC_FAX_InUse);	
				NackBuzzer();
				break;
			case FAX_RECEIVE_ENABLE:
				CL1_IsTransferInhibit = TRUE;  	/* このオペレーション中に、転送受信しない為 */
				if (ConfirmKeyInputOperation(D2W_ReceiveInFax, D2W_CheckStartStop, START, STOP) == CONFIRM_EXEC) {
					/* 手動受信を実行  */
					CL1_IsTransferInhibit = FALSE;
					OperationMessageToMain.Message = MSG_MANUAL_RX;
					snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
					MainTaskExecWait();	
				}
				CL1_IsTransferInhibit = FALSE;
				break;
   #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */	/* added by H.Hirao 1999/03/04 */
			case NO_RECEIVING_SCANNER_IN_USE:
				ChildDisplayStringLow(D2W_ScannerInUse);	
				NackBuzzer();
				break;
			case NO_RECEIVING_PRINTER_IN_USE:
				ChildDisplayStringLow(D2W_PrinterInUse);	
				NackBuzzer();
				break;
   #endif
			case FAX_RECEIVE_ONLY:
			default:
				/** 手動受信を実行  */
				OperationMessageToMain.Message = MSG_MANUAL_RX;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				break;
			}

 #else
			OperationMessageToMain.Message = MSG_MANUAL_RX;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
 #endif
		}
 #if (PRO_CL1_TELFAX_LAN == ENABLE)	/* PRO_MULTI_LINE == DISABLEの場合、以下のパスが抜けてました by H.Hirao 1999/03/05 */
		else if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {
  #if (PRO_DEPART_NEW_LIST == ENABLE)  /* この操作してもジャーナル記載無しですが、代行受信可の時との操作整合の為入れときます。 S.Fukui */
			if (CHK_DepartmentON() && CHK_UNI_ManualRxTimeManage()) {
				if ( DepartmentCodeOperation() == NG ) {
					return;
				}
			}
  #endif
			OperationMessageToMain.Message = MSG_CLASS1_MANUAL_RX;
			snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
			MainTaskExecWait();
		}
 #endif
		else {																			/** 代行受信不可能 */
			NackBuzzer();
			return;
		}
#else
 #if(PRO_CODEC_NUMBER == CDC_SINGLE)	/* デュアル・トリプル動作の制限対策 1997/11/03 Y.Matsukuma */
		if ((CMN_CheckMultiLineReceiveEnable() == TRUE) 
			&& (CTRY_NonePaperRx() != 0) 
			&& (OPR_ChildErrorFlag != PRINTER_IN_USE_ERROR)) {
 #else
		if ((CMN_CheckMultiLineReceiveEnable() == TRUE) && (CTRY_NonePaperRx() != 0)) {	/** 代行受信可能 */
 #endif
			/** 手動受信を実行 */
 #if (PRO_DEPART_NEW_LIST == ENABLE)  /* Added By S.Fukui Dec.4,1997 */
		if (CHK_DepartmentON()
		 && CHK_UNI_ManualRxTimeManage()) {
			if ( DepartmentCodeOperation() == NG ) {
				return;
			}
		}
 #endif
 #if (PRO_CL1_TELFAX_LAN == ENABLE)	/* S.Fukui June 19,1998 */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
			if (CL1_ExtFunctionEnableFlag == 0) {
				if (CHK_UNI_Class1_EXT_Function()) {
					if ((CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)
		   			   && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM))	/* CLASS1動作中? */
					   && (SYS_CL1_Status == 0) && (CL1_ExtFunctionEnableFlag == 0)) {	/* ｸﾗｽ1拡張が動作中 */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
						CL1_ExtFunctionEnableFlag = 1;
						OperationMessageToMain.Message = MSG_MANUAL_RX;
						snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
						MainTaskExecWait();
					}
					else {
						ChildDisplayStringLow(D2W_PC_FAX_InUse);	
						NackBuzzer();
					}
				}
				else {
					switch ( CL1_CheckReceiveByFaxOrPC() ) {
					case PC_RECEIVE_OK:
						OperationMessageToMain.Message = MSG_CLASS1_MANUAL_RX;
						snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
						MainTaskExecWait();
						break;
					case NO_RECEIVING:
						ChildDisplayStringLow(D2W_PC_FAX_InUse);	
						NackBuzzer();
						break;
					case FAX_RECEIVE_ENABLE:
						CL1_IsTransferInhibit = TRUE;  	/* このオペレーション中に、転送受信しない為 */
						if (ConfirmKeyInputOperation(D2W_ReceiveInFax, D2W_CheckStartStop, START, STOP) == CONFIRM_EXEC) {
							/* 手動受信を実行  */
							CL1_IsTransferInhibit = FALSE;
							OperationMessageToMain.Message = MSG_MANUAL_RX;
							snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
							MainTaskExecWait();	
						}
						CL1_IsTransferInhibit = FALSE;
						break;
    #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */	/* added by H.Hirao 1999/03/04 */
					case NO_RECEIVING_SCANNER_IN_USE:
						ChildDisplayStringLow(D2W_ScannerInUse);	
						NackBuzzer();
						break;
					case NO_RECEIVING_PRINTER_IN_USE:
						ChildDisplayStringLow(D2W_PrinterInUse);	
						NackBuzzer();
						break;
    #endif
					case FAX_RECEIVE_ONLY:
					default:
						/** 手動受信を実行  */
						OperationMessageToMain.Message = MSG_MANUAL_RX;
						snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
						MainTaskExecWait();
						break;
					}
				}
			}
			else {
				ChildDisplayStringLow(D2W_PC_FAX_InUse);	
				NackBuzzer();
			}
  #else
	/*　着信条件の仕様変更　*/ 
			switch ( CL1_CheckReceiveByFaxOrPC() ) {
			case PC_RECEIVE_OK:
				OperationMessageToMain.Message = MSG_CLASS1_MANUAL_RX;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				break;
			case NO_RECEIVING:
				ChildDisplayStringLow(D2W_PC_FAX_InUse);
				NackBuzzer();
				break;
			case FAX_RECEIVE_ENABLE:
				CL1_IsTransferInhibit = TRUE;  	/* このオペレーション中に、転送受信しない為 */
				if (ConfirmKeyInputOperation(D2W_ReceiveInFax, D2W_CheckStartStop, START, STOP) == CONFIRM_EXEC) {
					/* 手動受信を実行  */
					CL1_IsTransferInhibit = FALSE;
					OperationMessageToMain.Message = MSG_MANUAL_RX;
					snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
					MainTaskExecWait();	
				}
				CL1_IsTransferInhibit = FALSE;
				break;
  #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043内蔵のシリアル有効 */	/* added by H.Hirao 1999/03/04 */
			case NO_RECEIVING_SCANNER_IN_USE:
				ChildDisplayStringLow(D2W_ScannerInUse);	
				NackBuzzer();
				break;
			case NO_RECEIVING_PRINTER_IN_USE:
				ChildDisplayStringLow(D2W_PrinterInUse);	
				NackBuzzer();
				break;
  #endif
			case FAX_RECEIVE_ONLY:
			default:
				/** 手動受信を実行  */
				OperationMessageToMain.Message = MSG_MANUAL_RX;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				break;
			}
  #endif	/* PRO_CLASS1_EXT_FUNC 1999/7/27 K.Kawata */
 #else
			OperationMessageToMain.Message = MSG_MANUAL_RX;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
 #endif
		}
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/27 K.Kawata */
		else if ((CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) && (!CHK_UNI_Class1_EXT_Function())) {
  #else
		else if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {
  #endif
  #if (PRO_DEPART_NEW_LIST == ENABLE)  /* この操作してもジャーナル記載無しですが、代行受信可の時との操作整合の為入れときます。 S.Fukui */
			if (CHK_DepartmentON() && CHK_UNI_ManualRxTimeManage()) {
				if ( DepartmentCodeOperation() == NG ) {
					return;
				}
			}
  #endif
			OperationMessageToMain.Message = MSG_CLASS1_MANUAL_RX;
			snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
			MainTaskExecWait();
		}
 #endif
		else {																			/** 代行受信不可能 */
			NackBuzzer();
			return;
		}
#endif	/* (PRO_MULTI_LINE == DISABLE) */
	}

#if (0)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/10 */
//#if (PRO_COPY_FAX_MODE == ENABLE)
//	/* コピーモードで手動送受信された時は、ファクスモードに切り替えます */
//	if (CHK_ReadyModeCopy()) {
//		CopyFaxKeyOperation();
//	}
//#endif
#endif
}

/*************************************************************************
	module		:[ワンタッチダイアル発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void OnetouchDialStart(UBYTE onetouch)
{
	UBYTE	ont_number;
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE	position;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	UBYTE	status;
#endif


	ont_number = CMN_OnetouchCodeToOffset(onetouch);
	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);

	/* ワンタッチが登録されているか調べる */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	status = CheckOnetouchStoreStatus(onetouch);
	if (status == SYS_INF_ONETOUCH_MAILADDRESS) {
		OPR_ChildErrorFlag = MAIL_ADDRESS_STORED_ERROR;
		NackBuzzer();
		return;
	}
	else if (status == SYS_INF_ONETOUCH_NO_ENTRY) {
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		NackBuzzer();
		return;
	}
#else
	if (CheckOnetouchStoreStatus(onetouch) == NG) {	/** 未登録のワンタッチ */
		/** 発呼しない */
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		NackBuzzer();
		return; /* 終了 */
	}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */

	/** ダイアル番号を取り出す。 */
	CMN_BCD_ToASC_String(TelControl.Buffer, SYB_OnetouchDial[ont_number].Dial);
	
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/15 */
	if (CheckIsKanyuLine()) {
		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KANYU;
			}
			else if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KANYU;
			}
			
			if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
			}
			else {
				if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_KYOTSU) {
					SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
				}
				else if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SENYO){
					SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SENYOU;
				}
			}

		}
		else{
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KANYU;
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
		}
	}
	else {
		if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_ISSEI) {
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_MODE;
		}
		else if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_KOBETSU){
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_MODE;
		}

		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KEIDEN;;
			}
			else if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KEIDEN;
			}

			if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KEIDEN) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
			}
			else {
				if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_KYOTSU) {
					SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
				}
				else if (SYB_OnetouchDial[ont_number].Keisatsu & SYS_KEISATSU_SENYO){
					SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SENYOU;
				}
			}
		}
		else{
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KEIDEN;
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
		}
	}
	
	AttributeTimeoutCheck = 1;
	UpdateLCD();
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_PIN_ACCESS == ENABLE)
	if (TelControl.PinNumberDialFlag == 0) { /**  ＰＩＮ番号の送出はしていない */
		if (TelControl.PinAccessMode == PIN_ACCESS_MODE1) { /** 相手先別PINアクセスの場合 */
			/*　ワンタッチダイアルに登録されているＰＩＮ番号を使用する */
			if (CheckOnetouchPinNumberStore(onetouch) == FALSE) {/** PIN番号が登録されていない */
				/** 発呼しない。エラーで終わる */
				OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
				NackBuzzer();
				CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
				return;
			}
			/** ＰＩＮ番号が登録されている場合 */
			/** ＰＩＮ番号を取り出す.TelControl.Bufferのダイアル番号の後にセット  */
			position = CMN_StringLength(TelControl.Buffer);
			TelControl.Buffer[position++] = OPR_PIN_MARK; /*ダイアルとＰＩＮの区切りのコードをセット */
			CMN_BCD_ToASC_StringNum(&TelControl.Buffer[position],
									SYB_OnetouchDial[ont_number].PIN_Number,
									SYS_PIN_MAX * 2);
		}
		else if (TelControl.PinAccessMode == PIN_ACCESS_MODE2) {	/** 個人別ＰＩＮアクセスモードの場合 */
			/* ＰＩＮ番号入力オペレーションを行い、そこで入力されたＰＩＮ番号を使用 */
			position = CMN_StringLength(TelControl.Buffer);
			TelControl.Buffer[position++] = OPR_PIN_MARK;
			/** ＰＩＮ番号を入力させるオペレーション */
			if (TelPinNumberInput(&TelControl.Buffer[position]) == NG) {/** ストップ・タイムアップで終了 */
				/** 発呼しない。終了する */
				CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
				return;
			}
		}
	}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

	/** ダイアル番号（＋ＰＩＮ番号）をダイアルバッファにセットする(ダイアル開始 )*/
	SetDialingBuffer();
}

/*************************************************************************
	module		:[短縮ダイアル発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void SpeedDialStart(UBYTE speed)
{
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE	position;
#endif

	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);

	/* 短縮番号登録状態を調べる */
	if (CheckSpeedStoreStatus(speed) == NG) {	/** 未登録 */
		/** 発呼せずに終了する */
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		NackBuzzer();
		return; /* 終了 */
	}

	/** 登録済みの場合、ダイアル番号を取り出し、TelControl.Bufferにセット */
	CMN_BCD_ToASC_String(TelControl.Buffer, SYB_SpeedDial[speed].Dial);
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/15 */
	if (CheckIsKanyuLine()) {
		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KANYU;
			}
			else if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KANYU;
			}
			
			if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
			}
			else {
				if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_KYOTSU) {
					SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
				}
				else if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SENYO){
					SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SENYOU;
				}
			}
		}
		else{
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KANYU;
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
		}
	}
	else {
		if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_ISSEI) {
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_MODE;
		}
		else if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_KOBETSU) {
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_MODE;
		}

		if (CMN_CheckScrambleSwOn() == TRUE) {
			if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KEIDEN;
			}
			else if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KEIDEN;
			}
			
			if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KEIDEN) {
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
			}
			else {
				if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_KYOTSU) {
					SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
				}
				else if (SYB_SpeedDial[speed].Keisatsu & SYS_KEISATSU_SENYO){
					SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SENYOU;
				}
			}
		}
		else{
			SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KEIDEN;
			SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SENYOU;
		}
	}
	
	AttributeTimeoutCheck = 1;
	UpdateLCD();
#endif		/* End of (defined (KEISATSU)) */


#if (PRO_PIN_ACCESS == ENABLE)
	/* ＰＩＮアクセスのための処理を行う */
	if (TelControl.PinNumberDialFlag == 0) { /**ＰＩＮ番号のダイアルはまだしていない *//*一度PIN番号を送出したらからは通常ダイアルになる */
		if (TelControl.PinAccessMode == PIN_ACCESS_MODE1) { /**相手先別PINアクセスの場合 */
			/* 短縮に登録されているPIN番号を使用する */
			if (CheckSpeedPinNumberStore(speed) == FALSE) {/**PIN番号が登録されていない */
				/** 発呼できない。終了する */
				OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
				NackBuzzer();
				CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
				return;
			}

			/** ＰＩＮ番号が登録されている場合 */
			/** ＰＩＮ番号を取り出す.TelControl.Bufferのダイアル番号の後にセット  */
			position = CMN_StringLength(TelControl.Buffer);
			TelControl.Buffer[position++] = OPR_PIN_MARK; /*ＰＩＮの区切りの＊をセットする */
			CMN_BCD_ToASC_StringNum(&TelControl.Buffer[position],
									SYB_SpeedDial[speed].PIN_Number,
									SYS_PIN_MAX * 2);
		}
		else if (TelControl.PinAccessMode == PIN_ACCESS_MODE2) { /**個人別ＰＩＮアクセスモードの場合 */
			/* ＰＩＮ番号入力オペレーションを行い、そこで入力されたＰＩＮ番号を使用 */
			position = CMN_StringLength(TelControl.Buffer);
			TelControl.Buffer[position++] = OPR_PIN_MARK;
			/** ＰＩＮ番号を入力させる */
			if (TelPinNumberInput(&TelControl.Buffer[position]) == NG) {/** ストップ・タイムアップで終了 */
				/**発呼せずに終了する */
				CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
				return;
			}
		}
	}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

	SetDialingBuffer();
}

/*************************************************************************
	module		:[リダイアル発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void RedialStart(void)
{
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE	position;
#endif

	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);

	if (SYS_DialingNumber.Buffer[0] != NULL || SYB_RedialBuffer[0] == NULL) {
		/**ダイアルバッファが空でなくリダイアルバッファにデータがないとき */
		/**リダイアルキーは無効なので終了する */
		NackBuzzer();
		return;
	}

	/** リダイアルバッファの内容を取り出す */
	CMN_StringCopy(TelControl.Buffer, SYB_RedialBuffer);

#if (PRO_PIN_ACCESS == ENABLE)
	/* PIN番号送出したかどうかの判断は不要*/
	/* ＰＩＮアクセスのための処理 */
	if (TelControl.PinAccessMode == PIN_ACCESS_MODE2) {/* 個人別PINアクセスの場合 */
		/**ＰＩＮ番号入力オペレーションを行う */
		position = CMN_StringLength(TelControl.Buffer);
		TelControl.Buffer[position++] = OPR_PIN_MARK;
		if (TelPinNumberInput(&TelControl.Buffer[position]) == NG) {/** ストップ・タイムアップで終了*/
			CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
			return; /* 終了 */
		}
	}
	else if (TelControl.PinAccessMode == PIN_ACCESS_MODE1) {/* 相手先別PINアクセスの場合*/
		/* リダイアルバッファのなかに＊が含まれているか検索含まれていればＰＩＮの区切りに変換 */
		/* 特に必要な処理ではないが(むしろ無駄）、コマンド登録の時の使用とあわすために追加する*/
		/* 1996/04/04 Eguchi */
		for (position = 0; TelControl.Buffer[position] != NULL; position++) {
			if ((TelControl.Buffer[position] == '*') && (position > 0)) {
				TelControl.Buffer[position] = OPR_PIN_MARK;
				break;
			}
		}
	}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

	/** 電話番号をダイアルバッファにセットする */
	SetDialingBuffer();
}

/*************************************************************************
	module		:[ダイアル記号発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void DialMarkStart(UBYTE mark)
{
	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
	switch (mark) {
	case TONE_MARK:
		TelControl.Buffer[0] = '-';
		TelControl.Buffer[1] = '!';
		break;
	case PAUSE_MARK:
		TelControl.Buffer[0] = '-';
		TelControl.Buffer[1] = '/';
		break;
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH_MARK:
		TelControl.Buffer[0] = '/';
		break;
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/06/28 H,Yagi *//* by K.Watanabe 2004/10/12 */
	case MERCURY_MARK:
		TelControl.Buffer[0] = '!';
		break;
#endif
	}
	SetDialingBuffer();
}

/*************************************************************************
	module		:[ダイレクトダイアル発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void DirectDialStart(UBYTE key)
{
	/* *に注意するだけ */

	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
	if (key == TEN_AST_KEY) {	/** アスタリスクの場合 */
		/* ＰＩＮ番号の始まりかもしれないので注意 */
		if (SYS_DialingNumber.Buffer[0] == NULL) { /**先頭->ダイアルしていない状態 */
			/** そのまま＊を入力 */
			TelControl.Buffer[0] = key;
		}
		else {
			TelControl.Buffer[0] = key;
#if (PRO_PIN_ACCESS == ENABLE)
			if (TelControl.PinNumberDialFlag == 0) {/**ＰＩＮ番号はまだダイアルしていない *//* 区切りの＊がセットされていない */
				if (TelControl.PinAccessMode == PIN_ACCESS_MODE1) { /**相手先別ＰＩＮアクセスモードの場合 */
					/** 区切りのコードをセットする */
					TelControl.Buffer[0] = OPR_PIN_MARK;
				}
				else if (TelControl.PinAccessMode == PIN_ACCESS_MODE2) { /**個人別ＰＩＮアクセスモードの場合 */
					TelControl.Buffer[0] = OPR_PIN_MARK;
					/** ＰＩＮ番号を入力させる */
					if (TelPinNumberInput(&TelControl.Buffer[1]) == NG) {/* ストップ・タイムアップ*/
						CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
						return; /* 終了 */
					}
				}
			}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */
		}
	}
	else { /* シャープまたは数字 */
		/* そのままダイアルバッファにセットする */
		TelControl.Buffer[0] = key;
	}

	/** 電話番号をダイアルバッファにセットする */
	SetDialingBuffer();
}

/*************************************************************************
	module		:[ＰＩＮ番号入力]
	function	:[
		1.個人別ＰＩＮアクセスの時のＰＩＮ番号の入力
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE TelPinNumberInput(UBYTE *set_buffer)
{
	DisplayStringHigh(0, D2W_EnterPinNumber);
	if (PinNumberInput(NULL, SET_PIN_NUMBER) == OK) {
		StoreCharacterInputValue(set_buffer, ASC_DATA_TYPE);
		return (OK);
	}
	return (NG);
}
#endif

/*************************************************************************
	module		:[電話番号をダイアルバッファにセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void SetDialingBuffer(void)
{
	UBYTE	i;
	UBYTE	length;

	/** ダイアルバッファにセットするデータ量を取り出す */
	length = CMN_StringLength(TelControl.Buffer);

	/* ダイアルバッファに展開できるか調べる */
	if (CheckDialingEnable(length) == TRUE) { /** ダイアルバッファにセット可能 */
		for (i = 0; TelControl.Buffer[i] != NULL; i++) {
			/** ダイアルバッファに電話番号をセットしていく */
			if (TelControl.Buffer[i] == OPR_PIN_MARK) { /** セットする番号中にＰＩＮ番号の始まりを示す＊が含まれている場合 */
				/** ＰＩＮ番号をダイアルしたことを示すフラグをセットする */
				/* このフラグは電話が切れるまでさわらないこと */
				/* このフラグがセットされると次からは電話番号の入力がマスクされ、また２度とＰＩＮ番号の送出はされない */
				TelControl.PinNumberDialFlag = 1;
			}
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
			if (CMN_CheckAramcoModel() == 1) {
				/** セットする番号中にＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮの始まりを示す＃が含まれている場合 */
				if (TelControl.Buffer[i] == '#') {
					if (UAE_PIN_1stSharpPosition == 0xffff) {
						UAE_PIN_1stSharpPosition = (UWORD)((UWORD)SYS_DialingNumber.WritePointer 
													+ (UWORD)UAE_PIN_RoundFlag * (UWORD)DIALING_NUMBER_MAX);
					}
					else if (UAE_PIN_2ndSharpPosition == 0xffff) {
						UAE_PIN_2ndSharpPosition = (UWORD)((UWORD)SYS_DialingNumber.WritePointer 
													+ (UWORD)UAE_PIN_RoundFlag * (UWORD)DIALING_NUMBER_MAX);
					}
				}
			}
			SYS_DialingNumber.Buffer[SYS_DialingNumber.WritePointer++] = TelControl.Buffer[i];
			if (SYS_DialingNumber.WritePointer >= DIALING_NUMBER_MAX) {
				SYS_DialingNumber.WritePointer = 0;
				UAE_PIN_RoundFlag ++;	/* UAE ARAMCO PIN  By O.Kimoto 1997/06/04 */
			}
#else
			SYS_DialingNumber.Buffer[SYS_DialingNumber.WritePointer++] = TelControl.Buffer[i];
			if (SYS_DialingNumber.WritePointer >= DIALING_NUMBER_MAX) {
				SYS_DialingNumber.WritePointer = 0;
			}
 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/23 */
			TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer++] = TelControl.Buffer[i];
			if (TEL_ManualTxNumber.WritePointer >= DIALING_NUMBER_MAX) {
				TEL_ManualTxNumber.WritePointer = 0;
			}
 #endif		/* End of (defined (KEISATSU)) */
#endif
		}
		SYS_TxDetectFlag = 1; /*いらんか*/
	}
	else { /** ダイアルバッファにセット不可能  */
		NackBuzzer();
	}
	CMN_MemorySet(TelControl.Buffer, OPR_TELCONTROL_BUFFER_MAX, NULL);
}

/*************************************************************************
	module		:[ダイアル可能かどうか調べる]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
UBYTE CheckDialingEnable(UBYTE dial_length)
{
	/**************************************/
	/* 残りのバッファと必要な桁数との比較 */
	/**************************************/
	/* ダイヤル発呼が終了しているとき */ /*発呼した分は上書き可能*/
	if (SYS_DialingNumber.ReadPointer == SYS_DialingNumber.WritePointer) {
		return(TRUE); /* 空ｴﾘｱ有 */
	}
	/* 発呼中の時 */
	if (SYS_DialingNumber.ReadPointer < SYS_DialingNumber.WritePointer) {
		/*-----------------------------------------------------*/
		/*  バッファサイズからまだ発呼していない番号を引いた値 */
		/*	が必要バッファ量以上あるならダイアル可能		   */
		/*-----------------------------------------------------*/
		if (((UBYTE)DIALING_NUMBER_MAX - (SYS_DialingNumber.WritePointer - SYS_DialingNumber.ReadPointer))
			> dial_length) {
			return (TRUE); /* 空ｴﾘｱ有 */
		}
		else {
			return (FALSE); /* 空ｴﾘｱ無 */
		}
	}

	/* ライトポインタが一周した場合*/
	if (SYS_DialingNumber.ReadPointer > SYS_DialingNumber.WritePointer) {
		if ((SYS_DialingNumber.ReadPointer - SYS_DialingNumber.WritePointer) > dial_length) {
			return (TRUE); /* 空ｴﾘｱ有 */
		}
		else {
			return (FALSE); /* 空ｴﾘｱ無 */
		}
	}
}

/*************************************************************************
	module		:[回線回りの状態の表示]
	function	:[
		1.保留中／電話中の表示
	]
	return		:[]
	common		:[
				SYS_MachineStatus
				D2W_OnHold
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口]
*************************************************************************/
void DisplayNCUStatus(void)
{
	UWORD	status;

	if (CheckChildDisplay() == TRUE) {
		return;
	}

#if defined (KEISATSU)		/* 警察FAX DVT_ID12 Added by SMuratec K.W.Q 2005/11/02 */
	if (((!CheckIsKanyuLine()) && (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_LINE_KANYU)) ||
		(CheckIsKanyuLine() && (!(SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_LINE_KANYU)))) {
		AttributeTimeoutCheck = 1;
	}
#endif		/* End of (defined (KEISATSU)) */

	status = SYS_MachineStatus[SYS_MACHINE_STATUS_NCU];
	if (status & SYS_LINE_HOLD) {	/* 保留中の時 */
		DisplayStringHigh(0, D2W_OnHold);			/* "     ** ﾎﾘｭｳ **     " */
		ClearDisplayLow();
	}
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/13 */
	else if (status & SYS_HOOK_KEY_OFF_HOOK	||
			((status & SYS_TEL1_OFF_HOOK) && CheckIsKanyuLine()) || 
			((status & SYS_TEL2_OFF_HOOK) && !(CheckIsKanyuLine()))) {
		/* 表示用バッファの初期化 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayHigh();
		ClearDisplayLow();
 #endif

		DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
		DisplayStringHigh(0 , FunctionDisplayBufferHigh);

		DisplayTelNumber();
	}
	else {
		/* 表示用バッファの初期化 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayHigh();
 #endif
		DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
		DisplayStringHigh(0 , FunctionDisplayBufferHigh);
	}
#else
	else if (status & (SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK | SYS_HOOK_KEY_OFF_HOOK)) {	/* 通話中の時 */
		DisplayStringHigh(0, D2W_TelephoneMode);	/* "     ** ﾃﾞﾝﾜ **     " */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/25 */
		if (CMN_CheckDocumentOnFeeder()
		 && CMN_CheckFeederCommandEmpty() == TRUE						/** スキャナーコマンドがあらない時 Added by SMuratec L.Z.W 2003/11/19 */
		 && !((DS1()&&!(DS2())&&!TXIL()))								/* FEED IN SCANNER BUSYではない　SYS_FEED_INとしては表示の問題がある*/
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* FEED OUT SCANNER BUSYではない*/
			if (*(TelControl.SpeedBuffer) == NULL 
				&& *(SYS_DialingNumber.Buffer) == NULL) {
				DisplayDocumentSet();
				IsFlashDisplayLow = FALSE; /*点滅表示しない*/
				DisplayStringHigh(16, &D2W_TelephoneMode[16]);	/* "     ** ﾃﾞﾝﾜ **     " */
			}
	/** 原稿蓄積時の表示（次原稿の表示の関係で、PRO_FBSで表示の優先度を替えます） */
 #if (PRO_DISPLAY_STOP_KEY_OPR == ENABLE) /* By H.Fujimura 1999/01/18 */
			else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)					/* 原稿蓄積中で、*/
	 				&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE)) {	/* 原稿蓄積停止要求ではない*/
 #else
			else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
 #endif
				DisplayDocumentSet();
				IsFlashDisplayLow = FALSE; /*点滅表示しない*/
				DisplayStringHigh(16, &D2W_TelephoneMode[16]);	/* "     ** ﾃﾞﾝﾜ **     " */
			}
			else{
				/* 下段表示は電話番号とカーソルのみ（オペレーション中の表示以外上書きされません） */
				DisplayTelNumber();
			}
		}
		else{
			/* 下段表示は電話番号とカーソルのみ（オペレーション中の表示以外上書きされません） */
			DisplayTelNumber();
		}
#else
		/* 下段表示は電話番号とカーソルのみ（オペレーション中の表示以外上書きされません） */
		DisplayTelNumber();
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	}
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[電話番号表示]
	function	:[
		1.短縮番号入力中は短縮入力バッファの内容を表示する。
		2.通常入力中は、ダイアルバッファの内容を表示する
		3.ＰＩＮアクセスがＯＮの時、ＰＩＮ番号の始まりの＊が入力された以降、
		　の入力はマスクされる。（表示は変わらない)
		4.短縮番号の入力中は入力中の短縮番号は表示する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/06]
	author		:[江口]
*************************************************************************/
void DisplayTelNumber(void)
{
	UBYTE	cursor_position;
	UBYTE	start_position;
	UBYTE	counter;
	UBYTE	position;
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/19 for prefix *//* by K.Watanabe 2004/10/12 */
	UBYTE	display_buf[SYS_MERCURY_BUF_MAX + OPR_DISPLAY_MAX];
	UWORD	length;
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/07 */
	UBYTE	display_buf[OPR_DISPLAY_MAX + 5];
	UWORD	length;
#endif		/* End of (defined (KEISATSU)) */

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
	UBYTE	uae_pin_round_flag;	/* UAE ARAMCO PIN By O.Kimoto 1997/06/04 */
	
	uae_pin_round_flag = 0;	/* UAE ARAMCO PIN By O.Kimoto 1997/06/04 */
#endif

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');	/*表示用バッファ初期化*/

	if (TelControl.SpeedPosition > 0) { /* 短縮入力中 */
		/* 短縮番号入力バッファの内容を表示用のバッファにセット */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/22 */
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayLow();
 #else
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
 #endif

		CMN_StringCopyNum(FunctionDisplayBufferLow,D2W_Telephone,4);
		FunctionDisplayBufferLow[4] = ':';
		CMN_StringCopy(&FunctionDisplayBufferLow[5], TelControl.SpeedBuffer);
#else
		CMN_StringCopy(FunctionDisplayBufferLow, TelControl.SpeedBuffer);
#endif		/* End of (defined (KEISATSU)) */
	}

	else {/* 通常の電話中 */

		/*----------------------------------------------*/
		/* ＰＩＮ番号未ダイアルの時の表示のための処理 */
		/*----------------------------------------------*/
		if (TelControl.PinNumberDialFlag == 0) { /*ＰＩＮ番号送出していない */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/23 */
			if (TEL_ManualTxNumber.WritePointer <= 19) {
				if (TEL_ManualTxNumber.Buffer[DIALING_NUMBER_MAX - 1] == 0) { /* まだ一周はしていない*/
					for (counter = 0; counter < TEL_ManualTxNumber.WritePointer; counter++) {
						FunctionDisplayBufferLow[counter] = TEL_ManualTxNumber.Buffer[counter];
					}
					FunctionDisplayBufferLow[TEL_ManualTxNumber.WritePointer] = 0;
				}
				else { /*ダイアルバッファを既に１周以上している場合 */
					if (TEL_ManualTxNumber.WritePointer == 0) { /* ２周目以降のバッファの先頭に書き込み位置がきている */
						for ( counter = 0; counter <= 18; counter++ ) {
							FunctionDisplayBufferLow[counter] =
							TEL_ManualTxNumber.Buffer[(DIALING_NUMBER_MAX - 19) + counter];/*けつから19個分*/
						}
					}
					else { /* ２周目以降で書き込み位置がＬＣＤのサイズ（桁数）未満の時 */
						start_position = (UBYTE)DIALING_NUMBER_MAX + TEL_ManualTxNumber.WritePointer - (UBYTE)19;
						for ( counter = 0; counter <= 18; counter++ ) {
							if ( (start_position + counter) < DIALING_NUMBER_MAX ) {
								FunctionDisplayBufferLow[counter] =
								TEL_ManualTxNumber.Buffer[start_position + counter];
							}
							else {
								FunctionDisplayBufferLow[counter] =
 								TEL_ManualTxNumber.Buffer[start_position + counter - DIALING_NUMBER_MAX];
							}
						}
					}
				}
			}
			else {	/* ＷｒｉｔｅＰｏｉｎｔｅｒが２０以上の時 (LCDのサイズ（桁数）を越えている) */
				for ( counter = 0; counter <= 18; counter++ ) {
					FunctionDisplayBufferLow[counter] =
					TEL_ManualTxNumber.Buffer[(TEL_ManualTxNumber.WritePointer - 19) + counter];
				}
			}
#else
			if (SYS_DialingNumber.WritePointer <= 19) {
				if (SYS_DialingNumber.Buffer[DIALING_NUMBER_MAX - 1] == 0) { /* まだ一周はしていない*/
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
					UAE_PIN_CopiedSrcBufferPosition = 0;	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
#endif
					for (counter = 0; counter < SYS_DialingNumber.WritePointer; counter++) {
						FunctionDisplayBufferLow[counter] = SYS_DialingNumber.Buffer[counter];
					}
					FunctionDisplayBufferLow[SYS_DialingNumber.WritePointer] = 0;
				}
				else { /*ダイアルバッファを既に１周以上している場合 */
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
					uae_pin_round_flag = 1;	/* UAE ARAMCO PIN By O.Kimoto 1997/06/04 */
#endif

					if (SYS_DialingNumber.WritePointer == 0) { /* ２周目以降のバッファの先頭に書き込み位置がきている */

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
						UAE_PIN_CopiedSrcBufferPosition = (UWORD)(DIALING_NUMBER_MAX - 19);	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
#endif
						for ( counter = 0; counter <= 18; counter++ ) {
							FunctionDisplayBufferLow[counter] =
							SYS_DialingNumber.Buffer[(DIALING_NUMBER_MAX - 19) + counter];/*けつから19個分*/
						}
					}
					else { /* ２周目以降で書き込み位置がＬＣＤのサイズ（桁数）未満の時 */
						start_position = (UBYTE)DIALING_NUMBER_MAX + SYS_DialingNumber.WritePointer - (UBYTE)19;
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
						UAE_PIN_CopiedSrcBufferPosition = (UWORD)start_position; /* ARAMCO PIN By O.Kimoto 1997/05/21 */
#endif
						for ( counter = 0; counter <= 18; counter++ ) {
							if ( (start_position + counter) < DIALING_NUMBER_MAX ) {
								FunctionDisplayBufferLow[counter] =
								SYS_DialingNumber.Buffer[start_position + counter];
							}
							else {
								FunctionDisplayBufferLow[counter] =
 								SYS_DialingNumber.Buffer[start_position + counter - DIALING_NUMBER_MAX];
							}
						}
					}
				}
			}
			else {	/* ＷｒｉｔｅＰｏｉｎｔｅｒが２０以上の時 (LCDのサイズ（桁数）を越えている) */
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
				UAE_PIN_CopiedSrcBufferPosition = (UWORD)(SYS_DialingNumber.WritePointer - 19);	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
#endif
				for ( counter = 0; counter <= 18; counter++ ) {
					FunctionDisplayBufferLow[counter] =
					SYS_DialingNumber.Buffer[(SYS_DialingNumber.WritePointer - 19) + counter];
				}
			}
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
			if (CMN_CheckAramcoModel() == 1) {
				/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応
				** ”＃”から”＃”までの番号を”＊”に置き換えます。
				** By O.Kimoto 1997/04/16
				*/
				if (CHK_UNI_AramcoPinNotMasking() == 0) {	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
					if (UAE_PIN_1stSharpPosition != 0xFFFF) {
						if (UAE_PIN_RoundFlag != 0) {
							if (uae_pin_round_flag == 0) {
								UAE_PIN_CopiedSrcBufferPosition += 
										(UWORD)((UWORD)UAE_PIN_RoundFlag * (UWORD)(DIALING_NUMBER_MAX));
							}
						}
						if (UAE_PIN_CopiedSrcBufferPosition <= UAE_PIN_1stSharpPosition) {
							for ( counter = 0; counter <= 18; counter++ ) {
								if((UWORD)(UAE_PIN_CopiedSrcBufferPosition + counter) == UAE_PIN_1stSharpPosition) {
									counter ++;
									while ((FunctionDisplayBufferLow[counter] != '#') 
										&& (FunctionDisplayBufferLow[counter] != 0x00)
										&& (counter <= 18)
										&& ((UWORD)(UAE_PIN_CopiedSrcBufferPosition + counter) 
										!= UAE_PIN_2ndSharpPosition )) {
										FunctionDisplayBufferLow[counter] = '*';
										counter ++;
									}
									break;
								}
							}
						}
						else {
							if (UAE_PIN_CopiedSrcBufferPosition == 0) {
								;
							}
							else {
								if (UAE_PIN_2ndSharpPosition == 0xFFFF) {
									counter = 0;
									while ((FunctionDisplayBufferLow[counter] != '#') 
										&& (FunctionDisplayBufferLow[counter] != 0x00)
										&& (counter <= 18)
										&& ((UWORD)(UAE_PIN_CopiedSrcBufferPosition + counter) 
										!= UAE_PIN_2ndSharpPosition )) {
										FunctionDisplayBufferLow[counter] = '*';
										counter ++;
									}
								}
								else {
									if (UAE_PIN_CopiedSrcBufferPosition < UAE_PIN_2ndSharpPosition) {
										counter = 0;
										while ((FunctionDisplayBufferLow[counter] != '#') 
											&& (FunctionDisplayBufferLow[counter] != 0x00)
											&& (counter <= 18)
											&& ((UWORD)(UAE_PIN_CopiedSrcBufferPosition + counter) 
											!= UAE_PIN_2ndSharpPosition )) {
											FunctionDisplayBufferLow[counter] = '*';
											counter ++;
										}
									}
								}
							}
						}
					}
				}
			}
#endif
#endif		/* End of (defined (KEISATSU)) */

		}

		/*----------------------------------------------*/
		/* ＰＩＮ番号ダイアル済みの時の表示のための処理 */
		/*----------------------------------------------*/
		else { /*ＰＩＮ番号送出した (ぴん番号も含めて以降の入力は表示しない)*/
			if (TelControl.AfterPinDialDisplayBuffer[0] == ' ') { /*ＰＩＮ番号送出したところ */
				for (position = 0; position < DIALING_NUMBER_MAX; position++) {
					/* 区切りの＊を探す。絶対ある */
					if (SYS_DialingNumber.Buffer[position] == OPR_PIN_MARK) {
						break;
					}
				}
				if (position == DIALING_NUMBER_MAX) {
					/*バグ */
				}
				if (position <= 19) {
					if (SYS_DialingNumber.Buffer[DIALING_NUMBER_MAX - 1] == 0) { /* まだ一周はしていない*/
						for (counter = 0; counter < position; counter++) {
							TelControl.AfterPinDialDisplayBuffer[counter] = SYS_DialingNumber.Buffer[counter];
						}
					}
					else { /* 一周した */
						if (position == 0) {
							for (counter = 0; counter < 18; counter++ ) {
								TelControl.AfterPinDialDisplayBuffer[counter] =
								SYS_DialingNumber.Buffer[(DIALING_NUMBER_MAX - 19) + counter];/*けつから19個分*/
							}
						}
						else {
							start_position = (UBYTE)DIALING_NUMBER_MAX + position - (UBYTE)19;
							for ( counter = 0; counter <= 18; counter++ ) {
								if ((start_position + counter) < DIALING_NUMBER_MAX ) {
									TelControl.AfterPinDialDisplayBuffer[counter] =
									SYS_DialingNumber.Buffer[start_position + counter];
								}
								else {
									TelControl.AfterPinDialDisplayBuffer[counter] =
	 								SYS_DialingNumber.Buffer[start_position + counter - DIALING_NUMBER_MAX];
								}
							}
						}
					}
				}
				else {/* positionが２０を越える（LCDのサイズを越えている) */
					/* WritePointerから１８文字分セット */
					for ( counter = 0; counter <= 18; counter++ ) {
						TelControl.AfterPinDialDisplayBuffer[counter] =
						SYS_DialingNumber.Buffer[(position - 19) + counter];
					}
				}
			}
			CMN_StringCopy(FunctionDisplayBufferLow, TelControl.AfterPinDialDisplayBuffer);
		}
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/22 */
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayLow();
 #endif

		CMN_MemorySet(display_buf,OPR_DISPLAY_MAX + 5,NULL);
		length = CMN_StringLength(FunctionDisplayBufferLow);
		CMN_StringCopyNum(display_buf,D2W_Telephone,4);
		display_buf[4] = ':';
		
		if (length < 15){
			CMN_StringCopyNumNotNULL(&display_buf[5],FunctionDisplayBufferLow,length);
		}
		else if(length >= 15 && length < 20){
			CMN_StringCopyNumNotNULL(&display_buf[5],&FunctionDisplayBufferLow[length + 6 - OPR_DISPLAY_MAX],OPR_DISPLAY_MAX - 6);
		}
		else{
			CMN_StringCopyNumNotNULL(&display_buf[5],&FunctionDisplayBufferLow[length + 5 - OPR_DISPLAY_MAX],OPR_DISPLAY_MAX - 5);
		}
		
		CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow,display_buf,OPR_DISPLAY_MAX);
#endif		/* End of (defined (KEISATSU)) */
	}

#if !defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/22 */
	ClearDisplayLow();
#endif		/* End of (defined (KEISATSU)) */
	
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/19 for prefix *//* by K.Watanabe 2004/10/12 */
	CMN_MemorySet(display_buf,SYS_MERCURY_BUF_MAX + OPR_DISPLAY_MAX,NULL);
	ChangeInputBuffer(display_buf,FunctionDisplayBufferLow);
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	
	length = CMN_StringLength(display_buf);
	if(length <= 19) {
		CMN_StringCopyNum(FunctionDisplayBufferLow,&display_buf[0],19);
	}
	else {
		position = length -19;
		for(counter = 0;counter <= 18;counter++) {
			FunctionDisplayBufferLow[counter] = display_buf[position];
			position++;
		}
	}
	
	DisplayStringLow(0, FunctionDisplayBufferLow);
#else
	DisplayStringLow(0, FunctionDisplayBufferLow);
#endif
	cursor_position = (UBYTE)GetStringGapPoint(FunctionDisplayBufferLow, ' ');
	CursorOn((UBYTE)(cursor_position + OPR_LCD_LOWER_ADD));
}

/*************************************************************************
	module		:[スピーカーボリューム調整]
	function	:[
		1.キーを取り込み、＞キーでボリュームアップ、＜キーでボリュームダウンを行う。
		2.２秒間キー入力無しで終了。
		3.フックキー押下で終了。
		4.フックキーオフフック状態解除で終了
	]
	return		:[]
	common		:[SYB_MonitorSpeakerOutLevel]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口,渡辺一章]
*************************************************************************/
void SpeakerVolumeAdjust(void)
{
	UBYTE	key;
	UBYTE	key_type;
	UBYTE	is_loop_end;

	is_loop_end = FALSE;

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	/* ＣＧＲＡＭに濃度・ボリューム設定用のデータを書き込みます */
	WriteCGRAM((UBYTE *)CG_RamTableDensityVolumeSet);
#endif

	/* 下段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferLow, D2W_ChangeVolume);			/* "  ﾎﾞﾘｭｰﾑ:           " */

	while (is_loop_end == FALSE) {

		/* スピーカーボリューム調整中表示 */
		DisplayMonitorSpeakerVolume();

		OPR_GetKey(KEY_WAIT_2_SECOND);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {
		case FUNCTION:
			/* ボリュームアップ */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_MAXIMUM) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel++;
				/* リアルタイムにボリュームを更新すると、キーのブザーボリュームも変わる
				** （キー押すと必ず、アックがなるので）
				**
				** MonitorSpeakerVolumeControl();
				*/
#if (PRO_MULTI_LINE == ENABLE)
				MAN_ChangedSRAM_Parameter(OPT_CHANGED_SPEAKER_LEVEL);
#endif
			}
			break;
		case LEFT_ARROW:
			/* ボリュームダウン */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_OFF) {
				NackBuzzer();
			}
			else {
				SYB_MonitorSpeakerOutLevel--;
				/* リアルタイムにボリュームを更新すると、キーのブザーボリュームも変わる
				** （キー押すと必ず、アックがなるので）
				**
				**MonitorSpeakerVolumeControl();
				*/
#if (PRO_MULTI_LINE == ENABLE)
				MAN_ChangedSRAM_Parameter(OPT_CHANGED_SPEAKER_LEVEL);
#endif
			}
			break;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)		/* 音量調整キー有効 by Y.kano 2003/09/20 */
		case VOLUME:		/* 音量調整キー */
			if (SYB_MonitorSpeakerOutLevel == SYS_VOLUME_MAXIMUM) {
				SYB_MonitorSpeakerOutLevel = SYS_VOLUME_OFF;
			}
			else {
				SYB_MonitorSpeakerOutLevel++;
				/* リアルタイムにボリュームを更新すると、キーのブザーボリュームも変わる */
			}
			break;
#endif
		case HOOK:
			/* この関数にくる場合フックキーオフフック状態しかあり得ない */
			HookKeySet();
			is_loop_end = TRUE;
			break;
		case STOP:
		case KEY_TIME_UP: /* キー待ちタイムオーバー */
			is_loop_end = TRUE;
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			if (key == OPR_TEL_OPERATION) {
				if (CheckLineStatus() != OPR_HOOKKEY_OFFHOOK) {
					is_loop_end = TRUE;
				}
			}
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[スピーカーボリューム調整中表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayMonitorSpeakerVolume(void)
{
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様では'+'キーの表示を倍にします。by Y.Kano 2003/09/08 */
	CMN_MemorySet(&FunctionDisplayBufferLow[7], 12, ' ');
 #else
	CMN_MemorySet(&FunctionDisplayBufferLow[9], 6, ' ');
 #endif

	switch (SYB_MonitorSpeakerOutLevel) {
	case SYS_VOLUME_OFF:
		break;
	case SYS_VOLUME_MINIMUM:
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[9]  = 0xF5;
//		FunctionDisplayBufferLow[10] = 0xF5;
#endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様では'+'キーを使用します。by Y.Kano 2003/09/08 */
		FunctionDisplayBufferLow[7]  = 0x2B;	/* ++++ */
		FunctionDisplayBufferLow[8] =  0x2B;
		FunctionDisplayBufferLow[9]  = 0x2B;
		FunctionDisplayBufferLow[10] = 0x2B;
 #else	/* SATSUKI2以外 */
		FunctionDisplayBufferLow[9]  = OPR_CG_FONT_5;
		FunctionDisplayBufferLow[10] = OPR_CG_FONT_5;
 #endif
		break;
	case SYS_VOLUME_MIDDLE:
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[9]  = 0xF5;
//		FunctionDisplayBufferLow[10] = 0xF5;
//		FunctionDisplayBufferLow[11] = 0xF6;
//		FunctionDisplayBufferLow[12] = 0xF6;
#endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様では'+'キーを使用します。by Y.Kano 2003/09/08 */
		FunctionDisplayBufferLow[7]  = 0x2B;	/* ++++++++ */
		FunctionDisplayBufferLow[8] =  0x2B;
		FunctionDisplayBufferLow[9]  = 0x2B;
		FunctionDisplayBufferLow[10] = 0x2B;
		FunctionDisplayBufferLow[11] = 0x2B;
		FunctionDisplayBufferLow[12] = 0x2B;
		FunctionDisplayBufferLow[13] = 0x2B;
		FunctionDisplayBufferLow[14] = 0x2B;
 #else	/* SATSUKI2以外 */
		FunctionDisplayBufferLow[9]  = OPR_CG_FONT_5;
		FunctionDisplayBufferLow[10] = OPR_CG_FONT_5;
		FunctionDisplayBufferLow[11] = OPR_CG_FONT_6;
		FunctionDisplayBufferLow[12] = OPR_CG_FONT_6;
 #endif
		break;
	case SYS_VOLUME_MAXIMUM:
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[9]  = 0xF5;
//		FunctionDisplayBufferLow[10] = 0xF5;
//		FunctionDisplayBufferLow[11] = 0xF6;
//		FunctionDisplayBufferLow[12] = 0xF6;
//		FunctionDisplayBufferLow[13] = 0xF7;
//		FunctionDisplayBufferLow[14] = 0xF7;
#endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様では'+'キーを使用します。by Y.Kano 2003/09/08 */
		FunctionDisplayBufferLow[7]  = 0x2B;	/* ++++++++++++ */
		FunctionDisplayBufferLow[8] =  0x2B;
		FunctionDisplayBufferLow[9]  = 0x2B;
		FunctionDisplayBufferLow[10] = 0x2B;
		FunctionDisplayBufferLow[11] = 0x2B;
		FunctionDisplayBufferLow[12] = 0x2B;
		FunctionDisplayBufferLow[13] = 0x2B;
		FunctionDisplayBufferLow[14] = 0x2B;
		FunctionDisplayBufferLow[15] = 0x2B;
		FunctionDisplayBufferLow[16] = 0x2B;
		FunctionDisplayBufferLow[17] = 0x2B;
		FunctionDisplayBufferLow[18] = 0x2B;
 #else	/* SATSUKI2以外 */
		FunctionDisplayBufferLow[9]  = OPR_CG_FONT_5;
		FunctionDisplayBufferLow[10] = OPR_CG_FONT_5;
		FunctionDisplayBufferLow[11] = OPR_CG_FONT_6;
		FunctionDisplayBufferLow[12] = OPR_CG_FONT_6;
		FunctionDisplayBufferLow[13] = OPR_CG_FONT_7;
		FunctionDisplayBufferLow[14] = OPR_CG_FONT_7;
 #endif
		break;
	default:
		break;
	}

	DisplayStringLow(0, FunctionDisplayBufferLow);

}

/*************************************************************************
	module		:[待機モード表示制御処理]
	function	:[
		1.ファクスモードの時は、電話中なので UpdateLCD()で表示の更新をされ
		　ないように、SYS_PANEL_BUSYをＯＮします
		2.コピーモードの時は、UpdateLCD()で表示を更新するように、
		　SYS_PANEL_BUSYをＯＦＦします
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/10]
	author		:[渡辺一章]
*************************************************************************/
void ChangePanelBusy(void)
{
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		/* コピーモードの表示を、UpdateLCD()で行うために、SYS_PANEL_BUSYをＯＦＦします */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PANEL_BUSY;
	}
	else {						/* 電話中（ファクスモード）の時 */
		/* 電話中の表示を更新されないために、SYS_PANEL_BUSYをＯＮします */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
	}
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/25 */
UBYTE CheckRemoteTransfer(UBYTE key)
{
	UBYTE	keycode;
	UBYTE	dial_number[2];
	
	keycode = key;

	dial_number[0] = (SYS_MemorySwitch[MEMORY_SW_G7] & REMOTE_TRANSFER_DIAL_NUM1) >> 4;
	dial_number[1] = (SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM1) >> 4;

	/* 警察FAX DVT39 Added by SMuratec 夏 2005/11/15 */
	/* スクランブルと共通/専用の初期化 */
	if (CheckIsScrambleOFF() || (CMN_CheckScrambleSwOn() == FALSE)) {
		FCM_ExecutingS1Info.Available = FALSE;
		FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
	}
	else {
		FCM_ExecutingS1Info.Available = TRUE;
		
		if (CheckIsSenyou()) {
			FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
		}
		else {
			FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
		}
	}

	FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;	/* 警察FAX DVT_ID39 Added by SMuratec K.W.Q 2005/11/11 */
	
	if (SYS_RingCounter != 0 && CheckIsKanyuLine()) {
		SYS_InternalLineNumber = SYS_STD_LINE_COM;
		
		switch (SYB_SettingStatus[SETTING_STATUS_0] & LINE_TYPE0_MASK) {
		case DIAL_SPEED_10PPS:
		case DIAL_SPEED_20PPS:
			if (CHK_RemoteTransferDialOne()) {
				if ((keycode == '3') &&
					(dial_number[0] == 3)) {
					return (TRUE);
				}
			}
			else {
				if ((keycode == '3') &&
					(dial_number[0] == 3) &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					(TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[0]) {
					return (TRUE);
				}
			}
			
			break;
		case LINE_TYPE_TONE:
			if (CHK_RemoteTransferDialOne()) {
				if ((keycode - 48) == dial_number[0]) {
					return (TRUE);
				}
			}
			else {
				if ((keycode - 48) == dial_number[0] &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					((TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[0])) {
					return (TRUE);
				}
			}
		}
	}
	else if (SYS_RingCounterExt != 0 && !(CheckIsKanyuLine())) {
		SYS_InternalLineNumber = SYS_EXT_LINE_COM;

		switch (SYB_SettingStatus[SETTING_STATUS_0] & LINE_TYPE0_MASK) {
		case DIAL_SPEED_10PPS:
		case DIAL_SPEED_20PPS:
			if (CHK_RemoteTransferDialOne()) {
				if ((keycode == '3') && (dial_number[0] == 3)) {
					return (TRUE);
				}
				else if ((keycode == '9') && (dial_number[1] == 9)) {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
					return (TRUE);
				}
				else {
					return (FALSE);
				}
			}
			else {
				if ((keycode == '3') &&
					(dial_number[0] == 3) &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					((TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[0])) {
					return (TRUE);
				}
				else if ((keycode == '9') && 
					(dial_number[1] == 9) &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					((TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[1])) {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
					return (TRUE);
				}
				else {
					return (FALSE);
				}
			}
			
			break;
		case LINE_TYPE_TONE:
			if (CHK_RemoteTransferDialOne()) {
				if ((keycode - 48) == dial_number[0]) {
					return (TRUE);
				}
				else if ((keycode - 48) == dial_number[1]) {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
					return (TRUE);
				}
				else {
					return (FALSE);
				}
			}
			else {
				if (((keycode - 48) == dial_number[0]) &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					((TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[0])) {
					return (TRUE);
				}
				else if (((keycode - 48) == dial_number[1]) &&
					(TEL_ManualTxNumber.WritePointer >= 2) &&
					((TEL_ManualTxNumber.Buffer[TEL_ManualTxNumber.WritePointer - 2] - 48) == dial_number[1])) {
					FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
					return (TRUE);
				}
				else {
					return (FALSE);
				}
			}
		}
	}
	
	return (FALSE);
}


/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
/* 電話状態ではLCD属性自動更新 */
void ResetKeisatsuAttribute()
{	
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
	if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
		|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
		|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
	}
	else
	if (AttributeTimeoutCheck &&
		(!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) && 
		!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) &&
		!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK))) {
			SetKeisatsuSettings();
			AttributeTimeoutCheck = 0;
			NCU_HdstShift();
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_SHIREI_ON;
			snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
			rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
	}
}

#endif		/* End of (defined (KEISATSU)) */
