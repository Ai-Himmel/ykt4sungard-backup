/*------------------------------------------------------------------------------------*/
/*  プロジェクト	: POPLAR_F                                                        */
/*  ファイル名		: mdm.c                                                           */
/*  作成者			:                                                                 */
/*  日  付			: 1999/10/06                                                      */
/*  概  要			: モデムセットアップ処理                                          */
/*	keyword			:[MDM]                                                            */
/*	machine			:[SH7043,V53]                                                     */
/*	language		:[MS-C(Ver.6.0)]                                                  */
/*  修正履歴		:                                                                 */
/*------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 通信中電源断後、復帰しない件に対する対策。Added by H.Kubo 1998/11/17 *//* 2002/09/18 By M.Maeda */
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#endif

#if defined(HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* for NEWC debug 2002/12/27 T.Takagi */
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
#include "\src\atlanta\ext_v\fcm_data.h"
#endif

CONST UBYTE TCF_DEBUG = 0;	/* 1996/10/11 Y.M */
CONST UBYTE INT_DEBUG = 1;	/* for Searching a  long common interrupt and modem interrupt by O.Kimoto 1998/02/02 */
CONST UBYTE DBG_EXT_FIFO = 0;	/* For Debug Extended Fifo -26P by O.Kimoto 1998/11/19 */
#if (0) /* 1999/10/06 */
//CONST UBYTE DBG_IO = 0;		/* For I/O Debug 1999/02/22 by K.Okada */
//UWORD Address = 0xFFFF;		/* For I/O Debug 1999/02/22 by K.Okada */
//UWORD Address2 = 0xFFFF;	/* For I/O Debug 1999/02/22 by K.Okada */
//UBYTE BData = 0xFF;			/* For I/O Debug 1999/02/22 by K.Okada */
//UBYTE BMaskData = 0xFF;		/* For I/O Debug 1999/02/22 by K.Okada */
//UWORD WData = 0xFFFF;		/* For I/O Debug 1999/02/22 by K.Okada */
//UWORD WMaskData = 0xFFFF;	/* For I/O Debug 1999/02/22 by K.Okada */
#endif

/*************************************************************************
	module		:[モデムハードウェアリセット]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1999/05/07]
	author		:[K.Okada]
*************************************************************************/
void		MDM_ModemHardwareReset(void)
{
	Reset288ModemOn();
	wai_tsk(2); /* RESET 端子の 0 を少なくとも 3us 保つ。 */
	Reset288ModemOff();
}

