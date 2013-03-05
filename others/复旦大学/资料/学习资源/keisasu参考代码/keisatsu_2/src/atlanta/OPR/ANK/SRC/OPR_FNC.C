/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_FNC.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ファンクションオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include 	"\src\atlanta\define\unisw_i.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_PC_PRINT == ENABLE)
#include	"\src\atlanta\define\dpr_pro.h"
#endif

#if (PRO_CLASS1 == ENABLE)     /* added by honda 1997/11/18 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#else
	#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

struct	FUNCTION_TABLE_t *operation_pointer = NULL;	/* 選択中のファンクションへのポインター */
struct	FUNCTION_TABLE_t *save_top_pointer = NULL;
struct	FUNCTION_TABLE_t *save_bottom_pointer = NULL;
struct	FUNCTION_TABLE_t *save_operation_pointer = NULL;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (機能選択表示を修正します。) Added by SMuratec L.Z.W 2003/10/17 */
struct	FUNCTION_TABLE_t *mainfunction_bottom_pointer = NULL;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
UBYTE	function_group = 0;

/* Prototype
void	FunctionOperation(void);
void	OPR_SaveTopBottomOPRPointer(struct FUNCTION_TABLE_t *);
void	DisplayFunctionOperation(void);
UBYTE	CheckSelectFunctionEnable(struct FUNCTION_TABLE_t *);
void	ChangeWording(void);
void	ServiceFunctionOperation(void);
void	FunctionDummy(void);
*/

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/05/15 by K.Okada */
extern UBYTE	SYB_INF_DeviceExist;
#endif

/*************************************************************************
	module		:[ファンクションオペレーション]
	function	:[
		1.ファンクションの決定までを行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[機能の有無を判断する条件に、OPR_YESを追加1995/12/14]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/05]
	author		:[川崎、江口]
*************************************************************************/
void FunctionOperation(void)
{
	UBYTE	first_step_max;
	UBYTE	decimal;			/** 数字キーの十進待避用 */
	UBYTE	first_second_flag;
	UBYTE	key;				/* 入力ｷｰﾃﾞｰﾀ */
	UBYTE	keytype;
	UBYTE	select_count;		/* 選択肢数   */
	UBYTE	serv_enable;		/* サービスファンクション／ワーディング切り替え可・不可*/
	UBYTE	is_loop_end;		/* ループ終了で使用 */
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)		/* 2003/02/13 H.Tokuno */
	UBYTE	nackbuzzer_check;	/* [8]+[8]入力中ナックを鳴動フラグ TRUE:ナックを鳴らさない FALSE:ナックを鳴らす */
	UBYTE	remote_rx_func;
	UBYTE	remote_rx_lock;			/* 機能+[8]+[8]入力中に他のキーが割り込んだ時はもう受け付けない */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/29 */
	UBYTE	cutter_func;			/* 機能+[0]入力だけで手動カッターできるように変更。*/
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	first_second_flag = FIRST_KEY;
	serv_enable = TRUE;
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)		/* 2003/02/13 H.Tokuno */
	remote_rx_func = 0;
	remote_rx_lock = FALSE;
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/29 */
	cutter_func		= TRUE;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */


#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/08/14 */
	function_group = 1;
#else 
	function_group = 'A';
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/* 各ポインターの初期設定 */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (CMN_CheckCategory2()) {	/* F-101用の処理を追加します 1997/12/26 Y.Matsukuma */
		OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction_Category2);
	}
	else {
		OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction);
	}
#else
	OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction);
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (機能選択表示を修正します。) Added by SMuratec L.Z.W 2003/10/17 */
	mainfunction_bottom_pointer = save_bottom_pointer;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	first_step_max = save_bottom_pointer->FirstCode;

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {
		/** 決定前の表示処理 */
		DisplayFunctionOperation();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)
		/* 機能+[8]+[8}入力中はナックを鳴らさないこと */
		nackbuzzer_check = FALSE;		/* ナックを鳴らす */
		if (key != TEN_8_KEY) {
			remote_rx_func = 0;
			remote_rx_lock = TRUE;
		}
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/29 */
		if (key != TEN_0_KEY) {
			cutter_func = FALSE;
		}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ONETOUCH:	/** ワンタッチキー */
			/*---------------------*/
			/*   最上位階層の選択  */
			/*---------------------*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/*下記変更 By M.Kotani 1998/03/18*/
