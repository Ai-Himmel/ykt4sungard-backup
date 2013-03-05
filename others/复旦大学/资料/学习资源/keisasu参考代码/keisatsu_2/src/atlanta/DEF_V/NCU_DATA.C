/*	By Y.Suzuki 1996/10/25	*/
/*	Original File jun\usr2:\src\kobe\anzu\def_v\ncu_data.c	*/
#include    "\src\atlanta\define\product.h"
#include    "\src\atlanta\define\message.h"
#include    "\src\atlanta\define\ncu_def.h"
#include    "\src\atlanta\define\timer10.h"
#include    "\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\ncu_cnst.h"

/*------------------------------------------------------------------------------------------------*/
/*	ﾀｽｸ間のﾒｯｾｰｼﾞ送信／受信時のﾒｯｾ-ｼﾞの型                                                         */
/*                                                                                                */
/*	typedef struct {																			  */
/*		UWORD Item;                                                                               */
/*		UWORD Message;                                                                            */
/*		UWORD SubMessage1;                                                                        */
/*		UWORD SubMessage2;                                                                        */
/*		UWORD SubMessage3;                                                                        */
/*		UWORD SubMessage4;                                                                        */
/*		} MESSAGE_t;                                                                                */
/*------------------------------------------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/27 */
UWORD		tskno_DetectCalledTask			=	0;
UWORD		tskno_Detect2ndCalledTask		=	0;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/11 */
UWORD		IsNDSndMsg						=	0;
#endif /* defined (KEISATSU) */
#endif
MESSAGE_t						TxNCUTaskMsg                = {0};
MESSAGE_t						TxDetectCalledTaskMsg       = {0};
MESSAGE_t						TxTelephoneOperationTaskMsg = {0};
MESSAGE_t						TxTelephoneExecuteTaskMsg   = {0};
MESSAGE_t                 	TxTelephoneHookCheckTaskMsg = {0};
MESSAGE_t     				TxGenerateRingSignalTaskMsg = {0};
MESSAGE_t             		TxTransRBTAndDetCNGTaskMsg  = {0};
MESSAGE_t						TxFaxTadAutoSwitchTaskMsg   = {0};
MESSAGE_t						TxDetectSilentTaskMsg       = {0};
MESSAGE_t						TxReceiveDTMFTaskMsg        = {0};
#if ( PRO_DIALIN == ENABLE )
MESSAGE_t    					TxDialInAutoSwitchTaskMsg	= {0};
/*	#if (PRO_NCU_TYPE == SATSUKI_TYPE)								'94,12,20 By N.S. */
MESSAGE_t  					TxDetectDSETaskMsg          = {0};
/*	#endif															'94,12,20 By N.S. */
#endif
/* #if (PRO_CPU == V53) || (PRO_CPU == SH704X) || (PRO_CPU == SH7034) @* By S.Kawasaki 1996/03/06 */
#if (PRO_CPU == SH7043) /* By Y.Suzuki 1996/10/12 */
	#if (PRO_BUILTIN_TAD == DISABLE)
MESSAGE_t  					TxDetectNoiseTaskMsg        = {0};
	#endif
#endif
struct 		Timer10msData_t	NCU10msTimer				= {0};


/*--------------------------------------------------------------------------------------------------------*/
/*	NCU状態変数　　　　　                                                                                 */
/*--------------------------------------------------------------------------------------------------------*/
UWORD			NCUStatus                   = 0;
UWORD			TADStatus                   = 0;
UWORD     		RingStatus                  = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/06 */
UWORD     		RingStatus2nd               = 0;
#endif /* defined (KEISATSU) */

/*--------------------------------------------------------------------------------------------------------*/
/*  ブランチ電話ＯＨ監視(NCU_SUB)                                                                         */
/*--------------------------------------------------------------------------------------------------------*/
#if (PRO_BRANCH_RX == ENABLE )
UBYTE					BRCOhLevel						=	0;
UBYTE					BranchLevel						=	0;
/* unsigned	char					CML_BRCOhLevel					=	0;	sys_data.cに移動 1994/09/03 */
struct		BranchTelephoneData_t		BranchTelData					=	{0};
#endif

