/* By S.K Spe.21,1995 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_blk.h"

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Aug.22,1994
*		 FILE NAME:	 dma_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ＤＭＡの完了フラグ
*		 REFERENCE:
************************************************************************/
extern UBYTE DMA0_TC0Flag;
extern UBYTE DMA0_TC1Flag;
extern UBYTE DMA0_TC2Flag;
extern UBYTE DMA0_TC3Flag;

#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/29 */
extern UBYTE 	DMA_MemoryToMemory_TC_Flag;
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
extern struct DMA_SH_CntrlData_t DMA_SH_Cntrl[4];

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/17
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041DTCレジスタ情報メモリブロック
************************************************************************/
extern struct DMA_DTC_ParamData_t DMA_DTC_Param[4];

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/17
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041DTCレジスタ情報メモリブロック
*                    ANZU_L CLASS1用に追加する
************************************************************************/
extern struct DMA_DTC_ParamData_t DMA_DTC_Param2[1];

/***********************************************************************
*		   BY:	 H.Yoshikawa
*		 DATE:	 1998/06/16
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 SAKAKI用に定義する。
*				 値は、ALTANTAで使用しているものと重複しないようにしておきます。
*				 SAKAKIでは、IRQ3/IRQ4/IRQ5/IRQ6を使用します
* DESCRIPTION:	 DTC転送モードチャンネル
************************************************************************/
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)	/* ＳＣＩ用ＤＴＣレジスタ情報ブロック by H.Hirao 1999/01/23 */
extern struct DMA_DTC_ParamData_t DMA_DTC_ParamIRQ[10];
#else
extern struct DMA_DTC_ParamData_t DMA_DTC_ParamIRQ[8];
#endif


#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
extern UBYTE	DtcPermission;
#endif
