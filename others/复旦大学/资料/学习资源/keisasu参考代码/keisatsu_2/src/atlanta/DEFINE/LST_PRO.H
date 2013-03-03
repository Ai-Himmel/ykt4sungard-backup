/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_PRO.H
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票関係　関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言ﾌｧｲﾙ
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef	LST_PRO_H
	#define	LST_PRO_H	1

/*************************************************
*	FILE:=:\src\atlanta\src\lst_main.c			 *
*************************************************/
void	LST_PrintTask( void );
void	PrinterErrConvert(
			 WORD *Code,				/*コード*/
			 UBYTE Error );				/*プリンターエラーコード*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
WORD	Pattern_TempCheck( void );
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_name.c		 *
*************************************************/
void 	CommunicationModeName(
			 UWORD ComMode,
			 register UBYTE *ComName,
			 register UBYTE *ComAttribute );
void 	CommunicationResultName(
			 UWORD Result,
			 UBYTE NameCategory,
			 UBYTE Special,
			 register UBYTE *ResultName,
			 register UBYTE *ResultAttri );
void	CommunicationKindName(
			 UWORD ComKind,
			 UBYTE NameCategory,
			 register UBYTE *KindName,
			 register UBYTE *KindAttri );
UBYTE 	ProgramDataDialToString(
			 struct SYS_DialData_t *DialData,		/*変換元プログラムデータ*/
			 UBYTE DialDataMax,						/*変換元プログラムデータ数*/
			 register UBYTE *DialString,			/*変換先プログラムデータ文字列*/
			 UBYTE LineNumber );					/*行番号*/
/*ok*/
UBYTE 	L_string_over_chk(
			 UBYTE *StrOne,							/*１行文字列*/
			 UBYTE *StrRet,							/*ﾘﾀｰﾝ文字列*/
			 register UBYTE *String,				/*セット文字列*/
			 UBYTE *NowLine,						/*現在行*/
			 UBYTE LineNumber,						/*ﾘﾀｰﾝ対象行*/
			 UBYTE L_String,						/*１行の最大行数*/
			 UBYTE Comma );							/*ｶﾝﾏ位置*/
/*NG*/
#if ( PRO_MAKER == FX )
UBYTE 	ProgOptionDataToString(
			 UWORD Item,
			 WORD SecureNumber,
			 UBYTE RelayGroupNumber[],
			 UWORD DatabaseNumber[],
			 register UBYTE *ProgOptString,
			 UBYTE LineNumber );
#else
UBYTE 	ProgOptionDataToString(
			 UWORD Item,
			 WORD SecureNumber,
			 UDWORD RelayGroupNumber,
			 UWORD DatabaseNumber[],
			 register UBYTE *ProgOptString,
			 UBYTE LineNumber );
#endif
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
void	GroupToShortString(
			UDWORD GroupData,
			UBYTE* GroupString,
			UBYTE sifuto_cnt);
#else
void 	GroupToShortString(
			UDWORD GroupData,
			register UBYTE *GroupString );
#endif
void	MemoryEmptyBkString(
			UBYTE *String );						/*メモリ残量文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_tcr.c			 *
**************************************************/
WORD 	Print_TxConf_List( void );					/*なし*/
WORD 	Print_TxConf_One_List(
			 UBYTE TxJnNb );						/*送信ファイル番号*/
WORD	Print_TxConf(								/* 追加(ANZU) By H.Hirao Apr.17,1996 */
			 UBYTE prn_mode );						/** 印刷ﾓｰﾄﾞ */
													/* LST_ERR_CLOSE_NOT ｴﾗｰcloseしない */
													/* LST_ERR_CLOSE		ｴﾗｰcloseする */
WORD	Print_ManualTxConf(							/* 追加(ANZU) By H.Hirao 1996/06/24 */
			 void );								/* なし */

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* 日立特許回避 1998/10/28 Y.Matsukuma */
WORD	Print_TxConf_Head(							/* 追加(ANZU) By H.Hirao Apr.17,1996 */
			 UBYTE prn_mode,
			 UDWORD time );						/** ﾌﾟﾘﾝﾀﾓｰﾄﾞ */
#else
WORD	Print_TxConf_Head(							/* 追加(ANZU) By H.Hirao Apr.17,1996 */
			 UBYTE prn_mode );						/** ﾌﾟﾘﾝﾀﾓｰﾄﾞ */
#endif

WORD	Print_TxConf_Detail(						/* 追加(ANZU) By H.Hirao Apr.17,1996 */
			 UBYTE number,
			 UBYTE prn_mode );
WORD	Print_ManualTxConf_Detail(					/* 追加(ANZU) By H.Hirao 1996/06/24 */
			 UBYTE number );						/* 送信ファイル番号 */
WORD 	TTI_ID_Print_Feed(
			void );									/*なし*/
void 	Prn_Att_Str_Clear(
			 register UBYTE *prn_str,				/*印刷文字列*/
			 register UBYTE *att_str );				/*修飾文字列*/
WORD	CurrentTimePrint(
			 UBYTE LocateX );						/*印刷桁位置*/
void 	Print_Conf_List_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
void	Print_TxConf_Line(							/**追加(ANZU) By H.Hirao Apr.17,1996 */
			 UBYTE Category,						/**罫線種類 */
			 UBYTE *AscString,						/**印刷文字列 */
			 UBYTE *AttString );					/**修飾文字列 */
UBYTE	Print_LineNumber(UBYTE number, UBYTE check);
#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* 日立特許回避 1998/10/28 Y.Matsukuma */
UDWORD	TranceTime();
#endif
UBYTE	DialWithinCheck(CONST UBYTE *work);
#if defined(EUR) || (PRO_NEW_TX_CONF == ENABLE)	/* DTS対策[Bb5.1.1-4] Journal(TCR)の記述方法 S.Fukui Nov.5,1999 */
			/* 2000.2.9 K.Kawata	kakiから移植 by M.Harada 1999/11/17 */
UBYTE	Print_TTI_InsteadOfLineNumber(UWORD number, UBYTE check);
#endif
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000.2.9 K.Kawata */
void	NewSendDocumentMessage(UWORD);
WORD	MunualTxDocumentMessage(UWORD journal_num);	/* 2000/03/16 M.Matsumoto */
#endif
/*************************************************
*	FILE:=:\src\atlanta\src\lst_tti.c			 *
**************************************************/
WORD 	Print_TTI_List(
			void );									/*なし*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_cvr.c			 *
**************************************************/
WORD		Print_CoverPage_List(
		     UBYTE Mode,				/*実行モード*/
			 UBYTE *AscString,		/*印刷文字列*/
			 UBYTE *AttString,		/*修飾文字列*/
			 UBYTE Line,				/*対象行（１～）*/
			 UBYTE stack_number);
void 	Print_CoverPage_List_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_scr.c			 *
**************************************************/
WORD 	Print_Mailbox_List(
			 void );								/*なし*/
void 	Print_Mailbox_List_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_rscr.c		 *
**************************************************/
WORD 	Print_SecureRcv_Notice(
			 UBYTE MailboxNumber );					/*親展受信ボックス番号*/
