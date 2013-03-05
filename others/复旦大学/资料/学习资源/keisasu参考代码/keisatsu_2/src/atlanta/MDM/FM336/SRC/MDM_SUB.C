/*---------------------------------------------------------------------------------------*/
/*  ƒvƒƒWƒFƒNƒg : POPLAR_F                                                              */
/*  ƒtƒ@ƒCƒ‹–¼   : mdm_sub.c                                                             */
/*  ì¬Ò       :                                                                       */
/*  “ú  •t       : 1999/10/06                                                            */
/*  ŠT  —v       : ƒ‚ƒfƒ€ƒZƒbƒgƒAƒbƒvˆ—                                                */
/*  C³—š—ğ     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\sh7043\define\def_evtn.h" /* added by H.Kubo 1998/01/29 */

#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"		/* 1996/12/10 Y.M */
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\scn_pro.h"		/* ’Ç‰Á S.Fukui Jun.1,1999 */

/*******
** ext_v
*******/
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h" /* Added by H.Kubo 1997/0708 */
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\dma_data.h" /* added by H.Kubo 1998/01/29 */

/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒ[ƒN—Ìˆæ‰Šú‰»]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void 	InitializeModemWork(void)
{
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);		/**	ƒ‚ƒfƒ€ƒRƒ“ƒgƒ[ƒ‹ƒGƒŠƒA‰Šú‰»	*/
	SetClear((UBYTE *)MDM_RxSize, (sizeof(UWORD) * MODEM_BUFFER_MAX), 0x00);
	ModemWaitStatus = 0;
}


/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘Œ¹Šl“¾]
	function	:[
		1.w’è‚³‚ê‚½ƒ‚ƒfƒ€ƒoƒbƒtƒ@‚Ì‘Œ¹i‚O`‚Vj‚ğŠl“¾‚µ‚Ü‚·B
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void			ModemBufferWaiSem(UBYTE	buf_num)
{
	wai_sem(semno.ModemBuffer[buf_num]);
}


/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘Œ¹‰ğ•ú]
	function	:[
		1.w’è‚³‚ê‚½ƒ‚ƒfƒ€ƒoƒbƒtƒ@‚Ì‘Œ¹i‚O`‚Vj‚ğ‰ğ•ú‚µ‚Ü‚·B
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void			ModemBufferSigSem(UBYTE	buf_num)
{
/* Œ´ˆö‚Í‚í‚©‚Á‚Ä‚¢‚Ü‚¹‚ñ‚ªA‚o‚n‚o‚k‚`‚qQ‚a‚Å‚àSIG_SEM‚ÅƒŠƒZƒbƒg‚É”ò‚Ô‚Æ‚¢‚¤•s‹ï‡‚Å‚Ä‚¨‚èA
** ‚±‚Ì‘Îô‚ª{‚³‚ê‚Ä‚¢‚Ü‚·‚Ì‚Å‚o‚n‚o‚k‚`‚qQ‚g‚Å‚à‚¢‚ê‚Ü‚·
** 1998/03/27 by T.Soneoka */
	if (chk_semvl(semno.ModemBuffer[buf_num]) == 0) {
		sig_sem(semno.ModemBuffer[buf_num]);
	}
}

/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@ƒZƒ}ƒtƒHİ’è]
	function	:[
		1.w’è‚³‚ê‚½ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘Œ¹i‚O`‚Vj‚ğƒZƒ}ƒtƒHİ’è‚µ‚Ü‚·B
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void	CreateModemBufferSem(void)
{
	UBYTE	i;

	for (i=0; i<MODEM_BUFFER_MAX; i++) {
		cre_sem(&semno.ModemBuffer[i]);
	}
}

/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@ƒŠƒZƒbƒg]
	function	:[
		1.w’è‚³‚ê‚½ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘Œ¹i‚O`‚Vj‚ğŠl“¾‚µAŠJ•ú‚µ‚Ü‚·
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void			ResetModemBufferSem(void)
{
	UBYTE	i;

	for (i=0; i<MODEM_BUFFER_MAX; i++) {
		chk_sem(semno.ModemBuffer[i]);
		sig_sem(semno.ModemBuffer[i]);
	}
}

/*************************************************************************
	module		:[]
	function	:[
		1.ƒ\[ƒXƒf[ƒ^”‚©‚çw’èƒf[ƒ^”‚ğæ‚ê‚é‚©
		2.w’èƒf[ƒ^‚ğŠl“¾‚Å‚«‚½‚ÍAw’èƒf[ƒ^”‚ğ–ß‚è’l‚Æ‚µ‚Äİ’è
		3.Šl“¾‚Å‚«‚È‚©‚Á‚½‚ÍAƒ\[ƒXƒf[ƒ^”‚ğ–ß‚è’l‚Æ‚µ‚Äİ’è
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/08]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UWORD 	GetCount(UDWORD src_cnt,UWORD cnt)
{
	if (src_cnt >= (UDWORD)cnt) {
		return (cnt);
	}
	else {
		return ((UWORD)src_cnt);
	}
}


/*************************************************************************
	module		:[ƒNƒŠƒA]
	function	:[
		1.ƒ^[ƒQƒbƒgƒGƒŠƒA‚ğƒNƒŠƒA‚µ‚Ü‚·
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/08]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void SetClear(register UBYTE *buf,UWORD	cnt,UBYTE set_num)
{
	while (cnt--) {
		*buf++ = set_num;
	}
}


/*************************************************************************
	module		:[‘—oƒoƒCƒg”İ’è]
	function	:[
		1.@‘—M‘¬“x‚É‰‚¶‚ÄA‘—oƒoƒCƒg”‚ğİ’è‚·‚é
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/08]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UWORD 	SetTransmitCount(
UWORD time)		/**	‘—oŠÔ(’PˆÊ‚‚“j	*/
{
	UWORD	cnt;
	/*--------------------------------------------------------------*/
	/* ‘—oÊŞ²Ä”@‚P.5•bŠÔ											*/
	/* rate: 2400bps, 4800bps, 7200bps, 9600bps, 12000bps, 14400bps */
	/* byte:     450,     900,    1350,    1800,     2250,     2700 */
	/*--------------------------------------------------------------*/
	/* 2400bps = 2400/8(byte/s) = 300(byte/s) */
	/*----------------------------------------*/

	cnt = ( 3*time )/10;

	switch ( ModemBlock.Speed ) {
	case SPEED_33600:
		cnt = cnt*14;
		break;
	case SPEED_31200:
		cnt = cnt*13;
		break;
	case SPEED_28800:
		cnt = cnt*12;
		break;
	case SPEED_26400:
		cnt = cnt*11;
		break;
	case SPEED_24000:
		cnt = cnt*10;
		break;
	case SPEED_21600:
		cnt = cnt*9;
		break;
	case SPEED_19200:
		cnt = cnt*8;
		break;
	case SPEED_16800:
		cnt = cnt*7;
		break;
	case SPEED_14400:
		cnt = cnt*6;
		break;
	case SPEED_12000:
		cnt = cnt*5;
		break;
	case SPEED_9600:
		cnt = cnt*4;
		break;
	case SPEED_7200:
		cnt = cnt*3;
		break;
	case SPEED_4800:
		cnt = cnt*2;
		break;
	case SPEED_2400:
		break;
	case SPEED_300:
		cnt = cnt/8;	/*	¬”“_ˆÈ‰ºØ‚èÌ‚Ä	*/
		break;
	}

	if ( ModemBlock.Mode == MODE_RX_TCF ) {
		switch ( ModemBlock.Speed ) {
		case SPEED_14400:
			if ( cnt < MDM_TCF_MIN_14400BPS ) {
				cnt = MDM_TCF_MIN_14400BPS;
			}
			else if ( cnt > MDM_TCF_MAX_14400BPS ) {
				cnt = MDM_TCF_MAX_14400BPS;
			}
			break;
		case SPEED_12000:
			if ( cnt < MDM_TCF_MIN_12000BPS ) {
				cnt = MDM_TCF_MIN_12000BPS;
			}
			else if ( cnt > MDM_TCF_MAX_12000BPS ) {
				cnt = MDM_TCF_MAX_12000BPS;
			}
			break;
		case SPEED_9600:
			if ( cnt < MDM_TCF_MIN_9600BPS ) {
				cnt = MDM_TCF_MIN_9600BPS;
			}
			else if ( cnt > MDM_TCF_MAX_9600BPS ) {
				cnt = MDM_TCF_MAX_9600BPS;
			}
			break;
		case SPEED_7200:
			if ( cnt < MDM_TCF_MIN_7200BPS ) {
				cnt = MDM_TCF_MIN_7200BPS;
			}
			else if ( cnt > MDM_TCF_MAX_7200BPS ) {
				cnt = MDM_TCF_MAX_7200BPS;
			}
			break;
		case SPEED_4800:
			if ( cnt < MDM_TCF_MIN_4800BPS ) {
				cnt = MDM_TCF_MIN_4800BPS;
			}
			else if ( cnt > MDM_TCF_MAX_4800BPS ) {
				cnt = MDM_TCF_MAX_4800BPS;
			}
			break;
		case SPEED_2400:
			if ( cnt < MDM_TCF_MIN_2400BPS ) {
				cnt = MDM_TCF_MIN_2400BPS;
			}
			else if ( cnt > MDM_TCF_MAX_2400BPS ) {
				cnt = MDM_TCF_MAX_2400BPS;
			}
			break;
		default:
			break;
		}
	}
	return ( cnt );
}


/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘‚«‚İˆÊ’uXVˆ—]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void NextMdmBufWritePointSetExtRom(void)
{
	UBYTE debug;	/* debug */

	ModemControl.WritePoint++;									/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘‚«‚İˆÊ’uXV	*/
	if (ModemControl.WritePoint == MODEM_BUFFER_MAX) {			/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘‚«‚İˆÊ’u‚ª‚e‚t‚k‚k	*/
#if (PRO_CLASS1 == ENABLE) /* added by H.Kubo 1998/03/04 */
		ModemControl.WritePoint = MDM_ModemBufferFirstPoint;
#else
		ModemControl.WritePoint = 0;							/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@‘‚«‚İˆÊ’u‚ğæ“ª‚Éİ’è	*/
#endif
	}

/* debug 1997/03/22 Y.M */
	if (ModemControl.WritePoint == ModemControl.ReadPoint) {
		debug++;
	}
}


