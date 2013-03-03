/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/16
*        FILE NAME:  cdc_stup.c
*      DESCRIPTION:  松下製コーデックNM86063を制御する為のサブルーチン群
*  PUBLIC ROUTINES:  UWORD EncodeLine(UBYTE codec_type);
*                    UWORD DecodeLine(UBYTE codec_type);
*                    UWORD ErrorLine(UBYTE codec_type);
*                    UWORD CodecDMA0_Address(UBYTE codec_type);
*                    UWORD CodecDMA1_Address(UBYTE codec_type);
* PRIVATE ROUTINES:  void StartEncode(UBYTE codec_type, UBYTE code_type);
*                    void StartDecode(UBYTE codec_type, UBYTE code_type);
*                    void StartCodeConvert(UBYTE codec_type, UBYTE src_code_type, UBYTE dest_code_type);
*                    void SetRTC(UBYTE codec_type, UBYTE code_type);
*                    UWORD CDC_GetDocumentMaxLine(UBYTE	mode);
*                    UBYTECDC_GetTxTTI_Line(UBYTE	mode);
*                    UWORD CDC_CheckCodecLSI(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\cdc_def.h"
#include  "\src\atlanta\define\sysscan.h"
#include  "\src\atlanta\define\idp_def.h"

#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\mntsw_c.h"

#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\scn_data.h"
#include  "\src\atlanta\ext_v\scn_tbl.h"
#include  "\src\atlanta\ext_v\bkupram.h"


#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1998/1/7 */
#include "\src\atlanta\ext_v\sys_port.h"
#endif
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1998/1/7 */
#include "\src\atlanta\sh7043\define\sh_port.h"
#endif



#if (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1998/01/26 */
#include "\src\atlanta\ext_v\cdc_data.h"
#endif
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/17 */
 #if (PRO_MODEM == R288F)
  #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
   #include  "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
  #else
   #include  "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
  #endif
 #endif
 #if (PRO_MODEM == MN195006)
   #include  "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
 #endif
#endif

/*************************************************************************
	module		:[符号化処理を行ったライン数をリターンする]
	function	:[
		1.指定されたコーデックのパラメータレジスタ(C0_LCONT_ADR)を読みだす
	]
	return		:[
		n>0:符号化を行ったライン数
	]
	common		:[なし]
	condition	:[]
	comment		:[
		スキャナタスクからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD EncodeLine(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	return(ReadCodecParameterRegister(codec_type, C0_LCONT_ADR));
}


/*************************************************************************
	module		:[復号化処理を行ったライン数をリターンする]
	function	:[
		1.指定されたコーデックのパラメータレジスタ(D0_LCONT_ADR)を読みだす
	]
	return		:[
		n>0:復号化を行ったライン数
	]
	common		:[なし]
	condition	:[]
	comment		:[
		プリントタスクからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD DecodeLine(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	return(ReadCodecParameterRegister(SCANNER_CODEC, D1_LCONT_ADR));
#endif
	return(ReadCodecParameterRegister(codec_type, D0_LCONT_ADR));
}


/*************************************************************************
	module		:[復号化処理のエラーライン数をリターンする]
	function	:[
		1.指定されたコーデックのパラメータレジスタ(D0_ELIN_ADR)を読みだす
	]
	return		:[
		n>0:エラーしたライン数
	]
	common		:[なし]
	condition	:[]
	comment		:[
		通信タスクからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD ErrorLine(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	return(ReadCodecParameterRegister(SCANNER_CODEC, D1_ELIN_ADR));
#endif
	return(ReadCodecParameterRegister(codec_type, D0_ELIN_ADR));
}


/*************************************************************************
	module		:[DMAチャンネル0のDMAアドレスをリターンする]
	function	:[
		1.指定されたコーデックのパラメータレジスタ(T0_STRA_ADR)を読みだす
	]
	return		:[
		n>0:DMAアドレス
	]
	common		:[なし]
	condition	:[]
	comment		:[
		スキャナタスクからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD CodecDMA0_Address(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	return(ReadCodecParameterRegister(codec_type, T0_STRA_ADR));
}


/*************************************************************************
	module		:[DMAチャンネル1のDMAアドレスをリターンする]
	function	:[
		1.指定されたコーデックのパラメータレジスタ(T1_STRA_ADR)を読みだす
	]
	return		:[
		n>0:DMAアドレス
	]
	common		:[なし]
	condition	:[]
	comment		:[
		参考関数(未使用)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
UWORD CodecDMA1_Address(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	return(ReadCodecParameterRegister(codec_type, T1_STRA_ADR));
}


/*************************************************************************
	module		:[符号化方式に応じた符号化コマンドを発行する]
	function	:[
		1.指定された符号の符号化コマンドを発行する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		符号化処理を開始する時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void StartEncode(UBYTE codec_type,	/*使用するコーデック*/
				 UBYTE code_type)	/*符号化方式*/
{
	switch (code_type) {	/**符号化処理を行う*/
	case SYS_MH_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MH_ENCODE);
		break;
	case SYS_MR_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MR_ENCODE);
		break;
	case SYS_MMR_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MMR_ENCODE);
		break;
	case SYS_MG3_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MG3_ENCODE);
		break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/19 */
	case SYS_JBIG_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_JBIG_ENCODE);
		break;
