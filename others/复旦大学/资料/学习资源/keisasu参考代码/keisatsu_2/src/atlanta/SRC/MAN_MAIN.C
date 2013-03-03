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
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\define\def_semn.h"	/* 1999/10/19 Y.Murata */
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
#include  "\src\atlanta\define\mntsw_a.h"
#include  "\src\atlanta\define\mntsw_g.h"
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
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\define\opr_def.h" /* Changed by H.Kubo 1997/08/18 */
#endif

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#if (PRO_CLASS1 == ENABLE)
#include  "\src\atlanta\ext_v\cl1_data.h"
#endif
#include  "\src\atlanta\ext_v\man_data.h"
#include  "\src\atlanta\ext_v\mlt_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1999/10/19 Y.Murata */
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

#if (PRO_MULTI_LINE == ENABLE)
#include  "\src\atlanta\define\mlt_pro.h"
#endif
#if (PRO_CIPHER == ENABLE)/*	By Y.Suzuki 1997/09/04	*/
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_RELAYED_REPORT == ENABLE)	/* Added by H.Kubo 1998/01/06 */
#include  "\src\atlanta\ext_v\fcm_data.h"
#endif

/*DPR*/
#if (PRO_DPRAM == ENABLE)
#include  "\src\atlanta\ext_v\dpr_data.h"
#endif

#if defined(POPLAR_F)
#include  "\src\atlanta\ext_v\lst_data.h"
#endif

/*プロトタイプ宣言*/
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include  "\src\atlanta\define\uni_pro.h"
	void	SCN_Init( void );			/* SCN */
	WORD 	Check_AnyList(UBYTE Mode);	/* LST */
	void 	Init_AnyList(UBYTE Mode);	/* LST */

/*ROT*/	/* Add By O.Kimoto 1997/06/13 */
#if (PRO_ROTATE == ENABLE)
	#include "\src\atlanta\define\rot_pro.h"
		/*#include "\src\atlanta\define\dpr_pro.h"*/
		UBYTE DPR_CheckRotateBoardExist(void);
#endif
#if (PRO_SECURITY_RX == ENABLE)
	void	SetSecurityRxMode(void);
	UBYTE	CheckSecurityRxChkMsgPrint(void);
#endif
#if (PRO_CLASS1 == ENABLE)
	/*#include  "\src\atlanta\define\uni_pro.h"*/
	UBYTE  CHK_UNI_MemoryRxAndPrint(void);
 #if (PRO_PRINT_TYPE == THERMAL)
	#include  "\src\atlanta\define\mntsw_b.h"	/* added by H.Hirao 1999/01/30 */
 #endif
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	void	MAN_FromInfMain(UWORD, UWORD, UWORD, UWORD, UWORD, UWORD);
	void	StartMailComPrint(void);
	UBYTE	GetExecMailCommand(void);
	void	ClearMailComJournalTotalTime(void);
	#include "\src\atlanta\ext_v\sys_inf.h"
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/27 Y.Murata */
	#include  "\src\atlanta\sh7043\define\sh_port.h"
	#include  "\src\atlanta\sh7043\define\sh_sys.h"
	#include  "\src\atlanta\ext_v\sys_port.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/10/28 H.Yoshikawa */
	#include	"\src\atlanta\sakaki\define\gaio_pro.h"
#endif

#include "\src\atlanta\define\unisw_c.h"

CONST UBYTE	DEBUG_PrnTestNo = 0;	/* for debug */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
																		/* Add by Y.Kano 2003/07/11 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
** 　　きていない===>従来どおり発呼
** 　　きていた  ===>リダイヤルへ
** という風にする
** by O.Kimoto 2002/07/05
*/
#include "\src\atlanta\ext_v\ncu_data.h"

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/27 */
#include	"\src\atlanta\define\ncu_stat.h"
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/18 */
extern UBYTE	IsSHIREIDisable;
#endif /* defined (KEISATSU) */

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

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/09/25 Y.Murata */
	UWORD	io_wait;
	UBYTE	key_status;
	UBYTE	key_cnt;
	UBYTE	on_off_cnt;
	UBYTE	on_off_flag;
#endif

	MESSAGE_t	*MessageControl;

	debug_anzu = 0;	/* DEBUG */


#if (PRO_PRINT_TYPE == LED)	/* WDT T.Nose 1998/03/14 */
	PRN_MRD9604SoftReset();	/* ９６０４ソフトリセット */
	WDT_Disable();			/* ウォッチドックタイマー停止 */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/10/28 H.Yoshikawa */
	PRN_Init10msParameters();
#endif
	/*スタティック変数の初期化*/
	HungUpCheck = 0;			/* ハング・アップ・チェック無し */
	for (stack_num = 0; stack_num < SYS_OPTION_BOARD_MAX; stack_num++) {
		CommandErased[stack_num] = 0;
	}

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/15 Y.Murata */
 #if (PRO_PRINT_TYPE == LASER)

	/* 1998/09/30 Y.Murata */
	outpw(IO_PDDRH_PORT, (UWORD)(SYS_PDDRH_PortStatus &~ (IO_BIT_STAMP)));	/** Stamp OFF */

	/* 1998/09/18 Y.Murata
	 * パワーＯＮ時に白紙がでてくることがある。
	 * ここで一応スタート信号を無効としときます。
	*/
	/** MCR1レジスタ 初期設定 */
	PRN_MCR1PortData = PRN_MCR1_CBSYEN + PRN_MCR1_XCPRDY + PRN_MCR1_XSTART + PRN_MCR1_XPRFD;
	PRN_MCR1PortData &= ~PRN_MCR1_XPRFD;	/* 1998/09/21 */
	outp (PRN_IO_MCR1_ADDRESS, PRN_MCR1PortData);
	PRN_MinoltaPowerOnFlag = 1;				/* 1998/09/21 */

	/*DPRD_ResetOption(); 1998/08/27 Y.M */
	CMN_DisableInterrupt();	/**割り込み禁止*/
	SYS_COM_PortStatus |= IO_BIT_CURV1;
	outpw(COM_PORT,SYS_COM_PortStatus);
	CMN_EnableInterrupt();	/**割り込み許可*/


	/* 1998/09/25 Y.Murata
	 *
	*/
	on_off_flag = 0;
	on_off_cnt = 0;
	key_cnt = 0;
	while (1) {
		CMN_DisableInterrupt();
		io_wait = CMN_CheckSH_WCR1_CS3();
		CMN_SetSH_WCR1_CS3(7);
		key_status = (UBYTE)(inpw(KEY0_PORT));
		CMN_SetSH_WCR1_CS3(io_wait);
		CMN_EnableInterrupt();
		if (key_status == 0xBF) {	/* ｽﾀｰﾄｷｰのみ押下されている */
			key_cnt++;
			if (key_cnt > 5) {
				break;
			}
		}
		else {
			key_cnt = 0;
		}

		on_off_cnt++;
		if (on_off_cnt > 20) {
			on_off_cnt = 0;
			if (on_off_flag) {
				on_off_flag = 0;
			}
			else {
				on_off_flag = 1;
			}
		}
		if (on_off_flag) {
			AllLedOn();
		}
		else {
			AllLedOff();
		}
		wai_tsk(1);
	}

	/* 1998/09/30 Y.Murata */
	outpw(IO_PDDRH_PORT, (UWORD)(SYS_PDDRH_PortStatus | IO_BIT_STAMP));		/** Stamp ON */
 #endif
#endif

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

	/****************************************************************/
	/* PowerOn時のデバイスの初期化									*/
	/****************************************************************/
	MAN_InitializeDevice();

	/****************************************************************/
	/* 待機状態で動作しているタスク生成								*/
	/****************************************************************/
	MAN_InitializeTaskCreate();


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/15 Y.Murata */
 #if (PRO_PRINT_TYPE == LASER)
	/*DPRD_ResetOption(); 1998/08/27 Y.M */
	CMN_DisableInterrupt();	/**割り込み禁止*/
	SYS_COM_PortStatus &= ~IO_BIT_CURV1;
	outpw(COM_PORT,SYS_COM_PortStatus);
	CMN_EnableInterrupt();	/**割り込み許可*/
 #endif
#endif

	/****************************************************************/
	/* 最初のディスプレイの更新										*/
	/****************************************************************/
#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/09/29 H.Yoshikawa */
	/*--------------*/
	/*	LCD濃度処理	*/
	/*--------------*/
	ContrastLCD_Set();
#endif
	UpdateDisplay();
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/05/26 Y.Murata */
	/* 自動ラムクリアおよびオプションが変更された時オプションモデムのティーチングバッファをクリアします */
	if (SYS_AutoBackUpRAM_Clear == 1) {
		SYS_AutoBackUpRAM_Clear = 0;
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_DRD_TEADCHING_BUF);
	}
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/27 Y.Murata */
	wai_tsk(100);	/* 1sec */
	if (CMN_CheckMinoltaFlashEnable()) {
		CMN_MinoltaDataInitFla();
	}

	/* 1998/08/27 Y.Murata */
	OPR_MinoltaPatternCheck = 0xFF;						/* ミノルタテストプリント用バッファ初期化 */
	OPR_MinoltaPagesCheck	= 0;
	OPR_MinoltaOnetouch		= 0;
	OPR_MinoltaPatternItem 	= 0xFF;	/* 1998/08/31 Y.Matsukuma */
	OPR_MinoltaDisplayCheck = 0xFF;
#endif

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
		/****************************************************************/
		/* 手差し原稿繰込みタスクからのメッセージ処理					*/
		/****************************************************************/
		case FROM_PRN_MANUAL_DOC_IN_TASK:
			MAN_FromPRN_ManualDocInTask(Item, Message, SubMessage1, SubMessage2);
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
#if (PRO_CIPHER == ENABLE)
		/****************************************************************/
		/* スクランブルタスクからのメッセージ処理							*/
		/****************************************************************/
		case FROM_CIPHER_TASK:
			MAN_FromCipherTask(Item, Message, SubMessage1, SubMessage2);
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		/****************************************************************/
		/* インターネットＦＡＸメインタスクからのメッセージ処理			*/
		/****************************************************************/
		case FROM_INF_TASK:
			MAN_FromInfMain(Item,Message,SubMessage1,SubMessage2,SubMessage3,SubMessage4);
			break;
#endif
#if (PRO_PRINT_TYPE == THERMAL)	/* 1998/10/08 by T.Soneoka */
		case FROM_PRN_REALTIMECOPY_TASK:
			MAN_FromPRN_RealTimeCopyTask(Item, Message, SubMessage1, SubMessage2);
			break;
		case FROM_SCN_REALTIMECOPY_TASK:
			MAN_FromSCN_RealTimeCopyStore(Item, Message, SubMessage1, SubMessage2);
			break;
		case FROM_SCN_GETSHADE:
			MAN_FromSCN_GetShadingTask(Item, Message, SubMessage1, SubMessage2);
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
#if (PRO_PANEL == ANK)	/* 1999/10/19 Y.Murata */
		wai_sem(semno.OPR_UpDateDisp);	/** セマフォの獲得 */
		UpdateDisplay();
		sig_sem(semno.OPR_UpDateDisp);	/** セマフォの解放 */
#else
		UpdateDisplay();
#endif

#if (PRO_PANEL == ANK)
		/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする T.Nose 1997/12/01 */
		if ((SYB_MaintenanceSwitch[MNT_SW_A8] & 0x02)
		 && (DEBUG_LCD_ResetFlag == 1)) {
			LCD_Initialize();			/* LCDC初期化   */
			DEBUG_LCD_ResetFlag = 0;	/* フラグ初期化 */
		}
#endif

		/****************************************************************/
		/* 送出ダイヤルSWの監視					2003/09/17				*/
		/****************************************************************/
#if defined(SATSUKI2) || defined(STOCKHM2)	/* SATSUKI2は外付けSWで常に監視 by Y.Kano 2003/09/17 */
		CheckTxDialType();
