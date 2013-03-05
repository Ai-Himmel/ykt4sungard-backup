/*************************************************************************
*	System		: EVA
*	File Name	: lst_def.h
*	Author		: ‚–Ø@i
*	Date		: 1997/10/09
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_DEF_H
	#define	LST_DEF_H	1

#include "\src\atlanta\define\std.h"

/************************************************************************
 * ƒŠƒXƒgƒvƒŠƒ“ƒg—]”’‚ÌÝ’è												*
 ************************************************************************/
#define	LST_LEFT_WHITE_A4			14			/*¶—]”’A4 ’PˆÊ‚Í‚‚*/	/* 48->14 */

#define	LST_COLUM					80			/* ƒŠƒXƒgƒvƒŠƒ“ƒg—pƒoƒbƒtƒ@ */

#define	LST_BYTE_SIZE				256				/* ÌßØÝÀ°Ê°ÄÞ‚Ì1×²ÝÄÞ¯Ä”^8 */
#define	LST_IMAGE					(LST_BYTE_SIZE+8)	/* ƒeƒXƒgƒvƒŠƒ“ƒg—pƒoƒbƒtƒ@ */

/* ƒŠƒXƒgs”(100%) */
#define	LST_A4_LEN					68				/* A4—pŽ†‚Ìs”*/
#define	LST_LETTER_LEN				(LST_A4_LEN-4)	/* ÚÀ°—pŽ†‚Ìs”*/
#define	LST_LEGAL_LEN				(LST_A4_LEN+14)	/* Ø°¶ÞÙ—pŽ†‚Ìs”*/

/* ƒŠƒXƒgs”(75%) */
#define	LST_A4_LEN_75				91				/* A4—pŽ†‚Ìs” */
#define	LST_LETTER_LEN_75			85				/* ÚÀ°—pŽ†‚Ìs” */
#define	LST_LEGAL_LEN_75			110				/* Ø°¶ÞÙ—pŽ†‚Ìs” */
#define	LST_A4R_LEN_75				63				/* A4R—pŽ†‚Ìs” */

/* •¶Žš—ñ”äŠrŒ‹‰Ê(“d˜b’ H) */
#define	LST_LT						0				/* String1 < String2 */
#define	LST_EQ						1				/* String1 == String2 */
#define	LST_GT						2				/* String1 > String2 */

/* ƒAƒXƒL[‡ƒ\[ƒg‚Ì”äŠr•¶Žš”*/
#define	LST_COMP_LEN				16

/* ˆóü^•¶Žš—ñì¬‚Ì—¼•û‚ª•K—v‚È’ •[‚ÌŽÀsƒ‚[ƒh ex)ƒ‚ƒjƒ^[ƒŒƒ|[ƒg“™ */
#define	LST_MODE_PRINT				0			/* ˆóü */
#define	LST_MODE_LINE				1			/* ‚Psì¬ */

/* ƒOƒ‹[ƒvEƒŠƒXƒg */
#define	GROUP_END					0xff		/* ¸ÞÙ°ÌßØ½Ä »°Á‚Ì´ÝÄÞ */
#define	LST_SPEED					0			/* ½Ëß°ÄÞÀÞ²ÔÙ */
#define	LST_ONETOUCH				1			/* ÜÝÀ¯ÁÀÞ²ÔÙ */

/* ‚d‚m‚cƒ}[ƒN */
#define	NULL_PT						'\x0'		/* ‚m‚t‚k‚kƒ|ƒCƒ“ƒ^[ */
#define	LST_CR						'\x0D'		/* ƒLƒƒƒŠƒbƒWƒŠƒ^[ƒ“ */
#define	LST_LF						'\x0A'		/* ƒ‰ƒCƒ“ƒtƒB[ƒh */
#define	LST_EOT						'\x04'		/* ƒGƒ“ƒh ƒIƒu ƒeƒLƒXƒg */

#define	LST_GROUP_BIT				32			/* ƒOƒ‹[ƒv‚Ìƒrƒbƒg” */

/* “ú•to—Í•ÒW•û–@ */
#define	LST_YYMMDD					0			/* ”NŒŽ“úT */
#define	LST_DDHHMM					1			/* “úŽž•ª */
#define	LST_MMDDHHMM				2			/* ŒŽ“úŽž•ª */

