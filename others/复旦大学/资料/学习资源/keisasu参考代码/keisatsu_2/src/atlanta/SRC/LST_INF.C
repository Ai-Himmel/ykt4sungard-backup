/*************************************************************************
	System		:ANZU_L InternetFAX
				:POPLAR_B InternetFAX
				:POPLAR_H InternetFAX
	FileName	:LST_INF.C
	Author		:Y.Tanimoto
	Date		:1998/02/17
	RealTimeOS	:RISC Monitor
	Description	:ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　各種リストプリント
	Module		:
	Language	:SHC
	CPU			:SH7043
	Maintenance	:

	Copyright(C) 1997 Murata Machinery Ltd. All rights reserved
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysprint.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\memerpro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#include	"\src\atlanta\define\mon_pro.h"/*1998/05/22 Eguchi */
#include 	"\src\atlanta\sh7043\define\def_semn.h"	/* 1998/05/22 Eguchi */
#include 	"\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1998/05/22 Eguchi */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\define\inf_def.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
#include	"\src\atlanta\ext_v\inf_data.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/*************************************************************************
	module		:[受信したTEXTﾒｰﾙの印字]
	function	:[
		1.DRAMにｷｬﾗｸﾀｰで蓄積されているﾃﾞｰﾀをﾌﾟﾛｸﾞﾗﾑ転送で抜き出してくる
		2.FAX内部で持っているﾌｫﾝﾄに変換してﾌﾟﾘﾝﾄする
		3.対応している文字コード
		　ISO-2022JPコード
		　US-ASCIIコード
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		TEXTメールの終了コードは0008が入っていること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/17]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintRxTextMail(void)
{
	WORD	ret;		/*	実行結果	*/
	UBYTE	line;		/*	印刷可能行数	*/
	UBYTE	status;

	SYS_INF_IndexData.Item = SYS_MEM_MAIL_RX_FILE;
	SYS_INF_IndexData.No = SYS_DocumentPrintNo;
	SYS_INF_IndexData.BoxNumber = MEM_IGNORE_BOX_NUMBER;
	SYS_INF_IndexData.Page = CMN_GetRxMailPrintStartPage(SYS_MEM_MAIL_RX_FILE , SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER);
	if (MEM_ReadOpen(&SYS_INF_IndexData, &SYS_INF_ExecData) == MEM_NO_INDEX) {
		return ( MSG_PRN_LST_END );	/*　何もせずに終了を返して管理テーブルを消去する　*/
	}
	SYS_INF_DataReadPtr = (UBYTE *)((UDWORD)(MEM_STOREAREA_START_ADDRESS)+((UDWORD)MEM_BLOCK_SIZE * (UDWORD)SYS_INF_ExecData.ExecBlockNo));
	SYS_INF_DataReadCnt = 0;

	status = SYS_INF_READ_CHAR_START;
	while (status != SYS_INF_READ_CHAR_END) {
		/**	プリントスタート	*/
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		/**	印刷可能行数ｾｯﾄ	*/
		line = (UBYTE)PaperSizeLen();

		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		line--;

		while (1) {
			Prn_Att_Str_Clear(List.S.Print, List.S.Attribute);
			status = ConvertOneLineTextData(List.S.Print);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line--;
			if (status == SYS_INF_READ_CHAR_END) {
				MEM_ClearPage(&SYS_INF_IndexData);
				SYS_INF_IndexData.Page++;
				if (MEM_ReadOpen(&SYS_INF_IndexData, &SYS_INF_ExecData) == MEM_NO_INDEX) {
				/*　一つの管理テーブルで一通のTEXTメールを管理する時（普通はこっち）　*/
					ret = CharacterPrint( LST_CLOSE );
					return ( ret );
				}
				else {
				/*　一つの管理テーブルで複数のTEXTメールを管理する時　*/
					SYS_INF_DataReadPtr = (UBYTE *)((UDWORD)(MEM_STOREAREA_START_ADDRESS)+(UDWORD)((UDWORD)MEM_BLOCK_SIZE * (UDWORD)SYS_INF_ExecData.ExecBlockNo));
					SYS_INF_DataReadCnt = 0;
					status = SYS_INF_READ_CHAR_PAGE;
					line = 0;
				}
			}
			if ((line == 0) || (status == SYS_INF_READ_CHAR_PAGE)) {
				/* 改ページ　*/
				break;
			}
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
	return (ret);
}

/*************************************************************************
	module		:[TEXTﾒｰﾙの1行印字]
	function	:[
		1.以下のコード変換を行います。
		日本語（SJIS）対応機種			日本語（SJIS）非対応機種
			<POPLAR_B>                      <ANZU_L>
		US-ASCII -> SJIS				US-ASCII -> US-ASCII
		ISO-2022JP -> SJIS				ISO-2022JP -> 文字化け
		2.データはDRAMから読み出してきます。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1.受信原稿と同じようにDRAMにTEXTデータが蓄積されていること
		2.データの最後に0x00、0x08の2byteを付加して蓄積しておくこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/17]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	ConvertOneLineTextData(UBYTE *dst_ptr)
{
	UBYTE	size;
	UBYTE	ret;

	size = 0;
	ret = SYS_INF_READ_CHAR_CR;

#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	while (size < (LST_COLUM - 2)) {
#else
	while (size < (LST_COLUM - 1)) {
#endif
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		/*　半角→SJISへの変換　*/
		if (((0x20 <= *SYS_INF_DataReadPtr) && (*SYS_INF_DataReadPtr <= 0x70))
			|| ((0xA0 <= *SYS_INF_DataReadPtr) && (*SYS_INF_DataReadPtr <= 0xDF))) {
			*dst_ptr++ = 0x85;
			size++;
			if ((0x20 <= *SYS_INF_DataReadPtr) && (*SYS_INF_DataReadPtr <= 0x5F)) {
				*dst_ptr++ = (*SYS_INF_DataReadPtr + 0x1F);
				size++;
			}
			else if ((0x60 <= *SYS_INF_DataReadPtr) && (*SYS_INF_DataReadPtr <= 0x70)) {
				*dst_ptr++ = (*SYS_INF_DataReadPtr + 0x20);
				size++;
			}
			else {
				*dst_ptr++ = (*SYS_INF_DataReadPtr - 0x02);
				size++;
			}
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
		}
		/*　エスケープコードを検出　*/
		else if (*SYS_INF_DataReadPtr == 0x1B) {
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
			if (*SYS_INF_DataReadPtr == '$') {
				if (ReadNextData() != TRUE) {
					return (SYS_INF_READ_CHAR_END);
				}
				if ((*SYS_INF_DataReadPtr == 'B') || (*SYS_INF_DataReadPtr == '@')) {
					/*　これ以降はJISｺｰﾄﾞ　*/
					if (ReadNextData() != TRUE) {
						return (SYS_INF_READ_CHAR_END);
					}
					while ((*SYS_INF_DataReadPtr != 0x1b) && (size < (LST_COLUM - 2))) {
						/*　JIS→SJISへ変換　*/
						*dst_ptr = ((*SYS_INF_DataReadPtr - 0x21 >> 1) + 0x81);
						if (*dst_ptr > 0x9F) {
							*dst_ptr += 0x40;
						}
						dst_ptr++;
						size++;
						if (*SYS_INF_DataReadPtr & 0x01) {
							if (ReadNextData() != TRUE) {
								return (SYS_INF_READ_CHAR_END);
							}
							*dst_ptr = (*SYS_INF_DataReadPtr + 0x1F);
						}
						else {
							if (ReadNextData() != TRUE) {
								return (SYS_INF_READ_CHAR_END);
							}
							*dst_ptr = (*SYS_INF_DataReadPtr + 0x7D);
						}
						if (*dst_ptr >= 0x7F) {
							*dst_ptr += 0x01;
						}
						dst_ptr++;
						size++;
						if (ReadNextData() != TRUE) {
							return (SYS_INF_READ_CHAR_END);
						}
					}
				}
			}
			else if (*SYS_INF_DataReadPtr == '(') {
				if (ReadNextData() != TRUE) {
					return (SYS_INF_READ_CHAR_END);
				}
				if (*SYS_INF_DataReadPtr == 'B') {
					/*　ASCIIｺｰﾄﾞに戻ります　*/
					if (ReadNextData() != TRUE) {
						return (SYS_INF_READ_CHAR_END);
					}
				}
			}
		}
#else
		if (((UBYTE)0x20 <= (UBYTE)*SYS_INF_DataReadPtr) && ((UBYTE)*SYS_INF_DataReadPtr <= (UBYTE)0x7F)) {
			*dst_ptr = *SYS_INF_DataReadPtr;
			dst_ptr++;
			size++;
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
		}
#endif
		else if (*SYS_INF_DataReadPtr == CR) {
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
			return (SYS_INF_READ_CHAR_CR);
		}
		else if (*SYS_INF_DataReadPtr == 0x00) {
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
			if (*SYS_INF_DataReadPtr == 0x08) {
				return (SYS_INF_READ_CHAR_END);
			}
		}
		else if (*SYS_INF_DataReadPtr == 0x0A) {
			/* LFコードは読み飛ばします */
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
		}
		else {	/*　文字化けするけどそのままにします　*/
			*dst_ptr = *SYS_INF_DataReadPtr;
			dst_ptr++;
			size++;
			if (ReadNextData() != TRUE) {
				return (SYS_INF_READ_CHAR_END);
			}
		}
	}
	return(SYS_INF_READ_CHAR_CR);
}

/*************************************************************************
	module		:[DRAMから次の文字を読む]
	function	:[
		1.ポインタを進める
		2.1Block分のFATを読み終えたら次のFATのアドレスをセット
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/17]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	ReadNextData(void)
{
	SYS_INF_DataReadPtr++;
	SYS_INF_DataReadCnt++;
	if (SYS_INF_DataReadCnt >= MEM_BLOCK_SIZE) {
		if (SYS_INF_ExecData.ExecBlockNo == MEM_EOP_BLOCK) {
			return(FALSE);
		}
		SYS_INF_ExecData.ExecBlockNo = MEM_ReadGetNextBlockNoERom(SYS_INF_ExecData.ExecBlockNo);
		SYS_INF_DataReadPtr = (UBYTE *)((UDWORD)(MEM_STOREAREA_START_ADDRESS)+(UDWORD)((UDWORD)MEM_BLOCK_SIZE * (UDWORD)SYS_INF_ExecData.ExecBlockNo));
		SYS_INF_DataReadCnt = 0;
	}
	return(TRUE);
}

/*************************************************************************
	module		:[不達通知のTEXT部の印字]
	function	:[
		1.DRAMにｷｬﾗｸﾀｰで蓄積されているﾃﾞｰﾀをﾌﾟﾛｸﾞﾗﾑ転送で抜き出してくる
		2.FAX内部で持っているﾌｫﾝﾄに変換してﾌﾟﾘﾝﾄする
		3.対応している文字コード
		　ISO-2022JPコード
		　US-ASCIIコード
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		TEXTメールの終了コードは0008
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/25]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintReturnedMailTextPart( UBYTE prn_mode )
{
	WORD	ret;		/*	実行結果	*/
	UBYTE	line;		/*	印刷可能行数	*/
	UBYTE	status;
	UBYTE	page;

	SYS_INF_IndexData.Item = SYS_MEM_MAIL_RX_FILE;
	SYS_INF_IndexData.No = SYS_DocumentPrintNo;
	SYS_INF_IndexData.BoxNumber = MEM_IGNORE_BOX_NUMBER;
	SYS_INF_IndexData.Page = SYS_DocumentPrintPageNo;

	LST_CharacterLine = 0;	/* 印字した行数を初期化 */

	/*
	**　TEXT部はIndexTable上で必ず1ページ目として蓄積されていることが前提になります。
	**　ｲﾒｰｼﾞ部は2ページ目以降に蓄積される必要が有ります
	*/
	if (SYS_DocumentPrintPageNo > 1) {
		return ( OK );	/*　何もせずに画データ部の印字に移る　*/
	}
	if (MEM_ReadOpen(&SYS_INF_IndexData, &SYS_INF_ExecData) == MEM_NO_INDEX) {
		return ( OK );	/*　何もせずに画データ部の印字に移る　*/
	}
	SYS_INF_DataReadPtr = (UBYTE *)((UDWORD)(MEM_STOREAREA_START_ADDRESS)+(UDWORD)((UDWORD)MEM_BLOCK_SIZE * (UDWORD)SYS_INF_ExecData.ExecBlockNo));
	SYS_INF_DataReadCnt = 0;

	page = 1;

	while (1) {
		/**	プリントスタート	*/
		if ( page > 1) {
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
				return ( ret );
			}
		}
		/**	印刷可能行数ｾｯﾄ	*/
		line = (UBYTE)PaperSizeLen();
		if ( (ret = CharacterPrint((UBYTE)(LST_LINE_FEED+prn_mode))) != OK ) {
			return ( ret );
		}
		line--;
		while (1) {
			Prn_Att_Str_Clear(List.S.Print, List.S.Attribute);
			status = ConvertOneLineTextData(List.S.Print);
			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode))) != OK ) {
				return ( ret );
			}
			line--;
			if (status == SYS_INF_READ_CHAR_END) {
				/*　TEXT部とｲﾒｰｼﾞ部の間に一行空行を入れます　*/
				if ( (ret = CharacterPrint((UBYTE)(LST_LINE_FEED))) != OK ) {
					return ( ret );
				}
				line--;
				MEM_ClearPage(&SYS_INF_IndexData);
				/* 印字した行数をセット */
				LST_CharacterLine = (UBYTE)((UBYTE)PaperSizeLen() - line);
				if (line < 20) {	/*　残り行数が20行以下なら、次のページに原稿部を印字する　*/
					if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
						return ( ret );
					}
					if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
						return ( ret );
					}
					LST_CharacterLine = 0;	/* 印字した行数をクリア */
				}
				return ( OK );	/* 原稿部の印字へ　*/
			}
			if (line == 0) {
				break;
			}
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
}

