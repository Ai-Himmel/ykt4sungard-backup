/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_msge.c
*	Author			: 橘正樹
*	Date			: 1997/02/07
*	RealTimeOS		: RISCモニタ
*	Description		: メインタスクMAN_Task()のメッセージ処理部
*	Module Name		: MAN_FromSensor()
*					: MAN_FromTimer()
*					: MAN_From10msTimer()
*					: MAN_FromMultiTimer()
*	Maintenance		:
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sysscan.h"
#include  "\src\atlanta\define\mntsw_c.h" /* DOC IN T.Nose */
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
/* CDC */
#include  "\src\atlanta\define\cdc_def.h"

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include  "\src\atlanta\sh7043\ext_v\extv_sem.h"
/*SCN*/
#include  "\src\atlanta\ext_v\scn_data.h"
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
 #if (PRO_COPY_FAX_MODE == ENABLE)
/*	#include  "\src\atlanta\opr\ank\define\opr_pro.h"*/
	void	ModifyCopyMagnifi(UBYTE);
 #endif
#endif

#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\define\prn_def.h"
#include  "\src\atlanta\prt\ph3\define\prn_stat.h"
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif

/*プロトタイプ宣言*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\scn_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\sh7043\define\io_pro.h"
void AckBuzzer( void );

#if (PRO_MULTI_LINE == ENABLE) /* Added by H.Kubo 1997/08/13 */
#include  "\src\atlanta\define\mlt_pro.h"
#endif /* (PRO_MULTI_LINE == ENABLE) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
void	DecrementAutoRcvCounter(void);
void	DecrementRxMailHoldTime(void);
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/06/13 H.Yoshikawa */
#include	"\src\atlanta\define\sysprint.h"
 #if defined(STOCKHM2)
#include 	"\src\atlanta\prt\lv_therm\ext_v\prt_data.h" /* Added by SMuratec L.Z.W 2003/11/20 */
 #else
#include 	"\src\atlanta\prt\iu_therm\ext_v\prt_data.h" /* Added by SMuratec L.Z.W 2003/11/20 */
 #endif
#endif

#if (PRO_DOC_IN == ENABLE)
/*-------------------------------------------------------------
** 原稿セットしっぱなしの場合にランプが消灯しません
** RICEの処理を復活させます。
** 1998/11/02 H.Yoshikawa
*/
UWORD LampOffTimer = 0;
#endif

#if (PRO_COPY_FAX_MODE == ENABLE) || defined(KEISATSU)	/* by K.Watanabe 1999/01/20 @ 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#endif

/*************************************************************************
	module		:[センサータスクからのメッセージ処理]
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
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromSensor(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	UWORD	sensor_item;
	UWORD	sensor_message;
	UWORD	sensor_sub_message1;
	UWORD	sensor_sub_message2;

	sensor_item = item;
	sensor_message = message;
	sensor_sub_message1 = sub_message1;
	sensor_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.MAN_SensorTask, &MainTaskMessage); /** 同期用メッセージ */
	switch (sensor_message) {
	case MSG_DS1_ON: /** DS1 ON */
		if ((!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN))
		 && CMN_CheckScanEnable()
		 && CMN_CheckFeederCommandEmpty()
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_IN) /* 7/11/1994 */
		 &&	!(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_OUT)) { /* 7/11/1994 */
/*
** ＤＳ１ ＯｆｆでＤＳ２ Ｏｎ状態のときはＤＳ２のセンサ割り込みにてフィードエラーをセットするようにして
** ＤＳ２に原稿噛んだままでの次の原稿を読み取り動作を禁止するようにした
** しかし、原稿セットするとここでフィードエラーが落とされるので、読み取り動作が許可されてしまう
** よってここでは落とさないようにします
** また、原稿枚数エラー後、新たな原稿をセットした場合のためここでクリアします
** 1999/03/10 by T.Soneoka
*/
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_PAGE_ERROR;
#else
			/*------------------------------------------------------------------------------*/
			/* 枚数指定の原稿蓄積時に枚数エラーが発生し、エラー表示中に新たな原稿をセットし */
			/* 同エラーが発生してもエラーアラームが鳴らない不具合い対策。By S.K Oct.12,1994 */
			/* エラー・アラーム鳴動時にエラーステータスがセットしていればアラームを鳴らさな */
			/* いような構造になっているため。												*/
			/*------------------------------------------------------------------------------*/
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FEED_ERROR; /* フィード・エラー・クリア */
#endif
#if (PRO_FBS ==ENABLE)
			/* 待機状態でADFに原稿がセットされたらミラーキャリッジの待機位置をADFとする */
			if (CHK_UNI_MirrorReadyModeVariable()) {
				if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)
				 && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_BUSY)) {
					SCN_MirrorReadyPosition = READY_POSITION_ADF;
					MirrorTaskInstruction = MIRROR_TASK_TO_ADF_READY;
					MirrorTaskRequest = TRUE;
				}
			}
#endif
#if (PRO_DOC_IN == ENABLE)
			/* ＡＤＦに原稿がセットされたら原稿を繰り込む */
			if (tskno_DocumentInTask == 0xffff) {
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_IN;
				/* SCN_StopDS1OffDetect = 1;		@* 1996/08/14 By N.Sakamoto */
				cre_tsk(&tskno_DocumentInTask, TSK_MAN_DOCUMENTINTASK, 0);
			}
			/*-------------------------------------------------------------
			** 原稿セットしっぱなしの場合にランプが消灯しません
			** RICEの処理を復活させます。
			** 1998/11/02 H.Yoshikawa
			** インクリメント方式からデクリメント方式にします(1998/11/06)
			*/
			LampOffTimer = 3;	/*ランプ・オフ用のタイマーをセット */
			/* LampOffTimer = 0; @** ランプ・オフ用のタイマーをセット */