/*************************************************************************
	module		:[ƒ‚ƒfƒ€ƒoƒbƒtƒ@“Ç‚İo‚µˆÊ’uXVˆ—]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void NextMdmBufReadPointSetExtRom(void)
{
	ModemControl.ReadPoint++;									/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@“Ç‚İo‚µˆÊ’uXV	*/
	if (ModemControl.ReadPoint == MODEM_BUFFER_MAX) {			/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@“Ç‚İo‚µˆÊ’u‚ª‚e‚t‚k‚k	*/
#if (PRO_CLASS1 == ENABLE) /* added by H.Kubo 1998/03/04 */
		ModemControl.ReadPoint = MDM_ModemBufferFirstPoint;
#else
		ModemControl.ReadPoint = 0;								/**	ƒ‚ƒfƒ€ƒoƒbƒtƒ@“Ç‚İo‚µˆÊ’u‚ğæ“ª‚Éİ’è	*/
#endif
	}
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€“]‘—ƒ‹[ƒ`ƒ“]
	function	:[
		1.“]‘—Œ³‚ÌƒAƒhƒŒƒX‚Æ“]‘—æ‚ÌƒAƒhƒŒƒX‹y‚Ñ“]‘—ƒoƒCƒg”‚ğ“ü—Í
		2.“]‘—ƒoƒCƒg”•ªAŠeƒAƒhƒŒƒX‚ğƒCƒ“ƒNƒŠƒƒ“ƒg‚µ‚È‚ª‚çAƒRƒs[‚·‚é
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/13]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void MemoryMove(
register UBYTE	*tgt_adr,
register UBYTE	*src_adr,
UWORD	cnt)
{
	while (cnt--) {
		*tgt_adr++ = *src_adr++;
	}
}

/*
** ‚±‚ÌŠÖ”‚Íg—p‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚ÅAíœ‚µ‚Ü‚·Bg—p‚·‚é‚±‚Æ‚ª‚ ‚ê‚Î•œŠˆ‚µ‚Ä‚­‚¾‚³‚¢
** ƒtƒ‰ƒbƒVƒ…ƒvƒƒOƒ‰ƒ€“‹Ú‚É‚¨‚¢‚ÄAƒvƒƒOƒ‰ƒ€—Ìˆæß–ñ‚Ì‚½‚ß
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[ƒvƒƒOƒ‰ƒ€“]‘—ƒ‹[ƒ`ƒ“ƒoƒCƒgƒXƒƒbƒv]
//	function	:[
//		1.“]‘—Œ³‚ÌƒAƒhƒŒƒX‚Æ“]‘—æ‚ÌƒAƒhƒŒƒX‹y‚Ñ“]‘—ƒoƒCƒg”‚ğ“ü—Í
//		2.“]‘—ƒoƒCƒg”•ªAŠeƒAƒhƒŒƒX‚ğƒCƒ“ƒNƒŠƒƒ“ƒg‚µAƒoƒCƒg‚ÅŒğŠ·‚µ‚È‚ª‚çƒRƒs[‚·‚é
//	]
//	return		:[‚È‚µ]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	date		:[1997/03/07]
//	author		:[‘]ª‰ª‘ñ]
//*************************************************************************/
//void MemoryMoveSwap(
//register UBYTE	*tgt_adr,
//register UBYTE	*src_adr,
//WORD	cnt)
//{
//	while (cnt > 0) {
//		*tgt_adr = *(src_adr+1);
//		*(tgt_adr+1) = *src_adr;
//		tgt_adr += 2;
//		src_adr += 2;
//		cnt -= 2;
//	}
//}
#endif
/*************************************************************************
	module		:[‚d‚b‚lƒtƒŒ[ƒ€ƒXƒe[ƒ^ƒXƒ`ƒFƒbƒN]
	function	:[
		1.ƒtƒŒ[ƒ€”Ô†‚O`‚Q‚T‚T‚Ü‚Å“ü—Í
		2.ŠY“–”z—ñ‚ÌŠY“–ƒrƒbƒg‚ª—LŒø‚©‚Ç‚¤‚©‚ğŒ©‚éi—LŒøF‚OC–³ŒøF‚Pj
	]
	return		:[
		0:	‚d‚b‚lƒXƒe[ƒ^ƒX—LŒøiÄ‘—•s•K—vj
		1:	‚d‚b‚lƒXƒe[ƒ^ƒX–³ŒøiÄ‘—•K—vj
	]
	common		:[]
	condition	:[]
	comment		:[
		“ü—Í‚Í‚O`‚Q‚T‚T‚Ü‚Å
	]
	date		:[1994/01/13]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UBYTE	CheckEcmStatusExtRom(UWORD	frm_num)	/*	ƒtƒŒ[ƒ€”Ô†i‚O`‚Q‚T‚Tj	*/
{
	UBYTE	quo;		/**	ƒtƒŒ[ƒ€”Ô†‚O`‚R‚P	*/
	UBYTE	rem;		/**	ŠY“–ƒVƒtƒg”	*/
	UBYTE	chk_bit;	/**	ŠY“–ƒrƒbƒg	*/

	quo = 0;
	rem = 0;

	if (frm_num != 0) {
		quo = (UBYTE)(frm_num/8);			/**	ƒtƒŒ[ƒ€”Ô†İ’è	*/
		rem = (UBYTE)(frm_num%8);			/**	ƒVƒtƒg”İ’è	*/
	}
	chk_bit = (UBYTE)(1<<rem);				/**	ŠY“–ƒrƒbƒgİ’è	*/

	if (MDM_EcmStatus[quo] & chk_bit) {		/**	‚d‚b‚lƒtƒŒ[ƒ€ƒXƒe[ƒ^ƒXƒ`ƒFƒbƒN	*/
		return (1);
	}
	else {
		return (0);
	}
}


/*************************************************************************
	module		:[‚d‚b‚lƒtƒŒ[ƒ€ƒXƒe[ƒ^ƒX—LŒøƒZƒbƒgƒ‹[ƒ`ƒ“]
	function	:[
		1.ŠY“–ƒtƒŒ[ƒ€”Ô†‚ğ“ü—Í‚O`‚Q‚T‚T
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/14]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void 	EnableEcmStatus(UBYTE	num)
{
	MDM_EcmStatus[((UBYTE)(num)>>3)] &= ~(0x01 << ((num) & 0x07));
}

/*************************************************************************
	module		:[‚g‚c‚k‚bóMƒtƒŒ[ƒ€ƒTƒCƒYŠl“¾]
	function	:[
		1.
	]
	return		:[
		‚È‚µ
	]
	common		:[]
	condition	:[Š„‚è‚İ‚©‚ç‚ÌƒR[ƒ‹‚Ég—p‚µ‚Ü‚·]
	comment		:[
		‚e‚r‚jóM
		bƒAƒhƒŒƒXbƒRƒ“ƒgƒ[ƒ‹b‚e‚b‚eb‚e‚h‚eEEEb‚e‚b‚rb‚e‚b‚rb
		bƒ||||||||||||||||||||„b
		‚d‚b‚lóM
		bƒAƒhƒŒƒXbƒRƒ“ƒgƒ[ƒ‹b‚e‚b‚ei‚e‚b‚c^‚q‚b‚ojb‚e‚h‚eiƒtƒŒ[ƒ€ƒiƒ“ƒo[^ƒf[ƒ^jb‚e‚b‚rb‚e‚b‚rb
		bƒ||||||||||||||||||||||||||||||||||||||||||||||||„b
	]
	date		:[1994/01/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void GetRxSize(UBYTE	pnt)
{
	UWORD	cnt;		/**	‚c‚l‚`“]‘—‰ñ”	*/

	cnt = DMA_CheckDMA_Counter(DMA_CH_RX); /* Modified by H. Kubo for POPLAR_H	1997/06/17 */
	/*------------------*/
	/**	‚e‚r‚jóM	*/
	/*------------------*/
	if (ModemBlock.Mode == MODE_RX_FSK) {
		cnt = RX_FSK_HDLC_LENGTH - cnt;

		/*
		** R288F VERSION 24PˆÈ~‚Ìê‡
		** added by H.Kubo 1998/10/07
		** Changed by H.Kubo 1998/10/07
		*/
		if (MDM_ModemBuffer[ModemControl.WritePoint][cnt-1] != 0x7E) { /* óMƒf[ƒ^‚ÌÅŒã‚ªƒtƒ‰ƒO‚Å‚È‚©‚Á‚½‚çA*/
			if (cnt >= 2) {
				cnt-=2; /* ‚e‚b‚r•ª2ƒoƒCƒgˆø‚­B */
			}
		}
		else {
			if (cnt >= 3) {
				cnt -= 3;	/**	ƒtƒ‰ƒO‚Æ‚e‚b‚r•ª3ƒoƒCƒgˆø‚­	*/
			}
		}

	}
	/*------------------*/
	/**	‚d‚b‚lóM	*/
	/*------------------*/
	else if (ModemBlock.Mode == MODE_RX_ECM) {	/**	‚d‚b‚lóM‚Ì	*/
		cnt = (FcomEcmSize + MODEM_FRAMING_CODE_LENGTH + 1) - cnt;
	}
	MDM_RxSize[ModemControl.WritePoint] = cnt;
}


