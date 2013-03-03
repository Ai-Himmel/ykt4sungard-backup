/*---------------------------------------------------------------------------------------*/
/*  僾儘僕僃僋僩 : POPLAR_F                                                              */
/*  僼傽僀儖柤   : MDM_ECM.C                                                             */
/*  嶌惉幰       :                                                                       */
/*  擔  晅       : 1999/01/12                                                            */
/*  奣  梫       : 俤俠俵娭學                                                            */
/*  廋惓棜楌     :                                                                       */
/*	keyword			:[MDM]                                                               */
/*	machine			:[SH7043,V53]                                                        */
/*	language		:[MS-C(Ver.6.0)]                                                     */
/*---------------------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mnt_sw.h"  /* for SYB_MaintenanceSwitch by H.Kubo 1998/01/23 */
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */
#include "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1997/10/08 */

#if defined (KEISATSU) /* 寈嶡FAX 05/06/27 愇嫶惓榓 */
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\define\s1_pro.h"
#endif

/********
** ext_v
********/
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\bkupram.h" /* for SYB_MaintenanceSwitch by H.Kubo 1998/01/23 */

/*************************************************************************
	module		:[俤俠俵憲怣儌僨儉僆乕僾儞]
	function	:[
		1.儌僨儉惂屼僄儕傾弶婜壔
		2.巜掕偺儌僨儉僐儞僼傿僌儗乕僔儑儞傪幚峴偡傞
		3.俤俠俵僼儗乕儉娔帇僞僗僋傪婲摦偡傞
		4.倁侾俈帪丄僀僐儔僀僓儂乕儖僪俷俶偡傞
	]
	return		:[
		側偟
	]
	common		:[
		ModemControl
		ModemBlock
		MDM_PhaseC_Status
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void near	TxEcmOpen(void ){}]
	date		:[1993/12/24]
	update		:[1995/12/12]
	author		:[慮崻壀戱丄栘尦廋]
*************************************************************************/
void TxEcmOpen(void)
{
#if defined (KEISATSU) /* 寈嶡FAX 05/06/27 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		/* MDM_SetIO(POS_HDLC, OFF); */
		/* MDM_SetIO(POS_TPDM, OFF); */
		SetDTC_IntFromS1(); /* DTC妱傝崬傒傪S1偐傜偵偡傞 */
		
		if ((ModemBlock.Mode == MODE_TX_ECM) && (DBG_ECM_OriginalPosition == 1)) {
			S1_OpenECM_Tx(FCM_S1_Senyo); /* S1僆乕僾儞 */
		}
	}
	else {
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
	}
#endif

	/* 儌僨儉僐儞僩儘乕儖僽儘僢僋弶婜壔 */
	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);

#if (PRO_CLASS1 == ENABLE) /* added by H.Kubo */
	ModemControl.WritePoint = MDM_ModemBufferFirstPoint;
	ModemControl.ReadPoint = MDM_ModemBufferFirstPoint;
#endif

	/* 岎怣儌乕僪傪憲怣俥俽俲偵愝掕 */
	ModemBlock.Mode = MODE_TX_ECM;								/**	岎怣儌乕僪愝掕	*/

	/* 儌僨儉僗僥乕僞僗愝掕 俫俢俴俠儌乕僪
	 *                      僼儔僌憲弌拞
	 *                      扨撈僐儅儞僪乛儗僗億儞僗
	 *                      憲怣儌乕僪
	 */
	ModemControl.Status = STAT_FRSTON + STAT_HDLCMOD + STAT_REQRES + STAT_TXMOD;

	/*	儌僨儉僐儞僼傿僌幚峴		*/
	ModemConfig(WRITE_MODE);

	MDM_SetFlag2Tx(2); /* 僼儗乕儉娫僼儔僌偑侾偱偼丄帪乆僼儔僌傪庢傝偙傏偡庴怣婡偑偁傞偺偱丄俀偵偟傑偡丅by H.Kubo 1999/07/01 */

#if defined (KEISATSU) /* 寈嶡FAX 05/11/11 愇嫶惓榓 */
	if (FCM_S1_Scramble == FALSE) {
		MDM_SetIO(POS_NSIE,ON);	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */
	}
#else
	MDM_SetIO(POS_NSIE,ON);	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */
#endif
	
#if defined (KEISATSU) /* 寈嶡FAX 05/06/27 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		MDM_SetIO(POS_HDLC, OFF);
		MDM_SetIO(POS_TPDM, OFF);
		/* SetDTC_IntFromS1(); */ /* DTC妱傝崬傒傪S1偐傜偵偡傞 */
		
		/* S1_OpenECM_Tx(FCM_S1_Senyo); */ /* S1僆乕僾儞 */
		
		/* S1_SetRTS(1); */ /* RTS憲弌 */
		/* CTS_Check(); */ /* CTS僠僃僢僋 */
	}
#endif
	
	/**	俤俠俵憲怣僼儗乕儉娔帇僞僗僋婲摦	*/
	tskno_TxEcmControl = 0xffff;
	cre_tsk(&tskno_TxEcmControl, TSK_MDM_TXECMFRAMECONTROLTASK, 0);

	/*	僀僐儔僀僓儂乕儖僪愝掕	*/
	if ((CHK_V17EqualizerHold()) && (ModemBlock.Type == TYPE_V17)) {
		EqualizerHoldOn();
	}
	MDM_PhaseC_Status = 0;
}


/*************************************************************************
	module		:[俤俠俵憲怣儌僨儉儔僀僩]
	function	:[
		1.巜掕偝傟偨僶僢僼傽愭摢傾僪儗僗偲僨乕僞悢傪儌僨儉僶僢僼傽僐儞僩儘乕儖僽儘僢僋偵搊榐偡傞
		2.儌僨儉偑俬俢俴俤帪丄儌僨儉憲怣俢俵俙傪婲摦偡傞
	]
	return		:[
		側偟
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[
		妱傝崬傒嬛巭偺忬懺偱峴偆
	]
	date		:[1993/12/24]
	author		:[慮崻壀戱]
*************************************************************************/
void  TxEcmWrite(UBYTE  *buffer, UWORD count)
{
	/*----------------------*/
	/*	憲怣僼儗乕儉搊榐	*/
	/*----------------------*/
	MDMWPNT.TopAddress = buffer;	/**	儌僨儉僶僢僼傽彂偒崬傒埵抲偵僶僢僼傽億僀儞僞傪搊榐	*/
	MDMWPNT.DataCount = count;	/**	儌僨儉僶僢僼傽彂偒崬傒埵抲偵僨乕僞僇僂儞僩傪搊榐	*/

	/*
	** 慡婡庬偵斀塮偝偣傑偡丅by H.Kubo 1999/01/26 
	*/	
	/*
	** added by H.Hirao 1998/12/10
	*/
	IncModemControlUsedCount();

	/*--------------------------------------*/
	/*	儌僨儉僶僢僼傽彂偒崬傒埵抲峏怴張棟	*/
	/*--------------------------------------*/
	NextMdmBufWritePointSetExtRom();
	/*------------------------------------------------------*/
	/*	憲怣俢俵俙婲摦奐巒儊僢僙乕僕憲怣					*/
	/*	MSG_TX_FSK_START:	俥俽俲憲怣僼儗乕儉娔帇僞僗僋傊	*/
	/*------------------------------------------------------*/
	CMN_DisableInterrupt();
	if ((ModemControl.Status & STAT_ACT) != STAT_ACT) {
		ModemControl.Status |= STAT_ACT;	/**	儌僨儉僗僥乕僞僗傪俙俠俿俬倁俤偵愝掕	*/
		CMN_EnableInterrupt();
		ModemMessage.Message = MSG_TX_FSK_START;
		snd_msg(mbxno.MDM_Task, &ModemMessage);
	}
	CMN_EnableInterrupt();
}


/*************************************************************************
	module		:[俤俠俵憲怣儌僨儉僗僞乕僩]
	function	:[
		1.儌僨儉撪晹僐儞僩儘乕儖偺撉傒偩偟埵抲偵帵偝傟傞丄僶僢僼傽傾僪儗僗偲僨乕僞悢偱
		, 儌僨儉俢俵俙愝掕偡傞
		2.儌僨儉俢俵俙儅僗僋夝彍偡傞
	]
	return		:[
		側偟
	]
	common		:[
		ModemControl
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/24]
	author		:[慮崻壀戱]
*************************************************************************/
void 	TxEcmStart(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	/*--------------------------*/
	/*	儌僨儉俢俵俙愝掕	*/
	/*--------------------------*/
	CMN_DisableInterrupt();
#if defined (KEISATSU) /* 寈嶡FAX 05/07/21 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		S1_HDLC_TxLast(0);
	}
	else {
		MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
	}