#endif
		}
#if (PRO_DOC_IN == DISABLE)	/* POPLAR_L でも鳴らす 1997/11/27 By T.Yamaguchi */
/* #if (PRO_COPY_FAX_MODE == ENABLE) /@ コピー／ＦＡＸ切り替えあり */
		/* ＡＤＦに原稿がセットされたらＡＣＫブザーを鳴らす
		** T.Nose 1997/04/25
		*/
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) { /* ADFカバーが閉じている */
 #if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
			OPR_FeedinDispTime = 2;	/* 原稿繰り込みフラグ */
 #endif
			AckBuzzer();
		}
#endif
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {
			SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
			IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
		}
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)	/* 1997/07/03 by K.Watanabe */
		/* 倍率が変更されていない時のみ、倍率変更を行います */
		ModifyCopyMagnifi(OPR_ADF_DOC_IN);	/* コピー倍率変更処理 */
#endif
		break;
	case MSG_DS2_ON: /** DS2 ON */
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) &&
			(!SYS_MachineStatus[SYS_SCANNER_STATUS])) {
			/** 処理する内容無し */
		}

/*
** ＤＳ１ ＯｆｆでＤＳ２ Ｏｎ状態のときは原稿繰り込み不良をセットします
** 1999/03/10 by T.Soneoka
*/
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
		if ((!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY))
		&&  (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_FEED_IN | SYS_FEED_OUT)))
		&&  (!(SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS1_ON))) {
#if (0) /* カバーオープンした状態で、ＤＳ２をＯｎすると、フィードエラーになる不具合 1999/05/28 by T.Soneoka */
**			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
#else
			if (!TXIL()) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
			}
#endif
		}
#endif

		break;
	case MSG_DS1_OFF: /** DS1 OFF */
	case MSG_DS2_OFF: /** DS2 OFF */
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/10/02 by T.Soneoka */
#if (0)
** 		/* タイミングによっては、原稿排出中にもここを通ることがある。しかし、スキャナー送信をストップキーで
** 		** でキャンセルした場合などは、SYS_SCANNER_BUSYが落ちている。
** 		** よって、ここでは、SCANNER_BUSYにあわせて、FEED_IN/FEED_OUTも見るようにする。
** 		** by O.Kimoto 1999/01/14
** 		*/
** 		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
** 		&& (sensor_message == MSG_DS1_OFF)) {
** 			InitializeDocument();
** 		}
#else
		if ((!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY))
		&&  (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_FEED_IN | SYS_FEED_OUT)))
		&&  (sensor_message == MSG_DS1_OFF)) {
			InitializeDocument();
		}
#endif
#endif

		/* スキャナー送信中でなく、且つＤＳ１／ＤＳ２がOFFであれば初期化する。 */
#if (PRO_MULTI_LINE == DISABLE)	/* 1996/12/20 Y.Murata */
		if (!((SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FAXCOM) && ((SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) || (SYS_FaxComType == SYS_MANUAL_TX)))
#else
			if ((OPT_CHK_ScannerTxExecute() == 0xFF)
#endif
			&& (!(SYS_MachineStatus[SYS_SENSOR_STATUS]&SYS_SENSOR_DS1_ON))
			&& (!(SYS_MachineStatus[SYS_SENSOR_STATUS]&SYS_SENSOR_DS2_ON))
			&& (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR))
			&& (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR))) {

			/* スキャン中にサイズが変わるため削除  1997/04/24 s.takeuchi
			** CMN_ResetPrimaryDocumentSize(); @** 優先読み取りサイズの処理 *@
			*/
			if (!( (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
				&&(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_DOC_STORE|SYS_SCANNER_COPY)) )) {
				CMN_ResetMemoyFeederTx();	/* By H.Y 1994/08/23 */
				CMN_ResetStamp();			/* By H.Y 1994/08/23 */

#if (PRO_COPY_FAX_MODE == ENABLE) /* コピー／ＦＡＸ切り替えあり */
				if (CHK_ReadyModeCopy() == 0) { /* ファクスモードならば */
					CMN_ResetPrimaryMode(); /** 読み取りモードをリセット */
					CMN_ResetPrimaryContrast(); /** 読み取り濃度をリセット */
				}
#else
				CMN_ResetPrimaryMode(); /** 読み取りモードをリセット */
				CMN_ResetPrimaryContrast(); /** 読み取り濃度をリセット */
#endif

				CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
				CMN_ResetRedScan();
#endif

#if defined (KEISATSU)		/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
				ResetKeisatsuAttribute();
#endif
			}

			if (!CMN_CheckFeederCommandEmpty()) {
				CMN_ResetMemoyFeederTx();
				DeleteScannerCommand(); /** スキャナー・コマンド消去 */
				/* スキャナ送信の予約中に原稿を引き抜かれた時、スキャナ使用中をクリア 1994/06/01 Y.Murata */
				if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT))) {
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/30 */
					if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* スキャナー使用中をクリア */
					}
#else
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* スキャナー使用中をクリア */
#endif
				}
			}
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS]&SYS_SCANNER_BUSY) /** スキャナー使用中でなければ */
			 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN)) {	/** 繰り込み中でなければ T.Nose 1997/11/08 */
				LampOff(); /** ランプ消灯 */
			}

#if (0)	/* ＤＳ１、ＤＳ２がＯＦＦでＪＡＭエラーを解除しない（特許）By H.Yoshikawa 1996/08/14 */
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_FEED_ERROR+SYS_SCANNER_LAMP_ERROR);
#endif
		}
