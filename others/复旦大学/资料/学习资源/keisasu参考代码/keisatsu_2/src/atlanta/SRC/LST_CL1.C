/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CL1.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: クラス１モニタ－
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_tbl.h"
#include "\src\atlanta\ext_v\lst_wrd.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\define\cl1_def.h"
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

/*************************************************************************
	module		:[クラス１モニタ－印字]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1996/08/20]
	author		:[平尾 英典]
*************************************************************************/
#if ( PRO_CLASS1 == ENABLE )
WORD	PrintClass1Monitor(void )		/*	なし	*/
{
	WORD	ret;		/*	実行結果	*/
	UBYTE	line;		/*	印刷可能行数	*/
	UBYTE	i, pointer;
	
	i = 0;
	pointer = CL1MonitorNo;
	
	if ( (pointer == 0) && (CL1MonitorBuf[pointer].id == NULL) ) {
	 return ( MSG_PRN_LST_NO_LIST );
	}
	
	while ( i < CL1_MON_BUF_MAX ) {
		/**	プリンタースタート	*/
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		
		/**	印刷可能行数ｾｯﾄ	*/
		line = (UBYTE)PaperSizeLen();
		
		/**	１行改行	*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		line--;
	
		/**	＜ Ｏｎｌｉｎｅ  Ｍｏｎｉｔｏｒ ＞	*/
		if ( i == 0 ) {	/** １ページのみ印字する */
			Prn_Att_Str_Clear( List.S.Print,
			  List.S.Attribute );	/**	クリア	*/
			AttributeSet( &List.S.Print[21],
			  &List.S.Attribute[21],
			  PWRD_OnLineMonitor,
			  LST_XXX_TWI_XXX );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line -= 1;
		}
	
		/**	1行改行	*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		line--;
		
		/**	Time  Rx  Tx  Speed  Data	*/
		Prn_Att_Str_Clear( List.S.Print,
		  List.S.Attribute );	/**	クリア	*/
		CMN_StringCopy( &List.S.Print[1],
		  PWRD_CommStartTime );
		CMN_StringCopy( &List.S.Print[14],
		  PWRD_OnLineRx );
		CMN_StringCopy( &List.S.Print[25],
		  PWRD_OnLineTx );
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Speed );
		CMN_StringCopy( &List.S.Print[45],
		  PWRD_OnLineData );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line--;
		
		if ( CL1MonitorBuf[pointer].id == NULL ) {
				i = (UBYTE)(CL1_MON_BUF_MAX - pointer);
				pointer = 0;
		}
		
		for ( ; i < CL1_MON_BUF_MAX; ) {
			Prn_Att_Str_Clear( List.S.Print,
			  List.S.Attribute );	/**	クリア	*/
			
			/**	Cmd or Res or Abort or Data	*/
			switch ( CL1MonitorBuf[pointer].id ) {
			case 'C':
				TenMSecondToMinuteSecondASC( (UWORD)(CL1MonitorBuf[pointer].time),
				  &List.S.Print[1] );	/**	Time	*/
				
				CMN_StringCopy( &List.S.Print[14],
				  PWRD_Command );
				  
				List.S.Print[45] = 'A';	/** Data部の”AT”追加 */
				List.S.Print[46] = 'T';
				
				break;
			case 'A':
				TenMSecondToMinuteSecondASC( (UWORD)(CL1MonitorBuf[pointer].time),
				  &List.S.Print[1] );	/**	Time	*/
				
				CMN_StringCopy( &List.S.Print[14],
				  PWRD_Abort );
				break;
			case 'R':
				TenMSecondToMinuteSecondASC( (UWORD)(CL1MonitorBuf[pointer].time),
				  &List.S.Print[1] );	/** Time	*/
				
				CMN_StringCopy( &List.S.Print[25],
				  PWRD_Response );
				break;
			case 'D':
				TenMSecondToMinuteSecondASC( (UWORD)(CL1MonitorBuf[pointer].time),
				  &List.S.Print[1] );	/**	Time	*/
					
					if ( CL1MonitorBuf[pointer].TxOrRx == 'R' ) {
						CMN_StringCopy( &List.S.Print[14],
						  PWRD_OnLineData );
					}
					else {
						CMN_StringCopy( &List.S.Print[25],
						  PWRD_OnLineData );
					}
				break;
			}
			
			/**	Speed */
			SelectSpeedWording( pointer );
			
			/**	Data	*/
			if ( (CL1MonitorBuf[pointer].id == 'C') || ( CL1MonitorBuf[pointer].id == 'R') ) {
				CMN_StringCopy( &List.S.Print[47],
				  CL1MonitorBuf[pointer].cmd );
			}
			else if ( (CL1MonitorBuf[pointer].id == 'D') && (CL1MonitorBuf[pointer].cmd[0] != NULL) ) {
				List.S.Print[47] = '[';
				List.S.Print[51] = ']';
				GetFrameName( LST_FAX_CTRL, CL1MonitorBuf[pointer].cmd[2],
				  &List.S.Print[48] );
				if ( List.S.Print[48] != '?' ) {
					if ( Xmask(CL1MonitorBuf[pointer].cmd[3]) == PPS_F
					  || Xmask(CL1MonitorBuf[pointer].cmd[3]) == EOR_F ) {/* 2byte */
						List.S.Print[51] = '.';
						List.S.Print[55] = ']';
						GetFrameName( LST_FAX_CTRL, CL1MonitorBuf[pointer].cmd[4],
						  &List.S.Print[52] );
					}
				}
			}

			/**	１行印字	*/
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			i++;
			pointer++;
			line--;
			if ( pointer == CL1_MON_BUF_MAX ) {
				pointer = 0;
			}
			/**	１ページの行数を超えたかどうか	*/
			if ( line == 0 ) {
				break;
			}
		}
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
}
#endif /* PRO_CLASS1 == ENABLE */


