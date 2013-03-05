/************************************************************************
*	System			: POPLAR_H
*	File Name		: OPR_MAIN.C
*	Author			: 木元修
*	Date			: 1997/07/23
*	RealTimeOS		: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description		: オペレーションメイン
*	Original File	: jun\usr1:\src\rice\v53\src\opr_main.c
*	Maintenance		:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h" 
#include "\src\atlanta\define\std.h" 
#include "\src\atlanta\define\mem_pro.h" 
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#endif
/* For SCD */
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"

#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h"
#include "\src\cpu\sh7043_a\scd\ext_v\reductbl.h"

/********************************************************************/
/**  以下はソフトコーデックの関数群です。                          **/
/**  テスト的にここにおいていますが最終的には                      **/
/**          \src\cpu\sh7043_a\scd\                                **/
/**  のファイル（関数）を使用します。                              **/
/**  by O.Kimoto 1998/10/01                                        **/
/********************************************************************/

/*******************************************************
     module		:[１ライン分のＲＬをイメージに変換する]
     fonction	:[]
     return		:[]
     common		:[]
     condition	:[
		struct WorkBuf_t *point,
			  UWORD		Cout;		rl ﾊﾞｯﾌｧｻｲｽﾞｶｳﾝﾄ(rlﾊﾞｯﾌｧ相対位置 0 -- RL_SIZE) work.a_adr - wbuf.data で得られる
					＜毎回クリアされる＞
			  UBYTE		*Data;		使用rlﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ
			  UBYTE		Flag;		rl=0のFlag
					＜毎回クリアされる＞
		struct CdcBlk_t *scdcp,
			UBYTE BufMode;			ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ＜＜ＨＩＮＯＫＩは未使用＞＞
			UBYTE Coding;			coding_method
			UBYTE K_Para;			パラメータ Ｋ
			UBYTE DecBits;	        未書き込み端数ＭＨ、ＭＲデータのビット数（０～７）
			UWORD Line_Cntr;		ｺｰﾃﾞｯｸライン数
			UWORD Img_Size;	    	1ライン画素数サイズ
				＜参照されている＞
			struct Buf_p_t  *Wp;
					UBYTE	*Buf;	バッファ先頭アドレス
					UDWORD	Adr;	バイト位置
					UBYTE	Bit;	ビット位置
			struct Buf_p_t  *Rp;
					UBYTE	*Buf;	バッファ先頭アドレス
					UDWORD	Adr;	バイト位置
					UBYTE	Bit;	ビット位置
			union Byte_WordData_u_t DecData;未書き込み端数ＭＨ、ＭＲデータのビット
				struct{
					UBYTE	H;
					UBYTE	L;
				} Byte;
				UWORD	Word;
		UWORD line
			＜参照されている＞
     ]
     comment		:[]
     machine		:[SH7041]
     language	:[SHC]
     keyword		:[]
     date		:[1997/6/17]
     author		:[鈴木郁二]
********************************************************/
#pragma section SCD /* locate section name "PSCD" */
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

	do 	{
	    rl_a = GetRL(point);							/** run length バッファ から ＲＬを取り出す */

		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
			if (rl_a >= 8){
				do {
					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
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

					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
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
	return;

}


/********************************************************
	module		:[１ライン分のイメージをＲＬに変換する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[
		struct WorkBuf_t *point,
			  UWORD		Cout;		rl ﾊﾞｯﾌｧｻｲｽﾞｶｳﾝﾄ(rlﾊﾞｯﾌｧ相対位置 0 -- RL_SIZE) work.a_adr - wbuf.data で得られる
				＜毎回クリアされる＞
			  UBYTE		*Data;		使用rlﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ
			  UBYTE		Flag;		rl=0のFlag
				＜毎回クリアされる＞
		struct CdcBlk_t *scdcp,
			UBYTE BufMode;			ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ	＜＜ＨＩＮＯＫＩは未使用＞＞
			UBYTE Coding;			coding_method
			UBYTE K_Para;			パラメータ Ｋ
			UBYTE DecBits;	        未書き込み端数ＭＨ、ＭＲデータのビット数（０～７）
			UWORD Line_Cntr;		ｺｰﾃﾞｯｸライン数
			UWORD Img_Size;	    	1ライン画素数サイズ
				＜参照されている＞
			struct Buf_p_t  *Wp;
					UBYTE	*Buf;	バッファ先頭アドレス
					UDWORD	Adr;	バイト位置
					UBYTE	Bit;	ビット位置
			struct Buf_p_t  *Rp;
					UBYTE	*Buf;	バッファ先頭アドレス
					UDWORD	Adr;	バイト位置
					UBYTE	Bit;	ビット位置
			union Byte_WordData_u_t DecData;未書き込み端数ＭＨ、ＭＲデータのビット
				struct{
					UBYTE	H;
					UBYTE	L;
				} Byte;
				UWORD	Word;
		UWORD line
				＜参照されている＞
	]
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

		ImgBufData = *(img_buffer2 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */

		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
		if (ImgBufData == 0x00){
			if (col_flag == WHITE) {
				rl_data += SfitCntr;
			}
			else {
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
	return;
}


/*******************************************************
    module		:[１ライン分のＲＬをイメージに変換する]
    fonction	:[]
    return		:[]
    common		:[]
    condition	:[]
    comment		:[]
    machine		:[SH7041]
    language	:[SHC]
    keyword		:[]
    date		:[1998/9/7]
    author		:[K.Kawata]
********************************************************/
void SAKAKI1LineRL_ToImage(struct WorkBuf_t *point,
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

					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/

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

					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
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
#pragma section  /* locate section name "PSCD" */

/************************************************************************************************************************
	module		:[RUN_LENGTHデータの取り出す]
	function	:[
		1.１バイトＲＬデータｏｒ2バイトＲＬデータを取り出す。
		2.2560以上のRLが取り出された場合、次のRLのカラーが同じなら続けて取り出す。
	return		:[RUN_LENGTH]
	common		:[
	【引数】
		struct WorkBuf_t *gp,
			  UWORD		Cout;		rl ﾊﾞｯﾌｧｻｲｽﾞｶｳﾝﾄ(rlﾊﾞｯﾌｧ相対位置 0 -- RL_SIZE) work.a_adr - wbuf.data で得られる
					＜参照されている＞
					＜カウントアップされている＞
			  UBYTE		*Data;		使用rlﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ
					＜参照されている＞
			  UBYTE		Flag;		rl=0のFlag
	]
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
/************************************************************************************************************************
	module		:[RUN_LENGTHデータの格納する]
	function	:[
		1.１バイトＲＬデータor2バイトＲＬデータを格納する。
		2.2560 以上のRLを格納する場合、2560 + X  2560をｾｯﾄ後、同じカラーで次のバッファに残りXをセットする。
	return		:[]
	common		:[
		SCD_NgRl ：大域変数（内蔵ＲＡＭ）

	【引数】
		struct WorkBuf_t *point,
			  UWORD		Cout;		rl ﾊﾞｯﾌｧｻｲｽﾞｶｳﾝﾄ(rlﾊﾞｯﾌｧ相対位置 0 -- RL_SIZE) work.a_adr - wbuf.data で得られる
					＜参照されている＞
					＜カウントアップされている＞
			  UBYTE		*Data;		使用rlﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ
					＜参照されている＞
			  UBYTE		Flag;		rl=0のFlag
		UWORD rl
			＜参照されている＞
			＜更新されている＞
		UBYTE a_color
			＜参照されている＞
	]
                                                         7(データflag) 6(colorflag)    5 4 3 2 1 0  7 6 5 4 3 2 1 0
	condition	:[1, rl<=63１バイトでＲＬデータを格納仕様: 0(１バイト)  0/1(white/black) * * * * * *
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
void PutRLIntRom(struct WorkBuf_t *point, UWORD rl, UBYTE a_color)

{
	UWORD word_data;
	UBYTE byte_data;

	byte_data = 0;
	word_data = 0;

	if (rl > 4864) {/*	By Y.Suzuki 1997/02/08	*/
		SCD_NgRl = 1;	/* 大域変数（内蔵ＲＡＭ） */
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

/*************************************************************************
	module		:[縮小初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
void SetSkipIntRom(UWORD percent, struct reduction_t *rp)
{
	WORD i;

	rp->linecnt = 0;
	if (percent == A3_TO_A4) {
	/*	rp->cntr_loop = 38;		* 27/38 By Y.Suzuki 1997/09/29 */
		rp->cntr_loop = 32;		/* 27/32 */
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[0][0];
	}
	else if (percent == A3_TO_B4) {
		rp->cntr_loop = 38;		/* 32/38 */
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[1][0];
	}
	else if (percent == B4_TO_A4) {
		rp->cntr_loop = 32;		/* 27/32 */
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[2][0];
	}
	else if (percent == P_A3_TO_A4) {
		rp->cntr_loop = 38;		/* 26/38 */
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[3][0];
	}
	else if (percent == P_B4_TO_A4) {
		rp->cntr_loop = 32;		/* 26/32 */
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[4][0];
	}
	else if (percent >= 50) {
		rp->cntr_loop = 40;		/* 可変縮小 */
		i = ((102 - percent) * 10) / 25;
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[i+5][0];
	}
	else {
		rp->cntr_loop = 40;		/* 可変縮小 */
		i = (((102 - percent) * 10) / 25) - 20;
		i = (102 - percent) * 10;
		rp->r_tbl_p = (UBYTE *)&reduc_tbl[25-i][0];
	}
	return;
}

/*************************************************************************
	module		:[縮小パターンセット]
	function	:[
		1.
	]
	return		:[	Ｂ４－＞Ａ４：１
					Ａ３－＞Ｂ４：２
					Ａ３－＞Ａ４：３
					縮小なし	：０
					原稿幅の縮小なし、モード変更による主走査の縮小あり：４ By Y.Suzuki 1997/01/17
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetReduce(struct MEM_DocParamData_t *src,struct MEM_DocParamData_t *dst)
{
	UBYTE  flag;
	/* Ｈ＿ＦＩＮＥの処理 */

	switch(src->Size){
	case SYS_DOCUMENT_A4_SIZE:
		flag = 0;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
			flag = 3;
		else
			flag = 0;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
			flag = 1;
		else if(dst->Size == SYS_DOCUMENT_B4_SIZE)
			flag = 2;
		else
			flag = 0;
		break;
	default:
		flag = 0;
		break;
	}
	if (!flag && ReductionFromHfine) {/*	原稿幅の縮小なし、モード変更による主走査の縮小あり	*/
		flag = 6;
	}
	else if (!flag && ReductionFromR12) {/*	原稿幅の縮小なし、モード変更による主走査の縮小あり	*/
		flag = 10;
	}
	return(flag);
}


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

/*************************************************************************
	module		:[メモリライト]
	function	:[
		1.書き込みデータの内容を下位より１ビットづつチェックしながら書き込む。
		2.実際の書き込みは、直接書ける。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE MemWriteIntRom(	struct Buf_p_t *write_p,
								UBYTE num,/* 書き込みビット数 */
								UWORD data	/* 書き込みデータ ２バイト*/)
{
	UWORD data_chk;
	UBYTE mem_data;
	/* 書き込みデータのビットをＬＳＢから（１／０の）チェックする */
	data_chk = 0x0001;
	if(write_p->Bit == 1) {/** 前回使用時のゴミデータを消去 */
		*(write_p->Buf + write_p->Adr) = 0;
	}
	mem_data = (UBYTE)(*(write_p->Buf + write_p->Adr));
	do {
		/* 書き込むデータのＬＳＢの１／０をチェック */
		if(data & data_chk) {
			mem_data |= write_p->Bit;
		}
		data_chk <<= 1;

		/* 書き込みビットポインタ更新 */
		if(write_p->Bit == 0x80) {/* バイトポインタも更新 */
			/* バッファへ書き込み */
			*(write_p->Buf + write_p->Adr) = mem_data;
			write_p->Bit = 0x01;
			write_p->Adr++;
/*			if(write_p->Adr >= MEM_BLOCK_SIZE) @ 新ﾏｽｸ変更 */
			if(write_p->Adr >= SCD_MEM_BLOCK_SIZE_I) {
				write_p->Adr = 0;
				if(MEM_WriteGetNextBlockNo(&MemoryExecData) != MEM_OK) {
					return(RX_MEM_OVER);
				}
				write_p->Buf = (UBYTE*)(MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo));
				if (write_p->Buf == 0) {/* ありえないはず、入れておく。By Y.Suzuki 1997/10/01 */
					return(RX_MEM_OVER);
				}
			}
			mem_data = 0;
		}
		else {
			write_p->Bit <<= 1;
		}
	} while(--num > 0);
	if(write_p->Bit != 0x01) {
		/* バッファへ書き込み */
		*(write_p->Buf + write_p->Adr) = mem_data;
	}
	return(OK);
}