#if (PRO_COPY_FAX_MODE == ENABLE)
		/* 原稿セット時に、倍率変更がされている時のみ、初期値に戻します by K.Watanabe 1997/12/03 */
		ModifyCopyMagnifi(OPR_ADF_DOC_OUT);	/* コピー倍率変更処理 */
#endif
		break;
	case MSG_SCANNER_COVER_OPEN: /** スキャナー・カバー・オープン */
 #if (PRO_SEPERATE_INTER_LOCK == ENABLE) /* プリンター、スキャナーのインター・ロックが別々 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_FEED_ERROR+SYS_SCANNER_LAMP_ERROR);
		GearBackLashRequest = FALSE;

  #if defined(POPLAR_F) || (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)	/* 1999/12/01 Y.Murata *//* ベテランテストより By O.Kimoto 2002/10/24 */
		if (OPT_CHK_ScannerTxExecute() == 0xFF) {		/* スキャナー送信中でなく */
			if (!CMN_CheckFeederCommandEmpty()) {
				CMN_ResetMemoyFeederTx();
				DeleteScannerCommand(); /** スキャナー・コマンド消去 */
				/* スキャナ送信の予約中にスキャナカバーを開けられた時、スキャナ使用中をクリア */
				if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT))) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* スキャナー使用中をクリア */
				}
			}
		}
  #endif

  #if (PRO_FBS == ENABLE)
		if (CMN_CheckScanEnable()
		 &&	(SCN_MirrorCarriageStatus == MIRROR_READY)) {  /* スキャナー使用中でなければ又はメモリ・オバーであれば */
			LampOff(); /** ランプ消灯 */
		}
  #else
		if (CMN_CheckScanEnable()) {	 /* スキャナー使用中でなければ又はメモリ・オバーであれば */
			LampOff(); /** ランプ消灯 */
		}
  #endif
 #endif
 #if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/10/02 by T.Soneoka */
  #if (0) /* 寒冷地仕様のため変更します PreHeat 1999/02/09 by T.Soneoka */
	InitializeDocument();
  #else
   #if (PRO_PREHEAT == ENABLE)
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)) {
		InitializeDocument();
	}
   #else
	InitializeDocument();
   #endif
  #endif
 #endif
		break;
	case MSG_SCANNER_COVER_CLOSE: /** スキャナー・カバー・クローズ */
 #if (PRO_DOC_IN == ENABLE)
		GearBackLashRequest = TRUE;
 #endif
		break;
	case MSG_PRINTER_COVER_OPEN: /* プリンター・カバー・オープン */
		/* ここでは何もしない	*/
 #if (PRO_SEPERATE_INTER_LOCK == DISABLE)
  #if defined(SATSUKI2) /* SATSUKI2の場合カバーは一つなのでスキャナカバーをここで対応します。O.Oshima 2003/07/01 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_FEED_ERROR+SYS_SCANNER_LAMP_ERROR);
		GearBackLashRequest = FALSE;

    #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if (OPT_CHK_ScannerTxExecute() == 0xFF) {		/* スキャナー送信中でなく */
			if (!CMN_CheckFeederCommandEmpty()) {
				CMN_ResetMemoyFeederTx();
				DeleteScannerCommand(); /** スキャナー・コマンド消去 */
				/* スキャナ送信の予約中にスキャナカバーを開けられた時、スキャナ使用中をクリア */
				if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN))
				 && (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT))) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* スキャナー使用中をクリア */
				}
			}
		}
    #endif

		if (CMN_CheckScanEnable()) {	 /* スキャナー使用中でなければ又はメモリ・オバーであれば */
			LampOff(); /** ランプ消灯 */
		}
  #endif
 #endif

 #if !defined(HINOKI2) || !defined(HINOKI3)		/* HINOKI2,HINOKI3は下記処理しない。by Y.Kano 2005/01/25 */
 #if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/10/02 by T.Soneoka */
   #if (PRO_PREHEAT == ENABLE)
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)) {
		InitializeDocument();
	}
   #else
	InitializeDocument();
   #endif
 #endif
 #endif	/* End of !defined(HINOKI2) || !defined(HINOKI3) */

		break;
	case MSG_RESET_PRINTER_COVER_CLOSE: /* 新規追加ANZU By S.Kawasaki 1996/07/16 */
		/* プリンターリセットタスクの起動 By S.Kawasaki 1996/07/16	*/
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) { /* プリンター使用中でなければ By S.Kawasaki 1996/07/20 */
			if (tskno_PRN_PrinterResetTask == 0xFFFF) {
				SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_PRINTER_OPEN);
				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~(SYS_PRINTER_PAPER_JAM + SYS_PRINTER_EXIT_JAM + SYS_PRINTER_MISS_FEED_JAM + SYS_PRINTER_REG_JAM); /* ペーパージャム解除 */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_PAPER + SYS_PRINTER_NO_PAPER2);	/* 下段記録紙無し解除 */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= (SYS_PRINT_JAM_RECOVER);
				UpdateDisplay();
				cre_tsk(&tskno_PRN_PrinterResetTask, TSK_PRN_PRINTERRESETTASK, 0);
			}
		}
		break;
	case MSG_PRINTER_COVER_CLOSE: /* プリンター・カバー・クローズ */
  #if (PRO_SEPERATE_INTER_LOCK == ENABLE)
    #if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)		/* ＰＳ１、ＰＳ２、ＰＢ４閾値設定モード by Y.Kano 2004/10/06 */
		if (!OPR_PaperSensor_Adjust_Flg) {		/* 記録紙センサー設定中は処理しない。by Y.Kano 2004/10/06 */
    #endif										/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */
	    #if (PRO_PRINT_TYPE == LED)

	      #if (PRO_UPPER_COVER == ENABLE)
			/* ＰＯＰＬＡＲ＿Ｌ／Ｈではトップカバー開きでプリント不可とします。
			** By O.Kimoto 1998/03/10
			*/
			if(!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_PRINTER_OPEN | SYS_COVER_BOOK_OPEN))) {
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
						cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
					}
				}
			}
	      #else
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
				if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
					cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
				}
			}
	      #endif

	    #endif

	    #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) /* 1998/08/19 H.Yoshikawa */
			/*-----------------------------------------------------------------
			** プリンタカバークローズしたときに、SensorTaskでMachineStatusをOFFしていたので、
			** MainTaskで、イニシャルカット処理の前にプリントを起動してしまうことがあるので、
			** MachineStatusをOFFするのは、MainTaskで行うようにします。
			** 1998/12/04 H.Yoshikawa
			*/
			SYS_MachineStatus[SYS_COVER_STATUS] &= ~SYS_COVER_PRINTER_OPEN;	/* プリンターカバークローズ*//* 1998/12/04 H.Yoshikawa */
	      #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) /* 1998/08/19 H.Yoshikawa とりあえずSAKAKIだけ入れます。 HINOKI要検討 *//* ＨＩＮＯＫＩ追加 By O.Kimoto 1999/02/24 */
			/*-----------------------------------------------------------------
			**イニシャルカット起動後に、カバークローズされると、イニシャルカットしない時がある
			** イニシャルカット中にカバークローズされた場合には、再起動します。
			** 1998/11/25 H.Yoshikawa
			*/
			if((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
			&& (SYS_MachineStatus[SYS_MACHINE_STATUS]  & SYS_IMAGE_PRINT )
			&& (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL)) {
				if (tskno_PRN_ImagePrintTask != 0xffff) {
					del_tsk(&tskno_PRN_ImagePrintTask);
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
			}
	      #endif
	    		
			/*------------------------------------------------------------------------
			** SAKAKI用にMOMIJIから移植した
			** 1998/08/19 H.Yoshikawa
			*/
			if(!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* イメージ・プリント中セット */
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_INITIAL; /* プリンター初期化 */
	/* すいません、暫定的に下記のように変更させてください。
	** HINOKIの方が完成すれば元に戻しますので。 By O.Kimoto 1998/10/27 */
	      #if (PRO_PRINT_TYPE == THERMAL_TRANS)
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);	/* メモリ・プリント・タスク起動 */
	      #else
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_COPYPRINTTASK, 0); /* HINOKI 暫定 By O.Kimoto 1998/10/27 */
	      #endif
			}
	    #endif
	#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)
		}				/* 記録紙センサー設定中は処理しない by Y.Kano 2004/10/06 */
    #endif				/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */
  #endif
  #if (PRO_SEPERATE_INTER_LOCK == DISABLE)
    #if defined(SATSUKI2) /* SATSUKI2の場合カバーは一つなのでスキャナカバーをここで対応します。O.Oshima 2003/07/01 */
		SYS_MachineStatus[SYS_COVER_STATUS] &= ~(SYS_COVER_SCANNER_OPEN + SYS_COVER_PRINTER_OPEN);
    #endif
    #if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/07 */ /* ローカルに反映させる */
		if ((!CHK_WallHangSetting()) && (!OPR_PS2_Adjust_Flg)) { /** 壁掛け設定用 *//* PS2調整中は処理しない。by Y.Kano 2003/12/04 *//* Add by Y.kano 2003/10/07 */
    #endif	/* End of defined(SATSUKI2) */
      #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL) /* SATSUKI2用に上記から追加 O.Oshima 2003/07/01 */
		/*-----------------------------------------------------------------
		**イニシャルカット起動後に、カバークローズされると、イニシャルカットしない時がある
		** イニシャルカット中にカバークローズされた場合には、再起動します。
		** 1998/11/25 H.Yoshikawa
		*/
			if((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
			&& (SYS_MachineStatus[SYS_MACHINE_STATUS]  & SYS_IMAGE_PRINT )
			&& (SYS_DocumentPrintClass == SYS_PRINT_CLASS_INITIAL)) {
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* カッター動作中の開閉で次のスキャナコピーが固まる件 Added by SMuratec L.Z.W 2003/11/20 */
				if (tskno_PRN_PrintImageEvent != 0xffff) {
					del_tsk(&tskno_PRN_PrintImageEvent);
				}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
				if (tskno_PRN_ImagePrintTask != 0xffff) {
					del_tsk(&tskno_PRN_ImagePrintTask);
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
			}

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* カッター動作中の開閉で次のスキャナコピーが固まる件 Added by SMuratec L.Z.W 2003/11/20 */
			if((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
			&& (SYS_MachineStatus[SYS_MACHINE_STATUS]  & SYS_SCANNER_COPY)
			&& (SYS_DocumentPrintClass == SYS_PRINT_CLASS_REALTIMECOPY)) {
				if (tskno_PRN_PrintImageEvent != 0xffff) {
					del_tsk(&tskno_PRN_PrintImageEvent);
				}
				if (tskno_PRN_ImagePrintTask != 0xffff) {
					del_tsk(&tskno_PRN_ImagePrintTask);
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_SCANNER_COPY;
			}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */

      #endif
			if(!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {	 /* 94/8.3 by T.O スキャナ送信中もイニシャルカットしない */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* イメージ・プリント中セット */
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_INITIAL;				/* プリンター初期化 */

/* すいません、暫定的に下記のように変更させてください。
** HINOKIの方が完成すれば元に戻しますので。 By O.Kimoto 1998/10/27 */
      #if (PRO_PRINT_TYPE == THERMAL_TRANS)
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);	/* メモリ・プリント・タスク起動 */
      #else
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_COPYPRINTTASK, 0); /* HINOKI 暫定 By O.Kimoto 1998/10/27 */
      #endif
			}
    #if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/07 */
		}
    #endif	/* End of defined(SATSUKI2) */
  #endif
  #if (PRO_FBS == ENABLE)
		/* トップカバー開閉で「読取り準備中です」が解除されない対策
		** カバー閉で一旦以下のステータスを解除する
		** T.Nose 1997/10/16
		*/
    #if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/22 */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
			LampOff();
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY | SYS_PREHEAT);
    #else
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);
    #endif
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MIRROR_BUSY | SYS_SCANNER_MIRROR_INIT);

		/* ミラーキャリッジの初期化を行う */
		MirrorTaskInstruction = MIRROR_TASK_INITIALIZE;
		MirrorTaskRequest = TRUE;
  #else
    #if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/22 */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
			LampOff();
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY | SYS_PREHEAT);
		}
		/* SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY | SYS_PREHEAT); */
    #endif
  #endif

  #if (PRO_SEPERATE_24V == DISABLE)
		/* 原稿蓄積動作中のプリンターカバー 開→閉 ならばジャムリカバーオペレーションを行う */
		if (DocumentResetOperation == TRUE) {
    #if (PRO_FBS == ENABLE)
			/* ジャムリカバーオペレーション指示 */
			if (SYS_ScannerExecMode == SCN_FBS) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FBS_RECOVER_OPR;
			}
			else {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_JAM_RECOVER_OPR;
			}
    #else
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_JAM_RECOVER_OPR;
    #endif
			DocumentResetOperation = FALSE; /* ステータスをセットしたら初期化しておく */
			snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
			rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
		}
  #endif
		break;
	case MSG_JAM_COVER_OPEN: /* ジャム・カバー・オープン */
		break;
	case MSG_JAM_COVER_CLOSE: /* ジャム・カバー・クローズ */
