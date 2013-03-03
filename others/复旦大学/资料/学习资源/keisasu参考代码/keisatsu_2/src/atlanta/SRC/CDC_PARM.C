/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/16
*        FILE NAME:  cdc_parm.c
*      DESCRIPTION:  松下製コーデックNM86063のパラメータレジスタを
*                    設定する為のファイル群
*  PUBLIC ROUTINES:  void SetCodecParameterRegister(UBYTE codec_type, UWORD address, UWORD data);
*                    UWORD ReadCodecParameterRegister(UBYTE codec_type, UWORD address);
*                    void SetCodecPartParameterRegister(UBYTE codec_type);
*                    void SetCodecAllParameterRegister(UBYTE codec_type);
*                    void ReadCodecAllParameterRegister(UBYTE codec_type)
* PRIVATE ROUTINES:  void CodecEncodeParameterSetup(struct CodecEncodeParameterBlk_t *encode_block);
*                    void CodecDecodeParameterSetup(struct CodecDecodeParameterBlk_t *decode_block);
*                    void CodecCodeConvertParameterSetup(struct CodecCodeConvertParameterBlk_t *code_convert_block);
*                    void CodecDataTransferParameterSetup(struct CodecDataTransferParameterBlk_t *data_transfer_block);
*                    void CodecDMA_TransferParameterSetup(struct CodecDMA_TransferParameterBlk_t *DMA_transfer_block);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\cdc_blk.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"

/*************************************************************************
	module		:[指定されたパラメータレジスタを設定する]
	function	:[
		1.メモリアドレスレジスタ
		2.アドレスをセットする
		3.不要ビットをマスクする
		4.ライトを選択する
		5.アドレスをポートにライトする
		6.パラメータバッファレジスタ
		7.データをセットする
		8.データをポートにライトする
	]
	return		:[なし]
	common		:[
		CodecMAR_Status
		CodecPBR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		パラメータレジスタに書き込みする時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void SetCodecParameterRegister(UBYTE codec_type,	/*使用するコーデック*/
							   UWORD address,		/*セットするパラメータレジスタのアドレス*/
							   UWORD data)			/*セットするパラメータレジスタのデータ*/
{
	UWORD  int_enable;
	UWORD test;
	UWORD loop;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif

	test = 0;
	if (test) {
		int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
		loop = 10000; /**タイムアップ用のループカウンタを１００００回とする*/
		while (loop) {	/**PBRレディになるまで１００００回デッドループでチェックする（正常時最悪１３サイクル）*/
			if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
				CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
			}
			CMN_DisableInterrupt();	/** Sep.23,1994 割り込み禁止*/
			if (!CheckPBR_Ready(codec_type)) {
				loop--;
				continue;
			}
			CodecMAR_Status[codec_type] = 0;						/**メモリアドレスレジスタ*/
			CodecMAR_Status[codec_type] = address;					/**アドレスをセットする*/
			if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
				CodecMAR_Status[codec_type] &= 0x8FFF;					/**不要ビットをマスクする*/
			}
			else {
				CodecMAR_Status[codec_type] &= 0x87FF;					/**不要ビットをマスクする*/
			}
			CodecMAR_Status[codec_type] &= ~MAR_R_W_BIT;			/**ライトを選択する*/
			outpw(CodecRegisterAddressTable[codec_type][CODEC_MAR],
				  CodecMAR_Status[codec_type]);						/**アドレスをポートにライトする*/
			CodecPBR_Status[codec_type] = data;						/**データをセットする*/
			outpw(CodecRegisterAddressTable[codec_type][CODEC_PBR],
				  CodecPBR_Status[codec_type]);						/**データをポートにライトする*/
			WaitPBR_Ready(codec_type);
			if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
				CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
			}
			break;
		}
	}
	else {

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	WaitPBR_Ready(codec_type);
	CodecMAR_Status[codec_type] = 0;						/**メモリアドレスレジスタ*/
	CodecMAR_Status[codec_type] = address;					/**アドレスをセットする*/
	if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
		CodecMAR_Status[codec_type] &= 0x8FFF;					/**不要ビットをマスクする*/
	}
	else {
		CodecMAR_Status[codec_type] &= 0x87FF;					/**不要ビットをマスクする*/
	}
	CodecMAR_Status[codec_type] &= ~MAR_R_W_BIT;			/**ライトを選択する*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MAR],
		  CodecMAR_Status[codec_type]);						/**アドレスをポートにライトする*/
	CodecPBR_Status[codec_type] = data;						/**データをセットする*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_PBR],
		  CodecPBR_Status[codec_type]);						/**データをポートにライトする*/
	WaitPBR_Ready(codec_type);
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** 19978/08/28 割り込み許可*/
	}

	}
}


