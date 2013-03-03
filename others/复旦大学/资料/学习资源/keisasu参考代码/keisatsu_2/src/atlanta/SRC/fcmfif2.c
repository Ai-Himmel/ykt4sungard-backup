/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMFIF2.C												 */
/*	モジュール	 :															 */
/*				 : SetUpMemoryRx()											 */
/*				 : SetDocumentMemorySizeFrame()								 */
/*				 : CheckPollingTxType()										 */
/*				 : SetUpRxDocumentPollingTx()								 */
/*				 : SetRestMemoryFrame()										 */
/*				 : SetUpSecureMailRx()										 */
/*				 : SetUpSecureMailTx()										 */
/*				 : SetUpBufferingRx()										 */
/*				 : GetGroupNoFromStdID()									 */
/*				 : CountRelayedTxCommand()									 */
/*				 : SetUpRelayBroadCastRx()									 */
/*				 : GetDatabasePollingFileNumber()							 */
/*				 : SetUpRemoteFaxRx()										 */
/*				 : SetPasscodeFrame()										 */
/*				 : SetSecureMailFieldFrame()								 */
/*				 : SetDatabasePollingDataFrame()							 */
/*				 : SetRelayedBroadcastGroupFrame()							 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSMAILB.H"
#include "\src\atlanta\define\SYSDIAL.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\UNI_PRO.H"

#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\OPR_PRO.H"
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\OPR_PRO.H"
#endif
#include "\src\atlanta\define\status.H"		/* 1998/01/21  By T.Yamaguchi */

/* MDM */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/*--------------------------------------------------*/
/*	  TSIによる中々継指示 14.Feb'95 Y.Suzuki		*/
/*--------------------------------------------------*/
#if(PRO_TSI_RELAY_COM == ENABLE)
 #include "\src\atlanta\ext_v\ROM_TBL.h"
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* ワープ機能 By H.Hirao 1998/08/31 */
 #include "\src\atlanta\define\syswarp.h"
 #include "\src\atlanta\define\sysnd.h"
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/10/19 By M.Kuwahara */
 #include "\src\atlanta\define\cmn_nd.h"
#endif

/*************************************************************************
	module		:[メモリ受信準備]
	function	:[
		1.メモリ受信
	]
	return		:[準備完了:YES ＮＧ:NO]
	common		:[]
	condition	:[]
	comment		:[修正履歴
				1.94/9/8 代行バッファステータスの変更は、メインタスクにて行う。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/05/06]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetUpMemoryRx(void)
{
	/*struct SYS_MemoryRxPrintData_t far *MemoryRxPrintPoint;* 29.Apr'94 */
	/*UBYTE j;*/

	if (CMN_CheckMemoryReceiveEnable() == TRUE) {
		/**	代行受信バッファ、メモリに空きがあれば、メモリ受信	*/
		SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;/*	通常のメモリ受信	*/
		SYS_RxMemoryFileNo = SYB_MemoryRxPrintWritePoint;
		SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;

	/* man_main.c MSG_RX_PRINT_PAGE 受信後にセットしているのでここではやらない。8.Sep'94
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
		MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
	*/
		return(YES);
	}
	else {/**	空きがなければ、エラー処理	*/
		SYS_RxMemoryFileItem = NULL;/* 通信で使用中にしたプリンタを開放するため */
		return(NO);
	}
	return(NO);
}


/*************************************************************************
	module		:[ＮＳＳフレームに原稿メモリ容量セット]
	function	:[
		原稿メモリ使用容量をＮＳＳフレームにセットする
	]
	return		:[モデムバッファのポインタ]
	common		:[モデムバッファ]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/5/2]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetDocumentMemorySizeFrame(WORD pos)					/*	モデムバッファのポインタ	*/
{
	UWORD page;
	long block;
	UWORD no;

	page = 0;
	block = 0;
	no = 0;

	/* DBポーリング,バッチ送信の場合 */
	if((SYS_DocBlock.Index.Item == SYS_MEM_DB_POLLING_FILE) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE1) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE2) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE3) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE4) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE5)) {
		for(no = TxMemoryFileCurrentExecutingNo;TxMemoryFileNo[no] != 0xFFFF; no++) {
			block += MEM_CountTotalBlock(SYS_DocBlock.Index.Item,TxMemoryFileNo[no], MEM_IGNORE_BOX_NUMBER);
			page += MEM_CountTotalPage(SYS_DocBlock.Index.Item,TxMemoryFileNo[no], MEM_IGNORE_BOX_NUMBER);
		}
	}
	/* Ｆコードの処理を入れる事1997/03/12  By T.Yamaguchi */
	else if((SYS_DocBlock.Index.Item == SYS_MEM_SUB_SECURE_FILE)
		 || (SYS_DocBlock.Index.Item == SYS_MEM_SUB_BULLETIN_FILE)) {
		for(no = TxMemoryFileCurrentExecutingNo;TxMemoryFileNo[no] != 0xFFFF; no++) {
			block += MEM_CountTotalBlock(SYS_DocBlock.Index.Item,TxMemoryFileNo[no],SYS_DocBlock.Index.BoxNumber );
			page += MEM_CountTotalPage(SYS_DocBlock.Index.Item,TxMemoryFileNo[no],SYS_DocBlock.Index.BoxNumber );
		}
	}
	/* DBポーリング以外なら、*/
	else {
		block = MEM_CountTotalBlock(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, MEM_IGNORE_BOX_NUMBER);
		page = MEM_CountTotalPage(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, MEM_IGNORE_BOX_NUMBER);
	}
	/**	使用ページ数セット	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)page;
	pos++;
	/*１ブロック1024バイトに換算*/
	block *= MEM_BLOCK_SIZE;/* バイトサイズ */
	block /= 1024;
	/**	使用ブロック数セット	*/
	/*	下位	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)(0x000000FF & block);/*	下位の１バイトにｃａｓｔされるか要確認	*/
	pos++;
	/*	上位	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)((0x0000FF00 & block) >> 8);/*	下位の１バイトにｃａｓｔされるか要確認	*/

	/**	リターンモデムバッファのポインタ	*/
	return(pos);
}



/*************************************************************************
	module		:[受信原稿ポーリング送信種別確定]
	function	:[
		1.4つのメモリスイッチを見て、種別を確定する
		優先順位	代行受信　＞　親展受信　＞　ＦＩＰ受信　＞　送信予約原稿（とりあえず）
	]
	return		:[
					RX_DOC_POLLING_TX			:代行受信原稿ポーリング送信
					SECURE_DOC_POLLING_TX		:親展受信原稿ポーリング送信
					FIP_DOC_POLLING_TX			:ＦＩＰ受信原稿ポーリング送信
					TX_DOC_POLLING_TX			:送信予約原稿ポーリング送信
					NO							:受信原稿ポーリング送信なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/03/25]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckPollingTxType(void)
{
	if(CHK_UNI_RxDocToPollingDoc()) {
		return(RX_DOC_POLLING_TX);
	}
	else if(CHK_UNI_SecureDocToPollingDoc()) {
		return(SECURE_DOC_POLLING_TX);
	}
#if(PRO_FIP == ENABLE)
	else if(CHK_UNI_FIP_DocToPollingDoc()) {
		return(FIP_DOC_POLLING_TX);
	}
#endif
	else if(CHK_UNI_TxDocToPollingDoc()) {
		return(TX_DOC_POLLING_TX);
	}
#if (PRO_CIPHER == ENABLE)/*By Y.Suzuki 1998/10/07*/
	else if(CHK_UNI_ScrambleDocToPollingDoc()) {
		return(SCRAMBLE_DOC_POLLING_TX);
	}
#endif
	return(0);
}

