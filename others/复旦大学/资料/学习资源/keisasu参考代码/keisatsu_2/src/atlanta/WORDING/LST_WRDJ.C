/*@^s**************************************************************************
**@^1	lst_wrdj.c
**@^2	帳票用固定文字列 JAPANESE (JPN)
**@^3	JCS (j.m)
**@^4	桐（全角文字仕様）と皐月（半角文字仕様）の切分け
**@^e*************************************************************************/
#include	"\src\atlanta\define\product.h"

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	#include	"\src\atlanta\wording\lst_wkan.c"
#else
	#include	"\src\atlanta\wording\lst_wjpn.c"
#endif