/* ”NŒŽA—j“ú */
#define	LST_A_NICHI					0x08		/* ANK '“ú' */
#define	LST_A_GETU					0x09		/* ANK 'ŒŽ' */
#define	LST_A_KA					0x0A		/* ANK '‰Î' */
#define	LST_A_SUI					0x0B		/* ANK '…' */
#define	LST_A_MOKU					0x0C		/* ANK '–Ø' */
#define	LST_A_KIN					0x0D		/* ANK '‹à' */
#define	LST_A_DOU					0x0E		/* ANK '“y' */
#define	LST_A_NEN					0x0F		/* ANK '”N' */

/* “ÁŽê•¶Žš */
#define	LST_A_TENTEN				0x10		/* ANK 'd' */

/* Œrü */
#define	LST_KLINE7					0x15		/*†®*/
#define	LST_KLINE4					0x16		/*†¾*/
#define	LST_KLINE1					0x17		/*†¶*/
#define	LST_KLINE_					0x18		/*†¢*/
#define	LST_KLINE8					0x19		/*†Î*/
#define	LST_KLINE5					0x1a		/*†Þ*/
#define	LST_KLINE2					0x1b		/*†Ö*/
#define	LST_KLINE9					0x1c		/*†²*/
#define	LST_KLINE6					0x1d		/*†Æ*/
#define	LST_KLINE3					0x1e		/*†º*/
#define	LST_KLINEI					0x1f		/*†¤*/

/* •¶ŽšCü‚ÌŽí—Þ */
#define	LST_NOT						0x30		/* Cü‚È‚µ */
#define	LST_XXX_XXX_KAN				0x31		/* Š¿Žš */
#define	LST_XXX_TWI_XXX				0x32		/* ‰¡”{Šp */
#define	LST_XXX_TWI_KAN				0x33		/* ‰¡”{Šp{Š¿Žš */
#define	LST_MES_XXX_XXX				0x34		/* –ÔŠ| */
#define	LST_MES_XXX_KAN				0x35		/* –ÔŠ|{Š¿Žš */
#define	LST_MES_TWI_XXX				0x36		/* –ÔŠ|{‰¡”{Šp */
#define	LST_MES_TWI_KAN				0x37		/* –ÔŠ|{‰¡”{Šp{Š¿Žš */
#define	LST_INV_XXX_XXX				0x38		/* ”½“] */
#define	LST_INV_XXX_KAN				0x39		/* ”½“]{Š¿Žš */
#define	LST_INV_TWI_XXX				0x3A		/* ”½“]{‰¡”{Šp */
#define	LST_INV_TWI_KAN				0x3B		/* ”½“]{‰¡”{Šp{Š¿Žš */

#define	LST_DATE_HOUR_MINUTE		0			/* “úŽž•ªŒ`Ž® */
#define	LST_HOUR_MINUTE				1			/* Žž•ªŒ`Ž® */

/************************************************************************
 * Œ»ÝŽžŠÔ•\Ž¦ƒpƒ^[ƒ“													*
*************************************************************************/

#define	TIME_NOT			0					/* --:--             */
#define	TIME_PRT_1			1					/* Jan 01 1999 99:99 */
#define	TIME_PRT_2			2					/* 99/99 99:99 		 */
#define	TIME_PRT_3			3					/* 99, 99:99		 */


/************************************************************************
 * Žw’èŽžŠÔ•\Ž¦ƒpƒ^[ƒ“													*
*************************************************************************/
#define	LST_PTN_DDHHMM		0					/* 99,99:99				*/
#define	LST_PTN_MMDDHHMM	1					/* 99/99,99:99			*/


/************************************************************************
 * ƒŠƒXƒgƒvƒŠƒ“ƒg–ß‚è’l													*
*************************************************************************/
#define	LST_PRT_CONTINUE			0			/* ƒŠƒXƒgƒvƒŠƒ“ƒg‰üƒy[ƒW */
#define	LST_PRT_END					1			/* ƒŠƒXƒgƒvƒŠƒ“ƒg³íI—¹ */
#define	LST_PRT_ERROR				2			/* ƒŠƒXƒgƒvƒŠƒ“ƒgƒGƒ‰[I—¹ */