#endif
	default:
		break;
	}
}


/*************************************************************************
	module		:[符号化方式に応じた復号化コマンドを発行する]
	function	:[
		1.指定された符号の復号化コマンドを発行する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		復号化処理を開始する時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void StartDecode(UBYTE codec_type,	/*使用するコーデック*/
				 UBYTE code_type)	/*符号化方式*/
{
#if (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1998/01/26 */
	/* Vmn == 0x8000 でデコードチェックを行うと、デコードエラーを起こします。
	** これを回避するため、デコードチェック中は Vmn を 0 にしておきます。
	*/
	UWORD vmn_status;
	if (CDC_CheckCodecLSI(codec_type) == MN86064) {
		if (CodecCDCR_Status[codec_type] & ERCHK0_BIT) {
			vmn_status = ReadCodecParameterRegister(codec_type, VMN_ADR);
			SetCodecParameterRegister(codec_type, VMN_ADR, 0x0000);
		}
	}
#endif /* (PRO_COM_CODEC_TYPE == MN86064) */
	switch (code_type) {	/**復号化処理を行う*/
	case SYS_MH_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MH_DECODE);
		break;
	case SYS_MR_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MR_DECODE);
		break;
	case SYS_MMR_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MMR_DECODE);
		break;
	case SYS_MG3_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_MG3_DECODE);
		break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/19 */
	case SYS_JBIG_CODE:
		EnterCodecCommand(codec_type, CODEC_CMD_JBIG_DECODE);
		break;
#endif
	default:
		break;
	}
#if (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1998/01/26 */
	if (CDC_CheckCodecLSI(codec_type) == MN86064) {
		if (CodecCDCR_Status[codec_type] & ERCHK0_BIT) {
			SetCodecParameterRegister(codec_type, VMN_ADR, vmn_status);
		}
	}
#endif /* (PRO_COM_CODEC_TYPE == MN86064) */
}


/*************************************************************************
	module		:[符号変換するコマンドを発行する]
	function	:[
		1.元の符号を判断する
		2.変換する符号を判断する
		3.符号変換コマンドを発行する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		符号変換処理を開始する時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void StartCodeConvert(UBYTE codec_type,		/*使用するコーデック*/
					  UBYTE src_code_type,	/*変換元の符号化方式*/
					  UBYTE dest_code_type)	/*変換する符号化方式*/
{
	switch (src_code_type) {
	case SYS_MH_CODE:
		switch (dest_code_type) {
		case SYS_MH_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MH_TO_MH);
			break;
		case SYS_MR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MH_TO_MR);
			break;
		case SYS_MMR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MH_TO_MMR);
			break;
		case SYS_MG3_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MH_TO_MG3);
			break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
		case SYS_JBIG_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MH_TO_JBIG);
			break;
