#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_line.h" /** ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ用ｽﾃｰﾀｽのﾋﾞｯﾄ定義 */
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\define\mem_def.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\unisw_a.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"

#include "\src\memsw\define\mem_sw_b.h"
#include "\src\memsw\define\mems_pro.h"


/* #include "\src\atlanta\anzu\v53\define\v53io_pr.hv" */

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mlt_data.h"

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)
#endif

/*************************************************************************
	module		:[ポーリング原稿送信権利取得（受信起動用）]
	function	:[
		1.
	]
	return		:[
		０：獲得失敗
		１：獲得成功
	]
	common		:[
		SYB_PollingDocumentStatus
		SYB_PollingDocExclusiveFlag
	]
	condition	:[
		受信起動時にCallされる。
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[unsigned char far CMN_GetPollingDocRight(UWORD LineNumber){}]
	date		:[1996/11/11]
	author		:[木元修]
*************************************************************************/
unsigned char far CMN_GetPollingDocRight(UWORD LineNumber)
{
	unsigned char result;
	
	result = FALSE;
	
	CMN_DisableInterrupt();

	if (SYB_PollingDocumentStatus == 1) {

#if (0)	/*  By O.Kimoto 1997/07/07 */
** 		/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** 		** いう不具合が発生したので
** 		** By O.Kimoto 1997/07/07
** 		*/
** 		if ((SYS_PollingDocExclusiveFlag == SYS_EXIST_AND_NO_SENDING)
** 			|| ((SYS_PollingDocExclusiveFlag & SYS_ERR_POLLING_COM_EXIST)
** 				&& (SYS_PollingDocExclusiveFlag & 0x000F) == LineNumber)) {	/* 過去にエラーがあったかどうかの判断は不要？ */
** 			SYS_PollingDocExclusiveFlag = LineNumber;	/* 実際にポーリング送信を行なう回線番号を代入 */
** 			result = TRUE;
** 		}
#endif

		if(CHK_DocumentEraseAfterPolling() == 0) {				/** 正常交信でポーリング送信で原稿消去 */
			result = TRUE;
		}
		else {

#if (0)
** 			/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** 			if ((SYB_PollingDocExclusiveFlag == SYS_EXIST_AND_NO_SENDING)
** 				|| ((SYB_PollingDocExclusiveFlag & SYS_ERR_POLLING_COM_EXIST)
** 					&& (SYB_PollingDocExclusiveFlag & 0x000F) == LineNumber)) {	/* 過去にエラーがあったかどうかの判断は不要？ */
** 				SYB_PollingDocExclusiveFlag = LineNumber;	/* 実際にポーリング送信を行なう回線番号を代入 */
** 				result = TRUE;
** 			}
#else
			if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
				&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
				&& 	(SYS_DocumentPrintItem 	== SYS_MEM_POLLING_FILE)) {
				result = FALSE;
			}
			else if ((SYB_PollingDocExclusiveFlag == SYS_EXIST_AND_NO_SENDING)
				|| ((SYB_PollingDocExclusiveFlag & SYS_ERR_POLLING_COM_EXIST)
					&& (SYB_PollingDocExclusiveFlag & 0x000F) == LineNumber)) {	/* 過去にエラーがあったかどうかの判断は不要？ */
				SYB_PollingDocExclusiveFlag = LineNumber;	/* 実際にポーリング送信を行なう回線番号を代入 */
				result = TRUE;
			}
#endif

		}
	}

	CMN_EnableInterrupt();
	return(result);
}


