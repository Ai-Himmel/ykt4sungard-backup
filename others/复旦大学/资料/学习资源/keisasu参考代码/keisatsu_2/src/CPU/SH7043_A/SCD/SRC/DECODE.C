/*	By Y.Suzuki 1996/10/15	*/
/*	Original File jun\usr2:\src\kobe\anzu\scdc\src\decode.c	*/
/************************************************************************
*	System		: POPLAR
*	File Name	: DECODE.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mntsw_f.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"	/* 内蔵ＲＡＭにマッピングを変更します By O.Kimoto 1998/08/27 */
#else
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\scd_tbl.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"	/* 内蔵ＲＡＭにマッピングを変更します By O.Kimoto 1998/08/27 */
#endif

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
 #endif
#endif


#if (0)
/* 不要インクルードです。 By O.Kimoto 1998/08/27 */
** #include "\src\atlanta\ext_v\bkupram.h"		/* メモリＳＷ Ｆ参照のため By Y.Suzuki 1997/09/15 */
#endif

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/08/27 */
** #include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#else
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#endif

/* ダイレクトメモリ送信 By Y.Suzuki 1997/02/15 */
/* extern UBYTE SCD_DirectTx;*/

/*************************************************************
	module		:[Mem_Decode]
	function	:[one line MH,MR,MMR decode ]
	return		:[
	              TX_MEM_ERR                    7
	              RTC						    14
				  OK                            1
	              ]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[1 line Decode]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/16]
	author		:[王　慎]
*************************************************************/
/* static UBYTE SCD_NgRl = 0; */
BYTE Mem_DecodeIntRom(struct CdcBlk_t *dec,
					 struct WorkBuf_t *a_buf,
					 struct WorkBuf_t *b_buf)
{
	struct 	ScdcWorkData_t scdcdata, *scdcwork;
	UBYTE	rtn;							/* EOLsearch/MMLmodeのreturn値 */
	UBYTE	rtnrtc;							/* RTCsearchのreturn値 */
	UBYTE	rtneol;                         /* 画データの先頭に連続EOLsearchのreturn値 */
	WORD			runlen;							/* 白or黒ランレングス/EOL値	*/
	UWORD 			rl_b;							/* 参照ライン run length */
	WORD    		d;								/* a1-b1 */
	BYTE	        mode;							/* ＭＲmode */

	SCD_DBG_RLOVER = 0;/*	By Y.Suzuki 1997/01/28	*/


	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	scdcwork->b_pos = 0;
	a_buf->Cout = 0;
	a_buf->Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */

	SCD_NgRl = 0;/*	By Y.Suzuki 1997/02/27	*/

	/*----------------------------*/
	/* ライン開始のＥＯＬ検索処理 */
	/*----------------------------*/
	if (dec->Coding == SYS_MMR_CODE) {
		rtn = MMR_FOUND;
	}
	else {
		while(1) {/*デバックのため while でくくる。By Y.Suzuki 1998/01/20*/
			rtn = Mem_DetectEOL(dec);
			/* デバックのため以下のif文追加 */
			if (SCD_SkipMrEol) {/*	エラー発生時、ＭＲＥＯＬスキップ By Y.Suzuki 1998/01/20	*/
				if (rtn == MR_EOL_FOUND) {
					continue;
				}
				else {
					SCD_SkipMrEol = 0;
					break;
				}
			}
			else {
				break;
			}
		}
	}
	if (rtn == TX_MEM_ERR) {
		return(TX_MEM_ERR);
	}
		/*-----------------------------------*/
		/*　  1 ライン分RUNLENGTHデコード 　 */
		/*-----------------------------------*/
	if ((rtn == EOL_FOUND) || (rtn == MH_EOL_FOUND)) {
		if (SCD_DirectTx) {/*	ダイレクトメモリ送信 By Y.Suzuki 1997/02/15	*/
			if (rtn == EOL_FOUND) {
				Ecm_EOLWrite(EOL_NO, dec, 0) ;	 /* EOL 書き込む */
			}
			else {
				Ecm_EOLWrite(EOL_MH_NO, dec, 0);	 /* EOL_MH 書き込む */
			}
		}
		/*----------------------------------*/
		/* １ライン分のＭＨ－＞ＲＬ変換処理 */
		/*----------------------------------*/
		while (1) {
			runlen = Mem_MHDataToRL(dec, scdcwork->a_color);
			if (runlen == TX_MEM_ERR && MemReadStatus == NG) {
				return(TX_MEM_ERR);
			}
			if (runlen == EOL) {    			/* ランレングス値がＥＯＬ(0x00検出した）の時 */
				if (scdcwork->a_pos == 0) {
					if (dec->Line_Cntr == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
						rtneol = Mem_DetectEOL(dec);
						if (rtneol == TX_MEM_ERR) {
							return(TX_MEM_ERR);
						}
					}
					else {
						rtnrtc = Mem_DetectRTC(dec);
						if (rtnrtc == TX_MEM_ERR) {
							return(TX_MEM_ERR);
						}
						else {
							return(RTC);
						}
					}
				}
/*				else if (scdcwork->a_pos != dec->Img_Size) {
					return(TX_MEM_ERR);
				}
				else {
					return(OK);
				}
上記6行を以下3行に変更 S.Wang 96/03/15 */
				else {
					return(TX_MEM_ERR);
				}
			}
			else {
				/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
#if (0)/* By Y.Suzuki 1998/01/28 */
//				if ((runlen == 0) && (a_buf->Cout != 0)) {
//					SCD_NgRl = 3;
//				}
#endif
				PutRL(a_buf, runlen, scdcwork->a_color);        /* Put one runlength to Buffer RL */
				if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
					return(TX_MEM_ERR);
				}
				scdcwork->a_pos += runlen;						/*	レングス数を更新(count)	*/
				if (scdcwork->a_pos == dec->Img_Size) {
 					break;
				}
				if (scdcwork->a_pos > dec->Img_Size) {
					return(TX_MEM_ERR);
				}
				scdcwork->a_color = (UBYTE)(!scdcwork->a_color);			/**	処理中の画素色を反転させる	**/
			}
		}													/*	１ラインＭＨDecode終わり*/
	}
	else {   /* rtn == MR_EOL_FOUND or rtn == MMR_FOUND */
		if (SCD_DirectTx) {/*	ダイレクトメモリ送信 By Y.Suzuki 1997/02/15	*/
			if (rtn == MR_EOL_FOUND) {
				Ecm_EOLWrite(EOL_MR_NO, dec, 0); /* EOL_MR 書き込む */
			}
		}
		/*------------------------------------------*/
		/* １ライン分のＭＲ／ＭＭＲ－＞ＲＬ変換処理 */
		/*------------------------------------------*/
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->b0 = 0;
		scdcwork->V0_Count = 0;
		scdcwork->V0_Flag = 0;
		scdcwork->V0_Begin = 0;
		scdcwork->V0_End = 0;
		do {      												/* a0はImg_Sizeなるまで */
			while ((scdcwork->b_pos <= scdcwork->a0) || ((scdcwork->b_pos > scdcwork->a0) && (scdcwork->a_color == scdcwork->b_color))) { 	/* b_pos 検出 */
				scdcwork->b0 = scdcwork->b_pos; 				/* 更新する前の参照ラインの位置b0を記録 */
				if (scdcwork->b_pos < dec->Img_Size) {
					rl_b = GetRL(b_buf);
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if ((scdcwork->b_pos == 0) && (scdcwork->b0 == 0)) { /* 参照ラインの頭は黒の時(白RL=0) */
						break;
					}
				}
				else {
					/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/09/15	*/
					if (scdcwork->a_color != scdcwork->b_color) {
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					/*	SCD_MaintenanceSwitch[SCD_MNT_SW_F1] |= 0x08;*/
					}
				    break;
				}
			}													/* b_pos 検出した */
			mode = Mem_MRDataToMode(dec);
			if (mode == TX_MEM_ERR && MemReadStatus == NG) {
				return(TX_MEM_ERR);
			}
			/*--------------------------*/
			/* ＭＲ／ＭＭＲ－＞ＲＬ変換 */
			/*--------------------------*/
			if (mode == ERR) {
				return(TX_MEM_ERR);
			}
			else if (mode == EOL) {    							/* mode値がＥＯＬ(0x00検出した）の時 */
				/*------------*/
				/* ＥＯＬ検出 */
				/*------------*/
				if (scdcwork->a_pos == 0) {
					if (dec->Line_Cntr == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
						rtneol = Mem_DetectEOL(dec);
						if (rtneol == TX_MEM_ERR) {
							return(TX_MEM_ERR);
						}
					}
					else {
						rtnrtc = Mem_DetectRTC(dec);
						if (rtnrtc == TX_MEM_ERR) {
							return(TX_MEM_ERR);
						}
						else {
							return(RTC);
						}
					}
				}
/*				if (scdcwork->a_pos != dec->Img_Size) {
					return(TX_MEM_ERR);
				}
				else {
					return(OK);
				}
上記6行を以下3行に変更 S.Wang 96/03/15 */
				else {
					return(TX_MEM_ERR);
				}
			}
			else if (mode == V0_MODE) {  						/* V0 mode */
				scdcwork->V0_Count ++;						/* V0mode個数のcount */
				if (scdcwork->V0_Flag == 0) { 				/* 最初のV0mode */
					scdcwork->V0_Begin = b_buf->Cout;     	/* V0モードの最初位置　*/
					scdcwork->a1 = scdcwork->b_pos;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
#if (0)/* By Y.Suzuki 1998/01/28 */
//					if ((runlen == 0) && (a_buf->Cout != 0)) {
//						SCD_NgRl = 3;
//					}
#endif
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(TX_MEM_ERR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->V0_Flag = 1;
				}
				else {									    /* 連続V0モード */
					/*if (scdcwork->V0_Count > 1) { このif条件は要りません S.Wang 96/03/15 */
						scdcwork->a1 = scdcwork->b_pos;
						scdcwork->a_pos = scdcwork->a1;
						scdcwork->a0 = scdcwork->a1;
						scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					/*}*/
					if (scdcwork->V0_Count == V0_MAX_COUNT || scdcwork->a_pos == dec->Img_Size) {
						scdcwork->V0_End = b_buf->Cout;		/* 連続V0モードの終了位置　 */
						PutV0(scdcwork, a_buf, b_buf);		/* 連続V0モードデータを格納する */
						scdcwork->V0_Flag = 0;
						scdcwork->V0_Count = 0;
					}
				}
			}
			else {
				if (scdcwork->V0_Flag == 1) {
					if (rl_b >= 64) {  						/* rl_b は２バイドでデータを格納する時の連続V0モードの終了位置 */
						scdcwork->V0_End = b_buf->Cout - 2;
					}
					else {
						scdcwork->V0_End = b_buf->Cout - 1; /* rl_b は１バイドでデータを格納する時の連続V0モードの終了位置 */
					}
					PutV0(scdcwork, a_buf, b_buf);			/* 連続V0モードデータを格納する */
					scdcwork->V0_Flag = 0;
					scdcwork->V0_Count = 0;
				}
				if (mode == H_MODE) {
					runlen = Mem_MHDataToRL(dec, scdcwork->a_color);
					if (runlen == TX_MEM_ERR && MemReadStatus == NG) {
						return(TX_MEM_ERR);
					}
					scdcwork->a1 = scdcwork->a0 + runlen;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
#if (0)/* By Y.Suzuki 1998/01/28 */
//					if ((runlen == 0) && (a_buf->Cout != 0)) {
//						SCD_NgRl = 3;
//					}
#endif
					PutRL(a_buf, scdcwork->a1-scdcwork->a_pos, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(TX_MEM_ERR);
					}
					scdcwork->a_pos = scdcwork->a1;				/*	レングス数を更新(count)	*/
					if (scdcwork->a_pos > dec->Img_Size) {
						return(TX_MEM_ERR);
					}
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					runlen = Mem_MHDataToRL(dec, scdcwork->a_color);
					if (runlen == TX_MEM_ERR && MemReadStatus == NG) {
						return (TX_MEM_ERR);
					}
					scdcwork->a_pos += runlen;					/*	レングス数を更新(count)	*/
					if (scdcwork->a_pos > dec->Img_Size) {
						return(TX_MEM_ERR);
					}
					if ((scdcwork->a_pos == dec->Img_Size) && (runlen == 0)) {
						/* PutRL 無し */
					}
					else {
						/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
#if (0)/* By Y.Suzuki 1998/01/28 */
//						if ((runlen == 0) && (a_buf->Cout != 0)) {
//							SCD_NgRl = 3;
//						}
#endif
						PutRL(a_buf, runlen, scdcwork->a_color);   /* Put one runlength to Buffer RL */
						if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
							return(TX_MEM_ERR);
						}
					}
					scdcwork->a0 = scdcwork->a_pos;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
				}
				if (mode == P_MODE) {
					scdcwork->b0 = scdcwork->b_pos; 			/* 更新する前の参照ラインの位置b0を記録 */
					rl_b = GetRL(b_buf);  						/* b_pos 検出 */
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b_pos >= dec->Img_Size) {
						scdcwork->b_pos = dec->Img_Size;
					}  										   	/* b_pos 検出した */
					scdcwork->a0 = scdcwork->b_pos;
				}
				if (2 <= mode && mode <= 8 && mode != 5) {     /* V_MODE (V0_MODE除く) */
					d = mode - 5;
					scdcwork->a1 = scdcwork->b_pos + d;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
#if (0)/* By Y.Suzuki 1998/01/28 */
//					if ((runlen == 0) && (a_buf->Cout != 0)) {
//						SCD_NgRl = 3;
//					}
#endif
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(TX_MEM_ERR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (scdcwork->a_pos > dec->Img_Size) {
						return(TX_MEM_ERR);
					}
					if (d < -1) {     							/* VL(2) or VL(3) modeの特例 次の参照ラインb_posの検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
							if (rl_b >= 64) {  				    /* rl_b は２バイドでデータを格納する時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;				/* rl_b は1バイドでデータを格納する時時 */
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b_pos = scdcwork->b0;
						}
					}
				}
			}
		}while(scdcwork->a0 < dec->Img_Size);
	}
	if (scdcwork->a0 > dec->Img_Size) {/*	By Y.Suzuki 1997/01/28	*/
		SCD_DBG_RLOVER = 2;
	}
	dec->Line_Cntr ++; /* ｺｰﾃﾞｯｸライン数Countのincrement */
	return(OK);
}

