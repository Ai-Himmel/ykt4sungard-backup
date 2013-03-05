/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_SPD.C												 */
/*	モジュール	 :															 */
/*				 : FaxTxSpeedHandshake()									 */
/*				 : FaxRxSpeedHandshake()									 */
/*				 : FaxSNSS_SemiCompatibleCheck()							 */
/*				 : MuratecRxSpeedHandshakeEnable()							 */
/*				 : FaxTransmitCNG											 */
/*				 : FaxTransmitCED											 */
/*				 : FaxTransmit1300Hz()			   -- FX仕様(専用線対応)	 */
/*				 : FaxTransmit1080Hz()										 */
/*				 : ArrivalSignalToneTransmit()	  -- 新短縮のみ --			 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＦＡＸ通信短縮ハンドシェークモジュール					 */
/*				 : 単一トーン出												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\unisw_b.h"
#include "\src\atlanta\define\syscomf.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#if (PRO_MEM_RX_REJECT == ENABLE)
	#include "\src\atlanta\ext_v\rom_tbl.h"
#endif

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#if (1) /* (PRO_TX_SPEED == V34) */ /* Modified by H.Kubo 1997/08/06 */
#include "\src\atlanta\define\man_pro.h"
#endif /* (1) */ /* (PRO_TX_SPEED == V34) */


#include "\src\atlanta\ext_v\atd_tbl.h"	/* 96/06/06 */

#if (PRO_PRINTER_RX == ENABLE)
	#include "\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1998/12/25 */
#endif
/*************************************************************************
	module		:[短縮ハンドシェーク（「ＳＮＳＳ」「ＳＴＳＩ」「ＳＤＣＳ」）
				　の送信を行う。
	]
	function	:[]
	commom		:[
		SDCS_TransmitFlag		: 短縮ハンドシェーク送信フラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	FaxTxSpeedHandshake(void)
{

	/*---------------------------------------------*/
	/** 極反を検出し高速信号を送出するまでウエイト */
	/*---------------------------------------------*/
	wai_tsk(10);		/* 100ms Wait 受信側でリレー制御で100msウエイトしているため */

	/*************************/
	/** (SNSS)(STSI)SDCS Tx **/
	/*************************/
#if 0
//		if(( SYS_TxTotalPage == 0 ) || (!CHK_UNI_SUB_Frame_Off())) {	/* UNI_SW_B6-4 */
//			MakeSUB_FIF();
//			MakeTX_PWD_FIF();
//		}
#endif
	MakeDCS_FIF();				/** ＳＤＣＳフレーム作成 */
	MakeNSS_FIF();				/* 16.Jun'94 Y.Suzuki */
	SDCS_TransmitFlag = 1;
	MDM_TransmitCommand();
	SDCS_TransmitFlag = 0;
}


/*************************************************************************
	module		:[短縮ハンドシェーク信号の受信を行う。]
	function	:[]
	commom		:[
		FinalRxMode				: 確定受信モード
		FaxComRxPerformingFlag	: 通信受信フラグ
		RxSpeedHandshakeFlag	: 短縮ハンドシェークフラグ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	FaxRxSpeedHandshake(void)
{
	UBYTE	ret;			/* 関数戻り値 */

	ret = MDM_RxSpeedHandshake();				/* 短縮ハンドシェーク受信 */

	switch( ret ) {
		case FSK_RECEIVE	:
						 FaxComRxPerformingFlag = 1;
						 FinalRxMode = G3MODE;
						 if ( CheckHDLC_Command() == DCS_F ){	/** DCS Rx Check */
							if ( FaxSNSS_SemiCompatibleCheck() == 1 ){	/** SDCS Rx Check */
								RxSpeedHandshakeFlag = 1;
							}
							else{
								RxSpeedHandshakeFlag = 0;
							}
						 }
						 else{
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
							EOM_received = 1;			/* 96/05/29 */
#endif
							RxSpeedHandshakeFlag = 0;
						 }
						 break;

		case FSK_ERROR		:
						 RxSpeedHandshakeFlag = 0;
						 break;
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
		case CNG_RECEIVE	:					/* 2line add 96/05/28 By T.Yamaguchi */
						 RxSpeedHandshakeFlag = 0;
#endif
		default				:
						 RxSpeedHandshakeFlag = 0;
						 break;
	}
}


