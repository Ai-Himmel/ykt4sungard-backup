/************************************************************************
*	System		: POPLAR
*	File Name	: SCDRXPIX.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
/*---------------------------------------------------------------------------------------*/
/*	プロジェクト : RISC																	 */
/*	ファイル名	 : scdcrxpix.c															 */
/*	モジュール	 :																		 */
/*				 : unsigned char far SCDC_RxPix(unsigned char ecm_type,					 */
/*				 :							   unsigned char pm_type)					 */
/*				 : unsigned char near SCDC_EcmRx(void)									 */
/*				 : void	far SCDC_RxEcmControlTask(void)									 */
/*				 : void	far	SCDC_BreakRxTask(void)										 */
/*				 : UBYTE CRC_CheckRisc(UBYTE *bfp,	@*	フレームポインタ				 */
/*									   UWORD len,	@*	純フレームレングス				 */
/*									   UWORD fcs_dat)	@*	ＦＣＳ情報					 */
/*	作成者		 : 鈴木																	 */
/*	日	付		 : 94.5.10																 */
/*	概	要		 : 画データ受信処理														 */
/*	修正履歴	 :																		 */
/*---------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\sysdoc.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
 #endif
#endif

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#else
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\define\scdpro.h"
#endif

#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\message.h"
/* For DTC */
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_e.h"	/* By Y.Suzuki 1998/01/23 */

UWORD	FCM_MEM_WriteOpen(struct MEM_StoreData_t *, struct MEM_ExecData_t *);

static UWORD tskno_SCD_RxPixControl = 0;
/* 950131 1line insert */
static UWORD	tskno_SCDC_RxEcmControl = 0;
static UWORD	tskno_SCDC_ECM_Decode = 0;
static UWORD	tskno_SCD_G3_MemRxTask = 0;
/* static UWORD	tskno_SCD_ECM_RxTask = 0;*/
extern UDWORD	ebr_cnt;	/**	ＥＣＭバッファ読み出しバイト数	*/