/*************************************************************************
	module		:[指定されたパラメータレジスタを読み出す]
	function	:[
		1.メモリアドレスレジスタ
		2.アドレスをセットする
		3.不要ビットをマスクする
		4.リードを選択する
		5.アドレスをポートにライトする
		6.パラメータバッファレジスタ
	]
	return		:[
		n>0:	指定されたレジスタの値
	]
	common		:[
		CodecMAR_Status
		CodecPBR_Status
		CodecRegisterAddressTable
]
	condition	:[]
	comment		:[
		パラメータレジスタを読み出す時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD ReadCodecParameterRegister(UBYTE codec_type,	/*使用するコーデック*/
								 UWORD address)	 	/*リードするパラメータレジスタのアドレス*/
{
	UWORD  int_enable;
	UWORD  register_value;
	UWORD test;
	UWORD loop;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif

	test = 0;
	if (test) {
		int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
		loop = 10000; /**タイムアップ用のループカウンタを１００００回とする*/
		while (loop) {	/**PBRレディになるまで１００００回デッドループでチェックする（正常時最悪１３サイクル）*/
			if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
				CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
			}
			CMN_DisableInterrupt();	/** Sep.23,1994 割り込み禁止*/
			if (!CheckPBR_Ready(codec_type)) {
				loop--;
				continue;
			}
			CodecMAR_Status[codec_type] = 0;						/**メモリアドレスレジスタ*/
			CodecMAR_Status[codec_type] = address;					/**アドレスをセットする*/
			if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
				CodecMAR_Status[codec_type] &= 0x8FFF;					/**不要ビットをマスクする*/
			}
			else {
				CodecMAR_Status[codec_type] &= 0x87FF;					/**不要ビットをマスクする*/
			}
			CodecMAR_Status[codec_type] |= MAR_R_W_BIT;				/**リードを選択する*/
			outpw(CodecRegisterAddressTable[codec_type][CODEC_MAR],
				  CodecMAR_Status[codec_type]);						/**アドレスをポートにライトする*/
			WaitPBR_Ready(codec_type);
			CodecPBR_Status[codec_type] = 0;						/**パラメータバッファレジスタ*/
			register_value = CodecPBR_Status[codec_type] = inpw(CodecRegisterAddressTable[codec_type][CODEC_PBR]);			/**パラメータをリードする*/	/*1995/1/26内部変数を使用する Kotani*/
			if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
				CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
			}
			break;
		}
	}
	else {

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** Sep.23,1994 割り込み禁止*/
	WaitPBR_Ready(codec_type);
	CodecMAR_Status[codec_type] = 0;						/**メモリアドレスレジスタ*/
	CodecMAR_Status[codec_type] = address;					/**アドレスをセットする*/
	if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
		CodecMAR_Status[codec_type] &= 0x8FFF;					/**不要ビットをマスクする*/
	}
	else {
		CodecMAR_Status[codec_type] &= 0x87FF;					/**不要ビットをマスクする*/
	}
	CodecMAR_Status[codec_type] |= MAR_R_W_BIT;				/**リードを選択する*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MAR],
		  CodecMAR_Status[codec_type]);						/**アドレスをポートにライトする*/
	WaitPBR_Ready(codec_type);
	CodecPBR_Status[codec_type] = 0;						/**パラメータバッファレジスタ*/
	register_value = CodecPBR_Status[codec_type] = inpw(CodecRegisterAddressTable[codec_type][CODEC_PBR]);			/**パラメータをリードする*/	/*1995/1/26内部変数を使用する Kotani*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}

	}

	return(register_value);	/*1995/1/26内部変数に変更 Kotani*/
}


/*************************************************************************
	module		:[全てのパラメータレジスタを大域変数からセットする]
	function	:[
		1.スタートアドレスをセットする
		2.エンドアドレスをセットする
		3.プログラム転送開始
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		パラメータレジスタをモニタ用大域変数からセットする時Callされる
		パラメータレジスタへのシステムからのDMA転送できないためプログラム転送に変更
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void SetCodecPartParameterRegister(UBYTE codec_type,	/*使用するコーデック*/
								   UWORD start_address,	/*先頭レジスタアドレス*/
								   UWORD end_address)	/*終了レジスタアドレス*/
{
	UWORD *ram_address;	/**大域変数のアドレスポインタ変数*/
	UWORD reg_address;	/**パラメータレジスタのアドレス*/

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	ram_address = &CodecParameterRegister[codec_type].FRWORD_Status;
	ram_address += (start_address - FRWORD_ADR);
	for (reg_address = start_address; reg_address <= end_address; reg_address++) {
		SetCodecParameterRegister(codec_type, reg_address, *ram_address);
		ram_address++;
	}
}


/*************************************************************************
	module		:[全てのパラメータレジスタを大域変数からセットする]
	function	:[
		1.スタートアドレスをセットする
		2.エンドアドレスをセットする
		3.プログラム転送開始
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		パラメータレジスタをモニタ用大域変数からセットする時Callされる
		パラメータレジスタへのシステムからのDMA転送できないためプログラム転送に変更
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void SetCodecAllParameterRegister(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD *ram_address;	/**大域変数のアドレスポインタ変数*/
	UWORD reg_address;	/**パラメータレジスタのアドレス*/

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	ram_address = &CodecParameterRegister[codec_type].FRWORD_Status;
	if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
		for (reg_address =  FRWORD_ADR; reg_address <= D_QMBUF1_ADR; reg_address++) {
#else
		for (reg_address =  FRWORD_ADR; reg_address <= VMN_ADR; reg_address++) {
#endif
			SetCodecParameterRegister(codec_type, reg_address, *ram_address);
			ram_address++;
		}
	}
	else {
		for (reg_address =  FRWORD_ADR; reg_address <= ENDADD_ADR; reg_address++) {
			SetCodecParameterRegister(codec_type, reg_address, *ram_address);
			ram_address++;
		}
	}
	wai_tsk(1);	/*Add By M.Kotani 1998/02/08 処理を放す*/
}


/*************************************************************************
	module		:[全てのパラメータレジスタを大域変数に読み込む]
	function	:[
		1.スタートアドレスをセットする
		2.エンドアドレスをセットする
		3.プログラム転送開始
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		パラメータレジスタをモニタ用大域変数にセットする時Callされる
		パラメータレジスタへのシステムからのDMA転送できないためプログラム転送に変更
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void ReadCodecAllParameterRegister(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD *ram_address;	/**大域変数のアドレスポインタ変数*/
	UWORD reg_address;	/**パラメータレジスタのアドレス*/

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	ram_address = &CodecParameterRegister[codec_type].FRWORD_Status;
	if (CDC_CheckCodecLSI(codec_type) == CDC_MN86064) {
		for (reg_address =  FRWORD_ADR; reg_address <= VMN_ADR; reg_address++) {
			*ram_address = ReadCodecParameterRegister(codec_type, reg_address);
			ram_address++;
		}
	}
	else {
		for (reg_address =  FRWORD_ADR; reg_address <= ENDADD_ADR; reg_address++) {
			*ram_address = ReadCodecParameterRegister(codec_type, reg_address);
			ram_address++;
		}
	}
}


