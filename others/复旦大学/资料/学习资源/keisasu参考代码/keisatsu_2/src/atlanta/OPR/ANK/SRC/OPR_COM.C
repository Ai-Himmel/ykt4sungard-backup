/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_COM.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: コマンド登録時オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_b.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysscan.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\scn_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/15 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
 #endif
#endif

#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#else
	#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
#include	"\src\atlanta\define\sys_infd.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/28 */
#include "\src\atlanta\hinoki\define\m_param.h"
/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#include	"\src\atlanta\define\sysnd.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#endif 		/* End of (defined (KEISATSU)) */

/* Prototype
void	CommandOperation(UBYTE, UBYTE);
void	CommandInputInitial(void);
void	SetPinCheckStatus(void);
void	ComOptionInputInitial(void);
void	DisplayCommandOperation(void);
void	DisplayCommandNumber(void);
UBYTE	CheckNoCommandData(void);
UBYTE	CheckInputCommandDialNumber(void);
UBYTE	CheckInputSpecialCommand(void);
UBYTE	CheckInputBroadcast(void);
UBYTE	CheckInputOnetouchEnable(UBYTE);
UBYTE	CheckInputP_OnetouchEnable(UBYTE);
UBYTE	CheckPreDataSpeedMark(void);
UBYTE	CheckPreDataOnetouch(void);
UBYTE	CheckInputNumberCode(UBYTE);
UBYTE	CheckSpeedGroupAfterEnableKey(UBYTE);
UBYTE	CheckProgramAfterInput(UBYTE);
#if (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	CheckRegistrationData(UBYTE);
UBYTE	CheckInputDialData(UBYTE);
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
UBYTE	CheckInputDirectDial(UBYTE);
#endif
void	BroadcastCheck(void);
void	InputNumberTenKeySet(UBYTE);
void	InputNumberOnetouchSet(UBYTE);
void	InputNumberGroupSpeedMarkSet(UBYTE);
void	InputNumberProgramSet(UBYTE);
void	BroadcastMarkSet(void);
void	InputNumberDialMarkSet(UBYTE);
void	InputNumberCursorRight(void);
void	InputNumberCursorLeft(void);
void	InputNumberDataClear(void);
void	InputNumberDialCharacterSet(void);
void	InputNumberDataShift(UBYTE);
void	InputNumberDataSet(UBYTE);
void	InsertInputData(UBYTE *, UBYTE);
void	InputNumberClearBackSpace(void);
void	InputNumberClearDelete(void);
void	SetTelBookDataToInputBuffer(void);
UBYTE	ProgramOnetouchExecute(UBYTE);
UBYTE	FaxComTxReserveOperation(void);
#if (PRO_DEPARTMENT == ENABLE)
UBYTE	DepartmentCodeOperation(void);
#endif
#if (PRO_DEPARTMENT == ENABLE)
UBYTE	CheckInputDepartCode(void);
#endif
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	PinAccessOperation(void);
#endif
void	CalculateProgramExecTime(void);
UBYTE	CheckAndGetCommandArea(void);
void	ReleaseCommandArea(void);
void	ClearCommandFileData(struct SYS_CommandData_t *);
void	ClearDialNumber(struct SYS_DialData_t *);
void	ClearCommandPinNumber(struct SYS_CommandData_t *);
void	ClearDialPinNumber(struct SYS_DialData_t *);
UBYTE	CommandStartOperation(void);
void	SetCommandPinAccessMode(struct SYS_CommandData_t *);
void	SetCommandDialNumber(void);
void	SetDialNumber(struct SYS_DialData_t *, UBYTE);
void	SetCommandTime(void);
void	SetCommandOption(void);
void	SetCommandOptionItem(struct SYS_CommandData_t *);
void	SetCommandOptionNumber(struct SYS_CommandData_t *, UBYTE, UBYTE);
void	SetCommandConfirmReport(struct SYS_CommandData_t *);
void	SetCommandTitleMessage(void);
void	SetCommandPage(void);
#if (PRO_DEPARTMENT == ENABLE)
void	SetCommandDepartCode(void);
#endif
void	SetCommandPinNumber(void);
UBYTE	CheckMemoryTxEnable(void);
UBYTE	CheckScannerTxEnable(void);
UBYTE	CheckPollingCommandInput(void);
void	SetProgramDialToInputNumber(UBYTE);
UBYTE	DialCharacterCheck(UBYTE *, UWORD, UWORD);
#if (PRO_CONTINUOUS_POLLING == ENABLE)
UBYTE	SetContPollingCommandTime(void);
void	ClearContPollingData(struct SYS_ContinuousPollingData_t *);
void	ClearCommandPinNumberCP(struct SYS_ContinuousPollingData_t *);
#endif
#if (PRO_FBS == ENABLE)
UBYTE	BookDocumentSizeSet(UBYTE, UBYTE);
void	BookNextDocumentSet(UBYTE, UBYTE);
void	DisplayBookDocumentData(UBYTE);
#endif
#if (PRO_BATCH_TX == ENABLE)
UBYTE	ProgramOnetouchBatch(UBYTE);
#endif
#if (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	CheckRegistrationSpeedDial(UWORD, UWORD);
UBYTE	CheckRegistrationGroupDial(UWORD, UWORD);
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
UBYTE	CheckDirectDialCount(void);				/ by K.Watanabe 1999/01/28 /
UBYTE	CheckDirectDialLength(UBYTE, UBYTE);
void	ChangeAsteriskKeyCode(UBYTE);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE)
void	DisplayDialName(UBYTE, UWORD);
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
void	MinoltaOnetouchPrint(UBYTE);
UBYTE	MinoltaStandardPG(UBYTE, UBYTE)
#endif
*/

/*************************************************************************
	module		:[コマンド入力]
	function	:[
		1.送信オペレーション、送信予約オペレーションを行う
		2.枚数指定オペレーション時、枚数指定入力後相手先入力を行う
		3.TEL2オフフック時の予約オペレーションを行う
	]
	return		:[なし]
	common		:[]
	condition	:[
		ポプラＢで、次原稿ありで原稿蓄積中の時は、この関数に入らないこと
		（入ってしまうと、条件によっては次原稿がなしになってしまいます）
	]
	comment		:[
		InputNumber
							  LCD
							  |01234567890123456789|
							  |                    |
		InputNumber.Buffer[] = 123456789,A,G01,S002,345........
							   |	-				   |
							   |	|				   |
							   |	|				   InputNumber.WritePosition
							   |	|
							   |	InputNumber.CursorPosition
							   |
							   InputNumber.DisplayStartPosition

		CursorPosition	:入力位置 0 ～ WritePositionの間で自由に動く
		WritePosition	:入力後端位置、入力桁数。WritePositionの位置は必ずNULLである

		・コマンドファイルを掴むタイミングをスタートキー押下時に統一します
		・枚数指定オペレーション後、コマンドオペレーションを行う場合は引数はOPR_NO_KEYになります
		・データの挿入は必ず前に挿入することにする.
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/30]
	author		:[江口]
*************************************************************************/
void CommandOperation(UBYTE key_code, UBYTE key_type)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	key_request;
#if (PRO_FBS == ENABLE)
	UBYTE	last_key;	/* 前回キー入力値 */
#endif
	UBYTE	program;
	UBYTE	exec_program;
	UBYTE	command_end;
	UBYTE	is_scan_start;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	UBYTE	com_set_flg;
#endif
	UBYTE	tel_book_ope_rtn;	/* 電話帳機能実行後のリターン値 by K.Watanabe 1998/04/03 */
#if (PRO_NEW_DIAL_OPR == ENABLE)	/* by K.Watanabe 1998/04/03 */
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_number;		/* 電話帳で選択されたデータの配列番号	*/
#endif
	UWORD	data_number;		/* 電話帳で選択されたデータの配列番号	*/
#endif
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
	UBYTE	i;
#endif

	/** 初期化 */
	CommandInputInitial();								/* コマンド登録用バッファクリア							*/
	ComOptionInputInitial();							/* 応用機能登録用バッファクリア							*/
	InputNumber.InputDialType = COMMAND_DIAL_TYPE;		/* 登録する種類をセット									*/
	SetPinCheckStatus();								/* ＰＩＮ番号チェック要不要をセット						*/
	SettingCommandFileNumber = NO_SETTING_COMMAND_FILE;	/* 確保するコマンドファイル番号を初期化					*/
	OPR_TelBookTelephoneFlag = 0;						/* 電話帳電話発呼要求フラグをクリア						*/
	BackUpCurrentTime = 0;								/* 最初に時刻指定送信の登録モードにはいった時の現在時刻	*/
	BackUpCurrentTimeSet = 0;							/* 時刻指定送信登録済みフラグ							*/
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
	IsTxOrScanStart = FALSE;							/* 送信・原稿読み取りが実行されていない					*/
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	MailCommandInputInitial();							/* メールコマンド登録用変数初期化 */
	OPR_MailCommand.GetMailCommandFile = 0xFF;			/* コマンド99件なので、一応0xFFで初期化しておく */
	OPR_MailCommand.UserNumber = 0xFF;					/* メール送信起動ユーザの番号 */
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/07 Y.Matsukuma */
	if (CMN_CheckMinoltaTestPrintEnable() == 0xFFFF) {
		OPR_MinoltaPatternCheck = 0xFF;						/* ミノルタテストプリント用バッファ初期化 */
		OPR_MinoltaPagesCheck	= 0;
		OPR_MinoltaOnetouch		= 0;
		OPR_MinoltaPatternItem 	= 0xFF;	/* 1998/08/31 Y.Matsukuma */
		OPR_MinoltaDisplayCheck = 0xFF;
	}
#endif

	command_end = FALSE;
	key_request = 0;									/* キー入力を行なわない（上位からのキーを引き継ぐため）	*/

	/** キー入力を引き継ぐ */
	key = key_code;
	keytype = key_type;

#if (PRO_FBS == ENABLE)
	last_key = OPR_NO_KEY;
