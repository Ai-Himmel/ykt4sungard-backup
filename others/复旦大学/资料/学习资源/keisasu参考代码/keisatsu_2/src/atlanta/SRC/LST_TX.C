/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TX.C
*	Author		:
*	Date		: 1996/11/05
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キャラクタプリント、送信のイメージ展開
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"			/* By H.Hirao 1996/07/08 */
#include "\src\atlanta\define\sys_opt.h"

#include "\src\atlanta\define\lst_def.h"		/* リスト関係のデファイン */
#include "\src\atlanta\define\mem_def.h"		/* メモリ蓄積 原稿種別 */

#include "\src\atlanta\define\cmn_pro.h"		/* 共通関数のプロトタイプ宣言 */
#include "\src\atlanta\define\lst_pro.h"		/* リスト関係のプロトタイプ宣言 */
#include "\src\atlanta\define\uni_pro.h"		/* 1997/05/09  By T.Yamaguchi */
#include "\src\atlanta\define\mlt_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"			/* バックアップRAM */
#include "\src\atlanta\ext_v\fcm_data.h"		/* 通信関係 */
#include "\src\atlanta\ext_v\lst_data.h"		/* リスト関係のextern宣言 */
#include "\src\atlanta\ext_v\lst_wrd.h"			/* リスト関係のワーディング */
#include "\src\atlanta\ext_v\mlt_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#include "\src\memsw\define\mem_sw_b.h"			/* メモリスイッチBのデファイン 1996/04/17 Eguchi*/

#if (PRO_CIPHER == ENABLE)
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if  (PRO_RELAYED_REPORT == ENABLE)	/*  H.Kubo 1998/01/17 */
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\sh7043\define\def_mbxn.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h"
 #if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_def.h"
#include "\src\atlanta\opr\ank\define\opr_pro.h"
 #endif
 #if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#include "\src\atlanta\opr\kanji\define\opr_pro.h"
 #endif
 #if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1998/01/19 */
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
 #endif
 #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/19 */
  #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
  #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
  #endif
 #endif
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

#if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様の TTI 用。 added by H.Kubo 1999/02/17 */
#include "\src\memsw\define\mems_pro.h"
#endif

/*************************************************************************
	module		:[TTIイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/05/28]
	auther		:[石橋正和]
*************************************************************************/
void	LST_SetTTI_Image(
		UBYTE *dest)	/* 展開したイメージを格納する先頭アドレス */
{

	UBYTE	number;	/*  By O.Kimoto 1997/07/10 */

	CMN_MemorySetNULL(&LST_CharacterTx.String[0], (UWORD)(LST_COLUM - 1), ' ');
	LST_CharacterTx.String[LST_COLUM - 1] = '\0';
	if (((TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
	   ||(TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE))
	 && (CHK_UNI_F_CODE_TTI_On())) { /** 掲示板ポーリング送信の場合 */
#if (PRO_F_CODE == ENABLE)	/* By M.Kotani 97/05/21 */
		LST_CharacterTx.String[0] = 'B';
		LST_CharacterTx.String[1] = 'O';
		LST_CharacterTx.String[2] = 'X';
		CMN_UnsignedIntToASC(&LST_CharacterTx.String[3], TxMemoryFileBoxNumber, 2, '0');
		LST_CharacterTx.String[5] = ':';
		CMN_StringCopy(&LST_CharacterTx.String[6], &SYB_SubAddressBoxTable[TxMemoryFileBoxNumber-1].BoxName[0]);	/* BOX Name */
		LST_CharacterTx.String[23] = 'S';
		LST_CharacterTx.String[24] = 'U';
		LST_CharacterTx.String[25] = 'B';
		LST_CharacterTx.String[26] = ':';
		CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_SubAddressBoxTable[TxMemoryFileBoxNumber-1].SubAddress[0]);
		TimeDataAscii(ON, SYB_CurrentTime, &LST_CharacterTx.String[48], 0);
		LST_CharacterTx.String[69] = 'P';
		LST_CharacterTx.String[70] = '.';
		if (TxMemoryFilePage < 100) {
			CMN_UnsignedIntToASC(&LST_CharacterTx.String[71], TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
			LST_CharacterTx.String[74] = 'F';													/*	ファイル番号 */
			LST_CharacterTx.String[75] = '.';
			CMN_UnsignedIntToASC(&LST_CharacterTx.String[76], TxMemoryFileNo[TxMemoryFileCurrentExecutingNo], 2, '0');
		}
		else {
			CMN_UnsignedIntToASC(&LST_CharacterTx.String[71], TxMemoryFilePage, 3, '0');		/*	何枚目の原稿を送信中か	*/
			LST_CharacterTx.String[75] = 'F';													/*	ファイル番号 */
			LST_CharacterTx.String[76] = '.';
			CMN_UnsignedIntToASC(&LST_CharacterTx.String[77], TxMemoryFileNo[TxMemoryFileCurrentExecutingNo], 2, '0');
		}
#endif
	}
	else {

		/* 1997/01/23 Y.Murata
		 * ﾎｽﾄﾒﾓﾘ送信時のTTIがｵﾌﾟｼｮﾝ用のTTIを送信してしまうため修正
		*/
		number = OPT_CHK_ScannerTxExecute();
		if ((number != 0xFF) && (number != 0)) {	/* AL-100 Scanner Tx */
			CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_Option_TTI_Buffer[number][0]);
			if ( SYB_Option_ID_Buffer[number][0] != NULL ) {
				CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
				CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_Option_ID_Buffer[number][0]);
			}
			LST_CharacterTx.String[73] = 'P';
			LST_CharacterTx.String[74] = '.';
			TimeDataAscii(ON, SYB_CurrentTime, &LST_CharacterTx.String[48], number);

			CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_Opt[number].SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
#if defined(USA)
	/* ＵＳＡは、分母無し */
#else
 #if defined(AUS)
			if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
			}
			else{									/* THA,SGP */
				if ((SYS_Opt[number].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[number].CommandFilePage != 0)) {
					LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
					CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
				}
			}
 #else
  #if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/20 */
			if ((SYS_Opt[number].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[number].CommandFilePage != 0)
				&& (CommandFileOptionItem != SYS_RELAYED_TX_REPORT)
			) {
				LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
				CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
			}
  #else
			if ((SYS_Opt[number].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[number].CommandFilePage != 0)) {
				LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
				CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
			}
  #endif
 #endif
#endif

		}
		else{	/* ANZU Scanner Tx  or  ANZU Memory Tx */

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
			if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
				CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_Multi_TTI_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0]);
			}
			else {
				CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_TTI_Buffer[SYS_InternalLineNumber][0]);
			}
 #else
			CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_TTI_Buffer[SYS_InternalLineNumber][0]);
 #endif
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
			if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
				if ( SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] != NULL ) {
					CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
					CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0]);
				}
			}
			else {
				if ( SYB_ID_Buffer[SYS_InternalLineNumber][0] != NULL ) {
					CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
					CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_ID_Buffer[SYS_InternalLineNumber][0]);
				}
			}
 #else
			if ( SYB_ID_Buffer[SYS_InternalLineNumber][0] != NULL ) {
				CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
				CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_ID_Buffer[SYS_InternalLineNumber][0]);
			}
 #endif
#else
 #if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様 TTI 用 by H.Kubo 1999/02/17 */
			if (!CHK_TerminalNameTx()) {	/* 論理反転 1999.3.2 K.Kawata */
 #endif
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
			if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
				CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_Multi_TTI_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0]);
			}
			else {
				CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_TTI_Buffer[0]);
			}
 #else
			CMN_StringCopy(&LST_CharacterTx.String[0], &SYB_TTI_Buffer[0]);
 #endif
 #if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様 TTI 用 by H.Kubo 1999/02/17 */
			}
			if (!CHK_TerminalNumberTx()) {	/* 論理反転 1999.3.2 K.Kawata */
 #endif
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
			if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
				if ( SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] != NULL ) {
					CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
					CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0]);
				}
			}
			else {
				if ( SYB_ID_Buffer[0] != NULL ) {
					CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
					CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_ID_Buffer[0]);
				}
			}
 #else
			if ( SYB_ID_Buffer[0] != NULL ) {
				CMN_StringCopy(&LST_CharacterTx.String[23], &PWRD_FaxD[0]);
				CMN_StringCopy(&LST_CharacterTx.String[27], &SYB_ID_Buffer[0]);
			}
 #endif
 #if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様 TTI 用 by H.Kubo 1999/02/17 */
			}
 #endif