/*************************************************************************
	module		:[ＭＨデータをRUNLENGTHに展開]
	function	:[
		1.
	]
	return		:[
				  TX_MEM_ERR  7
				  EOL        -2
				  runcnt	 ランレングス
				  ]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref.PAT_ScdMHtoImage(unsigned char *image_buf, unsigned int  side_margin)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
WORD Mem_MHDataToRL(struct CdcBlk_t *mp, UBYTE a_color)
{
	UWORD 			decdata;						/*	ＭＨデータ */
	WORD			runlen;							/*	白or黒ランレングス	*/
	UWORD			tblno;							/*	テーブルＮｏ			*/
	UWORD			runcnt;							/*  同一色のランレングス数  メイクアップ + ターミネート   */
	UBYTE	bitlen;							/*	ＭＨデータのビット長	*/

	runcnt = 0;
	/*----------------------*/
	/* ＭＨ－＞ＲＬ１次変換 */
	/*----------------------*/
	do {
		if (mp->DecBits < 8) {		/* ＭＨデータが１次テーブル参照必要ビット数（８）以下 */
			decdata = MemRead(mp->Rp, 8);
			if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
				return(TX_MEM_ERR);
			}
/*			mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= mp->DecBits;
			mp->DecData.Word |= decdata;
			mp->DecBits += 8;
		}
		if (a_color == WHITE) {							/*	白レン	*/
			runlen = MH_DC_WhiteTableMain[mp->DecData.Byte.L].RunLength;
		}
		else {											/*	黒レン	*/
			runlen = MH_DC_BlackTableMain[mp->DecData.Byte.L].RunLength;
		}
	/*------------*/
	/* ＥＯＬ検出 */
	/*------------*/
		if (runlen == EOL) {								/* ランレングス値がＥＯＬの時 */
			return(EOL);
		}
	/*----------------------*/
	/* ＭＨ－＞ＲＬ２次変換 */
	/*----------------------*/
		if (runlen & 0x8000) {									/* ランレングス値の２次テーブル参照必要ビットがオン */
			if (SCD_DirectTx) {/* ダイレクトメモリ送信 By Y.Suzuki 1997/02/15 */
				EcmWrite(mp->Wp,8,mp->DecData.Word);
			}
			runlen &= ~0x8000;
			mp->DecData.Byte.L = mp->DecData.Byte.H;			/* チェック済みＭＨデータを１バイト廃棄 */
			mp->DecData.Byte.H = 0;
			mp->DecBits -= 8;									/* ## 注意１ ## */
			if (mp->DecBits < 5) {								/* ＭＨデータが２次テーブル参照必要ビット数（５）以下  MH符号はMAX13ﾋﾞｯﾄだから */
				decdata = MemRead(mp->Rp,8);
				if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
					return(TX_MEM_ERR);
				}
/*				mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
				decdata <<= mp->DecBits;
				mp->DecData.Word |= decdata;
				mp->DecBits += 8;
			}
			tblno = (UWORD)(MH_DC_TableSub[runlen].MaskBit & mp->DecData.Byte.L);
			runlen = MH_DC_TableSub[runlen].Adr[tblno].RunLength;
		}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		tblno = runlen;											/* テーブルの配列番号にランレングス値をセット（ターミネートの時）*/
		if (runlen > 63) {										/* メイクアップの時 */
			tblno = (runlen/64) + 63;							/* テーブルの配列番号[64]以降なので，64で割った商に63を足す */
		}
		if (a_color == WHITE) {						/* 白レン */
			bitlen = MH_EC_WhiteTableMain[tblno].BitLength;
		}
		else {										/* 黒レン */
			bitlen = MH_EC_BlackTableMain[tblno].BitLength;
		}
		if (bitlen > 8) {							/**	変換ビット数が８ビット以上	**/
			bitlen -= 8;							/* 9ﾋﾞｯﾄ以上ということは２次ﾃｰﾌﾞﾙを参照したということで，注意１ですでにScdMHBitsが８ひかれている */
		}											/**	既に８ビット分廃棄しているのでその分を差し引く	**/
		if (SCD_DirectTx) {/* ダイレクトメモリ送信 By Y.Suzuki 1997/02/15 */
			EcmWrite(mp->Wp,bitlen,mp->DecData.Word);
		}
		mp->DecData.Word >>= bitlen;				/**	 変換済みビット廃棄	 **/
		mp->DecBits -= bitlen;						/**  未変換ビット数算出	 **/
	/*---------------------------------------------------------*/
	/* ＲＬのＰＵＴ,メイクアップの時に同一色のレングス数の変換 */
	/*---------------------------------------------------------*/
		runcnt += runlen;				        	/**	 同一色のレングス数を更新	**/
		if (runlen <= 63) {							/**	 変換した値がターミネートの時	**/
			return(runcnt);
		}          									/* 1 runlength ＭＨDecode終わり*/
	}while (runlen > 63);
}

/*************************************************************************
	module		:[ＥＯＬDETECT]
	function	:[
		1.
	]
	return		:[
				  TX_MEM_ERR					7
				  EOL_FOUND                    15
                  MH_EOL_FOUND                 16
                  MR_EOL_FOUND                 17
				  ]
	common		:[
				  MemReadStatus
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref. PAT_ScdCheckEOL(unsigned char mhdata, unsigned char *ptnp)
				 ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995.12.18]
	author		:[S.Wang]
*************************************************************************/
UBYTE Mem_DetectEOL(struct CdcBlk_t *dp)
{
	WORD 	result;
	UWORD	decdata;
	UBYTE eoldet;

	eoldet = 0;
	while (1) {		   /* ＥＯＬを見つける間  */
		if (dp->DecBits < 8) {			/* ＭＨ／ＭＲデータが１バイト以下 */
			decdata = MemRead(dp->Rp,8);
			if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
				return(TX_MEM_ERR);
			}
		/*	dp->DecData.Word |= decdata << dp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= dp->DecBits;
			dp->DecData.Word |= decdata;
			dp->DecBits += 8;
		}
		result = ScdcCheckEOL(dp->DecData.Byte.L, &eoldet);			/* ＥＯＬ検索を実行 */
/*		if (result == -1) { 										 * ＥＯＬ検出ＮＧ *
			return (TX_MEM_ERR);
		} revised by S.Wang 96/06/10 */
#if(0)
** 		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
** 			if (dp->Coding == SYS_MH_CODE) {
** 				dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 				dp->DecBits -= result;
** 				return(EOL_FOUND);
** 			}
** 			else {
** 				if (result < 8) {										/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
** 					}
** 				}
** 				if (result == 8) {
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					dp->DecBits -= result;
** 					if (dp->DecBits < 8) {								/* ＭＨ／ＭＲデータが１バイト以下 */
** 						decdata = MemRead(dp->Rp,8);
** 						if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
** 							return(TX_MEM_ERR);
** 						}
** 						decdata <<= dp->DecBits;
** 						dp->DecData.Word |= decdata;
** 						dp->DecBits += 8;
** 					}
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MR_EOL_FOUND);
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MH_EOL_FOUND);
** 					}
** 				}
** 			}
** 		}
#endif		/* 上記のプログラムは以下のような変更 S.Wang 96/04/17 */
		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
			dp->DecData.Word >>= result;							/* ＥＯＬビットを廃棄 */
			dp->DecBits -= result;
			if (dp->Coding == SYS_MH_CODE) {
				return(EOL_FOUND);
			}														/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
			else {
				if (dp->DecBits < 1) {								/* 	ＥＯＬ_0/ＥＯＬ_1検出するのは次の1ﾋﾞｯﾄデータ参照必要 */
					decdata = MemRead(dp->Rp,8);
					if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
						return(TX_MEM_ERR);
					}
					decdata <<= dp->DecBits;
					dp->DecData.Word |= decdata;
					dp->DecBits += 8;
				}
				if ((dp->DecData.Word & 0x0001) == 0) {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
					dp->DecBits -= 1;
					return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
				}
				else {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
					dp->DecBits -=1;
					return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
				}
			}
		}
		else { /* ＥＯＬ検出ＮＧ(result=-1) or ＥＯＬ検出中(result=0) */
			dp->DecData.Byte.L = dp->DecData.Byte.H;		/* チェック済みＭＨデータを１バイト廃棄 */
			dp->DecData.Byte.H = 0;
			dp->DecBits -= 8;
		}
	}
}

