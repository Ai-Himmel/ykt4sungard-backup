/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA													 */
/*	ファイル名	 : FCM_FCD.C												 */
/*	モジュール	 :															 */
/*				 : FCM_Task()												 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1997/01/09												 */
/*	概	要		 : Ｆコード関連モジュール									 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mem_pro.h"

#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sysspeed.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\sysfcode.h"	/* 1997/01/09  By T.Yamaguchi */


#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\atd_data.h"

#if (PRO_FCODE_RELAY == ENABLE)
 #include "\src\atlanta\define\status.h"
#endif

/****************/
/* Ｆコード関連 */
/****************/

/*#if (PRO_F_CODE == ENABLE)*/
/*************************************************************************
	module		:[ＰＷＤフレーム作成（送信用）]
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
	date		:[1996/06/14]
	author		:[村田]
*************************************************************************/
void MakeTX_PWD_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxPasswordFrameByteCount = 0;

	if (PartnerT_PWD_Ability) {
		/*	ＰＷＤフレーム作成	*/
		MDM_ModemBuffer[InPWD][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InPWD][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InPWD][2] = T_PWD_F;
		if (DIS_ReceivedFlag == YES) {		/**	ＤＩＳを受信	*/
			MDM_ModemBuffer[InPWD][2] |= X_BIT;
		}

		if (MakePWD_FIF_Sub() == YES) {
			TxPasswordFrameByteCount = 23;
		}
	}
}


/*************************************************************************
	module		:[ＰＷＤフレーム作成（ポーリング用）]
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
	date		:[1996/06/14]
	author		:[村田]
*************************************************************************/
void MakePOL_PWD_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxPasswordFrameByteCount = 0;

	if (PartnerP_PWD_Ability) {
		/*	ＰＷＤフレーム作成	*/
		MDM_ModemBuffer[InPWD][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InPWD][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InPWD][2] = P_PWD_F;

		if (MakePWD_FIF_Sub() == YES) {
			TxPasswordFrameByteCount = 23;
		}
	}
}


/*************************************************************************
	module		:[ＰＷＤフレーム作成サブ]
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
	date		:[1996/06/14]
	author		:[村田]
*************************************************************************/
UBYTE MakePWD_FIF_Sub(void)
{
	return (SetF_CODE_ID(&OwnPasswordFrameID[0], InPWD));
}


/*************************************************************************
	module		:[ＳＥＰフレーム作成]
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
	date		:[1996/06/14]
	author		:[村田]
*************************************************************************/
void MakeSEP_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxSelectiveFrameByteCount = 0;

	if (PartnerSEP_Ability) {
		/*	ＳＥＰフレーム作成	*/
		MDM_ModemBuffer[InSEP][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InSEP][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InSEP][2] = SEP_F;

		if (SetF_CODE_ID(&OwnSelectivePollingFrameID[0], InSEP) == YES) {
			TxSelectiveFrameByteCount = 23;
		}
	}
}


/*************************************************************************
	module		:[ＳＵＢフレーム作成]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[山口]
*************************************************************************/
void MakeSUB_FIF(void)
{
	/**	送信バイト数変数初期化	*/
	TxSubaddressFrameByteCount = 0;

	if (PartnerSUB_Ability) {
		/*	ＳＵＢフレーム作成	*/
		MDM_ModemBuffer[InSUB][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InSUB][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InSUB][2] = SUB_F;
		if (DIS_ReceivedFlag == YES) {		/**	ＤＩＳを受信	*/
			MDM_ModemBuffer[InSUB][2] |= X_BIT;
		}

		if(SetF_CODE_ID(&OwnSubaddressFrameID[0], InSUB) == YES) {
			TxSubaddressFrameByteCount = 23;
		}
	}
}


/*************************************************************************
	module		:[Ｆコード確定]
	function	:[
		1.相手機のＦコード能力の獲得
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/09]
	author		:[山口]
*************************************************************************/
UBYTE SetTxF_CODE(void)
{
	PartnerT_PWD_Ability = 0;
	PartnerSEP_Ability = 0;
	PartnerSUB_Ability = 0;

	if (RxStandardFrameByteCount > 8) {
		/* 選択ポーリング受信ビットチェック */
		if (MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT) {
			if (MDM_ModemBuffer[StdFrmPos][8] & SELECTIVE_POLLING_BIT) {
				PartnerSEP_Ability = 1;
			}
		}
		/* サブアドレス、パスワードビットチェック */
		if (RxStandardFrameByteCount > 9) {
			if (MDM_ModemBuffer[StdFrmPos][8] & EXPAND_FIELD_BIT) {
				if (MDM_ModemBuffer[StdFrmPos][9] & SUBADDRESSING_BIT) {
					PartnerSUB_Ability = 1;
				}
				if (MDM_ModemBuffer[StdFrmPos][9] & PASSWORD_BIT) {
					PartnerT_PWD_Ability = 1;
				}
			}
		}
	}
	return(FcodeCompatibleCheck());
}
/*************************************************************************
	module		:[Ｆコード能力ｺﾝﾊﾟﾁﾁｪｯｸ]
	function	:[
		1.Ｆコード通信のとき、相手機の能力をﾁｪｯｸする
		  ＰＷＤの能力はチェックしない
	]
	return		:[YES:
				  NO:
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/23]
	author		:[山口哲治]
*************************************************************************/
UBYTE FcodeCompatibleCheck(void)
{
	if(SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/**	FaxComType	コマンド実行	*/
		switch(CommandFileOptionItem) {	/**	コマンドタイプ(CommandFileOptionItem)	*/
		case SYS_SCANNER_SUB_ADDRESS_TX:	/**	スキャナサブアドレス送信	*/
		case SYS_MEMORY_SUB_ADDRESS_TX:		/**	メモリサブアドレス送信	*/
			if (PartnerSUB_Ability == 0) {
				FaxCompatibleErrorCode = SUB_ABILITY_ERROR;
				return(NO);
			}
			break;
		case SYS_SELECT_POLLING_RX:			/**	選択ポーリング受信	*/
			if (PartnerSEP_Ability == 0) {
				FaxCompatibleErrorCode = SEP_ABILITY_ERROR;
				return(NO);
			}
			break;
		default:
			break;
		}
	}
	else if ((SYS_FaxComType == SYS_AUTO_CALLED)
		  || (SYS_FaxComType == SYS_MANUAL_RX)) {			/**	FaxComType	コマンド実行	*/
		PWDP_BitEnable = 0;	/* 初期化 */
		SEP_BitEnable = 0;

		if (PartnerSEP_Ability) {		/* 選択ポーリング送信 */
			if (SEP_FrmName == NO) {
				return(NO);
			}
			SEP_BitEnable = 1;
		}
		else {
			if (SEP_FrmName == NO) {
				return(NO);				/* 通常のポーリング送信 */
			}
			else {
				if (!CHK_UNI_OldFCodeBit()) {
					return(NO);			/* 通常のポーリング送信 */
				}
				SEP_BitEnable = 1;
			}
		}
		if (PartnerT_PWD_Ability == 1) {
			if (PWD_FrmName != NO) {	/* PWDﾋﾞｯﾄが立っているにもかかわらずPWD_IDを送ってこない */
				PWDP_BitEnable = 1;
			}
		}
		else {
			if (PWD_FrmName != NO) {	/* PWDﾋﾞｯﾄが立っていないにもかかわらずPWD_IDを送ってきている */
				if (CHK_UNI_OldFCodeBit()) {
					PWDP_BitEnable = 1;
				}
			}
		}
	}
	return(YES);
}


