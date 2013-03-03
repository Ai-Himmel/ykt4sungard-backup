/* copy 1996/12/20 */
/* Original File : jun\usr1:\src\rice\v53\kiri\src\scn_stor.c */
/************************************************************************
*				BY:	 S.Kawasaki
*			  DATE:	 Oct.4,1993
*		 FILE NAME:	 scn_stor.c
*	   Module Name:	 SCN_Task(void)
*		Task ID No:	 ?
*	   DESCRIPTION:	 原稿蓄積タスク、原稿の処理はスタック単位
*  PUBLIC ROUTINES:	 void StoreTask( void )
* PRIVATE ROUTINES:	 LampOnWait( void )
*					 OpenScanner( void )
*					 CloseScanner( void )
*					 ScanStoreDocument( void )
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mnt_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\idp_pro.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysscan.h"
#include "\src\atlanta\define\idp301.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#if (PRO_CLASS1 == ENABLE)	/* 1997/08/08 Y.Matsukuma */
#include  "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_PANEL == ANK)
/* 工場ファンクション原稿排出テスト用 T.Nose 1997/05/27 */
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
void DisplayStringLow(UBYTE, UBYTE *);
void ClearDisplayLow(void);
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
void  DisplayString2(UBYTE  *string);
void  ClearString2(void);
#endif


#if (PRO_FBS == ENABLE)
/* FBS DVT */
void DisplayStringHigh(UBYTE, UBYTE *);
CONST UBYTE SCN_FBS_DVT_Speed = SCN_MOVE_MIRROR; /* TOP SPEED = 2330pps */
CONST UWORD SCN_FBS_DVT_Count = (UWORD)11960; /* step */
static UBYTE DEBUG_ReadMotorStep = 0;
#endif

#if (PRO_PANEL == KANJI)
/* ＰＯＰＬＡＲ＿Ｈモデムチェッカー用プログラム By O.Kimoto 1998/03/05 */
CONST UBYTE CHECKER_PRG = 0;
#endif


/** Module Header For CIM-E ********************************************
		module		:	[原稿蓄積タスク]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
static	UWORD ret_code = 0;
void SCN_Task(void)
{
	UWORD	page_counter;	/* 読み取り処理開始済みページ数(ICHOUで追加) */
	UBYTE	is_copy_file;	/* コピー原稿識別用(ICHOUで追加) */
	UBYTE	is_file_enable;	/* 蓄積ファイル有効/無効(ICHOUで追加) */
	UBYTE	break_count;	/* ADFモーター停止待ちタイムアウト用  1997/03/07 */
	UBYTE	is_stop_key;	/* 停止処理追加  1997/04/18 */

	UBYTE	i;	/* 薄読みデバッグ用 */

	UBYTE	doc_size;	/* add by Y.Matsukuma 1997/08/08 */
	UBYTE	doc_mode;	/* T.Nose 1997/09/09 */
	UBYTE	is_lamp_ok;	/* T.Nose 1998/01/25 */

#if (PRO_PANEL == KANJI)
 #ifdef PRO_CHECKER
/* ＰＯＰＬＡＲ＿Ｈモデムチェッカー用プログラムです。 By O.Kimoto 1998/03/05 */

	UWORD count;
	UBYTE *dma_address;
 #endif
#endif

	tskno_SCN_DMA_WriteTask = 0xffff;
	tskno_CDC_EncodePageTask = 0xffff;
	tskno_SCN_WatchDocCoverTask = 0xffff;
	tskno_SCN_WatchDocFeedTask = 0xffff;
#if (PRO_FBS == ENABLE)
	tskno_SCN_WatchDocMirrorTask = 0xffff;
#endif
#if (PRO_SEPERATE_24V == DISABLE)
	tskno_SCN_WatchPrinterCoverTask = 0xffff;
#endif

#if (PRO_PANEL == KANJI)
 #ifdef PRO_CHECKER
/* ＰＯＰＬＡＲ＿Ｈモデムチェッカー用プログラムです。 By O.Kimoto 1998/03/05 */

	/** インデックスの作成 */
	MEM_IndexTable[0].No = 0;
	MEM_IndexTable[0].Page = 1;
	MEM_IndexTable[0].Item = SYS_MEM_TX_FILE;
	MEM_IndexTable[0].Code = SYS_MMR_CODE;
	MEM_IndexTable[0].Mode = SYS_NORMAL;
	MEM_IndexTable[0].Size = SYS_DOCUMENT_A4_SIZE;
	MEM_IndexTable[0].LineCount = 2000;
	MEM_IndexTable[0].StartBlockNo = 0x0;

	/** ＦＡＴの作成 */
	MEM_FATArea[0] = MEM_EOP_BLOCK;

	/** ダミーデータの蓄積 */
	dma_address = (UBYTE *)MEM_STOREAREA_START_ADDRESS;

	for (count = 0; count < (250 - 8); count ++) {
		*(dma_address + count) = 0xffff;
	}
	
	*(dma_address + 241) = 0x00;
	*(dma_address + 242) = 0x08;
	*(dma_address + 243) = 0x80;
	*(dma_address + 244) = 0x00;
	*(dma_address + 245) = 0x08;
	*(dma_address + 246) = 0x80;
	*(dma_address + 247) = 0x00;
	*(dma_address + 248) = 0x08;
	*(dma_address + 249) = 0x80;
	
	CMN_EnableInterrupt();			/** 割込禁止期間終了 */
	
	/** メインへのメッセージ送信 */
	StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;
	StoreTaskMsg.Item = FROM_DOCSTORE;
	wai_tsk(50);
	snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk( 0xFFFF );
 #endif
#endif

	StoreTaskMsg.Item = FROM_DOCSTORE;

	/* メモリー送信原稿後端縮む件
	** T.Nose 1997/10/31
	*/
	DEBUG_DocumentScanning = 0;

	/*--------------------------------------------*/
	/** スキャナオープンパラメータをセットします。*/
	/** For DISPLAY								  */
	/*--------------------------------------------*/

	/* 読取りページの初期化（読取り開始割り込みでカウントされる） T.Nose 1997/09/20 */
	SCN_Control.ScanPage = 0;

	/**	コピーの読み取りではADFの1スタックで原稿サイズを変えないため、
	**	コピーの読み取りかどうかを記憶する
	*/	/* ICHOU追加  1996/08/08 s.takeuchi */
	if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) { /* マルチコピー原稿 */
		is_copy_file = TRUE;
		SCN_CopyFile = &SYB_MultiCopyFile[SYS_DocumentStoreNo];		/** マルチコピーのポインタを記憶 */
	}
	else if (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE) { /* 手差しコピー原稿 */
		is_copy_file = TRUE;
		SCN_CopyFile = &SYB_ManualCopyFile;							/** 手差しコピーのポインタを記憶 */
	}
	else { /* その他の原稿 */
		is_copy_file = FALSE;
	}

#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_FBS) {	/** FBS読み取りの場合 */
		SYS_StampFlag = 0;	/** 必ずスタンプはＯＦＦ */
	}
	else {
#endif
		if ((SYS_DocumentStoreItem == SYS_MEM_TX_FILE)
		||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE1)
		||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE2)
		||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE3)
		||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE4)
		||	(SYS_DocumentStoreItem == SYS_MEM_BATCH_TX_FILE5)) {	/* メモリ送信/バッチ送信原稿1～5 */
			CMN_EvacuateStampSetting();	/** スタンプ設定待避 */
		}
		else {	/* コピー原稿など */
			SYS_StampFlag = 0;	/** スタンプ設定ＯＦＦ */
		}
#if (PRO_FBS == ENABLE)
	}
#endif

	SCN_MotorStopRequest = 1; /**  原稿読み取り終了時にモーター停止を行うにセット */

	/*-----------------------------------------------*/
	/** 読取り幅の設定  							 */
	/*-----------------------------------------------*/
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_FBS) {
		doc_size = CMN_GetFBS_DocumentScanSize();
	}
	else {
		doc_size = CMN_GetDocumentScanSize();
	}
#else
	doc_size = CMN_GetDocumentScanSize();
#endif

#if (0)	/* ここでは制限をかけず、ＰＣの能力に合わせて縮小後、サイズを合わせます。By S.Fukui Feb.23,1998 */
//#if (PRO_CLASS1 == ENABLE)	/* add by Y.Matsukuma 1997/08/08 */
//	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
//		if (CL1_PCDocumentSize < doc_size) { /* ＰＣの能力に合わせる */
//			doc_size = CL1_PCDocumentSize;
//		}
//	}
//#endif
#endif
	/** ADF部へ移動中に前のサイズと解像度が表示されるので、一旦ここでセットする */
	SYS_DocumentScanSize = doc_size;
	SCN_Control.DocumentSize = doc_size;

	/*-----------------------------------------------*/
	/** 読取りモードの設定							 */
	/*-----------------------------------------------*/
	doc_mode = SCN_GetScanMode( is_copy_file );
#if (PRO_CLASS1 == ENABLE)	/* add by Y.Matsukuma 1997/08/08 */
	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		CL1_Code = CL1_PCDocumentCode;
		CL1_Mode = CL1_PCDocumentMode;
		if (CL1_Mode < SYS_FINE) {
			SYB_ModeSw	= CL1_Mode;
		}
		else if (CL1_Mode == SYS_FINE) {
			if ((SYB_ModeSw == SYS_GRAY64)
			 || (SYB_ModeSw == SYS_NORMAL)
			 || (SYB_ModeSw == SYS_FINE)) {
				CL1_Mode = SYB_ModeSw;
			}
			else {
				SYB_ModeSw	= CL1_Mode;
			}
		}
		else {
			if ((SYB_ModeSw == SYS_GRAY64)
			 || (SYB_ModeSw == SYS_NORMAL)
			 || (SYB_ModeSw == SYS_FINE)) {
				CL1_Mode = SYB_ModeSw;
			}
			else {
				SYB_ModeSw	= CL1_Mode;
			}
		}
		doc_mode = CL1_Mode;
	}
#endif
	SCN_Control.DocumentMode = doc_mode;

	/*-----------------------------------------------*/
	/** 停止要求のクリア							 */
	/*-----------------------------------------------*/
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_DOC_STORE); /** 原稿蓄積の停止要求をクリア */
	is_stop_key = FALSE;	/* 停止処理追加  1997/04/18 */

	/*-----------------------------------------------*/
	/** 画像メモリのオープンパラメータをセットします */
	/*-----------------------------------------------*/
	SCN_StoreData.Item = SYS_DocumentStoreItem;	/** 原稿の種別をセット					*/
	SCN_StoreData.No   = SYS_DocumentStoreNo;	/** 原稿のNo／メイルボックスをセット	*/
	SCN_StoreData.Page = SYS_DocumentStorePage; /** 蓄積開始ページＮｏをセット			*/
	SCN_StoreData.BoxNumber = SYS_DocumentStoreBoxNumber; /** ＢｏｘＮｏをセット1997/03/11  By T.Yamaguchi	*/

	/*---------------------------------------------------*/
	/** 画像メモリのブレーク用のパラメータをセットします */
	/*---------------------------------------------------*/
	SCN_IndexData.Item = SYS_DocumentStoreItem;	/** 原稿の種別をセット					*/
	SCN_IndexData.No   = SYS_DocumentStoreNo;	/** 原稿のNo／メイルボックスをセット	*/
	SCN_IndexData.Page = SYS_DocumentStorePage; /** 蓄積開始ページＮｏをセット			*/
	SCN_IndexData.BoxNumber = SYS_DocumentStoreBoxNumber; /** ＢｏｘＮｏをセット1997/03/11  By T.Yamaguchi */

	if (CHK_DocumentWidthFull()) { /**	読み取り左右白マスク無し */
		SCN_WhiteMaskFlag = 0;
	}
	else { /** 白マスク有り */
		SCN_WhiteMaskFlag = 1;
	}

	SYS_DocumentWidthFullFlag = 1;	/* IDP設定は全画素読取り */
	SYS_DocumentLengthLimitFlag = CHK_DocumentLengthLimit();