#endif

	/* コマンド登録ループ */
	while (1) {
		if (key_request == 1) {		/*キー取り込み実行*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/15 by K.Okada */
			SetInputDialInfoFlag();
#endif
			/* コマンド入力中の表示 */
			DisplayCommandOperation();	/* メール用上段表示を追加 1998/03/13 by K.Okada */

#if (PRO_FBS == ENABLE)
			last_key = key;	/* 前回キー入力値の退避 */
#endif

			/** キー取り込み */
			OPR_GetKey(KEY_WAIT_ONE_MINUTE);
			key = GetInputKeyCode();
			keytype = GetInputKeyType();
		}
		key_request = 1;

		/* 現在の状態より押されたキーが有効かどうかをチェックします */
		CheckOperationValid(&keytype);

		/* 短縮・グループキーの直後のデータ入力チェック */
		if (CheckSpeedGroupAfterEnableKey(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

		/* プログラムワンタッチ入力後のデータ入力チェック */
		if (CheckProgramAfterInput(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

#if (PRO_NEW_DIAL_OPR == ENABLE)
		/* 入力データ（短縮・グループ）の登録チェック by K.Watanabe 1998/03/12 */
		if (CheckRegistrationData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

		/* ダイヤルデータ入力チェック by K.Watanabe 1998/03/24 */
#if defined (KEISATSU)		/* 警察FAX QAT Modify by SMuratec K.W.Q 2005/12/20 */
		/* 前後へのダイヤルデータ、属性キーを使用します */
		if ((key >= ONETOUCH_27_KEY) && (key <= ONETOUCH_30_KEY)) {
		}
		else
#endif
		if (CheckInputDialData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

#if (PRO_NEW_DIAL_OPR2 == ENABLE)
		/* 直接ダイヤル入力桁数・件数チェック by K.Watanabe 1998/04/17 */
		if (CheckInputDirectDial(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/31 */
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
			(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
			keytype = NO_EFFECT;	/* メインでは処理は行いません */
		}
#endif		/* End of (defined (KEISATSU)) */

		switch (keytype) {	/* 取り込んだキーのキー種別毎の処理 */
		case NUMBER:		/* ０～９キー				*/
		case AST:			/* ＊キー					*/
		case SHARP:			/* ＃キー					*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* （ダイヤル中のトーンキーが V650と同じくなります）Added by SMuratec L.Z.W 2003/09/18 */
			if (keytype == AST){
				if (InputNumber.Buffer[InputNumber.CursorPosition] == '*'){
					InputNumber.Buffer[InputNumber.CursorPosition] = '!';
					InputNumberDialCharacterSet();
				}
				else{
					InputNumberDialCharacterSet();
					if (InputNumber.Buffer[InputNumber.CursorPosition] == '-'
						|| InputNumber.Buffer[InputNumber.CursorPosition] == '/'
						|| InputNumber.Buffer[InputNumber.CursorPosition] == '!') {
						InputNumber.Buffer[InputNumber.CursorPosition] = '*';
					}
				}
			}
			else {
				InputNumberTenKeySet(key);	/* 入力バッファにデータをセット */
			}
#else
			InputNumberTenKeySet(key);	/* 入力バッファにデータをセット */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;

		case ONETOUCH:		/* ワンタッチキー入力		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/************************************************
			** ワンタッチ登録状態をチェック
			**（未登録、FAX番号、メールアドレスのどれか）
			************************************************/
			switch (CheckOnetouchStoreStatus(key)) { /** ワンタッチの登録状態チェック */
			case SYS_INF_ONETOUCH_FAXNUMBER:	/** FAX番号 */
				InputNumberOnetouchSet(key);	/* ワンタッチをバッファにセット */
				if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
					if ((CheckInputSpecialCommand() == FALSE) && (CheckInputBroadcast() == FALSE)) {
					/* 応用機能未登録かつ同報未入力の時、ワンタッチ発呼を行う */
						if (CommandStartOperation() == OPR_END) {
							command_end = TRUE;
						}
					}
				}
				break;
			case SYS_INF_ONETOUCH_MAILADDRESS:	/** メールアドレス */
				SendMailCommandOperation(key, keytype);		/** メールオペレーション関数 */
				command_end = MailCommandEndFlag;	/** コマンドエンドフラグ */
				break;
			case SYS_INF_ONETOUCH_NO_ENTRY:		/** 未登録 */
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
				NackBuzzer();
 #if (PRO_FBS == ENABLE)
				if ((CheckNoCommandData() == TRUE) && (!IsBookDocSizeSet)) {	/* 何も登録されていない */
					/* 終了する */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					ReleaseMailCommandFileRequest = TRUE; /** メールコマンドファイル解放要求フラグセット */
					command_end = TRUE;
				}
 #else
				if (CheckNoCommandData() == TRUE) {	/* 何も登録されていない */
					/* 終了する */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					ReleaseMailCommandFileRequest = TRUE; /** メールコマンドファイル解放要求フラグセット */
					command_end = TRUE;
				}
 #endif
				break;
			}
#else
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/16 Y.Matsukuma */
  #if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1998/10/06 Y.Matsukuma */
			if (key >= ONETOUCH_A_KEY && key <= ONETOUCH_R_KEY) {
  #else
			if (key >= ONETOUCH_01_KEY && key <= ONETOUCH_18_KEY) {
  #endif
				MinoltaTestPatternPrint(key);
			}
			else {
				NackBuzzer();
			}
			return;
 #endif
			if (CheckInputOnetouchEnable(key) == TRUE) {	/* セット可能（有効なワンタッチ） */
				InputNumberOnetouchSet(key);	/* ワンタッチをバッファにセット */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
  #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
if (ROM_SW_SpecialDoctorReport) {
					if (key == ONETOUCH_01_KEY || key == ONETOUCH_06_KEY) {
						OPR_SpecialDoctorReportFlag = key;
						if (CommandStartOperation() == OPR_END) {
							command_end = TRUE;
						}
						OPR_SpecialDoctorReportFlag = 0;
					}
					else {
						if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
							if ((CheckInputSpecialCommand() == FALSE) && (CheckInputBroadcast() == FALSE)) {
							/* 応用機能未登録かつ同報未入力の時、ワンタッチ発呼を行う */
								if (CommandStartOperation() == OPR_END) {
									command_end = TRUE;
								}
							}
						}
					}
}
else {
					if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
						if ((CheckInputSpecialCommand() == FALSE) && (CheckInputBroadcast() == FALSE)) {
						/* 応用機能未登録かつ同報未入力の時、ワンタッチ発呼を行う */
							if (CommandStartOperation() == OPR_END) {
								command_end = TRUE;
							}
						}
					}
}
  #else
				if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
					if ((CheckInputSpecialCommand() == FALSE) && (CheckInputBroadcast() == FALSE)) {
					/* 応用機能未登録かつ同報未入力の時、ワンタッチ発呼を行う */
						if (CommandStartOperation() == OPR_END) {
							command_end = TRUE;
						}
					}
				}
  #endif
 #else
				if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
					if ((CheckInputSpecialCommand() == FALSE) && (CheckInputBroadcast() == FALSE)) {
					/* 応用機能未登録かつ同報未入力の時、ワンタッチ発呼を行う */
						if (CommandStartOperation() == OPR_END) {
							command_end = TRUE;
						}
					}
				}
 #endif
			}
			else {											/* セット不可能（無効なワンタッチ） */
 #if (PRO_FBS == ENABLE)
				if ((CheckNoCommandData() == TRUE) && (!IsBookDocSizeSet)) {	/* 何も登録されていない */
					/* 終了する */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					command_end = TRUE;
				}
 #else
				if (CheckNoCommandData() == TRUE) {	/* 何も登録されていない */
					/* 終了する */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					command_end = TRUE;
				}
 #endif
			}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/13 by K.Okada */
			break;

		case PROGRAM:		/* プログラムキー			*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/05 */
			if ( (key >= ONETOUCH_27_KEY) && (key <= ONETOUCH_30_KEY)){
				switch (key){
				case ONETOUCH_27_KEY:			/* 警電/加入 */	/* ワンタッチ２７キー		*/
					if (CMN_CheckHDSTOnSTD() || CMN_CheckHDSTOnEXT()) {
						NackBuzzer();
						break;
					}
					KeidenKeyOperation();
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
				}
#if (0)		/* 警察FAX QAT Deleted by SMuratec K.W.Q 2005/12/19 */
				/* 表示用バッファの初期化 */
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
				ClearDisplayHigh();
 #endif
				DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
				DisplayStringHigh(0 , FunctionDisplayBufferHigh);
#endif
				break;
			}
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/********************************************
			** メールアドレスグループが登録されている
			** かどうかチェック
			********************************************/
			program = key - (UBYTE)OPR_TOP_PROGRAM_KEY;
			if (CheckProgramStoreStatus(program) == OPR_PRG_MAIL_GROUP) { /**メールアドレスワンタッチが登録されている*/
				SendMailCommandOperation(key, keytype);		/** メールオペレーション関数 */
				command_end = MailCommandEndFlag;	/** コマンドエンドフラグの値(メールオペレーション関数の中でセットされる) */
			}
			else if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) { /** 未登録 */
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
				NackBuzzer();
 #if (PRO_FBS == ENABLE)
				if ((CheckNoCommandData() == TRUE) && (!IsBookDocSizeSet)) {	/* 何も登録されていない */
					command_end = TRUE;	/* 終了する */
				}
 #else
				if (CheckNoCommandData() == TRUE) {	/* 何も登録されていない */
					command_end = TRUE;	/* 終了する */
				}
 #endif
			}
			else { /** プログラムワンタッチ登録状態がFAX関係 */
				if ((CheckDestKindInInputBuffer() != IS_MAIL_ADDRESS)
				&&	(CheckDestKindInInputBuffer() != IS_MAIL_FAX_DESTINATION)) { /** 入力バッファにメールアドレスが入っていない */
					if (CheckInputP_OnetouchEnable(program) == TRUE) {	/** プログラムワンタッチ発呼可能 */
						InputNumberProgramSet(key);		/* プログラムワンタッチをバッファにセット */
						exec_program = program;
						if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
							/** プログラムワンタッチ発呼 */
 #if (PRO_BATCH_TX == ENABLE)
							if (SYB_ProgramOnetouch[exec_program].Option.Item == SYS_BATCH_MEMORY_TX) {
								is_scan_start = ProgramOnetouchBatch(exec_program);
							}
							else {
								is_scan_start = ProgramOnetouchExecute(exec_program);
							}
 #else
							is_scan_start = ProgramOnetouchExecute(exec_program);
 #endif
 #if (PRO_FBS == ENABLE)
							if (!is_scan_start) {
								if (OPR_InputDialInfo & PROGRAM_INPUT) {	/* 送信できていない時 【条件追加】By S.Fukui Apr.22,1998 */
									OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
									SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
									IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
								}
							}
 #endif
							/* 結果的に発呼できていなくても終了 */
							command_end = TRUE;
						}
					}
				}
				else {
					OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
					NackBuzzer();
				}
			}
#else
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/20 Y.Matsukuma */
			if (CMN_CheckPrinting()	== TRUE || OPR_MinoltaPatternCheck != 0xFF) {	/* テストプリント中 */
				OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
				NackBuzzer();
				return;
			}
			program = key - (UBYTE)OPR_TOP_PROGRAM_KEY;
			if (MinoltaStandardPG(key, program) == TRUE) {
				return;
			}
			if (CheckInputP_OnetouchEnable(program) == TRUE) {	/** プログラムワンタッチ発呼可能 */
				OPR_MinoltaOnetouch = program;
				OPR_MinoltaPatternCheck = 8;
				OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
				OPR_MinoltaDisplayCheck = program + 1;
				MinoltaTestPatternPrintPG();
				return;
 #else
			program = key - (UBYTE)OPR_TOP_PROGRAM_KEY;
			if (CheckInputP_OnetouchEnable(program) == TRUE) {	/** プログラムワンタッチ発呼可能 */
 #endif
				InputNumberProgramSet(key);		/* プログラムワンタッチをバッファにセット */
				exec_program = program;
				if (IsOnetouchAutoStart) {	/* ワンタッチ発呼が従来通り、スタートキーなしの時 */
					/** プログラムワンタッチ発呼 */
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
					switch (CheckProgramStoreStatus(exec_program)) {
					case OPR_PRG_LIST:			/* リスト					*/
						for (i = 0; OPR_ProgramList[i].Item != 0xFE; i++) {
							if (OPR_ProgramList[i].Item == SYB_ProgramOnetouch[exec_program].EntryData.ListItem) {
								(OPR_ProgramList[i].EnterFunction)();
								break;
							}
						}
						is_scan_start = OPR_END;
						break;
					case OPR_PRG_STORE:			/* 蓄積						*/
						for (i = 0; OPR_ProgramStore[i].Item != 0xFE; i++) {
							if ((OPR_ProgramStore[i].Item == SYB_ProgramOnetouch[exec_program].EntryData.StoreData.Item)
							 || ((SYB_ProgramOnetouch[exec_program].EntryData.StoreData.Item == MSG_STORE_DBPOLLING_DOC)
							 && (OPR_ProgramStore[i].Item == MSG_STORE_POLLING_DOC))) {
								(OPR_ProgramStore[i].EnterFunction)(exec_program);
								break;
							}
						}
						is_scan_start = OPR_END;
						break;
  #if (PRO_BATCH_TX == ENABLE) /* By H.Fujimura 1999/01/06 */
					case OPR_PRG_BATCH_TX:		/* 一括送信					*/
						is_scan_start = ProgramOnetouchBatch(exec_program);
						break;
  #endif
					default:
						is_scan_start = ProgramOnetouchExecute(exec_program);
						break;
					}
 #else
  #if (PRO_BATCH_TX == ENABLE)
					if (SYB_ProgramOnetouch[exec_program].Option.Item == SYS_BATCH_MEMORY_TX) {
						is_scan_start = ProgramOnetouchBatch(exec_program);
					}
					else {
						is_scan_start = ProgramOnetouchExecute(exec_program);
					}
  #else
					is_scan_start = ProgramOnetouchExecute(exec_program);
  #endif
 #endif
 #if (PRO_FBS == ENABLE)
					if (!is_scan_start) {
						if (OPR_InputDialInfo & PROGRAM_INPUT) {	/* 送信できていない時 【条件追加】By S.Fukui Apr.22,1998 */
							OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
							SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
							IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
						}
					}
 #endif
					/* 結果的に発呼できていなくても終了 */
					command_end = TRUE;
				}
			}
			else {
 #if (PRO_FBS == ENABLE)
				if ((CheckNoCommandData() == TRUE) && (!IsBookDocSizeSet)) {	/* 何も登録されていない */
					command_end = TRUE;	/* 終了する */
				}
 #else
				if (CheckNoCommandData() == TRUE) {	/* 何も登録されていない */
					command_end = TRUE;	/* 終了する */
				}
 #endif
			}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/13 by K.Okada */
			break;

		case SPEED:			/* 短縮						*/
			/* 直前の入力が短縮キーの場合 */
			if (CheckPreDataSpeedMark()) {
				/* 短縮記号を消去しておく */
				InputNumber.CursorPosition--;
				InputNumberClearDelete();

				/** 電話帳オペレーション実行 */
				tel_book_ope_rtn = TelephoneBookOperation(OPR_COM_OPE);

#if (PRO_NEW_DIAL_OPR == ENABLE)	/* by K.Watanabe 1998/04/03 */
				/* 電話帳でデータが選択されて、かつＰＩＮ番号が必要な時は、ＰＩＮ番号の登録状態を調べます */
				if ((tel_book_ope_rtn != TELBOOK_END) && (tel_book_ope_rtn != TELBOOK_SPEED_KEY)
				 && (InputNumber.PIN_NumberCheck == YES)) {
					data_number = (UWORD)SYB_TelephoneBookData[GetTelBookDataPoint()][OPR_TELBOOK_DATANUMBER];
					if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチダイヤルが選択された時 */
						if (CheckOnetouchPinNumberStore(CMN_OffsetToOnetouchCode((UBYTE)data_number)) == FALSE) {
							/* ＰＩＮ番号が未登録の時 */
							NackBuzzer();
							OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
							break;
						}
					}
					else {									/* 短縮ダイヤルが選択された時 */
						data_number -= SYS_ONETOUCH_MAX;
						if (CheckSpeedPinNumberStore((UBYTE)data_number) == FALSE) {	/* ＰＩＮ番号が未登録の時 */
							NackBuzzer();
							OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
							break;
						}
					}
				}
#endif

				switch (tel_book_ope_rtn) {
				case TELBOOK_FAXCOM:
					SetTelBookDataToInputBuffer();
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 電話帳から連続ポーリングを実行させるため追加 1997/10/24 Y.Matsukuma */
					if (SpecialCommandValue.CommandOption.Item == SYS_CONTINUOUS_POLLING) {
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
						if ((CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS)
						||	(CheckDestKindInInputBuffer() == IS_MAIL_FAX_DESTINATION)) {
							NackBuzzer();
						}
						else {
							if (SetContPollingCommandTime() == OPR_END) {	/* 連続ポーリングコマンド用データに展開 */
								command_end = TRUE;
							}
						}
						break;
 #else
						if (SetContPollingCommandTime() == OPR_END) {	/* 連続ポーリングコマンド用データに展開 */
							command_end = TRUE;
						}
						break;
 #endif
					}
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
					if (CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS) {	/** 無いはず */
						if((com_set_flg = CheckPreMailCommandSet()) == OPR_END) {
							ReleaseMailCommandFileRequest = TRUE;	/** メールコマンドファイル解放要求セット */
							command_end = TRUE;				/** コマンドエンドフラグをセット */
						}
						else if (com_set_flg == OPR_MAIL_CONTINUE) {	/** カーソル位置がメールアドレス */
							SendMailCommandOperation(key, keytype);
							command_end = MailCommandEndFlag;
						}
						else if (com_set_flg == OPR_CONTINUE) {
							/** 何もしない */
						}
						else {
							MailCommandSet();		/** メールコマンドセット関数 */
							MailCommandMessageToMain();	/** メインへメッセージ */
							command_end = TRUE;		/** コマンドエンドフラグをセット */
						}
					}
					else if (CheckDestKindInInputBuffer() == IS_MAIL_FAX_DESTINATION) {
						if ((com_set_flg = CheckPreMixedCommandSet()) == OPR_END) {
							ReleaseMailCommandFileRequest = TRUE;
							/** FAXコマンドファイル解放要求はCheckPreMixedCommandSet()で */
							command_end = TRUE;
						}
						else if (com_set_flg == OPR_MAIL_CONTINUE) {	/** カーソル位置がメールアドレス */
							SendMailCommandOperation(key, keytype);
							command_end = MailCommandEndFlag;
						}
						else if (com_set_flg == OPR_CONTINUE) {
							/** 何もしない */
						}
						else {
							MixedCommandSet();			/** メールFAXコマンドセット */
							MixedCommandMessageToMain();	/** メインへメッセージ */
							command_end = TRUE;	/** コマンドエンドフラグをセット */
						}
					}
					else {
						if (CommandStartOperation() == OPR_END) {
							command_end = TRUE;
						}
					}
#else
					if (CommandStartOperation() == OPR_END) {
						command_end = TRUE;
					}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/13 by K.Okada */
					break;
				case TELBOOK_SET:
					SetTelBookDataToInputBuffer();
					break;
				case TELBOOK_TEL:
					OPR_TelBookTelephoneFlag = 1;
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
					ReleaseMailCommandFileRequest = TRUE; /* 念のため */
#endif
					command_end = TRUE;
					break;
				case TELBOOK_BROADCAST:
					SetTelBookDataToInputBuffer();
					BroadcastMarkSet();
					break;
				case TELBOOK_SPEED_KEY:
					InputNumberGroupSpeedMarkSet((UBYTE)SPEED_KEY);
					break;
				default:
					break;
				}
			}
			else {/*短縮記号をバッファにセット */
				InputNumberGroupSpeedMarkSet(key);
			}
			BroadcastCheck();
			break;

		case BROADCAST:		/* 同報キー					*/
			BroadcastMarkSet();
			break;

		case GROUP:			/* グループキー				*/
			InputNumberGroupSpeedMarkSet(key);
			break;

		case REDIAL:		/* リダイアル/ポーズキー	*/
			/* バッファが空でリダイアルバッファが空でない */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/**************************************************************
			** メールアドレスを除く宛先番号が未入力であった場合に変更↓
			**************************************************************/
			if (((CheckDestKindInInputBuffer() == IS_EMPTY_DESTINATION)
				|| (CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS))
				&& (SYB_RedialBuffer[0] != NULL)) { /** 入力バッファが空でリダイヤルバッファが空でないか、入力バッファにはメールアドレスのみでリダイヤルバッファが空でない場合 */
				if ((InputNumber.CursorPosition == InputNumber.WritePosition)
					|| ((InputNumber.CursorPosition != 0) && (InputNumber.Buffer[InputNumber.CursorPosition-1] == ','))) {	/** 新規入力位置か、同報区切りの後 */ 
					/* リダイアルバッファの内容をバッファにセット */
					InputNumberRedialSet(); 		/** InputNumber.Buffer[]にコピー */
				}
				else {
					NackBuzzer();
				}
			}
#else
			if ((CheckInputCommandDialNumber() == FALSE) && (SYB_RedialBuffer[0] != NULL)) {
				/* リダイアルバッファの内容をバッファにセット */
				CMN_StringCopy(InputNumber.Buffer, SYB_RedialBuffer);
				InputNumber.WritePosition = GetStringGapPoint(InputNumber.Buffer , NULL);
				InputNumber.CursorPosition = InputNumber.WritePosition;
				BroadcastCheck();
			}
#endif
			else {
				InputNumberDialMarkSet(PAUSE_MARK);
			}
			break;

		case FUNCTION:		/* 機能／右矢印キー			*/
			InputNumberCursorRight();
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/**********************************************
			** カーソル位置の宛先がメールアドレスなら、
			** メールオペレーション関数をコールする
			**********************************************/
			if ((CheckDestKindAtCursorPosition() == IS_MAIL_ADDRESS)
			&&	(CheckOnetouchAtCursorPosition() == FALSE)) { /** カーソル位置の文字がメールアドレスである */
				SendMailCommandOperation(key, keytype);		/** メールオペレーション関数 */
				command_end = MailCommandEndFlag;	/** コマンド入力終了フラグ */
			}
#endif
			break;

#if (PRO_FBS == ENABLE)
		case NEXT_DOC:		/* 次原稿キー				*/
			if (InputNumber.WritePosition == 0) {	/* 相手先番号が未登録の時 */
				BookNextDocumentSet(last_key, TRUE);
			}
			else {									/* 相手先番号が登録されている時 */
				InputNumberCursorLeft();	/* カーソル移動（左） */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
				/**********************************************
				** カーソル位置の宛先がメールアドレスなら、
				** メールオペレーション関数をコールする
				**********************************************/
				if ((CheckDestKindAtCursorPosition() == IS_MAIL_ADDRESS)
				&&	(CheckOnetouchAtCursorPosition() == FALSE)) { /** カーソル位置の文字がﾒｰﾙｱﾄﾞﾚｽである */
					SendMailCommandOperation(key, keytype);		/** メールオペレーション関数 */
					command_end = MailCommandEndFlag;	/** コマンド入力終了フラグ */
				}
#endif
			}
			break;
#else
		case LEFT_ARROW:	/* 左矢印キー				*/
			InputNumberCursorLeft();
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/**********************************************
			** カーソル位置の宛先がメールアドレスなら、
			** メールオペレーション関数をコールする
			**********************************************/
			if ((CheckDestKindAtCursorPosition() == IS_MAIL_ADDRESS)
			&&	(CheckOnetouchAtCursorPosition() == FALSE)) { /** カーソル位置の文字がﾒｰﾙｱﾄﾞﾚｽである */
				SendMailCommandOperation(key, keytype);		/** メールオペレーション関数 */
				command_end = MailCommandEndFlag;	/** コマンド入力終了フラグ */
			}
#endif
			break;
#endif

		case CLEAR:			/* クリアキー				*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/* 枚数指定・応用通信とその他の処理をわけました。97/11/28 T.Fukumoto */
			if ((CheckInputSpecialCommand() == TRUE) || (SpecialCommandValue.Page != 0)) {    /* 枚数指定・応用通信 */
				InputNumberDataClear();		/* データクリア実行 */
			}
			else {
				/* 同報の場合、入力データがないときにクリアキーを押すと、
				** ナックブザーを鳴らさないで待機状態に戻す。
				*/
				if (CheckInputCommandDialNumber() == TRUE) {
					InputNumberDataClear();	/* データクリア実行 */
				}

				if (CheckInputCommandDialNumber() == FALSE) {	/* 入力データがなくなったとき */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					command_end = TRUE;		/* 終了する */
				}
			}
			if (CheckDestKindInInputBuffer() == IS_EMPTY_DESTINATION) {
				ReleaseCommandFileRequest = TRUE;
				ReleaseMailCommandFileRequest = TRUE;
				command_end = TRUE;
			}
			else {
				if (CheckDestKindInInputBuffer() == IS_FAX_NUMBER) {
					ReleaseMailCommandArea();	/** メールコマンドファイル解放 */
					ReleaseMailCommandFileRequest = FALSE;
					ReleaseCommandFileRequest = FALSE;
					command_end = FALSE;
				}
				/*****************************************************************
				** メールアドレスだけが残った場合、FAXの場合はスタートを押すまで、
				** コマンドを掴んでいないので、解放要求の必要がない
				*****************************************************************/
				/**********************************************
				** カーソル位置の文字がメールアドレスである
				** かどうかを調べる
				**********************************************/
				else {
					if ((CheckDestKindAtCursorPosition() == IS_MAIL_ADDRESS) /** カーソル位置がメールアドレスである */
					&&	(CheckOnetouchAtCursorPosition() == FALSE)) {
						SendMailCommandOperation(key, keytype);				/** メールオペレーション関数 */
						command_end = MailCommandEndFlag;			/** コマンドエンドフラグの値 */
					}
				}
			}
#else
			/* 枚数指定・応用通信とその他の処理をわけました。97/11/28 T.Fukumoto */
			if ((CheckInputSpecialCommand() == TRUE) || (SpecialCommandValue.Page != 0)) {    /* 枚数指定・応用通信 */
				InputNumberDataClear();		/* データクリア実行 */
			}
			else {
				/* 同報の場合、入力データがないときにクリアキーを押すと、
				** ナックブザーを鳴らさないで待機状態に戻す。
				*/
				if (CheckInputCommandDialNumber() == TRUE) {
					InputNumberDataClear();	/* データクリア実行 */
				}

				if (CheckInputCommandDialNumber() == FALSE) {	/* 入力データがなくなったとき */
					ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
					command_end = TRUE;		/* 終了する */
				}
			}
#endif
			break;

		case DIALMARK:		/* ダイアル記号キー			*/

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			if (InputNumber.Buffer[InputNumber.CursorPosition] == DIRECT_ADDRESS_MARK) {
				if ((InputNumber.CursorPosition == 0)
				||	(InputNumber.Buffer[InputNumber.CursorPosition - 1] == ',')) {
					InputDialMarkSet('-');
					BroadcastMarkSet();
					InputNumber.CursorPosition -= 2;
					for ( ; InputNumber.CursorPosition > 0; InputNumber.CursorPosition--) {
						if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
						|| (InputNumber.Buffer[InputNumber.CursorPosition] == '!')
						|| (InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {
							break;
						}
					}
					break;
				}
			}
			SwitchDialMark(key, keytype);
			BroadcastCheck();	/** 同報の宛先がバッファに入っているかチェック */
			command_end = MailCommandEndFlag;		/** コマンドエンドフラグの値 */
#else
			InputNumberDialCharacterSet();
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/13 by K.Okada */
			break;

#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE:			/* トーンキー 				*/	/* 追加 97/11/13 T.Fukumoto */
			InputNumberDialMarkSet(TONE_MARK);
			break;
#endif

#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH:			/* フラッシュキー			*/
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/13 Y.Matsukuma */
			if (CMN_CheckMinoltaTestFuncEnable()) {
  #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* M.Tachibana 1998/10/08 */
				MinoltaTestOperation(FLASH);
  #else
				MinoltaTestOperation(HOLD);
  #endif
				return;
			}
 #endif
			InputNumberDialMarkSet(FLASH_MARK);
			break;
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* 1996/07/16 by H.Yagi *//* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
		case MERCURY:		/* マーキュリーキー			*/
			InputNumberDialMarkSet(MERCURY_MARK);
			break;
#endif
#if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
		case GROUND:
			if(CHK_UNI_GroundkeyCheck()){
				InputNumberDialMarkSet(PAUSE_MARK);
			}else{
				NackBuzzer();
			}
			break;
#endif

#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
		case COPY_RESET:	/* コピーリセットキー		*/
 #else
		case HOLD:			/* 保留キー					*/
 #endif
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/22 Y.Matsukuma */
  #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* M.Tachibana 1998/10/08 */
			if (CMN_CheckMinoltaTestFuncEnable()) {
				MinoltaTestOperation(HOLD);
				return;
			}
  #endif
 #endif
			/* 内線番号を示す「！」を保留キーにて入力 */
			InputNumberDialMarkSet(MULTI_TEL_MARK);
			break;
#endif

		case SPECIAL:		/* 応用通信					*/
			/* 初期登録で一度番号を入力し、クリアキーでダイヤルを消した後に応用通信キーを押しても、
			** 一括送信のメニューが出てこない不具合の修正のために、直前で毎回 OPR_BatchTxEnableFlagを
			** セットし直すように変更しました by K.Watanabe 1997/11/06
			*/
			OPR_BatchTxEnableFlag = TRUE;	/* 基本的に一括送信可能 */
			if (CheckInputCommandDialNumber() == TRUE) {	/* 番号入力後、応用通信キーが押された時 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
				/**************************************
				** メールアドレスが入っている場合は
				** 一括送信登録不可能にしておく
				**************************************/
				if (CheckDestKindInInputBuffer() == IS_FAX_NUMBER) {	/** バッファにFAX番号のみの場合 */
					if (CheckCommandNumber() == OK) {	/* 入力済みの番号が正しい場合 */
						OPR_BatchTxEnableFlag = FALSE;	/* 一括送信登録不可能 */
					}
					else {
						/* 応用通信登録不可 */
						NackBuzzer();
						break;
					}
				}
				else {
					/* HEXコード入力中はＮＧ*/
					if (CheckHexCodeInput() == TRUE) {
						NackBuzzer();
						break;
					}

					if (CheckCorrectAllCommand() == OK) { /** 入力済みのFAX番号とメールアドレスが正しい場合 */
						OPR_BatchTxEnableFlag = FALSE;   /** 一括送信登録不可能 */
					}
					else {
						NackBuzzer();					/** 応用通信登録不可 */
						break;
					}
				}
#else
				if (CheckCommandNumber() == OK) {	/* 入力済みの番号が正しい場合 */
					OPR_BatchTxEnableFlag = FALSE;	/* 一括送信登録不可能 */
				}
				else {
					/* 応用通信登録不可 */
					NackBuzzer();
					break;
				}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/13 by K.Okada */
			}

			/* 既に時刻指定等の応用機能をセットしたあとで、一括送信を登録した場合、*/
			/* 送信時刻等は一括送信のものに上書きされる */
			if ((SpecialCommandOperation(OPR_COM_OPE) == NG)
			 || (SpecialCommandValue.CommandOption.Item == SYS_BATCH_MEMORY_TX)) {
				/* 応用通信登録中断か一括送信が登録された時 */
				ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
				ReleaseMailCommandFileRequest = TRUE;	/** メールコマンドファイル解放要求セット */
#endif
				command_end = TRUE;
			}
			break;

		case KEY_TIME_UP:	/* キー入力なしで１分間経過	*/
		case STOP:			/* ストップキー				*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/01 */
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
			if ((NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
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
			}
#endif		/* End of (defined (KEISATSU)) */
			ReleaseCommandFileRequest = TRUE; /* 1995/12/20 Eguchi */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			ReleaseMailCommandFileRequest = TRUE;	/** メールコマンドファイル解放要求セット */
#endif
			command_end = TRUE;
			break;

		case START:			/* スタートキー				*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			/************************************************
			** メールアドレスがバッファにセット
			** されているかどうか
			************************************************/
			if ((CheckDestKindInInputBuffer() != IS_MAIL_ADDRESS)
				&& (CheckDestKindInInputBuffer() != IS_MAIL_FAX_DESTINATION)) {	/** メールアドレスがバッファにセットされていない */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				if (SpecialCommandValue.CommandOption.Item == SYS_CONTINUOUS_POLLING) {
					if (SetContPollingCommandTime() == OPR_END) {	/* 連続ポーリングコマンド用データに展開 */
						command_end = TRUE;
					}
					break;
				}
 #endif

				if ((OPR_InputDialInfo & PROGRAM_INPUT)	/* プログラムワンタッチが入力されている時 */
				 && (!IsOnetouchAutoStart)) {			/* ワンタッチ発呼でスタートキーが必要な時 */
					/** プログラムワンタッチ発呼 */
 #if (PRO_BATCH_TX == ENABLE)
					if (SYB_ProgramOnetouch[exec_program].Option.Item == SYS_BATCH_MEMORY_TX) {
						is_scan_start = ProgramOnetouchBatch(exec_program);
					}
					else {
						is_scan_start = ProgramOnetouchExecute(exec_program);
					}
 #else
					is_scan_start = ProgramOnetouchExecute(exec_program);
 #endif
					if (is_scan_start == OPR_END) {
						if (OPR_InputDialInfo & PROGRAM_INPUT) {	/* 送信できていない時 */
							OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
 #if (PRO_FBS == ENABLE)
							SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
							IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
 #endif
						}
						/* 結果的に発呼できていなくても終了 */
						command_end = TRUE;
					}
					break;
				}

				if (CommandStartOperation() == OPR_END) {
					command_end = TRUE;
				}
			}
			else if (CheckDestKindInInputBuffer() == IS_MAIL_FAX_DESTINATION) {
				if ((com_set_flg = CheckPreMixedCommandSet()) == OPR_END) {
					ReleaseMailCommandFileRequest = TRUE;
					ReleaseCommandFileRequest = TRUE;
					command_end = TRUE;
				}
				else if (com_set_flg == OPR_MAIL_CONTINUE) {	/** カーソル位置がメールアドレス */
					SendMailCommandOperation(key, keytype);
					command_end = MailCommandEndFlag;
				}
				else if (com_set_flg == OPR_CONTINUE) {
					/** 何もしない */
				}
				else {
					MixedCommandSet();	/** メールFAXコマンドセット関数 */
					MixedCommandMessageToMain();	/** メインへメッセージ */
					command_end = TRUE;		/** コマンドエンドフラグをセット */
				}
			}
			else if (CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS){/** メールアドレスがバッファにセットされている */
				if((com_set_flg = CheckPreMailCommandSet()) == OPR_END) {
					ReleaseMailCommandFileRequest = TRUE;	/** メールコマンドファイル解放要求セット */
					command_end = TRUE;				/** コマンドエンドフラグをセット */
				}
				else if (com_set_flg == OPR_MAIL_CONTINUE) {	/** カーソル位置がメールアドレス */
					SendMailCommandOperation(key, keytype);
					command_end = MailCommandEndFlag;
				}
				else if (com_set_flg == OPR_CONTINUE) {
					/** 何もしない */
				}
				else {
					MailCommandSet();		/** メールコマンドセット関数 */
					MailCommandMessageToMain();	/** メインへメッセージ */
					command_end = TRUE;		/** コマンドエンドフラグをセット */
				}
			}
			else {
				NackBuzzer();
			}
#else

#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
		 /* ダイアル番号を入力されスタートキーを押下されると
			入力されたダイアル番号を、SGPダイアルバッファに記憶し、メインタスクに通知する。
			ＯＰＲは待機モードに移る */
			SetSgpDialNumber();
			OperationMessageToMain.Message = MSG_ENTER_COMMAND;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
			command_end = TRUE;
#else /** PRO_SGP_TEST_ROM == ENABLE */

 #if (PRO_CONTINUOUS_POLLING == ENABLE)
			if (SpecialCommandValue.CommandOption.Item == SYS_CONTINUOUS_POLLING) {
				if (SetContPollingCommandTime() == OPR_END) {	/* 連続ポーリングコマンド用データに展開 */
					command_end = TRUE;
				}
				break;
			}
 #endif

			if ((OPR_InputDialInfo & PROGRAM_INPUT)	/* プログラムワンタッチが入力されている時 */
			 && (!IsOnetouchAutoStart)) {			/* ワンタッチ発呼でスタートキーが必要な時 */
				/** プログラムワンタッチ発呼 */
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
					switch (CheckProgramStoreStatus(exec_program)) {
					case OPR_PRG_LIST:			/* リスト					*/
						for (i = 0; OPR_ProgramList[i].Item != 0xFE; i++) {
							if (OPR_ProgramList[i].Item == SYB_ProgramOnetouch[exec_program].EntryData.ListItem) {
								(OPR_ProgramList[i].EnterFunction)();
								break;
							}
						}
						is_scan_start = OPR_END;
						break;
					case OPR_PRG_STORE:			/* 蓄積						*/
						for (i = 0; OPR_ProgramStore[i].Item != 0xFE; i++) {
							if ((OPR_ProgramStore[i].Item == SYB_ProgramOnetouch[exec_program].EntryData.StoreData.Item)
							 || ((SYB_ProgramOnetouch[exec_program].EntryData.StoreData.Item == MSG_STORE_DBPOLLING_DOC)
							 && (OPR_ProgramStore[i].Item == MSG_STORE_POLLING_DOC))) {
								(OPR_ProgramStore[i].EnterFunction)(exec_program);
								break;
							}
						}
						is_scan_start = OPR_END;
						break;
  #if (PRO_BATCH_TX == ENABLE) /* By H.Fujimura 1999/01/06 */
					case OPR_PRG_BATCH_TX:		/* 一括送信					*/
						is_scan_start = ProgramOnetouchBatch(exec_program);
						break;
  #endif
					default:
						is_scan_start = ProgramOnetouchExecute(exec_program);
						break;
					}
 #else
  #if (PRO_BATCH_TX == ENABLE)
				if (SYB_ProgramOnetouch[exec_program].Option.Item == SYS_BATCH_MEMORY_TX) {
					is_scan_start = ProgramOnetouchBatch(exec_program);
				}
				else {
					is_scan_start = ProgramOnetouchExecute(exec_program);
				}
  #else
				is_scan_start = ProgramOnetouchExecute(exec_program);
  #endif
 #endif
				if (is_scan_start == OPR_END) {
					if (OPR_InputDialInfo & PROGRAM_INPUT) {	/* 送信できていない時 */
						OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
 #if (PRO_FBS == ENABLE)
						SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
						IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
 #endif
					}
					/* 結果的に発呼できていなくても終了 */
					command_end = TRUE;
				}
				break;
			}

 #if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正 Added by SMuratec 李 2004/11/09 */
			IsScanTx = TRUE;
			if (CommandStartOperation() == OPR_END) {
				command_end = TRUE;
			}
			IsScanTx = FALSE;
  #else
			if (CommandStartOperation() == OPR_END) {
				command_end = TRUE;
			}
 #endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
#endif /** PRO_SGP_TEST_ROM == ENABLE */

#endif
			break;

#if (PRO_FBS == ENABLE)
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
			if (BookDocumentSizeSet(OPR_COM_OPE, last_key) == OPR_END) {
				command_end = TRUE;
			}
			break;
#endif

		case SINGLE:		/* 単一オペレーションキー	*/
			SingleKeyOperation(key);
			break;

		case NO_EFFECT:
			break;

		case ERROR_OPERATION:	/* 現在の状態では無効なキー */
			NackBuzzer();
			break;

		default:
			NackBuzzer();
			break;
		}
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/14 */
		if (CheckIsKanyuLine() &&
			(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)){		/*	指令モート,加入側無効 */
			command_end = TRUE;
		} 
#endif
		if (command_end == TRUE) {	/* コマンドオペレーション終了要求あり */
			if (ReleaseCommandFileRequest == TRUE) {	/* コマンドファイル解放 */
				ReleaseCommandArea();
			}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			if (ReleaseMailCommandFileRequest == TRUE) { /** メールコマンドファイル解放要求フラグセットされている */
				ReleaseMailCommandArea();	/** メールコマンドファイル解放（確保されていないなら処理しない） */
			}
#endif

			/* 枚数指定された場合と、されていない場合の判断ができないので、無条件でページ枚数を初期化します */
			/* 注）判断を行う場合はフラグを追加すれば可能ですがプログラム的に好ましくないので止めときます */
			SpecialCommandValue.Page = 0;	/* ページ枚数の初期化 */

#if (PRO_FBS == ENABLE)
			/* 何もしないでCommandOperation()を抜ける時以外は、読み取りを開始しているので
			** メインで初期値に戻してくれますが、ストップキー等で読み取り前に終了する時は、
			** ここでしか初期化しません
			*/
 #if (0)	/* ｽﾀｰﾄｷｰを押した後に、ｴﾗｰ等で待機状態に戻った場合に原稿ｻｲｽﾞが設定されたままになるので条件を変更
			** by K.Watanabe 1998/01/28
			*/
//			if ((keytype == STOP)
//			 || (keytype == CLEAR)
//			 || (keytype == KEY_TIME_UP)
//			 || ((keytype == SPECIAL) && (SpecialCommandValue.CommandOption.Item != SYS_BATCH_MEMORY_TX))
//			 || ((keytype == START) && (CheckPollingCommandInput()))) {
 #endif
			if (!IsTxOrScanStart) {	/* 送信・原稿読み取りが開始されていない時 */
				SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
				IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
			}
#endif
			CursorOff();
			return;
		}
	}
}

/*************************************************************************
	module		:[コマンド登録用のデータを初期化する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void CommandInputInitial(void)
{
	CMN_MemorySet(InputNumber.Buffer,OPR_INPUT_NUMBER_BUFFER_MAX + 1, NULL);
	InputNumber.WritePosition = 0;
	InputNumber.CursorPosition = 0;
	InputNumber.DisplayStartPosition = 0;
	InputNumber.MultiNumberStatus = 0;
	OPR_InputDialInfo = 0;
	ReleaseCommandFileRequest = FALSE;
}

/*************************************************************************
	module		:[ＰＩＮ番号のチェックが必要か調べる]
	function	:[
		1.オペレーション開始時のＰＩＮアクセスモードから、ＰＩＮ番号の入力が必要か調べる
		-> ダイアル番号チェックの時にＰＩＮ番号のチェックも必要かしらべる
		2.ＰＩＮアクセスモードが相手先別ＰＩＮアクセス_(Mode1)でかつ、入力するコマンドタイプが
		　コマンド送信ダイアル或いはプログラムワンタッチの登録の場合、ＰＩＮ番号が必要
		3.ＰＩＮアクセスモードがＯＦＦでなく、一括送信ダイアル入力の場合、ＰＩＮ番号が必要
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/11]
	author		:[江口]
*************************************************************************/
void SetPinCheckStatus(void)
{
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE pin_mode;

	pin_mode = CHK_PIN_AccessMode();

	if (((pin_mode == PIN_ACCESS_MODE1)&&(InputNumber.InputDialType != BATCH_DIAL_TYPE))
	||	((pin_mode != PIN_ACCESS_OFF  )&&(InputNumber.InputDialType == BATCH_DIAL_TYPE))) {
		InputNumber.PIN_NumberCheck = YES;
	}
	else {
		InputNumber.PIN_NumberCheck = NO;
	}
#else
	InputNumber.PIN_NumberCheck = NO;
#endif
}

/*************************************************************************
	module		:[応用機能登録用のデータを初期化する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void ComOptionInputInitial(void)
{
	SpecialCommandValue.CommandOption.Item = SYS_CHAR_TX;		/* 応用機能種別初期化*/
	SpecialCommandValue.CommandTime = 0x00000000UL;				/* 送信指定時刻初期化*/
	/* OptionNumberは初期化しない セットする項目に応じた初期化が必要 */

#if (PRO_DEPARTMENT == ENABLE)
	SpecialCommandValue.DepartmentCode = 0xFFFF;				/* 部門コード初期化 */
#endif

	if (CHK_MessageTxON()) {									/* カバーページ設定初期化 */
		SpecialCommandValue.TitleMessage = YES;
	}
	else {
		SpecialCommandValue.TitleMessage = 0xFF;
	}
#if (PRO_PIN_ACCESS == ENABLE)
	CMN_MemorySet(SpecialCommandValue.PIN_Number, SYS_PIN_MAX, 0xFF);
#endif
	/* SpecialCommandValue.Page = 0;						 @* ページ番号初期化 */
	/* 初期化はしたらあかん 1995/12/06 Eguchi*/

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	SpecialCommandValue.ContPollingStartTime = 0x00000000UL;	/* 連続ポーリング開始時刻初期化 */
	SpecialCommandValue.ContPollingEndTime   = 0x00000000UL;	/* 連続ポーリング終了時刻初期化 */
#endif
}

/*************************************************************************
	module		:[コマンド登録中のLCD表示を行う]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		D2W_EnterFaxNumber
		D2W_InputGroupNumber
		D2W_InputSpeedDialNumber
		D2W_PressStart
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void DisplayCommandOperation(void)
{
#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/12 */
	UWORD	data_top_pos;	/* ダミー引数（ここでは未使用）	*/
	UWORD	data_number;	/* ワンタッチ・短縮の配列番号	*/
	UBYTE	data_kind;		/* カーソル位置の相手先種別		*/
#endif

	if (CheckChildErrorDisplayReq() == TRUE) { /* オペレーション中にエラー発生 */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) { /* チャイルド表示中は表示をかえない*/
		return;
	}

	/* 上段表示 */
	/* バッファになにも入っていない（相手先が入力されていない）*/
	if (InputNumber.WritePosition == 0) {
		DisplayStringHigh(0, D2W_EnterFaxNumber);		/* "ｱｲﾃｻｷ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
	}
	/* 短縮キーが入力された場合 */
	else if (OPR_InputDialInfo & SPEED_MARK_INPUT) {
		DisplayStringHigh(0, D2W_InputSpeedDialNumber);	/* "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
	}
	/* グループキーの直後 */
	else if (OPR_InputDialInfo & GROUP_MARK_INPUT) {
		DisplayStringHigh(0, D2W_InputGroupNumber);		/* "ｸﾞﾙｰﾌﾟﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
	}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/***************************************
	** 上段表示をメール用の場合も追加
	***************************************/
	/** ダイレクトアドレスモード記号が入力された場合 */
	else if (OPR_InputDialInfo & MAIL_DIRECT_MARK_INPUT) {
		DisplayStringHigh(0, D2W_EnterMailAddress);			/* "Enter Address" */
	}
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/12 */
	/* カーソルがワンタッチ・短縮の所にある場合 */
	else if ((InputNumber.Buffer[InputNumber.CursorPosition] != ',')
		  && ((data_kind = GetCursorPositionDataKind(TRUE, &data_top_pos, &data_number))
			  & (OPR_CURSOR_ONETOUCH | OPR_CURSOR_SPEED))) {
		DisplayDialName(data_kind, data_number);
	}
#endif
	else {
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/05 */
		/* 表示用バッファの初期化 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	
 #if (0)		/* 警察FAX QAT_ID2 Deleted by SMuratec K.W.Q 2005/12/06 */
		ClearDisplayHigh();
 #endif
		DisplayKeisatsuSettings(FunctionDisplayBufferHigh);
		DisplayStringHigh(0 , FunctionDisplayBufferHigh);
#else
		DisplayStringHigh(0, D2W_PressStart);			/* "ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      " */
#endif		/* End of (defined (KEISATSU)) */
	}

	/* 下段表示（入力された番号を表示） */
	DisplayCommandNumber();
}

/*************************************************************************
	module		:[入力されたＦＡＸ番号をＬＣＤ下段に表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void DisplayCommandNumber(void)
{
	UBYTE	cursor;	/* カーソル表示位置 */
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P for prefix *//* by K.Watanabe 2004/10/12 */
	UWORD	pos;	/* カーソル位置計算 */
	UWORD	len;
#endif

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/12 *//* by K.Watanabe 2004/10/12 */
	pos = 0;
	len = CMN_StringLength(SYB_MercuryDialBuffer) + 1;
	CMN_MemorySet(InputNumber_Mercury.Buffer,OPR_INPUT_NUMBER_BUFFER_MAX + 1, NULL);
	InputNumber_Mercury.CursorPosition = 0;
	InputNumber_Mercury.DisplayStartPosition = 0;

	ChangeInputBuffer(InputNumber_Mercury.Buffer,InputNumber.Buffer);
	
	while(InputNumber_Mercury.Buffer[pos] != NULL) {
		InputNumber_Mercury.CursorPosition++;
		pos++;
	}
	pos = InputNumber.WritePosition - InputNumber.CursorPosition;
	while(pos) {
		InputNumber_Mercury.CursorPosition--;
		if(InputNumber_Mercury.Buffer[InputNumber_Mercury.CursorPosition] == ']') {
			InputNumber_Mercury.CursorPosition -= len;
		}
		pos--;
	}
	pos = 0;
	while(InputNumber_Mercury.Buffer[pos] != NULL) {
		if (InputNumber_Mercury.CursorPosition <= InputNumber_Mercury.DisplayStartPosition) {
			InputNumber_Mercury.DisplayStartPosition = InputNumber_Mercury.CursorPosition;
			if (InputNumber_Mercury.CursorPosition != 0) {/* カーソル位置がバッファの先頭でない */
				InputNumber_Mercury.DisplayStartPosition--;
			}
		}
		/* カーソル位置が現在の表示開始位置よりも後ろの時　*/
		else {
			/* ２1桁以上離れている時 */
			if (InputNumber_Mercury.CursorPosition - InputNumber_Mercury.DisplayStartPosition >= OPR_DISPLAY_MAX) {
				InputNumber_Mercury.DisplayStartPosition = InputNumber_Mercury.CursorPosition - 19;
			}
		}
		pos++;
	}

	/* カーソル位置が現在の表示開始位置よりまえの時 */
	if (InputNumber.CursorPosition <= InputNumber.DisplayStartPosition) {
		InputNumber.DisplayStartPosition = InputNumber.CursorPosition;
		if (InputNumber.CursorPosition != 0) {/* カーソル位置がバッファの先頭でない */
			InputNumber.DisplayStartPosition--;
		}
	}
	/* カーソル位置が現在の表示開始位置よりも後ろの時　*/
	else {
		/* ２1桁以上離れている時 */
		if (InputNumber.CursorPosition - InputNumber.DisplayStartPosition >= OPR_DISPLAY_MAX) {
			InputNumber.DisplayStartPosition = InputNumber.CursorPosition - 19;
		}
	}

	cursor = (UBYTE)(InputNumber_Mercury.CursorPosition - InputNumber_Mercury.DisplayStartPosition);
	
	if((cursor == 19) && (InputNumber_Mercury.Buffer[InputNumber_Mercury.CursorPosition] == '-')
		&&(InputNumber_Mercury.Buffer[InputNumber_Mercury.CursorPosition + 1] == '!')) {
		InputNumber_Mercury.DisplayStartPosition++;
		cursor = (UBYTE)(InputNumber_Mercury.CursorPosition - InputNumber_Mercury.DisplayStartPosition);
	}
	
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow,
							 &InputNumber_Mercury.Buffer[InputNumber_Mercury.DisplayStartPosition],
							 OPR_DISPLAY_MAX);
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor));

#else /* defined(STOCKHM2) */

	if (InputNumber.CursorPosition <= InputNumber.DisplayStartPosition) {
		InputNumber.DisplayStartPosition = InputNumber.CursorPosition;
		if (InputNumber.CursorPosition != 0) {/* カーソル位置がバッファの先頭でない */
			InputNumber.DisplayStartPosition--;
		}
	}
	/* カーソル位置が現在の表示開始位置よりも後ろの時　*/
	else {
		/* ２1桁以上離れている時 */
		if (InputNumber.CursorPosition - InputNumber.DisplayStartPosition >= OPR_DISPLAY_MAX) {
			InputNumber.DisplayStartPosition = InputNumber.CursorPosition - 19;
		}
	}
	cursor = (UBYTE)(InputNumber.CursorPosition - InputNumber.DisplayStartPosition);
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow,
							 &InputNumber.Buffer[InputNumber.DisplayStartPosition],
							 OPR_DISPLAY_MAX);
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor));

#endif	/* defined(STOCKHM2) */	
}