#else
	MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
#endif
	MDM_LastData = ON;
	CMN_EnableInterrupt();

	ModemWriteDMA_Data.Channel		= DMA_CH_TX;
	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	愨懳傾僪儗僗偵曄姺	*/

	/** 俼俀俉俉俥偱偼丄俥俠俽傪寁嶼偡傞偨傔偵嵟屻偺侾倐倷倲倕偼俤俶俢丵俿俠偺撪晹偱峴偄傑偡丅By O.K Dec.12,1995 **/
	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount - 1; /* Modified for DMA routine of Atlanta by H.Kubo 1997/06/25 */
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

	/*----------------------------------*/
	/*	儌僨儉俢俵俙儅僗僋夝彍	*/
	/*----------------------------------*/
	/* Added by H.Kubo 1997/10/08
	**儌僨儉梡 DREQ 堦杮偵側偭偨偨傔丄 I/O 億乕僩偱憲庴怣愗傝懼偊丅
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	DMA_RequestEnable(ModemWriteDMA_Data.Channel);/* 1st arg. ModemWriteDMA_Data.Item is deleted by H. Kubo, 1997/06/24 */

	/*--------------------------------------------------*/
	/*	儌僨儉僗僥乕僞僗愝掕丂僼儔僌憲弌俷俥俥			*/
	/*	丂丂丂丂丂丂丂丂丂丂丂儌僨儉僨僶僀僗傾僋僥傿僽	*/
	/*丂丂丂丂丂丂丂丂丂丂丂丂俥俠俽妱傝崬傒			*/
	/*--------------------------------------------------*/
	ModemControl.Status &= STAT_FRSTOFF;	/**	僼儔僌僔乕働儞僗憲弌僗僩僢僾	*/
	ModemControl.Status |= STAT_ACT + STAT_ALSENT;	/**	儌僨儉僗僥乕僞僗傪俙俠俿俬倁俤偵愝掕	*/
													/**	儌僨儉僗僥乕僞僗傪俥俠俽憲弌妱傝崬傒偵愝掕	*/
}

#if defined (KEISATSU) /* 寈嶡FAX 05/08/24 愇嫶惓榓 */
/**************************************************************************************************/
/**
	@brief		俤俠俵憲怣儌僨儉僗僞乕僩(RTS憲怣)
	
	@li			
	@param		
	@return		側偟
	@note		
	@date		2005/08/24 嶌惉
	@author		愇嫶惓榓
*/
/**************************************************************************************************/
void TxEcmStartWithRTS_Sent(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	/*--------------------------*/
	/*	儌僨儉俢俵俙愝掕	*/
	/*--------------------------*/
	CMN_DisableInterrupt();
#if defined (KEISATSU) /* 寈嶡FAX 05/07/21 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		S1_HDLC_TxLast(0);
	}
	else {
		MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
	}
#else
	MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
#endif
	MDM_LastData = ON;
	CMN_EnableInterrupt();

	ModemWriteDMA_Data.Channel		= DMA_CH_TX;
	ModemWriteDMA_Data.SrcAddress	= (UDWORD)MDMRPNT.TopAddress;	/*	愨懳傾僪儗僗偵曄姺	*/

	/** 俼俀俉俉俥偱偼丄俥俠俽傪寁嶼偡傞偨傔偵嵟屻偺侾倐倷倲倕偼俤俶俢丵俿俠偺撪晹偱峴偄傑偡丅By O.K Dec.12,1995 **/
	ModemWriteDMA_Data.Counter		= MDMRPNT.DataCount - 1; /* Modified for DMA routine of Atlanta by H.Kubo 1997/06/25 */
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_MEMORY_TO_IO;
	DMA_SetupDMAU(&ModemWriteDMA_Data);

	/*----------------------------------*/
	/*	儌僨儉俢俵俙儅僗僋夝彍	*/
	/*----------------------------------*/
	/* Added by H.Kubo 1997/10/08
	**儌僨儉梡 DREQ 堦杮偵側偭偨偨傔丄 I/O 億乕僩偱憲庴怣愗傝懼偊丅
	*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
	SelectDreqDirection(TX_DMA);
#else
	SetModemDMA_DirectionTx();
#endif
	
	S1_OpenECM_Tx(FCM_S1_Senyo); /* S1僆乕僾儞 */
	if ((DBG_DelayAfterS1Open / 10) > 0) {
		wai_tsk(DBG_DelayAfterS1Open / 10);
	}
	S1_SetRTS(1); /* RTS憲弌 */
	CTS_Check(); /* CTS僠僃僢僋 */
	if ((DBG_DelayAfterRTC / 10) > 0) {
		wai_tsk(DBG_DelayAfterRTC / 10);
	}
	DMA_RequestEnable(ModemWriteDMA_Data.Channel);/* 1st arg. ModemWriteDMA_Data.Item is deleted by H. Kubo, 1997/06/24 */

	/*--------------------------------------------------*/
	/*	儌僨儉僗僥乕僞僗愝掕丂僼儔僌憲弌俷俥俥			*/
	/*	丂丂丂丂丂丂丂丂丂丂丂儌僨儉僨僶僀僗傾僋僥傿僽	*/
	/*丂丂丂丂丂丂丂丂丂丂丂丂俥俠俽妱傝崬傒			*/
	/*--------------------------------------------------*/
	ModemControl.Status &= STAT_FRSTOFF;	/**	僼儔僌僔乕働儞僗憲弌僗僩僢僾	*/
	ModemControl.Status |= STAT_ACT + STAT_ALSENT;	/**	儌僨儉僗僥乕僞僗傪俙俠俿俬倁俤偵愝掕	*/
													/**	儌僨儉僗僥乕僞僗傪俥俠俽憲弌妱傝崬傒偵愝掕	*/
}
#endif

