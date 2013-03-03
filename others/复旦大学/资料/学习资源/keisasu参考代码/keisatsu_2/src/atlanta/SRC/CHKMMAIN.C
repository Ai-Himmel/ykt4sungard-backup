/************************************************************************
*				BY:	 S.Kawasaki, M.Kotani
*			  DATE:	 Sep.2,1993, 1996/10/11
*		 FILE NAME:	 man_main.c
*	   Module Name:	 MAN_Task(void)
*				  :	 MAN_AfterMessageCheck()
*				  :	 MAN_NextScanStart()
*		Task ID No:	 1
*		 REFERENCE:	 IdleTask()よりクリエイトされる.ファイル:man_idle.c参照
*************************************************************************/
/*********************************************************************
 * <<修正履歴>>
 * 1.\src\kobe\anzu\src\man_main.cをポプラ＆あんずＬ用に移動	1996/10/14 M.Kotani
 * 2.MAN_Task()をメッセージ別に分解＆整理	1996/10/14 M.Kotani
 *********************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\sysprint.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sys_line.h"
#include  "\src\atlanta\define\sysscan.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
#include  "\src\atlanta\define\mntsw_a.h"
#if defined(SCN_WS) /* Scanner Debug T.Nose */
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\mntsw_c.h"
#endif
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/*FCM*/
#include  "\src\atlanta\define\fcm_def.h"
/* 連続ポーリング機能 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include  "\src\atlanta\define\syscntpl.h"
#endif
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\define\opr_def.h"
void UpdateLCD2(void);
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\define\opr_def.h" /* Changed by H.Kubo 1997/08/18 */
#endif
#include	"\src\atlanta\define\chk_def.h"

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
#include  "\src\atlanta\ext_v\mlt_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
/*SCN*/
#include  "\src\atlanta\ext_v\scn_data.h"
/*PAT*/
#if (PRO_PAT_JOURNAL == ENABLE)
#include  "\src\atlanta\ext_v\pat_data.h"
#endif
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#include	"\src\atlanta\ext_v\cmn_data.h"	/* 1996/11/19 T.Nose */

#if (PRO_MULTI_LINE == ENABLE)
#include  "\src\atlanta\define\mlt_pro.h"
#endif
#if (PRO_CIPHER == ENABLE)/*	By Y.Suzuki 1997/09/04	*/
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif


/*プロトタイプ宣言*/
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\dpr_pro.h"
	void	SCN_Init( void );			/* SCN */
	void	SCN_SetMotorDrive( UBYTE );
	WORD 	Check_AnyList(UBYTE Mode);	/* LST */
	void 	Init_AnyList(UBYTE Mode);	/* LST */


/*ROT*/	/* Add By O.Kimoto 1997/06/13 */
#if (PRO_ROTATE == ENABLE)
	#include "\src\atlanta\define\rot_pro.h"
	#include  "\src\atlanta\ext_v\dpr_data.h"
		/*#include "\src\atlanta\define\dpr_pro.h"*/
		UBYTE DPR_CheckRotateBoardExist(void);
#endif
#if (PRO_SECURITY_RX == ENABLE)
	void	SetSecurityRxMode(void);
	UBYTE	CheckSecurityRxChkMsgPrint(void);
#endif
/* #if (PRO_CLASS1 == ENABLE) */
	#include "\src\atlanta\ext_v\cl1_data.h"
	extern UBYTE	RsTestChar;
	extern UBYTE	RsTestMode;
	#include "\src\atlanta\define\cl1_pro.h"
	void	CL1_RSHardWareCheck( void );
	/*#include  "\src\atlanta\define\uni_pro.h"*/
	UBYTE  CHK_UNI_MemoryRxAndPrint(void);
/* #endif */
void AnalogFunctionCheckerMain( void );	/* アナログファンクションチェッカー */
CONST UBYTE	DEBUG_PrnTestNo = 0;	/* for debug */

void MAN_InitializeDevice2(void);		/* チェッカー用 */
void MAN_InitializeTaskCreate2(void);	/* チェッカー用 */
void UpdateDisplay2(void);				/* チェッカー用 */
void ImagePrintTest(void);				/* チェッカー用 *//* By M.Tachibana 1998/03/31 */

UBYTE	DSW(void);	/* io_pro.h */
UBYTE			CheckMemory(
						 UBYTE	ReadWrite,		/* Read/Write */
						 UDWORD	address);	/* スタートアドレス */

/*---------------------------------------------------------------------
** chkicpu.cのInitializeSystemProcess()で
** CheckerModeRomSwをCheckerModeにコピーする
** HardDipを読んでテストモードを変えるため
*/
CONST UBYTE CheckerModeRomSw = 0x70;	/* チェッカー・テストモード */
UBYTE CheckerMode = 0;				/* チェッカー・テストモード */
/*----------------------------------------------------------------------
**	CheckerMode
**
**	０ｘ００：Ａ／Ｆ
**	０ｘ１？：サブＡＳＳＹ検査
**		０ｘ１０	Ａ：ＦＢＳ ＡＳＳＹ検査		ＤＳＷ：０
**		０ｘ１１	Ｂ：ＯＰカセット検査		ＤＳＷ：１
**					Ｃ：プリンタ ＡＳＳＹ検査	製品ＲＯＭ
**		０ｘ１２	Ｄ：パネル ＡＳＳＹ検査		ＤＳＷ：２
**	０ｘ２０：ＭＯＤＥＭ ＰＣＢテスト
**	０ｘ３０：ＰＡＮＥＬ＿ＬＣＤ ＰＣＢテスト
**		Ａ：ＬＥＤテスト
**		Ｂ：ＬＣＤテスト
**		Ｃ：ＫＥＹテスト
**	０ｘ４０：ＥＸ－ＭＥＭＯＲＹ ＰＣＢテスト
**		Ａ：８Ｍ
**		Ｂ：４Ｍ
**		Ｃ：２Ｍ
**	０ｘ５０：カセット テスト
**		Ａ：ＣＡＳＳＥＴＴＥ1
**		Ｂ：ＣＡＳＳＥＴＴＥ２
**	０ｘ６０：回転基板テスト
**	０ｘ７０：テストプリント
**	０ｘ７１：カセットテスト
**	０ｘ８０：ANZU_L用自動検査ロム
**	０ｘ９０：POPLAR_L ＣＣＤチェッカー
*/