#if (PRO_PRINT_TYPE == LED)
  #if (PRO_UPPER_COVER == ENABLE)	/* By M.Tachibana 1998/04/02 */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_JAM_OPEN | SYS_COVER_2JAM_OPEN | SYS_COVER_3JAM_OPEN
													| SYS_COVER_PRINTER_OPEN | SYS_COVER_BOOK_OPEN))) {	/* Add By M.Tachibana 1998/04/02 */
			if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_JAM)
			 || (SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_PSS_ON | SYS_SENSOR_PDS_ON))
			 || (PrinterStatus[PRN_STATUS_7] & PRN_S7_TONER_DRUM_CHECK)) {
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
						cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
					}
				}
			}
		}
  #else
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_JAM_OPEN | SYS_COVER_2JAM_OPEN | SYS_COVER_3JAM_OPEN
													| SYS_COVER_PRINTER_OPEN))) {	/* Add By M.Tachibana 1998/04/02 */
			if ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_ERROR_JAM)
			 || (SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_PSS_ON | SYS_SENSOR_PDS_ON))
			 || (PrinterStatus[PRN_STATUS_7] & PRN_S7_TONER_DRUM_CHECK)) {
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
						cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
					}
				}
			}
		}
  #endif
#endif
		break;
#if (PRO_DIALIN == ENABLE)
	case MSG_DIAL_IN_ON:	/* ダイヤルイン・スイッチＯＮ */
		SYB_DialInNoNumberSignal = 1;
		if (CMN_CheckInputDialInNumber()) {	/** ダイヤルイン番号が登録されている時 */
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_NO_DIAL_IN_NUMBER);
		}
		else {								/** ダイヤルイン番号が登録されていない時 */
			SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_NO_DIAL_IN_NUMBER;
		}
		break;
	case MSG_DIAL_IN_OFF:	/* ダイヤルイン・スイッチＯＦＦ */
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_NO_DIAL_IN_NUMBER);
		break;
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
	case MSG_SCRAMBLE_ON: /* スクランブルSW ON */
		break;
	case MSG_SCRAMBLE_OFF: /* スクランブルSW OFF */
		break;
	case MSG_S1_ERROR_ON: /* S1エラーON */
		break;
	case MSG_S1_ERROR_OFF: /* S1エラーOFF */
		break;