/*************************************************************************
	module		:[Ｆコードポーリング受信時の相手機能力チェック]
	function	:[
		1.
	]
	return		:[OK:1 NG:0]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/02/25]
	author		:[山口哲治]
*************************************************************************/
UBYTE SetPollF_CODE(void)
{
	PartnerP_PWD_Ability = 0;
	PartnerSEP_Ability = 0;
	PartnerSUB_Ability = 0;

	GetMultiFrameLine();
	if (RxStandardFrameByteCount > 8) {
		if (MDM_ModemBuffer[StdFrmPos][7] & EXPAND_FIELD_BIT) {
			if (MDM_ModemBuffer[StdFrmPos][8] & SELECTIVE_POLLING_BIT) {
				PartnerSEP_Ability = 1;
			}
		}
		if (RxStandardFrameByteCount > 9) {
			if (MDM_ModemBuffer[StdFrmPos][8] & EXPAND_FIELD_BIT) {
				if (MDM_ModemBuffer[StdFrmPos][9] & SUBADDRESSING_BIT) {
					PartnerSUB_Ability = 1;
				}
				if (MDM_ModemBuffer[StdFrmPos][9] & PASSWORD_BIT) {
					PartnerP_PWD_Ability = 1;
				}
			}
		}
	}
	if (PartnerSEP_Ability == 0) {
		FaxCompatibleErrorCode = SEP_ABILITY_ERROR;	/** for DEBUG コンパチエラー内容セット */
		return(NG);
	}
	return(YES);
}


/*************************************************************************
	module		:[Ｆコード獲得]
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
	date		:[1996/06/14]
	author		:[村田]
*************************************************************************/
void GetF_CODE_ID(void)
{
	if((PWD_FrmName != NO) && (PasswordFrameID[0] == NULL)) {
		GetPWD_ID();
	}
	if((SEP_FrmName != NO) && (SelectivePollingFrameID[0] == NULL)) {
		GetSEP_ID();
	}
	if((SUB_FrmName != NO) && (SubaddressFrameID[0] == NULL)) {
		GetSUB_ID();
	}
}

/*************************************************************************
	module		:[Ｆコードパスワード獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/31]
	author		:[山口]
*************************************************************************/
void GetPWD_ID(void)
{
	/**	スペースを取り除く処理をしながら大域配列にPWDをセットする	*/
	UBYTE data;
	UBYTE i;
	UBYTE j;
	UBYTE degit_flag;
	UBYTE is_space_check;

	is_space_check = CHK_UNI_Fcode_ID_Space_Check();	/* UNI_SW_B6-5 1999/02/12  By T.Yamaguchi */

	data = 0;
	i = 0;
	j = (UBYTE)(RxPasswordFrameByteCount - 1);
	degit_flag = 0;

	for ( ; ((i < (SYS_ID_MAX - 1) && (j >= START_HDLC_FIF_POS))); j--) {
		data = MDM_ModemBuffer[PWD_FrmPos][j];
		if ((data != ' ') || (is_space_check)) {
			PasswordFrameID[i] = data;
			i++;
		}
	}
	PasswordFrameID[i] = NULL;
}


/*************************************************************************
	module		:[ＦコードＳＥＰ獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/31]
	author		:[山口]
*************************************************************************/
void GetSEP_ID(void)
{
	/**	スペースを取り除く処理をしながら大域配列にSEPをセットする	*/
	UBYTE data;
	UBYTE i;
	UBYTE j;
	UBYTE degit_flag;
	UBYTE is_space_check;

	is_space_check = CHK_UNI_Fcode_ID_Space_Check();	/* UNI_SW_B6-5 1999/02/12  By T.Yamaguchi */

	data = 0;
	i = 0;
	j = (UBYTE)(RxSelectiveFrameByteCount - 1);
	degit_flag = 0;

	for ( ; ((i < (SYS_ID_MAX - 1) && (j >= START_HDLC_FIF_POS))); j--) {
		data = MDM_ModemBuffer[SEP_FrmPos][j];
		if ((data != ' ') || (is_space_check)) {
			SelectivePollingFrameID[i] = data;
			i++;
		}
	}
	SelectivePollingFrameID[i] = NULL;
}


/*************************************************************************
	module		:[ＦコードＳＵＢ獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SHC]
	language	:[SH7043]
	keyword		:[FCM]
	date		:[1997/01/31]
	author		:[山口]
*************************************************************************/
void GetSUB_ID(void)
{
	/**	スペースを取り除く処理をしながら大域配列にSUBをセットする	*/
	UBYTE data;
	UBYTE i;
	UBYTE j;
	UBYTE degit_flag;
	UBYTE is_space_check;

	is_space_check = CHK_UNI_Fcode_ID_Space_Check();	/* UNI_SW_B6-5 1999/02/12  By T.Yamaguchi */

	data = 0;
	i = 0;
	j = (UBYTE)(RxSubaddressFrameByteCount - 1);
	degit_flag = 0;

	for ( ; ((i < (SYS_ID_MAX - 1) && (j >= START_HDLC_FIF_POS))); j--) {
		data = MDM_ModemBuffer[SUB_FrmPos][j];
		if ((data != ' ') || (is_space_check)) {
			SubaddressFrameID[i] = data;
			i++;
		}
	}
	SubaddressFrameID[i] = NULL;
}


/*************************************************************************
	module		:[相手機に送るＦコードＩＤをモデムバッファにセット]
	function	:[
		1.ＦコードＩＤをﾓﾃﾞﾑﾊﾞｯﾌｧに貼り付ける
		2.２０桁未満の場合はスペースで埋める
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[山口]
*************************************************************************/
UBYTE SetF_CODE_ID(UBYTE *Buffer, UBYTE BufPos)
{

	UBYTE  i;
	UBYTE  j;
	UBYTE id_data;

	i = 0;
	j = 0;
	id_data = 0;

	/* 最終桁を探す(NULLまで) */
	while ((*(Buffer + j) != NULL) && (j < SYS_ID_MAX)) {
		j++;
		i++;
	}
	
	/* 何も登録されていない場合はセットせずに抜ける */
	if (i == 0) {
		return(NO);
	}
	
	for(j = 3; (j < (SYS_ID_MAX + 2)) && (i < SYS_ID_MAX ); i--)/**	ＩＤ桁数が２０以下*/ {
		id_data = *(Buffer + i);
		switch (id_data) {
		case NULL:
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '*':
		case '#':
			MDM_ModemBuffer[BufPos][j] = id_data;
			j++;
			break;
		default:
			MDM_ModemBuffer[BufPos][j] = ' ';
			j++;
			break;
		}
	}
	for(;j < SYS_ID_MAX+2; j++) {		/**	ＩＤが２０桁以下	*/
		MDM_ModemBuffer[BufPos][j] = ' ';
	}
	return(YES);

}


