/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1996/10/16
*		 FILE NAME:	 cdc_ctx.c
*	   DESCRIPTION:	 キャラクタ送信関連関数群
*					 cdc_main.cよりコールされる
*  PUBLIC ROUTINES:	 UDWORD CDC_SetTTI(void);
*					 UDWORD CDC_SetCoverPage(void);
*					 UDWORD CDC_SetRCR(void);
* PRIVATE ROUTINES:	 void CDC_CTxSetupCodec(void);
*					 void CDC_CTxSetupDMAU(void);
*					 void CDC_SetDummyLine(UBYTE line);
*		 REFERENCE:	 SH7043 for POPLAR/ANZU_L
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\sysdoc.h"
/*MON*/
/*DMA*/
#include  "\src\atlanta\define\dma_def.h"
#include  "\src\atlanta\define\dma_blk.h"
#include  "\src\atlanta\define\dma_pro.h"
/*CDC*/
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\define\cdc_def.h"
#include  "\src\atlanta\define\cdc_blk.h"
#include  "\src\atlanta\define\mem_pro.h"
/*SCN*/
/*MEM*/
/*PRN*/
/*MDM*/
/*FCM*/
#include  "\src\atlanta\define\fcm_def.h"
/*LST*/
#include  "\src\atlanta\define\lst_def.h"
#include  "\src\atlanta\define\lst_pro.h"
/*MDM*/
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#include  "\src\atlanta\define\cmn_pro.h"

#include  "\src\atlanta\define\uni_pro.h"

#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\define\mntsw_f.h"


/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\sys_data.h"
/*MON*/
/*DMA*/
#include  "\src\atlanta\ext_v\dma_data.h" /* for Debug. by H.Kubo 1997/11/28 */
#include  "\src\atlanta\sh7043\define\def_evtn.h" /* for Debug. by H.Kubo 1997/11/28 */
#include  "\src\atlanta\define\mon_pro.h" /* for Debug. by H.Kubo 1997/11/28 */
/*CDC*/
#include  "\src\atlanta\ext_v\cdc_data.h"
#include  "\src\atlanta\ext_v\cdc_tbl.h"
/*SCN*/
/*MEM*/
/*PRN*/
/*MDM*/
/*FCM*/
#include  "\src\atlanta\ext_v\fcm_data.h"
/*LST*/
#include  "\src\atlanta\ext_v\lst_data.h"

#if  (PRO_RELAYED_REPORT == ENABLE)	/*  H.Kubo 1998/01/19 */
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_mbxn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\apl_msg.h"
#endif /* (PRO_RELAYED_REPORT == ENABLE) */



static UDWORD dma_24bit_start_address = 0;

#if (PRO_COM_CODEC_TYPE != SOFTWARE) /* 通信コーデックがソフトでなければ */ /* added by H.Kubo 1997/11/07 */

#if (PRO_JBIG != ENABLE)	/*  by T.Soneoka 1997/12/19 */
static UBYTE dummy_line = 0;
#endif
/* static UDWORD dma_24bit_start_address = 0; 条件コンパイル外に移動 M.Kotani 1998/01/09*/



/*************************************************************************
	module		:[TTIの前につける白ラインの本数を返す。]
	function	:[
		送信原稿のモードと TTI の大きさから白ライン数を決定する
	]
	return		:[
		白ライン本数（ただし、実際の画データでは副走査拡大率倍された本数の白ラインが出力される）
	]
	common		:[
		SYS_DocBlock
		SYB_MaintenanceSwitch
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
		TTI 用にコーデックのセットアップが終わっていること
	]
	comment		:[
		ファイン/Ｓファイン時のＴＴＩ主走査圧縮時にポプラ同士で交信した場合、
		受信側でＴＴＩの頭が欠ける対策です。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/02/27]
	author		:[久保博]
*************************************************************************/
BYTE GetTopWhiteLineCountOfTTI(UBYTE codec_type)
{
	UWORD vconv;
	UBYTE tti_white_line_no;

	tti_white_line_no = 0;

	if (CHK_UNI_TTI_Size() && SYS_DocBlock.Dst.Mode != SYS_NORMAL) {
#if 0
@@		vconv = ReadCodecParameterRegister(codec_type, C0_VCONV_ADR);	/**副走査拡大率*/
@@		if (vconv == 0x0000 ) {
@@			if (!SYB_MaintenanceSwitch[MNT_SW_F5]) {
@@				tti_white_line_no = 16;
@@			}
@@			else {
@@				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
@@			}
@@		}
@@		else if (vconv == 0x0002){
@@			if (!SYB_MaintenanceSwitch[MNT_SW_F5]) {
@@				/* tti_white_line_no = 32; */
@@				tti_white_line_no = 16; /* 16 ラインがエンコード時に 2 倍に拡大される */
@@			}
@@			else {
@@				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
@@			}
@@		}
@@		else {
@@			tti_white_line_no = 16;
@@		}
#else
		if (!SYB_MaintenanceSwitch[MNT_SW_F5]) {
			tti_white_line_no = 16;
		}
		else {
			tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
		}
#endif
	}
	return tti_white_line_no;
}



/*************************************************************************
	module		:[TTIキャラクタの符号化を行う]
	function	:[
		1. V53DMAUを設定する
		2. ＴＴＩフォント展開関数をコール
		3. V53DMA許可
		4. 符号化を開始する
		5. V53DMA禁止
	]
	return		:[
		符号データ最終アドレス
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[
		ＥＣＭバッファ先頭アドレスからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UDWORD CDC_SetTTI(void)
{
	UBYTE tti_white_line_no;

	tti_white_line_no = GetTopWhiteLineCountOfTTI(COMMUNICATION_CODEC);

#if 0
@@	tti_white_line_no = 0;
@@
@@	/* ファイン/Ｓファイン時のＴＴＩ主走査圧縮時にポプラ同士で交信した場合、受信側でＴＴＩの頭が欠ける対策 By H.Kubo 1998/02/25 */
@@	if (CHK_UNI_TTI_Size() && SYS_DocBlock.Dst.Mode != SYS_NORMAL) {
@@		vconv = ReadCodecParameterRegister(COMMUNICATION_CODEC, C0_VCONV_ADR);	/**副走査拡大率*/
@@		if (vconv == 0x0000 ) {
@@			if (!SYB_MaintenanceSwitch[MNT_SW_F5]) {
@@				tti_white_line_no = 16;
@@			}
@@			else {
@@				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
@@			}
@@		}
@@		else if (vconv == 0x0002){
@@			if (!SYB_MaintenanceSwitch[MNT_SW_F5]) {
@@				/* tti_white_line_no = 32; */
@@				tti_white_line_no = 16; /* 16 ラインがエンコード時に 2 倍に拡大される */
@@			}
@@			else {
@@				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
@@			}
@@		}
@@	}
#endif


#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/19 */
	CDC_CTxSetupDMAU();
	/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	CDC_CTxSetupCodec(CDC_ENCODE_TTI); /* argument is added by H.Kubo 1997/12/19 */
	if (tti_white_line_no) { /* added by H.Kubo 1998/02/25 */
		CDC_SetDummyLine(tti_white_line_no);	/**ダミー白ラインをセット*/
		/* DMA のアドレスを設定し直す */
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	}
	LST_SetTTI_Image(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);	/**TTIのイメージをCharacterTxImage.Patternにセットする*/
	CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
	CDC_SetDummyLine(dummy_line);	/**ダミー白ラインをセット*/
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/

	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));

#else
	CDC_CTxSetupDMAU();
	CDC_CTxSetupCodec(CDC_ENCODE_TTI);  /* argument is added by H.Kubo 1997/12/19 */
	if (tti_white_line_no) {  /* added by H.Kubo 1998/02/25 */
		CDC_SetDummyLine(tti_white_line_no);	/**ダミー白ラインをセット*/
		/* DMA のアドレスを設定し直す */
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
	}
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	LST_SetTTI_Image(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);	/**TTIのイメージをCharacterTxImage.Patternにセットする*/
	StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
	CDC_SetDummyLine(dummy_line);	/**ダミー白ラインをセット*/
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));
#endif
}


/*************************************************************************
	module		:[カバーページの符号化を行う]
	function	:[
		1. V53DMAUを設定関数をコール
		2. カバーページフォント展開関数をコール
		3. V53DMA許可
		4. 符号化を開始する
		5. V53DMA禁止
	]
	return		:[
		符号データ最終アドレス
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[
		ＥＣＭバッファ先頭アドレスからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UDWORD CDC_SetCoverPage(void)
{
	UBYTE line;
	UWORD  cover_dmylinecnt;

/*941209 1line Insert for F43 Printer Rx by T.Soneoka*/
	cover_dmylinecnt = 0x12; /* 18*16=288line  CoverPage(74mm)+DummyLine(288line->74.80mm)=144.80mm */

