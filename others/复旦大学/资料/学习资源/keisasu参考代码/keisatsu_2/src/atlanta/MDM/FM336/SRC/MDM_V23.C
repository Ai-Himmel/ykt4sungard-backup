/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_v23.c                                                 */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ナンバーディスプレイ用Ｖ２３受信関連処理                  */
/*  修正履歴     : 2002/01/19 HINOKI2で使用するためNAGANOからフィードバック  */
/*	keyword      :[MDM]                                                      */
/*	machine      :[SH7043]                                                   */
/*	language     :[SHC]                                                      */
/*---------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\define\mdm_bps.h"
#include "\src\atlanta\mdm\fm336\define\mdmnddef.h"

#include "\src\atlanta\define\mon_pro.h"

void 	MDM_TxV23Start(void);
void MDM_RxV23Open(void);
void MDM_RxV23Close(void);
UBYTE MDM_ND_Read(UWORD dma_end_time);


/********
** define
********/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h" /* added by H.Kubo 1998/11/14 */
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

CONST UBYTE v23_rx_gain = 0;
extern UBYTE v23_rx_by_dma;

/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３受信モデムオープン]
	function	:[
		1.Ｖ２３受信モードでモデムを設定する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemBlock
		ModemRxStatus
	]
	condition	:[]
	comment		:[]
	date		:[1998/06/23]
	author		:[久保博]
*************************************************************************/
CONST UBYTE dma_enable_prior = 0;
void MDM_RxV23Open(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	SYS_V34ProcedureExecutingFlag = 0; /* これが下がっていないと、正しく動きません。added by H.Kubo 1998/11/14 */

	/**	モデムバッファ読み出し位置初期化	*/
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), (UBYTE) 0x00);
#if (PRO_CLASS1 == ENABLE)
	MDM_ModemBufferFirstPoint = 0; /* FSK の処理ではモデムバッファの先頭位置が固定。*/
#endif

	/*	モデム受信ステータス初期化	*/
	ModemRxStatus = 0xff;

	/**	モデムタイプ、速度設定	*/
	ModemTypeSet(TX1200_V23);	/**	V23 モードに設定。 TX1200_V23 は間違いではない。ロックウェルからの指示。	*/

	/*	モデムステータス設定　
	**　　　　　　　　　　　　単独コマンド／レスポンス
	*/
	ModemControl.Status = STAT_REQRES;

	/*	交信モードをナンバーディスプレイ情報受信に設定	*/
	ModemInterruptFlag = 0;
	ModemBlock.Mode = MODE_RX_ND;

	/**	モデムコンフィグレーション実行	*/
	
	ModemConfig(READ_MODE);

	MDM_SetMaskingRegsiter0A0B(0x104B); /** ATV25/FLAGDT,FLAGS,SYNCD,OE **/ /* added by H.Kubo 1998/10/27 */


	if (v23_rx_by_dma){
		ModemWriteDMA_Data.Channel		= DMA_CH_RX;
		ModemWriteDMA_Data.DstAddress	= (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0];	/*	絶対アドレスに変換	*/
		ModemWriteDMA_Data.SrcAddress	= ModemWriteDMA_Data.DstAddress; /* SrcAddress will be referred in DMA_SetupDMAU() */
		ModemWriteDMA_Data.Counter		= ND_MODEM_DMA_SIZE;
		ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
		ModemWriteDMA_Data.Direction	= DMA_IO_TO_MEMORY;
		DMA_SetupDMAU(&ModemWriteDMA_Data);

#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
		SelectDreqDirection(RX_DMA);
#else
		SetModemDMA_DirectionRx();
#endif
		/*--------------------------------------*/
		/*	モデムバッファ－＞モデムＤＭＡ起動	*/
		/*--------------------------------------*/
	
		if (dma_enable_prior){
			DMA_RequestEnable(DMA_CH_RX); /* Modified by H. Kubo for POOPLAR_H 1997/06/24 */
		}
		MDM_SetIO(POS_NSIE,ON);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */
	
		/* 一つ目のデータを受信したら、モデム割り込みが入るように設定します。 */
		if (MDM_DmaStart == MDM_DMA_MASK) {
			CMN_DisableInterrupt();
			MDM_SetIO(POS_RDBIE,ON);
			MDM_DmaStart = MDM_DMA_READY; /* モデム割り込みで DMA を起動します。*/
			CMN_EnableInterrupt();
		}
	}
	else {
		MDM_ND_WaitFirstDataEvent = TRUE;
		MDM_SetIO(POS_NSIE,ON);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */
		MDM_SetIO(POS_RDBIE,ON);
	}
}

