/************************************************************************
*	System			: POPLAR_H
*	File Name		: OPR_MAIN.C
*	Author			: 木元修
*	Date			: 1997/07/23
*	RealTimeOS		: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description		: オペレーションメイン
*	Original File	: jun\usr1:\src\rice\v53\src\opr_main.c
*	Maintenance		: エンコード関係のみです。（デコード関係はIU_THERMの方に有ります。
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h" 
#include "\src\atlanta\define\mntsw_a.h" 
#include "\src\atlanta\define\mntsw_h.h" 
#include "\src\atlanta\define\sysdoc.h" 
#include "\src\atlanta\define\mon_pro.h" 
#include "\src\atlanta\define\mem_def.h" 

#include "\src\atlanta\ext_v\sys_data.h" 
#include "\src\atlanta\ext_v\scn_data.h" 
#include "\src\atlanta\ext_v\bkupram.h" 

#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif
#if (PRO_MODEM == R288F)
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
		#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
		#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
	#endif
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#include "\src\atlanta\define\mon_pro.h"

/* For SCD */
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"

#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"

#include "\src\cpu\sh7043_a\irom\define\def_evtn.h" /* 1999/03/16 by T.Soneoka */

extern UWORD	ScanPageMemReadLine;	/* 次に読込むラインをポイント */

void OneLineRlToImg(struct WorkBuf_t *point,struct CdcBlk_t *scdcp,UWORD line);
void OneLineImgToRl(struct WorkBuf_t *point,struct CdcBlk_t *scdcp,UWORD line);

CONST UBYTE SCDC_SWITCHING_TEST = 0;	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */

/*************************************************************************
	module		:[ソフトコーデック用変数初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[SCDC]
	ProtoType	:[void SCDC_ScdDataInitialize(void){}]
	date		:[1998/10/05]
	author		:[木元  修]
*************************************************************************/
void SCDC_ScdDataInitialize(void)
{
	UBYTE i;

	/******************************/
	/* ソフトコーデック用帯域変数 */
	/******************************/
	SCD_DirectTx = 0;						/* 使用／デコード処理内で参照＜＝”０”固定です。 */
	SCD_SkipMrEol = 0;						/* 使用／デコード処理内で参照＜＝”０”固定です。 */
	SCD_TxMode = 0;							/* 使用／？？？ */
	SCD_DBG_OldRlSize = 0;					/* 使用／縮小時使用 */
	SCD_NgRl = 0;							/* 使用／？？？ */
	SCD_DBG_RLOVER = 0;						/* 使用／？？？ */
	SCD_DBG_PMODE = 0;						/* 使用／？？？*/
	SCD_DBG_ENC_RLSIZE = 0;					/* 使用／？？？*/
	ReductionFromR12 = 0;					/* 使用／線密度変換時使用＝＞”０”固定 */

	ReductionFromHfine = 0;					/* 未使用／線密度変換時の副走査方向ＨＦｉｎｅ対応用 */
	ScdcErrFlag = 0;						/* 未使用／メモリ送信時ソフトコーデックエラー用変数 */
	ScdcPageEndFlag = 0;					/* 未使用／削除可 */
	/* MemReadStatus = 0; Delete by O.Kimoto 1999/01/16 */						/* 未使用／メモリ受信時使用 */
	LineByteCnt = 0;						/* 未使用／メモリ送信時のフィル挿入用 */
	SCD_G3RxResult = 0;						/* 未使用／メモリ受信用 */
	SCD_G3ReadStatus = 0;					/* 未使用／メモリ受信用 */
	SoftcodecMessage.Item = 0;				/* 未使用／ソフトコーデックと通信タスク用 */
	SoftcodecMessage.Message = 0;			/* 未使用／ソフトコーデックと通信タスク用 */
	SoftcodecMessage.SubMessage1 = 0;		/* 未使用／ソフトコーデックと通信タスク用 */
	SoftcodecMessage.SubMessage2 = 0;		/* 未使用／ソフトコーデックと通信タスク用 */
	SoftcodecMessage.SubMessage3 = 0;		/* 未使用／ソフトコーデックと通信タスク用 */
	SoftcodecMessage.SubMessage4 = 0;		/* 未使用／ソフトコーデックと通信タスク用 */
	
	DEBUG_SCD_MDM_BufferSkip = 0;			/* 未使用／通信用 */
	SCD_CarryDownBlock = 0;					/* 未使用／通信でデコード時使用 */
	SCD_EcmSize = 0;						/* 未使用／通信で使用 */
	SCD_MinimumLineSize = 0;				/* 未使用／通信で使用 */
	SCD_LastEolDataCount = 0;				/* 未使用／削除可 */

	for (i = 0 ; i < 8 ; i ++) {
		SCD_MdmBufCount[i] = 0;				/* 未使用／削除可 */
	}
	SCD_EOL_WriteCount = 0;					/* 未使用／削除可 */
	tskno_SCD_CTxCodeConvertTask = 0xffff;	/* 未使用／キャラクター送信時使用 */
	SCD_CarryDownByteCnt = 0;				/* 未使用／通信時使用 */
	SCD_DirectRx = 0;						/* 未使用／通信時使用 */
	SCD_Det_Rcp = 0;						/* 未使用／通信時使用 */

	for (i = 0 ; i < SCD_MNT_SW_MAX ; i ++ ) {
		SCD_MaintenanceSwitch[i] = 0;		/* 未使用／通信時使用 */
	}
	SCD_EcmBufTopAddress = 0;				/* 未使用／通信時使用 */

	/* ScdcEcmBufCnt = 0; */
	/* DirectMemTx = 0; */
	/* UBYTE *SCD_LastEolAddr = 0; */
	/* SCD_Dummy[14] = {0}; */
}