#if (PRO_FBS == ENABLE)

	/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 T.Nose 1997/12/17 */
	DEBUG_OperationExitFlag = 0;		/* タスク終了フラグリセット */

	/* ＡＤＦ読取りの時、ミラーの移動終了待ちでタスクがループする件  T.Nose 1997/12/22 */
	if (SYB_MaintenanceSwitch[MNT_SW_C0] & SCN_WAIT_MIRROR_EXIT) {
		DEBUG_ReadMotorStep = 0;
	}

	/**	ミラーキャリッジが読み取り開始位置に移動し終わるまで、100ms単位で待つ
	**	ミラーエラーならエラーメッセージを返してタスクの削除を待つ
	*/
	while (!SYS_IsMirrorScanReady) {
		wai_tsk( 10 );		/* 100ms待つ */

		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & (SYS_SCANNER_MIRROR_ERROR|SYS_SCANNER_LAMP_ERROR)) {
			if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_LAMP_ERROR;
			}
			else {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MIRROR_ERROR;
				SYB_MaintenanceSwitch[MNT_SW_C5] = 7;	/* エラーコードをセット */
			}

			/** イベント待ちのプリントを動かすため */
			SYS_FCOT_PrintStartRequest = TRUE;
			det_evt( EVT_FCOT_PRINT_START );

			snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
			rcv_msg( mbxno.SCN_Task, &SCN_Msg );
			wai_tsk( 0xFFFF );
		}

		/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件
		** T.Nose 1997/12/20
		*/
		if ((SYB_MaintenanceSwitch[MNT_SW_C0] & MIRROR_MOVE_FORCE_END)
		 && (DEBUG_OperationExitFlag == 1)) {

			/** イベント待ちのプリントを動かすため */
			SYS_FCOT_PrintStartRequest = TRUE;
			det_evt( EVT_FCOT_PRINT_START );

			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;	/** 停止要求をセット */
			snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
			rcv_msg( mbxno.SCN_Task, &SCN_Msg );
			wai_tsk( 0xFFFF );
		}

		/* ＡＤＦ読取りの時、ミラーの移動終了待ちでタスクがループする件  T.Nose 1997/12/22 */
		if (SYB_MaintenanceSwitch[MNT_SW_C0] & SCN_WAIT_MIRROR_EXIT) {
			if (DEBUG_ReadMotorStep++ >= 50) {	/* 最大５秒で強制停止 */
				SYB_MaintenanceSwitch[68] |= 0x04; /* 保守スイッチ G8 */
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
				SCN_StopMotor();
				det_evt(EVT_MIRROR_MOVE_END);	/* ミラータスクを終了させる */

				/** イベント待ちのプリントを動かすため */
				/* T.Nose 1998/01/05 */
				SYS_FCOT_PrintStartRequest = TRUE;
				det_evt( EVT_FCOT_PRINT_START );

				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;	/* 停止要求をセット */
				snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
				rcv_msg( mbxno.SCN_Task, &SCN_Msg );
				wai_tsk( 0xFFFF );
			}
		}

		/* RXIL瞬断対策 T.Nose 1998/03/05 */
		if (SCN_MirrorMoveStatus == MIRROR_MOVE_RXIL_ABORT) {
			/** イベント待ちのプリントを動かすため */
			SYS_FCOT_PrintStartRequest = TRUE;
			det_evt( EVT_FCOT_PRINT_START );
#if (0)
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_RXIL_ABORT;
#endif
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
			snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
			rcv_msg( mbxno.SCN_Task, &SCN_Msg );
			wai_tsk( 0xFFFF );
		}
	}

	/** ここで、停止キーが押されていれば蓄積を中断する */
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE) {
		/** イベント待ちのプリントを動かすため */
		SYS_FCOT_PrintStartRequest = TRUE;
		det_evt( EVT_FCOT_PRINT_START );

		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;	/** 停止要求をセット */
		snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
		rcv_msg( mbxno.SCN_Task, &SCN_Msg );
		wai_tsk( 0xFFFF );
	}

	/** ADF読み取りなら、スキャナモーターをADF側に切替える */
	if (SYS_ScannerExecMode == SCN_ADF) {
		SCN_SetMotorDrive( SCN_ADF );
	}
#endif	/* (PRO_FBS == ENABLE) */


	/*----------------------------------------------------------*/
	/** 蓄積原稿の消去											*/
	/**	 今から蓄積しようとしている原稿の消去を念の為行います。 */
	/*----------------------------------------------------------*/
	/*	ICHOUではJAMリカバー時とFBSメモリ送信時に、
	**	同じStoreNoでつづきのPageNoから再起動されるので、
	**	1ページ目のときだけ、原稿の消去をする。
	**	(念のための消去なので、出来ればこの処理を削除したい)
	*/
	if (SYS_DocumentStorePage == 1) {
		MEM_ClearDocAndFATArea( SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber);
	}

#if (PRO_FBS == ENABLE)
	/** ここではADF読み取りの場合だけランプチェックする */
	if (SYS_ScannerExecMode == SCN_ADF) {
#endif
		/*----------------------------------------------*/
		/** ランプを点灯しＤＩＰＰでチェックします。	*/
		/*----------------------------------------------*/
		/* ランプチェックエラーの場合、もう一回トライします T.Nose 1998/01/25 */
		i = 2;
		is_lamp_ok = TRUE;
		while (i > 0) {
			if (DIPP_CheckLamp() == NG) { /** ランプ点灯が異常 */
				i--;
			}
			else { /* ランプチェックＯＫ */
				break;
			}
		}
		if (i == 0) {
			is_lamp_ok = FALSE;
		}
		if (is_lamp_ok == FALSE) {
			/** イベント待ちのプリントを動かすため */
			SYS_FCOT_PrintStartRequest = TRUE;
			det_evt( EVT_FCOT_PRINT_START );

			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_LAMP_ERROR;	/** ランプエラーをセット */
			snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
			rcv_msg(mbxno.SCN_Task, &SCN_Msg);
			wai_tsk( 0xFFFF );
		}
#if (PRO_FBS == ENABLE)
	}
#endif

	LampOn(); /** ランプ点灯 */

	/*	ADFでの繰込みタスクを取り込むため、以下のような動作に変更する  1996/06/24 s.takeuchi
	**		1. モーターテーブルをSCN_xxx_FEEDで起動してスルーアップする
	**		2. DS2ON割込みでスルーダウンする(最終速度は読取り速度とする)
	**		3. 最終速度でのモーター割り込みで読取り用のモーターテーブルに切替える
	**	ICHOUは、ADF繰込み時に1ページ目の原稿を区別するためにSCN_DOC_ADF_1ST_PAGEで起動する
	*/
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_ADF) {
		SCN_DocumentStatus = SCN_DOC_ADF_1ST_PAGE;
	}
	else {
		SCN_DocumentStatus = SCN_DOC_READY;
	}
#else
#if (PRO_DOC_IN == ENABLE)
	/* 原稿繰り込み終了時に以下の値がセットされています
	** SCN_DocumentStatus = SCN_DOC_READY;
	** T.Nose 1997/10/02
	*/
#else
	SCN_DocumentStatus = SCN_DOC_ADF_1ST_PAGE;
#endif
#endif /* PRO_FBS end */

#if (PRO_SCN_CODEC_TYPE == MN86063)
	/* Ａ３縮小コピー間に合わない件
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
	** スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
	** 出力ページ幅はＢ４で、縮小率はコピーファイルに設定されている縮小率を使用する
	*/
	if (((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) {
			SCN_DocumentReduction = SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction;	/** ０～１００ */
			SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 100;
		}
		else if (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE) {
			SCN_DocumentReduction = SYB_ManualCopyFile.Reduction;	/** ０～１００ */
			SYB_ManualCopyFile.Reduction = 100;
		}
	}
#endif

	page_counter = 0;	/** 読み取り開始済みページ数を初期化 */

#if (PRO_FBS == ENABLE)
	while (((SYS_ScannerExecMode == SCN_FBS) && (page_counter == 0))
	||	   ((SYS_ScannerExecMode == SCN_ADF) && DS1())) 	/** ADF読取りで原稿あり／FBS読取りの1ページ目 */
#else
	while (DS1()) /* 原稿有り */
#endif
	{
		page_counter++;		/** 原稿の蓄積処理を開始するとカウントアップする */

		/*	ICHOUのADF繰り込み制御変更のため、
		**	1ページ目の時はSCN_DOC_ADF_1ST_PAGEのままで、
		**	2ページ目以降の時はここでSCN_DOC_READYにする
		**		1996/10/07 s.takeuchi
		*/
		if (SCN_DocumentStatus != SCN_DOC_ADF_1ST_PAGE) {
			/* ソフトコーデックなど他の処理が重くなった時、ここへ来た時には
			** 既にＤＳ２ＯＮ、読取り開始割り込みも経過している時がある。
			** その場合にはＡＤＦを停止し、原稿詰まりエラーで終了させる。
			** T.Nose 1997/12/05
			*/
			CMN_DisableInterrupt();
			if (SCN_DocumentStatus != SCN_DOC_IN_SCANNING) {
				SCN_DocumentStatus = SCN_DOC_READY;
			}
			else {
				/* 原稿先端が既にＡＤＦ読み取り位置を過ぎている。
				** モーターを止め、エラー終了する。
				** T.Nose 1997/12/05
				*/
				SCN_ADF_MotorStopRequest = ADF_MOTOR_FEED_ERROR;
				SCN_PageChangeTimeOut = TRUE;				/* SCN_WatchDocumentFeedTask()に通知するフラグ */
				SYB_MaintenanceSwitch[MNT_SW_C9] |= 0x08;	/* 処理が間に合わなかったスイッチＯＮ */
			}
			CMN_EnableInterrupt();
		}

#if (PRO_CLASS1 == ENABLE)	/* add by Y.Matsukuma 1997/08/08 */
		if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		/* ここに来るまでにｾｯﾄ済み */

			/* 上記には、セット済と有るが、Ｆ－１５０の場合、１枚目：Ａ４、２枚目：Ｂ４の場合に
			** ＰＣの能力以上の幅で蓄積を行ってしまう。
			** よって、ここで再度SYS_DocumentScanSizeのセットを行う。
			** By O.Kimoto 1997/05/21
			*/
 #if (PRO_FBS == ENABLE)		/* FBSからのﾛｰｶﾙｽｷｬﾝ処理追加  By S.Fukui Jan.27,1998 */
			if (SYS_ScannerExecMode == SCN_ADF) {
				doc_size = CMN_GetDocumentScanSize();
			}
			else {
				doc_size = CMN_GetFBS_DocumentScanSize();
			}
 #else
			doc_size = CMN_GetDocumentScanSize();
 #endif

#if (0)	/* ここでは制限をかけず、ＰＣの能力に合わせて縮小後、サイズを合わせます。By S.Fukui Feb.23,1998 */
//			/* PCの能力とFAXの能力でFAX側が上回っているなら縮小するなどの
//			** 処理を入れるべき｡今のとこPCの能力に合わすだけ｡(ANZUはA4しかないけど)
//			*/
//			switch (doc_size) {	/* FAXの記録幅能力 */
//				case SYS_DOCUMENT_A3_SIZE:
//					switch (CL1_PCDocumentSize) {	/* PCの記録幅能力 */
//						case SYS_DOCUMENT_A3_SIZE:
//							SYS_DocumentScanSize = SYS_DOCUMENT_A3_SIZE;
//							break;
//						case SYS_DOCUMENT_B4_SIZE:
//							SYS_DocumentScanSize = SYS_DOCUMENT_B4_SIZE;
//							break;
//						case SYS_DOCUMENT_A4_SIZE:
//							SYS_DocumentScanSize = SYS_DOCUMENT_A4_SIZE;
//							break;
//					}
//					break;
//				case SYS_DOCUMENT_B4_SIZE:
//					switch (CL1_PCDocumentSize) {
//						case SYS_DOCUMENT_A3_SIZE:
//							SYS_DocumentScanSize = SYS_DOCUMENT_B4_SIZE;
//							break;
//						case SYS_DOCUMENT_B4_SIZE:
//							SYS_DocumentScanSize = SYS_DOCUMENT_B4_SIZE;
//							break;
//						default:
//							SYS_DocumentScanSize = SYS_DOCUMENT_A4_SIZE;
//							break;
//					}
//					break;
//				case SYS_DOCUMENT_A4_SIZE:
//					SYS_DocumentScanSize = SYS_DOCUMENT_A4_SIZE;
//					break;
//			}
#endif
			/* ADFにてA4,B4,A3の順でローカルスキャンすると、全てＡ３→Ａ４(70%)縮小され、
            ** ADFにてA3,B4,A4の順でローカルスキャンすると、A3(70%),B4(81%),A4(100%)の画像
            ** がスキャンされます。By S.Fukui Feb.23,1998
			*/
			SYS_DocumentScanSize = doc_size;
			switch (doc_size) {	/* FAXの記録幅能力 */
			case SYS_DOCUMENT_A3_SIZE:
				switch (CL1_PCDocumentSize) {	/* PCの記録幅能力 */
				case SYS_DOCUMENT_A3_SIZE:
					SCN_DocumentReduction = 100;
					break;
				case SYS_DOCUMENT_B4_SIZE:
					SCN_DocumentReduction = 86;
					break;
				case SYS_DOCUMENT_A4_SIZE:
					SCN_DocumentReduction = 70;
					break;
				}
				break;
			case SYS_DOCUMENT_B4_SIZE:
				switch (CL1_PCDocumentSize) {
				case SYS_DOCUMENT_A3_SIZE:
				case SYS_DOCUMENT_B4_SIZE:
					SCN_DocumentReduction = 100;
					break;	
				default:
					SCN_DocumentReduction = 81;
					break;
				}
				break;
			case SYS_DOCUMENT_A4_SIZE:
			default:
				SCN_DocumentReduction = 100;
				break;
			}

		}
		else {
/******		SYS_DocumentScanSize = CMN_GetDocumentScanSize();
            上記のみの内容から、下記elseの内容に変更 By S.Fukui Nov.12,1997
******/

			if (((is_copy_file == TRUE) && (page_counter == 1))
			||	(is_copy_file == FALSE)) {
 #if (PRO_FBS == ENABLE)
				if (SYS_ScannerExecMode == SCN_ADF) {
					SYS_DocumentScanSize = CMN_GetDocumentScanSize();
				}
				else {
					SYS_DocumentScanSize = CMN_GetFBS_DocumentScanSize();
				}
 #else
				SYS_DocumentScanSize = CMN_GetDocumentScanSize();
 #endif
			}
		}
#else  /* (PRO_CLASS1 == ENABLE) */
		/**	コピーの読み取りではADFの1スタックで原稿サイズを変えないため、
		**	コピーの場合は先頭ページの場合だけ、読取り原稿サイズをセットする
		**	その他の場合は、毎ページ読取り原稿サイズをセットする
		*/	/* ICHOU追加  1996/08/08 s.takeuchi */
		if (((is_copy_file == TRUE) && (page_counter == 1))
		||	(is_copy_file == FALSE)) {
#if (PRO_FBS == ENABLE)
			if (SYS_ScannerExecMode == SCN_ADF) {
				SYS_DocumentScanSize = CMN_GetDocumentScanSize();
			}
			else {
				SYS_DocumentScanSize = CMN_GetFBS_DocumentScanSize();
			}
#else
			SYS_DocumentScanSize = CMN_GetDocumentScanSize();
#endif
		}
#endif	/* (PRO_CLASS1 End) */

		/*--------------------------------------------*/
		/** スキャナオープンパラメータをセットします。*/
		/*--------------------------------------------*/
		SCN_Control.UseType			= IDP_DOCUMENT_STORE;
		SCN_Control.DocumentDensity = SCN_GetScanDensity( is_copy_file );
		SCN_Control.DocumentSize	= SYS_DocumentScanSize;
		SCN_Control.ScanReduction	= 100 * 10;			   /** 原稿蓄積では、縮小率１００％をセットします */

		if (!SCN_CheckMotorStopAfterScan()) { /** モーター停止要求がなければ */
		}
		else { /** モーターの停止要求が有る */
			SCN_ModeSw = SCN_GetScanMode( is_copy_file );	/** 読み取りモードをスキャナー用グローバルにページ毎に待避 */
#if (PRO_CLASS1 == ENABLE)
			/* ANZU_L CLASS 1 -- WC97303 1997/10/16 10:30 */
			/* 複数枚原稿がそれぞれ違うモードでSCANした場合 SFINEはFINEに落してSCANする */
			/* RESOLUTION LAMP も落す SYB_ModeSw -- WC97303 1997/10/16 13:10 */
			if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
				CL1_Code = CL1_PCDocumentCode;
				CL1_Mode = CL1_PCDocumentMode;
				if (CL1_Mode < SYS_FINE) {
					SYB_ModeSw = SCN_ModeSw = CL1_Mode;
				}
				else if (CL1_Mode == SYS_FINE) {
					if ((SCN_ModeSw == SYS_GRAY64)
					 || (SCN_ModeSw == SYS_NORMAL)
					 || (SCN_ModeSw == SYS_FINE)) {
						SYB_ModeSw = CL1_Mode = SCN_ModeSw;
					}
					else {
						SYB_ModeSw = SCN_ModeSw = CL1_Mode;
					}
				}
				else {
					if ((SCN_ModeSw == SYS_GRAY64)
					 || (SCN_ModeSw == SYS_NORMAL)
					 || (SCN_ModeSw == SYS_FINE)) {
						SYB_ModeSw = CL1_Mode = SCN_ModeSw;
					}
					else {
						SYB_ModeSw = SCN_ModeSw = CL1_Mode;
					}
				}
			}
			/* ANZU_L CLASS 1 -- WC97303 1997/10/16 10:30 */
#endif /* PRO_CLASS1 end */
#if (PRO_CCD == DPI400) /* POPLAR_B/H(400x400)以外は大丈夫でしょう T.Nose 1997/07/16 */
			if (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION) {
				/* ICHOUのプリンタのデコードが遅れるため  1997/02/20 */
				if ((SCN_ModeSw == SYS_HFINE)
				&&	is_copy_file
				&&	(SCN_CopyFile->Reduction < SCN_CopyReduction)) {	/** HFINE(16x15.4)コピーの70%未満 */
					SCN_ModeSw = SYS_SFINE;				/** 強制的にSFINE(8x15.4)に変える */
				}
			}
#endif

			SCN_Control.DocumentMode = SCN_ModeSw;
		}

