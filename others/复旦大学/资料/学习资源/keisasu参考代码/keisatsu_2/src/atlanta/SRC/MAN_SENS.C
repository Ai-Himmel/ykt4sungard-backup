/**********************************************************************
*               BY:  S.Kawasaki
*             DATE:  Tue 24 Mar 1992
*        Copy Date:  1996/10/22 From \src\kobe\anzu\src\ By M.Kotani
*        FILE NAME:  sensor.c
*      DESCRIPTION:  センサーの状態を10ｍｓｅｃ毎に監視するタスク
*  PUBLIC ROUTINES:  void InitializeSensor( void )
*                    void MAN_SensorTask(void)
*                    void MAN_CheckPrinterSensor(void)
* PRIVATE ROUTINES:  無し
*        REFERENCE:  SENSOR.JSW
**********************************************************************@H*/
/*定義ファイル*/
/*SYS*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\syslifem.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_h.h"
/*#include "\src\memsw\define\mem_sw_f.h"*/
/* ミラーキャリッジエラーデバッグ */
#include "\src\atlanta\define\mntsw_g.h"
/*MON*/
#include "\src\atlanta\define\mon_pro.h"
#if (PRO_CPU == SH7043)
	#include "\src\atlanta\sh7043\define\sh_port.h"
	#include "\src\atlanta\sh7043\define\io_pro.h"
	#include "\src\atlanta\sh7043\define\def_tib.h"
	#include "\src\atlanta\sh7043\define\def_evtn.h"
	#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif
/*PRN*/
#if (PRO_PRINT_TYPE == LASER)
	#include "\src\atlanta\prt\sp322\define\prn_def.h"
	#include "\src\atlanta\prt\sp322\define\prn_stat.h"
	#include "\src\atlanta\prt\sp322\define\prn_pro.h"
	#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LED)
	#include "\src\atlanta\prt\ph3\define\prn_def.h"
	#include "\src\atlanta\prt\ph3\define\prn_stat.h"
	#include "\src\atlanta\prt\ph3\define\prn_pro.h"
	#include "\src\atlanta\prt\ph3\ext_v\prn_data.h"
	#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
	#include "\src\atlanta\define\mntsw_h.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL)
 #if defined(STOCKHM2)
 	#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
 #else
	#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
 #endif
#endif
/*参照ファイル*/
/*SYS*/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\mnt_sw.h"
/*DPR*/
#if (PRO_PC_PRINT == ENABLE)
	#include	"\src\atlanta\ext_v\dpr_data.h"
	#include	"\src\atlanta\define\dpr_pro.h"
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/10/04 By M.Maeda */
#include "\src\atlanta\define\cmn_def.h"
#endif

#if defined(HINOKI2) || defined (HINOKI3)	/* Add by Y.Kano 2004/02/04 */
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/27 */
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\man_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\define\fcm_def.h"
#endif /* defined (KEISATSU) */

#define	DETECT_TIME				20		/* 20 * 10ms = 200ms */
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)
/*#define	DETECT_TIME_LONG		40		@* 40 * 10ms = 400ms V851 FAN ﾛｯｸ検出時間延長 By Y.Suzuki 2002/09/24 */
#define	DETECT_TIME_LONG		100		/* 100 * 10ms = 1000ms RDC 200300268 V851 FAN ﾛｯｸ検出時間延長 By Y.Suzuki 2003/06/26 */
#endif
#if (PRO_PRINT_TYPE == LASER)
#define	DETECT_TIME_CASSETTE	200		/* 200 * 10ms = 2000ms */
#endif
#if (PRO_PRINT_TYPE == LED)
#define	DETECT_TIME_CASSETTE	20		/* 40 * 10ms = 400ms */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* SAKAKI 1999/01/28 H.Yoshikawa */
#define	RXIL_DETECT_TIME		40		/* 40 * 10ms = 400ms */
#endif
#if (PRO_PRINT_TYPE == THERMAL)			 /* HINOKI 1999/01/28 H.Yoshikawa */
#if (0) /* 1999/04/22 by T.Soneoka */
** #define	RXIL_DETECT_TIME		20		/* 20 * 10ms = 200ms *//* 従来と同じ値です */
#else
#define	RXIL_DETECT_TIME		50		/* 50 * 10ms = 500ms */
#endif
#endif

/*スタティック変数*/
static MESSAGE_t	SensorTaskMessage = {0};
static MESSAGE_t	*SensorMsg = 0;

#if (PRO_PRINT_TYPE == LED)
static UWORD wk_paper_size1 = 0;
static UWORD wk_paper_size2 = 0;
static UWORD wk_paper_size3 = 0;
static UWORD old_paper_size1 = 0;
static UWORD old_paper_size2 = 0;
static UWORD old_paper_size3 = 0;
static UWORD paper_size1 = 0;
static UWORD paper_size2 = 0;
static UWORD paper_size3 = 0;
static UWORD size_counter1 = 0;
static UWORD size_counter2 = 0;
static UWORD size_counter3 = 0;
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* (DVT修正：初期化前の状態退避に関して変量が使用しなければならない事) Added by SMuratec 李 2004/08/25 */
static UWORD print_status1 = 0;
static UWORD print_status2 = 0;
static UWORD print_status3 = 0;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/18 */
UBYTE	IsSHIREIDisable = FALSE;
UBYTE	IsSHIREIInStart = FALSE;
#endif /* defined (KEISATSU) */

/*--------------------------------------*/
/*	センサー・タスク　イニシャル処理	*/
/*--------------------------------------*/
void InitializeSensor( void )
{
	OldDS1 = 0;		/** DS1を強制的にOFF */
	OldDS2 = 0;		/** DS2を強制的にOFF */
#if defined (KEISATSU) /* ハンドセット電話状態 Added by SMuratec 李 2005/06/27 */
	OldSHIREI = 0;
	IsSHIREIDisable = FALSE;
	IsSHIREIInStart = FALSE;
	/* 警察FAX DVT_ID81 Added by SMuratec 李 2005/12/21 */
	IsSHIREIKido = FALSE;
#endif /* defined (KEISATSU) */

	SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_DS1_ON+SYS_SENSOR_DS2_ON+SYS_SENSOR_DS3_ON);	
	
	OldPB4 = 0;		/** PB4を強制的にA4 */
	SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PB4_ON);

#if (PRO_PAPER_TYPE == ROLL_PAPER) 	/* TBD */
	if (OldPS1 = (UBYTE)PS1()) { /** PS1を強制的に紙有り */
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PS1_ON);
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;	/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PS1_ON);
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;		/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}
#endif

#if (PRO_SEPERATE_INTER_LOCK == DISABLE) /* プリンター、スキャナーのインター・ロックが共通 */
 #if defined (SATSUKI2) || defined(STOCKHM2)	/* SATSUKI2仕様 by Y.Kano 2003/07/02 */
	if (OldInterLock = (UBYTE)TXIL()) {	/** インター・ロックをオープン */
		SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN);
	}
	else {
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN);
	}
 #else
	if (OldInterLock = (UBYTE)InterLock()) {	/** インター・ロックをオープン */
	}
 #endif
#endif

#if (PRO_SEPERATE_INTER_LOCK == ENABLE) /* プリンター、スキャナーのインター・ロックが別々 */
	if (OldTXIL = (UBYTE)TXIL()) {	/** TXILを強制的にオープン */
		SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_SCANNER_OPEN);
	}
	else {
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_SCANNER_OPEN);
	}
 #if (PRO_PRINT_TYPE == LED)
	if (OldRXIL = (UBYTE)RXIL()) {	/** RXILを強制的にオープン */
		SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_PRINTER_OPEN);
	}
	else {
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_PRINTER_OPEN);
	}
 #endif
 #if (PRO_PRINT_TYPE == LASER)
	SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_PRINTER_OPEN);
 #endif
 #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/10/21 H.Yoshikawa */
	if (OldRXIL = (UBYTE)RXIL()) {	/** RXILを強制的にオープン */
		SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_PRINTER_OPEN);
	}
	else {
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_PRINTER_OPEN);
	}
 #endif
#endif

#if (PRO_FBS == ENABLE) || (PRO_UPPER_COVER == ENABLE)	/* 1998/02/25  By T.Yamaguchi */
	if (OldAPS = APS()) {	/** APS/TOP_COVERが閉じている */
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_BOOK_OPEN);
	}
	else {
		SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_BOOK_OPEN);
	}
#endif


#if (PRO_DIALIN == ENABLE)/* && !defined(SATSUKI2) 復活 O.Oshima 2003/10/31 *//* SATSUKI2は待機モードでダイヤルイン待機を持ちます。O.Oshima 2003/06/25 */
	OldDialIn = DialIn()? (UBYTE)0:(UBYTE)1;
	SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_DIAL_IN_ON);
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
	OldScrambleOn = CheckScrambleSwOn(); /* 背面スクランブルSW */
	if (OldScrambleOn == TRUE) {
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= SYS_SCRAMBLE_ON;
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~SYS_SCRAMBLE_ON;
	}
#endif

	MAN_InitPrinterSensor();

#if (PRO_PAPER_TYPE == ROLL_PAPER)
	if(PB4()) { /** Ｂ４センサーＯＮなら */
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= SYS_SENSOR_PB4_ON;
		SYS_Paper1Size = SYS_B4_PAPER;
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~SYS_SENSOR_PB4_ON;
		SYS_Paper1Size = SYS_A4_PAPER;
	}
#endif

/* Added by SMuratec 夏 2004/4/20 */
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)	/* 条件にSTOCKHM2を追加 By O.Kimoto 2004/10/15 */
	if(PB4()) { /** Ｂ４センサーＯＮなら */
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= SYS_SENSOR_PB4_ON;
		SYS_Paper1Size = SYS_B4_PAPER;
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~SYS_SENSOR_PB4_ON;
		SYS_Paper1Size = SYS_A4_PAPER;
	}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
 #if (PRO_PAPER_TYPE == CUT_PAPER)
	OldPSCST = CassettePaper1();
	OldWPSCST = CassettePaper2();

	/* 電源立ち上げ１発目は　チャタを見ず、マシーンステータスに紙有無をセット */
	if ( OldPSCST || OldWPSCST ) {	/* 上段 or 下段 どちらかが紙がある */
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;	/* ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}
	else {		/* 上段 or 下段 両方紙無し */
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;		/* ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}

 #endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
	if (NewRibon = (UBYTE)RIBON()) {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_INK);
	}
	else {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= (SYS_PRINTER_NO_INK);
	}
#endif


#if defined(STOCKHM2)/*(PRO_PRINT_TYPE == THERMAL)*/
	if (OldRibon = (UBYTE)RIBON()) {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_INK);
	}
	else {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= (SYS_PRINTER_NO_INK);
	}
#endif
}

unsigned char MAN_TopCoverNeedToBeOpenFlag = 0;	/** By S.Kawasaki 1997/05/07 JAM0507 */
/*********************************************************************************/
/**　Module Header For CIM-E ********************************************
		module		:	[ｾﾝｻｰ･ﾀｽｸ]
		function	:	[以下のセンサーのON/OFF状態を監視し、夫々に応じた
						ﾒｯｾｰｼﾞをﾒｲﾝ･ﾀｽｸへ送信する。
						１．ＤＳ１
						２．ＤＳ２
						３．ＤＳ３
						４．ｽｷｬﾅｰ･ｶﾊﾞｰ
						５．ﾌﾟﾘﾝﾀｰ･ｶﾊﾞｰ
						６．ｼﾞｬﾑ･ｶﾊﾞｰ1
						７．ｼﾞｬﾑ･ｶﾊﾞｰ２
						８．A4/B4センサ－（メッセ－ジの送信はしない）
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
 		keyword		:	[MAN]
     	date		:	[93/12/01(水)]
 		author		:	[川崎真史]
************************************************************************/
void MAN_SensorTask(void)
{
	UBYTE DS1_Counter = DETECT_TIME;
	UBYTE DS2_Counter = DETECT_TIME;
	UBYTE PB4_Counter = DETECT_TIME;
	UBYTE PS1_Counter = DETECT_TIME;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/18 */
	UBYTE SHIREI_Counter = DETECT_TIME;
#endif /* defined (KEISATSU) */
	
#if (PRO_PRINT_TYPE == THERMAL) /* HINOKI */
	UBYTE PS2_Counter = DETECT_TIME;
#endif
#if (PRO_DIALIN == ENABLE)
	UBYTE DialInCounter = DETECT_TIME;
#endif
#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
	UBYTE scramble_on_counter = DETECT_TIME;
	MESSAGE_t main_msg;
	
	BOOL s1_error_prev = FALSE;
#endif
#if (PRO_PRINT_TYPE == LASER)
	UBYTE no_paper_counter1 = 0;
	UBYTE no_paper_counter2 = 0;
#endif
#if (PRO_PRINT_TYPE == LED)
	UBYTE paper_size = 0;
	UBYTE unit2 = 0;
	UBYTE unit3 = 0;
	UBYTE paper_counter = 0;
	UBYTE PSS_Counter = DETECT_TIME;
	UBYTE PDS_Counter = DETECT_TIME;
	UBYTE HPES_Counter = DETECT_TIME;
	UBYTE DrumSwCounter = DETECT_TIME;
	UBYTE FanLockCounter = DETECT_TIME;
	UBYTE PsFanLockCounter = DETECT_TIME;
	UBYTE MotorLockCounter = DETECT_TIME;
	UBYTE HvFuseCounter = DETECT_TIME;	/* By M.Tachibana 1998/01/22 */
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)
	UBYTE long_detect_time = 0;/* V851 FAN ﾛｯｸ検出時間延長 By Y.Suzuki 2002/09/24*/
