/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdm_g3.c                                                              */
/*  作成者       :                                                                       */
/*  日  付       : 1999/10/06                                                            */
/*  概  要       : 画データ送信関連処理                                                  */
/*  修正履歴     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\define\s1_pro.h"
#endif

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
#include "\src\atlanta\ext_v\fcm_data.h"
#endif

/*************************************************************************
	module		:[Ｇ３送信モデムオープン]
	function	:[
		1.モデム制御エリア初期化
		2.指定のモデムコンフィグレーションを実行する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemBlock
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/20]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxG3_Open(void)
{
	/*------------------*/
	/**	各初期化処理	*/
	/*------------------*/
	TxCompleteEventFlag = 0;

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		/* MDM_SetIO(POS_DATA, OFF); */
		/* MDM_SetIO(POS_HDLC, OFF); */
		/* MDM_SetIO(POS_TPDM, OFF); */
		SetDTC_IntFromS1(); /* DTC割り込みをS1からにする */
		
		if ((ModemBlock.Mode == MODE_TX_TCF) || (ModemBlock.Mode == MODE_TX_G3)) {
			if (DBG_G3_TCF_OriginalPosition == 1) {
				S1_OpenG3Tx(FCM_S1_Senyo); /* S1オープン */
			}
		}
	}
	else {
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		MDM_SetIO(POS_DATA, ON);
		
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
	}
#endif
	
	/*----------------------------------*/
	/**	モデムコンフィグレーション実行	*/
	/*----------------------------------*/
	ModemConfig(WRITE_MODE);

#if defined (KEISATSU) /* 警察FAX 05/07/28 石橋正和 */
	if (FCM_S1_Scramble == FALSE) { /* スクランブル通信でない場合 */
		MDM_SetIO(POS_NSIE,ON);
	}
#else
	MDM_SetIO(POS_NSIE,ON);
#endif

	/*
	** R288F VERSION 24P以降の場合
	** by H.Kubo 1998/08/20
	*/
	if (SYS_ModemVersion == MDM_L6713_24P) {
		/* 24P 以降では、拡張ＦＩＦＯがつくようになりました。最大２５６バイトまでＦＩＦＯが拡張されます。
		** 拡張ＦＩＦＯが有効な状態では、（ＥＣＭなしの）Ｇ３送信で画データの最後のＲＴＣをモデムに送出
		** しても、一旦拡張ＦＩＦＯに格納されてから回線上に送出されるので、いつＲＴＣが回線上に送出
		** されたのかわかりません。そのため、ＰＩＸの高速信号を切るタイミングがわからなくなります。、
		** 24P では、拡張ＦＩＦＯがデフォルトで有効ですが、ここで送信用の拡張ＦＩＦＯを無効にします。
		** どうしても送信用の拡張ＦＩＦＯを有効にするときは、 TxG3_Close() で RTS を OFF にする前に、
		** 十分に待ち時間を取ってください。さもないと、ＰＩＸの最後が消失します。
		*/
		MDM_DisableExtendedTxFIFO(); /* 24P only. */
	}
	
#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		MDM_SetIO(POS_DATA, OFF);
		MDM_SetIO(POS_HDLC, OFF);
		MDM_SetIO(POS_TPDM, OFF);
		/* SetDTC_IntFromS1(); */ /* DTC割り込みをS1からにする */
		
		/* S1_OpenG3Tx(FCM_S1_Senyo); */ /* S1オープン */
		
		/* S1_SetRTS(1); */ /* RTS送出 */
		/* CTS_Check(); */ /* CTSチェック */
	}
#endif
}


/*************************************************************************
	module		:[Ｇ３送信モデムライト]
	function	:[
		1.指定されたバッファ先頭アドレスとデータ数をモデムバッファコントロールブロックに登録する
		2.モデムがＩＤＬＥ時、モデム送信ＤＭＡを起動する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemBlock
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/21]
	author		:[曽根岡拓]
*************************************************************************/
void 	TxG3_Write(
UBYTE			*buffer,
UWORD			count)
{
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	/*--------------------------*/
	/*	送信フレーム登録処理	*/
	/*--------------------------*/
	MDMWPNT.TopAddress = buffer;	/**	送出バッファ先頭アドレス登録	*/
	MDMWPNT.DataCount = count;	/**	送出バイト数登録	*/
	ModemControl.UsedCount++;	/**	モデムバッファ使用本数を１プラスする	*/

	if (ModemBlock.Chain == SET_COMPL) {	/**	最終データ登録時	*/
		ModemControl.Status |= STAT_EMPTYPT;	/**	送出データなし設定	*/
	}
	/*--------------------------------------*/
	/*	モデムバッファ書き込み位置更新処理	*/
	/*--------------------------------------*/
	NextMdmBufWritePointSetExtRom();

	/*----------------------*/
	/*	送信ＤＭＡ起動処理	*/
	/*----------------------*/
	if (!(ModemControl.Status & STAT_ACT)) {	/**	モデムがＩＤＬＥ状態の時	*/
		if (ModemBlock.Mode == MODE_TX_TCF) {
			if (ServiceFuncTx == TRUE) {
				TxTcfStart();
			}
			else {
				TxG3_Start();	/**	送信ＤＭＡ起動	*/
			}
		}
		else {
			TxG3_Start();	/**	送信ＤＭＡ起動	*/
		}
	}
	CMN_EnableInterrupt();	/**	割り込み許可	*/
}

