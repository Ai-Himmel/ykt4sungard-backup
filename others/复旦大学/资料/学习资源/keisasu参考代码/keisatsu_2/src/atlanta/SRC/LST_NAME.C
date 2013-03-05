/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_NAME.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 名称操作
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysdoc.h"	/*1996/06/13 Eguchi */

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_tbl.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_V\rom_tbl.h"		/*任意短縮番号で使用*/

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_def.h"	/* Oct.2,1995 By S.K */
#include	"\src\atlanta\opr\ank\define\opr_pro.h"	/*P-Onetouch,BCD変換で使用*/
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"	/* Oct.2,1995 By S.K */
#include	"\src\atlanta\opr\kanji\define\opr_pro.h"	/*P-Onetouch,BCD変換で使用*/
#include	"\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

#if defined(POPLAR_F) || defined(ANZU_L) || defined(POPLAR_L) || defined(POPLAR_N)
#include	"\src\atlanta\ext_V\mem_data.h"
#endif

/*************************************************************************
	module		:[通信ﾓｰﾄﾞ番号、通信ﾓｰﾄﾞ名称文字列変換。]
	function	:[
		番号で示される通信ﾓｰﾄﾞを、対応する通信ﾓｰﾄﾞ名称の文字列に変換する。
	]
	common		:[]
	condition	:[]
	commment	:[
		番号で示される通信ﾓｰﾄﾞに対応する通信ﾓｰﾄﾞ名称を、通信ﾓｰﾄﾞ名に、
		その修飾を通信ﾓｰﾄﾞ修飾にｾｯﾄする。

		near call を far call に変更	Line 55
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void CommunicationModeName(UWORD ComMode,					/* 通信モード */
						   register UBYTE *ComName,			/* 通信モード名 */
						   register UBYTE *ComAttribute)	/* 通信モード修飾 */
{
	switch (ComMode) {
	case SYS_NORMAL:
		AttributeSet(ComName, ComAttribute, PWRD_Normal, LST_NOT);
		break;
	case SYS_FINE:
		AttributeSet(ComName, ComAttribute, PWRD_Fine, LST_NOT);
		break;
	case SYS_SFINE:
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
		AttributeSet(ComName, ComAttribute, PWRD_SFine, LST_NOT);
		break;
#endif
	case SYS_HFINE:
	case SYS_EFINE:					/* add By T.Yamaguchi 96/06/26 */
	case SYS_E_HFINE:				/* 1997/11/27 */
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
		AttributeSet(ComName, ComAttribute, PWRD_HFine, LST_NOT); 	
#else
		AttributeSet(ComName, ComAttribute, PWRD_SFine, LST_NOT);
#endif
		break;
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		AttributeSet(ComName, ComAttribute, PWRD_Gray, LST_NOT);
		break;
#if (PRO_PITNEYBOWES == ENABLE) 	/* [ＰＢ用解像度表示対応] By S.Fukui Aug.25,1998  */
	case SYS_HGRAY:	
		AttributeSet(ComName, ComAttribute, PWRD_HGray, LST_NOT); 
		break;
#endif
	}
}

/*************************************************************************
	module		:[通信結果番号、通信結果名称文字列変換。]
	function	:[
		番号で示される通信結果を、対応する通信結果名称の文字列に変換する。
	]
	common		:[]
	condition	:[
		名称種類　LST_NAME_SHORT = 略称
				  LST_NAME_LONG	 = ﾌﾙ名称
		特殊機能  LST_RESULT_TX_CONF = 送信証専用形式
				  LST_RESULT_COMMON	 = 普通形式
				  LST_JOURNAL_TX	 = 送信ジャーナル形式
				  LST_JOURNAL_RX	 = 受信ジャーナル形式
	]
	commment	:[
		番号で示される通信結果に対応する通信結果名称を、通信結果名に、
		その修飾を通信結果修飾にｾｯﾄする。名称種類で、略称かﾌﾙ名称が
		選択できる。名称種類が略称の時のみ、特殊機能で送信証専用形式か普通形式
		かを選択できる。（送信証専用形式と普通形式では”ＯＫ”の位置が
		変化する。）

		near call を far call に変更	Line 110
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void CommunicationResultName(UWORD Result,					/* 通信結果 */
							 UBYTE NameCategory,			/* 名称種類 */
							 UBYTE Special,					/* 特殊機能 */
							 register UBYTE *ResultName,	/* 通信ﾓｰﾄﾞ名 */
							 register UBYTE *ResultAttri)	/* 通信結果修飾 */
{
	UBYTE	i;				/*loop & work*/
	UBYTE	j;				/*loop*/
	UBYTE	cmp_flg;		/*ｺﾝﾍﾟｱｰﾌﾗｸﾞ*/
	UBYTE	wk[6];			/*結果ｺｰﾄﾞ*/
	UBYTE	wk_cmp[7];		/*比較ｺｰﾄﾞ*/
#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/26 */
	UBYTE	wd;				/* ワーディングカウンタ */
#endif

	CMN_MemorySet( wk, 5, ' ' );
	wk[1] = '.';
	wk[3] = '.';
	wk[2] = (UBYTE)( ((Result & 0x00f0) >> 4) + 0x30 );
	if ( (Result & 0x000f) <= 9 ) {
		wk[4] = (UBYTE)( ((Result & 0x000f)) + 0x30 );
		wk[5] = NULL;
	}
	else {
		wk[4] = '1';
		wk[5] = (UBYTE)( ((Result & 0x000f)) + 0x30 - 10);
		wk[6] = NULL;
	}
	switch ( Result & 0x0C00 ) {
		case NO_ERROR:
			switch ( Special ) {
				case LST_JOURNAL_TX:
				case LST_JOURNAL_RX:
				case LST_RESULT_COMMON:
					wk[0] = ' ';
					CMN_StringCopyNULL( &wk[1] , PWRD_Ok);
					break;
				case LST_RESULT_TX_CONF:
					CMN_StringCopyNULL( &wk[0] , PWRD_Ok);
					break;
/*------------------
				case LST_JOURNAL_TX:
					wk[0] = 'T';
					wk[1] = '.';
					CMN_StringCopyNULL(	 &wk[2], PWRD_Ok );
					break;
				case LST_JOURNAL_RX:
					wk[0] = 'R';
					wk[1] = '.';
					CMN_StringCopyNULL(	 &wk[2], PWRD_Ok );
					break;
------------------*/
			}
			break;
		case TRANSMITERROR:
			wk[0] = 'T';
			break;
		case RECEIVEERROR:
			wk[0] = 'R';
			break;
		case DIALERROR:
			wk[0] = 'D';
			break;
	}
	if ( NameCategory == LST_NAME_SHORT ) {
		CMN_StringCopyNum( ResultName,	wk, CMN_StringLength(wk));
	}
	else {
		for ( i = 0;;i++ ) {
			CMN_StringCopyNumOrNULL( &wk_cmp[0], &PWRD_ResultCode[i][0], 6 ); /*1996/03/12 Eguchi */
			if ( wk_cmp[0] == NULL ) {
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED	== V34)	/* Add By O.Kimoto 1997/06/26 *//* 1998/10/27 By M.Kuwahara */
				/* R4.6のエラーメッセージをだすため、ワーディングのテーブルに追加しようとしたが */
				/* ドイツの空きがなかったため,こうした                                          */
				AttributeSet( ResultName, ResultAttri, &PWRD_ResultName[0][0], LST_NOT );
#endif
				break;
			}
			cmp_flg = ON;
			for ( j = 0; j < (UBYTE)CMN_StringLength(&wk_cmp[0]) ; j++ ) {
				if ( wk_cmp[j] != wk[j] ) {
					cmp_flg = OFF;
					break;
				}
			}
			if ( cmp_flg == ON ) {
				CMN_StringCopyNum( &wk_cmp[0], &PWRD_ResultChain[i], 1 );
				j = (UBYTE)(wk_cmp[0]-'A');
				AttributeSet( ResultName, ResultAttri, &PWRD_ResultName[j][0], LST_NOT );
#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/26 */
				if ((wk[0] == 'D') && 
					(wk[2] == '0') && 
					(wk[4] == '1') && 
					(wk[5] <= '3')) {
					wd = 0;	/* wk[5]が０の時カウンタも０ */
					if (wk[5] == '1') {
						wd = 1;
					}
					if (wk[5] == '2') {
						wd = 2;
					}
					if (wk[5] == '3') {
						wd = 3;
					}
					/* 下のパス、コメントになってたのをもどしました 1997/12/09 Y.Matsukuma */
					AttributeSet( ResultName, ResultAttri, &PWRD_AddErrorMessage[wd][0] , LST_NOT );
				}
#endif

				break;
			}
		}
	}
}