/*************************************************************************
	module		:[ＭＲデータをＭＲｍｏｄｅに展開]
	function	:[
		1.
	]
	return		:[
				  TX_MEM_ERR  7
				  ERR        -1
				  EOL        -2
				  mode       ＭＲ ｍｏｄｅ
			   	]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[SCD]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
BYTE Mem_MRDataToMode(struct CdcBlk_t *mrp)
{
	UWORD 	decdata;						/*	ＭＲデータ */
	BYTE	mode;							/*	ＭＲ ｍｏｄｅ	*/
	UBYTE	bitlen;					/*	ＭＲテーブルのビット長	*/

	if (mrp->DecBits < 8) {			        /* ＭＨ／ＭＲデータが１バイト以下 */
		decdata = MemRead(mrp->Rp, 8);
		if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
			return(TX_MEM_ERR);
		}
/*	mrp->DecData.Word |= decdata << mrp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
		decdata <<= mrp->DecBits;
		mrp->DecData.Word |= decdata;
		mrp->DecBits += 8;
	}
	/*----------------------*/
	/* ＭＲ－＞ＭＯＤＥ変換 */
	/*----------------------*/
	mode = MR_DC_TableMain[mrp->DecData.Byte.L].ModeType;
	if (mode == ERR) {
		return(ERR);
	}
	if (mode == EOL) {
		return(EOL);
	}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		bitlen = MR_EC_TableMain[mode].BitLength;
		if (SCD_DirectTx) {/* ダイレクトメモリ送信 By Y.Suzuki 1997/02/15 */
			EcmWrite(mrp->Wp,bitlen,mrp->DecData.Word);
		}
		mrp->DecData.Word >>= bitlen;					/**	 変換済みビット廃棄	 **/
		mrp->DecBits -= bitlen;							/**  未変換ビット数算出	 **/
		return(mode);
}

/*************************************************************************
	module		:[RTC/EOFB DETECT]
	function	:[
		1.
	]
	return		:[
				  TX_MEM_ERR                    7
	              RTC						    14
				  ]
	common		:[]
	condition	:[内蔵ＲＯＭ
					(1)RTC検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]３つ検出 --->
					   [00...0+(EOL/EOL+0/EOL+1)]１つと[EOL]１つ検出
				    (2)EOFB検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]２つ検出 --->
				       [EOL]１つ検出
				                      ----S.Wang 96/06/20
				 ]
	comment		:[
					１） RTC Detect時に2個目のＥＯＬは必ず１１個０であること"000000000001"
					２） ライン開始のＥＯＬ検索処理Mem_DetectEOL(dec)で(Fill+EOL)
					   を見付けた。またDecodeTableで８個連続０を検出した。このサブ
					   ルーチンは引き続き"0001"を検出する
				 ]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1996.2.23]
	author		:[S.Wang]
	修正履歴    :[
					1996.6.20 S.Wang
				 ]

*************************************************************************/
UBYTE Mem_DetectRTC(struct CdcBlk_t *dp)
{
#if(0)
** 	unsigned char ret;
** 
** 	ret = Mem_DetectEOL(dp);
** 	if (ret == TX_MEM_ERR) { 				/* MemRead error */
** 		return(TX_MEM_ERR);
** 	}
** 	else {									/* MR_EOL_FOUND/EOL_FOUND/MH_EOL_FOUND */
** 		ret = Mem_DetectEOL(dp);
** 		if (ret == TX_MEM_ERR) { 		/* MemRead error */
** 			return(TX_MEM_ERR);
** 		}
** 		else { 							/* MR_EOL_FOUND/EOL_FOUND/MH_EOL_FOUND */
** 			return(RTC); 				/* ＲＴＣ:連続ＥＯＬ三つを検出必要 */
** 		}                               /* ＥＯＦＢ:連続ＥＯＬ二つを検出必要  */
** 	}
#endif
	UWORD	decdata;

	dp->DecData.Word >>= 8;		/* Decode Tableで８個連続０を検出したので、変換済み８ビット廃棄 */
	dp->DecBits -= 8;			/* 未変換ビット数算出 */
	if (dp->DecBits < 4) {		/* ＭＨ／ＭＲデータが4ビット以下 */
		decdata = MemRead(dp->Rp, 8);
		if (decdata == TX_MEM_ERR && MemReadStatus == NG) {
			return(TX_MEM_ERR);
		}
		decdata <<= dp->DecBits;
		dp->DecData.Word |= decdata;
		dp->DecBits += 8;
	}
	if ((dp->DecData.Byte.L & 0x07) == 0) {		/* 今回3個連続０検出し、ここまできたということは０を１１個見付けた。 */
		if ((dp->DecData.Byte.L & 0x08) != 0) {	/* 次のビット１を見付けた。ＲＴＣ検出ＯＫ */
			return(RTC);
		}
		else {
			return(TX_MEM_ERR);
		}
	}
	else {
		return(TX_MEM_ERR);
	}
}

/*************************************************************
	module		:[Mdm_Decode]
	function	:[one line MH,MR,MMR decode ]
	return		:[
	              OK                            1
	              RX_CARRIER_DOWN				5
	              RX_ERROR						6
	              RTC						    14
	              ]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[1 line Decode]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/11/16]
	author		:[王　慎]
*************************************************************/
/* UBYTE SCD_SkipMrEol = 0;*/
/* static UBYTE SCD_DBG_RLOVER = 0;	By Y.Suzuki 1997/01/28	*/
BYTE Mdm_DecodeIntRom(struct CdcBlk_t *dec,
					 struct WorkBuf_t *a_buf,
					 struct WorkBuf_t *b_buf)
{
	struct 	ScdcWorkData_t scdcdata, *scdcwork;
	UBYTE	rtn;							/* EOLsearch/MMLmodeのreturn値 */
	UBYTE	rtnrtc;							/* RTCsearchのreturn値 */
	UBYTE	rtneol;                         /* 画データの先頭に連続EOLsearchのreturn値 */
	WORD	runlen;							/* 白or黒ランのレングス/EOL値 */
	UWORD 	rl_b;							/* 参照ライン run length */
	WORD    d;								/* a1-b1 */
	BYTE	mode;							/* ＭＲmode */

	SCD_DBG_RLOVER = 0;/*	By Y.Suzuki 1997/01/28	*/

	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	scdcwork->b_pos = 0;
	a_buf->Cout = 0;
	a_buf->Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */

	SCD_NgRl = 0;/*	By Y.Suzuki 1997/02/27	*/