/*************************************************************************
	module		:[受信原稿ポーリング送信準備]
	function	:[
		1.メモリスイッチ確認　どれか、１つのメモリスイッチにのみ対応
		2.親展原稿の場合／ＦＩＰ受信原稿の場合
		  ･受信原稿の有無チェック
		  ･送信ファイルアイテム,ナンバー､ページセット
		  ･存在する、ファイルナンバーの小さい順にセットする
		3.代行受信原稿の場合
		  ･受信原稿の有無チェック
		  ･送信ファイルアイテム,ナンバー､ページセット
		  ･受信した順番にセットする
		4.送信メモリファイルの次のバッファに0xFFFFを入れる
	]
	return		:[セットアップ完了:YES	ＮＧ:NO]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/03/25]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetUpRxDocumentPollingTx(void)
{
	UWORD  page;
	UBYTE a;
	UBYTE b;
	UBYTE end_point;
	UBYTE ok_flag;
	UBYTE abort_flag;

	a = 0;
	b = 0;
	abort_flag = 0;
	ok_flag = NO;
	page = 0;
	if(RxDocumentPollingTxFlag == RX_DOC_POLLING_TX) {/* 代行受信原稿の場合	*/
		/*b = (UBYTE)(SYB_MemoryRxPrintWritePoint);By Y.Suzuki 1998/09/25 */
		if ((SYB_MemoryRxPrintWritePoint < 0) || (SYS_MEMORY_RX_MAX <= SYB_MemoryRxPrintWritePoint)) {
			/* 代行受信フル、メモリー残量なし時は、0xffとなっている。By Y.Suzuki 1998/09/25 */
			b = 0;
		}
		else {
			b = (UBYTE)(SYB_MemoryRxPrintWritePoint);
		}
		if (b == 0) {
			end_point = (UBYTE)(SYS_MEMORY_RX_MAX - 1);
		}
		else {
			end_point = (UBYTE)(b - 1);
		}
	}
	/*for (a = 0; a < (SYS_TX_MEMORY_FILE_NO_MAX); b++) [@** 取り出せるファイルNOの数 By Y.Suzuki 1998/09/16 */
	for (a = 0; a < (SYS_MEMORY_RX_MAX); b++) {/** 取り出せるファイルNOの数 */
		switch(RxDocumentPollingTxFlag) {
		case SECURE_DOC_POLLING_TX:
			/**	親展受信原稿ポーリング送信スイッチＯＮ	*/
			if(b < SYS_MAILBOX_MAX) {/**	メイルボックス０－－９の受信原稿の有無をチェックする	*/
				if(SYB_MailBox[b].Status == SYS_MAILBOX_RECEIVE) {
					page = MEM_CountFinalPage(SYS_MEM_SECURE_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
					if(page != MEM_NO_INDEX) {/** 受信原稿あり	*/
						ok_flag = YES;
						TxMemoryFileNo[a] = b;/**	送信ファイルＮＯ,ページセット	*/
						PollingTxFilePage[a] = page;
						a++;
					}
				}
			}
			else {/**	チェック終了	*/
				if(ok_flag) {/**	送信ファイルアイテムセット	*/
					TxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_SECURE_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
 #if(PRO_FIP == ENABLE)
		case FIP_DOC_POLLING_TX:
			/**	ＦＩＰ受信原稿ポーリング送信スイッチＯＮ	*/
			page = MEM_CountTotalPage(SYS_MEM_FIP_FILE, 0, MEM_IGNORE_BOX_NUMBER);
			if(page != MEM_NO_INDEX) {/** 受信原稿あり	*/
				ok_flag = YES;
				TxMemoryFileItem = SYS_MEM_FIP_FILE;/**	送信ファイルアイテムセット	*/
				TxMemoryFileNo[a] = 0;/**	送信ファイルＮＯ,ページセット	*/
				PollingTxFilePage[a] = page;
				a++;
				abort_flag = 1;
				TxMemoryFilePage = SYS_TxTotalPage + 1;
			}
			break;
#endif
		case RX_DOC_POLLING_TX:
			/**	代行受信原稿ポーリング送信スイッチＯＮ	*/
			if (b > (SYS_MEMORY_RX_MAX - 1)) b = 0;/* 代行受信バッファ[0--9] */
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
			if(SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_PRINT) {
#else
			if ((SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_PRINT)
			 || (SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_FAST_PRINT)) {
#endif
				page = MEM_CountFinalPage(SYS_MEM_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
				if(page != MEM_NO_INDEX) {/** 受信原稿あり	*/
					ok_flag = YES;
					TxMemoryFileNo[a] = b;/**	送信ファイルＮＯ,ページセット	*/
					PollingTxFilePage[a] = page;
					a++;
				}
			}
			if(b == end_point) {	/* 修正 1997/04/01  By T.Yamaguchi */
				if(ok_flag) {/**	送信ファイルアイテムセット	*/
					TxMemoryFileItem = SYS_MEM_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
		case TX_DOC_POLLING_TX:
			/**	送信予約原稿ポーリング送信スイッチＯＮ　処理は、代行と同じ処理をとりあえず入れておく	*/
			abort_flag = 1;/* 追加 14.Mar'95 Y.Suzuki */
			ok_flag = NO;
			TxMemoryFilePage = SYS_TxTotalPage + 1;
			break;
#if (PRO_CIPHER ==ENABLE)/*By Y.Suzuki 1998/10/07*/
		case SCRAMBLE_DOC_POLLING_TX:
			/**	スクランブル受信原稿ポーリング送信スイッチＯＮ	*/
			if(b < SYS_CIPHERBOX_MAX) {/**	メイルボックス０－－９の受信原稿の有無をチェックする	*/
				if(SYB_CipherBox[b].Status == SYS_CIPHERBOX_RECEIVE) {
					page = MEM_CountFinalPage(SYS_MEM_CIPHER_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
					if(page != MEM_NO_INDEX) {/** 受信原稿あり	*/
						ok_flag = YES;
						TxMemoryFileNo[a] = b;/**	送信ファイルＮＯ,ページセット	*/
						PollingTxFilePage[a] = page;
						a++;
					}
				}
			}
			else {/**	チェック終了	*/
				if(ok_flag) {/**	送信ファイルアイテムセット	*/
					TxMemoryFileItem = SYS_MEM_CIPHER_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_CIPHER_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
#endif
		}
		if(abort_flag == 1) {
			break;
		}
	}
	if (ok_flag == NO) {	/**	指定されたファイルのページ数が全て０以下	*/
		return(NO);/**	リターン０	*/
	}
	/**	送信メモリファイルの次のバッファに0xFFFFを入れる	*/
	TxMemoryFileNo[a] = 0xFFFF;
	PollingTxFilePage[a] = 0xFFFF;
	/**	リターン1 送信ファイルページセット	*/

	/* 代行受信原稿を何枚かプリントした後（原稿が消された後）に、プリンタが止まった場合
	**	代行受信原稿をポーリング送信できない（１ページ目の原稿が消えているから）で途中の原稿からでもポーリング送信できる
	**	ようにTxMemoryFilePageに一番小さいpageをセットする様に変更	 1997/02/08	 By T.Yamaguchi
	TxMemoryFilePage = SYS_TxTotalPage + 1;
	*/

#if (0) /* 受信原稿ポーリング取り出し修正分 各RxDocumentPollingTxFlagごとにセットするように変更します by T.Soneoka 1997/02/21 */
//	TxMemoryFilePage = MEM_CheckMostSmallPage(TxMemoryFileItem,TxMemoryFileNo[0]);
//	PollingTxFilePage[0] = (PollingTxFilePage[0] + TxMemoryFilePage - 1);
#endif
	return (YES);
}


/*************************************************************************
	module		:[メモリ残量チェック]
	function	:[
		NSF､NSC のメモリ容量フィールドをセットする
	]
	return		:[モデムバッファのポインタ]
	common		:[モデムバッファ]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetRestMemoryFrame(
				UBYTE FrameName,	/*	NSC,NSS,NSF	*/
				WORD pos)					/*	モデムバッファのポインタ	*/
{
 #if 0 /* (PRO_PRINT_TYPE != LASER) 1997/03/22  By T.Yamaguchi */
//	UWORD page;
//	DWORD block;
//
//	page = 0;
//	block = 0;
//
//	page = MEM_CountTotalEmptyPage();
//	block = MEM_CountTotalEmptyBlock();
//	block *= MEM_BLOCK_SIZE;/* バイトサイズ */
//	block /= 1024;
//
//	/**	空き頁数セット	*/
//	if(page > 0x00FF) {/* 紅葉 */
//		MDM_ModemBuffer[InNS][pos] = 0xFF;
//	}
//	else {
//		MDM_ModemBuffer[InNS][pos] = (UBYTE)page;/* さつき、ラベンダーは、MAX 42､106(インデックス) */
//	}
//	pos++;
//	/**	空きブロック数セット	*/
//	/*	上位	*/
//	MDM_ModemBuffer[InNS][pos] = (UBYTE)(block & 0x000000FF);
//	pos++;
//	block &= 0x0000FF00;
//	block >>= 8;
//	/*	下位	*/
//	MDM_ModemBuffer[InNS][pos] = (UBYTE)block;
//#else
#endif
	switch (FrameName) {		/**	フレーム名	*/
		case NSF_F:	/**	NSF	*/
		case NSC_F:	/**	NSC	*/
			/**	FFを３バイトセット	*/
			MDM_ModemBuffer[InNS][pos] = 0xFF;
			MDM_ModemBuffer[InNS][++pos] = 0xFF;
			MDM_ModemBuffer[InNS][++pos] = 0xFF;
			break;
		case NSS_F:	/**	NSS	*/
			/**	00を３バイトセット	*/
			MDM_ModemBuffer[InNS][pos] = 0x00;
			MDM_ModemBuffer[InNS][++pos] = 0x00;
			MDM_ModemBuffer[InNS][++pos] = 0x00;
			break;
	}
/*  #endif */
	/**	リターンモデムバッファのポインタ	*/
	return(pos);
}


/*************************************************************************
	module		:[独自フレームに自社モードをセットする]
	function	:[
		1.ミランの場合は、ＦＸコードをセットする。
	]
	return		:[]
	common		:[
					MDM_ModemBuffer
					InNS
					MAKERCODE_POS
					OwnMakerCode
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/28]
	author		:[鈴木郁二]
*************************************************************************/
void SetMakerCodeFrame(void)
{
	MDM_ModemBuffer[InNS][MAKERCODE_POS] = OwnMakerCode;
	return;
}


/* ここより下ＭＭＬ専用 */
#if(PRO_MAKER == MML)
/*************************************************************************
	module		:[親展受信準備]
	function	:[
		1.親展受信可能なら受信ファイルのセットアップを行う
		2.NSSにより指定されたメイルボックスNO.の取り出し
		3.自機に指定されたメイルボックスが存在する
		4.メイルボックスの受信状態
		5.メイルボックス内相手先ＩＤ登録（同じメイルボックスに異なるＩＤの
		. ＦＡＸから受信すると最後に受信したＩＤのみ有効）
	]
	return		:[ＯＫ--YES／ＮＧ--NO]
	common		:[
				NonStdFrm
				RxMemoryFileItem
				RxMemoryFileNo
				Mailbox.:Status
				FipSecureStartPage
				SYB_TTI_ID_Buffer
				OwnMakerCode
				Mailbox.:RemoteName
				SYS_TTI_buffer
	]
	condition	:[]
	comment		:[メモリ残量チェックしていない メモリなし機は親展受信なし
				  親展受信のﾍﾟｰｼﾞNoのｾｯﾄでｽﾃｰﾀｽがRECEIVEでも１枚も受信し
				  ていない時もあるのでそのパスを追加		1994/11/29 Y.M
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE SetUpSecureMailRx(WORD pos)	/*	モデムバッファのポインター	*/
{
	UWORD mailbox_no;
	UBYTE temp;
	UBYTE i;

	mailbox_no = 0;
	temp = 0;
	i = 0;

	switch (MDM_ModemBuffer[NonStdFrmPos][pos]) {		/**	独自フレームのメイルボックスNO.チェック	*/
		/**	メイルボックスNO.をローカル変数にセット	*/
		/*	指定されるメイルボックスは、１つ	*/
		/*	２バイトに別れている	*/
		case 0x00:
			break;
		case 0x01:	/*	メイルボックスNO.0	*/
			mailbox_no = 0;
			break;
		case 0x02:	/*	メイルボックスNO.1	*/
			mailbox_no = 1;
			break;
		case 0x04:	/*	メイルボックスNO.2	*/
			mailbox_no = 2;
			break;
		case 0x08:	/*	メイルボックスNO.3	*/
			mailbox_no = 3;
			break;
		case 0x10:	/*	メイルボックスNO.4	*/
			mailbox_no = 4;
			break;
		case 0x20:	/*	メイルボックスNO.5	*/
			mailbox_no = 5;
			break;
		case 0x40:	/*	メイルボックスNO.6	*/
			mailbox_no = 6;
			break;
		case 0x80:	/*	メイルボックスNO.7	*/
			mailbox_no = 7;
			break;
		default:	/*	該当しないNO.の場合	*/
			/*	親展受信不可	*/
			return (NO);
	}
	switch(MDM_ModemBuffer[NonStdFrmPos][pos+1]) {
		case 0x00:	/*	メイルボックスNO.	*/
			break;
		case 0x01:	/*	メイルボックスNO.8	*/
			mailbox_no = 8;
			break;
		case 0x02:	/*	メイルボックスNO.9	*/
			mailbox_no = 9;
			break;
		case 0x04:	/*	メイルボックスNO.	*/
		case 0x08:	/*	メイルボックスNO.	*/
		case 0x10:	/*	メイルボックスNO.	*/
		case 0x20:	/*	メイルボックスNO.	*/
		case 0x40:	/*	メイルボックスNO.	*/
		case 0x80:	/*	メイルボックスNO.	*/
		default:	/*	親展受信不可	*/
			return (NO);
	}
	if (mailbox_no >= SYS_MAILBOX_MAX) {
		return (NO);
	}

	CMN_DisableInterrupt();		/** 割り込み禁止 *//*SYS_MAILBOX_RCV_TO_RECEVING*/

	/**	メモリ受信用アイテムセット（親展受信原稿）	*/
	SYS_RxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;

	/**	指定メイルボックスの状態のチェック	*/
	switch (SYB_MailBox[mailbox_no].Status) {		/**	メイルボックスのステータス	*/
		case SYS_MAILBOX_NO_SET:	/**	未登録	*/
			/**	親展受信しない	*/
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
			break;
		case SYS_MAILBOX_RECEIVE:			/**	メイルボックス受信済み	*/
			/**	メイルボックス受信中	*/
			/* SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RECEIVING;/@ バックアップのため追加 17.Aug'94 Y.Suzuki */
			SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RCV_TO_RECEVING;/* バックップのため追加 1997/10/18  By T.Yamaguchi */
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			/* 受信中の親展原稿の消去を防止するため ↑ */
			/**	メモリ受信用ページカウンタに親展受信済みページ数セット	*/
			/*	SYS_RxMemoryFilePage = (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE, mailbox_no, MEM_IGNORE_BOX_NUMBER) + 1);	*/
			SYS_RxMemoryFilePage = MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE, mailbox_no, MEM_IGNORE_BOX_NUMBER);
			if (SYS_RxMemoryFilePage == MEM_NO_INDEX) {	/* ｽﾃｰﾀｽがSYS_MAILBOX_RECEIVEでも受信枚数が０の時もある */
				SYS_RxMemoryFilePage = 1;		/* 1994/11/29 Y.Murata */
			}
			else {	/* 次ページをセット 1997/08/28  By T.Yamaguchi */
				SYS_RxMemoryFilePage++;
			}

 #if(PRO_FIP == ENABLE)
			/**	FIP親展受信開始ページにページカウンタをセット	*/
			SYS_FIP_SecureStartPage = SYS_RxMemoryFilePage;
 #endif
			break;
		case SYS_MAILBOX_SET:	/**	メイルボックス登録済み	*/
			/**	メイルボックス受信中	*/
			SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RECEIVING;/* バックアップのため追加 17.Aug'94 Y.Suzuki */
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			/* 受信中の親展原稿の消去を防止するため ↑ */
			/**	メモリ受信用ページカウンタに（受信ページ数＋１）をセット	*/
			SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
 #if(PRO_FIP == ENABLE)
			/**	FIP親展受信開始ページにページカウンタをセット	*/
			SYS_FIP_SecureStartPage = SYS_RxMemoryFilePage;
 #endif
			break;
		case SYS_MAILBOX_RECEIVING:
		case SYS_MAILBOX_RCV_TO_RECEVING:	/**	メイルボックス受信中	*/
			FaxCompatibleErrorCode = SECURE_INDEX_CONFLICT_ERROR;
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
			break;
		default:/**	ステータスエラー	*/
			/**	親展受信しない	*/
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
	}
	/**	メモリ受信ファイルNO.にメイルボックスNO.	*/
	SYS_RxMemoryFileNo = (UWORD)mailbox_no;			/* SYS_MAILBOX_RCV_TO_RECEVING */
	CMN_EnableInterrupt();		/** 割り込み許可 */

	/**	親展受信メイルボックス管理データ内の相手先ＩＤのデータの登録をする	*/
	if ((NonStandardID[0] != NULL) && (OwnMakerCode == MURATA_CODE)) {		/**	独自（カナ）ＩＤあり、かつＭＭＬ機	*/
		/**	カナＩＤ登録	*/
		for (i = 0; i < 16; i++) {
			SYB_MailBox[mailbox_no].RemoteName[i] = NonStandardID[i];
		}
		SYB_MailBox[mailbox_no].RemoteName[i] = NULL;
	}
	else if (StandardID[0] != NULL) {	/**	標準ＩＤあり	*/
		/**	標準ＩＤ登録	*/
		for (i = 0; i < 20; i++) {
			SYB_MailBox[mailbox_no].RemoteName[i] = StandardID[i];
		}
		SYB_MailBox[mailbox_no].RemoteName[i] = NULL;
	}
	else {
		/**	登録しない	*/
		SYB_MailBox[mailbox_no].RemoteName[0] = NULL;
	}
	/**	リターンYES	*/
	return(YES);
}


/*************************************************************************
	module		:[親展送信準備]
	function	:[
		1.親展送信に際して送信側で指示したメイルボックスが受信側にセットされているかチェックする
	]
	return		:[ＯＫ--YES／ＮＧ--NO]
	common		:[
					CommandP->Option.OptionNumber.:SecuteNumber
					MDM_ModemBuffer
					NonStdFrmPos
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE SetUpSecureMailTx(WORD pos)	/*	モデムバッファのポインター	*/
{
	UWORD compare_boxno;
	UWORD partner_boxno;
	UBYTE secure_no;	/* 親展番号 */

	compare_boxno = 0x01;
	partner_boxno = 0;
	secure_no = 0;

	secure_no = (UBYTE)(CommandP -> Option.OptionNumber.SecureNumber);

	compare_boxno = (UWORD)(compare_boxno << secure_no);

#if 0	/* ↑に変更 1996/12/02	By T.Yamaguchi */
	switch (CommandP -> Option.OptionNumber.SecureNumber) {
		case 0:
			compare_boxno = 0x0001;
			break;
		case 1:
			compare_boxno = 0x0002;
			break;
		case 2:
			compare_boxno = 0x0004;
			break;
		case 3:
			compare_boxno = 0x0008;
			break;
		case 4:
			compare_boxno = 0x0010;
			break;
		case 5:
			compare_boxno = 0x0020;
			break;
		case 6:
			compare_boxno = 0x0040;
			break;
		case 7:
			compare_boxno = 0x0080;
			break;
		case 8:
			compare_boxno = 0x0100;
			break;
		case 9:
			compare_boxno = 0x0200;
			break;
		case 10:
			compare_boxno = 0x0400;
			break;
	}
#endif
	partner_boxno = MDM_ModemBuffer[NonStdFrmPos][pos+1];
	partner_boxno = partner_boxno << 8;
	partner_boxno |= MDM_ModemBuffer[NonStdFrmPos][pos];
	if (compare_boxno != (partner_boxno & compare_boxno)) {		/**	送信側で指示したメイルボックスNOに該当する独自フレームのビットがONしている	*/
		/**	親展送信しない	*/
		return(NO);
	}
	/**	親展送信準備完了	*/
	return(YES);
}

#if(PRO_TSI_RELAY_COM == ENABLE)
/*************************************************************************
	module		:[ＴＳＩによる中々継指示受信]
	function	:[
		TSI_Relay == 1のとき、StandardID[]内 にスペースが入っている。
		グループNOの区切りとするため。
		1.中々継コマンド 000-
		2.1桁のグループＮＯは、１桁で指示する。
		3.グループＮＯ間は、'-'。
		4.中継指示配信の宛先用ｸﾞﾙｰﾌﾟNO.の次は、'--'。(最大10宛先)
		5.'--'の後に続くｸﾞﾙｰﾌﾟNO.は、孫機に中継指示するｸﾞﾙｰﾌﾟNO.。
		6.000-の直後に'--'がきたらエラー。
		7.'--'の直後にNULLがきたらｴﾗｰ。
		8.TSI内に２回'--'があったらｴﾗｰ。
		9.最後は、NULL。
	]
	return		:[正しくグループＮＯをセットしたとき:１ーＦＦＦＦＦＦＦＦ
				  グループＮＯがセットできなかったとき：０
	]
	common		:[]
	condition	:[]
	comment		:[
		1.中継指示配信の宛先のためのｸﾞﾙｰﾌﾟNO.の取り込追加。950929 Y.Suzuki
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/02/14]
	author		:[鈴木郁二]
*************************************************************************/
UDWORD GetGroupNoFromStdID(UBYTE pos)
{
	/* pos は、StandardID[]のﾎﾟｼﾞｼｮﾝ */
	/* UBYTE pos,h,k; 950929 */
	UBYTE h,k;
	UDWORD g,gtmp;
	UBYTE reserve_address;/* 中継指示配信の宛て先指定 '--' 検出用 950929 */

	/*--------------------------------------------------------------------------------*/
	/* PC の FAX BORD から中々継指示される TSI StandardID[] からグループNOを取り出す。*/
	/*--------------------------------------------------------------------------------*/
	h = 0;
	g = 0;
	gtmp = 0;
	k = 0;
	reserve_address = 0;
	if(pos == 0){
		pos = 4;
	}
	while(pos) {
		gtmp = 1;
		h = StandardID[pos++];
		if(((h < '0') || (h > '9')) && !reserve_address) {/* 000-,-,--の次が数字以外 */
			return(0);/* ｴﾗｰ */
		}
		else {
			if((reserve_address == 1) && (h == ' ')) {/* TSI 内に'--'検出 */
				if(g && !TSI_Ptr) {/* '--'検出までにｸﾞﾙｰﾌﾟNO.の検出あり == 中継指示配信宛て先 */
					TSI_Ptr = pos;
					return(g);
				}
				else{/* 000の直後に'--'、２度目の'--'を検出 */
					return(0);
				}
			}
			k = StandardID[pos++];
			switch(k) {
			case NULL:
			case ' ':
				/* 1桁指定 */
				if(h == '0') {/* 全グループＮＯ指定 */
					g = 0xFFFFFFFF;
					pos = 0;
				}
				else {
					h &= 0xCF;
					while(h) {
						h--;
						if(h > 0) {
							gtmp <<= 1;
						}
					}
					g |= gtmp;
				}
				if(k == NULL) {/* グループNO検索終了 */
					pos = 0;
				}
				else {
					reserve_address = 1;/* '--'検出用 */
				}
				break;
			default:/* 2桁で表わされるグループNO */
				if(((k < '0') || (k > '9')) || ((StandardID[pos] != ' ') && (StandardID[pos] != NULL))) {
					/* 2桁目が数字でないまたは、３桁目がある */
					return(0);
				}
				if(StandardID[pos] == NULL) {/* 最後のグループNO */
					pos = 0;
				}
				else {/* ' ' をスキップ */
					reserve_address = 1;/* '--'検出用 */
					pos++;
				}
				h &= 0xCF;
				k &= 0xCF;
				h = (UBYTE)((10 * h) + k);
				if( h <= 32) {/* 33 番以上のグループNOは、ありえない。*/
					while(h) {
						h--;
						if(h > 0) {
							gtmp <<= 1;
						}
					}
					g |= gtmp;
				}
				else {
					return(0);
				}
			}
		}
	}
	return(g);
}
#endif


#if (PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
/*************************************************************************
	module		:[中継配信コマンドチェック(椛)]
	function	:[
		不達通知設定ONの場合、中継配信コマンドは、最大９つまでとする。
		1.コマンドファイルの空き状態を調べる。
		2.コマンドファイルがフルなら、各コマンドファイルのアイテムを調べる。
		3.中継配信以外のコマンドが１つでもあればOK
	]
	return		:[
			コマンドファイル空きあり:YES ／ すべてのコマンドが中継配信である:NO
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/02/09]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CountRelayedTxCommand(void)
{
	UBYTE i;
	UBYTE empty_count;

	i = 0;
	empty_count = 0;
	/**	空きコマンドファイルがあればコマンドファイルへ展開する	*/
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if (SYB_CommandFile[i].Status == SYS_CMD_EMPTY) {
			empty_count++;
		}
	}
	if(empty_count >= 2) {	/**	コマンド登録８個以下	*/
		return(YES);
	}
	empty_count = 0;
	/** コマンドファイルフル */
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if((SYB_CommandFile[i].Option.Item) != SYS_RELAYED_TX) {/** 中継配信コマンド９個以下 */
			empty_count++;
		}
	}
	if(empty_count >= 2) {	/**	中継配信コマンド８個以下	*/
		return(YES);
	}
	/** 中継配信コマンド１０個 */
	return(NO);
}
#endif


/*************************************************************************
	module		:[中継配信受信準備]
	function	:[
		1.中継配信指示受信可能なら受信ファイルのセットアップまで行う
		2.指示されたグループNOが全て登録されていない場合は普通の受信
		3.指示されたグループNOの内ひとつでも登録されていたらOK
		4.コマンドファイルがフルの場合　受信しない
		5.メモリ受信ファイルの指定
		6.自機コマンドファイルへの展開
	]
	return		:[ＯＫ--RELAY_RX／受信のみ行う--YES／ＮＧ--NO]
	common		:[
					MDM_ModemBuffer
					NonStdFrmPos
					SYB_OnetouchDial.Setting.DialNumber.:Group
					SpeedMaxNumberRomDip
					SYB_SpeedDial.:Group
					SYB_CommandFile.:Status
					RelayedTxDocumentStatus
					RelayedCommandNo
					SYB_CommandFile.DialNumber.:Item
					SYB_CommandFile.DialNumber.FaxNumber.:Group
					SYB_CommandFile.Option.Item
					SYB_CommandFile.Option.OptionNumber.:RelaySourceID
					SYB_TTI_Buffer
					SYB_CommandFile.Option.:ConfirmationReport
					SYB_CommandFile.:DepartmentCode
					SYB_CommandFile.:TitleMessage
					RxMemoryFileItem
					RxMemoryFileNO
					SYS_RxMemoryFilePage
					SYS_RxTotalPage
					SYS_RxPrintFileItem
					SYS_RxPrintFileNo
					SYS_RxPrintFilePage
					SYS_RxTotalPage
					SYB_MemoryRxPrint.JournalPoint->:Number
					SYB_MemoryRxPrint.JournalPoint->:RemoteID_TTI
					SYB_MemoryRxPrint.JournalPoint->:Mode
					SYB_MemoryRxPrint.JournalPoint->:StartTime
					SYB_MemoryRxPrint.JournalPoint->:TotalTime
					SYB_MemoryRxPrint.JournalPoint->:DepartmentCode
					SYB_MemoryRxPrint.JournalPoint->:Type
					SYB_MemoryRxPrint.JournalPoint->:Result
					SYB_MemoryRxPrint.JournalPoint->:Kind
					SYB_MemoryRxPrint.JournalPoint->:Option
	]
	condition	:[]
	comment		:[修正履歴
					1.94/9/9 代行バッファのステータスのセットをやめた
					2.94/9/16 上記変更により出現した Warning 消去のため
					3.94/11/11 中々継の処理追加
					4.94/12/26 中継指示受信時、短縮・ワンタッチの登録状態を確認
					5.95/2/1 TSIを使用した中々継指示に対応（椛）
					6.95/9/29 TSIを使用した中々継指示に対応 仕様追加（椛）
					  中継指示配信宛先をｸﾞﾙｰﾌﾟNO.で指定する。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE SetUpRelayBroadCastRx(WORD pos)/*	モデムバッファのポジション	*/
{
	struct	SYS_CommandData_t	 *comp;/* 11.Jun'94 */
	/*struct SYS_MemoryRxPrintData far *MemoryRxPrintPoint;* 11.Jun'94 */
	UDWORD g;
	UDWORD gtmp;
	BYTE i;					/* char !! */
	UBYTE j;
	UBYTE ok_flag;
 #if(PRO_RELAYED_REPORT == ENABLE)
	UBYTE relayed_report;	/* 中継配信不達通知設定用 9.Feb'95 Y.Suzuki */
	relayed_report = 0;
 #endif

	g = 0;
	gtmp = 0;
	i = 0;
	j = 0;
	ok_flag = NO;

 #if(PRO_RELAYED_REPORT == ENABLE)
	if(CHK_RelayedTxReport() && pos != 0) {/* TSI による中々継指示では不達通知を送らない。中継配信不達通知設定セット 9.Feb'95 Y.Suzuki */
		relayed_report = YES;
	}
 #endif
	/**	中継指示されたグループNOの獲得 グループＮＯ.３２－＞６４対応の場合変更要	*/
#if(PRO_TSI_RELAY_COM == ENABLE)
	/*--------------------------------------------------*/
	/*	  TSIによる中々継指示 14.Feb'95 Y.Suzuki		*/
	/*--------------------------------------------------*/
	if((pos == 0) && (TSI_Relay == 1)) {
		/** 中継指示配信の宛先 獲得 */
		g = GetGroupNoFromStdID(0);/* 引数追加 950929 Y.S */
		if(g == 0) {/** TSI からグループＮＯ取り出せなかった */
			return(TSI_NG);
		}
	}
	else {
#endif
	for (i = 3; i >= 0; i--) {
		g = g | (UDWORD)MDM_ModemBuffer[NonStdFrmPos][pos + i];
		if (i != 0) {
			g = g << 8;
		}
	}
#if(PRO_TSI_RELAY_COM == ENABLE)
	}
#endif
	/*	中継指示されたグループNOがワンタッチに登録されているか　第２ワンタッチ、短縮の対応 必要 さつき、ラベンダー	*/
	for (j = 0; j < SYS_ONETOUCH_MAX; j++) {/**	標準ワンタッチダイヤル	*/
		if((SYB_OnetouchDial[j].Dial[0] & 0xF0) != 0xF0) {		/* '96.02.22 BY T.Y */
			if (g & (SYB_OnetouchDial[j].Group)) {
				ok_flag = YES;/**	グループ登録されている	*/
				break;
			}
		}
	}
	if (ok_flag != YES) {		/**	中継指示されたグループNOがワンタッチに登録されていない	*/
		for (j = 0; j < SYS_SPEED_DIAL_MAX; j++) {/**	標準短縮ダイヤル	*/
			if((SYB_SpeedDial[j].Dial[0] & 0xF0) != 0xF0) {/* 26.Dec'94 */
				if (g & (SYB_SpeedDial[j].Group)) {
					ok_flag = YES;/**	グループ登録されている	*/
					break;
				}
			}
		}
	}
	if (ok_flag == NO) {	/**	中継指示されたグループNOが短縮､ワンタッチに登録されていない	*/
 #if(PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
								   /*----------------------------------*/
		if(relayed_report == YES) {/** 中継配信不達通知がON ならエラー */
								   /*----------------------------------*/
			return(NO);
		}
 #endif
		/**	リターンYES	*//*	メモリ受信のみ行う	*/
		return(YES);
	}
	/**	空きコマンドファイルがあればコマンドファイルへ展開する	*/
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if (SYB_CommandFile[i].Status == SYS_CMD_EMPTY) {		/**	空きコマンドファイルあり	*/
#if(0) /* RelayedTxDocumentStatus[i] 未使用 21.Feb'95 Y.Suzuki */
//			if (RelayedTxDocumentStatus[i] == NO_RELAYED_DOC) {/**	配信原稿なし	*/
//				SYB_CommandFile[i].Status = SYS_CMD_SETTING;
//				RelayedCommandNo = i;
//				comp = &SYB_CommandFile[RelayedCommandNo];
//				break;
//			}
#endif
			SYB_CommandFile[i].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[i] = SYS_CMD_SETTING;
#endif
			RelayedCommandNo = i;
			comp = &SYB_CommandFile[RelayedCommandNo];
			break;
		}
	}
	if (RelayedCommandNo == 0xFF) {	/*	空ｺﾏﾝﾄﾞﾌｧｲﾙなし ｺﾝﾊﾟﾁｴﾗｰで回線断	*/
		return (NO);
	}
	/**	プリント用バッファセット	*/
	if (CMN_CheckMemoryReceiveEnable() == TRUE) {
		/**	空きがあれば、メモリ受信	*/
		SYS_RxPrintFileItem = SYS_MEM_RX_FILE;/*	通常のメモリ受信	*/
		SYS_RxPrintFileNo = SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage =  SYS_RxTotalPage + 1;
		/*--------- ここでは、セットしない。MAN_MAIN.C にてセットする。
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
		MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
		-------------------------------------------------------------*/
	}
	else {/**	空きがなければ、受信しない	*/
		return(NO);
	}
 #if(PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
	if(relayed_report == YES) {/** 中継配信不達通知	 */
		if(CountRelayedTxCommand() == NO) {/** 中継配信コマンドは、９個まで */
			return(NO);
		}
		/*------------------------------------------------------*/
		/**	コマンドファイルの中継局IDバッファに標準IDをセット	*/
		/*------------------------------------------------------*/
		if(SetTransmitStationID() == NO) {/** TSI 不良エラー */
			return(TSI_NG);
		}
	}
 #endif
#if 0	/* POPLAR変更 */
//	for (i = 0; i < SYS_COM_DIAL_MAX; i++) {/* Item Clear 95/03/28 Y.Suzuki	*/
//		comp->DialNumber[i].Item = SYS_EMPTY_DIAL;
//	}
#endif
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/* 1997/02/12  By T.Yamaguchi */
#if 0 /* POPLAR */
//	if (g == 0xFFFFFFFF) {		/**	全グループNOを指示された（グループ０指定）	*/
//		/**	コマンドファイルのダイヤルアイテムにグループをセット	*/
//		comp->DialNumber[0].Item = SYS_GROUP_DIAL;
//		/**	コマンドファイルのダイヤルグループNOに０をセット	*/
//		comp->DialNumber[0].FaxNumber.Group = 0;
//	}
//	else {
//		j = 1;			/* j == GroupNo */
//		gtmp = 0x00000001;
//		for (i = 0; i < SYS_COM_DIAL_MAX; i++) {/* １通信あたり最大１０宛て先	*/
//			ok_flag = NO;
//			/*comp->DialNumber[i].Item = SYS_EMPTY_DIAL; By H.Y 1994/11/30 */
//			while ((j <= 32) && (ok_flag == NO)){
//				if (g & gtmp) {
//					/**	コマンドファイルのダイヤルアイテムにグループをセット	*/
//					comp->DialNumber[i].Item = SYS_GROUP_DIAL;
//					/**	コマンドファイルのダイヤルグループNOに指示されたグループ全てセット	*/
//					comp->DialNumber[i].FaxNumber.Group = j;
//					ok_flag = YES;
//				}
//				gtmp = gtmp << 1;
//				j++;
//			}
//		}
//	}
#endif /* POPLAR */
	comp->DialNumber.Group = g;

#if(PRO_TSI_RELAY_COM == ENABLE)/*			950929 Y.Suzuki		*/
	/* 中継指示配信宛先ｸﾞﾙｰﾌﾟNO.と中継配信ｸﾞﾙｰﾌﾟNO.が異なる場合 */
	/* MMLの中々継では、２つのｸﾞﾙｰﾌﾟNO.は、共通だった。			*/
	/* 中継配信ｸﾞﾙｰﾌﾟNO.を獲得									*/
	if(TSI_Ptr) {
		/* TSI 内の'--'以降のｸﾞﾙｰﾌﾟNO.の獲得 */
		g = GetGroupNoFromStdID(TSI_Ptr);
		if(g == 0) {/** TSI からグループＮＯ取り出せなかった */
			return(TSI_NG);
		}
	}
	/**	コマンドファイルアイテムに中継送信をセット	*/
	/* 中中継ありの場合 Item:SYS_MEMORY_RELAY_BROADCAST	  OptionNumber.RelayGroupNumber にGroup NO. をｾｯﾄ */
	if(CHK_RelayedRelayTxON() || ((TSI_Relay == 1) && (pos == 0))) {
		/* TSI による中々継指示は、常に中々継指示受信する。14.Feb'95 Y.Suzuki */
		comp->Option.Item = SYS_MEMORY_RELAY_BROADCAST;
		comp->Option.OptionNumber.RelayGroupNumber = g;
	}
#else
	if(CHK_RelayedRelayTxON()) {
		comp->Option.Item = SYS_MEMORY_RELAY_BROADCAST;
		comp->Option.OptionNumber.RelayGroupNumber = g;
	}
#endif
	else {
		comp->Option.Item = SYS_RELAYED_TX;
	}
	/**	コマンドファイルの受領証ステータス、部門管理コード、タイトルメッセージをクリア	*/
	comp->Option.ConfirmationReport = NO;
  #if (PRO_DEPARTMENT == ENABLE)
	comp->DepartmentCode = 0xFFFF;	/* 96/08/14 By T.Yamaguchi */
/*	comp->DepartmentCode = NO;	*/
  #endif
	comp->TitleMessage = 0xFF;/* FF Clear !! 21.Oct'94 */

	comp->Ability = NO;		/* Clear 1996/09/12 T.Yamaguchi ANZUでは未使用だがクリアしておく */

#if (PRO_PIN_ACCESS == ENABLE)
	/*
	** ＰＩＮのモードが１の時、ワンタッチ／短縮に登録されている番号を送出可能ですが、
	** ＰＩＮのモードが２の時は、発呼するPIN番号が不定のためＯＦＦする 1998/01/21  By T.Yamaguchi
	*/
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp->PIN_AccessMode = PIN_ACCESS_MODE1;
	}
	else {
		comp->PIN_AccessMode = 0;
	}
#endif

	/**	メモリ受信ファイルの指定	*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;				  /* Itemは MEMORY_TX_DOCとする */
	SYS_RxMemoryFileNo = (UWORD)RelayedCommandNo;/* NoはｺﾏﾝﾄﾞNoに対応 */
	SYS_RxMemoryFilePage = (UWORD)SYS_RxTotalPage + 1;
	/**	リターンRELAY_RX	*//*	中継指示成立	*/
#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif
	return (SYS_RELAY_RX);
}


/*************************************************************************
	module		:[検索ポーリング送信時メモリファイル獲得]
	function	:[
		1.ＤＴＣより検索ポーリングファイルNO取り出す
		2.ファイルのページ数とファイルNOを送信メモリファイルにセットする
	]
	return		:[
				ファイル獲得--独自フレーム（ＤＴＣ）の検索ポーリング
				.			  ファイル指定の最後のポジション
				ファイルなし--０
	]
	common		:[
				MDM_ModemBuffer
				NonStdFrmPos
				TxMemoryFileNo
				PollingTxFilePage
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/28]
	author		:[鈴木 郁二]
*************************************************************************/
WORD GetDatabasePollingFileNumber(WORD pos)/*	モデムバッファのポインタ	*/
{
	UWORD  page;
	UBYTE i;
	UBYTE mdm_data;
	UBYTE first_flag;
	UBYTE ok_flag;

	i = 0;
	mdm_data = 0;
	first_flag = NO;
	ok_flag = NO;
/*	for (i = 0; i < (SYS_TX_MEMORY_FILE_NO_MAX - 1); pos+=2) {/@@ 取り出せるファイルNOの数、最大１０個 */
	for (i = 0; i < (SYS_DATA_BASE_MAX - 1); pos+=2) {/** 取り出せるファイルNOの数、最大１０個 */
		/**	検索ポーリングファイルNO取り出し	*/
		mdm_data = MDM_ModemBuffer[NonStdFrmPos][pos];
		if ((i == 0) && (first_flag == NO)) {
			page = MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, (UWORD)mdm_data, MEM_IGNORE_BOX_NUMBER);
			first_flag = YES;
			if (page != MEM_NO_INDEX) {
				ok_flag = YES;
				/**	送信メモリファイルNOに検索ポーリングファイルNOセット	*/
				TxMemoryFileNo[i] = mdm_data;
				/**	送信メモリファイルページにページ数セット	*/
				PollingTxFilePage[i] = page;
				i++;
			}
		}
		else {
			if (MDM_ModemBuffer[NonStdFrmPos][pos - 1] & BitNo8) {	/**	継続ビットＯＮ	*/
				/**	次の検索ポーリングファイルNO取り出し	*/
				page = MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, (UWORD)mdm_data, MEM_IGNORE_BOX_NUMBER);
				if (page != MEM_NO_INDEX) {
					ok_flag = YES;
					/**	送信メモリファイルNOに検索ポーリングファイルNOセット	*/
					TxMemoryFileNo[i] = mdm_data;
					/**	送信メモリファイルページにページ数セット	*/
					PollingTxFilePage[i] = page;
					i++;
				}
			}
			else {
				break;
			}
		}
	}
	/**	送信メモリファイルの次のバッファに0xFFFFを入れる	*/
	TxMemoryFileNo[i] = 0xFFFF;
	PollingTxFilePage[i] = 0xFFFF;

	if (ok_flag == NO) {	/**	指定されたファイルのページ数が全て０以下	*/
		pos = 1;/**	リターン０	*/
	}
	/**	リターンモデムバッファのポジション	*/
	return (pos - 1);
}


