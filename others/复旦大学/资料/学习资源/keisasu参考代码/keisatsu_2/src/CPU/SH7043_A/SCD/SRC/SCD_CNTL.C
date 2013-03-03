/************************************************************************
*	System		: POPLAR
*	File Name	: SCD_CNTL.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\lst_def.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mntsw_f.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
 #endif
#endif


#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#else
/* #include "\src\atlanta\mdm\orange\ext_v\mdm_data.h" */
/* #include "\src\atlanta\ext_v\bkupram.h" */
#endif

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\ext_v\reductbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
/* 新ﾏｽｸ変更 追加 */
#include "\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\mon_tbl.h"
#else
#include "\src\atlanta\scd\ext_v\reductbl.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
/* 新ﾏｽｸ変更 追加 */
#include "\src\atlanta\scd\ext_v\scd_tbl.h"
#include "\src\atlanta\sh7043\ext_v\mon_tbl.h"
#endif


#if(0)		/*	By Y.Suzuki 1997/03/07	*/
** /*************************************************************************
** 	module		:[ソフトエンコードで使用するローカル変数の初期化]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[SH7034/SH704X]
** 	language	:[SHC]
** 	keyword		:[MDM]
** 	date		:[1995/12/04]
** 	author		:[鈴木郁二]
** *************************************************************************/
//void SoftEncodeInitial(struct CdcBlk_t *scdcp)
//{
//	scdcp->Coding = SYS_DocBlock.Dst.Code;
//	switch(SYS_DocBlock.Dst.Size) {
//	case SYS_DOCUMENT_A4_SIZE:
//		scdcp->Img_Size = SYS_A4_LINE;
//		break;
//	case SYS_DOCUMENT_B4_SIZE:
//		scdcp->Img_Size = SYS_B4_LINE;
//		break;
//	case SYS_DOCUMENT_A3_SIZE:
//		scdcp->Img_Size = SYS_A3_LINE;
//		break;
//	}
//	switch(SYS_DocBlock.Dst.Mode) {
//	case SYS_NORMAL:
//		scdcp->K_Para = 2;
//		break;
//	case SYS_FINE:		/**	ファイン	*/
//	case SYS_GRAY16:	/**	中間調16	*/
//	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
//	case SYS_GRAY32:	/**	中間調32	*/
//	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
//	case SYS_GRAY64:	/**	中間調64	*/
//	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
//		scdcp->K_Para = 4;
//		break;
//	case SYS_SFINE:		/**	Sファイン	*/
//		scdcp->K_Para = 8;
//		break;
//	case SYS_HFINE:		/**	Hファイン	*/
//		scdcp->K_Para = 8;
//		scdcp->Img_Size *= 2;/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/01/10 */
//		break;
//	}
//	scdcp->Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */
//
//	/* 符号ライトポインタのセット */
//	if(scdcp->BufMode == MDM) {
//		scdcp->Wp = &MdmWp;
//		scdcp->Wp->Buf = &MDM_ModemBuffer[0][0];
//		scdcp->Wp->Adr = 0;
//		scdcp->Wp->Bit = 1;
//		LineByteCnt = 0;
//	}
//	else if(scdcp->BufMode == ECM_MODE) {
//		scdcp->Wp = &EcmWp;
//		scdcp->Wp->Buf = &EcmBuffer[0][0];
//		scdcp->Wp->Adr = 0;
//		scdcp->Wp->Bit = 1;
//	}
//	else if(scdcp->BufMode == MEM1) {
//		/* 蓄積符号化方式をＭＭＲ/ＭＲ */
//		scdcp->Coding = RxMemoryStoreData.Code;
//		scdcp->Wp = &MemWp;
//		/* メモリ書き込み先頭アドレスをセットすべき */
//		scdcp->Wp->Buf = MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo);/** 送信原稿のＤＲＡＭ内先頭アドレス */
//		scdcp->Wp->Adr = 0;
//		scdcp->Wp->Bit = 1;
//	}
//}


