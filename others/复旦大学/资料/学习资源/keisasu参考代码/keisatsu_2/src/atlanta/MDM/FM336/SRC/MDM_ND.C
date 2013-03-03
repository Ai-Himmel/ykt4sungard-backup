/*---------------------------------------------------------------------------*/
/*  プロジェクト : ATLANTA FM336                                             */
/*  ファイル名   : mdm_nd.c                                                  */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ナンバーディスプレイ受信関連処理                          */
/*  修正履歴     : 2002/01/19 HINOKI2で使用するためNAGANOからフィードバック  */
/*	keyword      :[MDM]                                                      */
/*	machine      :[SH7043]                                                   */
/*	language     :[SHC]                                                      */
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\mdm\fm336\define\mdmnddef.h"
#include "\src\atlanta\mdm\fm336\define\mdmndpro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\ncu_pro.h"


#include "\src\atlanta\mdm\fm336\define\mdm_io.h" /* For debug by H.Kubo 1998/08/27 */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* ナンバーディスプレイ */

/***********************
** ナンバーディスプレイ
***********************/
/*************************************************************************
	module		:[ナンバーディスプレーデータ受信]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[NAGANOよりフィードバック 2002/01/19 T.Takagi]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_ExtractDataOctet(UWORD dma_end_time, 
							UBYTE *data_status_ptr, 
							UBYTE *out_buffer, 
							UDWORD *bit_position_ptr)
{
	UBYTE	rtn;
	/* ND_MODEM_DMA_SIZE 分モデムバッファにデータが溜まるのを待ってもだめなら、タイムアウトする設定。 */
	rtn = MDM_ND_ModemRead(dma_end_time);
	/* モデムバッファにデータあり */
	if (MDM_RxSize[ModemControl.ReadPoint] > 0 ) {
		MDM_ND_ExtractDataFromBitStream(MDM_ModemBuffer[ModemControl.ReadPoint], 
										MDM_RxSize[ModemControl.ReadPoint],
										data_status_ptr,
										out_buffer,
										bit_position_ptr);
	}
#if 0 /* モデムバッファのリードポインタが進まず、全てのデータを受信しているのにタイムアウトする不具合対応 by H.Kubo 1999/10/13 */
@	if (RCV_BLOCK == rtn) { /* wait for MDM_ModemBuffer[ModemControl.ReadPoint] to be filled with Rx data. */
@		CMN_DisableInterrupt();
@		NextMdmBufReadPointSetExtRom(); /**	モデムバッファ読み出し位置更新	*/
@		ModemControl.UsedCount--;
@		CMN_EnableInterrupt();
@	}
#else
	CMN_DisableInterrupt();
	NextMdmBufReadPointSetExtRom(); /**	モデムバッファ読み出し位置更新	*/
	DecModemControlUsedCount(); /* ModemControl.UsedCount--; */
	CMN_EnableInterrupt();
#endif
	return rtn;
}

/*************************************************************************
	module		:[ナンバーディスプレーCRCチェック]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_CheckCRC(UBYTE *rx_buffer, UDWORD byte_count)
{
	if ( 0 == ND_CheckCRC16(rx_buffer, byte_count)) {
		return TRUE;
	}
	return FALSE;
}

/*************************************************************************
	module		:[ナンバーディスプレー データ終端判断処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_FindDleEtx(UBYTE *rx_buffer, UDWORD byte_count)
{
	if (((rx_buffer[byte_count - 1] & MDM_ND_PARTIY_MASK) == DLE) && ((rx_buffer[byte_count] &MDM_ND_PARTIY_MASK) == ETX)) {
		return TRUE;
	}
	return FALSE;
}


/*************************************************************************
	module		:[ナンバーディスプレー データ開始判断処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_FindDleSoh(UBYTE *rx_buffer, UDWORD byte_count)
{
	if (((rx_buffer[byte_count - 1] & MDM_ND_PARTIY_MASK) == DLE) && ((rx_buffer[byte_count] & MDM_ND_PARTIY_MASK)== SOH)) {
		return TRUE;
	}
	return FALSE;
}


/*************************************************************************
	module		:[ナンバーディスプレー 次処理判断]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
CONST UBYTE v23_check_parity = 1;

UBYTE MDM_ND_ExaminRxOctet(UBYTE rx_octet_status, UBYTE *rx_buffer, UDWORD byte_count)
{

	switch (rx_octet_status) {
	case ND_RX_STATUS_WAIT_1ST_BIT:
		rx_octet_status = ND_RX_STATUS_WAIT_HEADER;
		break;
	case ND_RX_STATUS_WAIT_HEADER:
		if (MDM_ND_FindDleSoh(rx_buffer, byte_count)) {
			rx_octet_status = ND_RX_STATUS_RECEIVING_DATA;
		}
		break;
	case ND_RX_STATUS_RECEIVING_DATA:
		if (!MDM_ND_CheckParity(rx_buffer[byte_count])) {
			if (v23_check_parity) {
				rx_octet_status = ND_RX_STATUS_RX_FAIL;
				break;
			}
		}
		if (MDM_ND_FindDleEtx(rx_buffer, byte_count)) {
			rx_octet_status = ND_RX_STATUS_WAIT_CRC1;
		}
		break;
	case ND_RX_STATUS_WAIT_CRC2:
		rx_octet_status = ND_RX_STATUS_FOUND_CRC2;
		break;
	case ND_RX_STATUS_WAIT_CRC1:
		rx_octet_status = ND_RX_STATUS_WAIT_CRC2;
		break;
	}
	return rx_octet_status;
}


extern UBYTE v23_rx_by_dma;
#if 0 /* moved to mdm_data.c by H.Kubo 1998/11/11 */
@@ static UWORD tskno_V23RlsdTimer;
@@ static UWORD tskno_V23_ModemRecover;
#endif

