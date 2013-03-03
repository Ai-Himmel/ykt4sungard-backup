/* Copy 1997/1/6 T.Nose */
/* Original File : jun\usr1:\src\rice\src\idp_di.c */
/*----------------------------------------------------------------------*/
/* プロジェクト : SATSUKI/LAVENDER                                      */
/* ファイル名   : IDP_DI.C                                              */
/* モジュール名 : void DIPP_Reset(void)                                 */
/*              : void DIPP_InitialSet(void)                            */
/*              : void DIPP_ChangeDocumentSize(void)                    */
/*              : void DIPP_ShadingExecute(void)                        */
/*              : void DIPP_ReadShadingRAM(void)                       */
/*              : void DIPP_WriteShadingRAM(void)                      */
/*              : void DIPP_ClearShadingData(void)                      */
/*              : void DIPP_SetBitDIPPINTE(unsigned char)               */
/*              : void DIPP_SetBitDIPPST(unsigned char)                 */
/*              : void DIPP_SetBitWCOM(unsigned char)                   */
/*              : void DIPP_SetBitMPUAE(unsigned char)                  */
/*              : void DIPP_SetBitPEAKE(unsigned char)                  */
/*              : void DIPP_SetBitAJMD(unsigned char)                   */
/*              : void DIPP_AutoIncrementNegate(unsigned char)          */
/* 作成者名     : 宮崎                                                  */
/* 日  付       : 93.11.27                                              */
/* 概  要       : IDP301(DIPP-AS)ドライバー サブルーチン                */
/* 修正履歴     : IDP_DI   C       19861 01-24-94   18:17               */
/*              : Update on Jun,08,1994 TimeStamp = 06-06-94 15:44      */
/*              : Update on Jul,06,1994 TimeStamp = 07-06-94 10:11      */
/*              : Update on Jul,08,1994 TimeStamp = 07-08-94 11:46      */
/*              : Update on Jul,21,1994 画質調整用処理追加（Debug）     */
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mnt_pro.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysscan.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"

#include "\src\atlanta\define\idp301.h"
#include "\src\atlanta\define\idp_pro.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\ext_v\idp_tbl.h"
#include "\src\atlanta\ext_v\idp_data.h"

#include "\src\atlanta\ext_v\scn_data.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mnt_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#include "\src\atlanta\sh7043\define\sh_sys.h"
extern CONST UBYTE CHEKER_InitialRAM[SYS_INITIAL_MAX];
extern CONST UBYTE CHEKER_ShadingRAM[SYS_SHADING_MAX];

/*************************************************************************
	module		:[DIPP-AS ソフトリセット]
	function	:[
		1.DIPP-ASをソフトリセットします。
		2.DIPP-ASをリセット解除します。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[
		1.DIPP_AS内のシェーディングRAMと中間初期値RAMはクリアされません。
		2.リセットレジスタbit3は0にして下さい。
		3."SCN_MAIN.C"の'SCN_Close()'からコールされます。
		4."本ファイル"の'DIPP_ShadingExecute()'からコールされます。
		5."本ファイル"の'DIPP_InitialSet()'と対で使用します。
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_Reset(void)
{
	IdpRegisterStatus.IDP_RESET = IDP_RESET_DIPP;  /* リセット:"H"を800ns保障するために2回ライトします */
	IdpOutputByte(IDP_RESET_PORT,IdpRegisterStatus.IDP_RESET);
	IdpOutputByte(IDP_RESET_PORT,IdpRegisterStatus.IDP_RESET);
	IdpRegisterStatus.IDP_RESET = 0x00;            /* リセット解除 */
	IdpOutputByte(IDP_RESET_PORT,IdpRegisterStatus.IDP_RESET);
}

/*************************************************************************
	module		:[DIPP-AS 初期設定]]
	function	:[
		1.DIPP-ASの初期設定を行います。
		2.DIPP-ASの初期値RAM,及びシェーディングRAMをクリアします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[
		1."SCN_MAIN.C"の'SCN_Open()'からのみコールされます。
		2."本ファイル"の'DIPP_Reset()'と対で使用します。

	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_InitialSet(void)
{
	UBYTE i;

	DIPP_Reset();

	for (i = 0; i < DIPP_REGISTER_SIZE; i++) {  /** DIPP Reg Rom to Ram */
		/* ICHOUのCCDはNEC/A3固定なので、テーブルを縮小  1996/05/21 s.takeuchi */
		/* DIPP_RegTable[i] = DIPP_RegRomTable[CCD_Maker][CCD_Size-1][i]; */
		DIPP_RegTable[i] = DIPP_RegRomTable[i];
	}

#if defined(ANZU_L)
	if (IO__PFDR & IO_BIT_DSW0) {
		DIPP_RegTable[2] = (DIPP_RegRomTable[2] | DIPP_CR_R02_CTSEL);
	}
