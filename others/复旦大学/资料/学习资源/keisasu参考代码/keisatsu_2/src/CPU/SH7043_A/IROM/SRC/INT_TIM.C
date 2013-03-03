/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : ini_tim.c                                                 */
/*  モジュ-ル    : void INT_Timer10ms(void)                                  */
/*               : void INT_TimerOneshot(void)                               */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 1996/10/15                                                */
/*  概  要       : 10ms/ワンショット タイマ割込みルーチン                    */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\scn_pro.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#else
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#endif

#include "\src\atlanta\ext_v\sys_data.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#else
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#endif

#if (PRO_PRINT_TYPE == LASER)
#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\define\prn_stat.h"
#include "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#include "\src\atlanta\ext_v\cmn_data.h"
#if (PRO_SEPERATE_24V == DISABLE) /* T.Nose 1997/08/25 */
#include "\src\atlanta\define\sys_stat.h"
#endif

void Timer_int_irom(void);	/* モニター１０ｍｓ割込処理 */
void Oneshot_int_irom(void);	/* モニタワンショットタイマー割込み処理 */
void OPR_KeyScan(void); /* キースキャン */
UWORD MDM_ModemStatusCheck(void);	/* T.Nose 1996/06/01 */

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)/* Added by H.Kubo 1997/09/05 */
void 	MDM_ToneCheck(void);
void	MDM_CheckInternalStatus(void);
#endif /* (PRO_MODEM == R288F) */

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/06/13 H.Yoshikawa */
void Tim10msecScannerPrinter(void);
#endif

void SaveReturnAddressAndJumpBegin(void);

/* 位相ずれ対策 インターバルタイマー 割り込みの処理を2回に分ける T.Nose 1998/01/20 */
void INT_Timer10msProcess(void);
extern CONST UBYTE INT_Interval5ms; /* 実体 ini_cpu.c T.Nose 1998/01/23 */
/******************************************************************************
	module		:[１０ｍｓインターバルタイマ割込み]
	function	:[
		1. 10msインターバルタイマ割込みで行う処理を登録します
	]
	return		:[なし]
	common		:[なし]
	machine		:[SH(SH7034/SH704X)]
	language	:[SHC(V.3.0C)]
	keyword		:[INT]
	date		:[1996/1/10]
	author		:[川崎真史]
******************************************************************************/
void INT_Timer10ms(void)
{
	/*---------------------------------------------------------------------*/
	/** コンペアマッチフラグＡをクリアして次の10msタイマ割込を許可します。 */
	/*  (CI割込に影響を与えてはいけない)                                   */
	/*---------------------------------------------------------------------*/
	MTU__TSR0 &= (0xFE);	/* TGFAのクリア */

#if defined(POPLAR_F)
	/* ｷｰｽｷｬﾝ Ｌ４００後継は５ｍｍでキースキャンする */
	OPR_KeyScan();
#endif

	if (INT_Interval5ms) {
		if (SYS_TimerJobSelectSwitch) {
			Timer_int_irom();		/* モニタ１０ｍｓ割り込み処理 */
								/* 次マスク出荷時、内蔵ＲＯＭに戻す T.Nose 1997/11/04 */
			SYS_TimerJobSelectSwitch = 0;
		}
		else {
			INT_Timer10msProcess();
			SYS_TimerJobSelectSwitch = 1;
		}
	}
	else {
		Timer_int_irom();	/* モニタ１０ｍｓ割り込み処理 */
							/* 次マスク出荷時、内蔵ＲＯＭに戻す T.Nose 1997/11/04 */
		INT_Timer10msProcess();
	}

}


