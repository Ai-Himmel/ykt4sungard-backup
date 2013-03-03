/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/15
*        FILE NAME:  cdc_cdcr.c
*      DESCRIPTION:  ¼‰º»ƒR[ƒfƒbƒNNM86063‚ÌCDCR(•„†, •œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^)‚ð
*                    Ý’è‚·‚éˆ×‚Ìƒtƒ@ƒCƒ‹ŒQ
*  PUBLIC ROUTINES: void AbortDecode(UBYTE codec_type)
* PRIVATE ROUTINES: void CodecEncodeCDCR_Setup(UBYTE codec_type)
*                   void CodecDecodeCDCR_Setup(UBYTE codec_type)
*                   void CodecDecodeCheckCDCR_Setup(UBYTE codec_type)
*                   void CodecCodeConvertCDCR_Setup(UBYTE codec_type)
*                   void CodecDataTransferCDCR_Setup(UBYTE codec_type)
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\memsw\define\mems_pro.h"	/* ƒfƒR[ƒhƒGƒ‰[ŽžAu‘Oƒ‰ƒCƒ“’u‚«Š·‚¦^”’ƒ‰ƒCƒ“’u‚«Š·‚¦v‚ðƒƒ‚ƒŠƒXƒCƒbƒ`‘I‘ð‰Â”\‚É‚·‚éBBy O.Kimoto 1998/03/20 */

/*************************************************************************
	module		:[•œ†‰»‚ðƒAƒ{[ƒg‚·‚é‚æ‚¤‚ÉCDCR‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É•œ†‰»‚ðƒAƒ{[ƒg‚·‚éƒrƒbƒg‚ðƒZƒbƒg‚·‚é
		2.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		•œ†‰»‚ÌŽž‰½‚ç‚©‚ÌŒ´ˆö‚ÅNM86063‚ªƒƒbƒN‚µ‚½ŽžCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void AbortDecode(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
	UWORD bit;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ƒn[ƒhƒR[ƒfƒbƒN‚PŒÂŽg—p‚Ìê‡‚Íƒ`ƒƒƒ“ƒlƒ‹‚ð•ª‚¯‚é*/
	if (codec_type == SCANNER_CODEC) {
		bit = DABT0_BIT;
	}
	else {
		bit = DABT1_BIT;
		codec_type = SCANNER_CODEC;	/** ƒn[ƒhƒR[ƒfƒbƒN‚ðƒXƒLƒƒƒi[ƒR[ƒfƒbƒN‚ÅŒÅ’è‚·‚é */
	}
#else	/** ’Êí‚Í‚»‚ê‚¼‚ê‚ÌƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚O‚ðŽg—p‚·‚é */
	bit = DABT0_BIT;
#endif
	/**•œ†‰»‚ðƒAƒ{[ƒg‚·‚é—l‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= bit;		/**0x0002 •œ†‰»ƒAƒ{[ƒg(0:’Êí, 1:•œ†‰»ƒAƒ{[ƒg)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR],
		  CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}


/*************************************************************************
	module		:[•„†‰»—p‚ÉCDCR(•„†‰», •œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^)‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É‰æ‘œ“ü—ÍŒo˜H•‰æ‘œo—ÍŒo˜H‚ðÝ’è‚·‚é
		2.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_stup.c‚Ì
		WORD far CodecEncodeSetup
		(struct CodecEncodeParameterBlk_t *)
		‚©‚çCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void CodecEncodeCDCR_Setup(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ƒn[ƒhƒR[ƒfƒbƒN‚PŒÂŽg—p‚Ìê‡‚Íƒ`ƒƒƒ“ƒlƒ‹‚O‚ðƒGƒ“ƒR[ƒh—p‚Æ‚·‚é*/
	codec_type = SCANNER_CODEC;	/** ƒn[ƒhƒR[ƒfƒbƒN‚ðƒXƒLƒƒƒi[ƒR[ƒfƒbƒN‚ÅŒÅ’è‚·‚é */
	CodecCDCR_Status[codec_type] &= 0xFF00;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^ ƒ`ƒƒƒ“ƒlƒ‹‚O‚ð‰Šú‰»*/
#else	/** ’Êí‚Í‚»‚ê‚¼‚ê‚ÌƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚O‚ðŽg—p‚·‚é */
	CodecCDCR_Status[codec_type] = 0;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^*/
#endif
	if (codec_type == COMMUNICATION_CODEC) {
		/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMIN00_BIT;	/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð0‚É‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMIN01_BIT;	/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
	else {
		/**‰æ‘œ“ü—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMIN00_BIT;	/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð0‚É‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMIN01_BIT;	/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
	/**‰æ‘œo—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMOT00_BIT;		/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMOT01_BIT;		/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**•„†‰»‚Ì‚Æ‚«•„†ƒf[ƒ^‚ðƒoƒCƒg’PˆÊ‚ÅI—¹‚·‚é‚æ‚¤‚ÉƒtƒBƒ‹ƒrƒbƒg‚ð‚Â‚¯‚é*/
	CodecCDCR_Status[codec_type] |= OCT0_BIT;		/**0x0020 ƒIƒNƒeƒbƒgƒ‚[ƒh(0:’Êí, 1:ƒIƒNƒeƒbƒg‰»)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR], CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}


/*************************************************************************
	module		:[•œ†‰»—p‚ÉCDCR(•„†‰», •œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^)‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É‰æ‘œ“ü—ÍŒo˜H•‰æ‘œo—ÍŒo˜H‚ðÝ’è‚·‚é
		2.ƒGƒ‰[ƒ‰ƒCƒ“‚Ìˆ—‚ðÝ’è‚·‚é
		3.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_stup.c‚Ì
		WORD far CodecDecodeSetup
		(struct CodecDecodeParameterBlk_t *)
		‚©‚çCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void CodecDecodeCDCR_Setup(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ƒn[ƒhƒR[ƒfƒbƒN‚PŒÂŽg—p‚Ìê‡‚Íƒ`ƒƒƒ“ƒlƒ‹‚P‚ðƒfƒR[ƒh—p‚Æ‚·‚é*/
	codec_type = SCANNER_CODEC;	/** ƒn[ƒhƒR[ƒfƒbƒN‚ðƒXƒLƒƒƒi[ƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚P‚ÅŒÅ’è‚·‚é */
	CodecCDCR_Status[codec_type] &= 0x00FF;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^ ƒ`ƒƒƒ“ƒlƒ‹‚P‚ð‰Šú‰»*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN10_BIT;		/**0x4000 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN11_BIT;		/**0x8000 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT10_BIT;	/**0x0400 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT11_BIT;	/**0x0800 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**ƒGƒ‰[ˆ—‚ð”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚ÉÝ’è‚·‚é*/

#if (0)
** 	/* ƒfƒR[ƒhƒGƒ‰[ŽžAu‘Oƒ‰ƒCƒ“’u‚«Š·‚¦^”’ƒ‰ƒCƒ“’u‚«Š·‚¦v‚ðƒƒ‚ƒŠƒXƒCƒbƒ`‘I‘ð‰Â”\‚É‚·‚éB
** 	** By O.Kimoto 1998/03/20
** 	*/
** 	CodecCDCR_Status[codec_type] |= ERROR1_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
#else
	if (CHK_ErrorLineReplace() == 1) {	/* ”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚È‚ç‚Î */
		CodecCDCR_Status[codec_type] |= ERROR1_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
	else {	/* ‘Oƒ‰ƒCƒ“’u‚«Š·‚¦ */
		CodecCDCR_Status[codec_type] &= ~ERROR1_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
#endif

#else	/** ’Êí‚Í‚»‚ê‚¼‚ê‚ÌƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚O‚ðŽg—p‚·‚é */
	CodecCDCR_Status[codec_type] = 0;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN00_BIT;		/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN01_BIT;		/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
#if (PRO_PRINTER_RX == ENABLE)	/* By H.Hirao 1998/10/27 */
	if (CodecGetID[codec_type] = CODEC_PRINTER_RX) { /* ƒvƒŠƒ“ƒ^ŽóM‚ÍAƒVƒXƒeƒ€ƒoƒX‚ÉƒfƒR[ƒh‚·‚é */
		/**‰æ‘œo—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMOT00_BIT;		/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð3‚É‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMOT01_BIT;		/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
	else {
		/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMOT00_BIT;	/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMOT01_BIT;	/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
#else
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/17 K.Kawata*/
	if (CodecGetID[codec_type] = CODEC_PRINTER_RX) { /* ƒvƒŠƒ“ƒ^ŽóM‚ÍAƒVƒXƒeƒ€ƒoƒX‚ÉƒfƒR[ƒh‚·‚é */
		/**‰æ‘œo—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMOT00_BIT;		/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð3‚É‚·‚é*/
		CodecCDCR_Status[codec_type] |= IMOT01_BIT;		/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
	else {
		/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMOT00_BIT;	/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
		CodecCDCR_Status[codec_type] &= ~IMOT01_BIT;	/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	}
#else
	/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT00_BIT;	/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT01_BIT;	/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
#endif
#endif
	/**ƒGƒ‰[ˆ—‚ð”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚ÉÝ’è‚·‚é*/

#if (0)
** 	/* ƒfƒR[ƒhƒGƒ‰[ŽžAu‘Oƒ‰ƒCƒ“’u‚«Š·‚¦^”’ƒ‰ƒCƒ“’u‚«Š·‚¦v‚ðƒƒ‚ƒŠƒXƒCƒbƒ`‘I‘ð‰Â”\‚É‚·‚éB
** 	** By O.Kimoto 1998/03/20
** 	*/
** 	CodecCDCR_Status[codec_type] |= ERROR0_BIT;		/**0x0001 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
#else
	if (CHK_ErrorLineReplace() == 1) {	/* ”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚È‚ç‚Î */
		CodecCDCR_Status[codec_type] |= ERROR0_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
	else {	/* ‘Oƒ‰ƒCƒ“’u‚«Š·‚¦ */
		CodecCDCR_Status[codec_type] &= ~ERROR0_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
#endif

#endif
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR],
		  CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}


/*************************************************************************
	module		:[•œ†ƒGƒ‰[ƒ`ƒFƒbƒN—p‚ÉCDCR‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É‰æ‘œ“ü—ÍŒo˜H‚ðÝ’è‚·‚é
		2.ƒGƒ‰[ƒ`ƒFƒbƒN‚Ìƒrƒbƒg‚ðƒZƒbƒg‚·‚é
		3.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_stup.c‚Ì
		WORD far CodecDecodeCheckSetup
		(struct CodecDecodeParameterBlk_t *)
		‚©‚çCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void CodecDecodeCheckCDCR_Setup(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ƒn[ƒhƒR[ƒfƒbƒN‚PŒÂŽg—p‚Ìê‡‚Íƒ`ƒƒƒ“ƒlƒ‹‚P‚ðƒfƒR[ƒh—p‚Æ‚·‚é*/
	codec_type = SCANNER_CODEC;	/** ƒn[ƒhƒR[ƒfƒbƒN‚ðƒXƒLƒƒƒi[ƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚P‚ÅŒÅ’è‚·‚é */
	CodecCDCR_Status[codec_type] &= 0x00FF;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^ ƒ`ƒƒƒ“ƒlƒ‹‚P‚ð‰Šú‰»*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN10_BIT;		/**0x4000 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN11_BIT;		/**0x8000 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**ƒGƒ‰[ƒ`ƒFƒbƒN“®ì‚ðÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= ERCHK1_BIT;		/**0x1000 ƒGƒ‰[ƒ`ƒFƒbƒN(0:’Êí, 1:‰æ‘œƒf[ƒ^o—Í‚¹‚¸)*/
#else	/** ’Êí‚Í‚»‚ê‚¼‚ê‚ÌƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚O‚ðŽg—p‚·‚é */
	CodecCDCR_Status[codec_type] = 0;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN00_BIT;		/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN01_BIT;		/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**ƒGƒ‰[ƒ`ƒFƒbƒN“®ì‚ðÝ’è‚·‚é*/
#if 0 /* (PRO_COM_CODEC_TYPE == MN86064) */ /* Modified by H.Kubo 1997/12/09 */
	/* 1997/12/09 Œ»ÝAMN86064 (ƒŠƒrƒWƒ‡ƒ“ ED)‚Å ERCHK0 ƒrƒbƒg‚ð—§‚Ä‚Ä
	**  MMR ‚ÌƒfƒR[ƒhˆ—‚ðs‚¤‚ÆAƒGƒ‰[‚Ì‚È‚¢Œ´e‚É‘Î‚µ‚Ä‚àƒfƒR[ƒh
	** ƒGƒ‰[‚ª”­¶‚µ‚Ü‚·BŽb’èˆ’u‚Æ‚µ‚ÄA ERCHK0 ƒrƒbƒg‚Í—§‚Ä‚È‚¢
	** ‚±‚Æ‚É‚µ‚ÄAƒfƒR[ƒhŒ‹‰Ê‚ÍƒCƒ[ƒWƒoƒX‚É‚‚ê—¬‚·‚±‚Æ‚É‚µ‚Ü‚·B
	** POPLAR_H ‚ÌƒCƒ[ƒWƒoƒX‚É‚Í‰½‚àŒ‹ü‚³‚ê‚Ä‚¢‚È‚¢‚Ì‚ÅA‚±‚ê‚Å‚à
	** “®ì‚µ‚Ü‚·B(‹v•Û”Ž)
	*/
	/* 1998/01/26 Vmn == 0x8000 ‚ÅƒfƒR[ƒhƒ`ƒFƒbƒN‚ð‚·‚é‚ÆAƒGƒ‰[‚É‚È‚è‚Ü‚·B
	** ‚±‚Ì‘Îô‚ÍA StartDecode() ‚Ì•û‚Ås‚¤‚±‚Æ‚É‚µ‚Ü‚·B
	*/
	CodecCDCR_Status[codec_type] &= ~ERCHK0_BIT;		/**0x0010 ƒGƒ‰[ƒ`ƒFƒbƒN(0:’Êí, 1:‰æ‘œƒf[ƒ^o—Í‚¹‚¸)*/
#else
	CodecCDCR_Status[codec_type] |= ERCHK0_BIT;		/**0x0010 ƒGƒ‰[ƒ`ƒFƒbƒN(0:’Êí, 1:‰æ‘œƒf[ƒ^o—Í‚¹‚¸)*/
#endif /* (PRO_COM_CODEC_TYPE == MN86064) */
#endif
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR],
		  CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}


/*************************************************************************
	module		:[•„†•ÏŠ·—p‚ÉCDCR(•„†‰», •œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^)‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É‰æ‘œ“ü—ÍŒo˜H•‰æ‘œo—ÍŒo˜H‚ðÝ’è‚·‚é
		2.ƒGƒ‰[ƒ‰ƒCƒ“‚Ìˆ—‚ðÝ’è‚·‚é
		3.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_stup.c‚Ì
		WORD far CodecCodeConvertSetup
		(struct CodecCodeConvertParameterBlk_t *)
		‚©‚çCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void CodecCodeConvertCDCR_Setup(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
	CodecCDCR_Status[codec_type] = 0;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN00_BIT;		/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN01_BIT;		/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**‰æ‘œo—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMOT00_BIT;		/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMOT01_BIT;		/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**ƒGƒ‰[ˆ—‚ð”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚ÉÝ’è‚·‚é*/

#if (0)
** 	/* ƒfƒR[ƒhƒGƒ‰[ŽžAu‘Oƒ‰ƒCƒ“’u‚«Š·‚¦^”’ƒ‰ƒCƒ“’u‚«Š·‚¦v‚ðƒƒ‚ƒŠƒXƒCƒbƒ`‘I‘ð‰Â”\‚É‚·‚éB
** 	** By O.Kimoto 1998/03/20
** 	*/
** 	CodecCDCR_Status[codec_type] |= ERROR0_BIT;		/**0x0001 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
#else
	if (CHK_ErrorLineReplace() == 1) {	/* ”’ƒ‰ƒCƒ“’u‚«Š·‚¦‚È‚ç‚Î */
		CodecCDCR_Status[codec_type] |= ERROR0_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
	else {	/* ‘Oƒ‰ƒCƒ“’u‚«Š·‚¦ */
		CodecCDCR_Status[codec_type] &= ~ERROR0_BIT;		/**0x0100 ƒGƒ‰[ˆ—(0:‘Oƒ‰ƒCƒ“’u‚«Š·‚¦, 1:”’ƒ‰ƒCƒ“’u‚«Š·‚¦)*/
	}
#endif

	/**•„†‰»‚Ì‚Æ‚«•„†ƒf[ƒ^‚ðƒoƒCƒg’PˆÊ‚ÅI—¹‚·‚é‚æ‚¤‚ÉƒtƒBƒ‹ƒrƒbƒg‚ð‚Â‚¯‚é*/
	CodecCDCR_Status[codec_type] |= OCT0_BIT;		/**0x0020 ƒIƒNƒeƒbƒgƒ‚[ƒh(0:’Êí, 1:ƒIƒNƒeƒbƒg‰»)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR], CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}


/*************************************************************************
	module		:[ƒf[ƒ^“]‘——p‚ÉCDCR(•„†‰», •œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^)‚ðÝ’è‚·‚é]
	function	:[
		1.‘åˆæ•Ï”‚É‰æ‘œ“ü—ÍŒo˜H•‰æ‘œo—ÍŒo˜H‚ðÝ’è‚·‚é
		2.Ý’è’l‚ðƒ|[ƒg‚Éo—Í‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
		CodecCDCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_stup.c‚Ì
		WORD far CodecDataTransferSetup
		(struct CodecDataTransferParameterBlk_t *)
		‚©‚çCall‚³‚ê‚é
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[¬’J³Ž÷]
*************************************************************************/
void CodecDataTransferCDCR_Setup(UBYTE codec_type)	/*Žg—p‚·‚éƒR[ƒfƒbƒN*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ƒn[ƒhƒR[ƒfƒbƒN‚PŒÂŽg—p‚Ìê‡‚Íƒ`ƒƒƒ“ƒlƒ‹‚P‚ðƒfƒR[ƒh—p‚Æ‚·‚é*/
	codec_type = SCANNER_CODEC;	/** ƒn[ƒhƒR[ƒfƒbƒN‚ðƒXƒLƒƒƒi[ƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚P‚ÅŒÅ’è‚·‚é */
	CodecCDCR_Status[codec_type] &= 0x00FF;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^ ƒ`ƒƒƒ“ƒlƒ‹‚P‚ð‰Šú‰»*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN10_BIT;		/**0x4000 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN11_BIT;		/**0x8000 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT10_BIT;	/**0x0400 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT11_BIT;	/**0x0800 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
#else	/** ’Êí‚Í‚»‚ê‚¼‚ê‚ÌƒR[ƒfƒbƒN‚Ìƒ`ƒƒƒ“ƒlƒ‹‚O‚ðŽg—p‚·‚é */
	CodecCDCR_Status[codec_type] = 0;		/**R/W •„†‰»,•œ†‰»ƒRƒ“ƒgƒ[ƒ‹ƒŒƒWƒXƒ^*/
	/**‰æ‘œ“ü—ÍŒo˜H‚ðƒVƒXƒeƒ€ƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN00_BIT;		/**0x0040 †®‰æ‘œƒf[ƒ^“ü—ÍŒo˜H‚ð3‚É‚·‚é*/
	CodecCDCR_Status[codec_type] |= IMIN01_BIT;		/**0x0080 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
	/**‰æ‘œo—ÍŒo˜H‚ðƒCƒ[ƒWƒoƒX‚ÉÝ’è‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT00_BIT;	/**0x0004 †®‰æ‘œƒf[ƒ^o—ÍŒo˜H‚ð0‚É‚·‚é*/
	CodecCDCR_Status[codec_type] &= ~IMOT01_BIT;	/**0x0008 †¶(0:ƒCƒ[ƒWƒoƒX, 1:-, 2:-, 3:ƒVƒXƒeƒ€ƒoƒX)*/
#endif
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CDCR],
		  CodecCDCR_Status[codec_type]);			/**Ý’è’l‚ðƒ|[ƒg‚Éƒ‰ƒCƒg‚·‚é*/
}
