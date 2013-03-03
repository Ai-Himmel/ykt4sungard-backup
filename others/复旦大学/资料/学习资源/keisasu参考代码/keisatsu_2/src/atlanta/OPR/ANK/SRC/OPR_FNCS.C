/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_FNCS.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 機器設定の小関数
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif
#if (PRO_CIPHER == ENABLE)
#include	"\src\atlanta\scd\ext_v\cph_data.h"	/* 98/04/16 Add By T.Fukumoto */
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/10/15 */
 #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\define\prt_def.h"
#include "\src\atlanta\prt\lv_therm\define\prt_pro.h"
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
 #else
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
 #endif
#endif

/* Prototype
void	PrintCommandList(void);
void	PrintStoredDocument(void);
#if (0)	/ この関数は必要ないので、削除します by K.Watanabe 1998/05/27 /
//UBYTE	CheckPollingCommand(UBYTE);
#endif
#if (PRO_CIPHER == ENABLE)
UBYTE	SetCipherTxDocDecipherPara(UBYTE *);
#endif
void	SetJournalOnOff(void);
void	PrintJournalList(void);
void	SetCommunicationResult(void);
void	PrintGroupList(void);
void	SetMessageOnOff(void);
void	SetMessageDataMode(void);
UBYTE	CoverPageMessageInput(void);
void	PrintMessageList(void);
void	SetNumberOfPages(void);
#if (PRO_PC_PRINT == ENABLE)
void	ResetPrinterBoard(void);
#endif
#if (PRO_DAILY_REPORT == ENABLE)
void	PrintDailyReport(void);
#endif
*/

/*************************************************************************
	module		:[通信予約リスト．コール。]
	function	:[
		1.通信予約リストをコールする。
		2.対象となるものは予約中、実行中、実行待ちのもの
		3.一括送信の予約状況は本リストでは参照できない
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PRG - F1]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintCommandList(void)
{
	/* 通信予約の有無をチェックする */
	if ((CheckReservedCommandExist() == TRUE)/** 通信予約あり */
	||	(CheckExecuteCommandExist() == TRUE)) {
		FinalListPrintOperation(LST_RESERVECMD_LIST); /** メインにリスト起動メッセージ送信*/
	}
#if (PRO_BATCH_TX_RESERVE_LIST == ENABLE) && (PRO_BATCH_TX == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	else if ((CheckReservedBatchExist() == TRUE)/** 一括送信予約あり */
		 || (CheckExecuteBatchExist() == TRUE)) {
		FinalListPrintOperation(LST_RESERVECMD_LIST); /** メインにリスト起動メッセージ送信*/
	}
#endif
	else { /** 通信予約なし */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_COMMAND_ERROR;
	}
}

