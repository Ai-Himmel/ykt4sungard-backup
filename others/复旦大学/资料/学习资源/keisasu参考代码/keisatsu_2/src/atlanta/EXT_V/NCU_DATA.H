/*	By Y.Suzuki 1996/10/12	*/
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
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
extern	UWORD		tskno_DetectCalledTask;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/11 */
/* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
extern	UBYTE		IsNDSndMsg;
extern	UBYTE		IsCiSndMsg;
extern	UWORD		tskno_Detect2ndCalledTask;
extern	UWORD		tskno_ND_DetectCalledTask;
#endif /* defined (KEISATSU) */
#endif
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
#if (PRO_CPU == SH7043) /*	By Y.Suzuki 1996/10/12	*/
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
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/06 */
extern	UWORD    		RingStatus2nd;
#endif /* defined (KEISATSU) */

/*--------------------------------------------------------------------------------------------------------*/
/*  ブランチ電話ＯＨ監視(NCU_SUB)                                                                         */
/*--------------------------------------------------------------------------------------------------------*/
#if (PRO_BRANCH_RX == ENABLE )
extern  UBYTE				BRCOhLevel;
extern	UBYTE				BranchLevel;
/* extern  unsigned    char				CML_BRCOhLevel;		sys_data.hに移動 1994/09/03 */
extern	struct	  BranchTelephoneData_t	BranchTelData;
#endif
/*--------------------------------------------------------------------------------------------------------*/
/*  着信検出(NCU_RING)                                                                                    */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD			RingingOnTime;
extern	UWORD			RingingOffTime;
extern	UBYTE		Ringing;
extern	UBYTE		TimeStatus;
extern	UBYTE		DoubleRingStatus;
extern	UBYTE		RingMasterFlag;
extern	UWORD			SamplingBuff[BUFF_MAX];			/* BUFF_MAX=10 '96,03,22 By N.S. */
/* extern	UWORD			SamplingBuff[6];			  '96,03,22 By N.S. */
extern	UWORD			CiOffTime;
extern	UWORD			CiMaxCycleTime;
extern	UWORD			CiMinCycleTime;
extern	UWORD			CI_Counter;
extern	UWORD			CI_OK_Counter;
extern	UWORD			CI_NG_Counter;
extern	UBYTE		FreqStatus;
extern	UBYTE		AfterCI_HL_RelayOn;
extern	UBYTE		RingBuzzerFlag;
extern	UBYTE		CI_DummyFlag;
#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/04 */
extern	UWORD			RingingOnTime2nd				;
extern	UWORD			RingingOffTime2nd				;
extern	UBYTE			Ringing2nd						;
extern	UBYTE			TimeStatus2nd					;
extern	UBYTE			DoubleRingStatus2nd				;
extern	UBYTE			RingMasterFlag2nd				;
extern	UWORD			SamplingBuff2nd[BUFF_MAX]		;	/*BUFF_MAX=10 '96,03,22 By N.S. */
extern	UWORD			CiOffTime2nd					;
extern	UWORD			CiMaxCycleTime2nd				;
extern	UWORD			CiMinCycleTime2nd				;
extern	UWORD			CI_Counter_2nd					;
extern	UWORD			CI_OK_Counter_2nd				;
extern	UWORD			CI_NG_Counter_2nd				;
extern	UBYTE    		FreqStatus2nd					;
#endif /* defined (KEISATSU) */
/*--------------------------------------------------------------------------------------------------------*/
/*　転送受信用(NCU_TEL/NCU_SUB)                                                                           */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD    		TransferReceiveAvailableTime;
extern	UBYTE   		TransferReceiveFlag;
/*--------------------------------------------------------------------------------------------------------*/
/* 回線補足・保留・ダイヤル同期フラグ(NCU_MAIN/NCU_TEL/NCU_D_IN/NCU_SUB)　　　　　　　                    */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE		HookKeyInputFlag;
extern	UBYTE		HoldKeyInputFlag;
extern	UBYTE		NumberKeyInputFlag;
/*--------------------------------------------------------------------------------------------------------*/
/* ダイヤル・インＤＴＭＦ検出(NCU_D_IN/NCU_SUB)                                                           */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE   		DTMF_ReceiverCounter;
extern	UBYTE   		DTMF_ReceiverDV_OnOff;
extern	UBYTE   		DTMF_ReceiverBuffer[4];
/*--------------------------------------------------------------------------------------------------------*/
/* リモート受信ＤＴＭＦ検出                                                                               */
/*--------------------------------------------------------------------------------------------------------*/
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
extern	UBYTE	DTMF_Detect_Buffer[3];
extern	UBYTE	NCU_RemotePulseCount;
extern	UBYTE	NCU_IsDetRemotePulse;
extern	UBYTE	NCU_IsRemotePulseRx;
#endif