/*#if defined(ANZU_L)*/
			if (ONETOUCH_a_KEY <= key && key <= ONETOUCH_z_KEY) {
				key -= 0x20; /* 大文字に変換 */
			}
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/08/14 */
			if (ONETOUCH_01_KEY <= key && key <= ONETOUCH_20_KEY) {
				key -= 0x40; /* 大文字に変換 */
			}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			save_operation_pointer = operation_pointer;	/** 現ポインター退避*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if (CMN_CheckCategory2()) {	/* F-101用の処理を追加します 1997/12/26 Y.Matsukuma */
				operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction_Category2;	/** 最上位階層のテーブルの先頭アドレスをセット*/
			}
			else {
				operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction;	/** 最上位階層のテーブルの先頭アドレスをセット*/
			}
#else
			operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction;	/** 最上位階層のテーブルの先頭アドレスをセット*/
#endif
			/** 指定されたワンタッチキーに対応する機能があるか調べる */
			for ( ;operation_pointer->FirstCode != NULL; operation_pointer++) {
				if ((operation_pointer->FirstCode == key) && (operation_pointer->Available == OPR_YES)) {
					break;
				}
			}

			if (operation_pointer->FirstCode == NULL) {	/** 選択されたファンクションが存在しない場合 */
				operation_pointer = save_operation_pointer;	/** ポインターを元に戻しておく */
				NackBuzzer();
			}
			else {										/** 入力されたキーに対する機能が存在する場合 */
				if (CheckSelectFunctionEnable(operation_pointer) == FALSE) {
					/* 選択された機能が、現在の状況では選択出来ない時 */
					operation_pointer = save_operation_pointer;
					NackBuzzer();
					break;
				}

				serv_enable = FALSE;	/* 一度通常のファンクションのモードに入ったらサービスファンクションは不可能 */

				/* 最上位階層の選択 */
				first_second_flag = FIRST_KEY;
#if (PRO_KEYPANEL == PANEL_ANZU_L)
				if (CMN_CheckCategory2()) {	/* F-101用の処理を追加します 1997/12/26 Y.Matsukuma */
					OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction_Category2);
				}
				else {
					OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction);
				}
#else
				OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)MainFunction);
#endif

				/* ファンクションテーブルの確定 */
				for ( ; operation_pointer->FirstCode != '\0'; operation_pointer++) {
					if ((operation_pointer->FirstCode == key) && (operation_pointer->Available == OPR_YES)) {
						break;
					}
				}
				function_group = operation_pointer->FirstCode;
			}
			break;

		case NUMBER:	/** 数字キー */
			/*--------------------------------*/
			/* 下位階層の選択				  */
			/*--------------------------------*/
			serv_enable = FALSE;

			/* 入力されたキーデータがファンクションテーブルに存在するかを調べる。なければ下位階層も調べる */
			save_operation_pointer = operation_pointer;	/** 現ポインター待避 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/08/14 */
			if (operation_pointer >= (struct FUNCTION_TABLE_t *)MainFunction && /* (機能選択表示を修正します。) Modify by SMuratec L.Z.W 2003/10/17 */
				operation_pointer <= mainfunction_bottom_pointer) {
#else 
			if (operation_pointer->FirstCode >= 'A') {	/** 最上位階層か？（ワンタッチの直後のテンキーの場合） */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
				if (operation_pointer->NextLevel != NULL) {	/** 下位階層がある */
					operation_pointer = operation_pointer->NextLevel;	/* 下位の階層に移行 */
					save_top_pointer = operation_pointer;
				}
				/* ワンタッチだけで機能する場合は、数字キーは無効です by K.Watanabe 1998/02/23 */
				else {										/** 下位階層がない */
					NackBuzzer();
					break;
				}
			}
			else {										/* 下位の階層にいる */
				/* 下位階層のテーブルの先頭のアドレスをセット */
				save_operation_pointer = operation_pointer;
				operation_pointer = save_top_pointer;
			}

			/* ファンクションの選択肢の個数を求める */
			/* Ex) PRG-Aなら３						*/
			while (operation_pointer->FirstCode != '\0') {
				if ((operation_pointer->FirstCode != '\0') && (operation_pointer->Available == OPR_YES)) {
					select_count = operation_pointer->FirstCode;
				}
				operation_pointer++;
			}

			/* テーブルの最初から（機能を）検索するためにポインターをセット */
			operation_pointer = save_top_pointer;

			/* 入力された数字を１０進数に変換します */
			if (first_second_flag == FIRST_KEY) {	/* ワンタッチキーの直後のテンキー */
				decimal = ChangeASC_CodeToNumber(key);	/** 十進に変換 */
			}
			else {	/* SECOND_KEY */				/* ２桁ある場合（J14とか）の２桁目のテンキー */
				decimal *= 10;
				decimal += ChangeASC_CodeToNumber(key);	/** 十進に変換 */
			}

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)		/* 2003/02/13 H.Tokuno */
			/* 機能+[8]+[8] */
			if (!remote_rx_lock) {
				if (decimal == 8) {
					remote_rx_func *= 10;
					remote_rx_func += decimal;
					nackbuzzer_check = TRUE;		/* ナックを鳴らさない */
				}
				else {
					remote_rx_func = 0;
				}

				if (remote_rx_func == 88) {
					DisplayRemoteTransferSetting();
					return;
				}
			}
