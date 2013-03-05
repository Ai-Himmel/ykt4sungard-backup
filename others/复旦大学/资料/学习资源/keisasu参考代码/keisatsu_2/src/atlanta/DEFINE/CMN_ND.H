#ifndef _CMN_ND_H
 #define _CMN_ND_H

#include "\src\atlanta\define\cmn_ndhs.h"

/************************************************************************************************************
*		   BY:	 久保博
*		 DATE:	 1998/10/07
* VAR TO HOLD:	 
* DESCRIPTION:	 ナンバーディスプレイ情報種別
************************************************************************************************************/
#define		ND_INFO_CALLER_NUMBER			0x02
#define		ND_INFO_CALLER_EXTRA			0x21
#define		ND_INFO_CALLER_NUMBER_REASON	0x04
#define		ND_INFO_DIALIN_NUMBER			0x09
#define		ND_INFO_DIALIN_EXTRA			0x22
#define		ND_INFO_TRANSFERER_NUMBER		0x0B
#define		ND_INFO_TRANSFERER_EXTRA		0x23
#define		ND_INFO_MESSAGE					0x13
#define		ND_INFO_TIME					0x01
#define		ND_INFO_CALLER_NAME				0x07
#define		ND_INFO_CALLER_NAME_REASON		0x08
#define		ND_INFO_PUBLIC_PHONE			0x14

struct SYS_NumberDisplayTable *CMN_ND_FindNdTableByPhoneNumber(CONST UBYTE *rx_dial, UBYTE length);
void CMN_ND_SetFaxComReportOnNDJrnl(SYS_ND_HistoryHandle_t handle);
UWORD CMN_ND_FindTailOfRxInfo(UBYTE *info, UWORD length);
UBYTE CMN_ND_FindHeadOfRxParameter(UBYTE *info, UWORD length);
UBYTE CMN_ND_GetMessageLengthIndex(UBYTE *info, UWORD length);
UWORD CMN_ND_7bitJisCharTo8bitJisChar(UBYTE *dst, UBYTE *src, UWORD length);
UBYTE CMN_ND_GetNextInfoIndex(UBYTE *info, UBYTE index);
UBYTE CMN_ND_CheckDialinNumber(UBYTE *in);
void CMN_ND_RxInfoToHistory(SYS_ND_HistoryHandle_t handle, UBYTE *in);

SYS_ND_HistoryHandle_t  CMN_ND_Parse(UBYTE *buffer, UWORD length, UBYTE *dialin_status);
UBYTE CMN_ND_AnalizeRxInformation(UBYTE *, UWORD, UBYTE *dialin_status);
UBYTE CMN_ND_SetEmptyHistory(void); /* by H.Kubo 1998/10/20 */
UBYTE CMN_ND_SetV23ErrorHistory(UBYTE error); /* added by H.Kubo 1998/10/21 */
UBYTE CMN_ND_SetFnetHistory(void); /* by H.Kubo 1998/10/20 */


#endif