/*************************************************************************
	module		:[メールアドレスリスト]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintMailAddressList(void)
{
	UBYTE 	i;						/*loop*/
	UBYTE 	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE 	line_cnt;				/*残り印刷可能行数*/
	UBYTE 	kind;					/*ｻｰﾁ種類*/
	UBYTE	one_cnt;				/*ﾜﾝﾀｯﾁﾃﾞｰﾀ番号*/
	WORD	ret;					/*実行結果*/

	page = 1;
	one_cnt = 0;

	CMN_MemorySetNULL( Search_str, SYS_INF_USER_NAME_MAX - 1, ' ' );
	if ( CHK_DialListPrint() ) {		/* I:0-6 */
		kind = LST_SEARCH_ASCII;
	}
	else {
		kind = LST_SEARCH_NUMBER;
	}

	one_cnt = MailAddressNextSearch( kind, one_cnt );

	while ( one_cnt < (UBYTE)SYS_ONETOUCH_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

		/*　最初のヘッダー部分を印字します　*/
		if ( (ret = PrintMailAddressListHead(page, &line_cnt)) != OK ) {
			return ( ret );
		}

		/*　データ部分を印字します　*/
		for ( i = 0;; i++ ) {
			if ( line_cnt < 3 ) {
				break;
			}
			if ( page > 1 && i == 0 ) {
				PrintMailAddressListLine( 0, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			else {
				PrintMailAddressListLine( 2, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			line_cnt--;

			if ( (ret = PrintMailAddressListSpecifi(one_cnt)) != OK ) {
				return ( ret );
			}
			line_cnt--;

			one_cnt++;	/* ワンタッチの番号を一つ進める　*/
			one_cnt = MailAddressNextSearch( kind, one_cnt );
			if ( one_cnt >= (UBYTE)SYS_ONETOUCH_MAX ) {
				break;
			}
		}
		PrintMailAddressListLine( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailAddressNextSearch(UBYTE kind, UBYTE one_cnt)
{
	if ( kind == LST_SEARCH_NUMBER ) {
		for ( ; one_cnt < (UBYTE)SYS_ONETOUCH_MAX; one_cnt++ ) {
			if (SYB_INF_OnetouchStatus[one_cnt] == SYS_INF_ONETOUCH_MAILADDRESS) {
				break;
			}
		}
	}
	else {
		one_cnt = MailOnetouchStrEqSearch( one_cnt );
		if ( one_cnt == SYS_ONETOUCH_MAX ) {
			one_cnt = MailOnetouchStrGtSearch();
		}
	}
	return (one_cnt);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailOnetouchStrEqSearch(UBYTE one_cnt)
{
	for ( ; one_cnt < (UBYTE)SYS_ONETOUCH_MAX; one_cnt++ ) {
		if (SYB_INF_OnetouchStatus[one_cnt] == SYS_INF_ONETOUCH_MAILADDRESS) {
			if ( CMN_StringCompare(Search_str,SYB_INF_Onetouch[one_cnt].Name,(UBYTE)(SYS_INF_USER_NAME_MAX - 1)) == STRCMP_EQUAL ) {
				break;
			}
		}
	}
	return (one_cnt);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailOnetouchStrGtSearch(void)
{
	UBYTE	one_pos;
	UBYTE	gt_pnt;		/*GT point*/
	UBYTE	*comp_pt;	/*compear pointer*/
	UBYTE	set_f;		/*comp_pt set flag*/
						/*OFF - > Not set*/
						/*ON  - > Set*/
	gt_pnt = 0xff;
	set_f = OFF;

	for ( one_pos = 0; one_pos < (UBYTE)SYS_ONETOUCH_MAX; one_pos++ ) {
		if (SYB_INF_OnetouchStatus[one_pos] == SYS_INF_ONETOUCH_MAILADDRESS) {
			if ( CMN_StringCompare(Search_str,SYB_INF_Onetouch[one_pos].Name,(UBYTE)(SYS_INF_USER_NAME_MAX - 1)) == STRCMP_LOWER ) {
				if ( set_f == OFF ) {
					comp_pt = SYB_INF_Onetouch[one_pos].Name;
					gt_pnt = one_pos;
					set_f = ON;
				}
				else {
					if ( CMN_StringCompare(comp_pt, SYB_INF_Onetouch[one_pos].Name, (UBYTE)(SYS_INF_USER_NAME_MAX - 1)) == STRCMP_UPPER ) {
						comp_pt = SYB_INF_Onetouch[one_pos].Name;
						gt_pnt = one_pos;
					}
				}
			}
		}
	}
	if ( gt_pnt == 0xff ) {
		one_pos = (UBYTE)SYS_ONETOUCH_MAX;
	}
	else {
		one_pos = gt_pnt;
		CMN_StringCopyNum(Search_str, comp_pt, (WORD)(SYS_INF_USER_NAME_MAX - 1));
		Search_str[SYS_INF_USER_NAME_MAX - 1] = NULL;
	}
	return (one_pos);
}

/*************************************************************************
	module		:[メールアドレスリストのヘッダ印字]
	functiom	:[]
	common		:[]
	condition	:[
		ヘッダ種類
			0->ページ先頭見出し
			1->ページエンド見出し
	]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailAddressListHead(UBYTE page, UBYTE *line_cnt)
{
	WORD	ret;					/*実行結果*/

	ret = OK;

	if ( page == 1 ) {
		/*＊＊　ワンタッチダイヤル　リスト　＊＊*/
		/*　4行空行＋タイトル＋1行空行で6行印字　*/
/*
**	12345678901234567890123456789012345678901234567890123456789012345678901234567890
**	           ＊＊　Ｍａｉｌ　Ａｄｄｒｅｓｓ　Ｄｉｒｅｃｔｏｒｙ　＊＊
*/
		if ( (ret = PrintMailHeadCommon( PWRD_INF_AddressList,  (UBYTE)LST_XXX_TWI_XXX, 12-1 )) != OK ) {
		    return ( ret );
		}
		/*Page 現在時間*/
		if ( (ret = PageTimePrint( page, 2-1, 58-1 )) != OK ) {
			return ( ret );
		}
		/* |￣￣|￣￣￣￣|￣￣￣￣￣￣| */
		PrintMailAddressListLine( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		/* | NO.(4 char)  | Mail Address(50 char)  | Remote Location(20 char)  | */
		PrintMailAddressListLine( 1, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt) -= 9;
	}
	else {
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		/* Page */
		if ( (ret = PagePrint( page, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt) -= 2;
	}
	return ( ret );
}

/*************************************************************************
	module		:[Print Header]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailHeadCommon(CONST UBYTE *PrnString, UBYTE Attribute, UBYTE LocateX )
{
	WORD	ret;

	ret = OK;

	/* ４行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED +4)) != OK ) {
		return ( ret );
	}

	/* タイトル行 */
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[LocateX], (UBYTE *)&List.S.Attribute[LocateX], PrnString, Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	return ( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailAddressListSpecifi( UBYTE one_cnt )
{
	WORD	ret;
	UBYTE	adr_length;
	UBYTE	one_code;

	ret = OK;

	PrintMailAddressListLine( 3, List.S.Print, List.S.Attribute );

	/* オフセットをコードに変換　*/
	one_code = CMN_OffsetToOnetouchCode( one_cnt );
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if ( one_code <= 0x7A ){
		List.S.Print[2-1] = one_code;
	}
	else{
		List.S.Print[2-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
		List.S.Print[3-1] = ( one_code & (UBYTE)0x0F | (UBYTE)0x30 ); /* U1～U8記号をつくる*/
	}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
	List.S.Print[2-1] = '[';
	List.S.Print[5-1] = ']';
	CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(one_code - 0x40), 2, '0' );
 #endif
 #if (PRO_PANEL == KANJI)
	/* ワンタッチの表示　[　]->絵文字 */
	List.S.Print[2-1] = LCD_PICFONT;
	List.S.Print[3-1] = LCD_PICFONT_LOWER;
	CMN_UnsignedIntToASC( &List.S.Print[4-1], (UWORD)(one_code - 0x40), 2, '0' );
 #endif
#endif
	/* Mail address 印字　*/
	adr_length = CMN_StringLength((UBYTE *)SYB_INF_Onetouch[one_cnt].MailAddress);
	CMN_StringCopyNum((UBYTE *)&List.S.Print[7-1],(UBYTE *)SYB_INF_Onetouch[one_cnt].MailAddress, (WORD)adr_length);

	/* Remote Location 印字　*/
	CMN_StringCopy((UBYTE *)&List.S.Print[58-1],(UBYTE *)SYB_INF_Onetouch[one_cnt].Name );

	if ((ret = CharacterPrint( LST_PRINT )) != OK) {
		return (ret);
	}
	return ( ret );
}

/*************************************************************************
	module		:[罫線印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
void	PrintMailAddressListLine(UBYTE Category,	/*罫線種類*/
								 UBYTE *AscString,	/*印刷文字列*/
								 UBYTE *AttString )	/*修飾文字列*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
	case 0:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |￣￣|￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣|￣￣￣￣￣￣￣￣￣￣|
*/
		AscString[1-1] = LST_KLINE7;
		CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );
		AscString[6-1] = LST_KLINE8;
		AscString[57-1] = LST_KLINE8;
		AscString[78-1] = LST_KLINE9;
		break;
	case 1:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |No. |                Mail Address                      |  Remote Location   |
*/
		AscString[1-1] = LST_KLINEI;
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );
		AscString[6-1] = LST_KLINEI;
		AttributeSet( &AscString[23-1], &AttString[23-1], PWRD_INF_Address, LST_NOT );
		AscString[57-1] = LST_KLINEI;
		AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_RemoteLocation, LST_NOT );
		AscString[78-1] = LST_KLINEI;
		break;
	case 2:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** ┣---╋-------------------------------------------------╋-------------------┫
*/
		AscString[1-1] = LST_KLINE4;
		CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );
		AscString[6-1] = LST_KLINE5;
		AscString[57-1] = LST_KLINE5;
		AscString[78-1] = LST_KLINE6;
		break;
	case 3:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |    |                                                  |                    |
*/
		AscString[1-1] = LST_KLINEI;
		AscString[6-1] = LST_KLINEI;
		AscString[57-1] = LST_KLINEI;
		AscString[78-1] = LST_KLINEI;
		break;
	case 4:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |____|__________________________________________________|____________________|
*/
		AscString[1-1] = LST_KLINE1;
		CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );
		AscString[6-1] = LST_KLINE2;
		AscString[57-1] = LST_KLINE2;
		AscString[78-1] = LST_KLINE3;
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[メールグループリスト]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintMailGroupList(void)
{

	UBYTE	i;				/*loop*/
	UBYTE	page;			/*ﾍﾟｰｼﾞ*/
	UBYTE	prg_pos;		/*Pﾜﾝﾀｯﾁﾃﾞｰﾀ番号*/
	UBYTE	line_cnt;		/*残り印刷可能行数*/
	UBYTE	group_line;
	WORD	ret;			/*実行結果*/

	page = 1;
	prg_pos = 0;

	prg_pos = MailGroupNextSearch(prg_pos);
	group_line = MailGroupLineCount(prg_pos);

	while ( prg_pos < (UBYTE)SYS_PROGRAM_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

		/*　最初のヘッダー部分を印字します　*/
		if ( (ret = PrintMailGroupListHead(page, &line_cnt)) != OK ) {
			return ( ret );
		}

		/*　データ部分を印字します　*/
		for ( i = 0;; i++ ) {
			if ( line_cnt < (UBYTE)(group_line + 2) ) {
				break;
			}
			if ( page > 1 && i == 0 ) {
				PrintMailGroupListLine( 0, List.S.Print, List.S.Attribute );
			}
			else {
				PrintMailGroupListLine( 2, List.S.Print, List.S.Attribute );
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line_cnt--;

			if ( (ret = PrintMailGroupListSpecifi(prg_pos,group_line)) != OK ) {
				return ( ret );
			}
			line_cnt -= group_line;

			prg_pos++;	/*　プログラムワンタッチの番号を一つ進めます　*/
			prg_pos = MailGroupNextSearch(prg_pos);
			if ( prg_pos >= (UBYTE)SYS_PROGRAM_MAX ) {
				break;
			}
			group_line = MailGroupLineCount(prg_pos);
		}
		PrintMailGroupListLine( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailGroupNextSearch(UBYTE prg_pos)
{
	for ( ; prg_pos < (UBYTE)SYS_PROGRAM_MAX; prg_pos++ ) {
		if (SYB_INF_ProgramOnetouchStatus[prg_pos] == (UBYTE)SYS_INF_P_ONETOUCH_MAILGROUP) {
			break;
		}
	}
	return (prg_pos);
}

/*************************************************************************
	module		:[メールアドレスリストのヘッダ印字]
	functiom	:[]
	common		:[]
	condition	:[
		ヘッダ種類
			0->ページ先頭見出し
			1->ページエンド見出し
	]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailGroupListHead(UBYTE page, UBYTE *line_cnt)
{
	WORD	ret;					/*実行結果*/

	ret = OK;

	if ( page == 1 ) {
		/*＊＊　ワンタッチダイヤル　リスト　＊＊*/
		/*　4行空行＋タイトル＋1行空行で6行印字　*/
/*
**	12345678901234567890123456789012345678901234567890123456789012345678901234567890
**	              ＊＊　Ｍａｉｌ　Ｇｒｏｕｐ　Ｄｉｒｅｃｔｏｒｙ　＊＊              
*/
		if ( (ret = PrintMailHeadCommon( PWRD_INF_GroupList,  LST_XXX_TWI_XXX, 15-1 )) != OK ) {
		    return ( ret );
		}
		/*Page 現在時間*/
		if ( (ret = PageTimePrint( page, 2-1, 58-1 )) != OK ) {
			return ( ret );
		}
		/* |￣￣|￣￣￣￣￣￣| */
		PrintMailGroupListLine( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		/* | NO.(4 char)  | Mail Group(48 char)  | */
		PrintMailGroupListLine( 1, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt) -= 9;
	}
	else {
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		/* Page */
		if ( (ret = PagePrint( page, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt) -= 2;
	}

	return ( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailGroupLineCount(UBYTE prg_pos)
{
	UBYTE	line;
	UBYTE	chk_pos;
	UBYTE	cnt;
	UBYTE	j,k;

	cnt = 0;
	chk_pos = 0x80;
	for (k = 0; k < SYS_INF_ONETOUCH_POSITION_MAX; k++) {
		for (j = 0; j < 8; j++) {
			if (SYB_INF_MailGroup[prg_pos][k] & (chk_pos >> j)) {
				cnt++;
			}
		}
	}
	line = (cnt / (UBYTE)12);
	if ((cnt % (UBYTE)12) > 0) {
		line += 1;
	}
	return (line);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailGroupListSpecifi(UBYTE prog_cnt, UBYTE group_line)
{
	WORD	ret;
	UBYTE	pos;
	UBYTE	one_pos;
	UBYTE	one_code;
	UBYTE	ptr;
	UBYTE	j;
	UBYTE	chk_chr;
	UBYTE	cnt;
	UBYTE	base;

	ret = OK;
	cnt = 0;

	PrintMailGroupListLine( 3, List.S.Print, List.S.Attribute );

	base = 6;
	/* No. 印字　*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	List.S.Print[(base+1)-1] = 0x50;	/* 'P'のASCIIｺ-ﾄﾞ */
	CMN_UnsignedIntToASC( &List.S.Print[(base+2)-1], (UWORD)(prog_cnt+1), 2, '0' ); /* ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ記号P1～P12をつくる */
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
	List.S.Print[(base+1)-1] = '[';
	List.S.Print[(base+4)-1] = ']';
	CMN_UnsignedIntToASC( &List.S.Print[(base+2)-1], (UWORD)(prog_cnt+73), 2, '0' ); /* ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ記号73～80をつくる */
 #endif
 #if (PRO_PANEL == KANJI)
	/* ワンタッチの表示 []->絵文字 */
	List.S.Print[(base+1)-1] = LCD_PICFONT+3;
	List.S.Print[(base+2)-1] = LCD_PICFONT_LOWER;
	CMN_UnsignedIntToASC( &List.S.Print[(base+3)-1], (UWORD)(prog_cnt+73), 2, '0' ); /* ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ記号73～80をつくる */
 #endif
#endif

/* ANZU_LもPOPLAR_Bもワンタッチの番号を[ ]でくくる
** 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**      |No. | [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] |
*/
	/* Gorup 印字　*/
	chk_chr = 0x80;
	for (pos = 0, ptr = 13; pos < SYS_INF_ONETOUCH_POSITION_MAX; pos++) {
		for (j = 0; j < 8; j++) {
			if (SYB_INF_MailGroup[prog_cnt][pos] & (chk_chr >> j)) {
				one_pos = (j + (pos * (UBYTE)8));
				one_code = CMN_OffsetToOnetouchCode( one_pos );
				cnt++;
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				List.S.Print[ptr-1] = '[';
				ptr++;
				if ( one_code <= 0x7A ){
					List.S.Print[ptr-1] = one_code;
					ptr += 2;
				}
				else{
					List.S.Print[ptr-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
					ptr++;
					List.S.Print[ptr-1] = ( one_code & (UBYTE)0x0F | (UBYTE)0x30 ); /* U1～U8記号をつくる*/
					ptr++;
				}
				List.S.Print[ptr-1] = ']';
				ptr += 2;
 #else	/* PANEL_POPLA_B/L/H */
  #if (PRO_PANEL == ANK)
				List.S.Print[ptr-1] = '[';
				ptr++;
				CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(one_code - 0x40), 2, '0' );
				ptr += 2;
				List.S.Print[ptr-1] = ']';
				ptr += 2;
  #endif
  #if (PRO_PANEL == KANJI)
				/* ワンタッチの表示　[　]->絵文字 */
				List.S.Print[ptr-1] = LCD_PICFONT;
				ptr++;
				List.S.Print[ptr-1] = LCD_PICFONT_LOWER;
				ptr++;
				CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(one_code - 0x40), 2, '0' );
				ptr += 3;
  #endif
 #endif
				if ((cnt == 12) && (group_line > 1)) {
					if ((ret = CharacterPrint( LST_PRINT )) != OK) {
						return (ret);
					}
					cnt = 0;
					group_line--;
					PrintMailGroupListLine( 3, List.S.Print, List.S.Attribute );
					ptr = 13;
				}
			}
		}
	}
	if ((ret = CharacterPrint( LST_PRINT )) != OK) {
		return (ret);
	}
	return ( ret );
}

/*************************************************************************
	module		:[罫線印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
void	PrintMailGroupListLine(
						 UBYTE Category,			/*罫線種類*/
						 register UBYTE *AscString,	/*印刷文字列*/
						 register UBYTE *AttString )/*修飾文字列*/
{
	UBYTE base;

	Prn_Att_Str_Clear( AscString, AttString );
	base = 6;
	switch ( Category ) {
		case 0:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**      |￣￣|￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣~|
*/
			AscString[base-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[(base+1)-1], 66, LST_KLINE_ );
			AscString[(base+5)-1] = LST_KLINE8;
			AscString[(base+67)-1] = LST_KLINE9;
			break;
		case 1:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**      |No. |                       Mail Group                            |
**      |No. |                       ﾒｰﾙ ｸﾞﾙｰﾌﾟ                            |
*/
			AscString[base-1] = LST_KLINEI;
			AttributeSet( &AscString[(base+1)-1], &AttString[(base+1)-1], PWRD_No, LST_NOT );
			AscString[(base+5)-1] = LST_KLINEI;
			AttributeSet( &AscString[(base+29)-1], &AttString[(base+29)-1], PWRD_INF_Group, LST_NOT );
			AscString[(base+67)-1] = LST_KLINEI;
			break;
		case 2:
			/* ┣ ━ ╋ ━ ┫*/
			AscString[base-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[(base+1)-1], 67, LST_KLINE_ );
			AscString[(base+5)-1] = LST_KLINE5;
			AscString[(base+67)-1] = LST_KLINE6;
			break;
		case 3:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**      |    |                                                             |
*/
			AscString[base-1] = LST_KLINEI;
			AscString[(base+5)-1] = LST_KLINEI;
			AscString[(base+67)-1] = LST_KLINEI;
			break;
		case 4:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**      |____|_____________________________________________________________|
*/
			AscString[base-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[(base+1)-1], 67, LST_KLINE_ );
			AscString[(base+5)-1] = LST_KLINE2;
			AscString[(base+67)-1] = LST_KLINE3;
			break;
	}
}


/*************************************************************************
	module		:[ユーザー設定リスト]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintMailSettingList(void)
{
	UBYTE 	page;			/*ﾍﾟｰｼﾞ*/
	UBYTE 	status;
	UBYTE 	line_cnt;		/*残り印刷可能行数*/
	UBYTE 	i;
	UBYTE	user_no;
	WORD	ret;			/*実行結果*/

	ret = OK;
	page = 1;
	line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

	user_no = (UBYTE)SYS_DocumentPrintNo;
	status = TRUE;
	i = 0;
	while (status == TRUE) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		/*　最初のヘッダー部分を印字します　*/
		if ( (ret = PrintMailSettingListHead(page, &line_cnt)) != OK ) {
			return ( ret );
		}
		/* |￣￣|￣￣￣￣￣￣￣￣￣￣| */
		PrintMailSettingListLine( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;
		/*　データ部分を印字します　*/
		for ( ;line_cnt > 1; i++ ) {
			if ( (i == 6) || (i == 7) || (i == 9) || (i == 15)
				 || (i == 16) || (i == 17) || (i == 18) ) {
				continue;	/* 上記の項目は現在リストに表示されないのでスキップする */
			}
			if (!(SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_RX_ON)) {
				if ( (i == 21) || (i == 22) || (i == 23) || (i == 24)
					 || (i == 25) || (i == 26) ) {
					continue;	/* このの項目は自動受信ＯＦＦの時はスキップする */
				}
			}
			if (!(SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_DOWNLOAD_ON)) {
				if ( (i == 25) || (i == 26) ) {
					continue;	/* この項目は自動ﾀﾞｳﾝﾛｰﾄﾞＯＦＦの時はスキップする */
				}
			}
			if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_PRINT_ON) {
				if ( i == 26) {
					continue;	/* この項目は自動プリントＯＮの時はスキップする */
				}
			}
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			PrintMailSettingListLine( 1, List.S.Print, List.S.Attribute );
			status = PrintMailSettingListSpecifi( i,user_no, List.S.Print, List.S.Attribute );
			if (status == FALSE) {
				break;
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line_cnt--;
		}
		PrintMailSettingListLine( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return (MSG_PRN_LST_END);

}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailSettingListHead(UBYTE page, UBYTE *line_cnt)
{
	WORD	ret;					/*実行結果*/

	ret = OK;

	if ( page == 1 ) {
		/*＊＊　ワンタッチダイヤル　リスト　＊＊*/
		/*　4行空行＋タイトル＋1行空行で6行印字　*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
/*
**	12345678901234567890123456789012345678901234567890123456789012345678901234567890
**	                  　　　＊＊　ユーザー設定　リスト　＊＊                 
*/
		if ( (ret = PrintMailHeadCommon( PWRD_INF_SettingList_K,  LST_NOT, 18-1 )) != OK ) {
		    return ( ret );
		}
#else
/*
**	12345678901234567890123456789012345678901234567890123456789012345678901234567890
**	                 ＊＊　Ｕｓｅｒ　Ｓｅｔｔｉｎｇ　Ｌｉｓｔ　＊＊                 
*/
		if ( (ret = PrintMailHeadCommon( PWRD_INF_SettingList,  LST_XXX_TWI_XXX, 18-1 )) != OK ) {
		    return ( ret );
		}
#endif
		(*line_cnt) -= 6;

		/*Page 現在時間*/
		if ( (ret = PageTimePrint( page, 2-1, 58-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	else {
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		/* Page */
		if ( (ret = PagePrint( page, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}

	return ( ret );
}

/*************************************************************************
	module		:[罫線印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
void	PrintMailSettingListLine(
						 	UBYTE Category,			/*罫線種類*/
						 	UBYTE *AscString,	/*印刷文字列*/
						 	UBYTE *AttString )/*修飾文字列*/
{

	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**  ____________________________________________________________________________
** |                         |                                                  |
*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );
			AscString[27-1] = LST_KLINE8;
			AscString[78-1] = LST_KLINE9;
			break;
		case 1:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |                         |                                                  |
*/
			AscString[1-1] = LST_KLINEI;
			AscString[27-1] = LST_KLINEI;
			AscString[78-1] = LST_KLINEI;
			break;
		case 2:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
** |_________________________|__________________________________________________|
*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );
			AscString[27-1] = LST_KLINE2;
			AscString[78-1] = LST_KLINE3;
			break;
	}
}

/*************************************************************************
	module		:[設定内容印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	PrintMailSettingListSpecifi(UBYTE kind,
									UBYTE user_no,
									UBYTE *AscString,
									UBYTE *AttString )
{
	UBYTE	status;
	UWORD	time;

	status = TRUE;

	switch (kind) {
	case 0:	/*　ユーザー名の印字　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_UserName, LST_NOT );
		if (SYB_INF_UserData[user_no].UserName[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].UserName);
		}
		break;
	case 1:	/*　ISP名　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_ProviderName, LST_NOT );
		if (SYB_INF_UserData[user_no].ISP_Name[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].ISP_Name);
		}
		break;
	case 2:	/*　1st ISP電話番号の印字　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AccessPoint1, LST_NOT );
		if (SYB_INF_UserData[user_no].TelNumber[0][0] == 0xff) {
			AscString[28-1] = '-';
		}
		else {
			CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[0][0] );
			CMN_StringCopy( &List.S.Print[28-1], List.S.Work );
		}
		break;
	case 3:	/*　2nd ISP電話番号の印字　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AccessPoint2, LST_NOT );
		if (SYB_INF_UserData[user_no].TelNumber[1][0] == 0xff) {
			AscString[28-1] = '-';
		}
		else {
			CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[1][0] );
			CMN_StringCopy( &List.S.Print[28-1], List.S.Work );
		}
		break;
	case 4:	/*　3rd ISP電話番号の印字　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AccessPoint3, LST_NOT );
		if (SYB_INF_UserData[user_no].TelNumber[2][0] == 0xff) {
			AscString[28-1] = '-';
		}
		else {
			CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[2][0] );
			CMN_StringCopy( &List.S.Print[28-1], List.S.Work );
		}
		break;
	case 5:	/*　ＰＰＰログインＩＤ　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_PPPLoginID, LST_NOT );
		if (SYB_INF_UserData[user_no].PPP_LoginID[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].PPP_LoginID);
		}
		break;
	case 6:	/*　ＰＰＰパスワード　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_PPPPassword, LST_NOT );
		if (SYB_INF_UserData[user_no].PPP_Password[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_MemorySet(&AscString[28-1], 10, '*');
		}
		break;
	case 7:	/*　ＰＰＰ認証方式　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_PPPAuth, LST_NOT );
		if (SYB_INF_UserData[user_no].PPP_Authentication == SYS_INF_PPP_AUTH_PAP) {
			AscString[28-1] = 'P';
			AscString[29-1] = 'A';
			AscString[30-1] = 'P';
		}
		else if (SYB_INF_UserData[user_no].PPP_Authentication == SYS_INF_PPP_AUTH_CHAP) {
			AscString[28-1] = 'C';
			AscString[29-1] = 'H';
			AscString[30-1] = 'A';
			AscString[31-1] = 'P';
		}
		else {
			AscString[28-1] = 'N';
			AscString[29-1] = 'O';
			AscString[30-1] = 'N';
			AscString[31-1] = 'E';
		}
		break;
	case 8:	/*　ＰＯＰログインＩＤ　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_POPLoginID, LST_NOT );
		if (SYB_INF_UserData[user_no].POP_LoginID[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].POP_LoginID);
		}
		break;
	case 9:	/*　ＰＯＰパスワード　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_POPPassword, LST_NOT );
		if (SYB_INF_UserData[user_no].POP_Password[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_MemorySet(&AscString[28-1], 10, '*');
		}
		break;
	case 10:	/* メールアドレス　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_MailAddress, LST_NOT );
		if (SYB_INF_UserData[user_no].ISP_Name[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].MailAddress);
		}
		break;
	case 11:	/* POP Server */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_POPServer, LST_NOT );
		if (SYB_INF_UserData[user_no].POP_Server[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].POP_Server);
		}
		break;
	case 12:	/* SMTP Server */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_SMTPServer, LST_NOT );
		if (SYB_INF_UserData[user_no].POP_Server[0] == NULL) {
			AscString[28-1] = '-';
		}
		else {
			CMN_StringCopy(&AscString[28-1], (UBYTE *)SYB_INF_UserData[user_no].SMTP_Server);
		}
		break;
	case 13:	/* Primary DNS Server */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_PriDNSServer, LST_NOT );
		CMN_UnsignedIntToASC(&AscString[28-1],(UWORD)SYB_INF_UserData[user_no].Primary_DNS_Server[0],3,'0');
		AscString[31-1] = '.';
		CMN_UnsignedIntToASC(&AscString[32-1],(UWORD)SYB_INF_UserData[user_no].Primary_DNS_Server[1],3,'0');
		AscString[35-1] = '.';
		CMN_UnsignedIntToASC(&AscString[36-1],(UWORD)SYB_INF_UserData[user_no].Primary_DNS_Server[2],3,'0');
		AscString[39-1] = '.';
		CMN_UnsignedIntToASC(&AscString[40-1],(UWORD)SYB_INF_UserData[user_no].Primary_DNS_Server[3],3,'0');
		break;
	case 14:	/* Secondary DNS Server */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_SecDNSServer, LST_NOT );
		CMN_UnsignedIntToASC(&AscString[28-1],(UWORD)SYB_INF_UserData[user_no].Secondary_DNS_Server[0],3,'0');
		AscString[31-1] = '.';
		CMN_UnsignedIntToASC(&AscString[32-1],(UWORD)SYB_INF_UserData[user_no].Secondary_DNS_Server[1],3,'0');
		AscString[35-1] = '.';
		CMN_UnsignedIntToASC(&AscString[36-1],(UWORD)SYB_INF_UserData[user_no].Secondary_DNS_Server[2],3,'0');
		AscString[39-1] = '.';
		CMN_UnsignedIntToASC(&AscString[40-1],(UWORD)SYB_INF_UserData[user_no].Secondary_DNS_Server[3],3,'0');
		break;
	case 15:	/* IPアドレス　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_ClientAddress, LST_NOT );
		CMN_UnsignedIntToASC(&AscString[28-1],(UBYTE)SYB_INF_UserData[user_no].IP_Address[0],3,'0');
		AscString[31-1] = '.';
		CMN_UnsignedIntToASC(&AscString[32-1],(UBYTE)SYB_INF_UserData[user_no].IP_Address[1],3,'0');
		AscString[35-1] = '.';
		CMN_UnsignedIntToASC(&AscString[36-1],(UBYTE)SYB_INF_UserData[user_no].IP_Address[2],3,'0');
		AscString[39-1] = '.';
		CMN_UnsignedIntToASC(&AscString[40-1],(UBYTE)SYB_INF_UserData[user_no].IP_Address[3],3,'0');
		break;
	case 16:	/* ISPアドレス　*/
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_ServerAddress, LST_NOT );
		CMN_UnsignedIntToASC(&AscString[28-1],(UBYTE)SYB_INF_UserData[user_no].ISP_ServerAddress[0],3,'0');
		AscString[31-1] = '.';
		CMN_UnsignedIntToASC(&AscString[32-1],(UBYTE)SYB_INF_UserData[user_no].ISP_ServerAddress[1],3,'0');
		AscString[35-1] = '.';
		CMN_UnsignedIntToASC(&AscString[36-1],(UBYTE)SYB_INF_UserData[user_no].ISP_ServerAddress[2],3,'0');
		AscString[39-1] = '.';
		CMN_UnsignedIntToASC(&AscString[40-1],(UBYTE)SYB_INF_UserData[user_no].ISP_ServerAddress[3],3,'0');
		break;
	case 17:	/* Gateway Address */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_GatewayAddress, LST_NOT );
		CMN_UnsignedIntToASC(&AscString[28-1],(UWORD)SYB_INF_UserData[user_no].GatewayAddress[0],3,'0');
		AscString[31-1] = '.';
		CMN_UnsignedIntToASC(&AscString[32-1],(UWORD)SYB_INF_UserData[user_no].GatewayAddress[1],3,'0');
		AscString[35-1] = '.';
		CMN_UnsignedIntToASC(&AscString[36-1],(UWORD)SYB_INF_UserData[user_no].GatewayAddress[2],3,'0');
		AscString[39-1] = '.';
		CMN_UnsignedIntToASC(&AscString[40-1],(UWORD)SYB_INF_UserData[user_no].GatewayAddress[3],3,'0');
		break;
	case 18:	/* TxRx */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_TxRx, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_TXRX_ON) {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_On, LST_NOT );
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Off, LST_NOT );
		}
		break;
	case 19:	/* Delete Mail */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_DeleteMail, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_DELETE_ON) {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_On, LST_NOT );
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Off, LST_NOT );
		}
		break;
	case 20:	/* Auto Check Mail */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AutoCheck, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_RX_ON) {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_On, LST_NOT );
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Off, LST_NOT );
		}
		break;
	case 21:	/* Start Time */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_StartTime, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_RX_ON) {
			time = (UWORD)(SYB_INF_UserData[user_no].StartTime / 60);
			CMN_UnsignedIntToASC(&AscString[28-1],time,2,'0');
			AscString[30-1] = ':';
			time = (UWORD)(SYB_INF_UserData[user_no].StartTime % 60);
			CMN_UnsignedIntToASC(&AscString[31-1],time,2,'0');
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_NotTime, LST_NOT );
		}
		break;
	case 22:	/* End Time */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_EndTime, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_RX_ON) {
			time = (UWORD)(SYB_INF_UserData[user_no].EndTime / 60);
			CMN_UnsignedIntToASC(&AscString[28-1],time,2,'0');
			AscString[30-1] = ':';
			time = (UWORD)(SYB_INF_UserData[user_no].EndTime % 60);
			CMN_UnsignedIntToASC(&AscString[31-1],time,2,'0');
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_NotTime, LST_NOT );
		}
		break;
	case 23:	/* Interval Time */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_IntervalTime, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_RX_ON) {
			time = (UWORD)(SYB_INF_UserData[user_no].IntervalTime / 60);
			CMN_UnsignedIntToASC(&AscString[28-1],time,2,'0');
			AscString[30-1] = ':';
			time = (UWORD)(SYB_INF_UserData[user_no].IntervalTime % 60);
			CMN_UnsignedIntToASC(&AscString[31-1],time,2,'0');
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_NotTime, LST_NOT );
		}
		break;
	case 24:	/* Download */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AutoDownLoad, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_DOWNLOAD_ON) {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_On, LST_NOT );
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Off, LST_NOT );
		}
		break;
	case 25:	/* Auto Print Mail */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_AutoPrint, LST_NOT );
		if (SYB_INF_UserData[user_no].OptionalSetting & SYS_INF_AUTO_PRINT_ON) {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_On, LST_NOT );
		}
		else {
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Off, LST_NOT );
		}
		break;
	case 26:	/* Hold Time */
		AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_INF_HoldTime, LST_NOT );
		time = (UWORD)(SYB_INF_UserData[user_no].HoldTime / 1440);
		CMN_UnsignedIntToASC(&AscString[28-1],time,2,'0');
		break;
	default:
		status = FALSE;
		break;
	}

	return (status);
}