#endif
		default:
			break;
		}
		break;
	case SYS_MR_CODE:
		switch (dest_code_type) {
		case SYS_MH_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MR_TO_MH);
			break;
		case SYS_MR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MR_TO_MR);
			break;
		case SYS_MMR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MR_TO_MMR);
			break;
		case SYS_MG3_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MR_TO_MG3);
			break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
		case SYS_JBIG_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MR_TO_JBIG);
			break;
#endif
		default:
			break;
		}
		break;
	case SYS_MMR_CODE:
		switch (dest_code_type) {
		case SYS_MH_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MMR_TO_MH);
			break;
		case SYS_MR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MMR_TO_MR);
			break;
		case SYS_MMR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MMR_TO_MMR);
			break;
		case SYS_MG3_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MMR_TO_MG3);
			break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
		case SYS_JBIG_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MMR_TO_JBIG);
			break;
#endif
		default:
			break;
		}
		break;
	case SYS_MG3_CODE:
		switch (dest_code_type) {
		case SYS_MH_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MG3_TO_MH);
			break;
		case SYS_MR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MG3_TO_MR);
			break;
		case SYS_MMR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MG3_TO_MMR);
			break;
		case SYS_MG3_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MG3_TO_MG3);
			break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
		case SYS_JBIG_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_MG3_TO_JBIG);
			break;
#endif
		default:
			break;
		}
		break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	case SYS_JBIG_CODE:
		switch (dest_code_type) {
		case SYS_MH_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_JBIG_TO_MH);
			break;
		case SYS_MR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_JBIG_TO_MR);
			break;
		case SYS_MMR_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_JBIG_TO_MMR);
			break;
		case SYS_MG3_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_JBIG_TO_MG3);
			break;
		case SYS_JBIG_CODE:
			EnterCodecCommand(codec_type, CODEC_CMD_JBIG_TO_JBIG);
			break;
		default:
			break;
		}
		break;
#endif
	default:
		break;
	}
}


/*************************************************************************
	module		:[符号化方式に応じたRTCを発行する]
	function	:[
		1.符号化方式を判断する
		2.RTC符号を出力するコマンドを発行する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		1ページ符号化終了時にCallされる
		ＦＸのある機械では、ＲＴＣを１０個付けるとＲＴＮを返してくる機種があるから
		ＭＨ、ＭＲのＲＴＣの個数は６個付ける
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void SetRTC(UBYTE codec_type,	/*使用するコーデック*/
			UBYTE code_type)	/*符号化方式*/
{
	switch (code_type) {	/**RTC符号を出力する*/
	case SYS_MH_CODE:
		SetCodecParameterRegister(codec_type, C0_RTCR_ADR, 6);	/* １０個つけると対ゼロックス機でＧ３送信するとページ再送となる*/
		EnterCodecCommand(codec_type, CODEC_CMD_MH_MMR_RTC);	/**000000000001B*/
		break;
	case SYS_MR_CODE:
		SetCodecParameterRegister(codec_type, C0_RTCR_ADR, 6);	/* １０個つけると対ゼロックス機でＧ３送信するとページ再送となる*/
		EnterCodecCommand(codec_type, CODEC_CMD_MR_MG3_RTC);	/**0000000000011B*/
		break;
	case SYS_MMR_CODE:
		SetCodecParameterRegister(codec_type, C0_RTCR_ADR, 6);	/*4->6 '94.9.20*/
		EnterCodecCommand(codec_type, CODEC_CMD_MH_MMR_RTC);	/**000000000001B*/
		break;
	case SYS_MG3_CODE:
		SetCodecParameterRegister(codec_type, C0_RTCR_ADR, 6);	/*4->6 '94.9.20*/
		EnterCodecCommand(codec_type, CODEC_CMD_MR_MG3_RTC);	/**0000000000011B*/
		break;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	case SYS_JBIG_CODE:
#endif
	default:
		break;
	}
}


