/**********************************************************************************************************************
	@(#)$Id: s1_int.c,v 1.5 2005/11/22 02:25:01 mi93007 Exp $
	Create        : 2005/07/01
	Author        : 石橋正和
	Description   : S1割込み処理
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

/**************************************************************************************************/
/**
	@brief		S1割込み処理
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/01 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_Interrupt(void)
{
	UBYTE int_kind;
	UBYTE int_factor;
	UBYTE status;
	
	UWORD rtn;
	
	rtn = 0;
	
	int_kind = S1_GetInterruptKind(); /* 割込み種別を得る */
	
	switch (ModemBlock.Mode) { /* 交信モード */
	case MODE_RX_G3:
		if (!(int_kind & S1_REG_BIT_IRRX_SCI)) { /* SCI受信部の割り込みでない場合 */
			break;
		}
		int_factor = S1_SCI_GetIntFactor(); /* 割込み要因を得る */
		status = S1_SCI_GetRxStatus(); /* 受信ステータスを得る */
		if (int_factor & S1_REG_BIT_SCI_OVERQ) { /* オーバーランエラーの場合 */
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* メンテナンススイッチに通知 */
		}
		S1_SCI_ClearRxStatus(); /* 受信ステイタスクリア */
		break;
	case MODE_TX_G3:
		if (!(int_kind & S1_REG_BIT_IRTX_SCI)) { /* SCI送信部の割り込みでない場合 */
			break;
		}
		int_factor = S1_SCI_GetIntFactor(); /* 割込み要因を得る */
		status = S1_SCI_GetTxStatus(); /* 受信ステータスを得る */
		if (int_factor & S1_REG_BIT_SCI_UNERQ) { /* アンダーランエラーの場合 */
			
			
			
		}
		if (int_factor & S1_REG_BIT_SCI_TXENDRQ) { /* TxEND(送信すべきデータがない)の場合 */
			
			
			
		}
		S1_SCI_ClearTxStatus(); /* 送信ステイタスクリア */
		break;
	case MODE_RX_ECM:
		if (!(int_kind & S1_REG_BIT_IRRX_HDLC)) { /* HDLC受信部の割り込みでない場合 */
			break;
		}
		status = S1_HDLC_GetRxStatus(); /* 受信ステータスを得る */
		
		if (status & S1_REG_BIT_HDLC_EOF) { /* フレーム終了 */
			if ((MDM_DmaStart != MDM_DMA_MASK) && !(status & S1_REG_BIT_HDLC_CRC)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
				/* ここに来るまでに次のフレームの先頭データを受信したときの処理を追加。 Changed by H.Kubo 1999/01/26 */
				/* DMA(DTC) はここで止めないといけない。カウンタを読んでからマスクするまでの間に次の DREQ が来たら
				** 終了割り込みがかかることがある。
				** by H.Kubo 1999/01/26 */
				DMA_RequestMask(DMA_CH_RX);
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				ModemControl.UsedCount++;
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
					/* フレーム最後のフラグを受信してからここに来るまでの間に次のフレームの先頭を受信していたら、
					** 次のフレームの先頭は次のモデムバッファにコピーして残りのデータの受信を始めます。
					** そうでなければ、次のフレームは普通に次のモデムバッファの先頭から受信し始めます。
					** by H.Kubo 1999/01/26
					*/
				if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
					&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
					/* 次のアドレスフィールドのデータが末尾にある場合 */
					MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
					MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のモデムバッファに移した分だけ引き算します。 */
					NextMdmBufWritePointSetExtRom();
					MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
				}
				else {
					NextMdmBufWritePointSetExtRom();
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
				}
				MDM_DmaStart = MDM_DMA_GO;
			}
			else {
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
				SelectDreqDirection(RX_DMA);
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
				MDM_DmaStart = MDM_DMA_GO;
			}
		}
		else if (status & (S1_REG_BIT_HDLC_CRC | S1_REG_BIT_HDLC_OER | S1_REG_BIT_HDLC_SFER | S1_REG_BIT_HDLC_ADET)) {
			DMA_RequestMask(DMA_CH_RX);
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			/* DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize + 4), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]); */
			MDM_DmaStart = MDM_DMA_GO;
			if (status & S1_REG_BIT_HDLC_OER) {
				SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN;
			}
		}
		S1_HDLC_ClearRxStatus(); /* 受信ステータスクリア */
		
		
		
		if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
			MDM_SetIO(POS_RDBIE,OFF);
			MDM_DmaStart = MDM_DMA_CONTINUE;
		}
		
		
		
		break;
	case MODE_TX_ECM:
		if (!(int_kind & S1_REG_BIT_IRTX_HDLC)) { /* HDLC送信部の割り込みでない場合 */
			break;
		}
		
		status = S1_HDLC_GetTxStatus();
		
