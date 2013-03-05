/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_PRN.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: セキュリティ受信
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysbatch.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdial.h"
#include	"\src\atlanta\define\sysmemrx.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

/* Protect
#if (PRO_SECURITY_RX == ENABLE)
void	SetSecurityReceive(void);
void	PrintMemoryReceiveDoc(void);
UBYTE	SecurityRxTimeInput(void);
UBYTE	CheckProtectedDocStored(void);
UBYTE	CheckProtectedDocStoring(void);
void	CalculateSecurityRxStartTime(UDWORD);
void	AllClearPrintProtect(void);
void	SetSecurityRxMode(void);
void	SetSecurityRxChkMsgPrint(void);
void	ClearSecurityRxChkMsgPrint(void);
UBYTE	CheckSecurityRxChkMsgPrint(void);
#endif
*/

#if (PRO_SECURITY_RX == ENABLE)
/*************************************************************************
	module		:[セキュリティ受信セット]
	function	:[
		1.セキュリティ受信機能有効／無効のセットおよびセキュリティ受信モード開始時刻の
		，セットを実行。
		2.プロテクトパスコードが登録されていない場合、このオペレーションは禁止される。
		3.プロテクトパスコード入力時に間違ったパスコードが入力された場合、エラーで終了
		4.ただしプロテクトパスコードが入力された場合、セキュリティ受信機能のセットを行う。
		5.セキュリティ受信機能ＯＦＦにセットされた場合。
		,　・セキュリティ受信原稿がメモリー内に存在する場合（プリント待ち、受信中で１ページ以上原稿確定しているもの）
		,　　ＯＦＦにセットすることはできない。オペレーション終了
		,　・セキュリティ受信モードの解除も行う。
		6.セキュリティ受信機能ＯＮにセットされた場合。
		,　・セキュリティ受信モード開始時刻の設定を行う。
		,　・セキュリティ受信モード開始時刻（ロング）を計算する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
void SetSecurityReceive(void)
{
	UBYTE	is_security_on;
	UWORD	passcode;
	UDWORD	current_time;

	/* ＬＣＤ上段表示書き換え */
	DisplayStringHigh(0, D2W_SetSecurityReceive);	/* "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ ｾｯﾄ    " */

	/** プロテクトのパスコードの有無をチェックする */
	if (CheckProtectPasscodeSet() == FALSE) {	/** パスコードが登録されていない */
		/** オペレーション禁止。終了*/
		OPR_ChildErrorFlag = NO_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ﾐﾄｳﾛｸﾃﾞｽ " */
		NackBuzzer();
		return;
	}

	/** プロテクトパスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		/** 終了 */
		return;
	}

	/** プロテクトパスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /** パスコード不一致 */
		/** 終了 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/** プロテクトの設定を行う */

	/* 現在の設定値の獲得 */
	is_security_on = FALSE;
	if (CHK_SecurityReceiveON()) {
		is_security_on = TRUE;
	}

	/* 通常は、EnterSettingStatus()を使用するべき箇所だが、SYB_SettingStatus[]にセットする
	** タイミングが重要なため使用できません
	*/
	if (SelectData(D2W_SecurityReceive,	/* "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ:       " */ /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
				   D2W_Off2,			/* "                OFF " */
				   2,
				   &is_security_on,
				   TRUE,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* 登録中止又は、タイムアップの時 */ 
		return;
	}

	if (is_security_on) {	/** ＯＮに設定された時 */
		/** セキュリティ受信開始時刻の設定を行う */
		current_time = SYB_CurrentTime;	/* 設定前の時刻を退避 */
		if (SecurityRxTimeInput() == NG) {	/** ストップキーでオペレーション終了 */
			return;
		}
		/** セキュリティ受信機能を有効にする */
		SYB_SettingStatus[SETTING_STATUS_23] |= SECURITY_RX_ON;
		if (SYB_SecurityRxModeFlag == 0) {	/** セキュリティ受信モード中でない */
			/** セキュリティ受信モード開始時刻の計算 */
			CalculateSecurityRxStartTime(current_time);
		}
	}
	else {					/** ＯＦＦに設定された時 */
		/* セキュリティ受信原稿の有無を調べ、もしセキュリティ受信原稿がプリントされていなかったり、
		** 受信中であった場合はＯＦＦにできない
		*/
		if ((CheckProtectedDocStored() == TRUE)		/** プリント待ちの状態のセキュリティ原稿がある */
		 || (CheckProtectedDocStoring() == TRUE)) {	/** 受信中で１ページ以上セキュリティ原稿が確定している */
			/** 設定をかえることはできない（OFF->OFFの時も同様） */
			NackBuzzer();
			OPR_ChildErrorFlag = PROTECT_DOCUMENT_STORED_ERROR;	/* "ｼﾞｭｼﾝ ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｽ " */
			return;
		}
		/** セキュリティ受信機能を無効にする */
		SYB_SettingStatus[SETTING_STATUS_23] &= ~SECURITY_RX_ON;
		/** セキュリティ受信モードも解除する */
		SYB_SecurityRxModeFlag = 0;
	}

	ChildDisplaySetCompleted(D2W_SetSecurityReceive);	/* "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ ｾｯﾄ    " */
}