/** Module Header For CIM-E ********************************************
		module		:	[メイン・タスク・タスク]
		function	:	[
						１．センサー・タスクのメッセージ処理
						２．原稿繰り込みタスクのメッセージ処理
						３．シングル・コピーのメッセージ
						４．蓄積タスクのメッセージ処理
						５．メモリ・プリント・タスクからのメッセージ処理
						６．ＮＣＵタスクからのメッセージ処理
						７．オペレーション・タスクからのメッセージ処理
						８．リスト・プリント・タスクのメッセージ処理
						９．通信タスクのメッセージ処理
						１０．ＦＩＰタスクからのメッセージ処理
						１１．タイマー・タスクからのメッセージ処理
						１２．通信スケジューラー／通信
						１３．蓄積原稿プリント起動と状態監視
						１４．リスト・プリントの起動と状態監視
						１５．ディスプレイの書き換え
						１６．バッファリング受信の起動メッセージ処理   add by Y.Murata 1994/06/18
						]
		return		:	[無し]
		common		:	[]
		condition	:	[アイドル・タスクからパワーON直後に一度だけクリエイトされ、電源がOFFになるまで死なない]
		comment		:	[]
		machine		:	[V53/H8]
		language	:	[MSC]
		keyword		:	[MAIN]
		date		:	[93/11/10(水)]
		author		:	[川崎真史]
************************************************************************/
void MAN_Task(void)
{
	UWORD Item;
	UWORD Message;
	UWORD SubMessage1;
	UWORD SubMessage2;
	UWORD SubMessage3;
	UWORD SubMessage4;
	UWORD stack_num;
	UBYTE debug_anzu;
	UBYTE result;			/*検査結果*/

	MESSAGE_t	*MessageControl;

	debug_anzu = 0;	/* DEBUG */

	/*スタティック変数の初期化*/
	HungUpCheck = 0;			/* ハング・アップ・チェック無し */
	for (stack_num = 0; stack_num < SYS_OPTION_BOARD_MAX; stack_num++) {
		CommandErased[stack_num] = 0;
	}

	/****************************************************************/
	/* ＤＳＷの読み出し												*/
	/****************************************************************/
	if (CheckerMode == 0x10) {
		switch(DSW()) {
		case 0x0F:
			CheckerMode = 0x10;
			break;
		case 0x07:
			CheckerMode = 0x11;
			break;
		case 0x0B:
			CheckerMode = 0x12;
			break;
		default:
			CheckerMode = 0x10;
			break;
		}
	}
	/****************************************************************/
	/* セマフォの作成(ＲＴＣのセマフォもあるのでメインの最初にする) */
	/****************************************************************/
	MAN_InitializeSemapho();
	/****************************************************************/
	/* メイル・ボックス作成											*/
	/****************************************************************/
	MAN_InitializeMailBox();
	/****************************************************************/
	/* タスク変数の初期化											*/
	/****************************************************************/
	MAN_InitializeTaskValue();
	/****************************************************************/
	/* PowerOn時の大域変数の初期化									*/
	/****************************************************************/
	MAN_InitializeRAM();

#if (PRO_PRINT_TYPE == LED)
	/* バックアップＲＡＭが壊れていた時、ドラム交換エラーを出さないため By M.Tachibana 1998/07/09 */
	if ((CheckerMode == 0x70) || (CheckerMode == 0x71)) {
		CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア */
	}
#endif

	/****************************************************************/
	/* PowerOn時のデバイスの初期化									*/
	/****************************************************************/
	MAN_InitializeDevice2();
	/****************************************************************/
	/* 待機状態で動作しているタスク生成								*/
	/****************************************************************/
	MAN_InitializeTaskCreate2();
	/****************************************************************/
	/* アナログファンクションチェッカーの時					        */
	/****************************************************************/
	if (CheckerMode == 0x00) {
		AnalogFunctionCheckerMain();
	}
	/****************************************************************/
	/* ＣＣＤチェッカーの時									        */
	/****************************************************************/
	if (CheckerMode == 0x90) {
		CheckShading();
	}
	/****************************************************************/
	/* ＦＢＳ ＡＳＳＹ検査の時                                      */
	/****************************************************************/
#if (PRO_FBS == ENABLE)		/* POPLAR_B用	1997/01/21 T.Nose */
	if (CheckerMode == 0x10) {
		SCN_Init();
		LampOn();
		SCN_SetMotorDrive(SCN_FBS);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
		MirrorTaskRequest = TRUE;
	}
#endif
#if (PRO_CLASS1 == ENABLE)
	/****************************************************************/
	/* ANZU_L用自動検査ロムの時 M.Kotani 1997/12/19                 */
	/****************************************************************/
	if (CheckerMode == 0x80) {
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferLow[0] = 'R';
		FunctionDisplayBufferLow[1] = 'S';
		FunctionDisplayBufferLow[2] = '2';
		FunctionDisplayBufferLow[3] = '3';
		FunctionDisplayBufferLow[4] = '3';
		FunctionDisplayBufferLow[5] = '2';
		FunctionDisplayBufferLow[6] = 'C';
		FunctionDisplayBufferLow[7] = ':';
		/* RS-232C速度19200
		** RS-232Cキャラクタービット８
		** RS-232Cパリティなし
		** RS-232Cストップビット１
		*/
		SYB_SettingStatus[5] = 0x0e;
		Class1InitVar();
		FunctionDisplayBufferLow[8] = 'N';
		FunctionDisplayBufferLow[9] = 'G';
		RsTestMode = 0x03;	/* 折り返しテスト */
		RsTestChar = RsTestMode;	/**	テスト用キャラクタ＝？をセット	**/
		if (RsOpen('t', 'c', 60) == 1) {
			if ( RsClose('t') == 1) {		/**	テスト終了を待つ	**/
				FunctionDisplayBufferLow[8] = 'O';
				FunctionDisplayBufferLow[9] = 'K';
			}
		}
		DisplayStringLow(0, FunctionDisplayBufferLow);
		/*拡張メモリ*/
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0] = 'E';
		FunctionDisplayBufferHigh[1] = 'X';
		FunctionDisplayBufferHigh[2] = 'M';
		FunctionDisplayBufferHigh[3] = 'E';
		FunctionDisplayBufferHigh[4] = 'M';
		FunctionDisplayBufferHigh[5] = ':';
		CMN_DisableInterrupt();				/** 割り込み禁止 */
		CheckMemory(CHK_WRITE,0x1200000);	/** チェック IC36 */
		if (CheckMemory(CHK_READ,0x1200000) != OK ) {	/** チェック IC36 */
			FunctionDisplayBufferHigh[6] = 'N';
			FunctionDisplayBufferHigh[7] = 'G';
		}
		else {
			FunctionDisplayBufferHigh[6] = 'O';
			FunctionDisplayBufferHigh[7] = 'K';
		}
		FunctionDisplayBufferHigh[8] = '1';
		CheckMemory(CHK_WRITE,0x1400000);	/** チェック IC36 */
		if (CheckMemory(CHK_READ,0x1400000) != OK ) {	/** チェック IC36 */
			FunctionDisplayBufferHigh[9] = 'N';
			FunctionDisplayBufferHigh[10] = 'G';
		}
		else {
			FunctionDisplayBufferHigh[9] = 'O';
			FunctionDisplayBufferHigh[10] = 'K';
		}
		FunctionDisplayBufferHigh[11] = '2';
		CheckMemory(CHK_WRITE,0x1600000);	/** チェック IC36 */
		if (CheckMemory(CHK_READ,0x1600000) != OK ) {	/** チェック IC36 */
			FunctionDisplayBufferHigh[12] = 'N';
			FunctionDisplayBufferHigh[13] = 'G';
		}
		else {
			FunctionDisplayBufferHigh[12] = 'O';
			FunctionDisplayBufferHigh[13] = 'K';
		}
		FunctionDisplayBufferHigh[14] = '3';
		CheckMemory(CHK_WRITE,0x1800000);	/** チェック IC36 */
		if (CheckMemory(CHK_READ,0x1800000) != OK ) {	/** チェック IC36 */
			FunctionDisplayBufferHigh[15] = 'N';
			FunctionDisplayBufferHigh[16] = 'G';
		}
		else {
			FunctionDisplayBufferHigh[15] = 'O';
			FunctionDisplayBufferHigh[16] = 'K';
		}
		FunctionDisplayBufferHigh[17] = '4';
		CMN_EnableInterrupt();
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		while (1) {
		}
	}
#endif
	/****************************************************************/
	/* 最初のディスプレイの更新										*/
	/****************************************************************/
	/* For Checker By M.Tachibana 1997/09/09 */
	if ((CheckerMode == 0x70) || (CheckerMode == 0x71)) {
		UpdateDisplay();
	}

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/05/26 Y.Murata */
	/* 自動ラムクリアおよびオプションが変更された時オプションモデムのティーチングバッファをクリアします */
	if (SYS_AutoBackUpRAM_Clear == 1) {
		SYS_AutoBackUpRAM_Clear = 0;
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_DRD_TEADCHING_BUF);
	}
