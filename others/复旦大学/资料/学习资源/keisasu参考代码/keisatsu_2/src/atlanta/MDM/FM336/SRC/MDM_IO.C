/*--------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                             */
/*  ファイル名   : mdm_IO.c                                                             */
/*  作成者       :                                                                      */
/*  日  付       : 1999/10/06                                                           */
/*  概  要       : Ｒｏｃｋｗｅｌｌ Ｒ２８８ＦモデムＩ／Ｏドライバー                    */
/*  修正履歴     :                                                                      */
/*	keyword			:[MDM]                                                              */
/*	machine			:[SH7043,V53]                                                       */
/*	language		:[MS-C(Ver.6.0)]                                                    */
/*--------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_conf.h" /* for FM336 CONF value. Added by H. Kubo 1997/06/19 *//* 99/07/06 Mod. by J.Kishida */
#include "\src\atlanta\define\mnt_sw.h"

/* #include "\src\atlanta\define\sta_pro.h" */
#include "\src\atlanta\define\mon_pro.h" /* Added by H. Kubo 1997/06/12 */
#include "\src\atlanta\define\cmn_pro.h" /* Added by H. Kubo 1997/07/11 */
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"		/* debug */
#include "\src\atlanta\ext_v\sys_data.h"		/* added by H.Kubo 1997/11/05 */
#include "\src\atlanta\ext_v\bkupram.h"


/*************************************************************************
	module		:[R288F モデムチップのモデムコンフィグレーション 設定値 (Designer's guide 表3.1 参照)]
	function	:[
		1.
	]
	return		:[UBYTE ( MDM_R288F_CONF_**** ) ]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void  MDM_BPS_ToR288F_MemBitCONF(UBYTE){}]
	date		:[1995/12/06]
	author		:[久保博]
*************************************************************************/

UBYTE MDM_BPS_ToR288F_MemBitCONF(UBYTE bps)
{
	switch(bps) {
	case V8_SETUP:
		return MDM_R288F_CONF_V8;
		break;
	case V8_CLEARDOWN:
		return MDM_R288F_CONF_V8_CLEARDOWN;
		break;
/** V.34 **/
	case BPS33600_V34:
		return MDM_R288F_CONF_BPS33600_V34;
		break;
	case BPS31200_V34:
		return	MDM_R288F_CONF_BPS31200_V34;
		break;
	case BPS28800_V34:
		return MDM_R288F_CONF_BPS28800_V34;
		break;
	case BPS26400_V34:
		return MDM_R288F_CONF_BPS26400_V34;
		break;
	case BPS24000_V34:
		return MDM_R288F_CONF_BPS24000_V34;
		break;
	case BPS21600_V34:
		return MDM_R288F_CONF_BPS21600_V34;
		break;
	case BPS19200_V34:
		return MDM_R288F_CONF_BPS19200_V34;
		break;
	case BPS16800_V34:
		return MDM_R288F_CONF_BPS16800_V34;
		break;
	case BPS14400_V34:
		return MDM_R288F_CONF_BPS14400_V34;
		break;
	case BPS12000_V34:
		return MDM_R288F_CONF_BPS12000_V34;
		break;
	case BPS9600_V34:
		return MDM_R288F_CONF_BPS9600_V34;
		break;
	case BPS7200_V34:
		return MDM_R288F_CONF_BPS7200_V34;
		break;
	case BPS4800_V34:
		return MDM_R288F_CONF_BPS4800_V34;
		break;
	case BPS2400_V34:
		return MDM_R288F_CONF_BPS2400_V34;
		break;
	case CLEARDOWN_V34:
		return MDM_R288F_CONF_CLEARDOWN_V34;
		break;
/** V.33 **/
	case BPS14400_V33:
		return MDM_R288F_CONF_BPS14400_V33;
		break;
	case BPS12000_V33:
		return MDM_R288F_CONF_BPS12000_V33;
		break;
	case BPS9600_V33:
		return MDM_R288F_CONF_BPS9600_V33;
		break;
	case BPS7200_V33:
		return MDM_R288F_CONF_BPS7200_V33;
		break;
/** V.17 **/
	case BPS14400_V17:
		return MDM_R288F_CONF_BPS14400_V17;
		break;
	case BPS12000_V17:
		return MDM_R288F_CONF_BPS12000_V17;
		break;
	case BPS9600_V17:
		return MDM_R288F_CONF_BPS9600_V17;
		break;
	case BPS7200_V17:
		return MDM_R288F_CONF_BPS7200_V17;
		break;
/** V.29 **/
	case BPS9600_V29:
		return MDM_R288F_CONF_BPS9600_V29;
		break;
	case BPS7200_V29:
		return MDM_R288F_CONF_BPS7200_V29;
		break;
	case BPS4800_V29:
		return MDM_R288F_CONF_BPS4800_V29;
		break;
/** V.27 ter **/
	case BPS4800_V27:
		return MDM_R288F_CONF_BPS4800_V27;
		break;
	case BPS2400_V27:
		return MDM_R288F_CONF_BPS2400_V27;
		break;
/** V.21 **/
	case BPS0_300_V21:
		return MDM_R288F_CONF_BPS0_300_V21;
		break;
	case BPS300_V21:
		return MDM_R288F_CONF_BPS300_V21;	/** Channel 2 **/
		break;
/** Etc. **/
	case TX_SINGLE_TONE:
		return MDM_R288F_CONF_TX_SINGLE_TONE;
		break;
	case TX_DUAL_TONE:
		return MDM_R288F_CONF_TX_DUAL_TONE;
		break;
	case DIALING:
		return MDM_R288F_CONF_DIALING;
		break;
	case DTMF_RECEIVER:
		return MDM_R288F_CONF_DTMF_RECEIVER;
		break;
/** V.23 **/
	case TX1200_V23:
		return MDM_R288F_CONF_TX1200_V23;	/* Tx:1200 Rx:75   */
		break;
	case RX1200_V23:
		return MDM_R288F_CONF_RX1200_V23;	/* Tx:75   Rx:1200 */
		break;
	default:
		/* This must not happen. */
		return bps;
		break;
	}
}


