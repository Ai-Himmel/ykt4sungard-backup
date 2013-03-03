/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_MER.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: マーキュリー設定オペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
/*#include	"\src\atlanta\define\prn_pro.h"		/* 移植まだ */
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Protype
UBYTE	SetMercuryNumber(void);
UBYTE	SetMercuryPause(void);
UBYTE	MercuryNumberInput(void);
void	SetMercury(void);
*/

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* 1996/06/26 H,Yagi *//* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*************************************************************************
	module		:[マーキュリー機能]
	function	:[
		1.マーキュリ番号の登録を行う
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
UBYTE SetMercuryNumber(void)
{
	UWORD	length;

	length = CMN_StringLength(SYB_MercuryDialBuffer);	/* マキュリー登録桁 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');	/* 上段表示 [Mercury Number    **] */
	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_MercuryNumberSet);
#if !defined(STOCKHM2) && (PRO_PREFIX_KEY == DISABLE)	/* Mod by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[OPR_DISPLAY_MAX - 2], length, MERCURY_DIGIT_MAX, '0');
#endif
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	if (MercuryNumberInput() == OK) {
		/* 入力データをセット */

		/* UPDATE BY EGUCHI 1997/05/27  */
		/* 未入力状態でセットキーが押された場合は、既に登録されている値を変更しない*/
		if (CheckCharacterInputEmpty() == FALSE) {/*未入力状態でない*/
/*			StoreCharacterInputValue(MercuryDialBuffer, ASC_DATA_TYPE); */
			StoreCharacterInputValue(SYB_MercuryDialBuffer, ASC_DATA_TYPE); /* Modified by S.Fukui Sep.18,1997 */
		}
#if (0) /*COMMENT BY EGUCHI 1997/05/27 Eguchi*/
//		if (MercuryDialBuffer[0] == NULL) {/*未入力でセットキーがおされた場合 1996/09/13 Eguchi*/
//			MercuryDialBuffer[0] = '1';
//			MercuryDialBuffer[1] = '3';
//			MercuryDialBuffer[2] = '2';
//		}
#endif
		return (OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[マーキュリポーズ時間セット]
	function	:[
			1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J05]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
	1996/06/24  H.Yagi
*************************************************************************/
UBYTE SetMercuryPause(void)
{
	UBYTE	disp_position;
	UWORD	mercury_pause_min;
	UWORD	mercury_pause_max;
	UWORD	MercuryPauseTime;

	mercury_pause_min = (UWORD)CTRY_MercuryPauseTimeMin();
	mercury_pause_max = (UWORD)CTRY_MercuryPauseTimeMax();
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_PauseTime);	/* "Time        :       " */
	FixedNumberInputRangeSet(mercury_pause_min , mercury_pause_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(mercury_pause_max));
	DisplayStringHigh(0 , D2W_MercuryPauseSet);
	MercuryPauseTime = FixedLengthNumberInput((UWORD)SYB_SettingStatus[MERCURY_PAUSE],
											  mercury_pause_min,
											  mercury_pause_max,
											  disp_position,
											  SubTitleDisplayBuffer);
	if (MercuryPauseTime != 0xFFFF) { /* 入力済み */
		SYB_SettingStatus[MERCURY_PAUSE] = (UBYTE)MercuryPauseTime;
		return (OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[マーキュリーダイアル番号入力]
	function	:[
				1
	]
	return		:[
				OK:正常終了
				NG:登録中止
				]
	common		:[
				FunctionDisplayBuffer
				CharacterInput
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/18]
	author		:[江口]
	1996/06/25  H,Yagi
*************************************************************************/
UBYTE MercuryNumberInput(void)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix number display *//* by K.Watanabe 2004/10/12 */
	UWORD	length;
#endif

	/* 使用するワークバッファをクリアする */
	ClearCharacterInput();
	CharacterInput.MaxFigure = (UBYTE)(SYS_MERCURY_BUF_MAX - 1);

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix number display *//* by K.Watanabe 2004/10/12 */
	length = CMN_StringLength(SYB_MercuryDialBuffer);
	CMN_StringCopy(CharacterInput.Buffer,SYB_MercuryDialBuffer);
	CharacterInput.CursorPosition = length;
	CharacterInput.WritePosition  = length;
#endif

	/*******************/
	/* データ入力処理  */
	/*******************/
	while (1) {

		/** 表示処理 */
		DisplayNumberInput(); /* 下段に入力状態を表示 */

		/** キー取り込み *//* カーソル移動などの処理は実行済み*/
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/** 終了 */
			CursorOff();
			return (NG);

		case SET_KEY:			/* セットキー	*/
			/*--------------------------------*/
			/* 入力された値のチェックを行う	  */
			/*--------------------------------*/
			if (CheckCharacterInputEmpty() == TRUE) { /* 入力されていない */
				CursorOff();	/* 終了する */
				return (OK);
			}

			/** チェック用のバッファにチェックする番号をセットする */
			SetToCheckBuffer(&CharacterInput.Buffer[0], NULL);
			if (CheckDirectDialNumberInput() == OK) {
				CursorOff();
				return (OK);
			}
			else {
				NackBuzzer();
				/** エラー箇所にカーソルを移動させる */
				CharacterInput.CursorPosition = ErrorPositionSet();
			}
			break;
		case DIAL_MARK_KEY:	/* ダイアル記号キー */
			CharacterInputDialCharSet();
			break;
		case REDIAL_KEY:	/* ポーズとして使用するかも */
			CharacterInputDialMarkSet(PAUSE_MARK);
			break;
		case FLASH_KEY:		/* フラッシュキー1996/04/20　追加 */
			CharacterInputDialMarkSet(FLASH_MARK);
			break;
		case MERCURY_KEY:	/* マーキュリーキー  1996/07/16 H,Yagi */
			CharacterInputDialMarkSet(MERCURY_TONE_MARK);
			break;
		case TEN_SHARP_KEY:	/* # */
/*		case TEN_ASTA_KEY:	*/
		case TEN_AST_KEY:   /* * */  /* Modified by S.Fukui Sep.18,1997 */
			CharacterDataSet_FigureCheck(key);
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[マーキュリーセット]
	function	:[
		1.マーキュリー番号のセットを行う
		2.マーキュリーポーズ時間（マーキュリーダイアルトーン検出時間）のセットを行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J-23]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/13]
	author		:[江口]
*************************************************************************/
void SetMercury(void)
{
	/*------------------------*/
	/* マーキュリー番号入力	  */
	/*------------------------*/
	if (SetMercuryNumber() == NG) {
		return;
	}
 
 #if !defined(STOCKHM2) && (PRO_PREFIX_KEY == DISABLE)	/* DVT : mod by SMuratec C.P 2004/09/06 *//* by K.Watanabe 2004/10/12 */
	/*-----------------------------*/
	/* マーキュリーポーズ時間入力  */
	/*-----------------------------*/
	if (SetMercuryPause() == NG) {
		return;
	}
 #endif
 
	ChildDisplaySetCompleted(D2W_SetMercury);
}
/*************************************************************************
	module		:[文字列の変更、プレフィクス機能のため]
	function	:[
		1.NULLを含まずに変更する（! -> [SYB_MercuryDialBuffer]）
	]
	return		:[変更後の文字列のアドレス]
	common		:[]
	condition	:[]
	comment		:[PRG-J-23]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2004/07/14]
	author		:[陳萍]
*************************************************************************/
UBYTE	*ChangeDisplayBuffer(UBYTE *string)
{
	UWORD	src_pos;		
	UWORD	dst_pos;
	UWORD	length;
	UBYTE	cnt1;
	UBYTE	cnt2;
	UBYTE*	tmp_str;
	UBYTE	src_buf[OPR_DISPLAY_MAX];
	UBYTE	tmp_buf[OPR_DISPLAY_MAX];

	tmp_str = string;
	src_pos  = 0;
	dst_pos  = 0;
	cnt1	 = 0;
	cnt2	 = 0;
	CMN_MemorySet(src_buf,OPR_DISPLAY_MAX,NULL);
	CMN_MemorySet(tmp_buf,OPR_DISPLAY_MAX,NULL);
	CMN_StringCopyNum(&src_buf[0],tmp_str,20);

	while((src_pos < 20) && (dst_pos < 20)) {
		if((src_buf[src_pos] == ',') || (src_buf[src_pos] == ':')) {
			tmp_str[dst_pos] = src_buf[src_pos];
			dst_pos++;
			src_pos++;
			cnt2 = 1;
			continue;
		}
		if(src_buf[src_pos] == '!') {
			if((cnt1 == 0) || (cnt2 == 1)) {
				length = CMN_StringLength(SYB_MercuryDialBuffer);
				if((dst_pos + length) <= 17) {
					tmp_str[dst_pos] = '['; 
					CMN_StringCopyNum(&tmp_str[dst_pos + 1],SYB_MercuryDialBuffer,length);
					tmp_str[dst_pos + length + 1] = ']';	
					dst_pos += length + 2;
					src_pos++;
				}
				else {
					if(length <= 18) {
						tmp_buf[0] = '[';
						CMN_StringCopyNum(&tmp_buf[1],SYB_MercuryDialBuffer,length);
						tmp_buf[length + 1] = ']';
					}
					else {
						tmp_buf[0] = '[';
						CMN_StringCopyNum(&tmp_buf[1],SYB_MercuryDialBuffer,19);
					}
					CMN_StringCopyNum(&tmp_str[dst_pos],&tmp_buf[0],20-src_pos);
					src_pos = 20;
				}
			}
			else {
				tmp_str[dst_pos] = src_buf[src_pos];
				dst_pos++;
				src_pos++;
			}
			cnt1 = 1;
			cnt2 = 0;
		}
		else {
			tmp_str[dst_pos] = src_buf[src_pos];
			dst_pos++;
			src_pos++;
			cnt1 = 1;
			cnt2 = 0;
		}
	}
	return(string);
}
/*************************************************************************
	module		:[文字列の変更、プレフィクス含の入力機能のため]
	function	:[
		1.NULLを含まずに変更する（! -> [SYB_MercuryDialBuffer]）
	]
	return		:[変更後の文字列のアドレス]
	common		:[]
	condition	:[]
	comment		:[PRG-J-23]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2004/07/14]
	author		:[陳萍]
*************************************************************************/
UBYTE	*ChangeInputBuffer(UBYTE *dst_str,UBYTE *src_str)
{
	UWORD	dst_pos;
	UWORD	src_pos;
	UWORD	length;
	UBYTE	cnt1;
	UBYTE	cnt2;
	UBYTE*	dst_tmp;
	UBYTE*	src_tmp;
	
	dst_tmp = dst_str;
	src_tmp = src_str;
	dst_pos = 0;
	src_pos = 0;
	cnt1	= 0;
	cnt2	= 0;
	
	while(src_tmp[src_pos] != NULL) {
		if(src_tmp[src_pos] == ' ') {
			break;
		}
		if((src_tmp[src_pos] == ',') || (src_tmp[src_pos] == ':')) {
			dst_tmp[dst_pos] = src_tmp[src_pos];
			dst_pos++;
			src_pos++;
			cnt2 = 1;
			continue;
		}
		if(src_tmp[src_pos] == '!') {
			if((cnt1 == 0) || (cnt2 == 1)) {
				length = CMN_StringLength(SYB_MercuryDialBuffer);
				
				dst_tmp[dst_pos] = '[';
				CMN_StringCopyNum(&dst_tmp[dst_pos + 1],SYB_MercuryDialBuffer,length);
				dst_tmp[dst_pos + length + 1] = ']';
				
				dst_pos += length + 2;
				src_pos++;
			}
			else {
				dst_tmp[dst_pos] = src_tmp[src_pos];
				dst_pos++;
				src_pos++;
			}
			cnt1 = 1;
			cnt2 = 0;
		}
		else {
			dst_tmp[dst_pos] = src_tmp[src_pos];
			dst_pos++;
			src_pos++;
			cnt1 = 1;
			cnt2 = 0;
		}
	}
}
#endif	/* defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
