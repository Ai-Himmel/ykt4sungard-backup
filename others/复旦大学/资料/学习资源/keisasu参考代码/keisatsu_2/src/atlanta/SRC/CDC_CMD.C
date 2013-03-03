/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/15
*        FILE NAME:  cdc_cmd.c
*      DESCRIPTION:  松下製コーデックNM86063のCMDR(コマンドレジスタ)を
*                    設定する為のファイル群
*                    cdc_stup.c cdc_sub.cよりCallされる
*  PUBLIC ROUTINES:  void EnterCodecCommand(UBYTE codec_type, UBYTE command_number);
*                    void AbortCodecCommand(UBYTE codec_type);
* PRIVATE ROUTINES:  void WaitCommandEnd(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"

/*************************************************************************
	module		:[指定されたコマンドをコーデックに発行する]
	function	:[
		1.大域変数をセット
		2.コマンドを発行する
		3.コマンド終了を待つ
	]
	return		:[なし]
	common		:[
		CodecCMDR_Status
	]
	condition	:[]
	comment		:[
		コーデックにコマンドをセットしたい時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void EnterCodecCommand(UBYTE codec_type,		/*使用するコーデック*/
					   UBYTE command_number)	/*コマンド番号*/
{
	CMN_DisableInterrupt();	/**割り込み禁止*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	if (codec_type == SCANNER_CODEC) {	/** スキャンはチャンネル０を使用 */
		CodecCMDR_Status[SCANNER_CODEC] &= 0xFF00;	/**下位クリア*/
		CodecCMDR_Status[SCANNER_CODEC] |= command_number;	/**コマンドレジスタをセーブ*/
		outp((CodecRegisterAddressTable[SCANNER_CODEC][CODEC_CMDR]) + 1, command_number);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/07/04*/
	}
	else {	/** プリントはチャンネル１を使用 */
		CodecCMDR_Status[SCANNER_CODEC] &= 0x00FF;	/**上位クリア*/
		CodecCMDR_Status[SCANNER_CODEC] |= (command_number << 8);	/**コマンドを上位にシフトしてコマンドレジスタをセーブ*/
		outp((CodecRegisterAddressTable[SCANNER_CODEC][CODEC_CMDR]) + 2, command_number);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/07/04*/
	}
#else	/** 通常はそれぞれのコーデックのチャンネル０を使用する */
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (Is_JBIG_Restart) {
		CodecCMDR_Status[codec_type] = (command_number | JBIGRST_BIT);	/**コマンドレジスタをセーブ*/
	}
	else {
		CodecCMDR_Status[codec_type] = command_number;	/**コマンドレジスタをセーブ*/
	}
#else
	CodecCMDR_Status[codec_type] = command_number;	/**コマンドレジスタをセーブ*/
#endif

#if (PRO_CPU==SH7043) /**ワードライトしかできない機種は、使わないチャンネルのコマンドをＦＦＨとして発行する*/
	CodecCMDR_Status[codec_type] |= 0xFF00;	/**チャンネル１は無効コマンドとする（ＦＦＨ）松下飯塚さんに確認済み*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_CMDR], CodecCMDR_Status[codec_type]);
#else	/**バイトでライトできる機種は、必要なチャンネルのコマンドだけをバイトでライトする*/
	outp(CodecRegisterAddressTable[codec_type][CODEC_CMDR], (UBYTE)CodecCMDR_Status[codec_type]);
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	Is_JBIG_Restart = 0;
#endif

#endif
	WaitCommandEnd(codec_type);	/**コマンド終了を待つ*/
}


/*************************************************************************
	module		:[コーデックに発行したコマンドをアボートする]
	function	:[
		1.大域変数のアボートビットをセット
		2.コマンドを発行する
		3.コマンド終了を待つ
	]
	return		:[なし]
	common		:[
		CodecCMDR_Status
	]
	condition	:[]
	comment		:[
		コーデックが実行中のコマンドを異常終了したい時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void AbortCodecCommand(UBYTE codec_type)	/*使用するコーデック*/
{
	CMN_DisableInterrupt();	/**割り込み禁止*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	if (codec_type == SCANNER_CODEC) {	/** スキャンはチャンネル０を使用 */
		CodecCMDR_Status[SCANNER_CODEC] |= CMABT0_BIT;		/**アボートビットをセット*/
	}
	else {	/** プリントはチャンネル１を使用 */
		CodecCMDR_Status[SCANNER_CODEC] |= CMABT1_BIT;		/**アボートビットをセット*/
	}
	outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_CMDR], CodecCMDR_Status[SCANNER_CODEC]);
#else	/** 通常はそれぞれのコーデックのチャンネル０を使用する */
		CodecCMDR_Status[codec_type] |= CMABT0_BIT;		/**アボートビットをセット*/
	#if (PRO_CPU==SH7043) /**ワードライトしかできない機種は、使わないチャンネルのコマンドをＦＦＨとして発行する*/
		outpw(CodecRegisterAddressTable[codec_type][CODEC_CMDR], CodecCMDR_Status[codec_type]);
	#else	/**バイトでライトできる機種は、必要なチャンネルのコマンドだけをバイトでライトする*/
		outp(CodecRegisterAddressTable[codec_type][CODEC_CMDR], (UBYTE)CodecCMDR_Status[codec_type]);
	#endif
#endif
	WaitCommandEnd(codec_type);	/**コマンド終了を待つ*/
}


/*************************************************************************
	module		:[コーデックに発行したコマンドの終了を待つ]
	function	:[
		1.引数のコーデックのコマンド終了イベントを待つ
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		コマンド処理中である事
	]
	comment		:[
		コーデックの割り込みルーチン(int_cdc?.asm)でイベントがセットされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void WaitCommandEnd(UBYTE codec_type)	/*使用するコーデック*/
{
	switch (codec_type) {
	case SCANNER_CODEC:
		wai_evt(EVT_CDC0_COMMAND_END);	/**スキャナコーデックのコマンド終了を待つ*/
		break;
	case PRINTER_CODEC:
		wai_evt(EVT_CDC1_COMMAND_END);	/**プリンタコーデックのコマンド終了を待つ*/
		break;
	case COMMUNICATION_CODEC:
		wai_evt(EVT_CDC2_COMMAND_END);	/**通信コーデックのコマンド終了を待つ*/
		break;
	default:
		break;
	}
}