/*--------------------------------------------------------------------------------------------------------*/
/* ＨＯＯＫ状態監視(NCU_SUB)                                                                              */
/*--------------------------------------------------------------------------------------------------------*/
extern	UWORD		Tel1OhCounter;	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
extern	UWORD		Tel2OhCounter;	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
extern	UBYTE		BRCTelOhCounter;
extern	UBYTE		OhPortStatus;
extern	UBYTE		BRC_TelephoneOhProtectFlag;
extern	UBYTE		BRC_OhDetectFlag;
extern	UBYTE		GenerateRingTel1OhCounter;
extern	UBYTE		GenerateRingTel2OhCounter;
extern	UBYTE		NCU_DetectStopSwitchFlag;
extern	UWORD			BranchDetectCounter;
extern	UBYTE		RelayOffFlag;					/* SATUKI ONLY  Add by TH92115 1995/01/10 */
#if defined (KEISATSU) /* 警察FAX 050616 Smuratec 李 */
extern	UBYTE	NCU_LineStatus;	/* 回線状態 */
#endif
/*--------------------------------------------------------------------------------------------------------*/
/*  回線監視が認識している現在の受信モード                                                                */
/*--------------------------------------------------------------------------------------------------------*/
extern  UBYTE		NCU_RxModeSwitch;
/*--------------------------------------------------------------------------------------------------------*/
/*  マーキュリーキー                                                                                      */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE		MercuryKeyEnableFlag;
extern	UBYTE		MercuryKeyEndFlag;
/* #if defined(USA) 1996/12/02 Eguchi -> アンズのあわす*/
/*--------------------------------------------------------------------------------------------------------*/
/*  ＰＩＮ                  '96,03,07 By N.S.                                                             */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE		PIN_NumberRedialProtectFlag;
/*#endif*/
/*--------------------------------------------------------------------------------------------------------*/
/*  その他                                                                                                */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE		SubDialBuffer[SYS_MERCURY_BUF_MAX];
extern	BYTE		TelRingCounter;
extern	UWORD			RingingType;
extern	UBYTE		PauseDetectFlag;
#if (PRO_MODEM == ORANGE3)		/* '94,08,18 By N.S. */
extern	UBYTE		FaxTadDetectCNGFlag;
extern	UBYTE		CNG_PatternDetectFlag;	/* '95,01,13 By N.S. */
extern	UWORD		CNG_Time;				/* Add by TH92115 1994/11/28 */
extern	UWORD		CNG_OffTime;			/* '95,01,13 By N.S.         */
#endif
extern	UWORD		CallRingBellOnTimer;		/* '96,01,10 By N.S. for ANZU USA */
#if defined(EC1)	/* ITA仕様 */
extern	UBYTE		PassCopyToRedialBuffer;
#endif
#if defined(EC1)	/* '98/04/9 M.H. HookKey timer for BEL */
extern 	UWORD		HookKeyTimer;
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
extern UWORD			NCU_ND_Status; /* added by H.Kubo 1998/07/02 */
extern UWORD			tskno_V23ToneTask; /* added by H.Kubo 1998/08/26 */
extern UWORD			tskno_BusyToneTask; /* added by H.Kubo 1998/08/26 */
extern UWORD			tskno_DetectDseTask; /* added by H.Kubo 1998/08/26 */
extern UWORD			tskno_V23RxTask; /* added by H.Kubo 1998/08/26 */
extern UBYTE			timerID_v23_arrival; /* added by H.Kubo 1998/08/26 */
extern UBYTE			timerID_ND_2ndCallTimer; /* added by H.Kubo 1998/10/14 */
extern UBYTE			timerID_ND_SleepAfterAck; /* added by H.Kubo 1998/11/25 */
extern UWORD			NCU_ND_FirstResponseTime; /* added by H.Kubo 1998/10/06 */
extern UWORD			tskno_CarOffTimer; /* added by H.Kubo 1998/10/16 */
#endif

#if (PRO_NCU_TYPE == HINOKI_TYPE)
extern UWORD			Tel1OhTimer;	/* added by H.Hirao 1999/03/13 */
extern UWORD			Tel2OhTimer;	/* added by H.Hirao 1999/03/13 */
#endif

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE) || (defined(POPLAR_H) && defined(JP1))	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG *//* 55転送 By O.Kimoto 2003/02/05 */
	/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
extern UBYTE			OneDigitDiallingExecute;
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
/* 特番受信フラグ */
extern UBYTE			NCU_SpecialReceiveFlag;
#endif /* defined (KEISATSU) */

/*--------------------------------------------------------------------------------------------------------*/
/* ＤＥＢＵＧ用・未使用                                                                                   */
/*--------------------------------------------------------------------------------------------------------*/
extern	UBYTE   	AfterFaxTransferT1Time;
extern	UWORD    	DTMF_ReceiverTimeup;
extern	UBYTE   	LC_CheckCounter;
extern	UBYTE   	LC_OnDetectCounter;
extern	UBYTE   	LC_OffDetectCounter;
extern	UBYTE		BRC_OutPutTest;
extern	UWORD	    DTMF_OutPutTest;
/* extern	UBYTE   CalledFromFaxNet;	*/
/* extern	UBYTE	NCU_DEBUG_SW;		*/

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 *//* Add By O.Kimoto 2002/03/11 */
extern UBYTE	IsTelFaxRingSend;		/* T/F待機で疑似ベル送出したら１になるフラグ O.Oshima 2002/03/05 */
#endif

/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
** 　　きていない===>従来どおり発呼
** 　　きていた  ===>リダイヤルへ
** という風にする
** なお、下記カウンターはフリーカウンターです。
** by O.Kimoto 2002/07/05
*/
extern UWORD	CI_Counter_for_FCM;

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
extern UBYTE DEBUG_RemoteTransferDialBufPoint;
extern UBYTE DEBUG_RemoteTransferDialBuf[20];
extern UBYTE DEBUG_Triger;
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
extern UBYTE IsDailing;
#endif /* defined (KEISATSU) */

#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
extern UBYTE CR_Ringing;
#endif

