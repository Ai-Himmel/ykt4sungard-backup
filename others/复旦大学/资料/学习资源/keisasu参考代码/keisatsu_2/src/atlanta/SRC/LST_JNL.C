/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_JNL.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 通信管理レポート「送受信」
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\status.h"	/* 97/04/20 M.Kuwahara */
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysjrnl.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\memsw\define\mems_pro.h"/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/09 */

#if ( PRO_PAT_JOURNAL == ENABLE )
/** ＰＡＴデバッグ用 By O.K Jul,03,1995 **/
#include	"\src\atlanta\define\pat_def.h"
#include	"\src\atlanta\ext_v\pat_data.h"
#endif

#include	"\src\atlanta\define\mlt_pro.h" /* 1997/09/16 Y.Matsukuma */
#include	"\src\atlanta\define\fcm_def.h"

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
#include	"\src\atlanta\define\mntsw_h.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

UBYTE		JournalYearPrint;				/* 西暦４桁対応 bythonda1999/11/16	*/
											/* ICHOUから移植してきました		*/
#if(PRO_PAT_JOURNAL == DISABLE)
/*************************************************************************
	module		:[通信管理レポート印刷]
	function	:[通信管理レポートを印刷する]
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
WORD	Print_Journal_List(void)
{
	register WORD	ret;	/*実行結果*/

	JournalYearPrint = CHK_JournalYearPrint();	/* 西暦４桁対応 bythonda1999/11/16	*/
												/* ICHOUから移植してきました		*/

	if ( (ret = Print_Journal_List2()) != OK ) {
		if ( ret == MSG_PRN_LST_STOPSW_ON ) {
			SYS_TxAutoJournalPrintRequest = 0;
			SYS_RxAutoJournalPrintRequest = 0;
		}
		return ( ret );
	}
	SYS_TxAutoJournalPrintRequest = 0;
	SYS_RxAutoJournalPrintRequest = 0;
	return ( OK );
}

#if defined(STOCKHM2)	/* Mod by SMuratec C.P for 送受信別プリント */
/*************************************************************************
	module		:[通信管理レポート印刷2]
	function	:[通信管理レポートを印刷する]
	common		:[
		List			:
		BKJournalFile	:
		SYB_JournalFile	;
	]
	condition	:[]
	commment	:[
		SYS_TxAutoJournalPrintRequest,SYS_RxAutoJournalPrintRequestを
		クリアーするタイミングの問題で、わざわざPrint_Journal_List()
		とは、別関数としている。
	]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD	Print_Journal_List2(void )				/*なし*/
{
	BYTE	i;								/*loop*/
	UBYTE	point;							/*位置ｗ*/
	UBYTE	bk_point;						/*位置退避ｗ*/
	UBYTE	count;							/*ﾃﾞｰﾀ数ｗ*/
	UBYTE	page;							/* ﾍﾟｰｼﾞｶｳﾝﾀ */
	UBYTE	line_cnt;						/* 行数ｶｳﾝﾀ */
	register WORD	ret;					/*実行結果*/
 #if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/16 */
	UBYTE	board_cnt;						/*モデムの数*/
	UBYTE	stack_cnt;						/*スタックカウンタ*/
	UBYTE	check;							
	UBYTE	check_item;
 #endif
	UBYTE	bk_count;							/*ﾃﾞｰﾀ数ｗ*/
	UBYTE	bk_point2;		/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */
	UBYTE	type;		/* 通信種類 */

 #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
	UBYTE	list_cut_request;	/* Add by O.Kimoto 1998/11/28 */

	if ((SYB_MaintenanceSwitch[MNT_SW_H1] & LIST_PRINT_NO_CUT) == LIST_PRINT_NO_CUT) {
		list_cut_request = 0;
	}
	else {
		list_cut_request = 1;
	}
 #endif

	CMN_DisableInterrupt();

	bk_point2 = 0;	/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */

	/*通信管理記録ﾌｧｲﾙのﾃﾞｰﾀｽﾀｰﾄ位置とﾃﾞｰﾀ数を求める*/
	JournalPointCount(SYB_JournalPoint, SYS_JOURNAL_MAX, &bk_point, &bk_count, SYB_JournalFile[SYB_JournalPoint].Number);

	/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信のデータと*/
	/*なる可能性があるため、一番上に印刷されるデータのみﾊﾞｯﾌｧに退避する。*/
	for (i = 0; i < 10; i++) {	/* add for() 1997/10/29 */
		/*ほんまは、こんな代入文は使っていいような悪いような う～ん */
		/*とりあえず、ＳＨとＶ５３は大丈夫みたいやし、これのほうが楽やしこうしとこ */
		
#if (0)
** 		/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */
** 		BKJournalFile[i] = SYB_JournalFile[bk_point+i];
#else
		if ((bk_point + i) >= SYS_JOURNAL_MAX ) {
			bk_point2 = SYS_JOURNAL_MAX;
		}
		else {
			bk_point2 = 0;
		}
		BKJournalFile[i] = SYB_JournalFile[bk_point+i-bk_point2];

 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
		BKJournalPoint[i] = bk_point+i-bk_point2;
 #endif

#endif

	}
	CMN_EnableInterrupt();

	/*
	 * ジャーナルは、１ページに２５件分記載されます。送信・受信どちらかが２５件ちょうど
	 * の時、タイトルだけ書いてしまうと言う不具合対策の２次障害で、１００件分すべて
	 * プリントされないと言う不具合発生。
	 * もともと、ジャーナルの検索カウンタ（i）とジャーナル検索数（count）を比較して
	 * 次データ有り無しの判断をするのは間違ってます。
	 * ジャーナルは送信・受信混ざってはいってるからです。
	 * これを、送信・受信で印字すべきデータ数をカウントし、その分書くように変更しました。
	 *
	*/

 #if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/16 */
	JournalLineNumber = 1;		/* ２回線追加 1997/09/16 Y.Matsukuma */
	board_cnt	= OPT_CountModems();
	stack_cnt	= 0;

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
	InternalLineNumber = 0;
  #endif
	while (board_cnt >= JournalLineNumber) {

		/* ジャーナル印字時、該当通信分がない場合に、タイトルのみ印字しているが、
		** このような場合は印字しないようにしてほしいというフィールドより仕様変更要求があり
		** メモリスイッチにて対応できるようにします。（メモリスイッチＨ：５－０～７、Ｈ：６－０～１）
		** 尚、変更後の仕様は、
		**    - 回線毎にジャーナルプリントのＯＮ／ＯＦＦが出来る（メモリスイッチＨ：５－０～７、Ｈ：６－０）
		**    - 該当通信分（送・受信）がない場合にタイトルのみをプリントするしない（メモリスイッチＨ：６－１）
		**  By O.Kimoto 1999/11/09
		*/
  #if (PRO_LINENUMBER == TWICE_LINE)
		if (CheckJournalPrintEachLine(stack_cnt,InternalLineNumber) == TRUE) {
  #else
		if (CheckJournalPrintEachLine(stack_cnt) == TRUE) {
  #endif
			if (SYS_JournalPrintType == BOTHTYPE){
				type = TXTYPE;
			}
			else{
				type = SYS_JournalPrintType;
			}
			
			while (type != FALSE) {
				page	= 1;
				point 	= bk_point;
				i	= 0;
				check = 0;
				check_item = 0;
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
				count = JournalCount(type, stack_cnt, bk_point, InternalLineNumber);
  #else
				count = JournalCount(type, stack_cnt, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif
				while(1) {

					/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
					if (count == 0) {
						if (CHK_JournalPrintTitle() == 0) {	/* 論理逆 By O.Kimoto 1999/12/20 */
							break;
						}
					}

					if ( (ret =	Print_TrxRcvJournal_Head( 0, page, type ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
						return ( ret );
					}
					if ( board_cnt > 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
						line_cnt = (UBYTE)(PaperSizeLen() - 13);/*印刷可能行数ｾｯﾄ*/
  #else
						line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #endif
					}
					else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
						line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
						line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
					}
					while( 1 ){

  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
						if (list_cut_request == 1){
							if( line_cnt <= 2 ){		/* 改ページ */
								break;
							}
						}
  #else
						if( line_cnt <= 2 ){		/* 改ページ */
							break;
						}
  #endif

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
						/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
						/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
						/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
						/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
						/*退避したﾃﾞｰﾀにて印刷する。*/
						if ( i < 10 ) {
							if (stack_cnt == 0) {	/* 標準ラインのとき */
								/*
								** ちょっとややこしい条件になってしもた
								** ジャーナルの回線＝＝内蔵の送信 ＆＆ 
								** （内蔵の中で標準ラインの場合で標準ライン印字の場合 || （内蔵の中で拡張ラインの場合で拡張ライン印字の場合）
								** のとき印字します
								*/
								if ((BKJournalFile[i].Type == type)
								&& (BKJournalFile[i].StackNumber == stack_cnt)
								&& (CheckInternalLinePrintEnable(InternalLineNumber, BKJournalFile[i].Option) == TRUE)) {
									if ((ret = Print_Journal_List_Specifi(			/*1明細印刷*/
									  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
										return ( ret );
									}
									line_cnt	-= 2;
									check++;	/* 1998/02/03 Y.Matsukuma */
								}
							}
							else {	/* オプションラインのとき */
								if (( BKJournalFile[i].Type == type) 
								&& (BKJournalFile[i].StackNumber == stack_cnt)) {
									if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
									  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
										return ( ret );
									}
									line_cnt	-= 2;
									check++;	/* 1998/02/03 Y.Matsukuma */
								}
							}
						}
						else {
							if (stack_cnt == 0) {	/* 標準ラインのとき */
								if ((SYB_JournalFile[point].Type == type)
								&&  (SYB_JournalFile[point].StackNumber == stack_cnt)
								&& (CheckInternalLinePrintEnable(InternalLineNumber, SYB_JournalFile[point].Option) == TRUE)) {
									if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
									  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
										return ( ret );
									}
									line_cnt	-= 2;
									check++;		/* 1998/02/03 Y.Matsukuma */
								}
							}
							else {	/* オプションラインのとき */
								if (( SYB_JournalFile[point].Type == type ) 
								&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
									if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
									  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
										return ( ret );
									}
									line_cnt	-= 2;
									check++;		/* 1998/02/03 Y.Matsukuma */
								}
							}
						}
  #else	/* (PRO_LINENUMBER == TWICE_LINE) */
						/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
						/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
						/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
						/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
						/*退避したﾃﾞｰﾀにて印刷する。*/
						if ( i < 10 ) {
							if (( BKJournalFile[i].Type == type ) 
								&& ( BKJournalFile[i].StackNumber == stack_cnt )){
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
									return ( ret );
								}
								line_cnt	-= 2;
								check++;	/* 1998/02/03 Y.Matsukuma */
							}
						}
						else {
							if (( SYB_JournalFile[point].Type == type ) 
								&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
									return ( ret );
								}
								line_cnt	-= 2;
								check++;		/* 1998/02/03 Y.Matsukuma */
							}
						}
  #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
						point++;
						if ( point >= SYS_JOURNAL_MAX ) {
							point = 0;
						}
						i++;
						if( i >= (BYTE)bk_count ){	/* 保険 */
							check_item = 1;
							break;
						}
						if( check >= count ){	/* 1998/02/03 Y.Matsukuma */
							check_item = 1;
							break;
						}
					}
					/*Print_TrxRcvJournal_Head( 1, page, type );1997/11/27 */	/* フッタ印字 */
					if ( (ret =	Print_TrxRcvJournal_Head( 1, page, type ) ) != OK ) {	/*フッタ印刷*/
						return ( ret );
					}

					if (check_item == 1) {
						break;
					}
					page++;
				}
				
				if (type == TXTYPE && SYS_JournalPrintType == BOTHTYPE) {
					type = RXTYPE;
				}
				else {
					type = FALSE;
				}
			}
		}	/* ジャーナル仕様変更分 */
		
		
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
		/* 内蔵回線で標準回線を印字し終わったら、次は内蔵回線の拡張回線の印字に移ります */
		if ((stack_cnt == 0)
		&& (InternalLineNumber == 0)
		&& (CHK_UNI_JrnlInternalSeprate())) {	/* 標準／拡張を分けてプリントするとき */
			InternalLineNumber++;
		}
		else {
			InternalLineNumber = 0;
			JournalLineNumber++;
			stack_cnt++;
			/* モデム基盤の間に回転基盤等が入った場合の処理 */
			if (CHK_OptionLineExist( stack_cnt ) != 1) {
				stack_cnt++;
			}
		}
  #else
		JournalLineNumber++;
		stack_cnt++;
		/* モデム基盤の間に回転基盤等が入った場合の処理 */
		if (CHK_OptionLineExist( stack_cnt ) != 1) {
			stack_cnt++;
		}
  #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
	}

 #else	/* ここまで２回線用 */

	if (SYS_JournalPrintType == BOTHTYPE){
		type = TXTYPE;
	}
	else{
		type = SYS_JournalPrintType;
	}
	
	while (type != FALSE) {
		  
		page	= 1;
		point = bk_point;
		i	= 0;

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */	/* 1998/09/21 Add By M.Kuwahara */
		count = JournalCount(type, 0, bk_point, InternalLineNumber);
  #else
		count = JournalCount(type, 0, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif
		while (count > 0){
			if ( (ret =	Print_TrxRcvJournal_Head( 0, page, type ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
				return ( ret );
			}
			if ( page == 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
				line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
				line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
			}
			else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
				line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
				line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
			}
			while( 1 ){
  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
				if (list_cut_request == 1){
					if( line_cnt <= 2 ){		/* 改ページ */
						break;
					}
				}
  #else
				if( line_cnt <= 2 ){		/* 改ページ */
					break;
				}
  #endif
				/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
				/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
				/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
				/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
				/*退避したﾃﾞｰﾀにて印刷する。*/
  #if (0)	/* 1998/10/06 By M.Kuwahara */
  //			if ( i == 0 ) {
  //				if ( BKJournalFile[0].Type == type ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)BKJournalFile, 0 )) != OK ) {
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  //			else {
  //				if ( SYB_JournalFile[point].Type == type ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  #else
				if (i < 10) {
					if ( BKJournalFile[i].Type == type ) {
						if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
						  (struct SYS_JournalData_t *)BKJournalFile, i)) != OK ) {
							return ( ret );
						}
						line_cnt	-= 2;
						count--;
					}
				}
				else {
					if ( SYB_JournalFile[point].Type == type ) {
						if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
						  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
							return ( ret );
						}
						line_cnt	-= 2;
						count--;
					}
				}
  #endif	/* #if (0) */
				point++;
				if ( point >= SYS_JOURNAL_MAX ) {
					point = 0;
				}
				i++;
				/* iは配列分のﾃﾞｰﾀ数をｶｳﾝﾄするので、送信分だけのｶｳﾝﾀと比較しても意味が無い 	*/
				/* 									1998/10/06 By M.Kuwahara 				*/
	/*			if( i >= (BYTE)count ){*/
				if (count <= 0) {
					break;
				}
			}
			/*Print_TrxRcvJournal_Head( 1, page, type );*/	/* フッタ印字 */
			if ( (ret =	Print_TrxRcvJournal_Head( 1, page, type ) ) != OK ) {	/*フッタ印刷*/
				return ( ret );
			}
			page++;
		}
		if (type == TXTYPE && SYS_JournalPrintType == BOTHTYPE) {
			type = RXTYPE;
		}
		else {
			type = FALSE;
		}
	}
 #endif	/* (PRO_MULTI_LINE == ENABLE) */
	return ( OK );
}