#endif

	/*---------------------------------------------------*/
	/** ピーク値リミットＲ０Ｆを再設定します             */
	/*---------------------------------------------------*/
	/*	※注意
	**	ICHOU(KIRI系)ではSCN_Open()で機器パラメータにある読み取りモード別
	**	の設定値を再セットするので、ここでセットする値は無視される
	**	DIPP_RegTable[0x0f] = SYS_MachineParameter[11];
	**	サイズ検知の時に使う値はDIPP_RegRomTableの値を使う  1996/11/22
	*/

	DIPP_AutoIncrementNegate();	/* 1996/09/25 */

	for (i = 0; i < 0x0d; i++) {  /** DIPPコントロールレジスタ設定 */

		/* 1996/09/25 */
		IdpRegisterStatus.DIPP_AR = i;
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

		IdpRegisterStatus.DIPP_CR = DIPP_RegTable[i];
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	/*---------------------------------------------------------------------------*/
	/** アドレスをインクリメントする為に、ピーク値レジスタをダミーで読みだします */
	/*---------------------------------------------------------------------------*/
	DIPP_RegTable[0x0d] = IdpInputByte(DIPP_CR_PORT);;

	/*-------------------------------*/
	/** DIPPのレジスタ設定を行います */
	/*-------------------------------*/
	for (i = 0x0e; i < DIPP_REGISTER_SIZE; i++) {

		/* 1996/09/25 */
		IdpRegisterStatus.DIPP_AR = i;
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

		IdpRegisterStatus.DIPP_CR = DIPP_RegTable[i];
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	DIPP_AutoIncrementNegate();  /** DIPP オートインクリメントネゲート */

	DIPP_ClearShadingData();     /** DIPP シェーディングデータクリア */
}

/*************************************************************************
	module		:[DIPP-AS 原稿サイズ(A4/B4)パラメータ再設定]
	function	:[
		1.原稿サイズ(A4/B4)よりDIPP-ASのIWIN,PAPWの再設定を行います。
		 .(1度は,"本ファイル"の'DIPP_InitialSet()'で原稿サイズB4で
         .設定されます。)
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		1996/05/21 s.takeuchi
			FBS読取り用の設定を追加
	]
	condition	:[
		1."SCN_MAIN.C"の'SCN_Open()'からのみコールされます。
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_ChangeDocumentSize(void)
{
	UBYTE	*ptr;
	UWORD	iwst;
	BYTE	offset;	/* FBS読み取り位置調整用 */
	UBYTE	i;

#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode == SCN_ADF) {
#endif
		ptr = &DIPP_RegScnSize[SCN_Control.DocumentSize][SYS_DocumentWidthFullFlag][0];

		SCN_FullWidthScan = 1;
		if (CHK_DocumentWidthFull()) { /**	読み取り左右白マスク無し */
			SCN_WhiteMaskFlag = 0;
		}
		else { /** 白マスク有り */
			SCN_WhiteMaskFlag = 1;
		}

		/* 機器パラの設定値で読み取り開始画素(IWST)を補正する */
#if (PRO_DOC_IN == ENABLE)
		offset = (BYTE)(SYB_MachineParameter[6] & 0x7F);
		if (SYB_MachineParameter[6] & 0x80) {
			offset *= -1;
		}
#else
		offset = (BYTE)(SYB_MachineParameter[12] & 0x7F);	/* 17 -> 12 By M.Tachibana 1997/11/28 */
		if (SYB_MachineParameter[12] & 0x80) {
			offset *= -1;
		}
#endif

#if (PRO_FBS == ENABLE)
	}
	else {	/* ICHOUのFBS読取りの場合は、FBS用のDIPPの設定を指定する */
		if (SYS_ScanDocSizeTable[SCN_RegularDocumentSize].IsFullScan) {	/* レター/リーガルなど */
			SCN_FullWidthScan = 1;
			SCN_WhiteMaskFlag = 0;
		}
		else {	/* その他の原稿 */
			SCN_FullWidthScan = 0;
			SCN_WhiteMaskFlag = 1;	/* ずらして読むため必ずマスクする */
		}
		ptr = &DIPP_FBS_RegScnSize[SCN_Control.DocumentSize][SCN_FullWidthScan][0];

		/* 機器パラの設定値で読み取り開始画素(IWST)を補正する */
		offset = (BYTE)(SYB_MachineParameter[13] & 0x7F);	/* 18 -> 13 By M.Tachibana 1997/11/28 */
		if (SYB_MachineParameter[13] & 0x80) {
			offset *= -1;
		}
	}
#endif

	/* 一旦、ROMテーブルからRAMにコピーする */
	for (i=DIPP_CR_R05_ADR; i<=DIPP_CR_R0C_ADR; i++) {
		DIPP_RegTable[i] = *ptr++;
	}

	iwst = (UWORD)(DIPP_RegTable[DIPP_CR_R07_ADR] & 0x0F);
	iwst <<= 8;
	iwst += (UWORD)DIPP_RegTable[DIPP_CR_R08_ADR];
	iwst += offset;
	DIPP_RegTable[DIPP_CR_R07_ADR] = (UBYTE)((iwst / 0x0100) | 0xF0);
	DIPP_RegTable[DIPP_CR_R08_ADR] = (UBYTE)(iwst & 0x00FF);

	for (i=DIPP_CR_R05_ADR; i<=DIPP_CR_R0C_ADR; i++) {
		/* DIPP_RegTable[i] = *ptr++; */
		IdpRegisterStatus.DIPP_AR = i;
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
		IdpRegisterStatus.DIPP_CR = DIPP_RegTable[i];
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}
}