#if (PRO_CCD == DPI400)
		/** ハーフトーンの時はマルチコピー原稿に限り最高の解像度で蓄積 */
		if (is_copy_file
		 && ((SCN_ModeSw == SYS_GRAY16)
		  || (SCN_ModeSw == SYS_GRAY16_SEP)
		  || (SCN_ModeSw == SYS_GRAY64)
		  || (SCN_ModeSw == SYS_GRAY64_SEP))) {
			/** 強制的に解像度を16*15.4にセット */
			SCN_StoreData.Mode = SYS_HFINE;

			/*	中間調の縮小コピーで70%未満の時は、200dpiディザで読み取る
			**	(ICHOUのプリンタのデコードが遅れるため)
			**  POPLAR_B/H 以外は大丈夫でしょう T.Nose
			*/
			if ((SCN_CopyFile->Reduction < SCN_CopyReduction)	/** 70%未満 */
			 && (SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION)) {
				SCN_StoreData.Mode = SCN_ModeSw;
			}
			else if ((SCN_CopyFile->Reduction < 100)
			 && CHK_UNI_ReduceGrayCopyDither200()) {	/* 縮小で200dpiディザ指定 */
				SCN_StoreData.Mode = SCN_ModeSw;
			}
		}
		else if ((!is_copy_file)
		 && ((SCN_ModeSw == SYS_GRAY16)
		  || (SCN_ModeSw == SYS_GRAY16_SEP)
		  || (SCN_ModeSw == SYS_GRAY64)
		  || (SCN_ModeSw == SYS_GRAY64_SEP))
		 && CHK_UNI_HalfTone400DPI_ON()) {
			SCN_StoreData.Mode = SYS_HFINE;	/** 強制的に解像度を16*15.4にセット */
		}
		else {
			SCN_StoreData.Mode = SCN_ModeSw;
		}
#endif /* (PRO_CCD == DPI400) */
#if (PRO_CCD == DPI300)
		/** ハーフトーンの時はマルチコピー原稿に限り最高の解像度で蓄積 */
		if (is_copy_file
		 && ((SCN_ModeSw == SYS_GRAY16)
		  || (SCN_ModeSw == SYS_GRAY16_SEP)
		  || (SCN_ModeSw == SYS_GRAY64)
		  || (SCN_ModeSw == SYS_GRAY64_SEP))) {
			/** 強制的に解像度を300*300にセット */
			SCN_StoreData.Mode = SYS_EFINE;
		}
		else if ((is_copy_file) && (SCN_ModeSw == SYS_FINE)) {
			SCN_StoreData.Mode = SYS_EFINE;	/** 強制的に解像度を12*11.25にセット */
		}
#if (0) /* ANZU_L 送信SFINEを300×400で蓄積します by T.Soneoka 1997/11/13 */
//		else if ((is_copy_file) && (SCN_ModeSw == SYS_SFINE)) @
#endif
		else if (SCN_ModeSw == SYS_SFINE) {
			SCN_StoreData.Mode = SYS_E_HFINE;	/** 強制的に解像度を12*15.4にセット */
		}
		else {
			SCN_StoreData.Mode = SCN_ModeSw;
		}
#endif /* (PRO_CCD == DPI300) */
#if (PRO_CCD == DPI200)
		SCN_StoreData.Mode = SCN_ModeSw;
#endif

		/**	蓄積時の符号化方式(二値:MMR/中間調:MG3)をセット */ /* whileの外から移動 */
		SCN_StoreData.Code = SCN_GetDocumentStoreCode(SCN_Control.DocumentMode, SYS_DocumentStoreItem);
		SCN_StoreData.Size = SYS_DocumentScanSize;;
		if (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE) {
			/* Ａ３縮小コピー間に合わない件
			** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
			** スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
			*/
			if (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10) {
				SCN_StoreData.Size = SCN_GetCopyDocStoreSize();
			}
		}
#if (PRO_CLASS1 == ENABLE)
		/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する By S.Fukui Feb.23,1998 */
		if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
			SCN_StoreData.Size = SCN_GetLocalScanSize();
		}
#endif

#if (PRO_EXT_DMAC == ENABLE)
		/* スキャナー位相ずれデバッグ T.Nose 1998/02/05 */
		if (SYB_MaintenanceSwitch[MNT_SW_C1] & 0x40) {
			MEM_ScanFlag = 1;			/** スキャナからの原稿蓄積の時のみV53DMAのオートイニシャライズを使用するため *//* Add by NOBUKO	 Dec.21,94 */
		}
		else {
			MEM_ScanFlag = 0;			/** オートイニシャライズしない */
		}
#endif

		if (SYS_MultiProgramFlag == 1) {
			/** DRAM１ページ・マルチオープン（０以外の戻り値はメモリオーバー */
			if (ret_code = MEM_MultiWriteOpen(&SCN_StoreData, &SCN_ExecData)) {
				/** Memory Overflow, ret_code:0xFC(Index Over),0xFE(Block Over) */
				MEM_ClearBreak(&SCN_IndexData); /** 蓄積途中のファイルをクリア */
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;
				SCN_ADF_MotorStopRequest = ADF_MOTOR_MEMORY_OVER;	/* 停止要求を出す */

				/*	タスクの終了処理はループの外でする  1996/10/31 s.takeuchi */
				break;	/* ループ終了 */
			}
		}
		else {
			/** DRAM１ページ・オープン（０以外の戻り値はメモリオーバー */
			if (ret_code = MEM_WriteOpen(&SCN_StoreData, &SCN_ExecData)) {
				/** Memory Overflow, ret_code:0xFC(Index Over),0xFE(Block Over) */
				MEM_ClearBreak(&SCN_IndexData); /** 蓄積途中のファイルをクリア */
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;
				SCN_ADF_MotorStopRequest = ADF_MOTOR_MEMORY_OVER;	/* 停止要求を出す */

				/*	タスクの終了処理はループの外でする  1996/10/31 s.takeuchi */
				break;	/* ループ終了 */
			}
		}

		/*-------------------------------*/
		/** スキャナコーデックを獲得する */
		/*-------------------------------*/
		if (!GetCodec(SCANNER_CODEC, CODEC_DOCUMENT_STORE)) { /** コーデック獲得失敗 */
			SaveReturnAddressAndJumpBegin();
		}

		/* ページ単位でエンコードタスクの起動前に行う必要があるのでここで行う  1997/02/12 */
		SCN_SetScanDocumentMask();	/** 読み取りマスクの有無を決定 */

#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {	/**	ADF読取りの場合だけのタスクを起動 */
#endif
			/*
			**	原稿繰り込み不良監視タスク起動
			*/
			cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, 0);
			/*
			**	スキャナカバー監視タスク起動
			*/
			cre_tsk(&tskno_SCN_WatchDocCoverTask, TSK_SCN_WATCHDOCUMENTCOVERTASK, 0);