#endif
#if !defined(STOCKHM2)
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 手動カッター制御追加 by Y.Kano 2003/10/15 */
			if (cutter_func) { /* 機能+[0]入力だけで手動カッターできるように変更。Modify by SMuratec L.Z.W 2003/10/29 */
				if (decimal == 0) {
					if (CHK_WallHangSetting()) { /** 壁掛け設定時のみカッター動作させる。*/
						if (PS1() && PS2()) {	/* ペーパー有りの時のみカッター動作させる。*/
							ManualCutter();					/* カッター動作 */
							return;
						}
						else {
							NackBuzzer();				/* ナックを鳴らす */
							return;
						}
					}
					else {
						NackBuzzer();					/* ナックを鳴らす */
						return;
					}
				}
			}
 #endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif	/* End of (!defined(STOCKHM2)) */

			if ((select_count >= 10 && decimal >= 10) /* 選択肢数が１０個以上で、入力された機能番号も１０以上 */
			||  (select_count <= 9  && decimal <= 9)  /* 選択肢数が９個以下で入力された機能番号も９以下 */
			||	(select_count >= 10 && decimal <=9 && first_second_flag == SECOND_KEY)) {/* 機能０，９とか言う風に押された */
				first_second_flag = FIRST_KEY;/* 次はファーストキーになる */
				/* 一致する機能番号を検索 */
				while( operation_pointer->FirstCode != '\0') {
					/* 一致する機能番号が存在し、かつ機能有効 */
					if ((operation_pointer->FirstCode == decimal) && (operation_pointer->Available == OPR_YES)) {
						save_operation_pointer = operation_pointer;
						OPR_SaveTopBottomOPRPointer(save_top_pointer);
						operation_pointer = save_operation_pointer;
						break;
					}
					operation_pointer++;
				}
				/* 一致する機能番号がない */
				if ((operation_pointer->FirstCode != decimal) || (operation_pointer->Available == OPR_NO)) {
					OPR_SaveTopBottomOPRPointer(save_top_pointer);
					operation_pointer = save_operation_pointer;
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)
					if (!nackbuzzer_check) {
						NackBuzzer();
					}
#else
					NackBuzzer();
#endif
				}
			}
			else if ((decimal <= 9) && (select_count >= 10)) { /* 選択肢数が１０以上ある場合の１桁目のみ入力 */
				first_second_flag = SECOND_KEY;
				OPR_SaveTopBottomOPRPointer(save_top_pointer);
				operation_pointer = save_operation_pointer;
			}
			else {
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)
				if (!nackbuzzer_check) {
					NackBuzzer();
				}
#else
				NackBuzzer();
#endif
			}
			break;

		case FUNCTION:
			/*----------------------------*/
			/* 同位階層（正方向)		  */
			/*----------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			is_loop_end = FALSE;

#if 0 /* (手動カッター制御変更) Delete by SMuratec L.Z.W 2003/11/10 */	
** #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/29 */
**			cutter_func = TRUE;
** #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif

			while (is_loop_end != TRUE) {
				operation_pointer++;
				if (operation_pointer->FirstCode == '\0') {
					operation_pointer = save_top_pointer;
				}

				if (operation_pointer->Available == OPR_YES) {	/* 現在の機能が有効な機能の時 */
					is_loop_end = CheckSelectFunctionEnable(operation_pointer);
				}
			}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/08/14 */
			if (operation_pointer >= (struct FUNCTION_TABLE_t *)MainFunction && /* (機能選択表示を修正します。) Modify by SMuratec L.Z.W 2003/10/17 */
				operation_pointer <= mainfunction_bottom_pointer) {
				function_group = operation_pointer->FirstCode;
			}