#elif defined(HINOKI3) && !defined(JPNNTT)	/* by K.Watanabe 2004/10/19 *//* NTT仕様は除く T.Nose 2005/01/13 */
/**********************************************************************************************************************/
/**
	@brief		通信管理レポート印刷２（降順プリント＋日報対応）
	
	@li			
	@param		なし
	@return		なし
	@note		なし
	@date		2004/10/19 作成
	@author		渡辺一章
*/
/**********************************************************************************************************************/
WORD Print_Journal_List2(void)
{
	register WORD	ret;			/* 実行結果 */
	UBYTE	i;						/* loop */
	UBYTE	page_number;			/* 印字ページ数 */
	UBYTE	line_cnt;				/* 印字行数 */
	UBYTE	print_start_pos;		/* 印字開始ジャーナル配列番号 */
	UBYTE	print_data_pos;			/* 印字ジャーナル配列番号 */
	UBYTE	print_pos;				/* 退避データを含めた印字ジャーナル配列番号 */
	UBYTE	print_data_count;		/* 印字データ件数 */
	UBYTE	print_data_max;			/* 印字データ最大件数 */
	UBYTE	print_com_type;			/* 印字するジャーナルの通信種類 */
	UBYTE	bkup_data_pos;			/* 退避するジャーナルの配列番号 */
	UBYTE	bkup_data_count;		/* 退避するジャーナルデータ件数 */
	BOOL	is_list_cut_request;	/* 定形サイズでカットするか */
	BOOL	is_use_backup_data;		/* 退避したデータを使用するか */
	BOOL	is_descending_print;	/* 降順にプリントするか */
	struct SYS_JournalData_t	*print_journal_ptr;

	bkup_data_count = 10;	/* 退避するジャーナルデータ件数（従来の機種と合わせておきます） */

  #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/27 */
  	InternalLineNumber = SYS_EXT_LINE_COM;
  #endif /* defined (KEISATSU) */
  
	if (CHK_UNI_JournalFixedFormSizeCut()) {	/* 定形サイズでカットする時 */
		is_list_cut_request = TRUE;
	}
	else {										/* 定形サイズでカットしない時 */
		is_list_cut_request = FALSE;
	}

	if (CHK_UNI_JournalDescendingPrint()) {	/* 降順にプリントする時 */
		is_descending_print = TRUE;
	}
	else {									/* 昇順にプリントする時 */
		is_descending_print = FALSE;
	}

	CMN_DisableInterrupt();

	if (SYB_JournalFile[SYB_JournalPoint].Number == 0xFFFF) {	/* ジャーナルデータがまだ一周していない時 */
		if (is_descending_print) {	/* 降順にプリントする時 */
			print_start_pos = SYB_JournalPoint - 1;
		}
		else {						/* 昇順にプリントする時 */
			print_start_pos = 0;
		}
		print_data_max = SYB_JournalPoint;
	}
	else {														/* ジャーナルデータがすでに一周している時 */
		if (is_descending_print) {	/* 降順にプリントする時 */
			if (SYB_JournalPoint == 0) {
				print_start_pos = SYS_JOURNAL_MAX - 1;
			}
			else {
				print_start_pos = SYB_JournalPoint - 1;
			}
		}
		else {						/* 昇順にプリントする時 */
			print_start_pos = SYB_JournalPoint;
		}
		print_data_max = SYS_JOURNAL_MAX;
	}

	if (SYS_DocumentPrintItem == LST_AUTO_ALL_JOURNAL) {	/* 通信管理記録自動プリントの時 */
		SYB_DailyReportPrintPos = SYB_JournalPoint;
	}
	else if (SYS_DocumentPrintItem == LST_DAILY_REPORT) {	/* 通信管理記録日報プリントの時 */
		/* 印字開始ジャーナル配列番号の補正 */
		if (!is_descending_print) {	/* 昇順にプリントする時 */
			print_start_pos = SYB_DailyReportPrintPos;
		}

		/* 印字データ最大件数の補正 */
		if (SYB_JournalPoint > SYB_DailyReportPrintPos) {
			print_data_max = SYB_JournalPoint - SYB_DailyReportPrintPos;
		}
		else {
			print_data_max = (SYS_JOURNAL_MAX - SYB_DailyReportPrintPos) + SYB_JournalPoint;
		}

		/* 印字開始位置を決定したら、自動プリント用のカウンタを初期化 */
		SYB_AutoJournalCounter = 0;
		SYB_DailyReportPrintPos = SYB_JournalPoint;
	}

	/* 印字件数から退避したデータを使用するかをチェックします */
	if (SYS_JOURNAL_MAX - print_data_max < bkup_data_count) {
		is_use_backup_data = TRUE;
	}
	else {
		is_use_backup_data = FALSE;
	}

	if (is_use_backup_data) {	/* 印字開始位置以降まで印字する時 */
		/* 印字中に通信された時の為に、古いジャーナルデータを退避しておきます */
		bkup_data_pos = SYB_JournalPoint;
		for (i = 0; i < bkup_data_count; i++) {
			BKJournalFile[i] = SYB_JournalFile[bkup_data_pos];
 #if (PRO_MULTI_T30_MONITOR == ENABLE)
			BKJournalPoint[i] = bkup_data_pos;
 #endif
			bkup_data_pos++;
			if (bkup_data_pos >= SYS_JOURNAL_MAX) {
				bkup_data_pos = 0;
			}
		}
	}

	CMN_EnableInterrupt();

	if (SYS_JournalPrintType == BOTHTYPE){
		print_com_type = TXTYPE;
	}
	else{
		print_com_type = SYS_JournalPrintType;
	}

	while (print_com_type != FALSE) {
		page_number = 1;
		print_data_pos = print_start_pos;
		print_data_count = print_data_max;

		while (print_data_count > 0){
 #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);	/* 印刷可能行数セット */
 #else
  #if 0
			line_cnt = (UBYTE)(PaperSizeLen() - 11);	/* 印刷可能行数セット */
  #else		/* PaperSizeLen()をコールしてライン数を求めると定型よりかなり短いため、HINOKI3のみ下記処理にします */
  			switch (PaperKind()) {
			case	SYS_B4_PAPER:
 #if defined (KEISATSU) /* 警察FAX 警電/加入の行が増えた分を修正 O.Oshima 2005/12/07 */
				line_cnt = (88 - 12);
 #else
				line_cnt = (88 - 11);
 #endif
				break;
  			case	SYS_A4_PAPER:
			default:
 #if defined (KEISATSU) /* 警察FAX 警電/加入の行が増えた分を修正 O.Oshima 2005/12/07 */
  				line_cnt = (72 -12);
 #else
  				line_cnt = (72 -11);
 #endif
			}
  #endif
 #endif

			/* ヘッダー印字 */
			if ((ret = Print_TrxRcvJournal_Head(0, page_number, print_com_type)) != OK) {
				return (ret);
			}

			while (1) {
				if (is_list_cut_request) {	/* 定形サイズでカットする時 */
					if (line_cnt <= 2) {	/* 改ページ */
						break;
					}
				}

				/* 印字データの設定 */
				if (is_descending_print) {	/* 降順にプリントする時 */
					/* バックアップデータを使用する時 */
					if (is_use_backup_data && (print_data_count <= bkup_data_count - (SYS_JOURNAL_MAX - print_data_max))) {
						/* 古いデータは印字中の通信で上書きされている可能性があるので、退避したデータを参照します */
						print_journal_ptr = BKJournalFile;
						if (print_data_pos > print_start_pos) {	/* 印字開始データ以降のデータの時 */
							print_pos = print_data_count + (SYS_JOURNAL_MAX - print_data_max) - 1;
						}
						else {									/* 印字開始データ以前のデータの時 */
							print_pos = (SYS_JOURNAL_MAX - 1 - print_start_pos) + print_data_pos;
						}
					}
					else {
						print_journal_ptr = SYB_JournalFile;
						print_pos = print_data_pos;
					}
				}
				else {						/* 昇順にプリントする時 */
					/* バックアップデータを使用する時 */
					if (is_use_backup_data && (print_data_max - print_data_count < bkup_data_count - (SYS_JOURNAL_MAX - print_data_max))) {
						/* 古いデータは印字中の通信で上書きされている可能性があるので、退避したデータを参照します */
						print_journal_ptr = BKJournalFile;
						print_pos = (SYS_JOURNAL_MAX - print_data_max) + (print_data_max - print_data_count);
					}
					else {
						print_journal_ptr = SYB_JournalFile;
						print_pos = print_data_pos;
					}
				}

				if (((print_journal_ptr + print_pos)->Type == print_com_type) && ((print_journal_ptr + print_pos)->Number != 0xFFFF)) {
	#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/27 */
					if (CheckInternalLinePrintEnable(InternalLineNumber, (print_journal_ptr + print_pos)->Option) == TRUE) {
						/* １明細印字 */
						if ((ret = Print_Journal_List_Specifi((struct SYS_JournalData_t *)print_journal_ptr, print_pos)) != OK) {
							return (ret);
						}
						line_cnt -= 2;
					}
	#else /* !defined (KEISATSU) */
					/* １明細印字 */
					if ((ret = Print_Journal_List_Specifi((struct SYS_JournalData_t *)print_journal_ptr, print_pos)) != OK) {
						return (ret);
					}
					line_cnt -= 2;
	#endif /* defined (KEISATSU) */
				}

				if (is_descending_print) {	/* 降順にプリントする時 */
					if (print_data_pos == 0) {
						print_data_pos = SYS_JOURNAL_MAX;
					}
					print_data_pos--;
				}
				else {						/* 昇順にプリントする時 */
					print_data_pos++;
					if (print_data_pos == SYS_JOURNAL_MAX) {
						print_data_pos = 0;
					}
				}

				print_data_count--;
				if (print_data_count <= 0) {
					break;
				}
			}

			/* フッター印字 */
			if ((ret = Print_TrxRcvJournal_Head(1, page_number, print_com_type)) != OK) {
				return (ret);
			}

			page_number++;
		}

	#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/27 */
		if ((InternalLineNumber == SYS_EXT_LINE_COM)
		&& (CHK_UNI_JrnlInternalSeprate())) {	/* 標準／拡張を分けてプリントするとき */
			InternalLineNumber = SYS_STD_LINE_COM;
			continue;
		}
		else {
			InternalLineNumber = SYS_EXT_LINE_COM;
		}
	#endif /* defined (KEISATSU) */
		if (print_com_type == TXTYPE && SYS_JournalPrintType == BOTHTYPE) {
			print_com_type = RXTYPE;
		}
		else {
			print_com_type = FALSE;
		}
	}

	return (OK);
}

