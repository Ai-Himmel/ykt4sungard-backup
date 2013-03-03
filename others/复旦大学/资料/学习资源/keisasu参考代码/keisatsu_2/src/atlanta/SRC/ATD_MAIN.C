/********************************************************************************************/
/*		ﾌﾟﾛｼﾞｪｸﾄ:ANZU																		*/
/*		ﾓｼﾞｭｰﾙ	:unsigned char AutoDial(unsigned char *)									*/
/*				:void far ToneDetectTaskInitial(void)										*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/30																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_MAIN.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\stng_pro.h"	/* CHK_DialType() */
#include "\src\atlanta\define\cmn_pro.h"	/* CMN_StringCopyNULL() */
#include "\src\atlanta\define\mon_pro.h"	/* wai_tsk() */
#include "\src\atlanta\define\man_pro.h"	/*	SYS_FaxComStopSwitch()	*/
#include "\src\atlanta\define\atd_pro.h"
#include "\src\memsw\define\mems_pro.h"		/*1996/04/17 Eguchi */
#include "\src\atlanta\define\ncu_pro.h"	/*	MercuryDial() */

#include "\src\atlanta\sh7043\define\io_pro.h"	/*	リレー関係	*/

#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\status.h"	/* LINE_TYPE_TONE */
#include "\src\atlanta\define\std.h"		/* NULL,OK,NG */
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\sys_stat.h"	/*Add By Eguchi 1994/09/12 "SYS_MACHINE_STATUS,SYS_POCKET_BELL"*/

#include "\src\atlanta\ext_v\bkupram.h"		/* SYB_RedialBuffer */
#include "\src\atlanta\ext_v\atd_data.h"
#include "\src\atlanta\ext_v\sys_data.h"	/* SYS_DialChange */

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) /* Added by SMuratec C.P 2004/07/08 for prefix */
#include "\src\atlanta\define\param.h"		/* COUNTRY_CODE 95.01.26 M.HARADA */
#include "\src\atlanta\ext_v\ncu_data.h"	/* MercuryKeyEnableFlag */
#endif

#include	"\src\atlanta\define\uni_pro.h"

#if (PRO_CLASS1 == ENABLE)		/* Add By Y.T 96.03.28 */
#include "\src\atlanta\ext_v\cl1_data.h"
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi*/
#endif
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_MULTI_LINE == ENABLE)	/* PSTN Access Number  By O.Kimoto 1996/12/25 */
	UBYTE ATD_PstnAccessNumberDialling(void);
#endif

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/06 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* MDM_BreakDTMF_Tx() */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* MDM_BreakDTMF_Tx() */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#endif

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\ext_v\atd_tbl.h"
#endif

#if defined(KEISATSU)	/* 警察FAX Added by SMuratec 夏 2005/10/24 */
#include "\src\memsw\define\mem_sw_a.h"
#endif