/*************************************************************************
	module		:[俤俠俵憲怣儌僨儉僋儘乕僘]
	function	:[
		1.俤俠俵僼儗乕儉娔帇僞僗僋傛傝丄儊僢僙乕僕乮慡僼儗乕儉憲弌姰椆乯傪庴偗傞
		2.俤俠俵僼儗乕儉娔帇僞僗僋傪廔椆偡傞
		3.儌僨儉俢俵俙儅僗僋偡傞
		4.儌僨儉僋儘乕僘傪幚峴偡傞
	]
	return		:[側偟]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/24]
	author		:[慮崻壀戱]
*************************************************************************/
#define	MSG_ECM_CLOSE_TIME_OVER	91
void 	TxEcmClose(void)
{
	MESSAGE_t	*MDM_Msg;
	struct	Timer10msData_t EcmCloseTimer;
	UWORD time;

	/*--------------------------------------------------------------------------*/
	/* 俤俠俵憲怣儖乕僾懳嶔														*/
	/* 俤俠俵僋儘乕僘僞僀儉傾僢僾帪娫傪愝掕偡傞	                                */
	/* 僞僀儉傾僢僾帪娫偼儌僨儉僶僢僼傽俉杮暘憲弌偡傞偺偵偐偐傞帪娫傪愝掕偡傞	*/
	/* 俉亊俀俇俀倐倷倲倕亖俀侽俋俇倐倷倲倕										*/
	/*--------------------------------------------------------------------------*/
	switch (ModemBlock.Speed) {
	case SPEED_33600:
		time =  500; /* 2096/4200= 499ms */
		break;
	case SPEED_31200:
		time =  540; /* 2096/3900= 537ms */
		break;
	case SPEED_28800:
		time =  590; /* 2096/3600= 582ms */
		break;
	case SPEED_26400:
		time =  640; /* 2096/3300= 635ms */
		break;
	case SPEED_24000:
		time =  700; /* 2096/3000= 698ms */
		break;
	case SPEED_21600:
		time =  780; /* 2096/2700= 776ms */
		break;
	case SPEED_19200:
		time =  880; /* 2096/2400= 873ms */
		break;
	case SPEED_16800:
		time = 1000; /* 2096/2100= 998ms */
		break;
	case SPEED_14400:
		time = 1170; /* 2096/1800=1164ms */
		break;
	case SPEED_12000:
		time = 1400; /* 2096/1500=1397ms */
		break;
	case SPEED_9600:
		time = 1750; /* 2096/1200=1746ms */
		break;
	case SPEED_7200:
		time = 2330; /* 2096/900=2329ms */
		break;
	case SPEED_4800:
		time = 3500; /* 2096/600=3493ms */
		break;
	case SPEED_2400:
	default:
		time = 6990; /* 2096/300=6987ms */
		break;
	}
	EcmCloseTimer.Time = (time/10);	/**	俥俽俲憲弌俵俙倃帪娫愝掕	*/
	EcmCloseTimer.SendMBX = mbxno.MDM_TxEcmControlTask;	/**	儊僢僙乕僕庴怣丄儊僀儖儃僢僋僗愝掕	*/
	EcmCloseTimer.ReturnValue = MSG_ECM_CLOSE_TIME_OVER;	/**	栠傝抣愝掕	*/
	timerID_EcmCloseTimer = 0xFF;  /* Added by H.Kubo 1997/12/15, replacing tskno_EcmCloseTimer */
	CMN_MultiTimer10msStart(&timerID_EcmCloseTimer, &EcmCloseTimer); /* 僞僀儅婲摦 */

	switch (MDM_PhaseC_Status) {
	case	TX_PAGE_END:
	case	TX_BLOCK_END:
	case	TX_1M_OVER:
		do {
			rcv_msg(mbxno.MDM_TxEcmControlTask, &MDM_Msg);	/**	儊僢僙乕僕庴怣	*/
		} while (!((MDM_Msg->Message == MSG_TX_COMPLETE) ||
		           (MDM_Msg->Message == MSG_ECM_CLOSE_TIME_OVER)));

		break;
	case	TX_STOPPED:
		if (MDM_TxForceStop() == 0) {	/* PRO_QUICK_TX */
			do {
				rcv_msg(mbxno.MDM_TxEcmControlTask, &MDM_Msg);	/**	儊僢僙乕僕庴怣	*/
			} while (!((MDM_Msg->Message == MSG_TX_COMPLETE) ||
			           (MDM_Msg->Message == MSG_ECM_CLOSE_TIME_OVER)));
		}
		break;
	case	TX_FILE_ERR:
	case	TX_MEM_ERR:
	case	TX_DOC_ERR:
	case	TX_LAMP_ERR:
	default:
		break;
	}
	if (timerID_EcmCloseTimer != 0xFF) {
		CMN_MultiTimer10msStop(&timerID_EcmCloseTimer);	/*僞僀儅廔椆	*/
	}
	/*----------------------*/
	/**	俢俵俙儅僗僋張棟	*/
	/*----------------------*/
	/* DMA_RequestMask(MASTER_DMAU, DMA_CH_TX); */
	DMA_RequestMask(DMA_CH_TX); /* Modified by H. Kubo, 1997/06/17 */

	/*----------------------*/
	/**	儌僨儉僋儘乕僘張棟	*/
	/*----------------------*/
	MDM_SetIO(POS_NSIE,OFF);	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */

#if 0
	if (SYS_V34ProcedureExecuting() == 0) {	/* 倁俁係偱側偄帪 1996/10/17 Y.Murata */
		MDM_SetIO(POS_RTS,OFF);
		wai_tsk(3);		/* at least 15ms */
	}

	MDM_InitialConfig();
#endif

  	/*--------------------------------------*/
  	/**	俤俠俵憲怣僼儗乕儉娔帇僞僗僋廔椆	*/
  	/*--------------------------------------*/
	if (tskno_TxEcmControl != 0xffff) {
		del_tsk(&tskno_TxEcmControl);
	}
	/*----------------------------------*/
	/*	儌僨儉妱傝崬傒娔帇僞僗僋廔椆	*/
	/*----------------------------------*/
	if (tskno_ModemInterrupt != 0xffff) {
		del_tsk(&tskno_ModemInterrupt);
	}
	/*------------------------------*/
	/**	ECM憲弌娔帇僞僀儅僞僗僋廔椆	*/
	/*------------------------------*/
	if (timerID_FcsDetectTimer != 0xFF) {
		CMN_MultiTimer10msStop(&timerID_FcsDetectTimer);
	}

	/*----------------------------------*/
	/*	儌僨儉僶僢僼傽僙儅僼僅儕僙僢僩	*/
	/*----------------------------------*/
	ResetModemBufferSem();
	
#if defined (KEISATSU) /* 寈嶡FAX 05/06/27 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		S1_CloseECM_Tx(); /* S1僋儘乕僘 */
		
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
	}
	else {
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
	}
#endif
	
	/*----------------------------*/
	/* 奀奜擣壜嫟捠懳墳           */
	/* FOREIGN_APPROVAL No.1-8 嘊 */
	/*----------------------------*/
	if (SYS_V34ProcedureExecuting() == 0) {	/* 倁俁係偱側偄帪 1996/10/17 Y.Murata */
		MDM_SetIO(POS_RTS,OFF);
		wai_tsk(3);		/* at least 15ms */
	}
	MDM_InitialConfig2(1);

}

/*************************************************************************
	module		:[俤俠俵憲怣僼儗乕儉娔帇僞僗僋]
	function	:[
		1.儌僨儉妱傝崬傒傛傝丄僼儗乕儉憲弌姰椆僀儀儞僩傪懸偮
		2.儌僨儉僶僢僼傽撉傒弌偟埵抲傪峏怴
		3.僼儗乕儉娫僼儔僌憲弌張棟
		4.師僼儗乕儉憲怣張棟
		5.廔寢僼儔僌憲弌張棟
		6.慡僼儗乕儉憲怣姰椆儊僢僙乕僕憲怣
	]
	return		:[
		側偟
	]
	common		:[
		ModemControl
		ModemMessage
		]
	condition	:[]
	comment		:[]
	date		:[1993/12/09]
	author		:[慮崻壀戱]
*************************************************************************/
void 	MDM_TxEcmFrameControlTask(void)
{
	MESSAGE_t	*MDM_Msg;
	struct	Timer10msData_t EcmTxTimer;
	UBYTE	loop_flg;
	UWORD	ecmtxtime;

	/*--------------------------------------*/
	/**	儌僨儉僶僢僼傽撉傒弌偟埵抲弶婜壔	*/
	/*--------------------------------------*/
	ModemControl.ReadPoint = 0;

	/*----------------------------------*/
	/**	儌僨儉妱傝崬傒娔帇僞僗僋婲摦	*/
	/*----------------------------------*/
	tskno_ModemInterrupt = 0xffff;
	cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);

	/*------------------------------------------*/
	/**	儊僢僙乕僕庴怣張棟						*/
	/*	MSG_TX_FSK_START	:	捠怣僞僗僋傛傝	*/
	/*------------------------------------------*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);
	} while (MDM_Msg->Message != MSG_TX_FSK_START);

	/* For Debug by O.Kimoto 1996/03/04 */
	wai_tsk(1);

	/*------------------------------------------------------*/
	/**	俤俠俵憲怣儌僨儉僗僞乕僩乮倁俆俁儌僨儉俢俵俙婲摦乯	*/
	/*------------------------------------------------------*/
#if defined (KEISATSU) /* 寈嶡FAX 05/08/24 愇嫶惓榓 */
	if ((FCM_S1_Scramble == TRUE) && (DBG_ECM_OriginalPosition == 0)) {
		TxEcmStartWithRTS_Sent();
	}
	else {
		TxEcmStart();
	}
#else
	TxEcmStart();
