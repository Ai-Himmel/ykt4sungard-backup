/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_DIAL.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ダイアルデータ登録
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\country.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\cmn_tbl.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
#include	"\src\atlanta\define\sys_infd.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/28 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif 		/* End of (defined (KEISATSU)) */

/* Prototype
UBYTE	OnetouchSpeedInput(void);
UBYTE	EnterOnetouchSpeedDialNumber(struct SYS_SpeedDialData_t *);
UBYTE	EnterOnetouchSpeedSubDial(struct SYS_SpeedDialData_t *);
UBYTE	DialNumberInput(UBYTE *);
UBYTE	EnterOnetouchSpeedRemoteName(struct SYS_SpeedDialData_t *);
UBYTE	DialNameInput(UBYTE *init_name);
UBYTE	EnterOnetouchSpeedGroup(struct SYS_SpeedDialData_t *);
UBYTE	GroupNumberInput(UBYTE, UDWORD);
UBYTE	CheckGroupNumberInput(UBYTE);
UBYTE	EnterOnetouchSpeedAttribute(struct SYS_SpeedDialData_t *);
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	EnterOnetouchSpeedPIN(struct SYS_SpeedDialData_t *);
#endif
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	PinNumberInput(UBYTE *, UBYTE);
#endif
void	ClearOnetouchSpeedRecord(struct SYS_SpeedDialData_t *);
void	DisplayEnterOnetouchSpeed(UBYTE);
*/

/*************************************************************************
	module		:[ワンタッチ・短縮。ダイアルデータ登録]
	function	:[
		1.ワンタッチ・短縮ダイアルの登録。
		2.FAX番号、転送番号、相手先名、グループ番号、ＰＩＮ番号、属性の登録を実行
	]
	return		:[]
	common		:[
		OPR_Buf:OntchSpdCtrl
		SYB_OnetouchDial
		SYB_SpeedDial
	]
	condition	:[ワンタッチ＋短縮個数が２５６件を越える場合、変更せなあかん箇所がある]
	comment		:[
		ユーザー側から見た短縮番号 001～170
		内部処理から見た短縮番号   000～169

		ワンタッチか短縮かはOPR_Buf.OntchSpdCtrl.SelectNumberの値できりわける
		,・ワンタッチ	：0                ～ SYS_ONETOUCH_MAX - 1
		,・短縮			：SYS_ONETOUCH_MAX ～ SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE OnetouchSpeedInput(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_number;		/* ワンタッチのデータ番号 	0				～SYS_ONETOUCH_MAX - 1						*/
#endif
	UWORD	data_number;		/* ワンタッチのデータ番号 	0				～SYS_ONETOUCH_MAX - 1						*/
								/* 短縮のデータ番号			SYS_ONETOUCH_MAX～SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1 */
	UBYTE	store_flag;			/* 既に登録データがあるかないか */
	UBYTE	onetouch_code;		/* ワンタッチ記号 */
	UBYTE	set_number;			/* ワンタッチ or 短縮の配列番号 */
	struct	SYS_SpeedDialData_t *set_dial; 	/* セットするダイアルデータの構造体を保持する変数 */

	store_flag = 0;
	data_number = OPR_Buf.OntchSpdCtrl.SelectNumber;

	/*-----------------------------------------------*/
	/** ダイアルデータをセットする構造体位置を求める */
	/*-----------------------------------------------*/
	if (data_number < SYS_ONETOUCH_MAX) {	/** ワンタッチダイアルの時 */
		set_number = (UBYTE)data_number;	/* ワンタッチの配列番号をセット */
		set_dial = &SYB_OnetouchDial[data_number];
		onetouch_code = CMN_OffsetToOnetouchCode((UBYTE)data_number);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (CheckOnetouchStoreStatus(onetouch_code) == SYS_INF_ONETOUCH_FAXNUMBER) {
			store_flag = 1;
		}
#else
		if (CheckOnetouchStoreStatus(onetouch_code) == OK) {
			store_flag = 1;
		}
#endif
	}
	else {									/** 短縮ダイアルの時 */
		set_number = (UBYTE)(data_number - SYS_ONETOUCH_MAX);	/* 短縮の配列番号をセット */
		set_dial = &SYB_SpeedDial[set_number];
		if (CheckSpeedStoreStatus(set_number) == OK) {
			store_flag = 1;
		}
	}

	if (store_flag == 0) { /** 未登録状態の場合 */
		/** データが初期化されていない可能性があるのでクリアしておく */
		ClearOnetouchSpeedRecord(set_dial);
	}

	/** ダイアル番号入力を行う */
	if (EnterOnetouchSpeedDialNumber(set_dial) == NG) {	/* ストップ */
		return (OPR_END); /*終了*/
	}

	/* ダイレクトメール防止機能用処理（登録したダイヤルの下４桁のみ別バッファに格納） by K.Watanabe 1997/10/22 */
	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチダイアルの時 */
		SYB_OnetouchJunkDial[set_number] = PickOutLastFourFigure(set_dial->Dial, 40);
	}
	else {									/* 短縮ダイヤルの時 */
		SYB_SpeedJunkDial[set_number] = PickOutLastFourFigure(set_dial->Dial, 40);
	}

	if ((set_dial->Dial[0] & 0xF0) == 0xF0) {	/** ダイアル番号が消去された場合*/

		/* ダイアルデータをクリアして終了 */
		ClearOnetouchSpeedRecord(set_dial);
		DeleteTelBookData(data_number);	/* 電話帳からも削除 1995/12/15 Eguchi*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (data_number < SYS_ONETOUCH_MAX) {
			SYB_INF_OnetouchStatus[data_number] = SYS_INF_ONETOUCH_NO_ENTRY;
		}
#endif
		if ((data_number >= SYS_ONETOUCH_MAX) && (CHK_UNI_OptionalSpeedDial())){	/* 任意短縮の時 */
			DeleteSpeedControlTable();	/* 任意短縮管理テーブルからの削除を行う */
		}
		return (OPR_CONTINUE);
	}
	else {										/** 電話番号が登録されたとき*/
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/16 Y.Matsukuma */
		return (OPR_CONTINUE);
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (data_number < SYS_ONETOUCH_MAX) {
			ClearMailAddressRecord(data_number);
			ClearOnetouchFromMailGroup(data_number);
			/* FAX番号登録済みをセット　*/
			SYB_INF_OnetouchStatus[data_number] = SYS_INF_ONETOUCH_FAXNUMBER;
		}
#endif
		if ((data_number >= SYS_ONETOUCH_MAX) &&	/* 短縮ダイアル */
			(CHK_UNI_OptionalSpeedDial() != 0 )){	/* 任意短縮の時 */
			if( SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber ) == 0xff ){
				/* 短縮ダイヤル管理未登録の時 */
				SetSpeedControlTable();	/* 短縮ダイヤル管理テーブルにセット */
			}
		}

		/** 転送先番号登録 */
		if (EnterOnetouchSpeedSubDial(set_dial) == NG) {
			return (OPR_END);
		}
		/** 相手先名入力 */
		if (EnterOnetouchSpeedRemoteName(set_dial) == NG) {
			return (OPR_END);
		}
		/* もし相手先が消去されていたら電話帳からは削除しておく 1995/09/27 Eguchi*/
		/* 電話帳にセットする際に相手先名がなければなにもしないと思うのでこの処理はいらんかも　1995/09/27 Eguchi*/
		if (set_dial->Name[0] == NULL) { /** 名前が登録されてなかった場合 */
			DeleteTelBookData(data_number); /** 電話帳から削除する */
		}
		else { /** 名前が登録されている */
			/** 電話帳にデータ登録 */
			SetTelephoneBook(data_number);
		}

		/** グループ番号入力 */
		if (EnterOnetouchSpeedGroup(set_dial) == NG) {
			return (OPR_END);
		}