/*************************************************************************
	module		:[相手機が自社機かどうか判断する。]
	function	:[]
	commom		:[
		FCF_Point				: 最終フレームポイント
		MakerCodeRxFlag			: 「村田（／ＸＥＲＯＸ）メーカコード受信」フラグ
		MDM_ModemBuffer			: モデムバッファ
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
UBYTE	FaxSNSS_SemiCompatibleCheck(void)
{
	UWORD	   point;			/* NSS Frame Point */
	UWORD	   counter;			/* 最終 Frame Counter */

	point = 0;

	for( counter = 0; counter <= FCF_Point; counter++){
		if( ( MDM_ModemBuffer[point][2] & 0xfe ) == NSS_F ){
		break;
		}
		point++;
	}

	if( ( MDM_ModemBuffer[point][5] & 0x45 ) == 0x45 ){	/** FIF3rd 通工会指定MMLｺｰﾄﾞ(0x45) Check */
		MakerCodeRxFlag = 1;
		return(1);									/** 相手機が自社機 */
	}
	else{
		return(0);									/** 相手機が他社機 */
	}
}


/*************************************************************************
	module		:[短縮ハンドシェーク受信を行うかどうかの判別]
	function	:[
		１．短縮ハンドシェークを行うかどうか判別する
		２．受信ボーレイトを決定する
	]
	return		:[
		0:	短縮ハンドシェークの受信を行わない
		1:	短縮ハンドシェークの受信を行う
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/04/18]
	author		:[村田]
*************************************************************************/
UBYTE	MuratecRxSpeedHandshakeEnable(void)
{
#if (PRO_MAKER == MML)
 #if (PRO_MEM_RX_REJECT == ENABLE)	/* 1994/12/20 */
/*--------------*/
/* もみじ沖仕様 */
/*--------------*/
	if (OKI_Model) {
		return(0);
	}
 #endif
/*----------*/
/* 村田仕様 */
/*----------*/
	if ((AvailableRxBaudRate == BPS9600_V29)  ||
		(AvailableRxBaudRate == BPS14400_V17) ||
		(AvailableRxBaudRate == BPS14400_V33)) {
 #if (PRO_PRINTER_RX == ENABLE)
		/*
		** 強制プリンタ受信の場合、短縮ハンドシェーク受信を行わない
		** added by H.Hirao
		*/
		if (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX) {
			return (0);
		}
 #endif
#if (PRO_MODEM == R288F) /* by H.Kubo 1998/04/08 */
	/* R288F は現状では受信時の短縮ハンドシェイクがうまく動きません。
	** そのため、受信時にもメモリスイッチを見ます。*/
		if (!SpeedHandshakeRomCheck()) {
			return (0);
		}
#endif
		AttemptRxBaudRate = AvailableRxBaudRate;	/* ボーレイトセット */
		return(1);
	}
	else {
		return(0);
	}
#endif
#if (PRO_MAKER == FX)
/*----------*/
/* ＦＸ仕様 */
/*----------*/
		return(0);
#endif
}

/*************************************************************************
	module		:[ＣＮＧ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/07/07]
	author		:[村田]
*************************************************************************/
void	FaxTransmitCNG(void)
{
	if (!SYS_V34ProcedureExecuting()) { /* Modified by H.Kubo 1997/08/06 */
		FaxTransmit1080Hz();	/** １０８０Ｈｚ  ０．５秒間 */
	}
}


/*************************************************************************
	module		:[ＣＥＤ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/06/09]
	author		:[村田]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998 */
void	FaxTransmitCEDFlsRom(void)
#else
void	FaxTransmitCED(void)
#endif
{
	UBYTE	tone_type;
	UWORD	time;

	tone_type = TONE_2100HZ;		/* 2100hz */
	time	  = 3000;				/* 3000ms */

	MDM_ToneTx(tone_type,time);

}