** /*************************************************************************
** 	module		:[ソフトデコードで使用するローカル変数の初期化]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[SH7034/SH704X]
** 	language	:[SHC]
** 	keyword		:[MDM]
** 	date		:[1995/12/04]
** 	author		:[鈴木郁二]
** *************************************************************************/
//void SoftDecodeInitial(struct CdcBlk_t *scdcp)
//{
//	/**	メモリ送信の場合、蓄積符号化方式 受信の場合、受信符号化方式をセット */
//	scdcp->Coding = SYS_DocBlock.Src.Code;
//	if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_A4_SIZE) {
//		scdcp->Img_Size = SYS_A4_LINE;
//	}
//	else if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_B4_SIZE) {
//		scdcp->Img_Size = SYS_B4_LINE;
//	}
//	else if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_A3_SIZE) {
//		scdcp->Img_Size = SYS_A3_LINE;
//	}
//	if (SYS_DocBlock.Src.Mode == SYS_HFINE) {/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/02/07 */
//		scdcp->Img_Size *= 2;
//	}
//	scdcp->Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */
//	/* 初期化 追加 王 96/1/23 */
//	scdcp->DecData.Byte.H = 0;
//	scdcp->DecData.Byte.L = 0;
//	scdcp->DecBits = 0;
//
//	/* 符号リードポインタのセット */
//	if(scdcp->BufMode == MDM) {
//		/* Ｇ３受信時 MDM_ModemBuffer[0] をスキップする */
//		DEBUG_SCD_MDM_BufferSkip = 0;	/*	By Y.Suzuki 1997/01/09	*/
//
//		scdcp->Rp = &MdmRp;
//		scdcp->Rp->Buf = &MDM_ModemBuffer[ModemControl.ReadPoint][0];
//		scdcp->Rp->Adr = 0;
//		scdcp->Rp->Bit = 1;
//	}
//	else if(scdcp->BufMode == ECM_MODE) {
//		scdcp->Rp = &EcmRp;
//		scdcp->Rp->Buf = &EcmBuffer[0][0];
//		scdcp->Rp->Adr = 0;
//		scdcp->Rp->Bit = 1;
//	}
//	else if(scdcp->BufMode == MEM1) {
//		scdcp->Rp = &MemRp;
//		/* メモリ読み出し先頭アドレスをセットすべき */
//		scdcp->Rp->Buf = MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo);/** 送信原稿のＤＲＡＭ内先頭アドレス */
//		scdcp->Rp->Adr = 0;
//		scdcp->Rp->Bit = 1;
//	}
//}
#endif		/*	By Y.Suzuki 1997/03/07	*/


/*************************************************************************
	module		:[ＲＬバッファ初期化]
	function	:[
		1.エンコード、デコードで使用する参照ラインにＲＬＢＵＦのアドレスをセット
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/11/17]
	author		:[鈴木郁二]
*************************************************************************/
void RlBufInitIntRom(UWORD img_size) {
	struct WorkBuf_t *rl_buf_p;
	SCD_NgRl = 0;		/*	By Y.Suzuki 1997/03/17	*/
	RL1.Cout = 0;
	RL1.Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*	RL1.Data = &RL_Buffer[RLBUF_ENC]; 新ﾏｽｸ変更 T.Nose 1998/08/27 */
	RL1.Data = RL_Buffer_p + RLBUF_ENC;
	rl_buf_p = &RL1;
	/* 全白イメージサイズをセットする */
	PutRL(rl_buf_p,img_size,0);
	RL2.Cout = 0;
	RL2.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*	RL2.Data = &RL_Buffer[RLBUF_ENC + RLBUF_SIZE]; 新ﾏｽｸ変更 T.Nose */
	RL2.Data = RL_Buffer_p + RLBUF_ENC + RLBUF_SIZE;
	rl_buf_p = &RL2;
	/* 全白イメージサイズをセットする */
	PutRL(rl_buf_p,img_size,0);
	RL3.Cout = 0;
	RL3.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
/*	RL3.Data = &RL_Buffer[RLBUF_DEC]; 新ﾏｽｸ変更 T.Nose */
	RL3.Data = RL_Buffer_p + RLBUF_DEC;
	rl_buf_p = &RL3;
	/* 全白イメージサイズをセットする */
	PutRL(rl_buf_p,img_size,0);
}


