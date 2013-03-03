/************************************************************************
*	System		: POPLAR
*	File Name	: SCDCPH.C
*	Author		: Y.Suzuki
*	Date		: 1997/6/10
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\syscph.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\lst_def.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sys_line.h"


 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "stdlib.h"
#include "stddef.h"
 #else
#include "f:\public\cc\shc\bin\stdlib.h"
#include "f:\public\cc\shc\bin\stddef.h"
 #endif


#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\define\cphpro.h"/*By Y.Suzuki 1998/02/18*/
#include "\src\cpu\sh7043_a\scd\define\alrpro.h"/*By Y.Suzuki 1998/03/11*/
#else
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\ext_v\cph_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\define\cphpro.h"/*By Y.Suzuki 1998/02/18*/
#include "\src\atlanta\scd\define\alrpro.h"/*By Y.Suzuki 1998/03/11*/
#endif

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/11/17 */
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/17 */
 #if defined(SATSUKI2) || defined(STOCKHM2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
  #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
   #include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
  #else
   #include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
  #endif
 #endif
#endif /* (PRO_MODEM == R288F) */


#include "\src\atlanta\ext_v\ncu_data.h"/*By Y.Suzuki 1998/06/08*/
#include "\src\atlanta\define\ncu_stat.h"/*By Y.Suzuki 1998/06/08*/

#if defined(SAKAKI)
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif

#if (0)/*By Y.Suzuki 1998/03/11*/
//extern void AlirooScramble (struct CipherTbl_t *);
//extern void AlirooDescramble (struct CipherTbl_t *);
#endif

extern int should_ask_cutting;
extern int	glb_err;

/*	By R.Cohen 1997/12/02	*/
extern int loc_slider;
extern int slider_size;

extern UWORD	tskno_SCN_DocumentStoreTask;
extern UWORD	tskno_OPR_KeyTimerTask;

#if (PRO_CIPHER == ENABLE)


/*************************************************************************
	module		:[cmをライン数に換算]
	function	:[
		1.サービスラベルのオフセットをｃｍからライン数に換算する
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/10/23]
	author		:[鈴木郁ニ]
*************************************************************************/
UWORD CmeterToLine(UBYTE size)
{
	UWORD ret_value;
	switch(CipherData.PageMode) {
	case SYS_NORMAL:
	/*	ret_value = (UWORD)((size * 39) + (size/2));By Y.Suzuki 1998/02/25 */
		ret_value = (UWORD)(size * 39);
		break;
	case SYS_FINE:
	case SYS_GRAY16:	/**	中間調16	*/
	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
	case SYS_GRAY32:	/**	中間調32	*/
	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
	case SYS_GRAY64:	/**	中間調64	*/
	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
	/*	ret_value = (UWORD)(size * 78);By Y.Suzuki 1998/02/25 */
		ret_value = (UWORD)(size * 77);
		break;
	}
	return(ret_value);
}


/*************************************************************************
	module		:[インチをライン数に換算]
	function	:[
		1.サービスラベルのオフセットをインチからライン数に換算する
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/10/23]
	author		:[鈴木郁ニ]
*************************************************************************/
UWORD InchToLine(UBYTE size)
{
	UWORD ret_value;
	switch(CipherData.PageMode) {
	case SYS_NORMAL:
		ret_value = (UWORD)(size * 10);
		break;
	case SYS_FINE:
	case SYS_GRAY16:	/**	中間調16	*/
	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
	case SYS_GRAY32:	/**	中間調32	*/
	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
	case SYS_GRAY64:	/**	中間調64	*/
	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
		ret_value = (UWORD)(size * 20);
		break;
	}
	return(ret_value);
}


/*************************************************************************
	module		:[暗号化エンコードで使用するローカル変数の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/6/11]
	author		:[鈴木郁二]
*************************************************************************/
void CipherEncodeInitial(void)
{
	CipherEncodeData.Coding = CipherStoreData.Code;
	switch(CipherData.PageType) {
	case SYS_DOCUMENT_A4_SIZE:
		CipherEncodeData.Img_Size = SYS_A4_LINE;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		CipherEncodeData.Img_Size = SYS_B4_LINE;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		CipherEncodeData.Img_Size = SYS_A3_LINE;
		break;
	}
/*	switch(CipherWriteMode) {*/
	switch(CipherData.PageMode) {
	case SYS_NORMAL:
		CipherEncodeData.K_Para = 2;
		break;
	case SYS_FINE:		/**	ファイン	*/
	case SYS_GRAY16:	/**	中間調16	*/
	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
	case SYS_GRAY32:	/**	中間調32	*/
	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
	case SYS_GRAY64:	/**	中間調64	*/
	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
		CipherEncodeData.K_Para = 4;
		break;
	case SYS_SFINE:		/**	Sファイン	*/
		CipherEncodeData.K_Para = 8;
		break;
	case SYS_HFINE:		/**	Hファイン	*/
		CipherEncodeData.K_Para = 8;
		CipherEncodeData.Img_Size *= 2;/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/01/10 */
		break;
	}
	CipherEncodeData.Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */

	/* 符号ライトポインタのセット */
	/* 蓄積符号化方式をＭＭＲ/ＭＲ */
	CipherEncodeData.Wp = &MemWp;
	/* メモリ書き込み先頭アドレスをセットすべき */
	CipherEncodeData.Wp->Buf = (UBYTE*)(MEM_CalculateSoftAddress(CipherExecWriteData.ExecBlockNo));
	CipherEncodeData.Wp->Adr = 0;
	CipherEncodeData.Wp->Bit = 1;
}


/*************************************************************************
	module		:[暗号化デコードで使用するローカル変数の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7041]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/6/11]
	author		:[鈴木郁二]
*************************************************************************/
void CipherDecodeInitial(void)
{
	/* 以下初期化追加 By Y.Suzuki 97/12/8 */
	SCD_DirectTx = 0;
	SCD_DirectRx = 0;
/*	CipherBegin = 0;*/
	CipherDecodeData.Coding = CipherReadCode;
/*	if(CipherReadSize == SYS_DOCUMENT_A4_SIZE) {*/
	if(CipherData.PageType == SYS_DOCUMENT_A4_SIZE) {
		CipherDecodeData.Img_Size = SYS_A4_LINE;
	}
/*	else if(CipherReadSize == SYS_DOCUMENT_B4_SIZE) {*/
	else if(CipherData.PageType == SYS_DOCUMENT_B4_SIZE) {
		CipherDecodeData.Img_Size = SYS_B4_LINE;
	}
/*	else if(CipherReadSize == SYS_DOCUMENT_A3_SIZE) {*/
	else if(CipherData.PageType == SYS_DOCUMENT_A3_SIZE) {
		CipherDecodeData.Img_Size = SYS_A3_LINE;
	}
/*	if (CipherReadMode == SYS_HFINE) {* ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/02/07 */
	if (CipherData.PageMode == SYS_HFINE) {/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/02/07 */
		CipherDecodeData.Img_Size *= 2;
	}
	CipherDecodeData.Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */
	/* 初期化 追加 王 96/1/23 */
	CipherDecodeData.DecData.Byte.H = 0;
	CipherDecodeData.DecData.Byte.L = 0;
	CipherDecodeData.DecBits = 0;

	/* 符号リードポインタのセット */
	CipherDecodeData.Rp = &MemRp;
	/* メモリ読み出し先頭アドレスをセットすべき */
	CipherDecodeData.Rp->Buf = (UBYTE*)(MEM_CalculateSoftAddress(CipherExecReadData.ExecBlockNo));
	CipherDecodeData.Rp->Adr = 0;
	CipherDecodeData.Rp->Bit = 1;
}

/*************************************************************************
	module		:[暗号化初期化]
	function	:[
		1.メモリリード・ライトオープン
		2.RLバッファ初期化
	]
	return		:[
					MEM_OK			:0
					MEM_INDEX_OVER	:0xFFFC
					MEM_BLOCK_OVER	:0xFFFE
					MEM_NO_INDEX	:0xFFFF
	]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/06/11]
	author		:[鈴木郁ニ]
*************************************************************************/
UWORD CipherInitial(void)
{
	UWORD result;
	struct WorkBuf_t *rl_buf_p;

	result = 0;/* OK */
	/* 以下の２つの変数は、暗号化／復元化タスク起動時にクリアが必要です。*/
	CipherReadPageNo++;	/* これから読み出すページ */
	CipherWritePageNo++;/* これから書込むページ */
	CipherData.ErrorCode = 0;

	/* 暗号化処理進捗率初期化 By Y.Suzuki 1997/12/04 */
	/*SYS_CipherPercent = 0;By Y.Suzuki 1998/05/27 */

	/* ALIROO FLAGクリア  */
	CipherData.Flags = SYB_MaintenanceSwitch[MNT_SW_F7];
	if(SYB_KeyBookData.NoiseRemovalOn)
		CipherData.Flags |= ARFL_NOISE_REMOVAL;

	/* For Debug	By Y.Suzuki 1997/11/02	*/
	SCD_DebugCopyOn = 0;
	SCD_DebugLineToLabel = 0;
	if (SYS_CipherComExec == SYS_DECIPHER_EXEC) {
		/* スクランブル受信原稿スクランブル解除の時 */
	/*	CipherReadIndex.No = SYS_DocumentPrintNo;* 受信ＮＯ．*/
		CipherReadIndex.BoxNumber = 0;
		CipherReadIndex.Page = CipherReadPageNo;
		CipherReadIndex.Item = SYS_MEM_CIPHER_RX_FILE;
		CipherStoreData.No = CipherReadIndex.No;
		CipherStoreData.BoxNumber = CipherReadIndex.BoxNumber;/* By Y.Suzuki 1998/05/09 */
		CipherStoreData.Page = CipherWritePageNo;
		CipherStoreData.Item = SYS_MEM_DECIPHER_FILE;
	/*	SYS_DocumentPrintNo = CipherReadIndex.No;By Y.Suzuki 1997/12/04 */
		CipherData.PageMode = MEM_CheckStoreMode(&CipherReadIndex);
	}
	else if (SYS_CipherComExec == SYS_TX_DOC_DECIPHER_EXEC) {
		/* スクランブル送信原稿スクランブル解除の時 */
	/*	CipherReadIndex.No = SYS_DocumentPrintNo;*/
		CipherReadIndex.BoxNumber = 0;
		CipherReadIndex.Page = CipherReadPageNo;
		CipherReadIndex.Item = SYS_MEM_TX_FILE;
		CipherStoreData.No = CipherReadIndex.No;
		CipherStoreData.BoxNumber = CipherReadIndex.BoxNumber;/* By Y.Suzuki 1998/05/09 */
		CipherStoreData.Page = CipherWritePageNo;
		CipherStoreData.Item = SYS_MEM_TX_DECIPHER_FILE;
	/*	SYS_DocumentPrintNo = CipherReadIndex.No;By Y.Suzuki 1997/12/04 */
		CipherData.PageMode = MEM_CheckStoreMode(&CipherReadIndex);
	}
	else {
		/* 暗号化の時 */
		/* CipherReadIndex は MAN_FromDocStore()でセットされる */
		CipherReadIndex.Page = CipherReadPageNo;/* ﾍﾟｰｼﾞのみここで再セット */
		CipherStoreData.No = CipherReadIndex.No;
		CipherStoreData.BoxNumber = CipherReadIndex.BoxNumber;/* By Y.Suzuki 1998/05/09 */
		CipherStoreData.Page = CipherWritePageNo;
		CipherStoreData.Item = SYS_MEM_TX_FILE;
		CipherData.PageMode = MEM_CheckStoreMode(&CipherReadIndex);
		/* Service label offset */
		/* ライン数に換算してセットする */
		CipherData.StartPageNo = CipherWritePageNo;/* By Y.Suzuki 97/11/05 */
		if (CipherWritePageNo < 2) {
			CipherData.OffsetServiceLabel = CmeterToLine(SYB_KeyBookData.OffsetServiceLabel);
		}
		else  {
			CipherData.OffsetServiceLabel = CmeterToLine(2);
		}

		/* For Debug	By Y.Suzuki 1997/11/02	*/
		SCD_DebugCopyOn = 0;
	}
	result = MEM_ReadOpen(&CipherReadIndex,&CipherExecReadData);
	if (result == MEM_NO_INDEX) {
		return(result);
	}
	/* スクランブル、デスクランブル対象ページ数初期化 By Y.Suzuki 97/10/30 */
	if (!(CipherData.PageNo)) {
		CipherData.PageNo = MEM_CountTotalPage(CipherReadIndex.Item, CipherReadIndex.No, MEM_IGNORE_BOX_NUMBER);
	}
	CipherReadCode = MEM_CheckStoreCode(&CipherReadIndex);
	CipherData.PageType = MEM_CheckStoreSize(&CipherReadIndex);
	CipherData.LineSize = MEM_CheckStoreLineCount(&CipherReadIndex);
/*この初期化は、スクランブルコマンドの開始で行なう /* By Y.Suzuki 97/10/24 */
/*	CipherData.PageNo = MEM_CountTotalPage(CipherReadIndex.Item, CipherReadIndex.No, MEM_IGNORE_BOX_NUMBER);*/
	if (SYB_MaintenanceSwitch[MNT_SW_F1] & ALIROO_MH_CODE) {
		CipherStoreData.Code = SYS_MH_CODE;
	}
	else if (SYB_MaintenanceSwitch[MNT_SW_F1] & ALIROO_MR_CODE) {
		CipherStoreData.Code = SYS_MR_CODE;
	}
	else {
		CipherStoreData.Code = CipherReadCode;
	}
	CipherStoreData.Mode = CipherData.PageMode;
	CipherStoreData.Size = CipherData.PageType;

	result = MEM_WriteOpen(&CipherStoreData,&CipherExecWriteData);
/*	if (result == MEM_NO_INDEX) [By Y.Suzuki 1998/08/25 */
	if (result != MEM_OK) {
		return(result);
	}

	if (!SYS_CipherInterruptionOn) {
		/*スクランブルオペレーション中に通信が始まった場合、ソフトコーデックの初期化をしない */
		CipherEncodeInitial();
		CipherDecodeInitial();

		SCD_NgRl = 0;		/*	By Y.Suzuki 1997/03/17	*/
		RL1.Cout = 0;
		RL1.Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*		RL1.Data = &RL_Buffer[RLBUF_CPH_ENC]; 新ﾏｽｸ変更 T.Nose */
		RL1.Data = RL_Buffer_p + RLBUF_CPH_ENC;
		rl_buf_p = &RL1;
		/* 全白イメージサイズをセットする */
		PutRL(rl_buf_p,CipherEncodeData.Img_Size,0);
		RL2.Cout = 0;
		RL2.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*		RL2.Data = &RL_Buffer[RLBUF_CPH_ENC + RLBUF_CPH_SIZE]; 新ﾏｽｸ変更 T.Nose */
		RL2.Data = RL_Buffer_p + RLBUF_CPH_ENC + RLBUF_CPH_SIZE;
		rl_buf_p = &RL2;
		/* 全白イメージサイズをセットする */
		PutRL(rl_buf_p,CipherEncodeData.Img_Size,0);
		RL3.Cout = 0;
		RL3.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*		RL3.Data = &RL_Buffer[RLBUF_CPH_DEC]; 新ﾏｽｸ変更 T.Nose */
		RL3.Data = RL_Buffer_p + RLBUF_CPH_DEC;
		rl_buf_p = &RL3;
		/* 全白イメージサイズをセットする */
		PutRL(rl_buf_p,CipherEncodeData.Img_Size,0);
		RL4.Cout = 0;
		RL4.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*		RL4.Data = &RL_Buffer[RLBUF_CPH_DEC + RLBUF_CPH_SIZE]; 新ﾏｽｸ変更 T.Nose */
		RL4.Data = RL_Buffer_p + RLBUF_CPH_DEC + RLBUF_CPH_SIZE;
		rl_buf_p = &RL4;
		/* 全白イメージサイズをセットする */
		PutRL(rl_buf_p,CipherEncodeData.Img_Size,0);

		EncodeA_buf = &RL1;
		EncodeB_buf = &RL2;
		DecodeA_buf = &RL3;
		DecodeB_buf = &RL4;
	}

	return(result);
}