/*	UBYTE FanLockDetectionTimes = 6;	@* RDC 200300268 FAN LOCK リトライ回数5回 V851 By Y.Suzuki 2003/06/23 */
#endif
#endif

#if (PRO_SEPERATE_INTER_LOCK == ENABLE)
	UBYTE TXIL_Counter = DETECT_TIME;
  #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) /* SAKAKI/HINOKI *//* 1999/01/30 H.Yoshikawa */
	UBYTE RXIL_Counter = RXIL_DETECT_TIME;	/* 1999/01/28 H.Yoshikawa */
  #else
	UBYTE RXIL_Counter = DETECT_TIME;
  #endif
#endif

#if (PRO_SEPERATE_INTER_LOCK == DISABLE)
 #if defined (SATSUKI2)	/* SATSUKI2仕様 by Y.Kano 2003/07/02 */
	UBYTE InterLockCounter = DETECT_TIME;
 #else
	UBYTE InterLockCounter = DETECT_TIME;
 #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)/*defined(STOCKHM2)*/
	UBYTE RibonCounter = DETECT_TIME;
#endif

#if (PRO_FBS == ENABLE)
	UBYTE APS_Counter = DETECT_TIME;		/* ADF許可センサのチャタリング監視時間 */
#endif

#if (PRO_UPPER_COVER == ENABLE)				/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	UBYTE APS_Counter = DETECT_TIME;		/* ADF許可センサのチャタリング監視時間 */
#endif

#if (PRO_FANLOCK_DETECT_TIME == ENABLE)
	if (!CHK_UNI_FanLockDetectTime()) {/* V851 FAN ﾛｯｸ検出時間延長 By Y.Suzuki 2002/09/24 */
		long_detect_time = 1;
		FanLockCounter = DETECT_TIME_LONG;
		PsFanLockCounter = DETECT_TIME_LONG;
	}
#endif
	
	MAN_TopCoverNeedToBeOpenFlag = 0;	/** By S.Kawasaki 1997/05/07 JAM0507 */

	SensorTaskMessage.Item = FROM_SENSOR;
	InitializeSensor();					/** ｾﾝｻｰ･ﾀｽｸで使用する大域変数の初期化 */

	while(1) { /** ﾊﾟﾜｰOFFされるまでﾙｰﾌﾟ */

		wai_tsk(1); /** 10ms待ち*/

#if (PRO_MULTI_LINE == ENABLE)	/* 1996/11/09 Y.Murata */
		/* ＤＰＲ（オプションの通信タスク）からメッセージをチェックしてメインに送信 */
		MAN_CheckFaxComOption();
#endif

#if (PRO_PC_PRINT == ENABLE)
		/** ＤＰＲ（プリンターオプション）からのメッセージをチェックしてメインに送信 */
		MAN_CheckPrinterOption();
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/18 */
		/***********************************************************************************/
		/* ＳＨＩＲＥＩポートの監視                                                            */
		/***********************************************************************************/
#if 0 	/* 警察FAX DVT_ID64 Modify by SMuratec 夏 2005/12/14 */ 
		NewSHIREI = (UBYTE)CheckShireiOn(); /** 現在のポートの状態を待避 */
#else
		if (IsSHIREIDisable == TRUE){
			NewSHIREI = FALSE;
		}
		else{
			NewSHIREI = (UBYTE)CheckShireiOn(); /** 現在のポートの状態を待避 */
		}
#endif		
		if (OldSHIREI^NewSHIREI) { /** 以前の状態と比較 */
			if (!(--SHIREI_Counter)) { /** チャタリング防止の為のカウンター減算 */
				if (OldSHIREI = NewSHIREI) { /** ポートの状態を登録 */
					switch (NCU_LineStatus & STD_LINE_STATUS) {
					case STD_COM_IN_USE:	/* 標準回線には通信中 */
					case STD_IN_USE:		/* 標準回線には本体使用中 */
						if ( !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
							/* 通信中断していない場合 */
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
							IsSHIREIInStart = TRUE;
						}
						break;
					default:
						switch (NCU_LineStatus & EXT_LINE_STATUS) {
						case EXT_COM_IN_USE:	/* 拡張回線には通信中 */
						case EXT_IN_USE:		/* 拡張回線には本体使用中 */
							if ( !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
								/* 通信中断していない場合 */
								SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
								IsSHIREIInStart = TRUE;
							}
							break;
						default:
							break;
						}
					}
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_SIGNEL_ON;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_IDLE;
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;
					IsSHIREIKido = FALSE;		/* 警察FAX DVT_ID81 Added by SMuratec 李 2005/12/21 */
					IsSHIREIDisable = FALSE;
					
					/* 警察FAX DVT_ID53 Added by SMuratec 夏 2005/12/01
					** 加入側受話器エラーの場合、指令信号印加して、加入側受話器エラーを消去する。
					** 原因：指令モードでは加入側電話OH状態検出しない。
					**       これから、指令モードで従来の電話機戻る方法は無効です。
					**       だから、指令信号印加時に、加入側受話器エラーを消去する。
					*/
					if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP){
						if (Hangup_Line == SYS_LINE_KANYU_HANGUP) {	/** ハング・アップ・エラ－の場合 TBD */
							HungUpCheck = 0; /* ハング・アップ・チェック・クリア */		/*-----------------------------------*/
							SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ハング・アップ・エラ－・クリア */
						}
						Hangup_Line &= ~SYS_LINE_KANYU_HANGUP;
					}
				}
				else {
					if (SYS_MachineStatus[SYS_MACHINE_STATUS]& SYS_FAXCOM) {
						if ( !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
							/* 通信中断していない場合 */
						#if 0	/* 警察FAX DVT41 by SMuratec 夏 2005/11/17 */
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
						#else
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;
						#endif
							IsSHIREIDisable = TRUE;
						}
						OldSHIREI = TRUE;
						
						if (FCM_ShireiKidoWaitFor1stDCS == TRUE) {
							main_msg.Item = FROM_SENSOR; /* 一斉指令受信終了 */
							main_msg.Message = MSG_SHIREI_OFF;
							snd_msg(mbxno.MDM_Task, &main_msg);
						}
					}
					else {
						SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
						SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_SHIREI_SIGNEL_ON);
						SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
						SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;						
						IsSHIREIDisable = FALSE;
					}
				}
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage); /** DS1 ON/OFFﾒｯｾｰｼﾞを送信 */
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				SHIREI_Counter = DETECT_TIME; /** 時間監視ｶｳﾝﾀｰを戻す */
			}
		}
		else {
			/* 履歴２ Modified By SMuratec 李 2005/10/11 */
			if ((tskno_FCM_Task == 0xffff) &&
				((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) &&
				((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) &&
				(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) &&
				!IsSHIREIDisable &&
				IsSHIREIInStart) {
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage); /** DS1 ON/OFFﾒｯｾｰｼﾞを送信 */
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
			IsSHIREIDisable = FALSE;
			SHIREI_Counter = DETECT_TIME;
		}
#endif /* defined (KEISATSU) */
		/***********************************************************************************/
		/* ＤＳ１センサーの監視                                                            */
		/***********************************************************************************/
		NewDS1 = (UBYTE)DS1(); /** 現在のポートの状態を待避 */
		if (OldDS1^NewDS1) { /** 以前の状態と比較 */
			if (!(--DS1_Counter)) { /** チャタリング防止の為のカウンター減算 */
				if (OldDS1 = NewDS1) { /** ポートの状態を登録 */
					SensorTaskMessage.Message = MSG_DS1_ON;
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= SYS_SENSOR_DS1_ON;
				}
				else {
					SensorTaskMessage.Message = MSG_DS1_OFF;
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_DS1_ON);
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage); /** DS1 ON/OFFﾒｯｾｰｼﾞを送信 */
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				DS1_Counter = DETECT_TIME; /** 時間監視ｶｳﾝﾀｰを戻す */
			}
		}
		else {
			DS1_Counter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* ＤＳ２センサーの監視                                                            */
		/***********************************************************************************/
		NewDS2 = (UBYTE)DS2();
		if (OldDS2^NewDS2) {
			if (!(--DS2_Counter)) {
				if (OldDS2 = NewDS2) {
					SensorTaskMessage.Message = MSG_DS2_ON;
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_DS2_ON);
				}
				else {
					SensorTaskMessage.Message = MSG_DS2_OFF;
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_DS2_ON);
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				DS2_Counter = DETECT_TIME;
			}
		}
		else {
			DS2_Counter = DETECT_TIME;
		}
		
#if (PRO_FBS == ENABLE)
		/***********************************************************************************/
		/* ADF許可センサー(APS)の監視                                                      */
		/***********************************************************************************/
		NewAPS = APS();	/** 現在のポートの状態を待避 */
		if (OldAPS^NewAPS) {	/** 以前の状態と比較 */
			if (!(--APS_Counter)) {		/** チャタリング防止の為のカウンター減算 */
				if (OldAPS = NewAPS) {		/** ポートの状態を登録 */
					/** ADF許可(FBSカバークローズ) */
					SensorTaskMessage.Message = MSG_FBS_PRESS_BOAD_CLOSE;
					SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_BOOK_OPEN);
				}
				else {
					/** ADF禁止(FBSカバーオープン) */
					SensorTaskMessage.Message = MSG_FBS_PRESS_BOAD_OPEN;
					SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_BOOK_OPEN);
				}
				/** メインにメッセージを送信して、監視時間を戻す */
				snd_msg( mbxno.MAN_Task, &SensorTaskMessage );
				rcv_msg( mbxno.MAN_SensorTask, &SensorMsg );
				APS_Counter = DETECT_TIME;
			}
		}
		else {
			APS_Counter = DETECT_TIME;		/** 監視時間を戻す */
		}
#endif


#if (PRO_UPPER_COVER == ENABLE)
		/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイドが一体になっているカバーです。
		** 読み取り中にこのカバーを開けられると、読み取りを強制的に終了させます。
		** => ＰＯＰＬＡＲ＿Ｂと同一動作とする。
		** By O.Kimoto 1998/01/17
		*/
		/***********************************************************************************/
		/* ADF許可センサー(APS)の監視                                                      */
		/***********************************************************************************/
		NewAPS = APS();	/** 現在のポートの状態を待避 */
		if (OldAPS^NewAPS) {	/** 以前の状態と比較 */
			if (!(--APS_Counter)) {		/** チャタリング防止の為のカウンター減算 */
				if (OldAPS = NewAPS) {		/** ポートの状態を登録 */
					/** ADF許可(FBSカバークローズ) */
					SensorTaskMessage.Message = MSG_FBS_PRESS_BOAD_CLOSE;
					SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_BOOK_OPEN);
				}
				else {
					/** ADF禁止(FBSカバーオープン) */
					SensorTaskMessage.Message = MSG_FBS_PRESS_BOAD_OPEN;
					SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_BOOK_OPEN);

					/* とりあえず、トップカバーが開けば直ちにプリント停止させる。
					** この場合、必ずジャムすることになるが。。。。
					** By O.Kimoto 1998/03/10
					*/
					if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
						det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
					}

				}
				/** メインにメッセージを送信して、監視時間を戻す */
				snd_msg( mbxno.MAN_Task, &SensorTaskMessage );
				rcv_msg( mbxno.MAN_SensorTask, &SensorMsg );
				APS_Counter = DETECT_TIME;
			}
		}
		else {
			APS_Counter = DETECT_TIME;		/** 監視時間を戻す */
		}
#endif


