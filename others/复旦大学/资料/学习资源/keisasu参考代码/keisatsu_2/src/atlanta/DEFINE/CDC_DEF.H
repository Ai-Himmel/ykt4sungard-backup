/*
 *  cdc_def.h  1996/10/14  ｺｰﾃﾞｯｸ 定義  By M.Kotani
 *  For MN86063 & MN86064
 */
#ifndef	cdc_def_h
	#define	cdc_def_h

#include "\src\atlanta\define\product.h"	/**Add By M.Kotani 1998/01/08*/
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   Fri 4 July 1997
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   ｺｰﾃﾞｯｸLSI
************************************************************************/
#define	CDC_MN86063	1
#define	CDC_MN86064	2
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   Tue 12 Oct 1993
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   ｺｰﾃﾞｯｸ使用個数
************************************************************************/
#define	CODEC_MAX	3
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/08(金)
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  ｺｰﾃﾞｯｸ種別(ID)
************************************************************************/
#define	SCANNER_CODEC		(UBYTE)0	/*読み取り用ｺｰﾃﾞｯｸ*/
#define	PRINTER_CODEC		(UBYTE)1	/*ﾌﾟﾘﾝﾄ用ｺｰﾃﾞｯｸ*/
#define	COMMUNICATION_CODEC	(UBYTE)2	/*通信用ｺｰﾃﾞｯｸ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/21(木)
*             TYPE:  define
*      VAR TO HOLD:  UBYTE CodecGetID[CODEC_MAX]
*      DESCRIPTION:  ｺｰﾃﾞｯｸが何に使用されているか
************************************************************************/
#define	CODEC_NOT_USE			(UBYTE)0
#define	CODEC_SCANNER_TX		(UBYTE)1
#define	CODEC_IMAGE_COPY		(UBYTE)2
#define	CODEC_DOCUMENT_STORE	(UBYTE)3
#define	CODEC_MEMORY_PRINT		(UBYTE)4
#define	CODEC_MEMORY_TX			(UBYTE)5
#define	CODEC_MEMORY_RX			(UBYTE)6
#define	CODEC_CHARACTER_PRINT	(UBYTE)7
#define	CODEC_CHARACTER_TX		(UBYTE)8
#define	CODEC_FIP_MEMORY_READ	(UBYTE)9
#define	CODEC_FIP_MEMORY_WRITE	(UBYTE)10
#define CODEC_PRINTER_RX		(UBYTE)11	/* Add By H.Hirao 1998/10/19 */
#define	CODEC_INITIALIZE		(UBYTE)0xFF		/**For MN864064 One Chip Dual Mode (SCN/PRN) Add By M.Kotani 1997/09/09*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/10/21(木)
*             TYPE:  define
*      VAR TO HOLD:  UBYTE CDC_ImageBufferStatus[2]
*      DESCRIPTION:  ｺｰﾃﾞｯｸのイメージメモリの状態
************************************************************************/
#define	CDC_NOT_ACCESS				(UBYTE)0	/*イメージバッファは使用していない*/
#define	CDC_LOWER_BLOCK_ACCESS		(UBYTE)1	/*Ａ面を符号化or復号化中*/
#define	CDC_UPPER_BLOCK_ACCESS		(UBYTE)2	/*Ｂ面を符号化or復号化中*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  94/6/2(木)
*             TYPE:  define
*      VAR TO HOLD:  UBYTE CDC_FontImageBuffer[3][80][16]
*      DESCRIPTION:  データ転送用のイメージバッファ
************************************************************************/
#define	CDC_CHARACTER_PRINT_A					(UBYTE)0
#define	CDC_CHARACTER_PRINT_B					(UBYTE)1
#define	CDC_CHARACTER_TX						(UBYTE)2

/************************************************************************
*               BY:  M.Kotani
*             DATE:  97/7/18
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  リストプリントにおける，一回のデータ転送ライン
************************************************************************/
#define	CDC_LIST_PRINT_LINE_COUNT				(UWORD)16