/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３受信モデムクローズ]
	function	:[
		1.ＤＭＡ終了処理
		2.モデムコンフィグレーション再設定
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1998/06/23]
	author		:[久保博]
*************************************************************************/
void MDM_RxV23Close(void)
{
	UWORD count;

	ModemBlock.Mode = 0;	/* 1997/02/10 Y.Murata */

	/**	モデム－＞モデムバッファＤＭＡ終了	*/
	DMA_RequestMask(DMA_CH_RX);

	/** ＤＭＡ起動処理 By O.K Jan.26,1996 **/
	MDM_SetIO(POS_RDBIE,OFF);
	MDM_DmaStart = MDM_DMA_MASK;

	MDM_ND_WaitFirstDataEvent = 0; /* 1998/09/25 */

	MDM_SetIO(POS_NSIE,OFF);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */
	MDM_SetIO(POS_NSIA,OFF);	/* テスト的に入れてみます。 by H.Kubo 1998/10/19 */
	MDM_SetIO(POS_NEWS,OFF);	/* テスト的に入れてみます。 by H.Kubo 1998/10/19 */

	/* 以下のコードはＲｏｃｋｗｅｌｌのソースより移植 By O.K Feb.17,1996 */
	for( count=0; count<256; count++ ) { /* ExFIFO 用に 255 byte 吐き出すように変更。 by H.Kubo 1998/10/19 */
		(void)inp(MDM_REG_0A_PORT); /* 効果は分かりませんが、念のため入れます。 by H.Kubo 1998/10/19 */
		(void)inp(MDM_REG_00_PORT);
	}

	/* 効果は分かりませんが、入れてみます。 by H.Kubo 1998/11/13 */
	MDM_SetRxFIFOClear();

	/** ＦＡＸ本体が着信できないとき、ＤＴＲが立ちっぱなしになり、
	** 待機状態に戻っても、ANSamが出っぱなしになる
	** DTR OFF added by H.Hirao 1998/12/21
	** Moved by H.Kubo 1998/12/21
	*/
	MDM_SetIO(POS_DTR, OFF);

	MDM_SetIO(POS_TXSQ, OFF); /* 送信スケルチを戻します。 by H.Kubo 1998/11/14 */

	/**	モデムクローズ処理	*/
	MDM_InitialConfig();
}

UBYTE MDM_ND_Read(UWORD dma_end_time)
{
	UBYTE	wrkmsk;
	UWORD	tmoutc;
	UWORD	dma_cnt;
	UBYTE 	test_sw;

	test_sw = 0;
	tmoutc = 0;
	
	/*------------------------------*/
	/**	該当受信位置設定	*/
	/*------------------------------*/

	wrkmsk = (UBYTE)(1 << ModemControl.ReadPoint);

	while (ModemRxStatus & wrkmsk) {
		if (tmoutc > dma_end_time) {	/* DMA転送時間経過 */
			/* DMA Disable */
			DMA_RequestMask(DMA_CH_RX);
			CMN_DisableInterrupt();		/* DI */
			if (ModemRxStatus & wrkmsk) {
				dma_cnt = DMA_CheckDMA_Counter(DMA_CH_RX); /*未転送バイト数 */
#if (PRO_CLASS1 == ENABLE) /* by H.Kubo  */
				MDM_RxSize[ModemControl.WritePoint] = MDM_ModemDmaSize - dma_cnt;
#else
				MDM_RxSize[ModemControl.WritePoint] = ND_MODEM_DMA_SIZE - dma_cnt;
#endif
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
				NextMdmBufWritePointSetExtRom();
				ModemControl.UsedCount++;
				MDM_DmaStart = MDM_DMA_MASK;
				CMN_EnableInterrupt();		/* EI */
			}
			else {
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif
				DMA_RequestEnable(DMA_CH_RX);
				CMN_EnableInterrupt();
			}
			break;
		}
		/* モデムバッファ溢れを監視。*/
		if (ModemControl.UsedCount > 8) {
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_MODEM_BUFFER_OVERLOW;
		}
		tmoutc++;
		wai_tsk(10/10);
	}

	/*------------------------------*/
	/**	該当受信ステータス初期化	*/
	/*------------------------------*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	ModemRxStatus |= wrkmsk;
	ModemControl.UsedCount--;
	CMN_EnableInterrupt();	/**	割り込み許可	*/
	return (RCV_BLOCK);
}


