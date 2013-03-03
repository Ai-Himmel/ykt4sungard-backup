/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		\src\kobe\anzu\src\fcm_getd.cを移植			 */
/*	ファイル名	 : FCM_GETD.C												 */
/*	モジュール	 :															 */
/*				 : SetPartnerAbility()										 */
/*				 : FCM_GetDialData()										 */
/*				 : GetDialNumber()											 */
/*				 : DecrementRedialCount()									 */
/*				 : GetCommandFileData()										 */
/*				 : GetPinNumber(void)										 */
/*	作成者		 : 山口														 */
/*	日	付		 :															 */
/*	概	要		 : ＦＡＸ通信ダイアル・データ取得モジュール					 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"

#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"			/* '94,10,14 By N.S. */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\sysdoc.h"				/* 1998/10/06 H.Yoshikawa */

#include "\src\atlanta\define\fcm_def.h"
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi*/
#include "\src\atlanta\define\syscomf.h"		/* 1994/11/01 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
#include  "\src\atlanta\define\sys_stat.h"
#endif

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#if 0	/* defined(FRA) *//* del by M.HARADA '96/11/15 */	/* by M.HARADA 1995/04/18 */

 #include "\src\atlanta\define\uni_pro.h" /*1996/04/17 Eguchi*/

 #include "\src\atlanta\define\atd_def.h"		/* add by M.HARADA 95.08.22 */
 void		ClearSpeedRecord(UWORD SpeedNumber );	/*短縮番号*/
 void		ClearOnetouchRecord(UBYTE OnetouchSw );	/*ワンタッチキー番号*/
#endif

#include	"\src\atlanta\define\std.h"	/* 96/06/06 */
#include	"\src\atlanta\define\uni_pro.h"