#if (PRO_PRINT_TYPE == LASER)
		/***********************************************************************************/
		/* プリンタにセットされている記録紙サイズおよび記録紙の有無の監視                  */
		/***********************************************************************************/
		/* 上段カセット                                                                    */
		/***********************************************************************************/
		/*****************************************************************/
		/* ANZU仕様                                                      */
		/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
		/* (注意）上段カセット（トレイ）の見方変更。 					 */
		/*        トレイはNO_CASSETTE状態にはならない。					 */
		/* By S.Kawasaki Jan.18,1996                                     */
		/*****************************************************************/
		/* カセットあり */
		if ((PrinterStatus[PRN_STATUS_21] & PRN_S21_MAIN_TRAY) != PRN_S21_MAIN_TRAY) {		/* 紙なし */
			no_paper_counter1 ++;
			if (no_paper_counter1 > 210) {	/* By H.Y 1994/10/15 100 -> 210 */
				no_paper_counter1 = 211;	/* By H.Y 1994/10/15 101 -> 211 */
				SYS_Paper1Size = SYS_NO_PAPER;
			}
		}
		else {
			no_paper_counter1 = 0;
 #if (PRO_PC_PRINT == DISABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能なし */
			/* 注）ＰＣプリント機能ありでもプリンタオプションボードが未装着の時は、
			**     ＰＣプリント機能なしの時と同じ処理を行うので、変更等を行った場合は、
			**     合わせてプリンタオプションボード未装着の時の所も変更して下さい
			*/
			/* For ANZU By S.K Jan.18,1996 switch (PrinterStatus[PRN_MAIN_CASSETTE_STATUS] & PRN_S_PAPER_SIZE_TEST_DATA) { */
			switch (CHK_UpperManualCassete()) {
			case UPPER_SIZE_NONE:
				SYS_Paper1Size = SYS_NO_PAPER;
				break;
			case UPPER_SIZE_A4:
				SYS_Paper1Size = SYS_A4_PAPER;
				break;
			case UPPER_SIZE_LETTER:
				SYS_Paper1Size = SYS_LT_PAPER;
				break;
			case UPPER_SIZE_B4:
				SYS_Paper1Size = SYS_B4_PAPER;
				break;
			case UPPER_SIZE_LEGAL:
				SYS_Paper1Size = SYS_LG_PAPER;
				break;
			case UPPER_SIZE_F4:
				SYS_Paper1Size = SYS_F4_PAPER;
				break;
			}
 #else							/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能あり 1996/09/18 by K.Watanabe */
			if (DPR_CheckOptionPrintBoardExist()/*DPR_PCR_Enable By J.Miyazaki 1997/01/14 */) {
			/*	SYS_Paper1Size = (UBYTE)(CHK_PCR_UpperManualCassete() - 1);	By M.Tachibana 1997/06/30 */
				SYS_Paper1Size = (UBYTE)(CHK_PCR_ManualCassetteSize() - 1);
			}
			else {					/** プリンタオプションボードが未装着の時 1996/10/08 by K.Watanabe*/
			/* プリンタオプションボードが未装着の時は、通常の記録紙サイズ設定の時と同じです */
				switch (CHK_UpperManualCassete()) {
				case UPPER_SIZE_NONE:
					SYS_Paper1Size = SYS_NO_PAPER;
					break;
				case UPPER_SIZE_A4:
					SYS_Paper1Size = SYS_A4_PAPER;
					break;
				case UPPER_SIZE_LETTER:
					SYS_Paper1Size = SYS_LT_PAPER;
					break;
				case UPPER_SIZE_B4:
					SYS_Paper1Size = SYS_B4_PAPER;
					break;
				case UPPER_SIZE_LEGAL:
					SYS_Paper1Size = SYS_LG_PAPER;
					break;
				case UPPER_SIZE_F4:
					SYS_Paper1Size = SYS_F4_PAPER;
					break;
				}
			}
 #endif
		}
		/***********************************************************************************/
		/* 下段カセット                                                                    */
		/***********************************************************************************/
		if (!(PrinterStatus[PRN_STATUS_18] & PRN_S18_AUX_TRAY)) { /** 下段給紙部ユニット無し */
			SYS_SecondCassetteFlag = 0;	/** 下段カセット部無し */
			SYS_Paper2Size = SYS_NO_PAPER;
		}
		else {
			SYS_SecondCassetteFlag = 1;	/** 下段カセット部有り */
			/*****************************************************************/
			/* ANZU仕様                                                      */
			/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
			/* By S.Kawasaki Jan.18,1996                                     */
			/*****************************************************************/
			if ((PrinterStatus[PRN_AUX_CASSETTE_STATUS] & PRN_S_PAPER_SIZE_TEST_DATA) == PAPER_NO_CASSETTE) {	/* カセットなし */
				no_paper_counter2 = 0;
				SYS_Paper2Size = SYS_NO_CASSETTE;
			}
			else {
				if ((PrinterStatus[PRN_STATUS_21] & PRN_S21_AUX_TRAY) != PRN_S21_AUX_TRAY) {			/* 紙なし */
					no_paper_counter2 ++;
					if (no_paper_counter2 > 210) {	/* By H.Y 1994/10/15 100 -> 210 */
						no_paper_counter2 = 211;	/* By H.Y 1994/10/15 101 -> 211 */
						SYS_Paper2Size = SYS_NO_PAPER;
					}
				}
				else {																				/* 紙あり */
					no_paper_counter2 = 0;
					switch (PrinterStatus[PRN_AUX_CASSETTE_STATUS] & PRN_S_PAPER_SIZE_TEST_DATA) {
					case PAPER_A4_PORTRATE:
						SYS_Paper2Size = SYS_A4_PAPER;
						break;
					case PAPER_LETTER_PORTRATE:
						SYS_Paper2Size = SYS_LT_PAPER;
						break;
					}
				}
			}
		}
#endif
#if (PRO_PRINT_TYPE == LED)
		/***********************************************************************************/
		/* プリンタにセットされている記録紙サイズおよび記録紙の有無の監視                  */
		/***********************************************************************************/
		wk_paper_size1 = AD_Cassette(SYS_1ST_CASSETTE);
		wk_paper_size2 = AD_Cassette(SYS_2ND_CASSETTE);
		wk_paper_size3 = AD_Cassette(SYS_3RD_CASSETTE);

		MAN_CheckAD_CassetteData(&wk_paper_size1, &old_paper_size1, &paper_size1, &size_counter1);
		MAN_CheckAD_CassetteData(&wk_paper_size2, &old_paper_size2, &paper_size2, &size_counter2);
		MAN_CheckAD_CassetteData(&wk_paper_size3, &old_paper_size3, &paper_size3, &size_counter3);

		PRN_Paper1SizeData = paper_size1;
		PRN_Paper2SizeData = paper_size2;
		PRN_Paper3SizeData = paper_size3;

		if (PRN_SizeNoCheckTimer) {
			PRN_SizeNoCheckTimer--;
		}
		if (PRN_SizeNoCheckTimer == 0) {
			/***********************************************************************************/
			/* １段カセット                                                                    */
			/***********************************************************************************/
			paper_size = PRN_CheckPaperSize(PRN_1ST_CASSETTE);
			/*-------------------------------------------------------+-------------------
			**	サイドカバー
			*/
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_JAM_OPEN) {
				if (paper_size != SYS_SIDE_COVER_OPEN) {
					/* サイドカバー・オープン -> クローズ */
					SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_JAM_OPEN;
					SensorTaskMessage.Message = MSG_JAM_COVER_CLOSE;	/* TBD */
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				}
			}
			else {
				if (paper_size == SYS_SIDE_COVER_OPEN) {
					/* サイドカバー・クローズ -> オープン */
					SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_JAM_OPEN;
					if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
						det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
					}
					SensorTaskMessage.Message = MSG_JAM_COVER_OPEN;	/* TBD */
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				}
			}

#if defined(POPLAR_F)
			/* 2000/02/29 Y.Murata
			 * サイドカバー１を、カチャカチャON/OFFすると一瞬記録紙無LEDで点灯する。
			 * カセット１だけは、カバーオープンが返ってきてもSYS_Paper1Size にSYS_NO_PAPERをセットしません
			*/
			if (paper_size == SYS_NO_UNIT) {
				SYS_Paper1Size = SYS_NO_PAPER;
			}
			else if (paper_size == SYS_SIDE_COVER_OPEN) {
				;	/* Nothing */
			}
			else {
				SYS_Paper1Size = paper_size;
			}
#else
			if ((paper_size == SYS_NO_UNIT) || (paper_size == SYS_SIDE_COVER_OPEN)) {
				SYS_Paper1Size = SYS_NO_PAPER;
			}
			else {
				SYS_Paper1Size = paper_size;
			}
#endif

			/***********************************************************************************/
			/* ２段カセット                                                                    */
			/***********************************************************************************/
			if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT) {
				paper_size = PRN_CheckPaperSize(PRN_2ND_CASSETTE);
			/*	unit2 = paper_size;*/
				/*-------------------------------------------------------+-------------------
				**	サイドカバー
				*/
				if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_2JAM_OPEN) {
					if (paper_size != SYS_SIDE_COVER_OPEN) {
						/* サイドカバー・オープン -> クローズ */
						SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_2JAM_OPEN;
						SensorTaskMessage.Message = MSG_JAM_COVER_CLOSE;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
				}
				else {
					if (paper_size == SYS_SIDE_COVER_OPEN) {
						/* サイドカバー・クローズ -> オープン */
						SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_2JAM_OPEN;
						if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
							det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
						}
						SensorTaskMessage.Message = MSG_JAM_COVER_OPEN;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
				}
				if ((paper_size == SYS_NO_UNIT) || (paper_size == SYS_SIDE_COVER_OPEN)) {
					SYS_Paper2Size = SYS_NO_PAPER;
				}
				else {
					SYS_Paper2Size = paper_size;
				}
			}

			/***********************************************************************************/
			/* ３段カセット                                                                    */
			/***********************************************************************************/
			if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT) {
				paper_size = PRN_CheckPaperSize(PRN_3RD_CASSETTE);
			/*	unit3 = paper_size;*/
				/*-------------------------------------------------------+-------------------
				**	サイドカバー
				*/
				if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_3JAM_OPEN) {
					if (paper_size != SYS_SIDE_COVER_OPEN) {
						/* サイドカバー・オープン -> クローズ */
						SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_3JAM_OPEN;
						SensorTaskMessage.Message = MSG_JAM_COVER_CLOSE;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
				}
				else {
					if (paper_size == SYS_SIDE_COVER_OPEN) {
						/* サイドカバー・クローズ -> オープン */
						SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_3JAM_OPEN;
						if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
							det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
						}
						SensorTaskMessage.Message = MSG_JAM_COVER_OPEN;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
				}
				if ((paper_size == SYS_NO_UNIT) || (paper_size == SYS_SIDE_COVER_OPEN)) {
					SYS_Paper3Size = SYS_NO_PAPER;
				}
				else {
					SYS_Paper3Size = paper_size;
				}
			}
		}
		/***********************************************************************************/
		/* ユニット                                                                        */
		/***********************************************************************************/
