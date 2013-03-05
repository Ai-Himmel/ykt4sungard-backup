/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_misc.c
 *	Create:	Mon Dec 29 16:14:07 1997	by	ishiyama
 *	Description:
 *		Scanner Control Miscellaneous Routines
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"

/*
 *	Name:	Clear Message Body
 *	Create:	Wed Feb 25 16:07:21 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	ClearMessageBody(
 *			MESSAGE	*Msg);
 *	Description:
 *		Message 構造体のクリア
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ClearMessageBody(
	MESSAGE_t	*Msg)
{
	Msg->Item = 0;
	Msg->Message = 0;
	Msg->SubMessage1 = 0;
	Msg->SubMessage2 = 0;
	Msg->SubMessage3 = 0;
	Msg->SubMessage4 = 0;
}

#if (0) /* 未使用です 1998/12/21 by T.Soneoka */
**void	TxMortorTest(void)
**{
**	InitializeGateArray();
**	SCN_Init();
**	SetupTxMotor(FEEDER_DOC_OUT);
**	CluchOn();
**	StartTxMotor();
**}
**
**BOOL	CIS_CCD_Test(void)
**{
**	UBYTE rtn;
**	struct ScanPageAtr      Page;
**
**	InzImageProcessor();
**	InitializeGateArray();
**
**	LampOn();
**	SetShadingData();
**	InzScanBuf();
**	InzImageProcessor();
**
**	Page.Mode = SYS_NORMAL;
**	Page.HolzReduction = 255;              /* 主走査縮小無し */
**	Page.VertReduction = IP_SUBM_NON;      /* 副操作縮小無し */
**	SetImageProcessor4Scan(&Page);          /* 画処理 ICの詳細設定 */
**
**	ScanExecFlagOn();
**
**	wai_tsk(5);
**
**	/* Ａ４左右５０ｍｍのところをサンプルします */
**	rtn = NG;
**	if ((ScanBuf[0][70] == 0x00)
**	&&  (ScanBuf[0][186] == 0xff)) {
**		rtn = OK;
**	}
**	
**	LampOff();          /* ランプ オフ */
**
**	return rtn;
**}
#endif