#endif

	/*----------------------------------------------------------*/
	/**	ECM憲弌俵俙倃帪娫愝掕張棟乮侾侽倣倱僞僀儅梡偵愝掕娷傓乯	*/
	/*	180ms													*/
	/*----------------------------------------------------------*/
	ecmtxtime = SetEcmTime(MDMRPNT.DataCount+128);

	/*----------------------*/
	/*	僞僀儅僞僗僋婲摦	*/
	/*----------------------*/
	EcmTxTimer.Time = (ecmtxtime/10);	/**	俥俽俲憲弌俵俙倃帪娫愝掕	*/
	EcmTxTimer.SendMBX = mbxno.MDM_TaskSub;	/**	儊僢僙乕僕庴怣丄儊僀儖儃僢僋僗愝掕	*/
	EcmTxTimer.ReturnValue = MSG_ECM_TIME_OVER;	/**	栠傝抣愝掕	*/

	timerID_FcsDetectTimer = 0xFF;
	CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &EcmTxTimer); /* 僞僀儅婲摦 */

	loop_flg = 1;
	while (loop_flg) {	/**	嵟廔僼儗乕儉憲弌偡傞傑偱丄僼儗乕儉娔帇幚峴	*/
		/*------------------------------------------------------*/
		/**	儊僢僙乕僕懸偪張棟									*/
		/* 侾丏MSG_TXFRAME_END	儌僨儉妱傝崬傒娔帇僞僗僋傛傝	*/
		/*------------------------------------------------------*/
		do {
			rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);
		} while (!((MDM_Msg->Message == MSG_TXFRAME_END) ||
		           (MDM_Msg->Message == MSG_ECM_TIME_OVER)));

		/*----------------------------------*/
		/**	儌僨儉妱傝崬傒娔帇僞僗僋廔椆	*/
		/*----------------------------------*/
		if (tskno_ModemInterrupt != 0xffff) {
			del_tsk(&tskno_ModemInterrupt);
		}

		/*------------------------------*/
		/**	ECM憲弌娔帇僞僀儅僞僗僋廔椆	*/
		/*------------------------------*/
		if (timerID_FcsDetectTimer != 0xFF) {
			CMN_MultiTimer10msStop(&timerID_FcsDetectTimer);
		}

		/*----------------------------------------------------------------------*/
		/**	儌僨儉僶僢僼傽帒尮夝曻乮崱丄憲弌姰椆偟偨儌僨儉僶僢僼傽傪夝曻偟傑偡乯*/
		/*----------------------------------------------------------------------*/
		ModemBufferSigSem(ModemControl.ReadPoint);
		DecModemControlUsedCount();

		/*--------------------------------------*/
		/**	儌僨儉僶僢僼傽撉傒弌偟埵抲峏怴張棟	*/
		/*--------------------------------------*/
		NextMdmBufReadPointSetExtRom();
		/*----------------------*/
		/**	師僼儗乕儉憲怣張棟	*/
		/*----------------------*/
		if (ModemControl.UsedCount != 0) {	/**	搊榐僼儗乕儉桳傝	*/
			/* Ecm Tx 偺僼儗乕儉娫僼儔僌憲弌帪偺懸偪帪娫惗惉梡 by H.Kubo 1999/01/25 */
			/*------------------------------*/
			/**	僼儗乕儉娫僼儔僌憲弌張棟	*/
			/*------------------------------*/
			/* 俽俫偺儌僯僞偺del_tsk偺張棟偑倁俆俁偵斾傋偰憗偔側偭偰偄傞偨傔
			** 俤俠俵僼儗乕儉娫偺僼儔僌偑侾屄偟偐晅偐側偄R288偺儌僨儉偱腾把娫偺僼儔僌
			** 偑堦屄偺帪偵丄蹦挹教ò倌迋饚鎮鑲眰趥礟PR偑懡敪偡傞偨傔僼儔僌偑嵟掅俀屄埲忋
			** 弌傞傛偆偵僂僃僀僩傪偍偔	
			** by H.Kubo 1999/01/25
			*/
			MDM_EcmTxFillFlags(); /* added by H.Kubo 1999/01/25 */

			/*----------------------------------*/
			/**	儌僨儉妱傝崬傒娔帇僞僗僋婲摦	*/
			/*----------------------------------*/
			tskno_ModemInterrupt = 0xffff;
			cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);
			/*----------------------------------*/
			/*	儌僨儉倁俆俁俢俵俙嵞婲摦張棟	*/
			/*----------------------------------*/

			/* 1999/10/01 Y.Murata   RCP_FRAME_ERROR
			 * 俼俠俹僼儗乕儉偑惓忢偵憲弌偝傟側偄偙偲偑偁傝傑偡丅
			 * 俼俠俹僼儗乕儉偑丄俥俥 侽俁 俠俼俠偺俀僶僀僩寁偺係僶僀僩偺僼儗乕儉
			 * 偲丄俉俇 俠俼俠偺俀僶僀僩偺寁俁僶僀僩僼儗乕儉偵暘偐傟偰偟傑偆偙偲偑偁傝傑偡丅
			 * 偙偺偨傔丄儈僲儖僞偺僨傾儖僞偼丄偙偺僼儗乕儉傪晄摉僼儗乕儉偲偟偰夞慄抐偟傑偡丅
			 * 俿俤俷俥偺惂屼傪傗傔偰傕丄俠俼俠偑惓忢偵晅壛偝傟傞偺偱丄俼俠俹偺帪偼俿俤俷俥偺惂屼傪傗傔傑偡丅
			 * 僐僱僋僒儞僩偵妋擣偟偨偲偙傠丄偙偺懳嶔偱俷俲丅
			 */
			if (MDMRPNT.DataCount <= 3) {
				CMN_DisableInterrupt();
#if defined (KEISATSU) /* 寈嶡FAX 05/07/21 愇嫶惓榓 */
				if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
					S1_HDLC_TxLast(0);
				}
				else {
					MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
				}
#else
				MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
#endif
				MDM_LastData = OFF;
				CMN_EnableInterrupt();	/**	妱傝崬傒嫋壜	*/
				DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, MDMRPNT.DataCount, (UDWORD)MDMRPNT.TopAddress);

			}
			else {
				CMN_DisableInterrupt();
#if defined (KEISATSU) /* 寈嶡FAX 05/07/21 愇嫶惓榓 */
				if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
					S1_HDLC_TxLast(0);
				}
				else {
					MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
				}
#else
				MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
#endif
				MDM_LastData = ON;
				CMN_EnableInterrupt();	/**	妱傝崬傒嫋壜	*/

				/** 俼俀俉俉俥偱偼丄俥俠俽傪寁嶼偡傞偨傔偵嵟屻偺侾倐倷倲倕偼俤俶俢丵俿俠偺撪晹偱峴偄傑偡丅By O.K Jan.26,1996 **/
				/* 1st argument MASTER_DMAU for DMA_RestartDMAU is deleted by H. Kubo 1997/06/24 */
				DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, MDMRPNT.DataCount - 1,(UDWORD)MDMRPNT.TopAddress);
			}

