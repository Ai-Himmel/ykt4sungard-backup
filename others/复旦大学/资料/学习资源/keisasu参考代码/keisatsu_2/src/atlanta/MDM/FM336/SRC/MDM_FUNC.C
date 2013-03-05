/*---------------------------------------------------------------------------*/
/*	プロジェクト : POPLAR_F													 */
/*	ファイル名	 : mdm_func.c												 */
/*	モジュール	 :															 */
/*				 :	UDWORD DMA_AddressSet(UBYTE *address)					 */
/*				 :	void MDM_ConfigReset(void)								 */
/*				 :	UWORD	 DetectEOL(register UBYTE *mdm_adr)				 */
/*	作成者		 : 															 */
/*	日	付		 : 1999/10/06												 */
/*	概	要		 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"	/* Add By O.Kimoto 1998/01/16 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h" /* Added by H.Kubo 1998/01/06 for MemoryMove */

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\ext_v\mlt_data.h" /* Added by H.Kubo 1998/01/06 for R288F_InternalStatus */


/*************************************************************************
	module		:[受信開始時、ＥＯＬ検出]
	function	:[
		1.
	]
	return		:[受信開始	OK:0  NG:-1]
	common		:[ハードコーデック用]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/11/07]
	author		:[鈴木郁二]
*************************************************************************/
UWORD	 DetectEOL(register UBYTE *mdm_adr)
{
	UBYTE bit_chk,zero_cnt,mdm_data;
	UWORD mdm_offset;

	zero_cnt = 0;
	mdm_data = 0;
	mdm_offset = 0;
	bit_chk = 1;

	/* 1997/11/06
	 * 沖の機械からＶ１９でＧ３受信すると発信元がラインぬけする。
	 * 次ぎのモデムバッファにＥＯＬを上書きしてるのを修正
	 * MODEM_BUFFER_LENGTH(262) -> 256
	*/

#if ((MODEM_DMA_SIZE+1)  < MODEM_BUFFER_LENGTH)
	/** モデムバッファの最後にＥＯＬをセットしとく */
	*(mdm_adr + MODEM_DMA_SIZE) = 0x00;
	*(mdm_adr + MODEM_DMA_SIZE + 1) = 0x08;
#endif

	mdm_data = *(mdm_adr + mdm_offset);
	while(1) {
		if(mdm_data == 0) {
			zero_cnt += 8;
			mdm_offset++;
			mdm_data = *(mdm_adr + mdm_offset);
		}
		else {
			/** 最下位ビットよりゼロをカウントしていく */
			if(!(mdm_data & bit_chk)) {
				zero_cnt++;
			}
			else {
				if(zero_cnt >= 11) {
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
					if(mdm_offset < MDM_ModemDmaSize) { /* mdm_offset < 256 */
#else
					if(mdm_offset < MODEM_DMA_SIZE) { /* mdm_offset < 256 */
#endif
						return(0);
					}
					else {
						return(-1);
					}
				}
				else {
					zero_cnt = 0;
				}
			}
			if(bit_chk >= 0x80) {
				bit_chk = 1;
				mdm_offset++;
				mdm_data = *(mdm_adr + mdm_offset);
			}
			else {
				bit_chk <<= 1;
			}
			/* G3 受信で処理が間に合わないので削ります。 H.Kubo 1998/01/23 */
			/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
		}

#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
		/* Add By O.Kimoto 1997/12/19 */
		if(mdm_offset >= MDM_ModemDmaSize) { /* mdm_offset < 256 */
			return(-1);
		}
#else
		/* Add By O.Kimoto 1997/12/19 */
		if(mdm_offset >= MODEM_DMA_SIZE) { /* mdm_offset < 256 */
			return(-1);
		}
#endif

	}
}


/*************************************************************************
	module		:[モデムの内部状態の履歴を LST のバッファへコピーする]
	function	:[
	]
	return		:[なし]
	common		:[
		R288F_InternalStatus
		MDM_InternalStatus
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1997/12/17]
	author		:[久保博]
*************************************************************************/
void	MDM_GetInternalStatus(void)
{
	UWORD size;
	size = (sizeof(R288F_InternalStatus) < sizeof(MDM_InternalStatus)) ? sizeof(R288F_InternalStatus) : sizeof(MDM_InternalStatus);
	MemoryMove((UBYTE *) &R288F_InternalStatus[0], (UBYTE *) &MDM_InternalStatus[0], size);
}



/*************************************************************************
	module		:[モデムの設定を行うタスク]
	function	:[
		1.メッセージにしたがってモデムを設定する
			1.1 MDM_FilterSet()
			1.2 MDM_ConfigReset()

	]
	return		:[]
	common		:[]
	condition	:[使いません。1997/12/19]
	comment		:[
		POPLAR_H では、小さなスタック領域しか持たないタスクから
		モデムの設定を行うと、スタックが溢れることがあります。
		そこで、モデム以外のモジュールでモデムの設定を行うときは
		このタスクにメッセージを送り、実際の設定はこのタスクが行います。
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1997/12/17]
	author		:[久保博]
*************************************************************************/
void MDM_ModemConfigTask(void)
{

}