/*************************************************************************
	module		:[通信種類番号、通信種類文字列変換。]
	function	:[
		番号で示される通信種類を、対応する通信種類名称の文字列に変換する。
	]
	common		:[
	]
	condition	:[
		名称種類　LST_NAME_1 = 名称１（備考）
				  LST_NAME_2 = 名称２（応用機能）
	]
	commment	:[
		番号で示される通信種類に対応する通信種類名称を、通信種類名に、
		その修飾を通信種類修飾にｾｯﾄする。名称種類で、名称１か名称２が
		選択できる。

		near call を far call に変更	Line 227
		95/05/20	By j.masuda
			ＦＩＰの種別を追加。
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void CommunicationKindName(UWORD ComKind,				/* 通信種類 */
						   UBYTE NameCategory,			/* 名称種類 */
						   register UBYTE *KindName,	/* 通信種類名 */
						   register UBYTE *KindAttri)	/* 通信種類修飾 */
{
	if (NameCategory == LST_NAME_2) {
		if (ComKind == SYS_SECURE_RX	|| ComKind == SYS_RELAY_RX
		 || ComKind == SYS_MANUAL_TX	|| ComKind == SYS_MANUAL_RX
#if (PRO_F_CODE == ENABLE)
		 || ComKind == SYS_SELECT_POLLING_TX || ComKind == SYS_SUBADDRESS_SECURE_RX
 #if (PRO_FCODE_KIND_DISPLAY == ENABLE)	/* 1998/09/28 By M.Kuwahara */
 #if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/25 Add By M.Kuwahara */
		 || ComKind == SYS_MEMORY_RELAY_BOX_RX
 #endif
		 || ComKind == SYS_SUBADDRESS_BULLETIN
 #endif
#endif
#if (PRO_CIPHER == ENABLE)
		 || ComKind == SYS_CIPHER_RX
#endif
#if (PRO_FIP == ENABLE)
		 || ComKind == SYS_FIP_TRANSMIT || ComKind == SYS_FIP_RECEIVE
		 || ComKind == SYS_FIP_POLLING	|| ComKind == SYS_FIP_SECURE
#endif	/* (PRO_FIP == ENABLE) */
		 || ComKind == SYS_POLLING_TX	|| ComKind == SYS_DB_POLLING_TX) {
			return;
		}
	}

	switch (ComKind) {
	case SYS_SCANNER_SECURE_TX:			/* ｽｷｬﾅ親展送信			*/
	case SYS_MEMORY_SECURE_TX:			/* ﾒﾓﾘ親展送信			*/
	case SYS_SECURE_RX:					/* 親展受信				*/
#if (PRO_MAKER == FX)
	case SYS_FX_MEMORY_SECURE_TX:		/* FX用メモリ親展送信	*/
	case SYS_FX_SCANNER_SECURE_TX:		/* FX用スキャナ親展送信	*/
#endif	/* (PRO_MAKER == FX) */
		AttributeSet(KindName, KindAttri, PWRD_Secure, LST_NOT);
		break;
	case SYS_SCANNER_RELAY_BROADCAST:	/* ｽｷｬﾅ中継指示送信		*/
	case SYS_MEMORY_RELAY_BROADCAST:	/* ﾒﾓﾘ中継指示送信		*/
	case SYS_RELAY_RX:					/* 中継受信				*/
#if (PRO_MAKER == FX)
	case SYS_FX_MEMORY_RELAY_TX:		/* FX用メモリ親展送信	*/
	case SYS_FX_SCANNER_RELAY_TX:		/* FX用スキャナ親展送信	*/
#endif	/* (PRO_MAKER == FX) */
		AttributeSet(KindName, KindAttri, PWRD_Relay, LST_NOT);
		break;
	case SYS_MANUAL_TRANSMIT:			/* 手動					*/
	case SYS_MANUAL_RECEIVE:			/* 手動					*/
		AttributeSet(KindName, KindAttri, PWRD_Manual, LST_NOT);
		break;
	case SYS_POLLING_TX:				/* ﾎﾟｰﾘﾝｸﾞ送信			*/
	case SYS_POLLING_RX:				/* ﾎﾟｰﾘﾝｸﾞ受信			*/
	case SYS_SEQUENTIAL_POLLING:		/* ﾏﾙﾁﾎﾟｰﾘﾝｸﾞ受信		*/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	case SYS_CONTINUOUS_POLLING_RX:		/* 連続ﾎﾟｰﾘﾝｸﾞ受信		*/
#endif
		AttributeSet(KindName, KindAttri, PWRD_Polling, LST_NOT);
		break;
	case SYS_DB_POLLING_TX:				/* 検索ﾎﾟｰﾘﾝｸﾞ送信		*/
	case SYS_DB_POLLING_RX:				/* 検索ﾎﾟｰﾘﾝｸﾞ受信		*/
		AttributeSet(KindName, KindAttri, PWRD_DbPolling, LST_NOT);
		break;
#if (PRO_F_CODE == ENABLE)
	case SYS_SCANNER_SUB_ADDRESS_TX:	/**	スキャナサブアドレス送信	*/
	case SYS_MEMORY_SUB_ADDRESS_TX:		/**	メモリサブアドレス送信	*/
		AttributeSet(KindName, KindAttri, PWRD_SUB_Tx, LST_NOT);
		break;
	case SYS_SELECT_POLLING_RX:			/**	選択ポーリング受信	*/
	case SYS_SELECT_POLLING_TX:
		AttributeSet(KindName, KindAttri, PWRD_SEP_Rx, LST_NOT);
		break;
	case SYS_SUBADDRESS_SECURE_RX:
 #if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/28 Add By M.Kuwahara */
		AttributeSet(KindName, KindAttri, PWRD_SUB_Secure, LST_NOT);	/* Ｆコード親展 */
 #else
		AttributeSet(KindName, KindAttri, PWRD_SUB_Rx, LST_NOT);
 #endif
		break;
 #if (PRO_FCODE_RELAY == ENABLE) && (PRO_FCODE_KIND_DISPLAY == ENABLE)/* 1998/09/25 Add By M.Kuwahara */
	case SYS_MEMORY_RELAY_BOX_RX:		/** Ｆコード中継 */
		AttributeSet(KindName, KindAttri, PWRD_SUB_Relay, LST_NOT);
		break;
 #endif
 #if (PRO_FCODE_KIND_DISPLAY == ENABLE)	/* 1998/09/28 By M.Kuwahara */
	case SYS_SUBADDRESS_BULLETIN:		/** Ｆコード掲示板 */
		AttributeSet(KindName, KindAttri, PWRD_SUB_Bulletin, LST_NOT);
		break;
 #endif
#endif
#if (PRO_CIPHER == ENABLE)
	case SYS_CIPHER_TX:
/*		AttributeSet(KindName, KindAttri, PWRD_SUB_Tx, LST_NOT);		/* LST ワーディング追加すること 1997/06/20	By T.Yamaguchi */
		AttributeSet(KindName, KindAttri, PWRD_Cipher_Tx, LST_NOT);		/* 97/10/01 By M.Kuwahara */
		break;
	case SYS_CIPHER_RX:
/*		AttributeSet(KindName, KindAttri, PWRD_SUB_Rx, LST_NOT);		/* LST ワーディング追加すること 1997/06/20	By T.Yamaguchi */
		AttributeSet(KindName, KindAttri, PWRD_Cipher_Rx, LST_NOT);		/* 97/10/01 By M.Kuwahara */
		break;
#endif
#if (PRO_FIP == ENABLE)
	case SYS_FIP_TRANSMIT:				/* FIP送信				*/
		AttributeSet(KindName, KindAttri, PWRD_FIP_Tx, LST_NOT);
		break;
	case SYS_FIP_RECEIVE:				/* FIP受信				*/
		AttributeSet(KindName, KindAttri, PWRD_FIP_Rx, LST_NOT);
		break;
	case SYS_FIP_POLLING:				/* FIPﾎﾟｰﾘﾝｸﾞ			*/
		AttributeSet(KindName, KindAttri, PWRD_FIP_Poll, LST_NOT);
		break;
	case SYS_FIP_SECURE:				/* FIPｼﾝﾃﾝ				*/
		AttributeSet(KindName, KindAttri, PWRD_FIP_Sec, LST_NOT);
		break;
#endif	/* (PRO_FIP == ENABLE) */
	case SYS_DELAYED_BROADCAST:			/* 順次同報送信			*/
		AttributeSet(KindName, KindAttri, PWRD_BrdCast, LST_NOT);
		break;
	case SYS_BATCH_MEMORY_TX:
		AttributeSet( KindName, KindAttri, PWRD_Batch, LST_NOT );
		break;
#if (PRO_RELAYED_REPORT == ENABLE)
	case SYS_RELAYED_TX_REPORT:			/* 配信用不達通知		*/
		AttributeSet(KindName, KindAttri, PWRD_RelayedTxReport, LST_NOT);
		break;
#endif	/* (PRO_RELAYED_REPORT == ENABLE) */
	}
}