/*************************************************************************
	module		:[相手機に送るＩＤの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[山口]
*************************************************************************/
void SetOwnF_CODE_ID(void)
{
	UBYTE	i;

	/* 初期化 */
	for (i = 0; i < SYS_ID_MAX; i++) {
		OwnPasswordFrameID[i] = NULL;
		OwnSelectivePollingFrameID[i] = NULL;
		OwnSubaddressFrameID[i] = NULL;
	}
#if (PRO_F_CODE == ENABLE)
	if (CHK_UNI_Fcode_Space_Tx_Enable()) {	/* スペース、＊、＃を送出可能 */
		/* PWD */
		CMN_FCODE_BCD_ToASC_String(&OwnPasswordFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_PassWordNumber);

		if (CommandFileOptionItem == SYS_SELECT_POLLING_RX) {
			/* SEP */
			CMN_FCODE_BCD_ToASC_String(&OwnSelectivePollingFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_SubAddressNumber);
		}
		else if ((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) || (CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)){
			/* SUB */
			CMN_FCODE_BCD_ToASC_String(&OwnSubaddressFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_SubAddressNumber);
		}
	}
	else {	/* SUB,SEP,PWDに*,#,ｽﾍﾟｰｽを出さない仕様の時 */
		/* PWDは０～９、＊、＃が送出可 */
		CMN_NoSpaceBCD_ToASC_String(&OwnPasswordFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_PassWordNumber);

		if (CommandFileOptionItem == SYS_SELECT_POLLING_RX) {
			/* SEPは０～９ */
			CMN_BCD_Number_ToASC_String(&OwnSelectivePollingFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_SubAddressNumber);
		}
		else if ((CommandFileOptionItem == SYS_SCANNER_SUB_ADDRESS_TX) || (CommandFileOptionItem == SYS_MEMORY_SUB_ADDRESS_TX)){
			/* SUBは０～９ */
			CMN_BCD_Number_ToASC_String(&OwnSubaddressFrameID[0], SYB_FcodeNumberCDataBuffer[CommandFileFcodePosition].SYS_SubAddressNumber);
		}
	}
#endif
}

/*************************************************************************
	module		:[バッファの比較]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[山口]
*************************************************************************/
UBYTE CheckF_CODE_ID(UBYTE *Rx_buf, UBYTE *Comp_buf)
{
	UBYTE	a[SYS_ID_MAX];
	UBYTE	b[SYS_ID_MAX];
	UBYTE	i;
	UBYTE	j;
	UBYTE	valid_number_i;	/* 有効桁数i */
	UBYTE	valid_number_j;	/* 有効桁数j */
	UBYTE	is_pace_check;

	valid_number_i = 0;
	valid_number_j = 0;
	is_pace_check = CHK_UNI_Fcode_ID_Space_Check();	/* UNI_SW_B6-5 */

	for (i = 0; i < SYS_ID_MAX; i++) {
		if (( *(Rx_buf + i) != ' ') /* スペースを取り除く */
		 || (is_pace_check) ){	/* UNI_SW_B6-5 */
			a[valid_number_i] = *(Rx_buf + i);
			if (a[valid_number_i] == NULL) {
				break;
			}
			valid_number_i++;
		}
	}
	
	for (j = 0; j < SYS_ID_MAX; j++) {
		if (( *(Comp_buf + j) != ' ') /* スペースを取り除く */
		 || (is_pace_check) ){	/* UNI_SW_B6-5 */
			b[valid_number_j] = *(Comp_buf + j);
			if (b[valid_number_j] == NULL) {
				break;
			}
			valid_number_j++;
		}
	}

	if (valid_number_i != valid_number_j) {
		return(NG);
	}

	for (i = 0; i < SYS_ID_MAX; i++) {
		if (a[i] == NULL) {
			break;
		}
		if (a[i] != b[i]) {
			return(NG);
		}
	}

	return(OK);
}

/*************************************************************************
	module		:[サブアドレスＢＩＴチェック]
	function	:[
		1.SUB/SEP/PWDのビットとＳＵＢ／ＳＥＰ／ＰＷＤのフレームが正しいか
		  チェックする
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
	date		:[1997/01/10]
	author		:[山口 哲治]
*************************************************************************/
UBYTE CheckRxF_CODE(void)
{
	UBYTE	is_ignore_bit_check;

	PWDT_BitEnable = 0;
	SUB_BitEnable = 0;

	is_ignore_bit_check = CHK_UNI_OldFCodeBit();	/* UNI_SW_B6-0 */
	
	if (RxStandardFrameByteCount > 9) {
		if (MDM_ModemBuffer[StdFrmPos][8] & EXPAND_FIELD_BIT) {
			if (MDM_ModemBuffer[StdFrmPos][9] & PASSWORD_BIT) {
				PWDT_BitEnable = 1;
			}
			if (MDM_ModemBuffer[StdFrmPos][9] & SUBADDRESSING_BIT) {
				SUB_BitEnable = 1;
			}
		}
	}

	if (PWDT_BitEnable == 1) {
		if (PWD_FrmName == NO) {	/* PWDﾋﾞｯﾄが立っているにもかかわらずPWD_IDを送ってこない */
			PWDT_BitEnable = 0;
			return(NO);
		}
	}
	else {
		if (PWD_FrmName != NO) {	/* PWDﾋﾞｯﾄが立っていないにもかかわらずPWD_IDを送ってきている */
			if (is_ignore_bit_check) {
				PWDT_BitEnable = 1;
			}
			else {
				return(NO);
			}
		}
	}

	if (SUB_BitEnable == 1) {
		if (SUB_FrmName == NO) {	/* SUBﾋﾞｯﾄが立っているにもかかわらずSUB_IDを送ってこない */
			SUB_BitEnable = 0;
			return(NO);
		}
	}
	else {
		if (SUB_FrmName != NO) {	/* SUBﾋﾞｯﾄが立っていないにもかかわらずSUB_IDを送ってきている */
			if (is_ignore_bit_check) {
				SUB_BitEnable = 1;
			}
			else {
				return(NO);
			}
		}
	}
	return(YES);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸの確定]
	function	:[
		1.SUBにより指定されたメイルボックスNO.の取り出し
		2.自機に指定されたｻﾌﾞｱﾄﾞﾚｽボックスが存在する
		3.存在しない場合はSUB_ADDRESS_BOX_MAXを返す
	]
	return		:[Ｆコードボックスのポジション]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/10/08]
	author		:[山口 哲治]
