/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DCMD.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ’ÊM—\–ñÁ‹Ž’Ê’m
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
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* ˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\’Ç‰Á 1996/10/18 Eguchi */
#include	"\src\atlanta\define\syscntpl.h" /* 1996/10/16 Eguchi */
#endif

/*************************************************************************
	module		:[’ÊM—\–ñÁ‹Ž’Ê’mˆóü]
	function	:[’ÊM—\–ñÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List			:
		SYB_CommandFile	:
		SYB_BatchTxFile	:
		SYS_ScannerComEraseRequest:
	]
	condition	:[]
	commment	:[
		C³—š—ð
		'94.10/20	   s–Ú:"Â³¼ÝÖÔ¸ ºÏÝÄÞ¶Þ ¼®³·® »ÚÏ¼À .............."
							‚ÌˆóŽš‚ÌŽžA‘¼‚ÌÁ‹Ž’Ê’m‚Æ“¯‚¶‚æ‚¤‚ÉA
							˜g‚ÅˆÍ‚Þ‚æ‚¤‚É•ÏX‚µ‚½
		'94.10/27		ˆêŠ‡‘—M‹@”\‚ª—L‚è‚ÅAˆêŠ‡‘—MŒ´e‚ªÁ‹Ž‚³‚ê‚½ŽžA
							"ˆêŠ‡‘—MŒ´e‚ªÁ‹Ž‚³‚ê‚Ü‚µ‚½DDD"‚ðˆóŽš‚·‚é
		'94.11/22		‘¼‚ÌƒŠƒXƒg‚Æ‡‚í‚¹‚é‚½‚ßA“úŽž‚ÌŒã‚Ì‰üs‚ð‚È‚­‚µ‚½B
						by j.masuda
		'94.11/26		ƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹‚ÌƒXƒe[ƒ^ƒX‚ðEMPTY‚É‚·‚é‘O‚É
						SYS_ScannerComEraseListRequest‚ðƒNƒŠƒA[‚·‚éB
						PRO_DRAM_BACKUP==ENABLE‚ÌŽž‚Ì‚ÝB
						By j.masuda
		'94.12/24		'94.11/26‚Ì•ÏX‚ªASATUKI/LVNDR‚ÌðŒƒRƒ“ƒpƒCƒ‹’†‚É
						“ü‚Á‚Ä‚¨‚èAKIRI/MOMIJI‚ÌðŒƒRƒ“ƒpƒCƒ‹‚É‚ÍA“ü‚Á‚Ä
						‚¢‚È‚©‚Á‚½ˆ×AKIRI/MOMIJI‚É‚à‚¢‚ê‚½B
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_DelReserveCmd_Notice(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

/* ˆÈ‰º‚P‚Ps‚ð˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\‚Ì‚½‚ß’Ç‰Á 1996/10/18 Eguchi */
	UWORD	status;
	status = Check_AnyList(LST_DELRESERVECMD_NOTICE);
#if (PRO_BATCH_TX == ENABLE)
	status &= Check_AnyList(LST_DELBATCHTXDOC_NOTICE);
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	status &= Check_AnyList(LST_DELCONTPOLLCMD_NOTICE);
#endif
	if (status == MSG_PRN_LST_NO_LIST) {
		return (MSG_PRN_LST_NO_LIST);
	}