void 	Print_Secure_Notice_List(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_dscr.c		 *
**************************************************/
WORD 	Print_DelSecure_Notice(
			 UBYTE Mode );							/*印刷モード*/
WORD 	Print_DelSecure_Notice_Specifi(
			 UBYTE MailNumber,
			 UBYTE mode );							/*親展受信データ番号*/
WORD	Print_DelSecure_Notice_Head(
			 UBYTE Category,						/*ヘッダ種類*/
			 UBYTE Page );							/*ページ*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_pdwn.c		 *
**************************************************/
WORD 	Print_PowerOff_Notice(
			 void );								/*なし*/
WORD 	Check_AnyList(
			 UBYTE Mode );							/*チェックモード*/
void 	Init_AnyList(
			 UBYTE Mode );							/*消去モード*/

#if defined(CHN)          /* S.Wang  1995/08/22 */
WORD	PowerDown_Secure(							/* 95/1/9 by BU */
			 void );
WORD	PowerDown_MemoryRcv(						/* 95/1/9 by BU */
			 void );
void	Print_Secure_Double_List(
			 UBYTE Category,
			 register UBYTE *AscString,
			 register UBYTE *AttString );			/* 95/1/12 by BU */
#endif
/*************************************************
*	FILE:=:\src\atlanta\src\lst_msw.c			 *
**************************************************/
WORD 	Print_Memory_switch(
			 void );								/*なし*/
void 	Dip_String_Set(
			 UBYTE DipSwitch,						/*デイップスイッチ データ*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
WORD				Print_MemorySwitch_Head(
			 UBYTE Category);						/*ヘッダ種類*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_cmd.c			 *
**************************************************/
WORD 	Print_ReserveCmd_List(
			 void );								/*なし*/
#if (0)
WORD 	Print_ReserveCmd_List_Specifi(
			 UBYTE ComNumber );						/*通信予約ﾃﾞｰﾀ番号*/
#endif
WORD	Print_ReserveCmd_List_Specifi(
			 UBYTE Page,							/*ページ*/
			 UBYTE ComNumber,						/*通信予約ﾃﾞｰﾀ番号*/
			 UBYTE *Line,							/* 現在明細数 */
			 UBYTE *LineCnt);						/* 印字行位置 */
void	Print_ReserveCmd_List_Line(					/*1996/12/28 T.Isobe ﾗｲﾝの位置を変更した為*/
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
#if (PRO_BATCH_TX_RESERVE_LIST == ENABLE) && (PRO_BATCH_TX == ENABLE)	/* Add By H.Fujimura 1998/12/01 */
WORD 	PrintReserveCmdBatchLine(
			 UBYTE Page,							/*ページ*/
			 UBYTE BoxNumber,						/*一括送信ボックス番号*/
			 UBYTE *LineCnt);						/* 印字行位置 */
#endif
/*************************************************
*	FILE:=:\src\atlanta\src\lst_dcmd.c		 *
**************************************************/
WORD 	Print_DelReserveCmd_Notice(
			 void );								/*なし*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_msgf.c		 *
**************************************************/
WORD 	Print_RxmryOver_ChkMsg(
			 void );								/*なし*/
void	Print_RxmryOver_ChkMsg_Line(
			 UBYTE Category,						/*見出し種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/

#if defined(KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
WORD 	Print_ForceStopComm_ChkMsg(
			 void );								/*なし*/

#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_ptn.c			 *
**************************************************/
#if (0)					/*	By Y.Suzuki 1996/11/09	*/
**#if (PRO_CODEC_TYPE == IDP301)	/** Without KIRI **//** Jul,27,1994 **/
**WORD 	Print_Pattern_Print(
**			UBYTE Pattern );						/*パターン（1-7）*/
**WORD	Pattern_Koushi(
**			void );									/*なし*/
**WORD	Pattern_Kamikasu(
**			void );									/*なし*/
**WORD	Pattern_Masume(
**			void );									/*なし*/
**WORD	Loop_Image(
**			UWORD Count );							/*縦ﾄﾞｯﾄ数*/
**#endif
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_msga.c		 *
**************************************************/
WORD 	Doc_ChkMsg(
			 void );								/*なし*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_msgb.c		 *
**************************************************/
WORD 	Print_CommErr_ChkMsg(
			 void );								/*なし*/
WORD 	Print_CommErr_ChkMsg_Common(
			 UBYTE PrnKind );						/*帳票種類*/
/* 引数追加	1998/10/28 Y.Matsukuma */
WORD 	Print_CommErr_ChkMsg_Specifi(
			 UBYTE Number,							/*番号*/
			 UBYTE PrnMode,							/*印刷モード*/
			 UBYTE PrnKind );						/*印刷種類*/
void 	Print_CommErr_ChkMsg_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
WORD 	Print_ChkMsg_Head(
			 UBYTE PrnMode );						/*印刷モード*/
#if defined(JPN)	/* DEUのみ復活  97/11/26 By M.Kuwahara */
WORD	Print_ChkMsg_ErrorPages(
			 UBYTE PrnMode,							/*印刷モード*/
			 UBYTE *ErrPageData,					/*エラーページデータ*/
			 UBYTE ErrPageSize,						/*エラーページデータ数*/
			 UBYTE *LineCnt );						/*残り印刷可能行数*/
#endif
WORD 	Print_ChkMsg_ErrorPages(
			 UBYTE PrnMode,							/*印刷モード*/
			 UBYTE *ErrPageData,					/*エラーページデータ*/
			 UBYTE ErrPageSize,						/*エラーページデータ数*/
			 UBYTE *LineCnt );						/*残り印刷可能行数*/
WORD	Print_Err_ChkMsg_Head(
			 UBYTE Category,						/*ヘッダ種類*/
			 UBYTE Page,							/*ページ*/
			 UBYTE PrnKind );						/*帳票種類*/
void	ExecQueueNextSearch(
			 register UBYTE *ExecCnt );				/*ExecQueueカウント*/

#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  竹内 Feb.14.1995 */
	UBYTE	Set_CommErr_ChkMsg( UBYTE, UBYTE *, UBYTE *, UBYTE );
	void	Set_ChkMsg_Head( UBYTE *, UBYTE *, UBYTE );
	void	Set_CommErr_MessageLine( UWORD, UBYTE *, UBYTE * );
	UBYTE	Set_ChkMsg_ErrorPages( UBYTE *, UBYTE, UBYTE *, UBYTE * );
	void	SearchNextRelayedError( UWORD * );
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_msgc.c	 	 *
**************************************************/
#if (PRO_PC_PRINT == ENABLE)
WORD	Print_PcMryOver_ChkMsg( void );
#endif
WORD 	Print_MryOver_ChkMsg(
			 UBYTE ComNumber );						/*コマンドファイル番号(0-)*/
void 	Print_MryOver_ChkMsg_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_msge.c		 *
**************************************************/
WORD 	Print_MnlErr_ChkMsg(
			 void );								/*なし*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_grp.c			 *
**************************************************/
WORD 	Print_Group_List(
			 void );								/*なし*/
WORD 	Print_Group_List_Head(
			 UBYTE Category,						/*ヘッダ種類*/
			 UBYTE Page );							/*ページ*/
void	GroupDataNextSearch(
			 register UBYTE *SoFlag,				/*短縮／ワンタッチフラグ*/
			 register UBYTE *GroupCnt );			/*データ番号*/
WORD	Print_Group_List_Specifi(
			 UBYTE Page,							/*ページ*/
			 UBYTE Line,							/*現在明細数*/
			 UBYTE SoFlag,							/*短縮／ワンタッチフラグ*/
			 UBYTE GroupCnt );						/*データ番号*/
WORD 	Print_Group_List_Common(
			 UBYTE SoFlag,							/*短縮／ワンタッチフラグ*/
			 UBYTE Number,							/*番号*/
			 UBYTE *Name,							/*名称*/
			 UDWORD Group );						/*グループ*/
void 	Print_Group_List_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_rcr.c			 *
**************************************************/
void 	Print_RxConf_List(
			 UBYTE *AscString,						/*印刷文字列*/
			 register UBYTE *AttString,				/*修飾文字列*/
			 register UBYTE Line,					/*対象行（１～）*/
			 UBYTE stack_number);
/*************************************************
*	FILE:=:\src\atlanta\src\lst_dpol.c	 	 *
**************************************************/
WORD 	Print_DelPoll_List(
			 void );								/* なし */
void 	Print_DelPoll_List_Line(
			 UBYTE Category,						/*罫線種類*/
			 register UBYTE *AscString,				/*印刷文字列*/
			 register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_msgs.c		 *
*	Add By H.Hirao 1996/06/27					 *
*************************************************/
WORD	Print_SecurityRx_MemOver( void );

/*************************************************
*	FILE:h:\src\rice\src\lst_date.c				 *
*************************************************/
void 	TimeDataAscii(
			 UBYTE DateTypeChange,
			 CONST UDWORD Current,
			 register UBYTE *AscString,
			 UBYTE line_number );
void 	SecondToMinuteSecondAsc(
			 register UWORD Second,
			 register UBYTE *AscString,
			 UBYTE Mode );
void 	SecondToHourMinuteSecondAsc(  /* added by thonda 1997/12/09 */
			 register UDWORD Second,
			 register UBYTE *AscString,
			 UBYTE Mode );
void 	MinuteToDayHourMinuteAsc(
			 register UWORD Minute,
			/* register UBYTE *AscString, */
			 UBYTE *AscString,
			 UBYTE Mode );
void 	CriterionMinuteToDayTimeAsc(
			 UDWORD Second,
			 UBYTE Kind,
			 register UBYTE *AscString );
UBYTE	DateTypeGet( void );

/************************************************************************
 * file name	\src\atlanta\\src\lst_prn.c							*
 ************************************************************************/
UWORD	GetTwiceFontData(UBYTE);	/* 8ビットフォントデータを2倍に引き伸ばし、16ビットデータを作る */
void	GetWordCharacterImage
			(UBYTE *, UBYTE *, UBYTE *, UBYTE);		/* For ANZU 96/02/20 H.Hirao */
													/* 全角１文字分のフォントイメージデータ作成 */
void	GetTwiceWordCharacterImage
			(UBYTE *, UBYTE *, UWORD *, UBYTE); 	/* For ANZU 96/02/20 H.Hirao */
													/* 全角１文字分の主走査２倍のフォントイメージデータ作成 */
void	GetByteCharacterImage
			(UBYTE, UBYTE, UBYTE *, UBYTE);
													/* 半角１文字分のフォントイメージデータ作成 */

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*  || (PRO_PRINT_TYPE == THERMAL) */
void	GetTwiceByteCharacterImage
			(UBYTE, UBYTE, UWORD *, UBYTE); 		/* 引数の型変更(ANZU) 96/01/26 H.HIRAO */
#elif (PRO_PRINT_TYPE == THERMAL)
void	GetTwiceByteCharacterImage
			(UBYTE, UBYTE, UWORD *, UBYTE); 		/* 引数の型変更(ANZU) 96/01/26 H.HIRAO */
													/* 半角１文字分の主走査２倍のフォントイメージデータ作成 */
#if defined (TWN)
void GetOneTwiceLineCharacterImage(UBYTE *,	UBYTE *, UWORD *);	/* added by H.Hirao 1999/03/11 */
#endif
#endif

void	GetOneLineCharacterImage(UBYTE *, UBYTE *, UBYTE *);
													/* １ラインフォントイメージデータ作成 */
/* void			GetOneTwiceLineCharacterImage(UBYTE *, UBYTE *, UWORD *); */ /* For ANZU 96/02/20 H.Hirao */
													/* 主走査２倍の１ラインフォントイメージデータ作成 */

WORD	CharacterPrint(
			UBYTE Mode );							/*モード*/

void	AttributeSet(
			 register UBYTE *PrnString,
			 register UBYTE *AttString,
			 CONST UBYTE *SetString,
			 UBYTE Attribute );

UBYTE	PaperSizeLen( void );

UBYTE	PaperKind( void );

/************************************************************************
 * file name	\src\atlanta\src\lst_tx.c								*
 ************************************************************************/
void	LST_SetTTI_Image(UBYTE *);					/* TTIイメージのセット */
void	LST_SetCoverPage_Image(UBYTE, UBYTE *);
													/* カバーページイメージのセット */
void	LST_SetRCR_Image(UBYTE, UBYTE *);
													/* 受信証イメージのセット */

#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  竹内 Feb.14.1995 */
	/* 中継配信不達通知イメージのセット */
	UBYTE		LST_SetCheckMsg_Image( UBYTE, UBYTE, UWORD * );
#endif


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  H.Kubo 1998/01/19  */
void	LST_SetRlyTxReportHeader_String( UBYTE *,	UBYTE *, UBYTE, UBYTE);
UBYTE	LST_LST_CheckPrintLineNumber(UBYTE number, UBYTE check);
UWORD	LST_CommErr_ChkMsg_Specifi(UBYTE *, UBYTE *, 	UBYTE);
UWORD	LST_SetRlyTxReportBody_String( UBYTE *,	UBYTE *, UBYTE,  UBYTE);
void	LST_SetRlyTxReportBody_Image(UBYTE line, UBYTE *dest, UBYTE number);
void	LST_SetRlyTxReportHeader_Image(UBYTE line, UBYTE *dest, UBYTE number, UBYTE page);
void	LST_RelayedTxReportImageTask(void);
#endif


void MLT_LST_SetTTI_Image(UBYTE *dest, UBYTE stack_number);
void MLT_LST_SetCoverPage_Image(UBYTE line,UBYTE *dest,UBYTE stack_number);
void MLT_LST_SetRCR_Image(UBYTE line,UBYTE *dest,UBYTE stack_number);
#if (PRO_CIPHER == ENABLE)
void	LST_SetCipher_Image(UBYTE line, UBYTE *dest);
#endif
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1998/06/15 Y.Murata */
void MLT_LST_SetCIL_Image(UBYTE *dest, UWORD page, UWORD *cilP, UBYTE stack_number);
#endif

/************************************************************************
 * file name	\src\atlanta\v53\src\lst_d56.c						*
 ************************************************************************/
WORD	ListOpen(void);							/* リストプリント(キャラクタ)の準備 */
void	ListPrintRunWithoutError(void);			/* 文字1ライン分を展開、DMA転送(エラー処理なし) */
WORD	ListPrintRun(void);						/* 文字1ライン分を展開、DMA転送 */
void	ListLineFeedWithoutError(UBYTE);		/* 空白をプリントする(エラー処理なし) */
WORD	ListLineFeed(UBYTE);					/* 引数分の行の空白をプリントする */
WORD	ListImagePrint(void);					/* テストパターンプリント */
WORD	ListImageLinePrint(UBYTE);				/* テストパターンプリント By M.Tachibana 1997/07/22 */
WORD	ListClose(void);						/* プリンタをクローズする(キャラクタプリント時) */
WORD	ListImagePreClose(void);				/* プリンタをクローズする(イメージプリント時のキャラクタプリント時) */
WORD	ListImageClose(void);					/* プリンタをクローズする(イメージプリント時) */
void	ListImagePrintMain(void);				/* 画像付きリストのメイン関数 */
void	LST_PrinterErrorDetectTask(void);		/* 桐用リストプリントエラー検出タスク */
void	LST_SelectPaperSize(void);				/* 桐専用リストプリント用に最適なのﾍﾟｰﾊﾟｰｻｲｽﾞをセットする */
WORD	ListSpacePrint(void);					/* 機器設定リスト用、行間挿入 (ANZU) By H.Hirao Feb 27,1996 */
WORD	ListHeadPrint(void);					/**ﾃｽﾄﾊﾟﾀｰﾝﾌﾟﾘﾝﾄ用、ﾍｯﾄﾞ挿入 (ANZU) By H.Hirao Apr.04,1996 */
/************************************************************************
 * file name	\src\rice\v53\kiri\src\lst_img.c						*
 *				(\src\rice\src\lst_ptn.cの桐版)							*
 ************************************************************************/
WORD	PrintKoushiPattern(void);					/* 格子パターン印刷 */
/* void			SetDiagonalLine(UWORD [4][2], UWORD [4][2],
									UWORD, UWORD,
									UWORD, UBYTE); */	/* 対角線セット */
/* void			ClearDiagonalLine(UWORD [4][2], UWORD [4][2], UBYTE); */
													/* 対角線クリア */
WORD	PrintMasumePattern(void);					/* 升目パターン印刷 */
/* int				PrintGrayPattern(void); */		/* グレイパターン印刷 */
/* WORD			PrintCleaningPaper(void); */		/* クリーニングペーパー印刷 */
WORD	Print_Pattern_Print(UBYTE);					/* テストパターン印刷 */
#if (PRO_PRINT_TYPE == LED )
WORD	PrintLinePattern(void);						/* 縦線、横線パターン印刷 */
WORD	PrintLinePatternImage(UBYTE, UBYTE);		/* 縦線、横線パターン印字処理 */
#endif

/*************************************************
*	FILE:i:\src\atlanta\src\lst_batb.c			 *
**************************************************/
WORD	Print_BatchTxBox_List(
			void );									/*なし*/
void	Print_BatchTxBox_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
UBYTE 	BatchTxFileDialDataToString(
			struct SYS_BatchTxDialData_t *DialData,/*変換元プログラムデータ*/
			UBYTE DialDataMax,						/*変換元プログラムデータ数*/
			register UBYTE *DialString,				/*変換先プログラムデータ文字列*/
			UBYTE LineNumber );						/*行番号*/

/*************************************************
*	FILE:i:\src\atlanta\src\lst_batd.c			 *
**************************************************/
WORD	Print_BatchTxDoc_List(
			void );									/*なし*/
WORD	Print_BatchTxDoc_Index_Specifi(
			UBYTE BoxNo );							/*なし*/

/*************************************************
*	FILE:i:\src\atlanta\src\lst_dbat.c			 *
**************************************************/
WORD	Print_DelBatchTxDoc_Notice(
			void );									/*なし*/
/*************************************************
*	FILE:i:\src\atlanta\src\lst_code.c			 *
**************************************************/
WORD	Print_DepartData_List(
			void );									/* なし */
WORD	Print_DepartData_List_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page);							/*ページ*/
void	DepartDataNextSearch(
			UBYTE *CodeCnt);						/*部門ｺｰﾄﾞデータ番号*/
WORD	Print_DepartData_List_Specifi(
			UBYTE Page,								/*ページ*/
			UBYTE Number,							/*行番号*/
			UBYTE CodeCnt);							/*部門管理ｺｰﾄﾞデータ番号*/
void	Print_DepartData_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString);				/*修飾文字列*/



WORD	Print_DepartManage_List(			/* added by thonda 1997/11/29 */
			void );									/* なし */
WORD	Print_DepartManage_List_Head(		/* added by thonda 1997/11/29 */
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page);							/*ページ*/
void	DepartManageNextSearch(				/* added by thonda 1997/11/29 */
			UBYTE *CodeCnt);						/*部門ｺｰﾄﾞデータ番号*/
WORD	Print_DepartManage_List_Specifi(	/* added by thonda 1997/11/29 */
			UBYTE Page,								/*ページ*/
			UBYTE Number,							/*行番号*/
			UBYTE CodeCnt);							/*部門管理ｺｰﾄﾞデータ番号*/
void	Print_DepartManage_List_Line(		/* added by thonda 1997/11/29 */
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString);				/*修飾文字列*/
WORD	LocateX_Page_Time_To_Time_Print(UBYTE LocateX1,UBYTE Page,UBYTE LocateX2, UBYTE LocateX3 );

/*************************************************
*	FILE:i:\src\atlanta\src\lst_spd.c			 *
*************************************************/
WORD	Print_SpeedDial_List(
			void );									/*なし*/
WORD	Print_SpeedDial_List_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page,								/*ページ*/
			UBYTE SpeedOnetouch );					/*スピードダイヤル／ワンタッチダイヤル*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
UBYTE	SpeedDataNextSearch(
			UBYTE Kind,								/*サーチ方法*/
			UBYTE *SpeedCnt,						/*短縮ダイヤルデータ番号*/
			UBYTE *SearchStr);						/*現在サーチ文字*/
#else
void	SpeedDataNextSearch(
			UBYTE Kind,								/*サーチ方法*/
			UBYTE *SpeedCnt,						/*短縮ダイヤルデータ番号*/
			UBYTE *SearchStr,						/*現在サーチ文字*/
			UBYTE *sub_dial_flag);					/* 転送先があれば1 */
#endif
void	SpeedStrEqSearch(
			UBYTE *SpeedCnt,						/*短縮ダイヤルデータ番号*/
			UBYTE *SearchStr );						/*現在サーチ文字*/
void	SpeedStrGtSearch(
			UBYTE *SpeedCnt,						/*短縮ダイヤルデータ番号*/
			UBYTE *SearchStr );						/*現在サーチ文字*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
WORD	Print_Dial_List_Specifi(
			UBYTE Kind,								/*種類*/
		 	UBYTE Page,								/*ページ*/
			UBYTE Line,								/*現在明細数*/
			UWORD DialCnt,							/*ダイヤル番号*/
			UBYTE *LineCnt );						/*印字行位置*/