#if (PRO_PIN_ACCESS == ENABLE)
		/** ＰＩＮ番号入力 -> For ANZU ダイアル個別ＰＩＮ番号入力 */
		if (EnterOnetouchSpeedPIN(set_dial) == NG) {
			return (OPR_END);
		}
#endif

		/* 属性編集 */
		if (CHK_SpeedDialSparateSet() != 0) {
			if (EnterOnetouchSpeedAttribute(set_dial) == NG) {
				/* 正常終了 */
				return (OPR_END);
			}
		}
	}
	return (OPR_CONTINUE);
}

/*************************************************************************
	module		:[ワンタッチ・短縮。電話番号登録]
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
UBYTE EnterOnetouchSpeedDialNumber(struct SYS_SpeedDialData_t *dial_position)
{
	/* 上段表示更新　「A:Fax Number        」[001:Fax Number       ]*/
	DisplayEnterOnetouchSpeed(ENTER_DIAL_NUMBER);

	/** ダイアル番号登録 */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
	if (DialNumberInput(&(dial_position -> Dial[0]),&(dial_position -> Keisatsu)) == OK) { /*登録完了*/
#else
	if (DialNumberInput(&(dial_position -> Dial[0])) == OK) { /*登録完了*/
#endif		/* End of (defined (KEISATSU)) */
		/* 新しい値をセットする */
		StoreCharacterInputValue(&(dial_position -> Dial[0]) , BCD_DATA_TYPE);

		return (OK);
	}
	else {
		return (NG);
	}
}

/*************************************************************************
	module		:[ワンタッチ・短縮。転送番号登録]
	function	:[
		1.
	]
	return		:[]
	common		:[
					SYB_SubDial
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE EnterOnetouchSpeedSubDial(struct SYS_SpeedDialData_t *dial_number)
{
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
	return (OK);
#else
	UBYTE	sub_number;
	UBYTE	no_subdial;

	no_subdial = 0;
	sub_number = 0;

	/* 転送番号格納バッファに空きがあるかと、
	   選択された短縮番号に転送先が登録されているかのチェック*/

	/** 転送ダイアル番号取りだし */
	sub_number = dial_number->SubDialPosition;

	/* リモート診断では、ダイヤル番号消去で 0xF0を書くので、判断を変更します 1998/04/01 by K.Watanabe */
