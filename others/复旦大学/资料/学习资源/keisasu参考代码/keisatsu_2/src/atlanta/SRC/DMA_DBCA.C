/* Copied by T.Nose 1996/11/12 */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.13,1994
*        FILE NAME:  dma_dbca.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DBA/DCAレジスタを制御する関数群
*  PUBLIC ROUTINES:  unsigned long far  DMA_CheckDMA_BaseAddress(unsigned char DMAUtype)
*                    unsigned long far  DMA_CheckDMA_CurrentAddress(unsigned char DMAUtype)
*                    void          far  DMA_SetDMA_BaseAddress(unsigned char DMAUtype, unsigned long address)
*                    void          far  DMA_SetDMA_BaseCurrentAddress(unsigned char DMAUtype, unsigned long address)
* PRIVATE ROUTINES:  unsigned long near CheckDMAU_DBA_DCA(unsigned char DMAUtype)
*                    void          near SetDMAU_DBA_DCA(unsigned char DMAUtype, unsigned long address)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h" /* Added by H.Kubo 19997/09/08 */
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cmn_pro.h"
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\define\mem_def.h"
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif /* (PRO_MODEM == R288F) */

#if (PRO_EXT_DMAC == ENABLE) /* ファイル内の関数全部 */

#if (PRO_CPU == SH7043)
#include "\src\atlanta\sh7043\define\sh_port.h"
#endif


/*************************************************************************
	module		:[uPD71071のDBA/DCAレジスタを読み出します]
	function	:[
		1.引数のDBA/DCA下位、中位レジスタポートのアドレスをリードする
		2.引数のDBA/DCA上位レジスタポートのアドレスをリードする
		3.上位、中位、下位をロング型にまとめてリターンする
	]
	return		:[
		n:DBA/DCAの値
	]
	common		:[なし]
	condition	:[
		チャンネル、アクセス条件が設定されていること
	]
	comment		:[
	1996/04/03 野瀬	DMAU_DBA_DCA_UPPER,SLAVE1_DMAU_DBA_DCA_UPPERにワードアクセス
					するよう変更
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD CheckDMAU_DBA_DCA(void)
{
	UDWORD address;
	UWORD lower_address;
	UBYTE upper_address;

	lower_address = (UWORD)inp(DMAU_DBA_DCA_WORD_LOWER - 1);
	lower_address <<= 8;
	lower_address += (UWORD)inp(DMAU_DBA_DCA_WORD_LOWER);
	upper_address = inp(DMAU_DBA_DCA_UPPER);
	address = (UDWORD)lower_address + ((UDWORD)upper_address << 16);	/**上位データと下位データを合成する*/
	return(address);
}


/*************************************************************************
	module		:[uPD71071のDBA/DCAレジスタをセットします]
	function	:[
		1.引数のデータを上位、中下位に分ける
		2.引数のDBA/DCA下位、中位レジスタポートのアドレスにアウトする
		3.引数のDBA/DCA上位レジスタポートのアドレスにアウトする
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		チャンネル、アクセス条件が設定されていること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void SetDMAU_DBA_DCA(UDWORD address)	/*DMAアドレス*/
{
	UWORD lower_address;
	UBYTE upper_address;

	lower_address = (UWORD)address;
	upper_address = (UBYTE)(address >> 16);
	outp((DMAU_DBA_DCA_WORD_LOWER - 1),(UBYTE)(lower_address >> 8));
	outp(DMAU_DBA_DCA_WORD_LOWER,(UBYTE)lower_address);
	outp(DMAU_DBA_DCA_UPPER, upper_address);
}


/*************************************************************************
	module		:[uPD71071のDBAレジスタを読み出します]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベースレジスタ読みだしに設定する
		3.DBA/DCAレジスタのポートを読みだす
	]
	return		:[
		n>=0:設定されているDMA転送開始アドレス
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD DMA_CheckDMA_BaseAddress(UBYTE channel)	/*DMAチャンネル*/
{
	UDWORD result;
	UBYTE dch;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	dch = channel;
	dch |= 0x04;	/**アクセス条件をセット*/
	SetDMAU_DCH(dch);
	result = CheckDMAU_DBA_DCA();
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
	return(result);
}


/*************************************************************************
	module		:[uPD71071のDCAレジスタを読み出します]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をカレントレジスタ読みだしに設定する
		3.DBA/DCAレジスタのポートを読みだす
	]
	return		:[
		n>=0:現在のDMA転送アドレス
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD DMA_CheckDMA_CurrentAddress(UBYTE channel)	/*DMAチャンネル*/
{
	UDWORD result;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	result = CheckDMAU_DBA_DCA();
	
	/* 外付けＤＭＡは２４ｂｉｔのアドレスバスしかないため、ポプラのシステムでは、
	では、01000000の上位８ｂｉｔは固定で使用されているため ＤＭＡのアドレスの値に
	01000000をプラスする	1997/04/11  By T.Yamaguchi
	*/
	if ((channel + DMA_INTERNAL_CH_MAX == DMA_SCNCDC_DRAM_CH)
	 || (channel + DMA_INTERNAL_CH_MAX == DMA_COMCDC_DRAM_CH)) {
		result = (UDWORD)(result + (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
	}
	
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	return(result);
}


/*************************************************************************
	module		:[uPD71071のDBAレジスタをセットします]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベースレジスタのみ書き込みに設定する
		3.DBA/DCAレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_BaseAddress(UBYTE channel,	/*DMAチャンネル*/
							UDWORD address)	/*DMA転送開始アドレス*/
{
	UBYTE dch;
	UWORD  int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	dch = channel;
	dch |= 0x04;	/**アクセス条件をセット*/
	SetDMAU_DCH(dch);
	SetDMAU_DBA_DCA(address);	/**DBA_DCAレジスタのセット*/
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}


/*************************************************************************
	module		:[uPD71071のDBA&DCAレジスタをセットします]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベース&カレントレジスタ書き込みに設定する
		3.DBA/DCAレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_BaseCurrentAddress(UBYTE channel,	/*DMAチャンネル*/
									UDWORD address)	/*DMA転送アドレス*/
{
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	SetDMAU_DBA_DCA(address);	/**DBA_DCAレジスタのセット*/
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}

#endif /* PRO_EXT_DMAC == ENABLE */
