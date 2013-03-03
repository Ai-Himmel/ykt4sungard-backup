/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_IO.C
*	Author		: 橘正樹
*	Date		: 1997/05/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_io.c
*				  HINOKI 対応 By O.Kimoto 1998/12/21
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\sh7043\define\cpu_def.h"

#include "\src\ATLANTA\FLA\define\sys_pro.h"
/* #include "\src\ATLANTA\FLA\ext_v\sys_data.h" */

#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1998/06/05 Y.Murata  LED_LCD_IO_WAIT */
	UWORD FLA_CheckSH_WCR1_CS3(void);
	void FLA_SetSH_WCR1_CS3(UWORD wait);
	void FLA_outpw_2(UDWORD PortAddress, UWORD data);
	UWORD FLA_inpw_2(UDWORD PortAddress);
#endif

#include "\src\atlanta\sh7043\define\io_pro.h"

#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
/************************************************************************
 * Ｉ／Ｏに関するプロトタイプ											*
 ************************************************************************/
/* I/Oからの入力 -------------------------------------------------------------------------------
extern UBYTE Input(*(volatile UBYTE *)addr);
extern UWORD InputWORD(*(volatile UWORD *)addr);
extern UDWORD InputDWORD(*(volatile UDWORD *)addr);
	Sample1: UBYTE a,*ap;	a = Input(addr);
	Sample2: UWORD b;	 	b = InputWORD(*(volatile UDWORD *)0x1234);
--------------------------------------------------------------------------------------------- */
/* ATTENTION ********
 *  if you want to use dummy read, you must set return value to a tempolary valiable.
 *  Input(IOPointer);               // It's BAD code
 *  UBYTE DummyStackValiable; DummyStackValiable = Input(IOPointer);  // Good
 */
#define	Input(Address)	((UBYTE)(*(Address)))
#define	InputWORD(Address)	((UWORD)(*(Address)))
#define	InputDWORD(Address)	((UDWORD)(*(Address)))
/* I/Oへの出力 -------------------------------------------------------------------------------
extern void Output(*(volatile UBYTE *)addr, UBYTE Data);
extern void OutputWORD(*(volatile UWORD *)addr, UWORD Data);
extern void OutputDWORD(*(volatile UDWORD *)addr, UDWORD Data);
	Sample: UDWORD c;   OutputDWORD(0x100, c);
--------------------------------------------------------------------------------------------- */
#define	Output(Address, Data)	{*(Address) = (UBYTE)(Data);}
#define	OutputWORD(Address, Data)	{*(Address) = (UWORD)(Data);}
#define	OutputDWORD(Address, Data)	{*(Address) = (UDWORD)(Data);}
#endif


#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)

/*************************************************************************
	module		:[ＩＯポートの初期化]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/10/09]
	author		:[橘正樹]
*************************************************************************/
void	FLA_IO_Port_Initialize(void)
{
	SYS_PADRH_PortStatus = IO__PADRH_DATA;		/* ＣＰＵポートＡＨ By M.Kotani 97/06/13 */
	SYS_PADRL_PortStatus = IO__PADRL_DATA;		/* ＣＰＵポートＡＬ By M.Kotani 97/06/13 */
	SYS_PDDRH_PortStatus = IO__PDDRH_DATA;		/* ＣＰＵポートＤＨ By M.Kotani 97/06/13 */
	SYS_Modem1PortStatus = 0;		/** MRD9201モデム・ポ－ト1／ビット・アサイメント */
	SYS_Modem2PortStatus = 0;		/** MRD9201モデム・ポ－ト2／ビット・アサイメント */
	SYS_ETC_PortStatus = 0;			/** その他・ポ－ト／ビット・アサイメント */
	SYS_ETC2_PortStatus = 0;		/** その他・ポ－ト／ビット・アサイメント */
	SYS_LED1_PortStatus = 0xFF;		/** ＬＥＤ・ポ－ト1／ビット・	アサイメント */
	SYS_LED2_PortStatus = 0xFF;		/** ＬＥＤ・ポ－ト２／ビット・アサイメント */

#if (PRO_PANEL == ANK)

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/* #if (PRO_KEYPANEL == PANEL_HINOKI)	*/	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */

 #else
	SYS_LCDC_PortStatus = LCDC_PORT_DATA;	/** ＬＣＤポ－ト／ビット・アサイメント */
 #endif
#endif

	SYS_LCD_DataPortStatus = 0;		/** ＬＣＤデータポート／ビット・アサイメント */
	SYS_RTC_PortStatus = 0;			/** ＲＴＣ・ポ－ト／ビット・アサイメント */

#if defined(POPLAR_B) || defined(POPLAR_L) || defined(POPLAR_H) || defined(POPLAR_N) || defined(POPLAR_F)
	/* 高圧、ＦＡＮ、ヒターをＯＦＦする */
	SYS_Modem2PortStatus = 0x0800;
	SYS_Modem2PortStatus = 0x0000;
	FLA_outpw(MODEM2_PORT, SYS_Modem2PortStatus);
	FLA_outpw(ETC_PORT, SYS_ETC_PortStatus);
#endif
}

