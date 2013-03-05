/*
 *  cdc_blk.h  1996/10/14  ｺｰﾃﾞｯｸ ﾒﾓﾘﾌﾞﾛｯｸ 定義  By M.Kotani
 *    ｴﾝｺｰﾄﾞ用.....struct CodecEncodeParameterBlk_t
 *    ﾃﾞｺｰﾄﾞ用.....struct CodecDecodeParameterBlk_t
 *    符号変換用...struct CodecCodeConvertParameterBlk_t
 *    ﾃﾞｰﾀ転送用...struct CodecDataTransferParameterBlk_t
 *    DMA転送用....struct CodecDMA_TransferParameterBlk_t
 *    内部処理用...struct CodecParameterRegisterData_t
 *  For (MN86063 | MN86064) & SH7043
 */
#ifndef cdc_blk_h
	#define cdc_blk_h

#include	"\src\atlanta\define\product.h"

/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/01(金)
*             TYPE:  struct
*      VAR TO HOLD:  各ﾛｰｶﾙｽﾀｯｸ
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ｴﾝｺｰﾄﾞ用 ﾊﾟﾗﾒｰﾀ ﾌﾞﾛｯｸ。
*                    ｴﾝｺｰﾄﾞを行う時このﾌﾞﾛｯｸにﾊﾟﾗﾒｰﾀをｾｯﾄして
*                    そのｱﾄﾞﾚｽを引数にしてCallする
************************************************************************/
struct CodecEncodeParameterBlk_t {
	/* Kiri用追加ﾊﾟﾗﾒｰﾀ */
	UBYTE  CodecType;		/*符号化に使用するｺｰﾃﾞｯｸID (ex. SCANNER_CODEC)*/
	UBYTE  CodeType;		/*符号化方式 (ex. MMR_CODE)*/
	/* 入出力ﾊﾟﾗﾒｰﾀ */
	UWORD  FRWORD_Status;	/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
	UWORD  INWORD_Status;	/*入力ﾜｰﾄﾞ数*/
	UWORD  INLINE_Status;	/*入力ﾗｲﾝ数*/
	UBYTE  I_OBXR_Status;	/*入力ｵﾌｾｯﾄ*/
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  C0_STRA_Status;	/*符号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  C0_PWDR_Status;	/*符号化ﾍﾟｰｼﾞ幅*/
	UWORD  C0_OBXR_Status;	/*符号化ｵﾌｾｯﾄ*/
	UBYTE  C0_KPR_Status;	/*符号化Kﾊﾟﾗﾒｰﾀ*/
	UWORD  C0_LCONT_Status;	/*符号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  C0_MCLR_Status;	/*符号化最小符号ﾊﾞｲﾄ数*/
	UWORD  C0_HCONV_Status;	/*符号化主走査方向変換率*/
	UWORD  C0_VCONV_Status;	/*符号化副走査方向変換率*/
	UWORD  C0_LMASK_Status;	/*符号化左側白ﾏｽｸ*/
	UWORD  C0_RMASK_Status;	/*符号化右側白ﾏｽｸ*/
	UWORD  C0_MTOPA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  C0_MENDA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Vmn_Status;		/*間引き/OR指定*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  C_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  C_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  C_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  C_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  C_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  D_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  D_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  D_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  D_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  D_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#endif
};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/01(金)
*             TYPE:  struct
*      VAR TO HOLD:  各ﾛｰｶﾙｽﾀｯｸ
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ﾃﾞｺｰﾄﾞ用 ﾊﾟﾗﾒｰﾀ ﾌﾞﾛｯｸ。
*                    ﾃﾞｺｰﾄﾞを行う時このﾌﾞﾛｯｸにﾊﾟﾗﾒｰﾀをｾｯﾄして
*                    そのｱﾄﾞﾚｽを引数にしてCallする
************************************************************************/
struct CodecDecodeParameterBlk_t {
	/* Kiri用追加ﾊﾟﾗﾒｰﾀ */
	UBYTE  CodecType;		/*復号化に使用するｺｰﾃﾞｯｸID (ex. SCANNER_CODEC)*/
	UBYTE  CodeType;		/*復号化方式 (ex. MMR_CODE)*/
	/* 入出力ﾊﾟﾗﾒｰﾀ */
	UWORD  FRWORD_Status;	/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
	UWORD  OTWORD_Status;	/*出力ﾜｰﾄﾞ数*/
	UBYTE  O_OBXR_Status;	/*出力ｵﾌｾｯﾄ*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  D0_STRA_Status;	/*復号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  D0_PWDR_Status;	/*復号化ﾍﾟｰｼﾞ幅*/
	UWORD  D0_OBXR_Status;	/*復号化ｵﾌｾｯﾄ*/
	UWORD  D0_RTCR_Status;	/*復号化RTC数*/
	UWORD  D0_BLGR_Status;	/*復号化処理ﾗｲﾝ数*/
	UWORD  D0_LCONT_Status;	/*復号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  D0_ELIN_Status;	/*復号化ｴﾗｰﾗｲﾝ数*/
	UWORD  D0_HCONV_Status;	/*復号化主走査方向変換率*/
	UWORD  D0_VCONV_Status;	/*復号化副走査方向変換率*/
	UWORD  D0_LMASK_Status;	/*復号化左側白ﾏｽｸ*/
	UWORD  D0_RMASK_Status;	/*復号化右側白ﾏｽｸ*/
	UWORD  D0_MTOPA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  D0_MENDA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Vmn_Status;		/*間引き/OR指定*/
	/* 
	** プリンタ受信の場合、ＪＢＩＧ符号をデコードできるようにします。
	** by H.Hirao 1998/10/28
	*/
#if (PRO_JBIG == ENABLE) && (PRO_PRINTER_RX == ENABLE)
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  C_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  C_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  C_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  C_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  C_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  D_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  D_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  D_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  D_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  D_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#endif
#if (PRO_JBIG == ENABLE) && (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.30 K.Kawata */
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  C_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  C_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  C_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  C_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  C_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  D_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  D_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  D_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  D_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  D_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#endif
};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/01(金)
*             TYPE:  struct
*      VAR TO HOLD:  各ﾛｰｶﾙｽﾀｯｸ
*      DESCRIPTION:  ｺｰﾃﾞｯｸ 符号変換用 ﾊﾟﾗﾒｰﾀ ﾌﾞﾛｯｸ。
*                    符号変換を行う時このﾌﾞﾛｯｸにﾊﾟﾗﾒｰﾀをｾｯﾄして
*                    そのｱﾄﾞﾚｽを引数にしてCallする
************************************************************************/
struct CodecCodeConvertParameterBlk_t {
	/* Kiri用追加ﾊﾟﾗﾒｰﾀ */
	UBYTE  CodecType;		/*符号化に使用するｺｰﾃﾞｯｸID (ex. SCANNER_CODEC)*/
	UBYTE  SrcCodeType;		/*復号化方式 (ex. MMR_CODE)*/
	UBYTE  DestCodeType;	/*符号化方式 (ex. MMR_CODE)*/
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  C0_PWDR_Status;	/*符号化ﾍﾟｰｼﾞ幅*/
	UWORD  C0_OBXR_Status;	/*符号化ｵﾌｾｯﾄ*/
	UBYTE  C0_KPR_Status;	/*符号化Kﾊﾟﾗﾒｰﾀ*/
	UWORD  C0_LCONT_Status;	/*符号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  C0_MCLR_Status;	/*符号化最小符号ﾊﾞｲﾄ数*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  D0_PWDR_Status;	/*復号化ﾍﾟｰｼﾞ幅*/
	UWORD  D0_OBXR_Status;	/*復号化ｵﾌｾｯﾄ*/
	UWORD  D0_RTCR_Status;	/*復号化RTC数*/
	UWORD  D0_BLGR_Status;	/*復号化処理ﾗｲﾝ数*/
	UWORD  D0_LCONT_Status;	/*復号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  D0_ELIN_Status;	/*復号化ｴﾗｰﾗｲﾝ数*/
	UWORD  D0_HCONV_Status;	/*復号化主走査方向変換率*/
	UWORD  D0_VCONV_Status;	/*復号化副走査方向変換率*/
	UWORD  D0_LMASK_Status;	/*復号化左側白ﾏｽｸ*/
	UWORD  D0_RMASK_Status;	/*復号化右側白ﾏｽｸ*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Vmn_Status;		/*間引き/OR指定*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  C_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  C_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  C_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  C_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  C_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  D_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  D_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  D_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  D_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  D_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#endif
};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/01(金)
*             TYPE:  struct
*      VAR TO HOLD:  各ﾛｰｶﾙｽﾀｯｸ
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ﾃﾞｰﾀ転送用 ﾊﾟﾗﾒｰﾀ ﾌﾞﾛｯｸ。
*                    ﾃﾞｰﾀ転送を行う時このﾌﾞﾛｯｸにﾊﾟﾗﾒｰﾀをｾｯﾄして
*                    そのｱﾄﾞﾚｽを引数にしてCallする
************************************************************************/
struct CodecDataTransferParameterBlk_t {
	/* Kiri用追加ﾊﾟﾗﾒｰﾀ */
	UBYTE  CodecType;		/*ﾃﾞｰﾀ転送に使用するｺｰﾃﾞｯｸID (ex. SCANNER_CODEC)*/
	/* 入出力ﾊﾟﾗﾒｰﾀ */
	UWORD  FRWORD_Status;	/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
	UWORD  INWORD_Status;	/*入力ﾜｰﾄﾞ数*/
	UWORD  INLINE_Status;	/*入力ﾗｲﾝ数*/
	UWORD  OTWORD_Status;	/*出力ﾜｰﾄﾞ数*/
	UBYTE  I_OBXR_Status;	/*入力ｵﾌｾｯﾄ*/
	UBYTE  O_OBXR_Status;	/*出力ｵﾌｾｯﾄ*/
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  C0_MTOPA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  C0_MENDA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  D0_MTOPA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  D0_MENDA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* ﾃﾞｰﾀ転送ﾊﾟﾗﾒｰﾀ */
	UWORD  B_STRA0_Status;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ0*/
	UWORD  B_STRA1_Status;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ1*/
	UWORD  B_HCONV_Status;	/*ﾃﾞｰﾀ転送主走査方向変換率*/
	UWORD  B_VCONV_Status;	/*ﾃﾞｰﾀ転送副走査方向変換率*/
	UWORD  B_LMASK_Status;	/*ﾃﾞｰﾀ転送左側白ﾏｽｸ*/
	UWORD  B_RMASK_Status;	/*ﾃﾞｰﾀ転送右側白ﾏｽｸ*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Vmn_Status;		/*間引き/OR指定*/
};

/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/01(金)
*             TYPE:  struct
*      VAR TO HOLD:  各ﾛｰｶﾙｽﾀｯｸ
*      DESCRIPTION:  ｺｰﾃﾞｯｸ DMA転送用 ﾊﾟﾗﾒｰﾀ ﾌﾞﾛｯｸ。
*                    ﾃﾞｰﾀ転送を行う時このﾌﾞﾛｯｸにﾊﾟﾗﾒｰﾀをｾｯﾄして
*                    そのｱﾄﾞﾚｽを引数にしてCallする
************************************************************************/
struct CodecDMA_TransferParameterBlk_t {
	/* Kiri用追加ﾊﾟﾗﾒｰﾀ */
	UBYTE  CodecType;		/*DMA転送に使用するｺｰﾃﾞｯｸID (ex. SCANNER_CODEC)*/
	UBYTE  Channel;			/*使用するﾁｬﾝﾈﾙ (0 or 1)*/
	/* 入出力ﾊﾟﾗﾒｰﾀ */
	UWORD  FRWORD_Status;	/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
	/* DMA転送ﾊﾟﾗﾒｰﾀ */
	UWORD  T0_STRA_Status;	/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
	UWORD  T0_WORD_Status;	/*DMA転送ﾜｰﾄﾞ数*/
	UWORD  T0_BLGR_Status;	/*DMA転送ﾗｲﾝ数*/
	UWORD  T0_MTOPA_Status;	/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  T0_MENDA_Status;	/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	UWORD  T1_STRA_Status;	/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
	UWORD  T1_WORD_Status;	/*DMA転送ﾜｰﾄﾞ数*/
	UWORD  T1_BLGR_Status;	/*DMA転送ﾗｲﾝ数*/
	UWORD  T1_MTOPA_Status;	/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  T1_MENDA_Status;	/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
};
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  struct
*      VAR TO HOLD:  \src\kiri\def_v\cdc_val.c CodecParameterRegister
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ﾊﾟﾗﾒｰﾀ ﾚｼﾞｽﾀ変数 管理ﾌﾞﾛｯｸ
*                    この大域変数ﾌﾞﾛｯｸをDMAでｺｰﾃﾞｯｸに転送する。
*                    ﾏﾙﾁﾀｽｸで動作する為、第三者の書き込みを禁止する。
************************************************************************/
struct CodecParameterRegisterData_t {
	/* 入出力ﾊﾟﾗﾒｰﾀ */
	UWORD  FRWORD_Status;	/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
	UWORD  INWORD_Status;	/*入力ﾜｰﾄﾞ数*/
	UWORD  INLINE_Status;	/*入力ﾗｲﾝ数*/
	UWORD  OTWORD_Status;	/*出力ﾜｰﾄﾞ数*/
#if (PRO_CPU == SH7043)	/**エンディアンに注意*/
	UBYTE  I_OBXR_Status;	/*入力ｵﾌｾｯﾄ*/
	UBYTE  O_OBXR_Status;	/*出力ｵﾌｾｯﾄ*/
#endif
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  C0_STRA_Status;	/*符号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  C0_PWDR_Status;	/*符号化ﾍﾟｰｼﾞ幅*/
	UWORD  C0_OBXR_Status;	/*符号化ｵﾌｾｯﾄ*/
#if (PRO_CPU == SH7043)	/**エンディアンに注意*/
	UBYTE  C0_KPR_Status;	/*符号化Kﾊﾟﾗﾒｰﾀ*/
	UBYTE  C0_RTCR_Status;	/*符号化RTC数*/
#endif
	UWORD  C0_LCONT_Status;	/*符号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  C0_MCLR_Status;	/*符号化最小符号ﾊﾞｲﾄ数*/
	UWORD  C0_HCONV_Status;	/*符号化主走査方向変換率*/
	UWORD  C0_VCONV_Status;	/*符号化副走査方向変換率*/
	UWORD  C0_LMASK_Status;	/*符号化左側白ﾏｽｸ*/
	UWORD  C0_RMASK_Status;	/*符号化右側白ﾏｽｸ*/
	UWORD  C0_MTOPA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  C0_MENDA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	UWORD  D0_STRA_Status;	/*復号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  D0_PWDR_Status;	/*復号化ﾍﾟｰｼﾞ幅*/
	UWORD  D0_OBXR_Status;	/*復号化ｵﾌｾｯﾄ*/
	UWORD  D0_RTCR_Status;	/*復号化RTC数*/
	UWORD  D0_BLGR_Status;	/*復号化処理ﾗｲﾝ数*/
	UWORD  D0_LCONT_Status;	/*復号化ﾗｲﾝｶｳﾝﾀ*/
#if (PRO_CPU == SH7043)	/**エンディアンに注意*/	/*MN86064で追加*//* MN86063 Dummy1 Extra Area*/
	UBYTE  D0_UWLIN_Status;	/*上端白ライン数*/
	UBYTE  D0_LWLIN_Status;	/*下端白ライン数*/
#endif
	UWORD  D0_ELIN_Status;	/*復号化ｴﾗｰﾗｲﾝ数*/
	UWORD  D0_HCONV_Status;	/*復号化主走査方向変換率*/
	UWORD  D0_VCONV_Status;	/*復号化副走査方向変換率*/
	UWORD  D0_LMASK_Status;	/*復号化左側白ﾏｽｸ*/
	UWORD  D0_RMASK_Status;	/*復号化右側白ﾏｽｸ*/
	UWORD  D0_MTOPA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  D0_MENDA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.1 */
	UWORD  C1_STRA_Status;	/*符号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  C1_PWDR_Status;	/*符号化ﾍﾟｰｼﾞ幅*/
	UWORD  C1_OBXR_Status;	/*符号化ｵﾌｾｯﾄ*/
#if (PRO_CPU == SH7043)	/**エンディアンに注意*/
	UBYTE  C1_KPR_Status;	/*符号化Kﾊﾟﾗﾒｰﾀ*/
	UBYTE  C1_RTCR_Status;	/*符号化RTC数*/
#endif
	UWORD  C1_LCONT_Status;	/*符号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  C1_MCLR_Status;	/*符号化最小符号ﾊﾞｲﾄ数*/
	UWORD  C1_HCONV_Status;	/*符号化主走査方向変換率*/
	UWORD  C1_VCONV_Status;	/*符号化副走査方向変換率*/
	UWORD  C1_LMASK_Status;	/*符号化左側白ﾏｽｸ*/
	UWORD  C1_RMASK_Status;	/*符号化右側白ﾏｽｸ*/
	UWORD  C1_MTOPA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  C1_MENDA_Status;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.1 */
	UWORD  D1_STRA_Status;	/*復号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
	UWORD  D1_PWDR_Status;	/*復号化ﾍﾟｰｼﾞ幅*/
	UWORD  D1_OBXR_Status;	/*復号化ｵﾌｾｯﾄ*/
	UWORD  D1_RTCR_Status;	/*復号化RTC数*/
	UWORD  D1_BLGR_Status;	/*復号化処理ﾗｲﾝ数*/
	UWORD  D1_LCONT_Status;	/*復号化ﾗｲﾝｶｳﾝﾀ*/
	UWORD  D1_ELIN_Status;	/*復号化ｴﾗｰﾗｲﾝ数*/
	UWORD  D1_HCONV_Status;	/*復号化主走査方向変換率*/
	UWORD  D1_VCONV_Status;	/*復号化副走査方向変換率*/
	UWORD  D1_LMASK_Status;	/*復号化左側白ﾏｽｸ*/
	UWORD  D1_RMASK_Status;	/*復号化右側白ﾏｽｸ*/
	UWORD  D1_MTOPA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  D1_MENDA_Status;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* ﾃﾞｰﾀ転送ﾊﾟﾗﾒｰﾀ */
	UWORD  B_STRA0_Status;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ0*/
	UWORD  B_STRA1_Status;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ1*/
	UWORD  B_HCONV_Status;	/*ﾃﾞｰﾀ転送主走査方向変換率*/
	UWORD  B_VCONV_Status;	/*ﾃﾞｰﾀ転送副走査方向変換率*/
	UWORD  B_LMASK_Status;	/*ﾃﾞｰﾀ転送左側白ﾏｽｸ*/
	UWORD  B_RMASK_Status;	/*ﾃﾞｰﾀ転送右側白ﾏｽｸ*/
	/* DMA転送ﾊﾟﾗﾒｰﾀ */
	UWORD  Dummy1;			/*Extra Area*/
	UWORD  T0_STRA_Status;	/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
	UWORD  T0_WORD_Status;	/*DMA転送ﾜｰﾄﾞ数*/
	UWORD  T0_BLGR_Status;	/*DMA転送ﾗｲﾝ数*/
	UWORD  T0_MTOPA_Status;	/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  Dummy2;			/*Extra Area*/
	UWORD  T0_MENDA_Status;	/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	UWORD  Dummy3;			/*Extra Area*/
	UWORD  T1_STRA_Status;	/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
	UWORD  T1_WORD_Status;	/*DMA転送ﾜｰﾄﾞ数*/
	UWORD  T1_BLGR_Status;	/*DMA転送ﾗｲﾝ数*/
	UWORD  T1_MTOPA_Status;	/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	UWORD  Dummy4;			/*Extra Area*/
	UWORD  T1_MENDA_Status;	/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* その他のﾊﾟﾗﾒｰﾀ */
	UWORD  C0_REFA_Status;	/*符号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy6 Extra Area*/
	UWORD  C1_REFA_Status;	/*符号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy7 Extra Area*/
	UWORD  D0_REFA_Status;	/*復号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy8 Extra Area*/
	UWORD  D1_REFA_Status;	/*復号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy9 Extra Area*/
	UWORD  STRADD_Status;	/*ﾒﾓﾘ先頭ｱﾄﾞﾚｽ*/
	UWORD  ENDADD_Status;	/*ﾒﾓﾘ最終ｱﾄﾞﾚｽ*/
	UWORD  Dummy5;			/*Extra Area*/
	UWORD  Dummy6;			/*Extra Area*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Vmn_Status;		/*間引き/OR指定*/
	UWORD  IMGWT_Status;	/*ｲﾒｰｼﾞﾊﾞｽwaitｻｲｸﾙ数*/
	UWORD  IMGBNK0_Status;	/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定0*/
	UWORD  IMGBNK1_Status;	/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定1*/
	/* JBIG ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  Y1CREFA_Status;	/*JBIG符号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
	UWORD  Y2CREFA_Status;	/*JBIG符号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
	UWORD  Y1DREFA_Status;	/*JBIG復号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
	UWORD  Y2DREFA_Status;	/*JBIG復号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
	UWORD  Dummy7;			/*Extra Area*/
	UWORD  Dummy8;			/*Extra Area*/
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  C_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  C_QMIR_Status;	/*QM割り込みﾚｼﾞｽﾀ*/
	UWORD  C_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  C_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  C_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  C_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	UBYTE  C_tx1_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
	UBYTE  C_tx0_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
	UWORD  C_YAT0_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
	UWORD  C_YAT1_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
	UWORD  C_QMBUF0_Status;	/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
	UWORD  C_QMBUF1_Status;	/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	UWORD  D_QMCR_Status;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	UWORD  D_QMIR_Status;	/*QM割り込みﾚｼﾞｽﾀ*/
	UWORD  D_QMIRM_Status;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	UWORD  D_Yd_Status;		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	UWORD  D_L0_Status;		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	UWORD  D_Mx_Status;		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	UBYTE  D_tx1_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
	UBYTE  D_tx0_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
	UWORD  D_YAT0_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
	UWORD  D_YAT1_Status;	/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
	UWORD  D_QMBUF0_Status;	/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
	UWORD  D_QMBUF1_Status;	/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
};

#endif