#if 0	/* 1999/10/01 Y.Murata */
//			CMN_DisableInterrupt();
//			MDM_SetIO(POS_TEOF,OFF);	/** 儌僨儉偵俿俤俷俥傪儕僙僢僩偡傞丅 **/
//			MDM_LastData = ON;
//			CMN_EnableInterrupt();	/**	妱傝崬傒嫋壜	*/
//
//			/** 俼俀俉俉俥偱偼丄俥俠俽傪寁嶼偡傞偨傔偵嵟屻偺侾倐倷倲倕偼俤俶俢丵俿俠偺撪晹偱峴偄傑偡丅By O.K Jan.26,1996 **/
//			/* 1st argument MASTER_DMAU for DMA_RestartDMAU is deleted by H. Kubo 1997/06/24 */
//			DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, MDMRPNT.DataCount - 1,(UDWORD)MDMRPNT.TopAddress);
#endif

			ModemControl.Status &= STAT_FRSTOFF;	/**	僼儔僌僔乕働儞僗憲弌僗僩僢僾	*/
			ModemControl.Status |= STAT_ACT + STAT_ALSENT;	/**	儌僨儉僗僥乕僞僗傪俙俠俿俬倁俤偵愝掕	*/

			/*----------------------------------------------------------*/
			/**	ECM憲弌俵俙倃帪娫愝掕張棟乮侾侽倣倱僞僀儅梡偵愝掕娷傓乯	*/
			/*	180ms													*/
			/*----------------------------------------------------------*/
			ecmtxtime = SetEcmTime(MDMRPNT.DataCount+128);
			/*----------------------*/
			/*	僞僀儅僞僗僋婲摦	*/
			/*----------------------*/
			EcmTxTimer.Time = (ecmtxtime/10);	/**	俥俽俲憲弌俵俙倃帪娫愝掕	*/
			EcmTxTimer.SendMBX = mbxno.MDM_TaskSub;	/**	儊僢僙乕僕庴怣丄儊僀儖儃僢僋僗愝掕	*/
			EcmTxTimer.ReturnValue = MSG_ECM_TIME_OVER;	/**	栠傝抣愝掕	*/

			timerID_FcsDetectTimer = 0xFF;
			CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &EcmTxTimer); /* 僞僀儅婲摦 */
		}
		/*--------------------------*/
		/**	師搊榐僼儗乕儉柍偟張棟	*/
		/*--------------------------*/
		else {
			CMN_DisableInterrupt();	/**	妱傝崬傒嬛巭	*/
			ModemControl.Status &= ~STAT_ACT;
			if (ModemBlock.Chain == SET_COMPL) {
				CMN_EnableInterrupt();	/**	妱傝崬傒嫋壜	*/
				loop_flg = 0;
			}
			else {
				CMN_EnableInterrupt();	/**	妱傝崬傒嫋壜	*/
				do {
					rcv_msg(mbxno.MDM_Task, &MDM_Msg);
				} while (MDM_Msg->Message != MSG_TX_FSK_START);
				/*----------------------------------*/
				/**	儌僨儉妱傝崬傒娔帇僞僗僋婲摦	*/
				/*----------------------------------*/
				tskno_ModemInterrupt = 0xffff;
				cre_tsk(&tskno_ModemInterrupt, TSK_MDM_MODEMINTERRUPTTASK, 0);
				/*----------------------------------*/
				/*	儌僨儉倁俆俁俢俵俙嵞婲摦張棟	*/
				/*----------------------------------*/
				TxEcmStart();
				/*----------------------------------------------------------*/
				/**	ECM憲弌俵俙倃帪娫愝掕張棟乮侾侽倣倱僞僀儅梡偵愝掕娷傓乯	*/
				/*----------------------------------------------------------*/
				ecmtxtime = SetEcmTime(MDMRPNT.DataCount+128);
				/*----------------------*/
				/*	僞僀儅僞僗僋婲摦	*/
				/*----------------------*/
				EcmTxTimer.Time = (ecmtxtime/10);	/**	俥俽俲憲弌俵俙倃帪娫愝掕	*/
				EcmTxTimer.SendMBX = mbxno.MDM_TaskSub;	/**	儊僢僙乕僕庴怣丄儊僀儖儃僢僋僗愝掕	*/
				EcmTxTimer.ReturnValue = MSG_ECM_TIME_OVER;	/**	栠傝抣愝掕	*/

				timerID_FcsDetectTimer = 0xFF;
				CMN_MultiTimer10msStart(&timerID_FcsDetectTimer, &EcmTxTimer); /* 僞僀儅婲摦 */
			}
		}
	}
	/*----------------------*/
	/**	廔寢僼儔僌憲弌張棟	*/
	/*----------------------*/
	wai_tsk(50/10);
	/*------------------------------------------------------*/
	/**	儊僢僙乕僕憲怣張棟									*/
	/*	1.MSG_TX_COMPLETE:	捠怣僞僗僋傊乮MDM_TxFskClose())	*/
	/*------------------------------------------------------*/
	ModemMessage.Message = MSG_TX_COMPLETE;
	snd_msg(mbxno.MDM_TxEcmControlTask, &ModemMessage);

	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[俤俠俵庴怣儌僨儉僆乕僾儞]
	functions	:[
		1.儌僨儉惂屼僄儕傾弶婜壔
		2.巜掕偺儌僨儉僐儞僼傿僌儗乕僔儑儞傪幚峴偡傞

	]
	return		:[
		側偟
	]
	common		:[
		ModemControl
		MDM_RxSize
		ModemRxStatus
		]
	condition	:[]
	comment		:[]
	ProtoType	:[void near RxEcmOpen(void ){}]
	date		:[1994/01/11]
	update		:[1995/12/15]
	author		:[慮崻壀戱丄栘尦廋]
*************************************************************************/
void  RxEcmOpen(void)
{
	struct DMA_Data_t ModemWriteDMA_Data;

	UWORD agcgain_value;		/** For V29 7200 start by O.kimoto 1997/02/27 */
	UWORD rlsd_turn_on_value;	/** For V29 7200 start by O.kimoto 1997/02/27 */
	UWORD rlsd_turn_off_value;	/** For V29 7200 start by O.kimoto 1997/02/27 */

#if defined (KEISATSU) /* 寈嶡FAX 05/06/20 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		SetDTC_IntFromS1(); /* DTC妱傝崬傒傪S1偐傜偵偡傞 */
		
		S1_OpenECM_Rx(FCM_S1_Senyo); /* S1僆乕僾儞 */
	}
	else {
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
	}
#endif

	SetClear((UBYTE *)&ModemControl, sizeof(struct mdmcntl_t), 0x00);
	ModemControl.Status = STAT_HDLCMOD+STAT_FLGDET+STAT_ECMMODE;
	ModemRxStatus = 0xff;
#if (PRO_CLASS1 == ENABLE) /* added by H.Kubo */
	ModemControl.ReadPoint = MDM_ModemBufferFirstPoint;
	ModemControl.WritePoint = MDM_ModemBufferFirstPoint;
#endif

	/*----------------------------------*/
	/*	儌僨儉僐儞僼傿僌幚峴			*/
	/*----------------------------------*/
	ModemBlock.Mode = MODE_RX_ECM;
	ModemConfig(READ_MODE);

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARA傛傝堏怉 2002/01/17 T.Takagi */
	/* Nothing */
#else
	/* 倁丏俁係僾儔僀儅儕乕僠儍儞僱儖帪偼俥俴俽俧俽偺妱傝崬傒傪儅僗僋偟傑偡 by O.Kimoto 1996/03/06 */
	if (SYS_V34ProcedureExecuting()) {	/* 倁丏俁係僾儘僩僐儖側傜偽 */
		MDM_SetMaskingRegsiter0A0B(0x0001);				/* SYNCD */
 #if defined (SAKAKI)
		/* R4.2 懳嶔(帋尡拞)丅  PC OFF 偺偲偒丄20P 傑偱偱巊偭偰偄偨 SECRXB傪娔帇偡傞曽朄偱偼偩傔側偙偲偑偁傞丅 by H.Kubo 1998/10/30 *//* 2002/09/18 By M.Maeda */
		if ((SYS_ModemVersion == MDM_L6713_24P)
			|| (SYS_ModemVersion == MDM_L6713_26P)) {
			MDM_SetMaskingRegsiter0C0D(0x8080);				/** P2DET,PNDET,PCOFF **/
			MDM_PreviousPCOFF_Status = MDM_GetIO(POS_PCOFF);
		}
 #endif
	}
#endif

	/** For V29 7200 start by O.kimoto 1997/02/27 */
	if (CHK_V34_V29_7200Special()) {	/* UNISW D6:4 */
		if (!(SYS_V34ProcedureExecuting())) {
			if (ModemBlock.Config == BPS7200_V29) {
				agcgain_value = DspRamAccessReadMethod4(0xA00);
				rlsd_turn_on_value = DspRamAccessReadMethod2(0x134,0x135);
				rlsd_turn_off_value = DspRamAccessReadMethod2(0x136,0x137);
			
				agcgain_value -= 0x1000;	/** 6dBm */
			
				if (agcgain_value >= rlsd_turn_on_value) {
					/** 俼俴俽俢 俿倳倰値 俷俶乛俷俥俥儗儀儖挷惍幚巤 */
					DspRamAccessWriteMethod1(0x10D, 0x04, 0xFB);	/** P.4-43 B. */
					DspRamAccessWriteMethod2(0x134, 0x145, (UWORD)(agcgain_value), 0x0000);	/** P.4-43 C */
					DspRamAccessWriteMethod2(0x136, 0x147, (UWORD)(agcgain_value - 0x22D), 0x0000);	/** P.4-43 C */
					/*MDM_SetIO(POS_NEWC,ON);1997/02/26 Y.M*/		/** P.4-43 D */

					if (MDM_ReceiveLevelExtension == 1) {
						DspRamAccessWriteMethod3(0x0B3C, 0x3700, 0x0000);	/* B3C<-3700h */
					}

				}
			}
		}
	}
	/** For V29 7200 end by O.kimoto 1997/02/27 */

	/*
	** R288F VERSION 24P埲崀偺応崌
	** by H.Kubo 1998/10/05
	*/
	if (!(SYS_V34ProcedureExecuting())) {
		switch (SYS_ModemVersion) {
		case MDM_L6713_13P:
		case MDM_L6713_14P:
		case MDM_L6713_20P:
		case MDM_L6713_22P:
			break;
		case MDM_L6713_24P:
		case MDM_L6713_26P:
#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(媽Rockwell) FM336 僥僗僩梡僐乕僪丅 by H.Kubo 1999/03/08 */
		case MDM_L6719_12P_ES:
		case MDM_L6719_12P_CS:
#endif
		default:
			MDM_EnableFastTrainingDetection(); /* RLSD 偑棫偮慜偐傜丄 valid training sequence 傪専弌偡傞愝掕丅*/
			break;
		}
	}

