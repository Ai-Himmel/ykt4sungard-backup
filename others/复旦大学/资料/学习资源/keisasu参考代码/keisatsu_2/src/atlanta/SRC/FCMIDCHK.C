/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMIDCHK.C												 */
/*	モジュール	 :															 */
/*				 : RxCheckOwnDialAndID()									 */
/*				 : CheckASCII_CodeAndStandardID()							 */
/*				 : CheckASCII_DialAndStandardID()							 */
/*				 : CheckBCD_DialAndStandardID()								 */
/*				 : CheckTransmitterID_Buf()									 */
/*				 : CheckSubscriberID_Buf()									 */
/*				 : SetTransmitterID_Frame()									 */
/*				 : SetSubscriberID_Frame()									 */
/*				 : GetOwnMakerPartnerID()									 */
/*				 : GetPartnerID()											 */
/*				 : SetTransmitStationID()									 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＩＤチェック												 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSMAX.H"
#include "\src\atlanta\define\SYSONET.H"
#include "\src\atlanta\define\SYSSPEED.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\cmn_pro.h" /* Added by H.Kubo 1998/01/08 */
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\FCM_DEF.H"
#if(PRO_RELAYED_REPORT == ENABLE)
 #include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#endif
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/11/18 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/18 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if(PRO_TSI_RELAY_COM == ENABLE)/* 15.Feb'95 Y.Suzuki */
 #include "\src\atlanta\ext_v\ROM_TBL.H"
#endif

#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\status.h"	/* 1997/05/12  By T.Yamaguchi */

#if 0	/* 時間がかかりＶ２９のときＴＣＦを１回取りこぼすため変更します 1997/10/22  By T.Yamaguchi */
///*************************************************************************
//	module		:[ジャンクメイル防止用ＩＤ照合]
//	function	:[
//		ワンタッチ、短縮に登録されたＩＤと相手先ＩＤの照合を行う
//	]
//	return		:[照合ＯＫ:YES	照合ＮＧ:NO]
//	common		:[
//					SYB_OnetouchDial.:Status						:ワンタッチダイヤルの登録状態
//					SYB_OnetouchDial.DialData.Onetouch.:dial		:ワンタッチダイヤルの相手先ＮＯ．
//					SYB_SpeedDial.:Dial								:短縮ダイヤルの相手先ＮＯ．
//				]
//	condition	:[]
//	comment		:[]
//	machine		:[V53,H8/300]
//	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
//	keyword		:[FCM]
//	date		:[1993/12/13]
//	author		:[鈴木 郁二]
//*************************************************************************/
//UBYTE RxCheckOwnDialAndID(UBYTE *id_buf)
//{
//	WORD i;
//
//	/* 3Line add 1997/05/12  By T.Yamaguchi */
//	if (CHK_BlockJunkFaxMode() == (UBYTE)BLOCK_JUNK_FAX_MODE2) {
//		return(YES);
//	}
//	
//	for (i = 0; i < SYS_ONETOUCH_MAX; i++)	{/**	ワンタッチダイヤルの個数回	*/
//		if((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) {		/* '96.02.22 BY T.Y */
//			if (CheckBCD_DialAndStandardID(SYB_OnetouchDial[i].Dial, id_buf) == YES)  {	/**	ダイヤル登録あり && 照合OK	*/
//				/**	リターンYES	*/
//				return(YES);
//			}
//		}
//	}
//	for (i = 0 ; i < SYS_SPEED_DIAL_MAX; i++)  {	/**	短縮ダイヤルの個数回	*/
//		if ((SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0) {
//			if (CheckBCD_DialAndStandardID(SYB_SpeedDial[i].Dial, id_buf) == YES) {	/**	ダイヤル登録あり 照合OK	*/
//				/**	リターンYES	*/
//				return(YES);
//			}
//		}
//	}
//	/**	リターンNO	*/
//	return(NO);
//}
#endif

