/************************************************************************
*	System		: POPLAR
*	File Name	: SCDFUNC.C
*	Author		: Y.Suzuki
*	Date		: 1997/3/7
*	Description	:ソフトコーデック、縮小の 初期化、およびＲＴＣ書き込み
*				ようは、内蔵に入れたくないモジュールをあつめた。
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysdblk.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\ext_v\bkupram.h"
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
 #endif
#endif

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#else
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#endif

#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[ソフトエンコードで使用するローカル変数の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/12/04]
	author		:[鈴木郁二]
*************************************************************************/
void SoftEncodeInitial(struct CdcBlk_t *scdcp)
{
	UBYTE buf_no;

	scdcp->Coding = SYS_DocBlock.Dst.Code;
	switch(SYS_DocBlock.Dst.Size) {
	case SYS_DOCUMENT_A4_SIZE:
		scdcp->Img_Size = SYS_A4_LINE;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		scdcp->Img_Size = SYS_B4_LINE;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		scdcp->Img_Size = SYS_A3_LINE;
		break;
	}
	switch(SYS_DocBlock.Dst.Mode) {
	case SYS_NORMAL:
		scdcp->K_Para = 2;
		break;
	case SYS_FINE:		/**	ファイン	*/
	case SYS_GRAY16:	/**	中間調16	*/
	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
	case SYS_GRAY32:	/**	中間調32	*/
	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
	case SYS_GRAY64:	/**	中間調64	*/
	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
		scdcp->K_Para = 4;
		break;
	case SYS_EFINE:		/**	Eファイン	*/
		scdcp->K_Para = 4;
		scdcp->Img_Size /= 2;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		scdcp->Img_Size *= 3;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		break;
	case SYS_SFINE:		/**	Sファイン	*/
		scdcp->K_Para = 8;
		break;
	case SYS_E_HFINE:		/**	EHファイン	*/
		scdcp->K_Para = 8;
		scdcp->Img_Size /= 2;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		scdcp->Img_Size *= 3;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		break;
	case SYS_HFINE:		/**	Hファイン	*/
		scdcp->K_Para = 8;
		scdcp->Img_Size *= 2;/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/01/10 */
		break;
	}
	scdcp->Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */

	/* 符号ライトポインタのセット */
	if(scdcp->BufMode == MDM) {
		scdcp->Wp = &MdmWp;
		scdcp->Wp->Buf = &MDM_ModemBuffer[0][0];
		scdcp->Wp->Adr = 0;
		scdcp->Wp->Bit = 1;
		LineByteCnt = 0;
		for(buf_no = 0; buf_no < 8; buf_no++) {
			SCD_MdmBufCount[buf_no] = 0;
		}
	}
	else if(scdcp->BufMode == ECM_BUF) {
		scdcp->Wp = &EcmWp;
		SCD_EcmBufTopAddress = &EcmBuffer[0][0];
		scdcp->Wp->Buf = SCD_EcmBufTopAddress;
		scdcp->Wp->Adr = 0;
		scdcp->Wp->Bit = 1;
		LineByteCnt = 0;
	}
	else if(scdcp->BufMode == MEM1) {
		/* 蓄積符号化方式をＭＭＲ/ＭＲ */
		scdcp->Coding = RxMemoryStoreData.Code;
		scdcp->Wp = &MemWp;
		/* メモリ書き込み先頭アドレスをセットすべき */
		scdcp->Wp->Buf = (UBYTE*)(MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo));/** 送信原稿のＤＲＡＭ内先頭アドレス */
		scdcp->Wp->Adr = 0;
		scdcp->Wp->Bit = 1;
	}
}