/*************************************************************************
	module		:[1ライン分のイメージをＲＬに変換する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[フォントのイメージの主走査方向を2倍する、400DPIはさらに２倍
					300dpi の処理追加各ＲＬサイズを３倍する。By Y.Suzuki 1997/09/30
	]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/11/29]
	author		:[鈴木郁二]
*************************************************************************/
void Img2RlIntRom(UBYTE *img_pntr,		/* Image Buf Pointer */
				 struct WorkBuf_t *rl_pntr,			/* RL Buf Pointer */
				 UBYTE size)				/* A4_SIZE or B4_SIZE or A3_SIZE */
{
	UWORD	j, rl, img_size ,rl_img_cnt,save_white_rl;
	UBYTE	mask_bit, col_flg,hfine_flag,img_buf_offset;
	UBYTE	efine_flag;

	/* ハイパーファインの場合は、ＲＬを４倍にする */
	hfine_flag = 0;
	efine_flag = 0;
	save_white_rl = 0;
	if (size == SYS_DOCUMENT_A4_SIZE) {
	/*	rl = (LST_LEFT_WHITE_A4 * 8);*/
		rl = (14 * 8);/* LST_LEFT_WHITE_A4 テーブルがなくなったため とりあえず直値を入れときます。*/
		img_size = SYS_A4_LINE;
	}
	else if (size == SYS_DOCUMENT_B4_SIZE) {
	/*	rl = (LST_LEFT_WHITE_B4 * 8);*/
		rl = (24 * 8);/* LST_LEFT_WHITE_A4 テーブルがなくなったため とりあえず直値を入れときます。*/
		img_size = SYS_B4_LINE;
	}
	else if (size == SYS_DOCUMENT_A3_SIZE) {
	/*	rl = (LST_LEFT_WHITE_A3 * 8);*/
		rl = (34 * 8);/* LST_LEFT_WHITE_A4 テーブルがなくなったため とりあえず直値を入れときます。*/
		img_size = SYS_A3_LINE;
	}
	if(SCD_TxMode == SYS_HFINE) {/** ハイパーファインなら主走査ドット数２倍 */
		img_size *= 2;
		hfine_flag = 1;
	}
	else if ((SCD_TxMode == SYS_E_HFINE) || (SCD_TxMode == SYS_EFINE)) {
		img_size = (img_size * 2)-(img_size / 2);
		efine_flag = 1;
	}

	rl_pntr->Cout = 0;	/** WorkBuf.Cont 初期化 */
	col_flg = WHITE;
	/** rl_img_cnt >= img_sige となるまでイメージをRLに変換する */
	for (rl_img_cnt = 0,img_buf_offset = 0; img_buf_offset < 80; img_pntr++,img_buf_offset++) {
		if (*img_pntr == 0) {			/* 1byte全白の場合 */
			if (col_flg == WHITE) {
				rl += 8;
			}
			else {
				if(hfine_flag) {
					rl *= 2;
				}
				/*	RL をバッファにセットするまえに2倍にする	*/
				rl *= 2;
				if (efine_flag) {
					rl += rl/2;
				}
				PutRL(rl_pntr, rl,1);
				rl_img_cnt += rl;
				rl = 8;
				col_flg = WHITE;
				save_white_rl = 0;
			}
		}
		else if (*img_pntr == 0xff) {		/* 1byte全黒の場合 */
			if (col_flg == BLACK) {
				rl += 8;
			}
			else {
				if(hfine_flag) {
					rl *= 2;
				}
				/*	RL をバッファにセットするまえに2倍にする	*/
				rl *= 2;
				if (efine_flag) {
					rl += rl/2;
				}
				PutRL(rl_pntr, rl,0);
				rl_img_cnt += rl;
				save_white_rl = rl;
				rl = 8;
				col_flg = BLACK;
			}
		}
		else {
			mask_bit = 0x80;					/* MSB Firstの場合 */
			for (j=0; j<8; j++) {
				if (*img_pntr & mask_bit) {
					if (col_flg == BLACK) {
						rl++;
					}
					else {
						if(hfine_flag) {
							rl *= 2;
						}
						/*	RL をバッファにセットするまえに2倍にする	*/
						rl *= 2;
						if (efine_flag) {
							rl += rl/2;
						}
						PutRL(rl_pntr, rl,0);
						rl_img_cnt += rl;
						save_white_rl = rl;
						rl = 1;
						col_flg = BLACK;
					}
				}
				else {
					if (col_flg == WHITE) {
						rl++;
					}
					else {
						if(hfine_flag) {
							rl *= 2;
						}
						/*	RL をバッファにセットするまえに2倍にする	*/
						rl *= 2;
						if (efine_flag) {
							rl += rl/2;
						}
						PutRL(rl_pntr, rl,1);
						rl_img_cnt += rl;
						rl = 1;
						col_flg = WHITE;
						save_white_rl = 0;
					}
				}
				mask_bit >>= 1;
			}
		}
	}
	/* ＴＴＩデータの最後のカラーが白の場合、原稿右端の余白にたし込む */
	if(col_flg == BLACK) {
		if(hfine_flag) {
			rl *= 2;
		}
		/*	RL をバッファにセットするまえに2倍にする	*/
		rl *= 2;
		if (efine_flag) {
			rl += rl/2;
		}
		PutRL(rl_pntr, rl,1);
		rl_img_cnt += rl;
	}
	rl = img_size - rl_img_cnt;/* 右端の余白部分のＲＬをセット */
	PutRL(rl_pntr, rl,0);
	rl_img_cnt += rl;
}


