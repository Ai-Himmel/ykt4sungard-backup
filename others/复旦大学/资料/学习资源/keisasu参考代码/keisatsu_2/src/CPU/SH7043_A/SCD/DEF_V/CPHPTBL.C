/************************************************************************
*	System		: POPLAR
*	File Name	: SCDIRPRO.C
*	Author		: Y.Suzuki
*	Date		: 1998/1/14
*	Description	:拡張ＲＯＭからフラッシュＲＯＭ内のモジュールを参照するため
*				フラッシュＲＯＭのコールされるモジュールのアドレスを固定する
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\cphfxpro.h"
#else
#include "\src\atlanta\scd\define\cphfxpro.h"
#endif

#pragma section SCDALR /* locate section name "CSCDALR" */

/*指定ﾗｲﾝ符号化*/
/*UBYTE CipherEncode(UWORD);*/
/*UBYTE CipherEncFlsRom(UWORD);*/
CONST UBYTE (*CONST cph_enc_adr_tbl)(UWORD) = (UBYTE (*)(UWORD))CipherEncFlsRom;
/*サービスラベル書込み*/
/*UBYTE WriteLabel(void);*/
/*UBYTE WriteLabelFlsRom(void);*/
CONST UBYTE (*CONST write_label_adr_tbl)() = (UBYTE (*)())WriteLabelFlsRom;

/**/
/*int CuttingHeader(void);*/
/*int CuttingHeaderFlsRom(void);*/
CONST int (*CONST cut_header_adr_tbl)() = (int (*)())CuttingHeaderFlsRom;

/*キー間違い検出通知*/
/*void IncorrectKey(void);*/
/*void IncorrectKeyFlsRom(void);*/
CONST void (*CONST incorrect_key_adr_tbl)() = (void (*)())IncorrectKeyFlsRom;

/*タスクスイッチ用ルーチン*/
/*void show_slider (int , int);*/
/*void show_sliderFlsRom (int , int);*/
CONST void (*CONST show_slid_adr_tbl)(int,int) = (void (*)(int,int))show_sliderFlsRom;

/*読み取り原稿上下逆時通知 （カラッポ） */
/*void notify_upside_down(void);*/
/*void notifyUpDownFlsRom(void);*/
CONST void (*CONST notify_up_dw_adr_tbl)() = (void (*)())notifyUpDownFlsRom;

/*以下ダミー*/
#if (0)
//void	CipherEncodeStart(void){};
//void	CipherEncodeEnd(void){};
//void	CipherDecodeStart(void){};
//void	CipherDecodeEnd(void){};
#endif
/*void	CphEncStartFlsRom(void){};*/
CONST void (*CONST cph_enc_st_adr_tbl)() = (void (*)())CphEncStartFlsRom;
/*void	CphEncEndFlsRom(void){};*/
CONST void (*CONST cph_enc_ed_adr_tbl)() = (void (*)())CphEncEndFlsRom;
/*void	CphDecStartFlsRom(void){};*/
CONST void (*CONST cph_dec_st_adr_tbl)() = (void (*)())CphDecStartFlsRom;
/*void	CphDecEndFlsRom(void){};*/
CONST void (*CONST cph_dec_ed_adr_tbl)() = (void (*)())CphDecEndFlsRom;


#pragma section /* locate section name "CSCDALR" */