/*******************************************************
    module		:[１ライン分のＲＬをイメージに変換する]
    fonction	:[]
    return		:[]
    common		:[]
    condition	:[フラッシュＲＯＭ]
    comment		:[]
    machine		:[SH7041]
    language	:[SHC]
    keyword		:[]
    date		:[1997/6/17]
    author		:[鈴木郁二]
********************************************************/
/*UBYTE SCD_Debug_Err_Img = 0;*/
/*UWORD SCD_Debug_Img_Size = 0;*/
void SCD1LineRlToImg(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{

	UWORD rl_a;			 							/** 走査線　run length */
	UWORD ImgCntr;									/** 走査線カウンタ */
	UBYTE SfitCntr;									/** ビット カウンタ */
	UWORD ImgBitCntr;								/** 1ライン走査線数カウンタ */
	UWORD BufCntr;									/** ＲＬ確認カウンタ */
	UBYTE ImgBufData;								/** イメージデータ バッファ */
	UBYTE ImgClor;									/** カラーデータ */
	UBYTE ImgbyteClor;								/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */


	point->Cout = 0;
	point->Flag = 0;
	SfitCntr = 0;
	ImgBitCntr = 0;
	ImgCntr = 0;
	ImgBufData = 0;
	ImgClor = 0;
	ImgbyteClor = 0x00;

	/*SCD_Debug_Img_Size = 0;*/

	do 	{
	    rl_a = GetRL(point);							/** run length バッファ から ＲＬを取り出す */

	/*	SCD_Debug_Img_Size += rl_a;*/

#if (0)/* By Y.Suzuki 1998/04/17 */
//		if (!(ImgBitCntr % 500)) {
//			wai_oneshot(1);
//		}
#endif
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
			if (rl_a >= 8){
				do {

#if (0)
** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** 					Img_Buffer1[line][ImgCntr] = ImgbyteClor;
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
#else
					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
#endif
#endif

				/*	AlirooTestData -> Img_Buffer[line][ImgCntr] = ImgbyteClor;*/
				/*	*(Img_Buffer[line][ImgCntr]) = ImgbyteClor;*/
					ImgCntr++;
					rl_a -= 8;
					ImgBitCntr += 8;
				} while (rl_a >= 8);
				ImgBufData = 0;
			}
		}
		if (rl_a != 0) {
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
												 	/** RL からイメージに変換 */
				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
				SfitCntr++;							/** ビット カウンタ 更新 */

				if (SfitCntr == 8){

#if (0)
** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
					Img_Buffer1[line][ImgCntr]=ImgBufData;
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
#else
					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
#endif
#endif

				/*	AlirooTestData -> Img_Buffer[line][ImgCntr]=ImgBufData;*/
				/*	*(Img_Buffer[line][ImgCntr])=ImgBufData;*/
													/** ＳＲＡＭにイメージ データ書き込み */
					ImgCntr++;
					SfitCntr=0;						/** ビット  カウンタ = 0 */
					ImgBufData = 0;
				}
				else {
					ImgBufData <<= 1;
				}
			}

		}

		ImgClor = (UBYTE)(ImgClor ^ 0x01);
		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
	} while (scdcp->Img_Size > ImgBitCntr);			/** 1ライン終了か ？ */
/*	if (scdcp->Img_Size != ImgBitCntr) {
//		SCD_Debug_Err_Img |= 1;
//	}*/
	return;

}


