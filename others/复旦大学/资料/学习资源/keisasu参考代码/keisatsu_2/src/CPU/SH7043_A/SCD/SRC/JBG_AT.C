/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/27
*        FILE NAME:  jbg_at.c
*       Task ID No:
*      DESCRIPTION:  ＡＴ(Adaptive templates)
*                    T.82(JBIG)によるアダプティブテンプレートモジュールのファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.85(JBIG)によるＡＴ(Adaptive templates)処理
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_AT(void)
{
	/** 今のところサポートせず */
}