/*************************************************************************
	module		:[óMƒ‚ƒfƒ€ƒoƒbƒtƒ@‚g‚c‚k‚b•â³]
	function	:[
		1.
	]
	return		:[
		OK:	ƒ‚ƒfƒ€ƒoƒbƒtƒ@ÄƒZƒbƒg‚n‚j
		NG:	ƒAƒhƒŒƒXƒtƒB[ƒ‹ƒh‚È‚µ
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/13]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UBYTE 	ModemBufferFormatControl(UBYTE point)
{
	UWORD	i;
	UBYTE	rtn;

	rtn = OK;
	for (i = 0;	i < MODEM_BUFFER_LENGTH; i++) {
		if ((MDM_ModemBuffer[point][i] == 0xff) &&
		    (MDM_ModemBuffer[point][i+1] == 0x13 || MDM_ModemBuffer[point][i+1] == 0x03)) {
			break;
		}
	}
	if (i >= MODEM_BUFFER_LENGTH) {
		MDM_RxSize[point] = 0;
		return (NG);
	}
	if (i > 0) {
		if (((MDM_RxSize[point]-i) <= (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)) &&	/**  By O.K Jan.23,1996 **/
	 		((MDM_RxSize[point]-i) > 0)) {
			MemoryMove(&MDM_ModemBuffer[point][0],
				&MDM_ModemBuffer[point][i],
					(MDM_RxSize[point]-i));
			MDM_RxSize[point]-=i;
		}
	}
	return (OK);
}


/*
** ‚±‚ÌŠÖ”‚Íg—p‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚ÅAíœ‚µ‚Ü‚·Bg—p‚·‚é‚±‚Æ‚ª‚ ‚ê‚Î•œŠˆ‚µ‚Ä‚­‚¾‚³‚¢
** ƒtƒ‰ƒbƒVƒ…ƒvƒƒOƒ‰ƒ€“‹Ú‚É‚¨‚¢‚ÄAƒvƒƒOƒ‰ƒ€—Ìˆæß–ñ‚Ì‚½‚ß
** 1998/04/10
*/
#if (0)
///*************************************************************************
//	module		:[Å¬“`‘—ŠÔİ’è]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	date		:[1994/02/14]
//	author		:[‘]ª‰ª‘ñ]
//*************************************************************************/
//UBYTE		SetMinimumScanningTime(
//UBYTE time_num)
//{
//	UBYTE	rtn;
//
//	switch (time_num) {
//	case SCAN_MINIMUM_TIME20   :
//	case SCAN_MINIMUM_TIME20_2 :
//		rtn = 20;
//		break;
//	case SCAN_MINIMUM_TIME40   :
//	case SCAN_MINIMUM_TIME40_2 :
//		rtn = 40;
//		break;
//	case SCAN_MINIMUM_TIME10   :
//	case SCAN_MINIMUM_TIME10_2 :
//		rtn = 10;
//		break;
//	case SCAN_MINIMUM_TIME5    :
//		rtn = 5;
//		break;
//	case SCAN_MINIMUM_TIME0    :
//	default:
//		rtn = 0;
//		break;
//	}
//	return (rtn);
//}
#endif

/*************************************************************************
	module		:[‘—M‰æƒf[ƒ^k¬•ÏŠ·—¦İ’è]
	function	:[
		1.’~ÏŒ´eƒTƒCƒY^ƒ‚[ƒh‚Æ‘—MŒ´eƒTƒCƒY^ƒ‚[ƒh^ƒCƒ“ƒ`ƒ~ƒŠŒn‚ğ
		@”»’f‚µA‚l‚m‚W‚U‚O‚U‚R‚Ìk¬—¦ƒpƒ‰ƒ[ƒ^i”CˆÓk¬E×ü•Ûƒ‚[ƒhj‚ğŒˆ’è‚·‚éB
	]
	return		:[‚È‚µ]
	common		:[
		SYS_DocBlock.Src.Mode
		SYS_DocBlock.Src.Size
		SYS_DocBlock.Dst.Mode
		SYS_DocBlock.Dst.Size
		SYS_DocBlock.ModeMethod
		Pix_H_Reduction
		Pix_V_Reduction
		TxReductionInchA4_DocTable[][]
		TxReductionMetricA4_DocTable[][]
		TxReductionInchB4_DocTable[][]
		TxReductionMetricB4_DocTable[][]
		TxReductionInchA3_DocTable[][]
		TxReductionMetricA3_DocTable[][]
	]
	condition	:[]
	comment		:[
		İ’è’l‚ÍAƒ‚ƒfƒ€‚Ì‘—M‰æƒf[ƒ^k¬—¦•ÏŠ·‚ÌİŒvd—l‘‚ğQÆ‚µ‚Ä‚­‚¾‚³‚¢
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1994/03/11]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
#define	TX_NORM_POSI		0
#define	TX_FINE_POSI		2
#define TX_SFINE_POSI		4
#define	TX_HFINE_POSI		6
#define TX_UFINE_INCH_POSI	8 /* 600dpi~600dpi‘Î‰ 1999/05/26 by K.Okada */

/******************************************
** 600dpi~600dpi‘Î‰ 1999/05/26 by K.Okada
******************************************/
#define MEM_A4_POSI			0
#define	MEM_B4_POSI			5
#define MEM_A3_POSI			10

#define	MEM_NORM_POSI		0
#define	MEM_FINE_POSI		1
#define	MEM_SFINE_POSI		2
#define	MEM_HFINE_POSI		3
#define MEM_UFINE_INCH_POSI	4 /* 600dpi~600dpi‘Î‰ 1999/05/26 by K.Okada */