/*************************************************************************
	module		:[相手先電話ＮＯ.(ASCII)と標準IDの下４桁を照合]
	function	:[
		1.
	]
	return		:[
			相手局のIDFrameがない､オールスペース NG		:NO(0)
			4桁照合OK									:YES(1)
			どちらかが4桁未満でその少ない方の桁照合OK	:(2)
	]
	common		:[
						StandardID	:標準ＩＤ（発信元）を格納するバッファ
				StandardIDを引数option_idで見る様に変更	1997/10/20  By T.Yamaguchi
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/10/22]
	author		:[山口哲治]
*************************************************************************/
UBYTE RxCheckOwnDialAndID(UBYTE *id_buf)
{
	UBYTE i;
	UWORD std_id;
	UBYTE bcd_id[11];
	
	/* 3Line add 1997/05/12  By T.Yamaguchi */
	if (CHK_BlockJunkFaxMode() == (UBYTE)BLOCK_JUNK_FAX_MODE2) {
		return(YES);
	}
	for (i = 0;i < 11; i++) {	/* 0xFFで初期化 */
		bcd_id[i] = 0xFF;
	}

	CMN_ASC_ToBCD_StringNumber(&bcd_id[0], id_buf, 20);
	std_id = PickOutLastFourFigure(&bcd_id[0], 20);	/* 下４桁を抜き出す */
	
	if (std_id == 0xFFFF) {	/* TSIが４桁未満であったら受信しない 1997/11/28 T.Yamaguchi */
		return(NO);
	}

	for (i = 0; i < SYS_ONETOUCH_MAX; i++)	{/**	ワンタッチダイヤルの個数回	*/
		if (SYB_OnetouchJunkDial[i] == std_id) {
			return(YES);
		}
	}
	for (i = 0 ; i < SYS_SPEED_DIAL_MAX; i++)  {	/**	短縮ダイヤルの個数回	*/
		if (SYB_SpeedJunkDial[i] == std_id) {
			return(YES);
		}
	}
	return(NO);
}

/*************************************************************************
	module		:[ジャンクメイル防止用ＩＤ照合]
	function	:[
		ジャンクダイヤルＩＤと相手先ＩＤの照合を行う
	]
	return		:[照合ＯＫ:YES	照合ＮＧ:NO]
	common		:[
					SYB_JunkMailProtectDialBuffer
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/05/12]
	author		:[山口哲治]
*************************************************************************/
UBYTE RxCheckJunkDialAndID(UBYTE *id_buf)
{
	UWORD i;
	UWORD std_id;
	UWORD junk_id;
	UBYTE bcd_id[11];

	if (CHK_BlockJunkFaxMode() == (UBYTE)BLOCK_JUNK_FAX_MODE1) {
		return(YES);
	}

	for (i = 0;i < 11; i++) {	/* 0xFFで初期化 */
		bcd_id[i] = 0xFF;
	}

	/* 標準ＩＤのをＢＣＤのバッファに変換する */	
	CMN_ASC_ToBCD_StringNumber(&bcd_id[0], id_buf, 20);
	/* 標準ＩＤの下４桁をUWORD型の変数にセットする */	
	std_id = PickOutLastFourFigure(&bcd_id[0], 20);	/* 下４桁を抜き出す */

	if (std_id == 0xFFFF) {	/* TSIが４桁未満なら受信する */
		return(YES);
	}

	for (i = 0; i < SYS_JUNK_DIAL_MAX; i++)	{/**	ジャンクダイヤルの個数回	*/
		if((SYB_JunkMailProtectDialBuffer[i][0] & 0xF0) != 0xF0) {		/* '96.02.22 BY T.Y */
			/* ８桁の中から下４桁を抜き出す */
			junk_id = PickOutLastFourFigure(&SYB_JunkMailProtectDialBuffer[i][0], 8);
			if (junk_id != 0xFFFF) {	/* 4桁以上有効数字があるなら */
				if (junk_id == std_id)  { /**	ダイヤル登録あり && 照合OK	*/
					/**	リターンNO	*/
					return(NO);		/* 受信しない */
				}
			}
		}
	}
	/**	リターンNO	*/
	return(YES);
}