/*--------------------------------------------------------------------------------------------------------*/
/*  着信検出(NCU_RING)                                                                                    */
/*--------------------------------------------------------------------------------------------------------*/
UWORD						RingingOnTime				= 0;
UWORD						RingingOffTime				= 0;
UBYTE			Ringing						= 0;
UBYTE			TimeStatus					= 0;
UBYTE			DoubleRingStatus			= 0;
UBYTE			RingMasterFlag				= 0;
UWORD						SamplingBuff[BUFF_MAX]		= {0};	/*BUFF_MAX=10 '96,03,22 By N.S. */
/*UWORD						SamplingBuff[6]				= {0};	  '96,03,22 By N.S. */
UWORD						CiOffTime					= 0;
UWORD						CiMaxCycleTime				= 0;
UWORD						CiMinCycleTime				= 0;
UWORD						CI_Counter					= 0;
UWORD						CI_OK_Counter				= 0;
UWORD						CI_NG_Counter				= 0;
UBYTE    		FreqStatus					= 0;
UBYTE    		AfterCI_HL_RelayOn			= 0;
UBYTE			RingBuzzerFlag				= 0;
UBYTE			CI_DummyFlag				= 0;
#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/04 */
UWORD			RingingOnTime2nd				= 0;
UWORD			RingingOffTime2nd				= 0;
UBYTE			Ringing2nd						= 0;
UBYTE			TimeStatus2nd					= 0;
UBYTE			DoubleRingStatus2nd				= 0;
UBYTE			RingMasterFlag2nd				= 0;
UWORD			SamplingBuff2nd[BUFF_MAX]		= {0};	/*BUFF_MAX=10 '96,03,22 By N.S. */
UWORD			CiOffTime2nd					= 0;
UWORD			CiMaxCycleTime2nd				= 0;
UWORD			CiMinCycleTime2nd				= 0;
UWORD			CI_Counter_2nd					= 0;
UWORD			CI_OK_Counter_2nd				= 0;
UWORD			CI_NG_Counter_2nd				= 0;
UBYTE    		FreqStatus2nd					= 0;
#endif /* defined (KEISATSU) */
/*--------------------------------------------------------------------------------------------------------*/
/*　転送受信用(NCU_TEL/NCU_SUB)                                                                           */
/*--------------------------------------------------------------------------------------------------------*/
UWORD			     		TransferReceiveAvailableTime = 0;
UBYTE    		TransferReceiveFlag          = 0;
/*--------------------------------------------------------------------------------------------------------*/
/* 回線補足・保留・ダイヤル同期フラグ(NCU_MAIN/NCU_TEL/NCU_D_IN/NCU_SUB)　　　　　　　                    */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE			HookKeyInputFlag            = 0;
UBYTE			HoldKeyInputFlag			= 0;
UBYTE			NumberKeyInputFlag          = 0;
/*--------------------------------------------------------------------------------------------------------*/
/* ダイヤル・インＤＴＭＦ検出(NCU_D_IN/NCU_SUB)                                                           */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE    		DTMF_ReceiverCounter        = 0;
UBYTE    		DTMF_ReceiverDV_OnOff       = 0;
UBYTE    		DTMF_ReceiverBuffer[4]      = {0};
/*--------------------------------------------------------------------------------------------------------*/
/* リモート受信ＤＴＭＦ検出                                                                               */
/*--------------------------------------------------------------------------------------------------------*/
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
UBYTE	DTMF_Detect_Buffer[3]		= {0};
UBYTE	NCU_RemotePulseCount = 0;
UBYTE	NCU_IsDetRemotePulse = 0;
UBYTE	NCU_IsRemotePulseRx = 0;
#endif

