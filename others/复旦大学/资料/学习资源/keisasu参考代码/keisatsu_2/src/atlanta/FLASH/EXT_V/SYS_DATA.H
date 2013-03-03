
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : sys_data.h                                                */
/*  作成者       : 橘正樹                                                    */
/*  日  付       : 1997/05/17                                                */
/*  概  要       : フラッシュ書き換えシステム                                */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/

extern UWORD	SYS_GeneralTimer;

extern UWORD	SYS_Modem1PortStatus;
extern UWORD	SYS_Modem2PortStatus;
extern UWORD	SYS_ETC_PortStatus;
extern UWORD	SYS_ETC2_PortStatus;
extern UWORD	SYS_LCDC_PortStatus;
extern UWORD	SYS_LCD_DataPortStatus;
extern UWORD	SYS_LED1_PortStatus;
extern UWORD	SYS_LED2_PortStatus;
extern UWORD	SYS_COM_PortStatus;
extern UWORD	SYS_RTC_PortStatus;
extern UWORD	SYS_PADRH_PortStatus;
extern UWORD	SYS_PADRL_PortStatus;
extern UWORD	SYS_PDDRH_PortStatus;

extern UBYTE	SCN_MTPC0_Status;
extern UBYTE	SCN_MTPC1_Status;
extern UBYTE	SCN_MTP0_Status;
extern UBYTE	SCN_MTP1_Status;
extern UBYTE	SCN_SENSTP_Status;
extern UBYTE	SCN_SSTSTP_Status;
extern UBYTE	SCN_SCNINT_Status;
extern UBYTE	SCN_DS2INTR_Status;
extern UBYTE	SCN_BUZZ_1K_Status;
extern UBYTE	SCN_MTCNT_Status;
extern UBYTE	SCN_SCCNT_Status;
extern UBYTE	SCN_INTLNCN_Status;

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)	/* Add by Y.Kano 2003/07/11 */
/*---------------------------------------------------------------------------------------
 * G/Aの出力ポート状態保存RAM
 *--------------------------------------------------------------------------------------*/
extern UWORD	RelayPortStatus;
extern UWORD	GA_IntMaskStatus;
extern UDWORD IntTimerCounter;	/* 2.5ms割込みを5msに見せかけるカウンタ */
extern UWORD	GA_MWR_Status;
extern UWORD	GaPstartStatus;
extern UWORD	GaPrtcStatus;
extern UBYTE	LcdScanPos;				/* LCD表示書き換え中の位置を示す */
extern UBYTE	DisplayBufferHigh[21];
extern UBYTE	DisplayBufferLow[21];
extern UBYTE	NewKey;					/* キー入力データ(割り込み内設定用) */
extern UWORD	GaTmr0Status; 	/* 1999/11/15 by T.Soneoka */
extern UWORD	GaRmrStatus;	/* 1999/11/15 by T.Soneoka */
#endif

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1999/10/18 H.Yoshikawa */
extern UWORD	M01_Status;		/** ＭＤ９４０２　アドレス０５７０Ｈ用ステータス **/
#endif

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/04 T.Takagi */
extern UBYTE	RomNumber;
extern UWORD	RomCheckSum[];
extern UWORD	SYS_ROM_LED_PortStatus;
#endif
