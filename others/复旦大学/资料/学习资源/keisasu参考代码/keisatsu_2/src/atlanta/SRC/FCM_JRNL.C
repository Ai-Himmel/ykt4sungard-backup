/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA	 ANZUを移植										 */
/*	ファイル名	 : FCM_JRNL.C												 */
/*	モジュール	 : SetJournal()												 */
/*				 : SetCOMEXEC_LocationJournal()								 */
/*				 : SetRemoteID_ToLocationJournal()							 */
/*				 : SaveT30Data()											 */
/*				 : SaveReceivedT30Data()									 */
/*				 : SaveT30TimingData()										 */
/*				 : SetPatJournalDataAtAutoFax(void)							 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ジャーナルのセットを行う									 */
/*				 : 分離型のジャーナルは存在しない							 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\syst30.h"

#if (PRO_FIP == ENABLE)
#include "\src\atlanta\define\fip_def.h"
#endif
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\mlt_data.h"	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */

#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\fcm_pro.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/05 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
#include "\src\atlanta\define\pat_def.h"
#include "\src\atlanta\define\pat_pro.h"
#include "\src\atlanta\ext_v\pat_data.h"
#include "\src\atlanta\ext_v\pat_tbl.h"
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/20 */
#include "\src\atlanta\define\cmn_nd.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#endif