/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３受信]
	function	:[
		モデムの RBUFFER から受信データをモデムバッファに読み込む
	]
	return		:[
		RCV_BLOCK		ND_MODEM_DMA_SIZE バイト読み込んだ
		RCV_TMOUT		受信データを ND_MODEM_DMA_SIZE バイト読む前にタイムアウトした
	]
	common		:[]
	condition	:[]
	comment		:[NAGANOよりフィードバック 2002/01/19 T.Takagi]
	date		:[1998/06/23]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_ModemRead(UWORD end_time)
{
	UWORD timeout;
	UWORD buffer_pos;
	
	buffer_pos = 0;
	for (timeout = end_time; timeout > 0; timeout--) {
		if (buffer_pos >= ND_MODEM_DMA_SIZE) {
			break;
		}
		while (MDM_GetIO(POS_RXFNE)) {
			MDM_ModemBuffer[ModemControl.WritePoint][buffer_pos++] = MDM_GetIO(POS_RBUFFER);
			timeout = ND_RX_OCTET_TIMEOUT; /* 1byte 受信した後は、 ND_RX_OCTET_TIMEOUT だけ次のデータを待つ */
			if (buffer_pos >= ND_MODEM_DMA_SIZE) { /* FIFO 監視ループ内でバッファがいっぱいになったら抜ける。 by H.Kubo 1999/10/13 */
				break;	/* NAGANOよりフィードバック 2002/01/19 T.Takagi */
			}
		}
		wai_tsk(10/10); /* 10ms 待つ */
	}
	CMN_DisableInterrupt();
	MDM_RxSize[ModemControl.WritePoint] = buffer_pos;
	NextMdmBufWritePointSetExtRom();
	IncModemControlUsedCount();	/* ModemControl.UsedCount++ NAGANOよりフィードバック 2002/01/19 T.Takagi */
	CMN_EnableInterrupt();
	if (buffer_pos >= ND_MODEM_DMA_SIZE) {
		return RCV_BLOCK;
	}
	return RCV_TMOUT;
}


/*******************   ナンバーディスプレイで使う関数はここまで。 ******************************/

#if 0 /* ナンバーディスプレイで使いません。 */
/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３送信モデムオープン]
	function	:[
		1.Ｖ２３送信モードでモデムを設定する
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
		ModemBlock
		ModemRxStatus
	]
	condition	:[]
	comment		:[]
	date		:[1998/08/24]
	author		:[久保博]
*************************************************************************/
void MDM_TxV23Open(void)
{
	/**	モデムバッファ読み出し位置初期化	*/
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), ( char )0x00);
#if (PRO_CLASS1 == ENABLE)
	MDM_ModemBufferFirstPoint = 0; /* FSK の処理ではモデムバッファの先頭位置が固定。*/
#endif

	/*	モデム受信ステータス初期化	*/
	ModemRxStatus = 0xff;

	/**	モデムタイプ、速度設定	*/
	ModemTypeSet(TX1200_V23);	/**	V23 モードに設定	*/

	/*	交信モードをナンバーディスプレイ情報受信に設定	*/
	ModemInterruptFlag = 0;
	ModemBlock.Mode = MODE_RX_ND;

	/**	モデムコンフィグレーション実行	*/
	
	ModemConfig(READ_MODE);

	MDM_SetIO(POS_NSIE,ON);	/* ﾓﾃﾞﾑ割り込みをON/OFFします By O.K Feb.20,1996 */
}