/*************************************************************************
	module		:[ワンタッチ／スピード・ダイアルに登録された個別設定を
				  取ってくる。
	]
	function	:[]
	commom		:[
		PartnerAbility0			: メモリ・スイッチＢ０
		PartnerAbility1			: メモリ・スイッチＢ１
		PartnerAbility2			: メモリ・スイッチＢ２
		PartnerAbility3			: メモリ・スイッチＢ3
		PartnerAbilityR0		: メモリ・スイッチ受信
		AvailableTxBaudRate		: 送信可能ボーレイト
		TxSpeedHandshakeFlag	: 短縮ハンドシェーク送信フラグ
		SYB_SpeedDial[]			: 短縮ダイアル
		SYB_OnetouchDial[]		: ワンタッチダイアル
		SYB_2ndSpeedDial[]		: 第２短縮ダイアル
		SYB_2ndOnetouchDial[]	: 第２ワンタッチダイアル
		Offset_2ndDial			: 第２短縮/ワンタッチ用オフセット

	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[山口]

*************************************************************************/
void	SetPartnerAbility(void)
{
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
	UBYTE ability1;
	
	ability1 = PartnerAbility1;
#endif
	
	/* PartnerAbility0,1,2,3には既にSYS_MemorySwitch[10],[11],[12]が登録されている。*/
	switch (DialKind) {	/** ダイアル種別 */
	case SYS_SPEED_DIAL:
		if ( SpeedDialPosition < SYS_SPEED_DIAL_MAX ) {		/** 短縮の判別 */
			PartnerAbility0 = SYB_SpeedDial[SpeedDialPosition].Attribute1;
			PartnerAbility1 = SYB_SpeedDial[SpeedDialPosition].Attribute2;
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
			if ((PartnerAbility1 & ATTENATION) == 0) {
				PartnerAbility1 |= (ability1 & ATTENATION);
			}
#endif
			PartnerAbility2 = SYB_SpeedDial[SpeedDialPosition].Attribute3;
			PartnerAbility3 = SYB_SpeedDial[SpeedDialPosition].Attribute4;
		}
		break;
	case SYS_ONETOUCH_DIAL:
		if ( OnetouchDialPosition < SYS_ONETOUCH_MAX ) {		/** ワンタッチの判別 */
			PartnerAbility0 = SYB_OnetouchDial[OnetouchDialPosition].Attribute1;
			PartnerAbility1 = SYB_OnetouchDial[OnetouchDialPosition].Attribute2;
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
			if ((PartnerAbility1 & ATTENATION) == 0) {
				PartnerAbility1 |= (ability1 & ATTENATION);
			}
#endif
			PartnerAbility2 = SYB_OnetouchDial[OnetouchDialPosition].Attribute3;
			PartnerAbility3 = SYB_OnetouchDial[OnetouchDialPosition].Attribute4;
		}
		break;
	default:
		break;
	}
	if (CommandFileAbility & SYS_OVERSEA) {		/** 通信予約の付加情報がたっているか *//* 1994/11/01 */
		PartnerAbility0 |= OVERRIDE_1ST_DIS;	/** B:0-4 ON → B:0-5 */
	}
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* By H.Fujimura 1999/01/05 */
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	if (!CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (CommandFileAbility & SYS_TTI_TX_AVAILABLE) {	/** 通信予約の付加情報がたっているか */
			PartnerAbility2 |= TTI_TX_AVAILABLE;			/** B:2-4 ON */
		}
		else {
			PartnerAbility2 &= ~TTI_TX_AVAILABLE;			/** B:2-4 OFF */
		}
	}
#endif

	/* 個別属性セーブ 1997/01/27 Y.Murata */
	SYS_FaxComAbility0[0] = PartnerAbility0;
	SYS_FaxComAbility1[0] = PartnerAbility1;
	SYS_FaxComAbility2[0] = PartnerAbility2;
	SYS_FaxComAbility3[0] = PartnerAbility3;

	InitializeBaudrate();					/** ボーレイト初期化 */

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
	/* Ｖ．８ハンドシェーク中のノイズ対策 by O.Kimoto 1999/04/13 */
	if(FCM_V34TransmitDisable()) {
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
		V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求セット */
	}

 #if defined(POPLAR_F)	/* 1999/11/16 Y.Murata とりあえず新Ｌ４００だけ */
	if (SYS_CurrentExecutingCommand->Option & SYS_V34_STUP_RECOVER) {
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
		V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求セット */
	}
 #endif
#endif

#if (PRO_MULTI_LINE == DISABLE)	/* PRO_MULTI_LINE部ができるまでは、この条件を入れておきます 1998/10/12 H.Yoshikawa */
	/*---------------------------------------------------------------------
	** 属性にＥＣＭ＿ＯＮ／ＯＦＦを追加しました
	** このBitは機器設定でECM_ON設定で、受信機がECM_ONのときでも、ECM_OFF送信するためのものです。
	** 機器設定でECM_OFF設定の場合は、属性がECM_ONでも、ECM_OFF送信します。
	** 1998/10/06 H.Yoshikawa
	*/
	if (CHK_ECM_ON() && !FCM_ECM_TxOFF()) {
		TxECM_Ability				= ECM_ON;					/** ＥＣＭ送信ＯＮ／ＯＦＦ指定 */
		RxECM_Ability				= ECM_ON;					/** ＥＣＭ受信ＯＮ／ＯＦＦ指定 */

#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1998/01/27 */
		SetAvailableCodingMethodEcmOn();
#else
		if (CHK_UNI_StoredMethodMMR()) {
			AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
			AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
		}
		else {
			AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
			AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
		}
  #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
		if (CHK_UNI_JBIG_TX_Enable()) {
			AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
		if (CHK_UNI_JBIG_RX_Enable()) {
			AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
  #endif
#endif
	}
	else {
		TxECM_Ability				= ECM_OFF;					/** ＥＣＭ送信ＯＮ／ＯＦＦ指定 */
		RxECM_Ability				= ECM_OFF;					/** ＥＣＭ受信ＯＮ／ＯＦＦ指定 */
		AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
		AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
	}
#endif

	/*------------------------------*/
	/* 短縮ハンドシェーク送信の確定 */
	/*------------------------------*/
#if (PRO_TX_SPEED == V34 ) /* Modified by H.Kubo 1997/08/05 */
	FCM_SetHandshakeAttribute();		/** ハンドシェーク属性の設定 */
#else /* (PRO_TX_SPEED == V34 ) */
	if (SpeedHandshakeRomCheck() == TRUE){
		if((FCM_PtnrChkSpeedHandshake144())
		&& ((AvailableTxBaudRate == BPS14400_V17) || (AvailableTxBaudRate == BPS14400_V33))){

			if (CHK_UNI_OptionSpeedHandshake()) {	/* 応用通信の時にも短縮ﾊﾝﾄﾞｼｪｰｸを行なう時 */
				TxSpeedHandshakeFlag =1;
			}
			else {
				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&		  /* スキャナ親展送信	  */
					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&		  /* メモリ親展送信		  */
					(CommandFileOptionItem != SYS_CIPHER_TX) &&				  /* 暗号化送信 1997/06/18  By T.Yamaguchi */
					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&	/* スキャナ中継指示送信 */
					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* メモリ中継指示送信は短縮しない  */

					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
				}
			}
		}
		if ((FCM_PtnrChkSpeedHandshake96())
		&& ((BPS9600_V29  == AvailableTxBaudRate) || (BPS9600_V17  == AvailableTxBaudRate) ||
			(BPS12000_V33 == AvailableTxBaudRate) || (BPS14400_V33 == AvailableTxBaudRate) ||
			(BPS12000_V17 == AvailableTxBaudRate) || (BPS14400_V17 == AvailableTxBaudRate))) {

			if (CHK_UNI_OptionSpeedHandshake()) {	/* 応用通信の時にも短縮ﾊﾝﾄﾞｼｪｰｸを行なう時 */
				TxSpeedHandshakeFlag =1;
				AvailableTxBaudRate = BPS9600_V29;			/** 送信可能ボーレイト９６００ＢＰＳセット */
			}
			else {
				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&
					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&
					(CommandFileOptionItem != SYS_CIPHER_TX) &&				  /* 暗号化送信 1997/06/18  By T.Yamaguchi */
					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */

					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
					AvailableTxBaudRate = BPS9600_V29;			/** 送信可能ボーレイト９６００ＢＰＳセット */
				}
			}
		}
#if (PRO_F_CODE == ENABLE)
		/* Ｆコード送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/01/09  By T.Yamaguchi */
		if	((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
			 (CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)) {	/* メモリサブアドレス送信 */
			TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
		}
#endif
#if (PRO_CIPHER == ENABLE)
		/* 暗号化送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/10/01  By T.Yamaguchi */
		if	(CommandFileOptionItem == SYS_CIPHER_TX) {	/* 暗号化送信 */
			TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
		}
#endif
	}
#endif /* (PRO_TX_SPEED == V34 ) */
}

/*************************************************************************
	module		:[BCDダイアル・バッファ・データをASCIIダイアル・バッファへ
				  転送する。
	]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[]
	date		:[]
	author		:[山口]
*************************************************************************/
void	FCM_GetDialData(UBYTE *ASCIIDialBuffer, UBYTE *BCDDialBuffer)
{
	CMN_BCD_ToASC_String(ASCIIDialBuffer,BCDDialBuffer);
}

#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
/*************************************************************************
	module		:[PIN BCDダイアル・バッファ・データをASCIIダイアル・バッファへ
				  転送する。
	]
	function	:[]
	commom		:[
				BCDで登録されている番号をアスキーに変換して、格納する
				最終桁の後には、終端コード０ｘ００を入れる
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,SH]
	language	:[MS-C(Ver6.0)]
	keyword		:[]
	date		:[]
	author		:[山口]
*************************************************************************/
void	FCM_GetPinDialData(UBYTE *PINASCIIDialBuffer, UBYTE *PINBCDDialBuffer)
{
	UBYTE counter;

	counter = 0;

	while (((*PINBCDDialBuffer & 0xF0) != 0xF0) && ((*PINBCDDialBuffer & 0x0F) != 0x0F) && (counter < SYS_PIN_MAX)) {
		*PINASCIIDialBuffer++ = CMN_BCD_ToASC((UBYTE)((*PINBCDDialBuffer & 0xF0) >> 4));
		*PINASCIIDialBuffer++ = CMN_BCD_ToASC((UBYTE)(*PINBCDDialBuffer++ & 0x0F));
		counter++;
	}
	if (((*PINBCDDialBuffer & 0xF0) != 0xF0) && ((*PINBCDDialBuffer & 0x0F) == 0x0F)) {	/* 奇数桁登録されている */
		*PINASCIIDialBuffer++ = CMN_BCD_ToASC((UBYTE)((*PINBCDDialBuffer & 0xF0) >> 4));
	}
	*PINASCIIDialBuffer = 0x00;

}
#endif



/*************************************************************************
	module		:[BCDダイアル・データをダイアル・バッファへ転送する]
	function	:[]
	commom		:[
		Offset_2ndDial				: 第２短縮/ワンタッチ用オフセット
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[]
	date		:[]
	author		:[村田]
*************************************************************************/
void	GetDialNumber(void)
{
	SetPartnerAbility();					/** 短縮／ワンタッチ個別データ取得 */

	switch (DialKind) {	/** ダイアル種別判定 */

	/*================*/
	/*= 短縮ダイアル =*/
	/*================*/
	case SYS_SPEED_DIAL	  :			/** 短縮ダイアル */
		if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_EXECUTE) {		/** 発信スケジューラ～実行中 */
			if (SpeedDialPosition < SYS_SPEED_DIAL_MAX) {	/** 第１短縮ダイアル */
				/** 第１短縮ダイアルの番号取得 */
				FCM_GetDialData(SYS_DialingNumber.Buffer, SYB_SpeedDial[SpeedDialPosition].Dial);
#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
				GetPinNumber();
#endif
			}
		}
		/*---------------------*/
		/* 転送先ダイアル 有り */
		/*---------------------*/
#if (PRO_SUB_DIAL == ENABLE)
		else { /** 転送先ﾀﾞｲｱﾙ */
/*
** 転送先ダイヤルを実行するときに、短縮ダイヤルが消去されていた場合に不定なダイヤル番号が送出されてしまう不具合
** 短縮ダイヤルが消去されたとき、SubDialPositionは初期化される為
** ここで短縮ダイヤルが登録されているかどうかをチェックしないと、SubDialPositionの指し示すところのデータを
** 引っ張ってきてしまう（ＲＡＭを破壊する）
** 1999/03/24 by T.Soneoka
*/
#if (0)
**			FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_SpeedDial[SpeedDialPosition].SubDialPosition][0]);
#else
/*
** 短縮ダイアルの転送先ダイヤルを実行するときに、実行中の短縮ダイヤルの転送先ダイアルのみが消去されていた場合に不定なダイヤル番号が送出されてしまう不具合
** 短縮ダイヤルが消去されたとき、SubDialPositionは初期化される為、ここで短縮ダイヤルが登録されているかどうかをチェックしないと、SubDialPositionの指し示すところのデータを
** 引っ張ってきてしまう（ＲＡＭを破壊する）
** 1999/03/30 by H.Hirao
*/
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
			SYS_DialingNumber.Buffer[0] = NULL;
#else

 #if (0)
 **			if (SYB_SpeedDial[SpeedDialPosition].Dial[0] == 0xff) {	/* ANKもKANJIも0xffで初期化されている */
 **				SYS_DialingNumber.Buffer[0] = NULL;
 **			} else {
 **				FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_SpeedDial[SpeedDialPosition].SubDialPosition][0]);
 **			}
 #else
			if (SYB_SpeedDial[SpeedDialPosition].SubDialPosition == 0xff) {
				SYS_DialingNumber.Buffer[0] = NULL;
			} else {
				FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_SpeedDial[SpeedDialPosition].SubDialPosition][0]);
			}
 #endif

