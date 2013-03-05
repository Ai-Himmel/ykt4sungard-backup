#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\product.h"
/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/14
*        FILE NAME:  cdc_tbl.c
*       Task ID No:  Not Valid
*      DESCRIPTION:  ｺｰﾃﾞｯｸ ﾚｼﾞｽﾀｱﾄﾞﾚｽ Romﾃｰﾌﾞﾙ定義 For MN86063
*        REFERENCE:
************************************************************************/
/*ホンちゃん用テーブル ※アドレスは４バイトおき*/
/*使用するコーデックの個数によって１つのコーデックを並列処理させます*/

/*
** ハードコーデック３個使用
*/
#if (PRO_CODEC_NUMBER == CDC_TRIPLE)	/*ハードコーデック３個使用*/
 #if defined(HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined (STOCKHM2) /* HINOKI2 2001/11/13 T.Takagi */
 /* HINOKIの通信のみハードコーデック 1998/09/30 By H.Hirao */
CONST UDWORD CodecRegisterAddressTable[CODEC_MAX][9] = {
	/*Scanner Codec Register Address*/
	{0},
	/*Printer Codec Register Address*/
	{0},
	/*Communication Codec Register Address*/
	{0xE00000,	/*CODEC_MSCR_DTCR*/
	 0xE00004,	/*CODEC_CDCR*/
	 0xE00008,	/*CODEC_CMDR*/
	 0xE00008,	/*CODEC_STIR*/
	 0xE0000C,	/*CODEC_DMCR_DMIR*/
	 0xE00010,	/*CODEC_MAR*/
	 0xE00014,	/*CODEC_PBR*/
	 0xE00018,	/*CODEC_HDMR_MODE*/
	 0xE0001C}	/*CODEC_TSTR*/
};
 #else /* HINOKI以外の場合 */
CONST UDWORD CodecRegisterAddressTable[CODEC_MAX][9] = {
	/*Scanner Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Printer Codec Register Address*/
  #if defined(SAKAKI)		/* 1998/11/20 H.Yoshikawa */
	{0xC70000,	/*CODEC_MSCR_DTCR*/
	 0xC70000,	/*CODEC_CDCR*/
	 0xC70000,	/*CODEC_CMDR*/
	 0xC70000,	/*CODEC_STIR*/
	 0xC7000C,	/*CODEC_DMCR_DMIR*/
	 0xC70000,	/*CODEC_MAR*/
	 0xC70000,	/*CODEC_PBR*/
	 0xC70000,	/*CODEC_HDMR_MODE*/
	 0xC70000},	/*CODEC_TSTR*/
  #else
	/*Printer Codec Register Address*/
	{0xC30000,	/*CODEC_MSCR_DTCR*/
	 0xC30004,	/*CODEC_CDCR*/
	 0xC30008,	/*CODEC_CMDR*/
	 0xC30008,	/*CODEC_STIR*/
	 0xC3000C,	/*CODEC_DMCR_DMIR*/
	 0xC30010,	/*CODEC_MAR*/
	 0xC30014,	/*CODEC_PBR*/
	 0xC30018,	/*CODEC_HDMR_MODE*/
	 0xC3001C},	/*CODEC_TSTR*/
  #endif

	/*Communication Codec Register Address*/
	{0xC40200,	/*CODEC_MSCR_DTCR*/
	 0xC40204,	/*CODEC_CDCR*/
	 0xC40208,	/*CODEC_CMDR*/
	 0xC40208,	/*CODEC_STIR*/
	 0xC4020C,	/*CODEC_DMCR_DMIR*/
	 0xC40210,	/*CODEC_MAR*/
	 0xC40214,	/*CODEC_PBR*/
	 0xC40218,	/*CODEC_HDMR_MODE*/
	 0xC4021C}	/*CODEC_TSTR*/
};
 #endif
#endif

/*
**ハードコーデック２個使用
*/
#if (PRO_CODEC_NUMBER == CDC_DOUBLE)	/*ハードコーデック２個使用*/
CONST UDWORD CodecRegisterAddressTable[CODEC_MAX][9] = {
	/*Scanner Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Printer Codec Register Address*/
	{0xC30000,	/*CODEC_MSCR_DTCR*/
	 0xC30004,	/*CODEC_CDCR*/
	 0xC30008,	/*CODEC_CMDR*/
	 0xC30008,	/*CODEC_STIR*/
	 0xC3000C,	/*CODEC_DMCR_DMIR*/
	 0xC30010,	/*CODEC_MAR*/
	 0xC30014,	/*CODEC_PBR*/
	 0xC30018,	/*CODEC_HDMR_MODE*/
	 0xC3001C},	/*CODEC_TSTR*/
	/*Communication Codec Register Address*/
	{0xC40200,	/*CODEC_MSCR_DTCR*/
	 0xC40204,	/*CODEC_CDCR*/
	 0xC40208,	/*CODEC_CMDR*/
	 0xC40208,	/*CODEC_STIR*/
	 0xC4020C,	/*CODEC_DMCR_DMIR*/
	 0xC40210,	/*CODEC_MAR*/
	 0xC40214,	/*CODEC_PBR*/
	 0xC40218,	/*CODEC_HDMR_MODE*/
	 0xC4021C}	/*CODEC_TSTR*/
};
#endif

/*
**ハードコーデック１個使用
*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
CONST UDWORD CodecRegisterAddressTable[CODEC_MAX][9] = {

 #if defined(POPLAR_F)
	/*Scanner Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Printer Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Communication Codec Register Address*/
	{0xC40200,	/*CODEC_MSCR_DTCR*/
	 0xC40204,	/*CODEC_CDCR*/
	 0xC40208,	/*CODEC_CMDR*/
	 0xC40208,	/*CODEC_STIR*/
	 0xC4020C,	/*CODEC_DMCR_DMIR*/
	 0xC40210,	/*CODEC_MAR*/
	 0xC40214,	/*CODEC_PBR*/
	 0xC40218,	/*CODEC_HDMR_MODE*/
	 0xC4021C}	/*CODEC_TSTR*/
 #else
	/*Scanner Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Printer Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C},	/*CODEC_TSTR*/
	/*Communication Codec Register Address*/
	{0xC20600,	/*CODEC_MSCR_DTCR*/
	 0xC20604,	/*CODEC_CDCR*/
	 0xC20608,	/*CODEC_CMDR*/
	 0xC20608,	/*CODEC_STIR*/
	 0xC2060C,	/*CODEC_DMCR_DMIR*/
	 0xC20610,	/*CODEC_MAR*/
	 0xC20614,	/*CODEC_PBR*/
	 0xC20618,	/*CODEC_HDMR_MODE*/
	 0xC2061C}	/*CODEC_TSTR*/
 #endif
};
#endif