/*************************************************************************
	module		:[モデムライト]
	function	:[
		1.１ラインの符号書き込み中にモデムバッファの変わり目がきたら、直前の
		   ＥＯＬからの符号を次のモデムバッファの先頭にコピーする。
		   ８本のモデムバッファの変わり目が常にラインの最後になるようにモデムバッファ
		   に符号をセットする。
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
void MdmWrite(	struct Buf_p_t *write_p,
					UBYTE num,/* 書き込みビット数 */
					UWORD data	/* 書き込みデータ ２バイト*/)
{
	UWORD data_chk;
	UBYTE mdm_data;
	/* 書き込みデータのビットをＬＳＢから（１／０の）チェックする */
	data_chk = 0x0001;
	if(write_p->Bit == 1) {/** 前回使用時のゴミデータを消去 */
		*(write_p->Buf + write_p->Adr) = 0;
	}
	mdm_data = (UBYTE)(*(write_p->Buf + write_p->Adr));
	do {
		/* 書き込むデータのＬＳＢの１／０をチェック */
		if(data & data_chk) {
			mdm_data |= write_p->Bit;
		}
		data_chk <<= 1;

		/* 書き込みビットポインタ更新 */
		if(write_p->Bit == 0x80) {/* バイトポインタも更新 */
			/* バッファへ書き込み */
			*(write_p->Buf + write_p->Adr) = mdm_data;
			write_p->Bit = 0x01;
			write_p->Adr++;
			LineByteCnt++;/* フィルセット用 */

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 			EncodeDataCount++;
#else
			(*EncodeDataCount_p)++;
#endif

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 			if(write_p->Adr >= (MODEM_BUFFER_LENGTH - 6)) {
#else
			if(write_p->Adr >= (UDWORD)(MODEM_BUF_LENGTH_P - 6)) {
#endif


				/* ここにきた時、ラインの途中なら、最後のラインを次のモデムバッファへコピー */

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				SCD_MdmBufCount[ModemControl.WritePoint] = (UWORD)EncodeDataCount;
#else
				SCD_MdmBufCount[ModemControl_p->WritePoint] = (UWORD)*EncodeDataCount_p;
#endif

			/*	(UWORD)(EncodeDataCount - SCD_LastEolDataCount);*/

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				TxStartFlag = 1;
#else
				*TxStartFlag_p = 1;
#endif

				wai_oneshot(1);		/*	Test By Y.Suzuki 1997/04/21	*/
				write_p->Adr = 0;
				/*------------------------------------------*/
				/*	フレーム書き込みモデムバッファ獲得処理	*/
				/*------------------------------------------*/
#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				while (ModemControl.UsedCount == MODEM_BUFFER_MAX) [	/**	モデムバッファ使用本数が８本の時	*/
#else
				while (ModemControl_p->UsedCount == MODEM_BUF_MAX_P) {	/**	モデムバッファ使用本数が８本の時	*/
#endif

					wai_oneshot(1);		/*	Test By Y.Suzuki 1997/04/21	*/
				/*	wai_tsk(10/10);	@**	タスクウェイト１０ｍｓ	*/
				}
				NextModemBufferWritePointSet();

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				write_p->Buf = &MDM_ModemBuffer[ModemControl.WritePoint][0];
#else
				write_p->Buf = (MDM_ModemBuffer_p + (ModemControl_p->WritePoint * MODEM_BUF_LENGTH_P));
#endif

#if(0)
//				SCD_MemoryMove(write_p->Buf,SCD_LastEolAddr,(UWORD)(EncodeDataCount - SCD_LastEolDataCount));
//				write_p->Adr = EncodeDataCount - SCD_LastEolDataCount;
#endif

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				EncodeDataCount = 0;
#else
				*EncodeDataCount_p = 0;
#endif

#if (0)
** 				/*---------下記３行を上記４行に変更 96/1/8 Y.S
** 				if(write_p->Buf == (MDM_ModemBuffer + (MODEM_BUFFER_LENGTH + 6) * 8)) {
** 					write_p->Buf = &MDM_ModemBuffer[0][0];
** 				}
** 				----------*/
#endif

			}
			mdm_data = 0;
		}
		else {
			write_p->Bit <<= 1;
		}
	}while(--num > 0);
	if(write_p->Bit != 0x01) {
		/* バッファへ書き込み */
		*(write_p->Buf + write_p->Adr) = mdm_data;
	}
}

/*************************************************************************
	module		:[プログラム転送ルーチン]
	function	:[
		1.転送元のアドレスと転送先のアドレス及び転送バイト数を入力
		2.転送バイト数分、各アドレスをインクリメントしながら、コピーする
		3.Ｇ３送信時、ラインの途中でモデムバッファの変わり目がきたとき
			直前のeolから書き込み中のモデムバッファの最後までを次のモデムバッファの
			先頭にコピーする。ために使用する。
	]
	return		:[なし]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[SHC(Ver.6.0)]
	keyword		:[SCD]
	date		:[1994/01/13]
	author		:[鈴木郁二]
*************************************************************************/
void SCD_MemoryMove(register UBYTE	*src_adr,register UBYTE	*tgt_adr,UWORD	cnt)
{
	while (cnt--) {
		*src_adr++ = *tgt_adr++;
	}
}


/*************************************************************************
	module		:[モデムリード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
WORD MdmRead(	struct Buf_p_t *read_p,
					UBYTE num	/* 読み出しビット数最大１６ビット */)
{
	WORD put_bit,rtn_data;
	UBYTE byte_data;
/*	UBYTE	debugsw;*/
/*	UBYTE	*ebf_base_rp;	@*	ＥＣＭバッファ先頭読み出しポインタ	*/

/*	debugsw = 0;	@*debug for ANZU_L R.3.3 1997/12/12 Y.M */

	rtn_data = 0;
	put_bit = 1;
	byte_data = *(read_p->Buf + read_p->Adr);
	SCD_G3ReadStatus = RCV_BLOCK;	/**	受信データリード	*/
	do {
		/* 読み出しデータ１ビットセット */
		if(read_p->Bit & byte_data) {
			rtn_data |= put_bit;
		}

		put_bit <<= 1;
		if(read_p->Bit == 0x80) {
			read_p->Bit = 0x01;
			read_p->Adr++;
			if (SCD_CarryDownByteCnt < (SCD_CarryDownBlock * 256)) {
				SCD_CarryDownByteCnt++;
			}
			else {
				SCD_CarryDownByteCnt = 0xFFFF;
			}

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 			if(read_p->Adr >= (MODEM_BUFFER_LENGTH - 6)) {	/*	MODEM_BUFFER_LENGTH : 262	*/
#else
			if(read_p->Adr >= (UDWORD)((MODEM_BUF_LENGTH_P - 6))) {	/*	MODEM_BUFFER_LENGTH : 262	*/
#endif

				/* Ｇ３受信時 MDM_ModemBuffer[0] をスキップする */
				DEBUG_SCD_MDM_BufferSkip = 1;	/*	By Y.Suzuki 1997/01/09	*/

				/* タスク切り替え */
				if (SCD_MaintenanceSwitch[SCD_MNT_SW_F3]) {/*	Test By Y.Suzuki 1997/07/07	*/
					wai_oneshot(SCD_MaintenanceSwitch[SCD_MNT_SW_F3]);
				}
				else {
					wai_oneshot(1);
				}

				read_p->Adr = 0;

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				read_p->Buf += (MODEM_BUFFER_LENGTH);
#else
				read_p->Buf += (MODEM_BUF_LENGTH_P);
#endif

				NextModemBufferReadPointSet();

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				if(ModemControl.ReadPoint == 0) {
** 					read_p->Buf = &MDM_ModemBuffer[0][0];
** 				}
#else
				if(ModemControl_p->ReadPoint == 0) {
					read_p->Buf = MDM_ModemBuffer_p;
				}
#endif

				/**	モデムバッファにデータが溜まるのを待つ	*/
				SCD_G3ReadStatus = RxG3_Read();	/**	受信データリード	*/
				if (SCD_G3ReadStatus != RCV_BLOCK) {	/**	キャリア断、停止キー	*/
					return(rtn_data);
				}
				/**	受信データ有り	*/
				/* モデム読み出し権獲得 */
				/* 次の２５６バイトの先頭をリード */
				byte_data = *(read_p->Buf + read_p->Adr);

#if(0)/* y.suzuki 980214 cpu 作成のため */
//		/* for debug */
//				if (debugsw) {	/*	このデバッグルーチンは残しておいたほうが、後々便利です	1997/12/16 */
//					if (MDM_DebugRxCount < 0x20000) {
//					/*	ebf_base_rp = &EcmBuffer[0][0];BY YSUZUKI 980214 */
//						ebf_base_rp = SCD_EcmBufTopAddress;
//						MemoryMove((UBYTE *)(ebf_base_rp+MDM_DebugRxCount),
//					  (UBYTE *)&MDM_ModemBuffer[ModemControl.ReadPoint][0], MODEM_DMA_SIZE);	/**	ＥＣＭバッファからモデムバッファにプログラム転送	*/
//						MDM_DebugRxCount += MODEM_DMA_SIZE;
//					}
//				}
//		/* for debug end */
#endif

			}
			else {
				byte_data = *(read_p->Buf + read_p->Adr);
			}
		}
		else {
			read_p->Bit <<= 1;
		}
	} while(--num > 0);
	return(rtn_data);
}

/*************************************************************************
	module		:[メモリライト]
	function	:[
		1.書き込みデータの内容を下位より１ビットづつチェックしながら書き込む。
		2.実際の書き込みは、直接書ける。
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
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

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				if(MEM_WriteGetNextBlockNo(&MemoryExecData) != MEM_OK) {
** 					return(RX_MEM_OVER);
** 				}
** 				write_p->Buf = (UBYTE*)(MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo));
** 				if (write_p->Buf == 0) {/* ありえないはず、入れておく。By Y.Suzuki 1997/10/01 */
** 					return(RX_MEM_OVER);
** 				}
#else
				if(MEM_WriteGetNextBlockNo(MemoryExecData_p) != MEM_OK) {
					return(RX_MEM_OVER);
				}
				write_p->Buf = (UBYTE*)(MEM_CalculateSoftAddress(MemoryExecData_p->ExecBlockNo));
				if (write_p->Buf == 0) {/* ありえないはず、入れておく。By Y.Suzuki 1997/10/01 */
					return(RX_MEM_OVER);
				}