/*************************************************************************
	module		:[Ｇ３送信モデムスタート]
	function	:[
		1.モデム内部コントロールの読みだし位置に示される、バッファアドレスとデータ数で
		, モデムＤＭＡ設定する
		2.モデムＤＭＡマスク解除する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far	TxG3_Start(void){}]
	date		:[1993/12/21]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void 	TxG3_Start(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;
	
	/*--------------------------*/
	/*	モデムＶ５３ＤＭＡ設定	*/
	/*--------------------------*/
	ModemControl.Status |= (STAT_ACT + STAT_FRSTON);
	ModemWriteDMA_Data.Channel		= DMA_CH_TX;

	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	絶対アドレスに変換	*/

	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount; /* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta*/
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

	/* Added by H.Kubo 1997/10/08
	**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	/*----------------------------------*/
	/*	モデムＶ５３ＤＭＡマスク解除	*/
	/*----------------------------------*/
	/* DMA_RequestEnable(ModemWriteDMA_Data.Item, ModemWriteDMA_Data.Channel); */
	DMA_RequestEnable(DMA_CH_TX); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */
}

#if defined (KEISATSU) /* 警察FAX 05/08/20 石橋正和 */
/**************************************************************************************************/
/**
	@brief		Ｇ３送信モデムライト(RTS送信)
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/08/20 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void TxG3_WriteWithRTS_Sent(
					UBYTE *buffer,
					UWORD count,
					BOOL bsend) /* RTSを送信するか否か */
{
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	/*--------------------------*/
	/*	送信フレーム登録処理	*/
	/*--------------------------*/
	MDMWPNT.TopAddress = buffer;	/**	送出バッファ先頭アドレス登録	*/
	MDMWPNT.DataCount = count;	/**	送出バイト数登録	*/
	ModemControl.UsedCount++;	/**	モデムバッファ使用本数を１プラスする	*/

	if (ModemBlock.Chain == SET_COMPL) {	/**	最終データ登録時	*/
		ModemControl.Status |= STAT_EMPTYPT;	/**	送出データなし設定	*/
	}
	/*--------------------------------------*/
	/*	モデムバッファ書き込み位置更新処理	*/
	/*--------------------------------------*/
	NextMdmBufWritePointSetExtRom();

	/*----------------------*/
	/*	送信ＤＭＡ起動処理	*/
	/*----------------------*/
	if (!(ModemControl.Status & STAT_ACT)) {	/**	モデムがＩＤＬＥ状態の時	*/
		if (ModemBlock.Mode == MODE_TX_TCF) {
			if (ServiceFuncTx == TRUE) {
				TxTcfStart();
			}
			else {
				TxG3_StartWithRTS_Sent(bsend);	/**	送信ＤＭＡ起動	*/
			}
		}
		else {
			TxG3_StartWithRTS_Sent(bsend);	/**	送信ＤＭＡ起動	*/
		}
	}
	CMN_EnableInterrupt();	/**	割り込み許可	*/
}

/**************************************************************************************************/
/**
	@brief		Ｇ３送信モデムスタート(RTS送信)
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/08/20 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void TxG3_StartWithRTS_Sent(
						BOOL bsend) /* RTSを送信するか否か */
{
	struct DMA_Data_t ModemWriteDMA_Data;
	
	/*--------------------------*/
	/*	モデムＶ５３ＤＭＡ設定	*/
	/*--------------------------*/
	ModemControl.Status |= (STAT_ACT + STAT_FRSTON);
	ModemWriteDMA_Data.Channel		= DMA_CH_TX;

	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	絶対アドレスに変換	*/

	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount; /* Modified by H.Kubo 1997/06/25 for DMA routine of Atlanta*/
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

	/* Added by H.Kubo 1997/10/08
	**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	
	if (bsend == TRUE) {
		S1_OpenG3Tx(FCM_S1_Senyo); /* S1オープン */
		if ((DBG_DelayAfterS1Open / 10) > 0) {
			wai_tsk(DBG_DelayAfterS1Open / 10);
		}
		S1_SetRTS(1); /* RTS送出 */
		CTS_Check(); /* CTSチェック */
		if ((DBG_DelayAfterRTC / 10) > 0) {
			wai_tsk(DBG_DelayAfterRTC / 10);
		}
	}
	
	/*----------------------------------*/
	/*	モデムＶ５３ＤＭＡマスク解除	*/
	/*----------------------------------*/
	/* DMA_RequestEnable(ModemWriteDMA_Data.Item, ModemWriteDMA_Data.Channel); */
	DMA_RequestEnable(DMA_CH_TX); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */
}

#endif

/*************************************************************************
	module		:[Ｇ３送信モデムクローズ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/21]
	author		:[曽根岡拓]
*************************************************************************/
/*
** R288F VERSION 24P以降の場合
** by H.Kubo 1998/10/20
*/
CONST UBYTE tcf_debug = 0;