/*************************************************************************
	module		:[ソフトエンコードで使用するローカル変数の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＨＩＮＯＫＩ用にカスタマイズしています。
	]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1998/10/01]
	author		:[木元修]
*************************************************************************/
void SCDC_SoftEncodeInitial()
{
	UBYTE buf_no;
	UWORD data_width;

	SCDC_ScdDataInitialize();	/* ソフトコーデックで使用する変数一括初期化 */

	enc_rp = &Enc_reduc_data;
	EncodeData.Coding = SCN_StoreData.Code;

	switch(SCN_StoreData.Size) {
	case SYS_DOCUMENT_A3_SIZE:
		EncodeData.Img_Size = SYS_A3_LINE;
		data_width = 2432;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		EncodeData.Img_Size = SYS_B4_LINE;
		data_width = 2048;
		break;
	case SYS_DOCUMENT_A4_SIZE:
	default:
		EncodeData.Img_Size = SYS_A4_LINE;
		data_width = 1728;
		break;
	}
	switch(SCN_StoreData.Mode) {
	case SYS_NORMAL:
		EncodeData.K_Para = 2;
		break;
	case SYS_FINE:		/**	ファイン	*/
	case SYS_GRAY16:	/**	中間調16	*/
	case SYS_GRAY16_SEP:/**	中間調16_SEP	*/
	case SYS_GRAY32:	/**	中間調32	*/
	case SYS_GRAY32_SEP:/**	中間調32_SEP	*/
	case SYS_GRAY64:	/**	中間調64	*/
	case SYS_GRAY64_SEP:/**	中間調64_SEP	*/
		EncodeData.K_Para = 4;
		break;
	case SYS_EFINE:		/**	Eファイン	*/
		EncodeData.K_Para = 4;
		EncodeData.Img_Size /= 2;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		EncodeData.Img_Size *= 3;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		break;
	case SYS_SFINE:		/**	Sファイン	*/
		EncodeData.K_Para = 8;
		break;
	case SYS_E_HFINE:		/**	EHファイン	*/
		EncodeData.K_Para = 8;
		EncodeData.Img_Size /= 2;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		EncodeData.Img_Size *= 3;/** ３００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/11/06 */
		break;
	case SYS_HFINE:		/**	Hファイン	*/
		EncodeData.K_Para = 8;
		EncodeData.Img_Size *= 2;/** ４００ＤＰＩ時のラインサイズ設定 By Y.Suzuki 1997/01/10 */
		break;
	default:
		EncodeData.K_Para = 2;
		break;
	}

#if (0)
** 	/** 縮小制御 */
** 	/* ＨＩＮＯＫＩの蓄積では基本的には縮小は行いませんが、万が一のことを考えて
** 	** ベースのソフトコーデックの縮小のパスを残しておきます。
** 	** By O.Kimoto 1998/10/01
** 	*/
** 	SCDC_EncReduction = SetReduce(&(SYS_DocBlock.Src), &(SYS_DocBlock.Dst));
** 	if(SCDC_EncReduction == 1) {
** 		SetSkip(A3_TO_A4,enc_rp);
** 	}
** 	else if(SCDC_EncReduction == 2) {
** 		SetSkip(A3_TO_B4,enc_rp);
** 	}
** 	else if(SCDC_EncReduction == 3) {
** 		SetSkip(B4_TO_A4,enc_rp);
** 	}
** 	else {
** 		SetSkip(100,enc_rp);
** 	}
#else
	SCDC_EncReduction = 0;
	SetSkip(100,enc_rp);
#endif


	EncodeData.Line_Cntr = 0; /* ｺｰﾃﾞｯｸライン数Count初期化 */

	/* 符号ライトポインタのセット */
	EncodeData.Coding = SCN_StoreData.Code;		/* 蓄積符号化方式をＭＭＲ/ＭＲ */
	EncodeData.Wp = &MemWp;

	/* メモリ書き込み先頭アドレスをセットすべき */
	EncodeData.Wp->Buf = (UBYTE*)(MEM_CalculateSoftAddressERom(SCN_ExecData.ExecBlockNo));	/** 蓄積原稿のＤＲＡＭ内先頭アドレス */
	EncodeData.Wp->Adr = 0;
	EncodeData.Wp->Bit = 1;

	SCD_NgRl = 0;		/*	By Y.Suzuki 1997/03/17	*/

	EncRL1.Cout = 0;
	EncRL1.Flag = 0; /* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	EncRL1.Data = RL_Buffer_p + RLBUF_ENC_B4;
	EncodeA_buf = &EncRL1;
	PutRL(EncodeA_buf,(UWORD)data_width,0);	/* 全白イメージサイズをセットする */

	EncRL2.Cout = 0;
	EncRL2.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	EncRL2.Data = RL_Buffer_p + RLBUF_ENC_B4 + RLBUF_SIZE_B4;
	EncodeB_buf = &EncRL2;
	PutRL(EncodeB_buf,(UWORD)data_width,0);	/* 全白イメージサイズをセットする */

	EncRL3.Cout = 0;
	EncRL3.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	EncRL3.Data = RL_Buffer_p + RLBUF_ENC_B4 + RLBUF_SIZE_B4 + RLBUF_SIZE_B4;
	DecodeC_buf = &EncRL3;
	PutRL(DecodeC_buf,(UWORD)data_width,0);	/* 全白イメージサイズをセットする */

	EncRL4.Cout = 0;
	EncRL4.Flag = 0;/* 白0､黒0データ受信時に使用 初期化 S.Wang 96/07/04 */
	EncRL4.Data = RL_Buffer_p + RLBUF_ENC_B4 + RLBUF_SIZE_B4 + RLBUF_SIZE_B4 + RLBUF_SIZE_B4;
	DecodeD_buf = &EncRL4;
	PutRL(DecodeD_buf,(UWORD)data_width,0);	/* 全白イメージサイズをセットする */

	first_line_encode = 1;	/*	By Y.Suzuki 1997/08/25	*/

	SCD_TxMode = SCN_StoreData.Mode;	/* イメージをＲＬに変換するところで参照しています。 */

	EncMemoryExecBkupData.IndexNo1 = MEM_NO_INDEX;
	EncMemoryExecBkupData.IndexNo2 = MEM_NO_INDEX;
	EncMemoryExecBkupData.ExecBlockNo = MEM_NO_INDEX;
	EncMemoryExecBkupData.NextBlockNo = MEM_NO_INDEX;
}