/* ˆÈã‚P‚Ps‚ð˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\‚Ì‚½‚ß’Ç‰Á 1996/10/18 Eguchi  */

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[21-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[22-1], 38, LST_KLINE_ );
	List.S.Print[60-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*––@ƒcƒEƒVƒ“ƒˆƒ„ƒN@ƒVƒ‡ƒEƒLƒ‡@ƒcƒEƒ`@––*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[21-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1],
		 PWRD_ErasedCommands_K, LST_NOT);		/* MES¨INV 94.7.20 -> NOT 8.10 */
#else
	AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1],
	  PWRD_ErasedCommands, LST_MES_TWI_XXX );

#endif

	List.S.Print[60-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[21-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[22-1], 38, LST_KLINE_ );
	List.S.Print[60-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}

#if ( PRO_BATCH_TX == ENABLE )	/* ’ÊM—\–ñÁ‹Ž’Ê’m‚ÉˆêŠ‡‘—MŒ´eÁ‹Ž‚à‹LÚ‚·‚é 94.10.27 Toyoda */
	for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
 #if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
		if ( SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF ) {
 #else
		if ( SYB_CommandStatus[i] == SYS_CMD_POWER_OFF ) {
 #endif
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†² '94.10/20 By K.Watanabe*/
			Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤Â³¼ÝÖÔ¸¹ÞÝº³¶Þ@¼®³·®@»ÚÏ¼À ................. †¤*/
			Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );	/* '94.10/20 By K.Watanabe */
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ThisComErased, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º '94.10/20 By K.Watanabe*/
			Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			break;
		}
	}
	for ( i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
		if ( SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF ) {
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†² '94.10/20 By K.Watanabe*/
			Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ˆêŠ‡‘—MŒ´e‚ªÁ‹Ž‚³‚ê‚Ü‚µ‚½ ................. †¤*/
			Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );	/* '94.10/20 By K.Watanabe */
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_BatchTxDocErase, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º '94.10/20 By K.Watanabe*/
			Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			break;
		}
	}
 #if (PRO_CONTINUOUS_POLLING == ENABLE) /* ˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\’Ç‰Á 1996/10/18 Eguchi */
	if (SYB_ContinuousPolling.Status == SYS_CMD_POWER_OFF) {/*‚¢‚ç‚ñ‚â‚ë*/

		Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/* ˜A‘±ƒ|[ƒŠƒ“ƒOŒ´e‚ªÁ‹Ž‚³‚ê‚Ü‚µ‚½EEEEE */
		Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ContinuousPollingErase, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º '94.10/20 By K.Watanabe*/
		Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
 #endif

 #if (PRO_DRAM_BACKUP == ENABLE)			/*94/12/24 « By jmasuda*/
	SYS_ScannerComEraseListRequest = 0;
 #endif									/*94/12/24 ª By jmasuda*/
	for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
 #if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
		if ( SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF ) {
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;

	#if (PRO_F_CODE == ENABLE)
			if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** ŒðMŽí•Ê”»’f */
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
	#endif
		}
 #else
		if ( SYB_CommandStatus[i] == SYS_CMD_POWER_OFF ) {
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
	#if (PRO_F_CODE == ENABLE)
			if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** ŒðMŽí•Ê”»’f */
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
	#endif
			SYB_CommandStatus[i] = SYS_CMD_EMPTY;
		}
 #endif
	}
	for ( i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
		if ( SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF ) {
			SYB_BatchTxFile[i].Status = SYS_CMD_EMPTY;
/*			for ( j = 0; j < SYS_BATCH_INDEX_MAX; j++ ) {	0¸Ø±‚ÍµÍßÚ°¼®Ý‚ª‚·‚é '94.11.16 H.T */
/*				SYB_BatchTxFile[i].IndexNo[j] = 0x0000;		*/
/*			}												*/
		}
	}

 #if (PRO_CONTINUOUS_POLLING == ENABLE) /* ˜A‘±ƒ|[ƒŠƒ“ƒOˆ—’Ç‰Á 1996/10/18 Eguchi */
	if (SYB_ContinuousPolling.Status == SYS_CMD_POWER_OFF) {
		SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
	}
 #endif


#else
 #if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/26 « By jmasuda*/
	SYS_ScannerComEraseListRequest = 0;
 #endif									/*94/11/26 ª By jmasuda*/
	for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
 #if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
		if ( SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF ) {
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
	#if (PRO_F_CODE == ENABLE)
			if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** ŒðMŽí•Ê”»’f */
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
	#endif
		}
 #else
		if ( SYB_CommandStatus[i] == SYS_CMD_POWER_OFF ) {
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
	#if (PRO_F_CODE == ENABLE)
			if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** ŒðMŽí•Ê”»’f */
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
	#endif
			SYB_CommandStatus[i] = SYS_CMD_EMPTY;
		}
 #endif
	}
	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†² '94.10/20 By K.Watanabe*/
	Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤Â³¼ÝÖÔ¸¹ÞÝº³¶Þ@¼®³·®@»ÚÏ¼À ................. †¤*/
	Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );	/* '94.10/20 By K.Watanabe */
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ThisComErased, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º '94.10/20 By K.Watanabe*/
	Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
#endif

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