#endif

#endif
 #if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
			GetPinNumber();
 #endif
		}
#endif
		break;

	/*========================*/
	/*= ワンタッチ・ダイアル =*/
	/*========================*/
	case SYS_ONETOUCH_DIAL:
		if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_EXECUTE) {
			FCM_GetDialData(SYS_DialingNumber.Buffer, SYB_OnetouchDial[OnetouchDialPosition].Dial);
#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
			GetPinNumber();
#endif
		}
		/*---------------------*/
		/* 転送先ダイアル 有り */
		/*---------------------*/
#if (PRO_SUB_DIAL == ENABLE)
		else { /** 転送先ﾀﾞｲｱﾙ */
/*
** 転送先ダイヤルを実行するときに、ワンタッチダイヤルが消去されていた場合に不定なダイヤル番号が送出されてしまう不具合
** ワンタッチダイヤルが消去されたとき、SubDialPositionは初期化される為
** ここで短縮ダイヤルが登録されているかどうかをチェックしないと、SubDialPositionの指し示すところのデータを
** 引っ張ってきてしまう（ＲＡＭを破壊する）
** 1999/03/24 by T.Soneoka
*/
#if (0)
**			FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_OnetouchDial[OnetouchDialPosition].SubDialPosition][0]);
#else
/*
** 短縮ダイアルの転送先ダイヤルを実行するときに、実行中の短縮ダイヤルの転送先ダイアルのみが消去されていた場合に不定なダイヤル番号が送出されてしまう不具合
** 短縮ダイヤルが消去されたとき、SubDialPositionは初期化される為、ここで短縮ダイヤルが登録されているかどうかをチェックしないと、SubDialPositionの指し示すところのデータを
** 引っ張ってきてしまう（ＲＡＭを破壊する）
** 1999/03/30 by H.Hirao
*/