/*************************************************************************
	module		:[モデムＨ／Ｗ初期化処理]
	function	:[
		1.モデムＩ／Ｆエリア初期化
		2.ゼロクロスタイム５０ｍｓ
		3.ケーブルイコライザ／郡遅延歪設定
		4.Ｔｘアッテネータレベル設定
	]
	return		:[なし]
	common		:[
		ModemBlock
		MDM_RxSize
		SYS_MachinecParameter
		PartnerAbility1
		ServiceFuncTx
		MDM_RxTotalLineSave
		MDM_RxErrorTotalLineSave
		MDM_PhaseC_Status
		MDM_TxStopSwFlag
		MDM_RTC_SeparateFlag
		DecodeEcmFrameNum
		GetCodecFlag
		CommunicateType
	]
	condition	:[]
	comment		:[]
	date		:[1994/01/08]
	author		:[曽根岡拓]
*************************************************************************/
void		MDM_ModemInitialize(void)
{
	UBYTE i;
	UBYTE  *modem_register_data_ptr;

#if defined(POPLAR_F)	/* 2000/02/04 Y.Murata */
	CMN_DisableInterrupt();
	MDM_StxLoopCounter = 0;
	CMN_EnableInterrupt();
#endif

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 通信中電源断後、復帰しない件に対する対策。Added by H.Kubo 1998/11/17 *//* 2002/09/18 By M.Maeda */
	DMA_RequestMask(DMA_CH_TX);
	DMA_RequestMask(DMA_CH_RX);
	DMA_RequestMask(DMA_CH_ENC);
	DMA_RequestMask(DMA_CH_DEC);
	/* カウンタを 0 に設定し、何かの間違いで終了割り込みが入った時、不要な再起動がかかるのを防ぎます。 */
	DMA_SetDMA_Counter(DMA_CH_RX,0);
	DMA_SetDMA_Counter(DMA_CH_TX,0);
	DMA_SetDMA_Counter(DMA_CH_ENC,0);
	DMA_SetDMA_Counter(DMA_CH_DEC,0);
#endif

	SetClear((UBYTE *)&ModemBlock, sizeof(struct mdmblk_t), 0x00);					/**	モデムＩ／Ｆエリアクリア	*/

	SetClear((UBYTE *)MDM_RxSize, MODEM_BUFFER_MAX*sizeof(MDM_RxSize[0]), 0x00);	/** 受信ﾌﾚｰﾑﾃﾞｰﾀｻｲｽﾞｸﾘｱ */
																				 	/* Modified by H.Kubo 1997/12/26 */
	SetClear(&ModemZeroBuffer[0], MODEM_DMA_SIZE, 0x00);		/**	送出データ数分、モデムバッファ０ｘ００でクリア	*/
																/** 256 Bytes **/
	SetClear((UBYTE *)&CDC_JBG_BIH, sizeof(struct JBG_BIH_Data_t), 0x00);	/**	JBIG BIGデータクリア	*/
																			/*  by T.Soneoka 1997/12/17 */
	ServiceFuncTx = FALSE;	/**	サービスファンクション用高速／低速データ切り替えＳｗクリア	*/
	MDM_ClearTskNoBuffer();	/** Clear Tsk ID Buffers By O.Kimoto 1996/07/27 **/

	for (i = 0; i < MDM_ERR_LINE_DATA_MAX; i++) {	/** 受信トータルライン、エラーライン数格納エリアのクリア */
		MDM_RxTotalLineSave[i]      = 0;
		MDM_RxErrorTotalLineSave[i] = 0;
	}

	/*
	** add 2line 1997/01/15 Y.Murata
	*/
	MDM_RxTotalLine = 0;
	MDM_RxErrorTotalLine = 0;

	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	MDM_V21MeasureStartGo = 0;		/* これはここでクリアせなあかん 1997/12/24 */
	MDM_RTH_ControlStatus = 0xFF;	/* 1997/12/22 RTH_CONTROL */ /* Ported from CLOVER by H.Kubo 1997/12/24 */
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	MDM_G3DummyDataDetecting = 0;	/* 1997/12/25 */

	MDM_PhaseC_Status = RX_CONTINUE;	/**	フェーズＣステータスクリア	*/
	CodecPageStatus = CDC_READY;		/**	コーデックステータスクリア	*/
	MDM_TxStopSwFlag = 0;				/**	画データ送出ストップＳｗクリア	*/
	MDM_RTC_SeparateFlag = 0;			/**	ＥＣＭ受信ブロック間またがりフラグクリア	*/
	DecodeEcmFrameNum = 0;				/**	受信デコード済みフレーム番号クリア	*/
	EchoFCF = 0;						/**	エコーフレームクリア	*/
	GetCodecFlag = NO;					/**	コーデック獲得有無フラグクリア	*/
	CommunicateType = 0;				/**	交信種別クリア	*/

	MDM_CtsTurnOffFlag = 0;				/**  By O.K Feb.05,1996 **/
	MDM_CtsTurnOnFlag = 0;				/**  By O.K Feb.05,1996 **/
	MDM_CtsTurnOffCheckFlag = 0;		/**  By O.K Feb.05,1996 **/
	MDM_RlsdTurnOffFlag = 0;			/**  By O.K Feb.05,1996 **/
	MDM_RlsdTurnOnFlag = 0;				/**  By O.K Feb.05,1996 **/
	MDM_RlsdTurnOffCheckFlag = 0;		/**  By O.K Feb.05,1996 **/
	MDM_DmaStart = MDM_DMA_MASK;		/** 不正割り込み対策 By O.K Feb.14,1996 **/

	MDM_OldSecTxb = 0x00;				/*  By O.Kimoto 1996/02/28 */
	MDM_NewSecTxb = 0x00;				/*  By O.Kimoto 1996/02/28 */
	MDM_OldSecRxb = 0x00;				/*  By O.Kimoto 1996/02/28 */
	MDM_NewSecRxb = 0x00;				/*  By O.Kimoto 1996/02/28 */

	MDM_OldDtrStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_NewDtrStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_OldRlsdStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_NewRlsdStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_OldCtsStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_NewCtsStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_OldRtsStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_NewRtsStatus = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_OldT30Status = 0x00;			/*  By O.Kimoto 1996/02/28 */
	MDM_NewT30Status = 0x00;			/*  By O.Kimoto 1996/02/28 */

	MDM_OldFedStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_NewFedStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_OldPndetStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_NewPndetStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_OldPnsucStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_NewPnsucStatus = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_OldDmy4Status = 0x00;			/*  By O.Kimoto 1996/12/20 */
	MDM_NewDmy4Status = 0x00;			/*  By O.Kimoto 1996/12/20 */

#if 0	/* 1999/7/1 Y.M 移動 */
	MDM_ModemInternalStatusTimer = (unsigned long)(0); 	/*  by O.Kimoto 1996/04/11 */

	CMN_MemorySet((UBYTE  *)&MDM_InternalStatus[0],(UWORD)(sizeof(struct	ModemInternalStatusTable_def)*MODEM_STATUS_TABLE_MAX),0xFF);	/** モデム内部遷移ステータステーブル初期化 **/
	CMN_MemorySet((UBYTE  *)&MDM_InternalStatus[0],(UWORD)(sizeof(struct	ModemInternalStatusTable_def)*2),0x00);	/** モデム内部遷移ステータステーブル初期 **/
	MDM_InternalStatus[1].Tx_Phase = 0xFF;
	MDM_InternalStatus[1].Rx_Phase = 0xFF;
	MDM_InternalStatus[0].Tx_Phase = SYS_ModemVersion;	/* ﾓﾃﾞﾑﾊﾞｰｼﾞｮﾝはPower ON時ﾒｲﾝでｾｯﾄ */
#endif
	MDM_ModemInternalStatusCounter = MODEM_STATUS_TABLE_MAX;

	MDM_RetrainFirstCCTrainFlag = 0;	/*  By O.Kimoto 1996/08/14 */
	MDM_CarrierDropoutTimer = 0;	/* キャリアがなくなった事を計測するタイマー By O.Kimoto 1996/09/10 */
	MDM_CarrierDropoutFlag = 0xff;	/* キャリアがなくなった事を示すフラグ By O.Kimoto 1996/09/10 */
	MDM_FedOffFlag = 0;	/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */

	MDM_PixStartFlag = 0;			/* For Control RTDIS By O.Kimoto 1996/12/09 */
	MDM_AlreadyRtdisSetFlag = 0;	/* For Control RTDIS By O.Kimoto 1996/12/09 */

	HighSpeedCheckFlag = 0;
	EchoFrameRcvFlag = 0;
	MDM_NoCarryOrErrorCount = 0;	/* EOL又はｴﾗｰがあったﾌﾞﾛｯｸ(G3) 1997/01/31 Y.Murata */
	MDM_CurrentTotalErrorLine = 0;	/* 1997/01/31 Y.Murata */
	MDM_FskModeFlag = 0;			/* 1997/02/06 Y.Murata */

	modem_register_data_ptr = &MDM_REG_00_PortStatus;

	for (i=0;i<0x20;i++) {
		*(modem_register_data_ptr + i) = 0x00;
	}

	MDM_DSP_RAM_0B3_Status = 0;
	MDM_DSP_RAM_10D_Status = 0;
	MDM_DSP_RAM_13F_Status = 0;
	MDM_DSP_RAM_32A_Status = 0;
	MDM_DSP_RAM_031_Status = 0;
	MDM_DSP_RAM_38F_Status = 0;
	MDM_DSP_RAM_3DF_Status = 0;
	MDM_DSP_RAM_C0E_Status = 0;
	MDM_DSP_RAM_3A5_Status = 0;		/* 1996/02/24 Y.M */

	for (i = 0; i < 3 ; i ++) {
		MDM_V8_StatusStatus[3] = 0;
	}

	for (i = 0; i < 7 ; i ++) {
		MDM_V8_ControlStatus[7] = 0;
	}

	for (i = 0; i < 4 ; i ++) {
		EQMAveragingBuffer[4] = 0;
	}

	MDM_SymbolRate = 0;

	for (i = 0; i < 16 ; i ++) {
		ARAThresholdBuffer[16] = 0;
	}

	MDM_AbortCode = 0;
	ControlChannelRetrainFlag = 0;	/* CC Retrain By O.Kimoto 1996/05/16 */
	
	MDM_EQM_Value = 0;	/* Add for EQM By O.Kimoto 1996/02/22 */

	if (SYB_MaintenanceSwitch[MNT_SW_D7] & MDM_R288F_HARD_RESET) { /* メンテナンススイッチ D7-7 を見る */
		MDM_ModemHardwareReset();
	}
	else {
		/*
		** ソフトウェアリセット
		*/
		MDM_SetIO(POS_SFRES,ON);
		MDM_SetIO(POS_NEWC,ON);
	}
	wai_tsk(400/10);

#if (0)
//	if (DBG_IO) {	/* For I/O Debug 1999/02/22 by K.Okada */
//		while(DBG_IO == (UBYTE)1) {
//			ret = MDM_GetIO(POS_CONF);
//			MDM_SetIO(POS_NEWC,ON);
//			ret = MDM_GetIO(POS_NEWS);
//		}
//		while(DBG_IO == (UBYTE)2) {
//			ret = DspRamAccessReadMethod1(Address);
//			DspRamAccessWriteMethod1( Address, BData, BMaskData );
//			ret = DspRamAccessReadMethod1(Address);
//		}
//		while(DBG_IO == (UBYTE)3) {
//			retw = DspRamAccessReadMethod2( Address,Address2 );
//			DspRamAccessWriteMethod2(Address, Address2, WData, WMaskData);
//			retw = DspRamAccessReadMethod2( Address,Address2 );
//		}
//		while(DBG_IO == (UBYTE)4) {
//			retw = DspRamAccessReadMethod3(Address);
//			DspRamAccessWriteMethod3( Address, WData, WMaskData );
//			retw = DspRamAccessReadMethod3(Address);
//		}
//		while(DBG_IO == (UBYTE)5) {
//			retw = DspRamAccessReadMethod4(Address);
//		}
//	}
#endif

	/* 
	** モデム内部ステータスの取り込み開始をここではなくて、
	** モデムリセット後に移動します。
	** by O.Kimoto 1998/11/28
	*/
	MDM_ModemInternalStatusTimer = (unsigned long)(0); 	/*  by O.Kimoto 1996/04/11 */

	CMN_MemorySet((UBYTE  *)&MDM_InternalStatus[0],(UWORD)(sizeof(struct	ModemInternalStatusTable_def)*MODEM_STATUS_TABLE_MAX),0xFF);	/** モデム内部遷移ステータステーブル初期化 **/
	CMN_MemorySet((UBYTE  *)&MDM_InternalStatus[0],(UWORD)(sizeof(struct	ModemInternalStatusTable_def)*2),0x00);	/** モデム内部遷移ステータステーブル初期 **/
	MDM_InternalStatus[1].Tx_Phase = 0xFF;
	MDM_InternalStatus[1].Rx_Phase = 0xFF;
	MDM_InternalStatus[0].Tx_Phase = SYS_ModemVersion;	/* ﾓﾃﾞﾑﾊﾞｰｼﾞｮﾝはPower ON時ﾒｲﾝでｾｯﾄ */

	MDM_ModemInternalStatusCounter = 1;

	/** ＲＩＦＰのソースからコピー By O.Kimoto 1996/07/15 **/
	MDM_SetIO(POS_NSIE,OFF);               /* turn off NEWS interrupt */
	MDM_SetIO(POS_NCIE,OFF);               /* turn off NEWC interrupt */
	MDM_SetIO(POS_RDBIE,OFF);              /* turn off RX Data Buffer Full interrupt */
	MDM_SetIO(POS_TDBIE,OFF);              /* turn off TX Data Buffer Empty interrupt */
	outp(MDM_REG_1B_PORT,0x00);
	MDM_SetIO(POS_EQFZ,OFF);

	/** 割り込みマスクレジスターのセットアップ **/
#ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	MDM_SetMaskingRegsiter01(0x00);
	MDM_SetMaskingRegsiter0A(0x5B);		/* FLAGDT,FE,OE,FLAGS,SYNCD */
	MDM_SetMaskingRegsiter0B(0x10);		/* ATV25 */
	MDM_SetMaskingRegsiter0C(0x00);
	MDM_SetMaskingRegsiter0D(0x40);		/* PNDET */
	MDM_SetMaskingRegsiter0E(0x00);
	MDM_SetMaskingRegsiter0F(0xC0);		/* RLSD,FED */
	MDM_SetMaskingRegsiter12(FALSE);	/** CONF Register Interrupt Disable **/
	MDM_SetMaskingRegsiter14(0x00);
	MDM_SetMaskingRegsiter16(0x00);
	MDM_SetMaskingRegsiter17(0x00);
	MDM_SetMaskingRegsiter1A(0x00);
	MDM_SetMaskingRegsiter1B(0x00);
	MDM_SetMemAccMaskingRegsiter(TRUE);		/** MemoryAccessInterrupt disable **/
#else
	MDM_SetMaskingRegsiter01(0x00);
	MDM_SetMaskingRegsiter0A0B(0x1043);				/** ATV25/FLAGDT,FLAGS,SYNCD **/
	MDM_SetMaskingRegsiter0C0D(0x8000);				/** P2DET,PNDET **/
	MDM_SetMaskingRegsiter0E0F(0xC000);				/** RLSD,FED **/
	MDM_SetMaskingRegsiter12(TRUE);			/** CONF Register Interrupt Disable **/ /* Changed by H. Kubo 1997/06/23 */
	MDM_SetMaskingRegsiter14(0x00);
	MDM_SetMaskingRegsiter16(0x00);
	MDM_SetMaskingRegsiter17(0x00);
	MDM_SetMaskingRegsiter1A1B(0x0000);
	MDM_SetMemAccMaskingRegsiter(TRUE);		/** MemoryAccessInterrupt disable **/
#endif

	MDM_SetIO(POS_DMAE,ON);	/** ﾛｯｸｳｪﾙ北爪氏から情報でﾓﾃﾞﾑﾘｾｯﾄ直後にONした後は触らない様に By O.K Feb.05,1996 **/

if (INT_DEBUG == 0) {	/* for DEBUG by O.Kimoto 1998/02/02 */
	MDM_SetIO(POS_NSIE,ON);
}
	/*------------------------------*/
	/* モデムのポートを初期化します */
	/*------------------------------*/	/* 1996/02/26 Y.M */
	MDM_SetIO(POS_DTR, OFF);		/* Data Terminal Ready */
	MDM_SetIO(POS_DATA, OFF);		/* Data */

	/*------------------------------------------------*/
	/* コンフィギュをＦＳＫ／ＤＴＭＦ受信に設定します */
	/*------------------------------------------------*/
	MDM_InitialConfig();	/* test 1997/01/30 Y.Murata */

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* added by H.Kubo 1999/06/25  */
	/* V29 9600bps 受信対策用。 by H.Kubo 1999/06/25 */
	MDM_CurrentFilterType = 0xff; /* フィル未設定 */
#endif

	/*
	** 無音検出等によりフィルタが再設定された時、
	** ＦＳＫが取れなくなる可能性があります
	*/
	MDM_FilterSet(FSK_FILTER);	/* フィルタ、受信レベルの設定 */

	/*-------------------*/
	/** 送信レベルの設定 */
	/*-------------------*/
	/*
	** PartnerAbility1   (B1のコピー) 通信のイニシャルでセット
	*/
	MDM_TransmitLevelSet((UBYTE) FCM_PtnrChk_T23Attenation()); /* Changed by H.Kubo 1997/11/05 */
	ModemBlock.TxAttenuation = FCM_PtnrChk_T23Attenation(); /** アッテネータレベル設定	*/

	/*------------------*/
	/* 受信レベルの設定 */
	/*------------------*/
	MDM_ReceiveLevelSet();

#if 0	/* 1999/12/28 Y.Murata SET_RTH_LEVEL */
	/*
	** Ｒ６７１３－２２Ｐ対応 By O.Kimoto 1997/07/03
	** 22P 以降では、DCS のレベルを測って、
	** 高速信号受信のアッテネータを設定してはいけない。
	** Ported from CLOVER by H.Kubo 1997/10/27
	*/
	if ((SYS_ModemVersion == MDM_L6713_14P) || (SYS_ModemVersion == MDM_L6713_20P)) {
		MDM_FirstV21Ch2FlagReceive = 1;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
	}
	else {
		MDM_FirstV21Ch2FlagReceive = 0;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
	}
#endif

	/* 1999/12/28 Y.Murata SET_RTH_LEVEL
	 * レベルを測定して、ＲＴＨを制御します。
	*/
	MDM_FirstV21Ch2FlagReceive = 1;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */


	MDM_ReceiveLevelExtension = 0;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
	MDM_V21MeasureReceiveLevel = 0;
	MDM_V21MeasureStartGo = 0;

	MDM_TrueConfValue = 0;	/* Add by O.Kimoto 1997/12/02 */

	MDM_V34_CC_RetrainTimeCutFlag = 0; /* Ported from Clover by H.Kubo 1998/02/03 */

if (INT_DEBUG == 1) {	/* for DEBUG by O.Kimoto 1998/02/02 */
	MDM_SetIO(POS_NSIE,ON);
}
#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
	MDM_ModemDmaSize = MODEM_DMA_SIZE; /* 受信時データを DMA でモデムバッファに一度に転送するバイト数 */
	MDM_ModemBufferFirstPoint = 0;     /* モデムバッファの先頭のインデックス。 MDM_ModemBufferFirstPoint,..., 6,7 番のモデムバッファを使う */
#endif
	
	IsMemoryOpen = 0; /* メモリオープン済みかどうか 1998/05/15 by T.Soneoka */

	/*
	** added by H.Kubo 1998/09/25
	*/
	MDM_ND_WaitFirstDataEvent = FALSE;
	tskno_V23RlsdTimer = 0xffff;			/* added by H.Kubo 1998/11/11 */
	MDM_V23_ModemRecoverRunning = FALSE;	/* added by H.Kubo 1998/11/11 */

	MDM_MemReadStatus = 0;

#if (PRO_PRINT_TYPE == THERMAL_TRANS ) || (PRO_PRINT_TYPE == THERMAL )	/*  プリントデコード停止要求フラグ By H.Kubo  1998/10/26 */
	/* ported for HINOKI2 2002/01/07 T.Takagi */
	SYS_PRN_StopRequestFromModem = FALSE;
#endif

	/*
	** R288Fバージョン24P以上のとき
	** by H.Kubo 1998/10/30
	*/
 	MDM_PreviousPCOFF_Status = 0;
 	
	/*
	** フレーム間フラグが短くてモデムがフラグを取り逃がしたときの救済用。
	** H.Kubo 1999/01/22
	*/
	MDM_EcmRxFcsCheckRequest = 0;

	/* 松下 Ｂ－５６がＣＩを検出しないため、Ｔ．１．１エラーが必ず発生する。
	** よって、その防御策として、ＣＩ送出回数を限定する。
	** By O.Kimoto 1999/03/11
	*/
	FCM_CI_TransmitCount = 0;

	BackUpDataLength = 0;	/* 64KB以上のバックアップRAMデータ送信に対応 1999/04/29 by K.Okada */

	/** 受信３Ｍオーバチェック処理用 by H.Kubo 1999/09/14 */
	Rx3mErrorLine = DECODE_MAX_LINE;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
	MDM_EcmBufferOverEncodeStop = 0;
	MDM_2ndEcmBufferReamin = 0;
	MDM_EcmRemainCount = 0;
	MDM_RTC_DetectStatusStopReq = 0;
#endif

/* #if defined(POPLAR_F) *//* 1999/11/6 M.Matsumoto */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	/* ﾀｽｸID初期化 */
	tskid_VoiceTimeUpTask = 0xFFFF;
	tskid_NAR_DetectTask = 0xFFFF;
	
	/* 音声LSI 初期化 */
	MDM_AnswerLSI_Initialize();

	BackUpCodecPageStatus = 0xFF;

	/*-------------------------------------------------
	** （NTT TEL/FAXで擬似RBT鳴動したままとなる対策）
	** 2001/11/30 M.Matsumoto
	** add by O.Kimoto 2002/11/14
	*/
	MDM_IsSingleToneON = 0;


 #endif
#endif

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P)
	/* FM336とFM336Plusとで「Forced Train Mode」の初期値が違うことが判明した。
	** FM336=0(Disable) FM336Plus=1(Enable)
	** 高速データ受信後にPNSUCが落ちない件がこれに起因するかどうか不明だが、
	** 同一ROMでモデムをFM336PlusからFM336に付け替えるだけで現象が出なくなるので
	** モデム内部の設定をあわせるためにモデムの初期化時に強制的にこのビットを落とすこととする
	** By O.Kimoto 2003/01/08
	*/
	if ((SYS_MemorySwitch[35] & 0x02) == 0x02) {	/* MemorySwitch D5:0 */
		DspRamAccessWriteMethod1(0x6CC, 0x00, 0xF7);
	}
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	BackupReceiveLevel = DspRamAccessReadMethod3(0x0B3C);
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/16 石橋正和 */
	MDM_SetIO(POS_TPDM, ON);
	MDM_SetIO(POS_HDLC, OFF);
	SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