void 	TxG3_Close(void)
{
	if (ModemBlock.Mode == MODE_TX_TCF) {
		if (TxCompleteEventFlag == 0) {
			wai_evt(EVT_TX_COMPLETE);
		}
	}
	else {
		switch (MDM_PhaseC_Status) {
		case	TX_PAGE_END:
		case	TX_BLOCK_END:
#if !defined (HINOKI2) && !defined (SATSUKI2) && !defined(STOCKHM2)	/* 長尺原稿ループ対策 by O.Kimoto 2003/01/30 */
		case	TX_1M_OVER:
#endif
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			if (TxCompleteEventFlag == 0) {
				wai_evt(EVT_TX_COMPLETE);
			}
			TxCompleteEventFlag = 0;
			CMN_EnableInterrupt();	/**	割り込み許可	*/
			break;
		case	TX_STOPPED:
			if (MDM_TxForceStop() == 0) {	/* PRO_QUICK_TX */
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (TxCompleteEventFlag == 0) {
					wai_evt(EVT_TX_COMPLETE);
				}
				TxCompleteEventFlag = 0;
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			break;
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 長尺原稿ループ対策 by O.Kimoto 2003/01/30 */
		case	TX_1M_OVER:
#endif
		case	TX_FILE_ERR:
		case	TX_MEM_ERR:
		case	TX_DOC_ERR:
		case	TX_LAMP_ERR:
		default:
			break;
		}
	}
	/*--------------------------------------*/
	/**	モデム－＞モデムバッファＤＭＡ終了	*/
	/*--------------------------------------*/
	DMA_RequestMask(DMA_CH_TX); /* 1st argument MASTER_DMAU is deleted by H. Kubo 1997/05/24 */
	/*----------------------------------*/
	/*	モデムバッファセマフォリセット	*/
	/*----------------------------------*/
	ResetModemBufferSem();

	/*------------------*/
	/**	モデムクローズ	*/
	/*------------------*/
	/*----------------------------*/
	/* 海外認可共通対応           */
	/* FOREIGN_APPROVAL No.1-2    */
	/*----------------------------*/
	MDM_ModemTxCloseWait();

	if (SYS_V34ProcedureExecuting() == 0) {	/* Ｖ３４でない時 1996/10/17 Y.Murata */
		MDM_SetIO(POS_RTS,OFF);
		wai_tsk(3);		/* at least 15ms */
	}

#if defined (KEISATSU) /* 警察FAX 05/06/27 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		
		
		
		UWORD i;
		for (i = 0; i < 100; i++) { /* 1秒待つ > (256byte / (300byte/sec)) */
			if (S1_SCI_GetTxStatus() & S1_REG_BIT_SCI_TXEND) {
				break;
			}
			wai_tsk(10/10); /* 10ms 待つ */
		}
		
		
		
		S1_CloseG3Tx(); /* S1クローズ */
		
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
		
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		MDM_SetIO(POS_DATA, ON);
	}
	else {
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
		
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		MDM_SetIO(POS_DATA, ON);
	}
#endif

	/*******************************
	** TxFIFO が空になるまで待つ処理
	*******************************/

	/*
	** RTS OFF の前から後ろに移動。by H.Kubo 1998/10/20
	*/
	/*
	** R288F VERSION 24P以降の場合
	** by H.Kubo 1998/08/20
	*/
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	if ((SYS_ModemVersion == MDM_L6713_26P)
	|| (SYS_ModemVersion >= MDM_L6719_12P_ES)) {
#else
	if (SYS_ModemVersion == MDM_L6713_26P) {
#endif
		UWORD i;
		if (!SYS_V34ProcedureExecuting()) {	/* Ｖ３４でない時 1996/10/17 Y.Murata */
			for (i = 0; i < 100; i++) { /* 1 秒待つ > (256byte / (300byte/sec))*/
				if (MDM_GetIO(POS_TPMT)) { /* FIFO が空か */
					break;
				}
				wai_tsk(10/10); /* 10ms 待つ */
			}
		}
		if (tcf_debug) { /* for debug by H.Kubo 1998/10/20 */
			MDM_SetIO(POS_TXSQ, ON);
		}
	}
#if 0
	MDM_InitialConfig();
#endif
	
	/*----------------------------*/
	/* 海外認可共通対応           */
	/* FOREIGN_APPROVAL No.1-8 ③ */
	/*----------------------------*/
	MDM_InitialConfig2(1);

	MDM_SetIO(POS_NSIE,OFF); /* モデムレジスタが変化しても割り込みをかけないようにする。 */
}


/*************************************************************************
	module		:[Ｇ３受信モデムオープン]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/12]
	author		:[曽根岡拓]
*************************************************************************/
void 	RxG3_Open(void)
{
	UWORD agcgain_value;		/** For V29 7200 start by O.kimoto 1997/02/27 */
	UWORD rlsd_turn_on_value;	/** For V29 7200 start by O.kimoto 1997/02/27 */
	UWORD rlsd_turn_off_value;	/** For V29 7200 start by O.kimoto 1997/02/27 */

#if defined (KEISATSU) /* 警察FAX 05/06/20 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		SetDTC_IntFromS1(); /* DTC割り込みをS1からにする */
		S1_OpenG3Rx(FCM_S1_Senyo); /* S1オープン */
	}
	else {
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
	}
#endif

	SetClear(( UBYTE * )&ModemControl, sizeof( struct mdmcntl_t ), 0x00 );	/**	モデムコントロール領域初期化	*/
#if ( PRO_CLASS1 == ENABLE ) /* added by H.Kubo */
	ModemControl.WritePoint = MDM_ModemBufferFirstPoint;
	ModemControl.ReadPoint = MDM_ModemBufferFirstPoint;
#endif

	/****************************/
	/**	モデムコンフィグ設定	*/
	/****************************/

 	/*
 	** R288F VERSION 24P以降の場合
 	** For configuring RLSD drop-out timer.
 	** by H.Kubo 1998/10/21
 	*/
 	IsRlsdAndRdbfOn = 0;

	ModemConfig( READ_MODE );
	/** For V29 7200 start by O.kimoto 1997/02/27 */
	if ( CHK_V34_V29_7200Special()) {	/* UNISW D6:4 */
		if (!( SYS_V34ProcedureExecuting())) {
			if ( ModemBlock.Config == BPS7200_V29 ) {
				agcgain_value = DspRamAccessReadMethod4( 0xA00 );
				rlsd_turn_on_value = DspRamAccessReadMethod2( 0x134,0x135 );
				rlsd_turn_off_value = DspRamAccessReadMethod2( 0x136,0x137 );

				if ( agcgain_value > 0x1000 ) {
					agcgain_value -= 0x1000;	/** -6dBm */
				}
				else {
					agcgain_value = 0x0000;
				}

				if ( agcgain_value >= rlsd_turn_on_value ) {
					/** ＲＬＳＤ Ｔｕｒｎ ＯＮ／ＯＦＦレベル調整実施 */
					DspRamAccessWriteMethod1( 0x10D, 0x04, 0xFB );	/** P.4-43 B. */
					DspRamAccessWriteMethod2( 0x134, 0x145, ( UWORD )( agcgain_value ), 0x0000 );	/** P.4-43 C */
					DspRamAccessWriteMethod2( 0x136, 0x147, ( UWORD )( agcgain_value - 0x22D ), 0x0000 );	/** P.4-43 C */

					if ( MDM_ReceiveLevelExtension == 1 ) {
						DspRamAccessWriteMethod3( 0x0B3C, 0x3700, 0x0000 );	/* B3C<-3700h */
					}
				}
			}
		}
	}
	/** For V29 7200 end by O.kimoto 1997/02/27 */
	
	/*
	** R288F VERSION 24P以降の場合
	** by H.Kubo 1998/10/05
	*/
	switch ( SYS_ModemVersion ) {
	case MDM_L6713_13P:
	case MDM_L6713_14P:
	case MDM_L6713_20P:
	case MDM_L6713_22P:
		break;
	case MDM_L6713_24P:
	case MDM_L6713_26P:
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	case MDM_L6719_12P_ES:
	case MDM_L6719_12P_CS:
#endif
	default:
		MDM_EnableFastTrainingDetection(); /* RLSD が立つ前から、 valid training sequence を検出する設定。*/
		break;
	}

#if defined (KEISATSU) /* 警察FAX 05/11/11 石橋正和 */
	if (FCM_S1_Scramble == FALSE) {
		MDM_SetIO( POS_NSIE, ON ); /* モデムレジスタが変化したら割り込みをかけるようにする。 */
	}
#else
	MDM_SetIO( POS_NSIE, ON ); /* モデムレジスタが変化したら割り込みをかけるようにする。 */
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/20 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		MDM_SetIO(POS_HDLC, OFF);
		MDM_SetIO(POS_TPDM, OFF);
	}