/*+++++++++++++++++++++++++++++++++++++++++++++++++++
 *  以下 ｺｰﾃﾞｯｸ I/O 定義  By M.Kotani 1996/10/14
 *  For MN86063 & MN86064
 ++++++++++++++++++++++++++++++++++++++++++++++++++*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ﾚｼﾞｽﾀ 定義
************************************************************************/
#define	CODEC_MSCR_DTCR		(UBYTE)0	/* R/W ﾏｽﾀｺﾝﾄﾛｰﾙ,ﾃﾞｰﾀｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ */
#define	CODEC_CDCR			(UBYTE)1	/* R/W 符号化,復号化ｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ */
#define	CODEC_CMDR			(UBYTE)2	/* W   ｺﾏﾝﾄﾞﾚｼﾞｽﾀ */
#define	CODEC_STIR			(UBYTE)3	/* R   状態,割り込みﾚｼﾞｽﾀ */
#define	CODEC_DMCR_DMIR		(UBYTE)4	/* R/W DMA転送ｺﾝﾄﾛｰﾙ,割り込みﾚｼﾞｽﾀ */
#define	CODEC_MAR			(UBYTE)5	/* R/W ﾒﾓﾘｱﾄﾞﾚｽﾚｼﾞｽﾀ */
#define	CODEC_PBR			(UBYTE)6	/* R/W ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧﾚｼﾞｽﾀ */
#define	CODEC_HDMR_MODR		(UBYTE)7	/* R/W ﾊｰﾄﾞﾏｽｸﾚｼﾞｽﾀ,ﾓｰﾄﾞﾚｼﾞｽﾀ Only MN86064 */
#define	CODEC_TSTR			(UBYTE)8	/* R/W ﾃｽﾄﾚｼﾞｽﾀ Only MN86064 (アクセスしないでください) */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMSCR_DTCR_Status
*      DESCRIPTION:  MSCR (Master Control Register)
************************************************************************/
#define	LONG_BIT	0x0001	/*ﾌﾚｰﾑ幅 (0:ｼｮｰﾄﾌﾚｰﾑ 2432bit, 1:ﾛﾝｸﾞﾌﾚｰﾑ 4864bit)*/		/*NM86063時のみ有効*/
#define	MODE_BIT	0x0001	/*動作ﾓｰﾄﾞ選択 (0:MN86064動作, 1:MN86063ｺﾝﾊﾟﾁ動作)*/	/*NM86064時のみ有効*/
#define	REQTM_BIT	0x0002	/*転送要求ﾀｲﾐﾝｸﾞ(0:ｴｯｼﾞ検出DMAC対応, 1:ﾚﾍﾞﾙ検出DMAC対応)*/
#define	DREQD1_BIT	0x0004	/*ﾃﾞｰﾀ入力要求(0:転送要求なし, 1:転送要求あり)*/
#define	DREQC1_BIT	0x0008	/*ﾃﾞｰﾀ出力要求(0:転送要求なし, 1:転送要求あり)*/
#define	DREQD0_BIT	0x0010	/*ﾃﾞｰﾀ入力要求(0:転送要求なし, 1:転送要求あり)*/
#define	DREQC0_BIT	0x0020	/*ﾃﾞｰﾀ出力要求(0:転送要求なし, 1:転送要求あり)*/
#define	PBRR_BIT	0x0040	/*PBRﾚﾃﾞｨ(0:PBRﾋﾞｼﾞｨ, 1:PBRﾚﾃﾞｨ)*/
#define	SWR_BIT		0x0080	/*ｿﾌﾄｳｪｱﾘｾｯﾄ(0:ﾘｾｯﾄ解除, 1:ﾘｾｯﾄ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMSCR_DTCR_Status
*      DESCRIPTION:  DTCR (Data Control Register)
************************************************************************/
#define	IOHEX_BIT	0x0100	/*I/Oﾊﾞｽ幅(0:8bit, 1:16bit) DTCR:IBHEX=1の時有効*/
#define	IBHEX_BIT	0x0200	/*ｲﾒｰｼﾞﾊﾞｽ幅(0:8bit, 1:16bit) 0の時ID0-7が有効*/
#define	BCODER_BIT	0x0400	/*符号ﾃﾞｰﾀﾋﾞｯﾄ送出順序*/
#define	BCSWAP_BIT	0x0800	/*符号ﾃﾞｰﾀﾊﾞｲﾄ交換*/
#define	BEODR0_BIT	0x1000	/*画像ﾃﾞｰﾀﾋﾞｯﾄ送出順序*/
#define	BESWP0_BIT	0x2000	/*画像ﾃﾞｰﾀﾊﾞｲﾄ交換*/
#define	BEODR1_BIT	0x4000	/*画像ﾃﾞｰﾀﾋﾞｯﾄ送出順序*/
#define	BESWP1_BIT	0x8000	/*画像ﾃﾞｰﾀﾊﾞｲﾄ交換*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecCDCR_Status
*      DESCRIPTION:  CDCR0 (Coder,Decoder Control Register Ch.0)
************************************************************************/
#define	ERROR0_BIT	0x0001	/*ｴﾗｰ処理(0:前ﾗｲﾝ置き換え, 1:白ﾗｲﾝ置き換え)*/
#define	DABT0_BIT	0x0002	/*復号化ｱﾎﾞｰﾄ(0:通常, 1:復号化ｱﾎﾞｰﾄ)*/
#define	IMOT00_BIT	0x0004	/*�ｮ画像ﾃﾞｰﾀ出力経路*/
#define	IMOT01_BIT	0x0008	/*�ｶ(0:ｲﾒｰｼﾞﾊﾞｽ, 1:-, 2:-, 3:ｼｽﾃﾑﾊﾞｽ)*/
#define	ERCHK0_BIT	0x0010	/*ｴﾗｰﾁｪｯｸ(0:通常, 1:画像ﾃﾞｰﾀ出力せず)*/
#define	OCT0_BIT	0x0020	/*ｵｸﾃｯﾄﾓｰﾄﾞ(0:通常, 1:ｵｸﾃｯﾄ化)*/
#define	IMIN00_BIT	0x0040	/*�ｮ画像ﾃﾞｰﾀ入力経路*/
#define	IMIN01_BIT	0x0080	/*�ｶ(0:ｲﾒｰｼﾞﾊﾞｽ, 1:-, 2:-, 3:ｼｽﾃﾑﾊﾞｽ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecCDCR_Status
*      DESCRIPTION:  CDCR1 (Coder,Decoder Control Register Ch.1)
************************************************************************/
#define	ERROR1_BIT	0x0100	/*ｴﾗｰ処理(0:前ﾗｲﾝ置き換え, 1:白ﾗｲﾝ置き換え)*/
#define	DABT1_BIT	0x0200	/*復号化ｱﾎﾞｰﾄ(0:通常, 1:復号化ｱﾎﾞｰﾄ)*/
#define	IMOT10_BIT	0x0400	/*�ｮ画像ﾃﾞｰﾀ出力経路*/
#define	IMOT11_BIT	0x0800	/*�ｶ(0:ｲﾒｰｼﾞﾊﾞｽ, 1:-, 2:-, 3:ｼｽﾃﾑﾊﾞｽ)*/
#define	ERCHK1_BIT	0x1000	/*ｴﾗｰﾁｪｯｸ(0:通常, 1:画像ﾃﾞｰﾀ出力せず)*/
#define	OCT1_BIT	0x2000	/*ｵｸﾃｯﾄﾓｰﾄﾞ(0:通常, 1:ｵｸﾃｯﾄ化)*/
#define	IMIN10_BIT	0x4000	/*�ｮ画像ﾃﾞｰﾀ入力経路*/
#define	IMIN11_BIT	0x8000	/*�ｶ(0:ｲﾒｰｼﾞﾊﾞｽ, 1:-, 2:-, 3:ｼｽﾃﾑﾊﾞｽ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecCMDR_Status
*      DESCRIPTION:  CMDR0 (Command Register Ch.0)
************************************************************************/
#define	CMD00_BIT	0x0001	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ0*/
#define	CMD01_BIT	0x0002	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ1*/
#define	CMD02_BIT	0x0004	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ2*/
#define	CMD03_BIT	0x0008	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ3*/
#define	CMD04_BIT	0x0010	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ4*/
#define	CMD05_BIT	0x0020	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ5*/
#define	JBIGRST_BIT	0x0040	/*JBIGﾘｽﾀｰﾄﾋﾞｯﾄ Only MN86064*/
#define	CMABT0_BIT	0x0080	/*ｺﾏﾝﾄﾞのｱﾎﾞｰﾄ(0:通常, 1:ｱﾎﾞｰﾄ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecCMDR_Status
*      DESCRIPTION:  CMDR1 (Command Register Ch.1)
************************************************************************/
#define	CMD10_BIT	0x0100	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ0*/
#define	CMD11_BIT	0x0200	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ1*/
#define	CMD12_BIT	0x0400	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ2*/
#define	CMD13_BIT	0x0800	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ3*/
#define	CMD14_BIT	0x1000	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ4*/
#define	CMD15_BIT	0x2000	/*ｺﾏﾝﾄﾞｺｰﾄﾞのﾋﾞｯﾄ5*/
#define	CMABT1_BIT	0x8000	/*ｺﾏﾝﾄﾞのｱﾎﾞｰﾄ(0:通常, 1:ｱﾎﾞｰﾄ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecCMDR_Status
*      DESCRIPTION:  Codec Command
************************************************************************/
	#define	CODEC_CMD_ALL_INIT			(UBYTE)0x00	/*初期化(全体)*/
	#define	CODEC_CMD_ENCODE_INIT		(UBYTE)0x01	/*初期化(符号化)*/
	#define	CODEC_CMD_DECODE_INIT		(UBYTE)0x02	/*初期化(復号化)*/
	#define	CODEC_CMD_TRANSFER_INIT		(UBYTE)0x03	/*初期化(ﾃﾞｰﾀ転送)*/
	#define	CODEC_CMD_INPUT_PARAM		(UBYTE)0x04	/*ﾊﾟﾗﾒｰﾀ転送(入力)*/
	#define	CODEC_CMD_OUTPUT_PARAM		(UBYTE)0x05	/*ﾊﾟﾗﾒｰﾀ転送(出力)*/
	#define	CODEC_CMD_MH_ENCODE			(UBYTE)0x06	/*符号化(MH)*/
	#define	CODEC_CMD_MR_ENCODE			(UBYTE)0x07	/*符号化(MR)*/
	#define	CODEC_CMD_MMR_ENCODE		(UBYTE)0x08	/*符号化(MMR)*/
	#define	CODEC_CMD_MG3_ENCODE		(UBYTE)0x09	/*符号化(MG3)*/
	#define	CODEC_CMD_MH_MMR_RTC		(UBYTE)0x0A	/*RTC符号(MH,MMR)*/
	#define	CODEC_CMD_MR_MG3_RTC		(UBYTE)0x0B	/*RTC符号(MR,MG3)*/
	#define	CODEC_CMD_MH_DECODE			(UBYTE)0x0C	/*復号化(MH)*/
	#define	CODEC_CMD_MR_DECODE			(UBYTE)0x0D	/*復号化(MR)*/
	#define	CODEC_CMD_MMR_DECODE		(UBYTE)0x0E	/*復号化(MMR)*/
	#define	CODEC_CMD_MG3_DECODE		(UBYTE)0x0F	/*復号化(MG3)*/
	#define	CODEC_CMD_MH_TO_MH			(UBYTE)0x10	/*符号変換(MH->MH)*/
	#define	CODEC_CMD_MH_TO_MR			(UBYTE)0x11	/*符号変換(MH->MR)*/
	#define	CODEC_CMD_MH_TO_MMR			(UBYTE)0x12	/*符号変換(MH->MMR)*/
	#define	CODEC_CMD_MH_TO_MG3			(UBYTE)0x13	/*符号変換(MH->MG3)*/
	#define	CODEC_CMD_MR_TO_MH			(UBYTE)0x14	/*符号変換(MR->MH)*/
	#define	CODEC_CMD_MR_TO_MR			(UBYTE)0x15	/*符号変換(MR->MR)*/
	#define	CODEC_CMD_MR_TO_MMR			(UBYTE)0x16	/*符号変換(MR->MMR)*/
	#define	CODEC_CMD_MR_TO_MG3			(UBYTE)0x17	/*符号変換(MR->MG3)*/
	#define	CODEC_CMD_MMR_TO_MH			(UBYTE)0x18	/*符号変換(MMR->MH)*/
	#define	CODEC_CMD_MMR_TO_MR			(UBYTE)0x19	/*符号変換(MMR->MR)*/
	#define	CODEC_CMD_MMR_TO_MMR		(UBYTE)0x1A	/*符号変換(MMR->MMR)*/
	#define	CODEC_CMD_MMR_TO_MG3		(UBYTE)0x1B	/*符号変換(MMR->MG3)*/
	#define	CODEC_CMD_MG3_TO_MH			(UBYTE)0x1C	/*符号変換(MG3->MH)*/
	#define	CODEC_CMD_MG3_TO_MR			(UBYTE)0x1D	/*符号変換(MG3->MR)*/
	#define	CODEC_CMD_MG3_TO_MMR		(UBYTE)0x1E	/*符号変換(MG3->MMR)*/
	#define	CODEC_CMD_MG3_TO_MG3		(UBYTE)0x1F	/*符号変換(MG3->MG3)*/
	#define	CODEC_CMD_DATA_TRANSFER		(UBYTE)0x20	/*ﾃﾞｰﾀ転送*/
	#define	CODEC_CMD_JBIG_ENCODE_INIT	(UBYTE)0x23	/*JBIG初期化(符号化) Only MN86064*/
	#define	CODEC_CMD_JBIG_DECODE_INIT	(UBYTE)0x24	/*JBIG初期化(復号化) Only MN86064*/
	#define	CODEC_CMD_JBIG_ENCODE		(UBYTE)0x25	/*符号化(JBIG) Only MN86064*/
	#define	CODEC_CMD_JBIG_DECODE		(UBYTE)0x26	/*復号化(JBIG) Only MN86064*/
	#define	CODEC_CMD_JBIG_TO_MH		(UBYTE)0x27	/*符号変換(JBIG->MH) Only MN86064*/
	#define	CODEC_CMD_JBIG_TO_MR		(UBYTE)0x28	/*符号変換(JBIG->MR) Only MN86064*/
	#define	CODEC_CMD_JBIG_TO_MMR		(UBYTE)0x29	/*符号変換(JBIG->MMR) Only MN86064*/
	#define	CODEC_CMD_JBIG_TO_MG3		(UBYTE)0x2A	/*符号変換(JBIG->MG3) Only MN86064*/
	#define	CODEC_CMD_MH_TO_JBIG		(UBYTE)0x2B	/*符号変換(MH->JBIG) Only MN86064*/
	#define	CODEC_CMD_MR_TO_JBIG		(UBYTE)0x2C	/*符号変換(MR->JBIG) Only MN86064*/
	#define	CODEC_CMD_MMR_TO_JBIG		(UBYTE)0x2D	/*符号変換(MMR->JBIG) Only MN86064*/
	#define	CODEC_CMD_MG3_TO_JBIG		(UBYTE)0x2E	/*符号変換(MG3->JBIG) Only MN86064*/
	#define	CODEC_CMD_JBIG_TO_JBIG		(UBYTE)0x2F	/*符号変換(JBIG->JBIG) Only MN86064*/
	#define	CODEC_CMD_NEWLEN			(UBYTE)0x30	/*NEWLENｺﾏﾝﾄﾞ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecSTIR_Status
