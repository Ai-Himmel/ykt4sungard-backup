/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SETT.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＯＮ／ＯＦＦ切り替えタイプの機器設定のセットオペレーション 
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\status.h"		/* 97/07/03 Add by M.Kuwahara */
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#if (PRO_DPRAM == ENABLE)
#include	"\src\atlanta\ext_v\dpr_tbl.h"		/* 97/07/03 Add by M.Kuwahara */
#endif
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\man_pro.h"
#endif

/* Prototype
UBYTE	EnterSettingStatus(UBYTE *, UBYTE *, UBYTE, UBYTE, UBYTE, UBYTE);
void	DisplayEnterSetting(void);
void	SettingForwordOperation(void);
void	SettingBackOperation(void);
void	CheckSelectItemEnable(UBYTE);
#if (PRO_PC_PRINT == ENABLE)
UBYTE	EnterSettingStatusToLong(UBYTE *, UBYTE *, UBYTE, UBYTE, UBYTE, UBYTE);
void	DisplayEnterSettingToLong(void);
void	SettingForwordOperationToLong(void);
void	SettingBackOperationToLong(void);
void	CheckSelectItemEnableToLong(UBYTE);
#endif
UBYTE	SelectData(UBYTE *, UBYTE *, UBYTE, UBYTE *, UBYTE, UBYTE);
*/

/*************************************************************************
	module		:[機能キー選択タイプ入力]
	function	:[
		1.機器設定等で、SYB_SettingStatus[]のデータの選択入力を行います

		2.引数の説明
		，UBYTE *ItemWording			:上段表示固定文字列（設定項目を表示)
		,								 表示しない場合D2W_Nullが指定される
		, UBYTE *SelectWording			:上段表示可変文字列（選択肢を表示)
		,								 設定値が０の時に選択する文字列を指定
		, UBYTE MaxSelectCount			:選択肢個数最大値（フルスペックの場合の選択肢個数）
		, UBYTE SetPosition				:SYB_SettingStatus[]のどの位置にセットするか
		, UBYTE ValidPatternPosition	:３通り以上選択肢がある場合にどのパターンが有効か無効かを保持する
		,								 テーブルの参照位置（国の違いによる設定データの違いを吸収するため)
		,								 選択肢が２通りしかない物は基本的に0xFFがセットされている
		, UBYTE EnableBit				:セットするビット位置
	]
	return		:[
		OK	:登録完了
		NG	:登録中止
	]
	common		:[]
	condition	:[]
	comment		:[
		注１）第５引数のValidPatternPosition(ValidSelectBitPatternTable[]のビット定義）は、
			　必ず１つの選択肢に対して１つのビットを割り当てる必要があります（0x03等の重複定義は不可）
		注２）第６引数のEnableBit(SYB_SettingStatus[]のビット定義）は、必ず最初のビット定義からは
			　連続した値である必要があります
			　例）#define COPY_FIXED_REDUCTION_1	0x00
				　#define COPY_FIXED_REDUCTION_2	0x08
				　#define COPY_FIXED_REDUCTION_3	0x10
				　#define COPY_FIXED_REDUCTION_4	0x18
				　#define COPY_FIXED_REDUCTION_5	0x20
				　#define COPY_FIXED_REDUCTION_6	0x28
				　#define COPY_FIXED_REDUCTION_7	0x30

			　　　先頭の定義が０の場合は、その次の定義から考えます
			　　　内部的には最初の定義を0x01から数え始めますので、この場合は、
			　　　0x01,0x02,0x03,0x04,0x05,0x06の定義と同じ事になります
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
UBYTE EnterSettingStatus(UBYTE *ItemWording,
						 UBYTE *SelectWording,
						 UBYTE MaxSelectCount,
						 UBYTE SetPosition,
						 UBYTE ValidPatternPosition,
						 UBYTE EnableBit)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ */
	UBYTE	key_type;

	/*------------------------------*/
	/** 初期化処理 					*/
	/* ワークのバッファを初期化する */
	/*------------------------------*/
	/* 上段固定文字列 */
	OPR_Buf.EntrSettingCtrl.ItemWording = ItemWording;
	OPR_Buf.EntrSettingCtrl.SelectWording = SelectWording;

	/* 選択肢個数 */
	OPR_Buf.EntrSettingCtrl.SelectCount = MaxSelectCount;

	/* ビット位置 */
	OPR_Buf.EntrSettingCtrl.EnableBit = EnableBit;

	/* 選択肢有効無効を保持するテーブルの該当位置 */
	if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