*************************************************************************/
UBYTE	FCM_CompFcodeBox(UBYTE * sub_id, UBYTE * pwd_id, UBYTE sub_bit_enable, UBYTE pwd_bit_enable)
/*		FCM_CompFcodeBox(&SubaddressFrameID[0],&PasswordFrameID[0],SUB_BitEnable,PWDT_BitEnable);	*/
{
	UBYTE i;
	UBYTE	ret;

	ret = 0;
		
	/** 取り敢えずＳＵＢを先にチェックして、ＰＷＤが同じものがあればＯＫにする */
	for (i = 0;i < SUB_ADDRESS_BOX_MAX;i++) {
		if (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY) {	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			if (sub_bit_enable == 1) {	/* ＳＵＢを受信 */
				ret = CheckF_CODE_ID(sub_id, &SYB_SubAddressBoxTable[i].SubAddress[0]);
			}
			if (ret == OK) {
				/* ＰＷＤの登録されていない場合は、ＰＷＤをチェックせず受信にいく
				** ように修正する ３Ｌｉｎｅ追加 1998/10/12  By T.Yamaguchi
				*/
				if (SYB_SubAddressBoxTable[i].PassWord[0] == NULL) {
					break;		/* ＳＵＢが一致でＰＷＤ未登録 */
				}
				if (pwd_bit_enable == 1) {	/* ＰＷＤを受信 */
					ret = CheckF_CODE_ID(pwd_id, &SYB_SubAddressBoxTable[i].PassWord[0]);
					if (ret == OK) {
						break;		/* ＳＵＢ、ＰＷＤ共にが一致 */
					}
				}
				else {
					/* ＰＷＤがＢＯＸに登録されている場合にＰＷＤを受信しない場合はエラーになります */
#if 0	/* 下記チェックは10Line上に移動しました 1998/10/12  By T.Yamaguchi */
//					if (SYB_SubAddressBoxTable[i].PassWord[0] == NULL) {
//						break;		/* ＳＵＢが一致でＰＷＤ受信せず */
//					}
#endif
				}
			}
		}
	}

	return (i);

}

/*************************************************************************
	module		:[サブアドレスＢＯＸに受信相手先ＩＤのデータの登録をする]
	function	:[
		1.指定されたボックスの受信相手先ＩＤを登録する
	]
	return		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/10/08]
	author		:[山口 哲治]
*************************************************************************/
void FCM_SetupRemoteID(UBYTE box_position, UBYTE * non_standard_id, UBYTE * standard_id)
{
	UBYTE i;
	
	/*	if ((NonStandardID[0] != NULL) && (OwnMakerCode == MURATA_CODE)) {	/@@	独自（カナ）ＩＤあり、かつＭＭＬ機	*/
	if (*non_standard_id != NULL) {		/**	独自（カナ）ＩＤあり、かつＭＭＬ機	*/
		/**	カナＩＤ登録	*/
		for (i = 0; i < 16; i++) {
			SYB_SubAddressBoxTable[box_position].RemoteName[i] = *(non_standard_id + i);
		}
		SYB_SubAddressBoxTable[box_position].RemoteName[i] = NULL;
	}
	else if (*standard_id != NULL) {	/**	標準ＩＤあり	*/
		/**	標準ＩＤ登録	*/
		for (i = 0; i < 20; i++) {
			SYB_SubAddressBoxTable[box_position].RemoteName[i] = *(standard_id + i);
		}
		SYB_SubAddressBoxTable[box_position].RemoteName[i] = NULL;
	}
	else {
		/**	登録しない	*/
		SYB_SubAddressBoxTable[box_position].RemoteName[0] = NULL;
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸの確定]
	function	:[
		1.SUBにより指定されたメイルボックスNO.の取り出し
		2.自機に指定されたｻﾌﾞｱﾄﾞﾚｽボックスが存在する
		3.存在しない場合はSUB_ADDRESS_BOX_MAXを返す
	]
	return		:[Ｆコードボックスのポジション]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/10/08]
	author		:[山口 哲治]
*************************************************************************/
UBYTE	FCM_RxFcodeStatusSet(struct MEM_IndexData_t *indexP, UBYTE box_position, UWORD rx_total_page)
{
	UBYTE result;
	UBYTE is_rx_print;	/* 同時プリントする */
	UDWORD	store_doc_bit;

	result = 0;
	is_rx_print = 0;
	store_doc_bit = 0;
	indexP->No = 0xFF;
	
	CMN_DisableInterrupt();		/** 割り込み禁止 */

	/************************************************************************
	** メモリ管理用のデータをセットする
	************************************************************************/
	indexP->BoxNumber = (UBYTE)(box_position + 1);

	if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX) {
		indexP->Item = SYS_MEM_SUB_BULLETIN_FILE;
	}
	else if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_SECURE_BOX) {
		indexP->Item = SYS_MEM_SUB_SECURE_FILE;
	}
#if (PRO_FCODE_RELAY == ENABLE) /* Add By H.Hirao 1998/08/21 */
	else if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_RELAY_BOX) {
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (SetUpFcodeRelayBroadCastRx(indexP, box_position, rx_total_page));
	}
