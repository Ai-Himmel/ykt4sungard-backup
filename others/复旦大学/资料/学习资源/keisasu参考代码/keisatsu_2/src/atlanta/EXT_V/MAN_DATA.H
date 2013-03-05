#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysmax.h"
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/21 */
#include "\src\atlanta\define\time.h"
#endif
/************************************************************************
 * 表示用タイマータスク													*
 * 1994/07/29															*
 * 吉川弘康																*
 ************************************************************************/
extern UWORD tskno_faxcom_complete;
extern UWORD tskno_store_complete;
extern UWORD tskno_print_complete;
extern UWORD tskno_cmn_watchtimer10msevent;	/** Add By Hirao 1996/08/24 */

#if (PRO_CLASS1 == ENABLE)
extern UWORD tskno_pc_fax_complete; /* 1996/09/13 Eguchi */
extern struct Timer10msData_t PC_FAX_CompleteMessage;/*1996/09/13 Eguchi */
#endif

extern struct Timer10msData_t FaxcomCompleteMessage;
extern struct Timer10msData_t StoreCompleteMessage;
extern struct Timer10msData_t PrintCompleteMessage;
extern struct Timer10msData_t NextScanStartOperation;
extern struct Timer10msData_t ParamDispCompleteMessage;

/************************************************************************
 * 表示用マルチタイマーＩＤ												*
 * 1997/01/23															*
 * 野瀬敏弘																*
 ************************************************************************/
extern UBYTE timer_store_copy_complete;	/* コピー蓄積完了 */
extern UBYTE timer_next_scan_complete;	/* 次原稿オペレーション表示用 */
extern UBYTE timer_store_fax_complete;	/* メモリー送信原稿蓄積完了表示用 */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
extern UBYTE timer_faxcom_complete;		/* 通信終了表示用 */
extern UBYTE timer_print_complete;		/* プリント完了時 */
 #if (PRO_PC_PRINT == ENABLE)
extern UBYTE timer_print_pc_complete;	/* ＰＣプリント追加 by T.Soneoka 1997/07/17 */
 #endif
#endif

/************************************************************************
 * 保留状態１分経過通知アラームタスク									*
 * 1994/09/17															*
 * 奥村明																*
 ***********************************************************************/
extern UWORD tskno_hold_alarm;

/************************************************************************
 * ブザー・アラーム用タイマータスク										*
 * 1994/07/29															*
 * 吉川弘康																*
 ************************************************************************/
extern UWORD tskno_end_buzzer;
extern UWORD tskno_error_alarm;
extern UWORD tskno_hunguperror;

/************************************************************************
 * マシーンステータス退避用変数
 * 1995/12/05 Eguchi
 * 江口
 ************************************************************************/
extern UWORD BackUpStatusPrinter1;
extern UWORD BackUpStatusPrinter2;
extern UWORD BackUpStatusPrinter3;
extern UWORD BackUpStatusScanner;
extern UWORD BackUpStatusError;
extern UWORD BackUpStatusCover;
extern UWORD BackUpStatusWarning; /* 追加　1996/06/20　Eguchi */
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/12 */
extern UWORD BackUpStatusCipher;
#endif

/************************************************************************
 * 保留警告ブザー鳴動指示フラグ											*
 * 1995/12/04															*
 * Eguchi																*
 * ブザーは全てUpdateDisplay()でならすようにするから					*
 ************************************************************************/
extern UBYTE HoldBuzzerRequest; 	/* 1995/12/04 Eguchi */
extern UBYTE HoldEndBuzzerRequest; /* 1995/12/04 Eguchi */

/************************************************************************
 * 保留終了ブザー鳴動タスク												*
 * 1995/12/05															*
 * Eguchi																*
 ************************************************************************/
extern	UWORD	 tskno_hold_end; 	/* 1995/12/05 Eguchi */
/************************************************************************
 * ＲＴＣテストモード実行フラグ											*
 * Feb.20,19965															*
 * Kawasaki																*
 ************************************************************************/
extern  UBYTE RTC_TestMode;
/************************************************************************
 * プリンター使用開始時のページカウンター								*
 * 1996/03/13															*
 * Kawasaki																*
 ************************************************************************/
extern UBYTE MAN_StartPageCounter;
/************************************************************************
 * プリンター使用終了時のページカウンター								*
 * 1996/03/13															*
 * Kawasaki																*
 ************************************************************************/
extern UBYTE MAN_EndPageCounter;

#if defined(GBR)
/************************************************************************
 * 受信完了ブザー鳴動タスク												*
 * 1996/07/08															*
 * GBRのみ		i														*
 * Eguchi																*
 ************************************************************************/
extern	UWORD	 tskno_audible_alarm;
#endif
/************************************************************************
 * ＴＣＢ格納ようのタスク変数（man_main.cから移動）						*
 * 1996/10/11															*
 * 小谷正樹																*
 ************************************************************************/
extern	UWORD	tskno_DocumentOutTask;
extern	UWORD	tskno_SCN_StampTestTask;
extern	UWORD	tskno_SCN_DocumentStoreTask;
extern	UWORD	tskno_PRN_ImagePrintTask;
extern	UWORD	tskno_CPY_Task;
extern	UWORD	tskno_LST_PrintTask;
extern	UWORD	tskno_FCM_Task;
extern	UWORD	tskno_MAN_SensorTask;
extern	UWORD	tskno_MAN_TimerTask;
extern	UWORD	tskno_NCU_TelephoneOperation;
extern	UWORD	tskno_NCU_Task;
extern	UWORD	tskno_OPR_Task;
extern	UWORD	tskno_SCN_GearBackLashTask;
extern	UWORD	tskno_OPR_SubMessageReceiveTask;
extern	UWORD	tskno_PRN_PrinterResetTask;
extern	UWORD	tskno_PRN_PrinterWarmUpTask;