/*************************************************************************
	module		:[スピーカミュートＯＮ]
	function	:[
		1.スピーカ出力をミュートする。（消音）
		２．ＥＴＣポート用ＲＡＭのＤ７に１をかく。
		３．ＥＴＣポート用ＲＡＭの値を５０Ｈに出力する。
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	FLA_SpeakerMuteOn(void)
{
#if defined(ANZU_L)	/** ＡＮＺＵ＿Ｌタイプ */
	IO__PADRH |= IO_BIT_MUTE;
#else
 #if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
	IO__PEDR |= IO_BIT_MUTE;
 #elif defined(SAKAKI)	/* 1998/10/17 H.Yoshikawa */
	outpw(MODEM2_PORT, (UWORD)(SYS_Modem2PortStatus |= IO_BIT_MUTE));
 #else
	SYS_ETC_PortStatus |= IO_BIT_MUTE;
	FLA_outpw(ETC_PORT, (UWORD)SYS_ETC_PortStatus);
 #endif
#endif
}

/*************************************************************************
	module		:[スピーカミュートOFF]
	function	:[
		1.スピーカミュートを解除する。（音が出る）
		２．ＥＴＣポート用ＲＡＭのＤ７に０をかく。
		３．ＥＴＣポート用ＲＡＭの値を５０Ｈに出力する。
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	FLA_SpeakerMuteOff(void)
{
#if defined(ANZU_L)	/** ＡＮＺＵ＿Ｌタイプ */
	IO__PADRH &= ~IO_BIT_MUTE;
#else
 #if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
	IO__PEDR &= ~IO_BIT_MUTE;
 #elif defined(SAKAKI)	/* 1998/10/17 H.Yoshikawa */
	outpw(MODEM2_PORT, (UWORD)(SYS_Modem2PortStatus &= (~IO_BIT_MUTE)));
 #else
	SYS_ETC_PortStatus &= ~IO_BIT_MUTE;
	FLA_outpw(ETC_PORT, (UWORD)SYS_ETC_PortStatus);
 #endif
#endif
}

/*************************************************************************
	module		:[スピーカーボリューム調整]
	function	:[
		1.ブザー鳴動時のボリューム調整を行う
	]
	return		:[]
	common		:[SYS_ETC_PortStatus]
	condition	:[]
	comment		:[引数で与えているボリュームの値はメモリースイッチにセットされている
				  1995/10/26 小／中の論理を変更]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	FLA_BuzzerVolumeControl(void)
{
	UBYTE	volume;

#if defined(ANZU_L)	/** ＡＮＺＵ＿Ｌタイプ */
	IO__PADRH |= IO_BIT_VOL1;
	IO__PADRH &= ~IO_BIT_VOL0;
