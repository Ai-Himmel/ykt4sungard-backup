/* ---------------------------------------------------------------------------------------- */
/*		ÌßÛ¼Şª¸Ä:ATLANTA																	*/
/*		Ó¼Ş­°Ù	:void ATD_CheckDSETask(void)												*/
/*		ì¬Ò	:RŒû																		*/
/*		“ú•t	:1996/10/31																	*/
/*		ŠT—v	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_DSE.C‚ğ—¬—p‚µ‚Ü‚µ‚½									*/
/*		C³—š—ğ:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\atd_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\atd_def.h"

#include "\src\atlanta\ext_v\atd_data.h"

#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"	/* By S.Kawasaki 1996/03/07 *//*	mbxno.FCM_Task	*/

#include "\src\atlanta\sh7043\define\io_pro.h"	/*	ƒŠƒŒ[ŠÖŒW	*/

/*************************************************************************
	module		:[‹É«”½“]ŒŸoƒ^ƒXƒN]
	function	:[
		‹É«‚ª”½“]‚µ‚½‚çƒƒbƒZ[ƒW‚ğ‘—M‚·‚é
	]
	common		:[
					ATD_DSE1_Status,ATD_DSE2_Status : ƒ_ƒCƒ„ƒ‹‘O‚Ì‹É«‚ğQÆ‚·‚é•Ï”
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§Ï²ºİ)]
	keyword		:[ATD]
	date		:[1993/12/5]
	author		:[‰œ‘º–¾]
*************************************************************************/
void	ATD_CheckDSETask()
{
	MESSAGE_t	 msg;

#if (0) /* ICHOU•ÏX by T.Soneoka 1997/04/01 */
// ‚c‚r‚d‚Q‚ÍŒ©‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·A‚c‚r‚d‚Q‚Íƒ_ƒCƒ„ƒ‹ƒCƒ“‚¨‚æ‚Ñ‚s‚d‚k^‚e‚`‚w‚Ì‹[—ƒxƒ‹–Â“®‚Ì‚İ‚Æ‚µ‚Ü‚·
//	while((dse1_flag == DSE1()) || (dse2_flag == DSE2())) {
//		wai_tsk(10);	/* 100ms */
//	}
#endif
	while(ATD_DSE1_Status == DSE1()) {
		wai_tsk(10);	/* 100ms */
	}
	msg.Message = MSG_DETECT_DSE;
	snd_msg(mbxno.FCM_Task, &msg);
	wai_tsk(0xffff);
}