/*************************************************************************
	module		:[DIPP-AS シェーディング実行]
	function	:[
		1.シェーディングを行い,シェーディングデータをDIPP-ASのシェーディン
		 .グRAMよりバックアップRAMにコピーします。
		2.Ｖ５３チームは、ランプエラーをチェックします

	]
	return		:[
		OK	1:	ランプエラー無し、シェーディングＯＫ
		NG	0:	ランプエラー
	]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
UBYTE DIPP_ShadingExecute(void)
{
	UBYTE tmpreg;

	DIPP_InitialSet();  /** DIPP-AS初期設定 */

	DIPP_SetBitDIPPST(IDP_BIT_ON);  /** DIPP-AS読み取り開始 */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();                       /** ランプオン */

	/** WCOM ONまでSYS_MachineParameter[80](I0)*10 mS(CCD Spec. = 300ms)待ちます */
	wai_tsk(SYB_MaintenanceSwitch[MNT_SW_C4] * 10);

	DIPP_SetBitPEAKE(IDP_BIT_ON);   /** ピーク値検出回路を動作 */
	wai_tsk(2);                         /** WCOM ONまで10mS（2ライン分）待ちます */

	/** DIPP-ASのステータスレジスタをリード */
	if((IdpInputByte(DIPP_SR_PORT)&DIPP_SR_FLEXG) == DIPP_SR_FLEXG) {
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);  /** DIPP-AS読み取り終了 */
		return(NG);
	}
	else {

#if (0)	/* ICHOU薄読み対策(PEAKE-OFFの後リードする)  1997/04/01 s.takeuchi */
		/*-------------------------*/
		/** ピーク値をセーブします */
		/*-------------------------*/
		IdpRegisterStatus.DIPP_AR = 0x0d;
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

		SYB_PeakData = IdpInputByte(DIPP_CR_PORT);
#endif

		DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_AUTO);	/** 自動初期値モード */

		DIPP_SetBitWCOM(IDP_BIT_ON);             /** DIPP-ASをシェーディング波形検出期間に移行    */

		while ((IdpInputByte(DIPP_SR_PORT) & DIPP_SR_WBSY) == DIPP_SR_WBSY) {  /** 検出が終了するまでループ */
			wai_tsk(1);
		}

		tmpreg = IdpInputByte(DIPP_SR_PORT);              /** DIPP-ASのステータスレジスタをリード */

		DIPP_SetBitWCOM(IDP_BIT_OFF);  /** DIPPを読み取り期間に移行 */

		/* ICHOU薄読み対策(PEAKE-OFFが抜けていた) */
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */

		DIPP_ReadPeakData();	/** ピーク値を保存する */

		/*------------------------------------------------*/
		/** DIPPを読み取り終了させます(DIPPSTをOFFします) */
		/*------------------------------------------------*/
		DIPP_SetBitDIPPST(IDP_BIT_OFF);

		/* DIPP_ReadInitialRAM( idp_no );	@** 初期値ＲＡＭをセーブします */ /* ICHOU薄読み対策  1997/04/25 */
		DIPP_ReadInitialRAM( &SYB_InitialRAM[0] );	/** 初期値ＲＡＭをセーブします */
		DIPP_ReadShadingRAM( &SYB_ShadingRAM[0] );	/** DIPP-ASのシェーディングRAMｰ>バックアップRAM */

		DIPP_Reset();             /** DIPP-ASソフトリセット */

		return(OK);
	}
}

#if (0) /* 薄読み対策 */
/*************************************************************************
	module		:[DIPP-AS 初期値ＲＡＭ読込み]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/06/22]
	author		:[宮崎]
*************************************************************************/
void DIPP_ReadInitialRAM(void)
{
	UBYTE i;

	/*---------------------------*/
	/* 初期値RAMをリセットします */
	/*---------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x1a;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/*--------------------------------------------*/
	/** DIPP オートインクリメントをネゲートします */
	/*--------------------------------------------*/
	DIPP_AutoIncrementNegate();

	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*----------------------------------------------*/
	/** 変化点モード指定をCPU書き込みモードとします */
	/*----------------------------------------------*/
	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);

	/*----------------------------------------*/
	/** MPUアクセスイネーブルビットをONします */
	/*----------------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_ON);

	/*--------------------------------*/
	/** 初期値RAMアドレスを選択します */
	/*--------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/* 左端が薄くなるので削除(初期値RAMが1バイトずれてしまう)  1996/11/28
	@*------------------------------------*@
	@** R19レジスタに初期値をライトします *@
	@*------------------------------------*@
	*	SYS_InitialRAM[0] = IdpInputByte(DIPP_CR_PORT);
	*/

	/*---------------------------------------------*/
	/** 192バイト分の初期値RAMデータを読み出します */
	/*---------------------------------------------*/
	/*  この部分はバグですが、ＱＡＴが始まりますの */
	/*  このまま進みます。将来的には修正する。　　 */
	/*  Dec.2,1994 By S.K                          */
	/*---------------------------------------------*/
	for (i = 0; i < SYS_INITIAL_MAX; i++) { /* Dec.2,1994 By S.K */
		SYB_InitialRAM[i] = IdpInputByte(DIPP_CR_PORT);
	}

	/*----------------------------------------*/
	/** MPUアクセスイネーブルビットをOFFします */
	/*----------------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_OFF);
}
#endif

/*************************************************************************
	module		:[DIPP初期値RAMの読み出し]
	function	:[
		1.	MPUAE ON
		2.	変化点モード(AJMD)をCPU Writeモード
		3.	初期値RAMアドレスをリセット
		4.	初期値/変化点データ(R19)とアドレス(R1A,R1B)を
		.	64回(192byte分)読み出す
		5.	MPUAE OFF
	]
	return		:[]
	common		:[]
	condition	:[
		引数で読み出す変数のポインタを指定する
	]
	comment		:[
		ICHOU薄読み対策  1997/04/25
		日立からの指示で初期値RAMの処理手順を変更
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[IDP]
	date		:[1997/04/25]
	author		:[竹内茂樹]
*************************************************************************/
void DIPP_ReadInitialRAM(
	UBYTE	*dst)
{
	UBYTE	i;

	DIPP_SetBitMPUAE( IDP_BIT_ON );				/** MPUAE ON */
	DIPP_SetBitAJMD( DIPP_CR_R04_AJMD_CPUW );	/** 変化点はCPU Writeモード */

	/** 初期値RAMアドレスをリセット */
	IdpRegisterStatus.DIPP_AR = 0x1A;
	IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );

	for (i = 0; i < (SYS_INITIAL_MAX / 3); i++) {	/** 初期値/変化点を64データ分ループ */
		/** R19 read */
		IdpRegisterStatus.DIPP_AR = 0x19;
		IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
		*dst++ = IdpInputByte( DIPP_CR_PORT );

		/** R1A read */
		IdpRegisterStatus.DIPP_AR = 0x1A;
		IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
		*dst++ = IdpInputByte( DIPP_CR_PORT );

		/** R1B read */
		IdpRegisterStatus.DIPP_AR = 0x1B;
		IdpOutputByte( DIPP_AR_PORT, IdpRegisterStatus.DIPP_AR );
		*dst++ = IdpInputByte( DIPP_CR_PORT );
	}

	DIPP_SetBitMPUAE( IDP_BIT_OFF );			/** MPUAE OFF */
}


