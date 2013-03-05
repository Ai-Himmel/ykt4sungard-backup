/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DPT.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 部門管理オペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysbatch.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdial.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"
#include	"\src\atlanta\define\sysdeprt.h"  /* added by thonda 1997/12/02 */

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Prototype
#if (PRO_DEPARTMENT == ENABLE)
void	SetDepartmentProtect(void);
void	SetDepartmentCode(void);
void	SetDepartmentOnOff(void);
//void	DepartmentCodeDisplay(UBYTE);
UBYTE	CheckDepartmentCode(void);
UBYTE	SetDeptCodeSelect(UBYTE);
void	SettingDeptCode(void);
void 	DepartmentSelectDisplay(void);
void	DisplayNumberLocation(UBYTE);
void	Del_DepartmentDuplication(UWORD, UBYTE);
#endif
*/

#if (PRO_DEPARTMENT == ENABLE)
/*************************************************************************
	module		:[部門管理プロテクトセット]
	function	:[
		1.部門管理オペレーションにプロテクトをかけるための設定
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/20]
	author		:[松隈]
*************************************************************************/
void SetDepartmentProtect(void)
{
	UWORD	passcode;

	DisplayStringHigh(0, (UBYTE *)D2W_SetDepartmentProtect);
	/* プロテクトのパスコードの有無をチェックする */
	if (CheckProtectPasscodeSet() == FALSE) {		/* パスコードが登録されていない */
		OPR_ChildErrorFlag = NO_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ﾐﾄｳﾛｸﾃﾞｽ " */
		NackBuzzer();
		return;
	}

	/* パスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, (UBYTE *)D2W_EnterProtectPasscode)) == 0xFFFF) {
		return;
	}
	/* パスコードチェック */
	if (passcode != SYB_ProtectPasscode) {	/* パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/* ON/OFF切り替え処理 */
	if (EnterSettingStatus((UBYTE *)D2W_DepartmentProtect,
						   (UBYTE *)D2W_Off2,
						   2,
						   SETTING_STATUS_23,
						   0xFF,
						   SECTION_CHECK_PROTECT_ON) == OK) {
		ChildDisplaySetCompleted(D2W_SetDepartmentProtect);    /* セット完了表示 */
	}
}


/*************************************************************************
	module		:[部門コード入力]
	function	:[
		1.４桁の数字を入力する。
		2.未登録は、空白。
		3.消去方法は、番号選択時にクリアキーで一括消去。
		4.未登録場所でセットキーで番号選択表示。
		5.終了は番号選択表示にストップキー
		6.終了時、部門コード重複チェックを行う
		7.番号上書きセット後は番号選択表示
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/26]
	author		:[桑原美紀]
*************************************************************************/
void SetDepartmentCode(void)
{
	UBYTE	set_cnt;		/* 登録番号 */

	if (CHK_SectionCheckProtect() != 0) {	/* ０ならプロテクトOFFで、０以外ならONになっている　*/
		NackBuzzer();		/* ナックブザー鳴らす */
		return;
	}

	/* セット番号の初期化 */
	OPR_Buf.DepartmentSelectNumber	= 0;

	while( 1 ){
		set_cnt	= CheckDepartmentCode();					/* 件数をｶｳﾝﾄ */
		if( set_cnt > 0 ){		/* 登録番号存在時 */
			if( SetDeptCodeSelect( set_cnt ) == NG ){		/* セット番号選択 */
#if (0)	/* 1998/05/25 By M.Kuwahara */
//				if (CheckDepartmentCode() == 0) {
//					SYB_SettingStatus[SETTING_STATUS_6] &= ~SECTION_CHECK_ON;
//					/* 登録されてなければ強制で部門管理設定をOFFにする */
//				}
#endif
/*				Del_DepartmentDuplication();				/* 重複番号詰め */
				return;
			}
		}
#if (PRO_DEPART_NEW_LIST == ENABLE)		/* 簡易時間部門管理の開始時間設定 By S.Fukui Dec.5,1997  */
		else {	/* set_cnt == 0 の時 */
			SYB_DepartManageStartTime = SYB_CurrentTime;
		}
#endif
		/* STOPｷｰが押されたら初期画面へ 97/09/16 By M.Kuwahara */
		if (SettingDeptCode() == NG) {				/* 部門コード登録 */
			if( CheckDepartmentCode() == 0 ){			/* １件も登録されずにｽﾄｯﾌﾟされた場合、初期画面に戻るようにする */
				SYB_SettingStatus[SETTING_STATUS_6] &= ~SECTION_CHECK_ON;	/* 1998/05/25 Add By M.Kuwahara */
				/* 登録されてなければ強制で部門管理設定をOFFにする */
			}
/*			Del_DepartmentDuplication();			/* 重複番号詰め */
			return;
		}
		if( CheckDepartmentCode() == 0 ){			/* １件も登録されずにｽﾄｯﾌﾟされた場合、初期画面に戻るようにする */
			SYB_SettingStatus[SETTING_STATUS_6] &= ~SECTION_CHECK_ON;	/* 1998/05/25 Add By M.Kuwahara */
			/* 登録されてなければ強制で部門管理設定をOFFにする */
			return;
		}
	}
}


/*************************************************************************
	module		:[部門コード登録番号選択の入力]
	function	:[
			1.部門コード登録番号を選択（直接入力も可）
			2.番号が最小になった時登録件数の最後に移動
			3.番号が最大になった時登録件数の先頭に移動
			4.クリアキーで部門コードを消去（確認無し）
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/26]
	author		:[桑原美紀]
*************************************************************************/
UBYTE				SetDeptCodeSelect(
						 UBYTE	SetMax)		/* セット番号最大値 */
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	set_no;
	UBYTE	loop;
	UBYTE	set_cnt;

	ClearCharacterInput();
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	CharacterInput.WritePosition = 3;
#else
	CharacterInput.WritePosition = 2;
#endif
	CharacterInput.LcdDisplayPosition = 0;
	set_cnt	= SetMax;
	while (1) {
		DepartmentSelectDisplay();				/* 表示処理 */
/*		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));*/

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (NG);
		case ENTER:
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				return (OK);
			}
			break;
		case FUNCTION:
			/* 選択番号を進める */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				if((UBYTE)(OPR_Buf.DepartmentSelectNumber+1) > set_cnt ){	/* 最大値以上は進まない */
					OPR_Buf.DepartmentSelectNumber	= 0;
				}
				else{
					if((OPR_Buf.DepartmentSelectNumber+1) >= SYS_DEPART_MAX ){	/* ｶｰｿﾙが最大件数目の時 */
						OPR_Buf.DepartmentSelectNumber	= 0;
					}
					else{
						OPR_Buf.DepartmentSelectNumber++;
					}
				}
			}
			break;
		case LEFT_ARROW:
			/* 選択番号を戻す */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
				NackBuzzer();
			}
			else {
				if( OPR_Buf.DepartmentSelectNumber <= 0 ){	/* 最小値以下は進まない */
					if( set_cnt == SYS_DEPART_MAX ){		/* 最大件数入力済みの時 */
						OPR_Buf.DepartmentSelectNumber	= set_cnt - (UBYTE)1;	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
					}
					else{
						OPR_Buf.DepartmentSelectNumber	= set_cnt;
					}
				}
				else{
					OPR_Buf.DepartmentSelectNumber--;
				}
			}
			break;
		case CLEAR:
			/* ﾃﾞｰﾀ自体クリア */
			if (CharacterInput.CursorPosition > 0) {
				/* 選択番号をテンキーで入力中 */
/*				NackBuzzer();*/
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
			else {
				if( SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] == 0xFFFF ){		/* データ無しの時 */
					NackBuzzer();
					break;
				}

#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 追加 By S.Fukui Jan.6,1998  */
				/* 表示バッファクリア*/
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				CMN_UnsignedIntToASC(FunctionDisplayBufferHigh, 
								 (UWORD)SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber],
								 DPTCODE_MAX, '0');
				CMN_StringCopy(&FunctionDisplayBufferHigh[4], &D2W_EraseDepartCode[4]);	/* "1234:ﾌﾞﾓﾝｺｰﾄﾞ ｼｮｳｷｮ " */

				if (ConfirmKeyInputOperation(FunctionDisplayBufferHigh,
											 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
											 ENTER,
								 			 FUNCTION) == CONFIRM_EXEC) {	/* 実行が選択された時 */
					
					for (loop = OPR_Buf.DepartmentSelectNumber; loop < SYS_DEPART_MAX; loop++ ){
						if( SYB_DepartmentCode[loop] == 0xFFFF ){
							break;
						}
						SYB_DepartmentCode[loop] = SYB_DepartmentCode[loop + 1];
						SYB_DepartManageTimeFile[loop].Timer = SYB_DepartManageTimeFile[loop + 1].Timer;
						SYB_DepartManageTimeFile[loop].Page  = SYB_DepartManageTimeFile[loop + 1].Page;
					}
					if( loop >= SYS_DEPART_MAX ){
						SYB_DepartmentCode[loop - 1]	= 0xFFFF;
						SYB_DepartManageTimeFile[SYS_DEPART_MAX - 1].Timer = 0x00000000;
						SYB_DepartManageTimeFile[SYS_DEPART_MAX - 1].Page  = 0x0000;
					}
					/* 消去完了表示処理 */
					if (ClearCompleteDisplayOperation(FunctionDisplayBufferHigh) == OPR_END) {
						return(NG);
					}
				}