/*************************************************************************
	module		:[セキュリティ受信原稿プリント]
	function	:[
		1.セキュリティ受信モード中に受信した原稿のプリントアウトを実行
		2.プロテクトパスコードがない場合、このオペレーションはできない
		3.プロテクトパスコード入力時に間違ったパスコードが入力された場合、エラーで終了
		4.セキュリティ受信原稿がない場合終了。
		,　セキュリティ受信原稿：受信完了して、プリント待ちのもの
		,　　　　　　　　　　　　受信中だが１ページ以上受信原稿が確定しているもの
		5.プリントできる状態であれば、メインタスクにプロテクト解除のメッセージ送信
		, メインタスクでプロテクト解除を行う。
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
*************************************************************************/
void PrintMemoryReceiveDoc(void)
{
	UWORD	passcode;

	passcode = 0;

	DisplayStringHigh(0, D2W_PrintMemoryReceiveDocMode);

	/* パスコードの有無を調べる .念のための処理 */
	if (CheckProtectPasscodeSet() == FALSE) {
		return;
	}

	/** パスコードの入力及びチェックを行う */
	/* パスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		/** stopキーでオペレーション終了 */
		return;
	}
	/** パスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /** パスコード不一致 */
		/**エラー終了*/
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/** 原稿の有無を調べる */
	if ((CheckProtectedDocStored() == TRUE)		/** プリント待ちのセキュリティ受信原稿あり */
	 || (CheckProtectedDocStoring() == TRUE)) {	/** 受信中のセキュリティ受信原稿あり(１ページ以上確定） */
		if (CheckPrintOperationEnable() == TRUE) {/**プリント可能*/
#if (PRO_PRINT_TYPE == LASER)	/* F100デュアル動作の制限対策 1997/12/27 Y.Matsukuma */
			if (CMN_CheckF100Model()) {
				if (CheckScannerSending()) {
					OPR_ChildErrorFlag = SCANNER_USE_ERROR;	/* Scanner In Use */
					NackBuzzer();
					return;
				}
			}
#endif
			/** メインタスクにプロテクト解除のメッセージ送信 */
			/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
			OperationMessageToMain.Message = MSG_PRINT_PROTECT_OFF;
			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
			MainTaskExecWait();
		}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && defined(GBR)	/* addedbythonda1999/03/31 */
		else {
			/* セキュリティ解除 */
			AllClearPrintProtect();
		}
#endif

	}
	else {	/** 原稿なし */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && defined(GBR)	/* addedbythonda1999/03/31 */
		/* セキュリティ解除 */
		AllClearPrintProtect();
#endif

		NackBuzzer();
		OPR_ChildErrorFlag = NO_PROTECT_DOCUMENT_ERROR;
	}
}