UBYTE	TxPixReductionSet(
UBYTE	src_size,
UBYTE	src_mode,
UBYTE	dst_size,
UBYTE	dst_mode,
UBYTE	mode_method)
{

	UWORD	table_locate_x;
	UWORD	table_locate_y;

	Pix_H_Reduction = 0;
	Pix_V_Reduction = 0;

	/*----------------------------------*/
	/*	k¬—¦‘I‘ğƒe[ƒuƒ‹‚w²İ’èˆ—	*/
	/*----------------------------------*/
	switch (dst_mode) {		/**	‘—MŒ´eƒ‚[ƒh	*/
	case	SYS_NORMAL:	/**	‘—MŒ´eƒ‚[ƒh‚ª‚m‚‚’‚‚Ì	*/
		table_locate_x = TX_NORM_POSI;
		break;
	case	SYS_FINE:	/**	‘—MŒ´eƒ‚[ƒh‚ª‚e‚‰‚‚…‚Ì	*/
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		table_locate_x = TX_FINE_POSI;
		break;
	case	SYS_SFINE:	/**	‘—MŒ´eƒ‚[ƒh‚ª‚r‚†‚‰‚‚…‚Ì	*/
		table_locate_x = TX_SFINE_POSI;
		break;
	case	SYS_HFINE:	/**	‘—MŒ´eƒ‚[ƒh‚ª‚g‚†‚‰‚‚…‚Ì	*/
		table_locate_x = TX_HFINE_POSI;
		break;
	case	SYS_UFINE: /* 600dpi~600dpi‘Î‰ 1999/05/26 by K.Okada */
		table_locate_x = TX_UFINE_INCH_POSI;
		break;
	}
	/*----------------------------------*/
	/*	k¬—¦‘I‘ğƒe[ƒuƒ‹‚x²İ’èˆ—	*/
	/*----------------------------------*/
	switch (src_size) {		/**	’~ÏŒ´eƒTƒCƒY	*/
	case	SYS_DOCUMENT_A4_SIZE:	/**	’~ÏŒ´eƒTƒCƒY‚ª‚`‚S‚Ì	*/
		/** ƒXƒLƒƒƒi‚Ì‰ğ‘œ“x–ˆ‚É’è‹`‚µ’¼‚µ‚½ 1997/10/28 By T.Yamaguchi */
		EncInpStatus = INPUT_A4_SIZE;
		table_locate_y = MEM_A4_POSI;
		break;
	case	SYS_DOCUMENT_B4_SIZE:	/**	’~ÏŒ´eƒTƒCƒY‚ª‚a‚S‚Ì	*/
		EncInpStatus = INPUT_B4_SIZE;
		table_locate_y = MEM_B4_POSI;
		break;
	case	SYS_DOCUMENT_A3_SIZE:	/**	’~ÏŒ´eƒTƒCƒY‚ª‚`‚R‚Ì	*/
		EncInpStatus = INPUT_A3_SIZE;
		table_locate_y = MEM_A3_POSI;
		break;
	}

	switch (src_mode) {
	case	SYS_NORMAL:	/**	TxŒ´eƒ‚[ƒh‚ª‚m‚‚’‚‚Ì	*/
		table_locate_y += MEM_NORM_POSI;
		break;
	case	SYS_FINE:	/**	TxŒ´eƒ‚[ƒh‚ª‚e‚‰‚‚…‚Ì	*/
		table_locate_y += MEM_FINE_POSI;
		break;
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		if ((CommunicateType == TX_G3_SCAN) ||
			(CommunicateType == TX_ECM_SCAN)) {
			if (GrayScannerTX_ReductionSet() == OK) {	/* ƒXƒLƒƒƒi’†ŠÔ’²‘—M‚Ìk¬—¦‚ğƒZƒbƒg‚·‚é */
				return(OK);								/* ƒZƒbƒgŠ®—¹ */
			}
			else {	/* SYS_A3_400_TO_A3_400:SYS_B4_400_TO_B4_400:SYS_A4_400_TO_A4_400:‚Ì‚Æ‚« */
#if (PRO_CCD == DPI400)
				table_locate_y += MEM_HFINE_POSI;
#endif
#if (PRO_CCD == DPI300)
				table_locate_y += MEM_EFINE_POSI;
#endif
#if (PRO_CCD == DPI200)
				table_locate_y += MEM_FINE_POSI;
#endif
			}
		}
		else {	/* ƒƒ‚ƒŠ‘—M‚Ìê‡ */
			table_locate_y += MEM_FINE_POSI;
		}
		break;
	case	SYS_SFINE:
		table_locate_y += MEM_SFINE_POSI;
		break;
	case	SYS_HFINE:
		table_locate_y += MEM_HFINE_POSI;
		break;
	case	SYS_UFINE: /* 600dpi~600dpi‘Î‰ 1999/05/26 by K.Okada */
		table_locate_y += MEM_UFINE_INCH_POSI;
		break;
	}

	/* TxReductionInch??_DocTable ‚É‚ÍAŒ´eƒTƒCƒY•ª‚Ì•ÏŠ·—¦‚ª“ü‚Á‚Ä‚¢‚Ü‚·B
	** TxRedutcionMetric??_DocTable ‚É‚ÍAŒ´eƒTƒCƒY•ª‚ÆƒCƒ“ƒ`[„ƒ~ƒŠ•ÏŠ·‚Ì•ÏŠ·—¦‚ª“ü‚Á‚Ä‚¢‚Ü‚·B
	** ‚±‚ê‚ÍA‹âˆÇ‚Ì–¼c‚Å‚·B
	** 1997/12/27
	** •¶Ó‹v•Û
	*/

	switch (dst_size) {		/**	‘—MŒ´eƒTƒCƒY	*/
	case	SYS_DOCUMENT_A4_SIZE:	/**	‘—MŒ´eƒTƒCƒY‚ª‚`‚S‚Ì	*/
		Pix_H_Reduction = TxReductionInchA4_DocTable[table_locate_y][table_locate_x];
		Pix_V_Reduction = TxReductionInchA4_DocTable[table_locate_y][table_locate_x+1];
		/*--------------------------*/
		/*	ƒXƒLƒƒƒi‘—M‚Ì‚İ—LŒø	*/
		/*--------------------------*/
		if ((CommunicateType == TX_G3_SCAN) ||
			(CommunicateType == TX_ECM_SCAN)) {

#if (PRO_CCD == DPI400)
			EncOtpStatus = 216;
			if (dst_mode != SYS_HFINE) {
				EncOtpStatus /= 2;
				if (src_mode != SYS_HFINE) {
					Pix_H_Reduction /= 2;
				}
			}
#endif
#if (PRO_CCD == DPI300)
			/* EncInpStatus = 2592 / 16; ŠÖ”‚Ì“ª‚Å‰Šú‰»‚·‚é 97/10/28 T.Yamaguchi */
			if (dst_mode == SYS_EFINE || dst_mode == SYS_E_HFINE) {
				EncOtpStatus = 2592 / 16;	/*162 Word*/
			}
			else {
				EncOtpStatus = 1728 / 16;	/*108 Word*/
				/* for ANZU_L 300*400 by T.Soneoka 1997/11/14 */
				if((src_mode != SYS_E_HFINE) && (src_mode != SYS_EFINE)){
					Pix_H_Reduction = ((Pix_H_Reduction * 2 )/ 3);	/* 1997/09/25 By M.Kotani */
				}
			}
#endif
#if (PRO_CCD == DPI200)
			EncOtpStatus = 108;
#endif
		}
		break;
	case	SYS_DOCUMENT_B4_SIZE:	/**	‘—MŒ´eƒTƒCƒY‚ª‚a‚S‚Ì	*/
		Pix_H_Reduction = TxReductionInchB4_DocTable[table_locate_y][table_locate_x];
		Pix_V_Reduction = TxReductionInchB4_DocTable[table_locate_y][table_locate_x+1];
		/*--------------------------*/
		/*	ƒXƒLƒƒƒi‘—M‚Ì‚İ—LŒø	*/
		/*--------------------------*/
		if ((CommunicateType == TX_G3_SCAN) ||
			(CommunicateType == TX_ECM_SCAN)) {
#if (PRO_CCD == DPI400)
			EncOtpStatus = 256;
			if (dst_mode != SYS_HFINE) {
				EncOtpStatus /= 2;
				if (src_mode != SYS_HFINE) {
					Pix_H_Reduction /= 2;
				}
			}
#endif
#if (PRO_CCD == DPI300)
			if (dst_mode == SYS_EFINE || dst_mode == SYS_E_HFINE) {
				EncOtpStatus = 3072 / 16;	/*192 Word*/
			}
			else {
				EncOtpStatus = 2048 / 16;	/*128 Word*/
				if((src_mode != SYS_E_HFINE) && (src_mode != SYS_EFINE)){
					Pix_H_Reduction = ((Pix_H_Reduction * 2 )/ 3);	/* 1997/09/25 By M.Kotani */
				}
			}
#endif
#if (PRO_CCD == DPI200)
			EncOtpStatus = 128;
#endif
		}
		break;
	case	SYS_DOCUMENT_A3_SIZE:	/**	‘—MŒ´eƒTƒCƒY‚ª‚`‚R‚Ì	*/
		Pix_H_Reduction = TxReductionInchA3_DocTable[table_locate_y][table_locate_x];
		Pix_V_Reduction = TxReductionInchA3_DocTable[table_locate_y][table_locate_x+1];
		/*--------------------------*/
		/*	ƒXƒLƒƒƒi‘—M‚Ì‚İ—LŒø	*/
		/*--------------------------*/
		if ((CommunicateType == TX_G3_SCAN) ||
			(CommunicateType == TX_ECM_SCAN)) {
#if (PRO_CCD == DPI400)
			EncOtpStatus = 304;
			if (dst_mode != SYS_HFINE) {
				EncOtpStatus /= 2;
				if (src_mode != SYS_HFINE) {
					Pix_H_Reduction /= 2;
				}
			}
#endif
#if (PRO_CCD == DPI300)
			if (dst_mode == SYS_EFINE || dst_mode == SYS_E_HFINE) {
				EncOtpStatus = 3648 / 16;	/*228 Word*/
			}
			else {
				EncOtpStatus = 2432 / 16;	/*152 Word*/
				if((src_mode != SYS_E_HFINE) && (src_mode != SYS_EFINE)){
					Pix_H_Reduction = ((Pix_H_Reduction * 2 )/ 3);	/* 1997/09/25 By M.Kotani */
				}
			}
#endif
#if (PRO_CCD == DPI200)
			EncOtpStatus = 152;
#endif
		}
		break;
	}
	return (OK);
}

