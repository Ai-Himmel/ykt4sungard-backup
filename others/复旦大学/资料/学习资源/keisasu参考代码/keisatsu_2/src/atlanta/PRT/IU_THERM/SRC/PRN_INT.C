/********************************************************************
*	System		: SAKAKI
*	File Name	: PRN_INT.C
*	Author		: K.Kawata
*	Date		: 1996/11/08
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\unisw_f.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\prt\thermal\define\prn_pro.h"
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#include "\src\atlanta\prt\thermal\define\prn_def.h"

#include "\src\atlanta\sakaki\ext_v\ga_data.h"
#include "\src\atlanta\define\cmn_pro.h"

extern UWORD INT_SP_Counter;

/*************************************************************************
	module		:[プリンタの割り込み処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SHC]
	language	:[SHC(Ver3.0C)]
	keyword		:[PRN]
	date		:[1998/6/2]
	author		:[K.Kawata]
*************************************************************************/
void	PRN_PrinterInterrupt(void)
{
UBYTE	motorcheck;

	if (INT_SP_Counter % 2) {

		if (PRN_DTC_Completed) {
			PRN_DTC_Completed = NO;
			if ((!(SYB_MaintenanceSwitch[MNT_SW_E6] & PRN_TEST_C)) && (!(SYB_MaintenanceSwitch[MNT_SW_E7] & PRN_TEST_B))) {	/* 位相ずれテスト 1998/10/22 K.Kawata */
				/*** SMCR Serial + IDP301 ***/
				SMCR_StatusPRN_Dummy = SMCR_Status;
				SMCR_StatusPRN_Dummy &= ~(0x0002);
				SMCR_StatusPRN_Dummy |= 0x0080;
				(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
				(*(UWORD *)0xC20644) = SMCR_Status;
				(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
				(*(UWORD *)0xC20644) = SMCR_Status;
				(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
				(*(UWORD *)0xC20644) = SMCR_Status;
				(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
				(*(UWORD *)0xC20644) = SMCR_Status;
				(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
				(*(UWORD *)0xC20644) = SMCR_Status;
			}
		}

		if (SYS_PRN_StopRequest == TRUE) {	/* 1998/09/09 H.Yoshikawa SCN・PRNのDual処理のためにとりあえず入れときます */
			SYS_SCN_StartRequest = TRUE;
			if (PRN_LineMemoryStatus == 99) {
				PRN_PreHeatProc();
				if (DecodeWaitFlag) {
					DecodeWaitFlag = FALSE;
					DecodeWaitCommandFlag = FALSE;
					idet_evt(EVT_PRINT_HEAT_1LINE_END);
				}
				else {
					DecodeWaitCommandFlag = TRUE;
				}
				if (PRN_ResonanceStopCount < 5) {
					PRN_ResonanceStopCount++;
				}
			}
		}
		else {
			motorcheck = NO;
			if (PRN_LineMemoryStatus == 99) {
				if (ReadPointWaitFlag) {
					if (PRN_ResonanceStopCount != 2) {
						motorcheck = YES;
						PRN_ResonanceStopCount = 0;
						/*Pmst();*/
						PRN_Control.PrintLineCount++;
						STCR1_Status = HeatTime();
						outpw(STCR1_PORT,STCR1_Status);
						Pst();
						PreheatContCount = SYB_MachineUniqSwitch[UNIQ_SW_F5];
						PreheatContCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F8];
						PreheatStopCount = SYB_MachineUniqSwitch[UNIQ_SW_F6];
						PreheatStopCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F9];
					}
					else {
						PRN_PreHeatProc();
					}
				}
				else {
					PRN_PreHeatProc();
				}
				if (PRN_ResonanceStopCount != 2) {
					if (RenewLineReadPoint()) {
						ReadPointWaitFlag = TRUE;
						LineBufferChange();
						DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, (UDWORD)&PRN_ImageBuffer1[ImageLineReadPoint][0]);
						DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, PRN_LineDMA.Counter);
						DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);
						DmaEnable();
						PRN_DTC_Completed = YES;
					}
					else {
						if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) {
							HeatPulseDisable();
						}
						ReadPointWaitFlag = FALSE;
					}
				}
				if (DecodeWaitFlag) {
					DecodeWaitFlag = FALSE;
					DecodeWaitCommandFlag = FALSE;
					idet_evt(EVT_PRINT_HEAT_1LINE_END);
				}
				else {
					DecodeWaitCommandFlag = TRUE;
				}
				if (PRN_ResonanceStopCount < 5) {
					PRN_ResonanceStopCount++;
				}
				if (motorcheck) {
					Pmst();
				}
			}
		}
	}
}

void	PRN_PreHeatProc(void)
{
/*ﾌﾟﾘﾋｰﾄ処理開始*/
					if (SYB_MachineUniqSwitch[UNIQ_SW_F8] != 0) {
						if (SYB_MachineUniqSwitch[UNIQ_SW_F9] == 0) {
							STCR1_Status = PRN_PreHeatTime();
							outpw(STCR1_PORT,STCR1_Status);
							Pst();
							PRN_Control.ReprintLineCount++;
						}
						else if (SYB_MachineUniqSwitch[UNIQ_SW_F9] == 0xff) {
							if (PreheatContCountSCN != 0) {
								STCR1_Status = PRN_PreHeatTime();
								outpw(STCR1_PORT,STCR1_Status);
								Pst();
								PRN_Control.ReprintLineCount++;
								PreheatContCountSCN--;
							}
						}
						else {
							if (PreheatContCountSCN != 0) {
								STCR1_Status = PRN_PreHeatTime();
								outpw(STCR1_PORT,STCR1_Status);
								Pst();
								PRN_Control.ReprintLineCount++;
								PreheatContCountSCN--;
							}
							else {
								if (PreheatStopCountSCN != 0) {
									PreheatStopCountSCN--;
								}
								else {
									PreheatContCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F8];
									PreheatStopCountSCN = SYB_MachineUniqSwitch[UNIQ_SW_F9];
								}
							}
						}
					}
/*ﾌﾟﾘﾋｰﾄ処理終了*/
}