#endif
}


/*************************************************************************
	module		:[モデムコンフィグ]
	function	:[
		1.各コントロールエリア初期化（ゼロクロス以外）
		2.Ｖ１７の時：モデム制御ブロックに従いトレーニング種別を設定する
		, 　　　　　　受信モードならイコライザ係数補正有りとする
		3.Ｖ２９／Ｖ３３の時：メモリＳＷに従い、ＥＰトーン設定する
		4.スピードの設定
		5.送信モードの時：減衰歪補正用内臓ケーブルイコライザフィルタ設定
		, 　　　　　　　　ＲＴＳ　ＯＮする
		6.受信モードの時：キャリア検出レベルを設定
		, 群遅延イコライザフィルタの選択
		, 減衰歪補正用内臓ケーブルイコライザフィルタ設定
		, ＳＩＯリセットキーをＯＮする
		7.コンフィグＢｉｔをＯＮする
		8.送信モードの時：ＣＴＳ　ＯＮチェック
		9.トレリス特殊対応（参考ＧＡＬＡＸＹ）
	]
	return		:[]
	common		:[
		ModemHigh
		ModemBlock
		PartnerAbility0
		]
	condition	:[]
	comment		:[]
	date		:[1994/01/07]
	update		:[1996/02/29]
	author		:[曽根岡拓、木元修]
*************************************************************************/
UBYTE secrxb = 0;		/* Alternative Workaround #2 By O.Kimoto 1996/07/26 */
UBYTE address_3dd = 0;	/* Alternative Workaround #2 By O.Kimoto 1996/07/26 */
UBYTE loop_flag = 0;	/* Alternative Workaround #2 By O.Kimoto 1996/07/26 */
UWORD	tmoutc = 0;	/** Debug **/
UWORD	RlsdOffCurrentValue = 0;	/* Add By O.Kimoto 1996/12/04 */