/*************************************************************************
	module		:[ナンバーディスプレー データ受信処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/10/08]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_ND_RxDataOctet(UWORD *offset_ptr, UWORD *rx_byte_ptr)
{
	struct Timer10msEventData_t new_data_timer;
	UBYTE 	*rx_buffer;
	UDWORD 	rx_bit_position;
	UWORD 	rx_byte_max;
	UWORD	rx_byte_counter;
	UWORD	rx_new_byte_counter;
	UWORD	rx_data_length;
	UWORD 	rx_timer;
	UWORD	rx_header_byte_position;
	UBYTE 	rx_bit_status;
	UBYTE 	rx_octet_status;
	UBYTE 	loop;


	rx_buffer = (UBYTE *) &EcmBuffer[0][0];
	rx_bit_position = 0;
	rx_byte_counter = 0;
	rx_data_length = 0;
	rx_byte_max = (ECM_BUFFER_LENGTH * ECM_BUFFER_MAX - MODEM_BUFFER_LENGTH); /* 受信可能最大バイト数 */
	rx_bit_status = ND_BIT_STATUS_MARK_BIT;
	rx_header_byte_position = 0;
	rx_octet_status = ND_RX_STATUS_WAIT_1ST_BIT;
	tskno_V23RlsdTimer = 0xffff; /* by H.Kubo 1998/03/12 */
	*offset_ptr = 0;

	/** V23 信号待ち **/
