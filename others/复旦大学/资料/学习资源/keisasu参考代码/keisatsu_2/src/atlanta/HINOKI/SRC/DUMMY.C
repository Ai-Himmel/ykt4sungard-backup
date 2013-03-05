/* ダミー関数 1998/09/24 By H.hirao */
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include  "\src\atlanta\define\mon_pro.h"

/* void MAN_DocumentInTask(void){exi_tsk();} */
/* void MAN_WatchDocumentSetTask(void){exi_tsk();} */
/* void MAN_WatchDocumentOutTask(void){exi_tsk();} */
/* void MAN_WatchDocumentFeedTask(void){exi_tsk();} */
/* void MAN_WatchDocumentCoverTask(void){exi_tsk();} */
/* void CDC_EncodePageTask(void){exi_tsk();} */
/* void CDC_STxCodeConvertPageTask(void){exi_tsk();} */
#if !defined (KEISATSU) /* 警察FAX 05/04/28 石橋正和 */
void NCU_FaxComTelHookChkTask(void){exi_tsk();}
#endif
/* void MDM_FskTxTask(void){exi_tsk();} */
/* void MDM_PixTxTask(void){exi_tsk();} */
/* void MDM_FactoryFunctionTask(void){exi_tsk();} */
void LST_PrinterErrorDetectTask(void){wai_tsk(0xFFFF);}
void PRN_DocumentOutTask(void){exi_tsk();}
void PRN_DataTxTask(void){exi_tsk();}
void PRN_MemoryDataTxTask(void){exi_tsk();}
void PRN_JournalPrintTask(void){exi_tsk();}
void PRN_JAMRecoverTask(void){exi_tsk();}
/* void PRN_PrinterResetTask(void){exi_tsk();} */
void PRN_FuserTempTask(void){exi_tsk();}
void PRN_PaperSensorTask(void){exi_tsk();}
void PRN_CheckTonerTask(void){exi_tsk();}
void PRN_HighVoltageTask(void){exi_tsk();}
void PRN_PaperFeedTask(void){exi_tsk();}
void PRN_ManualDocumentInTask(void){exi_tsk();}
void PRN_PrinterWarmUpTask(void){exi_tsk();}
void PRN_WarmUpControlTask(void){exi_tsk();}
void PRN_WarmUpDcoumentOutTask(void){exi_tsk();}
void PRN_ListDocumentOutTask(void){exi_tsk();}
void PRN_GetResistTask(void){exi_tsk();}
void SCN_Exit(void){}
/* void MDM_FactoryFunctionExit(void){} */
void PRN_DataTxExit(void){}
void PRN_HighVoltageExit(void){}
void PRN_WarmUpControlExit(void){}
void PRN_ListDocumentOutExit(void){}
void CDC_STxCodeConvertPageExit(void){}
void CTS_Interrupt(void){return;}
void SCI_Interrupt(void){return;}
UBYTE /*(man_init._*/CCD_MakerTOSHIBA(void){ return(0); /* NEC:0 TOSHIBA:1 *//*MODEM__PORTをリードして決定する*/ }
UBYTE /*(man_init._*/CCD_SizeB4(void){ return(1); /*MODEM__PORTをリードして決定する*/}
void /*(man_init._*/SCN_SetBuzzer(UBYTE i){ /** ブザー禁止 */ }
void /*(man_comm._*/DIPP_SetBitDIPPST(UBYTE i){ /* スキャナー送信 左端影が出る対策 T.Nose 1998/03/26 */ }
void /*(dma_int._*/SCN_StopMotor(void){}
void /*(cdc_cntl._*/SetScannerCodecToDramDACK(void){ /* スキャナコーデックDACK設定 */ }
/* #if !defined (HINOKI2) */	/* LCDドライバ変更対応 2002/05/14 T.Takagi */
void /*(opr_disp._*/InitializeCGRAM_Data(void){}
/* #endif */
#if (0)	/* Del By H.Fujimura 1998/10/23 */
//UBYTE /*(opr_serv._*/D2W_SF_LifeMonitorClear[] = {0};
#endif
void /*(opr_serv._*/MDM_ConfigReset(void){}
void /*(opr_serv._*/CMN_ClearPrinterLifeMonitorData(void){}
WORD /*(opr_serv._*/PRN_CalculateDispEnvTemp(void){ return(1); }
UWORD	PRN_HeaterTemp = 0;					/* 現在のヒーター温度		*/
UWORD	PRN_Paper1SizeData = 0;				/* カセット１平均ＡＤ入力値	*/
UWORD	PRN_Paper2SizeData = 0;				/* カセット２平均ＡＤ入力値	*/
UWORD	PRN_Paper3SizeData = 0;				/* カセット３平均ＡＤ入力値	*/
UWORD	PRN_TonerHighCount = 0;				/* トナーＨレベルカウンタ	*/
WORD	PRN_OutputVoltage = 0;				/* 出力電圧					*/
UWORD	PRN_PWM_Duty = 0;					/* ＰＷＭデューティ			*/
UWORD	PRN_AverageHVT_Ampere = 0;			/* 転写電流(work)			*/
float	PRN_HVT_Ampere = 0;					/* 転写電流					*/
UBYTE /*(opr_serv._*/CMN_ShadingExecute(void){}
void /*(opr_tel._*/WriteCGRAM(UBYTE *i){}
void /*(opr_top._*/LED_Initial(void){}
void /*(FCM_TXB._*/DIPP_ReadInitialRAM(UBYTE *i){}
void /*(FCM_TXB._*/DIPP_ReadShadingRAM(UBYTE *i){}
void /*(FCMTXC._*/SCN_DecideReductionPattern(void){}
void /*(cmn_buzz._*/SCN_SetBuzzerFrequency(UBYTE i){}
void /*(cmn_tup._*/SCN_GearBacklashTimeOutCheck(void){}
void PmenOff(void){}