/********************************************************
	module		:[１ライン分のイメージをＲＬに変換する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7041]
	language	:[SHC]
	keyword		:[]
	date		:[[1997/6/17]
	author		:[鈴木郁二]
*********************************************************/
void SCD1LineImgToRl(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{

	UWORD rl_data;
	UWORD BufCntr;									/** １ラインバイト数カウンタ */
	UBYTE col_flag;
	UBYTE ImgBufData;								/** カラーデータ */
	UBYTE SfitCntr;									/** ８ ビットシフトカウンタ */
	UWORD buf_max;									/* 1ラインＭＡＸバイト数 */
	UWORD rl_cnt;

	rl_data = 0;										/** ＲＬ　データ */
	col_flag = 0;										/** ０＝白，１＝黒 */
	point->Cout = 0;
	point->Flag = 0;
	rl_cnt = 0;
	buf_max = ((scdcp->Img_Size)/8);

	SfitCntr = 8;
	rl_data = 0;
	col_flag = WHITE;

	for (BufCntr = 0; BufCntr != buf_max; BufCntr++){
		ImgBufData = Img_Buffer2[line][BufCntr];/* 本番一回に１ラインのみ符号化 */
	/*	ImgBufData = CipherP -> Img_Buffer1[line][BufCntr];* デバック用 */

		if (!(BufCntr % 50)) {
		/*	wai_oneshot(1); By Y.Suzuki 97/10/29 */
		}

		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
		if (ImgBufData == 0x00){
			if (col_flag == WHITE) {
				rl_data += SfitCntr;
			}
			else {
				if ((point->Cout != 0) && !rl_data) {
					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
				}
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = WHITE;
			}
		}
		else if (ImgBufData == 0xff){
			if (col_flag == BLACK){
				rl_data += SfitCntr;
			}
			else {
				if ((point->Cout != 0) && !rl_data) {
					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
				}
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = BLACK;
			}
		}
		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */

		else {

 			do {
				if ((ImgBufData & 0x80) == WHITE) {		/* 白 ? */
					if (col_flag == WHITE) {
						rl_data++;
					}
					else {
						if ((point->Cout != 0) && !rl_data) {
							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
						}
						PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
						rl_cnt += rl_data;
						rl_data = 1;
						col_flag = WHITE;
					}
				}
				else {
					if (col_flag == BLACK) {
						rl_data++;
					}
					else {
						rl_cnt += rl_data;
						if ((point->Cout != 0) && !rl_data) {
							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
						}
						PutRL(point,rl_data,col_flag);
						rl_data = 1;
						col_flag = BLACK;
					}
				}
				ImgBufData <<= 1;
				SfitCntr--;
			} while (SfitCntr != 0);

		}
		SfitCntr = 8;
	}
	if (rl_data > 0) {
		rl_cnt += rl_data;
		PutRL(point,rl_data,col_flag);
	}
/*	if (scdcp->Img_Size != rl_cnt) {
//		SCD_Debug_Err_Img |= 0x80;
//	}*/
	return;
}


#if (0)
** /* 以下の関数は、基本的にはスクランブルとは、なんら関係が無いので、
** ** 標準で内蔵ＲＯＭ内に入れておきます。
** ** By O.Kimoto 1998/10/21
** */
** /*******************************************************
**     module		:[１ライン分のＲＬをイメージに変換する]
**     fonction	:[]
**     return		:[]
**     common		:[]
**     condition	:[内蔵ＲＯＭ]
**     comment		:[]
**     machine		:[SH7041]
**     language	:[SHC]
**     keyword		:[]
**     date		:[1997/6/17]
**     author		:[鈴木郁二]
** ********************************************************/
** #pragma section SCD /* locate section name "CMEMMTBL" */
** void SCD1LineRlToImgIntRom(struct WorkBuf_t *point,
** 					struct CdcBlk_t *scdcp,
** 					UWORD line)
** {
** 
** 	UWORD rl_a;			 							/** 走査線　run length */
** 	UWORD ImgCntr;									/** 走査線カウンタ */
** 	UBYTE SfitCntr;									/** ビット カウンタ */
** 	UWORD ImgBitCntr;								/** 1ライン走査線数カウンタ */
** 	UWORD BufCntr;									/** ＲＬ確認カウンタ */
** 	UBYTE ImgBufData;								/** イメージデータ バッファ */
** 	UBYTE ImgClor;									/** カラーデータ */
** 	UBYTE ImgbyteClor;								/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
** 
** 
** 	point->Cout = 0;
** 	point->Flag = 0;
** 	SfitCntr = 0;
** 	ImgBitCntr = 0;
** 	ImgCntr = 0;
** 	ImgBufData = 0;
** 	ImgClor = 0;
** 	ImgbyteClor = 0x00;
** 
** 	/*SCD_Debug_Img_Size = 0;*/
** 
** 	do 	{
** 	    rl_a = GetRL(point);							/** run length バッファ から ＲＬを取り出す */
** 
** 	/*	SCD_Debug_Img_Size += rl_a;*/
** 
** #if (0)/* By Y.Suzuki 1998/04/17 */
** //		if (!(ImgBitCntr % 500)) {
** //			wai_oneshot(1);
** //		}
** #endif
** 		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
** 		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
** 			if (rl_a >= 8){
** 				do {
** 
** #if (0)
** ** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** ** 					Img_Buffer1[line][ImgCntr] = ImgbyteClor;
** #else
** #if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
** **					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
** #else
** 					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
** #endif
** #endif
** 
** 				/*	AlirooTestData -> Img_Buffer[line][ImgCntr] = ImgbyteClor;*/
** 				/*	*(Img_Buffer[line][ImgCntr]) = ImgbyteClor;*/
** 					ImgCntr++;
** 					rl_a -= 8;
** 					ImgBitCntr += 8;
** 				} while (rl_a >= 8);
** 				ImgBufData = 0;
** 			}
** 		}
** 		if (rl_a != 0) {
** 		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
** 			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
** 												 	/** RL からイメージに変換 */
** 				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
** 				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
** 				SfitCntr++;							/** ビット カウンタ 更新 */
** 
** 				if (SfitCntr == 8){
** 
** #if (0)
** ** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** ** 					Img_Buffer1[line][ImgCntr]=ImgBufData;
** #else
** #if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
** ** 					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
** #else
** 					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
** #endif
** #endif
** 
** 				/*	AlirooTestData -> Img_Buffer[line][ImgCntr]=ImgBufData;*/
** 				/*	*(Img_Buffer[line][ImgCntr])=ImgBufData;*/
** 													/** ＳＲＡＭにイメージ データ書き込み */
** 					ImgCntr++;
** 					SfitCntr=0;						/** ビット  カウンタ = 0 */
** 					ImgBufData = 0;
** 				}
** 				else {
** 					ImgBufData <<= 1;
** 				}
** 			}
** 
** 		}
** 
** 		ImgClor = (UBYTE)(ImgClor ^ 0x01);
** 		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
** 	} while (scdcp->Img_Size > ImgBitCntr);			/** 1ライン終了か ？ */
** #if (0)
** //	if (scdcp->Img_Size != ImgBitCntr) {
** //		SCD_Debug_Err_Img |= 1;
** //	}
** #endif
** 	return;
** 
** }
** 
** 
** 
** /********************************************************
** 	module		:[１ライン分のイメージをＲＬに変換する]
** 	function	:[]
** 	return		:[]
** 	common		:[]
** 	condition	:[内蔵ＲＯＭ]
** 	comment		:[]
** 	machine		:[SH7041]
** 	language	:[SHC]
** 	keyword		:[]
** 	date		:[[1997/6/17]
** 	author		:[鈴木郁二]
** *********************************************************/
** void SCD1LineImgToRlIntRom(struct WorkBuf_t *point,
** 					struct CdcBlk_t *scdcp,
** 					UWORD line)
** {
** 
** 	UWORD rl_data;
** 	UWORD BufCntr;									/** １ラインバイト数カウンタ */
** 	UBYTE col_flag;
** 	UBYTE ImgBufData;								/** カラーデータ */
** 	UBYTE SfitCntr;									/** ８ ビットシフトカウンタ */
** 	UWORD buf_max;									/* 1ラインＭＡＸバイト数 */
** 	UWORD rl_cnt;
** 
** 	rl_data = 0;										/** ＲＬ　データ */
** 	col_flag = 0;										/** ０＝白，１＝黒 */
** 	point->Cout = 0;
** 	point->Flag = 0;
** 	rl_cnt = 0;
** 	buf_max = ((scdcp->Img_Size)/8);
** 
** 	SfitCntr = 8;
** 	rl_data = 0;
** 	col_flag = WHITE;
** 
** 	for (BufCntr = 0; BufCntr != buf_max; BufCntr++){
** 
** #if (0)
** ** 		/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** ** 		ImgBufData = Img_Buffer2[line][BufCntr];/* 本番一回に１ラインのみ符号化 */
** #else
** 		ImgBufData = *(img_buffer2 + (UDWORD)(line * SCD_LINE_BUF2_WIDTH) + (UDWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
** #endif
** 
** 	/*	ImgBufData = CipherP -> Img_Buffer1[line][BufCntr];* デバック用 */
** 
** 		if (!(BufCntr % 50)) {
** 		/*	wai_oneshot(1); By Y.Suzuki 97/10/29 */
** 		}
** 
** 		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
** 		if (ImgBufData == 0x00){
** 			if (col_flag == WHITE) {
** 				rl_data += SfitCntr;
** 			}
** 			else {
** #if (0)
** //				if ((point->Cout != 0) && !rl_data) {
** //					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //				}
** #endif
** 				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 				rl_cnt += rl_data;
** 				rl_data = 8;
** 				col_flag = WHITE;
** 			}
** 		}
** 		else if (ImgBufData == 0xff){
** 			if (col_flag == BLACK){
** 				rl_data += SfitCntr;
** 			}
** 			else {
** #if (0)
** //				if ((point->Cout != 0) && !rl_data) {
** //					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //				}
** #endif
** 				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 				rl_cnt += rl_data;
** 				rl_data = 8;
** 				col_flag = BLACK;
** 			}
** 		}
** 		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
** 
** 		else {
** 
**  			do {
** 				if ((ImgBufData & 0x80) == WHITE) {		/* 白 ? */
** 					if (col_flag == WHITE) {
** 						rl_data++;
** 					}
** 					else {
** #if (0)
** //						if ((point->Cout != 0) && !rl_data) {
** //							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //						}
** #endif
** 						PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 						rl_cnt += rl_data;
** 						rl_data = 1;
** 						col_flag = WHITE;
** 					}
** 				}
** 				else {
** 					if (col_flag == BLACK) {
** 						rl_data++;
** 					}
** 					else {
** 						rl_cnt += rl_data;
** #if (0)
** //						if ((point->Cout != 0) && !rl_data) {
** //							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //						}
** #endif
** 						PutRL(point,rl_data,col_flag);
** 						rl_data = 1;
** 						col_flag = BLACK;
** 					}
** 				}
** 				ImgBufData <<= 1;
** 				SfitCntr--;
** 			} while (SfitCntr != 0);
** 
** 		}
** 		SfitCntr = 8;
** 	}
** 	if (rl_data > 0) {
** 		rl_cnt += rl_data;
** 		PutRL(point,rl_data,col_flag);
** 	}
** #if (0)
** //	if (scdcp->Img_Size != rl_cnt) {
** //		SCD_Debug_Err_Img |= 0x80;
** //	}
** #endif
** 	return;
** }
** #pragma section /* locate section name "PSCD" */
#endif

/*	condition	:[フラッシュＲＯＭ] */
void CopyImg2ToImg1(UWORD line)
{
	/* Img_Buffer2[0][256] --> Img_Buffer1[line][256] */
	UWORD byte_cnt;

	for(byte_cnt=0; byte_cnt<SCD_LINE_BYTE_SIZE  ; byte_cnt++) {
		Img_Buffer1[line][byte_cnt] = Img_Buffer2[0][byte_cnt];
	}
}


/* 新ﾏｽｸ変更 */
/* show_sliderFlsRom で参照 */
/*	static int i;*/
	static UBYTE i;/*	By Y.Suzuki 1997/11/17	*/

/*************************************************************************
	module		:[暗号化エンコード]
	function	:[
		1.アリロ暗号化／復元化タスクからコールされる
		2.指定ライン数をビットマップからＭＭＲにエンコードする
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/06/10]
	author		:[鈴木郁ニ]
*************************************************************************/
#pragma section SCDALR /* locate section name "PSCDALR" */
UBYTE CipherEncFlsRom(UWORD line)
/*UBYTE CipherEncode(UWORD line) By Y.Suzuki 1998/02/18 */
{
	struct WorkBuf_t *tmp;
	UWORD line_cnt;
	WORD mem_status;

	line_cnt = 0;
	MemoryExecData = CipherExecWriteData;
	do {
		if (SCD_DebugCopyOn) {		/*	By Y.Suzuki 1997/11/02	*/
			CopyImg2ToImg1(SCD_DebugLineToLabel);
			SCD_DebugLineToLabel++;
		}
	/*	Fast1LineImgToRl(EncodeA_buf,&CipherEncodeData,line_cnt);*/
		if (SYB_MaintenanceSwitch[MNT_SW_E1] & FAST_RL_IMG) {
			Fast1LineImgToRl(EncodeA_buf,&CipherEncodeData,line_cnt);
		}
		else {
			SCD1LineImgToRl(EncodeA_buf,&CipherEncodeData,line_cnt);
		}
		mem_status = Mem_Encode(&CipherEncodeData,EncodeA_buf,EncodeB_buf);
		if(SCD_DBG_PMODE == 5) {
			SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
		}
		if(SCD_DBG_ENC_RLSIZE == 1) {
			SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
		}
		if(SCD_DBG_ENC_RLSIZE == 3) {
			SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
		}
		if(mem_status == RX_MEM_OVER) {
			return(SCD_MEMORY_OVER);
		}
		tmp = EncodeA_buf;
		EncodeA_buf = EncodeB_buf;
		EncodeB_buf = tmp;
		line--;
		line_cnt++;
	}while(line);
	CipherExecWriteData = MemoryExecData;
	/* ページエンドの場合ここでＲＴＣを入れる */
	/* mem_status = WriteRtcToMem(&CipherEncodeData); */
	if(mem_status == RX_MEM_OVER) {
		return(SCD_MEMORY_OVER);	/*	1	*/
	}
	return(SCD_ENCODE_OK);	/*	0	*/
}


/*************************************************************************
	module		:[サービスラベル作成]
	function	:[
		1.フォントとしては、16ライン＊３準備する
		2.実際は、上下のヨコ罫線部のフォントは、4ライン分しか使わない
		3.計 ４＋１６＋４の24ライン（ノーマル）となる。
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/07/23]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE WriteLabelFlsRom(void)
/*UBYTE WriteLabel(void)By Y.Suzuki 1998/02/18 */
{
	/* int		header;*/
	UBYTE	i, j, mode_cnt;
	/*struct	SYS_DocBlockData_t	*docp;*/
	struct	WorkBuf_t	*tmp;
	UBYTE	buf_cnt;
	UBYTE	start_line;
	UBYTE	end_line;
	WORD	result;

	result = 0;
/*	docp = &SYS_DocBlock;By Y.Suzuki 1997/12/02 */
	if (CipherData.PageMode == SYS_NORMAL) {
		mode_cnt = 1;
	}
	else if ((CipherData.PageMode == SYS_HFINE) || (CipherData.PageMode == SYS_SFINE)) {
		mode_cnt = 4;
	}
	else {	/* docp->dst.d_mode == FINE or GREY */
		mode_cnt = 2;
	}
	/* header スペースは、Img2Rl内で原稿幅に見合った値をセットする */

	/* スクランブル用インデックスデータを SCD で参照しているインデックスデータにコピー By Y.Suzuki 1998/02/24 */
	MemoryExecData = CipherExecWriteData;

	for (buf_cnt = 1; buf_cnt < 4; buf_cnt++) {
		LST_SetCipher_Image(buf_cnt, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);/* サービスラベルイメージをセット */
		EncodeB_buf->Cout = 0;
		if (CipherEncodeData.Line_Cntr == 0) { /* ページの先頭にサービスラベルを書く場合のみ */
			if (CipherData.PageType == SYS_DOCUMENT_A4_SIZE) {
				if (CipherData.PageMode == SYS_HFINE){
					PutRL(EncodeB_buf,SYS_A4_LINE*2,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/03/22	*/
				}
				else {
					PutRL(EncodeB_buf,SYS_A4_LINE,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/01/18	*/
				}
			}
			else if (CipherData.PageType == SYS_DOCUMENT_B4_SIZE) {
				if (CipherData.PageMode == SYS_HFINE){
					PutRL(EncodeB_buf,SYS_B4_LINE*2,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/03/22	*/
				}
				else {
					PutRL(EncodeB_buf,SYS_B4_LINE,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/01/18	*/
				}
			}
			else {
				if (CipherData.PageMode == SYS_HFINE){
					PutRL(EncodeB_buf,SYS_A3_LINE*2,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/03/22	*/
				}
				else {
					PutRL(EncodeB_buf,SYS_A3_LINE,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/01/18	*/
				}
			}
		}
		if (buf_cnt == 1) {/* 上部罫線部 */
			start_line = 6;
			end_line = 10;
		}
		else if(buf_cnt == 2) {/* ラベル部 */
			start_line = 0;
			end_line = 16;
		}
		else {/* 下部罫線部 */
			start_line = 6;
			end_line = 10;
		}

		for(i = start_line; i < end_line; i++) {
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],EncodeA_buf,CipherData.PageType);
			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],DecodeB_buf,CipherData.PageType);
			/** 1ラインエンコード */
			result = Mem_Encode(&CipherEncodeData, EncodeA_buf, EncodeB_buf);/* EncodeA_buf(符号化ライン)､EncodeB_buf(参照ライン) */
			if (result == RX_MEM_OVER) {
				return(SCD_MEMORY_OVER);/* 1 */
			}
			if(SCD_DBG_PMODE == 5) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
			}
			if(SCD_DBG_ENC_RLSIZE == 1) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
			}
			if(SCD_DBG_ENC_RLSIZE == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
			}
			for (j=1; j<mode_cnt; j++) {
				result = Mem_Encode(&CipherEncodeData, EncodeA_buf,DecodeB_buf);
				if (result == RX_MEM_OVER) {
					return(SCD_MEMORY_OVER);/* 1 */
				}
				if(SCD_DBG_PMODE == 5) {
					SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
				}
				if(SCD_DBG_ENC_RLSIZE == 1) {
					SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
				}
				if(SCD_DBG_ENC_RLSIZE == 3) {
					SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
				}
			}
			tmp = EncodeB_buf;
			EncodeB_buf = EncodeA_buf;
			EncodeA_buf = tmp;	/* 符号化ライン→参照ライン */
		}
	}
	/* For Debug	By Y.Suzuki 1997/11/02	*/
	SCD_DebugCopyOn = 0;

	/* SCDで参照更新したインデックスデータをスクランブル用インデックスデータへ復帰 By Y.Suzuki 1998/02/24 */
	CipherExecWriteData = MemoryExecData;
	return(SCD_ENCODE_OK);	/*	0	*/
}

/*
	This functions is called by the scrambler when found that header separator is cutting some data

	return 1 to stop scrambling, 0 to continue
	should_ask_cutting: set to 0 if don't want to ask for the next pages of this document only
*/

/*	condition	:[フラッシュＲＯＭ] */
int CuttingHeaderFlsRom(void)
/*int CuttingHeader(void)By Y.Suzuki 1998/02/18 */
{
	if (CipherData.Flags & ARFL_CHECK_SEPARATOR) {
		/* add murata handling here */
	}
	else {
		should_ask_cutting = 0;
	}
	return 0;
}

/*
	This function is called by the descrambler when found that descrambling with the wrong key.
	You can ask the user whether he wants to continue anyway (on rare occasions when the page is
	very distorted this function is called wrongfully)
	To stop descrambling set glb_err to 9999 The process will return
	with error code ARVL_CANCEL
*/

/*	condition	:[フラッシュＲＯＭ] */
void IncorrectKeyFlsRom(void)
/*void IncorrectKey(void)By Y.Suzuki 1998/02/18 */
{
	MESSAGE_t	*MessageControl;
	UBYTE result;/*By Y.Suzuki 1998/07/31*/
	if (CipherData.Flags & ARFL_CHECK_VALID_KEY) {
		/* 複数ページデスクランブル原稿がある場合最終ページでのみ継続オペレーションを出す */
		/* By Suzuki 98/4/14 */
		if ((CipherReadPageNo == CipherData.PageNo) || ((SYS_CipherComExec == SYS_DECIPHER_EXEC) && (CipherReadPageNo == 1)
			 && (SYB_MaintenanceSwitch[MNT_SW_E1] & ALIROO_PRT_START_ON))) {
			/*	全ページ終了または、スクランブル受信解除時の1ページ目終了時	*/
			/* スクランブル解除時のスクランブル原稿消去ＯＰＲのため1ページ目をプリントアウトする
			   仕様が追加されたため1ページ目の最後でもキー間違いＯＰＲを行なう By Y.Suzuki 1998/07/10 */
			/* デスクランブル処理継続するならば、glb_errをクリアする */
			glb_err = 9999;

			/*最終ページでキー間違いとなった場合でスクランブル原稿消去の場合ここで消去しておく By Y.Suzuki 1998/07/31*/
			if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC) {
				result = MEM_ClearPageAndFATArea(&CipherReadIndex);
				/*スクランブル解除完了後、受信原稿自動消去の場合*/
				/*スクランブル受信原稿ボックス受信なしにする。By Y.Suzuki 1998/08/12*/
				SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
			}

			/*	メインでマシンステータスオンさせる	*/
			CipherMessage.Message = MSG_OPT_DECIPHER_KEY_ERROR;
			snd_msg(mbxno.MAN_Task, &CipherMessage);

			/* メインからデスクランブル継続･中止のメッセージ待ち By Y.Suzuki 1997/12/05 */
			rcv_msg(mbxno.SCD_CipherResult, &MessageControl);
			if (MessageControl->Message == MSG_OPT_DECIPHER_FROM_OPR) {
				if (MessageControl->SubMessage1) {
					/* デスクランブル継続 */
					glb_err = 0;
				}
			}
		}
		else {
			glb_err = 0;
		}
	}
}


/*
	This functions gets called periodically for misc. functionality
	(progress bar, switch to other tasks etc.)
*/

/*	condition	:[フラッシュＲＯＭ] */
void show_sliderFlsRom (int relative, int val)
/*void show_slider (int relative, int val) By Y.Suzuki 1998/02/18 */
{
	int	percent;

	/* タスクスイッチング時間を自動調節する */
	UBYTE print_on;
	UBYTE scan_on;
	UBYTE panel_on;
	UBYTE called_cnt;
/*	UBYTE wait_ms;By Y.Suzuki 1998/04/15 */
	UWORD wait_ms;

	print_on = 0;
	scan_on= 0;
	panel_on = 0;

/* ＳＴＯＰキーの処理を入れる */
	if (CipherStopOn) {/* SYS_Machinestatus はできたら参照したくない */
		CipherMessage.Message = MSG_OPT_CIPHER_STOPON;
		snd_msg(mbxno.MAN_Task, &CipherMessage);	/*	エンコード開始メッセージ送信	*/
	}
	i++;
#if (0)/*By Y.Suzuki 1998/07/22*/
//	if (SYS_DocumentPrintItem != SYS_MEM_DECIPHER_FILE) {
//		/*スクランブル解除プリント中は、デスクランブルタスクを止めない。By Y.Suzuki 1998/07/03*/
//		print_on = CMN_CheckPrinting();
//	}
//	else if ((SYS_DocumentPrintItem == SYS_MEM_DECIPHER_FILE) && (SYS_DocumentPrintPageNo == 1)) {
//		/*スクランブル解除プリント中でも１ページ目の場合は、デスクランブルを止めて１ﾍﾟｰｼﾞ目をプリントする By Y.Suzuki 1998/07/03 */
//		/* ２ﾍﾟｰｼﾞ目以降は、スクランブル解除処理終了後プリントする。*/
//		if (!(SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DISPLAY_DESCRAMBLE)) {
//			/*1ﾍﾟｰｼﾞ目プリントアウト*/
//			print_on = CMN_CheckPrinting();
//		}
//	}
#endif
	print_on = CMN_CheckPrinting();

	if (tskno_SCN_DocumentStoreTask != 0xFFFF) {
		scan_on = 1;
	}
	else {
		scan_on = 0;
	}
	panel_on = CMN_CheckPanelBusy();
/*	if ((print_on == 1) && (scan_on == 1)) {By Y.Suzuki 1998/04/28 */
	if ((print_on == 1) && (scan_on == 1)) {
	/* al100が通信中を追加 By Y.Suzuki 1998/04/28 */
	/*	called_cnt = 3;By Y.Suzuki 1998/04/09 */
		called_cnt = 1;
	/*	wait_ms = 10;By Y.Suzuki 1998/03/04 */
	/*	wait_ms = 12;By Y.Suzuki 1998/04/09 */
		wait_ms = 512;
	}
	else if ((print_on == 1) || (scan_on == 1)) {
	/*	called_cnt = 3;By Y.Suzuki 1998/04/09 */
		called_cnt = 1;
	/*	wait_ms = 7;By Y.Suzuki 1998/03/04 */
	/*	wait_ms = 10;By Y.Suzuki 1998/04/09 */
		wait_ms = 320;
	}
	else if ((SYS_OptionLineStatus[OtherLineNo] & SYS_OPTION_LINE_BUSY) && (OtherLineNo != 0xff)) {
		called_cnt = 1;
		wait_ms = 150;
	}
	else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {
		/* CLASS1動作中 By Y.Suzuki 1998/07/15 */
		called_cnt = 1;
		wait_ms = 150;
	}

	else {
		if (panel_on) {
			called_cnt = 5;
		/*	wait_ms = 7;By Y.Suzuki 1998/03/04 */
		/*	wait_ms = 10;By Y.Suzuki 1998/04/15 */
			wait_ms = 50;
/*			called_cnt = 10;
 *			wait_ms = 3; By Y.Suzuki 1998/03/03 */
		}
		else {
			called_cnt = 10;
			wait_ms = 3;
		}
	}
/*	if (i > 9) {By Y.Suzuki 1997/12/21 *
	*	wai_tsk(1);By Y.Suzuki 1997/12/08
	*	wai_tsk(7);By Y.Suzuki 1997/12/21 */
#if (0)/*メインに表示用メッセージをなげてからタスクスイッチする */
//	if (i > 5) {
//		wai_tsk(7);
//		i = 0;
//	}
#endif
	/* 以下 By R.Cohen 1997/12/02 */
	if (!slider_size) return;

	if (relative)  loc_slider += val;
    else           loc_slider  = val;

	percent = (int) ((long)loc_slider * slider_size / MAX_SLIDER);
    if ( percent > slider_size)  percent = slider_size;

    percent *= (100/slider_size);
    /* percent holds value between 0-100 showing percent of scrambling/descrambling done */
#if (0)/*By Y.Suzuki 1998/05/27*/
//	if (SYS_CipherPercent < (UBYTE)percent) {
//		SYS_CipherPercent = (UBYTE)percent;/* By Y.Suzuki 1997/12/03 */
//		CipherMessage.Message = MSG_DISPLAY_IDLE;
//		snd_msg(mbxno.MAN_Task, &CipherMessage);
//	}
#endif
	if (i > called_cnt) {
		wai_tsk(wait_ms);
		i = 0;
	}
}

/*
	This function gets called before page is turned up side down
	to notify user
*/
/*	condition	:[フラッシュＲＯＭ] */
void notifyUpDownFlsRom(void)
/*void notify_upside_down(void) By Y.Suzuki 1998/02/18 */
{
}



/*************************************************************************
	module		:[スクランブル用ダミールーチン]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/10/21]
	author		:[鈴木郁ニ]
*************************************************************************/
void	CphEncStartFlsRom(void){}
void	CphEncEndFlsRom(void){}
void	CphDecStartFlsRom(void){}
void	CphDecEndFlsRom(void){}
/*void	CipherEncodeStart(void){}*/
/*void	CipherEncodeEnd(void){}*/
/*void	CipherDecodeStart(void){}*/
/*void	CipherDecodeEnd(void){}*/

#pragma section /* locate section name "PSCDALR" */


/*************************************************************************
	module		:[暗号化デコード]
	function	:[
		1.アリロ暗号化／復元化タスクからコールされる
		2.指定ライン数をＭＭＲからビットマップにデコードする
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/06/10]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE CipherDecode(UWORD line)
{
	UWORD result;
	struct WorkBuf_t *tmp;
	WORD	status;
	UWORD	line_cnt;

	line_cnt = 0;
#if(0)
	if (CipherBegin) {/**	ページごとの初期化	*/
	/*	CipherDecodeInitial();*/
	/*	CipherEncodeInitial();*/
	/*		result = CipherInitial();*/
		if (result != MEM_OK) {
			if ((result == MEM_INDEX_OVER) || (result == MEM_BLOCK_OVER)) {
				return(SCD_MEMORY_OVER);
			}
			else {
				return(SCD_NO_INDEX);
			}
		}
		EncodeA_buf = &RL1;
		EncodeB_buf = &RL2;
		DecodeA_buf = &RL3;
		DecodeB_buf = &RL4;
	}
