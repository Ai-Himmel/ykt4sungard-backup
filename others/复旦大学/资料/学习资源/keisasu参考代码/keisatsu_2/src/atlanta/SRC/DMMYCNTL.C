/************************************************************************
*               BY:  Y.Murata
*             DATE:  1999/10/07
*        FILE NAME:  cdc_cntl.c
*      DESCRIPTION:  コーデック排他制御ルーチン
*  PUBLIC ROUTINES:  UBYTE GetCodec(UBYTE codec_type, UBYTE get_id)
*                    UBYTE ReleaseCodec(UBYTE codec_type, UBYTE get_id)
*                    UBYTE CheckCodec(UBYTE codec_type)
* PRIVATE ROUTINES:
*        REFERENCE:  SH7043 for POPLAR_F
*************************************************************************/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\define\cdc_def.h"
#include  "\src\atlanta\ext_v\cdc_data.h"
#include  "\src\atlanta\ext_v\cdc_tbl.h"
#include  "\src\atlanta\ext_v\sys_data.h"	/*Add By M.Kotani 1998/01/30*/
#include  "\src\atlanta\define\sysprint.h"	/*Add By M.Kotani 1998/01/30*/


/*************************************************************************
	module		:[引数のMN86063の使用権を獲得する]
	function	:[
		1.大域変数に使用IDをセットする
	]
	return		:[
		1:獲得成功
		0:他で使用中
	]
	common		:[
		CodecGetID
	]
	condition	:[]
	comment		:[コーデック制御各タスクからCallされる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
UBYTE GetCodec(UBYTE codec_type,	/*使用するコーデック*/
			   UBYTE get_id)		/*コーデック使用目的*/
{
	/* DMACのデータ方向をCODECからDRAMの方向で初期化しておきます  by T.Soneoka 1998/01/14 */
	if (codec_type == SCANNER_CODEC) {
		SetScannerCodecToDramDACK();	/* スキャナコーデックDACK設定 */
	}
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	if (codec_type == COMMUNICATION_CODEC) {
		if (CodecGetID[codec_type] == CODEC_NOT_USE) {
			CodecGetID[codec_type] = get_id;
			InitializeCodec(codec_type);	/**コーデック初期化（リセットを含む）*/
			return(1);
		}
		else {
			return(0);
		}
	}
	else {

		CMN_DisableInterrupt();		/** 割り込み禁止 */
		if ((CodecGetID[SCANNER_CODEC] == CODEC_NOT_USE) &&
			(CodecGetID[PRINTER_CODEC] == CODEC_NOT_USE)) {	/**コーデック未使用状態*/
			CodecGetID[codec_type] = CODEC_INITIALIZE;
			CMN_EnableInterrupt();		/** 割り込み許可 */
			if (((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MEMORY) ||
				(SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR) ||
				(SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MEMORY) ||
				(SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR))
				&&
				(get_id == CODEC_MEMORY_PRINT)) {
				/*画像付きリストの画像印字の先頭ではコーデックの初期化はしない。DMAが一時停止して位相がずれるため By M.Kotani 1998/01/30*/
			}
			else {
				InitializeCodec(SCANNER_CODEC);	/**コーデック初期化（リセットを含む）*/
			}
			CodecGetID[codec_type] = get_id;
			return (1);
		}
		else {
			if (CodecGetID[codec_type] == CODEC_NOT_USE) {
				CodecGetID[codec_type] = get_id;
				CMN_EnableInterrupt();		/** 割り込み許可 */
				while ((CodecGetID[SCANNER_CODEC] == CODEC_INITIALIZE) ||
					   (CodecGetID[PRINTER_CODEC] == CODEC_INITIALIZE)) {	/**コーデック初期化中*/
					wai_tsk(1);
				}
				return(1);
			}
			else {
				CMN_EnableInterrupt();		/** 割り込み許可 */
				return(0);
			}
		}
	}
#else
	if (CodecGetID[codec_type] == CODEC_NOT_USE) {
		CodecGetID[codec_type] = get_id;
		InitializeCodec(codec_type);	/**コーデック初期化（リセットを含む）*/
		return(1);
	}
	else {
		return(0);
	}
#endif
}


/*************************************************************************
	module		:[引数のMN86063の使用権を解放する]
	function	:[
		1.大域変数をクリアする
	]
	return		:[
		1:解放成功
		0:他で使用中, 又は既に未使用
	]
	common		:[
		CodecGetID
	]
	condition	:[]
	comment		:[コーデック制御各タスクからCallされる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
UBYTE ReleaseCodec(UBYTE codec_type,	/*使用するコーデック*/
				   UBYTE get_id)	  	/*コーデック使用目的*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	if (codec_type == COMMUNICATION_CODEC) {
		if (CodecGetID[codec_type] == get_id) {
			CodecGetID[codec_type] = CODEC_NOT_USE;
			ResetCodec(codec_type);	/**コーデックリセットのみ（初期化はしません）*/
			return(1);
		}
		else {
			/**獲得していないタスクが解放要求した*/
			return(0);
		}
	}
	else {
		CMN_DisableInterrupt();		/** 割り込み禁止 */
		if (CodecGetID[codec_type] == get_id) {
			CodecGetID[codec_type] = CODEC_NOT_USE;
			CMN_EnableInterrupt();		/** 割り込み許可 */
			return(1);
		}
		else {
			/**獲得していないタスクが解放要求した*/
			CMN_EnableInterrupt();		/** 割り込み許可 */
			return(0);
		}
		if ((CodecGetID[SCANNER_CODEC] == CODEC_NOT_USE) &&
			(CodecGetID[PRINTER_CODEC] == CODEC_NOT_USE)) {	/**コーデック未使用状態*/
			ResetCodec(SCANNER_CODEC);	/**コーデックリセットのみ（初期化はしません）*/

		}
		CMN_EnableInterrupt();		/** 割り込み許可 */
	}
#else
	if (CodecGetID[codec_type] == get_id) {
		CodecGetID[codec_type] = CODEC_NOT_USE;
		ResetCodec(codec_type);	/**コーデックリセットのみ（初期化はしません）*/
		return(1);
	}
	else {
		/**獲得していないタスクが解放要求した*/
		return(0);
	}
#endif
}


/*************************************************************************
	module		:[引数のMN86063が何に使用されているかチェックする]
	function	:[
		1.引数のコーデックの使用IDをリターンする
	]
	return		:[
		n>0:使用ID
	]
	common		:[
		CodecGetID
	]
	condition	:[]
	comment		:[コーデック制御各タスクからCallされる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
UBYTE CheckCodec(UBYTE codec_type)	/*使用するコーデック*/
{
	return(CodecGetID[codec_type]);
}