#if defined (KEISATSU) 
#include  "\src\atlanta\define\sys_stat.h"	/* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/18 */
#include  "\src\atlanta\ext_v\man_data.h"	/* 警察FAX DVT_ID63 Added by SMuratec 夏 2005/12/13 */
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[ジャーナル・データを登録する]
	function	:[]
	commom		:[
		FaxComTXorRX_Sign		: 送信受信判別
		GrayModeFlag			: ハーフトーンモード
		FirstTxMode				: 送信モード
		TxMode					: 送信モード
		FaxComStartTime			: 通信開始時刻
		FaxComPeriod			: 通信時間
		SYS_TxTotalPage			: 送信ページ
		FaxComResult			: 通信結果
		SYS_FaxComType			: 通信種別
	]
	condition	:[]
	comment		:[
			修正履歴
			1.料金表に載せる部門コード毎の送受信ページ数のセット 94/9/12
	]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	SetJournal(void)
{
#if (0)	/* 1998/11/16 H.Yoshikawa */
//#if (PRO_NUMBER_DISPLAY == ENABLE) /* デバッグ用に通信管理記録に ND NG を載せる。 added by H.Kubo 1998/11/14 */
//		if ((NCU_ND_Status & ND_CALL_ACCEPTED) && !(NCU_ND_Status & ND_INFO_RECEIVED)) {
//			FaxComResult |= ND_NOT_RECEIVE;
//		}
//#endif
#endif
#if 0 /* 強制終了時も通信管理記録に載せます 05/11/22 石橋正和 */
// #if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/18 */
// 	if ( FaxComTXorRX_Flag ) {
// 		if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE) {
// 			return;
// 		}
// 	}
// #endif /* defined (KEISATSU) */
#endif
#if defined(KEISATSU)
	IsJournalCompleted = FALSE;			/* 警察FAX DVT_ID63 Added by SMuratec 夏 2005/12/13 */
#endif

	SetJournalQueueHostLine();	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */

		/*--------------------------*/
		/* 送信用ジャーナル・データ */
		/*--------------------------*/
		if ( FaxComTXorRX_Sign == TX_COM_MODE ) {		/** 送信 */
#if (PRO_PAT_JOURNAL == ENABLE)

			if (SYS_FaxComType != SYS_COMMAND_EXECUTE) {

				/* 相手先名 */
				SetRemoteID_ToLocationJournal();
				PAT_JournalDataToImage(LOCATION);

			}
			if ( GrayModeFlag == 1 ) {
				PAT_JournalWorkFile.Mode  = FirstTxMode;			/** 通信モード */
			}
			else{
				PAT_JournalWorkFile.Mode  = TxMode;
			}

			PAT_JournalWorkFile.TotalTime = FaxComPeriod;						/** 通信時間 */
/*			PAT_JournalWorkFile.Page	  = (UBYTE)SYS_TxTotalPage;		/@@ 通信ページ数 */
			PAT_JournalWorkFile.Page	  = SYS_TxTotalPage;		/** 通信ページ数 */
			PAT_JournalWorkFile.Result	  = FaxComResult;						/** 交信結果 */

			if (SYS_FaxComType == SYS_AUTO_CALLED) {
				switch (TxMemoryFileItem) {		/** メモリ送信種別 */
					case SYS_MEM_POLLING_FILE:		/** ポーリング送信原稿 */
						PAT_JournalWorkFile.Kind = SYS_POLLING_TX;
						break;

					case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング送信原稿 */
						PAT_JournalWorkFile.Kind = SYS_DB_POLLING_TX;
						break;

					case SYS_MEM_SUB_SECURE_FILE:	/* #if (PRO_F_CODE == ENABLE) */
					case SYS_MEM_SUB_BULLETIN_FILE:
						PAT_JournalWorkFile.Kind = SYS_SELECT_POLLING_TX;
						break;
					default:
						PAT_JournalWorkFile.Kind = 0xFF;
						break;
				}
				PAT_JournalDataToImage(NOTE);
			}

			PAT_JournalDataToImage(MODE);
			PAT_JournalDataToImage(TIME);
			PAT_JournalDataToImage(PAGE);
			PAT_JournalDataToImage(RESULT);

			/*PAT_SetJournal();*/
#endif
			SendMsgFaxComToMain(MSG_FAXCOM_SET_JOURNAL);

		}
		/*--------------------------*/
		/* 受信用ジャーナル・データ */
		/*--------------------------*/
		else if ( FaxComTXorRX_Sign == RX_COM_MODE ) {		/** 受信 */

#if (PRO_PAT_JOURNAL == ENABLE)
			if (SYS_FaxComType != SYS_COMMAND_EXECUTE) {

				/* 相手先名 */
				SetRemoteID_ToLocationJournal();
				PAT_JournalDataToImage(LOCATION);

			}
			PAT_JournalWorkFile.Mode	   = RxMode;							/** 通信モード */
			PAT_JournalWorkFile.TotalTime  = FaxComPeriod;						/** 交信時間 */
/*			PAT_JournalWorkFile.Page	   = (UBYTE)SYS_RxTotalPage;	/@@ 通信ページ数 */
			PAT_JournalWorkFile.Page	   = SYS_RxTotalPage;	/** 通信ページ数 */
			PAT_JournalWorkFile.Result	   = FaxComResult;						/** 交信結果 */

			PAT_JournalDataToImage(MODE);
			PAT_JournalDataToImage(TIME);
			PAT_JournalDataToImage(PAGE);
			PAT_JournalDataToImage(RESULT);

			if (SYS_FaxComType == SYS_AUTO_CALLED) {	/** 自動着信 */

				switch ( SYS_RxMemoryFileItem ) {	/** 受信原稿 */

					case SYS_MEM_SECURE_RX_FILE :		/** 親展受信原稿 */

						PAT_JournalWorkFile.Kind = SYS_SECURE_RX;
						PAT_JournalDataToImage(NOTE);
						break;

					case SYS_MEM_TX_FILE		:		/** メモリ送信原稿 (中継指示受信) */

						PAT_JournalWorkFile.Kind = SYS_RELAY_RX;
						PAT_JournalDataToImage(NOTE);
						break;

					case SYS_MEM_REMOTE_TX_FILE :		/** リモートＦＡＸ受信 */

						PAT_JournalWorkFile.Kind = SYS_REMOTE_RX;				/** リモートＦＡＸ受信 */
						PAT_JournalDataToImage(NOTE);
						break;

					case SYS_MEM_SUB_SECURE_FILE:	/* #if (PRO_F_CODE == ENABLE) */
					case SYS_MEM_SUB_BULLETIN_FILE:
						PAT_JournalWorkFile.Kind = SYS_SUBADDRESS_SECURE_RX;
						break;

					default:
						break;
				}
			}
			else if (SYS_FaxComType == SYS_FIP_CALLED) {		/** ＦＩＰ自動着信 */

				/* Journal->Kind = SYS_FIP_RECEIVE; 1995/05/22*/
				PAT_JournalWorkFile.Kind = SYS_FIP_RECEIVE;
				if ( SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE ) {
					/*Journal->Kind = SYS_FIP_SECURE; 1995/05/22*/
					PAT_JournalWorkFile.Kind = SYS_FIP_SECURE;
				}
				PAT_JournalDataToImage(NOTE);
			}
			else if (SYS_FaxComType == SYS_FIP_POLL) {		/** ＦＩＰポーリング */
				/*Journal->Kind = SYS_FIP_POLLING; 1995/05/22*/
				PAT_JournalWorkFile.Kind = SYS_FIP_POLLING;
				PAT_JournalDataToImage(NOTE);
			}

			/*PAT_SetJournal();*/
#endif
			SendMsgFaxComToMain(MSG_FAXCOM_SET_JOURNAL);

		}

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/20 */
		CMN_ND_SetFaxComReportOnNDJrnl(SYS_ND_CurrentJournalPoint);
#endif
}







