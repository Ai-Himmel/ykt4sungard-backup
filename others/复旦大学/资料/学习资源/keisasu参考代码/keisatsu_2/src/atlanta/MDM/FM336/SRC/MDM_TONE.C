/*---------------------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                              */
/*  ファイル名   : mdm_tone.c                                                            */
/*  作成者       :                                                                       */
/*  日  付       : 1999/10/06                                                            */
/*  概  要       : トーン送出処理                                                        */
/*  修正履歴     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\pro_def.h" /* Added by H.Kubo 1997/07/04 for USA_CODE */
#include "\src\atlanta\define\fcm_def.h" /* Added by H. Kubo 1997/06/23 */
#include "\src\atlanta\define\fcm_pro.h" /* Added by H. Kubo 1997/11/06 */

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"

#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0))/* By M.Maeda 2002/09/18 */
#include "\src\atlanta\mdm\fm336\define\mdm_conf.h"
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
#include "\src\atlanta\define\ncu_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\define\sysrxsw.h"
#endif

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

/*************************************************************************
	module		:[トーン送出]
	function	:[
		1.トーンテーブルの番号を指定する事で該当するトーンを送出します。
	]
	return		:[なし]
	common		:[
		ModemBlock
	]
	condition	:[
		called by NCU_SUB2.C:TransmitTone();
	]
	comment		:[]
	ProtoType	:[void far MDM_Tone(UBYTE ){}]
	date		:[1994/01/05]
	update		:[1995/12/16]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_Tone(UBYTE tblno)	/*	トーン選択テーブルＮｏ．	*/
{
	/* 送出レベルに応じたモデムのTxLossをセットします */
	MDM_TransmitLevelSet((UBYTE) FCM_PtnrChk_T23Attenation());

	MDM_SingleToneOn(tblno);	/* 単一トーンを送出します */

#if (PRO_VOICE_ANSWER == ENABLE)
	/*-------------------------------------------------
	** （NTT TEL/FAXで擬似RBT鳴動したままとなる対策）
	** この関数をコールしているTransmitTone()で単一トーンを送出した後
	** wai_tskし、その後単一トーンをストップしている。
	** そのため、wai_tskしている間にスケジューリングがおこりTransmitTone()
	** をコールしているタスクが殺された場合、単一トーンを送出したままとなる
	** 単一トーン送出中を示すフラグを作成し、送出中であれば、TransmitTone()
	** をコールしているタスクが殺される時に、単一トーンを止める処理をいれる。
	** 2001/11/30 M.Matsumoto
	** add by O.Kimoto 2002/11/14
	*/
	MDM_IsSingleToneON = 1;
#endif

}


/*************************************************************************
	module		:[トーン送出ストップ]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[YAWARAより移植]
	date		:[2002/11/14]
	author		:[木元]
*************************************************************************/
void  MDM_ToneOff(void)
{
	MDM_SetIO(POS_RTS,OFF);		/* モデムのRTSPをクリアーします */

#if (PRO_VOICE_ANSWER == ENABLE)
	/*-------------------------------------------------
	** （NTT TEL/FAXで擬似RBT鳴動したままとなる対策）
	** この関数をコールしているTransmitTone()で単一トーンを送出した後
	** wai_tskし、その後単一トーンをストップしている。
	** そのため、wai_tskしている間にスケジューリングがおこりTransmitTone()
	** をコールしているタスクが殺された場合、単一トーンを送出したままとなる
	** 単一トーン送出中を示すフラグを作成し、送出中であれば、TransmitTone()
	** をコールしているタスクが殺される時に、単一トーンを止める処理をいれる。
	** 2001/11/30 M.Matsumoto
	*/
	MDM_IsSingleToneON = 0;
#endif

}


