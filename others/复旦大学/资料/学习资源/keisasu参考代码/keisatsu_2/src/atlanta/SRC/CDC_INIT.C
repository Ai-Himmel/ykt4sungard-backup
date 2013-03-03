/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/16
*        FILE NAME:  cdc_init.c
*      DESCRIPTION:  松下製コーデックNM86063を初期化する為のファイル群
*  PUBLIC ROUTINES:  void InitializeCodec(UBYTE codec_type);
* PRIVATE ROUTINES:  void ResetCodec(UBYTE codec_type);
*                    void InitializeCodecValue(UBYTE codec_type);
*                    void InitializeCodecParameterValue(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\cdc_blk.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
/*DMA*/
#include  "\src\atlanta\define\dma_def.h"	/*Add By M.Kotani 1998/04/21*/
#include  "\src\atlanta\define\dma_blk.h"	/*Add By M.Kotani 1998/04/21*/
#include  "\src\atlanta\define\dma_pro.h"	/*Add By M.Kotani 1998/04/21*/

#if (PRO_JBIG == ENABLE)
#if (0)	/* 1998/03/24 調査終了 */
//extern UBYTE	debug_swap;	/* ＪＢＩＧ調査 Ｓｗａｐ処理 1998/03/23 by T.Soneoka */
#endif
 #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
  #include "\src\atlanta\ext_v\sys_data.h" /* added by H.Hirao 1998/12/16 */
  #include "\src\atlanta\define\sysdoc.h" /* added by H.Hirao 1998/12/16 */
 #endif
#endif

#if defined(POPLAR_H) && defined(JP0)/*V851 By Y.Suzuki 2002/10/01*/
  #include "\src\atlanta\ext_v\sys_data.h" /* added by H.Hirao 1998/12/16 */
  #include "\src\atlanta\define\sysprint.h"
#endif

/*************************************************************************
	module		:[引数のMN86063を初期化する]
	function	:[
		1.コーデックリセット&コーデック使用大域変数クリア
		2.MSCR(マスターコントロールレジスタ)を設定する
		3.DTCR(データコントロールレジスタ)を設定する
		4.初期化(全体)
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
	]
	condition	:[]
	comment		:[
		Power On, Codec Open時にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void InitializeCodec(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD test;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	InitializeCodecValue(codec_type);					/**コーデック使用大域変数クリア*/
	/*
	** Ｂ４の後のＡ４のプリンタ受信（ＪＢＩＧデコード）の時、左側の画像（４０ｍｍ程度）が
	** Ａ４右側に回り込む対策 by H.Hirao 1998/12/16
	*/
#if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
  #if (PRO_JBIG == ENABLE)
	if ((SYS_DocBlock.Src.Code == SYS_JBIG_CODE) && (CodecGetID[codec_type] == CODEC_PRINTER_RX)) {
		SetCodecAllParameterRegister(codec_type);
	}
  #endif
#endif
	ResetCodec(codec_type);								/**コーデックリセット*/
	/**MSCR(マスターコントロールレジスタ)を設定する*/
	if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
		CodecMSCR_DTCR_Status[codec_type] &= ~MODE_BIT;		/**0:MN86064動作*/
		CodecMSCR_DTCR_Status[codec_type] &= ~REQTM_BIT;	/**0:エッジ検出DMAC対応*/
		test = 0;
		if (test) {
			CodecMSCR_DTCR_Status[codec_type] |= REQTM_BIT;		/**0:レベル検出DMAC対応 MN86064Bug!!*/
		}
	}
	else {
		CodecMSCR_DTCR_Status[codec_type] |= LONG_BIT;		/**1:ロングフレーム 4864bit*//**MN86063動作*/
		CodecMSCR_DTCR_Status[codec_type] &= ~REQTM_BIT;	/**0:エッジ検出DMAC対応*/
	}
	/**DTCR(データコントロールレジスタ)を設定する*/
	CodecMSCR_DTCR_Status[codec_type] |= IOHEX_BIT;		/**I/Oバス幅(0:8bit, 1:16bit) DTCR:IBHEX=1の時有効*/
	CodecMSCR_DTCR_Status[codec_type] |= IBHEX_BIT;		/**イメージバス幅(0:8bit, 1:16bit) 0の時ID0-7が有効*/
	CodecMSCR_DTCR_Status[codec_type] &= ~BCODER_BIT;	/**符号データビット送出順序(0:入れ替えない, 1:入れ替える)*/