		/*----------------------------*/
		/* ライン開始のＥＯＬ検索処理 */
		/*----------------------------*/
#if (0)	/*	By Y.Suzuki 1997/01/09	*/
** 	/* モデムバッファ１本目読み飛ばし 問題解決後こちらに戻す  */
** 	if (dec->Coding == SYS_MMR_CODE) {
** 		rtn = MMR_FOUND;
** 	}
** 	else {
**    		rtn = Mdm_DetectEOL(dec);
** 	}
** 	if (rtn == RX_CARRIER_DOWN) {
** 		return(RX_CARRIER_DOWN);
** 	}
#endif	/* By Y.Suzuki 1997/01/09 */
	/* モデムバッファ１本目読み飛ばし */
	while (1) {
		if (dec->Coding == SYS_MMR_CODE) {
			rtn = MMR_FOUND;
		}
		else {
	   		rtn = Mdm_DetectEOL(dec);
		}
		if (rtn == RX_CARRIER_DOWN) {
			return(RX_CARRIER_DOWN);
		}
		if (SCD_SkipMrEol) {/*	エラー発生時、ＭＲＥＯＬスキップ By Y.Suzuki 1997/02/17	*/
			if (rtn == MR_EOL_FOUND) {
				continue;
			}
			else {
				SCD_SkipMrEol = 0;
				break;
			}
		}
		if (DEBUG_SCD_MDM_BufferSkip) {
			break;
		}
	}
	/* ここまで、By Y.Suzuki 1997/01/09 */
/*	if (rtn == RX_ERROR) {
		return(RX_ERROR);
	}*/
		/*-----------------------------------*/
		/*　  1 ライン分RUNLENGTHデコード 　 */
		/*-----------------------------------*/
	if ((rtn == EOL_FOUND) || (rtn == MH_EOL_FOUND)) {
		/*----------------------------------*/
		/* １ライン分のＭＨ－＞ＲＬ変換処理 */
		/*----------------------------------*/
		while (1) {
			runlen = Mdm_MHDataToRL(dec, scdcwork->a_color);
			if (runlen == EOL) {    			/* ランレングス値がＥＯＬ(0x00検出した）の時 */
				if (scdcwork->a_pos == 0) {
				/*	if (dec->Line_Cntr == 0) [ @* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
#if (0)
** 					/* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/08/27 */
** 					if (MDM_RxTotalLine == 0) [ /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず By Y.Suzuki 1997/07/10 */
#else
					if (*MDM_RxTotalLine_p == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず By Y.Suzuki 1997/07/10 */
#endif
						rtneol = Mdm_DetectEOL(dec);
						if (rtneol == RX_CARRIER_DOWN) {
							return(RX_CARRIER_DOWN);
						}
					}
					else {
						if (a_buf->Flag == 1) {
							/* 白0､黒0の後ならRTC By Y.Suzuki 1997/06/23 */
							return(RTC);
						}
						rtnrtc = Mdm_DetectRTC(dec);
						if (rtnrtc == RX_ERROR) {
							return(RX_ERROR);
						}
						else {
							return(RTC);
						}
					}
				}
				else {
					return(RX_ERROR);
				}
			}
			else {
				/*	白０、黒０連続データの処理 By Y.Suzuki 1997/02/19	*/
				if (runlen == 0) {
					if (a_buf->Flag == 1){
						/*return(RTC);*/
						continue;
					}
					else {
						a_buf->Flag = 1;
					}
				}
				else {
					a_buf->Flag = 0;
				}

				/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
				if ((runlen == 0) && (a_buf->Cout != 0)) {
					SCD_NgRl = 3;
				}
				PutRL(a_buf, runlen, scdcwork->a_color);         /* Put one runlength to Buffer RL */
				if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
					return(RX_ERROR);
				}
				scdcwork->a_pos += runlen;						/*	レングス数を更新(count)	*/
				if (scdcwork->a_pos == dec->Img_Size) {
 					break;
				}
				if (scdcwork->a_pos > dec->Img_Size) {
					return(RX_ERROR);
				}
				scdcwork->a_color = (UBYTE)(!scdcwork->a_color);			/**	処理中の画素色を反転させる	**/
		    }
		}														/*	１ラインＭＨDecode終わり*/
	}
	else {  /* rtn == MR_EOL_FOUND or rtn == MMR_FOUND */
		/*------------------------------------------*/
		/* １ライン分のＭＲ／ＭＭＲ－＞ＲＬ変換処理 */
		/*------------------------------------------*/
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->b0 = 0;
		scdcwork->V0_Count = 0;
		scdcwork->V0_Flag = 0;
		scdcwork->V0_Begin = 0;
		scdcwork->V0_End = 0;
		do {      												/* a0はImg_Sizeになるまで */
			while ((scdcwork->b_pos <= scdcwork->a0) || ((scdcwork->b_pos > scdcwork->a0) && (scdcwork->a_color == scdcwork->b_color))) { 	/* b_pos 検出 */
				scdcwork->b0 = scdcwork->b_pos; 				/* 更新する前の参照ラインの位置b0を記録 */
				if (scdcwork->b_pos < dec->Img_Size) {
					rl_b = GetRL(b_buf);
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if ((scdcwork->b_pos == 0) && (scdcwork->b0 == 0)) { /* 参照ラインの頭は黒の時(白RL=0) */
						break;
					}
				}
				else {
					/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/09/15	*/
					if (scdcwork->a_color != scdcwork->b_color) {
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					/*	SCD_MaintenanceSwitch[SCD_MNT_SW_F1] |= 0x08;*/
					}
				    break;
				}
			}													/* b_pos 検出した */
			mode = Mdm_MRDataToMode(dec);
			/*--------------------------*/
			/* ＭＲ／ＭＭＲ－＞ＲＬ変換 */
			/*--------------------------*/
			if (mode == ERR) {
				return(RX_ERROR);
			}
			else if (mode == EOL) {    /* mode値がＥＯＬ(0x00検出した）の時 */
				/*------------*/
				/* ＥＯＬ検出 */
				/*------------*/
				if (scdcwork->a_pos == 0) {
					if (dec->Line_Cntr == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
						rtneol = Mdm_DetectEOL(dec);
						if (rtneol == RX_CARRIER_DOWN) {
							return(RX_CARRIER_DOWN);
						}
					}
					else {
						rtnrtc = Mdm_DetectRTC(dec);
						if (rtnrtc == RX_ERROR) {
							return(RX_ERROR);
						}
						else {
							return(RTC);
						}
					}
				}
				else {
					return(RX_ERROR);
				}
			}
			else if (mode == V0_MODE) {  						/* V0 mode */
				scdcwork->V0_Count ++;						/* V0mode個数のcount */
				if (scdcwork->V0_Flag == 0) { 				/* 最初のV0mode */
					scdcwork->V0_Begin = b_buf->Cout;     	/* V0モードの最初位置　*/
					scdcwork->a1 = scdcwork->b_pos;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->V0_Flag = 1;
				}
				else {									    /* 連続V0モード */
					/*if (scdcwork->V0_Count > 1) { このif条件は要りません S.Wang 96/03/15 */
						scdcwork->a1 = scdcwork->b_pos;
						scdcwork->a_pos = scdcwork->a1;
						scdcwork->a0 = scdcwork->a1;
						scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					/*}*/
					if (scdcwork->V0_Count == V0_MAX_COUNT || scdcwork->a_pos == dec->Img_Size) {
						scdcwork->V0_End = b_buf->Cout;		/* 連続V0モードの終了位置　 */
						PutV0(scdcwork, a_buf, b_buf);		/* 連続V0モードデータを格納する */
						scdcwork->V0_Flag = 0;
						scdcwork->V0_Count = 0;
					}
				}
			}
			else {
				if (scdcwork->V0_Flag == 1) {
#if(0)
**					if (rl_b > MH_MAKEUP_MAX) {	/*	RLBUF 2バイト消費する By Y.Suzuki 1997/01/13	*/
**						rl_b -= MH_MAKEUP_MAX;
**						if (rl_b >= 64) {/* rl_b は２バイドでデータを格納する時の連続V0モードの終了位置 */
**							scdcwork->V0_End = b_buf->Cout - 4;
**						}
**						else {/* rl_b は１バイドでデータを格納する時の連続V0モードの終了位置 */
**							scdcwork->V0_End = b_buf->Cout - 3;
**						}
**						rl_b += MH_MAKEUP_MAX;	/* VL 特殊処理で使用するので元の値を戻す	By Y.Suzuki 1997/01/13	*/
**					}
**					else if (rl_b == MH_MAKEUP_MAX) {	/*	RLBUF 2バイト消費する By Y.Suzuki 1997/01/13	*/
**						scdcwork->V0_End = b_buf->Cout - 2;
**					}
**					else if (rl_b >= 64) [  						/* rl_b は２バイドでデータを格納する時の連続V0モードの終了位置 */
#endif
					if (rl_b >= 64) {  						/* rl_b は２バイドでデータを格納する時の連続V0モードの終了位置 */
						scdcwork->V0_End = b_buf->Cout - 2;
					}
					else {
						scdcwork->V0_End = b_buf->Cout - 1; /* rl_b は１バイドでデータを格納する時の連続V0モードの終了位置 */
					}
					PutV0(scdcwork, a_buf, b_buf);			/* 連続V0モードデータを格納する */
					scdcwork->V0_Flag = 0;
					scdcwork->V0_Count = 0;
				}
				if (mode == H_MODE) {
					runlen = Mdm_MHDataToRL(dec, scdcwork->a_color);
					scdcwork->a1 = scdcwork->a0 + runlen;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, scdcwork->a1-scdcwork->a_pos, scdcwork->a_color);	/* Put one runlength to Buffer RL */
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;							/*	レングス数を更新(count)	*/
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					runlen = Mdm_MHDataToRL(dec,scdcwork->a_color);
					scdcwork->a_pos += runlen;							/*	レングス数を更新(count)	*/
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					if ((scdcwork->a_pos == dec->Img_Size) && (runlen == 0)) {
						/* PutRL 無し */
					}
					else {
						/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
						if ((runlen == 0) && (a_buf->Cout != 0)) {
							SCD_NgRl = 3;
						}
						PutRL(a_buf, runlen, scdcwork->a_color);          /* Put one runlength to Buffer RL */
						if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
							return(RX_ERROR);
						}
					}
					scdcwork->a0 = scdcwork->a_pos;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
				}
				if (mode == P_MODE) {
					scdcwork->b0 = scdcwork->b_pos; 			/* 更新する前の参照ラインの位置b0を記録 */
					rl_b = GetRL(b_buf);  						/* b2 検出 */
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b_pos >= dec->Img_Size) {
						scdcwork->b_pos = dec->Img_Size;
						/* ラインの最後にパスモードがきた By Y.Suzuki 1997/06/23 */
						return(RX_ERROR);
					}  										   	/* b2 検出した */
					scdcwork->a0 = scdcwork->b_pos;
				}
				if (2 <= mode && mode <= 8 && mode != 5) {      /* V_MODE (V0_MODE除く) */
					d = mode - 5;
					scdcwork->a1 = scdcwork->b_pos + d;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					if (d < -1) {     							/* VL(2) or VL(3) modeの特例 次の参照ラインb_posの検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
#if(0)
**							if (rl_b > MH_MAKEUP_MAX) {	/*	RLBUF 2バイト消費する By Y.Suzuki 1997/01/13	*/
**								b_buf->Cout -= 2;
**								rl_b -= MH_MAKEUP_MAX;
**								if (rl_b >= 64) { /* rl_b は２バイドでデータを格納する時 */
**									b_buf->Cout -= 2;
**								}
**								else {/* rl_b は１バイドでデータを格納する時 */
**									b_buf->Cout -= 1;
**								}
**								rl_b += MH_MAKEUP_MAX;	/*	こわいんで元の値に戻しとくBy Y.Suzuki 1997/01/13	*/
**							}
**							else if (rl_b == MH_MAKEUP_MAX) {	/*	RLBUF 2バイト消費する By Y.Suzuki 1997/01/13	*/
**								b_buf->Cout -= 2;
**							}
**							else if (rl_b >= 64) [  				/* rl_b は２バイドでデータを格納する時 */
#endif
							if (rl_b >= 64) {  				/* rl_b は２バイドでデータを格納する時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;			/* rl_b は１バイドでデータを格納する時 */
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b_pos = scdcwork->b0;
						}
					}
				}
			}
		}while(scdcwork->a0 < dec->Img_Size);
	}
	if (scdcwork->a0 > dec->Img_Size) {/*	By Y.Suzuki 1997/01/28	*/
		SCD_DBG_RLOVER = 1;
	}
#if(0)
** 	if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/02/27	*/
** 		return(RX_ERROR);
** 	}
#endif
	dec->Line_Cntr ++; /* ｺｰﾃﾞｯｸライン数Countのincrement */
	return(OK);
}