#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
	CDC_CTxSetupDMAU();
	/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	CDC_CTxSetupCodec(CDC_ENCODE_COVERPAGE);  /* argument is added by H.Kubo 1997/12/19 */
	for (line = 1; line <= CVR_LINES; line++) {
		LST_SetCoverPage_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
#else
	CDC_CTxSetupDMAU();
	CDC_CTxSetupCodec(CDC_ENCODE_COVERPAGE);  /* argument is added by H.Kubo 1997/12/19 */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	for (line = 1; line <= CVR_LINES; line++) {
		LST_SetCoverPage_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
#endif /* (PRO_JBIG == ENABLE) */

/*941209 insert for F43 printer rx*/
	while (cover_dmylinecnt--) {
		CDC_SetDummyLine(16);	/**ダミー白16ラインをセット*/
	}
#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
	/* RTC/NEWLENコマンド発行 */
	if (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
	else {
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
#else
	SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**ページの終わりにRTCをセットする*/
#endif /* (PRO_JBIG == ENABLE) */
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));
}


/*************************************************************************
	module		:[受領証の符号化を行う]
	function	:[
		1. V53DMAUを設定する
		2. ＴＴＩフォント展開関数をコール
		3. 符号化を開始する
	]
	return		:[
		符号データ最終アドレス
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[
		ＥＣＭバッファ先頭アドレスからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UDWORD CDC_SetRCR(void)
{
	UBYTE line;

#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
	CDC_CTxSetupDMAU();
	/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	CDC_CTxSetupCodec(CDC_ENCODE_RCR);  /* argument is added by H.Kubo 1997/12/19 */
	for (line = 1; line <= RCR_LINES; line++) {
		LST_SetRCR_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
	/* RTC/NEWLENコマンド発行 */
	if (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
	else {
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
#else
	CDC_CTxSetupDMAU();
	CDC_CTxSetupCodec(CDC_ENCODE_RCR);  /* argument is added by H.Kubo 1997/12/19 */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	for (line = 1; line <= RCR_LINES; line++) {
		LST_SetRCR_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
	SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**ページの終わりにRTCをセットする*/
#endif
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));
}


/*************************************************************************
	module		:[キャラクタ送信用に通信コーデックを設定する]
	function	:[
		1.通信コーデックのパラメータを設定する
	]
	return		:[なし]
	common		:[
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
/* void CDC_CTxSetupCodec(void) */
void CDC_CTxSetupCodec(UBYTE image_kind)
{

	struct CodecEncodeParameterBlk_t enc_blk;


#if (PRO_COM_CODEC_TYPE == MN86064) /* デバッグ用。 H.Kubo 1997/12/08 */
	/* MTxCodeConvertPageTask と同じ設定を先にしておく。*/
#if (0) /* Deleted by H.Kubo 1998/02/18 同じ設定を下でやっています。*/
@@	enc_blk.CodecType = COMMUNICATION_CODEC;							/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
@@	enc_blk.CodeType  = SYS_DocBlock.Dst.Code;							/**符号化方式 (ex. SYS_MMR_CODE)*/
@@	enc_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
@@	enc_blk.C0_PWDR_Status  = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode);		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
@@	enc_blk.C0_OBXR_Status  = 0;					/**符号化オフセット*/
#endif
	enc_blk.C0_KPR_Status	  = GetK_Parameter(SYS_DocBlock.Dst.Mode);		/**符号化Kパラメータ*/
	enc_blk.C0_LCONT_Status = 0;					/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/

#if 0 /* メモリ節約のため、共通コードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	enc_blk.C0_MCLR_Status  = 0;					/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@	if (TxECM_Mode == ECM_ON) {
@@		enc_blk.C0_MCLR_Status  = 0;
@@	}
@@	else {
@@		if (SYS_DocBlock.MSE_Method == MSE1) {
@@			enc_blk.C0_MCLR_Status  = 0;
@@		}
@@		else {
@@			enc_blk.C0_MCLR_Status  = SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@		}
@@	}
#else
	enc_blk.C0_MCLR_Status =  CDC_GetCodecEncodeMCLR();
#endif

#if (0) /* Deleted by H.Kubo 1998/02/18 同じ設定を下でやっています。*/
@@	enc_blk.FRWORD_Status	= 0;		/**[システムメモリのため不要](イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
@@	enc_blk.INWORD_Status	= 0;		/**[１ライン半角８０文字]入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE))*/
@@	enc_blk.INLINE_Status	= 0;		/**入力ライン数(1回に符号化するライン数)*/
#endif
#endif /* (PRO_COM_CODEC_TYPE == MN86064) */ /* デバッグ用 */

	/**コーデックパラメータを設定する*/
	/** Kiri用追加パラメータ */
	enc_blk.CodecType = COMMUNICATION_CODEC;							/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
	enc_blk.CodeType  = SYS_DocBlock.Dst.Code;							/**符号化方式 (ex. SYS_MMR_CODE)*/
	/** 入出力パラメータ */
	enc_blk.FRWORD_Status	= 0;		/**[システムメモリのため不要](イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	enc_blk.INWORD_Status	= 40;		/**[１ライン半角８０文字]入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE))*/
	enc_blk.INLINE_Status	= 16;		/**入力ライン数(1回に符号化するライン数)*/
	enc_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 符号化パラメータ Ch.0 */
	enc_blk.C0_STRA_Status	= 0;		/**[システムメモリのため不要]符号化ライン先頭アドレス(通信イメージバッファの符号化開始アドレス)*/
	enc_blk.C0_MTOPA_Status = 0;		/**[システムメモリのため不要]符号化イメージバッファ先頭アドレス*/
	enc_blk.C0_MENDA_Status = 0;		/**[システムメモリのため不要]符号化イメージバッファ最終アドレス*/
	enc_blk.C0_OBXR_Status	= 0;		/**14,24,36符号化オフセット*/

#if 0 /* 上で同じことをしています。 Deleted by H.Kubo 1998/07/08 */
@@	enc_blk.C0_LCONT_Status = 0;		/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
@@	if (TxECM_Mode == ECM_ON) {	/* ＥＣＭ送信の時は最小伝送符号バイト数は０にセット */
@@		enc_blk.C0_MCLR_Status	= 0;
@@	}
@@	else {
@@		if (SYS_DocBlock.MSE_Method == MSE1) {
@@			enc_blk.C0_MCLR_Status	= 0;
@@		}
@@		else {
@@			enc_blk.C0_MCLR_Status	= SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@		}
@@	}
#endif

	enc_blk.C0_LMASK_Status = 0;		/**符号化左側白マスク*/
	enc_blk.C0_RMASK_Status = 0;		/**符号化右側白マスク*/

#if (0) /* Deleted by H.Kubo 1997/12/16 GetCodecSize() を使うのでいらない。*/
@@	switch (SYS_DocBlock.Dst.Size) {
@@	case SYS_DOCUMENT_A4_SIZE:
@@		enc_blk.C0_PWDR_Status	= 108;		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_B4_SIZE:
@@		enc_blk.C0_PWDR_Status	= 128;		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_B4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_A3_SIZE:
@@		enc_blk.C0_PWDR_Status	= 152;		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A3;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	default:
@@		break;
@@	}
#else 
	/* CDC_StxCodeConvertPageTask, CDC_MTxCodeConvertPageTask では、
	** GetCodecSize()で C0_PWDR_Status の値を求めているので、それに合わせる。
	** 1997/12/02 H.Kubo
	*/
	enc_blk.C0_PWDR_Status = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode); /* Added by H.Kubo 1997/12/02 */
#if 0 /* メモリ節約のため、共通コードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	switch (SYS_DocBlock.Dst.Size) {
@@	case SYS_DOCUMENT_A4_SIZE:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_B4_SIZE:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_B4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_A3_SIZE:
@@	default:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A3;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	}
@@	if (SYS_DocBlock.Dst.Mode == SYS_HFINE) { /* HFINE のときは主走査方向 2倍*/
@@		enc_blk.I_OBXR_Status *= 2;
@@	} 
@@	else if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) ||
@@			 (SYS_DocBlock.Dst.Mode == SYS_E_HFINE) ) { /* EFINE のときは主走査方向 2/3倍*/
@@		 enc_blk.I_OBXR_Status *=3;
@@		 enc_blk.I_OBXR_Status /=2;
@@	}
#else
	enc_blk.I_OBXR_Status = CDC_GetCtxCodecEncode_I_OBXR();