/*************************************************************************
	module		:[符号化に有効なパラメータレジスタ変数を設定する]
	function	:[
		1.コーデックのステータス大域変数に
		, 符号化用のスタックの値を代入する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void CodecEncodeSetup(struct CodecEncodeParameterBlk_t *)
		にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecEncodeParameterSetup(struct CodecEncodeParameterBlk_t *encode_block)	/*符号化用パラメータブロック*/
{
	UWORD word_data;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	/** 入出力パラメータ */
	SetCodecParameterRegister(SCANNER_CODEC, FRWORD_ADR,
	CodecParameterRegister[SCANNER_CODEC].FRWORD_Status	/**フレームワード数*/
	= encode_block->FRWORD_Status);
	SetCodecParameterRegister(SCANNER_CODEC, INWORD_ADR,
	CodecParameterRegister[SCANNER_CODEC].INWORD_Status	/**入力ワード数*/
	= encode_block->INWORD_Status);
	SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR,
	CodecParameterRegister[SCANNER_CODEC].INLINE_Status	/**入力ライン数*/
	= encode_block->INLINE_Status);

	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecParameterRegister[SCANNER_CODEC].I_OBXR_Status	/**入力オフセット*/
	= encode_block->I_OBXR_Status;
	word_data = (CodecParameterRegister[SCANNER_CODEC].I_OBXR_Status << 8) +
				 CodecParameterRegister[SCANNER_CODEC].O_OBXR_Status;
	SetCodecParameterRegister(SCANNER_CODEC, I_OBXR_ADR, word_data);
	CMN_EnableInterrupt();	/** 19978/08/28 割り込み許可*/

	/** 符号化パラメータ Ch.0 */
	SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_STRA_Status	/**符号化ライン先頭アドレス*/
	= encode_block->C0_STRA_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_PWDR_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_PWDR_Status	/**符号化ページ幅*/
	= encode_block->C0_PWDR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_OBXR_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_OBXR_Status	/**符号化オフセット*/
	= encode_block->C0_OBXR_Status);

	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecParameterRegister[SCANNER_CODEC].C0_KPR_Status	/**符号化Kパラメータ*/
	= encode_block->C0_KPR_Status;
	word_data = CodecParameterRegister[SCANNER_CODEC].C0_KPR_Status << 8;
	SetCodecParameterRegister(SCANNER_CODEC, C0_KPR_ADR, word_data);
	CMN_EnableInterrupt();	/** 19978/08/28 割り込み許可*/

	SetCodecParameterRegister(SCANNER_CODEC, C0_LCONT_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_LCONT_Status	/**符号化ラインカウンタ*/
	= encode_block->C0_LCONT_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_MCLR_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_MCLR_Status	/**符号化最小符号バイト数*/
	= encode_block->C0_MCLR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_HCONV_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_HCONV_Status	/**符号化主走査方向変換率*/
	= encode_block->C0_HCONV_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_VCONV_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_VCONV_Status	/**符号化副走査方向変換率*/
	= encode_block->C0_VCONV_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_LMASK_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_LMASK_Status	/**符号化左側白マスク*/
	= encode_block->C0_LMASK_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_RMASK_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_RMASK_Status	/**符号化右側白マスク*/
	= encode_block->C0_RMASK_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_MTOPA_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status	/**符号化イメージバッファ先頭アドレス*/
	= encode_block->C0_MTOPA_Status);
	SetCodecParameterRegister(SCANNER_CODEC, C0_MENDA_ADR,
	CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status	/**符号化イメージバッファ最終アドレス*/
	= encode_block->C0_MENDA_Status);
	if (CDC_CheckCodecLSI(SCANNER_CODEC) == CDC_MN86064) {
		SetCodecParameterRegister(SCANNER_CODEC, VMN_ADR,
		CodecParameterRegister[SCANNER_CODEC].Vmn_Status	/**間引き/OR指定*/
		= encode_block->Vmn_Status);
	}
#else
	/** 入出力パラメータ */
	CodecParameterRegister[encode_block->CodecType].FRWORD_Status	/**フレームワード数*/
	= encode_block->FRWORD_Status;
	CodecParameterRegister[encode_block->CodecType].INWORD_Status	/**入力ワード数*/
	= encode_block->INWORD_Status;
	CodecParameterRegister[encode_block->CodecType].INLINE_Status	/**入力ライン数*/
	= encode_block->INLINE_Status;
	CodecParameterRegister[encode_block->CodecType].I_OBXR_Status	/**入力オフセット*/
	= encode_block->I_OBXR_Status;
	/** 符号化パラメータ Ch.0 */
	CodecParameterRegister[encode_block->CodecType].C0_STRA_Status	/**符号化ライン先頭アドレス*/
	= encode_block->C0_STRA_Status;
	CodecParameterRegister[encode_block->CodecType].C0_PWDR_Status	/**符号化ページ幅*/
	= encode_block->C0_PWDR_Status;
	CodecParameterRegister[encode_block->CodecType].C0_OBXR_Status	/**符号化オフセット*/
	= encode_block->C0_OBXR_Status;
	CodecParameterRegister[encode_block->CodecType].C0_KPR_Status	/**符号化Kパラメータ*/
	= encode_block->C0_KPR_Status;
	CodecParameterRegister[encode_block->CodecType].C0_LCONT_Status	/**符号化ラインカウンタ*/
	= encode_block->C0_LCONT_Status;
	CodecParameterRegister[encode_block->CodecType].C0_MCLR_Status	/**符号化最小符号バイト数*/
	= encode_block->C0_MCLR_Status;
	CodecParameterRegister[encode_block->CodecType].C0_HCONV_Status	/**符号化主走査方向変換率*/
	= encode_block->C0_HCONV_Status;
	CodecParameterRegister[encode_block->CodecType].C0_VCONV_Status	/**符号化副走査方向変換率*/
	= encode_block->C0_VCONV_Status;
	CodecParameterRegister[encode_block->CodecType].C0_LMASK_Status	/**符号化左側白マスク*/
	= encode_block->C0_LMASK_Status;
	CodecParameterRegister[encode_block->CodecType].C0_RMASK_Status	/**符号化右側白マスク*/
	= encode_block->C0_RMASK_Status;
	CodecParameterRegister[encode_block->CodecType].C0_MTOPA_Status	/**符号化イメージバッファ先頭アドレス*/
	= encode_block->C0_MTOPA_Status;
	CodecParameterRegister[encode_block->CodecType].C0_MENDA_Status	/**符号化イメージバッファ最終アドレス*/
	= encode_block->C0_MENDA_Status;
	if (CDC_CheckCodecLSI(encode_block->CodecType) == CDC_MN86064) {
		CodecParameterRegister[encode_block->CodecType].Vmn_Status		/**間引き/OR指定*/
		= encode_block->Vmn_Status;
	}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	CodecParameterRegister[encode_block->CodecType].C_QMCR_Status	/* JBIG符号化QMコントロールレジスタ */
	= encode_block->C_QMCR_Status;
	CodecParameterRegister[encode_block->CodecType].C_QMIRM_Status	/* JBIG符号化QM割り込みマスクレジスタ */
	= encode_block->C_QMIRM_Status;
	CodecParameterRegister[encode_block->CodecType].C_Yd_Status	/* JBIG符号化１ページ処理ライン */
	= encode_block->C_Yd_Status;
	CodecParameterRegister[encode_block->CodecType].C_L0_Status	/* JBIG符号化ストライプライン数 */
	= encode_block->C_L0_Status;
	CodecParameterRegister[encode_block->CodecType].C_Mx_Status	/* JBIG符号化ATMOVE最大許容オフセット */
	= encode_block->C_Mx_Status;
	CodecParameterRegister[encode_block->CodecType].D_QMCR_Status	/* JBIG復号化QMコントロールレジスタ */
	= encode_block->D_QMCR_Status;
	CodecParameterRegister[encode_block->CodecType].D_QMIRM_Status	/* JBIG復号化QM割り込みマスクレジスタ */
	= encode_block->D_QMIRM_Status;
	CodecParameterRegister[encode_block->CodecType].D_Yd_Status	/* JBIG復号化１ページ処理ライン */
	= encode_block->D_Yd_Status;
	CodecParameterRegister[encode_block->CodecType].D_L0_Status	/* JBIG復号化ストライプライン数 */
	= encode_block->D_L0_Status;
	CodecParameterRegister[encode_block->CodecType].D_Mx_Status	/* JBIG復号化ATMOVE最大許容オフセット */
	= encode_block->D_Mx_Status;