/*************************************************************************
	module		:[セキュリティ受信モード開始時刻設定]
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
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
UBYTE SecurityRxTimeInput(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	hour;
	UBYTE	minute;

	/**初期化*/
	ClearCharacterInput();
	SetLongTimeToCharacterInput(SYB_CurrentTime, SECURITY_RX_TIME_TYPE);
	CharacterInput.WritePosition = 3;
	CharacterInput.LcdDisplayPosition = 14;
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_EnterDelayedTxTime;

	/**上段表示*/
	DisplayStringHigh(0, D2W_SetSecurityReceive);	/* "ｾｷｭﾘﾃｨ ｼﾞｭｼﾝ ｾｯﾄ    " */

	while (1) {
		DisplayTimeInput(SECURITY_RX_TIME_TYPE);

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			FixedNumberDataSet(key);
			break;
		case FUNCTION:
			CursorRightRotation();
			break;
		case LEFT_ARROW:
			CursorLeftRotation();
			break;
		case ENTER:
			hour = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 2);
			minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[2], 2);
			if (hour <= 24 && minute <= 59) {
				/*正しい値*/
				SYB_SecurityRxSettingTime = (UWORD)hour;
				SYB_SecurityRxSettingTime *= 60;
				SYB_SecurityRxSettingTime += (UWORD)minute;
				return (OK);
			}
			else {
				CharacterInput.CursorPosition = 0;
				NackBuzzer();
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return (NG);
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
	}
}