#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[ＰＩＸ受信]
	function	:[
		1.
	]
	return		:[
		受信結果(MDM_RxPix()ﾘﾀｰﾝ値)
		RX_CONTINUE					0
		RX_PAGE_END					1
		RX_BLOCK_END				2
		RX_STOPPED					3
		RX_MEM_OVER					4
		RX_CARRIER_DOWN				5
		RX_ERROR					6
		RX_TMOUT					7
		RX_STUP_ERR					8
		RX_PRT_ERR					9
		RX_CONTI_ERR				10
		RX_OVER						11
	]
	common		:[
		ソフトコーデック用タスク、サブルーチン起動 95/12/26 Y.S
	]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1995/12/26]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE	SCDC_RxPix(
UBYTE	ecm_type,
UBYTE	pm_type)
{
	UWORD	i;
	UBYTE	rtn;
	UWORD	result;
	MESSAGE_t	*SCD_Msg;
	struct	MEM_IndexData_t	index_data;
	result = 0;
	/*==========================================================================*/
	/*	MDM_PhaseC_Status	フェーズＣステータス初期化は通信の最初で行います	*/
	/*==========================================================================*/
	BreakEcmTaskFlag = YES;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
	ScdcPageEndFlag = 0;	/* 未使用変数です */
#if(0) /* (PRO_CODEC_TYPE == IDP301)		@* Sep.28.1994 */
	CodecReadDataReadyFlag = 0;
#endif
	/*--------------------------------------------------*/
	/*	各受信オープン／タスク起動／受信クローズ処理	*/
	/*--------------------------------------------------*/
	switch (pm_type) {	/**	受信種別	*/
	case RX_MEMORY:	/**	メモリ受信時	*/
		if (ecm_type == ECM_OFF) {	/**	Ｇ３受信時	*/
			BreakRxTaskCompleteFlag = NO;
			/*------------------------------*/
			/*	メモリライトパラメータ設定	*/
			/*------------------------------*/
			RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
			RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
			RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
			RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;
/* #endif */
			/*	蓄積はＭＭＲ／ＭＲをメモリスイッチで指定	*/
		/*	if (CHK_UNI_StoredMethodMMR()) { By Y.Suzuki 1998/01/23 */
			/* ＣＰＵのバージョンが新しければ（A0A0A0より)ＭＭＲ蓄積 By Y.Suzuki 1998/01/26 */
			if ((CHK_UNI_StoredMethodMMR()) && !(CHK_UNI_G3_RX_StoreMR())) {
				RxMemoryStoreData.Code = SYS_MMR_CODE;
			}
			else  {
				RxMemoryStoreData.Code = SYS_MR_CODE;
			}
			RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
			RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
			/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/
			/*------------------------------*/
			/*	メモリライトオープン処理	*/
			/*------------------------------*/
			if (SYS_RxPrintFileItem != 0) {	/** 中継指示受信、中継局同時プリントありならデュアルオープンする */
				index_data.No	= SYS_RxPrintFileNo;
				index_data.Page = SYS_RxPrintFilePage;
				index_data.Item = SYS_RxPrintFileItem;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
				index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
/* #endif */
				result = MEM_DualOpen(&RxMemoryStoreData, &index_data, &MemoryExecData);	/**	メモリデュアルライトオープン	*/
			}
			else {
				/*result = MEM_WriteOpen(&RxMemoryStoreData, &MemoryExecData);*/	/**	メモリライトオープン	*/
				result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MemoryExecData);	/**	メモリライトオープン	*/
			}
			if (result != MEM_OK) {	/**	メモリライトオープン失敗の時	*/

				if (result == MEM_INDEX_CONFLICT) {
					SYS_FaxComIndexConflictStatus = 1;
				}
				else {
					SYS_FaxComIndexConflictStatus = 0;
				}

				tskno_SCD_RxPixControl = 0xffff;
				BreakEcmTaskFlag = YES;
				SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
				return (RX_MEM_OVER);	/**	メモリオーバセット	*/
			}
			CommunicateType = RX_G3_MEM;
			/*rtn = SCDC_G3_MemRx();	@*	ソフトコーデック使用Ｇ３メモリ受信	*/
			tskno_SCD_G3_MemRxTask = 0xffff;
			/**	ｿﾌﾄｺｰﾃﾞｯｸ使用Ｇ３受信タスク起動	*/
			cre_tsk(&tskno_SCD_G3_MemRxTask, TSK_SCD_G3_MEMRXTASK, 0);
			do {
				rcv_msg(mbxno.SCDC_MTxCodeConvertTask, &SCD_Msg);
			} while (!(SCD_Msg->Message == MSG_SCDC_PAGE_END));
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = SCD_G3RxResult;
		}
		/*--------------------------*/
		/*	メモリＥＣＭ受信処理	*/
		/*--------------------------*/
		else {	/**	ＥＣＭ受信時	*/
			BreakEcmTaskFlag = NO;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
			CommunicateType = RX_ECM_MEM;
			/*--------------------------------------*/
			/*	ＥＣＭコントロールタスク起動処理	*/
			/*--------------------------------------*/
			for (i = 0; i < 32; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
				MDM_EcmStatus[i] = 0xff;
			}
			if (MDM_RTC_SeparateFlag == 0) {	/**	ＥＣＭ受信フレーム間またがりフラグが０の時	*/
			/*	if (CodecPageStatus == CDC_READY) {	/**	１つ前の送信がブロックエンドで終了した時以外	*/
				if ((CodecPageStatus == CDC_READY) ||	/**	１つ前の送信がブロックエンドで終了した時以外	*/
					(CodecPageStatus == CDC_DOC_ERROR)) {/* スキャナ送信終了後、ＲＣＲ受信 By Y.Suzuki 1997/09/01 */
					BreakRxTaskCompleteFlag = NO;
					tskno_SCDC_RxEcmControl = 0xffff;
					/**	ｿﾌﾄｺｰﾃﾞｯｸ使用ＥＣＭ受信コントロールタスク起動	*/
					cre_tsk(&tskno_SCDC_RxEcmControl, TSK_SCDC_RXECMCONTROLTASK, 0);
				}
				else {
					/* ブロックエンドが起こった場合 */
					wup_tsk(&tskno_SCDC_ECM_Decode);
				}
				/**	デコード開始メッセージ送信	*/
				SoftcodecMessage.Message = MSG_SCDC_DECODE_START;
				snd_msg(mbxno.SCDC_RxEcmControlTask, &SoftcodecMessage);
			}
			MDM_RTC_SeparateFlag = 0;	/**	ＥＣＭ受信フレームまたがりフラグを０に設定	*/
			rtn = SCDC_EcmRx();	/*	ソフトコーデック使用ＥＣＭメモリ受信	*/
		}
		break;

	case RX_PRINTER:	/**	プリンタ受信時	*/
#if (PRO_PRINTER_RX == ENABLE)
		/*--------------------------*/
		/*	Ｇ３／ＥＣＭ受信処理	*/
		/*--------------------------*/
		if (ecm_type == ECM_OFF) {	/**	Ｇ３受信時	*/
			BreakRxTaskCompleteFlag = NO;
			/*------------------------------------------*/
			/*	プリンタ受信１ページ符号変換タスク起動	*/
			/*------------------------------------------*/
			tskno_SCD_RxPixControl = 0xffff;
			cre_tsk(&tskno_SCD_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
			CommunicateType = RX_G3_PRT;
			rtn = G3_Rx();	/**	Ｇ３受信	*/
		}
		else {						/**	ＥＣＭ受信時	*/
			CommunicateType = RX_ECM_PRT;
			BreakEcmTaskFlag = NO;	/**	ＥＣＭコントロールタスク終了フラグ初期化	*/
	#if (0) /* (PRO_CODEC_TYPE == IDP301) */
			EcmPageEndFlag = 0;		/* RNR Bug.	 Nov.25.1994 */
	#endif
			/*--------------------------------------*/
			/*	ＥＣＭコントロールタスク起動処理	*/
			/*--------------------------------------*/
			for (i = 0; i < 32; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
				MDM_EcmStatus[i] = 0xff;
			}
			if (MDM_RTC_SeparateFlag == 0) {
				if (CodecPageStatus == CDC_READY) {	/**	１つ前の送信がブロックエンドで終了した時以外	*/
					BreakRxTaskCompleteFlag = NO;
					tskno_SCDC_RxEcmControl = 0xffff;
					cre_tsk(&tskno_SCDC_RxEcmControl, TSK_SCDC_RXECMCONTROLTASK, 0);
				}
				SoftcodecMessage.Message = MSG_SCDC_DECODE_START;
				snd_msg(mbxno.SCDC_RxEcmControlTask, &SoftcodecMessage);
			}
			MDM_RTC_SeparateFlag = 0;
			rtn = SCDC_EcmRx();	/**	ＥＣＭ受信	*/
		}
#endif
		break;
	case RX_BKUPRAM:	/* ●ICHOU追加 高速ＲＤＳ データライト by T.Soneoka 1996/06/18 */
		CommunicateType = RX_ECM_BKUPRAM;
		/*
		** ＥＣＭステータス０ｘＦＦで初期化していないと、前の状態で動作するため、実際受けれていないのに
		** ＰＰＲを返さないで変なデータを書き込んでしまう 1998/03/27  By T.Yamaguchi
		*/
		/*--------------------------------------*/
		/*	ＥＣＭコントロールタスク起動処理	*/
		/*--------------------------------------*/
		for (i = 0; i < 32; i++) {	/**	ＥＣＭステータス０ｘＦＦで初期化	*/
			MDM_EcmStatus[i] = 0xff;
		}
		BreakRxTaskCompleteFlag = YES;	/* 子タスクを全く起動しないので最初からＹＥＳにする */
#if 0	/* SCDC_EcmRx()でTMOUTで戻ってきた場合きれてしまう */
//		タイムアウト回避を有効にする	1998/04/09  By T.Yamaguchi
//		SCDC_EcmRx();
//		rtn = RX_PAGE_END;
#endif
		rtn = SCDC_EcmRx();	/**	ＥＣＭ受信	*/
		break;
	}
	return (rtn);
}