void  ModemConfig(UBYTE direction)
{
	UWORD	timer30sec;	/*  By O.Kimoto 1996/09/10 */
	UWORD	judge_time;	/*  By O.Kimoto 1996/09/13 */
	UBYTE	debug_fifo;

	debug_fifo = 0;

	/*
	** V17:12000
	** V33:12000
	** V27:4800
	** V27:2400
	** の時はCEQ=1にするべきかも tx level are slightly hight with CEQ ON.
	*/

	switch (ModemBlock.Type) {	/** モデム種別	*/
	case TYPE_V8:	/** モデム種別がＶ８の時	*/
		break;
	case TYPE_V34:	/** モデム種別がＶ３４の時	*/
		break;
	case TYPE_V17:	/** モデム種別がＶ１７の時	*/

		MDM_SetIO(POS_CEQ,OFF);		/* CEQ should be turned off for V21,V17,V29 Modes. 1996/10/17 Y.Murata */

		if (direction == WRITE_MODE) {	/**	送信モードの時	*/
			MDM_SetIO(POS_EPT,ON);
		}
		else {
			MDM_SetIO(POS_EPT,OFF);
		}

		if ((ModemBlock.Training == TRAINING_SHORT) 	/** ショートトレーニングモードの時	*/
			&& (direction == WRITE_MODE)) {	/**	送信モードの時	*/
			MDM_SetIO(POS_STRN,ON);	/**	コマンドレジスタ１をショートトレーニング設定	*/
		}
		break;
	case TYPE_V33:	/** モデム種別がＶ３３の時	*/

		MDM_SetIO(POS_CEQ,OFF);		/* CEQ should be turned off for V21,V17,V29 Modes. 1996/10/17 Y.Murata *//* Add By O.Kimoto 1997/02/25 */

		if (direction == WRITE_MODE) {	/**	送信モードの時	*/
			if (CHK_V29EPtoneAvailable()) {	/**	ＥＰトーン送出有効の時	*/
				MDM_SetIO(POS_EPT,ON);
			}
			else {
				MDM_SetIO(POS_EPT,OFF);
			}
		}
		break;
	case TYPE_V29:	/**	モデム種別がＶ２９の時	*/
		MDM_SetIO(POS_STRN,OFF);
		MDM_SetIO(POS_CEQ,OFF);		/* CEQ should be turned off for V21,V17,V29 Modes. 1996/10/17 Y.Murata */
		if (direction == WRITE_MODE) {	/**	送信モードの時	*/
		 	if (CHK_V29EPtoneAvailable()) {	/**	ＥＰトーン送出有効の時	*/
				MDM_SetIO(POS_EPT,ON);
			}
			else {
				MDM_SetIO(POS_EPT,OFF);
			}
		}
		break;
	case TYPE_V27:	/**	モデム種別がＶ２７の時	*/
		MDM_SetIO(POS_STRN,OFF);
		if (direction == WRITE_MODE) {	/**	送信モードの時	*/
			MDM_SetIO(POS_EPT,ON);
		}
		else {
			MDM_SetIO(POS_EPT,OFF);
		}
		break;
	case TYPE_FSK:	/** モデム種別がＦＳＫモードの時	*/
		/*MDM_SetIO(POS_CEQ,OFF); 1997/02/05*/		/* CEQ should be turned off for V21,V17,V29 Modes. 1996/10/17 Y.Murata */
		MDM_SetIO(POS_RTDIS,OFF);	/* Add By O.Kimoto 1996/11/28 */
		break;
	/*
	** ナンバーディスプレイ */ /* added by H.Kubo 1998/06/23
	*/
	case TYPE_V23:
		MDM_SetIO(POS_CEQ,OFF);		/* CEQ should be turned off */
		break;

	default:																	/* 拡張用					*/
		break;
	}

	/* Ｔ．３０ Ｂａｓｅならば */
	if (!(SYS_V34ProcedureExecuting())) {

		switch(ModemBlock.Mode) {
		case MODE_TX_FSK:	/**	低速、送信、ＨＤＬＣモード	*/
			MDM_FskConfig(1);
			break;

		case MODE_TX_ECM:	/**	高速、送信、ＨＤＬＣモード	*/
			MDM_HighSpeedConfig((UBYTE)1,(UBYTE)1);
			break;

		case MODE_TX_G3:	/**	高速、送信、ｎｏｎ＿ＨＤＬＣモード	*/
			MDM_HighSpeedConfig((UBYTE)1,(UBYTE)0);
			break;

		case MODE_TX_TCF:	/**	高速、送信、ｎｏｎ＿ＨＤＬＣモード	*/
			MDM_HighSpeedConfig((UBYTE)1,(UBYTE)0);
			break;

		case MODE_RX_FSK:	/**	低速、受信、ＨＤＬＣモード	*/
			MDM_FskConfig(0);
			break;

		case MODE_RX_ECM:	/**	高速、受信、ＨＤＬＣモード	*/
			MDM_SetReceiveLevelExtension(1);
			break;

		case MODE_RX_G3:	/**	高速、受信、ｎｏｎ＿ＨＤＬＣモード	*/
		case MODE_RX_TCF:	/**	高速、受信、ｎｏｎ＿ＨＤＬＣモード	*/
			MDM_SetReceiveLevelExtension(0);
			break;
		/*
		** ナンバーディスプレイ added by H.Kubo 1998/06/23
		*/
		case MODE_RX_ND: 	/** ナンバーディスプレイ */
			MDM_V23Config(0);
			break;
		case MODE_TX_ND:
			MDM_V23Config(1);
			break;

		}
	}

	if (direction == WRITE_MODE) {
		MDM_SetTxFIFOClear();
	}
	else {
		MDM_SetRxFIFOClear();
	}

	if (direction == WRITE_MODE) {
		MDM_SetIO(POS_TXSQ, OFF); /* 送信スケルチを OFF にします。 by H.Kubo 1998/11/14 */
	}
	else {

		/*
		** V17以下で処理が間に合わず、アイがひらきません
		** by H.Hirao 1998/12/02
		*/
			/*
			** CMN_DisableInterrupt();	For DEBUG By O.Kimoto 1998/01/16
			*/
		while (inp(MDM_REG_1E_PORT) & IO_BIT_RDBF) {
			inp(MDM_REG_00_PORT);
			/* wai_oneshot(1); */	/* for DEBUG by O.Kimoto 1998/01/17 */
		}

		/*
		** ＲＩＦＰのソースからコピー By O.Kimoto 1996/07/16
		*/
		MDM_SetIO(POS_PE, OFF);
		MDM_SetIO(POS_FE, OFF);
		MDM_SetIO(POS_OE, OFF);
		MDM_SetIO(POS_SYNCD, OFF);

		/*
		** CMN_EnableInterrupt();	For DEBUG By O.Kimoto 1998/01/16
		*/
	}

	/*
	** For PNSUC Debug By O.Kimoto 1996/05/13
	*/
	MDM_SetIO(POS_PNSUC,OFF);

	/* チャンネル切り替え時のキャリア断検出用フラグをセット By O.Kimoto 1996/09/10 */
	MDM_CarrierDropoutFlag = 0;	/* キャリアがなくなった事を示すフラグ By O.Kimoto 1996/09/10 */
	MDM_CarrierDropoutTimer = 0;	/* キャリアがなくなった事を計測するタイマー By O.Kimoto 1996/09/10 */
	MDM_FedOffFlag = 0;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */

	if ((direction == WRITE_MODE) && (ModemBlock.Type <= TYPE_FSK)) {
#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
		if ((FCM_S1_Scramble != TRUE) || (ModemBlock.Type == TYPE_FSK)) { /* スクランブル通信でない場合 */
			CTS_Check();	/** ＣＴＳチェック	*/
		}
		
		
		
		if (FCM_S1_Scramble == TRUE) {
			if ((ModemBlock.Mode == MODE_TX_TCF) || (ModemBlock.Mode == MODE_TX_G3)) {
				if (DBG_G3_TCF_OriginalPosition == 1) {
					CTS_Check();	/** ＣＴＳチェック	*/
				}
			}
			if ((ModemBlock.Mode == MODE_TX_ECM) && (DBG_ECM_OriginalPosition == 1)) {
				CTS_Check();	/** ＣＴＳチェック	*/
			}
		}
		
		
		
#else
		CTS_Check();	/** ＣＴＳチェック	*/
#endif

		/** Debug **/
		if (MDM_ClearToSendAbort != TRUE) {	/* Abort Process By O.Kimoto 1996/08/07 */
			if (ModemBlock.Mode == MODE_TX_FSK) {
				/** コントロールチャンネルのリトレイン対応 For Debug */
				tmoutc = 0;
				timer30sec = 0;	/*  By O.Kimoto 1996/09/10 */

				if (SYS_V34ProcedureExecuting()) {

					judge_time = 30000/10;	/* 30sec By O.Kimoto 1996/09/13 */
					while((MDM_GetIO(POS_SECRXB) != 0x84)) {
						wai_tsk(10/10);	/*  By O.K Feb.22,1996 */
						tmoutc++;	/**	ＣＴＳチェックタイムアウトカウンタインクリメント	*/
						timer30sec ++;	/*  By O.Kimoto 1996/09/10 */

						/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
						** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
						** レインが発生していれば、フラグをセットします。
						** By O.Kimoto 1996/08/14 **/
						if (MDM_RetrainFirstCCTrainFlag == 1) {
							MDM_RetrainFirstCCTrainFlag = 0;
							tmoutc = 0;
						}

						/* ２ｎｄＣＣでリトレインが発生した場合 By O.Kimoto 1996/09/04 */
						if (ControlChannelRetrainFlag == 1) {
							ControlChannelRetrainFlag = 0;
							tmoutc = 0;
						}

						if ((tmoutc >= judge_time) 	/**	ＣＴＳチェックタイムアウトカウンタが５００の時（５秒）	*/
							|| (timer30sec >= 30000/10)	/*  By O.Kimoto 1996/09/10 */
							|| (MDM_FedOffFlag == 1)
							|| (MDM_FedOffFlag == 2)) {	/*  By O.Kimoto 1996/09/21 */
							MDM_ClearToSendAbort = TRUE;
							MDM_CarrierDropoutFlag = 0xff;	/*  By O.Kimoto 1996/09/10 */
							break;
						}
					}
				}

				
				if (SYS_V34ProcedureExecuting()) {
					judge_time = 30000/10;	/* 30sec By O.Kimoto 1996/09/13 */
				}
				else {
					judge_time = 5000/10;	/* 5sec By O.Kimoto 1996/09/13 */
				}

				tmoutc = 0;
				timer30sec = 0;	/*  By O.Kimoto 1996/09/10 */

				while(!MDM_GetIO(POS_FLAGS) || !MDM_GetIO(POS_TDBE)) {
					wai_tsk(10/10);	/*  By O.K Feb.22,1996 */
					tmoutc++;	/**	ＣＴＳチェックタイムアウトカウンタインクリメント	*/
					timer30sec ++;	/*  By O.Kimoto 1996/09/10 */

					/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
					** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
					** レインが発生していれば、フラグをセットします。
					** By O.Kimoto 1996/08/14 **/
					if (MDM_RetrainFirstCCTrainFlag == 1) {
						MDM_RetrainFirstCCTrainFlag = 0;
						tmoutc = 0;
					}

					/* ２ｎｄＣＣでリトレインが発生した場合 By O.Kimoto 1996/09/04 */
					if (ControlChannelRetrainFlag == 1) {
						ControlChannelRetrainFlag = 0;
						tmoutc = 0;
					}

					if ((tmoutc >= judge_time) 	/**	ＣＴＳチェックタイムアウトカウンタが５００の時（５秒）	*/
						|| (timer30sec >= 30000/10)	/*  By O.Kimoto 1996/09/10 */
						|| (MDM_FedOffFlag == 1)
						|| (MDM_FedOffFlag == 2)) {	/*  By O.Kimoto 1996/09/21 */
						MDM_ClearToSendAbort = TRUE;
						MDM_CarrierDropoutFlag = 0xff;	/*  By O.Kimoto 1996/09/10 */
						break;
					}
				}
			}
#if defined (KEISATSU) /* 警察FAX 05/09/08 石橋正和 */
			else if ((ModemBlock.Mode == MODE_TX_ECM) && (FCM_S1_Scramble == FALSE)) {
#else
			else if (ModemBlock.Mode == MODE_TX_ECM) {
#endif
				if (SYS_V34ProcedureExecuting()) {
					judge_time = 30000/10;	/* 30sec By O.Kimoto 1996/09/13 */
				}
				else {
					judge_time = 5000/10;	/* 5sec By O.Kimoto 1996/09/13 */
				}

				tmoutc = 0;
				timer30sec = 0;	/*  By O.Kimoto 1996/09/10 */
				while(!MDM_GetIO(POS_FLAGS) || !(MDM_GetIO(POS_TDBE))) {
					wai_tsk(1);	/*  By O.K Feb.22,1996 */
					tmoutc++;	/**	ＣＴＳチェックタイムアウトカウンタインクリメント	*/
					timer30sec ++;	/*  By O.Kimoto 1996/09/10 */

					/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
					** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
					** レインが発生していれば、フラグをセットします。
					** By O.Kimoto 1996/08/14 **/
					if (MDM_RetrainFirstCCTrainFlag == 1) {
						MDM_RetrainFirstCCTrainFlag = 0;
						tmoutc = 0;
					}

					/* ２ｎｄＣＣでリトレインが発生した場合 By O.Kimoto 1996/09/04 */
					if (ControlChannelRetrainFlag == 1) {
						ControlChannelRetrainFlag = 0;
						tmoutc = 0;
					}

					if ((tmoutc >= judge_time) 	/**	ＣＴＳチェックタイムアウトカウンタが５００の時（５秒）	*/
						|| (timer30sec >= 30000/10)	/*  By O.Kimoto 1996/09/10 */
						|| (MDM_FedOffFlag == 1)
						|| (MDM_FedOffFlag == 2)) {	/*  By O.Kimoto 1996/09/21 */
						MDM_ClearToSendAbort = TRUE;
						MDM_CarrierDropoutFlag = 0xff;	/*  By O.Kimoto 1996/09/10 */
						break;
					}
				}
			}

			/* 下記ウエイト処理は、基本的に、Ｖ．３４での対策である。
			** しかし、一抹の不安が残るので、下記のようにした。
			** 結果的には、
			**     Ｖ．３４時はすべて１１０ｍｓウエイト
			**     それ以外の時は画データ送信時のみ１１０ｍｓウエイト
			** となる。
			** by O.Kimoto 1997/03/06
			*/
			if (SYS_V34ProcedureExecuting()) {	/** Ｖ．３４ばらば */
				if (ModemBlock.Mode == MODE_TX_ECM) {
					wai_tsk(11);	/** ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ By O.K Feb.11,1996 **/
				}
				else {
					wai_tsk(11);	/** ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ By O.K Feb.11,1996 **/
				}
			}
			else {	/** Ｇ．３ならば */
				if ((ModemBlock.Mode == MODE_TX_TCF) || (ModemBlock.Mode == MODE_TX_FSK)) {
					/* 何もしない */
				}
				else if ((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3)) {
#if defined (KEISATSU) /* 警察FAX 05/05/26 石橋正和 */
					if (FCM_S1_Scramble == FALSE) { /* スクランブル通信でない場合 */
						wai_tsk(11);	/** ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ By O.K Feb.11,1996 **/
					}
#else
					wai_tsk(11);	/** ﾛｯｸｳｪﾙからのｱﾄﾞﾊﾞｲｽ By O.K Feb.11,1996 **/
#endif
				}
			}

		}
	}
	else if ((direction == READ_MODE) && (ModemBlock.Type <= TYPE_FSK)) {
		if (SYS_V34ProcedureExecuting()) {	/** Ｖ．３４ばらば */
			if (ModemBlock.Mode == MODE_RX_FSK ) {
				/** コントロールチャンネルのリトレイン対応 **/

				if (SYS_V34ProcedureExecuting()) {
					judge_time = 30000/10;	/* 30sec By O.Kimoto 1996/09/13 */
				}
				else {
					judge_time = 5000/10;	/* 5sec By O.Kimoto 1996/09/13 */
				}

				tmoutc = 0;
				timer30sec = 0;	/*  By O.Kimoto 1996/09/10 */
				while((MDM_GetIO(POS_SECRXB) != 0x84)) {
					wai_tsk(10/10);
					tmoutc++;
					timer30sec ++;	/*  By O.Kimoto 1996/09/10 */

					/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
					** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
					** レインが発生していれば、フラグをセットします。
					** By O.Kimoto 1996/08/14 **/
					if (MDM_RetrainFirstCCTrainFlag == 1) {
						MDM_RetrainFirstCCTrainFlag = 0;
						tmoutc = 0;
					}

					/* ２ｎｄＣＣでリトレインが発生した場合 By O.Kimoto 1996/09/04 */
					if (ControlChannelRetrainFlag == 1) {
						ControlChannelRetrainFlag = 0;
						tmoutc = 0;
					}

					if ((tmoutc >= judge_time) 	/**	ＣＴＳチェックタイムアウトカウンタが５００の時（５秒）	*/
						|| (timer30sec >= 30000/10)	/*  By O.Kimoto 1996/09/10 */
						|| (MDM_FedOffFlag == 1)
						|| (MDM_FedOffFlag == 2)) {	/*  By O.Kimoto 1996/09/21 */
						MDM_ClearToSendAbort = TRUE;
						MDM_CarrierDropoutFlag = 0xff;	/*  By O.Kimoto 1996/09/10 */
						break;
					}
				}
			}
			else if (ModemBlock.Mode == MODE_RX_ECM ) {
				;
			}
		}
	}
	tmoutc = 0;

#ifdef MDM_LOOP_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	/* 拡張FIFOは使わないので、アクセスしません。　初期値は拡張FIFO無効です。 */
#else
	/* 拡張FIFO モードによって設定を変えることにします。*/
 #if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if ((SYS_ModemVersion == MDM_L6713_26P)
	|| (SYS_ModemVersion >= MDM_L6719_12P_ES)) {
 #else
	if (SYS_ModemVersion == MDM_L6713_26P) {
 #endif
		switch (ModemBlock.Type) {	/** モデム種別	*/
		case TYPE_V34:	/** モデム種別がＶ３４の時	*/
		case TYPE_V17:	/** モデム種別がＶ１７の時	*/
		case TYPE_V33:	/** モデム種別がＶ３３の時	*/
		case TYPE_V29:	/**	モデム種別がＶ２９の時	*/
		case TYPE_V27:	/**	モデム種別がＶ２７の時	*/
			if (direction == READ_MODE) {
				if (ModemBlock.Mode == MODE_RX_ECM ){

					if (CHK_UNI_R288fExtendedRxEcmFIFO()) {
						MDM_EnableExtendedFIFO();
						MDM_EnableExtendedRxFIFO();
						/* MDM_SetCapacityOfExtendedRxFIFO(0xf0); */ /* FIFO のすべてを受信用に使う by H.Kubo 1998/10/05 */
					}
					else {
						MDM_DisableExtendedFIFO();
					}
				}
				else {
					if (CHK_UNI_R288fExtendedRxFIFO()) {
						MDM_EnableExtendedFIFO();
						MDM_EnableExtendedRxFIFO();
						/* MDM_SetCapacityOfExtendedRxFIFO(0xf0); */ /* FIFO のすべてを受信用に使う by H.Kubo 1998/10/05 */
					}
					else {
						MDM_DisableExtendedFIFO();
					}
				}
			}
			else {
				if (CHK_UNI_R288fExtendedTxFIFO()) {
					MDM_EnableExtendedTxFIFO();
					/* MDM_SetCapacityOfExtendedRxFIFO(0x0f); */ /* FIFO のすべてを送信用に使う by H.Kubo 1998/10/05 */
				}
				else {
					MDM_DisableExtendedFIFO();
					MDM_DisableExtendedTxFIFO(); /* 念のため入れます。by H.Kubo 1998/10/20 */
				}
			}
			break;
		default: /* V8, V21 ch2, V23, etc */
			MDM_DisableExtendedFIFO();
			break;
		}
	}
#endif

	if (debug_fifo) {
		if (direction == WRITE_MODE) {
			MDM_SetTxFIFOClear();
		}
		else {
			MDM_SetRxFIFOClear();
		}
	}
}


/*************************************************************************
	module		:[モデムクローズ]
	function	:[
		1.ＦＳＫ受信モデムモードでモデムクローズする
	]
	return		:[なし]
	common		:[
		ModemControl
	]
	condition	:[
		割り込み禁止状態で行う
	]
	comment		:[]
	date		:[1994/01/07]
	author		:[曽根岡拓]
*************************************************************************/
void  MDM_InitialConfig(void)
{
	ModemControl.Status = 0;	/**	モデムステータスクリア	*/

	if (!(SYS_V34ProcedureExecuting())) {
		if (MDM_GetIO(POS_CONF) != BPS300_V21) {
			if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
				MDM_SetIO(POS_CONF, BPS300_V21);
				MDM_SetIO(POS_TXSQ, ON);
				wai_oneshot(25);			/* Spike Noise Wait 23300usec MAX */

				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, V21_300_NEWC_TIME);
				MDM_SetIO(POS_TXSQ, OFF);
			}
			else {
				MDM_SetIO(POS_CONF, BPS300_V21);

				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, V21_300_NEWC_TIME);
			}
			MDM_FskModeFlag = 0;
		}
	}
}