/*************************************************************************
	module		:[スピードの選択]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1996/08/21]
	author		:[平尾 英典]
*************************************************************************/
#if ( PRO_CLASS1 == ENABLE )
void	SelectSpeedWording( UBYTE number )
{
	switch ( CL1MonitorBuf[number].speed ) {
	case 0x01:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps600 );
		break;
	case 0x02:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps1200 );
		break;
	case 0x03:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps2400 );
		break;
	case 0x04:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps4800 );
		break;
	case 0x05:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps9600 );
		break;
	case 0x06:
		CMN_StringCopy( &List.S.Print[34],
		  PWRD_Bps19200 );
		break;
	default:
		break;
	}
}
#endif	/**	PRO_CLASS1 == ENABLE	*/


/*************************************************************************
	module		:[10mｓ単位の数値を分：秒：10ミリ秒のアスキーコードに変換する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[SHC]
	keyword		:[LST]
	date		:[1996/08/22]
	author		:[平尾 英典]
*************************************************************************/
#if ( PRO_CLASS1 == ENABLE )
void	TenMSecondToMinuteSecondASC(
				UWORD localtenmmsec,						/** 変換元10m秒値 */
				UBYTE *localascstring )		/** 変換先文字列 */
{
	UWORD	localmsec;
	UWORD	localsecond;
	UWORD	localminute;
	
	*localascstring = NULL;
	localmsec = localtenmmsec % 100;
	localsecond = (localtenmmsec / 100) % 60;
	localminute = ((localtenmmsec / 100) / 60) % 60;
	CMN_UnsignedIntToASC_NULL( localascstring, localminute, 2, '0' );
	localascstring[2] = 0x27;
	CMN_UnsignedIntToASC_NULL( &localascstring[3],
	  localsecond, 2, '0' );
	localascstring[5] = 0x22;
	CMN_UnsignedIntToASC_NULL( &localascstring[6],
	  localmsec, 2, '0' );
}
#endif	/**	PRO_CLASS1 == ENABLE	*/