/*************************************************************************
	module		:[ソフトデコードで使用するローカル変数の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/12/04]
	author		:[鈴木郁二]
*************************************************************************/
void SoftDecodeInitial(struct CdcBlk_t *scdcp)
{
	/**	メモリ送信の場合、蓄積符号化方式 受信の場合、受信符号化方式をセット */
	scdcp->Coding = SYS_DocBlock.Src.Code;
	if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_A4_SIZE) {
		scdcp->Img_Size = SYS_A4_LINE;
	}
	else if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_B4_SIZE) {
		scdcp->Img_Size = SYS_B4_LINE;
	}
	else if(SYS_DocBlock.Src.Size == SYS_DOCUMENT_A3_SIZE) {
		scdcp->Img_Size = SYS_A3_LINE;
	}
	if (SYS_DocBlock.Src.Mode == SYS_HFINE) {/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/02/07 */
		scdcp->Img_Size *= 2;
	}
	else if ((SYS_DocBlock.Src.Mode == SYS_EFINE)||(SYS_DocBlock.Src.Mode == SYS_E_HFINE)) {
		scdcp->Img_Size /= 2;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		scdcp->Img_Size *= 3;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
	}
	scdcp->Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */
	/* 初期化 追加 王 96/1/23 */
	scdcp->DecData.Byte.H = 0;
	scdcp->DecData.Byte.L = 0;
	scdcp->DecBits = 0;

	/* 符号リードポインタのセット */
	if(scdcp->BufMode == MDM) {
		/* Ｇ３受信時 MDM_ModemBuffer[0] をスキップする */
		DEBUG_SCD_MDM_BufferSkip = 0;	/*	By Y.Suzuki 1997/01/09	*/

		scdcp->Rp = &MdmRp;
		scdcp->Rp->Buf = &MDM_ModemBuffer[ModemControl.ReadPoint][0];
		scdcp->Rp->Adr = 0;
		scdcp->Rp->Bit = 1;
	}
	else if(scdcp->BufMode == ECM_BUF) {
		scdcp->Rp = &EcmRp;
		SCD_EcmBufTopAddress = &EcmBuffer[0][0];
		scdcp->Rp->Buf = SCD_EcmBufTopAddress;
		scdcp->Rp->Adr = 0;
		scdcp->Rp->Bit = 1;
	}
	else if(scdcp->BufMode == MEM1) {
		scdcp->Rp = &MemRp;
		/* メモリ読み出し先頭アドレスをセットすべき */
		scdcp->Rp->Buf = (UBYTE*)(MEM_CalculateSoftAddress(MemoryExecData.ExecBlockNo));/** 送信原稿のＤＲＡＭ内先頭アドレス */
		scdcp->Rp->Adr = 0;
		scdcp->Rp->Bit = 1;
	}
}


#if (0)	/*	By Y.Suzuki 1997/06/24	*/
** /*************************************************************************
** 	module		:[ＲＬバッファ初期化]
** 	function	:[
** 		1.エンコード、デコードで使用する参照ラインにＲＬＢＵＦのアドレスをセット
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[SH7034/SH704X]
** 	language	:[SHC]
** 	keyword		:[MDM]
** 	date		:[1995/11/17]
** 	author		:[鈴木郁二]
** *************************************************************************/
//void RlBufInit(UWORD img_size) {
//	struct WorkBuf_t *rl_buf_p;
//	SCD_NgRl = 0;		/*	By Y.Suzuki 1997/03/17	*/
//	RL1.Cout = 0;
//	RL1.Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
//	RL1.Data = &RL_Buffer[RLBUF_ENC];
//	rl_buf_p = &RL1;
//	/* 全白イメージサイズをセットする */
//	PutRL(rl_buf_p,img_size,0);
//	RL2.Cout = 0;
//	RL2.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
//	RL2.Data = &RL_Buffer[RLBUF_ENC + RLBUF_SIZE];
//	rl_buf_p = &RL2;
//	/* 全白イメージサイズをセットする */
//	PutRL(rl_buf_p,img_size,0);
//	RL3.Cout = 0;
//	RL3.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
//	RL3.Data = &RL_Buffer[RLBUF_DEC];
//	rl_buf_p = &RL3;
//	/* 全白イメージサイズをセットする */
//	PutRL(rl_buf_p,img_size,0);
//}
#endif	/*	By Y.Suzuki 1997/06/24	*/


#if(0)		/*	By Y.Suzuki 1997/06/24	*/
** /*************************************************************************
** 	module		:[モデムバッファにＲＴＣ書き込み]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[SH7034/SH704X]
** 	language	:[SHC]
** 	keyword		:[SCDC]
** 	date		:[1995/12/19]
** 	author		:[鈴木郁二]
** *************************************************************************/
//void WriteRtcToMdm(struct CdcBlk_t *cp)
//{
//	UBYTE bit_num,eol_cnt;
//	UWORD data;
//	eol_cnt = 6;/* eol の数 */
//	bit_num = 12;
//	data =0x800;/* For MH */
//	if(cp->Coding == SYS_MR_CODE) {
//		bit_num = 13;
//		data = 0x1800;
//	}
//	else if(cp->Coding == SYS_MMR_CODE) {
//		/* For EOFB */
//		eol_cnt = 6;
//	}
//	do {
//		MdmWrite(cp->Wp,bit_num,data);
//		eol_cnt--;
//	}while(eol_cnt);
//}

