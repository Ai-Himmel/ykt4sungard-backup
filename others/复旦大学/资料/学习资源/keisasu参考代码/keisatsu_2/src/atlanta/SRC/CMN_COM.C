/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_COM.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_com.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sysbatch.h"
#include "\src\atlanta\define\sys_stat.h"
#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#if (PRO_MODEM == R288F)
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#endif

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\scn_data.h"

#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\sh7043\define\io_pro.h"
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
#include "\src\atlanta\ext_v\ini_tbl.h"
#endif

#if defined(STOCKHM2)	/* QAT:会話予約変更対応 by SMuratec 夏 2004/11/03 */
#include "\src\atlanta\define\uni_pro.h"
#endif

/*************************************************************************
	module		:[マルチコピーコマンドの空き領域の確保]
	function	:[
		1.
	]
	return		:[]
	common		:[
		1.SYB_MultiCopyFile[]
		2.SYB_MultiCopyPoint
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_GetMulticopyArea(void)
{
	UBYTE	i;
	struct SYS_MultiCopyData_t	*mcopy_ptr;

	for (i = 0; i < SYS_MULTI_COPY_MAX; i++) {
		mcopy_ptr = &SYB_MultiCopyFile[SYB_MultiCopyPoint];
		if (mcopy_ptr->Status == SYS_MCOPY_EMPTY) {
			mcopy_ptr->Status = SYS_MCOPY_STORE;
			break;
		}
		else {
			SYB_MultiCopyPoint++;
			if (SYB_MultiCopyPoint >= SYS_MULTI_COPY_MAX) {
				SYB_MultiCopyPoint = 0;
			}
		}
	}
	return(i);
}

/*************************************************************************
	module		:[読取り原稿サイズの確保]
	function	:[
		1.
	]
	return		:[0:SYS_DOCUMENT_A4_SIZE
				  1:SYS_DOCUMENT_B4_SIZE
				  2:SYS_DOCUMENT_A3_SIZE
	]
	common		:[]
	condition	:[]
	comment		:[戻り値の確認は\src\atlanta\define\sysdoc.hで定義されている値を使用すること
				 ANZUの最大読みとり幅はB4なのでH8用のパスを使用 1995/09/12 Eguchi
				 ポプラはＡ３読み取りがあるので変更	 1996/11/28	 By T.Yamaguchi ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_GetDocumentScanSize(void)
{
#if (PRO_SCAN_WIDTH == A3WIDTH)	/* A3の機種はこのパスが必要 */
	if (DA3()) {	/** A document is A3 size **/
		switch(CHK_ScanningWidth()) {
		case SYS_DOCUMENT_A3_SIZE:
			return(SYS_DOCUMENT_A3_SIZE);
		case SYS_DOCUMENT_B4_SIZE:
			return(SYS_DOCUMENT_B4_SIZE);
		case SYS_DOCUMENT_A4_SIZE:
			return(SYS_DOCUMENT_A4_SIZE);
		}
	}
#endif
	if (DB4()) {	/** A document is B4 size **/
		switch(CHK_ScanningWidth()) {
		case SYS_DOCUMENT_A3_SIZE:
		case SYS_DOCUMENT_B4_SIZE:
			return(SYS_DOCUMENT_B4_SIZE);
		case SYS_DOCUMENT_A4_SIZE:
			return(SYS_DOCUMENT_A4_SIZE);
		}
	}
	else {				/** A document is A4 size **/
		return(SYS_DOCUMENT_A4_SIZE);
	}
}


