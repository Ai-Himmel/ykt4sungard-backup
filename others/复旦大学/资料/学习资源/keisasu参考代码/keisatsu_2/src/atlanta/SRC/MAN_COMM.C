/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_comm.c
*	Author			:
*	Date			: 1997/06/09
*	RealTimeOS		: RISCƒ‚ƒjƒ^
*	Description		: ƒƒCƒ“ƒ^ƒXƒNMAN_Task()‚ÌƒƒbƒZ[ƒWˆ—•”
*					: ‰ñüA’ÊMŠÖ˜A•”
*	Module Name		: MAN_FromNCU_Task()
*					: MAN_FromFaxcom()
*	Maintenance		:
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*’è‹`ƒtƒ@ƒCƒ‹*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\sysrxsw.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sys_opt.h"
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\sysmjnl.h"
#include  "\src\atlanta\define\mntsw_h.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/* ˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\ */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include  "\src\atlanta\define\syscntpl.h"
#endif

/*QÆƒtƒ@ƒCƒ‹*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include  "\src\atlanta\sh7043\ext_v\extv_sem.h"
/*FCM*/
#include  "\src\atlanta\ext_v\fcm_data.h"
/*SCN*/
#include  "\src\atlanta\ext_v\scn_data.h"
#include  "\src\atlanta\ext_v\scn_tbl.h"
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL)	/* Add by O.Kimoto 1998/11/17 */
 #if defined(STOCKHM2)		/* Modify by SMuratec K.W.Q 2004/05/18 */
#include  "\src\atlanta\prt\lv_therm\ext_v\prn_data.h"
 #else
#include  "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
 #endif
#endif
#if (PRO_CLASS1 == ENABLE)
#include  "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_CIPHER == ENABLE)	/* 98/06/16 By T.Fukumoto */
#include	"\src\atlanta\scd\ext_v\cph_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#endif

/*ƒvƒƒgƒ^ƒCƒvéŒ¾*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\scn_pro.h" /* Added by H.Kubo 197/08/13 */
#include  "\src\atlanta\sh7043\define\io_pro.h"
#include  "\src\atlanta\define\fcm_def.h"
	/*#include  "\src\atlanta\define\fcm_pro.h"*/
	UBYTE	CheckPollingTxType(void);


#if (PRO_MULTI_LINE == ENABLE)
#include  "\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1997/09/24 */
 #if (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\mntsw_b.h"	/* added by H.Hirao 1999/03/03 */
#include "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
 #endif
#include  "\src\atlanta\define\cl1_def.h"
#include  "\src\atlanta\define\sysmemrx.h"		/* S.Fukui Jun.19,1998 */
#endif /* (PRO_CLASS1 == ENABLE) */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* 1998/09/30 H.Yoshikawa */
#include  "\src\atlanta\define\sysnd.h"
#endif

/* ƒXƒLƒƒƒi[‘—M ¶’[‰e‚ªo‚é‘Îô T.Nose 1998/03/26 */
#include "\src\atlanta\define\idp_def.h"
#if (PRO_SCN_CODEC_TYPE == IDP301)
#include "\src\atlanta\define\idp_pro.h"
#endif

#if (PRO_PRINTER_RX == ENABLE) /* 1999/02/18 by T.Soneoka */
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_c.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#include "\src\atlanta\prt\thermal\define\prn_pro.h"
#endif

#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/07/13 */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
/* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Added by SMuratec —› 2005/11/01 */
#include "\src\atlanta\define\sys_line.h"

/* Œx@FAX Added by SMuratec —› 2005/10/27 */
static	UBYTE	hang_up_check	= 0;
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[‚m‚b‚tŠÖ˜Aƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒWˆ—]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[¬’J³÷]
*************************************************************************/
void	MAN_FromNCU_Task(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	UBYTE	main_rx_mode;
	UWORD	ncu_item;
	UWORD	ncu_message;
	UWORD	ncu_sub_message1;
	UWORD	ncu_sub_message2;
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
	UWORD	is_sendmsg;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* added (PRO_CLASS1 == ENABLE) 1999/05/28 */
	UBYTE	is_receive;	/* added by H.Hirao 1999/05/12 */
#endif
	ncu_item = item;
	ncu_message = message;
	ncu_sub_message1 = sub_message1;
	ncu_sub_message2 = sub_message2;
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
	is_sendmsg = 0;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/10 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
	is_receive = 0;	/* added by H.Hirao 1999/05/12 */
#endif


	/*--------------------------------------------*/
	/** Še‰ñüŠÄ‹ƒ^ƒXƒN‚Ö‚ÌƒƒbƒZ[ƒW‘—M “¯Šú—p */
	/*--------------------------------------------*/
	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	if (ncu_item == FROM_NCU_TASK) {
		snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage);
	}
	else if (ncu_item == FROM_NCU_TELEPHONEOPERATIONTASK) {
		snd_msg(mbxno.NCU_TelephoneOperationTaskSub, &MainTaskMessage);
	}
#if (PRO_DIALIN == ENABLE )
	else if (ncu_item == FROM_NCU_DIALINAUTOSWITCHTASK) {
		snd_msg(mbxno.NCU_DialInAutoSwitchTask, &MainTaskMessage);
	}
#endif
						/*-----------------------*/
	switch (ncu_message) {	/** ”­¶–Û‚É‘Î‚·‚éˆ— */
						/*-----------------------*/
	/*-------------------------------------------------------------------*/
	/*							’…MŒŸoŠÖ˜A							 */
	/*-------------------------------------------------------------------*/
						/*-------------*/
	case MSG_DETECT_CI: /** ‚b‚hŒŸo’† */
						/*-------------*/
		/*------------------------------------------------------------------*/
		/* ”­’…Õ“Ë‰ñ”ğ‚Ìˆ×A‹@Šíó‘Ô‚É‚b‚hŒŸo’†‚ğƒZƒbƒg‚·‚éB				*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚Í’…MŒŸo’†EƒIƒtEƒtƒbƒNŒŸo‘Ò‚¿ó‘Ô	*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚ÍA“àü’Ê˜bó‘Ô‚Å‚Ì’…MŒŸo’†				*/
		/*------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRE_LINE_BUSY;
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/12 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
		if (SYS_CL1_RxEnableFlag) {
			SYS_CalledRequestForDocStore = 1;
		}
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/* ’…M‚É’~Ï‚ª‚Æ‚Ü‚é‚Ì‚ğC³ 1999/02/22 by T.Soneoka */
		if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
			SYS_CalledRequestForDocStore = 1; /* added by H.Hirao 1998/12/28 */
		}
#endif
#if (0)	/* íœ 1997/10/03 Y.Matsukuma */
**#if (PRO_CLASS1 == ENABLE)
**		/* 1997/01/30 by Y.Tanimoto
**		ˆÈ‰º‚Ìif•¶‚ª”²‚¯‚Ä‚¢‚Ü‚µ‚½B
**		if•¶‚ÌˆÓ–¡‚ÍClass1“®ì’†(CIŒŸo’†)‚ğ”»’f‚µ‚Ü‚·B
**		*/
**#if (0) /* Changed by H.Kubo 1997/09/24 */
**		if (SYS_CL1_Status & 0x0010) {
**			MainTaskMessage.Item = FROM_MAIN;
**			MainTaskMessage.Message = CL1_CI_TIMEUP;
**			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
**		}
**#else /* 0 */
**		if (SYS_CL1_Status & CL1_CALLED) {
**			MainTaskMessage.Item = FROM_MAIN;
**			MainTaskMessage.Message = CL1_CI_TIMEUP;
**			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
**		}
**#endif /* 0 */
**#endif /* (PRO_CLASS1 == ENABLE) */
#endif
#if defined(STOCKHM2) /* –{‘Ì–Â“®‚ÌƒeƒXƒg :by SMuratec C.P 2004/09/24 */
		switch (CMN_PresentReceiveMode()) {
		case SYS_FAX_READY:
		case SYS_TEL_FAX_READY:
			if (CHK_RingCount()) {
				CallingBuzzer();
			}
			break;
		case SYS_TEL_READY:
		case SYS_ANS_FAX_READY:
			CallingBuzzer();
			break;
		default:
			break;
		}
#endif
		break;
								/*-----------------------*/
	case MSG_DETECT_CI_TIMEUP:	/** ‚b‚hŒŸo‚s‚‰‚‚…‚t‚ */
								/*-----------------------*/
		/*--------------------------------------------------------------------------*/
		/* ‹@Šíó‘Ô‚©‚ç‚b‚hŒŸo’†‚ğƒNƒŠƒA‚·‚éB										*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚Í‚b‚hŠ„‚è‚İ”­¶‘Ò‚¿EƒIƒtEƒtƒbƒNŒŸo‘Ò‚¿ó‘Ô	*/
		/* ‘½‹@”\“d˜b‚Í“àüŒÄ‚Ño‚µA•Û—¯“]‘—A“àü’Ê˜b‚ÅCIŠ„‚è‚İ‘Ò‚¿				*/
		/*--------------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
#if (PRO_NUMBER_DISPLAY == ENABLE) /*  */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/09/19 H.Yoshikawa */
#endif
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
#endif
#if (PRO_CLASS1 == ENABLE)
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
		if (SYS_CL1_Status & (CL1_CALLED | CL1_DIALIN_CALLED | CL1_FNET_CALLED)) {	/* ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Î‰ */
 #else
		if (SYS_CL1_Status & CL1_CALLED) {	/* if’Ç‰Á	1997/10/03 Y.Matsukuma */
 #endif
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_CI_TIMEUP;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
  #if (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		/*
		** ƒNƒ‰ƒX‚Pƒ\ƒtƒg‚ª‚q‚h‚m‚f‚É‘Î‚µ‚Ä‰“š‚ğ•Ô‚·‘O‚É‚b‚h‚ªƒ^ƒCƒ€ƒAƒbƒv‚µ‚½ê‡A
		** ƒNƒ‰ƒX‚PóM’†ƒtƒ‰ƒO‚ªƒŠƒZƒbƒg‚Å‚«‚È‚¢
		** by H.Hirao 1999/04/02
		*/
		CMN_DisableInterrupt();
		CL1_DualRestrictionStatus &= ~CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒŠƒZƒbƒg */
		CMN_EnableInterrupt();
  #endif
		}
#endif
#if (PRO_CIPHER == ENABLE)
		/* óM—Dæ‚Ì‚½‚ßƒXƒNƒ‰ƒ“ƒuƒ‹‚ğ’†’f‚µ‚Ä‚¢‚½ê‡
		** ‚b‚hŒŸo‚s‚‰‚‚…‚t‚‚Ì‚½‚ß’…M‚µ‚È‚¢‚Ì‚Å
		** ‚±‚±‚ÅƒXƒNƒ‰ƒ“ƒuƒ‹Ä‹N“®‚ğƒZƒbƒg‚µ‚Ü‚· 98/06/11 By T.Fukumoto
		*/
		if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
			SYS_CipherRestartEnable = 1;
		}
#endif
		break;
#if (PRO_CLASS1 == ENABLE)
	case MSG_DETECT_RING :
 #if (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		CMN_DisableInterrupt();
		CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒZƒbƒg */
		SYS_CalledRequestForDocStore = 0;	/* ’…M—v‹ƒtƒ‰ƒOƒŠƒZƒbƒg */
		CMN_EnableInterrupt();
 #endif
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_DETECT_RING;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
	case MSG_DETECT_CALL_TO_FAX_EXT:	/**	Šg’£ƒ‰ƒCƒ“‚b‚h’…MŒŸo	 */
#if (0) /* Šg’£‰ñü‚Í‚O‚˜‚W‚O‚Æ‚µ‚Ä‚İ‚é‚æ‚¤‚É•ÏX‚µ‚Ü‚· by T.Soneoka 1998/03/16 */
//		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
#else
		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0x80, AUTO_RECEIVE);
#endif
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
		if ( (SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW)
			&& ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType())) {
#else /* !defined (KEISATSU) */
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType()) {
#endif /* defined (KEISATSU) */
			if (tskno_NCU_TelephoneOperation != 0xffff) {
				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				is_sendmsg = 1;
			}
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS]  |= SYS_FAXCOM;
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/10/10 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
#endif /* defined (KEISATSU) */
			SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	Šg’£ƒ‰ƒCƒ“’ÊM’†	*/
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  ~SYS_TEL2_OFF_HOOK;
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
#endif /* defined (KEISATSU) */
			/*--------------------------------------*/
			/**		’ÊMƒ^ƒXƒN‹N“®i©“®óMj		*/
			/*--------------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

#if defined (KEISATSU)		/* Œx@FAX Added by SMuratec K.W.Q 2005/09/23 */
			FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;

			if (CMN_CheckScrambleSwOn()) {
				if (CheckIsScrambleOFF()) {
					FCM_ExecutingS1Info.Available = FALSE;
				}
				else {
					FCM_ExecutingS1Info.Available = TRUE;
				}

				if (CheckIsSenyou()) {
					FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
				}
				else {
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
			}
			else {
				FCM_ExecutingS1Info.Available = FALSE;
				FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			}
#endif		/* End of (defined (KEISATSU)) */

			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_AUTO_CALLED;
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
		else {
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/10/10 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
#endif /* defined (KEISATSU) */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
		break;
#endif
									/*-------------------*/
	case MSG_DETECT_CALL_TO_FAX	:	/**	   ‚b‚h’…MŒŸo	 */
	case MSG_DETECT_CALL_TO_TEL	:	/** ‰“Šu©“®Ø‘ÖŒŸo */
									/*-------------------*/
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND ‚Åƒƒ‚ƒŠ[ƒI[ƒo[‚Å’…M‹‘”Û‚ğl—¶Bchanged by H.Kubo 1999/02/26 */
	case MSG_DETECT_CALLED_REQUEST_ND: /** ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC‚Ìî•ñóMŒã‚Ì IR ‚Å’…MŒŸo by H.Kubo 1999/02/26 */
 #endif
/*		main_rx_mode = 1;							'95,11,24 By N.S. for ANZU ICE Start '95,12,21 By N.S.*/
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
		if ( SYB_RxModeSwitch & SYS_AUTO_CALLED_SW ) {
			main_rx_mode = SYS_FAX_READY;
		}
		else {
			main_rx_mode = SYS_TEL_READY;
		}
#else /* !defined (KEISATSU) */
		main_rx_mode = CMN_PresentReceiveMode();
#endif /* defined (KEISATSU) */
		if(( main_rx_mode == SYS_FAX_READY	   )
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
 #if 0 /* Changed by H.Kubo 1998/11/27 */
		|| ( main_rx_mode == SYS_MODEM_DIALIN_READY)
 #else
		|| (( main_rx_mode == SYS_MODEM_DIALIN_READY) && !NCU_ND_ShuldSwitchToDialin())
 #endif
#endif
		|| ( main_rx_mode == SYS_FAX_TEL_READY )	/* '95,12,27 BY N.S. */
		|| ( main_rx_mode == SYS_TEL_FAX_READY )){
			/*------------------------------------------------------------------------------------------------------*/
			/* ‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†E’ÊMÀs’†EƒvƒŠƒ“ƒ^g—p’†‚ğƒZƒbƒg‚·‚éB					*/
			/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡														*/
			/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																*/
			/*		‘½‹@”\“d˜b‹@”\‚ª“®ì‚µ‚Ä‚¢‚È‚¢‚Ì‚Å SYS_MachineStatus[SYS_MACHINE_STATUS]‚ÌƒNƒŠƒA‚Í•s•K—v‚Ì‚Í‚¸B*/
			/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡															*/
			/*		“àü’Ê˜bó‘Ô‚Å‚Ì’…MBˆ—‚·‚é“à—e‚È‚µ															*/
			/*------------------------------------------------------------------------------------------------------*/
#if (0) /* óMŒ´eƒ|[ƒŠƒ“ƒOæ‚èo‚µC³•ª by T.Soneoka 1997/02/21 */
**												/*-------------------------*/
**			if( CMN_CheckAutoCalledEnable()) {	/** ’…Mˆ—Às‰Â”\‚Ìê‡ */
**												/*-------------------------*/
#endif
/* óMŒ´eŠÇ—•û–@•ÏX‚É‚Â‚«‚Q‰ñüd—l‚Æ“¯‚¶ŠÖ”‚ğŒÄ‚Ô—l‚É•ÏXiŠÖ”‚Ì‚È‚©‚ÅA‚Q‰ñüd—l‚Ìˆ—‚ğ‚µ‚Ä‰º‚³‚¢
** 1997/03/19  By T.Yamaguchi	”ƒ–Š‚ ‚é
*/
			/* SYB_MemoryRxPrintWritePoint = (UBYTE)CMN_CheckMultiLineReceiveNumber((UWORD)0, AUTO_RECEIVE); 1997/11/20  By T.Yamaguchi */
			SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			if (QueryAutoCalledEnable(0)) { /* changed by H.Hirao 1998/12/26 */
	#else
	  		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || QueryPRxEnable()) {
	#endif
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.4 K.Kawata */
	  		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || (QueryPRxEnable() && QueryWarpAndSecurityDisable())) {
    #else
			if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType()) {
    #endif
  #endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
				if (tskno_NCU_TelephoneOperation != 0xffff) {
					del_tsk(&tskno_NCU_TelephoneOperation);
					SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
					is_sendmsg = 1;
				}
#endif
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS]  |= SYS_FAXCOM;
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &=  ~SYS_TEL1_OFF_HOOK;
#else /* !defined (KEISATSU) */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
#endif /* defined (KEISATSU) */
				SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	•W€ƒ‰ƒCƒ“’ÊM’†	*/
#endif
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/12 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
				CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒZƒbƒg */
  #endif
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
				SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
	#endif
				/*
				** ƒvƒŠƒ“ƒ^óM‚·‚é‰Â”\«‚Ì‚ ‚é‚Æ‚«‚¾‚¯SYS_PRINTER_BUSY‚ğƒZƒbƒg‚µ‚Ü‚·
				** 1999/02/18 by T.Soneoka
				*/
#if (0)
**				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
#else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
				}
#endif
  #endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
				PRN_ChechRxPrintCallProc();
#endif

 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND ‚Åƒƒ‚ƒŠ[ƒI[ƒo[‚Å’…M‹‘”Û‚ğl—¶Bchanged by H.Kubo 1999/02/26 */
				if (ncu_message == MSG_DETECT_CALLED_REQUEST_ND) {
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_EXIT;
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage); /* NCU_Task ‚Ì—Dæ‡ˆÊ‚ªã‚¾‚Æ‰¼’è‚µ‚Ü‚·B */
				}
 #endif
				/*--------------------------------------*/
				/**		’ÊMƒ^ƒXƒN‹N“®i©“®óMj		*/
				/*--------------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 				CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
				CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

#if defined (KEISATSU)		/* Œx@FAX Added by SMuratec K.W.Q 2005/09/23 */
				FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;

				if (CMN_CheckScrambleSwOn()) {
					if (CheckIsScrambleOFF()) {
						FCM_ExecutingS1Info.Available = FALSE;
					}
					else {
						FCM_ExecutingS1Info.Available = TRUE;
					}

					if (CheckIsSenyou()) {
						FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
					}
					else {
						FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
					}
				}
				else {
					FCM_ExecutingS1Info.Available = FALSE;
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
#endif		/* End of (defined (KEISATSU)) */

				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = SYS_AUTO_CALLED;
				snd_msg(mbxno.FCM_Task, &MainTaskMessage);
			}
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
			/* ‘ãsóM•s‰Â‚Å‚à‚o‚bóM‰Â”\‚È‚ç©“®óMˆ—‚ÖˆÚs */
			else if (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS]  |= SYS_FAXCOM;

 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND ‚Åƒƒ‚ƒŠ[ƒI[ƒo[‚Å’…M‹‘”Û‚ğl—¶Bchanged by H.Kubo 1999/02/26 */
				if (ncu_message == MSG_DETECT_CALLED_REQUEST_ND) {
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_EXIT;
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage); /* NCU_Task ‚Ì—Dæ‡ˆÊ‚ªã‚¾‚Æ‰¼’è‚µ‚Ü‚·B */
				}
 #endif

				/*--------------------------------------*/
				/**		’ÊMƒ^ƒXƒN‹N“®i©“®óMj		*/
				/*--------------------------------------*/
				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = SYS_AUTO_CALLED;
				snd_msg(mbxno.FCM_Task, &MainTaskMessage);
			}
#endif
			else {
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/26 */
				/* ƒƒ‚ƒŠ‚Í—L‚é‚Ì‚ÉAŒ´e’~Ï’†‚ÍA’…M‚µ‚È‚¢ê‡A‘ãsóMŠÇ—ƒoƒbƒtƒ@‚ğ‚Â‚©‚İ‚Á‚Ï‚È‚µ‚É‚È‚é
				*/
				if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;
				}
  #endif

 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ND ‚Åƒƒ‚ƒŠ[ƒI[ƒo[‚Å’…M‹‘”Û‚ğl—¶Bchanged by H.Kubo 1999/02/26 */
				if (ncu_message == MSG_DETECT_CALLED_REQUEST_ND) {/* NCU_Task ‚É‚Íˆø‚«‘±‚«ŒÄ‚Ño‚µ‰¹ŒŸo‚ğ‘±s‚µ‚Ä‚à‚ç‚¤B*/
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_TEL_FROM_MAIN; /* MSG_EXIT ‚Å‚È‚¯‚ê‚Î‚È‚ñ‚Å‚à‚¢‚¢B */
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage);
				}
				else {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
							SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
						}
					}
					else {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
#else /* !defined (KEISATSU) */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
						/*---------------------------------------*/
						/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
						/*---------------------------------------*/
						cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
						SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
				}
 #else
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
  #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/19 K.Kawata */
				if (CL1_ExtFunctionEnableFlag == 1) {
					SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM;	/** CLASS1“®ì’†ƒNƒŠƒA	*/
					CL1_ExtFunctionEnableFlag = 0;
				}
  #endif
					/*---------------------------------------*/
					/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
					/*---------------------------------------*/
					cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
					SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
 #endif
			}
			break;
		}
#if defined(JPN)
	#if (PRO_DIALIN == ENABLE)
		else {
			/*------------------------------------------------------------------------------------------------------*/
			/* ‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†Eƒ_ƒCƒ„ƒ‹EƒCƒ“Às’†‚ğƒZƒbƒg‚·‚éB						*/
			/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡														*/
			/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																*/
			/*		‘½‹@”\“d˜b‹@”\‚ª“®ì‚µ‚Ä‚¢‚È‚¢‚Ì‚Å SYS_MachineStatus[SYS_MACHINE_STATUS]‚ÌƒNƒŠƒA‚Í•s•K—v‚Ì‚Í‚¸B*/
			/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡															*/
			/*		“àü’Ê˜bó‘Ô‚Å‚Ì’…MBˆ—‚·‚é“à—e‚È‚µ															*/
			/*------------------------------------------------------------------------------------------------------*/
  #if (0) /* 1997/12/24 s.takeuchi -> 1998/01/05 Y.Murata */
  //‘ãsóMƒtƒ‹‚Ì‚É“d˜b‰ñü‚ÌŒÄ‚Ño‚µ/ƒ_ƒCƒ„ƒ‹ƒCƒ“e“W‰ñü‚Å‚ÌóM‚ª‚Å‚«‚È‚¢‚Ì‚Å
  //‚±‚±(‰¼’…M‘O)‚Å‚ÍóM‰Â”\‚©‚Ç‚¤‚©‚ÍŒ©‚È‚¢(–{’…M‚Ì‚ÉŒ©‚é)
  //		/* POPLAR•ÏX 1997/03/19  By T.Yamaguchi */
  //		/* SYB_MemoryRxPrintWritePoint = (UBYTE)CMN_CheckMultiLineReceiveNumber((UWORD)0, AUTO_RECEIVE); */
  //		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
  //		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType()) {
  #endif
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_DIAL_IN;
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by H.Kubo 1997/12/15 */

				/* ƒ_ƒCƒ„ƒ‹ƒCƒ“‰¼’…M’†‚É‘—M‚µ‚æ‚¤‚Æ‚·‚é‚ÆAƒŠƒZƒbƒg‚É”ò‚ÔB
				** =>‰ñü‚ªg‚¦‚é‚©‚Ç‚¤‚©‚ÌŠÖ”“à‚ÅAhPRE_LINE_BUSYh‚ğŒ©‚Ä‚¢‚é‚ªAÀÛ‚É‚ÍƒZƒbƒg‚³‚ê‚éêŠ‚ª‚È‚¢B
				**   ‚æ‚Á‚ÄA‰ñüg—p‰Â‚Æ”»’f‚µ‚Ä‚µ‚Ü‚¢AŒ‹‰Ê“I‚É‚Íƒ‚ƒfƒ€“à‚ÅWai_Oneshot‚ğg‚Á‚Ä‚¢‚é‚½‚ßA‚»‚±‚Å”ò‚ñ‚Å‚µ‚Ü‚¤B
				**   ‘Îô‚Æ‚µ‚Ä‚ÍAƒ_ƒCƒ„ƒ‹ƒCƒ“ˆêŸ‰“šˆ—‚ğ‚·‚é‘O‚ÉhPRE_LINE_BUSYh‚ğƒZƒbƒg‚µ‚Ä‚¨‚«‚Ü‚·B
				**   ‚±‚Ìƒrƒbƒg‚ğƒŠƒZƒbƒg‚·‚é‚Ì‚ÍA
				**        1.–{“–‚É‰ñü‚ğg—p‚·‚é‚Æ‚«i’ÊMA’Ê˜b“™j
				**        2.ƒ_ƒCƒ„ƒ‹ƒCƒ“‰¼’…M‚ğ‚ ‚«‚ç‚ß‚é‚Æ‚«
				** by O.Kimoto 1998/04/29
				*/
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRE_LINE_BUSY;

				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
				SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	•W€ƒ‰ƒCƒ“’ÊM’†	*/
#endif
				/*----------------------------------------------*/
				/**		ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‹N“®		*/
				/*----------------------------------------------*/
				cre_tsk(&tskno_NCU_DialInAutoSwitchTask, TSK_NCU_DIALINAUTOSWITCHTASK, 0);

  #if 0	/* 1998/01/05 Y.Murata */
  //‘ãsóMƒtƒ‹‚Ì‚É“d˜b‰ñü‚ÌŒÄ‚Ño‚µ/ƒ_ƒCƒ„ƒ‹ƒCƒ“e“W‰ñü‚Å‚ÌóM‚ª‚Å‚«‚È‚¢‚Ì‚Å
  //‚±‚±(‰¼’…M‘O)‚Å‚ÍóM‰Â”\‚©‚Ç‚¤‚©‚ÍŒ©‚È‚¢(–{’…M‚Ì‚ÉŒ©‚é)
  //		}
  //		else {
  //			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
  //				/*---------------------------------------*/
  //				/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
  //				/*---------------------------------------*/
  //				cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
  //				SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
  //		}
  #endif
			break;
		}
	#endif
#endif
		break;
#if defined(JPN)
	case MSG_DETECT_F_NET:	/** ‚e–Ô’…Mi‚P‚R‚O‚O‚g‚šjŒŸo */
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
	case MSG_DETECT_F_NET_EXT:	/** Šg’£ƒ‰ƒCƒ“‚e–Ô’…Mi‚P‚R‚O‚O‚g‚šjŒŸo */
#endif
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1 F–Ô‘Î‰ S.Fukui June 19,1998  */
		if ( CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK ) {		/* ‚o‚bóM */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRE_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_CL1_FNET_RING;
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/05/11 */
			CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒZƒbƒg */
			SYS_CalledRequestForDocStore = 0;
  #endif
			/*
			* F–Ô‚Ì1300HzŒÄ‚Ño‚µ‚ğCL1_Task‚É’Ê’m‚·‚é
			* (RS-232C‚Ö‚Ì"RING"‘—o‚ÍCL1_Task‚Ås‚¤)
			*/
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_DETECT_RING_FNET;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
		}
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/11 */
		if ((CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_SCANNER_IN_USE)
		 || (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_PRINTER_IN_USE)) {
			SYS_CalledRequestForDocStore = 1;
			/*  PC-FAX“®ì’†‚Å‚àClass1‚ª¶‚«‚Ä‚¢‚ê‚ÎFAX‘¤‚É’…M‚³‚¹‚È‚¢‚½‚ß‚ÉNCU_Task‚ğÄ‹N“®‚·‚é */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;
			break;
		}
		if ( CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING ) {
			/*  PC-FAX“®ì’†‚Å‚àClass1‚ª¶‚«‚Ä‚¢‚ê‚ÎFAX‘¤‚É’…M‚³‚¹‚È‚¢‚½‚ß‚ÉNCU_Task‚ğÄ‹N“®‚·‚é */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;
			break;
		}
  #else
		if ( CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING ) {
			/*  PC-FAX“®ì’†‚Å‚àClass1‚ª¶‚«‚Ä‚¢‚ê‚ÎFAX‘¤‚É’…M‚³‚¹‚È‚¢‚½‚ß‚ÉNCU_Task‚ğÄ‹N“®‚·‚é */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;
			break;
		}
  #endif
 #endif	/* PRO_CL1_TELFAX_LAN == ENABLE */
		/*------------------------------------------------------------------------------------------------------*/
		/* ‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†E’ÊMÀs’†EƒvƒŠƒ“ƒ^g—p’†‚ğƒZƒbƒg‚·‚éB					*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡														*/
		/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																*/
		/*		‘½‹@”\“d˜b‹@”\‚ª“®ì‚µ‚Ä‚¢‚È‚¢‚Ì‚Å SYS_MachineStatus[SYS_MACHINE_STATUS]‚ÌƒNƒŠƒA‚Í•s•K—v‚Ì‚Í‚¸B*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡															*/
		/*		“àü’Ê˜bó‘Ô‚Å‚Ì’…MBˆ—‚·‚é“à—e‚È‚µ															*/
		/*------------------------------------------------------------------------------------------------------*/
#if (PRO_CIPHER == ENABLE)
		/* óM—Dæİ’è‚ª‚n‚m‚É‚È‚Á‚Ä‚¢‚é‚Æ‚«‚ÉƒXƒNƒ‰ƒ“ƒuƒ‹ˆ—’†‚È‚çAƒXƒNƒ‰ƒ“ƒuƒ‹‚Ì’†’fˆ—‚ğs‚¢‚Ü‚·
		** 98/06/16 By T.Fukumoto
		*/
		if (CMN_CheckScrambleBusy()) {
			if ((!CHK_UNI_PriorityReceive()) && (!SYS_CipherInterruptionOn) && (!CipherStopOn)) {
				SYS_CipherInterruptionOn = SYS_CipherComExec;
				SYS_BackupCipherStatus = SYS_MachineStatus[SYS_CIPHER_STATUS];/*By Y.Suzuki 1998/08/12*/
				CipherStopOn = 1;
			}
		}
#endif
		/* POPLAR•ÏX 1997/03/19  By T.Yamaguchi */
		/* SYB_MemoryRxPrintWritePoint = (UBYTE)CMN_CheckMultiLineReceiveNumber((UWORD)0, AUTO_RECEIVE); 1997/11/20  By T.Yamaguchi */
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
#if (0) /* Šg’£‰ñü‚Í‚O‚˜‚W‚O‚Æ‚µ‚Ä‚İ‚é‚æ‚¤‚É•ÏX‚µ‚Ü‚· by T.Soneoka 1998/03/16 */
//		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
#else
		if (ncu_message == MSG_DETECT_F_NET) {
			SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
		}
		else {
			SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0x80, AUTO_RECEIVE);
		}
#endif
#else
		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
#endif

  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if (QueryAutoCalledEnable(0)) { /* changed by H.Hirao 1998/12/26 */
	#else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || QueryPRxEnable()) {
	#endif
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.8 K.Kawata */
  		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || (QueryPRxEnable() && QueryWarpAndSecurityDisable())) {
    #else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType()) {
    #endif
  #endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
			if (tskno_NCU_TelephoneOperation != 0xffff) {
				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				is_sendmsg = 1;
			}
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
			if (ncu_message == MSG_DETECT_F_NET) {	/** •W€ƒ‰ƒCƒ“‚e–Ô’…Mi‚P‚R‚O‚O‚g‚šjŒŸo */
				SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	•W€ƒ‰ƒCƒ“’ÊM’†	*/
			}
			else {
				SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	Šg’£ƒ‰ƒCƒ“’ÊM’†	*/
			}
#endif
			SYS_F_Net_AutoCalledDisableFlag = 0;							/* '95,11,17 By N.S. for ANZU */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
	#endif
			/*
			** ƒvƒŠƒ“ƒ^óM‚·‚é‰Â”\«‚Ì‚ ‚é‚Æ‚«‚¾‚¯SYS_PRINTER_BUSY‚ğƒZƒbƒg‚µ‚Ü‚·
			** 1999/02/18 by T.Soneoka
			*/
#if (0)
**			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
#else
			if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			}
#endif
  #endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
			PRN_ChechRxPrintCallProc();
#endif
			/*--------------------------------------*/
			/**		’ÊMƒ^ƒXƒN‹N“®i‚e–ÔóMj		*/
			/*--------------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_FNET_AUTO_CALLED;
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
		else {
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/26 */
			/* ƒƒ‚ƒŠ‚Í—L‚é‚Ì‚ÉAŒ´e’~Ï’†‚ÍA’…M‚µ‚È‚¢ê‡A‘ãsóMŠÇ—ƒoƒbƒtƒ@‚ğ‚Â‚©‚İ‚Á‚Ï‚È‚µ‚É‚È‚é
			*/
			if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
				SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;
			}
  #endif
#if (PRO_CIPHER == ENABLE)
			/* óM—Dæ‚Ì‚½‚ßƒXƒNƒ‰ƒ“ƒuƒ‹‚ğ’†’f‚µ‚Ä‚¢‚½ê‡Aƒƒ‚ƒŠƒtƒ‹‚Ìê‡óM‚µ‚È‚¢‚Ì‚Å
			** ‚±‚±‚ÅƒXƒNƒ‰ƒ“ƒuƒ‹Ä‹N“®‚ğƒZƒbƒg‚µ‚Ü‚· 98/06/16 By T.Fukumoto
			*/
			if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
				SYS_CipherRestartEnable = 1;
			}
#endif
			SYS_F_Net_AutoCalledDisableFlag = 1;							/* '95,11,17 By N.S. for ANZU */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
		break;

 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* Class1 F–Ô‘Î‰ S.Fukui June 19,1998  */
	case MSG_DETECT_F_NET_TIMEOUT:
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_FNET_TIMEUP;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
 #endif

#endif
	/*-----------------------------------------------------------------------*/
	/*					‚n‚gó‘Ô•Ï‰»ŒŸoE“]‘—óMŠÖ˜A						 */
	/*-----------------------------------------------------------------------*/
									/*-------------------------------*/
	case MSG_DETECT_TEL1_OFF_HOOK:	/** •t‘®“d˜b‚n‚e‚e@‚g‚n‚n‚jŒŸo */
	case MSG_DETECT_TEL2_OFF_HOOK:	/** ŠO•t“d˜b‚n‚e‚e@‚g‚n‚n‚jŒŸo */
									/*-------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*------------------------------------------------------------------------------------------------------*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡														*/
		/* ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡													*/
		/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN^ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒNI—¹“¯ŠúÏ								*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†E‘½‹@”\“d˜bg—p’†E‚g‚n‚n‚jó‘Ô‚ğƒZƒbƒg‚·‚éB		*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡															*/
		/*		•Û—¯ó‘Ô‚Ìê‡A‹@Šíó‘Ô‚©‚ç•Û—¯ó‘Ô‚ğƒNƒŠƒA‚·‚éB												*/
		/*------------------------------------------------------------------------------------------------------*/
										/*-------------------------------------------------*/
		if (ncu_item == FROM_NCU_TASK) {	/** ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡ */
										/*-------------------------------------------------*/
								/*---------------------------------*/
			if (HungUpCheck) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒN‚Ìê‡ */
								/*---------------------------------*/
				 /*---------------------------------*/
				 /** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰[‚ğƒZƒbƒg */
				 /*---------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
 #if defined(KEISATSU)	/* Œx@FAX DVT Modify by SMuratec ‰Ä 2005/11/21 */
 				if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {	/**	TEL1ƒIƒtƒtƒbƒN	*/
					if (hang_up_check == SYS_STD_LINE_COM) {	/**	•W€‰ñü‚Å‘—M	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
						Hangup_Line |= SYS_LINE_KANYU_HANGUP;
					}
				}
				else {	/**	TEL‚QƒIƒtƒtƒbƒN	*/
					if ((hang_up_check == SYS_STD_LINE_COM) 	/** •W€ƒ‰ƒCƒ“‚Å‘—M	*/
					&&  (!CHK_Phone2ExtLineOn())) {	/**	PHONE2ƒŠƒŒ[İ’è‚ª•W€ƒ‰ƒCƒ“‚Ìê‡	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
						Hangup_Line |= SYS_LINE_KANYU_HANGUP;
					}
 					if ((hang_up_check == SYS_EXT_LINE_COM) /** Šg’£ƒ‰ƒCƒ“‚Å‘—M	*/
					&&  (CHK_Phone2ExtLineOn())) {	/**	PHONE2ƒŠƒŒ[İ’è‚ªŠg’£ƒ‰ƒCƒ“‚Ìê‡	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
						Hangup_Line |= SYS_LINE_KEIDEN_HANGUP;
					}
				}
 #else
				if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {	/**	TEL1ƒIƒtƒtƒbƒN	*/
					if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	•W€‰ñü‚Å‘—M	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
					}
				}
				else {	/**	TEL‚QƒIƒtƒtƒbƒN	*/
					if ((SYS_InternalLineNumber == SYS_STD_LINE_COM) 	/** •W€ƒ‰ƒCƒ“‚Å‘—M	*/
					&&  (!CHK_Phone2ExtLineOn())) {	/**	PHONE2ƒŠƒŒ[İ’è‚ª•W€ƒ‰ƒCƒ“‚Ìê‡	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
					}
					if ((SYS_InternalLineNumber == SYS_EXT_LINE_COM) /** Šg’£ƒ‰ƒCƒ“‚Å‘—M	*/
					&&  (CHK_Phone2ExtLineOn())) {	/**	PHONE2ƒŠƒŒ[İ’è‚ªŠg’£ƒ‰ƒCƒ“‚Ìê‡	*/
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
					}
				}
 #endif
#else
				SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
#endif
				/*---------------------------------------------*/
				/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰[EƒuƒU[‹N“® TBD OPR */
				/*---------------------------------------------*/
			}
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= (SYS_TELEPHONE);
			if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
			}
#if (PRO_ECO_MODE == ENABLE) /* 2002/09/25 By M.Maeda */
 #if (1) /* ƒJƒo[ƒI[ƒvƒ“‚Å‚Q‚S‚u‚ğ‚n‚m‚µ‚È‚¢‚æ‚¤‚É‚·‚é By M.Maeda 2003/01/22 */
			MAN_ChangeEcoMode(0);
 #else
//			MAN_ChangeEcoMode(FALSE);
 #endif
#endif
			/*------------------------------------------------------*/
			/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
			/*------------------------------------------------------*/
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
			if (DEBUG_NumberDisplay) {
				if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {	/**	TEL1ƒIƒtƒtƒbƒN	*/
					if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
				else {	/**	TEL‚QƒIƒtƒtƒbƒN	*/
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			}
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
			cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		}													/*---------------------------------------------*/
		else if (ncu_item == FROM_NCU_TELEPHONEOPERATIONTASK) { /** ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡ */
															/*---------------------------------------------*/
#if(0)/* V851 TEL2‚ªŠg’£‰ñü Ú‘±‚Ìê‡ATEL2‚ÌµÌÌ¯¸‚Å•Û—¯‰ğœ‚µ‚È‚¢ By Y.Suzuki 2002/08/22*/
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
#endif
			if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);			/* V851 ã‚©‚çˆÚ“® By Y.Suzuki 2002/08/22 */
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/28 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2ƒŠƒŒ[İ’è‚ª•W€ƒ‰ƒCƒ“‚Ìê‡	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_HOOK_KEY_OFF_HOOK);	/* Add by TH92115 1994/06/01 */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL2_OFF_HOOK);		/* Add by TH92115 1994/07/04 */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_BRANCH_OFF_HOOK);	/* Add by TH92115 1995/03/16 */
				}
				else {
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
							SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
						}
					}
					/* Œx@FAX DVT Added by SMuratec —› 2005/11/18 */
					if (HungUpCheck) {
						if (hang_up_check == SYS_STD_LINE_COM) {	/**	•W€‰ñü‚Å‘—M	*/
							SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
							Hangup_Line |= SYS_LINE_KANYU_HANGUP;
						}
					}
#endif /* defined (KEISATSU) */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
				}
#else
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_HOOK_KEY_OFF_HOOK);	/* Add by TH92115 1994/06/01 */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL2_OFF_HOOK);		/* Add by TH92115 1994/07/04 */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_BRANCH_OFF_HOOK);	/* Add by TH92115 1995/03/16 */
#endif
			}
			else { /* ncu_message == MSG_DETECT_TEL2_OFF_HOOK */
				/*----------------------------------------------------------------
				** ‚s‚d‚k‚Q‚à‚s‚d‚k‚P‚Ìˆ—‚É“ˆê  By M.Tachibana 1997/09/25 3line
				*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/28 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2ƒŠƒŒ[İ’è‚ª•W€ƒ‰ƒCƒ“‚Ìê‡	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);/* V851 ã‚©‚çˆÚ“® By Y.Suzuki 2002/08/22 */
					if (CHK_UNI_TEL2_TEL1Action()) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_HOOK_KEY_OFF_HOOK);
					}
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK);
				}
				else {
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
							SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
						}
					}
					/* Œx@FAX DVT Added by SMuratec —› 2005/11/18 */
					if (HungUpCheck) {
						if (hang_up_check == SYS_EXT_LINE_COM) {	/**	•W€‰ñü‚Å‘—M	*/
							SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
							Hangup_Line |= SYS_LINE_KEIDEN_HANGUP;
						}
					}
#endif /* defined (KEISATSU) */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
				}
#else
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);/* V851 ã‚©‚çˆÚ“® By Y.Suzuki 2002/08/22 */
				if (CHK_UNI_TEL2_TEL1Action()) {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_HOOK_KEY_OFF_HOOK);	/* Add by TH92115 1994/06/01 */
				}
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK);		/* Add by TH92115 1994/07/04 */
#endif
			}
		}
#if (PRO_DIALIN == ENABLE)
				/*-------------------------------------------------------*/
		else {	/** ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡ */
				/*-------------------------------------------------------*/
			/*SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY; 1998/01/05 Y.Murata */	/** ƒ}ƒ‹ƒ`‰ñüd—l By M.Tachibana 1997/10/04 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_DIAL_IN);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_TELEPHONE;
			if (ncu_message == MSG_DETECT_TEL1_OFF_HOOK) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
			}
			/*------------------------------------------------------*/
			/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
			/*------------------------------------------------------*/
			cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		}