#endif

#if (PRO_PRINT_TYPE == LED)
	case MSG_HPES_ON:
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_JAM_OPEN)
		 && !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & (SYS_PRINTER_ERROR_JAM|SYS_PRINTER_SIZE_ERROR))) {	/* ジャムの条件追加 By M.Tachibanaa 1998/01/15 */
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
  #if (PRO_COPY_FAX_MODE == ENABLE)
				if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
					if (tskno_PRN_ManualDocInTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						cre_tsk(&tskno_PRN_ManualDocInTask, TSK_PRN_MANUALDOCUMENTINTASK, 0);
					}
				}
  #endif
  #if (PRO_COPY_FAX_MODE == DISABLE)
   #if (PRO_MANUAL_CASSETTE == ENABLE)				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
				if (tskno_PRN_ManualDocInTask == 0xFFFF) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
					cre_tsk(&tskno_PRN_ManualDocInTask, TSK_PRN_MANUALDOCUMENTINTASK, 0);
				}
   #endif
  #endif
			}
			else {
				if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_MANUAL_PAPER)) {
					/* ブザー鳴動 */
				}
			}
		}
		break;
	case MSG_HPES_OFF:
#if (0)
//		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY)) {
//			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_MANUAL_COPY_DOC_OPR;
//		}
#endif
		break;