#if (PRO_CPU == SH7043)	/**モトローラ系のエンディアンタイプ*/
		CodecMSCR_DTCR_Status[codec_type] |= BCSWAP_BIT;	/**符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
#if (0)	/* 1998/03/24 調査終了 */
//		if (!debug_swap) {	/* ＪＢＩＧ調査 Ｓｗａｐ処理 1998/03/23 by T.Soneoka */
//			CodecMSCR_DTCR_Status[codec_type] |= BCSWAP_BIT;	/**符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
//		}
#endif
#else	/**インテル系のエンディアンタイプ*/
	CodecMSCR_DTCR_Status[codec_type] &= ~BCSWAP_BIT;	/**符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
#endif
	CodecMSCR_DTCR_Status[codec_type] &= ~BEODR0_BIT;	/**画像データビット送出順序(0:入れ替えない, 1:入れ替える)*/
	CodecMSCR_DTCR_Status[codec_type] &= ~BESWP0_BIT;	/**画像データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
		CodecMODR_Enable(codec_type);	/**モードレジスタを有効にする*/
		CodecEncodeCodeByteSwapEnable(codec_type);	/**符号化符号データバイト交換:入れ替える*/
		CodecDecodeCodeByteSwapEnable(codec_type);	/**復号化符号データバイト交換:入れ替える*/
#if (0)
//		/**HDMR(ハードマスクレジスタ)を設定する*/
//		CodecHDMR_MODR_Status[codec_type] |= 0x007F;	/**ハードマスク有効(0:無効, 1:有効)*/
//		outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
#endif
#endif
#if (PRO_JBIG == ENABLE)
#if (0)	/* 1998/03/24 調査終了 */
//	if (debug_swap) {	/* ＪＢＩＧ調査 Ｓｗａｐ処理 1998/03/23 by T.Soneoka */
//		CodecHDMR_MODR_Status[codec_type] |= 0xC000;	/* 複合化時入力バイト交換有効 */
//		outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
//	}
#endif
#endif
#if (0) /* デバッグ終了 1998/04/30 by T.Soneoka */
**#if (PRO_PANEL == KANJI)
**	if (codec_type == PRINTER_CODEC) {
**		SetCodecParameterRegister(PRINTER_CODEC, IMGWT_ADR, CodecParameterRegister[codec_type].IMGWT_Status); /* 1998/04/30 by T.Soneoka */
**	}
**#endif
#endif
	EnterCodecCommand(codec_type, CODEC_CMD_ALL_INIT);	/**初期化(全体)*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	EnterCodecCommand(PRINTER_CODEC, CODEC_CMD_ALL_INIT);	/**初期化(全体)*//*チャンネル１も初期化する*/
#endif
}