#if (PRO_FBS == ENABLE)
		}
		else {
			/** ミラーキャリッジエラー監視タスク起動 */
			cre_tsk(&tskno_SCN_WatchDocMirrorTask, TSK_SCN_WATCHDOCUMENTMIRRORTASK, 0);
		}
#endif

		/*-----------------------------*/
		/** 原稿１ページ蓄積タスク起動 */
		/*-----------------------------*/
		cre_tsk(&tskno_CDC_EncodePageTask, TSK_CDC_ENCODEPAGETASK, 0);

		/*---------------------------------------------------------------*/
		/** 符号化されたデータを４Ｋ単位でＤＲＡＭへ蓄積するタスクの起動 */
		/*---------------------------------------------------------------*/
		cre_tsk(&tskno_SCN_DMA_WriteTask, TSK_SCN_DMA_WRITETASK, 0);

#if (PRO_SEPERATE_24V == DISABLE)
		/* プリンターカバー監視タスク */
		cre_tsk(&tskno_SCN_WatchPrinterCoverTask, TSK_SCN_WATCHPRINTERCOVERTASK, 0);
#endif
		/*-----------------------*/
		/** スキャナー・オープン */
		/*-----------------------*/
		if (SCN_Open() == SCN_OPEN_ERROR) { /** スキャナー・カバー・オープン・エラー */
			/*---------------------------------------------*/
			/* 不要タスクの消去							   */
			/*---------------------------------------------*/
			if (tskno_SCN_WatchDocFeedTask != 0xffff) {
				del_tsk(&tskno_SCN_WatchDocFeedTask);	/* 原稿繰り込み不良監視タスク */
			}
			if (tskno_SCN_WatchDocCoverTask != 0xffff) {
				del_tsk(&tskno_SCN_WatchDocCoverTask);	/* Watch CoverStatusタスク */
			}
			if (tskno_CDC_EncodePageTask != 0xFFFF) {
				del_tsk(&tskno_CDC_EncodePageTask);		/* 原稿１ページ蓄積タスク */
				/**スキャナコーデックを解放する*/
				if (!ReleaseCodec(SCANNER_CODEC, CODEC_DOCUMENT_STORE)) {	/** コーデック開放失敗 */
					/** 有り得ないけど、とりあえずリセット処理 */
					SaveReturnAddressAndJumpBegin();
				}
			}
			if (tskno_SCN_DMA_WriteTask != 0xFFFF) {
				del_tsk(&tskno_SCN_DMA_WriteTask);		/* 符号化データをＤＲＡＭへ蓄積するタスク */
			}
#if (PRO_FBS == ENABLE)
			/** ミラーキャリッジエラー監視タスク削除 */
			if (tskno_SCN_WatchDocMirrorTask != 0xFFFF) {
				del_tsk( &tskno_SCN_WatchDocMirrorTask );
			}
#endif
#if (PRO_SEPERATE_24V == DISABLE)
			/* プリンタカバー監視タスク削除 */
			if (tskno_SCN_WatchPrinterCoverTask != 0xFFFF) {
				del_tsk(&tskno_SCN_WatchPrinterCoverTask);
			}
#endif
			MEM_ClearBreak(&SCN_IndexData);	/** 蓄積途中のファイルをクリア */

			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR; /** 原稿セットエラーをセット */

			break;	/* ループ終了 */
		}

		/* 原稿蓄積枚数表示用に原稿蓄積開始メッセージをページ毎に発行 */
		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_1PAGE_START;
		snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
		rcv_msg(mbxno.SCN_Sub, &SCN_Msg);

		/** 蓄積関連タスクの状況をメッセージで待ち受け */
		rcv_msg(mbxno.SCN_Task, &SCN_Msg);
		SCN_Message = SCN_Msg->Message;		/** テンポラリ領域へ待避 */

if (SYB_MaintenanceSwitch[MNT_SW_C6] & CHECK_SHADING_RAM) { /* 薄読みデバッグ用 */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* Shading RAMを読むため */
		DIPP_ReadShadingRAM( &SCN_DebugShadingRAM[0] );	/* 1997/04/25 */
		for (i=0; i<SYS_SHADING_MAX; i++) {
			if (SYB_ShadingRAM[i] != SCN_DebugShadingRAM[i]) {
				/* 違ったらmnt swにセット */
				SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR1;
				break;
			}
		}
		/* 初期値RAMもコンペアする  1997/04/25 */
		DIPP_ReadInitialRAM( &SCN_DebugInitialRAM1[0] );
		for (i=0; i<SYS_INITIAL_MAX; i++) {
			if ((SYB_InitialRAM[i] != SCN_DebugInitialRAM0[i])
			||	(SYB_InitialRAM[i] != SCN_DebugInitialRAM1[i])) {
				/* 初期値RAMが違ったらmntB6-0にセット */
				SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR0;
				break;
			}
		}
		DIPP_SetBitDIPPST(IDP_BIT_ON);	/* Shading RAMを読むため */
}

		/*	停止キーの時にSCN_Intの前半でモーターが止まってしまうことがあるため
		**	ここで読み取り終了状態にする	1997/04/21
		*/
		SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;

		/** 不要タスクの消去 */
		if (tskno_SCN_WatchDocFeedTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchDocFeedTask);	/* 原稿繰り込み不良監視タスク */
		}
		if (tskno_SCN_WatchDocCoverTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchDocCoverTask);	/* ADFカバー監視タスク */
		}
		if (tskno_CDC_EncodePageTask != 0xFFFF) {
			del_tsk(&tskno_CDC_EncodePageTask);		/* 原稿1ページ蓄積タスク */
			/**スキャナコーデックを解放する*/
			if (!ReleaseCodec(SCANNER_CODEC, CODEC_DOCUMENT_STORE)) { /** コーデック開放失敗 */
				SaveReturnAddressAndJumpBegin();
			}
		}
		if (tskno_SCN_DMA_WriteTask != 0xFFFF) {
			del_tsk(&tskno_SCN_DMA_WriteTask);		/** 4K単位でDRAMへ蓄積するタスク */
		}
#if (PRO_FBS == ENABLE)	/* 1997/02/13 */
		/** ミラーキャリッジエラー監視タスク削除 */
		if (tskno_SCN_WatchDocMirrorTask != 0xFFFF) {
			del_tsk( &tskno_SCN_WatchDocMirrorTask );
		}
#endif
#if (PRO_SEPERATE_24V == DISABLE)
		/* プリンタカバー監視タスク削除 */
		if (tskno_SCN_WatchPrinterCoverTask != 0xFFFF) {
			del_tsk(&tskno_SCN_WatchPrinterCoverTask);
		}
#endif

		/*
		**	メモリファイルの有効/無効を判断する
		*/
		switch (SCN_Message) {	/** メッセージ解析 */
		case	SCN_DMA_WRITE_MEMORY_OVER:			/** (1) メモリオーバー */
		case	SCN_DMA_STOP_REQUEST:				/** (2) 停止要求  SCN_DMA_WriteTask() */
		case	SCN_PRINTER_COVER_OPEN:				/** (12) プリンタカバー開 */
#if (PRO_FBS == ENABLE)
			if ((SYS_ScannerExecMode == SCN_FBS)
			&&	is_copy_file
			&&	CMN_CheckScanFilePrinting()) {		/** FBSコピーで読み取り原稿をプリント中 */
				is_file_enable = TRUE;	/** 蓄積ファイル有効 */
			}
			else {
				is_file_enable = FALSE;	/** 蓄積ファイル無効 */
			}
#else
			is_file_enable = FALSE;	/** 蓄積ファイル無効 */
#endif
			is_stop_key = TRUE;		/* 1997/04/18 */
			break;
		case	CDC_ENCODE_OK:						/** (3) 蓄積正常終了 */
			is_file_enable = TRUE;		/** 蓄積ファイル有効 */

			/* 停止処理追加(1ページOKの時も停止キーを見る)  1997/04/18 */
			if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE) {
#if (PRO_FBS == ENABLE)
				/* is_file_enable = FALSE;	FCOTプリント中はファイルを確定する  1997/05/28 */
				if (is_copy_file
				 && (SYS_ScannerExecMode == SCN_FBS)
				 && CMN_CheckScanFilePrinting()) {	/** FCOTプリント中 */
					is_file_enable = TRUE;	/** 蓄積ファイル有効 */
				}
				else {
					is_file_enable = FALSE;	/** 蓄積ファイル無効 */
				}
				is_stop_key = TRUE;
				if (SYS_ScannerExecMode == SCN_ADF) {
					SCN_ADF_MotorStopRequest = ADF_MOTOR_STOP_REQUEST;
				}
#else
				is_stop_key = TRUE;
				SCN_ADF_MotorStopRequest = ADF_MOTOR_STOP_REQUEST;
#endif
			}
			break;
		default:	/** その他のメッセージ */
			is_file_enable = FALSE;		/** 蓄積ファイル無効 */
			break;
		}

		/* 蓄積OK以外でもファイルが有効なら確定する  1996/12/16 */
		if (is_file_enable) {	/** 蓄積ページが有効 */
			/*
			**	オープンファイルのクローズ
			*/
			if (SYS_MultiProgramFlag == 1) {
				MEM_MultiWriteClose(&SCN_ExecData, SCN_TotalEncodeLine);
			}
			else {
				MEM_WriteClose(&SCN_ExecData, SCN_TotalEncodeLine);
			}
		}
		else {
			MEM_ClearBreak( &SCN_IndexData );	/** 無効ページはここで削除 */
		}

		if (!is_stop_key						/* 停止条件追加  1997/04/18 */
		 && (SCN_Message == CDC_ENCODE_OK)) {		/** １ページ蓄積完了 */
			/** バッファリングコピーのため１ページ蓄積完了をメインに通知する */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_1PAGE_FINISH;
			snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
			rcv_msg( mbxno.SCN_Task, &SCN_Msg );

#if (PRO_FBS == ENABLE)
			if (SYS_ScannerExecMode == SCN_ADF) {
#endif
				if (DS1()) {	/** ADF読取りで、次原稿があれば */
					/** 蓄積原稿のページ数更新	*/
					SCN_StoreData.Page++;
					SCN_IndexData.Page++;
					SYS_DocumentStorePage++;
				}
#if (PRO_FBS == ENABLE)
			}
#endif

			SYB_LifeMonitor.ScanCount++;	/** ライフモニタの読取り枚数加算 */

#if (PRO_FBS == ENABLE)
			if (SYS_ScannerExecMode == SCN_ADF) {
#endif
				if (SCN_CheckMotorStopAfterScan()) { /* モーター停止要求があれば */
					break_count = 0;
					while (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
						wai_tsk( 10 );		/** 100ms wait */
						if (break_count++ > 10) {
							SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
							SCN_StopMotor();	/* 最大1秒で強制停止 */
							break;
						}
					}
					CMN_PushStamp();	/** スタンプを押す */
				}
#if (PRO_FBS == ENABLE)
			}
#endif
		}

		/*
		**	メッセージの変換と１ページの後処理
		*/
		switch (SCN_Message) { /** メッセージ解析 */
		case	SCN_DMA_WRITE_MEMORY_OVER:			/** (1) メモリオーバー  SCN_DMA_WriteTask() */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;	/** メモリオーバー */
			break;
		case	SCN_DMA_STOP_REQUEST:				/** (2) 停止要求  SCN_DMA_WriteTask() */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;	/** 停止処理実行 */
			break;
		case	CDC_ENCODE_OK:						/** (3) 蓄積正常終了  CDC_EncodePageTask() */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;

			/* 停止処理追加  1997/04/18 */
			if (is_stop_key) {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;	/** 停止処理実行 */
			}
			break;
		case	CDC_MAX_LINE_OVER:					/** (4) 1m原稿長制限  CDC_EncodePageTask() */
			/** モーターは停止していない */
			SCN_ADF_MotorStopRequest = ADF_MOTOR_MAXLINE_OVER;
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MAXLINE_OVER;	/** 原稿長制限 */
			break;
		case	SCN_SCANNER_COVER_OPEN:				/** (5) SCN_WatchDocumentCoverTask() */
		case	SCN_DOC_FEED_ERROR:					/** (6) SCN_WatchDocumentFeedTask() */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;	/** 原稿エラー */
			break;
		case	SCN_PRINTER_COVER_OPEN:				/** (12) プリンタカバー開 */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
			break;
		default:
			break;
		}

		/** 蓄積異常終了時はループを抜ける */
		if (SCN_Message != CDC_ENCODE_OK) {
			break;
		}

		/**	指定枚数に達していたらループを抜ける
		**	(モーターはSCN_Intで停止する)
		*/	/* 枚数指定チェック  1997/02/18 */
		if (SCN_StorePageCountError) {
			break;
		}

		/* 停止処理追加  1997/04/18 */
		if (is_stop_key) {
			break;
		}
	}

	/** イベント待ちのプリントを動かすため */
	SYS_FCOT_PrintStartRequest = TRUE;
	det_evt( EVT_FCOT_PRINT_START );

	/**	ADFの先頭ページの読取り開始時に原稿が抜かれていた場合は「原稿エラー」で終了する	*/
	if (page_counter == 0) {
		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
	}
	/** 最終ページの蓄積が正常終了した時はスキャナの終了処理をする */
	else if ((StoreTaskMsg.Message == MSG_SCN_DOCSTORE_OK)		/*(SCN_Message == CDC_ENCODE_OK)*/
	&&		 (!SCN_StorePageCountError)) {
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {		/** ADF読取り */
#endif
			/*----------------------------------*/
			/* スキャナー・クローズの結果を判定 */
			/*----------------------------------*/
			switch (SCN_Close(SCN_DOC_EXITING)) {
			case	SCN_SCANNER_COVER_OPEN:		/** 排出中にカバーが開けれれた */
			case	SCN_DOC_FEED_ERROR:			/** 排出エラー */
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
				break;
			case	SCN_DOC_EXIT_OK:			/** 排出正常終了 */
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;
				break;
			}

			/**	ADF送信原稿蓄積で正常終了したが指定枚数に満たない時は
			**	枚数指定エラーとしてMAN_Taskに返すメッセージをセットする
			*/	/* 枚数指定チェック  1997/02/18 */
			if ((SYS_DocumentStoreItem == SYS_MEM_TX_FILE)
			&&	(SYB_CommandFile[SYS_DocumentStoreNo].Page != 0)
			&&	(SYS_DocumentStorePage < SYB_CommandFile[SYS_DocumentStoreNo].Page)) {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STR_PAGE_ERROR;
				SCN_StorePageCountError = TRUE;
			}

#if (PRO_FBS == ENABLE)
		}
		else {		/** FBS読取り */
			/** ミラーが停止するのを待つ */
			CMN_DisableInterrupt();
			if (!SCN_IsMirrorMoveEnd) {
				wai_evt( EVT_MIRROR_MOVE_END );
			}
			CMN_EnableInterrupt();

			/*--------------------------------------------------------------*/
			/* 蓄積関連子タスクからのメッセージ受信後、ミラーキャリッジが   */
			/* ＦＢＳ ＥＮＤへ移動する間にトップカバーが開けられていないか  */
			/* チェックします        T.Nose 1998/02/03                      */
			/*--------------------------------------------------------------*/
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
				snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk( 0xFFFF );
			}

			/*----------------------------------------------*/
			/** ランプを点灯しＤＩＰＰでチェックします。	*/
			/*----------------------------------------------*/
			/* ランプチェックエラーの場合、もう一回トライします T.Nose 1998/01/25 */
			i = 2;
			is_lamp_ok = TRUE;
			while (i > 0) {
				if (DIPP_CheckLamp() == NG) { /** ランプ点灯が異常 */
					i--;
				}
				else { /* ランプチェックＯＫ */
					break;
				}
			}
			if (i == 0) {
				is_lamp_ok = FALSE;
			}
			if (is_lamp_ok == FALSE) {
				/** イベント待ちのプリントを動かすため */
				SYS_FCOT_PrintStartRequest = TRUE;
				det_evt( EVT_FCOT_PRINT_START );

				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_LAMP_ERROR;	/** ランプエラーをセット */
				snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk( 0xFFFF );
			}

			/**	ミラーがFBS後端に正常に停止したなら、蓄積タスクを正常終了とする
			**	(ミラーの引き戻し処理はメインタスクから起動される別タスクで行う)
			*/
			if ((SCN_MirrorCarriageStatus == MIRROR_FBS_END_STOP)
			&&	(SCN_MirrorMoveStatus == MIRROR_MOVE_OK)) {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;
			}
			else {
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MIRROR_ERROR;
				SYB_MaintenanceSwitch[MNT_SW_C5] = 8;	/* エラーコードをセット */
			}
		}