#endif

	if (debug_anzu) {
		/* デバック中！！ */
		MAN_Anzudebug();
	}

	/****************************************************************/
	/* ここからメインタスクのいっちゃん大きなル－プヘ入ります		*/
	/****************************************************************/
	while (1)  {
		rcv_msg(mbxno.MAN_Task, &MessageControl); /** タスクからメッセージ受信 */
		Item = MessageControl->Item;
		Message = MessageControl->Message;
		SubMessage1 = MessageControl->SubMessage1;
		SubMessage2 = MessageControl->SubMessage2;
		SubMessage3 = MessageControl->SubMessage3;
		SubMessage4 = MessageControl->SubMessage4;

		switch (Item) { /** メッセージ解析*/
#if (PRO_DOC_IN == ENABLE)
		/****************************************************************/
		/* 原稿繰り込みタスクからのメッセージ処理						*/
		/****************************************************************/
		case FROM_DOCUMENT_IN: /** 繰り込みタスク終了処理 */
			MAN_FromDocumentIn(Item, Message, SubMessage1, SubMessage2);
			break;
#endif
		/****************************************************************/
		/* ギア・バック・ラッシュタスクからのメッセージ処理				*/
		/****************************************************************/
		case FROM_SCN_GEAR_BACK_LASH_TASK:
			MAN_FromSCN_GearBackLashTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 原稿蓄積タスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_DOCSTORE: /** 原稿蓄積タスク終了処理 */
			MAN_FromDocStore(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* リスト・プリント・タスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_PRN_LST_PRINT_TASK:
			MAN_FromPRN_LST_PrintTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* メモリ・プリント・タスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_PRN_IMAGE_PRINT_TASK:
			MAN_FromPRN_ImagePrintTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* プリンターリセットタスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_PRN_RESET_TASK:
			MAN_FromPRN_ResetTask(Item, Message, SubMessage1, SubMessage2);
			break;
#if (PRO_PRINT_TYPE == LED)
		/****************************************************************/
		/* プリンタウォームアップタスクからのメッセージ処理				*/
		/****************************************************************/
		case FROM_PRN_WARMUP_TASK:
			MAN_FromPRN_WarmUpTask(Item, Message, SubMessage1, SubMessage2);
			break;
#endif
		/****************************************************************/
		/* 連続プリントタスクからのメッセージ処理						*/
		/****************************************************************/
		case FROM_PRN_ALLPAGE_PRINT_TASK:	/* By H.Y 1994/06/29 */
			MAN_FromPRN_AllPagePrintTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* センサー・タスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_SENSOR:
			MAN_FromSensor(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* タイマー・タスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_TIMER: /* タイマー・タスクからのメッセージ処理 */
			MAN_FromTimer(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 待機状態回線監視タスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_NCU_TASK:
		/****************************************************************/
		/* 多機能電話制御タスクからのメッセージ処理						*/
		/****************************************************************/
		case FROM_NCU_TELEPHONEOPERATIONTASK:
		/****************************************************************/
		/* ダイアル・イン着信後処理										*/
		/****************************************************************/
#if (PRO_DIALIN == ENABLE)
		case FROM_NCU_DIALINAUTOSWITCHTASK:
#endif
			MAN_FromNCU_Task(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* オペレーション・タスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_OPERATION:
			MAN_FromOperation(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 通信タスクからのメッセージ処理								*/
		/****************************************************************/
		case FROM_FAXCOM:
			MAN_FromFaxcom(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 原稿排出タスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_DOCUMENT_OUT:
			MAN_FromDocumentOut(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* スタンプ・テストタスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_SCN_STAMP_TEST_TASK:
			/* 済スタンプテスト */
			MAN_FromSCN_StampTestTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 原稿排出テストタスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_DOC_OUT_TEST_TASK:
			/* 原稿排出テスト */
			MAN_FromSCN_DocOutTestTask(Item, Message, SubMessage1, SubMessage2);
			break;
		/****************************************************************/
		/* 表示用タイマーからのメッセージ処理							*/
		/****************************************************************/
		case FROM_10MS_TIMER:
			MAN_From10msTimer(Item, Message, SubMessage1, SubMessage2);
			break;
#if (PRO_CLASS1 == ENABLE)
		/****************************************************************/
		/*	ＣＬＡＳＳ１タスクからのメッセージ処理						*/
		/****************************************************************/
		case FROM_CLASS1:
			MAN_FromClass1(Item, Message, SubMessage1, SubMessage2);
			break;
#endif	/* #if (PRO_CLASS1 == ENABLE) */
#if (PRO_CLASS1 == ENABLE)
		/****************************************************************/
		/* ＣＬＡＳＳ１通信タスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_CL1_FAXCOM:
			MAN_FromCL1Faxcom(Item, Message, SubMessage1, SubMessage2);
			break;
#endif	/* #if (PRO_CLASS1 == ENABLE) */
#if (PRO_PC_PRINT == ENABLE)		/* By J.Miyazaki 1996/08/09 */
		/****************************************************************/
		/* ＤＰＲＡＭリモート関数実行タスクからのメッセージ処理			*/
		/****************************************************************/
		case FROM_DPR_REMOTEFUNCEXECTASK:
			MAN_FromDPR_RemoteFuncExecTask(Item, Message, SubMessage1, SubMessage2);
			break;
#endif	/* #if (PRO_PC_PRINT == ENABLE) */
#if (PRO_PRINT_TYPE == LASER) /** TEST TEST */
		/****************************************************************/
		/* テスト用のメッセージ処理										*/
		/****************************************************************/
		case FROM_TEST_TEST:
			MAN_FromTestTest(Item, Message, SubMessage1, SubMessage2);
			break;
#endif	/* #if (PRO_PRINT_TYPE == LASER) */
		case FROM_UPDATE_DISPLAY:	/* By H.Y 1994/11/26 */
			break;
#if (PRO_FBS == ENABLE)		/* POPLAR_B用	1997/01/21 T.Nose */
		case FROM_SCN_MIRROR_MOVE_TASK:
			MAN_FromSCN_MirrorMoveTask(Item, Message, SubMessage1, SubMessage2);
			break;
#endif	/* (PRO_FBS == ENABLE) */
#if (PRO_MULTI_LINE == ENABLE)	/* 1996/11/08 Y.Murata */
		/****************************************************************/
		/* マルチ回線監視からのメッセージ処理							*/
		/****************************************************************/
		case FROM_FAXCOM_OPTION:
			MAN_FromFaxcomOption(Item, Message, SubMessage1, SubMessage2, SubMessage3, SubMessage4);
			break;
#endif
		/****************************************************************/
		/* マルチタイマーからのメッセージ処理							*/
		/****************************************************************/
		case FROM_MULTI_TIMER:
			MAN_FromMultiTimer(Item, Message, SubMessage1, SubMessage2);
			break;
#if (PRO_ROTATE == ENABLE)
		/****************************************************************/
		/* 回転受信タスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_ROT_TASK:
			MAN_FromROT_Task(Item, Message, SubMessage1, SubMessage2);
			break;
#endif
		default:	/* End Of Switch(Item) */
			break;
		} /* End of メッセージの解析switch */
		/****************************************************************/
		/* メインループのメッセージ処理以外								*/
		/* 各種プリントの起動処理										*/
		/* 発信スケジューラのチェック									*/
		/****************************************************************/
		MAN_AfterMessageCheck();
		/****************************************************************/
		/* Update LCD Display					Mar.10,1994				*/
		/****************************************************************/
		/* For Checker By M.Tachibana 1997/09/09 */
		if ((CheckerMode == 0x70) || (CheckerMode == 0x71)) {
			UpdateDisplay2();
		}
	} /* End OF WHILE(1) LOOP */
}


/*************************************************************************
	module		:[メインループのメッセージ処理以外]
	function	:[
		1.	各種プリントの起動処理
		2.	発信スケジューラのチェック
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コンパイル時の"out of heap space"解消のために
		メインタスクのループの中のメッセージ解析部分の後
		の処理を抜き出しました。（銀杏にあわせました）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/14]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_AfterMessageCheck( void )
{
	MESSAGE_t	MainTaskMessage;
	UWORD	i, j;
	UBYTE	number_of_okey; /** 通信終了後のＯＫ通信の数 */
	UBYTE	a;
	UBYTE	line_number;	/* For Debug By O.Kimoto 1996/12/13 */
	UBYTE	dial_kind;
	UBYTE	file_item;

	MainTaskMessage.Item = FROM_MAIN;

	if ((CheckerMode != 0x70) && (CheckerMode != 0x71)) {	/* By M.Tachibana 1998/03/31 */

#if (PRO_FBS == ENABLE)

	/** ミラータスクの起動要求があれば、起動条件を判断してここで起動する */
	if ((MirrorTaskRequest)
	 /* && (!SYB_ScannerTransportMode) */
	 && (tskno_SCN_GearBackLashTask == 0xffff)	/* バックラッシュとの排他制御  1997/05/10 s.takeuchi */
	 && (tskno_SCN_MirrorMoveTask == 0xffff)) {
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {	/* ミラーエラー中 */
			MirrorTaskRequest = FALSE;
		}
		else if ((MirrorTaskInstruction == MIRROR_TASK_TO_ADF)
		||	(MirrorTaskInstruction == MIRROR_TASK_TO_FBS)
		||	(MirrorTaskInstruction == MIRROR_TASK_FCOT_READY)) {	/* 読み取り位置への移動要求の場合 */
			MirrorTaskRequest = FALSE;
			SCN_MirrorTaskControl = MirrorTaskInstruction;	/* 動作要求をタスクへの指示変数にコピー */
			/* SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;	1997/01/10 */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MIRROR_BUSY;

			/* ADF読み取り前の準備中表示のため  1997/03/05 s.takeuchi */
			if ((SCN_MirrorTaskControl == MIRROR_TASK_TO_ADF)
			 || (SCN_MirrorTaskControl == MIRROR_TASK_TO_FBS)) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_PREPARATION_ADF;
			}

			cre_tsk( &tskno_SCN_MirrorMoveTask, TSK_SCN_MIRRORMOVETASK, 0 );
		}
		else {		/* その他の場合は、ギアバックラッシュを優先 */
			if (!(GearBackLashRequest)
			&&	(tskno_SCN_GearBackLashTask == 0xffff)) {
				MirrorTaskRequest = FALSE;
				/* 輸送用の固定位置への移動の時はミラー初期化中も立てる	 1996/12/10 */
				if (MirrorTaskInstruction == MIRROR_TASK_TRANSPORT) {
					SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MIRROR_INIT;
				}
				SCN_MirrorTaskControl = MirrorTaskInstruction;	/* 動作指示をタスクへの指示変数にコピー */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MIRROR_BUSY;
				cre_tsk( &tskno_SCN_MirrorMoveTask, TSK_SCN_MIRRORMOVETASK, 0 );
			}
		}
	}
#endif /* (PRO_FBS == ENABLE) */

	/**	ギアバックラッシュの起動要求があれば、起動条件を判断してここで起動する
	**	※このifブロックの前で必ずMirrorTaskRequestを見ておくこと
	*/
	if ((GearBackLashRequest)
#if (PRO_FBS == ENABLE)
	 && (tskno_SCN_MirrorMoveTask == 0xffff)	/* ミラーとの排他制御  1997/05/09 s.takeuchi */
	 && (!SYB_ScannerTransportMode)
#endif
	 && (tskno_SCN_GearBackLashTask == 0xffff)) {	/* 二重create対策  1997/05/09 s.takeuchi */
		if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)
		||	(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_FEED_IN|SYS_FEED_OUT))) {
			GearBackLashRequest = FALSE;	/* 起動要求をキャンセル */
		}
#if (PRO_FBS == ENABLE)
		else if ((MirrorTaskRequest)											/* ADF読み取り終了直後 */
		||	(!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY))) 	/* その他、待機中など */
#else
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)) 	/* 待機中 */
#endif
		{
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
			GearBackLashRequest = FALSE;

			/* ギアバックラッシュ中にSCANNER_BUSYをクリアさせないため追加  1997/05/10 s.takeuchi */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_GEAR_BACKLASH;

			/* タイムアウトの初期化、再起動処理  1997/05/09 s.takeuchi */
			CMN_DisableInterrupt();
			GearBackLashTimeout = FALSE;
			GearBackLashTimer = 100;		/* タイマ初期化(10msタイマで減算) */
			if (GearBackLashRetryCount == 0) {
				GearBackLashRetryCount = 3;	/* 最初の起動ならリトライカウンタを初期化 */
			}
			else {
				GearBackLashRetryCount--;	/* リトライでの起動ならカウンタを減算 */
			}
			CMN_EnableInterrupt();

			/* SCN_Init();  ギアバックラッシュタスク側へ移動  1997/05/09 */
			cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
		}
		/* ミラーが未使用になるまでは、起動要求を保留 */
	}

	}		/* By M.Tachibana 1998/03/31 */


	if (CheckerMode == 0x71) {	/* By M.Tachibana 1998/03/31 */
		/* ジャムアクセスカバーを閉じた */
		if (CMN_CheckPrintEnable(SYS_MULTI_COPY)) {
			if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2)) {
				/* 強制的にステータスをＥＭＰＴＹにして管理テーブルを再セットする */
				for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
					SYB_MultiCopyFile[i].Status = SYS_MCOPY_EMPTY;
				}
				ImagePrintTest();
			}
		}
	}

	/****************************************************************/
	/* Launch Multi Copy Doc Print									*/
	/* マルチ・コピー・プリント起動／再起動							*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_MULTI_COPY)) {
		if (CMN_CheckMultiCopyPrintEnable()) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_MULTI_COPY; /* Multi Copy使用中セット */
			SYS_DocumentPrintItem	= SYS_MEM_MULTI_COPY_FILE;
			SYS_DocumentPrintNo		= SYB_MultiCopyReadPoint;
			SYS_DocumentPrintPageNo = SYB_MultiCopyFile[SYB_MultiCopyReadPoint].PrintPage;
			/*----------------------------------------------------------------------------------*/
			/* 部数指定の印字原稿最終ページの印字直前でプリンターのエラー等で停止している場合	*/
			/* プリンターのエラー解除後に印字した原稿は最終ページのみ一部多く印字されてしまう。 */
			/* Aug.22,1994 SYS_DocumentPrintClass  = SYS_PRINT_CLASS; */
			/*----------------------------------------------------------------------------------*/
			SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
			if (tskno_PRN_ImagePrintTask != 0xffff) {
				SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
			}
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
		}
	}

/******************************************************************************************************************
** チェッカーでＲＯＭがあふれるためにリストをリンクしないのでリスト起動するパスを削除する M.Tachibana 97/10/24
*********************** CHECKER ************************************************************************************
*/

#if 0