#if defined (KEISATSU) /* 寈嶡FAX 05/11/11 愇嫶惓榓 */
	if (FCM_S1_Scramble == FALSE) {
		MDM_SetIO(POS_NSIE,ON);	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */
	}
#else
	MDM_SetIO(POS_NSIE,ON);	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */
#endif
	
#if defined (KEISATSU) /* 寈嶡FAX 05/06/20 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		MDM_SetIO(POS_HDLC, OFF);
		MDM_SetIO(POS_TPDM, OFF);
	}
#endif
	
	/*
	** 僼儗乕儉娫僼儔僌偑抁偔偰儌僨儉偑僼儔僌傪庢傝摝偑偟偨偲偒偺媬嵪梡丅
	** H.Kubo 1999/01/22
	*/
	MDM_EcmRxFcsCheckRequest = 0;

	/*--------------------------*/
	/*	儌僨儉俢俵俙愝掕	*/
	/*--------------------------*/
	/* ModemWriteDMA_Data.Item			= MASTER_DMAU; */ /* Deleted by H. Kubo 1997/06/24 */
	ModemWriteDMA_Data.Channel		= DMA_CH_RX;
	/* ModemWriteDMA_Data.StartAddress	= DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]);*/	/*	愨懳傾僪儗僗偵曄姺	*/

	ModemWriteDMA_Data.SrcAddress	= (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0];	/*	愨懳傾僪儗僗偵曄姺	*/

	/* ModemWriteDMA_Data.Counter		= (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1;*/ /*  By O.K Feb.17,1996 */
	ModemWriteDMA_Data.Counter	= FcomEcmSize + MODEM_FRAMING_CODE_LENGTH + 1; /*  Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
	ModemWriteDMA_Data.Unit			= DMA_BYTE_TRANSFER;
	ModemWriteDMA_Data.Direction	= DMA_IO_TO_MEMORY;

	DMA_SetupDMAU(&ModemWriteDMA_Data);

#if defined (KEISATSU) /* 寈嶡FAX 05/08/29 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		SelectDreqDirection(RX_DMA);
		DMA_RequestEnable(DMA_CH_RX); /* DMA婲摦 */
		MDM_DmaStart = MDM_DMA_GO;
	}
#else
#if (0)	/** 俢俵俙偺婲摦偼俵俢俵妱傝崬傒撪偱張棟偟傑偡 By O.K Jan.26,1996 **/
**	DMA_RequestEnable(ModemWriteDMA_Data.Item, ModemWriteDMA_Data.Channel);
#endif
#endif

#if defined(POPLAR_F)
	DMA_RequestEnableSub(DMA_CH_RX);
#endif

#if defined (KEISATSU) /* 寈嶡FAX 05/08/29 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) {
		return;
	}
#endif

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARA傛傝堏怉 2002/01/17 T.Takagi */
	if (MDM_DmaStart == MDM_DMA_MASK) {
		CMN_DisableInterrupt();
		MDM_SetIO(POS_RDBIE,ON);
		MDM_DmaStart = MDM_DMA_READY;

 		/*
 		** R288F VERSION 22P埲崀偺応崌
 		** by H.Kubo 1998/10/17
 		*/
 		IsRlsdAndRdbfOn = 0;

		CMN_EnableInterrupt();
	}
	else {
		outp(0,0);
	}
#else
	if (MDM_DmaStart == MDM_DMA_MASK) {	/** 晄惓妱傝崬傒懳嶔 By O.K Feb.14,1996 **/
		CMN_DisableInterrupt();
		MDM_SetIO(POS_RDBIE,ON);
		MDM_DmaStart = MDM_DMA_READY;

 		/*
 		** R288F VERSION 22P埲崀偺応崌
 		** by H.Kubo 1998/10/17
 		*/
 		IsRlsdAndRdbfOn = 0;

		CMN_EnableInterrupt();
	}
#endif
}