#endif

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
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	MESSAGE_t	*MessageControl;
#endif
	UWORD	i, j;
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	UWORD	exec_queue_point_save;	/* add by T.Soneoka 1999/1/19 */
	UBYTE	current_exec_no;		/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
	UBYTE	dont_check_exec_queue;		/* マルチポーリング時、メインが重くなる不具合対策 by O.Kimoto 1999/02/10 */
#endif
	UBYTE	number_of_okey; /** 通信終了後のＯＫ通信の数 */
	UBYTE	a;
	UBYTE	line_number;	/* For Debug By O.Kimoto 1996/12/13 */
	UBYTE	dial_kind;
	UBYTE	file_item;

#if (PRO_RELAYED_REPORT == ENABLE) /* Added by H.Kubo 1998/01/09 */
	UBYTE h;
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	UWORD	test_print_no;
	UWORD	debug;
#endif

#if (PRO_SGP_TEST_ROM == ENABLE)
	UBYTE SW ;
	SW = 1;
#endif

	MainTaskMessage.Item = FROM_MAIN;

#if (PRO_FBS == ENABLE)

	/** ミラータスクの起動要求があれば、起動条件を判断してここで起動する */
	if ((MirrorTaskRequest)
	 && (!SYB_ScannerTransportMode)
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

#if (0)
			/* ADF読み取り前の準備中表示のため  1997/03/05 s.takeuchi */
			if ((SCN_MirrorTaskControl == MIRROR_TASK_TO_ADF)
			 || (SCN_MirrorTaskControl == MIRROR_TASK_TO_FBS)) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_PREPARATION_ADF;
			}

			cre_tsk( &tskno_SCN_MirrorMoveTask, TSK_SCN_MIRRORMOVETASK, 0 );
#endif
			/* ミラーが既に読取り位置にある場合、ミラータスクを起動すると
			** 一瞬「ﾖﾐﾄﾘｼﾞｭﾝﾋﾞﾁｭｳﾃﾞｽ」表示するのでディスプレイがちらつく。
			** ミラーが所定の位置にある時はミラータスクを起動しない。
			** 1998/11/06 T.Nose
			*/
			if ((SCN_MirrorTaskControl == MIRROR_TASK_TO_ADF)
			 && (SCN_MirrorCarriageStatus == MIRROR_ADF_READY)) {
				SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
				SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
				SYS_IsMirrorScanReady = TRUE;
			}
			else if ((SCN_MirrorTaskControl == MIRROR_TASK_TO_FBS)
			 && (SCN_MirrorCarriageStatus == MIRROR_HS_ON)
			 && HS()) {
				SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
				SCN_WatchEndSensorStatus = WATCH_ES_ON;
				SYS_IsMirrorScanReady = TRUE;
			}
			else {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_PREPARATION_ADF;
				cre_tsk( &tskno_SCN_MirrorMoveTask, TSK_SCN_MIRRORMOVETASK, 0 );
			}
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

#if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0))
			/* 2000/02/29 Y.Murata
			 * ギアーバックラッシュが即時メモリ送信の時、２回走る。
			 * 通信起動時のモデムの初期化が重いため。メインが走りません。
			*/
			GearBackLashTimer = 150;		/* タイマ初期化(10msタイマで減算) */
#else
			GearBackLashTimer = 100;		/* タイマ初期化(10msタイマで減算) */
#endif
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
#if defined(POPLAR_F)
		SYS_ContPollingValiableTimer = 0;
#endif

	}
#endif

#if (PRO_SGP_TEST_ROM == ENABLE)
	/** SGPダイアルバッファに番号が入っていれば、SGPダイアルバッファのダイアル番号でコマンドファイルを展開し、
	SGPダイアルバッファに入っているダイアル番号を更新する。*/
	if (SYS_SgpDialBuffer[0] != 0xFF) {
		/*-------------------------------*/
		/** コマンドファイルを掴みにいく */
		/*-------------------------------*/
		if (CheckAndGetCommandArea() == NG) {
			/* コマンドファイルが確保できない.すべて使用中 */
			/* 何もしない */
		}
		else {
			if (SW) {
				ClearCommandFileData(&SYB_CommandFile[SettingCommandFileNumber]);	/* セットし直す場合があるのでクリアする */
				/* コマンドファイルにダイアル番号を展開		*/
				CMN_StringCopyNum(&SYB_CommandFile[SettingCommandFileNumber].DialNumber.Direct[0], &SYS_SgpDialBuffer);
				/** メモリー送信可能設定 */
				SYB_CommandFile[SettingCommandFileNumber].Option.Item = SYS_MEMORY_TX;
				SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_WAITING;
#endif
				SetSgpDialNumberIncrement();
			}
			else {
				if (SYS_CurrentExecQueueNo == SYS_EXEC_QUEUE_MAX) {	/** キューが存在しません */
					ClearCommandFileData(&SYB_CommandFile[SettingCommandFileNumber]);	/* セットし直す場合があるのでクリアする */
					/* コマンドファイルにダイアル番号を展開		*/
					CMN_StringCopyNum(&SYB_CommandFile[SettingCommandFileNumber].DialNumber.Direct[0],
					                  &SYS_SgpDialBuffer[0]);
					/*
					/** メモリー送信可能設定 */
					SYB_CommandFile[SettingCommandFileNumber].Option.Item = SYS_MEMORY_TX;
					SYB_CommandFile[SettingCommandFileNumber].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
					SYB_CommandStatus[SettingCommandFileNumber] = SYS_CMD_WAITING;
#endif
					SetSgpDialNumberIncrement();
				}
				else {
					/* 何もしない */
				}
			}
		}
	}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)
		/****************************************************************/
		/* サーマルヘッドの温度制御	 94/5/27 By T.O						*/
		/* 1998/09/29 H.Yoshikawa 										*/
		/****************************************************************/
		if (PRN_OverHeatCheck() == FALSE) {	/* ヘッドが冷えているならば */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;
		}
#endif

	/****************************************************************/
	/* 通信予約のスケジューリング									*/
	/* FAX Communication Re-Schejuling Jan.8,1994					*/
	/****************************************************************/
#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
	if (((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) == 1) /** プリンタ使用中セット */
	&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) == 1)/** リスト・プリント使用中セット */
	&& (SYS_DocumentPrintItem == LST_SGP_LIST)) {
	/** レポートをプリントしている時及びレポートを書こうとしているときは、発呼しない。*/
	}
	else {
#endif

	SetCommandToExec();
#if (PRO_SGP_TEST_ROM == ENABLE)
	}
#endif

#if (PRO_BATCH_TX == ENABLE)
	SetBatchCommandToExec();
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 連続ポーリング機能追加 1996/10/17 Eguchi */
	SetContinuousPollingToExec();		/** 連続ポーリングコマンドをキューに展開 */
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 回線選択処理 By O.Kimoto 1996/11/23 */

	line_number = MAN_JudgeSelectLine();	/* NEW_JUDGE 1997/10/28 */
	/*line_number = OPT_JudgeSelectLine();*/

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
		/*
		 * キューに展開されて、発呼待ちの時（回線空き待ち）の時もここ来るで～！
		*/
		SYS_NextQueueVariableTimer = 1;	/*２回線仕様では必要 */ /* Add By O.Kimoto 1997/01/22 */
	}
	else if ((line_number & ~INTERNAL_NUMBER) == 0) {
		/** 内蔵回線でした。 */

		dial_kind = (UBYTE)(line_number & INTERNAL_NUMBER);
		line_number &= ~INTERNAL_NUMBER;

#if (PRO_CIPHER == ENABLE) /* By Y.Suzuki 1997/12/10 */
 #if (PRO_COM_CODEC_TYPE == SOFTWARE) /* #if is added by H.Kubo 1997/12/24 */
		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
			/* スクランブル処理中ならスキャナコマンドのみ送信可能 */
			/* ＴＴＩをソフトコーデックで送信するので ダメ By Y.Suzuki 1998/04/17 */
			/* スクランブル処理中でも１回線目以外からの発信はＯＫ By Y.Suzuki 1998/04/27 */
			/* スクランブル中断中で１回線目からの発信はダメ By Y.Suzuki 1998/06/25 */
		/*	&& ((CMN_CheckScrambleBusy() && CheckScannerCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command))*/
		/*	|| !CMN_CheckScrambleBusy())*/
		/*	&& !CMN_CheckScrambleBusy()*/
			&& (!CMN_CheckScrambleBusy() || (CMN_CheckScrambleBusy() && (line_number != 0)))
			&& (!SYS_CipherInterruptionOn || (SYS_CipherInterruptionOn && (line_number != 0)))
			&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
			&& CMN_CheckAutoDialEnable() ) {						/* By T.O Jun.07.1994					  */
 #else

#if (0)	/* 発呼条件をＰＯＰＬＡＲ＿Ｂに合わせます  1998/05/06 by T.Soneoka */
**		/* 通信コーデックがハードウェアなら、スクランブル以外は処理可能。  H.Kubo 1997/12/24 */
**		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
**			&& CMN_CheckAutoDialEnable() ) {						/* By T.O Jun.07.1994					  */
#else
		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
			&& (!CMN_CheckScrambleBusy() || (CMN_CheckScrambleBusy() && (line_number != 0)))
			&& (!SYS_CipherInterruptionOn || (SYS_CipherInterruptionOn && (line_number != 0)))
			&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
			&& CMN_CheckAutoDialEnable() ) {						/* By T.O Jun.07.1994					  */
#endif

 #endif /* (PRO_COM_CODEC_TYPE == SOFTWARE) */
#else
  #if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/*
		** SYS_CurrentExecQueueNoを確定させるため下から移動しました moved by H.Hirao 1999/01/05
		** ポーリング受信デュアル制限チェックを追加 added by H.Hirao 1999/01/05
		*/
		/* 不具合修正
		** GetNextExecNo();をするとSYB_ExecQueueReadPointが進んでしまう為、もし以下のif文の条件に入らなかった場合
		** 次のSYB_ExecQueueReadPointのサーチ開始位置がくるってしまうので、GetNextExecNo()をコールする前に
		** SYB_ExecQueueReadPointを保存しておき、if文の条件にはいらなかった場合、保存した値を
		** SYB_ExecQueueReadPointにコピーします 1999/1/19 by T.Soneoka
		*/
		exec_queue_point_save = SYB_ExecQueueReadPoint;

#if (0)
** /* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
**		SYS_CurrentExecQueueNo = (UBYTE)GetNextExecNo();
#else

#if (0)
** 		/* マルチポーリング時、メインが重くなる不具合修正 by O.Kimoto 1999/02/10 */
** 		current_exec_no	= (UBYTE)GetNextExecNo();
#else
		dont_check_exec_queue = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		if (CMN_CheckTwiceLineEnable(SYB_ExecQueueKeisatsu[(UBYTE)GetNextExecNo()].Line)
			&& (SYS_VariableTimer == 0)) {
			SYB_ExecQueueReadPoint = exec_queue_point_save;
			current_exec_no = (UBYTE)GetNextExecNo();
		}
		else {
			/* 通信中ですよ */
			dont_check_exec_queue = 1;
		}
#else /* !defined (KEISATSU) */
		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)) {
			current_exec_no	= (UBYTE)GetNextExecNo();
		}
		else {
			/* 通信中ですよ */
			dont_check_exec_queue = 1;
		}
#endif /* defined (KEISATSU) */
#endif

#endif