/*************************************************************************
	module		:[DIPP-AS シェーディングデータ読込み]
	function	:[
		1.DIPP-ASのシェーディングRAMを読込み,SYS_ShadingRAM[]にコピー
		 .します。
		2.DIPP-ASの初期値RAMを読込み,SYS_InitialRAM[]にコピーします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		コピー先をポインタ引数に変更  1996/07/25 s.takeuchi
	]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_ReadShadingRAM(UBYTE	*dst)
{
	UBYTE i;

	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);  /** 変化点モード指定をCPU書き込みモードとします */

	DIPP_SetBitMPUAE(IDP_BIT_ON);            /** 内蔵RAMの書き込みを可能とします */

	DIPP_AutoIncrementNegate();  /** DIPP オートインクリメントネゲート */

	/*--------------------------------------------*/
	/** シェーディングRAMアドレスをリセットします */
	/*--------------------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x00;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*------------------------------------------*/
	/** シェーディングRAMアドレスをセットします */
	/*------------------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x1d;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	for (i = 0; i < SYS_SHADING_MAX; i++) {/** 224バイト分のシェーディングデータを読み込みます */
		/* コピー先をポインタに変更  1996/07/25 s.takeuchi
		**	SYS_ShadingRAM[i] = IdpInputByte(DIPP_CR_PORT);
		*/
		*dst++ = IdpInputByte( DIPP_CR_PORT );
	}

	/*--------------------------------------------*/
	/** シェーディングRAMアドレスをリセットします */
	/*--------------------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x00;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	DIPP_SetBitMPUAE(IDP_BIT_OFF);   /** 内蔵RAMの書き込みを不可能とします */
}

/*************************************************************************
	module		:[DIPP-AS 初期値データアドレス指定モードで書込み]
	function	:[
		1. アドレス指定モードで指定されたアドレスを３２画素単位に増加させ初期値RAMに書込む
		2. データ数は127byte固定(1+63*2)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		書込むアドレスデータを引数で初期値を指定する  1996/05/10 s.takeuchi
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[IDP]
	date		:[1996/05/10]
	author		:[竹内茂樹]
*************************************************************************/
void DIPP_WriteInitialAddressRAM(UWORD	address)
{
	UBYTE i;

	/*---------------------------*/
	/* 初期値RAMをリセットします */
	/*---------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x1a;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/*--------------------------------------------*/
	/** DIPP オートインクリメントをネゲートします */
	/*--------------------------------------------*/
	DIPP_AutoIncrementNegate();

	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*-----------------------------------------------*/
	/** 変化点モード指定をアドレス指定モードとします */
	/*-----------------------------------------------*/
	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_ADDR);

	/*----------------------------------*/
	/** 内蔵RAMの書き込みを可能とします */
	/*----------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_ON);

	/*----------------------------------*/
	/** 初期値RAMアドレスをセットします */
	/*----------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*------------------------------------*/
	/** R19レジスタに初期値をライトします */
	/*------------------------------------*/
	/* 引数指定に変更 idp_reg_ptr->DIPP_CR = DIPP_AddressApplyTable[0]; */
	IdpRegisterStatus.DIPP_CR = 0xd0;	/* 暫定で直値指定  1996/05/15 s.takeuchi */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/*---------------------------------------------*/
	/** 126バイト分の初期値RAMデータを書き込みます */
	/*---------------------------------------------*/
	for (i = 1; i < 127; i++) {
		/* 引数指定に変更 idp_reg_ptr->DIPP_CR = DIPP_AddressApplyTable[i]; */
		/* 指定アドレスから３２画素単位に増加させるように変更(アドレス指定モードなので＋１を設定) */
		IdpRegisterStatus.DIPP_CR = (UBYTE)(address + (((i - 1) * 32) + 1));
		address++;
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	/*------------------------------------*/
	/** 内蔵RAMの書き込みを不可能とします */
	/*------------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_OFF);
}

#if (0)	/* ICHOU薄読み対策 */
/*************************************************************************
	module		:[DIPP-AS 初期値データ書込み]
	function	:[
		1.DIPP-ASの初期値RAMに読込み,SYS_InitialRAM[]の内容をコピーします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_WriteInitialRAM(void)
{
	UBYTE i;

	/*---------------------------*/
	/* 初期値RAMをリセットします */
	/*---------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x1a;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/*--------------------------------------------*/
	/** DIPP オートインクリメントをネゲートします */
	/*--------------------------------------------*/
	DIPP_AutoIncrementNegate();

	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*----------------------------------------------*/
	/** 変化点モード指定をCPU書き込みモードとします */
	/*----------------------------------------------*/
	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);

	/*----------------------------------*/
	/** 内蔵RAMの書き込みを可能とします */
	/*----------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_ON);

	/*----------------------------------*/
	/** 初期値RAMアドレスをセットします */
	/*----------------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	/*------------------------------------*/
	/** R19レジスタに初期値をライトします */
	/*------------------------------------*/
	IdpRegisterStatus.DIPP_CR = SYB_InitialRAM[0];
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/*---------------------------------------------*/
	/** 192バイト分の初期値RAMデータを書き込みます */
	/*---------------------------------------------*/
	for (i = 1; i < SYS_INITIAL_MAX; i++) {
		IdpRegisterStatus.DIPP_CR = SYB_InitialRAM[i];
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	/*------------------------------------*/
	/** 内蔵RAMの書き込みを不可能とします */
	/*------------------------------------*/
	DIPP_SetBitMPUAE(IDP_BIT_OFF);
}
#endif