#else
				for (loop = OPR_Buf.DepartmentSelectNumber; loop < SYS_DEPART_MAX; loop++ ){
					if( SYB_DepartmentCode[loop] == 0xFFFF ){
						break;
					}
					SYB_DepartmentCode[loop] = SYB_DepartmentCode[loop + 1];
				}
				if( loop >= SYS_DEPART_MAX ){
					SYB_DepartmentCode[loop - 1]	= 0xFFFF;
				}
#endif	/* (PRO_DEPART_NEW_LIST == ENABLE) */

				CharacterInput.CursorPosition	= 0;
				if(( set_cnt = CheckDepartmentCode()) == 0 ){			/* 件数をｶｳﾝﾄ */
					return(OK);
				}
			}
			break;
		case NUMBER:
			if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* 桁数オーバー(あり得ない) */
				NackBuzzer();
			}
			else {
				CharacterInput.Buffer[CharacterInput.CursorPosition++] = key;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;

				if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {
					set_no	= (UBYTE)CMN_ASC_ToUnsignedInt( CharacterInput.Buffer,
														   	CharacterInput.CursorPosition);
					if(( set_no == 0 ) ||
					   ( set_no > SYS_DEPART_MAX ) ||
					   ((set_no - (UBYTE)1) > set_cnt )){	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
						NackBuzzer();
					}
					else {
						OPR_Buf.DepartmentSelectNumber = set_no - (UBYTE)1;	/* add (UBYTE) 1997/06/25 Y.Matsukuma */
					}
					CharacterInput.CursorPosition = 0;
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
	return( OK );
}

/*************************************************************************
	module		:[部門コードの登録]
	function	:[
			1.部門コードを登録する
			2.全ての文字がクリアされた時、番号を詰める
			3.新規入力の時、次番号入力画面へ進む
			4.上書きの時、番号選択画面に戻る
				]
	return		:[	OK: 正常終了
					NG: 異常終了（ＳＴＯＰキー）
]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/05/26]
	author		:[桑原美紀]
*************************************************************************/
UBYTE			SettingDeptCode( void )
{
	UBYTE	is_new;			/* 新規/上書き入力 */
	UBYTE	i;
	UBYTE	loop;
	UBYTE	ret;
	UWORD	code;		/* 97/11/07 By M.Kuwahara */
#if (PRO_DEPART_NEW_LIST == ENABLE)
	UBYTE	counter;	/* added by thonda 1997/12/02 */
	UBYTE	pointer;	/* added by thonda 1997/12/02 */
#endif

	if( SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] == 0xFFFF ){	/* 新規入力か？ */
		is_new = 1;
	}
	else{
		is_new = 0;
	}

#if (0)
//	/* ワークエリア初期化 */
//	ClearCharacterInput();
//	CharacterInput.WritePosition = 0;
//	CharacterInput.MaxFigure = DPTCODE_MAX;
//#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
//	CharacterInput.LcdDisplayPosition = 4;
//#else
//	CharacterInput.LcdDisplayPosition = 3;
//#endif
//	CMN_UnsignedIntToASC(CharacterInput.Buffer, 
//						 SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber], 
//						 DPTCODE_MAX, '0');
#endif
	CharacterInput.Buffer[0]	= NULL;
	while( 1 ){
		if((ret	= InputNumberRotation(OPR_TX_DEPART_CODE_INPUT)) == NG ){		/* 部門コードの入力 */
/*			break;*/		/* 97/09/16 By M.Kuwahara */
			return( NG );	/* STOPキーが押された時だけ初期画面へ */
		}
		i = (UBYTE)CMN_StringLength(CharacterInput.Buffer);		/* 文字数のｶｳﾝﾄ */
		if( i == 0 ){							/* 全ての文字がクリアされた時,番号を詰める */
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 編集モードでのコード削除禁止 By S.Fukui Jan.6,1998  */
			NackBuzzer();
#else
			for (loop = OPR_Buf.DepartmentSelectNumber; loop < SYS_DEPART_MAX; loop++ ){
				if( SYB_DepartmentCode[loop] == 0xFFFF ){
					break;
				}
				SYB_DepartmentCode[loop] = SYB_DepartmentCode[loop + 1];
			}
			if( loop >= SYS_DEPART_MAX ){
				SYB_DepartmentCode[loop - 1] = 0xFFFF;
			}
#endif
			break;								/* 入力無しでセットされた時,選択画面へ */

		}
		else if( i == DPTCODE_MAX ){			/* 入力ＯＫの時 */
			/* 一件毎に重複チェックを行う	 97/11/07 By M.Kuwahara */
			code = CharacterInputToNumber();
			if ( Del_DepartmentDuplication( code, OPR_Buf.DepartmentSelectNumber ) == NG ) {	/* 重複番号チェック */
				NackBuzzer();
				ChildDisplayStringLow(D2W_SetSameNumber);	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ" */
				continue;
			}
#if (PRO_DEPART_NEW_LIST == ENABLE)				/* added by thonda 1997/12/18 */
			if (CheckDepartmentCode() == SYS_DEPART_MAX) {  /* 部門ｺｰﾄﾞがＭＡＸ登録されている */
				NackBuzzer();
				ChildDisplayStringLow(D2W_DepartCodeFull);  /* "ﾄｳﾛｸ ﾊ 100ｹﾝ ﾏﾃﾞﾃﾞｽ " */
				continue;
			}
#endif
/*			SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] = CharacterInputToNumber();*/
#if (PRO_DEPART_NEW_LIST == DISABLE)							/* added by thonda 1997/12/02 */
			SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] = code;
#endif
#if (PRO_DEPART_NEW_LIST == ENABLE)  /* added by thonda 1997/12/02 */
			if (SYB_DepartmentCode[0] != 0xffff) {				/* 部門ｺｰﾄﾞﾘｽﾄが空でない */
				for (pointer = 0; pointer < SYS_DEPART_MAX; pointer++) {  /* ｿｰﾃｨﾝｸﾞします */
					if (SYB_DepartmentCode[pointer] > code) {
						counter = CheckDepartmentCode();
						for ( ; counter > pointer; counter--) {
							SYB_DepartmentCode[counter]         = SYB_DepartmentCode[counter - 1];
							SYB_DepartManageTimeFile[counter].Timer = SYB_DepartManageTimeFile[counter - 1].Timer;
							SYB_DepartManageTimeFile[counter].Page  = SYB_DepartManageTimeFile[counter - 1].Page;
						}
						SYB_DepartmentCode[pointer]         = code;	/* 下にずらしたあとに書き込みます */
						SYB_DepartManageTimeFile[pointer].Timer = 0x00000000;
						SYB_DepartManageTimeFile[pointer].Page  = 0x0000;
						break;
					}
				}
			}
			else {
			SYB_DepartmentCode[0] = code;				/* 部門ｺｰﾄﾞﾘｽﾄが空なので先頭に書き込みます */
			}
#endif  /* #if (PRO_DEPART_NEW_LIST == ENABLE) */
			if (OPR_Buf.DepartmentSelectNumber >= SYS_DEPART_MAX - 1) {	 	/* 最大値 */
				OPR_Buf.DepartmentSelectNumber = 0;
 			}
			else {
				OPR_Buf.DepartmentSelectNumber++;
			}
			if( is_new == 0 ){							/* 上書き入力の時,選択画面へ */
				break;
			}
/*			CharacterInput.CursorPosition	= 0;		/* 97/11/07 By M.Kuwahara */
			CharacterInput.Buffer[0]	= NULL;
		}
		else{
			NackBuzzer();
		}
	}
	if( is_new == 1 ){									/* 新規入力の時 */
		OPR_Buf.DepartmentSelectNumber	= 0;
	}
	return( OK );
}