#else
WORD	Print_SpeedDial_List_Specifi(
			UBYTE Page,								/*ページ*/
			UBYTE Line,								/*現在明細数*/
			UBYTE SpeedCnt,							/*短縮ダイヤル番号*/
			register UBYTE *LineCnt );				/*印字行位置*/
#endif
void	Print_Dial_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
WORD	PageTimePrint(
			UBYTE Page,								/*ページ*/
			UBYTE PagePos,							/*ページ印字場所*/
			UBYTE TimePos );						/*時間印字場所*/
WORD	PagePrint(
			UBYTE Page,								/*ページ*/
			UBYTE PagePos );						/*ページ印字場所 */
WORD	Print_Head1_Common(
			CONST UBYTE  *PrnString,				/*セット元文字列*/
			UBYTE Attribute,						/*修飾*/
			UBYTE LocateX );						/*セット元文字列ｘ方向セット位置*/
WORD	PrintDialAttributeList(
			UBYTE dial_type);						/*ワンタッチか短縮の切り替え*/
WORD	PrintSpeedDialAttrSpecifi(
			UBYTE is_page1st,						/*ページの先頭*/
			UBYTE page,								/*ページ*/
			UBYTE pos);								/*短縮セット番号*/
WORD 	PrintOnetouchDialAttrSpecifi(
			UBYTE is_page1st,						/*ページの先頭*/
			UBYTE page,								/*ページ*/
			UBYTE pos);								/*ワンタッチセット番号*/