/*************************************************************************
	module		:[リモートＦＡＸ取り出し用受信準備]
	function	:[
		1.リモート取り出し用ファイルセットアップ
		2.同時プリントありの場合、プリント用バッファセットアップ
	]
	return		:[
				YES--準備完了
				NO---同時プリントありの場合でプリント用バッファ
				.	 (代行受信用)がフル
				]
	common		:[
				SYS_RxMemoryFileItem
				SYS_RxMemoryFileNo
				SYB_MemoryRxPrint.:Status
				SYS_RxPrintFileItem
				SYS_RxPrintFileNo
				SYS_RxPrintFilePage
				SYS_RxTotalPage
	]
	condition	:[]
	comment		:[修正履歴
					1.94/9/9 代行バッファのステータスのセットをやめた
					2.94/9/16 上記変更により出現した Warning 消去のため
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/17]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetUpRemoteFaxRx(void)
{
	/* struct SYS_MemoryRxPrintData far *MemoryRxPrintPoint;* 29.Apr'94 */
	/**	親展受信の場合は、リモート受信しない 14.Apr'94	*/
	if (SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE) {
		return(YES);
	}
	/**	リモート取り出し用ファイルセットアップ	*/
	SYS_RxMemoryFileItem = SYS_MEM_REMOTE_TX_FILE;
	/* SYS_RxMemoryFilePage = (MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) + 1);	*/
	SYS_RxMemoryFilePage = MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
	SYS_RxMemoryFileNo = 0;/* 0 固定 */
	if(SYS_RxMemoryFilePage != MEM_NO_INDEX) {/* 該当インデックスなし MEM_CountTotalPage 0xFFFF */
		SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
	}
	if (RemoteFaxPRN_Flag == YES) {		/**	同時プリントあり	*/
		/**	プリント用バッファセット	*/
		if (CMN_CheckMemoryReceiveEnable() == TRUE) {
			/**	空きがあれば、メモリ受信	*/
			SYS_RxPrintFileItem = SYS_MEM_RX_FILE;/*	通常のメモリ受信	*/
			SYS_RxPrintFileNo = SYB_MemoryRxPrintWritePoint;
			SYS_RxPrintFilePage =  SYS_RxTotalPage + 1;
			/*--------- ここでは、セットしない。MAN_MAIN.C にてセットする。
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
			-------------------------------------------------------------*/
	}
		else {
			SYS_RxMemoryFileItem = NULL;
			return(NO);
		}
	}
	return(YES);
}