/*************************************************************************
	module		:[ＭＨデータをRUNLENGTHに展開]
	function	:[
		1.
	]
	return		:[EOL        -2
				  runcnt	 ランレングス
				  ]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref.PAT_ScdMHtoImage(unsigned char *image_buf, unsigned int  side_margin)]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
WORD Mdm_MHDataToRL(struct CdcBlk_t *mp, UBYTE a_color)
{
	UWORD 			decdata;						/*	ＭＨデータ */
	WORD			runlen;							/*	白or黒ランレングス	*/
	UWORD			tblno;							/*	テーブルＮｏ			*/
	UWORD			runcnt;							/*  同一色のランレングス数  メイクアップ + ターミネート   */
	UBYTE	bitlen;							/*	ＭＨデータのビット長	*/

	runcnt = 0;
	/*----------------------*/
	/* ＭＨ－＞ＲＬ１次変換 */
	/*----------------------*/
	do {
		if (mp->DecBits < 8) {		/* ＭＨデータが１次テーブル参照必要ビット数（８）以下 */
			decdata = MdmRead(mp->Rp, 8);
			if (SCD_G3ReadStatus == RCV_STOP) {
				return(RX_STOPPED);
			}
			else if (SCD_G3ReadStatus != RCV_BLOCK) {
				return(RX_CARRIER_DOWN);
			}
/*			mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= mp->DecBits;
			mp->DecData.Word |= decdata;
			mp->DecBits += 8;
		}
		if (a_color == WHITE) {							/*	白レン	*/
			runlen = MH_DC_WhiteTableMain[mp->DecData.Byte.L].RunLength;
		}
		else {											/*	黒レン	*/
			runlen = MH_DC_BlackTableMain[mp->DecData.Byte.L].RunLength;
		}
	/*------------*/
	/* ＥＯＬ検出 */
	/*------------*/
		if (runlen == EOL) {								/* ランレングス値がＥＯＬの時 */
			return(EOL);
	}
	/*----------------------*/
	/* ＭＨ－＞ＲＬ２次変換 */
	/*----------------------*/
		if (runlen & 0x8000) {									/* ランレングス値の２次テーブル参照必要ビットがオン */
			runlen &= ~0x8000;
			mp->DecData.Byte.L = mp->DecData.Byte.H;			/* チェック済みＭＨデータを１バイト廃棄 */
			mp->DecData.Byte.H = 0;
			mp->DecBits -= 8;									/* ## 注意１ ## */
			if (mp->DecBits < 5) {								/* ＭＨデータが２次テーブル参照必要ビット数（５）以下  MH符号はMAX13ﾋﾞｯﾄだから */
				decdata = MdmRead(mp->Rp,8);
				if (SCD_G3ReadStatus == RCV_STOP) {
					return(RX_STOPPED);
				}
				else if (SCD_G3ReadStatus != RCV_BLOCK) {
					return(RX_CARRIER_DOWN);
				}
/*				mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
				decdata <<= mp->DecBits;
				mp->DecData.Word |= decdata;
				mp->DecBits += 8;
			}
			tblno = (UWORD)(MH_DC_TableSub[runlen].MaskBit & mp->DecData.Byte.L);
			runlen = MH_DC_TableSub[runlen].Adr[tblno].RunLength;
		}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		tblno = runlen;											/* テーブルの配列番号にランレングス値をセット（ターミネートの時）*/
		if (runlen > 63) {										/* メイクアップの時 */
		tblno = (runlen/64) + 63;							/* テーブルの配列番号[64]以降なので，64で割った商に63を足す */
		}
		if (a_color == WHITE) {						/* 白レン */
			bitlen = MH_EC_WhiteTableMain[tblno].BitLength;
		}
		else {										/* 黒レン */
			bitlen = MH_EC_BlackTableMain[tblno].BitLength;
		}
		if (bitlen > 8) {							/**	変換ビット数が８ビット以上	**/
			bitlen -= 8;							/* 9ﾋﾞｯﾄ以上ということは２次ﾃｰﾌﾞﾙを参照したということで，注意１ですでにScdMHBitsが８ひかれている */
		}											/**	既に８ビット分廃棄しているのでその分を差し引く	**/
		mp->DecData.Word >>= bitlen;				/**	 変換済みビット廃棄	 **/
		mp->DecBits -= bitlen;						/**  未変換ビット数算出	 **/
	/*---------------------------------------------------------*/
	/* ＲＬのＰＵＴ,メイクアップの時に同一色のレングス数の変換 */
	/*---------------------------------------------------------*/
		runcnt += runlen;				        	/**	 同一色のレングス数を更新	**/
		if (runlen <= 63) {							/**	 変換した値がターミネートの時	**/
			return(runcnt);
		}          									/* 1 runlength ＭＨDecode終わり*/
	}while (runlen > 63);
}

/*************************************************************************
	module		:[ＥＯＬDETECT]
	function	:[
		1.
	]
	return		:[
				  RX_CARRIER_DOWN				5
				  EOL_FOUND                    15
                  MH_EOL_FOUND                 16
                  MR_EOL_FOUND                 17
				  ]
	common		:[
				  MemReadStatus
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref. PAT_ScdCheckEOL(unsigned char mhdata, unsigned char *ptnp)
				 ]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.18]
	author		:[S.Wang]
*************************************************************************/
UBYTE Mdm_DetectEOL(struct CdcBlk_t *dp)
{
	WORD 	result;
	UWORD	decdata;
	UWORD   carrydowndet;
	UBYTE eoldet;

	eoldet = 0;
	carrydowndet = 0;   /* ＥＯＬチェック済みデータのバイト数 */

	while (1) {		   /* ＥＯＬを見つける間  */
		if (carrydowndet >= SCD_CarryDownBlock * 256) {
			return(RX_CARRIER_DOWN);
		}
		if (dp->DecBits < 8) {			/* ＭＨ／ＭＲデータが１バイト以下 */
			decdata = MdmRead(dp->Rp,8);
			if (SCD_G3ReadStatus == RCV_STOP) {
				return(RX_STOPPED);
			}
			else if (SCD_G3ReadStatus != RCV_BLOCK) {
				return(RX_CARRIER_DOWN);
			}
/*			dp->DecData.Word |= decdata << dp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= dp->DecBits;
			dp->DecData.Word |= decdata;
			dp->DecBits += 8;
		}
		result = ScdcCheckEOL(dp->DecData.Byte.L, &eoldet);			/* ＥＯＬ検索を実行 */
/*		if (result == -1) { 										* ＥＯＬ検出ＮＧ *
			return (RX_ERROR);
		} revised by S.Wang 96/06/10 */
#if(0)
** 		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
** 			if (dp->Coding == SYS_MH_CODE) {
** 				dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 				dp->DecBits -= result;
** 				return(EOL_FOUND);
** 			}
** 			else {
** 				if (result < 8) {										/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
** 					}
** 				}
** 				if (result == 8) {
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					dp->DecBits -= result;
** 					if (dp->DecBits < 8) {								/* ＭＨ／ＭＲデータが１バイト以下 */
** 						decdata = MdmRead(dp->Rp,8);
** 						if (SCD_G3ReadStatus == RCV_STOP) {
** 							return(RX_STOPPED);
** 						}
** 						else if (SCD_G3ReadStatus != RCV_BLOCK) {
** 							return(RX_CARRIER_DOWN);
** 						}
** 						decdata <<= dp->DecBits;
** 						dp->DecData.Word |= decdata;
** 						dp->DecBits += 8;
** 					}
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MR_EOL_FOUND);
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MH_EOL_FOUND);
** 					}
** 				}
** 			}
** 		}
#endif		/* 上記のプログラムは以下のような変更 S.Wang 96/04/17 */
		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
			dp->DecData.Word >>= result;							/* ＥＯＬビットを廃棄 */
			dp->DecBits -= result;
			if (dp->Coding == SYS_MH_CODE) {
				return(EOL_FOUND);
			}														/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
			else {
				if (dp->DecBits < 1) {								/* 	ＥＯＬ_0/ＥＯＬ_1検出するのは次の1ﾋﾞｯﾄデータ参照必要 */
					decdata = MdmRead(dp->Rp,8);
					if (SCD_G3ReadStatus == RCV_STOP) {
						return(RX_STOPPED);
					}
					else if (SCD_G3ReadStatus != RCV_BLOCK) {
						return(RX_CARRIER_DOWN);
					}
					decdata <<= dp->DecBits;
					dp->DecData.Word |= decdata;
					dp->DecBits += 8;
				}
				if ((dp->DecData.Word & 0x0001) == 0) {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
					dp->DecBits -= 1;
					return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
				}
				else {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
					dp->DecBits -=1;
					return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
				}
			}
		}
		else { /* ＥＯＬ検出ＮＧ(result=-1) or ＥＯＬ検出中(result=0) */
			dp->DecData.Byte.L = dp->DecData.Byte.H;		/* チェック済みＭＨデータを１バイト廃棄 */
			dp->DecData.Byte.H = 0;
			dp->DecBits -= 8;
			carrydowndet ++;
		}
	}
}

/*************************************************************************
	module		:[ＭＲデータをＭＲｍｏｄｅに展開]
	function	:[
		1.
	]
	return		:[
				  ERR        -1
				  EOL        -2
				  mode       ＭＲ ｍｏｄｅ
	             ]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
BYTE Mdm_MRDataToMode(struct CdcBlk_t *mrp)
{
	UWORD 	decdata;						/*	ＭＲデータ */
	BYTE	mode;							/*	ＭＲ ｍｏｄｅ	*/
	UBYTE	bitlen;					/*	ＭＲテーブルのビット長	*/

	if (mrp->DecBits < 8) {			/* ＭＨ／ＭＲデータが１バイト以下 */
		decdata = MdmRead(mrp->Rp,8);
		if (SCD_G3ReadStatus == RCV_STOP) {
			return(RX_STOPPED);
		}
		else if (SCD_G3ReadStatus != RCV_BLOCK) {
			return(RX_CARRIER_DOWN);
		}
/*	mrp->DecData.Word |= decdata << mrp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
		decdata <<= mrp->DecBits;
		mrp->DecData.Word |= decdata;
		mrp->DecBits += 8;
	}
	/*----------------------*/
	/* ＭＲ－＞ＭＯＤＥ変換 */
	/*----------------------*/
	mode = MR_DC_TableMain[mrp->DecData.Byte.L].ModeType;
	if (mode == ERR) {
		return(ERR);
	}
	if (mode == EOL) {
		return(EOL);
	}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		bitlen = MR_EC_TableMain[mode].BitLength;
		mrp->DecData.Word >>= bitlen;					/**	 変換済みビット廃棄	 **/
		mrp->DecBits -= bitlen;							/**  未変換ビット数算出	 **/
		return(mode);
}

/*************************************************************************
	module		:[RTC/EOFB DETECT]
	function	:[
		1.
	]
	return		:[
				  TX_MEM_ERR                    7
	              RTC						    14
				  ]
	common		:[]
	condition	:[内蔵ＲＯＭ
					(1)RTC検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]３つ検出 --->
					   [00...0+(EOL/EOL+0/EOL+1)]１つと[EOL]１つ検出
				    (2)EOFB検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]２つ検出 --->
				       [EOL]１つ検出
				                      ----S.Wang 96/06/20
				 ]
	comment		:[
					１） RTC Detect時に2個目のＥＯＬは必ず１１個０であること"000000000001"
					２） ライン開始のＥＯＬ検索処理Mem_DetectEOL(dec)で(Fill+EOL)
					   を見付けた。またDecodeTableで８個連続０を検出した。このサブ
					   ルーチンは引き続き"0001"を検出する
				 ]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1996.2.23]
	author		:[S.Wang]
	修正履歴    :[
					1996.6.20 S.Wang
				 ]

*************************************************************************/
UBYTE Mdm_DetectRTC(struct CdcBlk_t *dp)
{
#if(0)
** 	unsigned char ret;
** 
** 	ret = Mdm_DetectEOL(dp);
** 	if (ret == RX_CARRIER_DOWN) {
** 		return(RX_CARRIER_DOWN);
** 	}
** /*	else if (ret == RX_ERROR) {	 			* ＥＯＬ検出ＮＧ *
** 		return (RX_ERROR);
** 	} S.Wang 96/06/10 */
** 	else {									/* MR_EOL_FOUND/EOL_FOUND/MH_EOL_FOUND */
** 		ret = Mdm_DetectEOL(dp);
** 		if (ret == RX_CARRIER_DOWN) {
** 			return(RX_CARRIER_DOWN);
** 		}
** /*			else if (ret == RX_ERROR) {	 	* ＥＯＬ検出ＮＧ *
** 				return (RX_ERROR);
** 			} S.Wang 96/06/10 */
** 		else { 							/* MR_EOL_FOUND/EOL_FOUND/MH_EOL_FOUND */
** 			return(RTC); 				/* ＲＴＣ:連続ＥＯＬ三つを検出必要 */
** 		}                               /* ＥＯＦＢ:連続ＥＯＬ二つを検出必要  */
** 	}
#endif
    UWORD	decdata;

	dp->DecData.Word >>= 8;		/* Decode Tableで８個連続０を検出したので、変換済み８ビット廃棄 */
	dp->DecBits -= 8;			/* 未変換ビット数算出 */
	if (dp->DecBits < 4) {		/* ＭＨ／ＭＲデータが4ビット以下 */
		decdata = MdmRead(dp->Rp, 8);
		if (SCD_G3ReadStatus == RCV_STOP) {
			return(RX_STOPPED);
		}
		else if (SCD_G3ReadStatus != RCV_BLOCK) {
			return(RX_CARRIER_DOWN);
		}
		decdata <<= dp->DecBits;
		dp->DecData.Word |= decdata;
		dp->DecBits += 8;
	}
	if ((dp->DecData.Byte.L & 0x07) == 0) {		/* 今回3個連続０検出し、ここまできたということは０を１１個見付けた。 */
		if ((dp->DecData.Byte.L & 0x08) != 0) {	/* 次のビット１を見付けた。ＲＴＣ検出ＯＫ */
			return(RTC);
		}
		else {
			return(RX_ERROR);
		}
	}
	else {
		return(RX_ERROR);
	}
}