#endif
#endif /* (0) */

#if 0 /* メモリ節約のため、共通のコードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	switch (SYS_DocBlock.Dst.Mode) {
@@	case SYS_NORMAL:
@@		if ( image_kind == CDC_ENCODE_TTI) { /* Changed by H.Kubo 1997/12/19 */
@@			enc_blk.C0_HCONV_Status = 0x2002;	/**符号化主走査方向変換率 ２倍*/
@@			enc_blk.C0_VCONV_Status = 0;		/**符号化副走査方向変換率 等倍*/
@@		}
@@		else {
@@#if (PRO_COM_CODEC_TYPE == MN86063)
@@			enc_blk.C0_HCONV_Status = 0xA002;	/**符号化主走査方向変換率 ２倍*/
@@#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
@@			enc_blk.C0_HCONV_Status = 0xB002;	/**符号化主走査方向変換率 ２倍*/
@@#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
@@#else /* (PRO_COM_CODEC_TYPE) */
@@#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
@@#endif/* (PRO_COM_CODEC_TYPE) */
@@			enc_blk.C0_VCONV_Status = 0x0000;		/**符号化副走査方向変換率 等倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 2;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_FINE:
@@	case SYS_GRAY16:
@@	case SYS_GRAY16_SEP:
@@	case SYS_GRAY32:
@@	case SYS_GRAY32_SEP:
@@	case SYS_GRAY64:
@@	case SYS_GRAY64_SEP:
@@#if (PRO_COM_CODEC_TYPE == MN86063)
@@		enc_blk.C0_HCONV_Status = 0xA002;	/**符号化主走査方向変換率 ２倍*/
@@#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
@@		enc_blk.C0_HCONV_Status = 0xB002;	/**符号化主走査方向変換率 ２倍*/ /* 符号化副走査方向固定倍率 */
@@#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
@@#else /* (PRO_COM_CODEC_TYPE) */
@@#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
@@#endif/* (PRO_COM_CODEC_TYPE) */
@@		if ( image_kind == CDC_ENCODE_TTI) { /* Changed by H.Kubo 1997/12/19 */
@@			if ( CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@				enc_blk.C0_VCONV_Status = 0x0000;	/**符号化副走査方向変換率等倍*/ /* Changed by H.Kubo 1997/12/19 */
@@			}
@@			else {
@@				enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@			}
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 4;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_SFINE:
@@#if (PRO_COM_CODEC_TYPE == MN86063)
@@		enc_blk.C0_HCONV_Status = (0xA000 | 0x0002); /**符号化主走査方向変換率 ２倍*/
@@#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
@@		enc_blk.C0_HCONV_Status = (0xB000 | 0x0002); /**符号化主走査方向変換率 ２倍＆符号化副走査方向固定倍率 */
@@#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
@@#else /* (PRO_COM_CODEC_TYPE) */
@@#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
@@#endif/* (PRO_COM_CODEC_TYPE) */
@@		if (image_kind == CDC_ENCODE_TTI) {
@@			if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@				enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@			}
@@			else {
@@				enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
@@			}
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 4倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_HFINE:
@@#if (PRO_COM_CODEC_TYPE == MN86063)
@@		enc_blk.C0_HCONV_Status = 0xA004;	/**符号化主走査方向変換率 ４倍*/
@@#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
@@		enc_blk.C0_HCONV_Status = 0xB004;	/**符号化主走査方向変換率 ４倍＆符号化副走査方向固定倍率 */
@@#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
@@#else /* (PRO_COM_CODEC_TYPE) */
@@#error	"The Communication CODEC is other than MN86063 or MN86064. Fix me!"
@@#endif/* (PRO_COM_CODEC_TYPE) */
@@		if ( image_kind == CDC_ENCODE_TTI) {
@@			if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@				enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@			}
@@			else {
@@				enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
@@			}
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 4倍*/
@@		}
@@#if (0) /* Deleted by H.Kubo 1997/12/18 */
@@@@		enc_blk.C0_PWDR_Status *= 2;		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
@@@@		enc_blk.I_OBXR_Status  *= 2;		/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@#endif /* (0) */
@@		enc_blk.C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_EFINE:
@@	case	SYS_E_HFINE:
@@#if (PRO_COM_CODEC_TYPE == MN86063)
@@		enc_blk.C0_HCONV_Status = 0xA003;	/**符号化主走査方向変換率 ３倍	for ANZU By T.YAMAGUCHI 96/05/14 */
@@#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/12/19 */
@@		enc_blk.C0_HCONV_Status = 0xB003;	/**符号化主走査方向変換率 ３倍	for ANZU */
@@#else /* (PRO_COM_CODEC_TYPE) */
@@#error	"The Communication CODEC is other than MN86063 or MN86064. Fix me!"
@@#endif/* (PRO_COM_CODEC_TYPE) */
@@		if ( (image_kind == CDC_ENCODE_TTI) && CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@			enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
@@		break;
@@	default:	/*ここはエラー*/
@@		enc_blk.C0_HCONV_Status = 0;	/**符号化主走査方向変換率*/
@@		enc_blk.C0_VCONV_Status = 0;	/**符号化副走査方向変換率*/
@@		enc_blk.C0_KPR_Status	= 1;	/**符号化Kパラメータ*/
@@		break;
@@	}
#else
	CDC_CtxCodecEncodeStructMagnify(&enc_blk, image_kind);
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	switch (CommunicateType) {
	case	TX_G3_MEM:
	case	TX_ECM_MEM:
	case	TX_G3_CVR: /* added by H.Kubo 1998/01/19 */
	case	TX_G3_RCR: /* added by H.Kubo 1998/01/19 */
	case	TX_ECM_CVR: /* added by H.Kubo 1998/01/19 */
	case	TX_ECM_RCR: /* added by H.Kubo 1998/01/19 */
#if (PRO_RELAYED_REPORT == ENABLE) /* H.Kubo 1998/01/19 */
	case	TX_G3_RELAYED_TX_REPORT:
	case	TX_ECM_RELAYED_TX_REPORT:
#endif
		dummy_line = 1;
		break;
	case	TX_G3_SCAN:
	case	TX_ECM_SCAN:
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
/*
** ＨＩＮＯＫＩのスキャナ送信は、通信コーデックにて、ＴＴＩもスキャンデータも符号化するので
** コーデックを切り替える必要がない為、ダミーデータ１ラインでＯＫである
** 他の機種は、ＴＴＩは通信コーデック、スキャンデータはスキャナコーデックで符号化するので
** ＴＴＩとスキャンデータの間、全白ラインを１ラインはさまなければならない。
** １ライン全白符号データを生成するのに、最悪ＭＭＲでは１ライン、１ビットになるため
** １６ライン転送しなければならない
** 1999/01/29 by T.Soneoka
*/
		switch (SYS_DocBlock.Dst.Code) {
		case SYS_MH_CODE:
		case SYS_MMR_CODE:
		case SYS_MG3_CODE:
		case SYS_JBIG_CODE:
		case SYS_MR_CODE:
		default:
			dummy_line = 1;
			break;
		}
#else
		switch (SYS_DocBlock.Dst.Code) {
		case SYS_MH_CODE:
		case SYS_MMR_CODE:
		case SYS_MG3_CODE:
		case SYS_JBIG_CODE:
			enc_blk.C0_KPR_Status	= 0;		/**符号化Kパラメータ*/
			dummy_line = 16;	/*940906 1->16*/
			break;
		case SYS_MR_CODE:
		default:
			dummy_line = enc_blk.C0_KPR_Status + ( (UBYTE)8 - (UBYTE)1) ;
			break;
		}
#endif
		break;
	default:
		break;
	}

	if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
#if 0 /* メモリ節約のため、共通のコードを関数にまとめます。By H.Kubo 1998/07/08 */
@@#if (0)	/* 下記メモリＳｗにて設定対応できるように変更 */
@@//		enc_blk.C_QMCR_Status = (VLENGTH_BIT | TPBON_BIT);	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@#endif
@@		enc_blk.C_QMCR_Status = VLENGTH_BIT;
@@		if (CHK_UNI_JBIG_2lineTemplate()) {
@@			enc_blk.C_QMCR_Status |= LRLTWO_BIT;
@@		}
@@		if (CHK_UNI_JBIG_TPB_Mode()) {
@@			enc_blk.C_QMCR_Status |= TPBON_BIT;
@@		}
@@		if (CHK_UNI_JBIG_SDRST()) {
@@			enc_blk.C_QMCR_Status |= SDRST_BIT;
@@		}
@@		enc_blk.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk.C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk.C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk.C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
@@		enc_blk.D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@		enc_blk.D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk.D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk.D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk.D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#else
		CDC_InitCodecEncodeStructJbig(&enc_blk);
#endif
	}