#endif
	SetCodecAllParameterRegister(encode_block->CodecType);
#endif
}


/*************************************************************************
	module		:[復号化に有効なパラメータレジスタ変数を設定する]
	function	:[
		1.コーデックのステータス大域変数に
		, 復号化用のスタックの値を代入する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void CodecDecodeSetup(struct CodecDecodeParameterBlk_t *)
		にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDecodeParameterSetup(struct CodecDecodeParameterBlk_t *decode_block)	/*復号化用パラメータブロック*/
{
	UWORD word_data;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	/** 入出力パラメータ */
	SetCodecParameterRegister(SCANNER_CODEC, FRWORD_ADR,
	CodecParameterRegister[SCANNER_CODEC].FRWORD_Status	/**フレームワード数*/
	= decode_block->FRWORD_Status);
	SetCodecParameterRegister(SCANNER_CODEC, OTWORD_ADR,
	CodecParameterRegister[SCANNER_CODEC].OTWORD_Status	/**出力ワード数*/
	= decode_block->OTWORD_Status);

	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecParameterRegister[SCANNER_CODEC].O_OBXR_Status	/**出力オフセット*/
	= decode_block->O_OBXR_Status;
	word_data = (CodecParameterRegister[SCANNER_CODEC].I_OBXR_Status << 8) +
				 CodecParameterRegister[SCANNER_CODEC].O_OBXR_Status;
	SetCodecParameterRegister(SCANNER_CODEC, O_OBXR_ADR, word_data);
	CMN_EnableInterrupt();	/** 19978/08/28 割り込み許可*/

#if (0)/* 小谷さんからの指摘。２重に設定されている。おまけに、下記の設定は間違ってる。 By Y.Suzuki 2000/12/04 */
//	SetCodecParameterRegister(SCANNER_CODEC, O_OBXR_ADR,
//	CodecParameterRegister[SCANNER_CODEC].O_OBXR_Status	/**出力オフセット*/
//	= decode_block->O_OBXR_Status);
#endif
	/** 復号化パラメータ Ch.0 */
	SetCodecParameterRegister(SCANNER_CODEC, D1_STRA_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_STRA_Status	/**復号化ライン先頭アドレス*/
	= decode_block->D0_STRA_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_PWDR_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_PWDR_Status	/**復号化ページ幅*/
	= decode_block->D0_PWDR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_OBXR_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_OBXR_Status	/**復号化オフセット*/
	= decode_block->D0_OBXR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_RTCR_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_RTCR_Status	/**復号化RTC数*/
	= decode_block->D0_RTCR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_BLGR_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_BLGR_Status	/**復号化処理ライン数*/
	= decode_block->D0_BLGR_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_LCONT_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_LCONT_Status	/**復号化ラインカウンタ*/
	= decode_block->D0_LCONT_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_ELIN_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_ELIN_Status	/**復号化エラーライン数*/
	= decode_block->D0_ELIN_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_HCONV_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_HCONV_Status	/**復号化主走査方向変換率*/
	= decode_block->D0_HCONV_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_VCONV_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_VCONV_Status	/**復号化副走査方向変換率*/
	= decode_block->D0_VCONV_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_LMASK_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_LMASK_Status	/**復号化左側白マスク*/
	= decode_block->D0_LMASK_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_RMASK_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_RMASK_Status	/**復号化右側白マスク*/
	= decode_block->D0_RMASK_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_MTOPA_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_MTOPA_Status	/**復号化イメージバッファ先頭アドレス*/
	= decode_block->D0_MTOPA_Status);
	SetCodecParameterRegister(SCANNER_CODEC, D1_MENDA_ADR,
	CodecParameterRegister[SCANNER_CODEC].D1_MENDA_Status	/**復号化イメージバッファ最終アドレス*/
	= decode_block->D0_MENDA_Status);
	if (CDC_CheckCodecLSI(SCANNER_CODEC) == CDC_MN86064) {
		SetCodecParameterRegister(SCANNER_CODEC, VMN_ADR,
		CodecParameterRegister[SCANNER_CODEC].Vmn_Status	/**間引き/OR指定*/
		= decode_block->Vmn_Status);
	}
#else
	/** 入出力パラメータ */
	CodecParameterRegister[decode_block->CodecType].FRWORD_Status	/**フレームワード数*/
	= decode_block->FRWORD_Status;
	CodecParameterRegister[decode_block->CodecType].OTWORD_Status	/**出力ワード数*/
	= decode_block->OTWORD_Status;
	CodecParameterRegister[decode_block->CodecType].O_OBXR_Status	/**出力オフセット*/
	= decode_block->O_OBXR_Status;
	/** 復号化パラメータ Ch.0 */
	CodecParameterRegister[decode_block->CodecType].D0_STRA_Status	/**復号化ライン先頭アドレス*/
	= decode_block->D0_STRA_Status;
	CodecParameterRegister[decode_block->CodecType].D0_PWDR_Status	/**復号化ページ幅*/
	= decode_block->D0_PWDR_Status;
	CodecParameterRegister[decode_block->CodecType].D0_OBXR_Status	/**復号化オフセット*/
	= decode_block->D0_OBXR_Status;
	CodecParameterRegister[decode_block->CodecType].D0_RTCR_Status	/**復号化RTC数*/
	= decode_block->D0_RTCR_Status;
	CodecParameterRegister[decode_block->CodecType].D0_BLGR_Status	/**復号化処理ライン数*/
	= decode_block->D0_BLGR_Status;
	CodecParameterRegister[decode_block->CodecType].D0_LCONT_Status	/**復号化ラインカウンタ*/
	= decode_block->D0_LCONT_Status;
	CodecParameterRegister[decode_block->CodecType].D0_ELIN_Status	/**復号化エラーライン数*/
	= decode_block->D0_ELIN_Status;
	CodecParameterRegister[decode_block->CodecType].D0_HCONV_Status	/**復号化主走査方向変換率*/
	= decode_block->D0_HCONV_Status;
	CodecParameterRegister[decode_block->CodecType].D0_VCONV_Status	/**復号化副走査方向変換率*/
	= decode_block->D0_VCONV_Status;
	CodecParameterRegister[decode_block->CodecType].D0_LMASK_Status	/**復号化左側白マスク*/
	= decode_block->D0_LMASK_Status;
	CodecParameterRegister[decode_block->CodecType].D0_RMASK_Status	/**復号化右側白マスク*/
	= decode_block->D0_RMASK_Status;
	CodecParameterRegister[decode_block->CodecType].D0_MTOPA_Status	/**復号化イメージバッファ先頭アドレス*/
	= decode_block->D0_MTOPA_Status;
	CodecParameterRegister[decode_block->CodecType].D0_MENDA_Status	/**復号化イメージバッファ最終アドレス*/
	= decode_block->D0_MENDA_Status;
	if (CDC_CheckCodecLSI(decode_block->CodecType) == CDC_MN86064) {
		CodecParameterRegister[decode_block->CodecType].Vmn_Status		/**間引き/OR指定*/
		= decode_block->Vmn_Status;
	}
	/* 
	** プリンタ受信の場合、ＪＢＩＧ符号をデコードできるようにします。
	** by H.Hirao 1998/10/28
	*/
 #if (PRO_JBIG == ENABLE) && (PRO_PRINTER_RX == ENABLE)
	CodecParameterRegister[decode_block->CodecType].C_QMCR_Status	/* JBIG符号化QMコントロールレジスタ */
	= decode_block->C_QMCR_Status;
	CodecParameterRegister[decode_block->CodecType].C_QMIRM_Status	/* JBIG符号化QM割り込みマスクレジスタ */
	= decode_block->C_QMIRM_Status;
	CodecParameterRegister[decode_block->CodecType].C_Yd_Status	/* JBIG符号化１ページ処理ライン */
	= decode_block->C_Yd_Status;
	CodecParameterRegister[decode_block->CodecType].C_L0_Status	/* JBIG符号化ストライプライン数 */
	= decode_block->C_L0_Status;
	CodecParameterRegister[decode_block->CodecType].C_Mx_Status	/* JBIG符号化ATMOVE最大許容オフセット */
	= decode_block->C_Mx_Status;
	CodecParameterRegister[decode_block->CodecType].D_QMCR_Status	/* JBIG復号化QMコントロールレジスタ */
	= decode_block->D_QMCR_Status;
	CodecParameterRegister[decode_block->CodecType].D_QMIRM_Status	/* JBIG復号化QM割り込みマスクレジスタ */
	= decode_block->D_QMIRM_Status;
	CodecParameterRegister[decode_block->CodecType].D_Yd_Status	/* JBIG復号化１ページ処理ライン */
	= decode_block->D_Yd_Status;
	CodecParameterRegister[decode_block->CodecType].D_L0_Status	/* JBIG復号化ストライプライン数 */
	= decode_block->D_L0_Status;
	CodecParameterRegister[decode_block->CodecType].D_Mx_Status	/* JBIG復号化ATMOVE最大許容オフセット */
	= decode_block->D_Mx_Status;
 #endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/17 K.Kawata*/
	CodecParameterRegister[decode_block->CodecType].C_QMCR_Status	/* JBIG符号化QMコントロールレジスタ */
	= decode_block->C_QMCR_Status;
	CodecParameterRegister[decode_block->CodecType].C_QMIRM_Status	/* JBIG符号化QM割り込みマスクレジスタ */
	= decode_block->C_QMIRM_Status;
	CodecParameterRegister[decode_block->CodecType].C_Yd_Status	/* JBIG符号化１ページ処理ライン */
	= decode_block->C_Yd_Status;
	CodecParameterRegister[decode_block->CodecType].C_L0_Status	/* JBIG符号化ストライプライン数 */
	= decode_block->C_L0_Status;
	CodecParameterRegister[decode_block->CodecType].C_Mx_Status	/* JBIG符号化ATMOVE最大許容オフセット */
	= decode_block->C_Mx_Status;
	CodecParameterRegister[decode_block->CodecType].D_QMCR_Status	/* JBIG復号化QMコントロールレジスタ */
	= decode_block->D_QMCR_Status;
	CodecParameterRegister[decode_block->CodecType].D_QMIRM_Status	/* JBIG復号化QM割り込みマスクレジスタ */
	= decode_block->D_QMIRM_Status;
	CodecParameterRegister[decode_block->CodecType].D_Yd_Status	/* JBIG復号化１ページ処理ライン */
	= decode_block->D_Yd_Status;
	CodecParameterRegister[decode_block->CodecType].D_L0_Status	/* JBIG復号化ストライプライン数 */
	= decode_block->D_L0_Status;
	CodecParameterRegister[decode_block->CodecType].D_Mx_Status	/* JBIG復号化ATMOVE最大許容オフセット */
	= decode_block->D_Mx_Status;
#endif
	SetCodecAllParameterRegister(decode_block->CodecType);
#endif
}


