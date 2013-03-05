/*--------------------------------------------------------------------------*/
/*ƒvƒƒWƒFƒNƒg: POPLAR/ANZU_L												*/
/*ƒ‚ƒWƒ…-ƒ‹–¼ : DEF_TIB.H													*/
/*ì¬Ò–¼	  : –ì£														*/
/*“ú  •t	  : 96.10.12													*/
/*ŠT  —v	  : TIB‹y‚ÑƒvƒƒOƒ‰ƒ€”Ô†’è‹`									*/
/*C³—š—ğ	  : ANZU‚©‚ç—¬—p 1996/10/12 T.Nose								*/
/*            : ‹@í•Ê‚ÉˆÚ“® By M.Kotani 97/06/24							*/
/*--------------------------------------------------------------------------*/
#ifndef def_tib2_h
	#define def_tib2_h 1

#include "\src\atlanta\define\product.h"

struct tib_table_data_t {
	UDWORD	(*start_addr)(void);
	UDWORD	(*end_addr)(void);
	UBYTE	stack_size;
	UBYTE	priority;
	UWORD	reserve;
};

/************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚a												*
 ************************************************************************/
#if defined(POPLAR_B)
#include "\src\atlanta\poplar_b\define\popb_tib.h"
#endif

/************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚a‚m 1999/05/13 by T.Soneoka						*
 ************************************************************************/
#if defined(POPLR_BN)
#include "\src\atlanta\poplr_bn\define\popb_tib.h"
#endif


/************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚k												*
 ************************************************************************/
#if defined(POPLAR_L)
#include "\src\atlanta\poplar_l\define\popl_tib.h"
#endif

/************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚m												*
 ************************************************************************/
#if defined(POPLAR_N)
#include "\src\atlanta\poplar_n\define\popn_tib.h"
#endif

/************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚g												*
 ************************************************************************/
#if defined(POPLAR_H)
#include "\src\atlanta\poplar_h\define\poph_tib.h"
#endif

/************************************************************************
 * ‚`‚m‚y‚t ƒ^ƒCƒv ‚k													*
 ************************************************************************/
#if defined(ANZU_L)
#include "\src\atlanta\anzu_l\define\anzu_tib.h"
#endif

/************************************************************************
 * ‚`‚m‚y‚t ƒ^ƒCƒv ‚u													*
 ************************************************************************/
#if defined(ANZU_V)
#include "\src\atlanta\anzu_l\define\anzu_tib.h"
#endif

/************************************************************************
 * ‚r‚`‚j‚`‚j‚h															*
 * 1998/10/09 H.Yoshikawa												*
 ************************************************************************/
#if defined(SAKAKI)
#include "\src\atlanta\sakaki\define\saki_tib.h"
#endif

/************************************************************************
 * ‚g‚h‚m‚n‚j‚h															*
 ************************************************************************/
#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
#include "\src\atlanta\hinoki\define\hino_tib.h"
#endif

/************************************************************************
 * ‚r‚`‚s‚r‚t‚j‚h‚Q														*
 ************************************************************************/
#if defined(SATSUKI2)
#include "\src\atlanta\satsuki2\define\sats_tib.h"
#endif

/************************************************************************
 * ‚r‚s‚n‚b‚j‚g‚n‚k‚l‚Q														*
 ************************************************************************/
#if defined(STOCKHM2)
#include "\src\atlanta\stockhm2\define\lvnd_tib.h"
#endif

#endif
