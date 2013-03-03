/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_OKEY.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 単一キーオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1998/12/28 */
#include	"\src\atlanta\define\fcm_def.h"
#endif
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_a.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\man_pro.h"
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
#include	"\src\atlanta\define\mntsw_g.h"
#endif

#if (PRO_CIPHER == ENABLE)
#include	"\src\atlanta\scd\ext_v\cph_data.h"	/* 追加 98/01/22 T.Fukumoto */
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/02 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#endif		/* End of (defined (KEISATSU)) */

/* Prototype
void	SingleKeyOperation(UBYTE);
#if (PRO_AUTO_RX_SWITCH == ENABLE)
void	ChangeRxMode(void);
#endif
void	ChangeMode(void);
void	ChangeModeSuperFine(UBYTE *);
void	ChangeModeHalfTone(UBYTE *);
void	ChangeDensity(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
void	SetDensityDispBuffer(UBYTE);
void	ChangeDensityLightToDark(UBYTE *);
void	ChangeDensityDarkToLight(UBYTE *);
void	ChangeDensityRotation(UBYTE *);
#endif
void	ChangeMemoryTx(void);
#if (PRO_STAMP == ENABLE)
void	ChangeTxStamp(void);
#endif
*/

/*************************************************************************
	module		:[単一キーオペレーション]
	function	:[
		1.状態に関係なく単一キーで同じオペレーションを行うもの
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/06/29]
	author		:[江口,渡辺一章]
*************************************************************************/
void SingleKeyOperation(UBYTE key)
{
	switch (key) {
	case MODE_KEY:		/* 画質キー */
		ChangeMode();
		break;
	case CONTRAST_KEY:	/* 濃度キー */
		ChangeDensity();
		break;
#if (PRO_AUTO_RX_SWITCH == ENABLE)
	case AUTO_RX_KEY:	/* 自動受信キー */
 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/02 */
		if ((SYB_MachineParameter[M_PARA_SW_I1] & KEY_LOCK_AUTO_RX) ||
			(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)) {
			NackBuzzer();
			break;
		}
 #endif		/* End of (defined (KEISATSU)) */

 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/28 */
		if (CheckIsKanyuLine() && 
			(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)){		/*	指令モート,指令側無効 */
			NackBuzzer();
			break;
		} 
 #endif		/* End of (defined (KEISATSU)) */

		ChangeRxMode();
		break;
#endif
	case MEMORY_TX_KEY:	/* メモリ送信キー */
		ChangeMemoryTx();
		break;
#if !defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/21 */
 #if (PRO_STAMP == ENABLE)
	case STAMP_KEY:		/* 済みスタンプキー */
		ChangeTxStamp();
		break;
 #endif
#endif		/* End of (defined (KEISATSU)) */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/21 */
	case RESERVATION:	/* 会話予約キー */
		if ( SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON ){	/* 指令印加中 Added by SMuratec 夏 2005/09/19 */
			NackBuzzer();
		}
		else if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (FCM_ExecutingS1Info.Protocol==SYS_PROTOCOL_KOBETSU) ) {	/** 個別通信中 Added by SMuratec 夏 2005/09/19*/
			if (CMN_ChangeVoiceSwitch() == FALSE) {/**会話予約のセット・リセット*/
				NackBuzzer();
			}
		}
		else {
			NackBuzzer();
		}

		if (SYS_VoiceSwitch == 1) {
			ReservationLedOn();
		}
		else {
			ReservationLedOff();
		}
		break;
#endif		/* End of (defined (KEISATSU)) */
	default:
		break;
	}
}

#if defined(KEISATSU) 	/* 警察FAX Modify start by SMuratec K.W.Q 2005/07/01 */
void UpdateRxModeDisplay(void)
{
	/* 警察FAX DVT Added by SMuratec 夏 2005/11/14 */
	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
		if ( CheckIsKanyuLine() ){
			AutoRxLedOn();
		}
		else{
			AutoRxLedOff();
		}
	}
	else if( CheckIsKanyuLine() && (SYB_RxModeSwitch & SYS_AUTO_CALLED_SW)) {
		AutoRxLedOn();
	}
	else if( !CheckIsKanyuLine() && (SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW)) {
		AutoRxLedOn();
	}
	else{
		AutoRxLedOff();
	}
}
#endif