/*************************************************************************
	module		:[パスコードセット]
	function	:[
		モデムバッファにパスコードをセットする
	]
	return		:[モデムバッファのポインタ]
	common		:[
			FrameName
			MDM_ModemBuffer
			SYB_PasscodeNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetPasscodeFrame(UBYTE FrameName,/*	NSC or NSS	*/WORD pos)
{
	UBYTE j;
	j = 0;
	/*	サンフラワーサークル用 ポーリングパスコード	*/
	if ((FrameName == NSC_F) && (CHK_UNI_SpecialPollingPasscode())) {		/**	ＮＳＣフレームでかつソフトスイッチ特殊ポーリングビットON	*/
		/**	パスコード＋ 0x11 をモデムバッファにセット	*/
		for(j = 0; j < 4; j++) {
			MDM_ModemBuffer[InNS][pos] = (UBYTE)(SYB_PasscodeNumber[j] + 0x11);
			pos++;
		}
	}
	else {
		/**	パスコードをモデムバッファにセット	*/
		for(j = 0; j < 4; j++) {
			MDM_ModemBuffer[InNS][pos] = SYB_PasscodeNumber[j];
			pos++;
		}
	}
	return(pos - 1);
}


/*************************************************************************
	module		:[親展フィールドデータセット]
	function	:[
		NSF の場合:10個のメイルボックスを１０ビットであらわす 登録済みのボックスはビットONする
	]
	return		:[モデムバッファのポインタ]
	common		:[
					MDM_ModemBuffer
					SYB_MailBox.:Status
					SYS_CommandP->Option.OptionNumber.:SecureNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetSecureMailFieldFrame(UBYTE FrameName,/*	NSF,NSS	*/WORD pos)
{
	UBYTE j;
	UBYTE i;
	j = 0;

	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	MDM_ModemBuffer[InNS][pos + 1] = BIT_CLEAR;

	switch (FrameName) {		/**	フレーム名	*/
		case NSF_F:	/**	NSF	*/
			/**	メイルボックスが登録されていれば、対応するビットをONする	*/
			i = 0;
			for (j = 0x01; i < 8; i++, j *= 2) {
				if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET) ||
					/* ↓モード変更されると次のページでコンパチエラーとなる 親展ﾌｨｰﾙﾄﾞなしになる 96/1/11 追加 Y.S */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) ||
					(SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING) ||	/* add 1997/10/18  By T.Yamaguchi */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)) {
					MDM_ModemBuffer[InNS][pos] |= j;
				}
			}
			for (j = 0x01; i < SYS_MAILBOX_MAX; i++, j *= 2) {
				if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET) ||
					/* ↓モード変更されると次のページでコンパチエラーとなる 親展ﾌｨｰﾙﾄﾞなしになる 96/1/11 追加 Y.S */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) ||
					(SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING) ||	/* add 1997/10/18  By T.Yamaguchi */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)) {
					MDM_ModemBuffer[InNS][pos + 1] |= j;
				}
			}
			break;
		case NSS_F:	/**	NSS	*/
			/**	コマンドにセットされている親展NOに対応するビットをONする	*/
			switch (CommandP -> Option.OptionNumber.SecureNumber) {
				case 0:
					MDM_ModemBuffer[InNS][pos] |= 0x01;
					break;
				case 1:
					MDM_ModemBuffer[InNS][pos] |= 0x02;
					break;
				case 2:
					MDM_ModemBuffer[InNS][pos] |= 0x04;
					break;
				case 3:
					MDM_ModemBuffer[InNS][pos] |= 0x08;
					break;
				case 4:
					MDM_ModemBuffer[InNS][pos] |= 0x10;
					break;
				case 5:
					MDM_ModemBuffer[InNS][pos] |= 0x20;
					break;
				case 6:
					MDM_ModemBuffer[InNS][pos] |= 0x40;
					break;
				case 7:
					MDM_ModemBuffer[InNS][pos] |= 0x80;
					break;
				case 8:
					MDM_ModemBuffer[InNS][pos + 1] |= 0x01;
					break;
				case 9:
					MDM_ModemBuffer[InNS][pos + 1] |= 0x02;
					break;
				}
				break;
		case NSC_F:	/**	NSC	*/
		default:
			break;
	}
	/**	リターンモデムバッファのポインタ	*/
	return (pos + 1);
}