/*************************************************************************
	module		:[コマンドに関するデータが登録済みが未登録かチェック]
	function	:[
		1.ダイアル番号が登録されているかチェック（バッファが空かどうか）
		2.応用機能がセットされているかチェック
		3.同報通信がセットされているかチェック
		4.原稿枚数が指定されているかチェック	97/12/02 T.Fukumoto

	]
	return		:[
		TRUE;未登録
		FALSE:なにか登録されている
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
UBYTE CheckNoCommandData(void)
{
	/* 全くなにも登録されていない状態かどうか調べる */
	if ((CheckInputCommandDialNumber() == FALSE)
	 && (CheckInputSpecialCommand() == FALSE)
	 && (CheckInputBroadcast() == FALSE)
	 && (SpecialCommandValue.Page == 0)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[ダイアルデータが入力されているか調べる]
	function	:[
		1.
	]
	return		:[
		TRUE :入力されている
		FALSE:入力されていない（入力バッファがから)
	]
	common		:[InputNumber]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputCommandDialNumber(void)
{
	if ((InputNumber.WritePosition == 0) && (InputNumber.Buffer[0] == NULL)) {
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[応用機能がセットされているか調べる]
	function	:[
		1.
	]
	return		:[
		TRUE：登録されている
		FALSE:未登録
	]
	common		:[SpecialCommandValue]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputSpecialCommand(void)
{
	if (SpecialCommandValue.CommandOption.Item == SYS_CHAR_TX) {
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[同報が入力されているか調べる]
	function	:[
		1.
	]
	return		:[
		TRUE：登録されている
		FALSE:未登録
	]
	common		:[InputNumber.MultiNumberStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputBroadcast(void)
{
	if (InputNumber.MultiNumberStatus == 1) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[ワンタッチ使用可能か調べる]
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
	date		:[1996/01/10]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputOnetouchEnable(UBYTE key)
{
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
if (ROM_SW_SpecialDoctorReport) {
		if (key == ONETOUCH_01_KEY || key == ONETOUCH_06_KEY) {
			if ((CheckInputCommandDialNumber() == FALSE)
			 && (CheckInputSpecialCommand() == FALSE)
			 && (CheckInputBroadcast() == FALSE)) {	/* コマンド未入力状態 */
			}
			else {
				NackBuzzer();
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
				return (FALSE);
			}
		}
}
 #endif
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	UBYTE	status;

	status = CheckOnetouchStoreStatus(key);
	if (status == SYS_INF_ONETOUCH_MAILADDRESS) {
		NackBuzzer();
		OPR_ChildErrorFlag = MAIL_ADDRESS_STORED_ERROR;
		return (FALSE);
	}
	else if (status == SYS_INF_ONETOUCH_NO_ENTRY) {
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		return (FALSE);
	}
#else
	if (CheckOnetouchStoreStatus(key) == NG) {	/** ワンタッチ未登録 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		return (FALSE);
	}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */

	/* ＰＩＮアクセスの処理追加 */
	if ((InputNumber.PIN_NumberCheck == YES) && (CheckOnetouchPinNumberStore(key) == 0)) {	/** ＰＩＮ番号未登録 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[プログラムワンタッチ使用可能か調べる]
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
	date		:[1996/01/10]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputP_OnetouchEnable(UBYTE program)
{
	UBYTE	error;

	error = OPR_NO_ERROR;

	if ((CheckInputCommandDialNumber() == FALSE)
	 && (CheckInputSpecialCommand() == FALSE)
	 && (CheckInputBroadcast() == FALSE)) {	/* コマンド未入力状態 */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			/* プログラムワンタッチ未登録 */
			error = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		}
		else if (CheckProgramStoreStatus(program) == OPR_PRG_MAIL_GROUP) {
			/* プログラムワンタッチ未登録 */
			error = MAIL_GROUP_STORED_ERROR;
		}
#else
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			/* プログラムワンタッチ未登録 */
			error = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		}
#endif
#if (PRO_PIN_ACCESS == ENABLE)
 #if (0)	/* この文を下の処理にさしかえます 1997/11/08 Y.Matsukuma */
		/* ＰＩＮ番号の有無を調べる必要あり */
		else if ((InputNumber.PIN_NumberCheck == YES) && (CheckProgramPinNumberStore(program) == FALSE)) {
			/* ＰＩＮ番号なし */
			error = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
		}
 #endif
		/* 
		 * 1997/11/05 Eguchi 
		 * 選択されたプログラムワンタッチに一括送信以外が登録されている場合,PIN番号の有無を調べる.
		 * 一括送信がセットされている場合のＰＩＮ番号の有無のチェックは別のところでやる。
		 *（現在の構成をかえない様にするため) 
		 */
		else if (CheckProgramStoreStatus(program) != OPR_PRG_BATCH_TX) {
			if ((InputNumber.PIN_NumberCheck == YES)
			&&	(CheckProgramPinNumberStore(program) == FALSE)) {
				error = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
			}
		}
#endif
	}
	else {
		/* プログラムワンタッチは同報に使用してはいけません */
		/* 応用通信と結合してもだめ */
		error = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
	}
	if (error == OPR_NO_ERROR) {
		return (TRUE);
	}
	else {
		NackBuzzer();
		OPR_ChildErrorFlag = error;
		return (FALSE);
	}
}

/*************************************************************************
	module		:[直前の入力が短縮記号かどうか調べる]
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
	date		:[1995/12/20]
	author		:[江口]
*************************************************************************/
UBYTE CheckPreDataSpeedMark(void)
{
	if ((InputNumber.CursorPosition != 0) && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == OPR_SPEED_MARK)) {
		return (1);
	}
	return (0);
}

/*************************************************************************
	module		:[カーソル前のデータがワンタッチかどうかチェック]
	function	:[
		1.カーソルの前のデータがワンタッチのＡ～Ｚ、ａ～ｚ、Ｕ１～Ｕ８かどうかを調べる。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		必ず、現在の入力位置が入力バッファの先頭でないことを確認してからコールすること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/06]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckPreDataOnetouch(void)
{
	UBYTE	*pre_data;			/* 直前の入力内容格納アドレス */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	UBYTE	onetouch_number;	/* ワンタッチ番号 */
#endif

	if (InputNumber.CursorPosition == 0) {	/* カーソルが先頭の時 */
		return(FALSE);
	}

	/* 直前のデータのアドレスを取得します */
	pre_data = &InputNumber.Buffer[InputNumber.CursorPosition - 1];

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* ワンタッチの０１～７２ */
#if (0)	/* アンズに合わせると以下の条件になるが、記号の検査だけでも問題は無いので、チェックを簡略化 */
//	onetouch_number = CMN_ASC_ToUnsignedInt(pre_data - 2, (UBYTE)OPR_ONETOUCH_NUMBER_FIGURE);
//	if ((*(pre_data - 3) == OPR_ONETOUCH_MARK_LEFT)
//	 && ((onetouch_number >= 1) && (onetouch_number <= SYS_ONETOUCH_MAX))
//	 && (*pre_data == OPR_ONETOUCH_MARK_RIGHT)) {
#endif
	if (*pre_data == OPR_ONETOUCH_MARK_RIGHT) {
		return(TRUE);
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* ワンタッチのＡ～Ｚ，ａ～ｚ */
	if (CheckOnetouchData(*pre_data) == OPR_ONETOUCH_ALPHABET) {
		return(TRUE);
	}
	/* ワンタッチのＵ１～Ｕ８ */
	onetouch_number = (UBYTE)CMN_ASC_ToUnsignedInt(pre_data, (UBYTE)OPR_ONETOUCH_NUMBER_FIGURE);
	if ((InputNumber.CursorPosition >= 2)
	 && (*(pre_data - 1) == OPR_ONETOUCH_MARK)
	 && ((onetouch_number >= 1) && (onetouch_number <= 8))) {
		return(TRUE);
	}
#endif

	return(FALSE);
}

/*************************************************************************
	module		:[ワンタッチ・短縮・プログラムワンタッチ・グループ入力チェック]
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
	date		:[1996/03/25]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckInputNumberCode(UBYTE data)
{
	/* 指定のデータがワンタッチ・短縮・プログラムワンタッチ・グループかどうかを調べる */
	if ((CheckOnetouchData(data) != OPR_EXCEPT_ONETOUCH)
	 || (data == OPR_SPEED_MARK)
	 || (CheckProgramOnetouchData(data))
	 || (data == OPR_GROUP_MARK)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[短縮・グループキーの直後のデータ入力チェック]
	function	:[
		1.
	]
	return		:[
		TRUE	:有効なキーが押された
		FALSE	:無効なキーが押された
	]
	common		:[]
	condition	:[短縮直後の短縮（電話帳）は上位でチェックすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckSpeedGroupAfterEnableKey(UBYTE keytype)
{
	UBYTE	ret;	/* リターン値 */

	ret = TRUE;

	if (OPR_InputDialInfo & (SPEED_MARK_INPUT | GROUP_MARK_INPUT)) {	/* 短縮・グループキーを押した直後の時 */
		switch (keytype) {
		case SPEED:			/* 短縮キー					*/
			if ((OPR_InputDialInfo & SPEED_MARK_INPUT)				/* 短縮キーを２回続けて押された時 */
			 && (InputNumber.InputDialType == COMMAND_DIAL_TYPE)) {	/* 電話帳が有効な時 */
				OPR_InputDialInfo &= ~SPEED_MARK_INPUT;
			}
			else {
				ret = FALSE;
			}
			break;
		case NUMBER:		/* 数字キー					*/
		case CLEAR:			/* クリアキー				*/
		case STOP:			/* ストップキー				*/
#if (PRO_NEW_DIAL_OPR == DISABLE)	/* by K.Watanabe 1998/04/02 */
			/* 同報の途中で、短縮キーを押した直後にクリアキーを押すと、上段の表示が変わってしまうので、
			** 無条件にフラグをクリアするのを止めます 98/3/20 Add By T.Fukumoto
			** 例）ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      　　→    ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ　 →    ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      
			** 　　[01],[02]           　短縮ｷｰ　[01],S,[02]         　ｸﾘｱｷｰ　[01],S,[02]         
			** 		   ~							   ~							~
 			*/
			if ((keytype == CLEAR)
			 && (CheckInputBroadcast() == TRUE)
			 && (InputNumber.CursorPosition != InputNumber.WritePosition)) {
				break;
			}
#endif
			OPR_InputDialInfo &= ~(SPEED_MARK_INPUT | GROUP_MARK_INPUT);
			break;
#if (PRO_FBS == ENABLE)
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
#endif
		case SINGLE:		/* 単一オペレーションキー	*/
		case KEY_TIME_UP:	/* タイムアップ				*/
		case NO_EFFECT:
		case ERROR_OPERATION:
			break;
		default:
			ret = FALSE;
			break;
		}

		if (ret == FALSE) {	/* 無効なキーが押された時 */
			OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[プログラムワンタッチ入力後のデータ入力チェック]
	function	:[
		1.
	]
	return		:[
		TRUE	:有効なキーが押された
		FALSE	:無効なキーが押された
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/13]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckProgramAfterInput(UBYTE keytype)
{
	UBYTE	ret;	/* リターン値 */

	ret = TRUE;

	if (OPR_InputDialInfo & PROGRAM_INPUT) {	/* プログラムワンタッチが入力されている時 */
		switch (keytype) {
		case CLEAR:			/* クリアキー				*/
		case STOP:			/* ストップキー				*/
			/* 現在は、プログラムワンタッチとの同報はできないので、プログラムワンタッチが
			** 入力されている状態でのクリアキーは、絶対にプログラムワンタッチのクリアなので
			** ここでステータスをクリアします
			** 注）プログラムワンタッチとの同報が有効になった場合には、クリアするタイミングで
			** 　　チェックしてからクリアする必要があります
			** by K.Watanabe 1997/11/13
			*/
			OPR_InputDialInfo &= ~PROGRAM_INPUT;
			break;
		case START:			/* スタートキー				*/
#if (PRO_FBS == ENABLE)
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
#endif
		case SINGLE:		/* 単一オペレーションキー	*/
		case KEY_TIME_UP:	/* タイムアップ				*/
		case NO_EFFECT:
		case ERROR_OPERATION:
			break;
		default:
			ret = FALSE;
			break;
		}

		if (ret == FALSE) {	/* 無効なキーが押された時 */
			OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
		}
	}

	return(ret);
}

#if (PRO_NEW_DIAL_OPR == ENABLE)
/*************************************************************************
	module		:[同報指定時の短縮・グループ登録検査]
	function	:[
		1.ダイヤル番号入力で同報が指定された時に、直前の入力が短縮・グループ
		　かを調べ、実際に登録されているかをチェックします
	]
	return		:[
		TRUE	:・同報でない
				 ・バッファの最後でない
				 ・電話帳を選択した
				 ・直前の入力が短縮・グループでない
				 ・短縮・グループに登録済み
		FALSE	:直前の短縮・グループが未登録（同報指示でバッファの最後の時）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/12]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckRegistrationData(UBYTE key_type)
{
	UWORD	data_top_pos;	/* カーソル位置のデータの先頭位置	*/
	UWORD	data_number;	/* 短縮の配列番号・グループ番号		*/
	UBYTE	data_kind;		/* カーソル位置のデータ種別			*/
	UBYTE	ret;			/* リターン値						*/

	ret = TRUE;

	/* 同報になる時のみチェックを行います */
	if ((key_type == BROADCAST)		/* 同報キー					*/
	 || (key_type == ONETOUCH)		/* ワンタッチキー			*/
	 || (key_type == SPEED)			/* 短縮／電話帳キー			*/
	 || (key_type == GROUP)) {		/* グループキー				*/
		/* ・現時点では短縮番号を一度入力後、カーソルを移動すれば、短縮番号の追加は可能ですが、
		** 　その場合の番号登録チェックは行いません
		** ・短縮キーを押した直後に、もう一度短縮キーが押された場合は、電話帳に移行するので、
		** 　短縮番号登録検査は行いません
		*/
		if ((InputNumber.CursorPosition == InputNumber.WritePosition)			/* バッファの最後の時			*/
		 && ((key_type != SPEED)												/* 短縮キー以外の時				*/
		  || ((key_type == SPEED) && (CheckPreDataSpeedMark() == FALSE)))) {	/* 短縮キーを押した直後でない時	*/
			/* カーソル位置のデータ種別を、取得します */
			data_kind = GetCursorPositionDataKind(TRUE, &data_top_pos, &data_number);
			if (data_kind & OPR_CURSOR_SPEED) {			/* カーソル位置のデータが短縮の時 */
				ret = CheckRegistrationSpeedDial(data_top_pos, data_number);
			}
			else if (data_kind & OPR_CURSOR_GROUP) {	/* カーソル位置のデータがグループの時 */
				ret = CheckRegistrationGroupDial(data_top_pos, data_number);
			}
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[ダイヤルデータ入力検査]
	function	:[
		1.ダイヤル番号入力でカーソル移動を行い同報が指定された時、一度入力
		　した短縮・グループ番号の途中だった時、入力を禁止します
		2.ワンタッチ・短縮・グループの前後へのダイヤルデータ入力を禁止します
	]
	return		:[
		TRUE	:同報でない・直前の入力が短縮でない・短縮番号に登録済み
		FALSE	:同報で、直前の入力が未登録の短縮
	]
	common		:[]
	condition	:[]
	comment		:[
		この内容のチェックは初めにまとめて行うのではなく、それぞれのキーの
		処理の中でチェックする方が、一括送信の時等でも共通で使用できるよう
		になり良いのですが、今の時点での大変更は危険性があるので、今回は止
		めておきます
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/24]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckInputDialData(UBYTE key_type)
{
 #if (PRO_NEW_DIAL_OPR2 == ENABLE)
	UWORD	data_top_pos;	/* カーソル位置のデータの先頭位置	*/
	UWORD	data_num;		/* ダミー引数（ここでは未使用）		*/
 #endif
	UBYTE	data_kind;		/* カーソル位置のデータ種別			*/
	UBYTE	ret;			/* リターン値						*/

	ret = TRUE;

	/* 本当は、初めに１回だけダイヤル種別を取得してその内容を参照すれば良いのだが、
	** 一般的と思われる、直接ダイヤルだけで送信する時には、チェックは必要ないので、
	** あえて必要な所でだけ毎回、種別を取得します
	*/
#if (0)
//	data_kind = GetCursorPositionDataKind(FALSE, NULL, NULL);
#endif

	switch (key_type) {
	case NUMBER:		/* ０～９キー				*/
		/* カーソルが最後以外で、ワンタッチの前後、短縮・グループ記号上にある時は、数字キーの入力を禁止します
		** 例）×  [01],123 → [01],1,123     ×  S001 → 1S001
		** 			   ~			 ~			  ~		  ~
		*/
		if (InputNumber.CursorPosition != InputNumber.WritePosition) {	/* 途中に入力する時 */
			data_kind = GetCursorPositionDataKind(FALSE, NULL, NULL);
			if ((data_kind & OPR_CURSOR_ONETOUCH)
			 || ((data_kind & OPR_CURSOR_SPEED) && (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_SPEED_MARK))
			 || ((data_kind & OPR_CURSOR_GROUP) && (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_GROUP_MARK))) {
				ret = FALSE;
			}
		}
		break;
	/* プログラムワンタッチは、ここでチェックしなくても入力される事はありませんが、ここでチェック
	** しておかないと、｢ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ｣の表示が出てしまいワンタッチ（未表示で弾く）と動作が
	** 違ってくるので、動作統一の為に判断に追加します
	*/
	case BROADCAST:		/* 同報キー					*/
	case ONETOUCH:		/* ワンタッチキー			*/
	case SPEED:			/* 短縮／電話帳キー			*/
	case PROGRAM:		/* プログラムキー			*/
	case GROUP:			/* グループキー				*/
		/* 一度入力した内容の途中に追加する時は、カンマの上のみ有効です（直接ダイヤルの途中の同報記号は除きます）
		** 例）×  S123 → S1,S,23     ×  S123,[01] → S123,S,[01]     ×  -/ → -/,[01]
		** 			 ~		   ~				~			  ~				  ~			 ~
		** 　　○  S123,[01] → S123,S,[01]
		** 			   ~			  ~
		*/
 #if (PRO_NEW_DIAL_OPR2 == ENABLE)
		data_kind = GetCursorPositionDataKind(TRUE, &data_top_pos, &data_num);
 #else
		data_kind = GetCursorPositionDataKind(FALSE, NULL, NULL);
 #endif
		if (InputNumber.CursorPosition != InputNumber.WritePosition) {	/* 途中に入力する時 */
			if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {	/* カンマの上の時 */
				/* 同報キーとプログラムワンタッチは、禁止します */
				if ((key_type == BROADCAST) || (key_type == PROGRAM)) {
					ret = FALSE;
				}
			}
			else {															/* 番号・記号の上の時 */
				/* 直接ダイヤルの途中では、同報記号以外の同報は、禁止します */
				if (data_kind & OPR_CURSOR_DIRECT_DIAL) {	/* カーソル位置が直接ダイヤルの時 */
					if (key_type != BROADCAST) {	/* 同報キー以外の時 */
						ret = FALSE;
					}
				}
				else {										/* カーソル位置がﾜﾝﾀｯﾁ・短縮・ｸﾞﾙｰﾌﾟ・ﾀﾞｲﾔﾙ記号の時 */
					/* データ未入力時は、最後に入力のロジックに入るので、ここでのチェックは必要ありません */
					ret = FALSE;
				}
			}
		}
		else {															/* 最後に入力する時 */
			/* ダイヤル記号しか入力されていない時は、同報を禁止します */
			if (data_kind & OPR_CURSOR_INVALID_DATA) {	/* 同報不可能な時 */
				ret = FALSE;
			}
 #if (PRO_NEW_DIAL_OPR2 == ENABLE)
			else {										/* 同報可能な時 */
				/* 直接ダイヤルで、ＰＩＮ番号が必要な時（ワンタッチ等は、この時点ではチェックされています） */
				if ((InputNumber.PIN_NumberCheck == YES)	/* ＰＩＮ番号が必要な時 */
				 && (data_kind & OPR_CURSOR_DIRECT_DIAL)) {	/* カーソル位置が直接ダイヤルの時 */
					/* カーソル位置の直接ダイヤルにＰＩＮ番号が入力されていない時 */
					if ((GetStringGapPoint(&InputNumber.Buffer[data_top_pos], OPR_PIN_MARK) + 2)
					  > GetStringGapPoint(&InputNumber.Buffer[data_top_pos], ',')) {
						OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
						ret = FALSE;
					}
				}
			}
 #endif
		}
		break;
	case AST:			/* テンキー ＊				*/
	case SHARP:			/* テンキー ＃				*/
 #if (PRO_DIALUP_INTERNET_FAX == DISABLE)	/* 1998/04/13 by K.Okada */
	case DIALMARK:		/* ダイアル記号キー			*/
 #endif
	case REDIAL:		/* リダイアル/ポーズキー	*/
 #if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
	case TONE:			/* トーンキー 				*/
 #endif
 #if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH:			/* フラッシュキー			*/
 #endif
 #if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case MERCURY:		/* マーキュリーキー			*/
 #endif
 #if defined(DEU)
	case GROUND:
 #endif
 #if (PRO_MULTI_LINE == ENABLE)
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)
	case COPY_RESET:	/* コピーリセットキー		*/
  #else
	case HOLD:			/* 保留キー					*/
  #endif
 #endif
		/* ワンタッチ・短縮・グループの直前・途中・直後では、ダイヤルマーク・＊・＃の入力を禁止します
		** 理由）・直前の場合は、入力できるとそのまま送信もできるが、実際は正しく送信出来ません
		** 　　　　（![01]と入力し、送信すると実際には、!/01/に送信します）
		** 　　　・直後の場合は、スタートキー押下でエラーで弾かれるので、動作的にはカンマで
		** 　　　　区切る方法でも問題はありませんが、イチョウに合わせて弾きます
		*/
		if (GetCursorPositionDataKind(FALSE, NULL, NULL) & (OPR_CURSOR_ONETOUCH | OPR_CURSOR_SPEED | OPR_CURSOR_GROUP)) {
			ret = FALSE;
		}
		break;
	default:
		break;
	}

	return(ret);
}
#endif	/* (PRO_NEW_DIAL_OPR == ENABLE) */

/*************************************************************************
	module		:[直接ダイヤル入力桁数・件数検査]
	function	:[
		1.同報キーが押された時は、入力済みの直接ダイヤルが２０件未満かを調べます
		2.直接ダイヤルが押された時は、入力済みの桁数が４０桁未満かを調べます
	]
	return		:[
		TRUE	:押されたキーが入力可能
		FALSE	:入力桁数オーバー or 入力件数オーバー
	]
	common		:[]
	condition	:[
		・この関数は、必ずCheckInputDialData()の後に呼ぶ事
		・この関数の引数を変更する時は、CheckDirectDialLength()の引数も変更する事
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/17]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
UBYTE CheckInputDirectDial(UBYTE key_type)
{
	UWORD	data_top_pos;	/* カーソル位置のデータの先頭位置		*/
	UWORD	pin_mark_pos;	/* ＰＩＮ記号の位置						*/
	UWORD	data_num;		/* ダミー引数（ここでは未使用）			*/
	UBYTE	data_len;		/* ダイヤル記号データ桁数				*/
	UBYTE	dial_len;		/* 直接ダイヤル桁数						*/
	UBYTE	pin_len;		/* ＰＩＮ番号桁数						*/
	UBYTE	direct_pin_len;	/* 直接ダイヤル＋PIN記号＋PIN番号の桁数	*/
	UBYTE	cursor_data;	/* カーソル位置のデータ					*/
	UBYTE	ret;			/* リターン値							*/

	ret = TRUE;

	switch (key_type) {
	case BROADCAST:		/* 同報キー					*/
		/* 同報キーが押された時にチェックするのは、直接ダイヤルの途中に入力された時だけにします
		** （バッファの最後でチェックを行うと、同報記号が入力できなくなる不具合修正の為、条件を追加）
		*/
		if (InputNumber.CursorPosition != InputNumber.WritePosition) {	/* by K.Watanabe 1999/01/28 */
			if ((ret = CheckDirectDialCount()) == FALSE) {	/* 既に直接ダイヤルが、最大件数入力されている時 */
				OPR_ChildErrorFlag = TOO_MANY_DIRECT_DIAL_ERROR;	/* "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 20ｶｼｮ ｲﾅｲ" */
			}
		}
		break;
	case NUMBER:		/* ０～９キー				*/
	case AST:			/* テンキー ＊				*/
	case SHARP:			/* テンキー ＃				*/
	case DIALMARK:		/* ダイアル記号キー			*/
	case REDIAL:		/* リダイアル/ポーズキー	*/
 #if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */ 
	case TONE:			/* トーンキー 				*/
 #endif
 #if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH:			/* フラッシュキー			*/
 #endif
 #if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case MERCURY:		/* マーキュリーキー			*/
 #endif
 #if defined(DEU)
	case GROUND:
 #endif
 #if (PRO_MULTI_LINE == ENABLE)
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)
	case COPY_RESET:	/* コピーリセットキー		*/
  #else
	case HOLD:			/* 保留キー					*/
  #endif
 #endif

		/* 同報キーの直後の入力の時、直接ダイヤルの入力件数をチェックします by K.Watanabe 1999/01/28 */
		if ((InputNumber.CursorPosition != 0)
		 && (InputNumber.CursorPosition == InputNumber.WritePosition)
		 && ((InputNumber.Buffer[InputNumber.CursorPosition - 1]) == ',')) {
			if ((ret = CheckDirectDialCount()) == FALSE) {	/* 既に直接ダイヤルが、最大件数入力されている時 */
				OPR_ChildErrorFlag = TOO_MANY_DIRECT_DIAL_ERROR;	/* "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 20ｶｼｮ ｲﾅｲ" */
				break;
			}
		}

		/* データ桁数の取得 */
		switch (key_type) {
		case REDIAL:		/* リダイアル/ポーズキー	*/
 #if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE:			/* トーンキー 				*/
 #endif
 #if defined(DEU)
		case GROUND:
 #endif
			data_len = 2;	/* データの桁数は２桁です */
			break;
		default:
			data_len = 1;	/* データの桁数は１桁です */
			break;
		}

		/* カーソル位置が直接ダイヤルの時 */
		if (GetCursorPositionDataKind(TRUE, &data_top_pos, &data_num)
			& (OPR_CURSOR_DIRECT_DIAL | OPR_CURSOR_INVALID_DATA)) {

			/* ダイアル記号上で、ダイヤル記号キーを押されても入力桁数は変わらないので、チェックを省きます by K.Watanabe 1998/12/03 */
			cursor_data = InputNumber.Buffer[InputNumber.CursorPosition];
			if ((key_type == DIALMARK) && ((cursor_data == '-') || (cursor_data == '/') || (cursor_data == '!'))) {
				break;
			}

#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
				/* 直接ダイヤルの桁数を取得します
				** （ＰＩＮ番号が未登録のまま同報が指定されている事は無いので、直接ダイヤルの長さは
				** 　必ずＰＩＮ記号又は、ＮＵＬＬまでです）
				*/
				dial_len = (UBYTE)GetStringGapPoint(&InputNumber.Buffer[data_top_pos], OPR_PIN_MARK);
				/* 直接ダイヤル＋ＰＩＮ記号＋ＰＩＮ番号の桁数を取得します */
				direct_pin_len = (UBYTE)GetStringGapPoint(&InputNumber.Buffer[data_top_pos], ',');

				if (dial_len < direct_pin_len) {	/* ＰＩＮ記号が入力（ＰＩＮ番号が登録）されている時 */
					/* ＰＩＮ記号の位置を計算します（カーソル位置は０から始まっているので、＋１は不要です） */
					pin_mark_pos = data_top_pos + dial_len;
					/* ＰＩＮ番号の桁数を計算します */
					pin_len = direct_pin_len - (dial_len + 1);
				}
				else {								/* ＰＩＮ記号が未入力（ＰＩＮ番号が未登録）の時 */
					/* 下の条件文で、ダイヤル番号のロジックに入るようにします */
					pin_mark_pos = data_top_pos + direct_pin_len;
					/* ＰＩＮ番号の桁数を初期化します */
					pin_len = 0;
				}

				if (pin_mark_pos >= InputNumber.CursorPosition) {	/* ダイヤル番号を入力する時 */
					if (key_type == AST) {	/* ＰＩＮ記号が入力された時 */
						/* ＰＩＮ記号の入力位置が、ＰＩＮ番号が１桁を超える位置の時 */
						if ((direct_pin_len - (InputNumber.CursorPosition - data_top_pos)) > (1)) {
							OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
							ret = FALSE;
						}
					}
					else {					/* ＊キー以外の時 */
						/* 直接ダイヤル桁数オーバーチェック */
						ret = CheckDirectDialLength(dial_len, data_len);
					}
				}
				else {												/* ＰＩＮ番号を入力する時 */
					if ((pin_len + data_len) > (1)) {				/* データ入力後、ＰＩＮ番号が１桁を超える時 */
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
						ret = FALSE;
					}
				}
#else
			if (InputNumber.PIN_NumberCheck == NO) {	/* ＰＩＮ番号が不必要な時 */
				/* 直接ダイヤルの桁数を取得します */
				dial_len = (UBYTE)GetStringGapPoint(&InputNumber.Buffer[data_top_pos], ',');
				/* 直接ダイヤル桁数オーバーチェック */
				ret = CheckDirectDialLength(dial_len, data_len);
			}
			else {										/* ＰＩＮ番号が必要な時 */
				/* 直接ダイヤルの桁数を取得します
				** （ＰＩＮ番号が未登録のまま同報が指定されている事は無いので、直接ダイヤルの長さは
				** 　必ずＰＩＮ記号又は、ＮＵＬＬまでです）
				*/
				dial_len = (UBYTE)GetStringGapPoint(&InputNumber.Buffer[data_top_pos], OPR_PIN_MARK);
				/* 直接ダイヤル＋ＰＩＮ記号＋ＰＩＮ番号の桁数を取得します */
				direct_pin_len = (UBYTE)GetStringGapPoint(&InputNumber.Buffer[data_top_pos], ',');

				if (dial_len < direct_pin_len) {	/* ＰＩＮ記号が入力（ＰＩＮ番号が登録）されている時 */
					/* ＰＩＮ記号の位置を計算します（カーソル位置は０から始まっているので、＋１は不要です） */
					pin_mark_pos = data_top_pos + dial_len;
					/* ＰＩＮ番号の桁数を計算します */
					pin_len = direct_pin_len - (dial_len + 1);
				}
				else {								/* ＰＩＮ記号が未入力（ＰＩＮ番号が未登録）の時 */
					/* 下の条件文で、ダイヤル番号のロジックに入るようにします */
					pin_mark_pos = data_top_pos + direct_pin_len;
					/* ＰＩＮ番号の桁数を初期化します */
					pin_len = 0;
				}

				if (pin_mark_pos >= InputNumber.CursorPosition) {	/* ダイヤル番号を入力する時 */
					if (key_type == AST) {	/* ＰＩＮ記号が入力された時 */
						/* ＰＩＮ記号の入力位置が、ＰＩＮ番号が８桁を超える位置の時 */
						if ((direct_pin_len - (InputNumber.CursorPosition - data_top_pos)) > (SYS_PIN_MAX * 2)) {
							OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
							ret = FALSE;
						}
					}
					else {					/* ＊キー以外の時 */
						/* 直接ダイヤル桁数オーバーチェック */
						ret = CheckDirectDialLength(dial_len, data_len);
					}
				}
				else {												/* ＰＩＮ番号を入力する時 */
					if ((pin_len + data_len) > (SYS_PIN_MAX * 2)) {	/* データ入力後、ＰＩＮ番号が８桁を超える時 */
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
						ret = FALSE;
					}
				}
			}
#endif
		}
		break;
	default:
		break;
	}

	return(ret);
}
#endif	/* (PRO_NEW_DIAL_OPR2 == ENABLE) */

/*************************************************************************
	module		:[同報入力をチェック]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void BroadcastCheck(void)
{
	UWORD	i;

	/* コンマを探す */
	for (i = 0; i < InputNumber.WritePosition; i++) {
		if (InputNumber.Buffer[i] == ',') {
			if (InputNumber.MultiNumberStatus == 0) {
				InputNumber.MultiNumberStatus = 1;
			}
		}
	}
}

/*************************************************************************
	module		:[コマンド入力バッファに入力されたテンキーをセット]
	function	:[
		1.バッファに数字、＃を入力する。
		2.カーソル位置の前の入力がワンタッチキーの場合、区切りのコンマを入力する。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口,渡辺一章]
*************************************************************************/
void InputNumberTenKeySet(UBYTE key)
{
	UBYTE	set_data[4];
	UBYTE	length;

	CMN_MemorySet(set_data, 4, NULL);
	length = 0;

	/* バッファにセットするデータの作成 */
	if (CheckPreDataOnetouch() == TRUE) {	/* カーソル前のデータがワンタッチの時 */
		set_data[length++] = ',';	/* ワンタッチの次に入力する場合、間にコンマを挿入 */
	}

	set_data[length++] = key;

	/* ダイヤル記号入力後の数字入力の時は、ダイヤル記号後に数字をセットします */
	if (DialCharacterCheck(&InputNumber.Buffer[InputNumber.CursorPosition],
						   InputNumber.CursorPosition,
						   InputNumber.WritePosition) == TRUE) {
		InputNumber.CursorPosition++;
	}

#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
	/* ダイヤル記号（ポーズ・トーン）入力後の数字入力の時は、ダイヤル記号（ポーズ・トーン）後に数字をセットします */
	if (DialCharacterCheck2(&InputNumber.Buffer[InputNumber.CursorPosition],
						   InputNumber.CursorPosition,
						   InputNumber.WritePosition) == TRUE) {
		InputNumber.CursorPosition += 2;
	}
#endif

	/* 作成したデータをバッファに格納 */
	InsertInputData(&set_data[0], length);
	BroadcastCheck();

#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/04/22 */
	/* 元々は'*'→PIN記号への変換を、セット・スタートキーが押された時に初めて行っていたが、仕様変更で
	** 入力中でも桁数オーバーチェックを行うようになった為に、入力されたらすぐに変換するようにします
	** 理由）元のままだと、PINの区切りの判断に使用するのが、入力中は最初の'*'で、セット・スタートキー
	** 　　　押下後はPIN記号（ただし、PIN記号の前に'*'を入力したら'*'）になり、状況によりバラバラなので、
	** 　　　判断が１つで済むよう（PIN記号のみ）にします
	*/
	ChangeAsteriskKeyCode(key);
#endif
}

/*************************************************************************
	module		:[ワンタッチをセット]
	function	:[
		1.コマンド入力バッファにワンタッチ記号をセットする
		2.バッファの途中に入力する場合は、ワンタッチ記号が区切りのコンマで囲まれるようにする。
		3.入力時の仕様
		,	 セット前		  セット後
		,	 _			 ->	  A_
		,
		,	 123456_	 ->	  123456,A_
		,
		,	 123456		 ->	  123,A,456
		,		~					~
		,	 123456		 ->	  A,123456
		,	 ~					~
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口,渡辺一章]
*************************************************************************/
void InputNumberOnetouchSet(UBYTE key)
{
	UBYTE	set_data[7];
	UBYTE	length;

	CMN_MemorySet(set_data, 7, NULL);
	length = 0;

	/** ワンタッチ記号をバッファにセット */
	if ((InputNumber.CursorPosition != 0) && (InputNumber.Buffer[InputNumber.CursorPosition - 1] != ',')) {
	/* カーソルが先頭でなくかつ前の入力がコンマでない */
		set_data[length++] = ',';	/* ワンタッチ記号の前にコンマを入力 */
	}

	length += SetOnetouchCode(&set_data[length], key, OPR_SET_ONETOUCH_CODE);

	if ((InputNumber.Buffer[InputNumber.CursorPosition] != ',')
	 && (InputNumber.CursorPosition != InputNumber.WritePosition)) {	/* カーソル位置がコンマである */
		set_data[length++] = ',';	/* ワンタッチ記号の後ろにコンマを入力する */
	}
	InsertInputData(&set_data[0], length);
	BroadcastCheck();
}

/*************************************************************************
	module		:[短縮記号/グループ記号をセット]
	function	:[
		1.コマンド入力バッファに短縮記号またはグループ記号をセットする。
		2,バッファの途中にセットする場合,記号をコンマで囲みます
		3.短縮記号／グループ記号の次には数字以外絶対はいらないようにする
		4.入力仕様
		,	入力前			入力後
		,	_		 ->		S_
		,
		,	123_	 ->		123,S_
		.
		.	12345	 ->		123,S,45
		,	   ~				 ~
		,	12345	 ->		S,12345
		,	~				 ~
		,	123,A	 ->		12,S,3,A
		,	  ~					~
		,	123,A	 ->		123,S,A
		,	   ~				 ~
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void InputNumberGroupSpeedMarkSet(UBYTE key)
{
	UBYTE	set_data[4];
	UBYTE	length;

	CMN_MemorySet(set_data, 4, NULL);
	length = 0;

	/* バッファにセットするデータを作成 */
	if ((InputNumber.CursorPosition != 0)
	&&	(InputNumber.Buffer[InputNumber.CursorPosition - 1] != ',')) { /* 先頭じゃなく、前の入力がコンマじゃない */
		set_data[length++] = ',';
	}
	if (key == SPEED_KEY) {	/* 短縮キーが押された時 */
		set_data[length++] = OPR_SPEED_MARK;	/* OPR_SPEED_MARK(0x05) != ONETOUCH_S_KEY(0x53) */
	}
	else {					/* グループキーが押された時 */
		set_data[length++] = OPR_GROUP_MARK;	/* OPR_GROUP_MARK(0x06) != ONETOUCH_G_KEY(0x47) */
	}

	if ((InputNumber.Buffer[InputNumber.CursorPosition] != ',')
	&&	(InputNumber.CursorPosition != InputNumber.WritePosition)) {/* 最後じゃなく、カーソル上に入力がコンマじゃない */
		set_data[length++] = ',';
	}

	/* 作成したデータをバッファに格納します */
	InsertInputData(&set_data[0], length);
	if (InputNumber.Buffer[InputNumber.CursorPosition - 1] == ',') {
		/* 短縮記号の次からでーたを入力させるために短縮記号のすぐ後にカーソルを持っていく */
		InputNumber.CursorPosition--;
	}

	if (key == SPEED_KEY) {	/* 短縮キーが押された時 */
		OPR_InputDialInfo |= SPEED_MARK_INPUT;	/* 短縮番号入力中をセット */
	}
	else {					/* グループキーが押された時 */
		OPR_InputDialInfo |= GROUP_MARK_INPUT;	/* グループ番号入力中をセット */
	}

	BroadcastCheck();
}

/*************************************************************************
	module		:[プログラムワンタッチをセット]
	function	:[
		1.コマンド入力バッファにプログラムワンタッチをセットする
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/12]
	author		:[渡辺一章]
*************************************************************************/
void InputNumberProgramSet(UBYTE key)
{
	UBYTE	set_data[5];
	UBYTE	length;

	CMN_MemorySet(set_data, 5, NULL);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	set_data[0] = OPR_PROGRAM_MARK_LEFT;	/* '[' */
	CMN_UnsignedIntToASC(&set_data[1], (UBYTE)(key - ONETOUCH_73_KEY + OPR_PRG_NUMBER_MIN), 2, '0');
	set_data[3] = OPR_PROGRAM_MARK_RIGHT;	/* ']' */
	length = 4;
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)  /* By H.Fujimura 1999/01/06 */
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
	set_data[0] = OPR_PROGRAM_MARK;
	CMN_UnsignedIntToASC(&set_data[1], (UBYTE)(key - ONETOUCH_25_KEY + OPR_PRG_NUMBER_MIN), 1, '0');
	length = 2;
 #else
	set_data[0] = OPR_PROGRAM_MARK_LEFT;	/* '[' */
	CMN_UnsignedIntToASC(&set_data[1], (UBYTE)(key - ONETOUCH_25_KEY + OPR_PRG_NUMBER_MIN), 2, '0');
	set_data[3] = OPR_PROGRAM_MARK_RIGHT;	/* ']' */
	length = 4;
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	set_data[0] = OPR_PROGRAM_MARK;
	CMN_UnsignedIntToASC(&set_data[1], (UBYTE)(key - PROGRAM_P01 + OPR_PRG_NUMBER_MIN), 2, '0');
	length = 3;
#endif
	InsertInputData(&set_data[0], length);

	OPR_InputDialInfo |= PROGRAM_INPUT;	/* プログラムワンタッチ入力中をセット */
}

/*************************************************************************
	module		:[同報キーの処理]
	function	:[
		1.コマンド入力バッファに同報の時の区切りのコンマをセットする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void BroadcastMarkSet(void)
{
	UBYTE	set_data[2];
	UBYTE	length;

	CMN_MemorySet(set_data, 2, NULL);
	length = 0;

	if (CheckInputCommandDialNumber() == FALSE) { /* バッファがからの場合 */
		InputNumber.MultiNumberStatus = 1;
	}
	else {
		if ((InputNumber.CursorPosition != 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] != ',')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] != ',')) {
			set_data[length++] = ',';
			/*先ほど作成したデータをバッファに格納します */
			InsertInputData(&set_data[0], length);
			BroadcastCheck();
		}
		else {
			NackBuzzer();
		}
	}
}