/*************************************************************************
	module		:[自動受信キー処理]
	function	:[
		1.手動受信／自動受信を切り替える
		2.ダイアルイン待機の場合なにもしない。（受信モードはかえられない)
	return		:[なし]
	common		:[
		SYB_RxModeSwitch:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC)
	keyword		:[OPR]
	date		:[95/09/13]
	author		:[江口,渡辺一章]
*************************************************************************/
#if (PRO_AUTO_RX_SWITCH == ENABLE)
void ChangeRxMode(void)
{
	
#if defined(KEISATSU) 	/* 警察FAX Modify start by SMuratec K.W.Q 2005/07/01 */
 	if( CheckIsKanyuLine() ){
		SYB_RxModeSwitch ^= SYS_AUTO_CALLED_SW;
		if(SYB_RxModeSwitch & SYS_AUTO_CALLED_SW) {
			AutoRxLedOn();
		}
		else {
			AutoRxLedOff();
		}
	}
	else{
		SYB_RxModeSwitchExt ^= SYS_AUTO_CALLED_SW;
		if(SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW) {
			AutoRxLedOn();
		}
		else {
			AutoRxLedOff();
		}
	}
	
#else
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
	UBYTE ret;

	ret = CMN_PresentReceiveMode();/** 現在の待機モードを獲得する */
	if ((ret == SYS_DIAL_IN_READY) ||	/** ダイヤルイン待機の時 */
		(ret == SYS_MODEM_DIALIN_READY)) {	/** ﾓﾃﾞﾑﾀﾞｲﾔﾙｲﾝの時 */
		NackBuzzer();/** モード変更を弾く */
		return;
	}
 #else
	/* ダイアルイン待機の場合ナック。自動／手動の切り替えはない */
	if (CMN_PresentReceiveMode() == SYS_DIAL_IN_READY) {
		NackBuzzer();
		return;
    }
 #endif
	/* 自動／手動を切り替える */
	SYB_RxModeSwitch ^= SYS_AUTO_CALLED_SW;

	/* 自動受信ＬＥＤの点灯／消灯を切り替える */
	if(SYB_RxModeSwitch & SYS_AUTO_CALLED_SW) {
		AutoRxLedOn();
	}
	else {
		AutoRxLedOff();
	}
	
 #if (PRO_MULTI_LINE == ENABLE)
	MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS);
 #endif
#endif /* 警察FAX Modify end by SMuratec K.W.Q 2005/07/01 */
}
#endif

/*************************************************************************
	module		:[原稿モードを変更]
	function	:[
		1.モードを変更
		,  NORMAL->FINE->SFINE->GRAY	:スーパーファインを２００×４００とする場合
		,  NORMAL->FINE->HFINE->GRAY	:スーパーファインを３００×４００とする場合
	]
	return		:[]
	common		:[
		SYB_ModeSw:
		SYB_CopyModeSw:
	]
	condition	:[]
	comment		:[桐とかではいとった、テストモードのモード変更はとりあえず対応しない。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void ChangeMode(void)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	/*--------------------*/
	/* コピーモードの場合 */
	/*--------------------*/
#if (0)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/10 */
	/* 仕様変更により、電話中でもコピーモードに変更可能になったので、条件を変更します */