/*************************************************************************
	module		:[•„†‰»ƒy[ƒW•İ’è]
	function	:[
		1.‘Šè‚Ì•„†‰»ƒTƒCƒY‚É‚æ‚èA‚l‚m‚W‚U‚O‚U‚R‚Ì•„‡‰»ƒy[ƒW•‚ğİ’è‚·‚é
	]
	return		:[
		•„†‰»ƒy[ƒW•
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UWORD		GetCodecSize(UBYTE size, UBYTE mode)
{
	UWORD	codec_size;
	codec_size = 0;

	switch (mode) {
	case	SYS_NORMAL:					/**	•’Ê	*/
	case	SYS_FINE:					/**	‚‰æ¿	*/
	case	SYS_GRAY16:					/**	16ŠK’²	*/
	case	SYS_GRAY16_SEP:				/**	16ŠK’²‘œˆæ•ª—£	*/
	case	SYS_GRAY32:					/**	32ŠK’²	*/
	case	SYS_GRAY32_SEP:				/**	32ŠK’²‘œˆæ•ª—£	*/
	case	SYS_GRAY64:					/**	64ŠK’²	*/
	case	SYS_GRAY64_SEP:				/**	64ŠK’²‘œˆæ•ª—£	*/
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
	case	SYS_SFINE:						/**	’´‚‰æ¿	*/
		switch (size) {						/**	‘—MŒ´eƒTƒCƒY	*/
		case	SYS_DOCUMENT_A3_SIZE:		/**	‚`‚RƒTƒCƒY‚Ì	*/
			codec_size = 152;				/**	‚`‚R•—LŒø‰æ‘f” 4862bit=304word	*/
			break;
		case	SYS_DOCUMENT_B4_SIZE:		/**	‚a‚SƒTƒCƒY‚Ì	*/
			codec_size = 128;				/**	‚a‚S•—LŒø‰æ‘f” 4096bit=256word	*/
			break;
		case	SYS_DOCUMENT_A4_SIZE:		/**	‚`‚SƒTƒCƒY‚Ì	*/
		default:
			codec_size = 108;				/**	‚`‚S•—LŒø‰æ‘f” 3456bit=216word	*/
			break;
		}
		break;
#if 1		/* ƒXƒLƒƒƒiå‘–¸‚R‚O‚O‚c‚o‚h‚Ì‚Æ‚« */ /* •œŠˆ‚³‚¹‚éB”Æl‚Í‹v•Û 1997/12/16 */
	case	SYS_EFINE:						/**	’´ã‰æ¿(300~300ƒ~ƒŠŒn)  1996/06/19 By N.Sakamoto	*/
	case	SYS_E_HFINE:					/**	’´‚‰æ¿(300~400ƒ~ƒŠŒn)  '96.03.08 By T.Y */
		switch (size) {						/**	‘—MŒ´eƒTƒCƒY	*/
		case	SYS_DOCUMENT_A3_SIZE:		/**	‚`‚RƒTƒCƒY‚Ì	*/
			codec_size = 228;				/**	‚`‚R•—LŒø‰æ‘f” 4862bit=304word * 3/4 = 228	*/
			break;
		case	SYS_DOCUMENT_B4_SIZE:		/**	‚a‚SƒTƒCƒY‚Ì	*/
			codec_size = 192;				/**	‚a‚S•—LŒø‰æ‘f” 4096bit=256word * 3/4 = 192	*/
			break;
		case	SYS_DOCUMENT_A4_SIZE:		/**	‚`‚SƒTƒCƒY‚Ì	*/
		default:
			codec_size = 162;				/**	‚`‚S•—LŒø‰æ‘f” 3456bit=216word * 3/4 = 162	*/
			break;
		}
		break;
#endif

	/**************************************
	** 600dpi~600dpi 1999/05/24 by K.Okada
	**************************************/
	case	SYS_UFINE:
		switch (size) {						/**	‘—MŒ´eƒTƒCƒY	*/
		case	SYS_DOCUMENT_A3_SIZE:		/**	‚`‚RƒTƒCƒY‚Ì	*/
			codec_size = 456;				/**	‚`‚R•—LŒø‰æ‘f” 4862bit=304word	*/
			break;
		case	SYS_DOCUMENT_B4_SIZE:		/**	‚a‚SƒTƒCƒY‚Ì	*/
			codec_size = 384;				/**	‚a‚S•—LŒø‰æ‘f” 4096bit=256word	*/
			break;
		case	SYS_DOCUMENT_A4_SIZE:		/**	‚`‚SƒTƒCƒY‚Ì	*/
		default:
			codec_size = 324;				/**	‚`‚S•—LŒø‰æ‘f” 3456bit=216word	*/
			break;
		}
		break;

	case	SYS_HFINE:						/**	’´‚‰æ¿(400~400ƒ~ƒŠŒn)  */
	default:
		switch (size) {						/**	‘—MŒ´eƒTƒCƒY	*/
		case	SYS_DOCUMENT_A3_SIZE:		/**	‚`‚RƒTƒCƒY‚Ì	*/
			codec_size = 304;				/**	‚`‚R•—LŒø‰æ‘f” 4862bit=304word	*/
			break;
		case	SYS_DOCUMENT_B4_SIZE:		/**	‚a‚SƒTƒCƒY‚Ì	*/
			codec_size = 256;				/**	‚a‚S•—LŒø‰æ‘f” 4096bit=256word	*/
			break;
		case	SYS_DOCUMENT_A4_SIZE:		/**	‚`‚SƒTƒCƒY‚Ì	*/
		default:
			codec_size = 216;				/**	‚`‚S•—LŒø‰æ‘f” 3456bit=216word	*/
			break;
		}
		break;
	}
	return (codec_size);
}


/*************************************************************************
	module		:[•„‡‰»‚jƒpƒ‰ƒ[ƒ^İ’è]
	function	:[
		1.‘Šè‚Ìƒ‚[ƒh‚É‰‚¶‚ÄA‚l‚m‚W‚U‚O‚U‚R‚Ì•„‡‰»‚jƒpƒ‰ƒ[ƒ^‚ğİ’è‚·‚é
	]
	return		:[
		•„‡‰»‚jƒpƒ‰ƒ[ƒ^
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UBYTE		GetK_Parameter(
UBYTE	mode)
{
	UBYTE	encode_kpara;
	/*--------------------------*/
	/*	•„†‰»‚jƒpƒ‰ƒ[ƒ^İ’è	*/
	/*--------------------------*/
	switch (mode) {			/**	•„†‰»•û®	*/
	case SYS_NORMAL:					/**	•’Ê	*/
		encode_kpara = 2;
		break;
	case SYS_FINE:						/**	‚‰æ¿	*/
	case SYS_GRAY16:					/**	16ŠK’²	*/
	case SYS_GRAY16_SEP:				/**	16ŠK’²‘œˆæ•ª—£	*/
	case SYS_GRAY32:					/**	32ŠK’²	*/
	case SYS_GRAY32_SEP:				/**	32ŠK’²‘œˆæ•ª—£	*/
	case SYS_GRAY64:					/**	64ŠK’²	*/
	case SYS_GRAY64_SEP:				/**	64ŠK’²‘œˆæ•ª—£	*/
		encode_kpara = 4;
		break;
	case SYS_SFINE:						/**	’´‚‰æ¿	*/
	case SYS_E_HFINE:					/**	’´‚‰æ¿	*/
	case SYS_HFINE:						/**	’´‚‰æ¿	*/
		encode_kpara = 8;
		break;
	
	/**************************************
	** 600dpi~600dpi 1999/05/24 by K.Okada
	**************************************/
	case SYS_UFINE:						/** 600~600iƒCƒ“ƒ`Œnj */
		encode_kpara = 12;
		break;

	default:
		encode_kpara = 0;
	}
	return (encode_kpara);
}


/*************************************************************************
	module		:[•œ†‰»Å‘åƒ‰ƒCƒ“”İ’è]
	function	:[
		1.‘Šè‚Ìƒ‚[ƒh‚É‰‚¶‚Ä•œ†‰»Å‘åƒ‰ƒCƒ“”‚ğİ’è‚·‚é
	]
	return		:[
		•œ†‰»ƒ‰ƒCƒ“”
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UWORD		GetMaxTxLine(
UWORD	length)
{
	UWORD	max_decode_line;

	max_decode_line = length;				/**	‚e‚b‚l‚ÌÅ‘åƒ‰ƒCƒ“”İ’è	*/
	if (max_decode_line != 0xffff) {
		switch (SYS_DocBlock.Src.Mode) {	/**	’~Ïƒ‚[ƒh	*/
		case SYS_NORMAL:					/**	•’Ê	*/
			break;
		case SYS_FINE:						/**	‚‰æ¿	*/
		case SYS_GRAY16:					/**	16ŠK’²	*/
		case SYS_GRAY16_SEP:				/**	16ŠK’²‘œˆæ•ª—£	*/
		case SYS_GRAY32:					/**	32ŠK’²	*/
		case SYS_GRAY32_SEP:				/**	32ŠK’²‘œˆæ•ª—£	*/
		case SYS_GRAY64:					/**	64ŠK’²	*/
		case SYS_GRAY64_SEP:				/**	64ŠK’²‘œˆæ•ª—£	*/
			max_decode_line *= 2;			/**	Å‘å•œ†‚©ƒ‰ƒCƒ“”‚Q”{	*/
			break;
		case SYS_SFINE:						/**	’´‚‰æ¿	*/
		case SYS_HFINE:						/**	’´‚‰æ¿	*/
			max_decode_line *= 4;			/**	Å‘å•œ†‰»ƒ‰ƒCƒ“”‚S”{	*/
			break;

		/**************************************
		** 600dpi~600dpi 1999/05/24 by K.Okada
		**************************************/
		case SYS_UFINE:						/**	600~600(ƒCƒ“ƒ`Œnj*/
			max_decode_line *= 6;			/**	Å‘å•œ†‰»ƒ‰ƒCƒ“”‚U”{	*/
			break;

		}
	}
	return (max_decode_line);
}