#endif

 #if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様 TTI 用 by H.Kubo 1999/02/17 */
			if (!CHK_TerminalAdditionalTx()) {	/* 論理反転 1999.3.2 K.Kawata */
 #endif
			TimeDataAscii(ON, SYB_CurrentTime, &LST_CharacterTx.String[48], 0);

			if (TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) { /** 検索ポーリング送信の場合 */
				LST_CharacterTx.String[69] = 'D';
				CMN_UnsignedIntToASC(&LST_CharacterTx.String[70], TxMemoryFileNo[TxMemoryFileCurrentExecutingNo], 2, '0');
				LST_CharacterTx.String[73] = 'P';
				LST_CharacterTx.String[74] = '.';
				if (TxMemoryFilePage < 100) {
					CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
				}
				else {
					CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], TxMemoryFilePage, 3, '0');		/*	何枚目の原稿を送信中か	*/
				}
			}
			else if (TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE) { /** 掲示板ポーリング送信の場合 */

#if (0)
** 				/* Ｆコード掲示板の場合、ボックス番号をＴＴＩに載せても受信した側にとっては何も意味が無いので、
** 				** はずします。
** 				** by O.Kimoto 1999/02/10
** 				*/
** 				LST_CharacterTx.String[69] = 'B';		/* ボックス番号 */
** 				CMN_UnsignedIntToASC(&LST_CharacterTx.String[70], TxMemoryFileBoxNumber, 2, '0');
#endif

				LST_CharacterTx.String[73] = 'P';
				LST_CharacterTx.String[74] = '.';
				if ((SYS_TxTotalPage + 1) < 100) {
					CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
				}
				else {
					CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/
				}
			}
			else {	/* 検索ポーリング送信原稿、掲示板ポーリング送信原稿以外 */

				if (CommandFilePage < 100 ) {	/* 総送信枚数が100枚未満の時 */
					LST_CharacterTx.String[73] = 'P';
					LST_CharacterTx.String[74] = '.';

#if (0)/** 一括送信後の手動送信で一括送信のパスを通ってしまう件 1997/06/25 */
** 					if (CommandFileOptionItem == SYS_BATCH_MEMORY_TX) { /** 一括送信時 */
** 					CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], BatchTxFinishPage + 1, 2, '0');	/*	何枚目の原稿を送信中か	*/
** 					}
** 					else if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) { /** 手動送信時 */
** 						CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
** 					}
** 					else {
** 						CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
** 					}
#endif
					/** 送信タイプの見方を変更します By Hirao 1997/06/25 ：変更１１ライン */
					switch (SYS_FaxComType) {
					case SYS_COMMAND_EXECUTE:
						if (CommandFileOptionItem == SYS_BATCH_MEMORY_TX) { /** 一括送信時 */
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], BatchTxFinishPage + 1, 2, '0');	/*	何枚目の原稿を送信中か	*/
						}
						else if (SYS_FaxComTxType == SYS_SCANNER_TX) { /** 手動送信時 */
							/* １００枚以上のスキャナ送信のページ数に対応します by H.Hirao 1999/12/07 */
							/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		@*	何枚目の原稿を送信中か	*/
							if ((SYS_TxTotalPage + 1) < 100) {
								CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
							}
							else {
								LST_CharacterTx.String[70] = 'P';
								LST_CharacterTx.String[71] = '.';
								CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
							}
						}
#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1008/01/21 */
						else if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) { /** 中継配信不達通知 */
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
						}
#endif
						else {
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
						}
						break;
					case SYS_MANUAL_TX:
						/* １００枚以上の手動送信ページ数に対応します by H.Hirao 1999/12/07 */
						/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		@*	何枚目の原稿を送信中か	*/
						if ((SYS_TxTotalPage + 1) < 100) {
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
						}
						else {
							LST_CharacterTx.String[70] = 'P';
							LST_CharacterTx.String[71] = '.';
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						}
						break;
					default:
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
						break;
					}

#if defined(USA)	/* 1996/10/21 ＵＳＡは分母なし */

	#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
	/* ＵＳＡは分母なしやけど、テストのため入れる 本チャンは外す */
					if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)) {
						LST_CharacterTx.String[77] = '/';											/*	「／」	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');	/*	送信合計枚数	*/
					}
	#endif

#else
	#if defined(AUS)								/* 1996/10/21 By N.Sakamoto */
					if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
					}
					else{									/* THA,SGP */
						if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)) {
							LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
						}
					}
	#else											/* 1996/10/21 By N.Sakamoto */
  	 #if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/20 */
					if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)
						&& (CommandFileOptionItem != SYS_RELAYED_TX_REPORT)
					) {
						LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
					}
	 #else
					if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)) {
						LST_CharacterTx.String[77] = '/';																		/*	「／」	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[78], CommandFilePage, 2, '0');			/*	送信合計枚数	*/
					}
	 #endif /* (PRO_RELAYED_REPORT == ENABLE) */
	#endif											/* 1996/10/21 By N.Sakamoto */
#endif

				}
				else {	/* 総送信枚数が３桁のとき */
					LST_CharacterTx.String[70] = 'P';
					LST_CharacterTx.String[71] = '.';

#if (0)/** 一括送信後の手動送信で一括送信のパスを通ってしまう件 1997/06/25 */
** 					if (CommandFileOptionItem == SYS_BATCH_MEMORY_TX) { /** 一括送信時 */
** 						CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], BatchTxFinishPage + 1, 3, '0');	/*	何枚目の原稿を送信中か	*/
** 					}
** 					else if (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) { /** 手動送信時 */
** 						CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/
** 					}
** 					else {
** 						CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], TxMemoryFilePage, 3, '0');		/*	何枚目の原稿を送信中か	*/
** 					}
#endif
					/** 送信タイプの見方を変更します By Hirao 1997/06/25 ：変更１１ライン */
					switch (SYS_FaxComType) {
					case SYS_COMMAND_EXECUTE:
						if (CommandFileOptionItem == SYS_BATCH_MEMORY_TX) { /** 一括送信時 */
							/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], BatchTxFinishPage + 1, 2, '0');	@*	何枚目の原稿を送信中か	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], BatchTxFinishPage + 1, 3, '0');	/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						}
						else if (SYS_FaxComTxType == SYS_SCANNER_TX) { /** 手動送信時 */
							/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 2, '0');		@*	何枚目の原稿を送信中か	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						}
#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1008/01/21 */
						else if (CommandFileOptionItem == SYS_RELAYED_TX_REPORT) { /** 中継配信不達通知 */
							/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 2, '0');		@*	何枚目の原稿を送信中か	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[75], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						}
#endif
						else {
							/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], TxMemoryFilePage, 2, '0');		@*	何枚目の原稿を送信中か	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], TxMemoryFilePage, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						}
						break;
					case SYS_MANUAL_TX:
						/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 2, '0');		@*	何枚目の原稿を送信中か	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], SYS_TxTotalPage + 1, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hirao 1999/12/07 */
						break;
					default:
						/* CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], TxMemoryFilePage, 2, '0');		@*	何枚目の原稿を送信中か	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[72], TxMemoryFilePage, 3, '0');		/*	何枚目の原稿を送信中か	*/	/* changed by H.Hiro 1999/12/07 */
						break;
					}

#if defined(USA)		/* 1996/10/21 ＵＳＡは分母なし */