#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
			SYS_DialingNumber.Buffer[0] = NULL;
#else

 #if (0)
 **			if (SYB_OnetouchDial[OnetouchDialPosition].Dial[0] == 0xff) { /* ANKもKANJIも0xffで初期化されている */
 **				SYS_DialingNumber.Buffer[0] = NULL;
 **			} else {
 **				FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_OnetouchDial[OnetouchDialPosition].SubDialPosition][0]);
 **			}
 #else
			if (SYB_OnetouchDial[OnetouchDialPosition].SubDialPosition == 0xff) {
				SYS_DialingNumber.Buffer[0] = NULL;
			} else {
				FCM_GetDialData(SYS_DialingNumber.Buffer, &SYB_SubDial[SYB_OnetouchDial[OnetouchDialPosition].SubDialPosition][0]);
			}
 #endif

#endif

#endif
 #if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
			GetPinNumber();
 #endif
		}
#endif
		break;

	/*================*/
	/*= 直接ダイアル =*/
	/*================*/
	case SYS_DIRECT_DIAL  :
		FCM_GetDialData(SYS_DialingNumber.Buffer, CommandFileDirectDial );
#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
		GetPinNumber();
#endif
		break;
	default :
		/* ｾｯﾄ･ｴﾗｰ･ｺｰﾄﾞ　*/
		break;
	}
}

