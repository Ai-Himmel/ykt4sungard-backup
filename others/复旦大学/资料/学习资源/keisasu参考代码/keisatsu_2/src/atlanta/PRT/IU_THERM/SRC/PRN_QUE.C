/****************************************************************
*	System		: SAKAKI
*	File Name	: PRN_QUE.C
*	Author		: K.Kawata
*	Date		: 1998/9/19
*	Description	:
*	Maintenance	:
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
****************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysmemrx.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\mnt_sw.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#if (0)
** /* SAKAKI */
** #include "\src\atlanta\prt\thermal\define\prn_pro.h"
** #include "\src\atlanta\prt\thermal\define\prn_def.h"
** #include "\src\atlanta\prt\thermal\define\prn_stat.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
** #include "\src\atlanta\sakaki\define\sakiport.h"
** #include "\src\atlanta\sakaki\ext_v\ga_data.h"
#else
/* HINOKI */
#include "\src\cpu\sh7043_a\irom\define\def_semn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"

#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\define\prtqueue.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scdc_dat.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
 #endif
#endif

#include "\src\atlanta\ext_v\scn_tbl.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\define\cph_def.h"
#else
	#include "\src\atlanta\scd\define\cph_def.h"
#endif
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif
#if (PRO_MODEM == R288F)
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
	#else
		#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
	#endif
#endif

#if defined(SATSUKI2)
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
#else
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#endif

extern CONST UBYTE SCDC_SWITCHING_TEST;	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */

#if (0)
/* SAKAKI */
UBYTE	RenewLineReadPoint(void)
{
#if (0)
** 	/* SAKAKI */
** 	if (ImageLineWritePoint == ImageLineReadPoint) {
** 		return(NG);
** 	}
** 	if (ImageLineReadPoint == (PRINT_IMAGE_BUF_LINE - 1)) {
** 		if (ImageLineWritePoint == ImageLineStartPoint) {
** 			return(NG);
** 		}
** 		ImageLineReadPoint = ImageLineStartPoint;
** 		return(OK);
** 	}
** 	else {
** 		if (ImageLineWritePoint == (ImageLineReadPoint + 1)) {
** 			return(NG);
** 		}
** 		ImageLineReadPoint++;
** 		return(OK);
** 	}
#endif
}

UBYTE	RenewLineWritePoint(void)
{
#if (0)
** 	/* SAKAKI */
** 	if (ImageLineWritePoint == (PRINT_IMAGE_BUF_LINE - 1)) {
** 		CMN_DisableInterrupt();
** 		if (ImageLineReadPoint == ImageLineStartPoint) {
** 			CMN_EnableInterrupt();
** 			return(NG);
** 		}
** 		CMN_EnableInterrupt();
** 		ImageLineWritePoint = ImageLineStartPoint;
** 		return(OK);
** 	}
** 	else {
** 		CMN_DisableInterrupt();
** 		if (ImageLineReadPoint == (ImageLineWritePoint + 1)) {
** 			CMN_EnableInterrupt();
** 			return(NG);
** 		}
** 		CMN_EnableInterrupt();
** 		ImageLineWritePoint++;
** 		return(OK);
** 	}
#endif
}


UBYTE	CheckLineWritePoint(void)
{
#if (0)
** 	/* SAKAKI */
** 	CMN_DisableInterrupt();
** 	if (ImageLineReadPoint == ImageLineWritePoint) {
** 			CMN_EnableInterrupt();
** 			return(OK);
** 	}
** 	if (ImageLineWritePoint == (PRINT_IMAGE_BUF_LINE - 1)) {
** 		if (ImageLineReadPoint == ImageLineStartPoint) {
** 			CMN_EnableInterrupt();
** 			return(NG);
** 		}
** 		CMN_EnableInterrupt();
** 		return(OK);
** 	}
** 	else {
** 		if (ImageLineReadPoint == (ImageLineWritePoint + 1)) {
** 			CMN_EnableInterrupt();
** 			return(NG);
** 		}
** 		CMN_EnableInterrupt();
** 		return(OK);
** 	}
#endif
}
#endif