#if (0) /* マルチ制限の追加 1999/01/14 by T.Soneoka */
**		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
**			&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
**			&& CMN_CheckAutoDialEnable()							/* By T.O Jun.07.1994					  */
**			&& QueryPollingRxEnable()) {
#else

#if (0)
** /* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
** 		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
** 			&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** 			&& CMN_CheckAutoDialEnable()							/* By T.O Jun.07.1994					  */
** 			&& QueryPollingRxEnable()
** 			&& QueryMultiEnable()) {
#else

#if (0)
** 		/* マルチポーリング時、メインが重くなる不具合修正 by O.Kimoto 1999/02/10 */
** 		if (QueryCommunicationStartEnable(current_exec_no)) {
#else
		if ((dont_check_exec_queue == 0) && (QueryCommunicationStartEnable(current_exec_no))) {
#endif

#endif

#endif
  #else
		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)		/* By MURATA May.27,1994 通信使用状況確認 */
			&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
			&& CMN_CheckAutoDialEnable() ) {						/* By T.O Jun.07.1994					  */
  #endif
#endif
			/*
			**	こんなところでやると同報時、最初の実行キューが飛ばされる By M.Tachibana 1997/09/27
			*/

			/* これ消したら MULTI LINE ないとき、立ち上げてすぐにキューもないのに通信始めおるやないか。
			*/
#if (PRO_MULTI_LINE == DISABLE) /*  #if is added by H.Kubo 1998/02/20 */
  #if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			/* 上に持っていきます moved by H.Hirao 1999/01/05 */
			SYS_CurrentExecQueueNo = (UBYTE)current_exec_no;	/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
  #else
			SYS_CurrentExecQueueNo = (UBYTE)GetNextExecNo();
  #endif
#endif /* (PRO_MULTI_LINE == DISABLE) */
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/10 */
			if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)
				&& (SYS_CurrentExecQueueNo < SYS_EXEC_QUEUE_MAX) )  {
#else /* !defined (KEISATSU) */
			if ( SYS_CurrentExecQueueNo < SYS_EXEC_QUEUE_MAX)  {
#endif /* defined (KEISATSU) */

				/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
				** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
				** 　　きていない===>従来どおり発呼
				** 　　きていた  ===>リダイヤルへ
				** という風にする
				** by O.Kimoto 2002/07/08
				*/
				CMN_DisableInterrupt();
				CI_Counter_for_FCM = 0;
				CMN_EnableInterrupt();

				if (tskno_NCU_Task != 0xffff) {
					del_tsk(&tskno_NCU_Task);/* Add J.M 1994/05/12 */
				}
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
				if (tskno_NCU_TelephoneOperation != 0xffff) {
					del_tsk(&tskno_NCU_TelephoneOperation);
					SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
					if (SYS_STD_LINE_COM == SYB_ExecQueueKeisatsu[current_exec_no].Line) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  ~SYS_TEL1_OFF_HOOK;				}
					else {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  ~SYS_TEL2_OFF_HOOK;
					}
					MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
				}
 #else
				if (tskno_NCU_TelephoneOperation != 0xffff) {
					del_tsk(&tskno_NCU_TelephoneOperation);
					SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
					MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
				}
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
 #endif /* defined (KEISATSU) */
#endif
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 通信使用中セット */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);/* CI検出中クリア */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM; /* FAXCOM動作中セット */

				if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_COMMAND_TRX) {	/* add if() 1997/03/06 Y.Murata */
					if (CheckScannerCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) { /* スキャナ－・コマンドかを確認 */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナー使用中セット */
					}

					if (CheckPollingRxCommand(SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command)) {
						/* ﾎﾟｰﾘﾝｸﾞ受信及び受領証受信時に代行受信ｷｰﾌﾟﾅﾝﾊﾞｰを覚えておく */
						/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0));  1997/11/20  By T.Yamaguchi */
						SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
						if (SYB_MemoryRxPrintWritePoint == 0xFF) {
							/* SaveReturnAddressAndJumpBegin(); */	/* ここに来るのはおかしい */
						}
	#if (PRO_PRINTER_RX == ENABLE)	/* ported from rice by H.Hirao 1998/12/16 */
						/*
						** プリンタ受信する可能性のあるときだけSYS_PRINTER_BUSYをセットします
						** 1999/02/22 by H.Hirao
						*/
	 #if (0)
	 //					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
	 #else
						if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
						}
	 #endif
	#endif
					}
					if (((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x03) == 0x03)
					  ||((SYB_CommandFile[SYB_ExecQueue[SYS_CurrentExecQueueNo].Number.Command].Option.ConfirmationReport & 0x80) == 0x80)) {	/* 受領証 */
						/* 1997/01/25 Y.Murata
						 * ﾎﾟｰﾘﾝｸﾞ受信及び受領証受信時に代行受信ｷｰﾌﾟﾅﾝﾊﾞｰを覚えておくのを忘れてた ﾎｽﾄ回線のみ
						*/
						/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); 1997/11/20  By T.Yamaguchi */
						SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
						if (SYB_MemoryRxPrintWritePoint == 0xFF) {
							/* Nothing */
						}
					}
				}
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング 1997/03/06 Y.Murata */
				if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Kind == SYS_CONTINUOUS_POLLING) {
					/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); 1997/11/20  By T.Yamaguchi */
					SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
					if (SYB_MemoryRxPrintWritePoint == 0xFF) {
						/* SaveReturnAddressAndJumpBegin(); */	/* ここに来るのはおかしい */
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
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
				if (tskno_NCU_TelephoneOperation != 0xffff) {
					del_tsk(&tskno_NCU_TelephoneOperation);
				}
#endif

				/* 移動 1999/10/21 Y.Murata */
				SYB_ExecQueue[SYS_CurrentExecQueueNo].StackNumber = 0;
				SYB_ExecQueue[SYS_CurrentExecQueueNo].Option |= dial_kind;	/*  By O.Kimoto 1996/12/26 */
				SYS_ExecutingExecNo[0] = (UWORD)SYS_CurrentExecQueueNo;		/* 1997/10/29 COMMAND_DEL */

				/* ここでキューのステータスをセット 1999/10/21 Y.Murata NAGANOより */
				/*--------------------------------------------------*/
				/** 発信スケジューラー(SYS_ExecQueue) 使用状況 Set **/
				/*--------------------------------------------------*/
				if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Status == SYS_EXEC_FORWARD_WAITING) {	/** 転送予約中 */
					SYB_ExecQueue[SYS_CurrentExecQueueNo].Status = SYS_EXEC_FORWARD_EXECUTE;		/** 転送実行中 */
				}
				else if (SYB_ExecQueue[SYS_CurrentExecQueueNo].Status == SYS_EXEC_WAITING) {
					SYB_ExecQueue[SYS_CurrentExecQueueNo].Status = SYS_EXEC_EXECUTE;				/** 実行中 */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/09/21 */
					GetExecutingS1Info(SYS_CurrentExecQueueNo);
#endif		/* End of (defined (KEISATSU)) */
				}


				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);

#if 0	/* 移動 1999/10/21 Y.Murata */
//				SYB_ExecQueue[SYS_CurrentExecQueueNo].StackNumber = 0;
//				SYB_ExecQueue[SYS_CurrentExecQueueNo].Option |= dial_kind;	/*  By O.Kimoto 1996/12/26 */
//				SYS_ExecutingExecNo[0] = (UWORD)SYS_CurrentExecQueueNo;		/* 1997/10/29 COMMAND_DEL */
#endif
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = SYS_COMMAND_EXECUTE;
				MainTaskMessage.SubMessage1 = SYS_CurrentExecQueueNo; /* コマンド番号 */
				snd_msg(mbxno.FCM_Task, &MainTaskMessage); /* 通信タスクへ起動パラメーターを通知*/
			}
			else { /* By S.K 7/15/1994 */
				SYS_CurrentExecQueueNo = (UBYTE)SYB_ExecQueueReadPoint;
			}
		}
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/* 不具合修正
		** GetNextExecNo();をするとSYB_ExecQueueReadPointが進んでしまう為、もし以下のif文の条件に入らなかった場合
		** 次のSYB_ExecQueueReadPointのサーチ開始位置がくるってしまうので、GetNextExecNo()をコールする前に
		** SYB_ExecQueueReadPointを保存しておき、if文の条件にはいらなかった場合、保存した値を
		** SYB_ExecQueueReadPointにコピーします 1999/1/19 by T.Soneoka
		*/
		else {

#if(0)
** 			/* 強制プリンター受信設定時、プリンターエラーが発生していた場合は、発呼しないように
** 			** します。
** 			** by O.Kimoto 1999/01/28
** 			*/
** 			SYB_ExecQueueReadPoint = exec_queue_point_save;
#else

#if (0)
** 		/* マルチポーリング時、メインが重くなる不具合修正 by O.Kimoto 1999/02/10 */
** 			if (current_exec_no < SYS_EXEC_QUEUE_MAX)  {
** 				SYB_ExecQueueReadPoint = exec_queue_point_save;
** 			}
** 			else {
** 				SYS_CurrentExecQueueNo = (UBYTE)SYB_ExecQueueReadPoint;
** 			}
#else
			if (dont_check_exec_queue == 0) {
				if (current_exec_no < SYS_EXEC_QUEUE_MAX)  {
					SYB_ExecQueueReadPoint = exec_queue_point_save;
				}
				else {
					SYS_CurrentExecQueueNo = (UBYTE)SYB_ExecQueueReadPoint;
				}
			}
#endif

#endif

		}
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/23 */
		if ((tskno_FCM_Task == 0xffff) &&
			((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) &&
			((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) &&
			(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) &&
			/* 警察FAX DVT Added by SMuratec 李 2005/12/17 */
			((NCU_LineStatus & STD_LINE_STATUS) != STD_COM_IN_USE) &&
			((NCU_LineStatus & EXT_LINE_STATUS) != EXT_COM_IN_USE) &&
			!IsSHIREIDisable) {
#if 0 /* 警察FAX DVT_ID74 Added by SMuratec 李 2005/12/21 */
/*
MAN_AfterMessageCheck()
の指令起動のところで、SYB_MemoryRxPrintWritePointの後に
SYB_MemoryRxPrintWritePoint =
(UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
が行われています。

通常順番が逆です。
*/
@@			if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX /**|| CheckPollingTxType() **/) {	/* 1999.3.19 K.Kawata CheckPollingTxType() 追加 */
#endif
			CMN_DisableInterrupt();
			CI_Counter_for_FCM = 0;
			CMN_EnableInterrupt();

			if (tskno_NCU_Task != 0xffff) {
				del_tsk(&tskno_NCU_Task);/* Add J.M 1994/05/12 */
			}

			/*----------------------------------------------------------------------------------------------------------*/
			/* 多機能電話制御タスクからのメッセージの場合																*/
			/*		多機能電話制御タスク終了同期済																		*/
			/*		機器状態よりＣＩ検出中・多機能電話使用中の全ステータスをクリアし									*/
			/*		回線使用中・通信実行中・プリンタ使用中をセットする。												*/
			/*----------------------------------------------------------------------------------------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			
			SYS_InternalLineNumber = SYS_STD_LINE_COM;
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
#if 0 /* 警察FAX DVT_ID74 Modified by SMuratec 夏 2005/12/19 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
				SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
				SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0x80, AUTO_RECEIVE);
			}
#else
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
#endif
				
			if (tskno_NCU_TelephoneOperation != 0xffff) {
				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
				IsSHIREIKido = TRUE;
				
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
			}
#if 0 /* 警察FAX DVT_ID74 Deleted by SMuratec 夏 2005/12/17 */
@@				else {		/* 警察FAX Added by SMuratec K.W.Q 2005/10/14 */
@@					MainTaskMessage.Item = FROM_MAIN;
@@					MainTaskMessage.Message = MSG_SHIREI_ON;
@@					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
@@					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
@@				}
#endif

			/* 警察FAX DVT_ID74 Added by SMuratec 夏 2005/12/17 */
			if (tskno_faxcom_complete != 0xffff) {
			}
			else {
				/* 警察FAX DVT_ID74 Added by SMuratec 夏 2005/12/19 */
				SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
				
				if (!IsSHIREIKido) {
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_SHIREI_ON;
					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
				}

				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
				/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
				IsSHIREIKido = TRUE;
				/*----------------------------------------------------------*/
				/**	  通信タスク起動（指令起動信号によって一斉指令受信）	*/
				/*----------------------------------------------------------*/
				CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
								
				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = SYS_ISSEI_KIDO_RX;
				MainTaskMessage.SubMessage1 = 0;
				snd_msg(mbxno.FCM_Task, &MainTaskMessage); /* 通信タスクへ起動パラメーターを通知*/
			}
		}
#endif /* defined (KEISATSU) */
	}
	else if (((line_number & ~INTERNAL_NUMBER) >= 1) && ((line_number & ~INTERNAL_NUMBER) <= 8)) {
#if (PRO_MULTI_LINE == ENABLE)	/* 回線選択処理 By O.Kimoto 1996/11/23 */
		/* ２回線仕様でここの処理追加すること */
		/** 外付け回線でした。 */
		dial_kind = (unsigned char)(line_number & INTERNAL_NUMBER);
		line_number &= ~INTERNAL_NUMBER;

#if (0)
** 		/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** 		if (CHK_SelectedLineEnable(line_number) && (SYS_MltVariableTimer[line_number] == 0)) {
#else
		if (CHK_SelectedLineEnable(line_number)
		&& CHK_MANSameDocumentAccess(SYS_CurrentExecQueueNo)	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
		&& (SYS_MltVariableTimer[line_number] == 0)) {
#endif

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
					if (MAN_GetMultiLineReceiveNumber((unsigned char)line_number) == 0xFFFF) {
					/* ２回線目、送信専用設定時、受領証取りに行かない不具合 1998/04/22  By T.Yamaguchi */
					/* if (MAN_CheckMultiLineReceiveEnable((unsigned char)line_number,AUTO_RECEIVE) == 0xFFFF) { */
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
			SYS_ExecutingExecNo[line_number] = (UWORD)SYS_CurrentExecQueueNo;		/* 1997/10/29 COMMAND_DEL */
			/* 個別属性セーブ 1997/01/27 Y.Murata */
			SYS_FaxComAbility0[line_number] = SYS_WorkAbility0;
			SYS_FaxComAbility1[line_number] = SYS_WorkAbility1;
			SYS_FaxComAbility2[line_number] = SYS_WorkAbility2;
			SYS_FaxComAbility3[line_number] = SYS_WorkAbility3;
			DPR_AutoFax((UWORD)(line_number-1));
		}

#endif
	}

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */

	/*************************************************
	 **	インターネットＦＡＸ　アカウント消去実行処理
	 *************************************************/
	ControlMailAccountData();
	/*************************************************
	 **	インターネットＦＡＸ　自動受信コマンド管理処理
	 *************************************************/
	ControlAutoReceiveMailCom();
	/*************************************************
	 **	インターネットＦＡＸ　通信管理記録更新処理
	 *************************************************/
	ClearMailComJournalTotalTime();
	/*************************************************
	 **	インターネットＦＡＸ　通信コマンド実行処理
	 *************************************************/
	ScheduleMailCommand();
	/*************************************************
	 **	インターネットＦＡＸ　Engineﾎﾞｰﾄﾞ監視処理
	 *************************************************/
	CheckInternetFaxDevice();

#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */

#if (PRO_CIPHER == ENABLE)
	/********************************************************************/
	/* スクランブル再起動(for 受信優先処理) 98/06/10 By T.Fukumoto		*/
	/********************************************************************/
	if ((ScrambleOn)													/* スクランブルが有効 */
	 && (SYS_CipherInterruptionOn)										/* スクランブル再起動要求がある */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)			/* 通信中ではない */
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)								/* メール送受信中ではない？ */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX)
 #endif
	 && (SYS_CipherRestartEnable)										/* スクランブル中断後着信した By Y.Suzuki 1998/06/10 */
	 && (CMN_CheckScrambleBusy() != TRUE)) {							/* スクランブル処理中ではない */
		if (((SYB_CPH_RxPrint[0].StorePage != CipherData.PageNo)
			&& (SYS_CipherInterruptionOn != SYS_CIPHER_EXEC)) /* 未処理のページが存在する。By Y.Suzuki 1998/12/26 */
			|| (SYS_CipherInterruptionOn == SYS_CIPHER_EXEC)) {
			SYS_CipherRestartEnable = 0;	/*By Y.Suzuki 1998/06/10*/
			if (SYS_CipherInterruptionOn == SYS_CIPHER_EXEC) {	/* スクランブル */
				SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_SCRAMBLE_EXEC;
			}
			else {												/* デスクランブル */
				SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_DESCRAMBLE_EXEC;
				/*スクランブル解除ﾌﾟﾘﾝﾄ中の場合でスクランブル原稿消去ONの場合はステータスも戻しておく By Y.Suzuki 1998/08/12 */
				if ((SYS_CipherInterruptionOn == SYS_DECIPHER_EXEC) && (SYS_BackupCipherStatus & SYS_ERASE_SCRAMBLE_DOC)) {
					SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_ERASE_SCRAMBLE_DOC;
				}
			}
			SYS_CipherComExec = SYS_CipherInterruptionOn;
			cre_tsk(&tskno_SCD_CipherTask, TSK_SCD_CIPHERTASK, 0);
		}
		else {/*スクランブル処理済 By Y.Suzuki 1998/12/26*/
			SYS_CipherRestartEnable = 0;
			SYS_CipherInterruptionOn = 0;
		}
	}