/*	if (sub_number == 0xFF) {/** 転送先未登録 */
	if ((sub_number & 0xF0) == 0xF0) {	/** 転送先未登録 */
		no_subdial = 1; /* 登録しようとしているワンタッチ短縮には転送番号は登録されていないことを表す */
		/** 転送ダイアル格納領域に空きがあるか調べる */
		if ((sub_number = CheckAndGetSubDialEmptyArea()) == 0xFF) {	/** 転送先格納エリアに空きがない */
			return (OK);	/** 転送番号登録オペレーションは行わない */
		}
	}

	/* 上段表示文字列を作成   */
	/* [001:Alt. No.        ] */
	DisplayEnterOnetouchSpeed(ENTER_SUB_DIAL);

	/** 番号入力 */
	if (DialNumberInput(&(SYB_SubDial[sub_number][0])) == OK) {
		/* 新しい番号をセットする */
		/** 転送先番号格納バッファに入力された番号をセット */
		StoreCharacterInputValue(&SYB_SubDial[sub_number][0], BCD_DATA_TYPE);

		/* リモート診断では、ダイヤル番号消去で 0xF0を書くので、判断を変更します 1998/04/01 by K.Watanabe */
/*		if (SYB_SubDial[sub_number][0] == 0xFF) { /** 番号が空 ->> クリアされた */
		if ((SYB_SubDial[sub_number][0] & 0xF0) == 0xF0) {	/** 番号が空 ->> クリアされた */
			dial_number->SubDialPosition = 0xFF; /** 未登録にする */
		}
		else { /** 番号が登録された場合 */
			if (no_subdial == 1) { /** 未登録状態たっだ場合 */
				dial_number->SubDialPosition = sub_number; /** 転送先番号をセット */
			}
		}
		return (OK);
	}
	else {
		return (NG);
	}
#endif
}

/*************************************************************************
	module		:[ダイアル番号入力]
	function	:[
		1.短縮電話番号入力
		2.ワンタッチ電話番号入力
		3.転送番号入力
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
	author		:[江口,渡辺一章]
*************************************************************************/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
UBYTE DialNumberInput(UBYTE *stored_data, UBYTE *Keisatsu)	/* 登録済みデータ */
#else
UBYTE DialNumberInput(UBYTE *stored_data)	/* 登録済みデータ */
#endif		/* End of (defined (KEISATSU)) */
{
	UBYTE	key;	/* ｷｰ取り込みﾃﾞｰﾀ */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/18 */
	UBYTE	chk_bef_key;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
	UBYTE	keisatsu_mask;
#endif		/* End of (defined (KEISATSU)) */

	/* 使用するワークバッファをクリアする */
	ClearCharacterInput();
	/* 登録済みデータをチェック */
	CMN_BCD_ToASC_String(CharacterInput.Buffer, stored_data);
	CharacterInput.MaxFigure = (UBYTE)((SYS_TEL_2DIGIT_MAX - 1) * 2);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
	CharacterInput.Keisatsu = *Keisatsu;

	CharacterInput.KeisatsuPosition = SetKeisatsuBuf(CharacterInput.KeisatsuBuf, *Keisatsu);
	CharacterInput.WritePosition += CharacterInput.KeisatsuPosition;
#endif		/* End of (defined (KEISATSU)) */
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/*******************/
	/* データ入力処理  */
	/*******************/
	while (1) {

		/** 表示処理 */
		DisplayNumberInput(); /* 下段に入力状態を表示 */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/18 */
		chk_bef_key = key;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		/** キー取り込み *//* カーソル移動などの処理は実行済み*/
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/** 終了 */
			CursorOff();
			return (NG);
			
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
		case ONETOUCH_27_KEY:			/* 警電/加入 */	/* ワンタッチ２７キー		*/
			if (SYB_MachineParameter[M_PARA_SW_I1] & KEY_LOCK_KEIDEN_KANYU) {
				NackBuzzer();
				break;
			}

			keisatsu_mask = CharacterInput.Keisatsu & ~(SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU);
			switch (CharacterInput.Keisatsu & (SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU)){
			case SYS_KEISATSU_KEIDEN:
				CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KANYU;
				if ((CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU)) != 0x00) {
					CharacterInput.Keisatsu = CharacterInput.Keisatsu | SYS_KEISATSU_KOBETSU;
					CharacterInput.Keisatsu = CharacterInput.Keisatsu & ~SYS_KEISATSU_ISSEI;
				}
				break;
			case SYS_KEISATSU_KANYU:
				CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KEIDEN;
				break;
			case 0x00:
				CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KEIDEN;
				CharacterInput.WritePosition++;
      			CharacterInput.CursorPosition++; 
      			break;
			}
			UpdateKeisatsuBuf();
			break;

		case ONETOUCH_28_KEY:			/* 一斉/個別 */	/* ワンタッチ２８キー		*/
			if (SYB_MachineParameter[M_PARA_SW_I1] & KEY_LOCK_ISSEI_KOBETSU) {
				NackBuzzer();
				break;
			}
			
			keisatsu_mask = CharacterInput.Keisatsu & ~(SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU);

			if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU)) == SYS_KEISATSU_KANYU){
				switch (CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU)){
				case SYS_KEISATSU_KOBETSU:
					NackBuzzer();
					break;
				case 0x00:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KOBETSU;
					CharacterInput.WritePosition++;
	      			CharacterInput.CursorPosition++; 
					break;
				}
			}
			else {
				switch (CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU)){
				case SYS_KEISATSU_ISSEI:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KOBETSU;
					break;
				case SYS_KEISATSU_KOBETSU:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_ISSEI;
					break;
				case 0x00:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_ISSEI;
					CharacterInput.WritePosition++;
	      			CharacterInput.CursorPosition++; 
					break;
				}
			}
			UpdateKeisatsuBuf();
			break;

		case ONETOUCH_29_KEY:			/* スクランブル */	/* ワンタッチ２９キー		*/
			if (CMN_CheckScrambleSwOn() == TRUE) {
				if (SYB_MachineParameter[M_PARA_SW_I1] & KEY_LOCK_S_ON_OFF) {
					NackBuzzer();
					break;
				}

				keisatsu_mask = CharacterInput.Keisatsu & ~(SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF);
				switch (CharacterInput.Keisatsu & (SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF)){
				case SYS_KEISATSU_SCRAMBLE_ON:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_SCRAMBLE_OFF;
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO)) != 0x00) {
						CharacterInput.Keisatsu = CharacterInput.Keisatsu | SYS_KEISATSU_KYOTSU;
						CharacterInput.Keisatsu = CharacterInput.Keisatsu & ~SYS_KEISATSU_SENYO;
					}
					break;
				case SYS_KEISATSU_SCRAMBLE_OFF:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_SCRAMBLE_ON;
					break;
				case 0x00:
					CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_SCRAMBLE_ON;
					CharacterInput.WritePosition++;
	      			CharacterInput.CursorPosition++; 
					break;
				}
				UpdateKeisatsuBuf();
			}
			else {
				NackBuzzer();
			}
			break;

		case ONETOUCH_30_KEY:			/* 共通/専用 */	/* ワンタッチ３０キー		*/
			if (CMN_CheckScrambleSwOn() == TRUE) {
				if (SYB_MachineParameter[M_PARA_SW_I1] & KEY_LOCK_KYOTSU_SENYO) {
					NackBuzzer();
					break;
				}
				
				keisatsu_mask = CharacterInput.Keisatsu & ~(SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO);
				
				if ((CharacterInput.Keisatsu & (SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF)) == SYS_KEISATSU_SCRAMBLE_OFF){
					switch (CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO)){
					case SYS_KEISATSU_KYOTSU:
						NackBuzzer();
						break;
					case 0x00:
						CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KYOTSU;
						CharacterInput.WritePosition++;
		      			CharacterInput.CursorPosition++; 
						break;
					}
				}
				else {
					switch (CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO)){
					case SYS_KEISATSU_KYOTSU:
						CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_SENYO;
						break;
					case SYS_KEISATSU_SENYO:
						CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KYOTSU;
						break;
					case 0x00:
						CharacterInput.Keisatsu = keisatsu_mask | SYS_KEISATSU_KYOTSU;
						CharacterInput.WritePosition++;
		      			CharacterInput.CursorPosition++; 
						break;
					}
				}
				
				UpdateKeisatsuBuf();
			}
			else {
				NackBuzzer();
			}
			break;