/*************************************************************************
	module		:[部門管理セット]
	function	:[
		1.この処理を実行するには、プロテクトが解除されていることと
		, 部門コードが、少なくとも、１部門は、登録されていることが
		, 必要となる。
		2.ＦＡＸからのダイヤルを部門コードで管理する/しないの切り替え
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/20]
	author		:[松隈]
*************************************************************************/
void SetDepartmentOnOff(void)
{

	if (CHK_SectionCheckProtect() == 0) {			/* ０ならプロテクトOFFで０以外ならプロテクトON */
		if (CheckDepartmentCode() != 0) {			/* 部門コードが登録してあるか */
			if (EnterSettingStatus((UBYTE *)D2W_DepartmentOnOff,
								   (UBYTE *)D2W_Off2,
								   2,
								   SETTING_STATUS_6,
								   0xFF,
								   SECTION_CHECK_ON) == OK) {
				ChildDisplaySetCompleted(D2W_SetDepartmentOnOff);
			}
		}
		else {
			OPR_ChildErrorFlag = NO_DEPARTMENTCODE_ERROR;
			NackBuzzer();
		}
	}
	else {
		NackBuzzer();
	}
}

/*************************************************************************
	module		:[部門コード選択表示]
	function	:[部門コードの選択表示を行う。]
	return		:[なし]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/05/26]
	author		:[桑原美紀]
*************************************************************************/
void DepartmentSelectDisplay(void)
{
	/* 上段「ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ 」*/
	/* 下段「001:                」「001:1234            」「1                  」*/

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_DepartmentSelectNumber);		/*"ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ"*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/** 通常入力中 */
	if (CharacterInput.CursorPosition == 0) {
		/* 注）表示は001から始める */
		CMN_UnsignedIntToASC(CharacterInput.Buffer,
							 (UWORD)OPR_Buf.DepartmentSelectNumber + 1,
						 	 CharacterInput.WritePosition,
							 '0');
		CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.Buffer);
		FunctionDisplayBufferLow[CharacterInput.WritePosition] = ':';
		/** 部門コード番号を取り出し、ASCIIになおして表示バッファにコピー */
		if( SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] != 0xFFFF ){
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[CharacterInput.WritePosition+1], 
								 (UWORD)SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber],
								 DPTCODE_MAX, '0');
		}
	}
	else {
		CMN_StringCopy(&FunctionDisplayBufferLow[0], CharacterInput.Buffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[部門コード登録チェック]
	function	:[
				1.部門コードの登録の有無
				2.データ存在時、件数を返すよう変更( 1997/05/27 M.Kuwahara )
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/12/20]
	author		:[松隈]
*************************************************************************/
UBYTE CheckDepartmentCode(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_DEPART_MAX; i++) {
		if (SYB_DepartmentCode[i] == 0xFFFF) {
/*			return(TRUE);*/
			break;
		}
	}
	return(i);
}

/*************************************************************************
	module		:[部門コード重複分削除]
	function	:[
	]
	return		:[
				]
	common		:[
				]
	condition	:[]
	comment		:[	部門コードセット終了時に重複分を削除していたのを、
					一件登録毎に同じコードが無いかチェックするように変更	* 97/11/07 By M.Kuwahara 
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/27]
	author		:[桑原美紀]
*************************************************************************/
#if (0)
//void	 Del_DepartmentDuplication( void )
//{
//	UWORD	dept_code;	/* 検索用ｺｰﾄﾞﾜｰｸ */
//	UBYTE	point;		/* 検索用ﾙｰﾌﾟ */
//	UBYTE	search;		/* 件数用ﾙｰﾌﾟ */
//	UBYTE	loop;		/* 移動用ﾙｰﾌﾟ */
//	UBYTE	is_dept;	/* ｺｰﾄﾞﾁｪｯｸ用ﾌﾗｸﾞ */
//
//	point	= 0;
//	while( point < SYS_DEPART_MAX ){
//		if( SYB_DepartmentCode[point] == 0xffff ){	/* 検索終了 */
//			break;
//		}
//		
//		dept_code	= SYB_DepartmentCode[point];
//		is_dept	= 0;
//		for( search = point + (UBYTE)1; search < SYS_DEPART_MAX; search++ ){	/* add (UBYTE) 1997/06/25 Y.Matsukuma *///
//			if( SYB_DepartmentCode[search] == 0xffff ){
//				break;
//			}
//			if( dept_code == SYB_DepartmentCode[search] ){
//				is_dept	= 1;
//				break;
//			}
//		}
//		if( is_dept == 1 ){		/* 同じコード存在時 */
//			for( loop = search; loop < SYS_DEPART_MAX; loop++ ){		/* 同じコードの所を詰める */
//				if( SYB_DepartmentCode[loop] == 0xffff ){	/* 移動終了 */
//					break;
//				}
//				SYB_DepartmentCode[loop]	= SYB_DepartmentCode[loop+1];
//			}
//			if( loop == SYS_DEPART_MAX ){		/* 最大値のみ */
//			 	SYB_DepartmentCode[loop-1] = 0xffff;
//			}
//		}
//		else{
//			point++;
//		}
//	}
//}
#endif

UBYTE	 Del_DepartmentDuplication( 
				UWORD	Code, 
				UBYTE	Point )
{
	UBYTE	loop;		/* 移動用ﾙｰﾌﾟ */

	loop	= 0;
	while( loop < SYS_DEPART_MAX ){
		if ( SYB_DepartmentCode[loop] == 0xffff ) {	/* 検索終了 */
			break;
		}
#if (PRO_DEPART_NEW_LIST == DISABLE)  /* bythonda 1997/12/15 */
		if ( loop == Point ) {
			loop++;
			continue;
		}
#endif
		if ( SYB_DepartmentCode[loop] == Code ) {
			return( NG );
		}
		loop++;
	}
	return( OK );
}

#endif	/* (PRO_DEPARTMENT == ENABLE) */


#if (PRO_DEPART_NEW_LIST == ENABLE)  /* added by thonda 1997/12/03 */
/*************************************************************************
	module		:[簡易料金管理リストプリント]
	function	:[
		1.簡易料金管理のリストの記録をプリントする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/03]
	author		:[本多智幸]
*************************************************************************/
void PrintDepartTimeList(void)
{
	if (CHK_SectionCheckProtect() == 0) {			/* ０ならプロテクトOFFで０以外ならプロテクトON */
		if (CheckDepartmentCode() != 0) {			/* 部門コードが登録してあるか */
			FinalListPrintOperation(LST_DEPARTMANAGE_LIST);
		}
		else {
			OPR_ChildErrorFlag = NO_DEPARTMENTCODE_ERROR;
			NackBuzzer();
		}
	}
	else {
		NackBuzzer();
	}
	
}

/*************************************************************************
	module		:[簡易料金管理リスト消去]
	function	:[
		1.簡易料金管理リストの記録を消去する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/03]
	author		:[本多智幸]
*************************************************************************/
void EraseDepartTimeList(void)
{
	UBYTE	i;

#if (0)
** 	/* 部門管理プロテクトのチェックが抜けてます。
** 	** by O.Kimoto 1999/02/10
** 	*/
** 	/* 消去前にもう一度、確認を行います */
** 	if (ConfirmKeyInputOperation(D2W_EraseDepartTimeListMode,
** 								 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
** 								 ENTER,
** 								 FUNCTION) == CONFIRM_EXEC) {	/* 実行が選択された時 */
** 		
** 		for (i = 0; i < SYS_DEPART_MAX; i++) {                    /* この行が確認のｵﾍﾟﾚｰｼｮﾝの前に記述してあった。 */
** 			SYB_DepartManageTimeFile[i].Timer = 0x00000000;       /* そのためｾｯﾄを押さなくてもﾘｽﾄが消去されて     */
** 			SYB_DepartManageTimeFile[i].Page  = 0x0000;           /* しまっていました。だからここに移動しました。 */
** 		}                                                         /* modified by thonda 1998/02/06                */
**         
** 		/* 簡易時間部門管理の開始時間再設定 By S.Fukui Dec.5,1997  */
** 		SYB_DepartManageStartTime = SYB_CurrentTime;
** 
** 		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
** 	}
#else
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	if (CHK_SectionCheckProtect() == 0) {			/* ０ならプロテクトOFFで０以外ならプロテクトON */
		/* 消去前にもう一度、確認を行います */
		if (ConfirmKeyInputOperation(D2W_EraseDepartTimeListMode,
									 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
									 ENTER,
									 FUNCTION) == CONFIRM_EXEC) {	/* 実行が選択された時 */
			
			for (i = 0; i < SYS_DEPART_MAX; i++) {                    /* この行が確認のｵﾍﾟﾚｰｼｮﾝの前に記述してあった。 */
				SYB_DepartManageTimeFile[i].Timer = 0x00000000;       /* そのためｾｯﾄを押さなくてもﾘｽﾄが消去されて     */
				SYB_DepartManageTimeFile[i].Page  = 0x0000;           /* しまっていました。だからここに移動しました。 */
			}                                                         /* modified by thonda 1998/02/06                */
	        
			/* 簡易時間部門管理の開始時間再設定 By S.Fukui Dec.5,1997  */
			SYB_DepartManageStartTime = SYB_CurrentTime;

			ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
		}
	}
	else {
		NackBuzzer();
	}
 #else
	/* 消去前にもう一度、確認を行います */
	if (ConfirmKeyInputOperation(D2W_EraseDepartTimeListMode,
								 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {	/* 実行が選択された時 */
		
		for (i = 0; i < SYS_DEPART_MAX; i++) {                    /* この行が確認のｵﾍﾟﾚｰｼｮﾝの前に記述してあった。 */
			SYB_DepartManageTimeFile[i].Timer = 0x00000000;       /* そのためｾｯﾄを押さなくてもﾘｽﾄが消去されて     */
			SYB_DepartManageTimeFile[i].Page  = 0x0000;           /* しまっていました。だからここに移動しました。 */
		}                                                         /* modified by thonda 1998/02/06                */
        
		/* 簡易時間部門管理の開始時間再設定 By S.Fukui Dec.5,1997  */
		SYB_DepartManageStartTime = SYB_CurrentTime;

		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
 #endif
#endif

}
#endif