#if defined(EC1)	/* 98/04/06 by M.H. for DNK NOR SWE FIN */
		if((ValidPatternPosition == OPR_LINE_TYPE)&&(SYB_MachineParameter[0] <= 7)&&(SYB_MachineParameter[0] >= 4)){
			OPR_Buf.EntrSettingCtrl.ValidPattern = OPR_DIAL_TONE;
		}else{
			OPR_Buf.EntrSettingCtrl.ValidPattern = ValidSelectBitPatternTable[ValidPatternPosition];
		}
#else
 #if defined(EUR)	/* EUR対策 99/10/05 by M.H */
		if((ValidPatternPosition == OPR_LINE_TYPE)&&(!CHK_DP_Enable())){
			OPR_Buf.EntrSettingCtrl.ValidPattern = OPR_DIAL_TONE;
		}else{
			OPR_Buf.EntrSettingCtrl.ValidPattern = ValidSelectBitPatternTable[ValidPatternPosition];
		}
 #else
		OPR_Buf.EntrSettingCtrl.ValidPattern = ValidSelectBitPatternTable[ValidPatternPosition];
 #endif
#endif
	}

	/* 設定済みデータ */
	OPR_Buf.EntrSettingCtrl.SettingData = SYB_SettingStatus[SetPosition] & EnableBit;

	/* 設定済みデータを変換 */
	OPR_Buf.EntrSettingCtrl.ShiftCount = 0;
	while ((OPR_Buf.EntrSettingCtrl.EnableBit & 0x01) == 0) {/* ここで無限ループする場合、引数に間違いあり */
		OPR_Buf.EntrSettingCtrl.ShiftCount++;
		OPR_Buf.EntrSettingCtrl.EnableBit >>= 1;	/* 最下位ビットにくるまで１ビットずつしふと */
	}
	if (OPR_Buf.EntrSettingCtrl.SettingData != 0) {
		OPR_Buf.EntrSettingCtrl.SettingData >>= OPR_Buf.EntrSettingCtrl.ShiftCount;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while ( 1 ) {
		/** LCD表示 */
		DisplayEnterSetting();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) { /** 取り込んだキーに対する処理 */
		case KEY_TIME_UP:
		case STOP:
			/** 終了 */
			return(NG);
		case FUNCTION:		/* 選択データを進める */
			SettingForwordOperation();
			if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
				CheckSelectItemEnable(key_type);
			}
			break;
		case LEFT_ARROW:	/* 選択データを戻す */
			SettingBackOperation();
			if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
				CheckSelectItemEnable(key_type);
			}
			break;
		case ENTER:
			/** 入力された値をセットして終了 */
			OPR_Buf.EntrSettingCtrl.EnableBit <<= OPR_Buf.EntrSettingCtrl.ShiftCount;
			if (OPR_Buf.EntrSettingCtrl.SettingData != 0) {
				OPR_Buf.EntrSettingCtrl.SettingData <<= OPR_Buf.EntrSettingCtrl.ShiftCount;
			}
			SYB_SettingStatus[SetPosition] &= ~OPR_Buf.EntrSettingCtrl.EnableBit;
			SYB_SettingStatus[SetPosition] |=  OPR_Buf.EntrSettingCtrl.SettingData;
#if (PRO_MULTI_LINE == ENABLE)
			MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS);
#endif
			return (OK);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			/* ナックを鳴らさないため */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[機器設定オペレーション表示]
	function	:[
		1.上段表示のみ書き換える
		2.点滅表示を行っているので、点滅表示文字列を更新する時以外
		　絶対に下段は書き換えてはいけない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/11]
	author		:[江口]