/*************************************************************************
	module		:[符号変換に有効なパラメータレジスタ変数を設定する]
	function	:[
		1.コーデックのステータス大域変数に
		, 符号変換用のスタックの値を代入する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void CodecCodeConvertSetup(struct CodecCodeConvertParameterBlk_t *)
		にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecCodeConvertParameterSetup(struct CodecCodeConvertParameterBlk_t *code_convert_block)	/*符号変換用パラメータブロック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
#else
	/** 符号化パラメータ Ch.0 */
	CodecParameterRegister[code_convert_block->CodecType].C0_PWDR_Status	/**符号化ページ幅*/
	= code_convert_block->C0_PWDR_Status;
	CodecParameterRegister[code_convert_block->CodecType].C0_OBXR_Status	/**符号化オフセット*/
	= code_convert_block->C0_OBXR_Status;
	CodecParameterRegister[code_convert_block->CodecType].C0_KPR_Status	/**符号化Kパラメータ*/
	= code_convert_block->C0_KPR_Status;
	CodecParameterRegister[code_convert_block->CodecType].C0_LCONT_Status	/**符号化ラインカウンタ*/
	= code_convert_block->C0_LCONT_Status;
	CodecParameterRegister[code_convert_block->CodecType].C0_MCLR_Status	/**符号化最小符号バイト数*/
	= code_convert_block->C0_MCLR_Status;
	/** 復号化パラメータ Ch.0 */
	CodecParameterRegister[code_convert_block->CodecType].D0_PWDR_Status	/**復号化ページ幅*/
	= code_convert_block->D0_PWDR_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_OBXR_Status	/**復号化オフセット*/
	= code_convert_block->D0_OBXR_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_RTCR_Status	/**復号化RTC数*/
	= code_convert_block->D0_RTCR_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_BLGR_Status	/**復号化処理ライン数*/
	= code_convert_block->D0_BLGR_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_LCONT_Status	/**復号化ラインカウンタ*/
	= code_convert_block->D0_LCONT_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_ELIN_Status	/**復号化エラーライン数*/
	= code_convert_block->D0_ELIN_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_HCONV_Status	/**復号化主走査方向変換率*/
	= code_convert_block->D0_HCONV_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_VCONV_Status	/**復号化副走査方向変換率*/
	= code_convert_block->D0_VCONV_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_LMASK_Status	/**復号化左側白マスク*/
	= code_convert_block->D0_LMASK_Status;
	CodecParameterRegister[code_convert_block->CodecType].D0_RMASK_Status	/**復号化右側白マスク*/
	= code_convert_block->D0_RMASK_Status;
	if (CDC_CheckCodecLSI(code_convert_block->CodecType) == CDC_MN86064) {
		CodecParameterRegister[code_convert_block->CodecType].Vmn_Status		/**間引き/OR指定*/
		= code_convert_block->Vmn_Status;
	}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	CodecParameterRegister[code_convert_block->CodecType].C_QMCR_Status	/* JBIG符号化QMコントロールレジスタ */
	= code_convert_block->C_QMCR_Status;
	CodecParameterRegister[code_convert_block->CodecType].C_QMIRM_Status	/* JBIG符号化QM割り込みマスクレジスタ */
	= code_convert_block->C_QMIRM_Status;
	CodecParameterRegister[code_convert_block->CodecType].C_Yd_Status	/* JBIG符号化１ページ処理ライン */
	= code_convert_block->C_Yd_Status;
	CodecParameterRegister[code_convert_block->CodecType].C_L0_Status	/* JBIG符号化ストライプライン数 */
	= code_convert_block->C_L0_Status;
	CodecParameterRegister[code_convert_block->CodecType].C_Mx_Status	/* JBIG符号化ATMOVE最大許容オフセット */
	= code_convert_block->C_Mx_Status;
	CodecParameterRegister[code_convert_block->CodecType].D_QMCR_Status	/* JBIG復号化QMコントロールレジスタ */
	= code_convert_block->D_QMCR_Status;
	CodecParameterRegister[code_convert_block->CodecType].D_QMIRM_Status	/* JBIG復号化QM割り込みマスクレジスタ */
	= code_convert_block->D_QMIRM_Status;
	CodecParameterRegister[code_convert_block->CodecType].D_Yd_Status	/* JBIG復号化１ページ処理ライン */
	= code_convert_block->D_Yd_Status;
	CodecParameterRegister[code_convert_block->CodecType].D_L0_Status	/* JBIG復号化ストライプライン数 */
	= code_convert_block->D_L0_Status;
	CodecParameterRegister[code_convert_block->CodecType].D_Mx_Status	/* JBIG復号化ATMOVE最大許容オフセット */
	= code_convert_block->D_Mx_Status;
