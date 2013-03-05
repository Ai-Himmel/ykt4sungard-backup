/*************************************
 * ˆ—Œn‚Ìˆá‚¢‚ğ‹zû‚·‚éƒwƒbƒ_[
 * 1996/04/17 Eguchi 
 *************************************/
#ifndef CPU_TYPE_H	
	#define	CPU_TYPE_H	1

/*--------------------*/
/* CPU‚ªV53‚Ìê‡	  */
/*--------------------*/
#if defined(V53)
	#define	UWORD	unsigned int
	#define	WORD	int
#endif

/*--------------------*/
/* CPU‚ªSH‚Ìê‡	  */
/*--------------------*/
#if defined(SH7034) || defined(SH704X) || defined(SH7043)
	#define	UWORD	unsigned short
	#define	WORD	short
	#define far
	#define near
#endif

#endif