/*--------------------------------------------------------------------------------------------------------*/
/* ＨＯＯＫ状態監視(NCU_SUB)                                                                              */
/*--------------------------------------------------------------------------------------------------------*/
UWORD    		Tel1OhCounter               = 0;	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
UWORD    		Tel2OhCounter               = 0;	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
UBYTE    		BRCTelOhCounter             = 0;
UBYTE    		OhPortStatus                = 0;
UBYTE    		BRC_TelephoneOhProtectFlag  = 0;
UBYTE			BRC_OhDetectFlag			= 0;
UBYTE			GenerateRingTel1OhCounter   = 0;
UBYTE			GenerateRingTel2OhCounter   = 0;
UBYTE			NCU_DetectStopSwitchFlag    = 0;
UWORD						BranchDetectCounter			= 0;
UBYTE			RelayOffFlag				= 0;	/* SATUKI ONLY  Add by TH92115 1995/01/10 */
#if defined (KEISATSU) /* 警察FAX 050616 Smuratec 李 */
UBYTE			NCU_LineStatus				= 0;	/* 回線状態 */
#endif
/*--------------------------------------------------------------------------------------------------------*/
/*  回線監視が認識している現在の受信モード                                                                */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE			NCU_RxModeSwitch            = 0;
/*--------------------------------------------------------------------------------------------------------*/
/*  マーキュリーキー                                                                                      */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE			MercuryKeyEnableFlag		= 0;
UBYTE			MercuryKeyEndFlag			= 0;
/*#if defined(USA) 1996/12/02 Eguchi アンズにあわす*/
/*--------------------------------------------------------------------------------------------------------*/
/*  ＰＩＮ                  '96,03,07 By N.S.                                                             */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE			PIN_NumberRedialProtectFlag = 0;
/*#endif*/
/*--------------------------------------------------------------------------------------------------------*/
/*  その他                                                                                                */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE			SubDialBuffer[SYS_MERCURY_BUF_MAX] = {0};
BYTE						TelRingCounter 				= 0;
UWORD						RingingType					= 0;
UBYTE			PauseDetectFlag				= 0;
#if (PRO_MODEM == ORANGE3)		/* '94,08,18 By N.S. */
UBYTE			FaxTadDetectCNGFlag			= 0;
UBYTE			CNG_PatternDetectFlag		= 0;	/* '95,01,13 By N.S. */
UWORD			CNG_Time					= 0;	/* Add by TH92115 1994/11/28 */
UWORD			CNG_OffTime					= 0;	/* '95,01,13 By N.S.  */
#endif
UWORD			CallRingBellOnTimer			= 0;	/* '96,01,10 By N.S. for ANZU USA */
#if defined(EC1)
UBYTE			PassCopyToRedialBuffer		= 0;
#endif
#if defined(EC1)	/* '97/04/16 M.H. HookKey timer for BEL */
UWORD			HookKeyTimer				= 0;
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
UWORD			NCU_ND_Status= 0; /* added by H.Kubo 1998/07/02 */
UWORD			tskno_V23ToneTask = 0xffff;		/* added by H.Kubo 1998/08/26 */
UWORD			tskno_BusyToneTask = 0xffff;	/* added by H.Kubo 1998/08/26 */
UWORD			tskno_DetectDseTask = 0xffff;	/* added by H.Kubo 1998/08/26 */
UWORD			tskno_V23RxTask = 0xffff;		/* added by H.Kubo 1998/08/26 */
UBYTE			timerID_v23_arrival = 0xff;		/* added by H.Kubo 1998/08/26 */
UBYTE			timerID_ND_2ndCallTimer = 0xff; /* added by H.Kubo 1998/10/14 */
UBYTE			timerID_ND_SleepAfterAck = 0xff; /* added by H.Kubo 1998/11/25 */
UWORD			NCU_ND_FirstResponseTime = 0xff; /* added by H.Kubo 1998/10/06 */
UWORD			tskno_CarOffTimer = 0xffff;		/* added by H.Kubo 1998/10/16 */
#endif

#if (0) /* (PRO_NCU_TYPE == HINOKI_TYPE) comment by H.Hirao 1999/03/15 */
UWORD			Tel1OhTimer = 0;	/* added by H.Hirao 1999/03/13 */
UWORD			Tel2OhTimer = 0;	/* added by H.Hirao 1999/03/13 */
#endif

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE) || (defined(POPLAR_H) && defined(JP1))	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG *//* 55転送 By O.Kimoto 2003/02/05 */
	/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
UBYTE			OneDigitDiallingExecute = 0;
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
/* 特番受信フラグ */
UBYTE			NCU_SpecialReceiveFlag = 0;
#endif /* defined (KEISATSU) */

/*--------------------------------------------------------------------------------------------------------*/
/* ＤＥＢＵＧ用・未使用                                                                                   */
/*--------------------------------------------------------------------------------------------------------*/
UBYTE    		AfterFaxTransferT1Time       = 0;
UWORD			DTMF_ReceiverTimeup          = 0;
UBYTE    		LC_CheckCounter              = 0;
UBYTE    		LC_OnDetectCounter           = 0;
UBYTE    		LC_OffDetectCounter          = 0;
UBYTE    		BRC_OutPutTest               = 0;
UWORD			DTMF_OutPutTest              = 0;

/* unsigned char    		CalledFromFaxNet             = 0;	*/
/* unsigned	char			NCU_DEBUG_SW				 = 0;	*/

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 *//* Add By O.Kimoto 2002/03/11 */
UBYTE	IsTelFaxRingSend = 0;		/* T/F待機で疑似ベル送出したら１になるフラグ O.Oshima 2002/03/05 */
#endif

/* FCMタスクが生成されてからここにいたるまでに呼びしがくる場合がある（モデムの初期化に時間がかかりすぎ！！！）
** よって、ここにくる前に本当に呼び出し信号がきていないかを判断し、
** 　　きていない===>従来どおり発呼
** 　　きていた  ===>リダイヤルへ
** という風にする
** なお、下記カウンターはフリーカウンターです。
** by O.Kimoto 2002/07/05
*/
UWORD	CI_Counter_for_FCM			= 0;

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
UBYTE DEBUG_RemoteTransferDialBufPoint = 0;
UBYTE DEBUG_RemoteTransferDialBuf[20] = {0};
UBYTE DEBUG_Triger = 0;
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
UBYTE IsDailing = 0;
#endif /* defined (KEISATSU) */

#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
UBYTE CR_Ringing = 0;
#endif