/*************************************************************************
	module		:[ダイアルマークをセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口,渡辺一章]
*************************************************************************/
void InputNumberDialMarkSet(UBYTE mark)
{
	UBYTE	set_data[5];
	UBYTE	length;

	CMN_MemorySet(set_data, 4, NULL);
	length = 0;

#if (PRO_NEW_DIAL_OPR == DISABLE)	/* by K.Watanabe 1998/03/25 */
	/* 新しいオペレーションでは、ワンタッチの直後のダイヤルマークは禁止するので、この処理は必要ありません */
	if (CheckPreDataOnetouch() == TRUE) {	/* 直前の入力がワンタッチの時 */
		set_data[length++] = ',';
	}
#endif

	switch (mark) {
	case PAUSE_MARK:
		set_data[length++] =  '-';
		set_data[length++] =  '/';
		break;
	case TONE_MARK:
		set_data[length++] =  '-';
		set_data[length++] =  '!';
		break;
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH_MARK:
		set_data[length++] =  '/';
		break;
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* 1996/06/28 H,Yagi *//* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case MERCURY_MARK:
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/19 *//* by K.Watanabe 2004/10/12 */
		if(InputNumber.CursorPosition == 0) {
			set_data[length++] =  '!';
		}
		else {
			if((InputNumber.CursorPosition != 0) && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == ',')) {
				set_data[length++] =  '!';
			}
			else {
				NackBuzzer();
			}
		}
#else
		set_data[length++] =  '!';
#endif
		break;
#endif
#if (PRO_MULTI_LINE == ENABLE)
	case MULTI_TEL_MARK:
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		/* ２回線以上ない時は、セットできない */
		if (OPT_CountModems() <= 1) {
			NackBuzzer();
			return;
		}
 #endif
		if (InputPbxCheck(OPR_INPUT_NUMBER) == FALSE) {	/* 内線記号の登録は１つのみとする */
			NackBuzzer();
			return;
		}
		set_data[length++] =  '!';
		break;
#endif
	default:
		break;
	}

	/* 先ほど作成したデータをバッファに格納します */
	InsertInputData(&set_data[0], length);
	BroadcastCheck();
}

/*************************************************************************
	module		:[カーソル移動（右方向）]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口,渡辺一章]
*************************************************************************/
void InputNumberCursorRight(void)
{
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/* HEXコード入力中は無効*/
	if (CheckHexCodeInput() == TRUE) {
		NackBuzzer();
		return;
	}
#endif
	if (InputNumber.CursorPosition >= InputNumber.WritePosition) {	/* 右端（入力後端位置) */
		NackBuzzer();	/* これ以上右にいけない */
	}
	else {
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		if (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_ONETOUCH_MARK_LEFT) {
			/* "[01] "のような時、カーソルを右移動させると"[01] "となる */
			/*  ~                                              ~        */
			InputNumber.CursorPosition += 3;
		}
#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
		/* ワンタッチＵ１～Ｕ８追加につき処理追加 1995/12/06 Eguchi */
		if (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_ONETOUCH_MARK) {
			/* "U1 "のような時、カーソルを右移動させると"U1 "となる */
			/*  ~                                          ~        */
			InputNumber.CursorPosition++;
		}
#endif
#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '/')) {		/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを右移動させると"-/ "となる */
			/*  ~                                          ~        */
			InputNumber.CursorPosition++;
		}
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '!')) {		/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを右移動させると"-! "となる */
			/*  ~                                          ~        */
			InputNumber.CursorPosition++;
		}
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/04/27 */
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == OPR_SPEED_MARK)
			  || (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_GROUP_MARK)) {
			/* "S001 "のような時、カーソルを右移動させると"S001 "となる */
			/*  ~                                              ~        */
			InputNumber.CursorPosition += GetStringGapPoint(&InputNumber.Buffer[InputNumber.CursorPosition + 1], ',');
		}
#endif

		InputNumber.CursorPosition++;

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
		if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
			if (OPR_MailCommand.HistoryReadPosition != 0xFF) {
				OPR_MailCommand.HistoryReadPosition = 0xFF;	/** ヒストリモード終了 */
			}
		}
#endif
	}
}

/*************************************************************************
	module		:[カーソル移動（左方向）]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口,渡辺一章]
*************************************************************************/
void InputNumberCursorLeft(void)
{
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/04/27 */
	UWORD	data_top_pos;	/* カーソル位置のデータの先頭位置	*/
	UWORD	data_number;	/* ダミー引数（ここでは未使用）		*/
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/* HEXコード入力中はＮＧ*/
	if (CheckHexCodeInput() == TRUE) {
		NackBuzzer();
		return;
	}
#endif
	if (InputNumber.CursorPosition == 0) {	/** バッファの先頭にカーソルがおる場合 */
		NackBuzzer();	/* これ以上左にいけへん */
	}
	else {
		InputNumber.CursorPosition--;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		if (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_ONETOUCH_MARK_RIGHT) {
			/* "[01] "のような時、カーソルを左移動させると"[01] "となる */
			/*      ~                                      ~            */
			InputNumber.CursorPosition -= 3;
		}
#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
		/* ワンタッチＵ１～Ｕ８追加につき処理追加 1995/12/06 Eguchi */
		if ((InputNumber.CursorPosition > 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == OPR_ONETOUCH_MARK)) {
			/* "U1 "のような時、カーソルを左移動させると"U1 "となる */
			/*    ~                                      ~          */
			InputNumber.CursorPosition--;
		}
#endif
#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
		if ((InputNumber.CursorPosition > 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを左移動させると"-/ "となる */
			/*    ~                                      ~          */
			InputNumber.CursorPosition--;
		}
		if ((InputNumber.CursorPosition > 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] == '!')) {		/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを左移動させると"-! "となる */
			/*    ~                                      ~          */
			InputNumber.CursorPosition--;
		}
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
		if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
			if (OPR_MailCommand.HistoryReadPosition != 0xFF) {
				OPR_MailCommand.HistoryReadPosition = 0xFF;
			}
		}
#endif

#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/04/27 */
		if ((InputNumber.Buffer[InputNumber.CursorPosition] != ',')
		 && (GetCursorPositionDataKind(TRUE, &data_top_pos, &data_number) & (OPR_CURSOR_SPEED | OPR_CURSOR_GROUP))) {
			/* "S001 "のような時、カーソルを左移動させると"S001 "となる */
			/*      ~                                      ~            */
			InputNumber.CursorPosition = data_top_pos;
		}
#endif
	}
}

/*************************************************************************
	module		:[クリアキーに対する処理]
	function	:[
		1.コマンド入力バッファのデータを１文字分クリアする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void InputNumberDataClear(void)
{
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/* HEXコード入力中*/
	if (CheckHexCodeInput() == TRUE) {
		OPR_MailCommand.HexCodeInputPosition--;
		OPR_MailCommand.HexCodeInputBuffer[OPR_MailCommand.HexCodeInputPosition] = NULL;
		return;
	}
#endif

	if (CheckInputCommandDialNumber() == FALSE) {/* 未入力 */
		NackBuzzer();
	}
	else {
		/* カーソルが新規入力位置にある場合はカーソル前を１文字消去 */
		/* 短縮、グループは１括して消去 */
		if (InputNumber.CursorPosition == InputNumber.WritePosition) { /* 最後尾 */
			InputNumberClearBackSpace();
		}
		else { /* 途中 */
			InputNumberClearDelete();
		}
	}
}

/*************************************************************************
	module		:[ダイアル記号セット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/02]
	author		:[江口]
*************************************************************************/
void InputNumberDialCharacterSet(void)
{
	UBYTE	data;
	UBYTE	flag;

	flag = 0;

	if (InputNumber.CursorPosition < InputNumber.WritePosition) {	/* バッファの途中 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
 #if (PRO_SPECIAL_PAUSE_INPUT == ENABLE)	/* ポーズ追加特ＲＯＭ【RDC-1436】By J.Kishida 1999/04/14 */
		if (ROM_SW_SpecialPauseInput == 1) {
			if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] != '!')
			 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] != '/')) {		/* ダイアル記号 */
				InputNumber.Buffer[InputNumber.CursorPosition] = '/';
			}
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイアル記号 */
				InputNumber.Buffer[InputNumber.CursorPosition] = '!';
			}
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '!')) {		/* ダイアル記号 */
				InputNumberDataShift(SHIFT_BACKWORD);
				InputNumber.WritePosition++;
				InputNumber.Buffer[InputNumber.CursorPosition] = '-';

				/* ファネット指摘事項(No.104)
				** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
				** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
				** by O.Kimoto 2002/10/29
				*/
				if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
					InputNumber.DisplayStartPosition ++;
				}

			}
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
				  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				InputNumber.Buffer[InputNumber.CursorPosition + 1] = '/';
			}
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
				  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '/')) {	/* ダイアル記号(ポーズ)*/
				InputNumberDataShift(SHIFT_FORWORD);
				InputNumber.WritePosition--;
				InputNumber.Buffer[InputNumber.CursorPosition] = '-';

				/* ファネット指摘事項(No.104)
				** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
				** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
				** by O.Kimoto 2002/10/29
				*/
				if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
					InputNumber.DisplayStartPosition ++;
				}

			}
			else {
				flag = 1;
			}
		}
		else {
			if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] != '!')) {		/* ダイアル記号 */
				InputNumber.Buffer[InputNumber.CursorPosition] = '/';
			}
   #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/20 for prefix *//* by K.Watanabe 2004/12/16 */
			else if((InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイアル記号 */
				if((InputNumber.CursorPosition == 0) || (InputNumber.Buffer[(InputNumber.CursorPosition - 1)] == ',')){
					InputNumber.Buffer[InputNumber.CursorPosition] = '!';
					InputNumberDataShift(SHIFT_BACKWORD);
					InputNumber.WritePosition++;
					InputNumber.Buffer[InputNumber.CursorPosition] = '-';

					if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 2)) {
						InputNumber.DisplayStartPosition ++;
					}
				}
				else {
					InputNumber.Buffer[InputNumber.CursorPosition] = '!';
				}
			}
   #else
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイアル記号 */
				InputNumber.Buffer[InputNumber.CursorPosition] = '!';
			}
   #endif
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '!')) {		/* ダイアル記号 */
				InputNumberDataShift(SHIFT_BACKWORD);
				InputNumber.WritePosition++;
				InputNumber.Buffer[InputNumber.CursorPosition] = '-';

				/* ファネット指摘事項(No.104)
				** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
				** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
				** by O.Kimoto 2002/10/29
				*/
				if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
					InputNumber.DisplayStartPosition ++;
				}

			}
			else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
				  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				InputNumberDataShift(SHIFT_FORWORD);
				InputNumber.WritePosition--;
				InputNumber.Buffer[InputNumber.CursorPosition] = '-';

				/* ファネット指摘事項(No.104)
				** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
				** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
				** by O.Kimoto 2002/10/29
				*/
				if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
					InputNumber.DisplayStartPosition ++;
				}

			}
			else {
				flag = 1;
			}
		}
 #else
		if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] != '!')) {		/* ダイアル記号 */
			InputNumber.Buffer[InputNumber.CursorPosition] = '/';
		}
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイアル記号 */
			InputNumber.Buffer[InputNumber.CursorPosition] = '!';
		}
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '!')) {		/* ダイアル記号 */
			InputNumberDataShift(SHIFT_BACKWORD);
			InputNumber.WritePosition++;
			InputNumber.Buffer[InputNumber.CursorPosition] = '-';

			/* ファネット指摘事項(No.104)
			** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
			** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
			** by O.Kimoto 2002/10/29
			*/
			if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
				InputNumber.DisplayStartPosition ++;
			}

		}
		else if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			  && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
			InputNumberDataShift(SHIFT_FORWORD);
			InputNumber.WritePosition--;
			InputNumber.Buffer[InputNumber.CursorPosition] = '-';

			/* ファネット指摘事項(No.104)
			** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
			** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
			** by O.Kimoto 2002/10/29
			*/
			if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
				InputNumber.DisplayStartPosition ++;
			}

		}
		else {
			flag = 1;
		}
 #endif
#else
		switch (InputNumber.Buffer[InputNumber.CursorPosition]) {	/* カーソル上の入力データにより分岐 */
		case '-':	/* ダイアル記号 */
			InputNumber.Buffer[InputNumber.CursorPosition] = '/';
			break;
		case '/':	/* ダイアル記号 */
			InputNumber.Buffer[InputNumber.CursorPosition] = '!';
			break;
		case '!':	/* ダイアル記号 */
			InputNumber.Buffer[InputNumber.CursorPosition] = '-';
			break;
		default:
			flag = 1;
			break;
		}
#endif
	}

	if ((InputNumber.CursorPosition == InputNumber.WritePosition) /* 入力後端位置*/
	||	(flag == 1)) {
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
 #if (PRO_SPECIAL_PAUSE_INPUT == ENABLE)	/* ポーズ追加特ＲＯＭ【RDC-1436】By J.Kishida 1999/04/14 */
		if (ROM_SW_SpecialPauseInput == 1) {
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			InputNumberTenKeySet('-');
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				InputNumberTenKeySet('!');
			}
			else {
				InputNumberTenKeySet('/');
			}
			InputNumber.CursorPosition -= 2;
		}
		else {
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				InputNumberTenKeySet('-');
				InputNumberTenKeySet('!');
				InputNumber.CursorPosition -= 2;
				
				/* ファネット指摘事項(No.104)
				** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
				** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
				** by O.Kimoto 2002/10/29
				*/
				if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
					InputNumber.DisplayStartPosition ++;
				}
				
			}
			else {
				InputNumberTenKeySet('-');
				InputNumber.CursorPosition--;
			}
		}
 #else
		/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
		if (CHK_UNI_CSDR_DialMarkExchange()) {
			InputNumberTenKeySet('-');
			InputNumberTenKeySet('!');
			InputNumber.CursorPosition -= 2;

			/* ファネット指摘事項(No.104)
			** LCDの右端にてトーンを入力(実際はダイヤル記号で）をした場合、"-"のみが表示され"!"が出てこない。。。。
			** よって、ここでカーソルが右端でトーン／ポーズの場合は表示開始ポジションを１つずらす
			** by O.Kimoto 2002/10/29
			*/
			if ((InputNumber.CursorPosition - InputNumber.DisplayStartPosition) == (OPR_DISPLAY_MAX - 1)) {
				InputNumber.DisplayStartPosition ++;
			}

		}
		else {
			InputNumberTenKeySet('-');
			InputNumber.CursorPosition--;
		}
 #endif
#else
		InputNumberTenKeySet('-');

		/* 以下、カーソル位置をダイアル記号の所に持ってくるための処理 */
		/* 普通にデータをセットすると、セットしたデータの分だけカーソル位置は右方向に動く */
		/* カーソル位置の１つ手前からバッファを検索して、最初のダイアル記号の位置までカーソル*/
		/* を移動させる */
		InputNumber.CursorPosition--;
		for ( ; InputNumber.CursorPosition > 0; InputNumber.CursorPosition--) {
			data = InputNumber.Buffer[InputNumber.CursorPosition];
			if ((data == '-') || (data == '!') || (data == '/')) {
				break;
			}
		}
#endif
	}
	BroadcastCheck();
}

/*************************************************************************
	module		:[バッファに入力されているデータを１文字分シフトする]
	function	:[
		1.モードがSHIFT_BACKWORDの場合：カーソル位置（入力位置）以降ののデータを後ろに１個ずらす
		2.モードがSHIFT_FORWORDの場合：カーソル位置（入力位置）以降のデータを前に１個ずらす
		,
		, SHIFT_BACKWORD
		, 01234567890123456_
		,	  ~
		, 012344567890123456_
		,	  ~
		, SHIFT_FORWORD
		, 0123456789012345_
		,	  ~
		, 012356789012345_
		,	  ~
		,
	]
	return		:[なし]
	common		:[
		InputNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void InputNumberDataShift(UBYTE shift_mode)
{
	UWORD	i;

	if (shift_mode == SHIFT_BACKWORD) {	/* 後ろ向きにずらす */
		for (i = InputNumber.WritePosition; i > InputNumber.CursorPosition; i--) {
			InputNumber.Buffer[i] = InputNumber.Buffer[(UWORD)(i - 1)];
		}
	}
	else {								/* 前向きにずらす */
		for (i = InputNumber.CursorPosition; i < InputNumber.WritePosition; i++) {
			InputNumber.Buffer[i] = InputNumber.Buffer[i + 1];
		}
	}
}

/*************************************************************************
	module		:[バッファにデータを１文字分セットする]
	function	:[
		1.カーソル位置にデータをセットし、カーソル位置と書き込み終端位置を一つ進める
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[データ挿入位置をあけておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void InputNumberDataSet(UBYTE data)
{
	InputNumber.Buffer[InputNumber.CursorPosition] = data;
	InputNumber.CursorPosition++;
	InputNumber.WritePosition++;
}

/*************************************************************************
	module		:[バッファにデータ列をセットする]
	function	:[
		1.バッファに与えられたデータ列をセットする。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void InsertInputData(UBYTE *set_data,	/* セットするデータ列 */
					 UBYTE length)		/* セットするデータ長 */
{
	/* バッファにすべて入るか調べる */
	/* InputNumber.WritePosition:入力されたデータの桁数 */
	if (InputNumber.WritePosition + (UWORD)length > OPR_INPUT_NUMBER_BUFFER_MAX) {	/* 入力済み桁数＋入力データ桁がバッファサイズを越える */
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
		NackBuzzer();
	}
	else {																			/* オーバーフローしない */
		if (InputNumber.CursorPosition < InputNumber.WritePosition) {	/* 途中に挿入する場合 */
			while (*set_data != NULL) {
				InputNumberDataShift(SHIFT_BACKWORD);
				InputNumberDataSet(*set_data);
				set_data++;
			}
		}
		else {															/* バッファの最後に挿入する場合 */
			while (*set_data != NULL) {
				InputNumberDataSet(*set_data);
				set_data++;
			}
		}
	}
}

/*************************************************************************
	module		:[カーソル前のデータを消去]
	function	:[
		1.カーソル前を１文字消去。
		2.短縮、グループ、ワンタッチは１宛先分まとめて消去する。
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[
		カーソルが新規入力位置にある場合(CursorPosition == WritePosition)はカーソル前を１文字消去
		短縮、グループは１括して消去
		プログラムワンタッチもまとめて消去 -> こんなパスは本来ないはず
		ワンタッチもまとめて消去。ワンタッチＵ１～Ｕ２が追加されたため処理追加 1995/12/06 Eguchi

		消去前			消去後
		S001_		->	_
		G01_		->	_
		U1_			->	_
		123_		->	12_
		123,_		->	123_
		123,4_		->	123,_
		1234,S001_	->	1234_
		1234,A_		->	1234_
		1234,G01_	->	1234_
		1234,S001,_	->	1234,S001_
		1234,A,_	->	1234,A_
		1234,G01,_	->	1234,G01_
		1234,P01_	->	1234_		-->	 ない
		1234,P01,_	->	1234,P01_	-->	 ない
		1234,U1_	->	1234_
		1234,U1,_	->	1234,U1_
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void InputNumberClearBackSpace(void)
{
	UWORD	i;
	UBYTE	block_clear;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	UBYTE	is_direct_adr;

	is_direct_adr = 0;
#endif
	block_clear = 0;

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/********************************************
	** カーソル位置の文字がダイレクトアドレス
	** の一部かどうかをチェック
	********************************************/
	for (i = InputNumber.WritePosition; (InputNumber.Buffer[i] != ',') && (i > 0); i--) {
		if (InputNumber.Buffer[i] == DIRECT_ADDRESS_MARK) {
			is_direct_adr = 1;
		}
	}
	if ((i == 0) && (is_direct_adr == 0)) {
		if (InputNumber.Buffer[i] == DIRECT_ADDRESS_MARK) {
			is_direct_adr = 1;
		}
	}

	if (!is_direct_adr) {
		for (i = InputNumber.WritePosition; (InputNumber.Buffer[i] != ',') && (i > 0); i--) {
			if (CheckInputNumberCode(InputNumber.Buffer[i]) == TRUE) {
				block_clear = 1;
			}
		}
		if ((i == 0) && (block_clear == 0)) {
			if (CheckInputNumberCode(InputNumber.Buffer[i]) == TRUE) {
				block_clear = 1;
			}
			/* 先頭にはコンマは入力できないので、コンマかどうかのチェックは不要 */
		}
	}
#else
	for (i = InputNumber.WritePosition; (InputNumber.Buffer[i] != ',') && (i > 0); i--) {
		if (CheckInputNumberCode(InputNumber.Buffer[i]) == TRUE) {
			block_clear = 1;
		}
	}
	if ((i == 0) && (block_clear == 0)) {
		if (CheckInputNumberCode(InputNumber.Buffer[i]) == TRUE) {
			block_clear = 1;
		}
		/* 先頭にはコンマは入力できないので、コンマかどうかのチェックは不要 */
	}
#endif

	if (block_clear == 1) {	/* SPEED,GROUP,ONETOUCHはまとめて消す */
		CMN_MemorySet(&InputNumber.Buffer[i], InputNumber.CursorPosition - i, NULL);
		InputNumber.CursorPosition = i;
		InputNumber.WritePosition = InputNumber.CursorPosition;
	}
	else {					/* １文字だけ消去 */
#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
		if ((InputNumber.CursorPosition > 1)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 2] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '/')) {		/* ダイヤル記号（ポーズ） */
			InputNumber.CursorPosition--;
			InputNumber.WritePosition--;
			InputNumber.Buffer[InputNumber.CursorPosition] = NULL;
		}
		if ((InputNumber.CursorPosition > 1)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 2] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '!')) {		/* ダイヤル記号（トーン） */
			InputNumber.CursorPosition--;
			InputNumber.WritePosition--;
			InputNumber.Buffer[InputNumber.CursorPosition] = NULL;
		}
#endif
		InputNumber.CursorPosition--;
		InputNumber.WritePosition--;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
		if (InputNumber.Buffer[InputNumber.CursorPosition] == DIRECT_ADDRESS_MARK) {
			if (OPR_MailCommand.HistoryReadPosition != 0xFF) {
				OPR_MailCommand.HistoryReadPosition = 0xFF;
			}
		}
#endif
		InputNumber.Buffer[InputNumber.CursorPosition] = NULL;
	}
}

/*************************************************************************
	module		:[カーソル上のデータを消去]
	function	:[
		1.カーソルが途中にある場合はカーソル上を１文字消去
		2, 短縮、グループは１括して消去
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[
		Cursor < Write

		消去前		   消去後
		1234		-> 124
		 ~				~
		S001		->
		~
		1234,G01	-> 1234
			 ~
		1234,A		-> 123,A
		  ~				   ~
		123,S002,A	-> 123,A
			~			   ~
		1234,2,234	-> 1234,234
			~				~
		1234,A,234	-> 1234,234
			~				~
		1234,U1,234	-> 1234,234
			~				~
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/10]
	author		:[江口]
*************************************************************************/
void InputNumberClearDelete(void)
{
	UWORD	tail;			/* カーソル位置より後方にある、最初のコンマの位置。又はNULLの位置 */
	UWORD	top;			/* カーソル位置より前方にある、最初のコンマの位置。又は先頭位置 */
	UBYTE	block_clear;	/* tailとtopの間にワンタッチ・短縮・グループがある場合、まとめて消すためにセット */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	UBYTE	is_direct_adr;
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
	UWORD	i;					/* ループ変数					*/
	UWORD	chk_start_pos;		/* 検索開始位置					*/
	UBYTE	is_pin_mark_clear;	/* 消去するデータがＰＩＮ記号か	*/
#endif

	top = 0;
	tail = 0;
	block_clear = 0;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	is_direct_adr = 0;
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
	is_pin_mark_clear = FALSE;
#endif

	/* カーソルが途中にある場合はカーソル上を１文字消去 */
	/* 短縮、グループ,ワンタッチは１括して消去 */

#if (PRO_NEW_DIAL_OPR == ENABLE)	/* by K.Watanabe 1998/03/27 */
	/* バッファの途中での短縮キー入力直後等でも、クリアキーを有効にします
	** 例）[01],123 → [01],S,123 → [01],123     123,[01] → 12,[01]
	** 		   ~			 ~			 ~           ~			~
	*/
	if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
		/* バッファの先頭に、同報記号があることは無いので、無条件にカーソル位置をずらしても問題はないはずです */
		InputNumber.CursorPosition--;
 #if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
		if ((InputNumber.CursorPosition > 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] == '/')) {		/* ダイヤル記号（ポーズ） */
			InputNumber.CursorPosition--;
		}
		if ((InputNumber.CursorPosition > 0)
		 && (InputNumber.Buffer[InputNumber.CursorPosition - 1] == '-')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] == '!')) {		/* ダイヤル記号（トーン） */
			InputNumber.CursorPosition--;
		}
 #endif
	}
#endif

	/* カーソル上にコンマがある場合、コンマは消去できない */
	if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
		NackBuzzer();
	}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/** ダイレクトアドレスマークを消去したら、そのアドレスを消去 */
	else if (InputNumber.Buffer[InputNumber.CursorPosition] == DIRECT_ADDRESS_MARK) {
		while (InputNumber.Buffer[InputNumber.CursorPosition] != NULL) {
			if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
				break;
			}
			InputNumberDataShift(SHIFT_FORWORD);
		}
		if ((InputNumber.CursorPosition == 0) && (InputNumber.Buffer[InputNumber.CursorPosition] == ',')) {
			InputNumberDataShift(SHIFT_FORWORD);
		}
		if ((InputNumber.CursorPosition != 0)
		&&	(InputNumber.Buffer[InputNumber.CursorPosition-1] == ',')
		&&	(InputNumber.Buffer[InputNumber.CursorPosition] == ',')) {
			InputNumberDataShift(SHIFT_FORWORD);
		}
		InputNumber.WritePosition = GetStringGapPoint(InputNumber.Buffer, NULL);
		if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
			InputNumber.CursorPosition++;
		}
	}
