/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_INIT.C												 */
/*	モジュール	 :															 */
/*				 : void MakeHDLC_Frame(UBYTE,UBYTE)							 */
/*				 : UBYTE CheckHDLC_Command(void)							 */
/*				 : void FaxPPR_Transmit(BYTE)								 */
/*				 : BYTE CheckPPS_Frame(void)								 */
/*				 : void ResultECM_ModeSet(void)								 */
/*				 : void TransmitError(UBYTE, BYTE)							 */
/*				 : void ReceiveError(UBYTE)									 */
/*				 : void DialError(UBYTE)									 */
/*				 : void SetFaxComErrorMonitor(void)							 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ＨＤＬＣフレーム作成モジュール							 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\FCM_TBL.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"

/* MDM */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#include "\src\atlanta\mdm\orange\define\MDM_PRO.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
#include "\src\atlanta\mdm\r288f\define\MDM_PRO.H"
 #endif
#endif /* (PRO_MODEM == R288F) */

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/*************************************************************************
	module		:[ＨＤＬＣフレーム作成]
	function	:[
		1.アドレスフィールドセット
		2.制御フィールドセット
		3.ファクシミリフィールドセット
	]
	return		:[]
	common		:[
					TxNonStandardFrameByte_Count
					TxID_FrameByteCount
					TxStandardFrameByteCount
					MDM_ModemBuffer
					TxECM_Mode
					ECM_PageCounter
					ECM_BlockCounter
					ECM_FrameCounter
				]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300,SH7043]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/07]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeHDLC_Frame(UBYTE fcfcode,UBYTE option_code)
{
	WORD pos;
	pos = 0;
	/**	標準、独自、ＩＤフレームの送信バイト数変数初期化	*/
	TxNonStandardFrameByteCount = 0;
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;
/* #if (PRO_F_CODE == ENABLE) */
	/**	Ｆコードフレーム送信バイト数変数初期化	*/
	TxPasswordFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＰＷＤフレームのバイト数	*/
	TxSelectiveFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＳＥＰフレームのバイト数	*/
	TxSubaddressFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＳＵＢフレームのバイト数	*/
/* #endif */

	/**	アドレスフィールドセット	*/
	MDM_ModemBuffer[InSTD][pos] = ADDRESS_FIELD_DATA;
	pos++;
	/**	制御フィールドセット	*/
	MDM_ModemBuffer[InSTD][pos] = LAST_FRAME_DATA ;
	pos++;
	/*	ファクシミリ制御フィールドセット	*/
	switch (fcfcode) {		/**	ＦＣＦ種別	*/
		case CFR_F:	/**	ＣＦＲ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)( CFR_F );
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case FTT_F:	/**	ＦＴＴ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)( FTT_F );
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case CTR_F:	/**	ＣＴＲ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)( CTR_F );
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case EOM_F:	/**	ＥＯＭ	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PPS-EOMセット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | EOM_F );
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos + 1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-EOMセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | EOM_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	ＦＣＦセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(EOM_F);
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}
			break;
		case MPS_F:	/**	ＭＰＳ	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PPS-MPS セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 |MPS_F);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-MPSセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | MPS_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	ＦＣＦセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(MPS_F );
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}
			break;
		case EOP_F:	/**	ＥＯＰ	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PPS-EOP セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | EOP_F);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-EOPセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 |EOP_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	ＦＣＦセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(EOP_F);
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}

			break;
		case NULL_FF:	/**	ＮＵＬＬ＿ＦＦ	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PPS-NULL セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(NULL_FF);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-NULLセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(NULL_FF);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			break;
		case PRI_EOM_F:	/**	PRI_EOM	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PRI_EOM セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | PRI_EOM_F);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-PRI-EOMセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | PRI_EOM_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
					else {
						/**	PRI_EOMセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_EOM_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	PRI_EOMセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_EOM_F);
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}
			break;
		case PRI_MPS_F:	/**	PRI_MPS	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PRI_MPS セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 |PRI_MPS_F);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-PRI-MPSセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | PRI_MPS_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
					else {
						/**	PRI_MPSセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_MPS_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	ＦＣＦセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_MPS_F);
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}
			break;
		case PRI_EOP_F:	/**	PRI_EOP	*/
			if (TxECM_Mode == ECM_ON) {		/**	ECMモード	*/
				if (option_code == PPS_F) {		/**	部分頁信号	*/
					/**	PRI_EOP セット	*/
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
					pos++;
					MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | PRI_EOP_F);
					pos++;
					/**	ページ、ブロック、フレームカウンタセット	*/
					MDM_ModemBuffer[InSTD][pos] = ECM_PageCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_BlockCounter;
					pos++;
					MDM_ModemBuffer[InSTD][pos] = ECM_FrameCounter;
					/**	送信バイト数セット	*/
					TxStandardFrameByteCount = pos+1;
				}
				else {
					if (option_code == EOR_F) {		/**	再送終了	*/
						/**	EOR-PRI-EOPセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(option_code);
						pos++;
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(0x01 | PRI_EOP_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
					else {
						/**	PRI_EOMセット	*/
						MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_EOP_F);
						/**	送信バイト数セット	*/
						TxStandardFrameByteCount = pos+1;
					}
				}
			}
			else {
				/**	ＦＣＦセット	*/
				MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PRI_EOP_F);
				/**	送信バイト数セット	*/
				TxStandardFrameByteCount = pos+1;
			}
			break;
		case RR_F:	/**	ＲＲ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(RR_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case MCF_F:	/**	ＭＣＦ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(MCF_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case RTP_F:	/**	ＲＴＰ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(RTP_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case RTN_F:	/**	ＲＴＮ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(RTN_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case PIP_F:	/**	ＰＩＰ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PIP_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case PIN_F:	/**	ＰＩＮ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(PIN_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case RNR_F:	/**	ＲＮＲ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(RNR_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case ERR_F:	/**	ＥＲＲ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(ERR_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case DCN_F:	/**	ＤＣＮ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(DCN_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		case CRP_F:	/**	ＣＲＰ	*/
			/**	ＦＣＦセット	*/
			MDM_ModemBuffer[InSTD][pos] = (UBYTE)(CRP_F);
			/**	送信バイト数セット	*/
			TxStandardFrameByteCount = pos+1;
			break;
		default:
			break;
	}
}