/*************************************************************************
	module		:[通信予約消去通知]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/23]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintErasedCommandNotice(void)
{
	WORD			ret;

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* 4CR */
	if ((ret = CharacterPrint( LST_LINE_FEED +4)) != OK) {
		return ( ret );
	}

	/* ** Erased Commands ** */
	Prn_Att_Str_Clear((UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
	AttributeSet((UBYTE *)&List.S.Print[15-1],(UBYTE *)&List.S.Attribute[15-1],PWRD_INF_ErasedCommand_K ,LST_NOT );
#else
	AttributeSet((UBYTE *)&List.S.Print[15-1],(UBYTE *)&List.S.Attribute[15-1],PWRD_INF_ErasedCommand ,LST_XXX_TWI_XXX );
#endif

	if ((ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}

	/* 2CR */
	if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
		return ( ret );
	}

	/* Current Time */
	if ((ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}

	/* 1CR */
	if ((ret = CharacterPrint(LST_LINE_FEED + 1)) != OK ) {
		return ( ret );
	}

	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute);
	CMN_StringCopy((UBYTE *)&List.S.Print[10],PWRD_INF_ComsWereErased);
	if ((ret = CharacterPrint( LST_PRINT )) != OK) {
		return ( ret );
	}

	if ((ret = CharacterPrint( LST_CLOSE )) != OK) {
		return ( ret );
	}

	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintMailCommandList(void)
{
	WORD	ret;
	UBYTE	user_no;
	UBYTE	cmd_no;
	UBYTE	cmd_line;
	UBYTE 	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE 	line_cnt;				/*残り印刷可能行数*/
	UBYTE 	i;

	page = 1;
	cmd_no = 0;
	ret = OK;

	user_no = (UBYTE)SYS_DocumentPrintNo;
	cmd_no = MailCommandNextSearch(user_no, cmd_no);
	/* コマンド内容を何行で印字できるかを調べる　*/
	cmd_line = GetMailCommandSpecific(cmd_no);

	while ( cmd_no < (UBYTE)SYS_INF_MAIL_COM_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/
		/*　最初のヘッダー部分を印字します　*/
		if ( (ret = PrintMailComListHead(page, &line_cnt, user_no)) != OK ) {
			return ( ret );
		}
		/*　データ部分を印字します　*/
		for (i = 0; ; i++) {
			if ( line_cnt < (cmd_line + (UBYTE)1) ) {
				break;
			}
			if ( (ret = PrintMailComListSpecifi(cmd_no, &line_cnt, cmd_line)) != OK ) {
				return ( ret );
			}
			cmd_no++;	/*　コマンド番号を一つ進めます　*/
			cmd_no = MailCommandNextSearch(user_no, cmd_no);
			cmd_line = GetMailCommandSpecific(cmd_no);
			if ( cmd_no >= (UBYTE)SYS_INF_MAIL_COM_MAX ) {
				break;
			}
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[通信予約リストのヘッダ印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailComListHead(UBYTE page, UBYTE *line_cnt, UBYTE user_no)
{
	WORD	ret;					/*実行結果*/

	ret = OK;

	if ( page == 1 ) {
		/*　4行空行＋タイトル＋1行空行で6行印字　*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
		if ( (ret = PrintMailHeadCommon( PWRD_INF_MailComList,  LST_NOT, 13-1 )) != OK ) {
		    return ( ret );
		}
#else
		if ( (ret = PrintMailHeadCommon( PWRD_INF_MailComList,  LST_XXX_TWI_XXX, 13-1 )) != OK ) {
		    return ( ret );
		}
#endif
		*line_cnt -= 6;

		/*Page 現在時間*/
		if ( (ret = PageTimePrint( page, 2-1, 58-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

		/* ユーザー名の印字　*/
		if ( (ret = PrintMailComUserName(user_no , 2-1)) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

	/* タイトル行の印字
	** 0        1         2         3         4         5         6         7         8
	** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
	** No. Start Time    Kind     Send To
	** -----------------------------------------------------------------------------
	** 00  00/00 00:00   Tx Mail  abcdefgh@abcdefg.hijk.lmn
	**                            [01][02][03][04][05][06][07][08][09][10][12]
	*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		CMN_StringCopy(&List.S.Print[1-1],PWRD_No);
		CMN_StringCopy(&List.S.Print[5-1],PWRD_Start);
		CMN_StringCopy(&List.S.Print[19-1],PWRD_INF_Kind);
		CMN_StringCopy(&List.S.Print[28-1],PWRD_INF_To);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	else {
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

		/* Page */
		if ( (ret = PagePrint( page, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;

		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}

	return ( ret );
}

/*************************************************************************
	module		:[ユーザー名を印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailComUserName(UBYTE user_no, UBYTE name_pos)
{
	UBYTE	length;

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	length = CMN_StringLength(PWRD_INF_User);
	CMN_StringCopy( &List.S.Print[name_pos], PWRD_INF_User );

	if (SYB_INF_UserData[user_no].UserName[0] != NULL) {
		CMN_StringCopy(&List.S.Print[name_pos+length], SYB_INF_UserData[user_no].UserName);
	}
	else {
		CMN_StringCopy(&List.S.Print[name_pos+length], SYB_INF_UserData[user_no].MailAddress);
	}

	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[次に印字するコマンド番号を取得]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	MailCommandNextSearch(UBYTE user_no, UBYTE cmd_no)
{
	for ( ;cmd_no < SYS_INF_MAIL_COM_MAX ; cmd_no++) {
		if ( ( (SYS_INF_MailCommand[cmd_no].Status == SYS_INF_MAIL_CMD_WAITING)
			   || (SYS_INF_MailCommand[cmd_no].Status == SYS_INF_MAIL_CMD_EXECUTE) )
			&& (SYS_INF_MailCommand[cmd_no].UserNumber == user_no) ) {
			return (cmd_no);
		}
	}
	return (cmd_no);
}

/*************************************************************************
	module		:[次に印字するコマンド番号を取得]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	GetMailCommandSpecific(UBYTE cmd_no)
{
	UBYTE line_cnt;
	UBYTE addr_cnt;
	UBYTE i,j;
	UBYTE chk_chr;
	
	line_cnt = 0;
	addr_cnt = 0;

	if (cmd_no >= (UBYTE)SYS_INF_MAIL_COM_MAX) {
		return (line_cnt);
	}
	chk_chr = 0x80;
	if ((SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TX)
		|| (SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TXRX)) {
		for (i = 0; i < SYS_INF_MAIL_DIRECT_COUNT_MAX; i ++) {
			if (SYS_INF_MailCommand[cmd_no].Direct[i][0] == NULL) {
				break;
			}
			line_cnt++;
		}
		for (i = 0; i < SYS_INF_ONETOUCH_POSITION_MAX; i++) {
			for (j = 0; j < 8; j++) {
				if (SYS_INF_MailCommand[cmd_no].Onetouch[i] & (chk_chr >> j)) {
					addr_cnt++;
				}
			}
		}
		if ((addr_cnt % 12) == 0) {
			line_cnt += (addr_cnt / 12);
		}
		else {
			line_cnt += ((addr_cnt / 12) + 1);
		}
	}
	else {
		line_cnt = 1;
	}
	return (line_cnt);
}

/*************************************************************************
	module		:[コマンドの詳細]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailComListSpecifi(UBYTE cmd_no, UBYTE *line_cnt, UBYTE cmd_line)
{
	UBYTE i,j;
	UBYTE chk_chr;
	UBYTE one_pos;
	UBYTE ptr;
	WORD  ret;

	ret = OK;

	/* 横罫線の印字　*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySet( &List.S.Print[1-1], 77, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	/* コマンドの内容を印字
	** 0        1         2         3         4         5         6         7         8
	** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
	** No. Start Time    Kind     Send To
	** -----------------------------------------------------------------------------
	** 00  00/00 00:00   Tx       abcdefgh@abcdefg.hijk.lmn
	**                            [01][02][03][04][05][06][07][08][09][10][12]
	*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_UnsignedIntToASC( &List.S.Print[1-1], (UWORD)cmd_no, 2,'0');
	CriterionMinuteToDayTimeAsc( SYS_INF_MailCommand[cmd_no].ExecTime/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[5-1], List.S.Work );
	if ((SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TX)
		|| (SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TXRX)) {
		CMN_StringCopy( &List.S.Print[19-1], PWRD_INF_Tx );

		for (i = 0; i < SYS_INF_MAIL_DIRECT_COUNT_MAX; i++) {
			if (SYS_INF_MailCommand[cmd_no].Direct[i][0] != NULL) {
				CMN_StringCopy( &List.S.Print[28-1], &SYS_INF_MailCommand[cmd_no].Direct[i][0] );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				(*line_cnt)--;
				cmd_line--;
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			}
		}
		chk_chr = 0x80;
		for (i = 0,ptr = 28; i < SYS_INF_ONETOUCH_POSITION_MAX; i++) {
			for (j = 0; j < 8; j++) {
				if (SYS_INF_MailCommand[cmd_no].Onetouch[i] & (chk_chr >> j)) {
					one_pos = (j + (i * (UBYTE)8));
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
					List.S.Print[ptr-1] = '[';
					ptr++;
					if ( CMN_OffsetToOnetouchCode( one_pos ) <= 0x7A ){
						List.S.Print[ptr-1] = CMN_OffsetToOnetouchCode( one_pos );
						ptr += 2;
					}
					else{
						List.S.Print[ptr-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
						ptr++;
						List.S.Print[ptr-1] = CMN_OffsetToOnetouchCode( one_pos ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1～U8記号をつくる*/
						ptr++;
					}
					List.S.Print[ptr-1] = ']';
					ptr ++;
 #else	/* PANEL_POPLA_B/L/H */
   #if (PRO_PANEL == ANK)
					List.S.Print[ptr-1] = '[';
					ptr++;
					CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(CMN_OffsetToOnetouchCode( one_pos ) - 0x40), 2, '0' );
					ptr += 2;
					List.S.Print[ptr-1] = ']';
					ptr ++;
   #endif
   #if (PRO_PANEL == KANJI)
					/* ワンタッチの表示　[　]->絵文字 */
					List.S.Print[ptr-1] = LCD_PICFONT;
					ptr++;
					List.S.Print[ptr-1] = LCD_PICFONT_LOWER;
					ptr++;
					CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(CMN_OffsetToOnetouchCode( one_pos ) - 0x40), 2, '0' );
					ptr += 2;
   #endif
 #endif
					if (( ptr >= 72 ) && (cmd_line > 0)) {
						if ((ret = CharacterPrint( LST_PRINT )) != OK) {
							return (ret);
						}
						(*line_cnt)--;
						cmd_line--;
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						ptr = 28;
					}
				}
			}
		}
		if (cmd_line > 0) {
			if ((ret = CharacterPrint( LST_PRINT )) != OK) {
				return (ret);
			}
			(*line_cnt)--;
			cmd_line--;
		}
	}
	else {
		CMN_StringCopy( &List.S.Print[19-1], PWRD_INF_Rx );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	return (ret);
}

/*************************************************************************
	module		:[受信メール消去通知]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintErasedRxMailNotice(void)
{
	WORD	ret;
	UBYTE	user_no;
	UBYTE	page;

	page = 1;
	user_no = (UBYTE)SYS_DocumentPrintNo;

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}
	/*　最初のヘッダー部分を印字します　*/
	/*　4行空行＋タイトル＋1行空行で6行印字　*/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
	if ( (ret = PrintMailHeadCommon( PWRD_INF_ErasedMailList_K,  LST_NOT, 23-1 )) != OK ) {
	    return ( ret );
	}
#else
	if ( (ret = PrintMailHeadCommon( PWRD_INF_ErasedMailList,  LST_XXX_TWI_XXX, 13-1 )) != OK ) {
	    return ( ret );
	}
#endif
	/* 1行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	/* Current Time */
	if ((ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}
	/* １行空行 */
	if ((ret = CharacterPrint(LST_LINE_FEED + 1)) != OK ) {
		return ( ret );
	}
	/* 受信者名の印字　*/
	if ( (ret = PrintMailReceiverName(user_no , 10-1)) != OK ) {
		return ( ret );
	}
	/* １行空行 */
	if ((ret = CharacterPrint(LST_LINE_FEED + 1)) != OK ) {
		return ( ret );
	}
	Prn_Att_Str_Clear(List.S.Print, List.S.Attribute);
	CMN_StringCopy(&List.S.Print[12-1],PWRD_INF_MailsWereErased);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[ユーザー名を印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailReceiverName(UBYTE user_no, UBYTE name_pos)
{
	UBYTE	length;

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	length = CMN_StringLength(PWRD_INF_Receiver);
	CMN_StringCopy( &List.S.Print[name_pos], PWRD_INF_Receiver );

	if (SYB_INF_UserData[user_no].UserName[0] != NULL) {
		CMN_StringCopy(&List.S.Print[name_pos+length], SYB_INF_UserData[user_no].UserName);
	}
	else {
		CMN_StringCopy(&List.S.Print[name_pos+length], SYB_INF_UserData[user_no].MailAddress);
	}

	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[ﾁｪｯｸﾒｯｾｰｼﾞﾌﾟﾘﾝﾄ]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[
		1枚の紙に書けることを前提にしているので
		異様に小さい紙をサポートしている機種の時は
		改ページの処理を入れる必要がある。
	]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintMailComCheckMsg(void)
{
	WORD	ret;
	UBYTE	cmd_no;
	UBYTE	line_cnt;
	UBYTE	page;
	UBYTE	opt_line;

	cmd_no = (UBYTE)SYS_DocumentPrintNo;

	page = 1;
	opt_line = 0;

	while(1) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/
		/*　最初のヘッダー部分を印字します　*/
		if ((ret = PrintMailCheckMsgHead(cmd_no, &line_cnt, page)) != OK) {
			return ( ret );
		}
		/*　最初のタイトル部分を印字します　*/
		if ((ret = PrintMailCheckMsgTitle(&line_cnt)) != OK) {
			return ( ret );
		}
		/*　メッセージ本体を印字します　*/
		if ( (ret = PrintMailCheckMsgSpecifi(cmd_no)) != OK ) {
			return ( ret );
		}
		line_cnt -= 3;
		if (line_cnt < 4) {
			page++;
			if ( (ret = MailComCheckMsgChangePage( cmd_no, &line_cnt, page )) != OK ) {
				return ( ret );
			}
		}
		/*　メッセージのオプションデータを印字します　*/
		if ( (ret = PrintMailCheckMsgOption(cmd_no, &line_cnt, page)) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		break;	/* PRINT END */
	}

	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailCheckMsgHead(UBYTE cmd_no, UBYTE *line_cnt, UBYTE page)
{
	WORD ret;

	ret = OK;

	if (page <= 1) {
		/* ４行改行 */
		if ((ret = CharacterPrint( LST_LINE_FEED + 4)) != OK) {
			return ( ret );
		}
		*line_cnt -= 4;
		Prn_Att_Str_Clear(List.S.Print, List.S.Attribute);
		List.S.Print[25-1] = LST_KLINE7;
		CMN_MemorySet(&List.S.Print[26-1], 30, LST_KLINE_ );
		List.S.Print[56-1] = LST_KLINE9;
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		/* 8901234567890123456789012345678901234567890123
		** |         Ｃｈｅｃｋ　Ｍｅｓｓａｇｅ         |
		** |            チェック　メッセージ            |
		*/
		Prn_Att_Str_Clear(List.S.Print, List.S.Attribute );
		List.S.Print[25-1] = LST_KLINEI;
	#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet(&List.S.Print[28-1], &List.S.Attribute[28-1], PWRD_CheckMessage_K, LST_NOT );
	#else
		AttributeSet(&List.S.Print[28-1], &List.S.Attribute[28-1], PWRD_CheckMessage, LST_XXX_TWI_XXX );
	#endif
		List.S.Print[56-1] = LST_KLINEI;
		if ((ret = CharacterPrint(LST_PRINT)) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		/*------------------------------*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[25-1] = LST_KLINE1;
		CMN_MemorySet( &List.S.Print[26-1], 30, LST_KLINE_ );
		List.S.Print[56-1] = LST_KLINE3;
		if ( (ret = CharacterPrint(LST_PRINT)) != OK) {
			return ( ret );
		}
		(*line_cnt)--;
	}

	/*１行印字（改行）*/
	if ((ret = CharacterPrint(LST_LINE_FEED)) != OK) {
		return (ret);
	}
	(*line_cnt)--;

	if (page <= 1) {
		/*Page 現在時間*/
		if ( (ret = PageTimePrint( page, 2-1, 58-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		/*１行印字（改行）*/
		if ((ret = CharacterPrint(LST_LINE_FEED)) != OK) {
			return (ret);
		}
		(*line_cnt)--;
		/* ユーザー名の印字　*/
		if ( (ret = PrintMailComUserName(SYS_INF_MailCommand[cmd_no].UserNumber, 2-1)) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	else {
		/* Page */
		if ( (ret = PagePrint( page, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	/* 1行印字（改行）*/
	if ((ret = CharacterPrint(LST_LINE_FEED)) != OK) {
		return (ret);
	}
	(*line_cnt)--;

	return (ret);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailCheckMsgTitle(UBYTE *line_cnt)
{
	WORD ret;
	UBYTE base;
	ret = OK;

	base = 6;

	/* 0        1         2         3         4         5         6         7         8
	** 12345678901234567890123456789012345678901234567890123456789012345678901234567890/
	**      ErrorCode     Note                         Kind    Start
	**      ---------------------------------------------------------------
	**      0101          Repeat transmission.         Tx      00/00 00:00
	*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
	CMN_StringCopy(&List.S.Print[base-1], PWRD_INF_ErrorCode);
	CMN_StringCopy(&List.S.Print[base+14-1], PWRD_Note);
	CMN_StringCopy(&List.S.Print[base+43-1], PWRD_INF_Kind);
	CMN_StringCopy(&List.S.Print[base+51-1], PWRD_Start);
	if ( (ret = CharacterPrint(LST_PRINT)) != OK) {
		return ( ret );
	}
	(*line_cnt)--;

	Prn_Att_Str_Clear(List.S.Print, List.S.Attribute);
	CMN_MemorySet(&List.S.Print[base-1], 63, LST_KLINE_ );
	if ( (ret = CharacterPrint(LST_PRINT)) != OK) {
		return ( ret );
	}
	(*line_cnt)--;
	return (ret);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	MailComCheckMsgChangePage( UBYTE cmd_no, UBYTE *line_cnt, UBYTE page )
{
	WORD	ret;
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}
	(*line_cnt) = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/
	if ((ret = PrintMailCheckMsgHead(cmd_no, line_cnt, page)) != OK) {
		return ( ret );
	}
	return (ret);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailCheckMsgSpecifi(UBYTE cmd_no)
{
	UBYTE base;
	UWORD err_code;
	WORD ret;

	base = 6;

	/*変更 1998/08/18 Eguchi */
	/*まだまだ暫定処理です。ｴﾗｰｺｰﾄﾞが確定したらもう少しましに作り直す*//*FOR DEBUG*/
	switch (SYS_INF_MailCommand[cmd_no].Result) {
	case SYS_INF_RESULT_COM_ERR:
		err_code = 1;
		break;

	case SYS_INF_RESULT_COM_ILL_ERR:
		err_code = 2;
		break;

	case SYS_INF_RESULT_ABORT:
		err_code = 3;
		break;

	case SYS_INF_RESULT_POWEROFF:
		err_code = 4;
		break;

	case SYS_INF_RESULT_DIALBUSY:
		err_code = 101;
		break;
	case SYS_INF_RESULT_NODIALTONE:
		err_code = 102;
		break;
	case SYS_INF_RESULT_NOCARRIER:
		err_code = 103;
		break;
	case SYS_INF_RESULT_DIALTIMEOUT:
		err_code = 104;
		break;
	case SYS_INF_RESULT_RX_ONLY:
		err_code = 105;
		break;
	case SYS_INF_RESULT_NOPSTNNUMBER:
		err_code = 106;
		break;
	case SYS_INF_RESULT_PPPAUTHERR:
		err_code = 201;;
		break;
	case SYS_INF_RESULT_PPPNEGOERR:
		err_code = 202;
		break;
	case SYS_INF_RESULT_PPP_NO_RES:
		err_code = 203;
		break;

	case SYS_INF_RESULT_PPP_DOWN:
		err_code = 204;
		break;
	case SYS_INF_RESULT_PPP_ERR:
		err_code = 205;
		break;
	case SYS_INF_RESULT_NO_DNS_SERVER:
		err_code = 206;
		break;
	case SYS_INF_RESULT_DNS_ERR:
		err_code = 207;
		break;
	case SYS_INF_RESULT_NO_SMTP_SERVER:
		err_code = 301;
		break;
	case SYS_INF_RESULT_SMTP_ERR_RES:
		err_code = 302;
		break;
	case SYS_INF_RESULT_SMTP_NO_RES:
		err_code = 303;
		break;
	case SYS_INF_RESULT_SMTP_DOWN:
		err_code = 304;
		break;
	case SYS_INF_RESULT_SMTP_ERR:
		err_code = 305;
		break;
	case SYS_INF_RESULT_NO_POP_SERVER:
		err_code = 401;
		break;
	case SYS_INF_RESULT_POP_USER_ERR:
		err_code = 402;
		break;
	case SYS_INF_RESULT_POP_PASS_ERR:
		err_code = 403;
		break;
	case SYS_INF_RESULT_POP_ERR_RES:
		err_code = 404;
		break;
	case SYS_INF_RESULT_POP_NO_RES:
		err_code = 405;
		break;
	case SYS_INF_RESULT_POP_DOWN:
		err_code = 406;
		break;
	case SYS_INF_RESULT_MEM_OVER:
		err_code = 407;
		break;
	case SYS_INF_RESULT_BOX_FULL:
		err_code = 408;
		break;
	case SYS_INF_RESULT_POP_ERR:
		err_code = 409;
		break;
	case SYS_INF_RESULT_NO_MAIL:
		err_code = 410;
		break;
	case SYS_INF_RESULT_ILL_ERR:
		err_code = 501;
		break;
	default:
		err_code = 999;
		break;
	}
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
	CMN_UnsignedIntToASC(&List.S.Print[base-1],err_code,3,'0');
	
	switch (err_code) {
	case 202:
	case 203:
	case 204:
	case 205:
		if ((SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TX)
		|| (SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TXRX)) {
			CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ReTx);
		}
		else {
			CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ReRx);
		}
		break;
	case 302:
	case 303:
	case 304:
	case 305:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ReTx);
		break;
	case 404:
	case 405:
	case 406:
	case 409:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ReRx);
		break;
	case 101:
	case 102:
	case 103:
	case 104:
	case 107:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_DialErr);
		break;
	case 105:
	case 106:
	case 201:
	case 301:
	case 401:
	case 402:
	case 403:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ChkSetting);
		break;
	case 1:
	case 2:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_ChkBoard);
		break;
	case 407:
	case 408:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_MemErr);
		break;
	case 4:
		CMN_StringCopy(&List.S.Print[base+14-1],PWRD_INF_PowerOff);
		break;
	}


	if ((SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TX)
		|| (SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TXRX)) {
		CMN_StringCopy(&List.S.Print[base+43-1],PWRD_INF_Tx);
	}
	else {
		CMN_StringCopy(&List.S.Print[base+43-1],PWRD_INF_Rx);
	}
	CriterionMinuteToDayTimeAsc( SYS_INF_MailCommand[cmd_no].ExecTime/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[base+51-1], List.S.Work );

	/* 1行印字（改行）*/
	if ((ret = CharacterPrint(LST_PRINT)) != OK) {
		return (ret);
	}

	/* 2行印字（改行）*/
	if ((ret = CharacterPrint(LST_LINE_FEED+2)) != OK) {
		return (ret);
	}

	return ( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintMailCheckMsgOption(UBYTE cmd_no, UBYTE *line_cnt, UBYTE page)
{
	WORD ret;
	UBYTE i,j;
	UBYTE ptr;
	UBYTE cnt;
	UBYTE chk_chr;
	UBYTE one_pos;
	UBYTE user_no;
	UBYTE length;
	UBYTE base;

	/* 0        1         2         3         4         5         6         7         8
	** 12345678901234567890123456789012345678901234567890123456789012345678901234567890/
	**      ErrorCode      Note                         Kind    Start
	**      ---------------------------------------------------------------
	**      0101           Repeat transmission.         Tx      00/00 00:00
	**
	**
	**      Access Point: 123456789-123456789
	**                    0123456789
	**                    1111-11111-11111
	**
	**      To: abcdefg@muratec.co.jp
	**          hijklmn@muratec.co.jp
	**          [01][02][03][04][05][06][07][08][09][10][11][12]
	**          [01][02][03][04][05][06][07]
	*/

	ret = OK;
	user_no = SYS_INF_MailCommand[cmd_no].UserNumber;
	base = 6;

	/*　ダイアルエラーの時は登録されている電話番号が印字されます　*/
	switch (SYS_INF_MailCommand[cmd_no].Result) {
	case SYS_INF_RESULT_DIALBUSY:
	case SYS_INF_RESULT_NODIALTONE:
	case SYS_INF_RESULT_DIALTIMEOUT:
	case SYS_INF_RESULT_NOCARRIER:
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
		length = CMN_StringLength(PWRD_INF_AccessPoint);
		CMN_StringCopy( &List.S.Print[base-1], PWRD_INF_AccessPoint );
		for (i = 0; i < SYS_INF_SUB_DIAL_MAX; i++) {
			if ((SYB_INF_UserData[user_no].TelNumber[i][0] & 0xF0) != 0xF0) {
				CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[i][0] );
				CMN_StringCopy( &List.S.Print[base+14-1], List.S.Work );
				if ( (ret = CharacterPrint(LST_PRINT)) != OK) {
					return ( ret );
				}
				(*line_cnt)--;
				if ( (*line_cnt) < 1 ) {
					page++;
					if ( (ret = MailComCheckMsgChangePage( cmd_no, line_cnt, page )) != OK ) {
						return ( ret );
					}
				}
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
			}
		}
		/* 1行印字（改行）*/
		if ((ret = CharacterPrint(LST_LINE_FEED)) != OK) {
			return (ret);
		}
		(*line_cnt)--;
		break;
	default:
		break;
	}

	/* メール送信の時は送信しようとしていた宛先が印字されます　*/
	if ((SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TX)
		|| (SYS_INF_MailCommand[cmd_no].Kind == SYS_INF_MAIL_TXRX)) {

		if ( (*line_cnt) < 1 ) {
			page++;
			if ( (ret = MailComCheckMsgChangePage( cmd_no, line_cnt, page )) != OK ) {
				return ( ret );
			}
		}

		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
		CMN_StringCopy(&List.S.Print[base-1],PWRD_INF_To);
		List.S.Print[base+2-1] = ':';
		for (i = 0; i < SYS_INF_MAIL_DIRECT_COUNT_MAX; i++) {
			if (SYS_INF_MailCommand[cmd_no].Direct[i][0] != NULL) {
				CMN_StringCopy( &List.S.Print[base+4-1], &SYS_INF_MailCommand[cmd_no].Direct[i][0] );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				(*line_cnt)--;
				if ( (*line_cnt) < 1 ) {
					page++;
					if ( (ret = MailComCheckMsgChangePage( cmd_no, line_cnt, page )) != OK ) {
						return ( ret );
					}
				}
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			}
		}
		chk_chr = 0x80;
		for (i = 0,ptr = (base+4); i < SYS_INF_ONETOUCH_POSITION_MAX; i++) {
			for (j = 0; j < 8; j++) {
				if (SYS_INF_MailCommand[cmd_no].Onetouch[i] & (chk_chr >> j)) {
					one_pos = (j + (i * (UBYTE)8));
					cnt++;
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
					List.S.Print[ptr-1] = '[';
					ptr++;
					if ( CMN_OffsetToOnetouchCode( one_pos ) <= 0x7A ){
						List.S.Print[ptr-1] = CMN_OffsetToOnetouchCode( one_pos );
						ptr += 2;
					}
					else{
						List.S.Print[ptr-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
						ptr++;
						List.S.Print[ptr-1] = CMN_OffsetToOnetouchCode( one_pos ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1～U8記号をつくる*/
						ptr++;
					}
					List.S.Print[ptr-1] = ']';
					ptr ++;
 #else	/* PANEL_POPLA_B/L/H */
   #if (PRO_PANEL == ANK)
					List.S.Print[ptr-1] = '[';
					ptr++;
					CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(CMN_OffsetToOnetouchCode( one_pos ) - 0x40), 2, '0' );
					ptr += 2;
					List.S.Print[ptr-1] = ']';
					ptr ++;
   #endif
   #if (PRO_PANEL == KANJI)
					/* ワンタッチの表示　[　]->絵文字 */
					List.S.Print[ptr-1] = LCD_PICFONT;
					ptr++;
					List.S.Print[ptr-1] = LCD_PICFONT_LOWER;
					ptr++;
					CMN_UnsignedIntToASC( &List.S.Print[ptr-1], (UWORD)(CMN_OffsetToOnetouchCode( one_pos ) - 0x40), 2, '0' );
					ptr += 2;
   #endif
 #endif
					if (cnt == 12) {
						if ((ret = CharacterPrint( LST_PRINT )) != OK) {
							return (ret);
						}
						(*line_cnt)--;
						if ( (*line_cnt) < 1 ) {
							page++;
							if ( (ret = MailComCheckMsgChangePage( cmd_no, line_cnt, page )) != OK ) {
								return ( ret );
							}
						}
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						ptr = (base+4);
						cnt = 0;
					}
				}
			}
		}
		if (cnt > 0) {
			if ((ret = CharacterPrint( LST_PRINT )) != OK) {
				return (ret);
			}
			(*line_cnt)--;
		}
	}
	return (ret);
}

/*************************************************************************
	module		:[親展受信通知ﾌﾟﾘﾝﾄ]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintSecureRxNotice(void)
{
	WORD	ret;
	UBYTE	cmd_no;
	UBYTE	user_no;
	UBYTE	box_no;
	UBYTE	line_cnt;
	UBYTE	page;

	cmd_no = (UBYTE)SYS_DocumentPrintNo;
	user_no = SYS_INF_MailCommand[cmd_no].UserNumber;
	box_no = GetFirstSecureMailBox(user_no, cmd_no);

	page = 1;

	while(1) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

		if (page == 1) {
			if ((ret = PrintReceiveReportTitle()) != OK) {
				return ( ret );
			}
			line_cnt -= 11;
		}

		if ((ret = PrintReceiveReportHead(user_no, &line_cnt, page)) != OK) {
			return ( ret );
		}

		while (line_cnt > 0) {
			if ((ret = PrintReceiveReportSpecific(box_no)) != OK) {
				return ( ret );
			}
			line_cnt--;
			box_no = GetNextSecureMailBox(box_no, cmd_no);
			if (box_no == SYS_INF_MAIL_BOX_MAX) {
				ret = CharacterPrint( LST_CLOSE );
				return ( ret );
			}
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}

	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[親展受信通知タイトル]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintReceiveReportTitle(void)
{
	WORD	ret;

#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
		if ( (ret = PrintMailHeadCommon( PWRD_MailReceptionReport,  LST_NOT, 13-1 )) != OK ) {
		    return ( ret );
		}
#else
		if ( (ret = PrintMailHeadCommon( PWRD_MailReceptionReport,  LST_XXX_TWI_XXX, 13-1 )) != OK ) {
		    return ( ret );
		}
#endif

	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[3-1], (UBYTE *)&List.S.Attribute[3-1], PWRD_MailRxReportState1, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[3-1], (UBYTE *)&List.S.Attribute[3-1], PWRD_MailRxReportState2, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[3-1], (UBYTE *)&List.S.Attribute[3-1], PWRD_MailRxReportState3, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[3-1], (UBYTE *)&List.S.Attribute[3-1], PWRD_MailRxReportState4, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	return( ret );
}

/*************************************************************************
	module		:[親展受信通知タイトル]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintReceiveReportHead(UBYTE user_no, UBYTE *line_cnt, UBYTE page)
{
	WORD	ret;

/*	0         1         2         3         4         5         6         7        8
**	01234567890123456789012345678901234567890123456789012345678901234567890123456790
**	  Following mails have been received.
**	  Please press PROGRAM,R,3,ENTER, and then enter your Code Number
**	  to print these mails.
**	  These mails will be printed automatically when \"PrintTime\" will be passed.
**	  
**	                                                                         P.1
**	   Receiver: USERNAME or MAILADDRESS
**	
**	   Sender                                   ReceivedTIme  PrintTime   
**	   -------------------------------------------------------------------
*/

	/* １行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*　ページ番号印字　*/
	if ( (ret = PagePrint( page, 74-1 )) != OK ) {
		return ( ret );
	}

	/*　受信者名またはメールアドレス印字　*/
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[4-1], (UBYTE *)&List.S.Attribute[4-1], PWRD_INF_Receiver, LST_NOT );
	if (SYB_INF_UserData[user_no].UserName[0] != NULL) {
		AttributeSet( (UBYTE *)&List.S.Print[14-1], (UBYTE *)&List.S.Attribute[14-1], SYB_INF_UserData[user_no].UserName, LST_NOT );
	}
	else {
		AttributeSet( (UBYTE *)&List.S.Print[14-1], (UBYTE *)&List.S.Attribute[14-1], SYB_INF_UserData[user_no].MailAddress, LST_NOT );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*　1行空行　*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*　ヘッダー行印字　*/
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[4-1], (UBYTE *)&List.S.Attribute[4-1], PWRD_MailSender, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[45-1], (UBYTE *)&List.S.Attribute[45-1], PWRD_MailReceivedTime, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[59-1], (UBYTE *)&List.S.Attribute[59-1], PWRD_MailAutoPrintTime, LST_NOT );
/***
	AttributeSet( (UBYTE *)&List.S.Print[71-1], (UBYTE *)&List.S.Attribute[71-1], PWRD_No, LST_NOT );
***/
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	CMN_MemorySet( &List.S.Print[4-1], 67, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	(*line_cnt) -= 6;

	return( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	GetFirstSecureMailBox(UBYTE user_no, UBYTE cmd_no)
{
	struct	SYS_INF_PrintPositionTable_t *print_pos;
	UBYTE	box_no;

	print_pos = &SYS_INF_ManualPrintPosition[user_no];

	box_no = print_pos->PrintTop;
	while ((box_no != 0xFF) && (box_no != 0xFE)) {
		if (SYS_INF_RxMailBox[box_no].CommandNo == cmd_no) {
			return (box_no);
		}
		box_no = SYS_INF_RxMailBox[box_no].NextBoxNo;
	}
	return(box_no);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	GetNextSecureMailBox(UBYTE box_no, UBYTE cmd_no)
{
	box_no = SYS_INF_RxMailBox[box_no].NextBoxNo;

	while ((box_no != 0xFF) && (box_no != 0xFE)) {
		if (SYS_INF_RxMailBox[box_no].CommandNo == cmd_no) {
			return (box_no);
		}
		box_no = SYS_INF_RxMailBox[box_no].NextBoxNo;
	}
	return(SYS_INF_MAIL_BOX_MAX);
}

/*************************************************************************
	module		:[親展受信通知詳細]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintReceiveReportSpecific(UBYTE box_no)
{

	UWORD	DEBUG;

/*	0         1         2         3         4         5         6         7        8
**	01234567890123456789012345678901234567890123456789012345678901234567890123456790
**	   Sender                                   ReceivedTIme  PrintTime   
**	   -------------------------------------------------------------------
**	                                            11/11 11:11   11/11 11:11 
*/
	/*　送信者名印字　*/
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	if (SYS_INF_RxMailBox[box_no].From[0] != NULL) {
		AttributeSet( (UBYTE *)&List.S.Print[4-1], (UBYTE *)&List.S.Attribute[4-1], SYS_INF_RxMailBox[box_no].From, LST_NOT );
	}

	CriterionMinuteToDayTimeAsc( SYS_INF_RxMailBox[box_no].ReceiveTime/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[45-1], List.S.Work );

	CriterionMinuteToDayTimeAsc( SYS_INF_RxMailBox[box_no].PrintTime/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[59-1], List.S.Work );

	DEBUG = 0;
	if (DEBUG) {
		/*　管理テーブルの使用状況のDEBUGのために印字する　*/
		CMN_UnsignedIntToASC( &List.S.Print[71-1], (UWORD)box_no, 2,'0');
	}

	return(CharacterPrint( LST_PRINT ));
}

/*************************************************************************
	module		:[通信管理記録ﾌﾟﾘﾝﾄ]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/15]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	LST_PrintJournalReport(void)
{
	WORD	ret;
	UBYTE	user_no;
	UBYTE	line_cnt;
	UBYTE	page;
	UBYTE	log_no;

	user_no = (UBYTE)SYS_DocumentPrintNo;
	page = 1;

	/* ジャーナルデータをプリント用のバッファにコピー 1998/05/22 Eguchi*/
	ReadMailJournal(user_no);

	while(1) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		line_cnt = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

		if (page == 1) {
			if ((ret = PrintJournalReportTitle(user_no, &line_cnt)) != OK) {
				return ( ret );
			}
			/*log_no = SYS_INF_MailJournalData[user_no].ReadPoint; 1998/05/22 Eguchi */
			log_no = SYS_PrintMailJournalData.ReadPoint; /*1998/05/22 Eguchi*/
		}

		if ((ret = PrintJournalReportHead(&line_cnt, page)) != OK) {
			return ( ret );
		}

		while (line_cnt > 1) {
			if ((ret = PrintJournalReportSpecific(&log_no)) != OK) {
				return ( ret );
			}
			line_cnt -= 2;
			if ((SYS_PrintMailJournalData.Log[log_no].Status == 0)
				|| (SYS_PrintMailJournalData.ReadPoint == log_no)) {
				ret = CharacterPrint( LST_CLOSE );
				return ( ret );
			}
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return (MSG_PRN_LST_END);
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/15]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintJournalReportTitle(UBYTE user_no, UBYTE *line_cnt)
{
	WORD	ret;
	UWORD	conn_min;
	UBYTE	base;

/*	0         1         2         3         4         5         6         7         8
**	012345678901234567890123456789012345678901234567890123456789012345678901234567890
***	  
**	 P.1                                                     MMDDHHMM
**	
**	 ------------------------------------------------------------------------
**	 |User Name          |12345678901234567890123456789012345678901234567890|
**	 ------------------------------------------------------------------------
**	 |ISP Name           |                                                  |
**	 ------------------------------------------------------------------------
**	 |Access Point       |
**	 -----------------------------------------------------------------------------
**	 |Connect Time       |
**	 -----------------------------------------------------------------------------
**	 |Connect Count      |
**	 -----------------------------------------------------------------------------
*/

	if ( (ret = PrintMailHeadCommon( PWRD_INF_MailJournal,  LST_XXX_TWI_XXX, 13-1 )) != OK ) {
		return ( ret );
	}
	(*line_cnt) -= 6;

	base = 2;
	/*Page 現在時間*/
	if ( (ret = PageTimePrint( 1, 2-1, 58-1 )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	/* １行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 0, List.S.Print, List.S.Attribute, base);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
	AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_UserName, LST_NOT );
	if (SYB_INF_UserData[user_no].UserName[0] != NULL) {
		AttributeSet( (UBYTE *)&List.S.Print[(base+21)-1], (UBYTE *)&List.S.Attribute[(base+21)-1], SYB_INF_UserData[user_no].UserName, LST_NOT );
	}
	else {
		AttributeSet( (UBYTE *)&List.S.Print[(base+21)-1], (UBYTE *)&List.S.Attribute[(base+21)-1], SYB_INF_UserData[user_no].MailAddress, LST_NOT );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	if (SYB_INF_UserData[user_no].ISP_Name[0] != NULL) {
		PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
		AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_ProviderName, LST_NOT );
		AttributeSet( (UBYTE *)&List.S.Print[(base+21)-1], (UBYTE *)&List.S.Attribute[(base+21)-1], SYB_INF_UserData[user_no].ISP_Name, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}

	if (SYB_INF_UserData[user_no].TelNumber[0][0] != 0xff) {
		PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
		AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_AccessPoint1, LST_NOT );
		CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[0][0] );
		CMN_StringCopy( &List.S.Print[(base+21)-1], List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	
	if (SYB_INF_UserData[user_no].TelNumber[1][0] != 0xff) {
		PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
		AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_AccessPoint2, LST_NOT );
		CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[1][0] );
		CMN_StringCopy( &List.S.Print[(base+21)-1], List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
	
	if (SYB_INF_UserData[user_no].TelNumber[2][0] != 0xff) {
		PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
		AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_AccessPoint3, LST_NOT );
		CMN_BCD_ToASC_String( List.S.Work, &SYB_INF_UserData[user_no].TelNumber[2][0] );
		CMN_StringCopy( &List.S.Print[(base+21)-1], List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}
		
	PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
	AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_ConnectTime, LST_NOT );

#if (0) /* 1998/05/25 Eguchi */
	SecondToHourMinuteSecondAsc( SYS_PrintMailJournalData.ConnectTime, List.S.Work, '0' );
	CMN_StringCopy( &List.S.Print[(base+21)-1], List.S.Work );
#endif
	conn_min =  (UWORD)(SYS_PrintMailJournalData.ConnectTime / 60);
	if (SYS_PrintMailJournalData.ConnectTime % 60) {
		conn_min++;
	}
	CMN_UnsignedIntToASC(&List.S.Print[(base + 21) - 1], conn_min , 0 ,NULL);/*全桁有効。左詰め*/

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 2, List.S.Print, List.S.Attribute, base);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 1, List.S.Print, List.S.Attribute, base);
	AttributeSet( (UBYTE *)&List.S.Print[(base+1)-1], (UBYTE *)&List.S.Attribute[(base+1)-1], PWRD_INF_ConnectCount, LST_NOT );
	CMN_UnsignedIntToASC( &List.S.Print[(base+21-1)], (UWORD)SYS_PrintMailJournalData.ConnectCount, 4, NULL);/*NULLにすると左詰めになる*/
	/*CMN_UnsignedIntToASC( &List.S.Print[(base+21-1)], (UWORD)SYS_PrintMailJournalData.ConnectCount, 4, 0);*/
	/*CMN_StringCopy( &List.S.Print[(base+21-1)], List.S.Work ); 1998/05/23 Eguchi */

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	PrintMailJournalListLine( 3, List.S.Print, List.S.Attribute, base);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	return( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/15]
	author		:[Y.Tanimoto]
*************************************************************************/
WORD	PrintJournalReportHead(UBYTE *line_cnt, UBYTE page)
{
	WORD	ret;
	UBYTE	base;

	base = 2;

	/* １行空行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	if (page > 1) {
		/*Page 現在時間*/
		if ( (ret = PagePrint( 1, 2-1 )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
		/* １行空行 */
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		(*line_cnt)--;
	}

/*	0         1         2         3         4         5         6         7         8
**	012345678901234567890123456789012345678901234567890123456789012345678901234567890
**	                                      
**	 No.  Mail Address                  StartTime    Time   Page(s)  Kind  Result
**	 ----------------------------------------------------------------------------
**	 999  1234568901234679012345678901  11/11 11:11  12:55   999      Tx    OK
**	 ----------------------------------------------------------------------------
*/
	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	AttributeSet( (UBYTE *)&List.S.Print[base-1], (UBYTE *)&List.S.Attribute[base-1], PWRD_CommNo, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[base+5-1], (UBYTE *)&List.S.Attribute[base+5-1], PWRD_INF_Address, LST_NOT );
	/*AttributeSet( (UBYTE *)&List.S.Print[base+35-1], (UBYTE *)&List.S.Attribute[base+35-1], PWRD_INF_StartTime, LST_NOT );*/
	AttributeSet( (UBYTE *)&List.S.Print[base+35-1], (UBYTE *)&List.S.Attribute[base+35-1], PWRD_INF_JournalComStartTime, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[base+47-1], (UBYTE *)&List.S.Attribute[base+47-1], PWRD_Time, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[base+55-1], (UBYTE *)&List.S.Attribute[base+55-1], PWRD_Pages, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[base+64-1], (UBYTE *)&List.S.Attribute[base+64-1], PWRD_INF_Kind, LST_NOT );
	AttributeSet( (UBYTE *)&List.S.Print[base+70-1], (UBYTE *)&List.S.Attribute[base+70-1], PWRD_CommResult, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_cnt)--;

	return( ret );
}

/*************************************************************************
	module		:[]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/05/15]
	author		:[Y.Tanimoto]
*************************************************************************/
/*WORD	PrintJournalReportSpecific(UBYTE user_no, UBYTE *log_no) 1998/05/22 Eguchi */
WORD	PrintJournalReportSpecific(UBYTE *log_no)
{
	WORD	ret;
	UWORD	num;
	UBYTE	base;
	UDWORD	time;
	UWORD	min;
	UWORD	sec;
	UWORD	err_code; /* 1998/08/19 Eguchi */
	
/*	0         1         2         3         4         5         6         7         8
**	012345678901234567890123456789012345678901234567890123456789012345678901234567890
**	                                      
**	 No.  Mail Address                  StartTime    Time   Page(s)  Kind  Result
**	 ----------------------------------------------------------------------------
**	 999  1234568901234679012345678901  11/11 11:11  12:55   999      Tx    OK
**	 ----------------------------------------------------------------------------
*/

	base = 2;

	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
	CMN_MemorySet( &List.S.Print[base-1], 76, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );

	num = SYS_PrintMailJournalData.Log[(*log_no)].Number;
	CMN_UnsignedIntToASC( &List.S.Print[base-1], num, 3, '0' );

	CMN_StringCopyNumNotNULL( &List.S.Print[base+5-1], SYS_PrintMailJournalData.Log[(*log_no)].Address, 31);

	time = SYS_PrintMailJournalData.Log[(*log_no)].StartTime;
	CriterionMinuteToDayTimeAsc( time/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[(base+35)-1], List.S.Work );

	min = sec = 0;
	min = (UWORD)(SYS_PrintMailJournalData.Log[(*log_no)].TotalTime / 60);
	sec = (UWORD)(SYS_PrintMailJournalData.Log[(*log_no)].TotalTime % 60);
	if(min > 99) {/*99分超えたら強制的に99分にする*/
		min = 99;
	}
	CMN_UnsignedIntToASC(&List.S.Print[(base + 48) - 1] , min , 2 , ' ');
	List.S.Print[(base + 50) - 1] = ':';
	CMN_UnsignedIntToASC(&List.S.Print[(base + 51) - 1] , sec , 2 , '0');

	CMN_UnsignedIntToASC( &List.S.Print[(base+56)-1], SYS_PrintMailJournalData.Log[(*log_no)].Page, 3, ' ' );

	/* Kind */
	/*暫定 1998/05/24 Eguchi*/
	if (SYS_PrintMailJournalData.Log[(*log_no)].Kind == SYS_INF_MAIL_TX) {	 /*送信*/
		CMN_StringCopy(&List.S.Print[(base + 65) - 1] , PWRD_INF_Tx);
	}
	else {/*受信*/
		CMN_StringCopy(&List.S.Print[(base + 65) - 1] , PWRD_INF_Rx);
	}

	/* Result */
	if (SYS_PrintMailJournalData.Log[(*log_no)].Result == SYS_INF_RESULT_OK) {
		CMN_StringCopy(&List.S.Print[(base + 71) - 1] , PWRD_INF_Ok);
	}
	else {
		/*CMN_StringCopy(&List.S.Print[(base + 71) - 1] , PWRD_INF_Error);*/
		/*変更 1998/08/18 Eguchi */
		/*まだまだ暫定処理です。ｴﾗｰｺｰﾄﾞが確定したらもう少しましに作り直す*//*FOR DEBUG*/
		switch (SYS_PrintMailJournalData.Log[(*log_no)].Result) {
		case SYS_INF_RESULT_COM_ERR:
			err_code = 1;
			break;
		case SYS_INF_RESULT_COM_ILL_ERR:
			err_code = 2;
			break;
		case SYS_INF_RESULT_ABORT:
			err_code = 3;
			break;
		case SYS_INF_RESULT_POWEROFF:
			err_code = 4;
			break;
		case SYS_INF_RESULT_DIALBUSY:
			err_code = 101;
			break;
		case SYS_INF_RESULT_NODIALTONE:
			err_code = 102;
			break;
		case SYS_INF_RESULT_NOCARRIER:
			err_code = 103;
			break;
		case SYS_INF_RESULT_DIALTIMEOUT:
			err_code = 104;
			break;
		case SYS_INF_RESULT_RX_ONLY:
			err_code = 105;
			break;
		case SYS_INF_RESULT_NOPSTNNUMBER:
			err_code = 106;
			break;
		case SYS_INF_RESULT_PPPAUTHERR:
			err_code = 201;;
			break;
		case SYS_INF_RESULT_PPPNEGOERR:
			err_code = 202;
			break;
		case SYS_INF_RESULT_PPP_NO_RES:
			err_code = 203;
			break;
		case SYS_INF_RESULT_PPP_DOWN:
			err_code = 204;
			break;
		case SYS_INF_RESULT_PPP_ERR:
			err_code = 205;
			break;
		case SYS_INF_RESULT_NO_DNS_SERVER:
			err_code = 206;
			break;
		case SYS_INF_RESULT_DNS_ERR:
			err_code = 207;
			break;
		case SYS_INF_RESULT_NO_SMTP_SERVER:
			err_code = 301;
			break;
		case SYS_INF_RESULT_SMTP_ERR_RES:
			err_code = 302;
			break;
		case SYS_INF_RESULT_SMTP_NO_RES:
			err_code = 303;
			break;
		case SYS_INF_RESULT_SMTP_DOWN:
			err_code = 304;
			break;
		case SYS_INF_RESULT_SMTP_ERR:
			err_code = 305;
			break;
		case SYS_INF_RESULT_NO_POP_SERVER:
			err_code = 401;
			break;
		case SYS_INF_RESULT_POP_USER_ERR:
			err_code = 402;
			break;
		case SYS_INF_RESULT_POP_PASS_ERR:
			err_code = 403;
			break;
		case SYS_INF_RESULT_POP_ERR_RES:
			err_code = 404;
			break;
		case SYS_INF_RESULT_POP_NO_RES:
			err_code = 405;
			break;
		case SYS_INF_RESULT_POP_DOWN:
			err_code = 406;
			break;
		case SYS_INF_RESULT_MEM_OVER:
			err_code = 407;
			break;
		case SYS_INF_RESULT_BOX_FULL:
			err_code = 408;
			break;
		case SYS_INF_RESULT_POP_ERR:
			err_code = 409;
			break;
		case SYS_INF_RESULT_NO_MAIL:
			err_code = 410;
			break;
		case SYS_INF_RESULT_ILL_ERR:
			err_code = 501;
			break;
		default:
			err_code = 999;
			break;
		}
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute);
		CMN_UnsignedIntToASC(&List.S.Print[(base + 71) - 1],err_code,3,'0');
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	(*log_no)++;
	if ((*log_no) >= SYS_INF_LOG_MAX) {
		(*log_no) = 0;
	}
	return (ret);

}

/*************************************************************************
	module		:[罫線印字]
	functiom	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/02/18]
	author		:[Y.Tanimoto]
*************************************************************************/
void	PrintMailJournalListLine(UBYTE Category, UBYTE *AscString, UBYTE *AttString, UBYTE base)
{

	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**  |~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/
			AscString[base-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[(base+1)-1], 70, LST_KLINE_ );
			AscString[(base+20)-1] = LST_KLINE8;
			AscString[(base+71)-1] = LST_KLINE9;
			break;
		case 1:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**  |                   |                                                  |
*/
			AscString[base-1] = LST_KLINEI;
			AscString[(base+20)-1] = LST_KLINEI;
			AscString[(base+71)-1] = LST_KLINEI;
			break;
		case 2:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**  |-------------------|--------------------------------------------------|
*/
			AscString[base-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[(base+1)-1], 70, LST_KLINE_ );
			AscString[(base+20)-1] = LST_KLINE5;
			AscString[(base+71)-1] = LST_KLINE6;
			break;
		case 3:
/* 0        1         2         3         4         5         6         7         8
** 12345678901234567890123456789012345678901234567890123456789012345678901234567890
**  |___________________|__________________________________________________|
*/
			AscString[base-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[(base+1)-1], 70, LST_KLINE_ );
			AscString[(base+20)-1] = LST_KLINE2;
			AscString[(base+71)-1] = LST_KLINE3;
			break;
	}
}



/*************************************************************************
	module		:[ジャーナルデータをプリント用バッファにコピー]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INF]
	date		:[1998/05/22]
	author		:[M.Eguchi]
*************************************************************************/
void	ReadMailJournal(UBYTE	user_no)
{
	struct	SYS_INF_MailJournalData_t *jrnl_ptr;
	struct	LogData_t *src_ptr;
	struct	LogData_t *dst_ptr;
	UBYTE	i;
	UBYTE	read_position;

	/* ｼﾞｬｰﾅﾙﾌﾟﾘﾝﾄ用ﾃﾞｰﾀの初期化*/
	CMN_ClearPrintJournalData(); /* 1998/05/22 Eguchi*/

	jrnl_ptr = &SYS_INF_MailJournalData[user_no];

	/*ｼﾞｬｰﾅﾙﾌｧｲﾙ確保*/
	wai_sem(semno.INF_MailJournal);
	/*ﾒｰﾙ送受信中にｼﾞｬｰﾅﾙ印字ｶﾞｰﾄﾞするのはなんとなくいやなので
	 *ｾﾏﾌｫで排他処理する
	 *また普通はﾕｰｻﾞ数分ｾﾏﾌｫを用意するべきだが、ﾕｰｻﾞ数が増えるとｾﾏﾌｫも増え
	 *ﾓﾆﾀｰｺｰﾙの処理が遅くなる。またﾒｯﾀにないﾀｲﾐﾝｸﾞなので、まとめて一つの
	 *ｾﾏﾌｫで排他処理する.
	 */


	read_position = jrnl_ptr->ReadPoint;
	for (i = 0; i < SYS_INF_LOG_MAX; i++) {
		src_ptr = &jrnl_ptr->Log[read_position];
		dst_ptr = &SYS_PrintMailJournalData.Log[i];
		
		if (src_ptr->Status == 1) {
			/*開始時刻*/
			dst_ptr->StartTime = src_ptr->StartTime;

			/*所要時刻*/
			dst_ptr->TotalTime = src_ptr->TotalTime;

			/*通信種別 */
			dst_ptr->Kind = src_ptr->Kind;

			/*通信結果 */
			dst_ptr->Result = src_ptr->Result;

			/*ﾍﾟｰｼﾞ数*/
			dst_ptr->Page = src_ptr->Page;

			/*ﾒｰﾙｱﾄﾞﾚｽ */
			CMN_StringCopyNULL(dst_ptr->Address , src_ptr->Address);

			/*通信番号 */
			dst_ptr->Number = src_ptr->Number;

			/*ｽﾃｰﾀｽ*/
			dst_ptr->Status = src_ptr->Status;

			read_position++;
			if (read_position >= SYS_INF_LOG_MAX) {
				read_position = 0;
			}
		}
		else {
			dst_ptr->Status = 0;
		}
	}

	/*接続回数*/
	SYS_PrintMailJournalData.ConnectCount = jrnl_ptr->ConnectCount;

	/*接続時間*/
	SYS_PrintMailJournalData.ConnectTime = jrnl_ptr->ConnectTime;

	/*読み出し位置*/
	SYS_PrintMailJournalData.ReadPoint  = 0;

	/*ｼﾞｬｰﾅﾙﾌｧｲﾙを解放*/
	sig_sem(semno.INF_MailJournal);
	/*ﾒｰﾙ送受信中にｼﾞｬｰﾅﾙ印字ｶﾞｰﾄﾞするのはなんとなくいやなので
	 *ｾﾏﾌｫで排他処理する
	 *また普通はﾕｰｻﾞ数分ｾﾏﾌｫを用意するべきだが、ﾕｰｻﾞ数が増えるとｾﾏﾌｫも増え
	 *ﾓﾆﾀｰｺｰﾙの処理が遅くなる。またﾒｯﾀにないﾀｲﾐﾝｸﾞなので、まとめて一つの
	 *ｾﾏﾌｫで排他処理する.
	 */
}



UDWORD	 MonitorOneLineSet(
					UBYTE	*dst,
					UDWORD 	read_pos,
					UDWORD	data_cnt)
{
	UDWORD	cp_cnt;
	UBYTE	data;
	
	for (cp_cnt = 0; cp_cnt < (UDWORD)(LST_COLUM - 1) && data_cnt > 0; cp_cnt++) {

		data = *(UBYTE *)(INF_IF_DataAreaStartAddress + (read_pos % INF_IF_DataAreaSize));

		if (data == 0x0D) { /*CRの場合*/
			*dst++ = 0xFF;
			cp_cnt++;
			read_pos++;
			data_cnt--;
			if ((data_cnt > 0) && (cp_cnt < (LST_COLUM - 1))) {
				data = *(UBYTE *)(INF_IF_DataAreaStartAddress + (read_pos % INF_IF_DataAreaSize));
				if (data == 0x0A) {
					*dst++ = 0xFE;
					data_cnt--;
					cp_cnt++;
					
				}
			}
			return (cp_cnt);
		}
		else {
			if (data == 0x00) {
				data = 0xFD;
			}
			*dst++ = data;
			read_pos++;
			data_cnt--;
		}
	}
	return (cp_cnt);
}



WORD	LST_INF_Monitor(void)
{
	UDWORD	data_count;
	UDWORD	read_count;
	UDWORD	cp_cnt;
	WORD	ret;
	UBYTE	rest_of_lines;
	UBYTE	break_flag;

	if (INF_IF_DataWriteCount > INF_IF_DataAreaSize) { /*1周以上している*/
		data_count = INF_IF_DataAreaSize;
		read_count = INF_IF_DataWriteCount;
	}
	else {
		data_count = INF_IF_DataWriteCount;
		read_count = 0;
	}
	cp_cnt = 0;
	break_flag = 0;

	while (!break_flag) {/*前ページ印字するまでループ*/

		/* リストオープン */
		if ((ret = CharacterPrint(LST_OPEN)) != OK) {
			return ( ret );
		}
		/* 印字可能行数を獲得 */
		rest_of_lines = (UBYTE)PaperSizeLen();	/*印刷可能行数ｾｯﾄ*/

		/* 1CR */
		if ((ret = CharacterPrint( LST_LINE_FEED + 1)) != OK) {
			return (ret);
		}
		rest_of_lines -= 1;

		/* １ページ分印字 */
		while (rest_of_lines > 0) {

			if (data_count == 0) {
				break_flag = 1;
				break;
			}
			else {
				Prn_Att_Str_Clear((unsigned char far *)List.S.Print, (unsigned char far *)List.S.Attribute );
				cp_cnt = MonitorOneLineSet((unsigned char far*)List.S.Print , read_count , data_count);
				if ((ret = CharacterPrint((unsigned char)(LST_PRINT))) != OK) {
					return (ret);
				}
				read_count += cp_cnt;
				data_count -= cp_cnt;
				rest_of_lines -= 1;
				cp_cnt = 0;
			}
		}
		if ((ret = CharacterPrint( LST_CLOSE )) != OK) {
			return ( ret );
		}
	}
	return (MSG_PRN_LST_END);
}

#endif /* PRO_DIALUP_INTERNET_FAX == ENABLE */