#endif
	else {
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
		/**********************************************
		** カーソル位置の文字がダイレクトアドレスの
		** 一部かどうか調べる
		**********************************************/
		for(top = InputNumber.CursorPosition; (InputNumber.Buffer[top] != ',') && (top > 0); top--) {
			if (InputNumber.Buffer[top] == DIRECT_ADDRESS_MARK) {
				is_direct_adr = 1;
			}
		}
		if ((top == 0) && (is_direct_adr == 0)) {
			if (InputNumber.Buffer[top] == DIRECT_ADDRESS_MARK) {
				is_direct_adr = 1;
			}
		}
		
		if (!is_direct_adr) {
			/* 後方位置を探す。その間に短縮/グループ/ワンタッチがあるか調べる */
			for (tail = InputNumber.CursorPosition; (tail < InputNumber.WritePosition)&&(InputNumber.Buffer[tail] != ','); tail++) {
				if (CheckInputNumberCode(InputNumber.Buffer[tail]) == TRUE) {
					block_clear = 1;
				}
			}

			/* 前方位置を探す。その間に短縮/グループ/ワンタッチがあるか調べる */
			for (top = InputNumber.CursorPosition; (InputNumber.Buffer[top] != ',') && (top > 0); top--) {
				if (CheckInputNumberCode(InputNumber.Buffer[top]) == TRUE) {
					block_clear = 1;
				}
			}
			if ((top == 0) && (block_clear == 0)) {
				if (CheckInputNumberCode(InputNumber.Buffer[top]) == TRUE) {
					block_clear = 1;
				}
				/* 先頭にはコンマは入力できないので、コンマかどうかのチェックは不要 */
			}
		}
#else
		/* 後方位置を探す。その間に短縮/グループ/ワンタッチがあるか調べる */
		for (tail = InputNumber.CursorPosition; (tail < InputNumber.WritePosition)&&(InputNumber.Buffer[tail] != ','); tail++) {
			if (CheckInputNumberCode(InputNumber.Buffer[tail]) == TRUE) {
				block_clear = 1;
			}
		}

		/* 前方位置を探す。その間に短縮/グループ/ワンタッチがあるか調べる */
		for (top = InputNumber.CursorPosition; (InputNumber.Buffer[top] != ',') && (top > 0); top--) {
			if (CheckInputNumberCode(InputNumber.Buffer[top]) == TRUE) {
				block_clear = 1;
			}
		}
		if ((top == 0) && (block_clear == 0)) {
			if (CheckInputNumberCode(InputNumber.Buffer[top]) == TRUE) {
				block_clear = 1;
			}
			/* 先頭にはコンマは入力できないので、コンマかどうかのチェックは不要 */
		}
#endif

		if (block_clear == 1) { /* 一括して消去する場合 .コンマとコンマで囲まれた部分、先頭からコンマまで、コンマから最後までを消去*/
			/*----------------------------------------------------------------*/
			/*456 , S 0 0 1 ,1 2 3....					4 5 6 , 123			  */
			/*	  |	  ~		|			 ----->				  ~				  */
			/*	  top	  tail												  */
			/*----------------------------------------------------------------*/
			/*S 0 0 1 ,1 2 3....				123							  */
			/*|	  ~	  |			   ----->		~							  */
			/*top	  tail													  */
			/*----------------------------------------------------------------*/

			InputNumber.CursorPosition = top;
			while (tail > top) {
				InputNumberDataShift(SHIFT_FORWORD);
				tail--;
			}
		}
		else { /* カーソル上１文字だけ消去 */
#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
			if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '/')) {		/* ダイヤル記号（ポーズ） */
				InputNumberDataShift(SHIFT_FORWORD);
			}
			if ((InputNumber.Buffer[InputNumber.CursorPosition] == '-')
			 && (InputNumber.Buffer[InputNumber.CursorPosition + 1] == '!')) {		/* ダイヤル記号（トーン） */
				InputNumberDataShift(SHIFT_FORWORD);
			}
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
			if (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_PIN_MARK) {	/* 消去するﾃﾞｰﾀがPIN記号の時 */
				chk_start_pos = InputNumber.CursorPosition;	/* 検索開始位置をセット */
				is_pin_mark_clear = TRUE;
			}
#endif

			InputNumberDataShift(SHIFT_FORWORD);
		}

		/* バッファの先頭がコンマかどうかしらべ、コンマなら詰める */
		/*---------------------------*/
		/* S001,123 -> ,123 ---> 123 */
		/*	~		   ~		 ~	 */
		/*---------------------------*/
		if ((InputNumber.CursorPosition == 0) && (InputNumber.Buffer[InputNumber.CursorPosition] == ',')) {
			InputNumberDataShift(SHIFT_FORWORD);
		}

		/* コンマが２個続く場合（123,4,567の様な形で4を消去した場合、123,,567となる）*/
		/*-------------------------------------*/
		/* 123,4,567 -> 123,,567  ---> 123,567 */
		/*	   ~			~			  ~	   */
		/*-------------------------------------*/
		if ((InputNumber.Buffer[InputNumber.CursorPosition - 1] == ',')
		 && (InputNumber.Buffer[InputNumber.CursorPosition] == ',')) {
			InputNumberDataShift(SHIFT_FORWORD);
		}

		/* 入力後端位置の更新 */
		InputNumber.WritePosition = GetStringGapPoint(InputNumber.Buffer , NULL);

#if (PRO_NEW_DIAL_OPR == ENABLE)	/* by K.Watanabe 1998/04/03 */
		/* カーソルが同報記号にあってもデータを消せる様にした為に、この処理があるとカーソルの動きが
		** 不自然になるので止めます
		** 例１）ｸﾘｱｷｰ押下前             この処理があった時    この処理をなくした時
		** 　　　123,[01]            　　12,[01]             　12,[01]             
		**          ~                       ~                    ~
		** ただし、カーソルが同報記号上でない時に、この処理がないと動きが不自然になるパターン（例２）も
		** ありますが、単純にカーソル位置が同報記号上の時だけ例１にすると、また別に不自然になる場合（例３）が
		** 出てくるので例２の場合はあきらめます
		** 例２）ｸﾘｱｷｰ押下前             この処理がない時      理想
		** 　　　[01],S001,[02]      　　[01],[02]           　[01],[02]           
		**            ~                      ~                      ~
		** 例３）ｸﾘｱｷｰ押下前             判断追加              この処理をなくした時
		** 　　　123,456             　　12,456              　12,456              
		**         ~                        ~                    ~
		*/
#else
		/* カーソル上がコンマの場合、次に進めておく */
		/*-----------------------*/
		/* 123,567 ----> 123,567 */
		/*	  ~				 ~	 */
		/*-----------------------*/
		if (InputNumber.Buffer[InputNumber.CursorPosition] == ',') {
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)
			if (CheckDirectAdrAtCursorPos() == FALSE) {
				InputNumber.CursorPosition++;
			}
 #else
			InputNumber.CursorPosition++;
 #endif
		}
#endif

#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
		/* 注）実際にはありえませんが、元々、直接ダイヤルの先頭の'*'だけはPIN記号に
		** 　　変換していなかったので、合わせておきます
		*/
		if ((InputNumber.Buffer[InputNumber.CursorPosition] == OPR_PIN_MARK)
		 && ((InputNumber.CursorPosition == 0) || (InputNumber.Buffer[InputNumber.CursorPosition - 1] == ','))) {
			InputNumber.Buffer[InputNumber.CursorPosition] = TEN_AST_KEY;
			chk_start_pos = InputNumber.CursorPosition + 1;	/* 検索開始位置をセット */
			is_pin_mark_clear = TRUE;
		}

		if (is_pin_mark_clear) {	/* PIN記号を消去した時 */
			/* カーソル位置より後ろに'*'が入力されていたら、PIN記号に変換します */
			for (i = chk_start_pos; i < InputNumber.WritePosition; i++) {	/* 入力バッファの最後まで */
				if (InputNumber.Buffer[i] == ',') {	/* 検索位置が同報記号になった時 */
					break;
				}

				if (InputNumber.Buffer[i] == TEN_AST_KEY) {	/* カーソル位置以降に'*'があった時 */
					InputNumber.Buffer[i] = OPR_PIN_MARK;	/* PIN記号に変換します */
					break;
				}
			}
		}
#endif
	}
}

/*************************************************************************
	module		:[電話帳登録データをコマンド登録バッファに展開]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/24]
	author		:[江口]
*************************************************************************/
void SetTelBookDataToInputBuffer(void)
{
	UBYTE	set_data[7];
	UBYTE	length;
	UBYTE	onetouch;
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	number;
#endif
	UWORD	number;
	UWORD	optional_number;	/* 任意短縮番号 */

	CMN_MemorySet(set_data, 7, NULL);
	length = 0;

	number = (UWORD)SYB_TelephoneBookData[GetTelBookDataPoint()][OPR_TELBOOK_DATANUMBER];

	if (number < SYS_ONETOUCH_MAX) {	/* ワンタッチの場合 */
		onetouch = CMN_OffsetToOnetouchCode((UBYTE)number);
		InputNumberOnetouchSet(onetouch);
	}
	else {								/* 短縮の場合 */
		number -= SYS_ONETOUCH_MAX;
		if ((InputNumber.CursorPosition != 0) && (InputNumber.Buffer[InputNumber.CursorPosition - 1] != ',')) {
			set_data[length++] = ',';
		}
		set_data[length++] = OPR_SPEED_MARK;
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
			CMN_UnsignedIntToASC(&set_data[length], (UWORD)(number + OPR_SPEED_DIAL_MIN), SPEED_FIGURE_MAX, '0');
		}
		else{	/* 任意短縮の時 */
			optional_number = GetRecordFromNumber( number );
			CMN_UnsignedIntToASC(&set_data[length], optional_number, SPEED_FIGURE_MAX, '0');
		}
		length += SPEED_FIGURE_MAX;
		if ((InputNumber.Buffer[InputNumber.CursorPosition] != ',')
		&&	(InputNumber.CursorPosition != InputNumber.WritePosition)) {
			set_data[length++] = ',';
		}
		InsertInputData(&set_data[0], length);
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ送信オペレーション]
	function	:[
		1.
	]
	return		:[
		OPR_CONTINUE	:コマンド入力継続
		OPR_END			:コマンド入力終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/30]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE ProgramOnetouchExecute(UBYTE prog_no)	/* 選択されたワンタッチダイアル */
{
	/*-------------------------------------*
	 * 通信中の場合２回スタートキーを押す
	 * １回なくなったがまた復活
	 * ロムディップで切替
	 * 1996/07/18 Eguchi
	 * 他機種とは順番が違うがゆるしてここしか無理です
	 * この後で通信が始まってしまった場合はしらん
	 *-------------------------------------*/
	if (CheckFaxComExecute() == TRUE) {	/* 通信中の場合 */
		if (PushStartTwiceFaxCom == 1) {	/* スタートキー２回押しの場合 */
			if (FaxComTxReserveOperation() == OPR_END) {	/* STOP */
				ReleaseCommandFileRequest = TRUE;	/* 終了時コマンドファイル解放 */
				return(OPR_END);
			}
		}
	}

	/* 送信できるかのチェックで、応用通信でセットされる変数でポーリング等のチェックを行っているので、
	** 正しくチェックされるように、先に応用通信の情報だけをプログラムワンタッチの変数からコピーします
	** 注）同じタイミングでダイヤル番号も取り出してしまうと、コマンド入力継続で戻った時に、
	** 　　表示がプログラムワンタッチに登録されている番号に変わってしまいます by K.Watanabe 1997/11/28
	*/
	GetProgramOnetouchOption(prog_no);	/* プログラムワンタッチの応用通信の情報を応用通信登録用変数にコピー */

#if (PRO_CIPHER == ENABLE)
	/*-------------------------*/
	/** 暗号化送信時のチェック */
	/*-------------------------*/
	if (CheckCipherExecEnable(OPR_CIPHER_TX) == FALSE) {
		NackBuzzer();
		return(OPR_CONTINUE);	/* コマンドオペレーション継続(再入力) */
	}
#endif

	/* メモリーオーバー・ジャムリカバーオペレーション等が起こっている時に、
	** 原稿読み取りを行うと問題があるので、チェックします
	** 注）メモリーオーバーオペレーションが起こっている場合、蓄積中のステータスが立ったままなので、
	** 　　CheckScanStartEnable()より後に行うと、エラー表示のみで処理を抜けてくれないので、
	** 　　ここでは先にチェックします
	*/
	/* Add By O.Kimoto 1999/07/19 */
	if (CheckScanDisableCondition() == TRUE) {
		NackBuzzer();
		ReleaseCommandFileRequest = TRUE;
		return(OPR_END);
	}

	/*-------------------------------------------*
	 * 送信コマンドの場合、読み取り可能か調べる
	 *-------------------------------------------*/
	if (CheckPollingCommandInput() == FALSE) {	/* 送信コマンドの場合（ポーリングでない場合) */
		if (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE) {
			/* 原稿読み取り不可能な時（ブック原稿サイズ未設定も含む）は、一度コマンド入力に戻ります */
			NackBuzzer();
			return(OPR_CONTINUE);
		}

		/* ＦＢＳからの送信か、複数宛先が指定されている時、メモリオーバーなら蓄積を行いません
		** 注）メモリーオーバーのエラーが発生していても、メモリーに十分な空き領域が
		** 　　存在する場合もありますが、蓄積は禁止します
		*/
		if ((CMN_CheckMemoryTxSetting() == FALSE) || (InputNumber.MultiNumberStatus)) {
			if (CheckMemoryOver() == TRUE) {	/* メモリーオーバーあり */
				NackBuzzer();
				ReleaseCommandFileRequest = TRUE;	/* 終了時コマンドファイル解放 */
				return(OPR_END);
			}
		}
	}

	/*-------------------------------*
	 ** コマンドファイルを掴みにいく *
	 *-------------------------------*/
	if (CheckAndGetCommandArea() == NG) { /** コマンドファイルが確保できない.すべて使用中 */
		NackBuzzer();
		OPR_ChildErrorFlag = COMMAND_FULL_ERROR;	/* "ﾂｳｼﾝ ﾃﾞｷﾏｾﾝ         " */
		ReleaseCommandFileRequest = TRUE; /*終了時コマンドファイル解放 */
		return(OPR_END);	/* コマンドオペレーション終了 */
	}

	/*----------------------------------------------------------------------*
	 * プログラムワンタッチは他の応用機能とあわせて使用することはできない
	 * プログラムワンタッチは同報に使用してはいけない。
	 * プログラムワンタッチは発呼にいけない場合、再入力でなく終了する
	 * よってこの時点でコマンド登録用のバッファをクリアしても問題はない
	 * ここでクリアしていないバッファにここにくるまでに値がセットされているということは絶対にない
	 *
	 *----------------------------------------------------------------------*/
	CMN_MemorySet(InputNumber.Buffer, OPR_INPUT_NUMBER_BUFFER_MAX + 1, NULL);
	InputNumber.WritePosition = 0;
	InputNumber.CursorPosition = 0;
	InputNumber.MultiNumberStatus = 0;

	/*----------------------------------------------------------------------------*
	 * 通常のコマンド送信と同じ関数を使用するために、プログラムワンタッチの内容を
	 * コマンド登録用のバッファにコピーします
	 *----------------------------------------------------------------------------*/
	SetProgramDialToInputNumber(prog_no);	/* ダイアル番号をコマンド登録用バッファに展開 */

#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	GetProgramTime(SYB_ProgramOnetouch[prog_no].EntryData.Command.ExecTime);	/* 送信時刻をとりだし */
#else
	GetProgramTime(SYB_ProgramOnetouch[prog_no].ExecTime);	/* 送信時刻をとりだし */
#endif

	CalculateProgramExecTime();				/* コマンドファイルにセットできる値(実際の送信時刻）に変換 */

	/*---------------------------------*
	 * 部門管理オペレーション
	 *---------------------------------*/
#if (PRO_DEPARTMENT == ENABLE)
	if (CHK_DepartmentON()) { /** 部門管理ＯＮ */
		if (DepartmentCodeOperation() == NG) { /* ＳＴＯＰ */
			ReleaseCommandFileRequest = TRUE; /**終了時コマンドファイル解放 */
			return(OPR_END);
		}
	}
#endif

	/*---------------------------------*
	 * ＰＩＮ番号入力オペレーション
	 *---------------------------------*/
	/*------------------------------------*/
	/** ＰＩＮ番号入力実行				  */
	/*------------------------------------*/
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE2) {	/* 個人別ＰＩＮの場合 */
		if (PinAccessOperation() == NG) {	/* STOP */
			ReleaseCommandFileRequest = TRUE;	/* 終了時コマンドファイル解放 */
			return(OPR_END);
		}
	}
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
	/*------------------------------------------------*/
	/* シングルキーにプログラムワンタッチの値をセット */
	/*------------------------------------------------*/
	SetProgramToSingleKey(prog_no);
#endif

	/*------------------------------------------------------*/
	/** コマンドファイルにプログラムワンタッチの内容をセット*/
	/*------------------------------------------------------*/
#if (PRO_PIN_ACCESS == ENABLE)
	/* 発呼時（コマンド登録時）のＰＩＮアクセスの設定状態をセット */
	SetCommandPinAccessMode(&SYB_CommandFile[SettingCommandFileNumber]);
#endif
	SetCommandDialNumber();		/* コマンドファイルにダイアル番号を展開		*/
	SetCommandTime();			/* コマンドファイルに通信開始時間を展開		*/
	SetCommandOption();			/* コマンドファイルに通信種別を展開			*/
	SetCommandTitleMessage();	/* コマンドファイルにカバーページ設定を展開	*/
	SetCommandPage();			/* コマンドファイルに送信枚数を展開			*/
#if (PRO_DEPARTMENT == ENABLE)
	SetCommandDepartCode();		/* コマンドファイルに部門コードをセット		*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
	SetCommandAbility();		/* コマンドファイルに付加属性をセット		*/
#endif
	SetCommandPinNumber();		/* コマンドファイルにＰＩＮ番号をセット(Mode2のときのみ値がはいる）	*/

#if (0) /* ＡＤＦ／ＦＢＳはＭＡＮタスクでセットします。T.Nose 1997/06/27 */
	/*---------------------------------*
	 * 送信原稿の読み取り先をセット
	 *---------------------------------*/
	if (CMN_CheckScanDocOnFeeder() == TRUE) {	/* ＡＤＦに原稿がセットされている時 */
		SYS_ScannerExecMode = SCN_ADF;
	}
	else {										/* ＦＢＳに原稿がセットされている（ADFに原稿がｾｯﾄされていない）時 */
		SYS_ScannerExecMode = SCN_FBS;
	}
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add by O.Kimoto 1998/11/25 */
	SetRxDocTransferPageCount();
#endif

	/*---------------------------------*
	 * メインにメッセージ送信
	 *---------------------------------*/
	if (CMN_CheckMemoryTxCommand(SettingCommandFileNumber, CMN_STATUS_NO_CHK) == TRUE) {
		/* メモリー送信コマンドの場合 */
#if (PRO_CIPHER == ENABLE)
		/* 暗号化送信だけメインへのメッセージが違います by K.Watanabe 1998/02/09 */
		if (SYB_CommandFile[SettingCommandFileNumber].Option.Item == SYS_CIPHER_TX) {	/* 暗号化送信 */
			OperationMessageToMain.Message = MSG_STORE_CIPHER_DOC;
		}
		else {
			OperationMessageToMain.Message = MSG_STORE_MEMORY_TX_DOC;
		}
#else
		OperationMessageToMain.Message = MSG_STORE_MEMORY_TX_DOC;
#endif
		OperationMessageToMain.SubMessage1 = (UWORD)SettingCommandFileNumber;
		SYB_CommandFile[OperationMessageToMain.SubMessage1].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[OperationMessageToMain.SubMessage1] = SYS_CMD_SETTING;
#endif
	}
	else {
		/* スキャナコマンドの場合 */
		OperationMessageToMain.Message = MSG_ENTER_COMMAND;
		OperationMessageToMain.SubMessage1 = (UWORD)SettingCommandFileNumber;
		SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_WAITING;
#endif
	}
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();

	OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
	ReleaseCommandFileRequest = FALSE; /* 念のため */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
	if (CheckPollingCommandInput() == FALSE) {	/* ポーリング以外の送信の時 */
		IsTxOrScanStart = TRUE;	/* 送信・原稿読み取り開始 */
	}
#endif

	return(OPR_END);
}

/*************************************************************************
	module		:[送信予約オペレーション]
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
	date		:[1995/03/30]
	author		:[江口]
*************************************************************************/
UBYTE FaxComTxReserveOperation(void)
{
	/***************************************************************
	 * 通信中の場合、通常の通信予約とは異なり、２回スタートキーを
	 * 押すことにします。 やむおえない事情による
	 * このモジュールはその２回めのスタートキーを取り込むためのものです
	 * ストップキーが押されるか、１分間キー入力がない場合、オペレーション
	 * は終了します
	 ***************************************************************/
	UBYTE	key;
	UBYTE	keytype;

	/* 表示きりかえ */
	DisplayStringHigh(0 , D2W_PressStartAgain); /* 表示変更。1996/09/04　Eguchi */
	DisplayCommandNumber();

	while (1) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key		= GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);

		case START:
			return (OPR_CONTINUE);

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif

		case NO_EFFECT:
			break; /* Nackを鳴らさないため */

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[部門管理オペレーション]
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
	date		:[1995/03/30]
	author		:[江口]
*************************************************************************/
#if (PRO_DEPARTMENT == ENABLE)
UBYTE DepartmentCodeOperation(void)
{
	/***********************************************************************
	 * 部門管理設定がONのとき部門管理オペレーションをおこなう
	 * スタートキーが押された後に、部門管理コードの入力を促します
	 * 入力されていた部門コードが登録されているものであれば、通信を実行します
	 * 存在しない部門コードを入力、ストップキーを入力、１分間キー入力なし
	 * の場合はオペレーション終了し、通信は実行しません
	 ***********************************************************************/
	UBYTE	key;

	/* 部門コードの入力実行 */

	ClearCharacterInput();
	CharacterInput.MaxFigure = 4;
	DisplayStringHigh(0 , D2W_EnterDepartmentCode);

	while (1) {
		DisplayNumberInput();
		key = NumberInputKeyGet();
		switch (key) {
		case START_KEY:
			if (CheckCharacterInputEmpty() == TRUE) {
				NackBuzzer();
			}
			else {
				return (CheckInputDepartCode());
			}
			break;
		case STOP_KEY:
			return (NG);

		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif	/* (PRO_DEPARTMENT == ENABLE) */

/*************************************************************************
	module		:[送信時に入力された部門コードが登録されているか調べる]
	function	:[
		1.
	]
	return		:[
		OK:登録済み
		NG:未登録
	]
	common		:[SYB_DepartmentCode]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
#if (PRO_DEPARTMENT == ENABLE)
UBYTE CheckInputDepartCode(void)
{
	UWORD	code;
	UBYTE	i;

	code = CharacterInputToNumber();
	/* 部門コードチェック */
	for (i = 0; i < SYS_DEPART_MAX; i++) {
		if (SYB_DepartmentCode[i] == code) {
			SpecialCommandValue.DepartmentCode = code;
			return (OK);
		}
	}

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* 部門管理コード入力時、未登録コードが入力された場合は、「セット サレテイマセン」と表示するように
	** 品証部より、変更依頼が有ったため、
	** 尚、現状のポプラはすでに量産開始しており、マニュアル等の修正の問題も発生するので、
	** 対応はＨＩＮＯＫＩのみとします。
	** by O.Kimoto 1999/02/01
	*/
	OPR_ChildErrorFlag = NO_DEPARTMENTCODE_ERROR;
#endif

	NackBuzzer();
	return (NG);
}
#endif

/*************************************************************************
	module		:[ＰＩＮ番号入力オペレーション]
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
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE PinAccessOperation(void)
{
	DisplayStringHigh(0 , D2W_EnterPinNumber);
	if (PinNumberInput(NULL , START_PIN_NUMBER) == OK) {
		/* ＰＩＮ番号はＭＡＸ桁まで登録すると終端文字が付けられないため
		** ＢＣＤに変換する前に0xFFで初期化した後、
		** StoreCharacterInputValue()で引数 BCD_PIN_DATA_TYPE を指定し
		** 桁数指定で変換するように変更します
		** 97/12/05 T.Fukumoto
		*/
		CMN_MemorySet(SpecialCommandValue.PIN_Number, SYS_PIN_MAX, 0xFF);
		StoreCharacterInputValue(SpecialCommandValue.PIN_Number , BCD_PIN_DATA_TYPE);
		return (OK);
	}
	return (NG);
}
#endif

/*************************************************************************
	module		:[プログラム送信時刻セット]
	function	:[
		1.プログラムワンタッチ・一括送信にセットされている送信時刻を
		　コマンドファイルにセットする形に変換する
		2.月始めからの積算分数として格納されているデータを、基準時間からの積算分数に直す
	]
	return		:[なし]
	common		:[SpecialCommandValue]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/27]
	author		:[江口]
*************************************************************************/
void CalculateProgramExecTime(void)
{
	/* 送信時刻の計算 */
	/************************************************************************************************
	 * 仕様																							*
	 * (1)日に０日が指定されている場合																*
	 *	  1.送信時刻が現在時刻よりも前の場合、次の日の指定時刻に送信する							*
	 *	  2.送信時刻が現在時刻より以降の場合、指定時刻に送信する									*
	 * (2)日に０日が指定されていない場合															*
	 *	  1.送信時刻が現在時刻よりも前の場合、翌月の指定時刻に送信する。							*
	 *	　　もし、翌月に指定日が存在しなかった場合は翌々月の１日の指定時間に送信する。				*
	 *	  2.送信時刻が現在時刻以降の場合で、指定日が現在の月に存在しない場合、翌月の指定時刻に		*
	 *		送信を行う。もし翌月に指定日が存在しなかった場合、翌々月の１日の指定時間に送信する。	*
	 *	  3.上記以外の場合、指定された時刻に送信を行う												*
	 * ※時刻指定送信の場合とは異なっているので注意													*
	 ************************************************************************************************/
	UBYTE	trans_day;
	UBYTE	trans_hour;
	UBYTE	trans_minute;
	UBYTE	current_day;
	UBYTE	current_hour;
	UBYTE	current_minute;
	UBYTE	max_day;
	UBYTE	next_month;
	UBYTE	next_max_day;
	UBYTE	add_day;
	UBYTE	next;
	UDWORD	add_minute;

	next = 0;
	add_day = 0;

	if (SpecialCommandValue.CommandTime == 0) { /* 時刻がセットされていない */
		return;
	}
	if (SpecialCommandValue.CommandTime & 0x80000000UL) {
		SpecialCommandValue.CommandTime &= ~0x80000000UL;
	}
	trans_day	 = (UBYTE)(SpecialCommandValue.CommandTime / 1440);
	trans_hour	 = (UBYTE)((SpecialCommandValue.CommandTime % 1440) / 60);
	trans_minute = (UBYTE)((SpecialCommandValue.CommandTime % 1440) % 60);

	CMN_LongTimeToBCD(&OperationTime.BCD_StructTime , SYB_CurrentTime);
	current_day	   = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Date);
	current_hour   = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Hour);
	current_minute = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Minute);

	if (trans_day == 0) { /* ０日が指定 */
		if (( trans_hour <	current_hour)
		||	((trans_hour == current_hour)&&(trans_minute < current_minute))) {
			/* 入力された指定時刻が現在時刻よりも前 */
			/* 翌日に送信する */
			next = 1;
		}
		add_minute = (UDWORD)(24 * next * 60)
				   + (UDWORD)(trans_hour * 60 + trans_minute)
				   - (UDWORD)(current_hour * 60 + current_minute);
	}
	else {
		max_day = GetDayFromMonth(CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Year),
								  CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Month));
		next_month = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Month) + (UBYTE)1;
		if (next_month > 12)
			next_month = 1;
		next_max_day = GetDayFromMonth(CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Year), next_month);

		if (( trans_day <  current_day)
		||	((trans_day == current_day)&&(trans_hour <	current_hour))
		||	((trans_day == current_day)&&(trans_hour == current_hour)&&(trans_minute < current_minute))
		||	((trans_day >  current_day)&&(trans_day > max_day))) {
			/* 翌月に送信する */
			if (trans_day > next_max_day) { /* 翌月に該当する日が存在しない */
				/* 翌々月の１日に送信する */
				trans_day = 1;
				add_day = max_day + next_max_day;
				next = 1;
			}
			else {
				add_day = max_day;
				next = 1;
			}
		}

		/* 送信指定時刻と現在時刻の差分を計算 */
		add_minute = 0;
		if (next) {
			add_minute = (UDWORD)add_day;
			add_minute *= 24 * 60;	/* 日数を分に換算 */
		}
		add_minute += TotalMinutesFromMonthHead((UBYTE)(trans_day - 1), trans_hour, trans_minute);
		add_minute -= TotalMinutesFromMonthHead((UBYTE)(current_day - 1), current_hour, current_minute);

	}
/*	*(UDWORD *)(&CharacterInput.Buffer[22]) = add_minute;*/
	SpecialCommandValue.CommandTime = 0x00000000UL;
	SpecialCommandValue.CommandTime = add_minute + SYB_CurrentTime / 60;
}

/*****************************************/
/*		コマンドファイル操作関数群		 */
/*****************************************/
/*************************************************************************
	module		:[コマンドファイルを掴む]
	function	:[
		1.すでにコマンドファイルを掴んでいたらOKを返す
		2.コマンドファイルの未使用領域を探し、確保する
		3.確保したとき、確保したコマンドファイルの内容をクリアしておく
		4.コマンドファイルに空きがない場合はNGを返す
	]
	return		:[
		OK:コマンドファイル確保OK或いはすでに確保している
		NG;コマンドファイルに空きがない
	]
	common		:[
		SYB_CommandFile			:コマンドファイル
		SettingCommandFileNumber:設定中のコマンドファイル番号
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/29]
	author		:[江口]
*************************************************************************/
UBYTE CheckAndGetCommandArea(void)
{
	UBYTE	com_file;

	if (SettingCommandFileNumber != NO_SETTING_COMMAND_FILE) {	/*コマンドファイル確保済み */
		/** 既にコマンドファイルを確保している場合、なにもしない */
		return (OK);
	}
	else {
		/** コマンドファイルの未使用領域をさがし、確保する */
		com_file = CMN_GetCommandArea();
		if (com_file < SYS_COM_FILE_MAX) { /** コマンドファイルが確保できた */
			/** 確保したコマンドファイルデータをクリア*/
			ClearCommandFileData(&SYB_CommandFile[com_file]);
			SettingCommandFileNumber = com_file;
			return (OK);
		}
		if (com_file >= SYS_COM_FILE_MAX) { /** コマンドファイルが確保できなかった */
			/** ＮＧを返す */
			return (NG);
		}
	}
}

/*************************************************************************
	module		:[コマンドエリア解放]
	function	:[
		1.コマンドエリア解放
	]
	return		:[なし]
	common		:[
		SYB_CommandFile:
		CommnadFileNo:
	]
	condition	:[]
	comment		:[
		入力中の状態のコマンドエリアをサーチし、空き状態とする。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/18]
	author		:[江口]
*************************************************************************/
void ReleaseCommandArea(void)
{
	if (SettingCommandFileNumber != NO_SETTING_COMMAND_FILE) { /* セットするためコマンドファイルを掴んでいた */
		if (SYB_CommandFile[SettingCommandFileNumber].Status == SYS_CMD_SETTING) { /* ステータスがセット中のまま */
			SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_EMPTY;	   /*解放 */
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_EMPTY;	   /*解放 */
#endif
		}
	}
	SettingCommandFileNumber = NO_SETTING_COMMAND_FILE;
}

/*************************************************************************
	module		:[コマンドファイルデータをクリア]
	function	:[
		1.コマンドファイルを確保したときにステータス以外を初期化
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
void ClearCommandFileData(struct SYS_CommandData_t *com_ptr)
{
	/* ダイアル番号のクリア */
	ClearDialNumber(&com_ptr->DialNumber);

