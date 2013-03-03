/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\time.h */
#ifndef time_h
    #define time_h

/************************************************************************
 * BCDŒ^ŠÔ															*
 * 1993/12/13															*
 * ‹gìON																*
 ************************************************************************/
typedef struct {
	UBYTE Year; 	/* ”N 00`99‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é (’)2000”N¥¥¥00 */
	UBYTE Month;	/* Œ 1`12‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é  */
	UBYTE Date; 	/* “ú 1`31‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é  */
	UBYTE Hour; 	/*  00`23‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é */
	UBYTE Minute;	/* •ª 00`59‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é */
	UBYTE Second;	/* •b 00`59‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é */
	UBYTE Week; 	/* —j“ú 1`7‚Ì’l‚ªBCD‚É‚Äİ’è‚³‚ê‚é */
} TIME_DATA_t;

#endif