#else
			if (operation_pointer->FirstCode >= 'A') {	/* 最上位階層 */
				function_group = operation_pointer->FirstCode;
			}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;
		case LEFT_ARROW:
			/*----------------------------*/
			/* 同位階層（負（逆）方向)	  */
			/*----------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			is_loop_end = FALSE;

			while (is_loop_end != TRUE) {
				if (operation_pointer == save_top_pointer) {
					operation_pointer = save_bottom_pointer;
				}
				else {
					--operation_pointer;
				}

				if (operation_pointer->Available == OPR_YES) {	/* 現在の機能が有効な機能の時 */
					is_loop_end = CheckSelectFunctionEnable(operation_pointer);
				}
			}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modified by SMuratec L.Z.W 2003/08/14 */
			if (operation_pointer >= (struct FUNCTION_TABLE_t *)MainFunction && /* (機能選択表示を修正します。) Modify by SMuratec L.Z.W 2003/10/17 */
				operation_pointer <= mainfunction_bottom_pointer) {
				function_group = operation_pointer->FirstCode;
			}
#else
			if (operation_pointer->FirstCode >= 'A') {	/* 最上位階層 */
				function_group = operation_pointer->FirstCode;
			}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;

		case AST:
		case SHARP:
			if (serv_enable == FALSE) {
				NackBuzzer();
			}
			else {
				if (key == TEN_SHARP_KEY) {	/* ワーディング切り替え */

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
 #if defined(TWN)
 					/* ＨＩＮＯＫＩ ＴＷＮ仕様はワーディング切替えはありません。
 					** by O.Kimoto 1999/02/02
 					*/
					NackBuzzer();
 #elif defined (KEISATSU) /* 警察FAX 05/05/26 石橋正和 */
					NackBuzzer();
					break;
 #else
  #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ユニークSWONでワーディング切り替え。by Y.Kano 2003/10/16 */
					if (CHK_UNI_WordingChangeEnable()) {
						ChangeWording();
						if (CHK_StoringFlashEnable()) { /* JPN、USAで点滅機能切り替え. SMuratec H.C.H 2003/10/30 */
							SYB_MachineUniqSwitch[UNIQ_SW_I7] &= ~STORING_FLASH_ENABLE;
						}
						else {
							SYB_MachineUniqSwitch[UNIQ_SW_I7] |= STORING_FLASH_ENABLE;
						}
					}
					else {
						NackBuzzer();
						return;
					}
  #else
  					ChangeWording();
  #endif

 #endif
#else
					ChangeWording();
#endif

				}
				else {						/* サービスファンクション */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2ではナック音を鳴らすように修正 by Y.Kano 2003/10/06 */
					NackBuzzer();
#endif

#if defined(FRA)	/* by M.H.  8 Dec 97 */
					/* 標準で入れます。 HardDIP_SwitchEnableが0の時は、常にNoでﾘﾀｰﾝされます。*/
					if (CHK_HardDipProtection() == YES) {
						NackBuzzer();
					} else {
						ServiceFunctionOperation();
					}
#else
					ServiceFunctionOperation();
#endif
				}
				return;
			}
			break;

		case ENTER:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/05/15 by K.Okada */
			if (CheckSelectMailFunction(operation_pointer) == FALSE) {
				NackBuzzer();
				OPR_ChildErrorFlag = NO_DEVICE_ERROR;
				return;
			}
#endif
			/*------------------------------------*/
			/* 階層の確定或いはファンクション実行 */
			/*------------------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			if (operation_pointer->NextLevel == NULL) { /** これ以上下位の階層がない */
				/** ファンクションの実行 */
				(*operation_pointer->FunctionName)();
				return;
			}
			else { /** 下位の階層がある */
				/** 下位階層へ移行  */
				OPR_SaveTopBottomOPRPointer(operation_pointer->NextLevel);
			}

			break;

		case STOP:
		case KEY_TIME_UP:
			/*-----------------------------------*/
			/** ポインターを初期状態に戻して終了 */
			/*-----------------------------------*/
			first_second_flag = FIRST_KEY;
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if (CMN_CheckCategory2()) {	/* F-101用の処理を追加します 1997/12/26 Y.Matsukuma */
				operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction_Category2;	/** 最上位階層のテーブルの先頭アドレスをセット*/
			}
			else {
				operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction;	/** 最上位階層のテーブルの先頭アドレスをセット*/
			}