#endif
	}
	else {	/** 異常終了時 (MSG_SCN_DOCSTORE_OK以外) */
#if (PRO_FBS == ENABLE)
		/**	ADF読取りの時は、モーターが停止するのを待つ
		**	(モーターがミラーキャリッジ側に切り替わらないため)
		*/
		if (SYS_ScannerExecMode == SCN_ADF) {
			break_count = 0;	/* 1997/03/07 */
			while (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
				wai_tsk( 10 );

				/* 約1秒間待ってSTOPにならなかったら抜ける  1997/03/07 s.takeuchi */
				if (break_count++ > 10) {
					SYB_MaintenanceSwitch[MNT_SW_C6] |= ADF_MOTOR_STOP_TIME_OUT;
					break;
				}
			}
		}
		else {	/* 正規の動作で停止させるため追加  1997/04/21 */
			/** FBSの時は中断停止要求を出し、ミラーが停止するのを待つ */
			CMN_DisableInterrupt();
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
			SCN_MirrorCarriageStatus = MIRROR_MOVE_ABORT;
			if (!SCN_IsMirrorMoveEnd) {
				wai_evt( EVT_MIRROR_MOVE_END );
			}
			CMN_EnableInterrupt();
			/** スキャナモータの回転方向を変えるために待つ */
			wai_tsk( SCN_MotorChangeInterval );
		}
#endif
		LampOff();	/** ランプを消す */	/* 1997/02/13 */
	}

	/*	最後に停止キーを直接見て、停止処理する
	**	(原稿はMAN_Task側で消去される)
	**		1997/04/18 s.takeuchi
	*/
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE) {	/** 停止キーあり */
		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;
		if (StoreTaskMsg.Message != MSG_SCN_DOCSTORE_OK) {
			/* ADFで最終原稿なら排出する */
#if (PRO_FBS == ENABLE)
			if (SYS_ScannerExecMode == SCN_ADF) {
#endif
				if (!DS1()) {
					switch (SCN_Close(SCN_DOC_EXITING)) {
					case	SCN_SCANNER_COVER_OPEN:
					case	SCN_DOC_FEED_ERROR:
						StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
						break;
					case	SCN_DOC_EXIT_OK:
						/* MANへのメッセージは停止のまま変えない */
						break;
					}
				}
#if (PRO_FBS == ENABLE)
			}
#endif
		}
	}

	DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* DIPP 停止 T.nose 1997/11/25 */
	StoreTaskMsg.Item = FROM_DOCSTORE;
	wai_tsk(50);	/** Oct.12,1994 */
	snd_msg( mbxno.MAN_Task, &StoreTaskMsg );
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk( 0xFFFF );
}
/** Module Header For CIM-E ********************************************
		module		:	[符号化データ蓄積タスク]
		function	:	[
						１．４Ｋ単位で符号化されたデータをＤＲＡＭへ転送
						２．４Ｋ消費後新たなブロックを探す
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
static	MESSAGE_t SCN_DMA_WriteTaskMsg = {0};
static	UWORD result = 0;

void SCN_DMA_WriteTask(void)
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*//*add by M.Kotani 1997/11/26*/
	struct DMA_Data_t MEM_WriteDMA;
#endif

	SCN_DMA_WriteTaskMsg.Item = FROM_SCN_SUB_TASK;

	while(1) {
		result = MEM_Write(MEM_SCANNER, &SCN_ExecData); /** 次ブロックを獲得できれば４ＫバイトのＤＭＡを起動 */

		if (result == MEM_BLOCK_OVER) { /** 次ブロックが無い */
			SCN_DMA_WriteTaskMsg.Message = SCN_DMA_WRITE_MEMORY_OVER;

			/* 完全に止まるのを待つため、追加  1996/10/28 */
			CMN_DisableInterrupt();
			SCN_ADF_MotorStopRequest = ADF_MOTOR_MEMORY_OVER;
			CMN_EnableInterrupt();
			break;
		}
		else if (result == MEM_STOP_SW) { /** ＤＭＡ転送中に停止キーが押された */
			SCN_DMA_WriteTaskMsg.Message = SCN_DMA_STOP_REQUEST;

			/* 完全に止まるのを待つため、追加  1996/10/28 */
			CMN_DisableInterrupt();
			SCN_ADF_MotorStopRequest = ADF_MOTOR_STOP_REQUEST;
			CMN_EnableInterrupt();
			break;
		}
#if (0)
		else { /** ４Ｋバイト正常に転送終了 */
		}
#endif
	}
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用 DMAを止めない*//*add by M.Kotani 1997/11/26*/
	MEM_WriteDMA.Channel = DMA_SCNCDC_DRAM_CH;		/** DMA Channel指定 */
	MEM_WriteDMA.SrcAddress = (UDWORD)&EcmBuffer2;	/** DMA開始アドレス指定 *//*ECMバッファに捨てる*/
	MEM_WriteDMA.Counter = (UWORD)(0xFFFF / 2);		/** 転送WORD数指定 １を引かなくしたM.Kotani1996/12/17*/
	MEM_WriteDMA.Unit = DMA_WORD_TRANSFER;			/** WORD転送指定 */
	MEM_WriteDMA.Direction = DMA_IO_TO_MEMORY;		/** 転送方向指定 */
	DMA_SetupDMAU(&MEM_WriteDMA);					/** DMAU Setup */
	DMA_RequestEnable(MEM_WriteDMA.Channel);		/** DMA Start (CODEC -> DRAM) */
	if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_ADJUST) {
		SCN_StopMotor();
		SCN_MotorCurrentStopCounter = 0;
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_ADJUST;
	}
#endif
	snd_msg( mbxno.SCN_Task, &SCN_DMA_WriteTaskMsg ); /** 蓄積タスクへ結果を通知 */
	wai_tsk(0xffff); /** 殺されるまで待つ */
}

/** Module Header For CIM-E ********************************************
		module		:	[符号化データ蓄積タスク終了処理]
		function	:	[
						１．スキャナーコーデック→ＤＲＡＭのＤＭＡをマスクします
						２．オートイニシャライズをディセーブルします
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[1998/02/09]
		author		:	[野瀬敏弘]
************************************************************************/
void SCN_DMA_WriteTaskExit(void)
{
	DMA_RequestMask(DMA_SCNCDC_DRAM_CH);
	DMA_AutoInitializeDisable(DMA_SCNCDC_DRAM_CH);
	exi_tsk();
}

/** Module Header For CIM-E ********************************************
		module		:	[蓄積中の繰り込み不良検出タスク]
		function	:	[
						１．読み取り開始後、ＤＳ３がＯＮになるまでのステップを監視する。
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
void SCN_WatchDocumentFeedTask( void )
{
	MESSAGE_t SCN_WatchDocumentFeedTaskMsg = {0};

	SCN_WatchDocumentFeedTaskMsg.Item = FROM_SCN_SUB_TASK;
	SCN_WatchDocumentFeedTaskMsg.Message = SCN_DOC_FEED_ERROR;

	/* ソフトコーデックなど他の処理が重くなった時、ここへ来た時には
	** 既にＤＳ２ＯＮ、読取り開始割り込みも経過している時がある。
	** その場合にはＡＤＦを停止し、原稿詰まりエラーで終了させる。
	** T.Nose 1997/12/05
	*/
	if (SCN_PageChangeTimeOut == FALSE) {
		wai_evt(EVT_SCN_FEED_ERROR);
	}

	snd_msg(mbxno.SCN_Task, &SCN_WatchDocumentFeedTaskMsg);
	wai_tsk(0xFFFF);
}
/** Module Header For CIM-E ********************************************
		module		:	[原稿一ページ排出正常終了監視タスク]
		function	:	[
						１．ＤＳ３がＯＦＦになるのを監視。
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
void SCN_WatchDocumentExitTask( void )
{
	MESSAGE_t SCN_WatchDocumentExitTaskMsg = {0};

	SCN_WatchDocumentExitTaskMsg.Item = FROM_SCN_SUB_TASK;
	SCN_WatchDocumentExitTaskMsg.Message = SCN_DOC_EXIT_OK;

	wai_evt(EVT_SCN_DOC_OUT_OK);

	snd_msg(mbxno.SCN_Task, &SCN_WatchDocumentExitTaskMsg);
	wai_tsk(0xFFFF);
}
/** Module Header For CIM-E ********************************************
		module		:	[蓄積中のスキャナー・カバー・オープン監視タスク]
		function	:	[
						１．１００ｍｓｅｃ毎にスキャナー・カバー・オープンを監視する。
						２．カバーが開いていればモーターを停止し、
						３．その旨を蓄積タスクへ通知する。
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
void SCN_WatchDocumentCoverTask( void )
{
	MESSAGE_t SCN_WatchDocumentCoverTaskMsg = {0};
	SCN_WatchDocumentCoverTaskMsg.Item = FROM_SCN_SUB_TASK;
	SCN_WatchDocumentCoverTaskMsg.Message = SCN_SCANNER_COVER_OPEN;

	/*-------------------------------------------------------------------------
	** 読み取り中なのになぜかモータが停止している不具合対策
	** 1997/05/10 H.Yoshikawa
	*/
	SCN_PreINT_Counter = 0;
	SCN_WatchDocTimer = 0;

	while (1) {
		if (TXIL()) {
			SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
			/* SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;  1996/11/15 */
			break;
		}
#if (PRO_FBS == ENABLE) || (PRO_UPPER_COVER == ENABLE) /* トップカバーの条件追加 1998/01/19  By T.Yamaguchi */
		if (SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_BOOK_OPEN)) {	/** FBSカバーオープン(APS) */
			SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
			break;
		}