#if (PRO_FBS == ENABLE)
/*************************************************************************
	module		:[FBS原稿の読取り主走査サイズの取得]
	function	:[
		指定済みの定型原稿サイズから、読取り主走査サイズを取得する
	]
	return		:[
		0:SYS_DOCUMENT_A4_SIZE
		1:SYS_DOCUMENT_B4_SIZE
		2:SYS_DOCUMENT_A3_SIZE
		(sysdoc.h参照)
	]
	common		:[]
	condition	:[]
	comment		:[
		ICHOUのADF/FBS区別のため
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/12/09]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CMN_GetFBS_DocumentScanSize(void)
{
	UBYTE	size;

	switch (SCN_RegularDocumentSize) {
	case	SYS_REGULAR_SIZE_A3:		/* A3縦 */
	case	SYS_REGULAR_SIZE_A4R:		/* A4横 */
	case	SYS_REGULAR_SIZE_LETTER_R:	/* レター横 */
		size = SYS_DOCUMENT_A3_SIZE;
		break;
	case	SYS_REGULAR_SIZE_B4:		/* B4縦 */
	case	SYS_REGULAR_SIZE_B5R:		/* B5横 */
		size = SYS_DOCUMENT_B4_SIZE;
		break;
	case	SYS_REGULAR_SIZE_A4:		/* A4縦 */
	case	SYS_REGULAR_SIZE_A5R:		/* A5横 */
	case	SYS_REGULAR_SIZE_LETTER:	/* レター縦 */
	case	SYS_REGULAR_SIZE_LEGAL:		/* リーガル */
	case	SYS_REGULAR_SIZE_F4:		/* F4縦 */  /* POPLAR_B AUS bythonda1998/05/12 */
	default:
		size = SYS_DOCUMENT_A4_SIZE;
		break;
	}

	return (size);
}
#endif	/* (PRO_FBS == ENABLE) */


/*************************************************************************
	module		:[通信予約番号の空き領域の確保]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_GetCommandArea(void)
{
	UBYTE	i;
	struct SYS_CommandData_t	*com_ptr;

	CMN_DisableInterrupt();
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		com_ptr = &SYB_CommandFile[i];
		if (com_ptr->Status == SYS_CMD_EMPTY) {
			com_ptr->Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[i] = SYS_CMD_SETTING;
#endif
			break;
		}
	}
	CMN_EnableInterrupt();
	return(i);
}

/*************************************************************************
	module		:[通信予約番号に対する発信スケジューラの消去]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ClearCommandArea(UBYTE com_type,	/* 通信予約種別 */
							 UBYTE com_no)		/* 通信予約番号 */
{
	UBYTE	i;
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
	/* 毎日ポーリングＲＯＭ
	** 一度予約したポーリングコマンドは毎日指定時刻実行するものとする
	** 消去されるのは通信予約で削除するか、バックアップが消えたときのみという特殊仕様
	** by O.Kimoto 2002/06/17 */
	UBYTE	old_status;
	UBYTE	fcode_polling_rx;

	old_status = 0;
	fcode_polling_rx = 0;

#endif

	if (com_type == SYS_COMMAND_TRX) {

		/*------------------------------------------------*/
		/* スキャナ送信であればスキャナ使用中をクリアする */
		/*							  1994/10/19 Y.Murata */
		/*------------------------------------------------*/
		switch (SYB_CommandFile[com_no].Option.Item) {	/** 交信種別判断 */
		case SYS_SCANNER_TX:
		case SYS_DELAYED_SCANNER_TX:
		case SYS_SCANNER_SECURE_TX:
		case SYS_SCANNER_RELAY_BROADCAST:	/** スキャナ送信であれば */
#if (PRO_F_CODE == ENABLE)
		case SYS_SCANNER_SUB_ADDRESS_TX:	/* スキャナＦコード送信 */
#endif

			/* 条件を追加する */
			/* 他の動作がスキャナを使用していなければスキャナ使用中をクリア 1996/08/05 Eguchi EGU  */
			/* 原稿蓄積中でなく、かつ
			 * スキャナーコピー中でなく、かつ
			 * 原稿排出中でなく、かつ
			 * スタンプテスト中でなく、かつ
			 * スキャナー送信実行中でなく,かつ
			 * 手動送信実行中でない
			 * -> スキャナ使用中クリア
			 */
			/* クラス１がはいってきたときは条件を追加する必要があるかもしれないので注意してください */
			if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) {
				if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)
				&&	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY)
				&&	!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)