#endif		/* End of (defined (KEISATSU)) */

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

#if defined(KEISATSU)			/* 警察FAX Added by SMuratec 夏 2005/06/22 */
			if (SetToCheckKeisatsuBuffer(CharacterInput.Keisatsu) == NG) {
				NackBuzzer();
				CharacterInput.CursorPosition = 0;
				break;
			}
#endif
			/* HINOKI2 NTT ファネットテスト指摘項目(No.105)
			** 40桁目にトーン記号が入力できてしまう・・・・１桁あふれている。
			** よって、ここで桁数再度確認しておく
			** by O.Kimoto 2002/10/29
			*/
#if (0)
** #if defined(FRA)
** 			/* ワンタッチ／短縮ダイヤル内に同番号があれば弾く処理追加 By S.Fukui Dec.4,1997 */
** 			if (CheckSameNumber() == TRUE) {
** 				OPR_ChildErrorFlag = ALREADY_NUMBER_STORED_ERROR;
** 				NackBuzzer();
** 				break;
** 			}
** #endif
** 			if (CheckDirectDialNumberInput() == OK) {
** 				CursorOff();
** 				return (OK);
** 			}
** 			else {
** 				NackBuzzer();
** 				/** エラー箇所にカーソルを移動させる */
** 				CharacterInput.CursorPosition = ErrorPositionSet();
** 			}
#else
 #if defined(KEISATSU)	/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/13 */
			if (CheckMaxFigureOver(CharacterInput.MaxFigure - CharacterInput.KeisatsuPosition) == TRUE) {			/* 桁数オーバー */
				NackBuzzer();
				/** エラー箇所にカーソルを移動させる */
				
				/* 入力バッファの最終がポーズ(-/)かトーン(-!)の場合だけ例外処理をします。 */
				if (   ((OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == '/') && (OPR_CharacterCheckBuffer[(OPR_CharacterCheckPoint - 1)] == '-'))
					|| ((OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == '!') && (OPR_CharacterCheckBuffer[(OPR_CharacterCheckPoint - 1)] == '-'))) {
					/* ErrorPositionSetの戻り値はCharacterInput.MaxFigure（この場合４０)である。しかしCursorPositionは0から数えているので
					** 上記のポーズ、トーンの場合だけカーソル位置が１桁右にずれてしまう。よってここでそのずれを補正する
					** by O.Kimoto 2002/10/29
					*/
					CharacterInput.CursorPosition = (UBYTE)(ErrorPositionSet() - 1) + CharacterInput.KeisatsuPosition;
				}
				else {
					CharacterInput.CursorPosition = ErrorPositionSet() + CharacterInput.KeisatsuPosition;
				}
				OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
			}
 #else
	 		if (CheckMaxFigureOver(CharacterInput.MaxFigure) == TRUE) {			/* 桁数オーバー */
				NackBuzzer();
				/** エラー箇所にカーソルを移動させる */
				
				/* 入力バッファの最終がポーズ(-/)かトーン(-!)の場合だけ例外処理をします。 */
				if (   ((OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == '/') && (OPR_CharacterCheckBuffer[(OPR_CharacterCheckPoint - 1)] == '-'))
					|| ((OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == '!') && (OPR_CharacterCheckBuffer[(OPR_CharacterCheckPoint - 1)] == '-'))) {
					/* ErrorPositionSetの戻り値はCharacterInput.MaxFigure（この場合４０)である。しかしCursorPositionは0から数えているので
					** 上記のポーズ、トーンの場合だけカーソル位置が１桁右にずれてしまう。よってここでそのずれを補正する
					** by O.Kimoto 2002/10/29
					*/
					CharacterInput.CursorPosition = (UBYTE)(ErrorPositionSet() - 1);
				}
				else {
					CharacterInput.CursorPosition = ErrorPositionSet();
				}
				OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
			}
  #endif
			else {

#if defined(FRA)
				/* ワンタッチ／短縮ダイヤル内に同番号があれば弾く処理追加 By S.Fukui Dec.4,1997 */
				if (CheckSameNumber() == TRUE) {
					OPR_ChildErrorFlag = ALREADY_NUMBER_STORED_ERROR;
					NackBuzzer();
					break;
				}
#endif
				if (CheckDirectDialNumberInput() == OK) {
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/22 */
					*Keisatsu = CharacterInput.Keisatsu;
#endif		/* End of (defined (KEISATSU)) */
					CursorOff();
					return (OK);
				}
				else {
					NackBuzzer();
					/** エラー箇所にカーソルを移動させる */
					CharacterInput.CursorPosition = ErrorPositionSet();
				}
			}