/*************************************************************************
	module		:[検索ポーリングフィールドセット]
	function	:[
		NSCの検索ポーリングフィールド(ファイルNO.０－－７ＦＦＦ(32767))を
		.モデムバッファにセットする このフィールドは、通常 拡張ビット
		.(1ビット)＋ファイルNO(7ビット)の１バイトであらわされる 拡張ビット
		.が１なら次のバイトも検索ポーリングフィールドとなる
	]
	return		:[モデムバッファのポインタ]
	common		:[
					MDM_ModemBuffer
					CommandP->Option.OptionNumber.:DatabaseNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetDatabasePollingDataFrame(WORD pos)/*	モデムバッファのポインタ	*/
{
	UWORD n;	/* WORD -> UWORDに変更 0xFFFFと比較する時に、0xFFFFFFFFと比較しているためおかしくなる 1997/09/16  By T.Yamaguchi */
	UBYTE nh;
	UBYTE nl;
	UBYTE i;

	n = 0;
	nh = 0;
	nl = 0;
	i = 0;

	for (i = 0; i < SYS_DATA_BASE_MAX; i++) {	/*	0 <= ファイル数 < 11	*/
		n = (CommandP -> Option.OptionNumber.DatabaseNumber[i]);
		if (n != 0xFFFF) {		/**	コマンドファイルにセットされたファイルNOが FFFF ではない	*/
			/**	モデムバッファにセット	*/
			nl = (UBYTE)(n & 0x00FF);
			nh = (UBYTE)((n & 0xEF00) >> 8);
			MDM_ModemBuffer[InNS][pos] = nl;
			pos++;
			MDM_ModemBuffer[InNS][pos] = nh;
			/**	拡張ビットをONする	*/
			MDM_ModemBuffer[InNS][pos] |= BitNo8;
			pos++;
		}
		else {
			/**	ONした拡張ビットをOFFする	*/
			pos--;
			MDM_ModemBuffer[InNS][pos] &= ~BitNo8;
			break;
		}
	}
	/**	リターンモデムバッファのポインタ	*/
	return (pos);
}


