/*--------------------------------------------------------------------------*/
/*  ﾌﾟﾛｼﾞｪｸﾄ : POPLAR/ANZU_L                                                */
/*  ﾌｧｲﾙ名   : int_slve.c                                                   */
/*  作成者   : 野瀬                                                         */
/*  日  付   : 1996/11/08                                                   */
/*  概  要   : 外部追加割込エントリ                                         */
/*  修正履歴 :                                                              */
/*  コメント :                                                              */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\idp301.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\define\cl1_pro.h"	/* S.Fukui Jul.7,1998 */

UWORD SCN_Int(void);
void PRN_PSS_Interrupt(void);
void NCU_CI_Interrupt(void);
void DPRAM_Interrupt(void);
void INT_MPSC(void);	/* 1997/08/18 Y.Matsukuma */

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
void NCU_CI2_Interrupt(void);
#endif
#if defined(ANZU_V)	/* 1998/04/03 Eguchi */
void	INF_MPSC_Interrupt(void);
#endif
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
void MDM_ModemInterrupt(void);	/* 外部追加割り込み７０の処理（モデム割り込み) */
#endif

/*************************************************************************
	module		:[外部追加割込エントリー]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INT]
	date		:[1996/11/08]
	author		:[野瀬敏弘]
*************************************************************************/
void INT_SlaveInterrupt(void)
{
	UWORD i_status;
	UWORD value;

	i_status = inpw(INTERRPUT_PORT);

	if (i_status & IO_BIT_INT70) {		/* 外部追加割込み７０（ＤＩＰＰ割込み） */
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR70;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR70;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

		MDM_ModemInterrupt();	/* 外部追加割り込み７０の処理（モデム割り込み) */

		SYS_InterruptPortStatus &= IO_BIT_INTCLR70;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
#else
		SYS_InterruptPortStatus &= IO_BIT_INTCLR70;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR70;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
   #if !defined (KEISATSU) /* Modify by SMuratec 李 2005/06/29 */
		NCU_CI2_Interrupt(); /* 外部追加割り込み７０の処理（ＣＩ２割り込み) */
   #endif /* defined (KEISATSU) */
  #else
		inpw(IDP_INT_PORT);				/* 割込みステータスレジスタをリード
										** リードするだけ。リードした結果を何かに使用する事はありません
										*/
  #endif
#endif
	}


	else if (i_status & IO_BIT_INT71) {	/* 外部追加割込み７１ （スキャナー・モーター割込み）*/
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR71;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR71;	/* 割込検出を禁止 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

		NCU_CI_Interrupt(); /* 外部追加割り込み７１の処理（ＣＩ割り込み) */

		SYS_InterruptPortStatus &= IO_BIT_INTCLR71;	/* 割込検出を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
#else
		SYS_InterruptPortStatus &= IO_BIT_INTCLR71;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR71;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

		value = SCN_Int();
		if (value) {
			idet_evt(value);
		}
#endif
	}


	else if (i_status & IO_BIT_INT72) {	/* 外部追加割込み７２ */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR72;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR72;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
		DPRAM_Interrupt(); /* 外部追加割込み７２の処理（ＤＰＲＡＭ割り込み）*/
#else
		NCU_CI_Interrupt(); /* 外部追加割り込み７２の処理（ＣＩ割り込み) */
#endif

	}


	else if (i_status & IO_BIT_INT73) {	/* 外部追加割込み７３ */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR73;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR73;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
		/* SAKAKIは未使用 1998.6.9 K.kawata */
#else
		DPRAM_Interrupt(); /* 外部追加割込み７３の処理（ＤＰＲＡＭ割り込み）*/
#endif
	}


	else if (i_status & IO_BIT_INT74) {	/* 外部追加割込み７４ */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR74;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR74;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

#if defined(ANZU_L)	/** ＡＮＺＵ＿ＬタイプはＲＳ２３２Ｃです */
		INT_MPSC();	/* 1997/08/18 Y.Matsukuma */
#else
 #if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
 		/* SAKAKIは未使用 1998.6.9 K.kawata */
 #else
  #if defined(ANZU_V)
		INF_MPSC_Interrupt();
  #else
		PRN_PSS_Interrupt();	/* 外部追加割込み７４の処理（ＰＳＳ割り込み） */
  #endif
 #endif
#endif
	}

#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
 		/* SAKAKIは未使用 1998.6.9 K.kawata */
#else
 #if defined(ANZU_L) || defined (ANZU_V) || defined (POPLAR_L)/** ＡＮＺＵ＿ＬタイプはＲＳ２３２Ｃです */
 #else
	else if (i_status & IO_BIT_INT77) {	/* 外部追加割込み７７ */
		SYS_InterruptPortStatus &= IO_BIT_INTCLR77;		/* 割込検出フラグをクリア */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		SYS_InterruptPortStatus |= ~IO_BIT_INTCLR77;	/* 割込検出フラグ出力を許可 */
		outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
		INT_MPSC();	/* 1997/08/18 Y.Matsukuma */
	}
 #endif
#endif
	else {
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[外部追加割込制御ポートの初期設定]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		ＩＲＱ７６，７７は使用しないので定義されていません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INT]
	date		:[1997/02/07]
	author		:[野瀬敏弘]
*************************************************************************/
void INT_InitializeExternalInterrupt(void)
{
	/* ＩＲＱ７０～７５をマスク */
	/* ＩＲＱ７０～７５の割込要因レジスタのフラグをクリア */
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	SYS_InterruptPortStatus = 0x03ff; /* MSK0 - MSK4 までを立てて割り込みをマスクする。 */
#else
	SYS_InterruptPortStatus = 0x0000;
#endif
	outpw(INT_MASK_PORT,SYS_InterruptPortStatus);
	/* 外部追加割り込みの検出をエッジ検出にする */
	SYS_COM_PortStatus = 0;
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	/* SAKAKIでは、IREQSELはMCR_PORT（SYS_MCR_PortStatus）にあります。
	** このポート自体、SAKAKIで追加されたものです。
	** SAKAKIでは、SYS_COM_PortStatusは使用していませんが、０クリアだけしておきます。
	** 1998/06/22 H.Yoshikawa
	*/ 
	SYS_MCR_PortStatus = 0;
	SYS_MCR_PortStatus &= ~IO_BIT_INTSEL;
	SYS_MCR_PortStatus |= IO_BIT_MDMACKCLR; /* MD9805 のモデムACKクリア時間設定 480ns にする。 added by H.Kubo 1998/07/20 */
	outpw(MCR_PORT,SYS_MCR_PortStatus);
#else
	SYS_COM_PortStatus = 0;
	SYS_COM_PortStatus &= ~IO_BIT_IREQSEL;
	outpw(COM_PORT,SYS_COM_PortStatus);
#endif

	/* ＩＲＱ７０～７５の割込要因レジスタの出力許可 */
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	SYS_InterruptPortStatus = 0x001C; /* MSK0 - MSK1 までを 0 にして割り込みマスクを解除する。 */
#else
	SYS_InterruptPortStatus = 0x0FFF;
#endif
	outpw(INT_MASK_PORT,SYS_InterruptPortStatus);

	return;
}