/*************************************************
*	FILE:i:\src\atlanta\src\lst_tch.c			 *
**************************************************/
WORD	Print_OnetouchDial_List(
			void );									/*なし*/
#if (PRO_DIAL_LIST_GROUP == DISABLE)	/* by K.Watanabe 1999/05/24 */
WORD	Print_OnetouchDial_List_Specifi(
			UBYTE Page,								/*ページ*/
			UBYTE Line,								/*現在明細数*/
			UBYTE OnetouchCnt,						/*ワンタッチダイヤル番号*/
			UBYTE *LineCnt );						/*印字行位置*/
#endif
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
UBYTE	OnetouchDataNextSearch(
			UBYTE Kind,								/*サーチ方法*/
			WORD *OnetouchCnt,						/*ワンタッチダイヤルデータ番号*/
			UBYTE *SearchStr);						/*現在サーチ文字*/
#else
void	OnetouchDataNextSearch(
			UBYTE Kind,								/*サーチ方法*/
			WORD *OnetouchCnt,						/*ワンタッチダイヤルデータ番号*/
			UBYTE *SearchStr,						/*現在サーチ文字*/
			UBYTE *sub_dial_flag);					/* 転送先があれば1 */
#endif
void	OnetouchStrEqSearch(
			UBYTE *OnetouchCnt,						/*ワンタッチダイヤルデータ番号*/
			UBYTE *SearchStr );						/*現在サーチ文字*/