/*************************************************************************
	module		:[MN86063をソフトウェアリセットする]
	function	:[
		1.コーデックリセット
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
	]
	condition	:[]
	comment		:[
		void far InitializeCodec(unsigned char)よりCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void ResetCodec(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	CodecMSCR_DTCR_Status[codec_type] |= SWR_BIT;	/**R/W マスタコントロール,データコントロールレジスタ*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
	CodecMSCR_DTCR_Status[codec_type] &= ~SWR_BIT;	/**R/W マスタコントロール,データコントロールレジスタ*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
	wai_tsk(1);
}


/*************************************************************************
	module		:[MN86063用大域変数を初期化する]
	function	:[
		1.MN86063が使用する大域変数を初期化する
		2.コーデックの使用状況格納用変数のクリア
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
		CodecCDCR_Status
		CodecCMDR_Status
		CodecSTIR_Status
		CodecDMCR_DMIR_Status
		CodecMAR_Status
		CodecPBR_Status
	]
	condition	:[]
	comment		:[
		void far InitializeCodec(unsigned char)よりCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void InitializeCodecValue(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/** CODEC REGISTER SETTING STATUS */
	CodecMSCR_DTCR_Status[codec_type]	= 0;	/**R/W マスタコントロール,データコントロールレジスタ*/
	CodecCDCR_Status[codec_type]		= 0;	/**R/W 符号化,復号化コントロールレジスタ*/
	CodecCMDR_Status[codec_type]		= 0;	/**W   コマンドレジスタ*/
	CodecSTIR_Status[codec_type]		= 0;	/**R   状態,割り込みレジスタ*/
	CodecDMCR_DMIR_Status[codec_type]	= 0;	/**R/W DMA転送コントロール,割り込みレジスタ*/
	CodecMAR_Status[codec_type]			= 0;	/**R/W メモリアドレスレジスタ*/
	CodecPBR_Status[codec_type]			= 0;	/**R/W パラメータバッファレジスタ*/
	CodecHDMR_MODR_Status[codec_type]	= 0;	/*R/W ﾊｰﾄﾞﾏｽｸﾚｼﾞｽﾀ,ﾓｰﾄﾞﾚｼﾞｽﾀ Only MN86064*/
	CodecTSTR_Status[codec_type]		= 0;	/*R/W ﾃｽﾄﾚｼﾞｽﾀ Only MN86064 (アクセスしないでください)*/
	/**MN86063パラメータレジスタ用大域変数を初期化する*/
	InitializeCodecParameterValue(codec_type);
	/**コーデックのイメージバッファアクセス状態を初期化する*/
	CDC_ImageBufferStatus[codec_type] = CDC_NOT_ACCESS;	/* =0 */
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	Is_JBIG_Restart = 0;	/**	JBIGリスタート */
#endif
}