#elif defined(SAKAKI) && defined(JP1)  /* SAKAKI3 by M.Maeda 2005/03/09 */
/**********************************************************************************************************************/
/**
	@brief		通信管理レポート印刷２（降順プリント＋日報対応）
	
	@li			
	@param		なし
	@return		なし
	@note		なし
	@date		2004/10/19 作成
	@author		渡辺一章
*/
/**********************************************************************************************************************/
WORD Print_Journal_List2(void)
{
	register WORD	ret;			/* 実行結果 */
	UBYTE	i;						/* loop */
	UBYTE	page_number;			/* 印字ページ数 */
	UBYTE	line_cnt;				/* 印字行数 */
	UBYTE	print_start_pos;		/* 印字開始ジャーナル配列番号 */
	UBYTE	print_data_pos;			/* 印字ジャーナル配列番号 */
	UBYTE	print_pos;				/* 退避データを含めた印字ジャーナル配列番号 */
	UBYTE	print_data_count;		/* 印字データ件数 */
	UBYTE	print_data_max;			/* 印字データ最大件数 */
	UBYTE	print_com_type;			/* 印字するジャーナルの通信種類 */
	UBYTE	bkup_data_pos;			/* 退避するジャーナルの配列番号 */
	UBYTE	bkup_data_count;		/* 退避するジャーナルデータ件数 */
	BOOL	is_list_cut_request;	/* 定形サイズでカットするか */
	BOOL	is_use_backup_data;		/* 退避したデータを使用するか */
	BOOL	is_descending_print;	/* 降順にプリントするか */
	struct SYS_JournalData_t	*print_journal_ptr;

	bkup_data_count = 10;	/* 退避するジャーナルデータ件数（従来の機種と合わせておきます） */

	if (CHK_UNI_JournalFixedFormSizeCut()) {	/* 定形サイズでカットする時 */
		is_list_cut_request = TRUE;
	}
	else {										/* 定形サイズでカットしない時 */
		is_list_cut_request = FALSE;
	}

	if (CHK_UNI_JournalDescendingPrint()) {	/* 降順にプリントする時 */
		is_descending_print = TRUE;
	}
	else {									/* 昇順にプリントする時 */
		is_descending_print = FALSE;
	}

	CMN_DisableInterrupt();

	if (SYB_JournalFile[SYB_JournalPoint].Number == 0xFFFF) {	/* ジャーナルデータがまだ一周していない時 */
		if (is_descending_print) {	/* 降順にプリントする時 */
			print_start_pos = SYB_JournalPoint - 1;
		}
		else {						/* 昇順にプリントする時 */
			print_start_pos = 0;
		}
		print_data_max = SYB_JournalPoint;
	}
	else {														/* ジャーナルデータがすでに一周している時 */
		if (is_descending_print) {	/* 降順にプリントする時 */
			if (SYB_JournalPoint == 0) {
				print_start_pos = SYS_JOURNAL_MAX - 1;
			}
			else {
				print_start_pos = SYB_JournalPoint - 1;
			}
		}
		else {						/* 昇順にプリントする時 */
			print_start_pos = SYB_JournalPoint;
		}
		print_data_max = SYS_JOURNAL_MAX;
	}

	if (SYS_DocumentPrintItem == LST_AUTO_ALL_JOURNAL) {	/* 通信管理記録自動プリントの時 */
		SYB_DailyReportPrintPos = SYB_JournalPoint;
	}
	else if (SYS_DocumentPrintItem == LST_DAILY_REPORT) {	/* 通信管理記録日報プリントの時 */
		/* 印字開始ジャーナル配列番号の補正 */
		if (!is_descending_print) {	/* 昇順にプリントする時 */
			print_start_pos = SYB_DailyReportPrintPos;
		}

		/* 印字データ最大件数の補正 */
		if (SYB_JournalPoint > SYB_DailyReportPrintPos) {
			print_data_max = SYB_JournalPoint - SYB_DailyReportPrintPos;
		}
		else {
			print_data_max = (SYS_JOURNAL_MAX - SYB_DailyReportPrintPos) + SYB_JournalPoint;
		}

		/* 印字開始位置を決定したら、自動プリント用のカウンタを初期化 */
		SYB_AutoJournalCounter = 0;
		SYB_DailyReportPrintPos = SYB_JournalPoint;
	}

	/* 印字件数から退避したデータを使用するかをチェックします */
	if (SYS_JOURNAL_MAX - print_data_max < bkup_data_count) {
		is_use_backup_data = TRUE;
	}
	else {
		is_use_backup_data = FALSE;
	}

	if (is_use_backup_data) {	/* 印字開始位置以降まで印字する時 */
		/* 印字中に通信された時の為に、古いジャーナルデータを退避しておきます */
		bkup_data_pos = SYB_JournalPoint;
		for (i = 0; i < bkup_data_count; i++) {
			BKJournalFile[i] = SYB_JournalFile[bkup_data_pos];
 #if (PRO_MULTI_T30_MONITOR == ENABLE)
			BKJournalPoint[i] = bkup_data_pos;
 #endif
			bkup_data_pos++;
			if (bkup_data_pos >= SYS_JOURNAL_MAX) {
				bkup_data_pos = 0;
			}
		}
	}

	CMN_EnableInterrupt();

	switch (SYS_DocumentPrintItem) {
	case LST_JOURNAL_TX_LIST:			/* 通信管理レポート「送信」  */
		SYS_JournalPrintType = TXTYPE;
		break;
	case LST_JOURNAL_RX_LIST:			/* 通信管理レポート「受信」  */
		SYS_JournalPrintType = RXTYPE;
		break;
	default:
		SYS_JournalPrintType = BOTHTYPE;
		break;
	}

	if (SYS_JournalPrintType == BOTHTYPE){
		print_com_type = TXTYPE;
	}
	else{
		print_com_type = SYS_JournalPrintType;
	}

	while (print_com_type != FALSE) {
		page_number = 1;
		print_data_pos = print_start_pos;
		print_data_count = print_data_max;

		while (print_data_count > 0){
 #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);	/* 印刷可能行数セット */
 #else
			line_cnt = (UBYTE)(PaperSizeLen() - 11);	/* 印刷可能行数セット */
 #endif

			/* ヘッダー印字 */
			if ((ret = Print_TrxRcvJournal_Head(0, page_number, print_com_type)) != OK) {
				return (ret);
			}

			while (1) {
				if (is_list_cut_request) {	/* 定形サイズでカットする時 */
					if (line_cnt <= 2) {	/* 改ページ */
						break;
					}
				}

				/* 印字データの設定 */
				if (is_descending_print) {	/* 降順にプリントする時 */
					/* バックアップデータを使用する時 */
					if (is_use_backup_data && (print_data_count <= bkup_data_count - (SYS_JOURNAL_MAX - print_data_max))) {
						/* 古いデータは印字中の通信で上書きされている可能性があるので、退避したデータを参照します */
						print_journal_ptr = BKJournalFile;
						if (print_data_pos > print_start_pos) {	/* 印字開始データ以降のデータの時 */
							print_pos = print_data_count + (SYS_JOURNAL_MAX - print_data_max) - 1;
						}
						else {									/* 印字開始データ以前のデータの時 */
							print_pos = (SYS_JOURNAL_MAX - 1 - print_start_pos) + print_data_pos;
						}
					}
					else {
						print_journal_ptr = SYB_JournalFile;
						print_pos = print_data_pos;
					}
				}
				else {						/* 昇順にプリントする時 */
					/* バックアップデータを使用する時 */
					if (is_use_backup_data && (print_data_max - print_data_count < bkup_data_count - (SYS_JOURNAL_MAX - print_data_max))) {
						/* 古いデータは印字中の通信で上書きされている可能性があるので、退避したデータを参照します */
						print_journal_ptr = BKJournalFile;
						print_pos = (SYS_JOURNAL_MAX - print_data_max) + (print_data_max - print_data_count);
					}
					else {
						print_journal_ptr = SYB_JournalFile;
						print_pos = print_data_pos;
					}
				}

				if (((print_journal_ptr + print_pos)->Type == print_com_type) && ((print_journal_ptr + print_pos)->Number != 0xFFFF)) {
					/* １明細印字 */
					if ((ret = Print_Journal_List_Specifi((struct SYS_JournalData_t *)print_journal_ptr, print_pos)) != OK) {
						return (ret);
					}
					line_cnt -= 2;
				}

				if (is_descending_print) {	/* 降順にプリントする時 */
					if (print_data_pos == 0) {
						print_data_pos = SYS_JOURNAL_MAX;
					}
					print_data_pos--;
				}
				else {						/* 昇順にプリントする時 */
					print_data_pos++;
					if (print_data_pos == SYS_JOURNAL_MAX) {
						print_data_pos = 0;
					}
				}

				print_data_count--;
				if (print_data_count <= 0) {
					break;
				}
			}

			/* フッター印字 */
			if ((ret = Print_TrxRcvJournal_Head(1, page_number, print_com_type)) != OK) {
				return (ret);
			}

			page_number++;
		}

		if (print_com_type == TXTYPE && SYS_JournalPrintType == BOTHTYPE) {
			print_com_type = RXTYPE;
		}
		else {
			print_com_type = FALSE;
		}
	}

	return (OK);
}