/*************************************************************************
	module		:[パスコードと標準IDの下４桁を照合]
	function	:[
		1.ＦＸポーリング送信用
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1994/08/12]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckASCII_CodeAndStandardID(UBYTE *ASCII_Code)
{
	BYTE i;
	BYTE j;
	UBYTE k;

	/**	標準ＩＤの最後の桁数(最大21桁)をローカル変数にセット	*/
	for (j = 0; j < SYS_ID_MAX; j++)  {
		if (StandardID[j] == 0x00)	{
			if (j == 0) {/**	標準ＩＤが登録されていない	*/
				return (NO);
			}
			break;
		}
	}
	i = 4;/* パスコード４桁 */
	for (k = 0; k < 4; k++)	 {/**	終わりの４桁が一致するか	*/
		do	{
			--i;
			if (i < 0)	{
				return(2);
			}
		}  while ((ASCII_Code[i] < '0') ||	/* !isdigit(ASCII_Dial[i]) */
				  (ASCII_Code[i] > '9'));
		do	{
			--j;
			if (j < 0)	{
				return(2);
			}
		}  while ((StandardID[j] < '0') ||	/* !isdigit(SYB_ID_Buffer[j]) */
				  (StandardID[j] > '9'));

		if (ASCII_Code[i] != StandardID[j])	 {
			return(NO);/**	一致しない	*/
		}
	}
	return(YES);
}


/*************************************************************************
	module		:[相手先電話ＮＯ.(ASCII)と標準IDの下４桁を照合]
	function	:[
		1.
	]
	return		:[
			相手局のIDFrameがない､オールスペース NG		:NO(0)
			4桁照合OK									:YES(1)
			どちらかが4桁未満でその少ない方の桁照合OK	:(2)
	]
	common		:[
						StandardID	:標準ＩＤ（発信元）を格納するバッファ
		修正：StandardIDを引数option_idで見る様に変更	1997/10/20  By T.Yamaguchi
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/24]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckASCII_DialAndStandardID(UBYTE *ASCII_Dial, UBYTE *std_id)
{
	BYTE i;
	BYTE j;
	UBYTE k;
	/**	ワンタッチ､または短縮ダイヤルの最後の桁数(最大40桁)をローカル変数 i にセット	*/
	/*	桁数のテーブルは、最大のもので固定しておく	*/
	for (i = 0; i < (SYS_TEL_2DIGIT_MAX * 2); i++)	{
		if (ASCII_Dial[i] == NULL)	{
			break;
		}
	}
	/**	標準ＩＤの最後の桁数(最大21桁)をローカル変数にセット	*/
	for (j = 0; j < SYS_ID_MAX; j++)  {
		if (std_id[j] == 0x00)	{
		/* if (StandardID[j] == 0x00)	{ */
			if (j == 0) {/**	標準ＩＤが登録されていない	*/
				return (NO);
			}
			break;
		}
	}
	for (k = 0; k < 4; k++)	 {/**	終わりの４桁が一致するか	*/
		do	{
			--i;
			if (i < 0)	{
				return(2);
			}
		}  while ((ASCII_Dial[i] < '0') ||	/* !isdigit(ASCII_Dial[i]) */
				  (ASCII_Dial[i] > '9'));
		do	{
			--j;
			if (j < 0)	{
				return(2);
			}
		}  while ((std_id[j] < '0') ||	/* !isdigit(SYB_ID_Buffer[j]) */
				  (std_id[j] > '9'));

		if (ASCII_Dial[i] != std_id[j])	 {
			return(NO);/**	一致しない	*/
		}
	}
	return(YES);
}


/*************************************************************************
	module		:[BCDダイヤルＮＯ.と標準ＩＤのチェック]
	function	:[
		1.
	]
	return		:[
			相手局のIDFrameがない､オールスペース NG		:NO(1)
			4桁照合OK									:YES(0)
			どちらかが4桁未満でその少ない方の桁照合OK	:(2)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/07]
	author		:[鈴木郁二]
*************************************************************************/
static UBYTE  ASCII_DialBuf[SYS_TEL_2DIGIT_MAX * 2] = {0};	/*	最長のものにあわせた40桁	*/

UBYTE CheckBCD_DialAndStandardID(UBYTE *BCD_Dial, UBYTE *id_buf)
{
	FCM_GetDialData(ASCII_DialBuf, BCD_Dial);	/*	BCD ダイヤルデータを ASCII ダイヤルデータにセット	*/
	return(CheckASCII_DialAndStandardID(ASCII_DialBuf, id_buf));
}