#if (PRO_PIN_ACCESS == ENABLE)
	/* ＰＩＮ番号のクリア */
	ClearCommandPinNumber(com_ptr);
	ClearDialPinNumber(&com_ptr->DialNumber);
#endif
	/* 送信時刻のクリア */
	com_ptr->ExecTime = 0x00000000UL;

	/* オプションのクリア */
	com_ptr->Option.Item = SYS_CHAR_TX; /*Itemのみクリア*/

	com_ptr->Option.ConfirmationReport = 0;

#if (PRO_DEPARTMENT == ENABLE)
	/* 部門管理コードのクリア */
	com_ptr->DepartmentCode = 0xFFFF;
#endif

	/* タイプの初期化 */
	com_ptr->Type = 0;

	/* カバーメッセージ設定の初期化 */
	com_ptr->TitleMessage = 0;

	/* ページ枚数の初期化 */
	com_ptr->Page = 0;

	/* 付加属性の初期化*/
	com_ptr->Ability = 0;

#if (PRO_PIN_ACCESS == ENABLE)
	/* ＰＩＮアクセスモードの初期化 */
	com_ptr->PIN_AccessMode = 0;
#endif
}

/*************************************************************************
	module		:[指定されたダイアルをクリアする]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDialNumber(struct SYS_DialData_t *dial_ptr)
{
	UWORD	i;	/* ﾙｰﾌﾟ変数 */

	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {
		dial_ptr->Direct[i][0] = 0xF0;
	}
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		dial_ptr->Onetouch[i] = 0;
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		dial_ptr->Speed[i] = 0;
	}
	dial_ptr->Group = 0;
}

/*************************************************************************
	module		:[コマンドＰＩＮ番号をクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
void ClearCommandPinNumber(struct SYS_CommandData_t *com_ptr)
{
#if (PRO_PIN_ACCESS == ENABLE)
	CMN_MemorySet(com_ptr->PIN_Number, SYS_PIN_MAX, 0xFF);
#endif
}

/*************************************************************************
	module		:[ダイアルＰＩＮ番号をクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDialPinNumber(struct SYS_DialData_t *dial_ptr)
{
#if (PRO_PIN_ACCESS == ENABLE)
	UBYTE	dial;

	/* for (dial = 0; dial < SYS_COM_DIAL_MAX; dial++) { Change SYS_COM_DIAL_MAX to SYS_COM_DIRECT_DIAL_MAX 1998/01/21  By T.Yamaguchi */
	for (dial = 0; dial < SYS_COM_DIRECT_DIAL_MAX; dial++) {
		CMN_MemorySet(&dial_ptr->PIN_Number[dial][0], SYS_PIN_MAX, 0xFF);
	}
#endif
}

/*************************************************************************
	module		:[コマンド発呼処理]
	function	:[
		1.コマンドファイルを確保する
		2.入力されたダイアル番号を検査する
		3.部門管理がＯＮならば、部門コードの入力オペレーションを実行
		4.ＰＩＮモードがＭｏｄｅ２の場合、ＰＩＮ番号の入力を行う
		5.送信コマンドの場合、原稿読み取り可能かしらべる。
		6.コマンドファイルにデータをセット
		7.メインにメッセージ送信
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/26]
	author		:[江口]
*************************************************************************/
UBYTE CommandStartOperation(void)
{
	/*-------------------------------------*
	 * 通信中の場合２回スタートキーを押す
	 * １回なくなったがまた復活
	 * ロムディップで切替
	 * 1996/07/18 Eguchi
	 * 他機種とは順番が違うがゆるしてここしか無理です
	 * この後で通信が始まってしまった場合はしらん
	 *-------------------------------------*/
	 
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正 Added by SMuratec 李 2004/11/09 */
	UBYTE command_no;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/**************************
	** メール送受信中も追加
	**************************/
	if (CheckFaxComExecute() == TRUE
		|| CheckMailComExecute() == TRUE) { /* 通信中の場合 */
		if (PushStartTwiceFaxCom == 1) { /* スタートキー２かい押しの場合 */
			if (FaxComTxReserveOperation() == OPR_END) {/*STOP*/
				ReleaseCommandFileRequest = TRUE; /*終了時コマンドファイル解放 */
				return(OPR_END);
			}
		}
	}
#else
	if (CheckFaxComExecute() == TRUE) { /* 通信中の場合 */
		if (PushStartTwiceFaxCom == 1) { /* スタートキー２かい押しの場合 */
			if (FaxComTxReserveOperation() == OPR_END) {/*STOP*/
				ReleaseCommandFileRequest = TRUE; /*終了時コマンドファイル解放 */
				return(OPR_END);
			}
		}
	}
#endif

	/*----------------------------------*/
	/** 入力された番号のチェックを行う	*/
	/*----------------------------------*/
	if (CheckCommandNumber() == NG) {	/** 番号不良 */
		NackBuzzer();
		return(OPR_CONTINUE);	/* コマンドオペレーション継続(再入力) */
	}

#if (PRO_CIPHER == ENABLE)
	/*-------------------------*/
	/** 暗号化送信時のチェック */
	/*-------------------------*/
	if (CheckCipherExecEnable(OPR_CIPHER_TX) == FALSE) {
		NackBuzzer();
		return(OPR_CONTINUE);	/* コマンドオペレーション継続(再入力) */
	}
#endif

	/* メモリーオーバー・ジャムリカバーオペレーション等が起こっている時に、
	** 原稿読み取りを行うと問題があるので、チェックします
	** 注）メモリーオーバーオペレーションが起こっている場合、蓄積中のステータスが立ったままなので、
	** 　　CheckScanStartEnable()より後に行うと、エラー表示のみで処理を抜けてくれないので、
	** 　　ここでは先にチェックします
	*/
	/* Add By O.Kimoto 1999/07/19 */
	if (CheckScanDisableCondition() == TRUE) {
		NackBuzzer();
		ReleaseCommandFileRequest = TRUE;
		return(OPR_END);
	}

	/*-----------------------------------------*
	 * 送信コマンドの場合、読み取り可能か調べる
	 *-----------------------------------------*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
	if ((!ROM_SW_SpecialDoctorReport || !OPR_SpecialDoctorReportFlag) && CheckPollingCommandInput() == FALSE) {	/* 送信コマンドの場合（ポーリングでない場合) */
 #else
	if (CheckPollingCommandInput() == FALSE) {	/* 送信コマンドの場合（ポーリングでない場合) */
 #endif
#else
	if (CheckPollingCommandInput() == FALSE) {	/* 送信コマンドの場合（ポーリングでない場合) */
#endif
		if (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE) {
			/* 原稿読み取り不可能な時（ブック原稿サイズ未設定も含む）は、一度コマンド入力に戻ります */
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/25 */
			NackBuzzer();
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
				return(OPR_END);			/* コマンドオペレーション終了 */
			}
			else {
				return(OPR_CONTINUE);		/* コマンドオペレーション継続(再入力) */
			}
#else
			NackBuzzer();
			return(OPR_CONTINUE);			/* コマンドオペレーション継続(再入力) */
#endif
		}

		/* ＦＢＳからの送信か、複数宛先が指定されている時、メモリオーバーなら蓄積を行いません
		** 注）メモリーオーバーのエラーが発生していても、メモリーに十分な空き領域が
		** 　　存在する場合もありますが、蓄積は禁止します
		*/
		if ((CMN_CheckScanDocOnFeeder() == FALSE) || (InputNumber.MultiNumberStatus)) {
			if (CheckMemoryOver() == TRUE) {	/* メモリーオーバーあり */
				NackBuzzer();
				ReleaseCommandFileRequest = TRUE;	/* 終了時コマンドファイル解放 */
				return(OPR_END);	/* オペレーションを終了する */
			}
		}
	}

	/*-------------------------------*/
	/** コマンドファイルを掴みにいく */
	/*-------------------------------*/
	if (CheckAndGetCommandArea() == NG) {	/* コマンドファイルが確保できない.すべて使用中 */
		NackBuzzer();
		OPR_ChildErrorFlag = COMMAND_FULL_ERROR;	/* "ﾂｳｼﾝ ﾃﾞｷﾏｾﾝ         " */
		return(OPR_END);	/* コマンドオペレーション終了 */
		/* コマンドファイル解放は必要ない */
	}

	/*---------------------------------*
	 * 部門管理オペレーション
	 *---------------------------------*/
#if (PRO_DEPARTMENT == ENABLE)
	if (CHK_DepartmentON()) { /* 部門管理ＯＮ */
		if (DepartmentCodeOperation() == NG) {
			ReleaseCommandFileRequest = TRUE; /* 終了時コマンドファイル解放 */
			return(OPR_END);
		}
	}
#endif

	/*------------------------------------*/
	/** ＰＩＮ番号入力実行				  */
	/*------------------------------------*/
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE2) {	/* 個人別ＰＩＮの場合 */
		if (PinAccessOperation() == NG) {	/* STOP */
			ReleaseCommandFileRequest = TRUE;	/* 終了時コマンドファイル解放 */
			return(OPR_END);
		}
	}
#endif

	/*------------------------------------*
	 * コマンドファイルにデータをセット
	 *------------------------------------*/
	ClearCommandFileData(&SYB_CommandFile[SettingCommandFileNumber]);	/* セットし直す場合があるのでクリアする */
#if (PRO_PIN_ACCESS == ENABLE)
	/* コマンド登録時のPINアクセスモードをコマンドファイルにセット */
	SetCommandPinAccessMode(&SYB_CommandFile[SettingCommandFileNumber]);
#endif
	SetCommandDialNumber();		/* コマンドファイルにダイアル番号を展開		*/
	SetCommandTime();			/* コマンドファイルに通信開始時間を展開		*/
	SetCommandOption();			/* コマンドファイルに通信種別を展開			*/
	SetCommandTitleMessage();	/* コマンドファイルにカバーページ設定を展開	*/
	SetCommandPage();			/* コマンドファイルに送信枚数を展開			*/
#if (PRO_DEPARTMENT == ENABLE)
	SetCommandDepartCode();		/* コマンドファイルに部門コードをセット		*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
	SetCommandAbility();		/* コマンドファイルに付加属性をセット		*/
#endif
	SetCommandPinNumber();		/* コマンドファイルにＰＩＮ番号をセット(Mode2のときのみ値がはいる）	*/

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/25 */
	SetCommandKeisatsu();
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正 Added by SMuratec 李 2004/11/09 */
	if (!IsScanReserved && (!CheckPollingCommandInput()) ) {
		IsScanReserved = TRUE;
		command_no = SettingCommandFileNumber;
		if ( !ScanReservingOperation() ) {
			SettingCommandFileNumber = command_no;
			ClearCommandFileData(&SYB_CommandFile[SettingCommandFileNumber]);	/* セットし直す場合があるのでクリアする */
			ReleaseCommandFileRequest = TRUE; /* 終了時コマンドファイル解放 */
			IsScanReserved = FALSE;	
			return(OPR_END);
		}
		else {
			SettingCommandFileNumber = command_no;
			IsScanReserved = FALSE;	
		}
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if (PRO_FBS == ENABLE)
	/*---------------------------------*
	 * 次原稿の最終チェック
	 *---------------------------------*/
	if (CMN_CheckMemoryTxSetting() == FALSE) {	/* スキャナー送信に設定されている */
		SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
	}
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add by O.Kimoto 1998/11/25 */
	SetRxDocTransferPageCount();
#endif

	/*---------------------------------*
	 * メインにメッセージ送信
	 *---------------------------------*/
	if (CMN_CheckMemoryTxCommand(SettingCommandFileNumber, CMN_STATUS_NO_CHK) == TRUE) {
		/* メモリー送信コマンドの場合 */
#if (PRO_CIPHER == ENABLE)
		/* 暗号化送信だけメインへのメッセージが違います */
		if (SYB_CommandFile[SettingCommandFileNumber].Option.Item == SYS_CIPHER_TX) {	/* 暗号化送信 */
			OperationMessageToMain.Message = MSG_STORE_CIPHER_DOC;
		}
		else {
			OperationMessageToMain.Message = MSG_STORE_MEMORY_TX_DOC;
		}
#else
		OperationMessageToMain.Message = MSG_STORE_MEMORY_TX_DOC;
#endif
		OperationMessageToMain.SubMessage1 = (UWORD)SettingCommandFileNumber;
		SYB_CommandFile[OperationMessageToMain.SubMessage1].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[OperationMessageToMain.SubMessage1] = SYS_CMD_SETTING;
#endif
	}
	else {
		/* スキャナコマンドの場合 */
#if (PRO_FBS == ENABLE) /* スキャナー送信の時だけＯＰＲ側でセットします T.Nose 1997/10/13 */
		/*---------------------------------*
		 * 送信原稿の読み取り先をセット
		 *---------------------------------*/
		if (!(CMN_CheckScanDocOnFeeder() == TRUE)	/* ＡＤＦに原稿が無い */
		 && (SYB_MaintenanceSwitch[MNT_SW_B4] & FBS_REALTIME_TX)) {
			SYS_ScannerExecMode = SCN_FBS;
		}
		else {										/* ＡＤＦに原稿がセットされている */
			SYS_ScannerExecMode = SCN_ADF;
		}
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
		if (MultiLineBusy() != 0xFF) {
			StopChildDisplay();
			ChildTimer.Time = 200;	/* 表示時間（２秒） */
			StartChildDisplay();
			DisplayStringHigh(0, D2W_SF_OK);	/* テスト用 */
		}
#endif

		OperationMessageToMain.Message = MSG_ENTER_COMMAND;
		OperationMessageToMain.SubMessage1 = (UWORD)SettingCommandFileNumber;
		SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_WAITING;
#endif
	}

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/05 */
if (ROM_SW_SpecialDoctorReport) {
		if (OPR_SpecialDoctorReportFlag) {
			/* 医師会特ＲＯＭはここで強制的にコマンドをＷａｉｔｉｎｇにします。 By O.Kimoto 1999/04/05 */
			OperationMessageToMain.Message = MSG_ENTER_COMMAND;
			OperationMessageToMain.SubMessage1 = (UWORD)SettingCommandFileNumber;
			SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_WAITING;
 #if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_WAITING;
 #endif
		}
}
 #endif
#endif

	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
	ReleaseCommandFileRequest = FALSE; /* 念のため->コマンドファイルを解放されることがないように */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
	if (CheckPollingCommandInput() == FALSE) {	/* ポーリング以外の送信の時 */
		IsTxOrScanStart = TRUE;	/* 送信・原稿読み取り開始 */
	}
#endif
	return (OPR_END);
}

/*************************************************************************
	module		:[コマンドファイルにＰＩＮアクセスのモードをセットする]
	function	:[
		1.確保したコマンドファイルにコマンド登録の時点でのＰＩＮアクセスのモードをセットする。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
void SetCommandPinAccessMode(struct SYS_CommandData_t *com_ptr)
{
#if (PRO_PIN_ACCESS == ENABLE)
	com_ptr->PIN_AccessMode = CHK_PIN_AccessMode();
#endif
}

/*************************************************************************
	module		:[コマンドファイルに電話番号をセット]
	function	:[
		1.確保したコマンドファイルに入力されたダイアル番号を入力する
	]
	return		:[なし]
	common		:[
		SYB_CommandFile
		SettingCommandFileNumber
	]
	condition	:[]
	comment		:[コマンドファイルを確保してからコールすること]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetCommandDialNumber(void)
{
#if (PRO_PIN_ACCESS == ENABLE)
	SetDialNumber(&SYB_CommandFile[SettingCommandFileNumber].DialNumber,
				  SYB_CommandFile[SettingCommandFileNumber].PIN_AccessMode);
#else
	/* ＰＩＮ機能なしの時は、ＰＩＮアクセスモードは関係ないので、とりあえずＰＩＮアクセスしないを渡す */
	SetDialNumber(&SYB_CommandFile[SettingCommandFileNumber].DialNumber, PIN_ACCESS_OFF);
#endif
}

/*************************************************************************
	module		:[電話番号を指定されたダイアルにセットする]
	function	:[
		1.指定されたコマンドファイルに入力されたダイアル番号をセットする。
		2.セットするダイアル番号がダイレクトダイアルの場合でかつＰＩＮアクセスモードが
		　相手先別ＰＩＮの場合、ＰＩＮ番号のセットも行う
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[
		ダイアル番号が正しいことを確認してからコマンドファイルにセットすること

		連続ポーリングでも共通で使用できるように、引数を変更
		void SetDialNumber(struct SYS_CommandData_t *com_ptr)
		void SetDialNumberCP(struct SYS_ContinuousPollingData_t *cont_ptr)

										↓

		void SetDialNumber(struct SYS_DialData_t *dial_ptr, UBYTE pin_access_mode)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetDialNumber(struct SYS_DialData_t *dial_ptr, UBYTE pin_access_mode)
{
	UBYTE	direct_cnt;			/* 直接ダイヤル数 */
	UBYTE	asc_buff[OPR_DIRECT_DIAL_BUFFER_MAX];
	UWORD	length;				/* コンマ～コンマまでのデータ数 */
	UWORD	dial_data;			/* ダイアル番号 */
	UWORD	dial_length;		/* ダイアル番号の桁数 */
	UWORD	pin_length;			/* ＰＩＮ番号の桁数 */
	UWORD	cursor_position;	/* 入力位置 */

	length = 0;
	direct_cnt = 0;
	cursor_position = 0;

	/* コマンド入力バッファの最後まで */
	while ((InputNumber.Buffer[cursor_position] != ' ') && (InputNumber.Buffer[cursor_position] != NULL)) {

		/*--------------------------------------*/
		/* 宛先の種類ごとにデータをセットします */
		/*--------------------------------------*/
		switch (InputNumber.Buffer[cursor_position]) {
		case ',':						/* 同報の区切り記号 */
			cursor_position++;
			break;
		case OPR_ONETOUCH_MARK_LEFT:	/* ワンタッチ記号の左かっこ */
			cursor_position++;	/* ワンタッチの番号に進める（[01]の'0'の位置） */
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], OPR_ONETOUCH_NUMBER_FIGURE);
			CMN_SetBitAssign(dial_ptr->Onetouch, (UBYTE)(dial_data - 1));
			cursor_position += (OPR_ONETOUCH_NUMBER_FIGURE + 1);	/* ワンタッチの次に進める（[01]の']'の後) */
			break;
		case OPR_SPEED_MARK:			/* 短縮記号 */
			cursor_position++;	/* 短縮の番号に進める（S1の'1'の位置 )*/
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], (UBYTE)length);
			if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
				dial_data--;
			}
			else{		/* 任意短縮の時 */
				dial_data	= (UBYTE)SetOptionalSpeedStatus( dial_data );	/* ダイヤルレコードオフセット取得 */
			}
			CMN_SetBitAssign(dial_ptr->Speed, (UBYTE)dial_data);
			cursor_position += length;	/* 短縮の次に進める（S1の'1'の後 )*/
			break;
		case OPR_GROUP_MARK:			/* グループ記号 */
			cursor_position++;	/* グループの番号に進める（G1の'1'の位置 )*/
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], (UBYTE)length);
			if (dial_data == 0) {	/* グループ０が指定されている時 */
				dial_ptr->Group = 0xffffffff;
			}
			else {
				CMN_SetLongBitAssign(&dial_ptr->Group, (UBYTE)(dial_data - 1));
			}
			cursor_position += length;	/* グループの次に進める（G1の'1'の後 )*/
			break;
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/07/10 Y.Matsukuma */
		case OPR_ONETOUCH_MARK:			/* ワンタッチ記号の「Ｕ」 */
			cursor_position++;	/* ワンタッチの番号に進める（U1の'1'の位置 )*/
			dial_data = ChangeOnetouchCode((UWORD)cursor_position); /* ビットアサインのため、ワンタッチコードを数字に置き換える */
			CMN_SetBitAssign(dial_ptr->Onetouch, (UBYTE)dial_data);
			cursor_position += OPR_ONETOUCH_NUMBER_FIGURE;	/* ワンタッチの次に進める（U1の'1'の後 )*/
			break;
 #endif
		default:
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ANZU_Lの場合、アルファベットのワンタッチをここで処理する。1997/07/10 Y.Matsukuma */
			if ((ONETOUCH_A_KEY <= InputNumber.Buffer[cursor_position] 
								&& InputNumber.Buffer[cursor_position] <= ONETOUCH_Z_KEY) 
				|| (ONETOUCH_a_KEY <= InputNumber.Buffer[cursor_position] 
								&& InputNumber.Buffer[cursor_position] <= ONETOUCH_z_KEY)) {
				dial_data = ChangeOnetouchCode((UWORD)cursor_position); /* ビットアサインのため、ワンタッチコードを数字に置き換える */
				CMN_SetBitAssign(dial_ptr->Onetouch, (UBYTE)dial_data);
				cursor_position += OPR_ONETOUCH_NUMBER_FIGURE;	/* ワンタッチの次に進める（'A'の後 )*/
				break;
			}
 #endif
			/* 直接ダイヤル */
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
			dial_length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], (UBYTE)OPR_PIN_MARK);
			if (length - (dial_length + 1) >= 0) {
				pin_length = length - (dial_length + 1);
			}
			else {
				dial_length = length;
				pin_length = 0;
			}
#else
			dial_length = length;
			pin_length = 0;
 #if (PRO_PIN_ACCESS == ENABLE)
			if (pin_access_mode == PIN_ACCESS_MODE1) {	/* ＰＩＮアクセスモードが相手先別ＰＩＮの場合 */
				/** ダイアル番号はチェック済みなので必ずＰＩＮ番号は入力されている筈 */
				dial_length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], (UBYTE)OPR_PIN_MARK);
				pin_length = length - (dial_length + 1);
			}
 #endif
#endif
			CMN_MemorySet(asc_buff, OPR_DIRECT_DIAL_BUFFER_MAX, NULL);
			CMN_StringCopyNum(asc_buff, &InputNumber.Buffer[cursor_position], dial_length);
			CMN_ASC_ToBCD_String(dial_ptr->Direct[direct_cnt], asc_buff);
#if (PRO_PIN_ACCESS == ENABLE)
			if (pin_length > 0) {	/* ＰＩＮ番号あり */
				/* cursor_position += (dial_length + 1); @* +1はＰＩＮの区切りの'*'の分 */
				if (pin_length > (SYS_PIN_MAX * 2)) {
					pin_length = SYS_PIN_MAX * 2;
				}
				CMN_ASC_ToBCD_StringNum(dial_ptr->PIN_Number[direct_cnt],
										&InputNumber.Buffer[cursor_position + dial_length + 1],
										(UBYTE)pin_length);
				cursor_position += length;
			}
			else {
				cursor_position += length;
			}
#else
			cursor_position += length;
#endif
			direct_cnt++;
			break;
		}
	}
}

/*************************************************************************
	module		:[コマンドファイルに送信時刻をセット]
	function	:[
		1.登録中のコマンドファイルに入力された送信時刻をセットする。
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:CommandTime->指定時刻の基準からの積算分
		SYB_CommandFile:ExecTime->基準からの積算秒
		SettingCommandFileNumber:登録中（確保している）コマンドファイル番号
	]
	condition	:[]
	comment		:[コマンドファイルを確保してからコールすること]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口]
*************************************************************************/
void SetCommandTime(void)
{
	if (SpecialCommandValue.CommandTime == 0x00000000UL) { /* 時間がセットされていない（即時の場合） */
		if (SYB_CurrentTime) {
			SYB_CommandFile[SettingCommandFileNumber].ExecTime = (SYB_CurrentTime - 1);
		}
		else {
			SYB_CommandFile[SettingCommandFileNumber].ExecTime = 0x00000000UL;
		}
	}
	else {	/* 指定時刻がセットされている */
		SYB_CommandFile[SettingCommandFileNumber].ExecTime = SpecialCommandValue.CommandTime * 60;
	}
}

/*************************************************************************
	module		:[コマンドファイルに応用機能をセット]
	function	:[
		1.登録中のコマンドファイルに入力された応用機能をセットする。
	]
	return		:[なし]
	common		:[
		SYB_CommandFile
		SettingCommandFileNumber:登録中（確保している）コマンドファイル番号
	]
	condition	:[]
	comment		:[コマンドファイルを確保してからコールすること]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口]
*************************************************************************/
void SetCommandOption(void)
{
	SetCommandOptionItem(&SYB_CommandFile[SettingCommandFileNumber]);
	SetCommandOptionNumber(&SYB_CommandFile[SettingCommandFileNumber], OPR_COM_OPE, NULL);
	SetCommandConfirmReport(&SYB_CommandFile[SettingCommandFileNumber]);
}

/*************************************************************************
	module		:[コマンドオプションのタイプをセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		SYB_CommandFile
		CommandOptionTable
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetCommandOptionItem(struct SYS_CommandData_t *com_ptr)
{
	UBYTE	colum;
	UBYTE	row;

	if (InputNumber.MultiNumberStatus) {	/** 同報の時（宛先が複数箇所指定されている） */
		/* 同報コマンドは無条件にメモリー送信します
		** ただし、スキャナー送信設定の時でも、この場合はＬＥＤは点灯しません
		** （サクラ・イチョウ等そうなっているので仕様を合わせておきます）
		** 注）メモリーオーバーエラーが発生している時は、この関数がコールされる前に同報送信は拒否されています
		*/
		colum = 1;	/* 同報送信をセット */
	}
	else {									/** 同報でない時（宛先は一ヶ所のみ指定されている） */
		if (CMN_CheckMemoryTxSetting() == TRUE) {	/** メモリー送信に設定されている */
			colum = 3;	/* メモリー送信をセット */

			if (CheckMemoryTxEnable() == FALSE) {	/** メモリー送信不可能な時 */
				if (CheckScannerTxEnable() == TRUE) {	/* スキャナ送信可能な時 */
					colum = 2;	/* スキャナ送信をセット */
					ChangeMemoryTx();
				}
			}
		}
		else {										/** スキャナ送信に設定されている */
			colum = 2;	/* スキャナ送信をセット */

			if (CheckScannerTxEnable() == FALSE) {	/* スキャナ送信不可能な時 */
				colum = 3;	/* メモリー送信をセット */
				ChangeMemoryTx();
			}
		}
	}

	for (row = 0; CommandOptionTable[row][0] != 0xFF; row++) {
		if (CommandOptionTable[row][0] == SpecialCommandValue.CommandOption.Item) {
			com_ptr->Option.Item = CommandOptionTable[row][colum];
			break;
		}
	}
}

/*************************************************************************
	module		:[応用通信設定内容セット]
	function	:[
		1.親展，中継指示，検索ポーリング，Ｆコードの詳細データをセット
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		第３引数の option_itemは、modeがOPR_PRG_OPEで、Ｆコードのメニューが
		選択されている時のみ使用します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetCommandOptionNumber(struct SYS_CommandData_t *com_ptr, UBYTE mode, UBYTE option_item)
{
	UBYTE	i;					/* ループ変数 */
#if (PRO_F_CODE == ENABLE)	/* 1997/06/25 Y.Matsukuma */
	UBYTE	fcode_data_pos;		/* Ｆコードデータ格納バッファの配列番号 */
#endif
#if (PRO_CIPHER == ENABLE)
	UBYTE	prog_no;			/* プログラムワンタッチの番号 */
#endif

	switch (SpecialCommandValue.CommandOption.Item) {
	case SYS_SCANNER_SECURE_TX:			/* スキャナ親展送信 */
		com_ptr->Option.OptionNumber.SecureNumber = SpecialCommandValue.CommandOption.OptionNumber.SecureNumber;
		break;
	case SYS_SCANNER_RELAY_BROADCAST:	/* スキャナ中継指示送信 */
		com_ptr->Option.OptionNumber.RelayGroupNumber = 0x00000000UL;
		com_ptr->Option.OptionNumber.RelayGroupNumber = SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber;
		break;
	case SYS_DB_POLLING_RX:				/* 検索ポーリング受信 */
		CMN_WordMemorySet(com_ptr->Option.OptionNumber.DatabaseNumber, (UWORD)SYS_DATA_BASE_MAX, (UWORD)0xFFFF);
		for (i = 0; i < SYS_DATA_BASE_MAX; i++) {
			com_ptr->Option.OptionNumber.DatabaseNumber[i]
			 = SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i];
			if (SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i] == 0xFFFF) {
				break;
			}
		}
		break;
#if (PRO_F_CODE == ENABLE)
	case SYS_SCANNER_SUB_ADDRESS_TX:	/* Ｆコードスキャナ送信 */
	case SYS_SELECT_POLLING_RX:			/* 選択ポーリング受信 */
		if (mode == OPR_COM_OPE) {	/* コマンド入力から呼ばれた時 */
			/* Ｆコードデータ格納バッファの空き領域を獲得します */
			fcode_data_pos = GetEmptyFcodeNumberData(mode);
			if (fcode_data_pos != 0xFF) {	/* 空き領域があった時 */
				/* サブアドレス番号をＡＳＣＩＩからＢＣＤに変換します */
				CMN_ASC_ToBCD_String(SYB_FcodeNumberCDataBuffer[fcode_data_pos].SYS_SubAddressNumber,
									 OPR_FcodeData.SubAddress);
				/* 通信パスワード番号をＡＳＣＩＩからＢＣＤに変換します */
				CMN_ASC_ToBCD_String(SYB_FcodeNumberCDataBuffer[fcode_data_pos].SYS_PassWordNumber,
									 OPR_FcodeData.Password);
				/* Ｆコードデータ格納バッファの配列番号をセットします */
				com_ptr->Option.OptionNumber.FcodeDataPosition[0] = fcode_data_pos;
				com_ptr->Option.OptionNumber.FcodeDataPosition[1] = 0xFF;
			}
		}
		else {						/* プログラムワンタッチ登録から呼ばれた時 */
			/* 一度登録された内容を変更された時（前回の登録がＦコード送信又は、Ｆコードポーリングの時） */
			if ((option_item == SYS_SCANNER_SUB_ADDRESS_TX) || (option_item == SYS_SELECT_POLLING_RX)) {
				fcode_data_pos = com_ptr->Option.OptionNumber.FcodeDataPosition[0];
				/* 前に登録された内容をクリアします */
				CMN_MemorySet(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber,
							  SUB_ADDRESS_NUMBER_MAX,
							  0xFF);
				CMN_MemorySet(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber,
							  PASSWORD_NUMBER_MAX,
							  0xFF);

				/* サブアドレス番号をＡＳＣＩＩからＢＣＤに変換します */
				CMN_ASC_ToBCD_String(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber,
									 OPR_FcodeData.SubAddress);
				/* 通信パスワード番号をＡＳＣＩＩからＢＣＤに変換します */
				CMN_ASC_ToBCD_String(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber,
									 OPR_FcodeData.Password);
			}
			/* 新規登録の時 */
			else {
				/* Ｆコードデータ格納バッファの空き領域を獲得します */
				fcode_data_pos = GetEmptyFcodeNumberData(mode);
				if (fcode_data_pos != 0xFF) {	/* 空き領域があった時（elseはありえません） */
					/* サブアドレス番号をＡＳＣＩＩからＢＣＤに変換します */
					CMN_ASC_ToBCD_String(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber,
										 OPR_FcodeData.SubAddress);
					/* 通信パスワード番号をＡＳＣＩＩからＢＣＤに変換します */
					CMN_ASC_ToBCD_String(SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber,
										 OPR_FcodeData.Password);
					/* Ｆコードデータ格納バッファの配列番号をセットします */
					com_ptr->Option.OptionNumber.FcodeDataPosition[0] = fcode_data_pos;
					com_ptr->Option.OptionNumber.FcodeDataPosition[1] = 0xFF;
				}
			}
		}
		break;