#else	/* #if defined(STOCKHM2) Mod by SMuratec C.P for 送受信別プリント */
/*************************************************************************
	module		:[通信管理レポート印刷2]
	function	:[通信管理レポートを印刷する]
	common		:[
		List			:
		BKJournalFile	:
		SYB_JournalFile	;
	]
	condition	:[]
	commment	:[
		SYS_TxAutoJournalPrintRequest,SYS_RxAutoJournalPrintRequestを
		クリアーするタイミングの問題で、わざわざPrint_Journal_List()
		とは、別関数としている。
	]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD	Print_Journal_List2(void )				/*なし*/
{
	BYTE	i;								/*loop*/
	UBYTE	point;							/*位置ｗ*/
	UBYTE	bk_point;						/*位置退避ｗ*/
	UBYTE	count;							/*ﾃﾞｰﾀ数ｗ*/
	UBYTE	page;							/* ﾍﾟｰｼﾞｶｳﾝﾀ */
	UBYTE	line_cnt;						/* 行数ｶｳﾝﾀ */
	register WORD	ret;					/*実行結果*/
 #if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/16 */
	UBYTE	board_cnt;						/*モデムの数*/
	UBYTE	stack_cnt;						/*スタックカウンタ*/
	UBYTE	check;							
	UBYTE	check_item;
 #endif
	UBYTE	bk_count;							/*ﾃﾞｰﾀ数ｗ*/
	UBYTE	bk_point2;		/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */

 #if defined(SAKAKI) && defined(JP0)
 	UBYTE	jnl_item;
 #endif

 #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
	UBYTE	list_cut_request;	/* Add by O.Kimoto 1998/11/28 */

	if ((SYB_MaintenanceSwitch[MNT_SW_H1] & LIST_PRINT_NO_CUT) == LIST_PRINT_NO_CUT) {
		list_cut_request = 0;
	}
	else {
		list_cut_request = 1;
	}
 #endif

 #if defined(SAKAKI) && defined(JP0)
 	jnl_item = SYS_DocumentPrintItem;
 #endif

	CMN_DisableInterrupt();

	bk_point2 = 0;	/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */

	/*通信管理記録ﾌｧｲﾙのﾃﾞｰﾀｽﾀｰﾄ位置とﾃﾞｰﾀ数を求める*/
	JournalPointCount( SYB_JournalPoint, SYS_JOURNAL_MAX, &bk_point, &bk_count,
	  SYB_JournalFile[SYB_JournalPoint].Number );

	/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信のデータと*/
	/*なる可能性があるため、一番上に印刷されるデータのみﾊﾞｯﾌｧに退避する。*/
	for (i = 0; i < 10; i++) {	/* add for() 1997/10/29 */
		/*ほんまは、こんな代入文は使っていいような悪いような う～ん */
		/*とりあえず、ＳＨとＶ５３は大丈夫みたいやし、これのほうが楽やしこうしとこ */
		
#if (0)
** 		/* ジャーナルが消える不具合修正 By O.Kimoto 1999/03/01 */
** 		BKJournalFile[i] = SYB_JournalFile[bk_point+i];
#else
		if ((bk_point + i) >= SYS_JOURNAL_MAX ) {
			bk_point2 = SYS_JOURNAL_MAX;
		}
		else {
			bk_point2 = 0;
		}
		BKJournalFile[i] = SYB_JournalFile[bk_point+i-bk_point2];

 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
		BKJournalPoint[i] = bk_point+i-bk_point2;
 #endif

#endif

	}
	CMN_EnableInterrupt();

	/*
	 * ジャーナルは、１ページに２５件分記載されます。送信・受信どちらかが２５件ちょうど
	 * の時、タイトルだけ書いてしまうと言う不具合対策の２次障害で、１００件分すべて
	 * プリントされないと言う不具合発生。
	 * もともと、ジャーナルの検索カウンタ（i）とジャーナル検索数（count）を比較して
	 * 次データ有り無しの判断をするのは間違ってます。
	 * ジャーナルは送信・受信混ざってはいってるからです。
	 * これを、送信・受信で印字すべきデータ数をカウントし、その分書くように変更しました。
	 *
	*/

 #if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/16 */
	JournalLineNumber = 1;		/* ２回線追加 1997/09/16 Y.Matsukuma */
	board_cnt	= OPT_CountModems();
	stack_cnt	= 0;

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
	InternalLineNumber = 0;
  #endif
	while (board_cnt >= JournalLineNumber) {
		page	= 1;
		point 	= bk_point;
		i	= 0;
		check = 0;
		check_item = 0;
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
		count = JournalCount(TXTYPE, stack_cnt, bk_point, InternalLineNumber);
  #else
		count = JournalCount(TXTYPE, stack_cnt, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif

		/* ジャーナル印字時、該当通信分がない場合に、タイトルのみ印字しているが、
		** このような場合は印字しないようにしてほしいというフィールドより仕様変更要求があり
		** メモリスイッチにて対応できるようにします。（メモリスイッチＨ：５－０～７、Ｈ：６－０～１）
		** 尚、変更後の仕様は、
		**    - 回線毎にジャーナルプリントのＯＮ／ＯＦＦが出来る（メモリスイッチＨ：５－０～７、Ｈ：６－０）
		**    - 該当通信分（送・受信）がない場合にタイトルのみをプリントするしない（メモリスイッチＨ：６－１）
		**  By O.Kimoto 1999/11/09
		*/
  #if (PRO_LINENUMBER == TWICE_LINE)
		if (CheckJournalPrintEachLine(stack_cnt,InternalLineNumber) == TRUE) {
  #else
		if (CheckJournalPrintEachLine(stack_cnt) == TRUE) {
  #endif

			while(1) {

				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
				if (count == 0) {
					if (CHK_JournalPrintTitle() == 0) {	/* 論理逆 By O.Kimoto 1999/12/20 */
						break;
					}
				}

				if ( (ret =	Print_TrxRcvJournal_Head( 0, page, TXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
					return ( ret );
				}
				if ( board_cnt > 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
					line_cnt = (UBYTE)(PaperSizeLen() - 13);/*印刷可能行数ｾｯﾄ*/
  #else
					line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #endif
				}
				else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
					line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
					line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
				}
				while( 1 ){

  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
					if (list_cut_request == 1){
						if( line_cnt <= 2 ){		/* 改ページ */
							break;
						}
					}
  #else
					if( line_cnt <= 2 ){		/* 改ページ */
						break;
					}
  #endif

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
					/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
					/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
					/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
					/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
					/*退避したﾃﾞｰﾀにて印刷する。*/
					if ( i < 10 ) {
						if (stack_cnt == 0) {	/* 標準ラインのとき */
							/*
							** ちょっとややこしい条件になってしもた
							** ジャーナルの回線＝＝内蔵の送信 ＆＆ 
							** （内蔵の中で標準ラインの場合で標準ライン印字の場合 || （内蔵の中で拡張ラインの場合で拡張ライン印字の場合）
							** のとき印字します
							*/
							if ((BKJournalFile[i].Type == TXTYPE)
							&& (BKJournalFile[i].StackNumber == stack_cnt)
							&& (CheckInternalLinePrintEnable(InternalLineNumber, BKJournalFile[i].Option) == TRUE)) {
								if ((ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
									return ( ret );
								}
								line_cnt	-= 2;
								check++;	/* 1998/02/03 Y.Matsukuma */
							}
						}
						else {	/* オプションラインのとき */
							if (( BKJournalFile[i].Type == TXTYPE) 
							&& (BKJournalFile[i].StackNumber == stack_cnt)) {
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
									return ( ret );
								}
								line_cnt	-= 2;
								check++;	/* 1998/02/03 Y.Matsukuma */
							}
						}
					}
					else {
						if (stack_cnt == 0) {	/* 標準ラインのとき */
#if (0)	/* 1998/03/19 by T.Soneoka 通信管理レポート送受入り交ざる件 */
//						if ((SYB_JournalFile[i].Type == TXTYPE)
//						&&  (SYB_JournalFile[i].StackNumber == stack_cnt)
//						&& (CheckInternalLinePrintEnable(InternalLineNumber, SYB_JournalFile[i].Option) == TRUE)) {
#else
							if ((SYB_JournalFile[point].Type == TXTYPE)
							&&  (SYB_JournalFile[point].StackNumber == stack_cnt)
							&& (CheckInternalLinePrintEnable(InternalLineNumber, SYB_JournalFile[point].Option) == TRUE)) {
#endif
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
									return ( ret );
								}
								line_cnt	-= 2;
								check++;		/* 1998/02/03 Y.Matsukuma */
							}
						}
						else {	/* オプションラインのとき */
							if (( SYB_JournalFile[point].Type == TXTYPE ) 
							&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
									return ( ret );
								}
								line_cnt	-= 2;
								check++;		/* 1998/02/03 Y.Matsukuma */
							}
						}
					}
  #else	/* (PRO_LINENUMBER == TWICE_LINE) */
					/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
					/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
					/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
					/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
					/*退避したﾃﾞｰﾀにて印刷する。*/
					if ( i < 10 ) {
						if (( BKJournalFile[i].Type == TXTYPE ) 
							&& ( BKJournalFile[i].StackNumber == stack_cnt )){
							if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
							  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
								return ( ret );
							}
							line_cnt	-= 2;
							check++;	/* 1998/02/03 Y.Matsukuma */
						}
					}
					else {
						if (( SYB_JournalFile[point].Type == TXTYPE ) 
							&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
							if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
							  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
								return ( ret );
							}
							line_cnt	-= 2;
							check++;		/* 1998/02/03 Y.Matsukuma */
						}
					}
  #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
					point++;
					if ( point >= SYS_JOURNAL_MAX ) {
						point = 0;
					}
					i++;
					if( i >= (BYTE)bk_count ){	/* 保険 */
						check_item = 1;
						break;
					}
					if( check >= count ){	/* 1998/02/03 Y.Matsukuma */
						check_item = 1;
						break;
					}
				}
				/*Print_TrxRcvJournal_Head( 1, page, TXTYPE );1997/11/27 */	/* フッタ印字 */
				if ( (ret =	Print_TrxRcvJournal_Head( 1, page, TXTYPE ) ) != OK ) {	/*フッタ印刷*/
					return ( ret );
				}

				if (check_item == 1) {
					break;
				}

#if 0
**			/* 改ページでヘッダのみ書く不具合の対策 1997/10/30 Old-Y.Matsukuma */
**			check = point;
**			check_item = FALSE;
**			while(count > check) {
**				if (( SYB_JournalFile[check].Type == TXTYPE ) 
**					&& ( SYB_JournalFile[check].StackNumber == stack_cnt )){
**					check_item = TRUE;
**					break;
**				}
**				check++;
**			}
**			if (check_item == FALSE) {
**				break;
**			}
**			/* 対策ＥＮＤ */
#endif

				page++;
			}

			/* 受信管理 */
			page	= 1;
			point = bk_point;
			i	= 0;
			check = 0;		/* 1998/02/03 Y.Matsukuma */
			check_item = 0;
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
			count = JournalCount(RXTYPE, stack_cnt, bk_point, InternalLineNumber);
  #else
			count = JournalCount(RXTYPE, stack_cnt, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif

			while(1) {

				/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/15 */
				if (count == 0) {
					if (CHK_JournalPrintTitle() == 0) {	/* 論理逆 By O.Kimoto 1999/12/20 */
						break;
					}
				}

  #if (1) /* 通信管理レポートが受信のみの場合、印刷可能行数が前回印刷した記録紙で計算されてしまう。By H.Fujimura 2002/08/13 */
				if ( (ret = Print_TrxRcvJournal_Head( 0, page, RXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
					return ( ret );
				}
  #endif
				if ( board_cnt > 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
					line_cnt = (UBYTE)(PaperSizeLen() - 13);/*印刷可能行数ｾｯﾄ*/
  #else
					line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #endif
				}
				else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
					line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
					line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
				}
  #if (0) /* 通信管理レポートが受信のみの場合、印刷可能行数が前回印刷した記録紙で計算されてしまう。By H.Fujimura 2002/08/13 */
//				if ( (ret = Print_TrxRcvJournal_Head( 0, page, RXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
//					return ( ret );
//				}
  #endif
				while( 1 ){
  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
					if (list_cut_request == 1){
						if( line_cnt <= 2 ){		/* 改ページ */
							break;
						}
					}
  #else
					if( line_cnt <= 2 ){		/* 改ページ */
						break;
					}
  #endif
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
					/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
					/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
					/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
					/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
					/*退避したﾃﾞｰﾀにて印刷する。*/
					if ( i < 10 ) {
						if (stack_cnt == 0) {	/* 標準ラインのとき */
							/*
							** ちょっとややこしい条件になってしもた
							** ジャーナルの回線＝＝内蔵の送信 ＆＆ 
							** （内蔵の中で標準ラインの場合で標準ライン印字の場合 || （内蔵の中で拡張ラインの場合で拡張ライン印字の場合）
							** のとき印字します
							*/
							if ((BKJournalFile[i].Type == RXTYPE)
							&& (BKJournalFile[i].StackNumber == stack_cnt)
							&& (CheckInternalLinePrintEnable(InternalLineNumber, BKJournalFile[i].Option) == TRUE)) {
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
									return ( ret );
								}
								line_cnt	-= 2;
								check++;
							}
						}
						else {	/* オプションラインのとき */
							if (( BKJournalFile[i].Type == RXTYPE ) 
								&& ( BKJournalFile[i].StackNumber == stack_cnt )){
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
									return ( ret );
								}
								line_cnt	-= 2;
								check++;
							}
						}
					}
					else {
						if (stack_cnt == 0) {	/* 標準ラインのとき */
#if (0)	/* 1998/03/19 by T.Soneoka 通信管理レポート送受入り交ざる件 */
//						if ((SYB_JournalFile[i].Type == RXTYPE)
//						&&  (SYB_JournalFile[i].StackNumber == stack_cnt)
//						&& (CheckInternalLinePrintEnable(InternalLineNumber, SYB_JournalFile[i].Option) == TRUE)) {
#else
							if ((SYB_JournalFile[point].Type == RXTYPE)
							&&  (SYB_JournalFile[point].StackNumber == stack_cnt)
							&& (CheckInternalLinePrintEnable(InternalLineNumber, SYB_JournalFile[point].Option) == TRUE)) {
#endif
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
									return ( ret );
								}
								line_cnt	-= 2;
								check++;
							}
						}
						else {	/* オプションラインのとき */
							if (( SYB_JournalFile[point].Type == RXTYPE ) 
							&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
								if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
								  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
									return ( ret );
								}
								line_cnt	-= 2;
								check++;
							}
						}
					}
  #else	/* (PRO_LINENUMBER == TWICE_LINE) */
					/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
					/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
					/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
					/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
					/*退避したﾃﾞｰﾀにて印刷する。*/
					if ( i < 10 ) {
						if (( BKJournalFile[i].Type == RXTYPE ) 
							&& ( BKJournalFile[i].StackNumber == stack_cnt )){
							if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
							  (struct SYS_JournalData_t *)BKJournalFile, i )) != OK ) {
								return ( ret );
							}
							line_cnt	-= 2;
							check++;
						}
					}
					else {
						if (( SYB_JournalFile[point].Type == RXTYPE ) 
							&& ( SYB_JournalFile[point].StackNumber == stack_cnt )){
							if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
							  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
								return ( ret );
							}
							line_cnt	-= 2;
							check++;
						}
					}
  #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
					point++;
					if ( point >= SYS_JOURNAL_MAX ) {
						point = 0;
					}
					i++;
					if( i >= (BYTE)bk_count ){	/* 保険 */
						check_item = 1;
						break;
					}
					if( check >= count ){	/* 1998/02/03 Y.Matsukuma */
						check_item = 1;
						break;
					}
				}
				/*Print_TrxRcvJournal_Head( 1, page, RXTYPE );1997/11/27 */	/* フッタ印字 */
				if ( (ret = Print_TrxRcvJournal_Head( 1, page, RXTYPE ) ) != OK ) {	/*フッタ印刷*/
					return ( ret );
				}

				if (check_item == 1) {
					break;
				}