#endif

	RxG3_Start();
}


/*************************************************************************
	module		:[Ｇ３受信モデムリード]
	function	:[
		1.
	]
	return		:[
		RCV_STOP:	ストップＳｗ検出
		RCV_BLOCK:	１ブロック受信
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/12]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE	RxG3_ReadExtRom(void)
{
	UBYTE	wrkmsk;
	UWORD	tmoutc;
	UWORD	dma_end_time;
	UWORD	dma_cnt;
	UWORD	i;
	UBYTE	buf_line;
	UBYTE	debug;
	UBYTE	test_sw;

	test_sw = 1;
	tmoutc = 0;
	dma_end_time = 0;	/* 1996/10/29 Y.Murata */
	/* debug ポストメッセージ 1回取れず対策 1996/11/01 Y.M */
	debug = 0;
	
	/*------------------------------*/
	/**	該当受信フレーム位置設定	*/
	/*------------------------------*/
	buf_line = ModemControl.ReadPoint;
	wrkmsk = (UBYTE)(1 << buf_line);

	/*--------------------------------------------------------------*/
	/**	受信フレーム待ち（２５６ｂｙｔｅ受信ＤＭＡ転送終了待ち）	*/
	/*--------------------------------------------------------------*/
	/* ２５６バイトＤＭＡ転送終了と転送時間を待ちます               */
	/* 256byte DMA Time                                             */
	/*	14400bps	14400bit/8bit = 1800byte/sec  256/1800 = 142ms  */
	/*	12000bps	12000bit/8bit = 1500byte/sec  256/1500 = 171ms  */
	/*	 9600bps	 9600bit/8bit = 1200byte/sec  256/1200 = 213ms  */
	/*	 7200bps	 7200bit/8bit =  900byte/sec  256/ 900 = 284ms  */
	/*	 4800bps	 4800bit/8bit =  600byte/sec  256/ 600 = 427ms  */
	/*	 2400bps	 2400bit/8bit =  300byte/sec  256/ 300 = 853ms  */
	/*--------------------------------------------------------------*/

	switch (ModemBlock.Speed) {
	case SPEED_14400:
		dma_end_time = 16;		/* 142ms + 10ms(10ms割り込み誤差) */
		break;
	case SPEED_12000:
		dma_end_time = 19;		/* 171ms + 10ms(10ms割り込み誤差) */
		break;
	case SPEED_9600:
		dma_end_time = 23;		/* 213ms + 10ms(10ms割り込み誤差) */
		break;
	case SPEED_7200:
		dma_end_time = 30;		/* 284ms + 10ms(10ms割り込み誤差) */
		break;
	case SPEED_4800:
		dma_end_time = 49;		/* 472ms + 10ms(10ms割り込み誤差) */
		break;
	case SPEED_2400:
		/* 1999/12/13 Y.Murata
		 * ２４００のNon-ECMでエラーラインが数ライン発生する。
		 * このタイマーがタイムアップしてしまい、モデムバッファに0xffをうめる処理が走っていた。
		 * 多分、fifoのデータ分遅れて出てきていると思われる。
		 * fifoの16バイトを考慮してタイマーを増やす。
		 * 2400bit/8bit =  300byte/sec   (256+16)/300 = 906ms + 10ms(10ms割り込み誤差)
		*/
		/*dma_end_time = 87;*/		/* 853ms + 10ms(10ms割り込み誤差) */
		dma_end_time = 92;
		break;
	default:
		dma_end_time = 0xFFFF;	/* 保険 */
		break;
	}