/*************************************************************************
	module		:[ﾌﾟﾛｸﾞﾗﾑﾃﾞｰﾀ･ﾀﾞｲﾔﾙﾃﾞｰﾀ（ProgramData）、文字列変換。]
	function	:[ﾌﾟﾛｸﾞﾗﾑﾃﾞｰﾀ･ﾀﾞｲﾔﾙﾃﾞｰﾀ（ProgramData）を文字列に変換する。]
	common		:[
		変換先ﾌﾟﾛｸﾞﾗﾑﾃﾞｰﾀ文字列
			必要ない時は、ﾇﾙﾎﾟｲﾝﾀとする。
		行番号（０～）
	]
	condition	:[]
	commment	:[
		変換元ﾌﾟﾛｸﾞﾗﾑﾃﾞｰﾀを、変換先桁数の文字列に変換する。そして、１行の
		最大文字数を４０とした時、行番号で示される行にはいる文字列を、
		変換先ﾌﾟﾛｸﾞﾗﾑﾃﾞｰﾀ文字列にセットする。
	]
	return		:[
					TRUE :全ての検索終了
					FALSE:改行有り
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/12/25]
	author		:[磯辺毅, 桑原美紀]
*************************************************************************/
#define	LN	40		/*１行の文字数*/
UBYTE		ProgramDataDialToString(
						 struct SYS_DialData_t	*DialData,		/*変換元プログラムデータ*/
						 UBYTE DialDataMax,				/*変換元プログラムデータ数*/
						 register UBYTE *DialString,	/*変換先プログラムデータ文字列*/
						 UBYTE LineNumber )				/*行番号*/
{
	UBYTE	i;							/*ﾀﾞｲﾔﾙﾃﾞｰﾀ位置w*/
	UBYTE	j;							/*現在行番号w*/
	UBYTE	str_one[LN+1];				/*１行文字列w*/
#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/11/10 */
//	static UBYTE	string[((SYS_DIRECT_DIAL_MAX - 1) * 2) + SYS_MERCURY_BUF_MAX + 2 + 1];
//	static UBYTE	prefix_number[SYS_MERCURY_BUF_MAX + 2 + 1];
#else
	UBYTE	string[SYS_DIRECT_DIAL_MAX*2+1];/*文字列w*/
#endif
	UBYTE	ret;						/* 文字列ｵｰﾊﾞｰﾁｪｯｸ用のﾘﾀｰﾝ値 */
	UBYTE	length;
	UBYTE	str_len;

	i = 0;
/*	j = 0;*/
	j = LineNumber;	/* 97/09/03 By M.Kuwahara */
	length = 0;
	CMN_MemorySet( str_one, (LN+1), NULL );
	if( DialString != NULL ){
		CMN_MemorySet( DialString, (LN + 1), NULL );
	}

	while( 1 ){
		switch (DialCheckPointer) {
		case	SYS_DIRECT_DIAL:			/* 直接ダイヤル */
			for (i = DialCheckBitPointer; i < SYS_COM_DIRECT_DIAL_MAX ; i++) {
				if (( DialData->Direct[i][0] & 0xF0) != 0xF0) {
					CMN_BCD_ToASC_String( string, DialData->Direct[i] );

#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/11/10 */
//					if (string[0] == '!') {	/* プレフィックス番号登録時 */
//						CMN_MemorySetNULL(prefix_number, SYS_MERCURY_BUF_MAX + 2, NULL);
//						*CMN_StringCopy(prefix_number, SYB_MercuryDialBuffer) = ']';
//
//						string[0] = '[';
//						CMN_InsertString(string, prefix_number, 1);
//					}
#endif

					if( DialString == NULL ){	/* 文字列のセット無しの時 */
						str_len = CMN_StringLength(string);
						if (str_len >= LN) { 	/* １件で改行してしまうデータの時 */
							if (length == 0) {	/* データ無しの時 */
								DialCheckBitPointer = (UBYTE)(i + 1);/** ポインタを次へ更新 */
								return(FALSE);
							}
						}
						if ((length + str_len + 1) > LN){	/* 改行される時 */
							DialCheckBitPointer	= i;
							return( FALSE );
						}
						length	+= str_len + 1;
					}
					else{
						ret = L_string_over_chk(str_one, DialString, string, &j, LineNumber, LN, LST_COMMA_STR_FRONT);
						if( ret == TRUE ){		/* 改行有りの時 */
							DialCheckBitPointer	= i;
							return( FALSE );
						}
					}
				}
			}
			DialCheckPointer	= SYS_ONETOUCH_DIAL;
			DialCheckBitPointer	= 0;
			break;
		case	SYS_ONETOUCH_DIAL:			/* ワンタッチダイヤル */
			for (i = DialCheckBitPointer; i < SYS_ONETOUCH_MAX ; i++) {
				if (CMN_CheckBitAssign( (UBYTE *) DialData->Onetouch, i) == TRUE) {
#if (PRO_KEYPANEL == PANEL_ANZU_L)
					if ( CMN_OffsetToOnetouchCode( i ) <= 0x7A ){
						CMN_MemorySet( string, 3, ' ' );
						string[3] = NULL;
						string[0] = '[';
						string[1] = CMN_OffsetToOnetouchCode( i );
						string[2] = ']';
					}
					else{																/* 'U1'～'U2' */
						CMN_MemorySet( string, 4, ' ' );
						string[4] = NULL;
						string[0] = '[';
						string[1] = 0x55; /* 'U'のASCIIｺ-ﾄﾞ */
						string[2] = CMN_OffsetToOnetouchCode( i ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1～U8記号をつくる */
						string[3] = ']';
					}
#else	/* PANEL_POPLA_B/L/H */
					CMN_MemorySet( string, 4, ' ' );
					string[4] = NULL;
 #if (PRO_PANEL == ANK)
					string[0] = '[';
					CMN_UnsignedIntToASC( &string[1], 	/* 01～72記号をつくる */
						(UWORD)(CMN_OffsetToOnetouchCode( i ) - 0x40), 2, '0' );
					string[3] = ']';
 #endif
 #if (PRO_PANEL == KANJI)
			 		/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
					string[0] = LCD_PICFONT;
					string[1] = LCD_PICFONT_LOWER;
					CMN_UnsignedIntToASC( &string[2], 	/* 01～72記号をつくる */
						(UWORD)(CMN_OffsetToOnetouchCode( i ) - 0x40), 2, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
					if( DialString == NULL ){	/* 文字列のセット無しの時 */
						str_len = CMN_StringLength(string);
						if ((length + str_len + 1) > LN){
							DialCheckBitPointer	= i;
							return( FALSE );
						}
						length += str_len + 1;
					}
					else{
						ret = L_string_over_chk(str_one, DialString, string, &j, LineNumber, LN, LST_COMMA_STR_FRONT);
						if( ret == TRUE ){		/* 改行有りの時 */
							DialCheckBitPointer	= i;
							return( FALSE );
						}
					}
				}
			}
			DialCheckPointer	= SYS_SPEED_DIAL;
			DialCheckBitPointer	= 0;
			break;
		case	SYS_SPEED_DIAL:			/* 短縮ダイヤル */
			for (i = DialCheckBitPointer; i < SYS_SPEED_DIAL_MAX ; i++) {
				if (CMN_CheckBitAssign( (UBYTE *) DialData->Speed, i) == TRUE) {
					if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
						string[0] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
						string[0] = 'S';
#endif
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
							if ( GetRecordFromNumber( i ) != 0xFFFF ) {
#if (1) /* 任意短縮４桁化 2002/02/13 By M.Maeda */
 								CMN_UnsignedIntToASC( &string[1], GetRecordFromNumber( i ), OP_SPEED_FIGURE_MAX, '0' );
#else
//								CMN_UnsignedIntToASC( &string[1], 
//									GetRecordFromNumber( i ), 2, '0' );
#endif
							}
							else {
#if (1) /* 任意短縮４桁化 2002/02/13 By M.Maeda */
								CMN_MemorySet( &string[1], OP_SPEED_FIGURE_MAX,'*' );
#else
//								CMN_MemorySet( &string[1], 3,'*' );
#endif
							}
						}
						else{	/* 通常の短縮の時 */
 #if ( PRO_CPU == SH7043 )	/* FX,MMLで短縮ﾀﾞｲﾔﾙNo.が000～or001～と違う時のため */
							CMN_UnsignedIntToASC( &string[1], i+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
							CMN_UnsignedIntToASC( &string[1], i+1, 3, '0' );
 #endif
						}
#if (1) /* 任意短縮４桁化 2002/02/13 By M.Maeda */
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
							string[OP_SPEED_FIGURE_MAX + 1] = NULL;
						}
						else {
							string[4] = NULL;
						}
#else
//						string[4] = NULL;
#endif
					}
					else {
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
						string[0] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
						string[0] = 'S';
#endif
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
							if ( GetRecordFromNumber( i ) != 0xFFFF ) {
								CMN_UnsignedIntToASC( &string[1], 
									GetRecordFromNumber( i ), 2, '0' );
							}
							else {
								CMN_MemorySet( &string[1], 3,'*' );
							}
						}
						else{	/* 通常の短縮の時 */
 #if ( PRO_CPU == SH7043 )	/* FX,MMLで短縮ﾀﾞｲﾔﾙNo.が000～or001～と違う時のため */
  #if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2で短縮ﾀﾞｲﾔﾙNoか、01からカントすること) Modify by SMuratec L.Z.W 2003/10/08 */
							CMN_UnsignedIntToASC( &string[1], i+(OPR_SPEED_DIAL_MIN), OP_SPEED_FIGURE_MAX, '0' );
  #else
							CMN_UnsignedIntToASC( &string[1], i, 2, '0' );
  #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
 #else
							CMN_UnsignedIntToASC( &string[1], DialData->Speed[i]+1, 2, '0' );
 #endif
						}
						string[3] = NULL;
					}
					if( DialString == NULL ){	/* 文字列のセット無しの時 */
						str_len = CMN_StringLength(string);
						if ((length + str_len + 1) > LN){
							DialCheckBitPointer = i;
							return( FALSE );
						}
						length += str_len + 1;
					}
					else{
						ret = L_string_over_chk(str_one, DialString, string, &j, LineNumber, LN, LST_COMMA_STR_FRONT);
						if( ret == TRUE ){		/* 改行有りの時 */
							DialCheckBitPointer	= i;
							return( FALSE );
						}
					}
				}
			}
			DialCheckPointer	= SYS_GROUP_DIAL;
			DialCheckBitPointer	= 0;
			break;
		case	SYS_GROUP_DIAL:				/* グループダイヤル */
			if (DialData->Group == 0xffffffff) {
				string[0] = 'G';
				CMN_UnsignedIntToASC_NULL(&string[1] ,0, 0, 0);
				if( DialString == NULL ){	/* 文字列のセット無しの時 */
					str_len = CMN_StringLength(string);
					if ((length + str_len + 1) > LN){
						DialCheckBitPointer	= i;
						return( FALSE );
					}
					length += str_len + 1;
				}
				else{
					ret = L_string_over_chk(str_one, DialString, string, &j, LineNumber, LN, LST_COMMA_STR_FRONT);
					if( ret == TRUE ){		/* 改行有りの時 */
						DialCheckBitPointer	= i;
						return( FALSE );
					}
				}
			}
			else {
				for (i = DialCheckBitPointer; i < SYS_GROUP_NUMBER_MAX; i++) {
					if (CMN_CheckLongBitAssign(DialData->Group, i) == TRUE) {
						string[0] = 'G';
						CMN_UnsignedIntToASC_NULL(&string[1] ,(i + 1), 0, 0);
						if( DialString == NULL ){	/* 文字列のセット無しの時 */
							str_len = CMN_StringLength(string);
							if ((length + str_len + 1) > LN){
								DialCheckBitPointer = i;
								return( FALSE );
							}
							length += str_len + 1;
						}
						else{
							ret = L_string_over_chk(str_one, DialString, string, &j, LineNumber, LN, LST_COMMA_STR_FRONT);
							if( ret == TRUE ){		/* 改行有りの時 */
								DialCheckBitPointer	= i;
								return( FALSE );
							}
						}
					}
				}
			}
			DialCheckPointer	= SYS_EMPTY_DIAL;
			DialCheckBitPointer	= 0;
			return( TRUE );
		}
	}
	return ( TRUE );
}
#undef	LN