#else
	dummy_line = enc_blk.C0_KPR_Status + ( (UBYTE)8 - (UBYTE)1) ;
	switch (SYS_DocBlock.Dst.Code) {
	case SYS_MH_CODE:
	case SYS_MMR_CODE:
	case SYS_MG3_CODE:
		enc_blk.C0_KPR_Status	= 0;		/**符号化Kパラメータ*/
		dummy_line = 16;	/*940906 1->16*/
		break;
	default:
		break;
	}
#endif


	/**上記のパラメータでコーデックをセットアップする*/
	CodecEncodeSetup(&enc_blk);

#if (PRO_CPU != SH7043) /* #if condition is added by H.Kubo 1997/11/07 */
	CodecImageByteSwapEnable(enc_blk.CodecType);	/**DTCR設定(バイトSwap有効)*/
#else /* (PRO_CPU != SH7043) */
	/* MSB is first. 
	** Nothing to do for SH series CPU. The default setting is OK.
	** H.Kubo 1997/11/06
	*/
	CodecImageByteSwapDisable(enc_blk.CodecType);	/**DTCR設定(バイトSwap無効)*/
	CodecCodeByteSwapEnable(enc_blk.CodecType);	/**DTCR設定(バイトSwap有効)*/
#endif /* (PRO_CPU != SH7043) */
}


/*************************************************************************
	module		:[キャラクタ送信用にＶ５３ＤＭＡＵを設定する]
	function	:[
		1.マスターのチャンネル２を設定する
		2.スレーブのチャンネル０を設定する
	]
	return		:[なし]
	common		:[
		FontImageBuffer
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CDC_CTxSetupDMAU(void)
{
	struct DMA_Data_t dma;
	UBYTE *offset;

#if (PRO_CPU == SH7043)
	dma_24bit_start_address = (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0];
	/**DMAUをセットアップする*/
	dma.Channel = DMA_COMCDC_DRAM_CH;							/*DMAチャンネル*/
	dma.SrcAddress = ECM_BUFFER_AREA_START_ADDRESS;				/*DMA開始アドレス(絶対アドレス24ビットで指定)*//*0x30000*/
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_IO_TO_MEMORY;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);

	dma.Channel = DMA_DRAM_COMCDC_CH;							/*DMAチャンネル*/
	dma.SrcAddress = dma_24bit_start_address;
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);
#else
	offset = &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0];
	dma_24bit_start_address = (unsigned long)(((unsigned long)offset & (unsigned long)(0xffff0000)) >> 12)
							+ (unsigned long)(((unsigned long)offset & (unsigned long)(0x0000ffff)));	/*DMA開始アドレス(絶対アドレス24ビットで指定)*/
	/**V53DMAUをセットアップする*/
	dma.Item = MASTER_DMAU;										/*使用するDMAU(MASTER_DMAU, SLAVE1_DMAU or SLAVE2_DMAU)*/
	dma.Channel = 2;											/*DMAチャンネル*/
	dma.SrcAddress = ECM_BUFFER_AREA_START_ADDRESS;				/*DMA開始アドレス(絶対アドレス24ビットで指定)*//*0x30000*/
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_IO_TO_MEMORY;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);

	dma.Item = SLAVE1_DMAU;										/*使用するDMAU(MASTER_DMAU, SLAVE1_DMAU or SLAVE2_DMAU)*/
	dma.Channel = 0;											/*DMAチャンネル*/
	dma.SrcAddress = dma_24bit_start_address;
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);
#endif

}


/*************************************************************************
	module		:[Ｋパラメータの差分だけ全白ラインを符号化する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		ＥＣＭバッファ続きからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
#if (1) /* for Debug by H.Kubo 1997/11/28 */
static	UDWORD	DREQC0_wait_count = 0;
#endif
void CDC_SetDummyLine(UBYTE line)
{
#if (PRO_CPU == SH7043)
	/* Modifed for SH7943 by H.Kubo 1997/11/07 	*/
	UBYTE *temp;
	UWORD codec_parameter_inline;

	temp = CMN_MemorySet(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
							 (UWORD)(80*line),		/* セット文字数 */
							 (UBYTE)0);				/* セット文字 */

	DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
	DMA_SetDMA_Counter(DMA_DRAM_COMCDC_CH, (UWORD)(80 / 2 * line)); /* H.Kubo 1997/11/28 */
	/* INLINE の設定を覚えておく。 by H.Kubo 1998/01/23 */
	codec_parameter_inline = ReadCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR);	/**入力ライン数(1回に符号化するライン数)*/
	SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, line);	/**入力ライン数(1回に符号化するライン数)*/
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH); /* H.Kubo 1997/11/28 */
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/19 */
	CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
#else
	StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
#endif
	/* INLINE の設定を元に戻す。 by H.Kubo 1998/01/23 */
	SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, codec_parameter_inline);	/**入力ライン数(1回に符号化するライン数)*/
	return;


#else
	unsigned char far *temp;


	switch (CommunicateType) {
	case	TX_G3_SCAN:
	case	TX_ECM_SCAN:
		temp = CMN_MemorySet((unsigned char far *)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
							 (UWORD)(80*line),		/* セット文字数 */
							 (unsigned char)0);				/* セット文字 */
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
		SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, line);	/**入力ライン数(1回に符号化するライン数)*/
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
		break;
	case	TX_G3_MEM:	/**何もしない*/
	case	TX_ECM_MEM:	/**何もしない*/
	case	TX_G3_RCR: /* added by H.Kubo 1998/01/19 */
	case	TX_ECM_RCR: /* added by H.Kubo 1998/01/19 */
		line = 1;	/*test*/
		temp = CMN_MemorySet((unsigned char far *)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
							 (UWORD)(80*line),		/* セット文字数 */
							 (unsigned char)0);				/* セット文字 */
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
		SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, line);	/**入力ライン数(1回に符号化するライン数)*/
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
		break;
/*941209 9line Insert for F43 Printer Rx by T.Soneoka*/
	case	TX_G3_CVR:
	case	TX_ECM_CVR:
		temp = CMN_MemorySet((unsigned char far *)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
							 (UWORD)(80*line),		/* セット文字数 */
							 (unsigned char)0);				/* セット文字 */
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
		SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, line);	/**入力ライン数(1回に符号化するライン数)*/
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
		break;
	default:			/**何もしない*/
		break;
	}
#endif
}

#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
/*************************************************************************
	module		:[JBIG 符号化開始]
	function	:[
		1. JBIG の符号化を開始する。
		2. STIR の JBIG コマンド終了割り込みに対する処理を行う。
		3. STIR のコマンド終了割り込みが来たら、終了する。
	]
	return		:[なし]
	common		:[
		CodecSTIR_Status
		SYS_DocBlock.Dst.Code
	]
	condition	:[
		CDC_CTx のモジュールの中で使うこと。
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/12/27]
	author		:[久保博]
*************************************************************************/
void CDC_CTxStartEncodeAndJBIGIRQ(UBYTE codec_type,	/*使用するコーデック*/
								 UBYTE code_type)	/*符号化方式*/
{
	UWORD allowed_restart = 0xffff; /* StartEncode 起動回数カウントダウン */
	while (allowed_restart--) {
		StartEncode(codec_type, code_type);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
		/* JBIGコマンド割り込み */
		if (CodecSTIR_Status[codec_type] & JBIGIRQ_BIT) {
			SetCodecParameterRegister(codec_type, C_QMIR_ADR, 0);	/* QMIRクリア */
			CodecParameterRegister[codec_type].C_QMIR_Status = ReadCodecParameterRegister(codec_type, C_QMIR_ADR);
			Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
		}
		/* コマンド終了時 */
		/* ここまでで CODEC 終了割り込みがないこと。チャンネル 1 が動作するときは注意。 */
		if (CodecSTIR_Status[codec_type] & CMDE0_BIT) {
			return; /* 正常終了*/
		}
	}
	/* StartEncode起動回数多すぎ。ここに来たら何かおかしい。*/
	SaveReturnAddressAndJumpBegin();
}
#endif /* (PRO_JBIG == ENABLE) */

#endif /* (PRO_COM_CODEC_TYPE != SOFTWARE) 通信コーデックがソフトでなければ */ /* ファイルの頭の #if に対応。 */


#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/1/7 */
	#if (PRO_SCN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