#endif

		/*-------------------------------------------------------------------------
		** ライン割り込みカウンター
		** メモリ蓄積時は、一定速で読み取りを行っているので、このカウンターも一定周期でインクリメントされている。
		** 読み取り中なのになぜかモータが停止している不具合対策
		** 一定周期でカウントアップされるべきこのカウンターが１０秒間インクリメントされていない場合には、
		** 不具合発生として、ＳＣＮタスクを終了し、原稿ＪＡＭ状態にするようにする。
		** 1997/05/10 H.Yoshikawa
		*/
		if ((SCN_DocumentStatus == SCN_DOC_IN_SCANNING) ||		/** 原稿SCANNINGなら */
			(SCN_DocumentStatus == SCN_DOC_DS2_OFF)) {			/* 原稿読取り中でDS2 OFF検出直後なら*/
			if (SCN_PreINT_Counter == SCN_INT_Counter) {
				SCN_WatchDocTimer++;
				if (SCN_WatchDocTimer > (10 * 10)) {	/* 1997/06/02 H.Yoshikawa 100 -> 10 */
					SCN_ADF_MotorStopRequest = ADF_MOTOR_COVER_OPEN;
 					SYB_MaintenanceSwitch[MNT_SW_C6] |= ADF_WATCH_DOC_RESET;
					break;
				}
			}
			else {
				SCN_WatchDocTimer = 0;
			}
			SCN_PreINT_Counter = SCN_INT_Counter;
		}
		else {
			SCN_WatchDocTimer = 0;
		}

		wai_tsk(10); /** 100msec wait */
	}
	snd_msg(mbxno.SCN_Task, &SCN_WatchDocumentCoverTaskMsg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[ミラーキャリッジエラー監視タスク]
	function	:[
		FBS読み取り中にミラーキャリッジエラーが発生した時に
		スキャンタスクを停止させるため
		1.	読み取り中のミラーキャリッジエラーを100ms毎に監視する
		2.	発生するとスキャンタスクにメッセージを送る
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1997/02/13]
	author		:[竹内茂樹]
*************************************************************************/
void	SCN_WatchDocumentMirrorTask( void )
{
#if (PRO_FBS == ENABLE)
	MESSAGE_t		message = {0};

	message.Item = FROM_SCN_SUB_TASK;
	message.Message = SCN_SCANNER_MIRROR_ERROR;

	while (1) {
		if (SCN_MirrorMoveStatus == MIRROR_MOVE_ERROR) {
			break;
		}
		wai_tsk( 10 );	/** 100ms wait */
	}

	snd_msg( mbxno.SCN_Task, &message );
	wai_tsk( 0xFFFF );
#endif
}

#if (PRO_SEPERATE_24V == DISABLE)
/*************************************************************************
	module		:[プリンタカバー開監視タスク]
	function	:[
		スキャナー稼働中にプリンタカバーが開けられた時に-
		スキャンタスク及びミラータスクを停止させるため
		1.	１０ｍｓ割込みから立てられるイベントを待つ
		2.	発生するとスキャンタスクにメッセージを送る
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1997/08/25]
	author		:[野瀬敏弘]
*************************************************************************/
void SCN_WatchPrinterCoverTask(void)
{
	MESSAGE_t		message = {0};

	message.Item = FROM_SCN_SUB_TASK;
	message.Message = SCN_PRINTER_COVER_OPEN;

	wai_evt(EVT_SCN_TOP_COVER_OPEN);
	snd_msg(mbxno.SCN_Task, &message);
	wai_tsk(0xFFFF);
}
#endif

/** Module Header For CIM-E ********************************************
		module		:	[ギア・バック・ラッシュ終了監視タスク]
		function	:	[モーターが逆回転で設定数回転するのを待つ]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/6/20]
		author		:	[川崎真史]
************************************************************************/
void SCN_WatchGearBackLashTask( void )
{
	MESSAGE_t SCN_WatchGearBackLashTaskMsg = {0};

	SCN_WatchGearBackLashTaskMsg.Item = FROM_SCN_SUB_TASK;
	SCN_WatchGearBackLashTaskMsg.Message = SCN_GEAR_BACK_LASH_OK;

	wai_evt(EVT_SCN_GEAR_BACK_LASH_END);

	snd_msg(mbxno.SCN_GearBackLashTask, &SCN_WatchGearBackLashTaskMsg);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[セットされている原稿の排出監視タスク]
		function	:	[
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[
							#define	MSG_DOCUMENT_OUT_OK					1
							#define	MSG_DOCUMENT_OUT_ERROR				2
							#define	MSG_DOCUMENT_OUT_NEXTPAGE_OK		3
							#define	MSG_DOCUMENT_OUT_NEXTPAGE_ERROR		4
						]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/6/27]
		author		:	[川崎真史]
************************************************************************/
void MAN_DocumentOutTask( void )
{
	UBYTE doc_stat;
	StoreTaskMsg.Item = FROM_DOCUMENT_OUT;

#if (PRO_FBS == ENABLE)
	/** スキャナモーターをADF側に切替える */
	SCN_SetMotorDrive( SCN_ADF );
#endif

	/*----------------------------------*/
	/* スキャナー・クローズの結果を判定 */
	/*----------------------------------*/
	if (DS1()) {
		if (DS2()) {
			doc_stat = SCN_DOC_FEED_DS2OFF_WAIT;
		}
		else {
			doc_stat = SCN_DOC_FEED_DS2ON_WAIT;
		}
	}
	else {
		if (DS2()) {
			doc_stat = SCN_DOC_FEED_DS2OFF_WAIT;
		}
		else {
			doc_stat = SCN_DOC_FEED_DS3OFF_WAIT;	/* 排出完了ステップだけ送る  1996/07/15 s.takeuchi */
		}
	}

	/* DS2割り込みの許可/禁止はSCN_Close()で行う  1996/09/28 s.takeuchi */

	switch (SCN_Close(doc_stat)) {
	case	SCN_SCANNER_COVER_OPEN:	/** 排出中にカバーが開けれれた */
	case	SCN_DOC_FEED_ERROR:		/** 排出エラー */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_ERROR;
		break;
	case	SCN_DOC_EXIT_OK:		/** 排出正常終了 */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_OK;
		break;
	}

#if (PRO_FBS == ENABLE)
	/** スキャナモーターをFBS側に切替える(戻す) */
	/* SCN_SetMotorDrive( SCN_FBS );  1996/10/31 */
#endif

	wai_tsk( 10 );	/* MAN_Taskでカバーオープンにならないため待つ  1996/10/31 */

	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[スタンプ・テスト・タスク]
		function	:	[
						・原稿をセット後、工場ファンクションのスタンプテストを起動
						・スタンプ・テスト・タスク起動された直後ＤＳ１、２がＯＮであれば
						　ＤＳ３へ原稿を移動させ、一旦原稿を停止させる。
						・これ以降内部スタンプ設定に関らずスタンプを約５ｃｍ間隔で、ＤＳ２
						　がＯＦＦするまで押す。
						・ＤＳ２がＯＦＦした後は原稿排出。
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/8/22]
		author		:	[川崎真史]
************************************************************************/
void SCN_StampTestTask( void )
{
	UWORD pps = 0;
	UWORD step = 0;
	UBYTE exit_flag = FALSE;

	StoreTaskMsg.Item = FROM_SCN_STAMP_TEST_TASK;

	/*	ICHOUにはDS3がないため、スタンプテストタスクでは、DS2ON割り込みと
	**	スキャンスタート割り込みで、スタンプを最初に押す位置に停止させる
	**		1996/07/16 s.takeuchi
	*/
	/**	DS2ONからスタンプ位置までのステップ数をG/Aにセットし、DS2割り込みを許可する */
	SCN_SetScanStartStep( SYB_MachineParameter[3] + (UBYTE)((ADF_READ_POINT_TO_STAMP + ADF_DOC_EDGE_TO_STAMP)/10) );
	/* SCN_SetDS2_ON_Int( SCN_ENABLE );  この処理はSCN_Close()でする  1996/09/28 s.takeuchi */

	/*----------------------------------*/
	/* 原稿先端をスタンプ位置へ移動		*/
	/*----------------------------------*/
	switch (SCN_Close(SCN_DOC_STAMP_TEST_FEED_READY)) {	/** 原稿を待機位置からスタンプ位置へ移動させる。 */
	case	SCN_SCANNER_COVER_OPEN:	/** スタンプ位置へ移動中にカバーが開けれれた */
	case	SCN_DOC_FEED_ERROR:		/** 繰り込み不良 */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_ERROR;
		break;
	case	SCN_DOC_EXIT_OK:		/** スタンプ位置で停止終了 */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_OK; /** スタンプ位置で正常に停止していれば */
		break;
	}

	if (StoreTaskMsg.Message == MSG_DOCUMENT_OUT_OK) { /** スタンプ位置で正常に停止していれば */

		SYS_StampFlag = 1; /** スタンプ設定ＯＮ */

		SCN_DocumentStatus = SCN_DOC_STAMP_TEST_ON_GOING;

		/*	DS3はないので、ここではDS2に原稿がある時にスタンプを押すようにする
		**		条件の DS3() を DS2() に置き換える
		*/

		while (DS2() && !exit_flag) { /** 原稿がスタンプ位置にある間５０ｍｍ間隔でスタンプを押し続ける */

			wai_tsk(50); /** モーターの慣性による移動を避けるため５００ｍｓウェイト */

			if (DS2()) {/** ＤＳ２がＯＮ（原稿がスタンプの押せる位置にある） */
				CMN_PushStamp(); /** スタンプを押す */
			}
			else { /** ＤＳ２がＯＦＦ（原稿がスタンプ押す位置よりはずれた） */
				break;
			}

			SCN_SetMotor(SCN_DISABLE); /** モーター・ディスエーブル */

			/** Ｓファインモードでモーターを５ｃｍ移動させる */
/*			SCN_VerticalMode = SCN_SFINE_FEED; H/Lの騒音対策 1998/03/02 */
			SCN_VerticalMode = SCN_SFINE;
			SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];
/*			SCN_MotorTablePoint = SCN_MotorPointer->InitialSpeed; H/Lの騒音対策 1998/03/02 */
			SCN_MotorTablePoint = SCN_MotorPointer->TopSpeed;
			SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;
			pps = SCN_MotorPointer->ThroughUpDownTable[SCN_MotorTablePoint].PPS;
			step = 770; /** スタンプを押す間隔(50mm)をステップ数(15.4step/mm)でセット */

			/** モーターの速度設定  MTPC0,1 */
			SCN_SetMotorPulseRate( pps );

			/** モーターの速度変更間隔設定  MTP0 */
			SCN_SetMotorIntStep( step, SCN_MotorPointer->ExciteMethod );

			SCN_LatchMotorSpeedAndInterval();			/** モーター速度変更間隔、速度初期ラッチ */
			SCN_SetMotorSpeedIntervalInt(SCN_ENABLE);	/** モーター速度変更間隔割り込み許可 */
			SCN_SetMotorCurrent(SCN_CURRENT_POWER_100);	/** モーターの電流値を１００％にセット */
			SCN_SetMotorExciteMethod( SCN_MotorPointer->ExciteMethod );	/* モーター励磁相設定 (MTP1) 1998/03/03 */
			SCN_SetDS2_OFF_Int(SCN_ENABLE);				/** ＤＳ２　ＯＦＦ割り込み許可 */

			/** 読み取り後端ステップ設定、初期ラッチ */
#if (PRO_DOC_IN == ENABLE) /* ANZU_L */
			if (SCN_MotorPointer->ExciteMethod == SCN_MOTOR_2_EXCITE) {
				SCN_SetScanEndStep(SYB_MachineParameter[4]);
			}
			else {
				SCN_SetScanEndStep(SYB_MachineParameter[19]);
			}
#else
			SCN_SetScanEndStep(SYB_MachineParameter[4]);
#endif

			SCN_ADF_MotorStopRequest = ADF_MOTOR_NO_STOP;	/* 1996/10/29 s.takeuchi */

			SCN_SetMotor(SCN_ENABLE); /** モーター・イネーブル・セット MTEN-MTCNT */

			if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_ON_GOING) { /** スタンプテスト実行中 */
				wai_evt(EVT_SCN_DOC_OUT_OK); /** ５ｃｍ移動のイベントを待ち */
			}
			else {	/* SCN_DOC_STAMP_TEST_STOP / SCN_DOC_STAMP_TEST_ERROR */
				exit_flag = TRUE;
			}
		}

		if (SCN_DocumentStatus == SCN_DOC_STAMP_TEST_ERROR) {
			StoreTaskMsg.Message = MSG_DOCUMENT_OUT_ERROR;
		}
		else {
			/* スキャナー・クローズの結果を判定 */
			switch (SCN_Close(SCN_DOC_FEED_OUT)) {	/** スキャナー・クローズ */
			case	SCN_SCANNER_COVER_OPEN:		/** 排出中にカバーが開けれれた */
			case	SCN_DOC_FEED_ERROR:			/** 排出エラー */
				StoreTaskMsg.Message = MSG_DOCUMENT_OUT_ERROR;
				break;
			case	SCN_DOC_EXIT_OK:			/** 排出正常終了 */
				StoreTaskMsg.Message = MSG_DOCUMENT_OUT_OK;
				break;
			}
		}
	}

	SYS_StampFlag = 0; /** スタンプ設定ＯＦＦ */

	wai_tsk( 10 );	/* MAN_Taskでカバーオープンにならないため待つ  1996/10/31 */

	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
	module		:	[原稿排出中のページ間ＤＳ２ＯＦＦ監視タスク]
	function	:	[
		１．
	]
	return		:	[無し]
	common		:	[]
	condition	:	[]
	comment		:	[]
	machine		:	[SH7043]
	language	:	[SHC]
	keyword		:	[SCN]
 	date		:	[97/05/23]
	author		:	[野瀬敏弘]
************************************************************************/
void SCN_DocumentPageCountTask(void)
{
	MESSAGE_t DocumentPageCountTaskMessage;

	DocumentPageCountTaskMessage.Item = FROM_MAN_DOCUMENT_WATCH_TASK;
	DocumentPageCountTaskMessage.Message = SCN_DOC_PAGE_COUNT;

	while (1) {
		wai_evt(EVT_DOC_PAGE_COUNT);
		snd_msg(mbxno.SCN_Task,&DocumentPageCountTaskMessage);
	}
}

/** Module Header For CIM-E ********************************************
	module		:	[原稿排出・テスト・タスク]
	function	:	[
		・原稿をセット後、工場ファンクション（ＴＢＤ）の原稿排出テストを起動
		・ＡＤＦに原稿がある限り原稿排出を続ける
	]
	return		:	[無し]
	common		:	[]
	condition	:	[]
	comment		:	[]
	machine		:	[SH7043]
	language	:	[SHC]
	keyword		:	[SCN]
	date		:	[1997/05/22]
	author		:	[野瀬敏弘]
************************************************************************/
void SCN_DocumentOutTestTask(void)
{
	UBYTE disp_buf[3];
	UBYTE roop_flag;

	StoreTaskMsg.Item = FROM_DOC_OUT_TEST_TASK;

	tskno_SCN_WatchDocumentExitTask = 0xffff;
	tskno_SCN_WatchDocFeedTask = 0xffff;
	tskno_SCN_WatchDocCoverTask = 0xffff;
	tskno_SCN_DocumentPageCountTask = 0xffff;

	SYS_DocumentStorePage = 0;
	SCN_FeedErrorCheckStep = 0;
	SCN_ADF_MotorStopRequest = ADF_MOTOR_NO_STOP;
	SCN_VerticalMode = SCN_DOC_OUT;							/** 原稿繰り込み又は排出用のモードにセット */
	SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];	/** モーター制御用テーブルのポインター確保 */
	SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;		/** モーターのテーブルを初期値にセット */
	SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;				/** モーターをスルー・アップするように設定 */
	SCN_DocumentStatus = SCN_DOC_FEED_DS2ON_WAIT;
	SCN_DocExitTopSpeedCount = SCN_DOC_EXIT_STEP;		/** 原稿排出時にDS1/DS2に原稿が無くなってから最高速でまわす回数 1632step */

#if (PRO_PANEL == ANK)
	ClearDisplayLow(); /* 下段表示のクリア */
#endif
#if (PRO_PANEL == KANJI)
	ClearString2();
#endif

	/*---------------------------------*/
	/** 原稿排出正常終了監視タスク起動 */
	/*---------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocumentExitTask, TSK_SCN_WATCHDOCUMENTEXITTASK, 0);

	/*----------------------------------*/
	/** 原稿繰り込み不良監視 タスク起動 */
	/*----------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, 0);

	/*--------------------------------*/
	/** Watch Cover Status タスク起動 */
	/*--------------------------------*/
	cre_tsk(&tskno_SCN_WatchDocCoverTask, TSK_SCN_WATCHDOCUMENTCOVERTASK, 0);

	/*--------------------------------*/
	/** 原稿排出ページカウントタスク  */
	/*--------------------------------*/
	cre_tsk(&tskno_SCN_DocumentPageCountTask, TSK_SCN_DOCUMENTPAGECOUNTTASK, 0);

#if (PRO_FBS == ENABLE)
	SCN_SetMotorDrive( SCN_ADF );		/** スキャナモーターをADF側に切替える */
#endif
	SCN_SetDS2_ON_Int( SCN_ENABLE );	/** ＤＳ２ＯＮ 割り込み許可 */
	SCN_SetDS2_OFF_Int( SCN_DISABLE );	/** ＤＳ２ＯＦＦ 割り込み禁止 */
	SCN_SetLineInt(SCN_DISABLE); 		/** ライン割り込み禁止 */
	SCN_SetScanDMA(SCN_DISABLE); 				/** スキャン用ＤＭＡ禁止 */
	SCN_SetMotorSpeed(); 						/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
	SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル */
	SCN_LatchMotorSpeedAndInterval(); 			/** モーター速度変更間隔、速度初期ラッチ */
	SCN_SetMotorSpeedIntervalInt(SCN_ENABLE); 	/** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
	SCN_SetMotorPulse(SCN_ENABLE); 				/** モーター励磁ＯＮ MTCLR-MTCNT */
	SCN_SetMotorClockwise( SCN_DISABLE );		/** モーター正転 */
	SCN_SetMotor(SCN_ENABLE); 			/** モーター・イネーブル・セット MTEN-MTCNT */

	/* ＡＤＦ上に原稿がなくなるまで排出を続ける */
	roop_flag = TRUE;
	while (roop_flag == TRUE) {

		/* 排出ページ数の表示 */
		CMN_UnsignedIntToASC_NULL(disp_buf, SYS_DocumentStorePage, 2, '0');
#if (PRO_PANEL == ANK)
		DisplayStringLow((UBYTE)1, disp_buf);
#endif
#if (PRO_PANEL == KANJI)
		DisplayString2(disp_buf);
#endif
		/* 排出結果をメッセージで受ける */
		rcv_msg(mbxno.SCN_Task, &SCN_Msg);

		/* メッセージの解析 */
		switch (SCN_Msg->Message) {
		case SCN_SCANNER_COVER_OPEN:	/** 排出中にカバーが開けられた */
#if (PRO_PANEL == ANK)
			DisplayStringLow((UBYTE)0, D2W_PleaseCloseScannerCover);	/* "ｹﾞﾝｺｳｶﾊﾞｰｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
#endif
#if (PRO_PANEL == KANJI)
			DisplayString2(D4W_CloseScannerCover);
#endif
			StoreTaskMsg.Message = MSG_DOC_OUT_COVER_ERROR;
			roop_flag = FALSE;
			break;
		case SCN_DOC_FEED_ERROR:		/** 排出エラー */
#if (PRO_PANEL == ANK)
			DisplayStringLow((UBYTE)0, D2W_ResetDocument);				/* "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ" */
#endif
#if (PRO_PANEL == KANJI)
			DisplayString2(D4W_ResetDocument);
#endif
			StoreTaskMsg.Message = MSG_DOC_OUT_FEED_ERROR;
			roop_flag = FALSE;
			break;
		case SCN_DOC_PAGE_COUNT:		/** 排出ページカウント */
			SYS_DocumentStorePage++;	/* ページカウンタインクリメント */
			break;
		case SCN_DOC_EXIT_OK:			/** 排出正常終了 */
			StoreTaskMsg.Message = MSG_DOC_OUT_COMPLETE;
			roop_flag = FALSE;
			break;
		default: /* あり得ない */
			roop_flag = FALSE;
			break;
		}

		/* モード変更があれば、モーターストップ・モードの設定 */

	}

	/**********************************/
	/* 原稿排出テストタスクの終了処理 */
	/**********************************/

	/* 各監視タスクの削除 */
	if (tskno_SCN_WatchDocumentExitTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocumentExitTask);
	}
	if (tskno_SCN_WatchDocFeedTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocFeedTask);
	}
	if (tskno_SCN_WatchDocCoverTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocCoverTask);
	}
	if (tskno_SCN_DocumentPageCountTask != 0xffff) {
		del_tsk(&tskno_SCN_DocumentPageCountTask);
	}

	/* 排出の結果をメインタスクへ通知 */
	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿を待機位置へ移動中の原稿が正常にセットされたかを検出するタスク]
		function	:	[
						１．ＤＳ２　ＯＮ直後にモーターをスルー・ダウンし停止する。
						２．イベントを発行する。
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/6/20]
 		author		:	[川崎真史]