/*************************************************************************
	module		:[ＥＣＭバッファにＲＴＣ書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/19]
	author		:[鈴木郁二]
*************************************************************************/
//void WriteRtcToEcm(struct CdcBlk_t *cp)
//{
//	UBYTE bit_num,eol_cnt;
//	UWORD data;
//	eol_cnt = 6;/* eol の数 */
//	bit_num = 12;
//	data =0x800;/* For MH */
//	if(cp->Coding == SYS_MR_CODE) {
//		bit_num = 13;
//		data = 0x1800;
//	}
//	else if(cp->Coding == SYS_MMR_CODE) {
//		/* For EOFB */
//		eol_cnt = 6;
//	}
//	do {
//		EcmWrite(cp->Wp,bit_num,data);
//		eol_cnt--;
//	}while(eol_cnt);
//}

/*************************************************************************
	module		:[メモリにＲＴＣ書き込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1995/12/19]
	author		:[鈴木郁二]
*************************************************************************/
//UBYTE WriteRtcToMem(struct CdcBlk_t *cp)
//{
//	UBYTE bit_num,eol_cnt;
//	UWORD data;
//	eol_cnt = 6;/* eol の数 */
//	bit_num = 12;
//	data =0x800;/* For MH */
//	if(cp->Coding == SYS_MR_CODE) {
//		bit_num = 13;
//		data = 0x1800;
//	}
//	else if(cp->Coding == SYS_MMR_CODE) {
//		/* For EOFB */
//		eol_cnt = 6;
//	}
//	do {
//		if(MemWrite(cp->Wp,bit_num,data) == RX_MEM_OVER) {
//			return(RX_MEM_OVER);
//		}
//		eol_cnt--;
//	}while(eol_cnt);
//}

#endif		/*	By Y.Suzuki 1997/06/24	*/


/*************************************************************************
	module		:[線密度モードパラメータ変換]
	function	:[
		1.
	]
	return		:[	ＮＯＲＭＡＬ	：１
					ＦＩＮＥ		：２
					ＳＦＩＮＥ		：４
					ＨＦＩＮＥ		：４ POPLAR:R16 * 15.4l/mm
	]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE ModePara(UBYTE mode)
{
	UBYTE para;

	switch(mode){
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		para = 2;
		break;
	case SYS_EFINE:/*	By Y.Suzuki 1997/11/06	*/
		para = 3;
		break;
	case SYS_SFINE:
		para = 4;
		break;
	case SYS_HFINE:
		para = 5;
		break;
	case SYS_E_HFINE:/* 副走査に関しては、SFINEと同じ  By Y.Suzuki 1997/11/06 */
		para = 6;
		break;
	default:	/* NORMAL */
	     para = 1;
	     break;
	}
	return(para);
}


/*************************************************************************
	module		:[モード変更による縮小時、副走査スキップモード獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
/* get mode skip parameter */
UBYTE GetModeSkip(UBYTE src_mode,UBYTE dst_mode)
{
	UBYTE    src,dst;

	ReductionFromHfine = 0;
	ReductionFromR12 = 0;/*	By Y.Suzuki 1997/11/06	*/
	src = ModePara(src_mode);
	dst = ModePara(dst_mode);
	if(src == 4 && dst == 2) {     /* SFINE to FINE */
	   dst++;
	}
	else if(src == 5 && dst != 5) {
		ReductionFromHfine = 1;
		src = 4;/* 副走査の縮小は、スーパーファインと同じ */
		if(dst == 2) {
			dst++;
		}
	}
	else if((src == 3 && dst <= 2)||(src == 6 && dst <= 4))  {
		ReductionFromR12 = 1;/*	By Y.Suzuki 1997/11/06	*/
		if ((src == 6)||(src == 3 && dst == 2)) {
			if (src==3) {/* EFINEからFINEの縮小は、特殊処理になる */
				ReductionFromR12 = 2;
			}
			/* E_HFINE の副走査はSFINEとおなじ。*/
			if (dst != 3) {/* E_HFINE --> EFINEは考慮しない.この関数からの戻り値は、3がかえるようにする */
				src = 4;
				if(dst == 2) {
					dst++;
				}
			}
		}
		else {
			ReductionFromR12 = 0;
		}
	}
	return((UBYTE)(src - dst));
}