/*************************************************************************
	module		:[R288F モデムチップのモデムコンフィグレーション 設定値 (Designer's guide 表3.1 参照)
					から大域で参照される転送速度の #define 値 ]
	function	:[
		1.
	]
	return		:[UBYTE ( MDM_R288F_CONF_**** ) ]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void MDM_R288F_MemBitCONF_ToBPS(UBYTE conf){}]
	date		:[1995/12/06]
	author		:[久保博]
*************************************************************************/


UBYTE MDM_R288F_MemBitCONF_ToBPS(UBYTE conf)
{
	switch(conf) {
	case MDM_R288F_CONF_V8:
		return V8_SETUP;
		break;
	case MDM_R288F_CONF_V8_CLEARDOWN:
		return V8_CLEARDOWN;
		break;
/** V.34 **/
	case MDM_R288F_CONF_BPS33600_V34:
		return BPS33600_V34;
		break;
	case MDM_R288F_CONF_BPS31200_V34:
		return	BPS31200_V34;
		break;
	case MDM_R288F_CONF_BPS28800_V34:
		return BPS28800_V34;
		break;
	case MDM_R288F_CONF_BPS26400_V34:
		return BPS26400_V34;
		break;
	case MDM_R288F_CONF_BPS24000_V34:
		return BPS24000_V34;
		break;
	case MDM_R288F_CONF_BPS21600_V34:
		return BPS21600_V34;
		break;
	case MDM_R288F_CONF_BPS19200_V34:
		return BPS19200_V34;
		break;
	case MDM_R288F_CONF_BPS16800_V34:
		return BPS16800_V34;
		break;
	case MDM_R288F_CONF_BPS14400_V34:
		return BPS14400_V34;
		break;
	case MDM_R288F_CONF_BPS12000_V34:
		return BPS12000_V34;
		break;
	case MDM_R288F_CONF_BPS9600_V34:
		return BPS9600_V34;
		break;
	case MDM_R288F_CONF_BPS7200_V34:
		return BPS7200_V34;
		break;
	case MDM_R288F_CONF_BPS4800_V34:
		return BPS4800_V34;
		break;
	case MDM_R288F_CONF_BPS2400_V34:
		return BPS2400_V34;
		break;
	case MDM_R288F_CONF_CLEARDOWN_V34:
		return CLEARDOWN_V34;
		break;
/** V.33 **/
	case MDM_R288F_CONF_BPS14400_V33:
		return BPS14400_V33;
		break;
	case MDM_R288F_CONF_BPS12000_V33:
		return BPS12000_V33;
		break;
	case MDM_R288F_CONF_BPS9600_V33:
		return BPS9600_V33;
		break;
	case MDM_R288F_CONF_BPS7200_V33:
		return BPS7200_V33;
		break;
/** V.17 **/
	case MDM_R288F_CONF_BPS14400_V17:
		return BPS14400_V17;
		break;
	case MDM_R288F_CONF_BPS12000_V17:
		return BPS12000_V17;
		break;
	case MDM_R288F_CONF_BPS9600_V17:
		return BPS9600_V17;
		break;
	case MDM_R288F_CONF_BPS7200_V17:
		return BPS7200_V17;
		break;
/** V.29 **/
	case MDM_R288F_CONF_BPS9600_V29:
		return BPS9600_V29;
		break;
	case MDM_R288F_CONF_BPS7200_V29:
		return BPS7200_V29;
		break;
	case MDM_R288F_CONF_BPS4800_V29:
		return BPS4800_V29;
		break;
/** V.27 ter **/
	case MDM_R288F_CONF_BPS4800_V27:
		return BPS4800_V27;
		break;
	case MDM_R288F_CONF_BPS2400_V27:
		return BPS2400_V27;
		break;
/** V.21 **/
	case MDM_R288F_CONF_BPS0_300_V21:
		return BPS0_300_V21;
		break;
	case MDM_R288F_CONF_BPS300_V21:		/** Channel 2 **/
		return BPS300_V21;
		break;
/** Etc. **/
	case MDM_R288F_CONF_TX_SINGLE_TONE:
		return TX_SINGLE_TONE;
		break;
	case MDM_R288F_CONF_TX_DUAL_TONE:
		return TX_DUAL_TONE;
		break;
	case MDM_R288F_CONF_DIALING:
		return DIALING;
		break;
	case MDM_R288F_CONF_DTMF_RECEIVER:
		return DTMF_RECEIVER;
		break;
/** V.23 **/
	case MDM_R288F_CONF_TX1200_V23: 	/* Tx:1200 Rx:75   */
		return TX1200_V23;
		break;
	case MDM_R288F_CONF_RX1200_V23:
		return RX1200_V23;	/* Tx:75   Rx:1200 */
		break;
	default:
		/* This must not happen. */
		return conf;
		break;
	}
}


