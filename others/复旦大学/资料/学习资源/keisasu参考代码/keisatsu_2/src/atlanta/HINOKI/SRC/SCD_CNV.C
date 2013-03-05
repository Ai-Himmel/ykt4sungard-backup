#include "\src\atlanta\define\product.h"

#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"

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
			UBYTE BufMode;			ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ
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
			UBYTE BufMode;			ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ
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