#endif
			break;
#if (PRO_MINOLTA_TEST_FUNC == DISABLE)	/* 1998/07/16 Y.Matsukuma */
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			CharacterInputDialCharSet();
			break;
		case REDIAL_KEY:		/* ポーズとして使用するかも */
			CharacterInputDialMarkSet(PAUSE_MARK);
			break;
 #if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH_KEY:			/* フラッシュキー */
			CharacterInputDialMarkSet(FLASH_MARK);
			break;
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 追加 97/11/04 T.Fukumoto */
 																		/* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE_KEY:			/* トーンキー */
			CharacterInputDialMarkSet(TONE_MARK);
			break;
 #endif
 #if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/07/17 by H.Yagi *//* by K.Watanabe 2004/10/12 */
		case MERCURY_KEY:		/* マーキュリーキー */
  #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/20 for prefix *//* by K.Watanabe 2004/10/12 */
			if(CharacterInput.CursorPosition == 0) {
				CharacterInputDialMarkSet(MERCURY_MARK);
			}
			else {
				NackBuzzer();
			}
  #else
			CharacterInputDialMarkSet(MERCURY_MARK);
  #endif
			break;
 #endif
 #if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
		case GROUND_KEY:
			if(CHK_UNI_GroundkeyCheck()){
				CharacterInputDialMarkSet(PAUSE_MARK);
			}else{
				NackBuzzer();
			}
			break;
 #endif
 #if (PRO_MULTI_LINE == ENABLE)
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
		case COPY_RESET_KEY:	/* コピーリセットキー */
  #else
		case HOLD_KEY:			/* 保留キー */
  #endif
  #if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* ２回線以上ない時は、セットできない */
			if (OPT_CountModems() <= 1) {
				NackBuzzer();
				break;
			}
  #endif
			/* 内線番号を示す「！」を保留キーにて入力 */
			if (InputPbxCheck(OPR_CHARACTER_INP) == TRUE) {
				key = '!';
/*				CharacterInputDataSet(key); 関数の中身が変わったため 1998/01/06 Y.Matsukuma */
				CharacterDataSet_FigureCheck(key);
			}
			else {
				NackBuzzer();
			}
			break;
 #endif
		case TEN_SHARP_KEY:		/* # */
		case TEN_AST_KEY:		/* * */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
			if (CharacterInput.CursorPosition < CharacterInput.KeisatsuPosition){
				NackBuzzer();
				break;
			}
#endif		/* End of (defined (KEISATSU)) */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/18 */
			if (key == TEN_AST_KEY && chk_bef_key == key && 
					CharacterInput.Buffer[CharacterInput.CursorPosition] == '*') {
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			}
			else if (key == TEN_AST_KEY && chk_bef_key == key && 
						CharacterInput.Buffer[CharacterInput.CursorPosition] == '-' &&
						CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!') { /* ダイアル記号（トーン）*/
					CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
									  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
									  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
					CharacterInput.WritePosition--;
					CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
					CharacterInput.Buffer[CharacterInput.CursorPosition] = '*';
			}
			else {
				chk_bef_key = (chk_bef_key == key? TRUE : FALSE);
				InputNumberAsteriskSharpKey(0,								/* 2001/05/01 K.Sasaki */
								key,
								&CharacterInput.Buffer[CharacterInput.CursorPosition],
								&CharacterInput.CursorPosition,
								CharacterInput.WritePosition,
								&chk_bef_key);
			}
#else
			CharacterDataSet_FigureCheck(key);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;
#endif
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ワンタッチ・短縮。相手先名登録]
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
UBYTE EnterOnetouchSpeedRemoteName(struct SYS_SpeedDialData_t *dial_number)
{
	/* 上段表示更新。[A: Remote Name         ] */ /* モード表示はNameInputにはいってから */
	DisplayEnterOnetouchSpeed(ENTER_REMOTE_NAME);

	/** 相手先名入力 */
	if (DialNameInput(&(dial_number->Name[0])) == OK) {

		/** 新しい相手先をセーブ*/
		StoreCharacterInputValue(&(dial_number->Name[0]), ASC_DATA_TYPE);

		return( OK );
	}
	else {
		return ( NG );
	}
}

