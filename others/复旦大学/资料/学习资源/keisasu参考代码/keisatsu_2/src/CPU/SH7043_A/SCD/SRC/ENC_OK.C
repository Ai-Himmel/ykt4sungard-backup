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
#include "\src\atlanta\define\std.h"

#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#endif
#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#if (PRO_MODEM == R288F)
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#endif


UBYTE Mem_EOLWrite(UWORD eol, struct CdcBlk_t *point, UBYTE a_color);
UBYTE Mem_RLToMHWrite(UWORD rl, struct CdcBlk_t *point, UBYTE a_color);
UBYTE Mem_MRDataWrite(UBYTE code, struct CdcBlk_t *point);

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