#endif
	if (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_RECEIVE) {	/*	受信不許可	*/
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
		return(SUB_PROHIBIT_RX_ERROR);	/*	受信禁止設定のＢＯＸに受信	*/
	}

	switch (SYB_SubAddressBoxTable[box_position].DataStatus) {		/**	ボックスの原稿蓄積ステータス	*/
	case SYS_SUB_ADDRESS_BOX_RECEIVE:	/**	ボックス受信済み	*/
	case SYS_SUB_ADDRESS_BOX_STORED:	/**	ボックス蓄積済み	*/
		/**	ｻﾌﾞｱﾄﾞﾚｽＢＯＸ受信中	*/
		/* 受信中のＢＯＸ原稿の消去を防止するため  */
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING;/* バックアップのため */
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
		if ((SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX)
		 && (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_DOC_ADD) ) {	/* 上書き設定 */
			/* 上書きの場合は、原稿消去してから蓄積する仕様とする メモリが一杯になり受信できなくなるため */
			MEM_ClearDoc(indexP->Item, MEM_ALL_NO, indexP->BoxNumber);
			SYB_SubAddressBoxTable[box_position].StoredDocBit = 0;	/* 受信蓄積ファイル番号リセット */
			indexP->No = 1;	/* 蓄積番号 */
		}
		else {	/* 原稿追加 */
			/**	メモリ受信用ページカウンタにＢＯＸ受信済みページ数セット	*/
			store_doc_bit = (UDWORD)(SYB_SubAddressBoxTable[box_position].StoredDocBit);
			indexP->No = SubaddressBoxDetectEmptyNo(store_doc_bit);
			if (indexP->No == FULL_STORED) {	/* 原稿が３０件蓄積されている */
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;/* バックアップのため追加 17.Aug'94 Y.Suzuki */
				return(SUBADDRESS_BOX_INDEX_MAX_ERROR);	/*	受信禁止設定のＢＯＸに受信	*/
			}
		}
		/* 受信中の蓄積番号を記憶 */
		SYB_SubAddressBoxTable[box_position].RxStoringNo = (UBYTE)indexP->No;
		indexP->Page = rx_total_page + 1;
		break;
	case SYS_SUB_ADDRESS_BOX_PRINTING:	/** 原稿プリント中 */
		if ((SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX)
		 && (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_DOC_ADD) ) {	/* 上書き設定 */
			/* 上書きの場合は、原稿消去してから蓄積するためプリント中は受信しない */
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			return(SUBADDRESS_BOX_PRINTING_ERROR);	/*	受信禁止設定のＢＯＸに受信	*/
		}
		else {	/* 原稿追加 */
			SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_PRT_RX;	/* プリント中の受信 */
			/**	メモリ受信用ページカウンタにＢＯＸ受信済みページ数セット	*/
			store_doc_bit = (UDWORD)(SYB_SubAddressBoxTable[box_position].StoredDocBit);
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
			indexP->No = SubaddressBoxDetectEmptyNo(store_doc_bit);
			if (indexP->No == FULL_STORED) {	/* 原稿が３０件蓄積されている */
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
				return(SUBADDRESS_BOX_INDEX_MAX_ERROR);	/*	受信禁止設定のＢＯＸに受信	*/
			}
		}
		/* 受信中の蓄積番号を記憶 */
		SYB_SubAddressBoxTable[box_position].RxStoringNo = (UBYTE)indexP->No;
		indexP->Page = rx_total_page + 1;
		break;
	case SYS_SUB_ADDRESS_BOX_STORING:	/** 蓄積中原稿あり */
	case SYS_SUB_ADDRESS_BOX_DELETING:  /** 原稿消去中 */
		/* 蓄積中の場合は受信できない */
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
		return(SUBADDRESS_BOX_STORING);	/*	蓄積中のため受信拒否	*/
	case SYS_SUB_ADDRESS_BOX_NO_SET:	/**	 未蓄積 */
		/**	ｻﾌﾞｱﾄﾞﾚｽＢＯＸ受信中	*/
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING;/* バックアップのため */
		/* 受信中のＢＯＸ原稿の消去を防止するため ↑ */
		indexP->No = 1;	/* 蓄積番号 */
		/* 受信中の蓄積番号を記憶 */
		SYB_SubAddressBoxTable[box_position].RxStoringNo = 1;
		/**	メモリ受信用ページカウンタに（受信ページ数＋１）をセット	*/
		indexP->Page = rx_total_page + 1;
		break;
	case SYS_SUB_ADDRESS_BOX_RECEIVING:	/**	ボックス受信中	*/
	case SYS_SUB_ADDRESS_BOX_TXING:		/**	ボックス送信中	*/
	case SYS_SUB_ADDRESS_BOX_PRT_RX:	/* プリント中且つ 受信中 */
	case SYS_SUB_ADDRESS_BOX_PRT_TX:    /* プリント中且つ 送信中 */
	case SYS_SUB_ADDRESS_BOX_STR_TX:    /* 蓄積中且つ 送信中 */
	default:/**	ステータスエラー	*/
		/**	受信しない	*/
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/22  By T.Yamaguchi */
		return(SUB_RECEIVING_BOX_ERROR);	/*	受信中のＢＯＸに受信	*/
	}

	CMN_EnableInterrupt();		/** 割り込み許可 */

	return(0);	/* 受信可能 */
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ受信準備]
	function	:[
		1.サブアドレス受信可能なら受信ファイルのセットアップを行う
		2.SUBにより指定されたメイルボックスNO.の取り出し
		3.自機に指定されたｻﾌﾞｱﾄﾞﾚｽボックスが存在する
		4.メイルボックスの受信状態
		5.メイルボックス内相手先ＩＤ登録（同じメイルボックスに異なるＩＤの
		. ＦＡＸから受信すると最後に受信したＩＤのみ有効）
	]
	return		:[ＯＫ--YES／ＮＧ--NO]
	common		:[50件２０桁登録時、34ms掛かっている
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[山口 哲治]
*************************************************************************/
UBYTE SetUpSubaddressBoxRx(void)	/*	モデムバッファのポインター	*/
{
	UBYTE	box_position;
	struct MEM_IndexData_t fcode;
	UBYTE	result;
	
	result = 0;
	
	/**	指定サブアドレスボックスのチェック	*/
	box_position = FCM_CompFcodeBox(&SubaddressFrameID[0],&PasswordFrameID[0], SUB_BitEnable, PWDT_BitEnable);

	if (box_position == SUB_ADDRESS_BOX_MAX ) {	/* 一致するＢＯＸがなかった */
		FaxCompatibleErrorCode = NOT_SUB_ADDRESS_BOX_ERROR;
		return(NO);
	}

	if (CMN_CheckMemoryReceiveEnable() == FALSE) {
		FaxCompatibleErrorCode = SUBSTITUTE_PRINTER_ERROR;	/*	代行受信バッファフルエラー	*/
		return(NO);	/**	空きがなければ、受信しない	*/
	}

	/* ここの部分を２回線対応のために割り込み禁止で関数化する */
	result = FCM_RxFcodeStatusSet(&fcode, box_position, SYS_RxTotalPage);

	if (result != 0) {
		FaxCompatibleErrorCode = result;
		return(NO);		/* エラー */
	}

	SYS_RxMemoryFileNo = fcode.No;	/* 蓄積番号 */
	SYS_RxMemoryFilePage = fcode.Page;
	SYS_RxMemoryFileItem = fcode.Item;
	SYS_RxMemoryFileBoxNumber = fcode.BoxNumber;
	
	/* 掲示板受信時に同時プリント設定の場合プリント用のインデックスをセットする */
	if ((SYS_RxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)
	  &&(SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_PRINT)) {
		SYS_RxPrintFileItem = SYS_MEM_RX_FILE;
		SYS_RxPrintFileNo = SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage =  SYS_RxTotalPage + 1;
		SYS_RxPrintFileBoxNumber = MEM_IGNORE_BOX_NUMBER;
	}
	
	/* サブアドレスＢＯＸに受信相手先ＩＤのデータの登録をする */
	FCM_SetupRemoteID(box_position, &NonStandardID[0], &StandardID[0]);

	return(YES);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸﾎﾟｰﾘﾝｸﾞ送信ファイル準備]
	function	:[
		1.サブアドレスポーリング送信可能なら送信ファイルのセットアップ
		2.メイルボックスの状態設定
	]
	return		:[]
	]
	condition	:[22us]
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/31]
	author		:[山口 哲治]
