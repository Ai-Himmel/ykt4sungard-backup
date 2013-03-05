#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\mem_def.h"
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/21 */
#include "\src\atlanta\define\time.h"
#endif
/************************************************************************
 * 表示用タイマータスク													*
 * 1994/07/29															*
 * 吉川弘康																*
 ************************************************************************/
UWORD tskno_faxcom_complete = 0;
UWORD tskno_store_complete = 0;
UWORD tskno_print_complete = 0;

#if (PRO_CLASS1 == ENABLE)
UWORD tskno_pc_fax_complete = 0; /* 1996/09/13 Eguchi */
struct Timer10msData_t PC_FAX_CompleteMessage = {0};/*1996/09/13 Eguchi */
#endif

struct Timer10msData_t FaxcomCompleteMessage = {0};
struct Timer10msData_t StoreCompleteMessage = {0};
struct Timer10msData_t PrintCompleteMessage = {0};
struct Timer10msData_t NextScanStartOperation = {0};
struct Timer10msData_t ParamDispCompleteMessage = {0};

/************************************************************************
 * 表示用マルチタイマーＩＤ												*
 * 1997/01/23															*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE timer_store_copy_complete = 0;	/* コピー蓄積完了 */
UBYTE timer_next_scan_complete = 0;		/* 次原稿オペレーション表示用 */
UBYTE timer_store_fax_complete = 0;		/* メモリー送信原稿蓄積完了表示用 */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
UBYTE timer_faxcom_complete = 0;		/* 通信終了表示用 */
UBYTE timer_print_complete = 0;			/* プリント完了時 */
 #if (PRO_PC_PRINT == ENABLE)
UBYTE timer_print_pc_complete = 0;	/* ＰＣプリント追加 by T.Soneoka 1997/07/17 */
 #endif
#endif

/************************************************************************
 * 保留状態１分経過通知アラームタスク									*
 * 1994/09/17															*
 * 奥村明																*
 ***********************************************************************/
UWORD tskno_hold_alarm = 0;

/************************************************************************
 * ブザー・アラーム用タイマータスク										*
 * 1994/07/29															*
 * 吉川弘康																*
 ************************************************************************/
UWORD tskno_end_buzzer = 0;
UWORD tskno_error_alarm = 0;
UWORD tskno_hunguperror = 0;

/************************************************************************
 * マシーンステータス退避用変数
 * 1995/12/05 Eguchi
 * 江口
 ************************************************************************/
UWORD BackUpStatusPrinter1 = 0;
UWORD BackUpStatusPrinter2 = 0;
UWORD BackUpStatusPrinter3 = 0;
UWORD BackUpStatusScanner = 0;
UWORD BackUpStatusError = 0;
UWORD BackUpStatusCover = 0;
UWORD BackUpStatusWarning = 0; /* 追加　1996/06/20　Eguchi */
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
UWORD BackUpStatusCipher = 0;
#endif

/************************************************************************
 * 保留警告ブザー鳴動指示フラグ											*
 * 1995/12/04															*
 * Eguchi																*
 * ブザーは全てUpdateDisplay()でならすようにするから					*
 ************************************************************************/
UBYTE HoldBuzzerRequest = 0; 	/* 1995/12/04 Eguchi */
UBYTE HoldEndBuzzerRequest = 0; /* 1995/12/04 Eguchi */

/************************************************************************
 * 保留終了ブザー鳴動タスク												*
 * 1995/12/05															*
 * Eguchi																*
 ************************************************************************/
UWORD tskno_hold_end = 0; 	/* 1995/12/05 Eguchi */
/************************************************************************
 * ＲＴＣテストモード実行フラグ											*
 * Feb.20,19965															*
 * Kawasaki																*
 ************************************************************************/
UBYTE RTC_TestMode = 0;
/************************************************************************
 * プリンター使用開始時のページカウンター								*
 * 1996/03/13															*
 * Kawasaki																*
 ************************************************************************/
UBYTE MAN_StartPageCounter = 0;
/************************************************************************
 * プリンター使用終了時のページカウンター								*
 * 1996/03/13															*
 * Kawasaki																*
 ************************************************************************/
UBYTE MAN_EndPageCounter = 0;

#if defined(GBR)
/************************************************************************
 * 受信完了ブザー鳴動タスク												*
 * 1996/07/08															*
 * GBRのみ																*
 * Eguchi																*
 ************************************************************************/
UWORD	 tskno_audible_alarm = 0;
#endif
/************************************************************************
 * ＴＣＢ格納ようのタスク変数（man_main.cから移動）						*
 * 1996/10/11															*
 * 小谷正樹																*
 ************************************************************************/
UWORD	tskno_DocumentOutTask			= 0;
UWORD	tskno_SCN_StampTestTask			= 0;
UWORD	tskno_SCN_DocumentStoreTask		= 0;
UWORD	tskno_PRN_ImagePrintTask		= 0;
UWORD	tskno_CPY_Task					= 0;
UWORD	tskno_LST_PrintTask				= 0;
UWORD	tskno_FCM_Task					= 0;
UWORD	tskno_MAN_SensorTask			= 0;
UWORD	tskno_MAN_TimerTask				= 0;
UWORD	tskno_NCU_TelephoneOperation	= 0;
UWORD	tskno_NCU_Task					= 0;
UWORD	tskno_OPR_Task					= 0;
UWORD	tskno_SCN_GearBackLashTask		= 0;
UWORD	tskno_OPR_SubMessageReceiveTask = 0;
UWORD	tskno_PRN_PrinterResetTask		= 0;
UWORD	tskno_PRN_PrinterWarmUpTask		= 0;