#else
			operation_pointer = (struct FUNCTION_TABLE_t *)MainFunction;
#endif
			return;

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
	module		:[ポインターの計算]
	function	:[
		１．ファンクションテーブルの頭とけつのポインターを取り出す。
		,
		,	 機能Ａ系列
		,	const struct FUNCTION_TABLE_t OneTouchFunction[] = {
		,	    {1,   '\0', OPR_YES, D2W_EnterOneTouchMode,	EnterOneTouch, 		NULL} <- save_top_pointer
		,	    {2,   '\0', OPR_YES, D2W_EraseOneTouchMode,	EraseOneTouch, 		NULL}
   		,		{3,   '\0', OPR_YES, D2W_PrintOneTouchMode,	PrintOneTouchList, 	NULL} <- save_bottom_pointer
		,   	{'\0', '\0', OPR_NO,  NULL, Dummy, NULL}
		,	}
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/30]
	author		:[江口]
*************************************************************************/
void OPR_SaveTopBottomOPRPointer(struct FUNCTION_TABLE_t *opr_ptr)
{
	operation_pointer = opr_ptr;
	save_top_pointer  = opr_ptr;
	/* けつを求める */
	while (operation_pointer->FirstCode != '\0') { /* ボトムポインターの待避が必要 */
		save_bottom_pointer = operation_pointer;
		operation_pointer++;
	}
	/* 頭をセット */
	operation_pointer = save_top_pointer;
}

/*************************************************************************
	module		:[ファンクションオペレーション中の表示]
	function	:[
		1.ファンクション選択中の画面表示
		2.上段表示のみ更新する.下段表示は点滅タスクが書き換えている

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/30]
	author		:[江口]
*************************************************************************/
void DisplayFunctionOperation(void)
{
	if (CheckChildErrorDisplayReq() == TRUE) { /* エラー等でチャイルド表示要求あり */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) { /* チャイルド表示中 */
		return;
	}

	/* 上段表示 */
	/* 機能番号＋機能名 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(&FunctionDisplayBufferHigh[0], operation_pointer->Wording);

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/14 */
	if (operation_pointer >= (struct FUNCTION_TABLE_t *)MainFunction && /* (機能選択表示を修正します。) Modify by SMuratec L.Z.W 2003/10/17 */
		operation_pointer <= mainfunction_bottom_pointer) {
		FunctionDisplayBufferHigh[0] = '[';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)(function_group), 2, '0');
		FunctionDisplayBufferHigh[3] = ']';			
	}
	else{
		/* 下位の階層にいる */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[0], (UWORD)(operation_pointer->FirstCode), 2, '0');
		FunctionDisplayBufferHigh[2] = ':';
	}