*************************************************************************/
UBYTE	FCM_TxFcodeStatusSet(UBYTE box_position)
{
	CMN_DisableInterrupt();		/** 割り込み禁止 */

	switch (SYB_SubAddressBoxTable[box_position].DataStatus) {		/**	ボックスの原稿蓄積ステータス	*/
	case SUB_ADDRESS_BOX_EMPTY:
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/26  By T.Yamaguchi */
		return(NO_SUB_POLLING_DOC_ERROR);	/**	蓄積原稿が無い	*/
	case SYS_SUB_ADDRESS_BOX_PRINTING:
	case SYS_SUB_ADDRESS_BOX_STORING:
		/* プリント中または蓄積中で送信後の原稿消去設定の場合は送信しない */
		if (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_ERASE) {
			CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/26  By T.Yamaguchi */
			return(NO_SUB_POLLING_DOC_ERROR);
		}
		break;
	case SYS_SUB_ADDRESS_BOX_DELETING:  /** 原稿消去中 */
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/26  By T.Yamaguchi */
		return(SUBADDRESS_BOX_STORING);	/*	蓄積中のため受信拒否	*/
	case SYS_SUB_ADDRESS_BOX_RECEIVING:	/**	ボックス受信中	*/
	case SYS_SUB_ADDRESS_BOX_TXING:		/**	ボックス送信中	*/
	case SYS_SUB_ADDRESS_BOX_PRT_RX:	/* プリント中且つ 受信中 */
	case SYS_SUB_ADDRESS_BOX_PRT_TX:    /* プリント中且つ 送信中 */
	case SYS_SUB_ADDRESS_BOX_STR_TX:    /* 蓄積中且つ 送信中 */
		CMN_EnableInterrupt();		/** 割り込み許可 */	/* 1998/01/26  By T.Yamaguchi */
		return(SUB_RECEIVING_BOX_ERROR);	/*	受信中のＢＯＸに受信	*/
	default:	/* SYS_SUB_ADDRESS_BOX_STORED, SYS_SUB_ADDRESS_BOX_RECEIVE */
		break;
	}

	/* データステータスを送信中にセットする */
	if (SYB_SubAddressBoxTable[box_position].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING) {
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_PRT_TX;
	}
	else if (SYB_SubAddressBoxTable[box_position].DataStatus == SYS_SUB_ADDRESS_BOX_STORING) {
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STR_TX;
	}
	else {
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;	/* 送信中をセット */
	}

	CMN_EnableInterrupt();		/** 割り込み許可 */

	return(0);	/* 送信準備ＯＫ */
}

/*************************************************************************
	module		:[Ｆコードﾎﾟｰﾘﾝｸﾞ送信ファイル準備]
	function	:[
		1.サブアドレスポーリング送信可能なら送信ファイルのセットアップ
		2.メイルボックスの状態設定
	]
	return		:[]
	]
	condition	:[]
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/01/31]
	author		:[山口 哲治]
*************************************************************************/
UBYTE	FCM_TxFcodeFileSet(UBYTE tx_memory_file_item, UBYTE box_position, UWORD * tx_memory_file_no, UWORD * polling_tx_file_page)
{
	UDWORD	stored_no_bit;
	UBYTE	box_number;
	UBYTE	index_no;
	UBYTE	buf_no;

	box_number = box_position + 1;
	stored_no_bit = 0;
	
	stored_no_bit = (UDWORD)(SYB_SubAddressBoxTable[box_position].StoredDocBit);

	if (stored_no_bit == 0) {	/* 蓄積中のファイルしかない */
		return(NO_SUB_POLLING_DOC_ERROR);
	}
	
	for(index_no = 0,buf_no = 0; index_no < SYS_SUBADDRESS_BOX_INDEX_MAX; index_no++) {
		if ((stored_no_bit >> index_no) & 0x0001) {
			*(tx_memory_file_no + buf_no) = (UWORD)(index_no + 1);
			*(polling_tx_file_page + buf_no) = MEM_CountTotalEachDocPage(tx_memory_file_item, (UWORD)(index_no + 1), box_number);
			buf_no++;
		}
	}

	/**	送信メモリファイルの次のバッファに0xFFFFを入れる	*/
	*(tx_memory_file_no + buf_no) = 0xFFFF;
	*(polling_tx_file_page + buf_no) = 0xFFFF;

	return(0);	/* 送信原稿準備ＯＫ */

}

/*************************************************************************
	module		:[サブアドレスＢＯＸﾎﾟｰﾘﾝｸﾞ送信準備]
	function	:[
		1.サブアドレスポーリング送信可能なら送信ファイルのセットアップを行う
		2.SUBにより指定されたメイルボックスNO.の取り出し
		3.自機に指定されたｻﾌﾞｱﾄﾞﾚｽボックスが存在する
		4.メイルボックスの受信状態
		5.メイルボックス内相手先ＩＤ登録（同じメイルボックスに異なるＩＤの
		. ＦＡＸから受信すると最後に受信したＩＤのみ有効）
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
	date		:[1997/01/31]
	author		:[山口 哲治]
*************************************************************************/
UBYTE SetUpSubaddressBoxPollingTx(void)
{
	UBYTE	box_position;
	UBYTE	result;
	
	result = 0;
	TxMemoryFileItem = SYS_MEM_SUB_BULLETIN_FILE;	/* ジャーナル用にセットしておく 1997/08/30  By T.Yamaguchi */

	/**	指定サブアドレスボックスのチェック	*/
	/** 取り敢えずＳＥＰを先にチェックして、ＰＷＤが同じものがあればＯＫにする */
	box_position = FCM_CompFcodeBox(&SelectivePollingFrameID[0], &PasswordFrameID[0], SEP_BitEnable, PWDP_BitEnable);

	/* TxMemoryFileBoxNumber = (UBYTE)(box_position + 1); */

	if (box_position == SUB_ADDRESS_BOX_MAX ) {	/* 一致するＢＯＸがなかった */
		FaxCompatibleErrorCode = NOT_SUB_ADDRESS_BOX_ERROR;
		return(NO);
	}
	
	if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_SECURE_BOX) {	/* 親展ＢＯＸなら */
		if (!CHK_UNI_FcodeSecureDocPollTx()) {	/* サブアドレス親展ポーリングしない */
			FaxCompatibleErrorCode = SUB_POLLING_SECURE_BOX_ERROR;
			return(NO);		/**	掲示板でない	*/
		}
		TxMemoryFileItem = SYS_MEM_SUB_SECURE_FILE;
	}
	else if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX) {
		TxMemoryFileItem = SYS_MEM_SUB_BULLETIN_FILE;
	}
	
	/* ここの部分を２回線対応のために割り込み禁止で関数化する */
	/* エラーの場合は、エラーコードが返ってくる */
	result = FCM_TxFcodeStatusSet(box_position);
	
	if (result != 0) {
		FaxCompatibleErrorCode = result;
		return(NO);
	}

	TxMemoryFileBoxNumber = (UBYTE)(box_position + 1);

	result = FCM_TxFcodeFileSet(TxMemoryFileItem, box_position, &TxMemoryFileNo[0], &PollingTxFilePage[0]);

	if (result != 0) {
		FaxCompatibleErrorCode = result;
		return(NO);
	}
	
	return(YES);
}

