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
/* #include "\src\atlanta\ext_v\sys_data.h" */
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\define\mntsw_e.h"
/* #include "\src\atlanta\ext_v\bkupram.h" */
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\lst_def.h"
/* #include "\src\atlanta\ext_v\lst_data.h" */
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\apl_msg.h"
/* #include "\src\atlanta\ext_v\mem_data.h" */
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sys_line.h"

#include "z:\public\cc\shc\bin\stdlib.h"
#include "z:\public\cc\shc\bin\stddef.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h"
#include "\src\cpu\sh7043_a\scd\aliroo\define\resource.h" /*	By R.Cohen 1997/12/02	*/
#include "\src\cpu\sh7043_a\scd\define\cphpro.h"/*By Y.Suzuki 1998/02/18*/
#include "\src\cpu\sh7043_a\scd\define\alrpro.h"/*By Y.Suzuki 1998/03/11*/
#else
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\ext_v\cph_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\aliroo\define\scrdlapi.h"
#include "\src\atlanta\scd\aliroo\define\resource.h" /*	By R.Cohen 1997/12/02	*/
#include "\src\atlanta\scd\define\cphpro.h"/*By Y.Suzuki 1998/02/18*/
#include "\src\atlanta\scd\define\alrpro.h"/*By Y.Suzuki 1998/03/11*/
#endif

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/11/17 */
/* #include "\src\atlanta\mdm\orange\ext_v\mdm_data.h" */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/17 */
/* #include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h" */
#endif /* (PRO_MODEM == R288F) */

/* #include "\src\atlanta\ext_v\ncu_data.h" *//*By Y.Suzuki 1998/06/08*/
#include "\src\atlanta\define\ncu_stat.h"/*By Y.Suzuki 1998/06/08*/

#if defined(SAKAKI)
/* #include "\src\atlanta\prt\thermal\ext_v\prn_data.h" */
#endif

#if (0)/*By Y.Suzuki 1998/03/11*/
//extern void AlirooScramble (struct CipherTbl_t *);
//extern void AlirooDescramble (struct CipherTbl_t *);
#endif

#if (0)
extern int should_ask_cutting;
extern int	glb_err;

/*	By R.Cohen 1997/12/02	*/
extern int loc_slider;
extern int slider_size;

extern UWORD	tskno_SCN_DocumentStoreTask;
extern UWORD	tskno_OPR_KeyTimerTask;
#endif


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
#pragma section SCD /* locate section name "CMEMMTBL" */
void SCD1LineRlToImgIntRom(struct WorkBuf_t *point,
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
					Img_Buffer1[line][ImgCntr] = ImgbyteClor;
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
					Img_Buffer1[line][ImgCntr]=ImgBufData;
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
#pragma section /* locate section name "PSCD" */

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
void SCD1LineRlToImgIntRom2(struct WorkBuf_t *point,
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
					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UDWORD)ImgCntr) = ImgbyteClor;
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
					*(img_buffer1 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UDWORD)ImgCntr) = ImgBufData;
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
void SCD1LineImgToRlIntRom2(struct WorkBuf_t *point,
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
		ImgBufData = *(img_buffer2 + (UWORD)(line * SCD_LINE_BUF_WIDTH) + (UWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
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
void SAKAKI1LineRL_ToImage2(struct WorkBuf_t *point,
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
					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgbyteClor;	/*1998.8.19 K.Kawata*/
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
					*(prn_imgbuf1_p + (line * PRT_IMG_BUF_SIZE) + ImgCntr) = ImgBufData;	/*1998.8.19 K.Kawata*/
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
#pragma section  /* locate section name "PSCD" */