#else
	#if defined(AUS)								/* 1996/10/21 By N.Sakamoto */
					if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
					}
					else{									/* THA,SGP */
						if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)) {
							LST_CharacterTx.String[75] = '/';																		/*	「／」	*/
							CMN_UnsignedIntToASC(&LST_CharacterTx.String[76], CommandFilePage, 3, '0');			/*	送信合計枚数	*/
						}
					}
	#else											/* 1996/10/21 By N.Sakamoto */
  	 #if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/20 */
					if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)
						&& (CommandFileOptionItem != SYS_RELAYED_TX_REPORT)
					) {
						LST_CharacterTx.String[75] = '/';																		/*	「／」	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[76], CommandFilePage, 3, '0');			/*	送信合計枚数	*/
					}
	 #endif /* (PRO_RELAYED_REPORT == ENABLE) */
					if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (CommandFilePage != 0)) {
						LST_CharacterTx.String[75] = '/';																		/*	「／」	*/
						CMN_UnsignedIntToASC(&LST_CharacterTx.String[76], CommandFilePage, 3, '0');			/*	送信合計枚数	*/
					}
	#endif											/* 1996/10/21 By N.Sakamoto */
#endif
				}
			}
 #if (PRO_TTI_TYPE == TTI_OKI_TYPE) /* 沖仕様 TTI 用 by H.Kubo 1999/02/17 */

			} /* endif (CHK_TerminalAdditionalTx()) */
 #endif

		}
	}
	CMN_MemorySetNULL(&LST_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);

	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}


/*************************************************************************
	module		:[カバーページイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/02]
	auther		:[石橋正和]
*************************************************************************/
void	LST_SetCoverPage_Image(
		UBYTE line,			/* 展開する副走査の行(1～18) */
		UBYTE *dest)	/* 展開したイメージを格納する先頭アドレス */
{
	Print_CoverPage_List(LST_MODE_LINE, &LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], line, 0);
	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}

/*************************************************************************
	module		:[受信証イメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/02]
	auther		:[石橋正和]
*************************************************************************/
void	LST_SetRCR_Image(
		UBYTE line,			/* 展開する副走査の行(1～22) */
		UBYTE *dest)	/* 展開したイメージを格納する先頭アドレス */
{
	Print_RxConf_List(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], line, 0);
	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}

#if 0 /* (PRO_RELAYED_REPORT == ENABLE)	*/ /* 中継配信不達通知のため  竹内 Feb.14.1995 */
/*************************************************************************
	module		:[中継配信不達通知イメージのセット]
	function	:[
		1.
	]
	return		:[
		0	次の行なし
		1	次の行あり
		2	次も同じ行 (エラーページの続き)
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1995/02/15]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE		LST_SetCheckMsg_Image(
	UBYTE		kind,	/* タイトル部／メッセージ部 */
	UBYTE		line,	/* 展開する副走査の行 */
	UWORD		*dest)	/* 展開したイメージを格納する先頭アドレス */
{
	UBYTE	result;

	result = Set_CommErr_ChkMsg( kind, &LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], line );

	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);

	return (result);
}
#endif


/*------------------------------------*/
/* マルチ回線用キャラクタイメージ展開 */
/*------------------------------------*/
/*************************************************************************
	module		:[TTIイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[]
	auther		:[]
*************************************************************************/
void MLT_LST_SetTTI_Image(UBYTE *dest, UBYTE stack_number)
{
	UBYTE	num;

	num = stack_number;

	CMN_MemorySetNULL((UBYTE *)&MLT_CharacterTx.String[0], (UWORD)(LST_COLUM - 1), ' ');
	MLT_CharacterTx.String[LST_COLUM - 1] = '\0';
#if (PRO_F_CODE == ENABLE)	/* By M.Kotani 97/05/21 */
	if ( ((SYS_Opt[num].TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
	    ||(SYS_Opt[num].TxMemoryFileItem == SYS_MEM_SUB_SECURE_FILE))
	  && (CHK_UNI_F_CODE_TTI_On()) ) { /** 掲示板ポーリング送信の場合 */
		MLT_CharacterTx.String[0] = 'B';
		MLT_CharacterTx.String[1] = 'O';
		MLT_CharacterTx.String[2] = 'X';
		CMN_UnsignedIntToASC(&MLT_CharacterTx.String[3], SYS_Opt[num].TxMemoryFileBoxNumber, 2, '0');
		MLT_CharacterTx.String[5] = ':';
		CMN_StringCopy(&MLT_CharacterTx.String[6], &SYB_SubAddressBoxTable[SYS_Opt[num].TxMemoryFileBoxNumber-1].BoxName[0]);	/* BOX Name */
		MLT_CharacterTx.String[23] = 'S';
		MLT_CharacterTx.String[24] = 'U';
		MLT_CharacterTx.String[25] = 'B';
		MLT_CharacterTx.String[26] = ':';
		CMN_StringCopy(&MLT_CharacterTx.String[27], &SYB_SubAddressBoxTable[SYS_Opt[num].TxMemoryFileBoxNumber-1].SubAddress[0]);
		TimeDataAscii(ON, SYB_CurrentTime, &MLT_CharacterTx.String[48], 0);
		MLT_CharacterTx.String[69] = 'P';
		MLT_CharacterTx.String[70] = '.';
		CMN_UnsignedIntToASC(&MLT_CharacterTx.String[71], SYS_Opt[num].TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
		MLT_CharacterTx.String[74] = 'F';													/*	ファイル番号 */
		MLT_CharacterTx.String[75] = '.';
		CMN_UnsignedIntToASC(&MLT_CharacterTx.String[76], SYS_Opt[num].FCM_DataBasePollingNumber, 2, '0');
	}
	else {
#endif
		CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&SYB_Option_TTI_Buffer[num][0]);
		if ( SYB_Option_ID_Buffer[num][0] != NULL ) {
			CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[23], (UBYTE *)&PWRD_FaxD[0]);
			CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[27], (UBYTE far *)&SYB_Option_ID_Buffer[num][0]);
		}
		TimeDataAscii(ON, SYB_CurrentTime, &MLT_CharacterTx.String[48], num);

		/* 検索ポーリング送信原稿 */
		if (SYS_Opt[num].TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) { /** 検索ポーリング送信の場合 */
			MLT_CharacterTx.String[69] = 'D';
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[70], SYS_Opt[num].FCM_DataBasePollingNumber, 2, '0');
		}
#if (PRO_F_CODE == ENABLE)	/* By M.Kotani 97/05/21 */
		else if (SYS_Opt[num].TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE) { /** 掲示板ポーリング送信の場合 */
#if (0)
** 				/* Ｆコード掲示板の場合、ボックス番号をＴＴＩに載せても受信した側にとっては何も意味が無いので、
** 				** はずします。
** 				** by O.Kimoto 1999/02/10
** 				*/
//			MLT_CharacterTx.String[69] = 'B';		/* ボックス番号 */
//			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[70], SYS_Opt[num].TxMemoryFileBoxNumber, 2, '0');
#endif
		}
#endif
		MLT_CharacterTx.String[73] = 'P';
		MLT_CharacterTx.String[74] = '.';

		if (SYS_Opt[num].CommandFileOptionItem == SYS_BATCH_MEMORY_TX) { /** 一括送信時 */
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[75], SYS_Opt[num].BatchTxFinishPage + 1, 2, '0');	/*	何枚目の原稿を送信中か	*/
		}
		else if (SYS_Opt[num].SYS_FaxComTxType == SYS_SCANNER_TX) { /** 手動送信時 */
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[75], SYS_Opt[num].SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
		}
		else if (SYS_Opt[num].TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE) { /** 掲示板ポーリング送信の場合 */
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[75], SYS_Opt[num].SYS_TxTotalPage + 1, 2, '0');		/*	何枚目の原稿を送信中か	*/
		}
		else {
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[75], SYS_Opt[num].TxMemoryFilePage, 2, '0');		/*	何枚目の原稿を送信中か	*/
		}
	/*	@if defined(USA) || defined(AUS) @**	USAでは‘／’‘分母’は付けない仕様 By H.Hirao 1996/05/16	*/
#if defined(USA) 								/* 1996/10/21 By N.Sakamoto */