/*************************************************************************
	module		:[モデム  インターフェースメモリ  ポートの状態を保持する変数のアドレス取得 ]
	function	:[
		1.
	]
	return		:[UDWORD]
	common		:[]
	condition	:[]
	comment		:[ Inteded to be used in MDM_SetIO() and MDM_SetIO_NewcAfterConf()
					+ これは mdm_io.c の外部からは参照しないでください。
					+ Modem の I/O 周りに変更があったときは、この関数も覗いてください。
	 ]
	ProtoType	:[STATIC UBYTE *MDM_GetPortStatusAddress(CONST struct MDM_I_O_Memory_t *);]
	date		:[1997/07/14]
	author		:[久保 博]
*************************************************************************/
/*
** Get an address where the status of modem port is stored.
** モデムポートの状態を保持するメモリのアドレスを取得する。
** By H.Kubo 1997/07/14
*/

UBYTE *MDM_GetPortStatusAddress(CONST struct MDM_I_O_Memory_t * io_port_ptr)
{
	register UDWORD offset = io_port_ptr->Address - MDM_R288F_BASE_PORT;
	offset >>= 1;	/* Address line is shifted by 1 bit. */
					/* This comes from hardware specification of POPLAR_H.*/
					/* 16bit Bus Width */
	return &MDM_REG_00_PortStatus + offset;
}