#else /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	/* 機能番号を求める */
	FunctionDisplayBufferHigh[0] = function_group;

	if (((operation_pointer->FirstCode >= 'A')&&
		 (operation_pointer->FirstCode <= 'Z')) == 0) { /*アルファベットじゃない*/

		/* 下位の階層にいる */
		if (save_bottom_pointer->FirstCode >= 10) { /* ２桁以上ファンクションの選択肢がある。例)機能Ｊ->22個 */
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)(operation_pointer->FirstCode), 2, '0');
		}
		else {
			FunctionDisplayBufferHigh[1] = ChangeNumberToASC_Code(operation_pointer->FirstCode);
		}
	}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[選択機能有効検査]
	function	:[
		1.選択された機能が、現在の状況で選択可能かをチェックします
	]
	return		:[
		TRUE	:選択可能
		FALSE	:選択不可能
	]
	common		:[]
	condition	:[]
	comment		:[
		ファンクションテーブルの定義だけでは、無効に出来ない機能について、
		再チェックします
		例）プリンターボードのリセットは、(PRO_PC_PRINT == ENABLE)であれば、
		　　テーブルの定義上は選択可能ですが、プリンターボードがついていなければ
		　　ファンクションメニューにも出さない仕様なので、選択時にプログラムで
		　　判断してはじきます。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/26]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckSelectFunctionEnable(struct FUNCTION_TABLE_t *func_ptr)
{
#if (PRO_PC_PRINT == ENABLE)
	/* プリンターボードのリセットを選択されたが、オプションボードにプリンターボードがない時は、選択できません */
	if ((func_ptr->FunctionName == ResetPrinterBoard) && (!DPR_CheckOptionPrintBoardExist())) {
		return(FALSE);
	}
#endif

#if (PRO_CLASS1 == ENABLE)     /* added by honda 1997/11/18 */
	/* クラス１のモードを選択されたが、ＲＳ２３２Ｃのボードがないときは、選択できません */
	if ((func_ptr->NextLevel == Class1Function) && (!SYS_RS232C_Exist)) {
		return(FALSE);
	}
#endif

#if (PRO_CIPHER == ENABLE)
	/* スクランブル機能が有効でも、ＲＯＭスイッチがＯＦＦの時は選択できません */
	if ((func_ptr->NextLevel == CipherFunction) && (!ScrambleOn)) {
		return(FALSE);
	}

	/* スクランブル解除プリントが有効でも、ＲＯＭスイッチがＯＦＦの時は選択できません by K.Watanabe 1998/01/06 */
	if ((func_ptr->FunctionName == PrintDecipherDocument) && (!ScrambleOn)) {
		return(FALSE);
	}
#endif
	return(TRUE);
}

/*************************************************************************
	module		:[選択機能有効検査]
	function	:[
		1.E-Mailエンジンボードが無い場合選択できない
		  設置オペレーションを実行後でないと、オペレーションできない
	]
	return		:[
		TRUE	:選択可能
		FALSE	:選択不可能
	]
	common		:[]
	condition	:[]
	comment		:[
		CheckSelectFunctionEnableと分けたのはボード無しと判断しても
		メニューには出すため。
		階層構造になってないFunctionについては各Function内でチェック
		している。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/05/15]
	author		:[K.Okada]
*************************************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/05/15 by K.Okada */
UBYTE CheckSelectMailFunction(struct FUNCTION_TABLE_t *func_ptr)
{
	/* E-Mailエンジンボードが無いときは選択不可 */
	/* 階層構造になっていないFunctionについては各Function内ではじく処理を入れている */
	if ((func_ptr->NextLevel == EMailFunction) && (SYB_INF_DeviceExist == FALSE)) {
		return(FALSE);
	}
	if ((func_ptr->NextLevel == MailAddressFunction) && (SYB_INF_DeviceExist == FALSE)) {
		return(FALSE);
	}
	if ((func_ptr->NextLevel == ConfirmInternetFaxCommand) && (SYB_INF_DeviceExist == FALSE)) {
		return(FALSE);
	}
	return (TRUE);
}
#endif

/*************************************************************************
	module		:[ワーディング切り替え]
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
	date		:[1995/12/06]
	author		:[江口]
*************************************************************************/
void ChangeWording(void)
{
	/* ワーディング切り替え */
    if (SYB_WordingNumber == CTRY_WordingNumberMax())
		SYB_WordingNumber = 1;
	else
		SYB_WordingNumber++;

#if (0)	/* 未使用なので削除します by K.Watanabe 1998/07/10 */
//	SetWording(SYB_WordingNumber);
//	CalculateWordingOffset();	/** ワーディングの実体までのオフセットの計算 1996/03/11 Eguchi*/
#endif
}