/*************************************************************************
	module		:[c‚è‚ÌƒGƒ“ƒR[ƒhƒf[ƒ^İ’è]
	function	:[
		1.
	]
	return		:[ƒGƒ“ƒR[ƒhƒf[ƒ^]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/26]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UDWORD			EncodeDataCountSet(void)
{
	UWORD counter;
	UDWORD address;
	UBYTE debug;

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/13 By H.Hirao */ /* ported for HINOKI2 2001/12/26 T.Takagi */
	/* ƒXƒLƒƒƒi‘—M‚Í’ÊMƒR[ƒfƒbƒN‚ğg—p */
	EncodeDataCount = DMA_CheckDMA_Address(DMA_CH_ENC, DMA_IO_TO_MEMORY) - (UDWORD) ECM_BUFFER_AREA_START_ADDRESS;
#else

	switch (CommunicateType) {
	case	TX_G3_SCAN:
	case	TX_ECM_SCAN:
		EncodeDataCount = DMA_CheckDMA_Address(DMA_SCNCDC_DRAM_CH,DMA_IO_TO_MEMORY) - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
		break;
	case	TX_G3_MEM:
	case	TX_ECM_MEM:
		EncodeDataCount = DMA_CheckDMA_Address(DMA_CH_ENC, DMA_IO_TO_MEMORY) - (UDWORD) ECM_BUFFER_AREA_START_ADDRESS;
		break;
	default:
		break;
	}
#endif
	return(EncodeDataCount);
}

/*************************************************************************
	module		:[Pix‘—oŠÔİ’è]
	function	:[
	]
	return		:[
		‘—oŠÔ*10(ms)
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UWORD		Set64K_PixTime(void)
{
	UWORD	time;

	switch (PixRxSpeed) {
	case SPEED_33600:
		time = 3360; /* 36408ms */
		break;
	case SPEED_31200:
		time = 1681; /* 36408ms */
		break;
	case SPEED_28800:
		time = 1821; /* 36408ms */
		break;
	case SPEED_26400:
		time = 1986; /* 36408ms */
		break;
	case SPEED_24000:
		time = 2185; /* 36408ms */
		break;
	case SPEED_21600:
		time = 2428; /* 36408ms */
		break;
	case SPEED_19200:
		time = 2731; /* 36408ms */
		break;
	case SPEED_16800:
		time = 3121; /* 36408ms */
		break;
	case SPEED_14400:
		time = 3641; /* 36408ms */
		break;
	case SPEED_12000:
		time = 4370; /* 43691ms */
		break;
	case SPEED_9600:
		time = 5462; /* 54613ms */
		break;
	case SPEED_7200:
		time = 7282; /* 72818ms */
		break;
	case SPEED_4800:
		time = 10923; /* 109227ms */
		break;
	case SPEED_2400:
		time = 21846; /* 218453ms */
		break;
	default:
		break;
	}
	return (time);
}