/*************************************************************************
	module		:[１０８０Ｈｚ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/06/09]
	author		:[村田]
*************************************************************************/
void	FaxTransmit1080Hz(void)
{
	UBYTE	tone_type;
	UWORD	time;

	/*-------------------------------------*/
	/* 1080Hzの単一トーンを500ms送出します */
	/*-------------------------------------*/
	tone_type = TONE_1080HZ;		/* 1080hz */
	time	  = 500;				/* 500ms */

	MDM_ToneTx(tone_type,time);
}


/*************************************************************************
	module		:[１３００Ｈｚ送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[2003/5/13]
	author		:[鈴木郁二]
*************************************************************************/
void	FaxTransmit1300Hz(void)
{
	UBYTE	tone_type;
	UWORD	time;

	/*--------------------------------------*/
	/* 1300Hzの単一トーンを1500ms送出します */
	/*--------------------------------------*/
	tone_type = TONE_1300HZ;		/* 1300hz */
	time	  = 3000;				/* 3000ms (受信側検出時間2.2秒) */

	MDM_ToneTx(tone_type,time);
}


#if (PRO_SPEED_EX == ENABLE)
/*************************************************************************
	module		:[着信後トーン送出]
	function	:[
		1.AutoCalled() から、呼び出される。
		2.新短縮ハンドシェーク用着信トーンを送出
		3.周波数はメモリースイッチまたは、保守モードで設定
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/10/20]
	author		:[山口]
				95.10.20	メモリースイッチが決まっていないので後で設定する。
							周波数選択は、保守モードで設定できる様にする
*************************************************************************/
void	ArrivalSignalToneTransmit(void)
{
	UBYTE	tone_type;
	UWORD	time;

	/*--------------------------------------------------*/
	/* 短縮（海外用）着信後の単一トーンを１秒送出します */
	/*--------------------------------------------------*/
	if (CHK_UNI_ArrivalSignalToneType() != 0) {

		switch (CHK_UNI_ArrivalSignalToneType()) {
			case SPD_TONE_697HZ:
				tone_type = ROW_1;
				break;
			case SPD_TONE_770HZ:
				tone_type = ROW_2;
				break;
			case SPD_TONE_852HZ:
				tone_type = ROW_3;
				break;
			default:		/* ここに来たらバグ */
				tone_type = ROW_1;
				break;
		}
		time = CHK_UNI_ArrivalSignalToneTxTime();	 /* 着信トーン送出時間獲得 */

		MDM_DTMF_Tx(tone_type,time);
	}
	else {
		tone_type = TONE_2100HZ;		/* 初期値2100hz */

		time = CHK_UNI_ArrivalSignalToneTxTime();	/* 着信トーン送出時間獲得 */

		MDM_ToneTx(tone_type,time);
	}
}
#endif

#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
/*************************************************************************
	module		:[モード変更時の短縮ハンドシェークチェック]
	function	:[
		1.モード変更時の短縮手順を決める
			相手機がモード変更時の短縮手順を持っている
			交信速度が１４．４Ｋｏｒ９．６Ｋ
	]
	return		:[0:通常手順
				  1:CNG送出
				  2:SDCS送出
				 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/06/01]
	author		:[山口　哲治]
*************************************************************************/
UBYTE	ModeChangeMethodCheck(void)
{
	if (PartnerSpeedModeChangeAbility == YES) {
		if ( ((TxBaudRate == BPS14400_V17)
			||(TxBaudRate == BPS14400_V33)
			||(TxBaudRate == BPS9600_V29)
			||(TxBaudRate == BPS9600_V17))
		  && (!CHK_UNI_SpeedModeChange())) {
			return(HIGH_SPEED_MODE);
		}
		else {
			if (!CHK_UNI_SDCSModeChange()) {
				return(CNG_MODE);
			}
			else {
				return(USUALLY_MODE);
			}
		}
	}
	else {
		return(USUALLY_MODE);
	}
}
#endif

