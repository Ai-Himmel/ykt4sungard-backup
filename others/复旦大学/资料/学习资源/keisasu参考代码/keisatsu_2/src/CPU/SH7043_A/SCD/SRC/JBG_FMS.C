/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/23
*        FILE NAME:  jbg_fms.c
*       Task ID No:
*      DESCRIPTION:  ‚e‚l‚r(floating marker segment)
*                    T.82(JBIG)‚É‚æ‚é‚e‚l‚r‚ğ‘€ì‚·‚éˆ×‚Ìƒtƒ@ƒCƒ‹ŒQ
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚e‚l‚rì¬
	]
	function	:[
		1.‚r‚c‚m‚n‚q‚l‚Ìì¬
		2.‚r‚c‚q‚r‚s‚Ìì¬
		3.‚`‚s‚l‚n‚u‚dƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬
		4.‚m‚d‚v‚k‚d‚mƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬
		5.‚b‚n‚l‚l‚d‚m‚sƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬
	]
	return		:[‚È‚µ]
	common		:[
		JBG_RequestSDRST
		JBG_RequestSDNORM
		JBG_RequestATMOVE
		JBG_RequestNEWLWN
		JBG_RequestCOMMENT
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_MakeFMS(void)
{
	if (JBG_RequestSDRST) {	/** ‚r‚c‚q‚r‚s‚Ìì¬—v‹B•Ï”‚Ì‰Šú‰»‚ÍAŸ‚ÌƒXƒgƒ‰ƒCƒv‚Ìæ“ª‚Ås‚¤ */
		JBG_WriteSDRST();
	}
	else {
		if (JBG_RequestSDNORM) {	/** ‚r‚c‚m‚n‚q‚l‚Ìì¬—v‹B•Ï”‚Ì‰Šú‰»‚ÍAŸ‚ÌƒXƒgƒ‰ƒCƒv‚Ìæ“ª‚Ås‚¤ */
			JBG_WriteSDNORM();
		}
	}
	while (JBG_RequestATMOVE) {	/** ‚`‚s‚l‚n‚u‚dƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬—v‹ */
		JBG_RequestATMOVE--;	/** ‚`‚s‚l‚n‚u‚d‚Ìì¬—v‹•Ï”‚ÌŒ¸Z */
		JBG_WriteATMOVE();
	}
	while (JBG_RequestNEWLWN) {	/** ‚m‚d‚v‚k‚d‚mƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬—v‹ */
		JBG_RequestNEWLWN--;	/** ‚m‚d‚v‚k‚d‚m‚Ìì¬—v‹•Ï”‚ÌŒ¸Z */
		JBG_WriteNEWLEN();
	}
	while (JBG_RequestCOMMENT) {	/** ‚b‚n‚l‚l‚d‚m‚sƒtƒ[ƒeƒBƒ“ƒOƒ}[ƒJ[ƒZƒOƒƒ“ƒg‚Ìì¬—v‹ */
		JBG_RequestCOMMENT--;	/** ‚b‚n‚l‚l‚d‚m‚s‚Ìì¬—v‹•Ï”‚ÌŒ¸Z */
		JBG_WriteCOMMENT();
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚r‚c‚q‚r‚s‚Ìo—Í
	]
	function	:[
		1.‚r‚c‚q‚r‚s‚Ìo—Í
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/15]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_WriteSDRST(void)
{
	JBG_WriteBid(JBG_SYMBOL_ESC);
	JBG_WriteBid(JBG_SYMBOL_SDRST);
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚r‚c‚m‚n‚q‚l‚Ìo—Í
	]
	function	:[
		1.‚r‚c‚m‚n‚q‚l‚Ìo—Í
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/15]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_WriteSDNORM(void)
{
	JBG_WriteBid(JBG_SYMBOL_ESC);
	JBG_WriteBid(JBG_SYMBOL_SDNORM);
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚`‚s‚l‚n‚u‚d‚Ìo—Í
	]
	function	:[
		1.‚`‚s‚l‚n‚u‚d‚Ìo—Í
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/17]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_WriteATMOVE(void)
{
	JBG_WriteBid(JBG_SYMBOL_ESC);
	JBG_WriteBid(JBG_SYMBOL_ATMOVE);
}