/******************************************************************************
	module		:[１０ｍｓインターバルタイマ割込み]
	function	:[
		1. １０ｍｓインターバルタイマ割込みで行う処理を登録します
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		SH704Xではタイマーチャネル０（ＭＴＵ０）を使用する
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INT]
	date		:[1998/01/20]
	author		:[野瀬敏弘]
******************************************************************************/
void INT_Timer10msProcess(void)
{
	UWORD modem_status_result;

	SYS_GeneralTimer++;

#if (PRO_PRINT_TYPE == LED)
	if ((PrinterStatus[PRN_STATUS_0] & PRN_S0_PRINTING)
	 && (PrinterStatus[PRN_STATUS_8] & PRN_S8_PSS)) {	/* PSS追加 1998/02/06 */
		if (!PSS()) {
			PrinterStatus[PRN_STATUS_6] |= PRN_S6_PSS_OFF;
			idet_evt(EVT_PRN_PAPER_SENSOR);	/* イメージプリント用 */
			idet_evt(EVT_PRN_PSS_OFF);		/* リストプリント用   */
		}
	}
#endif

#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* HINOKIはGA割り込みの中で処理します 1998/09/22 by T.Soneoka */
																	   /* Add by Y.Kano 2003/07/14 */
 #if defined(POPLAR_F)
 #else
	/* ｷｰｽｷｬﾝ */
	OPR_KeyScan();
 #endif
#endif

	modem_status_result = MDM_ModemStatusCheck(); /* T.Nose 1996/06/01 */
	if (modem_status_result != 0) {
		idet_evt(modem_status_result);
	}

/* SATSUKI2用カッター制御 start by Y.Kano 2003/06/24 */
#if defined (SATSUKI2)
	Tim10msCutter();
#endif
/* SATSUKI2用カッター制御 end   by Y.Kano 2003/06/24 */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/09/05 */
	MDM_ToneCheck();
	MDM_CheckInternalStatus();
#if (0) /* とりあえず Clober の INT_TIME.ASM のコードをそのまま入れます。
		** by H.Kubo 1997/09/05
		*/
;
; CNG検出用ｾﾞﾛｸﾛｽｶｳﾝﾀのﾁｪｯｸ 1996/12/06 Y.Murata
;
		PUSH	AX
		PUSH	DX
		PUSH	BX
;
		MOV		DX,TMD			;ﾗｯﾁｺﾏﾝﾄﾞ発行
		MOV		AL,80H
		OUT		DX,AL
;
		MOV		DX,TCT2			;ｶｳﾝﾀﾘｰﾄﾞ
		MOV		AX,TCT2_DATA
		IN		AL,DX			;Lower Byte Read
		MOV		BL,AL
		IN		AL,DX			;High Byte Reah
		MOV		AH,AL
		MOV		AL,BL
;
		MOV		BX,AX
		MOV		AX,DS:WORD PTR _SYS_BackUpZeroCrossCountCNG
		SUB		AX,BX
		MOV		DS:WORD PTR _SYS_ZeroCrossCountCNG,AX
		MOV		AX,BX
		MOV		DS:WORD PTR _SYS_BackUpZeroCrossCountCNG,AX
;
		POP		BX
		POP		DX
		POP		AX				;CNGﾁｪｯｸ終了
;
;イベント発生チェック
		CALL   event_check
		JMP    rescheduler
#endif /* 0 */

#endif /* (PRO_MODEM == R288F) */


#if (PRO_FBS == ENABLE)
	SCN_CheckEndSensor();	/* FBS ｴﾝﾄﾞｾﾝｻ監視 T.Nose 1997/01/20 */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/06/13 H.Yoshikawa */
	Tim10msecScannerPrinter();
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/09/18 H.Yoshikawa */
  #if (PRO_NCU_TYPE == SAKAKI_TYPE)
	CMN_ND_SetReset();
  #endif
#endif

}

/******************************************************************************
	module		:[ワンショットタイマ割込み]
	function	:[
		1. ワンショットタイマ割込みで行う処理を登録します
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		SH704Xではタイマーチャネル１（ＭＴＵ１）を使用する
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INT]
	date		:[1996/1/24]
	author		:[野瀬敏弘]
******************************************************************************/
void INT_TimerOneshot(void)
{

	/* SAKAKIでパルスダイヤル時、メイク／ブレイクが短くなるという現象が出ている。
	** トレースの結果ではワンショットタイマーが設定より早く帰ってくるというのが見つかった。
	** よって、ここで、ワンショットタイマーの動作状態とカウンター値を読み出して見ることにする。
	** それとあわせて、動作ビットとカウンターを念のため初期化する処理も入れておく。
	** By O.Kimoto 2001/02/20
	*/
	UBYTE	dummy_TSR1;
	UBYTE	dummy_TSTR;
	
	dummy_TSR1 = MTU__TSR1;
	dummy_TSTR = MTU__TSTR;
	
	/* トレース結果によると不正割り込みが発生していたので、
	** ここで、本当に割り込みが来たのかどうかをチェックして不正割り込みと判断したならば
	** 以下の処理をせずにそのままぬけてます。
	** by O.Kimoto 20001/02/21
	*/
	
	if ((dummy_TSR1 & 0x01) == 0) {
		return;
	}
	
	MTU__TSR1 &= (0xFE);			/* TGFAのクリア */
	MTU__TSTR &= ~TSTR_START_CH1;	/* タイマーストップ */

	Oneshot_int_irom();	/* モニタワンショットタイマ割込処理 */
}