void	OnetouchStrGtSearch(
			UBYTE *OnetouchCnt,						/*ワンタッチダイヤルデータ番号*/
			UBYTE *SearchStr );						/*現在サーチ文字*/

/*************************************************
*	FILE:i:\src\atlanta\src\lst_prg.c			 *
**************************************************/
WORD	Print_Program_List(
			void );									/*なし*/
WORD	Print_Program_List_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page );							/*ページ*/
WORD	Print_Program_List_Specifi(
			UBYTE Page,								/*ページ*/
			UBYTE *Line,							/*現在明細数*/
			UBYTE ProgCnt,							/*プログラムダイヤル番号*/
			register UBYTE *LineCnt);				/*印字行位置*/
void	ProgDataNextSearch(
			register UBYTE *ProgCnt );				/*短縮ダイヤル番号*/
void	Print_Program_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
WORD	PrintProgramBatchLine(
			 UBYTE Page,							/*ページ*/
			 UBYTE *Line,							/*現在明細数*/
			 UBYTE ProgCnt,							/*プログラムダイヤル番号*/
			 register UBYTE *LineCnt );				/*印字行位置*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/26 By M.Kuwahara */
UBYTE	ProgDataEntryCheck( UBYTE Type, UBYTE ProgCnt);
WORD	PrintProgExtEntry( UBYTE Item, UBYTE *Page,	UBYTE *IsChangePage,register UBYTE *LineCnt );
WORD	Print_Program_List_Head_Ext( UBYTE Category, UBYTE Page, UBYTE Item);
WORD	Print_ProgEntryList_Specifi( UBYTE Page, UBYTE Line, UBYTE ProgCnt );
WORD	Print_ProgEntryStore_Specifi( UBYTE Page, UBYTE Line, UBYTE ProgCnt );
/* WORD	EntrySingleKeySpecifi( UBYTE ProgCnt, UBYTE LineCnt, UBYTE Item); */
WORD	EntrySingleKeySpecifi( UBYTE ProgCnt, UBYTE *LineCnt, UBYTE Item); /* 行数が足らないバグの対策。 changed by H.Kubo 1999/01/06 */
UBYTE	*EntryListWordingSet( UBYTE	ListItem );
 #if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* added by H.Kubo 1999/01/06 */
WORD	EntrySingleKeySeparatorSpecifi(UBYTE ProgCnt, UBYTE NextProgCnt, UBYTE LineCnt,UBYTE, UBYTE Item);
WORD	PrintProgramBatchLineSeparator(UBYTE Page, UBYTE *Line, register UBYTE *LineCnt );
 #endif
#endif

/*************************************************
*	FILE:i:\src\atlanta\src\lst_jnl.c			 *
**************************************************/
WORD	Print_Journal_List(
			void );									/*なし*/
WORD	Print_Journal_List2(
			void );									/*なし*/
WORD	Print_Journal_List_Specifi(
			struct SYS_JournalData_t JournalFile[],	/*通信記録データ*/
			UBYTE Point );							/*通信記録データ番号*/
void	JournalPointCount(
			UBYTE JournalPoint,						/*通信記録ファイル書き込み位置*/
			UBYTE JournalMax,						/*通信記録データ最大数*/
			UBYTE *Point,							/*開始位置*/
			UBYTE *Count,							/*データ数*/
			UWORD Number );							/*通信記録ファイル書き込み位置の通番*/
void	Print_Journal_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
WORD	LocateX_Page_Print( 			/* lst_mltp.cから移動 By H.Hirao Mar.08,1996 */
			UBYTE LocateX,							/*印刷桁位置-Page*/
			UBYTE Page);							/*ページ*/
WORD	Print_Journal_Head(
			UBYTE Page,								/*ﾍﾟｰｼﾞ数*/
			UBYTE Type);							/*送受区別*/