#else
 #if defined(AUS) 								/* 1996/10/21 By N.Sakamoto */
		if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
		}
		else{									/* THA,SGP */
			if ((SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[num].CommandFilePage != 0)) {
				MLT_CharacterTx.String[77] = '/';																		/*	「／」	*/
				CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[78], SYS_Opt[num].CommandFilePage, 2, '0');			/*	送信合計枚数	*/
			}
		}
 #else 											/* 1996/10/21 By N.Sakamoto */
  #if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/20 */
		if ((SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[num].CommandFilePage != 0)
				&& (SYS_Opt[num].CommandFileOptionItem != SYS_RELAYED_TX_REPORT)
			) {
			MLT_CharacterTx.String[77] = '/';																		/*	「／」	*/
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[78], SYS_Opt[num].CommandFilePage, 2, '0');			/*	送信合計枚数	*/
		}
  #else
		if ((SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[num].CommandFilePage != 0)) {
			MLT_CharacterTx.String[77] = '/';																		/*	「／」	*/
			CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[78], SYS_Opt[num].CommandFilePage, 2, '0');			/*	送信合計枚数	*/
		}
  #endif
 #endif 											/* 1996/10/21 By N.Sakamoto */
#endif
#if (PRO_F_CODE == ENABLE)	/* By M.Kotani 97/05/21 */
	}
#endif
	CMN_MemorySetNULL((UBYTE *)&MLT_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);

	GetOneLineCharacterImage((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&MLT_CharacterTx.Attribute[0], (UBYTE *)dest);
}


/*************************************************************************
	module		:[カバーページイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[]
	auther		:[]
*************************************************************************/
void MLT_LST_SetCoverPage_Image(
		UBYTE line,			/* 展開する副走査の行(1～18) */
		UBYTE *dest,	/* 展開したイメージを格納する先頭アドレス */
		UBYTE stack_number)
{
	Print_CoverPage_List(LST_MODE_LINE, &MLT_CharacterTx.String[0], &MLT_CharacterTx.Attribute[0], line, stack_number);

	GetOneLineCharacterImage((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&MLT_CharacterTx.Attribute[0], (UBYTE *)dest);
}


/*************************************************************************
	module		:[受信証イメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[]
	auther		:[]
*************************************************************************/
void MLT_LST_SetRCR_Image(
		UBYTE line,			/* 展開する副走査の行(1～22) */
		UBYTE *dest,	/* 展開したイメージを格納する先頭アドレス */
		UBYTE stack_number)
{
	Print_RxConf_List(&MLT_CharacterTx.String[0], &MLT_CharacterTx.Attribute[0], line, stack_number);

	GetOneLineCharacterImage((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&MLT_CharacterTx.Attribute[0], (UBYTE *)dest);
}

#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[暗号化サービスラベルイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1997/06/12]
	auther		:[桑原美紀]
*************************************************************************/
void	LST_SetCipher_Image(
		UBYTE line,		/* 出力行 */
		UBYTE *dest)	/* 展開したイメージを格納する先頭アドレス */
{
	switch( line ){
	case	1:			/* １行目 */
		/* "┌─────────────┬─┬──────┬──┐ "*/
		LST_CharacterTx.String[1] = LST_KLINE7;
		CMN_MemorySetNULL(&LST_CharacterTx.String[2], 77, LST_KLINE_ );
		LST_CharacterTx.String[46] = LST_KLINE8;
		LST_CharacterTx.String[49] = LST_KLINE8;
		LST_CharacterTx.String[72] = LST_KLINE8;
		LST_CharacterTx.String[78] = LST_KLINE9;
		CMN_MemorySetNULL(&LST_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);
		GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
		break;
	case	2:			/* ２行目 */
		/* "│ｷｰﾉﾋﾝﾄ:					│	│MURATA MACHINERY,LTD.│  /  │" */
		CMN_MemorySetNULL(&LST_CharacterTx.String[0], (UWORD)(LST_COLUM - 1), ' ');
		LST_CharacterTx.String[LST_COLUM - 1] = '\0';
		LST_CharacterTx.String[1] = LST_KLINEI;
/*		CMN_StringCopy(&LST_CharacterTx.String[2], &PWRD_KeyClue[0]);*/	/* 97/12/19 By M.Kuwahara */
		CMN_StringCopy(&LST_CharacterTx.String[2], PWRD_KeyWordClue);
		LST_CharacterTx.String[10] = ':';
		LST_CharacterTx.String[10] = ':';
		CMN_StringCopy(&LST_CharacterTx.String[11], CipherData.KeyClue);		/* キーのヒント */
		LST_CharacterTx.String[46] = LST_KLINEI;
/*		CMN_StringCopy(&LST_CharacterTx.String[47], CipherData.ExtensionKey);	/* 拡張キー */
		CMN_UnsignedIntToASC(&LST_CharacterTx.String[47], CipherData.ExtensionKey, 2, '0');	/* 拡張キー */
		LST_CharacterTx.String[49] = LST_KLINEI;
		CMN_StringCopy((UBYTE *)&LST_CharacterTx.String[50], (UBYTE *)&SYB_TTI_Buffer);
#if (0)
		LST_CharacterTx.String[50] = 'M';
		LST_CharacterTx.String[51] = 'U';
		LST_CharacterTx.String[52] = 'R';
		LST_CharacterTx.String[53] = 'A';
		LST_CharacterTx.String[54] = 'T';
		LST_CharacterTx.String[55] = 'A';
		LST_CharacterTx.String[56] = ' ';
		LST_CharacterTx.String[57] = 'M';
		LST_CharacterTx.String[58] = 'A';
		LST_CharacterTx.String[59] = 'C';
		LST_CharacterTx.String[60] = 'H';
		LST_CharacterTx.String[61] = 'I';
		LST_CharacterTx.String[62] = 'N';
		LST_CharacterTx.String[63] = 'E';
		LST_CharacterTx.String[64] = 'R';
		LST_CharacterTx.String[65] = 'Y';
		LST_CharacterTx.String[66] = ',';
		LST_CharacterTx.String[67] = 'L';
		LST_CharacterTx.String[68] = 'T';
		LST_CharacterTx.String[69] = 'D';
		LST_CharacterTx.String[70] = '.';
#endif
		LST_CharacterTx.String[72] = LST_KLINEI;
		CMN_UnsignedIntToASC(&LST_CharacterTx.String[73], CipherWritePageNo, 2, '0');
		LST_CharacterTx.String[75] = '/';
		CMN_UnsignedIntToASC(&LST_CharacterTx.String[76], CipherData.PageNo, 2, '0');
		LST_CharacterTx.String[78] = LST_KLINEI;
		CMN_MemorySetNULL(&LST_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);
		GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
		break;
	case	3:			/* ３行目 */
		/* "└─────────────┴─┴──────────┴──┘"*/
		LST_CharacterTx.String[1] = LST_KLINE1;
		CMN_MemorySetNULL(&LST_CharacterTx.String[2], 77, LST_KLINE_ );
		LST_CharacterTx.String[46] = LST_KLINE2;
		LST_CharacterTx.String[49] = LST_KLINE2;
		LST_CharacterTx.String[72] = LST_KLINE2;
		LST_CharacterTx.String[78] = LST_KLINE3;
		CMN_MemorySetNULL(&LST_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);
		GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
		break;
	}
}
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /*  H.Kubo 1998/01/17 */
/*************************************************************************
	module		:[中継配信不達通知のヘッダ部のテキストデータ作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
static UBYTE char_work[LST_COLUM]; /* 作業領域 */

void	LST_SetRlyTxReportHeader_String(
		 UBYTE *AscString,			/*印刷文字列*/
		UBYTE *AttString,	/*修飾文字列*/
		UBYTE line, /* ヘッダー部内の相対的な行番号 */
		UBYTE page
		)
{
#if 0
@@	UBYTE	char_work[LST_COLUM];		/* 作業領域 */
#endif

	Prn_Att_Str_Clear( AscString, AttString );		/*印刷、修飾文字列ｸﾘｱｰ*/
	switch (line) {
	case 1:
	case 5:
		/* 改行 */
		break;
	case 2:
		/* 罫線（上側）*/
		AscString[25-1] = LST_KLINE7;
		CMN_MemorySet( &AscString[26-1], 30, LST_KLINE_ );
		AscString[56-1] = LST_KLINE9;
		break;
	case 3:
		/* 表題 */
		AscString[25-1] = LST_KLINEI;
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &AscString[28-1], &AttString[28-1],
			PWRD_CheckMessage_K, LST_NOT );		/* MES→INV 94.7.20 -> NOT 8.10 */
 #else		/* ｻﾂｷ､ﾗﾍﾞﾝﾀﾞｰはこっちを通る。今のところ一括送信､ﾓﾆﾀｰﾚﾎﾟｰﾄ機能が無い為これで良いが、*/
		AttributeSet( &AscString[28-1], &AttString[28-1],
			PWRD_CheckMessage, LST_MES_TWI_XXX );
 #endif
		AscString[56-1] = LST_KLINEI;
		break;
	case 4:
		/* 罫線（下側）*/
		AscString[25-1] = LST_KLINE1;
		CMN_MemorySet( &AscString[26-1], 30, LST_KLINE_ );
		AscString[56-1] = LST_KLINE3;
		break;
	case 6:
		if (FCM_PtnrChkTTI_TxAvailable()) { /* TTI がつくときは、何も書きません。*/
		}
		else {
			/*Page 現在時間*/
			AscString[2-1] = 'P';
			AscString[3-1] = '.';
			CMN_MemorySet(char_work, LST_COLUM, ' '); /* 作業領域を空白文字で初期化 */
			CMN_UnsignedIntToASC( &AscString[4-1], (UWORD)page, 0, 0 );
			TimeDataAscii( OFF, SYB_CurrentTime, char_work, 0 );
			CMN_StringCopy( &AscString[60-1], char_work );
		}
	default:
		break;
	}
}


/*************************************************************************
	module		:[中継配信不達通知で回線番号表示するかどうか判断する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
UBYTE LST_CheckPrintLineNumber(UBYTE number, UBYTE check)
{
 #if (PRO_LINENUMBER == TWICE_LINE)
 #else
	if (OPT_CountModems() < 2) { /* 始めに、複数回線じゃなかったら、はじくようにします。1997/03/12 Y.Matsukuma */
		return(FALSE);
	}
 #endif
 #if (PRO_MULTI_LINE == ENABLE)	 /* Add By O.Kimoto 1997/06/26 */
	if (check == 0) {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* 初期値のままなら表示しない */
			return(FALSE);
		}
	}
	else {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* 初期値のままなら表示しない */
			return(FALSE);
		}
	}
	return(TRUE);
 #else
	return FALSE;
 #endif
}