*************************************************************************/
void DisplayEnterSetting(void)
{
	/*--------------*/
	/* 上段表示		*/
	/*--------------*/
	/* 表示用バッファクリア */
	CMN_MemorySetNULL(OPR_Buf.EntrSettingCtrl.DisplayBuffer, OPR_DISPLAY_MAX, ' ');

	/** 選択肢（ＯＮ／ＯＦＦ等の選択状態）を表示バッファにコピー */
	CMN_StringCopy(OPR_Buf.EntrSettingCtrl.DisplayBuffer,
				   OPR_Buf.EntrSettingCtrl.SelectWording + OPR_Buf.EntrSettingCtrl.SettingData * OPR_WORDING_LEN);
	/** 設定項目を示す固定文字列をコピー */
	CMN_StringCopy(OPR_Buf.EntrSettingCtrl.DisplayBuffer, OPR_Buf.EntrSettingCtrl.ItemWording);

	DisplayStringHigh(0, OPR_Buf.EntrSettingCtrl.DisplayBuffer);
}

/*************************************************************************
	module		:[選択する設定を進める]
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
	date		:[1995/07/11]
	author		:[江口]
*************************************************************************/
void SettingForwordOperation(void)
{
	if (OPR_Buf.EntrSettingCtrl.SettingData == (UBYTE)(OPR_Buf.EntrSettingCtrl.SelectCount - 1)) {
		OPR_Buf.EntrSettingCtrl.SettingData = 0;
	}
	else {
		OPR_Buf.EntrSettingCtrl.SettingData++;
	}
}

/*************************************************************************
	module		:[選択する設定を戻す]
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
	date		:[1995/07/11]
	author		:[江口]
*************************************************************************/
void SettingBackOperation(void)
{
	if (OPR_Buf.EntrSettingCtrl.SettingData == 0) {
		OPR_Buf.EntrSettingCtrl.SettingData = (UBYTE)(OPR_Buf.EntrSettingCtrl.SelectCount - 1);
	}
	else {
		OPR_Buf.EntrSettingCtrl.SettingData--;
	}
}

/*************************************************************************
	module		:[選択肢有効無効の判断]
	function	:[
		1.選択された選択肢が有効か無効か調べる

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/20]
	author		:[江口]
*************************************************************************/
void CheckSelectItemEnable(UBYTE key_type)
{
	UBYTE	bit_position;
	UBYTE	bit_pattern;
	UBYTE	select_count;

	select_count = OPR_Buf.EntrSettingCtrl.SelectCount;		/* 選択できる個数 */
	bit_pattern  = OPR_Buf.EntrSettingCtrl.ValidPattern;	/* 選択肢の有効／無効のテーブル情報 */

	while (select_count > 0) {
		bit_position = OPR_Buf.EntrSettingCtrl.SettingData;	/* 現在の設置値 */
		if (((bit_pattern >> bit_position) & 0x01) != 0) {
			return;
		}
		else {
			if (key_type == FUNCTION) {	/* 選択データを進める時 */
				SettingForwordOperation();
			}
			else {						/* 選択データを戻す時 */
				SettingBackOperation();
			}
		}
		select_count--;	/* この変数は一応ループ脱出手段として、使用する */
	}
	/* select_count が０になっていることはまずない */
	/* ０になっているのは全ての選択肢が無効な場合なので、オペレーション自体が存在しないはず */
}