/*************************************************************************
	module		:[オートダイアラー]
	function	:[
		1.ダイアルトーン検出
		2.電話番号送出
		3.相手先着信検出
	]
	common		:[
		SYS_DialChange	:パルス－＞トーンに回線タイプ変更
		SYS_FaxComStopSwitch():ストップ・キー情報
		SYB_RedialBuffer[]:
	]
	condition	:[]
	comment		:[]
	return		:[
		AD_OK				:フェーズＡ完了
		AD_TIME_OVER		:タイムオーバー
		AD_DIAL_EMPTY		:バッファに電話番号が登録されていない
		AD_DESTROYD			:バッファの内容が壊れている
		AD_LOCAL_BUSY		:発着衝突発生
		AD_REMOTE_BUSY		:送信先が話中、又は回線混雑
		AD_NO_CURRENT_LOOP	:ループ電流が無い
		AD_STOPPED			:停止ボタンが押された
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[奥村明]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun. 19,1998 */
UBYTE	AutoDialFlsRom(UBYTE  *Buffer)
#else
UBYTE	AutoDial(UBYTE	*Buffer)
#endif
{
	UBYTE is_dialtonedetect = TRUE;	/*ﾀﾞｲｱﾙﾄｰﾝ検出ﾌﾗｸﾞ　FALSE:検出しない　TRUE:検出する*/
	UBYTE return_value = 0;			/*ﾄｰﾝ検出関数のﾘﾀｰﾝ値*/
	UBYTE cnt = 0;					/*ﾀﾞｲｱﾙﾊﾞｯﾌｧ(Buffer)のｲﾝｸﾘﾒﾝﾄ･ｶｳﾝﾀｰ*/
	UBYTE dial_num = 0;				/*Buffer[cnt]に登録されているﾀﾞｲｱﾙ番号*/
	UBYTE pre_dial_num = 0;			/*Buffer[cnt-1]に登録されているﾀﾞｲｱﾙ番号*/
#if defined(FRA)
	UBYTE is_continuous_pause = 0;	/*ﾎﾟｰｽﾞ記号("-/")が連続で続くかどうかの判断ﾌﾗｸﾞ*/
#endif
#if defined(EC1)	/* ITA仕様 */
	UBYTE redial_check_pointer = 0;
#endif
#if (PRO_PIN_ACCESS == ENABLE)		/* 95.12.26 By Y.Tanimoto */
	UBYTE pin_dial_num = 0;			/*SYS_PinBuffer[cnt]に登録されているPINﾀﾞｲｱﾙ番号*/
#endif

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
	UBYTE i;
	UBYTE compare_pos;
	UBYTE match;
	UBYTE is_find;
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/07/04 By N.Sakamot For Mercury *//* by K.Watanabe 2004/10/12 */
	#if (PRO_MODEM == ORANGE3)
	tskno_ATD_freq_check = 0xFFFF;
	#endif
#endif
	FCM_Is_ToneDetecting = YES;		/* 1997/09/12  By T.Yamaguchi */

	ToneDetectTaskInitial();/*	ﾀｽｸID初期化	*/
	SYS_DialChange = 0;		/* pulse -> tone に切り替える参照変数 */
	IsDialFirstNum = TRUE;	/* ダイヤル送出時にリレー（DP_Relay,S_Relay)を引く事を判断するフラグ(ダイヤルパルスのみ)	*/
	cnt = 0;				/* ダイヤルバッファのカウンタ	*/
#if defined(EC1)	/* ITA仕様 */
	redial_check_pointer = 0;
#endif

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Added by H.Kubo 1997/07/19 */
	/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */
	SYS_ToneCheckTimer = 0;
#endif

#if defined(POPLAR_H) && defined(JP1)/* V851 関西電力専用線 By Y.Suzuki 2003/05/30*/
	if (CHK_TransmitBy1300Hz()) {
		return(AD_OK);	/** AD_DIAL_EMPTYをﾘﾀｰﾝ */
	}
#endif

	if (Buffer[0] == NULL) {	/** ﾊﾞｯﾌｧに何も登録されていないとき */
		return(AD_DIAL_EMPTY);	/** AD_DIAL_EMPTYをﾘﾀｰﾝ */
	}

#if (PRO_CLASS1 == ENABLE)		/* 96.03.28 */
	CL1_ATD_DialType = 0x00;
	CL1_ContoneDet = 0;
	if ((Buffer[0] == 'D') || (Buffer[0] == '.')) {
		/* ダイヤルトーン検出の有無 */
		if (Buffer[0] == 'D') {
			is_dialtonedetect = TRUE;
		}
		else {
			is_dialtonedetect = FALSE;
			wai_tsk(S6*100+1);
		}
		/* ビジートーン検出の有無 */
		if (Buffer[1] == 'B') {
			PartnerAbility0 |= MEM_BUSYTONE_DETECT;
			CL1_ContoneDet = 1;	/* 96.04.19 */
		}
		else {
			PartnerAbility0 &= ~MEM_BUSYTONE_DETECT;
		}
		/* ダイヤル方式 */
		if (Buffer[2] == 'T') {
			CL1_ATD_DialType = 'T';
		}
		else {
			CL1_ATD_DialType = 'P';
		}
		cnt = 3;				/* ダイヤルバッファのカウンタ	*/
	}
#endif

	/*----------------*/
	/*内線発呼時の設定*/
	/*----------------*/
#if (PRO_CLASS1 == ENABLE)		/* Add By M.Tachibana 1995/12/25 */
	if ((CL1_ATD_DialType == 0x00) && CHK_PBX()) {	/** 内線の時 */
#else
 #if defined(POPLAR_H) /* V851 拡張回線の内線設定も見なければダメ By Y.Suzuki 2002/07/25*/
	if (CHK_PBX() || CHK_PBX_EXT()) {	/** 内線の時 */
 #else
	if (CHK_PBX()) {	/** 内線の時 */
 #endif
#endif
		/*---------------------------------------------------------------*/
		/*ﾀﾞｲｱﾙ前に回線にﾙｰﾌﾟ電流があるかﾁｪｯｸする  && 内線発呼前ﾎﾟｰｽﾞ　　*/
		/*0:電流無し　1:電流有り										 */
		/*---------------------------------------------------------------*/
		if (!LoopCurrentCheck(0)) {	/** ﾙｰﾌﾟ電流が無い時 */
			return (AD_NO_CURRENT_LOOP);	/** AD_NO_CURRENT_LOOPをﾘﾀｰﾝ */
		}
		/*---------------*/
		/*ｸﾞﾗﾝﾄﾞ･ｷｰの設定*/
		/*---------------*/
		if ((CHK_UNI_GroundkeyCheck())
			&& Buffer[0] == '-' && Buffer[1] == '/') {	/** ｸﾞﾗﾝﾄﾞｷｰ設定の時 */
			cnt = 2;		/**	バッファカウンタを２つ進める	*/
			GroundKeyOn();	/** ｸﾞﾗﾝﾄﾞｷｰ･ﾘﾚｰを引く */
			wai_tsk(30);	/** 300ms 待つ */
			GroundKeyOff();	/** ｸﾞﾗﾝﾄﾞｷｰ･ﾘﾚｰを開放 */
		}
		/*---------*/
		/* ﾌﾗｯｼｭｷｰ */		/* add by HARADA '94.3.21 */
		/*---------*/
		else if((CHK_UNI_FlashkeyCheck()) && Buffer[0] == '/' ){ /* '96.04.15 */
			cnt = 1;							/** バッファカウンタを２つ進める	*/
			Flash_Off_On(DIAL_STATUS_AUTODIAL);
		}
		else {	/** ｸﾞﾗﾝﾄﾞｷｰ･ﾌﾗｯｼｭｷｰ設定でない時 */
			is_dialtonedetect = FALSE; /** ﾀﾞｲｱﾙﾄｰﾝ検出無しにﾌﾗｸﾞをｾｯﾄ */
		}

#if (PRO_MULTI_LINE == ENABLE)	/* PSTN Access Number  By O.Kimoto 1996/12/25 */

 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/04/15 Eguchi */

		if (SYS_INF_ExecuteIFAX == TRUE) { /* INTERNET FAX 実行中 */
			if (SYS_INF_PSTN_AccessReq == TRUE) {/* ２回線以上あり、１回線目がPBX設定でPSTNｱｸｾｽ番号をダイアルする必要がある場合*/
				/* 機器に設定されているPSTN番号のダイアルを行う */
				if ((return_value = ATD_PstnAccessNumberDialling()) != AD_OK) {
					ATD_BreakDTMF_Tx();		/* H.Kubo 1997/11/06 */
					return(return_value);
				}
			}
		}
		else { /*INTERNET FAX実行中でない*/
			if ((SYS_CurrentExecutingCommand->Option & SYS_PSTN_ACCESS_ENABLE) != SYS_PSTN_ACCESS_ENABLE) {/** いまから発呼する宛先は内線／外線アクセス？ */
				/** 外線でした。－＞PSTN Access Number Dial */
				if ((return_value = ATD_PstnAccessNumberDialling()) != AD_OK) {
					ATD_BreakDTMF_Tx();		/* H.Kubo 1997/11/06 */
					return(return_value);
				}
			}
			else {
				/** 内線でした。－＞なにもせず */
			}
		}
 #else  /* PRO_DIALUP_INTERNET_FAX == DISABLE *//* 1998/04/14 Eguchi */

		if ((SYS_CurrentExecutingCommand->Option & SYS_PSTN_ACCESS_ENABLE) != SYS_PSTN_ACCESS_ENABLE) {/** いまから発呼する宛先は内線／外線アクセス？ */
			/** 外線でした。－＞PSTN Access Number Dial */
			if ((return_value = ATD_PstnAccessNumberDialling()) != AD_OK) {
				ATD_BreakDTMF_Tx();		/* H.Kubo 1997/11/06 */
				return(return_value);
			}
		}
		else {
			/** 内線でした。－＞なにもせず */
		}
 #endif /*End of (PRO_DIALUP_INTERNET_FAX == ENABLE) 1998/04/15 Eguchi*/
#endif

	}
	/*--------------------------------*/
	/*ﾀﾞｲｱﾙﾄｰﾝ検出処理 (DT,BT,CT,STOP)*/
	/*--------------------------------*/
	if (is_dialtonedetect) {	 /** ﾀﾞｲｱﾙﾄｰﾝ検出の時 */
		ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
		if ((return_value = DialToneDetect(BEFORE_DIAL)) != AD_OK) {	/* ﾀﾞｲｱﾙﾄｰﾝが検出できなかった時 */
#else
		if ((return_value = DialToneDetect()) != AD_OK) {	/* ﾀﾞｲｱﾙﾄｰﾝが検出できなかった時 */
#endif
			if (return_value == AD_NO_DIAL_TONE) {	/** ﾀｲﾑｵｰﾊﾞｰの時 */
#if (PRO_CLASS1 == ENABLE)
				if (CL1_ATD_DialType != 0x00) {
					return (return_value);	/** ﾀﾞｲｱﾙﾄｰﾝ検出結果をﾘﾀｰﾝ */
				}
#endif
#if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/10/24 */
				if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/* 加入回線 */
					if (!CHK_DialToneOrTimeupAvailable()) {	/** ﾀﾞｲｱﾙﾄｰﾝを検出しないと発呼しない設定になっている時 */
						return (return_value);				/** ﾀﾞｲｱﾙﾄｰﾝ検出結果をﾘﾀｰﾝ */
					}
				}
				else{												/* 警電回線 */
					if (!(SYS_MemorySwitch[MEMORY_SW_A1] & DIALTONE_OR_TIMEUP_EXT)) {	/** ﾀﾞｲｱﾙﾄｰﾝを検出しないと発呼しない設定になっている時 */
						return (return_value);				/** ﾀﾞｲｱﾙﾄｰﾝ検出結果をﾘﾀｰﾝ */
					}
				}
#else
				if (!CHK_DialToneOrTimeupAvailable()) {	/** ﾀﾞｲｱﾙﾄｰﾝを検出しないと発呼しない設定になっている時 */
					return (return_value);				/** ﾀﾞｲｱﾙﾄｰﾝ検出結果をﾘﾀｰﾝ */
				}
#endif
			}
			else {	/** ﾋﾞｼﾞｰﾄｰﾝ，ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝを検出、もしくはｽﾄｯﾌﾟｷｰが押された時 */
				return (return_value);	/** ﾀﾞｲｱﾙﾄｰﾝ検出結果をﾘﾀｰﾝ */
			}
		}
	}
	/*----------------------------*/
	/** ﾀﾞｲﾔﾙ前に現在の極性を獲得 */
	/*----------------------------*/
	if (CHK_UNI_DSE_Detect()) {		/* 個別Ａ０ */
		ATD_DSE1_Status = DSE1();
		ATD_DSE2_Status = DSE2();
	}
	/*---------------------------------*/
	/** ﾘﾀﾞｲｱﾙﾊﾞｯﾌｧにﾊﾞｯﾌｧの内容をｺﾋﾟｰ */
	/*---------------------------------*/
	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_POCKET_BELL)) {
#if (PRO_CLASS1 == ENABLE)
		/* CLASS1リモート送信の際、RedialBufferに残さない。("DBT"等の文字が残る為) By S.Fukui Mar.31,1998 */
		if ((Buffer[0] != 'D') && (Buffer[0] != '.')) {
			CMN_StringCopyNULL((UBYTE *)SYB_RedialBuffer, (UBYTE *)Buffer);
		}
#else
			CMN_StringCopyNULL((UBYTE *)SYB_RedialBuffer, (UBYTE *)Buffer);
#endif
#if defined(EC1)	/* ITA仕様 */
    	if(SYB_MachineParameter[0]==2){
			while(SYB_RedialBuffer[redial_check_pointer++] != NULL){
				if((SYB_RedialBuffer[redial_check_pointer - 1]=='-')
					&& (SYB_RedialBuffer[redial_check_pointer]=='!')){
					SYB_RedialBuffer[redial_check_pointer - 1]=NULL;
					break;
				}
			}
		}
#endif
	}

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
	if (CHK_UNI_FORVAL_LCR_Enable()) {
		i = 0;
		is_find = FALSE;

		if (CMN_StringCompare((Buffer + cnt), (CONST UBYTE*)"9999", 4) == STRCMP_EQUAL) {
			cnt += 4;
			is_find = TRUE;
		}

		while (ATD_PrefixTable[i].SrcDial[0] != '\0' && !is_find) {
			compare_pos = 0;
			match = 0;
			while (Buffer[cnt + compare_pos]) {
				if (CMN_isdigit(Buffer[cnt + compare_pos])	/* 数字 */
				 || (Buffer[cnt + compare_pos] == '#')		/* '＃' */
				 || (Buffer[cnt + compare_pos] == '*')) {	/* '＊' */
					if (ATD_PrefixTable[i].SrcDial[match] != Buffer[cnt + compare_pos]) { /* 一致しない */
						/* 一致しない場合はテーブルの次の番号と比較する */
						break;
					}
					match++;
					if (ATD_PrefixTable[i].SrcDial[match] == '\0') { /* 番号がすべて一致した */
						/* 市外局番を付加する */
						if (ATD_PrefixTable[i].IsAreaCode) {
							CMN_InsertString((Buffer + cnt), SYB_AreaCode, 0);
						}
						/* "00500"を付加する */
						CMN_InsertString((Buffer + cnt), ATD_PrefixTable[i].AddDial, 0);
						is_find = TRUE;
						break;
					}
				}

				compare_pos++;
			}
			i++;
		}
	}
#endif

	/*---------------------------*/
	/*ﾀﾞｲｱﾙ送出　＆　ﾀﾞｲｱﾗｰの処理*/
	/*---------------------------*/
	while ((dial_num = Buffer[cnt++]) != NULL) {	/** ﾊﾞｯﾌｧがNULLでない時 */

		if (SYS_FaxComStopSwitch()) {	/** ｽﾄｯﾌﾟｷｰが押された時 */
			return (AD_STOPPED);	/** AD_STOPPEDをﾘﾀｰﾝ */
		}
#if (PRO_CLASS1 == ENABLE)
		if ((CL1_ATD_DialType != 0x00) && CL1DialAbort) {
			return (AD_STOPPED);	/** AD_STOPPEDをﾘﾀｰﾝ */
		}
#endif
#if defined(FRA)
		/*-----------------------*/
		/*連続ﾎﾟｰｽﾞ判断ﾌﾗｸﾞの処理*/
		/*-----------------------*/
		is_continuous_pause = (UBYTE)(is_continuous_pause >> 1);
#endif
		/*-----------------------*/
		/* ﾊﾞｯﾌｧﾃﾞｰﾀに対する処理 */
		/*-----------------------*/
		switch (dial_num) {
		case	'-':
			break;
		case	'!':
			/*---------------------------*/
			/*ﾀﾞｲｱﾙﾊﾟﾙｽからDTMFに切り変え*/
			/*---------------------------*/
			if (pre_dial_num == '-') {
				SYS_DialChange = 1;
				ATD_RelayOff();		/**	ダイヤルトーン送出の為にリレーを戻す	*/
			}
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* add by HARADA '94.3.21 *//* by K.Watanabe 2004/10/12 */
			/*------------*/
			/*ﾏｰｷｭﾘｰｷｰ動作*/
			/*------------*/
			else if((cnt == 1)
					&& (SYB_MachineParameter[COUNTRY_CODE] == 0)){		/* DialBufferの先頭に！がある時 & country code = 0(GBR) */
				ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
				MercuryDial(DIAL_STATUS_AUTODIAL);
			}
#endif
			/*------------*/
			/*ﾀﾞｲｱﾙﾄｰﾝ検出*/
			/*------------*/
			else {
				if (Buffer[cnt] == NULL) {	/* 28.8用 */
					/* 一番最後の「！」は無視する 1996/12/25 Y.Murata */
				}
				else {
					ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
					ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
					if ((return_value = DialToneDetect(NOT_BEFORE_DIAL)) != AD_OK) {
#else
					if ((return_value = DialToneDetect()) != AD_OK) {
#endif
						return(return_value);
					}
					IsDialFirstNum = TRUE;	/**	ダイアル送出前にリレーを引く(OutPutDial()) */
				}
			}
			break;
		case	'/':
			/*---------*/
			/*ﾎﾟｰｽﾞ処理*/
			/*---------*/
			if (pre_dial_num == '-') {
#if defined(FRA)		/* FRAは、連続ポーズ不可　'95/03/02 by M.HARADA */
				if (is_continuous_pause) {
				/*-----------------------------*/
				/*連続でﾎﾟｰｽﾞ記号("-/")が来た時*/
				/*-----------------------------*/
				}
				/*-----------------------------*/
				/*単発でﾎﾟｰｽﾞ記号("-/")が来た時*/
				/*-----------------------------*/
				else {
					wai_tsk(CHK_PauseTime()*100 + 1 - 60);	/* close to 2.5sec */
				}
				/*---------------------------------------------------*/
				/* ﾎﾟｰｽﾞが連続で来ると 00000100 を右に2bitｼﾌﾄしても正*/
				/*---------------------------------------------------*/
				is_continuous_pause = 0x04;
#else
				wai_tsk(CHK_PauseTime()*100 + 1);	/*	CHK_PauseTime()がゼロの可能性があるので１を足している	*/
#endif
			}
			/*----------------*/
			/*第２ﾀﾞｲｱﾙﾄｰﾝ検出*/
			/*----------------*/
			else {
				ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
				ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/
				if ((return_value = Dial2ndToneDetect()) != AD_OK) {
					return(return_value);
				}
				IsDialFirstNum = TRUE;	/**	ダイアル送出前にリレーを引く */
			}
			break;
		case	'*':
		case	'#':
			/*--------------------------*/
			/*回線ﾀｲﾌﾟがDTMFの時だけ送出*/
			/*--------------------------*/
#if (PRO_CLASS1 == ENABLE)		/* 96.03.28 */
			if (((CL1_ATD_DialType == 0x00) && (CHK_DialType() & LINE_TYPE_TONE))
			 || (CL1_ATD_DialType == 'T')
			 || (SYS_DialChange)) {
				OutPutDial(dial_num);
			}
#else
 #if (PRO_LINENUMBER == TWICE_LINE)/* V851 DP設定の時に｢*、#｣が｢0、b｣と送出される。 By Y.Suzuki 2002/09/12 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
			else {/*拡張回線*/
				if ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
 #else
			if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
				OutPutDial(dial_num);
			}
 #endif
#endif

			break;

#if (PRO_CLASS1 == ENABLE)		/* 96.03.28 */
		case	'P':
			break;
		case	'T':
			/*---------------------------*/
			/*ﾀﾞｲｱﾙﾊﾟﾙｽからDTMFに切り変え*/
			/*---------------------------*/
			SYS_DialChange = 1;
			ATD_RelayOff();		/**	ダイヤルトーン送出の為にリレーを戻す	*/
			break;
		case	',':
			wai_tsk(S8*100+1);
			break;
		case	'W':
			/*----------------*/
			/*第２ﾀﾞｲｱﾙﾄｰﾝ検出*/
			/*----------------*/
			ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
			ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/
			if ((return_value = Dial2ndToneDetect()) != AD_OK) {
				return(return_value);
			}
			IsDialFirstNum = TRUE;	/**	ダイアル送出前にリレーを引く */
			break;
		case	';':
			ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
			ATD_RelayOff();
			return (AD_OK);
			break;
#endif

		default :
			if (('0' <= dial_num) && (dial_num <= '9')) {
				if(!OutPutDial(dial_num)) {
					ATD_BreakDTMF_Tx();	 /* H.Kubo 1997/11/06 */
					return(AD_NO_CURRENT_LOOP);
				}
			}
			else {		   /*ここに来たらバグ*/
				ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */
				return(AD_DESTROYED);
			}
			break;
		}
		/*Buffer[cnt]の値をｾｯﾄ*/
		pre_dial_num = dial_num;
	}

#if (PRO_PIN_ACCESS == ENABLE)		/* 95.12.26 by Y.Tanimoto */
	cnt = 0;
	while ((pin_dial_num = SYS_PinBuffer[cnt]) != NULL) {	/* ﾊﾞｯﾌｧがNULLでない時 */
		/*-------------*/
		/* PIN番号送出 */
		/*-------------*/
		if (('0' <= pin_dial_num) && (pin_dial_num <= '9')) {
			if(!OutPutDial(pin_dial_num)) {
				ATD_BreakDTMF_Tx();	 /* H.Kubo 1997/11/06 */
				return(AD_NO_CURRENT_LOOP);
			}
		}
		else if ((pin_dial_num == '*') || (pin_dial_num == '#')) {
 #if (PRO_LINENUMBER == TWICE_LINE)/* V851 DP設定の時に｢*、#｣が｢0、b｣と送出される。 By Y.Suzuki 2002/09/12 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
			else {/*拡張回線*/
				if ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
 #else
			if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
				OutPutDial(pin_dial_num);
			}
 #endif
		}
		else {
			/* その他の番号は送出しない */
		}
		cnt++;
	}
#endif

	ATD_BreakDTMF_Tx();	/* DTMF Close 1996/11/28 Y.M */ /* H.Kubo 1997/11/06 */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)/* 1998/04/15 Eguchi */

	if (SYS_INF_ExecuteIFAX == TRUE) { /*INTERNET FAX実行時*/

		/* ダイアル後のトーン検出は行わない */
		ATD_RelayOff();		/**	トーン検出の為にリレーを戻す	*/
		FCM_Is_ToneDetecting = NO;
		return (AD_OK);
	}

#endif /* 1998/04/18 Eguchi */

	/*--------------------------------------------------------*/
	/*ﾀﾞｲｱﾙ後ﾄｰﾝ検出  （BT,CT,CED,DIS,DSE,STOP検出 & CNG送出）*/
	/*--------------------------------------------------------*/
	ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Added by H.Kubo 1997/07/19 */
	/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */
	AfterToneCheckStartTimer = SYS_GeneralTimer;
#endif

	return_value = AfterDial_ToneDetect();

	FCM_Is_ToneDetecting = NO;
	return(return_value);
}