#endif
#if (PRO_CLASS1 == ENABLE)	/* by Y.Tanimoto */
		/*------------------------------------------------------*/
		/*	Class1‚ÌƒXƒe[ƒ^ƒX‚ğ‰ğœ‚³‚¹‚Ü‚·					*/
		/*------------------------------------------------------*/
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
		if (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED)) {
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_DETECT_OFF_HOOK;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
 #else
		if (SYS_CL1_Status & 0x0010) {
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_DETECT_OFF_HOOK;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
 #endif
#endif
		break;
#if (PRO_BRANCH_RX == ENABLE)
	#if (PRO_CPU == SH7043)				/*-------------------*/
	case MSG_BRC_LINE_VOLT_CHK_START:	/** ‰ñü“dˆ³‘ª’èŠJn */
										/*-------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_BRC_LINE_VOLT_CHK;
		SYS_MachineStatus[SYS_RESOURCE_STATUS]	  |= SYS_LINE_BUSY;
		break;
										/*-------------------*/
	case MSG_BRC_LINE_VOLT_CHK_END	:	/** ‰ñü“dˆ³‘ª’èI—¹ */
										/*-------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~( SYS_BRC_LINE_VOLT_CHK );
		SYS_MachineStatus[SYS_RESOURCE_STATUS]	  &= ~( SYS_LINE_BUSY );
		break;
										/*-----------------------------------------------------*/
	case MSG_NO_LINE_CHK_START:			/** ‰ñü“dˆ³‘ª’è’†‰ñü”²‚¯ŒŸoA‰ñüÚ‘±‘Ò‚¿ó‘Ô‚ÌŠJn */
										/*-----------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_NO_LINE;
		break;
										/*-----------------------------------------------------*/
	case MSG_NO_LINE_CHK_END  :			/** ‰ñü“dˆ³‘ª’è’†‰ñü”²‚¯ŒŸoA‰ñüÚ‘±‘Ò‚¿ó‘Ô‚ÌI—¹ */
										/*-----------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_NO_LINE);
		break;
	#endif
										/*-----------------------------------*/
	case MSG_DETECT_BRN_OFF_HOOK:		/** ƒuƒ‰ƒ“ƒ`“d˜b‚n‚e‚e@‚g‚n‚n‚jŒŸo */
										/*-----------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*------------------------------------------------------------------------------------------------------*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡														*/
		/* ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡													*/
		/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†E‘½‹@”\“d˜bg—p’†Eƒuƒ‰ƒ“ƒ`g—p’†‚ğƒZƒbƒg‚·‚éB		*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡															*/
		/*		•Û—¯ó‘Ô‚Å“àü’Ê˜b’†‚Å‚È‚¢ê‡A‹@Šíó‘Ô‚©‚ç•Û—¯ó‘Ô‚ğƒNƒŠƒA‚·‚éB								*/
		/*------------------------------------------------------------------------------------------------------*/
										/*-------------------------------------------*/
		if (ncu_item == FROM_NCU_TASK) {	/** ‘Ò‹@ó‘ÔŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡ */
										/*-------------------------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= (SYS_TELEPHONE);
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_BRANCH_OFF_HOOK);
			/*------------------------------------------------------*/
			/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
			/*------------------------------------------------------*/
			cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		}
		else {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
			if(!( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM )){
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
			}
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_BRANCH_OFF_HOOK);
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TAD);	/* QAT1 1994/09/01 by TH92115 */
		}
		break;
#endif										/*---------------------------------------------------------------*/
	case MSG_DETECT_TRANSFER_TEL_EXIT:		/** “]‘—óM^‰¼’…MŒã‚Ì’…M‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚ªI—¹‚·‚éê‡ */
											/*---------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*----------------------------------------------------------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡																*/
		/*		‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹“¯ŠúÏ																		*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†E‘½‹@”\“d˜bg—p’†‚Ì‘SƒXƒe[ƒ^ƒX‚ğƒNƒŠƒA‚µ									*/
		/*		‰ñüg—p’†E’ÊMÀs’†EƒvƒŠƒ“ƒ^g—p’†‚ğƒZƒbƒg‚·‚éB												*/
		/*----------------------------------------------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) { /* •W€ƒ‰ƒCƒ“óM */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
		}
		else {	/* Šg’£ƒ‰ƒCƒ“óM */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
		}
#else /* !defined (KEISATSU) */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
#endif /* defined (KEISATSU) */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
		/* POPLAR•ÏX 1997/03/19  By T.Yamaguchi */
		/* SYB_MemoryRxPrintWritePoint = (UBYTE)CMN_CheckMultiLineReceiveNumber((UWORD)0, AUTO_RECEIVE); 1997/11/20  By T.Yamaguchi */
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
#if (0) /* Šg’£‰ñü‚Í‚O‚˜‚W‚O‚Æ‚µ‚Ä‚İ‚é‚æ‚¤‚É•ÏX‚µ‚Ü‚· by T.Soneoka 1998/03/16 */
//		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
#else
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
			SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
		}
		else {
			SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0x80, AUTO_RECEIVE);
		}
#endif
#else
		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
#endif

#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
 #if (PRO_RS_INTERNAL == ENABLE)	/* SH7043“à‘ ‚ÌƒVƒŠƒAƒ‹—LŒø */
		if ((CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING) 			/* PC/FAX óM•s‰Â */
		|| (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_SCANNER_IN_USE)	/* ƒXƒLƒƒƒ“’†‚Ì‚½‚ßóM“®ì‹Ö~ */
		|| (CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING_PRINTER_IN_USE)	/* ƒvƒŠƒ“ƒg’†‚Ì‚½‚ßóM“®ì‹Ö~ */
		|| ((CL1_CheckReceiveByFaxOrPC() != PC_RECEIVE_OK)			/* FAXóM‰Â”\‚Å‘ãsóM•s‰Â‚Ìê‡ */
			&& (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX))) {
 #else
		if ((CL1_CheckReceiveByFaxOrPC() == NO_RECEIVING) 			/* PC/FAX óM•s‰Â */
		|| ((CL1_CheckReceiveByFaxOrPC() != PC_RECEIVE_OK)			/* FAXóM‰Â”\‚Å‘ãsóM•s‰Â‚Ìê‡ */
			&& (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX))) {
 #endif

			ClearMemoryRxSetting();		/* SYS_MEMORY_RX_SETTING ‚Å‘ãsóMŠÇ—ƒe[ƒuƒ‹‚ğŠm•Û‚µ‚Ä‚¢‚½‚ç
										** SYS_MEMORY_RX_EMPTY ‚É–ß‚· */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
		else {														/* PC/FAXóM‰Â”\‚Èê‡ */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;
			/*------------------------------------------*/
			/**		’ÊMƒ^ƒXƒN‹N“®i“]‘—©“®óMj		*/
			/*------------------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
**  #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
**  #endif
#else
			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_TRANSFER_AUTO_CALLED;
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
		break;
#else
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if (QueryAutoCalledEnable(1)) { /* changed by H.Hirao 1998/12/26 */
	#else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || QueryPRxEnable()) {
	#endif
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.4 K.Kawata */
	  	if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || (QueryPRxEnable() && QueryWarpAndSecurityDisable())) {
    #else
		if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX /**|| CheckPollingTxType() **/) {	/* 1999.3.19 K.Kawata CheckPollingTxType() ’Ç‰Á */
    #endif
  #endif
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
	#endif
			/*
			** ƒvƒŠƒ“ƒ^óM‚·‚é‰Â”\«‚Ì‚ ‚é‚Æ‚«‚¾‚¯SYS_PRINTER_BUSY‚ğƒZƒbƒg‚µ‚Ü‚·
			** 1999/02/18 by T.Soneoka
			*/
#if (0)
**			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
#else
			if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			}
#endif
  #endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
			PRN_ChechRxPrintCallProc();
#endif
			/*------------------------------------------*/
			/**		’ÊMƒ^ƒXƒN‹N“®i“]‘—©“®óMj		*/
			/*------------------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
**  #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
**  #endif
#else
			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif


			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_TRANSFER_AUTO_CALLED;
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/08/16 */
			if (NCU_SpecialReceiveFlag) {
				NCU_SpecialReceiveFlag = FALSE;
				FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_ISSEI;
				MainTaskMessage.Message = SYS_ISSEI_RX;
			}
			else {
				FCM_ExecutingS1Info.Protocol = SYS_PROTOCOL_KOBETSU;				
			}

			if (CheckIsScrambleOFF() || (CMN_CheckScrambleSwOn() == FALSE)) {
				FCM_ExecutingS1Info.Available = FALSE;
				FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
			}
			else {
				FCM_ExecutingS1Info.Available = TRUE;
				
				if (CheckIsSenyou()) {
					FCM_ExecutingS1Info.Method = SYS_S1_SENYO;
				}
				else {
					FCM_ExecutingS1Info.Method = SYS_S1_KYOTSU;
				}
			}
#endif /* defined (KEISATSU) */
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
		else {
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/26 */
			/* ƒƒ‚ƒŠ‚Í—L‚é‚Ì‚ÉAŒ´e’~Ï’†‚ÍA’…M‚µ‚È‚¢ê‡A‘ãsóMŠÇ—ƒoƒbƒtƒ@‚ğ‚Â‚©‚İ‚Á‚Ï‚È‚µ‚É‚È‚é
			*/
			if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
				SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;
			}
  #endif
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
			if (DEBUG_NumberDisplay) {
				if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {	/**	•W€‰ñü	*/
					if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
				else {	/** Šg’£ƒ‰ƒCƒ“	*/
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			}
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
		break;
#endif	/* PRO_CL1_TELFAX_LAN  */
								/*----------------------------------------------*/
	case MSG_HOLD_ELAPSE_1MIN:	/** •Û—¯ó‘Ô1•ªŒo‰ß ³‚Í‘O‰ñ“¯ƒƒbƒZ[ƒW‚æ‚è1•ªŒo‰ß */
								/*----------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/* ƒAƒ‰[ƒ€–Â“®w¦ARICE‚Ås‚Á‚Ä‚¢‚½ƒƒbƒZ[ƒW‘—M‚Í‚â‚ß‚é 1995/12/04 Eguchi*/
		HoldBuzzerRequest = 1; /* 1995/12/04 Eguchi */
		break;
										/*-----------------------------*/
	case MSG_DETECT_INPUT_HOOK_KEY	:	/** ‰ñü•ß‘¨ƒL[“ü—ÍŒŸo‚Ìê‡ */
										/*-----------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
/* QAT•s‹ï‡ NoD71-075 1998/05/05 by T.Soneoka
** ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Ò‹@‚É‚s‚d‚k‚P–Â“®’†‚ÉƒIƒ“ƒtƒbƒN‚µAÄ“xƒtƒbƒNƒL[‚ğ‰Ÿ‚µ‚½‚Æ‚«‚É‘Ò‹@ó‘Ô‚É–ß‚ç‚¸
** •s‹ï‡C³
*/
#if (0)
**		if (ncu_item == FROM_NCU_TASK) {	/** ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡ */
#else
		if ((ncu_item == FROM_NCU_TASK)
		||  (ncu_item == FROM_NCU_DIALINAUTOSWITCHTASK)) {
#endif
			is_sendmsg = 1;
			/*--------------------------------------------------------------------------------------------------------------*/
			/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡																*/
			/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																		*/
			/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñü•ß‘¨ƒL[‚É‚Ä‰ñü•ß‘¨ó‘ÔE‰ñüg—p’†E‘½‹@”\“d˜bg—p’†‚ğƒZƒbƒg‚·‚éB*/
			/*--------------------------------------------------------------------------------------------------------------*/
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |=   SYS_HOOK_KEY_OFF_HOOK;
			SYS_MachineStatus[SYS_RESOURCE_STATUS]	  &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS]	  |=   SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS]	  |=  (SYS_TELEPHONE);
			if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_DIAL_IN) {	/* QAT1 1994/08/30 by TH92115 */
				/*SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY; 1998/01/05 Y.Murata */	/** ƒ}ƒ‹ƒ`‰ñüd—l By M.Tachibana 1997/10/04 */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_DIAL_IN;
			}
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
			if (DEBUG_NumberDisplay) {
				if (CHK_LineSetting()) { /* ‰ñüİ’è == •W€‰ñü */
					if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
				else {	/* ‰ñüİ’è == Šg’£‰ñü */
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			}
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/10/18 */
			if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
			}
#endif /* defined (KEISATSU) */
			/*------------------------------------------------------*/
			/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
			/*------------------------------------------------------*/
			cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
			MainTaskMessage.Item	= FROM_MAIN;
			MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
	#if (PRO_CLASS1 == ENABLE)	/* by Y.Tanimoto */
			/*------------------------------------------------------*/
			/*	Class1‚ÌƒXƒe[ƒ^ƒX‚ğ‰ğœ‚³‚¹‚Ü‚·					*/
			/*------------------------------------------------------*/
     #if (PRO_CL1_TELFAX_LAN == ENABLE) /* ‚e–Ô^ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Î‰ S.Fukui June 19,1998 */
			if (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED)) {
     #else
			if (SYS_CL1_Status & 0x0010) {
     #endif
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = CL1_DETECT_OFF_HOOK;
				snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			}
	#endif
		}
		else {
			if (CHK_Phone2ExtLineOn()) {	/**	PHONE2ƒŠƒŒ[İ’è‚ªŠg’£ƒ‰ƒCƒ“‚Ìê‡	*/
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_HOOK_KEY_OFF_HOOK;
#if defined (KEISATSU) /* Modify by SMuratec —› 2005/08/18 */
				if (CHK_LineSetting()) { /* ‰ñüİ’è == •W€‰ñü */
					if (!HDST_RelaySetting()) { 			/* ƒnƒ“ƒhƒZƒbƒg‚Í•W€‰ñü‘¤Ú */
						SYS_HookKeyInputFlag = 0;
						is_sendmsg = 1;
					}
					if (DEBUG_NumberDisplay) {
						/* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Added by SMuratec —› 2005/10/25 */
						if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
							SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
						}
					}
				}
				else { /* ‰ñüİ’è == Šg’£‰ñü */
					if (HDST_RelaySetting()) { 			/* ƒnƒ“ƒhƒZƒbƒg‚ÍŠg’£‰ñü‘¤Ú */
						SYS_HookKeyInputFlag = 0;
						is_sendmsg = 1;
					}
					if (DEBUG_NumberDisplay) {
						/* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Added by SMuratec —› 2005/10/25 */
						if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
							SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
						}
					}
				}
#endif /* defined (KEISATSU) */
			}
		}
