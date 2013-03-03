/*	By Y.Suzuki 1996/10/24	*/
/* Original File jun\usr2:\src\kobe\anzu\ext_v\ncu_data.h */
#include 	"\src\atlanta\define\sysmax.h"
#include    "\src\atlanta\define\ncu_def.h"
#include	"\src\atlanta\define\timer10.h"
#include    "\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\ncu_cnst.h"

/*--------------------------------------------------------------------------------------------------------*/
/*	ﾀｽｸ間のﾒｯｾｰｼﾞ送信／受信時のﾒｯｾ-ｼﾞの型                                                                 */
/*                                                                                                        */
/*	typedef struct {																					  */
/*		UWORD Item;                                                                                */
/*		UWORD Message;                                                                             */
/*		UWORD SubMessage1;                                                                         */
/*		UWORD SubMessage2;                                                                         */
/*		UWORD SubMessage3;                                                                         */
/*		UWORD SubMessage4;                                                                         */
/*		} MESSAGE_t;                                                                                        */
/*--------------------------------------------------------------------------------------------------------*/
extern		MESSAGE_t				TxNCUTaskMsg;
extern		MESSAGE_t				TxDetectCalledTaskMsg;
extern		MESSAGE_t				TxTelephoneOperationTaskMsg;
extern		MESSAGE_t				TxTelephoneExecuteTaskMsg;
extern		MESSAGE_t        		TxTelephoneHookCheckTaskMsg;
extern		MESSAGE_t 			TxGenerateRingSignalTaskMsg;
extern		MESSAGE_t        		TxTransRBTAndDetCNGTaskMsg;
extern		MESSAGE_t				TxFaxTadAutoSwitchTaskMsg;
extern		MESSAGE_t				TxDetectSilentTaskMsg;
extern		MESSAGE_t				TxReceiveDTMFTaskMsg;
#if ( PRO_DIALIN == ENABLE )
extern		MESSAGE_t 			TxDialInAutoSwitchTaskMsg;
/*	#if ( PRO_CPU == H8 )										'94,12,20 By N.S. */
		#if defined(JPN)
extern		MESSAGE_t				TxDetectDSETaskMsg;
		#endif
/*	#endif														'94,12,20 By N.S. */
#endif
/* #if (PRO_CPU == V53) || (PRO_CPU ==SH7034) || (PRO_CPU == SH704X) */
#if (PRO_CPU == SH7043)
	#if (PRO_BUILTIN_TAD == DISABLE)
extern		MESSAGE_t  			TxDetectNoiseTaskMsg;
	#endif
#endif
extern		struct 				Timer10msData_t	NCU10msTimer;


/*--------------------------------------------------------------------------------------------------------*/
/*	NCU状態変数　　　　　                                                                                 */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD			NCUStatus;
extern	UWORD			TADStatus;
extern	UWORD    		RingStatus;

