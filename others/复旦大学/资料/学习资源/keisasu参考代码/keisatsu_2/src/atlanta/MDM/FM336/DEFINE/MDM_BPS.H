#ifndef mdm_bps_h
	#define	mdm_bps_h
/***********************************************************************
*          BY:   
*        DATE:   1999/10/06
* VAR TO HOLD:   unsigned int	TxBaudRate;
* DESCRIPTION:   通信ボーレート
* MODIFICATION:	 久保博 1997/06/19 POPLAR_H への移植
				 POPLAR_B の FCM_DEF.H に追加。
				 番号の振り方も FCM_DEF.H に準ずる。
************************************************************************/


/* For secure update, check the definitions. */
#ifdef BPS14400_V33
#error "BPS14400_V33 is defined in elsewhere."
#endif
#ifdef BPS12000_V33
#error "BPS12900_V33 is defined in elsewhere."
#endif
#ifdef BPS14400_V17
#error "BPS14400_V17 is defined in elsewhere."
#endif
#ifdef BPS12000_V17
#error "BPS12000_V17 is defined in elsewhere."
#endif
#ifdef BPS9600_V17	
#error "BPS9600_V17 is defined in elsewhere."
#endif
#ifdef BPS7200_V17
#error "BPS7200_V17 is defined in elsewhere."
#endif
#ifdef BPS9600_V29
#error "BPS9600_V29 is defined in elsewhere."
#endif
#ifdef BPS7200_V29
#error "BPS7200_V29 is defined in elsewhere."
#endif
#ifdef BPS4800_V27
#error "BPS4800_V27 is defined in elsewhere."
#endif
#ifdef BPS2400_V27
#error "BPS2400_V27 is defined in elsewhere."
#endif
#ifdef BPS300_V21
#error "BPS300_V21 is defined in elsewhere."
#endif

/** V.8 **/
#define		V8_SETUP		92
#define		V8_CLEARDOWN	91
/** V.34 **/
#define		BPS33600_V34	115
#define		BPS31200_V34	114
#define		BPS28800_V34	113
#define		BPS26400_V34	112
#define		BPS24000_V34	111
#define		BPS21600_V34	110
#define		BPS19200_V34	109
#define		BPS16800_V34	108
#define		BPS14400_V34	107
#define		BPS12000_V34	106
#define		BPS9600_V34		105
#define		BPS7200_V34		104
#define		BPS4800_V34		103
#define		BPS2400_V34		102
#define		CLEARDOWN_V34	101
/** V.33 **/
#define		BPS14400_V33	5	/* Old Data = 31 */
#define		BPS12000_V33	4	/* Old Data = 32 */
#define		BPS9600_V33		122	/* Old Data = 34 */
#define		BPS7200_V33		121	/* Old Data = 38 */
/** V.17 **/
#define		BPS14400_V17	9
#define		BPS12000_V17	8
#define		BPS9600_V17		7
#define		BPS7200_V17		6
/** V.29 **/
#define		BPS9600_V29		3
#define		BPS7200_V29		2
#define		BPS4800_V29		131
/** V.27 ter **/
#define		BPS4800_V27		1
#define		BPS2400_V27		0
/** V.21 **/
#define		BPS0_300_V21	141
#define		BPS300_V21		10	/** Channel 2 **/
/** Etc. **/
#define		TX_SINGLE_TONE	154
#define		TX_DUAL_TONE	153
#define		DIALING			152
#define		DTMF_RECEIVER	151
/** V.23 **/
#define		TX1200_V23		162	/* Tx:1200 Rx:75   */
#define		RX1200_V23		161	/* Tx:75   Rx:1200 */

#endif	/* End Of File */