/*************************************************************************
	module		:[縮小パターンセット]
	function	:[
		1.
	]
	return		:[	Ｂ４－＞Ａ４：１
					Ａ３－＞Ｂ４：２
					Ａ３－＞Ａ４：３
					縮小なし	：０
					原稿幅の縮小なし、モード変更による主走査の縮小あり：４ By Y.Suzuki 1997/01/17
	]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SetReduce(struct MEM_DocParamData_t *src,struct MEM_DocParamData_t *dst)
{
	UBYTE  flag;
	/* Ｈ＿ＦＩＮＥの処理 */

	switch(src->Size){
	case SYS_DOCUMENT_A4_SIZE:
		flag = 0;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
			flag = 3;
		else
			flag = 0;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
			flag = 1;
		else if(dst->Size == SYS_DOCUMENT_B4_SIZE)
			flag = 2;
		else
			flag = 0;
		break;
	default:
		flag = 0;
		break;
	}
	if (!flag && ReductionFromHfine) {/*	原稿幅の縮小なし、モード変更による主走査の縮小あり	*/
		flag = 6;
	}
	else if (!flag && ReductionFromR12) {/*	原稿幅の縮小なし、モード変更による主走査の縮小あり	*/
		flag = 10;
	}
	return(flag);
}


/*************************************************************************
	module		:[送信原稿サイズ縮小にて生ずる副走査の間引き処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/25]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE Skip(struct reduction_t *rp)
{
	UWORD h, i, j;

	i = rp->linecnt - (rp->cntr_loop * (rp->linecnt / rp->cntr_loop));
	/* Ex.    85 - (38 * (85 / 38)) */
	j = i % 8;		/* 何ﾋﾞｯﾄ目か */
	i = i / 8;		/* 何ﾊﾞｲﾄ目か */
	h = (0x80 >> j);
	rp->linecnt++;
	if ((*(rp->r_tbl_p + i)) & h) {
		return(1);	/* 縮小せよ */
	}
	return(0);	/* 縮小しない */
}


/*************************************************************************
	module		:[メンテナンスＳＷ－ＦをＳＣＤ用ＳＷにコピーする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/10/16]
	author		:[鈴木郁ニ]
*************************************************************************/
void CopyFromMantSwF(void)
{
	SCD_MaintenanceSwitch[SCD_MNT_SW_F0] =  SYB_MaintenanceSwitch[MNT_SW_F0];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F1] =  SYB_MaintenanceSwitch[MNT_SW_F1];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F2] =  SYB_MaintenanceSwitch[MNT_SW_F2];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F3] =  SYB_MaintenanceSwitch[MNT_SW_F3];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F4] =  SYB_MaintenanceSwitch[MNT_SW_F4];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F5] =  SYB_MaintenanceSwitch[MNT_SW_F5];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F6] =  SYB_MaintenanceSwitch[MNT_SW_F6];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F7] =  SYB_MaintenanceSwitch[MNT_SW_F7];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F8] =  SYB_MaintenanceSwitch[MNT_SW_F8];
	SCD_MaintenanceSwitch[SCD_MNT_SW_F9] =  SYB_MaintenanceSwitch[MNT_SW_F9];
}


/*************************************************************************
	module		:[ＳＣＤ用ＳＷをメンテナンスＳＷ－Ｆにコピーする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/10/16]
	author		:[鈴木郁ニ]
*************************************************************************/
void CopyToMantSwF(void)
{
	SYB_MaintenanceSwitch[MNT_SW_F0] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F0];
	SYB_MaintenanceSwitch[MNT_SW_F1] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F1];
	SYB_MaintenanceSwitch[MNT_SW_F2] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F2];
	SYB_MaintenanceSwitch[MNT_SW_F3] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F3];
	SYB_MaintenanceSwitch[MNT_SW_F4] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F4];
	SYB_MaintenanceSwitch[MNT_SW_F5] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F5];
	SYB_MaintenanceSwitch[MNT_SW_F6] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F6];
	SYB_MaintenanceSwitch[MNT_SW_F7] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F7];
	SYB_MaintenanceSwitch[MNT_SW_F8] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F8];
	SYB_MaintenanceSwitch[MNT_SW_F9] =  SCD_MaintenanceSwitch[SCD_MNT_SW_F9];
}