#if (PRO_PC_PRINT == ENABLE)
/*************************************************************************
	module		:[機能キー選択タイプ入力（選択枝９個以上用）]
	function	:[
		1.機器設定等で、SYB_SettingStatus[]のデータの選択入力を行います
		　（選択肢が９個以上ありEnterSettingStatus()では対応できない場合用です）

		2.引数の説明
		，第１引数　*ItemWording	:上段表示固定文字列（設定項目を表示)
		，							 表示しない場合D2W_Nullが指定される
		，第２引数　*SelectWording	:上段表示可変文字列（選択肢を表示)
		，							 設定値が０の時に選択する文字列を指定
		，第３引数　MaxSelectCount	:選択肢個数最大値（フルスペックの場合の選択肢個数）
		，第４引数　SetPosition		:SYB_SettingStatus[]のどの位置にセットするか
		，第５引数　ValidPattern	:選択肢のどのパターンが有効か無効かを保持するテーブルの参照位置
		，							 （国の違いによる設定データの違いを吸収するため）
		，第６引数　EnableBit		:セットするビット位置
	]
	return		:[
		OK	:登録完了
		NG	:登録中止
	]
	common		:[]
	condition	:[]
	comment		:[
		注１）第５引数のValidPatternPosition(ValidSelectBitPatternTable[]のビット定義）は、
			　必ず１つの選択肢に対して１つのビットを割り当てる必要があります（0x03等の重複定義は不可）
		注２）第６引数のEnableBit(SYB_SettingStatus[]のビット定義）は、必ず最初のビット定義からは
			　連続した値である必要があります
			　例）#define COPY_FIXED_REDUCTION_1	0x00
				　#define COPY_FIXED_REDUCTION_2	0x08
				　#define COPY_FIXED_REDUCTION_3	0x10
				　#define COPY_FIXED_REDUCTION_4	0x18
				　#define COPY_FIXED_REDUCTION_5	0x20
				　#define COPY_FIXED_REDUCTION_6	0x28
				　#define COPY_FIXED_REDUCTION_7	0x30

			　　　先頭の定義が０の場合は、その次の定義から考えます
			　　　内部的には最初の定義を0x01から数え始めますので、この場合は、
			　　　0x01,0x02,0x03,0x04,0x05,0x06の定義と同じ事になります
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/17]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE EnterSettingStatusToLong(UBYTE *ItemWording,
							   UBYTE *SelectWording,
							   UBYTE MaxSelectCount,
							   UBYTE SetPosition,
							   UBYTE ValidPatternPosition,
							   UBYTE EnableBit)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ */
	UBYTE	key_type;

	/*------------------------------*/
	/** 初期化処理 					*/
	/* ワークのバッファを初期化する */
	/*------------------------------*/
	/* 上段固定文字列 */
	OPR_Buf.EntrSettingCtrlLng.ItemWording = ItemWording;
	OPR_Buf.EntrSettingCtrlLng.SelectWording = SelectWording;

	/* 選択肢個数 */
	OPR_Buf.EntrSettingCtrlLng.SelectCount = MaxSelectCount;

	/* ビット位置 */
	OPR_Buf.EntrSettingCtrlLng.EnableBit = EnableBit;

	/* セットステータス */
	OPR_Buf.EntrSettingCtrlLng.SetPosition	= SetPosition;

	/* 選択肢有効無効を保持するテーブルの該当位置 */
	if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
		OPR_Buf.EntrSettingCtrlLng.ValidPattern = ValidSelectBitPatternTableLong[ValidPatternPosition];
	}

	/* 設定済みデータ */
	OPR_Buf.EntrSettingCtrlLng.SettingData = SYB_SettingStatus[SetPosition] & EnableBit;

	/* 設定済みデータを変換 */
	OPR_Buf.EntrSettingCtrlLng.ShiftCount = 0;
	while ((OPR_Buf.EntrSettingCtrlLng.EnableBit & 0x01) == 0) {	/* ここで無限ループする場合、引数に間違いあり */
		OPR_Buf.EntrSettingCtrlLng.ShiftCount++;
		OPR_Buf.EntrSettingCtrlLng.EnableBit >>= 1;	/* 最下位ビットにくるまで１ビットずつシフト */
	}

	if (OPR_Buf.EntrSettingCtrlLng.SettingData != 0) {
		OPR_Buf.EntrSettingCtrlLng.SettingData >>= OPR_Buf.EntrSettingCtrlLng.ShiftCount;
	}

	while ( 1 ) {
		/** LCD表示 */
		DisplayEnterSettingToLong();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) {	/** 取り込んだキーに対する処理 */
		case KEY_TIME_UP:
		case STOP:
			/** 終了 */
			return(NG);
		case FUNCTION:		/** 選択データを進める */
			SettingForwordOperationToLong();
			if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
				CheckSelectItemEnableToLong(key_type);
			}
			break;
		case LEFT_ARROW:	/** 選択データを戻す */
			SettingBackOperationToLong();
			if (ValidPatternPosition != OPR_VALID_CHECK_NOT_NEED) {	/* 選択肢が２個以上ある場合 */
				CheckSelectItemEnableToLong(key_type);
			}
			break;
		case ENTER:			/** 入力された値をセットして終了 */
			OPR_Buf.EntrSettingCtrlLng.EnableBit <<= OPR_Buf.EntrSettingCtrlLng.ShiftCount;
			if (OPR_Buf.EntrSettingCtrlLng.SettingData != 0) {
				OPR_Buf.EntrSettingCtrlLng.SettingData <<= OPR_Buf.EntrSettingCtrlLng.ShiftCount;
			}
			SYB_SettingStatus[SetPosition] &= ~OPR_Buf.EntrSettingCtrlLng.EnableBit;
			SYB_SettingStatus[SetPosition] |=  OPR_Buf.EntrSettingCtrlLng.SettingData;