#endif



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


/*************************************************************************
	module		:[メモリリード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
WORD MemReadIntRom(	struct Buf_p_t *read_p,
					UBYTE num	/* 読み出しビット数最大１６ビット */)
{
	WORD put_bit,rtn_data;
	UBYTE byte_data;
	MemReadStatus = OK;
	rtn_data = 0;
	put_bit = 1;
	byte_data = (UBYTE)(*(read_p->Buf + read_p->Adr));
	do {
		if(read_p->Bit & byte_data) {
			rtn_data |= put_bit;
		}
		put_bit <<= 1;
		if(read_p->Bit == 0x80) {
			read_p->Bit = 0x01;
			read_p->Adr++;
/*			if(read_p->Adr >= MEM_BLOCK_SIZE) @ 新ﾏｽｸ変更 */
			if(read_p->Adr >= SCD_MEM_BLOCK_SIZE_I) {
				read_p->Adr = 0;

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				MemoryExecData.ExecBlockNo = MEM_ReadGetNextBlockNo(MemoryExecData.ExecBlockNo);
** 				if((MemoryExecData.ExecBlockNo == MEM_EOP_BLOCK)
** 				|| (MemoryExecData.ExecBlockNo == MEM_EOB_BLOCK) || (MemoryExecData.ExecBlockNo == MEM_BLOCK_OVER)) {
** 					/* 指定ブロックNoがEOPか */
** 					/* 指定ブロックNoがEOBか */
** 					/* 指定ブロックNoがMEM_BLOCK_OVERなら */
** 					MemReadStatus = NG;
** 					return(TX_MEM_ERR);
** 				}
** 				read_p->Buf = (UBYTE *)(MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo));
#else
				MemoryExecData_p->ExecBlockNo = MEM_ReadGetNextBlockNo(MemoryExecData_p->ExecBlockNo);
				if((MemoryExecData_p->ExecBlockNo == MEM_EOP_BLOCK)
				|| (MemoryExecData_p->ExecBlockNo == MEM_EOB_BLOCK) || (MemoryExecData_p->ExecBlockNo == MEM_BLOCK_OVER)) {
					/* 指定ブロックNoがEOPか */
					/* 指定ブロックNoがEOBか */
					/* 指定ブロックNoがMEM_BLOCK_OVERなら */
					MemReadStatus = NG;
					return(TX_MEM_ERR);
				}
				read_p->Buf = (UBYTE *)(MEM_CalculateSoftAddress(MemoryExecData_p->ExecBlockNo));
#endif

				/* 次のブロックの先頭をリード */
				byte_data = (UBYTE)(*(read_p->Buf + read_p->Adr));
			}
			else {
				byte_data = (UBYTE)(*(read_p->Buf + read_p->Adr));
			}
		}
		else {
			read_p->Bit <<= 1;
		}
	}while(--num > 0);
	return(rtn_data);
}

