/************************************************************************
*	System		: POPLAR
*	File Name	: SCDCHTX.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
/*----------------------------------------------------------------------*/
/* ソフトコーデック使用 キャラクタ送信									*/
/*											95/11/16 Y.Suzuki			*/
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\sysdblk.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\message.h"				/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"		/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/
/* #include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"	*/	/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/
 #endif
#endif

#include "\src\atlanta\define\syscomf.h"				/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/
#include "\src\atlanta\define\sysdoc.h"					/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/
#include "\src\atlanta\define\lst_def.h"				/*	カバーページ送信のため By Y.Suzuki 1996/10/01 */
#include "\src\atlanta\define\mon_pro.h"
/* #include "\src\atlanta\ext_v\fcm_data.h" */
#include "\src\atlanta\define\uni_pro.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#endif

#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[Ｇ３／ＥＣＭキャラクタ送信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[
		300DPIのＴＴＩ対応 By Y.Suzuki 1997/09/30
	]
	machine		:[704X]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/16]
	author		:[鈴木郁二]
*************************************************************************/
/* UWORD SCD_EOL_WriteCount = 0;		@*	By Y.Suzuki 1997/04/14	*/
/* スタックオーバーフロー対策 By Y.Suzuki 1998/02/10 */
static struct	SYS_DocBlockData_t	*tti_docp = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*tti_tmp = {0};				/* B Section By O.Kimoto 1998/08/28 */
static UBYTE tti_bit = 0;								/* B Section By O.Kimoto 1998/08/28 */
static UBYTE tti_bit_cnt = 0;							/* B Section By O.Kimoto 1998/08/28 */
static UWORD	tti_write_data = 0;						/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*tti_mr_ref_buf = {0};		/* B Section By O.Kimoto 1998/08/28 */
static UDWORD	tti_byte_cnt = 0;						/* B Section By O.Kimoto 1998/08/28 */
static UBYTE 	tti_white_line_no = 0;					/* B Section By O.Kimoto 1998/08/28 */
void SF_ECM_CharTx(	struct CdcBlk_t *ecp,		/* ソフトコーデックパラメータ */
					struct WorkBuf_t *char_a,	/* 参照ラインバッファのポインタ */
					struct WorkBuf_t *char_b)	/* 符合化ラインバッファのポインタ */
{
	/* int		header;*/
	int		i, j, mode_cnt;
#if (0)/*By Y.Suzuki 1998/02/10 */
//	struct	SYS_DocBlockData_t	*docp;
//	struct	WorkBuf_t	*tmp;
//	UBYTE bit,bit_cnt;
//	UWORD	write_data;
//	struct	WorkBuf_t	*mr_ref_buf;
//	UDWORD	byte_cnt;
//	UBYTE 	white_line_no;
#endif

	tti_mr_ref_buf = &RL3;
	tti_docp = &SYS_DocBlock;
	if (tti_docp->Dst.Mode == SYS_NORMAL) {
		mode_cnt = 1;
	}
	else if ((tti_docp->Dst.Mode == SYS_HFINE) || (tti_docp->Dst.Mode == SYS_SFINE) ||(tti_docp->Dst.Mode ==SYS_E_HFINE)) {
		mode_cnt = 4;
	}
	else if (tti_docp->Dst.Mode == SYS_EFINE) {/* R12 * 11.55l/mm TTI LINE 48LINE */
		mode_cnt = 3;
	}
	else {	/* docp->dst.d_mode == FINE or GREY */
		mode_cnt = 2;
	}
	if (CHK_UNI_TTI_Size() && (mode_cnt > 1)) {
		/**	ファイン、Ｓファイン時副走査方向１／２にする	*/
		mode_cnt /= 2;
	}
	LST_SetTTI_Image(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);/* ＴＴＩイメージをセット */
	char_a->Cout = 0;
	char_b->Cout = 0;
	tti_mr_ref_buf->Cout = 0;