************************************************************************/
void MAN_WatchDocumentSetTask( void )
{
	MESSAGE_t		WatchDocumentSetTaskMessage = {0};
	WatchDocumentSetTaskMessage.Item = FROM_MAN_DOCUMENT_WATCH_TASK;
	WatchDocumentSetTaskMessage.Message = MSG_DOCUMENT_SET_OK;

	wai_evt(EVT_SCN_DOCUMENT_SET_OK);

	snd_msg(mbxno.MAN_DocumentInTask, &WatchDocumentSetTaskMessage);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿を待機位置へ移動中の原稿引き抜き検出タスク]
		function	:	[
						１．モーター速度変更間隔毎にＤＳ１を監視する。
						２．原稿がなければモーターを停止し、
						３．イベントを発行する。
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/6/20]
 		author		:	[川崎真史]
************************************************************************/
void MAN_WatchDocumentOutTask( void )
{
	MESSAGE_t		WatchDocumentOutTaskMessage = {0};
	WatchDocumentOutTaskMessage.Item = FROM_MAN_DOCUMENT_WATCH_TASK;
	WatchDocumentOutTaskMessage.Message = MSG_DOCUMENT_OUT;

	wai_evt(EVT_SCN_NO_DOC);

	snd_msg(mbxno.MAN_DocumentInTask, &WatchDocumentOutTaskMessage);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿を待機位置へ移動中の繰り込み不良検出タスク]
		function	:	[
						１．ＤＳ１　ＯＮ後、ＤＳ２がＯＮになるまでのステップを監視する。
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/6/20]
 		author		:	[川崎真史]
************************************************************************/
void MAN_WatchDocumentFeedTask( void )
{
	MESSAGE_t		WatchDocumentFeedTaskMessage = {0};
	WatchDocumentFeedTaskMessage.Item = FROM_MAN_DOCUMENT_WATCH_TASK;
	WatchDocumentFeedTaskMessage.Message = MSG_DOCUMENT_FEED_ERROR;

	wai_evt(EVT_SCN_FEED_ERROR);

	snd_msg(mbxno.MAN_DocumentInTask, &WatchDocumentFeedTaskMessage);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿を待機位置へ移動中のスキャナー・カバー・オープン監視タスク]
		function	:	[
						１．モーター速度変更間隔毎にスキャナー・カバー・オープンを監視する。
						２．カバーが開いていればモーターを停止し、
						３．イベントを発行する。
						]
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
  		language	:	[MSC(V53)]
 		keyword		:	[]
     	date		:	[94/6/20]
 		author		:	[川崎真史]
