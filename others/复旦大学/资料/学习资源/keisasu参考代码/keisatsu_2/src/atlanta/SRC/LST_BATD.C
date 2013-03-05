/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_BATD.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ˆêŠ‡‘—MŒ´eØ½Ä
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if	( PRO_PANEL == ANK )
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if	( PRO_PANEL == KANJI )
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#endif

#if (PRO_BATCH_TX == ENABLE)

/*************************************************************************
	module		:[ˆêŠ‡‘—MŒ´eƒŠƒXƒgˆóü]
	functiom	:[ˆêŠ‡‘—MŒ´eƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_BatchTxFile		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 7]
	author		:[–L“c_Žq]
*************************************************************************/
WORD		 		Print_BatchTxDoc_List(
						 void )					/*‚È‚µ*/
{

	register WORD	ret;							/*ŽÀsŒ‹‰Ê*/
	UBYTE	BoxNo;						/*ˆêŠ‡‘—MBoxNo.*/

	if (( ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_BatchTxDocList_K,
		 LST_NOT,20-1 )) != OK ) {
			return ( ret );
		}

#else
	if ( (ret = Print_Head1_Common( PWRD_BatchTxDocList,
	  LST_XXX_TWI_XXX, 16 )) != OK ) {
		return ( ret );
	}

#endif

	/* Œ»ÝŽžŠÔ */
	if (( ret = CurrentTimePrint( 60 - 1 )) != OK ) {
		return ( ret );
	}

	/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢†O †S @ˆêŠ‡‘—MŒ´eƒŠƒXƒg@*/
	Print_BatchTxBox_List_Line( 0, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ No.„ ‘ŠŽèæ–¼„ †E@@Žó•t”Ô†@@  „ †E */
	Print_BatchTxBox_List_Line( 1, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*ˆêŠ‡‘—MŒ´eƒŠƒXƒg‚Ì‚Ps–¾× */
	for ( BoxNo = 0; BoxNo < SYS_BATCH_FILE_MAX; BoxNo++ ) {
		if ( SYB_BatchTxFile[BoxNo].DialNumber[0].Item != SYS_EMPTY_DIAL ) {
			/*  „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§†g */
			Print_BatchTxBox_List_Line( 2, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†E„  9 „ xxxxxxx„ xxxxxxxxxxxxxxxxxxxx„    */
			Print_BatchTxBox_List_Line( 3,List.S.Print, List.S.Attribute);
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(BoxNo + OPR_BATCH_FILE_MIN), 1, '0' );
			/*CMN_StringCopyNum( &List.S.Print[6-1], SYB_BatchTxFile[BoxNo].Name, 16 ); 1997/11/28 */
			CMN_StringCopyNumNotNULL( &List.S.Print[6-1], SYB_BatchTxFile[BoxNo].Name, 16 );
			if ( (SYB_BatchTxFile[BoxNo].Status == SYS_CMD_SETTING) ||
			     (SYB_BatchTxFile[BoxNo].Status == SYS_CMD_WAITING) ||
			     (SYB_BatchTxFile[BoxNo].Status == SYS_CMD_EXECUTE) ) {
				if ( (ret = Print_BatchTxDoc_Index_Specifi( BoxNo )) != OK ) {
					return ( ret );
				}
			}
			else {
				if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
		}
	}

	/* †W„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£  */
	Print_BatchTxBox_List_Line( 4, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ˆêŠ‡‘—MŒ´eƒŠƒXƒgŽó•t‚¯”Ô†–¾×ˆóü]
	functiom	:[ˆêŠ‡‘—MŒ´eƒŠƒXƒg‚ÌŽó•t”Ô†‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_BatchTxFile		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/16]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_BatchTxDoc_Index_Specifi(
						 UBYTE BoxNo ) 				/*ˆêŠ‡‘—M‚a‚‚˜‚m‚D*/
{

	UBYTE	i;			/*loop*/
	UBYTE	IndexNo;	/*Žó•t‚¯‚m‚*/
	register WORD	ret;		/*ŽÀsŒ‹‰Ê*/

	i = 0;
	CMN_MemorySetNULL( List.S.Work, 57, ' ');
	for ( IndexNo = 0; IndexNo < SYS_BATCH_INDEX_MAX; IndexNo++ ) {
		if ( SYB_BatchTxFile[BoxNo].IndexNo[IndexNo] != 0x0000 ) {
			if ( i == 19) {
				CMN_StringCopy( &List.S.Print[23-1], List.S.Work );
				if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				i = 0;
				CMN_MemorySetNULL( List.S.Work, 57, ' ');
				Print_BatchTxBox_List_Line( 3, List.S.Print, List.S.Attribute);
			}
			if ( i > 0 ) {
				List.S.Work[i*3-1] = ',';
			}
			CMN_UnsignedIntToASC( &List.S.Work[i*3], (UWORD)IndexNo, 2, ' ');
			i++;
		}
	}
	CMN_StringCopy( &List.S.Print[23-1], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

#endif