/*************************************************************************
	module		:[TTIイメージをスキャナコーデック経由で53Lineのイメージバッファに転送する]
	function	:[
		1. V53DMAUを設定する
		2. ＴＴＩフォント展開関数をコール
		3. V53DMA許可
		4. 符号化を開始する
		5. V53DMA禁止
	]
	return		:[
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[曽根岡拓]
*************************************************************************/
UDWORD CDC_DataTransferAndSetTTI(void)
{
	struct CodecDataTransferParameterBlk_t data_trans_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	struct CodecEncodeParameterBlk_t enc_blk;

	struct DMA_Data_t dma;
	UBYTE	debugsw;	/* 1998/03/12 by T.Soneoka スキャナ送信ダミーライン処理 */
	UBYTE *temp;	/* 1998/03/12 by T.Soneoka スキャナ送信ダミーライン処理 */
	
	/* ファイン/Ｓファイン時のＴＴＩ主走査圧縮時にポプラ同士で交信した場合、受信側でＴＴＩの頭が欠ける対策 By H.Kubo 1998/02/27 */
	UBYTE tti_white_line_no;

	debugsw = 1;	/* ダミーデータ送出初期値ＯＮにします by T.Soneoka 1998/03/12 */
	/*
	** DRAMにあるTTIイメージをスキャナコーデックイメージメモリへ転送する処理
	*/
	/* V53DMAセットアップ */
	dma_24bit_start_address = (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0];
	dma.Channel = DMA_SCNCDC_DRAM_CH;							/*DMAチャンネル*/
	dma.SrcAddress = dma_24bit_start_address;
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);
	DMA_RequestEnable(dma.Channel);	/*DMAUの種類*/

	/* コーデックセットアップ */
	SetScannerDramToCodecDACK();	/* スキャナコーデックDACK設定 */
	SetClear((UBYTE *)&data_trans_blk, sizeof(struct CodecDataTransferParameterBlk_t), 0x00);
	data_trans_blk.CodecType = SCANNER_CODEC;
	data_trans_blk.FRWORD_Status = 304;
	data_trans_blk.INWORD_Status = 40;
	data_trans_blk.INLINE_Status = 16;
	data_trans_blk.OTWORD_Status = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode);
	data_trans_blk.I_OBXR_Status = 0;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
	data_trans_blk.O_OBXR_Status = 0;	/*出力ｵﾌｾｯﾄ*/
	/* 符号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	data_trans_blk.C0_MTOPA_Status = 0;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	data_trans_blk.C0_MENDA_Status = 0;	/*符号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* 復号化ﾊﾟﾗﾒｰﾀ Ch.0 */
	data_trans_blk.D0_MTOPA_Status = 0;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ*/
	data_trans_blk.D0_MENDA_Status = 0xFE20;	/*復号化ｲﾒｰｼﾞﾊﾞｯﾌｧ最終ｱﾄﾞﾚｽ*/
	/* ﾃﾞｰﾀ転送ﾊﾟﾗﾒｰﾀ */
	data_trans_blk.B_STRA0_Status = 0;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ0*/
	data_trans_blk.B_STRA1_Status = 0;	/*ﾃﾞｰﾀ転送先頭ｱﾄﾞﾚｽ1*/
	data_trans_blk.B_HCONV_Status = 0;	/*ﾃﾞｰﾀ転送主走査方向変換率*/
	data_trans_blk.B_VCONV_Status = 0;	/*ﾃﾞｰﾀ転送副走査方向変換率*/
	data_trans_blk.B_HCONV_Status = 0;	/**符号化主走査方向変換率*/
	data_trans_blk.B_VCONV_Status = 0;	/**符号化副走査方向変換率*/
	data_trans_blk.B_LMASK_Status = 0;	/*ﾃﾞｰﾀ転送左側白ﾏｽｸ*/
	data_trans_blk.B_RMASK_Status = 0;	/*ﾃﾞｰﾀ転送右側白ﾏｽｸ*/
	data_trans_blk.Vmn_Status = 0;		/*間引き/OR指定*/
	/**上記のパラメータでコーデックをセットアップする*/
	CodecDataTransferSetup(&data_trans_blk);

#if (1) /* added by H.Kubo 1998/02/27 */
	/* ファイン/Ｓファイン時のＴＴＩ主走査圧縮時にポプラ同士で交信した場合、受信側でＴＴＩの頭が欠ける対策 By H.Kubo 1998/02/27 */
	tti_white_line_no = GetTopWhiteLineCountOfTTI(SCANNER_CODEC);
	if (tti_white_line_no) {  /* added by H.Kubo 1998/02/27 */
		/**ダミー白ラインをセット*/
		temp = CMN_MemorySet(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
							 (UWORD)(2 * data_trans_blk.INWORD_Status * tti_white_line_no),		/* セット文字数 */
							 (UBYTE)0);				/* セット文字 */
		/* INLINE の設定を白ライン用にする。*/
		SetCodecParameterRegister(data_trans_blk.CodecType, INLINE_ADR, tti_white_line_no);	/**入力ライン数(1回に符号化するライン数)*/
		DMA_RequestEnable(dma.Channel);
		EnterCodecCommand(data_trans_blk.CodecType, CODEC_CMD_DATA_TRANSFER);	/* データ転送コマンド発行 */
		DMA_RequestMask(dma.Channel);	/*DMAUの種類*/
		DMA_SetDMA_Address(dma.Channel, dma.Direction, (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		DMA_RequestEnable(dma.Channel);
		/* INLINE の設定を元に戻す。 by H.Kubo 1998/01/23 */
		SetCodecParameterRegister(data_trans_blk.CodecType, INLINE_ADR, data_trans_blk.INLINE_Status);	/**入力ライン数(1回に符号化するライン数)*/
		/* DMA のアドレスを設定し直す */
	}
#endif

	LST_SetTTI_Image(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);	/**TTIのイメージをCharacterTxImage.Patternにセットする*/

	EnterCodecCommand(data_trans_blk.CodecType, CODEC_CMD_DATA_TRANSFER);	/* データ転送コマンド発行 */
	DMA_RequestMask(dma.Channel);	/*DMAUの種類*/

	/***********************************************************
	** 1998/03/12 by T.Soneoka スキャナ送信ダミーライン処理
	*/
	if (debugsw) {
		dummy_line = 1;
		temp = CMN_MemorySet(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0],	/* セット先アドレス */
								 (UWORD)(80*dummy_line),		/* セット文字数 */
								 (UBYTE)0);				/* セット文字 */
		/* INLINE の設定を白ライン用にする。*/
		SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, dummy_line);	/**入力ライン数(1回に符号化するライン数)*/
		DMA_SetDMA_Address(dma.Channel, dma.Direction, (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		DMA_SetDMA_Counter(dma.Channel, (UWORD)(80/2*dummy_line));
		DMA_RequestEnable(dma.Channel);
		EnterCodecCommand(data_trans_blk.CodecType, CODEC_CMD_DATA_TRANSFER);	/* データ転送コマンド発行 */
		DMA_RequestMask(dma.Channel);	/*DMAUの種類*/
	}
	/***********************************************************/


	/*
	** スキャナコーデックイメージメモリに転送されたTTIをECMバッファへ符号化する処理
	*/
	/* V53DMAセットアップ */
	dma.Channel = DMA_SCNCDC_DRAM_CH;							/*DMAチャンネル*/
	dma.SrcAddress = ECM_BUFFER_AREA_START_ADDRESS;				/*DMA開始アドレス(絶対アドレス24ビットで指定)*//*0x30000*/
	dma.Counter = 0xFFFF;										/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_IO_TO_MEMORY;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);
	DMA_RequestEnable(DMA_SCNCDC_DRAM_CH);	/*DMAUの種類*/

	/**コーデックパラメータを設定する*/
	SetScannerCodecToDramDACK();	/* スキャナコーデックDACK設定 */
	SetClear((UBYTE *)&enc_blk, sizeof(struct CodecEncodeParameterBlk_t), 0x00);

	enc_blk.CodeType  = SYS_DocBlock.Dst.Code;					/**符号化方式 (ex. SYS_MMR_CODE)*/
	/** 入出力パラメータ */
	enc_blk.FRWORD_Status = 304;		/**[システムメモリのため不要](イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	if (debugsw) {
		enc_blk.INLINE_Status = 16+dummy_line;		/**入力ライン数(1回に符号化するライン数)*/
	}
	else {
		enc_blk.INLINE_Status = 16;		/**入力ライン数(1回に符号化するライン数)*/
	}
	if (tti_white_line_no) {  /* added by H.Kubo 1998/03/16 */
		enc_blk.INLINE_Status += tti_white_line_no; /* 先頭のダミー白ライン数を加算 */
	}
	enc_blk.C0_MTOPA_Status = 0;		/**[システムメモリのため不要]符号化イメージバッファ先頭アドレス*/
	enc_blk.C0_MENDA_Status = 0xFE20;		/**[システムメモリのため不要]符号化イメージバッファ最終アドレス*/