#if (PRO_FBS == ENABLE)
/*************************************************************************
	module		:[読取りライン数を取得]
	function	:[
		原稿の読取りライン数を取得
		ＡＤＦでは無制限、ＦＢＳでは原稿の縦サイズ
	]
	return		:[
		読取りライン数
		ＡＤＦ：0xffff(無限)
		ＦＢＳ：原稿サイズとモードによる値
	]
	common		:[]
	condition	:[]
	comment		:[
		ICHOUより移植 T.Nose 1997/02/03
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/06/03]
	author		:[竹内茂樹]
*************************************************************************/
UWORD	CDC_GetDocumentScanLine(
	UBYTE	mode)
{
	UWORD	scan_line;	/* 読取りライン */

	/** スキャナ(ADF/FBS)と原稿サイズによって、ノーマル原稿での読取りライン数を決める */

	/** 読取り装置を確認し、ADFは無限(0xffff)にする
	**	FBSは定型原稿サイズを確認し、それを読取りライン数とし、先後端の余白分を引く
	*/
	if (SYS_ScannerExecMode == SCN_ADF) {		/** ADF読取り */
		scan_line = 0xffff;
	}
	else {		/** FBS読取り */
		/** 指定された原稿サイズのライン数を取得し、SFine(15.4l/mm)でのライン数とする */
		scan_line = SYS_ScanDocSizeTable[SCN_RegularDocumentSize].Length * 4;

		/** 先端余白と後端余白をSFine(15.4l/mm)のライン数に変換して引く */
		scan_line -= ((CHK_UNI_FBS_TopMargin() + CHK_UNI_FBS_BottomMargin()) * 154) / 10;

		/**	余白0mmでも先後端の影を読まないように読み飛ばし分を引く
		**	(先端:2.5mm / 後端:2mm)
		*/	/* ICHOUよりコピー 1997/12/16 T.Nose */
		scan_line -= 70;	/* ((2.5+2)*154)/10 */

		/** コピー読み取りの場合は、更に先端印字余白分を引く */	/* ICHOUよりコピー T.Nose 1997/12/16 */
		if ((SCN_Control.UseType == IDP_DOCUMENT_STORE)
		&&	((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			||(SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))) {
			scan_line -= CHK_UNI_CopyDocTopSkipLine() * 10;
		}

		/**	読取りモードによって1/n倍して、実際の読取りライン数にする */
		switch (mode) {		/* 読み取りモードをチェック */
		case	SYS_NORMAL:		/* 普通     8 dot/mm  3.85 line/mm */
			scan_line /= 4;
			break;
		case	SYS_FINE:		/* 高画質   8 dot/mm  7.7 line/mm */
			scan_line /= 2;
			break;
		case	SYS_GRAY16:		/* 16階調   8 dot/mm  7.7 line/mm */
		case	SYS_GRAY16_SEP:	/* 16階調   8 dot/mm  7.7 line/mm */
		case	SYS_GRAY32:		/* 32階調   8 dot/mm  7.7 line/mm */
		case	SYS_GRAY32_SEP:	/* 32階調   8 dot/mm  7.7 line/mm */
		case	SYS_GRAY64:		/* 64階調   8 dot/mm  7.7 line/mm */
		case	SYS_GRAY64_SEP:	/* 64階調   8 dot/mm  7.7 line/mm */
			if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
				if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
				||	(SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
					/* マルチコピーは 15.4l/mm */
					if (((SYB_MaintenanceSwitch[MNT_SW_C6] & COPY_GREY_70REDUCTION) && (SCN_CopyFile->Reduction < SCN_CopyReduction))	/* 70%未満は必ず200dpiディザ */
					 || ((SCN_CopyFile->Reduction < 100) && CHK_UNI_ReduceGrayCopyDither200())) { /* 縮小率で200dpiディザ指定 */
						/** ディザ200dpiでスキャンするため、画素を1/2にする */
						scan_line /= 2;	/** 読み取りライン */
					}
				}
/* MemTx & LocalScan Gray 400dpi で縦方向が半分しか符号化されない T.Nose 1998/07/14 */
#if (PRO_CCD == DPI400)
				else if (CHK_UNI_HalfTone400DPI_ON()) {
					break;
				}
#endif
				else {
					/* メモリ送信は 7.7l/mm */
					scan_line /= 2;
				}
			}
			else {	/* IDP_SCANNER_TX */
				/*	CDC_STxCodeConvertPageTask()側でTTIインサイド分を引いた後で、
				**	IDPの縮小率でライン数を変換するので、そのまま 15.4l/mm で返す
				*/
			}
			break;
		case	SYS_SFINE:		/* 超高画質  8 dot/mm  15.4 line/mm */
		case	SYS_HFINE:		/* 超高画質 16 dot/mm  15.4 line/mm */
	 		/* 15.4l/mmになってるのでそのまま */
	 		break;
	 	default:
			scan_line /= 4;
	 			break;
		}
	}

	return (scan_line);
}
#endif /* (PRO_FBS == ENABLE) */