#if 0 /* オープンで立てているのでここでは触りません。 Deleted by H.Kubo 1998/11/16 */
@@	MDM_ND_WaitFirstDataEvent = TRUE;
#endif
	/* 最初の一バイトが来るまで５秒を限度に待つ */
	new_data_timer.Time = rx_timer = NCU_ND_GetDataTimerInterval();  /* 最初は５秒のタイマー*/
	new_data_timer.Event = EVT_MDM_RX_NEW_DATA;
	cre_tsk( &tskno_V23RlsdTimer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &new_data_timer);
	CMN_DisableInterrupt();
	if (!v23_rx_by_dma) {
		if  (MDM_ND_WaitFirstDataEvent) {
			wai_evt(EVT_MDM_RX_NEW_DATA);
		}
	}
	else {
		if ((MDM_DmaStart != MDM_DMA_CONTINUE) && (MDM_DmaStart != MDM_DMA_GO)) {
			wai_evt(EVT_MDM_RX_NEW_DATA);
		}
	}
	del_tsk( &tskno_V23RlsdTimer);
	CMN_EnableInterrupt();

	/** データ受信処理 **/
	if ((v23_rx_by_dma && ((MDM_DmaStart == MDM_DMA_CONTINUE) || (MDM_DmaStart == MDM_DMA_GO)))
	||  (!v23_rx_by_dma && !MDM_ND_WaitFirstDataEvent)
	) {
		rx_timer = ND_RX_TIMEOUT; /* 数バイト分のタイマー */
		loop = 1;
		/*** モデムからデータ受信 ***/
		while (loop) {
			if (RCV_BLOCK != MDM_ND_ExtractDataOctet(rx_timer, &rx_bit_status, rx_buffer, &rx_bit_position)) {
				if (loop == 2) { /* 一次応答から5秒たってもデータがこなかった */
#if (0) /* NAGANOよりフィードバック 2002/01/19 T.Takagi */
** 					/*---------------------------------------------------------------------
** 					** 実際にはECMバッファにデータが入っているにも関わらず、
** 					** 最終データが16バイトより少ないとき、ステータスがタイムアウトになり、
** 					** ECMバッファの受信データを解析しないで抜けてしまう不具合
** 					** 1999/11/05
** 					*/
** //					rx_octet_status = ND_RX_STATUS_RX_TIMEOUT;
#endif
					loop = FALSE; /* while ループを脱出 */
				}
				else {
					loop = 2;
					rx_timer = NCU_ND_GetDataTimerInterval(); /* 一次応答から5秒たつまで待ってみる */
				}
			}
			else { /* RCV_BLOCK で来た後、受信データ待ちタイマー長を正しく設定する。 by H.Kubo 1999/10/13 */
				loop = 1;	/* NAGANOよりフィードバック 2002/01/19 T.Takagi */
			}
			if (rx_byte_counter < (rx_new_byte_counter = rx_bit_position / 8)) { /* 一バイト以上受信していれば、*/
				do {
					/* <DLE><ETX> 探索、 パリティチェックなど。*/
					rx_octet_status = MDM_ND_ExaminRxOctet(rx_octet_status, rx_buffer, rx_byte_counter);
					if (rx_octet_status == ND_RX_STATUS_WAIT_HEADER) {
						*offset_ptr = rx_byte_counter;
					}
					rx_byte_counter++;
					if ((rx_header_byte_position == 0) && (rx_octet_status == ND_RX_STATUS_RECEIVING_DATA)) {
						rx_header_byte_position = rx_byte_counter;
					}
					if (rx_octet_status == ND_RX_STATUS_FOUND_CRC2) {
						rx_data_length = rx_byte_counter;
						if (MDM_ND_CheckCRC(rx_buffer + rx_header_byte_position, (UWORD) (rx_byte_counter - rx_header_byte_position) )) {
							rx_octet_status = ND_RX_STATUS_RX_COMPLETE;
						}
						else {
							rx_octet_status = ND_RX_STATUS_RX_FAIL;
						}
					}
					if ((rx_octet_status == ND_RX_STATUS_RX_FAIL)
					 || (rx_octet_status == ND_RX_STATUS_RX_COMPLETE)) {
						loop = FALSE;
						break;
					}
				} while ((rx_byte_counter < rx_new_byte_counter));
			}
			if (rx_byte_counter >= rx_byte_max) {
				rx_octet_status = ND_RX_STATUS_RX_FAIL;
				loop =  FALSE;
			}
		}
		/* パリティビット削除 */
		for (rx_byte_counter = 0; rx_byte_counter < rx_data_length; rx_byte_counter++) {
			rx_buffer[rx_byte_counter] &= MDM_ND_PARTIY_MASK;
		}
		/*---------------------------------------------------------------------
		** 実際にはECMバッファにデータが入っているにも関わらず、
		** 最終データが16バイトより少ないとき、ステータスがタイムアウトになり、
		** ECMバッファの受信データを解析しないで抜けてしまう不具合
		** 1999/11/05	NAGANOよりフィードバック 2002/01/19 T.Takagi
		*/
		if ((rx_octet_status != ND_RX_STATUS_RX_FAIL)
		 && (rx_octet_status != ND_RX_STATUS_RX_COMPLETE)) {
			rx_octet_status = ND_RX_STATUS_RX_TIMEOUT;
		}
	}
	else {
		rx_octet_status = ND_RX_STATUS_RX_TIMEOUT;
	}
	*rx_byte_ptr = rx_byte_counter;
	return rx_octet_status;
}




/*************************************************************************
	module		:[ナンバーディスプレイ用Ｖ２３受信タスク]
	function	:[
		1.ナンバーディスプレーデータの受信を待つ
		2.受信結果を判断し、上位処理に通知する。
		3.子タスクを終了する。
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	date		:[1998/08/21]
	author		:[久保博]
*************************************************************************/
CONST UWORD v23_debug = 0;