/*************************************************************************
	module		:[MN86063パラメータレジスタ用大域変数を初期化する]
	function	:[
		1.MN86063パラメータレジスタ用大域変数を初期化する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void near InitializeCodecValue(unsigned char)よりCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void InitializeCodecParameterValue(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/** CODEC PARAMETER REGISTER SETTING STATUS */
	/** 入出力パラメータ */
	CodecParameterRegister[codec_type].FRWORD_Status = 0;		/**フレームワード数*/
	CodecParameterRegister[codec_type].INWORD_Status = 0;		/**入力ワード数*/
	CodecParameterRegister[codec_type].INLINE_Status = 0;		/**入力ライン数*/
	CodecParameterRegister[codec_type].OTWORD_Status = 0;		/**出力ワード数*/
	CodecParameterRegister[codec_type].I_OBXR_Status = 0;		/**入力オフセット*/
	CodecParameterRegister[codec_type].O_OBXR_Status = 0;		/**出力オフセット*/
	/** 符号化パラメータ Ch.0 */
	CodecParameterRegister[codec_type].C0_STRA_Status = 0;		/**符号化ライン先頭アドレス*/
	CodecParameterRegister[codec_type].C0_PWDR_Status = 0;		/**符号化ページ幅*/
	CodecParameterRegister[codec_type].C0_OBXR_Status = 0;		/**符号化オフセット*/
	CodecParameterRegister[codec_type].C0_RTCR_Status = 0;		/**符号化RTC数*/
	CodecParameterRegister[codec_type].C0_KPR_Status = 0;		/**符号化Kパラメータ*/
	CodecParameterRegister[codec_type].C0_LCONT_Status = 0;		/**符号化ラインカウンタ*/
	CodecParameterRegister[codec_type].C0_MCLR_Status = 0;		/**符号化最小符号バイト数*/
	CodecParameterRegister[codec_type].C0_HCONV_Status = 0;		/**符号化主走査方向変換率*/
	CodecParameterRegister[codec_type].C0_VCONV_Status = 0;		/**符号化副走査方向変換率*/
	CodecParameterRegister[codec_type].C0_LMASK_Status = 0;		/**符号化左側白マスク*/
	CodecParameterRegister[codec_type].C0_RMASK_Status = 0;		/**符号化右側白マスク*/
	CodecParameterRegister[codec_type].C0_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス*/
	CodecParameterRegister[codec_type].C0_MENDA_Status = 0;		/**符号化イメージバッファ最終アドレス*/
	/** 復号化パラメータ Ch.0 */
	CodecParameterRegister[codec_type].D0_STRA_Status = 0;		/**復号化ライン先頭アドレス*/
	CodecParameterRegister[codec_type].D0_PWDR_Status = 0;		/**復号化ページ幅*/
	CodecParameterRegister[codec_type].D0_OBXR_Status = 0;		/**復号化オフセット*/
	CodecParameterRegister[codec_type].D0_RTCR_Status = 0;		/**復号化RTC数*/
	CodecParameterRegister[codec_type].D0_BLGR_Status = 0;		/**復号化処理ライン数*/
	CodecParameterRegister[codec_type].D0_LCONT_Status = 0;		/**復号化ラインカウンタ*/
	CodecParameterRegister[codec_type].D0_UWLIN_Status = 0;		/**上端白ライン数*/	/*MN86064で追加*//* MN86063 Dummy1 Extra Area*/
	CodecParameterRegister[codec_type].D0_LWLIN_Status = 0;		/**下端白ライン数*/	/*MN86064で追加*//* MN86063 Dummy1 Extra Area*/
	CodecParameterRegister[codec_type].D0_ELIN_Status = 0;		/**復号化エラーライン数*/
	CodecParameterRegister[codec_type].D0_HCONV_Status = 0;		/**復号化主走査方向変換率*/
	CodecParameterRegister[codec_type].D0_VCONV_Status = 0;		/**復号化副走査方向変換率*/
	CodecParameterRegister[codec_type].D0_LMASK_Status = 0;		/**復号化左側白マスク*/
	CodecParameterRegister[codec_type].D0_RMASK_Status = 0;		/**復号化右側白マスク*/
	CodecParameterRegister[codec_type].D0_MTOPA_Status = 0;		/**復号化イメージバッファ先頭アドレス*/
	CodecParameterRegister[codec_type].D0_MENDA_Status = 0;		/**復号化イメージバッファ最終アドレス*/
	/** 符号化パラメータ Ch.1 */
	CodecParameterRegister[codec_type].C1_STRA_Status = 0;		/**符号化ライン先頭アドレス*/
	CodecParameterRegister[codec_type].C1_PWDR_Status = 0;		/**符号化ページ幅*/
	CodecParameterRegister[codec_type].C1_OBXR_Status = 0;		/**符号化オフセット*/
	CodecParameterRegister[codec_type].C1_RTCR_Status = 0;		/**符号化RTC数*/
	CodecParameterRegister[codec_type].C1_KPR_Status = 0;		/**符号化Kパラメータ*/
	CodecParameterRegister[codec_type].C1_LCONT_Status = 0;		/**符号化ラインカウンタ*/
	CodecParameterRegister[codec_type].C1_MCLR_Status = 0;		/**符号化最小符号バイト数*/
	CodecParameterRegister[codec_type].C1_HCONV_Status = 0;		/**符号化主走査方向変換率*/
	CodecParameterRegister[codec_type].C1_VCONV_Status = 0;		/**符号化副走査方向変換率*/
	CodecParameterRegister[codec_type].C1_LMASK_Status = 0;		/**符号化左側白マスク*/
	CodecParameterRegister[codec_type].C1_RMASK_Status = 0;		/**符号化右側白マスク*/
	CodecParameterRegister[codec_type].C1_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス*/
	CodecParameterRegister[codec_type].C1_MENDA_Status = 0;		/**符号化イメージバッファ最終アドレス*/
	/** 復号化パラメータ Ch.1 */
	CodecParameterRegister[codec_type].D1_STRA_Status = 0;		/**復号化ライン先頭アドレス*/
	CodecParameterRegister[codec_type].D1_PWDR_Status = 0;		/**復号化ページ幅*/
	CodecParameterRegister[codec_type].D1_OBXR_Status = 0;		/**復号化オフセット*/
	CodecParameterRegister[codec_type].D1_RTCR_Status = 0;		/**復号化RTC数*/
	CodecParameterRegister[codec_type].D1_BLGR_Status = 0;		/**復号化処理ライン数*/
	CodecParameterRegister[codec_type].D1_LCONT_Status = 0;		/**復号化ラインカウンタ*/
	CodecParameterRegister[codec_type].D1_ELIN_Status = 0;		/**復号化エラーライン数*/
	CodecParameterRegister[codec_type].D1_HCONV_Status = 0;		/**復号化主走査方向変換率*/
	CodecParameterRegister[codec_type].D1_VCONV_Status = 0;		/**復号化副走査方向変換率*/
	CodecParameterRegister[codec_type].D1_LMASK_Status = 0;		/**復号化左側白マスク*/
	CodecParameterRegister[codec_type].D1_RMASK_Status = 0;		/**復号化右側白マスク*/
	CodecParameterRegister[codec_type].D1_MTOPA_Status = 0;		/**復号化イメージバッファ先頭アドレス*/
	CodecParameterRegister[codec_type].D1_MENDA_Status = 0;		/**復号化イメージバッファ最終アドレス*/
	/** データ転送パラメータ */
	CodecParameterRegister[codec_type].B_STRA0_Status = 0;		/**データ転送先頭アドレス0*/
	CodecParameterRegister[codec_type].B_STRA1_Status = 0;		/**データ転送先頭アドレス1*/
	CodecParameterRegister[codec_type].B_HCONV_Status = 0;		/**データ転送主走査方向変換率*/
	CodecParameterRegister[codec_type].B_VCONV_Status = 0;		/**データ転送副走査方向変換率*/
	CodecParameterRegister[codec_type].B_LMASK_Status = 0;		/**データ転送左側白マスク*/
	CodecParameterRegister[codec_type].B_RMASK_Status = 0;		/**データ転送右側白マスク*/
	/** DMA転送パラメータ */
	CodecParameterRegister[codec_type].Dummy1 = 0;				/**Extra Area*/
	CodecParameterRegister[codec_type].T0_STRA_Status = 0;		/**DMA転送先頭アドレスポインタ*/
	CodecParameterRegister[codec_type].T0_WORD_Status = 0;		/**DMA転送ワード数*/
	CodecParameterRegister[codec_type].T0_BLGR_Status = 0;		/**DMA転送ライン数*/
	CodecParameterRegister[codec_type].T0_MTOPA_Status = 0;		/**DMA転送バッファ先頭アドレス*/
	CodecParameterRegister[codec_type].Dummy2 = 0;				/**Extra Area*/
	CodecParameterRegister[codec_type].T0_MENDA_Status = 0;		/**DMA転送バッファ最終アドレス*/
	CodecParameterRegister[codec_type].Dummy3 = 0;				/**Extra Area*/
	CodecParameterRegister[codec_type].T1_STRA_Status = 0;		/**DMA転送先頭アドレスポインタ*/
	CodecParameterRegister[codec_type].T1_WORD_Status = 0;		/**DMA転送ワード数*/
	CodecParameterRegister[codec_type].T1_BLGR_Status = 0;		/**DMA転送ライン数*/
	CodecParameterRegister[codec_type].T1_MTOPA_Status = 0;		/**DMA転送バッファ先頭アドレス*/
	CodecParameterRegister[codec_type].Dummy4 = 0;				/**Extra Area*/
	CodecParameterRegister[codec_type].T1_MENDA_Status = 0;		/**DMA転送バッファ最終アドレス*/
	/** その他のパラメータ */
	CodecParameterRegister[codec_type].C0_REFA_Status = 0;		/*符号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy6 Extra Area*/
	CodecParameterRegister[codec_type].C1_REFA_Status = 0;		/*符号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy7 Extra Area*/
	CodecParameterRegister[codec_type].D0_REFA_Status = 0;		/*復号化ﾁｬﾝﾈﾙ0参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy8 Extra Area*/
	CodecParameterRegister[codec_type].D1_REFA_Status = 0;		/*復号化ﾁｬﾝﾈﾙ1参照ﾗｲﾝ先頭ｱﾄﾞﾚｽ*/	/*MN86064で追加*//* MN86063 Dummy9 Extra Area*/
	CodecParameterRegister[codec_type].STRADD_Status = 0;		/**メモリ先頭アドレス*/
	CodecParameterRegister[codec_type].ENDADD_Status = 0;		/**メモリ最終アドレス*/
	CodecParameterRegister[codec_type].Dummy5 = 0;				/**Extra Area*/
	CodecParameterRegister[codec_type].Dummy6 = 0;				/**Extra Area*/
	/* LSI Config ﾊﾟﾗﾒｰﾀ For MN86064 */
	CodecParameterRegister[codec_type].Vmn_Status = 0;			/*間引き/OR指定*/