/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３送信モデムクローズ]
	function	:[
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1998/08/24]
	author		:[久保博]
*************************************************************************/
void 	MDM_TxV23Close(void)
{
	if (TxCompleteEventFlag == 0) {
		wai_evt(EVT_TX_COMPLETE);
	}
	/*--------------------------------------*/
	/**	モデム－＞モデムバッファＤＭＡ終了	*/
	/*--------------------------------------*/
	DMA_RequestMask(DMA_CH_TX); /* 1st argument MASTER_DMAU is deleted by H. Kubo 1997/05/24 */
	/*----------------------------------*/
	/*	モデムバッファセマフォリセット	*/
	/*----------------------------------*/
	ResetModemBufferSem();

	MDM_InitialConfig();
	MDM_SetIO(POS_NSIE,OFF); /* モデムレジスタが変化しても割り込みをかけないようにする。 */
}


/*************************************************************************
	module		:[Ｖ２３送信モデムライト]
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
	date		:[1998/08/24]
	author		:[久保博]
*************************************************************************/
void 	MDM_TxV23Write(
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
#if (0)	/* Remane By O.Kimoto 1997/12/22 */
**	NextModemBufferWritePointSet();	/**	モデムバッファ書き込み位置更新	*/
#else
	NextMdmBufWritePointSetExtRom();
#endif

	/*----------------------*/
	/*	送信ＤＭＡ起動処理	*/
	/*----------------------*/
	if (!(ModemControl.Status & STAT_ACT)) {	/**	モデムがＩＤＬＥ状態の時	*/
		MDM_TxV23Start();	/**	送信ＤＭＡ起動	*/
	}
	CMN_EnableInterrupt();	/**	割り込み許可	*/
}

/*************************************************************************
	module		:[Ｖ２３送信モデムスタート]
	function	:[
	]
	return		:[
		なし
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[]
	date		:[1998/08/24]
	author		:[久保博]
*************************************************************************/
void 	MDM_TxV23Start(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;
	
	/*--------------------------*/
	/*	モデムＶ５３ＤＭＡ設定	*/
	/*--------------------------*/
	ModemControl.Status |= (STAT_ACT + STAT_FRSTON);
	ModemWriteDMA_Data.Channel		= DMA_CH_TX;
	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;
	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount;
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	/*----------------------------------*/
	/*	モデムＶ５３ＤＭＡマスク解除	*/
	/*----------------------------------*/
	DMA_RequestEnable(DMA_CH_TX); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */
}
#endif /* 0 */

#if 0
CONST UBYTE V23_TxTest[] = "\010\\007\001\020\\040\014\\002\012075672824\010003";

void MDM_ND_TestTxV23(void)
{
	UDWORD i;
	UDWORD bit_pos;
	union w_data_t tx_crc;

	bit_pos = 0;
	
	MDM_TxV23Open();

	for (i = 0; i < sizeof (V23_TxTest_Preamble); i++) {
		MDM_ModemBuffer[0][i] = '\255';
	}

	for (i = 0; i < sizeof (V23_TxTest_Preamble) && V23_TxTest[i] != '\0'; i++) {
		MDM_ND_InsertStartStopBits(MDM_ND_SetParity(V23_TxTest[i]), &MDM_ModemBuffer[1][0], &bit_pos);
	}
	tx_crc = crc(i, MDM_ModemBuffer[1][0]);
	MDM_ModemBuffer[1][bit_pos / 8] = tx_crc.byte_data.h_data;
	MDM_ModemBuffer[1][bit_pos / 8 + 1] = rx_crc.byte_data.l_data;


	MDM_TxV23Write(&MDM_ModemBuffer[0][0], 256);
	MDM_TxV23Write(&MDM_ModemBuffer[0][0], (UWORD)(bit_pos / 8 + 2));

	MDM_TxV23Close();
}
#endif /* 0 */