/*************************************************************************
	module		:[ProgramDataDialToString()ProgOptionDataToString()の下位関数]
	function	:[]
	common		:[
	]
	condition	:[
		ｶﾝﾏ位置	LST_COMMA_STR_BACK
				LST_COMMA_STR_FRONT
	]
	commment	:[]
	return		:[
					TRUE :改行有り
					FALSE:改行無し
]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
UBYTE				L_string_over_chk(
						 UBYTE *str_one,			/*１行文字列*/
						 UBYTE *str_ret,			/*ﾘﾀｰﾝ文字列*/
						 register UBYTE *string,	/*セット文字列*/
						 UBYTE *j,					/*現在行*/
						 UBYTE linenumber,			/*ﾘﾀｰﾝ対象行*/
						 UBYTE l_string,			/*１行の最大行数*/
						 UBYTE comma )				/*ｶﾝﾏ位置*/
{
	register UWORD	i;
	BYTE			k;
	UBYTE			ret = FALSE;

	if ( (UBYTE)(CMN_StringLength(str_one) + CMN_StringLength(string) +1) <= l_string
		  || CMN_StringLength(str_one) == 0 ) {
		if ( CMN_StringLength(str_one) > 0 ) {
			i = CMN_StringLength(str_one);
			if ( comma == LST_COMMA_STR_FRONT ) {
				if ( i + CMN_StringLength(string) != l_string) {
					*(str_one+i) = ',';
					*(str_one+i+1) = NULL;
				}
			}
			else {
				*(str_one+i) = ' ';
				*(str_one+i+1) = NULL;
				i++;
				for ( k = (BYTE)(i-1); k >= 0; k-- ) {
					if ( *(str_one+k) != ' ' && *(str_one+k) != NULL ) {
						*(str_one+k+1) = ',';
						break;
					}
				}
			}
			if ( *j == linenumber ) {
				i = CMN_StringLength(str_ret);
				if ( comma == LST_COMMA_STR_FRONT ) {
					if ( i + CMN_StringLength(string) != l_string) {
						*(str_ret+i) = ',';
						*(str_ret+i+1) = NULL;
					}
				}
				else {
					*(str_ret+i) = ' ';
					*(str_ret+i+1) = NULL;
					i++;
					for ( k = (BYTE)(i-1); k >= 0; k-- ) {
						if ( *(str_ret+k) != ' ' && *(str_ret+k) != NULL ) {
							*(str_ret+k+1) = ',';
							break;
						}
					}
				}
			}
		}
	}
	else {
		(*j)++;
		CMN_MemorySet( str_one, (l_string+1), NULL );
		ret	= TRUE;
	}
	CMN_StringCopy( (str_one+CMN_StringLength(str_one)), string ); /* 1996/03/12 Eguchi */
	if ( *j == linenumber ) {
		CMN_StringCopy( (str_ret+CMN_StringLength(str_ret)), string ); /*1996/03/12 Eguchi */
	}
	return( ret );
}