/*************************************************************************
	module		:[最大読取りライン数を取得]
	function	:[
		最大原稿長制限より、現在の読取りモードでのライン数を返す
	]
	return		:[
		最大読取りライン数
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CDC]
	date		:[1996/06/03]
	author		:[竹内茂樹]
*************************************************************************/
UWORD	CDC_GetDocumentMaxLine(	UBYTE	mode)
{
	UWORD	max_line;

#if (PRO_CIPHER == ENABLE)
	if (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) {
 #if (PRO_FBS == ENABLE) /* By Y.Suzuki 1998/07/07 */
		if (SYS_ScannerExecMode == SCN_ADF) {		/** ADF読取り */
			if (CMN_GetDocumentScanSize() == SYS_DOCUMENT_B4_SIZE) {
				/* 364+10mm */
				max_line = (UWORD)(SYS_B4_PAGE_LENGTH+38);
			}
			else {
				if (!CHK_UNI_NoLengthError()) {
					/* 297+10mm */
					max_line = (UWORD)(SYS_A4_PAGE_LENGTH+38);
				}
				else {
					max_line = (UWORD)(10 * 385);	/** ノーマル1mでは3850ライン */
				}
			}
		}
		else {/*FBSは関係ないはずですが MAXLINEをADFと共通でチェックされるのでセットが必要です。*/
			if (CMN_GetFBS_DocumentScanSize() == SYS_DOCUMENT_B4_SIZE) {
				/* 364+10mm */
				max_line = (UWORD)(SYS_B4_PAGE_LENGTH+38);
			}
			else {
				if (!CHK_UNI_NoLengthError()) {
					/* 297+10mm */
					max_line = (UWORD)(SYS_A4_PAGE_LENGTH+38);
				}
				else {
					max_line = (UWORD)(10 * 385);	/** ノーマル1mでは3850ライン */
				}
			}
		}
 #else /* PRO_FBS DISENABLE */
			if (CMN_GetDocumentScanSize() == SYS_DOCUMENT_B4_SIZE) {
				/* 364+10mm */
				max_line = (UWORD)(SYS_B4_PAGE_LENGTH+38);
			}
			else {
				if (!CHK_UNI_NoLengthError()) {
					/* 297+10mm */
					max_line = (UWORD)(SYS_A4_PAGE_LENGTH+38);
				}
				else {
					max_line = (UWORD)(10 * 385);	/** ノーマル1mでは3850ライン */
				}
			}
 #endif
	}
	else {/* スクランブル原稿以外 */
#endif
	/** 原稿長制限の設定によって、ノーマル原稿での最大ライン数を決める
	*** 1m制限=3850lines / 3.6m制限=13860lines
	*/
	if (SYS_DocumentLengthLimitFlag) {
		/* max_line = (UWORD)(1000 * 3.85);	 ノーマル1mでは3850ライン M.Kotani 1997/12/18*/
#if (PRO_SCAN_1000mm == ENABLE)/* L400 By Y.Suzuki 1998/04/01 */
		/* 読み取り原稿長のＭＡＸを１ｍとする。制限を１ｍ5ｃｍにする */
		max_line = (UWORD)((10 * 385)+38*5);	/** ノーマル1mでは3850ライン */
#else
		max_line = (UWORD)(10 * 385);	/** ノーマル1mでは3850ライン */
#endif
	}
	else {	/** ３．６ｍ制限設定時のノーマル・ライン数 */
		/* max_line = (UWORD)(3600 * 3.85);	ノーマル3.6mでは13860ライン M.Kotani 1997/12/18*/
		max_line = (UWORD)(36 * 385);	/** ノーマル3.6mでは13860ライン */
	}
#if (PRO_CIPHER == ENABLE)
	}
#endif

	/**	読取りモードによって、更にn倍する */
	switch (mode) {	 /** 読み取りモードをチェック */
	case	SYS_NORMAL:		/* 普通     8 dot/mm  3.85 line/mm */
#if (PRO_SCN_CODEC_TYPE == MN86064) /* T.Nose 1998/01/07 */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {	/*蓄積とスキャナ送信で違う Add By M.Kotani 1998/01/17*/
			if (CHK_UNI_FineNormalConvert()	/* ファイン→ノーマル変換する */
			 || CMN_NormalScan4Sec()) {		/* ノーマル４秒読取り */
				max_line *= 2;
			}
			else {
				max_line *= 1;
			}
		}
		else {
			if (CHK_UNI_FineNormalConvert()) {	/* ファイン→ノーマル変換する */
				max_line *= 2;
			}
			else {
				max_line *= 1;
			}
		}
#else
		max_line *= 1;
#endif
		break;
	case	SYS_FINE:		/* 高画質   8 dot/mm  7.7 line/mm */
#if (PRO_CCD == DPI300)	/* for anzu_l 1997/11/29 by M.Kotani */
		if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
		||	(SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
			max_line *= 3;	/* マルチコピーはEFine (12l/mm) */
		}
		else {
			max_line *= 2;	/* メモリ送信はFine (7.7l/mm) */
		}
#else	/*elseの位置を変更1997/12/18 By M.Kotani*/
		max_line *= 2;
#endif
		break;
	case	SYS_GRAY16:		/* 16階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY16_SEP:	/* 16階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY32:		/* 32階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY32_SEP:	/* 32階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY64:		/* 64階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY64_SEP:	/* 64階調   8 dot/mm  7.7 line/mm */
	case	SYS_GRAY128:	/* 128階調  8 dot/m   7.7 line/mm */
	case	SYS_GRAY128_SEP:/* 128階調  8 dot/m   7.7 line/mm */
	case	SYS_SGRAY:		/* 写真コピーの縮小スキャン(16x15.4) */
		if (SCN_Control.UseType == IDP_DOCUMENT_STORE) {
			if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
			||	(SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)) {
#if (PRO_CCD == DPI300)	/* for anzu_l 1997/11/29 by M.Kotani */
				max_line *= 3;	/* マルチコピーはEFine (12l/mm) */
				/*max_line *= 2;	マルチコピーはFine (7.7l/mm) バグでした上記に変更 By M.Kotani 1998/01/16*/
#endif
#if (PRO_CCD == DPI200)	/* for anzu_l 1997/11/29 by M.Kotani */
				max_line *= 2;	/* マルチコピーはFine (7.7l/mm) */
#endif
#if (PRO_CCD == DPI400)	/* for anzu_l 1997/11/29 by M.Kotani */
				max_line *= 4;	/* マルチコピーはSFine (15.4l/mm) */
#endif
			}
			else if (CHK_UNI_HalfTone400DPI_ON()) {
				/* メモリ送信原稿の中間調で400dpi蓄積(debug用)  1997/06/19 */
#if (PRO_CCD == DPI400)	/* for anzu_l 1997/11/29 by M.Kotani */
				max_line *= 4;	/* メモリ送信はFine (15.4l/mm) */
#else
				max_line *= 2;	/* メモリ送信はFine (7.7l/mm) */
#endif
			}
			else {
				max_line *= 2;	/* メモリ送信はFine (7.7l/mm) */
			}
		}
		else {	/* IDP_SCANNER_TX */
			switch (SCN_ScannerTxReductionPattern) {
			case	SYS_A3_400_TO_B4_400:
			case	SYS_A3_400_TO_A4_400:
			case	SYS_B4_400_TO_A4_400:
			case	SYS_A3_400_TO_A3_400:
			case	SYS_B4_400_TO_B4_400:
			case	SYS_A4_400_TO_A4_400:
#if (PRO_CCD == DPI400)	/* for anzu_l 1997/11/14 by T.Soneoka */
				max_line *= 4;	/* 15.4l/mm */
#endif
#if (PRO_CCD == DPI300)	/* for anzu_l 1997/11/14 by T.Soneoka */
				max_line *= 3;
#endif
#if (PRO_CCD == DPI200)	/* for anzu_l 1997/11/14 by T.Soneoka */
				max_line *= 2;	/* 7.7l/mm */
#endif
				break;
			default:
				max_line *= 2;	/* 7.7l/mm */
				break;
			}
		}
		break;
	case	SYS_SFINE:		/* 超高画質  8 dot/mm  15.4 line/mm */
	case	SYS_HFINE:		/* 超高画質 16 dot/mm  15.4 line/mm */
	/* for anzu_l 1997/11/14 by T.Soneoka */
	case	SYS_E_HFINE:		/* 超高画質 16 dot/mm  15.4 line/mm */
		max_line *= 4;
 		break;
 	default:
		max_line *= 1;
 			break;
	}

	return (max_line);
}