#else
		/*--------------------------------------------------------------------------------------------------------------*/
		/* ‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡																*/
		/*		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒNI—¹“¯ŠúÏ																		*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñü•ß‘¨ƒL[‚É‚Ä‰ñü•ß‘¨ó‘ÔE‰ñüg—p’†E‘½‹@”\“d˜bg—p’†‚ğƒZƒbƒg‚·‚éB*/
		/*--------------------------------------------------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |=   SYS_HOOK_KEY_OFF_HOOK;
		SYS_MachineStatus[SYS_RESOURCE_STATUS]	  &= ~(SYS_PRE_LINE_BUSY);
		SYS_MachineStatus[SYS_RESOURCE_STATUS]	  |=   SYS_LINE_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS]	  |=  (SYS_TELEPHONE);
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_DIAL_IN) {	/* QAT1 1994/08/30 by TH92115 */
			/*SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY; 1998/01/05 Y.Murata */	/** ƒ}ƒ‹ƒ`‰ñüd—l By M.Tachibana 1997/10/04 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_DIAL_IN;
		}
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#if (PRO_ECO_MODE == ENABLE) /* 2002/09/25 By M.Maeda */
 #if (1) /* ƒJƒo[ƒI[ƒvƒ“‚Å‚Q‚S‚u‚ğ‚n‚m‚µ‚È‚¢‚æ‚¤‚É‚·‚é By M.Maeda 2003/01/22 */
		MAN_ChangeEcoMode(0);
 #else