*      DESCRIPTION:  STIR0 (Status,Interrupt Register Ch.0)
************************************************************************/
#define	CMDE0_BIT	0x0001	/*ｺﾏﾝﾄﾞ終了(0:通常, 1:ｺﾏﾝﾄﾞ終了)*/
#define	JBIGIRQ_BIT	0x0002	/*JBIGｺﾏﾝﾄﾞ割り込み(0:通常, 1:割り込み発生) Only MN86064*/
#define	RTCDT0_BIT	0x0004	/*RTC符号検出(0:通常, 1:RTC符号検出)*/
#define	DERR0_BIT	0x0008	/*復元ｴﾗｰ(0:通常, 1:復元ｴﾗｰあり)*/
#define	ABACT0_BIT	0x0010	/*ｱﾎﾞｰﾄ受け付け(0:通常, 1:ｱﾎﾞｰﾄ受け付け)*/
/*#define	DREQD0_BIT	0x0020	ﾃﾞｰﾀ入力要求(0:転送要求なし, 1:転送要求あり)*/
/*#define	DREQC0_BIT	0x0040	ﾃﾞｰﾀ出力要求(0:転送要求なし, 1:転送要求あり)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecSTIR_Status
*      DESCRIPTION:  STIR1 (Status,Interrupt Register Ch.1)
************************************************************************/
#define	CMDE1_BIT	0x0100	/*ｺﾏﾝﾄﾞ終了(0:通常, 1:ｺﾏﾝﾄﾞ終了)*/
#define	RTCDT1_BIT	0x0400	/*RTC符号検出(0:通常, 1:RTC符号検出)*/
#define	DERR1_BIT	0x0800	/*復元ｴﾗｰ(0:通常, 1:復元ｴﾗｰあり)*/
#define	ABACT1_BIT	0x1000	/*ｱﾎﾞｰﾄ受け付け(0:通常, 1:ｱﾎﾞｰﾄ受け付け)*/
/*#define	DREQD1_BIT	0x2000	ﾃﾞｰﾀ入力要求(0:転送要求なし, 1:転送要求あり)*/
/*#define	DREQC1_BIT	0x4000	ﾃﾞｰﾀ出力要求(0:転送要求なし, 1:転送要求あり)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecSTIR_Status
*      DESCRIPTION:  STIR0,1 (Status,Interrupt Register Ch.0,1)
************************************************************************/
/*#define	PBRR_BIT	0x0080	PBRﾚﾃﾞｨ(0:PBRﾋﾞｼﾞｨ, 1:PBRﾚﾃﾞｨ)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecDMCR_DMIR_Status
*      DESCRIPTION:  DMCR (DMA Control Register)
************************************************************************/
#define	MBEND0_BIT	0x0002	/*DBEND0ﾏｽｸ(0:割り込みﾏｽｸ, 1:割り込み許可)*/
#define	DMABT0_BIT	0x0004	/*DMA0転送ｱﾎﾞｰﾄ(0:通常, 1:ｱﾎﾞｰﾄ)*/
#define	DMENB0_BIT	0x0008	/*DMA0転送ｲﾈｰﾌﾞﾙ*/
#define	MBEND1_BIT	0x0020	/*DBEND1ﾏｽｸ(0:割り込みﾏｽｸ, 1:割り込み許可)*/
#define	DMABT1_BIT	0x0040	/*DMA1転送ｱﾎﾞｰﾄ(0:通常, 1:ｱﾎﾞｰﾄ)*/
#define	DMENB1_BIT	0x0080	/*DMA1転送ｲﾈｰﾌﾞﾙ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecDMCR_DMIR_Status
*      DESCRIPTION:  DMIR (DMA Interrupt Register)
************************************************************************/
#define	DBEND0_BIT	0x0200	/*DMA転送ﾁｬﾝﾈﾙ1ﾌﾞﾛｯｸ転送終了(0:通常, 1:ﾌﾞﾛｯｸ終了)*/
#define	DABOT0_BIT	0x0400	/*DMA転送ｱﾎﾞｰﾄ受け付け(0:通常, 1:ｱﾎﾞｰﾄ受け付け)*/
#define	DBEND1_BIT	0x2000	/*DMA転送ﾁｬﾝﾈﾙ1ﾌﾞﾛｯｸ転送終了(0:通常, 1:ﾌﾞﾛｯｸ終了)*/
#define	DABOT1_BIT	0x4000	/*DMA転送ｱﾎﾞｰﾄ受け付け(0:通常, 1:ｱﾎﾞｰﾄ受け付け)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMAR_Status
*      DESCRIPTION:  MARL (Memory Address Register Lower Byte)
************************************************************************/
#define	MAD0		0x0001	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD1		0x0002	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD2		0x0004	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD3		0x0008	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD4		0x0010	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD5		0x0020	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD6		0x0040	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD7		0x0080	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMAR_Status
*      DESCRIPTION:  MARU (Memory Address Register Upper Byte)
************************************************************************/
#define	MAD8		0x0100	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD9		0x0200	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD10		0x0400	/*ﾒﾓﾘｱﾄﾞﾚｽ*/
#define	MAD11		0x0800	/*ﾒﾓﾘｱﾄﾞﾚｽ Only MN86064*/
#define	MAR_R_W_BIT	0x8000	/*ﾘｰﾄﾞ/ﾗｲﾄ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/09(木)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMAR_Status
*      DESCRIPTION:  MAR (Memory Address Register) に
*                    ｾｯﾄするﾊﾟﾗﾒｰﾀﾚｼﾞｽﾀｱﾄﾞﾚｽの定義
************************************************************************/
#define		FRWORD_ADR		0x0600		/*ﾌﾚｰﾑﾜｰﾄﾞ数*/
#define		INWORD_ADR		0x0601		/*入力ﾜｰﾄﾞ数*/
#define		INLINE_ADR		0x0602		/*入力ﾗｲﾝ数*/
#define		OTWORD_ADR		0x0603		/*出力ﾜｰﾄﾞ数*/
#define		I_OBXR_ADR		0x0604		/*入力ｵﾌｾｯﾄ*/
#define		O_OBXR_ADR		0x0604		/*出力ｵﾌｾｯﾄ*/
#define		C0_STRA_ADR		0x0605		/*符号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
#define		C0_PWDR_ADR		0x0606		/*符号化ﾍﾟｰｼﾞ幅*/
#define		C0_OBXR_ADR		0x0607		/*符号化ｵﾌｾｯﾄ*/
#define		C0_KPR_ADR		0x0608		/*符号化Kﾊﾟﾗﾒｰﾀ*/
#define		C0_RTCR_ADR		0x0608		/*符号化RTC数*/
#define		C0_LCONT_ADR	0x0609		/*符号化ﾗｲﾝｶｳﾝﾀ*/
#define		C0_MCLR_ADR		0x060A		/*符号化最小符号ﾊﾞｲﾄ数*/
#define		C0_HCONV_ADR	0x060B		/*符号化主走査方向変換率*/
#define		C0_VCONV_ADR	0x060C		/*符号化副走査方向変換率*/
#define		C0_LMASK_ADR	0x060D		/*符号化左側白ﾏｽｸ*/
#define		C0_RMASK_ADR	0x060E		/*符号化右側白ﾏｽｸ*/
#define		C0_MTOPA_ADR	0x060F		/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		C0_MENDA_ADR	0x0610		/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		D0_STRA_ADR		0x0611		/*復号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
#define		D0_PWDR_ADR		0x0612		/*復号化ﾍﾟｰｼﾞ幅*/
#define		D0_OBXR_ADR		0x0613		/*復号化ｵﾌｾｯﾄ*/
#define		D0_RTCR_ADR		0x0614		/*復号化RTC数*/
#define		D0_BLGR_ADR		0x0615		/*復号化処理ﾗｲﾝ数*/
#define		D0_LCONT_ADR	0x0616		/*復号化ﾗｲﾝｶｳﾝﾀ*/
#define		D0_UWLIN_ADR	0x0617		/*上端白ライン数*/	/*MN86064で追加*//* MN86063 Dummy1 Extra Area*/
#define		D0_LWLIN_ADR	0x0617		/*下端白ライン数*/	/*MN86064で追加*//* MN86063 Dummy1 Extra Area*/
#define		D0_ELIN_ADR		0x0618		/*復号化ｴﾗｰﾗｲﾝ数*/
#define		D0_HCONV_ADR	0x0619		/*復号化主走査方向変換率*/
#define		D0_VCONV_ADR	0x061A		/*復号化副走査方向変換率*/
#define		D0_LMASK_ADR	0x061B		/*復号化左側白ﾏｽｸ*/
#define		D0_RMASK_ADR	0x061C		/*復号化右側白ﾏｽｸ*/
#define		D0_MTOPA_ADR	0x061D		/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		D0_MENDA_ADR	0x061E		/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		C1_STRA_ADR		0x061F		/*符号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
#define		C1_PWDR_ADR		0x0620		/*符号化ﾍﾟｰｼﾞ幅*/
#define		C1_OBXR_ADR		0x0621		/*符号化ｵﾌｾｯﾄ*/
#define		C1_RTCR_ADR		0x0622		/*符号化RTC数*/
#define		C1_KPR_ADR		0x0622		/*符号化Kﾊﾟﾗﾒｰﾀ*/
#define		C1_LCONT_ADR	0x0623		/*符号化ﾗｲﾝｶｳﾝﾀ*/
#define		C1_MCLR_ADR		0x0624		/*符号化最小符号ﾊﾞｲﾄ数*/
#define		C1_HCONV_ADR	0x0625		/*符号化主走査方向変換率*/
#define		C1_VCONV_ADR	0x0626		/*符号化副走査方向変換率*/
#define		C1_LMASK_ADR	0x0627		/*符号化左側白ﾏｽｸ*/
#define		C1_RMASK_ADR	0x0628		/*符号化右側白ﾏｽｸ*/
#define		C1_MTOPA_ADR	0x0629		/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		C1_MENDA_ADR	0x062A		/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		D1_STRA_ADR		0x062B		/*復号化ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/
#define		D1_PWDR_ADR		0x062C		/*復号化ﾍﾟｰｼﾞ幅*/
#define		D1_OBXR_ADR		0x062D		/*復号化ｵﾌｾｯﾄ*/
#define		D1_RTCR_ADR		0x062E		/*復号化RTC数*/
#define		D1_BLGR_ADR		0x062F		/*復号化処理ﾗｲﾝ数*/
#define		D1_LCONT_ADR	0x0630		/*復号化ﾗｲﾝｶｳﾝﾀ*/
#define		D1_ELIN_ADR		0x0631		/*復号化ｴﾗｰﾗｲﾝ数*/
#define		D1_HCONV_ADR	0x0632		/*復号化主走査方向変換率*/
#define		D1_VCONV_ADR	0x0633		/*復号化副走査方向変換率*/
#define		D1_LMASK_ADR	0x0634		/*復号化左側白ﾏｽｸ*/
#define		D1_RMASK_ADR	0x0635		/*復号化右側白ﾏｽｸ*/
#define		D1_MTOPA_ADR	0x0636		/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		D1_MENDA_ADR	0x0637		/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		B_STRA0_ADR		0x0638		/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ0*/
#define		B_STRA1_ADR		0x0639		/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ1*/
#define		B_HCONV_ADR		0x063A		/*ﾃﾞｰﾀ転送主走査方向変換率*/
#define		B_VCONV_ADR		0x063B		/*ﾃﾞｰﾀ転送副走査方向変換率*/
#define		B_LMASK_ADR		0x063C		/*ﾃﾞｰﾀ転送左側白ﾏｽｸ*/
#define		B_RMASK_ADR		0x063D		/*ﾃﾞｰﾀ転送右側白ﾏｽｸ*/
#define		T0_STRA_ADR		0x063F		/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
#define		T0_WORD_ADR		0x0640		/*DMA転送ﾜｰﾄﾞ数*/
#define		T0_BLGR_ADR		0x0641		/*DMA転送ﾗｲﾝ数*/
#define		T0_MTOPA_ADR	0x0642		/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		T0_MENDA_ADR	0x0644		/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		T1_STRA_ADR		0x0646		/*DMA転送先頭ｱﾄﾞﾚｽﾎﾟｲﾝﾀ*/
#define		T1_WORD_ADR		0x0647		/*DMA転送ﾜｰﾄﾞ数*/
#define		T1_BLGR_ADR		0x0648		/*DMA転送ﾗｲﾝ数*/
#define		T1_MTOPA_ADR	0x0649		/*DMA転送ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
#define		T1_MENDA_ADR	0x064B		/*DMA転送ﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
#define		C0_REFA_ADR		0x064C		/*符号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy6 Extra Area*/
#define		C1_REFA_ADR		0x064D		/*符号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy7 Extra Area*/
#define		D0_REFA_ADR		0x064E		/*復号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy8 Extra Area*/
#define		D1_REFA_ADR		0x064F		/*復号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy9 Extra Area*/
#define		STRADD_ADR		0x0650		/*ﾒﾓﾘ先頭ｱﾄﾞﾚｽ*/
#define		ENDADD_ADR		0x0651		/*ﾒﾓﾘ最終ｱﾄﾞﾚｽ*/
/*MN86064で追加*/
#define		VMN_ADR			0x0654		/*間引き/OR指定*/
#define		IMGWT_ADR		0x0655		/*ｲﾒｰｼﾞﾊﾞｽwaitｻｲｸﾙ数*/
#define		IMGBNK0_ADR		0x0656		/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定0*/
#define		IMGBNK1_ADR		0x0657		/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定1*/
#define		Y1CREFA_ADR		0x0658		/*JBIG符号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
#define		Y2CREFA_ADR		0x0659		/*JBIG符号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
#define		Y1DREFA_ADR		0x065A		/*JBIG復号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
#define		Y2DREFA_ADR		0x065B		/*JBIG復号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
#define		C_QMCR_ADR		0x065E		/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
#define		C_QMIR_ADR		0x065F		/*QM割り込みﾚｼﾞｽﾀ*/
#define		C_QMIRM_ADR		0x0660		/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
#define		C_YD_ADR		0x0661		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
#define		C_L0_ADR		0x0662		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
#define		C_MX_ADR		0x0663		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#define		C_TX1_ADR		0x0664		/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
#define		C_TX0_ADR		0x0664		/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
#define		C_YAT0_ADR		0x0665		/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
#define		C_YAT1_ADR		0x0666		/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
#define		C_QMBUF0_ADR	0x0667		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
#define		C_QMBUF1_ADR	0x0668		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
#define		D_QMCR_ADR		0x0669		/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
#define		D_QMIR_ADR		0x066A		/*QM割り込みﾚｼﾞｽﾀ*/
#define		D_QMIRM_ADR		0x066B		/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
#define		D_YD_ADR		0x066C		/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
#define		D_L0_ADR		0x066D		/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
#define		D_MX_ADR		0x066E		/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#define		D_TX1_ADR		0x066F		/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
#define		D_TX0_ADR		0x066F		/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
#define		D_YAT0_ADR		0x0670		/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
#define		D_YAT1_ADR		0x0671		/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
#define		D_QMBUF0_ADR	0x0672		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
#define		D_QMBUF1_ADR	0x0673		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecPBR_Status
*      DESCRIPTION:  PBRL (Parameter Buffer Register Lower Byte)
************************************************************************/
#define	PD0			0x0001	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD1			0x0002	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD2			0x0004	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD3			0x0008	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD4			0x0010	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD5			0x0020	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD6			0x0040	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD7			0x0080	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  93/09/06(月)
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecPBR_Status
*      DESCRIPTION:  PBRU (Parameter Buffer Register Upper Byte)
************************************************************************/
#define	PD8			0x0100	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD9			0x0200	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD10		0x0400	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD11		0x0800	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD12		0x1000	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD13		0x2000	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD14		0x4000	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
#define	PD15		0x8000	/*ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧ*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  97/09/18
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecHDMR_MODR_Status
*      DESCRIPTION:  HDMR (Hard Mask Register) Only MN86064
************************************************************************/
#define	HDENB_BIT	0x0001	/*ﾊｰﾄﾞﾏｽｸ有効 (0:無効, 1:有効)*/
#define	MINTR0_BIT	0x0002	/*INTR0ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	MINTR1_BIT	0x0004	/*INTR1ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	MREQC0_BIT	0x0008	/*REQC0ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	MREQC1_BIT	0x0010	/*REQC1ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	MREQD0_BIT	0x0020	/*REQD0ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	MREQD1_BIT	0x0040	/*REQD1ﾏｽｸ解除 (0:ﾏｽｸ, 1:ﾏｽｸ解除)*/
#define	REQOR_BIT	0x0080	/*REQC0/1, REQD0/1OR処理有効 (0:無効, 1:有効)*/
/************************************************************************
*               BY:  M.Kotani
*             DATE:  97/09/18
*             TYPE:  DEFINE
*      VAR TO HOLD:  UWORD CodecMDMR_MODR_Status
*      DESCRIPTION:  MODR (Mode Register) Only MN86064
************************************************************************/
#define	EXAENB_BIT	0x0100	/*外部ｱﾄﾞﾚｽ拡張有効 (0:DMAスタート信号有効, 1:外部ｱﾄﾞﾚｽ拡張有効*/
#define	DECODER_BIT	0x0800	/*復号化時入力ビット順序 (DTCRの代わり)*/
#define	DECSWAP_BIT	0x1000	/*復号化時入力バイト交換 (DTCRの代わり)*/
#define	ENCODER_BIT	0x2000	/*符号化時出力ビット順序 (DTCRの代わり)*/
#define	ENCSWAP_BIT	0x4000	/*符号化時出力バイト交換 (DTCRの代わり)*/
#define	MODRENB_BIT	0x8000	/*BCSWAP/BCODER有効 (0:DTCR有効, 1:MODR有効)*/
/************************************************************************
*               BY:  T.Soneoka
*             DATE:  97/12/9
*             TYPE:  DEFINE
*      VAR TO HOLD:  CodecParameterRegister[].C_QMCR_Status
*                 :  CodecParameterRegister[].D_QMCR_Status
*      DESCRIPTION:  QMCR (QMコントロールレジスタ) Only MN86064
************************************************************************/
#define	AT1ENB_BIT	0x0200	/*0:AT1無効 1:AT0有効値設定*/
#define	AT0ENB_BIT	0x0400	/*0:AT0無効 1:AT1有効値設定*/
#define	SDRST_BIT	0x0800	/*0:終端ﾏｰｶSDNORM選択 1:終端ﾏｰｶSDRST選択*/
#define	TPBON_BIT	0x2000	/*0:TPモード無効 1:TPモード有効*/
#define	VLENGTH_BIT	0x4000	/*0:NEWLENﾏｰｶ無効 1:NEWLENﾏｰｶ有効*/
#define	LRLTWO_BIT	0x8000	/*0:3ラインテンプレート選択 1:2ラインテンプレート選択*/
/************************************************************************
*               BY:  T.Soneoka
*             DATE:  97/12/9
*             TYPE:  DEFINE
*      VAR TO HOLD:  CodecParameterRegister[].C_QMIR_Status
*                 :  CodecParameterRegister[].D_QMIR_Status
*      DESCRIPTION:  QMIR (QM割り込みレジスタ) Only MN86064
************************************************************************/
#define	ERR0_BIT	0x0001	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
#define	ERR1_BIT	0x0002	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
#define	PAGEND_BIT	0x0080	/*1ページ処理終了*/
#define	DETERR_BIT	0x0100	/*エラー検出（ビット1,0参照）*/
#define	DETABT_BIT	0x0200	/*アボートBIDマーカの検出*/
#define	DETNWL_BIT	0x0400	/*NEWLENマーカの検出*/
#define	DETCMT_BIT	0x0800	/*コメントマーカの検出*/
#define	DETATM_BIT	0x1000	/*ATMOVEマーカの検出（1ストライプ3個以上）*/
#define	ATMREQ_BIT	0x4000	/*ATMOVEパラメータ（τx，YAT）の書き込み要求*/
#define	STRPIR_BIT	0x8000	/*1ストライプ処理終了*/
/************************************************************************
*               BY:  T.Soneoka
*             DATE:  97/12/9
*             TYPE:  DEFINE
*      VAR TO HOLD:  CodecParameterRegister[].C_QMIRM_Status
*                 :  CodecParameterRegister[].D_QMIRM_Status
*      DESCRIPTION:  QMIR (QM割り込みレジスタ) Only MN86064
************************************************************************/
#define	PAGENDM_BIT	0x0080	/*PAGEENDの割り込みマスク*/
#define	DETABTM_BIT	0x0200	/*DETABTの割り込みマスク*/
#define	DETNWLM_BIT	0x0400	/*DETNWLの割り込みマスク*/
#define	DETCMTM_BIT	0x0800	/*DETCMTの割り込みマスク*/
#define	ATMREQM_BIT	0x4000	/*ATMREQの割り込みマスク*/
#define	STRPIRM_BIT	0x8000	/*STRPIRの割り込みマスク*/