#if (PRO_PAT_JOURNAL == ENABLE)
/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする（発呼）]
	function	:[]
	commom		:[
		SYB_SpeedDial[]			: 短縮ダイアル
		SYB_2ndSpeedDial[]		: 第２短縮ダイアル
		SYB_OnetouchDial[]		: ワンタッチダイアル
		SYB_2ndOnetouchDial[]	: 第２ワンタッチダイアル
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	SetCOMEXEC_LocationJournal(void)
{
	switch (DialKind) {	/** ダイアル種別 */

		/*================*/
		/*= 短縮ダイアル =*/
		/*================*/
		case SYS_SPEED_DIAL:		/** スピード・ダイアル */

			if ( SpeedDialPosition < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 */
			/*----------*/
			/* 第１短縮 */
			/*----------*/

				if (SYB_SpeedDial[SpeedDialPosition].Name[0] != 0x00) {	/** 相手先名が登録されている */
					CMN_StringCopyNumOrNULL(PAT_JournalWorkFile.RemoteID_TTI, SYB_SpeedDial[SpeedDialPosition].Name, 20);		/** 相手先名セット */
				}
				else if ((SYB_SpeedDial[SpeedDialPosition].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている */
					CMN_StringCopyNumOrNULL(&PAT_JournalWorkFile.RemoteID_TTI[0],
											&SYS_DialingNumber.Buffer[0], 20);		/** 相手先名にセット */
				}
			}
			break;

		/*========================*/
		/*= ワンタッチ・ダイアル =*/
		/*========================*/
		case SYS_ONETOUCH_DIAL:		/** ワンタッチ・ダイアル */
			if (SYB_OnetouchDial[OnetouchDialPosition].Name[0] != 0x00) {	/** 相手先名が登録されている */
				CMN_StringCopyNumOrNULL(PAT_JournalWorkFile.RemoteID_TTI,SYB_OnetouchDial[OnetouchDialPosition].Name, 20);		/** 相手先名セット */
			}
			else if ((SYB_OnetouchDial[OnetouchDialPosition].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている */
				CMN_StringCopyNumOrNULL(&PAT_JournalWorkFile.RemoteID_TTI[0],
										&SYS_DialingNumber.Buffer[0], 20);		/** 相手先名にセット */
			}
			break;

		/*================*/
		/*= 直接ダイアル =*/
		/*================*/
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
				CMN_StringCopyNumOrNULL(PAT_JournalWorkFile.RemoteID_TTI, &SYS_DialingNumber.Buffer[0], 20);		/** ダイアル・データを相手先名にセット */
				break;
		default:
				break;
	}
}


/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする]
	function	:[]
	commom		:[
		NonStandardID[]		: 非標準ＩＤ
		StandardID[]		: 標準ＩＤ
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	SetRemoteID_ToLocationJournal(void)
{
	if (NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(PAT_JournalWorkFile.RemoteID_TTI, (UBYTE *)&NonStandardID[0], 20);		/** 相手先名セット */
	}
	else if (StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(PAT_JournalWorkFile.RemoteID_TTI, (UBYTE *)&StandardID[0], 20);		/** 相手先名セット */
	}
}
#endif

/*-------------*/
/* T30 ﾓﾆﾀ関係 */
/*-------------*/

/*************************************************************************
	module		:[Save T30 data to T30Monitor.Buffer]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void SaveT30Data(UBYTE FrameKind, UBYTE *SourceBuffer, UWORD NumberOfByte)
{
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
	UWORD	pnt;
	UWORD	i;
	UWORD	old_write_pointer;
#endif

	if (NumberOfByte > 0x00FF) {	/* 1996/02/15 */
		NumberOfByte = 0x00FF;
	}

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
	if ((FrameKind == SYS_T30_TX_PIX) || (FrameKind == SYS_T30_RX_PIX)) {
		if (SYB_T30Monitor.A_Pointer == 0) {
			if (SYB_T30Monitor.WritePointer < (SYS_T30MONITOR_BUF_MAX-256)) {
				SYB_T30Monitor.A_Pointer = SYB_T30Monitor.WritePointer;
			}
		}
	}
	else {
		if (SYB_T30Monitor.A_Pointer == 0) {
			if ((SYB_T30Monitor.WritePointer >= 0x200) && (SYB_T30Monitor.WritePointer < (SYS_T30MONITOR_BUF_MAX-256))) {
				SYB_T30Monitor.A_Pointer = SYB_T30Monitor.WritePointer;
			}
		}
	}
#endif

	/*---------------------------------------------------------------*/
	/*	NumberOfByte : HDLCﾌﾚｰﾑのﾊﾞｲﾄ数（送信ﾌﾚｰﾑはFCSを含まない）	 */
	/*	2			 : FrameKind + T30_END_OF_FRAMEの分				 */
	/*---------------------------------------------------------------*/
	if ( (SYB_T30Monitor.WritePointer + 2 + NumberOfByte) < SYS_T30MONITOR_BUF_MAX ) {

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
		old_write_pointer = SYB_T30Monitor.WritePointer;
#endif

		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = FrameKind;
		if ( NumberOfByte != 0 ) {
			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)NumberOfByte;
			while( NumberOfByte-- != 0 ) {
				SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = *SourceBuffer++;
			}
		}
		/*-----------------------------------------------------------------*/
		/* T30ﾃﾞｰﾀ終了の判断がつけにくい為、毎回ﾌﾚｰﾑ･ｴﾝﾄﾞ(0xFF)を書き込む。*/
		/* もちろん、ﾎﾟｲﾝﾀｰは進めない。									   */
		/*-----------------------------------------------------------------*/
		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer] = SYS_T30_END_OF_FRAME;

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
		pnt = SYB_T30Monitor.WritePointer;
		if (pnt < 0x100) {
			if (SYB_T30Monitor.Flag == 0) {
				SYB_T30Monitor.BK_Pointer1 = pnt;
			}
			else {
				if (SYB_T30Monitor.BK_Pointer1 >= pnt) {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer1;
				}
				else {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer2;
					SYB_T30Monitor.BK_Pointer1 = pnt;
				}
			}
		}
		else if ((pnt >= 0x100) && (pnt < 0x200)) {
			if (SYB_T30Monitor.Flag == 0) {
				SYB_T30Monitor.BK_Pointer2 = pnt;
			}
			else {
				if (old_write_pointer < 0x100) {
					SYB_T30Monitor.BK_Pointer1 = old_write_pointer;
				}
				if (SYB_T30Monitor.BK_Pointer2 >= pnt) {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer2;
				}
				else {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer3;
					SYB_T30Monitor.BK_Pointer2 = pnt;
				}
			}
		}
		else if ((pnt >= 0x200) && (pnt < 0x300)) {
			if (SYB_T30Monitor.Flag == 0) {
				SYB_T30Monitor.BK_Pointer3 = pnt;
			}
			else {
				if (old_write_pointer < 0x200) {
					SYB_T30Monitor.BK_Pointer2 = old_write_pointer;
				}
				if (SYB_T30Monitor.BK_Pointer3 >= pnt) {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer3;
				}
				else {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer4;
					SYB_T30Monitor.BK_Pointer3 = pnt;
				}
			}
		}
		else {
			if (SYB_T30Monitor.Flag == 0) {
				SYB_T30Monitor.BK_Pointer4 = pnt;
			}
			else {
				if (old_write_pointer < 0x300) {
					SYB_T30Monitor.BK_Pointer3 = old_write_pointer;
				}
				if (SYB_T30Monitor.BK_Pointer4 >= pnt) {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer4;
				}
				else {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.A_Pointer;
					SYB_T30Monitor.BK_Pointer4 = pnt;
				}
			}

		}
#endif

	}
	else {
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
		if (SYB_T30Monitor.A_Pointer) {
			old_write_pointer = SYB_T30Monitor.WritePointer;
			SYB_T30Monitor.WritePointer = SYB_T30Monitor.A_Pointer;

			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = FrameKind;
			if ( NumberOfByte != 0 ) {
				SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)NumberOfByte;
				while( NumberOfByte-- != 0 ) {
					SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = *SourceBuffer++;
				}
			}
			/*-----------------------------------------------------------------*/
			/* T30ﾃﾞｰﾀ終了の判断がつけにくい為、毎回ﾌﾚｰﾑ･ｴﾝﾄﾞ(0xFF)を書き込む。*/
			/* もちろん、ﾎﾟｲﾝﾀｰは進めない。									   */
			/*-----------------------------------------------------------------*/
			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer] = SYS_T30_END_OF_FRAME;
			SYB_T30Monitor.Flag++;

			pnt = SYB_T30Monitor.WritePointer;
			if (pnt < 0x100) {
				if (SYB_T30Monitor.BK_Pointer1 >= pnt) {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer1;
				}
				else {
					SYB_T30Monitor.B_Pointer = SYB_T30Monitor.BK_Pointer2;
					SYB_T30Monitor.BK_Pointer1 = pnt;
				}
			}
			else {
				/* ありえない */
				outp((UDWORD)0,(UBYTE)0);/* WriteProtectError for ICE */
			}

		}
		else {
			SYB_T30Monitor.WritePointer = SYS_T30MONITOR_BUF_MAX - 1;
		}