/*************************************************************************
	module		:[予約原稿プリント機能]
	function	:[
		1.メモリー送信予約されているものについて予約原稿のプリントを実行する
	]
	return		:[なし]
	common		:[
		SYB_CommandFile
		OPR_ChildErrorFlag
	]
	condition	:[]
	comment		:[PRG-F2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/28]
	author		:[江口,渡辺一章]
*************************************************************************/
void PrintStoredDocument(void)
{
	UWORD	com_file;		/* 予約番号 */
	struct SYS_CommandData_t	*com_ptr;
#if (PRO_CIPHER == ENABLE)
	UBYTE	is_decipher_on;	/* 暗号化解除ＯＮ */
#endif

	/* 上段の表示 */
	DisplayStringHigh(0, D2W_PrintStoredDocument);	/* "ﾖﾔｸｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ      " */

	/** 予約ファイル番号の入力  */
	if (NumberInput(OPR_COMMAND_NUMBER_INPUT) == OK) {
		com_file = CharacterInputToNumber();	/* 入力された文字列を数値に変換 */
		com_ptr = &SYB_CommandFile[com_file];	/* コマンドファイルのアドレスをセット */

		if ((com_ptr->Status == SYS_CMD_WAITING) || (com_ptr->Status == SYS_CMD_EXECUTE)) {
			/** 入力されたコマンド番号に対応するコマンドが存在する時 */
#if (0)	/* by K.Watanabe 1998/05/27 */
//			/* ﾎﾟｰﾘﾝｸﾞはﾒﾓﾘ送信でないので CMN_CheckMemoryTxCommand()で弾かれる為、
//			** CheckPollingCommand()は無意味なので削除します
//			*/
//			if ((CMN_CheckMemoryTxCommand((UBYTE)com_file, CMN_STATUS_CHK) == TRUE)	/** メモリ送信原稿である */
//			 && (CheckPollingCommand((UBYTE)com_file) == FALSE)) {					/** ポーリングでない */
#endif
			if (CMN_CheckMemoryTxCommand((UBYTE)com_file, CMN_STATUS_CHK) == TRUE) {	/** メモリ送信原稿の時 */
#if (PRO_CIPHER == ENABLE)
				/* スクランブルの拡張ＲＯＭをはずした後に、暗号化原稿を復号化すると正しく動作しないので
				** オペーレーションで弾きます By 98/04/16 T.Fukumoto
				*/
				if ((com_ptr->Option.Item == SYS_CIPHER_TX)	/* 指定されたファイルが暗号化原稿の時 */
				 && (ScrambleOn)) {							/* ＲＯＭスイッチがＯＮの時 98/04/16 Add By T.Fukumoto */
					/* 暗号化送信予約原稿復号化用パラメータ設定 */
					if (SetCipherTxDocDecipherPara(&is_decipher_on) == FALSE) {	/* 登録中止又は、タイムアップの時 */
						return;
					}
					if (is_decipher_on) {	/* 暗号化原稿を復号化する時 */
						/* プリントできる状態かをチェックします */
						if (CheckPrintOperationEnable() == FALSE) {
							return;
						}

						/* 復号化可能かチェックします 98/03/11 Add By T.Fukumoto */
						if (CheckCipherExecEnable(OPR_DECIPHER_TX_DOC) == FALSE) {
							NackBuzzer();	/* by K.Watanabe 1998/05/11 */
							return;
						}

						/* 暗号化原稿復号化メッセージの送信 */
						OperationMessageToMain.Message = MSG_DECIPHER_START;
						OperationMessageToMain.SubMessage1 = SYS_MEM_TX_FILE;
						OperationMessageToMain.SubMessage2 = com_file;
						snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
						MainTaskExecWait();
						return;
					}
				}
#endif
				/* プリント起動メッセージの送信 */
				FinalMemoryPrintOperation(SYS_MEM_TX_FILE, com_file, NULL);	/* 通信中の物もプリントできるのか？TBD*/
			}
			else {	/** スキャナーコマンド或いはポーリングコマンド */
				NackBuzzer();
				OPR_ChildErrorFlag = NO_COMMAND_DOCUMENT_ERROR;	/* "ﾖﾔｸｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ   " */
			}
		}
		else {	/** 入力されたコマンド番号に対応するコマンドが存在しない */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_COMMAND_ERROR;	/* "ﾂｳｼﾝﾏﾁ ｱﾘﾏｾﾝ        " */
		}
	}
}

/*************************************************************************
	module		:[]
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
	date		:[]
	author		:[]
*************************************************************************/
#if (0)	/* この関数は必要ないので、削除します by K.Watanabe 1998/05/27 */
//UBYTE CheckPollingCommand(UBYTE com_file)
//{
//	if ((SYB_CommandFile[com_file].Option.Item == SYS_POLLING_RX)
//	||	(SYB_CommandFile[com_file].Option.Item == SYS_DB_POLLING_RX)
//	||	(SYB_CommandFile[com_file].Option.Item == SYS_SEQUENTIAL_POLLING)) {
//		return (TRUE);
//	}
//	return (FALSE);
//}
#endif