/*************************************************************************
	module		:[中継配信不達通知本文中の一通信分のテキスト作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
UWORD LST_CommErr_ChkMsg_Specifi(
		UBYTE *AscString,			/*印刷文字列*/
		UBYTE *AttString,	/*修飾文字列*/
		UBYTE Number		/*番号*/
)
{
#if 0
@@	UBYTE	char_work[LST_COLUM];		/* 作業領域 */
#endif

	CMN_MemorySet(char_work, LST_COLUM, ' '); /* 作業領域を空白文字で初期化 */


	Print_CommErr_ChkMsg_Line( 1, AscString, AttString );
	/*ﾂｳｼﾝｹｯｶ番号*/
	CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_SHORT,
	  LST_RESULT_COMMON, &AscString[2-1], &AttString[2-1] );
	/*ﾂｳｼﾝｹｯｶ ﾒｯｾｰｼﾞ*/
	if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)
	 || (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR)){	/* ﾓﾆﾀｰﾚﾎﾟｰﾄON 一括送信 */
		if ((SYB_ExecQueue[Number].Result & ~ECM_MODE_SET) == NO_ERROR) { /* 正常終了時 Anzu By H.Y 1994/12/19 */
			AttributeSet( &AscString[9-1], &AttString[9-1], PWRD_CheckMessage, LST_NOT );
		}
		else{														/* ｴﾗｰ終了時 */
			CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_LONG,
			  LST_RESULT_COMMON, &AscString[9-1], &AttString[9-1] );
		}
	}
	else{
		/* ﾁｪｯｸﾒｯｾｰｼﾞ */
		CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_LONG,
		  LST_RESULT_COMMON, &AscString[9-1], &AttString[9-1] );
	}
	/*ﾀﾞｲﾔﾙﾊﾞﾝｺﾞｳ*/
	/* CMN_MemorySetNULL( char_work, LST_COLUM-1, ' ' ); */ /**	ワークエリアのクリア By H.Hirao 1996/06/04	*/
	if ( SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR ) {		/* 一括送信 H8は絶対elseに行く*/
 #if ( PRO_BATCH_TX == ENABLE ) /* 不達通知ではこないけど、一応残します。*/
		if ( SYB_BatchTxFile[SYS_DocumentPrintNo].Name[0] != 0x00 ) {	/* BOX名有り */
			CMN_StringCopy( &AscString[40-1], SYB_BatchTxFile[SYS_DocumentPrintNo].Name );
		}
		else {																/* BOX名無しｰ>ﾀﾞｲﾔﾙ番号 */
			BatchTxFileDialDataToString( &SYB_BatchTxFile[SYS_DocumentPrintNo].DialNumber[0],1,char_work,0 );
			CMN_StringCopy( &AscString[40-1], char_work );
		}
 #endif
	}
	else {
		/* 一括送信以外 */
		switch ( SYB_ExecQueue[Number].ExecDial.Item ) {
			case SYS_DIRECT_DIAL:
				CMN_BCD_ToASC_String( char_work, SYB_CommandFile
				  [SYB_ExecQueue[Number].Number.Command].DialNumber.Direct
				  [SYB_ExecQueue[Number].ExecDial.ExecNumber.Command] );
				CMN_StringCopy( &AscString[40-1], char_work );
			break;
			case SYS_ONETOUCH_DIAL:
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				if ( CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.
				  ExecNumber.Onetouch ) <= 0x7A ){ /* ﾜﾝﾀｯﾁ記号が変更(ANZU) By H.Hirao 1996/01/10 */
					AscString[40-1] = '[';
					AscString[42-1] = ']';
					AscString[41-1] =
				  	  CMN_OffsetToOnetouchCode(SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch );
				} else{
					AscString[40-1] = '[';
					AscString[43-1] = ']';
					AscString[41-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
					AscString[42-1] = CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.
					    ExecNumber.Onetouch ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1～U8記号をつくる */
				}
 #else	/* PANEL_POPLA_B/L/H */
  #if (PRO_PANEL == ANK)
				AscString[40-1] = '[';
				AscString[43-1] = ']';
				CMN_UnsignedIntToASC(
 					&AscString[41-1], 
					(UWORD)(CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch ) - 0x40),
					2, 
					'0' );
  #endif
  #if (PRO_PANEL == KANJI)
		 		/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
				AscString[40-1] = LCD_PICFONT;
				AscString[41-1] = LCD_PICFONT_LOWER;
				CMN_UnsignedIntToASC(
 					&AscString[42-1], 
					(UWORD)(CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch ) - 0x40),
					2, 
					'0' );
  #endif
 #endif
				/**	ﾜﾝﾀｯﾁﾀﾞｲｱﾙ記号に加えて相手先名 又は 電話番号を印字する 以下11行追加 For ANZU By H.Hirao 1996/05/10
				*	電話番号は40桁まで登録できるが34桁まで印字する
				*	通信中にﾜﾝﾀｯﾁﾀﾞｲｱﾙを登録し直す可能性はあるが？？？
				*/

 #if (0)
 **				/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
 **				/*
 **				** リモート診断が未登録ならＦ０を書く場合があるのでＦＦで見ているとおかしくなる
 **				** 1997/10/03 M.Shimizu
 **				*/
 **				if ( SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial[0] != LST_DIAL_NOT ) [ /**	ﾜﾝﾀｯﾁﾀﾞｲｱﾙが登録されている場合	*/
 #else
				if ( (SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial[0] & 0xF0) != 0xF0 ) { /**	ﾜﾝﾀｯﾁﾀﾞｲｱﾙが登録されている場合	*/
 #endif

					if ( SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Name[0] != NULL ) { /**	相手先名が登録されている場合	*/
						CMN_StringCopy( &AscString[45],
						  SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Name );
					}
					else { /**	相手先名が登録されていない場合電話番号を印字する	*/
						CMN_BCD_ToASC_String( char_work,
						  SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial );
						CMN_StringCopyNum( &AscString[45], char_work, 34 );
					}
				}
				break;
			case SYS_SPEED_DIAL:
				if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX > 100 ) {
/*					AscString[40-1] = '(';*/
/*					AscString[44-1] = ')';*/
 #if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
					AscString[40-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
					AscString[40-1] = 'S';
 #endif
					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
#if (1) /* 任意短縮４桁化 2002/02/13 By M.Maeda */
						if ( GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF ){
							CMN_UnsignedIntToASC( &AscString[41-1],
								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), OP_SPEED_FIGURE_MAX, '0' );
						}
						else {
							CMN_MemorySet( &AscString[41-1], OP_SPEED_FIGURE_MAX, '*' );
						}
#else
//						if ( GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF ){
//							CMN_UnsignedIntToASC( &AscString[41-1],
//								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), 3, '0' );
//						}
//						else {
//							CMN_MemorySet( &AscString[41-1], 3,'*' );
//						}
#endif
					}
					else{
 #if ( PRO_CPU == SH7043 )	/* FX,MMLで短縮ﾀﾞｲﾔﾙNo.が000～or001～と違う時のため */
						CMN_UnsignedIntToASC( 
							&AscString[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN), 
							3, 
							'0' );
 #else
						CMN_UnsignedIntToASC( 
							&AscString[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+1), 
							3, 
							'0' );
 #endif
					}
				}
				else {
/*					AscString[40-1] = '(';*/
/*					AscString[43-1] = ')';*/
 #if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
					AscString[40-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
					AscString[40-1] = 'S';
 #endif
					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
						if ( GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF ) {							CMN_UnsignedIntToASC( 
								&AscString[41-1],
								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), 
								2, 
								'0' );
						}
						else {
							CMN_MemorySet( &AscString[41-1], 2,'*' );
						}
					}
					else{	/* 通常の短縮の時 */
 #if ( PRO_CPU == SH7043 )	/* FX,MMLで短縮ﾀﾞｲﾔﾙNo.が000～or001～と違う時のため */
						CMN_UnsignedIntToASC( 
							&AscString[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN), 
							2, 
							'0' );
 #else
						CMN_UnsignedIntToASC( 
							&AscString[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+1), 
							2, 
							'0' );
 #endif
					}
				}
				/**	短縮番号に加えて相手先名 又は 電話番号を印字する 以下11行追加 For ANZU By H.Hirao 1996/05/10
				*	電話番号は40桁まで登録できるが34桁まで印字する
				*/

 #if (0)
 **				/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
 **				/*
 **				** リモート診断が未登録ならＦ０を書く場合があるのでＦＦで見ているとおかしくなる
 **				** 1997/10/03 M.Shimizu
 **				*/
 **				if ( SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial[0] != LST_DIAL_NOT ) [ /**	短縮ﾀﾞｲｱﾙが登録されている場合	*/
 #else
				if ( (SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial[0] & 0xF0) != 0xF0 ) { /**	短縮ﾀﾞｲｱﾙが登録されている場合	*/
 #endif
					if ( SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name[0] != NULL ) { /**	相手先名が登録されている場合	*/
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* 任意短縮４桁化 2002/02/13 By M.Maeda */	/* if 1 になっていたが、３桁時に文字がずれるので条件つけます 2003/01/07 T.Takagi */
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
							CMN_StringCopy( &AscString[46], SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
						}
						else {
							CMN_StringCopy( &AscString[45], SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
						}
#else
						CMN_StringCopy( &AscString[45],
						SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
#endif
					}
					else { /**	相手先名が登録されていない場合電話番号を印字する	*/
						CMN_BCD_ToASC_String( char_work,
						  SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial );
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* 任意短縮４桁化 2002/02/13 By M.Maeda */	/* if 1 になっていたが、３桁時に文字がずれるので条件つけます 2003/01/07 T.Takagi */
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* 任意短縮の時 */
							CMN_StringCopyNum( &AscString[46], char_work, 33 );
						}
						else {
							CMN_StringCopyNum( &AscString[45], char_work, 34 );
						}
#else
						CMN_StringCopyNum( &AscString[45], char_work, 34 );
#endif
					}
				}
				break;
		}
	}
	return ( OK );
}