#endif
	SetCodecAllParameterRegister(code_convert_block->CodecType);
#endif
}


/*************************************************************************
	module		:[データ転送に有効なパラメータレジスタ変数を設定する]
	function	:[
		1.コーデックのステータス大域変数に
		, データ転送用のスタックの値を代入する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void CodecDataTransferSetup(struct CodecDataTransferParameterBlk_t *)
		にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDataTransferParameterSetup(struct CodecDataTransferParameterBlk_t *data_transfer_block)	/*データ転送用パラメータブロック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	/** 入出力パラメータ */
	CodecParameterRegister[SCANNER_CODEC].FRWORD_Status	/**フレームワード数*/
	= data_transfer_block->FRWORD_Status;
	CodecParameterRegister[SCANNER_CODEC].INWORD_Status	/**入力ワード数*/
	= data_transfer_block->INWORD_Status;
	CodecParameterRegister[SCANNER_CODEC].INLINE_Status	/**入力ライン数*/
	= data_transfer_block->INLINE_Status;
	CodecParameterRegister[SCANNER_CODEC].OTWORD_Status	/**出力ワード数*/
	= data_transfer_block->OTWORD_Status;
	CodecParameterRegister[SCANNER_CODEC].I_OBXR_Status	/**入力オフセット*/
	= data_transfer_block->I_OBXR_Status;
	CodecParameterRegister[SCANNER_CODEC].O_OBXR_Status	/**出力オフセット*/
	= data_transfer_block->O_OBXR_Status;
	/** 符号化パラメータ Ch.0 */
	CodecParameterRegister[SCANNER_CODEC].C1_MTOPA_Status	/**符号化イメージバッファ先頭アドレス*/
	= data_transfer_block->C0_MTOPA_Status;
	CodecParameterRegister[SCANNER_CODEC].C1_MENDA_Status	/**符号化イメージバッファ最終アドレス*/
	= data_transfer_block->C0_MENDA_Status;
	/** 復号化パラメータ Ch.0 */
	CodecParameterRegister[SCANNER_CODEC].D1_MTOPA_Status	/**復号化イメージバッファ先頭アドレス*/
	= data_transfer_block->D0_MTOPA_Status;
	CodecParameterRegister[SCANNER_CODEC].D1_MENDA_Status	/**復号化イメージバッファ最終アドレス*/
	= data_transfer_block->D0_MENDA_Status;
	/** データ転送パラメータ */
	CodecParameterRegister[SCANNER_CODEC].B_STRA0_Status	/**データ転送先頭アドレス0*/
	= data_transfer_block->B_STRA0_Status;
	CodecParameterRegister[SCANNER_CODEC].B_STRA1_Status	/**データ転送先頭アドレス1*/
	= data_transfer_block->B_STRA1_Status;
	CodecParameterRegister[SCANNER_CODEC].B_HCONV_Status	/**データ転送主走査方向変換率*/
	= data_transfer_block->B_HCONV_Status;
	CodecParameterRegister[SCANNER_CODEC].B_VCONV_Status	/**データ転送副走査方向変換率*/
	= data_transfer_block->B_VCONV_Status;
	CodecParameterRegister[SCANNER_CODEC].B_LMASK_Status	/**データ転送左側白マスク*/
	= data_transfer_block->B_LMASK_Status;
	CodecParameterRegister[SCANNER_CODEC].B_RMASK_Status	/**データ転送右側白マスク*/
	= data_transfer_block->B_RMASK_Status;
	if (CDC_CheckCodecLSI(SCANNER_CODEC) == CDC_MN86064) {
		SetCodecParameterRegister(SCANNER_CODEC, VMN_ADR,
		CodecParameterRegister[SCANNER_CODEC].Vmn_Status	/**間引き/OR指定*/
		= data_transfer_block->Vmn_Status);
	}

	SetCodecAllParameterRegister(SCANNER_CODEC);