/*************************************************************************
	module		:[ＥＣＭ受信]
	function	:[
		1.
	]
	return		:[]
	common		:[
		MDM_PhaseC_Status
	]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1993/12/28]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE	SCDC_EcmRx(
void)
{
	UBYTE	retry_cnt;	/**	モデムリードリトライカウンタ	*/
	UBYTE	mdm_cnt_save;	/**	ショートフレーム対策用モデム書き込み位置保存	*/
	UBYTE	short_flg;	/**	ショートフレーム対策用ショートフレーム受信有無フラグ	*/
	UBYTE	rtn;
	UBYTE	tmp_rp;
	UBYTE	loop_flg;
	UBYTE	hold_flg;
	struct	DMA_DTC_Data_t dma_setup;/* For DTC By Y.Suzuki 1997/06/15 */

	tmp_rp = 0;
	short_flg = 0;	/**	ショートフレームフラグ初期化	*/
/* 950105 6line Insert for R.5.2 */
	if (CHK_UNI_ECM_RxTM_OutEvade()) {
		retry_cnt = 3;
	}
	else {
		retry_cnt = 0;
	}
#if defined(DEU)
	/* ドイツ申請時、キャリア断の時、６±１秒で回線断させるため */
	retry_cnt = 3;
#endif
/*  950105 1line Delete for R.5.2 */
/*	retry_cnt = 0;	**	リードリトライカウンタ初期化	*/
	mdm_cnt_save = 0;	/**	ショートフレーム対策用モデム書き込み位置初期化	*/
	MDM_EcmFrameNumber = 0;	/**	ＥＣＭフレームナンバー初期化	*/
	hold_flg = 0;
	SCD_Det_Rcp = 0;	/*	By Y.Suzuki 1997/07/01	*/

	loop_flg = 1;	/**	ループ制御フラグ１に設定	*/
	while (loop_flg) {/**	１ブロック受信するまでループ	*/
		rtn = RxEcmRead();	/**	受信ＥＣＭリード	*/
		if (rtn == RCV_BLOCK) {	/**	受信フレーム有り	*/
			/*------------------------------*/
			/*	イコライザーホールド処理	*/
			/*------------------------------*/
			if (hold_flg == 0) {
				if (CHK_V17EqualizerHold()) {	/**	イコライザホールドのメモリスイッチが有効の時	*/
					if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
						EqualizerHoldOn();	/**	イコライザホールドに設定	*/
					}
				}
				hold_flg = 1;
			}
			switch (MDM_ModemBuffer[ModemControl.ReadPoint][FCF_FLD]) {	/**	受信フレームのＦＣＦフィールドを見る	*/
			/*--------------------------*/
			/*	ＦＣＤフレーム受信処理	*/
			/*--------------------------*/
			case HDLC_FCD:	/**	ＦＣＤフレーム受信の時	*/
				MDM_EcmFrameNumber = MDM_ModemBuffer[ModemControl.ReadPoint][FIF_FLD];	/**	ＥＣＭフレームナンバをセット	*/
				/*----------------------*/
				/* ショートフレーム処理	*/
				/*----------------------*/
				if (MDM_RxSize[ModemControl.ReadPoint] != (FcomEcmSize+6)) {	/**	アドレス＋コントロール＋ＦＣＤ＋フレームＮｏ＋ＦＩＦ（２５６／６４）＋ＦＣＳ	*/
					short_flg = 1;	/**	ショートフレーム受信フラグセット	*/
#if (0) /* ショートフレームの場合でも、フレーム数に関係なく、モデムバッファ１本分全て、待避するように変更します */
//					RxFrameLength = MDM_RxSize[ModemControl.ReadPoint];	/**	ショートフレームサイズ保存	*/
//					if (SYB_MaintenanceSwitch[MNT_SW_F1] & DTC_OFF) {
//						MemoryMove(FaxComTxFrame,
//							&MDM_ModemBuffer[ModemControl.ReadPoint][0], RxFrameLength);	/**	ショートフレーム保存	*/
//					}
//					else {
//						dma_setup.Unit = DMA_BYTE_TRANSFER;
//					/*	dma_setup.Length = next_mbf_set_cnt;*/
//						dma_setup.DTC_Mode = DTC_BLOCK_MODE;	/* 1997/07/17  By T.Yamaguchi */
//						dma_setup.Length = RxFrameLength;
//						dma_setup.Counter = 1;
//					/*	dma_setup.SrcAddress= (UDWORD)(ebf_base_rp+ebr_cnt);*/
//						dma_setup.SrcAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.ReadPoint][0]);
//					/*	dma_setup.DstAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.WritePoint][0]);*/
//						dma_setup.DstAddress= (UDWORD)(&FaxComTxFrame);
//						CMN_DisableInterrupt();
//						DMA_SetupDTC(&dma_setup);
//					/*	DMA_DTC_TransferStart();	1997/07/17  By T.Yamaguchi */
//						DMA_DTC_TransferStart(DTC_BLOCK_MODE);
//						CMN_EnableInterrupt();
//					}
#endif	/* 1998/04/01  By T.Yamaguchi */
					if (SYB_MaintenanceSwitch[MNT_SW_F1] & DTC_OFF) {
						MemoryMove((UBYTE *)FaxComTxFrame, (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], (UWORD)MODEM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
					}
					else {
						dma_setup.Unit = DMA_BYTE_TRANSFER;
						dma_setup.DTC_Mode = DTC_BLOCK_MODE;	/* 1997/07/17  By T.Yamaguchi */
						dma_setup.Length = MODEM_BUFFER_LENGTH;
						dma_setup.Counter = 1;
						dma_setup.SrcAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.ReadPoint][0]);
						dma_setup.DstAddress= (UDWORD)(&FaxComTxFrame);
						CMN_DisableInterrupt();
						DMA_SetupDTC(&dma_setup);
						DMA_DTC_TransferStart(DTC_BLOCK_MODE);
						CMN_EnableInterrupt();
					}
					break;
				}
				short_flg = 0;	/**	ショートフレーム受信フラグ初期化	*/
				/*-------------------------------------------------------*/
				/*	モデムバッファからＥＣＭバッファにプログラム転送処理 */
				/*-------------------------------------------------------*/
#if(0) /* 941205 Modify for Speed Up */
//				for (i = 0; i < 256; i++) {	/**	０から２５５までループ	*/
//					EcmBuffer[MDM_EcmFrameNumber][i] = MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD+i];
//						/**	ＥＣＭバッファの該当フレームナンバの位置に、受信フレームのデータ部分からコピー	*/
//				}
#endif
					if (SYB_MaintenanceSwitch[MNT_SW_F1] & DTC_OFF) {
						MemoryMove(&EcmBuffer[MDM_EcmFrameNumber][0],
							&MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD], ECM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
					}
					else {
						dma_setup.Unit = DMA_BYTE_TRANSFER;
					/*	dma_setup.Length = next_mbf_set_cnt;*/
						dma_setup.DTC_Mode = DTC_BLOCK_MODE;	/* 1997/07/17  By T.Yamaguchi */
						dma_setup.Length = ECM_BUFFER_LENGTH;
						dma_setup.Counter = 1;
					/*	dma_setup.SrcAddress= (UDWORD)(ebf_base_rp+ebr_cnt);*/
						dma_setup.SrcAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD]);
					/*	dma_setup.DstAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.WritePoint][0]);*/
						dma_setup.DstAddress= (UDWORD)(&EcmBuffer[MDM_EcmFrameNumber][0]);
						CMN_DisableInterrupt();
						DMA_SetupDTC(&dma_setup);
					/*	DMA_DTC_TransferStart();	1997/07/17  By T.Yamaguchi */
						DMA_DTC_TransferStart(DTC_BLOCK_MODE);
						CMN_EnableInterrupt();
					}