	PutRL(char_b,ecp->Img_Size,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/03/22	*/
	PutRL(char_a,ecp->Img_Size,0);		/*	MMR用参照ラインクリア By Y.Suzuki 1997/08/25	*/
	PutRL(tti_mr_ref_buf,ecp->Img_Size,0);	/*	MMR用参照ラインクリア By Y.Suzuki 1997/08/25	*/

	/* ファイン/Ｓファイン時のＴＴＩ主走査圧縮時にポプラ同士で交信した場合、受信側でＴＴＩの頭が欠ける対策 By Y.Suzuki 1997/08/18 */
	if (CHK_UNI_TTI_Size() && (tti_docp->Dst.Mode != SYS_NORMAL)) {
		if (mode_cnt == 1) { /* Fine */
			if (!SYB_MaintenanceSwitch[MNT_SW_F5])
				tti_white_line_no = 16;
			else
				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
		}
		else if (mode_cnt == 2){
			if (!SYB_MaintenanceSwitch[MNT_SW_F5])
				tti_white_line_no = 32;
			else
				tti_white_line_no = SYB_MaintenanceSwitch[MNT_SW_F5];
		}
		while(tti_white_line_no) {
			Ecm_Encode(ecp, char_a,tti_mr_ref_buf);
			if(SCD_DBG_PMODE == 5) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
			}
			if(SCD_DBG_ENC_RLSIZE == 1) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
			}
			if(SCD_DBG_ENC_RLSIZE == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
			}
			tti_white_line_no--;
		}
	}
	for(i = 0; i < 16; i++) {
		Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],char_a,tti_docp->Dst.Size);
		/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
		Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],tti_mr_ref_buf,tti_docp->Dst.Size);
		/** 1ラインエンコード */
		SCD_EOL_WriteCount++;		/*	By Y.Suzuki 1997/04/14	*/
		Ecm_Encode(ecp, char_a, char_b);/* char_a(符号化ライン)､char_b(参照ライン) */
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
			SCD_EOL_WriteCount++;		/*	By Y.Suzuki 1997/04/14	*/
			Ecm_Encode(ecp, char_a,tti_mr_ref_buf);
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
		tti_tmp = char_b;
		char_b = char_a;
		char_a = tti_tmp;	/* 符号化ライン→参照ライン */
	}
	/* ＴＴＩに漢字が使われた時のため全白ライン挿入By Y.Suzuki 1997/05/14 */
	/* 漢字フォントは、１６ライン目もデータあり */
	char_a->Cout = 0;
	PutRL(char_a,ecp->Img_Size,0);
	SCD_EOL_WriteCount++;		/*	By Y.Suzuki 1997/04/14	*/
	Ecm_Encode(ecp, char_a, char_b);/* char_a(符号化ライン)､char_b(参照ライン) */

	/*	スキャナ送信の時は、符号の最後がバイトバウンダリーとなるようにする	*/
	if (SYS_FaxComTxType == SYS_SCANNER_TX) {
		tti_bit_cnt = 0;/* クリア ！！ By Y.Suzuki 1997/08/28 */
		if (ecp->Wp->Bit != 0x01) {
			tti_bit = ecp->Wp->Bit;
			while (tti_bit != 0x01) {
				tti_bit_cnt++;
				if (tti_bit == 0x80) {
					tti_bit = 0x01;
					break;
				}
				else {
					tti_bit <<= 1;
				}
			}
			if (tti_docp->Dst.Code == SYS_MMR_CODE) {
				tti_write_data = 0xffff;
			}
			else {
				tti_write_data = 0;
			}
			if (tti_bit_cnt) {
				EcmWrite(ecp->Wp,tti_bit_cnt,tti_write_data);
			}
		}
		tti_byte_cnt = ecp->Wp->Adr;
		if (tti_byte_cnt % 2) {/* ワードバウンダリにしてみる By Y.Suzuki 1997/05/13 */
			tti_bit_cnt = 8;
			if (tti_docp->Dst.Code == SYS_MMR_CODE) {
				tti_write_data = 0xffff;
			}
			else {
				tti_write_data = 0;
			}
			EcmWrite(ecp->Wp,tti_bit_cnt,tti_write_data);
		}
	}
}



/*************************************************************************
	module		:[カバーページ送信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC(Ver3.0F)]
	keyword		:[SCD]
	date		:[1996/10/01]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_TxCoverPage(	struct CdcBlk_t *ecp,		/* ソフトコーデックパラメータ */
					struct WorkBuf_t *char_a,	/* 参照ラインバッファのポインタ */
					struct WorkBuf_t *char_b)	/* 符合化ラインバッファのポインタ */
{
	/* int		header;*/
	int		i, j, mode_cnt;
	struct	SYS_DocBlockData_t	*docp;
	struct	WorkBuf_t	*tmp;
	UBYTE line_cnt;
	struct	WorkBuf_t	*mr_ref_buf;