/************************************************************************
 * 1•Åƒf[ƒ^ˆóŽš”														*
*************************************************************************/

#define		PRT_DATA_MAX			28

/************************************************************************
 * ’ZkAƒƒ“ƒ^ƒbƒ`														*
*************************************************************************/
#define		NO_DATA		0xf0
/************************************************************************
 * ƒŠƒXƒg”Ô†(ƒŠƒXƒgŽí•Ê)												*
*************************************************************************/
/* New Define By M.IIDA '98.04.10 */
/* ˆê”ÊƒŠƒXƒg */					/* ”Ô†‚Ífile.h‚Æd‚È‚ç‚È‚¢‚æ‚¤‚É‚·‚é‚±‚Æ */
#define	LST_JOURNAL_LIST				20		/* ’ÊMŠÇ—ƒŒƒ|[ƒgu‘—MŽóMv	*/
	#define	LST_AUTO_JOURNAL				1		/* Ž©“®o—Í */
	#define	LST_MANU_JOURNAL				2		/* Žè“®o—Í	*/
#define	LST_SPEEDDIAL_LIST				21		/* ’Zkƒ_ƒCƒ„ƒ‹ƒŠƒXƒg			*/
#define	LST_ONETOUCHDIAL_LIST			22		/* ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg		*/
#define	LST_PROGRAM_LIST				23		/* ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`ƒŠƒXƒg	*/
#define	LST_FUNCTION_LIST				24		/* ‹@”\ƒŠƒXƒg					*/
#define	LST_PARAMETER_LIST				25		/* ‹@ŠíÝ’èƒŠƒXƒg				*/
#define	LST_RESERVECMD_LIST				26		/* ’ÊM—\–ñƒŠƒXƒg				*/
#define	LST_TTI_LIST					27		/* ”­MŒ³ƒŠƒXƒg					*/
#define	LST_COVERPAGE_LIST				28		/* ƒJƒo[ƒy[ƒW					*/
#define LST_F_CODE_BOX_LIST				29		/* ‚eƒR[ƒhƒ{ƒbƒNƒXƒŠƒXƒg		*/
#define LST_F_CODE_DOC_LIST				30		/* ‚eƒR[ƒh’~ÏŒ´eƒŠƒXƒg		*/
#define	LST_BLOCK_JUNK_LIST				31		/* ƒWƒƒƒ“ƒNƒ[ƒ‹–hŽ~ƒŠƒXƒg		*/
#define	LST_CALLERID_LIST				32		/* ‚b‚‚Œ‚Œ‚…‚’ ‚h‚cƒŠƒXƒg		*/

/* “dŒ¹ONŽž‚Éo—Í‚³‚ê‚éƒŠƒXƒg */
#define LST_DELPOLLING_NOTICE			40		/* ƒ|[ƒŠƒ“ƒOŒ´eÁ‹Ž’Ê’m	*/
	#define LST_DEL_POLLING					1		/* ƒ|[ƒŠƒ“ƒOŒ´e‚Ì‚ÝÁ‹Ž */
	#define LST_DEL_DBPOLLING				2		/* ŒŸõƒ|[ƒŠƒ“ƒOŒ´e‚Ì‚ÝÁ‹Ž */	
	#define LST_DEL_ALL_POLLING				3		/* ƒ|[ƒŠƒ“ƒOAŒŸõƒ|[ƒŠƒ“ƒO*/
#define	LST_DELMEMORYRCV_NOTICE			41		/* ‘ãsŽóMÁ‹Ž’Ê’m			*/
#define	LST_DELRESERVECMD_NOTICE		42		/* ’ÊM—\–ñÁ‹Ž’Ê’m			*/
#define LST_DEL_FCODE_BOX_DOC_NOTICE	43		/* ‚eƒR[ƒhŒ´eÁ‹Ž’Ê’m 	*/
	#define LST_DEL_ALL_FCODE_BOX			0xFF	/* ‘S‚Ä‚Ì‚eƒR[ƒhŒ´eÁ‹Ž’Ê’mo—Í—v‹ */