/*************************************************************************
	module		:[中継配信不達通知本文の一行分のテキスト作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
UWORD	LST_SetRlyTxReportBody_String(
		UBYTE *AscString,			/*印刷文字列*/
		UBYTE *AttString,	/*修飾文字列*/
		UBYTE line, /* ヘッダー部内の相対的な行番号 */
		UBYTE number		/*ExecQueue の番号*/
		)
{
	UBYTE 	line_number;


	Prn_Att_Str_Clear( AscString, AttString );		/*印刷、修飾文字列ｸﾘｱｰ*/
 	switch (line) {
	case 1: /* 回線番号表示*/
		line_number = OPT_GetMultiLinrNumber(SYB_ExecQueue[number].StackNumber);
		AttributeSet( &AscString[1-1], &AttString[1-1],
	  				PWRD_LineNumber, LST_NOT );
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/5 */
		if (SYB_ExecQueue[number].StackNumber == 0) {
			if (!(SYB_ExecQueue[number].Option & SYS_EXT_LINE_TX)) {
				AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[0], LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[1], LST_NOT );
			}
		}
		else {
			AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[2], LST_NOT );
		}
 #else
		CMN_UnsignedIntToASC( &AscString[13-1], line_number, 1, '0' );
 #endif
		break;
	case 2:  /* 罫線（上側）*/
	/*�ｮ�｢�ﾎ�｢�｢�｢�｢�ﾎ�｢�｢�｢�｢�｢�ｲ*/
		Print_CommErr_ChkMsg_Line( 0, AscString, AttString );
		break;
	case 3:
		LST_CommErr_ChkMsg_Specifi( AscString, AttString, number ); /*1明細印刷*/
		break;
	case 4: /* 罫線（下側）*/
		Print_CommErr_ChkMsg_Line( 3, AscString, AttString );
		break;
	case 5:
	case 6: /* 空行 */
		break;

 #if (PRO_RESULT_REPORT_TX == ENABLE)
	case 7:  /* 外枠（上側）*/
		Print_CommErr_ChkMsg_Line( 0, AscString, AttString );
		break;
	case 8: /* 罫線（）*/
		Print_CommErr_ChkMsg_Line( 4, AscString, AttString );
		break;
	case 9: /*1明細印刷*/
		LST_CommErr_ChkMsg_Specifi( AscString, AttString, number );
		break;
	case 10: /* 外枠（下側）*/
		Print_CommErr_ChkMsg_Line( 3, AscString, AttString );
		break;
 #endif

	}
	return MSG_LST_ACK_NEW_LINE;
}


/*************************************************************************
	module		:[中継配信不達通知のヘッダのキャラクタイメージデータ作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		LST_CharacterTx
		FontImageBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/

void	LST_SetRlyTxReportHeader_Image(
		UBYTE line, /* ヘッダー部内の相対的な行番号 */
		UBYTE *dest,	/* 展開したイメージを格納する先頭アドレス */
		UBYTE Number,		/*ExecQueue の番号*/
		UBYTE page
		)
{
	LST_SetRlyTxReportHeader_String(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0],line, page);
	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}

/*************************************************************************
	module		:[中継配信不達通知本文のキャラクタイメージデータ作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		LST_CharacterTx
		FontImageBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
void	LST_SetRlyTxReportBody_Image(
		UBYTE line, /* ヘッダー部内の相対的な行番号 */
		UBYTE *dest,	/* 展開したイメージを格納する先頭アドレス */
		UBYTE number		/*ExecQueue の番号*/
		)
{
	LST_SetRlyTxReportBody_String(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0],line, number);
	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}