#else
	/** 入出力パラメータ */
	CodecParameterRegister[data_transfer_block->CodecType].FRWORD_Status	/**フレームワード数*/
	= data_transfer_block->FRWORD_Status;
	CodecParameterRegister[data_transfer_block->CodecType].INWORD_Status	/**入力ワード数*/
	= data_transfer_block->INWORD_Status;
	CodecParameterRegister[data_transfer_block->CodecType].INLINE_Status	/**入力ライン数*/
	= data_transfer_block->INLINE_Status;
	CodecParameterRegister[data_transfer_block->CodecType].OTWORD_Status	/**出力ワード数*/
	= data_transfer_block->OTWORD_Status;
	CodecParameterRegister[data_transfer_block->CodecType].I_OBXR_Status	/**入力オフセット*/
	= data_transfer_block->I_OBXR_Status;
	CodecParameterRegister[data_transfer_block->CodecType].O_OBXR_Status	/**出力オフセット*/
	= data_transfer_block->O_OBXR_Status;
	/** 符号化パラメータ Ch.0 */
	CodecParameterRegister[data_transfer_block->CodecType].C0_MTOPA_Status	/**符号化イメージバッファ先頭アドレス*/
	= data_transfer_block->C0_MTOPA_Status;
	CodecParameterRegister[data_transfer_block->CodecType].C0_MENDA_Status	/**符号化イメージバッファ最終アドレス*/
	= data_transfer_block->C0_MENDA_Status;
	/** 復号化パラメータ Ch.0 */
	CodecParameterRegister[data_transfer_block->CodecType].D0_MTOPA_Status	/**復号化イメージバッファ先頭アドレス*/
	= data_transfer_block->D0_MTOPA_Status;
	CodecParameterRegister[data_transfer_block->CodecType].D0_MENDA_Status	/**復号化イメージバッファ最終アドレス*/
	= data_transfer_block->D0_MENDA_Status;
	/** データ転送パラメータ */
	CodecParameterRegister[data_transfer_block->CodecType].B_STRA0_Status	/**データ転送先頭アドレス0*/
	= data_transfer_block->B_STRA0_Status;
	CodecParameterRegister[data_transfer_block->CodecType].B_STRA1_Status	/**データ転送先頭アドレス1*/
	= data_transfer_block->B_STRA1_Status;
	CodecParameterRegister[data_transfer_block->CodecType].B_HCONV_Status	/**データ転送主走査方向変換率*/
	= data_transfer_block->B_HCONV_Status;
	CodecParameterRegister[data_transfer_block->CodecType].B_VCONV_Status	/**データ転送副走査方向変換率*/
	= data_transfer_block->B_VCONV_Status;
	CodecParameterRegister[data_transfer_block->CodecType].B_LMASK_Status	/**データ転送左側白マスク*/
	= data_transfer_block->B_LMASK_Status;
	CodecParameterRegister[data_transfer_block->CodecType].B_RMASK_Status	/**データ転送右側白マスク*/
	= data_transfer_block->B_RMASK_Status;
	if (CDC_CheckCodecLSI(data_transfer_block->CodecType) == CDC_MN86064) {
		CodecParameterRegister[data_transfer_block->CodecType].Vmn_Status		/**間引き/OR指定*/
		= data_transfer_block->Vmn_Status;
	}

	SetCodecAllParameterRegister(data_transfer_block->CodecType);