#endif	/* (PRO_F_CODE == ENABLE) */
#if (PRO_CIPHER == ENABLE)
	case SYS_CIPHER_TX:					/* 暗号化送信			*/
		if (mode == OPR_COM_OPE) {	/* コマンド入力から呼ばれた時 */
			CMN_StringCopyNULL(CipherData.Key, OPR_CipherData.Key);				/* 暗号化キーをセット				*/
			CMN_StringCopyNULL(CipherData.KeyClue, OPR_CipherData.KeyClue);		/* 暗号化キーのヒントをセット		*/
			SYB_KeyBookData.KeyExtensionOn = OPR_CipherData.KeyExtensionOn;		/* 拡張キーのＯＮ／ＯＦＦをセット	*/
		}
		else {						/* プログラムワンタッチ登録から呼ばれた時 */
			prog_no = OPR_Buf.ProgOntchCtrl.SelectNumber;
			SYB_CipherPData[prog_no].SetKeyMode = OPR_CipherData.SetKeyMode;				/* キー入力の設定方法	*/
			SYB_CipherPData[prog_no].KeyNumber = OPR_CipherData.KeyBookNumber;				/* キー番号				*/
			CMN_StringCopyNULL(SYB_CipherPData[prog_no].Key, OPR_CipherData.Key);			/* 暗号化キー			*/
			CMN_StringCopyNULL(SYB_CipherPData[prog_no].KeyClue, OPR_CipherData.KeyClue);	/* 暗号化キーのヒント	*/
			SYB_CipherPData[prog_no].KeyExtensionOn = OPR_CipherData.KeyExtensionOn;		/* 拡張キーのON/OFF		*/
		}
		break;
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[通信証の設定をコマンドファイルにセットする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[コマンドファイルのオプションをセットしてからコールすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口]
*************************************************************************/
void SetCommandConfirmReport(struct SYS_CommandData_t *com_ptr)
{
	com_ptr->Option.ConfirmationReport &= ~(SYS_CFR_PRINT | SYS_RCR_SELECT | SYS_TCR_AND_RCR);
	switch (SYB_ConfirmationReportSwitch) {	/* 通信証の状態 */
	case TCR_REQUEST:	/* 送信証 */
		com_ptr->Option.ConfirmationReport |= SYS_CFR_PRINT;
		break;
	case RCR_REQUEST:	/* 受領証 */
		com_ptr->Option.ConfirmationReport |= (SYS_CFR_PRINT | SYS_RCR_SELECT);
		break;
	default:
		break;
	}

	/* ポーリングの場合、セットしない。KIRI/MOMIJIと同じはず */
	if ((com_ptr->Option.Item == SYS_POLLING_RX)
	||	(com_ptr->Option.Item == SYS_SEQUENTIAL_POLLING)
#if (PRO_F_CODE == ENABLE)	/* 97/10/28 T.Yamaguchi */
	||	(com_ptr->Option.Item == SYS_SELECT_POLLING_RX)
#endif
	||	(com_ptr->Option.Item == SYS_DB_POLLING_RX)) {
		com_ptr->Option.ConfirmationReport = 0;
	}
}

/*************************************************************************
	module		:[タイトルメッセージの設定のセット]
	function	:[
		1.タイトルメッセージ（カバーページ）の設定をコマンドファイルにセットする
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:
		SYB_CommandFile:
		SettingCommandFileNumber:セット中（確保している)コマンドファイル番号
	]
	condition	:[]
	comment		:[
		絶対にコマンドファイルを確保してからよびだしてね
		SettingCommandFilenumberに値が入っていないから
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/08/31]
	author		:[江口]
*************************************************************************/
void SetCommandTitleMessage(void)
{
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
if (ROM_SW_SpecialDoctorReport) {
		switch (OPR_SpecialDoctorReportFlag) {
		case ONETOUCH_01_KEY:
			SYB_CommandFile[SettingCommandFileNumber].TitleMessage = 0x11;
			break;
		case ONETOUCH_06_KEY:
			SYB_CommandFile[SettingCommandFileNumber].TitleMessage = 0x21;
			break;
		default:
			SYB_CommandFile[SettingCommandFileNumber].TitleMessage = SpecialCommandValue.TitleMessage;
			break;
		}
}
else {
		SYB_CommandFile[SettingCommandFileNumber].TitleMessage = SpecialCommandValue.TitleMessage;
}
 #else
	SYB_CommandFile[SettingCommandFileNumber].TitleMessage = SpecialCommandValue.TitleMessage;
 #endif
#else
	SYB_CommandFile[SettingCommandFileNumber].TitleMessage = SpecialCommandValue.TitleMessage;
#endif
}

/*************************************************************************
	module		:[原稿枚数のセット]
	function	:[
		1.設定された原稿枚数をコマンドファイルにセットする
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:
		SYB_CommandFile:
		SettingCommandFileNumber:セット中（確保している)コマンドファイル番号
	]
	condition	:[]
	comment		:[
		絶対にコマンドファイルを確保してからよびだしてね
		SettingCommandFilenumberに値が入っていないから
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/08/31]
	author		:[江口 ]
*************************************************************************/
void SetCommandPage(void)
{
	/* ポーリングの時も値をそのままセットしていいのやろか TBD */
	SYB_CommandFile[SettingCommandFileNumber].Page = (UWORD)SpecialCommandValue.Page;
}

/*************************************************************************
	module		:[部門管理コードのセット]
	function	:[
		1.登録中のコマンドファイルに入力された部門管理コードをセットする。
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:
		SYB_CommandFile:
		SettingCommandFileNumber:セット中（確保している)コマンドファイル番号
	]
	condition	:[]
	comment		:[絶対にコマンドファイルを確保してからよびだしてね]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口]
*************************************************************************/
#if (PRO_DEPARTMENT == ENABLE)
void SetCommandDepartCode(void)
{
	SYB_CommandFile[SettingCommandFileNumber].DepartmentCode = SpecialCommandValue.DepartmentCode;
}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[コマンドファイルに付加属性をセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		SYB_CommandFile:
		SettingCommandFileNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void	SetCommandAbility(void)
{
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	if (!CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_TTI_TX_AVAILABLE_ON) {
			SYB_CommandFile[SettingCommandFileNumber].Ability |= SYS_TTI_TX_AVAILABLE;
		}
		else {
			SYB_CommandFile[SettingCommandFileNumber].Ability &= ~SYS_TTI_TX_AVAILABLE;
		}
	}
}
#endif

/*************************************************************************
	module		:[コマンドファイルにＰＩＮ番号をセット]
	function	:[
		1.ＰＩＮアクセスモードが個人別ＰＩＮアクセス(PIN_ACCESS_MODE2)の時に
		  入力されるＰＩＮ番号をコマンドファイルにセットする。
	]
	return		:[なし]
	common		:[
		SYB_CommandFile:PIN_Number(コマンドＰＩＮ)
		SpecialCommandValue
		SettingCommandFileNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/09]
	author		:[江口]
*************************************************************************/
void SetCommandPinNumber(void)
{
#if (PRO_PIN_ACCESS == ENABLE)
	CMN_StringCopyNum(SYB_CommandFile[SettingCommandFileNumber].PIN_Number,
					  SpecialCommandValue.PIN_Number,
					  SYS_PIN_MAX);
#endif
}

/*************************************************************************
	module		:[メモリー送信可能かどうかしらべる]
	function	:[
		1.以下の３つの条件が全て成立してるか調べる。３つとも成立していたらメモリー送信可能とする
		,・インデックステーブルに空きページがある。
		,・６４Ｋ分（CCITT No1チャート約４枚分）の空きブロックがある。
		,・メモリーオーバーエラーは発生していない。

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[メモリーオーバーエラーでもメモリー残量は十分にある場合もあるが蓄積禁止とする]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/26]
	author		:[江口]
*************************************************************************/
UBYTE CheckMemoryTxEnable(void)
{
	if ((MEM_CountTotalEmptyPage() > 0)							/** インデックスに空きページがある */
	 && (MEM_CountTotalEmptyBlock() >= OPR_MEM_TX_STORE_BORDER)	/** CCITT　No.1チャート4枚蓄積できるだけの空きブロックあり */
	 && (CheckMemoryOver() == FALSE)) {							/** メモリーオーバーエラーは発生していない */
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[スキャナ送信可能チェック]
	function	:[
		1.スキャナ送信が可能かをチェックします
	]
	return		:[
		TRUE	:スキャナー送信可能
		FALSE	:スキャナー送信不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/13]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckScannerTxEnable(void)
{
#if (PRO_FBS == ENABLE)
	if (!(SYB_MaintenanceSwitch[MNT_SW_B4] & FBS_REALTIME_TX)) {	/* ＦＢＳからのリアルタイム送信不可能な時 */
		/* ブックからのスキャナ送信は、仕様で無くなったので、無条件にメモリー送信にします
		** 理由）リアルタイム送信時の停止／起動時にイチョウ同様、画ひずみが発生するが、
		** 　　　有効な対策方法が見つからないため
		*/
		if (CMN_CheckScanDocOnFeeder() == FALSE) {	/* FBSに原稿がｾｯﾄされている（ADFに原稿がｾｯﾄされていない）時 */
			return(FALSE);
		}
	}
	else {															/* ＦＢＳからのリアルタイム送信可能な時 */
		/* ブックからの送信（ＡＤＦに原稿がセットされていない）で、時刻指定されている場合か、
		** 送信中に送信予約をする場合は、無条件にメモリー送信にします
		** 注）ブックの送信予約は出来ないため
		*/
		if ((CMN_CheckScanDocOnFeeder() == FALSE)
		 && ((SpecialCommandValue.CommandTime != 0) || (CheckFaxComExecute() == TRUE))) {
			return(FALSE);
		}
	}
#endif

#if (PRO_CIPHER == ENABLE)
	/* 暗号化送信はメモリ送信でしか出来ません */
	if (SpecialCommandValue.CommandOption.Item == SYS_CIPHER_TX) {	/* 暗号化送信 */
		return(FALSE);
	}
#endif

	return(TRUE);
}

/*************************************************************************
	module		:[ポーリングが指定されているか調べる]
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
	date		:[1996/06/26]
	author		:[江口]
*************************************************************************/
UBYTE CheckPollingCommandInput(void)
{
	if ((SpecialCommandValue.CommandOption.Item == SYS_POLLING_RX)
	||	(SpecialCommandValue.CommandOption.Item == SYS_DB_POLLING_RX)
	||	(SpecialCommandValue.CommandOption.Item == SYS_SEQUENTIAL_POLLING)
	||	(SpecialCommandValue.CommandOption.Item == SYS_CONTINUOUS_POLLING)
	||	(SpecialCommandValue.CommandOption.Item == SYS_SELECT_POLLING_RX)) {	/* Ｆコードﾎﾟｰﾘﾝｸﾞ受信追加 1997/05/13  By T.Yamaguchi */
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[プログラムワンタッチのダイアル番号の取り出し]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetProgramDialToInputNumber(UBYTE prg_no)	/* ワンタッチ記号 */
{
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
	SetDialDataToDispBuffer(OPR_PROGRAM_EXECUTE, &SYB_ProgramOnetouch[prg_no].EntryData.Command, InputNumber.Buffer);
#else
	SetDialDataToDispBuffer(OPR_PROGRAM_EXECUTE, &SYB_ProgramOnetouch[prg_no], InputNumber.Buffer);
#endif
}

/*************************************************************************
	module		:[カーソル位置ダイヤル記号検査]
	function	:[
		1.入力前の値が、ダイヤル記号かどうかを調べます
	]
	return		:[
		TRUE	:入力前の値がダイヤル記号
		FALSE	:入力前の値がダイヤル記号以外
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/21]
	author		:[渡辺一章]
*************************************************************************/
UBYTE DialCharacterCheck(UBYTE *chk_buf, UWORD cursor_pos, UWORD write_pos)
{
	UBYTE	ret;

	ret = FALSE;

	if ((*chk_buf == '-') || (*chk_buf == '/') || (*chk_buf == '!')) {
		if (cursor_pos + 1 == write_pos) {
			ret = TRUE;
		}
	}
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* '*'とﾄｰﾝ'-!'切り替えのため SMuratec H.C.H 2003/10/22 */
	else if (*chk_buf == '*') {
		if (cursor_pos + 1 == write_pos) {
			ret = TRUE;
		}
	}
	else if (*chk_buf == '#') { /* '#'と'-!'切り替えのため SMuratec L.Z.W 2003/10/23 */
		if (cursor_pos + 1 == write_pos) {
			ret = TRUE;
		}
	}	
#endif

	return(ret);
}

#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[カーソル位置ダイヤル記号（ポーズ・トーン）検査]
	function	:[
		1.入力前の値が、ダイヤル記号（ポーズ・トーン）かどうかを調べます
	]
	return		:[
		TRUE	:入力前の値がダイヤル記号（ポーズ・トーン）
		FALSE	:入力前の値がダイヤル記号（ポーズ・トーン）以外
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
UBYTE DialCharacterCheck2(UBYTE *chk_buf, UWORD cursor_pos, UWORD write_pos)
{
	UBYTE	ret;

	ret = FALSE;

	if ((*chk_buf == '-') && (*(chk_buf + 1) == '/')) {		/* ダイヤル記号（ポーズ）*/
		if (cursor_pos + 2 == write_pos) {
			ret = TRUE;
		}
	}
	if ((*chk_buf == '-') && (*(chk_buf + 1) == '!')) {		/* ダイヤル記号（トーン）*/
		if (cursor_pos + 2 == write_pos) {
			ret = TRUE;
		}
	}

	return(ret);
}
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
/*************************************************************************
	module		:[連続ポーリングコマンド用データセット]
	function	:[
		1.登録中の連続ポーリングコマンド用データにセットする。
	]
	return		:[]
	common		:[
		SYS_ContinuousPolling.StartTime->指定時刻の基準からの積算秒
		SYS_ContinuousPolling.EndTime  ->指定時刻の基準からの積算秒
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/10/18]
	author		:[松隈]
*************************************************************************/
UBYTE SetContPollingCommandTime(void)
{
	if (SYB_ContinuousPolling.Status == SYS_CMD_EMPTY) {
		SYB_ContinuousPolling.Status = SYS_CMD_SETTING;
	}
	else {
		NackBuzzer();
		ReleaseCommandFileRequest = TRUE;
		return (OPR_END);
	}
	if (CheckFaxComExecute() == TRUE) { /* 通信中の場合 */
		if (PushStartTwiceFaxCom == 1) { /* スタートキー２かい押しの場合 */
			if (FaxComTxReserveOperation() == OPR_END) {/*STOP*/
				ReleaseCommandFileRequest = TRUE;
				SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
				return (OPR_END);
			}
		}
	}

	/*----------------------------------*/
	/** 入力された番号のチェックを行う	*/
	/*----------------------------------*/
	if (CheckCommandNumber() == NG) {/** 番号不良 */
		NackBuzzer();
		SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
		return (OPR_CONTINUE); /* オペレーション継続(再入力) */
	}

	/*---------------------------------*
	 * 部門管理オペレーション
	 *---------------------------------*/
#if defined(POPLAR_F)
	/* Nothing 1999/11/19 Y.Murata */
#else
 #if (PRO_DEPART_NEW_LIST == DISABLE)  /* ポプラＢ ＵＳＡは連続ﾎﾟｰﾘﾝｸﾞは部門管理しません added by thonda 1997/12/16 */
  #if (PRO_DEPARTMENT == ENABLE)
	if (CHK_DepartmentON()) { /* 部門管理ＯＮ */
		if (DepartmentCodeOperation() == NG) {
			ReleaseCommandFileRequest = TRUE;
			SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
			return (OPR_END);
		}
	}
  #endif
 #endif  /* #if (PRO_DEPART_NEW_LIST == DISABLE) */
#endif
	/*------------------------------------*/
	/** ＰＩＮ番号入力実行				  */
	/*------------------------------------*/
 #if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE2) { /* 個人別ＰＩＮの場合 */
		if (PinAccessOperation() == NG) { /* STOP */
			ReleaseCommandFileRequest = TRUE;
			SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
			return (OPR_END);
		}
	}
 #endif
/* 連続ポーリングコマンド用データにそれぞれの値を展開する */

	/* セットし直す場合があるのでクリアする */
	ClearContPollingData(&SYB_ContinuousPolling);

 #if (PRO_PIN_ACCESS == ENABLE)
	/* 登録時のPINアクセスモードをセット */
	SYB_ContinuousPolling.PIN_AccessMode = CHK_PIN_AccessMode();
 #endif

	SYB_ContinuousPolling.StartTime = SpecialCommandValue.ContPollingStartTime;
	SYB_ContinuousPolling.EndTime   = SpecialCommandValue.ContPollingEndTime;
 #if (PRO_DEPARTMENT == ENABLE)
	SYB_ContinuousPolling.DepartmentCode = SpecialCommandValue.DepartmentCode;
 #endif
 #if (PRO_PIN_ACCESS == ENABLE)
	SetDialNumber(&SYB_ContinuousPolling.DialNumber, SYB_ContinuousPolling.PIN_AccessMode);
 #else
	/* ＰＩＮ機能なしの時は、ＰＩＮアクセスモードは関係ないので、とりあえずＰＩＮアクセスしないを渡す */
	SetDialNumber(&SYB_ContinuousPolling.DialNumber, PIN_ACCESS_OFF);
 #endif

 #if (PRO_PIN_ACCESS == ENABLE)
	/* ＰＩＮ番号をセット(Mode2のときのみ値がはいる）	*/
	CMN_StringCopyNum(SYB_ContinuousPolling.PIN_AccessNumber, SpecialCommandValue.PIN_Number, SYS_PIN_MAX);
 #endif

	/*---------------------------------*
	 * メインにメッセージ送信
	 *---------------------------------*/
	OperationMessageToMain.Message = MSG_ENTER_COMMAND;
	SYB_ContinuousPolling.Status   = SYS_CMD_WAITING;
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
	ReleaseCommandFileRequest = TRUE;
	return (OPR_END);
}

/*************************************************************************
	module		:[連続ポーリングコマンドデータをクリア]
	function	:[
		1.コマンドデータを確保したときにステータス以外を初期化
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/10/29]
	author		:[松隈]
*************************************************************************/
void ClearContPollingData(struct SYS_ContinuousPollingData_t *cont_ptr)
{
	/* 開始時刻・終了時刻のクリア */
	cont_ptr->StartTime = 0x00000000UL;
	cont_ptr->EndTime   = 0x00000000UL;

	/* ダイアル番号のクリア */
	ClearDialNumber(&cont_ptr->DialNumber);

	/* ＰＩＮ番号のクリア */
 #if (PRO_PIN_ACCESS == ENABLE)
	ClearCommandPinNumberCP(cont_ptr);
	ClearDialPinNumber(&cont_ptr->DialNumber);
 #endif

	/* 部門管理コードのクリア */
 #if (PRO_DEPARTMENT == ENABLE)
	cont_ptr->DepartmentCode = 0xFFFF;
 #endif

	/* ＰＩＮアクセスモードの初期化 */
 #if (PRO_PIN_ACCESS == ENABLE)
	cont_ptr->PIN_AccessMode = 0;
 #endif
}

/*************************************************************************
	module		:[コマンドＰＩＮ番号をクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/10/29]
	author		:[松隈]
*************************************************************************/
void ClearCommandPinNumberCP(struct SYS_ContinuousPollingData_t *cont_ptr)
{
 #if (PRO_PIN_ACCESS == ENABLE)
	CMN_MemorySet(cont_ptr->PIN_AccessNumber, SYS_PIN_MAX, 0xFF);
 #endif
}

#endif	/* (PRO_CONTINUOUS_POLLING == ENABLE) */

#if (PRO_FBS == ENABLE)
/*************************************************************************
	module		:[ブック原稿サイズセット]
	function	:[
		1.コピー以外で、ブックから原稿を読み取る場合、読み取る原稿のサイズを設定します
	]
	return		:[
		OPR_CONTINUE	:コマンド入力継続
		OPR_END			:コマンド入力終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/31]
	author		:[渡辺一章]
*************************************************************************/
UBYTE BookDocumentSizeSet(UBYTE call_place, UBYTE last_key)
{
	/* ＡＤＦに原稿がセットされているか、原稿蓄積中は設定できません */
	if ((CMN_CheckDocumentOnFeeder() == TRUE) || (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {
		NackBuzzer();
		/* 待機状態から呼ばれた時は、何もしないでCommandOperation()を抜けます */
		if (CheckNoCommandData() == TRUE) {	/* 送信データ未入力の時 */
			return(OPR_END);
		}
		else {								/* 送信データ入力済みの時 */
			return(OPR_CONTINUE);
		}
	}

	/* 枚数指定オペレーションは、ＡＤＦからのみ有効です */
	if (SpecialCommandValue.Page != 0) {
		NackBuzzer();
		return(OPR_CONTINUE);
	}

 #if defined(USA)  /* modified by honda 1997/11/14 */
	if (last_key == BOOK_DOC_SIZE_KEY) {	/* 連続してブック原稿サイズキーが押された時 */
		switch (SCN_RegularDocumentSize) {
		case SYS_REGULAR_SIZE_LETTER:		/* レター縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_LEGAL;			/* リーガル縦 */
			break;
		case SYS_REGULAR_SIZE_LEGAL:		/* リーガル縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_HALFLETTER_R;	/* ハーフレター横 */
			break;
		case SYS_REGULAR_SIZE_HALFLETTER_R:	/* ハーフレター横 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B4;				/* Ｂ４縦 */
			break;
		case SYS_REGULAR_SIZE_B4:			/* Ｂ４縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_LETTER;			/* レター縦 */
			break;
		default:
			break;
		}
	}
	/* ブック原稿サイズキーが１回押されただけの時、
	** ・サイズが未設定の場合				→	サイズの初期値・次原稿ありをセットし、設定値を表示します
	** ・すでにサイズが設定されている場合	→	現在の設定値を表示します（サイズの変更は行いません）
	*/
	else {									/* ブック原稿サイズキーが１回押されただけの時 */
		if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_LETTER;	/* レター縦 */
			IsBookDocSizeSet = TRUE;						/* ブック原稿サイズが設定された */

			/* 手動送信では、ＡＤＦ・ＦＢＳのどちらかしか送信できない仕様なので、次原稿の設定はできません */
			if (call_place != OPR_TEL_OPE) {	/* 手動送信用の原稿サイズ設定でない時 */
				SYS_NextBookDocument = TRUE;	/* 次原稿をありにセット */
			}
		}
	}
 #elif defined(AUS)  /* POPLAR_B AUS bythonda1998/05/12 */
	if (last_key == BOOK_DOC_SIZE_KEY) {	/* 連続してブック原稿サイズキーが押された時 */
		switch (SCN_RegularDocumentSize) {
		case SYS_REGULAR_SIZE_A4:	/* A4縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B4;	/* B4縦 */
			break;
		case SYS_REGULAR_SIZE_B4:	/* B4縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A5R;	/* A5横 */
			break;
		case SYS_REGULAR_SIZE_A5R:	/* A5横 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B5R;	/* B5横 */
			break;
		case SYS_REGULAR_SIZE_B5R:	/* B5横 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_F4;	/* F4縦 *//* F4対応 */
			break;
		case SYS_REGULAR_SIZE_F4:	/* F4縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A4;	/* A4縦 */
			break;
		default:
			break;
		}
	}
	/* ブック原稿サイズキーが１回押されただけの時、
	** ・サイズが未設定の場合				→	サイズの初期値・次原稿ありをセットし、設定値を表示します
	** ・すでにサイズが設定されている場合	→	現在の設定値を表示します（サイズの変更は行いません）
	*/
	else {									/* ブック原稿サイズキーが１回押されただけの時 */
		if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A4;	/* A4縦 */
			IsBookDocSizeSet = TRUE;						/* ブック原稿サイズが設定された */

			/* 手動送信では、ＡＤＦ・ＦＢＳのどちらかしか送信できない仕様なので、次原稿の設定はできません */
			if (call_place != OPR_TEL_OPE) {	/* 手動送信用の原稿サイズ設定でない時 */
				SYS_NextBookDocument = TRUE;	/* 次原稿をありにセット */
			}
		}
	}
 #else  /* (USA),(AUS)以外 */
	if (last_key == BOOK_DOC_SIZE_KEY) {	/* 連続してブック原稿サイズキーが押された時 */
		switch (SCN_RegularDocumentSize) {
		case SYS_REGULAR_SIZE_A4:	/* A4縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B4;	/* B4縦 */
			break;
		case SYS_REGULAR_SIZE_B4:	/* B4縦 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A5R;	/* A5横 */
			break;
		case SYS_REGULAR_SIZE_A5R:	/* A5横 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B5R;	/* B5横 */
			break;
		case SYS_REGULAR_SIZE_B5R:	/* B5横 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A4;	/* A4縦 */
			break;
		default:
			break;
		}
	}
	/* ブック原稿サイズキーが１回押されただけの時、
	** ・サイズが未設定の場合				→	サイズの初期値・次原稿ありをセットし、設定値を表示します
	** ・すでにサイズが設定されている場合	→	現在の設定値を表示します（サイズの変更は行いません）
	*/
	else {									/* ブック原稿サイズキーが１回押されただけの時 */
		if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
			SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A4;	/* A4縦 */
			IsBookDocSizeSet = TRUE;						/* ブック原稿サイズが設定された */

			/* 手動送信では、ＡＤＦ・ＦＢＳのどちらかしか送信できない仕様なので、次原稿の設定はできません */
			if (call_place != OPR_TEL_OPE) {	/* 手動送信用の原稿サイズ設定でない時 */
				SYS_NextBookDocument = TRUE;	/* 次原稿をありにセット */
			}
		}
	}
 #endif

	DisplayStringHigh(0, D2W_SetBookTxDocumentSize);	/* "ｹﾞﾝｺｳ ｻｲｽﾞ ｾｯﾃｲ     " */
	DisplayBookDocumentData(OPR_CHG_BOOK_SIZE);

	return(OPR_CONTINUE);
}

/*************************************************************************
	module		:[ブック次原稿あり／なし設定]
	function	:[
		1.送信等で原稿蓄積時、次のブック原稿のあり／なしを設定します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/25]
	author		:[渡辺一章]
*************************************************************************/
void BookNextDocumentSet(UBYTE last_key, UBYTE is_display_enable)
{
	/* ＡＤＦに原稿がセットされている時か、ブック原稿サイズがセットされている時のみ次原稿の設定が可能です */
	if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
		if (CMN_CheckDocumentOnFeeder() == FALSE) {	/* ＡＤＦに原稿がセットされていない時 */
			NackBuzzer();
			return;
		}
		else {										/* ＡＤＦに原稿がセットされている時 */
			if (CMN_CheckFeederCommandEmpty() == FALSE) {	/* スキャナ送信予約・実行中の時 */
				NackBuzzer();
				return;
			}
		}
	}

	/* 原稿読み取り時、ミラーが読み取り準備の移動中は、下段で状態表示をしているために、
	** 次原稿の変更を行っても表示上の確認が出来ないので、変更を禁止します
	*/
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PREPARATION_ADF) {
		NackBuzzer();
		return;
	}

	/* 連続して次原稿キーが押された時は、次原稿のあり／なしを切り替えます */
	if (last_key == NEXT_DOC_KEY) {	/* 連続して次原稿キーが押された時 */
		SYS_NextBookDocument ^= TRUE;
	}

	/* 次原稿設定表示不可能な時は、UpdateLCD()の中で表示の更新を行っています */
	if (is_display_enable) {	/* 次原稿設定表示可能な時 */
		DisplayStringHigh(0, D2W_SetBookTxNextDocument);	/* "ｼﾞｹﾞﾝｺｳ ｾｯﾃｲ        " */
		DisplayBookDocumentData(OPR_CHG_NEXT_DOC);
	}
}

/*************************************************************************
	module		:[ブック原稿設定値表示]
	function	:[
		1.ブック原稿サイズと、次原稿のあり／なしを表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/25]
	author		:[渡辺一章]
*************************************************************************/
void DisplayBookDocumentData(UBYTE call_place)
{
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* 原稿サイズのワーディングをセット */
	if (IsBookDocSizeSet) {	/* ブック原稿サイズが設定済み（ＦＢＳに原稿をセット）の時 */
		switch (SCN_RegularDocumentSize) {
		case SYS_REGULAR_SIZE_A4:			/* A4縦 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A4);				/* "A4\0  " */
			break;
		case SYS_REGULAR_SIZE_B4:			/* B4縦 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_B4);				/* "B4\0  " */
			break;
		case SYS_REGULAR_SIZE_A5R:			/* A5横 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A5R);			/* "A5R\0 " */
			break;
		case SYS_REGULAR_SIZE_B5R:			/* B5横 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_B5R);			/* "B5R\0 " */
			break;
		case SYS_REGULAR_SIZE_LETTER:		/* レター縦 */							/* Ltr,Legal,Half-LtrR 追加 By S.Fukui Nov.15,1997 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_Letter);			/* "Ltr\0 " */
			break;
		case SYS_REGULAR_SIZE_LEGAL:		/* リーガル縦 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_Legal);			/* "Legl\0" */
			break;
		case SYS_REGULAR_SIZE_HALFLETTER_R:	/* ハーフレター横 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_HalfLetterR);	/* "HLtrR" */
			break;
		case SYS_REGULAR_SIZE_F4:			/* F4縦 */  /* POPLAR_B AUS bythonda1998/05/12 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_F4);	/* "F4" */
			break;
		default:
			break;
		}
	}
	else {					/* ＡＤＦに原稿がセットされている時 */
		switch(CMN_GetDocumentScanSize()) {
		case SYS_DOCUMENT_A4_SIZE:	/* A4 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A4);		/* "A4\0  " */
			break;
		case SYS_DOCUMENT_B4_SIZE:	/* B4 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_B4);		/* "B4\0  " */
			break;
		case SYS_DOCUMENT_A3_SIZE:	/* A3 */
			CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A3);		/* "A3\0  " */
			break;
		default:
			break;
		}
	}

	/* （仕様変更）原稿サイズ変更時は、次原稿の設定値を表示しない  by K.Watanabe 1997/09/12 */
	if (call_place == OPR_CHG_NEXT_DOC) {
		/* 次原稿のあり／なしをセット */
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/17 */
		if (SYS_NextBookDocument == TRUE) {
			CMN_StringCopy(&FunctionDisplayBufferLow[5], D2W_NextDocument);	/* "ｼﾞｹﾞﾝｺｳ" */
		}
 #else
		if (SYS_NextBookDocument == TRUE) {
			CMN_StringCopy(&FunctionDisplayBufferLow[5], D2W_NextDocument_Ari);		/* "次原稿あり     " */
		}
		else {
			CMN_StringCopy(&FunctionDisplayBufferLow[5], D2W_NextDocument_Nashi);	/* "次原稿なし     " */
		}
 #endif
	}

	/* 原稿サイズ・次原稿のあり／なしを表示 */
	ChildDisplayStringLow(FunctionDisplayBufferLow);
}
#endif	/* (PRO_FBS == ENABLE) */

/*************************************************************************
	module		:[一括送信のプログラムワンタッチ]
	function	:[
		1.
	]
	return		:[
		OPR_CONTINUE	:コマンド入力継続
		OPR_END			:コマンド入力終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/21]
	author		:[松隈]
*************************************************************************/
#if (PRO_BATCH_TX == ENABLE)
UBYTE ProgramOnetouchBatch(UBYTE prog_no)
{
	UBYTE	index_no;
	UBYTE	box_no;
	UBYTE	start_enable;

#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	box_no = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.BatchNumber;
#else
	box_no = SYB_ProgramOnetouch[prog_no].Option.OptionNumber.BatchNumber;
#endif

	start_enable = FALSE;

	/*-----------------------------------------*/
	/** 一括送信原稿が登録できるかどうか調べる */
	/*-----------------------------------------*/
	switch (CheckBatchTxFileStatus(box_no)) {
	case BATCH_BOX_NOT_ENTRY:	/** 未登録 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		break;
	case BATCH_BOX_STORING:		/** 蓄積中 */
	case BATCH_BOX_EXECUTE:		/** 実行中 */
	case BATCH_BOX_ERASED:		/** 消去中 */
	case BATCH_BOX_POWER_OFF:	/** 電源断検出 */
		NackBuzzer();
		break;
	case BATCH_BOX_EMPTY:		/** 未使用 */
 #if (0)	/* この文を下の処理にさしかえます 1997/11/08 Y.Matsukuma */
		/** インデックスを初期化する */
		CMN_WordMemorySet(SYB_BatchTxFile[box_no].IndexNo, SYS_BATCH_INDEX_MAX, SYS_BAT_DOC_EMPTY);
		start_enable = TRUE;
		break;
 #endif
		if (ExistPinNumberAtSelectedBox(box_no) == TRUE) {/*PINアクセスがMode1/Mode2でPIN番号が登録されている*/
			/** インデックスを初期化する */
			CMN_WordMemorySet(SYB_BatchTxFile[box_no].IndexNo , SYS_BATCH_INDEX_MAX , SYS_BAT_DOC_EMPTY);
			start_enable = TRUE;
		}
		else {
			NackBuzzer();
			OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
		}
		break;
	case BATCH_BOX_WAITING:		/** 予約中 */
		start_enable = TRUE;
		break;
	default:
		break;
	}

	if (start_enable == FALSE) {
		return(OPR_END);
	}

	/* メモリーオーバー・ジャムリカバーオペレーション等が起こっている時に、
	** 原稿読み取りを行うと問題があるので、チェックします
	** 注）メモリーオーバーオペレーションが起こっている場合、蓄積中のステータスが立ったままなので、
	** 　　CheckScanStartEnable()より後に行うと、エラー表示のみで処理を抜けてくれないので、
	** 　　ここでは先にチェックします
	*/
	/* Add By O.Kimoto 1999/07/19 */
	if (CheckScanDisableCondition() == TRUE) {
		NackBuzzer();
		ReleaseCommandFileRequest = TRUE;
		return(OPR_END);
	}

	/* 原稿読み取り可能かのチェック */
	if (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE) {
		/* 原稿読み取り不可能な時（ブック原稿サイズ未設定も含む）は、一度コマンド入力に戻ります */
		NackBuzzer();
		return(OPR_CONTINUE);
	}

	/* メモリーオーバーのチェック */
	if (CheckMemoryOver() == TRUE) {	/* メモリーオーバーの時 */
		/* 注）メモリーオーバーのエラーが発生していても、メモリーに十分な空き領域が
		** 　　存在する場合もありますが、蓄積は禁止します
		*/
		NackBuzzer();
		return(OPR_END);
	}

	for (index_no = 0; index_no < SYS_BATCH_INDEX_MAX; index_no++) {
		if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_EMPTY) {
			break;
		}
	}
	if (index_no >= SYS_BATCH_INDEX_MAX) {
		NackBuzzer();
		/*OPR_ChildErrorFlag = BATCH_DOCUMENT_FULL_ERROR;*/
		return(OPR_END);
	}

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/06 */
	/* シングルキーにプログラムワンタッチの値をセット */
	SetProgramToSingleKey(prog_no);
#endif

	/* 送信可能な場合 */
	if (SYB_BatchTxFile[box_no].Status == SYS_CMD_EMPTY) {/**初めて原稿を登録する場合 */
		/** 送信指定時刻をセット */
		SpecialCommandValue.CommandTime = 0x00000000UL;
		GetProgramTime(SYB_BatchTxFile[box_no].ProgramTime);
		CalculateProgramExecTime();
		SYB_BatchTxFile[box_no].ExecTime = SpecialCommandValue.CommandTime * 60;
	}

	/** ボックスの使用状況を蓄積中にセットする */
	SYB_BatchTxFile[box_no].Status = SYS_CMD_SETTING;		/* 蓄積中をセット */

#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SYB_ProgramOnetouch[prog_no].EntryData.Command.Status = SYS_CMD_SETTING;	/* セット中にする */
#else
	SYB_ProgramOnetouch[prog_no].Status = SYS_CMD_SETTING;	/* セット中にする */
#endif

	/** メインタスクに原稿蓄積起動のメッセージを送信 */
	OperationMessageToMain.Message = MSG_STORE_MEMORY_BATCH_TX_DOC;
	OperationMessageToMain.SubMessage1 = box_no;
	OperationMessageToMain.SubMessage2 = index_no;
	snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
	MainTaskExecWait();

	OPR_InputDialInfo &= ~PROGRAM_INPUT;	/* プログラムワンタッチ入力のクリア */
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
	IsTxOrScanStart = TRUE;	/* 送信・原稿読み取り開始 */
#endif
	return(OPR_END);
}
#endif	/* (PRO_BATCH_TX == ENABLE) */