#if (0)
//				/* 竹内 Dec.06.1994 */
//				MemoryMove2( &EcmBuffer[MDM_EcmFrameNumber][0],
//							 &MDM_ModemBuffer[ModemControl.ReadPoint][FDF_FLD],
//							 ECM_BUFFER_LENGTH);			/**	ショートフレーム保存	*/
#endif
				/*------------------------------------------*/
				/*	ＥＣＭバッファフレームステータス有効	*/
				/*------------------------------------------*/
				EnableEcmStatus(MDM_EcmFrameNumber);	/**	ＥＣＭバッファフレームステータス有効	*/
				break;
			/*----------------------*/
			/*	ＲＣＰフレーム受信	*/
			/*----------------------*/
			case HDLC_RCP:	/**	ＲＣＰフレーム受信の時	*/
				SCD_Det_Rcp = 1;	/*	By Y.Suzuki 1997/07/01	*/
				loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
				/*-------------------------------------*/
				/*	最終フレームがショートフレームの時 */
				/*-------------------------------------*/
				if (short_flg == 1) {	/**	ショートフレーム受信済み	*/
					MDM_EcmFrameNumber = FaxComTxFrame[FIF_FLD];
					/*-------------------------------------------------------*/
					/*	モデムバッファからＥＣＭバッファにプログラム転送処理 */
					/*-------------------------------------------------------*/
#if(0) /* 941205 Modify for Speed Up */
//					for (i = 0; i < (RxFrameLength - 2); i++) {
//						EcmBuffer[MDM_EcmFrameNumber][i] = FaxComTxFrame[FDF_FLD+i];
//						/**	ＥＣＭバッファの該当フレームナンバの位置に、受信フレームのデータ部分からコピー	*/
//					}
#endif
#if 0	/* ショートフレームの場合でも、２５６分固定でＥＣＭバッファに転送します */
//					if (SYB_MaintenanceSwitch[MNT_SW_F1] & DTC_OFF) {
//						MemoryMove(&EcmBuffer[MDM_EcmFrameNumber][0],
//							&FaxComTxFrame[FDF_FLD], (RxFrameLength-6));	/**	ショートフレーム保存	*/
///*							&FaxComTxFrame[FDF_FLD], (RxFrameLength-2));	/@@	ショートフレーム保存 2→6 1998/03/27  By T.Yamaguchi	*/
//					}
//					else {
//						dma_setup.Unit = DMA_BYTE_TRANSFER;
//					/*	dma_setup.Length = next_mbf_set_cnt;*/
//						dma_setup.DTC_Mode = DTC_BLOCK_MODE;	/* 1997/07/17  By T.Yamaguchi */
//						dma_setup.Length = RxFrameLength-6;
//					/*	dma_setup.Length = RxFrameLength-2; 2→6 1998/03/27  By T.Yamaguchi */
//						dma_setup.Counter = 1;
//					/*	dma_setup.SrcAddress= (UDWORD)(ebf_base_rp+ebr_cnt);*/
//						dma_setup.SrcAddress= (UDWORD)(&FaxComTxFrame[FDF_FLD]);
//					/*	dma_setup.DstAddress= (UDWORD)(&MDM_ModemBuffer[ModemControl.WritePoint][0]);*/
//						dma_setup.DstAddress= (UDWORD)(&EcmBuffer[MDM_EcmFrameNumber][0]);
//						CMN_DisableInterrupt();
//						DMA_SetupDTC(&dma_setup);
//					/*	DMA_DTC_TransferStart();	1997/07/17  By T.Yamaguchi */
//						DMA_DTC_TransferStart(DTC_BLOCK_MODE);
//						CMN_EnableInterrupt();
//					}
#endif
					if (SYB_MaintenanceSwitch[MNT_SW_F1] & DTC_OFF) {
						MemoryMove((UBYTE *)&EcmBuffer[MDM_EcmFrameNumber][0], (UBYTE *)&FaxComTxFrame[FDF_FLD], (UWORD)ECM_BUFFER_LENGTH);	/**	ショートフレーム保存	*/
					}
					else {
						dma_setup.Unit = DMA_BYTE_TRANSFER;
						dma_setup.DTC_Mode = DTC_BLOCK_MODE;	/* 1997/07/17  By T.Yamaguchi */
						dma_setup.Length = (UWORD)ECM_BUFFER_LENGTH;
						dma_setup.Counter = 1;
						dma_setup.SrcAddress= (UDWORD)(&FaxComTxFrame[FDF_FLD]);
						dma_setup.DstAddress= (UDWORD)(&EcmBuffer[MDM_EcmFrameNumber][0]);
						CMN_DisableInterrupt();
						DMA_SetupDTC(&dma_setup);
						DMA_DTC_TransferStart(DTC_BLOCK_MODE);
						CMN_EnableInterrupt();
					}
#if (0)
//					/* 竹内 Dec.06.1994 */
//					MemoryMove2( &EcmBuffer[MDM_EcmFrameNumber][0],
//								 &FaxComTxFrame[FDF_FLD],
//								 (RxFrameLength-2));	/**	ショートフレーム保存	*/
#endif
					/*------------------------------------------*/
					/*	ＥＣＭバッファフレームステータス有効	*/
					/*------------------------------------------*/
					EnableEcmStatus(MDM_EcmFrameNumber);	/**	ＥＣＭバッファフレームステータス有効	*/
				}
				rtn = MDM_PhaseC_Status;	/*	今現在のデーコード状態を返す	*/
				break;
			/*--------------------------*/
			/*	不当フレーム受信処理	*/
			/*--------------------------*/
			default:	/**	不当フレーム受信処理	*/
				break;
			}
			/*--------------------------------------*/
			/*	モデムバッファ読み出し位置更新処理	*/
			/*--------------------------------------*/
			NextModemBufferReadPointSet();	/**	モデムバッファ読み出し位置更新処理	*/
		}
		/*------------------------------*/
		/* タイムアウト時（６秒）処理	*/
		/*	現在３回で１８秒			*/
		/*------------------------------*/
		else if (rtn == RCV_TMOUT) {	/**	タイムアウト時	*/
/* '94.11.28 941226 remodify for zenshiro rx */
			if (retry_cnt++ >= 3) {	/**	３回目のタイムアウト時	*/
				rtn = RX_TMOUT;	/**	戻り値タイムアウト設定	*/
				loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
			}
		}
		else if (rtn == RCV_STOP) {	/**	ストップＳｗ	*/
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STOPPED;	/**	戻り値ストップＳｗ設定	*/
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
		}
		else {	/**	その他の時	*/
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			rtn = RX_STUP_ERR;	/**	戻り値セットアップエラー設定	*/
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		}
		/* メモリオーバー時に受信できなかった原稿をプリントしないようにする By Y.Suzuki 1998/02/20 */
		/* ＲＣＰフレームまで受信していたのをメモリオーバー時は、すぐ抜けるように変更 */
		if (MDM_PhaseC_Status == RX_MEM_OVER) {
			rtn = MDM_PhaseC_Status;	/*	今現在のデーコード状態を返す	*/
			loop_flg = 0;	/**	ループ制御フラグ０に設定	*/
		}
	}
	return(rtn);
}
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/