#endif
	case MSG_PAPER_NOT_EXIST:
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
		break;
	case MSG_PAPER_EXIST:
		SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~SYS_PRINTER_NO_PAPER;
		break;
	case MSG_FBS_PRESS_BOAD_OPEN:	/* ADF許可センサ(APS)がOFF (FBS押圧板が開) */
#if (PRO_FBS == ENABLE)
		/* 待機状態でFBS押圧板が開けられたらミラーキャリッジ待機位置をFBSにする */
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
		 && !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)) {/* プリンターカバー閉じている */
			if (CHK_UNI_MirrorReadyModeVariable()) {
				SCN_MirrorReadyPosition = READY_POSITION_FBS;
				MirrorTaskInstruction = MIRROR_TASK_TO_FBS_READY;
				MirrorTaskRequest = TRUE;
			}
		}
#endif
		break;
	case MSG_FBS_PRESS_BOAD_CLOSE:	/* ADF許可センサ(APS)がON (FBS押圧板が閉) */
#if (PRO_UPPER_COVER == ENABLE)
		/* ＰＯＰＬＡＲ＿Ｌ／Ｈではトップカバー開きでプリント不可とします。
		** By O.Kimoto 1998/03/10
		*/
		if(!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_PRINTER_OPEN | SYS_COVER_BOOK_OPEN))) {
			if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
				if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
					cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
				}
			}
		}
#endif
		/* 何もしません */
		break;
	case MSG_CASSETTE_OPEN:
		break;
	case MSG_CASSETTE_CLOSE:
#if (PRO_COPY_FAX_MODE == ENABLE)	/* By M.Tachibana 1997/07/05 */
		/* 固定倍率が選択されていて、ADFに原稿がｾｯﾄされている時に、ｶｾｯﾄの記録紙が交換されたら倍率変更を行います */
		ModifyCopyMagnifi(OPR_CASSETTE_CLOSE);	/* コピー倍率変更処理 */
#endif
#if (PRO_PRINT_TYPE == LED)
 #if (PRO_UPPER_COVER == ENABLE)	/* By M.Tachibana 1998/04/02 */
		if (PrinterStatus[PRN_STATUS_7] & PRN_S7_TONER_DRUM_CHECK) {
			if(!(SYS_MachineStatus[SYS_COVER_STATUS] & (SYS_COVER_PRINTER_OPEN | SYS_COVER_BOOK_OPEN))) {	/* Add By M.Tachibana 1998/04/02 */
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
						cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
					}
				}
			}
		}
 #else
		if (PrinterStatus[PRN_STATUS_7] & PRN_S7_TONER_DRUM_CHECK) {
			if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)) {	/* Add By M.Tachibana 1998/04/02 */
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
					if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
						SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
						cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
					}
				}
			}
		}
 #endif
#endif
		break;
	default:
		break;
	}
}


/*************************************************************************
	module		:[タイマー・タスクからのメッセージ処理]
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
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromTimer(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	timer_item;
	UWORD	timer_message;
	UWORD	timer_sub_message1;
	UWORD	timer_sub_message2;

	timer_item = item;
	timer_message = message;
	timer_sub_message1 = sub_message1;
	timer_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.MAN_TimerTask, &MainTaskMessage);
	switch (timer_message) { /* タイマーからのメッセージ解析 */
	case MSG_TIME_UP_1MIN: /* １分経過メッセージ */
		/*----------------------------------------------------------------------*/
		/* ＤＲＡＭ上の原稿が０ページで空きブロック数が正常な値に戻っているかを */
		/* 確認する処理をここにいれましょか？									*/
		/* （注意）																*/
		/*	確認作業に入る前に画像メモリをアクセスするようなタスクが走ってしない*/
		/*	のを確認し、確認終了まではそれらの実行を禁止する必要有り			*/
		/*----------------------------------------------------------------------*/
		DecrementRedialTime(); /* 再ダイアル発呼のコマンドの時間減算 */

#if (PRO_DOC_IN == ENABLE)
/* #if (0) *//* POPLAR_B はFBSカバー閉でランプ点灯しないので削除 T.Nose */
		/*-----------------------------------------------------------------
		** 原稿セットしっぱなしの場合にランプが消灯しません
		** RICEの処理を復活させます。
		** 1998/11/02 H.Yoshikawa
		** インクリメント方式からデクリメント方式にします(1998/11/06)
		*/
		if (LampOffTimer) {
			LampOffTimer --;
			if ((LampOffTimer == 0) && CMN_CheckScanEnable()) { /* ランプ点灯時間が３分以上経過していてスキャナーが未使用であれば */
				LampOff(); /* ランプの消灯 */
			}
		}
#if (0)	/* インクリメント方式からデクリメント方式にします 1998/11/06 */
//		LampOffTimer++; /* ランプ点灯時間を１分加算 */
//		if ((LampOffTimer > 2) && CMN_CheckScanEnable()) { /* ランプ点灯時間が３分以上経過していてスキャナーが未使用であれば */
//			LampOff(); /* ランプの消灯 */
//		}
#endif
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */

		/*************************************************
		 **	インターネットＦＡＸ　自動受信タイマー減算
		 *************************************************/
		DecrementAutoRcvCounter();

		/****************************************************
		 **	インターネットＦＡＸ　親展受信原稿の保持期間減算
		 ****************************************************/
		DecrementRxMailHoldTime();