/*************************************************************************
	module		:[ＣＴＳ　ＯＮ　チェック]
	function	:[
		1.ＣＴＳ　ＯＮするまで、タスクウェイトしながら待ちます
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/07]
	author		:[曽根岡拓]
*************************************************************************/
void  CTS_Check(void)
{
	UWORD	tmoutc;
	UWORD	timer30sec;	/*  By O.Kimoto 1996/09/10 */
	UWORD	judge_time;	/*  By O.Kimoto 1996/09/13 */
#if defined (KEISATSU) /* 警察FAX 05/07/22 石橋正和 */
	UBYTE cts;
#endif

	if (SYS_V34ProcedureExecuting()) {
		judge_time = 30000/10;	/* 30sec By O.Kimoto 1996/09/13 */
	}
	else {
		judge_time = 5000/10;	/* 5sec By O.Kimoto 1996/09/13 */
	}

	tmoutc = 0;	/*  By O.Kimoto 1996/09/13 */
	timer30sec = 0;	/*  By O.Kimoto 1996/09/10 */

	if (MDM_ClearToSendAbort == FALSE) {	/** Add By O.Kimoto 1996/08/08 **/
#if defined (KEISATSU) /* 警察FAX 05/07/22 石橋正和 */
		while(1) {
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				/* スクランブル通信の場合 */
				cts = S1_GetCTS();
			}
			else {
				cts = MDM_GetIO(POS_CTS);
			}
			if (cts) {
				break;
			}
			/**	ＣＴＳビットがＯＦＦの時	*/
#else
		while(!MDM_GetIO(POS_CTS)) {	/**	ＣＴＳビットがＯＦＦの時	*/
#endif
			wai_tsk(10/10); /** １０ｍｓウエイトします。 */
			tmoutc ++;	/**	ＣＴＳチェックタイムアウトカウンタインクリメント	*/
			timer30sec ++;	/*  By O.Kimoto 1996/09/10 */
			
			/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
			** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
			** レインが発生していれば、フラグをセットします。
			** By O.Kimoto 1996/08/14 **/
			if (MDM_RetrainFirstCCTrainFlag == 1) {
				MDM_RetrainFirstCCTrainFlag = 0;
				tmoutc = 0;
			}

			/* ２ｎｄＣＣでリトレインが発生した場合 By O.Kimoto 1996/09/04 */
			if (ControlChannelRetrainFlag == 1) {
				ControlChannelRetrainFlag = 0;
				tmoutc = 0;
			}
			
			if ((tmoutc >= judge_time) 	/**	ＣＴＳチェックタイムアウトカウンタが５００の時（５秒）	*/
				|| (timer30sec >= 30000/10)	/*  By O.Kimoto 1996/09/10 */
				|| (MDM_FedOffFlag == 1)
				|| (MDM_FedOffFlag == 2)) {	/*  By O.Kimoto 1996/09/21 */
				MDM_ClearToSendAbort = TRUE;
				MDM_CarrierDropoutFlag = 0xff;	/*  By O.Kimoto 1996/09/10 */
				break;
			}
		}
	}
}