#else
		/*--------------------------------------------------------------------*/
		/* T30ﾊﾞｯﾌｧに収まらなければ、ﾗｲﾄﾎﾟｲﾝﾀｰを最後にしておきます 1996/01/25 */
		/*--------------------------------------------------------------------*/
		SYB_T30Monitor.WritePointer = SYS_T30MONITOR_BUF_MAX - 1;
#endif
	}
}


/*************************************************************************
	module		:[Save received T30 data to T30Monitor.Buffer]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void  SaveReceivedT30Data(void)
{
	WORD	i = 0;
	while ( i < MODEM_BUFFER_MAX ) {	/** モデムバッファ本数 */
		if (MDM_RxSize[i] != 0) {

			/* 1997/02/01 -> 1998/03/27 Y.Murata cloverより移植
			 * 画ﾃﾞｰﾀを受信してﾎﾟｽﾄﾒｯｾｰｼﾞを受信した時にT30にFCD、RCPが載る事がある
			 * これは、FSK受信する時にまだ、ﾌﾚｰﾑを受信していないのにﾓﾃﾞﾑ割り込みで
			 * FCSﾁｪｯｸOKのﾊﾟｽに入ってしまいﾌﾚｰﾑｻｲｽﾞ（MDM_RxSize[]に入る）を獲得してしまう起こる
			 * 一応FCD、RCPがT30に載るだけみたいなので、ここではじきます
			*/
			if (MDM_ModemBuffer[i][2] == 0x06) {	/* FCD */
				i++;
				continue;
				/*return; 1997/10/16*/
			}
			if (MDM_ModemBuffer[i][2] == 0x86) {	/* RCP */
				i++;
				continue;
				/*return; 1997/10/16*/
			}

			SaveT30Data(SYS_T30_RX_FRAME, &MDM_ModemBuffer[i][0], MDM_RxSize[i]);
		}
		if (MDM_ModemBuffer[i][LAST_FRAME_POS] == LAST_FRAME_DATA) {
			break;
		}
		i++;
	}
}