#if (PRO_DOC_IN == ENABLE)
UWORD	tskno_DocumentInTask			= 0;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
UWORD	tskno_JournalPrintTask			= 0;
#endif

#if (PRO_DIALIN == ENABLE)
UWORD	tskno_NCU_DialInAutoSwitchTask	= 0;
#endif

#if (PRO_PRINT_TYPE == LED)
UWORD	tskno_PRN_FuserTempTask			= 0;
UWORD	tskno_PRN_ManualDocInTask		= 0;
#endif

#if (PRO_PRINT_TYPE == THERMAL)
UWORD	tskno_SCN_CopyStoreTask 		= 0;
#endif

#if (PRO_ROTATE == ENABLE)
UWORD	tskno_ROT_Task					= 0;
UWORD	MAN_RotateIsBusy = 0;
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
UWORD	tskno_NCU_FaxComTelHookChkTask	= 0;
#endif

#if defined(POPLAR_F)
UWORD	tskno_MDM_InternalStatus 		= 0;
#endif

/* SCN T.Nose 1997/01/17 */
UBYTE	GearBackLashRequest = 0;	/* ICHOU用	1996/07/24 s.takeuchi */
UBYTE	exit_flag = 0;
#if (PRO_FBS == ENABLE)
UBYTE	MirrorTaskInstruction = 0;	/* ICHOU用	1996/12/09 s.takeuchi */
UBYTE	MirrorTaskRequest = 0;		/* ICHOU用	1996/11/20 s.takeuchi */
#endif
/* ギアバックラッシュタスクのタイムアウト強制終了、再起動処理用  1997/05/09 s.takeuchi */
UBYTE	GearBackLashTimer = 0;
UBYTE	GearBackLashTimeout = 0;
UBYTE	GearBackLashRetryCount = 0;
UBYTE	DocumentResetOperation = 0; /* 原稿セットやり直し操作要求フラグ T.Nose 1997/08/21 */

/* POPLAR_B はFBSカバー閉でランプ点灯しないので削除 T.Nose */
/* UWORD	LampOffTimer = 0;			/* ICHOUで変更  減算タイマー(単位:1min) */

UBYTE	CommandErased[SYS_OPTION_BOARD_MAX] = {0};

UBYTE	HungUpCheck = 0;
UBYTE	main_rx_mode = 0;
UBYTE	FCOT_PrintExecute = 0;

#if (PRO_CIPHER == ENABLE)		/*	By Y.Suzuki 1997/07/11	*/
UWORD	tskno_SCD_CipherTask = 0;
UWORD	tskno_SCD_DeCipherTask = 0;
#endif

#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
UWORD	tskno_SCN_GetShade = 0;
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
UWORD	tskno_MAN_WakeUpSystemTask 		= 0;
UWORD	tskno_MAN_SleepSystemTask		= 0;
#endif

/************************************************************************
 * 受信完了、送信完了表示識別用											*
 * 1997/5/29															*
 * M.Kotani																*
 ************************************************************************/
UBYTE FaxComCompleteDisplaySign = 0;	/* 1997/01/09 Y.Murata */

#if defined (KEISATSU)		/* 警察FAX DVT_ID43 Added by SMuratec K.W.Q 2005/11/15 */
UBYTE FaxComCompleted = 0;
/* 警察FAX DVT Added by SMuratec 李 2005/11/30 */
UBYTE NCUSndMsg 	= 0;
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/08/10 */
/************************************************************************
 * ＰＣプリントメモリ管理データ											*
 * 1997/5/29															*
 * M.Kotani																*
 ************************************************************************/
struct MEM_IndexData_t		PcRxErasePoint = {0};
struct MEM_IndexData_t		PcRxPagePoint = {0};	/* By J.Miyazaki 1996/09/21 */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
UWORD	tskno_INF_Task	= 0;
UWORD	tskno_inf_terminate = 0;
UWORD	tskno_inf_nomail = 0;
UWORD	tskno_inf_complete = 0;
struct	Timer10msData_t	INF_CompleteMessage = {0};
struct	Timer10msData_t	INF_NoNewMailMessage = {0};
struct	Timer10msData_t	INF_TerminateMessage = {0};
#endif


/************************************************************************
 * デバッグ用アイドル表示用変数											*
 * 1997/12/10															*
 * M.Kotani	アイドルカウンターともに表示する							*
 ************************************************************************/
UWORD MAN_DebugCounter = 0;

#if (PRO_PREHEAT == ENABLE)
/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
UDWORD	PreHeatStartTime = 0;
UDWORD	PreHeatEndTime = 0;
TIME_DATA_t		PreHeatEndTimeBCD = {0};
#endif

#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
UWORD tskno_callingbuzzer = 0;	/* 呼出ブザー鳴動用 */
#endif

#if defined(KEISATSU)	
UBYTE	Hangup_Line	= 0;			/* 警察FAX DVT by SMuratec 夏 2005/11/19 */
UBYTE	IsJournalCompleted = 0;		/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
#endif