/*--------------------------------------------------------------------------------------------------------*/
/*  ブランチ電話ＯＨ監視(NCU_SUB)                                                                         */
/*--------------------------------------------------------------------------------------------------------*/
#if (PRO_BRANCH_RX == ENABLE )
extern  UBYTE	BRCOhLevel;
extern	UBYTE	BranchLevel;
/* extern  unsigned    char				CML_BRCOhLevel;		sys_data.hに移動 1994/09/03 */
extern	struct	  BranchTelephoneData_t	BranchTelData;
#endif
/*--------------------------------------------------------------------------------------------------------*/
/*  着信検出(NCU_RING)                                                                                    */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD	RingingOnTime;
extern	UWORD	RingingOffTime;
extern	UBYTE	Ringing;
extern	UBYTE	TimeStatus;
extern	UBYTE	DoubleRingStatus;
extern	UBYTE	RingMasterFlag;
extern	UWORD	SamplingBuff[BUFF_MAX];			/* BUFF_MAX=10 '96,03,22 By N.S. */
/* extern	UWORD			SamplingBuff[6];			  '96,03,22 By N.S. */
extern	UWORD	CiOffTime;
extern	UWORD	CiMaxCycleTime;
extern	UWORD	CiMinCycleTime;
extern	UWORD	CI_Counter;
extern	UWORD	CI_OK_Counter;
extern	UWORD	CI_NG_Counter;
extern	UBYTE	FreqStatus;
extern	UBYTE	AfterCI_HL_RelayOn;
extern	UBYTE	RingBuzzerFlag;
extern	UBYTE	CI_DummyFlag;
/*--------------------------------------------------------------------------------------------------------*/
/*　転送受信用(NCU_TEL/NCU_SUB)                                                                           */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD	TransferReceiveAvailableTime;
extern	UBYTE	TransferReceiveFlag;
/*--------------------------------------------------------------------------------------------------------*/
/* 回線補足・保留・ダイヤル同期フラグ(NCU_MAIN/NCU_TEL/NCU_D_IN/NCU_SUB)　　　　　　　                    */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	HookKeyInputFlag;
extern	UBYTE	HoldKeyInputFlag;
extern	UBYTE	NumberKeyInputFlag;
/*--------------------------------------------------------------------------------------------------------*/
/* ダイヤル・インＤＴＭＦ検出(NCU_D_IN/NCU_SUB)                                                           */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	DTMF_ReceiverCounter;
extern	UBYTE	DTMF_ReceiverDV_OnOff;
extern	UBYTE	DTMF_ReceiverBuffer[4];
/*--------------------------------------------------------------------------------------------------------*/
/* ＨＯＯＫ状態監視(NCU_SUB)                                                                              */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	Tel1OhCounter;
extern	UBYTE	Tel2OhCounter;
extern	UBYTE	BRCTelOhCounter;
extern	UBYTE	OhPortStatus;
extern	UBYTE	BRC_TelephoneOhProtectFlag;
extern	UBYTE	BRC_OhDetectFlag;
extern	UBYTE	GenerateRingTel1OhCounter;
extern	UBYTE	GenerateRingTel2OhCounter;
extern	UBYTE	NCU_DetectStopSwitchFlag;
extern	UWORD	BranchDetectCounter;
extern	UBYTE	RelayOffFlag;					/* SATUKI ONLY  Add by TH92115 1995/01/10 */
/*--------------------------------------------------------------------------------------------------------*/
/*  回線監視が認識している現在の受信モード                                                                */
/*--------------------------------------------------------------------------------------------------------*/
extern  UBYTE	NCU_RxModeSwitch;
/*--------------------------------------------------------------------------------------------------------*/
/*  マーキュリーキー                                                                                      */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	MercuryKeyEnableFlag;
extern	UBYTE	MercuryKeyEndFlag;
/*	@if defined(USA)			1996/10/21 By N.Sakamoto */
/*--------------------------------------------------------------------------------------------------------*/
/*  ＰＩＮ                  '96,03,07 By N.S.                                                             */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	PIN_NumberRedialProtectFlag;
/*	@endif						1996/10/21 By N.Sakamoto */
/*--------------------------------------------------------------------------------------------------------*/
/*  その他                                                                                                */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	SubDialBuffer[SYS_MERCURY_BUF_MAX];
extern	BYTE	TelRingCounter;
extern	UWORD	RingingType;
extern	UBYTE	PauseDetectFlag;
#if (PRO_MODEM == ORANGE3)		/* '94,08,18 By N.S. */
extern	UBYTE	FaxTadDetectCNGFlag;
extern	UBYTE	CNG_PatternDetectFlag;	/* '95,01,13 By N.S. */
extern	UWORD	CNG_Time;				/* Add by TH92115 1994/11/28 */
extern	UWORD	CNG_OffTime;			/* '95,01,13 By N.S.         */
#endif
extern	UWORD	CallRingBellOnTimer;		/* '96,01,10 By N.S. for ANZU USA */
#if defined(ITA)
extern	UBYTE	PassCopyToRedialBuffer;
#endif
/*--------------------------------------------------------------------------------------------------------*/
/* ＤＥＢＵＧ用・未使用                                                                                   */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE	AfterFaxTransferT1Time;
extern	UWORD	DTMF_ReceiverTimeup;
extern	UBYTE	LC_CheckCounter;
extern	UBYTE	LC_OnDetectCounter;
extern	UBYTE	LC_OffDetectCounter;
extern	UBYTE	BRC_OutPutTest;
extern	UWORD	    	DTMF_OutPutTest;
/* extern	unsigned    char   		CalledFromFaxNet;	*/
/* extern	unsigned	char		NCU_DEBUG_SW;		*/