/*************************************************************************
	module		:[トーン送出（時間指定有り）]
	function	:[
		1.指定されたトーンテーブルのトーンを送出します
		2.指定時間トーンを送出すればトーンを停止する
		3.時間はｗａｉ＿ｔｓｋ（）を使用して他のタスクに制御を渡す
	]
	return		:[なし]
	common		:[]
	condition	:[
		called by FCM_SPD.C(278):FaxTransmitCED();
		called by FCM_SPD.C(309):FCM_FaxTransmit1080Hz();
		called by FCM_SPD.C(340):FaxTransmit1300Hz();
	]
	comment		:[]
	ProtoType	:[void far MDM_ToneTx(UBYTE ,UWORD ){}]
	date		:[1994/01/05]
	update		:[1995/12/16]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_ToneTx(
	UBYTE	tblno,		/* トーン選択テーブルＮｏ．	*/
	UWORD	time) 		/* 送出期間 ( ms )          */
{
	UBYTE level_value;

	/**************************************
	** 送出レベルに応じたモデムのTxLoss設定
	**************************************/
	level_value = FCM_PtnrChk_T23Attenation();
	level_value *= ( (UBYTE) 0x10 );	/** 設定する値を換算します **/
	MDM_TxLossSet(level_value);	/* 送出レベルに応じたモデムのTxLossをセットします */

	/**************************
	** 単一トーンを指定時間送出
	**************************/
	MDM_SingleToneOn(tblno);
	wai_tsk(time/10);			/* 1ms単位 */
	MDM_SingleToneOff();

	/**********************
	** 送信レベルを再セット
	**********************/
	MDM_TxLossSet(MDM_TxLevelSaveValue);
}


/******************************************************************************
	module		:[単一トーン送出開始]
	function	:[
		1. モデムコンフィギュをトーン送出に構成にします
		2. 単一トーンの周波数をセットします
		3. 単一トーンのレベルを0dBmにセットします
		4. モデムのRTSをセットします
	]
	return		:[なし]
	common		:[
		SingleFrequencyTable
	]
	condition	:[
		送信レベル設定を事前に行っておく事
	]
	date		:[1993/11/29]
	update		:[1996/03/13]
	author		:[橘正樹、木元修]
******************************************************************************/
void  MDM_SingleToneOn(UBYTE tone_type)
{
	UBYTE country_code;
	UBYTE base_level;

	country_code = (SYB_MachineParameter[COUNTRY_CODE] & 0x0F);

	/*------------------------------*/
	/* トーン送出モデム構成にします */
	/*------------------------------*/
	MDM_ToneTxConfigSet(TX_SINGLE_TONE);

	/*----------------------------------*/
	/* 単一トーンの周波数をセットします */
	/*----------------------------------*/
	/*----------------------------------------------*/
	/* 高群,低群の周波数REGに同じ値を設定します.    */
	/* どちらか一方だけをセットすると,DTMF送出後の  */
	/* CNG信号がミックス・トーンになります.         */
	/* DTMF送出の設定が,半分,残っているためです.    */
	/*----------------------------------------------*/
	MDM_SetDualTone1Frequency(SingleFrequencyTable[tone_type]);
	MDM_SetDualTone2Frequency(SingleFrequencyTable[tone_type]);

	/*-----------------------------------------------*/
	/* 単一トーンの送出レベルはRAMのトーンレベルを   */
	/* -1.0dBmに固定してTxLossの値で変更します       */
	/*-----------------------------------------------*/
	/*-----------------------------------------------*/
	/* 単一トーンのレベルを-1.0dBmにセットします     */
	/* 同一TXLOSSの設定の場合に,                     */
	/* FSK,PIXの信号レベルと単一トーンの信号レベルを */
	/* 合わす必要があります.                         */
	/*-----------------------------------------------*/
	/*-----------------------------------------------*/
	/* 低群のレベルは最小に設定する必要があります.   */
	/* 高群レベルと低群レベルを同じ値に設定した場合, */
	/* 設定レベルで出力される場合と設定レベルより    */
	/* かなり低い値で出力される場合があります.       */
	/* これは,高群と低群のトーンが同一位相で         */
	/* 出力されないために,振幅が打ち消されて,        */
	/* レベルが下がると予想されます.                 */
	/*-----------------------------------------------*/
	base_level = MDM_GetToneBaseLevel();
	MDM_SetDualTone1PowerLevel(DTMF_LevelCountryTable[country_code][base_level].HighLevel);
	MDM_SetDualTone2PowerLevel((UWORD)(0x0000));

	/**********************
	** モデムのRTSPをセット
	**********************/
	MDM_SetIO(POS_RTS,ON);
}