/*************************************************************************
	module		:[ExecQueue エラーデータ ネクスト サーチ］
	function	:[ExecQueueの次にエラーとなっているデータをサーチする]
	common		:[
		SYB_ExecQueue:
	]
	condition	:[
	]
	commment	:[]
	return		:[
				relayed_tx_command_number と同じコマンド番号の ExecQueue の番号。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/02/18]
	author		:[久保博]
*************************************************************************/
UBYTE	NextErrorExecQueueOfTheCommand( UBYTE relayed_tx_command_number, 
								UBYTE ExecCnt )/*ExecQueueカウント*/
{
	UBYTE	i;						/*loop*/

 #if (PRO_RESULT_REPORT_TX == ENABLE)

	UBYTE	j;
	
	j = 0;
	if (CHK_UNI_ResultReportTxEnable()) {
		if (!CHK_RelayedTxReport()) {
			j = 1;	/* 結果通知 */
		}
		else {
			j = 0;	/* 不達通知 */
		}
	}
	else {
		j = 0;	/* 不達通知 */
	}

	if (j == 1) {
		for ( i = ExecCnt; i < SYS_EXEC_QUEUE_MAX; i++ ) {
			if ((SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)
				&& (relayed_tx_command_number == SYB_ExecQueue[i].Number.Command)	/* ﾁｪｯｸﾒｯｾｰｼﾞ */
				&& ((SYB_ExecQueue[i].Status == SYS_EXEC_OK ) || (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR ))
				) {
				break;
			}
		}
	}
	else {
		for ( i = ExecCnt; i < SYS_EXEC_QUEUE_MAX; i++ ) {
			if ((SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)
				&& (relayed_tx_command_number == SYB_ExecQueue[i].Number.Command)	/* ﾁｪｯｸﾒｯｾｰｼﾞ */
				&& (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR )) {
				break;
			}
		}
	}
	return ((UBYTE)i);
 #else
	for ( i = ExecCnt; i < SYS_EXEC_QUEUE_MAX; i++ ) {
		if ((SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)
			&& (relayed_tx_command_number == SYB_ExecQueue[i].Number.Command)	/* ﾁｪｯｸﾒｯｾｰｼﾞ */
			&& (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR )) {
			break;
		}
	}
	return i;
 #endif

}


#endif /* (PRO_RELAYED_REPORT == ENABLE) */

/*************************************************************************
	module		:[中継配信不達通知のキャラクタイメージデータ作成]
	function	:[
		1. コーデックのタスクから、一行分のキャラクタイメージを作るメッセージを受ける
		2. 一行分のキャラクタイメージをバッファに展開する。
		3. コーデックのタスクに作業完了を通知。
		4. コーデックのメッセージに応じて改ページ処理を行う。
		5. 次の一行を展開する準備をする。
	]
	return		:[なし]
	common		:[
		mbxno.CDC_CTx
		LST_CharacterTx
		FontImageBuffer
	]
	condition	:[
		同時に二つ立ち上げないこと。でないと、フォントバッファが競合する。
		起動時にコマンド送信が始まっていること。
	]
	comment		:[
		CDC_CTxCodeConvertPageTask と組にして使う。
		複数ページにまたがるキャラクタイメージからなるページは、これを元にして作ると楽でしょう。
		本当は、リストプリントと共通の関数を使いたかったのだが、作業バッファが競合するので断念。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/01/17]
	auther		:[久保博]
*************************************************************************/
#if (PRO_RELAYED_REPORT == ENABLE)
CONST UBYTE rtr_debug = 0;
#endif /* (PRO_RELAYED_REPORT == ENABLE) */
void LST_RelayedTxReportImageTask(void)
{
#if (PRO_RELAYED_REPORT == ENABLE)
	/* 初期化 */
	MESSAGE_t *message_from_cdc;
	MESSAGE_t message_to_cdc;
	struct DMA_Data_t dma;
	UWORD ret;
	UBYTE line;
	UBYTE line_of_column;
	UBYTE exec_cnt;
	UBYTE page;
	UBYTE relayed_tx_command_number; /* H.Kubo 1998/02/18 */

	LST_TxPageFinishStatus = TX_PAGE_END;

	exec_cnt = 0;
	
	/* 現在の通信のコマンドの元になった中継配信コマンドのコマンド番号を取得。 H.Kubo 1998/02/18 */
	relayed_tx_command_number = SYB_CommandFile[SYS_CurrentExecutingCommand->Number.Command].Option.OptionNumber.RelaySourceID[0];

	message_from_cdc = NULL;
	page = 1;


	/* DRAM -> COM_CODEC の DMA 初期化 */
	dma.Channel = DMA_DRAM_COMCDC_CH;							/*DMAチャンネル*/
	dma.SrcAddress = (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0];
	dma.Counter = (UWORD)(80 * 16 / 2);							/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	dma.Unit = DMA_WORD_TRANSFER;								/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;							/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	/* 一行分の画データを作っては CDC 側に送る */
	
		/* ヘッダ部 */
	for (line = 1; line <= 6 ;line++) { /* ヘッダの行数だけループ */
			/* CDC から画データ作成依頼のメッセージを待つ */
		rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
		if (message_from_cdc->Message & MSG_CDC_REQUEST_NEW_LINE) {
			/* バッファにキャラクタ一行分の画データを用意する */
			LST_SetRlyTxReportHeader_Image(line, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], exec_cnt, page);
			/* 画データができたことを CDC 側に知らせる */
			message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
			DMA_SetupDMAU(&dma);
			DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
		}
		else {
			line--; 
			message_to_cdc.Message = MSG_LST_EMPTY_NEW_LINE;
		}
		if (message_from_cdc->Message & MSG_CDC_REQUEST_PAGE_END) {
			page++;
			message_to_cdc.Message |= MSG_LST_ACK_PAGE_END;
		}
		snd_msg(mbxno.CDC_CTx, &message_to_cdc);
		
	}

	if (rtr_debug == 1) {
		while (1) {
			rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
			message_to_cdc.Message = MSG_LST_EMPTY_NEW_LINE | MSG_LST_ACK_PAGE_END;
			snd_msg(mbxno.CDC_CTx, &message_to_cdc);
			LST_TxPageFinishStatus = TX_END;
		}
	}

#if (PRO_RESULT_REPORT_TX == ENABLE)	/* Add By O.Kimoto 1998/12/10 */
	/* ボディ部 */

	/* 不達／結果通知のフォーマットを変更します。
	** 従来の「１明細／１表」から「全部／１表」形式にします。
	** よって、外枠の上側と下側は例外処理が必要となります。
	** by O.Kimoto 1998/12/10
	*/

 #if (0)	/* 罫線が一本多い不具合修正。By H.Fujimura 1999/02/08 */
 //	/* CDC から画データ作成依頼のメッセージを待つ */
 //	rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
 //	/* バッファにキャラクタ一行分の画データを用意する */
 //	LST_SetRlyTxReportBody_Image(7, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], 0);
 //	/* 画データができたことを CDC 側に知らせる */
 //	message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
 //	DMA_SetupDMAU(&dma);
 //	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
 //	snd_msg(mbxno.CDC_CTx, &message_to_cdc);
 //	line ++;
 //	line_of_column = 9;
 #endif

	while (exec_cnt < SYS_EXEC_QUEUE_MAX) {
		exec_cnt = NextErrorExecQueueOfTheCommand(relayed_tx_command_number, exec_cnt );		/*次ﾃﾞｰﾀｻｰﾁ*/
		if (exec_cnt >= SYS_EXEC_QUEUE_MAX) {
			break;
		}

 #if (0)	/* 罫線が一本多い不具合修正。By H.Fujimura 1999/02/08 */
 //		if (line == 0) {
 #else
		if (line == 7) {
 #endif
			rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
			/* バッファにキャラクタ一行分の画データを用意する */
			LST_SetRlyTxReportBody_Image(7, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], 0);
			/* 画データができたことを CDC 側に知らせる */
			message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
			DMA_SetupDMAU(&dma);
			DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
			snd_msg(mbxno.CDC_CTx, &message_to_cdc);
			line ++;
			line_of_column = 9;
		}
		else {
			line_of_column = 8;
		}

		for (; line_of_column < 10; line++, line_of_column++) { /* 一つのキューの印字がすむまで */
			/* CDC から画データ作成依頼のメッセージを待つ */
			rcv_msg(mbxno.CDC_CTx, &message_from_cdc);

			/* バッファにキャラクタ一行分の画データを用意する */
			message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
			if ((message_from_cdc->Message & MSG_CDC_REQUEST_PAGE_END ) && (line_of_column == 9) ) {
				line_of_column ++;
				page++;
				line = 0; /* 改ページしたら、行カウンタはリセット */
				message_to_cdc.Message |= MSG_LST_ACK_PAGE_END;
			}
			LST_SetRlyTxReportBody_Image(line_of_column, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], exec_cnt);
			/* 画データができたことを CDC 側に知らせる */
			DMA_SetupDMAU(&dma);
			DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
			snd_msg(mbxno.CDC_CTx, &message_to_cdc);
		}
		exec_cnt++;
	}

	rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
	/* バッファにキャラクタ一行分の画データを用意する */
	LST_SetRlyTxReportBody_Image(10, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], 0);
	/* 画データができたことを CDC 側に知らせる */
	message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
	DMA_SetupDMAU(&dma);
	DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
	snd_msg(mbxno.CDC_CTx, &message_to_cdc);
	line ++;