#else
 #if (PRO_MEKA_VOLUME == ENABLE)
 /* ＳＡＫＡＫＩ／ＨＩＮＯＫＩは回転ボリュームが付いているので、
 ** 以下のような処理は出来ない。
 ** By O.Kimoto 1998/09/22
 */
 #else
	volume = 2;

	SYS_ETC_PortStatus &= ~(IO_BIT_SPVR1 | IO_BIT_SPVR2);
	switch (volume) {
		case 0:					/* 切  */
			break;
		case 1:					/* 小  */
			SYS_ETC_PortStatus |= IO_BIT_SPVR1;
			break;
		case 2:					/* 中  */
			SYS_ETC_PortStatus |= IO_BIT_SPVR2;
			break;
		case 3:					/* 大  */
			SYS_ETC_PortStatus |= (IO_BIT_SPVR1 | IO_BIT_SPVR2);
			break;
		default:
			break;
	}
	FLA_outpw(ETC_PORT, (UWORD)SYS_ETC_PortStatus);
 #endif
#endif
}

/*************************************************************************
	module		:[スピーカー出力切り替え(BUZZER)]
	function	:[
		1.スピーカー出力をブザー側に切り替える
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[デフォルトはブザー側にしておくこと。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/04]
	author		:[江口]
*************************************************************************/
void	FLA_SpeakerOutBuzzer(void)
{
#if defined(ANZU_L)	/** ＡＮＺＵ＿Ｌタイプ */
	IO__PADRL &= ~IO_BIT_RXA_BZ;
#else
 #if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
	RelayPortStatus &= ~IO_BIT_RXA_BZ;
	OutputWORD(GA_PGADR, RelayPortStatus);
	IO__PEDR |= IO_BIT_BUZZ;
 #elif defined(SAKAKI)	/* 1998/10/17 H.Yoshikawa */
	SYS_Modem2PortStatus &= ~IO_BIT_RXA_BZ;
	outpw(MODEM2_PORT, SYS_Modem2PortStatus);
 #else
	SYS_Modem2PortStatus &= ~IO_BIT_RXA_BZ;
	FLA_outpw(MODEM2_PORT, SYS_Modem2PortStatus);
 #endif
#endif
}



#if (PRO_KEYPANEL == PANEL_ANZU_L)
/* 1998/06/05 Y.Murata  LED_LCD_IO_WAIT
 * ＬＣＤＣポート、ＬＣＤデータポート、ＬＣＤビジーポート
 * ＬＥＤ１ポート、ＬＥＤ２ポートのＩＯウエイトだけを伸ばします。
 * 他のポートのウエイトは同じ
 * 一段かまします。
*/
UWORD FLA_CheckSH_WCR1_CS3(void)
{
	UWORD wcr1;

	wcr1 = SH__WCR1;				/**I/O Read*/
	wcr1 >>= (UWORD)12;				/**12ビットシフト*/
	wcr1 &= 0x000F;					/**上位クリア*/
	return(wcr1);
}

void FLA_SetSH_WCR1_CS3(UWORD wait)
{
	UWORD wcr1;

	wcr1 = SH__WCR1;				/**I/O Read*/
	wcr1 &= 0x0FFF;					/**最上位クリア*/
	wcr1 |= (UWORD)(wait << 12);	/**12ビットシフト*/
	SH__WCR1 = wcr1;
}

void  FLA_outpw(UDWORD PortAddress, UWORD data)
{
	UWORD	io_wait;

	if ((PortAddress == LCDC_PORT)
	 || (PortAddress == LCD_DATA_PORT)
	 || (PortAddress == LED1_PORT)
	 || (PortAddress == LED2_PORT)) {

		io_wait = FLA_CheckSH_WCR1_CS3();
		FLA_SetSH_WCR1_CS3(5);
		FLA_outpw_2(PortAddress, data);
		FLA_SetSH_WCR1_CS3(io_wait);
	}
	else {
		FLA_outpw_2(PortAddress, data);
	}
}

UWORD  FLA_inpw(UDWORD PortAddress)
{
	UWORD	io_wait;
	UWORD	ret;

	if (PortAddress == LCD_BUSY_PORT) {

		io_wait = FLA_CheckSH_WCR1_CS3();
		FLA_SetSH_WCR1_CS3(5);
		ret = FLA_inpw_2(PortAddress);
		FLA_SetSH_WCR1_CS3(io_wait);
		return(ret);
	}
	else {
		return (FLA_inpw_2(PortAddress));
	}
}
#endif

#endif

#pragma section
