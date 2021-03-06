/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SPD.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 短縮ダイアルオペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Prototype
void	EnterSpeedDial(void);
void	EraseSpeedDial(void);
void	PrintSpeedDialList(void);
UBYTE	SelectSpeedNumber(void);
UBYTE	InputSpeedOptionalNumber(void);
void	SpeedForwordOperation(void);
void	SpeedBackOperation(void);
void	SpeedOperationInitial(void);
void	SpeedSelectDisplay(void);
void	SpeedSelectOptionalDisplay(void);
UWORD	GetRecordFromNumber(UWORD);
UBYTE	SetOptionalSpeedStatus(UWORD);
UBYTE	GetSpeedEntryCount(void);
UBYTE	GetSpeedDialRecord(void);
void	SetSpeedControlTable(void);
void	DeleteSpeedControlTable(void);
UBYTE	CheckSpeedStoreStatus(UBYTE);
*/

/*************************************************************************
	module		:[短縮ダイヤル登録機能]
	function	:[
		1.短縮ダイヤル登録の機能を実行する
		2.任意短縮番号選択での直接入力のみの表示は最初だけ
		  ２度目以降は普通の短縮番号選択画面と同じ
	]
	common		:[]
	condition	:[]
	comment		:[
		内部から見た短縮番号 000〜
		外部から見た短縮番号 001〜
		内部処理ではワンタッチ短縮を１続きのデータと考え
		SYS_ONETOUCH_MAX 〜 SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1が短縮000〜169として処理
		ダイアルデータの登録等の下位モジュールはOPR_DIAL.Cにまとめてある
		ワンタッチ＋短縮が２５５を越える場合、作り替える必要あり
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/19]
	author		:[江口]
*************************************************************************/
void EnterSpeedDial(void)
{
	SpeedOperationInitial();

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
		if (InputSpeedOptionalNumber() == OPR_END) { /* ＳＴＯＰ */
			return;
		}
	}
	/* 短縮番号選択ループ*/
	while (1) {
		/** 登録短縮ダイヤルを選択する */
		if (SelectSpeedNumber() == OPR_END) { /* ＳＴＯＰ */
			return;
		}
		/** 短縮ダイアルデータセットを行う */
		if (OnetouchSpeedInput() == OPR_END) { /* ＳＴＯＰ */
			return;
		}

		/* 次の登録に備えて短縮番号を進める */
		SpeedForwordOperation();
	}
}