/*************************************************************************
	module		:[セキュリティ受信原稿の有無を調べる(受信完了のもの）]
	function	:[
		1．受信完了している、（プリント待ち）のセキュリティ受信原稿の有無を調べる
	]
	return		:[
				TRUE:原稿あり
				FALSE:原稿なし
				]
	common		:[SYB_MemoryRxPrint]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
UBYTE CheckProtectedDocStored(void)
{
	UBYTE	loop;

	for (loop = 0; loop < SYS_MEMORY_RX_MAX; loop++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/26 */
		if ((SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_PRINT)
		&&	(SYB_MemoryRxPrint[loop].Protect== SYS_PROTECT_ON)) {
#else
		if (((SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_PRINT)
		 || (SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_FAST_PRINT))
		&&	(SYB_MemoryRxPrint[loop].Protect== SYS_PROTECT_ON)) {
#endif
			return (TRUE);
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[セキュリティ受信原稿の有無を調べる(受信中のもの）]
	function	:[
		1．受信中のもの（少なくとも１ページ以上受信完了）のセキュリティ受信原稿の有無を調べる
	]
	return		:[
				TRUE:原稿あり
				FALSE:原稿なし
				]
	common		:[SYB_MemoryRxPrint]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
UBYTE CheckProtectedDocStoring(void)
{
	UBYTE	loop;

	for (loop = 0; loop < SYS_MEMORY_RX_MAX; loop++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/26 */
		if ((SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_STORE)
		&&	(SYB_MemoryRxPrint[loop].Protect== SYS_PROTECT_ON)) {
#else
		if (((SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_STORE)
		 ||  (SYB_MemoryRxPrint[loop].Status == SYS_MEMORY_RX_STORE_PRINT))
		&&	(SYB_MemoryRxPrint[loop].Protect== SYS_PROTECT_ON)) {
#endif
			return (TRUE);
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[セキュリティ受信モード開始時刻の計算]
	function	:[
		1.オペレーションで設定した値を基準時刻（1992年1月1日0時0分0秒）からの積算秒に変換する
		2.引数で現在時刻の基準時刻からの積算秒をもらう。
		3.オペレーションで設定した値が現在時刻よりも前の場合、次の日の指定時刻にセキュリティ受信モードにはいる
	]
	return		:[]
	common		:[
				SYB_SecurityRxModeStartTime
				SYB_SecurityRxSettingTime
				]
	condition	:[]
	comment		:[
		この関数がコールされるのは以下の場合にかぎる
		　・オペレーションでセキュリティ受信機能を有効にセットしたとき
		　　（ただしセキュリティ受信モード中は除く）(OPR)
		　・セキュリティ受信原稿のプリントを実行し、セキュリティ受信モードが
		　　解除された時。(MAN)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
void CalculateSecurityRxStartTime(UDWORD std_time)
{
	UBYTE		next;
	UWORD		current_time;
	UDWORD		add_minute;
	TIME_DATA_t	bcd_time;

	CMN_LongTimeToBCD(&bcd_time, std_time);

	current_time = (UWORD)CMN_BCD_ToDecimal(bcd_time.Hour);
	current_time *= 60;
	current_time += (UWORD)CMN_BCD_ToDecimal(bcd_time.Minute);

	next = 0;
	if (SYB_SecurityRxSettingTime < current_time) {
		/* 現在時刻よりも前が設定されている */
		next = 1;
	}
	add_minute = 0x00000000UL;
	add_minute = (UDWORD)(24 * next * 60) + (UDWORD)SYB_SecurityRxSettingTime - (UDWORD)current_time;

	SYB_SecurityRxModeStartTime = std_time + add_minute*60;
}

/*************************************************************************
	module		:[セキュリティ受信原稿のプロテクトを解除する]
	function	:[
		1.セキュリティ受信モード中に受信した原稿（プロテクト状態になっている）
		,　のプロテクトをすべて解除する。
		2.セキュリティ受信モード状態を解除する
		3.次のセキュリティ受信モード開始時刻を計算する。
		4.この関数は、オペレーションでセキュリティ受信原稿プリントオペレーションが実行され
		, MANタスクがOPRタスクからのプロテクト解除のメッセージを受信したところで実行される
		, よって以下の状態が保証されている筈である。
		, ・セキュリティ受信原稿がある
		, ・セキュリティ受信モード中である
		, ・セキュリティ受信機能は有効である
		]
	return		:[]
	common		:[
				SYB_MemoryRxPrint
				SYB_SecurityRxModeFlag
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
void AllClearPrintProtect(void)
{
	UBYTE	loop;
	UBYTE	read_point;

	read_point = SYB_MemoryRxPrintReadPoint;

	/* セキュリティ受信原稿のプロテクトをすべて解除する */
	for (loop = 0; loop < SYS_MEMORY_RX_MAX; loop++) {
#if (PRO_REVERSE_PRINT == DISABLE)
		if ((SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_PRINT)
		||	(SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_STORE)) {
#else
		if ((SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_PRINT)
		||	(SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_STORE)
		||	(SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_STORE_PRINT)
		||	(SYB_MemoryRxPrint[read_point].Status == SYS_MEMORY_RX_FAST_PRINT)) {
#endif
			if (SYB_MemoryRxPrint[read_point].Protect == SYS_PROTECT_ON) {
				SYB_MemoryRxPrint[read_point].Protect = SYS_PROTECT_OFF;
			}
		}
		read_point++;
		if (read_point >= SYS_MEMORY_RX_MAX) {
			read_point = 0;
		}
	}
	/* セキュリティ受信モードを解除する */
	SYB_SecurityRxModeFlag = 0;

	/* 次のセキュリティ受信モード開始時刻を計算する */
	CalculateSecurityRxStartTime(SYB_CurrentTime);
}

/*************************************************************************
	module		:[セキュリティ受信モードのセット]
	function	:[
		1.セキュリティ受信モードフラグをセットする
		2.以下の条件がすべて成立した時、セキュリティ受信モードとなる
		,　・セキュリティ受信機能有効
		,　・現在セキュリティ受信モード中ではない
		,　・現在時刻がセキュリティ受信モード開始時刻をこえた
		3.セキュリティ受信モードのセットおよびその監視はメインタスクで行う
		,　メインタスクがループを一回まわる毎にこの関数を実行する。
		,　よってセキュリティ受信モードにはいる時に設定した時刻から最悪１分のおくれが生じる可能性がある
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/26]
	author		:[江口]
*************************************************************************/
void SetSecurityRxMode(void)
{
	/* セキュリティ受信モードの設定を行う */
	if ((CHK_SecurityReceiveON())							/* セキュリティ受信機能有効 */
	 && (SYB_SecurityRxModeFlag == 0)						/* セキュリティ受信モード中でない */
	 && (SYB_CurrentTime > SYB_SecurityRxModeStartTime)) {	/* セキュリティ受信モード開始時刻になった */
		SYB_SecurityRxModeFlag = 1;		/* セキュリティ受信モード中にセットする */
		SYB_SecurityRxChkMsgPrint = 0;	/* セキュリティ受信メモリーオーバーチェックメッセージプリント済みフラグクリア */
	}
}

/*************************************************************************
	module		:[セキュリティ受信モード中の受信メモリーオーバーチェックメッセージ起動]
	function	:[
		1.受信中にメモリーオーバーした時、セキュリティ受信モードでかつ
		,セキュリティ受信原稿が１ページ以上蓄積されている場合メモリーオーバー
		,チェックメッセージの印字起動のフラグをセットする。
		2.通信タスクで受信中メモリーオーバーが発生した時にコールされる。
		3.ここではクリアはしない
	]
	return		:[]
	common		:[SYB_SecurityRxChkMsgPrint]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/28]
	author		:[江口]
*************************************************************************/
void SetSecurityRxChkMsgPrint(void)
{
	if ((CheckProtectedDocStored() == TRUE)		/** プリント待ちのセキュリティ受信原稿あり*/
	 || (CheckProtectedDocStoring() == TRUE)) {	/** 受信中のセキュリティ受信原稿あり(１ページ以上確定） */
		if (SYB_SecurityRxChkMsgPrint == 0) {	/** チェックメッセージ印字済みでない場合 */
			SYB_SecurityRxChkMsgRequest = 1;
		}
	}
}

/*************************************************************************
	module		:[セキュリティ受信モード中、受信メモリーオーバーメッセージ印字終了処理]
	function	:[
		1.セキュリティ受信モード中の、受信メモリーオーバーメッセージのプリントが正常終了
		,したときの処理。
		2.メッセージ印字済みフラグをセット。２度と書かさないため
		3.メッセージ印字要求フラグをリセット.
		4.リストプリントが正常に終了した時のみ起動される
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/28]
	author		:[江口]
*************************************************************************/
void ClearSecurityRxChkMsgPrint(void)
{
	SYB_SecurityRxChkMsgPrint = 1;	/* セキュリティ受信モード中、受信メモリーオーバーメッセージ印字済みフラグセット */
	SYB_SecurityRxChkMsgRequest = 0;/* セキュリティ受信モード中、受信メモリーオーバーメッセージ印字要求フラグクリア */
}

/*************************************************************************
	module		:[セキュリティ受信モード中のメモリーオーバーメッセージ印字要求の有無の獲得]
	function	:[
		1.セキュリティ受信モード中、受信メモリーオーバーが発生した時のチェックメッセージ起動
		,要求の有無を調べる
	]
	return		:[
				TRUE:プリント起動
				FALSE:プリント起動要求なし
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/28]
	author		:[江口]
*************************************************************************/
UBYTE CheckSecurityRxChkMsgPrint(void)
{
	if ((SYB_SecurityRxChkMsgRequest == 1)	/* メッセージ起動要求あり */
	 && (SYB_SecurityRxChkMsgPrint == 0)) {	/* メッセージ印字済みでない(念のため) */
		return (TRUE);
	}
	return (FALSE);
}

#endif	/* (PRO_SECURITY_RX == ENABLE) */