/*************************************************************************
	module		:[イコライザ係数ＨＯＬＤ]
	function	:[
		1.Ｖ１７時、イコライザ係数をＨＯＬＤする
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	date		:[1994/01/07]
	author		:[曽根岡拓]
*************************************************************************/
void  EqualizerHoldOn(void)
{
	MDM_SetIO(POS_EQFZ,ON);
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[イコライザ係数ＨＯＬＤ解除]
//	function	:[
//		1.Ｖ１７時、イコライザ係数をＨＯＬＤを解除する
//	]
//	return		:[なし]
//	common		:[
//	]
//	condition	:[]
//	comment		:[]
//	date		:[1994/01/07]
//	author		:[曽根岡拓]
//*************************************************************************/
//void  EqualizerHoldOff(void)
//{
//	MDM_SetIO(POS_EQFZ,OFF);
//}
#endif

/*************************************************************************
	module		:[モデムドライバーＩ／Ｆブロック設定]
	function	:[
		1.交信スピードより、モデムタイプ及びスピードをセットする
	]
	return		:[なし]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void near ModemTypeSet(unsigned char ){}]
	date		:[1993/12/08]
	update		:[1995/12/12]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  ModemTypeSet(UBYTE uprate)	/*	通信速度	*/
{

	ModemBlock.Config = uprate;

	switch (uprate) {	/**	通信速度	*/
	case BPS33600_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_33600;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS31200_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_31200;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS28800_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_28800;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS26400_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_26400;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS24000_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type 	= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_24000;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS21600_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_21600;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS19200_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_19200;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS16800_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_16800;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS14400_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_14400;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS12000_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_12000;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS9600_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_9600;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS7200_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_7200;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS4800_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_4800;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS2400_V34:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V34;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_2400;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS14400_V17:	/**	Ｖ１７　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V17;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_14400;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		break;
	case BPS12000_V17:	/**	Ｖ１７　１２０００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V17;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_12000;	/**	モデムスピード１２０００ｂｐｓ設定	*/
		break;
	case BPS9600_V17:	/**	Ｖ１７　９６００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V17;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_9600;	/**	モデムスピード９６００ｂｐｓ設定	*/
		break;
	case BPS7200_V17:	/**	Ｖ１７　７２００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V17;	/**	モデムタイプ　Ｖ１７設定	*/
		ModemBlock.Speed	= SPEED_7200;	/**	モデムスピード７２００ｂｐｓ設定	*/
		break;
	case BPS14400_V33:	/**	Ｖ３３　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V33;	/**	モデムタイプ　Ｖ３３設定	*/
		ModemBlock.Speed	= SPEED_14400;	/**	モデムスピード１４４００ｂｐｓ設定	*/
		/*
		** R288F V33未対応のためV17にする 1997/03/18 Y.Murata
		*/
		ModemBlock.Config	= BPS14400_V17;
		break;
	case BPS12000_V33:	/**	Ｖ３３　１４４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V33;	/**	モデムタイプ　Ｖ３３設定	*/
		ModemBlock.Speed	= SPEED_12000;	/**	モデムスピード１２０００ｂｐｓ設定	*/
		/*
		** R288F V33未対応のためV17にする 1997/03/18 Y.Murata
		*/
		ModemBlock.Config	= BPS12000_V17;
		break;
	case BPS9600_V29:	/**	Ｖ２９　９６００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V29;	/**	モデムタイプ　Ｖ２９設定	*/
		ModemBlock.Speed	= SPEED_9600;	/**	モデムスピード９６００ｂｐｓ設定	*/
		break;
	case BPS7200_V29:	/**	Ｖ２９　７２００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V29;	/**	モデムタイプ　Ｖ２９設定	*/
		ModemBlock.Speed	= SPEED_7200;	/**	モデムスピード７２００ｂｐｓ設定	*/
		break;
	case BPS4800_V27:	/**	Ｖ２７　４８００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V27;	/**	モデムタイプ　Ｖ２７設定	*/
		ModemBlock.Speed	= SPEED_4800;	/**	モデムスピード４８００ｂｐｓ設定	*/
		break;
	case BPS2400_V27:	/**	Ｖ２７　２４００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V27;	/**	モデムタイプ　Ｖ２７設定	*/
		ModemBlock.Speed	= SPEED_2400;	/**	モデムスピード２４００ｂｐｓ設定	*/
		break;
	/*
	** added by H.Kubo 1998/06/23
	*/
	case RX1200_V23:	/**	Ｖ２３　１２００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V23;	/**	モデムタイプ　Ｖ２３設定	*/
		ModemBlock.Speed	= SPEED_1200;	/**	モデムスピード１２００ｂｐｓ設定	*/
		ModemBlock.Config 	= TX1200_V23;	/* なぜか受信のときも送信と同じ設定にするようロックウェルから指示があった。 by H.Kubo 1998/09/02 */
		break;
	case TX1200_V23:	/**	Ｖ２３　１２００ｂｐｓの時	*/
		ModemBlock.Type		= TYPE_V23;	/**	モデムタイプ　Ｖ２３設定	*/
		ModemBlock.Speed	= SPEED_1200;	/**	モデムスピード１２００ｂｐｓ設定	*/
		break;

	case BPS300_V21:	/**	Ｖ２１　３００ｂｐｓの時	*/
	default:
		ModemBlock.Type		= TYPE_FSK;	/**	モデムタイプ　ＦＳＫ設定	*/
		ModemBlock.Speed	= SPEED_300;	/**	モデムスピード３００ｂｐｓ設定	*/
		break;
	}
}

/******************************************************************************
	module		:[モデムの送信レベルの設定]
	function	:[
		1. モデムのTXLOSSをセットします
		2. 送信レベルをセットします
	]
	return		:[なし]
	common		:[
		MDM_TxLevelSaveValue
	]
	date		:[1993/11/29]
	update		:[1996/03/13]
	author		:[橘正樹、木元修]
******************************************************************************/
void  MDM_TransmitLevelSet(		/* near->far 1997/02/08 Y.Murata */
	UBYTE level)	/* 設定する送出レベル */
{
	UBYTE level_value;
	
	level_value = (UBYTE)(level * 0x10);	/** 設定する値を換算します **/
	MDM_TxLossSet(level_value);	/** 送信レベル設定 **/

	/*MDM_TxLevelSaveValue = level; 1996/03/18 Y.M */ /** 送信レベルをセーブします **/
	MDM_TxLevelSaveValue = level_value;	/** 設定する値を換算し送信レベルをセーブします **/
}


/*************************************************************************
	module		:[モデムをソフトリセットする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/02/24]
	author		:[村田]
*************************************************************************/
void  MDM_ModemSoftReset(void)
{
	MDM_SetIO(POS_SFRES,ON);
	MDM_SetIO(POS_NEWC,ON);
	wai_tsk(400/10);			/* 400ms */

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* Naganoより移植 O.Oshima 2003/10/07 */
	/* 2001/02/06 Y.Murata
	 * 初期化抜け。FAX/TEL待機で受信した後、ANS/FAX待機でCNG検出ができない不具合。海外仕様全滅
	*/
	MDM_CurrentFilterType = 0xff; /* フィルタ未設定 */
#endif

}

/*************************************************************************
	module		:[Clear Tsk No Buffers]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1996/07/27]
	author		:[木元修]
*************************************************************************/
void 	MDM_ClearTskNoBuffer(void)
{
	tskno_MDM_ScanTx				= 0xFFFF;
	tskno_MDM_MemoryTx				= 0xFFFF;
	tskno_MDM_CharTx				= 0xFFFF;
	tskno_MDM_EcmRxPrint			= 0xFFFF;
	tskno_MDM_EcmRxMemory			= 0xFFFF;
	tskno_MDM_Print					= 0xFFFF;
	tskno_TxFskControl				= 0xFFFF;
	tskno_ModemInterrupt			= 0xFFFF;
	tskno_ModemDMA_TC_Detect		= 0xFFFF;
	
	tskno_RxFrameControl			= 0xFFFF;
	tskno_T3_Timer					= 0xFFFF;
	tskno_T1_Timer					= 0xFFFF;
	tskno_Bell						= 0xFFFF;
	tskno_ModemStatusCheck			= 0xFFFF;
	tskno_RxFlagDetect				= 0xFFFF;
	tskno_Timer1					= 0xFFFF;
	tskno_Timer2					= 0xFFFF;
	tskno_TimerEqz					= 0xFFFF;
	
	tskno_RxPixControl				= 0xFFFF;
	tskno_RxEcmControl				= 0xFFFF;
	tskno_DMA_TC_Detect				= 0xFFFF;
	tskno_FlagDetect				= 0xFFFF;
	tskno_FcsDetect					= 0xFFFF;
	tskno_RxDeviceWriteControl		= 0xFFFF;
	tskno_DecodeDMA_End				= 0xFFFF;
	tskno_DecodeTimer				= 0xFFFF;
	tskno_EyeQualityMonitor			= 0xFFFF;
	
	tskno_EncodeDMA_End				= 0xFFFF;
	tskno_CDC_MTxCodeConvertTask	= 0xFFFF;
	tskno_CDC_CTxCodeConvertTask	= 0xFFFF;
	tskno_MTxReadDMA_Task			= 0xFFFF;
/*	tskno_CDC_EncodePageTask		= 0xFFFF; 蓄積中に通信が走ると蓄積タスク終了できないくなるので移動します 1998/02/06 by T.Soneoka */
	
	tskno_TimerTCF_End				= 0xFFFF;
	tskno_TimerEYE_Q				= 0xFFFF;
	tskno_TimerTCF					= 0xFFFF;
	tskno_TimerTCF_ReadTime			= 0xFFFF;
	tskno_TimerTrainingDetect		= 0xFFFF;
	tskno_TimerRLSD_Detect			= 0xFFFF;
	tskno_TimerBaudWait				= 0xFFFF;
	
	tskno_v21_timeup				= 0xFFFF;
	tskno_v21_off					= 0xFFFF;
	
	tskno_TxEcmControl				= 0xFFFF;

	tskno_TxDMA_TC_Detect			= 0xFFFF;
	tskno_RxDMA_TC_Detect			= 0xFFFF;
	tskno_RxFcsDetect				= 0xFFFF;
	tskno_CcRetrainDetect			= 0xFFFF;
	tskno_MDM_BackupRamToEcmBufTask = 0xFFFF;

	/*
	** Used with CMN_MultiTimer10msStart()
	*/
	timerID_DummyPixTimer			= 0xFF; /* Added by H.Kubo 1997/07/14, replacing tskno_DummmyPixTimer. */
	timerID_Timer30sec				= 0xFF; /* Added by H.Kubo 1997/07/15, replacing tskno_Timer30sec */
	timerID_TimerT2					= 0xFF;
	timerID_Timer3sec				= 0xFF;
	timerID_EcmCloseTimer 			= 0xFF; /* Added by H.Kubo 1997/12/15, replacing tskno_EcmCloseTimer */
 	timerID_FcsDetectTimer			= 0xFF; /* Added by H.Kubo 1997/12/15, replacing tskno_FcsDetectTimer */
	tskno_MDM_ModemRecoverTask		= 0xFFFF; /* Add By O.Kimoto 1998/02/03 */

	/* ported for HINOKI2 2002/01/07 T.Takagi */
#if (PRO_PRINTER_RX == ENABLE)	/* By H.Hirao 1998/10/27 */
	tskno_CDC_PRxDMA_Task			= 0xFFFF;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.2 K.Kawata	*//* By M.Maeda 2002/10/24 */
	tskno_CDC_PRxDMA_Task			= 0xFFFF;
#endif
#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/09 By H.Hirao */
	tskno_CDC_STxDMA_Task			= 0xFFFF;
#endif

}


/*************************************************************************
	module		:[Ｖ１７以下で受信レベルのシフトをする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/28]
	author		:[村田]
*************************************************************************/
void  MDM_SetReceiveLevelExtension(UBYTE hdlc_mode)
{
	UWORD	timer;
	UWORD	newc_count;

	/* 1997/02/08 Y.Murata */
	newc_count = MDM_GetConfigTimeCount(ModemBlock.Config);

	MDM_FskModeFlag = 0;

	if (SYS_V34ProcedureExecuting() == 0) {

		MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
		MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/

		MDM_SetIO(POS_TPDM,ON);
		if (hdlc_mode) {
			MDM_SetIO(POS_HDLC,ON);
		}
		else {
			MDM_SetIO(POS_HDLC,OFF);
		}
		MDM_SetIO(POS_DATA,ON);
		
		
		
#if defined (KEISATSU) /* 警察FAX 05/07/21 石橋正和 */
		if ((FCM_S1_Scramble == TRUE) && 
			((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
			|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
			/* スクランブル通信の場合 */
			S1_SetRTS(0);
		}
		else {
			MDM_SetIO(POS_RTS,OFF);
		}
#else
		MDM_SetIO(POS_RTS,OFF);
#endif
		MDM_SetIO(POS_DTR,OFF);

		if (MDM_ReceiveLevelExtension == 1) {
			if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
				timer = MDM_GetSpikeNoiseWaitTime();
				MDM_SetIO(POS_CONF,ModemBlock.Config);
				DspRamAccessWriteMethod3(0x010D, 0x0004, 0xFFFB);	/* 10D:2 ON */
				MDM_SetReceiveLevelExtendRLSD();
				MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
				wai_oneshot(timer);

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

				DspRamAccessWriteMethod3(0x0B3C, 0x3700, 0x0000);	/* B3C<-3700h */
				MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
			}
			else {
				MDM_SetIO(POS_CONF,ModemBlock.Config);
				DspRamAccessWriteMethod3(0x010D, 0x0004, 0xFFFB);	/* 10D:2 ON */
				MDM_SetReceiveLevelExtendRLSD();

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

				DspRamAccessWriteMethod3(0x0B3C, 0x3700, 0x0000);	/* B3C<-3700h */
			}
		}
		else {
			if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
				timer = MDM_GetSpikeNoiseWaitTime();
				MDM_SetIO(POS_CONF,ModemBlock.Config);
				MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
				wai_oneshot(timer);

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

				MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
			}
			else {
				MDM_SetIO(POS_CONF,ModemBlock.Config);

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);
			}
		}
	}
}