//	if ((CHK_ReadyModeCopy()) && (!CheckTelephoneUsing())) {	/* コピーモードで電話未使用の時 */
#endif
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		/* ハードのチェック用に追加 */
/*		if (SYB_MaintenanceSwitch[MNT_SW_A8] & COPY_NORMAL_FINE_ENABLE) {*/	/* メンテナンスＳＷ　Ａ：８－５ */
		if (CHK_UNI_SwCopyTestMode()) {	/* By M.Tachibana 1998/01/22 */
			switch (SYB_CopyModeSw) {
			case SYS_NORMAL:	/** ノーマルの場合				*/
				SYB_CopyModeSw = SYS_FINE;		/** ファインをセット */
				break;
			case SYS_FINE:		/** ファインの場合				*/
				ChangeModeSuperFine(&SYB_CopyModeSw);
				break;
			case SYS_SFINE:		/** スーパーファインの場合		*/
 #if (PRO_HQ_MODE == ENABLE)
			case SYS_HFINE:		/** ハイパーファインの場合		*/
			case SYS_EFINE:		/** エクセレントファインの場合	*/
 #endif
				ChangeModeHalfTone(&SYB_CopyModeSw);
				break;
			case SYS_GRAY16:	/** １６階調					*/
			case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
			case SYS_GRAY64:	/** ６４階調					*/
			case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
				SYB_CopyModeSw = SYS_NORMAL;	/** ノーマルをセット */
				break;
			default:
				break;
			}
			return;
		}

		switch (SYB_CopyModeSw) {
		case SYS_NORMAL:	/** ノーマルの場合				*/
		case SYS_FINE:		/** ファインの場合				*/
		case SYS_SFINE:		/** スーパーファインの場合		*/
 #if (PRO_HQ_MODE == ENABLE)
		case SYS_HFINE:		/** ハイパーファインの場合		*/
		case SYS_EFINE:		/** エクセレントファインの場合	*/
 #endif
			ChangeModeHalfTone(&SYB_CopyModeSw);
			break;
		case SYS_GRAY16:	/** １６階調					*/
		case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
		case SYS_GRAY64:	/** ６４階調					*/
		case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
			ChangeModeSuperFine(&SYB_CopyModeSw);
			break;
		default:
			break;
		}
	}
	/*----------------------*/
	/* ファクスモードの場合 */
	/*----------------------*/
	else {						/* ファクスモードの時 */
		switch (SYB_ModeSw) {
		case SYS_NORMAL:	/** ノーマルの場合				*/
			SYB_ModeSw = SYS_FINE;		/** ファインをセット */
			break;
		case SYS_FINE:		/** ファインの場合				*/
 #if (PRO_CIPHER == ENABLE)
			/* 暗号化送信にはスーパーファインは使用できないので、
			** 暗号化前原稿の蓄積中はスーパーファインの選択をとばし、
			** 写真モードにします。
			** 98/01/20 T.Fukumoto 
			** 次原稿蓄積確認処理に対応
			** 98/03/25 T.Fukumoto 
			*/
			if (ScrambleOn) {	/* ＲＯＭスイッチがＯＮの時 */
				if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
				 && (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE)) {	/* 暗号化前原稿を蓄積中の時 */
					ChangeModeHalfTone(&SYB_ModeSw);	/* 写真モードへ */
				}
  #if (PRO_FBS == ENABLE)
				else if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR)
				 && (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE)) {	/* 暗号化前原稿の次原稿蓄積確認処理時 */
					ChangeModeHalfTone(&SYB_ModeSw);	/* 写真モードへ */
				}
  #endif
				else {
					ChangeModeSuperFine(&SYB_ModeSw);	/* スーパーファインモードへ */
				}
			}
			else {				/* ＲＯＭスイッチがＯＦＦの時 */
				ChangeModeSuperFine(&SYB_ModeSw);		/* スーパーファインモードへ */
			}
 #else
			ChangeModeSuperFine(&SYB_ModeSw);
 #endif
			break;
		case SYS_SFINE:		/** スーパーファインの場合		*/
 #if (PRO_HQ_MODE == ENABLE)
		case SYS_HFINE:		/** ハイパーファインの場合		*/
		case SYS_EFINE:		/** エクセレントファインの場合	*/
 #endif
			ChangeModeHalfTone(&SYB_ModeSw);
			break;
		case SYS_GRAY16:	/** １６階調					*/
		case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
		case SYS_GRAY64:	/** ６４階調					*/
		case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
			SYB_ModeSw = SYS_NORMAL;	/** ノーマルをセット */
			break;
		default:
			break;
		}
	}