/*************************************************************************
	module		:[ＥＣＭ受信コントロールタスク]
	function	:[
		1.ＥＣＭ受信したフレームをフレーム番号０から順次デコードを実行する
		2.受信フレームが無い場合１００ｍｓタスクウェイトをおき、
		　再度受信フレームがないかどうかチェックする。
	]
	return		:[]
	common		:[
			ソフトコーデック使用メモリＥＣＭ受信コントロールタスク 95/12/26 Y.S
	]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1994/02/22]
	author		:[鈴木郁ニ]
*************************************************************************/
void	SCDC_RxEcmControlTask(
void)
{
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	MESSAGE_t	*SCD_Msg;

	UBYTE	page_loop;
	UWORD	result;
	struct	MEM_IndexData_t	index_data;

	result = 0;
	DecodeEcmFrameNum = 0;
	CodecPageStatus = CDC_CONTINUE;	/**	符号変換終了ステータスを初期化	*/
	MDM_PhaseC_Status = RX_CONTINUE;
	MDM_RxTotalLine = 0;	/**	１ページトータルライン数初期化	*/
	MDM_RxErrorTotalLine = 0;	/**	１ページエラーライン数初期化	*/
	MDM_EncodeLine = 0;
/*	DebugDecodeStartFlag = 0; */

	/*------------------------------*/
	/*	デコード開始メッセージ受信	*/
	/*------------------------------*/
	while (1) {
		rcv_msg(mbxno.SCDC_RxEcmControlTask, &SCD_Msg);	/**	デコード開始メッセージ受信	*/
		if (SCD_Msg->Message == MSG_SCDC_DECODE_START) {
			break;
		}
	}
	if (CommunicateType == RX_ECM_MEM) {	/**	ＥＣＭメモリ受信の場合	*/
		/*------------------------------*/
		/*	メモリライトパラメータ設定	*/
		/*------------------------------*/
		RxMemoryStoreData.No   = SYS_DocBlock.Index.No;
		RxMemoryStoreData.Page = SYS_DocBlock.Index.Page;
		RxMemoryStoreData.Item = SYS_DocBlock.Index.Item;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
		RxMemoryStoreData.BoxNumber = SYS_DocBlock.Index.BoxNumber;
/* #endif */
		/*	蓄積はＭＭＲ／ＭＲをメモリスイッチで指定	*/
		if (CHK_UNI_StoredMethodMMR()) {
			RxMemoryStoreData.Code = SYS_MMR_CODE;
		}
		else {
			RxMemoryStoreData.Code = SYS_MR_CODE;
		}
		RxMemoryStoreData.Mode = SYS_DocBlock.Src.Mode;
		RxMemoryStoreData.Size = SYS_DocBlock.Src.Size;
		/*	上記のサイズにミリ系・インチ系ビットを立てる MEM_MILLI_BIT	*/

		/*------------------------------*/
		/*	メモリライトオープン処理	*/
		/*------------------------------*/
		/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/10/14 Y.Suzuki */
		if (SYS_RxPrintFileItem != 0) {
			index_data.No	= SYS_RxPrintFileNo;
			index_data.Page = SYS_RxPrintFilePage;
			index_data.Item = SYS_RxPrintFileItem;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
			index_data.BoxNumber = SYS_RxPrintFileBoxNumber;
/* #endif */
			result = MEM_DualOpen(&RxMemoryStoreData, &index_data, &MemoryExecData);
		}
		else {
			/*result = MEM_WriteOpen(&RxMemoryStoreData, &MemoryExecData);*/
			result = FCM_MEM_WriteOpen(&RxMemoryStoreData, &MemoryExecData);
		}
		if (result != MEM_OK) {

			if (result == MEM_INDEX_CONFLICT) {
				SYS_FaxComIndexConflictStatus = 1;
			}
			else {
				SYS_FaxComIndexConflictStatus = 0;
			}

			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();		/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_MEM_OVER;	/**	受信セットアップエラーセット	*/
			exi_tsk();	/**	自タスク終了処理	*/
		}
	}
	/*------------------------------*/
	/*	ＥＣＭフレーム受信待ち処理	*/
	/*------------------------------*/
	/**	モデムバッファ --> ＥＣＭバッファ ２５６転送待ち	*/
	while (CheckEcmStatus(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
		wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
		if (CodecPageStatus != CDC_CONTINUE) {
			break;
		}
	}
	/*--------------------------------------*/
	/*	受信１ページ符号変換タスク起動処理	*/
	/*--------------------------------------*/
	/* ソフトコーデック1ページ処理起動に変更 95/12/26 Y.S */
	tskno_SCDC_ECM_Decode = 0xffff;
	if (CommunicateType == RX_ECM_MEM) {	/**	ＥＣＭメモリ受信の場合	*/
		cre_tsk(&tskno_SCDC_ECM_Decode, TSK_SCDC_ECMDECODETASK, 0);
	}
#if(0)/* ｿﾌﾄｺｰﾃﾞｯｸ用 不要 95/12/26 Y.S */
//	else {									/**	ＥＣＭプリンタ受信の場合	*/
//		/* ソフトコーデックは、今のところメモリ受信のみ ここには、こないはず */
//		cre_tsk(&tskno_RxPixControl, TSK_CDC_PRXCODECONVERTPAGETASK, 0);	/**	プリンタ受信１ページ符号変換タスク起動	*/
//	}
#endif/* ｿﾌﾄｺｰﾃﾞｯｸ用 不要 95/12/26 Y.S */
	page_loop = 1;	/**	１ページデコード終了フラグ設定	*/
/* 941202 */
	while (page_loop) {	/**	１ページデコードするまでループ	*/
		/*--------------------------------------*/
		/*	メッセージ受信待ち					*/
		/*	1.デコードＤＭＡ終了割り込みより	*/
		/*	2.受信デバイス監視タスクより		*/
		/*--------------------------------------*/
		/**	256バイトデコード終了時	*/
		/* １ページ終了待ち 95/12/26 Y.S */
/*		DebugDecodeStartFlag = 0;*/
		wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
		switch (CodecPageStatus) {	/**	受信１ページ符号変換タスク状態	*/
		case	CDC_BLOCK_END:	/**	ブロックエンド	*/
				SCD_Det_Rcp = 1;	/*	By Y.Suzuki 1997/07/01	*/
			MDM_PhaseC_Status = RX_BLOCK_END;	/**	ブロックエンド設定	*/
			do {
				rcv_msg(mbxno.SCDC_RxEcmControlTask, &SCD_Msg);	/**	デコード開始メッセージ受信	*/
			} while (!(SCD_Msg->Message == MSG_SCDC_DECODE_START));
			switch (CodecPageStatus) {
			case	CDC_RTC_DET:
				BreakEcmTaskFlag = YES;
				SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
				MDM_PhaseC_Status = RX_PAGE_END;
				page_loop = 0;
				break;
			case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
				BreakEcmTaskFlag = YES;
				SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
				MDM_PhaseC_Status = RX_ERROR;
				page_loop = 0;
				break;
			case	CDC_MEM_OVER:
				BreakEcmTaskFlag = YES;
				SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
				MDM_PhaseC_Status = RX_MEM_OVER;	/**	メモリオーバセット	*/
				page_loop = 0;
				break;
#if (PRO_PRINTER_RX == ENABLE)		/* Takeuchi	 Nov.15.1994 */
			case	CDC_PRINTER_ERROR:
				BreakEcmTaskFlag = YES;
				SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
				MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
				page_loop = 0;
				break;
#endif
			default:
				MDM_PhaseC_Status = RX_CONTINUE;
				SCD_Det_Rcp = 0;	/*	By Y.Suzuki 1997/07/01	*/
			/*	DecodeEcmFrameNum = 0;	*	ＥＣＭフレームナンバ初期化	*/
				break;
			}
			break;
		case	CDC_CONTINUE:	/**	デコード継続	*/
			break;
		case	CDC_RTC_DET:	/**	ＲＴＣ検出時	*/
			SCD_Det_Rcp = 1;	/*	By Y.Suzuki 1997/07/07	*/
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_PAGE_END;
			page_loop = 0;
			break;
		case	CDC_DECODE_ERROR:	/**	デコードエラー時	*/
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_ERROR;
			page_loop = 0;
			break;
		case	CDC_STOPPED:	/**	強制終了発生時	*/
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_STOPPED;
			page_loop = 0;
			break;
		case	CDC_PAGE_SEPARATE:	/**	最大受信原稿長制限オーバ処理	*/
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_OVER;
			page_loop = 0;
			break;
#if (PRO_PRINTER_RX == ENABLE)		/* Takeuchi	 Nov.15.1994 */
		case	CDC_PRINTER_ERROR:
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_PRT_ERR;		/**	Printer Error セット	*/
			page_loop = 0;
			break;
#endif
		case	CDC_MEM_OVER:
		default:
			BreakEcmTaskFlag = YES;
			SCDC_BreakRxTask();	/**	受信子タスク終了処理	*/
			MDM_PhaseC_Status = RX_MEM_OVER;	/**	メモリオーバセット	*/
			page_loop = 0;
			break;
		}
	}
	exi_tsk();	/**	自タスク終了処理	*/
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
}


#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[受信タスク強制終了]
	function	:[
		1.ＥＣＭ受信タスクの中からコーデックアボードコマンドを呼ぶことで
		　ＥＣＭ受信タスクで自タスク終了する。
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1994/02/25]
	author		:[鈴木郁ニ]
*************************************************************************/
void	SCDC_BreakRxTask(void)
{
	if (BreakRxTaskCompleteFlag == YES) {
		return;
	}
	if (SYS_RxTotalPage < MDM_ERR_LINE_DATA_MAX) {
		MDM_RxTotalLineSave[SYS_RxTotalPage] = MDM_RxTotalLine;
		MDM_RxErrorTotalLineSave[SYS_RxTotalPage] = MDM_RxErrorTotalLine;
	}
	switch (CommunicateType) {
	case	RX_G3_MEM:
	case	RX_ECM_MEM:
		if (CommunicateType == RX_G3_MEM) {
			if (tskno_SCD_G3_MemRxTask != 0xffff) {
				del_tsk(&tskno_SCD_G3_MemRxTask);
			}
		}
		else {
				if (tskno_SCDC_ECM_Decode != 0xffff) {
					del_tsk(&tskno_SCDC_ECM_Decode);
				}
			}
/*		}*/
		/* MEM_DMAEndStatus |= MEM_RX_PAGE_END;	*/
	/*	det_evt(EVT_DMA0_TC1); MEMREAD.C 未使用なら不要 By Y.Suzuki 1996/07/23 */
		/* 中継指示受信、中継局同時プリントありならデュアルオープンする 94/9/28 Y.Suzuki */
		if (SYS_RxPrintFileItem != 0) {
			MEM_DualClose(&MemoryExecData, MDM_EncodeLine);
		}
		else {
			/*MEM_WriteClose(&MemoryExecData, MDM_EncodeLine);*/
			if (SYS_FaxComIndexConflictStatus == 0) {
				MEM_WriteClose(&MemoryExecData, MDM_EncodeLine);
			}
		}
	/*	DMA_RequestMask(MASTER_DMAU, 2);/@ ほんとに必要か確認 By Y.Suzuki 1996/07/23 */
	/*	DMA_RequestMask(DMA_MDM_MDMBUF_CH);CDC--DRAMは、ソフト転送なんでいりません By Y.Suzuki 1997/10/14 */
#if(0)/* for ｿﾌﾄｺｰﾃﾞｯｸ 95/12/27 Y.S */
/* #if (PRO_CODEC_TYPE == MN86063) By Y.Suzuki 1996/10/18 */
//#if (PRO_CODEC_TYPE == MN86064)
//		if (tskno_RxDeviceWriteControl != 0xffff) {
//			del_tsk(&tskno_RxDeviceWriteControl);
//		}
//		DMA_RequestMask(MASTER_DMAU, 2);
//#endif
//		break;
//	case	RX_G3_PRT:
//	case	RX_ECM_PRT:
//		/* ﾊｰﾄﾞｺｰﾃﾞｯｸの終了処理は、prt_rxの時のみ行う 95/12/25 Y.S */
		/*------------------------------------------*/
		/*	メモリ受信１ページ符号変換タスク終了	*/
		/*------------------------------------------*/
//		if (tskno_RxPixControl != 0xffff) {
			/*------------------------------*/
			/*	通信コーデックを開放する	*/
			/*------------------------------*/
	/* #if (PRO_CODEC_TYPE == MN86063) By Y.Suzuki 1996/10/18 */
//	#if (PRO_CODEC_TYPE == MN86064)
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
//				SaveReturnAddressAndJumpBegin();
//			}
//	#endif
//			del_tsk(&tskno_RxPixControl);
//		}
	/* #if (PRO_CODEC_TYPE == MN86063) By Y.Suzuki 1996/10/18 */
//	#if (PRO_CODEC_TYPE == MN86064)
//		if (tskno_DecodeDMA_End != 0xffff) {
//			del_tsk(&tskno_DecodeDMA_End);
//		}
//		DMA_RequestMask(SLAVE1_DMAU, 0);
//	#endif
#endif/* for ｿﾌﾄｺｰﾃﾞｯｸ 95/12/27 Y.S */
	/*	DMA_RequestMask(SLAVE1_DMAU, 0);ハードコデック未使用ならいらないはず By Y.Suzuki 1996/11/26 */
		break;
	}
	switch (CommunicateType) {
	case	RX_ECM_MEM:
	case	RX_ECM_PRT:
		if (BreakEcmTaskFlag != YES) {
			if (tskno_SCDC_RxEcmControl != 0xffff) {
				del_tsk(&tskno_SCDC_RxEcmControl);
			}
		}
		break;
	default:
		break;
	}
	CodecPageStatus = CDC_READY;
	BreakRxTaskCompleteFlag = YES;
}


/*************************************************************************
	module		:[ＣＲＣチェック]
	function	:[
		1.
	]
	return		:[
		OK:		ＣＲＣチェックＯＫ
		NG:		ＣＲＣチェックＮＧ
	]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[奇数アドレスに対するワードアクセスを防止するため、ＦＣＳの渡し方変更]
	machine		:[SH704X/SH7034]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1996/7/23]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE CRC_CheckRisc(
UBYTE *bfp,	/*	フレームポインタ	*/
UWORD len,	/*	純フレームレングス	*/
UWORD fcs_dat)	/*	ＦＣＳ情報	*/
{
	UWORD	chk_rslt;

	chk_rslt = 0;

	chk_rslt = crc(len, bfp);
	if (chk_rslt != fcs_dat) {
		return (NG);
	}
	return (OK);
}
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