#if (PRO_MULTI_LINE == ENABLE)
			MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS);
#endif
			return (OK);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:		/* ナックを鳴らさないため */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[機器設定オペレーション表示]
	function	:[
		1.上段表示のみ書き換える
		2.点滅表示を行っているので、点滅表示文字列を更新する時以外
		　絶対に下段は書き換えてはいけない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayEnterSettingToLong(void)
{
	/*--------------*/
	/* 上段表示		*/
	/*--------------*/
	/* 表示用バッファクリア */
	CMN_MemorySetNULL(OPR_Buf.EntrSettingCtrlLng.DisplayBuffer, OPR_DISPLAY_MAX, ' ');

	/** 選択肢（ＯＮ／ＯＦＦ等の選択状態）を表示バッファにコピー */
	CMN_StringCopy(OPR_Buf.EntrSettingCtrlLng.DisplayBuffer,
				   OPR_Buf.EntrSettingCtrlLng.SelectWording + OPR_Buf.EntrSettingCtrlLng.SettingData * OPR_WORDING_LEN);

	/** 設定項目を示す固定文字列をコピー */
	CMN_StringCopy(OPR_Buf.EntrSettingCtrlLng.DisplayBuffer, OPR_Buf.EntrSettingCtrlLng.ItemWording);

	DisplayStringHigh(0, OPR_Buf.EntrSettingCtrlLng.DisplayBuffer);
}

/*************************************************************************
	module		:[選択する設定を進める]
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
	date		:[1996/09/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void SettingForwordOperationToLong(void)
{
	if (OPR_Buf.EntrSettingCtrlLng.SettingData == (UBYTE)(OPR_Buf.EntrSettingCtrlLng.SelectCount - 1)) {
		OPR_Buf.EntrSettingCtrlLng.SettingData = 0;
	}
	else {
		OPR_Buf.EntrSettingCtrlLng.SettingData++;
	}
}

/*************************************************************************
	module		:[選択する設定を戻す]
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
	date		:[1996/09/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void SettingBackOperationToLong(void)
{
	if (OPR_Buf.EntrSettingCtrlLng.SettingData == 0) {
		OPR_Buf.EntrSettingCtrlLng.SettingData = (UBYTE)(OPR_Buf.EntrSettingCtrlLng.SelectCount - 1);
	}
	else {
		OPR_Buf.EntrSettingCtrlLng.SettingData--;
	}
}

/*************************************************************************
	module		:[選択肢有効無効の判断]
	function	:[
		1.選択された選択肢が有効か無効か調べる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void CheckSelectItemEnableToLong(UBYTE key_type)
{
	UBYTE	select_count;
	UDWORD	bit_position;
	UDWORD	bit_pattern;

	select_count = OPR_Buf.EntrSettingCtrlLng.SelectCount;
	bit_position = OPR_Buf.EntrSettingCtrlLng.SettingData;
	bit_pattern  = OPR_Buf.EntrSettingCtrlLng.ValidPattern;

	while (select_count > 0) {
		bit_position = OPR_Buf.EntrSettingCtrlLng.SettingData;
		bit_pattern  = OPR_Buf.EntrSettingCtrlLng.ValidPattern;
		if (((bit_pattern >> bit_position) & 0x01) != 0) {
			return;
		}
		else {
			if (key_type == FUNCTION) {	/* 進める方向 */
				SettingForwordOperationToLong();
			}
			else {
				SettingBackOperationToLong();
			}
		}
		select_count--;	/* この変数は一応ループ脱出手段として，使用する */
	}
	/* select_count が０になっていることはまずない */
	/* ０になっているのは全ての選択肢が無効な場合なので、オペレーション自体が存在しないはず */
}
#endif	/* (PRO_PC_PRINT == ENABLE) */