WORD	Print_TrxRcvJournal_Head(
			 UBYTE Category,						/*ヘッダ種類*/
			 UBYTE Page,							/*ページ*/
			 UBYTE TxRx );							/* 送信、受信判別フラグ*/

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
UBYTE JournalCount(UBYTE type, UBYTE stack_num, UBYTE bk_point, UBYTE internal_cnt);
UBYTE CheckJournalPrintEachLine(UBYTE stack_num, UBYTE internal_cnt);	/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/09 */
#else
UBYTE JournalCount(UBYTE type, UBYTE stack_num, UBYTE bk_point);	/* 1998/02/03 Y.Matsukuma */
UBYTE CheckJournalPrintEachLine(UBYTE stack_num);	/* ジャーナルタイトルのみ印字対応 By O.Kimoto 1999/11/09 */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
UBYTE CheckInternalLinePrintEnable(UBYTE internal_line, UBYTE Option);
#endif
/*************************************************
*	FILE:i:\src\atlanta\src\lst_dmry.c			 *
**************************************************/
WORD	Print_DelMemoryRcv_Notice(
			void );									/*なし*/
UBYTE GetDelMemoryRcvData(UBYTE line_number, UBYTE sub_line_number);	/* 引数追加 By O.Kimoto 1998/05/13 */
#if (PRO_MULTI_LINE == DISABLE ) /* (0) */
WORD	Print_DelMemoryRcv_Notice_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page );		/*ページ*/
#endif
WORD	Print_DelMemoryRcv_Specifi(
			UBYTE TxRx,								/*送受信区分*/
			struct SYS_JournalData_t *JournalFile );/*通信記録データ*/
void	Print_DelMemoryRcv_Line(
			UBYTE Category,							/*罫線種類*/
			UBYTE TxRx,								/*送受信区分*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
/*************************************************
*	FILE:i:\src\atlanta\src\lst_t30.c			 *
**************************************************/
WORD	Print_T30Monitor(
			void );									/*なし*/
WORD	Print_T30Monitor_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page );							/*ページ*/
WORD	Print_T30_Journal_Specifi(
			UBYTE TxRx,								/*送受信区分*/
			struct SYS_JournalData_t JournalFile[],	/*通信記録データ*/
			UBYTE Point );							/*通信記録データ番号*/
void	GetFrameName(
			UBYTE FrameCategory,					/*フレーム種類*/
			UBYTE FrameCode,						/*フレームコード*/
			UBYTE *FrameName );						/*フレーム名称*/
void	DataFieldSet(
			UBYTE *Data,							/*T30データ*/
			UBYTE DataSize,							/*T30データ数*/
			register UBYTE *PrnString );			/*印刷文字列*/
void	SettingName(
			UBYTE TxRxFlag,							/**ﾌﾚｰﾑ種別 */ /* 追加(ANZU) By H.Hirao Apr.11,1996 */
			UBYTE speed_handshakeflag,				/**短縮ﾊﾝﾄﾞｼｪｰｸﾌﾗｸﾞ */ /* 追加(ANZU) By H.Hirao Apr.11,1996 */
			UBYTE Frame,							/*フレームコード*/
			UBYTE *Data,							/*T30データ*/
			UBYTE DataSize,							/*T30データ数*/
			register UBYTE *PrnString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
void	SettingSpeed(
			UBYTE Data,								/*T30データ*/
			register UBYTE *PrnString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
UBYTE	Xmask(
			UBYTE FrameCode );						/*フレームコード*/
WORD	Tsk_Dump(
			void );									/*なし*/
WORD	Tsk_Dump_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page );							/*ページ*/
UBYTE	CheckEndOfFrame(
			UWORD Point );							/*T30ﾃﾞｰﾀ位置*/
WORD	Memory_Dump(
			void);
WORD	Memory_Dump_Head(
			UBYTE Category);						/*ﾍｯﾀﾞ種類*/
WORD	Memory_Dump_1Line(
			UBYTE *LineCnt);						/*ﾍﾟｰｼﾞの行数*/
WORD	Dpram_Dump(
		 	void );									/*なし*/
WORD	Dpram_Dump_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page );							/*ページ*/
WORD	MemoryDumpList(
			void);
WORD	MemoryDumpListHead(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page);							/*ページ*/

/*************************************************
*	FILE:i:\src\atlanta\src\lst_fnc.c			 *
**************************************************/
WORD	Print_Function_List(
			void );									/*なし*/
void	Print_Function_List_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
#if 0
UBYTE	FuncTableEndCheck(
			UBYTE TableNumber,						/*FuncTableSw番号*/
			UBYTE TableBit );						/*FuncTableSwﾋﾞｯﾄ位置*/
void	FuncCountryTableCopy(UBYTE Type);			/*OPR or LST*/
void	SettingsFuncCountryTableCopy(UBYTE Type);	/*OPR or LST*/
WORD	PrintProjectList(void);						/* プロジェクトリスト */
#endif

void	LST_RemoveAscString1stSpace(
			UBYTE *NoSpaceAscString,				/* スペースを取り除いた後のアスキー文字列 */
			UBYTE *AscString );						/* キャラクタ文字列 */

#if (PRO_PANEL == KANJI)
UBYTE IsFunctionEnable(	UBYTE func_no);					/** 機能設定番号 */
UBYTE IsSettingEnable(	UBYTE func_no);					/** 機器設定番号 */
WORD PrintFunctionListFunction( void );
WORD PrintFunctionListSettingFunc(	UBYTE func_no);		/** 機能番号 */
WORD PrintFunctionListFuncMenu(	UBYTE func_no);			/* 機能番号 */
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_prm.c			 *
**************************************************/
WORD	Print_Parameter_List(
			void );									/*なし*/
#if (0)
WORD	Print_Parameter_List2(
		 	UBYTE	set_no );							/*処理番号*/
#endif
UBYTE	GetParameterLine(
		 	UBYTE	set_no );						/*処理番号*/
#if (0)
WORD	Print_Parameter_Head(
			UBYTE Category,							/*ヘッダ種類*/
			UBYTE Page);							/*ページ*/
#endif
WORD	Print_Parameter_Head(
			 UBYTE Category,						/*ヘッダ種類*/
			 UWORD *LineDot);						/*残りラインドット数*/
WORD	Machine_Setting_RS232C(
			UWORD *LineDot);						/*残りラインドット数*/ /* 変更 S.Fukui Sep.17,1997 */
void	Param_set(
			register UBYTE *Prn_Str,				/*印刷文字列*/
			register UBYTE *Att_Str,				/*修飾文字列*/
			UBYTE Status,							/*項目番号*/
			UBYTE WideX,							/*１項目の間隔*/
			UBYTE *W_Pt[] );						/*項目名称*/
void	Machine_Setting_Line(
			UBYTE Category,							/*罫線種類*/
			register UBYTE *AscString,				/*印刷文字列*/
			register UBYTE *AttString );			/*修飾文字列*/
WORD	Machine_Setting_Middle(
			void );									/*なし*/
WORD Print_MultiParameter(UWORD *LineDot);			/*残りラインドット数*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_fry.c			 *
**************************************************/
WORD	Print_Fact_Menu(
			void );									/*なし*/
