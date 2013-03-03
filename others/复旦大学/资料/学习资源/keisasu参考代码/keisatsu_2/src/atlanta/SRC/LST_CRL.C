/*************************************************************************
*	System		: SHIRAKABA
*	File Name	: LST_CRL.C
*	Author		: 村松繁治
*	Date		: 2001/10/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 通信結果プリント
*	Maintenance	:
*
*	Copyright (C) 1999 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#if ( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif
#if ( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
/*************************************************************************
	module		:[通信結果プリントヘッダ印刷]
	functiom	:[通信結果プリントのヘッダを印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2001/07/17]
	author		:[佐々木佳世]
*************************************************************************/
WORD	Print_CRL_Head(
			const UWORD	job)		/* 印刷対象JOB番号 */
{
	WORD	ret;					/* 実行結果 */
	UBYTE	LocateX;				/* セット元文字列ｘ方向セット位置 */
	UBYTE	time_length;			/* 日時の印字サイズ */

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* 2回線Fax番号表示 By M.Tachibana 2001/09/26 */
	JournalLineNumber = SYB_JournalFile[job].StackNumber + 1;

	if( SYB_JournalFile[job].Type == TXTYPE ){			/* 送信の時 */
		/*１改行＋発信元名、番号印刷＋２改行＋見出し＋１改行*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
		LocateX = (80 - CMN_StringLength(PWRD_TransmitResult_K)) / 2;
		if ( (ret = Print_Head1_Common(PWRD_TransmitResult_K, LST_NOT, LocateX )) != OK ) {
			return ( ret );
		}
#else
		LocateX = (80 - CMN_StringLength(PWRD_TransmitResult)*2) / 2;
		if ( (ret = Print_Head1_Common(PWRD_TransmitResult, LST_XXX_TWI_XXX, LocateX )) != OK ) {
			return ( ret );
		}
#endif
	}
	else{					/* 受信の時 */
		/*１改行＋発信元名、番号印刷＋２改行＋見出し＋１改行*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
		LocateX = (80 - CMN_StringLength(PWRD_ReceiveResult_K)) / 2;
		if ( (ret = Print_Head1_Common(PWRD_ReceiveResult_K, LST_NOT, LocateX )) != OK ) {
			return ( ret );
		}
#else
		LocateX = (80 - CMN_StringLength(PWRD_ReceiveResult)*2) / 2;
		if ( (ret = Print_Head1_Common(PWRD_ReceiveResult, LST_XXX_TWI_XXX, LocateX )) != OK ) {
			return ( ret );
		}
#endif
	}

	/*現在時間*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if (0)
//	TimeDataAsciiNULL( OFF, SYB_CurrentTime, List.S.Work, 0 );
#else
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	List.S.Work[24] = NULL;
#endif

	/* 日付を右枠線にそろえます 2002/08/27 By M.Maeda */
	/*CMN_StringCopy( &List.S.Print[37-1], List.S.Work);*/
	CMN_StringCopy( &List.S.Print[47-1], List.S.Work);

	/* タイトル印字 */
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
}


/*************************************************************************
	module		:[通信結果プリント明細印刷]
	function	:[通信結果プリントの明細部分を印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2001/07/17]
	author		:[佐々木佳世]
*************************************************************************/
WORD	Print_CRL_Specifi(
			const UWORD	job )		/* 印刷対象JOB番号 */
{
	WORD	ret;					/* 実行結果 */
#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
#endif

	/* 上部罫線印字 */
	Print_Conf_List_Line( 6, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* No. */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_No );
	CMN_UnsignedIntToASC( &List.S.Print[34], (UWORD)SYB_JournalFile[job].Number, 3, '0' );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Location */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Location );

#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//	if (SYB_JournalFile[job].RemoteID_TTI[0] == '!'){
//		length = CMN_StringLength(SYB_MercuryDialBuffer);	/* マキュリー登録桁 */
//
//		List.S.Print[34] = '[';
//		if (length > 18){
//			CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, 19);
//		}
//		else{
//			List.S.Print[35 + length] = ']';
//			
//			CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, length);
//			CMN_StringCopyNumUntilNull( &List.S.Print[36 + length], &SYB_JournalFile[job].RemoteID_TTI[1],
//				(SYS_JOURNAL_RMT_MAX - length - 3) );
//		}
//	}
//	else{
//		CMN_StringCopyNumUntilNull( &List.S.Print[34], &SYB_JournalFile[job].RemoteID_TTI[0], (SYS_JOURNAL_RMT_MAX - 1) );
//	}
#else
	CMN_StringCopyNumUntilNull( &List.S.Print[34], &SYB_JournalFile[job].RemoteID_TTI[0], (SYS_JOURNAL_RMT_MAX - 1) );
#endif

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Mode */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Mode );
	CommunicationModeName( SYB_JournalFile[job].Mode, &List.S.Print[34], &List.S.Attribute[34] );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Start */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Start );
 	CMN_MemorySet( List.S.Work, 20, NULL );	/* （作業に必要なエリア + α）分 初期化しておきます。 */
