/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/22
*        FILE NAME:  jbg_aad.c
*       Task ID No:
*      DESCRIPTION:  ＡＡＤ(Adaptive Arithmetic Decoder)
*                    T.82(JBIG)によるアダプティブ算術復号化を行う為のファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.82(JBIG)によるＡＡＤメイン処理
	]
	function	:[
		1.手順ＩＮＩＴＤＥＣを呼ぶ
		2.ＣＸ、ＴＰＶＡＬＵＥ、ＤＰＶＡＬＵＥを読む
		3.ＴＰＶＡＬＵＥ！＝２の時の処理
		4.ＤＰＶＡＬＵＥ！＝２の時の処理
		5.手順ＤＥＣＯＤＥを呼ぶ
		6.ストライプ終了まで繰り返す
	]
	return		:[なし]
	common		:[
		JBG_Cx, JBG_TpValue, JBG_DpValue
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void JBG_AAD(void)
{
	AAD_InitDec();							/** Ｔ．８２：手順ＩＮＩＴＤＥＣを呼ぶ */
	do {	/** ストライプ終了までループする */
		JBG_DecodeTPB();				/** ＴＰＢ(Typical Prediction (Bottom))典型的予測（ボトム）器の呼び出し */
		if (!JBG_LntpY) {					/** 前ラインと同一の場合 */
			JBG_CopyReferenceLine();		/** 前参照ラインを参照ラインにコピー出力する */
		}
		else {							/**	前ラインと一致しない場合(JBG_TpValue = 2) */
			JBG_DecodeReferenceLine();		/** 参照ラインに復号化したイメージをセットする */
		}
		JBG_IncrementReferenceLineY();	/** 参照ラインポインタを１ライン更新する */
		JBG_DecodeLineCount++;			/** 復号化ラインをインクリメント */
		JBG_DecodeStripeLineCount++;	/** ストライプ中の復号化ラインをインクリメント */
	} while (JBG_DecodeStripeLineCount < JBG_BIH.L0);	/** ストライプ終了か？ */
	JBG_DecodeStripeCount++;			/** ストライプカウンタをインクリメント */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による１ライン復号化する
		参照ラインに復号化したイメージをセットする
	]
	function	:[
		1.参照コンテクストの初期化
		2.復号化ラインのＸポインタの初期化
		3.ＣＸを獲得する
		4.手順ＤＥＣＯＤＥを呼ぶ
		5.Pixを参照ラインに出力する
		6.復号化ラインのＸポインタをインクリメントする
		7.１ライン終了まで3.にループする
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/12]
	author		:[小谷正樹]
*************************************************************************/
void JBG_DecodeReferenceLine(void)
{
	UWORD loop;
	UWORD end_ptr;

	JBG_ResetCx();	/** 参照コンテクストの初期化 */
	JBG_ReferenceLineX_Ptr = JBG_BYTE_MARGIN_LEFT * 8;	/** 復号化ラインのＸポインタの初期化 */
	end_ptr = (UWORD)(JBG_BIH.XD + (JBG_BYTE_MARGIN_LEFT * 8));	/*１ライン終了位置*/
	for (loop = 0; loop < JBG_MAX_REFERENCE_X; loop++) {
		JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][loop] = 0;	/** 参照ラインの初期化 */
	}
	JBG_PrePrePix = 0;			/** 前々画素 */
	JBG_PrePix = 0;		/** 前画素を初期化 */
	JBG_Pix = 0;		/** 画素を初期化 */
	do {	/** １ライン終了までループする */
		JBG_PrePrePix = JBG_PrePix;	/** 現ラインのコンテクスト作成のために前々画素を保存 */
		JBG_PrePix = JBG_Pix;		/** 現ラインのコンテクスト作成のために現画素を保存 */
		JBG_MT();	/** ＣＸを獲得する */
		AAD_Decode();	/** 手順ＤＥＣＯＤＥを呼ぶ */
		if (JBG_Pix) {	/** Pixを参照ラインに出力する */
			JBG_PixByteP = JBG_ReferenceLineX_Ptr / 8;
			JBG_PixByteBitP = JBG_ReferenceLineX_Ptr % 8;
			JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][JBG_PixByteP]
			|= (UBYTE)(0x80 >> (UBYTE)JBG_PixByteBitP);
		}
#if (JBG_DEBUG)
/*DumpRLTable();*/
DumpRL();
#endif
		JBG_ReferenceLineX_Ptr++;	/** 復号化ラインのＸポインタをインクリメントする */
	} while (JBG_ReferenceLineX_Ptr < end_ptr);	/*１ライン終了か？*/