/*************************************************
*	FILE:=:\src\atlanta\src\lst_cl1.c			*
**************************************************/
WORD	PrintClass1Monitor( void );
void	SelectSpeedWording( UBYTE number );
void	TenMSecondToMinuteSecondASC(
			UWORD tenmmsec,							/** 変換元10m秒値 */
			UBYTE *ascstring );						/** 変換先文字列 */

#if (PRO_F_CODE == ENABLE)
/*************************************************
*	FILE:=:\src\atlanta\src\lst_box.c	 		*
**************************************************/
WORD	Print_F_CodeBox_List( void );
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
WORD	Print_Box_List_Head(
					 UBYTE Category,				/*ヘッダ種類*/
					 UBYTE Page, 					/*ページ*/
					 UBYTE BoxCnt );				/*ＢＯＸ番号*/
WORD	Print_BoxExecData_Specifi( 
					 UBYTE	*Line, 					/*配信明細行*/
					 UBYTE	*LineCnt, 				/*印字行位置*/
					 UBYTE	*Item, 					/*出力項目番号*/
					 UBYTE	BoxCnt );				/*ＢＯＸ番号*/
#else
WORD	Print_Box_List_Head(
					 UBYTE Category,				/*ヘッダ種類*/
					 UBYTE Page );					/*ページ*/
#endif
void	F_CodeDataNextSearch(
					 UBYTE SoFlag,					/*検索種類*/
					 register UBYTE *DataCnt );		/*データ番号*/
WORD	Print_Box_List_Specifi(
					 UBYTE Page,					/*ページ*/
					 UBYTE Line,					/*現在明細数*/
					 UBYTE BoxCnt );				/*ＢＯＸ番号*/
void	Print_F_CodeBox_List_Line(
					UBYTE Category,				 	/*罫線種類*/
					register UBYTE *AscString,	 	/*印刷文字列*/
					register UBYTE *AttString ); 	/*修飾文字列*/
void	OptionToShortString(
					UBYTE OptionData,				/*ｵﾌﾟｼｮﾝﾃﾞｰﾀ*/
					register UBYTE* OptionString );	/*ｵﾌﾟｼｮﾝ文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_ddoc.c	 		*
**************************************************/
WORD	Print_Del_F_CodeBoxDoc_Notice( UBYTE mode );
WORD	Print_Del_F_Code_Notice_Head(
						 UBYTE Category,			/*ヘッダ種類*/
						 UBYTE Page );				/*ページ*/
void	Print_Del_F_Code_Notice_Line(
					UBYTE Category,				 	/*罫線種類*/
					register UBYTE *AscString,	 	/*印刷文字列*/
					register UBYTE *AttString ); 	/*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_fcdd.c	 		*
**************************************************/
WORD	Print_F_CodeDoc_List( void );
WORD	Print_CodeDoc_List_Head(
					 UBYTE Category,	/*ヘッダ種類*/
					 UBYTE Page );		/*ページ*/
void	Print_F_CodeDoc_List_Line(
					 UBYTE Category,				 /*罫線種類*/
					 register UBYTE *AscString,		 /*印刷文字列*/
					 register UBYTE *AttString);	 /*修飾文字列*/
WORD	Print_CodeDoc_List_Specifi(
					 UBYTE Page,		/*ページ*/
					 UBYTE Line,		/*現在明細数*/
					 UBYTE BoxCnt );	/*ＢＯＸ番号*/
WORD	Print_F_CodeDocNo_Specifi(
					 UBYTE BoxNo );		/*サブアドレスＢｏｘＮｏ．*/
UBYTE	Get_CodeDocCount(
					 UBYTE BoxNo ); 	/*サブアドレスＢｏｘＮｏ．*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_rx.c	 		*
**************************************************/
WORD	Print_F_CodeBoxRcv_Notice(
					UBYTE	BoxNumber,		/*Ｂｏｘ*/
					UBYTE	FileNumber );	/*ファイル番号*/
#endif /* (PRO_F_CODE == ENABLE) */

/*************************************************
*	FILE:=:\src\atlanta\src\lst_junk.c	 		*
**************************************************/
WORD	Print_BlockJunkFax_List( void );
WORD	Print_BlockJunkFax_List_Head(
					 UBYTE Category,	/*ヘッダ種類*/
					 UBYTE Page );		/*ページ*/
WORD	Print_BlockJunk_List_Specifi(
					 UBYTE Page,			/* ﾍﾟｰｼﾞ */
					 UBYTE Line,			/* 行数 */
					 UBYTE *DialCnt );		/*ＢＯＸ番号*/
void	Print_BlockJunk_List_Line(
					UBYTE Category,				 /*罫線種類*/
					register UBYTE *AscString,	 /*印刷文字列*/
					register UBYTE *AttString);	 /*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_serv.c	97.05.20 *
**************************************************/
WORD	Print_ServiceReport( void );
WORD	ServiceReport_Head(
					 UBYTE Category,		/*ヘッダ種類*/
					 UBYTE Page);			/*ページ*/
WORD	Print_ServiceReport_Specifi(
					 UBYTE SetNo );			/* 処理番号 */
UBYTE	Get_FaxComErrorLine( void );
WORD	Print_FaxComError_Specifi(
					 UBYTE	err_line,
					 UBYTE	stack_cnt );
#if (PRO_CIPHER == ENABLE)
/*************************************************
*	FILE:=:\src\atlanta\src\lst_cph.c	97.06.12 *
**************************************************/
WORD	Print_CipherRecieve_Notice( void );
void	Print_CipherRecieve_List_Line(
					 UBYTE Category,				/*罫線種類*/
					 register UBYTE *AscString,		/*印刷文字列*/
					 register UBYTE *AttString);	/*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_keyb.c	97.06.13 *
**************************************************/
WORD	Print_KeyBook_List( void );
void	Print_KeyBook_List_Line(
					 UBYTE Category,				/*罫線種類*/
					 register UBYTE *AscString,		/*印刷文字列*/
					 register UBYTE *AttString );	/*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_key.c	97.06.13 *
**************************************************/
WORD	Print_KeyWord_List( void );
void	Print_KeyWord_List_Line(
					 UBYTE Category,				/*罫線種類*/
					 register UBYTE *AscString,		/*印刷文字列*/
					 register UBYTE *AttString );	/*修飾文字列*/

/*************************************************
*	FILE:=:\src\atlanta\src\lst_dcph.c	97.11.21 *
**************************************************/
WORD	Print_DelScrambleRx_List( void );
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_ord.c	97.09.19 *
**************************************************/
WORD	Print_ConsumerOrder_Sheet( void );

#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_text.c	97.01.27 *
**************************************************/
#if(0)
WORD Print_TextFile( void );
UWORD MEM_ReadOpen (struct MEM_IndexData_t *, struct MEM_ExecData_t *);
UDWORD MEM_CaluclateDMAAddress( UWORD );
UWORD MEM_ReadGetNextBlockNo( UWORD );
/*UBYTE CharAttributeSet( UBYTE );*/
UBYTE CharAttributeSet( UWORD );
UBYTE SequelExistCheck( UDWORD, UWORD, UWORD );
#endif