#if 0
		if (status & S1_REG_BIT_HDLC_TXEND) {
			if (ModemControl.Status & STAT_ALSENT) {			/**	送出データがセット済みの時	*/
				ModemControl.Status &= (~STAT_ALSENT);		/**	ＦＣＳ割り込み待ち解除	*/
				ModemInterruptFlag = 1;						/**	モデム割り込み発生フラグセット	*/
				MDM_SetIO(POS_TEOF,OFF);
				rtn |= MDM_EVT_TX_FCS_COMPLETE_BIT;		/* V21ch2 フラグ(7E) 検出 */
			}
			S1_HDLC_ClearTxStatus(S1_REG_BIT_HDLC_TXEND);
		}
		
		
		
		if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
			MDM_SetIO(POS_RDBIE,OFF);
			MDM_DmaStart = MDM_DMA_CONTINUE;
		}
		
		
		
#endif
		break;
	case 0: /* モデムクローズした後の割込み(なぜか入ることがある) */
		if (int_kind & S1_REG_BIT_IRRX_HDLC) { /* HDLC受信部の割り込み */
			status = S1_HDLC_GetRxStatus(); /* 受信ステータスを得る */
			S1_HDLC_ClearRxStatus(); /* 受信ステータスクリア */
		}
		if (int_kind & S1_REG_BIT_IRTX_HDLC) { /* HDLC送信部の割り込み */
			status = S1_HDLC_GetTxStatus(); /* 送信ステータスを得る */
			S1_HDLC_ClearTxStatus(status); /* 送信ステータスクリア */
		}
		if (int_kind & S1_REG_BIT_IRRX_SCI) { /* SCI受信部の割り込み */
			status = S1_SCI_GetRxStatus(); /* 受信ステータスを得る */
			S1_SCI_ClearRxStatus(); /* 受信ステータスクリア */
		}
		if (int_kind & S1_REG_BIT_IRTX_SCI) { /* SCI送信部の割り込み */
			status = S1_SCI_GetTxStatus(); /* 送信ステータスを得る */
			S1_SCI_ClearTxStatus(); /* 送信ステータスクリア */
		}
		break;
	default:
		break;
	}
	
	S1_ClearInterrupt(); /* 割込みクリア */
	
	if (rtn != 0 ) {
		if ( (rtn & MDM_EVT_ATV25_DETECT_BIT) != 0 ) {
			idet_evt(EVT_MDM_ATV25);
		}
		if ( (rtn & MDM_EVT_MDM_PNSUC_BIT) != 0 ) {
			idet_evt(EVT_MDM_PNSUC);
		}
		if ( (rtn & MDM_EVT_TX_FCS_COMPLETE_BIT) != 0 ) {
			idet_evt(EVT_TX_FCS_COMPLETE);
		}
		if ( (rtn & MDM_EVT_RX_FLG_DETECT_BIT) != 0 ) {
			idet_evt(EVT_RX_FLG_DETECT);
		}
		if ( (rtn & MDM_EVT_RX_RDBF_BIT) != 0 ) {
			idet_evt(EVT_MDM_RX_NEW_DATA);
		}
	}
}