************************************************************************/
void MAN_WatchDocumentCoverTask( void )
{
	MESSAGE_t		WatchDocumentCoverTaskMessage = {0};
	WatchDocumentCoverTaskMessage.Item = FROM_MAN_DOCUMENT_WATCH_TASK;
	WatchDocumentCoverTaskMessage.Message = MSG_DOCUMENT_FEED_ERROR;

	wai_evt(EVT_SCN_COVER_OPEN);

	snd_msg(mbxno.MAN_DocumentInTask, &WatchDocumentCoverTaskMessage);
	wai_tsk(0xFFFF);
}

/** Module Header For CIM-E ********************************************
		module		:	[原稿繰り込みタスク]
		function	:	[	１．ランプ点灯
							２．シェーディング・データの取り込み
							３．原稿をＤＳ２の手前まで繰り込む
  		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[原稿がセットされた直後に起動される]
		machine		:	[]
  		language	:	[]
 		keyword		:	[]
     	date		:	[94/3/30]
 		author		:	[川崎真史]
	#define FROM_DOCUMENT_IN			6
		#define	MSG_DOCUMENT_IN_SETUP		1
		#define	MSG_DOCUMENT_IN_ERROR		2
		#define MSG_DOCUMENT_IN_NOTHING		3
		#define	MSG_DOCUMENT_IN_LAMP_ERROR	4
************************************************************************/
static	MESSAGE_t		DocumentInTaskMessage = {0};
static	MESSAGE_t		*Msg = 0;

static	UWORD	tskno_MAN_WatchDocumentSetTask = 0;
static	UWORD	tskno_MAN_WatchDocumentOutTask = 0;
static	UWORD	tskno_MAN_WatchDocFeedTask = 0;
static	UWORD	tskno_MAN_WatchDocCoverTask = 0;
void MAN_DocumentInTask( void )
{

	tskno_MAN_WatchDocumentSetTask = 0xFFFF;
	tskno_MAN_WatchDocumentOutTask = 0xFFFF;
	tskno_MAN_WatchDocFeedTask = 0xFFFF;
	tskno_MAN_WatchDocCoverTask = 0xFFFF;

	DocumentInTaskMessage.Item = FROM_DOCUMENT_IN;
	DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_SETUP;

	SCN_Init(); /* TBD */
	LampOn(); /** ランプ点灯 */
	/** 原稿待機位置への繰り込み */
	/** 原稿位置確認 */
	/** 送信モーター／Ｌａｍｐ設定 */
	/** スキャナー割り込み許可 */
	/** 24V　ON */
	/** スキャナー・カバーの開閉チェック */
	/** ＡＧＣ設定 */
	/** シェーディング・データ取り込み */
	/** 原稿の引き抜きチェック */
	/** Ｌａｍｐ　Ｅｒｒｏｒチェック */
	/** 繰り込み不良チェック */

	SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;	/** モーターをスルー・アップするように設定 */
	SCN_DocumentStatus = SCN_DOC_MOVE_TO_READY;	/** 原稿をＤＳ１からＤＳ２手前の待機位置まで移動中のステータスセット */

	if (DS1()&&!(DS2())&&!TXIL()) { /** 原稿繰り込みタスク起動時にＤＳ１のみＯＮなら原稿を繰り込む。　Sep.12,1994 */
		/*-------------------------------------------------------------------------*/
		/*  シェーディング・データ取り込み                                         */
		/*  固定シェーディングは機能＊９のサービス・ファンクションでデータ取り込み */
		/*-------------------------------------------------------------------------*/
		if (!CHK_ShadingFixAvailable()) { /** 固定シェーディング設定 */
			if (!CMN_ShadingExecute()) {	/** TBD */
				/** TBD Lamp Error */
				DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_LAMP_ERROR;
				snd_msg(mbxno.MAN_Task, &DocumentInTaskMessage);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk(0xffff);
			}
		}
		else {
			if (DIPP_CheckLamp() == NG) { /* ランプ点灯が異常 */
				DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_LAMP_ERROR;
				snd_msg(mbxno.MAN_Task, &DocumentInTaskMessage);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk(0xffff);
			}
		}

		cre_tsk(&tskno_MAN_WatchDocumentSetTask, TSK_MAN_WATCHDOCUMENTSETTASK, 0);
		cre_tsk(&tskno_MAN_WatchDocumentOutTask, TSK_MAN_WATCHDOCUMENTOUTTASK, 0);
		cre_tsk(&tskno_MAN_WatchDocFeedTask, TSK_MAN_WATCHDOCUMENTFEEDTASK, 0);
		cre_tsk(&tskno_MAN_WatchDocCoverTask, TSK_MAN_WATCHDOCUMENTCOVERTASK, 0);

		/* SCN_StopDS1OffDetect = 0;		@* 1996/08/14 By N.Sakamoto */

		SCN_StartFeed(SCN_DOC_IN); /** 原稿繰り込み開始 */

		rcv_msg(mbxno.MAN_DocumentInTask, &Msg);
		if (Msg->Message == MSG_DOCUMENT_SET_OK) { /** 原稿セット正常終了 */
			DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_SETUP;
			SCN_DocumentStatus = SCN_DOC_READY; /* Jun.29,1994 */
		}
		else if (Msg->Message == MSG_DOCUMENT_OUT) { /** 原稿引き抜き検出 */
			DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_NOTHING;
			/** 原稿ステータス更新 TBD */
		}
		else if (Msg->Message == MSG_DOCUMENT_FEED_ERROR) { /** 原稿引き抜き検出 */
			DocumentInTaskMessage.Message = MSG_DOCUMENT_IN_ERROR;
			/** 原稿ステータス更新 TBD */
		}

		if (tskno_MAN_WatchDocumentSetTask != 0xFFFF) {
			del_tsk(&tskno_MAN_WatchDocumentSetTask);
		}
		if (tskno_MAN_WatchDocumentOutTask != 0xFFFF) {
			del_tsk(&tskno_MAN_WatchDocumentOutTask);
		}
		if (tskno_MAN_WatchDocFeedTask != 0xFFFF) {
			del_tsk(&tskno_MAN_WatchDocFeedTask);
		}
		if (tskno_MAN_WatchDocCoverTask != 0xFFFF) {
			del_tsk(&tskno_MAN_WatchDocCoverTask);
		}
	}
	else {
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP; /** モーター停止中 */
		SCN_DocumentStatus = SCN_DOC_READY;	/** 原稿が待機位置にある */
	}

	wai_tsk(50);	/** Oct.12,1994 */

	snd_msg(mbxno.MAN_Task, &DocumentInTaskMessage);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);

}

#if (0)
#if (PRO_FBS == ENABLE)
/** Module Header For CIM-E ********************************************
	module		:	[ＦＢＳカバー開閉ＤＶＴ]
	function	:	[
		・電源ＯＮでメインからコールされるサブルーチン
	]
	return		:	[無し]
	common		:	[
	]
	condition	:	[]
	comment		:	[
		・プリンタのヒーターははずしておくこと（安全のため）
		・カウンターは保存されません。電源ＯＦＦの前にメモっておくこと
		・この関数をMAN_Task()のループに入る前、UpdateDisplay()の直前でコールすると
		  ”ぱたぱた君”が登場します。
	]
	machine		:	[SH7043]
	language	:	[SHC]
	keyword		:	[SCN]
	date		:	[1997/09/03]
	author		:	[野瀬敏弘]
************************************************************************/
void SCN_FBS_DVT(void)
{
	UBYTE disp_buf[9];
	UDWORD count = (UDWORD)0;;

	SCN_Init();

	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY; /* UpDateDisplay()を無効にする */
	SCN_VerticalMode = SCN_FBS_DVT_Speed;

	SCN_MirrorMoveStatus = MIRROR_MOVE_OK;
	SCN_WatchEndSensorStatus = WATCH_ES_DISABLE;
	SCN_MirrorCarriageStatus = MIRROR_MOVE_OPEN;			/* ＦＢＳカバーオープン */

#if (PRO_PANEL == ANK)
	ClearDisplayLow(); /* 下段表示のクリア */
#endif
#if (PRO_PANEL == KANJI)
	ClearString2();
#endif
	SCN_SetMotorDrive( SCN_FBS );		/* FBSモーターを使用する */
	SYS_ScannerExecMode = SCN_FBS;
	SCN_SetDS2_ON_Int( SCN_DISABLE );	/** ＤＳ２ＯＮ 割り込み禁止 */
	SCN_SetDS2_OFF_Int( SCN_DISABLE );	/** ＤＳ２ＯＦＦ 割り込み禁止 */
	SCN_SetLineInt(SCN_DISABLE); 		/** ライン割り込み禁止 */
	SCN_SetScanDMA(SCN_DISABLE); 				/** スキャン用ＤＭＡ禁止 */

	while (1) {
		SCN_MotorSpeedControl = SCN_MOTOR_SPEED_UP;
		SCN_DocExitTopSpeedCount = SCN_FBS_DVT_Count;	/* 巻き上げステップ数 */
		SCN_MotorPointer = &SCN_MotorTable[SCN_VerticalMode];
		SCN_MotorTablePoint = SCN_MotorTable->InitialSpeed;
		SCN_MirrorMotorPulseCount = 0;			/* ミラー用のパルスカウンタを０クリア */
		SCN_SetMotor(SCN_DISABLE); 					/** モーター・ディスエーブル */
		SCN_SetMotorSpeed(); 						/** モーターの速度設定(MTPC0,1)、速度変更間隔設定(MTP0) */
		SCN_LatchMotorSpeedAndInterval(); 			/** モーター速度変更間隔、速度初期ラッチ */
		SCN_SetMotorSpeedIntervalInt(SCN_ENABLE); 	/** モーター速度変更間隔割り込み許可 	INTMTEN-MTCNT */
		SCN_SetMotorPulse(SCN_DISABLE); 				/** モーター励磁ＯＮ MTCLR-MTCNT */
		if (SCN_MirrorCarriageStatus == MIRROR_MOVE_OPEN) {
			SCN_SetMotorClockwise(SCN_ENABLE); /* FBSカバークローズはモーター逆転 */
		}
		else {
			SCN_SetMotorClockwise(SCN_DISABLE); /* FBSカバーオープンはモーター正転 */
		}
		SCN_SetMotorPulse(SCN_ENABLE); 				/** モーター励磁ＯＮ MTCLR-MTCNT */
		SCN_SetMotor(SCN_ENABLE); 			/** モーター・イネーブル・セット MTEN-MTCNT */

		wai_evt(EVT_MIRROR_MOVE_END); /* モーター停止のイベントを待つ */

		CMN_UnsignedLongToASC_NULL(disp_buf, count, 8, '0');
#if (PRO_PANEL == ANK)
		DisplayStringHigh((UBYTE)1, disp_buf);
#endif
#if (PRO_PANEL == KANJI)
		DisplayString2(disp_buf);
#endif

		if (SCN_MirrorCarriageStatus == MIRROR_MOVE_OPEN) {
			/* FBSカバー開き終わった */
			count++;
			wai_tsk(50); /* 500ms wait */
			if (JamCover1Open()) { /* FBSカバー閉まってる */
				/* 糸が切れてる */
				break; /* テスト終了 */
			}
			SCN_MirrorCarriageStatus = MIRROR_MOVE_CLOSE;
		}
		else {
			/* FBSカバー閉じ終わった */
			if (!JamCover1Open()) { /* FBSカバー開いてる */
				/* カバーが引っかかってる */
				break; /* テスト終了 */
			}
			SCN_SetMotorPulse(SCN_DISABLE); /** モーター励磁ＯＦＦ */
			wai_tsk(300); /* 3sec Wait */
			SCN_MirrorCarriageStatus = MIRROR_MOVE_OPEN;
		}
	}
	SCN_SetMotorPulse(SCN_DISABLE); /** モーター励磁ＯＦＦ */
#if (PRO_PANEL == ANK)
	DisplayStringLow((UBYTE)0, D2W_InterruptDocScan); /* ”読取りが中断されました” */
#endif
#if (PRO_PANEL == KANJI)
	DisplayString2(D4W_WaitMinuteForPrint);	/* Wordingは適当 By O.Kimoto 1997/09/05 */
#endif
	wai_tsk(0xffff); /* メインタスクが寝る */
}
#endif
#endif /* 0 */