/*************************************************************************
	module		:[相手先名入力]
	function	:[
		1.ワンタッチ・短縮の相手先名入力。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/04]
	author		:[江口]
*************************************************************************/
UBYTE DialNameInput(UBYTE *init_name)
{
	/* 編集用のバッファに必要なデータをセットする */
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, init_name);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = (UBYTE)(SYS_DIAL_NAME_MAX - 1);
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[ワンタッチ・短縮。グループ番号登録]
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
UBYTE EnterOnetouchSpeedGroup(struct SYS_SpeedDialData_t *dial_number)
{
	/** 上段表示文字列を作成 [A: ｸﾞﾙｰﾌﾟ ﾊﾞﾝｺﾞｳ    ]*/
	DisplayEnterOnetouchSpeed(ENTER_GROUP_NUMBER);

	/** 番号入力 */
	if (GroupNumberInput(OPR_GROUP_NUMBER_INPUT, dial_number->Group) == OK) {
		/** グループ番号をセット */
		dial_number->Group = StoreCharacterInputToLongGroup();

		return( OK );
	}
	else {
		return( NG );
	}
}

/*************************************************************************
	module		:[グループ番号の入力]
	function	:[
		1.ワンタッチ・短縮に登録するグループ番号の登録
		2.中継指示送信のグループ番号の登録
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/09]
	author		:[江口]
*************************************************************************/
UBYTE GroupNumberInput(UBYTE	type,			/* グループ番号の種類 */
					   UDWORD	group_number)	/* 登録済みのデータ   */
{
	UBYTE	key;	/* ｷｰ取り込みﾃﾞｰﾀ */

	/* 作業バッファに初期データをセット */
	ClearCharacterInput();
	CharacterInput.MaxFigure = OPR_CHARACTER_INPUT_MAX;
	StoreGroupToCharacterInput(group_number);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	if (type == OPR_RELAYGROUP_NUMBER_INPUT) { /* 中継同報のグループ番号の入力の場合 */
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_RelayTxGroupNumber;
	}

	/*******************/
	/**  キー取り込み **/
	/*******************/
	while (1) {

		/** 表示処理 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();
		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/** 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/** 入力チェックを実行 */
			if (CheckGroupNumberInput(type) == OK) {
				CursorOff();
				return (OK);
			}
			else {
				NackBuzzer();
			}
			break;
		case GROUP_KEY:			/* グループキー		*/
			/* 区切りのコンマを挿入 */
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] != ',')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] != ',')
			 && (CheckCharacterInputEmpty() == FALSE)) {
				CharacterDataSet_FigureCheck(',');
			}
			else {
				NackBuzzer();
			}
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
	module		:[グループ番号の入力チェック]
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
	date		:[1995/04/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckGroupNumberInput(UBYTE type)
{
	UBYTE	location_count;
	UBYTE	length;
	UBYTE	error_status;

	length = 0;
	location_count = 0;
	error_status = OPR_NO_ERROR;

	CharacterInput.CursorPosition = 0;

	if (CheckCharacterInputEmpty() == TRUE) { /** 未入力 */
		if (type == OPR_RELAYGROUP_NUMBER_INPUT) {	/* 中継指示送信の時 */
			/** 中継同報入力時にデータが未入力の場合はエラー*/
			OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
			return (NG);
		}
		else {
			return (OK);
		}
	}

	while (1) {
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] == NULL) {
			return (OK);
		}
		else {
#if (0)	/* アンズＬも全グループ指定可能にします 1997/11/21 Y.Matsukuma */
//	#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ANZU_Lは１０件まで 1997/10/16 Y.Matsukuma */
//			if (location_count >= GROUP_DIAL_MAX) { /* 既に10箇所入力されている */
//				OPR_ChildErrorFlag = TOO_MANY_LOCATION_ERROR;
//				return (NG);
//			}
//	#endif
#endif
			/* コマンドファイルのグループもビットアサインになったので、イチョウに合わせて
			** 登録時の入力は全グループ指定可能にします  by K.Watanabe 1997/09/25
			*/
			if (type == OPR_RELAYGROUP_NUMBER_INPUT) {	/* 中継指示送信の時 */
				if (location_count >= GROUP_DIAL_MAX) {	/* 既に10箇所入力されている */
					OPR_ChildErrorFlag = TOO_MANY_LOCATION_ERROR;
					return (NG);
				}
			}

			length = SetToCheckBuffer(&CharacterInput.Buffer[CharacterInput.CursorPosition], ',');
			if (length == 0) {	/* ,と,の間にデータがない */
				OPR_ChildErrorFlag = INVALID_GROUP_NUMBER_ERROR;
				return (NG);
			}
			else {

				/* 数字のみの入力か、桁数オーバーしていないか、範囲内に収まっているかチェック */
				error_status = CheckNumberFigureRange(GROUP_FIGURE_MAX, 0, SYS_GROUP_NUMBER_MAX);
				if (error_status == OPR_NO_ERROR) { /*エラーなし */
					CharacterInput.CursorPosition += length;
					if (CharacterInput.Buffer[CharacterInput.CursorPosition] == ',') {
						CharacterInput.CursorPosition++;
					}
					location_count++;
				}
				else {
					/* エラーコードのセット */
					if ((error_status == TOO_MANY_DIGITS_ERROR) || (error_status == INPUT_RANGE_OVER_ERROR)) {
						OPR_ChildErrorFlag = INVALID_GROUP_NUMBER_ERROR;
					}
					else {
						OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
					}
					CharacterInput.CursorPosition += ErrorPositionSet();
					return (NG);
				}
			}
		}
	}
}