/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚m‚d‚v‚k‚d‚m‚Ìo—Í
	]
	function	:[
		1.‚m‚d‚v‚k‚d‚m‚Ìo—Í
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/17]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_WriteNEWLEN(void)
{
	JBG_WriteBid(JBG_SYMBOL_ESC);
	JBG_WriteBid(JBG_SYMBOL_NEWLEN);
	JBG_WriteBid((UBYTE)(JBG_BIH.YD >> 24));
	JBG_WriteBid((UBYTE)(JBG_BIH.YD >> 16));
	JBG_WriteBid((UBYTE)(JBG_BIH.YD >> 8));
	JBG_WriteBid((UBYTE)(JBG_BIH.YD));
}

/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚b‚n‚l‚l‚d‚m‚s‚Ìo—Í
	]
	function	:[
		1.‚b‚n‚l‚l‚d‚m‚s‚Ìo—Í
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/17]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_WriteCOMMENT(void)
{
	JBG_WriteBid(JBG_SYMBOL_ESC);
	JBG_WriteBid(JBG_SYMBOL_COMMENT);
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚`‚s‚l‚n‚u‚d‚ğÄƒZƒbƒg‚·‚é
	]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		‚e‚l‚r‚Å‚ ‚é‚±‚Æi‚r‚c‚d‚Ì’†‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚È‚¢‚±‚Æj
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/30]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_ResetATMOVE(void)
{
	UDWORD bid;
	UDWORD yat;

	JBG_ATMOVE.Esc = JBG_SYMBOL_ESC;
	JBG_ATMOVE.Atmove = JBG_SYMBOL_ATMOVE;
	yat = 0;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yat += bid << 24;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yat += bid << 16;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yat += bid << 8;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yat += bid;
	JBG_ATMOVE.Yat = yat;
	JBG_ATMOVE.Tx = JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	if (JBG_ATMOVE.Tx > JBG_BIH.MX) {
		JBG_DecodeEndStatus |= JBG_BIT_ERROR;	/** ƒfƒR[ƒhƒGƒ‰[”­¶ */
	}
	JBG_ATMOVE.Ty = JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚b‚n‚l‚l‚d‚m‚s‚ğÄƒZƒbƒg‚·‚é
	]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		‚e‚l‚r‚Å‚ ‚é‚±‚Æi‚r‚c‚d‚Ì’†‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚È‚¢‚±‚Æj
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/30]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_ResetCOMMENT(void)
{
	UDWORD bid;
	UDWORD lc;

	JBG_COMMENT.Esc = JBG_SYMBOL_ESC;
	JBG_COMMENT.Comment = JBG_SYMBOL_COMMENT;
	lc = 0;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	lc += bid << 24;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	lc += bid << 16;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	lc += bid << 8;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	lc += bid;
	JBG_COMMENT.Lc = lc;
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚m‚d‚v‚k‚d‚m‚ğÄƒZƒbƒg‚·‚é
	]
	function	:[
		1.
	]
	return		:[]
	common		:[
		JBG_BIH.YD
	]
	condition	:[
		‚e‚l‚r‚Å‚ ‚é‚±‚Æi‚r‚c‚d‚Ì’†‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚È‚¢‚±‚Æj
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/30]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_ResetNEWLEN(void)
{
	UDWORD bid;
	UDWORD yd;

	JBG_NEWLEN.Esc = JBG_SYMBOL_ESC;
	JBG_NEWLEN.Newlen = JBG_SYMBOL_NEWLEN;
	yd = 0;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yd += bid << 24;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yd += bid << 16;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yd += bid << 8;
	bid = (UDWORD)JBG_ReadBID();	/** ‚a‚h‚c‚©‚ç‚PƒoƒCƒg“Ç‚İ‚Æ‚é */
	yd += bid;
	JBG_NEWLEN.Yd = yd;
	JBG_BIH.YD = yd;
}


