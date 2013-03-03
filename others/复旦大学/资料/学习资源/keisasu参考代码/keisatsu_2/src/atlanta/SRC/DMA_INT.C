/**********************************************************************
*	RISC
*	File   Name:	DMA_INT.C
*	Coded    by:	è¨íJê≥é˜
*	Date       :	1996/11/26
*	Module Name:
*	Note       :	ÇcÇlÇ`ÇsÇbäÑçûèàóùÉTÉuÉãÅ[É`Éì
*
***********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\define\cdc_pro.h"	/* for Debug 1997/11/1  By M.Kotani */
#include "\src\atlanta\define\cdc_def.h"	/* for Debug 1997/11/1  By M.Kotani */
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\sh_port.h"

#include "\src\atlanta\ext_v\dma_data.h"
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* for Debug 1997/05/23  By T.Yamaguchi */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\ext_v\bkupram.h"
#endif

/*************************************************************************
	module		:[äOïtÇØÇcÇlÇ`ÇbÇÃÇsÇbäÑÇËçûÇ›]
	function	:[
		1.
	]
	return		:[ñ≥Çµ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/26]
	author		:[è¨íJê≥é˜]
*************************************************************************/
void DMA1_TC_Interrupt(void)
{
	UBYTE status;

	status = inp(DMAU_DST);

	if ((status & DST_TC0) != 0) {
/*		DecodeDMA_TC_Flag = 1;ç°ÇæÇØ*/
		DMA0_TC0Flag = 1;

		if (SCN_Control.UseType == IDP_SCANNER_TX) {
			DebugDMA_EncodeStopCounter++;
			if (DebugDMA_EncodeStopCounter == 256) {
				if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_ADJUST) {
					SCN_StopMotor();
					SCN_MotorCurrentStopCounter = 0;
					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_ADJUST;
				}
				DebugDMA_EncodeStopCounter = 0;
			}
		}
		else {
			DebugDMA_EncodeStopCounter = 0;
		}
		idet_evt(EVT_DMA_SCNCDC_DRAM);
	}
	if ((status & DST_TC1) != 0) {
		DMA0_TC1Flag = 1;
		idet_evt(EVT_DMA_DRAM_PRNCDC);
	}
	if ((status & DST_TC2) != 0) {
		DMA0_TC2Flag = 1;
		idet_evt(EVT_DMA_COMCDC_DRAM);
	}
	if ((status & DST_TC3) != 0) {
		DMA0_TC3Flag = 1;
		idet_evt(EVT_DMA_DRAM_COMCDC);
	}
/***
	idet_evt(EVT_DMA_SCNCDC_DRAM);
	idet_evt(EVT_DMA_DRAM_PRNCDC);
	idet_evt(EVT_DMA_COMCDC_DRAM);
	idet_evt(EVT_DMA_DRAM_COMCDC);
***/
}


/*************************************************************************
	module		:[ÇbÇcÇbÇ©ÇÁÇcÇqÇ`ÇlÇÃì‡ë†ÇcÇlÇ`ÇbÇÃÇsÇbäÑÇËçûÇ›]
	function	:[
		1.
	]
	return		:[ñ≥Çµ]
	common		:[]
	condition	:[]
	comment		:[ÇoÇnÇoÇkÇ`ÇqÅQÇkÅAÇ`ÇmÇyÇtÅQÇkópÅAà⁄êAÇ‡ÇÍ(Fix By M.Kotani 1997/11/25)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/06/16]
	author		:[è¨íJê≥é˜]
*************************************************************************/
void DMA_TC_CDC2DRAM_Interrupt(void)
{
	DMA0_TC0Flag = 1;
	if (SCN_Control.UseType == IDP_SCANNER_TX) {
		DebugDMA_EncodeStopCounter++;
		if (DebugDMA_EncodeStopCounter == 256) {
			if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_ADJUST) {
/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
				if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_DOWN;
					SCN_STxLineIntDisableFlag = 1;
					SCN_SetLineInt(SCN_DISABLE); /* ÉâÉCÉìäÑçûÇ›ã÷é~ */
					SCN_MotorCurrentStopCounter = 0;
				}
				else {
					SCN_StopMotor();
					SCN_MotorCurrentStopCounter = 0;
					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_ADJUST;
				}
#else
				SCN_StopMotor();
				SCN_MotorCurrentStopCounter = 0;
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_ADJUST;
#endif
			}
			DebugDMA_EncodeStopCounter = 0;
		}
	}
	else {
		DebugDMA_EncodeStopCounter = 0;
	}
	idet_evt(EVT_DMA_SCNCDC_DRAM);
}