/*************************************************************************
	module		:[ワンタッチ・短縮。属性登録]
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
UBYTE EnterOnetouchSpeedAttribute(struct SYS_SpeedDialData_t *dial_number)
{
	UBYTE	*atr_ptr;
	UBYTE	number;

	for (number = 1; number <= 4; number++) {
		switch (number) {
		case 1:
			atr_ptr = &(dial_number->Attribute1);
			break;
		case 2:
			atr_ptr = &(dial_number->Attribute2);
			break;
		case 3:
			atr_ptr = &(dial_number->Attribute3);
			break;
		case 4:
			atr_ptr = &(dial_number->Attribute4);
			break;
		default:
			break;
		}

		/** 属性登録初期化 */
		ClearCharacterInput();					/* 作業用バッファをクリア */
		CharacterInput.WritePosition 	  = 7; 	/* 編集後端位置をセット */
		StoreSoftDipToCharacterInput(*atr_ptr);/* 初期値を編集用に文字列形式に変換 */

		/** 上段表示 */
		DisplayEnterOnetouchSpeed((UBYTE)(ENTER_ATTRIBUTE1 + number - 1));

		/** 属性登録 */
		if (SoftDipInput() == OK) {
			/** 登録された属性をワンタッチ・短縮にセット */
			*atr_ptr = StoreCharacterInputToSoftDip();
		}
		else {
			return (NG);
		}
	}
	return (OK);
}

/*************************************************************************
	module		:[ワンタッチ・短縮。ＰＩＮ番号登録]
	function	:[
		1.要仕様検討
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
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE EnterOnetouchSpeedPIN(struct SYS_SpeedDialData_t *dial_number)
{
#if (PRO_MULTI_TTI == DISABLE) /* By H.Fujimura 1999/03/29 */
	UWORD	passcode;

	passcode = 0;
	/** プロテクトパスコードの有無をチェックする */
	if (CheckProtectPasscodeSet() == FALSE) {
		return (OK);/*注意*/
	}

	/** ＰＩＮアクセスの設定状態を調べる */
	if (CHK_PIN_AccessMode() != PIN_ACCESS_MODE1) { /* ＰＩＮアクセスＯＦＦまたはモード２*/
		/* 終了 */
		return (OK);/*注意 */
	}

	/** プロテクトパスコードの入力を行う */
	DisplayStringHigh(0, D2W_SetPIN_Number);
	/* パスコードの入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		/* 入力終了 (STOP) */
		return (NG);
	}
	/* パスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /* パスコード不一致 */
		NackBuzzer();
		ChildDisplayStringLow(D2W_InvalidNumber);
		if (ChildCompleteOperation() == OPR_END) { /*ストップキー */
			return (NG);
		}
		return (OK);
	}
#endif

	/** ＰＩＮ番号の入力を行う */
	DisplayEnterOnetouchSpeed(ENTER_PIN_NUMBER);
	if (PinNumberInput(dial_number->PIN_Number, SET_PIN_NUMBER) == OK) {
		/* ＰＩＮ番号はＭＡＸ桁まで登録すると終端文字が付けられないため
		** ＢＣＤに変換する前に0xFFで初期化した後、
		** StoreCharacterInputValue()で引数 BCD_PIN_DATA_TYPE を指定し
		** 桁数指定で変換するように変更します
		** 97/12/05 T.Fukumoto
		*/
		CMN_MemorySet(dial_number->PIN_Number, SYS_PIN_MAX, 0xFF);
		StoreCharacterInputValue(dial_number->PIN_Number, BCD_PIN_DATA_TYPE);
		return (OK);
	}
	return (NG);
}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

