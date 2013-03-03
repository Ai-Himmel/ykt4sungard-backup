/************************************************************************
*	System		: POPLAR
*	File Name	: CPHPTBL.H
*	Author		: Y.Suzuki
*	Date		: 1998/1/14
*	Description	:拡張ＲＯＭからフラッシュＲＯＭ内のモジュールを参照するため
*				フラッシュＲＯＭのコールされるモジュールのアドレスを固定する
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"


/*指定ﾗｲﾝ符号化*/
/*UBYTE CipherEncode(UWORD);*/
/*UBYTE CipherEncFlsRom(UWORD);*/
extern CONST UBYTE (*CONST cph_enc_adr_tbl)(UWORD);
/*サービスラベル書込み*/
/*UBYTE WriteLabel(void);*/
/*UBYTE WriteLabelFlsRom(void);*/
extern CONST UBYTE (*CONST write_label_adr_tbl)();

/**/
/*int CuttingHeader(void);*/
/*int CuttingHeaderFlsRom(void);*/
extern CONST int (*CONST cut_header_adr_tbl)();

/*キー間違い検出通知*/
/*void IncorrectKey(void);*/
/*void IncorrectKeyFlsRom(void);*/
extern CONST void (*CONST incorrect_key_adr_tbl)();

/*タスクスイッチ用ルーチン*/
/*void show_slider (int , int);*/
/*void show_sliderFlsRom (int , int);*/
extern CONST void (*CONST show_slid_adr_tbl)(int,int);

/*読み取り原稿上下逆時通知 （カラッポ） */
/*void notify_upside_down(void);*/
/*void notifyUpDownFlsRom(void);*/
extern CONST void (*CONST notify_up_dw_adr_tbl)();

/*以下ダミー*/
#if (0)
//void	CipherEncodeStart(void){};
//void	CipherEncodeEnd(void){};
//void	CipherDecodeStart(void){};
//void	CipherDecodeEnd(void){};
#endif
/*void	CphEncStartFlsRom(void){};*/
extern CONST void (*CONST cph_enc_st_adr_tbl)();
/*void	CphEncEndFlsRom(void){};*/
extern CONST void (*CONST cph_enc_ed_adr_tbl)();
/*void	CphDecStartFlsRom(void){};*/
extern CONST void (*CONST cph_dec_st_adr_tbl)();
/*void	CphDecEndFlsRom(void){};*/
extern CONST void (*CONST cph_dec_ed_adr_tbl)();