/*************************************************************************
	module		:[ÇbÇcÇbÇ©ÇÁÇcÇqÇ`ÇlÇÃì‡ë†ÇcÇlÇ`ÇbÇÃÇsÇbäÑÇËçûÇ›]
	function	:[
		1.
	]
	return		:[ñ≥Çµ]
	common		:[]
	condition	:[]
	comment		:[ÇoÇnÇoÇkÇ`ÇqÅQÇkÅAÇ`ÇmÇyÇtÅQÇkóp]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/06/16]
	author		:[è¨íJê≥é˜]
*************************************************************************/
void DMA_TC_DRAM2CDC_Interrupt(void)
{
	DMA0_TC1Flag = 1;
	idet_evt(EVT_DMA_DRAM_PRNCDC);

	if (DMA_SH_Cntrl[DMA_DRAM_PRNCDC_CH].AutoInit == AUTO_INITIALIZE_ON) {
		DMA_RequestEnableInternalDMAU(DMA_DRAM_PRNCDC_CH);
	}
}


#if (PRO_COM_CODEC_TYPE == MN86064) && (PRO_EXT_DMAC == DISABLE)
/*************************************************************************
	module		:[í êMÇbÇnÇcÇdÇbÇ©ÇÁÇcÇqÇ`ÇlÇÃì‡ë†ÇcÇlÇ`ÇbÇÃÇsÇbäÑÇËçûÇ›]
	function	:[
		1.
	]
	return		:[ñ≥Çµ]
	common		:[]
	condition	:[]
	comment		:[ÇrÇ`ÇjÇ`ÇjÇhóp]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/29]
	author		:[ãvï€îé]
*************************************************************************/
#if 0 /* defined (SAKAKI) /* added by H.Kubo 1998/08/07 */
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\sakaki\define\sakiport.h"
CONST UBYTE DMA_ComCodecToDram_DebugSw = 0;
extern UDWORD DMA_ComCodecToDram_Debug;
#endif
void DMA_TC_ComCodecToRam_Interrupt(void)
{
#if 0 /* defined (SAKAKI) /* added for debugging by H.Kubo 1998/08/07 */
	UDWORD memwrite_current_address;
	UDWORD original_data_address;
	
	if (DMA_ComCodecToDram_DebugSw && DMA_ComCodecToDram_Debug) {
		memwrite_current_address = CheckDMAU_SH_DAR(0);
		original_data_address = (UDWORD) (memwrite_current_address- (UDWORD) (MEM_STOREAREA_START_ADDRESS - MEM_ECM_BUFFER_START_ADDRESS));
		if (*( ((UWORD *)memwrite_current_address) - 1) !=  *( ((UWORD *)original_data_address) - 1  )
			) {
			DMA_ComCodecToDram_Debug++;
			SYS_Modem2PortStatus |= IO_BIT_SOH_TCK;
			outpw(MODEM2_PORT, SYS_Modem2PortStatus);
		}
		if (*( ((UWORD *)memwrite_current_address) - 2) != *( ((UWORD *)original_data_address) - 2  )
			) {
			DMA_ComCodecToDram_Debug++;
			SYS_Modem2PortStatus |= IO_BIT_SOH_TCK;
			outpw(MODEM2_PORT, SYS_Modem2PortStatus);
		}
	}
#endif

	DMA0_TC2Flag = 1;
	idet_evt(EVT_DMA_COMCDC_DRAM);
}

/*************************************************************************
	module		:[ÇcÇqÇ`ÇlÇ©ÇÁí êMÇbÇnÇcÇdÇbÇÃì‡ë†ÇcÇlÇ`ÇbÇÃÇsÇbäÑÇËçûÇ›]
	function	:[
		1.
	]
	return		:[ñ≥Çµ]
	common		:[]
	condition	:[]
	comment		:[ÇrÇ`ÇjÇ`ÇjÇhóp]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/29]
	author		:[ãvï€îé]
*************************************************************************/
void DMA_TC_RamToComCodec_Interrupt(void)
{
	DMA0_TC3Flag = 1;
	idet_evt(EVT_DMA_DRAM_COMCDC);
}

#endif /* (PRO_COM_CODEC == MN86064) && (PRO_EXT_DMAC == DISABLE) */