void SCDC_ScdDataInitialize(void)
{
	UBYTE i;
	/******************************/
	/* ソフトコーデック用帯域変数 */
	/******************************/
	ReductionFromHfine = 0;
	ScdcErrFlag = 0;
	ScdcPageEndFlag = 0;
	/* ScdcEcmBufCnt = 0; */
	MemReadStatus = 0;
	/* DirectMemTx = 0; */
	LineByteCnt = 0;
	SCD_G3RxResult = 0;
	SCD_G3ReadStatus = 0;
	MESSAGE_t	SoftcodecMessage = {0};
	DEBUG_SCD_MDM_BufferSkip = 0;
	SCD_DirectTx = 0;
	SCD_SkipMrEol = 0;
	SCD_CarryDownBlock = 0;
	SCD_TxMode = 0;
	SCD_EcmSize = 0;
	SCD_MinimumLineSize = 0;
	/* UBYTE *SCD_LastEolAddr = 0; */
	SCD_LastEolDataCount = 0;

	if (i = 0 ; i < 8 ; i ++) {
		SCD_MdmBufCount[i] =0;
	}
	SCD_EOL_WriteCount = 0;
	tskno_SCD_CTxCodeConvertTask = 0xffff;
	SCD_DBG_OldRlSize = 0;
	SCD_NgRl = 0;
	SCD_DBG_RLOVER = 0;
	SCD_DBG_PMODE = 0;
	SCD_DBG_ENC_RLSIZE = 0;
	SCD_CarryDownByteCnt = 0;
	SCD_DirectRx = 0;
	SCD_Det_Rcp = 0;

	if (i = 0 ; i < SCD_MNT_SW_MAX ; i ++ ) {
		SCD_MaintenanceSwitch[i] = 0;
	}
	UBYTE *SCD_EcmBufTopAddress = 0;
	ReductionFromR12 = 0;
	/* SCD_Dummy[14] = {0}; */
}