/*************************************************************************
	module		:[カナＩＤバッファチェック]
	function	:[
			カナＩＤバッファ内にカナＩＤが入っているかどうかをチェックする
	]
	return		:[カナＩＤまたは、セット:YES  ＩＤ なし:NO]
	common		:[
			SYB_TTI_Buffer		:カナＩＤ（発信元）を格納するバッファ
	]
	condition	:[]
	comment		:[TTI の有無は確認しない。
			1.94/11/15 桐、椛は、SYB_TTI_ID_Buffer[] をチェック。
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckTransmitterID_Buf(void)
{

#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)

 /* ＰＯＰＬＡＲ＿Ｈ標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
  #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		if(SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] == NULL) {		/**	カナＩＤ無し	*/
			return(NO);
		}
		else {	/**	カナＩＤあり	*/
			return(YES);
		}
	}
	else {
		if(SYB_TTI_ID_Buffer[SYS_InternalLineNumber][0] == NULL) {		/**	カナＩＤ無し	*/
			return(NO);
		}
		else {	/**	カナＩＤあり	*/
			return(YES);
		}
	}
  #else
	if(SYB_TTI_ID_Buffer[SYS_InternalLineNumber][0] == NULL) {		/**	カナＩＤ無し	*/
		return(NO);
	}
  #endif
 #else
  #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		if(SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] == NULL) {		/**	カナＩＤ無し	*/
			return(NO);
		}
		else {	/**	カナＩＤあり	*/
			return(YES);
		}
	}
	else {
		if(SYB_TTI_ID_Buffer[0] == NULL) {		/**	カナＩＤ無し	*/
			return(NO);
		}
		else {	/**	カナＩＤあり	*/
			return(YES);
		}
	}
  #else
	if(SYB_TTI_ID_Buffer[0] == NULL) {		/**	カナＩＤ無し	*/
		return(NO);
	}
  #endif
 #endif

#else
	/* 常にNOでリターンしていたので修正する QAT SATUKI_H 940706 12.Jly'94 Y.Suzuki */
 /* ＰＯＰＬＡＲ＿Ｈ標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	if (SYB_TTI_Buffer[SYS_InternalLineNumber][0] == NULL) {		/**	カナＩＤ無し	*/
		return(NO);
	}
 #else
	if (SYB_TTI_Buffer[0] == NULL) {		/**	カナＩＤ無し	*/
		return(NO);
	}
 #endif
#endif
#if (PRO_MULTI_TTI == DISABLE) /* By H.Fujimura 1999/03/25 */
	else {	/**	カナＩＤあり	*/
		return(YES);
	}
#endif
}


/*************************************************************************
	module		:[ＩＤバッファチェック]
	function	:[
		ＩＤバッファ内にSUB_IDが入っているかどうかをチェックする
	]
	return		:[SUB_ID セット:YES	 SUB_ID なし:NO]
	common		:[
			SYB_ID_Buffer		:自機電話ＮＯ．を格納するバッファ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckSubscriberID_Buf(void)
{
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		if (SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] == NULL) {		/**	自機電話番号登録なし	*/
			/**	リターンNO	*/
			return(NO);
		}
		else {
			/**	リターンYES	*/
			return(YES);
		}
	}
	else {
		if (SYB_ID_Buffer[SYS_InternalLineNumber][0] == NULL) {		/**	自機電話番号登録なし	*/
			/**	リターンNO	*/
			return(NO);
		}
		else {
			/**	リターンYES	*/
			return(YES);
		}
	}
 #else
  #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/26 */
	if (SYB_ID_Buffer[0][0] == NULL) {							/**	自機電話番号登録なし	*/
  #else
	if (SYB_ID_Buffer[SYS_InternalLineNumber][0] == NULL) {		/**	自機電話番号登録なし	*/
  #endif		/* End of (defined (KEISATSU)) */
		/**	リターンNO	*/
		return(NO);
	}
	else {
		/**	リターンYES	*/
		return(YES);
	}
 #endif
#else
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		if (SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] == NULL) {		/**	自機電話番号登録なし	*/
			/**	リターンNO	*/
			return(NO);
		}
		else {
			/**	リターンYES	*/
			return(YES);
		}
	}
	else {
		if (SYB_ID_Buffer[0] == NULL) {		/**	自機電話番号登録なし	*/
			/**	リターンNO	*/
			return(NO);
		}
		else {
			/**	リターンYES	*/
			return(YES);
		}
	}
 #else
	if (SYB_ID_Buffer[0] == NULL) {		/**	自機電話番号登録なし	*/
		/**	リターンNO	*/
		return(NO);
	}
	else {
		/**	リターンYES	*/
		return(YES);
	}
 #endif