#else
		/* ボディ部 */
	while (exec_cnt < SYS_EXEC_QUEUE_MAX) {
		exec_cnt = NextErrorExecQueueOfTheCommand(relayed_tx_command_number, exec_cnt );		/*次ﾃﾞｰﾀｻｰﾁ*/
		if (exec_cnt >= SYS_EXEC_QUEUE_MAX) {
			break;
		}
#if 0
@@		if(LST_CheckPrintLineNumber(exec_cnt, 0)) {
@@			line_of_column = 1;
@@		}
@@		else {
@@			line_of_column = 2;
@@		}
#else
		line_of_column = 2; /* 回線番号は常に表示しません。*/
#endif
		for (; line_of_column < 6; line++, line_of_column++) { /* 一つのキューの印字がすむまで */
			/* CDC から画データ作成依頼のメッセージを待つ */
			rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
			/* バッファにキャラクタ一行分の画データを用意する */
			LST_SetRlyTxReportBody_Image(line_of_column, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], exec_cnt);
			/* 画データができたことを CDC 側に知らせる */
			message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
			if ((message_from_cdc->Message & MSG_CDC_REQUEST_PAGE_END ) && (line_of_column == 5) ) {
				page++;
				line = 0; /* 改ページしたら、行カウンタはリセット */
				message_to_cdc.Message |= MSG_LST_ACK_PAGE_END;
			}
			DMA_SetupDMAU(&dma);
			DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
			snd_msg(mbxno.CDC_CTx, &message_to_cdc);
		}
		exec_cnt++;
	}
#endif

	/* 原稿長が短すぎると受信エラーを起こす FAX があるため、原稿長がカバーページと同じになるように
	** 空白行を最後につけます。
	*/
	while (line++ < CVR_LINES) {
		/* CDC から画データ作成依頼のメッセージを待つ */
		rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
		/* バッファにキャラクタ一行分の画データを用意する */
		CMN_MemorySet(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], (UWORD)(80*16), (UBYTE)0);
		/* 画データができたことを CDC 側に知らせる */
		/* message_to_cdc.Message = ret; */
		message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
		if ( message_from_cdc->Message & MSG_CDC_REQUEST_PAGE_END  ) {
			page++;
			message_to_cdc.Message |= MSG_LST_ACK_PAGE_END;
		}
		DMA_SetupDMAU(&dma);
		DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
		snd_msg(mbxno.CDC_CTx, &message_to_cdc);
	}

	/* これより上では、こちらからページ終了要求を言い出しません。 */

	/* 通信タスクにもう送信するものがないことを教えてやる */
	LST_TxPageFinishStatus = TX_END;

	/* これより下では、こちらからページ終了を要求します。 */
	for (; /* 殺されるまで無限ループ */ ;) {
			/* CDC から画データ作成依頼のメッセージを待つ */
		rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
		if (message_from_cdc->Message & MSG_CDC_REQUEST_PAGE_END) {
			/* ページ切り替えしてヘッダを出力することだけは受け付ける */
			message_to_cdc.Message = MSG_LST_EMPTY_NEW_LINE | MSG_LST_ACK_PAGE_END;
			snd_msg(mbxno.CDC_CTx, &message_to_cdc);
			page++;
			rcv_msg(mbxno.CDC_CTx, &message_from_cdc);
			if (message_from_cdc->Message & MSG_CDC_REQUEST_NEW_LINE) {
				LST_SetRlyTxReportHeader_Image(4, &FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], exec_cnt, page);
				DMA_SetupDMAU(&dma);
				DMA_RequestEnable(DMA_DRAM_COMCDC_CH);	/*DMAUの種類*/
				message_to_cdc.Message = MSG_LST_ACK_NEW_LINE;
				line++;
			}
			else {
				message_to_cdc.Message = MSG_LST_EMPTY_NEW_LINE;
			}
		}
		else {
			/* 画データはもうないことを CDC 側に知らせる */
			message_to_cdc.Message = MSG_LST_EMPTY_NEW_LINE | MSG_LST_ACK_PAGE_END;
		}
		message_to_cdc.Message |=  MSG_LST_ACK_PAGE_END;
		page++;
		snd_msg(mbxno.CDC_CTx, &message_to_cdc);
	}
#endif /* (PRO_RELAYED_REPORT == ENABLE) */

}


#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1998/06/15 Y.Murata */
/*************************************************************************
	module		:[CILイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[F120/F100 RISC対応 1998/06/15 Y.Murata]
	machine		:[SHC]
	language	:[MS-C(Ver.6.0)]
	keyward		:[LST]
	date		:[1997/08/06]
	auther		:[宮崎]
*************************************************************************/
void MLT_LST_SetCIL_Image(UBYTE *dest, UWORD page, UWORD *cilP, UBYTE stack_number)
{
	UBYTE	num;

	num = stack_number;

	CMN_MemorySetNULL((UBYTE *)&MLT_CharacterTx.String[0], (UWORD)(LST_COLUM - 1), ' ');
	MLT_CharacterTx.String[LST_COLUM - 1] = '\0';

#if defined(JPN)	/* 日本語では、ﾜｰﾃﾞｨﾝｸﾞが長いため、ずらします。1998/07/10 Y.Matsukuma */
	if (CHK_UNI_CIL_TSIPrintOn()) {	/* 相手先 1234567890 */
		/* PWRD_RemoteFromは「相手先名」ですが、番号に「名」はおかしいので、NULLで上書きして使います */
		CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&PWRD_RemoteFrom[0]);
		MLT_CharacterTx.String[6] = ' ';
		MLT_CharacterTx.String[7] = ' ';
		CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[7], (UBYTE *)cilP);
		MLT_CharacterTx.String[27] = ' ';
	}
#else
	if (CHK_UNI_CIL_TSIPrintOn()) {	/* From:1234567890 */
		CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&PWRD_RemoteFrom[0]);
		CMN_StringCopy((UBYTE *)&MLT_CharacterTx.String[6], (UBYTE *)cilP);
		MLT_CharacterTx.String[26] = ' ';
	}
#endif

	TimeDataAscii(ON, SYB_CurrentTime, &MLT_CharacterTx.String[48], num);

	if (CHK_UNI_CIL_TSIPrintOn()) {
		MLT_CharacterTx.String[73] = 'P';
		MLT_CharacterTx.String[74] = '.';

		CMN_UnsignedIntToASC((UBYTE *)&MLT_CharacterTx.String[75], page, 2, '0');		/*	何枚目の原稿を送信中か	*/
	}
	CMN_MemorySetNULL((UBYTE *)&MLT_CharacterTx.Attribute[0], (UWORD)(LST_COLUM - 1), LST_NOT);

	GetOneLineCharacterImage((UBYTE *)&MLT_CharacterTx.String[0], (UBYTE *)&MLT_CharacterTx.Attribute[0], (UBYTE *)dest);
}
#endif	/* End of (PRO_DATE_SET_RXDOC_CHK == ENABLE) */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
/*************************************************************************
	module		:[カバーページイメージのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/02]
	auther		:[石橋正和]
*************************************************************************/
void	LST_SetEmergencyReport_Image(
		UBYTE line,			/* 展開する副走査の行(1～18) */
		UBYTE *dest)	/* 展開したイメージを格納する先頭アドレス */
{
	Print_EmergencyReport_List(LST_MODE_LINE, &LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], line, 0);
	GetOneLineCharacterImage(&LST_CharacterTx.String[0], &LST_CharacterTx.Attribute[0], dest);
}
 #endif
#endif