#else
	switch (SYB_ModeSw) {
	case SYS_NORMAL:	/** ノーマルの場合				*/
		SYB_ModeSw = SYS_FINE;		/** ファインをセット */
		break;
	case SYS_FINE:		/** ファインの場合				*/
 #if (PRO_CIPHER == ENABLE)
		/* 暗号化送信にはスーパーファインは使用できないので、
		** 暗号化前原稿の蓄積中はスーパーファインの選択をとばし、
		** 写真モードにします。
		** 98/01/20 T.Fukumoto 
		** 次原稿蓄積確認処理に対応
		** 98/03/25 T.Fukumoto 
		*/
		if (ScrambleOn) {	/* ＲＯＭスイッチがＯＮの時 */
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
			 && (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE)) {	/* 暗号化前原稿を蓄積中の時 */
				ChangeModeHalfTone(&SYB_ModeSw);	/* 写真モードへ */
			}
  #if (PRO_FBS == ENABLE)
			else if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR)
			 && (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE)) {	/* 暗号化前原稿の次原稿蓄積確認処理時 */
				ChangeModeHalfTone(&SYB_ModeSw);	/* 写真モードへ */
			}
  #endif
			else {
				ChangeModeSuperFine(&SYB_ModeSw);	/* スーパーファインモードへ */
			}
		}
		else {				/* ＲＯＭスイッチがＯＦＦの時 */
			ChangeModeSuperFine(&SYB_ModeSw);		/* スーパーファインモードへ */
		}
 #else
  #if defined(KEISATSU)	/* 警察FAX DVT_ID17 Modify by SMuratec 夏 2005/11/05 */
		if( FCM_ISSEI_TX ){	/* 一斉送信又は指令送信のスキャナ中、超高画質を無効になる */
			ChangeModeHalfTone(&SYB_ModeSw);
		}
		else{
			ChangeModeSuperFine(&SYB_ModeSw);
		}
  #else
		ChangeModeSuperFine(&SYB_ModeSw);
  #endif	/* KEISATSU */
 #endif
		break;
	case SYS_SFINE:		/** スーパーファインの場合		*/
 #if (PRO_HQ_MODE == ENABLE)
	case SYS_HFINE:		/** ハイパーファインの場合		*/
	case SYS_EFINE:		/** エクセレントファインの場合	*/
 #endif
		ChangeModeHalfTone(&SYB_ModeSw);
		break;
	case SYS_GRAY16:	/** １６階調					*/
	case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
	case SYS_GRAY64:	/** ６４階調					*/
	case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
 #if (PRO_PRINT_TYPE == THERMAL)	/* Add By H.Fujimura 1998/12/28 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) {	/* スキャナー・コピー中の時 */
			SYB_ModeSw = SYS_FINE;		/** ファインをセット */
		}
		else {
			SYB_ModeSw = SYS_NORMAL;	/** ノーマルをセット */
		}
 #else
		SYB_ModeSw = SYS_NORMAL;	/** ノーマルをセット */
 #endif
		break;
	default:
		break;
	}
#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Modify by SMuratec 李 2004/06/16 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) {	/* スキャナー・コピー中の時 */
		if (SYB_ModeSw == SYS_NORMAL || SYB_ModeSw == SYS_FINE ) {
			SYB_ModeSw = SYS_SFINE;
		}
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

	/* 画質ＬＥＤ点灯 */
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	ModeLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[超高画質モード切り替え]
	function	:[
		1.画質を超高画質に切り替える
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/24]
	author		:[渡辺一章]
*************************************************************************/
void ChangeModeSuperFine(UBYTE *mode_switch)
{
	*mode_switch = SYS_SFINE;		/** スーパーファインをセット */
#if (PRO_HQ_MODE == ENABLE)
	if (CHK_UNI_HyperFineON()) {			/* 超高画質がハイパーファインの時 */
		*mode_switch = SYS_HFINE;	/** ハイパーファインをセット */
	}
	if( SYB_MaintenanceSwitch[40] & 0x02 ){	/* 超高画質がエクセレントファインの時 */
		*mode_switch = SYS_EFINE;	/** エクセレントファインをセット*/
	}
#endif
}

