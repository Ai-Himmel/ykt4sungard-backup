/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L												*/
/*モジュ-ル名 : DEF_MBXN.H													*/
/*作成者名	  : 野瀬														*/
/*日  付	  : 96.10.12													*/
/*概  要	  : メイルボックス定義											*/
/*修正履歴	  : ANZUから流用 1996/10/12 T.Nose								*/
/*			  : 順番を変更	 1996/10/25 M.Tachibana							*/
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#define	 DEF_MBXN

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_mbxn.h"
#else

#ifndef	def_mbxn_h
	#define	def_mbxn_h

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｂ												*
 ************************************************************************/
#if defined(POPLAR_B)
#define	 MAX_MBXNO	71	/* \src\atlanta\sh7043\define\def_mon.hdr に
                        ** 同一の定義あり。同値に保ってください。T.Nose
                        */
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19 	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
	
};
#endif


/************************************************************************
 * ＰＯＰＬＡＲ タイプ ＢＮ												*
 ************************************************************************/
#if defined(POPLR_BN)
#define	 MAX_MBXNO	71	/* \src\atlanta\sh7043\define\def_mon.hdr に
                        ** 同一の定義あり。同値に保ってください。T.Nose
                        */
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19 	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/15  By T.Yamaguchi */
	WORD	FCM_BusyToneDetect;					/* By T.Yamaguchi 1998/03/15 NTT BusyTone検出 */
#endif
};
#endif


/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｌ												*
 ************************************************************************/
#if defined(POPLAR_L) || defined(POPLAR_N)
/*	とりあえずＢと同じにしとく By Y.Suzuki 1997/04/04	*/
#define	 MAX_MBXNO	71
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/15  By T.Yamaguchi */
	WORD	FCM_BusyToneDetect;					/* By T.Yamaguchi 1998/03/15 NTT BusyTone検出 */
#endif
};
#endif

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｈ												*
 ************************************************************************/
#if defined(POPLAR_H)
#define	 MAX_MBXNO	77
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
	WORD	FCM_V8Task;							/* By Y.Murata 1995/12/13  */
	WORD	MDM_V21DetectTask;					/* by H.Kubo ported from Clover 1997/06/30 */
	WORD	MDM_TxEcmControlTask;		/* R288Fモデムで使用しています	By T.Soneoka */ /*Ported From Clover by H.Kubo 1997/07/02*/
	WORD	FCM_Dummy;				/* by Y.Murata 1997/02/24 */ /* Ported from Clover by H.Kubo 1997/07/08 */
	WORD	CDC_Task;							/*  for JBIG by T.Soneoka 1997/12/11 */
	WORD	CDC_CTx;							/* By H.Kubo 1998/01/17 不達通知 */
};
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｌ													*
 ************************************************************************/
#if defined(ANZU_L)
#define	 MAX_MBXNO	71
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
};
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｖ													*
 ************************************************************************/
#if defined(ANZU_V)
#define	MAX_MBXNO	75	/* 72 -> 75 Modified by Eguchi 1998/04/03 */
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
	WORD	CDC_Task;							/*  for JBIG by T.Soneoka 1997/12/11 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	WORD	INF_Task;							/*  for InternetFAX by Y.Tanimototo 1998/03/12 */
	WORD	INF_RsWriteTask;					/* For Internet FAX 1998/04/01 Eguchi *//*要追加*/
	WORD	INF_RsReadTask;						/* For Internet FAX 1998/04/01 Eguchi *//*要追加*/
#endif
};
#endif

/************************************************************************
 * ＳＡＫＡＫＩ															*
 ************************************************************************/
#if defined(SAKAKI)
#define	 MAX_MBXNO	78
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
	WORD	FCM_V8Task;							/* By Y.Murata 1995/12/13  */
	WORD	MDM_V21DetectTask;					/* by H.Kubo ported from Clover 1997/06/30 */
	WORD	MDM_TxEcmControlTask;		/* R288Fモデムで使用しています	By T.Soneoka */ /*Ported From Clover by H.Kubo 1997/07/02*/
	WORD	FCM_Dummy;				/* by Y.Murata 1997/02/24 */ /* Ported from Clover by H.Kubo 1997/07/08 */
	WORD	CDC_Task;							/*  for JBIG by T.Soneoka 1997/12/11 */
	WORD	CDC_CTx;							/* By H.Kubo 1998/01/17 不達通知 */
	WORD	NCU_ND;								/* By H.Kubo 1998/08/21 ナンバーディスプレイ着信処理 */
};
#endif


/************************************************************************
 * Ｌ４００後継												*
 ************************************************************************/
