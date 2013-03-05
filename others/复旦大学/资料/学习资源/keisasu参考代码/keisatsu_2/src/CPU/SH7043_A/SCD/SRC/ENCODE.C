/************************************************************************
*	System		: POPLAR
*	File Name	: ENCODE.C
*	Author		: 王 慎 Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
 #endif
#endif
#include "\src\atlanta\define\std.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h"
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scd_tbl.h"
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scdpro.h"
#endif

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/08/27 */
** #include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#else
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#endif

/*#include "\src\atlanta\ext_v\bkupram.h"*/
/*#include "\src\atlanta\define\mntsw_f.h"*/

/*************************************************************
	module		:[Mem_Encode]
	function	:[one line MH,MR,MMR ｴﾝｺｰﾄﾞ ]
	return		:[
	             OK
	             RX_MEM_OVER
	             ]
	common		:[]
	condition	:[]
	comment		:[1 line encede]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/10/14]
	author		:[王　慎]
*************************************************************/
/*	Debug sw By Y.Suzuki 1997/01/27	*/
/* static UBYTE	SCD_DBG_PMODE = 0; */
/* static UBYTE	SCD_DBG_ENC_RLSIZE = 0;*/

UBYTE Mem_EncodeIntRom(struct CdcBlk_t *enc,
			struct WorkBuf_t *a_buf,
			struct WorkBuf_t *b_buf)
{
	struct ScdcWorkData_t scdcdata, *scdcwork;
	UWORD rl_a;							 /*  走査ライン run length */
	UWORD rl_b;							 /*  参照ライン run length */
	WORD  d;			                 /*  a1 - b1 */

	SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
	SCD_DBG_ENC_RLSIZE = 0;		/*	By Y.Suzuki 1997/01/29	*/

	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	a_buf->Cout = 0;
	a_buf->Flag = 0;  /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0;

	if ((enc->Coding != SYS_MMR_CODE) && ((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE))) {	  /* MH ENCODE For Performance measurement by S.Wang 96/03/28 */
	/*if (((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE)) && (enc->Coding != SYS_MMR_CODE)) 	  * MH ENCODE */
		if (enc->Coding == SYS_MH_CODE) {
			if (Mem_EOLWrite(EOL_NO, enc, scdcwork->a_color) == RX_MEM_OVER) {	     /* EOL 書き込む */
				return(RX_MEM_OVER);
			}
		}
		else {
			if (Mem_EOLWrite(EOL_MH_NO, enc, scdcwork->a_color) == RX_MEM_OVER) {	 /* EOL_MH 書き込む */
				return(RX_MEM_OVER);
			}
		}
		do { /* 1 line MHencode */
			rl_a = GetRL(a_buf);                                                     /* イメージバッファよりrl取り出す */
			scdcwork->a_pos += rl_a;
			if (scdcwork->a_pos > enc->Img_Size) {
				return(RL_OVER); /* for debug */
			}
			if (Mem_RLToMHWrite(rl_a, enc, scdcwork->a_color) == RX_MEM_OVER) {
				return(RX_MEM_OVER);
			}
			if (scdcwork->a_pos == enc->Img_Size) {
				break;
			}
			scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
		}while (scdcwork->a_pos != enc->Img_Size);
	}
	else { /* 1 line MR/MMR ENCODE */
		if (enc->Coding == SYS_MR_CODE) {
			if (Mem_EOLWrite(EOL_MR_NO, enc, scdcwork->a_color) == RX_MEM_OVER) {     /* EOL_MR 書き込む */;
				return(RX_MEM_OVER);
			}
		}
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->a2 = 0;
		scdcwork->b0 = 0;
		scdcwork->b1 = 0;
		scdcwork->b2 = 0;
		do {
#if(0)		/* 以下の5行に変更してみる By S.Wang 96/04/11 */
** 			while (scdcwork->a1 <= scdcwork->a0) {
** 				rl_a = GetRL(a_buf);
** 				scdcwork->a_pos += rl_a;
** 				scdcwork->a1 = scdcwork->a_pos;			  /* a1位置更新 */
** 				if ((scdcwork->a1 == 0) && (scdcwork->a0 == 0)) { /* 符号化ラインの頭は黒の時(白RL=0) */
** 					break;
** 				}
** 			}	/* a1 検出した */
#endif
			if (scdcwork->a1 <= scdcwork->a0) {
				rl_a = GetRL(a_buf);
				scdcwork->a_pos += rl_a;
				scdcwork->a1 = scdcwork->a_pos;           /* a1位置検出した */
			}
  			while ((scdcwork->b1 <= scdcwork->a0) || ((scdcwork->b1 > scdcwork->a0) && (scdcwork->a_color != scdcwork->b_color))) {
				if (scdcwork->b2 != 0 && scdcwork->b1 < enc->Img_Size) {
					scdcwork->b0 = scdcwork->b1;          /* b0位置更新 */
					scdcwork->b1 = scdcwork->b2;          /* b1位置更新 */
					if (scdcwork->b1 != enc->Img_Size) {
						rl_b = GetRL(b_buf);
						scdcwork->b2 += rl_b;             /* b2位置更新 */
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					}
					else {
						/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/08/21	*/
						if (scdcwork->a_color != scdcwork->b_color) {
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						}
						break;
					}
				}
				else if ((scdcwork->b1 == 0) && (scdcwork->b2 == 0)) {		      /* 参照Lineの最初位置の時 */
					rl_b = GetRL(b_buf);
					scdcwork->b1 = rl_b;			      /* b1位置更新 */
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b1 == enc->Img_Size) {
						scdcwork->b2 = enc->Img_Size;
						break;
					}
					else {
						rl_b = GetRL(b_buf);			  /* b2位置更新 */
						scdcwork->b2 = scdcwork->b1 + rl_b;
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						break; 							  /* whileから抜ける S.Wang 96/04/03 */
					}
				}
				else { 	  /* 参照Lineの最後位置の時 */
				    break;
				}
			}	/* b1, b2 検出した */
			if (scdcwork->a1 > scdcwork->b2) {                           /* Pass mode */
				SCD_DBG_PMODE = 1;/*	Debug sw By Y.Suzuki 1997/01/27	*/
				if (Mem_MRDataWrite(P_MODE, enc) == RX_MEM_OVER) {  /* Pass mode MRデータを格納する */
					return(RX_MEM_OVER);
				}
				scdcwork->a0 = scdcwork->b2;
			}
			else {
				d = scdcwork->a1 - scdcwork->b1;
				if (-3 <= d && d <= 3) {              /* Vertical mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
					if (Mem_MRDataWrite((UBYTE)(V0_MODE + d), enc) == RX_MEM_OVER) {
						return(RX_MEM_OVER);
					}
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (d < -1) {     /* VL(2) or VL(3) modeの特例 次の参照ラインb1の検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
							if (rl_b >= 64) {  /* rl_bは２バイド時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b2 = scdcwork->b1;
							scdcwork->b1 = scdcwork->b0;
						}
					}
				}
				else {                                /* Horizontal mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
					if (Mem_MRDataWrite(H_MODE, enc) == RX_MEM_OVER) {		  /* Horizontal mode MRデータを格納する */
						return(RX_MEM_OVER);
					}
					if (Mem_RLToMHWrite((scdcwork->a1-scdcwork->a0), enc, scdcwork->a_color) == RX_MEM_OVER) {  /* MH(a1-a0) */
						return(RX_MEM_OVER);
					}
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					rl_a = GetRL(a_buf);
					scdcwork->a_pos += rl_a;
					scdcwork->a2 = scdcwork->a_pos;
					if (scdcwork->a2 >= enc->Img_Size) {
				 		scdcwork->a2 = enc->Img_Size;
					} /* 意味はあまりないので削除する S.Wang 96.03.12 必要！！ By Y.Suzuki 1997/09/26 */
					if (Mem_RLToMHWrite((scdcwork->a2-scdcwork->a1), enc, scdcwork->a_color) == RX_MEM_OVER) {       /* MH(a2-a1) */
						return(RX_MEM_OVER);
					}
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->a0 = scdcwork->a2;
				}
			}
		/*	if (scdcwork->a0 > enc->Img_Size) {
		**		return(RL_OVER);  for debug コメントにする By Y.Suzuki 1997/10/02
			}*/
		}while(scdcwork->a0 < enc->Img_Size);
	} 							/*  1 line MR/MMR ENCODE end */
	if (SCD_DBG_PMODE != 0) {/*	Debug sw By Y.Suzuki 1997/01/27	*/
		SCD_DBG_PMODE = 5;
	}

	if ((enc->Coding != SYS_MMR_CODE) && ((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE))) {	  /* MH ENCODE For Performance measurement by S.Wang 96/03/28 */
		/*	ＭＨラインの場合	*/
		if (scdcwork->a_pos > enc->Img_Size) {/*	By Y.Suzuki 1997/01/29	*/
			SCD_DBG_ENC_RLSIZE = 3;
		}
	}
	else {
		if(scdcwork->a0 > enc->Img_Size) {/*	By Y.Suzuki 1997/01/29	*/
			SCD_DBG_ENC_RLSIZE = 1;
		}
	}
	enc->Line_Cntr ++; 			/* ｺｰﾃﾞｯｸライン数Countのincrement */
	return(OK);
}