/*************************************************************************
	module		:[モデム  インターフェースメモリ NEWC （新規コンフィグレーション）ビットが 0 になるまで待つ]
	function	:[
		1.
	]
	return		:[UDWORD]
	common		:[]
	condition	:[]
	comment		:[ Inteded to be used in MDM_SetIO() and MDM_SetIO_NewcAfterConf()
					+ これは mdm_io.c の外部からは参照しないでください。
	 ]
	ProtoType	:[STATIC void MDM_WaitForNEWC_ToNegate(void);]
	date		:[1997/10/02]
	author		:[久保 博]
*************************************************************************/
UBYTE sfres_bit_status = 0;	/* Add By O.Kimoto 1998/11/16 */

void MDM_WaitForNEWC_ToNegate(UWORD time_count)
{
	UWORD loop = 0;
	UWORD int_enable;

	sfres_bit_status = (UBYTE)(inp(SFRES_PORT) & IO_BIT_SFRES);	/* Add By O.Kimoto 1998/11/16 */
	
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_EnableInterrupt();	/* Add By O.Kimoto 1997/08/13 */

	do {
		loop ++;

		if (sfres_bit_status == 0) {
			/* ＳＡＫＡＫＩのＱＡＴ中に、ソフトリセット＆ＮＥＷＣでＮＥＷＣが落ちず、
			** 下記ＤＳＰＲＡＭで救済しようとしたが
			** 今度はモデムが本当に折ってしまうため、ループしてしまう。
			** よって、ここで直前のモデムのＩ/ＯセットがＳＦＲＥＳの場合は、
			** 所定時間経過してもＮＥＷＣが落ちない場合、
			** ここで、ハードリセットをたたいて強制的にモデムを復旧させます。
			** by O.Kimoto 1998/11/16
			*/
			if (loop >= time_count) {	/** 0x10B9 = 50ms */

#if 0
				/* 1999/09/28 Y.Murata
				 * コネクサント 北瓜氏に確認した所、
				 * ＦＭ３３６では、この処理（ＤＰＳラムアクセス）は行わないでくれとのこと。
				 * 内部アドレスが変更になっているのと、これらを行う必要がないよう変更してるとのこと。
				*/
				outp((UDWORD)0,(UBYTE)0); /* WriteProtectError for ICE */
				/*DspRamAccessWriteMethod1(0x4802,0x02,0xFB);*/
#endif
				/* 復活させます。1999/12/04 Y.M
				** HIIRAGI 受信機、 TAS で 53dBrn のノイズを加えた jpn1 回線で、 
				** V29 9600 からフォールバックすると、最初の V27ter 4800 の TCF 受信時、
				** 高速にコンフィグする処理で NEWC が落ちるのに 2.5 秒かかってしまいます。
				** これを避けるため、やっぱり NEWC が落ちなかったら DSP RAM に書き込みすることに
				** します。
				** by H.Kubo 1999/12/02
				*/
				DspRamAccessWriteMethod1(0x4802,0x02,0xFB);
				break;
			}
		}
		else {
#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
			if (loop >= 0xC800) {	/** おいおい短いやんけ！ 2001/12/07 */
#else
			if (loop >= 0x9000) {	/** 0x9000 = 36ms for SH2 by H.Kubo 1998/11/16 */
#endif
				/************************
				** 強制モデムリセット実行
				************************/
				MDM_ModemHardwareReset();
				if (int_enable) {	/**割り込み禁止に変更時、割り込み許可中だったら*/
					CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
				}
				return;
#ifdef MDM_INT_DMA_BUG_FIX
			}
#else
			}
#endif
		}
	}while (inp(NEWC_PORT) & IO_BIT_NEWC);

	loop = 0xffff;	/**  (Clover で) 約７６５．３ｍｓ **/
	do {
		loop--;
		if (! loop) {
			if (1) { /* FM336PlusNEWC落ちず対策 2002/12/16 T.Takagi (CHK_UNI_IgnoreNEWC_Reset())[ */
				break;
			}
			else {
				outp((unsigned long)0,(UBYTE)0); /* WriteProtectError for ICE */	/**オプションボードをリセットしてください*/
				SaveReturnAddressAndJumpBegin();
				break;
			}
		}
	}while (inp(NEWC_PORT) & IO_BIT_NEWC);

	if (int_enable) {	/**割り込み禁止に変更時、割り込み許可中だったら*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*//* Changed by H.Kubo 1998/03/18 */
	}
}