/*************************************************************************
	module		:[短縮ハンドシェーク（前手順）有効／無効チェック]
	function	:[
		1.短縮手順を搭載するかどうか、未定のためＲＯＭの値で
		　有効／無効をきめる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/06/06]
	author		:[山口　哲治]
*************************************************************************/
UBYTE	SpeedHandshakeRomCheck(void)
{
	UBYTE rom_data;
	rom_data = (UBYTE)SpeedHandshakeValiableData;

#if defined(JPN)
	if (CHK_SpeedHandshake())  {
#else
	if ((CHK_SpeedHandshake()) && (rom_data &= 0x01)) {
#endif
		return (TRUE);
	}
	return (FALSE);
}

#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
/*************************************************************************
	module		:[短縮ハンドシェーク(モード変更）有効／無効チェック]
	function	:[
		1.短縮手順を搭載するかどうか、未定のためＲＯＭの値で
		　有効／無効をきめる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/06/06]
	author		:[山口　哲治]
*************************************************************************/
UBYTE	SpeedModeChangeRomCheck(void)
{
	UBYTE rom_data;
	rom_data = (UBYTE)SpeedHandshakeValiableData;

	if ((CHK_UNI_HiSpeedModeChange()) && (rom_data &= 0x02)) {
		return (TRUE);
	}
	return (FALSE);
}
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/05 */
/*************************************************************************
	module		:[ハンドシェーク属性の設定]
	function	:[
		1.自動ダイアル後にコールされる
	]
	return		:[]
	common		:[
					V8ProcedureRequestFlag
					AvailableTxBaudRate
					TxSpeedHandshakeFlag
					CommandFileOptionItem
	]
	condition	:[]
	comment		:[]
	machine		:[V53/SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/09/20]
	author		:[村田]
*************************************************************************/
void FCM_SetHandshakeAttribute(void)
{
	if (FCM_CheckV8ProcedurePhaseA()) {	/** 送信フェーズＡでＶ８行う */

		V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
	}
	else {
		V8ProcedureRequestFlag = 0;		/** Ｖ８手順移行要求クリア */
		/*------------------------------*/
		/* 短縮ハンドシェーク送信の確定 */
		/*------------------------------*/
		if (SpeedHandshakeRomCheck() == TRUE){
			if ((FCM_PtnrChkSpeedHandshake144())
			&& ((AvailableTxBaudRate == BPS14400_V17) || (AvailableTxBaudRate == BPS14400_V33))){


				if (CHK_UNI_OptionSpeedHandshake()) {	/* 応用通信の時にも短縮ﾊﾝﾄﾞｼｪｰｸを行なう時 */
					TxSpeedHandshakeFlag =1;
				}
				else {
					if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&		  /* スキャナ親展送信	  */
						(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&		  /* メモリ親展送信		  */
						(CommandFileOptionItem != SYS_CIPHER_TX) &&				  /* 暗号化送信 1997/06/18  By T.Yamaguchi */
						(CommandFileOptionItem != SYS_SCANNER_SUB_ADDRESS_TX) &&	/* スキャナサブアドレス送信 */ /* Added by H.Kubo 1998/04/20 */
						(CommandFileOptionItem != SYS_MEMORY_SUB_ADDRESS_TX) && 	/* メモリサブアドレス送信 */ /* Added by H.Kubo 1998/04/20 */
						(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&	/* スキャナ中継指示送信 */
						(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* メモリ中継指示送信は短縮しない  */
	
						TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
					}
					else {
						V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
					}
				}

#if 0 /* Changed by H.Kubo 1998/04/20 */
@@				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
@@					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */

@@					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
@@				}
@@				else {
@@					V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
@@				}
#endif
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
						(CommandFileOptionItem != SYS_SCANNER_SUB_ADDRESS_TX) &&	/* スキャナサブアドレス送信 */ /* Added by H.Kubo 1998/04/20 */
						(CommandFileOptionItem != SYS_MEMORY_SUB_ADDRESS_TX) && 	/* メモリサブアドレス送信 */ /* Added by H.Kubo 1998/04/20 */
						(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
						(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */
							TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
							AvailableTxBaudRate = BPS9600_V29;			/** 送信可能ボーレイト９６００ＢＰＳセット */
					}
					else {
						V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
					}
				}

#if 0 /* Changed by H.Kubo 1998/04/20 */
@@				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
@@					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */
@@
@@					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
@@					AvailableTxBaudRate = BPS9600_V29;			/** 送信可能ボーレイト９６００ＢＰＳセット */
@@				}
@@				else {
@@					V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
@@				}
#endif
			}
#if (PRO_F_CODE == ENABLE)
			/* Ｆコード送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/01/09  By T.Yamaguchi */
			if	((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
				 (CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)) {	/* メモリサブアドレス送信 */
				TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
				V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */ /* added by H.Kubo 1998/04/20 */
			}
#endif
#if (PRO_CIPHER == ENABLE)
			/* 暗号化送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/10/01  By T.Yamaguchi */
			if	(CommandFileOptionItem == SYS_CIPHER_TX) {	/* 暗号化送信 */
				TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
				V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */ /* added by H.Kubo 1998/04/20 */
			}
#endif
		}
	}
}

#if 0 /* Obsoleted by the above code. Changed by H.Kubo 1998/04/20 */
@@{
@@	if (FCM_CheckV8ProcedurePhaseA()) {	/** 送信フェーズＡでＶ８行う */
@@
@@		V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
@@	}
@@	else {
@@		V8ProcedureRequestFlag = 0;		/** Ｖ８手順移行要求クリア */
@@		/*------------------------------*/
@@		/* 短縮ハンドシェーク送信の確定 */
@@		/*------------------------------*/
@@#if 0 /* Changed by H.Kubo 1998/01/09 */
@@@@		if ( CHK_SpeedHandshake() != 0 ) {		/** 短縮ハンドシェイク */
@@@@			if ((CHK_SpeedHandshake144())
@@@@			&& ((AvailableTxBaudRate == BPS14400_V17) || (AvailableTxBaudRate == BPS14400_V33))){
@@#else
@@		if (SpeedHandshakeRomCheck() == TRUE){
@@			if ((FCM_PtnrChkSpeedHandshake144())
@@			&& ((AvailableTxBaudRate == BPS14400_V17) || (AvailableTxBaudRate == BPS14400_V33))){
@@#endif /* 0 */
@@				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
@@					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */
@@
@@					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
@@				}
@@				else {
@@					V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
@@				}
@@			}
@@#if 0 /* Changed by H.Kubo 1998/01/09 */
@@@@			if ((CHK_SpeedHandshake96())
@@#else
@@			if ((FCM_PtnrChkSpeedHandshake96())
@@#endif /* 0 */
@@			&& ((BPS9600_V29  == AvailableTxBaudRate) || (BPS9600_V17  == AvailableTxBaudRate) ||
@@				(BPS12000_V33 == AvailableTxBaudRate) || (BPS14400_V33 == AvailableTxBaudRate) ||
@@				(BPS12000_V17 == AvailableTxBaudRate) || (BPS14400_V17 == AvailableTxBaudRate))) {
@@
@@				if ((CommandFileOptionItem != SYS_SCANNER_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_MEMORY_SECURE_TX) &&
@@					(CommandFileOptionItem != SYS_SCANNER_RELAY_BROADCAST) &&
@@					(CommandFileOptionItem != SYS_MEMORY_RELAY_BROADCAST)) {	/* 1994/11/25 */
@@
@@					TxSpeedHandshakeFlag = 1;					/** 短縮ハンドシェーク送信フラグ SET */
@@					AvailableTxBaudRate = BPS9600_V29;			/** 送信可能ボーレイト９６００ＢＰＳセット */
@@				}
@@				else {
@@					V8ProcedureRequestFlag = 1;		/** Ｖ８手順移行要求セット */
@@				}
@@			}
@@#if (PRO_F_CODE == ENABLE)
@@			/* Ｆコード送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/01/09  By T.Yamaguchi */
@@			if	((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) ||	/* スキャナサブアドレス送信 */
@@				 (CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)) {	/* メモリサブアドレス送信 */
@@				TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
@@			}
@@#endif
@@#if (PRO_CIPHER == ENABLE)
@@			/* 暗号化送信の短縮ﾊﾝﾄﾞｼｪｰｸは行なわない 1997/10/01  By T.Yamaguchi */
@@			if	(CommandFileOptionItem == SYS_CIPHER_TX) {	/* 暗号化送信 */
@@				TxSpeedHandshakeFlag = 0;					/** 短縮ハンドシェーク送信フラグ クリア */
@@			}
@@#endif
@@		}
@@	}
@@}
#endif /* 0 */
#endif /* (PRO_TX_SPEED == V34) */