/*************************************************************************
	module		:[TTIのライン数を取得]
	function	:[
		読み取りモードからTTIのライン数を取得する
		スキャナ送信での線密度変換なども考慮
	]
	return		:[
		TTIライン数
	]
	common		:[]
	condition	:[]
	comment		:[
		CDC_STxCodeConvertPageTask()から抜き出した
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CDC]
	date		:[1996/06/03]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CDC_GetTxTTI_Line(UBYTE	mode)
{
	UBYTE	tti_line;

	switch (mode) {	/** 読み取りモードをチェック */
	case	SYS_NORMAL:		/* 普通     200dpi:8 dot/mm  100dpi:3.85本/l */
		tti_line = 16;
		break;
	case	SYS_FINE:		/* 高画質   200dpi:8 dot/mm  200dpi:7.7 本/l */
		tti_line = 32;
		break;
	case	SYS_GRAY16:		/* 16階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
	case	SYS_GRAY16_SEP:	/* 16階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
	case	SYS_GRAY32:		/* 32階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
	case	SYS_GRAY32_SEP:	/* 32階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
	case	SYS_GRAY64:		/* 64階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
	case	SYS_GRAY64_SEP:	/* 64階調   200dpi:8 dot/mm  200dpi:7.7 本/l */
#if (PRO_CCD == DPI200) /* By Y.Suzuki 1998/11/02 */
/*ポプラLの場合は、強制的に３２らいんをセットします。*/
/*本来は SCN_ScannerTxReductionPattern の値をかえるべきです。*/
		tti_line = 32;
		break;