/*************************************************************************
	module		:[サービスファンクションモード]
	function	:[
		1.サービスファンクションの決定までを行う
		2.存在しないサービスファンクションが選択された時は、エラーになり、オペレーション終了し
		, 待機状態に戻る.
		, ex)機能＊７とかが選択された場合。
		,	従来：ファンクションオペレーション状態のまま
		,	ANZU：終了する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[＊の次に正しくないキーが入った場合終了]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/06]
	author		:[江口]
*************************************************************************/
void ServiceFunctionOperation(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	struct	SERV_FUNCTION_t *fnc_ptr;
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/03 By M.Maeda */	/* RDC200200635 By O.Kimoto 2003/02/14 */
	UBYTE	sharp_on;														/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */

	sharp_on = FALSE;														/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
#endif																		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */

	while (1) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/03 By M.Maeda */	/* RDC200200635 By O.Kimoto 2003/02/14 */
			if (sharp_on == TRUE) {											/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				if ((keycode == TEN_1_KEY) || (keycode == TEN_2_KEY)) {		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
					FirstOrLastClear(keycode);								/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
					return;													/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				}															/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
#if defined (KEISATSU) /* 警察FAX 05/11/18 石橋正和 */
				else if (keycode == TEN_9_KEY) {
					FactoryFirstClear(); /* 工場検査用ファーストクリア(S1バイパスON) */
					return;
				}
#endif
				else {														/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
					NackBuzzer();											/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
					return;													/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				}															/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			}																/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			/* 注意：ONETOUCHの処理へ移行します */							/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
#endif																		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */

		case ONETOUCH:
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
		case PROGRAM:
#endif
			for (fnc_ptr = (struct SERV_FUNCTION_t *)ServiceFunctionTable; fnc_ptr->KeyCode != NULL; fnc_ptr++) {
				if (fnc_ptr->KeyCode == keycode) { /*入力されたキーに対するファンクションが存在する */
					(*(fnc_ptr->ExecFunction))(); /* 関数実行*/
					return; /*終了 */
				}
			}
			/* ここにくるのは入力されたコードに対するファンクションがない場合 */
			NackBuzzer();
			return;

		case AST: /* アスタリスク→追加1996/09/03　Eguchi*/
 #if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/07 */
			NackBuzzer();
 #endif
			MaintenanceOperationMode();/* 開発時のテスト用オペレーション1996/09/03　Eguchi */
			return;

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/03 By M.Maeda */	/* RDC200200635 By O.Kimoto 2003/02/14 */
		case SHARP:															/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			if (sharp_on == FALSE) {										/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				sharp_on = TRUE;											/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */

 #if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/07 */
				NackBuzzer();
 #endif
			}																/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			else {															/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				NackBuzzer();												/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
				return;														/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			}																/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
			break;															/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */
#endif																		/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/04 By M.Maeda */

		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			return;
		}
	}
}

/*************************************************************************
	module		:[ファンクションオペレーション。ダミー関数]
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
	date		:[1996/04/01]
	author		:[江口]
*************************************************************************/
void FunctionDummy(void)
{
	return;
}

#if (PRO_CPU == SH7043)
/*************************************************************************
	module		:[ＤＲＡＭアドレス変更用空関数]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[ＳＨ用のＤＲＡＭはリニア空間なので空関数を定義します。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/11]
	author		:[川崎]
*************************************************************************/
UWORD DRAM_AddressChange(UWORD address)
{
	return (address);
}

/*************************************************************************
	module		:[ＤＲＡＭアドレス変更用空関数]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[ＳＨ用のＤＲＡＭはリニア空間なので空関数を定義します。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/11]
	author		:[川崎]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui June 19,1998  */