/*************************************************************************
	module		:[1ラインエンコードする関数]
	function	:[
		3.縮小処理(副走査)
		4.1ラインイメージからＲＬ符号に変換
		5.縮小加工(主走査)
		6.１ラインエンコード
	]
	return		:[
													MG3	MECM	SG3	SECM
			TX_PAGE_END					0			○	○		○	○		1ﾍﾟｰｼﾞ送信完了
			TX_BLOCK_END				1			×	○		×	○		64KByte送信完了
			TX_STOPPED					2			○	○		○	○		停止ＳＷ　ＯＮ
			TX_DOC_ERR					3			×	×		○	○		原稿繰り込み不良
			TX_LAMP_ERR					4			×	×		○	○		ﾗﾝﾌﾟｴﾗｰ
			TX_FILE_ERR					5			○	○		×	×		該当するﾒﾓﾘﾌｧｲﾙが存在しない
			TX_MEM_ERR					7			○	○		×	×		画像ﾒﾓﾘ画品質不良
			TX_1M_OVER					8 			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
			TX_SEPARATE					9 			×	×		○	○		F網設定時、送信がA4 2枚分に達した
	]
	common		:[]
	condition	:[]
	comment		:[
		ソフトコーデックのＤＲＡＭアクセス時、内蔵ＲＯＭ側で１つの間接参照ポインタ－しか用意されておらず、
		そのままでは、ＥｎｃｏｄｅとＤｅｃｏｄｅが同時に処理しようとすると、不具合が発生する。
		よって、セマフォで切り替えてＥｎｃｏｄｅとＤｅｃｏｄｅを処理するようにする。
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1998/10/01]
	author		:[木元修]
*************************************************************************/
void EncodeOneLine(void)
{
	WORD	cdc_status;


if (SCDC_SWITCHING_TEST == 0) {	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */

	wai_sem(semno.SCDC_DRAM_Access);

	CMN_DisableInterrupt();
	EncMemoryExecBkupData = MemoryExecData;
	MemoryExecData = SCN_ExecData;
	CMN_EnableInterrupt();
}

	cdc_status = 0;

/* 
** ScanPageMemReadLineはEncodeOneLineの後でインクリメントするように変更したので
** ここではScanPageMemReadLineをそのままの値のラインをＲＬ変換するように変更 1998/11/13 by T.Soneoka
*/
	/* １ライン イメージからＲＬに変換 */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RL_TO_IMAGE_EROM) {
		OneLineImgToRl(EncodeA_buf, &EncodeData, (UWORD)(ScanPageMemReadLine));		/* 外ＲＯＭ */
	}
	else {
		Fast1LineImgToRl(EncodeA_buf, &EncodeData, (UWORD)(ScanPageMemReadLine));	/* 内蔵ＲＯＭ */
	}

	/*	１０ｍｓタスク切替えする By Y.Suzuki 1996/08/23	*/
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & SCDC_10MS_WAIT) {
		wai_tsk(1);
	}

	/* タスクスイッチのさせるために挿入します 1999/03/17 by T.Soneoka */
	det_evt(SCN_DUMMY_EVT);

	if (SCDC_EncReduction) {
		if(!Skip(enc_rp)){/** 主走査縮小による副走査間引き処理 */
			RedLine(&EncodeData, EncodeA_buf,SCDC_EncReduction);
		}
	}