/*************************************************************************
	module		:[短縮消去オペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-B2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口]
*************************************************************************/
void EraseSpeedDial(void)
{
	UBYTE	speed_number;	/* 選択された短縮番号 */
	UBYTE	erase_step;		/* 消去段階 */

	speed_number = 0;
	erase_step = ERASE_ITEM_SELECT_STEP;
	SpeedOperationInitial();

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
		if (InputSpeedOptionalNumber() == OPR_END) { /* ＳＴＯＰ */
			return;
		}
	}

	while (1) {
		switch (erase_step) {
		case ERASE_ITEM_SELECT_STEP:	/* 選択状態 */
			if (SelectSpeedNumber() == OPR_END) { /* ＳＴＯＰ */
				return;
			}
			speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
			if (CheckSpeedStoreStatus(speed_number) == OK) {
				erase_step = ERASE_CONFIRM_STEP;
			}
			else {
				NackBuzzer();
			}
			break;
		case ERASE_CONFIRM_STEP:	/* クリア確認状態 */
			switch (ConfirmKeyInputOperation((UBYTE *)D2W_EraseSpeedDial, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
			case CONFIRM_EXEC:	/* 実行 */
				/* 短縮消去実行 */
				ClearOnetouchSpeedRecord(&SYB_SpeedDial[speed_number]);
				DeleteTelBookData(OPR_Buf.OntchSpdCtrl.SelectNumber);   /* 電話帳からも削除 */
				if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* 任意短縮の時 */
					DeleteSpeedControlTable();
				}
				/* ダイレクトメール防止機能用処理（登録したﾀﾞｲﾔﾙの下４桁のみ別ﾊﾞｯﾌｧに格納） by K.Watanabe 1997/10/22 */
				SYB_SpeedJunkDial[speed_number] = PickOutLastFourFigure(SYB_SpeedDial[speed_number].Dial, 40);
				erase_step = ERASE_COMPLETE_STEP;
				break;
			case CONFIRM_ABORT:	/* 取り消し */
				erase_step = ERASE_ITEM_SELECT_STEP;
				break;
			case OPR_END:		/* 中止・タイムアップ */
				return;	
			default:
				break;
			}
			break;
		case ERASE_COMPLETE_STEP:	/* 消去完了表示 */
			if (ClearCompleteDisplayOperation((UBYTE *)D2W_EraseSpeedDial) == OPR_CONTINUE) {
				erase_step = ERASE_ITEM_SELECT_STEP;
				SpeedForwordOperation();
			}
			else {
				return;
			}
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[短縮ダイアルリスト]
	function	:[
		1.短縮ダイアルリストの印字の起動をかける
		2.短縮ダイアルが登録されている必要がある
	]
	return		:[]
	common		:[SYB_SpeedDial]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintSpeedDialList(void)
{
	UBYTE	speed_number;	/*短縮ﾀﾞｲﾔﾙ番号*/

	for (speed_number = 0; speed_number < SYS_SPEED_DIAL_MAX; speed_number++ ){
		if (CheckSpeedStoreStatus(speed_number) == OK) {	/* 登録済み */
			FinalListPrintOperation(LST_SPEEDDIAL_LIST);	/* メインにリスト起動メッセージ送信 */
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[短縮番号選択]
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
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE SelectSpeedNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	record_no;
	UWORD	speed_number;

	while (1) {
		SpeedSelectDisplay();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);
		case ENTER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				NackBuzzer();
			}
			else {
				if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* 任意短縮の時 */
					record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
					if( record_no != 0xff ){		/* 任意短縮番が存在する時 */
						OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
					}
					else{
						/** 件数がオーバーしていないかチェック */
						if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
							NackBuzzer();
							OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
							return(OPR_END);
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
							OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
						}
					}
				}
				return (OPR_CONTINUE);
			}
			break;
		case FUNCTION:
			/* 短縮番号を進める */
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* 短縮番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				SpeedForwordOperation();
			}
			break;
		case LEFT_ARROW:
			/* 短縮番号を戻す */
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* 短縮番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				SpeedBackOperation();
			}
			break;
		case CLEAR:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {/*短縮番号入力中 */
				/* 短縮入力バッファのデータを１文字クリア */
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition--;
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {	/* 桁数オーバー(あり得ない) */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition++] = key;
				if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {
					speed_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
														 OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
					if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* 任意短縮の時 */
						if( speed_number > OPR_OPTIONAL_SPEED_MAX ){
							NackBuzzer();
							break;
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = speed_number;
						}
						record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
						if( record_no != 0xff ){		/* 任意短縮番が存在する時 */
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
						}
						else{
							/** 件数がオーバーしていないかチェック */
							if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
								NackBuzzer();
								OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
								return(OPR_END);
							}
							else{
								OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
								OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
							}
						}
					}else{										/* 通常の短縮の時 */
						if ((speed_number < OPR_SPEED_DIAL_MIN) ||		/* 表示は１から */
						    (speed_number > SYS_SPEED_DIAL_MAX)){
							NackBuzzer();
						}
						else {
							OPR_Buf.OntchSpdCtrl.SelectNumber
							= (UWORD)((speed_number - OPR_SPEED_DIAL_MIN) + SYS_ONETOUCH_MAX);
						}
					}
					CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
					OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
				}
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
	}
}

/*************************************************************************
	module		:[短縮番号入力(任意短縮用)]
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
	date		:[1997/04/01]
	author		:[桑原美紀]
*************************************************************************/
UBYTE InputSpeedOptionalNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	record_no;
	UWORD	option_number;

	while (1) {
		SpeedSelectOptionalDisplay();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);
		case ENTER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition <= 0) {
				NackBuzzer();
			}
			else{
				option_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
													  OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
				if( option_number > OPR_OPTIONAL_SPEED_MAX ){
					NackBuzzer();
				}
				else{
					OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = option_number;
				}
				CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
				return (OK);
			}
			break;
		case FUNCTION:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* 短縮番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
				return (OPR_CONTINUE);
			}
			break;
		case LEFT_ARROW:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* 短縮番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 999;
				return (OPR_CONTINUE);
			}
			break;
		case CLEAR:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {/*短縮番号入力中 */
				/* 短縮入力バッファのデータを１文字クリア */
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition--;
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {	/* 桁数オーバー(あり得ない) */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition++] = key;
				if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {
					option_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
														  OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
					if( option_number > OPR_OPTIONAL_SPEED_MAX ){
						NackBuzzer();
						break;
					}
					else{
						OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = option_number;
					}
					record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
					/** 短縮データに対応するレコード番号をセット **/
					if( record_no != 0xff ){		/* 任意短縮が存在する時 */
						OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
					}
					else{
						/** 件数がオーバーしていないかチェック */
						if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
							NackBuzzer();
							OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
							return(OPR_END);
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
							OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
						}
					}
					CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
					OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
					return( OPR_CONTINUE );
				}
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
	}
}