#if 0 /* メモリ節約のため、共通コードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	switch (SYS_DocBlock.Dst.Size) {
@@	case SYS_DOCUMENT_A4_SIZE:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_B4_SIZE:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_B4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	case SYS_DOCUMENT_A3_SIZE:
@@	default:
@@		enc_blk.I_OBXR_Status	= LST_LEFT_WHITE_A3;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
@@		break;
@@	}
@@	if (SYS_DocBlock.Dst.Mode == SYS_HFINE) { /* HFINE のときは主走査方向 2倍*/
@@		enc_blk.I_OBXR_Status *= 2;
@@	} 
@@	else if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) ||
@@			 (SYS_DocBlock.Dst.Mode == SYS_E_HFINE) ) { /* EFINE のときは主走査方向 2/3倍*/
@@		 enc_blk.I_OBXR_Status *=3;
@@		 enc_blk.I_OBXR_Status /=2;
@@	}
#else
	enc_blk.I_OBXR_Status = CDC_GetCtxCodecEncode_I_OBXR();
#endif

	enc_blk.C0_LCONT_Status = 0;		/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
	enc_blk.C0_STRA_Status	= 0;		/**[システムメモリのため不要]符号化ライン先頭アドレス(通信イメージバッファの符号化開始アドレス)*/
	enc_blk.C0_OBXR_Status	= 0;		/**14,24,36符号化オフセット*/
#if 0 /* メモリ節約のため、共通コードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	if (TxECM_Mode == ECM_ON) {	/* ＥＣＭ送信の時は最小伝送符号バイト数は０にセット */
@@		enc_blk.C0_MCLR_Status	= 0;
@@	}
@@	else {
@@		if (SYS_DocBlock.MSE_Method == MSE1) {
@@			enc_blk.C0_MCLR_Status	= 0;
@@		}
@@		else {
@@			enc_blk.C0_MCLR_Status	= SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@		}
@@	}
#else
	enc_blk.C0_MCLR_Status =  CDC_GetCodecEncodeMCLR();
#endif
	enc_blk.CodecType = dma_blk.CodecType = SCANNER_CODEC;							/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/

#if 0 /* メモリ節約のため、共通のコードを関数にまとめました。Changed by H.Kubo 1998/07/08 */
@@	switch (SYS_DocBlock.Dst.Mode) {
@@	case SYS_NORMAL:
@@		enc_blk.C0_HCONV_Status = 0x2002;	/**符号化主走査方向変換率 ２倍*/
@@		enc_blk.C0_VCONV_Status = 0;		/**符号化副走査方向変換率 等倍*/
@@		enc_blk.C0_KPR_Status	= 2;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_FINE:
@@	case SYS_GRAY16:
@@	case SYS_GRAY16_SEP:
@@	case SYS_GRAY32:
@@	case SYS_GRAY32_SEP:
@@	case SYS_GRAY64:
@@	case SYS_GRAY64_SEP:
@@		enc_blk.C0_HCONV_Status = 0xB002;	/**符号化主走査方向変換率 ２倍*/ /* 符号化副走査方向固定倍率 */
@@		if ( CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@			enc_blk.C0_VCONV_Status = 0x0000;	/**符号化副走査方向変換率等倍*/ /* Changed by H.Kubo 1997/12/19 */
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 4;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_SFINE:
@@		enc_blk.C0_HCONV_Status = (0xB000 | 0x0002); /**符号化主走査方向変換率 ２倍＆符号化副走査方向固定倍率 */
@@		if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@			enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@		}
@@		else {
@@			enc_blk.C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
@@		break;
@@	case SYS_HFINE:
@@		enc_blk.C0_HCONV_Status = 0xB004;	/**符号化主走査方向変換率 ４倍＆符号化副走査方向固定倍率 */
@@		if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
@@			enc_blk.C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
@@		}
@@		else {
@@			data_trans_blk.B_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
@@		}
@@		enc_blk.C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
@@		break;
@@	default:	/*ここはエラー*/
@@		enc_blk.C0_HCONV_Status = 0;	/**符号化主走査方向変換率*/
@@		enc_blk.C0_VCONV_Status = 0;	/**符号化副走査方向変換率*/
@@		enc_blk.C0_KPR_Status	= 1;	/**符号化Kパラメータ*/
@@		break;
@@	}
#else
	CDC_CtxCodecEncodeStructMagnify(&enc_blk, CDC_ENCODE_TTI);
#endif
	switch (SYS_DocBlock.Dst.Code) {
	case SYS_MH_CODE:
	case SYS_MMR_CODE:
	case SYS_MG3_CODE:
		enc_blk.C0_KPR_Status	= 0;		/**符号化Kパラメータ*/
		break;
	default:
		break;
	}
	enc_blk.INWORD_Status = 40;		/**[１ライン半角８０文字]入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE))*/
	enc_blk.C0_PWDR_Status = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode); /* Added by H.Kubo 1997/12/02 */
	enc_blk.C0_LMASK_Status = 0;		/**符号化左側白マスク*/
	enc_blk.C0_RMASK_Status = 0;		/**符号化右側白マスク*/
	enc_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 符号化パラメータ Ch.0 */

	if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
#if 0 /* メモリ節約のため、共通のコードを関数にまとめます。By H.Kubo 1998/07/08 */
@@#if (0)	/* 下記メモリＳｗにて設定対応できるように変更 1998/03/27 by T.Soneoka */
@@//		enc_blk.C_QMCR_Status = (VLENGTH_BIT | TPBON_BIT);	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@#endif
@@		enc_blk.C_QMCR_Status = VLENGTH_BIT;
@@		if (CHK_UNI_JBIG_2lineTemplate()) {
@@			enc_blk.C_QMCR_Status |= LRLTWO_BIT;
@@		}
@@		if (CHK_UNI_JBIG_TPB_Mode()) {
@@			enc_blk.C_QMCR_Status |= TPBON_BIT;
@@		}
@@		if (CHK_UNI_JBIG_SDRST()) {
@@			enc_blk.C_QMCR_Status |= SDRST_BIT;
@@		}
@@		enc_blk.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk.C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk.C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk.C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
@@		enc_blk.D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@		enc_blk.D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk.D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk.D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk.D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#else
		CDC_InitCodecEncodeStructJbig(&enc_blk);
#endif
	}

	CodecEncodeSetup(&enc_blk);
	CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/

#if (PRO_CPU != SH7043) /* #if condition is added by H.Kubo 1997/11/07 */
	CodecImageByteSwapEnable(enc_blk.CodecType);	/**DTCR設定(バイトSwap有効)*/
#else /* (PRO_CPU != SH7043) */
	/* MSB is first. 
	** Nothing to do for SH series CPU. The default setting is OK.
	** H.Kubo 1997/11/06
	*/
	CodecImageByteSwapDisable(enc_blk.CodecType);	/**DTCR設定(バイトSwap無効)*/
	CodecCodeByteSwapEnable(enc_blk.CodecType);	/**DTCR設定(バイトSwap有効)*/
#endif /* (PRO_CPU != SH7043) */

	CDC_CTxStartEncodeAndJBIGIRQ(enc_blk.CodecType, SYS_DocBlock.Dst.Code);
	DMA_RequestMask(DMA_SCNCDC_DRAM_CH);	/*DMAUの種類*/

	return(DMA_CheckDMA_Address(DMA_SCNCDC_DRAM_CH, DMA_IO_TO_MEMORY));
}
#endif	/* 1998/06/11 H.Yoshikawa */
#endif

#if (PRO_COM_CODEC_TYPE != SOFTWARE) /* 通信コーデックがソフトでなければ */ /* added by H.Kubo 1997/11/07 */
#if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/17 */
/*************************************************************************
	module		:[中継配信不達通知一ページ分の符号化を行う]
	function	:[
		1. V53DMAUを設定する
		2. ＴＴＩフォント展開関数をコール
		3. 符号化を開始する
	]
	return		:[
		符号データ最終アドレス
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅、原稿長が確定している事
		GetCodec で通信コーデックを獲得していること。
		通信コーデックの設定が終了していること。
	]
	comment		:[
		ＥＣＭバッファ先頭アドレスからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UDWORD CDC_SetRelayedTxReport(void)
{
	UWORD line;
	UWORD max_line_of_page = 0;
	MESSAGE_t *message_from_lst;
	MESSAGE_t message_to_lst;
	UBYTE	tti_available;
	UBYTE ret;

	ret = FALSE;

	/* 原稿長確定 */
	/* 蓄積原稿長とは別に決めるので、 SYS_DocBlock は参照しない。*/
	switch (FaxTxMaxLength) {
	case SYS_B4_LENGTH:
		max_line_of_page = GetMaxTxLine(SYS_B4_PAGE_LENGTH);
		break;
	case SYS_NO_LIMIT:
		max_line_of_page = GetMaxTxLine(SYS_NO_LIMIT_PAGE_LENGTH);
		break;
	case SYS_A4_LENGTH:
	default:
		max_line_of_page = GetMaxTxLine(SYS_A4_PAGE_LENGTH);
		break;
	}