#if (0)	/* By M.Tachibana 1997/10/10 */
//		if ((unit2 == SYS_NO_UNIT) && (unit3 == SYS_NO_UNIT)) {
//			SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] = SYS_1ST_UNIT;
//		}
//		else if (unit3 == SYS_NO_UNIT) {
//			SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] = (SYS_1ST_UNIT | SYS_2ND_UNIT);
//		}
//		else {
//			SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] = (SYS_1ST_UNIT | SYS_2ND_UNIT | SYS_3RD_UNIT);
//		}
#endif

		/***********************************************************************************/
		/* ＰＳＳセンサーの監視                                                            */
		/* チャタリングを見る必要なし                                                      */
		/* 精度を上げるには１０ｍｓタイマの中で見る                                        */
		/***********************************************************************************/
		NewPSS = PSS();
		if (OldPSS^NewPSS) {
			if (!(--PSS_Counter)) {
				if (OldPSS = NewPSS) {
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PSS_ON);
				}
				else {
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PSS_ON);
				}
				PSS_Counter = DETECT_TIME;
			}
		}
		else {
			PSS_Counter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* ＰＤＳセンサーの監視                                                            */
		/***********************************************************************************/
		NewPDS = PDS();
		if (OldPDS^NewPDS) {
			if (!(--PDS_Counter)) {
				if (OldPDS = NewPDS) {
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PDS_ON);
					PrinterStatus[PRN_STATUS_6] |= PRN_S6_PDS_ON;
					det_evt(EVT_PRN_PAPER_SENSOR);	/* イメージプリント用 */
					det_evt(EVT_PRN_PDS_ON);		/* リストプリント用   */
				}
				else {
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PDS_ON);
					PrinterStatus[PRN_STATUS_6] |= PRN_S6_PDS_OFF;
					det_evt(EVT_PRN_PAPER_SENSOR);	/* イメージプリント用 */
					det_evt(EVT_PRN_PDS_OFF);		/* リストプリント用   */
				}
				PDS_Counter = DETECT_TIME;
			}
		}
		else {
			PDS_Counter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* ＨＰＥＳセンサーの監視                                                          */
		/***********************************************************************************/
		NewHPES = HPES();
		if (OldHPES^NewHPES) {
			if (!(--HPES_Counter)) {
				if (OldHPES = NewHPES) {
					SensorTaskMessage.Message = MSG_HPES_ON;
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_HPES_ON);
				}
				else {
					SensorTaskMessage.Message = MSG_HPES_OFF;
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_HPES_ON);
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				HPES_Counter = DETECT_TIME;
			}
		}
		else {
			HPES_Counter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* ドラムユニットの監視                                                            */
		/***********************************************************************************/
		NewDrumSw = DrumStatus();
		if (OldDrumSw^NewDrumSw) {
			if (!(--DrumSwCounter)) {
				SYS_DrumUnitStatus = OldDrumSw = NewDrumSw;
				DrumSwCounter = DETECT_TIME;
			}
		}
		else {
			DrumSwCounter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* モーターロックの監視                                                            */
		/***********************************************************************************/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_MOTOR_ABNORMAL) {
			if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_MOTOR_ABNORMAL)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~(SYS_PRINTER_MOTOR_ABNORMAL);
				SYB_PrinterLifeMonitor.ErrorStatus &= ~SYS_RX_MOTOR_TROUBLE;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		if (SYS_MotorLockCheckStart == 1) {
			NewMotorLock = MotorLock();
			if (NewMotorLock && (RXIL() == 0)) {	/* RXILの条件追加 By M.Tachibana 1998/01/07 */
				if (!(--MotorLockCounter)) {
					if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_MOTOR_ABNORMAL)) {
						PrinterStatus[PRN_STATUS_4] |= PRN_S4_MOTOR_ABNORMAL;
						SYS_MachineStatus[SYS_PRINTER_STATUS3] |= (SYS_PRINTER_MOTOR_ABNORMAL);
						SYB_PrinterLifeMonitor.ErrorStatus |= SYS_RX_MOTOR_TROUBLE;
						SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
					MotorLockCounter = DETECT_TIME;
				}
#if !defined(SATSUKI2)	/* ＲＸインターロック廃止の為、削除 by Y.Kano 2003/07/03 */
			}
			else {
				MotorLockCounter = DETECT_TIME;
			}
#endif
		}
		else {
			MotorLockCounter = DETECT_TIME;
		}
		/***********************************************************************************/
		/* 機内冷却ファンモーターロックの監視                                              */
		/***********************************************************************************/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FAN_ABNORMAL) {
			if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_FAN_ABNORMAL)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~(SYS_PRINTER_FAN_ABNORMAL);
				SYB_PrinterLifeMonitor.ErrorStatus &= ~SYS_FAN_MOTOR_TROUBLE;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		if (SYS_FanLockEnableTimer > 0) {
			SYS_FanLockEnableTimer--;
			SYS_FanLockDetectTimer = 0;	/* By M.Tachibana 1998/04/02 */
			if (SYS_FanLockEnableTimer == 0) {
				SYS_FanLockDetectTimer = 300;
			}
		}
		if (SYS_FanLockDetectTimer > 0) {
			SYS_FanLockDetectTimer--;
		}
		if (CheckFanMotorLockEnable() && (SYS_FanLockDetectTimer > 0)) {
#if(0)
//#if defined(POPLAR_H) && defined(JP0)/*V851 機内FANエラー調査 By Y.Suzuki 2002/09/11*/
//			if(SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
//				ChkFanMotorLock();
//			}
#endif
			NewFanLock = FanMotorLock();
			if (NewFanLock && (RXIL() == 0)) {	/* RXILの条件追加 By M.Tachibana 1998/01/17 */
#if defined(POPLAR_H) && defined(JP0)/*V851 機内FANエラー調査 By Y.Suzuki 2002/09/21 */
				if(SYB_MaintenanceSwitch[MNT_SW_F0] & 0x04) {
					/*ﾎﾟｰﾄをhighにする。*/
					ChkFanMotorLock();
				}
#endif
				if (!(--FanLockCounter)) {
					if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FAN_ABNORMAL)) {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2003/06/23 */
				/*	if (!(--FanLockDetectionTimes)) [@* RDC 200300268 FAN LOCK 検出回数5回にする V851 By Y.Suzuki 2003/06/23 */
#endif

#if defined(POPLAR_H) && defined(JP0)/*V851 機内FANエラー調査 By Y.Suzuki 2002/09/21 */
						if(SYB_MaintenanceSwitch[MNT_SW_F0] & 0x08) {
							/*ﾎﾟｰﾄをhighにする。*/
							ChkFanMotorLock();
						}
#endif
						PrinterStatus[PRN_STATUS_4] |= PRN_S4_FAN_ABNORMAL;
						SYS_MachineStatus[SYS_PRINTER_STATUS3] |= (SYS_PRINTER_FAN_ABNORMAL);
						SYB_PrinterLifeMonitor.ErrorStatus |= SYS_FAN_MOTOR_TROUBLE;
						SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);

#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2003/06/23 */
					/*	FanLockDetectionTimes = 6;@* RDC 200300268 FAN LOCK 検出回数5回にする V851 By Y.Suzuki 2003/06/23 */
				/*	]*/
#endif
					}
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
					if (long_detect_time) {
						FanLockCounter = DETECT_TIME_LONG;
					}
					else {
						FanLockCounter = DETECT_TIME;
					}
				/*	FanLockDetectionTimes = 6;@* RDC 200300268 FAN LOCK 検出回数5回にする V851 By Y.Suzuki 2003/06/23 */
#else
					FanLockCounter = DETECT_TIME;
#endif
				}
			}
			else {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
				if (long_detect_time) {
					FanLockCounter = DETECT_TIME_LONG;
				}
				else {
					FanLockCounter = DETECT_TIME;
				}
#else
				FanLockCounter = DETECT_TIME;
#endif
			}
		}
		else {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
			if (long_detect_time) {
				FanLockCounter = DETECT_TIME_LONG;
			}
			else {
				FanLockCounter = DETECT_TIME;
			}
#else
			FanLockCounter = DETECT_TIME;
#endif
			SYS_FanLockDetectTimer = 0;	/* By M.Tachibana 1998/04/06 */
		}
		/***********************************************************************************/
		/* 電源冷却ファンモーターロックの監視                                              */
		/***********************************************************************************/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_PS_FAN_ABNORMAL) {
			if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_PS_FAN_ABNORMAL)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~(SYS_PRINTER_PS_FAN_ABNORMAL);
				SYB_PrinterLifeMonitor.ErrorStatus &= ~SYS_PS_FAN_MOTOR_TROUBLE;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		if (SYS_PsFanLockEnableTimer > 0) {
			SYS_PsFanLockEnableTimer--;
			SYS_PsFanLockDetectTimer = 0;	/* By M.Tachibana 1998/04/02 */
			if (SYS_PsFanLockEnableTimer == 0) {
				SYS_PsFanLockDetectTimer = 300;
			}
		}
		if (SYS_PsFanLockDetectTimer > 0) {
			SYS_PsFanLockDetectTimer--;
		}
		if (CheckPsFanMotorLockEnable() && (SYS_PsFanLockDetectTimer > 0)) {
			NewPsFanLock = PsFanMotorLock();
			if (NewPsFanLock && (RXIL() == 0)) {	/* RXILの条件追加 By M.Tachibana 1998/01/17 */
				if (!(--PsFanLockCounter)) {
					if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_PS_FAN_ABNORMAL)) {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2003/06/23 */
				/*	if (!(--FanLockDetectionTimes)) [@* RDC 200300268 FAN LOCK 検出回数5回にする V851 By Y.Suzuki 2003/06/23 */
#endif
						PrinterStatus[PRN_STATUS_4] |= PRN_S4_PS_FAN_ABNORMAL;
						SYS_MachineStatus[SYS_PRINTER_STATUS3] |= (SYS_PRINTER_PS_FAN_ABNORMAL);
						SYB_PrinterLifeMonitor.ErrorStatus |= SYS_PS_FAN_MOTOR_TROUBLE;
						SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2003/06/23 */
					/*	FanLockDetectionTimes = 6;@* RDC 200300268 FAN LOCK 検出回数5回にする V851 By Y.Suzuki 2003/06/23 */
				/*	]*/
#endif
					}
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
					if (long_detect_time) {
						PsFanLockCounter = DETECT_TIME_LONG;
					}
					else {
						PsFanLockCounter = DETECT_TIME;
					}
#else
					PsFanLockCounter = DETECT_TIME;
#endif
				}
			}
			else {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
				if (long_detect_time) {
					PsFanLockCounter = DETECT_TIME_LONG;
				}
				else {
					PsFanLockCounter = DETECT_TIME;
				}
#else
				PsFanLockCounter = DETECT_TIME;
#endif
			}
		}
		else {
#if (PRO_FANLOCK_DETECT_TIME == ENABLE)/*V851 機内FANｴﾗｰ対策 By Y.Suzuki 2002/09/26 */
			if (long_detect_time) {
				PsFanLockCounter = DETECT_TIME_LONG;
			}
			else {
				PsFanLockCounter = DETECT_TIME;
			}
#else
			PsFanLockCounter = DETECT_TIME;
#endif
			SYS_PsFanLockDetectTimer = 0;	/* By M.Tachibana 1998/04/06 */
		}
		/***********************************************************************************/
		/* 高圧ヒューズの監視                                                              */
		/***********************************************************************************/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_HV_FUSE_ERROR) {
			if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_HV_FUSE_ABNORMAL)) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~SYS_PRINTER_HV_FUSE_ERROR;
				SYB_PrinterLifeMonitor.ErrorStatus &= ~SYS_HV_FUSE_DISCONNECT;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)	/** プリンタ使用中なら */
			 && (HV24V()) && (RXIL() == 0)) {
				if (!(--HvFuseCounter)) {	/* カウンタの追加 by M.Tachibana 1998/01/22 */
					PrinterStatus[PRN_STATUS_4] |= PRN_S4_HV_FUSE_ABNORMAL;
					HvFuseCounter = DETECT_TIME;
				}
			}
			else {
				HvFuseCounter = DETECT_TIME;
			}
			if (PrinterStatus[PRN_STATUS_4] & PRN_S4_HV_FUSE_ABNORMAL) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_HV_FUSE_ERROR;
				SYB_PrinterLifeMonitor.ErrorStatus |= SYS_HV_FUSE_DISCONNECT;
				if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
					det_evt(EVT_PRN_PRINTER_ERROR);
				}
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
#endif

		/***********************************************************************************/
		/* プリンター関連センサーの監視                                                    */
		/***********************************************************************************/
		MAN_CheckPrinterSensor();


#if (PRO_PAPER_TYPE == ROLL_PAPER)
#if (PRO_PRINT_TYPE == THERMAL_TRANS) /* SAKAKI */
		/***********************************************************************************/
		/* ＰＢ４センサーの監視                                                            */
		/* メイン・タスクへの通知はしない                                                  */
		/***********************************************************************************/
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {	/* プリンターが使用中でなければ */
			NewPB4 = (UBYTE)PB4();
			if (OldPB4^NewPB4) {
				if (!(--PB4_Counter)) {
					if (OldPB4 = NewPB4) {
						SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PB4_ON);
						SYS_Paper1Size = SYS_B4_PAPER;
					}
					else {
						SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PB4_ON);
						SYS_Paper1Size = SYS_A4_PAPER;
					}
					PB4_Counter = DETECT_TIME;
				}
			}
			else {
				PB4_Counter = DETECT_TIME;
			}
		}
#else /*HINOKI*/
		/***********************************************************************************/
		/* ＰＢ４センサーの監視                                                            */
		/* メイン・タスクへの通知はしない                                                  */
		/***********************************************************************************/
		NewPB4 = (UBYTE)PB4();
		if (OldPB4^NewPB4) {
			if (!(--PB4_Counter)) {
				if (OldPB4 = NewPB4) {
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PB4_ON);
					SYS_Paper1Size = SYS_B4_PAPER;
				}
				else {
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PB4_ON);
					SYS_Paper1Size = SYS_A4_PAPER;
				}
				PB4_Counter = DETECT_TIME;
			}
		}
		else {
			PB4_Counter = DETECT_TIME;
		}