#endif
	MemoryExecData = CipherExecReadData;
	do {
		tmp = DecodeA_buf;
		DecodeA_buf = DecodeB_buf;
		DecodeB_buf = tmp;
		status = Mem_Decode(&CipherDecodeData,DecodeA_buf,DecodeB_buf);
		if(SCD_DBG_RLOVER == 2) {
			SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x04;
		}
	/*	if ((status == TX_MEM_ERR) && (SYS_DocBlock.Src.Code == SYS_MMR_CODE)) By Y.Suzuki 1997/12/02 */
		if ((status == TX_MEM_ERR) && (CipherReadCode == SYS_MMR_CODE)) {
			CodecPageStatus = CDC_DECODE_ERROR;
		/*	ScdcErrFlag = 1;*/
			status = RTC;	/*	14	*/
			return(SCD_DECODE_NG);	/*	4	*/
		}
		if (status == RTC) {
			return(RTC);
		}
		if (CipherStopOn) {/* １ラインごとにストップキーの入力をﾁｪｯｸする By Y.Suzuki 1998/04/12 */
			return(SCD_DECODE_OK);	/*	0	*/
		}
		show_slider(1,0);/*By Y.Suzuki 1998/04/15*/
		/** ＲＬをビットマップに展開する */
	/*	Fast1LineRlToImg(DecodeA_buf,&CipherDecodeData,line_cnt);By Y.Suzuki 980305 */
		if (SYB_MaintenanceSwitch[MNT_SW_E1] & FAST_RL_IMG) {
			Fast1LineRlToImg(DecodeA_buf,&CipherDecodeData,line_cnt);
		}
		else {
			SCD1LineRlToImg(DecodeA_buf,&CipherDecodeData,line_cnt);
		}
		line_cnt++;
		/* タスクスイッチング 必要 */
		line--;
	}while(0 < line);
	CipherExecReadData = MemoryExecData;
	return(SCD_DECODE_OK);	/*	0	*/
}