/*************************************************************
	module		:[Ecm_Decode]
	function	:[one line MH,MR,MMR decode ]
	return		:[
				  OK                            1
	              RX_CARRIER_DOWN				5
	              RX_ERROR						6
	              RTC						    14
	              RX_MEM_OVER					4 ダイレクト受信時のみ
	              ]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[1 line Decode]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1996/03/14]
	author		:[王　慎]
*************************************************************/
BYTE Ecm_DecodeIntRom(struct CdcBlk_t *dec,
					 struct WorkBuf_t *a_buf,
					 struct WorkBuf_t *b_buf)
{
	struct 	ScdcWorkData_t scdcdata, *scdcwork;
	UBYTE	rtn;							/* EOLsearch/MMLmodeのreturn値 */
	UBYTE	rtnrtc;							/* RTCsearchのreturn値 */
	UBYTE	rtneol;                         /* 画データの先頭に連続EOLsearchのreturn値 */
	WORD			runlen;							/* 白or黒ランのレングス/EOL値 */
	UWORD 			rl_b;							/* 参照ライン run length */
	WORD    		d;								/* a1-b1 */
	BYTE	        mode;							/* ＭＲmode */

	SCD_DBG_RLOVER = 0;/*	By Y.Suzuki 1997/01/28	*/


	scdcwork = &scdcdata;
	scdcwork->a_color = WHITE;
	scdcwork->b_color = WHITE;
	scdcwork->a_pos = 0;
	scdcwork->b_pos = 0;
	a_buf->Cout = 0;
	a_buf->Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	b_buf->Cout = 0;
	b_buf->Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */

	SCD_NgRl = 0;/*	By Y.Suzuki 1997/02/27	*/


		/*----------------------------*/
		/* ライン開始のＥＯＬ検索処理 */
		/*----------------------------*/
	if (dec->Coding == SYS_MMR_CODE) {
		rtn = MMR_FOUND;
	}
	else {
   		rtn = Ecm_DetectEOL(dec);
	}
#if(0) /* S.Wang 96.06.10 */
** 	if (rtn == RX_CARRIER_DOWN) {
** 		return(RX_CARRIER_DOWN);
** 	}
** 	if (rtn == RX_ERROR) {
** 		return(RX_ERROR);
** 	}
#endif
		/*-----------------------------------*/
		/*　  1 ライン分RUNLENGTHデコード 　 */
		/*-----------------------------------*/
	if ((rtn == EOL_FOUND) || (rtn == MH_EOL_FOUND)) {
		if (SCD_DirectRx) {/*	ダイレクトメモリ受信 By Y.Suzuki 1997/06/13	*/
			if (rtn == EOL_FOUND) {
				Mem_EOLWrite(EOL_NO, dec, 0) ;	 /* EOL 書き込む */
			}
			else {
				Mem_EOLWrite(EOL_MH_NO, dec, 0);	 /* EOL_MH 書き込む */
			}
		}
		/*----------------------------------*/
		/* １ライン分のＭＨ－＞ＲＬ変換処理 */
		/*----------------------------------*/
		while (1) {		/* レングス数をImg_Sizeまで */
			runlen = Ecm_MHDataToRL(dec, scdcwork->a_color);
			if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/09/11 */
				if (runlen == MEM_OVER) {
					return(RX_MEM_OVER);
				}
			}
			if (runlen == EOL) {    			/* ランレングス値がＥＯＬ(0x00検出した）の時 */
				if (scdcwork->a_pos == 0) {
					if (dec->Line_Cntr == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
						rtneol = Ecm_DetectEOL(dec);
					}
					else {
						rtnrtc = Ecm_DetectRTC(dec);
						if (rtnrtc == RX_ERROR) {
							return(RX_ERROR);
						}
						else {
							return(RTC);
						}
					}
				}
				else {
					return(RX_ERROR);
				}
			}
			else {
				/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
				if ((runlen == 0) && (a_buf->Cout != 0)) {
					SCD_NgRl = 3;
				}
				PutRL(a_buf, runlen, scdcwork->a_color);         /* Put one runlength to Buffer RL */
				if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
					return(RX_ERROR);
				}
				scdcwork->a_pos += runlen;						/*	レングス数を更新(count)	*/
				if (scdcwork->a_pos == dec->Img_Size) {
 					break;
				}
				if (scdcwork->a_pos > dec->Img_Size) {
					return(RX_ERROR);
				}
				scdcwork->a_color = (UBYTE)(!scdcwork->a_color);			/**	処理中の画素色を反転させる	**/
			}
		}														/*	１ラインＭＨDecode終わり*/
	}
	else {  /* rtn == MR_EOL_FOUND or rtn == MMR_FOUND */
		if (SCD_DirectRx) {/*	ダイレクトメモ受送信 By Y.Suzuki 1997/06/13	*/
			if (rtn == MR_EOL_FOUND) {
				Mem_EOLWrite(EOL_MR_NO, dec, 0); /* EOL_MR 書き込む */
			}
		}
		/*------------------------------------------*/
		/* １ライン分のＭＲ／ＭＭＲ－＞ＲＬ変換処理 */
		/*------------------------------------------*/
		scdcwork->a0 = 0;
		scdcwork->a1 = 0;
		scdcwork->b0 = 0;
		scdcwork->V0_Count = 0;
		scdcwork->V0_Flag = 0;
		scdcwork->V0_Begin = 0;
		scdcwork->V0_End = 0;
		do {      												/* a0はImg_Sizeになるまで */
			while ((scdcwork->b_pos <= scdcwork->a0) || ((scdcwork->b_pos > scdcwork->a0) && (scdcwork->a_color == scdcwork->b_color))) { 	/* b_pos 検出 */
				scdcwork->b0 = scdcwork->b_pos; 				/* 更新する前の参照ラインの位置b0を記録 */
				if (scdcwork->b_pos < dec->Img_Size) {
					rl_b = GetRL(b_buf);
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if ((scdcwork->b_pos == 0) && (scdcwork->b0 == 0)) { /* 参照ラインの頭は黒の時(白RL=0) */
						break;
					}
				}
				else {
					/*	ラインの最後でＶＬ参照ラインポインタ戻し処理を行うため By Y.Suzuki 1997/09/15	*/
					if (scdcwork->a_color != scdcwork->b_color) {
						scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					/*	SCD_MaintenanceSwitch[SCD_MNT_SW_F1] |= 0x08;*/
					}
				    break;
				}
			}													/* b_pos 検出した */
			mode = Ecm_MRDataToMode(dec);
			/*--------------------------*/
			/* ＭＲ／ＭＭＲ－＞ＲＬ変換 */
			/*--------------------------*/
			if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/09/11 */
				if (mode == MEM_OVER) {
					return(RX_MEM_OVER);
				}
			}
			if (mode == ERR) {
				return(RX_ERROR);
			}
			else if (mode == EOL) {    /* mode値がＥＯＬ(0x00検出した）の時 */
				/*------------*/
				/* ＥＯＬ検出 */
				/*------------*/
				if (scdcwork->a_pos == 0) {
					if (dec->Line_Cntr == 0) { /* 画データの先頭に連続ＥＯＬを見付けてもＲＴＣとせず S.Wang 96/06/10 */
						rtneol = Ecm_DetectEOL(dec);
					}
					else {
						rtnrtc = Ecm_DetectRTC(dec);
						if (rtnrtc == RX_ERROR) {
							return(RX_ERROR);
						}
						else {
							return(RTC);
						}
					}
				}
				else {
					return(RX_ERROR);
				}
			}
			else if (mode == V0_MODE) {  						/* V0 mode */
				scdcwork->V0_Count ++;						/* V0mode個数のcount */
				if (scdcwork->V0_Flag == 0) { 				/* 最初のV0mode */
					scdcwork->V0_Begin = b_buf->Cout;     	/* V0モードのバイド最初位置　*/
					scdcwork->a1 = scdcwork->b_pos;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					scdcwork->V0_Flag = 1;
				}
				else {									    /* 連続V0モード */
					/*if (scdcwork->V0_Count > 1) { このif条件は要りません S.Wang 96/03/15 */
						scdcwork->a1 = scdcwork->b_pos;
						scdcwork->a_pos = scdcwork->a1;
						scdcwork->a0 = scdcwork->a1;
						scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					/*}*/
					if (scdcwork->V0_Count == V0_MAX_COUNT || scdcwork->a_pos == dec->Img_Size) {
						scdcwork->V0_End = b_buf->Cout;		/* 連続V0モードのバイド終了位置　 */
						PutV0(scdcwork, a_buf, b_buf);		/* 連続V0モードデータを格納する */
						scdcwork->V0_Flag = 0;
						scdcwork->V0_Count = 0;
					}
				}
			}
			else {
				if (scdcwork->V0_Flag == 1) {
					if (rl_b >= 64) {  						/* rl_b は２バイドでデータを格納する時の連続V0モードのバイド終了位置 */
						scdcwork->V0_End = b_buf->Cout - 2;
					}
					else {
						scdcwork->V0_End = b_buf->Cout - 1; /* rl_b は１バイドでデータを格納する時の連続V0モードのバイド終了位置 */
					}
					PutV0(scdcwork, a_buf, b_buf);			/* 連続V0モードデータを格納する */
					scdcwork->V0_Flag = 0;
					scdcwork->V0_Count = 0;
				}
				if (mode == H_MODE) {
					runlen = Ecm_MHDataToRL(dec, scdcwork->a_color);
					if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/09/11 */
						if (runlen == MEM_OVER) {
							return(RX_MEM_OVER);
						}
					}
					scdcwork->a1 = scdcwork->a0 + runlen;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, scdcwork->a1-scdcwork->a_pos, scdcwork->a_color);	/* Put one runlength to Buffer RL */
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;							/*	レングス数を更新(count)	*/
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					runlen = Ecm_MHDataToRL(dec,scdcwork->a_color);
					if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/09/11 */
						if (runlen == MEM_OVER) {
							return(RX_MEM_OVER);
						}
					}
					scdcwork->a_pos += runlen;							/*	a2 検出 */
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					if ((scdcwork->a_pos == dec->Img_Size) && (runlen == 0)) {
						/* PutRL 無し */
					}
					else {
						/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
						if ((runlen == 0) && (a_buf->Cout != 0)) {
							SCD_NgRl = 3;
						}
						PutRL(a_buf, runlen, scdcwork->a_color);          /* Put one runlength to Buffer RL */
						if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
							return(RX_ERROR);
						}
					}
					scdcwork->a0 = scdcwork->a_pos;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
				}
				if (mode == P_MODE) {
					scdcwork->b0 = scdcwork->b_pos; 			/* 更新する前の参照ラインの位置b0を記録 */
					rl_b = GetRL(b_buf);  						/* b2 検出 */
					scdcwork->b_pos += rl_b;
					scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
					if (scdcwork->b_pos >= dec->Img_Size) {
						scdcwork->b_pos = dec->Img_Size;
					}  										   	/* b2 検出した */
					scdcwork->a0 = scdcwork->b_pos;
				}
				if (2 <= mode && mode <= 8 && mode != 5) {      /* V_MODE (V0_MODE除く) */
					d = mode - 5;
					scdcwork->a1 = scdcwork->b_pos + d;
					runlen = scdcwork->a1 - scdcwork->a_pos;
					/* ＲＬバッファの先頭以外に０をライトしたら エラーとする By Y.Suzuki 1998/01/21 */
					if ((runlen == 0) && (a_buf->Cout != 0)) {
						SCD_NgRl = 3;
					}
					PutRL(a_buf, runlen, scdcwork->a_color);
					if (SCD_NgRl) {		/*	デコードした結果のＲＬ値が異常 By Y.Suzuki 1997/03/11	*/
						return(RX_ERROR);
					}
					scdcwork->a_pos = scdcwork->a1;
					scdcwork->a0 = scdcwork->a1;
					scdcwork->a_color = (UBYTE)(!scdcwork->a_color);
					if (scdcwork->a_pos > dec->Img_Size) {
						return(RX_ERROR);
					}
					if (d < -1) {     							/* VL(2) or VL(3) modeの特例 次の参照ラインb_posの検出 */
						if ((scdcwork->b0 != 0) && (scdcwork->b0 > scdcwork->a0)) {
							if (rl_b >= 64) {  				/* rl_b は２バイドでデータを格納する時 */
								b_buf->Cout -= 2;
							}
							else {
								b_buf->Cout -= 1;			/* rl_b は１バイドでデータを格納する時 */
							}
							scdcwork->b_color = (UBYTE)(!scdcwork->b_color);
							scdcwork->b_pos = scdcwork->b0;
						}
					}
				}
			}
		}while(scdcwork->a0 < dec->Img_Size);
	}
	if (scdcwork->a0 > dec->Img_Size) {/*	By Y.Suzuki 1997/01/28	*/
		SCD_DBG_RLOVER = 3;
	}
	dec->Line_Cntr ++; /* ｺｰﾃﾞｯｸライン数Countのincrement */
	return(OK);
}