/*************************************************************************
	module		:[短縮番号をすすめる]
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
	date		:[1995/04/14]
	author		:[江口]
*************************************************************************/
void SpeedForwordOperation(void)
{
	/* 最後までいったら戻す */
	if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
		if (OPR_Buf.OntchSpdCtrl.SelectNumber == SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1) {
			OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectNumber++;
		}
	}
	else{	/* 任意短縮の時 */
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber == OPR_OPTIONAL_SPEED_MAX ){
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber++;
		}
	}
}

/*************************************************************************
	module		:[短縮番号を戻す]
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
	date		:[1995/04/14]
	author		:[江口]
*************************************************************************/
void SpeedBackOperation(void)
{
	/* 先頭まできたら最後にする(回る) */
	if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
		if (OPR_Buf.OntchSpdCtrl.SelectNumber == SYS_ONETOUCH_MAX) {
			OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectNumber--;
		}
	}
	else{	/* 任意短縮の時 */
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber == 0 ) {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = OPR_OPTIONAL_SPEED_MAX;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber--;
		}
	}
}

/*************************************************************************
	module		:[短縮オペレーション初期化]
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
	date		:[1995/07/17]
	author		:[江口]
*************************************************************************/
void SpeedOperationInitial(void)
{
	/* 短縮番号表示用バッファを作成(短縮番号はまだ)*/
	CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer, 5, NULL);	/*とりあえずクリアしておく*/
	OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[SPEED_FIGURE_MAX] = ':';

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');		/* 上段表示文字列を初期化 */
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');		/* 下段表示文字列を初期化 */
	CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4, NULL);	/* 短縮番号入力用バッファを初期化 */
	OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;						/* 短縮番号入力位置を初期化 */
	OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX;
	OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
}

/*************************************************************************
	module		:[短縮ダイヤル選択表示]
	function	:[短縮ダイヤルの選択表示を行う。]
	return		:[なし]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[短縮番号は１から表示する]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
void SpeedSelectDisplay(void)
{
	/* 上段「Select Speed Dial   」*/
	/* 下段「001:No Stored       」「001:1234456789      」「12                 」*/

	UBYTE	speed_number;

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/17 */
	UBYTE	kei_pos;
#endif		/* End of (defined (KEISATSU)) */

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_InputSpeedDialNumber);		/*"ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ"*/

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/** 通常入力中 */
	if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition == 0) {
		/* 注）表示は001から始める */
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮 */
			speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
			CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
								 speed_number + OPR_SPEED_DIAL_MIN,
								 SPEED_FIGURE_MAX,
								 '0');
		}
		else{			/* 任意短縮の時 */
			speed_number = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
			CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
								 OPR_Buf.OntchSpdCtrl.SelectOptionalNumber,
								 SPEED_FIGURE_MAX,
								 '0');
		}
		OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[SPEED_FIGURE_MAX] = ':';
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);
		/* 短縮ダイアル設定状況を調べる */
		if ((CheckSpeedStoreStatus(speed_number) == OK) && (speed_number != 0xFF)) {	/* セット済み */
			/** ダイアル番号を取り出し、ASCIIになおして表示バッファにコピー*/

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/17 */
 /* 警察設定表示 */
		 	kei_pos = SPEED_FIGURE_MAX + 1;
			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KEIDEN){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｹ", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KANYU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｶ", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_ISSEI){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｲ", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KOBETSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｺ", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "S", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "N", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KYOTSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｷ", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SENYO){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｾ", 1);
				kei_pos++;
			}

			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[kei_pos],
									&SYB_SpeedDial[speed_number].Dial[0],
									(UBYTE)(OPR_DISPLAY_MAX - kei_pos));
