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
/*指定ﾗｲﾝ符号化*/
/*UBYTE CipherEncode(UWORD);*/
UBYTE CipherEncFlsRom(UWORD);

/*サービスラベル書込み*/
/*UBYTE WriteLabel(void);*/
UBYTE WriteLabelFlsRom(void);

/**/
/*int CuttingHeader(void);*/
int CuttingHeaderFlsRom(void);

/*キー間違い検出通知*/
/*void IncorrectKey(void);*/
void IncorrectKeyFlsRom(void);

/*タスクスイッチ用ルーチン*/
/*void show_slider (int , int);*/
void show_sliderFlsRom (int , int);

/*読み取り原稿上下逆時通知 （カラッポ） */
/*void notify_upside_down(void);*/
void notifyUpDownFlsRom(void);

/*以下ダミー*/
#if (0)
//void	CipherEncodeStart(void){};
//void	CipherEncodeEnd(void){};
//void	CipherDecodeStart(void){};
//void	CipherDecodeEnd(void){};
#endif
void	CphEncStartFlsRom(void){};
void	CphEncEndFlsRom(void){};
void	CphDecStartFlsRom(void){};
void	CphDecEndFlsRom(void){};
