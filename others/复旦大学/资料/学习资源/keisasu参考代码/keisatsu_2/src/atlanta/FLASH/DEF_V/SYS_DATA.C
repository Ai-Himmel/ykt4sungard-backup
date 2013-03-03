/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : sys_data.c                                                */
/*  作成者       : 橘正樹                                                    */
/*  日  付       : 1997/05/17                                                */
/*  概  要       : フラッシュ書き換えシステム                                */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"

UWORD	SYS_GeneralTimer = 0;

UWORD	SYS_Modem1PortStatus = 0;
UWORD	SYS_Modem2PortStatus = 0;
UWORD	SYS_ETC_PortStatus = 0;
UWORD	SYS_ETC2_PortStatus = 0;
UWORD	SYS_LCDC_PortStatus = 0;
UWORD	SYS_LCD_DataPortStatus = 0;
UWORD	SYS_LED1_PortStatus = 0;
UWORD	SYS_LED2_PortStatus = 0;
UWORD	SYS_COM_PortStatus = 0;
UWORD	SYS_RTC_PortStatus = 0;
UWORD	SYS_PADRH_PortStatus = 0;
UWORD	SYS_PADRL_PortStatus = 0;
UWORD	SYS_PDDRH_PortStatus = 0;


UBYTE	SCN_MTPC0_Status = 0;
UBYTE	SCN_MTPC1_Status = 0;
UBYTE	SCN_MTP0_Status = 0;
UBYTE	SCN_MTP1_Status = 0;
UBYTE	SCN_SENSTP_Status = 0;
UBYTE	SCN_SSTSTP_Status = 0;
UBYTE	SCN_SCNINT_Status = 0;
UBYTE	SCN_DS2INTR_Status = 0;
UBYTE	SCN_BUZZ_1K_Status = 0;
UBYTE	SCN_MTCNT_Status = 0;
UBYTE	SCN_SCCNT_Status = 0;
UBYTE	SCN_INTLNCN_Status = 0;


#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)	/* Add by Y.Kano 2003/07/11 */
/*---------------------------------------------------------------------------------------
 * G/Aの出力ポート状態保存RAM
 *--------------------------------------------------------------------------------------*/
UWORD	RelayPortStatus = 0;
UWORD	GA_IntMaskStatus = 0;
UDWORD IntTimerCounter = 0;	/* 2.5ms割込みを5msに見せかけるカウンタ */

UWORD	GA_MWR_Status = 0;
UWORD	GaPstartStatus = 0;
UWORD	GaPrtcStatus = 0;

/************************************
 * 表示関連
 ************************************/
UBYTE	LcdScanPos = 0;				/* LCD表示書き換え中の位置を示す */
UBYTE	DisplayBufferHigh[21] = {0};
UBYTE	DisplayBufferLow[21] = {0};
UBYTE	NewKey = 0;					/* キー入力データ(割り込み内設定用) */

UWORD	GaTmr0Status = 0; 	/* 1999/11/15 by T.Soneoka */
UWORD	GaRmrStatus = 0;	/* 1999/11/15 by T.Soneoka */

#endif

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1999/10/18 H.Yoshikawa */
UWORD	M01_Status		= 0;		/** ＭＤ９４０２　アドレス０５７０Ｈ用ステータス **/
#endif

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/04 T.Takagi */
UBYTE	RomNumber = 0;
UWORD	RomCheckSum[6] = {0,0,0,0,0,0};
UWORD	SYS_ROM_LED_PortStatus = 0;
#endif