#if 0 /* Changed by H.Kubo 1998/01/20 */
	max_line_of_page /= CodecParameterRegister[COMMUNICATION_CODEC].INLINE_Status;
#else
	if (FaxTxMaxLength != SYS_NO_LIMIT) {
		max_line_of_page /= 16; /* 走査線16本で1行 */
	}
#endif
	if (CodecParameterRegister[COMMUNICATION_CODEC].C0_VCONV_Status != 0) {
		max_line_of_page /= CodecParameterRegister[COMMUNICATION_CODEC].C0_VCONV_Status;
	}

	/* TTI 送出処理 */
	if(CHK_UNI_RxDocToPollingDoc()) {
		tti_available = 0;
	}
	else {
		tti_available = FCM_PtnrChkTTI_TxAvailable();
		max_line_of_page -= 1;
	}

	/*-----------------*/
	/**ＴＴＩセット処理*/
	/*-----------------*/
	if (tti_available) {	/**ＴＴＩを送出するとき*/
		/*----------------------------------*/
		/*	ＥＣＭバッファにＴＴＩをセット	*/
		/*----------------------------------*/
		EcmBufferBaseWritePoint = CDC_SetTTI();
		ModemMessage.Message = MSG_TTI_COMPLETE;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, 16);	/**入力ライン数(1回に符号化するライン数)*/
		CodecCodeConvertCDCR_Setup(COMMUNICATION_CODEC);	/**CDCR設定*/
	}
	else {
		/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
		ModemMessage.Message = MSG_TTI_COMPLETE;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		CDC_CTxSetupCodec(CDC_ENCODE_RCR);  /* argument is added by H.Kubo 1997/12/19 */
	}
	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/


	/* TTI 終わり */


	/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
#if 0
@@	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
@@	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
#endif

	message_to_lst.Item = FROM_CODEC_CTX;
	message_to_lst.Message = MSG_CDC_REQUEST_PAGE_END;

	ret = FALSE;
	for (line = 1; line <= max_line_of_page; line++) {
		/* リスト側に一行分のイメージ作成依頼 */
		/*
		**	CDC_REQUEST_NEW_LINE_PAGE_END  一行印字要求＆ページ終了要求
		**	CDC_REQUEST_NEW_LINE           一行印字要求
		*/
		message_to_lst.Message = MSG_CDC_REQUEST_NEW_LINE;
		if (line > max_line_of_page - 6 ) { /*一ページ最大行数の 5 行前から改ページを試みる */
			message_to_lst.Message |= MSG_CDC_REQUEST_PAGE_END;
		}
		snd_msg(mbxno.CDC_CTx,&message_to_lst);

		/* 結果通知 */
		rcv_msg(mbxno.CDC_CTx, &message_from_lst);
		
		/* LST_ACK_ONE_LINE_IMAGE   一行印字成功
		** LST_EMPTY_ONE_LINE_IMAGE 印字データ無
		** LST_ACK_PAGE_END          改ページ許可
		*/

		switch( message_from_lst->Message ) {
		case MSG_LST_ACK_NEW_LINE: /* 画データができた */
			CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
			break;
		case (MSG_LST_ACK_NEW_LINE | MSG_LST_ACK_PAGE_END):
			CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
			ret = TRUE;
			break;
		default:  /* できんかった */
			/* 終わり。ループを抜ける */
			ret = TRUE;
			break;
		}
		if (ret == TRUE) {
			break;
		}
	}

#if 0 /* Deleted by H.Kubo 1998/01/17 画データはつけないので、いらない。*/
@@	/**残り行数が17行以下の場合、次のﾍﾟｰｼﾞに蓄積原稿を印字する*/
@@	if (line > RELAYED_TX_REPORT_LINES - 17) {
@@		message_to_lst.Message = MSG_CDC_REQUEST_NEW_LINE | MSG_CDC_REQUEST_NEW_PAGE;
@@		snd_msg(mbxno.CDC_CTx,&message_to_lst);
@@		/* 結果通知 */
@@		rcv_msg(mbxno.CDC_CTx, &message_from_lst);
@@
@@	}
@@	else {
@@		/* 後は画データをくっつけるだけ。*/
@@	}
#endif

	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	/* CDC_MTxCodeConvertPageTask で RTC/NEWLEN をつけます。 */
#else
	/* RTC/NEWLENコマンド発行 */
	if (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
	else {
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
#endif
	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));

}
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
#endif /* (PRO_COM_CODEC_TYPE != SOFTWARE) 通信コーデックがソフトでなければ */ /* ファイルの頭の #if に対応。 */

#if (PRO_COM_CODEC_TYPE == MN86064) && (PRO_JBIG == ENABLE) /* added by H.Kubo 1998/07/08 */
void CDC_InitCodecEncodeStructJbig(struct CodecEncodeParameterBlk_t *cdc_cnv)
{
	cdc_cnv->C_QMCR_Status = VLENGTH_BIT;
	if (CHK_UNI_JBIG_2lineTemplate()) {
		cdc_cnv->C_QMCR_Status |= LRLTWO_BIT;
	}
	if (CHK_UNI_JBIG_TPB_Mode()) {
		cdc_cnv->C_QMCR_Status |= TPBON_BIT;
	}
	if (CHK_UNI_JBIG_SDRST()) {
		cdc_cnv->C_QMCR_Status |= SDRST_BIT;
	}
	cdc_cnv->C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	cdc_cnv->C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	cdc_cnv->C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	cdc_cnv->C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	cdc_cnv->D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	cdc_cnv->D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	cdc_cnv->D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	cdc_cnv->D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	cdc_cnv->D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
}
#endif

#if (PRO_COM_CODEC_TYPE != SOFTWARE) /* 共通のコードをまとめます。 added by H.Kubo 1998/07/08 */
UWORD CDC_GetCodecEncodeMCLR(void)
{
	UWORD co_mclr;
	if (TxECM_Mode == ECM_ON) {
		co_mclr = 0;
	}
	else {
		if (SYS_DocBlock.MSE_Method == MSE1) {
			co_mclr = 0;
		}
		else {
			co_mclr = SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
		}
	}
	return co_mclr;
}


UBYTE CDC_GetCtxCodecEncode_I_OBXR(void)
{
	UBYTE obxr;
	switch (SYS_DocBlock.Dst.Size) {
	case SYS_DOCUMENT_A4_SIZE:
		obxr	= LST_LEFT_WHITE_A4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
		break;
	case SYS_DOCUMENT_B4_SIZE:
		obxr	= LST_LEFT_WHITE_B4;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
		break;
	case SYS_DOCUMENT_A3_SIZE:
	default:
		obxr	= LST_LEFT_WHITE_A3;	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
		break;
	}
	if (SYS_DocBlock.Dst.Mode == SYS_HFINE) { /* HFINE のときは主走査方向 2倍*/
		obxr *= 2;
	} 
	else if ((SYS_DocBlock.Dst.Mode == SYS_EFINE) ||
			 (SYS_DocBlock.Dst.Mode == SYS_E_HFINE) ) { /* EFINE のときは主走査方向 2/3倍*/
		 obxr *=3;
		 obxr /=2;
	}
	return obxr;
}