/*************************************************************************
	module		:[トーン検出ﾀｽｸID Initial]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[ATD]
	date		:[1994/03/07]
	author		:[奥村明]
*************************************************************************/
void	ToneDetectTaskInitial(void)
{
	UBYTE loop = 0;

	for (loop = 0; loop < CONTINUE_TONE_MAX; loop++) {
		tskno_filter1_off[loop] = 0xFFFF;
		tskno_filter2_off[loop] = 0xFFFF;
		tskno_filter3_off[loop] = 0xFFFF;
		tskno_tone_timeup[loop] = 0xFFFF;
	}
}
#if (PRO_MULTI_LINE == ENABLE)	/* PSTN Access Number  By O.Kimoto 1996/12/25 */
/*************************************************************************
	module		:[外線アクセス番号発呼処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[ATD]
	ProtoType	:[unsigned char near ATD_PstnAccessNumberDialling(void){}]
	date		:[1996/12/25]
	author		:[木元修]
*************************************************************************/
UBYTE ATD_PstnAccessNumberDialling(void)
{
	UBYTE dial_buffer[11];
	UBYTE dial_num;
	UBYTE count;
	UBYTE pre_dial_number;
	UBYTE is_continuous_pause;

	pre_dial_number = 0;
	is_continuous_pause = 0;

 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/4 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ライン通信中	*/
		CMN_BCD_ToASC_String(&dial_buffer[0],(UBYTE *)&SYB_PbxAccessNumber[0][0][0]);
	}
	else {
		CMN_BCD_ToASC_String(&dial_buffer[0],(UBYTE *)&SYB_PbxAccessNumber[0][1][0]);
	}
 #else
	CMN_BCD_ToASC_String(&dial_buffer[0],&SYB_PbxAccessNumber[0][0]);
 #endif
	count = 0;
	while ((dial_num = dial_buffer[count++]) != NULL) {	/** ﾊﾞｯﾌｧがNULLでない時 */

		if (SYS_FaxComStopSwitch()) {	/** ｽﾄｯﾌﾟｷｰが押された時 */
			return (AD_STOPPED);	/** AD_STOPPEDをﾘﾀｰﾝ */
		}
		/*-----------------------*/
		/*連続ﾎﾟｰｽﾞ判断ﾌﾗｸﾞの処理*/
		/*-----------------------*/
		is_continuous_pause = (unsigned char)(is_continuous_pause >> 1);

		/*-----------------------*/
		/* ﾊﾞｯﾌｧﾃﾞｰﾀに対する処理 */
		/*-----------------------*/
		switch (dial_num) {
		case	'-':
			break;
		case	'*':
		case	'#':
			/*--------------------------*/
			/*回線ﾀｲﾌﾟがDTMFの時だけ送出*/
			/*--------------------------*/
 #if (PRO_LINENUMBER == TWICE_LINE)/* V851 DP設定の時に｢*、#｣が｢0、b｣と送出される。 By Y.Suzuki 2002/09/12 */
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
			else {/*拡張回線*/
				if ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange) {
					OutPutDial(dial_num);
				}
			}
 #else
			if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {

				OutPutDial(dial_num);
			}
 #endif
			break;
		case	'/':
			/*---------*/
			/*ﾎﾟｰｽﾞ処理*/
			/*---------*/
			if (pre_dial_number == '-') {
				/*-----------------------------*/
				/*連続でﾎﾟｰｽﾞ記号("-/")が来た時*/
				/*-----------------------------*/
				if (is_continuous_pause) {
 #if defined(FRA)		/* FRAは、連続ポーズ不可　'95/03/02 by M.HARADA */
 #else
					wai_tsk(CHK_PauseTime()*100 + 1);	/*	CHK_PauseTime()がゼロの可能性があるので１を足している	*/
 #endif
				}
				/*-----------------------------*/
				/*単発でﾎﾟｰｽﾞ記号("-/")が来た時*/
				/*-----------------------------*/
				else {
					wai_tsk(CHK_PauseTime()*100 + 1);
 #if defined(FRA)
					if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
						wai_tsk(88);			/* 95/05/05 by M.HARADA  DTMF時のPause時間を3秒に合わせるため */
					}
 #endif
				}
				/*---------------------------------------------------*/
				/* ﾎﾟｰｽﾞが連続で来ると 00000100 を右に2bitｼﾌﾄしても正*/
				/*---------------------------------------------------*/
				is_continuous_pause = 0x04;
			}
			else {
				/* '/' が単体で入っている時は無視 */
			}
			break;
		default :
			if (('0' <= dial_num) && (dial_num <= '9')) {
				if(!OutPutDial(dial_num)) {
					return(AD_NO_CURRENT_LOOP);
				}
			}
			else {		   /*ここに来たらバグ*/
				return(AD_DESTROYED);
			}
			break;
		}
		pre_dial_number = dial_num;
	}
	return(AD_OK);
}