#if defined(POPLAR_F)
#define	 MAX_MBXNO	80
struct mbxno_data_t {
	WORD	MAN_Task;							/* By S.K Nov.11,1993 */
	WORD	MAN_TimerTask;						/* By S.K Nov.11,1993 */
	WORD	MAN_SensorTask;						/* By S.K Feb.7,1994  */
	WORD	MAN_DocumentInTask;					/* By S.K Apr.8,1994 */
	WORD	CMN_BuzzerTask;
	WORD	NCU_Task;							/* By N.S Nov.19,1993 */
	WORD	NCU_TaskSub;						/* By N.S Sep.02,1994 */
	WORD	NCU_DetectCalledTask;				/* By N.S Nov.19,1993 */
	WORD	NCU_TelephoneHookCheckTask;			/* By N.S Nov.19,1993 */
	WORD	NCU_DetectFnetTask;					/* By N.S Nov.24,1993 */
	WORD	NCU_DialInAutoSwitchTask;			/* By S.K Apr.4,1994  */
	WORD	NCU_TelephoneOperationTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneOperationTaskSub;		/* By N.S Dec.10,1993 */
	WORD	NCU_FaxTadAutoSwitchTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_TelephoneExecuteTask;			/* By N.S Dec.10,1993 */
	WORD	NCU_ReceiveDTMFTask;				/* By N.S Dec.10,1993 */
	WORD	NCU_DailInAutoSwitchTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_TransRBTAndDetCNGTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_GenerateRingSignalTask;			/* By N.S Jan.21,1994 */
	WORD	NCU_DetectDSETask;					/* By N.S.Feb.24,1994 */
	WORD	NCU_DetectSilentTask;				/* By T.H.Mar.23,1994 */
	WORD	MDM_Task;
	WORD	MDM_TaskSub;
	WORD	MDM_PixDummy;						/* by T.S 1994.10.5 */
	WORD	MDM_EncodeDMA_TC_DetectTask;		/* By T.S 1994.8.20 */
	WORD	MDM_MTxReadDMA_Task;				/* By T.S 1994.8.21 */
	WORD	MDM_RxEcmControlTask;				/* By T.S 1994.8.22 */
	WORD	OPR_Task;							/* By S.K Dec. 1,1993 */
	WORD	OPR_SubMessageTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_Sub_MANTask;					/* By S.K Jan.11,1995 */
	WORD	OPR_MAN_MessageTask;				/* By T.N Jan.13,1995 */
	WORD	LST_Task;							/* BY H.T 1994. 3.30  */
	WORD	FCM_Task;							/* By S.K Dec. 1,1993 */
	WORD	Tone[6];							/* By A.O Dec. 2,1993 *//*	変更 5->6 1996/12/12  By T.Yamaguchi	*/
	WORD	ATD_SPD_Tone;						/* By T.Y Jan.29,1996 */
	WORD	SCN_Task;							/* BY J.M 1993.12.25  */
	WORD	SCN_ControlTask;					/* BY J.M 1993.12.25  */
	WORD	SCN_Sub;							/* By S.K Nov.2,1994 */
	WORD	SCN_GearBackLashTask;				/* By S.K Jan.24,1995 */
	WORD	SCN_MirrorMoveTask;					/* 1996/06/27 s.takeuchi */
	WORD	PRN_Task;							/* BY J.M 1993.12.25  */
	WORD	PRN_ControlTask;					/* by NOBUKO  Apr.15,94 */
	WORD	PRN_Serial;							/* by NOBUKO  Sep.23,94 */
	WORD	PRN_SerialInTimer;					/* by NOBUKO  Oct.04,94 */
	WORD	PRN_HighVoltageTask;				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_DocumentOutTask[3];				/* by M.Tachibana  1996/11/11 */
	WORD	PRN_ListDocumentOutTask;			/* by M.Tachibana  1996/11/11 */
	WORD	CPY_Task;							/* By S.K May.19,1994 */
	WORD	FIP;								/* By S.K Dec. 1,1993 */
	WORD	CL1_Task;							/* By Y.T 96'1.24	  */
	WORD	CL1_HdlcReceiveTask;				/* By Y.T 96'1.24	  */
	WORD	CL1_FaxComTask;						/* By Y.T 96'1.24	  */
	WORD	SCDC_TaskSub;						/* By Y.S 96/3/19	*/
	WORD	SCDC_RxEcmControlTask;				/* By Y.S 96/3/19	*/
	WORD	SCDC_MTxCodeConvertTask;			/* By Y.S 96/3/19	*/
	WORD	DPR_RemoteFuncExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_RemoteDataExecTask;				/* By M.Kotani 1996/08/05 */
	WORD	DPR_UpLoadRxTask;					/* By M.Kotani 1996/08/05 完了通知 */
	WORD	DPR_FunctionResult;					/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_DataResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_AtResult;						/* By M.Kotani 1996/08/05 スレーブ側からの応答を待つ */
	WORD	DPR_Task;							/* By M.Kotani 1996/08/05 メインタスクからの受信完了通知 */
	WORD	FCM_Option;							/* 1996/11/09 Y.Murata ２回線仕様の通信オプション */
	WORD	SCD_CipherResult;					/* By Y.Suzuki 1997/07/25 暗号化結果通知用 */
	WORD	FCM_BusyToneDetect;					/* By T.Yamaguchi 1998/03/15 NTT BusyTone検出 */
	WORD	FCM_V8Task;							/* By Y.Murata 1995/12/13  */
	WORD	MDM_V21DetectTask;					/* by H.Kubo ported from Clover 1997/06/30 */
	WORD	MDM_TxEcmControlTask;				/* R288Fモデムで使用しています	By T.Soneoka */ /*Ported From Clover by H.Kubo 1997/07/02*/
	WORD	FCM_Dummy;							/* by Y.Murata 1997/02/24 */ /* Ported from Clover by H.Kubo 1997/07/08 */
	WORD	CDC_Task;							/*  for JBIG by T.Soneoka 1997/12/11 */
	WORD	CDC_CTx;							/* By H.Kubo 1998/01/17 不達通知 */
	WORD	MDM_VoiceTask;						/* by m.matsumoto */
	WORD	FCM_V34Task;						/* By Y.Murata 1999/10/28  */
};
#endif


#endif

#endif