/*************************************************************************
	module		:[ライブラリ関数ｍａｌｌｏｃの使用する関数]
	function	:[
		1.
	]
	return		:[割り付けた領域の先頭アドレス]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/09/10]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE *sbrk(UDWORD size)
{
	UBYTE *ptr;
	/* アンズＬにスクランブルを入れる場合、MEM_StoreAreaのアドレスが必ずしも蓄積開始アドレスになるとはかぎらない */
	if ((brk + size) > (HeapArea.MEM_StoreArea + MEM_SCRAMBLE_INTERNAL_BLOCK * MEM_BLOCK_SIZE)) {
		/* 空き領域なし */
		return(UBYTE *)-1;
	}
	ptr = brk;
	brk += size;
	return(ptr);
}


/*	condition	:[フラッシュＲＯＭ] */
void CopyImg1ToImg2(UWORD line)
{
	/* Img_Buffer1[linen][256] --> Img_Buffer2[0][256] */
	UWORD byte_cnt;

	for(byte_cnt=0; byte_cnt<SCD_LINE_BYTE_SIZE  ; byte_cnt++) {
		Img_Buffer2[0][byte_cnt] = Img_Buffer1[line][byte_cnt];
	}
}

/*	condition	:[フラッシュＲＯＭ] */
void MML_CipherDebug2(void)
{
/*#if (0) このモジュールを使用する時は、このコメントをはずすこと */
	UBYTE result;
	/* malloc Test */
	void * ret;
	size_t size;/* size_t = UDWORD */
#if (0)/*	By Y.Suzuki 1997/12/02	*/
**	WORD rand_data1;
**	WORD rand_data2;
**	WORD rand_data3;
**	WORD rand_data4;
**	UWORD seed;
#endif
	UWORD enc_line_cnt;
	UWORD enc_max_line;

	/* freeptr = 0;		By Y.Suzuki 1997/10/08	*/

#if (0) /*	By Y.Suzuki 1997/12/25	*/
	size = 100;
	ret = malloc(size);
	if (ret == NULL) {
		result = SCD_MEMORY_OVER;
		return;
	}
	free(ret);
	size = 1000;
	ret = malloc(size);
	if (ret == NULL) {
		result = SCD_MEMORY_OVER;
		return;
	}
	free(ret);

**	seed = 1;
**	rand_data1 = 0;
**	rand_data2 = 0;
**	rand_data3 = 0;
**	rand_data4 = 0;
**	srand(seed);/* 初期化 */
**	rand_data1 = rand();
**	rand_data2 = rand();
**	rand_data3 = rand();
**	rand_data4 = rand();
#endif

	result = 0;
/*	CipherInitial();*/
#if (0)
*	if (CipherData.LineSize <= SCD_LINE_SIZE) {
*		result = CipherDecode(CipherData.LineSize);
*	}
*	else {
*		result = CipherDecode(SCD_LINE_SIZE);
*	}
#endif

	enc_line_cnt = 0;
	if (CipherData.LineSize >= SCD_LINE_SIZE) {
		enc_max_line = SCD_LINE_SIZE;
	/*	result = CipherEncode(SCD_LINE_SIZE);*/
	}
	else {
		enc_max_line = CipherData.LineSize;
	/*	result = CipherEncode(CipherData.LineSize);*/
	/*	return;*/
	}
	do {
		CopyImg1ToImg2(enc_line_cnt);
		result = CipherEncode(1);
		enc_line_cnt++;
		if (result == SCD_MEMORY_OVER) {
			enc_line_cnt = enc_max_line;
			break;
		}
		if (enc_line_cnt == CipherData.OffsetServiceLabel) {
			result = WriteLabel();
			if (result) {
				enc_line_cnt = enc_max_line;
			}
		}
	}while(enc_line_cnt < enc_max_line);

	if (result == SCD_MEMORY_OVER) {	/*	1	*/
		/* exi_tsk();*/
		return;
	}
/*#endif このモジュールは、コメントにする */
}


/*************************************************************************
	module		:[暗号化・復号化タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/07/24]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_CipherTask(void)
{
	UBYTE page_exist;
	UBYTE result;
	int *lib_ptr;
	UBYTE i;
	MESSAGE_t	*MessageControl;/*By Y.Suzuki 1998/07/09*/

	CipherMessage.Item = FROM_CIPHER_TASK;
	CipherMessage.SubMessage1 = 0;
	CipherMessage.SubMessage2 = 0;

	/*受信優先処理 By Y.Suzuki 1998/06/09 */
	if (SYS_CipherInterruptionOn != 0) {/*受信優先処理からの起動 By Y.Suzuki 1998/06/09 */
		if (CipherWritePageNo >= 1) {/*スクランブル処理が複数ページあり、１ページ以上処理が終わっている */
			CipherReadPageNo--;
			CipherWritePageNo--;
		}
		/*SYS_CipherInterruptionOn = 0;ここでは、クリアしない By Y.Suzuki 1998/08/05 */
	}
	else {/* 通常の起動*/
		CipherData.PageNo = 0;
		CipherReadPageNo = 0;
		CipherWritePageNo = 0;
	}

	page_exist = 1;
	CipherStopOn = 0;

	/* 2回線目のラインNO.取り込み By Y.Suzuki 1998/04/28 */
	for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
		if (CHK_OptionLineExist((UBYTE)i)) {
			break;
		}
	}
	if (i < SYS_OPTION_BOARD_MAX) {
		OtherLineNo = i;
	}
	else {
		OtherLineNo = 0xff;
	}

	/*アリロの大域変数初期化 キー間違いでクリアした場合 9999が入る */
	/*クリアするとデスクランブル原稿をプリントしない By Y.Suzuki 1998/04/15 */
	glb_err = 0;

	/* スクランブル時拡張キーの初期化 */
	if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
		CipherData.ExtensionKey = SYB_KeyBookData.KeyExtensionOn;
		if (CipherData.ExtensionKey) {
			CipherData.ExtensionKey = 1 + (UBYTE)(SYB_CurrentTime % 99);
		}
	}
	/* デスクランブル時 プリント用管理テーブル セット */
	else {
		SYB_CipherPrintNo = CipherReadIndex.No;

		/* スクランブル解除時にスクランブル原稿のクリアOPRを入れたので、受信優先によりスクランブル解除が中断された場合、
		** プリント用管理パラメータを初期化してはいけないケースがある。 By Y.Suzuki 1998/08/05 */
		if (!((SYS_CipherInterruptionOn != 0) && (SYS_CipherComExec == SYS_DECIPHER_EXEC))) {
			/*受信優先処理からの起動ではない By Y.Suzuki 1998/08/05 */
			SYB_CPH_RxPrint[0].Status = SYS_MCOPY_STORE; /* 蓄積開始～蓄積完了までのステータス登録 */
			SYB_CPH_RxPrint[0].PrintPage = 1;
			SYB_CPH_RxPrint[0].ExecutiveNumber = 1;
			SYB_CPH_RxPrint[0].StorePage = 0;
		}
		if(SYS_CipherComExec == SYS_DECIPHER_EXEC) {
			/* 受信原稿 デスクランブル時 部数セット */
			SYB_CipherPrintItem = SYS_MEM_DECIPHER_FILE;
			SYB_CPH_RxPrint[0].ReserveNumber = CipherData.PrintPageNo;/* 部数 */
		}
		else {
			SYB_CipherPrintItem = SYS_MEM_TX_DECIPHER_FILE;
			SYB_CPH_RxPrint[0].ReserveNumber = 1;/* 部数 */
		}
	}
	if (SYS_CipherInterruptionOn != 0){
		SYS_CipherInterruptionOn = 0;/*受信優先処理フラグクリア By Y.Suzuki 1998/08/05 */
	}

	/*lib_ptr = _B_BGN - 2;* B_BGN - 8 BYTE */