/* MainTask‚ÅŽ©“®‚Åo—Í‚³‚ê‚éƒŠƒXƒg */
#define	LST_CHKMSG						50		/* Œ´e–³‚µƒ`ƒFƒbƒNƒƒbƒZ[ƒW	*/
#define	LST_MANURX_CHKMSG				51		/* Žè“®ŽóMƒ`ƒFƒbƒNƒƒbƒZ[ƒW(Œ´e–³)	*/
#define	LST_DOC_CHKMSG					52		/* Œ´e•t‚«ƒ`ƒFƒbƒNƒƒbƒZ[ƒW	*/
#define	LST_TCR							53		/* Œ´e–³‚µ‘—MØ	*/
#define	LST_DOC_TCR						54		/* Œ´e•t‚«‘—MØ	*/
#define LST_FCODE_BOXRCV_NOTICE			55		/* ‚eƒR[ƒhŽóM’Ê’m		*/
#define	LST_SEC_RX_MEMOVER_CHKMSG		56		/* ¾·­ØÃ¨ŽóMÓ°ÄÞ’†‚ÌÒÓØ-µ°ÊÞ° */
#define	LST_SCANTX_CHKMSG				57		/* ƒXƒLƒƒƒi‘—Mƒ`ƒFƒbƒNƒƒbƒZ[ƒW(Œ´e–³)	*/
#define	LST_SCANTX_TCR					58		/* ƒXƒLƒƒƒi‘—M‚Ì‘—MØ(Œ´e–³)	*/
	/* LST_SCANTX_CHKMSG¥LST_SCANTX_TCRŽž‚ÍASubMessage2‚É‚ÍAJournal”Ô†‚ð“n‚· */

/* ƒT[ƒrƒXEƒtƒ@ƒ“ƒNƒVƒ‡ƒ“EƒŠƒXƒg */
#define LST_PATTERN_PRINT				90	   	/* ƒeƒXƒgƒvƒŠƒ“ƒg(1-8)		*/
	#define LST_PATTERN1					1		/* ƒpƒ^[ƒ“‚P			*/
	#define LST_PATTERN2					2		/* ƒpƒ^[ƒ“‚Q			*/
	#define LST_PATTERN3					3		/* ƒpƒ^[ƒ“‚R			*/
	#define LST_PATTERN4					4		/* ƒpƒ^[ƒ“‚S			*/
	#define LST_PATTERN5					5		/* ƒpƒ^[ƒ“‚T			*/
	#define LST_PATTERN6					6		/* ƒpƒ^[ƒ“‚U			*/
	#define LST_PATTERN7					7		/* ƒpƒ^[ƒ“‚V			*/
	#define LST_PATTERN8					8		/* ƒpƒ^[ƒ“‚W			*/
	#define LST_PATTERN10					10		/* ‚o‚b‚©‚ç‚ÌŠiŽqÊßÀ°ÝÌßØÝÄ	*/
	#define LST_PATTERN11					11		/* ‚o‚b‚©‚ç‚Ì¡–ÚÊßÀ°ÝÌßØÝÄ	*/
#define LST_T30MONITOR					91		/* ‚s‚R‚Oƒ‚ƒjƒ^				*/
#define LST_FACT_MENU					92		/* Factory Menu(Function List) */
#define LST_MEM_SW						93		/* ƒƒ‚ƒŠƒXƒCƒbƒ`			*/
#define	LST_CL1_ONLINE_MONITOR	 		94		/* ƒNƒ‰ƒX‚PƒIƒ“ƒ‰ƒCƒ“ƒ‚ƒjƒ^|  */
#define	LST_SERVICE_LIST				95		/* ƒT[ƒrƒXƒŒƒ|[ƒg 		*/
#define LST_MEMORY_DUMP					96		/* ƒƒ‚ƒŠƒ_ƒ“ƒvƒŠƒXƒg   	*/
#define LST_ORDER_SHEET					97		/* Á–Õ•i”­’ƒV[ƒg			*/