#endif
#endif
		/***********************************************************************************/
		/* スキャナー・カバー センサーの監視                                               */
		/***********************************************************************************/
#if (PRO_SEPERATE_INTER_LOCK == ENABLE)
		NewTXIL = (UBYTE)TXIL();
		if (OldTXIL^NewTXIL) {	/** スキャナー・カバーの開－＞閉又は閉－＞開があった。 */
			if (!(--TXIL_Counter)) {
				if (OldTXIL = NewTXIL) {	/** スキャナー・カバー・オープン */
					SensorTaskMessage.Message = MSG_SCANNER_COVER_OPEN;
					SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_SCANNER_OPEN;	/* スキャナカバーオープン*/
	
 #if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
  #if (0) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
//					MAN_ChangeEcoMode(0);
  #endif
 #endif
				}
				else {	/** スキャナー・カバー・クローズ */
					SensorTaskMessage.Message = MSG_SCANNER_COVER_CLOSE;
					SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_SCANNER_OPEN;	/* スキャナカバークローズ*/
	
		#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* DVT修正： JamRecover時 SCNカーバー中原稿をやり直してください by SMuratec 夏 2004/08/18 */
					if (SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS2_ON) {
						SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
					}
		#endif
		
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				TXIL_Counter = DETECT_TIME;
			}
		}
		else {
			TXIL_Counter = DETECT_TIME;
		}
#endif

#if (PRO_PAPER_TYPE == ROLL_PAPER ) 	/* TBD */
		/***********************************************************************************/
		/* PS1 ｾﾝｻｰの監視                                                          		   */
		/***********************************************************************************/
		/*---------------------------------------------------------------------------------*/
		/** 椛の記録紙有り／無しの監視は待機中のみ行います。                               */
		/** 印字中に記録紙の監視を行うと、記録紙を引き戻した際に紙無し状態となる為。       */
		/** Sep.7,1994 By S.K                                                              */
		/*---------------------------------------------------------------------------------*/
 #if (PRO_ECO_MODE == ENABLE) /* 2002/10/04 By M.Maeda */
		if (SYS_EcoModeStatus == ECO_MODE_OFF) {
 #endif
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {  /** プリンターが使用中でなければ */
			NewPS1 = (unsigned char)PS1();
			if (OldPS1^NewPS1) {
				if (!(--PS1_Counter)) {
					if (OldPS1 = NewPS1) {
						SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PS1_ON); /** PS1 センサ－ON */
						SensorTaskMessage.Message = MSG_PAPER_EXIST;
					}
					else {
						SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PS1_ON); /** PS1 センサ－OFF */
						SensorTaskMessage.Message = MSG_PAPER_NOT_EXIST;
					}
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					PS1_Counter = DETECT_TIME;
				}
			}
			else {
				PS1_Counter = DETECT_TIME;
			}
		}
 #if (PRO_ECO_MODE == ENABLE) /* 2002/10/04 By M.Maeda */
		}
 #endif
#endif

		/***********************************************************************************/
		/* プリンター・カバー センサーの監視                                                          */
		/***********************************************************************************/
#if (PRO_SEPERATE_INTER_LOCK == ENABLE)
  #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) /* MOMIJI/SAKAKI */
		NewRXIL = (unsigned char)RXIL();
		if (OldRXIL^NewRXIL) { /** プリンター・カバーの開－＞閉又は閉－＞開があった。 */
			if (!(--RXIL_Counter)) {
				if (OldRXIL = NewRXIL) { /** プリンター・カバー・オープン */
	#if (PRO_ECO_MODE == ENABLE) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
					MAN_ChangeEcoMode(2);
	#endif
					SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;
    #if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* DVT修正：原稿蓄積中にはカバーステータスにスキャナーとプリンターオープンステータスを同時に設定 by SMuratec 李 2004/08/17 */
					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
						OldTXIL = TRUE;
						TXIL_Counter = DETECT_TIME;
						SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN);
						SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
					}
					else {
						SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;/* プリンターカバーオープン*/
					}
	#else /* (PRO_PAPER_TYPE != CUT_PAPER) || !defined(STOCKHM2) */
					SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;/* プリンターカバーオープン*/
	#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
    #if (PRO_PRINT_TYPE == THERMAL)
					AD_PS2_Value = 1;	/* 初期値紙あり 1999/04/13 by T.Soneoka */
    #endif

	#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
     #if (0) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
//					MAN_ChangeEcoMode(0);
     #endif
	#endif
				}
				else { /** スキャナー・カバー・クローズ */
	#if (PRO_ECO_MODE == ENABLE)  /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
					MAN_ChangeEcoMode(3);
	#endif
					SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;
					/*-----------------------------------------------------
					** プリンタカバークローズしたときに、ここでMachineStatusをOFFし、
					** MainTaskで、イニシャルカット処理の前にプリントを起動してしまうことがあるので、
					** MachineStatusをOFFするのは、MainTaskで行うようにします。
					** 1998/12/04 H.Yoshikawa
					*/
/*					SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_PRINTER_OPEN; 1998/12/04 H.Yoshikawa *//* プリンターカバークローズ*/
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				/*---------------------------------------------------------
				** ＜「カバークローズ時に記録紙なしのためにイニシャルカットせず」対策＞
				** カバーオープン→クローズ時には、RXIL_Counter = RXIL_DETECT_TIME;とし、
				** ＜「カバーオープン時に記録紙なしアラームが鳴動する」対策＞
				** カバークローズ→オープン時は、RXIL_Counter = DETECT_TIME;とする
				** 1999/02/09 H.Yoshikawa
				*/
				if (NewRXIL) {
					RXIL_Counter = RXIL_DETECT_TIME;	/* 1999/01/28 H.Yoshikawa */
				}
				else {
					RXIL_Counter = DETECT_TIME;			/* 1999/02/09 H.Yoshikawa */
				}
			}
		}
		else {
			/*---------------------------------------------------------
			** ＜「カバークローズ時に記録紙なしのためにイニシャルカットせず」対策＞
			** カバーオープン→クローズ時には、RXIL_Counter = RXIL_DETECT_TIME;とし、
			** ＜「カバーオープン時に記録紙なしアラームが鳴動する」対策＞
			** カバークローズ→オープン時は、RXIL_Counter = DETECT_TIME;とする
			** 1999/02/09 H.Yoshikawa
			*/
			if (NewRXIL) {
				RXIL_Counter = RXIL_DETECT_TIME;	/* 1999/01/28 H.Yoshikawa */
			}
			else {
				RXIL_Counter = DETECT_TIME;			/* 1999/02/09 H.Yoshikawa */
			}
		}
 #endif

 #if (PRO_PRINT_TYPE == LED)
		NewRXIL = (UBYTE)RXIL();
		if (OldRXIL^NewRXIL) {	/** プリンター・カバーの開－＞閉又は閉－＞開があった。 */
			if (!(--RXIL_Counter)) {
				if (OldRXIL = NewRXIL) {	/** プリンター・カバー・オープン */
					SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;
					SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;	/* プリンターカバーオープン*/
					if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
						det_evt(EVT_PRN_PRINTER_ERROR);									/** JAM発生イベント発行 */
					}
				}
				else {	/** プリンター・カバー・クローズ */
					SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;
					SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_PRINTER_OPEN;	/* プリンターカバークローズ*/
#if (PRO_FBS == ENABLE)
					/* RXIL瞬断対策 T.Nose 1998/03/03 */
					SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_MOMENT_TOP_COVER_OPEN;
#endif
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				RXIL_Counter = DETECT_TIME;
			}
		}
		else {
			RXIL_Counter = DETECT_TIME;
		}
 #endif
#endif
#if (PRO_SEPERATE_INTER_LOCK == DISABLE)
 #if defined (SATSUKI2) || defined(STOCKHM2)
		NewInterLock = (UBYTE)TXIL();
 #else
		NewInterLock = (UBYTE)InterLock();
 #endif
		if (OldInterLock^NewInterLock) {
			if (!(--InterLockCounter)) {
				if (OldInterLock = NewInterLock) {
	#if (PRO_ECO_MODE == ENABLE) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
					MAN_ChangeEcoMode(2);
	#endif
					SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;
    #if defined(SATSUKI2)	/* カバーステータスにスキャナーとプリンターオープンステータスを同時に設定 by Y.Kano 2003/07/01 */
					SYS_MachineStatus[SYS_COVER_STATUS] |= (SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN);
    #endif

    #if (PRO_PRINT_TYPE == THERMAL)
					AD_PS2_Value = 1;	/* 初期値紙あり 1999/04/13 by T.Soneoka */
    #endif
				}
				else {
	#if (PRO_ECO_MODE == ENABLE)  /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
					MAN_ChangeEcoMode(3);
	#endif
					SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;
					/*-----------------------------------------------------
					** プリンタカバークローズしたときに、ここでMachineStatusをOFFし、
					** MainTaskで、イニシャルカット処理の前にプリントを起動してしまうことがあるので、
					** MachineStatusをOFFするのは、MainTaskで行うようにします。
					** 1998/12/04 H.Yoshikawa
					*/
					/* SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN); */
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				InterLockCounter = DETECT_TIME;
			}
		}
		else {
			InterLockCounter = DETECT_TIME;
		}
#endif

#if (PRO_DIALIN == ENABLE)/* && !defined(SATSUKI2) 復活します。O.Oshima 2003/10/31 *//* SATSUKI2は待機モードでダイヤルイン待機を持ちます。O.Oshima 2003/06/25 */
		/***********************************************************************************/
		/* ダイアル・イン・スイッチの監視                                                  */
		/***********************************************************************************/
		NewDialIn = (UBYTE)DialIn();
		if (OldDialIn^NewDialIn) {
			if (!(--DialInCounter)) {
				if (OldDialIn = NewDialIn) {
					SensorTaskMessage.Message = MSG_DIAL_IN_ON;
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_DIAL_IN_ON);
					SYB_SettingStatus[SETTING_STATUS_3] |= DIAL_IN_ON;
				}
				else {
					SensorTaskMessage.Message = MSG_DIAL_IN_OFF;
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_DIAL_IN_ON);
					SYB_SettingStatus[SETTING_STATUS_3] &= ~DIAL_IN_ON;
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				DialInCounter = DETECT_TIME;
			}
		}
		else {
			DialInCounter = DETECT_TIME;
		}
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
		/***********************************************************************************/
		/* スクランブル・スイッチの監視                                                    */
		/***********************************************************************************/
		NewScrambleOn = CheckScrambleSwOn();
		if (OldScrambleOn^NewScrambleOn) {
			if (!(--scramble_on_counter)) {
				if ((OldScrambleOn = NewScrambleOn) == TRUE) {
					SensorTaskMessage.Message = MSG_SCRAMBLE_ON;
					SYS_MachineStatus[SYS_SENSOR_STATUS] |= SYS_SCRAMBLE_ON;
				}
				else {
					SensorTaskMessage.Message = MSG_SCRAMBLE_OFF;
					SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~SYS_SCRAMBLE_ON;
				}
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				scramble_on_counter = DETECT_TIME;
			}
		}
		else {
			scramble_on_counter = DETECT_TIME;
		}
		
		/***********************************************************************************/
		/* S1エラーの監視                                                                  */
		/***********************************************************************************/
		if ((CheckS1Error() == TRUE) && (CHK_IgnoreS1Error() == FALSE)) {
			SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_S1;
			if (s1_error_prev == FALSE) {
				SensorTaskMessage.Message = MSG_S1_ERROR_ON;
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
			s1_error_prev = TRUE;
		}
		else {
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_S1;
			if (s1_error_prev == TRUE) {
				SensorTaskMessage.Message = MSG_S1_ERROR_OFF;
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
			s1_error_prev = FALSE;
		}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
		/***********************************************************************************/
		/* リボン（ドナー・フィルム）の監視                                                */
		/***********************************************************************************/
 #if (PRO_ECO_MODE == ENABLE) /* 2002/10/04 By M.Maeda */
		if (SYS_EcoModeStatus == ECO_MODE_OFF) {
 #endif
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {  /** プリンターが使用中でなければ *//* 1998/11/25 H.Yoshikawa */
			NewRibon = (UBYTE)RIBON();
			if (OldRibon^NewRibon) {
				if (!(--RibonCounter)) {
					if (OldRibon = NewRibon) {
						SensorTaskMessage.Message = MSG_RIBON_EXIST;
						SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_INK);
					}
					else {
						SensorTaskMessage.Message = MSG_RIBON_NOT_EXIST;
						SYS_MachineStatus[SYS_PRINTER_STATUS1] |= (SYS_PRINTER_NO_INK);
					}

					/*---------------------------------------------------------
					** リボン交換エラー表示時にアラームが鳴ったり、鳴らない件
					** プリンタ使用中の場合のみ、MANにメッセージを送出しないようにしているが、
					** SYS_MachineStatusには値を書き込んでいます。
					** プリンタ使用中の場合には、これらの処理全体行わないようにします。
					** 1998/11/25 H.Yoshikawa
					*/
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
#if (0)	/* 1998/11/25 H.Yoshikawa */
					if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {	/** プリンターが使用中でなければ */
						snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
						rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
					}
#endif
					RibonCounter = DETECT_TIME;
				}
			}
			else {
				RibonCounter = DETECT_TIME;
			}
		}
 #if (PRO_ECO_MODE == ENABLE) /* 2002/10/04 By M.Maeda */
		}
 #endif
#endif


#if defined(STOCKHM2)/*(PRO_PRINT_TYPE == THERMAL)*/
		/***********************************************************************************/
		/* リボン（ドナー・フィルム）の監視                                                */
		/***********************************************************************************/
#if (0)
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {  /** プリンターが使用中でなければ *//* 1998/11/25 H.Yoshikawa */
#else
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) ||
			Paper.Position != PAPER_POS_PRINTING) { 
#endif
			NewRibon = (UBYTE)RIBON();
			if (OldRibon^NewRibon) {
				if (!(--RibonCounter)) {
					if (OldRibon = NewRibon) {
						SensorTaskMessage.Message = MSG_RIBON_EXIST;
						SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_INK);
					}
					else {
						SensorTaskMessage.Message = MSG_RIBON_NOT_EXIST;
						SYS_MachineStatus[SYS_PRINTER_STATUS1] |= (SYS_PRINTER_NO_INK);
					}

					/*---------------------------------------------------------
					** リボン交換エラー表示時にアラームが鳴ったり、鳴らない件
					** プリンタ使用中の場合のみ、MANにメッセージを送出しないようにしているが、
					** SYS_MachineStatusには値を書き込んでいます。
					** プリンタ使用中の場合には、これらの処理全体行わないようにします。
					** 1998/11/25 H.Yoshikawa
					*/
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);

					RibonCounter = DETECT_TIME;
				}
			}
			else {
				RibonCounter = DETECT_TIME;
			}
		}