/*************************************************************************
	module		:[DIPP初期値RAMを書き込み]
	function	:[
		1.	MPUAE ON
		2.	変化点モード(AJMD)をCPU Writeモード
		3.	初期値RAMアドレスをリセット
		4.	ARを19Hにセットして192byte分書き込む
		.	(DIPP内部でR19,R1A,R1Bが繰り返される)
		5.	MPUAE OFF
	]
	return		:[]
	common		:[]
	condition	:[
		引数で読み出す変数のポインタを指定する
	]
	comment		:[
		ICHOU薄読み対策  1997/04/25
		日立からの指示で初期値RAMの処理手順を変更
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[IDP]
	date		:[1997/04/25]
	author		:[竹内茂樹]
*************************************************************************/
void DIPP_WriteInitialRAM(void)
{
	UBYTE	i;

	DIPP_SetBitMPUAE( IDP_BIT_ON );				/** MPUAE ON */
	DIPP_SetBitAJMD( DIPP_CR_R04_AJMD_CPUW );	/** 変化点はCPU Writeモード */

	/** 初期値RAMアドレスをリセット */
	IdpRegisterStatus.DIPP_AR = 0x1A;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/** 初期値RAMアドレス(R19)をセット */
	IdpRegisterStatus.DIPP_AR = 0x19;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	for (i = 0; i < SYS_INITIAL_MAX; i++) {	/** 初期値/変化点を(64x3)データ分ループ */
		/** 初期値RAM(DIPP内部でR19,R1A,R1Bが繰り返される)を書き込み */
		IdpRegisterStatus.DIPP_CR = CHEKER_InitialRAM[i];
		IdpOutputByte( DIPP_CR_PORT, IdpRegisterStatus.DIPP_CR );
	}

	DIPP_SetBitMPUAE( IDP_BIT_OFF );			/** MPUAE OFF */
}


/*************************************************************************
	module		:[DIPP-AS シェーディングデータ書込み]
	function	:[
		1.DIPP-ASのシェーディングRAMに,SYS_ShadingRAM[]の内容をコピーします。
		2.DIPP-ASの初期値RAMに読込み,SYS_InitialRAM[]の内容をコピーします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_WriteShadingRAM(void)
{
	UBYTE i;

	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);	/** 変化点モード指定をCPU書き込みモードとします */

	DIPP_SetBitMPUAE(IDP_BIT_ON);           /** 内蔵RAMの書き込みを可能とします */

	DIPP_AutoIncrementNegate();             /** DIPP オートインクリメントネゲート */

	IdpRegisterStatus.DIPP_AR = 0x00;  /** シェーディングRAMアドレス リセット */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	IdpRegisterStatus.DIPP_AR = 0x1d;  /** シェーディングRAMアドレス セット	 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	for (i=0; i<SYS_SHADING_MAX; i++) {
		IdpRegisterStatus.DIPP_CR = CHEKER_ShadingRAM[i];
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	IdpRegisterStatus.DIPP_AR = 0x00;  /** シェーディングRAMアドレス リセット */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	DIPP_SetBitMPUAE(IDP_BIT_OFF);   /** 内蔵RAMの書き込みを不可能とします */
}

/*************************************************************************
	module		:[DIPP-AS シェーディングデータクリア]
	function	:[
		1.DIPP-ASのシェーディングRAMをを'0'クリアします。
		2.DIPP-ASの初期値RAMをを'0'クリアします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_ClearShadingData(void)
{
	UBYTE i;

	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);  /** 変化点モード指定をCPU書き込みモードとします */

	DIPP_SetBitMPUAE(IDP_BIT_ON);            /** 内蔵RAMの書き込みを可能とします */

	DIPP_AutoIncrementNegate();  /** DIPP オートインクリメントネゲート *

	/*---------------------------*/
	/* 初期値RAMをリセットします */
	/*---------------------------*/
	IdpRegisterStatus.DIPP_AR = 0x1a;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = 0x00;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	IdpRegisterStatus.DIPP_AR = 0x19;  /** 初期値RAMアドレス セット */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	for (i = 0; i < SYS_INITIAL_MAX; i++) {/** 192バイト分の0x00のデータを書き込みます */
		IdpRegisterStatus.DIPP_CR = 0x00;
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	DIPP_AutoIncrementNegate();  /** DIPP オートインクリメントネゲート */

	IdpRegisterStatus.DIPP_AR = 0x00;  /** シェーディングRAMアドレス リセット */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	IdpRegisterStatus.DIPP_AR = 0x1d;  /** シェーディングRAMアドレス セット   */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	for (i = 0; i < SYS_SHADING_MAX; i++) {  /** 224バイト分の0x00のデータを書き込みます */
		IdpRegisterStatus.DIPP_CR = 0x00;
		IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
	}

	IdpRegisterStatus.DIPP_AR = 0x00;  /** シェーディングRAMアドレス リセット */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	DIPP_SetBitMPUAE(IDP_BIT_OFF);   /** 内蔵RAMの書き込みを不可能とします */
}