UDWORD DMA_AddressSetFlsRom(UBYTE *address)
#else
UDWORD DMA_AddressSet(UBYTE *address)
#endif
{
	return((UDWORD)address);
}
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/09 */
void	KeisatsuService(void)
{
	UBYTE	first_step_max;
	UBYTE	decimal;			/** 数字キーの十進待避用 */
	UBYTE	first_second_flag;
	UBYTE	select_count;		/* 選択肢数   */
	UBYTE	serv_enable;		/* サービスファンクション／ワーディング切り替え可・不可*/
	UBYTE	is_loop_end;		/* ループ終了で使用 */
	UBYTE	function_group = 0;

	UBYTE	keycode;
	UBYTE	keytype;

	decimal = 0;
	first_second_flag = FIRST_KEY;
	serv_enable = TRUE;
	
	function_group = 1;

	OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)KeisatsuServiceTable);

	first_step_max = save_bottom_pointer->FirstCode;

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */


	while (1) {
		/** 決定前の表示処理 */
		if (CheckChildErrorDisplayReq() == TRUE) { /* エラー等でチャイルド表示要求あり */
			DisplayChildError();
			return;
		}
		if (CheckChildDisplay() == TRUE) { /* チャイルド表示中 */
			return;
		}

		/* 上段表示 */
		/* 機能番号＋機能名 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(&FunctionDisplayBufferHigh[0], operation_pointer->Wording);

		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[0], (UWORD)(function_group), 2, '0');

		DisplayStringHigh(0, FunctionDisplayBufferHigh);
	
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			/*---------------------*/
			/*   最上位階層の選択  */
			/*---------------------*/
			save_operation_pointer = operation_pointer;	/** 現ポインター退避*/
			operation_pointer = (struct FUNCTION_TABLE_t *)KeisatsuServiceTable;	/** 最上位階層のテーブルの先頭アドレスをセット*/
			/** 指定されたワンタッチキーに対応する機能があるか調べる */
			
			if (first_second_flag == FIRST_KEY && (keycode == '0' || keycode == '1')){
				decimal = ChangeASC_CodeToNumber(keycode);
				first_second_flag = SECOND_KEY;
				
				break;
			}
			else if (first_second_flag == SECOND_KEY && keycode >= '0' && keycode <= '9'){
				decimal *= 10;
				decimal += ChangeASC_CodeToNumber(keycode);
				first_second_flag = FIRST_KEY;
			}
			else{
				operation_pointer = save_operation_pointer;
				NackBuzzer();
				
				break;
			}
			
			for ( ;operation_pointer->FirstCode != NULL; operation_pointer++) {
				if ((operation_pointer->FirstCode == decimal) && (operation_pointer->Available == OPR_YES)) {
					break;
				}
			}

			if (operation_pointer->FirstCode == NULL) {	/** 選択されたファンクションが存在しない場合 */
				operation_pointer = save_operation_pointer;	/** ポインターを元に戻しておく */
				NackBuzzer();
			}
			else {										/** 入力されたキーに対する機能が存在する場合 */
				if (CheckSelectFunctionEnable(operation_pointer) == FALSE) {
					/* 選択された機能が、現在の状況では選択出来ない時 */
					operation_pointer = save_operation_pointer;
					NackBuzzer();
					break;
				}

				serv_enable = FALSE;	/* 一度通常のファンクションのモードに入ったらサービスファンクションは不可能 */

				/* 最上位階層の選択 */
				first_second_flag = FIRST_KEY;
				OPR_SaveTopBottomOPRPointer((struct FUNCTION_TABLE_t *)KeisatsuServiceTable);

				/* ファンクションテーブルの確定 */
				for ( ; operation_pointer->FirstCode != '\0'; operation_pointer++) {
					if ((operation_pointer->FirstCode == decimal) && (operation_pointer->Available == OPR_YES)) {
						break;
					}
				}
				function_group = operation_pointer->FirstCode;
			}

			break;
		case FUNCTION:
			/*----------------------------*/
			/* 同位階層（正方向)		  */
			/*----------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			is_loop_end = FALSE;

			while (is_loop_end != TRUE) {
				operation_pointer++;
				if (operation_pointer->FirstCode == '\0') {
					operation_pointer = save_top_pointer;
				}

				if (operation_pointer->Available == OPR_YES) {	/* 現在の機能が有効な機能の時 */
					is_loop_end = CheckSelectFunctionEnable(operation_pointer);
				}
			}
			function_group = operation_pointer->FirstCode;

			break;
		case LEFT_ARROW:
			/*----------------------------*/
			/* 同位階層（負（逆）方向)	  */
			/*----------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			is_loop_end = FALSE;

			while (is_loop_end != TRUE) {
				if (operation_pointer == save_top_pointer) {
					operation_pointer = save_bottom_pointer;
				}
				else {
					--operation_pointer;
				}

				if (operation_pointer->Available == OPR_YES) {	/* 現在の機能が有効な機能の時 */
					is_loop_end = CheckSelectFunctionEnable(operation_pointer);
				}
			}
			function_group = operation_pointer->FirstCode;

			break;
		case ENTER:
			/*------------------------------------*/
			/* 階層の確定或いはファンクション実行 */
			/*------------------------------------*/
			serv_enable = FALSE;
			first_second_flag = FIRST_KEY;
			if (operation_pointer->NextLevel == NULL) { /** これ以上下位の階層がない */
				/** ファンクションの実行 */
				(*operation_pointer->FunctionName)();
				return;
			}
			else { /** 下位の階層がある */
				/** 下位階層へ移行  */
				OPR_SaveTopBottomOPRPointer(operation_pointer->NextLevel);
			}

			break;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			return;
		}
	}
}
#endif		/* End of (defined (KEISATSU)) */