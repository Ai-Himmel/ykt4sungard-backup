/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DBAT.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ˆêŠ‡‘—MŒ´eÁ‹Ž’Ê’m
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

#if ( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if ( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#endif

#if (PRO_BATCH_TX == ENABLE)

/*************************************************************************
	module		:[ˆêŠ‡‘—MŒ´eÁ‹Ž’Ê’mˆóü]
	functiom	:[ˆêŠ‡‘—MŒ´eÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
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
	date		:[94/ 3/15]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DelBatchTxDoc_Notice(
						 void )						/*‚È‚µ*/
{
	UBYTE			BoxNo;		/*ˆêŠ‡‘—MBoxNo.*/
	register WORD	ret;		/*ŽÀsŒ‹‰Ê*/
	UBYTE			i;			/*roop*/

	if ( Check_AnyList( LST_DELBATCHTXDOC_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* 1s‰üs{”­MŒ³–¼C”Ô†ˆóü{‚Qs‰üs */
	if ( (ret = TTI_ID_Print_Feed() ) != OK ) {
		return ( ret );
	}

	/* „¡„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[19-1], 43, LST_KLINE_ );
	List.S.Print[62-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ @@ˆêŠ‡‘—MŒ´eÁ‹Ž’Ê’m@@„  */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINEI;

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[20-1], &List.S.Attribute[20-1],
		  PWRD_EraseBatchTxDoc_K, LST_NOT );		/* MES¨INV 94.7.20 -> NOT 8.10 */
#else
	AttributeSet( &List.S.Print[20-1], &List.S.Attribute[20-1],
	  PWRD_EraseBatchTxDoc, LST_MES_TWI_XXX );
#endif

	List.S.Print[62-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „¤„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[19-1], 43, LST_KLINE_ );
	List.S.Print[62-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* ‚Ps‰üs */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* Œ»ÝŽžŠÔ */
	if ( (ret = CurrentTimePrint( 60-1 ) ) != OK ) {
		return ( ret );
	}

	/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢†O †S @ˆêŠ‡‘—MŒ´eƒŠƒXƒg@*/
	Print_BatchTxBox_List_Line( 0, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ No.„ ‘ŠŽèæ–¼„ †E@@Žó•t”Ô†@@	„ †E */
	Print_BatchTxBox_List_Line( 1, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* ˆêŠ‡‘—MŒ´eÁ‹ŽƒŠƒXƒg‚Ì‚Ps–¾× */
	for ( BoxNo = OPR_BATCH_FILE_MIN; BoxNo <= SYS_BATCH_FILE_MAX; BoxNo++ ) {
		if ( SYB_BatchTxFile[BoxNo-1].Status == SYS_CMD_POWER_OFF ) {
			/*	„¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§†g */
			Print_BatchTxBox_List_Line( 2, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†E„  9 „ xxxxxxx„ xxxxxxxxxxxxxxxxxxxx„ 	 */
			Print_BatchTxBox_List_Line( 3, List.S.Print, List.S.Attribute);
			CMN_UnsignedIntToASC( &List.S.Print[2-1], BoxNo, 1, '0' );
			CMN_StringCopy( &List.S.Print[6-1], SYB_BatchTxFile[BoxNo-1].Name );
			if ( ( ret = Print_BatchTxDoc_Index_Specifi( BoxNo )) != OK ) {
				return ( ret );
			}
		}
	}

	/* †W„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£	 */
	Print_BatchTxBox_List_Line( 4, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
		if ( SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF ) {
			SYB_BatchTxFile[i].Status = SYS_CMD_EMPTY;
		}
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* ˆêŠ‡‘—MŒ´e‚ªÁ‹Ž‚³‚ê‚Ü‚µ‚½DDDDDD */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
	  PWRD_BatchTxDocErase, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
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

#endif