/*************************************************************************
	module		:[中継同報のグループセット]
	function	:[
		NSSの中継同報フィールドにグループNOをセットする
	]
	return		:[モデムバッファのポインタ]
	common		:[
					MDM_ModemBuffer
					CommandP->Option.OptionNumber.:RelayGroupNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
WORD SetRelayedBroadcastGroupFrame(WORD pos)/*	モデムバッファのポインタ	*/
{
	UBYTE i;
	UBYTE j;
	UBYTE k;
	UBYTE n;
	UBYTE dummy_group;
	UDWORD g;
	UDWORD group;

	i = 0;
	j = 0;
	k = 0x01;
	n = 0;
	dummy_group = 0;
	g = 0x0001;
	group = 0;

	/**	モデムバッファのクリア	*/
	for(i = 0; i < 4; i++) {
		MDM_ModemBuffer[InNS][pos + i] = BIT_CLEAR;
	}

	group = CommandP->Option.OptionNumber.RelayGroupNumber;
	for(j = 0, i = 0; i < 4; i++) {	/*	４回ループ	３２バイトチェック	*/
		k = 0x01;
		dummy_group = 0;
		for(n = 0; n < 8; j++,n++) {/*	８回ループ	１バイトチェック	*/
			/**	グループNOのビットチェック	*/
			if (group & ((UDWORD)(g << j))) {
				dummy_group |= (UBYTE)(k << n);
			}
		}
		/**	１バイト分のグループNOセット	*/
		MDM_ModemBuffer[InNS][pos + i] = dummy_group;
	}
	/**	リターンモデムバッファのポインタ	*/
	return(pos + 3);
}