#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 連続ポーリング機能追加 1996/10/17 Eguchi */
	if ((SYB_ContinuousPolling.Status == SYS_CMD_WAITING) && (SYB_ContinuousPolling.EndTime < SYB_CurrentTime)) {
	/* 連続ポーリングコマンドの登録状況が予約中で、かつ終了時刻が過ぎている時 */
		CancelExecQueue(SYS_CONTINUOUS_POLLING, 0);	/* キューは残っていないはずだが念のため */

		/* 連続ポーリングの標準の仕様は、設定した時間で１日だけ実行するようにします  97'09/03 by K.Watanabe */
		if (!CHK_UNI_ContPollingDaily()) {	/* 連続ポーリングを、１日で停止する時 */
			SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;	/* 連続ポーリングコマンドをクリアする */
		}
		else {								/* 連続ポーリングを、コマンドファイルが消去されるまで行う時 */
			/* ＭＢＳより、連続ポーリングの仕様変更の要求があった。
			** 変更内容は、
			**   現状：StartTimer から End Timeまでの間、連続してPollingを実行し、End Timeを過ぎるとコマンド消去
			**   変更：StartTimer から End Timeまでの間、連続してPollingを実行し、End Timeを過ぎると１日後に予約中
			** よって、従来コマンド消去していたところで、Start TimeとEnd Timeにそれぞれ１日分（２４時間）進め
			** 予約中にする。
			** By O.Kimoto 1997/04/30
			*/
			MAN_CalcContPollingExecTime();
			SYB_ContinuousPolling.Status = SYS_CMD_WAITING;
		}
	}
#endif

	/****************************************************************/
	/* 通信予約のスケジューリング									*/
	/* FAX Communication Re-Schejuling Jan.8,1994					*/
	/****************************************************************/
	SetCommandToExec();
#if (PRO_BATCH_TX == ENABLE)
	SetBatchCommandToExec();
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 連続ポーリング機能追加 1996/10/17 Eguchi */
	SetContinuousPollingToExec();		/** 連続ポーリングコマンドをキューに展開 */
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 回線選択処理 By O.Kimoto 1996/11/23 */
	line_number = OPT_JudgeSelectLine();
#else
	line_number = 0;	/* １回線仕様 */
#endif
	if (line_number == 0xF0) {
		/* 実行すべきキューが存在しませんでした。 */
		SYS_CurrentExecQueueNo = (UBYTE)SYB_ExecQueueReadPoint;
	}
	else if(line_number == 0xFF) {
		/* ここへ来たということは下記のエラーのいずれかが発生したということです。
		** Ｄ．０．１０ 発呼出来る回線が１つもなかった
		** Ｄ．０．１１ スーパーＧ３で発呼する為の回線が１つも無い
		** Ｄ．０．１２ 番号：内線専用、回線設定：外線設定の為、発呼出来ず
		** Ｄ．０．１３ 番号：外線専用、回線設定：内線設定の為、発呼出来ず
		** by O.Kimoto 1997/01/22
		*/
		SYS_NextQueueVariableTimer = 1;	/*２回線仕様では必要 */ /* Add By O.Kimoto 1997/01/22 */
	}
	else if ((line_number & ~INTERNAL_NUMBER) == 0) {
		/** 内蔵回線でした。 */

		dial_kind = (UBYTE)(line_number & INTERNAL_NUMBER);
		line_number &= ~INTERNAL_NUMBER;

		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
			&& CMN_CheckAutoDialEnable() ) {						/* By T.O Jun.07.1994					  */
			SYS_CurrentExecQueueNo = (UBYTE)GetNextExecNo();
			if ( SYS_CurrentExecQueueNo < SYS_EXEC_QUEUE_MAX)  {
				if (tskno_NCU_Task != 0xffff) {
					del_tsk(&tskno_NCU_Task);/* Add J.M 1994/05/12 */
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 通信使用中セット */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);/* CI検出中クリア */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM; /* FAXCOM動作中セット */

				if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_COMMAND_TRX) {	/* add if() 1997/03/06 Y.Murata */
					if (CheckScannerCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) { /* スキャナ－・コマンドかを確認 */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナー使用中セット */
					}

					if (CheckPollingRxCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) {
						/* ﾎﾟｰﾘﾝｸﾞ受信及び受領証受信時に代行受信ｷｰﾌﾟﾅﾝﾊﾞｰを覚えておく */
						/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); */
						SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
						if (SYB_MemoryRxPrintWritePoint == 0xFF) {
							SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
						}
					}
					if (((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x03) == 0x03)
					  ||((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x80) == 0x80)) {	/* 受領証 */
						/* 1997/01/25 Y.Murata
						 * ﾎﾟｰﾘﾝｸﾞ受信及び受領証受信時に代行受信ｷｰﾌﾟﾅﾝﾊﾞｰを覚えておくのを忘れてた ﾎｽﾄ回線のみ
						*/
						/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); */
						SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
						if (SYB_MemoryRxPrintWritePoint == 0xFF) {
							/* Nothing */
						}
					}
				}
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング 1997/03/06 Y.Murata */
				if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_CONTINUOUS_POLLING) {
					/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); */
					SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
					if (SYB_MemoryRxPrintWritePoint == 0xFF) {
						SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
					}
				}
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 回線選択処理 By O.Kimoto 1996/11/23 */
				/* 個別属性セーブ 1997/01/27 Y.Murata */
				SYS_FaxComAbility0[0] = SYS_WorkAbility0;
				SYS_FaxComAbility1[0] = SYS_WorkAbility1;
				SYS_FaxComAbility2[0] = SYS_WorkAbility2;
				SYS_FaxComAbility3[0] = SYS_WorkAbility3;
#endif
				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
				SYB_ExecQueue[SYS_CurrentExecQueueNo].StackNumber = 0;
				SYB_ExecQueue[SYS_CurrentExecQueueNo].Option |= dial_kind;	/*  By O.Kimoto 1996/12/26 */
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = SYS_COMMAND_EXECUTE;
				MainTaskMessage.SubMessage1 = SYS_CurrentExecQueueNo; /* コマンド番号 */
				snd_msg(mbxno.FCM_Task, &MainTaskMessage); /* 通信タスクへ起動パラメーターを通知*/
			}
			else { /* By S.K 7/15/1994 */
				SYS_CurrentExecQueueNo = (UBYTE)SYB_ExecQueueReadPoint;
			}
		}
	}
	else if (((line_number & ~INTERNAL_NUMBER) >= 1) && ((line_number & ~INTERNAL_NUMBER) <= 8)) {
#if (PRO_MULTI_LINE == ENABLE)	/* 回線選択処理 By O.Kimoto 1996/11/23 */
		/* ２回線仕様でここの処理追加すること */
		/** 外付け回線でした。 */
		dial_kind = (unsigned char)(line_number & INTERNAL_NUMBER);
		line_number &= ~INTERNAL_NUMBER;

		if (CHK_SelectedLineEnable(line_number) && (SYS_MltVariableTimer[line_number] == 0)) {
			MAN_OptionModemStart((unsigned char)line_number);
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;

			if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_COMMAND_TRX) {	/* add if() 1997/03/06 Y.Murata */
				if (CheckScannerCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) { /* スキャナ－・コマンドかを確認 */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナー使用中セット */
					SYS_Opt[line_number].SYS_FaxComTxType = SYS_SCANNER_TX;
				}
				else {
					SYS_Opt[line_number].SYS_FaxComTxType = SYS_MEMORY_TX;
				}
			}
			else {
				SYS_Opt[line_number].SYS_FaxComTxType = SYS_MEMORY_TX;
			}
			SYS_Opt[line_number].SYS_FaxComType = SYS_COMMAND_EXECUTE;
			if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Status == SYS_EXEC_FORWARD_WAITING) {	/** 転送予約中 */
				SYB_ExecQueue[SYS_CurrentExecQueueNo].Status = SYS_EXEC_FORWARD_EXECUTE;		/** 転送実行中 */
			}
			else {
				SYB_ExecQueue[SYS_CurrentExecQueueNo].Status = SYS_EXEC_EXECUTE;		/** 実行中 */
			}

			if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_COMMAND_TRX) {	/* add if() 1997/03/06 Y.Murata */
				/*if (MAN_CheckPollingCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) {*/
				if (CheckPollingRxCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) {
					if (MAN_GetMultiLineReceiveNumber((unsigned char)line_number) == 0xFFFF) {
						/*
						 * ｷｭｰ獲得の時にｺﾏﾝﾄﾞの空きをﾁｪｯｸしているのでここでは獲得だけ行う
						 * 代行受信管理ﾃｰﾌﾞﾙの獲得はﾒｲﾝでし行わないので、ここで獲得できないと言う
						 * 事は絶対ありえない
						*/
						outp((unsigned long)0,(unsigned char)0);/* WriteProtectError for ICE */
					}
				}
				if (((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x03) == 0x03)
				|| ((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x80) == 0x80)) {	/* 受領証 */
					if (MAN_CheckMultiLineReceiveEnable((unsigned char)line_number,AUTO_RECEIVE) == 0xFFFF) {
						/* Nothing */
					}
				}
			}

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング 1997/03/06 Y.Murata */
			if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_CONTINUOUS_POLLING) {
				if (MAN_GetMultiLineReceiveNumber((unsigned char)line_number) == 0xFFFF) {
					/*
					 * ｷｭｰ獲得の時にｺﾏﾝﾄﾞの空きをﾁｪｯｸしているのでここでは獲得だけ行う
					 * 代行受信管理ﾃｰﾌﾞﾙの獲得はﾒｲﾝでし行わないので、ここで獲得できないと言う
					 * 事は絶対ありえない
					*/
					outp((unsigned long)0,(unsigned char)0);/* WriteProtectError for ICE */
				}
			}
#endif

			SYB_ExecQueue[SYS_CurrentExecQueueNo].StackNumber = line_number;
			SYB_ExecQueue[SYS_CurrentExecQueueNo].Option |= dial_kind;	/* Add By O.Kimoto 1996/12/26 */
			/* 個別属性セーブ 1997/01/27 Y.Murata */
			SYS_FaxComAbility0[line_number] = SYS_WorkAbility0;
			SYS_FaxComAbility1[line_number] = SYS_WorkAbility1;
			SYS_FaxComAbility2[line_number] = SYS_WorkAbility2;
			SYS_FaxComAbility3[line_number] = SYS_WorkAbility3;
			DPR_AutoFax((UWORD)(line_number-1));
		}

#endif
	}