/*************************************************************************
	module		:[Save T30 Timing data to T30Monitor.Buffer]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void  SaveT30TimingData(UBYTE FrameKind)
{
	/*--------------------------------------------*/
	/*	2	: intﾀｲﾌﾟのGenaralTimerのﾊﾞｲﾄ数		  */
	/*	2	: FrameKind + T30_END_OF_FRAMEの分	  */
	/*--------------------------------------------*/
	if ( (SYB_T30Monitor.WritePointer + 2 + 2) < SYS_T30MONITOR_BUF_MAX ) {
		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = FrameKind;
		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)((SYS_GeneralTimer>>8)&0xFF);	/* 上位 */
		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)(SYS_GeneralTimer&0xFF);		/* 下位 */
		SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer]	 = SYS_T30_END_OF_FRAME;
	}
	else {
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
		if (SYB_T30Monitor.A_Pointer) {
			SYB_T30Monitor.WritePointer = SYB_T30Monitor.A_Pointer;

			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = FrameKind;
			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)((SYS_GeneralTimer>>8)&0xFF);	/* 上位 */
			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer++] = (UBYTE)(SYS_GeneralTimer&0xFF);		/* 下位 */
			SYB_T30Monitor.Buffer[SYB_T30Monitor.WritePointer]	 = SYS_T30_END_OF_FRAME;

			SYB_T30Monitor.Flag = 1;
		}
		else {
			/*--------------------------------------------------------------------*/
			/* T30ﾊﾞｯﾌｧに収まらなければ、ﾗｲﾄﾎﾟｲﾝﾀｰを最後にしておきます 1996/01/25 */
			/*--------------------------------------------------------------------*/
			SYB_T30Monitor.WritePointer = SYS_T30MONITOR_BUF_MAX - 1;
		}