/*************************************************************************
	module		:[写真モード切り替え]
	function	:[
		1.画質を写真に切り替える
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/24]
	author		:[渡辺一章]
*************************************************************************/
void ChangeModeHalfTone(UBYTE *mode_switch)
{
	if (CHK_Halftone64ON()) {	/** ６４階調に設定されている時 */
		if (CHK_Halftone2ON()) {	/** 写真２（像域分離）である場合 */
			*mode_switch = SYS_GRAY64_SEP;	/** ６４階調：像域分離をセット */
		}
		else {						/** 写真１（像域分離）の場合 */
			*mode_switch = SYS_GRAY64;		/** ６４階調をセット */
		}
	}
	else {						/** １６階調に設定されている時 */
		if (CHK_Halftone2ON()) {	/** 写真２（像域分離）である場合 */
			*mode_switch = SYS_GRAY16_SEP;	/** １６階調：像域分離をセット */
		}
		else {						/** 写真１（像域分離）の場合 */
			*mode_switch = SYS_GRAY16;		/** １６階調をセット */
		}
	}
}

/*************************************************************************
	module		:[濃度変更]
	function	:[
		（ポプラ）
		1.１度、濃度キーが押されたら、現在の設定値を表示します
		2.濃度設定表示中に、　濃度キーが押されたら濃度を、薄く→濃く→薄く→・・・に変更します
		3.濃度設定表示中に、左矢印キーが押されたら濃度を、濃く→薄くに変更します
		4.濃度設定表示中に、右矢印キーが押されたら濃度を、薄く→濃くに変更します
		（アンズ）
		1.濃度をLight->Normal->Dark->Light・・・の順に変更します
	]
	return		:[]
	common		:[SYB_DensitySw]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void ChangeDensity(void)
{
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	UBYTE	*density_switch;

 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	/* ＣＧＲＡＭに濃度・ボリューム設定用のデータを書き込みます */
	WriteCGRAM((UBYTE *)CG_RamTableDensityVolumeSet);
 #endif

	/* 現在のモードにより、濃度を作業用変数にセットする */
 #if (0)	/* （仕様変更）電話中のコピーオペレーション追加 by K.Watanabe '97.09/10 */
	/* 仕様変更により、電話中でもコピーモードに変更可能になったので、条件を変更します */
 //	if ((CHK_ReadyModeCopy()) && (!CheckTelephoneUsing())) {	/* コピーモードで電話未使用の時 */
 #endif
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		density_switch = &SYB_CopyDensitySw;
	}
	else {						/* ファクスモードの時 */
		density_switch = &SYB_DensitySw;
	}

	/* 濃度変更用に、押されたキーの値を無理矢理変更しているので、ここで元々押されていたキーをチェックします */
	switch (OPR_ChangeDensityKey) {	/* 濃度変更に使用されたキー */
	case CONTRAST_KEY:		/* 濃度キーが押された時 */
		ChangeDensityRotation(density_switch);
		break;
	case CURSOR_LEFT_KEY:	/* 左矢印キーが押された時 */
		ChangeDensityDarkToLight(density_switch);
		break;
	case FUNCTION_KEY:		/* 右矢印キーが押された時 */
		ChangeDensityLightToDark(density_switch);
		break;
	default:
		break;
	}
	/* 濃度設定表示中に使用する濃度変更キー by K.Watanabe 1997/11/27 */
	OPR_ChangeDensityKey = NO_KEYCODE;

 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/18 */
	/* 上段の表示 */
	DisplayStringHigh(0, D2W_SetPaperContrast);		/* "ﾖﾐﾄﾘ ﾉｳﾄﾞ ｾｯﾃｲ      " */
 #endif

	/* 下段表示ワーディングのセット */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferLow, D2W_ContrastLightDark);	/* "   ｳｽｸ         ｺｸ   " */

	/* 下段表示バッファに濃度の設定値をセット */
	SetDensityDispBuffer(*density_switch);

	/* 下段のチャイルド表示 */
	ParamChildDisplayStringLow(FunctionDisplayBufferLow);

	/* 濃度設定中をＯＮにします by K.Watanabe 1997/11/25 */
	IsSettingDensity = TRUE;
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/15 Y.Matsukuma */
	/* ミノルタ用のカセット選択プロテクトを、ECMのON/OFFでみます */
	if ( CHK_ECM_ON() != 0 ) {
		NackBuzzer();
		return;
	}
 #endif
	switch (SYB_DensitySw) {
	case SYS_NORMAL_DENSITY:	/* Normalの時 */
		SYB_DensitySw = SYS_DARK_DENSITY;
		break;
	case SYS_DARK_DENSITY:		/* Darkの時 */
		SYB_DensitySw = SYS_LIGHT_DENSITY;
		break;
	case SYS_LIGHT_DENSITY:		/* Lightの時 */
		SYB_DensitySw = SYS_NORMAL_DENSITY;
		break;
	default:
		break;
	}

	/* 原稿濃度ＬＥＤ点灯 */
 #if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
	DensityLedOn();
 #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