#endif

/*************************************************************************
	module		:[DTMF送出の最後の処理]
	function	:[
	]
	return		:[]
	common		:[
			SYS_DialChange
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300,SHC]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン),SHC]
	keyword		:[ATD]
	date		:[1996/11/29]
	author		:[村田]
*************************************************************************/
void ATD_BreakDTMF_Tx(void)
{
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Ported from CLOVER by H.Kubo 1997/11/06 */
	/* 1996/11/29 Y.Murata
	 * DTMF設定で自動ダイアルを行う場合、１桁ずつDTMFを出し
	 * そのたびに、DTMF Open と Close をするとコンフィグに時間がかかり
	 * メイク、ブレーク時間が正しくでない
	 * Closeは全部のダイアルを発呼してから行うようにする
	 * Openは、DTMFモードでなかったらOpenするようにする
	*/
 #if (PRO_LINENUMBER == TWICE_LINE)/* V851 DP設定の時に｢*、#｣が｢0、b｣と送出される。 By Y.Suzuki 2002/09/12 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
		if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
			MDM_BreakDTMF_Tx();
		}
	}
	else {/*拡張回線*/
		if ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange) {
			MDM_BreakDTMF_Tx();
		}
	}
 #else
	if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
		MDM_BreakDTMF_Tx();
	}
 #endif
#endif /* (PRO_MODEM == R288F) */
}