#if 0			
**			/* 改ページでヘッダのみ書く不具合の対策 1997/10/30 Y.Matsukuma */
**			check = point;
**			check_item = FALSE;
**			while(count > check) {
**				if (( SYB_JournalFile[check].Type == RXTYPE ) 
**					&& ( SYB_JournalFile[check].StackNumber == stack_cnt )){
**					check_item = TRUE;
**					break;
**				}
**				check++;
**			}
**			if (check_item == FALSE) {
**				break;
**			}
**			/* 対策ＥＮＤ */
#endif

				page++;
			}
		}	/* ジャーナル仕様変更分 */
		
		
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
		/* 内蔵回線で標準回線を印字し終わったら、次は内蔵回線の拡張回線の印字に移ります */
		if ((stack_cnt == 0)
		&& (InternalLineNumber == 0)
		&& (CHK_UNI_JrnlInternalSeprate())) {	/* 標準／拡張を分けてプリントするとき */
			InternalLineNumber++;
		}
		else {
			InternalLineNumber = 0;
			JournalLineNumber++;
			stack_cnt++;
			/* モデム基盤の間に回転基盤等が入った場合の処理 */
			if (CHK_OptionLineExist( stack_cnt ) != 1) {
				stack_cnt++;
			}
		}
  #else
		JournalLineNumber++;
		stack_cnt++;
		/* モデム基盤の間に回転基盤等が入った場合の処理 */
		if (CHK_OptionLineExist( stack_cnt ) != 1) {
			stack_cnt++;
		}
  #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
	}

 #else	/* ここまで２回線用 */

	page	= 1;
	point = bk_point;
	i	= 0;

  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */	/* 1998/09/21 Add By M.Kuwahara */
	count = JournalCount(TXTYPE, 0, bk_point, InternalLineNumber);
  #else
	count = JournalCount(TXTYPE, 0, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif
/*	while( i < (BYTE)count ){*/	/* 1998/10/06 By M.Kuwahara */
	while (count > 0){

 #if defined(SAKAKI) && defined(JP0)	/* 2002/08/23 By M.Maeda */
		if (!((jnl_item == LST_JOURNAL_LIST) || (jnl_item == LST_JOURNAL_TX_LIST))) {
			break;
		}
 #endif

		if ( (ret =	Print_TrxRcvJournal_Head( 0, page, TXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		if ( page == 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
		}
		else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
		}
		while( 1 ){
  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
			if (list_cut_request == 1){
				if( line_cnt <= 2 ){		/* 改ページ */
					break;
				}
			}
  #else
			if( line_cnt <= 2 ){		/* 改ページ */
				break;
			}
  #endif
			/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
			/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
			/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
			/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
			/*退避したﾃﾞｰﾀにて印刷する。*/
  #if (0)	/* 1998/10/06 By M.Kuwahara */
  //			if ( i == 0 ) {
  //				if ( BKJournalFile[0].Type == TXTYPE ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)BKJournalFile, 0 )) != OK ) {
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  //			else {
  //				if ( SYB_JournalFile[point].Type == TXTYPE ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  #else
			if (i < 10) {
				if ( BKJournalFile[i].Type == TXTYPE ) {
					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
					  (struct SYS_JournalData_t *)BKJournalFile, i)) != OK ) {
						return ( ret );
					}
					line_cnt	-= 2;
					count--;
				}
			}
			else {
				if ( SYB_JournalFile[point].Type == TXTYPE ) {
					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
					  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
						return ( ret );
					}
					line_cnt	-= 2;
					count--;
				}
			}
  #endif	/* #if (0) */
			point++;
			if ( point >= SYS_JOURNAL_MAX ) {
				point = 0;
			}
			i++;
			/* iは配列分のﾃﾞｰﾀ数をｶｳﾝﾄするので、送信分だけのｶｳﾝﾀと比較しても意味が無い 	*/
			/* 									1998/10/06 By M.Kuwahara 				*/
/*			if( i >= (BYTE)count ){*/
			if (count <= 0) {
				break;
			}
		}
		/*Print_TrxRcvJournal_Head( 1, page, TXTYPE );*/	/* フッタ印字 */
		if ( (ret =	Print_TrxRcvJournal_Head( 1, page, TXTYPE ) ) != OK ) {	/*フッタ印刷*/
			return ( ret );
		}
		page++;
	}

	/* 受信管理 */
	page	= 1;
	point = bk_point;
	i	= 0;
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */	/* 1998/09/21 Add By M.Kuwahara */
	count = JournalCount(RXTYPE, 0, bk_point, InternalLineNumber);
  #else
	count = JournalCount(RXTYPE, 0, bk_point);	/* 1998/02/03 New-Matsukuma */
  #endif