/*
 * ### このtest_swは動作を確認してからいれる事！ ###
*/
if (test_sw) {

	/* 1997/12/24
	 * クラス１のリモート送信機から受信する(14400bps)と画データの先頭にエラーラインがでる。
	 * なぜか、タイムアップのdma_end_timeがきてしまい、残りのモデムバッファに０ｘＦＦをいれるので
	 * エラーラインとなる。クラス１のときはダミーデータが２５６byteに満たないため、
	 * 画データ前のＥＰトーンの誤検出がタイミングを狂わすと思われる。
	 * タイムアップの処理は回線断されたときのためのタイムアップなのでダミーデータのときはタイマーを延ばす。
	*/
	/* 東芝 TF-3500, NEC NEFAX 650 からの受信でも同様にエラーラインが出てしまいます。この処理は必要です。 by H.Kubo 1999/04/12 */
#if (0)	/* 東芝 TF61(V.29)でも同様の不具合が発生したのでＧ３全てにこの処理を通します by J.Kishida 99/10/19 */
//	if (ModemBlock.Type == TYPE_V17) {
//		if (MDM_G3DummyDataDetecting == 1) {
//			dma_end_time = 100;			/* 1000ms */
//			MDM_G3DummyDataDetecting = 0;
//		}
//	}
#endif
	if (MDM_G3DummyDataDetecting == 1) {
#if defined (KEISATSU) /* 警察FAX 05/10/20 石橋正和 */
		dma_end_time = 400;			/* 4000ms */
#else
		dma_end_time = 100;			/* 1000ms */
#endif
		MDM_G3DummyDataDetecting = 0;
	}

}

	while (ModemRxStatus & wrkmsk) {

		if ((tmoutc > dma_end_time) || (MDM_RlsdTurnOffFlag == 1)) {
			if (MDM_RlsdTurnOffFlag == 1) {
				/* debug ポストメッセージ 1回取れず対策 1996/11/01 Y.M */
				if (debug == 1) {
					MDM_SetIO(POS_HDLC, ON);
				}
				MDM_RlsdTurnOffFlag = 0;
			}

			/*
			 * モデムバッファの残りを０ｘ００でうめます
			 * このパスを通るのは、画データ最後のＲＴＣを含む256ﾊﾞｲﾄに満たない部分及び
			 * 瞬断、キャリア断の時です
			*/
			/* DMA Disable */
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo 1997/06/24 */
			CMN_DisableInterrupt();		/* DI */
			if (ModemRxStatus & wrkmsk) {
				dma_cnt = DMA_CheckDMA_Counter(DMA_CH_RX); /*未転送バイト数 */ /* Modified line by H. Kubo 1997/06/25 */
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
				NextMdmBufWritePointSetExtRom();
				ModemControl.UsedCount++;
				/* Next Modem->ModemBuffer DMA Enable and Start */

				/* Added by H.Kubo 1997/10/09
				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
				*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
				DMA_RestartDMAU(DMA_CH_RX,  DMA_IO_TO_MEMORY, MDM_ModemDmaSize,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/

				CMN_EnableInterrupt();		/* EI */
				for (i = (MDM_ModemDmaSize - dma_cnt); i < MODEM_BUFFER_LENGTH; i++) { /* Modified line by H. Kubo 1997/06/25 */
					/* 1997/01/24 Y.Murata
					 * TCFのｾﾞﾛﾁｪｯｸでﾁｪｯｸ時間が100msや200msの時にOKとなってしまう可能性が
					 * あるためＦＦでうめる
					 * MDM_ModemBuffer[buf_line][i] = 0x00;
					*/
					MDM_ModemBuffer[buf_line][i] = 0xFF;
				}
#else
				/* Below Modification by H. Kubo 1997/06/24 */
				DMA_RestartDMAU(DMA_CH_RX,  DMA_IO_TO_MEMORY, MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/

				CMN_EnableInterrupt();		/* EI */
				for (i = (MODEM_DMA_SIZE - dma_cnt); i < MODEM_BUFFER_LENGTH; i++) { /* Modified line by H. Kubo 1997/06/25 */
					/* 1997/01/24 Y.Murata
					 * TCFのｾﾞﾛﾁｪｯｸでﾁｪｯｸ時間が100msや200msの時にOKとなってしまう可能性が
					 * あるためＦＦでうめる
					 * MDM_ModemBuffer[buf_line][i] = 0x00;
					*/
					MDM_ModemBuffer[buf_line][i] = 0xFF;
				}
#endif
			}
			else {
				/* Added by H.Kubo 1997/10/08
				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
				*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif

				DMA_RequestEnable(DMA_CH_RX); /* Changed for POPLAR_H by H. Kubo, 1997/06/17 */
				CMN_EnableInterrupt();		/* EI */
			}
			break;
		}
		if (SYS_FaxComStopSwitch() == 1) {
			return (RCV_STOP);
		}
		if (tmoutc > (UWORD)(5000/FRAME_WAIT)) {	/* 保険 */
			return (RCV_TMOUT);						/**	現在　監視時間5s	*/
		}

		/* モデムバッファ溢れを監視。 by H.Kubo 1998/01/23 */
		if (ModemControl.UsedCount > 8) {
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_MODEM_BUFFER_OVERLOW;
		}
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/*  プリントデコード停止要求フラグ。モデムバッファ溢れ回避のため。 By H.Kubo  1998/10/26 */
		/* ported for HINOKI2 2001/12/26 T.Takagi */
		if (ModemControl.UsedCount > ((SYB_MaintenanceSwitch[MNT_SW_E5] & 0xE0) >> 5) ) { /* モデムバッファの空きが残り少なくなったらプリント停止要求。 1998/11/12 */
			SYS_PRN_StopRequestFromModem = TRUE;
		}
		else {
			SYS_PRN_StopRequestFromModem = FALSE;
		}
#endif

		tmoutc++;
		wai_tsk(FRAME_WAIT/10);
	}
	/*------------------------------*/
	/**	該当受信ステータス初期化	*/
	/*------------------------------*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	ModemRxStatus |= wrkmsk;
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/*
	** 全機種に反映させます。  by H.Kubo 1999/01/26
	*/
	/*
	** added by H.Hirao 1998/12/10
	*/
	DecModemControlUsedCount();

	return (RCV_BLOCK);
}

