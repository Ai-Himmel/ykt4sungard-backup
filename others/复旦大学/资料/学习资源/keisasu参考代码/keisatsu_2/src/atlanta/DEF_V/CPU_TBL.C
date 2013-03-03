/************************************************************************
 * ÇbÇoÇt ﬁ∞ºﬁÆ›ñºÇíËã` (16 Chars + NULL)								*
 * CPU_Revision[ROM_REVISION_MAX] = "0123456789ABCDEF";					*
 * 01234 : ã@éÌñº														*
 * 5	 : ãÛîí															*
 * 678	 : édå¸çëñº(ISOéQè∆)											*
 * 9	 : ãÛîí															*
 * ABCDEF: ÉoÅ[ÉWÉáÉìñº													*
 ************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

#pragma section CPU_VER		/* ÉZÉNÉVÉáÉìéwíË */

/* ÇoÇnÇoÇkÇ`ÇqÅ^Ç`ÇmÇyÇtÅQÇkÉVÉäÅ[ÉYÇ∆ÇrÇ`ÇjÇ`ÇjÇhÅ^ÇgÇhÇmÇnÇjÇhÇãÊï Ç∑ÇÈÅB
** By O.Kimoto 1998/09/04
*/
#if (PRO_CPU_VERSION == SH7043_A)
	/* CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "SH7043_A  980904"; */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "SH7043_A  981021";	*//* ÇrÇ`ÇjÇ`ÇjÇh ÇpÇ`Çsóp by O.Kimoto 1998/10/21 */
	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU_A     A0A0A0";	/* ÇrÇ`ÇjÇ`ÇjÇh1stÉçÉbÉgóp by H.Yoshikawa 1998/11/05 */
#else
/*------------------------------------------------------------------------
**	É|ÉvÉâÇa É|ÉvÉâÇk ÉAÉìÉYÇk ÉAÉìÉYÇu É|ÉvÉâÇg
*/
/*#if defined(POPLAR_B) || defined(POPLAR_L) || defined(ANZU_L) || defined(ANZU_V)*/
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970515";	/@ By M.Tachibana 1997/03/07 */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970604";	@* By T.Yamaguchi 1997/06/04 */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970616";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970627";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970707";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970711";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970716";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970821";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970827";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  970917";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_B  971001";	@*    Y.Murata    */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU       971009";	@* By M.Tachibana */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU       971020";	@* By Y.Suzuki 1997/10/20 */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU       A0A0A0";	@* By T.yamaguchi 1997/10/28 */
/*	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU       980205";	@* By T.yamaguchi 1997/10/28 */
	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "CPU       C0C0C0";	/* By Y.Suzuki 1998/10/07 */
/*#endif*/

#if (0)
///*------------------------------------------------------------------------
//**	É|ÉvÉâÇg
//*/
//#if defined(POPLAR_H)
//	CONST UBYTE CPU_Revision[ROM_REVISION_MAX] = "POPLAR_H  970515";	/* By Y.Suzuki 1996/10/24 */
//#endif
#endif
#endif

#pragma section