/*************************************************************************
	module		:[サブアドレスボックス有無チェック]
	function	:[
		サブアドレスボックスのステータスをチェックする
	]
	return		:[サブアドレスボックスあり:SUB,PWD登録(3) SUBのみ(1)  なし:NO]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/02/24]
	author		:[山口 哲治]
*************************************************************************/
UBYTE CheckSubaddressBox(void)
{
	UBYTE i;
	UBYTE ret;

	ret = 0;

	for (i = 0;i < SUB_ADDRESS_BOX_MAX;i++) {
		if (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY) {	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			if (SYB_SubAddressBoxTable[i].SubAddress[0]) {
				ret |= SUB_SET;
				if (SYB_SubAddressBoxTable[i].PassWord[0]){
					ret |= PWD_SET;
					break;
				}
			}
		}
	}
	return(ret);
}

/*************************************************************************
	module		:[サブアドレスボックス空蓄積Ｎｏ．を獲得]
	function	:[
		サブアドレスボックスの蓄積されているステータスをチェックする
	]
	return		:[]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/02/24]
	author		:[山口 哲治]
*************************************************************************/
UBYTE SubaddressBoxDetectEmptyNo(UDWORD stored_doc_bit)
{
	UBYTE i;

	/* 原稿が全く蓄積されていない	*/
	if(stored_doc_bit == 0) {
		return(1);	/* 原稿No.１を返す */
	}
	for (i = 0; i < SYS_SUBADDRESS_BOX_INDEX_MAX; i++) {
		if ((stored_doc_bit >> i) & 0x0001) {
			/* そのＮｏ．に蓄積原稿がある */
		}
		else {	/* 空Ｎｏ．発見 */
			return((UBYTE)(i + 1));
		}
	}
	return(FULL_STORED);
}
/*#endif*/

/*************************************************************************
これ以下の３関数は、Ｆコード中継配信用に追加分 By Hirao 1998/08/21
*************************************************************************/
#if (PRO_FCODE_RELAY == ENABLE)
/*************************************************************************
	module		:[Ｆコード中継配信受信準備]
	function	:[
	]
	return		:[RELAYED_RX_COMMAND_ERROR：中継同報要求時、展開可能コマンドファイルなし
				  SUBSTITUTE_PRINTER_ERROR：代行受信バッファフルエラー
				  0                       ：正常終了]
	common		:[]
	condition	:[]
	comment		:[FCM_RxFcodeStatusSet()からコールされる]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1998/08/21]
	author		:[平尾 英典]
*************************************************************************/
UBYTE SetUpFcodeRelayBroadCastRx(struct MEM_IndexData_t *indexP, UBYTE box_position, UWORD rx_total_page)
{
	struct	SYS_CommandData_t	 *comp;
	BYTE	command_no, i;

#if (PRO_FCODE_DELAYED_RELAY == ENABLE) /** Ｆコード時刻指定中継配信機能 By S.Wang 98/10/30 */

	CMN_DisableInterrupt();	/* 割り込み禁止 By S.Wang 98/10/30 */
	command_no = SYB_SubAddressBoxTable[box_position].CommandNo;
	
	switch (SYB_CommandFile[command_no].Status) {
	case SYS_CMD_WAITING:
		/**********************************************************
		* サブアドレスＢＯＸに中継配信予約あれば、送信コマンド
		* 番号はサブアドレスＢＯＸの中継配信コマンド番号にセット
		**********************************************************/
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
		SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
 #if (PRO_COMMANDFILE_SRAM == DISABLE)
		SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
 #endif
		RelayedCommandNo = command_no;
		if (CMN_CheckMemoryReceiveEnable() == TRUE) {
			/*----------------------------------------*/
			/* 配信局でも同報原稿をプリントするか否か */
			/*----------------------------------------*/
			if (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_PRINT) {
				SYS_RxPrintFileItem			= SYS_MEM_RX_FILE;
				SYS_RxPrintFileNo			= SYB_MemoryRxPrintWritePoint;
				SYS_RxPrintFilePage			= rx_total_page + 1;
			}
			else {	/* 受信原稿が中継機にプリントされない時 1998/09/30 By M.Kuwahara */
				SYB_CommandFile[RelayedCommandNo].Ability |= SYS_WARP_PRINT;
			}
		}
		else {
			CMN_EnableInterrupt();	/** 割り込み許可 */
			return(SUBSTITUTE_PRINTER_ERROR);
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
		break;
		
	case SYS_CMD_EMPTY:
	case SYS_CMD_ERASED:
	case SYS_CMD_POWER_OFF:
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
			return (RELAYED_RX_COMMAND_ERROR);
		}
		/*----------------------------------------*/
		/* 配信局でも同報原稿をプリントするか否か */
		/*----------------------------------------*/
		if (CMN_CheckMemoryReceiveEnable() == TRUE) {
			if (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_PRINT) {
				SYS_RxPrintFileItem			= SYS_MEM_RX_FILE;
				SYS_RxPrintFileNo			= SYB_MemoryRxPrintWritePoint;
				SYS_RxPrintFilePage			= rx_total_page + 1;
			}
			else {	/* 受信原稿が中継機にプリントされない時 1998/09/30 By M.Kuwahara */
				SYB_CommandFile[RelayedCommandNo].Ability |= SYS_WARP_PRINT;
			}
		}
		else {
			CMN_EnableInterrupt();	/** 割り込み許可 */
			return(SUBSTITUTE_PRINTER_ERROR);
		}
		/* サブアドレスＢＯＸに中継配信コマンド番号セット */
		SYB_SubAddressBoxTable[box_position].CommandNo = RelayedCommandNo;
		/* このコマンド番号に中継配信まだ有りません */
		SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
		/*------------------------------*/
		/* コマンドファイルのメンバ登録 */
		/*------------------------------*/
		ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** ダイアルデータ初期化 */
		for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
			comp -> DialNumber.Onetouch[i] = SYB_SubAddressBoxTable[box_position].Onetouch[i];
		}
		for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
			comp -> DialNumber.Speed[i] = SYB_SubAddressBoxTable[box_position].Speed[i];
		}
		comp -> DialNumber.Group = SYB_SubAddressBoxTable[box_position].Group;
	
		comp -> Option.Item = SYS_RELAYED_TX;	/** TBD 中継配信のアイテム */
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
		break;
	case SYS_CMD_SETTING: /* 中継配信コマンドはセット中 */
	case SYS_CMD_EXECUTE: /* 中継配信コマンド送信実行中 */
	default: /**	ステータスエラー	*/
		/**	受信しない	*/
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return (SUB_RECEIVING_BOX_ERROR);
	}
 #if (PRO_FCODE_RELAYED_REPORT == ENABLE)
 	if (CHK_RelayedRelayTxON()) {
		if(SetTransmitStationID() == NO) {	/** TBD コマンドファイルの中継局IDバッファに標準IDをセット */
			return (RELAYED_RX_TSI_ERROR); /** TSI 不良エラー */
		}
	}
 #endif
 #if (0)
	SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING; /** TBD 受信中原稿有り */
 #endif
	CMN_EnableInterrupt();	/** 割り込み許可 */

	/*--------------------------*/
	/* インデックスのメンバ登録 */
	/*--------------------------*/
	indexP -> Item		= SYS_MEM_TX_FILE;
	indexP -> No		= (UWORD)RelayedCommandNo;
	indexP -> Page		= (UWORD)rx_total_page + 1;

	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = (UBYTE)box_position + 1;

	return (0);