#endif
}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
/*************************************************************************
	module		:[濃度設定値セット]
	function	:[
		1.下段表示用バッファに、現在の濃度の設定値（ＣＧを使用）をセットします
	]
	return		:[なし]
	common		:[
		FunctionDisplayBufferLow[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/25]
	author		:[渡辺一章]
*************************************************************************/
void SetDensityDispBuffer(UBYTE density_switch)
{
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) /* T.Fukumoto 97/10/27 */
	/* 両端を表すＣＧをセット */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//	FunctionDisplayBufferLow[7]  = 0xF0;
//	FunctionDisplayBufferLow[13] = 0xF1;
//
//	/* 濃度の段階を表すＣＧをセット */
//	FunctionDisplayBufferLow[8]  = 0xF2;
//	FunctionDisplayBufferLow[9]  = 0xF2;
//	FunctionDisplayBufferLow[10] = 0xF3;
//	FunctionDisplayBufferLow[11] = 0xF2;
//	FunctionDisplayBufferLow[12] = 0xF2;
#endif
	FunctionDisplayBufferLow[7]  = OPR_CG_FONT_0;
	FunctionDisplayBufferLow[13] = OPR_CG_FONT_1;

	/* 濃度の段階を表すＣＧをセット */
	FunctionDisplayBufferLow[8]  = OPR_CG_FONT_2;
	FunctionDisplayBufferLow[9]  = OPR_CG_FONT_2;
	FunctionDisplayBufferLow[10] = OPR_CG_FONT_3;
	FunctionDisplayBufferLow[11] = OPR_CG_FONT_2;
	FunctionDisplayBufferLow[12] = OPR_CG_FONT_2;

	/* 現在設定されている濃度をセットします */
	switch (density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[8] = 0xF4;
#endif
		FunctionDisplayBufferLow[8] = OPR_CG_FONT_4;
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* 薄く－普通の間 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[9] = 0xF4;
#endif
		FunctionDisplayBufferLow[9] = OPR_CG_FONT_4;
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[10] = 0xF4;
#endif
		FunctionDisplayBufferLow[10] = OPR_CG_FONT_4;
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* 濃く－普通の間 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[11] = 0xF4;
#endif
		FunctionDisplayBufferLow[11] = OPR_CG_FONT_4;
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[12] = 0xF4;
#endif
		FunctionDisplayBufferLow[12] = OPR_CG_FONT_4;
		break;
	default:
		break;
	}
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) /* ポプラＬの濃度は３段階 T.Fukumoto 97/10/27 */
	/* 両端を表すＣＧをセット */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//	FunctionDisplayBufferLow[8]  = 0xF0;
//	FunctionDisplayBufferLow[12] = 0xF1;
//
//	/* 濃度の段階を表すＣＧをセット */
//	FunctionDisplayBufferLow[9]  = 0xF2;
//	FunctionDisplayBufferLow[10] = 0xF3;
//	FunctionDisplayBufferLow[11] = 0xF2;
#endif
	FunctionDisplayBufferLow[8]  = OPR_CG_FONT_0;
	FunctionDisplayBufferLow[12] = OPR_CG_FONT_1;

	/* 濃度の段階を表すＣＧをセット */
	FunctionDisplayBufferLow[9]  = OPR_CG_FONT_2;
	FunctionDisplayBufferLow[10] = OPR_CG_FONT_3;
	FunctionDisplayBufferLow[11] = OPR_CG_FONT_2;

	/* 現在設定されている濃度をセットします */
	switch (density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[9] = 0xF4;
#endif
		FunctionDisplayBufferLow[9] = OPR_CG_FONT_4;
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[10] = 0xF4;
#endif
		FunctionDisplayBufferLow[10] = OPR_CG_FONT_4;
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		FunctionDisplayBufferLow[11] = 0xF4;
#endif
		FunctionDisplayBufferLow[11] = OPR_CG_FONT_4;
		break;
	default:
		break;
	}
 #endif
}