#endif
}


/*************************************************************************
	module		:[ＴＴＩのセット]
	function	:[
		1.カナＩＤをモデムバッファにセットする。
		2.さつき、ラベンダーは、SYB_TTI_Buffer の内容をセット
		3.桐、紅葉は、SYB_TTI_ID_Buffer の内容をセット　SYB_TTI_ID_Buffer がなければ
		  SYB_TTI_Buffer の内容をセットとする 18.Jly'94 Y.Suzuki
	]
	return		:[モデムバッファのポインタ]
	common		:[
				SYB_TTI_Buffer		:カナＩＤ（発信元）を格納するバッファ
				MDM_ModemBuffer			:モデムバッファ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
UWORD SetTransmitterID_Frame(WORD pos)/*	モデムバッファのポインター	*/
{
	WORD i;/* pos は int である */
	UBYTE j;

#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)

 /* ＰＯＰＬＡＲ＿Ｈ標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
  #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
			if(SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
				break;
			}
			/**	カナＩＤバッファの内容をモデムバッファにセット	*/
			MDM_ModemBuffer[InNS][i] = SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j];
		}
	}
	else {
		for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
			if(SYB_TTI_ID_Buffer[SYS_InternalLineNumber][j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
				break;
			}
			/**	カナＩＤバッファの内容をモデムバッファにセット	*/
			MDM_ModemBuffer[InNS][i] = SYB_TTI_ID_Buffer[SYS_InternalLineNumber][j];
		}
	}
  #else
	for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
		if(SYB_TTI_ID_Buffer[SYS_InternalLineNumber][j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
			break;
		}
		/**	カナＩＤバッファの内容をモデムバッファにセット	*/
		MDM_ModemBuffer[InNS][i] = SYB_TTI_ID_Buffer[SYS_InternalLineNumber][j];
	}
  #endif
 #else
  #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
			if(SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
				break;
			}
			/**	カナＩＤバッファの内容をモデムバッファにセット	*/
			MDM_ModemBuffer[InNS][i] = SYB_Multi_TTI_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j];
		}
	}
	else {
		for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
			if(SYB_TTI_ID_Buffer[j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
				break;
			}
			/**	カナＩＤバッファの内容をモデムバッファにセット	*/
			MDM_ModemBuffer[InNS][i] = SYB_TTI_ID_Buffer[j];
		}
	}
  #else
	for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
		if(SYB_TTI_ID_Buffer[j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
			break;
		}
		/**	カナＩＤバッファの内容をモデムバッファにセット	*/
		MDM_ModemBuffer[InNS][i] = SYB_TTI_ID_Buffer[j];
	}
  #endif
 #endif

#else
	for(i = pos,j = 0;j < 16; i++,j++) {/**	カナＩＤセット	*/
 /* ＰＯＰＬＡＲ＿Ｈ標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		if (SYB_TTI_Buffer[SYS_InternalLineNumber][j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
			break;
		}
		/**	カナＩＤバッファの内容をモデムバッファにセット	*/
		MDM_ModemBuffer[InNS][i] = SYB_TTI_Buffer[SYS_InternalLineNumber][j];
 #else
		if (SYB_TTI_Buffer[j] == NULL) {		/**	カナＩＤバッファ＝＝NULL	*/
			break;
		}
		/**	カナＩＤバッファの内容をモデムバッファにセット	*/
		MDM_ModemBuffer[InNS][i] = SYB_TTI_Buffer[j];
 #endif

	}
#endif
	for(;j < 16; j++) {/**	１６文字に満たない場合、スペースをセット	*/
		MDM_ModemBuffer[InNS][i] = ' ';
		i++;
	}
	/**	リターン引数＋１５	*/
	return(pos+15);
}