#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
		break;
	case MSG_TIME_UP_VAR:
		HungUpCheck = 0;
		break;
	case MSG_DATE_CHANGED:
		break;
#if (PRO_PRINT_TYPE == LASER)
	/*********************************************************************/
	/* 1sec.タイマの中でのプリンタ・ステータスの監視からのメッセージ処理 */
	/* エラー内容は														 */
	/*		UWORD PRN_ErrorDetails							from NOBUKO	 */
	/*********************************************************************/
	/*		オペレータ・コール											 */
	/*			PRN_ERROR_COVER_OPEN		0x0001	カバー・オープン	 */
	/*			PRN_ERROR_NO_PAPER			0x0002	指定カセット紙なし	 */
	/*			PRN_ERROR_CASSETTE_OPEN		0x0004	カセット・オープン	 */
	/*			PRN_ERROR_NO_EP				0x0008	EPカートリッジなし	 */
	/*			PRN_ERROR_EXIT_JAM			0x0010	EXITジャム			 */
	/*			PRN_ERROR_MISS_FEED_JAM		0x0020	ミスフィード・ジャム */
	/*			PRN_ERROR_REG_JAM			0x0040	レジスト・ジャム	 */
	/*********************************************************************/
	/*		サービス・コール											 */
	/*			PRN_ERROR_MEMORY_ABNORMAL	0x0100	メモリ異常			 */
	/*			PRN_ERROR_FAN_ABNORMAL		0x0200	冷却ファン異常		 */
	/*			PRN_ERROR_MOTOR_ABNORMAL	0x0400	モータ異常			 */
	/*			PRN_ERROR_FUSER_ABNORMAL	0x0800	フューザ異常		 */
	/*********************************************************************/
	case MSG_PRINTER_ERROR:
		break;
	case MSG_PRINTER_ERROR_CLEAR:
		break;
#endif
	case MSG_SUMMER_TIME_EXECUTE: /* サマータイム実行->表示更新 1996/01/23 Eguchi */
		/* カレンダー表示を更新するのみなので特に処理はない */
		break;
#if (PRO_MULTI_LINE == ENABLE)	/* マルチ回線表示 1997/02/04 Y.Matsukuma */
	case MSG_MULTI_DISPLAY_TIME:
		/* マルチ表示を更新するのみなので特に処理はない */
		break;
#endif
#if (PRO_PRINT_TYPE == LED)
	case MSG_PRINTER_WAKEUP:
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) {
			if (tskno_PRN_PrinterWarmUpTask == 0xFFFF) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
				SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINTER_WAKEUP;
				cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
			}
		}
		break;
#endif

#if (PRO_PREHEAT == ENABLE)
	/*
	* 寒冷地 PreHeat
	*/
	case MSG_PREHEAT_START_TIME:
		if (CMN_CheckScanEnable()
		&& (!SYB_ScannerTransportMode)
		&& !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
		&& !(SYS_MachineStatus[SYS_SCANNER_STATUS] & (SYS_SCANNER_LAMP_ERROR
														| SYS_SCANNER_MIRROR_ERROR
														| SYS_SCANNER_FBS_RECOVER_OPR
														| SYS_SCANNER_GEAR_BACKLASH
														| SYS_SCANNER_MEMORY_OVER_OPR
														| SYS_SCANNER_JAM_RECOVER_OPR
														| SYS_SCANNER_NEXT_SCAN_OPR
														| SYS_SCANNER_NEXT_SCAN_START_OPR
														| SYS_SCANNER_NEXT_SCAN_START
														| SYS_SCANNER_MIRROR_BUSY))) {	/* スキャナ使用可 */

			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= (SYS_PREHEAT | SYS_SCANNER_BUSY);
#if (PRO_FBS == ENABLE)
			/* 「しばらくお待ちください」表示のため */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= (SYS_SCANNER_MIRROR_INIT|SYS_SCANNER_MIRROR_BUSY);
#endif

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
			PC_24V_On();
#endif

#if (PRO_ECO_MODE == ENABLE)		/* 2002/09/20 By M.Maeda */
 #if (1) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
			MAN_ChangeEcoMode(0);
 #else
//			MAN_ChangeEcoMode(FALSE);
 #endif
#endif
			LampOn();
		}
		break;
	case MSG_PREHEAT_END_TIME:
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {	/* プリヒート中 */
			LampOff();
			/* Statusをクリアする */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PREHEAT | SYS_SCANNER_BUSY);
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MIRROR_INIT|SYS_SCANNER_MIRROR_BUSY);
		}
		break;
#endif /* PRO_PREHEAT == ENABLE */
#if 0 /* (PRO_ENERGY_SAVE == ENABLE) 見送る */		/* 頻繁に24VOnOffが起こり、リレーの寿命が持たない対策 2002/11/29 T.Takagi */
	case MSG_24V_OFF:
		PC_24V_Off();
		break;
#endif
	default:
		break;
	}
}


/*************************************************************************
	module		:[表示用タイマータスクからのメッセージ処理]
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
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_From10msTimer(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	timer_item;
	UWORD	timer_message;
	UWORD	timer_sub_message1;
	UWORD	timer_sub_message2;

	timer_item = item;
	timer_message = message;
	timer_sub_message1 = sub_message1;
	timer_sub_message2 = sub_message2;

	switch (timer_message) {
	case MSG_FAXCOM_COMPLETE:
		if (tskno_faxcom_complete != 0xffff) {
			del_tsk(&tskno_faxcom_complete);
		}
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
		/* 待機モード自動切替処理 */
		if (MAN_AutoReadyModeChangeEnable() == TRUE) {
			MAN_AutoChangeReadyMode();
		}
