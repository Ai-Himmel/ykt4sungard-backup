/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA	 ANZUを移植										 */
/*	ファイル名	 : FCM_FSUB.C												 */
/*	モジュール	 :															 */
/*				 : FaxTimer()												 */
/*				 : FaxRxDCS_SemiCompatibleCheck()							 */
/*				 : FaxHDLC_Transmit()										 */
/*				 : SendMsgFaxComToMain()									 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ＦＣＭサブ関数											 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_def.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/05 */
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (POR_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif
#if (1) /* (PRO_TX_SPEED == V34) */
#include "\src\atlanta\define\man_pro.h"
#endif /* (1) */ /* (PRO_TX_SPEED == V34) */

/*************************************************************
*				BY:	 M.HARADA
*			  DATE:	 Mon 15 Feb. 1993
*	  ROUTINE NAME:	 FaxTimer()
*	   DESCRIPTION:	 通信用タイマー
*		   RETURNS:	 無し
*		 CALLED BY:	 色々
*		　変更履歴:	 1994/12/6	M.H.  引き数（set_timer）が０のときは、タイムカウントしないように変更。
***************************************************************/
void		FaxTimer( UWORD	 set_timer )
{
	UWORD	start_timer;
	UWORD	timer;

	set_timer	  = set_timer / 10;
	start_timer	  = SYS_GeneralTimer;
	timer		  = ( UWORD )1;

	if(set_timer != 0){
		while(( UWORD )( SYS_GeneralTimer - start_timer ) < ( set_timer )){
			wai_tsk(timer);
		}
	}
}

/************************************************************
*				BY:	 M.HARADA
*	  ROUTINE NAME:	 FaxRxDCS_SemiCompatibleCheck()
*	   DESCRIPTION:　相手送信機指定ＴＣＦ受信ボーレイト設定[DCS/CTC]
*		   RETURNS:	 無し
*		 CALLED BY:	 FaxRxPhaseb1()
*					 FaxRxNegotiate()
**************************************************************/
void   FaxRxDCS_SemiCompatibleCheck(void)
{
	UBYTE datarate;

	datarate = ( UBYTE )((MDM_ModemBuffer[FCF_Point][4] >> 2) & 0x0f);

	if (SYS_V34ProcedureExecuting() == 0) {	/** Ｖ３４でない */

		switch (datarate) {
			case 0x00:
				RxBaudRate = BPS2400_V27;
				break;
			case 0x02:
				RxBaudRate = BPS4800_V27;
				break;
			case 0x01:
				RxBaudRate = BPS9600_V29;
				break;
			case 0x03:
				RxBaudRate = BPS7200_V29;
				break;
			case 0x04:
				RxBaudRate = BPS14400_V33;
				break;
			case 0x06:
				RxBaudRate = BPS12000_V33;
				break;
			case 0x08:
				RxBaudRate = BPS14400_V17;
				break;
			case 0x0A:
				RxBaudRate = BPS12000_V17;
				break;
			case 0x09:
				RxBaudRate = BPS9600_V17;
				break;
			case 0x0B:
				RxBaudRate = BPS7200_V17;
				break;
			default:
				break;
		}
	}
}


/******************************************************
*				BY:	 M.HARADA
*			  DATE:	 Sat 18 Jul 1992
*	  ROUTINE NAME:	 FaxHDLC_Transmit()
*	   DESCRIPTION:	 コマンドの送出
*		   RETURNS:	 無し
*		 CALLED BY:	 色々
*****************************************************/
void	  FaxHDLC_Transmit( UBYTE	fcfcode, UBYTE option_code )
{
	MakeHDLC_Frame( fcfcode, option_code );

#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1997/08/05 */
	FCM_TransmitCommand();
#else /* (PRO_TX_SPEED == V34) */
	MDM_TransmitCommand();
#endif /* (PRO_TX_SPEED == V34) */
}

/*************************************************************************
	module		:[メインタスクへメッセージ送信]
	function	:[
		1.	Item に FROM_FAXCOM をセットにする
		2.	MAN_Task へ snd_msg() する
		3.	MAN_Task から同期用の rcv_msg() する
	]
	return		:[]
	common		:[
		MsgFromFaxComToMain
	]
	condition	:[
		Messageは引き数で指定
		SubMessage1…は必要なら上位でセット
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[FCM]
	date		:[1994/07/26]
	author		:[竹内茂樹]
*************************************************************************/
void		SendMsgFaxComToMain(
	UWORD	message)
{
	MsgFromFaxComToMain.Item	= FROM_FAXCOM;
	MsgFromFaxComToMain.Message	= message;

	snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
	rcv_msg( mbxno.FCM_Task, &FcomMsg );
}

/*************************************************************************
	module		:[コマンド通信の送受信識別]
	function	:[
		1.コマンドファイルのオプションアイテムを調べて、送信であるか、受信であるかを
		  返す。
	]
	return		:[COMMAND_KIND_TX	0
				  COMMAND_KIND_RX	1
				 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/05/07]
	author		:[山口　哲治]
*************************************************************************/
UBYTE FCM_CheckCommandTRx(void)
{
	switch (CommandFileOptionItem) {
	case	SYS_SCANNER_TX:
	case	SYS_MEMORY_TX:
	case	SYS_DELAYED_SCANNER_TX:
	case	SYS_DELAYED_MEMORY_TX:
	case	SYS_SCANNER_SECURE_TX:
	case	SYS_MEMORY_SECURE_TX:
	case	SYS_SCANNER_RELAY_BROADCAST:
	case	SYS_MEMORY_RELAY_BROADCAST:
	case	SYS_DELAYED_BROADCAST:
	case	SYS_RELAYED_TX:
	case	SYS_RELAYED_TX_REPORT:		/* MOMIJI 1995/02/15 */
	case	SYS_BATCH_MEMORY_TX:		/* 一括送信 */
#if (PRO_F_CODE == ENABLE)
	case	SYS_SCANNER_SUB_ADDRESS_TX:	/*	Ｆｺｰﾄﾞｽｷｬﾅ送信(親展・掲示板に送信） */
	case	SYS_MEMORY_SUB_ADDRESS_TX:	/*	Ｆｺｰﾄﾞﾒﾓﾘ送信(親展・掲示板に送信） */
#endif
#if (PRO_CIPHER == ENABLE)
	case	SYS_CIPHER_TX:				/* 暗号化送信 */
#endif
		return(COMMAND_KIND_TX);		/** 送信 */
		break;
	case	SYS_POLLING_RX:
	case	SYS_DB_POLLING_RX:
	case	SYS_SEQUENTIAL_POLLING:
	case	SYS_CONTINUOUS_POLLING_RX:
#if (PRO_F_CODE == ENABLE)
	case	SYS_SELECT_POLLING_RX:		/* 1997/01/23  By T.Yamaguchi */
#endif
		return(COMMAND_KIND_RX);		/** 受信 */
		break;
	default:
		break;	/* ここに来たらバグ */
	}
}