/*************************************************************************
	module		:[DIPP-AS 割込み許可ビット設定]
	function	:[
		1.引数(setbit)により、ビットのON/OFFを行います。
		 .setbit  : IDP_BIT_ON(1)   割込み許可
		 .        : IDP_BIT_OFF(0)  割込み禁止

	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitDIPPINTE( UBYTE setbit )  /** ビットON/OFF指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x00;    /** R00:コントロールレジスタ(0)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R00:コントロールレジスタ(0)リード */

	if (setbit==IDP_BIT_ON)
		tmpreg |= DIPP_CR_R00_INTE;
	else
		tmpreg &= ~DIPP_CR_R00_INTE;

	IdpRegisterStatus.DIPP_AR = 0x00;           /** R00:コントロールレジスタ(0)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = (UBYTE)(tmpreg | 0x80);  /** R00:コントロールレジスタ(0)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS スタートビット設定]
	function	:[
		1.引数(setbit)により、ビットのON/OFFを行います。
		 .setbit  : IDP_BIT_ON(1)   読み取りスタート
		 .        : IDP_BIT_OFF(0)  読み取りストップ

	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitDIPPST(UBYTE setbit)  /** ビットON/OFF指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x00;    /** R00:コントロールレジスタ(1)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R00:コントロールレジスタ(1)リード */

	if (setbit==IDP_BIT_ON)
		tmpreg |= DIPP_CR_R00_DIPPST;   /** DIPP-ASスタートビット ON */
	else
		tmpreg &= ~DIPP_CR_R00_DIPPST;  /** DIPP-ASスタートビット OFF */

	IdpRegisterStatus.DIPP_AR = 0x00;           /** R00:コントロールレジスタ(1)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = (UBYTE)(tmpreg | 0x80);  /** R00:コントロールレジスタ(1)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS ライトコマンドビット設定]
	function	:[
		1.引数(setbit)により、ビットのON/OFFを行います。
		 .setbit : IDP_BIT_ON(1)   読み取り期間に移行
		 .       : IDP_BIT_OFF(0)  シェーディング波形検出期間に移行

	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[
		1.割り込み発行後もWCOMビットが"1"のままだと,割り込みが発生しません。
		2.割り込み発行前にWCOMビットを"0"にするとDIPPは割り込みを発行しません。
		 .この場合は,SR(ステータスレジスタ)のWBSYビットをモニタし,
		 .シェーディング波形の検出が終了したことを確かめてからDIPPの
		 .TSCAN入力を"High"レベルにする必要があります。
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitWCOM(UBYTE setbit)  /** ビットON/OFF指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x00;    /** R00:コントロールレジスタ(1)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R00:コントロールレジスタ(1)リード */

	if (setbit==IDP_BIT_ON)
		tmpreg |= DIPP_CR_R00_WCOM;   /** ライトコマンドビット ON */
	else
		tmpreg &= ~DIPP_CR_R00_WCOM;  /** ライトコマンドビット OFF */

	IdpRegisterStatus.DIPP_AR = 0x00;           /* R00:コントロールレジスタ(1)選択   */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = (UBYTE)(tmpreg | 0x80);  /* R00:コントロールレジスタ(1)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS MPUアクセスイネーブルビット設定]
	function	:[
		1.引数(setbit)により、ビットのON/OFFを行います。
		 .setbit : IDP_BIT_ON(1)   MPUがDIPP-ASの初期値RAMをアクセス可
		 .       : IDP_BIT_OFF(0)  MPUアクセス不可

	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitMPUAE(UBYTE setbit)  /** ビットON/OFF指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x00;    /** R00:コントロールレジスタ(1)選択   */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R00:コントロールレジスタ(1)リード */

	if (setbit==IDP_BIT_ON)
		tmpreg |= DIPP_CR_R00_MPUAE;   /** MPUアクセスイネーブルビット ON */
	else
		tmpreg &= ~DIPP_CR_R00_MPUAE;  /** MPUアクセスイネーブルビット OFF */

	IdpRegisterStatus.DIPP_AR = 0x00;           /** R00:コントロールレジスタ(1)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = (UBYTE)(tmpreg | 0x80);  /** R00:コントロールレジスタ(1)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS ピーク値検出イネーブルビット設定]
	function	:[
		1.引数(setbit)により、ビットのON/OFFを行います。
		 .setbit : IDP_BIT_ON(1)  ピーク値検出回路動作
		 .       : IDP_BIT_OFF(0) ピーク値検出回路停止

	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[
		1.センサのブルーミングを避けるためには,R01レジスタ内のDIPPSTビット
		 .を"1"に設定して,蛍光灯をつけ光量が安定してから数φTGサイクル後に
		 .PEAKEビットを"1"に設定してください。
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitPEAKE(UBYTE setbit)  /** ビットON/OFF指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x03;    /** R03:コントロールレジスタ(4)選択   */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R03:コントロールレジスタ(4)リード */

	if (setbit==IDP_BIT_ON)
		tmpreg |= DIPP_CR_R03_PEAKE;   /** ピーク値検出イネーブルビット ON */
	else
		tmpreg &= ~DIPP_CR_R03_PEAKE;  /** ピーク値検出イネーブルビット OFF */

	IdpRegisterStatus.DIPP_AR = 0x03;    /** R03:コントロールレジスタ(4)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = tmpreg;  /** R03:コントロールレジスタ(4)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS 変化点モード設定]
	function	:[
		1.引数(SetBit)により、各モード設定を行います。
		 .setbit : 00000000(0)     自動初期値
		 .       : 00000100(0x40)  アドレス指定
		 .       : 00001000(0x80)  CPU書き込み
		 .       : 00001100(0xa0)  設定禁止
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_SetBitAJMD(UBYTE setbit)  /** 変化点モード指定 */
{
	UBYTE tmpreg;

	IdpRegisterStatus.DIPP_AR = 0x04;    /** R04:コントロールレジスタ(5)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	tmpreg = IdpInputByte(DIPP_CR_PORT);  /** R04:コントロールレジスタ(5)リード */

	tmpreg &= ~(DIPP_CR_R04_AJMD1|DIPP_CR_R04_AJMD2);
	tmpreg |= setbit;

	IdpRegisterStatus.DIPP_AR = 0x04;           /* R04:コントロールレジスタ(5) 選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = (UBYTE)(tmpreg | 0x80);  /* R04:コントロールレジスタ(5)ライト */
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);
}

