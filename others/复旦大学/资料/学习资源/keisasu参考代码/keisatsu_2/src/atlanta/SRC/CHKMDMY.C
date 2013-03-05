#include "\src\atlanta\define\product.h"

#if (PRO_KEYPANEL == PANEL_POPLAR_B)
#if defined(JPN)
#undef	PRO_CLASS1		/* 強制的にCLASS1をENABLEにする */
#define	PRO_CLASS1	ENABLE
#endif
#endif

#if (PRO_DPRAM == DISABLE)				/* By J.Miyazaki 1996/08/07 */
#include "\src\atlanta\define\dpr_def.h"
#endif

#if (PRO_SPEED_EX == DISABLE)
	void ATD_CheckToneTask(void){}
	void ATD_CheckToneExit(void){}
	void ATD_WatchTimer10msEventTask(void){}
#endif

#if (PRO_CLASS1 == DISABLE)
	void CL1_Task(void){}
	void CL1_RsControlTask(void){}
	void CL1_CommandReceiveTask(void){}
	void CL1_HdlcReceiveTask(void){}
	void CL1_HdlcReceiveExit(void){}
	void CL1_DataReceiveTask(void){}
	void CL1_DataReceiveExit(void){}
	void CL1_DummyDataTxTask(void){}
	void CL1_CEDTxTask(void){}
	void CL1_CEDTxExit(void){}
	void CL1_AutoDialTask(void){}
	void CL1_DialAbortTask(void){}
	void CL1_FaxComTask(void){}
	void CL1_FaxComExit(void){}
	void CL1_RsTimerTask(void){}
	void MPC_DMA_TC_Interrupt(void){}
#endif

#if (PRO_DPRAM == DISABLE)				/* By J.Miyazaki 1996/08/07 */
	void DPR_UpLoadRxTask(void){}
	void DPR_RemoteFuncExecTask(void){}
/*	void DPR_RemoteDataExecTask(void){} */
	void DPR_InsteadOfSlaveTask(void){}
	void DPR_CopyECM_BufferTask(void){}
	void DPRD_ErrorOpenDownLoadTx(void){}			/*	ここから By Y.Suzuki 1997/07/16	*/
	void DPRD_ErrorCloseDownLoadTx(void){}
	void DPRD_ErrorReceiveDataResult(void){}
	void DPRD_ErrorReceiveFunctionResult(void){}
	void DPRD_SetSlaveIdentification(void){}
	void DPRD_SetSlavePerformance(void){}/**/
	void DPRD_ErrorSetDownLoadTxArea(void){}
	void DPRD_StoreSamplingTxBuffer(void){}
	void DPR_GetBatchFile(void){}
	void DPRD_ErrorUpLoadModemFuncCom(void){}
	void DPRD_ErrorFunctionArgument(void){}
	void DPRD_StoreTTI_Data(void){}
	void DPRD_PAT_StoreImageBuffer(void){}
	void DPRD_SlaveDownLoadAreaWrite(void){}
	void DPRD_SlaveDownLoadAreaRead(void){}
	void DPRD_ErrorUpLoadID(void){}
	void DPRD_ErrorUpLoadDataType(void){}
	void DPRD_ErrorUpModemFuncResult(void){}
	void DPRD_ErrorUpModemDataResult(void){}
	void DPRD_SaveSamplingBuffer(void){}
	void DPRD_ErrorUpLoadRxInterrupt(void){}		/*	ここまで By Y.Suzuki 1997/07/16	*/
	void DPRD_SwapCopyV53toSH(void){}
	void DPRD_SwapCopySHtoV53(void){}
	void DPRD_CopySHtoV53(void){}
	void DPRD_CopyV53toSH(void){}
	void DPRD_ByteTypeCopyV53toSH(void){}
	void DPRD_ByteTypeCopySHtoV53(void){}
	void DPRD_WordTypeCopyV53toSH(void){}
	void DPRD_WordTypeCopySHtoV53(void){}
	void DPR_ReStoreR288F_InternalStatus(void){}
#endif
	/*不要なタスクstart*/
	void DPR_FuncReceiveMessageTask(void){}
	void DPR_DataReceiveMessageTask(void){}
	void DPR_FuncSendMessageTask(void){}
	void DPR_DataSendMessageTask(void){}
	/*不要なタスクend*/

#if (PRO_ROTATE == DISABLE)
	void ROT_Task(void){}
#endif

#if (PRO_FBS == DISABLE)
	void SCN_MirrorMoveTask(void){}
#endif

#if (PRO_PRINT_TYPE == LASER)
	void PRN_FuserTempTask(void){}
	void PRN_PaperSensorTask(void){}
	void PRN_CheckTonerTask(void){}
	void PRN_HighVoltageTask(void){}
	void PRN_HighVoltageExit(void){}
	void PRN_PaperFeedTask(void){}
	void PRN_PrinterErrorDetectTask(void){}
	void PRN_WarmUpControlTask(void){}
	void PRN_WarmUpControlExit(void){}
	void PRN_WarmUpDcoumentOutTask(void){}
	void PRN_ListDocumentOutTask(void){}
	void PRN_ListDocumentOutExit(void){}
	void PRN_GetResistTask(void){}
	void PRN_PrinterWarmUpTask(void){}
#endif

#if (PRO_CIPHER == DISABLE)
	void SCD_CipherTask(void){}
#endif

#if (0)	/* mdm_data.c で定義してある By m.Tachibana 1997/09/06 */
/*テンポラリ、開発中のためのもの*/
#if (PRO_COM_CODEC_TYPE == MN86063)
	UBYTE CodecRestartFlag = 0;
#endif
#endif

	void	SCN_MotorTestTask(void){}