/*************************************************************************
	module		:[ﾘﾀﾞｲｱﾙ･ｶｳﾝﾄを減算し、転送電話番号をｾｯﾄする。]
	function	:[]
	commom		:[
		FaxComResult : 交信結果
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[]
	date		:[]
	author		:[村田]
*************************************************************************/
void	DecrementRedialCount(void)
{
	if ((--SYS_CurrentExecutingCommand->RedialCount) > 0) {		/** 発信スケジューラリダイアル回数 */
		/*----------*/
		/*	Redial	*/
		/*----------*/
#if 0	/* defined(FRA) */	/* del by M.HARADA '96/11/15 */	/* 95/01/21 by M.HARADA */
**		switch(AD_Result) {
**			case AD_REMOTE_BUSY:
**			case AD_TIME_OVER:
**				/* 2分後に再ダイアル*/
**				SYS_CurrentExecutingCommand->RedialTime = (UBYTE )3;
**				break;
**			case AD_NO_DIAL_TONE:
**			case AD_NO_CURRENT_LOOP:
**				/* 10分後に再ダイアル*/
**				SYS_CurrentExecutingCommand->RedialTime = (UBYTE )11;
**				/* 再ダイアル回数無制限*/
**				++SYS_CurrentExecutingCommand->RedialCount;
**				break;
**			default:
**				SYS_CurrentExecutingCommand->RedialTime = (UBYTE )(CHK_RedialInterval()+1);
**				break;
**		}
#else
		/*-----------------------------------------------------------------
		** 1998/4以降、リダイヤルに関するJATEの基準が変更となりました。
		** ●３分以内には２回までの再発呼をしてもよい。
		**				↓
		** ●再発呼間隔の制限がなくなった。ただし最大１５回まで
		**   リダイヤル間隔が０分の場合は、即発呼できるように、RedialTime = 0としておきます。
		** 1998/09/30 H.Yoshikawa
		*/
/*		SYS_CurrentExecutingCommand->RedialTime = (UBYTE )(CHK_RedialInterval()+1);	1998/09/30 *//** 発信スケジューラリダイアル間隔セット １～２５６分*/
		if (!CHK_RedialInterval()) {

	#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
			SYS_CurrentExecutingCommand->RedialTime = 0xFF;
	#else
			SYS_CurrentExecutingCommand->RedialTime = 0;
	#endif
		}
		else {
			SYS_CurrentExecutingCommand->RedialTime = (UBYTE )(CHK_RedialInterval()+1);		/** 発信スケジューラリダイアル間隔セット １～２５６分*/
		}
#endif
		if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_EXECUTE) {		/** 発信スケジューラ実行中 */
			SYS_CurrentExecutingCommand->Status = SYS_EXEC_WAITING;			/** 発信スケジューラ予約中 */
		}
		else {
			SYS_CurrentExecutingCommand->Status = SYS_EXEC_FORWARD_WAITING;		/** 発信スケジューラ転送予約中 */
		}
	}
	else {
		/*---------------------*/
		/* 転送先ダイアル 有り */
		/*---------------------*/
#if (PRO_SUB_DIAL == ENABLE)
		if ((SYS_CurrentExecutingCommand->Status == SYS_EXEC_EXECUTE) /* 発信スケジューラ実行中 */
			&&(CommandFileOptionItem != SYS_SCANNER_SECURE_TX)
			&&(CommandFileOptionItem != SYS_MEMORY_SECURE_TX)
			&&(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST)
			&&(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {

			/* ﾒｲﾝのﾀﾞｲｱﾙを全て終了し、転送先ﾀﾞｲｱﾙ番号がｾｯﾄされていれば、転送用 */
			/* ｺﾏﾝﾄﾞ、ﾘﾀﾞｲｱﾙ回数、ﾘﾀﾞｲｱﾙ時間のみをｾｯﾄする。 */
			switch (DialKind) {		/** 発信スケジューラダイアル種別 */
				case SYS_SPEED_DIAL:
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
					/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
					SYS_CurrentExecutingCommand->Result = FaxComResult;
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
#else
					if (SYB_SpeedDial[SpeedDialPosition].SubDialPosition < SYS_SUB_DIAL_MAX) {
						SYS_CurrentExecutingCommand->RedialCount = CHK_RedialCount() + (UBYTE)0x01;
						SYS_CurrentExecutingCommand->RedialTime	 = (UBYTE)(CHK_RedialInterval() + 1);
						SYS_CurrentExecutingCommand->Status		 = SYS_EXEC_FORWARD_WAITING;
					}
					else {
						/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
						SYS_CurrentExecutingCommand->Result = FaxComResult;
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
					}
#endif
					break;
				case SYS_ONETOUCH_DIAL:
#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
						/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
						SYS_CurrentExecutingCommand->Result = FaxComResult;
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
#else
					if (SYB_OnetouchDial[OnetouchDialPosition].SubDialPosition < SYS_SUB_DIAL_MAX) {
						SYS_CurrentExecutingCommand->RedialCount = CHK_RedialCount() + (UBYTE)0x01;
						SYS_CurrentExecutingCommand->RedialTime	 = (UBYTE)(CHK_RedialInterval() + 1);
						SYS_CurrentExecutingCommand->Status		 = SYS_EXEC_FORWARD_WAITING;
					}
					else {
						/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
						SYS_CurrentExecutingCommand->Result = FaxComResult;
						SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
					}
#endif
					break;
				default:
					/* 通信中にﾜﾝﾀｯﾁ/ｽﾋﾟｰﾄﾞ･ﾀﾞｲｱﾙが消されたとき。	*/
					/* ﾀﾞｲﾚｸﾄﾀﾞｲｱﾙでﾘﾀﾞｲｱﾙ回数分ﾀﾞｲｱﾙした時。		*/
					SYS_CurrentExecutingCommand->Result = FaxComResult;
					SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
					break;
			}

			/* 転送ダイヤル時の処理が抜けていました。 By O.Kimoto 1999/01/12 */
			/*-----------------------------------------------------------------
			** 1998/4以降、リダイヤルに関するJATEの基準が変更となりました。
			** ●３分以内には２回までの再発呼をしてもよい。
			**				↓
			** ●再発呼間隔の制限がなくなった。ただし最大１５回まで
			**   リダイヤル間隔が０分の場合は、即発呼できるように、RedialTime = 0としておきます。
			** 1998/09/30 H.Yoshikawa
			*/
			if ((DialKind == SYS_SPEED_DIAL) || (DialKind == SYS_ONETOUCH_DIAL)) {
				if (!CHK_RedialInterval()) {

	#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
					SYS_CurrentExecutingCommand->RedialTime = 0xFF;
	#else
					SYS_CurrentExecutingCommand->RedialTime = 0;
	#endif
				}
				else {
					SYS_CurrentExecutingCommand->RedialTime = (UBYTE )(CHK_RedialInterval()+1);		/** 発信スケジューラリダイアル間隔セット １～２５６分*/
				}
			}

		}
		else {
			/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
			SYS_CurrentExecutingCommand->Result = FaxComResult;
			SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
		}
#else
/* 転送先ダイアル無し */
		/* ﾁｪｯｸ･ﾒｯｾｰｼﾞのﾌﾟﾘﾝﾄ･ｾｯﾄだけを行ってｼﾞｬｰﾅﾙには載せません。*/
		SYS_CurrentExecutingCommand->Result = FaxComResult;
		SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERROR;
 #if 0	/* defined(FRA) */ /* del by M.HARADA '96/11/15 */			/* '95/04/18	by M.HARADA	*/
		if (CHK_UNI_HumanAnswerClear()) {
			switch (DialKind) {
			case SYS_SPEED_DIAL:
				ClearSpeedRecord(SpeedDialPosition);
				break;
			case SYS_ONETOUCH_DIAL:
				ClearOnetouchRecord(OnetouchDialPosition);
				break;
			default:
				break;
			}
		}
 #endif
#endif
	}
}

/*************************************************************************
	module		:[通信予約データ取得]
	function	:[
		1.発信スケジューラーが通信予約ファイルから展開されたか一括送信ファイル
		　から展開されたかを判断し、データをバッファにセット
	]
	return		:[]
	common		:[
		CommandFileOptionItem			: 通信種別
		CommandFileConfirmationReport	: 通信証
		CommandFileTitleMessage			: タイトルメッセージ
		CommandFilePage					: 送信ページ
		CommandFileDepartmentCode		: 部門コード
		*CommandP						: 通信予約ファイルポインター
		*BatchP							: 一括送信ファイルポインター
		*ContPollingP					: 連続ポーリング受信ファイルポインター
		*SYS_CurrentExecutingCommand	: 発信スケジューラーポインター
		*CommandFilePinNumber			: ダイヤル時のPIN番号ポインター
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/03/04]
	author		:[村田]
*************************************************************************/
void	GetCommandFileData(void)
{
	SYS_CurrentExecutingCommand = &SYB_ExecQueue[FcomMsg->SubMessage1];		/** 発信スケジューラー ポインター Set */

	GetDialOffesetNumber();								/* ダイヤル種別ごとに格納されている場所を変数にセットする */

	if ( SYS_CurrentExecutingCommand->Kind == SYS_COMMAND_TRX ){			/** 通信予約による送受信 */
		/*----------*/
		/* 通信予約 */
		/*----------*/
		CommandP					  = &SYB_CommandFile[SYS_CurrentExecutingCommand->Number.Command];	/** 通信予約番号 */
		CommandFileStatus			  = CommandP->Status;							/** 使用状況	 */
		CommandFileOptionItem		  = CommandP->Option.Item;						/** 通信種別	 */
#if(PRO_MEM_RX_REJECT == ENABLE)			/* メモリ受信拒絶機能 '94,10,14 By N.S. */
		/*------------------------------*/
		/* 不達通知送信には通信証はない */
		/*------------------------------*/	/* 1995/02/10 */
		if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) {
			CommandFileConfirmationReport = 0x00;				/** 通信証		 */
		}
		else {	/* 不達通知でない */

			/* if( CMN_CheckAutoCalledEnable( 1 )){ */ /* Changed by H.Kubo 1998/05/26 */
			if( CMN_CheckAutoCalledEnable() ){ /* Changed by H.Kubo 1998/05/26 */
				CommandFileConfirmationReport = CommandP->Option.ConfirmationReport;	/** 通信証		 */
			}
			else{
				CommandFileConfirmationReport = (UBYTE)(CommandP->Option.ConfirmationReport & ~SYS_RCR_SELECT);	/** 通信証		 */
			}
		}
#else
		CommandFileConfirmationReport = CommandP->Option.ConfirmationReport;		/** 通信証		 */
#endif
		CommandFileTitleMessage		  = CommandP->TitleMessage;						/** カバーページ */
		CommandFilePage				  = CommandP->Page;								/** 送信ページ */
#if (PRO_DEPARTMENT==ENABLE)
		CommandFileDepartmentCode	  = CommandP->DepartmentCode;					/** 部門管理コード */
#endif
		if ( DialKind == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			CommandFileDirectDial
			= CommandP->DialNumber.Direct[DirectNumberPosition];			/** ダイレクトダイアルセーブ */
		}
		CommandFileAbility			  = CommandP->Ability;							/** 通信予約の付加情報 *//* 1994/11/01 */
#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
		CommandFilePinAccessMode = CommandP->PIN_AccessMode;						/** ＰＩＮアクセスモード */
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		switch (PIN_ACCESS_MODE1) {
 #else
		switch (CommandFilePinAccessMode) {
 #endif
			case	PIN_ACCESS_OFF:
				break;
			case	PIN_ACCESS_MODE1:
				if ( DialKind == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
					CommandFilePinNumber
					= CommandP->DialNumber.PIN_Number[DirectNumberPosition];	/** ダイレクトダイアルPIN番号セーブ */
				}	/** 直接ダイヤル以外はGetDialNumber()で取ってくる */
				break;
			case	PIN_ACCESS_MODE2:
				CommandFilePinNumber
				= CommandP->PIN_Number;
				break;
			default:
				break;
		}
#endif
#if (PRO_F_CODE == ENABLE)
		if ((CommandFileOptionItem == SYS_SELECT_POLLING_RX)
		  ||(CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX)
		  ||(CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)) {
			CommandFileFcodePosition = CommandP->Option.OptionNumber.FcodeDataPosition[0];
			SetOwnF_CODE_ID();
		}
#endif

	}
#if (PRO_BATCH_TX == ENABLE)
	else if ( SYS_CurrentExecutingCommand->Kind == SYS_BATCH_TX ){		/** 一括送信 */
		/*----------*/
		/* 一括送信 */
		/*----------*/
		BatchP						  = &SYB_BatchTxFile[SYS_CurrentExecutingCommand->Number.Batch];	/** 通信予約番号 */
		CommandFileStatus			  = BatchP->Status;			/** 使用状況 */
		CommandFileOptionItem		  = SYS_BATCH_MEMORY_TX;	/** 一括送信 */												/** 通信種別	 */
	#if (PRO_MAKER == MML)
		if (CHK_BatchTxTCR_ON() != 0x00) {	/** メモリＳＷがＯＮである *//* 1994/11/17 */
			CommandFileConfirmationReport = 0x01;				/** 通信証		 */
		}
		else {
			CommandFileConfirmationReport = 0x00;				/** 通信証		 */
		}
	#endif
		CommandFileTitleMessage		  = 0xff;					/** カバーページ */
		CommandFilePage				  = BatchP->Page;			/** 送信ページ */
	#if (PRO_DEPARTMENT==ENABLE)
		CommandFileDepartmentCode	  = 0xffff;					/** 部門管理コード */
/*		CommandFileDepartmentCode	  = 0x00;					/@@ 部門管理コード ↑に変更	96/08/13 By T.Yamaguchi */
	#endif
		CommandFileAbility			  = 0x00;							/** 通信予約の付加情報 *//* 1994/11/01 */
	#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
		/* 1line add Oct.14.1996  By T.Yamaguchi */
		CommandFilePinAccessMode = CHK_PIN_AccessMode();		/** ＰＩＮアクセスモード */
	#endif
		if ( DialKind == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			CommandFileDirectDial
			= BatchP->DialNumber[DirectNumberPosition].FaxNumber.Direct;		/** ダイレクトダイアルセーブ */
	#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
	 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
			if (PIN_ACCESS_MODE1) {
	 #else
			if (CHK_PIN_AccessMode()) {		/* 一括送信の場合はモード１でも２でも、同じ所から取ってくる */
	 #endif
				CommandFilePinNumber
				= BatchP->DialNumber[DirectNumberPosition].PIN_Number;			/** ダイレクトダイアルPIN番号セーブ */
			}
		}
		if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE2) {		/* 一括送信の場合はモード２でも強制的にEXECQUEUから取ってくる */
			if ( DialKind == SYS_SPEED_DIAL) {		/** 短縮ダイアル */
				CommandFilePinNumber
				= SYB_SpeedDial[SpeedDialPosition].PIN_Number;
			}
			if ( DialKind == SYS_ONETOUCH_DIAL) {		/** ワンタッチダイアル */
				CommandFilePinNumber
				= SYB_OnetouchDial[OnetouchDialPosition].PIN_Number;
			}
	#endif
		}
	}
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	else if ( SYS_CurrentExecutingCommand->Kind == SYS_CONTINUOUS_POLLING ){		/** 連続ポーリング */

		/** 連続ポーリング受信 */

		ContPollingP				  = &SYB_ContinuousPolling;				/** 連続ポーリング受信ファイル */
		CommandFileStatus			  = ContPollingP->Status;				/** 使用状況 */
		CommandFileOptionItem		  = SYS_CONTINUOUS_POLLING_RX;			/** 連続ポーリング	 */	/** 通信種別	 */
		CommandFileConfirmationReport = 0x00;								/** 通信証なし		 */
		CommandFileTitleMessage		  = 0xff;								/** カバーページなし */
		CommandFilePage				  = 0x00;								/** 送信ページなし	 */
	#if (PRO_DEPARTMENT==ENABLE)
		CommandFileDepartmentCode	  = ContPollingP->DepartmentCode;		/** 部門管理コード */
	#endif
		CommandFileAbility			  = 0x00;								/** 通信予約の付加情報 *//* 1994/11/01 */
		if ( DialKind == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			CommandFileDirectDial
			= ContPollingP->DialNumber.Direct[DirectNumberPosition];		/** ダイレクトダイアルセーブ */
		}
	#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
		CommandFilePinAccessMode	  = ContPollingP->PIN_AccessMode;		/** ＰＩＮアクセスモード */
	 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		switch (PIN_ACCESS_MODE1) {
	 #else
		switch (CommandFilePinAccessMode) {
	 #endif
		case	PIN_ACCESS_OFF:
			break;
		case	PIN_ACCESS_MODE1:
			if ( DialKind == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
				CommandFilePinNumber
				= ContPollingP->DialNumber.PIN_Number[DirectNumberPosition];	/** ダイレクトダイアルPIN番号セーブ */
			}	/** 直接ダイヤル以外はGetDialNumber()で取ってくる */
			break;
		case	PIN_ACCESS_MODE2:
			CommandFilePinNumber	= ContPollingP->PIN_AccessNumber;			/** PIN番号セーブ */
			break;
		default:
			break;
		}
	#endif
	}
#endif
	else {
		/** ここに来るのはバグ ExecQueueのKindに変な値が入っている */
	}
}



/*************************************************************************
	module		:[ダイヤルする番号が格納されている場所を確定する]
	function	:[
		1.キューの格納されているダイヤル種別、格納されている場所を通信用参照変数にコピーする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[ＳＨＣ]
	keyword		:[FCM]
	date		:[1996/11/21]
	author		:[山口　哲治]
*************************************************************************/
void GetDialOffesetNumber(void)
{
	DialKind = SYS_CurrentExecutingCommand->ExecDial.Item;		/* 実行ｷｭｰに入っているダイヤル種別 */

	switch ( DialKind) {
	case  SYS_DIRECT_DIAL:		/** 直接ダイアル */
		DirectNumberPosition = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Command;
		break;
	case  SYS_SPEED_DIAL:	/** 短縮ダイアル */
		SpeedDialPosition = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed;
		break;
	case  SYS_ONETOUCH_DIAL:	/** ワンタッチダイアル */
		OnetouchDialPosition = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch;
		break;
	default:
		break;	/* ここに来るのはバグ */
	}
}

#if (PRO_PIN_ACCESS == ENABLE)	/* '95.12.22 By t.yamaguchi */
/*************************************************************************
	module		:[ＰＩＮ番号の獲得]
	function	:[
		1.ＰＩＮ番号をSYS_PinBufferにセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[ＳＨＣ]
	keyword		:[FCM]
	date		:[1996/11/21]
	author		:[山口　哲治]
*************************************************************************/
void	GetPinNumber(void)
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
{
		*SYS_PinBuffer = 0x00;	/* NULL */
		switch (DialKind) {
		case SYS_DIRECT_DIAL  :
			FCM_GetPinDialData(SYS_Multi_PinBuffer, CommandFilePinNumber );
			break;
		case SYS_ONETOUCH_DIAL:
			FCM_GetPinDialData(SYS_Multi_PinBuffer, SYB_OnetouchDial[OnetouchDialPosition].PIN_Number);
			break;
		case SYS_SPEED_DIAL	  :			/** 短縮ダイアル */
			FCM_GetPinDialData(SYS_Multi_PinBuffer, SYB_SpeedDial[SpeedDialPosition].PIN_Number);
			break;
		}
}
#else
{
	switch (CommandFilePinAccessMode) {
	case	PIN_ACCESS_OFF:
		*SYS_PinBuffer = 0x00;	/* NULL */
		break;
	case	PIN_ACCESS_MODE1:
		switch (DialKind) {
		case SYS_DIRECT_DIAL  :
			FCM_GetPinDialData(SYS_PinBuffer, CommandFilePinNumber );
			break;
		case SYS_ONETOUCH_DIAL:
			FCM_GetPinDialData(SYS_PinBuffer, SYB_OnetouchDial[OnetouchDialPosition].PIN_Number);
			break;
		case SYS_SPEED_DIAL	  :			/** 短縮ダイアル */
			FCM_GetPinDialData(SYS_PinBuffer, SYB_SpeedDial[SpeedDialPosition].PIN_Number);
			break;
		}
		break;
	case	PIN_ACCESS_MODE2:
		FCM_GetPinDialData(SYS_PinBuffer, CommandFilePinNumber);
		break;
	}
}
#endif
#endif

#if (PRO_TX_SPEED == V34) /* Ported from clover\src\fcm_getd.c by H.Kubo 1997/08/05 */
/*************************************************************************
	module		:[コマンドファイアルが送信か否か]
	function	:[
		1.
	]
	return		:[
				１：送信
				０：送信でない
	]
	common		:[
			CommandFileOptionItem
	]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/11/25]
	author		:[村田]
*************************************************************************/
UBYTE CheckCommnadFileTxItem(void)
{
	if (CommandFileOptionItem == SYS_SCANNER_TX ||
		CommandFileOptionItem == SYS_MEMORY_TX ||
		CommandFileOptionItem == SYS_DELAYED_SCANNER_TX ||
		CommandFileOptionItem == SYS_DELAYED_MEMORY_TX ||
		CommandFileOptionItem == SYS_SCANNER_SECURE_TX ||
		CommandFileOptionItem == SYS_MEMORY_SECURE_TX ||
		CommandFileOptionItem == SYS_SCANNER_RELAY_BROADCAST ||
		CommandFileOptionItem == SYS_MEMORY_RELAY_BROADCAST ||
		CommandFileOptionItem == SYS_DELAYED_BROADCAST ||
		CommandFileOptionItem == SYS_RELAYED_TX ||
		CommandFileOptionItem == SYS_FX_MEMORY_RELAY_TX ||			/* FX仕様 */
		CommandFileOptionItem == SYS_FX_SCANNER_RELAY_TX ||			/* FX仕様 */
		CommandFileOptionItem == SYS_FX_MEMORY_SECURE_TX ||			/* FX仕様 */
		CommandFileOptionItem == SYS_FX_SCANNER_SECURE_TX ||		/* FX仕様 */
		CommandFileOptionItem == SYS_RELAYED_TX_REPORT ||		/* MIMIJI 1995/02/15 */
		CommandFileOptionItem == SYS_BATCH_MEMORY_TX ||
		CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX	||	/*	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
		CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX	||	/*	Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */

#if (PRO_CIPHER == ENABLE)
		/* CIPHER スクランブル対応 By O.Kimoto 1998/04/09 */
		CommandFileOptionItem == SYS_CIPHER_TX	||	/*	暗号化送信 By Y.Suzuki 1997/06/03	*/
#endif
		CommandFileOptionItem == SYS_SUB_ADDRESS_RELAYED_TX) {	/*	中々継ﾎﾞｯｸｽ送信（中継配信）	  */

		return(1);
	}
	else {
		return(0);
	}
}
#endif /* (PRO_TX_SPEED == V34) */


#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
/*
 * クイックメモリ送信か否かのチェック
*/
UBYTE FCM_CheckQucikMemoryTx(void)
{
	UWORD command_no;

	if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
		if (TxMemoryFileItem == SYS_MEM_TX_FILE) {
			command_no = (UWORD)SYS_CurrentExecutingCommand->Number.Command;
			if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
	 		&& (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {
				if (SYS_DocumentStoreItem == SYS_MEM_TX_FILE) {
					if (SYS_DocumentStoreNo == command_no) {
						return(1);
					}
				}
			}
		}
	}
	return(0);

	/* こっちの方がすっきりしてる */
	if (SYS_FaxComTxType == SYS_MEMORY_TRANSMIT) {
		command_no = (UWORD)SYS_CurrentExecutingCommand->Number.Command;
		if (CommandFilePage == 0) {
			return(1);
		}
		else {
			return(0);
		}
	}

}



#endif