/*************************************************************************
	module		:[ｵﾌﾟｼｮﾝﾃﾞｰﾀ、文字列変換。]
	function	:[ｵﾌﾟｼｮﾝﾃﾞｰﾀを文字列に変換する。]
	common		:[
	]
	condition	:[
		変換先ｵﾌﾟｼｮﾝﾃﾞｰﾀ文字列
			必要ない時は、ﾇﾙﾎﾟｲﾝﾀとする。
	]
	commment	:[
		変換元ｵﾌﾟｼｮﾝﾃﾞｰﾀを、変換先桁数の文字列に変換する。そして、１行の
		最大文字数を１５とした時、行番号で示される行にはいる文字列を、
		変換先ｵﾌﾟｼｮﾝﾃﾞｰﾀ文字列にｾｯﾄする。
	]
	return		:[
		１行の最大文字数を１５とした時、ｵﾌﾟｼｮﾝﾃﾞｰﾀを全て印刷するのに
		何行必要かを返す。（１～）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
#define	LN	15		/*１行の文字数*/
#if ( PRO_MAKER == FX )
UBYTE		ProgOptionDataToString(
						 UWORD Item,					/*変換元通信種類*/
						 WORD SecureNumber,				/*変換元親展番号*/
						 UBYTE RelayGroupNumber[],		/*変換元中継ｸﾞﾙｰﾌﾟ番号*/
						 UWORD DatabaseNumber[],		/*変換元検索番号*/
						 register UBYTE *ProgOptString,	/*変換先ｵﾌﾟｼｮﾝﾃﾞｰﾀ文字列*/
						 UBYTE LineNumber )				/*行番号*/