/*************************************************************************
	module		:[ＨＤＬＣコマンドチェック]
	function	:[
		1.最終フレームの検索
		2.マルチフレーム例外処理
		3.標準コマンドの特定(FX NSS フレーム受信時は、NSFを標準コマンドとする)
	]
	return		:[ＦＳＫ命令ＦＣＦ部分]
	common		:[
					MDM_ModemBuffer
					FCFPoint
				]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/07]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE  CheckHDLC_Command(void)
{
	UWORD	   point;
	UWORD	   counter;
	UBYTE	   command;
	UBYTE	   search_fcf;
	UBYTE	   digital_signal_exist;

	digital_signal_exist = NO;
	/**	最終フレームの入ったモデムバッファを探す(0-8)	*/
#if (PRO_MODEM == ORANGE3)
	for(point = 0; point <= 8; point++) {
#else 
	for(point = 0; point < MODEM_BUFFER_MAX; point++) { /* 8 is replaced with MODEM_BUFFER_MAX by H.Kubo 1997/07/25 */
#endif
#if (PRO_MODEM == R288F)
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_22P) /* 空のモデムバッファに対応。by H.Kubo 1998/10/19  */
		if (MDM_RxSize[point] <= 1) {
		}
		else
#endif
#endif
		if(MDM_ModemBuffer[point][1] == LAST_FRAME_DATA) {
			FCF_Point = point;
			break;
		}
	}
	if (point != 0) {		/**	マルチフレームを受信した	*/
		/* NSF+DIS,NSF+CSI+DIS,CSI+DIS,NSC+DTC,NSC+CIG+DTC,CIG+DTC,TSI+DCS */
		/* NSS+TSI+DCS(MML),NSS+DCS(MML),TSI+NSS(FX) */
		/*	マルチフレームの処理　標準フレームの入ったモデムバッファを探す	*/
		for( counter = 0; counter <= FCF_Point; counter++){
			search_fcf = MDM_ModemBuffer[point][2];
#if (PRO_MODEM == R288F)
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_22P) /* 空のモデムバッファに対応。by H.Kubo 1998/10/19  */
			if (MDM_RxSize[point] <= 1) {
			}
			else
#endif
#endif
			if(( DCS_F == ( search_fcf & DCS_F ))||( DIS_F == ( search_fcf & DIS_F ))||( DTC_F == ( search_fcf & DTC_F ))){
				digital_signal_exist = YES;
				FCF_Point = point;
				break;
			}
			point--;
		}
	}
	command = ( UBYTE )(MDM_ModemBuffer[FCF_Point][2] );
	if ((command != DTC_F) && (command != NSC_F)) {		/**	ＤＴＣ､ＮＳＣではない	*/
		/**	ＦＣＦのＸビットを取り除く	*/
		command = (UBYTE)(MDM_ModemBuffer[FCF_Point][2] & 0xfe );
	}
	/**	return(FCF);*/
	return(command);
}