/*************************************************************************
	module		:[DIPP-AS ピーク値レジスタリード]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		ICHOU薄読み対策  1997/04/08 s.takeuchi
		ピークデータをアクセスする時はDIPPSTのON/OFFはしない
		但し、必ずDIPPST-OFF状態でcallすること
	]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/02/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_ReadPeakData(void)
{
	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);  /** 変化点モード指定をCPU書き込みモードとします */
	/* DIPP_SetBitDIPPST(IDP_BIT_ON);           @** DIPPSTビットをONにします */
	DIPP_SetBitMPUAE(IDP_BIT_ON);            /** 内蔵RAMの書き込みを可能とします */

	IdpRegisterStatus.DIPP_AR = 0x0d;                          /** R0D:コントロールレジスタ(13)選択 */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);

	SYB_PeakData = IdpInputByte(DIPP_CR_PORT);    /** R0D:コントロールレジスタ(13)リード */

	/* DIPP_SetBitDIPPST(IDP_BIT_OFF);          @** DIPPSTビットをOFFします */
	DIPP_SetBitMPUAE(IDP_BIT_OFF);           /** 内蔵RAMの書き込みを不可能とします */
}

/*************************************************************************
	module		:[DIPP-AS ピーク値レジスタライト]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		ICHOU薄読み対策  1997/04/08 s.takeuchi
		ピークデータを書き込む時はDIPPST-OFF状態でないと
		いけないので、DIPPSTのON/OFFは削除
		但し、必ずDIPPST-OFF状態でcallすること
	]
	condition	:[なし]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1994/02/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_WritePeakData(void)
{
	DIPP_SetBitAJMD(DIPP_CR_R04_AJMD_CPUW);  /** 変化点モード指定をCPU書き込みモードとします */
	/* DIPP_SetBitDIPPST(IDP_BIT_ON);           @** DIPPSTビットをONにします */
	DIPP_SetBitMPUAE(IDP_BIT_ON);            /** 内蔵RAMの書き込みを可能とします */

	IdpRegisterStatus.DIPP_AR = 0x0d;
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);
	IdpRegisterStatus.DIPP_CR = SYB_PeakData;
	IdpOutputByte(DIPP_CR_PORT,IdpRegisterStatus.DIPP_CR);

	/* DIPP_SetBitDIPPST(IDP_BIT_OFF);          @** DIPPSTビットをOFFします */
	DIPP_SetBitMPUAE(IDP_BIT_OFF);           /** 内蔵RAMの書き込みを不可能とします */
}

/*************************************************************************
	module		:[DIPP-AS オートインクリメントネゲート]
	function	:[
		1.DIPP-ASのオートインクリメントをネゲートします。
	]
	return		:[なし]
	common		:[なし]
	comment		:[なし]
	condition	:[
		1.DIPPのオートインクリメントのネゲートは,以下の順で行い,①②の間に
		 .リードをしないうにして下さい。
			① AR=0x1Bを設定
			② ARに任意のアドレスを設定
		2.オートインクリメントのネゲートの確認は必ず上記①②の後に行って下さい
		 .ネゲートされていない時は①②を繰り返します
	]
	machine		:[H8/300]
	language	:[CH38(V.2.0.B)]
	keyword		:[H8/300(日立マイコン)]
	date		:[1993/11/25]
	author		:[宮崎]
*************************************************************************/
void DIPP_AutoIncrementNegate(void)
{
	IdpRegisterStatus.DIPP_AR = 0x1b;  /* ① */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);  /* ① */
	IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);  /* ② */

	while (IdpInputByte(DIPP_SR_PORT) & DIPP_SR_ATINC) {
		IdpRegisterStatus.DIPP_AR = 0x1b;  /* ① */
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);  /* ① */
		IdpOutputByte(DIPP_AR_PORT,IdpRegisterStatus.DIPP_AR);  /* ② */
	}
}


/*************************************************************************
	module		:[シェーディングデータ取り込み]
	function	:[
		1.
	]
	return		:[
	-	OK	1	シェーディングＯＫ
	-	NG	0	ランプエラー発生
	-	尚、シェーディングはエラーを発生しません。
	]
	common		:[]
	condition	:[]
	comment		:[
	-	この関数を呼んだ側で、戻り値をチェックして、
	-	ｓｙｓ＿ＭａｃｈｉｎｅＳｔａｔｕｓ［ＳＹＳ＿ＳＣＡＮＮＥＲ＿ＳＴＡＴＵＳ］
	-	にＳＹＳ＿ＳＣＡＮＮＥＲ＿ＬＡＭＰ＿ＥＲＲＯＲをセットしてください。
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[SCN]
	date		:[1994/04/15]
	author		:[木元　修]
*************************************************************************/
UBYTE CMN_ShadingExecute(void)
{
	return(DIPP_ShadingExecute());
}