void	WaitAllImageLinePrint(void)
{
	
/*
** デコード終了のところで、セットするようにします
** 1999/03/03 by T.Soneoka
*/
#if (0)
** 	int	dummyline; /* 1999/03/02 by T.Soneoka */
** 	int	loop; /* 1999/03/02 by T.Soneoka */
#endif
	
#if (0)
** 	/* SAKAKI */
** 	WORD	i;
** 
** 	i = (PRINT_IMAGE_BUF_LINE * 2);
** 	if (ImageLineWritePoint == ImageLineStartPoint ) {
** 		while ((ImageLineReadPoint != (PRINT_IMAGE_BUF_LINE - 1)) && (i > 0)) {
** 			wai_tsk(2);
** 			i--;
** 		}
** 	}
** 	else {
** 		while ((ImageLineReadPoint != (ImageLineWritePoint - 1)) && (i > 0)) {
** 			wai_tsk(2);
** 			i--;
** 		}
** 	}
** 	RenewLineWritePoint();
** 	wai_tsk(10);
#else


/*
** デコード終了のところで、セットするようにします
** 1999/03/03 by T.Soneoka
*/
#if (0)
** 	/* 最終ラインを印字します  1999/03/02 by T.Soneoka */
** 	dummyline = 2;
** 	while (dummyline--) {
** 		(void)CMN_WordMemorySet((UWORD *)&PrinterBuffer[GetPrtImageBufWriteLineNo()][0], (UWORD)128, 0x00);
** 		(void)GetWritePtrPrtImageBuf();
** 		IncPrtImageReadableLine();
** 	}
#endif
	IsPrintFinish = TRUE;
	while (EnableToReadPrtImageBuf()) {
		if ((PRN_PrintHaltRequest() == NG) || (PRN_PrintErrorHaltRequest() == NG)) {
			break;
		}
		wai_tsk(2);
	}
	IsPrintFinish = FALSE;

#endif
}


/*************************************************************************
	module		:[直前のデータをコピーする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PrvBitImageToBitImage(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PrvBitImageToBitImage(void)
{
#if (0)
** 	/* SAKAKI */
** 	WORD	i, j;
** 
** 	if (ImageLineWritePoint == ImageLineStartPoint) {
** 		j = (PRINT_IMAGE_BUF_LINE - 1);
** 	}
** 	else {
** 		j = (ImageLineWritePoint - 1);
** 	}
** 	for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
** 		PRN_ImageBuffer1[ImageLineWritePoint][i] = PRN_ImageBuffer1[j][i];
** 	}
#else
	/* HINOKI */
	WORD	i, j;

	j = (UWORD)GetPrtImageBufWriteLineNo();
	if (j == 0) {
		j = (PRINT_IMAGE_BUF_LINE - 1);
	}
	else {
		j -= 1;
	}
	for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
		PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][i] = PRN_ImageBuffer1[j][i];	/* このまま By O.Kimoto 1998/11/10 */
	}
#endif
}


/*************************************************************************
	module		:[プリント用バッファを全白に初期化する。]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void BitImageAllWhiteData(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	BitImageAllWhiteData(void)
{
#if (0)
** 	/* SAKAKI */
** 	WORD	i;
** 
** 	for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
** 		PRN_ImageBuffer1[ImageLineWritePoint][i] = 0xff;
** 	}
#else
	/* HINOKI */
	WORD	i;

	for (i = 0; i < PRINT_IMAGE_BUF_SIZE; i++) {
		PRN_ImageBuffer1[(UWORD)GetPrtImageBufWriteLineNo()][i] = 0x00;	/* このまま By O.Kimoto 1998/11/10 */
	}
#endif
}