/*************************************************************************
	module		:[ポーリング原稿送信権利放棄（受信起動用）]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYB_PollingDocumentStatus
		SYB_PollingDocExclusiveFlag
	]
	condition	:[
		引数はＣａｌｌする前に＋１しておいてください。
		受信側のＤＩＳのコンパチの結果でポーリング送信で無い場合にCallされる。
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[void far CMN_ReleasePollingDocRight(UWORD LineNumber){}]
	date		:[1996/11/11]
	author		:[木元修]
*************************************************************************/
void far CMN_ReleasePollingDocRight(UWORD LineNumber)
{
	CMN_DisableInterrupt();

	if (SYB_PollingDocumentStatus == 1) {
#if (0)	/*  By O.Kimoto 1997/07/07 */
** 		/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** 		** いう不具合が発生したので
** 		** By O.Kimoto 1997/07/07
** 		*/
** 		if ((SYS_PollingDocExclusiveFlag & 0x000F) == LineNumber) {
** 			SYS_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;
** 		}
#endif

		if(CHK_DocumentEraseAfterPolling() != 0) {				/** 正常交信でポーリング送信で原稿消去 */
			if ((SYB_PollingDocExclusiveFlag & 0x000F) == LineNumber) {
				SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;
			}
		}

	}

	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[ポーリング原稿消去（排他処理用）]
	function	:[
		1.
	]
	return		:[]
	common		:[
		SYB_PollingDocumentStatus
		SYB_PollingDocExclusiveFlag
	]
	condition	:[
		この関数が呼ばれる前に「SYB_PollingDocumentStatus」がクリアされているのが前提です。
		ポーリング送信が正常終了時に、通信からCallされる。
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[void far CMN_ErasePollingDoc(UWORD LineNumber){}]
	date		:[1996/11/11]
	author		:[木元修]
*************************************************************************/
void far CMN_ErasePollingDoc(UWORD LineNumber)
{
	CMN_DisableInterrupt();

	if ((SYB_PollingDocExclusiveFlag & 0x000F) ==  LineNumber) {
		SYB_PollingDocumentStatus = 0;
		SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;

		CMN_EnableInterrupt();

		MEM_ClearDoc(SYS_MEM_POLLING_FILE, 0, MEM_IGNORE_BOX_NUMBER);	/** ポーリング原稿消去 */
	}

	CMN_EnableInterrupt();
}

#if 0
///*************************************************************************
//	module		:[Ｆコードポーリング原稿消去（排他処理用）]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[
//		SYB_PollingDocumentStatus
//		SYB_PollingDocExclusiveFlag
//	]
//	condition	:[
//		この関数が呼ばれる前に「SYB_PollingDocumentStatus」がクリアされているのが前提です。
//		ポーリング送信が正常終了時に、通信からCallされる。
//	]
//	comment		:[]
//	machine		:[SH7041]
//	language	:[SHC]
//	keyword		:[OPT]
//	ProtoType	:[void far CMN_EraseFcodePollingDoc(UWORD LineNumber){}]
//	date		:[1997/09/29]
//	author		:[山口哲治]
//*************************************************************************/
//void CMN_EraseFcodePollingDoc(UWORD LineNumber,UBYTE BoxNumber)
//{
//	CMN_DisableInterrupt();
//
//	if ((SYB_PollingDocExclusiveFlag & 0x000F) ==  LineNumber) {
//		SYB_PollingDocumentStatus = 0;
//		SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;
//
//		CMN_EnableInterrupt();
//
//		MEM_ClearDoc(SYS_MEM_SUB_BULLETIN_FILE, MEM_ALL_NO, BoxNumber);	/** ポーリング原稿消去 */
//	}
//
//	CMN_EnableInterrupt();
//}
#endif

#if (0)
** /* 未使用です。 By O.Kimoto 1998/09/01 */
** /*************************************************************************
** 	module		:[ポーリング送信済みセット（エラー終了時）（排他処理用）]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[
** 		SYB_PollingDocumentStatus
** 		SYB_PollingDocExclusiveFlag
** 	]
** 	condition	:[
** 		ポーリング送信がエラー終了時に、通信からCallされる。
** 	]
** 	comment		:[]
** 	machine		:[V53]
** 	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
** 	keyword		:[OPT]
** 	ProtoType	:[void far CMN_SetAlreadySentPollingDoc(UWORD LineNumber){}]
** 	date		:[1996/11/11]
** 	author		:[木元修]
** *************************************************************************/
** void far CMN_SetErrorComPollingDoc(UWORD LineNumber)
** {
** 	CMN_DisableInterrupt();
** 
** 	if (SYB_PollingDocumentStatus == 1) {
** #if (0)	/*  By O.Kimoto 1997/07/07 */
** ** 		/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** ** 		** いう不具合が発生したので
** ** 		** By O.Kimoto 1997/07/07
** ** 		*/
** ** 		if ((SYS_PollingDocExclusiveFlag & 0x000F) ==  LineNumber) {
** ** 			SYS_PollingDocExclusiveFlag |= SYS_ERR_POLLING_COM_EXIST;
** ** 		}
** #endif
** 
** 		if(CHK_DocumentEraseAfterPolling() != 0) {				/** 正常交信でポーリング送信で原稿消去 */
** 			if ((SYB_PollingDocExclusiveFlag & 0x000F) ==  LineNumber) {
** 				SYB_PollingDocExclusiveFlag |= SYS_ERR_POLLING_COM_EXIST;
** 			}
** 		}
** 
** 	}
** 
** 	CMN_EnableInterrupt();
** }
#endif


/*************************************************************************
	module		:[ポーリング原稿送信権利チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MLT]
	ProtoType	:[UWORD far CMN_CheckPollingDocRights(UWORD){}]
	date		:[1997/07/07]
	author		:[木元修]
*************************************************************************/
UWORD far CMN_CheckPollingDocRights(UWORD line_number)
{
	if (SYB_PollingDocumentStatus) {
		if(CHK_DocumentEraseAfterPolling() == 0) {				/** 正常交信でポーリング送信で原稿消去 */
			return(1);
		}
		else {

#if (0)
** 			/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** 			if ((SYB_PollingDocExclusiveFlag & 0x000F) == (UWORD)line_number) {
** 				return(1);
** 			}
#else
			if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
				&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
				&& 	(SYS_DocumentPrintItem 	== SYS_MEM_POLLING_FILE)) {
				return(0);
			}
			else if ((SYB_PollingDocExclusiveFlag & 0x000F) == (UWORD)line_number) {
				return(1);
			}
#endif

		}
	}
	return(0);
}

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #endif
#endif