/*************************************************************************
	module		:[暗号化送信予約原稿復号化用パラメータ設定]
	function	:[
		1.暗号化原稿を復号化するかを設定します
		2.復号化する時は、暗号化キー・拡張キーの入力を行います
		3.復号化しない時は、そのまま終了します
	]
	return		:[
		TRUE	:セット完了
		FALSE	:セット中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/22]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
UBYTE SetCipherTxDocDecipherPara(UBYTE *is_decipher_on)
{
	*is_decipher_on = FALSE;	/* 暗号化解除の初期値ＯＦＦをセット */
	if (SelectData(D2W_SelectDecipher,	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ  :    " */
				   D2W_Off2,			/* "                OFF " */
				   2,
				   is_decipher_on,
				   TRUE,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* 選択中止又は、タイムアップの時 */ /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(FALSE);
	}
	if (*is_decipher_on) {	/* 暗号化解除がＯＮに設定された時 */
		/* 暗号化機能用変数クリア */
		ClearOPR_CipherData();

		/* タイトルワーディングの作成 */
		CMN_StringCopy(OPR_CipherData.TitleWording, D2W_PrintStoredDocument);	/* "ﾖﾔｸｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ      " */

		/* 暗号化キー・拡張キーの入力 */
		if (SetDecipherParameter() == FALSE) {
			return(FALSE);
		}

		/* 暗号化送信予約原稿復号化用データのセット */
		SetDecipherData();
	}

	return(TRUE);
}
#endif

/*************************************************************************
	module		:[通信管理記録自動出力セット]
	function	:[
		1.通信管理記録の自動出力のＯＮ／ＯＦＦの設定を行う。
	]
	return		:[PRG - G1]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
void SetJournalOnOff(void)
{
	if (EnterSettingStatus(D2W_SelectAutoPrint,	/* "ｼﾞﾄﾞｳ ﾌﾟﾘﾝﾄ:        " */
						   D2W_Off2,			/* "                OFF " */
						   2,
						   SETTING_STATUS_2,
						   OPR_VALID_CHECK_NOT_NEED,
						   JOURNAL_AUTO_PRINT_ON) == OK) {
		ChildDisplaySetCompleted(D2W_JournalOnOff);	/* "ﾂｳｼﾝｷﾛｸ ｼﾞﾄﾞｳｾｯﾄ    " */
	}
}

/*************************************************************************
	module		:[通信管理記録リスト．コール。]
	function	:[
		1.通信管理記録リストをコールする。
		2.通信結果がある時のみ印字可能である
	]
	return		:[なし]
	common		:[
		SYB_JournalFile
		OPR_ChildErrorFlag
	]
	condition	:[]
	comment		:[PRG-G2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintJournalList(void)
{
	UWORD	journal_number;		/*ｼﾞｬｰﾅﾙ番号*/
	
/*----------------------------------* 
 *	ジャーナルプリント
 *----------------------------------*/
#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	status;

	SYS_JournalPrintType = TXTYPE;

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */

	while (1) {
		/** 画面の表示 */
		DisplayJournalSelect();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {	 /**入力キーによる処理*/
		case FUNCTION:		/* 機能／右矢印キー			*/
			if (SYS_JournalPrintType < BOTHTYPE){
				SYS_JournalPrintType++;
			}
			else{
				SYS_JournalPrintType = TXTYPE;
			}
			
			break;
		case LEFT_ARROW:		/* 左矢印キー */

			if (SYS_JournalPrintType > TXTYPE){
				SYS_JournalPrintType--;
			}
			else{
				SYS_JournalPrintType = BOTHTYPE;
			}
			
			break;
			
		case ENTER:					/**セットキー入力*/
			/** ジャーナルデータの有無をチェック */	/* 修正 送信、受信を別々でチェックします。by Y.Kano 2004/04/26 */
			switch (SYS_JournalPrintType){
			case TXTYPE:
				for (journal_number = 0; journal_number < SYS_JOURNAL_MAX; journal_number++) {
					if (SYB_JournalFile[journal_number].Type == TX_COM_MODE ) {
						if (SYB_JournalFile[journal_number].Number != 0xffff) {
							FinalListPrintOperation(LST_JOURNAL_LIST);
							return;
						}
					}
				}
				NackBuzzer();
				OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;
				return;

			case RXTYPE:
				for (journal_number = 0; journal_number < SYS_JOURNAL_MAX; journal_number++) {
					if (SYB_JournalFile[journal_number].Type == RX_COM_MODE ) {
						if (SYB_JournalFile[journal_number].Number != 0xffff) {
							FinalListPrintOperation(LST_JOURNAL_LIST);
							return;
						}
					}
				}
				NackBuzzer();
				OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;
				return;

			case BOTHTYPE:
				for (journal_number = 0; journal_number < SYS_JOURNAL_MAX; journal_number++) {
					if (SYB_JournalFile[journal_number].Number != 0xffff) {
						FinalListPrintOperation(LST_JOURNAL_LIST);
						return;
					}
				}
				NackBuzzer();
				OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;
				return;
			default:
				break;
			}
			
		case NO_EFFECT:
			break;
			
		case STOP:					/**ストップキー入力*/
		case KEY_TIME_UP:			/**キー待ちタイムオーバー*/
			return;
			
		default:
			NackBuzzer();
			break;
		}
	}