#else
			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[SPEED_FIGURE_MAX + 1],
									&SYB_SpeedDial[speed_number].Dial[0],
									(UBYTE)(OPR_DISPLAY_MAX - SPEED_FIGURE_MAX - 1));
#endif 		/* End of (defined (KEISATSU)) */

		}
		else { /* セットされていない */
			CMN_StringCopy(&FunctionDisplayBufferLow[SPEED_FIGURE_MAX + 1], D2W_NoNumberStored);
		}
	}
	else {
		CMN_StringCopy(&FunctionDisplayBufferLow[0], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(FunctionDisplayBufferLow);
#endif
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[短縮ダイヤル選択表示(短縮番号登録画面)]
	function	:[短縮ダイヤルの選択表示を行う。]
	return		:[なし]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/04/01]
	author		:[桑原美紀]
*************************************************************************/
void SpeedSelectOptionalDisplay(void)
{
	UBYTE	speed_number;
	UBYTE	entry_count;	/* 現在短縮登録数 */
	UWORD	option_number;	/* 任意短縮用 */

	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_InputSpeedDialNumber);			/*"ﾀﾝｼｭｸ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ"*/

	CMN_StringCopy(FunctionDisplayBufferLow,D2W_SelectOptionalSpeedNumber);	/*"   /     (0-999):   "*/

	entry_count = GetSpeedEntryCount();						/* 現在短縮登録数 */
	CMN_UnsignedIntToASC_NULL(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
							  entry_count,
							  SPEED_FIGURE_MAX,
							  '0');
	CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);

	CMN_UnsignedIntToASC_NULL(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,	/* 最大短縮登録数 */
							  SYS_SPEED_DIAL_MAX,
							  SPEED_FIGURE_MAX,
							  '0');
	CMN_StringCopy(&FunctionDisplayBufferLow[4], OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);

	if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition == 0) {	/* 数値入力中 */
		CMN_StringCopy(&FunctionDisplayBufferLow[17], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}
	else{
		speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
		option_number = GetRecordFromNumber(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
		CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
							 option_number,
							 SPEED_FIGURE_MAX,
							 '0');
		CMN_StringCopy(&FunctionDisplayBufferLow[17], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CharacterInput.LcdDisplayPosition = 18;
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD
					 + OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition
					 + CharacterInput.LcdDisplayPosition
					 - 1));
}

/*************************************************************************
	module		:[短縮番号に対応する発信用短縮番号を検索する]
	function	:[
		1.
	]
	return		:[	0xFFFF    :	登録データ無し
					0xFFFF以外:	登録有り
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/31]
	author		:[桑原美紀]
*************************************************************************/
UWORD GetRecordFromNumber(UWORD record)
{
	UBYTE count;
	UBYTE rcd_no;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		rcd_no = SYB_OptionalSpeed[count].Record;
		if (record == rcd_no) {
			return(SYB_OptionalSpeed[count].Number);
		}
		else if (rcd_no == 0xFF) {
			break;
		}
	}
	return(0xFFFF);
}

/*************************************************************************
	module		:[任意短縮時のダイヤルレコードオフセットのセット]
	function	:[
	]
	return		:[
				  ]
	common		:[	SYS_SpeedDial[].Dial[]
	]
	condition	:[]
	comment		:[任意短縮番号仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1997/04/01]
	auther		:[桑原美紀]
*************************************************************************/
UBYTE SetOptionalSpeedStatus(UWORD optional_no)	/* 発信用任意短縮番号 */
{
	UBYTE count;
	UBYTE record_no;
	UWORD opt_no;

	record_no	= 0xFF;
	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		opt_no = SYB_OptionalSpeed[count].Number;
		if (optional_no == opt_no) {
			record_no = SYB_OptionalSpeed[count].Record;
			break;
		}
		else if (opt_no == 0xFFFF) {
			break;
		}
	}
	return( record_no );
}

/*************************************************************************
	module		:[現在の短縮登録数の取得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[任意短縮番号仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1997/04/01]
	auther		:[桑原美紀]
*************************************************************************/
UBYTE GetSpeedEntryCount(void)
{
	UBYTE	count;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		if (SYB_OptionalSpeed[count].Number == 0xFFFF) {
			break;
		}
	}
	return(count);
}