/*************************************************************************
	module		:[濃度変更（薄く→濃く）]
	function	:[
		1.濃度を現在の設定値から、薄く→やや薄く→普通→やや濃く→濃くの順で変更します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/25]
	author		:[渡辺一章]
*************************************************************************/
void ChangeDensityLightToDark(UBYTE *density_switch)
{
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) /* T.Fukumoto 97/10/27 */
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		*density_switch = SYS_LIGHT_NORMAL_DENSITY;	/* 薄く－普通の間をセット */
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* 薄く－普通の間 */
		*density_switch = SYS_NORMAL_DENSITY;		/* 普通をセット */
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_DARK_NORMAL_DENSITY;	/* 濃く－普通の間をセット */
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* 濃く－普通の間 */
		*density_switch = SYS_DARK_DENSITY;			/* 濃くをセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		NackBuzzer();
		break;
	default:
		break;
	}
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) /* ポプラＬの濃度は３段階 T.Fukumoto 97/10/27 */
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		*density_switch = SYS_NORMAL_DENSITY;	/* 普通をセット */
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_DARK_DENSITY;		/* 濃くをセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		NackBuzzer();
		break;
	default:
		break;
	}
 #endif
}

/*************************************************************************
	module		:[濃度変更（濃く→薄く）]
	function	:[
		1.濃度を現在の設定値から、濃く→やや濃く→普通→やや薄く→薄くの順で変更します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/25]
	author		:[渡辺一章]
*************************************************************************/
void ChangeDensityDarkToLight(UBYTE *density_switch)
{
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) /* T.Fukumoto 97/10/27 */
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		NackBuzzer();
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* 薄く－普通の間 */
		*density_switch = SYS_LIGHT_DENSITY;		/* 薄くをセット */
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_LIGHT_NORMAL_DENSITY;	/* 薄く－普通の間をセット */
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* 濃く－普通の間 */
		*density_switch = SYS_NORMAL_DENSITY;		/* 普通をセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		*density_switch = SYS_DARK_NORMAL_DENSITY;	/* 濃く－普通の間をセット */
		break;
	default:
		break;
	}
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) /* ポプラＬの濃度は３段階 T.Fukumoto 97/10/27 */
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		NackBuzzer();
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_LIGHT_DENSITY;	/* 薄くをセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		*density_switch = SYS_NORMAL_DENSITY;	/* 普通をセット */
		break;
	default:
		break;
	}
 #endif
}

/*************************************************************************
	module		:[濃度変更（薄く→濃く→薄く）]
	function	:[
		1.濃度を現在の設定値から、薄く→やや薄く→普通→やや濃く→濃く→薄く→・・・の順で変更します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/29]
	author		:[渡辺一章]
*************************************************************************/
void ChangeDensityRotation(UBYTE *density_switch)
{
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		*density_switch = SYS_LIGHT_NORMAL_DENSITY;	/* 薄く－普通の間をセット */
		break;
	case SYS_LIGHT_NORMAL_DENSITY:	/* 薄く－普通の間 */
		*density_switch = SYS_NORMAL_DENSITY;		/* 普通をセット */
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_DARK_NORMAL_DENSITY;	/* 濃く－普通の間をセット */
		break;
	case SYS_DARK_NORMAL_DENSITY:	/* 濃く－普通の間 */
		*density_switch = SYS_DARK_DENSITY;			/* 濃くをセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		*density_switch = SYS_LIGHT_DENSITY;		/* 薄くをセット */
		break;
	default:
		break;
	}
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) /* ポプラＬの濃度は３段階 T.Fukumoto 97/10/27 */
	switch (*density_switch) {
	case SYS_LIGHT_DENSITY:			/* 薄く */
		*density_switch = SYS_NORMAL_DENSITY;		/* 普通をセット */
		break;
	case SYS_NORMAL_DENSITY:		/* 普通 */
		*density_switch = SYS_DARK_DENSITY;			/* 濃くをセット */
		break;
	case SYS_DARK_DENSITY:			/* 濃く */
		*density_switch = SYS_LIGHT_DENSITY;		/* 薄くをセット */
		break;
	default:
		break;
	}
 #endif
}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */

/*************************************************************************
	module		:[メモリ送信切り替え]
	function	:[
		1.メモリ送信キーが押されたときの処理を実行。
		2.メモリ送信／スキャナ送信を切り替える。
		3.キーが押された時の通信のみ有効な設定。
	]
	return		:[]
	common		:[SYB_LocalStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/13]
	author		:[江口]
*************************************************************************/
void ChangeMemoryTx(void)
{
	if (CMN_CheckMemoryTxSetting() == FALSE) {
		SYB_LocalStatus[0] |= SYS_MEMORY_TX_ON;
		MemoryTxLedOn();
	}
	else {
		SYB_LocalStatus[0] &= ~SYS_MEMORY_TX_ON;
		MemoryTxLedOff();
	}
}

/*************************************************************************
	module		:[済みスタンプ設定切り替え]
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
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
#if (PRO_STAMP == ENABLE)
void ChangeTxStamp(void)
{
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1998/12/28 */
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	/* 朱色原稿読み取りON/OFF有効時 */
	if (CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_RED_SCAN) {
			SYB_LocalStatus[0] &= ~SYS_RED_SCAN;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
			SYB_LocalStatus[0] |= SYS_RED_SCAN;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return;
	}
	/*【CSDR-No.111】通信証ON/OFF有効時 */
	if (!CHK_UNI_RedScanModeEnable() && CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
			if (CTRY_RCR() && CHK_RCR_ON()) {	/* 機器設定の設定値が受領証の時 */
				SYB_ConfirmationReportSwitch = RCR_REQUEST;
			}
			else {								/* 機器設定の設定値が送信証の時 */
				SYB_ConfirmationReportSwitch = TCR_REQUEST;
			}
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
			SYB_ConfirmationReportSwitch = NO_CONFIRMATION_REPORT;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return;
	}
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	if (!CHK_UNI_RedScanModeEnable() && !CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_TTI_TX_AVAILABLE_ON) {
			SYB_LocalStatus[0] &= ~SYS_TTI_TX_AVAILABLE_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
			SYB_LocalStatus[0] |= SYS_TTI_TX_AVAILABLE_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return;
	}
  #else
	/*【CSDR-No.111】通信証ON/OFF有効時 */
	if (CHK_UNI_CSDR_ConfirmOprEnable() && !CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
			if (CTRY_RCR() && CHK_RCR_ON()) {	/* 機器設定の設定値が受領証の時 */
				SYB_ConfirmationReportSwitch = RCR_REQUEST;
			}
			else {								/* 機器設定の設定値が送信証の時 */
				SYB_ConfirmationReportSwitch = TCR_REQUEST;
			}
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
			SYB_ConfirmationReportSwitch = NO_CONFIRMATION_REPORT;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return;
	}
	/*【CSDR-No.102】発信元ON/OFF有効時 */
	if (!CHK_UNI_CSDR_ConfirmOprEnable() && CHK_UNI_CSDR_TtiTxOprEnable()) {
		if (SYB_LocalStatus[0] & SYS_TTI_TX_AVAILABLE_ON) {
			SYB_LocalStatus[0] &= ~SYS_TTI_TX_AVAILABLE_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		else {
			SYB_LocalStatus[0] |= SYS_TTI_TX_AVAILABLE_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
			StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		}
		return;
	}
  #endif
 #endif
	if (SYB_LocalStatus[0] & SYS_STAMP_ON) {
		SYB_LocalStatus[0] &= ~SYS_STAMP_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		StampLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	}
	else {
		SYB_LocalStatus[0] |= SYS_STAMP_ON;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
		StampLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	}
}
#endif