#else
	/** ジャーナルデータの有無をチェック */
	for (journal_number = 0; journal_number < SYS_JOURNAL_MAX; journal_number++){
		if (SYB_JournalFile[journal_number].Number != 0xffff) {	/* -1 -> 0xffff By M.Tachibana 1997/05/10 */
			FinalListPrintOperation(LST_JOURNAL_LIST); /** メインにリスト起動メッセージ送信 1995/04/04 Egu*/
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;
#endif	/* defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE) */
}

/*************************************************************************
	module		:[通信証セット機能]
	function	:[
		1.通信証セットの機能を実行する。
		2.送信証と受領証の選択を行う。
		3.自動プリントのＯＮ／ＯＦＦの設定を行う。
	]
	return		:[なし]
	common		:[
		SYB_ConfirmationReportSwitch:
	]
	condition	:[]
	comment		:[PRG-J02]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/22]
	author		:[江口]
*************************************************************************/
void SetCommunicationResult(void)
{
	if (CTRY_RCR() != 0) { /** 受領証機能有り */
		/** 送信証／受領証の選択を行う */
		if (EnterSettingStatus(D2W_Null,
							   D2W_TCRSelected,
							   2,
							   SETTING_STATUS_6,
							   OPR_VALID_CHECK_NOT_NEED,
						       CONFIRM_TYPE_RCR ) == NG) { /*STOP*/
			return;
		}

		/*
		** 送信証／受領証で選択したあと、そのままストップキーで抜けると、
		** SettingStatusは書き換えられるが、SYB_ConfirmationReportSwitchは
		** 書き換えられず、以前に設定した状態を維持してしまう by H.Hirao 1999/03/12
		*/
		/** セットした状態により通信証スイッチに値をセットする　*/
		if (CHK_ConfirmationReportON()) {
			if (CTRY_RCR() && CHK_RCR_ON()) {
				SYB_ConfirmationReportSwitch = RCR_REQUEST;
			}
			else {
				SYB_ConfirmationReportSwitch = TCR_REQUEST;
			}
		}
		else {
			SYB_ConfirmationReportSwitch = NO_CONFIRMATION_REPORT;
		}
	}
	/** 自動プリントのＯＮ／ＯＦＦのセット */
	if (EnterSettingStatus(D2W_SelectAutoPrint,	/* "ｼﾞﾄﾞｳ ﾌﾟﾘﾝﾄ:        " */
						   D2W_Off2,			/* "                OFF " */
						   2 ,
						   SETTING_STATUS_6,
						   OPR_VALID_CHECK_NOT_NEED,
						   CONFIRM_ON ) == NG) { /* STOP */
		return;
	}

	/** セットした状態により通信証スイッチに値をセットする　*/
	if (CHK_ConfirmationReportON()) {
		if (CTRY_RCR() && CHK_RCR_ON()) {
			SYB_ConfirmationReportSwitch = RCR_REQUEST;
		}
		else {
			SYB_ConfirmationReportSwitch = TCR_REQUEST;
		}
	}
	else {
		SYB_ConfirmationReportSwitch = NO_CONFIRMATION_REPORT;
	}
	ChildDisplaySetCompleted(D2W_SetCommunicationResult);
}

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
/*************************************************************************
	module		:[ナンバーディスプレイ着信履歴プリント]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	Print_ND_JournalList(void)
{
	if (SYB_NumberDisplayJournal[0].Status & SYS_ND_SET) { /** 通信履歴がある場合 */
		/* リストプリント起動メッセージ送信 */
		FinalListPrintOperation(LST_INF_ND_LIST);
		return;
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;	/* "ﾂｳｼﾝｹｯｶ ｱﾘﾏｾﾝ       " */
}
#endif