//		MAN_ChangeEcoMode(FALSE);
 #endif
#endif
		/*------------------------------------------------------*/
		/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
		/*------------------------------------------------------*/
		cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
		MainTaskMessage.Item	= FROM_MAIN;
		MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
		snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
#if (PRO_CLASS1 == ENABLE)	/* by Y.Tanimoto */
		/*------------------------------------------------------*/
		/*	Class1‚ÌƒXƒe[ƒ^ƒX‚ğ‰ğœ‚³‚¹‚Ü‚·					*/
		/*------------------------------------------------------*/
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* ‚e–Ô^ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Î‰ S.Fukui June 19,1998 */
		if (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED)) {
 #else
		if (SYS_CL1_Status & 0x0010) {
 #endif
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_DETECT_OFF_HOOK;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
#endif
#endif
		break;
										/*-------------------------*/
	case MSG_DETECT_INPUT_HOLD_KEY	:	/** •Û—¯ƒL[“ü—ÍŒŸo‚Ìê‡ */
										/*-------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*------------------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡						*/
		/*		‹@Šíó‘Ô‚É‚æ‚è•Û—¯ó‘Ô‚ğƒZƒbƒg–”‚ÍƒNƒŠƒA‚·‚éB				*/
		/*		“àü’Ê˜b’†‚Å•Û—¯ó‘Ô‚Ìê‡AOÒ’Ê˜bó‘Ô‚ğƒZƒbƒg‚·‚éB		*/
		/*------------------------------------------------------------------*/
		if( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_LINE_HOLD ){
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
			if( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM ){
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_INTER_COM);	/* Add by TH92115 1994/06/08 */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TRIPLE_COM;	/* '94,06,02 By N.S.*/
			}
		}
		else{
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_LINE_HOLD;
		}
		break;
							/*------------------------------------*/
	case MSG_HOLD_TIMEUP:	/* •Û—¯ó‘Ô‚T•ªŒo‰ß‚s‚‰‚‚…‚t‚‚Ìê‡ */
							/*------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*------------------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡						*/
		/*		‹@Šíó‘Ô‚æ‚è•Û—¯ó‘Ô‚ğƒNƒŠƒA‚·‚éB							*/
		/*		‚n‚e‚e@‚g‚n‚n‚jó‘Ô‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNŒp‘±				*/
		/*------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
		/* ƒAƒ‰[ƒ€–Â“®w¦ARICE‚Ås‚Á‚Ä‚¢‚½ƒƒbƒZ[ƒW‘—M‚Í‚â‚ß‚é 1995/12/04 Eguchi*/
		HoldEndBuzzerRequest = 1; /* 1995/12/04 Eguchi */
		break;
									/*-------------------------------------------------------------------*/
	case MSG_DETECT_ON_HOOK_EXIT:	/** •t‘®^ŠO•t“d˜b‚n‚m@‚g‚n‚n‚jŒŸo‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹‚Ìê‡ */
									/*-------------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*----------------------------------------------------------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡																*/
		/*		‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹“¯ŠúÏ																		*/
		/*		‹@Šíó‘Ô‚æ‚è‘½‹@”\“d˜bg—p’†‚Ì‘SƒXƒe[ƒ^ƒX‚ğƒNƒŠƒA‚·‚éB											*/
		/*		“àü’Ê˜b’†‚Ì— ‚Å’ÊM‚ªn‚Ü‚Á‚Ä‚¢‚È‚¯‚ê‚ÎA‚b‚hŒŸo’†E‰ñüg—p’†‚ğƒNƒŠƒA‚·‚éB						*/
		/*----------------------------------------------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
		/*---------------------------------------------*/
		/** ƒIƒyƒŒ[ƒVƒ‡ƒ“‚ÉƒAƒ‰[ƒ€–Â“®‚ğw¦ TBD OPR */
		/*								94.08.24 S.Tan */
		/*---------------------------------------------*/
		if ( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_LINE_HOLD ){
			/* ƒAƒ‰[ƒ€–Â“®w¦ARICE‚Ås‚Á‚Ä‚¢‚½ƒƒbƒZ[ƒW‘—M‚Í‚â‚ß‚é 1995/12/04 Eguchi*/
			HoldEndBuzzerRequest = 1; /* 1995/12/04 Eguchi */
		}
#if defined (KEISATSU) /* Œx@FAX DVT_ID37 Added by SMuratec —› 2005/11/11 */
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) { /* •W€ƒ‰ƒCƒ“ */
			SYS_RingCounter = 0;
		}
		else {	/* Šg’£ƒ‰ƒCƒ“ */
			SYS_RingCounterExt = 0;		
		}
#endif /* defined (KEISATSU) */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
																		/*-----------------------------------*/
#if defined (KEISATSU) /* Œx@FAX DVT Added by SMuratec —› 2005/11/29 */
 		if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP){
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) { /* •W€ƒ‰ƒCƒ“ */
				if (Hangup_Line == SYS_LINE_KANYU_HANGUP) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
					HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
					SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
				}
				Hangup_Line &= ~SYS_LINE_KANYU_HANGUP;
			}
			else { /* Šg’£ƒ‰ƒCƒ“ */
				if (Hangup_Line == SYS_LINE_KEIDEN_HANGUP) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
					HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
					SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
				}
				Hangup_Line &= ~SYS_LINE_KEIDEN_HANGUP;
			}
		}
#else /* !defined (KEISATSU) */
		if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
			HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
 #if defined(KEISATSU) /* Œx@FAX DVT Modify by SMuratec ‰Ä 2005/11/24 */
			Hangup_Line &= ~SYS_TWICE_LINE_HANGUP;
 #endif
		}
#endif /* defined (KEISATSU) */
#if (PRO_CIPHER == ENABLE)
		/* óM—Dæ‚Ì‚½‚ßƒXƒNƒ‰ƒ“ƒuƒ‹‚ğ’†’f‚µ‚Ä‚¢‚½ê‡AóM‚¹‚¸‚É“d˜b‚ğØ‚é‚±‚Æ‚ª‚ ‚é‚Ì‚Å
		** ‚±‚±‚ÅƒXƒNƒ‰ƒ“ƒuƒ‹Ä‹N“®‚ğƒZƒbƒg‚µ‚Ü‚· 98/06/16 By T.Fukumoto
		*/
		if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
			SYS_CipherRestartEnable = 1;
		}
#endif
																		/*-------------------------*/
#if defined (KEISATSU) /* Œx@FAX DVT_ID37 Added by SMuratec —› 2005/11/14 */
		if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			}
			else if (CHK_KEIDENRxPriority()
					&& (SYS_RingCounterExt >= (UBYTE)GetRingCounter(1))
					&& !(NCUStatus & TELEPHONE2_OFF_HOOK)) {			/** ’…MğŒ‚ğ–‚½‚µ‚½ */
			}
			else {
				/* Œx@FAX DVT Added by SMuratec —› 2005/11/30 */
	 			if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
					if (NCUStatus & TELEPHONE1_OFF_HOOK) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL1_OFF_HOOK;
					}
					else {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL2_OFF_HOOK;
					}
					NCUSndMsg = 2;
				}
				else {
					NCUSndMsg = TRUE;
				}
				TelOperationInitial();
#if 0 /* DVT Deleted by SMuratec —› 2005/11/30 */
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
#endif
			}
		}
#endif /* defined (KEISATSU) */

		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {	/** ’ÊM‚ªÀs’†‚Å‚È‚¯‚ê‚Î */
																		/*-------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
#if 0 /* Œx@FAX DVT_ID37 Deleted by SMuratec —› 2005/11/14 */
@@#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/07/19 */
@@		if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
@@			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
@@			}
@@ #if 0 /* Œx@FAX DVT_ID37 Modify by SMuratec —› 2005/11/12 */
@@@@			else if ((SYS_RingCounterExt >= CHK_ExtRingCount())
@@@@					&& !(NCUStatus & TELEPHONE2_OFF_HOOK)) {			/** ’…MğŒ‚ğ–‚½‚µ‚½ */
@@@@			}
@@ #else
@@			else if (CHK_KEIDENRxPriority()
@@					&& (SYS_RingCounterExt >= (UBYTE)GetRingCounter(1))
@@					&& !(NCUStatus & TELEPHONE2_OFF_HOOK)) {			/** ’…MğŒ‚ğ–‚½‚µ‚½ */
@@			}
@@ #endif
@@			else {
@@				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
@@			}
@@		}
@@#endif /* defined (KEISATSU) */
#endif
		break;
									/*-------------------------------------------------------------------*/
	case MSG_DETECT_ON_HOOK_CONT:	/** •t‘®^ŠO•t“d˜b‚n‚m@‚g‚n‚n‚jŒŸo‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹‚Ìê‡ */
									/*-------------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/10/26 */
 #if 0	/* Œx@FAX DVT Modify by SMuratec ‰Ä 2005/11/24 */
		if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) && (Hangup_Line == SYS_STD_LINE_COM)) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
			HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
		}
 #else
 		if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP){
			if (Hangup_Line == SYS_LINE_KANYU_HANGUP) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
				HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
				SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
			}
			Hangup_Line &= ~SYS_LINE_KANYU_HANGUP;
		}
 #endif
#endif /* defined (KEISATSU) */
		/*----------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡				*/
		/*		‹@Šíó‘Ô‚æ‚è•t‘®“d˜bƒIƒtƒtƒbƒNó‘Ô‚ğƒNƒŠƒA‚·‚éB	*/	/* Add by TH92115 1994/07/04 */
		/*		•Û—¯ó‘Ô‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNŒp‘±B				*/
		/*----------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK);
		break;

	/*-----------------------------------------------------------
	** ‚s‚d‚k‚Q‚à‚s‚d‚k‚P‚Ìˆ—‚É“ˆê  By M.Tachibana 1997/09/25
	*/
										/*-------------------------------------------------------------------*/
	case MSG_DETECT_ON_HOOK_CONT_TEL2:	/** •t‘®^ŠO•t“d˜b‚n‚m@‚g‚n‚n‚jŒŸo‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹‚Ìê‡ */
										/*-------------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/10/26 */
 #if 0 /* Œx@FAX DVT Modify by SMuratec ‰Ä 2005/11/24 */
		if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) && (Hangup_Line == SYS_EXT_LINE_COM)) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
			HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
		}
 #else
 		if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP){
			if (Hangup_Line == SYS_LINE_KEIDEN_HANGUP) {	/** ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|‚Ìê‡ TBD */
				HungUpCheck = 0; /* ƒnƒ“ƒOEƒAƒbƒvEƒ`ƒFƒbƒNEƒNƒŠƒA */		/*-----------------------------------*/
				SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP); /* ƒnƒ“ƒOEƒAƒbƒvEƒGƒ‰|EƒNƒŠƒA */
			}
			Hangup_Line &= ~SYS_LINE_KEIDEN_HANGUP;
		}
 #endif
#endif /* defined (KEISATSU) */
		/*----------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡				*/
		/*		‹@Šíó‘Ô‚æ‚è•t‘®“d˜bƒIƒtƒtƒbƒNó‘Ô‚ğƒNƒŠƒA‚·‚éB	*/	/* Add by TH92115 1994/07/04 */
		/*		•Û—¯ó‘Ô‚Å‘½‹@”\“d˜b§Œäƒ^ƒXƒNŒp‘±B				*/
		/*----------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL2_OFF_HOOK);
		break;

#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
	case MSG_DETECT_ON_HOOK_CONT_HKEY:
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
#if defined (KEISATSU) /* Modify by SMuratec —› 2005/09/14 */
		if (CHK_LineSetting()) { /* ‰ñüİ’è == •W€‰ñü */
			if (!HDST_RelaySetting()) { 			/* ƒnƒ“ƒhƒZƒbƒg‚Í•W€‰ñü‘¤Ú */
				SYS_HookKeyInputFlag = 0;
				is_sendmsg = 1;
			}
		}
		else { /* ‰ñüİ’è == Šg’£‰ñü */
			if (HDST_RelaySetting()) { 			/* ƒnƒ“ƒhƒZƒbƒg‚ÍŠg’£‰ñü‘¤Ú */
				SYS_HookKeyInputFlag = 0;
				is_sendmsg = 1;
			}
		}
#endif /* defined (KEISATSU) */
		break;
#endif

#if (PRO_BRANCH_RX == ENABLE)			/*---------------------------------------------------------------------*/
	case MSG_DETECT_BRN_ON_HOOK_EXIT:	/** ƒuƒ‰ƒ“ƒ`“d˜b‚Ì‚n‚m@‚g‚n‚n‚jŒŸo‚µ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚ªI—¹‚Ìê‡ */
										/*---------------------------------------------------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/20 */
		is_sendmsg = 1;
#endif
		/*----------------------------------------------------------------------------------------------------------*/
		/* ‘½‹@”\“d˜b§Œäƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡																*/
		/*		‘½‹@”\“d˜b§Œäƒ^ƒXƒNI—¹“¯ŠúÏ																		*/
		/*		‹@Šíó‘Ô‚æ‚è‘½‹@”\“d˜bg—p’†‚Ì‘SƒXƒe[ƒ^ƒX‚ğƒNƒŠƒA‚·‚éB											*/
		/*		“àü’Ê˜b’†‚Ì— ‚Å’ÊM‚ªn‚Ü‚Á‚Ä‚¢‚È‚¯‚ê‚ÎA‚b‚hŒŸo’†E‰ñüg—p’†‚ğƒNƒŠƒA‚·‚éB						*/
		/*----------------------------------------------------------------------------------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
																		/*-------------------------*/
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {	/** ’ÊM‚ªÀs’†‚Å‚È‚¯‚ê‚Î */
																		/*-------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;
			/*---------------------------------------*/
			/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
			/*---------------------------------------*/
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		}
		break;
#endif
	/*-----------------------------------------------------------------------*/
	/*					ƒ_ƒCƒ„ƒ‹EƒCƒ“‰¼’…MŒŸoŠÖ˜A						 */
	/*-----------------------------------------------------------------------*/
#if (PRO_DIALIN == ENABLE)			/*-------------------------------------------*/
	case MSG_DETECT_TRANSFER_D_IN:	/** ƒ_ƒCƒ„ƒ‹EƒCƒ“‰¼’…M‚æ‚è‚e‚`‚w’…M‚ğŒŸo */
									/*-------------------------------------------*/
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1999/02/25 */
	case MSG_DETECT_TRANSFER_MODEM_D_IN: /* ƒ‚ƒfƒ€ƒ_ƒBƒ„ƒ‹ƒCƒ“‚Å’…MŒŸo */
 #endif
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/12 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
  		is_receive = CL1_CheckReceiveByFaxOrPC();
		if ((is_receive == NO_RECEIVING) || (is_receive == NO_RECEIVING_SCANNER_IN_USE) || (is_receive == NO_RECEIVING_PRINTER_IN_USE)) {
			if (ncu_message == MSG_DETECT_TRANSFER_MODEM_D_IN) {/* NCU_Task ‚É‚Íˆø‚«‘±‚«ŒÄ‚Ño‚µ‰¹ŒŸo‚ğ‘±s‚µ‚Ä‚à‚ç‚¤B*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN; /* MSG_EXIT ‚Å‚È‚¯‚ê‚Î‚È‚ñ‚Å‚à‚¢‚¢B */
				if (ncu_item == FROM_NCU_TASK) {
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage);
					break;
				}
			}
		}
  #endif
		/*--------------------------------------------------------------------------------------------------*/
		/* ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡												*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†‚ğƒNƒŠƒA‚µ‰ñüg—p’†E’ÊMÀs’†EƒvƒŠƒ“ƒ^g—p’†‚ğƒZƒbƒg‚·‚éB		*/
		/*--------------------------------------------------------------------------------------------------*/
 #if (PRO_CIPHER == ENABLE)
		/* óM—Dæİ’è‚ª‚n‚m‚É‚È‚Á‚Ä‚¢‚é‚Æ‚«‚ÉƒXƒNƒ‰ƒ“ƒuƒ‹ˆ—’†‚È‚çAƒXƒNƒ‰ƒ“ƒuƒ‹‚Ì’†’fˆ—‚ğs‚¢‚Ü‚·
		** 98/06/16 By T.Fukumoto
		*/
		if (CMN_CheckScrambleBusy()) {
			if ((!CHK_UNI_PriorityReceive()) && (!SYS_CipherInterruptionOn) && (!CipherStopOn)) {
				SYS_CipherInterruptionOn = SYS_CipherComExec;
				SYS_BackupCipherStatus = SYS_MachineStatus[SYS_CIPHER_STATUS];/*By Y.Suzuki 1998/08/12*/
				CipherStopOn = 1;
			}
		}
 #endif
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);

 #if (0)	/* ‚b‚hŒŸoŒãiMSG_DETECT_CALL_TO_FAXjƒ‰ƒCƒgƒ|ƒCƒ“ƒ^‚ğŠl“¾‚µ‚Ä‚¢‚é‚Ì‚Å
