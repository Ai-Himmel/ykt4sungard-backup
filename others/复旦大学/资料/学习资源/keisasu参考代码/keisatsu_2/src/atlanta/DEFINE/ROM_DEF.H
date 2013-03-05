/************************************************************************
*	System		: POPLAR_H/POPLAR_B
*	File Name	: ROM_DEF.H
*	Author		: “n•ÓˆêÍ
*	Date		: 1998/02/27
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: Šg’£‚q‚n‚lŒÅ’è’l’è‹`
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef rom_def_h
	#define rom_def_h

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1998/02/27
*             TYPE:  CONST UBYTE EXT_ROM_Revision[SYS_EXT_ROM_MAX][ROM_REVISION_MAX]
*      VAR TO HOLD:
*      DESCRIPTION:  Šg’£‚q‚n‚l“à—e’è‹`
************************************************************************/
#define	ROM_EXT_SCRAMBLE	0	/* ƒXƒNƒ‰ƒ“ƒuƒ‹—p‚q‚n‚l	*/
#define	ROM_EXT_CLASS1		1	/* ƒNƒ‰ƒX‚P—p‚q‚n‚l		*/	/* ’Ç‰Á S.Fukui Jun.19,1998 */
#define	ROM_EXT_RSV2		2	/* —\–ñ‚Q				*/
#define	ROM_EXT_RSV3		3	/* —\–ñ‚R				*/
#define	ROM_EXT_RSV4		4	/* —\–ñ‚S				*/

/************************************************************************
*               BY:  Y.Suzuki
*             DATE:  1998/03/2
*             TYPE:  CONST UWORD ExtRomType
*      VAR TO HOLD:
*      DESCRIPTION:  Šg’£‚q‚n‚lg—pƒ‚ƒWƒ…[ƒ‹
************************************************************************/
#define	MOD_SCRAMBLE	0x0001	/* ƒXƒNƒ‰ƒ“ƒuƒ‹—p‚q‚n‚l	*/
#define	MOD_RSV1		0x0002	/* —\–ñ‚P				*/
#define	MOD_RSV2		0x0004	/* —\–ñ‚Q				*/
#define	MOD_RSV3		0x0008	/* —\–ñ‚R				*/
#define	MOD_RSV4		0x0010	/* —\–ñ‚S				*/

#endif