#if (0) /* デバッグ終了 1998/04/30 by T.Soneoka */
**#if (PRO_PANEL == KANJI)
**	if (codec_type == PRINTER_CODEC) {
**		CodecParameterRegister[codec_type].IMGWT_Status = 0;		/*ｲﾒｰｼﾞﾊﾞｽwaitｻｲｸﾙ数*//*変更時はハード屋に確認すること*/
**	}
**	else {
**		CodecParameterRegister[codec_type].IMGWT_Status = 2;		/*ｲﾒｰｼﾞﾊﾞｽwaitｻｲｸﾙ数*//*変更時はハード屋に確認すること*/
**	}
**#else
**	CodecParameterRegister[codec_type].IMGWT_Status = 2;		/*ｲﾒｰｼﾞﾊﾞｽwaitｻｲｸﾙ数*//*変更時はハード屋に確認すること*/
**#endif
#endif
/* 
** 上記のイメージ側のWaitのデバッグ終了時にミスした（全部コメントにしてしまった）
** 元に戻します  1999/01/12 by T.Soneoka
*/
    CodecParameterRegister[codec_type].IMGWT_Status = 2;

	CodecParameterRegister[codec_type].IMGBNK0_Status = 0;		/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定0*/
	CodecParameterRegister[codec_type].IMGBNK1_Status = 0;		/*ｲﾒｰｼﾞﾊﾞｽｱﾄﾞﾚｽ空間ﾊﾞﾝｸ指定1*/
	/* JBIG ﾊﾟﾗﾒｰﾀ For MN86064 */
	CodecParameterRegister[codec_type].Y1CREFA_Status = 0;		/*JBIG符号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
	CodecParameterRegister[codec_type].Y2CREFA_Status = 0;		/*JBIG符号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
	CodecParameterRegister[codec_type].Y1DREFA_Status = 0;		/*JBIG復号化参照ﾗｲﾝ1先頭ｱﾄﾞﾚｽ*/
	CodecParameterRegister[codec_type].Y2DREFA_Status = 0;		/*JBIG復号化参照ﾗｲﾝ2先頭ｱﾄﾞﾚｽ*/
	CodecParameterRegister[codec_type].Dummy7 = 0;				/*Extra Area*/
	CodecParameterRegister[codec_type].Dummy8 = 0;				/*Extra Area*/
	/* JBIG 符号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	CodecParameterRegister[codec_type].C_QMCR_Status = 0;		/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].C_QMIR_Status = 0;		/*QM割り込みﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].C_QMIRM_Status = 0;		/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].C_Yd_Status = 0;			/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	CodecParameterRegister[codec_type].C_L0_Status = 0;			/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	CodecParameterRegister[codec_type].C_Mx_Status = 0;			/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	CodecParameterRegister[codec_type].C_tx1_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
	CodecParameterRegister[codec_type].C_tx0_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
	CodecParameterRegister[codec_type].C_YAT0_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
	CodecParameterRegister[codec_type].C_YAT1_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
	CodecParameterRegister[codec_type].C_QMBUF0_Status = 0;		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
	CodecParameterRegister[codec_type].C_QMBUF1_Status = 0;		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
	/* JBIG 復号化ﾊﾟﾗﾒｰﾀ For MN86064 */
	CodecParameterRegister[codec_type].D_QMCR_Status = 0;		/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].D_QMIR_Status = 0;		/*QM割り込みﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].D_QMIRM_Status = 0;		/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
	CodecParameterRegister[codec_type].D_Yd_Status = 0;			/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
	CodecParameterRegister[codec_type].D_L0_Status = 0;			/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
	CodecParameterRegister[codec_type].D_Mx_Status = 0;			/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	CodecParameterRegister[codec_type].D_tx1_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ1*/
	CodecParameterRegister[codec_type].D_tx0_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ2*/
	CodecParameterRegister[codec_type].D_YAT0_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ0有効ﾗｲﾝ指定*/
	CodecParameterRegister[codec_type].D_YAT1_Status = 0;		/*ATMOVEﾊﾟﾗﾒｰﾀ1有効ﾗｲﾝ指定*/
	CodecParameterRegister[codec_type].D_QMBUF0_Status = 0;		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ0*/
	CodecParameterRegister[codec_type].D_QMBUF1_Status = 0;		/*QMﾃﾞｰﾀﾊﾞｯﾌｧ1*/
}