/* íœ—\’èƒŠƒXƒg€–Ú ----------------------------------*/
#define	LST_EXIT						-1		/* EXIT_MESSAGE				*/
#define	LST_TXCONF_REPORT				2		/* TRANSMIT CONF.REPORT		*/
#define	LST_TXJOURNAL_LIST				3		/* ’ÊMŠÇ—ÚÎß°Äu‘—Mv	*/
#define	LST_RXJOURNAL_LIST				4		/* ’ÊMŠÇ—ÚÎß°ÄuŽóMv	*/
#define	LST_GROUP_LIST					8		/* ƒOƒ‹[ƒvƒŠƒXƒg			*/
#define	LST_MAILBOX_LIST				12		/* e“WŽÒƒŠƒXƒg				*/
#define	LST_SECURERCV_NOTICE			15		/* e“WŽóM’Ê’m				*/
#define	LST_DELSECURE_NOTICE			16		/* e“WŽóMÁ‹Ž’Ê’m			*/
#define	LST_TXCONFJOURNAL_LIST			19		/* ‘—MŠm”FƒŒƒ|[ƒg			*/
#define	LST_DOC_CHECKMSG				20		/* Áª¯¸Ò¯¾°¼ÞA ¹ÞÝº³		*/
#define	LST_COMMERR_CHECKMSG			21		/* Áª¯¸Ò¯¾°¼ÞB º³¼Ý			*/
#define	LST_MRYOVER_CHECKMSG			22		/* Áª¯¸Ò¯¾°¼ÞC ÒÓØµ°ÊÞ°		*/
#define	LST_MRYINIT_CHECKMSG			23		/* Áª¯¸Ò¯¾°¼ÞD ÒÓØ²Æ¼¬Ù		*/
#define	LST_MNLERR_CHECKMSG				24		/* Áª¯¸Ò¯¾°¼ÞE Žè“®‘—M´×°	*/
#define	LST_RXMRYOVER_CHECKMSG			25		/* Áª¯¸Ò¯¾°¼ÞF ŽóMÒÓØµ°ÊÞ°	*/
/*#define LST_CATCHPHONE_CHKMSG			26*/	/* Áª¯¸Ò¯¾°¼ÞG ·¬¯ÁÎÝ		*/
/*#define LST_LOSTPAGE_CHKMSG			27*/	/* Áª¯¸Ò¯¾°¼ÞI ŽóMÍß°¼•´Ž¸	*/
#define LST_POWEROFF_NOTICE				42		/* ’â“dŒŸo’Ê’m				*/
/*#define LST_REMOTEFAX_NOTICE			44		   ØÓ°ÄÌ§¸½Œ´eÁ‹Ž’Ê’m		*/
#define	LST_MONITOR_REPORT				95		/* ÓÆÀ°ÚÎß°Ä(ON‚ÌŒ´e–³‚µŽž)*/
#define		LST_DELCONTPOLLCMD_NOTICE	99		/* ˜A‘±ƒ|[ƒŠƒ“ƒOƒRƒ}ƒ“ƒh	*/
#define	LST_MANUAL_TXCONF_REPORT		100		/* Žè“®‘—M‘—MØ			*/
#define LST_DEL_DB_POLLING				104		/* ŒŸõŒ´eÁ‹Ž’Ê’m			*/

/* íœ—\’èƒŠƒXƒg€–Ú -------------------------  I—¹  ---------*/