/******************************************************************************
	module		:[単一トーン送出終了]
	function	:[
		1. モデムのRTSPをクリアします
		2. モデムコンフィギュのトーン送出を解除します
	]
	return		:[なし]
	common		:[
		R96_Reg     モデム・インタフェース・メモリ
	]
	condition	:[
		処理終了後、送信レベルを再セットする事
	]
	date		:[1993/11/29]
	author		:[橘正樹]
******************************************************************************/
void  MDM_SingleToneOff(void)
{
	MDM_SetIO(POS_RTS,OFF);		/* モデムのRTSPをクリアーします */
	MDM_InitialConfig();		/* トーン送出モデムを解除します */
}


/******************************************************************************
	module		:[モデムのTXLOSSの設定]
	function	:[
		1. モデムインターフェースメモリのＴＬＶＬを設定します。
	]
	return		:[なし]
	common		:[
	]
	ProtoType	:[void near MDM_TxLossSet(UBYTE ){}]
	date		:[1993/11/29]
	update		:[1995/12/16]
	author		:[橘正樹、木元修]
******************************************************************************/
void  MDM_TxLossSet(UBYTE	level)
{
	/*
	** ＤＳＰ＿ＲＡＭでも調整出来ますが、とりあえず、
	**インターフェース･メモリで調整しておきます。
	*/
	MDM_SetIO(POS_TLVL,level);	
	MDM_SetIO(POS_NEWC,ON);
}

/*************************************************************************
	module		:[トーン送出コンフィギュレーション]
	function	:[
		1. モデムのコンフィギュレーションに0x80を設定します
		5. セットアップ・ビットをＯＮします
		6. セットアップ終了を待ちます
	]
	return		:[なし]
	common		:[なし]
	date		:[1993/11/29]
	update		:[1996/03/13]
	author		:[橘正樹、木元修]
*************************************************************************/
void  MDM_ToneTxConfigSet(UBYTE mode)
{
	MDM_SetIO(POS_CONF,mode);	/** CONFをデュアルトーンにセットします */

	/*-----------------------------------------------------*/
	/** OVRUN,EQSV,EQFZ,ZEROC,ABIDL,EOF,CRC,FLAGのクリアー */
	/*-----------------------------------------------------*/

	/*----------------------------*/
	/* セット・アップを実行します */
	/*----------------------------*/
	MDM_SetIO(POS_NEWC,ON);
}


/*************************************************************************
	module		:[トーンモードコンフィグ]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[MDM]
	date		:[1996/11/29]
	author		:[村田]
*************************************************************************/
void MDM_ToneModeConfig(void)
{
	MDM_SetIO(POS_CONF, TX_SINGLE_TONE);
	MDM_SetIO(POS_NEWC, ON);
}


/*************************************************************************
	module		:[トーン送出基準レベルの獲得]
	function	:[
					単一トーンの送出レベルは、DSP RAMのトーンレベルを
					固定してTLVLの値で変更します
					固定するDSP RAMの値はDTMF_LevelCountryTable[]より
					決定します。
					ＵＳＡの場合-1dBに設定します。
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[SH7043,V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1997/04/01]
	author		:[村田]
*************************************************************************/
UBYTE  MDM_GetToneBaseLevel(void)
{
	UBYTE country_code;
	country_code = (SYB_MachineParameter[COUNTRY_CODE] & 0x0F);

#if defined(USA)
	if (country_code == 0) {
		return(1);		/* DSP RAM -1dB */
	}
	else {
		return(8);		/* DSP RAM -8dB */
	}
#else
 #if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)
 	/* 
 	**トーン送出レベルはTLVLの値だけでなく、DTMFレベルの値にも影響を
 	** 受ける。DTMF送出レベルのテーブル値を変更したため、ここを微調整
 	** して、送出レベルを合わせる
 	**
 	** 2000/09/24 by K.Okada
 	**
 	** HINOKI2ではDTMF送出レベルのテーブル値を4dB下げたので、ここで4dBあげておく
 	** 2002/01/23 T.Takagi
 	*/
	return(4);		/* DSP RAM -4dB */
 #else
	return(8);		/* DSP RAM -8dB */
 #endif
#endif
}

