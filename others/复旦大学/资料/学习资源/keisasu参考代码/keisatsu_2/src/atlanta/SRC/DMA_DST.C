/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.14,1994
*        FILE NAME:  dma_dst.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DSTレジスタを制御する関数群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  unsigned char near CheckDMAU_DST(unsigned char DMAUtype)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\sh7043\define\sh_port.h"

#if (PRO_EXT_DMAC == ENABLE)

/*************************************************************************
	module		:[uPD71071のDSTレジスタを読み出します]
	function	:[
		1.引数のDSTレジスタポートのアドレスをリードする
	]
	return		:[
		n:DSTの値
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
UBYTE CheckDMAU_DST(void)
{
	return(inp(DMAU_DST));
}

#endif