#endif

	}
}


/*************************************************************************
	module		:[プリンタ関係のセンサーを初期化する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/23]
	author		:[橘正樹]
*************************************************************************/
void MAN_InitPrinterSensor(void)
{


#if defined(STOCKHM2)
#if (0) /* Modified by SMuratec L.Z.W 2004/06/03  */
	if( OldPS0 = CassettePaper() ){ /** PS0を強制的に紙有り */
#else
	if( OldPS0 = QueryPs0On() ){ /** PS0を強制的に紙有り */
#endif
/*		SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PS1_ON);	*/
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;	/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}
	else {
/*		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PS1_ON);	*/
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;		/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
	}
#endif
	
#if (PRO_PRINT_TYPE == LASER)
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* (注意）下段はオプションであるため見方が変更になる可能性有り。 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	SYS_MachineStatus[SYS_PRINTER_STATUS1] = 0;	/** プリンター関係の初期化はエラー無し */
	SYS_MachineStatus[SYS_PRINTER_STATUS2] = 0;	/** プリンター関係の初期化はエラー無し */
	SYS_MachineStatus[SYS_PRINTER_STATUS3] = 0;	/** プリンター関係の初期化はエラー無し */
	/* 上下段記録紙無しと確定するのが約２秒かかるため、電源ＯＮ後すぐにプリントしようとする場合、その記録紙有無判断までに値がセットされないので、ここでセットします */
	if ((PrinterStatus[PRN_STATUS_21] & PRN_S21_MAIN_TRAY) != PRN_S21_MAIN_TRAY) {		/* 紙なし */
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;	/* 上段記録紙無し */
		SYS_Paper1Size = SYS_NO_PAPER;
	}
	if (SYS_SecondCassetteFlag == 1) { /* By S.Kawasaki 1996/03/15 */
		if ((PrinterStatus[PRN_STATUS_21] & PRN_S21_AUX_TRAY) != PRN_S21_AUX_TRAY) {			/* 紙なし */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER2;	/* 下段記録紙無し */
			SYS_Paper2Size = SYS_NO_PAPER;
		}
	}
	else {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER2;	/* 下段記録紙無し */
		SYS_Paper2Size = SYS_NO_PAPER;
	}

	SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_PRINTER_OPEN+SYS_COVER_CASSETTE1_OPEN+SYS_COVER_CASSETTE2_OPEN); /** プリンター関係の初期化はエラー無し */
#endif	/* PRO_PRINT_TYPE == LASER */

#if (PRO_PRINT_TYPE == LED)
	/*--------------------------------------------------------------------
	** 記録紙サイズ・なし状態
	*/
	PRN_InitPaperSize();

	paper_size1 = AD_Cassette(SYS_1ST_CASSETTE);
	paper_size2 = AD_Cassette(SYS_2ND_CASSETTE);
	paper_size3 = AD_Cassette(SYS_3RD_CASSETTE);
	old_paper_size1 = paper_size1;
	old_paper_size2 = paper_size2;
	old_paper_size3 = paper_size3;
	size_counter1 = DETECT_TIME_CASSETTE;
	size_counter2 = DETECT_TIME_CASSETTE;
	size_counter3 = DETECT_TIME_CASSETTE;

	if (SYS_Paper1Size == SYS_NO_PAPER) {
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
	}
	if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT) {
		if (SYS_Paper2Size == SYS_NO_PAPER) {
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER2;
		}
	}
	if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT) {
		if (SYS_Paper3Size == SYS_NO_PAPER) {
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER3;
		}
	}


	/*--------------------------------------------------------------------
	** 各種センサー状態
	*/
	if (OldPSS = PSS()) {
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PSS_ON);
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PSS_ON);
	}
	if (OldPDS = PDS()) {
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PDS_ON);
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PDS_ON);
	}
	if (OldHPES = HPES()) {
		SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_HPES_ON);
	}
	else {
		SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_HPES_ON);
	}
	OldDrumSw = DrumStatus();
	SYS_DrumUnitStatus = OldDrumSw;
	SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_DRUM);

#if (0)	/* By M.Tachibana 1998/01/26 */
//	OldMotorLock = 0;
//	SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~(SYS_PRINTER_MOTOR_ABNORMAL);
//	OldFanLock = 0;
//	SYS_MachineStatus[SYS_PRINTER_STATUS3] &= ~(SYS_PRINTER_FAN_ABNORMAL);
#endif

#endif	/* PRO_PRINT_TYPE == LED */

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* (DVT修正) Added by SMuratec 李 2004/08/25 */
	/* プリンタ状態退避用変量 */
	print_status1 = 0;
	print_status2 = 0;
	print_status3 = 0;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

}

/*************************************************************************
	module		:[プリンタ関係のセンサーをチェックする]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/23]
	author		:[橘正樹]
*************************************************************************/
void MAN_CheckPrinterSensor(void)
{
	/* V851By Y.Suzuki 2002/09/17 */
	UWORD page_count;

	page_count = 0;
	
#if defined(STOCKHM2)
	/* Modify by SMuratec 李 2004/4/20 */
#if (0) /* Modified by SMuratec L.Z.W 2004/06/03  */
	NewPS0 = (UBYTE)CassettePaper();
#else
	NewPS0 = (UBYTE)QueryPs0On();
#endif
	if (OldPS0^NewPS0) {
		if (OldPS0 = NewPS0) { 
		/*	SYS_MachineStatus[SYS_SENSOR_STATUS] |= (SYS_SENSOR_PS1_ON);*/
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;	/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */
			
			SensorTaskMessage.Message = MSG_PAPER_EXIT;
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
		else {
		/*	SYS_MachineStatus[SYS_SENSOR_STATUS] &= ~(SYS_SENSOR_PS1_ON);*/
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;		/* 1994/06/16 Y.Murata  ﾌﾟﾘﾝﾀｲﾈｰﾌﾞﾙはプリンタステータスでみているため */

			SensorTaskMessage.Message = MSG_PAPER_NOT_EXIT;
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Modify by SMuratec 李 2004/07/07 */
 #if (PRO_PRINT_TYPE == THERMAL) && (PRO_DISPLAY_PRN_INITIALIZE == ENABLE) /* Added by SMuratec 李 2004/7/7 */
/*
	DVT修正：初期化前の状態退避に関して変量が
			 使用しなければならない事。
			 SMuratec 李 2004/08/25 
*/ 
	if ( (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)			/* ｲﾒｰｼﾞ･ﾌﾟﾘﾝﾄ中で、*/
	 && (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL) ) {					/* プリンターの初期化要求です*/
	 	if ( SYS_MachineStatus[SYS_PRINTER_STATUS1] ) {
			print_status1 ^= (print_status1 ^ SYS_MachineStatus[SYS_PRINTER_STATUS1]) ;
#if 0 /* QAT修正：初期化での記録紙無しの変量を退避しない事 by SMuratec 李 2004/11/03 */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] = 0;
#else
			SYS_MachineStatus[SYS_PRINTER_STATUS1] = (print_status1 & SYS_PRINTER_NO_PAPER);
#endif
		}
	 	if ( SYS_MachineStatus[SYS_PRINTER_STATUS2] ) {
			print_status2 ^= (print_status2 ^ SYS_MachineStatus[SYS_PRINTER_STATUS2]);
			SYS_MachineStatus[SYS_PRINTER_STATUS2] = (print_status2 & SYS_PRINTER_HIGH_TEMP);
		}
		
	 	if ( SYS_MachineStatus[SYS_PRINTER_STATUS3] ) {
			print_status3 ^= (print_status3 ^ SYS_MachineStatus[SYS_PRINTER_STATUS3]);
			SYS_MachineStatus[SYS_PRINTER_STATUS3] = 0;
		}
		return;
	}
	else {
		if (print_status1 || print_status2 || print_status3) {
		 	if ( print_status1 ) {
				SYS_MachineStatus[SYS_PRINTER_STATUS1] = print_status1;
				print_status1 = 0;
			}
			
		 	if ( print_status2 ) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] = print_status2;
				print_status2 = 0;
			}
			
		 	if ( print_status3 ) {
				SYS_MachineStatus[SYS_PRINTER_STATUS3] = print_status3;
				print_status3 = 0;
			}
			return;
		}
	}
 #endif
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if (PRO_PRINT_TYPE == LASER)
	/***********************************************************************************/
	/* プリンタ・カバーの監視                                                          */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* （注意）PRN_STATUS_3には紙サイズエラーが含まれているが、		 */
	/*         クリアはしていません。								 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		if (!(PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_COVER_OPEN)) {
			/* カバー・オープン -> クローズ */
			/* センサ・タスクで使用するFlagはここで立てます */
			SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_PRINTER_OPEN;

			/*
			** ジャム発生時のカバーオープン－＞クローズ時にはリセット処理を行う。
			** By S.Kawasaki 1996/07/16
			*/
			SensorTaskMessage.Message = MSG_RESET_PRINTER_COVER_CLOSE;
#if (0) /* By H.Hirao 1996/07/18 */
** 			if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & (SYS_PRINTER_PAPER_JAM | SYS_PRINTER_EXIT_JAM |
** 														  SYS_PRINTER_MISS_FEED_JAM | SYS_PRINTER_REG_JAM)) { /* ペーパージャム発生時 */
** 				SensorTaskMessage.Message = MSG_RESET_PRINTER_COVER_CLOSE;
** 			}
** 			else {
** 				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;
** 			}
#endif
			PRN_ResetMisPrint();	/* By H.Y 1994/08/08 */
			PrinterStatus[PRN_STATUS_3] &= ~PRN_S3_JAM_TEST_DATA;		/** 暫定でJAMｽﾃｰﾀｽをこかします Oct.14,94 */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_COVER_OPEN) {
			/*
			** プリンターカバーが確実に開けられたかをセットする。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			MAN_TopCoverNeedToBeOpenFlag = 0;	/** By S.Kawasaki 1997/05/07 JAM0507 */

			/* カバー・クローズ -> オープン */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
			}
			SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・カセットの監視 (上段)トレイ部                                         */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* トレイ部は常に装着された状態であるため監視を削除します。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