void CDC_CtxCodecEncodeStructMagnify(struct CodecEncodeParameterBlk_t *cdc_cnv, UBYTE image_kind)
{
	switch (SYS_DocBlock.Dst.Mode) {
	case SYS_NORMAL:
		if ( image_kind == CDC_ENCODE_TTI) { /* Changed by H.Kubo 1997/12/19 */
			cdc_cnv->C0_HCONV_Status = 0x2002;	/**符号化主走査方向変換率 ２倍*/
			cdc_cnv->C0_VCONV_Status = 0;		/**符号化副走査方向変換率 等倍*/
		}
		else {
#if (PRO_COM_CODEC_TYPE == MN86063)
			cdc_cnv->C0_HCONV_Status = 0xA002;	/**符号化主走査方向変換率 ２倍*/
#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
			cdc_cnv->C0_HCONV_Status = 0xB002;	/**符号化主走査方向変換率 ２倍*/
#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
#else /* (PRO_COM_CODEC_TYPE) */
#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
#endif/* (PRO_COM_CODEC_TYPE) */
			cdc_cnv->C0_VCONV_Status = 0x0000;		/**符号化副走査方向変換率 等倍*/
		}
		cdc_cnv->C0_KPR_Status	= 2;		/**符号化Kパラメータ*/
		break;
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY32:
	case SYS_GRAY32_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
#if (PRO_COM_CODEC_TYPE == MN86063)
		cdc_cnv->C0_HCONV_Status = 0xA002;	/**符号化主走査方向変換率 ２倍*/
#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
		cdc_cnv->C0_HCONV_Status = 0xB002;	/**符号化主走査方向変換率 ２倍*/ /* 符号化副走査方向固定倍率 */
#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
#else /* (PRO_COM_CODEC_TYPE) */
#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
#endif/* (PRO_COM_CODEC_TYPE) */
		if ( image_kind == CDC_ENCODE_TTI) { /* Changed by H.Kubo 1997/12/19 */
			if ( CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
				cdc_cnv->C0_VCONV_Status = 0x0000;	/**符号化副走査方向変換率等倍*/ /* Changed by H.Kubo 1997/12/19 */
			}
			else {
				cdc_cnv->C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
			}
		}
		else {
			cdc_cnv->C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
		}
		cdc_cnv->C0_KPR_Status	= 4;		/**符号化Kパラメータ*/
		break;
	case SYS_SFINE:
#if (PRO_COM_CODEC_TYPE == MN86063)
		cdc_cnv->C0_HCONV_Status = (0xA000 | 0x0002); /**符号化主走査方向変換率 ２倍*/
#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
		cdc_cnv->C0_HCONV_Status = (0xB000 | 0x0002); /**符号化主走査方向変換率 ２倍＆符号化副走査方向固定倍率 */
#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
#else /* (PRO_COM_CODEC_TYPE) */
#error "The Communication CODEC is other than MN86063 or MN86064. Fix me!"
#endif/* (PRO_COM_CODEC_TYPE) */
		if (image_kind == CDC_ENCODE_TTI) {
			if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
				cdc_cnv->C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
			}
			else {
				cdc_cnv->C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
			}
		}
		else {
			cdc_cnv->C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 4倍*/
		}
		cdc_cnv->C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
		break;
	case SYS_HFINE:
#if (PRO_COM_CODEC_TYPE == MN86063)
		cdc_cnv->C0_HCONV_Status = 0xA004;	/**符号化主走査方向変換率 ４倍*/
#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/19 */
		cdc_cnv->C0_HCONV_Status = 0xB004;	/**符号化主走査方向変換率 ４倍＆符号化副走査方向固定倍率 */
#elif (PRO_COM_CODEC_TYPE == SOFTWARE) /* added by H.Kubo 1997/11/19 */
#else /* (PRO_COM_CODEC_TYPE) */
#error	"The Communication CODEC is other than MN86063 or MN86064. Fix me!"
#endif/* (PRO_COM_CODEC_TYPE) */
		if ( image_kind == CDC_ENCODE_TTI) {
			if (CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
				cdc_cnv->C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
			}
			else {
				cdc_cnv->C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
			}
		}
		else {
			cdc_cnv->C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 4倍*/
		}
		cdc_cnv->C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
		break;
	case SYS_EFINE:
	case	SYS_E_HFINE:
#if (PRO_COM_CODEC_TYPE == MN86063)
		cdc_cnv->C0_HCONV_Status = 0xA003;	/**符号化主走査方向変換率 ３倍	for ANZU By T.YAMAGUCHI 96/05/14 */
#elif (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/12/19 */
		cdc_cnv->C0_HCONV_Status = 0xB003;	/**符号化主走査方向変換率 ３倍	for ANZU */
#else /* (PRO_COM_CODEC_TYPE) */
#error	"The Communication CODEC is other than MN86063 or MN86064. Fix me!"
#endif/* (PRO_COM_CODEC_TYPE) */
		if ( (image_kind == CDC_ENCODE_TTI) && CHK_UNI_TTI_Size()) { /* image_kind is added by H.Kubo 1997/12/19 */
			cdc_cnv->C0_VCONV_Status = 0x0002;	/**符号化副走査方向変換率 2倍*/
		}
		else {
			cdc_cnv->C0_VCONV_Status = 0x0004;	/**符号化副走査方向変換率 ４倍*/
		}
		cdc_cnv->C0_KPR_Status	= 8;		/**符号化Kパラメータ*/
		break;
	default:	/*ここはエラー*/
		cdc_cnv->C0_HCONV_Status = 0;	/**符号化主走査方向変換率*/
		cdc_cnv->C0_VCONV_Status = 0;	/**符号化副走査方向変換率*/
		cdc_cnv->C0_KPR_Status	= 1;	/**符号化Kパラメータ*/
		break;
	}
}
#endif

/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
/*************************************************************************
	module		:[カバーページの符号化を行う]
	function	:[
		1. V53DMAUを設定関数をコール
		2. カバーページフォント展開関数をコール
		3. V53DMA許可
		4. 符号化を開始する
		5. V53DMA禁止
	]
	return		:[
		符号データ最終アドレス
	]
	common		:[
		FontImageBuffer
		SYS_DocBlock
	]
	condition	:[
		ハンドシェーク後、通信符号化方式、および原稿幅が確定している事
	]
	comment		:[
		ＥＣＭバッファ先頭アドレスからセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UDWORD CDC_SetEmergencyReport(void)
{
	UBYTE line;

#if (0)
** /* 下記処理、やっぱり必要だそうです。（７ｃｍ分） By O.Kimoto 1999/12/10 */
#if (0)
** 	/* 医師会の特ＲＯＭの為、メッセージ送信長は必要分しか送信しません。 By O.Kimoto 1999/04/01 */
** 	UWORD  cover_dmylinecnt;
** 
** 	/*941209 1line Insert for F43 Printer Rx by T.Soneoka*/
** 	cover_dmylinecnt = 0x12; /* 18*16=288line  CoverPage(74mm)+DummyLine(288line->74.80mm)=144.80mm */
#endif
#else
	UWORD  cover_dmylinecnt;

	cover_dmylinecnt = 0x12; /* 18*16=288line  CoverPage(74mm)+DummyLine(288line->74.80mm)=144.80mm */
#endif

#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
	CDC_CTxSetupDMAU();
	/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	CDC_CTxSetupCodec(CDC_ENCODE_COVERPAGE);  /* argument is added by H.Kubo 1997/12/19 */
	for (line = 1; line <= 8; line++) {
		LST_SetEmergencyReport_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		CDC_CTxStartEncodeAndJBIGIRQ(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
#else
	CDC_CTxSetupDMAU();
	CDC_CTxSetupCodec(CDC_ENCODE_COVERPAGE);  /* argument is added by H.Kubo 1997/12/19 */
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestEnable(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	for (line = 1; line <= 8; line++) {
		LST_SetEmergencyReport_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**PBR:INLINEに設定したライン数を連続して符号化する*/
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestMask(DMA_DRAM_COMCDC_CH);
 #endif
		DMA_SetDMA_Address(DMA_DRAM_COMCDC_CH, DMA_MEMORY_TO_IO, dma_24bit_start_address);
 #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/08/19 */
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);
 #endif
	}
#endif /* (PRO_JBIG == ENABLE) */

#if (0)
** /* 下記処理、やっぱり必要だそうです。（７ｃｍ分） By O.Kimoto 1999/12/10 */
** #if (0)
** ** 	/* 医師会の特ＲＯＭの為、メッセージ送信長は必要分しか送信しません。 By O.Kimoto 1999/04/01 */
** ** 	/*941209 insert for F43 printer rx*/
** ** 	while (cover_dmylinecnt--) {
** ** 		CDC_SetDummyLine(16);	/**ダミー白16ラインをセット*/
** ** 	}
** #endif
#else
	while (cover_dmylinecnt--) {
		CDC_SetDummyLine(16);	/**ダミー白16ラインをセット*/
	}
#endif


#if (PRO_JBIG == ENABLE)	/*  by H.Kubo 1997/12/27 */
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
	/* RTC/NEWLENコマンド発行 */
	if (SYS_DocBlock.Dst.Code != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
	else {
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
#else
	SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**ページの終わりにRTCをセットする*/
#endif /* (PRO_JBIG == ENABLE) */
	DMA_RequestMask(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	DMA_RequestMask(DMA_COMCDC_DRAM_CH);	/*DMAUの種類*/
	return(DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));
}
 #endif
#endif