#endif

#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)
		&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (FaxComTXorRX_Flag) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_FORCE_STOP_COMM_CHKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
		}
	}
#endif /* defined (KEISATSU) */

/* 優先順位を高くした。 By S.Fukui Nov.27,1997 	*/
	/****************************************************************/
	/* 消耗品発注用紙のプリント要求									*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if ((SYB_ConsumerOrderListRequest) && (CHK_UNI_OrderListPrint())) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_CONSUMERORDER_SHEET;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
		else {
			SYB_ConsumerOrderListRequest = 0;
		}
	}

#if (PRO_PRINT_TYPE == LED)
	/****************************************************************/
	/* 手差しコピー・プリント起動／再起動							*/
	/****************************************************************/
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
#endif

	/****************************************************************/
	/* Launch Multi Copy Doc Print									*/
	/* マルチ・コピー・プリント起動／再起動							*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_MULTI_COPY)) {	/*種類を追加 M.Kotani 1997/10/16*/
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
#if (PRO_PC_PRINT == ENABLE)
 #if (PRO_PRINT_TYPE == LED)
	/*
	** ＰＯＰＬＡＲのプリントすべき原稿の優先順位は、順位の高い順に、
	** 手差しコピー原稿 ＞ マルチコピー原稿 ＞ ＰＣプリント原稿 ＞ 受信原稿
	*/
	/************************************************************/
	/* ＰＣ受信原稿プリント起動／再起動							*/
	/************************************************************/
	DPR_PCR_NoSameDocument = FALSE;	/* By M.Tachibana 1998/02/20 */

  #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* Add By M.Tachibana 1998/10/08 */

	if ((CMN_CheckPrinterError()	== FALSE)
	&&	(CMN_CheckPrinting()		== FALSE )) {
		/** ＰＣからの受信ページがある場合 */
		if ((SYB_PcRxPrint.Status == SYS_PC_RX_STORE) || (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT)) {
			test_print_no = CMN_CheckMinoltaTestPrintEnable();

			PcRxPagePoint.Item = SYS_MEM_PC_RX_FILE;
			PcRxPagePoint.No   = 0;
			if (test_print_no != 0xFFFF) {
				PcRxPagePoint.No   = test_print_no;
			}
			PcRxPagePoint.Page = SYB_PcRxPrint.PrintPage;
			PcRxPagePoint.BoxNumber = MEM_IGNORE_BOX_NUMBER;
			/** 指定されたカセットに記録紙がある場合 */
			if (CMN_CheckPcCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
				SYS_MinoltaFuncIntervalTimer = 0;
				if (SYB_PcRxPrint.StorePage >= SYB_PcRxPrint.PrintPage)	 {
					if (DPR_PCR_CheckCassettePaper(&PcRxPagePoint) == TRUE) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
						SYS_DocumentPrintNo		= 0;
						if (test_print_no != 0xFFFF) {
							SYS_DocumentPrintNo   = test_print_no;
						}
						SYS_DocumentPrintPageNo = SYB_PcRxPrint.PrintPage;
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);
					}
					else {	/* By M.Tachibana 1998/02/20 */
						DPR_PCR_NoSameDocument = TRUE;
					}
				}
				else if (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					/*-----------------------------------------------------
					** 他の原稿をプリント中に、最終ページでメモリオーバーした場合に、
					** ＰＣ原稿管理テーブルのステータスが未使用にもどらない。
					** ＩｔｅｍとＮｏを指定を忘れていたため
					** 1997/09/11 H.Yoshikawa
					** ＩＣＨＯＵからコピー By M.Tachibana 1997/09/24
					*/
					SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
					SYS_DocumentPrintNo		= 0;
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
			}
		}
	}

  #else

#if (0)	/* By M.Tachibana 1998/02/20 */
//	if ((CMN_CheckNoPrinterError()		== TRUE)
//	&&	(CMN_CheckPrinterCoverClose()	== TRUE)
//	&&	(CMN_CheckBothCassetteClose()	== TRUE)
//	&&	(CMN_CheckPrinting()			== FALSE )) {
#endif
	if ((CMN_CheckPrinterError()	== FALSE)
	&&	(CMN_CheckPrinting()		== FALSE )) {
		/** ＰＣからの受信ページがある場合 */
		if ((SYB_PcRxPrint.Status == SYS_PC_RX_STORE) || (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT)) {
			PcRxPagePoint.Item = SYS_MEM_PC_RX_FILE;
			PcRxPagePoint.No   = 0;
			PcRxPagePoint.Page = SYB_PcRxPrint.PrintPage;
			PcRxPagePoint.BoxNumber = MEM_IGNORE_BOX_NUMBER;
			/** 指定されたカセットに記録紙がある場合 */
			if (CMN_CheckPcCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
				if (SYB_PcRxPrint.StorePage >= SYB_PcRxPrint.PrintPage)	 {
					if (DPR_PCR_CheckCassettePaper(&PcRxPagePoint) == TRUE) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
						SYS_DocumentPrintNo		= 0;
						SYS_DocumentPrintPageNo = SYB_PcRxPrint.PrintPage;
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);
					}
					else {	/* By M.Tachibana 1998/02/20 */
						DPR_PCR_NoSameDocument = TRUE;
					}
				}
				else if (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					/*-----------------------------------------------------
					** 他の原稿をプリント中に、最終ページでメモリオーバーした場合に、
					** ＰＣ原稿管理テーブルのステータスが未使用にもどらない。
					** ＩｔｅｍとＮｏを指定を忘れていたため
					** 1997/09/11 H.Yoshikawa
					** ＩＣＨＯＵからコピー By M.Tachibana 1997/09/24
					*/
					SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
					SYS_DocumentPrintNo		= 0;
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
			}
		}
	}

  #endif	/* (PRO_MINOLTA_TEST_FUNC == ENABLE) */

	/*---------------------------------------------------------------------
	** 指定されたカセットに記録紙がない場合はプリントしない
	** M.Tachibana 1998/02/20
	*/
	if (DPR_PCR_NoSameDocument == TRUE) {
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PC_NO_SAME_DOCUMENT;
	}
	else {
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PC_NO_SAME_DOCUMENT;
	}

 #endif