/*************************************************************************
	module		:[俤俠俵庴怣儌僨儉儕乕僪]
	function	:[
		1.俆侽倣倱僞僗僋僂僃僀僩偟側偑傜丄奩摉僼儗乕儉庴怣桳岠懸偪偡傞丅
		丂儌僨儉妱傝崬傒偺拞偱僼儗乕儉庴怣桳岠偵僙僢僩偝傟傞丅
		丂傑偨丄偙偺拞偱僗僩僢僾俽倵媦傃儊儌儕僆乕僾儞乛僾儕儞僞僆乕僾儞堎忢張棟傪尒傞
		2.僼儗乕儉傪庴怣偟偨屻丄僼儗乕儉曗惓張棟傪峴偆
		3.儌僨儉僶僢僼傽彂偒崬傒埵抲峏怴
	]
	return		:[
		RCV_BLOCK:		侾僽儘僢僋庴怣
		RCV_TMOUT:		僞僀儉僆乕僶
		RCV_STOP:		僗僩僢僾俽倵専弌
		RCV_OPEN_ERR:	儊儌儕乛僾儕儞僞僆乕僾儞僄儔乕
	]
	common		:[
		ModemControl
		ModemRxStatus
		MDM_ModemBuffer
		]
	condition	:[]
	comment		:[]
	date		:[1994/01/11]
	author		:[慮崻壀戱]
*************************************************************************/
UBYTE 	RxEcmRead(void)
{
	UWORD	tmout;
	UWORD	tmoutc;
	UBYTE	wrkmsk;
	UBYTE	loop_flg;
	UBYTE 	rx_status_loop_count; /* by H.Kubo 1998/01/28 */

	tmoutc = 0;

	loop_flg = 1;
	while (loop_flg) {
		/*----------------------*/
		/**	奩摉僼儗乕儉儅僗僋	*/
		/*----------------------*/
		wrkmsk = (UBYTE) (1 << ModemControl.ReadPoint);
		/*--------------------------*/
		/**	奩摉僼儗乕儉庴怣懸偪	*/
		/*--------------------------*/
		if (ModemBlock.RxCheck == RX_CHKONLY) {
			if (ModemRxStatus & wrkmsk) {
				return (RCV_TMOUT);
			}
			else {
				return (RCV_BLOCK);
			}
		}
		else {
			/* V34 偱儌僨儉僶僢僼傽俀杮偛偲偵昁偢 wai_tsk 偱 10ms 懸偮傛偆偵偟傑偡丅
			** 33.6Kbps 偱庴怣偟偰偄傞偲偒丄嵟懍栺 61ms 偱儌僨儉僶僢僼傽偑偄偭傁偄偵側傝傑偡丅
			** 偦偺偨傔(?)丄儌僨儉僶僢僼傽堦杮庴怣偡傞偛偲偵 10ms 懸偮偲庴怣偑捛偄偮偒傑偣傫丅
			** 傑偨 PIX 庴怣拞 wai_tsk 偑擖傜側偄偲丄僉乕偑岠偐側偔側傞偙偲偑偁傞偺偱丄偙偺傛偆偵
			** 偟傑偡丅
			*/
			rx_status_loop_count = (wrkmsk & 0x11) ? 0 : 1; /* by H.Kubo 1998/01/28 */
			while (ModemRxStatus & wrkmsk) {

				/** 倁丏俁係帪丄俤俠俵偺僼儗乕儉庴怣偑抶偄偨傔 By O.K Feb.06,1996 **/
				if (ModemBlock.Type != TYPE_V34) {
					tmout = FRAME_WAIT;							/** 尰嵼丂侾侽倣倱丂*/
					wai_tsk(tmout/10);
				}
				else if (rx_status_loop_count++) { /* 嵟弶偼 wai_tsk 偟側偄丅*/
					wai_tsk(1);	/*  By O.K Feb.22,1996 */
				}
				/* 倁丏俁係岎怣偱偼丄俹倰倝倣倎倰倷俠倛倎値値倕倢偺廔抂偼俼俴俽俢價僢僩媦傃
				** 俿倳倰値俷倖倖偱専弌弌棃傞偺偱丄偙偺僞僀儉傾僂僩張棟偼偄傝傑偣傫丅
				** By O.Kimoto 1996/09/11
				**/
				if (!SYS_V34ProcedureExecuting()) {
					if (++tmoutc > (UWORD)(TOUT_FRAME/FRAME_WAIT)) {			/**	尰嵼丂侾俀侽夞娔帇	*/
						return (RCV_TMOUT);								/**	尰嵼丂娔帇帪娫俆侽仏侾俀侽亖俇侽侽侽倣倱	*/
					}
				}
				else {
/* #if defined(POPLAR_F)	壓婰張棟偼慡婡庬嫟捠 By O.Kimoto 2002/10/23 */
					/* 2000/02/04 Y.Murata
					 * 僞僀儉傾僂偼偄傞偲巚偆傫偩偗偳丅丅丅 側偣倁俁係偩偗丅丅丅
					*/
					tmoutc++;
					if (tmoutc > (UWORD)(TOUT_FRAME/FRAME_WAIT)) {	/* 俇昩 */
						return (RCV_TMOUT);							/* 侾侽倣倱 */
					}
/* #endif */
				}

				if (SYS_FaxComStopSwitch() == 1) {
					return (RCV_STOP);
				}
				/** 億僗僩儊僢僙乕僕慡偔庢傟偢懳嶔乮巄掕乯 By O.K Feb.06,1996 **/
				if (SYS_V34ProcedureExecuting()) {
					if (MDM_RlsdTurnOffFlag == 1) {
						MDM_RlsdTurnOffFlag = 0;
						return (RCV_TURNOFF);
					}
				}
				
				/*  By O.Kimoto 1996/09/21 */
				if ((MDM_FedOffFlag == 1) || (MDM_FedOffFlag == 2)) {
					MDM_RlsdTurnOffFlag = 0;
					return (RCV_TURNOFF);
				}
			}
			/* 儌僨儉僶僢僼傽堨傟傪娔帇丅 by H.Kubo 1998/01/23 */
			if (ModemControl.UsedCount > 8) {
				SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_MODEM_BUFFER_OVERLOW;
			}
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/*  僾儕儞僩僨僐乕僪掆巭梫媮僼儔僌丅儌僨儉僶僢僼傽堨傟夞旔偺偨傔丅 By H.Kubo  1998/10/26 */
			/* ported for HINOKI2 2002/01/07 T.Takagi */
			if (ModemControl.UsedCount > ((SYB_MaintenanceSwitch[MNT_SW_E5] & 0xE0) >> 5) ) { /* 儌僨儉僶僢僼傽偺嬻偒偑巆傝彮側偔側偭偨傜僾儕儞僩掆巭梫媮丅 1998/11/12 */
				SYS_PRN_StopRequestFromModem = TRUE;
			}
			else {
				SYS_PRN_StopRequestFromModem = FALSE;
			}
#endif
		}

		/* For Debug  By O.K Feb.17,1996 */
		if ((MDM_ModemBuffer[ModemControl.ReadPoint][ADR_FLD] == 0x7E) &&
			(MDM_ModemBuffer[ModemControl.ReadPoint][CTRL_FLD] == 0xFF)) {
			if (loop_flg != 0) {
				MDM_RxSize[ModemControl.ReadPoint] = MODEM_BUFFER_LENGTH;
				(void)ModemBufferFormatControl(ModemControl.ReadPoint);
			}
		}

		/* For Debug  By O.K Feb.17,1996 */
		if ((MDM_ModemBuffer[ModemControl.ReadPoint][ADR_FLD] == 0x7E) &&
		   ((MDM_ModemBuffer[ModemControl.ReadPoint][CTRL_FLD] == 0x03) ||
		    (MDM_ModemBuffer[ModemControl.ReadPoint][CTRL_FLD] == 0x13))) {
			if (loop_flg != 0) {
				MDM_ModemBuffer[ModemControl.ReadPoint][ADR_FLD] = 0xFF;
			}
		}

		if ((MDM_ModemBuffer[ModemControl.ReadPoint][ADR_FLD] == 0xFF) &&
		   ((MDM_ModemBuffer[ModemControl.ReadPoint][CTRL_FLD] == 0x03) ||
		    (MDM_ModemBuffer[ModemControl.ReadPoint][CTRL_FLD] == 0x13))) {

			/*
			** The following code is ported from ORANGE and modified
			** by H.Kubo 1997/07/17
			*/
			/*
			** 僼儗乕儉娫僼儔僌偑抁偔偰儌僨儉偑僼儔僌傪庢傝摝偑偟偨偲偒偺媬嵪梡丅
			** H.Kubo 1999/01/22
			*/
			if (MDM_EcmRxFcsCheckRequest & (1 << ModemControl.WritePoint)) {
				UWORD	fcs_data;
				/*	SH704X,SH7043	By Y.Suzuki 1996/07/24	*/
				/*	婏悢傾僪儗僗偺儚乕僪傾僋僙僗傪杊巭偡傞偨傔	儌僨儉僶僢僼傽偺嵟屻偺俥俠俽俀僶僀僩傪庢傝弌偡	*/
				fcs_data = (UWORD)(MDM_ModemBuffer[ModemControl.ReadPoint][MDM_RxSize[ModemControl.ReadPoint] - 2]);
				fcs_data <<= 8;
				fcs_data |= MDM_ModemBuffer[ModemControl.ReadPoint][MDM_RxSize[ModemControl.ReadPoint] - 3];
				if (crc(MDM_RxSize[ModemControl.ReadPoint] - 3, MDM_ModemBuffer[ModemControl.ReadPoint]) == fcs_data) {	/**	俠俼俠僠僃僢僋張棟	*/
					loop_flg = 0;										/* 庴怣儌僨儉僶僢僼傽憖嶌 */
				}
				else {
					loop_flg = 1;
				}
				MDM_EcmRxFcsCheckRequest &= ~(1 << ModemControl.WritePoint);
			}
			else {
				/* 儌僨儉偺FCS専嵏傪僷僗偟偰偄傞偺偱丄張棟偑廳偔側傞僜僼僩偱偼FCS専嵏傪偟側偄丅*/
				loop_flg = 0;										/* 庴怣儌僨儉僶僢僼傽憖嶌 */
			}
		}

		if (loop_flg == 1) {
			/*--------------------------------------*/
			/**	儌僨儉僶僢僼傽撉傒弌偟埵抲峏怴張棟	*/
			/*--------------------------------------*/
			NextMdmBufReadPointSetExtRom();
		}
		/*--------------------------------------*/
		/**	奩摉庴怣僼儗乕儉僗僥乕僞僗弶婜壔	*/
		/*--------------------------------------*/
		ModemRxStatus |= wrkmsk;
		/*
		** 慡婡庬偵斀塮偝偣傑偡丅  by H.Kubo 1999/01/26
		*/
		DecModemControlUsedCount();
	}
	return RCV_BLOCK;
}


