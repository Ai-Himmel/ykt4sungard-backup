/*
 *  dma_blk.h  1994/01/11  DMA ﾒﾓﾘﾌﾞﾛｯｸ 定義  By M.Kotani
 *  For V53 & uPD71071
 */
#ifndef dma_blk_h
	#define dma_blk_h

/************************************************************************
*               BY:  M.Kotani
*             DATE:  94/01/13(木)
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  DMAUセットアップ用のメモリブロック
*                    DMA_SetupDMAU(suruct DMA_Data *)をコールしてDMAを設定する
************************************************************************/
struct DMA_Data_t {
	UBYTE	Channel;			/*DMAチャンネル*/
	UBYTE	Unit;				/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	UBYTE	Direction;			/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	UDWORD	SrcAddress;			/*DMA転送開始アドレス（MEMORY_TO_MEMORY の時は転送元アドレス）*/
	UDWORD	DstAddress;			/*DMA転送先アドレス（MEMORY_TO_MEMORY の時のみ使用）*/
	UWORD	Counter;			/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
};

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/10
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041内蔵DMAUセットアップ用のメモリブロック
*                    DMA_RequestEnable(UBYTE channnel)がコールされると
*                    内蔵DMAUのレジスタにセットされる
************************************************************************/
struct DMA_SH_CntrlData_t {
	UBYTE	AutoInit;			/*オートイニシャライズ設定フラグ*/
	UBYTE	Unit;				/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	UBYTE	Direction;			/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	UDWORD	SrcAddress;			/*DMA転送元アドレス*/
	UDWORD	DstAddress;			/*DMA転送先アドレス*/
	UDWORD	Counter;			/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  94/01/13(木)
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041内蔵DTCセットアップ用のメモリブロック
************************************************************************/
struct DMA_DTC_Data_t {
	UBYTE	Unit;				/* DTC転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER or DMA_DWORD_TRANSFER) */
	UBYTE	DTC_Mode;			/* DTC転送モード(DTC_BLOCK_MODE or DTC_NORMAL_MODE or DTC_REPEAT_MODE) 追加 1997/07/17  By T.Yamaguchi */
	UWORD	Length;				/* DTC転送ブロック長 */
	UWORD	Counter;			/* DTC転送回数（転送バイト数/ブロック長） */
	UDWORD	SrcAddress;			/* DTC転送元アドレス */
	UDWORD	DstAddress;			/* DTC転送先アドレス */
#if defined (SAKAKI) || defined(HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2) /* Add HINOKI 1998/09/21 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */ 
	UBYTE	Direction;			/*DTC転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
#endif
};

/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/12/10
*             TYPE:  struct
*      VAR TO HOLD:  ~
*      DESCRIPTION:  SH7041内蔵DTCレジスタ情報メモリブロック
************************************************************************/
#if 0	/* unionで取った方がよいのでは 1997/07/16  By T.Yamaguchi */
/************************/
/* ブロック転送モード用 */	/* 変更した 1997/07/17  By T.Yamaguchi */
/************************/
struct DMA_DTC_ParamData_t {
	UWORD	DTMR_Status;		/* モードレジスタ         */
	UWORD	DTCRA_Status;		/* 転送カウントレジスタ   */
	UWORD	reserve;			/* 未使用                 */
	UWORD	DTCRB_Status;		/* ブロック転送ブロック長 */
	UDWORD	DTSAR_Status;		/* 転送元アドレスレジスタ */
	UDWORD	DTDAR_Status;		/* 転送先アドレスレジスタ */
};
#endif
/************************/
/* ブロック転送モード用 */
/************************/
struct DMA_DTC_BlockMode_t {
	UWORD	DTMR_Status;		/* モードレジスタ         */
	UWORD	DTCRA_Status;		/* 転送カウントレジスタ   */
	UWORD	reserve;			/* 未使用                 */
	UWORD	DTCRB_Status;		/* ブロック転送ブロック長 */
	UDWORD	DTSAR_Status;		/* 転送元アドレスレジスタ */
	UDWORD	DTDAR_Status;		/* 転送先アドレスレジスタ */
};

/************************/
/*  ノーマルモード用    */
/************************/
struct DMA_DTC_NormalMode_t {
	UWORD	DTMR_Status;		/* モードレジスタ         */
	UWORD	DTCRA_Status;		/* 転送カウントレジスタ   */
	UDWORD	reserve;			/* 未使用                 */
	UDWORD	DTSAR_Status;		/* 転送元アドレスレジスタ */
	UDWORD	DTDAR_Status;		/* 転送先アドレスレジスタ */
};

/************************/
/*  リピートモード用    */
/************************/
struct DMA_DTC_RepeatMode_t {
	UWORD	DTMR_Status;		/* モードレジスタ         */
	UWORD	DTCRA_Status;		/* 転送カウントレジスタ   */
	UDWORD	DTIAR_Status;		/* 初期アドレスレジスタ   */
	UDWORD	DTSAR_Status;		/* 転送元アドレスレジスタ */
	UDWORD	DTDAR_Status;		/* 転送先アドレスレジスタ */
};

/************************/
/* ブロック転送モード用 */
/************************/
struct DMA_DTC_ParamData_t {
	union {
		struct DMA_DTC_BlockMode_t	BlockMode;		/* ブロック転送モード用 */
		struct DMA_DTC_NormalMode_t	NormalMode;		/*  ノーマルモード用    */
		struct DMA_DTC_RepeatMode_t	RepeatMode;		/*  リピートモード用    */
	} SetData;
};
/*----------------------------------*/
/*	ＤＴＣレジスタ情報管理マクロ	*/
/*----------------------------------*/
#define DTC_INT_BLOCK	DMA_DTC_Param[DTC_INTERRUPT_CH].SetData.BlockMode
#define DTC_INT_NORMAL	DMA_DTC_Param[DTC_INTERRUPT_CH].SetData.NormalMode
#define DTC_INT_REPEAT	DMA_DTC_Param[DTC_INTERRUPT_CH].SetData.RepeatMode
#define DTC_BLOCK		DMA_DTC_Param[DTC_BLOCK_MODE].SetData.BlockMode
#define DTC_NORMAL		DMA_DTC_Param[DTC_NORMAL_MODE].SetData.NormalMode
#define DTC_REPEAT		DMA_DTC_Param[DTC_REPEAT_MODE].SetData.RepeatMode

/* CL1用に用意しておく */
#define DTC_INT_BLOCK2	DMA_DTC_Param2[DTC_INTERRUPT_CH].SetData.BlockMode
#define DTC_INT_NORMAL2	DMA_DTC_Param2[DTC_INTERRUPT_CH].SetData.NormalMode
#define DTC_INT_REPEAT2	DMA_DTC_Param2[DTC_INTERRUPT_CH].SetData.RepeatMode

/* SAKAKI用 1998/06/16 H.Yoshikawa */
/* HINOKI用 1998/09/21 H.Hirao */
/* HINOKI2追加 2001/11/12 T.Takagi */
#if defined (SAKAKI) || defined (HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2)
#define DTC_INT_BLOCK_IRQ0	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ0-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ0	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ0-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ0	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ0-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ1-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ1-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ1-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ2	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ2-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ2	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ2-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ2	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ2-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ3	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ3-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ3	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ3-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ3	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ3-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ4	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ4-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ4	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ4-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ4	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ4-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ5	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ5-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ5	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ5-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ5	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ5-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ6	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ6-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ6	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ6-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ6	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ6-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_IRQ7	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ7-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_IRQ7	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ7-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_IRQ7	DMA_DTC_ParamIRQ[DTC_INTERRUPT_IRQ7-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
 #if defined (HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2)	/* added by H.Hirao 1999/01/23 */ /* HINOKI2 2001/11/12 T.Takagi */
#define DTC_INT_BLOCK_RXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_RXI1-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_RXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_RXI1-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_RXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_RXI1-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
#define DTC_INT_BLOCK_TXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_TXI1-DTC_INTERRUPT_IRQ0].SetData.BlockMode
#define DTC_INT_NORMAL_TXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_TXI1-DTC_INTERRUPT_IRQ0].SetData.NormalMode
#define DTC_INT_REPEAT_TXI1	DMA_DTC_ParamIRQ[DTC_INTERRUPT_TXI1-DTC_INTERRUPT_IRQ0].SetData.RepeatMode
 #endif
#endif

#endif