/*************************************************************************
	module		:[Ｖ１７以下で受信レベルのシフトを解除]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/28]
	author		:[村田]
*************************************************************************/
void  MDM_ReSetReceiveLevelExtension(void)
{
	if ( SYS_V34ProcedureExecuting() == 0 ) {
		if ( MDM_ReceiveLevelExtension == 1 ) {
			DspRamAccessWriteMethod3( 0x010D, 0x0000, 0xFFFB );	/* 10D:2 OFF */
		}
	}
}


/*************************************************************************
	module		:[Ｖ１７以下で受信レベルのシフトにともないＲＬＳＤレベルの変える]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/28]
	author		:[村田]
*************************************************************************/
void  MDM_SetReceiveLevelExtendRLSD(void)
{
	UWORD	turn_on;
	UWORD	turn_off;

	turn_on = 0;
	turn_off = 0;

	switch (ModemBlock.Config) {
	case BPS14400_V17:
		turn_on = 0x1300;
		turn_off = 0x1950;
		break;
	case BPS12000_V17:
		turn_on = 0x1320;
		turn_off = 0x1850;
		break;
	case BPS9600_V17:
		turn_on = 0x1300;
		turn_off = 0x1900;
		break;
	case BPS7200_V17:
		turn_on = 0x1270;
		turn_off = 0x1900;
		break;
	case BPS9600_V29:
		turn_on = 0x0143;
		turn_off = 0x0075;
		break;
	case BPS7200_V29:
		turn_on = 0x0133;
		turn_off = 0x0070;
		break;
	case BPS4800_V27:
		turn_on = 0x11F0;
		turn_off = 0x1169;
		break;
	case BPS2400_V27:
		turn_on = 0x1210;
		turn_off = 0x1250;
		break;
	}
	if (turn_on) {
		DspRamAccessWriteMethod2(0x0134, 0x0135, turn_on, 0x0000);
		DspRamAccessWriteMethod2(0x0136, 0x0137, turn_off, 0x0000);
	}
}


/*
** この関数は使用されていないので、削除します。使用することがあれば復活してください
** フラッシュプログラム搭載において、プログラム領域節約のため
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[Ｖ１７以下コンフィグレーションセット]
//	function	:[
//		1.メモリＳＷによりスパイクノイズ対策も行う
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[MDM]
//	date		:[1997/01/30]
//	author		:[村田]
//*************************************************************************/
//UBYTE  MDM_SetConfigRationForG3Start(void)
//{
//#if 0
//	UWORD	timer;
//
//	timer = 0;
//
//	if (SYS_V34ProcedureExecuting() == 0) {
//		if ((ModemBlock.Config == BPS300_V21) &&
//			(MDM_GetIO(POS_CONF) == BPS300_V21)) {
//			/* Nothing */
//			return(0);
//		}
//		else {
//			if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
//				timer = MDM_GetSpikeNoiseWaitTime();
//				MDM_SetIO(POS_CONF,ModemBlock.Config);
//				MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
//				wai_oneshot(timer);
//				MDM_SetIO(POS_NEWC,ON);
//				MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
//			}
//			else {
//				MDM_SetIO(POS_CONF,ModemBlock.Config);
//				MDM_SetIO(POS_NEWC,ON);
//			}
//			return(1);
//		}
//	}
//#endif
//	return(0);
//}
#endif

/*************************************************************************
	module		:[スパイクノイズ対策ウエイト時間]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/01/30]
	author		:[村田]
*************************************************************************/
UWORD  MDM_GetSpikeNoiseWaitTime(void)
{
	UWORD	timer;

	timer = 1;

	switch (ModemBlock.Config) {
	case BPS14400_V17:
	case BPS14400_V33:
		timer = 2;			/* Spike Noise Wait 486usec MAX */
		break;
	case BPS12000_V17:
	case BPS12000_V33:
		timer = 2;			/* Spike Noise Wait 583usec MAX */
		break;
	case BPS9600_V17:
		timer = 2;			/* Spike Noise Wait 729usec MAX */
		break;
	case BPS7200_V17:
		timer = 2;			/* Spike Noise Wait 972usec MAX */
		break;
	case BPS9600_V29:
		timer = 2;			/* Spike Noise Wait 729usec MAX */
		break;
	case BPS7200_V29:
		timer = 2;			/* Spike Noise Wait 972usec MAX */
		break;
	case BPS4800_V27:
		timer = 3;			/* Spike Noise Wait 1458usec MAX */
		break;
	case BPS2400_V27:
		timer = 4;			/* Spike Noise Wait 2916usec MAX */
		break;
	case BPS300_V21:		/** Channel 2 **/
		timer = 25;			/* Spike Noise Wait 23300usec MAX */
		break;
	default:
		timer = 1;
		break;
	}
	return(timer);
}

CONST UBYTE fsk_conf_for_nd = 0; /* added by H.Kubo 1998/10/19 */
/*************************************************************************
	module		:[低速コンフィグ]
	function	:[
		1.パラレルデータ、ＨＤＬＣ、およびデータビットをセットする
		2.送出時のみＲＴＳをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/02/06]
	author		:[村田]
*************************************************************************/
void  MDM_FskConfig(UBYTE tx_mode)
{
	UWORD	timer;
	UWORD	newc_count;

	/* 1997/02/08 Y.Murata */
	newc_count = MDM_GetConfigTimeCount(ModemBlock.Config);

	if (MDM_FskModeFlag == 0) {	/* 通信１発目のＦＳＫモード */
		MDM_FskModeFlag = 1;
	}
	else {

		if ((MDM_GetIO(POS_CONF) == BPS300_V21) &&
			(MDM_GetIO(POS_HDLC)) &&
			(MDM_GetIO(POS_DATA)) &&
			(MDM_GetIO(POS_TPDM)) ) {	/* すでにＦＳＫモードなら何もしない */

			if (tx_mode) {
				MDM_SetIO(POS_RTS,ON);
			}
			else {
				MDM_SetIO(POS_RTS,OFF);
			}
			return;
		}
	}

	if (fsk_conf_for_nd) { /* added by H.Kubo 1998/10/19 */
		UWORD timer = 30; /* 300ms のタイマー */

		MDM_SetIO(POS_NSIE,OFF);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */
		MDM_SetIO(POS_NSIA,OFF);	/* テスト的に入れてみます。 by H.Kubo 1998/10/19 */
		MDM_SetIO(POS_NEWS,OFF);	/* テスト的に入れてみます。 by H.Kubo 1998/10/19 */

		MDM_SetIO(POS_CONF,ModemBlock.Config);

		MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
		MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
		MDM_SetIO(POS_TPDM,ON);
		MDM_SetIO(POS_HDLC,ON);
		MDM_SetIO(POS_DATA,ON);

		MDM_SetIO(POS_NEWC,ON);
		do {
			wai_tsk(10/10); /* 10ms wait */
		} while (MDM_GetIO(POS_NEWC) && (timer-- > 0));
	}
	else {
		if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
			timer = MDM_GetSpikeNoiseWaitTime();
			MDM_SetIO(POS_CONF,ModemBlock.Config);

			MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_TPDM,ON);
			MDM_SetIO(POS_HDLC,ON);
			MDM_SetIO(POS_DATA,ON);

			MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
			wai_oneshot(timer);

			/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
			MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);
			MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
		}
		else {
			MDM_SetIO(POS_CONF,ModemBlock.Config);

			MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_TPDM,ON);
			MDM_SetIO(POS_HDLC,ON);
			MDM_SetIO(POS_DATA,ON);

			/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
			MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);
		}
	} /* added by H.Kubo 1998/10/19 */
	if (tx_mode) {
		MDM_SetIO(POS_RTS,ON);
	}
	else {
		MDM_SetIO(POS_RTS,OFF);
	}
}