#endif	/* #if (PRO_PC_PRINT == ENABLE) */
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
	/* 全カセット紙無し時の代行受信で紙セット後の受信原稿が回転受信できないときの対策 By S.Fukui Mar.14,1998 */
	if ( ROT_CheckRotateEnable() &&
		(((CMN_CheckPaperExist() == TRUE) && (CMN_CheckNoPrinterError() == TRUE)) || CHK_UNI_StartRotateAfterRX()) ) {

/*	if (ROT_CheckRotateEnable())	 {	*/
		/* SYS_MemoryRxRotateReadPoint = (UBYTE)CMN_GetMemoryRxPrintNumber(); */
		SYS_MemoryRxRotateReadPoint = (UBYTE)MAN_GetMemoryRxPrintNumber();
		if (SYS_MemoryRxRotateReadPoint < SYS_MEMORY_RX_MAX) {
			MemoryRxRotatePoint = &SYB_MemoryRxPrint[SYS_MemoryRxRotateReadPoint];
			if (MemoryRxRotatePoint->Protect == SYS_PROTECT_OFF) {
 #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
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

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else
				else {	/** 回転オプション基盤未装着時 */
					if (MemoryRxRotatePoint->StorePage >= MemoryRxRotatePoint->RotatePage)	 {
						MemoryRxRotatePoint->RotatePage = MemoryRxRotatePoint->StorePage + 1;
						if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
						 && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
							PRN_1PageReceived = 1;
							det_evt(EVT_PRN_RESTART);
						}
					}
				}

#endif

 #else
				if (DPR_SlaveBoardEnable && DPR_CheckRotateBoardExist()) {	/** 回転オプション基盤装着時 */
					if ((MemoryRxRotatePoint->RotatePage <= MemoryRxRotatePoint->StorePage)
					 && (MemoryRxRotatePoint->RotatePage != 0))	 {
						SYS_DocumentRotateItem	= SYS_MEM_RX_FILE;
						SYS_DocumentRotateNo	= SYS_MemoryRxRotateReadPoint;
						SYS_DocumentRotatePageNo = MemoryRxRotatePoint->RotatePage;
						SYS_DocumentRotateClass	= SYS_PRINT_CLASS;
						MAN_RotateIsBusy = 1;
						cre_tsk(&tskno_ROT_Task, TSK_ROT_TASK, 0); /* 原稿回転・タスク起動 */
					}
				}
				else {	/** 回転オプション基盤未装着時 */
					if ((MemoryRxRotatePoint->StorePage >= MemoryRxRotatePoint->RotatePage)
					 && (MemoryRxRotatePoint->RotatePage != 0)) {
						if (CHK_UNI_RxDocReversePrint() && (MemoryRxRotatePoint->Status == SYS_MEMORY_RX_PRINT)) {
							MemoryRxRotatePoint->RotatePage = 0;
						}
						else {
							MemoryRxRotatePoint->RotatePage = MemoryRxRotatePoint->StorePage + 1;
						}
						if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
						 && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
							PRN_1PageReceived = 1;
							det_evt(EVT_PRN_RESTART);
						}
					}
				}
 #endif
			}
		}
	}
#endif
	/****************************************************************/
	/* Launch Memory Receive Doc Print								*/
	/* メモリ受信原稿プリント起動／再起動							*/
	/****************************************************************/
	/** POPLAR変更 1997/03/07  By T.Yamaguchi */
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT))	 {	/*種類を追加 M.Kotani 1997/10/16*/
		/* SYB_MemoryRxPrintReadPoint = (UBYTE)CMN_GetMemoryRxPrintNumber(); */
		SYB_MemoryRxPrintReadPoint = (UBYTE)MAN_GetMemoryRxPrintNumber();
		if (SYB_MemoryRxPrintReadPoint < SYS_MEMORY_RX_MAX) {
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint];
			if (MemoryRxPrintPoint->Protect == SYS_PROTECT_OFF) {
#if (PRO_ROTATE == DISABLE)	/** 回転受信機能のない時は蓄積ページをプリントする */
 #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
				if (MemoryRxPrintPoint->StorePage >= MemoryRxPrintPoint->PrintPage)	 {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
					SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS;

  #if (PRO_PRINT_TYPE == THERMAL)	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
					SYB_MaintenanceSwitch[78] &= 0xEF; /* 78 = MNT_SW_H8 2002/04/17 by T.Soneoka */
  #endif
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;				/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;	/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else { /** 異常状態 */
					/* T.B.D 多分大丈夫 */
				}
 #else
				if (MemoryRxPrintPoint->StorePage >= MemoryRxPrintPoint->PrintPage)	 {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
					SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS;

  #if (PRO_PRINT_TYPE == THERMAL)	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
					SYB_MaintenanceSwitch[78] &= 0xEF; /* 78 = MNT_SW_H8 2002/04/17 by T.Soneoka */
  #endif

					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else if ((MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) ||
						 (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_FAST_PRINT)) {
					/* メモリ受信終了。ページ合成排出処理 TBD */
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;				/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;	/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else { /** 異常状態 */
					/* T.B.D 多分大丈夫 */
				}
 #endif
#else	/** (PRO_ROTATE == ENABLE)回転受信機能のある時は回転ページをプリントする */
 #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
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
					SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;				/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;	/* Add By M.Tachibana 1997/12/22 */
					SYS_DocumentPrintClass	= SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
				else { /** 異常状態 */
					/* T.B.D 多分大丈夫 */
				}
 #else
				if (CHK_UNI_RxDocReversePrint() && (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT)) {
					if (MemoryRxPrintPoint->RotatePage < MemoryRxPrintPoint->PrintPage)	 {
						/* PrintPageが０にならない。大丈夫か？ RotatePage=0 PrintPage=1 */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
						SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
						SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
					else if (MemoryRxPrintPoint->RotatePage == 0) {
						/* メモリ受信終了。ページ合成排出処理 TBD */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;				/* Add By M.Tachibana 1997/12/22 */
						SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;	/* Add By M.Tachibana 1997/12/22 */
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS_END;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
				}
				else {
					if (MemoryRxPrintPoint->RotatePage > MemoryRxPrintPoint->PrintPage) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;
						SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;
						SYS_DocumentPrintPageNo = MemoryRxPrintPoint->PrintPage;
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
					else if ((MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT)
							&& (MemoryRxPrintPoint->StorePage < MemoryRxPrintPoint->RotatePage)) {
						/* メモリ受信終了。ページ合成排出処理 TBD */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_RX_FILE;				/* Add By M.Tachibana 1997/12/22 */
						SYS_DocumentPrintNo		= SYB_MemoryRxPrintReadPoint;	/* Add By M.Tachibana 1997/12/22 */
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS_END;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
				}
 #endif
#endif
			}
		}
	}
	/* 1997/03/07  By T.Yamaguchi */


#if (PRO_CIPHER == ENABLE)
	/*******************************************************************/
	/* スクランブル受信解除プリント起動／再起動 By Y.Suzuki 1998/01/12 */
	/*******************************************************************/
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {	/*種類を追加 M.Kotani 1997/10/16*/
		if (CMN_CheckCipherPrintEnable()) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
		/*	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_MULTI_COPY; * Multi Copy使用中セット */
			SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DESCRAMBLE_PRINT; /* デスクランブルプリント中セット */
			SYS_DocumentPrintItem	= SYB_CipherPrintItem;
			SYS_DocumentPrintNo		= SYB_CipherPrintNo;
			SYS_DocumentPrintPageNo = SYB_CPH_RxPrint[0].PrintPage;
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
#endif


	/****************************************************************/
	/* Power Down Notice List Print									*/
	/* 停電検出時のリスト・プリント起動								*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /* プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	/* 未使用 */
#if (0)
** 	/* このリストの起動してもリストタスク側では何も判断していないのでごみです。
**  ** よって、コメントにします。
**	** by O.Kimoto 1997/12/03 */
** 	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /* プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
** 		if (SYS_BackUpRamListRequest) { /* ＲＡＭ初期化要求の確認 */
** 			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
** 			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
** 			SYS_DocumentPrintItem	= LST_MRYINIT_CHECKMSG;
** 			SYS_DocumentPrintNo		= 0;
** 			SYS_DocumentPrintPageNo = 1;
** 			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
** 		}
** 	}
#endif

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
#if (PRO_RELAYED_REPORT == ENABLE)	/* Ported from RICE by H.Kubo 1998/01/12   */
				if ((SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX) && CHK_RelayedTxReport() ) { /* 中継配信コマンド終了か？ */
					for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) { /** 実行終了の通信エラーチェック */
						if ((SYB_ExecQueue[i].Number.Command == (UBYTE)j) && /** ExecQueueのコマンド番号とコマンド・ファイルの番号が一致 */
							(SYB_ExecQueue[i].Status == SYS_EXEC_ERROR))  {	/* 通信エラー */
							break; /** 通信エラーがあった。 iはSYS_EXEC_QUEUE_MAXに達しない */
								   /** このパスを通らなければi==SYS_EXEC_QUEUE_MAXになる */
						}
					}
					if (i <SYS_EXEC_QUEUE_MAX) { /** エラーになった交信がある */
						/*----------------------------------------------------------------------------------*/
						/* 中継配信用のコマンド終了であれば空き領域に不達通知用コマンドを登録する。         */
						/* 中継指示時のコマンドファイルのItem                                               */
						/*     #define SYS_SCANNER_RELAY_BROADCAST	7	 スキャナ中継指示送信 			    */
						/*     #define SYS_MEMORY_RELAY_BROADCAST	8	 メモリ中継指示送信 				*/
						/* 中継配信時のコマンドファイルのItem                                               */
						/*     #define SYS_RELAYED_TX				10	 中継配信送信                       */
						/*----------------------------------------------------------------------------------*/
						/* if ((SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX) && CHK_RelayedTxReport() ) { */ /* 中継配信コマンド終了か？ */
						if (SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0] & 0x30) {	/** 不達通知は未作成 */
							for (i = 0; i < SYS_COM_FILE_MAX; i++) { /** 通信予約数の間 Loop */
								if (SYB_CommandFile[i].Status == SYS_CMD_EMPTY) { /* コマンドファイル未使用？ */
									/* 不達通知プリントのため追加(ここから)  竹内 Apr.07.1995 */
									RelayedReportPrintStatus[j] = 0;	/** 不達通知(中継配信チェックメッセージ)を,送信/プリント中(=0)とする */
									if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
										if (CMN_CheckPrintEnable(SYS_LIST_PRINT) && CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {	/** プリンタ使用可能 */
											ExecuteRelayedReportPrint( (UBYTE)j );	/** 不達通知プリントを起動 */
										}
										else {
											/**	不達通知プリントＯＮの場合は，プリント可能になるまで不達通知は作らない	*/
											break;
										}
									}
									/* 追加(ここまで)  竹内 Apr.07.1995 */
									CreateRelayedReportCommand( (UBYTE)i, (UBYTE)j );	/** 不達通知のコマンドファイルを作成 */
									break;
								}
							}
						}
						else {	/** 不達通知は作成済み */
							if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
								/* 不達通知の同時プリントがＯＮの場合は，プリンタが未使用で不達プリント済みでなければ */
								if (CMN_CheckPrintEnable(SYS_LIST_PRINT) && CMN_CheckPrintEnable(SYS_IMAGE_PRINT)
								&&	!(RelayedReportPrintStatus[j] & PRINT_IS_OVER)) { /** プリンタ未使用で，不達通知プリント済でない */
									ExecuteRelayedReportPrint( (UBYTE)j );	/** 不達通知プリントを再起動 */
								}
							}
						}
					/* } */ /* end of 中継配信コマンド終了か？ */
					}
					else { /* 中継配信がすべて正常終了の場合 */ /* H.Kubo 1998/02/18 */
						/** 中継配信コマンドを消去する */
						CMN_ClearCommandArea(SYS_COMMAND_TRX , (UBYTE)j);
					}
				} /* end of 中継配信コマンド終了か？ */
				else
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
				/**********************************/
				/* 送信証ＯＮの場合				  */
				/**********************************/
/*				if ((SYB_CommandFile[j].Option.ConfirmationReport == TCR_REQUEST)	*/
#if 0	/* 受領証リダイヤル時の処理のため見方変更します 1998/04/21  By T.Yamaguchi */
//				if (((SYB_CommandFile[j].Option.ConfirmationReport & SYS_RCR_REQUESTED) == SYS_TCR_REQUESTED)
//				||	((SYB_CommandFile[j].Option.ConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR)) {/** 送信証ＯＮ */
#endif
				if (CMN_TCR_PrintRequestCheck(j) == TRUE) {
					if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) { /** プリント可能 */	/*種類を追加 M.Kotani 1997/10/16*/



#if (PRO_NEW_TX_CONF == ENABLE) /* 2000.2.8 K.Kawata */
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
							if (CheckDocStoredCommand((UBYTE )j)
							&&	((CHK_TcrWithDocumentON() && (number_of_okey > 0 && a == 0))
							  || (CHK_TcrWithErrorDocumentON() && (number_of_okey <= 0 || a != 0)))) { /** メモリー送信コマンドでかつ原稿印字可能  */
#else
						if (CheckDocStoredCommand((UBYTE )j)
/* Atlanta TCR画像つける・つけないSW追加1999/08/26 M.Maeda */
/*						&&	CHK_DocumentPrintAfterMemTx()  ) { メモリー送信コマンドでかつ原稿印字可能  */
						&&  !( CHK_TcrWithDocument() ) ){
#endif
							/** 原稿つきの送信証を印字する */
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
							SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
							SYS_DocumentPrintItem = SYS_MEM_TX_FILE;
							SYS_DocumentPrintNo = (UBYTE)j;
  #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 受信原稿の転送(FAXワープ) H.Yoshikawa 1998/09/30 */
							SYS_DocumentPrintPageNo = SYB_CommandFile[j].PrintPage;
  #else
							SYS_DocumentPrintPageNo = 1;
  #endif
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
#if (PRO_RELAYED_REPORT == ENABLE)	/* Ported from RICE by H.Kubo 1998/01/06   */
#if 0
@@						/* 不達通知プリントのため変更(ここから)  竹内 Apr.10.1995 */
@@						if (SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) {
@@							h = SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0];
@@							if	(CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮで不達通知送信がおわった */
@@								RelayedReportPrintStatus[h] |= RELAYED_IS_OVER;		/* 不達通知を送信済みとする */
@@								if (RelayedReportPrintStatus[h] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {	/** 不達通知プリント済 */
@@									/** 不達通知と親(配信)のコマンドを消去する */
@@									CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
@@									CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)j );	/* 不達通知 */
@@								}
@@								else if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) {	/** まだプリント済でない(最初のプリントがエラーなどで中断した) */
@@									ExecuteRelayedReportPrint( (UBYTE)h );	/** 不達通知プリントを再起動 */
@@								}
@@							}
@@							else {		/** 不達通知プリントＯＦＦ */
@@								/* 不達の親(配信)コマンドが残ることがあるので追加(ここから)  竹内 Apr.12.1995   */
@@								/* if (SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) { */	/** 不達通知がおわった */
@@								/** 不達通知の親(配信)のコマンドを消去する */
@@								/* CMN_ClearCommandArea( SYS_COMMAND_TRX, SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0]); */
@@								CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
@@							}
@@						}
@@						else {  /* 不達通知以外 */
@@							/* 追加(ここまで)  竹内 Apr.12.1995 */
@@							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
@@						}
#else
						MAN_ClearCommandAreaAfterRlyTx(j);
#endif /* 0 */
#else
						/** コマンドを消去する */
						CMN_ClearCommandArea(SYS_COMMAND_TRX , (UBYTE)j);
#endif
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
#if (PRO_RELAYED_REPORT == ENABLE)	/* Ported from RICE by H.Kubo 1998/01/13   */
#if 0 /* Changed by H.Kubo 1998/01/13 */
@@							if (SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) {
@@								h = SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0];
@@								if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮで不達通知送信がおわった */
@@									RelayedReportPrintStatus[h] |= RELAYED_IS_OVER;		/* 不達通知を送信済みとする */
@@									if (RelayedReportPrintStatus[h] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {	/** 不達通知プリント済 */
@@										/** 不達通知と親(配信)のコマンドを消去する */
@@										CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
@@										CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)j );	/* 不達通知 */
@@									}
@@									else if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) {	/** まだプリント済でない(最初のプリントがエラーなどで中断した) */
@@										ExecuteRelayedReportPrint( (UBYTE)h );	/** 不達通知プリントを再起動 */
@@									}
@@								}
@@								else {		/** 不達通知プリントＯＦＦ */
@@								/* 不達の親(配信)コマンドが残ることがあるので追加(ここから)  竹内 Apr.12.1995   */
@@									/** 不達通知の親(配信)のコマンドを消去する */
@@									/* CMN_ClearCommandArea( SYS_COMMAND_TRX, SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0]); */
@@									CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
@@									CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
@@								}
@@								/* 追加(ここまで)  竹内 Apr.12.1995 */
@@							}
@@							else {
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
@@							}
#else
							MAN_ClearCommandAreaAfterRlyTx(j);