/*	while( i < (BYTE)count ){*/
	while (count > 0) {

 #if defined(SAKAKI) && defined(JP0)	/* 2002/08/23 By M.Maeda */
		if (!((jnl_item == LST_JOURNAL_LIST) || (jnl_item == LST_JOURNAL_RX_LIST))) {
			break;
		}
 #endif

  #if (1) /* 通信管理レポートが受信のみの場合、印刷可能行数が前回印刷した記録紙で計算されてしまう。By H.Fujimura 2002/08/13 */
		if ( (ret = Print_TrxRcvJournal_Head( 0, page, RXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
  #endif
		if ( page == 1 ) {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
		}
		else {
  #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
			line_cnt = (UBYTE)(PaperSizeLen() - 12);/*印刷可能行数ｾｯﾄ*/
  #else
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
  #endif
		}
  #if (0) /* 通信管理レポートが受信のみの場合、印刷可能行数が前回印刷した記録紙で計算されてしまう。By H.Fujimura 2002/08/13 */
//		if ( (ret = Print_TrxRcvJournal_Head( 0, page, RXTYPE ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
//			return ( ret );
//		}
  #endif
		while( 1 ){
  #if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ロール紙 *//* Add by O.Kimoto 1998/11/28 */
			if (list_cut_request == 1){
				if( line_cnt <= 2 ){		/* 改ページ */
					break;
				}
			}
  #else
			if( line_cnt <= 2 ){		/* 改ページ */
				break;
			}
  #endif
			/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
			/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
			/*通信とのタイムラグの関係上一番上に印刷されるデータが最終通信の*/
			/*データとなる可能性があるため、一番上に印刷されるﾃﾞｰﾀのみﾊﾞｯﾌｧに*/
			/*退避したﾃﾞｰﾀにて印刷する。*/
  #if (0)	/* 1998/10/06 By M.Kuwahara */
  //			if ( i == 0 ) {
  //				if ( BKJournalFile[0].Type == RXTYPE ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)BKJournalFile, 0 )) != OK ) {
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  //			else {
  //				if ( SYB_JournalFile[point].Type == RXTYPE ) {
  //					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
  //					  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
  //						return ( ret );
  //					}
  //					line_cnt	-= 2;
  //				}
  //			}
  #else
			if (i < 10 ) {
				if (BKJournalFile[i].Type == RXTYPE) {
					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
					  (struct SYS_JournalData_t *)BKJournalFile, i)) != OK ) {
						return ( ret );
					}
					line_cnt	-= 2;
					count--;
				}
			}
			else {
				if ( SYB_JournalFile[point].Type == RXTYPE ) {
					if ( (ret = Print_Journal_List_Specifi(			/*1明細印刷*/
					  (struct SYS_JournalData_t *)SYB_JournalFile, point )) != OK ){
						return ( ret );
					}
					line_cnt	-= 2;
					count--;
				}
			}
  #endif	/* #if (0) */
			point++;
			if ( point >= SYS_JOURNAL_MAX ) {
				point = 0;
			}
			i++;
			/* iは配列分のﾃﾞｰﾀ数をｶｳﾝﾄするので、送信分だけのｶｳﾝﾀと比較しても意味が無い 	*/
			/* 									1998/10/06 By M.Kuwahara 				*/
/*			if( i >= (BYTE)count ){*/
			if (count <= 0) {
				break;
			}
		}
		/*Print_TrxRcvJournal_Head( 1, page, RXTYPE );*/	/* フッタ印字 */
		if ( (ret = Print_TrxRcvJournal_Head( 1, page, RXTYPE ) ) != OK ) {	/*フッタ印刷*/
			return ( ret );
		}
		page++;
	}
 #endif	/* (PRO_MULTI_LINE == ENABLE) */
	return ( OK );
}
#endif /* #if defined(STOCKHM2) Mod by SMuratec C.P for 送受信別プリント */

/*************************************************************************
	module		:[通信管理レポートヘッダ印刷]
	functiom	:[通信管理レポートのヘッダを印刷する]
	common		:[
	]
	condition	:[
		ﾍｯﾀﾞ種類
			0->ﾍﾟｰｼﾞ先頭見出し
			1->ﾍﾟｰｼﾞｴﾝﾄﾞ見出し
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/20]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_TrxRcvJournal_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page,		/*ページ*/
						 UBYTE TxRx )		/* 送信、受信判別フラグ*/
{
	register WORD	ret;					/*実行結果*/

	if ( Category == 0 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if( TxRx == TXTYPE ){			/* 送信の時 */
			/*１改行＋発信元名、番号印刷＋２改行＋見出し＋１改行*/
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common(PWRD_TransmitJournal_K, LST_NOT, 21-1 )) != OK ) {
				return ( ret );
			}
 #else
			if ( (ret = Print_Head1_Common(PWRD_TransmitJournal, LST_XXX_TWI_XXX, 21-1 )) != OK ) {
				return ( ret );
			}
 #endif
		}
		else{					/* 受信の時 */
			/*１改行＋発信元名、番号印刷＋２改行＋見出し＋１改行*/
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common(PWRD_RecieveJournal_K, LST_NOT, 21-1 )) != OK ) {
				return ( ret );
			}
 #else
			if ( (ret = Print_Head1_Common(PWRD_RecieveJournal, LST_XXX_TWI_XXX, 21-1 )) != OK ) {
				return ( ret );
			}
 #endif
		}

 #if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* 日立特許回避(プリント時間を印字しない) By M.Tachibana 1998/04/14 */
		/* 現在時刻印字 */
		if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
			return ( ret );
		}
 #endif

		/* ページ番号印字 */
		if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
			return ( ret );
		}

 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
		/* ライン番号印字 */
		Prn_Att_Str_Clear(List.S.Print,List.S.Attribute );
		AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_LineNumber, LST_NOT );
  #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/27 */
		AttributeSet( &List.S.Print[7-1], &List.S.Attribute[13-1], PWRD_LineName[InternalLineNumber], LST_NOT );
  #else /* defined (KEISATSU) */
		if (JournalLineNumber == 1) {
			if (CHK_UNI_JrnlInternalSeprate()) {	/* 標準／拡張を分けてプリントするとき */
				AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[InternalLineNumber], LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[0], LST_NOT );
				List.S.Print[17-1] = '/';
				AttributeSet( &List.S.Print[18-1], &List.S.Attribute[13-1], PWRD_LineName[1], LST_NOT );
			}
		}
		else {
			AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[2], LST_NOT );
		}
  #endif /* defined (KEISATSU) */

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
 #else
  #if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/02 */
		if (OPT_CountModems() > 1) {	/* Change CheckMultiLine() to OPT_CountModems() By O.Kimoto 1997/06/26 */
			/* ライン番号印字 */
			Prn_Att_Str_Clear(List.S.Print,List.S.Attribute );
			AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_LineNumber, LST_NOT );
			CMN_UnsignedIntToASC( &List.S.Print[13-1], (UWORD)JournalLineNumber, 1, '0' );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
  #endif
 #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
		/* ﾂｳﾊﾞﾝ  ｱｲﾃｻｷﾒｲ	ﾓｰﾄﾞ  ｶｲｼｼﾞｺｸ	ｼﾞｶﾝ  ﾏｲｽｳ	ﾌﾞﾓﾝ  ｹｯｶ	ﾋﾞｺｳ  */
		Print_Journal_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else{
		/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
		Print_Journal_List_Line( 1, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED+1 )) != OK ) {
			return ( ret );
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
}

/*************************************************************************
	module		:[通信管理レポート明細印刷]
	function	:[通信管理レポートの明細部分を印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/12/02]
	author		:[増田次郎]
*************************************************************************/
WORD				Print_Journal_List_Specifi(
						 struct SYS_JournalData_t JournalFile[],/*通信記録データ*/
						 UBYTE Point )			/*通信記録データ番号*/
{
	register WORD	ret;					/*実行結果*/
	UBYTE	i;		/* 西暦４桁対応 bythonda1999/11/16	*/
#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
#endif

	/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
	Print_Journal_List_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*	999	 xxxxxx	 xxxx  Z9/Z9 Z9:99	Z9'99"  ZZ9   XXXX  XXXXXX */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	/*ﾂｳﾊﾞﾝ*/
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/13 */

  #if defined(POPLAR_F)

	if (CHK_UNI_MultiT30Monitor()) {
		/* Ｔ３０シリアル番号用 */
		if (JournalFile == BKJournalFile) {
			if (SYB_T30MonitorDRAM_Status[Point] == 1) {
				CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)BKJournalPoint[Point], 3, ' ' );
			}
			else {
				List.S.Print[1-1] = '-';
				List.S.Print[2-1] = '-';
				List.S.Print[3-1] = '-';
			}
		}
		else {
			if (SYB_T30MonitorDRAM_Status[Point] == 1) {
				CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)Point, 3, ' ' );
			}
			else {
				List.S.Print[1-1] = '-';
				List.S.Print[2-1] = '-';
				List.S.Print[3-1] = '-';
			}
		}
	}
	else {
		CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)JournalFile[Point].Number, 3, '0' );
	}

  #else

	if (CHK_UNI_MultiT30Monitor()) {
		if (JournalFile == BKJournalFile) {
			if (((SYS_T30Monitor + BKJournalPoint[Point])->JournalType != SYS_T30_EMPTY)
			 && ((SYS_T30Monitor + BKJournalPoint[Point])->WritePointer != 0)) {
				CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)BKJournalPoint[Point], 3, '0' );
			}
			else {
				List.S.Print[1-1] = '-';
				List.S.Print[2-1] = '-';
				List.S.Print[3-1] = '-';
			}
		}
		else {
			if (((SYS_T30Monitor + Point)->JournalType != SYS_T30_EMPTY)
			 && ((SYS_T30Monitor + Point)->WritePointer != 0)) {
				CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)Point, 3, '0' );
			}
			else {
				List.S.Print[1-1] = '-';
				List.S.Print[2-1] = '-';
				List.S.Print[3-1] = '-';
			}
		}
	}
	else {
		CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)JournalFile[Point].Number, 3, '0' );
	}

  #endif
 #else
	CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)JournalFile[Point].Number, 3, '0' );
 #endif

	if ( JournalYearPrint ) {	/* 西暦４桁対応 bythonda1999/11/16	*/
		i = 5;
	}
	else {
		i = 0;
	}
	/*ｱｲﾃｻｷﾒｲ*/