	mr_ref_buf = &RL3;
	docp = &SYS_DocBlock;
	/* Ｅ＿ＦＩＮＥ/Ｅ＿Ｈ＿ＦＩＮＥの処理をいれるBy Y.Suzuki 1997/12/18 */
	if (docp->Dst.Mode == SYS_NORMAL) {
		mode_cnt = 1;
	}
	else if ((docp->Dst.Mode == SYS_HFINE)||(docp->Dst.Mode == SYS_SFINE)||(docp->Dst.Mode ==SYS_E_HFINE)) {
		mode_cnt = 4;
	}
	else if (docp->Dst.Mode == SYS_EFINE) {/* R12 * 11.55l/mm TTI LINE 48LINE */
		mode_cnt = 3;
	}
	else {	/* docp->dst.d_mode == FINE or GREY */
		mode_cnt = 2;
	}
	CodecPageStatus = CDC_CONTINUE;			/**	初期化 By Y.Suzuki 1997/10/30	*/
	for (line_cnt = 1; line_cnt <= CVR_LINES; line_cnt++) {
#if (0)
//#if (PRO_PRINT_TYPE == LED)
//		LST_SetCoverPage_Image(line_cnt, &FontImageBuffer[CDC_CHARACTER_TX][0][0]);
//#else
//		LST_SetCoverPage_Image(line_cnt, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
#endif
		LST_SetCoverPage_Image(line_cnt, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		for(i = 0; i < 16; i++) {
#if (0)
//#if (PRO_PRINT_TYPE == LED)
//			Img2Rl(&FontImageBuffer[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
//			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
//			Img2Rl(&FontImageBuffer[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
//#else
//			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
//			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
//			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
#endif
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
			/** 1ラインエンコード ,モデム用ＲＡＭにライト */
			Ecm_Encode(ecp, char_a, char_b);/* char_a(符号化ライン)､char_b(参照ライン) */
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
				Ecm_Encode(ecp, char_a, mr_ref_buf);
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
			tmp = char_b;
			char_b = char_a;
			char_a = tmp;	/* 符号化ライン→参照ライン */
		}
	}
	WriteRtcToEcm(ecp);
	CodecPageStatus = CDC_RTC_DET;
	if(!TxStartFlag) {
		TxStartFlag = 1;
	}
}


/*************************************************************************
	module		:[受領証送信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC(Ver3.0F)]
	keyword		:[SCD]
	date		:[1996/10/01]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_TxRCR(		struct CdcBlk_t *ecp,		/* ソフトコーデックパラメータ */
					struct WorkBuf_t *char_a,	/* 参照ラインバッファのポインタ */
					struct WorkBuf_t *char_b)	/* 符合化ラインバッファのポインタ */
{
	int		i, j, mode_cnt;
	struct	SYS_DocBlockData_t	*docp;
	struct	WorkBuf_t	*tmp;
	UBYTE line_cnt;
	struct	WorkBuf_t	*mr_ref_buf;

	mr_ref_buf = &RL3;
	docp = &SYS_DocBlock;
	/* Ｅ＿ＦＩＮＥ/Ｅ＿Ｈ＿ＦＩＮＥの処理をいれるBy Y.Suzuki 1997/12/18 */
	if (docp->Dst.Mode == SYS_NORMAL) {
		mode_cnt = 1;
	}
	else if ((docp->Dst.Mode == SYS_HFINE)||(docp->Dst.Mode == SYS_SFINE)||(docp->Dst.Mode ==SYS_E_HFINE)) {
		mode_cnt = 4;
	}
	else if (docp->Dst.Mode == SYS_EFINE) {/* R12 * 11.55l/mm TTI LINE 48LINE */
		mode_cnt = 3;
	}
	else {	/* docp->dst.d_mode == FINE or GREY */
		mode_cnt = 2;
	}
	CodecPageStatus = CDC_CONTINUE;			/**	初期化 By Y.Suzuki 1997/10/30	*/
	for (line_cnt = 1; line_cnt <= RCR_LINES; line_cnt++) {
#if (0)
//#if (PRO_PRINT_TYPE == LED)
//		LST_SetRCR_Image(line_cnt, &FontImageBuffer[CDC_CHARACTER_TX][0][0]);
//#else
//		LST_SetRCR_Image(line_cnt, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
#endif
		LST_SetRCR_Image(line_cnt, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0]);
		for(i = 0; i < 16; i++) {
#if (0)
//#if (PRO_PRINT_TYPE == LED)
//			Img2Rl(&FontImageBuffer[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
//			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
//			Img2Rl(&FontImageBuffer[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
//#else
//			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
//			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
//			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
#endif
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],char_a,docp->Dst.Size);
			/*	符号化ラインと参照ラインが同じＲＬの内容の場合 By Y.Suzuki 1996/10/28	*/
			Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0],mr_ref_buf,docp->Dst.Size);
			/** 1ラインエンコード  */
			Ecm_Encode(ecp, char_a, char_b);/* char_a(符号化ライン)､char_b(参照ライン) */
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
			/*	Ecm_Encode(ecp, char_a, char_b);*/
				Ecm_Encode(ecp, char_a, mr_ref_buf);
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
			tmp = char_b;
			char_b = char_a;
			char_a = tmp;	/* 符号化ライン→参照ライン */
		}
	}
	WriteRtcToEcm(ecp);
	CodecPageStatus = CDC_RTC_DET;
	if(!TxStartFlag) {
		TxStartFlag = 1;
	}
}
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/


/*************************************************************************
	module		:[ソフトコーデックキャラクタ送信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1996/10/29]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_CTxCodeConvertPageTask(void)
{
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	struct CdcBlk_t encdata,*Sedp;
	struct WorkBuf_t *a_buf;
	struct WorkBuf_t *b_buf;

	Sedp = &encdata;
	CodecPageStatus = CDC_READY;
	EncodeDataCount = 0;
	Sedp->BufMode = ECM_BUF;

	SoftEncodeInitial(Sedp);
	RlBufInit(Sedp->Img_Size);
	a_buf = &RL1;
	b_buf = &RL2;

	SCD_TxMode = TxMode;

	switch (TxSmType) {
	case TX_RCR:
		SCD_TxRCR(Sedp,a_buf,b_buf);
		break;
	case TX_CVR:
	/*------------------------------------------*/
	/*	ＥＣＭバッファにカバーページをセット	*/
	/*------------------------------------------*/
		SCD_TxCoverPage(Sedp,a_buf,b_buf);
		break;
	default:
		break;
	}
	wai_tsk(0xFFFF);
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
}