/*************************************************************************
	module		:[グループリスト]
	function	:[
		1.グループリストの印字の起動をかける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG - H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintGroupList(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	cnt;
#endif
	UWORD	cnt;
	struct	SYS_SpeedDialData_t *ptr;

	for (cnt = 0; cnt < SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX; cnt++) {
		if (cnt < SYS_ONETOUCH_MAX) {
			ptr = &SYB_OnetouchDial[cnt];
		}
		else {
			ptr = &SYB_SpeedDial[(UBYTE)(cnt - SYS_ONETOUCH_MAX)];
		}
		if (((ptr->Dial[0] & 0xF0) != 0xF0) && (ptr->Group != 0x00000000UL)) {
			FinalListPrintOperation(LST_GROUP_LIST); /** メインにリスト起動メッセージ送信 */
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[メッセージソウシンON/OFF設定機能]
	function	:[
		1.メッセージソウシンON/OFF設定の機能を実行する。
	]
	return		:[なし]
	common		:[
		SYB_SettingStatus:
	]
	condition	:[]
	comment		:[PRG - L1]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
void SetMessageOnOff(void)
{
	if (EnterSettingStatus( D2W_MessageOnOff ,
							D2W_Off2,
							2 ,
							SETTING_STATUS_4 ,
							OPR_VALID_CHECK_NOT_NEED,
	 						MESSAGE_TRANSMIT_ON) == OK) {
		ChildDisplaySetCompleted(D2W_MessageTx); /* [   ** ｾｯﾄｶﾝﾘｮｳ **  ] */
	}
}

/*************************************************************************
	module		:[メッセージ機能]
	function	:[
		1.カバーページのユーザーメッセージの登録を実行
	]
	return		:[なし]
	common		:[
		SYB_CoverPageMessage:
		D2W_SetCoverPageMessage;
	]
	condition	:[]
	comment		:[PRG - L2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/28]
	author		:[江口]
*************************************************************************/
void SetMessageDataMode(void)
{
	DisplayStringHigh(0, D2W_SetCoverPageMessage);	/*"Cover Page          "*/
	/** メッセージ登録 */
	if (CoverPageMessageInput() == OK) { /** 登録完了 */
		/** 新しいデータを登録 */
#if (PRO_MESSAGE_KANJI_INPUT == ENABLE)	/* Add By O.Kimoto 1999/01/13 */
		StoreCharacterInputValue(SYB_CoverPageMessage , ASC_JIS_DATA_TYPE);
#else
		StoreCharacterInputValue(SYB_CoverPageMessage , ASC_DATA_TYPE);
#endif

		ChildDisplaySetCompleted(D2W_MessageSet); /* "Enter Cover Message "*/
	}
}