/*************************************************************************
	module		:[暗号化受信準備]
	function	:[
		1.暗号化受信可能なら受信ファイルのセットアップを行う
		2.空暗号化受信ＢＯＸを検索
		3.自機に指定されたメイルボックスが存在する
		4.メイルボックスの受信状態
		5.
	]
	return		:[ＯＫ--YES／ＮＧ--NO]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/06/18]
	author		:[山口 哲治]
*************************************************************************/
UBYTE SetUpCipherRx(void)
{
#if (PRO_CIPHER == ENABLE)
	UBYTE i;

	/* 空、暗号化受信番号の獲得 */
	CMN_DisableInterrupt();
	for (i = 0; i < SYS_CIPHERBOX_MAX; i++) {
		if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_NO) {
			break;
		}
	}
	if (i == SYS_CIPHERBOX_MAX) {	/* 全てのBOXが使用中、受信できない */
		FaxCompatibleErrorCode = NO_EMPTY_CIPHERBOX_ERROR;/* 暗号化受信BOXフルエラー	*/;
		CMN_EnableInterrupt();
		return(NO);
	}

	/* バックアップのため */
	SYB_CipherBox[i].Status = SYS_CIPHERBOX_RECEIVING;
	CMN_EnableInterrupt();

	/**	メモリ受信用アイテムセット（暗号化受信原稿）	*/
	SYS_RxMemoryFileItem = SYS_MEM_CIPHER_RX_FILE;
	/**	メモリ受信ファイルNO.に受信NO.	*/
	SYS_RxMemoryFileNo = (UWORD)i;
	SYS_RxMemoryFilePage = 1;
	SYS_RxMemoryFileBoxNumber = MEM_IGNORE_BOX_NUMBER;

	return(YES);
#else
	return(NO);
#endif
}

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* ワープ機能 By H.Hirao 1998/08/31 */
/*************************************************************************
	module		:[ワープ受信準備]
	function	:[1.ワープ機能が時間内かどうかのチェック 全て時間外の場合何もせずにリターン
				  2.コマンドファイルの空きを検索 空きが無い場合何もせずにリターン
				  3.ワープ転送する受信原稿をローカルのプリンタでプリントするかどうかのチェック
				  4.コマンドファイルのメンバ登録（ワンタッチダイヤル、短縮ダイヤル、グループ等登録）
				  5.メモリ受信ファイルアイテムを受信ファイルから送信ファイルに変更
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[有効なワープ機能の設定の中の同時プリントＯＮが優先される
				  RxOriginalModeCheck()からコールされる
	]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1998/08/31]
	author		:[平尾 英典]
*************************************************************************/
UBYTE SetUpWarpRx(void)
{
	struct	SYS_CommandData_t	 *comp;
	struct SYS_NumberDisplayTable *table;
	BYTE	is_warp_enable[SYS_WARP_MAX],
/*			is_nd_warp_enable[SYS_ND_MAX],*/	/* 1998/10/16 By M.Kuwahara */
			is_nd_warp_enable,
			warp_no,
/*			nd_warp_no,*/	/* 1998/10/16 By M.Kuwahara */
			command_no,
			exec_no,		/* added by H.Hirao 1999/01/12 */
			i,				/* added by H.Hirao 1999/01/12 */
			is_print;

	is_print	= 0;	/* 1998/10/07 By M.Kuwahara */
	exec_no		= 0;	/* added by H.Hirao 1999/01/12 */
	/*--------------------------------------------------*/
	/* ワープ機能が有効か原稿を印字するか否かのチェック */
	/*--------------------------------------------------*/
	CMN_DisableInterrupt();	/* 割り込み禁止 */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
		if (!CHK_WarpFunctionON()) {
			is_warp_enable[warp_no] = FALSE;
			continue;
		}
#endif
		is_warp_enable[warp_no] = CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_WarpFile[warp_no], FaxComStartTime);
		if (is_warp_enable[warp_no]) {
			is_print |= CMN_CheckWarpPrint(SYB_WarpFile[warp_no].Option);
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	is_nd_warp_enable = FALSE;
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL && CHK_ND_WarpON()) {	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信の時 */
 #else
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL) {	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信の時 */
 #endif
		/** ナンバーディスプレイ着信番号が、登録されているかのチェック 	1998/10/16 By M.Kuwahara */
		/** もし同じ番号が登録されていても、一番始めに検出されたものだけをセットする */
		table = CMN_ND_FindNdTableByPhoneNumber( SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial,
												 (UBYTE)CMN_StringLength(SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial));
		if (table != NULL) {
			/** ここで、現在受信中のナンバーディスプレイと登録されているナンバーディスプレイの比較をする */
			is_nd_warp_enable = 
						CMN_CheckWarpRange(&table->WarpData, FaxComStartTime);
			if (is_nd_warp_enable) {
				is_print |= CMN_CheckWarpPrint(table->WarpData.Option);
			}
		}
	}
 #if (0)	/* 1998/10/16 By M.Kuwahara */
//		for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//			/** ここで、現在受信中のナンバーディスプレイと登録されているナンバーディスプレイの比較をする */
//			is_nd_warp_enable[nd_warp_no] = 
//						CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_NumberDisplay[nd_warp_no].WarpData, FaxComStartTime);
//			if (is_nd_warp_enable[nd_warp_no]) {
//				is_print |= CMN_CheckWarpPrint(SYB_NumberDisplay[nd_warp_no].WarpData.Option);
//			}
//		}
//	}
 #endif
#endif
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
			break;
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
 #if (0)	/* 1998/10/16 By M.Kuwahara */
//	for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//		if (is_nd_warp_enable[nd_warp_no]) {
//			break;
//		}
//	}
//	if (warp_no == SYS_WARP_MAX && nd_warp_no == SYS_ND_MAX) {	/** ワープ機能がすべて時間外 */
 #endif
	if (warp_no == SYS_WARP_MAX && is_nd_warp_enable == FALSE) {	/** ワープ機能がすべて時間外 */
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (0);
	}
#else
	if (warp_no == SYS_WARP_MAX) {	/** ワープ機能がすべて時間外 */
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (0);
	}
#endif
	/*------------------------------*/
	/* コマンドファイルの空きを検索 */
	/*------------------------------*/
	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
#endif
			RelayedCommandNo = command_no;
			comp = &SYB_CommandFile[RelayedCommandNo];
			break;
		}
	}
	if (RelayedCommandNo == 0xFF) {	/** 空きコマンド無し */
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (0);
	}
	/*--------------------------*/
	/* 原稿をプリントするか否か */
	/*--------------------------*/
	if (is_print) {
		SYS_RxPrintFileItem		= SYS_MEM_RX_FILE;
		SYS_RxPrintFileNo		= SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage		= SYS_RxTotalPage + 1;
/*		SYB_CommandFile[RelayedCommandNo].Ability &= ~SYS_WARP_PRINT; 下に移動 1998/10/21 H.Yoshikawa */	/* 1998/10/09 By M.Kuwahara */
	}
	else {	/* 受信原稿が中継機にプリントされない時 1998/09/30 By M.Kuwahara */
/*		SYB_CommandFile[RelayedCommandNo].Ability |= SYS_WARP_PRINT;	下に移動 1998/10/21 H.Yoshikawa */
	}
	/*------------------------------*/
	/* コマンドファイルのメンバ登録 */
	/*------------------------------*/
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** ダイヤルデータ初期化 */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
#if (0)	/* 1998/10/06 By M.Kuwahara */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_WarpFile[warp_no].Onetouch[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Speed[0],
//							(UDWORD)SYB_WarpFile[warp_no].Group);
#else
 #if (0) /* comment by H.Hirao 1999/01/12 */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_WarpFile[warp_no].Direct[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Onetouch[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Speed[0],
//							(UDWORD)SYB_WarpFile[warp_no].Group);
 #else
			/* 
			** CMN_SetDialData()は、コールする毎に上書きされてしまいますので、結局最後の一件しか転送できません
			** by H.Hirao 1999/01/12
			*/
			for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
				comp->DialNumber.Direct[exec_no][i] = SYB_WarpFile[warp_no].Direct[i];
			}
			for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Onetouch[i] |= SYB_WarpFile[warp_no].Onetouch[i];
			}
			for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Speed[i] |= SYB_WarpFile[warp_no].Speed[i];
			}
			comp->DialNumber.Group |= SYB_WarpFile[warp_no].Group;
			if (++exec_no >= SYS_COM_DIRECT_DIAL_MAX) {
				break;
				/* SaveReturnAddressAndJumpBegin(); */
			}
 #endif
#endif
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
 #if (0)
//	for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//		if (is_nd_warp_enable[nd_warp_no]) {
// #if (0)	/* 1998/10/06 By M.Kuwahara */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Onetouch[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Speed[0],
//							(UDWORD)SYB_NumberDisplay[nd_warp_no].WarpData.Group);
// #else
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Direct[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Onetouch[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Speed[0],
//							(UDWORD)SYB_NumberDisplay[nd_warp_no].WarpData.Group);
// #endif
//		}
//	}
 #endif
	if (is_nd_warp_enable) {
 #if (0) /* comment by H.Hirao 1999/01/12 */
//		CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//						(UBYTE *)table->WarpData.Direct,
//						(UBYTE *)table->WarpData.Onetouch,
//						(UBYTE *)table->WarpData.Speed,
//						(UDWORD)table->WarpData.Group);
 #else
		/* 
		** CMN_SetDialData()は、コールする毎に上書きされてしまいますので、結局最後の一件しか転送できません
		** by H.Hirao 1999/01/12
		*/
		if (exec_no < SYS_COM_DIRECT_DIAL_MAX) {
			for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
				comp->DialNumber.Direct[exec_no][i] = table->WarpData.Direct[i];
			}
			for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Onetouch[i] |= table->WarpData.Onetouch[i];
			}
			for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Speed[i] |= table->WarpData.Speed[i];
			}
			comp->DialNumber.Group |= table->WarpData.Group;
		}
 #endif
	}