//		** ‚±‚±‚Å‚Íƒƒ‚ƒŠ—e—Ê‚¾‚¯‚ğ‚İ‚é By M.Tachibana 1997/10/04
//		*/
//		/* POPLAR•ÏX 1997/03/19  By T.Yamaguchi */
//		SYB_MemoryRxPrintWritePoint = (UBYTE)CMN_CheckMultiLineReceiveNumber((UWORD)0, AUTO_RECEIVE);
//		if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
 #endif
 #if 0	/* 1998/01/05 Y.Murata */
//		/* if (CMN_CheckMemoryReceiveEnable()) { 1997/11/20  By T.Yamaguchi */
//		if (CMN_CheckMultiLineReceiveEnable()) {
 #endif
		/* ‚e‚`‚w’…M‚Ì‚Æ‚«‚Éƒ|ƒCƒ“ƒ^‚ğŠl“¾‚µ‚Ä‚¨‚­A“d˜b‚Ì‚Æ‚«ƒ|ƒCƒ“ƒ^c‚ç‚È‚¢‚æ‚¤‚ÉB
		 *
		*/
		SYB_MemoryRxPrintWritePoint = (UBYTE)MAN_CheckMultiLineReceiveEnable((UWORD)0, AUTO_RECEIVE);
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
  #if (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/18 */
		if (QueryAutoCalledEnable(0) || (CL1_CheckReceiveByFaxOrPC() == PC_RECEIVE_OK)) {
  #else
   #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/6 K.Kawata */
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) && ((CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING) || (SYS_CL1_RxEnableFlag == 1))) {
   #else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) && (CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING)) {
   #endif
  #endif
 #else
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		if (QueryAutoCalledEnable(0)) { /* changed by H.Hirao 1998/12/26 */
	#else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || QueryPRxEnable()) {
	#endif
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.4 K.Kawata */
	  	if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || (QueryPRxEnable() && QueryWarpAndSecurityDisable())) {
    #else
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) /**|| CheckPollingTxType()**/) {	/* 1999.3.19 K.Kawata CheckPollingTxType() ’Ç‰Á */
    #endif
  #endif
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
			if (tskno_NCU_TelephoneOperation != 0xffff) {
				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				is_sendmsg = 1;
			}
#if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/07/13 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= (~(SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK));
#endif /* defined (KEISATSU) */
			SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	•W€ƒ‰ƒCƒ“’ÊM’†	*/
 #endif
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/12 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
			CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒZƒbƒg */
  #endif
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
	#endif
			/*
			** ƒvƒŠƒ“ƒ^óM‚·‚é‰Â”\«‚Ì‚ ‚é‚Æ‚«‚¾‚¯SYS_PRINTER_BUSY‚ğƒZƒbƒg‚µ‚Ü‚·
			** 1999/02/18 by T.Soneoka
			*/
#if (0)
**			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
#else
			if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			}
#endif
  #endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.1 K.Kawata */
			PRN_ChechRxPrintCallProc();
#endif
			/*----------------------------------*/
			/**		’ÊMƒ^ƒXƒN‹N“®i©“®óMj	*/
			/*----------------------------------*/
#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
**  #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
**  #endif
#else
			CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ƒ‚ƒfƒ€ƒ_ƒBƒ„ƒ‹ƒCƒ“—pB added by H.Kubo 1999/02/25 */
			if (ncu_message == MSG_DETECT_TRANSFER_MODEM_D_IN) {
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_EXIT;
				if (ncu_item == FROM_NCU_TASK) {
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage); /* NCU_Task ‚Ì—Dæ‡ˆÊ‚ªã‚¾‚Æ‰¼’è‚µ‚Ü‚·B */
					/* NCU_Task ‚Ì—Dæ‡ˆÊ‚ª’á‚¢ê‡‚ÍA‚±‚±‚É rcv_msg ‚ğ“ü‚ê‚é‚±‚ÆB*/
				}
			}
 #endif

			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_AUTO_CALLED;
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
		else {													/* Add by TH92115 1994/09/19 */
#if 0 /* ƒ‚ƒfƒ€ƒ_ƒCƒ„ƒ‹ƒCƒ“—pC³BChanged by H.Kubo 1999/02/25 */
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/26 */
			/* ƒƒ‚ƒŠ‚Í—L‚é‚Ì‚ÉAŒ´e’~Ï’†‚ÍA’…M‚µ‚È‚¢ê‡A‘ãsóMŠÇ—ƒoƒbƒtƒ@‚ğ‚Â‚©‚İ‚Á‚Ï‚È‚µ‚É‚È‚é
			*/
			if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
				SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;
			}
  #endif

			/*
			** ƒ‚ƒfƒ€ƒ_ƒCƒ„ƒ‹ƒCƒ“‚Åƒƒ‚ƒŠƒtƒ‹‚Å’…M‚Å‚«‚È‚¢‚Æ‚«A‚m‚c•\¦‚ªÁ‚¦‚È‚¢•s‹ï‡
			** 1999/02/24 by T.Soneoka
			*/
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;

			/* ‚±‚Ìˆ—‚¾‚Æ–³–Â“®‚Å‚QŸ‰“š‘Ò‚¿‚Æ‚È‚è”­MÕ“Ë‚Æ‚È‚é‚Ì‚ÅA‘ãsóM•s‰Â‚Ì‚Í
               ãˆÊ‚ÅMSG_DETECT_TRANSFER_D_IN ‚É—ˆ‚È‚¢‚æ‚¤‚É‚µ‚½B‚±‚ê‚Í•ÛŒ¯I S.Fukui June 19,1998 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
#else
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* ƒ‚ƒfƒ€ƒ_ƒCƒ„ƒ‹ƒCƒ“’…M‹‘”Û—p added by H.Kubo 1999/02/25 */
			if (ncu_message == MSG_DETECT_TRANSFER_MODEM_D_IN) {/* NCU_Task ‚É‚Íˆø‚«‘±‚«ŒÄ‚Ño‚µ‰¹ŒŸo‚ğ‘±s‚µ‚Ä‚à‚ç‚¤B*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN; /* MSG_EXIT ‚Å‚È‚¯‚ê‚Î‚È‚ñ‚Å‚à‚¢‚¢B */
				if (ncu_item == FROM_NCU_TASK) {
					snd_msg(mbxno.NCU_TaskSub, &MainTaskMessage);
				}
			}
			else {
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/26 */
				/* ƒƒ‚ƒŠ‚Í—L‚é‚Ì‚ÉAŒ´e’~Ï’†‚ÍA’…M‚µ‚È‚¢ê‡A‘ãsóMŠÇ—ƒoƒbƒtƒ@‚ğ‚Â‚©‚İ‚Á‚Ï‚È‚µ‚É‚È‚é
				*/
				if (SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) {
					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;
				}
  #endif

				/*
				** ƒ‚ƒfƒ€ƒ_ƒCƒ„ƒ‹ƒCƒ“‚Åƒƒ‚ƒŠƒtƒ‹‚Å’…M‚Å‚«‚È‚¢‚Æ‚«A‚m‚c•\¦‚ªÁ‚¦‚È‚¢•s‹ï‡
				** 1999/02/24 by T.Soneoka
				*/
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;

				/* ‚±‚Ìˆ—‚¾‚Æ–³–Â“®‚Å‚QŸ‰“š‘Ò‚¿‚Æ‚È‚è”­MÕ“Ë‚Æ‚È‚é‚Ì‚ÅA‘ãsóM•s‰Â‚Ì‚Í
	               ãˆÊ‚ÅMSG_DETECT_TRANSFER_D_IN ‚É—ˆ‚È‚¢‚æ‚¤‚É‚µ‚½B‚±‚ê‚Í•ÛŒ¯I S.Fukui June 19,1998 */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY);
				cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
				SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
			}
 #endif
#endif
		}
		break;
							/*-----------------------------------------*/
	case MSG_D_IN_TIMEUP:	/** ƒ_ƒCƒ„ƒ‹EƒCƒ“‹^—ƒxƒ‹–Â“®‚s‚‰‚‚…‚t‚ */
							/*-----------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/* ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒãˆ—ƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒW‚Ìê‡										*/
		/*		‹@Šíó‘Ô‚æ‚è‚b‚hŒŸo’†E‰ñüg—p’†E‘½‹@”\“d˜bŠÖŒW‘SƒXƒe[ƒ^ƒX‚ğƒNƒŠƒA‚·‚éB		*/
		/*------------------------------------------------------------------------------------------*/
		/*SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY; 1998/01/05 Y.Murata */	/** ƒ}ƒ‹ƒ`‰ñüd—l By M.Tachibana 1997/10/04 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY);
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
 #if (PRO_CIPHER == ENABLE)
		/* óM—Dæ‚Ì‚½‚ßƒXƒNƒ‰ƒ“ƒuƒ‹‚ğ’†’f‚µ‚Ä‚¢‚½ê‡A‚s‚‰‚‚…‚t‚‚Ì‚½‚ß’…M‚µ‚È‚¢‚Ì‚Å
		** ‚±‚±‚ÅƒXƒNƒ‰ƒ“ƒuƒ‹Ä‹N“®‚ğƒZƒbƒg‚µ‚Ü‚· 98/06/11 By T.Fukumoto
		*/
		if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
			SYS_CipherRestartEnable = 1;
		}
 #endif
		/*---------------------------------------*/
		/**		‘Ò‹@ó‘Ô‰ñüŠÄ‹ƒ^ƒXƒN‹N“®	 */
		/*---------------------------------------*/
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
		SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		break;
 #if (PRO_CL1_TELFAX_LAN == ENABLE) /* ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Î‰ S.Fukui June 19,1998 */
	case MSG_DETECT_CL1_D_IN:

		/*
		* SYS_LINE_BUSY‚ÆSYS_DIAL_IN‚Í—§‚Ä‚Ä‚¨‚­
		*/
		/* SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK + SYS_TEL2_OFF_HOOK
														+ SYS_BRANCH_OFF_HOOK + SYS_HOOK_KEY_OFF_HOOK
													/*	+ SYS_TAD + SYS_DIAL_IN + SYS_INTER_COM + SYS_INTER_CALL */
														+ SYS_TAD + SYS_INTER_COM + SYS_INTER_CALL
														+ SYS_LINE_HOLD + SYS_HOLD_TRANSFER + SYS_TRIPLE_COM);
  #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_RS_INTERNAL == ENABLE) /* by H.Hirao 1999/05/10 */
		CL1_DualRestrictionStatus |= CL1_CLASS1_IN_USE;	/* ƒNƒ‰ƒX‚PóM’†ƒZƒbƒg */
		SYS_CalledRequestForDocStore = 0;
  #endif
		/*
		* ƒ_ƒCƒ„ƒ‹ƒCƒ“FAX‰ñü‚Ö‚ÌŒÄ‚Ño‚µ‚ğCL1_Task‚É’Ê’m‚·‚é
		* (RS-232C‚Ö‚Ì"RING"‘—o‚ÍCL1_Task‚Ås‚¤)
		*/
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_DETECT_RING_DIALIN;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;

	case MSG_DETECT_CL1_D_IN_DSE:	/* Class1ƒ_ƒCƒ„ƒ‹ƒCƒ“‚Å‹É”½ŒŸo */

		SYB_MemoryRxPrint[CL1_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_EMPTY;	/** ƒ}ƒ‹ƒ`‰ñüd—l */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY);
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK + SYS_TEL2_OFF_HOOK
														+ SYS_BRANCH_OFF_HOOK + SYS_HOOK_KEY_OFF_HOOK
														+ SYS_TAD + SYS_DIAL_IN + SYS_INTER_COM + SYS_INTER_CALL
														+ SYS_LINE_HOLD + SYS_HOLD_TRANSFER + SYS_TRIPLE_COM);
		/*
		* ‹É”½ŒŸo‚É‚æ‚é’†’f‚ğCL1_Task‚Ö’Ê’m
		*/
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_DIALIN_DETECT_DSE;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		/*
		* NCU_Task‹N“®
		*/
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
		SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */

		break;
	case MSG_DETECT_CL1_NON_D_IN:	/* Class1 ƒ_ƒCƒ„ƒ‹ƒCƒ“İ’è‚Ì”ñƒ_ƒCƒ„ƒ‹ƒCƒ“ŒÄ‚É‘Î‚·‚é‚o‚bóM */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK + SYS_TEL2_OFF_HOOK
														+ SYS_BRANCH_OFF_HOOK + SYS_HOOK_KEY_OFF_HOOK
														+ SYS_TAD + SYS_DIAL_IN + SYS_INTER_COM + SYS_INTER_CALL
														+ SYS_LINE_HOLD + SYS_HOLD_TRANSFER + SYS_TRIPLE_COM);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CIŒŸo’†ƒNƒŠƒA */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; 		/* ‰ñüg—p’†ƒZƒbƒg */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; 			/* ’ÊMÀs’†ƒZƒbƒg */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_NON_DIAL_IN_RX_REQ;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
 #endif /* (PRO_CL1_TELFAX_LAN == ENABLE) */
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/04 */
	case MSG_DETECT_ND_CAR: /* ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC CAR M†ŒŸo */
		/* ’…M‘Oî•ñóMƒ^ƒXƒN‚ğ‹N“® */
		break;
	/*---------------------------------------------------------------------
	** ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’…M‚É”­MÒ”Ô†‚ğŒŸo‚µ‚½‚Ì‚ÅA
	** ŒŸo‚µ‚½”­MÒ”Ô†‚ğ•\¦‚·‚é‚½‚ß‚Éƒtƒ‰ƒO‚ğƒZƒbƒg‚µ‚Ü‚·B
	** ‚±‚±‚Å—§‚Ä‚½ƒtƒ‰ƒO‚ÍAMSG_DETECT_CI_TIMEUP‚Ì‚Æ‚«‚ÉƒNƒŠƒA‚µ‚Ü‚·B
	** 1998/09/19 H.Yoshikawa
	*/
	case MSG_DETECT_ND_NUMBER:  /* ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC‚Ì”­MÒ”Ô†ŒŸo H.Yoshikawa 1998/09/19 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRE_LINE_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_ND_DISPLAY;
		break;
	/*---------------------------------------------------------------------
	** ND‚Ìˆ—‚ğs‚Á‚½Œã‚ÍA•K‚¸ANCU_Task‚ğÄ‹N“®‚µ‚Ü‚·B
	** ‚±‚±‚Å‚ÍATEL–Â“®‚µ‚½‚ªAƒIƒtƒtƒbƒN‚·‚é‘O‚ÉA”­MÒ‚ªó˜bŠí‚ğ’u‚¢‚½ê‡‚É‚«‚Ü‚·B
	** 1998/11/14 H.Yoshikawa
	*/
	case MSG_NCU_RESTART:	/* ND‚Ìˆ—‚ğs‚Á‚½Œã‚ÍA•K‚¸ANCU_Task‚ğÄ‹N“®‚µ‚Ü‚·B*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRE_LINE_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
		break;
#endif
	default:
		break;
	}
#if (PRO_CPU == SH7043) /** TBD Jun.4,1994 By S.K */
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^—‚Q‰ñüd—l by T.Soneoka 1997/11/25 */
	if (is_sendmsg) {
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
		snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
		rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
 #if defined (KEISATSU)		/* Œx@FAX DVT_ID43 Added by SMuratec K.W.Q 2005/11/15 */
 		FaxComCompleted = TRUE;
		/* Œx@FAX DVT_ID81 Added By SMuratec —› 2005/12/21 */
		IsSHIREIKido = FALSE;
		
		/* Œx@FAX DVT Added by SMuratec —› 2005/11/30 */
		if (NCUSndMsg) {
			if (!(--NCUSndMsg)){
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
			}
		}
 #endif		/* End of (defined (KEISATSU)) */
	}
#else
	#if (PRO_CLASS1 == DISABLE) /* 1996/09/13 Eguchi */
	if ((ncu_message != MSG_DETECT_CI) && (ncu_message != MSG_DETECT_CI_TIMEUP) && (ncu_message != MSG_DETECT_CALL_TO_FAX) && (ncu_message != MSG_DETECT_F_NET)
	 && (ncu_message != MSG_DETECT_CALL_D_IN) && (ncu_message != MSG_DETECT_TRANSFER_D_IN) && (ncu_message != MSG_D_IN_TIMEUP)) {
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
		snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);	/* Jan.11,1995 By S.K -> vjqÇqŞzj| Jan.18,1995 By T.Nose */
		rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);		/* Jan.11,1995 By S.K -> vjqÇqŞzj| Jan.18,1995 By T.Nose */
	}
	#endif
	#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
	if ((ncu_message != MSG_DETECT_CI) && (ncu_message != MSG_DETECT_CI_TIMEUP) && (ncu_message != MSG_DETECT_CALL_TO_FAX) && (ncu_message != MSG_DETECT_F_NET)
     #if (PRO_CL1_TELFAX_LAN == ENABLE) /* ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Î‰ S.Fukui June 19,1998 */
	 && (ncu_message != MSG_DETECT_CL1_D_IN) && (ncu_message != MSG_DETECT_CL1_D_IN_DSE)
     #endif
	 && (ncu_message != MSG_DETECT_CALL_D_IN) && (ncu_message != MSG_DETECT_TRANSFER_D_IN) && (ncu_message != MSG_D_IN_TIMEUP) && (ncu_message != MSG_DETECT_RING)) {
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
		snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);	/* Jan.11,1995 By S.K -> vjqÇqŞzj| Jan.18,1995 By T.Nose */
		rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);		/* Jan.11,1995 By S.K -> vjqÇqŞzj| Jan.18,1995 By T.Nose */
	}
	#endif
#endif
#endif
}




/*************************************************************************
	module		:[’ÊMƒ^ƒXƒN‚©‚ç‚ÌƒƒbƒZ[ƒWˆ—]
	function	:[
		1.

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[¬’J³÷]
*************************************************************************/
void	MAN_FromFaxcom(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
	MESSAGE_t	MainToCL1TaskMessage;
#endif
	UWORD	memory_rx_num;	/* 1997/02/08 Y.Murata */

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.FCM_Task, &MainTaskMessage);
	switch (message) {
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
	case MSG_CL1_CNG_DETECT:
		ClearMemoryRxSetting();		/* SYS_MEMORY_RX_SETTING ‚Å‘ãsóMŠÇ—ƒe[ƒuƒ‹‚ğŠm•Û‚µ‚Ä‚¢‚½‚ç
									** SYS_MEMORY_RX_EMPTY ‚É–ß‚· */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_FAXCOM); /* "** Á¬¸¼İ **"‚Ì•\¦Á‹‚Ìˆ× */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;  /* CLASS1“®ì’†ƒZƒbƒg */
		MainToCL1TaskMessage.Item = FROM_MAIN;
		MainToCL1TaskMessage.Message = CL1_CNG_RX_REQ;
		snd_msg(mbxno.CL1_Task, &MainToCL1TaskMessage);
		break;