#endif
		switch (SCN_ScannerTxReductionPattern) {
		case	SYS_A3_400_TO_A3_200:
		case	SYS_A3_400_TO_A3_203:
		case	SYS_A3_400_TO_B4_200:
		case	SYS_A3_400_TO_B4_203:
		case	SYS_A3_400_TO_A4_200:
		case	SYS_A3_400_TO_A4_203:
		case	SYS_B4_400_TO_B4_200:
		case	SYS_B4_400_TO_B4_203:
		case	SYS_B4_400_TO_A4_200:
		case	SYS_B4_400_TO_A4_203:
		case	SYS_A4_400_TO_A4_200:
		case	SYS_A4_400_TO_A4_203:
			tti_line = 32;
			break;
		case	SYS_A3_400_TO_B4_400:
		case	SYS_A3_400_TO_A4_400:
		case	SYS_B4_400_TO_A4_400:
		case	SYS_A3_400_TO_A3_400:
		case	SYS_B4_400_TO_B4_400:
		case	SYS_A4_400_TO_A4_400:
		default:
			tti_line = 64;
			break;
		}
		break;
	case	SYS_SFINE:		/* 超高画質 200dpi:8 dot/mm  400dpi:15.4本/l */
	case	SYS_HFINE:		/* 超高画質 400dpi:16dot/mm  400dpi:15.4本/l */
		tti_line = 64;
 		break;
 	default:
		tti_line = 16;
 			break;
	}

	return (tti_line);
}