/*-------------------------*/
/* ‹@ŠíÝ’èƒŠƒXƒg—p’è‹`  @*/
/*-------------------------*/
#define	LST_PRM_TTI_ID				1			/* ”­MŒ³–¼					*/
#define	LST_PRM_SECUREDOCHOLD		2			/* e“WŽóM‹L‰¯ŠúŠÔ			*/
#define	LST_PRM_JOURNALAUTOPRT		3			/* ’ÊMŠÇ—‹L˜^Ž©“®			*/
#define	LST_PRM_CONFREPORT			4			/* ’ÊMØ					*/
#define	LST_PRM_PHONETYPE			5			/* ’ÊM‰ñü					*/
#define	LST_PRM_TXRXTYPE			6			/* ‘—MEŽóM				*/
#define	LST_PRM_LINETYPE			7			/* ‰ñüƒ^ƒCƒv				*/
#define	LST_PRM_RECEIVEMODE			8			/* ŽóMƒ‚[ƒh				*/
#define	LST_PRM_SCANNERWIDTH		9			/* “ÇŽæƒTƒCƒY				*/
#define	LST_PRM_PRIMARYMODE			10			/* —Dæ•¶ŽšƒTƒCƒY			*/
#define	LST_PRM_CONTRAST			11			/* —DæŒ´e”Z“x				*/
#define	LST_PRM_REDUCTIONRATE		12			/* ƒvƒŠƒ“ƒgk¬—¦			*/
#define	LST_PRM_ROTATEMARGIN		13			/* ‰ñ“]ƒ}[ƒWƒ“				*/
#define	LST_PRM_PAGECOMPOUND		14			/* ƒy[ƒW‡¬				*/
#define	LST_PRM_DIALINGPAUSE		15			/* ƒ|[ƒYŽžŠÔ				*/
#define	LST_PRM_RINGGINGTIMES		16			/* ŒÄoƒxƒ‹‰ñ”				*/
#define	LST_PRM_REDIALTIMES			17			/* ƒŠƒ_ƒCƒ„ƒ‹‰ñ”			*/
#define	LST_PRM_ECMMODE				18			/* ECMƒ‚[ƒh				*/
#define	LST_PRM_PASSCODE			19			/* ƒpƒXƒR[ƒh				*/
#define	LST_PRM_CLOSEDNETWORK		20			/* •Âˆæ’ÊM					*/
#define	LST_PRM_SECURITYTX			21			/* ƒpƒXƒ[ƒh‘—M			*/
#define	LST_PRM_BLOCKJUNKFAX		22			/* ƒ_ƒCƒŒƒNƒgƒ[ƒ‹			*/
#define	LST_PRM_REMOTEDIAGNOSTIC	23			/* ƒŠƒ‚[ƒgf’f				*/
#define	LST_PRM_MEMORYTX			24			/* ƒƒ‚ƒŠ‘—M				*/
#define	LST_PRM_STAMP				25			/* ÏƒXƒ^ƒ“ƒv				*/
#define	LST_PRM_RS232C				26			/* ‚q‚r‚Q‚R‚Q‚b				*/
#define	LST_PRM_DIALIN				27			/* ƒ_ƒCƒ„ƒ‹ƒCƒ“				*/
#define	LST_PRM_OPERATIONPROTECT	28			/* ƒIƒyƒŒ[ƒVƒ‡ƒ“ƒvƒƒeƒNƒg	*/
#define	LST_PRM_MESAGETRANS			29			/* ƒƒbƒZ[ƒW‘—M			*/
#define	LST_PRM_SILENTOPERATION		30			/* ƒTƒCƒŒƒ“ƒgƒIƒyƒŒ[ƒVƒ‡ƒ“	*/
#define	LST_PRM_COPYREDUCTION		31			/* ƒRƒs[k¬—¦				*/
#define	LST_PRM_PAPERSIZE			32			/* ‹L˜^Ž†ƒy[ƒp[ƒTƒCƒY		*/
#define	LST_PRM_DEPARTMENT			33			/* •”–åŠÇ—ƒZƒbƒg			*/
#define	LST_PRM_DEPARTMENTPROTECT	34			/* •”–åŠÇ—ƒvƒƒeƒNƒg		*/
#define	LST_PRM_REMOTESECURITYRX	35			/* ƒZƒLƒ…ƒŠƒeƒBŽóM			*/
#define	LST_PRM_PIN_ACCESSMODE		36			/* ‚o‚h‚mƒAƒNƒZƒX			*/
#define	LST_PRM_DAYLIGHTSAVING		37			/* ‰ÄŽžŠÔŽ©“®ØŠ·‚¦			*/
#define	LST_PRM_RINGMASTR			38			/* ‚c‚q‚c(ƒŠƒ“ƒOƒ}ƒXƒ^)		*/
#define	LST_PRM_MERCURYPAUSE		39			/* ƒ}[ƒLƒ…ƒŠ[ƒ|[ƒY		*/
#define	LST_PRM_RXALARM				40			/* ŽóMŠ®—¹ƒAƒ‰[ƒ€			*/
#define	LST_PRM_COMPAGES			41			/* –‡”						*/
#define LST_PRM_COPYPROTECT			42			/* ƒRƒs[‹ÖŽ~				*/
#define LST_PRM_PRIMARYTELFAX		43			/* Primary Tel/Fax			*/
#define LST_PRM_SORTINGCOPY			44			/* ƒ\[ƒeƒBƒ“ƒOƒRƒs[		*/

#define	LST_ERR_CODE_MAX			40			/* error code max */