#if (1)
 #if defined(STOCKHM2) /*Mod by SMuratec C.P 2004/06/18 */
	CriterionMinuteToDayTimeAsc( SYB_JournalFile[job].StartTime/60, LST_MMDDHHMM2, List.S.Work );
 #else
	CriterionMinuteToDayTimeAsc( SYB_JournalFile[job].StartTime/60, LST_YYYYMMDDHHMM2, List.S.Work );
 #endif
#else
//	if (CHK_JournalYearPrint()) {
//		CriterionMinuteToDayTimeAsc( SYB_JournalFile[job].StartTime/60, LST_YYYYMMDDHHMM2, List.S.Work );
//	}
//	else {
//		CriterionMinuteToDayTimeAsc( SYB_JournalFile[job].StartTime/60, LST_MMDDHHMM, List.S.Work );
//	}
#endif

	LST_RemoveAscString1stSpace( &List.S.Print[34], List.S.Work );

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Time */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Time );
	CMN_MemorySet( List.S.Work, 10, NULL );	/* （作業に必要なエリア + α）分 初期化しておきます。 */
	SecondToMinuteSecondAsc( SYB_JournalFile[job].TotalTime, List.S.Work , ' ' );
	LST_RemoveAscString1stSpace( &List.S.Print[34], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Page */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Page );
	CMN_MemorySet( List.S.Work, 5, NULL );	/* （作業に必要なエリア + α）分 初期化しておきます。 */
	CMN_UnsignedIntToASC( List.S.Work, (UWORD)SYB_JournalFile[job].Page, 3, ' ' );
	LST_RemoveAscString1stSpace( &List.S.Print[34], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

#if ( PRO_DEPARTMENT == ENABLE )	/* 部門有り *//* DVT: Modify by SMuratec K.W.Q 2004/09/08 */
	/* Code */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Code );
	if ( (CHK_DepartmentON() != OFF) && (CHK_SectionCheckProtect() != OFF) ) {
		if (SYB_JournalFile[job].DepartmentCode != 0xffff) {
			List.S.Print[34] = '*';
			List.S.Print[35] = '*';
			List.S.Print[36] = '*';
			List.S.Print[37] = '*';
		}
	}
	else {
		if (SYB_JournalFile[job].DepartmentCode != 0xffff) {
			CMN_UnsignedIntToASC( &List.S.Print[34], (UWORD)SYB_JournalFile[job].DepartmentCode, 4, '0' );
		}
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
#endif

	/* Result */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Result );
	if ( (SYB_JournalFile[job].Result & LST_ECM) != 0 ) {
		List.S.Print[34] = '*';
	
	}
	if ( (SYB_JournalFile[job].Result & V34_MODE_SET) != 0 ) {	/* Ｖ３４交信時 */
		List.S.Print[34] = '#';
	}
	if ( SYB_JournalFile[job].Type == TXTYPE ) {
		CommunicationResultName(SYB_JournalFile[job].Result, LST_NAME_SHORT, LST_JOURNAL_TX, &List.S.Print[35], &List.S.Attribute[35]);
	}
	else {
		CommunicationResultName(SYB_JournalFile[job].Result, LST_NAME_SHORT, LST_JOURNAL_RX, &List.S.Print[35], &List.S.Attribute[35]);
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* Note */
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	LST_RemoveAscString1stSpace( &List.S.Print[14], PWRD_Note );
	CommunicationKindName( SYB_JournalFile[job].Kind, LST_NAME_1, &List.S.Print[34], &List.S.Attribute[34] );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 下部罫線印字 */
	Print_Conf_List_Line( 5, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	
	return ( OK );
}


/*************************************************************************
	module		:[通信結果プリントフッター印刷]
	functiom	:[通信結果プリントのフッターを印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2001/07/17]
	author		:[佐々木佳世]
*************************************************************************/
WORD	Print_CRL_Foot(void)
{
	WORD	ret;					/* 実行結果 */

	/*１行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED + 1 )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
}


/*************************************************************************
	module		:[通信結果プリント印刷]
	function	:[通信結果プリントを印刷する]
	common		:[
					List			:
					SYB_JournalFile	;
	]
	condition	:[]
	commment	:[	]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2001/07/017]
	author		:[佐々木佳世]
*************************************************************************/
WORD	PrintComResultList( void )
{
	WORD	ret;					/* 実行結果 */
	UWORD	job_no;					/* 印刷対象Job番号 */

	job_no = SYS_DocumentPrintNo;		/* Job番号の保管 */

	/* ヘッダー処理 */
	if ( (ret = Print_CRL_Head(job_no)) != OK ) {
		return ( ret );
	}

	/* 明細処理 */
	if ( (ret = Print_CRL_Specifi(job_no)) != OK ) {
		return ( ret );
	}

	/* フッター処理 */
	if ( (ret = Print_CRL_Foot()) != OK ) {
		return ( ret );
	}
	return ( OK );
}
#endif /* (PRO_COM_RESULT == ENABLE) */