/*************************************************************************
	module		:[ƒXƒLƒƒƒi‘—M‰æƒf[ƒ^k¬•ÏŠ·—¦İ’è]
	function	:[
		1.’†ŠÔ’²i‚h‚c‚oj‚Ì•ÏŠ·‚ğ‰Á‚¦‚½Ak¬—¦‚ğƒZƒbƒg
	]
	return		:[OK:k¬—¦ƒZƒbƒgŠ®—¹
				  NO:k¬—¦ƒe[ƒuƒ‹‚©‚çƒZƒbƒg‚·‚éik¬‚µ‚È‚¢)
				 ]
	common		:[
		Pix_H_Reduction
		Pix_V_Reduction
		EncInpStatus
		EncOtpStatus
	]
	condition	:[]
	comment		:[
		İ’è’l‚ÍAƒ‚ƒfƒ€‚Ì‘—M‰æƒf[ƒ^k¬—¦•ÏŠ·‚ÌİŒvd—l‘‚ğQÆ‚µ‚Ä‚­‚¾‚³‚¢
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1996/12/09]
	author		:[RŒû]
*************************************************************************/
UBYTE GrayScannerTX_ReductionSet(void)
{
#if (PRO_CCD == DPI200)  /* POPLAR_L */
	switch (SCN_ScannerTxReductionPattern) {
	case	SYS_A3_400_TO_B4_400:
		/*	•K—v‚Æ‚³‚ê‚ék¬—¦ ‚W‚SD‚R‚V‚T“i‚Q‚V^‚R‚Qj
		**	‚h‚c‚oå‘–¸k¬@‚W‚SD‚T‚R‚X“
		**	‚W‚SD‚R‚V‚T^‚W‚SD‚T‚R‚X‚OD‚X‚X‚W
		**	‚b‚n‚c‚d‚bå‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚W‚P‚O‚Q‚Qi‚O‚˜‚O‚R‚e‚dj
		**  ‚b‚n‚c‚d‚b•›‘–¸k¬
		**	‚P‚U‚R‚W‚S|i‚OD‚X‚X‚W~‚P‚U‚R‚W‚Sj ‚R‚Ri‚O‚˜‚O‚O‚Q‚Pj
		*/
		Pix_H_Reduction = 0x03FE;
		Pix_V_Reduction = 0x0021;
		EncInpStatus = 128;/* 2056 / 16 = 128.5 */
		EncOtpStatus = 128;/* 128 * 0.998 */
		return (OK);
	case	SYS_A3_400_TO_A4_400:
		/*	•K—v‚Æ‚³‚ê‚ék¬—¦ ‚U‚WD‚V‚T“i‚Q‚Q^‚R‚Qj
		**	‚h‚c‚oå‘–¸k¬@‚U‚WD‚V‚T“
		**	‚U‚WD‚V‚T^‚U‚WD‚V‚T‚PD‚O‚O‚O
		**	‚b‚n‚c‚d‚bå‘–¸“™”{
		**	‚P‚O‚Q‚S~‚PD‚O‚O‚O‚P‚O‚Q‚Si‚O‚˜‚O‚S‚O‚Oj
		**  ‚b‚n‚c‚d‚b•›‘–¸“™”{
		**	‚P‚U‚R‚W‚S|i‚PD‚O‚O‚O~‚P‚U‚R‚W‚Sj ‚O
		*/
		Pix_H_Reduction = 0x0400;
		Pix_V_Reduction = 0x0000;
		EncInpStatus = 108;	/* 1672/16=108.5    */
		EncOtpStatus = 108; /* 108*1.00=108     */
		return (OK);
	case	SYS_B4_400_TO_A4_400:
		/*	•K—v‚Æ‚³‚ê‚ék¬—¦ ‚W‚PD‚Q‚T“i‚Q‚U^‚R‚Qj
		**	‚h‚c‚oå‘–¸k¬@‚W‚PD‚Q‚T“
		**	‚W‚PD‚Q‚T^‚W‚PD‚Q‚T‚PD‚O
		**	‚b‚n‚c‚d‚bå‘–¸“™”{
		**	‚P‚O‚Q‚S~‚PD‚O‚O‚O‚P‚O‚Q‚Si‚O‚˜‚O‚S‚O‚Oj
		**	‚b‚n‚c‚d‚b•›‘–¸“™”{
		**	‚P‚U‚R‚W‚S|i‚PD‚O‚O‚O~‚P‚U‚R‚W‚Sj ‚O
		*/
		Pix_H_Reduction = 0x0400;
		Pix_V_Reduction = 0x0000;
		EncInpStatus = 103;	/* 1664/16=104     */
		EncOtpStatus = 108; /* 104*1.00 = 104  */
		return (OK);
	case	SYS_A3_400_TO_A3_400:
	case	SYS_B4_400_TO_B4_400:
	case	SYS_A4_400_TO_A4_400:
	default:
		return(NO);	/* •ÏŠ·‚µ‚È‚¢‚Æ‚« */
	}
#elif (PRO_CCD == DPI400)
/* Ported from ORANGE\SRC\MDM_SUB.C by H.Kubo 1997/07/08 */
/* POPLAR_H —p‚Å‚·B  POPLAR_B ‚Æ“¯‚¶‚É‚È‚é‚æ‚¤‚É‚µ‚Ä‚¢‚Ü‚·B */
/*#if (PRO_CCD == DPI400)	@* POPLAR_H */
/*************************************************************************
	module		:[ƒXƒLƒƒƒi‘—M‰æƒf[ƒ^k¬•ÏŠ·—¦İ’è]
	function	:[
		1.’†ŠÔ’²i‚h‚c‚oj‚Ì•ÏŠ·‚ğ‰Á‚¦‚½Ak¬—¦‚ğƒZƒbƒg
	]
	return		:[OK:k¬—¦ƒZƒbƒgŠ®—¹
				  NO:k¬—¦ƒe[ƒuƒ‹‚©‚çƒZƒbƒg‚·‚éik¬‚µ‚È‚¢)
				 ]
	common		:[
		Pix_H_Reduction
		Pix_V_Reduction
		EncInpStatus
		EncOtpStatus
	]
	condition	:[]
	comment		:[
		İ’è’l‚ÍAƒ‚ƒfƒ€‚Ì‘—M‰æƒf[ƒ^k¬—¦•ÏŠ·‚ÌİŒvd—l‘‚ğQÆ‚µ‚Ä‚­‚¾‚³‚¢
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1996/12/09]
	author		:[RŒû]
*************************************************************************/
/*UBYTE GrayScannerTX_ReductionSet(void)
{*/
	switch (SCN_ScannerTxReductionPattern) {
	case	SYS_A3_400_TO_A3_200:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚XD‚W“
		**	‚OD‚T^‚OD‚S‚X‚W‚PD‚O‚O‚S	‚b‚n‚c‚d‚bå•›‘–¸Šg‘å
		**	‚P‚O‚Q‚S~‚PD‚O‚O‚S‚P‚O‚Q‚Wi‚O‚˜‚S‚O‚Sj
		**	‚PD‚O‚O‚S~‚U‚T‚T‚R‚U|‚U‚T‚T‚R‚U‚Q‚U‚Qi‚O‚˜‚P‚O‚Uj
		*/
		Pix_H_Reduction = 0x8404;
		Pix_V_Reduction = 0x0106;
		EncInpStatus = 152;	/*	2432/16=152 */
		EncOtpStatus = 304/2;
		return (OK);
	case	SYS_A3_400_TO_A3_203:
		/*	‚h‚c‚oå‘–¸k¬@‚T‚PD‚T“
		**	‚OD‚T‚O‚W^‚OD‚T‚P‚T‚OD‚X‚W‚U	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚W‚U‚P‚O‚P‚Oi‚O‚˜‚R‚†‚Qj
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚W‚U~‚U‚T‚T‚R‚Uj‚X‚P‚Wi‚O‚˜‚R‚X‚Uj
		*/
		Pix_H_Reduction = 0x03f2;
		Pix_V_Reduction = 0x0396;
		EncInpStatus = 156;	/* 2506/16=156.63 */
		EncOtpStatus = 304/2;
		return (OK);
	case	SYS_A3_400_TO_B4_200:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚QD‚T“
		**	‚OD‚S‚Q‚Q^‚OD‚S‚Q‚T‚OD‚X‚X‚R	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚R‚P‚O‚P‚Vi‚O‚˜‚R‚†‚Xj
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚R~‚U‚T‚T‚R‚Uj‚S‚T‚Xi‚O‚˜‚P‚ƒ‚‚j
		**	ICHOUC³  1996/11/12 s.takeuchi
		**	IDPå‘–¸k¬—¦‚ª 42.1% ‚Æ‚µ‚ÄCODEC‚ğİ’è‚·‚é‚Æ‚Ü‚Æ‚à‚È‰æ‚ªo‚é
		**		ª“ú—§‚©‚ç‚Ì‰ñ“šFAX‚Å‚Í 42.11% ‚É‚È‚é  1996/12/12 s.takeuchi
		**	0.422 / 0.421 = 1.002  :  CODECå‘–¸k¬—¦
		**	å‘–¸k¬İ’è’l : 1024 * 1.002 = 1026 (402h)
		**	•›‘–¸k¬İ’è’l : (1.002 * 65536) - 65536 = 131 (83h)
		**	å‘–¸“ü—Í‰æ‘f	 : 128 WORD
		*/
	/*	Pix_H_Reduction = 0x0402;	ICHOU‚É‡‚í‚¹‚½1997/05/27  By T.Yamaguchi */
		Pix_H_Reduction = 0x8402;	/* 0x03f9 */
		Pix_V_Reduction = 0x0083;	/* 0x01cb */
		EncInpStatus = 128;	/* 2068/16=129.25 */
		EncOtpStatus = 256/2;
		return (OK);
	case	SYS_A3_400_TO_B4_203:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚RD‚Q“
		**	‚OD‚S‚Q‚X^‚OD‚S‚R‚Q‚OD‚X‚X‚R	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚R‚P‚O‚P‚Vi‚O‚˜‚R‚†‚Xj
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚R~‚U‚T‚T‚R‚Uj‚S‚T‚Xi‚O‚˜‚P‚ƒ‚‚j
		*/
		Pix_H_Reduction = 0x03f2;	/* '94.10.25 0x3f9->0x3f2 98.7% */
		Pix_V_Reduction = 0x0a3d;	/* '94.10.25 0x1cb->0xa3d 96%	*/
		/* EncInpStatus = 129;	@* 2103/16=131.44 */
		EncInpStatus = 131;	/* 2103/16=131.44 */	/* ICHOUC³  1996/11/12 s.takeuchi */
		EncOtpStatus = 256/2;
		return (OK);
	case	SYS_A3_400_TO_A4_200:
		/*	‚h‚c‚oå‘–¸k¬@‚R‚SD‚T“
		**	‚OD‚R‚S‚S^‚OD‚R‚S‚T‚OD‚X‚X‚V	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚V‚P‚O‚Q‚Pi‚O‚˜‚R‚†‚„j
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚V~‚U‚T‚T‚R‚Uj‚P‚X‚Vi‚O‚˜‚ƒ‚Tj
		*/
		Pix_H_Reduction = 0x03fd;
		Pix_V_Reduction = 0x00c5;
		EncInpStatus = 104;	/* 1677/16=104.81 */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_A3_400_TO_A4_203:
		/*	‚h‚c‚oå‘–¸k¬@‚R‚T“
		**	‚OD‚R‚T^‚OD‚R‚T‚PD‚O	‚b‚n‚c‚d‚b•›‘–¸“™”{
		*/
		Pix_H_Reduction = 0x03f9;	/* '94.10.25 0x400->0x3f9 99.4%	*/
		Pix_V_Reduction = 0x08f5;	/* '94.10.25 0x00 ->0x8f5 96.5%	*/
		EncInpStatus = 106;	/* 1702/16=106.38 */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_B4_400_TO_B4_200:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚XD‚W“
		**	‚OD‚T^‚OD‚S‚X‚W‚PD‚O‚O‚S	‚b‚n‚c‚d‚bå•›‘–¸Šg‘å
		**	‚P‚O‚Q‚S~‚PD‚O‚O‚S‚P‚O‚Q‚Wi‚O‚˜‚S‚O‚Sj
		**	‚PD‚O‚O‚S~‚U‚T‚T‚R‚U|‚U‚T‚T‚R‚U‚Q‚U‚Qi‚O‚˜‚P‚O‚Uj
		*/
		Pix_H_Reduction = 0x8404;
		Pix_V_Reduction = 0x0106;
		EncInpStatus = 128;	/* 2048/16=128 */
		EncOtpStatus = 256/2;
		return (OK);
	case	SYS_B4_400_TO_B4_203:
		/*	‚h‚c‚oå‘–¸k¬@‚T‚PD‚S“
		**	‚OD‚T‚O‚W^‚OD‚T‚P‚S‚OD‚X‚W‚W	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚W‚W‚P‚O‚P‚Qi‚O‚˜‚R‚†‚Sj
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚W‚W~‚U‚T‚T‚R‚Uj‚V‚W‚Ui‚O‚˜‚R‚P‚Qj
		**	Pix_H_Reduction = 0x03f4;
		**	Pix_V_Reduction = 0x0312;
		** '94.10.25 H_Reduction = 0.985 V_Reduction = 0.955
		*/
		Pix_H_Reduction = 0x03f0;
		Pix_V_Reduction = 0x0b85;	/*	•›‘–¸k¬‚OD‚S‚O‚V“	*/
		EncInpStatus = 131;	/* 2110/16=131.88 */
		EncOtpStatus = 256/2;
		return (OK);
	case	SYS_B4_400_TO_A4_200:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚OD‚V“
		**	‚OD‚S‚O‚V^‚OD‚S‚O‚V‚PD‚O	‚b‚n‚c‚d‚b•›‘–¸“™”{
		*/
		Pix_H_Reduction = 0x0400;
		Pix_V_Reduction = 0x0000;
		/* EncInpStatus = 105;	@* 1688/16=105.5 */
		EncInpStatus = 104;	/* 1668/16=104.25 */	/* ICHOUC³  1996/11/12 s.takeuchi */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_B4_400_TO_A4_203:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚PD‚S“
		**	‚OD‚S‚P‚R^‚OD‚S‚P‚S‚OD‚X‚X‚W	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚W‚P‚O‚Q‚Qi‚O‚˜‚R‚†‚…j
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚W~‚U‚T‚T‚R‚Uj‚P‚R‚Pi‚O‚˜‚W‚Rj
		*/
		Pix_H_Reduction = 0x03fa;	/*	0x3fe->0x3fa 0.995%	*/
		Pix_V_Reduction = 0x08f5;	/*	0x83->0x8f5	0.965%	*/
		EncInpStatus = 105; /* 1694/16=105.88 */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_A4_400_TO_A4_200:
		/*	‚h‚c‚oå‘–¸k¬@‚S‚XD‚W“
		**	‚OD‚T^‚OD‚S‚X‚W‚PD‚O‚O‚S	‚b‚n‚c‚d‚bå•›‘–¸Šg‘å
		**	‚P‚O‚Q‚S~‚PD‚O‚O‚S‚P‚O‚Q‚Wi‚O‚˜‚S‚O‚Sj
		**	‚PD‚O‚O‚S~‚U‚T‚T‚R‚U|‚U‚T‚T‚R‚U‚Q‚U‚Qi‚O‚˜‚P‚O‚Uj
		*/
		Pix_H_Reduction = 0x8404;
		Pix_V_Reduction = 0x0106;
		EncInpStatus = 108; /* 1728/16=108 */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_A4_400_TO_A4_203:
		/*	‚h‚c‚oå‘–¸k¬@‚T‚PD‚Q“
		**	‚OD‚T‚O‚W^‚OD‚T‚P‚Q‚OD‚X‚X‚Q	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚Q‚P‚O‚P‚Ui‚O‚˜‚R‚†‚Wj
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚Q~‚U‚T‚T‚R‚Uj‚T‚Q‚Si‚O‚˜‚Q‚O‚ƒj
		**	Pix_H_Reduction = 0x03f8;
		**	Pix_V_Reduction = 0x020c;		•›‘–¸k¬‚OD‚S‚O‚V“
		** '94.10.25 H_Reduction = 0.985 V_Reduction = 0.955
		*/
		Pix_H_Reduction = 0x03f0;
		Pix_V_Reduction = 0x0b85;	/*	•›‘–¸k¬‚OD‚S‚O‚V“	*/
		EncInpStatus = 111; /* 1780/16=111.25 */
		EncOtpStatus = 216/2;
		return (OK);
	case	SYS_A3_400_TO_B4_400:
		/*	‚h‚c‚oå‘–¸k¬@‚W‚SD‚T“
		**	‚OD‚W‚S‚S^‚OD‚W‚S‚T‚OD‚X‚X‚X	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚X‚P‚O‚Q‚Ri‚O‚˜‚R‚†‚†j
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚X~‚U‚T‚T‚R‚Uj‚U‚Ui‚O‚˜‚S‚Qj
		*/
		Pix_H_Reduction = 0x03ff;
		Pix_V_Reduction = 0x0042;
		EncInpStatus = 256;/* 4109/16=256.81 */
		EncOtpStatus = 256;
		return (OK);
	case	SYS_A3_400_TO_A4_400:
		/*	‚h‚c‚oå‘–¸k¬@‚U‚XD‚Q“
		**	‚OD‚U‚W‚W^‚OD‚U‚X‚Q‚OD‚X‚X‚S	‚b‚n‚c‚d‚bå•›‘–¸k¬
		**	‚P‚O‚Q‚S~‚OD‚X‚X‚S‚P‚O‚P‚Wi‚O‚˜‚R‚†‚j
		**	‚U‚T‚T‚R‚U|i‚OD‚X‚X‚S~‚U‚T‚T‚R‚Uj‚R‚X‚Ri‚O‚˜‚P‚W‚Xj
		*/
		Pix_H_Reduction = 0x03fa;
		Pix_V_Reduction = 0x0189;
		EncInpStatus = 210;	/*	3367/16=210.44	*/
		EncOtpStatus = 216;
		return (OK);
	case	SYS_B4_400_TO_A4_400:
		/*	‚h‚c‚oå‘–¸k¬@‚W‚PD‚R“
		**	‚OD‚W‚P‚R^‚OD‚W‚P‚R‚PD‚O	‚b‚n‚c‚d‚b•›‘–¸“™”{
		*/
		Pix_H_Reduction = 0x0400;
		Pix_V_Reduction = 0x0000;
		EncInpStatus = 208;	/* 3331/16=208.19 */
		EncOtpStatus = 216;
		return (OK);
	case	SYS_A3_400_TO_A3_400:
	case	SYS_B4_400_TO_B4_400:
	case	SYS_A4_400_TO_A4_400:
	default:
		return(NO);	/* •ÏŠ·‚µ‚È‚¢‚Æ‚« */
	}
#endif /* (PRO_CCD == DPI400) */
}

/*************************************************************************
	module		:[
		T.85(JBIG)‚É‚æ‚é‚a‚h‚g‚ğ“Ç‚İ‚İ
	]
	function	:[
		1.óM‚µ‚½‚a‚h‚g‚ğ‘åˆæ•Ï”‚ÉƒZƒbƒg‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[Œ³‚Í\src\atlanta\scd\src\jbg_bih.c‚©‚ç‚Æ‚Á‚Ä‚«‚Ü‚µ‚½]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/12/17]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
void MDM_JBG_ReadBIH(void)
{
	UBYTE loop;
	UBYTE *dst;
	UBYTE *src;

	dst = (UBYTE *)&CDC_JBG_BIH;
	src = (UBYTE *)&EcmBuffer;
	for (loop = 0; loop < 20; loop++) {
		*dst = *src;
		src++;
		dst++;
	}
}


/*************************************************************************
	module		:[’ÊM‹­§’â~‚©”Û‚©]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRO_QUICK_TX]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1998/12/11]
	author		:[‘º“c]
*************************************************************************/
UBYTE MDM_TxForceStop(void)
{
	if (CHK_TxForceStop()) {
		return(1);
	}
#if 0
**	if (SYS_QuickTxStopSwitch(0)) {
**		return(1);
**	}
#endif
	return(0);
}

/* ‘S‹@í‚É”½‰f‚³‚¹‚Ü‚·B  by H.Kubo 1999/01/26 */
/*
** ModemControl.UsedCount‚ªA‚e‚b‚lƒ^ƒXƒN‚ÆŠ„‚è‚İ‚Ì‚È‚©‚ÅA“¯‚Éƒ‰ƒCƒg‚³‚ê‚Ä‚¢‚Ü‚·
** ‚e‚b‚lƒ^ƒXƒN‚Ì‚È‚©‚ÅAƒ‰ƒCƒg‚·‚é‚Æ‚«AŠ„‚è‚İ‹Ö~ó‘Ô‚Ås‚¤‚½‚ß‚ÉAˆÈ‰º‚ÌŠÖ”‚Æ’u‚«Š·‚¦‚Ü‚·B
** –â‘è‚È‚¢‚Æ‚Ív‚¢‚Ü‚·‚ªA‚Æ‚è‚ ‚¦‚¸HINOKI‚¾‚¯
** by H.Hirao 1998/12/10
*/
/*
** ƒ‚ƒfƒ€ƒoƒbƒtƒ@g—p–{”‚ğ‚Pƒvƒ‰ƒX‚·‚é
*/
void IncModemControlUsedCount(void)
{
	UBYTE is_int_enable; /* BOOL => UBYTE by H.Kubo 1999/01/26 */
	
	if(is_int_enable = CheckInterruptEnable()) {
		CMN_DisableInterrupt();
	}
	ModemControl.UsedCount++;
	
	if (is_int_enable) {
		CMN_EnableInterrupt();
	}
}

/*
** ƒ‚ƒfƒ€ƒoƒbƒtƒ@g—p–{”‚ğ‚Pƒ}ƒCƒiƒX‚·‚é
*/
void DecModemControlUsedCount(void)
{
	UBYTE is_int_enable; /* BOOL => UBYTE by H.Kubo 1999/01/26 */
	
	if(is_int_enable = CheckInterruptEnable()) {
		CMN_DisableInterrupt();
	}
	ModemControl.UsedCount--;
	
	if (is_int_enable) {
		CMN_EnableInterrupt();
	}
}

/*
** Ecm Tx ‚ÌƒtƒŒ[ƒ€ŠÔƒtƒ‰ƒO‘—o‚Ì‘Ò‚¿ŠÔ¶¬—p
** by H.Kubo 1999/01/25
*/
void MDM_EcmTxFillFlags(void)
{
	CMN_ModemWait100microSec(MDM_EcmTxFillFlagsTable[ModemBlock.Speed]); /* ƒtƒ‰ƒO“ñ‚Â•ª‚ÌŠÔ‚ªŒo‚Â‚Ü‚Å‘Ò‚Â */
	return;
}

