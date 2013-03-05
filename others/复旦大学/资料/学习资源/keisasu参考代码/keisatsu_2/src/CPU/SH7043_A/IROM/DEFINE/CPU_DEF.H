/*---------------------------------------------------------------------------*/
/*  ƒvƒƒWƒFƒNƒg : SAKAKI/HINOKI                                             */
/*  ƒtƒ@ƒCƒ‹–¼   : cpu_def.h                                                 */
/*  ì¬Ò       : –ØŒ³C^–ì£•qO                                          */
/*  “ú  •t       : 1998/09/07                                                */
/*  ŠT  —v       : SH7043 ‹@í•ÊCPU‰Šúİ’è’è‹`ƒtƒ@ƒCƒ‹                      */
/*  C³—š—ğ     : SH7043_A—p‚Å‚·B                                          */
/*---------------------------------------------------------------------------*/
#ifndef	CPU_DEF2_H
	#define	CPU_DEF2_H	1

#if defined(POPLAR_B)	/** ‚o‚n‚o‚k‚`‚qQ‚aƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\poplar_b\define\popb_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLR_BN)	/** ‚o‚n‚o‚k‚`‚qQ‚a‚mƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\poplr_bn\define\popb_cpu.h"
#endif
#if defined(POPLAR_L)	/** ‚o‚n‚o‚k‚`‚qQ‚kƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\poplar_l\define\popl_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_N)	/** ‚o‚n‚o‚k‚`‚qQ‚mƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\poplar_n\define\popn_cpu.h"	/* By M.Kotani 97/06/11 */
#endif
#if defined(POPLAR_H)	/** ‚o‚n‚o‚k‚`‚qQ‚gƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\poplar_h\define\poph_cpu.h"	/* Add By O.Kimoto 1997/06/13 */
#endif
#if defined(ANZU_L)		/** ‚`‚m‚y‚tQ‚kƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\anzu_l\define\anzu_cpu.h"	/* By M.Kotani 97/06/10 */
#endif
#if defined(ANZU_V)		/** ‚`‚m‚y‚tQ‚uƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\anzu_l\define\anzu_cpu.h"	/* By M.Kotani 98/01/08 */
#endif
#if defined(SAKAKI)		/** ‚r‚`‚j‚`‚j‚hƒ^ƒCƒv‚Í‹@í•ÊƒfƒBƒŒƒNƒgƒŠ‚ÉˆÚ“®‚µ‚Ü‚µ‚½ */
	#include "\src\atlanta\sakaki\define\saki_cpu.h"	/* By H.Yoshikawa 1998/10/09 */
#endif
#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(KEISATSU)	/* ‚e‚‚’ ‚g‚h‚m‚n‚j‚h By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
	#include "\src\atlanta\hinoki\define\hino_cpu.h"
#endif
#if defined(SATSUKI2)
	#include "\src\atlanta\satsuki2\define\sats_cpu.h"
#endif
#if defined(STOCKHM2)
	#include "\src\atlanta\stockhm2\define\lvnd_cpu.h"
#endif

#endif