#if (JBG_DEBUG)
DumpEOL();
#endif
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＤＥＣＯＤＥ処理
	]
	function	:[
		1.インタバルサイズレジスタにＭＰＳのサブインタバルをセット
		2.CHIGH_RegisterとＭＰＳのサイズを比較
		3.ＭＰＳの正規化が必要なときは、ＭＰＳ／ＬＰＳの条件付き変換が起こる可能性がある
		4.ＭＰＳよりＰＩＸを獲得する
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_Pix
	]
	condition	:[]
	comment		:[
		void JBG_AAD(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAD_Decode(void)
{
	JBG_A_Register -= JBG_LszTable[JBG_St[JBG_Cx]];		/** インタバルサイズレジスタにＭＰＳのサブインタバルをセット */
	/* if (CHIGH_Register < JBG_A_Register) { */	/* 下記に置き換え */
	if ((JBG_C_Register >> 16) < JBG_A_Register) {	/** CHIGH_RegisterとＭＰＳのサイズを比較。正規化が必要？ */
		if (JBG_A_Register < 0x8000) {				/** ＭＰＳサイズをチェック。ＭＰＳの正規化が必要？ */
			AAD_MpsExchange();						/** 手順ＭＰＳ－ＥＸＣＨＡＮＧＥを呼ぶ */
			AAD_Renormd();							/** 手順ＲＥＮＯＲＭＤを呼ぶ */
		}
		else {
			JBG_Pix = JBG_Mps[JBG_Cx];				/** ＭＰＳより、ＰＩＸを獲得 */
		}
	}
	else {
		AAD_LpsExchange();							/** 手順ＬＰＳ－ＥＸＣＨＡＮＧＥを呼ぶ */
		AAD_Renormd();								/** 手順ＲＥＮＯＲＭＤを呼ぶ */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＬＰＳ－ＥＸＣＨＡＮＧＥ処理
	]
	function	:[
		1.ＭＰＳサイズとＬＰＳサイズを比較
		2.コードレジスタからＭＰＳサブインタバルを減算する
		3.ＬＳＰサイズを符号化インタバルとする
		4.ＭＰＳよりＰＩＸを獲得する
		5.新しいステータスをセット
	]
	return		:[なし]
	common		:[
		JBG_C_Register, JBG_A_Register, JBG_Pix, JBG_St, JBG_Mps
	]
	condition	:[]
	comment		:[
		void AAD_Decode(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/23]
	author		:[小谷正樹]
*************************************************************************/
void AAD_LpsExchange(void)
{
	if (JBG_A_Register < JBG_LszTable[JBG_St[JBG_Cx]]) {	/** ＭＰＳサイズがＬＰＳサイズより小さい場合 */
		/* CHIGH_Register -= JBG_A_Register; */	/* 下記に置き換え */
		JBG_C_Register -= (JBG_A_Register << 16);	/** コードレジスタからＭＰＳサブインタバルを減算する */
		JBG_A_Register = JBG_LszTable[JBG_St[JBG_Cx]];	/** ＬＳＰサイズを符号化インタバルとする */
		JBG_Pix = JBG_Mps[JBG_Cx];					/** ＭＰＳより、ＰＩＸを獲得 */
		JBG_St[JBG_Cx] = JBG_NmpsTable[JBG_St[JBG_Cx]];	/** ステータスを次のＭＰＳであるＮＭＳＰテーブルの値とする */
	}
	else {
		/* CHIGH_Register -= JBG_A_Register; */	/* 下記に置き換え */
		JBG_C_Register -= (JBG_A_Register << 16);	/** コードレジスタからＭＰＳサブインタバルを減算する */
		JBG_A_Register = JBG_LszTable[JBG_St[JBG_Cx]];	/** ＬＳＰサイズを符号化インタバルとする */
		JBG_Pix = (UBYTE)(1 - JBG_Mps[JBG_Cx]);	/** ＭＰＳの反転より、ＰＩＸを獲得 */
		if (JBG_SwitchTable[JBG_St[JBG_Cx]] == 1) {		/** スイッチが１の時 */
			JBG_Mps[JBG_Cx] = (UBYTE)(1 - JBG_Mps[JBG_Cx]);	/** ＭＰＳを反転する */
		}
		JBG_St[JBG_Cx] = JBG_NlpsTable[JBG_St[JBG_Cx]];	/** ステータスを次のＬＰＳであるＮＬＳＰテーブルの値とする */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＭＰＳ－ＥＸＣＨＡＮＧＥ処理
	]
	function	:[
		1.ＭＰＳサイズとＬＰＳサイズを比較
		2.ＭＰＳよりＰＩＸを獲得する
		3.新しいステータスをセット
	]
	return		:[なし]
	common		:[
		JBG_Pix, JBG_St, JBG_Mps
	]
	condition	:[]
	comment		:[
		void AAD_Decode(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/23]
	author		:[小谷正樹]
*************************************************************************/
void AAD_MpsExchange(void)
{
	if (JBG_A_Register < JBG_LszTable[JBG_St[JBG_Cx]]) {	/** ＭＰＳサイズがＬＰＳサイズより小さい場合 */
		JBG_Pix = (UBYTE)(1 - JBG_Mps[JBG_Cx]);		/** ＭＰＳの反転より、ＰＩＸを獲得 */
		if (JBG_SwitchTable[JBG_St[JBG_Cx]] == 1) {			/** スイッチが１の時 */
			JBG_Mps[JBG_Cx] = (UBYTE)(1 - JBG_Mps[JBG_Cx]);	/** ＭＰＳを反転する */
		}
		JBG_St[JBG_Cx] = JBG_NlpsTable[JBG_St[JBG_Cx]];		/** ステータスを次のＬＰＳであるＮＬＳＰテーブルの値とする */
	}
	else {
		JBG_Pix = JBG_Mps[JBG_Cx];							/** ＭＰＳの反転より、ＰＩＸを獲得 */
		JBG_St[JBG_Cx] = JBG_NmpsTable[JBG_St[JBG_Cx]];		/** ステータスを次のＬＰＳであるＮＭＳＰテーブルの値とする */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＲＥＮＯＲＭＤ処理
	]
	function	:[
		1.シフトカウンタが０の時は１バイト符号データをＳＣＤより入力する
		2.インタバルサイズレジスタを１ビットシフトする
		3.コードレジスタを１ビットシフトする
		4.シフトカウンタをデクリメントする
		5.インタバルサイズレジスタが０ｘ８０００より小さい間これを繰り返す
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_C_Register, JBG_CT_Counter
	]
	condition	:[]
	comment		:[
		void AAD_LpsExchange(void)
		void AAD_MpsExchange(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/23]
	author		:[小谷正樹]
*************************************************************************/
void AAD_Renormd(void)
{
	do {
		if (!JBG_CT_Counter) {	/** シフトカウンタが０の時 */
			AAD_ByteIn();	  	/** 手順ＢＹＴＥＩＮ１を呼ぶ（バイト符号データを獲得する） */
		}
		JBG_A_Register <<= 1;	/** インタバルサイズレジスタを１ビットシフトする */
		JBG_C_Register <<= 1;	/** コードレジスタを１ビットシフトする */
		JBG_CT_Counter--;	 	/** シフトカウンタをデクリメントする */
	} while (JBG_A_Register < 0x8000);	/** インタバルサイズレジスタが０ｘ８０００より小さい間これを繰り返す */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＢＹＴＥＩＮ処理
	]
	function	:[
		1.ＳＣＤから１バイト取りだし、ＣＬＯＷの上位８ビットに加算する
		2.次の１バイトＳＣＤデータを取り出すまでのビットカウンタを８にセットする
	]
	return		:[なし]
	common		:[
		JBG_Buffer, JBG_C_Register, JBG_CT_Counter
	]
	condition	:[]
	comment		:[
		void AAD_Renormd(void)
		void AAD_InitDec(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/23]
	author		:[小谷正樹]
*************************************************************************/
void AAD_ByteIn(void)
{
	if (JBG_DecodeEndStatus) {		/** ＳＣＤ終了か？ */
		JBG_Buffer = 0;			/** ＢＵＦＦＥＲを０で初期化 */
	}
	else {
		JBG_Buffer = JBG_ReadSCD();	/** ＳＣＤから１バイト読み、ＢＵＦＦＥＲにセット */
	}
	JBG_C_Register += JBG_Buffer << 8;	/**ＣＬＯＷの上位８ビットに加算する*/
	JBG_CT_Counter = 8;					/** 次の１バイトＳＣＤデータを取り出すまでのビットカウンタを８にセットする */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＩＮＩＴＤＥＣ処理
	]
	function	:[
		1.このレイヤの最初のストライプor強制リセットか
		2.それぞれのケースで、大域変数を初期化する
	]
	return		:[なし]
	common		:[
		JBG_C_Register, JBG_A_Register, JBG_St, JBG_Mps
	]
	condition	:[]
	comment		:[
		void AAD_JBG_AAD(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/23]
	author		:[小谷正樹]
*************************************************************************/
void AAD_InitDec(void)
{
	UDWORD loop;

	JBG_IsDecodeSDE = 0;				/** ＳＤＥを復号化中をクリア */
	JBG_DecodeStripeLineCount = 0;		/** ストライプ中の復号化ラインを初期化 */
	JBG_DecodeEndStatus = 0;			/** 復号化終了時のステータスを初期化 */
	if ((JBG_DecodeStripeCount == 0) || (JBG_DecodeEndStatus & JBG_BIT_RESET)) {	/** このレイヤの最初のストライプor強制リセットか */
		JBG_DpValue = 2;	/** Ｔ．８５準拠（ＤＰＶＡＬＵＥは使用しない） */
		JBG_TpValue = 2;	/** 初期化しておく */
		for (loop = 0; loop < JBG_MAX_CX; loop++) {
			JBG_St[loop] = 0;
			JBG_Mps[loop] = 0;
		}
	}
	else {
		/*Nothing to do*/
	}
	JBG_C_Register = 0;
	AAD_ByteIn();
	JBG_C_Register <<= 8;
	AAD_ByteIn();
	JBG_C_Register <<= 8;
	AAD_ByteIn();
	JBG_A_Register = 0x10000;
}