#else	/* PRO_FCODE_DELAYED_RELAY */

	/*------------------------------*/
	/* コマンドファイルの空きを検索 */
	/*------------------------------*/
	CMN_DisableInterrupt();	/* 割り込み禁止 */
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
		return (RELAYED_RX_COMMAND_ERROR);
	}
	/*----------------------------------------*/
	/* 配信局でも同報原稿をプリントするか否か */
	/*----------------------------------------*/
	if (CMN_CheckMemoryReceiveEnable() == TRUE) {
		if (SYB_SubAddressBoxTable[box_position].Option & SUB_ADDRESS_OPTION_PRINT) {
			SYS_RxPrintFileItem			= SYS_MEM_RX_FILE;
			SYS_RxPrintFileNo			= SYB_MemoryRxPrintWritePoint;
			SYS_RxPrintFilePage			= rx_total_page + 1;
		}
		else {	/* 受信原稿が中継機にプリントされない時 1998/09/30 By M.Kuwahara */
			SYB_CommandFile[RelayedCommandNo].Ability |= SYS_WARP_PRINT;
		}
	}
	else {
		CMN_EnableInterrupt();	/** 割り込み許可 */
		return(SUBSTITUTE_PRINTER_ERROR);
	}
	/*------------------------------*/
	/* コマンドファイルのメンバ登録 */
	/*------------------------------*/
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** ダイアルデータ初期化 */
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		comp -> DialNumber.Onetouch[i] = SYB_SubAddressBoxTable[box_position].Onetouch[i];
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		comp -> DialNumber.Speed[i] = SYB_SubAddressBoxTable[box_position].Speed[i];
	}
	comp -> DialNumber.Group = SYB_SubAddressBoxTable[box_position].Group;
	
	comp -> Option.Item = SYS_RELAYED_TX;	/** TBD 中継配信のアイテム */
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
#if (PRO_FCODE_RELAYED_REPORT == ENABLE)
	if (CHK_RelayedRelayTxON()) {
		if(SetTransmitStationID() == NO) {	/** TBD コマンドファイルの中継局IDバッファに標準IDをセット */
			return (RELAYED_RX_TSI_ERROR); /** TSI 不良エラー */
		}
	}
#endif
#if (0)
	SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVING; /** TBD 受信中原稿有り */
#endif
	CMN_EnableInterrupt();	/** 割り込み許可 */

	/*--------------------------*/
	/* インデックスのメンバ登録 */
	/*--------------------------*/
	indexP -> Item		= SYS_MEM_TX_FILE;
	indexP -> No		= (UWORD)RelayedCommandNo;
	indexP -> Page		= (UWORD)rx_total_page + 1;

	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = (UBYTE)box_position + 1;

	return (0);

#endif /* PRO_FCODE_DELAYED_RELAY */

}


/*************************************************************************
	module		:[配信時に配信局の発信元を無しにするか否か]
	function	:[
		1.
	]
	return		:[0	   :無し
				  0以外:有り
	]
	common		:[]
	condition	:[]
	comment		:[CDC_MTxCodeConvertPageTask()からコールされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/07/15]
	author		:[平尾 英典]
*************************************************************************/
UBYTE FCM_FcodeRelayTxTTI_Available(void)
{
	UBYTE	box_no;	/** 中継指示されたＦコードボックス */
	
	box_no = SYB_FcodeBoxNoByRelayedTxComNo[SYS_CurrentExecutingCommand->Number.Command];
	if ((!box_no)
	 || (CommandFileOptionItem != SYS_RELAYED_TX)) {
		return (FCM_PtnrChkTTI_TxAvailable());
	}
	else {
		if (SYB_SubAddressBoxTable[box_no - 1].Status == SUB_ADDRESS_RELAY_BOX) {
			return (SYB_SubAddressBoxTable[box_no - 1].Option & SUB_ADDRESS_OPTION_TTI_AVAIL);
		}
		else {
			return (FCM_PtnrChkTTI_TxAvailable());
		}
	}
}


/*************************************************************************
	module		:[配信時に配信局の発信元を上書きにするか否か]
	function	:[
		1.
	]
	return		:[0	   :外付け
				  0以外:上書き
	]
	common		:[]
	condition	:[]
	comment		:[CDC_MTxCodeConvertPageTask()からコールされる
				  中継配信時は、ユニークスイッチの設定が無効になる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/07/15]
	author		:[平尾 英典]
*************************************************************************/
UBYTE FCM_FcodeRelayTxTTI_Inside(void)
{
	UBYTE	box_no;	/** 中継指示されたＦコードボックス */
	
	box_no = SYB_FcodeBoxNoByRelayedTxComNo[SYS_CurrentExecutingCommand->Number.Command];
	if ((!box_no)
	 || (CommandFileOptionItem != SYS_RELAYED_TX)) {
		return (CHK_UNI_TTI_Inside());
	}
	else {
		if (SYB_SubAddressBoxTable[box_no - 1].Status == SUB_ADDRESS_RELAY_BOX) {
			return (SYB_SubAddressBoxTable[box_no - 1].Option & SUB_ADDRESS_OPTION_TTI_INSIDE);
		}
		else {
			return (CHK_UNI_TTI_Inside());
		}
	}
}
#endif /* (PRO_FCODE_RELAY == ENABLE) */