/*------------------------------------------------------------------*/
/* ƒŠƒXƒgƒvƒŠƒ“ƒg—pƒoƒbƒtƒ@								 	 		*/
/*------------------------------------------------------------------*/
union LstBuffer_t {
	struct Code_t {
		  UBYTE Print[LST_COLUM];
		  UBYTE Attribute[LST_COLUM];
		  UBYTE Work[LST_COLUM];
	} S;
	UBYTE Image[LST_IMAGE];
};

/*------------------------------------------------------------------*/
/* ƒLƒƒƒ‰ƒNƒ^‘—M—pƒoƒbƒtƒ@								 	 		*/
/*------------------------------------------------------------------*/
struct TxText_t {
	UBYTE TxText[80];
	UBYTE Attribute[80];
};


/************************************************************************
* DESCRIPTION:	ƒCƒ[ƒW“WŠJ—pƒoƒbƒtƒ@
************************************************************************/
	#define LST_A4_WORD_WIDTH		216				/* TBD */
	#define LST_WORD_WIDTH			304				/* TBD */
	#define	LST_PRM_SPACE			4				/* ‹@ŠíÝ’èƒŠƒXƒg‚ÌsŠuƒhƒbƒg” */

	/* ƒCƒ[ƒWƒvƒŠƒ“ƒg’†‚Éƒy[ƒW‚ÌÅŒã‚Ü‚ÅˆóŽš‚µ‚½ê‡‚Ì•Ô‚è’l‚Æ‚µ‚Ä */
	#define LST_END_OF_PAGE			0x0F

	union FontImageBufferData_t {
		UBYTE	Font[3][16][80];				/* ƒŠƒXƒgƒvƒŠƒ“ƒg—pƒtƒHƒ“ƒgƒCƒ[ƒW */
												/* [0]&[1]=CharaterPrint [2]=CharacterTx */
		UWORD	Image[4][LST_WORD_WIDTH];		/* ƒeƒXƒgƒpƒ^[ƒ“ƒvƒŠƒ“ƒg—p */
		UWORD	HeadImage[LST_WORD_WIDTH];		/* Ã½ÄÊßÀ°ÝÌßØÝÄ‚ÌÍ¯ÄÞ—p  */
		UWORD	ByteImage[LST_PRM_SPACE][40];	/* ‹@ŠíÝ’èƒŠƒXƒg—p  */
	};


	/* ƒGƒ‰[ƒR[ƒhƒe[ƒuƒ‹ */
	struct CodeErr_t {
		UBYTE	*Code;						/* Ši’ÊMƒGƒ‰[ƒR[ƒh */
		UBYTE	GrpNo;		 			 	/* ƒGƒ‰[ƒƒbƒZ[ƒW‘®« */
	};


/************************************************************************
* DESCRIPTION:	ƒCƒ[ƒW“WŠJ—pƒoƒbƒtƒ@
************************************************************************/
	struct LstModelTbl_t {
		CONST UBYTE	*model1;
		CONST UBYTE	*model2;
	};


/************************************************************************
* DESCRIPTION:	ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`ƒŠƒXƒg
************************************************************************/
	#define	LST_DIAL_NO_LEN		40				/* ƒ_ƒCƒ„ƒ‹‚m‚Ši”[Œ…” */
	#define	LST_NOTE_CNT		 3				/* ”õlƒZƒbƒgƒf[ƒ^”	*/


/************************************************************************
* DESCRIPTION:	’ÊMƒGƒ‰[ƒR[ƒh‚l‚`‚w									*
* 				Žg—p‚·‚éƒGƒ‰[ƒR[ƒh‚Í53Ží—Þ							*
************************************************************************/
	#define	ERR_COOD_MAX		53

/************************************************************************
* DESCRIPTION:	‚s‚R‚O													*
************************************************************************/
struct Fcf_Str {
/***	BYTE	Fcf;	1998.8.18 Modify M.Ishibashi ****/
	UBYTE	Fcf;
	UBYTE	StringLength;
	UBYTE	Str[8];
};

#define MODEM_TYPE	0
#define CODE_TYPE	1
#define PAPER_SIZE	2
#define LINE_TIME	3
#define MODE_TYPE	4
#define ECM_TYPE	5

#define RECEIVER	0
#define TRANSMITTER	1

#endif