/*************************************************************************
	module		:[MN8606xに接続されているイメージメモリを初期化する]
	function	:[
		1. DMAUを設定する
		2. DMA許可
		3. CDCを設定する
		4. データ転送を開始する
		5. DMA禁止
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		POPLAR_Lのデバッグ用
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/04/21]
	author		:[小谷正樹]
*************************************************************************/
void CDC_InitializePrintImageMemory(UWORD initial_data)	/*初期化データ*/
{
	struct CodecDataTransferParameterBlk_t data_trans_blk;
	struct DMA_Data_t dma;

	/* DMAUセットアップ */
	dma.Channel = DMA_DRAM_PRNCDC_CH;			/*DMAチャンネル*/
	dma.SrcAddress = (UDWORD)&initial_data;
	dma.Counter = 0x0001;						/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;				/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;			/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	DMA_SetupDMAU(&dma);
	DMA_AutoInitializeEnable(DMA_DRAM_PRNCDC_CH);	/** DMAU AutoInitializeMode Enable */
	DMA_RequestEnable(dma.Channel);

	/* コーデックセットアップ */
	SetClear((UBYTE *)&data_trans_blk, sizeof(struct CodecDataTransferParameterBlk_t), 0x00);
	data_trans_blk.CodecType = PRINTER_CODEC;
	data_trans_blk.FRWORD_Status = 304;
	data_trans_blk.INWORD_Status = 304;
	data_trans_blk.INLINE_Status = 107;
	data_trans_blk.OTWORD_Status = 304;
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
	data_trans_blk.B_LMASK_Status = 0;	/*ﾃﾞｰﾀ転送左側白ﾏｽｸ*/
	data_trans_blk.B_RMASK_Status = 0;	/*ﾃﾞｰﾀ転送右側白ﾏｽｸ*/
	data_trans_blk.Vmn_Status = 0;		/*間引き/OR指定*/
	/**上記のパラメータでコーデックをセットアップする*/
	CodecDataTransferSetup(&data_trans_blk);
	EnterCodecCommand(PRINTER_CODEC, CODEC_CMD_DATA_TRANSFER);	/**PBR:INLINEに設定したライン数を連続してデータ転送する*//*※データ転送するまでリターンしない*/
	DMA_AutoInitializeDisable(DMA_DRAM_PRNCDC_CH);	/** DMAU AutoInitializeMode Enable */
	DMA_RequestMask(dma.Channel);
}

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*By Y.Suzuki 2002/06/07*/
/*************************************************************************
	module		:[システムに応じたコーデックの使用方法を設定します]
	function	:[
	]
	return		:[なし]
	common		:[
		CDC_HowToUse
	]
	condition	:[]
	comment		:[
		Power On時、省エネからの復帰時にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[2002/06/07]
	author		:[鈴木]
*************************************************************************/
void CDC_InitializeCodec(void)
{
	InitializeCodec(SCANNER_CODEC);			/*	読み取りコーデック初期化（リセットを含む）              */
	InitializeCodec(COMMUNICATION_CODEC);	/*	通信コーデック初期化（リセットを含む）              */
	InitializeCodec(PRINTER_CODEC);			/*	プリントコーデック初期化（リセットを含む）              */
}
#endif

