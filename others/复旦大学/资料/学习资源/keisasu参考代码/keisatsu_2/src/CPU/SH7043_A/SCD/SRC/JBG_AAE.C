/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/22
*        FILE NAME:  jbg_aae.c
*       Task ID No:
*      DESCRIPTION:  ＡＡＥ(Adaptive Arithmetic Encoder)
*                    T.82(JBIG)によるアダプティブ算術符号化を行う為のファイル群
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
		T.82(JBIG)によるＡＡＥメイン処理
	]
	function	:[
		1.手順ＩＮＩＴＥＮＣを呼ぶ
		2.ＰＩＸ、ＣＸ、ＴＰＶＡＬＵＥ、ＤＰＶＡＬＵＥを読む
		3.ＴＰＶＡＬＵＥ！＝２またはＤＰＶＡＬＵＥ！＝２かどうか
		4.手順ＥＮＣＯＤＥを呼ぶ
		5.ストライプ終了まで繰り返す
		6.手順ＦＬＵＳＨを呼ぶ
	]
	return		:[なし]
	common		:[
		JBG_Pix, JBG_Cx, JBG_TpValue, JBG_DpValue
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void JBG_AAE(void)
{
	AAE_InitEnc();	/*手順ＩＮＩＴＥＮＣを呼ぶ*/
	do {	/** １回のループで１ライン符号化する */
		JBG_ReadImageLine();	/** 符号化するためイメージを参照ラインに読み込む */
		JBG_EncodeTPB();	/** ＴＰＢ(Typical Prediction (Bottom))典型的予測（ボトム）器の呼び出し */
		if (JBG_LntpY) {	/** 前ラインと違う場合または、ＴＰＢＯＮ＝０の場合 */
			JBG_EncodeReferenceLine();	/** 参照ラインのイメージを符号化する */
		}
		JBG_IncrementReferenceLineY();	/** 参照ラインポインタを１ライン更新する */
		JBG_EncodeLineCount++;			/** 復号化ラインをインクリメント */
		JBG_EncodeStripeLineCount++;	/** ストライプ中の符号化ラインをインクリメント */
		if (JBG_EncodeLineCount >= JBG_BIH.YD) {	/** 符号化するラインが終了したとき */
			break;
		}
	} while (JBG_EncodeStripeLineCount < JBG_BIH.L0);	/** ストライプ終了か？ */
	JBG_EncodeStripeCount++;			/** ストライプカウンタをインクリメント */
	/*手順ＦＬＵＳＨを呼ぶ*/
	AAE_Flush();
}


/*************************************************************************
	module		:[
		T.82(JBIG)による１ライン符号化する
		参照ラインのイメージを符号化する
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
	date		:[1997/02/14]
	author		:[小谷正樹]
*************************************************************************/
void JBG_EncodeReferenceLine(void)
{
	UWORD end_ptr;
	UBYTE *byte_ptr;
	UBYTE bit_position;
	UBYTE byte_data;
	UBYTE bit_data;

	JBG_ResetCx();	/** 参照コンテクストの初期化 */
	JBG_ReferenceLineX_Ptr = JBG_BYTE_MARGIN_LEFT * 8;	/** 復号化ラインのＸポインタの初期化 */
	end_ptr = (UWORD)(JBG_BIH.XD + (JBG_BYTE_MARGIN_LEFT * 8));	/*１ライン終了位置*/
	JBG_PrePrePix = 0;		/** 前々画素を初期化 */
	JBG_PrePix = 0;		/** 前画素を初期化 */
	JBG_Pix = 0;		/** 画素を初期化 */
	byte_ptr = &JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][JBG_BYTE_MARGIN_LEFT];
	byte_data = *byte_ptr;
	bit_position = 7;
	do {	/** １ライン終了までループする */
		JBG_PrePrePix = JBG_PrePix;	/** 現ラインのコンテクスト作成のために前々画素を保存 */
		JBG_PrePix = JBG_Pix;		/** 現ラインのコンテクスト作成のために前画素を保存 */
		JBG_Pix = 0;		/** 画素を初期化 */
		if (bit_position) {
			bit_data = (UBYTE)(byte_data >> bit_position);
			if (bit_data & 1) {
				JBG_Pix = 1;
			}
			bit_position--;
		}
		else {
			if (byte_data & 1) {
				JBG_Pix = 1;
			}
			byte_ptr++;
			byte_data = *byte_ptr;
			bit_position = 7;
		}
		JBG_MT();	/** ＣＸを獲得する */
		AAE_Encode();	/** 手順ＥＮＣＯＤＥを呼ぶ */
		JBG_ReferenceLineX_Ptr++;	/** 復号化ラインのＸポインタをインクリメントする */
	} while (JBG_ReferenceLineX_Ptr < end_ptr);	/*１ライン終了か？*/
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＥＮＣＯＤＥ処理
	]
	function	:[
		1.符号化対象画素が、優勢確率シンボルか、劣性確率シンボルか判断する
		2.それぞれの処理をコールする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		void AAE_JBG_AAE(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_Encode(void)
{
	if (JBG_Pix == JBG_Mps[JBG_Cx]) {	/** 符号化対象画素が、優勢確率シンボルの場合 */
		AAE_CodeMps();	/** 手順ＣＯＤＥＭＰＳを呼ぶ */
	}
	else {
		AAE_CodeLps();	/** 手順ＣＯＤＥＬＰＳを呼ぶ */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＣＯＤＥＬＰＳ処理
	]
	function	:[
		1.インタバルサイズレジスタにＭＰＳのサブインタバルをセット
		2.ＭＰＳサイズとＬＰＳサイズを比較
		3.スイッチテーブルによるＭＰＳの反転
		4.次のＬＳＰをステータスに格納する
		5.手順ＲＥＮＯＲＭＥを呼ぶ
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_C_Register, JBG_Mps, JBG_St
	]
	condition	:[]
	comment		:[
		void AAE_Encode(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_CodeLps(void)
{
	JBG_A_Register -= JBG_LszTable[JBG_St[JBG_Cx]];			/** インタバルサイズレジスタにＭＰＳのサブインタバルをセット */
	if (JBG_A_Register >= JBG_LszTable[JBG_St[JBG_Cx]]) {	/** ＭＰＳサイズがＬＰＳサイズより大きい場合 */
		JBG_C_Register += JBG_A_Register;					/** コードレジスタにＭＰＳサブインタバルを加える */
		JBG_A_Register = JBG_LszTable[JBG_St[JBG_Cx]];		/** ＬＳＰサイズを符号化インタバルとする */
	}
	if (JBG_SwitchTable[JBG_St[JBG_Cx]] == 1) {					/** スイッチが１の時 */
		JBG_Mps[JBG_Cx] = (UBYTE)(1 - JBG_Mps[JBG_Cx]);	/** ＭＰＳを反転する */
	}
	JBG_St[JBG_Cx] = JBG_NlpsTable[JBG_St[JBG_Cx]];		/** ステータスを次のＬＰＳであるＮＬＳＰテーブルの値とする */
	AAE_Renorme();										/** 手順ＲＥＮＯＲＭＥを呼ぶ */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＣＯＤＥＭＰＳ処理
	]
	function	:[
		1.インタバルサイズレジスタにＭＰＳのサブインタバルに減らす
		2.ＭＰＳサイズと０ｘ８０００を比較
		3.ＭＰＳサイズとＬＰＳサイズを比較
		4.次のＭＳＰをステータスに格納する
		5.手順ＲＥＮＯＲＭＥを呼ぶ
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_C_Register, JBG_St
	]
	condition	:[]
	comment		:[
		void AAE_Encode(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_CodeMps(void)
{
	JBG_A_Register -= JBG_LszTable[JBG_St[JBG_Cx]];				/** インタバルサイズレジスタにＭＰＳのサブインタバルをセット */
	if (JBG_A_Register < 0x8000) {								/** ＭＰＳサイズが０ｘ８０００より小さい場合 */
		if (JBG_A_Register < JBG_LszTable[JBG_St[JBG_Cx]]) {	/** ＭＰＳサイズがＬＰＳサイズより小さい場合 */
			JBG_C_Register += JBG_A_Register;					/** コードレジスタにＭＰＳサブインタバルを加える */
			JBG_A_Register = JBG_LszTable[JBG_St[JBG_Cx]];		/** ＬＳＰサイズを符号化インタバルとする */
		}
		JBG_St[JBG_Cx] = JBG_NmpsTable[JBG_St[JBG_Cx]];			/** ステータスを次のＭＰＳであるＮＭＳＰテーブルの値とする */
		AAE_Renorme();											/** 手順ＲＥＮＯＲＭＥを呼ぶ */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＲＥＮＯＲＭＥ処理
	]
	function	:[
		1.インタバルサイズレジスタを１ビットシフトする
		2.コードレジスタを１ビットシフトする
		3.シフトカウンタをデクリメントする
		4.シフトカウンタが０の時は１バイト符号データをコードレジスタより出力する
		5.インタバルサイズレジスタが０ｘ８０００より小さい間これを繰り返す
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_C_Register, JBG_CT_Counter
	]
	condition	:[]
	comment		:[
		void AAE_CodeLps(void)
		void AAE_CodeMps(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_Renorme(void)
{
	do {
		JBG_A_Register <<= 1;	/** インタバルサイズレジスタを１ビットシフトする */
		JBG_C_Register <<= 1;	/** コードレジスタを１ビットシフトする */
		JBG_CT_Counter--;		/** シフトカウンタをデクリメントする */
		if (!JBG_CT_Counter) {	/** シフトカウンタが０の時 */
			AAE_ByteOut();		/** １バイト符号データを出力する */
		}
	} while (JBG_A_Register < 0x8000);	/** インタバルサイズレジスタが０ｘ８０００より小さい間これを繰り返す */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＢＹＴＥＯＵＴ処理
	]
	function	:[
		1.コードレジスタから完成した１バイトのデータを出力する
		2.コードレジスタから取り出したバイトデータをマスクする
		3.次の１バイトデータを取り出すまでのビットカウンタを８にセットする
	]
	return		:[なし]
	common		:[
		JBG_C_Register, JBG_CT_Counter, JBG_Buffer, JBG_SC_StackCounter
	]
	condition	:[
		Bufferは最初から初期化されない変数
	]
	comment		:[
		void AAE_Renorme(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_ByteOut(void)
{
	UWORD temp;

	temp = (UWORD)(JBG_C_Register >> 19);	/** できあがった上位９バイトをセット */
	if (temp > 0xff) {								/** オーバーフローしている場合 */
		JBG_Buffer++;
		JBG_WritePscd((UBYTE)JBG_Buffer);
		while (JBG_SC_StackCounter) {
			JBG_WritePscd(0x00);							/** スタックカウンター分０を出力する */
			JBG_SC_StackCounter--;
		}
		JBG_Buffer = temp & 0xff;					/** バッファは最下位バイトとする */
	}
	else {
		if (temp == 0xff) {
			JBG_SC_StackCounter++;					/** スタックカウンタをインクリメントする */
		}
		else {
			JBG_WritePscd((UBYTE)JBG_Buffer);
			while (JBG_SC_StackCounter) {			/** スタックカウンター分０ｘＦＦを出力する */
				JBG_WritePscd(0xff);
				JBG_SC_StackCounter--;
			}
			JBG_Buffer = temp;			/** バッファは最下位バイトとする */
		}
	}
	JBG_C_Register &= 0x7ffff;			/** コードレジスタから取り出したバイトデータをマスクする */
	JBG_CT_Counter = 8;					/** 次の１バイトデータを取り出すまでのビットカウンタを８にセットする */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＩＮＩＴＥＮＣ処理
	]
	function	:[
		1.このレイヤの最初のストライプor強制リセットか
		2.それぞれのケースで、大域変数を初期化する
	]
	return		:[なし]
	common		:[
		JBG_A_Register, JBG_C_Register, JBG_CT_Counter, JBG_SC_StackCounter,
		JBG_St, JBG_Mps
	]
	condition	:[]
	comment		:[
		void AAE_JBG_AAE(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_InitEnc(void)
{
	UDWORD loop;

	JBG_EncodeStripeLineCount = 0;	/** ストライプ中の符号化ラインを初期化 */
	if ((JBG_EncodeStripeCount == 0) || JBG_RequestSDRST) {	/** このレイヤの最初のストライプor強制リセットか */
		for (loop = 0; loop < JBG_MAX_CX; loop++) {
			JBG_St[loop] = 0;
			JBG_Mps[loop] = 0;
		}
	}
	else {
		/*Nothing to do*/
	}
	JBG_SC_StackCounter = 0;
	JBG_A_Register = 0x10000;
	JBG_C_Register = 0;
	JBG_CT_Counter = 11;
	JBG_RequestSDRST = 0;	/** ＳＤＲＳＴの作成要求変数の初期化 */
	JBG_RequestSDNORM = 0;	/** ＳＤＮＯＲＭの作成要求変数の初期化 */
	JGB_NullCount = 0;		/** ストライプ最後のＮＵＬＬの個数の初期化 */
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＦＬＵＳＨ処理
	]
	function	:[
		1.手順ＣＬＥＡＲＢＩＴＳを呼ぶ
		2.手順ＦＩＮＡＬＷＲＩＴＥＳを呼ぶ
		3.ＳＣＤ内の最初のバイトを取り除く
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		void AAE_JBG_AAE(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_Flush(void)
{
	AAE_ClearBits();	/*手順ＣＬＥＡＲＢＩＴＳを呼ぶ*/
	AAE_FinalWrite();	/*手順ＦＩＮＡＬＷＲＩＴＥＳを呼ぶ*/
	/*ＳＣＤ内の最初のバイトを取り除く*/
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＣＬＥＡＲＢＩＴＳ処理
	]
	function	:[
		1.コードレジスタは、[C, C+A-1]の中で可能な最大数のゼロビットで終了する
	]
	return		:[なし]
	common		:[
		JBG_C_Register
	]
	condition	:[]
	comment		:[
		void AAE_Flush(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_ClearBits(void)
{
	UDWORD temp;

	temp = (JBG_A_Register - 1 + JBG_C_Register) & 0xffff0000;
	if (temp < JBG_C_Register) {
		JBG_C_Register = temp + 0x8000;
	}
	else {
		JBG_C_Register = temp;
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による手順ＦＩＮＡＬＷＲＩＴＥＳ処理
	]
	function	:[
		1.最終キャリー処理で、コードレジスタから２バイト出力される
	]
	return		:[なし]
	common		:[
		JBG_C_Register, JBG_SC_StackCounter
	]
	condition	:[]
	comment		:[
		void AAE_Flush(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/22]
	author		:[小谷正樹]
*************************************************************************/
void AAE_FinalWrite(void)
{
	JBG_C_Register <<= JBG_CT_Counter;
	if (JBG_C_Register > 0x7ffffff) {
		JBG_WritePscd((UBYTE)(JBG_Buffer + 1));
		while (JBG_SC_StackCounter) {
			JBG_WritePscd(0x00);
			JBG_SC_StackCounter--;
		}
	}
	else {
		JBG_WritePscd((UBYTE)JBG_Buffer);
		while (JBG_SC_StackCounter) {
			JBG_WritePscd(0xff);
			JBG_SC_StackCounter--;
		}
	}
	JBG_WritePscd((UBYTE)((JBG_C_Register >> 19) & 0xff));
	JBG_WritePscd((UBYTE)((JBG_C_Register >> 11) & 0xff));
	JBG_IsFirstScd = 1;				/** 最初のＳＣＤ（出力しないようにするため） */
}