/*************************************************************************
	module		:[ＰＩＮ番号入力]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE PinNumberInput(UBYTE *pin_number, UBYTE mode)
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
{
	UBYTE	key;

	ClearCharacterInput();
	CharacterInput.MaxFigure = 1; /* １桁 */
	if (pin_number != NULL) {
		CMN_BCD_ToASC_StringNum(CharacterInput.Buffer, pin_number, (UBYTE)1);
	}
	CharacterInput.WritePosition = CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	while (1) {
		DisplayNumberInput();

		/* キー取り込み処理 */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/** 終了 */
			CursorOff();
			return (NG);

		case SET_KEY:			/* セットキー	*/
		case START_KEY:			/* スタートキー */
			if ((mode == SET_PIN_NUMBER && key == SET_KEY) || (mode == START_PIN_NUMBER && key == START_KEY)) {
					CursorOff();	/* 終了する */
					return (OK);
			}
			else {
				NackBuzzer();
			}
			break;
		case TEN_SHARP_KEY:		/* # */
		case TEN_AST_KEY:		/* * */ /* この場合ＰＩＮは関係ない */
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
#else
{
	UBYTE	key;

	ClearCharacterInput();
	CharacterInput.MaxFigure = SYS_PIN_MAX*2; /* ８桁 */
	if (pin_number != NULL) {
		CMN_BCD_ToASC_StringNum(CharacterInput.Buffer, pin_number, (UBYTE)SYS_PIN_MAX * 2);
	}
	CharacterInput.WritePosition = CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	while (1) {
		DisplayNumberInput();

		/* キー取り込み処理 */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/** 終了 */
			CursorOff();
			return (NG);

		case SET_KEY:			/* セットキー	*/
		case START_KEY:			/* スタートキー */
			if ((mode == SET_PIN_NUMBER && key == SET_KEY) || (mode == START_PIN_NUMBER && key == START_KEY)) {
				if (CheckCharacterInputEmpty() == FALSE) {
					CursorOff();	/* 終了する */
					return (OK);
				}
				else {
					OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
					NackBuzzer();
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case TEN_SHARP_KEY:		/* # */
		case TEN_AST_KEY:		/* * */ /* この場合ＰＩＮは関係ない */
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
#endif
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

/*************************************************************************
	module		:[ワンタッチ・短縮。ダイアルデータクリア]
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
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearOnetouchSpeedRecord(struct SYS_SpeedDialData_t *dial_data)
{
	char	sub_number;

	/** ダイアル番号をFFでクリア */
	CMN_MemorySet(&(dial_data->Dial[0]), SYS_TEL_2DIGIT_MAX, 0xFF);

	/** 相手先名をＮＵＬＬでクリアする */
#if (PRO_MINOLTA_TEST_FUNC == DISABLE)	/* 1998/07/21 Y.Matsukuma */
	CMN_MemorySet(&(dial_data->Name[0]), SYS_DIAL_NAME_MAX, NULL);
#endif

	/** グループ番号を０でクリア */
	dial_data->Group = (UDWORD)0x00000000;

#if (PRO_PIN_ACCESS == ENABLE)
	/** ＰＩＮ番号をＦＦでクリア */
	CMN_MemorySet(&(dial_data->PIN_Number[0]), SYS_PIN_MAX, 0xFF);
#endif

	/** 属性をクリア */
	dial_data->Attribute1 = MemorySwitchInitialTable[MEMORY_SW_B0];
	dial_data->Attribute2 = MemorySwitchInitialTable[MEMORY_SW_B1];
	/* 送出レベル画データ（減衰器設定値） */
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
	dial_data->Attribute2 &= ~ATTENATION;
#else
	/* 機器パラメータの画信号アッテネータが０以外の場合は、機器パラメータの値をコピーします
	** ０の場合はカントリーテーブルからコピーします
	*/
	if (SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA) {
		dial_data->Attribute2 |= SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA;
	}
	else {
		dial_data->Attribute2 |= (ATTENATION & (CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]));
	}
#endif
	dial_data->Attribute3 = MemorySwitchInitialTable[MEMORY_SW_B2];
	dial_data->Attribute4 = MemorySwitchInitialTable[MEMORY_SW_B3];

#if defined (KEISATSU) /* 警察属性 05/04/14 石橋正和 */
	dial_data->Keisatsu = 0;
#else
	/** 転送先番号の消去 */
	/* 転送先番号が登録されているかどうか調べる */
	sub_number = dial_data->SubDialPosition;
	/* リモート診断では、ダイヤル番号消去で 0xF0を書くので、判断を変更します 1998/04/01 by K.Watanabe */
/*	if (sub_number != 0xFF) { /* 転送先番号が登録されている */
	if ((sub_number & 0xF0) != 0xF0) {	/* 転送先番号が登録されている */
		/* 転送先番号をＦＦでクリア */
		CMN_MemorySet(&SYB_SubDial[sub_number][0], SYS_TEL_2DIGIT_MAX, 0xFF);
	}
	/* 転送先番号登録状態を未登録にする */
	dial_data->SubDialPosition = 0xFF;
#endif
}

/*************************************************************************
	module		:[ワンタッチ・短縮登録中の上段表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		ワーディングを表示を出す順番に並べておく必要がある
		引数の数値が表示の順番と一致していないといかん
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/05]
	author		:[江口]
*************************************************************************/
void DisplayEnterOnetouchSpeed(UBYTE mode)
{

	/* ワンタッチダイアル登録中の表示 */
	/* Fax Number -> Alt .no -> Remote Name -> Group Number -> PIN -> Attribute*/
	/* と変わっていく表示を行う */
	/* 注意！上記の順にワーディングを登録しておくこと */
	/*       または実行時に上記に順に並び替えること   */

	UBYTE position;

	position = CMN_StringLength(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_InputPageCount + (OPR_WORDING_LEN * mode),
							 (UBYTE)(OPR_DISPLAY_MAX - position));
#else
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_FaxNumber + (OPR_WORDING_LEN * mode),
							 (UBYTE)(OPR_DISPLAY_MAX - position));
#endif
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
UBYTE SetKeisatsuBuf(UBYTE  *ASC_KeisatsuStr, const UBYTE Keisatsu)
{
	UBYTE	kei_pos;
	kei_pos = 0;
	
	if (Keisatsu & SYS_KEISATSU_KEIDEN){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｹ", 1);
		kei_pos++;
	}
	else if (Keisatsu & SYS_KEISATSU_KANYU){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｶ", 1);
		kei_pos++;
	}

	if (Keisatsu & SYS_KEISATSU_ISSEI){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｲ", 1);
		kei_pos++;
	}
	else if (Keisatsu & SYS_KEISATSU_KOBETSU){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｺ", 1);
		kei_pos++;
	}

	if (Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "S", 1);
		kei_pos++;
	}
	else if (Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "N", 1);
		kei_pos++;
	}

	if (Keisatsu & SYS_KEISATSU_KYOTSU){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｷ", 1);
		kei_pos++;
	}
	else if (Keisatsu & SYS_KEISATSU_SENYO){
		CMN_StringCopyNumNotNULL(&ASC_KeisatsuStr[kei_pos], "ｾ", 1);
		kei_pos++;
	}

	return (kei_pos);
}



UBYTE SetToCheckKeisatsuBuffer(UBYTE Keisatsu_String)
{
	/* 「加入 一斉 … 」：NG */
	if ((Keisatsu_String & SYS_KEISATSU_KANYU) && (Keisatsu_String & SYS_KEISATSU_ISSEI)){
		return (NG);
	}	
	
	return (OK);
}

#endif 		/* End of (defined (KEISATSU)) */