/*************************************************************************
	module		:[]
	function	:[
		1.モデム内部コントロールの読みだし位置に示される、バッファアドレスとデータ数で
		, モデムＤＭＡ設定する
		2.モデムＤＭＡマスク解除する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/21]
	author		:[曽根岡拓]
*************************************************************************/
void 	RxG3_Start(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	ModemWriteDMA_Data.Channel		= DMA_CH_RX;
	ModemWriteDMA_Data.DstAddress	= (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0];	/*	絶対アドレスに変換	*/
	ModemWriteDMA_Data.SrcAddress	= ModemWriteDMA_Data.DstAddress; /* SrcAddress will be referred in DMA_SetupDMAU() */
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
	ModemWriteDMA_Data.Counter		= MDM_ModemDmaSize;	 /* 普通は 256 byte . CLASS1 で応答時間の厳しいときはそれより少ない。*/
#else
	ModemWriteDMA_Data.Counter		= MODEM_DMA_SIZE;	/** 256 Bytes **//* By H.Kubo 1997/06/25 for DMA routine of Atlanta*/
#endif
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_IO_TO_MEMORY;
	DMA_SetupDMAU( &ModemWriteDMA_Data );

	/* Added by H.Kubo 1997/10/08
	**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(RX_DMA);
#else
	SetModemDMA_DirectionRx();
#endif
	/*--------------------------------------*/
	/*	モデムバッファ－＞モデムＤＭＡ起動	*/
	/*--------------------------------------*/
	DMA_RequestEnable(DMA_CH_RX); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */
}


/*************************************************************************
	module		:[Ｇ３受信モデムクローズ]
	function	:[
		1.ＦＳＫ受信モードに設定する
		2.モデム受信ＤＭＡをマスクする
		3.モデム割り込みをマスクする
	]
	return		:[
		無し
	]
	common		:[
		ModemBlock.Chain
	]
	condition	:[]
	comment		:[]
	prototype	:[void near	RxG3_Close(void){}]
	date		:[1994/01/12]
	update		:[1996/03/01]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void 	RxG3_Close(void)
{
	/* FM336PLUS NEWCロックアップ不具合対策 2003/02/07 NEWC_LOCKUP_BUG_FIX */
	UBYTE is_ok;
	UWORD counter;

	ModemBlock.Mode = 0;	/* 1997/02/10 Y.Murata */

	/* 受信レベルのシフト 1997/01/28 Y.Murata */
	MDM_ReSetReceiveLevelExtension();

	/** For V29 7200 start by O.kimoto 1997/02/27 */
	if (!( SYS_V34ProcedureExecuting())) {
		if ( ModemBlock.Config == BPS7200_V29 ) {
				DspRamAccessWriteMethod1( 0x10D, 0x00, 0xFB );	/** P.4-43 F. */
		}
	}
	/** For V29 7200 end by O.kimoto 1997/02/27 */

	/* FM336PLUS NEWCロックアップ不具合対策 2003/02/07 NEWC_LOCKUP_BUG_FIX
	** RLSD OFF後7～8msの間行われるドロップアウト処理に不具合があり、NEWC割り込みフラグが
	** リセットされ、ロックアップしていた。
	** RLSD OFF後、最低10ms待つことで、ロックアップを回避します。
	** 2003/03/10 T.Takagi
	*/
	is_ok = 0;
	counter = 0;
	while (1) {
		if (!MDM_GetIO(POS_RLSD)) {
			is_ok++;
			if (is_ok > 2) {	/* 最低10ms待ちます */
				break;
			}
		}
		else {
			is_ok = 0;
			counter++;
			if (counter > 10) {	/* 100ms間で、RLSDのOFFをみつけられなかったときは、強制的にループ脱出 */
				break;
			}
		}
		wai_tsk(1);
	}

	MDM_InitialConfig();		/**	ＦＳＫ受信モード設定	*/
	DMA_RequestMask( DMA_CH_RX );	/**	モデム受信ＤＭＡをマスクする	*/ /* Modified by H. Kubo 1997/06/24 */
	ModemBlock.Chain = CHAIN_ON;		/**		*/
	MDM_SetIO( POS_NSIE,OFF );		/**	モデム割り込みをマスクする	*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS /*THERMAL*/) || (PRO_PRINT_TYPE == THERMAL)	/*  プリントデコード停止要求フラグ落とす By H.Kubo  1998/10/26 */
/* ported for HINOKI2 2001/12/26 T.Takagi */
	SYS_PRN_StopRequestFromModem = FALSE;
#endif
	
#if defined (KEISATSU) /* 警察FAX 05/06/20 石橋正和 */
	if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
		S1_CloseG3Rx(); /* S1クローズ */
		
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
	}
	else {
		SetDTC_IntFromModem(); /* DTC割り込みをモデムからにする */
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
	}
#endif
}


/*************************************************************************
	module		:[モデムクローズまでのウエイト時間]
	function	:[
		1.海外認可共通対応		FOREIGN_APPROVAL No.1-2
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[MDM]
	date		:[1994/01/12]
	author		:[村田]
*************************************************************************/
void	MDM_ModemTxCloseWait(void)
{
	UWORD	time;

#if 0	/* とりあえず なし。 これかぶってる */
//	time = (UWORD)SYB_MaintenanceSwitch[16];
//	if (time) {
//		wai_tsk(time);
//	}
#endif
}

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* by H.Kubo 1999/03/20 *//* 2002/09/18 By M.Maeda */
		/* SAKAKI プリンタ受信で受信画が壊れる対策。記録紙の準備ができる前に
		** モデムバッファ溢れが起こるので、モデムバッファの空きが少なくなったら
		** モデムバッファに溜まった受信データを ECM バッファに待避します。
		** プリンタ受信のない機種では必要ないでしょう。また、 POPLAR_H の
		**  ECM バッファの使い方とは共存できないので注意してください。
		** by H.Kubo 1999/03/20
		*/