/*************************************************************************
	module		:[俤俠俵庴怣儌僨儉僋儘乕僘]
	function	:[
		1.儌僨儉俢俵俙儅僗僋偡傞
		2.儌僨儉僋儘乕僘傪幚峴偡傞
	]
	return		:[
		側偟
	]
	common		:[
		ModemBlock
	]
	condition	:[]
	comment		:[]
	date		:[1994/01/11]
	author		:[慮崻壀戱]
*************************************************************************/
void 	RxEcmClose(void)
{
	UBYTE count;
#if 0	/* ECM偱偼NEC儘僢僋傾僢僾偼婲偙偭偰偄側偄偨傔丄懳嶔傪擖傟傑偣傫 2003/03/10 NEWC_LOCKUP_BUG_FIX */
//	UBYTE is_ok;
//	UWORD counter;
#endif

	ModemBlock.Mode = 0;	/* 1997/02/10 Y.Murata */

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARA傛傝堏怉 2002/01/17 T.Takagi */
	/* Nothing */
#else
	/* 倁丏俁係僾儔僀儅儕乕僠儍儞僱儖帪偼俥俴俽俧俽偺妱傝崬傒傪儅僗僋偟傑偡 by O.Kimoto 1996/03/06 */
	if ( SYS_V34ProcedureExecuting()) {	/* 倁丏俁係僾儘僩僐儖側傜偽 */
		MDM_SetMaskingRegsiter0A0B( 0x1003 );				/** ATV25/FLAGS,SYNCD **/
		if (( SYS_ModemVersion == MDM_L6713_24P )
 #if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(媽Rockwell) FM336 僥僗僩梡僐乕僪丅 by H.Kubo 1999/03/08 */
			|| (SYS_ModemVersion == MDM_L6719_12P_ES)
			|| (SYS_ModemVersion == MDM_L6719_12P_CS)
 #endif
			|| ( SYS_ModemVersion == MDM_L6713_26P )) {
			MDM_SetMaskingRegsiter0C0D( 0x8000 );				/** P2DET,PNDET **/
		}
	}
#endif

	MDM_SetIO( POS_NSIE,OFF );	/* 用扪妱傝崬傒傪ON/OFF偟傑偡 By O.K Feb.20,1996 */

	/** 俢俵俙婲摦張棟 By O.K Jan.26,1996 **/
	MDM_SetIO( POS_RDBIE,OFF );
	MDM_DmaStart = MDM_DMA_MASK;

	DMA_RequestMask( DMA_CH_RX ); /* Modified by H. Kubo, 1997/06/17 */
	/* 庴怣儗儀儖偺僔僼僩 1997/01/28 Y.Murata */
	MDM_ReSetReceiveLevelExtension();

	/** For V29 7200 start by O.kimoto 1997/02/27 */
	if (!( SYS_V34ProcedureExecuting())) {
		if ( ModemBlock.Config == BPS7200_V29 ) {
			DspRamAccessWriteMethod1( 0x10D, 0x00, 0xFB );	/** P.4-43 F. */
		}
	}
	/** For V29 7200 end by O.kimoto 1997/02/27 */

	/* 1997/02/10 Y.Murata
	 *
	 *
	*/
	if ( SYS_V34ProcedureExecuting() == 0 ) {

#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
		count = 0;
		if ( MDM_GetIO(POS_SYNCD )) {
			do {
				wai_tsk( 1 );
				count++;
				if ( count > 4 ) {
					break;
				}
			} while ( MDM_GetIO( POS_SYNCD ));
		}
#else
		count = 0;
		if ( MDM_GetIO(POS_SYNCD )) {
			do {
				wai_oneshot( 1 );
				count++;
				if ( count > 30 ) {
					break;
				}
			} while ( MDM_GetIO( POS_SYNCD ));
		}
#endif
		else {
			wai_tsk( 1 );
		}
#if 0	/* ECM偱偼NEC儘僢僋傾僢僾偼婲偙偭偰偄側偄偨傔丄懳嶔傪擖傟傑偣傫 2003/03/10 NEWC_LOCKUP_BUG_FIX */
//		is_ok = 0;
//		counter = 0;
//		while (1) {
//			if (!MDM_GetIO(POS_RLSD)) {
//				is_ok++;
//				if (is_ok > 2) {	/* 嵟戝20ms懸偭偰傒傑偡 */
//					break;
//				}
//			}
//			else {
//				is_ok = 0;
//				counter++;
//				if (counter > 3) {	/* ECM偺帪偼壗傕偟側偔偰傕20,000夞OK偩偭偨偺偱丄僞僀儅乕傪30ms偵偟傑偡 */
//					break;
//				}
//			}
//			wai_tsk(1);
//		}
#endif
	}

#if (0) /* (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) */ /* by H.Kubo 1998/11/05 */ /* Deleted by H.Kubo 1998/11/11 */
** 	/* R4.2 懳嶔(帋尡拞)丅  PIX 庴怣屻丄僐儞僩儘乕儖僠儍儞僱儖妋棫偡傞傑偱 FE 價僢僩偑棫偪偭傁側偟偺偲偒偑偁傞 */
** 	if (SYS_V34ProcedureExecuting()) {
** 		if (MDM_GetIO(POS_FE) || MDM_GetIO(POS_PE)) {
** 			UBYTE i;
** 			for (i = 0; (i < 16) && (MDM_GetIO(POS_FE) || MDM_GetIO(POS_PE)); i++) {
** 				(void) MDM_GetIO(POS_RBUFFER);
** 			}
** 			MDM_SetIO(POS_FE, OFF);
** 			MDM_SetIO(POS_PE, OFF);
** 		}
** 		MDM_SetIO(POS_OE, OFF);
** 	}
#endif

	MDM_InitialConfig();
	ModemBlock.Chain = CHAIN_ON;
	ModemBlock.RxCheck = CHECK_OFF;

#if (PRO_PRINT_TYPE == THERMAL_TRANS /*THERMAL*/) || (PRO_PRINT_TYPE == THERMAL)	/*  僾儕儞僩僨僐乕僪掆巭梫媮僼儔僌棊偲偡 By H.Kubo  1998/10/26 */
	/* ported for HINOKI2 2002/01/07 T.Takagi */
	SYS_PRN_StopRequestFromModem = FALSE;
#endif
	
#if defined (KEISATSU) /* 寈嶡FAX 05/06/20 愇嫶惓榓 */
	if (FCM_S1_Scramble == TRUE) { /* 僗僋儔儞僽儖捠怣偺応崌 */
		S1_CloseECM_Rx(); /* S1僋儘乕僘 */
		
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
		MDM_SetIO(POS_TPDM, ON);
		MDM_SetIO(POS_HDLC, ON);
	}
	else {
		SetDTC_IntFromModem(); /* DTC妱傝崬傒傪儌僨儉偐傜偵偡傞 */
	}
#endif
}


/*************************************************************************
	module		:[ECM憲弌帪娫愝掕]
	function	:[
		1.堷偒悢偺僨乕僞検傪憲弌偡傞偺偵偐偐傞乮俥俽俲憲怣俁侽侽倐倫倱乯帪娫傪愝掕偡傞
		2.侾偺埵偼愗傝忋偘張棟傪峴偆乮侾侽倣倱僞僀儅梡乯
	]
	return		:[
		憲弌帪娫(ms)
	]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UWORD	near	SetEcmTime(UWORD ){}]
	date		:[1994/02/17]
	update		:[1995/12/12]
	author		:[慮崻壀戱丄栘尦廋]
*************************************************************************/
UWORD		SetEcmTime(UWORD	datacnt)
{
	UWORD	remainecmtime;
	UWORD	ecmtime;

	switch (ModemBlock.Speed) {
	case SPEED_33600:
		remainecmtime = datacnt*10%42;
		ecmtime = datacnt*10/42;
		break;
	case SPEED_31200:
		remainecmtime = datacnt*10%39;
		ecmtime = datacnt*10/39;
		break;
	case SPEED_28800:
		remainecmtime = datacnt*10%36;
		ecmtime = datacnt*10/36;
		break;
	case SPEED_26400:
		remainecmtime = datacnt*10%33;
		ecmtime = datacnt*10/33;
		break;
	case SPEED_24000:
		remainecmtime = datacnt*10%30;
		ecmtime = datacnt*10/30;
		break;
	case SPEED_21600:
		remainecmtime = datacnt*10%27;
		ecmtime = datacnt*10/27;
		break;
	case SPEED_19200:
		remainecmtime = datacnt*10%24;
		ecmtime = datacnt*10/24;
		break;
	case SPEED_16800:
		remainecmtime = datacnt*10%21;
		ecmtime = datacnt*10/21;
		break;
	case SPEED_14400:
		remainecmtime = datacnt*10%18;
		ecmtime = datacnt*10/18;
		break;
	case SPEED_12000:
		remainecmtime = datacnt*10%15;
		ecmtime = datacnt*10/15;
		break;
	case SPEED_9600:
		remainecmtime = datacnt*10%12;
		ecmtime = datacnt*10/12;
		break;
	case SPEED_7200:
		remainecmtime = datacnt*10%9;
		ecmtime = datacnt*10/9;
		break;
	case SPEED_4800:
		remainecmtime = datacnt*10%6;
		ecmtime = datacnt*10/6;
		break;
	case SPEED_2400:
	default:
		remainecmtime = datacnt*10%3;
		ecmtime = datacnt*10/3;
		break;
	}
	/*--------------------------------------*/
	/**	憲弌帪娫愝掕乛彫悢揰埲壓愗傝忋偘	*/
	/*--------------------------------------*/
	if (remainecmtime > 0) {
		ecmtime = ecmtime+1;
	}
	/*--------------------------------------*/
	/* 侾侽倣倱僞僀儅梡丄侾埵愗傝忋偘張棟	*/
	/*--------------------------------------*/
	remainecmtime = ecmtime%10;
	ecmtime = ecmtime/10;
	if (remainecmtime > 0) {
		ecmtime = (ecmtime*10)+10;
	}
	else {
		ecmtime = ecmtime*10;
	}
	return(ecmtime);
}

