 /*
  *	@(#)%W%
  *	FileName:	/mnt/jason/home2/prj/Eva/Src/def/sreg.c
  *	Create:	Tue Feb  3 11:21:02 1998	by	ishiyama
  *	Description:
  *		三洋画処理 LSI LC82103 Register & Buffer 定義
  *	Change Log:
  *		
  */
#include	"\src\atlanta\define\product.h"

#pragma section SREG		/* locate section name "BSREG" */
volatile UBYTE	Sreg0;
volatile UBYTE	Sreg1;
volatile UBYTE	Sreg2;
volatile UBYTE	Sreg3;
volatile UBYTE	Sreg4;
volatile UBYTE	Sreg5;
volatile UBYTE	Sreg6;
volatile UBYTE	Sreg7;
volatile UBYTE	Sreg8;
volatile UBYTE	Sreg9;
volatile UBYTE	SregA;
volatile UBYTE	SregB;
volatile UBYTE	SregC;
volatile UBYTE	SregD;
volatile UBYTE	SregE;
volatile UBYTE	SregF;
volatile UBYTE	Sreg10;
volatile UBYTE	Sreg11;
volatile UBYTE	Sreg12;
volatile UBYTE	Sreg13;
volatile UBYTE	Sreg14;
volatile UBYTE	Sreg15;
volatile UBYTE	Sreg16;
volatile UBYTE	Sreg17;
volatile UBYTE	Sreg18;
volatile UBYTE	Sreg19;
volatile UBYTE	Sreg1A;
volatile UBYTE	Sreg1B;
volatile UBYTE	Sreg1C;
volatile UBYTE	Sreg1D;
#pragma section

#pragma section LSI_RAM		/* locate section name "BLSI_BUF" */
UBYTE Lc82103Ram[3072];
#pragma section

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様 ガンマ補正メモリを追加 by Y.Kano 2003/11/27 */
#pragma section GAM_RAM		/* locate section name "BGAM_RAM" */
UBYTE Lc821033GammaRam[256];
#pragma section
#endif