#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//	if (JournalFile[Point].RemoteID_TTI[0] == '!'){
//		length = CMN_StringLength(SYB_MercuryDialBuffer);	/* マキュリー登録桁 */
//
//		List.S.Print[4] = '[';
//		if (length > 18 - i){
//			CMN_StringCopyNumUntilNull( &List.S.Print[5], SYB_MercuryDialBuffer, 19 - i);
//		}
//		else{
//			List.S.Print[5 + length] = ']';
//
//			CMN_StringCopyNumUntilNull(&List.S.Print[5], SYB_MercuryDialBuffer, length);
//			CMN_StringCopyNumUntilNull(&List.S.Print[6 + length], &JournalFile[Point].RemoteID_TTI[1], (18 - i - length));
//		}
//	}
//	else{
//		CMN_StringCopyNumOrNULL( &List.S.Print[5-1], &JournalFile[Point].RemoteID_TTI[0], 20 - i );
//	}
#else
/*	CMN_StringCopy( &List.S.Print[5-1], JournalFile[Point].RemoteID_TTI );*/	/* 西暦４桁対応 bythonda1999/11/16	*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
	if (JournalFile[Point].KeisatsuID[0] != NULL) {
		CMN_StringCopyNumOrNULL( &List.S.Print[5-1], &JournalFile[Point].KeisatsuID[0], 4 );		
		CMN_StringCopyNumOrNULL( &List.S.Print[9-1], &JournalFile[Point].RemoteID_TTI[0], 20 - i - 4 );		
	}
	else {
		CMN_StringCopyNumOrNULL( &List.S.Print[5-1], &JournalFile[Point].RemoteID_TTI[0], 20 - i );
	}
#else /* !defined (KEISATSU) */
	CMN_StringCopyNumOrNULL( &List.S.Print[5-1], &JournalFile[Point].RemoteID_TTI[0], 20 - i );
#endif /* defined (KEISATSU) */
#endif

	/*ﾓｰﾄﾞ*/
/*	CommunicationModeName( JournalFile[Point].Mode, &List.S.Print[26-1], &List.S.Attribute[26-1] );*/	/* 西暦４桁対応 bythonda1999/11/16	*/
	CommunicationModeName( JournalFile[Point].Mode, &List.S.Print[26 - i - 1], &List.S.Attribute[26 - i - 1] );

	/*ｶｲｼ ﾆﾁｼﾞ*/
 #if (PRO_OKI == ENABLE)	/* 沖ヨーロッパ仕様では、月／日を日／月に変更します by K.Watanabe 1998/10/13 */
	CriterionMinuteToDayTimeAsc( JournalFile[Point].StartTime/60, LST_DDMMHHMM, List.S.Work );
 #else
	if ( JournalYearPrint ) {	/* 西暦４桁対応 bythonda1999/11/16	*/
		CriterionMinuteToDayTimeAsc( JournalFile[Point].StartTime/60, LST_YYYYMMDDHHMM2, List.S.Work );
	}
	else {
		CriterionMinuteToDayTimeAsc( JournalFile[Point].StartTime/60, LST_MMDDHHMM, List.S.Work );
	}
 #endif
/*	CMN_StringCopy( &List.S.Print[36-1], List.S.Work );*/
	CMN_StringCopy( &List.S.Print[36 - i - 1], List.S.Work );

	/*ｼﾞｶﾝ*/
	SecondToMinuteSecondAsc( JournalFile[Point].TotalTime, List.S.Work , ' ' );
	CMN_StringCopy( &List.S.Print[49-1], List.S.Work );

	/*ﾏｲｽｳ*/
	CMN_UnsignedIntToASC( &List.S.Print[56-1], (UWORD)JournalFile[Point].Page, 3, ' ' );

 #if ( PRO_DEPARTMENT == ENABLE )	/* 部門有り */
	/*-----------------------------------------------------*/
	/*部門*/
	/* 部門管理ONで、プロテクトONの時、部門コードをマスクするためのif else文追加 */
	/* ちょうちょう、アンズはＰＡＴなんやから、単純にもってきたらあかんで～ 考えてもってきいや */
	/* 平尾は無罪や～！ もってきたやつが悪い！ */
	if ( (CHK_DepartmentON() != OFF) && (CHK_SectionCheckProtect() != OFF) ) {
		if (JournalFile[Point].DepartmentCode != 0xffff) { /* if文ぬけてたで 1997/11/28 */
			List.S.Print[61-1] = '*';
			List.S.Print[62-1] = '*';
			List.S.Print[63-1] = '*';
			List.S.Print[64-1] = '*';
		}
	}
	else {
		if (JournalFile[Point].DepartmentCode != 0xffff) { /* 初期値が0xffffに変更のため */
			/*CMN_UnsignedIntToASC( &List.S.Print[61-1], (UWORD)SYB_JournalFile[Point].DepartmentCode, 4, '0' ); 2001/05/16 Y.Murata */
			CMN_UnsignedIntToASC( &List.S.Print[61-1], (UWORD)JournalFile[Point].DepartmentCode, 4, '0' );
		}
	}
	/*ECM */
	if ( (JournalFile[Point].Result & LST_ECM) != 0 ) {
		List.S.Print[67-1] = '*';
	
	}
  #if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)/* ２回線：追加 1997/09/04 Y.Matsukuma */ /* V34 H.Yoshikawa 1998/11/06 */
	if ( (JournalFile[Point].Result & V34_MODE_SET) != 0 ) {	/* Ｖ３４交信時 */
		List.S.Print[67-1] = '#';
	}
#if (0)	/* テスト用に使用します 1998/11/16 H.Yoshikawa */
//  #if (PRO_NUMBER_DISPLAY == ENABLE) /* 1998/11/14 H.Yoshikawa */
//	if ( (JournalFile[Point].Result & ND_NOT_RECEIVE) != 0 ) {
//		if ( (JournalFile[Point].Result & V34_MODE_SET) != 0 ) {	/* Ｖ３４交信時 */
//			List.S.Print[67-1] = 'X';
//		}
//		else {
//			List.S.Print[67-1] = 'x';
//		}
//	}
//  #endif
#endif
  #endif
	/*ｹｯｶ*/
	if ( JournalFile[Point].Type == TXTYPE ) {
		CommunicationResultName( (JournalFile[Point].Result),
		  LST_NAME_SHORT, LST_JOURNAL_TX, &List.S.Print[68-1], &List.S.Attribute[68-1] );
	}
	else {
		CommunicationResultName( (JournalFile[Point].Result), LST_NAME_SHORT, 
		  LST_JOURNAL_RX, &List.S.Print[68-1], &List.S.Attribute[68-1] );
	}

	/*------------------------------------------------------*/
	/*ﾋﾞｺｳ*/
	CommunicationKindName( JournalFile[Point].Kind, LST_NAME_1, &List.S.Print[74-1], &List.S.Attribute[74-1] );
 #else
	/*-----------------------------------------------------*/
	/*ECM */
	if ( (JournalFile[Point].Result & LST_ECM) != 0 ) {
		List.S.Print[61-1] = '*';
	}

 /* DVT: Added by SMuratec K.W.Q 2004/09/17 */
 #if defined(STOCKHM2)
  #if (PRO_TX_SPEED == V34)
	if ( (JournalFile[Point].Result & V34_MODE_SET) != 0 ) {	/* Ｖ３４交信時 */
		List.S.Print[61-1] = '#'; /* 67→61 DVT修正 by SMuratec L.Z.W 2004/09/21 */
	}
  #endif
 #endif 
	
	/*ｹｯｶ*/
	if ( JournalFile[Point].Type == TXTYPE ) {
		CommunicationResultName( (JournalFile[Point].Result),
		  LST_NAME_SHORT, LST_JOURNAL_TX, &List.S.Print[62-1], &List.S.Attribute[62-1] );
	}
	else {
		CommunicationResultName( (JournalFile[Point].Result),
		  LST_NAME_SHORT, LST_JOURNAL_RX, &List.S.Print[62-1], &List.S.Attribute[62-1] );
	}
	/*------------------------------------------------------*/
	/*ﾋﾞｺｳ*/
	CommunicationKindName( JournalFile[Point].Kind, LST_NAME_1, &List.S.Print[70-1], &List.S.Attribute[70-1] );
 #endif	/* (PRO_DEPARTMENT == ENABLE) */
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ジャーナル開始位置、データ数取得]
	function	:[ジャーナルの開始位置、データ数を取得する]
	common		:[]
	condition	:[]
	commment	:[通信管理記録ファイルのデータスタート位置とデータ数を求める]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/12/02]
	author		:[増田次郎]
*************************************************************************/
void				JournalPointCount(
						 UBYTE JournalPoint,/*通信記録ファイル書き込み位置*/
						 UBYTE JournalMax,	/*通信記録データ最大数*/
						 UBYTE *Point,		/*開始位置*/
						 UBYTE *Count,		/*データ数*/
						 UWORD Number )		/*通信記録ファイル書き込み位置の通番*/
{
	if ( Number == 0xffff ) {	/* -1 -> 0xffff By M.Tachibana 1997/05/10 */
		/*ﾘﾝｸﾞﾃﾞｰﾀがまだ一周していない*/
		*Point = 0;
		*Count = JournalPoint;
	}
	else {
		/*ﾘﾝｸﾞﾃﾞｰﾀがすでに一周している*/
		*Point = JournalPoint;							/*ﾃﾞｰﾀｽﾀｰﾄ位置*/
		*Count = JournalMax;
	}
}
#endif	/* (PRO_PAT_JOURNAL == DISABLE) */

/*************************************************************************
	module		:[通信管理の横区切り罫線作成]
	function	:[通信管理の横区切り罫線を作成する。]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/12/02]
	author		:[増田次郎]
*************************************************************************/
void				Print_Journal_List_Line(
						 UBYTE Category,			/*罫線種類*/
						 register UBYTE *AscString,	/*印刷文字列*/
						 register UBYTE *AttString )/*修飾文字列*/
{
	UBYTE	i;		/* 西暦４桁対応 bythonda1999/11/16	*/

	Prn_Att_Str_Clear( AscString, AttString );

	switch ( Category ) {
		case 0:
			/* No.	ｱｲﾃｻｷﾒｲ	 ﾓｰﾄﾞ  ｶｲｼｼﾞｺｸ	ｼﾞｶﾝ  ﾏｲｽｳ	ｹｯｶ	 ﾋﾞｺｳ */
			AttributeSet( &AscString[1-1], &AttString[1-1], PWRD_No, LST_NOT );
			AttributeSet( &AscString[5-1], &AttString[5-1], PWRD_Location, LST_NOT );

			if ( JournalYearPrint ) {	/* 西暦４桁対応 bythonda1999/11/16	*/
				i = 5;
			}
			else {
				i = 0;
			}
#if (PRO_COMMON_SAKAKI2 == ENABLE) /* 画質ﾓｰﾄﾞ By M.Maeda 2002/10/15 */
			AttributeSet( &AscString[25 - i - 1], &AttString[25 - i - 1], PWRD_Mode, LST_NOT );
#else
			AttributeSet( &AscString[24 - i - 1], &AttString[24 - i - 1], PWRD_Mode, LST_NOT );
#endif
			AttributeSet( &AscString[36 - i - 1], &AttString[36 - i - 1], PWRD_Start, LST_NOT );

			AttributeSet( &AscString[49-1], &AttString[49-1], PWRD_Time, LST_NOT );
			AttributeSet( &AscString[56-1], &AttString[56-1], PWRD_Page, LST_NOT );
#if ( PRO_DEPARTMENT == ENABLE )	/* 部門有り */
			AttributeSet( &AscString[61-1], &AttString[61-1], PWRD_Code, LST_NOT );
			AttributeSet( &AscString[67-1], &AttString[67-1], PWRD_Result, LST_NOT );
			AttributeSet( &AscString[74-1], &AttString[74-1], PWRD_Note, LST_NOT );
#else
			AttributeSet( &AscString[61-1], &AttString[61-1], PWRD_Result, LST_NOT );
			AttributeSet( &AscString[69-1], &AttString[69-1], PWRD_Note, LST_NOT );
#endif
			break;
		case 1:
			/*・・・・・・・・・・・・・・・・・*/
			CMN_MemorySet( &AscString[1-1], 80, LST_KLINE_ );
			break;
	}
}

