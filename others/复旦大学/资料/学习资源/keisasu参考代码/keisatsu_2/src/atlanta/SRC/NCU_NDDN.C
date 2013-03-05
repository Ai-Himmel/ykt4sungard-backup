/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA													 */
/*	ファイル名	 : NCU_NDDN.C												*/
/*	モジュール	 :															 */
/*				 : CMN_ND_Parse()											 */
/*				 : CMN_ND_AnalizeRxInformation()							 */
/*				 : CMN_ND_RxInfoToHistory()									 */
/*	作成者		 : 久保博													 */
/*	日	付		 :	1998/10/14												 */
/*	概	要		 : モデムダイヤルイン処理									 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/

/* 仮のコードです。 by H.Kubo 1998/06/24 */


#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdiali.h"
#include "\src\atlanta\define\ncu_ret.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_NUMBER_DISPLAY == ENABLE) && ( PRO_DIALIN == ENABLE )


UBYTE	NCU_ND_CompareDialinNumber(UBYTE *ref_number, UBYTE *called_number, UBYTE length)
{
	UBYTE i;
	UBYTE ref_index;
	ref_index = SYS_DIALIN_MAX - 2;
	for (i = length - 1; i > 0; i--) {
		if (ref_number[ref_index] != called_number[i]) {
			return FALSE;
		}
		if (ref_index == 0) {
			return TRUE;
		}
		ref_index--;
	}
	if (ref_number[ref_index] == called_number[i]) {
		if (ref_index == 0) {
			return TRUE;
		}
	}
	return FALSE;
}

UBYTE	NCU_ND_CheckDialinNumber(UBYTE *number, UBYTE length)
{
	if (NCU_ND_CompareDialinNumber(SYB_Dialin.FaxNumber, number, length)) {
		return (D_IN_FAX);
	}
	else if (NCU_ND_CompareDialinNumber(SYB_Dialin.Tel1Number, number, length)) {
		if (NCU_ND_CompareDialinNumber(SYB_Dialin.Tel2Number, number, length)) {
			return(D_IN_TEL1_TEL2);
		}
		else {
			return (D_IN_TEL1);	/**	TEL1のみ呼び出し	*/
		}
	}
	else if (NCU_ND_CompareDialinNumber(SYB_Dialin.Tel2Number, number, length)) {
		return(D_IN_TEL2);
	}
	return (D_IN_UNMATCH);
}


#endif /*  (PRO_NUMBER_DISPLAY == ENABLE) && ( PRO_DIALIN == ENABLE ) */