/*************************************************************************
	module		:[使用するコーデックタイプを判断する]
	function	:[
	]
	return		:[
		コーデックタイプ
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/07/04]
	author		:[小谷正樹]
*************************************************************************/
UWORD CDC_CheckCodecLSI(UBYTE codec_type)
{
	UWORD codec_lsi;

	switch (codec_type) {
	case SCANNER_CODEC:
#if (PRO_SCN_CODEC_TYPE == MN86064)
		codec_lsi = CDC_MN86064;
#else
		codec_lsi = CDC_MN86063;
#endif
		break;
	case PRINTER_CODEC:
#if (PRO_PRN_CODEC_TYPE == MN86064)
		codec_lsi = CDC_MN86064;
#else
		codec_lsi = CDC_MN86063;
#endif
		break;
	case COMMUNICATION_CODEC:
#if (PRO_COM_CODEC_TYPE == MN86064)
		codec_lsi = CDC_MN86064;
#else
		codec_lsi = CDC_MN86063;
#endif
		break;
	default:
		SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
	}
	return (codec_lsi);

/*下記の問題点 By M.Kotani MN86064が実装されていてMN86063モードで動かす事ができません．Because チップで自動判断するため．*/
#if (PRO_CPU != SH7043) /* Added by H.Kubo 1998/02/14 */
	/* コーデックのレジスタを見て MN86063 か MN86064 かを判断する方法です。
	** 一つの ROM で MN86063 と MN86064 の両方に対応するにはこうするのがいいと思います。
	** ただし、ATLANTA での動作は未確認です。
	*/
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	/* DMCR のアドレスは正しく設定されるようにしてください。*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (CodecDMCR_DMIR_Status[codec_type] & 0x0001) {
		codec_lsi = CDC_MN86064;
	}
	else {
		codec_lsi = CDC_MN86063;
	}
	if (int_enable) {	/**割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** 割り込み許可*/
	}
	return codec_lsi;
#endif

}

#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
/*************************************************************************
	module		:[通信コーデックを使っての送信時、デコードライン数を計算する。]
	function	:[
		Pix_H_Reduction, Pix_V_Reduction と引数に与えられる出力希望ライン数から、入力ライン数を求める。
	]
	return		:[
		入力ライン数
	]
	common		:[
			Pix_H_Reduction, Pix_V_Reduction
	]
	condition	:[
		Pix_H_Reduction, Pix_V_Reduction が確定していること
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/12/16]
	author		:[久保博]
*************************************************************************/
UWORD CDC_GetDecodeLineFromOutLine(UWORD out_line)
{
	UWORD decode_line;
	if (Pix_V_Reduction == 0) { /* 無変換 */
				decode_line = out_line;
	}
	else {
		if (Pix_H_Reduction & 0x8000) { /* 拡大 */
			if (Pix_H_Reduction & 0x2000) {
				decode_line = (out_line * Pix_V_Reduction); /* MN86063 の固定拡大のとき。 */
			}
			else {
				decode_line =  (((UDWORD) out_line) * 65536) / (65536 + ((UDWORD) Pix_V_Reduction)); /* MN86063 の任意拡大のとき。 */
			}
		}
		else {/* 縮小 */
			if (((UDWORD) Pix_V_Reduction) < 65536) {
				decode_line =  (((UDWORD) out_line) * 65536) / (65536 - ((UDWORD) Pix_V_Reduction)); /* MN86063 の任意縮小のとき。 */
			}
			else {
				decode_line =  out_line;
			}
		}
	}
	return decode_line;
}
#endif