#if(0)
*	lib_ptr = _B_BGN;
*	lib_ptr -= 2;/* B_BGN - 8 BYTE == FREEPTR のアドレス */
*	for (lib_ptr=_B_BGN ;lib_ptr>(_B_BGN-2) ;lib_ptr--) {
*		/* FREEPTR のクリア */
*		*lib_ptr = 0;
*	}
#endif
	/*_INIT_IOLIB();*/
	while(page_exist) {
		/* Ｃライブラリの初期化 */
		brk = (UBYTE *)&HeapArea;/* malloc 使用のための初期設定 */
		init_freeptr();
	/*	result = CipherInitial();1998/6/18 y.suzuki */
	/*スクランブルオペレーション中の受信開始後のスクランブルの初期化場所変更*/
		/*スクランブル機能ＯＰＲ中に着信してしまった By Y.Suzuki 1998/06/08 */
		/*if ((NCUStatus & DETECT_CI_STATE)||(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) [*/
		/* スクランブルタスクは、waioneshotを使用しない様にしてます */
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
		/*ユニークＳＷの設定によらず、スクランブル処理をリセットする。*/
			SYS_CipherInterruptionOn = SYS_CipherComExec;
			CipherStopOn = 1;
			/*SYS_CipherInterruptionOnがセットされてから初期化する*/
			result = CipherInitial();
			show_slider(0,0);/* ストップキーONメッセージ送信 */
		}
		else {
			result = CipherInitial();
		}

		/* 表示切り替えのため */
		/*蓄積完了の表示がちらつくので表示完了するまで(2秒)ウエイトする*/
		if ((CipherWritePageNo == 1) && (SYS_CipherComExec == SYS_CIPHER_EXEC)) {
			wai_tsk(200);
		}
		CipherMessage.Message = MSG_DISPLAY_IDLE;
		snd_msg(mbxno.MAN_Task, &CipherMessage);
		if (result == MEM_OK) {
			/* １ページデコード ＭＭＲからイメージ */
			if (CipherData.LineSize <= SCD_LINE_SIZE) {
				result = CipherDecode(CipherData.LineSize);
			}
			else {
				result = CipherDecode(SCD_LINE_SIZE);
			}
		}
		/*デコード中にストップキーを押された場合 By Y.Suzuki 1998/04/12 */
		if (CipherStopOn) {
			show_slider(0,0);/* ストップキーONメッセージ送信 */
		}
		if (result == SCD_DECODE_OK || result == RTC) {
			if (SYS_CipherComExec == SYS_CIPHER_EXEC) {/*	暗号化	*/
				/* 暗号化 モジュール */
				if (SYB_MaintenanceSwitch[MNT_SW_F1] & ALIROO_CALL) {
					AlirooScramble (&CipherData);
				}
				else {
					MML_CipherDebug2();
				}
			}
			else {/*	復号化	*/
				/* 復号化モジュール */
				if (SYB_MaintenanceSwitch[MNT_SW_F1] & ALIROO_CALL) {
					AlirooDescramble (&CipherData);
				}
				else {
					MML_CipherDebug2();
				}
			}
		}
		else {
			/* 元原稿メモリエラー */
			CipherData.ErrorCode = result;
			/* 元原稿メモリエラー場合でスクランブル原稿消去の場合ここで消去しておく By Y.Suzuki 1998/07/31*/
			if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC) {
				result = MEM_ClearPageAndFATArea(&CipherReadIndex);/* By Y.Suzuki 1998/07/15 */
			}
			break;
		}
		/* デスクランブル最終ページのときキー間違いエラーをセットする By Y.Suzuki 1998/04/15 */
		/* wrong key を無視するとIDS_NEED_KEY_EXTでデスクランブルから帰ってくることがあった */
		/* 複数ページデスクランブル原稿がある場合、最終ページまで処理を続ける。*/
		if (((CipherData.ErrorCode == 0)||(CipherData.ErrorCode == IDS_NEED_KEY_EXT)) && (glb_err == 9999)) {
		/*	&& (CipherReadPageNo == CipherData.PageNo)) [/* キー間違い検出 By Suzuki 98/4/15 */
			/* IncorrectKey()の方でチェックするので、最終ページの条件不要。By Y.Suzuki 1998/08/11 */
			CipherData.ErrorCode = glb_err;
		}
	/*	if (CipherData.ErrorCode == 0) {* 1ページ正常終了 By Suzuki 98/4/14 */
		if (CipherData.ErrorCode == 0) {/* 1ページ正常終了 */
			result = WriteRtcToMem(&CipherEncodeData);
			if (result != SCD_MEMORY_OVER) {
				MEM_WriteClose(&CipherExecWriteData ,CipherEncodeData.Line_Cntr);
				/* 以下部数プリントのため追加 By Y.Suzuki 1998/01/12 */
				/* デスクランブル時１ページ蓄積完了 */
				if (SYS_CipherComExec != SYS_CIPHER_EXEC) {
					SYB_CPH_RxPrint[0].StorePage++;/* 書込み完了したページ */
					if ((SYB_MaintenanceSwitch[MNT_SW_E1] & ALIROO_PRT_START_ON)
						&& (SYS_CipherComExec == SYS_DECIPHER_EXEC)) {
						if (SYB_CPH_RxPrint[0].StorePage > 1) {
						/*２ページ目以降メインでプリントリスタートイベント発生*/
						/*	CipherMessage.Message = MSG_OPT_CIPHER_PRT_RESTART;By Y.Suzuki 1998/07/08
						**	snd_msg(mbxno.MAN_Task, &CipherMessage);	*	エンコード開始メッセージ送信	*/
							if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC) {
								/* スクランブル原稿を消去By Y.Suzuki 1998/07/09 */
								result = MEM_ClearPageAndFATArea(&CipherReadIndex);/* By Y.Suzuki 1998/07/15 */
							}
						}
						else {
							/*１ページ目をプリントさせるため By Y.Suzuki 1998/07/03 */
							show_slider(0,0);
							/* メインからスクランブル原稿消去･消去中止のメッセージ待ち By Y.Suzuki 1998/07/09 */
							rcv_msg(mbxno.SCD_CipherResult, &MessageControl);
							if (MessageControl->Message == MSG_OPT_DECIPHER_FROM_OPR) {
								if (MessageControl->SubMessage1) {
									/* スクランブル原稿1ﾍﾟｰｼﾞ目クリア */
									SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_ERASE_SCRAMBLE_DOC;
									result = MEM_ClearPageAndFATArea(&CipherReadIndex);/* By Y.Suzuki 1998/07/15 */
								}
								SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_FIRST_PAGE;
								SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DISPLAY_DESCRAMBLE;
							}
						}
					}
				}
			}
			if (result != MEM_OK) {/* エラー */
				CipherData.ErrorCode = SCD_MEMORY_OVER;
				break;
			}
		}
		else {/* エラー */
			/* エラーとなった場合でスクランブル原稿消去の場合ここで消去しておく By Y.Suzuki 1998/07/31*/
			if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC) {
				result = MEM_ClearPageAndFATArea(&CipherReadIndex);/* By Y.Suzuki 1998/07/15 */
			}
			break;
		}
		/* ライブラリ ファイルのクローズ */
		/*_CLOSEALL();*/

		if ((SYS_CipherComExec == SYS_CIPHER_EXEC) && (CipherData.ErrorCode == 0)) {/* 元原稿の消去 */
			/* スクランブルエラーの場合はここでは消さない。By Y.Suzuki 1998/04/12 */
			if(SYB_MaintenanceSwitch[MNT_SW_F7] != NO_ERASE_DOC) {
				result = MEM_ClearPage(&CipherReadIndex);
			}
		}
		if (CipherReadPageNo == CipherData.PageNo) {/*	全ページ終了	*/
			page_exist = 0;
			/*	正常終了メッセージ送信	*/
			CipherMessage.Message = MSG_OPT_CIPHER_COMPLETE;
			if (SYS_CipherComExec != SYS_CIPHER_EXEC) {
				/* SYS_DocumentPrintNo をメッセージで送る */
				/*CipherMessage.SubMessage2 = CipherReadIndex.No;By Y.Suzuki 1998/07/08 */
				if ((CipherReadPageNo != 1) || ((CipherReadPageNo == 1)
					&& (SYS_CipherComExec == SYS_TX_DOC_DECIPHER_EXEC))) {
					/*1ページ目は、既にプリント済み。2ページ目以降があるときのみ By Y.Suzuki 1998/07/24*/
					/*送信原稿のスクランブル解除プリントのときは、１ページ目でもステータスセットする By Y.Suzuki 1998/07/25 */
					SYB_CPH_RxPrint[0].Status = SYS_MCOPY_PRINT; /* 蓄積完了のステータス登録 */
				}
			}
			snd_msg(mbxno.MAN_Task, &CipherMessage);
			wai_tsk(0xffff);
		}
#if(0)
		else {/* Next page exist */
			CipherBegin = 1;
		}