/*************************************************************************
	module		:[ＭＨデータをRUNLENGTHに展開]
	function	:[
		1.
	]
	return		:[EOL        -2
				  runcnt	 ランレングス
				  MEM_OVER   -3 ダイレクト受信のみ
				  ]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref.PAT_ScdMHtoImage(unsigned char *image_buf, unsigned int  side_margin)]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
WORD Ecm_MHDataToRL(struct CdcBlk_t *mp, UBYTE a_color)
{
	UWORD 			decdata;						/*	ＭＨデータ */
	WORD			runlen;							/*	白or黒ランレングス	*/
	UWORD			tblno;							/*	テーブルＮｏ			*/
	UWORD			runcnt;							/*  同一色のランレングス数  メイクアップ + ターミネート   */
	UBYTE	bitlen;							/*	ＭＨデータのビット長	*/
	WORD			retdata;

	runcnt = 0;
	/*----------------------*/
	/* ＭＨ－＞ＲＬ１次変換 */
	/*----------------------*/
	do {
		if (mp->DecBits < 8) {		/* ＭＨデータが１次テーブル参照必要ビット数（８）以下 */
			decdata = EcmRead(mp->Rp, 8);
/*			mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= mp->DecBits;
			mp->DecData.Word |= decdata;
			mp->DecBits += 8;
		}
		if (a_color == WHITE) {							/*	白レン	*/
			runlen = MH_DC_WhiteTableMain[mp->DecData.Byte.L].RunLength;
		}
		else {											/*	黒レン	*/
			runlen = MH_DC_BlackTableMain[mp->DecData.Byte.L].RunLength;
		}
	/*------------*/
	/* ＥＯＬ検出 */
	/*------------*/
		if (runlen == EOL) {								/* ランレングス値がＥＯＬの時 */
			return(EOL);
	}
	/*----------------------*/
	/* ＭＨ－＞ＲＬ２次変換 */
	/*----------------------*/
		if (runlen & 0x8000) {									/* ランレングス値の２次テーブル参照必要ビットがオン */
			if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/06/13 */
				retdata = MemWrite(mp->Wp,8,mp->DecData.Word);
				if (retdata == RX_MEM_OVER) {
					return(MEM_OVER);
				}
			}
			runlen &= ~0x8000;
			mp->DecData.Byte.L = mp->DecData.Byte.H;			/* チェック済みＭＨデータを１バイト廃棄 */
			mp->DecData.Byte.H = 0;
			mp->DecBits -= 8;									/* ## 注意１ ## */
			if (mp->DecBits < 5) {								/* ＭＨデータが２次テーブル参照必要ビット数（５）以下  MH符号はMAX13ﾋﾞｯﾄだから */
				decdata = EcmRead(mp->Rp,8);
/*				mp->DecData.Word |= decdata << mp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
				decdata <<= mp->DecBits;
				mp->DecData.Word |= decdata;
				mp->DecBits += 8;
			}
			tblno = (UWORD)(MH_DC_TableSub[runlen].MaskBit & mp->DecData.Byte.L);
			runlen = MH_DC_TableSub[runlen].Adr[tblno].RunLength;
		}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		tblno = runlen;											/* テーブルの配列番号にランレングス値をセット（ターミネートの時）*/
		if (runlen > 63) {										/* メイクアップの時 */
		tblno = (runlen/64) + 63;							/* テーブルの配列番号[64]以降なので，64で割った商に63を足す */
		}
		if (a_color == WHITE) {						/* 白レン */
			bitlen = MH_EC_WhiteTableMain[tblno].BitLength;
		}
		else {										/* 黒レン */
			bitlen = MH_EC_BlackTableMain[tblno].BitLength;
		}
		if (bitlen > 8) {							/**	変換ビット数が８ビット以上	**/
			bitlen -= 8;							/* 9ﾋﾞｯﾄ以上ということは２次ﾃｰﾌﾞﾙを参照したということで，注意１ですでにScdMHBitsが８ひかれている */
		}											/**	既に８ビット分廃棄しているのでその分を差し引く	**/
		if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/06/13 */
			retdata = MemWrite(mp->Wp,bitlen,mp->DecData.Word);
			if (retdata == RX_MEM_OVER) {
				return(MEM_OVER);
			}
		}
		mp->DecData.Word >>= bitlen;				/**	 変換済みビット廃棄	 **/
		mp->DecBits -= bitlen;						/**  未変換ビット数算出	 **/
	/*---------------------------------------------------------*/
	/* ＲＬのＰＵＴ,メイクアップの時に同一色のレングス数の変換 */
	/*---------------------------------------------------------*/
		runcnt += runlen;				        	/**	 同一色のレングス数を更新	**/
		if (runlen <= 63) {							/**	 変換した値がターミネートの時	**/
			return(runcnt);
		}          									/* 1 runlength ＭＨDecode終わり*/
	}while (runlen > 63);
}

/*************************************************************************
	module		:[ＥＯＬDETECT]
	function	:[
		1.
	]
	return		:[
				  EOL_FOUND                    15
                  MH_EOL_FOUND                 16
                  MR_EOL_FOUND                 17
				  ]
	common		:[
				  MemReadStatus
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[Ref. PAT_ScdCheckEOL(UBYTE mhdata, unsigned char *ptnp)
			ＥＯＬを見つけるまで検出続ける。EOL検出不可能エラーは上位で判断。 S.Wang 96/06/10
				 ]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.18]
	author		:[S.Wang]
*************************************************************************/
UBYTE Ecm_DetectEOL(struct CdcBlk_t *dp)
{
	WORD 	result;
	UWORD	decdata;
	/*UWORD   carrydowndet;*/
	UBYTE eoldet;

	eoldet = 0;
	/*carrydowndet = 0;    ＥＯＬチェック済みデータのバイト数 */

	while (1) {		   /* ＥＯＬを見つける間  */
#if(0)
** 		if (carrydowndet >= SCD_CarryDownBlock * 256) {
** 			return(RX_CARRIER_DOWN);
** 		}
#endif
		if (dp->DecBits < 8) {			/* ＭＨ／ＭＲデータが１バイト以下 */
			decdata = EcmRead(dp->Rp,8);
/*			dp->DecData.Word |= decdata << dp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
			decdata <<= dp->DecBits;
			dp->DecData.Word |= decdata;
			dp->DecBits += 8;
		}
		result = ScdcCheckEOL(dp->DecData.Byte.L, &eoldet);			/* ＥＯＬ検索を実行 */
/*		if (result == -1) { 										* ＥＯＬ検出ＮＧ *
			return (RX_ERROR);
		} revised by S.Wang 96/06/10 */
#if(0)
** 		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
** 			if (dp->Coding == SYS_MH_CODE) {
** 				dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 				dp->DecBits -= result;
** 				return(EOL_FOUND);
** 			}
** 			else {
** 				if (result < 8) {										/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= (result + 1);
** 						return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
** 					}
** 				}
** 				if (result == 8) {
** 					dp->DecData.Word >>= result;						/* ＥＯＬビットを廃棄 */
** 					dp->DecBits -= result;
** 					if (dp->DecBits < 8) {								/* ＭＨ／ＭＲデータが１バイト以下 */
** 						decdata = EcmRead(dp->Rp,8);
** 						decdata <<= dp->DecBits;
** 						dp->DecData.Word |= decdata;
** 						dp->DecBits += 8;
** 					}
** 					if ((dp->DecData.Word & 0x0001) == 0) {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MR_EOL_FOUND);
** 					}
** 					else {
** 						dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
** 						dp->DecBits -= 1;
** 						return(MH_EOL_FOUND);
** 					}
** 				}
** 			}
** 		}
#endif 		/* 上記のプログラムは以下のような変更 S.Wang 96/04/17 */
		if ((result >= 1) && (result <= 8)) {						/* ＥＯＬを検出した */
			dp->DecData.Word >>= result;							/* ＥＯＬビットを廃棄 */
			dp->DecBits -= result;
			if (dp->Coding == SYS_MH_CODE) {
				return(EOL_FOUND);
			}														/* ＥＯＬ_0(0000000000010)/ＥＯＬ_1(0000000000011)検出 */
			else {
				if (dp->DecBits < 1) {								/* 	ＥＯＬ_0/ＥＯＬ_1検出するのは次の1ﾋﾞｯﾄデータ参照必要 */
					decdata = EcmRead(dp->Rp,8);
					decdata <<= dp->DecBits;
					dp->DecData.Word |= decdata;
					dp->DecBits += 8;
				}
				if ((dp->DecData.Word & 0x0001) == 0) {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_0の最後ビットを廃棄 */
					dp->DecBits -= 1;
					return(MR_EOL_FOUND);							/* ＥＯＬ_0を検出した */
				}
				else {
					dp->DecData.Word >>= 1;							/* ＥＯＬ_1の最後ビットを廃棄 */
					dp->DecBits -=1;
					return(MH_EOL_FOUND);							/* ＥＯＬ_1を検出した */
				}
			}
		}
		else { /* ＥＯＬ検出ＮＧ(result=-1) or ＥＯＬ検出中(result=0) */
			dp->DecData.Byte.L = dp->DecData.Byte.H;		/* チェック済みＭＨデータを１バイト廃棄 */
			dp->DecData.Byte.H = 0;
			dp->DecBits -= 8;
			/*carrydowndet ++;*/
		}
	}
}