#endif /* 0 */
#else
							CMN_ClearCommandArea(SYS_COMMAND_TRX , (UBYTE)j);
#endif
						}
						else { /** 交信エラーあり */
							if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) { /** プリント可能 */	/*種類を追加 M.Kotani 1997/10/16*/
#if (0)	/* 97/11/25 By M.Kuwahara */
//								if ((i >= SYS_EXEC_QUEUE_MAX) /** ｴﾗｰの数が10件以下 */
//								&&	CheckDocStoredCommand((UBYTE)j) /** 指定されたｺﾏﾝﾄﾞ番号がﾒﾓﾘ蓄積ｺﾏﾝﾄﾞ可 */
//								&&	CHK_DocumentPrintAfterMemTx()) { /** ﾒﾓﾘ送信時ｴﾗｰ時蓄積原稿ﾌﾟﾘﾝﾄ有効 */
#endif
#if (PRO_RELAYED_REPORT == ENABLE)	/* 不達通知プリントのため追加  竹内 Apr.10.1995 */ /* Ported from RICE by H.Kubo 1998/01/09 */
								/* 不達通知プリントＯＮの時は，不達通知がエラー終了しても */
								/* 配信のチェックメッセージプリントは起動しない           */
								/* 不達通知プリントの状況により，コマンドを消去する       */
								if ((SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT)
								&&	CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮで不達通知送信がエラー終了した */
									/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
									h = SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0];
									RelayedReportPrintStatus[h] |= RELAYED_IS_OVER;		/* 不達通知を送信済みとする */
									if (RelayedReportPrintStatus[h] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {	/** 不達通知プリント済 */
										/** 不達通知と親(配信)のコマンドを消去する */
										CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
										CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)j );	/* 不達通知 */
									}
									else {	/** まだプリント済でない(最初のプリントがエラーなどで中断した) */
										ExecuteRelayedReportPrint( (UBYTE) h );	/** 不達通知プリントを再起動 */
									}
								}
								else
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
/* 医師会特ＲＯＭはチェックメッセージは蓄積原稿は存在しないので、
** 原稿無しチェックメッセージにしなければならない。
** by O.Kimoto 1999/04/19
*/
if (ROM_SW_SpecialDoctorReport) {

#if (0)
** 		/* 医師会特ＲＯＭで、通常の送信が出来ない不具合修正 CSH-004-D86-001 by O.Kimoto 1999/10/16 */
** 									if ((SYB_CommandFile[j].TitleMessage & 0x30) != 0x00) {
** 										a = 1;
** 									}
** 									else {
** 										a = 0;
** 									}
#else
									if ((SYB_CommandFile[j].TitleMessage == 0x11) || (SYB_CommandFile[j].TitleMessage == 0x21)) {
										a = 1;
									}
									else {
										a = 0;
									}
#endif

}
else {
									a = 0;
}
								if ((a == 0)
									&& CheckDocStoredCommand((UBYTE)j) /** 指定されたｺﾏﾝﾄﾞ番号がﾒﾓﾘ蓄積ｺﾏﾝﾄﾞ可 */
									&& CHK_DocumentPrintAfterMemTx()) { /** ﾒﾓﾘ送信時ｴﾗｰ時蓄積原稿ﾌﾟﾘﾝﾄ有効 */
 #else
								if (CheckDocStoredCommand((UBYTE)j) /** 指定されたｺﾏﾝﾄﾞ番号がﾒﾓﾘ蓄積ｺﾏﾝﾄﾞ可 */
								&&	CHK_DocumentPrintAfterMemTx()) { /** ﾒﾓﾘ送信時ｴﾗｰ時蓄積原稿ﾌﾟﾘﾝﾄ有効 */
 #endif
#else

								if (CheckDocStoredCommand((UBYTE)j) /** 指定されたｺﾏﾝﾄﾞ番号がﾒﾓﾘ蓄積ｺﾏﾝﾄﾞ可 */
								&&	CHK_DocumentPrintAfterMemTx()) { /** ﾒﾓﾘ送信時ｴﾗｰ時蓄積原稿ﾌﾟﾘﾝﾄ有効 */
#endif

									SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
									SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
									SYS_DocumentPrintItem = SYS_MEM_TX_FILE;
#if (PRO_RELAYED_REPORT == ENABLE) /* Ported from RICE by H.Kubo 1998/01/09 */
									if(SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) { /** 不達通知が送信エラーとなった場合、 */
										/* エラーとなった配信のコマンドNOをセット 95/02/17 Y.Suzuki */
										SYS_DocumentPrintNo = (UBYTE)(SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0]);
									}
									else {
										SYS_DocumentPrintNo = (UBYTE) j;
									}
#else
									SYS_DocumentPrintNo = (UBYTE)j;
#endif /* (PRO_RELAYED_REPORT == ENABLE) */

  #if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 受信原稿の転送(FAXワープ) H.Yoshikawa 1998/09/30 */
									SYS_DocumentPrintPageNo = SYB_CommandFile[j].PrintPage;
  #else
									SYS_DocumentPrintPageNo = 1;
  #endif
									SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MEMORY;	/** 原稿付きチェックメッセージ印字指定 */
									cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
								}
								else {/** スキャナコマンドまたはポーリングコマンドまたはエラーが１０件以上 */
									SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
									SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** ﾘｽﾄﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
									SYS_DocumentPrintItem  = LST_COMMERR_CHECKMSG;
#if (PRO_RELAYED_REPORT == ENABLE) /* Ported from RICE by H.Kubo 1998/01/09 */
									if(SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) { /** 不達通知が送信エラーとなった場合、 */
										/* エラーとなった配信のコマンドNOをセット 95/02/17 Y.Suzuki */
										SYS_DocumentPrintNo = (UBYTE)(SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0]);
									}
									else {
										SYS_DocumentPrintNo = (UBYTE)j;
									}
#else
									SYS_DocumentPrintNo		= (UBYTE)j;
#endif
									SYS_DocumentPrintPageNo = 1;
									SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MEMORY;
									cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** ﾘｽﾄﾌﾟﾘﾝﾄﾀｽｸ起動 */
								} /* end of if (CheckDocStoredCommand((UBYTE)j) && CHK_DocumentPrintAfterMemTx()) */
							} /* end of if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) */
						} /* end of if ( number_of_okey > 0 && a == 0 ) */
					} /* end of if (!CHK_CheckMessagePrint()) */
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
					if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
						if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
#if defined(KEISATSU) /* 警察FAX DVT_ID46 Modify by SMuratec 夏 2005/11/24 */	
	if ((BackUpFaxComResult & 0x00FF) == 0x91){
	}
	else