/*************************************************************************
	module		:[カーバーページメッセージ登録]
	function	:[
		1.カバーページのメッセージの登録を行う。
		2.登録できるメッセージは最大40桁
	]
	return		:[]
	common		:[CharacterInput
				  SYB_CoverPageMessage]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/04]
	author		:[江口]
*************************************************************************/
UBYTE CoverPageMessageInput(void)
{
	/** 初期化 */
	ClearCharacterInput();											/* ワークバッファクリア */
	SetCharacterInputMode();										/* 文字入力モード初期化 */

#if (PRO_MESSAGE_KANJI_INPUT == ENABLE)	/* Add By O.Kimoto 1999/01/14 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, SYB_CoverPageMessage, 0);	/* 前回登録データをセット */
 #else
	SetCharacterInputBuf(SYB_CoverPageMessage);
 #endif
#else
	CMN_StringCopy(CharacterInput.Buffer, SYB_CoverPageMessage);	/* 前回登録データをセット */
#endif

	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_MESSAGE_MAX - 1;					/* 入力最大文字数セット */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
 #if (PRO_MESSAGE_KANJI_INPUT == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
 #else
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
 #endif
#else
#if (PRO_MESSAGE_KANJI_INPUT == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	return (NameInput(OPR_KANJI_ENABLE));
#else
	return (NameInput(OPR_KANJI_DISABLE));
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

}

/*************************************************************************
	module		:[メッセージリスト]
	function	:[
		1.カバーページの印字要求をメインにおくる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-L3]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintMessageList(void)
{
	FinalListPrintOperation(LST_COVERPAGE_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
}

/*************************************************************************
	module		:[原稿枚数セット機能]
	function	:[
		1.原稿枚数セットの機能を実行する。
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:
	]
	condition	:[]
	comment		:[PRG-M]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[]
*************************************************************************/
void SetNumberOfPages(void)
{
	UWORD	pages;

	pages = 0;

	DisplayStringHigh(0, D2W_InputPageCount);	/* "ｹﾞﾝｺｳ ﾏｲｽｳ ｦ ﾄﾞｳｿﾞ  " */

	/** ページ数入力 */
#if defined(POPLAR_F)
 #if defined(JP1)
	pages = FixedLengthNumberInput(1, 1, 50, (UBYTE)18, D2W_PageCount1_30);	/* 入力範囲は国、最大スタック数によりかわるかも 1995/08/29 Eguchi*/
 #else
	pages = FixedLengthNumberInput(1, 1, 30, (UBYTE)18, D2W_PageCount1_30);	/* "ｹﾞﾝｺｳ ﾏｲｽｳ (1-30):  " */
 #endif
#else
 #if defined(POPLAR_N) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
	pages = FixedLengthNumberInput(1, 1, 30, (UBYTE)18, D2W_PageCount1_30);	/* "ｹﾞﾝｺｳ ﾏｲｽｳ (1-30):  " */
 #else
	pages = FixedLengthNumberInput(1, 1, 50, (UBYTE)18, D2W_PageCount1_30);	/* 入力範囲は国、最大スタック数によりかわるかも 1995/08/29 Eguchi*/
 #endif
#endif

	if (pages != 0xFFFF) {	/* 登録された（0xFFFF:登録中止） */
		SpecialCommandValue.Page = (UBYTE)pages;
	}
}

/*************************************************************************
	module		:[プリンタオプションリセット（ＰＣプリント対応用）]
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
	date		:[1997/07/02]
	author		:[桑原美紀]
*************************************************************************/
#if (PRO_PC_PRINT == ENABLE)
void ResetPrinterBoard(void)
{
	if (ConfirmKeyInputOperation(D2W_BoardReset, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
 #if (PRO_PRINT_TYPE == LASER)	/* 1998/01/27 Y.Matsukuma */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_PRINTDATA_RX) { /** PCプリント動作中 */
			OperationMessageToMain.Item = FROM_DPR_REMOTEFUNCEXECTASK;
			OperationMessageToMain.Message = MSG_DPR_PCPRINTPAGETRANSABORT;
			OperationMessageToMain.SubMessage1 = 0;
			OperationMessageToMain.SubMessage2 = 0;
			snd_msg(mbxno.MAN_Task,&OperationMessageToMain);
			MainTaskExecWait();
			OperationMessageToMain.Item = FROM_OPERATION;
			OperationEnd();
		}
		else {
			NackBuzzer();
		}
 #else
		OperationMessageToMain.Item = FROM_DPR_REMOTEFUNCEXECTASK;
		OperationMessageToMain.Message = MSG_DPR_PCPRINTPAGETRANSABORT;
		OperationMessageToMain.SubMessage1 = 0;
		OperationMessageToMain.SubMessage2 = 0;
		snd_msg(mbxno.MAN_Task,&OperationMessageToMain);
		MainTaskExecWait();
		OperationMessageToMain.Item = FROM_OPERATION;
		OperationEnd();
 #endif
	}
}
#endif	/* (PRO_PC_PRINT == ENABLE) */

