#ifndef STD_H
    #define STD_H
/***********************************************************************
* DESCRIPTION:   ïœêîå^íËã`
************************************************************************/
	#define	BOOL			char			/* 1Byte:TRUE or FALSE */
	#define	BYTE			char			/* 1Byte */
	#define	UBYTE			unsigned char	/* 1Byte:ïÑçÜñ≥ */
	#define	WORD			short			/* 2Byte */
		#define	WORD_MAX	(WORD)32767
		#define	WORD_MIN	(WORD)(-32768)
	#define	UWORD			unsigned short	/* 2Byte:ïÑçÜñ≥ */
	#define	DWORD			long			/* 4Byte */
	#define	UDWORD			unsigned long	/* 4Byte:ïÑçÜñ≥ */
	#define CONST			const			/* ROM */
/***********************************************************************
* DESCRIPTION:   ïWèÄíËã`
************************************************************************/
#define		TRUE	1
#define		FALSE	0

#define		OK		1
#define		NG		0
#define		ERROR	-1

#define		YES		1
#define		NO		0

#define		NULL	0x00
#define		CR		0x0D

#ifndef	SPACE
	#define	SPACE	0x20
#endif

#endif