/*************************************************************************
	module		:[Ｇ３受信時にＥＣＭバッファからコーデックへのＤＭＡの転送バイト数の計算]
	function	:[
	]
	return		:[
			ＤＭＡ転送のバイト数
	]
	common		:[
		EcmBufferBaseWritePoint :	すでに貯えられているデータの最下位アドレス
		EncodeDataCount			:	すでに貯えられているデータのバイト数
		EcmBuffer
	]
	condition	:[]
	comment		:[
		Ｇ３プリンタ受信で使います。
	]
	prototype	:[]
	date		:[1999/03/20]
	update		:[1999/03/20]
	author		:[久保博]
*************************************************************************/
UWORD MDM_G3Rx_EcmBufToCdcDmaCount(void)
{
	if ((EcmBufferBaseWritePoint + EncodeDataCount) >
		(ECM_BUFFER_AREA_START_ADDRESS + (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX))
	) {
		return (UWORD) ((ECM_BUFFER_AREA_START_ADDRESS + (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX)) - EcmBufferBaseWritePoint);
	}
	else {
		return (UWORD) EncodeDataCount;
	}
}

/*************************************************************************
	module		:[引数のバッファの内容をＥＣＭバッファに転送する]
	function	:[
		転送データが EcmBuffer の末尾を超えたら、残りの部分を EcmBuffer の先頭に折り返してコピー。
	]
	return		:[
		無し
	]
	common		:[
		EcmBufferBaseWritePoint :	すでに貯えられているデータの最下位アドレス
		EncodeDataCount			:	すでに貯えられているデータのバイト数
		EcmBuffer
		ModemControl
		ModemRxStatus
	]
	condition	:[]
	comment		:[
		Ｇ３プリンタ受信で使います。
	]
	prototype	:[]
	date		:[1999/03/20]
	update		:[1999/03/20]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_G3Rx_bufferToEcmBuffer(UBYTE *src_addr, UWORD count)
{
	UDWORD rest_length; /* EcmBuffer のアドレス上位部分の連続した空き領域 */
	UDWORD free_length;
	free_length = (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX) - EncodeDataCount;
	if (free_length < count) {
		return FALSE;
	}

	if (EcmBufferBaseWritePoint + EncodeDataCount >= (ECM_BUFFER_AREA_START_ADDRESS + (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX))) {
		MemoryMove((((UBYTE *)EcmBufferBaseWritePoint) + EncodeDataCount - (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX)), src_addr, count);
	}
	else {
		rest_length = (UDWORD) ((ECM_BUFFER_AREA_START_ADDRESS + (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX)) - (EcmBufferBaseWritePoint + EncodeDataCount));
		if (rest_length >= count) { /* EcmBuffer の連続した空き領域に納まる場合 */
			MemoryMove(((UBYTE *)EcmBufferBaseWritePoint) + EncodeDataCount, src_addr, count);
		}
		else { /* EcmBuffer の末尾から先頭にまたがる場合 */
			MemoryMove(((UBYTE *)EcmBufferBaseWritePoint) + EncodeDataCount, src_addr, (UWORD) rest_length);
			MemoryMove(((UBYTE *)&EcmBuffer[0][0]), src_addr + rest_length, (UWORD) (count - rest_length));
		}
	}
	EncodeDataCount += count;
	return TRUE;
}

/*************************************************************************
	module		:[G3 受信ＥＣＭバッファからコーデックへのＤＭＡ転送の終了処理]
	function	:[
	]
	return		:[
		無し
	]
	common		:[
		EcmBufferBaseWritePoint
		EncodeDataCount
		MDM_ModemBuffer
		EcmBuffer
		ModemControl
		ModemRxStatus
	]
	condition	:[]
	comment		:[
		Ｇ３プリンタ受信で使います。
	]
	prototype	:[]
	date		:[1999/03/20]
	update		:[1999/03/20]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_G3RxNextDmaFromEcmBuffer(void)
{
	UWORD dma_byte_count;
	if (EncodeDataCount == 0) {
		DMA_RequestMask(DMA_CH_DEC);	/* Memory to CODEC の DMA を停止 */
		dma_byte_count = 2 * DMA_CheckDMA_Counter(DMA_CH_DEC); /* ワード転送を想定。 */
		if (dma_byte_count > 0) {
			DMA_Continue(DMA_CH_DEC);
			return TRUE;
		}
		return FALSE;
	}
	else {
		DMA_RequestMask(DMA_CH_DEC);	/* Memory to CODEC の DMA を停止 */
		dma_byte_count = 2 * DMA_CheckDMA_Counter(DMA_CH_DEC); /* ワード転送を想定。 */
		if (dma_byte_count > 0) { /* まだ途中なら */
			DMA_Continue(DMA_CH_DEC); /* 続きをやる。*/
			return TRUE;
		}
		else {
			/**********************************************************************/
			/* ECM バッファに待避したデータを CODEC に転送する DMA を起動  */
			/**********************************************************************/
			dma_byte_count = MDM_G3Rx_EcmBufToCdcDmaCount();
			DMA_SetDMA_Counter(DMA_CH_DEC, dma_byte_count / 2);
			DMA_SetDMA_Address(DMA_CH_DEC, DMA_MEMORY_TO_IO, EcmBufferBaseWritePoint);
			DMA_RequestEnable(DMA_CH_DEC);	 /**	通信コーデック復号化Ｖ５３ＤＭＡ起動	*/
			/**********************************************************************/
			/* ECM バッファの管理変数を更新  */
			/**********************************************************************/
			if (EncodeDataCount > dma_byte_count) { /* EcmBuffer の折り返しがあったら */
				EcmBufferBaseWritePoint = (UDWORD) &EcmBuffer[0][0];
			}
			else {
				EcmBufferBaseWritePoint += dma_byte_count;
			}
			EncodeDataCount -= dma_byte_count;
			return TRUE;
		}
	}
}