#if (PRO_PRINT_TYPE == LED)
	/****************************************************************/
	/* 手差しコピー・プリント起動／再起動							*/
	/****************************************************************/
	if (CMN_CheckManualCopyPrintEnable()) {
		if (CMN_CheckManualCopyPrintEnable()) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_MANUAL_COPY_DOC_OPR;	/*要検討*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_MANUAL_COPY;
			SYS_DocumentPrintItem	= SYS_MEM_MANUAL_COPY_FILE;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = SYB_ManualCopyFile.PrintPage;
			SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
			if (tskno_PRN_ImagePrintTask != 0xffff) {
				SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
			}
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* メモリ・プリント・タスク起動 */
		}
	}
#endif
	/****************************************************************/
	/* Launch Multi Copy Doc Print									*/
	/* マルチ・コピー・プリント起動／再起動							*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_MULTI_COPY)) {
		if (CMN_CheckMultiCopyPrintEnable()) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_MULTI_COPY; /* Multi Copy使用中セット */
			SYS_DocumentPrintItem	= SYS_MEM_MULTI_COPY_FILE;
			SYS_DocumentPrintNo		= SYB_MultiCopyReadPoint;
			SYS_DocumentPrintPageNo = SYB_MultiCopyFile[SYB_MultiCopyReadPoint].PrintPage;
			/*----------------------------------------------------------------------------------*/
			/* 部数指定の印字原稿最終ページの印字直前でプリンターのエラー等で停止している場合	*/
			/* プリンターのエラー解除後に印字した原稿は最終ページのみ一部多く印字されてしまう。 */
			/* Aug.22,1994 SYS_DocumentPrintClass  = SYS_PRINT_CLASS; */
			/*----------------------------------------------------------------------------------*/
			SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
			if (tskno_PRN_ImagePrintTask != 0xffff) {
				SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
			}
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
		}
	}
	/************************************************************/
	/* セキュリティ受信機能追加		1996/04/27 Eguchi			*/
	/************************************************************/
#if (PRO_SECURITY_RX == ENABLE)
	SetSecurityRxMode();
#endif
	/****************************************************************/
	/* メモリ受信原稿回転起動 By M.Kotani 97/03/27					*/
	/****************************************************************/
#if (PRO_ROTATE == ENABLE)
	if (ROT_CheckRotateEnable())	 {
		SYS_MemoryRxRotateReadPoint = (UBYTE)MAN_GetMemoryRxPrintNumber();
		if (SYS_MemoryRxRotateReadPoint < SYS_MEMORY_RX_MAX) {
			MemoryRxRotatePoint = &SYB_MemoryRxPrint[SYS_MemoryRxRotateReadPoint];
			if (MemoryRxRotatePoint->Protect == SYS_PROTECT_OFF) {
				if (DPR_SlaveBoardEnable && DPR_CheckRotateBoardExist()) {	/** 回転オプション基盤装着時 */
					if (MemoryRxRotatePoint->RotatePage <= MemoryRxRotatePoint->StorePage)	 {
						SYS_DocumentRotateItem	= SYS_MEM_RX_FILE;
						SYS_DocumentRotateNo	= SYS_MemoryRxRotateReadPoint;
						SYS_DocumentRotatePageNo = MemoryRxRotatePoint->RotatePage;
						SYS_DocumentRotateClass	= SYS_PRINT_CLASS;
						MAN_RotateIsBusy = 1;
						cre_tsk(&tskno_ROT_Task, TSK_ROT_TASK, 0); /* 原稿回転・タスク起動 */
					}
				}
				else {	/** 回転オプション基盤未装着時 */
					if (MemoryRxRotatePoint->StorePage >= MemoryRxRotatePoint->RotatePage)	 {
						MemoryRxRotatePoint->RotatePage = MemoryRxRotatePoint->StorePage + 1;
						PRN_1PageReceived = 1;
					}
				}
			}
		}
	}
#endif
	/****************************************************************/
	/* Launch Memory Receive Doc Print								*/
	/* メモリ受信原稿プリント起動／再起動							*/
	/****************************************************************/
	/** POPLAR変更 1997/03/07  By T.Yamaguchi */
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT))	 {
		SYB_MemoryRxPrintReadPoint = (UBYTE)MAN_GetMemoryRxPrintNumber();
		if (SYB_MemoryRxPrintReadPoint < SYS_MEMORY_RX_MAX) {
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint];
			if (MemoryRxPrintPoint->Protect == SYS_PROTECT_OFF) {
#if (PRO_ROTATE == DISABLE)	/** 回転受信機能のない時は蓄積ページをプリントする */
				if (MemoryRxPrintPoint->StorePage >= MemoryRxPrintPoint->PrintPage)	 {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
					SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
#else	/** (PRO_ROTATE == ENABLE)回転受信機能のある時は回転ページをプリントする */
				if (MemoryRxPrintPoint->RotatePage > MemoryRxPrintPoint->PrintPage)	 {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
					SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT
						&& MemoryRxPrintPoint->StorePage < MemoryRxPrintPoint->RotatePage) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
#endif
				else { /** 異常状態 */
					/* T.B.D 多分大丈夫 */
				}
			}
		}
	}
	/* 1997/03/07  By T.Yamaguchi */


	/****************************************************************/
	/* Power Down Notice List Print									*/
	/* 停電検出時のリスト・プリント起動								*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /* プリンタ使用状況の確認 */
		if (SYS_ErasePixMemoryListRequest) { /* 停電発生の確認 */
			if ((Check_AnyList(LST_POWEROFF_NOTICE) != MSG_PRN_LST_NO_LIST) /* 消去メッセージの有り無し */
				&& CHK_PowerDownMessagePrint() ) {	/* ﾒﾓﾘSW I-0,SW2 が "1" ならば */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
				SYS_DocumentPrintItem	= LST_POWEROFF_NOTICE;
				SYS_DocumentPrintNo		= 0;
				SYS_DocumentPrintPageNo = 1;
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
			}
			else {
				SYS_ErasePixMemoryListRequest = 0; /* 停電発生初期化 */
				Init_AnyList(LST_POWEROFF_NOTICE);
			}
		}
	}
	/****************************************************************/
	/* Power Down Notice List Print									*/
	/* ＲＡＭ領域初期化通知のプリント起動							*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /* プリンタ使用状況の確認 */
		if (SYS_BackUpRamListRequest) { /* ＲＡＭ初期化要求の確認 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_MRYINIT_CHECKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* Check Message Print											*/
	/* チェックメッセージのプリント起動								*/
	/****************************************************************/
/*.PRO_MONITOR_REPORT == DISABLE（従来のチェックメッセージプリント）の条件部をコメント 1996/10/07 By S.Kawasaki */
#if (PRO_MONITOR_REPORT == ENABLE)
	/* 変更しました 1996/07/26 Eguchi */
	/*----------------------------------------------------------------------*/
	/*	--------------------------------------------						*/
	/*	同報		  |ﾓﾆﾀｰON		 |ﾓﾆﾀｰOFF		|						*/
	/*				  |ﾁｪｯｸ･ﾒｯｾｰｼﾞON |ﾁｪｯｸ･ﾒｯｾｰｼﾞON |						*/
	/*	--------------|--------------|--------------|						*/
	/*	全てＯＫ	  |	 ﾓﾆﾀｰ印字	 |	印字無し	|						*/
	/*	--------------|--------------|--------------|						*/
	/*	一部ＯＫ　　　|	 ﾓﾆﾀｰ印字	 | ﾁｪｯｸ･ﾒｯｾｰｼﾞ	|						*/
	/*	一部ＥＲＲＯＲ|				 |	  印字		|						*/
	/*	--------------|--------------|--------------|						*/
	/*	全てＥＲＲＯＲ|	 ﾓﾆﾀｰ印字	 | ﾁｪｯｸ･ﾒｯｾｰｼﾞ	|						*/
	/*				  |				 |	　印字		|						*/
	/*	--------------------------------------------						*/
	/*----------------------------------------------------------------------*/
	/*
	 *	コマンドファイル番号			：ｊ
	 *　キュー番号						：ｉ
	 *　１コマンド当たりの交信エラー数	：ａ
	 *　１コマンド当たり正常交信数		：number_of_okey
	 */
	/*------------------------------------------*/
	/* コマンド・ファイルのチェック・メッセージ */
	/*------------------------------------------*/
	for (j = 0; j < SYS_COM_FILE_MAX; j++) {
		if (SYB_CommandFile[j].Status == SYS_CMD_EXECUTE) { /** 実行中のコマンド・ファイル有り　コマンド番号＝Ｊ */
			/************************************************/
			/* コマンドに対するキューが全て実行終了している */
			/* か調べる。									*/
			/************************************************/
			for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) { /** ExecQueueを全てスキャン／通信予約の実行中チェック */
				if ((SYB_ExecQueue[i].Status >= SYS_EXEC_WAITING)
				&&	(SYB_ExecQueue[i].Status <	SYS_EXEC_OK)
				&&	(SYB_ExecQueue[i].Number.Command == (UBYTE)j)
				&&	(SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)) { /** コマンド・ファイル */
					break; /** 実行中又は予約中のコマンドがまだ残っている iはSYS_EXEC_QUEUE_MAXに達しない */
						   /** このパスを通らなければi==SYS_EXEC_QUEUE_MAXになる */
				}
			}
			if (i >= SYS_EXEC_QUEUE_MAX) { /** 実行中又は予約中のコマンド無し／コマンド実行終了 */
				/**********************************/
				/* 送信証ＯＮの場合				  */
				/**********************************/
/*				if ((SYB_CommandFile[j].Option.ConfirmationReport == TCR_REQUEST)	*/
				if (((SYB_CommandFile[j].Option.ConfirmationReport & SYS_RCR_REQUESTED) == SYS_TCR_REQUESTED)
				||	((SYB_CommandFile[j].Option.ConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR)) {/** 送信証ＯＮ */
					if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) { /** プリント可能 */
						if (CheckDocStoredCommand((UBYTE )j)
						&&	CHK_DocumentPrintAfterMemTx()  ) { /** メモリー送信コマンドでかつ原稿印字可能  */
							/** 原稿つきの送信証を印字する */
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
							SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
							SYS_DocumentPrintItem = SYS_MEM_TX_FILE;
							SYS_DocumentPrintNo = (UBYTE)j;
							SYS_DocumentPrintPageNo = 1;
							SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MONITOR; /** TCR 印字指定 */
							cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
						}
						else { /**スキャナコマンドまたはメモリー送信で原稿印字不可 */
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
							SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
							SYS_DocumentPrintItem  = LST_MONITOR_REPORT;
							SYS_DocumentPrintNo	= (UBYTE)j;
							SYS_DocumentPrintPageNo = 1;
							SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MONITOR; /** TCR 印字指定 */
							cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** ﾘｽﾄﾌﾟﾘﾝﾄﾀｽｸ起動 */
						}
					}
				}
				/**********************************/
				/*	  送信証ＯＦＦの場合		  */
				/**********************************/
				else { /** チェックメッセージ印字 */
					if (!CHK_CheckMessagePrint()) { /**チェックメッセージ印字しない設定の場合 */
						/** コマンドを消去する */
						CMN_ClearCommandArea(SYS_COMMAND_TRX , (UBYTE)j);
					}
					else {
						/*-----------------------------------------------------*
						 * 交信ＯＫ(number_of_okey)と交信エラー(a)の数を数える
						 *-----------------------------------------------------*/
						a = number_of_okey = 0;
						for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
							if ((SYB_ExecQueue[i].Number.Command == (UBYTE)j)
							&&	(SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)) {
								if (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR) {
									a++; /** 交信エラー数を加算 */
								}
								else if (SYB_ExecQueue[i].Status == SYS_EXEC_OK) {
									number_of_okey++; /** 交信ＯＫ数を加算 */
								}
							}
							if (a >10) { /** エラーの数が１０件以上 */
								break;
							}
						}
						if (number_of_okey > 0 && a == 0) {/** 交信エラーなし */
							/** コマンドをクリア */
							CMN_ClearCommandArea(SYS_COMMAND_TRX , (UBYTE)j);
						}
						else { /** 交信エラーあり */
							if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) { /** プリント可能 */
								if ((i >= SYS_EXEC_QUEUE_MAX) /** ｴﾗｰの数が10件以下 */
								&&	CheckDocStoredCommand((UBYTE)j) /** 指定されたｺﾏﾝﾄﾞ番号がﾒﾓﾘ蓄積ｺﾏﾝﾄﾞ可 */
								&&	CHK_DocumentPrintAfterMemTx()) { /** ﾒﾓﾘ送信時ｴﾗｰ時蓄積原稿ﾌﾟﾘﾝﾄ有効 */
									SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
									SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
									SYS_DocumentPrintItem = SYS_MEM_TX_FILE;
									SYS_DocumentPrintNo = (UBYTE)j;
									SYS_DocumentPrintPageNo = 1;
									SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MEMORY;	/** 原稿付きチェックメッセージ印字指定 */
									cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
								}
								else {/** スキャナコマンドまたはポーリングコマンドまたはエラーが１０件以上 */
									SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
									SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** ﾘｽﾄﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
									SYS_DocumentPrintItem  = LST_COMMERR_CHECKMSG;
									SYS_DocumentPrintNo		= (UBYTE)j;
									SYS_DocumentPrintPageNo = 1;
									SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MEMORY;
									cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** ﾘｽﾄﾌﾟﾘﾝﾄﾀｽｸ起動 */
								}
							}
						}
					}
				}
			}
		}
	}
	/* By H.Y 1994/08/23 追加 ここから */
	/* とりあえず PRO_MONITOR_REPORTがENABLEだけ入れましたが、DISABLEも必要ですので忘れないように */
	/*------------------------------------------*/
	/* 一括送信ファイルのチェック・メッセージ	*/
	/*------------------------------------------*/
	/* 必ずモニタレポートをプリントします		*/
	/*------------------------------------------*/
 #if (PRO_BATCH_TX == ENABLE)
	exit_flag = 0;	/**	共通メモリスイッチで一括送信の送信証を印字しない設定の時、チェックメッセージを印字するしないのフラグ By H.Hirao 1996/07/04 */
	for (j = 0; j < SYS_BATCH_FILE_MAX; j++) {
		if (SYB_BatchTxFile[j].Status == SYS_CMD_EXECUTE) { /** 実行中のコマンド・ファイル有り　コマンド番号＝Ｊ */
			for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) { /** ExecQueueを全てスキャン／通信予約の実行中チェック */
				a = SYB_ExecQueue[i].Status; /** ExecQueueのステータスを保存＝ａ*/
				if ( a == SYS_EXEC_ERROR ) {
					exit_flag = 1;
				}
				if ((a >= SYS_EXEC_WAITING) && /** ExecQueueが予約中 */
					(SYB_ExecQueue[i].Number.Command == (UBYTE)j) && /** ExecQueueのコマンド番号とコマンド・ファイルの番号が一致 */
					(a < SYS_EXEC_OK) && /** ExecQueueが予約中 */
					(SYB_ExecQueue[i].Kind == SYS_BATCH_TX)) { /** 一括送信ファイル */
					break; /** 実行中又は予約中のコマンドがまだ残っている iはSYS_EXEC_QUEUE_MAXに達しない */
						   /** このパスを通らなければi==SYS_EXEC_QUEUE_MAXになる */
				}
			}
			if (i >= SYS_EXEC_QUEUE_MAX) { /** 通信終了済み */
				if (CHK_BatchTxTCR_ON()) { /** 一括送信後、送信証印字する設定の場合 */
					if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem  = LST_COMMERR_BATCH_CHECKMSG;
						SYS_DocumentPrintNo		= (UBYTE)j;
						SYS_DocumentPrintPageNo = 1;
						SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_BA_MONITOR; /** モニター・レポート印字指定 */
						cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
					}
				}
				else { /** 一括送信時、送信証印字しない設定の場合 */
					if ( exit_flag == 1 ) { /** 一括送信後、送信証を印字しない設定の場合、交信エラーならチェックメッセージを印字 By H.Hirao 1996/07/04*/
						if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
							SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** ﾘｽﾄﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
							SYS_DocumentPrintItem  = LST_COMMERR_BATCH_CHECKMSG;
							SYS_DocumentPrintNo		= (UBYTE)j;
							SYS_DocumentPrintPageNo = 1;
							SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_BA_MONITOR;
							cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** ﾘｽﾄﾌﾟﾘﾝﾄﾀｽｸ起動 */
						}
					}
					else {
						CMN_ClearCommandArea(SYS_BATCH_TX, (UBYTE)j); /** 一括送信コマンドのクリア */
					}
				}
			}
		}
	}
 #endif