/*************************************************************************
	module		:[メモリ送信時主走査のソフト縮小]
	function	:[
		メモリ内にｍｍで蓄積される。
		1.	Ａ３ー＞Ｂ４
			Ａ３－＞Ａ４
			Ｂ４－＞Ａ４
			ＨＦＩＮＥ－＞ＮＯＲＭ，ＳＦＩＮＥ，ＦＩＮＥ（％ Ｒ１６－＞Ｒ８）
		2.ｒｌバッファからｒｌを取り出し、縮小率により縮小しｒｌバッファに戻す。
		3.取り出してきたｒｌの総和を縮小後、前の縮小後の値との差から縮小後のｒｌを算出。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
					STIGR-007 の規定により縮小率変更 By Y.Suzuki 1996/12/12
					原稿幅の縮小とＨＦＩＮＥからのモード変更が同時に発生した場合、同時に処理する
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
void RedLineIntRom(struct CdcBlk_t *Sddp,struct WorkBuf_t *rl_buf,UBYTE reduc/* 縮小パターン */)
{
	DWORD	mul_value;
	UWORD	new_rl_size;			/* 縮小前、後のrl_size記憶 */
	UWORD	new_rl_cnt;				/* 縮小後のrl_sizeのカウンタ */
	DWORD	old_rl_cnt;				/* 縮小前のrl_sizeのカウンタ A3->のときwordではﾌﾛｰする */
	UWORD	mul_data,div_data;
	UWORD	rl_data;				/* 縮小後のrl */
	UWORD	write_pointer;			/* rlバッファから書き込み用 */
	UWORD	update_rl;
	UWORD	pre_data;				/* 前にセットした縮小後のＲＬのサイズ */
	UWORD	old_data;				/* 前にリードした縮小前のＲＬのサイズ */

	UBYTE	col,pre_col;	/* ｾｯﾄするrlのｶﾗｰ,一つ前のｶﾗｰ */
	UBYTE	byte_data;

	/* GetRL */
	UWORD	firstbyte;
	UWORD	secondbyte;
	UWORD	rl;
	/* PutRL */
	UWORD	word_data;

	mul_value = 0;
	mul_data = 0;
	div_data = 0;
	new_rl_size = 0;
	old_rl_cnt = 0;
	new_rl_cnt = 0;
	write_pointer = 0;
	update_rl = 0;
	col = 0;
	pre_col = 0;
	byte_data = 0;
	pre_data = 0;
	old_data = 0;

	SCD_DBG_OldRlSize = 0;/*	By Y.Suzuki 1997/02/08	*/

	/** １ラインのイメージサイズを縮小する */
	mul_value =  Sddp->Img_Size;
	switch(reduc) {
	case A3_TO_A4:
		mul_data = 22;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case A3_TO_B4:
		mul_data = 32;
		div_data = 38;
		break;
	case B4_TO_A4:
		mul_data = 26;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case P_A3_TO_A4:
		mul_data = 26;
		div_data = 38;
		break;
	case P_B4_TO_A4:
		mul_data = 26;
		div_data = 32;
		break;
	case HFINE_TO_OTHER:
		mul_data = 20;
		div_data = 40;
		ReductionFromHfine = 0;/* 単なる主走査のみの縮小時 */
		break;
	/* ハイパーファインの原稿でモード変更、縮小が同時の場合 縮小率、未定 */
	case HFA3_TO_A4_OTHER:
		mul_data = 11;
		div_data = 32;
		break;
	case HFA3_TO_B4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	case HFB4_TO_A4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	default:
		new_rl_size = 0;
	}
	if(ReductionFromHfine) {/*	ハイパーファインからのモード変更あり */
		div_data *= 2;
	}
	new_rl_size = (UWORD)((mul_value * mul_data)/div_data);	/* mul_value == Src.Img_Size */
	rl_buf->Cout = 0;										/* RL Buffer Read Byte Pointer 初期化 */
	/*-------------------------------------------------*/
	/**ライン先頭のＲＬを縮小後､ＲＬバッファに格納する */
	/*-------------------------------------------------*/
	/* old_data = GetRLR(rl_buf,read_pointer);*/
	firstbyte = *(rl_buf->Data + rl_buf->Cout);
	col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
	if ((firstbyte & 0x0080) != 0x0080) {
		rl_buf->Cout ++;
		rl = firstbyte & 0x003F;
	}
	else {
		rl_buf->Cout ++;
		secondbyte = *(rl_buf->Data + rl_buf->Cout);
		rl = ((firstbyte & 0x003F) << 8) + secondbyte;
		rl_buf->Cout ++;
	}

	old_data = rl;

	old_rl_cnt += (DWORD)old_data;
	update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
	rl_data = update_rl - new_rl_cnt;
	new_rl_cnt = update_rl;
	pre_data = rl_data;
/*	PutRLR(rl_buf,write_pointer,rl_data,0);* 縮小後のrlをRLバッファに再セット */
	col = 0;
	byte_data = 0;
	word_data = 0;

	if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
		SCD_NgRl = 1;
	}
	if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
		SCD_NgRl = 2;
	}
	if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
		return;
	}
	if (rl_data <= 0x003F) {
		if (col == WHITE) {
			byte_data = (UBYTE)rl_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
		else {
			word_data = rl_data | 0x0040;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
	}
	else {
		if (col == WHITE) {
			rl_data |= 0x8000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
		else {
			rl_data |= 0xC000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
	}


	rl_data = 0;
	while(new_rl_size > new_rl_cnt) {						/** ＤＳＴのサイズになるまでＲＬを縮小する */
		/*-------------------------------------------------------*/
		/**一ライン分のＲＬを縮小しながら､ＲＬバッファに格納する */
		/*-------------------------------------------------------*/
		/* RLバッファからRL取り出し	*/
	/*	old_data = GetRLR(rl_buf,read_pointer);*/
		firstbyte = *(rl_buf->Data + rl_buf->Cout);
		col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
		if ((firstbyte & 0x0080) != 0x0080) {
			rl_buf->Cout ++;
			rl = firstbyte & 0x003F;
		}
		else {
			rl_buf->Cout ++;
			secondbyte = *(rl_buf->Data + rl_buf->Cout);
			rl = ((firstbyte & 0x003F) << 8) + secondbyte;
			rl_buf->Cout ++;
		}

		old_data = rl;
		old_rl_cnt += (DWORD)old_data;
		if ((UWORD)old_rl_cnt > Sddp->Img_Size) {
			SCD_DBG_OldRlSize = 1;/*	By Y.Suzuki 1997/02/08	*/
		}
		update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
		if(update_rl != new_rl_cnt) {/* 縮小後のrl発生 */
			rl_data = update_rl - new_rl_cnt;
			/* 縮小前のrlｶﾗｰ情報の取得 */
			if(old_data < 64) {/* rlが６３以下 */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 1));
			}
			else {/* if(old_data <= MH_MAKEUP_MAX) @* rlが２５６０以下 */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 2));
			}
			new_rl_cnt = update_rl;/* 縮小後ＲＬ更新 */
			col = (UBYTE)(byte_data & 0x40);
			/* 前にセットしたｒｌと同じ色か */
			if(pre_data < 64) {
				byte_data = *(rl_buf->Data + (write_pointer - 1));
			}
			else { /*if(pre_data <= MH_MAKEUP_MAX) */
				byte_data = *(rl_buf->Data + (write_pointer - 2));
			}
			pre_col = (UBYTE)(byte_data & 0x0040);
			if(col == pre_col) {/* 前にセットしたｒｌと同じ色 */
				rl_data += pre_data;
				if(pre_data < 64) {
					write_pointer--;
				}
				else {
					write_pointer -= 2;
				}
			}
			pre_data = rl_data;
		/*	PutRLR(rl_buf,write_pointer,rl_data,col);@* 縮小後のrlをRLバッファに再セット */
			byte_data = 0;
			word_data = 0;

			if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
				SCD_NgRl = 1;
			}
			if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
				SCD_NgRl = 2;
			}
			if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
				return;
			}
			if (rl_data <= 0x003F) {
				if (col == WHITE) {
					byte_data = (UBYTE)rl_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
				else {
					word_data = rl_data | 0x0040;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
			}
			else {
				if (col == WHITE) {
					rl_data |= 0x8000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
				else {
					rl_data |= 0xC000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
			}


			rl_data = 0;
			col = 0;
			pre_col = 0;
		}
	}
	if (new_rl_cnt > new_rl_size) {
		SCD_DBG_RLOVER = 4;
	}
	/*	主走査に満たないＲＬをセットする By Y.Suzuki 1997/09/26	*/
	if ((reduc == A3_TO_A4) || (reduc == B4_TO_A4)) {
		col = 0;
		if(SCD_TxMode == SYS_HFINE) {/** ハイパーファインなら主走査ドット数２倍 */
			rl_data = SYS_A4_LINE * 2 - new_rl_size;
		}
		else {
			rl_data = SYS_A4_LINE - new_rl_size;
		}
		if(pre_data < 64) {
			byte_data = *(rl_buf->Data + (write_pointer - 1));
		}
		else { /*if(pre_data <= MH_MAKEUP_MAX) */
			byte_data = *(rl_buf->Data + (write_pointer - 2));
		}
		pre_col = (UBYTE)(byte_data & 0x0040);
		if(col == pre_col) {/* 前にセットしたｒｌと同じ色 */
			rl_data += pre_data;
			if(pre_data < 64) {
				write_pointer--;
			}
			else {
				write_pointer -= 2;
			}
		}
		byte_data = 0;
		word_data = 0;

		if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
			SCD_NgRl = 1;
		}
		if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
			SCD_NgRl = 2;
		}
		if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
			return;
		}
		if (rl_data <= 0x003F) {
			if (col == WHITE) {
				byte_data = (UBYTE)rl_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
			else {
				word_data = rl_data | 0x0040;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
		}
		else {
			if (col == WHITE) {
				rl_data |= 0x8000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
			else {
				rl_data |= 0xC000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
		}
	}
}