/*************************************************************************
	module		:[ＥＣＭバッファライト]
	function	:[
		1.書き込みデータの内容を下位より１ビットづつチェックしながら書き込む。
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
void EcmWriteIntRom(struct Buf_p_t *write_p,
					UBYTE num,/* 書き込みビット数 */
					UWORD data	/* 書き込みデータ ２バイト*/)
{
	MESSAGE_t	*SCD_Msg;
	UWORD data_chk;
	UBYTE ecm_data;

	struct mbxno_data_t *mbxno_ptr;
	mbxno_ptr = mbxno_p;

	/* 書き込みデータのビットをＬＳＢから（１／０の）チェックする */
	data_chk = 0x0001;
	if(write_p->Bit == 1) {/** 前回使用時のゴミデータを消去 */
		*(write_p->Buf + write_p->Adr) = 0;
	}
	ecm_data = *(write_p->Buf + write_p->Adr);
	do {
		if(data & data_chk) {
			ecm_data |= write_p->Bit;
		}
		data_chk <<= 1;

		/* 書き込みビットポインタ更新 */
		if(write_p->Bit == 0x80) {/* バイトポインタも更新 */
			/* バッファへ書き込み */
			*(write_p->Buf + write_p->Adr) = ecm_data;
			write_p->Bit = 0x01;
			write_p->Adr++;
			LineByteCnt++;/* フィルセット用 By Y.Suzuki 1997/04/03 */

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 			EncodeDataCount++;
#else
			(*EncodeDataCount_p)++;
#endif

			if(write_p->Adr >= 256) {/* 送信時 256 */

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				TxStartFlag = 1;
#else
				*TxStartFlag_p = 1;
#endif

#if (0)
//				if (SCD_MaintenanceSwitch[SCD_MNT_SW_F2]) {
//					wai_oneshot(SCD_MaintenanceSwitch[SCD_MNT_SW_F2]);
//				}
//				else {
//					wai_oneshot(1);		/*	Test By Y.Suzuki 1996/08/22	*/
//				}
#endif
				write_p->Adr = 0;
				write_p->Buf += ECM_BUFFER_LENGTH;
#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 				if(EncodeDataCount >= (UDWORD)ECM_BUFFER_DATA_MAX) [
#else
				if(*EncodeDataCount_p >= (UDWORD)ECM_BUFFER_DATA_MAX) {
#endif

					/* write_p->Buf = &EcmBuffer[0][0];Ｌ系とＢ，Ｈでアドレスが異なるため By Y.Suzuki 1997/10/16*/
					write_p->Buf = SCD_EcmBufTopAddress;
					/* ブロックエンドの処理 */

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 					CodecPageStatus = CDC_BLOCK_END;
#else
					*CodecPageStatus_p = CDC_BLOCK_END;
#endif

					do {	/**	エンコード再起動メッセージ待ち	*/
						rcv_msg(mbxno_ptr->SCDC_MTxCodeConvertTask, &SCD_Msg);
					} while (!(SCD_Msg->Message == MSG_SCDC_START));
					/*wai_tsk(0xffff);*/
#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 					CodecPageStatus = CDC_CONTINUE;	/**	コーデックステータスをコンティニューにセット	*/
** 					TxStartFlag = 0;
** 					EncodeDataCount = 0;
#else
					*CodecPageStatus_p = CDC_CONTINUE;	/**	コーデックステータスをコンティニューにセット	*/
					*TxStartFlag_p = 0;
					*EncodeDataCount_p = 0;
#endif

				}
				/* マルチコピー中のECM送信ループの対策 By Y.Suzuki 1998/01/26 */
				if (SCD_MaintenanceSwitch[SCD_MNT_SW_F2]) {
					wai_oneshot(SCD_MaintenanceSwitch[SCD_MNT_SW_F2]);
				}
				else {
					wai_oneshot(1);		/*	Test By Y.Suzuki 1996/08/22	*/
				}
			}
			ecm_data = 0;
		}
		else {
			write_p->Bit <<= 1;
		}
	} while(--num > 0);
	if(write_p->Bit != 0x01) {
		/* バッファへ書き込み */
		*(write_p->Buf + write_p->Adr) = ecm_data;
	}
}