#endif
	/****************************************************************/
	/* 手動送受信チェックメッセージのプリント						*/
	/****************************************************************/
	/** TCR ONの時は手動送信チェックメッセージを印字しない Add By H.Hirao 1996/06/24 */
	exit_flag = 0;
	for (j = 0; j < SYS_JOURNAL_MAX; j++) {
		if ( (SYB_JournalFile[j].Kind == SYS_MANUAL_TRANSMIT)
		  && (SYB_JournalFile[j].Option & SYS_TCR_REQUEST) ) { /** 送信証プリント要求の確認 */
			exit_flag = 1;
			break;
		}
	}
	if ( !exit_flag && CMN_CheckPrintEnable(SYS_LIST_PRINT) ) { /** TCR要求無しの条件追加 By H.Hirao 1996/06/24 */
	/* if (CMN_CheckPrintEnable()) { */ /** プリンタ使用状況の確認 */
		if (SYS_ManualFaxCommErrRequest) { /** 手動送受信チェックメッセージ・プリント要求の確認 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_MNLERR_CHECKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* 手動送信送信証のプリント										*/
	/* 手動送信はコマンドファイルがないのでここで送信証を起動する	*/
	/* ジャーナルファイルの送信証の要求はリストプリント終了時に消去 */
	/* します							Add By H.Hirao 1996/06/24	*/
	/****************************************************************/
	if ( exit_flag && CMN_CheckPrintEnable(SYS_LIST_PRINT) ) { /** TCR要求有り && プリンタ使用状況の確認 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
		SYS_DocumentPrintItem	= LST_MANUAL_TXCONF_REPORT;
		SYS_DocumentPrintNo		= 0;
		SYS_DocumentPrintPageNo = 1;
		cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
	}
	/****************************************************************/
	/* 親展受信通知のプリント										*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		for (i = 0; i < SYS_MAILBOX_MAX; i++) {
			if (SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE &&
				SYB_MailBox[i].MessageStatus == SYS_MAILBOX_RCV_MSG) { /** 親展受信通知プリント要求の確認 */
				break;
			}
		}
		if (i < SYS_MAILBOX_MAX)  {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_SECURERCV_NOTICE;
			SYS_DocumentPrintNo		= (UBYTE)i;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* 親展受信消去通知のプリント									*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		for (i = 0; i < SYS_MAILBOX_MAX; i++) {
			if ((SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE) &&
				(SYB_CurrentTime >= SYB_MailBox[i].ErasedTime)) { /** 親展受信消去通知プリント要求の確認 */
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_ERASED_MSG;
				break;
			}
		}
		if (i < SYS_MAILBOX_MAX) {
			/* ここで親展受信原稿を消去するように変更 */
			MEM_ClearDocAndFATArea( (UBYTE)SYS_MEM_SECURE_RX_FILE, (UWORD)i, MEM_IGNORE_BOX_NUMBER);	/* 1994/11/26 Y.Murata */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DELSECURE_NOTICE;
			SYS_DocumentPrintNo		= (UBYTE)i;	/** 現状の仕様では無意味 TBD */
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
#if (PRO_F_CODE == ENABLE)	/* 1997/01/31  By T.Yamaguchi */
	/****************************************************************/
	/* サブアドレス受信原稿通知のプリント							*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		for (i = 0;i < SUB_ADDRESS_BOX_MAX;i++) {
			if ( (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY)	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			   &&((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE)	/* 受信原稿あり */
				||(SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED))	/* 受信中に蓄積した */
			   &&(SYB_SubAddressBoxTable[i].MessageStatus == SYS_SUB_ADDRESS_BOX_RCV_MSG) ) {	/* ｻﾌﾞｱﾄﾞﾚｽBOX受信通知ﾌﾟﾘﾝﾄ要求 */
				break;
			}
		}
		if (i < SUB_ADDRESS_BOX_MAX)  {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_FCODE_BOXRCV_NOTICE;
			SYS_DocumentPrintBoxNumber = (UBYTE)(i + 1);					/*	 ＢＯＸ番号 */
			SYS_DocumentPrintNo		= (UBYTE)(SYB_SubAddressBoxTable[i].RxStoringNo);	/* 受信ファイル番号がはいる */
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* サブアドレス蓄積原稿消去通知のプリント									*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		for (i = 0;i < SUB_ADDRESS_BOX_MAX;i++) {
			if ((SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY)		/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			  &&(SYB_SubAddressBoxTable[i].StoredDocBit)	/* 受信原稿あり */
			  &&(SYB_CurrentTime >= SYB_SubAddressBoxTable[i].ErasedTime) ){	/* ｻﾌﾞｱﾄﾞﾚｽBOX受信消去通知ﾌﾟﾘﾝﾄ要求の確認 */
				break;
			}
		}
		if (i < SUB_ADDRESS_BOX_MAX) {
			if (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_BULLETIN_BOX) {
				file_item = SYS_MEM_SUB_BULLETIN_FILE;
			}
			else if (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_SECURE_BOX) {
				file_item = SYS_MEM_SUB_SECURE_FILE;
			}
			MEM_ClearDoc(file_item, MEM_ALL_NO, (UBYTE)(i+1));
/*			MEM_ClearDocAndFATArea(file_item, MEM_ALL_NO, (UBYTE)(i+1));  1997/04/28  By T.Yamaguchi */
			SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_ERASED_MSG;
			SYB_SubAddressBoxTable[i].StoredDocBit = 0;	/* 蓄積原稿クリア */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DEL_FCODE_BOX_DOC_NOTICE;
			SYS_DocumentPrintBoxNumber = (UBYTE)(i + 1);					/*	 ＢＯＸ番号 */
			SYS_DocumentPrintNo		= (UBYTE)i;	/** 現状の仕様では無意味 TBD */
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
#endif	/* PRO_F_CODE */
#if (PRO_CIPHER == ENABLE)
	/****************************************************************/
	/* 暗号化受信原稿通知のプリント									*/
	/****************************************************************/
	if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
		if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
			for (i = 0;i < SYS_CIPHERBOX_MAX;i++) {
				if ((SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVE)
				 && (SYB_CipherBox[i].MessageStatus == SYS_CIPHERBOX_RCV_MSG)) {
					break;
				}
			}

			if (i < SYS_CIPHERBOX_MAX) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
				SYS_DocumentPrintItem	= SYS_MEM_CIPHER_RX_FILE;
				SYS_DocumentPrintNo		= (UBYTE)i;	/** 現状の仕様では無意味 TBD */
				SYS_DocumentPrintPageNo = 1;
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_CIPHER;
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
			}
		}
	}
