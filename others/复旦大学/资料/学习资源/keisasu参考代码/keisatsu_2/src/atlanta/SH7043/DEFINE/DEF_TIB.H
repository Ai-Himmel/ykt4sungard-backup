/*--------------------------------------------------------------------------*/
/*ƒvƒƒWƒFƒNƒg: POPLAR/ANZU_L												*/
/*ƒ‚ƒWƒ…-ƒ‹–¼ : DEF_TIB.H													*/
/*ì¬Ò–¼	  : –ì£														*/
/*“ú  •t	  : 96.10.12													*/
/*ŠT  —v	  : TIB‹y‚ÑƒvƒƒOƒ‰ƒ€”Ô†’è‹`									*/
/*C³—š—ğ	  : ANZU‚©‚ç—¬—p 1996/10/12 T.Nose								*/
/*            : ‹@í•Ê‚ÉˆÚ“® By M.Kotani 97/06/24							*/
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚hˆÈ~‚Ì‹@í‚ÍAƒ}ƒXƒNƒvƒƒOƒ‰ƒ€•ÏX
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#else
#ifndef def_tib_h
	#define def_tib_h

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


/****************************************************************************
 * ‚o‚n‚o‚k‚`‚q ƒ^ƒCƒv ‚a‚m i‚k‚T‚O‚O ‚m‚s‚sd—lj 1999/05/13 by T.Soneoka	*
 ***************************************************************************/
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
/*
**	ANZU_V(²İÀ°È¯ÄFAXµÌß¼®İ•t‚«ÓÃŞÙ)—p‚ÌÌ§²Ù‚É‚µ‚Ü‚·Bby Y.Tanimoto 1998/03/18
*/
#include "\src\atlanta\anzu_v\define\anzu_tib.h"
#endif

/************************************************************************
 * ‚r‚`‚j‚`‚j‚h															*
 ************************************************************************/
#if defined(SAKAKI)
#include "\src\atlanta\sakaki\define\saki_tib.h"
#endif

/************************************************************************
 * ‚k‚S‚O‚OŒãŒp															*
 ************************************************************************/
#if defined(POPLAR_F)
#include "\src\atlanta\poplar_f\define\popf_tib.h"
#endif


#endif

#endif
