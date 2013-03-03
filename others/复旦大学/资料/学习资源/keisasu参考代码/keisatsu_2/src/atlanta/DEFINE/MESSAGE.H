/* Copied by T.Nose 1996/10/14 */
#ifndef message_h
    #define message_h
/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Oct.20,1993
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   ¿Ω∏ä‘ÇÃ“Øæ∞ºﬁëóêMÅ^éÛêMéûÇÃ“Øæ-ºﬁÇÃå^
************************************************************************/
typedef struct {
    UWORD Item;
    UWORD Message;
    UWORD SubMessage1;
    UWORD SubMessage2;
    UWORD SubMessage3;
    UWORD SubMessage4;
} MESSAGE_t;

/*#if (PRO_MULTI_LINE == ENABLE) || (PRO_DPRAM == ENABLE)*/	/* 1996/11/09 Y.Murata */
	struct	SYS_OptionMessageData_t {
		UBYTE	Status;
		UWORD	Item;
		UWORD	Message;
		UWORD	SubMessage1;
		UWORD	SubMessage2;
		UWORD	SubMessage3;
		UWORD	SubMessage4;
	};
/*#endif*/

/*#if (PRO_PC_PRINT == ENABLE)*/	/* Add BY H.H 1997/03/05 */
 	struct	SYS_PCR_OptionMessageData_t {
		UBYTE	Status;
		UWORD	Item;
		UWORD	Message;
	};
/*#endif*/

#endif