/*************************************************************************
	module		:[Check Lamp]
	function	:[]
	return		:[
		OK	1:	ランプエラー無し
		NG	0:	ランプエラー
	]
	common		:[なし]
	comment		:[
					Must decide R0F value for black level!!!!
				 ]
	condition	:[なし]
	machine		:[V53]
	language	:[MSC]
	keyword		:[DIPP]
	date		:[1994/5/11]
	author		:[S.Kawasaki]
*************************************************************************/
UBYTE DIPP_CheckLamp(void)
{

	/* TBD R0F Value for Lamp Check */

	DIPP_Reset();       /** DIPP-ASソフトリセット */
	DIPP_InitialSet();  /** DIPP-AS初期設定 */

	DIPP_SetBitDIPPST(IDP_BIT_ON);  /** DIPP-AS読み取り開始 */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();                       /** ランプオン */
	wai_tsk(40);                         /** WCOM ONまで100mS（2ライン分）待ちます */
	DIPP_SetBitPEAKE(IDP_BIT_ON);   /** ピーク値検出回路を動作 */
	wai_tsk(2);                         /** WCOM ONまで10mS（2ライン分）待ちます */
	if((IdpInputByte(DIPP_SR_PORT)&DIPP_SR_FLEXG) == DIPP_SR_FLEXG) {	/** ステータスレジスタをリード */
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);  /** DIPP-AS読み取り終了 */
		return(NG);
	}
	else {
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);  /** DIPP-AS読み取り終了 */
		return(OK);
	}
}


/*************************************************************************
	module		:[高速ランプチェック]
	function	:[
		1.	ADFスキャナ送信1ページ目でのランプチェック
		2.	LampOn,DIPP_Reset,DIPP_InitialSetの後にcallする
		3.	動作はIDP_NO1固定
	]
	return		:[
		TRUE	正常
		FALSE	光源異常
	]
	common		:[]
	condition	:[
		ランプの点灯とDIPPの初期化は必ず行っておくこと
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[IDP]
	date		:[1997/03/31]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	DIPP_QuickCheckLamp( void )
{
	DIPP_SetBitDIPPST( IDP_BIT_ON );				/** DIPP-AS読み取り開始 */

	wai_tsk( 2 );									/** WCOM ONまで100mS（2ライン分）待ちます */
	DIPP_SetBitPEAKE( IDP_BIT_ON );					/** ピーク値検出回路を動作 */
	wai_tsk( 2 );									/** WCOM ONまで10mS（2ライン分）待ちます */

	if((IdpInputByte(DIPP_SR_PORT)&DIPP_SR_FLEXG) == DIPP_SR_FLEXG) {	/** 光源異常 */
		DIPP_SetBitPEAKE( IDP_BIT_OFF );	/** ピーク値検出回路停止 */
		DIPP_SetBitDIPPST( IDP_BIT_OFF );	/** DIPP-AS読み取り終了 */
		return( FALSE );
	}
	else {
		DIPP_SetBitPEAKE( IDP_BIT_OFF );	/** ピーク値検出回路停止 */
		DIPP_SetBitDIPPST( IDP_BIT_OFF );	/** DIPP-AS読み取り終了 */
		return( TRUE );
	}
}


/*************************************************************************
	module		:[Check Lamp]
	function	:[]
	return		:[
		OK	1:	ランプエラー無し
		NG	0:	ランプエラー
	]
	common		:[なし]
	comment		:[
					Must decide R0F value for black level!!!!
				 ]
	condition	:[なし]
	machine		:[V53]
	language	:[MSC]
	keyword		:[DIPP]
	date		:[1994/5/11]
	author		:[S.Kawasaki]
*************************************************************************/
UBYTE DIPP_STx_CheckLamp(void)
{

	/* TBD R0F Value for Lamp Check */

	DIPP_Reset();       /** DIPP-ASソフトリセット */
	DIPP_InitialSet();  /** DIPP-AS初期設定 */

	DIPP_SetBitDIPPST(IDP_BIT_ON);  /** DIPP-AS読み取り開始 */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();                       /** ランプオン */
	wai_tsk(1);
	DIPP_SetBitPEAKE(IDP_BIT_ON);   /** ピーク値検出回路を動作 */
	wai_tsk(2);                         /** WCOM ONまで10mS（2ライン分）待ちます */
	if((IdpInputByte(DIPP_SR_PORT)&DIPP_SR_FLEXG) == DIPP_SR_FLEXG) {	/** ステータスレジスタをリード */
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);  /** DIPP-AS読み取り終了 */
		return(NG);
	}
	else {
		DIPP_SetBitPEAKE(IDP_BIT_OFF);   /** ピーク値検出回路停止(ピーク値固定) */
		DIPP_SetBitDIPPST(IDP_BIT_OFF);  /** DIPP-AS読み取り終了 */
		return(OK);
	}
}


/************************************************************************
	module		:[ＩＤＰレジスタ書き込み関数]
	function	:[
		1.ｉｄｐ＿ｎｏに従って、ＩＤＰのアドレスを変換し、指定されたデータを書き込む。
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[IDP]
	date		:[1997/01/07]
	author		:[野瀬敏弘]
************************************************************************/
void IdpOutputByte(UDWORD idp_reg, UBYTE data)
{
	UWORD int_status;

	int_status = CheckInterruptEnable();
	CMN_DisableInterrupt();

	outpw(idp_reg, (UWORD)data);

	if (int_status) { /* 割込み禁止時、割込み許可状態だった */
		CMN_EnableInterrupt(); /* 割込み許可 */
	}
}


/************************************************************************
	module		:[ＩＤＰレジスタ読み込み関数]
	function	:[
		1.ｉｄｐ＿ｎｏに従って、ＩＤＰのアドレスを変換し、指定されたアドレスからデータを読み込む。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[IDP]
	date		:[1997/01/07]
	author		:[野瀬敏弘]
************************************************************************/
UBYTE IdpInputByte(UDWORD idp_reg)
{
	UBYTE idp_value;
	UWORD int_status;

	int_status = CheckInterruptEnable();
	CMN_DisableInterrupt();

	idp_value = (UBYTE)inpw(idp_reg);

	if (int_status) { /* 割込み禁止時、割込み許可状態だった */
		CMN_EnableInterrupt(); /* 割込み許可 */
	}
	return(idp_value);
}