#endif
	if ( !exit_flag && CMN_CheckPrintEnable(SYS_LIST_PRINT) ) { /** TCR要求無しの条件追加 By H.Hirao 1996/06/24 */	/*種類を追加 M.Kotani 1997/10/16*/
	/* if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { */ /** プリンタ使用状況の確認 */
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
	if ( exit_flag && CMN_CheckPrintEnable(SYS_LIST_PRINT) ) { /** TCR要求有り && プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	/* サブアドレス蓄積原稿消去通知のプリント						*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
		if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (SYS_DepartmentListRequest)	{
			SYS_DepartmentClearRequest = 1;	/* Add By O.Kimoto 1997/11/13 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DEPARTDATACODE_LIST;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
  #endif
  #if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By thonda 1997/11/29 */
	/****************************************************************/
	/* 簡易料金管理リストのプリント										*/
	/* By H.Y 1994/07/31											*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (SYS_DepartManageListRequest)	{
			SYS_DepartManageClearRequest = 1;	/* Add By O.Kimoto 1997/11/13 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_DEPARTMANAGE_LIST;
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (SYB_AutoJournalCounter >= SYS_JOURNAL_MAX)	{
			SYB_AutoJournalCounter = 0;
			if (CHK_JournalAutoPrintON()) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
 #if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
				SYS_DocumentPrintItem	= LST_AUTO_ALL_JOURNAL;
 #else
				SYS_DocumentPrintItem	= LST_JOURNAL_LIST;
 #endif
				SYS_DocumentPrintNo		= 0;
				SYS_DocumentPrintPageNo = 1;
#if (PRO_JOURNAL_VER_UP == ENABLE)	/* by K.Watanabe 2005/01/26 */
				/* ジャーナルを手動でプリントしていない状態で、ジャーナル自動プリントが起動されると、
				** 受信の内容がプリントされない不具合修正
				** （手動プリントが実行されない限り、下記変数に値がセットされていなかった）
				*/
				SYS_JournalPrintType = BOTHTYPE;
#endif
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
			}
		}
	}
#endif
#if (PRO_TCR_PRINT == ENABLE)	/* POPLAR/ANZUはDISABLE */
	/****************************************************************/
	/* Transmit Confirmation Report Print							*/
	/* 送信証のプリント Jan.7,1993									*/
	/* 送信証の印字機能有りでジャーナルの印字が一体／分離型			*/
	/*--------------------------------------------------------------*/
	/* ＦＸ仕様は原稿付きのチェック・メッセージを印字するのでここの */
	/* パスは通さない。												*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
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
#if (0)		/* 発注用紙プリント要求から印字禁止になる迄にこのパスを通らなければ
       		   トナー交換後に発注用紙が印字される可能性がある為、優先順位を高く
               する。イチョウではその可能性が大である為、ポプラでも同仕様とする。
               動作確認後、このif (0)は消去する。By S.Fukui Nov.27,1997 */
	/****************************************************************/
	/* 消耗品発注用紙のプリント要求									*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if ((SYB_ConsumerOrderListRequest) && (CHK_UNI_OrderListPrint())) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_CONSUMERORDER_SHEET;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
		else {
			SYB_ConsumerOrderListRequest = 0;
		}
	}
#endif /* if (0)  S.Fukui */
	/****************************************************************/
	/* プロトコルモニタのプリント Jan.7,1993						*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		/*if (SYS_ProtocolMonitorPrintRequest) { 1997/10/18 *//** プロトコルモニタプリント要求の確認 */
		if (SYS_ProtocolMonitorPrintRequest || SYS_OptionLineT30PrintRequest) { /** プロトコルモニタプリント要求の確認 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_T30MONITOR;
			if (SYS_ProtocolMonitorPrintRequest) {	/* 1997/10/18 */
				SYS_DocumentPrintNo		= 0;
			}
			else {
				SYS_DocumentPrintNo		= 1;
			}
#if defined(POPLAR_F)
			LST_T30ConfNumber = 0xFF;
#endif
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
	/****************************************************************/
	/* 画像メモリあふれ→消去通知のプリント	Jan.7,1993				*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (SYS_MemoryOverListRequest) { /** 画像メモリあふれ通知プリント要求有り? */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_MRYOVER_CHECKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
#if (PRO_PC_PRINT == ENABLE)	/* By M.Tachibana 1997/10/02 */
	/****************************************************************/
	/* ＰＣプリント用画像メモリあふれ通知のプリント要求				*/
	/****************************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if ((SYS_PcMemoryOverListRequest)  /** 画像メモリあふれ通知プリント要求有り? */
		&& (CHK_UNI_PcMemoryOverMsgPrint())) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_PCMRYOVER_CHECKMSG;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
		else {
			SYS_PcMemoryOverListRequest = 0;
		}
	}
#endif
#if (PRO_DRAM_BACKUP == ENABLE)		/* 1994/11/26 */
	/************************************/
	/* スキャナコマンド消去リクエスト	*/
	/************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) {	/*種類を追加 M.Kotani 1997/10/16*/
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
#if (PRO_SECURITY_RX == ENABLE)
	/****************************************************/
	/* セキュリティ受信モード中の受信メモリーオーバー	*/
	/* チェックメッセージ起動処理						*/
	/****************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) {	/*種類を追加 M.Kotani 1997/10/16*/
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
#if (PRO_CLASS1 == ENABLE)
	/****************************************************************/
	/* Class1 Memory Receive Doc Print								*/
	/* Class1受信原稿プリント起動／再起動							*/
	/* add by Y.Tanimoto											*/
	/****************************************************************/
	if (CMN_CheckPrintEnable( SYS_IMAGE_PRINT))	 {	/* SYS_LIST_PRINT->SYS_IMAGE_PRINT 1997/12/09 Y.Murata *//*種類を追加 M.Kotani 1997/10/16*/
		CL1_MemoryRxPrintPoint = &SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintReadPoint];
/*#if (PRO_PRINT_TYPE == LASER)*/
 #if (PRO_PRINT_TYPE == THERMAL) 
		/*(SYB_MaintenanceSwitch[MNT_SW_B5] & 0x20)の条件削除 M.Iida 2003/02/05*/
		if (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) {	/* メモリ受信原稿の有無確認 */
 #else
		if ((CHK_UNI_MemoryRxAndPrint() && ((CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE) || (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT))) ||
			(!CHK_UNI_MemoryRxAndPrint() && (CL1_MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT))) {	/* メモリ受信原稿の有無確認 */
																										/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
 #endif
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
/* 暫定でプリント優先順位を低いところに置いておきます　By J.Miyazaki 1996/08/10 */
#if (PRO_PC_PRINT == ENABLE)	/* J.Miyazaki 1996/09/04 */
 #if (PRO_PRINT_TYPE == LASER)

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
	debug = 0;
	if (debug) {
		CMN_SetMinoltaTestFuncData(0, 10, 0);
		debug = 0;
	}

	/************************************************************/
	/* テストプリントプリント起動／再起動						*/
	/************************************************************/
	test_print_no = CMN_CheckMinoltaTestPrintEnable();
	if (test_print_no != 0xFFFF) {
		if ((CMN_CheckNoPrinterError()		== TRUE)
		&&	(CMN_CheckPrinterCoverClose()	== TRUE)
		&&	(CMN_CheckBothCassetteClose()	== TRUE)
		&&	(CMN_CheckPrinting()			== FALSE )) {
			/** ＰＣからの受信ページがある場合 */
			if ((SYB_PcRxPrint.Status == SYS_PC_RX_STORE) || (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT)) {
				PcRxPagePoint.Item = SYS_MEM_PC_RX_FILE;
				PcRxPagePoint.No   = test_print_no;
				PcRxPagePoint.Page = SYB_PcRxPrint.PrintPage;
				PcRxPagePoint.BoxNumber = MEM_IGNORE_BOX_NUMBER;
				/** 指定されたカセットに記録紙がある場合 */
				if (CMN_CheckPcCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
					SYS_MinoltaFuncIntervalTimer = 0;
					if (SYB_PcRxPrint.StorePage >= SYB_PcRxPrint.PrintPage)	 {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* メモリ・プリント使用中セット */
						SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
						SYS_DocumentPrintNo		= test_print_no;
						SYS_DocumentPrintPageNo = SYB_PcRxPrint.PrintPage;
						SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);
					}
					else if (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT) {
						/* メモリ受信終了。ページ合成排出処理 TBD */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* ﾒﾓﾘ･ﾌﾟﾘﾝﾄ使用中セット */
						/*-----------------------------------------------------
						** 他の原稿をプリント中に、最終ページでメモリオーバーした場合に、
						** ＰＣ原稿管理テーブルのステータスが未使用にもどらない。
						** ＩｔｅｍとＮｏを指定を忘れていたため
						** 1997/09/11 H.Yoshikawa
						** ＩＣＨＯＵからコピー By M.Tachibana 1997/09/24
						*/
						SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
						SYS_DocumentPrintNo		= 0;
						SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
				}
			}
		}
	}
	else {

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
				if (CMN_CheckPcCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
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
						/*-----------------------------------------------------
						** 他の原稿をプリント中に、最終ページでメモリオーバーした場合に、
						** ＰＣ原稿管理テーブルのステータスが未使用にもどらない。
						** ＩｔｅｍとＮｏを指定を忘れていたため
						** 1997/09/11 H.Yoshikawa
						** ＩＣＨＯＵからコピー By M.Tachibana 1997/09/24
						*/
						SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
						SYS_DocumentPrintNo		= 0;
						SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
						cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
					}
				}
			}
		}
	}

#else

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
			if (CMN_CheckPcCassettePaper(MEM_CheckStoreCassette(&PcRxPagePoint)) == TRUE) {
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
					/*-----------------------------------------------------
					** 他の原稿をプリント中に、最終ページでメモリオーバーした場合に、
					** ＰＣ原稿管理テーブルのステータスが未使用にもどらない。
					** ＩｔｅｍとＮｏを指定を忘れていたため
					** 1997/09/11 H.Yoshikawa
					** ＩＣＨＯＵからコピー By M.Tachibana 1997/09/24
					*/
					SYS_DocumentPrintItem	= SYS_MEM_PC_RX_FILE;
					SYS_DocumentPrintNo		= 0;
					SYS_DocumentPrintClass = SYS_PRINT_CLASS_END;
					cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
				}
			}
		}
	}

#endif	/* (PRO_MINOLTA_TEST_FUNC == ENABLE) */

 #endif
#endif	/* #if (PRO_PC_PRINT == ENABLE) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
	/*************************************************
	 **	インターネットＦＡＸ　各種プリント起動処理
	 *************************************************/
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == (UBYTE)TRUE)	 {
		StartMailComPrint();
	}
#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */

#if (PRO_SGP_TEST_ROM == ENABLE) /* by S.Wang 98/07/24 */
	/**************************************************
	 ** シンガポール市場調査レポートプリント起動処理
	 **************************************************/
	if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) { /** プリンタ使用状況の確認 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (SYB_AutoSgpReportCounter >= SYS_SGP_REPORT_MAX)	{
			SYB_AutoSgpReportCounter = 0;
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /** リスト・プリント使用中セット */
			SYS_DocumentPrintItem	= LST_SGP_REPORT_LIST;
			SYS_DocumentPrintNo		= 0;
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /** リスト・プリント・タスク起動 */
		}
	}
#endif

#if (PRO_PRINT_TYPE == LASER)
	if (CMN_CheckF100Model()) {	/* for F100R D65RL 1997/12/05 */
		/* 一応保険の処理いれておきます。
		 * イメージプリントで、通信中ではないのに、プリントウエイト状態が５秒間あれば
		 * 強制的に、イベントを発行します。
		*/
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
				/* Nothing */
			}
			else {
				if (SYS_VariableTimer == 0) {
					CMN_DisableInterrupt();	/**	割り込み禁止	*/
					if (SYS_DualPrinerWakeUpStatus) {
						if (SYS_DualPrinerWakeUpStatus > 120) {
							outp((unsigned long)0,(unsigned char)0);/* debug WriteProtectError for ICE */
							PRN_1PageReceived = 1;
							SYS_DualPrinerWakeUpStatus = 1;
							det_evt(EVT_PRN_RESTART);
						}
					}
					else {
						if (SYS_DualPrinterWaiting) {
							if (SYS_DualPrinterWaitStatus > 120) {
								outp((unsigned long)0,(unsigned char)0);/* debug WriteProtectError for ICE */
								PRN_1PageReceived = 1;
								det_evt(EVT_PRN_RESTART);
							}
						}
					}
					CMN_EnableInterrupt();	/**	割り込み許可	*/
				}
			}
		}
	}