/*************************************************************************
	module		:[メモリ送信時主走査のソフト縮小]
	function	:[
		メモリ内にｍｍで蓄積される。
		1.	Ａ３ー＞Ｂ４
			Ａ３－＞Ａ４
			Ｂ４－＞Ａ４
			ＨＦＩＮＥ－＞ＮＯＲＭ，ＳＦＩＮＥ，ＦＩＮＥ（％ Ｒ１６－＞Ｒ８）
		2.ｒｌバッファからｒｌを取り出し、縮小率により縮小しｒｌバッファに戻す。
		3.取り出してきたｒｌの総和を縮小後、前の縮小後の値との差から縮小後のｒｌを算出。
		4.300dpi からの縮小の処理を入れる
	]
	return		:[]
	common		:[]
	condition	:[外ＲＯＭ]
	comment		:[
					STIGR-007 の規定により縮小率変更 By Y.Suzuki 1996/12/12
					原稿幅の縮小とＨＦＩＮＥからのモード変更が同時に発生した場合、同時に処理する
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[鈴木郁二]
*************************************************************************/
/* static UBYTE SCD_DBG_OldRlSize = 0;*/
void RedLineR12ToR8(struct CdcBlk_t *Sddp,struct WorkBuf_t *rl_buf,UBYTE reduc/* 縮小パターン */)
{
	DWORD	mul_value;
	UWORD	new_rl_size;			/* 縮小前、後のrl_size記憶 */
	UWORD	new_rl_cnt;				/* 縮小後のrl_sizeのカウンタ */
	DWORD	old_rl_cnt;				/* 縮小前のrl_sizeのカウンタ A3->のときwordではﾌﾛｰする */
	UWORD	mul_data,div_data;
	UWORD	rl_data;				/* 縮小後のrl */
/*	UWORD	read_pointer;			 rlバッファから読み出し用 */
	UWORD	write_pointer;			/* rlバッファから書き込み用 */
	UWORD	update_rl;
	UWORD	pre_data;				/* 前にセットした縮小後のＲＬのサイズ */
	UWORD	old_data;				/* 前にリードした縮小前のＲＬのサイズ */

	UBYTE	col,pre_col;	/* ｾｯﾄするrlのｶﾗｰ,一つ前のｶﾗｰ */
	UBYTE	byte_data;

	/* GetRL */
	UWORD	firstbyte;
	UWORD	secondbyte;
	UWORD	rl;
	/* PutRL */
	UWORD	word_data;

	mul_value = 0;
	mul_data = 0;
	div_data = 0;
	new_rl_size = 0;
	old_rl_cnt = 0;
	new_rl_cnt = 0;
/*	read_pointer = 0;*/
	write_pointer = 0;
	update_rl = 0;
	col = 0;
	pre_col = 0;
	byte_data = 0;
	pre_data = 0;
	old_data = 0;

	SCD_DBG_OldRlSize = 0;/*	By Y.Suzuki 1997/02/08	*/

	/** １ラインのイメージサイズを縮小する */
	mul_value =  Sddp->Img_Size;
	switch(reduc) {
	case A3_TO_A4:
	/*	mul_data = 27;
	**	div_data = 38;*/
		mul_data = 22;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case A3_TO_B4:
		mul_data = 32;
		div_data = 38;
	/*	mul_data = 27;
	**	div_data = 32;*/
		break;
	case B4_TO_A4:
	/*	mul_data = 27;
	**	div_data = 32;*/
		mul_data = 26;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case P_A3_TO_A4:
		mul_data = 26;
		div_data = 38;
		break;
	case P_B4_TO_A4:
		mul_data = 26;
		div_data = 32;
		break;
	case HFINE_TO_OTHER:
		mul_data = 20;
		div_data = 40;
		ReductionFromHfine = 0;/* 単なる主走査のみの縮小時 */
		break;
	/* ハイパーファインの原稿でモード変更、縮小が同時の場合 縮小率、未定 */
	case HFA3_TO_A4_OTHER:
		mul_data = 11;
		div_data = 32;
		break;
	case HFA3_TO_B4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	case HFB4_TO_A4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	case R12_TO_R8:/*	By Y.Suzuki 1997/11/13	*/
		mul_data = 2;
		div_data = 3;
		ReductionFromR12 = 0;/* 単なる主走査のみの縮小時 */
		break;
	default:
		new_rl_size = 0;
	}
	if(ReductionFromHfine) {/*	ハイパーファインからのモード変更あり */
		div_data *= 2;
	}
	else if (ReductionFromR12) {/*	By Y.Suzuki 1997/11/06	*/
		mul_data *= 2;
		div_data *= 3;
	}
	new_rl_size = (UWORD)((mul_value * mul_data)/div_data);	/* mul_value == Src.Img_Size */
	rl_buf->Cout = 0;										/* RL Buffer Read Byte Pointer 初期化 */
	/*-------------------------------------------------*/
	/**ライン先頭のＲＬを縮小後､ＲＬバッファに格納する */
	/*-------------------------------------------------*/
	/* old_data = GetRLR(rl_buf,read_pointer);*/
	firstbyte = *(rl_buf->Data + rl_buf->Cout);
	col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
	if ((firstbyte & 0x0080) != 0x0080) {
		rl_buf->Cout ++;
		rl = firstbyte & 0x003F;
	}
	else {
		rl_buf->Cout ++;
		secondbyte = *(rl_buf->Data + rl_buf->Cout);
		rl = ((firstbyte & 0x003F) << 8) + secondbyte;
		rl_buf->Cout ++;
	}

	old_data = rl;

	old_rl_cnt += (DWORD)old_data;
	update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
	rl_data = update_rl - new_rl_cnt;
	new_rl_cnt = update_rl;
	pre_data = rl_data;
/*	PutRLR(rl_buf,write_pointer,rl_data,0);* 縮小後のrlをRLバッファに再セット */
	col = 0;
	byte_data = 0;
	word_data = 0;

	if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
		SCD_NgRl = 1;
	}
	if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
		SCD_NgRl = 2;
	}
	if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
		return;
	}
	if (rl_data <= 0x003F) {
		if (col == WHITE) {
			byte_data = (UBYTE)rl_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
		else {
			word_data = rl_data | 0x0040;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
	}
	else {
		if (col == WHITE) {
			rl_data |= 0x8000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
		else {
			rl_data |= 0xC000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
	}


	rl_data = 0;
	while(new_rl_size > new_rl_cnt) {						/** ＤＳＴのサイズになるまでＲＬを縮小する */
		/*-------------------------------------------------------*/
		/**一ライン分のＲＬを縮小しながら､ＲＬバッファに格納する */
		/*-------------------------------------------------------*/
		/* RLバッファからRL取り出し	*/
	/*	old_data = GetRLR(rl_buf,read_pointer);*/
		firstbyte = *(rl_buf->Data + rl_buf->Cout);
		col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
		if ((firstbyte & 0x0080) != 0x0080) {
			rl_buf->Cout ++;
			rl = firstbyte & 0x003F;
		}
		else {
			rl_buf->Cout ++;
			secondbyte = *(rl_buf->Data + rl_buf->Cout);
			rl = ((firstbyte & 0x003F) << 8) + secondbyte;
			rl_buf->Cout ++;
		}

		old_data = rl;
		old_rl_cnt += (DWORD)old_data;
		if ((UWORD)old_rl_cnt > Sddp->Img_Size) {
			SCD_DBG_OldRlSize = 1;/*	By Y.Suzuki 1997/02/08	*/
		}
		update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
		if(update_rl != new_rl_cnt) {/* 縮小後のrl発生 */
			rl_data = update_rl - new_rl_cnt;
			/* 縮小前のrlｶﾗｰ情報の取得 */
			if(old_data < 64) {/* rlが６３以下 */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 1));
			}
			else {/* if(old_data <= MH_MAKEUP_MAX) @* rlが２５６０以下 */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 2));
			}
			new_rl_cnt = update_rl;/* 縮小後ＲＬ更新 */
			col = (UBYTE)(byte_data & 0x40);
			/* 前にセットしたｒｌと同じ色か */
			if(pre_data < 64) {
				byte_data = *(rl_buf->Data + (write_pointer - 1));
			}
			else { /*if(pre_data <= MH_MAKEUP_MAX) */
				byte_data = *(rl_buf->Data + (write_pointer - 2));
			}
			pre_col = (UBYTE)(byte_data & 0x0040);
			if(col == pre_col) {/* 前にセットしたｒｌと同じ色 */
				rl_data += pre_data;
				if(pre_data < 64) {
					write_pointer--;
				}
				else {
					write_pointer -= 2;
				}
			}
			pre_data = rl_data;
		/*	PutRLR(rl_buf,write_pointer,rl_data,col);@* 縮小後のrlをRLバッファに再セット */
			byte_data = 0;
			word_data = 0;

			if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
				SCD_NgRl = 1;
			}
			if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
				SCD_NgRl = 2;
			}
			if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
				return;
			}
			if (rl_data <= 0x003F) {
				if (col == WHITE) {
					byte_data = (UBYTE)rl_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
				else {
					word_data = rl_data | 0x0040;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
			}
			else {
				if (col == WHITE) {
					rl_data |= 0x8000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
				else {
					rl_data |= 0xC000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
			}


			rl_data = 0;
			col = 0;
			pre_col = 0;
		}
	}
	if (new_rl_cnt > new_rl_size) {
		SCD_DBG_RLOVER = 4;
	}
	/*	主走査に満たないＲＬをセットする By Y.Suzuki 1997/09/26	*/
	if ((reduc == A3_TO_A4) || (reduc == B4_TO_A4)) {
		col = 0;
		if(SCD_TxMode == SYS_HFINE) {/** ハイパーファインなら主走査ドット数２倍 */
			rl_data = SYS_A4_LINE * 2 - new_rl_size;
		}
		else if((SCD_TxMode == SYS_E_HFINE) || (SCD_TxMode == SYS_EFINE)) {/** R12なら主走査ドット数1.5倍 */
			rl_data = (SYS_A4_LINE * 2 - SYS_A4_LINE/2) - new_rl_size;
		}
		else {
			rl_data = SYS_A4_LINE - new_rl_size;
		}
		if(pre_data < 64) {
			byte_data = *(rl_buf->Data + (write_pointer - 1));
		}
		else { /*if(pre_data <= MH_MAKEUP_MAX) */
			byte_data = *(rl_buf->Data + (write_pointer - 2));
		}
		pre_col = (UBYTE)(byte_data & 0x0040);
		if(col == pre_col) {/* 前にセットしたｒｌと同じ色 */
			rl_data += pre_data;
			if(pre_data < 64) {
				write_pointer--;
			}
			else {
				write_pointer -= 2;
			}
		}
		byte_data = 0;
		word_data = 0;

		if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
			SCD_NgRl = 1;
		}
		if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
			SCD_NgRl = 2;
		}
		if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
			return;
		}
		if (rl_data <= 0x003F) {
			if (col == WHITE) {
				byte_data = (UBYTE)rl_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
			else {
				word_data = rl_data | 0x0040;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
		}
		else {
			if (col == WHITE) {
				rl_data |= 0x8000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
			else {
				rl_data |= 0xC000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
		}
	}
}

#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* \src\atlanta\scd\src\scdfunc.cに合わせる 1998/10/09 H.Yoshikawa */
/*************************************************************************
	module		:[送信原稿サイズ縮小にて生ずる副走査の間引き処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/25]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE Skip(struct reduction_t *rp)
{
	UWORD h, i, j;

	i = rp->linecnt - (rp->cntr_loop * (rp->linecnt / rp->cntr_loop));
	/* Ex.    85 - (38 * (85 / 38)) */
	j = i % 8;		/* 何ﾋﾞｯﾄ目か */
	i = i / 8;		/* 何ﾊﾞｲﾄ目か */
	h = (0x80 >> j);
	rp->linecnt++;
	if ((*(rp->r_tbl_p + i)) & h) {
		return(1);	/* 縮小せよ */
	}
	return(0);	/* 縮小しない */
}
#endif