/*************************************************************************
	module		:[サブＩＤセット]
	function	:[
		TSI,CSI,CIG のためモデムバッファにサブＩＤをセットする
	]
	return		:[]
	common		:[
					SYB_ID_Buffer		:自機電話ＮＯ．を格納するバッファ
					MDM_ModemBuffer	:モデムバッファ
	]
	condition	:[]
	comment		:[SYB_ID_Buffer[]の中には､サブIDの先頭の桁から入っている.モデムバッファには、サブIDの最後の桁からセットする。（Ｔ３０の規定）
		モデムバッファのライトポインタは､３から必ず始まるので引き数として取り込まなくてよい｡]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[鈴木 郁二]
*************************************************************************/
void SetSubscriberID_Frame(void)
{
	UBYTE  i;
	UBYTE  j;
	UBYTE id_data;

	i = 0;
	j = 0;
	id_data = 0;

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		while ((SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j] != NULL) && (j < SYS_ID_MAX)) {
			j++;
			i++;
		}
	}
	else {
		while ((SYB_ID_Buffer[SYS_InternalLineNumber][j] != NULL) && (j < SYS_ID_MAX)) {
			j++;
			i++;
		}
	}
 #else
	while ((SYB_ID_Buffer[SYS_InternalLineNumber][j] != NULL) && (j < SYS_ID_MAX)) {
		j++;
		i++;
	}
 #endif
#else
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
		while ((SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][j] != NULL) && (j < SYS_ID_MAX)) {
			j++;
			i++;
		}
	}
	else {
		while ((SYB_ID_Buffer[j] != NULL) && (j < SYS_ID_MAX)) {
			j++;
			i++;
		}
	}
 #else
	while ((SYB_ID_Buffer[j] != NULL) && (j < SYS_ID_MAX)) {
		j++;
		i++;
	}
 #endif
#endif

	for(j = 3; (j < (SYS_ID_MAX + 2)) && (i < SYS_ID_MAX ); i--)/**	ＩＤ桁数が２０以下*/ {
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
			id_data = SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][i];
		}
		else {
			id_data = SYB_ID_Buffer[SYS_InternalLineNumber][i];
		}
 #else
		id_data = SYB_ID_Buffer[SYS_InternalLineNumber][i];
 #endif
#else
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
			id_data = SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][i];
		}
		else {
			id_data = SYB_ID_Buffer[i];
		}
 #else
		id_data = SYB_ID_Buffer[i];
 #endif