#endif
#if (PRO_DEPARTMENT == ENABLE)
 #if (PRO_COST == ENABLE)
	/****************************************************************/
	/* 部門管理リストのプリント										*/
	/* By H.Y 1994/07/31											*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		if (SYS_DepartmentListRequest)	{
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DEPARTDATACODE_LIST;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
 #endif
#endif
	/****************************************************************/
	/* 通信管理記録のプリント Jan.7,1994							*/
	/****************************************************************/
#if (PRO_PAT_JOURNAL == ENABLE)
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		if (PAT_JournalPrintReq) {
			if (CHK_JournalAutoPrintON()) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
				SYS_DocumentPrintItem	= LST_JOURNAL_LIST;
				SYS_DocumentPrintNo		= 0;
				SYS_DocumentPrintPageNo = 1;
				cre_tsk(&tskno_JournalPrintTask, TSK_PRN_JOURNALPRINTTASK, 0); /** ジャーナルプリントタスク起動 */
			}
		}
	}
#else
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		if (SYB_AutoJournalCounter >= SYS_JOURNAL_MAX)	{
			SYB_AutoJournalCounter = 0;
			if (CHK_JournalAutoPrintON()) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
				SYS_DocumentPrintItem	= LST_JOURNAL_LIST;
				SYS_DocumentPrintNo		= 0;
				SYS_DocumentPrintPageNo = 1;
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
			}
		}
	}
#endif
#if (PRO_TCR_PRINT == ENABLE)
	/****************************************************************/
	/* Transmit Confirmation Report Print							*/
	/* 送信証のプリント Jan.7,1993									*/
	/* 送信証の印字機能有りでジャーナルの印字が一体／分離型			*/
	/*--------------------------------------------------------------*/
	/* ＦＸ仕様は原稿付きのチェック・メッセージを印字するのでここの */
	/* パスは通さない。												*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		for (j = 0; j < SYS_JOURNAL_MAX; j++)  {
			if (SYB_JournalFile[j].Option & SYS_TCR_REQUEST) { /** 送信証プリント要求の確認 */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
				SYS_DocumentPrintItem	= LST_TXCONF_REPORT;
				SYS_DocumentPrintNo		= 0;
				SYS_DocumentPrintPageNo = 1;
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
				break;
			}
		}
	}
#endif
	/****************************************************************/
	/* プロトコルモニタのプリント Jan.7,1993						*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		if (SYS_ProtocolMonitorPrintRequest) { /** プロトコルモニタプリント要求の確認 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_T30MONITOR;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* 画像メモリあふれ→消去通知のプリント	Jan.7,1993				*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */
		if (SYS_MemoryOverListRequest) { /** 画像メモリあふれ通知プリント要求有り? */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_MRYOVER_CHECKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
#if (PRO_DRAM_BACKUP == ENABLE)		/* 1994/11/26 */
	/*--------------------------------*/
	/* スキャナコマンド消去リクエスト */
	/*--------------------------------*/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) {
		if (SYS_ScannerComEraseListRequest == 1) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DELRESERVECMD_NOTICE;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
		}
	}
#endif
	/************ ↓　追加　1996/06/28　Eguchi **************************/
#if (PRO_SECURITY_RX == ENABLE)
	/*------------------------------------------------*
	 * セキュリティ受信モード中の受信メモリーオーバー
	 * チェックメッセージ起動処理
	 *------------------------------------------------*/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) {
		if (CheckSecurityRxChkMsgPrint() == TRUE) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_SEC_RX_MEMOVER_CHKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
		}
	}
#endif
/************ ↓　追加　1996/06/28　Y.Tanimoto **************************/
#if (PRO_CLASS1 == ENABLE)
	/****************************************************************/
	/* Class1 Memory Receive Doc Print								*/
	/* Class1受信原稿プリント起動／再起動							*/
	/* add by Y.Tanimoto											*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT))	 {
		CL1_MemoryRxPrintPoint = &SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintReadPoint];
/*#if (PRO_PRINT_TYPE == LASER)*/
		if ((CHK_UNI_MemoryRxAndPrint() && ((CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE) || (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT))) ||
			(!CHK_UNI_MemoryRxAndPrint() && (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT))) {	/* メモリ受信原稿の有無確認 */
																										/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
/*#else*/
/*		if ((CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE)||(CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT))	{ @* メモリ受信原稿の有無確認 */
/*#endif*/
			if (CL1_MemoryRxPrintPoint->StorePage >= CL1_MemoryRxPrintPoint->PrintPage)	 {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
				SYS_DocumentPrintItem	= SYS_MEM_CL1_RX_FILE;
				SYS_DocumentPrintNo		= CL1_MemoryRxPrintReadPoint;
				SYS_DocumentPrintPageNo = CL1_MemoryRxPrintPoint->PrintPage;
				SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
			}
			else if (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) {
				/* メモリ受信終了。ページ合成排出処理 TBD */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
			}
			else { /** 異常状態 */
				/*--------------------------------------------------------------------------*/
				/* 代行受信原稿が存在するのに印字しない時の処理を取り敢えず入れて起きます。 */
				/* By S.K on Jun.30,1994													*/
				/*--------------------------------------------------------------------------*/
				if (CL1_MemoryRxPrintReadPoint != CL1_MemoryRxPrintWritePoint)	{
					CL1_MemoryRxPrintReadPoint++;
					if (CL1_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX)  {
						CL1_MemoryRxPrintReadPoint = 0;
					}
				}
			}
		}
	}
#endif /* PRO_CLASS1 == ENABLE */
/************ ↑　追加　1996/06/28　Y.Tanimoto **************************/
/* 暫定でプリント優先順位を低いところに置いておきます　By J.Miyazaki 1996/08/10 */
#if (PRO_PC_PRINT == ENABLE)	/* J.Miyazaki 1996/09/04 */
	/************************************************************/
	/* ＰＣ受信原稿プリント起動／再起動							*/
	/************************************************************/
	if ((CMN_CheckNoPrinterError()		== TRUE)
	&&	(CMN_CheckPrinterCoverClose()	== TRUE)
	&&	(CMN_CheckBothCassetteClose()	== TRUE)
	&&	(CMN_CheckPrinting()			== FALSE )) {
		/** ＰＣからの受信ページがある場合 */
		if ((SYB_PcRxPrint.Status == SYS_PC_RX_STORE) || (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT)) {
			PcRxPagePoint.Item = SYS_MEM_PC_RX_FILE;
			PcRxPagePoint.No   = 0;
			PcRxPagePoint.Page = SYB_PcRxPrint.PrintPage;
			PcRxPagePoint.BoxNumber = MEM_IGNORE_BOX_NUMBER;
			/** 指定されたカセットに記録紙がある場合 */
		/*	if (CMN_PC_CheckCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) { By M.Tachibana 1997/06/26 */
			if (CMN_CheckCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
				if (SYB_PcRxPrint.StorePage >= SYB_PcRxPrint.PrintPage)	 {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
					SYS_DocumentPrintNo		= 0;
					SYS_DocumentPrintPageNo = SYB_PcRxPrint.PrintPage;
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);
				}
				else if (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
			}
		}
	}
#endif	/* #if (PRO_PC_PRINT == ENABLE) */

#endif /* ここまで削除 CHECKER M.Tachibana 97/10/24 */
}

/*************************************************************************
	module		:[次原稿読取開始処理]
	function	:[
		ミラーキャリッジが待機状態にあり、次原稿読取指示があった場合の処理
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/10/1]
	author		:[曽根岡拓]
*************************************************************************/
void	MAN_NextScanStart(void)
{
	/* ADF継続ＪＡＭのとき */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_JAM_RECOVER_OPR | SYS_SCANNER_NEXT_SCAN_START);
	}
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
	/* FBSリカバーのとき */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_FBS_RECOVER_OPR | SYS_SCANNER_NEXT_SCAN_START);
	}