/*************************************************************************
	module		:[ＰＰＲ作成・送出]
	function	:[
		1.アドレスフィールド､コントロールフィールド､ＦＣＦ（ＰＰＲ）セット
		2.送信バイト数セット
		3.エラーフレームセット
		4.コマンド送信
	]
	return		:[]
	common		:[
						TxNonStandardFrameByteCount
						TxID_FrameByteCount
						TxStandardFramByteCount
						MDM_ModemBuffer
						ecm_stat
						ErrorFrame
				 ]
	condition	:[]
	comment		:[ecm_stat[]の内容はモデムのほうでセットして欲しい]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/07]
	author		:[鈴木 郁二]
*************************************************************************/
void FaxPPR_Transmit(WORD ErrorFrame)
{
	WORD			  byte_counter;
	WORD			  counter;

	/**	標準、独自、ＩＤフレームの送信バイト数変数初期化	*/
	TxNonStandardFrameByteCount = 0;
	TxID_FrameByteCount			 = 0;
	TxStandardFrameByteCount	= 0;
	/**	アドレスフィールド､制御フィールド､ファクシミリフィールドセット	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = PPR_F;

	/**	送信バイト数を大域変数に記憶	*/
	byte_counter = 3;
	TxStandardFrameByteCount = byte_counter + ECM_STATUS_MAX;

	if (ErrorFrame == 1) {		/**	全てのフレームがエラー	*/
		/**	モデムバッファ[3]--[34](32バイト)にＦＦをセット	*/
		for(counter = byte_counter; counter < TxStandardFrameByteCount; ){
			MDM_ModemBuffer[InSTD][counter++] = 0xff;
		}
	}
	else {
		/**	ecm_stat[]の内容をモデムバッファにセット	*/
		for( counter = 0; counter < ECM_STATUS_MAX; ){
			MDM_ModemBuffer[InSTD][ byte_counter++ ] =	MDM_EcmStatus[ counter++ ];
		}
	}
	/**	コマンド送信	*/
	MDM_TransmitCommand();
}