/*************************************************************************
	module		:[G3 受信でコーデックへの画データ転送元をモデムバッファからＥＣＭバッファに切り替える]
	function	:[
		1. モデムバッファの残り本数を検査する。
		2. 残り本数少なければ、受信済データを ECM バッファに待避する。
		3. モデムバッファを解放する。
		3. ModemBuffer => Codec の DMA を EcmBuffer => Codec に切り替える
	]
	return		:[
		無し
	]
	common		:[
		EcmBufferBaseWritePoint
		EncodeDataCount
		MDM_ModemBuffer
		EcmBuffer
		ModemControl
		ModemRxStatus
	]
	condition	:[]
	comment		:[
		Ｇ３プリンタ受信で使います。
	]
	prototype	:[]
	date		:[1999/03/20]
	update		:[1999/03/20]
	author		:[久保博]
*************************************************************************/
CONST UBYTE MDM_G3Rx_DebugSwitch = 0; /* ECM バッファに受信データをすべてはる時に 1 にしてください by H.Kubo 1999/03/30 */
UBYTE MDM_G3RxModemBufferToEcmBuffer(void)
{
	UWORD 	dma_byte_count;
	UWORD 	mem_move_byte_count;
	UWORD	data_from_mdmbuf_count;
	UDWORD	dma_address;
	UBYTE wrkmsk;
	UBYTE rtn = TRUE;

	dma_byte_count = 0;
	mem_move_byte_count = 0;

	if ((ModemControl.UsedCount > 4) || MDM_G3Rx_DebugSwitch) { /* 残り本数が少ない */
		/**********************************************************************/
		/* Memory to CODEC の DMA で転送していないデータを ECM バッファに待避 */
		/**********************************************************************/
		DMA_RequestMask(DMA_CH_DEC);	/* Memory to CODEC の DMA を停止 */
		dma_byte_count = 2 * DMA_CheckDMA_Counter(DMA_CH_DEC); /* ワード転送を想定。 */
		dma_address = DMA_CheckDMA_Address(DMA_CH_DEC, DMA_MEMORY_TO_IO);
		if ((dma_address < ECM_BUFFER_AREA_START_ADDRESS) 
		||	 dma_address > (ECM_BUFFER_AREA_START_ADDRESS + (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX))) {
			if (dma_byte_count > 0 ) {
				rtn =  MDM_G3Rx_bufferToEcmBuffer((UBYTE *)dma_address , dma_byte_count);
				if (rtn == FALSE) {
					DMA_Continue(DMA_CH_DEC);
					return;
				}
			}
			dma_byte_count = 0;
			dma_address = EcmBufferBaseWritePoint;
		}
		if (MDM_G3Rx_DebugSwitch && ((dma_address + dma_byte_count) != EcmBufferBaseWritePoint)) { /* For debug, added by H.Kubo 1999/03/30 */
			rtn = FALSE;			/* ECM バッファが一周するまでにここに来たらおかしい */
		}
		/**********************************************************************/
		/* モデムバッファに溜まったデータを ECM バッファに待避 */
		/**********************************************************************/
		wrkmsk = (UBYTE)(1 << ModemControl.ReadPoint); 
		if (MDM_G3Rx_DebugSwitch) { /* For debug, added by H.Kubo 1999/03/30 */
			while ((ModemRxStatus & wrkmsk) && ((CodecPageStatus == CDC_CONTINUE) || (CodecPageStatus == CDC_READY)) ) {
				wai_tsk(1); /* モデムバッファにデータが来るまで待つ */
			}
		}
		while (!(ModemRxStatus & wrkmsk)) {
			rtn = MDM_G3Rx_bufferToEcmBuffer(MDM_ModemBuffer[ModemControl.ReadPoint], MDM_RxSize[ModemControl.ReadPoint]);
			if (rtn == TRUE) { /* モデムバッファを解放 */
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				ModemRxStatus |= wrkmsk;
				DecModemControlUsedCount();
				NextMdmBufReadPointSetExtRom();
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				wrkmsk = (UBYTE)(1 << ModemControl.ReadPoint); 
			}
			else {
				break;
			}
		}
		/**********************************************************************/
		/* ECM バッファに待避したデータを CODEC に転送する DMA を起動  */
		/**********************************************************************/
		data_from_mdmbuf_count = MDM_G3Rx_EcmBufToCdcDmaCount();
		/* DMA のカウンタに 0 を入れないようにします by H.Kubo 1999/03/30 */
		if ((dma_byte_count += data_from_mdmbuf_count) > 0) {
			DMA_SetDMA_Counter(DMA_CH_DEC, dma_byte_count / 2);
			DMA_SetDMA_Address(DMA_CH_DEC, DMA_MEMORY_TO_IO, dma_address);
			DMA_RequestEnable(DMA_CH_DEC);	 /**	通信コーデック復号化Ｖ５３ＤＭＡ起動	*/
		}
		else {
			return FALSE;
		}

		/**********************************************************************/
		/* ECM バッファの管理変数を更新  */
		/**********************************************************************/
		if (EncodeDataCount > data_from_mdmbuf_count) { /* EcmBuffer の折り返しがあったら */
			EcmBufferBaseWritePoint = (UDWORD) &EcmBuffer[0][0];
		}
		else {
			EcmBufferBaseWritePoint += data_from_mdmbuf_count;
		}
		EncodeDataCount -= data_from_mdmbuf_count;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

#endif /* (PRO_PRINT_TYPE == THERMAL_TRANS) */