#endif
}


/*************************************************************************
	module		:[DMA転送に有効なパラメータレジスタ変数を設定する]
	function	:[
		1.コーデックのステータス大域変数に
		, DMA転送用のスタックの値を代入する
	]
	return		:[なし]
	common		:[
		CodecParameterRegister
	]
	condition	:[]
	comment		:[
		void CodecDMA_TransferSetup(struct CodecDMA_TransferParameterBlk_t *)
		にCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDMA_TransferParameterSetup(struct CodecDMA_TransferParameterBlk_t *DMA_transfer_block)	/*DMA転送用パラメータブロック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	if (DMA_transfer_block->Channel == 0) {	/**チャンネル０を使用する*/
		/** 入出力パラメータ */
		SetCodecParameterRegister(SCANNER_CODEC, FRWORD_ADR,
		CodecParameterRegister[SCANNER_CODEC].FRWORD_Status	/**フレームワード数*/
		= DMA_transfer_block->FRWORD_Status);
		/** DMA転送パラメータ */
		SetCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status	/**DMA転送先頭アドレスポインタ*/
		= DMA_transfer_block->T0_STRA_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T0_WORD_ADR,
		CodecParameterRegister[SCANNER_CODEC].T0_WORD_Status	/**DMA転送ワード数*/
		= DMA_transfer_block->T0_WORD_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T0_BLGR_ADR,
		CodecParameterRegister[SCANNER_CODEC].T0_BLGR_Status	/**DMA転送ライン数*/
		= DMA_transfer_block->T0_BLGR_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T0_MTOPA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T0_MTOPA_Status	/**DMA転送バッファ先頭アドレス*/
		= DMA_transfer_block->T0_MTOPA_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T0_MENDA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T0_MENDA_Status	/**DMA転送バッファ最終アドレス*/
		= DMA_transfer_block->T0_MENDA_Status);
	}
	if (DMA_transfer_block->Channel == 1) {	/**チャンネル１を使用する*/
		/** 入出力パラメータ */
		SetCodecParameterRegister(SCANNER_CODEC, FRWORD_ADR,
		CodecParameterRegister[SCANNER_CODEC].FRWORD_Status	/**フレームワード数*/
		= DMA_transfer_block->FRWORD_Status);
		/** DMA転送パラメータ */
		SetCodecParameterRegister(SCANNER_CODEC, T1_STRA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T1_STRA_Status	/**DMA転送先頭アドレスポインタ*/
		= DMA_transfer_block->T1_STRA_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T1_WORD_ADR,
		CodecParameterRegister[SCANNER_CODEC].T1_WORD_Status	/**DMA転送ワード数*/
		= DMA_transfer_block->T1_WORD_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T1_BLGR_ADR,
		CodecParameterRegister[SCANNER_CODEC].T1_BLGR_Status	/**DMA転送ライン数*/
		= DMA_transfer_block->T1_BLGR_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T1_MTOPA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T1_MTOPA_Status	/**DMA転送バッファ先頭アドレス*/
		= DMA_transfer_block->T1_MTOPA_Status);
		SetCodecParameterRegister(SCANNER_CODEC, T1_MENDA_ADR,
		CodecParameterRegister[SCANNER_CODEC].T1_MENDA_Status	/**DMA転送バッファ最終アドレス*/
		= DMA_transfer_block->T1_MENDA_Status);
	}
#else
	/** 入出力パラメータ */
	CodecParameterRegister[DMA_transfer_block->CodecType].FRWORD_Status	/**フレームワード数*/
	= DMA_transfer_block->FRWORD_Status;
	/** DMA転送パラメータ */
	CodecParameterRegister[DMA_transfer_block->CodecType].T0_STRA_Status	/**DMA転送先頭アドレスポインタ*/
	= DMA_transfer_block->T0_STRA_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T0_WORD_Status	/**DMA転送ワード数*/
	= DMA_transfer_block->T0_WORD_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T0_BLGR_Status	/**DMA転送ライン数*/
	= DMA_transfer_block->T0_BLGR_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T0_MTOPA_Status	/**DMA転送バッファ先頭アドレス*/
	= DMA_transfer_block->T0_MTOPA_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T0_MENDA_Status	/**DMA転送バッファ最終アドレス*/
	= DMA_transfer_block->T0_MENDA_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T1_STRA_Status	/**DMA転送先頭アドレスポインタ*/
	= DMA_transfer_block->T1_STRA_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T1_WORD_Status	/**DMA転送ワード数*/
	= DMA_transfer_block->T1_WORD_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T1_BLGR_Status	/**DMA転送ライン数*/
	= DMA_transfer_block->T1_BLGR_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T1_MTOPA_Status	/**DMA転送バッファ先頭アドレス*/
	= DMA_transfer_block->T1_MTOPA_Status;
	CodecParameterRegister[DMA_transfer_block->CodecType].T1_MENDA_Status	/**DMA転送バッファ最終アドレス*/
	= DMA_transfer_block->T1_MENDA_Status;
	SetCodecAllParameterRegister(DMA_transfer_block->CodecType);
#endif
}