#if (0) /* For ANZU By S.K Jan.18,1996 上段部（トレイ部の監視削除）*/
** 	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE1_OPEN) {
** 		if (SYS_Paper1Size != SYS_NO_CASSETTE) {
** 			/* カセット・オープン -> クローズ */
** 			PRN_CassetteOpenClose = 1;
** 			SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_CASSETTE1_OPEN;
** 			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD  */
** 			PRN_ResetMisPrint();	/* By H.Y 1994/08/08 */
** 			PrinterStatus[PRN_STATUS_3] &= ~PRN_S3_JAM_TEST_DATA;		/** 暫定でJAMｽﾃｰﾀｽをこかします Oct.14,94 */
** 			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
** 			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
** 		}
** 	}
** 	else {
** 		if (SYS_Paper1Size == SYS_NO_CASSETTE) {
** 			/* カセット・クローズ -> オープン */
** 			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
** 				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
** 			}
** 			SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_CASSETTE1_OPEN;
** 			SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;		/* TBD */
** 			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
** 			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
** 		}
** 	}
#endif /* For ANZU By S.K Jan.18,1996 上段部（トレイ部の監視削除）*/
	/***********************************************************************************/
	/* プリンタ・カセットの監視 (下段)                                                 */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* （注意）PRN_STATUS_3には紙サイズエラーが含まれているが、		 */
	/*         クリアはしていません。								 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) {
		if (SYS_Paper2Size != SYS_NO_CASSETTE) {
			/* カセット・オープン -> クローズ */
			PRN_CassetteOpenClose = 1;
			SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_CASSETTE2_OPEN;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD  */
			PRN_ResetMisPrint();	/* By H.Y 1994/08/08 */
			PrinterStatus[PRN_STATUS_3] &= ~PRN_S3_JAM_TEST_DATA;		/** 暫定でJAMｽﾃｰﾀｽをこかします Oct.14,94 */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (SYS_Paper2Size == SYS_NO_CASSETTE) {
			/* カセット・クローズ -> オープン */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
			}
			SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_CASSETTE2_OPEN;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_OPEN;		/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・上段・記録紙の監視                                                    */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* （注意）SYS_MachineStatusは上段／下段の区別無し。			 */
	/*         クリアはしていません。								 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
		if (SYS_Paper1Size != SYS_NO_PAPER) {
			/* 紙なし -> 紙あり */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (SYS_Paper1Size == SYS_NO_PAPER) {
			/* 紙あり -> 紙なし */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・下段・記録紙の監視                                                    */
	/***********************************************************************************/
	if (SYS_SecondCassetteFlag == 1) { /** 下段カセットが装着されている */
		/*****************************************************************/
		/* ANZU仕様                                                      */
		/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
		/* （注意）SYS_MachineStatusは上段／下段の区別無し。			 */
		/*         クリアはしていません。								 */
		/* By S.Kawasaki Jan.18,1996                                     */
		/*****************************************************************/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) {
			if (SYS_Paper2Size != SYS_NO_PAPER) {
				/* 紙なし -> 紙あり */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER2;
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if (SYS_Paper2Size == SYS_NO_PAPER) {
				/* 紙あり -> 紙なし */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER2;
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	else {
		SYS_Paper2Size = SYS_NO_PAPER;
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER2;
	}

	/***********************************************************************************/
	/* プリンタ・記録紙ジャムの監視                                                    */
	/***********************************************************************************/
	/** ジャム関係は、SYS_MachineStatus[SYS_PRINTER_STATUS]の書き換えのみ行います      */
	/** MainTaskにはメッセージは送りません                                             */
	/** プリント中にジャム発生した場合、ジャム解除後にすぐにプリントを再開するために   */
	/** MainTakにメッセージを送ります By H.Y 1994/08/12                                */
	/***********************************************************************************/
	/* 全体のJAM                                                                       */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
		if (!((PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_JAM) == PRN_S1_JAM)) {
			/*
			** プリンターカバーが確実に開けらたかを確認する。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			if (MAN_TopCoverNeedToBeOpenFlag == 1) { /** By S.Kawasaki 1997/05/07 JAM0507 */
				/** まだ開けられていない */
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_PAPER_JAM;		/* JAM解除 */
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask, &SensorMsg);
			}
		}
	} else {
		if ((PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_JAM) == PRN_S1_JAM) {
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
			}
			/*
			** プリンターカバーが確実に開けらる必要があることをセットする。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			MAN_TopCoverNeedToBeOpenFlag = 1;	/** By S.Kawasaki 1997/05/07 JAM0507 */

			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;		/* JAM発生 */
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask, &SensorMsg);
		}
	}
	/***********************************************************************************/
	/* EXIT JAM                                                                        */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_EXIT_JAM) {
		if (!((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_EXIT_JAM)) {
			/*
			** プリンターカバーが確実に開けらたかを確認する。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			if (MAN_TopCoverNeedToBeOpenFlag == 1) { /** By S.Kawasaki 1997/05/07 JAM0507 */
				/** まだ開けられていない */
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_EXIT_JAM;		/* JAM解除 */
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	else {
		if ((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_EXIT_JAM) {
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
			}
			/*
			** プリンターカバーが確実に開けらる必要があることをセットする。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			MAN_TopCoverNeedToBeOpenFlag = 1;	/** By S.Kawasaki 1997/05/07 JAM0507 */

			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_EXIT_JAM;		/* JAM発生 */
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* MISS FEED JAM                                                                   */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MISS_FEED_JAM) {
		if (!((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_MIS_FEED_JAM)) {
			/*
			** プリンターカバーが確実に開けらたかを確認する。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			if (MAN_TopCoverNeedToBeOpenFlag == 1) { /** By S.Kawasaki 1997/05/07 JAM0507 */
				/** まだ開けられていない */
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_MISS_FEED_JAM;	/* JAM解除 */
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	else {
		if ((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_MIS_FEED_JAM) {
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);												/** JAM発生イベント発行 */
			}
			/*
			** プリンターカバーが確実に開けらる必要があることをセットする。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			MAN_TopCoverNeedToBeOpenFlag = 1;	/** By S.Kawasaki 1997/05/07 JAM0507 */

			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_MISS_FEED_JAM;		/* JAM発生 */
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* REG JAM                                                                         */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_REG_JAM) {
		if (!((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_REG_JAM)) {
			/*
			** プリンターカバーが確実に開けらたかを確認する。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			if (MAN_TopCoverNeedToBeOpenFlag == 1) { /** By S.Kawasaki 1997/05/07 JAM0507 */
				/** まだ開けられていない */
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_REG_JAM;		/* JAM解除 */
				SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	else {
		if ((PrinterStatus[PRN_STATUS_3] & PRN_S3_JAM_TEST_DATA) == PRN_S3_REG_JAM) {
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PAPER_JAM);											/** JAM発生イベント発行 */
			}
			/*
			** プリンターカバーが確実に開けらる必要があることをセットする。
			** By S.Kawasaki 1997/05/07 JAM0507
			*/
			MAN_TopCoverNeedToBeOpenFlag = 1;	/** By S.Kawasaki 1997/05/07 JAM0507 */

			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_REG_JAM;		/* JAM発生 */
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}

	/***********************************************************************************/
	/* プリンタ・EP・カートリッジなしの監視                                            */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
#if (0) /**  ミノルタのプリンターにはこのステータスは無い By S.K Nov.13,199 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_CARTRIDGE) {
		if (!(PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_XERO_FAIL)) {
			/* EPなし -> EPあり */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_CARTRIDGE;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_OPERATER_CALL] & PRN_S1_XERO_FAIL) {
			/* EPあり -> EPなし */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_CARTRIDGE;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
#endif
	/***********************************************************************************/
	/* プリンタ・EP・カートリッジトナー少量の監視                                      */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	/* if (SYS_MachineStatus[SYS_PRINTER_STATUS] & SYS_PRINTER_FEW_EP_CARTRIDGE) { By S.Kawasaki 1996/06/20 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) { /** 名称変更 */
		if (!(PrinterStatus[PRN_TONAR_STATUS] & PRN_S15_TONAR_WARNING)) {
			/* EP少量 -> EPあり */
			/* SYS_MachineStatus[SYS_PRINTER_STATUS] &= ~SYS_PRINTER_FEW_EP_CARTRIDGE; By S.Kawasaki 1996/06/20 */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_FEW_TONER; /** 名称変更 */
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_TONAR_STATUS] & PRN_S15_TONAR_WARNING) {
			/* EPあり -> EP少量 */
			/* SYS_MachineStatus[SYS_PRINTER_STATUS] |= SYS_PRINTER_FEW_EP_CARTRIDGE; By S.Kawasaki 1996/06/20 */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_FEW_TONER; /** 名称変更 */

#if	(PRO_LOW_TONER_PRINT == PRINT_LIMIT)	/** F-150 Low Toner時のプリント枚数制限処理 By O.Kimoto 1996/12/26 */
			SYB_RestPrintPages = (WORD)CHK_UNI_RestPrintPage();
#endif
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki 1996/03/15                                      */
	/*****************************************************************/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
		if (!(PrinterStatus[PRN_STATUS_3] & PRN_S3_NOTEQUAL_PAPERSIZE)) {
			/* 記録しサイズエラー EP無し */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_SIZE_ERROR;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_STATUS_3] & PRN_S3_NOTEQUAL_PAPERSIZE) {
			/* 記録しサイズエラー EP有り */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_SIZE_ERROR;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・FUN・エラーの監視 (サービス・コール)                                  */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FAN_ABNORMAL)) {
		if (PrinterStatus[PRN_SERVICE_CALL] & PRN_S2_FAN_ALARM) {
			/* FUN・エラー発生 */
			SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_FAN_ABNORMAL;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・モータ・エラーの監視 (サービス・コール)                               */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* 以下のプリンターステータスの確認方法で問題ないはずです。      */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_MOTOR_ABNORMAL)) {
		if (PrinterStatus[PRN_SERVICE_CALL] & PRN_S2_ROS_MOTOR_ABNORMAL) {
			/* モータ・エラー発生 */
			SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_MOTOR_ABNORMAL;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・レーザー異常の監視 (サービス・コール)                                 */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* レーザー異常の追加。					      					 */
	/* By S.Kawasaki Jan.18,1996                                     */
	/*****************************************************************/
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_LASER_ABNORMAL)) {
		if (PrinterStatus[PRN_SERVICE_CALL] & PRN_S2_LASER_ABNORMAL) {
			/* モータ・エラー発生 */
			SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_LASER_ABNORMAL;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・定着器の異常温度エラーの監視 (サービス・コール)                       */
	/***********************************************************************************/
	/*****************************************************************/
	/* ANZU仕様                                                      */
	/* ミノルタ新規追加。                         					 */
	/* By S.Kawasaki Feb.7,1996                                      */
	/*****************************************************************/
	if (!(SYS_MachineStatus[SYS_PRINTER_STATUS3] & SYS_PRINTER_FUSER_ABNORMAL)) {
		if (PrinterStatus[PRN_SERVICE_CALL] & PRN_S2_HIGH_TEMP) {
			/* 定着器異常温度検出エラー発生 */
			SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_FUSER_ABNORMAL;
			SensorTaskMessage.Message = MSG_PRINTER_COVER_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}

#endif	/* PRO_PRINT_TYPE == LASER */

#if (PRO_PRINT_TYPE == LED)
	/***********************************************************************************/
	/* プリンタ・１段・記録紙の監視                                                    */
	/***********************************************************************************/
	/*-------------------------------------------------------+-------------------
	**	カセット
	*/
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE1_OPEN) {
		if (SYS_Paper1Size != SYS_NO_CASSETTE) {
			/* カセット・オープン -> クローズ */
			SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_CASSETTE1_OPEN;
			SensorTaskMessage.Message = MSG_CASSETTE_CLOSE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (SYS_Paper1Size == SYS_NO_CASSETTE) {
			/* カセット・クローズ -> オープン */
			SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_CASSETTE1_OPEN;
#if (0)	/* プリントは停止しない By M.Tachibana 1998/01/13 */
//			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
//				det_evt(EVT_PRN_PRINTER_ERROR);		/** JAM発生イベント発行 */
//			}
#endif
			SensorTaskMessage.Message = MSG_CASSETTE_OPEN;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*-------------------------------------------------------+-------------------
	**	記録紙
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
		if (SYS_Paper1Size != SYS_NO_PAPER) {
			/* 紙なし -> 紙あり */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (SYS_Paper1Size == SYS_NO_PAPER) {
			/* 紙あり -> 紙なし */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/***********************************************************************************/
	/* プリンタ・２段・記録紙の監視                                                    */
	/***********************************************************************************/
	if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT) {
		/*-------------------------------------------------------+-------------------
		**	カセット
		*/
		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN) {
			if (SYS_Paper2Size != SYS_NO_CASSETTE) {
				/* カセット・オープン -> クローズ */
				SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_CASSETTE2_OPEN;
				SensorTaskMessage.Message = MSG_CASSETTE_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if (SYS_Paper2Size == SYS_NO_CASSETTE) {
				/* カセット・クローズ -> オープン */
				SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_CASSETTE2_OPEN;
#if (0)	/* プリントは停止しない By M.Tachibana 1998/01/13 */
//				if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
//					det_evt(EVT_PRN_PRINTER_ERROR);		/** JAM発生イベント発行 */
//				}
#endif
				SensorTaskMessage.Message = MSG_CASSETTE_OPEN;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		/*-------------------------------------------------------+-------------------
		**	記録紙
		*/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) {
			if (SYS_Paper2Size != SYS_NO_PAPER) {
				/* 紙なし -> 紙あり */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER2;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if (SYS_Paper2Size == SYS_NO_PAPER) {
				/* 紙あり -> 紙なし */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER2;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	/***********************************************************************************/
	/* プリンタ・３段・記録紙の監視                                                    */
	/***********************************************************************************/
	if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT) {
		/*-------------------------------------------------------+-------------------
		**	カセット
		*/
		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE3_OPEN) {
			if (SYS_Paper3Size != SYS_NO_CASSETTE) {
				/* カセット・オープン -> クローズ */
				SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_CASSETTE3_OPEN;
				SensorTaskMessage.Message = MSG_CASSETTE_CLOSE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if (SYS_Paper3Size == SYS_NO_CASSETTE) {
				/* カセット・クローズ -> オープン */
				SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_CASSETTE3_OPEN;
#if (0)	/* プリントは停止しない By M.Tachibana 1998/01/13 */
//				if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
//					det_evt(EVT_PRN_PRINTER_ERROR);		/** JAM発生イベント発行 */
//				}
#endif
				SensorTaskMessage.Message = MSG_CASSETTE_OPEN;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		/*-------------------------------------------------------+-------------------
		**	記録紙
		*/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3) {
			if (SYS_Paper3Size != SYS_NO_PAPER) {
				/* 紙なし -> 紙あり */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER3;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
		else {
			if (SYS_Paper3Size == SYS_NO_PAPER) {
				/* 紙あり -> 紙なし */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER3;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}

	/*-------------------------------------------------------+-------------------
	**	MISS FEED JAM
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_MISS_FEED_JAM) {
		if (!(PrinterStatus[PRN_STATUS_2] & PRN_S2_MIS_FEED_JAM)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~(SYS_PRINTER_MISS_FEED_JAM	/* JAM解除 */
													  | SYS_PRINTER_1ST_FEED_JAM
													  | SYS_PRINTER_2ND_FEED_JAM
													  | SYS_PRINTER_3RD_FEED_JAM
													  | SYS_PRINTER_MANUAL_FEED_JAM);
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_STATUS_2] & PRN_S2_MIS_FEED_JAM) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_MISS_FEED_JAM;	/* JAM発生 */
			if (PrinterStatus[PRN_STATUS_2] & PRN_S2_1ST_FEED_JAM) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_1ST_FEED_JAM;
			}
			else if (PrinterStatus[PRN_STATUS_2] & PRN_S2_2ND_FEED_JAM) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_2ND_FEED_JAM;
			}
			else if (PrinterStatus[PRN_STATUS_2] & PRN_S2_3RD_FEED_JAM) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_3RD_FEED_JAM;
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_MANUAL_FEED_JAM;
			}
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {		/** プリンタ使用中なら */
				det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
			}
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*--------------------------------------------------------------------------
	**	REG JAM
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_REG_JAM) {
		if (!(PrinterStatus[PRN_STATUS_2] & PRN_S2_REG_JAM)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_REG_JAM;		/* JAM解除 */
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_STATUS_2] & PRN_S2_REG_JAM) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_REG_JAM;		/* JAM発生 */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PRN_PRINTER_ERROR);										/** JAM発生イベント発行 */
			}
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*--------------------------------------------------------------------------
	**	EXIT JAM
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_EXIT_JAM) {
		if (!(PrinterStatus[PRN_STATUS_2] & PRN_S2_EXIT_JAM)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_EXIT_JAM;		/* JAM解除 */
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[PRN_STATUS_2] & PRN_S2_EXIT_JAM) {
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_EXIT_JAM;		/* JAM発生 */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンタ使用中なら */
				det_evt(EVT_PRN_PRINTER_ERROR);									/** JAM発生イベント発行 */
			}
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*--------------------------------------------------------------------------
	**	トナー残量検出
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
/*		if (SYB_PrinterLifeMonitor.TonerLifeCount == 0) {	*/
		if (!(PrinterStatus[PRN_STATUS_5] & PRN_S5_TONER_WARNING)) {
			/* トナー少量 -> トナーあり */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_FEW_TONER;
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_END_TONER;
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
/*		if (SYB_PrinterLifeMonitor.TonerLifeCount > 0) {	*/
		if (PrinterStatus[PRN_STATUS_5] & PRN_S5_TONER_WARNING) {
			/* トナーあり -> トナー少量 */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_FEW_TONER;
			if (CHK_UNI_ContinueToPrintForTonar() == 0) {	/* 強制的にプリント停止 */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_END_TONER;
				SYB_PrinterLifeMonitor.TonerLifeCount = (UWORD)CHK_UNI_RestPrintPage() * 10 + 1;
			}
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*--------------------------------------------------------------------------
	**	トナー交換検出
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_TONER) {
#if (0)
//		if (SYB_PrinterLifeMonitor.TonerLifeCount == 0) {
//			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_END_TONER;
//			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
//			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
//			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
//		}
#endif
	}
	else {
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
			if (SYB_PrinterLifeMonitor.TonerLifeCount > (UWORD)CHK_UNI_RestPrintPage() * 10) {
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_END_TONER;
				SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
				snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
				rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
			}
		}
	}
	/*--------------------------------------------------------------------------
	**	ドラム寿命近し検出
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NEAREND_DRUM) {
/*		if (SYB_PrinterLifeMonitor.DrumLifeCount == 0) {	By M.Tachibana 1998/02/01 */
		if (!(PrinterStatus[PRN_STATUS_5] & PRN_S5_DRUM_WARNING)) {
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NEAREND_DRUM;
			SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_END_DRUM;	/* By M.Tachibana 1998/01/27 */
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
/*		if (SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintMax) {	By M.Tachibana 1998/02/01 */
		if (PrinterStatus[PRN_STATUS_5] & PRN_S5_DRUM_WARNING) {
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NEAREND_DRUM;
			if (SYB_PrinterLifeMonitor.OrderListRequest) {
				if (CHK_UNI_OrderListPrint() & DRUM_ORDER_LIST_PRINT) {
				/*	SYB_ConsumerOrderListRequest = 1;	By M.Tachibana 1998/01/31 */
					SYB_ConsumerOrderListRequest |= SYS_ORDER_ITEM_DRUM;
				}
				SYB_PrinterLifeMonitor.OrderListRequest = 0;
			}
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	/*--------------------------------------------------------------------------
	**	ドラム寿命検出	By M.Tachibana 1998/01/27
	*/
#if (PRO_DRUM_PRT_CNT == ENABLE)/* NTT のみ By Y.Suzuki 1998/07/06*/
#else
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_END_DRUM) {
	}
	else {
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NEAREND_DRUM) {
			if (!(page_count = CHK_UNI_AdditionalDrumLifeCount() * 100)) {/*V851 ﾄﾞﾗﾑ寿命枚数 調整 By Y.Suzuki 2002/09/17*/
				if (SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintStopMax) {
					SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_END_DRUM;
					SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				}
			}
			else {/*V851 ﾄﾞﾗﾑ寿命枚数 調整 By Y.Suzuki 2002/09/17 */
				if (SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)(PRN_DrumPrintStopMax + page_count)) {
					SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_END_DRUM;
					SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
					snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
					rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
				}
			}
		}
	}
#endif
	/*--------------------------------------------------------------------------
	**	トナーカートリッジ（現像器）なし
	*/
	MAN_PrinterToMachineStatus(SYS_PRINTER_STATUS1, SYS_PRINTER_NO_CARTRIDGE,
							   PRN_STATUS_3, PRN_S3_NO_CARTRIDGE);
	/*--------------------------------------------------------------------------
	**	ドラムユニットなし
	*/
	MAN_PrinterToMachineStatus(SYS_PRINTER_STATUS1, SYS_PRINTER_NO_DRUM,
							   PRN_STATUS_3, PRN_S3_NO_DRUM);
	/*--------------------------------------------------------------------------
	**	サイズエラー検出
	*/
	MAN_PrinterToMachineStatus(SYS_PRINTER_STATUS2, SYS_PRINTER_SIZE_ERROR,
							   PRN_STATUS_1, PRN_S1_SIZE_ERROR);
	/*--------------------------------------------------------------------------
	**	ドラムユニット異常
	*/
	MAN_PrinterToMachineStatus(SYS_PRINTER_STATUS3, SYS_PRINTER_DRUM_ABNORMAL,
							   PRN_STATUS_4, PRN_S4_DRUM_ABNORMAL);

	if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_DRUM_ABNORMAL)) {
		SYB_PrinterLifeMonitor.ErrorStatus &= ~SYS_DRUM_TROUBLE;
	}
	/*--------------------------------------------------------------------------
	**	定着器異常
	*/
	MAN_PrinterToMachineStatus(SYS_PRINTER_STATUS3, SYS_PRINTER_FUSER_ABNORMAL,
							   PRN_STATUS_4, PRN_S4_FUSER_ABNORMAL);

	if (!(PrinterStatus[PRN_STATUS_4] & PRN_S4_FUSER_ABNORMAL)) {
		/* 定着器異常あり -> 定着器異常なし */
		SYB_PrinterLifeMonitor.ErrorStatus &= ~(SYS_HEATER_TROUBLE|SYS_HEATER_DISCONNECT|SYS_HEATER_SHORT);
	}

#endif	/* PRO_PRINT_TYPE == LED */

}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[プリンタ情報をマシンステータスにセットする]
	function	:[
		1.
	]
	return		:[
		1.ＦＡＬＳＥ：マシンステータスに更新せず
		2.ＴＲＵＥ  ：マシンステータスを更新した
	]
	common		:[]
	condition	:[]
	comment		:[
		1.プリンタ情報については、複数のビット指定ができる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/06/13]
	author		:[橘正樹]
*************************************************************************/
void MAN_PrinterToMachineStatus(
UBYTE machine_data_pos,
UWORD machine_test_bit,
UBYTE printer_data_pos,
UBYTE printer_test_bit )
{
	if (SYS_MachineStatus[machine_data_pos] & machine_test_bit) {
		if (!(PrinterStatus[printer_data_pos] & printer_test_bit)) {
			/* なし -> あり */
			SYS_MachineStatus[machine_data_pos] &= ~machine_test_bit;
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
	else {
		if (PrinterStatus[printer_data_pos] & printer_test_bit) {
			/* あり -> なし */
			SYS_MachineStatus[machine_data_pos] |= machine_test_bit;
			SensorTaskMessage.Message = MSG_SENSOR_UPDATE;	/* TBD */
			snd_msg(mbxno.MAN_Task, &SensorTaskMessage);
			rcv_msg(mbxno.MAN_SensorTask,&SensorMsg);
		}
	}
}
#endif

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[ＡＤカセットデータのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/06/13]
	author		:[橘正樹]
*************************************************************************/
void MAN_CheckAD_CassetteData(
UWORD *wk_paper_size,
UWORD *base_paper_size,
UWORD *ave_paper_size,
UWORD *counter )
{
	UBYTE is_count;

	is_count = 0;
	/*-------------------------------------------------------------------
	** 急激なＡＤデータの変化は値に反映させない
	** マージン±0x10 -> ±0x1C  1998/01/23
	*/
	if (*wk_paper_size >= *base_paper_size) {
		if (*wk_paper_size < *base_paper_size + 0x1C) {
			is_count = 1;
		}
	}
	else {
		if (*base_paper_size >= 0x1C) {
			if (*wk_paper_size > *base_paper_size - 0x1C) {
				is_count = 1;
			}
		}
		else {
			is_count = 1;
		}
	}
	if (is_count) {
		if (--(*counter) == 0) {
			*ave_paper_size = *wk_paper_size;
			*base_paper_size = *wk_paper_size;	/* By M.Tachibana 1998/01/22 */
			*counter = DETECT_TIME_CASSETTE;
		}
	}
	else {
		*base_paper_size = *wk_paper_size;
		*counter = DETECT_TIME_CASSETTE;
	}
}
#endif