/*************************************************************************
	module		:[直前に受信したＰＰＳのＰＣ､ＢＣ､ＦＣとの比較]
	function	:[
		ブロックの取りこぼし防止のための処理
	]
	return		:[同（１）､違（０）､PPS_NULL/PPS_MPSではない（－１）]
	common		:[
					MDM_ModemBuffer
					ECM_PageCounter
					ECM_BlockCounter
					ECM_FrameCounter
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/08]
	author		:[鈴木 郁二]
*************************************************************************/
BYTE  CheckPPS_Frame(void)
{
/*
** ＥＣＭ受信にて、最終ページ受信時（PPS-EOP)、モード変更時(PPS-EOM)は、高低速識別で高速信号がとれなかったときに
** ＤＣＮを送出し、Ｒ４．２エラーになってしまう（日立テレコム不具合、ＫＩＲＩでのフィードバック）
** 全フレームエラーとしてリカバーするようにします
** 2000/03/01 by T.Soneoka
*/
#if (0)
**	if ((MDM_ModemBuffer[FCF_Point][3] == NULL_FF) || ((MDM_ModemBuffer[FCF_Point][3] & 0xfe) == MPS_F)) {		/**	PPS_NULLまたは､PPS_MPSである	*/
#else
	if ((MDM_ModemBuffer[FCF_Point][3] == NULL_FF)
	|| ((MDM_ModemBuffer[FCF_Point][3] & 0xfe) == MPS_F)
	|| ((MDM_ModemBuffer[FCF_Point][3] & 0xfe) == EOP_F)
	|| ((MDM_ModemBuffer[FCF_Point][3] & 0xfe) == EOM_F)) {
#endif
		if (ECM_PageCounter != MDM_ModemBuffer[FCF_Point][4]) {		/**	直前に受信したＰＣと今受信したＰＣが異なる	*/
			/**	エラーリターン（０）	*/
			return(NO);
		}
		else {
			if (ECM_BlockCounter != MDM_ModemBuffer[FCF_Point][5]) {		/**	直前に受信したＢＣと今受信したＢＣが異なる	*/
				/**	エラーリターン（０）	*/
				return(NO);
			}
			else {
				if (ECM_FrameCounter != MDM_ModemBuffer[FCF_Point][6]) {		/**	直前に受信したＦＣと今受信したＦＣが異なる	*/
					/**	エラーリターン（０）	*/
					return(NO);
				}
				else {
					/**	正常リターン（１）	*/
					return(YES);
				}
			}
		}
	}
	/**	エラーリターン（－１）PPS-NULL PPS-MPS ではない	*/
	return(-1);
}



/*************************************************************************
	module		:[ＥＣＭモードセット]
	function	:[
		ECM交信の場合､交信結果を記憶する大域変数にECMモードの交信だったことをセットする
	]
	return		:[]
	common		:[TxECMMode	RxECMMode]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/08]
	author		:[鈴木 郁二]
*************************************************************************/
void  ResultECM_ModeSet(void)
{
	if ((TxECM_Mode == ECM_ON) || (RxECM_Mode == ECM_ON)) {		/**	ECM送信､またはECM受信がON	*/
		/**	交信結果を記憶する大域変数にECMモードビットをセットする	*/
		FaxComResult = FaxComResult | ECM_MODE_SET;
	}
}


/*************************************************************************
	module		:[送信エラー処理]
	function	:[
		1.
	]
	return		:[]
	common		:[
					FaxComResult
					TxECM_Mode
					FaxComPerformingFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/08]
	author		:[鈴木 郁二]
*************************************************************************/
void  TransmitError(UBYTE error_number,/*	エラーナンバー	*/ char abort_flag)	/*	交信終了フラグ	*/
{
	/**	交信結果を記憶する大域変数に送信エラービットとエラーナンバーをセット	*/
	FaxComResult = TRANSMITERROR | error_number;
	if (TxECM_Mode == ECM_ON) {		/**	ECM送信	*/
		/**	交信結果を記憶する大域変数にECMモードをセット	*/
		FaxComResult |= ECM_MODE_SET;
	}
	if (abort_flag ==1) {		/**	交信終了フラグON	*/
		/**	交信中フラグOFF	*/
		FaxComPerformingFlag = 0;
	}
}

/*************************************************************************
	module		:[受信エラー処理]
	function	:[
		1.
	]
	return		:[]
	common		:[
					FaxComResult
					RxECM_Mode
					FaxComPerformingFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/08]
	author		:[鈴木 郁二]
*************************************************************************/
void  ReceiveError(UBYTE error_number/*	エラーナンバー	*/)
{
	/**	交信結果を記憶する大域変数に受信エラービットとエラーナンバーをセット	*/
	FaxComResult = RECEIVEERROR | error_number;
	if (RxECM_Mode == ECM_ON) {		/**	ECM受信	*/
		/**	交信結果を記憶する大域変数にECMモードをセット	*/
		FaxComResult |= ECM_MODE_SET;
	}
	/**	交信中フラグOFF	*/
	FaxComPerformingFlag = 0;
}


/*************************************************************************
	module		:[ダイヤルエラー]
	function	:[交信結果を記憶する大域変数にダイヤルエラービット､エラーナンバーをセット]
	return		:[]
	common		:[
					FaxComResult
					FaxComPerformingFlag
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/08]
	author		:[鈴木 郁二]
*************************************************************************/
void  DialError(UBYTE error_number)	/*		エラーナンバー	*/
{
	/**	交信結果を記憶する大域変数にダイヤルエラービット､エラーナンバーをセット	*/
	FaxComResult = DIALERROR | error_number;
	/**	交信中フラグをOFFする	*/
	FaxComPerformingFlag = 0;
}

/*************************************************************************
	module		:[通信エラーモニターのクリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/23]
	author		:[橘正樹]
*************************************************************************/
void	FCM_SetFaxComErrorMonitor(UWORD error_code, UWORD maker, UWORD line_number)
{
	UWORD	result;
	UBYTE	i;
	UBYTE	num;

	result = error_code & ~(ECM_MODE_SET|V34_MODE_SET);

	if (result == NO_ERROR) {
		return;
	}

	for (i = 0; i < SYS_FAXCOM_ERROR_MONITOR_MAX; i++) {
		if (FaxComErrorMonitorTable[i] == result) {
			break;
		}
	}
	if (i == SYS_FAXCOM_ERROR_MONITOR_MAX) {
		return;
	}

	if (line_number == 0) {
		num = 0;
	}
	else {
		num = 1;
	}

	CMN_DisableInterrupt();
	if (maker == YES) {
		SYB_FaxComErrorMonitor[num][i].MML_Count++;
	}
	else {
		SYB_FaxComErrorMonitor[num][i].OtherCount++;
	}
	CMN_EnableInterrupt();
}