#else
		/*--------------------------------------------------------------------*/
		/* T30ﾊﾞｯﾌｧに収まらなければ、ﾗｲﾄﾎﾟｲﾝﾀｰを最後にしておきます 1996/01/25 */
		/*--------------------------------------------------------------------*/
		SYB_T30Monitor.WritePointer = SYS_T30MONITOR_BUF_MAX - 1;
#endif
	}
}

/*************************************************************************
	module		:[自動送信時にジャーナルをセットする]
	function	:[
		1. 通番
		2. 相手先名
		3. 通信開始時刻
		4. 部門コード
		5. 備考
	]
	return		:[]
	common		:[ジャーナルセットを関数化した]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/11/28]
	author		:[山口]
*************************************************************************/
void SetPatJournalDataAtAutoFax(void)
{
	/*-----------------------*/
	/** ジャーナル通番セーブ */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount			= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount			= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

	if (FCM_CheckCommandTRx() == COMMAND_KIND_TX) {
		PAT_JournalWorkFile.Number = JournalTxTotalCount;
	}
	else {	/** 受信 */
		PAT_JournalWorkFile.Number = JournalRxTotalCount;
	}
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Kind = CommandFileOptionItem;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
 #if (PRO_DEPARTMENT == ENABLE)
	PAT_JournalWorkFile.DepartmentCode = (CommandFileDepartmentCode != 0) ? CommandFileDepartmentCode : 0;
 #endif
	SetCOMEXEC_LocationJournal();		/* 相手先名 */

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(LOCATION);
	PAT_JournalDataToImage(START);
 #if (PRO_DEPARTMENT == ENABLE)
	PAT_JournalDataToImage(DCODE);
 #endif
	PAT_JournalDataToImage(NOTE);
#endif
}


/*************************************************************************
	module		:[キャラクタジャーナル記載用データセット CHAR_JOURNAL]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1998/02/03]
	author		:[村田]
*************************************************************************/
void	SetJournalQueueHostLine(void)
{
	if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {
		SYS_Opt[0].CommandFileOptionItem = CommandFileOptionItem;
		SYS_Opt2[0].QueueKind = SYS_CurrentExecutingCommand->Kind;
		SYS_Opt2[0].CommandDepartmentCode = CommandFileDepartmentCode;
		SYS_Opt2[0].QueueDialItem = SYS_CurrentExecutingCommand->ExecDial.Item;
		switch (SYS_Opt2[0].QueueDialItem) {
		case SYS_ONETOUCH_DIAL:
			SYS_Opt2[0].QueueDialOffset = (UWORD)SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch;
			break;
		case SYS_SPEED_DIAL:
			SYS_Opt2[0].QueueDialOffset = (UWORD)SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed;
			break;
		case SYS_DIRECT_DIAL:
			if (SYS_Opt2[0].QueueKind == SYS_COMMAND_TRX) {
				CMN_StringCopyNum(&SYS_Opt2[0].CommandDirectDial[0], &CommandP->DialNumber.Direct[DirectNumberPosition][0], 20);
			}
			else if (SYS_Opt2[0].QueueKind == SYS_BATCH_TX) {
				CMN_StringCopyNum(&SYS_Opt2[0].CommandDirectDial[0], BatchP->DialNumber[DirectNumberPosition].FaxNumber.Direct, 20);
			}
#if (PRO_CONTINUOUS_POLLING == ENABLE)
			else {
				CMN_StringCopyNum(&SYS_Opt2[0].CommandDirectDial[0], ContPollingP->DialNumber.Direct[DirectNumberPosition], 20);
			}
#endif
			break;
		default:
			break;
		}
	}
}