if (SCDC_SWITCHING_TEST == 1) {	/* For Debug SoftCodec Switch Test by O.Kimoto 1998/12/16 */

	wai_sem(semno.SCDC_DRAM_Access);

	CMN_DisableInterrupt();
	EncMemoryExecBkupData = MemoryExecData;
	MemoryExecData = SCN_ExecData;
	CMN_EnableInterrupt();
}

	/** １ラインエンコード */
	SCD_EOL_WriteCount++;		/*	By Y.Suzuki 1997/04/14	*/
	if (SCDC_EncReduction && first_line_encode) {/* 縮小送信時の参照ライン をセット By Y.Suzuki 1997/08/25 */
		EncodeB_buf->Cout = 0;
		PutRL(EncodeB_buf,EncodeData.Img_Size,0);
		first_line_encode = 0;
	}
	cdc_status = Mem_Encode(&EncodeData, EncodeA_buf, EncodeB_buf);

	/* メモリオーバーのチェック */
	if(cdc_status == RX_MEM_OVER) {
		EncCodecPageStatus = CDC_MEM_OVER;
	}
	if(EncCodecPageStatus == CDC_CONTINUE) {
		EncCodecPageStatus = CDC_RTC_DET;
	}

	CMN_DisableInterrupt();
	SCN_ExecData = MemoryExecData;
	MemoryExecData = EncMemoryExecBkupData;
	CMN_EnableInterrupt();	/* For Debug By O.Kimoto 1998/12/16 */

	/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
	sig_sem(semno.SCDC_DRAM_Access);

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
UBYTE SetReduce(UBYTE src_size, UBYTE dst_size)
{
	UBYTE  flag;
	/* Ｈ＿ＦＩＮＥの処理 */

	switch(src_size){
	case SYS_DOCUMENT_A3_SIZE:
		if(dst_size == SYS_DOCUMENT_A4_SIZE)
			flag = 1;
		else if(dst_size == SYS_DOCUMENT_B4_SIZE)
			flag = 2;
		else
			flag = 0;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		if(dst_size == SYS_DOCUMENT_A4_SIZE)
			flag = 3;
		else
			flag = 0;
		break;
	default:
	case SYS_DOCUMENT_A4_SIZE:
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


/********************************************************
	module		:[１ライン分のイメージをＲＬに変換する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[内蔵ＲＯＭ]
	comment		:[]
	machine		:[SH7041]
	language	:[SHC]
	keyword		:[]
	date		:[[1997/6/17]
	author		:[鈴木郁二]
*********************************************************/
void OneLineImgToRl(struct WorkBuf_t *point,
					struct CdcBlk_t *scdcp,
					UWORD line)
{

	UWORD rl_data;
	UWORD BufCntr;									/** １ラインバイト数カウンタ */
	UWORD buf_max;									/* 1ラインＭＡＸバイト数 */
	UWORD rl_cnt;
	UBYTE col_flag;
	UBYTE ImgBufData;								/** カラーデータ */
	UBYTE SfitCntr;									/** ８ ビットシフトカウンタ */

	rl_data = 0;										/** ＲＬ　データ */
	col_flag = 0;										/** ０＝白，１＝黒 */
	point->Cout = 0;
	point->Flag = 0;
	rl_cnt = 0;
	buf_max = ((scdcp->Img_Size)/8);

	SfitCntr = 8;
	rl_data = 0;
	col_flag = WHITE;

	for (BufCntr = 0; BufCntr != buf_max; BufCntr++){

#if (0)
** 		/* 間接ポインターに変更 By O.Kimoto 1998/09/24 */
** 		ImgBufData = Img_Buffer2[line][BufCntr];/* 本番一回に１ラインのみ符号化 */
#else
#if (0)	/* キャストミス by O.Kimoto 1998/10/19 */
** 		ImgBufData = *(img_buffer2 + (UWORD)(line * SCD_LINE_BUF2_WIDTH) + (UWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
#else
		ImgBufData = *(img_buffer2 + (UDWORD)(line * SCD_LINE_BUF2_WIDTH) + (UDWORD)BufCntr);/* 本番一回に１ラインのみ符号化 */
#endif
#endif

	/*	ImgBufData = CipherP -> Img_Buffer1[line][BufCntr];* デバック用 */

		if (!(BufCntr % 50)) {
		/*	wai_oneshot(1); By Y.Suzuki 97/10/29 */
		}

		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */
		if (ImgBufData == 0x00){
			if (col_flag == WHITE) {
				rl_data += SfitCntr;
			}
			else {
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = WHITE;
			}
		}
		else if (ImgBufData == 0xff){
			if (col_flag == BLACK){
				rl_data += SfitCntr;
			}
			else {
				PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
				rl_cnt += rl_data;
				rl_data = 8;
				col_flag = BLACK;
			}
		}
		/**速度　ｕｐの為の変更　 1997/03/27 by T.Mizuguchi */

		else {

 			do {
				if ((ImgBufData & 0x80) == WHITE) {		/* 白 ? */
					if (col_flag == WHITE) {
						rl_data++;
					}
					else {
						PutRL(point,rl_data,col_flag);	/** ＲＬバッファに書き込み */
						rl_cnt += rl_data;
						rl_data = 1;
						col_flag = WHITE;
					}
				}
				else {
					if (col_flag == BLACK) {
						rl_data++;
					}
					else {
						rl_cnt += rl_data;
						PutRL(point,rl_data,col_flag);
						rl_data = 1;
						col_flag = BLACK;
					}
				}
				ImgBufData <<= 1;
				SfitCntr--;
			} while (SfitCntr != 0);

		}
		SfitCntr = 8;
	}
	if (rl_data > 0) {
		rl_cnt += rl_data;
		PutRL(point,rl_data,col_flag);
	}
	return;
}