#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0))/* By M.Maeda 2002/09/18 */
/*************************************************************************
	module		:[DTMF受信器にコンフィグ]
	function	:[
		1.モデムをDTMF受信モードに設定します
		2.受信信号レベルゲインを下げる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ダイヤルインDTMF検出時のみ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[2000/06/05]
	author		:[K.Okada]
*************************************************************************/
void MDM_ConfigDTMF_ReceiverMode(void)
{
	MDM_SetIO(POS_CONF, MDM_R288F_CONF_DTMF_RECEIVER);
	MDM_SetIO(POS_NEWC, ON);

/*
** [ダイヤルイン外線でDTMFをたまにとりこぼす不具合 2000/12/12 by K.Okada]
** ダイヤルインのときのDTMF検出性能として、TASで-5dBm(低群-9.5dBm、高群-7.5dBm)程度であるが、
** ダイヤルイン外線からは低群-8.5dBm、高群-7.6dBm程度の信号がきている。
** よって、ダイヤルインDTMF検出時のみ、受信信号レベルゲインを下げる
**
** NTT技術資料によると、DTMFレベルは低群(-15.5-0.8L)dBm以上(-4.0-0.8L)dBm以下、
** 高群(-14.5-L)dBm以上(-3.0-L)dBm以下となっている。
** 現在のレベル境界から約6dBmあげるように、受信信号レベルゲインを下げる。
** DSP RAMアドレス0x0B3CはFM336のマニュアルには記載がないので、
** 測定して最適値を決定した。測定結果は次のとおり。
** (ただし、低群レベル = TAS測定値 - 約4dBm、高群レベル = TAS測定値 - 約2dBm程度となる)
** -------------------------------
** 0x0B3Cの値      TAS測定値(dBm)
** -------------------------------
** 0x3000        ：-38.1～ 0.0
** 0x4000        ：-40.6～-1.4
** 0x4800        ：-41.7～-2.5
** 0x5000        ：-43.0～-4.0
** 0x5500        ：-43.2～-4.0
** 0x61D4(ﾃﾞﾌｫﾙﾄ)：-44.4～-5.2
** -------------------------------
**
**	HINOKI2 0x4000 で-40.9～0.0(dBm) measured by 2002/01/30 T.Takagi
**
*/
	BackupReceiveLevel = DspRamAccessReadMethod3(0x0B3C);
 #if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	if (((AttemptRxModeSwitch == SYS_DIAL_IN_READY)
	|| (AttemptRxModeSwitch == SYS_MODEM_DIALIN_READY))
	&& (!NCU_RemoteTransferDial())){
		DspRamAccessWriteMethod3(0x0B3C, 0x3000, 0x0000);
 	}
 	else {

		/* リモートダイアル転送時のＤＴＭＦ信号検出
		** ＤＴＭＦ送出のNTT規格は、
		**             低群            高群
		**  上限      -3.5dBm         -2.5dBm
		**  下限     -20.3dBm        -20.3dBm
		**
		**  実力は、
		**  SAKAKI2
		**  上限      -3.5dBm         -1.1dBm
		**  下限     -30.0dBm以下    -30.0dBm以下
		**  ＯＮ時間のMIN：４９ｍｓ
		**  ＯＦＦ時間のMIN：３４ｍｓ
		**
		**  HINOKI2
		**  上限      -3.3dBm         -1.2dBm
		**  下限     -30.0dBm以下    -30.0dBm以下
		**  ＯＮ時間のMIN：４９ｍｓ
		**  ＯＦＦ時間のMIN：３５ｍｓ
		*/
		switch (CHK_ReceiveDtmfLevelRange()) {
		case 0:
			DspRamAccessWriteMethod3(0x0B3C, 0x2000, 0x0000);
			break;
		case 1:	/* -38.1～ 0.0 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, 0x3000, 0x0000);
			break;
		case 2:	/* -40.6～-1.4 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, 0x4000, 0x0000);
			break;
		case 3:	/* -41.7～-2.5 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, 0x4800, 0x0000);
			break;
		case 4:	/* -43.0～-4.0 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, 0x5000, 0x0000);
			break;
		case 5:	/* -43.2～-4.0 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, 0x5500, 0x0000);
			break;
		case 6:
			DspRamAccessWriteMethod3(0x0B3C, 0x1000, 0x0000);
			break;
		default:/* -44.4～-5.2 (dBm) */
			DspRamAccessWriteMethod3(0x0B3C, BackupReceiveLevel, 0x0000);
			break;
		}
	}
 #else
	DspRamAccessWriteMethod3(0x0B3C, 0x4000, 0x0000);
 #endif
}
#endif