#if (PRO_DOC_IN == ENABLE)
extern	UWORD	tskno_DocumentInTask;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
extern	UWORD	tskno_JournalPrintTask;
#endif

#if (PRO_DIALIN == ENABLE)
extern	UWORD	tskno_NCU_DialInAutoSwitchTask;
#endif

#if (PRO_PRINT_TYPE == LED)
extern	UWORD	tskno_PRN_FuserTempTask;
extern	UWORD	tskno_PRN_ManualDocInTask;
#endif

#if (PRO_PRINT_TYPE == THERMAL)
extern UWORD	tskno_SCN_CopyStoreTask;
#endif

#if (PRO_ROTATE == ENABLE)
extern	UWORD	tskno_ROT_Task;
extern UWORD MAN_RotateIsBusy;
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
extern	UWORD	tskno_NCU_FaxComTelHookChkTask;
#endif

#if defined(POPLAR_F)
extern UWORD	tskno_MDM_InternalStatus;
#endif

/* SCN T.Nose 1997/01/17 */
extern UBYTE	GearBackLashRequest;	/* ICHOU用	1996/07/24 s.takeuchi */
extern UBYTE	exit_flag;
#if (PRO_FBS == ENABLE)
extern UBYTE	MirrorTaskInstruction;	/* ICHOU用	1996/12/09 s.takeuchi */
extern UBYTE	MirrorTaskRequest;		/* ICHOU用	1996/11/20 s.takeuchi */
#endif
/* ギアバックラッシュタスクのタイムアウト強制終了、再起動処理用  1997/05/09 s.takeuchi */
extern UBYTE	GearBackLashTimer;
extern UBYTE	GearBackLashTimeout;
extern UBYTE	GearBackLashRetryCount;
extern UBYTE	DocumentResetOperation; /* 原稿セットやり直し操作要求フラグ T.Nose 1997/08/21 */
/* POPLAR_B はFBSカバー閉でランプ点灯しないので削除 T.Nose */
/* extern UWORD	LampOffTimer;			/* ICHOUで変更  減算タイマー(単位:1min) */

extern UBYTE	CommandErased[SYS_OPTION_BOARD_MAX];

extern UBYTE	HungUpCheck;
extern UBYTE	main_rx_mode;
extern UBYTE	FCOT_PrintExecute;

#if (PRO_CIPHER == ENABLE)		/*	By Y.Suzuki 1997/07/11	*/
extern UWORD	tskno_SCD_MML_CipherDebugTask;
extern UWORD	tskno_SCD_CipherTask;
extern UWORD	tskno_SCD_DeCipherTask;
#endif
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
extern UWORD	tskno_SCN_GetShade;
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/* V851 省エネBy Y.Suzuki 2002/06/18 */
extern UWORD	tskno_MAN_WakeUpSystemTask;
extern UWORD	tskno_MAN_SleepSystemTask;
#endif
/************************************************************************
 * 受信完了、送信完了表示識別用											*
 * 1997/5/29															*
 * M.Kotani																*
 ************************************************************************/
extern UBYTE FaxComCompleteDisplaySign;	/* 1997/01/09 Y.Murata */

#if defined (KEISATSU)		/* 警察FAX DVT_ID43 Added by SMuratec K.W.Q 2005/11/15 */
extern UBYTE FaxComCompleted;
/* 警察FAX DVT Added by SMuratec 李 2005/11/30 */
extern UBYTE NCUSndMsg;
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/08/10 */
/************************************************************************
 * ＰＣプリントメモリ管理データ											*
 * 1997/5/29															*
 * M.Kotani																*
 ************************************************************************/
extern struct MEM_IndexData_t		PcRxErasePoint;
extern struct MEM_IndexData_t		PcRxPagePoint;	/* By J.Miyazaki 1996/09/21 */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
extern UWORD tskno_INF_Task;
extern UWORD tskno_inf_terminate;
extern UWORD tskno_inf_nomail;
extern UWORD tskno_inf_complete;
extern struct	Timer10msData_t	INF_CompleteMessage;
extern struct	Timer10msData_t	INF_NoNewMailMessage;
extern struct	Timer10msData_t	INF_TerminateMessage;
#endif

/************************************************************************
 * デバッグ用アイドル表示用変数											*
 * 1997/12/10															*
 * M.Kotani	アイドルカウンターともに表示する							*
 ************************************************************************/
extern UWORD MAN_DebugCounter;

#if (PRO_PREHEAT == ENABLE)
/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
extern UDWORD	PreHeatStartTime;
extern UDWORD	PreHeatEndTime;
extern TIME_DATA_t	PreHeatEndTimeBCD;
#endif

#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
extern UWORD tskno_callingbuzzer;	/* 呼出ブザー鳴動用 */
#endif

#if defined(KEISATSU)	
extern UBYTE	Hangup_Line;			/* 警察FAX DVT by SMuratec 夏 2005/11/19 */
extern UBYTE	IsJournalCompleted;		/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
#endif