#if (0)
void DBG_MakeCommandFile(void)
{
	struct	SYS_CommandData_t	 *com_p;
	struct IndexTableData_t	*index_p;
	BYTE	command_no;
	
	/*------------------------------*/
	/* コマンドファイルの空きを検索 */
	/*------------------------------*/
	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
			break;
		}
	}
	/*------------------------------*/
	/* コマンドファイルのメンバ登録 */
	/*------------------------------*/
	if (command_no < SYS_COM_FILE_MAX) {
		com_p = &SYB_CommandFile[command_no];
		comp -> DialNumber.Speed[i] = SYB_SubAddressBoxTable[box_position].Speed[i];
		comp -> Option.Item = SYS_RELAYED_TX;	/** TBD 中継配信のアイテム */
		comp -> Option.ConfirmationReport	= NO;
		comp -> TitleMessage				= 0xFF;
		comp -> Ability						= NO;
		comp -> DepartmentCode				= 0xFFFF;

	/*--------------------------*/
	/* インデックスのメンバ登録 */
	/*--------------------------*/
		index_p = &MEM_IndexTable[0];
		index_p -> Item		= SYS_MEM_TX_FILE;
		index_p -> No		= (UWORD)command_noRelayedCommandNo;
		index_p -> Page		= (UWORD)rx_total_page + 1;
		index_p -> BoxNumber	= MEM_IGNORE_BOX_NUMBER;
		index_p -> Code		= SYS_MMR_CODE;
		index_p -> Mode		= SYS_NORMAL;
		index_p -> Size		= SYS_DOCUMENT_A4_SIZE;
		index_p -> LineCount	= 0;
		index_p -> StartBlockNo	= 0;
	}
	return;
}
#endif


/* 以下は、プリンター関係の不要タスクです。
** 本当はTIBを整理したいのですが、まだ変更の可能性が有るので
** とりあえず、ここにダミータスクをおいておいて、時期を見計らって
** 一気に整理することにします。
** By O.Kimoto 1998/10/27
*/
void AddIndexQueueTask(void){exi_tsk();}
void ExitAddIndexQueueTask(void){exi_tsk();}
void MakeImageTask(void){exi_tsk();}
void ExitMakeImageTask(void){exi_tsk();}
void MakeImageDecodeTask(void){exi_tsk();}
void MakeImageListTask(void){exi_tsk();}
void MakeImageDirectTask(void){exi_tsk();}
void PrinterResetTask(void){exi_tsk();}
void WatchPrinterTask(void){exi_tsk();}
void ExitWatchPrinterTask(void){exi_tsk();}
void WatchPrinter1SecTask(void){exi_tsk();}


#if (0)
/*POPLAR_H のためのﾀﾞﾐｰ*/
void	PRN_JournalPrintTask(void){}
/****************
void	Print_Journal_ImagePrint(void){}
void	next_journal_data(void){}
void PRN_Tim10msCAINValue(void){}
*******************/
void	LST_PrinterErrorDetectTask(void){}
void	PRN_DocumentOutTask(void){}
void	PRN_DataTxTask(void){}
void	PRN_MemoryDataTxTask(void){}
void	PRN_JAMRecoverTask(void){}
void	PRN_PrinterResetTask(void){}
void	PRN_FuserTempTask(void){}
void	PRN_PaperSensorTask(void){}
void	PRN_CheckTonerTask(void){}
void	PRN_HighVoltageTask(void){}
void	PRN_PaperFeedTask(void){}
void	PRN_ManualDocumentInTask(void){}
void	PRN_PrinterWarmUpTask(void){}
void	PRN_WarmUpControlTask(void){}
void	PRN_WarmUpDcoumentOutTask(void){}
void	PRN_ListDocumentOutTask(void){}
void	PRN_GetResistTask(void){}
void	PRN_DataTxExit(void){}
void	PRN_HighVoltageExit(void){}
void	PRN_WarmUpControlExit(void){}
void	PRN_ListDocumentOutExit(void){}
void	PRN_GetReduction(void){}
void	PRN_StartImagePrint(void){}
void	PRN_ModeDataToData400(void){}
void	PRN_Data400ToModeData(void){}
void	LST_StartPrinter(){}
void	LST_EndPrinter(){}
#endif
#if defined (TWN) /* added by H.Hirao 1999/02/03 */
CONST UWORD	PRN_DrumPrintMax = 10000;		/** ドラム交換予報までに印字可能なプリント枚数 */
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/21 石橋正和 */
#if (PRO_CLASS1 == DISABLE)
void CL1_FRH_ReceiveFrameTask(UWORD *mbx_no){}
void CL1_FRH_ReceiveFrameTaskExit(void) {}
void CL1_FRH_CarDownDetectTask(void) {}
void INT_DMA_RsTxRx(void) {}
#endif
#if (PRO_DPRAM == DISABLE)
void DPR_RemoteDataExecTask(void) {}
#endif
#endif