/*******************************************************
    module		:[１ライン分のＲＬをイメージに変換する]
    fonction	:[]
    return		:[]
    common		:[]
    condition	:[COMMON]
    comment		:[]
    machine		:[SH7041]
    language	:[SHC]
    keyword		:[]
    date		:[1998/9/7]
    author		:[K.Kawata]
********************************************************/
void LineRL_ToImage(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{
	UWORD rl_a;			 			/** 走査線　run length */
	UWORD ImgCntr;					/** 走査線カウンタ */
	UWORD ImgBitCntr;				/** 1ライン走査線数カウンタ */
	UWORD BufCntr;					/** ＲＬ確認カウンタ */
	UBYTE ImgBufData;				/** イメージデータ バッファ */
	UBYTE ImgClor;					/** カラーデータ */
	UBYTE ImgbyteClor;				/** イメージバイトカラーデータ   1997/03/28 by T.Mizuguchi */
	UBYTE SfitCntr;					/** ビット カウンタ */

	point->Cout = 0;
	point->Flag = 0;
	SfitCntr = 0;
	ImgBitCntr = 0;
	ImgCntr = 0;
	ImgBufData = 0;

#if (0)
** 	/* SAKAKI */
** 	ImgClor = 0x01;	/*1998.7.16 K.Kawata*/
** 	ImgbyteClor = 0xff;	/*1998.7.16 K.Kawata*/
#else
	/* HINOKI */
	ImgClor = 0x00;
	ImgbyteClor = 0x00;
#endif

	do 	{
	    rl_a = GetRL(point);	/** run length バッファ から ＲＬを取り出す */
		/** 速度　ｕｐの為の変更　 1997/03/28 by T.Mizuguchi */
		if ((ImgBitCntr == 0 ) || (SfitCntr == 0)){
			if (rl_a >= 8){
				do {

#if (0)
** 					/* PRN_ImageBuffer1のOffSetを入れます。 By O.Kimoto 1998/11/10 */
** 					PRN_ImageBuffer1[line][ImgCntr] = ImgbyteClor;	/*1998.8.19 K.Kawata*/
#else
					*(prn_imgbuf1_p + (UDWORD)(line * PRINT_IMAGE_BUF_SIZE) + (UDWORD)ImgCntr) = ImgbyteClor;
#endif

					ImgCntr++;
					rl_a -= 8;
					ImgBitCntr += 8;
				} while (rl_a >= 8);
				ImgBufData = 0;
			}
		}
		if (rl_a != 0) {
			for(BufCntr=0; BufCntr != rl_a; BufCntr++){
												 	/** RL からイメージに変換 */
				ImgBufData += ImgClor;				/** １ビット イメージデータ書き込み */
				ImgBitCntr++;						/** 1ライン走査線数カウンタ */
				SfitCntr++;							/** ビット カウンタ 更新 */
				if (SfitCntr == 8){
#if (0)
** 					/* PRN_ImageBuffer1のOffSetを入れます。 By O.Kimoto 1998/11/10 */
** 					PRN_ImageBuffer1[line][ImgCntr] = ImgBufData;	/*1998.8.19 K.Kawata*/
#else
					*(prn_imgbuf1_p + (UDWORD)(line * PRINT_IMAGE_BUF_SIZE) + (UDWORD)ImgCntr) = ImgBufData;
#endif
					/** ＳＲＡＭにイメージ データ書き込み */
					ImgCntr++;
					SfitCntr=0;	/** ビット  カウンタ = 0 */
					ImgBufData = 0;
				}
				else {
					ImgBufData <<= 1;
				}
			}
		}
		ImgClor = (UBYTE)(ImgClor ^ 0x01);
		ImgbyteClor = (UBYTE)(ImgbyteClor ^ 0xff);
	} while (scdcp->Img_Size > ImgBitCntr);	/* 1ライン終了か ？ */
	return;
}

/*****************************************************************
	module		:[UBYTE CipherDecode(UWORD line)]
	function	:[
		1.ＭＨ、ＭＲ、ＭＭＲからビットマップにデコードする
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1998/6/17]
	author		:[K.Kawata]
*****************************************************************/
UBYTE CodeToBitImage(UWORD line)
{
UWORD	result;
struct	WorkBuf_t *tmp;
WORD	status;

#if (0)
** 	/* SAKAKI */
** 	MemoryExecData = PrintExecReadData;
#else
	/* HINOKI */
#if (0)
** 	/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
** 	wai_sem(semno.SCDC_DRAM_Access);
** 
** 	CMN_DisableInterrupt();
** 	DecMemoryExecBkupData	= MemoryExecData;
** 	MemoryExecData			= PrintExecReadData;
** 	CMN_EnableInterrupt();
#endif
#endif
	for (;;) {

if (SCDC_SWITCHING_TEST == 1) {	/* for DEBUG by O.Kimoto 1999/01/16 */
	wai_sem(semno.SCDC_DRAM_Access);

	CMN_DisableInterrupt();
	DecMemoryExecBkupData	= MemoryExecData;
	MemoryExecData			= PrintExecReadData;
	CMN_EnableInterrupt();
}

		tmp = DecodeA_buffer;
		DecodeA_buffer = DecodeB_buffer;
		DecodeB_buffer = tmp;
		status = Mem_Decode(&PrintDecodeData, DecodeA_buffer, DecodeB_buffer);

if (SCDC_SWITCHING_TEST == 1) {	/* for DEBUG by O.Kimoto 1999/01/16 */
		/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
		CMN_DisableInterrupt();

		PrintExecReadData	= MemoryExecData;
		MemoryExecData	= DecMemoryExecBkupData;

		/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
		sig_sem(semno.SCDC_DRAM_Access);
}
		if (status != OK) {
			if (status == RTC) {
				return(NG);
			}
			if (status == TX_MEM_ERR) {
				if (PrintDecodeData.Coding == SYS_MMR_CODE) {
					SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR;
					return(NG);
				}
				if (CHK_ErrorLineReplace()) {
					BitImageAllWhiteData();
				}
				else {
					PrvBitImageToBitImage();
				}
				return(OK);
			}
		}

#if (0)
** 		/* SAKAKI */
** 		if (PRN_Control.ReductionType == 0) {
** 			break;
** 		}
** 		if (!Skip(&PRN_LineSkipData)) {
** 			RedLine(&PrintDecodeData, DecodeB_buffer, PRN_Control.ReductionType);
** 			break;
** 		}
** 		if (PRN_PrintModeCount != 0) {
** 			RedLine(&PrintDecodeData, DecodeB_buffer, PRN_Control.ReductionType);
** 			PRN_PrintModeCount--;
** 			Skip(&PRN_LineSkipData);
** 			break;
** 		}
#else
		/* HINOKI */
		if (PageQ.Reduction == 0) {
			break;
		}
		if (!Skip(&PRN_LineSkipData)) {
			RedLine(&PrintDecodeData, DecodeB_buffer, PageQ.Reduction);
			break;
		}
		if (PRN_PrintModeCount != 0) {
			RedLine(&PrintDecodeData, DecodeB_buffer, PageQ.Reduction);
			PRN_PrintModeCount--;
			Skip(&PRN_LineSkipData);
			break;
		}
#endif

	}

	/*	１０ｍｓタスク切替えする By Y.Suzuki 1996/08/23	*/
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & SCDC_10MS_WAIT) {
		wai_tsk(1);
	}

	/* ＲＬをビットマップに展開する */

#if (0)
** 	/* 騒音対策（Image To RL 変換を外ＲＯＭでする） By O.Kimoto 1999/03/01 */
** 	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RL_TO_IMAGE_EROM) {
** 		PrintDecodeData.Img_Size = PRN_ReductionImageSize;
** 		LineRL_ToImage(DecodeB_buffer, &PrintDecodeData, line);		/* 外ＲＯＭ */
** 		PrintDecodeData.Img_Size = PRN_OriginalImageSize;
** 	}
#else
	if (((Paper.Mode == SYS_FINE) || (Paper.Mode == SYS_GRAY64))
		&& ((SYB_MaintenanceSwitch[MNT_SW_H0] & IMAGE_TO_RL_EROM) == IMAGE_TO_RL_EROM)
		&& ((SYB_MaintenanceSwitch[MNT_SW_H7] & 0x20) == 0x00)) {
		PrintDecodeData.Img_Size = PRN_ReductionImageSize;
		LineRL_ToImage(DecodeB_buffer, &PrintDecodeData, line);		/* 外ＲＯＭ */
		PrintDecodeData.Img_Size = PRN_OriginalImageSize;
	}
#endif

	else {
		PrintDecodeData.Img_Size = PRN_ReductionImageSize;

#if (0)
** 		/* SAKAKI */
** 		FastLineRlToImg1(DecodeB_buffer, &PrintDecodeData, line);	/* 1998/10/21 H.Yoshikawa */
#else
		/* HINOKI */
		Fast1LineRlToImg(DecodeB_buffer, &PrintDecodeData, line);	/* 1998/10/21 H.Yoshikawa */
#endif

		PrintDecodeData.Img_Size = PRN_OriginalImageSize;
	}

#if (0)
** 	/* SAKAKI */
** 	PrintExecReadData = MemoryExecData;
#else
	/* HINOKI */
#if (0)
** 	/* HINOKIはこの関数を呼ぶ前に以下の処理をするように変更します。 By O.Kimoto 1998/11/05 */
** 	CMN_DisableInterrupt();
** 
** 	PrintExecReadData	= MemoryExecData;
** 	MemoryExecData	= DecMemoryExecBkupData;
** 
** 	/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
** 	sig_sem(semno.SCDC_DRAM_Access);
#endif
#endif

	return(OK);
}
