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