#if !defined(STOCKHM2)
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Add by Y.Kano 2003/10/15 */
/*************************************************************************
	module		:[手動カッター実行]
	function	:[
		1.手動カッター動作を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/15]
	author		:[加納]
*************************************************************************/
void ManualCutter(void)
{
	/* 上段表示 */
	DisplayStringHigh(0, D2W_ManualCutterMode);			/* "ｼｭﾄﾞｳ ｶｯﾀｰ ｼﾞｯｺｳ    " */

	/* 下段表示 */
	ClearDisplayLow();
#if (0) /* ここで表示しないことは良いと思います。Modify by SMuratec L.Z.W 2003/10/29 */
	DisplayStringLow(0, FunctionDisplayBufferLow);
#endif

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
 #endif
	if (CutterPosition() != CUTTER_BUSY) {	/* カッターが待機位置にあるかチェックする */
		CutterOn();	/* カッターが待機位置にないときはカッター動作させてカッターを待機位置に置く */
		while (PRN_Control.CutterBusy) {	/* カッター動作終了待ち */
			wai_tsk(2);	/* 20ms */
		}
	}
 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_Off();
 #endif
}
 #endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif	/* End of (!defined(STOCKHM2)) */

/*----------------------------------*
 *	ジャーナルプリント
 *----------------------------------*/
#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
void	DisplayJournalSelect(void)
{
	/*if (OPR_ErrorWordingLow != NULL) [*/
	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	switch (SYS_JournalPrintType){
	case TXTYPE:
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_JournalTx);	/*"[01] ｿｳｼﾝｷﾛｸ          "*/
		break;
	case RXTYPE:
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_JournalRx);	/*"[02] ｼﾞｭｼﾝｷﾛｸ         "*/
		break;
	case BOTHTYPE:
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_JournalTxRx);	/*"[03] ｿｳｼﾞｭｼﾝｷﾛｸ       ";*/
		break;
	default:
		break;
	}

 #if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2004/10/22 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	FlashDisplayStringLow(D2W_ProgramEnter);			/* "            ｷﾉｳ/ｾｯﾄ " */
 #else
/* DVT : Delete by SMuratec C.P 2004/09/06 *
**	CMN_StringCopy(FunctionDisplayBufferLow, D2W_FunctionEnter);
**	FunctionDisplayBufferLow[12] = '\x7F';					( <- )
**	FunctionDisplayBufferLow[13] = '/';						( /  )
**	FunctionDisplayBufferLow[14] = '\x7E';					( -> )
*/
	CMN_StringCopy(FunctionDisplayBufferLow, D2W_ProgramEnter);

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
#endif
}
#endif

/**********************************************************************************************************************/
/**
	@brief		通信管理記録日報プリント
	
	@li			
	@param		なし
	@return		なし
	@note		なし
	@date		2004/10/22 作成
	@author		渡辺一章
*/
/**********************************************************************************************************************/
#if (PRO_DAILY_REPORT == ENABLE)
void PrintDailyReport(void)
{
	if (SYB_DailyReportPrintPos != SYB_JournalPoint) {
		SYS_JournalPrintType = BOTHTYPE;
		FinalListPrintOperation(LST_DAILY_REPORT);
	}
	else {
		NackBuzzer();
		OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;	/* "ﾂｳｼﾝｹｯｶ ｱﾘﾏｾﾝ       " */
	}
}
#endif