/*************************************************
*	FILE:=:\src\atlanta\src\lst_cost.c
**************************************************/
short  Print_CostTable_List(void);
short  Print_CostTable_List_Head(unsigned char  Category,unsigned char  Page);
void  CostDataNextSearch(unsigned char  *CostCnt);
short  Print_CostTable_List_Specifi(unsigned char  Page,unsigned char  Line,unsigned short  CostCnt);
void  Print_Cost_Keta(unsigned char  *AscString);
void  Print_CostTable_List_Line(unsigned char  Category,unsigned char  *AscString,unsigned char  *AttString);
WORD	LocateX_Page_Time_Print(UBYTE LocateX1,UBYTE Page,UBYTE LocateX2 );
/* FILE:i:\src\atlanta\src\lst_jnl.c でも宣言されているので削除 By S.Fukui Dec.1,1997 
***  WORD	LocateX_Page_Print(UBYTE LocateX,UBYTE Page );  ***/

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/************************************************************************
 * プロトタイプ宣言
 * 1998/03/31 Y.Tanimoto
 * LST_INF.C
 ************************************************************************/
WORD	LST_PrintRxTextMail( void );
UBYTE	SetOneLineData( UBYTE * );
UBYTE	ReadNextData( void );
WORD	PrintReturnedMailTextPart( UBYTE );
WORD	LST_PrintMailAddressList( void );
UBYTE	MailAddressNextSearch( UBYTE, UBYTE );
UBYTE	MailOnetouchStrEqSearch( UBYTE );
UBYTE	MailOnetouchStrGtSearch( void );
WORD	PrintMailAddressListHead( UBYTE, UBYTE * );
WORD	PrintMailHeadCommon( CONST UBYTE *, UBYTE, UBYTE );
WORD	PrintMailAddressListSpecifi( UBYTE );
void	PrintMailAddressListLine( UBYTE, register UBYTE *, register UBYTE * );
WORD	LST_PrintMailGroupList( void );
UBYTE	MailGroupNextSearch( UBYTE );
WORD	PrintMailGroupListHead( UBYTE, UBYTE * );
UBYTE	MailGroupLineCount( UBYTE );
WORD	PrintMailGroupListSpecifi( UBYTE, UBYTE );
void	PrintMailGroupListLine( UBYTE, register UBYTE *, register UBYTE * );
WORD	LST_PrintMailSettingList( void );
WORD	PrintMailSettingListHead( UBYTE, UBYTE * );
void	PrintMailSettingListLine( UBYTE, register UBYTE *, register UBYTE * );
UBYTE	PrintMailSettingListSpecifi( UBYTE, UBYTE, register UBYTE *, register UBYTE * );
WORD	LST_PrintErasedCommandNotice( void );
WORD	LST_PrintMailCommandList( void );
WORD	PrintMailComListHead( UBYTE, UBYTE *, UBYTE );
WORD	PrintMailComUserName( UBYTE, UBYTE );
UBYTE	MailCommandNextSearch( UBYTE, UBYTE );
UBYTE	GetMailCommandSpecific( UBYTE );
WORD	PrintMailComListSpecifi( UBYTE, UBYTE *, UBYTE );
WORD	LST_PrintErasedRxMailNotice( void );
WORD	PrintMailReceiverName( UBYTE, UBYTE );
WORD	LST_PrintMailComCheckMsg( void );
WORD	PrintMailCheckMsgHead( UBYTE, UBYTE *, UBYTE );
WORD	PrintMailCheckMsgTitle( UBYTE * );
WORD	MailComCheckMsgChangePage( UBYTE, UBYTE *, UBYTE );
WORD	PrintMailCheckMsgSpecifi( UBYTE );
WORD	PrintMailCheckMsgOption( UBYTE, UBYTE *, UBYTE );
UBYTE	ConvertOneLineTextData( UBYTE * );
WORD	LST_PrintSecureRxNotice( void );
WORD	PrintReceiveReportTitle( void );
WORD	PrintReceiveReportHead( UBYTE, UBYTE *, UBYTE );
UBYTE	GetFirstSecureMailBox( UBYTE, UBYTE );
UBYTE	GetNextSecureMailBox( UBYTE, UBYTE );
WORD	PrintReceiveReportSpecific( UBYTE );
WORD	LST_PrintJournalReport(void);
WORD	PrintJournalReportTitle(UBYTE , UBYTE *);
WORD	PrintJournalReportHead(UBYTE *, UBYTE );
/*WORD	PrintJournalReportSpecific(UBYTE, UBYTE *); 1998/05/22 Eguchi */
WORD	PrintJournalReportSpecific(UBYTE *); /*1998/05/22 Eguchi */
void	PrintMailJournalListLine(UBYTE , UBYTE *, UBYTE *, UBYTE);
void	ReadMailJournal(UBYTE); /* 1998/05/22 Eguchi */
WORD	LST_INF_Monitor(void);
UDWORD MonitorOneLineSet(UBYTE *,UDWORD ,UDWORD);


#endif	/* end of PRO_DIALUP_INTERNET_FAX */

/***************************************************
*	FILE:=:\src\atlanta\src\lst_mcr.c	1998.06.24 *
****************************************************/
#if (PRO_KEY_MACRO == ENABLE)
WORD	Print_KeyMacro_List(void);
void	Print_KeyMacroList_Line(UBYTE, register UBYTE *, register UBYTE *);
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/***************************************************
*	FILE:=:\src\atlanta\src\lst_nd.c	1998.06.24 *
****************************************************/
WORD	Print_ND_List(void);
WORD	Print_ND_List_Head(UBYTE, UBYTE);
UBYTE	ND_DataNextSearch(UBYTE);
WORD	Print_ND_List_Specifi(UBYTE *, UBYTE, UBYTE *, UBYTE, UBYTE *);
void	Print_ND_List_Line(UBYTE, register UBYTE *, register UBYTE *);

/***************************************************
*	FILE:=:\src\atlanta\src\lst_ndj.c	1998.10.01 *
****************************************************/
WORD	Print_INF_ND_List(void);
WORD	Print_INF_ND_Head(UBYTE, UBYTE);
WORD	Print_INF_ND_Specifi(UBYTE, UBYTE);
void	Print_INF_ND_Line(UBYTE, register UBYTE *, register UBYTE *);
#endif

/***************************************************
*	FILE:=:\src\atlanta\src\lst_warp.c	1998.06.24 *
****************************************************/
#if (PRO_RX_DOC_TRANSFER == ENABLE)
WORD	Print_Warp_List(void);
WORD	PrintWarpList_Head(UBYTE, UBYTE);
UBYTE	WarpDataNextSearch(UBYTE);
WORD	PrintWarpList_Specifi(UBYTE, UBYTE *, UBYTE, UBYTE *);
void	PrintWarpList_Line(UBYTE, register UBYTE *, register UBYTE *);
void 	WarpTimeDataSet(struct SYS_SubDialData_t *, register UBYTE *);
void 	SetLstWeekData(UBYTE, UBYTE	*);
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
WORD	PrintComResultList( void );
#endif