#endif
		break;
	case MSG_STORE_COMPLETE:
		if (tskno_store_complete != 0xffff) {
			del_tsk(&tskno_store_complete);
		}
		break;
	case MSG_PRINT_COMPLETE:
		if (tskno_print_complete != 0xffff) {
			del_tsk(&tskno_print_complete);
		}
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
		/* 待機モード自動切替処理 */
		if (MAN_AutoReadyModeChangeEnable() == TRUE) {
			MAN_AutoChangeReadyMode();
		}
#endif
		break;
#if (PRO_CLASS1 == ENABLE)
	case MSG_PC_FAX_COMPLETE:	/* 1996/09/13 Eguchi */
		if (tskno_pc_fax_complete != 0xffff) {
			del_tsk(&tskno_pc_fax_complete);
		}
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	case MSG_INF_COMPLETE:
		if (tskno_inf_complete != 0xffff) {
			del_tsk(&tskno_inf_complete);
		}
		break;
	case MSG_INF_TERMINATE:
		if (tskno_inf_terminate != 0xffff) {
			del_tsk(&tskno_inf_terminate);
		}
		break;
	case MSG_INF_NO_NEW_MAIL:
		if (tskno_inf_nomail != 0xffff) {
			del_tsk(&tskno_inf_nomail);
		}
		break;
#endif
	default:
		break;
	}
}


/*************************************************************************
	module		:[マルチタイマータスクからのメッセージ処理]
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
	date		:[1996/01/23]
	author		:[野瀬敏弘]
*************************************************************************/
void MAN_FromMultiTimer(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	timer_item;
	UWORD	timer_message;
	UWORD	timer_sub_message1;
	UWORD	timer_sub_message2;

	timer_item = item;
	timer_message = message;
	timer_sub_message1 = sub_message1;
	timer_sub_message2 = sub_message2;

	switch(timer_message){
	case MSG_STORE_COMPLETE:
		/* 特に何もしない T.Nose */
		break;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
	case MSG_SCAN_CONT_TIMEUP:
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			SYS_NextBookDocument = FALSE;	/* 次原稿ＯＰ指示変数を初期化 */
			IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
#endif
			switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
			case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
				/* メモリ送信コマンド・ファイルの登録 */
				MemoryTxDocStoreOK(SYS_COMMAND_TRX);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
				break;
#if (PRO_BATCH_TX == ENABLE)
			case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
			case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
			case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
			case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
			case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
				/* 一括送信コマンド・ファイルの登録 */
				MemoryTxDocStoreOK(SYS_BATCH_TX);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
				break;
#endif
			case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
				/* SYS_SpecialMode &= ~POLLING_STORE; 未定 T.Nose 1997/05/08 */
				SYB_PollingDocumentStatus = 1; /** ポーリング原稿有りセット */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)
** 				SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
				SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
#endif

				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
				break;
			case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
				/* SYS_SpecialMode &= ~POLLING_STORE; 未定 T.Nose 1997/05/08 */
				SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
				break;
#if (0) /* コピーは次原稿ＯＰは適用しない T.Nose */
			case SYS_MEM_MULTI_COPY_FILE: /* マルチ・コピーファイル */
				/* 1ページ以上蓄積されていれば */
				if (page = MEM_CountTotalPage(SYS_DocumentStoreItem, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER) ) {
					if (page != MEM_NO_INDEX) {
						MultiCopyDocStoreOK(); /* マルチ・コピー・ファイルの登録 TBD */
						/* 原稿蓄積完了表示起動 */
						if (timer_store_fax_complete == 0xff) {
							CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
						}
					}
					else {
						MultiCopyDocStoreNG();
						MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
					}
				}
				else {
					MultiCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
				}
				break;
			case SYS_MEM_MANUAL_COPY_FILE: /* 手差し・コピーファイル */
				if (page = MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) ) { /* 1ページ以上蓄積されていれば */
					if (page != MEM_NO_INDEX) {
						ManualCopyDocStoreOK();
						/* 原稿蓄積完了表示起動 */
						if (timer_store_fax_complete == 0xff) {
							CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
						}
					}
					else {
						ManualCopyDocStoreNG();
						MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
					}
				}
				else {
					ManualCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
				}
				break;
#endif /* コピーは次原稿ＯＰは適用しない T.Nose */
#if (PRO_F_CODE == ENABLE)
			case SYS_MEM_SUB_BULLETIN_FILE:	/** Ｆコード */
				/* Ｆコード原稿の登録 */
				FcodeDocStoreOK(SYS_DocumentStoreBoxNumber);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			break;
#endif
			default:
				break;
			}
		}

		switch (SYS_DocumentStoreItem) {	/** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE:			/** メモリ送信ファイル */
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5:	/** 一括送信原稿 */
#endif
		case SYS_MEM_POLLING_FILE:		/** ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング・ファイル */
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:	/** Ｆコード */
#endif
			CMN_ResetMemoyFeederTx();
			CMN_ResetStamp();
			CMN_ResetPrimaryMode();
			CMN_ResetPrimaryContrast();
			CMN_ResetConfirmationReport();
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
			CMN_ResetRedScan();
#endif
			break;
		case SYS_MEM_MULTI_COPY_FILE:	/** マルチ・コピー・ファイル */
		case SYS_MEM_MANUAL_COPY_FILE:	/** 手差し・コピー・ファイル */
		default:
			break;
		}
		break;
#endif /* 0 */
	default:
		break;
	}
}