#endif
	/* 次原稿蓄積開始のとき	 */
	else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
	}

	if (!CHK_ReadyModeCopy()) {
		/* 次原稿あり／なしオペレーション開始指示 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_OPR;
#if (0) /* POPLAR_H で必要？ T.Nose 1997/05/04 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE)) {
			InitializeSoftKey(WAIT_STATE);
		}
#endif
	}

#if (PRO_FBS == ENABLE)
	/* ミラーキャリッジタスク起動して、所定の読み取り待機位置へ移動する */
	if (SYS_ScannerExecMode == SCN_ADF) {
		/* SCN_MirrorTaskControl = MIRROR_TASK_TO_ADF;  1996/12/09 */
		MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
		 /* ＡＤＦ送信／コピーの場合は次原稿あり／なしの初期値なし設定 by T.Soneoka 1996/07/18 */
		SYS_NextBookDocument = FALSE;
	}
	else {
		/* SCN_MirrorTaskControl = MIRROR_TASK_TO_FBS;  1996/12/09 */
		MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
		 /* ブックコピーの場合は次原稿あり／なしの初期値なし設定 by T.Soneoka 1996/07/18 */
		if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) ||
		    (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
			SYS_NextBookDocument = FALSE;
		}
		 /* ブック送信の場合は次原稿あり／なしの初期値あり設定 by T.Soneoka 1996/07/18 */
		else {
			SYS_NextBookDocument = TRUE;
		}
	}

	SYS_IsMirrorScanReady = FALSE;
	MirrorTaskRequest = TRUE;	/* ミラータスク起動方法を変更  1996/11/20 */
#endif /* (PRO_FBS == ENABLE) */

	if (tskno_SCN_DocumentStoreTask == 0xffff) {
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナー資源確保*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE; /* 原稿蓄積をセット */
		cre_tsk(&tskno_SCN_DocumentStoreTask, TSK_SCN_TASK, 0); /* 原稿蓄積タスク起動 */
	}
	else {
		SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
	}
}


/*************************************************************************
	module		:[周辺デバイスの初期化]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/11/18]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeDevice2(void)
{

	/*****SCN*****/
	SCN_SetBuzzer(SCN_DISABLE); /** ブザー禁止 */
	SCN_Init();					/** スキャナー用ゲートアレイの初期設定 */

	/*****DPR*****/
#if (PRO_DPRAM == ENABLE)		/* By J.Miyazaki 1996/08/12 */	/**プリンタ初期化の前に移動 97/06/26 M.Kotani*/
	DPRD_InitializeInterface();	/**DPRAM通信を開始するための一連の初期化*/
 #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/14 */
	MAN_InitilizeOptionBoard();	/* Add By O.Kimoto 1996/11/18 */
 #endif
#endif

	/*****PRN*****/
	/****************************************************************/
	/* プリンターの初期化（リセット）を実行							*/
	/****************************************************************/
#if (PRO_PRINT_TYPE == LASER)
	SCN_GeneratePrinter1KHz();	/** プリンタ用1KHzのセット */
	if (CheckerMode != 0x80) {
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP; /** プリンターリセット中のウォームアップヲセット Feb.23,1996 */
		DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
		if (PRN_InitPrinter()) { /** プリンタまわりの初期設定 */	/**この前にＤＰＲの初期化がされていること*/
			/** プリンター初期化正常終了 */
		}
		else { /** プリンター異常 */
			/** プリンター初期化異常のステータスをセット */
			SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_RESET_ERROR;	/* ﾐﾉﾙﾀ ﾌﾟﾘﾝﾀｰ初期化エラー By S.K Jan.29,1996 */
		}
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_PRINT_WARMUP); /** プリンターリセット中のウォームアップヲセット Feb.23,1996 */
		UpdateDisplay(); /** プリンターウォームアップの表示を更新 Feb.23,1996 */
		PRN_1stPagePrintFlag = 1;		/* 電源ＯＮ直後の黒ライン対策 By S.Kawasaki 1996/08/22 */
	}
#endif
#if (PRO_PRINT_TYPE == LED)
	SCN_GeneratePrinter1KHz();	/** プリンタ用1KHzのセット */
	PRN_InitHighVoltage();
	PRN_InitPrinter();
#endif

	/*****SCN*****/
	/* 電源ON時のスキャナの初期化処理 T.Nose 1997/01/17
	** 電源ON直後は、SYS_MachineStatusを初期化中にして
	** ミラーキャリッジを待機位置へ移動する
	*/

	SCN_MotorDriveMode = SCN_ADF;	/* 現在のモーター駆動経路の状態を、一旦ADF側にする */

#if (0)	/* For Checker By M.Tachibana 1997/09/09 */

#if (PRO_FBS == ENABLE)
	SCN_RegularDocumentSize = SYS_REGULAR_SIZE_UNKNOWN;

	/* ミラーキャリッジの待機位置の初期化 */
	if (CHK_UNI_MirrorReadyModeVariable()) { /* 待機位置可動モード */
		SCN_MirrorReadyPosition = READY_POSITION_ADF;
	}
	else { /* 待機位置固定モード */
		if (CHK_UNI_MirrorStaticPositionADF()) {
			SCN_MirrorReadyPosition = READY_POSITION_ADF;
		}
		else {
			SCN_MirrorReadyPosition = READY_POSITION_FBS;
		}
	}
#endif

	MAN_InitializeScanner(); /* man_oprm.c でも同じ処理を行うため関数化 */

#endif

}


/*************************************************************************
	module		:[待機状態で動作しているタスク生成]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeTaskCreate2(void)
{
	/****************************************************************/
	/* 待機状態で動作しているタスク生成								*/
	/****************************************************************/
	cre_tsk(&tskno_MAN_SensorTask, TSK_MAN_SENSORTASK, 0);
	cre_tsk(&tskno_MAN_TimerTask, TSK_MAN_TIMERTASK, 0);
	cre_tsk(&tskno_OPR_Task, TSK_OPR_TASK, 0);
	cre_tsk(&tskno_OPR_SubMessageReceiveTask, TSK_OPR_SUBMESSAGERECEIVETASK, 0);
	cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
	cre_tsk(&tskno_CMN_MultiTimer10msTask,TSK_CMN_MULTITIMER10MSTASK,0);

#if (PRO_CLASS1 == ENABLE) /* 1996/02/21 Eguchi */

	SYS_CL1_Status = 0;		/* とりあえずクリアしておく */

	CL1_RSHardWareCheck();
	if (SYS_RS232C_Exist) {
		cre_tsk(&tskno_CL1_Task, TSK_CL1_TASK, 0 );
	}
#endif

#if (PRO_PRINT_TYPE == LED)

/*#if (0)*/	/* For Checker By M.Tachibana 1997/09/09 */
	if (CheckerMode == 0x71) {
		SYB_SettingStatus[26] &= ~0x02;	/* ＦＡＸモードにする  表示の関係上 */
		SYB_MaintenanceSwitch[71] = 5;	/* カセット１のサイズをＬＴＲにする */
		SYB_MachineUniqSwitch[93] = 0;
	}

	if ((CheckerMode == 0x70) || (CheckerMode == 0x71)) {

		/* メンテナンスＳＷ＿Ｈ５－６ 1998/01/20  By M.Tachibana */
		/* 電源ＦＡＮを接続しなくてもエラー発生しないようにする */
		SYB_MaintenanceSwitch[75] |= 0x40;

 #if (PRO_PRINTER == DPI200)
		/* ＰＯＰＬＡＲ＿Ｌの場合、トップカバーのセンサーを無視する By M.Tachibana 1998/07/20 */
		SYB_MaintenanceSwitch[41] |= 0x08;
 #endif

		/*
		** センサータスクのイニシャルが走らずSYS_DrumUnitStatusが０のまま
		** ウォームアップタスクが走るため”ドラムガアリマセン”エラーがでる
		*/
		wai_tsk(100);

		cre_tsk(&tskno_PRN_FuserTempTask, TSK_PRN_FUSERTEMPTASK, 0);

		DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINTER_POWER_ON;
		cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);

	}

/*#endif*/


#endif

}

/*************************************************************************
	module		:[動作状態表示]
	function	:[
		1.メインタスクが１周する毎に実行される
		2.ブザー鳴動／停止
		3.ＬＥＤ点灯／消灯
		4.機器状態表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/05/10]
	author		:[江口]
*************************************************************************/
void UpdateDisplay2(void)
{
	/************************/
	/** ブザー鳴動			*/
	/************************/
	UpdateBuzzer();

	/************************/
	/** LED制御				*/
	/************************/
	UpdateLED();

	/************************/
	/** 動作状態表示	    */
	/************************/
	UpdateLCD2();

#if (PRO_PRINT_TYPE == LASER)	/**FEMの為*/
	/*
	 * プリンターステータスを機種固有スイッチＦ５，６にコピーする
	 * プリンターエラー発生時の詳細データの獲得のため
	 */
	/* UNIQ_SW_F5に下位バイトをセット*/
	/* UNIQ_SW_F6に上位バイトをセット*/
	/* 上位／下位を反転 */
	SYB_MachineUniqSwitch[UNIQ_SW_F5] = (UBYTE)(SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0x00FF);
	SYB_MachineUniqSwitch[UNIQ_SW_F6] = (UBYTE)((SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0xFF00) >> 8);
#else
#if (0)	/* POPLARでは使用しない */
	/*
	 * プリンターステータスをメンテスイッチＦ８，９にコピーする
	 * プリンターエラー発生時の詳細データの獲得のため
	 */
	/* MNT_SW_F8に下位バイトをセット*/
	/* MNT_SW_F9に上位バイトをセット*/
	/* 上位／下位を反転 */
	/* とりあえずサービスコールの３番目だけセットする（必要によって１，２番目もセットする） */
//	SYB_MaintenanceSwitch[MNT_SW_F8] = (UBYTE)((SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0xFF00) >> 8);
//	SYB_MaintenanceSwitch[MNT_SW_F9] = (UBYTE)(SYS_MachineStatus[SYS_PRINTER_STATUS3] & 0x00FF);
#endif
#endif
}