#if (PRO_NEW_DIAL_OPR == ENABLE)
/*************************************************************************
	module		:[短縮ダイヤル登録検査]
	function	:[
		1.短縮ダイヤルに登録されているかを調べます
		2.ＰＩＮ番号が必要な時は、登録されているかを調べます
	]
	return		:[
		TRUE	:短縮が登録済み（ＰＩＮ番号登録済み）
		FALSE	:短縮未登録（ＰＩＮ番号未登録）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/12]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckRegistrationSpeedDial(UWORD data_top_pos, UWORD data_number)
{
	UWORD	speed_number;	/* 短縮番号		*/
	UBYTE	ret;			/* リターン値	*/

	ret = TRUE;

	if (data_number == 0xFFFF) {		/* 短縮番号有効桁数オーバーの時 */
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
		InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＳの下に移動 */
		ret = FALSE;
	}
	else if (data_number == 0xFFFE) {	/* 任意短縮が未登録の時 */
		/* 短縮と任意短縮を共通化させる都合上、この時点で任意短縮だけは登録状態がわかっています */
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
		InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＳの下に移動 */
		ret = FALSE;
	}
	else {								/* 短縮番号有効桁数以内の時 */
		if (CHK_UNI_OptionalSpeedDial() == 0) {	/* 通常の短縮の時 */
			speed_number = data_number + OPR_SPEED_DIAL_MIN;	/* 短縮番号を計算します */
			if ((speed_number < OPR_SPEED_DIAL_MIN) || (speed_number > SYS_SPEED_DIAL_MAX)) {	/* 有効範囲外の時 */
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
				InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＳの下に移動 */
				ret = FALSE;
			}
		}
#if (0)	/* 任意短縮では、有効桁数以内の番号は全て登録できるので、有効範囲内のチェックは必要ありません */
//		else {									/* 任意短縮の時 */
//			speed_number = GetRecordFromNumber(data_number);	/* 短縮番号を取得します */
//			if (speed_number > OPR_OPTIONAL_SPEED_MAX) {	/* 有効範囲外の時 */
//				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
//				InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＳの下に移動 */
//				ret = FALSE;
//			}
//		}
#endif

		if (ret == TRUE) {	/* 有効範囲内の時 */
			/* 短縮の登録状態を調べます */
			if (CheckSpeedStoreStatus((UBYTE)data_number) == NG) {	/* 未登録の時 */
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
				InputNumber.CursorPosition = data_top_pos;		/* カーソル位置をＳの下に移動 */
				ret = FALSE;
			}
			else {													/* 登録済みの時 */
				/* ＰＩＮ番号が必要な時、登録状態を調べます */
				if ((InputNumber.PIN_NumberCheck == YES) && (CheckSpeedPinNumberStore((UBYTE)data_number) == FALSE)) {
					/* ＰＩＮ番号が未登録の時 */
					OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
					InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＳの下に移動 */
					ret = FALSE;
				}
			}
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[グループダイヤル登録検査]
	function	:[
		1.ワンタッチ・短縮に、指定のグループが登録されているかを調べます
	]
	return		:[
		TRUE	:グループが登録済み
		FALSE	:グループ未登録
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/02]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckRegistrationGroupDial(UWORD data_top_pos, UWORD data_number)
{
	UBYTE	ret;	/* リターン値	*/

	ret = TRUE;

	if (data_number == 0xFFFF) {	/* グループ番号有効桁数オーバーの時 */
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
		InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＧの下に移動 */
		ret = FALSE;
	}
	else {							/* グループ番号有効桁数以内の時 */
		if (data_number > SYS_GROUP_NUMBER_MAX) {	/* 有効範囲外の時 */
			OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
			InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＧの下に移動 */
			ret = FALSE;
		}
		else {										/* 有効範囲内の時 */
			/* グループの登録状態を調べます */
			if (CheckGroupDialStoreStatus((UBYTE)data_number) == 0) {	/* 未登録の時 */
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
				InputNumber.CursorPosition = data_top_pos;		/* カーソル位置をＧの下に移動 */
				ret = FALSE;
			}
			else {												/* 登録済みの時 */
				/* ＰＩＮ番号が必要な時、登録状態を調べます */
				if ((InputNumber.PIN_NumberCheck == YES) && (CheckGroupPinNumberStore((UBYTE)data_number) == FALSE)) {
					/* ＰＩＮ番号が未登録のメンバーを含む時 */
					OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;	/* "PIN ﾊﾞﾝｺﾞｳ ｶﾞ ｱﾘﾏｾﾝ " */
					InputNumber.CursorPosition = data_top_pos;	/* カーソル位置をＧの下に移動 */
				}
			}
		}
	}

	return(ret);
}
#endif	/* (PRO_NEW_DIAL_OPR == ENABLE) */

#if (PRO_NEW_DIAL_OPR2 == ENABLE)
/*************************************************************************
	module		:[直接ダイヤル件数オーバー検査]
	function	:[
		1.直接ダイヤルが最大件数未満かを調べます
	]
	return		:[
		TRUE	:直接ダイヤル最大件数未満
		FALSE	:直接ダイヤル最大件数以上
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/28]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckDirectDialCount(void)
{
	UWORD	buf_count;		/* ダイヤルデータ位置	*/
	UBYTE	direct_count;	/* 直接ダイヤル件数		*/
	UBYTE	ret;			/* リターン値			*/

	buf_count = 0;
	direct_count = 0;
	ret = TRUE;

	/* 現在入力されている直接ダイヤルの件数を計算します */
	while (buf_count < InputNumber.WritePosition) {	/* 入力されているデータを全てチェックするまで */
		if (CheckInputNumberCode(InputNumber.Buffer[buf_count]) == FALSE) {	/* 直接ダイヤルの時 */
			direct_count++;
		}

		/* 次のダイヤルデータまで進めます */
		buf_count += GetStringGapPoint(&InputNumber.Buffer[buf_count], ',');
		buf_count++;
	}

	if (direct_count >= SYS_COM_DIRECT_DIAL_MAX) {	/* 直接ダイヤルが、最大件数入力されている時 */
		ret = FALSE;
	}

	return(ret);
}

/*************************************************************************
	module		:[直接ダイヤル桁数オーバー検査]
	function	:[
		1.データ入力した後、直接ダイヤルが有効桁数を超えないかを調べます
	]
	return		:[
		TRUE	:有効桁数内
		FALSE	:有効桁数オーバー
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/20]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckDirectDialLength(UBYTE direct_dial_len, UBYTE data_len)
{
	UBYTE	ret;	/* リターン値	*/

	ret = TRUE;

	if ((direct_dial_len + data_len) > ((SYS_DIRECT_DIAL_MAX - 1) * 2)) {
		/* データ入力後、直接ダイヤルが４０桁を超えてしまう時 */
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
		ret = FALSE;
	}

	return(ret);
}

/*************************************************************************
	module		:[アスタリスクコードＰＩＮ記号変換]
	function	:[
		1.＊を入力位置に応じてＰＩＮ記号に変換します
	]
	return		:[＊・ＰＩＮ記号]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/22]
	author		:[渡辺一章]
*************************************************************************/
void ChangeAsteriskKeyCode(UBYTE key)
{
	UWORD	i;				/* ループ変数						*/
	UBYTE	is_pin_mark;	/* 押された'*'がＰＩＮ記号かどうか	*/

#if (PRO_MULTI_TTI == DISABLE) /* By H.Fujimura 1999/03/29 */
	/* ＰＩＮ番号が不必要な時は、関係ありません */
	if (InputNumber.PIN_NumberCheck == NO) {
		return;
	}
#endif

	/* 直接ダイヤルの先頭が'*'の時に先頭にデータが挿入された時
	** 注）直接ダイヤルの先頭の'*'だけはPIN記号に変換していないので、その前にデータを挿入されると、
	** 　　PIN記号に変換する必要があります
	*/
	if ((InputNumber.Buffer[InputNumber.CursorPosition] == TEN_AST_KEY)
	 && ((InputNumber.CursorPosition == 1)
	  || ((InputNumber.CursorPosition >= 2) && (InputNumber.Buffer[InputNumber.CursorPosition - 2] == ',')))) {
		/* カーソル位置の'*'を、ＰＩＮ記号に変換します */
		InputNumber.Buffer[InputNumber.CursorPosition] = OPR_PIN_MARK;

		/* カーソル位置より後ろにPIN記号が入力されていた場合は、'*'に戻します */
		for (i = InputNumber.CursorPosition + 1; i < InputNumber.WritePosition; i++) {	/* 入力バッファの最後まで */
			if (InputNumber.Buffer[i] == ',') {	/* 検索位置が同報記号になった時 */
				break;
			}

			if (InputNumber.Buffer[i] == OPR_PIN_MARK) {	/* カーソル位置以降にPIN記号があった時 */
				InputNumber.Buffer[i] = TEN_AST_KEY;	/* '*'に戻します */
				break;
			}
		}
	}
	/* ＊キーが押された時 */
	else if (key == TEN_AST_KEY) {
		/* 注）実際にはありえませんが、元々、直接ダイヤルの先頭の'*'だけはPIN記号に
		** 　　変換していなかったので、合わせておきます
		*/
		if ((InputNumber.CursorPosition != 1)
		 && ((InputNumber.CursorPosition >= 2) && (InputNumber.Buffer[InputNumber.CursorPosition - 2] != ','))) {
			is_pin_mark = TRUE;

			/* カーソル位置より前にＰＩＮ記号があるかを調べます */
			for (i = InputNumber.CursorPosition - 2; i > 0; i--) {	/* 入力したﾃﾞｰﾀの前から入力ﾊﾞｯﾌｧの先頭まで */
				if (InputNumber.Buffer[i] == ',') {	/* 検索位置が同報記号になった時 */
					break;
				}

				if (InputNumber.Buffer[i] == OPR_PIN_MARK) {	/* カーソル位置より前にＰＩＮ記号がある時 */
					is_pin_mark = FALSE;
					break;
				}
			}

			if (is_pin_mark) {	/* 入力する'*'がＰＩＮ記号の時 */
				/* 入力した'*'をＰＩＮ記号に変換します */
				InputNumber.Buffer[InputNumber.CursorPosition - 1] = OPR_PIN_MARK;

				/* カーソル位置より後ろにＰＩＮ記号が入力されているかを調べ、入力されていたら'*'に戻します */
				for (i = InputNumber.CursorPosition; i < InputNumber.WritePosition; i++) {	/* 入力バッファの最後まで */
					if (InputNumber.Buffer[i] == ',') {	/* 検索位置が同報記号になった時 */
						break;
					}

					if (InputNumber.Buffer[i] == OPR_PIN_MARK) {	/* カーソル位置以降にＰＩＮ記号がある時 */
						InputNumber.Buffer[i] = TEN_AST_KEY;	/* '*'に変換 */
						break;
					}
				}
			}
		}
	}
}
#endif	/* (PRO_NEW_DIAL_OPR2 == ENABLE) */

/*************************************************************************
	module		:[ワンタッチ・短縮相手先名表示]
	function	:[
		1.指定されたワンタッチ・短縮の相手先名が登録されていれば表示し、
		　未登録の時は、ダイヤル番号を表示します
	]
	return		:[相手先名・ダイヤル番号桁数]
	common		:[]
	condition	:[
		この関数は、既に登録されているデータに対してのみ有効です
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/31]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_DIAL_NAME_DISP == ENABLE)
void DisplayDialName(UBYTE data_kind, UWORD data_number)
{
#if (0)	/* by K.Watanabe 1998/05/19 */
//	UBYTE	speed_number;	/* 短縮番号				*/
#endif
	UWORD	speed_number;	/* 短縮番号				*/
	UBYTE	is_err_display;	/* エラー表示を行ったか	*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/17 */
	struct SYS_SpeedDialData_t	*dial_data_ptr;	/* ワンタッチ・短縮ダイヤルデータのポインター */
	UBYTE	kei_pos;
#endif		/* End of (defined (KEISATSU)) */

	is_err_display = FALSE;

	/* 表示用バッファの初期化 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	if (data_kind & OPR_CURSOR_SPEED) {	/* カーソルが短縮の所にある時 */
		/* 短縮番号桁数オーバー・任意短縮未登録チェック */
		if ((data_number == 0xFFFF) || (data_number == 0xFFFE)) {	/* 短縮番号有効桁数オーバー・任意短縮未登録の時 */
			CMN_StringCopy(FunctionDisplayBufferHigh, D2W_InputSpeedDialNumber);	/* "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
			is_err_display = TRUE;
		}
		else {							/* 短縮番号有効桁数以内の時 */
			/* 短縮番号有効範囲内チェック */
			if (CHK_UNI_OptionalSpeedDial() == 0) {	/* 通常の短縮の時 */
				speed_number = data_number + OPR_SPEED_DIAL_MIN;	/* 短縮番号を計算します */
				if ((speed_number < OPR_SPEED_DIAL_MIN) || (speed_number > SYS_SPEED_DIAL_MAX)) {	/* 有効範囲外の時 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_InputSpeedDialNumber);	/* "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
					is_err_display = TRUE;
				}
			}
#if (0)	/* 有効桁数以内の番号は全て登録できるので、有効範囲内のチェックは行いません */
//			else {									/* 任意短縮の時 */
//				speed_number = GetRecordFromNumber(data_number);	/* 短縮番号を取得します */
//				if (speed_number > OPR_OPTIONAL_SPEED_MAX) {	/* 有効範囲外の時 */
//					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_InputSpeedDialNumber);	/* "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
//					is_err_display = TRUE;
//				}
//			}
#endif

			/* 短縮登録チェック */
			if ((!is_err_display) && (CheckSpeedStoreStatus((UBYTE)data_number) == NG)) {	/* 未登録の時 */
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_InputSpeedDialNumber);	/* "ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
				is_err_display = TRUE;
			}
		}
	}

	if (!is_err_display) {	/* エラー未表示の時 */
		/* 表示用バッファに相手先名・番号をセットする */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/05 */
		/* 警察設定表示 */
		if (data_kind == OPR_CURSOR_ONETOUCH) {	/* ワンタッチの相手先名を表示する時 */
			dial_data_ptr = &SYB_OnetouchDial[data_number];
		}
		else {									/* 短縮の相手先名を表示する時 */
			dial_data_ptr = &SYB_SpeedDial[data_number];
		}

		if (dial_data_ptr->Name[0] != NULL) {	/* 相手先名が登録されている時 */
			SetOnetouchSpeedDialName(FunctionDisplayBufferHigh, data_kind, data_number);
		}
		else{
			
			/* 警察FAX DVT_ID13 Modify by SMuratec K.W.Q 2005/07/05 */
		 	kei_pos = 0;
			if (dial_data_ptr->Keisatsu & SYS_KEISATSU_KEIDEN){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｹ", 1);
				kei_pos++;
			}
			else if (dial_data_ptr->Keisatsu & SYS_KEISATSU_KANYU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｶ", 1);
				kei_pos++;
			}

			if (dial_data_ptr->Keisatsu & SYS_KEISATSU_ISSEI){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｲ", 1);
				kei_pos++;
			}
			else if (dial_data_ptr->Keisatsu & SYS_KEISATSU_KOBETSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｺ", 1);
				kei_pos++;
			}

			if (dial_data_ptr->Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "S", 1);
				kei_pos++;
			}
			else if (dial_data_ptr->Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "N", 1);
				kei_pos++;
			}

			if (dial_data_ptr->Keisatsu & SYS_KEISATSU_KYOTSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｷ", 1);
				kei_pos++;
			}
			else if (dial_data_ptr->Keisatsu & SYS_KEISATSU_SENYO){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[kei_pos], "ｾ", 1);
				kei_pos++;
			}
			
			SetOnetouchSpeedDialName(&FunctionDisplayBufferHigh[kei_pos], data_kind, data_number);
		}
#else
		SetOnetouchSpeedDialName(FunctionDisplayBufferHigh, data_kind, data_number);
#endif		/* End of (defined (KEISATSU)) */
	}
	
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(FunctionDisplayBufferHigh);
#endif
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}
#endif	/* (PRO_DIAL_NAME_DISP == ENABLE) */

/*************************************************************************
	module		:[ライフモニタクリアオペレーション]
	function	:[ライフモニタクリアするためのパスコード入力
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/06/01]
	author		:[本多]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
UBYTE LifeMonitorPasscodeOperation(void)
{
	/***********************************************************************
	 * ライフモニタクリアパスコードが０以外のときパスコード入力を促します
	 * パスコードが一致すれば、ライフモニタクリアオペレーションを続けます
	 * 間違ったパスコードを入力、ストップキーを入力、１分間キー入力なし
	 * の場合はオペレーション終了し、ライフモニタクリアオペレーションは実行しません
	 ***********************************************************************/

	UWORD	passcode;
	passcode = 0;

	/** 古いパスコードを入力させる */
	DisplayStringHigh(0, D2W_SF_EnterServiceCode);  /* "ﾗｲﾌﾓﾆﾀﾊﾟｽｺｰﾄﾞｦ ﾄﾞｳｿﾞ" */
	if ((passcode = EnterPassCode(SYB_LifeMonitorPasscode, CHK_PASS_CODE_ENTER, D2W_InputPasscode)) == 0xFFFF) {
		/* 入力終了 */
		return(NG);
	}

	/** パスコードチェックを行う */
	if (passcode != SYB_LifeMonitorPasscode) { /** パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		return(NG);
	}

	return(OK);
}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN) */


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/16 Y.Matsukuma */
/*************************************************************************
	module		:[ミノルタワンタッチテストプリント]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/07/16]
	author		:[松隈]
*************************************************************************/
void	MinoltaOnetouchPrint(UBYTE key)
{
	UWORD ptn;
	UWORD pages;
	UBYTE buffer[4];
	UBYTE i;

	ptn = 0;
	pages = 0;

	if (CMN_CheckPrinting()	== TRUE) {	/* テストプリント中 */
		OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
		NackBuzzer();
		return;
	}

	for(i = 0; i < 4; i++) {
		buffer[i] = 0;
	}

	ptn = (UWORD)(key - 0x41);
	CMN_BCD_ToASC_StringNum(&buffer[0], &SYB_OnetouchDial[ptn].Dial[0], 4);

	if (buffer[3] != NULL) {
		pages += (UWORD)(buffer[0] - 0x30) * (UWORD)1000;
		pages += (UWORD)(buffer[1] - 0x30) * (UWORD)100;
		pages += (UWORD)(buffer[2] - 0x30) * (UWORD)10;
		pages += (UWORD)(buffer[3] - 0x30) * (UWORD)1;
	}
	else if (buffer[2] != NULL) {
		pages += (UWORD)(buffer[0] - 0x30) * (UWORD)100;
		pages += (UWORD)(buffer[1] - 0x30) * (UWORD)10;
		pages += (UWORD)(buffer[2] - 0x30) * (UWORD)1;
	}
	else if (buffer[1] != NULL) {
		pages += (UWORD)(buffer[0] - 0x30) * (UWORD)10;
		pages += (UWORD)(buffer[1] - 0x30) * (UWORD)1;
	}
	else if (buffer[0] != 0xFF) {
		pages += (UWORD)(buffer[0] - 0x30) * (UWORD)1;
	}

	ptn++;
	CMN_SetMinoltaTestFuncData(ptn, pages, 0);

}



/*************************************************************************
	module		:[ミノルタプログラムプリント基本値]
	function	:[
		1.Ｐ１．Ｐ２．Ｐ３のみ基本値を設定しておく。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/08/05]
	author		:[松隈]
*************************************************************************/
UBYTE	MinoltaStandardPG(UBYTE key, UBYTE program)
{
	switch (key) {
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1998/10/06 Y.Matsukuma */
	case PROGRAM_P01:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_P_KEY);
			return(TRUE);
		}
		break;
	case PROGRAM_P02:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_I_KEY);
			return(TRUE);
		}
		break;
	case PROGRAM_P03:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_R_KEY);
			return(TRUE);
		}
		break;
#else
	case ONETOUCH_73_KEY:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_16_KEY);
			return(TRUE);
		}
		break;
	case ONETOUCH_74_KEY:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_09_KEY);
			return(TRUE);
		}
		break;
	case ONETOUCH_75_KEY:
		if (CheckProgramStoreStatus(program) == OPR_PRG_NO_STORED) {
			OPR_MinoltaPatternItem 	= OPR_MINOLTA_PROGRAM;	/* 1998/08/31 Y.Matsukuma */
			OPR_MinoltaDisplayCheck = program + 1;
			MinoltaTestPatternPrint(ONETOUCH_18_KEY);
			return(TRUE);
		}
		break;
#endif
	default:
		return(FALSE);
		break;
	}
	return(FALSE);
}

#endif

#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
/*************************************************************************
	module		:[シンガポール市場調査ＲＯＭ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/07/25]
	author		:[王 慎]
*************************************************************************/
void SetSgpDialNumber(void)
{
	UBYTE	asc_buff[OPR_DIRECT_DIAL_BUFFER_MAX];
	UWORD	length;				/* コンマ～コンマまでのデータ数 */
	UWORD	dial_length;		/* ダイアル番号の桁数 */
	UWORD	cursor_position;	/* 入力位置 */

	length = 0;
	cursor_position = 0;
	
	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {
		SYS_SgpDialBuffer[i] = 0xFF;
	}
	/* コマンド入力バッファの最後まで */
	while ((InputNumber.Buffer[cursor_position] != ' ') && (InputNumber.Buffer[cursor_position] != NULL)) {
		/* 直接ダイヤル */
		length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
		dial_length = length;
		CMN_MemorySet(asc_buff, OPR_DIRECT_DIAL_BUFFER_MAX, NULL);
		CMN_StringCopyNum(asc_buff, &InputNumber.Buffer[cursor_position], dial_length);
		CMN_ASC_ToBCD_String(SYS_SgpDialBuffer, asc_buff);
		cursor_position += length;
	}
}
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[指定されたダイアルをクリアする]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void ClearDialNumber2(UBYTE *Direct, UBYTE *Onetouch, UBYTE *Speed, UDWORD *Group)
{
	UWORD	i;	/* ﾙｰﾌﾟ変数 */

	if (Direct != NULL) {
		Direct[0] = 0xF0;
	}
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		Onetouch[i] = 0;
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		Speed[i] = 0;
	}
	*Group = 0;
}

/*************************************************************************
	module		:[電話番号を指定されたダイアルにセットする]
	function	:[
		1.指定されたコマンドファイルに入力されたダイアル番号をセットする。
		2.セットするダイアル番号がダイレクトダイアルの場合でかつＰＩＮアクセスモードが
		　相手先別ＰＩＮの場合、ＰＩＮ番号のセットも行う
	]
	return		:[なし]
	common		:[InputNumber]
	condition	:[]
	comment		:[
		ダイアル番号が正しいことを確認してからコマンドファイルにセットすること

		連続ポーリングでも共通で使用できるように、引数を変更
		void SetDialNumber(struct SYS_CommandData_t *com_ptr)
		void SetDialNumberCP(struct SYS_ContinuousPollingData_t *cont_ptr)

										↓

		void SetDialNumber(struct SYS_DialData_t *dial_ptr, UBYTE pin_access_mode)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void SetDialNumber2(UBYTE *Direct, UBYTE *Onetouch, UBYTE *Speed, UDWORD *Group)
{
	UBYTE	asc_buff[OPR_DIRECT_DIAL_BUFFER_MAX];
	UWORD	length;				/* コンマ～コンマまでのデータ数 */
	UWORD	dial_data;			/* ダイアル番号 */
	UWORD	dial_length;		/* ダイアル番号の桁数 */
	UWORD	cursor_position;	/* 入力位置 */

	length = 0;
	cursor_position = 0;

	/* コマンド入力バッファの最後まで */
	while ((InputNumber.Buffer[cursor_position] != ' ') && (InputNumber.Buffer[cursor_position] != NULL)) {

		/*--------------------------------------*/
		/* 宛先の種類ごとにデータをセットします */
		/*--------------------------------------*/
		switch (InputNumber.Buffer[cursor_position]) {
		case ',':						/* 同報の区切り記号 */
			cursor_position++;
			break;
		case OPR_ONETOUCH_MARK_LEFT:	/* ワンタッチ記号の左かっこ */
			cursor_position++;	/* ワンタッチの番号に進める（[01]の'0'の位置） */
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], OPR_ONETOUCH_NUMBER_FIGURE);
			CMN_SetBitAssign(Onetouch, (UBYTE)(dial_data - 1));
			cursor_position += (OPR_ONETOUCH_NUMBER_FIGURE + 1);	/* ワンタッチの次に進める（[01]の']'の後) */
			break;
		case OPR_SPEED_MARK:			/* 短縮記号 */
			cursor_position++;	/* 短縮の番号に進める（S1の'1'の位置 )*/
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], (UBYTE)length);
			if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
				dial_data--;
			}
			else{		/* 任意短縮の時 */
				dial_data	= (UBYTE)SetOptionalSpeedStatus( dial_data );	/* ダイヤルレコードオフセット取得 */
			}
			CMN_SetBitAssign(Speed, (UBYTE)dial_data);
			cursor_position += length;	/* 短縮の次に進める（S1の'1'の後 )*/
			break;
		case OPR_GROUP_MARK:			/* グループ記号 */
			cursor_position++;	/* グループの番号に進める（G1の'1'の位置 )*/
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
			dial_data = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[cursor_position], (UBYTE)length);
			if (dial_data == 0) {	/* グループ０が指定されている時 */
				*Group = 0xffffffff;
			}
			else {
				CMN_SetLongBitAssign(Group, (UBYTE)(dial_data - 1));
			}
			cursor_position += length;	/* グループの次に進める（G1の'1'の後 )*/
			break;
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/07/10 Y.Matsukuma */
		case OPR_ONETOUCH_MARK:			/* ワンタッチ記号の「Ｕ」 */
			cursor_position++;	/* ワンタッチの番号に進める（U1の'1'の位置 )*/
			dial_data = ChangeOnetouchCode((UWORD)cursor_position); /* ビットアサインのため、ワンタッチコードを数字に置き換える */
			CMN_SetBitAssign(Onetouch, (UBYTE)dial_data);
			cursor_position += OPR_ONETOUCH_NUMBER_FIGURE;	/* ワンタッチの次に進める（U1の'1'の後 )*/
			break;
 #endif
		default:
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ANZU_Lの場合、アルファベットのワンタッチをここで処理する。1997/07/10 Y.Matsukuma */
			if ((ONETOUCH_A_KEY <= InputNumber.Buffer[cursor_position] 
								&& InputNumber.Buffer[cursor_position] <= ONETOUCH_Z_KEY) 
				|| (ONETOUCH_a_KEY <= InputNumber.Buffer[cursor_position] 
								&& InputNumber.Buffer[cursor_position] <= ONETOUCH_z_KEY)) {
				dial_data = ChangeOnetouchCode((UWORD)cursor_position); /* ビットアサインのため、ワンタッチコードを数字に置き換える */
				CMN_SetBitAssign(Onetouch, (UBYTE)dial_data);
				cursor_position += OPR_ONETOUCH_NUMBER_FIGURE;	/* ワンタッチの次に進める（'A'の後 )*/
				break;
			}
 #endif
			/* 直接ダイヤル */
			length = GetStringGapPoint(&InputNumber.Buffer[cursor_position], ',');
			if (Direct != NULL) {
				dial_length = length;
				CMN_MemorySet(asc_buff, OPR_DIRECT_DIAL_BUFFER_MAX, NULL);
				CMN_StringCopyNum(asc_buff, &InputNumber.Buffer[cursor_position], dial_length);
				CMN_ASC_ToBCD_String(Direct, asc_buff);
			}
			cursor_position += length;
			break;
		}
	}
}
#endif	/* (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) */


/*************************************************************************
	module		:[ワープ用転送エラー時のページプリントのカウンタセット]
	function	:[
		1.指定されたコマンドファイルのワープ用ページカウンターを初期化
	]
	return		:[なし]
	common		:[SYB_CommandFile[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/11/25]
	author		:[木元修]
*************************************************************************/
void SetRxDocTransferPageCount(void)
{
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/09/30 By M.Kuwahara */
	/** 転送ｴﾗｰ時のﾍﾟｰｼﾞﾌﾟﾘﾝﾄのｶｳﾝﾀをｸﾘｱしておく */
	SYB_CommandFile[SettingCommandFileNumber].PrintPage = 1;
#endif
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/25 */
void SetCommandKeisatsu(void)
{
	if (CheckIsKanyuLine()) {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Line = SYS_LINE_KANYU;
	}
	else {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Line = SYS_LINE_KEIDEN;
	}

	if (CheckIsScrambleOFF()) {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Scramble = FALSE;
	}
	else {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Scramble = TRUE;
	}

	if (CheckIsSenyou()) {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Senyo = TRUE;
	}
	else {
		SYB_CommandKeisatsu[SettingCommandFileNumber].Senyo = FALSE;
	}

}

#endif		/* End of (defined (KEISATSU)) */