#else
UBYTE		ProgOptionDataToString(
						 UWORD Item,					/*変換元通信種類*/
						 WORD SecureNumber,				/*変換元親展番号*/
						 UDWORD RelayGroupNumber,		/*変換元中継ｸﾞﾙｰﾌﾟ番号*/
						 UWORD DatabaseNumber[],		/*変換元検索番号*/
						 register UBYTE *ProgOptString,	/*変換先ｵﾌﾟｼｮﾝﾃﾞｰﾀ文字列*/
						 UBYTE LineNumber )				/*行番号*/
#endif
{
	UBYTE	j;				/*現在行番号w*/
	UBYTE	k;				/*ｸﾞﾙｰﾌﾟ番号w*/
#if ( PRO_MAKER != FX )
	UDWORD	l;				/*ｸﾞﾙｰﾌﾟﾋﾞｯﾄ*/
#endif
	UBYTE	m;				/*loop*/
	UBYTE	str_one[LN+1];	/*１行文字列w*/
	UBYTE	str_ret[LN+1];	/*ﾘﾀｰﾝ文字列w*/
	UBYTE	string[6];		/*文字列w*/

	j = 0;
	CMN_MemorySet( str_one, (LN+1), NULL );
	CMN_MemorySet( str_ret, (LN+1), NULL );
	switch ( Item ) {
		case SYS_SCANNER_SECURE_TX:
		case SYS_MEMORY_SECURE_TX:
			CMN_UnsignedIntToASC_NULL( string, SecureNumber, 1, '0' );
			L_string_over_chk( str_one, str_ret, string, &j, LineNumber, LN, LST_COMMA_STR_BACK );
			break;
#if ( PRO_MAKER == FX )
		case	SYS_FX_MEMORY_SECURE_TX:	 /*	 FX用メモリ親展送信	 */
		case	SYS_FX_SCANNER_SECURE_TX:	 /*	 FX用スキャナ親展送信*/
			CMN_UnsignedIntToASC_NULL( string, SecureNumber, 2, ' ' );
			L_string_over_chk( str_one, str_ret, string, &j, LineNumber, LN, LST_COMMA_STR_BACK );
			break;
#endif
#if ( PRO_MAKER != FX )
		case SYS_SCANNER_RELAY_BROADCAST:
		case SYS_MEMORY_RELAY_BROADCAST:
			l = 1;
			for ( k = 1; k <= LST_GROUP_BIT; k++ ) {
				if ( (RelayGroupNumber & l) == l ) {
					string[0] = 'G';
					CMN_UnsignedIntToASC_NULL( &string[1], k, 0, 0 );
					/* for ( m = (UBYTE)CMN_StringLength(string); m < 3; m++ ) [*/
					for ( m = (UBYTE)CMN_StringLength(string); m < 4; m++ ) {	/* By M.Kuwahara 97/01/23 */
						string[m] = ' ';
						string[m+1] = NULL;
					}
					L_string_over_chk( str_one, str_ret, string, &j, LineNumber
					  , LN, LST_COMMA_STR_BACK );
				}
				l <<= 1;
			}
			break;
#endif
#if ( PRO_MAKER == FX )
		case	SYS_FX_MEMORY_RELAY_TX:		/*	FX用メモリ中継送信	*/
		case	SYS_FX_SCANNER_RELAY_TX:	/*	FX用スキャナ中継送信*/
			for ( k = 0; k < SYS_FX_RELAY_MAX; k++ ) {
				if ( RelayGroupNumber[k] == 0xff ) {
					break;
				}
				else {
					string[0] = FXBCD_ToASC((UBYTE)((RelayGroupNumber[k] & 0xF0) >> 4));
					string[1] = FXBCD_ToASC((UBYTE)(RelayGroupNumber[k] & 0x0F));
					string[2] = NULL;
				}
				L_string_over_chk( str_one, str_ret, string, &j, LineNumber
				  , LN, LST_COMMA_STR_BACK );
			}
			break;
#endif
		case SYS_DB_POLLING_RX:
			for ( k = 0; k < SYS_DATA_BASE_MAX; k++ ) {
				if ( DatabaseNumber[k] == 0xFFFF ) {
					break;
				}
				CMN_UnsignedIntToASC_NULL( string, DatabaseNumber[k], 0, 0 );
				for ( m = (UBYTE)CMN_StringLength(string); m < 4; m++ ) {
					string[m] = ' ';
					string[m+1] = NULL;
				}
				L_string_over_chk( str_one, str_ret, string, &j, LineNumber
				  , LN, LST_COMMA_STR_BACK );
			}
			break;
		case SYS_BATCH_MEMORY_TX:
			CMN_StringCopyNULL(str_ret, PWRD_BoxNo);
			break;
		case SYS_CHAR_TX:
			break;
	}
	if ( ProgOptString != NULL_PT ) {
		CMN_StringCopyNULL( ProgOptString, str_ret ); /*1996/03/12 Eguchi */
	}
	return ( (UBYTE)( j+1 ) );
}
#undef	LN