#endif
	}
	/* エラー時の後始末 */
	/* スクランブル時全てのページを消去 */
	if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
		/* スクランブル前原稿のクリア */
		MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, MEM_IGNORE_BOX_NUMBER);
		/* スクランブル原稿のクリア */
		MEM_ClearDocAndFATArea(SYS_MEM_TX_FILE, CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
		/* スクランブル原稿の最初のブロック蓄積中（１ブロック以下）に元原稿をデコードエラーすると
		*  スクランブル原稿蓄積中のＦＡＴを消すとこでMEM_TOTALSTOREBLOCKCOUNTERをFFFFにしてしまう。
		*  ほかに蓄積原稿があった場合、MEM_TOTALSTOREBLOCKCOUNTERが1少なくなってしまう。*/
		MEM_TotalStoreBlockCounter++;
	}
	else {
		/*if (CipherData.ErrorCode == 9999) [By Y.Suzuki 1998/08/25*/
		if ((CipherData.ErrorCode == 9999) || (CipherData.ErrorCode == IDS_NEED_KEY_EXT)) {
			/* 拡張キー必要エラー（キー間違いＯＰＲにはならない）場合追加 By Y.Suzuki 1998/08/25 */
			/* キー間違いオペレーションでクリアを押された場合は、全ページ消去する。By Y.Suzuki 98/4/14 */
			SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
			MEM_ClearDocAndFATArea(CipherStoreData.Item, CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
			/*  デスクランブル原稿蓄積中のＦＡＴを消すとこでMEM_TOTALSTOREBLOCKCOUNTERをFFFFにしてしまう。
			*  ほかに蓄積原稿があった場合、MEM_TOTALSTOREBLOCKCOUNTERが1少なくなってしまう。By Y.Suzuki 1998/08/24 */
			MEM_TotalStoreBlockCounter++;
		}
		else {
			/* エラーしたページのみを消去 復元時  */
			SYB_CPH_RxPrint[0].Status = SYS_MCOPY_MEMORY_OVER;
			CipherWriteIndex.No  = CipherStoreData.No;
			CipherWriteIndex.Page  = CipherStoreData.Page;
			CipherWriteIndex.Item  = CipherStoreData.Item;
			CipherWriteIndex.BoxNumber = 0;/* By Y.Suzuki 1998/04/14 */
			CipherWriteIndex.Item |= MEM_NOW_STORING;/* By Y.Suzuki 1998/04/08 */
			result = MEM_ClearPageAndFATArea(&CipherWriteIndex);/* By Y.Suzuki 1998/04/8 */
			/*  デスクランブル原稿蓄積中のＦＡＴを消すとこでMEM_TOTALSTOREBLOCKCOUNTERをFFFFにしてしまう。
			*  ほかに蓄積原稿があった場合、MEM_TOTALSTOREBLOCKCOUNTERが1少なくなってしまう。By Y.Suzuki 1998/08/24 */
			MEM_TotalStoreBlockCounter++;

			/* 復元処理中のエラー発生時、正常終了したページがあったらプリントする。 */
			if ((MEM_CountTotalPage(SYS_MEM_DECIPHER_FILE, CipherStoreData.No, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX)
				|| (MEM_CountTotalPage(SYS_MEM_TX_DECIPHER_FILE, CipherStoreData.No, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX)){
				/** １枚以上正常原稿がある場合は、プリント */
				CipherMessage.SubMessage1 = 1;/* By Y.Suzuki 1998/07/08 */
				SYB_CPH_RxPrint[0].Status = SYS_MCOPY_PRINT;
			}
			else  {	/** 原稿がない */
				CipherMessage.SubMessage1 = 0;/* By Y.Suzuki 1998/07/08 */
				SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;/* By Y.Suzuki 1998/04/17 */
			}
		}
	}

	switch(CipherData.ErrorCode) {
	/*	エラーメッセージ送信	*/
	/*case SCD_MEMORY_OVER:By Y.Suzuki 1998/04/18 */
	case IDS_OUTPUT_IMAGE:
		if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
			CipherMessage.Message = MSG_OPT_CIPHER_MEM_ERROR;
		}
		else {
			CipherMessage.Message = MSG_OPT_DECIPHER_MEM_ERROR;
		}
		break;
	case SCD_DECODE_NG:
		if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
			CipherMessage.Message = MSG_OPT_CIPHER_DECODE_ERROR;
		}
		else {
			CipherMessage.Message = MSG_OPT_DECIPHER_DECODE_ERROR;
		}
		break;
	case 9999:
		/* キー間違いでクリアキーを選択したときはエラーにしない By Y.Suzuki 98/04/15 */
	/*	CipherMessage.Message = MSG_OPT_CIPHER_COMPLETE;By Y.Suzuki 1998/04/28 */
		/* 取説とあわせるため、エラーにする By Y.Suzuki 1998/04/28 */
		CipherMessage.Message = MSG_OPT_ALIROO_ERROR;
		break;
	default:
		CipherMessage.Message = MSG_OPT_ALIROO_ERROR;
	}
	snd_msg(mbxno.MAN_Task, &CipherMessage);
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[ＭＭＬ作成モジュールデバック用タスク]
	function	:[
		1.本来アリロさんが作るサブルーチンです。
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/07/06]
	author		:[鈴木郁ニ]
*************************************************************************/
/* void MML_CipherDebugTask(void) */
void MML_CipherDebug(void)
{
	UBYTE result;
	UWORD line_cnt;
	UWORD total_line;

	result = 0;
	line_cnt = 0;
	total_line = 0;
	CipherReadPageNo = 0;
	CipherWritePageNo = 0;
	CipherData.StartPageNo = 0;/* By Y.Suzuki 97/11/05 */
/*	CipherBegin = 1;*/
/*	CipherInitial();*/
	while(1) {
		result = CipherDecode(100);	/*	100ライン分イメージRAMへ書込み	*/
		if (result == SCD_DECODE_OK) {
			result = CipherEncode(100);	/*	100ライン分イメージRAMへ書込み	*/
			total_line += 100;
			if (CipherData.PageMode == SYS_NORMAL) {
				if (total_line == 300) {
					result = WriteLabel();
				}
			}
			else if(CipherData.PageMode == SYS_FINE){
				if (total_line == 900) {
					result = WriteLabel();
				}
			}
		}
		else if(result == RTC) {	/*	14	*/
			line_cnt = CipherReadTotalLine % 100;
			result = CipherEncode(line_cnt);
			total_line += line_cnt;
#if(0)
*			result = WriteRtcToMem(&CipherEncodeData);
*			MEM_WriteClose(&CipherExecWriteData ,total_line);
#endif
			return;
		}
		else {
			return;
			/* exi_tsk();*/
		}
		if (result == SCD_MEMORY_OVER) {	/*	1	*/
			/* exi_tsk();*/
			return;
		}
	}
}

#endif	/* #if (PRO_CIPHER == ENABLE) By O.Kimoto 1998/10/21 */

/*******************************************************
    module		:[１ライン分のＲＬをイメージに変換する]
    fonction	:[]
    return		:[]
    common		:[]
    condition	:[内蔵ＲＯＭ]
    comment		:[]
    machine		:[SH7041]
    language	:[SHC]
    keyword		:[]
    date		:[1997/6/17]
    author		:[鈴木郁二]
********************************************************/
#pragma section SCD /* locate section name "PSCD" */

#if (0)
** /* ＨＩＮＯＫＩも新しいＣＰＵ（下記キャストミス修正版）にします。 By O.Kimoto 1998/11/20 */
** /* 間接参照ポインターの処理でキャストミスが見つかった。
** ** しかし、ＨＩＮＯＫＩはＥＳを組み立てた直後＆Ｅｎｃｏｄｅ/Ｄｅｃｏｄｅも
** ** それほど動作していないので、当面、条件コンパイルで切り分けておきます。
** ** ＨＩＮＯＫＩはＣＰＵを書き直すときは必ずこの条件コンパイルを削除すること！！！
** ** by O.Kimoto 1998/10/21
** */
** #if defined (HINOKI)
** 
** void SCD1LineRlToImgIntRom(struct WorkBuf_t *point,
** 					struct CdcBlk_t *scdcp,
** 					UWORD line)
** {
** 
** 	UWORD rl_a;			 							/** 走査線　run length */
** 	UWORD ImgCntr;									/** 走査線カウンタ */
** 	UWORD ImgBitCntr;								/** 1ライン走査線数カウンタ */
** 	UWORD BufCntr;									/** ＲＬ確認カウンタ */
** 	UBYTE ImgBufData;								/** イメージデータ バッファ */
** 	UBYTE ImgClor;									/** カラーデータ */
** 	UBYTE ImgbyteClor;								/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
** 	UBYTE SfitCntr;									/** ビット カウンタ */
** 
** 
** 	point->Cout = 0;
** 	point->Flag = 0;
** 	SfitCntr = 0;
** 	ImgBitCntr = 0;
** 	ImgCntr = 0;
** 	ImgBufData = 0;
** 	ImgClor = 0;
** 	ImgbyteClor = 0x00;
** 
** 	/*SCD_Debug_Img_Size = 0;*/
** 
** 	do 	{
** 	    rl_a = GetRL(point);							/** run length バッファ から ＲＬを取り出す */
** 
** 	/*	SCD_Debug_Img_Size += rl_a;*/
** 
** #if (0)/* By Y.Suzuki 1998/04/17 */
** //		if (!(ImgBitCntr % 500)) {
** //			wai_oneshot(1);
** //		}
** #endif
** 		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
** 		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
** 			if (rl_a >= 8){
** 				do {
** 
** #if (0)
** ** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** ** 					Img_Buffer1[line][ImgCntr] = ImgbyteClor;
** #else
** #if (1)	/* キャストミス by O.Kimoto 1998/10/19 */
** 					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF1_WIDTH) + (UWORD)ImgCntr) = ImgbyteClor;
** #else
** **					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
** #endif
** #endif
** 
** 
** 				/*	AlirooTestData -> Img_Buffer[line][ImgCntr] = ImgbyteClor;*/
** 				/*	*(Img_Buffer[line][ImgCntr]) = ImgbyteClor;*/
** 					ImgCntr++;
** 					rl_a -= 8;
** 					ImgBitCntr += 8;
** 				} while (rl_a >= 8);
** 				ImgBufData = 0;
** 			}
** 		}
** 		if (rl_a != 0) {
** 		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
** 			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
** 												 	/** RL からイメージに変換 */
** 				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
** 				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
** 				SfitCntr++;							/** ビット カウンタ 更新 */
** 
** 				if (SfitCntr == 8){
** 
** #if (0)
** ** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** ** 					Img_Buffer1[line][ImgCntr]=ImgBufData;
** #else
** #if (1)	/* キャストミス by O.Kimoto 1998/10/19 */
** 					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF1_WIDTH) + (UWORD)ImgCntr) = ImgBufData;
** #else
** ** 					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
** #endif
** #endif
** 
** 				/*	AlirooTestData -> Img_Buffer[line][ImgCntr]=ImgBufData;*/
** 				/*	*(Img_Buffer[line][ImgCntr])=ImgBufData;*/
** 													/** ＳＲＡＭにイメージ データ書き込み */
** 					ImgCntr++;
** 					SfitCntr=0;						/** ビット  カウンタ = 0 */
** 					ImgBufData = 0;
** 				}
** 				else {
** 					ImgBufData <<= 1;
** 				}
** 			}
** 
** 		}
** 
** 		ImgClor = (UBYTE)(ImgClor ^ 0x01);
** 		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
** 	} while (scdcp->Img_Size > ImgBitCntr);			/** 1ライン終了か ？ */
** #if (0)
** //	if (scdcp->Img_Size != ImgBitCntr) {
** //		SCD_Debug_Err_Img |= 1;
** //	}
** #endif
** 	return;
** 
** }
** 
** 
** 
** /********************************************************
** 	module		:[１ライン分のイメージをＲＬに変換する]
** 	function	:[]
** 	return		:[]
** 	common		:[]
** 	condition	:[内蔵ＲＯＭ]
** 	comment		:[]
** 	machine		:[SH7041]
** 	language	:[SHC]
** 	keyword		:[]
** 	date		:[[1997/6/17]
** 	author		:[鈴木郁二]
** *********************************************************/
** void SCD1LineImgToRlIntRom(struct WorkBuf_t *point,
** 					struct CdcBlk_t *scdcp,
** 					UWORD line)
** {
** 
** 	UWORD rl_data;
** 	UWORD BufCntr;									/** １ラインバイト数カウンタ */
** 	UWORD buf_max;									/* 1ラインＭＡＸバイト数 */
** 	UWORD rl_cnt;
** 	UBYTE col_flag;
** 	UBYTE ImgBufData;								/** カラーデータ */
** 	UBYTE SfitCntr;									/** ８ ビットシフトカウンタ */
** 
** 	rl_data = 0;										/** ＲＬ　データ */
** 	col_flag = 0;										/** ０＝白，１＝黒 */
** 	point->Cout = 0;
** 	point->Flag = 0;
** 	rl_cnt = 0;
** 	buf_max = ((scdcp->Img_Size)/8);
** 
** 	SfitCntr = 8;
** 	rl_data = 0;
** 	col_flag = WHITE;
** 
** 	for (BufCntr = 0; BufCntr != buf_max; BufCntr++){
** 
** #if (0)
** ** 		/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** ** 		ImgBufData = Img_Buffer2[line][BufCntr];/* 本番一回に１ラインのみ符号化 */
** #else
** #if (1)	/* キャストミス by O.Kimoto 1998/10/19 */
** 		ImgBufData = *(img_buffer2 + (UWORD)(line * SCD_LINE_BUF2_WIDTH) + (UWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
** #else
** **		ImgBufData = *(img_buffer2 + (UDWORD)(line * SCD_LINE_BUF2_WIDTH) + (UDWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
** #endif
** #endif
** 
** 	/*	ImgBufData = CipherP -> Img_Buffer1[line][BufCntr];* デバック用 */
** 
** 		if (!(BufCntr % 50)) {
** 		/*	wai_oneshot(1); By Y.Suzuki 97/10/29 */
** 		}
** 
** 		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
** 		if (ImgBufData == 0x00){
** 			if (col_flag == WHITE) {
** 				rl_data += SfitCntr;
** 			}
** 			else {
** #if (0)
** //				if ((point->Cout != 0) && !rl_data) {
** //					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //				}
** #endif
** 				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 				rl_cnt += rl_data;
** 				rl_data = 8;
** 				col_flag = WHITE;
** 			}
** 		}
** 		else if (ImgBufData == 0xff){
** 			if (col_flag == BLACK){
** 				rl_data += SfitCntr;
** 			}
** 			else {
** #if (0)
** //				if ((point->Cout != 0) && !rl_data) {
** //					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //				}
** #endif
** 				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 				rl_cnt += rl_data;
** 				rl_data = 8;
** 				col_flag = BLACK;
** 			}
** 		}
** 		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
** 
** 		else {
** 
**  			do {
** 				if ((ImgBufData & 0x80) == WHITE) {		/* 白 ? */
** 					if (col_flag == WHITE) {
** 						rl_data++;
** 					}
** 					else {
** #if (0)
** //						if ((point->Cout != 0) && !rl_data) {
** //							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //						}
** #endif
** 						PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
** 						rl_cnt += rl_data;
** 						rl_data = 1;
** 						col_flag = WHITE;
** 					}
** 				}
** 				else {
** 					if (col_flag == BLACK) {
** 						rl_data++;
** 					}
** 					else {
** 						rl_cnt += rl_data;
** #if (0)
** //						if ((point->Cout != 0) && !rl_data) {
** //							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
** //						}
** #endif
** 						PutRL(point,rl_data,col_flag);
** 						rl_data = 1;
** 						col_flag = BLACK;
** 					}
** 				}
** 				ImgBufData <<= 1;
** 				SfitCntr--;
** 			} while (SfitCntr != 0);
** 
** 		}
** 		SfitCntr = 8;
** 	}
** 	if (rl_data > 0) {
** 		rl_cnt += rl_data;
** 		PutRL(point,rl_data,col_flag);
** 	}
** #if (0)
** //	if (scdcp->Img_Size != rl_cnt) {
** //		SCD_Debug_Err_Img |= 0x80;
** //	}
** #endif
** 	return;
** }
** 
** 
** /*******************************************************
**     module		:[１ライン分のＲＬをイメージに変換する]
**     fonction	:[]
**     return		:[]
**     common		:[]
**     condition	:[内蔵ＲＯＭ]
**     comment		:[]
**     machine		:[SH7041]
**     language	:[SHC]
**     keyword		:[]
**     date		:[1998/9/7]
**     author		:[K.Kawata]
** ********************************************************/
** /* void SAKAKI1LineRL_ToImage(struct WorkBuf_t *point,	1998/10/21 H.Yoshikawa */
** void SCD1LineRlToImg1IntRom(struct WorkBuf_t *point,
** 					struct CdcBlk_t *scdcp,
** 					UWORD line)
** {
** 	UWORD rl_a;			 			/** 走査線　run length */
** 	UWORD ImgCntr;					/** 走査線カウンタ */
** 	UWORD ImgBitCntr;				/** 1ライン走査線数カウンタ */
** 	UWORD BufCntr;					/** ＲＬ確認カウンタ */
** 	UBYTE ImgBufData;				/** イメージデータ バッファ */
** 	UBYTE ImgClor;					/** カラーデータ */
** 	UBYTE ImgbyteClor;				/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
** 	UBYTE SfitCntr;					/** ビット カウンタ */
** 
** 	point->Cout = 0;
** 	point->Flag = 0;
** 	SfitCntr = 0;
** 	ImgBitCntr = 0;
** 	ImgCntr = 0;
** 	ImgBufData = 0;
** 	ImgClor = 0x01;	/*1998.7.16 K.Kawata*/
** 	ImgbyteClor = 0xff;	/*1998.7.16 K.Kawata*/
** 
** 	do 	{
** 	    rl_a = GetRL(point);	/** run length バッファ から ＲＬを取り出す */
** 		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
** 		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
** 			if (rl_a >= 8){
** 				do {
** 
** #if (0)
** ** 					/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** ** 					PRN_ImageBuffer1[line][ImgCntr] = ImgbyteClor;	/*1998.8.19 K.Kawata*/
** #else
** #if (1)	/* キャストミス by O.Kimoto 1998/10/19 */
** 					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/
** #else
** ** 					*(prn_imgbuf1_p + (UDWORD)(line * PRT_IMG_BUF_SIZE) + (UDWORD)ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/
** #endif
** #endif
** 
** 					ImgCntr++;
** 					rl_a -= 8;
** 					ImgBitCntr += 8;
** 				} while (rl_a >= 8);
** 				ImgBufData = 0;
** 			}
** 		}
** 		if (rl_a != 0) {
** 			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
** 												 	/** RL からイメージに変換 */
** 				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
** 				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
** 				SfitCntr++;							/** ビット カウンタ 更新 */
** 				if (SfitCntr == 8){
** 
** #if (0)
** ** 					/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** ** 					PRN_ImageBuffer1[line][ImgCntr] = ImgBufData;	/*1998.8.19 K.Kawata*/
** #else
** #if (1)	/* キャストミス by O.Kimoto 1998/10/19 */
** 					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
** #else
** **					*(prn_imgbuf1_p + (UDWORD)(line * PRT_IMG_BUF_SIZE) + (UDWORD)ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
** #endif
** #endif
** 					/** ＳＲＡＭにイメージ データ書き込み */
** 					ImgCntr++;
** 					SfitCntr=0;	/** ビット  カウンタ = 0 */
** 					ImgBufData = 0;
** 				}
** 				else {
** 					ImgBufData <<= 1;
** 				}
** 			}
** 		}
** 		ImgClor = (UBYTE)(ImgClor ^ 0x01);
** 		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
** 	} while (scdcp->Img_Size > ImgBitCntr);	/* 1ライン終了か ？ */
** 	return;
** }
#else
/* 間接参照ポインターの処理でキャストミスが見つかった。
** しかし、ＨＩＮＯＫＩはＥＳを組み立てた直後＆Ｅｎｃｏｄｅ/Ｄｅｃｏｄｅも
** それほど動作していないので、当面、条件コンパイルで切り分けておきます。
** ＨＩＮＯＫＩはＣＰＵを書き直すときは必ずこの条件コンパイルを削除すること！！！
** by O.Kimoto 1998/10/21
*/
/* 上記にある条件コンパイルは削除！ By O.Kimoto 1998/11/20 */

void SCD1LineRlToImgIntRom(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{

	UWORD rl_a;			 							/** 走査線　run length */
	UWORD ImgCntr;									/** 走査線カウンタ */
	UWORD ImgBitCntr;								/** 1ライン走査線数カウンタ */
	UWORD BufCntr;									/** ＲＬ確認カウンタ */
	UBYTE ImgBufData;								/** イメージデータ バッファ */
	UBYTE ImgClor;									/** カラーデータ */
	UBYTE ImgbyteClor;								/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
	UBYTE SfitCntr;									/** ビット カウンタ */


	point->Cout = 0;
	point->Flag = 0;
	SfitCntr = 0;
	ImgBitCntr = 0;
	ImgCntr = 0;
	ImgBufData = 0;
	ImgClor = 0;
	ImgbyteClor = 0x00;

	/*SCD_Debug_Img_Size = 0;*/

	do 	{
	    rl_a = GetRL(point);							/** run length バッファ から ＲＬを取り出す */

	/*	SCD_Debug_Img_Size += rl_a;*/

#if (0)/* By Y.Suzuki 1998/04/17 */
//		if (!(ImgBitCntr % 500)) {
//			wai_oneshot(1);
//		}
#endif
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
			if (rl_a >= 8){
				do {

#if (0)
** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** 					Img_Buffer1[line][ImgCntr] = ImgbyteClor;
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF1_WIDTH) + (UWORD)ImgCntr) = ImgbyteClor;
#else
					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
#endif
#endif


				/*	AlirooTestData -> Img_Buffer[line][ImgCntr] = ImgbyteClor;*/
				/*	*(Img_Buffer[line][ImgCntr]) = ImgbyteClor;*/
					ImgCntr++;
					rl_a -= 8;
					ImgBitCntr += 8;
				} while (rl_a >= 8);
				ImgBufData = 0;
			}
		}
		if (rl_a != 0) {
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
												 	/** RL からイメージに変換 */
				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
				SfitCntr++;							/** ビット カウンタ 更新 */

				if (SfitCntr == 8){

#if (0)
** 					/* 間接参照ポインターに変更 By O.Kimoto 1998/09/25 */
** 					Img_Buffer1[line][ImgCntr]=ImgBufData;
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF1_WIDTH) + (UWORD)ImgCntr) = ImgBufData;
#else
 					*(img_buffer1 + (UDWORD)(line * SCD_LINE_BUF1_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
#endif
#endif

				/*	AlirooTestData -> Img_Buffer[line][ImgCntr]=ImgBufData;*/
				/*	*(Img_Buffer[line][ImgCntr])=ImgBufData;*/
													/** ＳＲＡＭにイメージ データ書き込み */
					ImgCntr++;
					SfitCntr=0;						/** ビット  カウンタ = 0 */
					ImgBufData = 0;
				}
				else {
					ImgBufData <<= 1;
				}
			}

		}

		ImgClor = (UBYTE)(ImgClor ^ 0x01);
		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
	} while (scdcp->Img_Size > ImgBitCntr);			/** 1ライン終了か ？ */
#if (0)
//	if (scdcp->Img_Size != ImgBitCntr) {
//		SCD_Debug_Err_Img |= 1;
//	}
#endif
	return;

}



/********************************************************
	module		:[１ライン分のイメージをＲＬに変換する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7041]
	language	:[SHC]
	keyword		:[]
	date		:[[1997/6/17]
	author		:[鈴木郁二]
*********************************************************/
void SCD1LineImgToRlIntRom(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{

	UWORD rl_data;
	UWORD BufCntr;									/** １ラインバイト数カウンタ */
	UWORD buf_max;									/* 1ラインＭＡＸバイト数 */
	UWORD rl_cnt;
	UBYTE col_flag;
	UBYTE ImgBufData;								/** カラーデータ */
	UBYTE SfitCntr;									/** ８ ビットシフトカウンタ */

	rl_data = 0;										/** ＲＬ　データ */
	col_flag = 0;										/** ０＝白，１＝黒 */
	point->Cout = 0;
	point->Flag = 0;
	rl_cnt = 0;
	buf_max = ((scdcp->Img_Size)/8);

	SfitCntr = 8;
	rl_data = 0;
	col_flag = WHITE;

	for (BufCntr = 0; BufCntr != buf_max; BufCntr++){

#if (0)
** 		/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** 		ImgBufData = Img_Buffer2[line][BufCntr];/* 本番一回に１ラインのみ符号化 */
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**		ImgBufData = *(img_buffer2 + (UWORD)(line * SCD_LINE_BUF2_WIDTH) + (UWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
#else
		ImgBufData = *(img_buffer2 + (UDWORD)(line * SCD_LINE_BUF2_WIDTH) + (UDWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
#endif
#endif

	/*	ImgBufData = CipherP -> Img_Buffer1[line][BufCntr];* デバック用 */

		if (!(BufCntr % 50)) {
		/*	wai_oneshot(1); By Y.Suzuki 97/10/29 */
		}

		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
		if (ImgBufData == 0x00){
			if (col_flag == WHITE) {
				rl_data += SfitCntr;
			}
			else {
#if (0)
//				if ((point->Cout != 0) && !rl_data) {
//					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
//				}
#endif
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = WHITE;
			}
		}
		else if (ImgBufData == 0xff){
			if (col_flag == BLACK){
				rl_data += SfitCntr;
			}
			else {
#if (0)
//				if ((point->Cout != 0) && !rl_data) {
//					SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
//				}
#endif
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = BLACK;
			}
		}
		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */

		else {

 			do {
				if ((ImgBufData & 0x80) == WHITE) {		/* 白 ? */
					if (col_flag == WHITE) {
						rl_data++;
					}
					else {
#if (0)
//						if ((point->Cout != 0) && !rl_data) {
//							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
//						}
#endif
						PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
						rl_cnt += rl_data;
						rl_data = 1;
						col_flag = WHITE;
					}
				}
				else {
					if (col_flag == BLACK) {
						rl_data++;
					}
					else {
						rl_cnt += rl_data;
#if (0)
//						if ((point->Cout != 0) && !rl_data) {
//							SYB_MaintenanceSwitch[MNT_SW_E1] | 0x20;
//						}
#endif
						PutRL(point,rl_data,col_flag);
						rl_data = 1;
						col_flag = BLACK;
					}
				}
				ImgBufData <<= 1;
				SfitCntr--;
			} while (SfitCntr != 0);

		}
		SfitCntr = 8;
	}
	if (rl_data > 0) {
		rl_cnt += rl_data;
		PutRL(point,rl_data,col_flag);
	}
#if (0)
//	if (scdcp->Img_Size != rl_cnt) {
//		SCD_Debug_Err_Img |= 0x80;
//	}
#endif
	return;
}


/*******************************************************
    module		:[１ライン分のＲＬをイメージに変換する]
    fonction	:[]
    return		:[]
    common		:[]
    condition	:[内蔵ＲＯＭ]
    comment		:[]
    machine		:[SH7041]
    language	:[SHC]
    keyword		:[]
    date		:[1998/9/7]
    author		:[K.Kawata]
********************************************************/
/* void SAKAKI1LineRL_ToImage(struct WorkBuf_t *point,	1998/10/21 H.Yoshikawa */
void SCD1LineRlToImg1IntRom(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{
	UWORD rl_a;			 			/** 走査線　run length */
	UWORD ImgCntr;					/** 走査線カウンタ */
	UWORD ImgBitCntr;				/** 1ライン走査線数カウンタ */
	UWORD BufCntr;					/** ＲＬ確認カウンタ */
	UBYTE ImgBufData;				/** イメージデータ バッファ */
	UBYTE ImgClor;					/** カラーデータ */
	UBYTE ImgbyteClor;				/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
	UBYTE SfitCntr;					/** ビット カウンタ */

	point->Cout = 0;
	point->Flag = 0;
	SfitCntr = 0;
	ImgBitCntr = 0;
	ImgCntr = 0;
	ImgBufData = 0;
	ImgClor = 0x01;	/*1998.7.16 K.Kawata*/
	ImgbyteClor = 0xff;	/*1998.7.16 K.Kawata*/

	do 	{
	    rl_a = GetRL(point);	/** run length バッファ から ＲＬを取り出す */
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
			if (rl_a >= 8){
				do {

#if (0)
** 					/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** 					PRN_ImageBuffer1[line][ImgCntr] = ImgbyteClor;	/*1998.8.19 K.Kawata*/
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/
#else
 					*(prn_imgbuf1_p + (UDWORD)(line * PRT_IMG_BUF_SIZE) + (UDWORD)ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/
#endif
#endif

					ImgCntr++;
					rl_a -= 8;
					ImgBitCntr += 8;
				} while (rl_a >= 8);
				ImgBufData = 0;
			}
		}
		if (rl_a != 0) {
			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
												 	/** RL からイメージに変換 */
				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
				SfitCntr++;							/** ビット カウンタ 更新 */
				if (SfitCntr == 8){

#if (0)
** 					/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** 					PRN_ImageBuffer1[line][ImgCntr] = ImgBufData;	/*1998.8.19 K.Kawata*/
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
**					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
#else
					*(prn_imgbuf1_p + (UDWORD)(line * PRT_IMG_BUF_SIZE) + (UDWORD)ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
#endif
#endif
					/** ＳＲＡＭにイメージ データ書き込み */
					ImgCntr++;
					SfitCntr=0;	/** ビット  カウンタ = 0 */
					ImgBufData = 0;
				}
				else {
					ImgBufData <<= 1;
				}
			}
		}
		ImgClor = (UBYTE)(ImgClor ^ 0x01);
		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
	} while (scdcp->Img_Size > ImgBitCntr);	/* 1ライン終了か ？ */
	return;
}
#endif

#pragma section  /* locate section name "PSCD" */