/*************************************************************************
	module		:[モデム  インターフェースメモリ  書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetIO(unsigned char,unsigned char){}]
	date		:[1995/12/06]
	author		:[木元　修]
*************************************************************************/
void  MDM_SetIO(UBYTE bit_position, UBYTE sw)
{
	UBYTE *port_status_ptr;
	CONST struct MDM_I_O_Memory_t  *mdm_io_memory_ptr;
	
	/*
	** Changed V53 inline asssembler to C by H.Kubo 1997/07/11
	*/
	register UWORD int_enable;	/* variable to hold a flag whether interrupt is enabled.*/
								/* Referred when exit this function. */

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();					/*  By O.Kimoto 1997/08/13 */

	if ( bit_position == POS_CONF ) { 	/* Translate global bps to R288F's CONF value.  Added by H. Kubo 1997/06/19 */
		sw = MDM_BPS_ToR288F_MemBitCONF(sw);
	}

	/*
	** Changed by H.Kubo 1997/07/14
	*/
	mdm_io_memory_ptr = &MDM_I_O_MemoryMap[bit_position];
	port_status_ptr = MDM_GetPortStatusAddress(mdm_io_memory_ptr);
	*port_status_ptr = inp(mdm_io_memory_ptr->Address);
	*port_status_ptr &= ~(mdm_io_memory_ptr->BitPosition);
	
	if (mdm_io_memory_ptr->BitType == SW_TYPE) {
		if(sw == ON) {
			*port_status_ptr |= mdm_io_memory_ptr->BitPosition;
		}
		else { /** sw = OFF **/
			*port_status_ptr &= ~(mdm_io_memory_ptr->BitPosition);
		}
	}
	else {	/** VALUE_TYPE **/
		*port_status_ptr |= sw;
	}
	outp(mdm_io_memory_ptr->Address, *port_status_ptr);

	/*
	** ＮＥＷＣビットがＮｅｇａｔｅされるまで待ちます
	*/
	if (bit_position == POS_NEWC) {
#if (0) /* 50msになるように値を変更 1999/09/20 by K.Okada */
//		MDM_WaitForNEWC_ToNegate(0x10B9);
#else
		MDM_WaitForNEWC_ToNegate(0xC800);
#endif
	}

	/*
	** Changed V53 inline asssembler to C by H.Kubo 1997/07/11
	*/
	if (int_enable) {	/**割り込み禁止に変更時、割り込み許可中だったら*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}
}


/*************************************************************************
	module		:[モデム  インターフェースメモリ  読み出し]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[unsigned char far MDM_GetIO(unsigned char){}]
	date		:[1995/12/06]
	author		:[木元　修]
*************************************************************************/
UBYTE  MDM_GetIO(UBYTE  Bit)
{
	UBYTE return_value;
	UWORD int_enable;
	CONST struct MDM_I_O_Memory_t  *mdm_io_memory_ptr;
	
	mdm_io_memory_ptr = &MDM_I_O_MemoryMap[Bit];
	
	/*
	** Changed V53 inline asssembler to C by H.Kubo 1997/07/11
	*/

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();

	if (mdm_io_memory_ptr->BitType == SW_TYPE) {
		if (inp(mdm_io_memory_ptr->Address) & mdm_io_memory_ptr->BitPosition) {
			return_value = ON;
		}
		else {
			return_value = OFF;
		}
	}
	else {	/** == VALUE_TYPE **/
		return_value = (UBYTE)(inp(mdm_io_memory_ptr->Address) & mdm_io_memory_ptr->BitPosition);
	}

	if ( Bit == POS_CONF ) { /* translate R288F's CONF value to global bps. Added by H. Kubo 1997/06/19 */
		MDM_TrueConfValue = return_value;	/** Add By O.Kimoto 1997/12/02 */
		return_value = MDM_R288F_MemBitCONF_ToBPS(return_value);
	}

	/*
	** Changed V53 inline asssembler to C by H.Kubo 1997/07/11
	*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}

	return(return_value);
}


/*************************************************************************
	module		:[Flip ORG bit]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043,V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void far MDM_FlipAnsOrg(void){}]
	date		:[1996/06/26]
	author		:[木元修]
*************************************************************************/
void  MDM_FlipAnsOrg(void)
{
	register UBYTE reg_org_value;

	reg_org_value = MDM_GetIO(POS_ORG);
	if (reg_org_value & ON) {
		MDM_SetIO(POS_ORG,OFF);
	}
	else {
		MDM_SetIO(POS_ORG,ON);
	}
}

/*************************************************************************
	module		:[モデム  インターフェースメモリ  書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_SetIO_NewcAfterConf(unsigned char,unsigned char, UWORD){}]
	date		:[1997/02/07]
	author		:[木元　修]
*************************************************************************/
void MDM_SetIO_NewcAfterConf(UBYTE bit_position,UBYTE  sw, UWORD time_count)
{

	UWORD int_enable;
	register CONST struct MDM_I_O_Memory_t  *mdm_io_memory_ptr;
	register UBYTE *port_status_ptr;

	/*
	** Changed V53 inline asssembler to C by H.Kubo 1997/07/11
	*/

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/* Add By O.Kimoto 1997/08/13 */

  /** changed by H.Kubo 1997/07/14 **/
	mdm_io_memory_ptr = &MDM_I_O_MemoryMap[bit_position];
	port_status_ptr = MDM_GetPortStatusAddress(mdm_io_memory_ptr);

	*port_status_ptr = inp(mdm_io_memory_ptr->Address);
	*port_status_ptr &= ~(mdm_io_memory_ptr->BitPosition);
  /** end of change by H.Kubo **/

	if (mdm_io_memory_ptr->BitType == SW_TYPE) {
		if(sw == ON) {
			*port_status_ptr |= mdm_io_memory_ptr->BitPosition;
		}
		else { /** sw = OFF **/
			*port_status_ptr &= ~(mdm_io_memory_ptr->BitPosition);
		}
	}
	else {	/** VALUE_TYPE **/
		*port_status_ptr |= sw;
	}
	outp(mdm_io_memory_ptr->Address,*port_status_ptr);

	/*
	** ＮＥＷＣビットがＮｅｇａｔｅされるまで待ちます
	*/
	if (bit_position == POS_NEWC) {
		MDM_WaitForNEWC_ToNegate(time_count);
	}

	/*
	** V53 inline asssembler is changed to C by H.Kubo 1997/07/11
	*/
	if (int_enable) {	/**割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}

}


#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/09 */
/*************************************************************************
	module		:[FM336 モデムをチェックします]
	function	:[
			モデムのバージョンをモデムから吸い出します。
			モデムのバージョンを SYS_ModemVersion に代入します。
	]
	return		:[]
	common		:[
			SYS_ModemVersion
	]
	condition	:[
			MAN_MainTask で呼ばれることを想定しています。
	]
	comment		:[
			SYS_ModemVersion に正しい値が設定されていないと、
			モデムが正常に動作しません。モデムを実際に通信で使う前に、
			この関数を呼んでください。
			手順は、"R288F V.34 Fax/V.17 Fax Modem Designer's Guide" 4.10節 に従っています。
	]
	machine		:[V43, SH7043]
	language	:[MS-C(Ver.6.0), SHC]
	keyword		:[modem, version ]
	date		:[1999/04/09]
	author		:[久保]
*************************************************************************/
#if 0
#define MDM_FM336_SUPPORT_VERSION_MAX 1
@ CONST UWORD MDM_FM336_RAM1_Checksum[MDM_FM336_SUPPORT_VERSION_MAX] = {0x0451};
@ CONST UWORD MDM_FM336_RAM2_Checksum[MDM_FM336_SUPPORT_VERSION_MAX] = {0x495A};
@ CONST UBYTE MDM_FM336_DebugSwitch = 0;
#endif
UBYTE MDM_InitializeFm336ModemCheck(void)
{
	UWORD i;
	UWORD time10_count;
	UWORD reg1b1a = 0;
	UWORD reg1d1c = 0;
	UBYTE tmp_reg;
	UBYTE tmp_reg12 = 0;
	UBYTE tmp_reg13 = 0;


	SYS_ModemVersion = 0;

	MDM_SetIO(POS_SFRES,ON);			/* モデムソフトリセット */

	tmp_reg = inp(MDM_REG_1F_PORT);
	tmp_reg |= IO_BIT_NEWC;
	outp(MDM_REG_1F_PORT,tmp_reg);

	
#if 0
@	time10_count = 0xffff;
@	while (time10_count--) {
@		reg1b1a = (inp(MDM_REG_1B_PORT) << 8) | inp(MDM_REG_1A_PORT);
@		reg1d1c = (inp(MDM_REG_1D_PORT) << 8) | inp(MDM_REG_1C_PORT);
@		for (i = 0; i < MDM_FM336_SUPPORT_VERSION_MAX; i++) {
@			if (((MDM_FM336_RAM1_Checksum[i] == reg1d1c) && (MDM_FM336_RAM2_Checksum[i] == reg1b1a))
@			 || MDM_FM336_DebugSwitch) {
@				break;
@			}
@		}
@		if (i < MDM_FM336_SUPPORT_VERSION_MAX) {
@			/* OK. ready to read modem part number. */
@			tmp_reg13 = inp(MDM_REG_13_PORT);
@			tmp_reg12 = inp(MDM_REG_12_PORT);
@			SYS_ModemVersion = (UBYTE)(((tmp_reg13-0x30)*0x10)+(tmp_reg12-0x30));
@			(void) inp(MDM_REG_10_PORT); /* clear 1E:3 */
@			break;
@		}
@	}
#else
	time10_count = 0xffff;
	while ((tmp_reg13 & 0xf0) != 0x30) {
		tmp_reg13 = inp(MDM_REG_13_PORT);
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	time10_count = 0xffff;
	while ((tmp_reg12 & 0xf0) != 0x30) {
		tmp_reg12 = inp(MDM_REG_12_PORT);
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	tmp_reg13 = inp(MDM_REG_13_PORT);
	tmp_reg12 = inp(MDM_REG_12_PORT);
	SYS_ModemVersion = (UBYTE)(((tmp_reg13-0x30)*0x10)+(tmp_reg12-0x30));
	(void) inp(MDM_REG_10_PORT); /* clear 1E:3 */

#endif

	/* Wait for NEWC to be 0 */
	time10_count = 0xffff;
	while((inp(MDM_REG_1F_PORT) & IO_BIT_NEWC) == IO_BIT_NEWC) {
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}
	wai_tsk(40);
	/* ﾓﾃﾞﾑｿﾌﾄﾘｾｯﾄを行っているので、その終了をまつためのｳｴｲﾄ */

	if (SYS_ModemVersion > 0x80) {
		return 1;
	}
	else {
		if ((SYS_ModemVersion & 0xf0) != 0x50) {
			SYS_ModemVersion = MDM_L6713_26P; /* 0x57 */
		}
		return 0;
	}
}
#endif

/*************************************************************************
	module		:[モデムをチェックします]
	function	:[
			モデムのバージョンをモデムから吸い出します。
			モデムのバージョンを SYS_ModemVersion に代入します。
	]
	return		:[]
	common		:[
			SYS_ModemVersion
	]
	condition	:[
			MAN_MainTask で呼ばれることを想定しています。
	]
	comment		:[
			SYS_ModemVersion に正しい値が設定されていないと、
			モデムが正常に動作しません。モデムを実際に通信で使う前に、
			この関数を呼んでください。
	]
	machine		:[V43, SH7043]
	language	:[MS-C(Ver.6.0), SHC]
	keyword		:[modem, version ]
	date		:[1996/02/01]
	update		:[1997/11/05 by H.Kubo]
	author		:[村田]
*************************************************************************/
UBYTE cmn_tmp_reg12 = 0;
UBYTE cmn_tmp_reg13 = 0;

void MDM_InitializeModemCheck(void)
{
	UWORD time10_count;
	UBYTE tmp_reg;

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/09 */
	if (MDM_InitializeFm336ModemCheck()) {
		return; /* Success to read FM336 PartNumber. */
	}
#endif
	SYS_ModemVersion = 0;
	cmn_tmp_reg13 = 0;
	cmn_tmp_reg12 = 0;

	MDM_SetIO(POS_SFRES,ON);			/* モデムソフトリセット */

	tmp_reg = inp(MDM_REG_1F_PORT);
	tmp_reg |= IO_BIT_NEWC;
	outp(MDM_REG_1F_PORT,tmp_reg);

	time10_count = 0xffff;
	while((inp(MDM_REG_1F_PORT) & 0x80) == 0x80) {
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	time10_count = 0xffff;
	while((inp(MDM_REG_1E_PORT) & 0x08) == 0x00) {
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	time10_count = 0xffff;
	while ((cmn_tmp_reg13 & 0xf0) != 0x30) {
		cmn_tmp_reg13 = inp(MDM_REG_13_PORT);
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	time10_count = 0xffff;
	while ((cmn_tmp_reg12 & 0xf0) != 0x30) {
		cmn_tmp_reg12 = inp(MDM_REG_12_PORT);
		time10_count --;
		if (time10_count == 0) {
			break;
		}
		/* wai_oneshot(1); */		/* For DEBUG By O.Kimoto 1998/01/16 */
	}

	SYS_ModemVersion = (UBYTE)(((cmn_tmp_reg13-0x30)*0x10)+(cmn_tmp_reg12-0x30));

	if ((SYS_ModemVersion & 0xf0) != 0x50) {
		SYS_ModemVersion = 0x52; /* L6713-13P */
	}

	time10_count = 0;
	
	wai_tsk(40);	/* 400ms wait 1997/08/04 Y.Murata */
	/* ﾓﾃﾞﾑｿﾌﾄﾘｾｯﾄを行っているので、その終了をまつためのｳｴｲﾄ */


}


#if (0) /* For test */
** void MDM_TestIO(void)
** {
** 	register int addr;
** 	register int data;
** 	addr = POS_VOLUME;
** 	data = VOLUME_LARGE;
** 	MDM_SetIO(addr, data);
** 	data = MDM_GetIO(addr);
** 	data = data & data;
** 	data = data | data;
** }
** 
** void MDM_TestTxFskOpen(void)
** {
** 	register UBYTE flag = OFF;
** 	TxFskOpen();
** 	do {
** 		flag = MDM_GetIO(POS_RTDIS);
** 		if (flag != OFF ) break;
** 		if (MDM_GetIO(POS_ASYN) != OFF ) break;
** 		if (MDM_GetIO(POS_TPDM) != ON ) break;
** 		if (MDM_GetIO(POS_HDLC) != ON ) break;
** 		if (MDM_GetIO(POS_DATA) != ON ) break;
** 		if (MDM_GetIO(POS_TXSQ) != ON ) break;
** 		if (MDM_GetIO(POS_FIFOEN) != ON ) break;
** 		if (MDM_GetIO(POS_RTS) != ON ) break;
** 		if (MDM_GetIO(POS_NSIE) != ON ) break;
** 		wai_tsk(0xffff);
** 	} while (0);
** 
** 	wai_tsk(0xffff);
** 
** }
** 
#endif /* 0 */
