/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMMKCTC.C												 */
/*	モジュール	 :															 */
/*				 : MakeCTC_FIF()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : CTCのFIFを作成(DCS の1-16ビット)							 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSMAX.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"

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

/*************************************************************************
	module		:[MakeCTCFIF()]
	function	:[
		CTCのFIFを作成(DCS の1-16ビット)
		1.アドレスフィールドセット
		2.ラストフレーム
		3.FCFセット(CTC)
		4.伝送速度セット
		5.線密度セット
		6.符号化方式セット
	]
	return		:[なし]
	common		:[
					TxNonStandardFrameByteCount
					TxID_FrameByteCount
					TxStandardFrameByteCount
					MDM_ModemBuffer
					TxBaudRate
					TxMode
					TxCodingMethod
				]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/01]
	author		:[鈴木 郁二]
*************************************************************************/
void MakeCTC_FIF(void)
{
	/**	各フレーム送信バイト数大域変数初期化	*/
	TxNonStandardFrameByteCount = 0;
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;
	/**	モデムバッファにアドレスフィールド､制御フィールド､FCFセット､第３バイトは０クリア	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = CTC_F;
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR;
	MDM_ModemBuffer[InSTD][4] = DCS_FIF_2ND_BYTE;

	switch (TxBaudRate) {		/**	送信ボーレート	*/
			/*	それぞれのポーレート	*/
			/*	ボーレートに対応したテーブルをモデムバッファにセット	*/
		case BPS2400_V27:	/**	2400BPS	*/
			/**	V27-2400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V27_2400BPS_BIT;
			break;
		case BPS4800_V27:	/**	4800BPS	*/
			/**	V27-4800BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V27_4800BPS_BIT;
			break;
		case BPS7200_V29:	/**	V29-7200BPS	*/
			/**	V29-7200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V29_7200BPS_BIT;
			break;
		case BPS9600_V29:	/**	V29-9600BPS	*/
			/**	V29-9600BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V29_9600BPS_BIT;
			break;
		case BPS7200_V17:	/**	V17-7200BPS	*/
			/**	V17-7200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_7200BPS_BIT;
			break;
		case BPS9600_V17:	/**	V17-9600BPS	*/
			/**	V17-9600BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_9600BPS_BIT;
			break;
		case BPS12000_V17:	/**	V17-12000BPS	*/
			/**	V17-1200BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_12000BPS_BIT;
			break;
		case BPS14400_V17:	/**	V17-14400BPS	*/
			/**	V17-14400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V17_14400BPS_BIT;
			break;
		case BPS12000_V33:	/**	V33-12000BPS	*/
			/**	V33-12000BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V33_12000BPS_BIT;
			break;
		case BPS14400_V33:	/**	V33-14400BPS	*/
			/**	V33-14400BPSビットON	*/
			MDM_ModemBuffer[InSTD][4] |= DATA_V33_14400BPS_BIT;
			break;
	}
	switch (TxMode) {		/**	送信線密度	*/
#if 1 /* 中間調の場合が抜けていました。 added by H.Kubo 1998/09/24 */
		case SYS_GRAY16:		/**	中間調１６	*/
		case SYS_GRAY16_SEP:	/**	中間調１６_SEP	*/
		case SYS_GRAY32:		/**	中間調３２	*/
		case SYS_GRAY32_SEP:	/**	中間調３２_SEP	*/
		case SYS_GRAY64:		/**	中間調６４	*/
		case SYS_GRAY64_SEP:	/**	中間調６４_SEP	*/
		case SYS_GRAY128:
		case SYS_GRAY128_SEP:
		case SYS_EFINE: /** E-FINE(R12*11.55L/mm)は、FINEﾋﾞｯﾄＯＮ 96/06/14 By t.yamaguchi */
#endif
		case SYS_FINE:	/**	ノーマル､ファインのみセット	*/
			MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;
			break;
		default:
			break;
	}
	switch (TxCodingMethod) {		/**	送信符号化方式	*/
		case SYS_MR_CODE:	/**	MRのみセット	*/
			MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
			break;
		default:
			break;
	}
	/**	送信バイト数５セット	*/
	TxStandardFrameByteCount = 5;
}