#endif

#if (PRO_ENERGY_SAVE == ENABLE)	/* 2001/11/22 T.Takagi */
 #if 1	/* タイマーで見る処理は見送り、現状のままにします。 2002/12/03 T.Takagi */
 		/* 頻繁に24VOnOffが起こり、リレーの寿命が持たない対策 2002/11/29 T.Takagi */
 		/* タイマーで管理するようにします */
		/****************************************************************/
		/* 待機中のPC_24V_Off処理										*/
		/****************************************************************/
		if (CMN_Check24V_OffEnable() == TRUE) {		/* 24VをOFFしてもよい条件が整っていれば */
			PC_24V_Off();
		}
 #endif
		/****************************************************************/
		/* クロックのオンオフ											*/
		/****************************************************************/
		if (SYS_HaltClock == TRUE) {					/* 現在クロックが供給されていて */
			if (CMN_CheckClockOffEnable() == TRUE) {	/* クロックを停止してもよい条件が整っていれば */
				SubResetOn();
				wai_tsk(1); 					/* サブリセットがかかってから最低0.6us待ってクロックOff */
				CMN_DisableInterrupt();			/**	割り込み禁止 クロックが止まってるのにフラグが落とされないとまずいので追加 2002/03/07 T.Takagi */
				HaltClockOff();
				SYS_HaltClock = FALSE;			/* クロックが停止していることを示すフラグ */
				SYS_ShadingDataSet = FALSE;		/* シェーディングデータがとんだことを示すフラグ */
				CMN_EnableInterrupt();			/**	割り込み許可	*/
			}
		}
		else {											/* 現在クロックが停止していて */
			if (CMN_CheckClockOffEnable() == FALSE) {	/* クロックを供給してもよい条件が整っていれば */
				HaltClockOn();
				wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
				CMN_DisableInterrupt();			/**	割り込み禁止 2002/03/07 T.Takagi */
				SubResetOff();
				SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
				CMN_EnableInterrupt();			/**	割り込み許可 */
			}
		}
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
	MAN_ExecEcoMode();
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
 #if (1) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
	MAN_ChangeEcoMode(1);
 #else
//	MAN_ChangeEcoMode(TRUE);
 #endif
#endif
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
#if (PRO_FBS == ENABLE)
	/* FBSリカバーのとき */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_FBS_RECOVER_OPR | SYS_SCANNER_NEXT_SCAN_START);
	}
#endif
	/* 次原稿蓄積開始のとき	 */
	else if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
		SYS_DocumentStorePage++;	/* 蓄積ページ数更新 */
	}

	if (!CHK_ReadyModeCopy()) {
		/* 次原稿あり／なしオペレーション開始指示 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_OPR;
#if (PRO_PANEL == KANJI)
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
#if (PRO_IMAGE_PROCESSOR !=	IMAGE_PROCESSOR_LC82103)
		SCN_Init();
#endif
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナー資源確保*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE; /* 原稿蓄積をセット */
		cre_tsk(&tskno_SCN_DocumentStoreTask, TSK_SCN_TASK, 0); /* 原稿蓄積タスク起動 */
	}
	else {
		SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
	}
}


#if (PRO_RELAYED_REPORT == ENABLE)	/*  H.Kubo 1998/01/13   */
/*************************************************************************
	module		:[中継送信の不達通知に対応した
					通信予約番号に対する発信スケジューラの消去
				]
	function	:[
		1. コマンドが不達通知を消去のときは、親の中継送信コマンドも消去。
		2. 不達通知プリントを起動。
		3. 不達通知でなければ、普通に消去。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/01/13]
	author		:[久保博]
*************************************************************************/
void	MAN_ClearCommandAreaAfterRlyTx( UBYTE j)		/* 通信予約番号 */
{
	UBYTE h;
	if (SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX_REPORT) {
		h = SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0];
		if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮで不達通知送信がおわった */
			RelayedReportPrintStatus[h] |= RELAYED_IS_OVER;		/* 不達通知を送信済みとする */
			if (RelayedReportPrintStatus[h] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {	/** 不達通知プリント済 */
				/** 不達通知と親(配信)のコマンドを消去する */
				CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
				CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)j );	/* 不達通知 */
			}
			else if (CMN_CheckPrintEnable(SYS_LIST_PRINT)) {	/** まだプリント済でない(最初のプリントがエラーなどで中断した) */
				ExecuteRelayedReportPrint( (UBYTE)h );	/** 不達通知プリントを再起動 */
			}
		}
		else {		/** 不達通知プリントＯＦＦ */
		/* 不達の親(配信)コマンドが残ることがあるので追加(ここから)  竹内 Apr.12.1995   */
			/** 不達通知の親(配信)のコマンドを消去する */
			/* CMN_ClearCommandArea( SYS_COMMAND_TRX, SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0]); */
			CMN_ClearCommandArea( SYS_COMMAND_TRX, (UBYTE)h );	/* 配信(親) */
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
		}
		/* 追加(ここまで)  竹内 Apr.12.1995 */
	}
#if (1) /* 追加 by H.Kubo 1998/02/06 */
	else if ((SYB_CommandFile[j].Option.Item == SYS_RELAYED_TX)
	 /* && CHK_RelayedTxReport() */ /* Deleted by H.Kubo 1998/02/18 */
	 && (SYB_CommandFile[j].Option.OptionNumber.RelaySourceID[0] == 0x00)) {
		/* 一度不達通知コマンドが作られた中継配信コマンドは、不達通知と共にしか消去しない。*/

		/* 次の処理はいつまでも消されないコマンドができないための保険です。 */
		for (h = 0; h < SYS_COM_FILE_MAX; h++) {
			/*-------------------------------------------------------------
			** コマンドが使用中かどうかの判断を追加する
			** 1998/11/06 H.Yoshikawa
			*/
/*			if ( (SYB_CommandFile[h].Option.Item == SYS_RELAYED_TX_REPORT)	1998/11/06 H.Yoshikawa */
			if ( (SYB_CommandFile[h].Status != SYS_CMD_EMPTY)
				 && (SYB_CommandFile[h].Option.Item == SYS_RELAYED_TX_REPORT)
				 && (j == SYB_CommandFile[h].Option.OptionNumber.RelaySourceID[0]) ) {
					break; /* 消さない */
			}
		}
		if ( h == SYS_COM_FILE_MAX) { /* もし中継配信コマンド j を親とする不達通知がなければ */
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j); /* 消す */
		}
	}
#endif
	else {
		CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)j);
	}
}
#endif /* (PRO_RELAYED_REPORT == ENABLE) */



#if (PRO_SGP_TEST_ROM == ENABLE)
void SetSgpDialNumberIncrement(void)
{
	UBYTE 	buffer_counter;
	UBYTE 	dedgit_counter;
	UBYTE	BCD, temp_bcd;
	UBYTE	dedgit;
	ULONG	dial_number;

	dedgit_counter = 0;

	for (buffer_counter = 0; ;buffer_counter++) {
		BCD = (SYS_SgpDialBuffer[buffer_counter] & 0xf0);
		BCD >>= 4;
		if (BCD != 0x0f) {
			if (BCD >= 0x00 && BCD <= 0x09) {
				dial_number = (dial_number + BCD*(10^dedgit_counter));
				dedgit_counter++;
			}
			else { /** ﾀﾞｲｱﾙ記号 */
				;
			}
		}
		else { /** 終了コードみっけ */
			break;
		}

		BCD = (SYS_SgpDialBuffer[buffer_counter] & 0x0f);
		if (BCD != 0x0f) {
			if (BCD >= 0x00 && BCD <= 0x09) {
				dial_number = (dial_number + BCD*(10^dedgit_counter));
				dedgit_counter++;
			}
			else { /** ﾀﾞｲｱﾙ記号 */
				;
			}
		}
		else { /** 終了コードみっけ */
			break;
		}
	}

	dial_number++;

	for (buffer_counter = 0; ;buffer_counter++) {
		temp_bcd = SYS_SgpDialBuffer[buffer_counter];
		BCD = (temp_bcd & 0xf0);
		if (BCD != 0xf0) {
			if (BCD >= 0x00 && BCD <= 0x90) {
				dedgit = dial_number/(10^(dedgit_counter-1));

				SYS_SgpDialBuffer[buffer_counter] = (temp_bcd & 0x0f); /** 旧データクリア */
				SYS_SgpDialBuffer[buffer_counter] |= (dedgit << 4);
				dial_number -= (dedgit*(10^(dedgit_counter-1)));
				dedgit_counter--;
			}
			else { /** ﾀﾞｲｱﾙ記号 */
				;
			}
		}
		else { /** 終了コードみっけ */
			break;
		}

		temp_bcd = SYS_SgpDialBuffer[buffer_counter];
		BCD = (temp_bcd & 0x0f);
		if (BCD != 0x0f) {
			if (BCD >= 0x00 && BCD <= 0x09) {
				dedgit = dial_number/(10^(dedgit_counter-1));

				SYS_SgpDialBuffer[buffer_counter] = (temp_bcd & 0xf0); /** 旧データクリア */
				SYS_SgpDialBuffer[buffer_counter] |= dedgit;
				dial_number -= (dedgit*(10^(dedgit_counter-1)));
				dedgit_counter--;
			}
			else { /** ﾀﾞｲｱﾙ記号 */
				;
			}
		}
		else { /** 終了コードみっけ */
			break;
		}
	}
}

#if 0
UDWORD	PickOutLastEightFigure(unsigned char *id_buf, unsigned char count)
{
	unsigned char i;
	unsigned char figure;	/* 有効桁数（終端コードまでの桁数) */
	unsigned char bcd_buffer[8];
	unsigned char work;
	unsigned char even;		/* 読み出し位置が奇数位置か偶数位置かを保持*/
	UDWORD result;
	unsigned char figure_max;

	result = 0xFFFFFFFF;
	figure = 0;

	for (i = 0; i < 8; i++) {
		bcd_buffer[i] = 0xFF;
 	}

	/* 最終桁を見つける */
	for (i = 0; i < count; i++) {
		if ((*(id_buf + i) & 0xF0) == 0xF0) {
			break;
		}
		figure++;
		if ((*(id_buf + i) & 0x0F) == 0x0F) {
			break;
		}
		figure++;
	}

	if (figure <= 7) {	/* 8桁未満 */
		figure_max = figure;
	}

	count = (unsigned char)(figure / 2);
	even = (unsigned char)(figure % 2);
	i = 0;

	if (even == 1) {	/* 奇数桁の場合 */
		if ((work = (unsigned char)( ( (*(id_buf + count)) >> 4) & 0x0F) ) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
	}
	count--;

	while(1) { /* 偶数桁の場合 */
		if (i == 8) {	/* 8桁見つけたとき */
			break;
		}
		if ((work = (unsigned char)(*(id_buf + count) & 0x0F)) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
		if (i == 8) {	/* 8桁見つけたとき */
			break;
		}
		if ((work = (unsigned char)((*(id_buf + count) >> 4) & 0x0F)) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
		if (count == 0) {
			break;	/* 最終桁までﾁｪｯｸ終了 */
		}
		count--;
	}

	for (i = 0; i < (8 - figuer_max); i ++) {
		bcd_buffer[figuer_max-i] = 0x00;
	}

	data_increment = (UDWORD)((bcd_buffer[7] * 10000000) +
	                  		  (bcd_buffer[6] * 1000000) +
	                          (bcd_buffer[5] * 100000) +
	                          (bcd_buffer[4] * 10000) +
					          (bcd_buffer[3] * 1000) +
					          (bcd_buffer[2] * 100) +
					          (bcd_buffer[1] * 10) +
					          (bcd_buffer[0] * 1) +
					           1);
	CMN_DecimalToBCD(UBYTE decimal)


	return(result);
}
#endif /** #if 0 */

#endif