#if ( PRO_PAT_JOURNAL == ENABLE )
/*************************************************************************
	module		:[ジャーナルヘッダ]
	function	:[ジャーナルのヘッダを書く]
	common		:[]
	condition	:[]
	commment	:[PRN_JournalPrintTaskから呼ばれる]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/09/29]
	author		:[豊田浩子]
*************************************************************************/
WORD		Print_Journal_Head( UBYTE Page, UBYTE Type)
{
	WORD	ret;									/**	実行結果*/

	/*２行印字（改行）*/
	if ((ret = CharacterPrint(LST_LINE_FEED+2)) != OK) {
		return ( ret );
	}

	/*＊＊	通信管理レポート  ＊＊*/
	if ( Type == LST_JRNL_TX ) {
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_TransmitJournal_K, LST_NOT );
 #else
		AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_TransmitJournal, LST_XXX_TWI_XXX );
 #endif
		if ((ret = CharacterPrint(LST_PRINT)) != OK) {
			return ( ret );
		}
	}
	else {
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_RecieveJournal_K, LST_NOT );
 #else
		AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_RecieveJournal, LST_XXX_TWI_XXX );
 #endif
		if ((ret = CharacterPrint(LST_PRINT)) != OK) {
			return ( ret );
		}
	}

 #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/26 */
	if (OPT_CountModems() > 1) {	/* Change CheckMultiLine() to OPT_CountModems() By O.Kimoto 1997/06/26 */
		/*1行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED+1 )) != OK ) {
			return ( ret );
		}

		/*ﾍﾟｰｼﾞ記載*/
		if ( (ret = LocateX_Page_Print(3-1,Page)) != OK ) {
			return ( ret );
		}

		/* ライン番号印字 */
		Prn_Att_Str_Clear(List.S.Print,List.S.Attribute );
		AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_LineNumber, LST_NOT );
		CMN_UnsignedIntToASC( &List.S.Print[13-1], (UWORD)JournalLineNumber, 1, '0' );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*２行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
			return ( ret );
		}

		/*ﾍﾟｰｼﾞ記載*/
		if ( (ret = LocateX_Page_Print(3-1, Page)) != OK ) {
			return ( ret );
		}
	}
 #else
	/*２行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
		return ( ret );
	}

	/*ﾍﾟｰｼﾞ記載*/
	if ( (ret = LocateX_Page_Print(3-1, Page)) != OK ) {
		return ( ret );
	}
 #endif	/* (PRO_MULTI_LINE == ENABLE) */
	/* ﾂｳﾊﾞﾝ  ｱｲﾃｻｷﾒｲ	ﾓｰﾄﾞ  ｶｲｼｼﾞｺｸ	ｼﾞｶﾝ  ﾏｲｽｳ	ﾌﾞﾓﾝ  ｹｯｶ	ﾋﾞｺｳ  */
	Print_Journal_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/*・・・・・・・・・・・・・・・・・・・・・・・・・・・・・*/
	Print_Journal_List_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
#endif	/* (PRO_PAT_JOURNAL == ENABLE) */

/*************************************************************************
	module		:[ページ印刷]
	functiom	:[ページを印刷する。]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[lst_mltp.cから移動した]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Mar.08,1996]
	author		:[平尾英典]
*************************************************************************/
WORD				LocateX_Page_Print(
						 UBYTE LocateX,		/*印刷桁位置-Page*/
						 UBYTE Page )		/*ページ*/
{
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySetNULL( List.S.Work, 80, ' ' );
	List.S.Print[LocateX-2] = 'P';
	List.S.Print[LocateX-1] = '.';
	CMN_UnsignedIntToASC( List.S.Work, (UWORD)Page, 0, 0 );
	CMN_StringCopy( &List.S.Print[LocateX], List.S.Work );
	return ( CharacterPrint( LST_PRINT ) );
}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
/*************************************************************************
	module		:[ジャーナルの書くべき数をカウントする]
	functiom	:[]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[lst_mltp.cから移動した]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/03]
	author		:[松隈]
*************************************************************************/
UBYTE JournalCount(UBYTE type, UBYTE stack_num, UBYTE bk_point, UBYTE internal_cnt)
{
	UBYTE	i;
	UBYTE	count;
	UBYTE	point;

	point = bk_point;

	count = 0;
	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		if (i < 10) {
			if (BKJournalFile[i].Number != 0xFFFF) {
				if ((BKJournalFile[i].Type == type)
				&& (BKJournalFile[i].StackNumber == stack_num)
				&& (CheckInternalLinePrintEnable(internal_cnt, BKJournalFile[i].Option) == TRUE)) {
					count++;
				}
			}
		}
		else {
 #if (0) /* ジャーナルファイルが正確にでない不具合修正 1998/04/16 by T.Soneoka */
 **			if (SYB_JournalFile[point].Number != 0xFFFF) {
 **				if ((SYB_JournalFile[point].Type == type)
 **				&& (SYB_JournalFile[i].StackNumber == stack_num)
 **				&& (CheckInternalLinePrintEnable(internal_cnt, SYB_JournalFile[i].Option) == TRUE)) {
 #else
			if (SYB_JournalFile[point].Number != 0xFFFF) {
				if ((SYB_JournalFile[point].Type == type)
				&& (SYB_JournalFile[point].StackNumber == stack_num)
				&& (CheckInternalLinePrintEnable(internal_cnt, SYB_JournalFile[point].Option) == TRUE)) {
 #endif
					count++;
				}
			}
		}
		point++;
		if (point >= SYS_JOURNAL_MAX) {
			point = 0;
		}
	}
	return (count);
}

#else	/* (PRO_LINENUMBER == TWICE_LINE) */
/*************************************************************************
	module		:[ジャーナルの書くべき数をカウントする]
	functiom	:[]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[lst_mltp.cから移動した]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/03]
	author		:[松隈]
*************************************************************************/
UBYTE JournalCount(UBYTE type, UBYTE stack_num, UBYTE bk_point)
{
	UBYTE	i;
	UBYTE	count;
	UBYTE	point;

	point = bk_point;

	count = 0;
	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		if (i < 10) {
			if (BKJournalFile[i].Number != 0xFFFF) {
				if (BKJournalFile[i].Type == type) {
					if (BKJournalFile[i].StackNumber == stack_num) {
						count++;
					}
				}
			}
		}
		else {
			if (SYB_JournalFile[point].Number != 0xFFFF) {
				if (SYB_JournalFile[point].Type == type) {
					if (SYB_JournalFile[point].StackNumber == stack_num) {
						count++;
					}
				}
			}
		}
		point++;
		if (point >= SYS_JOURNAL_MAX) {
			point = 0;
		}
	}
	return (count);
}
#endif	/* (PRO_LINENUMBER == TWICE_LINE) */

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
/*************************************************************************
	module		:[内蔵回線の標準／拡張回線ジャーナル印字チェック]
	function	:[
		引数で渡された回線に対する、オプションの標準／拡張かをチェックし、
		ジャーナルに載せるかどうか判断します
	]
	common		:[
	]
	condition	:[]
	commment	:[
	]
	return		:[
		TRUE: 印字する
		FALSE: 印字
	印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/02/04]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CheckInternalLinePrintEnable(UBYTE internal_cnt, UBYTE Option)
{
	if (!(CHK_UNI_JrnlInternalSeprate())) {	/* 標準／拡張を分けてプリントしないとき */
		return(TRUE);
	}
	if ((internal_cnt == 0) && (!(Option & SYS_EXT_LINE))) {
		return(TRUE);
	}
	if ((internal_cnt == 1) && (Option & SYS_EXT_LINE)) {
		return(TRUE);
	}
	return(FALSE);
}
#endif	/* (PRO_LINENUMBER == TWICE_LINE) */

#if (PRO_MULTI_LINE == ENABLE)	/* Add By Y.Matsukuma 1997/09/16 */
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
/*************************************************************************
	module		:[該当回線のタイトルだけページを印字するかどうかの判断]
	functiom	:[]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/11/09]
	author		:[木元]
*************************************************************************/
UBYTE CheckJournalPrintEachLine(UBYTE stack_num, UBYTE internal_cnt)
{
	UBYTE LineAttribute;

	LineAttribute = TRUE;

	/* 該当回線の印字設定をチェック */
	switch(stack_num) {
	case 0:
		if (internal_cnt == 0) {
			LineAttribute = CHK_JournalNoPrintLine0();
		}
		else {
			LineAttribute = CHK_JournalNoPrintLineEXT();
		}
		break;
	case 1:
		LineAttribute = CHK_JournalNoPrintLine1();
		break;
	case 2:
		LineAttribute = CHK_JournalNoPrintLine2();
		break;
	case 3:
		LineAttribute = CHK_JournalNoPrintLine3();
		break;
	case 4:
		LineAttribute = CHK_JournalNoPrintLine4();
		break;
	case 5:
		LineAttribute = CHK_JournalNoPrintLine5();
		break;
	case 6:
		LineAttribute = CHK_JournalNoPrintLine6();
		break;
	case 7:
		LineAttribute = CHK_JournalNoPrintLine7();
		break;
	default:
		/* ここへ来る事はないはずですが、万が一って事を考えて、内蔵回線にしときます */
		LineAttribute = CHK_JournalNoPrintLine0();
		break;
	}

	if (LineAttribute == 0) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
}

 #else	/* (PRO_LINENUMBER == TWICE_LINE) */
/*************************************************************************
	module		:[該当回線のタイトルだけページを印字するかどうかの判断]
	functiom	:[]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/11/09]
	author		:[木元]
*************************************************************************/
UBYTE CheckJournalPrintEachLine(UBYTE stack_num)
{
	UBYTE LineAttribute;

	LineAttribute = TRUE;

	/* 該当回線の印字設定をチェック */
	switch(stack_num) {
	case 0:
		LineAttribute = CHK_JournalNoPrintLine0();
		break;
	case 1:
		LineAttribute = CHK_JournalNoPrintLine1();
		break;
	case 2:
		LineAttribute = CHK_JournalNoPrintLine2();
		break;
	case 3:
		LineAttribute = CHK_JournalNoPrintLine3();
		break;
	case 4:
		LineAttribute = CHK_JournalNoPrintLine4();
		break;
	case 5:
		LineAttribute = CHK_JournalNoPrintLine5();
		break;
	case 6:
		LineAttribute = CHK_JournalNoPrintLine6();
		break;
	case 7:
		LineAttribute = CHK_JournalNoPrintLine7();
		break;
	default:
		/* ここへ来る事はないはずですが、万が一って事を考えて、内蔵回線にしときます */
		LineAttribute = CHK_JournalNoPrintLine0();
		break;
	}

	if (LineAttribute == 0) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
}
 #endif	/* (PRO_LINENUMBER == TWICE_LINE) */
#endif	/* (PRO_LINENUMBER == TWICE_LINE) */