/*************************************************************************
	module		:[高速コンフィグ]
	function	:[
		1.パラレルデータ、ＨＤＬＣ、およびデータビットをセットする
		2.送信時のみＲＴＳをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/02/06]
	author		:[村田]
*************************************************************************/
void  MDM_HighSpeedConfig(UBYTE tx_mode, UBYTE hdlc_mode)
{
	UWORD	timer;
	UWORD	newc_count;

	MDM_FskModeFlag = 0;
	
	/* 1997/02/08 Y.Murata */
	newc_count = MDM_GetConfigTimeCount(ModemBlock.Config);
	
	if (SYS_V34ProcedureExecuting() == 0) {
		if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
			timer = MDM_GetSpikeNoiseWaitTime();
			MDM_SetIO(POS_CONF,ModemBlock.Config);

			MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_TPDM,ON);
			if (hdlc_mode) {
				MDM_SetIO(POS_HDLC,ON);
			}
			else {
				MDM_SetIO(POS_HDLC,OFF);
			}
			MDM_SetIO(POS_DATA,ON);
			MDM_SetIO(POS_DTR,OFF);

			MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
			wai_oneshot(timer);

			/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
			MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

			MDM_SetIO(POS_TXSQ, OFF);	/* 送信器スケルチ ＯＦＦ */
		}
		else {
			MDM_SetIO(POS_CONF,ModemBlock.Config);
			MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
			MDM_SetIO(POS_TPDM,ON);
			if (hdlc_mode) {
				MDM_SetIO(POS_HDLC,ON);
			}
			else {
				MDM_SetIO(POS_HDLC,OFF);
			}
			MDM_SetIO(POS_DATA,ON);




			if (tx_mode == 0) {
#if defined (KEISATSU) /* 警察FAX 05/07/21 石橋正和 */
				if ((FCM_S1_Scramble == TRUE) && 
					((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
					|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
					/* スクランブル通信の場合 */
					S1_SetRTS(0);
				}
				else {
					MDM_SetIO(POS_RTS,OFF);
				}
#else
				MDM_SetIO(POS_RTS,OFF);
#endif
			}
			MDM_SetIO(POS_DTR,OFF);

			/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
			MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);
		}
		if (tx_mode) {
#if defined (KEISATSU) /* 警察FAX 05/07/21 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				/* スクランブル通信の場合 */
				
				
				
				if ((ModemBlock.Mode == MODE_TX_TCF) || (ModemBlock.Mode == MODE_TX_G3)) {
					if (DBG_G3_TCF_OriginalPosition == 1) {
						S1_SetRTS(1);
					}
				}
				if ((ModemBlock.Mode == MODE_TX_ECM) && (DBG_ECM_OriginalPosition == 1)) {
					S1_SetRTS(1);
				}
				
				
				
				/* S1_SetRTS(1); */
				
				
				
			}
			else {
				MDM_SetIO(POS_RTS,ON);
			}
#else
			MDM_SetIO(POS_RTS,ON);
#endif
		}
	}
}


/*************************************************************************
	module		:[コンフィグ TIME ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/02/08]
	author		:[村田]
*************************************************************************/
UWORD  MDM_GetConfigTimeCount(UBYTE mode)
{
	UWORD	ret_cnt;
	
	switch (mode) {
	case BPS14400_V33:
		ret_cnt = V33_14400_NEWC_TIME;
		break;
	case BPS12000_V33:
		ret_cnt = V33_12000_NEWC_TIME;
		break;
	case BPS14400_V17:
		ret_cnt = V17_14400_NEWC_TIME;
		break;
	case BPS12000_V17:
		ret_cnt = V17_12000_NEWC_TIME;
		break;
	case BPS9600_V17:
		ret_cnt = V17_9600_NEWC_TIME;
		break;
	case BPS7200_V17:
		ret_cnt = V17_7200_NEWC_TIME;
		break;
	case BPS9600_V29:
		ret_cnt = V29_9600_NEWC_TIME;
		break;
	case BPS7200_V29:
		ret_cnt = V29_7200_NEWC_TIME;
		break;
	case BPS4800_V27:
		ret_cnt = V27_4800_NEWC_TIME;
		break;
	case BPS2400_V27:
		ret_cnt = V27_4800_NEWC_TIME;
		break;
	case BPS300_V21:
	default:
		ret_cnt = V21_300_NEWC_TIME;
		break;
	}
	return(ret_cnt);
}


/*************************************************************************
	module		:[モデムクローズ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1997/03/17]
	author		:[村田]
*************************************************************************/
UWORD  MDM_InitialConfig2(UBYTE type)
{
	UWORD	newc_count;
	UWORD	ret;
	UWORD	start_time;
	UWORD	exec_time;
	UWORD	wait_time;
	UWORD	comp_time;
	
	switch (type) {
	case 1:	/* PIX-EOP */
		comp_time = 1;		/* 9->1 1997/08/11 Y.Murata */
		break;
	case 2:	/* CED-DIS */
		comp_time = CHK_WaitAfterDIS();
		if (comp_time == 75) {
			comp_time = (1);	/* 7-1 -> 1  DEU信号間ﾀｲﾐﾝｸﾞ対策 CED(AnsAM)-DIS */
		}
		else if (comp_time == 1000) {
			comp_time = 100;
		}
		else {
			comp_time = 7;
		}
		break;
	default:
		comp_time = 7;
		break;
	}

	start_time = SYS_GeneralTimer;
	newc_count = V21_300_NEWC_TIME;

	ModemControl.Status = 0;	/**	モデムステータスクリア	*/

	if (!(SYS_V34ProcedureExecuting())) {
		if (MDM_GetIO(POS_CONF) != BPS300_V21) {
			if (CHK_V34SpikeNoiseEvasion()) {	/* スパイクノイズ対策有効 */
				MDM_SetIO(POS_CONF,BPS300_V21);
				MDM_SetIO(POS_TXSQ, ON);
				wai_oneshot(25);			/* Spike Noise Wait 23300usec MAX */

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 Y.Murata */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

				MDM_SetIO(POS_TXSQ, OFF);

				MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
				MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
				MDM_SetIO(POS_TPDM,ON);
				MDM_SetIO(POS_HDLC,ON);
				MDM_SetIO(POS_DATA,ON);

			}
			else {
				MDM_SetIO(POS_CONF,BPS300_V21);

				/*MDM_SetIO(POS_NEWC,ON); 1997/02/08 */
				MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);

				MDM_SetIO(POS_ASYN,OFF);		/**	ＦＩＦＯ使用	*/
				MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
				MDM_SetIO(POS_TPDM,ON);
				MDM_SetIO(POS_HDLC,ON);
				MDM_SetIO(POS_DATA,ON);
			}
			MDM_FskModeFlag = 0;
		}
	}

	exec_time = (SYS_GeneralTimer - start_time);
	
	if (exec_time < comp_time) {
		wait_time = (comp_time - exec_time);
		
		wai_tsk(wait_time);
	}
	else {
	}

	return(ret);
}

/*************************************************************************
	module		:[V23 コンフィグ]
	function	:[
		1.パラレルデータ、ＨＤＬＣ、およびデータビットをセットする
		2.送出時のみＲＴＳをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/06/23]
	author		:[久保]
*************************************************************************/
CONST UBYTE v23_rx_conf_method = 1;
CONST UBYTE v23_rx_by_dma = 0;
void  MDM_V23Config(UBYTE tx_mode)
{
	UWORD	timer;
	UWORD	newc_count;

	MDM_SetIO(POS_CONF, ModemBlock.Config);

	MDM_SetIO(POS_V23HDX, ON); /* V23 半二重 */
	MDM_SetIO(POS_DATA, ON); /* ANS/FAX 待機で ND データを取りそこなう不具合の対策 By H.Kubo 1998/12/14 */

	/* 8bit Non-parity で受信するときは、 パリティチェック OFF, データビット7bit, イーブンパリティ付きに設定する*/ 
	MDM_SetIO(POS_PARSL, IO_BIT_PARSL2);
	MDM_SetIO(POS_PEN, OFF);
	MDM_SetIO(POS_WDSZ, WDSZ_8BITS); /* 7 => 8 changed by H.Kubo 1998/09/21 */ /* data bits are 7 bits */

	MDM_SetIO(POS_EXOS, ON); /* OFF => ON changed by H.Kubo 1998/09/21 */
	
	MDM_SetIO(POS_HDLC,OFF); /* 順番入れ替えてみる by H.Kubo 1998/10/19 */
	MDM_SetIO(POS_RTDIS, OFF);
	MDM_SetIO(POS_TPDM,ON);
	MDM_SetIO(POS_ASYN,ON);		/**	ＦＩＦＯ使用	*/
	MDM_SetIO(POS_TXSQ, ON);	/* 送信器スケルチ ＯＮ */
	/* MDM_SetIO(POS_HDLC,OFF); */ /* 順番入れ替えてみる by H.Kubo 1998/10/19 */
	MDM_SetIO(POS_CEQ, OFF);
	MDM_SetIO(POS_FIFOEN,ON);		/**	ＦＩＦＯ使用	*/
	if (v23_rx_by_dma) {
		MDM_SetIO(POS_DMAE, ON);
	}
	else {
		MDM_SetIO(POS_DMAE, OFF);
	}

	if (v23_rx_conf_method) {
                timer = 30; /* 300ms のタイマー */
		MDM_SetIO(POS_NEWC,ON);
		do {
			wai_tsk(10/10); /* 10ms wait */
		} while (MDM_GetIO(POS_NEWC) && (timer-- > 0));
		MDM_SetIO(POS_DTR,ON);
	}
	else {
		newc_count = MDM_GetConfigTimeCount(ModemBlock.Config);
		MDM_SetIO_NewcAfterConf(POS_NEWC,ON, newc_count);
	}

	if (tx_mode) {
		MDM_SetIO(POS_RTS,ON);
	}
	else {
		MDM_SetIO(POS_RTS,OFF);
	}
}