/*************************************************************************
	module		:[ＥＣＭバッファリード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/15]
	author		:[鈴木郁二]
*************************************************************************/
WORD EcmRead(	struct Buf_p_t *read_p,
					UBYTE num	/* 読み出しビット数最大１６ビット */)
{
	WORD put_bit,rtn_data;
	UBYTE byte_data;
	rtn_data = 0;
	put_bit = 1;
	byte_data = (UBYTE)(*(read_p->Buf + read_p->Adr));
	do {
		if(read_p->Bit & byte_data) {
			rtn_data |= put_bit;
		}
		put_bit <<= 1;
		if(read_p->Bit == 0x80) {
			read_p->Bit = 0x01;
			read_p->Adr++;
			if(SCD_EcmSize == ECM_64_OCT) {
				if(read_p->Adr >= 64) {
					if (SCD_MaintenanceSwitch[SCD_MNT_SW_F3]) {/*	Test By Y.Suzuki 1997/07/07	*/
						wai_oneshot(SCD_MaintenanceSwitch[SCD_MNT_SW_F3]);
					}
					else {
						wai_oneshot(1);
					}
					read_p->Adr = 0;
					read_p->Buf += ECM_BUFFER_LENGTH;

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 					DecodeEcmFrameNum++;
#else
					(* DecodeEcmFrameNum_p)++;
#endif

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 					if(DecodeEcmFrameNum >= ECM_BUFFER_MAX) {
** 						DecodeEcmFrameNum = 0;
** 						/* read_p->Buf = &EcmBuffer[0][0];Ｌ系とＢ，Ｈでアドレスが異なるため By Y.Suzuki 1997/10/16*/
** 						read_p->Buf = SCD_EcmBufTopAddress;
** 						/* ブロックエンドの処理 */
** 						CodecPageStatus = CDC_BLOCK_END;
** 					/*	SCD_Det_Rcp = 1;		By Y.Suzuki 1997/07/01	*/
** 						wai_tsk(0xffff);
** 						CodecPageStatus = CDC_CONTINUE;
** 					/*	SCD_Det_Rcp = 0;		By Y.Suzuki 1997/07/01	*/
** 						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
** 						while (CheckEcmStatus(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
** 							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
** 						}
** 					}
** 					else {
** 						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
** 						while (CheckEcmStatus(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
** 							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
** 						}
** 					}
#else
					if(*DecodeEcmFrameNum_p >= ECM_BUFFER_MAX) {
						*DecodeEcmFrameNum_p = 0;
						/* read_p->Buf = &EcmBuffer[0][0];Ｌ系とＢ，Ｈでアドレスが異なるため By Y.Suzuki 1997/10/16*/
						read_p->Buf = SCD_EcmBufTopAddress;
						/* ブロックエンドの処理 */
						*CodecPageStatus_p = CDC_BLOCK_END;
					/*	SCD_Det_Rcp = 1;		By Y.Suzuki 1997/07/01	*/
						wai_tsk(0xffff);
						*CodecPageStatus_p = CDC_CONTINUE;
					/*	SCD_Det_Rcp = 0;		By Y.Suzuki 1997/07/01	*/
						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
						while (CheckEcmStatus(*DecodeEcmFrameNum_p) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
						}
					}
					else {
						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
						while (CheckEcmStatus(*DecodeEcmFrameNum_p) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
						}
					}
#endif

				}
			}
			else {
				if(read_p->Adr >= ECM_BUFFER_LENGTH) {
					if (SCD_MaintenanceSwitch[SCD_MNT_SW_F3]) {/*	Test By Y.Suzuki 1997/07/07	*/
						wai_oneshot(SCD_MaintenanceSwitch[SCD_MNT_SW_F3]);
					}
					else {
						wai_oneshot(1);
					}
					read_p->Adr = 0;
					read_p->Buf += ECM_BUFFER_LENGTH;

#if (0)
** /* 大域変数の参照を直接型から間接型に変更 By O.Kimoto 1998/10/05 */
** 					DecodeEcmFrameNum++;
** 					if(DecodeEcmFrameNum >= ECM_BUFFER_MAX) {
** 						DecodeEcmFrameNum = 0;
** 						/* read_p->Buf = &EcmBuffer[0][0];Ｌ系とＢ，Ｈでアドレスが異なるため By Y.Suzuki 1997/10/16*/
** 						read_p->Buf = SCD_EcmBufTopAddress;
** 						/* ブロックエンドの処理 */
** 						CodecPageStatus = CDC_BLOCK_END;
** 						SCD_Det_Rcp = 1;	/*	By Y.Suzuki 1997/07/01	*/
** 						wai_tsk(0xffff);
** 						CodecPageStatus = CDC_CONTINUE;
** 						SCD_Det_Rcp = 0;	/*	By Y.Suzuki 1997/07/01	*/
** 						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
** 						while (CheckEcmStatus(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
** 							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
** 						}
** 					}
** 					else {
** 						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
** 						while (CheckEcmStatus(DecodeEcmFrameNum) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
** 							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
** 						}
** 					}
#else
					(* DecodeEcmFrameNum_p)++;
					if(*DecodeEcmFrameNum_p >= ECM_BUFFER_MAX) {
						*DecodeEcmFrameNum_p = 0;
						/* read_p->Buf = &EcmBuffer[0][0];Ｌ系とＢ，Ｈでアドレスが異なるため By Y.Suzuki 1997/10/16*/
						read_p->Buf = SCD_EcmBufTopAddress;
						/* ブロックエンドの処理 */
						*CodecPageStatus_p = CDC_BLOCK_END;
						SCD_Det_Rcp = 1;	/*	By Y.Suzuki 1997/07/01	*/
						wai_tsk(0xffff);
						*CodecPageStatus_p = CDC_CONTINUE;
						SCD_Det_Rcp = 0;	/*	By Y.Suzuki 1997/07/01	*/
						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
						while (CheckEcmStatus(*DecodeEcmFrameNum_p) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
						}
					}
					else {
						/*	モデムバッファ －－＞ ＥＣＭバッファ転送待ち	*/
						while (CheckEcmStatus(*DecodeEcmFrameNum_p) == 1) {	/**	ＥＣＭフレームステータスが無効の時	*/
							wai_tsk(10/10);	/**	１０ｍｓタスクウェイト	*/
						}
					}
#endif

				}
			}
			byte_data = (UBYTE)(*(read_p->Buf + read_p->Adr));
		}
		else {
			read_p->Bit <<= 1;
		}
	} while(--num > 0);
	return(rtn_data);
}


/*************************************************************************
	module		:[モデムバッファにＲＴＣ書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/19]
	author		:[鈴木郁二]
*************************************************************************/
void WriteRtcToMdmIntRom(struct CdcBlk_t *cp)
{
	UBYTE bit_num,eol_cnt;
	UWORD data;
	eol_cnt = 6;/* eol の数 */
	bit_num = 12;
	data =0x800;/* For MH */
	if(cp->Coding == SYS_MR_CODE) {
		bit_num = 13;
		data = 0x1800;
	}
	else if(cp->Coding == SYS_MMR_CODE) {
		/* For EOFB */
		eol_cnt = 6;
	}
	do {
		MdmWrite(cp->Wp,bit_num,data);
		eol_cnt--;
	}while(eol_cnt);
}

/*************************************************************************
	module		:[ＥＣＭバッファにＲＴＣ書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/19]
	author		:[鈴木郁二]
*************************************************************************/
void WriteRtcToEcmIntRom(struct CdcBlk_t *cp)
{
	UBYTE bit_num,eol_cnt;
	UWORD data;
	eol_cnt = 6;/* eol の数 */
	bit_num = 12;
	data =0x800;/* For MH */
	if(cp->Coding == SYS_MR_CODE) {
		bit_num = 13;
		data = 0x1800;
	}
	else if(cp->Coding == SYS_MMR_CODE) {
		/* For EOFB */
		eol_cnt = 6;
	}
	do {
		EcmWrite(cp->Wp,bit_num,data);
		eol_cnt--;
	}while(eol_cnt);
}

/*************************************************************************
	module		:[メモリにＲＴＣ書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/19]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE WriteRtcToMemIntRom(struct CdcBlk_t *cp)
{
	UBYTE bit_num,eol_cnt;
	UWORD data;
	eol_cnt = 6;/* eol の数 */
	bit_num = 12;
	data =0x800;/* For MH */
	if(cp->Coding == SYS_MR_CODE) {
		bit_num = 13;
		data = 0x1800;
	}
	else if(cp->Coding == SYS_MMR_CODE) {
		/* For EOFB */
		eol_cnt = 6;
	}
	do {
		if(MemWrite(cp->Wp,bit_num,data) == RX_MEM_OVER) {
			return(RX_MEM_OVER);
		}
		eol_cnt--;
	}while(eol_cnt);
}

/*************************************************************************
	module		:[縮小初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
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