/*************************************************************************
	module		:[ｸﾞﾙｰﾌﾟﾃﾞｰﾀ、略称型文字列変換。]
	function	:[ｸﾞﾙｰﾌﾟﾃﾞｰﾀを略称型の文字列に変換する。]
	common		:[
	]
	condition	:[]
	commment	:[
		ｸﾞﾙｰﾌﾟﾃﾞｰﾀを文字列に変換しｸﾞﾙｰﾌﾟ文字列にｾｯﾄする。
		ﾌｫｰﾏｯﾄは以下の通り。
		　”xxxxxxxxxxxxxxx”先頭から９文字がｸﾞﾙｰﾌﾟ番号１～９に対応。
		　ｸﾞﾙｰﾌﾟ番号１０～１９のうち１つでも指定されていたなら１０，１１
		　文字目に”1X”をｾｯﾄ。ｸﾞﾙｰﾌﾟ番号２０～２９、３０～３２に
		　ついても同じ。
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
void				GroupToShortString(
						UDWORD GroupData,		/*ｸﾞﾙｰﾌﾟﾃﾞｰﾀ*/
						UBYTE* GroupString,		/*ｸﾞﾙｰﾌﾟ文字列*/
						UBYTE sifuto_cnt)		/*ｼﾌﾄﾃﾞｰﾀ*/
#else
void				GroupToShortString(
						UDWORD GroupData,				/*ｸﾞﾙｰﾌﾟﾃﾞｰﾀ*/
						register UBYTE* GroupString )	/*ｸﾞﾙｰﾌﾟ文字列*/
