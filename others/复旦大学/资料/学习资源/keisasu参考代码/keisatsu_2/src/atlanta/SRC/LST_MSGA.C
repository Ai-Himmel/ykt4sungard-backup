/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSGA.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: チェックメッセージＡ原稿添付
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\apl_msg.h"
#include 	"\src\atlanta\define\std.h"

#include 	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include 	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include 	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"

/*************************************************************************
	module		:[チェックメッセージA 原稿添付印刷]
	function	:[チェックメッセージAを印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD 			Doc_ChkMsg(
						 void )			/*なし*/
{
	register WORD	ret;					/*実行結果*/

	ret = Print_CommErr_ChkMsg_Common( LST_DOC_CHECKMSG );

	return ( ret );
}

