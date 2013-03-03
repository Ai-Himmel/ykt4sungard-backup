/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\atlanta\def_v\ctry_tbl.c */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\country.h"

#pragma section CTRY_TBL		/* セクション指定 */

#if defined(JPN)
	#include "\src\atlanta\def_v\ctry_jpn.c"
#endif
#if defined(USA)
	#include "\src\atlanta\def_v\ctry_usa.c"
#endif
#if defined(AUS)
	#include "\src\atlanta\def_v\ctry_aus.c"
#endif
#if defined(GBR)
	#include "\src\atlanta\def_v\ctry_gbr.c"
#endif
#if defined(FRA)
	#include "\src\atlanta\def_v\ctry_fra.c"
#endif
#if defined(DEU)
	#include "\src\atlanta\def_v\ctry_deu.c"
#endif
#if defined(TWN)
	#include "\src\atlanta\def_v\ctry_twn.c"	/* 1998/02/09 Y.M ctry_sea.c->ctry_twn.c */
#endif
#if defined(EC1)
	#include "\src\atlanta\def_v\ctry_EC1.c"
#endif
#if defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/15 */
	#include "\src\atlanta\def_v\ctry_EUR.c"
#endif

#pragma section