#endif
	CMN_EnableInterrupt();	/** 割り込み許可 */
	comp -> Option.Item = SYS_RELAYED_TX;	/** TBD 中継配信のアイテム */
	comp -> Option.ConfirmationReport	= NO;
	comp -> TitleMessage				= 0xFF;
/*	comp -> Ability						= NO;*/	/* 1998/10/06 By M.Kuwahara */
	if (is_print) {	/* 1998/10/21 H.Yoshikawa */
		comp -> Ability						&= ~SYS_WARP_PRINT;
	}
	else {
		comp -> Ability						|= SYS_WARP_PRINT;
	}
#if (PRO_DEPARTMENT == ENABLE)
	comp -> DepartmentCode				= 0xFFFF;
#endif
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp -> PIN_AccessMode			= PIN_ACCESS_MODE1;
	}
	else {
		comp -> PIN_AccessMode			= 0;
	}
#endif
	/*---------------------------------------------------------------------
	** Warpのチェックメッセージのときは、１ページ目にチェックメッセージ（キャラクタ部）
	** ２ページ目以降には、画像メモリをプリントします。
	** プリント中にJAMが発生した場合には、再プリントできるように、
	** キャラクタ部を０ページ目とカウントするようにします。
	** だから、初期化も０とします。プリント部には、これに対応したソフトが必要です
	** 1998/10/20 H.Yoshikawa
	*/
	if (is_print) {
		comp -> PrintPage					= 1;
	}
	else {
		comp -> PrintPage					= 0;
	}		
#if (0) /* TBD コマンドファイルの中継局IDバッファに標準IDをセット（不達通知用）*/
	if(SetTransmitStationID() == NO) {
		return (FALSE); /** TSI 不良エラー */
	}
#endif
	/*------------------------------------*/
	/* メモリ受信原稿ファイルアイテム変更 */
	/*------------------------------------*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;	/** SYS_MEM_RX_FILE -> SYS_MEM_TX_FILE */
	SYS_RxMemoryFileNo = RelayedCommandNo;				/* 1998/11/06 H.Yoshikawa */
	SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;			/* 1998/11/06 H.Yoshikawa */
	SYS_RxPrintFileBoxNumber = MEM_IGNORE_BOX_NUMBER;	/* 1998/11/06 H.Yoshikawa */

#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif

	return (0);
}


/*************************************************************************
	module		:[ワープ受信判断]
	function	:[1.ワープ機能が時間内かどうかのチェック 全て時間外の場合何もせずにリターン
				  2.コマンドファイルの空きを検索 空きが無い場合何もせずにリターン
	]
	return		:[
		TRUE
		FALSE
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1998/11/06]
	author		:[久保博]
*************************************************************************/
UBYTE CheckWarpRx(void)
{
	struct	SYS_CommandData_t	 *comp;
	struct SYS_NumberDisplayTable *table;
	BYTE	is_warp_enable[SYS_WARP_MAX],
			is_nd_warp_enable,
			warp_no,
			command_no,
			is_print;

	is_print	= 0;	/* 1998/10/07 By M.Kuwahara */
	/*--------------------------------------------------*/
	/* ワープ機能が有効か原稿を印字するか否かのチェック */
	/*--------------------------------------------------*/
	CMN_DisableInterrupt();	/* 割り込み禁止 */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
		if (!CHK_WarpFunctionON()) {
			is_warp_enable[warp_no] = FALSE;
			continue;
		}
#endif
		is_warp_enable[warp_no] = CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_WarpFile[warp_no], FaxComStartTime);
		if (is_warp_enable[warp_no]) {
			is_print |= CMN_CheckWarpPrint(SYB_WarpFile[warp_no].Option);
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	is_nd_warp_enable = FALSE;
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL && CHK_ND_WarpON()) {	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信の時 */
 #else
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL) {	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信の時 */
 #endif
		/** ナンバーディスプレイ着信番号が、登録されているかのチェック 	1998/10/16 By M.Kuwahara */
		/** もし同じ番号が登録されていても、一番始めに検出されたものだけをセットする */
		table = CMN_ND_FindNdTableByPhoneNumber( SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial,
												 (UBYTE)CMN_StringLength(SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial));
		if (table != NULL) {
			/** ここで、現在受信中のナンバーディスプレイと登録されているナンバーディスプレイの比較をする */
			is_nd_warp_enable = 
						CMN_CheckWarpRange(&table->WarpData, FaxComStartTime);
			if (is_nd_warp_enable) {
				is_print |= CMN_CheckWarpPrint(table->WarpData.Option);
			}
		}
	}
#endif
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
			break;
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	if (warp_no == SYS_WARP_MAX && is_nd_warp_enable == FALSE) {	/** ワープ機能がすべて時間外 */
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (FALSE);
	}
#else
	if (warp_no == SYS_WARP_MAX) {	/** ワープ機能がすべて時間外 */
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (FALSE);
	}
#endif
	/*------------------------------*/
	/* コマンドファイルの空きを検索 */
	/*------------------------------*/
#if (0)
**		/* １０１件目（SYS_COM_FILE_MAX + 1）のワープで、必ずアドレスエラーでリセット
**		** チェック関数なのに、コマンドファイルのステータスを書き換えてしまう。
**		** by H.Hirao 1999/03/04
**		*/
**	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
**		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
**			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
**#if (PRO_COMMANDFILE_SRAM == DISABLE)
**			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
**#endif
**			RelayedCommandNo = command_no;
**			comp = &SYB_CommandFile[RelayedCommandNo];
**			break;
**		}
**	}
**	if (RelayedCommandNo == 0xFF) {	/** 空きコマンド無し */
**		CMN_EnableInterrupt();	/** 割り込み許可 */
**		return (FALSE);
**	}
#endif
	CMN_EnableInterrupt();
	return TRUE;
}

#endif /* (PRO_RX_DOC_TRANSFER == ENABLE) */

 /** #if (PRO_KEYPANEL == PANEL_HINOKI) **/	/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
  #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
/*************************************************************************
	module		:[ＴＳＩを判断し、その番号にＦＡＸを折り返すためのコマンドファイルの作成]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[特ＲＯＭ(RDC-D83-002)]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1999/04/02]
	author		:[平尾 英典]
*************************************************************************/
void SetUpSpecialReplayTrans(void)
{
	struct	SYS_CommandData_t	 *comp;
	UBYTE	is_print;
	UBYTE	command_no;
	
#if (0)
** 	/* ＣＳから折り返し特ＲＯＭにおいて、センター側でも受信原稿をプリントしてほしいというＲＤＣが
** 	** 発行されたため、メモリスイッチ（UNISWJ-5-5）でON/OFFできるようにしておく。（RDC200100059)
** 	** by O.Kimoto 2001/02/22
** 	*/
** 	is_print = 0;	/* 原稿はプリントしない */
#else
	if (CHK_UNI_TSI_RelayTxCenterPrint()) {
		is_print = 1;	/* 原稿はプリントする */
	}
	else {
		is_print = 0;	/* 原稿はプリントしない */
	}
#endif
	
	CMN_DisableInterrupt();	/* 割り込み禁止 */
	/*------------------------------*/
	/* コマンドファイルの空きを検索 */
	/*------------------------------*/
	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
#endif
			comp = &SYB_CommandFile[command_no];
			RelayedCommandNo = command_no;
			break;
		}
	}
	CMN_EnableInterrupt();	/** 割り込み許可 */
	if (RelayedCommandNo == 0xFF) {	/** 空きコマンド無し */
		return;
	}
	if (SetTransmitStationID() == NO) {
		CMN_DisableInterrupt();	/* 割り込み禁止 */
		SYB_CommandFile[RelayedCommandNo].Status = SYS_CMD_EMPTY;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
		SYB_CommandStatus[RelayedCommandNo] = SYS_CMD_EMPTY;
#endif
		CMN_EnableInterrupt();	/** 割り込み許可 */
		RelayedCommandNo = 0xFF;
		return;
	}
	/*--------------------------*/
	/* 原稿をプリントするか否か */
	/*--------------------------*/
	if (is_print) {
		SYS_RxPrintFileItem		= SYS_MEM_RX_FILE;
		SYS_RxPrintFileNo		= SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage		= SYS_RxTotalPage + 1;
	}
	/*------------------------------*/
	/* コマンドファイルのメンバ登録 */
	/*------------------------------*/
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** ダイヤルデータ初期化 */
	CMN_MemorySet(&comp->DialNumber.Direct[0][0], SYS_DIRECT_DIAL_MAX, 0xFF);
	CMN_ASC_ToBCD_StringNum(&comp->DialNumber.Direct[0][0], &comp->Option.OptionNumber.RelaySourceID[0], (SYS_DIRECT_DIAL_MAX-1));
	comp -> Option.Item = SYS_MEMORY_TX;
	comp -> Option.ConfirmationReport	= NO;
	comp -> TitleMessage				= 0xFF;
	comp -> Ability						= NO;
#if (PRO_DEPARTMENT == ENABLE)
	comp -> DepartmentCode				= 0xFFFF;
#endif
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp -> PIN_AccessMode			= PIN_ACCESS_MODE1;
	}
	else {
		comp -> PIN_AccessMode			= 0;
	}
#endif
	if (is_print) {
		comp -> PrintPage				= 1;
	}
	else {
		comp -> PrintPage				= 0;
	}
	/*------------------------------------*/
	/* メモリ受信原稿ファイルアイテム変更 */
	/*------------------------------------*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;
	SYS_RxMemoryFileNo = RelayedCommandNo;
	SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
	SYS_RxPrintFileBoxNumber = MEM_IGNORE_BOX_NUMBER;

#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif

	return;
}
  #endif
 /**#endif**/	/**他の機種も特ＲＯＭ対応 1999.4.21 K.Kawata **/
/* SetUpSecureMailRx(WORD pos) よりここまでＭＭＬ専用 */
#endif	/* (PRO_MAKER == MML) */
