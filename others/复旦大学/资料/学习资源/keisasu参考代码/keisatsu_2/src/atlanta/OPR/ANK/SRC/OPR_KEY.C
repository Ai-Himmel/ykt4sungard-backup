/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_KEY.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キー取り込みモジュール
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\timer10.h"
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\opr\ank\ext_v\key_tbl.h"	/* ファイル移動 By O.Kimoto 1997/07/16 */
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include    "\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1997/12/17 */
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#endif

/* Prototype
void	OPR_GetKey(UWORD);
UBYTE	GetInputKeyCode(void);
UBYTE	GetInputKeyType(void);
void	OPR_KeyTask(void);
UBYTE	GetKeyPortBit(void);
void	OPR_CheckOnetouchSheetTask(void);
UBYTE	GetOnetouchSheetStatus(void);
void	AckBuzzer(void);
void	NackBuzzer(void);
*/

static UBYTE	InputKeyCode = OPR_NO_KEY;	/* 入力されたキーコード */
static UBYTE	InputKeyType = OPR_NO_KEY;	/* 入力されたキー種別   */
static UBYTE	OnetouchSheetStatus = 0;	/* ワンタッチシート状態 */

/*************************************************************************
	module		:[キー入力まち]
	function	:[
		1.キースキャンタスクからのメッセージをまちます
		2.キータイマータスクからのメッセージをまちます
		3.メインタスクからのメッセージをまちます
		4.キー入力が必要なときのみコールされます
		5.キー入力待ちの時間は引数で指定します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/28]
	author		:[江口,渡辺一章]
*************************************************************************/
void OPR_GetKey(UWORD key_wait_time)	/* キー待ちの時間 */
{
	UWORD	item;
	UWORD	message;
	UWORD	submessage;
	MESSAGE_t	*rx_message;

	/** キータイマータスクを起動する */
	tskno_OPR_KeyTimerTask = 0xffff;
	GetKeyTimer.Time = key_wait_time;
	cre_tsk(&tskno_OPR_KeyTimerTask, TSK_CMN_MAN_TIMER10MSTASK, &GetKeyTimer);

	/** キーコードをクリアする */
	InputKeyCode = OPR_NO_KEY;
	InputKeyType = OPR_NO_KEY;

	/** キー入力禁止を解除する */
	OPR_InhibitKeyScan = 0;

	/** キースキャンタスクからのメッセージ受信待ち */
	rcv_msg(mbxno.OPR_Task, &rx_message);
	item = rx_message->Item;
	message = rx_message->Message;
	submessage = rx_message->SubMessage1;

	/** キータイマータスクを消去する */
	if (tskno_OPR_KeyTimerTask != 0xffff) {
		del_tsk(&tskno_OPR_KeyTimerTask);
	}

	switch (item) {
	case FROM_KEYSCAN:				/** 受信したメッセージがキースキャンタスクからのメッセージである */
		/** チャイルド表示中であれば止める */
		StopChildDisplay();
#if (PRO_CONT_KEY_INPUT == ENABLE)
		/* 連続入力中（キーが押しっぱなし）の時は、うるさいのでアックブザーを鳴らさない */
		if (ContinuousKeyHit == FALSE) {
			/** アックブザーを鳴らす */
			AckBuzzer();
		}
#else
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
		if (SYS_KeyTouchFrequencySetting == 0) {	/* キータッチ音色設定オペレーション中でない時はアックブザーを鳴らす。 */
			/** アックブザーを鳴らす */
			AckBuzzer();
		}
 #else
		/** アックブザーを鳴らす */
		AckBuzzer();
 #endif
#endif

		/** 入力されたキーをセット */
		InputKeyCode = (UBYTE)message;
		InputKeyType = (UBYTE)submessage;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
		if (SYS_KeyTouchFrequencySetting == 1) {	/* キータッチ音色設定オペレーション中 */
			if ((InputKeyCode == CURSOR_LEFT_KEY) || (InputKeyCode == FUNCTION_KEY )) {
				SYS_AckBuzzerFlag = 1;	/* AckBuzzerをOFFに */
			}
		}
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Added by SMuratec L.Z.W 2003/07/31 */
		if (IsDocumentSet && (!CHK_ReadyModeCopy())) {	/* ファクスモードの時			*/
			if (InputKeyCode == SET_KEY) {	/* セットキーが押された時			*/
				InputKeyCode = CONTRAST_KEY;	/* 濃度キーをセット */
				InputKeyType = SINGLE;		/* 単一オペレーションキーをセット */
			}
			if (InputKeyCode == CLEAR_KEY) {	/* クリアキーが押された時			*/
				InputKeyCode = MODE_KEY;	/* 画質キーをセット */
				InputKeyType = SINGLE;		/* 単一オペレーションキーをセット */
			}
		}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
		if ((InputKeyType == SINGLE)	/* 単一オペレーションキーが押された時	*/
		 && (IsSingleKeyOperation)) {	/* 単一オペレーションが有効な時			*/
			SingleKeyOperation(InputKeyCode);
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1997/11/20 */
		/* ファクスモードでは、縮小キーを済みスタンプキーとして使用する場合、キーの値を直接ここで変更します
		** （ソートキー等のように、キーの値を同じにすると、キータイプにより処理を行うswitch文で、
		** 　縮小キーと単一オペレーションキーが同時に存在する場合があり、そのままではコンパイル
		** 　できなくなるので、この場合だけ仕方なく方法を変えます）
		*/
		if ((InputKeyCode == REDUCTION_KEY)	/* 縮小キーが押された時			*/
		 && (!CHK_ReadyModeCopy())			/* ファクスモードの時			*/
		 && (CHK_UNI_StampKeyEnable())) {	/* 済みスタンプキーが有効な時	*/
			InputKeyCode = STAMP_KEY;	/* 済みスタンプキーをセット */
			InputKeyType = SINGLE;		/* 単一オペレーションキーをセット */
		}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/27 */
		/* 濃度設定中に左右の矢印キーが押されたら、濃度キーが押された時と同じパスを通って濃度が変更できるように、
		** ここでキーの値を直接変更します（あまり好ましい方法では無いが、左右の矢印キーをそのまま使用しようとすると、
		** 濃度表示中のフラグの初期化等、変更が大変困難になるので仕方なくこうしました）
		*/
		if (IsSettingDensity) {	/* 濃度設定中の時 */
			switch (InputKeyCode) {
			case CONTRAST_KEY:		/* 濃度キー */
				OPR_ChangeDensityKey = InputKeyCode;
				break;
			case CURSOR_LEFT_KEY:	/* 左矢印キー */
				OPR_ChangeDensityKey = InputKeyCode;
				InputKeyCode = CONTRAST_KEY;	/* 濃度キーをセット */
				InputKeyType = SINGLE;			/* 単一オペレーションキーをセット */
				break;
			case FUNCTION_KEY:		/* 右矢印キー */
				OPR_ChangeDensityKey = InputKeyCode;
				InputKeyCode = CONTRAST_KEY;	/* 濃度キーをセット */
				InputKeyType = SINGLE;			/* 単一オペレーションキーをセット */
				break;
			default:
				/* 濃度変更以外の時は、濃度設定中をＯＦＦにします */
				IsSettingDensity = FALSE;
				break;
			}
		}
#endif
		break;

	case FROM_ONETOUCH_SHEET_CHECK:	/** ワンタッチシート切り替えタスクからの場合 */
		InputKeyCode = (UBYTE)OPR_SHEET_CHANGE;
		InputKeyType = (UBYTE)NO_EFFECT;
		break;

	case FROM_10MS_TIMER:			/** 受信したタスクがタイマータスクからの場合 */
#if (PRO_COPY_FAX_MODE == ENABLE)
		/* コピーパラメーター優先表示のタイマーは、コピーモードでパラメーターが変更される度に起動しているので、
		** 例えば、部数入力後に濃度キーを押すとチャイルド表示のタイムオーバーより先に、コピーパラメーター優先表示
		** のタイムオーバーが起こるために、無条件にチャイルド表示を止めると、濃度設定表示が早く消えてしまいます
		*/
		if (message != MSG_PARAM_DISP_TIMEUP) {	/* コピーパラメーター優先表示のタイムオーバー以外の時 */
			/** チャイルド表示中なら止める */
			StopChildDisplay();
		}
#else
		/** チャイルド表示中なら止める */
		StopChildDisplay();
#endif

		switch (message) {
		case MSG_GET_KEY_TIMEUP:	/** キー待ちのタイムオーバーの時 */
			InputKeyCode = (UBYTE)OPR_GET_KEY_TIMEUP;	/* キーコードにキー待ちタイムアップをセット */
			InputKeyType = (UBYTE)KEY_TIME_UP;
			break;
		case MSG_CHILD_TIMEUP:		/** チャイルド表示のタイムオーバーの時 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/25 */
			/* チャイルド表示がタイムアップした時には、濃度表示のタイムアップの場合も含まれているので、
			** ここで濃度設定中をＯＦＦにします
			** 注）完了表示等のタイムアップの時に、余分な処理は増えますが、チャイルド表示が重複している
			** 　　ことはありえないので、特に条件がなくても問題はありません
			** 　　（条件を追加しようとすると変更が多くなるので、こうしました）
			*/
			IsSettingDensity = FALSE;
#endif
			InputKeyCode = (UBYTE)OPR_CHILD_TIMEUP;		/* キーコードにチャイルド表示タイムアップをセット */
			InputKeyType = (UBYTE)NO_EFFECT;
			break;
#if (PRO_COPY_FAX_MODE == ENABLE)
		case MSG_PARAM_DISP_TIMEUP:	/** コピーパラメーター優先表示のタイムオーバーの時 */
			/* コピーパラメーター優先表示を止めます */
			StopParamDispTask();
			InputKeyCode = (UBYTE)OPR_PARAM_DISP_TIMEUP;/* キーコードにコピーパラメーター優先表示タイムアップをセット */
			InputKeyType = (UBYTE)NO_EFFECT;
			break;
#endif
		default:
			break;
		}
		break;

	case FROM_MAIN:					/** メインタスクからのメッセージの場合 */
		/** チャイルド表示中でも止めない */

		/** 電話状態変化の場合 */
		if (message == MSG_TEL_FROM_MAIN) {
			InputKeyCode = (UBYTE)OPR_TEL_OPERATION;		/* キーコードに電話状態変化をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/14 */
		else if (message == MSG_SHIREI_ON) {
			InputKeyCode = (UBYTE)OPR_NO_KEY;
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#endif		/* End of (defined (KEISATSU)) */
		/** メモリーオーバー発生の場合 */
		else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER_OPR) {
			InputKeyCode = (UBYTE)OPR_MEMORY_OVER_OPR;		/* キーコードにメモリーオーバー処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
		/** ジャムリカバーオペレーション実行の場合 */
		else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR) {
			InputKeyCode = (UBYTE)OPR_JAM_RECOVER_OPR;		/* キーコードにジャムリカバー処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
		/** ＦＢＳ読み取り中断リカバーオペレーション実行の場合 */
		else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR) {
			InputKeyCode = (UBYTE)OPR_JAM_RECOVER_OPR;		/* キーコードにジャムリカバー処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#if (PRO_FBS == ENABLE)
		/** 次原稿蓄積確認の場合 */
		else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR) {
			InputKeyCode = (UBYTE)OPR_NEXT_DOC_STORED_OPR;	/* キーコードに次原稿蓄積確認処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#endif
#if (PRO_CIPHER == ENABLE)
		/** 復号化時キー間違いの場合 */
		else if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_WRONG_KEY_ERROR) {
			InputKeyCode = (UBYTE)OPR_DIFFERENT_KEY_OPR;	/* キーコードに復号化時キー間違い処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
		/** 受信暗号化原稿消去確認の場合 by K.Watanabe 1998/07/08 */
		else if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_FIRST_PAGE) {
			InputKeyCode = (UBYTE)OPR_RX_ERASE_CIPHER_DOC_OPR;	/* キーコードに受信暗号化原稿消去確認処理をセット */
			InputKeyType = (UBYTE)NO_EFFECT;
		}
#endif
		break;
	}
}

/*************************************************************************
	module		:[入力されたキーコードを返す]
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
	date		:[1995/11/21]
	author		:[江口]
*************************************************************************/
UBYTE GetInputKeyCode(void)
{
	return (InputKeyCode);
}

/*************************************************************************
	module		:[入力されたキータイプを返す]
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
	date		:[1995/11/21]
	author		:[江口]
*************************************************************************/
UBYTE GetInputKeyType(void)
{
	return (InputKeyType);
}

/*************************************************************************
	module		:[キースキャンタスク]
	function	:[
		1.10msecタイマー割り込みで発行されるイベントをまつ。
		2.イベントをうけたらキーコードを計算してオペレーションタスクにメッセージとして送信する。
		3.イベントをうけたらキーコードを計算する前にキー入力禁止にしておく。
	]
	return		:[なし]
	common		:[
		OPR_InhibitKeyScan
		KeyPortTable
		KeyPortNumber
		KeyPortTable
		KeyTypeTable
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/28]
	author		:[江口]
*************************************************************************/
void OPR_KeyTask(void)
{
	UBYTE	bit;
	UWORD	keycode;	/* キーコード */
	UWORD	keytype;	/* キータイプ */
	MESSAGE_t	tx_message;
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
	UBYTE	row, col;
#endif

	tx_message.Item = FROM_KEYSCAN;

	while (1) {
		/** タイマー割り込みからのキー入力のイベント待ち */
		wai_evt(EVT_KEY_DECIDE);

		/** キー入力禁止フラグをセットする（タイマー割り込みのキースキャンを止める） */
		OPR_InhibitKeyScan = 1;

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
 #if (1)	/* Change By H.Fujimura 1999/01/06 */
		row = NewKeyData / 8;	/* ROWの取り出し */
		col = NewKeyData % 8;	/* COLの取り出し */
 #else
//		row = ((NewKeyData & 0x78) >> 3) - 1;	/* ROWの取り出し */
//		col = (NewKeyData & 0x07);		/* COLの取り出し */
 #endif
		keycode = (UWORD)KeyTableSheet1[row][col];
		keytype = (UWORD)KeyTypeTable1[row][col];
		tx_message.Message = keycode & 0x00FF;		/* 符号拡張されて上位バイトが0xFFになるのを防ぐため */
		tx_message.SubMessage1 = keytype & 0x00FF;	/* メッセージを受ける方で下位バイトのみ参照していたらこの処理はいらんが念のため */

		/** オペレーションタスクにメッセージを送信する */
		snd_msg(mbxno.OPR_Task , &tx_message);
#else
		/** キーポート番号とポートの状態から、キーコードを計算する */
		bit = GetKeyPortBit();

		if (bit != 8) {
			/** ANZUはワンタッチキーがシート切り替えなのでシートの状態もふまえてキーコードを得る */
			if (OnetouchSheetStatus == ONETOUCH_SHEET1) {
				keycode = (UWORD)KeyTableSheet1[KeyPortNumber][bit];
				keytype = (UWORD)KeyTypeTable1[KeyPortNumber][bit];
			}
			else {
				keycode = (UWORD)KeyTableSheet2[KeyPortNumber][bit];
				keytype = (UWORD)KeyTypeTable2[KeyPortNumber][bit];
			}

			tx_message.Message = keycode & 0x00FF;		/* 符号拡張されて上位バイトが0xFFになるのを防ぐため */
			tx_message.SubMessage1 = keytype & 0x00FF;	/* メッセージを受ける方で下位バイトのみ参照していたらこの処理はいらんが念のため */

			/** オペレーションタスクにメッセージを送信する */
			snd_msg(mbxno.OPR_Task , &tx_message);
		}
		else {	/* 非常用の処理 */
			/* キー入力のイベントが発生したのに、ポートの値がくさっているような *
			 * ときがあった場合、キー入力禁止フラグがたったままなのでその後、キー*
			 * が効かなくなってしまうので一応、保険の処理をいれておく */
			 /* ここにくるのはあまり好ましい状態ではない */
			OPR_InhibitKeyScan = 0;
		}
#endif
	}
}


/*************************************************************************
	module		:[キーテーブルの行番号を求める]
	function	:[
		1.キーポートの何ビット目が０になっているか調べる。
		2.この関数で返す値がそのままキーテーブルの行番号に相当する。
	]
	return		:[
		０になっているビット:０～７
		　異常な値:８
	]
	common		:[NewKeyCode]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/06]
	author		:[江口]
*************************************************************************/
UBYTE GetKeyPortBit(void)
{
	UBYTE	bit;

	for (bit = 0; bit < 8; bit++) {	/* ＬＳＢからＭＳＢまで */
		/* ビットのＯＮ／ＯＦＦを調べる */
		if ((NewKeyCode & (0x01 << bit)) == 0) {	/* BITがOFF->キーが押されている */
			break;
		}
	}
	return (bit);
}

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
void OPR_CheckOnetouchSheetTask(void)
{
	/* dummy */
}
#else
/*************************************************************************
	module		:[ワンタッチのシート状態を調べる]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		シート状態確定。
		ビットが０：シート1　ビットが１：シート0 :一応最終確認はしとかなあかん.1996/04/26

		 このタスクはキースキャンタスクより先にクリエイトされなくてはならない
		 (シート状態を確定するため）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/21]
	author		:[江口]
*************************************************************************/
void OPR_CheckOnetouchSheetTask(void)
{
	/* 50msecに一回シートの状態をチェックするタスク */
	UBYTE	new_sheet_status;
	UBYTE	old_sheet_status;
	UBYTE	sheet_change;
	UBYTE	timer;
/* #if (PRO_KEYPANEL == PANEL_ANZU_L) ATLANTA共通で入れます T.Nose 1998/04/30 */
	UWORD	io_wait;
/* #endif */
	MESSAGE_t	tx_message;

	new_sheet_status = sheet_change = timer = 0;

	/* 電源たち上げ１発目の状態を得る */
#if (PRO_CPU == SH7043)
	/* キーポートをリードするときだけ７ウェイトにする
	** ANZU_Lのみの処理でしたがATLANTA共通で入れます
	** T.Nose 1998/04/30
	*/
	CMN_DisableInterrupt(); /* 割込み禁止追加 T.Nose 1998/04/30 */
	io_wait = CMN_CheckSH_WCR1_CS3();
	CMN_SetSH_WCR1_CS3(7);
 #if (PRO_KEYPANEL == PANEL_ANZU_L) /* ポートがポプラと異なるため */
	old_sheet_status = (UBYTE)(inpw(SHEET_PORT) & IO_BIT_SHEET_CHANGE);
 #else	/* POPLAR */
	old_sheet_status = (UBYTE)(inpw(KEY0_PORT) & IO_BIT_SHEET_CHANGE);
 #endif
	CMN_SetSH_WCR1_CS3(io_wait);
	CMN_EnableInterrupt();
#endif

	/* シート状態を保持する変数を初期化する */
	if (old_sheet_status) {
		OnetouchSheetStatus = ONETOUCH_SHEET1;
	}
	else {
		OnetouchSheetStatus = ONETOUCH_SHEET2;
	}

	while (1) {
		/* とりあえず５０msecに一回とする */
		/* チャタリングの検出時間によってはもっと短くする必要あり */
		wai_tsk(5);

		/* シート切り替えのポートを調べる */
#if (PRO_CPU == SH7043)
		/* キーポートをリードするときだけ７ウェイトにする
		** ANZU_Lのみの処理でしたがATLANTA共通で入れます
		** T.Nose 1998/04/30
		*/
		CMN_DisableInterrupt();
		io_wait = CMN_CheckSH_WCR1_CS3();
		CMN_SetSH_WCR1_CS3(7);
 #if (PRO_KEYPANEL == PANEL_ANZU_L) /* ポートがポプラと異なるため */
		new_sheet_status = (UBYTE)(inpw(SHEET_PORT) & IO_BIT_SHEET_CHANGE);
 #else	/* POPLAR */
		new_sheet_status = (UBYTE)(inpw(KEY0_PORT) & IO_BIT_SHEET_CHANGE);
 #endif
		CMN_SetSH_WCR1_CS3(io_wait);
		CMN_EnableInterrupt();
#endif

		if (new_sheet_status != old_sheet_status) {	/* シート状態が変わった */
			timer = 0;
			sheet_change = 1;
			old_sheet_status = new_sheet_status;
		}
		else {										/* シート状態が変わっていない */
			if (sheet_change == 1) {	/* シート状態変化 */
				timer++;
				if (timer > SHEET_SWITCH_CHATTERING_TIME) {
					/* シート切り替えとみなす */
					/* シート状態更新*/
					if (new_sheet_status) {
						OnetouchSheetStatus = ONETOUCH_SHEET1;
					}
					else {
						OnetouchSheetStatus = ONETOUCH_SHEET2;
					}
					timer = 0;
					sheet_change = 0;
					old_sheet_status = new_sheet_status;

					/* メッセージ送信 */
					/* このメッセージは名前入力時のモード切り替えに必要なため送信する */
					tx_message.Item = FROM_ONETOUCH_SHEET_CHECK;
					tx_message.Message = MSG_ONETOUCH_SHEET_CHANGE;
					snd_msg(mbxno.OPR_Task, &tx_message);
				}
			}
			else {
				timer = 0;
				sheet_change = 0;
				old_sheet_status = new_sheet_status;
			}
		}
	}
}
#endif


/*************************************************************************
	module		:[ワンタッチシート状態]
	function	:[
		1.
	]
	return		:[
		ONETOUCH_SHEET1:シート１（大文字）
		ONETOUCH_SHEET2:シート２（小文字）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/13]
	author		:[江口]
*************************************************************************/
UBYTE GetOnetouchSheetStatus(void)
{
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
	return (ONETOUCH_SHEET1);
#else
	return (OnetouchSheetStatus);
#endif
}

/*************************************************************************
	module		:[アックブザー鳴動]
	function	:[
		1.アックブザーを鳴らすためのデータをセットしてブザータスクにメッセージ
		　を送信する
	]
	return		:[なし]
	common		:[mbxno]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void AckBuzzer(void)
{
	MESSAGE_t	buzz_type;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
	if (SYS_AckBuzzerFlag == 1) {	/*	アックブザーOFFに設定されていたら  2001/08/08 T.Takagi*/
		return;
	}
#endif
	buzz_type.Message = ACK_BUZZER;
	snd_msg(mbxno.CMN_BuzzerTask, &buzz_type);
}

/*************************************************************************
	module		:[ナックブザー鳴動]
	function	:[
		1.
	]
	return		:[]
	common		:[mbxno]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/18]
	author		:[江口]
*************************************************************************/
void NackBuzzer(void)
{
	MESSAGE_t	buzz_type;

	buzz_type.Message = NACK_BUZZER;
	snd_msg(mbxno.CMN_BuzzerTask, &buzz_type);
}