/*************************************************************************
	module		:[ダイヤルデータを登録する短縮ダイヤルレコードを獲得する]
	function	:[
		1.
	]
	return		:[短縮ダイヤルのレコード番号]
	common		:[SYB_SpeedDial.Dial]
	condition	:[]
	comment		:[任意短縮番号仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/02]
	author		:[桑原美紀]
*************************************************************************/
UBYTE GetSpeedDialRecord(void)
{
	UBYTE count;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		/* リモート診断では、ダイヤル番号消去で 0xF0を書くので、判断を変更します 1998/04/01 by K.Watanabe */
/*		if (SYB_SpeedDial[count].Dial[0] == 0xFF) {*/
		if ((SYB_SpeedDial[count].Dial[0] & 0xF0) == 0xF0) {
			return(count);
		}
	}
	return(count);
}

/*************************************************************************
	module		:[短縮番号管理テーブルへの登録を行う]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		SYS_OptionalSpeed.Number
		SYS_OptionalSpeed.Record
		OPR_Buf.OntchSpdCtrl.SelectOptionalNumber
		OPR_Buf.OntchSpdCtrl.SelectNumber
	]
	condition	:[]
	comment		:[任意短縮番号仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/02]
	author		:[桑原美紀]
*************************************************************************/
void SetSpeedControlTable(void)
{
	UBYTE input_pos;
	UBYTE move_point;

	for (input_pos = 0; input_pos < SYS_SPEED_DIAL_MAX; input_pos++) {
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber < SYB_OptionalSpeed[input_pos].Number) {
			for (move_point = (UBYTE)(SYS_SPEED_DIAL_MAX - 1); move_point >= 0; move_point--) {
				if (SYB_OptionalSpeed[move_point].Number != 0xFFFF) {
					if (move_point < (UBYTE)(SYS_SPEED_DIAL_MAX - 1)) {
						SYB_OptionalSpeed[move_point + 1].Number = SYB_OptionalSpeed[move_point].Number;
						SYB_OptionalSpeed[move_point + 1].Record = SYB_OptionalSpeed[move_point].Record;
					}
				}
				if (move_point == input_pos) {
					SYB_OptionalSpeed[move_point].Number = OPR_Buf.OntchSpdCtrl.SelectOptionalNumber;
					SYB_OptionalSpeed[move_point].Record = 
								(UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
					return;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[短縮番号管理テーブルからの削除を行う]
	function	:[
		1.
	]
	return		:[無し]
	common		:[
		SYS_OptionalSpeed.Number
		SYS_OptionalSpeed.Record
		OPR_Buf.OntchSpdCtrl.SelectOptionalNumber
	]
	condition	:[]
	comment		:[任意短縮番号仕様]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/01]
	author		:[桑原美紀]
*************************************************************************/
void DeleteSpeedControlTable(void)
{
	UBYTE serach;
	UBYTE move_point;

	for (serach = 0; serach < SYS_SPEED_DIAL_MAX; serach++) {
		if (SYB_OptionalSpeed[serach].Number == OPR_Buf.OntchSpdCtrl.SelectOptionalNumber) {
			for (move_point = serach; move_point < SYS_SPEED_DIAL_MAX; move_point++) {
				if (move_point == (UBYTE)(SYS_SPEED_DIAL_MAX - 1)) {
					SYB_OptionalSpeed[move_point].Number = 0xFFFF;
					SYB_OptionalSpeed[move_point].Record = 0xFF;
					return;
				}
				SYB_OptionalSpeed[move_point].Number = SYB_OptionalSpeed[move_point + 1].Number;
				SYB_OptionalSpeed[move_point].Record = SYB_OptionalSpeed[move_point + 1].Record;
				if (SYB_OptionalSpeed[move_point].Number == 0xFFFF) {
					return;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[短縮ダイアル登録状態を得る]
	function	:[
		1.指定された短縮番号の登録状態を得る
		2.引数で短縮番号を得る
	]
	return		:[
		NG:未登録
		OK:登録済み
	]
	common		:[SYB_SpeedDial]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/17]
	author		:[江口]
*************************************************************************/
UBYTE CheckSpeedStoreStatus(UBYTE speed)
{
	if ((SYB_SpeedDial[speed].Dial[0] & 0xF0) == 0xF0) {
		return (NG);
	}
	return (OK);
}