/*************************************************************************
	module		:[ＭＲデータをＭＲｍｏｄｅに展開]
	function	:[
		1.
	]
	return		:[
				  ERR        -1
				  EOL        -2
				  mode       ＭＲ ｍｏｄｅ
				  MEM_OVER   -3 ダイレクト受信のみ
	             ]
	common		:[
					dec->DecBits
					dec->DecData
	]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.12.04]
	author		:[S.Wang]
*************************************************************************/
BYTE Ecm_MRDataToMode(struct CdcBlk_t *mrp)
{
	UWORD 	decdata;						/*	ＭＲデータ */
	BYTE	mode;							/*	ＭＲ ｍｏｄｅ	*/
	UBYTE	bitlen;					/*	ＭＲテーブルのビット長	*/
	BYTE	retdata;

	if (mrp->DecBits < 8) {			/* ＭＨ／ＭＲデータが１バイト以下 */
		decdata = EcmRead(mrp->Rp,8);
/*	mrp->DecData.Word |= decdata << mrp->DecBits;この行を以下２行に変更 Y.S 96/1/20 */
		decdata <<= mrp->DecBits;
		mrp->DecData.Word |= decdata;
		mrp->DecBits += 8;
	}
	/*----------------------*/
	/* ＭＲ－＞ＭＯＤＥ変換 */
	/*----------------------*/
	mode = MR_DC_TableMain[mrp->DecData.Byte.L].ModeType;
	if (mode == ERR) {
		return(ERR);
	}
	if (mode == EOL) {
		return(EOL);
	}
	/*---------------------------------------------*/
	/* 次のdecdataのreadのため、未変換ビット数算出 */
	/*---------------------------------------------*/
		bitlen = MR_EC_TableMain[mode].BitLength;
		if (SCD_DirectRx) {/* ダイレクトメモリ受信 By Y.Suzuki 1997/06/13 */
			retdata = MemWrite(mrp->Wp,bitlen,mrp->DecData.Word);
			if (retdata == RX_MEM_OVER) {
				return(MEM_OVER);
			}
		}
		mrp->DecData.Word >>= bitlen;					/**	 変換済みビット廃棄	 **/
		mrp->DecBits -= bitlen;							/**  未変換ビット数算出	 **/
		return(mode);
}

/*************************************************************************
	module		:[RTC/EOFB DETECT]
	function	:[
		1.
	]
	return		:[
				  RX_ERROR						6
	              RTC						    14
				  ]
	common		:[]
	condition	:[内蔵ＲＯＭ
					(1)RTC検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]３つ検出 --->
					   [00...0+(EOL/EOL+0/EOL+1)]１つと[EOL]１つ検出
				    (2)EOFB検出必要条件:[00...0+(EOL/EOL+0/EOL+1)]２つ検出 --->
				       [EOL]１つ検出
				                      ----S.Wang 96/06/20
				 ]
	comment		:[
					１） RTC Detect時に2個目のＥＯＬは必ず１１個０であること"000000000001"
					２） ライン開始のＥＯＬ検索処理Mem_DetectEOL(dec)で(Fill+EOL)
					   を見付けた。またDecodeTableで８個連続０を検出した。このサブ
					   ルーチンは引き続き"0001"を検出する
				 ]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1996.2.23]
	author		:[S.Wang]
	修正履歴    :[
					1996.6.20 S.Wang
				 ]

*************************************************************************/
UBYTE Ecm_DetectRTC(struct CdcBlk_t *dp)
{
#if(0)
** 	unsigned char ret;
** 
** 	ret = Ecm_DetectEOL(dp);
** 	ret = Ecm_DetectEOL(dp);
** 	return(RTC); 				/* ＲＴＣ:連続ＥＯＬ三つを検出必要 */
**                               	/* ＥＯＦＢ:連続ＥＯＬ二つを検出必要  */
#endif
    UWORD	decdata;

	dp->DecData.Word >>= 8;		/* Decode Tableで８個連続０を検出したので、変換済み８ビット廃棄 */
	dp->DecBits -= 8;			/* 未変換ビット数算出 */
	if (dp->DecBits < 4) {		/* ＭＨ／ＭＲデータが4ビット以下 */
		decdata = EcmRead(dp->Rp, 8);
		decdata <<= dp->DecBits;
		dp->DecData.Word |= decdata;
		dp->DecBits += 8;
	}
	if ((dp->DecData.Byte.L & 0x07) == 0) {		/* 今回3個連続０検出し、ここまできたということは０を１１個見付けた。 */
		if ((dp->DecData.Byte.L & 0x08) != 0) {	/* 次のビット１を見付けた。ＲＴＣ検出ＯＫ */
			return(RTC);
		}
		else {
			return(RX_ERROR);
		}
	}
	else {
		return(RX_ERROR);
	}
}

/*************************************************************************
	module		:[ＥＯＬチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[ Ref. PAT_ScdCheckEOL(unsigned char mhdata, unsigned char *ptnp)]
	machine		:[]
	language	:[]
	keyword		:[SCDC]
	date		:[1995.11.23]
	author		:[S.Wang]
*************************************************************************/
WORD ScdcCheckEOL(UBYTE decdata, UBYTE *ptnp)
{
	WORD			ret;						/*	リターンコード	*/
	UBYTE	ptn;
	UBYTE	maskbit;

	ptn = *ptnp;									/* 前回検出の連続０の個数をひっぱてくる */
	ret = -1;										/**	ＥＯＬ検出ＮＧセット	*/
	if (ptn != 0) {									/**	前回連続０検出している	*/
		if (ptn >= 11) {							/**	前回１１連続０検出済み	*/
			ret = 0;								/**	ＥＯＬ検出中をセット	*/
			if (decdata != 0) {
				ret = 1;							/**	ＥＯＬ検出ＯＫセット	*/
			}
		}
		else if (ptn >= 4) {							/* 今回の８ビットでＥＯＬを検出する可能性がある */
			maskbit= (UBYTE)(0xff >> ptn - 3);	/* 今回で０が連続１１続くためにはあと何ビット必要か算出 11-8 = 3 */
			if ((decdata & maskbit) == 0) {				/* 今回１１連続０検出した	*/
				ptn = 11;
				ret = 0;								/**	ＥＯＬ検出中をセット	*/
				if ((decdata & (~maskbit)) != 0) {		/* ここまできたということは０を１１みつけて、あとは１をみつけるだけ */
					ret = 1;							/**	ＥＯＬ検出ＯＫセット	*/
				}
			}
		}
		else {										/* 今回の８ビットでＥＯＬを検出する可能性がない */
			if (decdata == 0) {
				ptn += 8;
				ret = 0;							/**	ＥＯＬ検出中をセット	*/
			}
		}
	}

	if (ret == 1) {									/**	ＥＯＬ検出ＯＫ時		*/
		/**	検出に使用したビット数を算出	**/
		for (maskbit = 0x01; (decdata & maskbit) == 0; maskbit <<= 1) {
			ret++;
		}
	}
	/*----------------------------------------------------------------------*/
	/*	前回連続０未検出時－＞連続０が有れば検出中，無ければＮＧリターン	*/
	/*	今回検出ＮＧの時　－＞再度連続０を検索するが，ＮＧリターンさせる	*/
	/*	今回検出ＯＫの時　－＞再度連続０を検索し，ＯＫリターンさせる		*/
	/*----------------------------------------------------------------------*/
	if (ret != 0) {								/**	ＥＯＬ検出ＯＫ／ＮＧ時	*/
												/** ＥＯＬ検出中でないとき  */
		if (ptn == 0) {							/**	前回連続０なし			*/
			if ((decdata & 0x80) == 0) {	    /**	１個以上ゼロ有り	    */
				ret = 0;						/**	ＥＯＬ検出中をセット	*/
				if (decdata == 0) {				/**	８連続ゼロ有り			*/
					*ptnp = 8;
					return(ret);				/**	ＥＯＬ検出中リターン	*/
				}
			}
		}
		for (ptn = 0; (decdata & 0x80) == 0; ptn++) { 	/* 今回０が何ビット続くかチェック */
			decdata <<= 1;
		}
	}
	*ptnp = ptn;										/* ０が続いたビット数を格納 */
	return(ret);
}

/************************************************************************************************************************
	module		:[RUN_LENGTHデータの格納する]
	function	:[
		1.１バイトＲＬデータor2バイトＲＬデータを格納する。
		2.2560 以上のRLを格納する場合、2560 + X  2560をｾｯﾄ後、同じカラーで次のバッファに残りXをセットする。
	return		:[]
	common		:[]
                                                         7(データflag) 6(colorflag)    5 4 3 2 1 0  7 6 5 4 3 2 1 0
	condition	:[内蔵ＲＯＭ
                  1, rl<=63１バイトでＲＬデータを格納仕様: 0(１バイト)  0/1(white/black) * * * * * *
	                 rl>=64 2バイトでＲＬデータを格納仕様: 1(２バイト)  0/1(white/black) * * * * * *  * * * * * * * *
                                                           |<-------------------１バイト目 ---------->|<--２バイト目-->|
	              2, 連続 rl=0 の場合、rlをｒｌ＿ｂｕｆへ書かない(point->Flagはrl=0のFlag）S.Wang 96/07/04

	             ]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver6.0)]
	keyword		:[SCDC]
	date		:[1995/11/18]
	author		:[S.Wang]
*************************************************************************************************************************/
/* #pragma inline (PutRL)*/
void PutRLIntRom(struct WorkBuf_t *point, UWORD rl, UBYTE a_color)

{
	UWORD word_data;
	UBYTE byte_data;

	byte_data = 0;
	word_data = 0;

	if (rl > 4864) {/*	By Y.Suzuki 1997/02/08	*/
		SCD_NgRl = 1;
	}
	if (rl & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
		SCD_NgRl = 2;
	}
	if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
		return;
	}
	if (rl <= 0x003F) {
		if (a_color == WHITE) {
			byte_data = (UBYTE)rl;
			*(point->Data + point->Cout) = byte_data;
			point->Cout ++;
		}
		else {
			word_data = rl | 0x0040;
			byte_data = (UBYTE)word_data;
			*(point->Data + point->Cout) = byte_data;
			point->Cout ++;
		}
		return; /*break;*/
	}
	else {
		if (a_color == WHITE) {
			rl |= 0x8000;
			word_data = rl & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(point->Data + point->Cout) =  byte_data;
			point->Cout ++;
			byte_data = (UBYTE)(rl & 0x00FF);
			*(point->Data + point->Cout) =  byte_data;
			point->Cout ++;
		}
		else {
			rl |= 0xC000;
			word_data = rl & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(point->Data + point->Cout) =  byte_data;
			point->Cout ++;
			byte_data = (UBYTE)(rl & 0x00FF);
			*(point->Data + point->Cout) =  byte_data;
			point->Cout ++;
		}
	}
}

/***************************************************************************
	module		:[V0_MODEのRUN_LENGTHデータの格納する]
	function	:[
		1.連続V0_MODEのRUN_LENGTHデータの格納する
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver6.0)]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[S.Wang]
***************************************************************************/
/*#pragma inline (PutV0)*/
void PutV0(struct ScdcWorkData_t *point, struct WorkBuf_t *ap, struct WorkBuf_t *bp)
{
    UWORD i;

    for (i = point->V0_Begin; i < point->V0_End; i++) {
		*(ap->Data + ap->Cout) = *(bp->Data + i);
		ap->Cout ++;
	}
}