void MDM_ND_RxV23Task(UWORD *mbox_no)
{
	MESSAGE_t 	msg;
	UWORD 	offset = 0;
	UWORD	rx_byte = 0;


	msg.Item = FROM_NCU_ND;


	if (v23_debug) {
		UDWORD i;
		UBYTE *buffer = (UBYTE *) &EcmBuffer[ECM_BUFFER_LENGTH / 2][0];
		wai_tsk(v23_debug);
		for (i = 0; i < ECM_BUFFER_LENGTH * ECM_BUFFER_MAX / 2; i++) {
			wai_oneshot(1);
			if (v23_debug == 2) {
				while (MDM_GetIO(POS_RXFNE)) {
					buffer[i] = MDM_GetIO(POS_RBUFFER);
				}
			}
			else if (v23_debug == 3) {
				buffer[i] = MDM_GetIO(POS_FED);
			}
			else if (v23_debug == 4) {
				buffer[i] = MDM_GetIO(POS_RLSD);
			}
			else if (v23_debug == 5) {
				buffer[i] = MDM_GetIO(POS_RDBF);
			}
			else if (v23_debug == 6) {
				buffer[i] = MDM_GetIO(POS_TONEA);
			}
			else if (v23_debug == 7) {
				buffer[i] = MDM_GetIO(POS_TONEB);
			}
			else if (v23_debug == 8) {
				buffer[i] = MDM_GetIO(POS_TONEC);
			}
			else if (v23_debug == 9) {
				buffer[i] = MDM_GetIO(POS_RXFNE);
			}
			else {
				buffer[i] = MDM_GetIO(POS_RBUFFER);
			}
		}
	}
	offset = 0;

	/*
	** ROCKWELL製 28.8K
	*/
	/* モデム救済タスク起動 */
	if (tskno_MDM_ModemRecoverTask == 0xffff) {
		cre_tsk(&tskno_MDM_ModemRecoverTask, TSK_MDM_MODEMRECOVERTASK, 0);
		MDM_V23_ModemRecoverRunning = TRUE;		
	}

	switch (MDM_ND_RxDataOctet(&offset, &rx_byte)) {
	case ND_RX_STATUS_RX_COMPLETE:
		msg.Message = MSG_NCU_ND_RX_V23_SUCCESS; 	/* success */
		msg.SubMessage1 = rx_byte;					/* EcmBuffer 上のデータの先頭位置 */
		EcmBufferBaseWritePoint = (UDWORD) (&EcmBuffer[0][0] + offset);
		break;
	case ND_RX_STATUS_RX_FAIL:
		msg.Message = MSG_NCU_ND_RX_V23_FAIL;		/* fail */
		break;
	case ND_RX_STATUS_RX_TIMEOUT:
		if (MDM_ND_WaitFirstDataEvent) {
			msg.Message = MSG_NCU_ND_RX_V23_TIMEOUT;	/* time out */
		}
		else {
			msg.Message = MSG_NCU_ND_RX_V23_NO_DATA;	/* No data is received. */
		}
		break;
	default:
		/* ここにはこないはず。 */
		SaveReturnAddressAndJumpBegin();	/**リセットする*/
		break;
	}

	snd_msg(*mbox_no, &msg);

	if (tskno_V23RlsdTimer != 0xffff) {
		del_tsk(&tskno_V23RlsdTimer);
	}
	if (tskno_MDM_ModemRecoverTask != 0xffff) {
		if (MDM_V23_ModemRecoverRunning) {
			del_tsk(&tskno_MDM_ModemRecoverTask);
		}
	}
	MDM_V23_ModemRecoverRunning = 0;
	wai_tsk(0xffff);
}

/*************************************************************************
	module		:[ナンバーディスプレイ用受信タスク終了処理]
	function	:[
		1.ナンバーディスプレイ用Ｖ２３受信タスクを終了させる。
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[
	]
	comment		:[NAGANOからフィードバック 2002/01/19 T.Takagi]
	date		:[1998/08/21]
	author		:[久保博]
*************************************************************************/
void MDM_ND_RxV23TaskExit(void)
{
	if (tskno_V23RlsdTimer != 0xffff) {
		del_tsk(&tskno_V23RlsdTimer);
	}
	if (tskno_MDM_ModemRecoverTask != 0xffff) {
		if (MDM_V23_ModemRecoverRunning) {
			del_tsk(&tskno_MDM_ModemRecoverTask);
		}
	}
	MDM_V23_ModemRecoverRunning = 0;
	exi_tsk();
}

#else	/* added by H.Hirao 1999/01/12 */	/* ダミータスク忘れてました 2002/07/18 T.Takagi */
/* dummy TASK */
void MDM_ND_RxV23Task(UWORD *mbox_no)
{
	wai_tsk(0xffff);
}
#endif /* (PRO_NUMBER_DISPLAY == ENABLE) */