#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/30 */
				&&	!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)
#endif
				&&	!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)&&(SYS_FaxComType == SYS_COMMAND_EXECUTE && SYS_FaxComTxType == SYS_SCANNER_TRANSMIT))
/*				&&	!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)&&(SYS_FaxComType == SYS_COMMAND_EXECUTE && SYS_FaxComTxType == SYS_SCANNER_TX))	*/
				&&	!((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)&&(SYS_FaxComType == SYS_MANUAL_TX))) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);	/** スキャナ使用中クリア */
				}
			}
			break;
		default:
			break;
		}
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/* #if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_DAILY_POLLING == ENABLE)
	/* 毎日ポーリングＲＯＭ
	** 一度予約したポーリングコマンドは毎日指定時刻実行するものとする
	** 消去されるのは通信予約で削除するか、バックアップが消えたときのみという特殊仕様
	** by O.Kimoto 2002/06/17 */
		old_status = SYB_CommandFile[com_no].Status;
 #endif
#endif


		SYB_CommandFile[com_no].Status = SYS_CMD_EMPTY;
		
		
#if (PRO_F_CODE == ENABLE)	/* 1997/08/08  By T.Yamaguchi */
		if (CMN_CheckFcodeCommand(SYB_CommandFile[com_no].Option.Item) == TRUE) {	/** 交信種別判断 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/* #if (PRO_KEYPANEL == PANEL_HINOKI)*/
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
			fcode_polling_rx = 0;

  #if (PRO_DAILY_POLLING == ENABLE)
			/* 毎日ポーリングＲＯＭ
			** 一度予約したポーリングコマンドは毎日指定時刻実行するものとする
			** 消去されるのは通信予約で削除するか、バックアップが消えたときのみという特殊仕様
			** by O.Kimoto 2002/06/17 */
		 	if (ROM_SW_SpecialDailyPolling == 1) {
				if ((old_status != SYS_CMD_ERASED) && (old_status != SYS_CMD_POWER_OFF)) {
					if (SYB_CommandFile[com_no].Option.Item == SYS_SELECT_POLLING_RX) {	/** 交信種別判断 */
						fcode_polling_rx = 1;
					}
				}
			}
  #endif
  			if (fcode_polling_rx == 0) {
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[com_no].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[com_no].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
 #else
			SYB_FcodeNumberCDataBuffer[SYB_CommandFile[com_no].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
			SYB_FcodeNumberCDataBuffer[SYB_CommandFile[com_no].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
 #endif
		}
#endif

#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[com_no] = SYS_CMD_EMPTY;
#endif

		/*
		** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
		** 原稿無し：MEM_NO_INDEX(0xFFFF)
		** 原稿有り：０以外のページ数
		** By S.Kawasaki 1996/08/10
		*/
		if (MEM_CountTotalPage(SYS_MEM_TX_FILE, (UWORD)com_no, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** 指定原稿があれば */
			MEM_ClearDoc(SYS_MEM_TX_FILE, com_no, MEM_IGNORE_BOX_NUMBER);
		}
	}
#if (PRO_BATCH_TX == ENABLE)
	else {
		SYB_BatchTxFile[com_no].Status = SYS_CMD_EMPTY;
		for (i = 0; i < SYS_BATCH_INDEX_MAX; i ++) {
			if (SYB_BatchTxFile[com_no].IndexNo[i] != SYS_BAT_DOC_EMPTY) {	/** 登録原稿有り */
				MEM_ClearDoc((UBYTE)(SYS_MEM_BATCH_TX_FILE1 + com_no), i, MEM_IGNORE_BOX_NUMBER) ;
			}
		}
	}
#endif
	CancelExecQueue(com_type, com_no);
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_DAILY_POLLING == ENABLE)
	/* 毎日ポーリングＲＯＭ
	** 一度予約したポーリングコマンドは毎日指定時刻実行するものとする
	** 消去されるのは通信予約で削除するか、バックアップが消えたときのみという特殊仕様
	** by O.Kimoto 2002/06/17 */
 	if (ROM_SW_SpecialDailyPolling == 1) {
		if (SYB_CommandFile[com_no].Option.Item == SYS_SELECT_POLLING_RX) {	/** 交信種別判断 */
			if ((old_status != SYS_CMD_ERASED) && (old_status != SYS_CMD_POWER_OFF)) {
				CMN_DisableInterrupt();

				/* 予約を1日進める */
				SYB_CommandFile[com_no].ExecTime += (unsigned long)(24UL*60UL*60UL);
				SYB_CommandFile[com_no].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
				SYB_CommandStatus[com_no] = SYS_CMD_WAITING;
#endif
				CMN_EnableInterrupt();
			}
		}
	}
 #endif
#endif



	return;
}


/*************************************************************************
	module		:[受信モードの獲得]
	function	:[
		1.
	]
	return		:[
		0	電話待機
		1	FAX待機
		2	FAX/電話待機
		3	電話/FAX待機
		4	留守/FAX待機
		5	ダイヤルイン待機
		6	ダイアルインで内蔵TAD待機
		7	内蔵TAD待機

	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/08]
	author		:[村田,渡辺一章]
*************************************************************************/
UBYTE	CMN_PresentReceiveMode(void)
{
	UBYTE	ret;

	if (SYB_RxModeSwitch & SYS_TAD_CALLED_SW) {	/** 内蔵ＴＡＤキー　ＯＮ */
		if (CHK_DialinModeON()) {	/** ダイアルイン設定 */
			ret = SYS_DIALIN_TAD_READY;					/** ダイアルインでＴＡＤ待機 */
		}
		else {						/** ダイアルイン設定でない */
			ret = SYS_TAD_READY;						/** 内蔵ＴＡＤ待機 */
		}
	}
	else {	/** 内蔵ＴＡＤキー　ＯＦＦ */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
		if (CHK_ModemDialinON()) {
			ret = SYS_MODEM_DIALIN_READY;
		}
		else
#endif
		if (CHK_DialinModeON()) {	/** ダイアルイン設定 */
			ret = SYS_DIAL_IN_READY;					/** ダイアルイン待機 */
		}
		else {						/** ダイアルイン設定でない */
#if (PRO_AUTO_RX_SWITCH == ENABLE)
 #if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/9/21 */
		 	if( CheckIsKanyuLine() ){
				ret = (UBYTE)(SYB_RxModeSwitch & SYS_AUTO_CALLED_SW);
			}
			else{
				ret = (UBYTE)(SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW);
			}
 #else
			if (CHK_AutoRxSwitch()) {	/** 自動受信設定 */
				ret = (UBYTE)(CHK_AutoRxMode());	/** 自動受信モード */
			}
			else {						/** 手動受動設定 */
				ret = SYS_TEL_READY;					/** 電話待機 */
			}
 #endif /* Modify end*/
#else
			ret = CHK_AutoRxMode();						/** オペレーションにて設定されている待機モード */
#endif
		}
	}
	return(ret);
}

/*************************************************************************
	module		:[会話予約のON/OFF]
	function	:[
		1.
	]
	return		:[
		TRUE	:SYS_VoiceSwitchを変更
		FALSE	:SYS_VoiceSwitchを変更不可
	]
	common		:[
		SYS_VoiceSwitch
		FaxComPhaseStatus
		TxPageFinishStatus
		RxEOP_ReceiveFlag
	]
	condition	:[]
	comment		:[
		この関数を呼ぶ前に機器が通信中であることを確認すること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/29]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CMN_ChangeVoiceSwitch(void)
{

#if defined(STOCKHM2)	/* QAT：会話予約変更対応 by SMuratec 夏 2004/11/03 */
	if (CHK_VoiceCallEnable()==FALSE){	/* 会話予約無効/有効の獲得 */
		SYS_VoiceSwitch = 0;
		return (FALSE);
	}
#endif

/*	if (((FaxComPhaseStatus & FAX_TX_PH_D) && (TxPageFinishStatus & TX_END)) */
/*	 || ((FaxComPhaseStatus & FAX_RX_PH_D) && (RxEOP_ReceiveFlag == 1))) {	 */
/*		return(FALSE);														 */
/*	  会話予約設定がナックではじかれるやつのデバッグ  1994/09/07 Y.Murata */

	if ((((FaxComPhaseStatus & FAX_TX_PH_D) == FAX_TX_PH_D) && (TxPageFinishStatus == TX_END))
	 || (((FaxComPhaseStatus & FAX_RX_PH_D) == FAX_RX_PH_D) && (RxEOP_ReceiveFlag == 1))
	 || ((FaxComPhaseStatus & FAX_PH_E) == FAX_PH_E)) {
		return(FALSE);
	}
	else {
#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知 95.02.28 T.Nose */
#if (0) /* 95.03.20 T.Nose */
//		if (CHK_RelayedTxReport()) {
//			if ((CommandFileOptionItem == SYS_RELAYED_TX_REPORT) && (FaxComPerformingFlag == 1) && (FaxComTXorRX_Sign == TX_COM_MODE)) {
//				return(FALSE);
//			}
//		}
#endif
		if (TxRelayReport != 0) {
				return(FALSE);
		}
#endif
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/08 */
		if (SYS_V34ProcedureExecuting()) { /* V34 交信中は会話予約できない。 */
			if (SYS_VoiceSwitch == 1) { /* 会話予約がすでにかかっていたら、取り消すことはできるようにする。 Changed by H.Kubo 1998/05/15 */
				SYS_VoiceSwitch = 0;
				return(TRUE);
			}
			return(FALSE);
		}
#endif /* (PRO_TX_SPEED == V34) */

		if (SYS_VoiceSwitch == 1) {
			SYS_VoiceSwitch = 0;
		}
		else {
			SYS_VoiceSwitch = 1;
		}
		return(TRUE);
	}
}

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
/*************************************************************************
	module		:[モデムのリソースの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/01/18]
	author		:[村田]
*************************************************************************/
UWORD far CMN_GetDataSignalingRate(void)
{
	return(SYS_DataSignalingRate);
}
/*************************************************************************
	module		:[モデムのリソースのセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/07/24]
	author		:[久保]
*************************************************************************/
UWORD CMN_SetDataSignalingRate(UWORD rate)
{
	SYS_DataSignalingRate |= rate;
	return(SYS_DataSignalingRate);
}

/*************************************************************************
	module		:[モデムのリソースのリセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/07/24]
	author		:[久保]
*************************************************************************/
UWORD CMN_ResetDataSignalingRate(UWORD rate)
{
	SYS_DataSignalingRate &= ~rate;
	return(SYS_DataSignalingRate);
}


/*************************************************************************
	module		:[会話予約を行うかどうか判断する]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYS_VoiceSwitch
	]
	condition	:[
		交信中であること。
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/01/08]
	author		:[久保博]
*************************************************************************/
UBYTE CMN_GetVoiceSwitch(void)
{
	if (SYS_V34ProcedureExecuting()/* V34 交信中は会話予約できない。*/
	  || FCM_CheckV8ProcedureRequest() ) { /* V8 交信中は V34 になるかも。だから、V8 では会話予約しない。*/
		return FALSE;
	}
	else {
		return(SYS_VoiceSwitch);
	}
}

#endif /* (PRO_TX_SPEED == V34) */