/***************************************************************************
	module		:[ＭＨデータの書き込み]
	function	:[
		1.　指定されたＲＬはＭＨエンコードテーブル配列Ｎｏ．を求めてＭＨデータの書き込み]
		2.2560以上のRLがきた場合の処理追加 By Y.Suzuki 1996/12/03

	return		:[RX_MEM_OVER, OK]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/
UBYTE Mem_RLToMHWrite(UWORD rl, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UBYTE	mhbits2;
	UWORD 			mhdata1;
	UWORD 			mhdata2;

	while (1) {
		if (rl < 64) {				/* ＭＨ符号データはﾀｰﾐﾈｲﾃｨﾝｸﾞ時ﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl].BitLength;
			}
			if (MemWrite(point->Wp, mhbits1, mhdata1) == RX_MEM_OVER) {
				return(RX_MEM_OVER);
			}
			return(OK);
		}
	/*	else if ((rl >= 64) && (rl <= point->Img_Size)) [ @* ＭＨ符号データメイクアップのとき */
		else if ((rl < MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* ＭＨ符号データメイクアップのとき */
		/*	By Y.Suzuki 1997/01/23	*/
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_WhiteTableMain[rl%64].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_WhiteTableMain[rl%64].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_BlackTableMain[rl%64].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_BlackTableMain[rl%64].BitLength;
			}
			if (MemWrite(point->Wp, mhbits1, mhdata1) == RX_MEM_OVER) {  /* 最初のＭＨ符号データを求める */
				return(RX_MEM_OVER);
			}
			if (MemWrite(point->Wp, mhbits2, mhdata2) == RX_MEM_OVER) {  /* 最後のＭＨ符号データをターミネートテーブルで求める */
				return(RX_MEM_OVER);
			}
			return(OK);
		}
		else if ((rl >= MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* RL > 2560の場合 */
			do {
				rl -= MH_MAKEUP_MAX;
				if (a_color == WHITE) {
					mhdata1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				else {
					mhdata1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				if (MemWrite(point->Wp, mhbits1, mhdata1) == RX_MEM_OVER) {  /* 最初のＭＨ符号データを求める */
					return(RX_MEM_OVER);
				}
				if (rl == 0) {
					if (MemWrite(point->Wp, mhbits2, mhdata2) == RX_MEM_OVER) {  /* 最後のＭＨ符号データをﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
						return(RX_MEM_OVER);
					}
					return(OK);
				}
			}while (rl >= MH_MAKEUP_MAX);
		}
		else {/*	ここにきたらNG By Y.Suzuki 1997/01/30	*/
			SCD_DBG_ENC_RLSIZE = 2;
			break;
		}
	}	/* while (1) */
}

/*********************************************************************************
	module		:[ＥＯＬデータの書き込み]
	function	:[
		1.　指定されたＭＨエンコードテーブル配列Ｎｏ．のＥＯＬデータを書き込む．
	]
	return		:[RX_MEM_OVER, OK]
	common		:[]
	condition	:[]
	comment		:[ XX 00 X8 のようにＥＯＬをｾｯﾄしないとＥＯＬを検出できませんので
	               ０のﾋﾞｯﾄ数をenc->Wp->Bitのﾋﾞｯﾄ調整 96/05/13 S.Wang (requested by Y.Suzuki)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
**********************************************************************************/

UBYTE Mem_EOLWrite(UWORD eol, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UWORD		 	mhdata1;

	if (a_color == WHITE) {
		mhdata1 = MH_EC_WhiteTableMain[eol].MHData;
		mhbits1 = MH_EC_WhiteTableMain[eol].BitLength;
	}
	else {
		mhdata1 = MH_EC_BlackTableMain[eol].MHData;
		mhbits1 = MH_EC_BlackTableMain[eol].BitLength;
	}
	switch(point->Wp->Bit) { /* 96/05/13 S.Wang (requested by Y.Suzuki) */
	case 0x01:
		 break;
	case 0x02:
		if (MemWrite(point->Wp, 7, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x04:
		if (MemWrite(point->Wp, 6, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x08:
		if (MemWrite(point->Wp, 5, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x10:
		if (MemWrite(point->Wp, 4, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x20:
		if (MemWrite(point->Wp, 3, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x40:
		if (MemWrite(point->Wp, 2, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	case 0x80:
		if (MemWrite(point->Wp, 1, 0x00) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		break;
	default:
		break;
	}
	if (MemWrite(point->Wp, mhbits1, mhdata1) == RX_MEM_OVER) {
		return(RX_MEM_OVER);
	}
}

/***************************************************************************
	module		:[ＭＲデータの書き込み]
	function	:[
		1.　指定されたＭＲエンコードのＭＲデータを書き込む．
	]
	return		:[RX_MEM_OVER, OK]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
****************************************************************************/

UBYTE Mem_MRDataWrite(UBYTE code, struct CdcBlk_t *point)	/* MR code */
{
	UBYTE	mrcode;
	UBYTE	mrbits;

	mrcode = MR_EC_TableMain[code].MRData;
	mrbits = MR_EC_TableMain[code].BitLength;
	if (MemWrite(point->Wp, mrbits, mrcode) == RX_MEM_OVER) {
		return(RX_MEM_OVER);
	}
}

/*************************************************************
	module		:[G3_Encode]
	function	:[one line MH,MR,MMR ｴﾝｺｰﾄﾞ ]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[1 line encede]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/10/14]
	author		:[王　慎]
*************************************************************/

void G3_EncodeIntRom(struct CdcBlk_t *enc,
			struct WorkBuf_t *a_buf,
			struct WorkBuf_t *b_buf)
{
	struct ScdcWorkData_t scdcdata, *scdcwork;
	UWORD rl_a;							 /*  走査ライン run length */
	UWORD rl_b;							 /*  参照ライン run length */
	WORD  d;			                 /*  a1-b1 */

	/*	フィルセット用 By Y.Suzuki 1997/04/03	*/
	UWORD set_byte_num;
	UWORD set_word_num;
	UBYTE bit_cnt;


	SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
	SCD_DBG_ENC_RLSIZE = 0;		/*	By Y.Suzuki 1997/01/29	*/

	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	a_buf->Cout = 0;
	a_buf->Flag = 0;  /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0;

	if ((enc->Coding != SYS_MMR_CODE) && ((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE))) {	  /* MH ENCODE For Performance measurement by S.Wang 96/03/28 */
	/*if (((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE)) && (enc->Coding != SYS_MMR_CODE)) 	  @* MH ENCODE */
		if (enc->Coding == SYS_MH_CODE) {
			/*SetFill(enc); 修正　S.Wang 96/03/21 */
			G3_EOLWrite(EOL_NO, enc, scdcwork->a_color) ;	 /* EOL 書き込む */
		}
		else {
			/*SetFill(enc); 修正　S.Wang 96/03/21 */
			G3_EOLWrite(EOL_MH_NO, enc, scdcwork->a_color);	 /* EOL_MH 書き込む */
		}
		do { /* 1 line MHencode */
			rl_a = GetRL(a_buf);  							/* イメージバッファよりrl取り出す */
			scdcwork->a_pos += rl_a;
			G3_RLToMHWrite(rl_a, enc, scdcwork->a_color);
			if (scdcwork->a_pos >= enc->Img_Size) {
			    break;
			}
			scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
		}while (scdcwork->a_pos != enc->Img_Size);
	}
	else { /* 1 line MR/MMR ENCODE */
		if (enc->Coding == SYS_MR_CODE) {
			/*SetFill(enc); 修正　S.Wang 96/03/21 */
			G3_EOLWrite(EOL_MR_NO, enc, scdcwork->a_color); /* EOL_MR 書き込む */
		}
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->a2 = 0;
		scdcwork->b0 = 0;
		scdcwork->b1 = 0;
		scdcwork->b2 = 0;
		do {
#if(0)		/* 以下の5行に変更してみる By S.Wang 96/04/11 */
//			while (scdcwork->a1 <= scdcwork->a0) {
//				rl_a = GetRL(a_buf);
//				scdcwork->a_pos += rl_a;
//				scdcwork->a1 = scdcwork->a_pos;			  /* a1位置更新 */
//				if ((scdcwork->a1 == 0) && (scdcwork->a0 == 0)) { /* 符号化ラインの頭は黒の時(白RL=0) */
//					break;
//				}
//			}	/* a1 検出した */
#endif
			if (scdcwork->a1 <= scdcwork->a0) {
				rl_a = GetRL(a_buf);
				scdcwork->a_pos += rl_a;
				scdcwork->a1 = scdcwork->a_pos;           /* a1位置検出した */
			}
			while ((scdcwork->b1 <= scdcwork->a0) || ((scdcwork->b1 > scdcwork->a0) && (scdcwork->a_color != scdcwork->b_color))) {
				if (scdcwork->b2 != 0 && scdcwork->b1 < enc->Img_Size) {
					scdcwork->b0 = scdcwork->b1;		  /* b0位置更新 */
					scdcwork->b1 = scdcwork->b2;		  /* b1位置更新 */
					if (scdcwork->b1 != enc->Img_Size) {
						rl_b = GetRL(b_buf);
						scdcwork->b2 += rl_b;		      /* b2位置更新 */
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					}
					else {
						/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/08/21	*/
						if (scdcwork->a_color != scdcwork->b_color) {
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						}
						break;
					}
				}
				else if ((scdcwork->b1 == 0) && (scdcwork->b2 == 0)) {				  /* 参照Lineの最初位置の時 */
					rl_b = GetRL(b_buf);
					scdcwork->b1 = rl_b;				  /* b1位置更新 */
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b1 == enc->Img_Size) {
						scdcwork->b2 = enc->Img_Size;
						break;
					}
					else {
						rl_b = GetRL(b_buf);			  /* b2位置更新 */
						scdcwork->b2 = scdcwork->b1 + rl_b;
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						break; 							  /* whileから抜ける S.Wang 96/04/03 */
	  				}
				}
				else {	  /* 参照Lineの最後位置の時 */
				    break;
				}
			}	/* b1, b2 検出した */
			if (scdcwork->a1 > scdcwork->b2) {                           /* Pass mode */
				SCD_DBG_PMODE = 1;/*	Debug sw By Y.Suzuki 1997/01/27	*/
				G3_MRDataWrite(P_MODE, enc);							  /* Pass mode MRデータを格納する */
				scdcwork->a0 = scdcwork->b2;
			}
			else {
				d = scdcwork->a1 - scdcwork->b1;
				if (-3 <= d && d <= 3) {              /* Vertical mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
					G3_MRDataWrite((UBYTE)(V0_MODE + d), enc);
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (d < -1) {     /* VL(2) or VL(3) modeの特例 次の参照ラインb1の検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
							if (rl_b >= 64) {  /* rl_bは２バイド時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b2 = scdcwork->b1;
							scdcwork->b1 = scdcwork->b0;
						}
					}
				}
				else {                                /* Horizontal mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/01/27	*/
					G3_MRDataWrite(H_MODE, enc);	  /* Horizontal mode MRデータを格納する */
					G3_RLToMHWrite((scdcwork->a1-scdcwork->a0), enc, scdcwork->a_color);   /* MH(a1-a0) */
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					rl_a = GetRL(a_buf);
					scdcwork->a_pos += rl_a;
					scdcwork->a2 = scdcwork->a_pos;
					/* 意味はあまりないので削除する S.Wang 96.03.12 必要！！ By Y.Suzuki 1997/09/29 */
					if (scdcwork->a2 >= enc->Img_Size) {
				 		scdcwork->a2 = enc->Img_Size;
					}
					G3_RLToMHWrite((scdcwork->a2-scdcwork->a1), enc, scdcwork->a_color);       /* MH(a2-a1) */
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->a0 = scdcwork->a2;
				}
			}
		}while(scdcwork->a0 < enc->Img_Size);
	} 														/*  1 line MR/MMR ENCODE end */
	/*	Ｇ３フィルの処理	By Y.Suzuki 1997/04/03	*/
	if((SCD_MinimumLineSize) && (SCD_MinimumLineSize != 0xFFFF)) {
		/*	最小電送時間 ０ｍｓ以外 ＭＳＥではない。	*/
		if(enc->Coding != SYS_MMR_CODE) {
			if(LineByteCnt < SCD_MinimumLineSize) {
				set_byte_num = SCD_MinimumLineSize - LineByteCnt;
				set_word_num = set_byte_num/2;
				set_byte_num %= 2;
				if(set_byte_num) {
					set_word_num++;
				}
				/* フィルを多めにセットする By Y.suzuki 97/7/14 */
				if (SCD_MaintenanceSwitch[SCD_MNT_SW_F4]) {
					set_word_num += SCD_MaintenanceSwitch[SCD_MNT_SW_F4];
				}
				else {
					set_word_num += 3;
				}
				if(set_word_num) {
					bit_cnt = 16;
					while(set_word_num) {
						EcmWrite(enc->Wp,bit_cnt,0);
						set_word_num--;
					}
				}
			}
		}
	}
	LineByteCnt = 0;
	/*	ここまで	By Y.Suzuki 1997/04/03	*/

	if (SCD_DBG_PMODE != 0) {/*	Debug sw By Y.Suzuki 1997/01/27	*/
		SCD_DBG_PMODE = 5;
	}

	if ((enc->Coding != SYS_MMR_CODE) && ((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE))) {	  /* MH ENCODE For Performance measurement by S.Wang 96/03/28 */
		/*	ＭＨラインの場合	*/
		if (scdcwork->a_pos > enc->Img_Size) {/*	By Y.Suzuki 1997/01/29	*/
			SCD_DBG_ENC_RLSIZE = 3;
		}
	}
	else {
		if(scdcwork->a0 > enc->Img_Size) {/*	By Y.Suzuki 1997/01/29	*/
			SCD_DBG_ENC_RLSIZE = 1;
		}
	}
	enc->Line_Cntr ++; 										/* ｺｰﾃﾞｯｸライン数Countのincrement */
}

/***************************************************************************
	module		:[ＭＨデータの書き込み]
	function	:[
		1.　指定されたＲＬはＭＨエンコードテーブル配列Ｎｏ．を求めてＭＨデータの書き込み]

	return		:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/
void G3_RLToMHWrite(UWORD rl, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UBYTE	mhbits2;
	UWORD 	mhdata1;
	UWORD 	mhdata2;

	while (1) {
		if (rl < 64) {				/* ＭＨ符号データはﾀｰﾐﾈｲﾃｨﾝｸﾞ時ﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl].BitLength;
			}
			MdmWrite(point->Wp, mhbits1, mhdata1);
		}
	/*	else if ((rl >= 64) && (rl <= point->Img_Size)) [ @* ＭＨ符号データはNotﾀｰﾐﾈｲﾃｨﾝｸﾞとき */
		else if ((rl < MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* ＭＨ符号データメイクアップのとき */
		/*	By Y.Suzuki 1997/01/23	*/
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_WhiteTableMain[rl%64].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_WhiteTableMain[rl%64].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_BlackTableMain[rl%64].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_BlackTableMain[rl%64].BitLength;
			}
			MdmWrite(point->Wp, mhbits1, mhdata1);  /* 最初のＭＨ符号データを求める */
			MdmWrite(point->Wp, mhbits2, mhdata2);  /* 最後のＭＨ符号データをﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
		}
		else if ((rl >= MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* RL > 2560の場合 */
			do {
				rl -= MH_MAKEUP_MAX;
				if (a_color == WHITE) {
					mhdata1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				else {
					mhdata1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				MdmWrite(point->Wp, mhbits1, mhdata1); /* 最初のＭＨ符号データを求める */
				if (rl == 0) {
					MdmWrite(point->Wp, mhbits2, mhdata2);  /* 最後のＭＨ符号データをﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
					return;
				}
			}while (rl >= MH_MAKEUP_MAX);
		}
		else {/*	ここにきたらNG By Y.Suzuki 1997/01/30	*/
			SCD_DBG_ENC_RLSIZE = 2;
			break;
		}
	}
}

/***************************************************************************
	module		:[ＥＯＬデータの書き込み]
	function	:[
		1.　指定されたＭＨエンコードテーブル配列Ｎｏ．のＥＯＬデータを書き込む．
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ XX 00 X8 のようにＥＯＬをｾｯﾄしないとＥＯＬを検出できませんので
	               ０のﾋﾞｯﾄ数をenc->Wp->Bitのﾋﾞｯﾄ調整 96/05/13 S.Wang (requested by Y.Suzuki)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/

void G3_EOLWrite(UWORD eol, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UWORD 	mhdata1;

	if (a_color == WHITE) {
		mhdata1 = MH_EC_WhiteTableMain[eol].MHData;
		mhbits1 = MH_EC_WhiteTableMain[eol].BitLength;
	}
	else {
		mhdata1 = MH_EC_BlackTableMain[eol].MHData;
		mhbits1 = MH_EC_BlackTableMain[eol].BitLength;
	}
	switch(point->Wp->Bit) { /* 96/05/13 S.Wang (requested by Y.Suzuki) */
	case 0x01:
		break;
	case 0x02:
		MdmWrite(point->Wp, 7, 0x00);
		break;
	case 0x04:
		MdmWrite(point->Wp, 6, 0x00);
		break;
	case 0x08:
		MdmWrite(point->Wp, 5, 0x00);
		break;
	case 0x10:
		MdmWrite(point->Wp, 4, 0x00);
		break;
	case 0x20:
		MdmWrite(point->Wp, 3, 0x00);
		break;
	case 0x40:
		MdmWrite(point->Wp, 2, 0x00);
		break;
	case 0x80:
		MdmWrite(point->Wp, 1, 0x00);
		break;
	default:
		break;
	}
/*	SCD_LastEolAddr = point->Wp->Buf + point->Wp->Adr;*/

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/08/27 */
** 	SCD_LastEolDataCount = EncodeDataCount;
#else
	SCD_LastEolDataCount = *EncodeDataCount_p;
#endif
	MdmWrite(point->Wp, mhbits1, mhdata1);
}

/***************************************************************************
	module		:[ＭＲデータの書き込み]
	function	:[
		1.　指定されたＭＲエンコードのＭＲデータを書き込む．
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/

void G3_MRDataWrite(UBYTE code, struct CdcBlk_t *point)	/* MR code */
{
	UBYTE	mrcode;
	UBYTE	mrbits;

	mrcode = MR_EC_TableMain[code].MRData;
	mrbits = MR_EC_TableMain[code].BitLength;
	MdmWrite(point->Wp, mrbits, mrcode);
}

/*************************************************************
	module		:[Ecm_Encode]
	function	:[one line MH,MR,MMR ｴﾝｺｰﾄﾞ ]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[1 line encede]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1996/03/14]
	author		:[王　慎]
*************************************************************/

void Ecm_EncodeIntRom(struct CdcBlk_t *enc,
			struct WorkBuf_t *a_buf,
			struct WorkBuf_t *b_buf)
{
	struct ScdcWorkData_t scdcdata, *scdcwork;
	UWORD rl_a;							 /*  走査ライン run length */
	UWORD rl_b;							 /*  参照ライン run length */
	WORD  d;			                 /*  a1-b1 */

	/*	フィルセット用 By Y.Suzuki 1997/04/03	*/
	UWORD set_byte_num;
	UWORD set_word_num;
	UBYTE bit_cnt;

	SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/02/01	*/
	SCD_DBG_ENC_RLSIZE = 0;		/*	By Y.Suzuki 1997/02/01	*/

	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	/*scdcwork->b_pos = 0; scdcwork->b_pos使う必要がない。 S.Wang 96/03/15 */
	a_buf->Cout = 0;
	a_buf->Flag = 0;  /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0;

	/*	MMR送信縮小時参照ラインをセット By Y.Suzuki 1997/02/08	*/
	if (enc->Line_Cntr == 0) {
		PutRL(b_buf,enc->Img_Size,0);
		b_buf->Cout = 0;
	}
	if ((enc->Coding != SYS_MMR_CODE) && ((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE))) {	  /* MH ENCODE For Performance measurement by S.Wang 96/03/28 */
	/*if (((enc->Line_Cntr % enc->K_Para == 0) || (enc->Coding == SYS_MH_CODE)) && (enc->Coding != SYS_MMR_CODE)) [	  MEM_ENCODEとあわす By Y.Suzuki 1997/08/19 */
		if (enc->Coding == SYS_MH_CODE) {
			/* SetFill(enc); ECM_Encodeと関係ない */
			Ecm_EOLWrite(EOL_NO, enc, scdcwork->a_color) ;	 /* EOL 書き込む */
		}
		else {
			/* SetFill(enc); ECM_Encodeと関係ない */
			Ecm_EOLWrite(EOL_MH_NO, enc, scdcwork->a_color);	 /* EOL_MH 書き込む */
		}
		do { /* 1 line MHencode */
			rl_a = GetRL(a_buf);  							/* イメージバッファよりrl取り出す */
			scdcwork->a_pos += rl_a;
			Ecm_RLToMHWrite(rl_a, enc, scdcwork->a_color);
			if (scdcwork->a_pos == enc->Img_Size) {
			    break;
			}
			scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
		}while (scdcwork->a_pos != enc->Img_Size);
	}
	else { /* 1 line MR/MMR ENCODE */
		if (enc->Coding == SYS_MR_CODE) {
			/* SetFill(enc); ECM_Encodeと関係ない */
			Ecm_EOLWrite(EOL_MR_NO, enc, scdcwork->a_color); /* EOL_MR 書き込む */
		}
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->a2 = 0;
		scdcwork->b0 = 0;
		scdcwork->b1 = 0;
		scdcwork->b2 = 0;
		do {
#if(0)		/* 以下の5行に変更してみる By S.Wang 96/04/11 */
** 			while (scdcwork->a1 <= scdcwork->a0) {
** 				rl_a = GetRL(a_buf);
** 				scdcwork->a_pos += rl_a;
** 				scdcwork->a1 = scdcwork->a_pos;			  /* a1位置更新 */
** 				if ((scdcwork->a1 == 0) && (scdcwork->a0 == 0)) { /* 符号化ラインの頭は黒の時(白RL=0) */
** 					break;
** 				}
** 			}	/* a1 検出した */
#endif
			if (scdcwork->a1 <= scdcwork->a0) {
				rl_a = GetRL(a_buf);
				scdcwork->a_pos += rl_a;
				scdcwork->a1 = scdcwork->a_pos;           /* a1位置検出した */
			}
  			while ((scdcwork->b1 <= scdcwork->a0) || ((scdcwork->b1 > scdcwork->a0) && (scdcwork->a_color != scdcwork->b_color))) {
				if (scdcwork->b2 != 0 && scdcwork->b1 < enc->Img_Size) {
					scdcwork->b0 = scdcwork->b1;          /* b0位置更新 */
					scdcwork->b1 = scdcwork->b2;          /* b1位置更新 */
					if (scdcwork->b1 != enc->Img_Size) {
						rl_b = GetRL(b_buf);
						scdcwork->b2 += rl_b;             /* b2位置更新 */
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					}
					else {
						/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/08/21	*/
						if (scdcwork->a_color != scdcwork->b_color) {
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						}
						break;
					}
				}
				else if ((scdcwork->b1 == 0) && (scdcwork->b2 == 0)) {		      /* 参照Lineの最初位置の時 */
					rl_b = GetRL(b_buf);
					scdcwork->b1 = rl_b;			      /* b1位置更新 */
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b1 == enc->Img_Size) {
						scdcwork->b2 = enc->Img_Size;
						break;
					}
					else {
						rl_b = GetRL(b_buf);			  /* b2位置更新 */
						scdcwork->b2 = scdcwork->b1 + rl_b;
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
						break; 							  /* whileから抜ける S.Wang 96/04/03 */
					}
				}
				else { 	  /* 参照Lineの最後位置の時 */
				    break;
				}
			}	/* b1, b2 検出した */
			if (scdcwork->a1 > scdcwork->b2) {                           /* Pass mode */
				SCD_DBG_PMODE = 1;/*	Debug sw By Y.Suzuki 1997/02/01	*/
				Ecm_MRDataWrite(P_MODE, enc);							  /* Pass mode MRデータを格納する */
				scdcwork->a0 = scdcwork->b2;
			}
			else {
				d = scdcwork->a1 - scdcwork->b1;
				if (-3 <= d && d <= 3) {              /* Vertical mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/02/01	*/
					Ecm_MRDataWrite((UBYTE)(V0_MODE + d), enc);
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (d < -1) {     /* VL(2) or VL(3) modeの特例 次の参照ラインb1の検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
						/*	else if (rl_b >= 64) {  @* rl_bは２バイド時 */
							if (rl_b >= 64) {  /* rl_bは２バイド時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b2 = scdcwork->b1;
							scdcwork->b1 = scdcwork->b0;
						}
					}
				}
				else {                                /* Horizontal mode */
					SCD_DBG_PMODE = 0;/*	Debug sw By Y.Suzuki 1997/02/1	*/
					Ecm_MRDataWrite(H_MODE, enc);	  /* Horizontal mode MRデータを格納する */
					Ecm_RLToMHWrite((scdcwork->a1-scdcwork->a0), enc, scdcwork->a_color);   /* MH(a1-a0) */
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					rl_a = GetRL(a_buf);
					scdcwork->a_pos += rl_a;
					scdcwork->a2 = scdcwork->a_pos;
					if (scdcwork->a2 >= enc->Img_Size) {
				 		scdcwork->a2 = enc->Img_Size;
					}
					Ecm_RLToMHWrite((scdcwork->a2-scdcwork->a1), enc, scdcwork->a_color);       /* MH(a2-a1) */
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->a0 = scdcwork->a2;
				}
			}
		}while(scdcwork->a0 < enc->Img_Size);
	}
	/*	Ｇ３フィルの処理	By Y.Suzuki 1997/04/03	*/
	if((SCD_MinimumLineSize) && (SCD_MinimumLineSize != 0xFFFF)) {
		/*	最小電送時間 ０ｍｓ以外 ＭＳＥではない。	*/
		if(enc->Coding != SYS_MMR_CODE) {
			if(LineByteCnt <= SCD_MinimumLineSize) {
/*			if(LineByteCnt < SCD_MinimumLineSize) { */
				set_byte_num = SCD_MinimumLineSize - LineByteCnt;
				set_word_num = set_byte_num/2;
				set_byte_num %= 2;
				/* フィルを多めにセットする By Y.suzuki 97/7/14 */
				if (SCD_MaintenanceSwitch[SCD_MNT_SW_F4]) {
					set_word_num += SCD_MaintenanceSwitch[SCD_MNT_SW_F4];
				}
				else {
					set_word_num += 1;
				}
				if(set_byte_num) {
					set_word_num++;
				}
				if(set_word_num) {
					bit_cnt = 16;
					while(set_word_num) {
						EcmWrite(enc->Wp,bit_cnt,0);
						set_word_num--;
					}
				}
			}
		}
	}
	LineByteCnt = 0;
	/*	ここまで	By Y.Suzuki 1997/04/03	*/

	if (SCD_DBG_PMODE != 0) {/*	Debug sw By Y.Suzuki 1997/02/01	*/
		SCD_DBG_PMODE = 5;
	}
	if (scdcwork->a0 > enc->Img_Size) {/*	By Y.Suzuki 1997/02/01	*/
		SCD_DBG_ENC_RLSIZE = 1;
	}
	if (scdcwork->a_pos > enc->Img_Size) {/*	By Y.Suzuki 1997/02/01	*/
		SCD_DBG_ENC_RLSIZE = 1;
	} 														/*  1 line MR/MMR ENCODE end */
	enc->Line_Cntr ++; 										/* ｺｰﾃﾞｯｸライン数Countのincrement */
}

/***************************************************************************
	module		:[ＭＨデータの書き込み]
	function	:[
		1.　指定されたＲＬはＭＨエンコードテーブル配列Ｎｏ．を求めてＭＨデータの書き込み]

	return		:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/
void Ecm_RLToMHWrite(UWORD rl, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UBYTE	mhbits2;
	UWORD 	mhdata1;
	UWORD 	mhdata2;

	while (1) {
		if (rl < 64) {				/* ＭＨ符号データはﾀｰﾐﾈｲﾃｨﾝｸﾞ時ﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl].BitLength;
			}
			EcmWrite(point->Wp, mhbits1, mhdata1);
			return;
		}
	/*	else if ((rl >= 64) && (rl <= point->Img_Size)) [ * ＭＨ符号データはNotﾀｰﾐﾈｲﾃｨﾝｸﾞとき */
		else if ((rl < MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* ＭＨ符号データメイクアップのとき */
			if (a_color == WHITE) {
				mhdata1 = MH_EC_WhiteTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_WhiteTableMain[rl%64].MHData;
				mhbits1 = MH_EC_WhiteTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_WhiteTableMain[rl%64].BitLength;
			}
			else {
				mhdata1 = MH_EC_BlackTableMain[rl/64+63].MHData;
				mhdata2 = MH_EC_BlackTableMain[rl%64].MHData;
				mhbits1 = MH_EC_BlackTableMain[rl/64+63].BitLength;
				mhbits2 = MH_EC_BlackTableMain[rl%64].BitLength;
			}
			EcmWrite(point->Wp, mhbits1, mhdata1);  /* 最初のＭＨ符号データを求める */
			EcmWrite(point->Wp, mhbits2, mhdata2);  /* 最後のＭＨ符号データをﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
			return;
		}
		else if ((rl >= MH_MAKEUP_MAX) && (rl <= point->Img_Size)) { /* RL > 2560の場合 */
			do {
				rl -= MH_MAKEUP_MAX;
				if (a_color == WHITE) {
					mhdata1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_WhiteTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				else {
					mhdata1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].MHData;
					mhdata2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].MHData;
					mhbits1 = MH_EC_BlackTableMain[MH_MAKEUP_MAX/64+63].BitLength;
					mhbits2 = MH_EC_BlackTableMain[MH_MAKEUP_MAX%64].BitLength;
				}
				EcmWrite(point->Wp, mhbits1, mhdata1);  /* 最初のＭＨ符号データを求める */
				if (rl == 0) {
					EcmWrite(point->Wp, mhbits2, mhdata2); /* 最後のＭＨ符号データをﾀｰﾐﾈｲﾃｨﾝｸﾞﾃｰﾌﾞﾙで求める */
					return;
				}
			}while (rl >= MH_MAKEUP_MAX);
		}
		else {/*	ここにきたらNG By Y.Suzuki 1997/02/01	*/
			SCD_DBG_ENC_RLSIZE = 2;
			break;
		}
	}	/* while (1) */
}

/***************************************************************************
	module		:[ＥＯＬデータの書き込み]
	function	:[
		1.　指定されたＭＨエンコードテーブル配列Ｎｏ．のＥＯＬデータを書き込む．
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ XX 00 X8 のようにＥＯＬをｾｯﾄしないとＥＯＬを検出できませんので
	               ０のﾋﾞｯﾄ数をenc->Wp->Bitのﾋﾞｯﾄ調整 96/05/13 S.Wang (requested by Y.Suzuki)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/

void Ecm_EOLWrite(UWORD eol, struct CdcBlk_t *point, UBYTE a_color)
{
	UBYTE	mhbits1;
	UWORD 	mhdata1;

	if (a_color == WHITE) {
		mhdata1 = MH_EC_WhiteTableMain[eol].MHData;
		mhbits1 = MH_EC_WhiteTableMain[eol].BitLength;
	}
	else {
		mhdata1 = MH_EC_BlackTableMain[eol].MHData;
		mhbits1 = MH_EC_BlackTableMain[eol].BitLength;
	}
	switch(point->Wp->Bit) { /* 96/05/13 S.Wang (requested by Y.Suzuki) */
	case 0x01:
		break;
	case 0x02:
		EcmWrite(point->Wp, 7, 0x00);
		break;
	case 0x04:
		EcmWrite(point->Wp, 6, 0x00);
		break;
	case 0x08:
		EcmWrite(point->Wp, 5, 0x00);
		break;
	case 0x10:
		EcmWrite(point->Wp, 4, 0x00);
		break;
	case 0x20:
		EcmWrite(point->Wp, 3, 0x00);
		break;
	case 0x40:
		EcmWrite(point->Wp, 2, 0x00);
		break;
	case 0x80:
		EcmWrite(point->Wp, 1, 0x00);
		break;
	default:
		break;
	}
	EcmWrite(point->Wp, mhbits1, mhdata1);
}

/***************************************************************************
	module		:[ＭＲデータの書き込み]
	function	:[
		1.　指定されたＭＲエンコードのＭＲデータを書き込む．
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/28]
	author		:[S.Wang]
***************************************************************************/

void Ecm_MRDataWrite(UBYTE code, struct CdcBlk_t *point)	/* MR code */
{
	UBYTE	mrcode;
	UBYTE	mrbits;

	mrcode = MR_EC_TableMain[code].MRData;
	mrbits = MR_EC_TableMain[code].BitLength;
	EcmWrite(point->Wp, mrbits, mrcode);
}


/************************************************************************************************************************
	module		:[RUN_LENGTHデータの取り出す]
	function	:[
		1.１バイトＲＬデータｏｒ2バイトＲＬデータを取り出す。
		2.2560以上のRLが取り出された場合、次のRLのカラーが同じなら続けて取り出す。
	return		:[RUN_LENGTH]
	common		:[]
                                                         7(データflag) 6(colorflag)    5 4 3 2 1 0  7 6 5 4 3 2 1 0
	condition	:[ rl<=63１バイトでＲＬデータを格納仕様: 0(１バイト)  0/1(white/black) * * * * * *
	               rl>=64 2バイトでＲＬデータを格納仕様: 1(２バイト)  0/1(white/black) * * * * * *  * * * * * * * *
                                                        |<-------------------１バイト目 ---------->|<--２バイト目-->|
				 ]
	comment		:[]
	machine		:[RISC]
	language	:[MS-C(Ver6.0)]
	keyword		:[SCDC]
	date		:[1995/11/18]
	author		:[S.Wang]
*************************************************************************************************************************/
/* #pragma inline (GetRL)*/
UWORD GetRLIntRom(struct WorkBuf_t *gp)
{
	UWORD FirstByte;
	UWORD SecondByte;
	UWORD RL;
	UWORD color;

	FirstByte = *(gp->Data + gp->Cout);
	color = FirstByte & 0x0040;	/*	White:0  Black:0x0040	*/
	if ((FirstByte & 0x0080) != 0x0080) {
		gp->Cout ++;
		RL = FirstByte & 0x003F;
		return (RL);
	}
	else {
		gp->Cout ++;
		SecondByte = *(gp->Data + gp->Cout);
		RL = ((FirstByte & 0x003F) << 8) + SecondByte;
		gp->Cout ++;
		return(RL);
	}
}