/*************************************************************************
	module		:[機能キー選択タイプ入力]
	function	:[
		1.機器設定などで、ON,OFFなど、選択肢が決まっているような入力に用いる。
	]
	return		:[
		ENTERED			:登録完了
		CANCELED		:登録中止
		CHANGED_MODE	:モード変更	(引数の xg_mode_type)
	]
	common		:[]
	condition	:[]
	comment		:[
		引数の説明
			*item_wording		:上段表示固定文字列（設定項目)
			*select_wording		:上段表示可変文字列（選択肢)
			select_data_count	:選択肢個数
			*set_data			:登録するデータのアドレス
			enable_bit			:設定可能ビット位置
			xg_mode_type		:モード変更用のKeyType(Keycode.h参照)

		EnterSettingStatus()では、SYB_SettingStatus[]にしかデータをセット
		できないので、それ以外のデータをON/OFFする時にこの関数を使用する

		注１）上段表示文字列は、*item_wordingのNULLの位置以降しか、
			  *select_wordingのワーディングをコピーしません
			　例）                                      [01234567890123456789]
			　　　item_wording   = D2W_ConfirmReport	"ﾂｳｼﾝｼｮｳ        :\0   ";
			　　　select_wording = D2W_Off2				"                OFF "

		注２）EnableBitは、必ず最初のビット定義からは連続した値である必要があります
			　例）#define COPY_FIXED_REDUCTION_1	0x00
				　#define COPY_FIXED_REDUCTION_2	0x08
				　#define COPY_FIXED_REDUCTION_3	0x10
				　#define COPY_FIXED_REDUCTION_4	0x18
				　#define COPY_FIXED_REDUCTION_5	0x20
				　#define COPY_FIXED_REDUCTION_6	0x28
				　#define COPY_FIXED_REDUCTION_7	0x30

			　　　先頭の定義が０の場合は、その次の定義から考えます
			　　　内部的には最初の定義を0x01から数え始めますので、この場合は、
			　　　0x01,0x02,0x03,0x04,0x05,0x06の定義と同じ事になります

		注３）内部の処理の変数をOPR_Buf.EntrSettingCtrlを使用したかったのですが、
			  EnterSettingStatus()と違いOPR_Bufの共用体が使用されている状態で、
			  この関数がCallされると内容がつぶれてしまうので、止めます

		注４）xg_mode_type に keycode.hの keytypeを割当てるとそのキー入力時、CHANGED_MODEを
			  戻り値とします。但し xg_mode_type = NO_KEYTYPE とすると影響しません。
			  選択モードを順次移行する時等に使用します。（例、通信コマンドキャンセル→通信証設定）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/15]
	author		:[渡辺一章,福井知史]
*************************************************************************/
UBYTE SelectData(UBYTE *item_wording,
				 UBYTE *select_wording,
				 UBYTE select_data_count,
				 UBYTE *set_data,
				 UBYTE enable_bit,
				 UBYTE xg_mode_type)
{
	UBYTE	key;
	UBYTE	key_type;
	UBYTE	setting_data;	/* 設定データ */
	UBYTE	shift_cnt;		/* 設定可能ビットの最初の有効位置 */
	UBYTE	item_wrd_last;	/* 設定項目ワーディングのNULLの位置 */
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	ret;

	/*------------*/
	/* 初期化処理 */
	/*------------*/
	/* 表示用バッファクリア */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	/* 設定項目を示す固定文字列をコピー */
	CMN_StringCopy(FunctionDisplayBufferHigh, item_wording);
	item_wrd_last = (UBYTE)GetStringGapPoint(item_wording, NULL);

	/* 設定済みデータ */
	setting_data = *set_data & enable_bit;

	/* 設定済みデータを変換 */
	shift_cnt = 0;
	while (!(enable_bit & 0x01)) {	/* ここで無限ループする場合、引数に間違いあり */
		enable_bit >>= 1;	/* 最下位ビットにくるまで１ビットずつシフト */
		shift_cnt++;
	}
	if (setting_data != 0) {
		setting_data >>= shift_cnt;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */
	ret = OPR_ENTERED;
	is_loop_end = FALSE;

	while (is_loop_end != TRUE) {
		if (CheckChildDisplay() == FALSE) {	/** チャイルド未表示の時 */
			/* 上段表示 */
			CMN_StringCopy(&FunctionDisplayBufferHigh[item_wrd_last],
						   &select_wording[item_wrd_last] + (setting_data * OPR_WORDING_LEN));
			DisplayStringHigh(0, FunctionDisplayBufferHigh);

			/* 下段点滅表示再開 */
			FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */
		}

		/* キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		key_type = GetInputKeyType();

		switch (key_type) { /** 取り込んだキーに対する処理 */
		case STOP:
		case KEY_TIME_UP:
			ret = OPR_CANCELED;
			is_loop_end = TRUE;
			break;
		case FUNCTION:		/* 選択データを進める */
			if (setting_data == (UBYTE)(select_data_count - 1)) {
				setting_data = 0;
			}
			else {
				setting_data++;
			}
			break;
		case LEFT_ARROW:	/* 選択データを戻す */
			if (setting_data == 0) {
				setting_data = (UBYTE)(select_data_count - 1);
			}
			else {
				setting_data--;
			}
			break;
		case ENTER:
			/* 入力された値をセットして終了 */
			enable_bit <<= shift_cnt;
			if (setting_data != 0) {
				setting_data <<= shift_cnt;
			}
			*set_data &= ~enable_bit;
			*set_data |=  setting_data;
			is_loop_end = TRUE;
			break;
		case SINGLE:		/* 単一オペレーションキー */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
 #if (PRO_F_CODE == ENABLE)
			/* Ｆコード原稿蓄積時、待機状態で画質・濃度を変更していないと、原稿追加設定の時しか変更できる
			** タイミングがないので、追加します（無条件に呼んでもかまわないが、ポプラでは濃度がＬＣＤ表示
			** になったために、表示が上書きされてしまうので関係ある所でしか呼ばないようにしています）
			** 注）本当は、設定内容種別を表す引数を追加するか、単一キーが有効／無効の引数を追加するべきだが、
			** 　　変更箇所が多くなるので、ワーディングで判断します
			*/
			if (item_wording == D2W_SelectFcodeStoreDocAdd) {	/* Ｆコード原稿蓄積時の原稿追加設定の時 */
				SingleKeyOperation(key);
			}
			else {
				NackBuzzer();
			}
 #else
			NackBuzzer();
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
			SingleKeyOperation(key);
#endif
			break;
		case NO_EFFECT:
			break;
		default:	/* 通信コマンドキャンセル操作対応 By S.Fukui Oct.1,1997 */
			if ((xg_mode_type != NO_KEYTYPE) && (key_type == xg_mode_type)) {
				ret = OPR_CHANGED_MODE;
				is_loop_end = TRUE;
			}
			else {
				NackBuzzer();
			}
			break;
		}
	}

	return(ret);
}