#endif
{
	UBYTE	i;			/*loop*/
	UDWORD	j;			/*ｸﾞﾙｰﾌﾟﾋﾞｯﾄ*/
	UBYTE	k;			/*ﾃﾞｰﾀ数*/

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	CMN_MemorySetNULL( GroupString, 27, ' ' ) ;
#else
	CMN_MemorySetNULL( GroupString, 15, ' ' ) ;
#endif
	j = 1;
	k = 0;

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	j = j << (UWORD)sifuto_cnt;	/* 検索したい場所までシフトさせる */
#endif

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	for ( i = sifuto_cnt + 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
#else
	for ( i = 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
#endif
		if ( (GroupData & j) == j ) {
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			if ( k < 9 ) {
#else
			if ( k < 5 ) {
#endif
				if ( k > 0 ) {
					GroupString[k*3-1] = ',';
				}
				CMN_UnsignedIntToASC( &GroupString[k*3], (UWORD)(i), 2, ' ' );
				k++;
			}
			else {
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
				GroupString[k*3-1] = ',';
#else
				GroupString[k*3-1] = LST_A_TENTEN;
#endif
				break;
			}
		}
		j <<= 1;
	}
}
#if(0)
/*************************************************************************
	module		:[メモリ残量（ＫＢ）]
	function	:[メモリ残量（ＫＢ）を文字列にて返す]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		メモリ残量は512ｷﾛﾊﾞｲﾄ単位とする
			例	400kb -> 512kb	1000kb ->1024kb
				  0kb -> 512kb
		メモリ残量文字列の例
			512ｷﾛﾊﾞｲﾄの時->"512 KB"
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1994/02/10]
	author		:[豊田]
*************************************************************************/
//void					MemoryEmptyBkString(
//							 UBYTE *String )	/*メモリ残量文字列*/
//#if (0) /* 機器設定リストに残量と搭載量の両方または搭載量のみを記載する。By H.Fujimura 1999/03/04 */ /* 1999/08/23 M.Maeda */
//{
//	UWORD	work;	/*kb*/
//
//	/* Modify by NOBUKO	 Aug.30,94 */
//	work = MEM_CountTotalEmptyBlock()*4;	/* KIRI ｷﾛﾊﾞｲﾄ*/
//
//	if ( work == 0 ) {
//		work = 1;
//	}
//
//	work = (UWORD)( (work-1)/512);	/*512kbを1とした単位に変換*/
//											/*512kbまでなら0となる*/
//	work = (work+1) * 512;					/*ｷﾛﾊﾞｲﾄ*/
//
//	CMN_UnsignedIntToASC_NULL( String, work, 0, '0' );
//	work = CMN_StringLength( String );
//	String[work] = ' ';
//	String[work+1] = 'K';
//	String[work+2] = 'B';
//	String[work+3] = NULL;
//}
//#else /** メモリ量表記統一 1999/08/23 M.Maeda */
//{
//	UBYTE	i;
//
//	/* 機器設定リストに残量と搭載量の両方を記載する */
//	if (CHK_RestMemorySizePrint()) {
//		CMN_UnsignedIntToASC_NULL(&String[0], (UWORD)(MEM_CountTotalEmptyBlock() * 4), 0, 0);
//		i = CMN_StringLength(String);
//		String[i++] = ' ';
//		String[i++] = 'K';
//		String[i++] = 'B';
//		String[i++] = ' ';
//		String[i++] = '/';
//		String[i++] = ' ';
//		CMN_UnsignedIntToASC_NULL(&String[i], (UWORD)(MEM_TotalAvailableStoreBlkCnt * 4), 0, 0);
//		i = CMN_StringLength(String);
//		String[i++] = ' ';
//		String[i++] = 'K';
//		String[i++] = 'B';
//		String[i++] = '\0';
//	}
//	/* 機器設定リストに搭載量のみを記載する */
//	else {
//		CMN_UnsignedIntToASC_NULL(&String[0], (UWORD)(MEM_TotalAvailableStoreBlkCnt * 4), 0, 0);
//		i = CMN_StringLength(String);
//		String[i++] = ' ';
//		String[i++] = 'K';
//		String[i++] = 'B';
//		String[i++] = '\0';
//	}
//}
#endif
/** メモリ量表記統一 KAKIからコピー 1999/08/23 M.Maeda */
/*************************************************************************
	module		:[メモリ搭載量（ＫＢ）]
	function	:[メモリ搭載量（ＫＢ）を文字列にて返す]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		メモリ搭載量 ＝ 標準メモリ量(ｶﾀﾛｸﾞｽﾍﾟｯｸ)＋増設メモリ量
		増設メモリ量は512ｷﾛﾊﾞｲﾄ単位とする
			例	400kb -> 512kb	1000kb ->1024kb
				  0kb -> 512kb
		メモリ残量文字列の例
			2048ｷﾛﾊﾞｲﾄの時->"2048 KB"
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/08/19]
	author		:[村田]
*************************************************************************/
void	MemoryEmptyBkString( UBYTE *String )	/*メモリ残量文字列*/
{
	UBYTE	i;
	UWORD	work;	/*kb*/
	UWORD	option_memory;
#if defined(POPLAR_F) || defined(ANZU_L) || defined(POPLAR_L) || defined(POPLAR_N)
	UWORD	mask;
#endif

#if defined(POPLAR_F) || defined(ANZU_L) || defined(POPLAR_L) || defined(POPLAR_N)
								/* 2000/09/26 Y.Murata ANZU_L POPLAR_L POPLAR_N条件追加 */
	/* 2000/01/11 Y.Murata
	 * メモリ残量印字対応
	*/
	if (MEM_FATArea[0] == MEM_BAD_BLOCK) {	/* 最初の１Ｍがマスクされている時 */
		work = 1024;
		mask = MEM_DRAM_MASK_BLOCK;
	}
	else {
		work = 2048;
		mask = 0;
	}
	if (MEM_TotalAvailableStoreBlkCnt > (MEM_FAT_AREA_STANDARD -mask - 1)) {
		option_memory = (MEM_TotalAvailableStoreBlkCnt - (MEM_FAT_AREA_STANDARD - mask - 1)) * 4;
		option_memory = (UWORD)((option_memory-1)/512);		/*512kbを1とした単位に変換*/
															/*512kbまでなら0となる*/
		option_memory = (option_memory+1) * 512;			/*ｷﾛﾊﾞｲﾄ */
		work += option_memory;
	}

#else
	/* 標準メモリ －カタログ上のメモリ搭載量－*/
	work = MEM_SPEC_STANDARD_SIZE;

	/* 増設メモリ */
	if (MEM_TotalAvailableStoreBlkCnt > (MEM_FAT_AREA_STANDARD - 1)) {
		option_memory = (MEM_TotalAvailableStoreBlkCnt - (MEM_FAT_AREA_STANDARD - 1)) * 4;
		option_memory = (UWORD)((option_memory-1)/512);		/*512kbを1とした単位に変換*/
															/*512kbまでなら0となる*/
		option_memory = (option_memory+1) * 512;			/*ｷﾛﾊﾞｲﾄ */
		work += option_memory;
	}
#endif

	/* メモリSW H-2-4 をONにすると
	 * 機器設定リストに残量と搭載量(ｶﾀﾛｸﾞｽﾍﾟｯｸ)の両方を記載する
	*/
	if (CHK_RestMemorySizePrint()) {
		CMN_UnsignedIntToASC_NULL(&String[0], (UWORD)(MEM_CountTotalEmptyBlock() * 4), 0, 0);
		i = CMN_StringLength(String);
		String[i++] = ' ';
		String[i++] = 'K';
		String[i++] = 'B';
		String[i++] = ' ';
		String[i++] = '/';
		String[i++] = ' ';
		CMN_UnsignedIntToASC_NULL(&String[i], work, 0, 0);
		i = CMN_StringLength(String);
		String[i++] = ' ';
		String[i++] = 'K';
		String[i++] = 'B';
		String[i++] = '\0';
	}
	else {
		CMN_UnsignedIntToASC_NULL( String, work, 0, '0' );
		i = CMN_StringLength( String );
		String[i++] = ' ';
		String[i++] = 'K';
		String[i++] = 'B';
		String[i++] = NULL;
	}
}
