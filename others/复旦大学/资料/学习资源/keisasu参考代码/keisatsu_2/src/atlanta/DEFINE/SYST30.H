/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\syst30.h */
#ifndef	syst30_h
	#define	syst30_h

#include	"\src\atlanta\define\sysmax.h"

/************************************************************************
 * T30ÉÇÉjÉ^															*
 * struct SYS_T30MonitorData_t SYB_T30Monitor (By S.K Jan.17,1994)  	*
 * 1993/11/24															*
 * ãgêÏçOçN																*
 ************************************************************************/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/29 Y.Murata */
	struct SYS_T30MonitorData_t{
		UBYTE JournalType;				/* í êMéÌï  */
		UBYTE Index;					/* ÉfÅ[É^éØï  */
		UWORD ReadPointer;
		UWORD WritePointer;
		UWORD A_Pointer;
		UWORD B_Pointer;
		UWORD Flag;
		UWORD BK_Pointer1;
		UWORD BK_Pointer2;
		UWORD BK_Pointer3;
		UWORD BK_Pointer4;
		UBYTE Buffer[SYS_T30MONITOR_BUF_MAX];	/* By S.K Jan.17,1994 */
	};
#else
	struct SYS_T30MonitorData_t{
		UBYTE JournalType;				/* í êMéÌï  */
		UBYTE Index;					/* ÉfÅ[É^éØï  */
		UWORD ReadPointer;
		UWORD WritePointer;
		UBYTE Buffer[SYS_T30MONITOR_BUF_MAX];	/* By S.K Jan.17,1994 */
	};
#endif

/************************************************************************
 * T30ÉÇÉjÉ^ÇÃí êMéÌï 													*
 * unsigned char SYB_T30Monitor.JournalType								*
 * 1993/11/24															*
 * ãgêÏçOçN																*
 ************************************************************************/
#define SYS_T30_TXJOURNAL		0x01	/* TX_mode */
#define SYS_T30_RXJOURNAL   	0x02	/* RX_mode */
#define SYS_T30_EMPTY       	0xFF	/* no data */

/************************************************************************
 * T30ÉÇÉjÉ^ÇÃí êMéÌï 													*
 * unsigned char SYB_T30Monitor.Index									*
 * 1993/11/24															*
 * ãgêÏçOçN																*
 ************************************************************************/
#define SYS_T30_TX_FRAME			0x11
#define	SYS_T30_TX_TCF				0x12
#define SYS_T30_TX_PIX				0x13
#if (PRO_TX_SPEED == V34) || (PRO_MULTI_LINE == ENABLE) /* Added by H.Kubo 1997/08/08 *//* Add MULTI by 1997/09/04 Y.Matsukuma */
#define SYS_T30_TX_CJ				0x14
#define SYS_T30_TX_CI				0x15
#define SYS_T30_TX_ANS				0x16
#endif /* (PRO_TX_SPEED == V34) */


#define SYS_T30_RX_FRAME			0x21
#define SYS_T30_RX_TCF				0x22
#define SYS_T30_RX_PIX				0x23
#if (PRO_TX_SPEED == V34) || (PRO_MULTI_LINE == ENABLE) /* Added by H.Kubo 1997/08/08 *//* Add MULTI by 1997/09/04 Y.Matsukuma */
#define SYS_T30_RX_CJ				0x24
#define SYS_T30_RX_CI				0x25
#define SYS_T30_RX_ANS				0x26
#define SYS_T30_RX_CED				0x27
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_TX_SPEED == V34) || (PRO_MULTI_LINE == ENABLE) /* Added by H.Kubo 1997/08/08 *//* Add MULTI by 1997/09/04 Y.Matsukuma */
#define SYS_T30_V34_TX_RATE			0x30
#define SYS_T30_V34_RX_RATE			0x31
#endif /* (PRO_TX_SPEED == V34) */

#define SYS_T30_START_TIME 	 		0x41
#define SYS_T30_END_TIME   	 		0x42

#define SYS_T30TX_FRAMEBIT  		0x10
#define SYS_T30RX_FRAMEBIT 			0x20
#define SYS_T30_TIMEBIT     		0x40
#define SYS_T30_NOT_END_OF_FRAME	0x00
#define SYS_T30_END_OF_FRAME		0xFF

/************************************************************************
 * T30ÉÇÉjÉ^ÇÃä‘äuéûä‘ï‚ê≥íl											*
 * unsigned char SYB_T30Monitor.Buffer[SYS_T30MONITOR_BUF_MAX]			*
 * 1993/11/24															*
 * ãgêÏçOçN																*
 ************************************************************************/
#define SYS_T30_TIME_ADJ_POS		5
#define	SYS_T30_TIME_ADJ_NEG		-5

#endif
