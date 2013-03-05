/* By Y.Suzuki 1996/10/14 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_blk.h"

/************************************************************************
*               BY:  M.Kotani
*             DATE:  Aug.22,1994
*        FILE NAME:  dma_data.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  ＤＭＡの完了フラグ
*        REFERENCE:
************************************************************************/
UBYTE DMA0_TC0Flag = 0;
UBYTE DMA0_TC1Flag = 0;
UBYTE DMA0_TC2Flag = 0;
UBYTE DMA0_TC3Flag = 0;

#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/29 */
UBYTE 	DMA_MemoryToMemory_TC_Flag = 0;
#endif


/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/10
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041内蔵DMAUセットアップ用のメモリブロック
*                    DMA_RequestEnable(UBYTE channnel)がコールされると
*                    内蔵DMAUのレジスタにセットされる
************************************************************************/
struct DMA_SH_CntrlData_t DMA_SH_Cntrl[4] = {0};

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/17
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041DTCレジスタ情報メモリブロック
************************************************************************/
#pragma section DTCBLK /* locate section name "DDTC_BLK" */
struct DMA_DTC_ParamData_t DMA_DTC_Param[4] = {0};
#pragma section

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/17
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041DTCレジスタ情報メモリブロック
*                    ANZU_L CLASS1用に追加する
************************************************************************/
#pragma section DTCBLK2 /* locate section name "DDTC_BLK2" */
struct DMA_DTC_ParamData_t DMA_DTC_Param2[1] = {0};
#pragma section

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/***********************************************************************
*		   BY:	 H.Yoshikawa
*		 DATE:	 1998/06/16
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 SAKAKI用に定義する。
*				 値は、ALTANTAで使用しているものと重複しないようにしておきます。
*				 SAKAKIでは、IRQ3/IRQ4/IRQ5/IRQ6を使用します
* DESCRIPTION:	 DTC転送モードチャンネル
************************************************************************/
#pragma section DTCBLK3 /* locate section name "DDTC_BLK3" */
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)	/* ＳＣＩ用ＤＴＣレジスタ情報ブロック by H.Hirao 1999/01/23 */
struct DMA_DTC_ParamData_t DMA_DTC_ParamIRQ[10] = {0};
 #else
struct DMA_DTC_ParamData_t DMA_DTC_ParamIRQ[8] = {0};
 #endif
#pragma section
#endif

#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
UBYTE	DtcPermission = 0;
#endif