#endif
	case MSG_FAXCOM_CLOSE_ERROR:
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /** ƒXƒLƒƒƒi[EƒtƒB[ƒhEƒGƒ‰[‚ğƒZƒbƒg */
		break;
	case MSG_FAXCOM_DISPLAY:
#if (PRO_NUMBER_DISPLAY == ENABLE) /* Changed by H.Kubo 1998/12/14 */
		if (SYS_FaxCommStage != FCM_CALLED) {
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
			if (DEBUG_NumberDisplay) {
				if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {	/**	•W€‰ñü	*/
					if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
				else {	/** Šg’£ƒ‰ƒCƒ“	*/
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					}
				}
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
			}
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
		}
#else
#endif
		break;
	case MSG_RX_PRINT_PAGE: /* ’Êí‚Ìƒƒ‚ƒŠóMŒ´e‚Ì‚¾‚¯‚±‚ÌƒƒbƒZ[ƒW‚ğóMA‚Pƒy[ƒWóM–ˆ‚Éƒƒ‚ƒŠóMƒe[ƒuƒ‹‚ğXV */
		for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
			if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
			|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
			if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
			|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
			|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
				/* ‚p‚`‚s•s‹ï‡
				** Šg’£‰ñü‚ÅóM‚ª‚Å‚«‚È‚¢•s‹ï‡C³
				** Šg’£‰ñü‚Ìˆ—‚ª”²‚¯‚Ä‚¢‚½i "& 0x7f")
				** by O.Kimoto 1998/04/13
				*/
				if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (unsigned char)0) {
					break;
				}
#else
				if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (unsigned char)0) {
					break;
				}
#endif
			}
		}

		if (memory_rx_num < SYS_MEMORY_RX_MAX) {
			if ( (SYS_RxMemoryFileItem != SYS_MEM_BUFFERING_RX_FILE)
			 &&	 (MEM_CountTotalPage(SYS_MEM_RX_FILE, memory_rx_num, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) ) { /* 1ƒy[ƒWˆÈã’~Ï‚³‚ê‚Ä‚¢‚ê‚Î */
				/* ƒƒ‚ƒŠóMƒe[ƒuƒ‹XV */
				MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];

#if (PRO_MULTI_LINE == DISABLE)
				if ( SYS_RxReceiptRequestFlag == 1 /* YES TBD */ ) { /* ó—ÌØóM */
					MemoryRxPrintPoint->JournalPoint = &SYB_JournalFile[SYB_JournalPoint]; /* ‘—óMƒWƒƒ-ƒiƒ‹‚Ìƒ|ƒCƒ“ƒ^-‚ğ“o˜^ */
				}
				else { /* ó—ÌØˆÈŠO‚ÌŒ´eóM */
					MemoryRxPrintPoint->JournalPoint = &SYB_JournalFile[SYB_JournalPoint]; /* ‘—MƒWƒƒ-ƒiƒ‹‚Ìƒ|ƒCƒ“ƒ^-‚ğ“o˜^ */
				}
#endif
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
#else
				if (CHK_UNI_RxDocReversePrint()) {
					if (MemoryRxPrintPoint->Status != SYS_MEMORY_RX_STORE_PRINT) {
						if (CMN_CheckFastPrintStart()) {
							MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE_PRINT;
						}
						else {
							MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
						}
					}
				}
				else {
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
				}
#endif
				MemoryRxPrintPoint->StorePage++;

				if (MemoryRxPrintPoint->StorePage == 1) {
					MemoryRxPrintPoint->ReceiveTime = SYB_CurrentFaxReceiveTime;	/* add 1997/03/19  By T.Yamaguchi	*/
					/*
					** ‚Pƒy[ƒWŠ®—¹ŠÔ‚É‚¨‚¢‚ÄA‘¼‚ÌóM‚Å“¯‚¶‚ª‚ ‚éê‡Aƒvƒ‰ƒX‚P•b‰ÁZ‚·‚éˆ—
					** ‰ñ“]ƒIƒvƒVƒ‡ƒ“‚ª‚ ‚éê‡‚ÅA“¯‚ÌóM‚ª‚ ‚é‚ÆAƒvƒŠƒ“ƒg‚Å‚«‚È‚­‚È‚é‚±‚Æ‚ª‚ ‚é
					** 1998/05/20 by T.Soneoka */
					if (MAN_CheckReceiveTime(MemoryRxPrintPoint->ReceiveTime, memory_rx_num)) {
						MemoryRxPrintPoint->ReceiveTime++;
					}
				}
				/*----------------------------------------------------------*/
				/* ƒZƒLƒ…ƒŠƒeƒBóM‹@”\’Ç‰Á		1996/04/27 Eguchi			*/
				/*----------------------------------------------------------*/
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/7/6 K.Kawata */
				if ((SYB_SecurityRxModeFlag == 1) && (!SYS_CL1_RxEnableFlag)) {/** ƒZƒLƒ…ƒŠƒeƒBóMƒ‚[ƒh’† */
					if ((MemoryRxPrintPoint->StorePage == 1) /*‚Q–‡–ÚˆÈ~‚ÉƒvƒƒeƒNƒg‚n‚m‚É‚µ‚Ä‚à–³Œø‚É‚·‚é‚½‚ß */
					     && (MemoryRxPrintPoint->Protect == SYS_PROTECT_OFF)) {
#else
				if (SYB_SecurityRxModeFlag == 1) {/** ƒZƒLƒ…ƒŠƒeƒBóMƒ‚[ƒh’† */
					if ((MemoryRxPrintPoint->StorePage == 1) /*‚Q–‡–ÚˆÈ~‚ÉƒvƒƒeƒNƒg‚n‚m‚É‚µ‚Ä‚à–³Œø‚É‚·‚é‚½‚ß */
					&&	(MemoryRxPrintPoint->Protect == SYS_PROTECT_OFF)) {
#endif
						MemoryRxPrintPoint->Protect = SYS_PROTECT_ON;
					}
				}
				/* 1997/02/10 Y.Murata
				 * ƒvƒŠƒ“ƒ^‚ª¡AóM‚µ‚Ä‚¢‚éŒ´e‚ğƒvƒŠƒ“ƒg‚µ‚Ä‚¢‚éê‡‚Ì‚İƒCƒxƒ“ƒg‚ğ”­s‚µ‚Ü‚·
				*/
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
					if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
					&& (SYS_DocumentPrintNo == memory_rx_num)) {

						CMN_DisableInterrupt();	/**	Š„‚è‚İ‹Ö~	*/
						PRN_1PageReceived = 1;
						det_evt(EVT_PRN_RESTART);
						CMN_EnableInterrupt();	/**	Š„‚è‚İ‹–‰Â	*/
					}
				}
			}
		}
		break;
	case MSG_FAXCOM_END:
	case MSG_FAXCOM_END_OFF_HOOK:
	case MSG_FAXCOM_ANS_CHANGE_KAMO:
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/09/17 */
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	•W€ƒ‰ƒCƒ“‚É‚Ä‘—M	*/
			SYS_CalledLineNumber &= ~SYS_STD_LINE_IN_CI;
		}
		else {
			SYS_CalledLineNumber &= ~SYS_EXT_LINE_IN_CI;
		}
		SYS_MachineStatus[SYS_OTHER_STATUS] &=	~SYS_CONT24_LINE_BUSY; /* ‹[—–Â“®ó‘Ô‚ğÁ‹‚µ‚Ü‚· */
		if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* •t‘®“d˜b‚ÍƒtƒtƒbƒN‚Å‚Í‚È‚¢ */
			NCU_HdstShift();
		}
		/* Œx@FAX DVT_ID2 Added by SMuratec —› 2005/11/19 */
		if ( !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE) ) {
			if (FaxComTXorRX_Flag) {
				FaxComTXorRX_Flag = 0;
			}
		}
#endif /* defined (KEISATSU) */
#if defined (KEISATSU)		/* Œx@FAX Added by SMuratec K.W.Q 2005/09/07 */
 #if (1)
		if (!SYS_HookKeyFlagBk) {
  #if 0	/* Œx@FAX DVT by SMuratec ‰Ä 2005/11/19 */
			if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & (SYS_HDST_STD_OFFHOOK | SYS_HDST_EXT_OFFHOOK)) ) {	/* •t‘®“d˜b‚ÍƒtƒtƒbƒN‚Å‚Í‚È‚¢ */
				SetKeisatsuSettings();
				NCU_HdstShift();
			}
  #else
			ResetKeisatsuAttribute();
  #endif
		}
 #else
#if 0 /* Œx@FAX DVT Added by SMuratec —› 2005/09/07 */
@@		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & (SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK)) &&
@@			!(NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK))) {
#else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & (SYS_TEL1_OFF_HOOK | SYS_TEL2_OFF_HOOK)) &&
			!(NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) &&
			!SYS_HookKeyFlagBk) {
#endif

			if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & (SYS_HDST_STD_OFFHOOK | SYS_HDST_EXT_OFFHOOK)) ) {	/* •t‘®“d˜b‚ÍƒtƒtƒbƒN‚Å‚Í‚È‚¢ */
				SetKeisatsuSettings();
				NCU_HdstShift();
			}
		}
 #endif
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* ˜A‘±ƒ|[ƒŠƒ“ƒO‹@”\’Ç‰Á */
		/* ˜A‘±ƒ|[ƒŠƒ“ƒOƒRƒ}ƒ“ƒhÀsI—¹‚Å‚ ‚ê‚ÎƒLƒ…[‚ğ–³ğŒ‚ÅƒNƒŠƒA */
		/* –{“–‚É‚±‚ÌêŠ‚Å‚¢‚¢‚Ì‚© */
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/**ƒRƒ}ƒ“ƒh’ÊM‚Å */
			if (SYS_CurrentExecutingCommand->Kind == SYS_CONTINUOUS_POLLING) {	/** ÀsI—¹‚µ‚½’ÊM‚ª˜A‘±ƒ|[ƒŠƒ“ƒO */
				SYS_CurrentExecutingCommand->Status = SYS_EXEC_ERASED;	/* –³—–î—Á‹ */
				DeleteContinuousPollingCommand();
				CommandErased[0] = 0;		/* 1997/10/29 COMMAND_DEL */
			}
		}
#endif
#if defined(KEISATSU)	/* Œx@FAX DVT_ID34 Modify by SMuratec ‰Ä 2005/11/09 */	
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) && 
			!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) &&
			!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK)) {
			CMN_MemorySet(SYS_DialingNumber.Buffer, DIALING_NUMBER_MAX, 0);
			SYS_DialingNumber.ReadPointer = SYS_DialingNumber.WritePointer = 0;
		}
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* ”­MÒ”Ô†•\¦Á‹ added by H.Kubo 1998/10/28 */
#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
		if (DEBUG_NumberDisplay) {
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {	/**	•W€‰ñü	*/
				if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
				}
			}
			else {	/** Šg’£ƒ‰ƒCƒ“	*/
				if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
				}
			}
		}
		else {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
		}
#else /* !defined (KEISATSU) */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
#endif /* defined (KEISATSU) */
#endif
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/*
		** óM’†‚ÌƒXƒe[ƒ^ƒX‚ğƒŠƒZƒbƒg added by H.Hirao 1998/12/26
		*/
		CMN_DisableInterrupt();
		SYS_DualRestrictionStatus &= ~(0x01);
		CMN_EnableInterrupt();
#endif

#if defined (KEISATSU)		/* Œx@FAX DVT_ID43 Added by SMuratec K.W.Q 2005/11/15 */
		FaxComCompleted = FALSE;
#endif

		switch (sub_message1) { /** ’ÊMI—¹ó‹µ‚ğ’²‚×‚é */
		case FAXCOM_OK:
#if defined (KEISATSU) /* Œx@FAX 05/11/21 Î‹´³˜a */
			if (FCM_ShireiOff == TRUE) { /* ’ÊM‚ğŠJn‚¹‚¸‚Éw—ß‹N“®M†‚ªOFF‚³‚ê‚½ê‡ */
				break;
			}
#endif
			if (tskno_faxcom_complete == 0xffff) {
				cre_tsk(&tskno_faxcom_complete, TSK_CMN_MAN_TIMER10MSTASK, &FaxcomCompleteMessage);
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/01/09 Y.Murata */
				FaxComCompleteDisplaySign = FaxComTXorRX_Sign;
#endif
			}
			break;
		case FAXCOM_REDIAL:
			break;
		case FAXCOM_ERROR:
			/*
			** ‚t‚r‚`d—l‚Ì‚İ’ÊMƒGƒ‰[”­¶Œã‚ÌƒGƒ‰[‚ÍAƒ`ƒFƒbƒNƒƒbƒZ[ƒWˆóšI—¹‚Æ“¯‚É
			** Á‹‚·‚éd—l‚Æ‚µ‚Ü‚·BF-82/92‚ÅÌ—pÏ‚İB By S.Kawasaki 1996/04/26
			** ‘S‚Ä‚ÌdŒü‚¯æ‚É‘Î‰‚µ‚Ü‚· M.Tachibana 1997/04/17
			*/
/*#if defined(USA)*/
			if (CHK_UNI_ClearCommunicationError()) {
				if (SYS_FaxComType == SYS_AUTO_CALLED) {
					/** ‰½‚à‚µ‚È‚¢ */
				}
				else {
					SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_FAXCOM; /** ’ÊMƒGƒ‰[‚ğƒZƒbƒg */
					/* ’ÊMƒGƒ‰[‚ğ’ÊM–ˆ‚ÉƒNƒŠƒA‚·‚éê‡A‚±‚Ìˆ—‚Í•s—v‚É‚È‚é‚Í‚¸@TBD 1995/12/06 Eguchi*/
					BackUpStatusError &= ~SYS_ERROR_FAXCOM;	/* 94.11.16 by T.Nose */
				}
			}
			else {
				SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_FAXCOM; /** ’ÊMƒGƒ‰[‚ğƒZƒbƒg */
				/* ’ÊMƒGƒ‰[‚ğ’ÊM–ˆ‚ÉƒNƒŠƒA‚·‚éê‡A‚±‚Ìˆ—‚Í•s—v‚É‚È‚é‚Í‚¸@TBD 1995/12/06 Eguchi*/
				BackUpStatusError &= ~SYS_ERROR_FAXCOM;	/* 94.11.16 by T.Nose */
			}
/*#else*/
#if (0)
**			SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_FAXCOM; /** ’ÊMƒGƒ‰[‚ğƒZƒbƒg */
**			/* ’ÊMƒGƒ‰[‚ğ’ÊM–ˆ‚ÉƒNƒŠƒA‚·‚éê‡A‚±‚Ìˆ—‚Í•s—v‚É‚È‚é‚Í‚¸@TBD 1995/12/06 Eguchi*/
**			BackUpStatusError &= ~SYS_ERROR_FAXCOM;	/* 94.11.16 by T.Nose */
#endif
			break;
		}
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/18 K.Kawata */
		if ((CL1_ExtFunctionEnableFlag == 1) && (FaxComTXorRX_Sign == RX_COM_MODE)) {
			if (MEM_CheckStoreDoc(SYS_MEM_CLASS1_TX_FILE) == 0) {	/** Œ´e—L‚è **/
				CL1_ExtTransmitErrorFlag = 0;
				CL1_ExtLocalPrtRejectCnt = 120;
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = CL1_SCAN_REQ;
				MainTaskMessage.SubMessage1 = SYS_CLASS1_SCAN_MEMORY;
				snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM;	/** CLASS1“®ì’†ƒNƒŠƒA	*/
				CL1_ExtFunctionEnableFlag = 0;
			}
		}
#endif
		/* add 1997/03/07  By T.Yamaguchi */
		for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
			if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
			 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
			if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
			 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
			 || (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
				/* ‚p‚`‚s•s‹ï‡
				** Šg’£‰ñü‚ÅóM‚ª‚Å‚«‚È‚¢•s‹ï‡C³
				** Šg’£‰ñü‚Ìˆ—‚ª”²‚¯‚Ä‚¢‚½i "& 0x7f")
				** by O.Kimoto 1998/04/13
				*/
				if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)0) {
					break;
				}
#else
				if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)0) {
					break;
				}
#endif
			}
		}
		/* óMŒ´eƒ|[ƒŠƒ“ƒOæ‚èo‚µC³•ª‚É‚Ä’Ç‰Á‚µ‚Ü‚· by T.Soneoka 1997/02/21
		** ƒ|[ƒŠƒ“ƒOæ‚èo‚µƒ‚[ƒhi‹@íŒÅ—L‚r‚—j‚Å‘ãsóM–”t‚ÅƒAƒNƒZƒX‚³‚ê‚½ê‡AƒvƒŠƒ“ƒgƒ‰ƒCƒgˆÊ’u‚ğXV‚µ‚È‚¢
		*/
		if (memory_rx_num < SYS_MEMORY_RX_MAX) {
/*		if ((memory_rx_num < SYS_MEMORY_RX_MAX) && (!(CheckPollingTxType())) )@ */
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];

			if (MemoryRxPrintPoint->StorePage > 0) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT; /* By H.Y 1994/11/17 */
#else
				if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE_PRINT) {
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_FAST_PRINT;
				}
				else {
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT;
					if (CHK_UNI_RxDocReversePrint()) {
						MemoryRxPrintPoint->PrintPage = MemoryRxPrintPoint->StorePage;
						MemoryRxPrintPoint->RotatePage = MemoryRxPrintPoint->StorePage;
					}
				}
#endif

				/* óM‚µ‚Ä‚àƒvƒŠƒ“ƒg‚µ‚È‚¢‚ÅÁ‹‚·‚éƒ‚[ƒh‚ğ’Ç‰Á 1997/11/28  By T.Yamaguchi */
				/* ‚±‚ÌƒXƒCƒbƒ`‚ğ—§‚Ä‚é‚ÍAóMŒ´’†‚ÌƒvƒŠƒ“ƒg‚ğ‚µ‚È‚¢İ’è(UNI_SW_C0-1‚ğ‚O)‚É‚µ‚Äg—p‚·‚é‚±‚Æ */
				if ((SYB_MaintenanceSwitch[37] & 0x20) && (!CHK_UNI_MemoryRxAndPrint()) ) { /* MNT_SW_D7-5 */
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
					MemoryRxPrintPoint->StorePage = 0;
					MemoryRxPrintPoint->RotatePage = 1;
					MemoryRxPrintPoint->PrintPage = 1;
					MemoryRxPrintPoint->ErasePage = 1;
					MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**óMŒ´eƒvƒŠƒ“ƒgƒvƒƒeƒNƒg‰Šú‰» */
					MemoryRxPrintPoint->StackNumber = 0;
					MemoryRxPrintPoint->ReceiveTime = 0;
					MemoryRxPrintPoint->JournalPoint = 0;
					MEM_ClearDoc(SYS_MEM_RX_FILE, memory_rx_num, MEM_IGNORE_BOX_NUMBER);
				}
				else {
					/* 1997/02/10 Y.Murata
					 * ƒvƒŠƒ“ƒ^‚ª¡AóM‚µ‚Ä‚¢‚éŒ´e‚ğƒvƒŠƒ“ƒg‚µ‚Ä‚¢‚éê‡‚Ì‚İƒCƒxƒ“ƒg‚ğ”­s‚µ‚Ü‚·
					*/
					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
						if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
						&& (SYS_DocumentPrintNo == memory_rx_num)) {

							CMN_DisableInterrupt();	/**	Š„‚è‚İ‹Ö~	*/
							PRN_1PageReceived = 1;
							det_evt(EVT_PRN_RESTART);
							CMN_EnableInterrupt();	/**	Š„‚è‚İ‹–‰Â	*/
						}
					}
				}
			}
			else  {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
				MemoryRxPrintPoint->StorePage = 0;
				MemoryRxPrintPoint->RotatePage = 1;
				MemoryRxPrintPoint->PrintPage = 1;
				MemoryRxPrintPoint->ErasePage = 1;
				MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**óMŒ´eƒvƒŠƒ“ƒgƒvƒƒeƒNƒg‰Šú‰» */
	/* 3Line add 1997/03/07  By T.Yamaguchi */
				MemoryRxPrintPoint->StackNumber = 0;
				MemoryRxPrintPoint->ReceiveTime = 0;
				MemoryRxPrintPoint->JournalPoint = 0;
			}
		}