/* ここからJBIGデファインです
** \src\atlanta\scd\define\jbg_def.hからコピーしてきました
** by T.Soneoka 1997/12/17 */

/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/22
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   最大値定義
************************************************************************/
#define JBG_BYTE_MARGIN_LEFT		1				/** ４画素 */
#define JBG_BYTE_MARGIN_RIGHT		1				/** ２画素 */
#define JBG_MAX_REFERENCE_X		(912 + JBG_BYTE_MARGIN_LEFT + JBG_BYTE_MARGIN_RIGHT)	/** 参照ライン(A3 600DPI)7296Dots */
#define JBG_MAX_REFERENCE_Y		3		/** 参照ライン(3 Lines) (y, y-1. y-2)*/
#define JBG_MAX_CX				1024	/** コンテクスト２値１０画素＝１０２４値*/
#define JBG_MAX_ST				113		/** 確率推定ステータス ０～１１２＝１１３値*/
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/30
*        TYPE:   DEFINE
* VAR TO HOLD:   JBG_DecodeEndStatus
* DESCRIPTION:   デコード終了時の状態
************************************************************************/
#define JBG_BIT_RESET	0x01				/** ストライプ終了時にパラメータリセット要求あり */
#define JBG_BIT_END		0x02				/** ストライプ正常終了 */
#define JBG_BIT_ABORT	0x04				/** ストライプ異常終了 */
#define JBG_BIT_ERROR	0x80				/** デコードエラー発生 */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/24
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   記号化された定数
************************************************************************/
#define JBG_SYMBOL_ABORT	0x04	/** アボート */
#define JBG_SYMBOL_ATMOVE	0x06	/** ＡＴ移動 */
#define JBG_SYMBOL_COMMENT	0x07	/** プライベートコメント */
#define JBG_SYMBOL_ESC		0xff	/** エスケープ */
#define JBG_SYMBOL_NEWLEN	0x05	/** 新しい長さ */
#define JBG_SYMBOL_RESERVE	0x01	/** リザーブ */
#define JBG_SYMBOL_SDNORM	0x02	/** ストライプデータ終了 */
#define JBG_SYMBOL_SDRST	0x03	/** ストライプデータ終了時のリセット */
#define JBG_SYMBOL_STUFF	0x00	/** スタッフ */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/23
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   オーダーバイトのビット定義
************************************************************************/
#define JBG_BIT_SMID	0x01	/** 中央のループインデックスはストライプ	（Ｔ．８５では０固定） */
#define JBG_BIT_ILEAVE	0x02	/** インタリーブされた複数のビットプレーン	（Ｔ．８５では０固定） */
#define JBG_BIT_SEQ		0x04	/** シーケンシャル							（Ｔ．８５では０固定） */
#define JBG_BIT_HITOLO	0x08	/** 上位から下位へ							（Ｔ．８５では０固定） */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/23
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   オプションバイトのビット定義
************************************************************************/
#define JBG_BIT_DPLAST	0x01	/** 最後のＤＰ								（Ｔ．８５では０固定） */
#define JBG_BIT_DPPRIV	0x02	/** プライベートＤＰ						（Ｔ．８５では０固定） */
#define JBG_BIT_DPON	0x04	/** ＤＰ使用								（Ｔ．８５では０固定） */
#define JBG_BIT_TPBON	0x08	/** 最低解像度レイヤのＴＰ使用　０：ＯＦＦ、１：ＯＮ */
#define JBG_BIT_TPDON	0x10	/** 差分レイヤのＴＰを使用する				（Ｔ．８５では０固定） */
#define JBG_BIT_VLENGTH	0x20	/** ０：ＮＥＷＬＥＮを使用しない、１：ＮＥＷＬＥＮ使用をする */
#define JBG_BIT_LRLTWO	0x40	/** ０：３ラインテンプレート、１：２ラインテンプレート */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/23
*             TYPE:  struct
*      VAR TO HOLD:  JBG_BIH
*      DESCRIPTION:  ＢＩＨ定義(bi-level image header)
************************************************************************/
struct JBG_BIH_Data_t {	/** ２０バイト */
	UBYTE	DL;			/** 送るべき最初のレイヤ	（Ｔ．８５では０固定） */
	UBYTE	D;			/** 差分レイヤの数			（Ｔ．８５では０固定） */
	UBYTE	P;			/** ビットプレーン数		（Ｔ．８５では１固定） */
	UBYTE	dummy;		/** フィルバイト			（Ｔ．８２で０固定） */
	UDWORD	XD;			/** 水平方向の画素数（Ｔ．８５ではＧ３はＴ．４、Ｇ４はＴ．５６３に準拠） */
	UDWORD	YD;			/** 垂直方向の画素数（Ｔ．８２で１～４２９４９６７２９５） */
	UDWORD	L0;			/** 最低解像度のストライブのライン数（Ｔ．８５で１２８ライン固定、独自手順で変更可能） */
	UBYTE	MX;			/** ＡＴ画素に許される最大水平オフセット（Ｔ．８５では０～１２７） */
	UBYTE	MY;			/** ＡＴ画素に許される最大垂直オフセット（Ｔ．８５では０固定） */
	UBYTE	Order;		/** ＳＣＤの順序（オーダービット定義参照） */
	UBYTE	Options;	/** オプション（オプションビット定義参照） */
};
/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/30
*             TYPE:  struct
*      VAR TO HOLD:  JBG_ATMOVE
*      DESCRIPTION:  ＡＴＭＯＶＥ
************************************************************************/
struct JBG_ATMOVE_Data_t {	/** ８バイト */
	UBYTE Esc;
	UBYTE Atmove;
	UDWORD Yat;
	UBYTE Tx;
	UBYTE Ty;
};
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＮＥＷＬＥＮ
*		 REFERENCE:
************************************************************************/
struct JBG_NEWLEN_Data_t {	/** ６バイト */
	UBYTE Esc;
	UBYTE Newlen;
	UDWORD Yd;
};
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＣＯＭＭＥＮＴ
*		 REFERENCE:
************************************************************************/
struct JBG_COMMENT_Data_t {	/** ６バイト */
	UBYTE Esc;
	UBYTE Comment;
	UDWORD Lc;
};

/* Added by H.Kubo 1997/12/19 */
/* Used in cdc_ctx.c */
#define CDC_ENCODE_TTI 1
#define CDC_ENCODE_COVERPAGE 2
#define CDC_ENCODE_RCR 3

/* 不達通知用 H.Kubo 1998/01/19 */
#define CDC_REQUEST_NEW_LINE 0x01
#define CDC_REQUEST_PAGE_END 0x02

/*  追加 by T.Soneoka 1998/01/12 */
#define CDC_SCODEC_DRAM_TO_CODEC	0
#define CDC_SCODEC_CODEC_TO_DRAM	1


#if (PRO_COM_CODEC_TYPE == MN86064)
 #if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1999/10/19 Y.Murata */
/************************************************************************
*				BY:	 K.Okada
*			  DATE:	 1999/05/27
*	   DESCRIPTION:	 キャラクタ送信用コーデックパラメータ
*		 REFERENCE:
************************************************************************/
/********************
** 16ドットフォント用
********************/
#define CDC_CTX_INWORD	40		/* 入力ワード数 */
#define CDC_CTX_INLINE	16		/* 入力ライン数 */
 #endif
#endif

#endif