#endif
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
		case '+':
			MDM_ModemBuffer[InID][j] = id_data;
			j++;
			break;
		default:
			MDM_ModemBuffer[InID][j] = ' ';
			j++;
			break;
		}
	}
	for(;j < SYS_ID_MAX+2; j++) {		/**	サブＩＤが２０桁以下	*/
		/* スペースが正しくセットされていなかった QAT SATUKI_H 940706 15.Jly'94 Y.Suzuki */
		/**	スペースをセット	*/
		MDM_ModemBuffer[InID][j] = ' ';
	}
	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[GetOwnMakerPartnerID()]
	function	:[
		独自フレームよりｶﾅIDを取り出し大域の配列にセットする
		相手機がカナＩＤを持たない場合、TTIを取り込むことになる。
	]
	return		:[なし]
	common		:[
				MDM_ModemBuffer		:モデムバッファ
				NonStdFrmPos			:受信した独自フレームのモデムバッファ上の位置
				NonStandardID	:相手機カナＩＤを格納するバッファ
	]
	condition	:[]
	comment		:[FX仕様の場合は不要]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/27]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void GetOwnMakerPartnerID(WORD pos)	/*	独自フレームのリードポインターｰ	*/
{
	UBYTE i;
	WORD j;
	i = 0;
	j = 0;

	/**	大域配列にモデムバッファからカナIDをセットする	*/
	for (i = 0, j = pos; i < (SYS_TTI_ID_MAX - 1); i++, j++) {
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
		if((MDM_ModemBuffer[NonStdFrmPos][j] >= 0x80) && (MDM_ModemBuffer[NonStdFrmPos][j] <= 0x9F)) {/* 特殊文字のコードの場合 '*' に置き換える */
			NonStandardID[i] = 0x2A;
		}
		else {
			NonStandardID[i] = MDM_ModemBuffer[NonStdFrmPos][j];
		}
#else
		NonStandardID[i] = MDM_ModemBuffer[NonStdFrmPos][j];
#endif
	}
	NonStandardID[SYS_TTI_ID_MAX - 1] = NULL;
	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[GetPartnerID()]
	function	:[
		大域配列にTSI,CSI,CIG よりSUB_IDをセットする
	]
	return		:[なし]
	common		:[
				RxID_FrameByteCount		:受信したＩＤフレームのバイト数
				MDM_ModemBuffer		:モデムバッファ
				ID_FrmPos				:受信したＩＤフレームのモデムバッファ上の位置
				RxStandardID_Buffer	:相手機標準ＩＤ（サブＩＤ）を格納するバッファ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/27]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void GetPartnerID(void)
{
	/**	スペースを取り除く処理をしながら大域配列にSUB_IDをセットする	*/
	UBYTE data;
	UBYTE i;
	UBYTE j;
	UBYTE degit_flag;

	data = 0;
	i = 0;
	j = (UBYTE)(RxID_FrameByteCount - 1);
	degit_flag = 0;

	for ( ; ((i < (SYS_ID_MAX - 1) && (j >= START_HDLC_FIF_POS))); j--) {
		data = MDM_ModemBuffer[ID_FrmPos][j];
#if(PRO_TSI_RELAY_COM == ENABLE)
		/*-------------------------------------------------------------------------------------------*/
		/*	 TSIによる中々継を受け付ける場合は、グループＮＯを明確にするためスペースを削除しない。	 */
		/*	 15.Feb'95 Y.Suzuki																		 */
		/*-------------------------------------------------------------------------------------------*/
		if(TSI_Relay == 1)	{
			if(degit_flag == 0) {
				if (data != ' ') {
					degit_flag = 1;
					StandardID[i] = data;
					i++;
				}
			}
			else {
				StandardID[i] = data;
				i++;
			}
		}
		else {
			if (data != ' ') {
				StandardID[i] = data;
				i++;
			}
		}
#else
/*		if (data != ' ') {	1997/02/12	By T.Yamaguchi */
		/* ０～９または、＊、＃、＋のとき スペースその他のデータは無視する	 */
		if (((data >= '0') && (data <= '9')) || (data == '+') || (data == '*') || (data == '#')) {
			StandardID[i] = data;
			i++;
		}
#endif
	}
	StandardID[i] = NULL;

	return;
}


#if (PRO_RELAYED_REPORT == ENABLE)/* 椛のみ 27.Jan'94 */
/*************************************************************************
	module		:[配信結果返送先ＮＯセット]
	function	:[
		1.有効とするTSIは、+81-75(0を省略した市外局番)-??-???? または、
		  +81-075(市外局番)??-???? または、075(市外局番)-??-????. その他は、NG とする。
		2.有効とするTSIの桁数に満たないTSIは、NGにする。
	]
	return		:[
			セットOK:YES ／ TSI不良:NO
	]
	common		:[
					StandardID
					SYB_CommandFile:RelaySourceID
	]
	condition	:[]
	comment		:[親機のIDをコマンドファイルの所定の位置にセットする]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/01/27]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetTransmitStationID(void)
{
	UBYTE i;
	UBYTE j;
	/* '+' '8' '1' を削除　'0'を付加 */
	j = 0;
	i = 0;

	/* TSI に格納された番号が次の場合のみ、不達通知を受け付ける。
	** 1. +81...
	** 2. 81...
	***3. 0...
	*/

	/* 先頭の処理 */
	if((StandardID[j] < '0') || (StandardID[j] > '9')) {/* １桁目の'+'を削除 */
		j++;
	}
	if(StandardID[j] == '8') {/* 先頭が81なら削除 */
		j++;
		if(StandardID[j] == '1') {
			j++;
			if(StandardID[j] != '0') {/* 先頭に'0'がついてなければ付加する 市外局番から入っているはず */
				SYB_CommandFile[RelayedCommandNo].Option.OptionNumber.RelaySourceID[i] = '0';
				i++;
			}
		}
		else {/** TSI NG */
			return(NO);
		}
	}
	else if(StandardID[j] != '0') {/* 先頭 81､0 以外で始まる。TSI NG */
		return(NO);
	}
	while(StandardID[j] != NULL) {/* j の最大値も条件に加えるべき */
		if((StandardID[j] < '0') || (StandardID[j] > '9')) {/* 数字以外は削除 */
			j++;
		}
		SYB_CommandFile[RelayedCommandNo].Option.OptionNumber.RelaySourceID[i] = StandardID[j];
		i++;
		j++;
	}
	SYB_CommandFile[RelayedCommandNo].Option.OptionNumber.RelaySourceID[i] = NULL;
	if (j < CHK_TSI_Figur()) {/* 先頭の+を含むTSIの桁数 */
		return(NO);
	}
	return(YES);
}
#endif