/*#if (PRO_PRINT_TYPE == LASER)*/		/* By H.Y 1994/06/29 */
/*		PRN_1PageReceived = 1;	*/	/* ‚±‚±‚Ì‚Qs‚Í•K—v‚©‚í‚©‚ç‚ñ‚Ì‚Å—vŠm”F 1997/03/07  By T.Yamaguchi */
/*		det_evt(EVT_PRN_RESTART);	*/
/*#endif*/


		SYS_VariableTimer = 5; /* ƒ^ƒCƒ}[Eƒ^ƒXƒN‚Ö‚T•bƒ^ƒCƒ}[‹N“® */
		if ((SYS_VoiceCallAccepted)||(SYS_TensouJushinFlag)) { /* ’ÊMI—¹‚É‰ï˜b—\–ñ‚ª¬—§‚µ‚Ä‚¢‚ê‚Î */
			HungUpCheck = 0; /* ’ÊMI—¹Œã‚Ìó˜bŠíã‚ª‚è‚ÍŒŸo‚µ‚È‚¢ */
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/09/19 */
			if (message == MSG_FAXCOM_END_OFF_HOOK) {
				if (sub_message2 == MSG_FCOM_TEL1_OH) {
					NCU_LineStatus &= ~STD_LINE_STATUS;
 #if 0 /* ‰ï˜b—\–ñ‚É‚æ‚Á‚Ä“Á”Ô‹@”\Á‹ Modified By SMuratec —› 2005/10/14 */
**					NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_RECEIVE);
**					SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_STD_LINE_IN_RECEIVE; 
 #else
					NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_TRANSMIT);
					if ( NCU_LineStatus & STD_HDST_OFFHOOK ) {	/* •t‘®“d˜b‚ÍƒtƒtƒbƒN‚Å‚Í‚È‚¢ */
						SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_LINE;
					}
 #endif
				}
				else if (sub_message2 == MSG_FCOM_TEL2_OH) {
					NCU_LineStatus &= ~EXT_LINE_STATUS;
 #if 0 /* ‰ï˜b—\–ñ‚É‚æ‚Á‚Ä“Á”Ô‹@”\Á‹ Modified By SMuratec —› 2005/10/14 */
**					NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
**					SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_EXT_LINE_IN_RECEIVE; 
 #else
					NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_TRANSMIT);
					if ( NCU_LineStatus & EXT_HDST_OFFHOOK ) {	/* •t‘®“d˜b‚ÍƒtƒtƒbƒN‚Å‚Í‚È‚¢ */
						SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_LINE;
					}
 #endif
				}
			}
#endif /* defined (KEISATSU) */
		}
		else {
			if ((message == MSG_FAXCOM_END_OFF_HOOK) ||
				(message == MSG_FAXCOM_ANS_CHANGE_KAMO)) {
				HungUpCheck = 0; /* ’ÊMI—¹Œã‚Ìó˜bŠíã‚ª‚è‚ÍŒŸo‚µ‚È‚¢ */
			}
			else {
				if (CHK_HANGUP_ALARM_AVAILABLE()) {		/* By M.Tachibana 1997/06/04 */
 #if defined (KEISATSU) /* Œx@FAX Modify by SMuratec —› 2005/10/26 */
					HungUpCheck = 1; /* ’ÊMI—¹Œã‚Ìó˜bŠíã‚ª‚è‚ğŒŸo‚·‚é */
 					if (SYS_STD_LINE_COM == SYS_InternalLineNumber) { /* •W€‰ñü’ÊM */
						hang_up_check = SYS_STD_LINE_COM;
					}
					else { /* Šg’£‰ñü’ÊM */
						hang_up_check = SYS_EXT_LINE_COM;
					}
 #else /* !defined (KEISATSU) */
					HungUpCheck = 1; /* ’ÊMI—¹Œã‚Ìó˜bŠíã‚ª‚è‚ğŒŸo‚·‚é */
 #endif /* defined (KEISATSU) */
				}
				else {
					HungUpCheck = 0; /* ’ÊMI—¹Œã‚Ìó˜bŠíã‚ª‚è‚ÍŒŸo‚µ‚È‚¢ */
				}
			}
		}
		/*----------------------------------------------------*/
		/* ‰ï˜b—\–ñ‚ÌƒNƒŠƒAˆ—								  */
		/* ‰ï˜b—\–ñ‚Ì•\¦^‚k‚d‚c‚ğÁ‚·‚È‚ç‚±‚±‚Å‚â‚Á‚Ä‰º‚³‚¢ */
		/*----------------------------------------------------*/
		SYS_VoiceSwitch = 0;				/* ‰ï˜b—\–ñ‚ÌƒŠƒZƒbƒg */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_FAXCOM); /* ’ÊMÀs’†‚ğƒNƒŠƒA */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY); /* ‰ñüg—p’†ƒNƒŠƒA */

#if defined (KEISATSU) /* Œx@FAX (ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC) Modify by SMuratec —› 2005/10/25 */
		if (DEBUG_NumberDisplay) {
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {	/**	•W€‰ñü	*/
				if (SYS_LineNDStatus == ND_USED_IN_STD) {	/**	•W€‰ñü	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					NCU_ND_InitializeStatus();
				}
			}
			else {	/** Šg’£ƒ‰ƒCƒ“	*/
				if (SYS_LineNDStatus == ND_USED_IN_EXT) {/** Šg’£ƒ‰ƒCƒ“	*/
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
					NCU_ND_InitializeStatus();
				}
			}
		}
		else {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
		}
#else /* !defined (KEISATSU) */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;	/* 1998/10/16 H.Yoshikawa */
#endif /* defined (KEISATSU) */
#if (PRO_CIPHER == ENABLE)
		/* óM—Dæ‚Ì‚½‚ßƒXƒNƒ‰ƒ“ƒuƒ‹‚ğ’†’f‚µ‚Ä‚¢‚½ê‡AƒXƒNƒ‰ƒ“ƒuƒ‹ƒ^ƒXƒN‚æ‚è’ÊM‚ªæ‚É
		** ‹N“®‚µ‚Ä‚¢‚½ê‡A‚±‚±‚ÅƒXƒNƒ‰ƒ“ƒuƒ‹Ä‹N“®‚ğƒZƒbƒg‚µ‚Ü‚· By Y.Suzuki 1998/06/17
		*/
		if ((SYS_CipherInterruptionOn) && (SYS_CipherRestartEnable != 1)) {
			/* TEL/FAX FAX/TEL‘Ò‹@‚Éƒnƒ“ƒhƒZƒbƒg‚ğƒIƒtƒtƒbƒNAƒIƒ“ƒtƒbƒN‚·‚é‚Æ‚±‚±‚É‚­‚é
			** ‚»‚Ìê‡‚ÍAƒŠƒXƒ^[ƒg‚µ‚È‚¢è“®óM‚Å‚«‚È‚­‚È‚é */
			if ((AttemptRxModeSwitch != SYS_TEL_FAX_READY)&&(AttemptRxModeSwitch != SYS_FAX_TEL_READY)) {
				SYS_CipherRestartEnable = 1;
			}
			else {
				/*TEL/FAX FAX/TEL ‚Å‚àƒnƒ“ƒhƒZƒbƒg‚ª‚ ‚°‚ç‚ê‚Ä‚¢‚È‚¢‚Æ‚«‚Í Ä‹N“®‚·‚é */
				if (((NCUStatus & TELEPHONE1_OFF_HOOK) != TELEPHONE1_OFF_HOOK)
				&&((NCUStatus & TELEPHONE2_OFF_HOOK) != TELEPHONE2_OFF_HOOK)) {
					SYS_CipherRestartEnable = 1;
				}
			}
		}
#endif

#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** /* ƒƒ‚ƒŠƒXƒCƒbƒ`‚gF‚Q|‚P‚ğ‚O‚É‚µ‚½‚Æ‚«‚ÉAƒ|[ƒŠƒ“ƒOŒ´e‚ÌŒ —˜‚ğ•ú‚³‚È‚¢
** ** ‚Æ‚¢‚¤•s‹ï‡‚ª”­¶‚µ‚½‚Ì‚Å
** ** By O.Kimoto 1997/07/07
** */
** #if (PRO_MULTI_LINE == ENABLE)
** 			CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
			CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif


		if (((SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
			/* ½·¬Å‚ÌÛ°×°‰º‚ª‚è‚Á‚Ï‚È‚µ‘Îô 1996/08/05 T.Yamaguchi */
			/* ’ÊMƒ^ƒXƒN‚©‚ç‚ÌÒ¯¾°¼Ş‚ğ“Š‚°‚½‚Æ‚«‚Ìƒ^ƒXƒN‚Ì½²¯Áİ¸Ş‚ÅºÏİÄŞ‚ªæ‚ÉÁ‚³‚ê‚Ä‚¢‚ÄA‰º‚ÌğŒ‚Å‚Í‚¶‚©‚ê½·¬ÅÛ°×°‚ª‰º‚ª‚è‚Á‚Ï‚È‚µ‚É‚È‚Á‚Ä‚¢‚½ */
			/*(CheckScannerCommand(SYS_CurrentExecutingCommand->Number.Command)) && */
/*			(SYS_FaxComTxType == SYS_SCANNER_TX) &&		1996/11/28	By T.Yamaguchi	*/
			(SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) &&
			(!((SYS_CurrentExecutingCommand->Status == SYS_EXEC_WAITING) || (SYS_CurrentExecutingCommand->Status == SYS_EXEC_FORWARD_WAITING))))
			|| (SYS_FaxComType == SYS_MANUAL_TX)) { /* ÀsI—¹‚µ‚½’ÊM‚ªƒXƒLƒƒƒi[‘—M‚ÌƒRƒ}ƒ“ƒhƒ^ƒCƒv‚ÅAƒŠƒ_ƒCƒAƒ‹‚É‚È‚ç‚È‚©‚Á‚½‚Æ */
													/* ÀsI—¹‚µ‚½’ÊM‚ªè“®‘—M‚Ì */
			CMN_ResetMemoyFeederTx();
			CMN_ResetStamp();
			CMN_ResetPrimaryMode(); /* “Ç‚İæ‚èƒ‚[ƒhA”Z“x‚ğƒŠƒZƒbƒg */
			CMN_ResetPrimaryContrast(); /* “Ç‚İæ‚èƒ‚[ƒhA”Z“x‚ğƒŠƒZƒbƒg */
			CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
#if (PRO_RED_SCAN == ENABLE)	/* éF“Ç‚İæ‚è 2002/03/05 T.Takagi */
			CMN_ResetRedScan();
#endif
			if (!(SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_DS1_ON+SYS_SENSOR_DS2_ON))) { /* ƒXƒLƒƒƒi[‚ÉŒ´e‚ª‚È‚¯‚ê‚Î */
				CMN_ResetPrimaryDocumentSize(); /* —Dæ“Ç‚İæ‚èƒTƒCƒY‚Ìˆ— */
			}

			/* ƒXƒLƒƒƒi[‘—M ¶’[‰e‚ªo‚é‘Îô T.Nose 1998/03/26 */
			DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* DIPP ’â~ T.nose 1998/03/26 */
#if (PRO_FBS == ENABLE)
			/** ƒ~ƒ‰[ƒ^ƒXƒN‚ğ‹N“®‚µ‚Ä‘Ò‹@ˆÊ’u‚É–ß‚·(SYS_SCANNER_BUSY‚Í‚»‚Ì‚Ü‚Ü) */
			if (CHK_UNI_MirrorReadyModeVariable()) { /* ƒ~ƒ‰[‘Ò‹@ˆÊ’u‰Â“®ƒ‚[ƒh‚È‚ç */
				SCN_MirrorReadyPosition = READY_POSITION_ADF; /* –³ğŒ‚Å‚`‚c‚e */
			}
			else { /* ƒ~ƒ‰[‘Ò‹@ˆÊ’uŒÅ’èƒ‚[ƒh‚È‚ç */
				if (CHK_UNI_MirrorStaticPositionADF()) { /* ‘Ò‹@ˆÊ’u‚`‚c‚e‚È‚ç */
					SCN_MirrorReadyPosition = READY_POSITION_ADF;
				}
				else { /* ‘Ò‹@ˆÊ’u‚e‚a‚r‚È‚ç */
					SCN_MirrorReadyPosition = READY_POSITION_FBS;
				}
			}

			if (SCN_MirrorReadyPosition == READY_POSITION_ADF) { /* ‚`‚c‚e‘Ò‹@ˆÊ’uİ’è‚È‚ç‚Î */
				if ((SCN_MirrorCarriageStatus == MIRROR_HS_ON) /* ADF¨FBSˆÚ“®’†‚Ì’â~ˆ— */
				 || (SCN_MirrorCarriageStatus == MIRROR_FBS_SCANNING)) { /* FBS“Ç‚İæ‚è’†‚Ì’â~ˆ— */
					MirrorTaskInstruction = MIRROR_TASK_TO_ADF_READY;
				}
				else { /* FBS“Çæ‚èI—¹‚Ì */
					MirrorTaskInstruction = MIRROR_TASK_FBS_END_TO_ADF;
				}
			}
			else { /* ‚e‚a‚r‘Ò‹@ˆÊ’uİ’è‚È‚ç‚Î */
				MirrorTaskInstruction = MIRROR_TASK_TO_READY;
			}
			MirrorTaskRequest = TRUE;	/* ƒ~ƒ‰[ƒ^ƒXƒN‹N“®•û–@‚ğ•ÏX  1996/11/20 */

			/** ADFƒXƒLƒƒƒi‘—MI—¹‚ÍƒMƒAƒoƒbƒNƒ‰ƒbƒVƒ…‚ğ—\–ñ‚·‚é */
			if (SYS_ScannerExecMode == SCN_ADF) {
				GearBackLashRequest = TRUE;
			}
#else	/* (PRO_FBS == ENABLE) */
			/** ƒXƒLƒƒƒi[g—p’†‚ğƒNƒŠƒA */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);

			/** ADFƒXƒLƒƒƒi‘—MI—¹‚ÍƒMƒAƒoƒbƒNƒ‰ƒbƒVƒ…‚ğ—\–ñ‚·‚é */
			GearBackLashRequest = TRUE;
#endif /* (PRO_FBS == DISABLE) */

		}

		if (((SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_FaxComTxType == SYS_SCANNER_TRANSMIT))
		  ||(SYS_FaxComType == SYS_MANUAL_TX)) { /* ÀsI—¹‚µ‚½’ÊM‚ªƒXƒLƒƒƒi[‘—M‚ÌƒRƒ}ƒ“ƒhƒ^ƒCƒv‚ÅAƒŠƒ_ƒCƒAƒ‹‚É‚È‚ç‚È‚©‚Á‚½‚Æ */
													/* ÀsI—¹‚µ‚½’ÊM‚ªè“®‘—M‚Ì */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* ˆÚ“® 1994/06/01 Y.Murata */ /* ƒXƒLƒƒƒi[g—p’†‚ğƒNƒŠƒA */
		}
		/* ©“®‚Ì½·¬Å‘—M‚ÅØÀŞ²±Ù‚É‚È‚Á‚½‚ÉŒ´e‚ª–³‚¯‚ê‚Î½·¬ÅºÏİÄŞ‚ğÁ‹	1994/08/27 Y.Murata */
		/* ‚»‚¤‚µ‚È‚¢‚ÆƒR[ƒ‹‚µ‚Ä‚¢‚é‚ÉŒ´e‚ğ‚Ê‚©‚ê‚½‚ç‘—‚éŒ´e‚à–³‚¢‚Ì‚É—\–ñ‚É‚È‚Á‚Ä‚µ‚Ü‚¤‚½‚ß‚Ì‘Î‰ */
		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
			(CheckScannerCommand(SYS_CurrentExecutingCommand->Number.Command)) &&
			((SYS_CurrentExecutingCommand->Status == SYS_EXEC_WAITING) || (SYS_CurrentExecutingCommand->Status == SYS_EXEC_FORWARD_WAITING)) &&
			(!(SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_DS1_ON+SYS_SENSOR_DS2_ON)))) {
			DeleteScannerCommand();
		}
		if (CommandErased[0]) { /* ƒRƒ}ƒ“ƒhÁ‹‚ªƒIƒyƒŒ[ƒVƒ‡ƒ“‚æ‚èÀs‚³‚ê‚Ä‚¢‚ê‚Î */
			CommandErased[0] = 0;
			MltDeleteComFileExecQueueFile(0); /* ƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹AExecQueue‚ğÁ‹ */
		}
#if 0
**		if (CommandErased) { /* ƒRƒ}ƒ“ƒhÁ‹‚ªƒIƒyƒŒ[ƒVƒ‡ƒ“‚æ‚èÀs‚³‚ê‚Ä‚¢‚ê‚Î */
**			CommandErased = 0;
**			DeleteCommandFileExecQueueFile(); /* ƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹AExecQueue‚ğÁ‹ */
**		}
#endif
		/* 1994/06/20 Y.Murata MSG_FAXCOM_END_OFF_HOOK ‚Ì‘‹Œû’Ç‰Á‚É‚Â‚« ‚¿‚å‚Á‚Æ‚İ‚â‚·‚­‚µ‚½ */
		if (message == MSG_FAXCOM_END) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CIŒŸo’†ƒNƒŠƒA */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY; /* ‰ñüg—p’†ƒNƒŠƒA */
#if defined(GBR)
			/*óMŠ®—¹ƒAƒ‰[ƒ€–Â“®ˆ— 1996/08/13 Eguchi */
			if ((CHK_AudibleAlarmON() && !SYB_SecurityRxModeFlag)
			&&	((sub_message1 == FAXCOM_OK) || (sub_message1 == FAXCOM_ERROR && SYS_RxTotalPage > 0))
			&&	(SYS_FaxComType == SYS_AUTO_CALLED || SYS_FaxComType == SYS_MANUAL_RX)
			&&	(FaxComTXorRX_Sign == RX_COM_MODE)
			&&	(!SYS_AudibleAlarmStatus)) {
				SYS_AudibleAlarmStatus |= 0x01; /* –Â“®—v‹ƒZƒbƒg */
			}
#endif
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
#if defined(SAKAKI)	/* 2003/09/20 H.Yoshikawa */
			if (SYB_MaintenanceSwitch[MNT_SW_H4] & TX_INTERVAL) {
				SYS_VariableTimer = (SYB_MaintenanceSwitch[MNT_SW_H4] & TX_INTERVAL) * 60;
			}
#endif
		}
		else if (message == MSG_FAXCOM_END_OFF_HOOK) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* ‰ñüg—p’† QAT1 1994/07/20 by TH92115 */
			SYS_RxDetectFlag = 1;
			if (sub_message2 == MSG_FCOM_TEL1_OH) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
			}
			else if (sub_message2 == MSG_FCOM_TEL2_OH) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
			}
			else if (sub_message2 == MSG_FCOM_HOOK_KEY_OH) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_HOOK_KEY_OFF_HOOK);
			}
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= (SYS_TELEPHONE);
			 /* SYS_TELEPHONE‚ğƒZƒbƒgŒã‚ÉƒƒbƒZ[ƒW‘—M‚µ‚È‚¯‚ê‚Î‚È‚ç‚È‚¢BŸè‚ÉˆÚ“®‹Ö~*/
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
			snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);	/* Jan.18,1995 By T.Nose */
			rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);		/* Jan.18,1995 By T.Nose */
			/*------------------------------------------------------*/
			/**		‘½‹@”\“d˜b§Œäƒ^ƒXƒN‹N“®i‘½‹@”\“d˜b‚ğ‘I‘ğj	*/
			/*------------------------------------------------------*/
			cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_TELEPHONE_OPERATION;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		}
		else if (message == MSG_FAXCOM_ANS_CHANGE_KAMO) {
			/** Switch Answer Mode to	*/
			/* MSG_AFTER_FAXCOM; */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CIŒŸo’†ƒNƒŠƒA */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* ‰ñüg—p’†ƒZƒbƒg */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TAD; /* TADg—p’†ƒZƒbƒg */
			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM)) { /** “àü’Ê˜bó‘Ô‚Å‚È‚¢ QAT SATUKI_H 7/6/1994 */
				cre_tsk(&tskno_NCU_TelephoneOperation, TSK_NCU_TELEPHONEOPERATIONTASK, 0); /* y\v_zÚz„|àr}rwrmqîvmzM */
			}
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_AFTER_FAXCOM;
			snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		}
#if (PRO_PRINTER_RX == ENABLE)
  #if (0) /* Œ³‚É–ß‚µ‚Ü‚· 1998/12/10 by T.Soneoka */
**	#if (PRO_PRINT_TYPE != THERMAL)	/* ‚g‚h‚m‚n‚j‚h‚ÌƒvƒŠƒ“ƒ^óM‚ÍƒvƒŠƒ“ƒgI—¹‚ÉƒƒCƒ“‚Ås‚¢‚Ü‚· 1998/11/12 by T.Soneoka */
**		/* TBD ‚³‚Â‚«/‚à‚İ‚¶‚Í–â‘è‚È‚¢‚ª,ƒ‰ƒxƒ“ƒ_[‚Ìƒoƒbƒtƒ@ƒŠƒ“ƒOóM‚Ì‚Í’ˆÓII Y.Murata */
**		/*	ƒvƒŠƒ“ƒ^óM‚Å‚©‚ÂFAXCOMƒ^ƒXƒN‚ªPRINTER‚ğg—p’†‚É‚µ‚Ä‚¢‚½‚çAPRINTER ‚ğŠJ•ú‚·‚é 1994/05/30 Y.Murata*/
**		if((SYS_RxMemoryFileItem == NULL) && (CMN_CheckFaxComPrinterEnable() == TRUE)) {/* ƒvƒŠƒ“ƒ^óM‚©‚Â’ÊMˆÈŠO‚Ìƒ^ƒXƒN‚ªƒvƒŠƒ“ƒ^‚ğg—p‚µ‚Ä‚¢‚È‚¢*/
**			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* ƒvƒŠƒ“ƒ^ŠJ•ú‚·‚é */
**		}
**	#endif
  #else
		/* TBD ‚³‚Â‚«/‚à‚İ‚¶‚Í–â‘è‚È‚¢‚ª,ƒ‰ƒxƒ“ƒ_[‚Ìƒoƒbƒtƒ@ƒŠƒ“ƒOóM‚Ì‚Í’ˆÓII Y.Murata */
		/*	ƒvƒŠƒ“ƒ^óM‚Å‚©‚ÂFAXCOMƒ^ƒXƒN‚ªPRINTER‚ğg—p’†‚É‚µ‚Ä‚¢‚½‚çAPRINTER ‚ğŠJ•ú‚·‚é 1994/05/30 Y.Murata*/
		if((SYS_RxMemoryFileItem == NULL) && (CMN_CheckFaxComPrinterEnable() == TRUE)) {/* ƒvƒŠƒ“ƒ^óM‚©‚Â’ÊMˆÈŠO‚Ìƒ^ƒXƒN‚ªƒvƒŠƒ“ƒ^‚ğg—p‚µ‚Ä‚¢‚È‚¢*/
			/* 
			** ’ÊM‚ÅƒvƒŠƒ“ƒ^ƒI[ƒvƒ“‚ğs‚Á‚Ä‚¢‚È‚¢‚Æ‚«‚¾‚¯‚e‚b‚l‚ÅSYS_PRINTER_BUSY‚ğ—‚Æ‚µ‚Ü‚·
			** ƒvƒŠƒ“ƒ^ƒI[ƒvƒ“‚µ‚Ä‚©‚ç‚ÍPRT‚Ì‚Ù‚¤‚ÅƒvƒŠƒ“ƒ^‚ğ—‚Æ‚·‚æ‚¤‚É‚µ‚Ü‚·
			** 1999/1/21 by T.Soneoka
			*/
#if (0)
**			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* ƒvƒŠƒ“ƒ^ŠJ•ú‚·‚é */
#else
			if (!PrinterRxPreOpenFlag) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* ƒvƒŠƒ“ƒ^ŠJ•ú‚·‚é */
			}
#endif
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
				/*
				** óM’†‚ÌƒXƒe[ƒ^ƒX‚ğƒŠƒZƒbƒg added by H.Hirao 1998/12/26
				*/
				CMN_DisableInterrupt();
				SYS_DualRestrictionStatus &= ~(0x01);
				CMN_EnableInterrupt();
	#endif
		}
  #endif
#endif
#if (PRO_PRINT_TYPE == LASER)
		if (CMN_CheckF100Model()) {	/* for F100R D65RL 1997/12/05 */
			if ((SYS_FaxComTxType == SYS_SCANNER_TRANSMIT) || (SYS_FaxComType == SYS_MANUAL_TX)) {
				CMN_DisableInterrupt();	/**	Š„‚è‚İ‹Ö~	*/
				PRN_1PageReceived = 1;
				det_evt(EVT_PRN_RESTART);
				CMN_EnableInterrupt();	/**	Š„‚è‚İ‹–‰Â	*/
			}
		}
#endif
		SYS_BackupFaxComType = 0xFF;	/* 1997/12/05 Y.Murata */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
		if (SYS_QucikTxStopStatus & 0x0001) {
			SYS_QucikTxStopStatus = 0;
		}
#endif
#if defined (KEISATSU) /* Œx@FAX Added by SMuratec —› 2005/07/19 */
		if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			}
 #if 0 /* Œx@FAX DVT_ID37 Modify by SMuratec —› 2005/11/12 */
@@			else if ((SYS_RingCounterExt >= (UBYTE)CHK_ExtRingCount())
@@					&& !SYS_HookKeyFlagBk
@@					&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {			/** ’…MğŒ‚ğ–‚½‚µ‚½ */
@@			}
 #else
			else if (CHK_KEIDENRxPriority()
					&& (SYS_RingCounterExt >= (UBYTE)GetRingCounter(1))
					&& !SYS_HookKeyFlagBk
					&& !(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {			/** ’…MğŒ‚ğ–‚½‚µ‚½ */
			}
			/* Œx@FAX DVT_ID45 Added by SMuratec —› 2005/11/14 */
			else if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE) {
			}
 #endif
			else {
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
			}
		}
		/* Œx@FAX DVT_ID2 Added by SMuratec —› 2005/11/19 */
		if (SYS_EXT_LINE_COM == SYS_InternalLineNumber) {	/**	Šg’£‰ñü	*/
			if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE ){ 		/* Šg’£‰ñü‚É’ÊM‚µ‚½ê‡ */
				NCU_LineStatus &= ~EXT_LINE_STATUS;
				NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
			}
		}
		else {
			if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE ) {	/* •W€‰ñü‚É’ÊM‚µ‚½ê‡ */
				NCU_LineStatus &= ~STD_LINE_STATUS;
				NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
			}
		}
#endif /* defined (KEISATSU) */
		break;
	case MSG_FAXCOM_TX_START: /* Nov.7,1994 */
		/*	ƒ|[ƒŠƒ“ƒO‘—M‚Å‚ ‚é‚±‚Æ‚ª”»–¾‚·‚ê‚ÎA’…M‚ÉŠm•Û‚µ‚½ƒvƒŠƒ“ƒ^[‚ğŠJ•ú‚·‚éBŒ»óŠ‘‚Ì‚İ’Ê‚éƒpƒXB By S.K Nov.7,1994 */
		if(CMN_CheckFaxComPrinterEnable() == TRUE) {/** ’ÊM‚Ìƒ^ƒXƒN‚ªƒvƒŠƒ“ƒ^‚ğg—p‚µ‚Ä‚¢‚é */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* ƒvƒŠƒ“ƒ^ŠJ•ú‚·‚é */
		}
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/*
		** óM’†‚ÌƒXƒe[ƒ^ƒX‚ğƒŠƒZƒbƒg added by H.Hirao 1998/12/26
		*/
		CMN_DisableInterrupt();
		SYS_DualRestrictionStatus &= ~(0x01);
		CMN_EnableInterrupt();
	#endif

#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/01/30 */
** 			if (TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) { /** ŒŸõƒ|[ƒŠƒ“ƒO‘—M‚Ìê‡ */
** 				CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
** 			}
** #endif
#else
			if ((TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
				|| (TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)) { /** ŒŸõƒ|[ƒŠƒ“ƒO‘—M‚Ìê‡ */
				CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
			}
#endif

		break;
	case MSG_FAXCOM_RX_START:
		/*	ƒƒ‚ƒŠóM‚Å‚©‚ÂFAXCOMƒ^ƒXƒN‚ªPRINTER‚ğg—p’†‚É‚µ‚Ä‚¢‚½‚çAPRINTER ‚ğŠJ•ú‚·‚é Y.Suzuki*/
		if((SYS_RxMemoryFileItem != NULL) && (CMN_CheckFaxComPrinterEnable() == TRUE)) {/* ƒƒ‚ƒŠóM‚©‚Â’ÊMˆÈŠO‚Ìƒ^ƒXƒN‚ªƒvƒŠƒ“ƒ^‚ğg—p‚µ‚Ä‚¢‚È‚¢*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* ƒvƒŠƒ“ƒ^ŠJ•ú‚·‚é */
		}

#if (0)
** /* ƒƒ‚ƒŠ‘—M’†‚ÌŠm”FƒvƒŠƒ“ƒg•s‹ï‡ By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
			CMN_ReleasePollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif

		break;
	case MSG_BUFFERING_PRINT_START:
		break;
	/* ƒvƒŠƒ“ƒ^óM‚©‚çƒvƒŠƒ“ƒ^ƒGƒ‰[‚Å‘ãsóM‚ÉˆÚs‚µ‚½‚Æ‚«‚Ìˆ— */	/* 1994/07/20 Y.Murata */
	case MSG_FAXCOM_PRINTER_ERROR:
#if (PRO_PRINTER_RX == ENABLE) /* ported from rice by H.Hirao 1998/12/10 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** ƒvƒŠƒ“ƒ^g—p’†‚ğƒNƒŠƒA */
		switch (sub_message1) {		/** ƒvƒŠƒ“ƒ^[ƒGƒ‰[‰ğÍ */
		case MSG_FAXCOM_NO_PAPER:		/* ‹L˜^†Ø‚ê (•ƒGƒ“ƒhƒ}[ƒN‚à) */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
			break;
		case MSG_FAXCOM_CUTTER_ERROR:	/* ƒJƒbƒ^[ƒGƒ‰[ */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
			break;
		case MSG_FAXCOM_PAPER_JAM:		/* ƒWƒƒƒ€ */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
			break;
		case MSG_FAXCOM_NO_INK:			/* ƒhƒi[Ø‚ê */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_INK;
			break;
		case MSG_FAXCOM_TH_HI_TEMP:		/* ‚s^‚gƒnƒCƒeƒ“ƒv */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
			break;
		case MSG_FAXCOM_3M_OVER:		/* 3mŒ´e’·ƒI[ƒo */ /* added by H.Hirao 1998/12/16 */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_3M_OVER;
			break;
		default:	/* ƒJƒo[ƒI[ƒvƒ“‚ÍƒZƒ“ƒT[ƒ^ƒXƒN‚ÅŠÄ‹‚µ‚Ä‚é‚©‚ç‚±‚±‚Å‚ÍƒGƒ‰[ƒZƒbƒg‚µ‚È‚­‚Ä‚æ‚¢‚¾‚ë‚¤ */
			break;
		}
#endif
		break;
	case MSG_FAXCOM_SET_JOURNAL:
		if (SYS_JournalRequest[0] == SYS_JOURNAL_REQ_NOTHING) {
			SYS_JournalRequest[0] = SYS_JOURNAL_REQ;
		}
		else {
			SYS_JournalRequest[0] = SYS_JOURNAL_REQ;
		}
		break;
	case MSG_FAXCOM_SCANNER_DECIDE:
#if (PRO_FBS == ENABLE)
#if (0) /* T.Nose 1997/10/13 */
//		/** ‚`‚c‚e‚ÌŒ´e‚Ì—L–³‚ğŠm”F‚µA“Çæ‚è‘•’u(ADF/FBS)‚ğŒˆ’è‚µA
//		**	ƒ~ƒ‰[ƒLƒƒƒŠƒbƒWƒ^ƒXƒN‹N“®‚µ‚ÄAŠ’è‚Ì“Ç‚İæ‚è‘Ò‹@ˆÊ’u‚ÖˆÚ“®‚·‚é
//		*/
//		if (SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS1_ON) {	/* ADF‚ÉŒ´e‚ª‚ ‚é */
//			SYS_ScannerExecMode = SCN_ADF;
//			MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
//		}
//		else {			/* ADF‚ÉŒ´e‚ª‚È‚¢ */
//			SYS_ScannerExecMode = SCN_FBS;
//			MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
//		}
#endif
		if (SYS_ScannerExecMode == SCN_ADF) {
			MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
		}
		else {
			MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
		}

		SYS_IsMirrorScanReady = FALSE;
		MirrorTaskRequest = TRUE;

		if (SYS_ScannerExecMode == SCN_ADF) {
			SCN_DocumentStatus = SCN_DOC_ADF_1ST_PAGE;
		}
		else {		/* SCN_FBS */
			SCN_DocumentStatus = SCN_DOC_READY;
		}
#else /* (PRO_FBS == ENABLE) */
	#if (PRO_DOC_IN == ENABLE)	/** Add By M.Kotani ANZU_L QAT Bug Fix */
	/* F100‚ÅƒXƒLƒƒƒi‘—Mƒnƒ“ƒhƒVƒF[ƒNŒãAƒGƒ‰[‚ÅA‚»‚Ì‚Ü‚Üƒƒ‚ƒŠ‘—M‚µ‚½Œ´e‚ªk‚ŞBƒm[ƒ}ƒ‹‘¬“x‚ÅŒJ‚è‚Ş*/
		SCN_DocumentStatus = SCN_DOC_READY;
	#else
		SCN_DocumentStatus = SCN_DOC_ADF_1ST_PAGE;
	#endif /* (PRO_DOC_IN == ENABLE) */
#endif /* (PRO_FBS == DISABLE) */
		/* ƒXƒLƒƒƒ“ŠJn‚Éƒ‚[ƒ^[‚ª“®‚©‚È‚­‚È‚é‚±‚Æ‚ª‚ ‚é‚½‚ß
		*  ‹N“®‘O‚ÉƒXƒLƒƒƒi‚ğ‰Šú‰»‚·‚é
		*		1997/06/02 s.takeuchi
		*/
#if (PRO_IMAGE_PROCESSOR !=	IMAGE_PROCESSOR_LC82103)	/* 1998/10/31 by H.Hirao */
		SCN_Init();					/** ƒXƒLƒƒƒi[—pƒQ[ƒgƒAƒŒƒC‚Ì‰Šúİ’è */
#endif
		break;
	default:
		break;
	} /* End of ’ÊMˆ— */
#if (PRO_DOC_IN == ENABLE)
 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
/* 
** Œ´e”ro’†‚ÉŒ´eŒJ‚è‚İ‚ªŒÄ‚Î‚ê‚Ä‚àŒ´eŒJ‚è‚İƒ^ƒXƒN‚ğƒNƒŠƒGƒCƒg‚·‚é‚æ‚¤‚É‚µ‚Ü‚·
** Œ´eŒJ‚è‚İƒ^ƒXƒN‚Ì’†‚Å”roŠ®—¹‚·‚é‚Ü‚Å‘Ò‚Â‚æ‚¤‚É‚µ‚Ü‚·
** 1999/02/12 by T.Soneoka
*/
#if (0)
**	if ((!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN))
**	 && CMN_CheckScanEnable()
**	 && CMN_CheckFeederCommandEmpty()
**	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_IN) /* 7/11/1994 */
**	 &&	!(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_OUT)) { /* 7/11/1994 */
#else
	if ((!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN))
	 && CMN_CheckScanEnable()
	 && CMN_CheckFeederCommandEmpty()
 /* ’ÊMI—¹‚Ìê‡AŒ´e”ro’†AŒ´eŒJ‚è‚İ•s‰Â */
 #if(0)		/* Œx@FAX QAT Added by SMuratec K.W.Q 2005/12/08 */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_IN)) {
 #else
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_IN)
	 &&	!(SYS_MachineStatus[SYS_MACHINE_STATUS]&SYS_FEED_OUT)) { /* 7/11/1994 */
 #endif
#endif
		if (DS1()) {
			/* ‚`‚c‚e‚ÉŒ´e‚ªƒZƒbƒg‚³‚ê‚Ä‚¢‚½‚çŒ´e‚ğŒJ‚è‚Ş */
			if (tskno_DocumentInTask == 0xffff) {
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_IN;
				cre_tsk(&tskno_DocumentInTask, TSK_MAN_DOCUMENTINTASK, 0);
			}
		}
	}
 #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.2.26 K.Kawata */
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)) {
		PRN_MD9402_INT_Timing();
	}
#endif
}
