/*
 *	@(#)$Id: SCN_IP.C,v 1.1.1.1 2005/04/04 04:24:27 mi93007 Exp $
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/scn/scn_ip.c
 *	Create:	Wed Dec 24 15:49:16 1997	by	ishiyama
 *	Description:
 *		Scanner Image Processor Control
 *		Sanyo LC82103 に特化した処理
 *	Change Log:
 *		\prj\eva\src\scn\scn_ip.cからコピーし、HINOKI用にメンテしました
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysshad.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysshad.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\cpu_def.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\ext_v\sys_data.h" /* 1999/06/29 by T.Soneoka */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
#include "\src\atlanta\define\syslocal.h"
#include "\src\atlanta\ext_v\ini_tbl.h"		/* 2002/03/11 T.Takagi */
#endif
/*
 *	Name:	Initialize Image Processor
 *	Create:	Fri Jan 16 15:40:11 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	InzImageProcessor(void);
 *	Description:
 *		SANYO 画処理チップ LC82103 レジスタ初期化
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzImageProcessor(void)
{
	UBYTE	MaskAdj;
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_0, LC821033_IniSreg[0]);
		Output(SREG_1, LC821033_IniSreg[1]);
		Output(SREG_2, LC821033_IniSreg[2]);
		Output(SREG_3, LC821033_IniSreg[3]);
		Output(SREG_4, LC821033_IniSreg[4]);
		Output(SREG_5, LC821033_IniSreg[5]);
		Output(SREG_6, LC821033_IniSreg[6]);
		Output(SREG_7, LC821033_IniSreg[7]);
		Output(SREG_8, LC821033_IniSreg[8]);
		Output(SREG_9, LC821033_IniSreg[9]);
		Output(SREG_A, LC821033_IniSreg[0x0a]);
		if (CHK_SP_Test()) {
			Work = LC821033_IniSreg[0x0b];
			Work &= ~IP_SP_LC33;
			Work |= CHK_SP_Test();
			Output(SREG_B, Work);
		} else {
			Output(SREG_B, LC821033_IniSreg[0x0b]);
		}
		Output(SREG_C, LC821033_IniSreg[0x0c]);
		Output(SREG_D, LC821033_IniSreg[0x0d]);
		Output(SREG_E, LC821033_IniSreg[0x0e]);
		Output(SREG_F, LC821033_IniSreg[0x0f]);
		Output(SREG_10, LC821033_IniSreg[0x10]);
		Output(SREG_11, LC821033_IniSreg[0x11]);
		Output(SREG_12, LC821033_IniSreg[0x12]);
		Work = SYB_AgcDaHighReference & 0x3f;
		Output(SREG_13, Work);
		Output(SREG_14, LC821033_IniSreg[0x14]);
		Output(SREG_15, LC821033_IniSreg[0x15]);
		Output(SREG_18, LC821033_IniSreg[0x18]);
		Output(SREG_19, LC821033_IniSreg[0x19]);
		Output(SREG_1A, LC821033_IniSreg[0x1a]);

		/* NTTファネット指摘事項No5
		** マスク量を原稿サイズによって変えます
		** A4 210mm に対してマスク1mm（LEDに対しては4mm 216-(2*4)=208mm）
		** B4 256mm に対してマスク2mm（LED256に対しては256-(2*2)=252mm）、プリントも252mmしか印字できない
		** とします（既に製品仕様書にうたっているため）
		** 2002/10/30 by T.Soneoka
		*/
		if (SYS_DocumentScanSize == SYS_DOCUMENT_A4_SIZE) {
			Work = 0x20; /* 4mm指定 Bit3～7 */
		} else { /* (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) */
			Work = 0x10; /* 2mm指定 Bit3～7 */
		}
		Work >>= 3;
		if (CHK_DocumentWidthFull()) {
			Work = 0;
		} else {
			MaskAdj = CHK_QueryScanMaskAdjust();
			if (MaskAdj & 0x80) {
				Work += (MaskAdj & 0x1f);
				if (Work > 0x1f) {
					Work = 0x1f;
				}
			} else {
				if (Work > (MaskAdj & 0x1f)) {
					Work -= (MaskAdj & 0x1f);
				} else {
					Work = 0;
				}
			}
		}
		Work <<= 3;

		Output(SREG_1B, Work);

		Output(SREG_1C, LC821033_IniSreg[0x1c]);
		Output(SREG_1D, LC821033_IniSreg[0x1d]);
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, IniSreg[0]);
		Output(SREG_1, IniSreg[1]);
		Output(SREG_2, IniSreg[2]);
		Output(SREG_3, IniSreg[3]);
		Output(SREG_4, IniSreg[4]);
		Output(SREG_5, IniSreg[5]);
		Output(SREG_6, IniSreg[6]);
		Output(SREG_7, IniSreg[7]);
		Output(SREG_8, IniSreg[8]);
		Output(SREG_9, SYB_BlackCorrectionData);
		Output(SREG_A, IniSreg[0x0a]);
		if (CHK_SP_Test()) {
			Work = IniSreg[0x0b];
			Work &= ~IP_SP;
			Work |= CHK_SP_Test();
			Output(SREG_B, Work);
		} else {
			Output(SREG_B, IniSreg[0x0b]);
		}
		Output(SREG_C, IniSreg[0x0c]);
		Output(SREG_D, IniSreg[0x0d]);
		Output(SREG_E, IniSreg[0x0e]);
		Output(SREG_F, IniSreg[0x0f]);
		Output(SREG_10, IniSreg[0x10]);
		Output(SREG_11, SYB_AgcDaLowReference);
		Output(SREG_12, IniSreg[0x12]);
		Output(SREG_13, SYB_AgcDaHighReference);
		Output(SREG_14, IniSreg[0x14]);
		Output(SREG_15, IniSreg[0x15]);
		Output(SREG_18, IniSreg[0x18]);
		Output(SREG_19, IniSreg[0x19]);
		Output(SREG_1A, IniSreg[0x1a]);

		/* NTTファネット指摘事項No5
		** マスク量を原稿サイズによって変えます
		** A4 210mm に対してマスク1mm（LEDに対しては4mm 216-(2*4)=208mm）
		** B4 256mm に対してマスク2mm（LED256に対しては256-(2*2)=252mm）、プリントも252mmしか印字できない
		** とします（既に製品仕様書にうたっているため）
		** 2002/10/30 by T.Soneoka
		*/
		if (SYS_DocumentScanSize == SYS_DOCUMENT_A4_SIZE) {
			Work = 0x20; /* 4mm指定 Bit3～7 */
		} else { /* (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) */
			Work = 0x10; /* 2mm指定 Bit3～7 */
		}
		Work >>= 3;
		if (CHK_DocumentWidthFull()) {
			Work = 0;
		} else {
			MaskAdj = CHK_QueryScanMaskAdjust();
			if (MaskAdj & 0x80) {
				Work += (MaskAdj & 0x1f);
				if (Work > 0x1f) {
					Work = 0x1f;
				}
			} else {
				if (Work > (MaskAdj & 0x1f)) {
					Work -= (MaskAdj & 0x1f);
				} else {
					Work = 0;
				}
			}
		}
		Work <<= 3;

		Output(SREG_1B, Work);

		Output(SREG_1C, IniSreg[0x1c]);
		Output(SREG_1D, IniSreg[0x1d]);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, IniSreg[0]);
	Output(SREG_1, IniSreg[1]);
	Output(SREG_2, IniSreg[2]);
	Output(SREG_3, IniSreg[3]);
	Output(SREG_4, IniSreg[4]);
	Output(SREG_5, IniSreg[5]);
	Output(SREG_6, IniSreg[6]);
	Output(SREG_7, IniSreg[7]);
	Output(SREG_8, IniSreg[8]);
	Output(SREG_9, SYB_BlackCorrectionData);
	Output(SREG_A, IniSreg[0x0a]);
	if (CHK_SP_Test()) {
		Work = IniSreg[0x0b];
		Work &= ~IP_SP;
		Work |= CHK_SP_Test();
		Output(SREG_B, Work);
	} else {
		Output(SREG_B, IniSreg[0x0b]);
	}
	Output(SREG_C, IniSreg[0x0c]);
	Output(SREG_D, IniSreg[0x0d]);
	Output(SREG_E, IniSreg[0x0e]);
	Output(SREG_F, IniSreg[0x0f]);
	Output(SREG_10, IniSreg[0x10]);
	Output(SREG_11, SYB_AgcDaLowReference);
	Output(SREG_12, IniSreg[0x12]);
	Output(SREG_13, SYB_AgcDaHighReference);
	Output(SREG_14, IniSreg[0x14]);
	Output(SREG_15, IniSreg[0x15]);
	Output(SREG_18, IniSreg[0x18]);
	Output(SREG_19, IniSreg[0x19]);
	Output(SREG_1A, IniSreg[0x1a]);

	/* NTTファネット指摘事項No5
	** マスク量を原稿サイズによって変えます
	** A4 210mm に対してマスク1mm（LEDに対しては4mm 216-(2*4)=208mm）
	** B4 256mm に対してマスク2mm（LED256に対しては256-(2*2)=252mm）、プリントも252mmしか印字できない
	** とします（既に製品仕様書にうたっているため）
	** 2002/10/30 by T.Soneoka
	*/
	if (SYS_DocumentScanSize == SYS_DOCUMENT_A4_SIZE) {
		Work = 0x20; /* 4mm指定 Bit3～7 */
	} else { /* (SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE) */
		Work = 0x10; /* 2mm指定 Bit3～7 */
	}
	Work >>= 3;
	if (CHK_DocumentWidthFull()) {
		Work = 0;
	} else {
		MaskAdj = CHK_QueryScanMaskAdjust();
		if (MaskAdj & 0x80) {
			Work += (MaskAdj & 0x1f);
			if (Work > 0x1f) {
				Work = 0x1f;
			}
		} else {
			if (Work > (MaskAdj & 0x1f)) {
				Work -= (MaskAdj & 0x1f);
			} else {
				Work = 0;
			}
		}
	}
	Work <<= 3;

	Output(SREG_1B, Work);

	Output(SREG_1C, IniSreg[0x1c]);
	Output(SREG_1D, IniSreg[0x1d]);
#endif	/* End of defined(HINOKI2) */
}

/*
 *	Name:	Clear Image Processor Internal Memory
 *	Create:	Thu Apr 30 14:08:21 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	ClearIPInternalMemory(void);
 *	Description:
 *		内蔵メモリ(フィルタ用ラインメモリ、誤差拡散用誤差メモリ、
 *		副走査方向縮小用ラインメモリなど)初期化
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ClearIPInternalMemory(void)
{
	BOOL	CurrentScanInt;
	
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_0, (IP_FLG_LC33|IP_WD_LC33|IP_PM_2CHI_LC33|LC821033_IniSreg[0]));
		wai_tsk(5);						/* 5line 以上のWait */
		Output(SREG_0, LC821033_IniSreg[0]);
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, (IP_FLG|IP_WD|IP_PM_2CHI|IniSreg[0]));
		wai_tsk(5);						/* 5line 以上のWait */
		Output(SREG_0, IniSreg[0]);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, (IP_FLG|IP_WD|IP_PM_2CHI|IniSreg[0]));
	wai_tsk(5);						/* 5line 以上のWait */
	Output(SREG_0, IniSreg[0]);
#endif	/* End of defined(HINOKI2) */

	EnableScannerInt = CurrentScanInt;
}

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
/*************************************************************************
	module		:[IFLGが1になるのを待つ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1999/12/27]
	author		:[大島 修]
*************************************************************************/
void	WaitIflgOn(void)		/* LC821033仕様の為、追加 Y.Kano 2003/07/08 */
{
	while (!(Input(SREG_0) & IP_IFLG_LC33)) {
		wai_tsk(1);
	}
}
#endif	/* End of defined(HINOKI2) */

/*
 *	Name:	Wait IFLG Off
 *	Create:	Thu Jan 22 15:58:26 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	WaitIflgOff(void);
 *	Description:
 *		Wait for IFLG Turn To 0
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	WaitIflgOff(void)
{
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		while (Input(SREG_0) & IP_IFLG_LC33) {
			wai_tsk(1);
		}
	}
	else {	/* LC82103仕様 */
		while (Input(SREG_0) & IP_IFLG) {
			wai_tsk(1);
		}
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	while (Input(SREG_0) & IP_IFLG) {
		wai_tsk(1);
	}
#endif	/* End of defined(HINOKI2) */
}

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
/*************************************************************************
	module		:[IMFLGが1になるのを待つ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1999/11/02]
	author		:[大島 修]
*************************************************************************/
void	WaitImflgOn(void)		/* LC821033仕様の為、追加 Y.Kano 2003/07/08 */
{
	while (!LC821033_CheckIMFLG()) {
		wai_tsk(1);
	}
}

/*************************************************************************
	module		:[IMFLGが0になるのを待つ]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[1999/12/20]
	author		:[大島 修]
*************************************************************************/
void	WaitImflgOff(void)		/* LC821033仕様の為、追加 Y.Kano 2003/07/08 */
{
	while (LC821033_CheckIMFLG()) {
		wai_tsk(1);
	}
}
#endif	/* End of defined(HINOKI2) */

/***********************************************************************
 *	Analog
 ***********************************************************************/
/*
 *	Name:	Set Auto Gain Control
 *	Create:	Mon Jan 19 14:38:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	SetAgc(
 *		UBYTE	Mode,					// デジタルクランプのモード
 *		UBYTE	ClampPoint);			// クランプ位置
 *	Description:
 *		内蔵 A/D コンバータのダイナミックレンジをとるためゲインを調整
 *		1)初期設定
 *		2)白基準読込み
 *		3)１ライン以上のウェイト
 *		4)レジスタ読取り
 *		5)AGC 設定値演算
 *		6)レジスタ設定
 *		LC82103 技術資料 12 CPU の制御フロー参照
 *		光源は ON しておくこと
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetAgc(void)
{
	UBYTE	Work;
	UBYTE	Maxd;
	UBYTE	Mind;
	BOOL	CurrentScanInt;
	UBYTE	MaxdSmpl[10];
	UBYTE	MindSmpl[10];
	int	Index;
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	UBYTE	daa;
	UBYTE	add_ref;
#endif

	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;
	
	/* 1)初期設定 */
	SetClamp(AgcClampMode, AgcClampPoint);/* Set Digital Clamp */

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_13, IP_DAHA_MAX_LC33);		/* センサ信号期間 A/D ハイリファレンス用 D/A 値(DAHA) 最大値 */
		Output(SREG_14, IP_DAHT_MAX_LC33);		/* 温度信号期間 A/D ハイリファレンス用 D/A 値(DAHT) 最大値 */
		Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */
		Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(AgcPes & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

		/* 2)白基準読込み */
		WaitIflgOff();
		Output(SREG_0, IP_PM_2CHI_LC33);

		/* MIND 作成 */
		LampOff();
		wai_tsk(5);						/* 光量安定待ち */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MindSmpl[Index] = Input(SREG_8);
		}
		Mind = CalcCenterAverage(MindSmpl);

		/* MAXD 作成 */

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
  #endif
		LampOn();

		/*
		** 光量安定待ちを５０ｍｓから１ｓに伸ばします
		** 1999/03/15 by T.Soneoka
		*/
		wai_tsk(100);						/* 光量安定待ち */

		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MaxdSmpl[Index] = Input(SREG_7);
		}
		Maxd = CalcCenterAverage(MaxdSmpl);

		/* AGC設定 三洋の指示どおりにします */
		daa = 0x35;
		add_ref = 0x02;			/* リファレンス電圧 */
		while (1) {
			LC821033_SetTMPR(ENABLE);
			LC821033_SetDAHA(daa);
			wai_tsk(1);
			Work = (UBYTE)LC821033_CheckFF();
			if (Work == 0x0f) {
				LC821033_SetTMPR(ENABLE);
				LC821033_SetDAHA((UBYTE)(daa + add_ref));
			 	/* リファレンスを分けないとゴミが出る */
				SYB_AgcDaHighReference = daa + add_ref;
				break;
			}
			else {
				daa--;
				if (!daa) {
					break;
				}
			}
		}
		Work = SYB_AgcDaHighReference & 0x3f;
		Output(SREG_13, Work);
		SYB_AgcDaLowReference  = (UBYTE)((((UWORD)Mind * 17) / 100) + 0x0a);

		/*
		** ＤＡＬＡオフセット＋１ 並川からの依頼 
		** 1999/02/08 by T.Soneoka 
		*/
		SYB_AgcDaLowReference += 1;

		SYB_AgcDaLowReference  += CHK_QueryAgcLowRefOffset();
	}
	else {	/* LC82103仕様 */
		Output(SREG_13, IP_DAHA_MAX);		/* センサ信号期間 A/D ハイリファレンス用 D/A 値(DAHA) 最大値 */
		Output(SREG_14, IP_DAHT_MAX);		/* 温度信号期間 A/D ハイリファレンス用 D/A 値(DAHT) 最大値 */
		Output(SREG_11, IP_DALA_MIN);		/* センサ信号期間 A/D ローレファレンス用 D/A 値(DALA) 最小値 */
		Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
		Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(AgcPes & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

		/* 2)白基準読込み */
		WaitIflgOff();
		Output(SREG_0, IP_PM_2CHI);

		/* MIND 作成 */
		LampOff();
		wai_tsk(5);						/* 光量安定待ち */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);
			
			/* 4)レジスタ読取り */
			MindSmpl[Index] = Input(SREG_8);
		}
		Mind = CalcCenterAverage(MindSmpl);

		/* MAXD 作成 */

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
  #endif
		LampOn();

		/*
		** 光量安定待ちを５０ｍｓから１ｓに伸ばします
		** 1999/03/15 by T.Soneoka
		*/
		wai_tsk(100);						/* 光量安定待ち */

		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MaxdSmpl[Index] = Input(SREG_7);
		}
		Maxd = CalcCenterAverage(MaxdSmpl);

		/* 5)AGC 設定値演算 */
		/* 6)レジスタ設定 */
		/* Work = (64 * (InMax - DAHRL))/(DAHRH - DAHRL); */
		/*
	 	*	8bit A/D のHight Reference が 4.2v, Low Reference が 0.8v
	 	*	6bit D/A のHight Reference が 5.0v, Low Reference が 0.0v
	 	*	(((4.2v-0.8v)/256) * maxd +0.8v)/((5v-0v)/64) = 0.17
	 	*	Offset 0x0b,0x0a は、
	 	*	6bit D/A (Hight Reference:5.0v, Low Reference:0.0v)で、
	 	*	0.8v を出力するために設定
	 	*/
		SYB_AgcDaHighReference = (UBYTE)((((UWORD)Maxd * 17) / 100) + 0x0b);
		SYB_AgcDaHighReference -= 3;
		SYB_AgcDaHighReference += CHK_QueryAgcHighRefOffset();
		Output(SREG_13, SYB_AgcDaHighReference);
		SYB_AgcDaLowReference  = (UBYTE)((((UWORD)Mind * 17) / 100) + 0x0a);

		/*
		** ＤＡＬＡオフセット＋１ 並川からの依頼 
		** 1999/02/08 by T.Soneoka 
		*/
		SYB_AgcDaLowReference += 1;

		SYB_AgcDaLowReference  += CHK_QueryAgcLowRefOffset();
		Output(SREG_11, SYB_AgcDaLowReference);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_13, IP_DAHA_MAX);		/* センサ信号期間 A/D ハイリファレンス用 D/A 値(DAHA) 最大値 */
	Output(SREG_14, IP_DAHT_MAX);		/* 温度信号期間 A/D ハイリファレンス用 D/A 値(DAHT) 最大値 */
	Output(SREG_11, IP_DALA_MIN);		/* センサ信号期間 A/D ローレファレンス用 D/A 値(DALA) 最小値 */
	Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
	Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
	Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */
	Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
	Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
	Output(SREG_1B, Work);
	Work = (UBYTE)(AgcPes & 0x00ff);
	Output(SREG_1C, Work);
	Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

	/* 2)白基準読込み */
	WaitIflgOff();
	Output(SREG_0, IP_PM_2CHI);

	/* MIND 作成 */
	LampOff();
	wai_tsk(5);						/* 光量安定待ち */
	for (Index = 0; Index < 10; Index++) {
		/* 3)１ライン以上のウェイト */
		wai_tsk(1);
		
		/* 4)レジスタ読取り */
		MindSmpl[Index] = Input(SREG_8);
	}
	Mind = CalcCenterAverage(MindSmpl);

	/* MAXD 作成 */

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
  #endif
	LampOn();

	/*
	** 光量安定待ちを５０ｍｓから１ｓに伸ばします
	** 1999/03/15 by T.Soneoka
	*/
	wai_tsk(100);						/* 光量安定待ち */

	for (Index = 0; Index < 10; Index++) {
		/* 3)１ライン以上のウェイト */
		wai_tsk(1);
		
		/* 4)レジスタ読取り */
		MaxdSmpl[Index] = Input(SREG_7);
	}
	Maxd = CalcCenterAverage(MaxdSmpl);

	/* 5)AGC 設定値演算 */
	/* 6)レジスタ設定 */
	/* Work = (64 * (InMax - DAHRL))/(DAHRH - DAHRL); */
	/*
	 *	8bit A/D のHight Reference が 4.2v, Low Reference が 0.8v
	 *	6bit D/A のHight Reference が 5.0v, Low Reference が 0.0v
	 *	(((4.2v-0.8v)/256) * maxd +0.8v)/((5v-0v)/64) = 0.17
	 *	Offset 0x0b,0x0a は、
	 *	6bit D/A (Hight Reference:5.0v, Low Reference:0.0v)で、
	 *	0.8v を出力するために設定
	 */
	SYB_AgcDaHighReference = (UBYTE)((((UWORD)Maxd * 17) / 100) + 0x0b);
	SYB_AgcDaHighReference -= 3;
	SYB_AgcDaHighReference += CHK_QueryAgcHighRefOffset();
	Output(SREG_13, SYB_AgcDaHighReference);
	SYB_AgcDaLowReference  = (UBYTE)((((UWORD)Mind * 17) / 100) + 0x0a);

	/*
	** ＤＡＬＡオフセット＋１ 並川からの依頼 
	** 1999/02/08 by T.Soneoka 
	*/
	SYB_AgcDaLowReference += 1;

	SYB_AgcDaLowReference  += CHK_QueryAgcLowRefOffset();
	Output(SREG_11, SYB_AgcDaLowReference);

#endif	/* End of defined(HINOKI2) */
	/* Restore Interrupt */
	EnableScannerInt = CurrentScanInt;
}

/*
 *	Name:	Calculate Center Average 10
 *	Create:	Thu Jun 04 14:19:14 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82013.h"
 *		UBYTE	CalcCenterAverage(UWORD	Smpl[5]);
 *	Description:
 *		要素10個の真ん中8個の平均値を返す
 *	Return Value:
 *		UWORD
 *	Change Log:
 *		
 */
UBYTE	CalcCenterAverage(UBYTE	Smpl[10])
{
	int	Index;
	int	Min;
	int	Max;
	UWORD	Temp;

	/* 最小値の抽出 */
	Min = 0;
	for (Index = 0; Index < 10; Index++) {
		if (Smpl[Min] >= Smpl[Index]) {
			Min = Index;
		}
	}

	/* 最大値の抽出 */
	Max = 0;
	for (Index = 0; Index < 10; Index++) {
		if (Index != Min) {
			if (Smpl[Max] <= Smpl[Index]) {
				Max = Index;
			}
		}
	}

	/* 平均値の計算 */
	Temp = 0;
	for (Index = 0; Index < 10; Index++) {
		if ((Index != Min) && (Index != Max)) {
			Temp += Smpl[Index];
		}
	}
	return	(UBYTE)(Temp / 8);
}

/***********************************************************************
 *	デジタルクランプ
 ***********************************************************************/
/*
 *	Name:	Set Digital Clamp Parameter
 *	Create:	Fri Jan 16 16:05:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	SetClamp(
 *		UBYTE	Mode,					// デジタルクランプのモード
 *		UBYTE	ClampPoint);			// クランプ位置
 *	Description:
 *		デジタルクランプのモードとクランプ位置を設定
 *		割込み禁止／許可処理は,外部で行うこと。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetClamp(
	UBYTE	Mode,					/* デジタルクランプのモード(IP_DC_XX) */
	UBYTE	ClampPoint)				/* クランプ位置 */
{
	UBYTE	Sreg;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Sreg = Input(SREG_1);
		Sreg = ((Sreg & ~IP_DC_LC33) | Mode);
		Output(SREG_1, Sreg);
		Sreg = Input(SREG_6);
		Sreg = ((Sreg & ~IP_CP_LC33) | ClampPoint);
		Output(SREG_6, Sreg);
	}
	else {	/* LC82103仕様 */
		Sreg = Input(SREG_1);
		Sreg = ((Sreg & ~IP_DC) | Mode);
		Output(SREG_1, Sreg);
		Sreg = Input(SREG_6);
		Sreg = ((Sreg & ~IP_CP) | ClampPoint);
		Output(SREG_6, Sreg);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Sreg = Input(SREG_1);
	Sreg = ((Sreg & ~IP_DC) | Mode);
	Output(SREG_1, Sreg);
	Sreg = Input(SREG_6);
	Sreg = ((Sreg & ~IP_CP) | ClampPoint);
	Output(SREG_6, Sreg);
#endif	/* End of defined(HINOKI2) */
}


/***********************************************************************
 *	歪み補正
 ***********************************************************************/
/*
 *	Name:	Make Shading Data
 *	Create:	Tue Jan 20 15:26:35 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	MakeShadingData(void);
 *	Description:
 *		シェーディングデータ作成
 *		歪み補正:黒データ作成
 *		歪み補正:白補正データ作成
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	MakeShadingData(void)
{
	UBYTE	*SrcPtr;
	UBYTE	*DestPtr;
	WORD	Counter;
	WORD	Wcr1Stat;	/* insert 98.09.18 M.IIDA */
	UBYTE	Work;
	BOOL	CurrentScanInt;
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2004/01/19 */
	UBYTE	MaxdSmpl[10];
	UBYTE	MindSmpl[10];
	UDWORD	SrcAdr;
	UDWORD	DestAdr;
	UWORD	i;
	UBYTE	daa;
	UBYTE	add_ref;
	UBYTE	maxd;
	UBYTE	mind;

	UBYTE	int_enable;
	UBYTE	data_high;
	UBYTE	data_low;
	int		Index;
 #if (1)
	UDWORD	shading_avr;	/* 黒シェーディング平均値 by Y.Kano 2004/01/27 */
 #endif
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		CurrentScanInt = EnableScannerInt;
		EnableScannerInt = FALSE;

	#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

		if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
			HaltClockOn();
			wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
			SubResetOff();
			SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
		}

		InzImageProcessor();	/* LC82103レジスタ初期化 */
	#endif

		/* ガンマ補正 */
		SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

		/* シェーディング処理開始位置、期間設定 */
		Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */

		/* 処理開始位置、期間設定 */
		Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(AgcPes & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

		/* クランプ設定 */
		SetClamp(AgcClampMode, 0x19);/* Set Digital Clamp */

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
  #endif
		/* 歪み補正:白補正データ作成 */
		LampOn();
		wai_tsk(250);

		/* MAXD測定 TH算出用 */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MaxdSmpl[Index] = Input(SREG_7);
		}
		maxd = CalcCenterAverage(MaxdSmpl);

		/* AGC設定 三洋の指示どおりにします */
		daa = 0x35;
		add_ref = 0x02;			/* リファレンス電圧 */
		while (1) {
			LC821033_SetTMPR(ENABLE);
			LC821033_SetDAHA(daa);
			wai_tsk(1);
			Work = (UBYTE)LC821033_CheckFF();
			if (Work == 0x0f) {
				LC821033_SetTMPR(ENABLE);
				LC821033_SetDAHA((UBYTE)(daa + add_ref));
			 	/* リファレンスを分けないとゴミが出る */
				SYB_AgcDaHighReference = daa + add_ref;
				break;
			}
			else {
				daa--;
				if (!daa) {
					break;
				}
			}
		}

		/* 歪み補正:白データ作成 */
		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			WaitImflgOff();		/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_WHITE_LC33));
			ScanExecFlagOff();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			wai_tsk(1);
			ScanExecFlagOn();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			WaitIflgOn();		/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			wai_tsk(1);			/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			ScanExecFlagOff();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
		}
		WaitIflgOff();

		/* 白選択 */
		WaitIflgOff();
		WaitImflgOff();
		LC821033_SetMSEL(SCN_SD_WHITE);
		LC821033_SetMFLG(ENABLE);
		WaitImflgOn();
		CMN_DisableInterrupt();
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_WhiteShadingRAM[0];

		Wcr1Stat = SH__WCR1; 		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		/* データをSRAMに保存 8bit */
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		SH__WCR1 = Wcr1Stat;		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		WaitIflgOff();
		LC821033_SetMFLG(DISABLE);
		CMN_EnableInterrupt();
		WaitImflgOff();

		/* ランプ消灯 */
		LampOff();
		wai_tsk(250);

		/* MIND測定 TH算出用 */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MindSmpl[Index] = Input(SREG_8);
		}
		mind = CalcCenterAverage(MindSmpl);

		/* 歪み補正:黒データ作成 */
		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			WaitImflgOff();
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_BLACK_LC33));
			ScanExecFlagOff();
			wai_tsk(1);
			ScanExecFlagOn();
			WaitIflgOn();
			wai_tsk(1);
			ScanExecFlagOff();
		}
		WaitIflgOff();

		/* 黒選択 */
		WaitIflgOff();
		WaitImflgOff();
		LC821033_SetMSEL(SCN_SD_BLACK);
		LC821033_SetMFLG(ENABLE);
		WaitImflgOn();
		CMN_DisableInterrupt();
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_BlackShadingRAM[0];
 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
		shading_avr = 0;
 #endif

		Wcr1Stat = SH__WCR1; 			/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		/* データをSRAMに保存 8bit */
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
			shading_avr += *SrcPtr;
 #endif
			*DestPtr++ = *SrcPtr++;
		}
		SH__WCR1 = Wcr1Stat;			/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
		shading_avr /= SYS_SHADING_MAX;
		DestPtr = &SYB_BlackShadingRAM[0];

		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = (UBYTE)shading_avr;
		}
		
/*		for (Counter = 0; Counter < 9; Counter++) {*/	/* 画処理テスト用 by Y.Kano 2004/03/30 */
/*			SYB_MachineParameter[M_PARA_SW_I1 + Counter] = SYB_BlackShadingRAM[Counter];
		}*/
 #endif
		WaitIflgOff();
		LC821033_SetMFLG(DISABLE);
		CMN_EnableInterrupt();
		WaitImflgOff();

		Output(SREG_A, (IP_RSTB_LC33 | (LC821033_IniSreg[0x0a] & IP_TH_LC33)));

		/* 白Shading Data 孤立点除去 */
		if (SCN_WHITE_THRESHOLD != 0) {
			DestPtr = &SYB_WhiteShadingRAM[0];
			for (Counter = SYS_SHADING_MAX; Counter > 2; Counter--) {
				DestPtr++;
				if (*(DestPtr - 1) > *DestPtr) {
					data_low = (*(DestPtr - 1) - *DestPtr);
				}
				else {
					data_low = (*DestPtr - *(DestPtr - 1));
				}

				if (*DestPtr > *(DestPtr + 1)) {
					data_high = (*DestPtr - *(DestPtr + 1));
				}
				else {
					data_high = (*(DestPtr + 1) - *DestPtr);
				}

				if (data_low < data_high) {
					if (data_low >= SCN_WHITE_THRESHOLD) {
						*DestPtr = *(DestPtr - 1);
					}
				}
				else {
					if (data_high >= SCN_WHITE_THRESHOLD) {
						*DestPtr = *(DestPtr + 1);
					}
				}
			}
		}

		/* 黒Shading Data 孤立点除去 */
		if (SCN_BLACK_THRESHOLD != 0) {
			DestPtr = &SYB_BlackShadingRAM[0];
			for (Counter = SYS_SHADING_MAX; Counter > 2; Counter--) {
				DestPtr++;
				if (*(DestPtr - 1) > *DestPtr) {
					data_low = (*(DestPtr - 1) - *DestPtr);
				}
				else {
					data_low = (*DestPtr - *(DestPtr - 1));
				}

				if (*DestPtr > *(DestPtr + 1)) {
					data_high = (*DestPtr - *(DestPtr + 1));
				}
				else {
					data_high = (*(DestPtr + 1) - *DestPtr);
				}

				if (data_low < data_high) {
					if (data_low >= SCN_BLACK_THRESHOLD) {
						*DestPtr = *(DestPtr - 1);
					}
				}
				else {
					if (data_high >= SCN_BLACK_THRESHOLD) {
						*DestPtr = *(DestPtr + 1);
					}
				}
			}
		}

		/* 白シェーディング調整 by M.Maeda 2001/07/25 */
		DestPtr = &SYB_WhiteShadingRAM[0];
		for (Counter = 0; Counter < SYS_SHADING_MAX; Counter++) {
			if (Counter % 2) {	/* 奇数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			else {				 /* 偶数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			DestPtr++;
		}

		/* 黒シェーディング調整 by M.Maeda 2001/07/25 */
		DestPtr = &SYB_BlackShadingRAM[0];
		for (Counter = 0; Counter < SYS_SHADING_MAX; Counter++) {
			if (Counter % 2) {	/* 奇数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			else {				 /* 偶数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			DestPtr++;
		}
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
#endif

		EnableScannerInt = CurrentScanInt;
	}
	else {	/* LC82103仕様 */
		CurrentScanInt = EnableScannerInt;
		EnableScannerInt = FALSE;

	#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */

		SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

		if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
			HaltClockOn();
			wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
			SubResetOff();
			SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
		}

		InzImageProcessor();	/* LC82103レジスタ初期化 */

	#endif

		/* ガンマ補正 */
		SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

		/* ゲインコントロール */
	#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
	#endif
		LampOn();

		/*
		** ＣＳＤＲ Ｎｏ１３０ ＣＣＤ調整モード
		** テストの終了は電源OFF/ONとする。
		*/
		if (CHK_UNI_ShadingTest()) {
			wai_tsk(0xffff);
		}

		SetAgc();

		/* 歪み補正:黒データ作成 */
		LampOff();
		wai_tsk(10);

		SetClamp(ScanClampMode, ScanClampPoint);	/* Set Digital Clamp */	

		Output(SREG_19, ScanSesB4);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, ScanSelB4);			/* 補正有効期間長(SEL) */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((ScanPesB4 >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(ScanPesB4 & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, ScanPelB4);			/* 処理有効期間長(PEL) */

		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			Output(SREG_0, (IP_FLG | IP_PM_BLACK));
			wai_tsk(1);
			Output(SREG_0, IP_PM_BLACK);
		}
		WaitIflgOff();
		SYB_BlackCorrectionData = Input(SREG_9);

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
  #endif
		/* 歪み補正:白補正データ作成 */
		LampOn();
		/*
		** 光量安定待ちを１００ｍｓから１ｓに伸ばします
		** 1999/03/15 by T.Soneoka
		*/
		wai_tsk(100);

		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			Output(SREG_0, (IP_FLG | IP_PM_WHITE));
			wai_tsk(1);
			Output(SREG_0, IP_PM_WHITE);
		}
		WaitIflgOff();
	
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_ShadingRAM[0];
		Wcr1Stat = SH__WCR1; 
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;
		Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
		WaitScanLineInt();
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
		SH__WCR1 = Wcr1Stat;
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
#endif

		EnableScannerInt = CurrentScanInt;
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */

	SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

	if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
	}

	InzImageProcessor();	/* LC82103レジスタ初期化 */

#endif

	/* ガンマ補正 */
	SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

	/* ゲインコントロール */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();

	/*
	** ＣＳＤＲ Ｎｏ１３０ ＣＣＤ調整モード
	** テストの終了は電源OFF/ONとする。
	*/
	if (CHK_UNI_ShadingTest()) {
		wai_tsk(0xffff);
	}

	SetAgc();

	/* 歪み補正:黒データ作成 */
	LampOff();
	wai_tsk(10);

	SetClamp(ScanClampMode, ScanClampPoint);	/* Set Digital Clamp */	

	Output(SREG_19, ScanSesB4);			/* 補正有効期間スタート(SES) */
	Output(SREG_1A, ScanSelB4);			/* 補正有効期間長(SEL) */
	Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
	Work |= (UBYTE)((ScanPesB4 >> 8) & 0x00ff);
	Output(SREG_1B, Work);
	Work = (UBYTE)(ScanPesB4 & 0x00ff);
	Output(SREG_1C, Work);
	Output(SREG_1D, ScanPelB4);			/* 処理有効期間長(PEL) */

	for (Counter = 0; Counter < 5; Counter++) {
		WaitIflgOff();
		Output(SREG_0, (IP_FLG | IP_PM_BLACK));
		wai_tsk(1);
		Output(SREG_0, IP_PM_BLACK);
	}
	WaitIflgOff();
	SYB_BlackCorrectionData = Input(SREG_9);

  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
  #endif
	/* 歪み補正:白補正データ作成 */
	LampOn();
	/*
	** 光量安定待ちを１００ｍｓから１ｓに伸ばします
	** 1999/03/15 by T.Soneoka
	*/
	wai_tsk(100);

	for (Counter = 0; Counter < 5; Counter++) {
		WaitIflgOff();
		Output(SREG_0, (IP_FLG | IP_PM_WHITE));
		wai_tsk(1);
		Output(SREG_0, IP_PM_WHITE);
	}
	WaitIflgOff();
	
	SrcPtr = &Lc82103Ram[0];
	DestPtr = &SYB_ShadingRAM[0];
	Wcr1Stat = SH__WCR1; 
	SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;
	Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
	WaitScanLineInt();
	for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
		*DestPtr++ = *SrcPtr++;
	}
	Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
	SH__WCR1 = Wcr1Stat;
#endif	/* End of defined(HINOKI2) */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
	SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
#endif

	EnableScannerInt = CurrentScanInt;
}


/*
 *	Name:	Set Shading Data
 *	Create:	Tue Jan 20 16:05:37 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		SetShadingData(void);
 *	Description:
 *		歪み補正データセット
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetShadingData(void)
{
	UBYTE	*SrcPtr;
	UBYTE	*DestPtr;
	WORD	Counter;
	WORD	Wcr1Stat;	/* insert 98.09.18 M.IIDA */

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		CMN_DisableInterrupt();		/* 追加 by Y.Kano 2003/11/27 */

		/* 歪み補正:黒データセット */
		LC821033_SetMSEL(SCN_SD_BLACK);
  #if defined(HINOKI3) && (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */ /* 朱色読取り対応 2005/01/24 */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
				SrcPtr = &SYB_BlackShadingRAM_ForRedScan[0];
			}
			else {
				SrcPtr  = &SYB_BlackShadingRAM[0];	/* コピー元 */
			}
		}
		else {
			SrcPtr  = &SYB_BlackShadingRAM[0];	/* コピー元 */
		}
  #else
		SrcPtr  = &SYB_BlackShadingRAM[0];	/* コピー元 */
  #endif

		DestPtr = &Lc82103Ram[0];
		ScanExecFlagOff();
		WaitIflgOff();
		LC821033_SetMFLG(ENABLE);
		WaitImflgOn();

		Wcr1Stat = SH__WCR1; 		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter -= 64) {
			/* 割込み禁止にする時間を短縮したいのでベタ書きします */
			*DestPtr++ = *SrcPtr++; /* 1 */
			*DestPtr++ = *SrcPtr++; /* 2 */
			*DestPtr++ = *SrcPtr++; /* 3 */
			*DestPtr++ = *SrcPtr++; /* 4 */
			*DestPtr++ = *SrcPtr++; /* 5 */
			*DestPtr++ = *SrcPtr++; /* 6 */
			*DestPtr++ = *SrcPtr++; /* 7 */
			*DestPtr++ = *SrcPtr++; /* 8 */
			*DestPtr++ = *SrcPtr++; /* 9 */
			*DestPtr++ = *SrcPtr++; /* 10 */
			*DestPtr++ = *SrcPtr++; /* 11 */
			*DestPtr++ = *SrcPtr++; /* 12 */
			*DestPtr++ = *SrcPtr++; /* 13 */
			*DestPtr++ = *SrcPtr++; /* 14 */
			*DestPtr++ = *SrcPtr++; /* 15 */
			*DestPtr++ = *SrcPtr++; /* 16 */
			*DestPtr++ = *SrcPtr++; /* 17 */
			*DestPtr++ = *SrcPtr++; /* 18 */
			*DestPtr++ = *SrcPtr++; /* 19 */
			*DestPtr++ = *SrcPtr++; /* 20 */
			*DestPtr++ = *SrcPtr++; /* 21 */
			*DestPtr++ = *SrcPtr++; /* 22 */
			*DestPtr++ = *SrcPtr++; /* 23 */
			*DestPtr++ = *SrcPtr++; /* 24 */
			*DestPtr++ = *SrcPtr++; /* 25 */
			*DestPtr++ = *SrcPtr++; /* 26 */
			*DestPtr++ = *SrcPtr++; /* 27 */
			*DestPtr++ = *SrcPtr++; /* 28 */
			*DestPtr++ = *SrcPtr++; /* 29 */
			*DestPtr++ = *SrcPtr++; /* 30 */
			*DestPtr++ = *SrcPtr++; /* 31 */
			*DestPtr++ = *SrcPtr++; /* 32 */
			*DestPtr++ = *SrcPtr++; /* 33 */
			*DestPtr++ = *SrcPtr++; /* 34 */
			*DestPtr++ = *SrcPtr++; /* 35 */
			*DestPtr++ = *SrcPtr++; /* 36 */
			*DestPtr++ = *SrcPtr++; /* 37 */
			*DestPtr++ = *SrcPtr++; /* 38 */
			*DestPtr++ = *SrcPtr++; /* 39 */
			*DestPtr++ = *SrcPtr++; /* 40 */
			*DestPtr++ = *SrcPtr++; /* 41 */
			*DestPtr++ = *SrcPtr++; /* 42 */
			*DestPtr++ = *SrcPtr++; /* 43 */
			*DestPtr++ = *SrcPtr++; /* 44 */
			*DestPtr++ = *SrcPtr++; /* 45 */
			*DestPtr++ = *SrcPtr++; /* 46 */
			*DestPtr++ = *SrcPtr++; /* 47 */
			*DestPtr++ = *SrcPtr++; /* 48 */
			*DestPtr++ = *SrcPtr++; /* 49 */
			*DestPtr++ = *SrcPtr++; /* 50 */
			*DestPtr++ = *SrcPtr++; /* 51 */
			*DestPtr++ = *SrcPtr++; /* 52 */
			*DestPtr++ = *SrcPtr++; /* 53 */
			*DestPtr++ = *SrcPtr++; /* 54 */
			*DestPtr++ = *SrcPtr++; /* 55 */
			*DestPtr++ = *SrcPtr++; /* 56 */
			*DestPtr++ = *SrcPtr++; /* 57 */
			*DestPtr++ = *SrcPtr++; /* 58 */
			*DestPtr++ = *SrcPtr++; /* 59 */
			*DestPtr++ = *SrcPtr++; /* 60 */
			*DestPtr++ = *SrcPtr++; /* 61 */
			*DestPtr++ = *SrcPtr++; /* 62 */
			*DestPtr++ = *SrcPtr++; /* 63 */
			*DestPtr++ = *SrcPtr++; /* 64 */
		}
		SH__WCR1 = Wcr1Stat;		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

  #if (PRO_RED_SCAN == DISABLE)	/* 朱色原稿読み取り禁止 Y.Kano 2003/11/27 */
		Output(SREG_9, SYB_BlackCorrectionData);
  #endif
		/* 歪み補正:白補正データセット */
		WaitIflgOff();

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
   #if defined(HINOKI3)			/* 白シェーディングデータバッファの名前を変更 by Y.Kano 2005/01/24 */
				SrcPtr = &SYB_WhiteShadingRAM_ForRedScan[0];
   #else
				SrcPtr = &SYB_ShadingRAM_ForRedScan[0];
   #endif
			}
			else {
				SrcPtr  = &SYB_WhiteShadingRAM[0];	/* コピー元 */
			}
		}
		else {
			SrcPtr  = &SYB_WhiteShadingRAM[0];	/* コピー元 */
		}
  #else
		SrcPtr  = &SYB_WhiteShadingRAM[0];	/* コピー元 */
  #endif

		LC821033_SetMSEL(SCN_SD_WHITE); 	/* 白歪み補正メモリにアクセス */

		DestPtr = &Lc82103Ram[0];						/* コピー先 */

		Wcr1Stat = SH__WCR1; 		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter -= 64) {
			/* 割込み禁止にする時間を短縮したいのでベタ書きします */
			*DestPtr++ = *SrcPtr++;	/* 1 */
			*DestPtr++ = *SrcPtr++;	/* 2 */
			*DestPtr++ = *SrcPtr++;	/* 3 */
			*DestPtr++ = *SrcPtr++;	/* 4 */
			*DestPtr++ = *SrcPtr++;	/* 5 */
			*DestPtr++ = *SrcPtr++;	/* 6 */
			*DestPtr++ = *SrcPtr++;	/* 7 */
			*DestPtr++ = *SrcPtr++;	/* 8 */
			*DestPtr++ = *SrcPtr++;	/* 9 */
			*DestPtr++ = *SrcPtr++;	/* 10 */
			*DestPtr++ = *SrcPtr++;	/* 11 */
			*DestPtr++ = *SrcPtr++;	/* 12 */
			*DestPtr++ = *SrcPtr++;	/* 13 */
			*DestPtr++ = *SrcPtr++;	/* 14 */
			*DestPtr++ = *SrcPtr++;	/* 15 */
			*DestPtr++ = *SrcPtr++;	/* 16 */
			*DestPtr++ = *SrcPtr++;	/* 17 */
			*DestPtr++ = *SrcPtr++;	/* 18 */
			*DestPtr++ = *SrcPtr++;	/* 19 */
			*DestPtr++ = *SrcPtr++;	/* 20 */
			*DestPtr++ = *SrcPtr++;	/* 21 */
			*DestPtr++ = *SrcPtr++;	/* 22 */
			*DestPtr++ = *SrcPtr++;	/* 23 */
			*DestPtr++ = *SrcPtr++;	/* 24 */
			*DestPtr++ = *SrcPtr++;	/* 25 */
			*DestPtr++ = *SrcPtr++;	/* 26 */
			*DestPtr++ = *SrcPtr++;	/* 27 */
			*DestPtr++ = *SrcPtr++;	/* 28 */
			*DestPtr++ = *SrcPtr++;	/* 29 */
			*DestPtr++ = *SrcPtr++;	/* 30 */
			*DestPtr++ = *SrcPtr++;	/* 31 */
			*DestPtr++ = *SrcPtr++;	/* 32 */
			*DestPtr++ = *SrcPtr++;	/* 33 */
			*DestPtr++ = *SrcPtr++;	/* 34 */
			*DestPtr++ = *SrcPtr++;	/* 35 */
			*DestPtr++ = *SrcPtr++;	/* 36 */
			*DestPtr++ = *SrcPtr++;	/* 37 */
			*DestPtr++ = *SrcPtr++;	/* 38 */
			*DestPtr++ = *SrcPtr++;	/* 39 */
			*DestPtr++ = *SrcPtr++;	/* 40 */
			*DestPtr++ = *SrcPtr++;	/* 41 */
			*DestPtr++ = *SrcPtr++;	/* 42 */
			*DestPtr++ = *SrcPtr++;	/* 43 */
			*DestPtr++ = *SrcPtr++;	/* 44 */
			*DestPtr++ = *SrcPtr++;	/* 45 */
			*DestPtr++ = *SrcPtr++;	/* 46 */
			*DestPtr++ = *SrcPtr++;	/* 47 */
			*DestPtr++ = *SrcPtr++;	/* 48 */
			*DestPtr++ = *SrcPtr++;	/* 49 */
			*DestPtr++ = *SrcPtr++;	/* 50 */
			*DestPtr++ = *SrcPtr++;	/* 51 */
			*DestPtr++ = *SrcPtr++;	/* 52 */
			*DestPtr++ = *SrcPtr++;	/* 53 */
			*DestPtr++ = *SrcPtr++;	/* 54 */
			*DestPtr++ = *SrcPtr++;	/* 55 */
			*DestPtr++ = *SrcPtr++;	/* 56 */
			*DestPtr++ = *SrcPtr++;	/* 57 */
			*DestPtr++ = *SrcPtr++;	/* 58 */
			*DestPtr++ = *SrcPtr++;	/* 59 */
			*DestPtr++ = *SrcPtr++;	/* 60 */
			*DestPtr++ = *SrcPtr++;	/* 61 */
			*DestPtr++ = *SrcPtr++;	/* 62 */
			*DestPtr++ = *SrcPtr++;	/* 63 */
			*DestPtr++ = *SrcPtr++;	/* 64 */
		}
		SH__WCR1 = Wcr1Stat;		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		Output(SREG_A, (IP_RSTB_LC33 | (LC821033_IniSreg[0x0a] & IP_TH_LC33)));

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
				SYS_IsRedShading = TRUE;	/* 朱色読み取り用シェーディングがセットされていることを示すフラグ */
			}
			else {
				SYS_IsRedShading = FALSE;
			}
		}
		else {
			SYS_IsRedShading = FALSE;
		}
  #endif

		LC821033_SetMFLG(DISABLE);
		WaitImflgOff();
		CMN_EnableInterrupt();		/* Add by Y.Kano 2003/11/27 */
	}
	else {	/* LC82103仕様 */
		/* 歪み補正:黒データセット */
		WaitIflgOff();
		Output(SREG_0, IP_PM_BLACK);
		WaitIflgOff();
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
				Output(SREG_9, SYB_BLK_CorrectionDataForRedSCN);
			}
			else {
				Output(SREG_9, SYB_BlackCorrectionData);
			}
		}
		else {
			Output(SREG_9, SYB_BlackCorrectionData);
		}
  #else
		Output(SREG_9, SYB_BlackCorrectionData);
  #endif
		/* 歪み補正:白補正データセット */
		Output(SREG_0, IP_PM_WHITE);
		WaitIflgOff();

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
				SrcPtr = &SYB_ShadingRAM_ForRedScan[0];
			}
			else {
				SrcPtr = &SYB_ShadingRAM[0];
			}
		}
		else {
			SrcPtr = &SYB_ShadingRAM[0];
		}
  #else
		SrcPtr = &SYB_ShadingRAM[0];
  #endif
		DestPtr = &Lc82103Ram[0];
		Wcr1Stat = SH__WCR1; 
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* 0x2642 */
		Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
		WaitScanLineInt();
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
		SH__WCR1 = Wcr1Stat;

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
				SYS_IsRedShading = TRUE;	/* 朱色読み取り用シェーディングがセットされていることを示すフラグ */
			}
			else {
				SYS_IsRedShading = FALSE;
			}
		}
		else {
			SYS_IsRedShading = FALSE;
		}
  #endif
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 歪み補正:黒データセット */
	WaitIflgOff();
	Output(SREG_0, IP_PM_BLACK);
	WaitIflgOff();
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
			Output(SREG_9, SYB_BLK_CorrectionDataForRedSCN);
		}
		else {
			Output(SREG_9, SYB_BlackCorrectionData);
		}
	}
	else {
		Output(SREG_9, SYB_BlackCorrectionData);
	}
  #else
	Output(SREG_9, SYB_BlackCorrectionData);
  #endif
	/* 歪み補正:白補正データセット */
	Output(SREG_0, IP_PM_WHITE);
	WaitIflgOff();

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
			SrcPtr = &SYB_ShadingRAM_ForRedScan[0];
		}
		else {
			SrcPtr = &SYB_ShadingRAM[0];
		}
	}
	else {
		SrcPtr = &SYB_ShadingRAM[0];
	}
  #else
	SrcPtr = &SYB_ShadingRAM[0];
  #endif
	DestPtr = &Lc82103Ram[0];
	Wcr1Stat = SH__WCR1; 
	SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* 0x2642 */
	Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
	WaitScanLineInt();
	for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
		*DestPtr++ = *SrcPtr++;
	}
	Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
	SH__WCR1 = Wcr1Stat;

  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYB_LocalStatus[0] & SYS_RED_SCAN) {		/* 朱色読み取り要求ならば */
			SYS_IsRedShading = TRUE;	/* 朱色読み取り用シェーディングがセットされていることを示すフラグ */
		}
		else {
			SYS_IsRedShading = FALSE;
		}
	}
	else {
		SYS_IsRedShading = FALSE;
	}
  #endif
#endif	/* End of defined(HINOKI2) */
}


/***********************************************************************
 *	多値解像度変換
 ***********************************************************************/
/*
 *	Name:	Set Resolution Transform
 *	Create:	Tue Jan 20 16:19:06 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	SetResolutionTransform(void);
 *	Description:
 *		多値解像度変換設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetResolutionTrasnfrom(void)
{
	UBYTE	Work;

	/* フィルタモードセット */
	Work = (Input(SREG_3) & ~IP_MFMX);
	Work |= CHK_PreFilter();
	Output(SREG_3, Work);
	
	/* 主走査方向多値解像度変換セット */
	Work = (Input(SREG_4) & ~IP_RES);
	Work |= CHK_Transform();
	Output(SREG_4, Work);
}


/***********************************************************************
 *	ガンマ補正
 ***********************************************************************/
/*
 *	Name:	Set Gamma Correction
 *	Create:	Tue Jan 20 16:34:37 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	SetGammaCorrection(
 *			UBYTE ScanMode);					// 送信モード(doc.h)
 *	Description:
 *		ガンマ補正テーブルセット
 *		ガンマ補正データを内蔵 RAM に直線補間で書込む
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetGammaCorrection(
	UBYTE	ScanMode,					/* 送信モード(doc.h) */
	UBYTE	Density)					/* 読み取り濃度(doc.h)  1998/07/20 by T.Soneoka */
{
	UBYTE	Work;
	BOOL	GrayScale;
	UBYTE	Pos;
	BOOL	CurrentScanInt;
	UBYTE	SavePm;
	UBYTE	DataMin;	/* 1999/06/28 by T.Soneoka */
	UBYTE	DataMax;	/* 1999/06/28 by T.Soneoka */
	UBYTE	DataSample;	/* 1999/06/28 by T.Soneoka */
	BYTE	shift;		/* 1999/06/29 by T.Soneoka */
	WORD	i;			/* 1999/06/29 by T.Soneoka */
	WORD	Counter;
	WORD	Wcr1Stat;
	
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;

	/* ガンマテーブルをライト */
	switch (ScanMode) {
	case SYS_NORMAL:
	case SYS_FINE:
	case SYS_SFINE:
	case SYS_HFINE:
		GrayScale = FALSE;
		break;
	default:
		GrayScale = TRUE;
		break;
	}
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/27 */
		SavePm = (Input(SREG_0) & IP_PM_LC33);
	}
	else {	/* LC82103仕様 */
		Work = Input(SREG_A);
		Output(SREG_A, (Work & ~IP_SDSEL));
		SavePm = (Input(SREG_0) & IP_PM);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work = Input(SREG_A);
	Output(SREG_A, (Work & ~IP_SDSEL));
	SavePm = (Input(SREG_0) & IP_PM);
#endif	/* End of defined(HINOKI2) */

	/*
	 *	1998/06/04:
	 *	竹内さんのリクエストにより、GAMMA 補正以外のモードに設定
	 */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG_LC33 | IP_PM_LC33)) | IP_PM_2CHI_LC33));
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG | IP_PM)) | IP_PM_2CHI));
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG | IP_PM)) | IP_PM_2CHI));
#endif	/* End of defined(HINOKI2) */

	WaitIflgOff();
	Wcr1Stat = SH__WCR1; 
/*
** ガンマメモリをアクセスするときのウェイトがはいっていない（タイプミスしている）
** コードは何も生成されていない（コンパイルエラーもでない）
** ガンマメモリをライトする場合は特にウェイト３でも問題なし。（リードはぎりぎりＯＫ）
** 1999/04/02 by T.Soneoka
*/
#if (0)
**	SH__WCR1, SH__WCR1_DATA_FOR_IMAGE_LSI;
#else
/*	SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI; */
#endif
/*
** ソフト直線補完処理に変更します
** 1999/06/28 by T.Soneoka
*/
#if (0)
**	Counter = 0;
**	Pos = 0;
**	do {
**		Lc82103Ram[Counter] = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos);
**		Counter += 0x10;
**		Pos++;
**	} while (Counter < 0x100);
**	Lc82103Ram[0xff] = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos);
#else
	if (CHK_QueryGammaDataSpecial()) {
		/*
		** 特殊ガンマ曲線 RDC-D86-001 項目4.
		** アドレス０ｘ００～０ｘ９ｆ：００
		** アドレス０ｘＡ０～０ｘｆｆ：ＦＦ
		** 1999/06/29 by T.Soneoka
		*/
		for (i = 0x00; i <= 0xff; i++) {
  #if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
			if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/28 */
				if (i <= 0x9f) {
					Lc821033GammaRam[i] = 0x00;
				} else {
					Lc821033GammaRam[i] = 0xff;
				}
			}
			else {	/* LC82103仕様 */
				if (i <= 0x9f) {
					Lc82103Ram[i] = 0x00;
				} else {
					Lc82103Ram[i] = 0xff;
				}
			}
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
			if (i <= 0x9f) {
				Lc82103Ram[i] = 0x00;
			} else {
				Lc82103Ram[i] = 0xff;
			}
  #endif	/* End of defined(HINOKI2) */
		}
	} else {
		/*
		** ソフト直線補完処理  RDC-D86-001 項目3.
		** 1999/06/28 by T.Soneoka
		*/
		Counter = 0;
		Pos = 0;
		do {
			DataMin = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos);
			DataMax = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos+1);
			DataSample = 16;
  #if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
			if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/28 */
				MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc821033GammaRam[Counter]);
			}
			else {	/* Lc82103仕様 */
				MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc82103Ram[Counter]);
			}
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
			MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc82103Ram[Counter]);
  #endif	/* End of defined(HINOKI2) */
			Counter += 0x10;
			Pos++;
		} while (Counter < 0xf0);
		DataMin = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos);
		DataMax = CHK_QueryGammaValue(GrayScale, Density, (UBYTE)Pos+1);
		DataSample = 15;
  #if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
		if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/28 */
			MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc821033GammaRam[Counter]);
			Lc821033GammaRam[0xff] = DataMax;
		}
		else {	/* LC82103仕様 */
			MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc82103Ram[Counter]);
			Lc82103Ram[0xff] = DataMax;
		}
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
		MakeDirectGammmaData(DataMin, DataMax, DataSample, (UBYTE *)&Lc82103Ram[Counter]);
		Lc82103Ram[0xff] = DataMax;
  #endif	/* End of defined(HINOKI2) */
	}
	/*
	** ガンマ補正データ調整 データシフト処理  RDC-D86-001 項目3.
	** 1999/06/28 by T.Soneoka
	*/
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYS_IsRedShading == TRUE) {
			shift = CHK_GammaShiftForRedScan();
		}
		else {
			shift = CHK_GammaShift();
		}
	}
	else {
		shift = CHK_GammaShift();
	}
  #else
	shift = CHK_GammaShift();
  #endif

  #if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/28 */
		if (shift > 0) {
			for (i = 0xff; i >= 0x00; i--) {
				if ((i-shift) < 0) {
					Lc821033GammaRam[i] = 0;
				} else {
					Lc821033GammaRam[i] = Lc821033GammaRam[i-shift];
				}
			}
		} else if (shift < 0) {
			for (i = 0x00; i <= 0xff; i++) {
				if ((i-shift) > 0xff) {
					Lc821033GammaRam[i] = 0xff;
				} else {
					Lc821033GammaRam[i] = Lc821033GammaRam[i-shift];
				}
			}
		}
	}
	else {	/* LC82103仕様 */
		if (shift > 0) {
			for (i = 0xff; i >= 0x00; i--) {
				if ((i-shift) < 0) {
					Lc82103Ram[i] = 0;
				} else {
					Lc82103Ram[i] = Lc82103Ram[i-shift];
				}
			}
		} else if (shift < 0) {
			for (i = 0x00; i <= 0xff; i++) {
				if ((i-shift) > 0xff) {
					Lc82103Ram[i] = 0xff;
				} else {
					Lc82103Ram[i] = Lc82103Ram[i-shift];
				}
			}
		}
 	}
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	if (shift > 0) {
		for (i = 0xff; i >= 0x00; i--) {
			if ((i-shift) < 0) {
				Lc82103Ram[i] = 0;
			} else {
				Lc82103Ram[i] = Lc82103Ram[i-shift];
			}
		}
	} else if (shift < 0) {
		for (i = 0x00; i <= 0xff; i++) {
			if ((i-shift) > 0xff) {
				Lc82103Ram[i] = 0xff;
			} else {
				Lc82103Ram[i] = Lc82103Ram[i-shift];
			}
		}
	}
  #endif	/* End of defined(HINOKI2) */
#endif

	
	SH__WCR1 = Wcr1Stat;

/*
** ソフト直線補完処理に変更します RDC-D86-001 項目3.
** 1999/06/28 by T.Soneoka
*/
#if (0)
**	Output(SREG_0, ((Input(SREG_0) & ~IP_PM) | (IP_FLG | IP_PM_GAMMA)));
**	wai_tsk(1);
**	Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG | IP_PM)) | IP_PM_GAMMA));
#endif
	WaitIflgOff();
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG_LC33 | IP_PM_LC33)) | SavePm));
	}
	else {
		Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG | IP_PM)) | SavePm));
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, ((Input(SREG_0) & ~(IP_FLG | IP_PM)) | SavePm));
#endif	/* End of defined(HINOKI2) */

	EnableScannerInt = CurrentScanInt;
}


/***********************************************************************
 *	filter
 ***********************************************************************/
/*
 *	Name:	Set 2D Emphasize Filter
 *	Create:	Wed Jan 21 15:03:04 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		Set2DFilter(
 *			UBYTE	ScanMode);			// 送信モード(doc.h)
 *	Description:
 *		二次元強調フィルタを設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	Set2DFilter(
	UBYTE	ScanMode)					/* 送信モード(doc.h) */
{
	BOOL	BinaryFilter;
	BOOL	GrayFilter;
	UBYTE	Work;

	BinaryFilter = FALSE;
	GrayFilter = FALSE;
	switch (ScanMode) {
	case SYS_NORMAL:
	case SYS_FINE:
	case SYS_SFINE:
	case SYS_HFINE:
		if (CHK_2ChiEmphasizeFilter()) {
			BinaryFilter = TRUE;
		}
		break;
	default:
		/* Gray Scale */
		if (CHK_GrayEmphasizeFilter()) {
			GrayFilter = TRUE;
		}
		if (CHK_ZouikiBunri()) {
			if (CHK_2ChiEmphasizeFilter()) {
				BinaryFilter = TRUE;
			}
		}
		break;
	}


	/* 二値化強調係数 */
	Work = Input(SREG_2) & ~(IP_BFMX|IP_BFMY);
	if (BinaryFilter) {
#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYS_IsRedShading == TRUE) {
				Work |= (CHK_BfmxForRedScan()|CHK_BfmyForRedScan());
			}
			else {
				Work |= (CHK_Bfmx()|CHK_Bfmy());
			}
		}
		else {
			Work |= (CHK_Bfmx()|CHK_Bfmy());
		}
#else
		Work |= (CHK_Bfmx()|CHK_Bfmy());
#endif
	}
	Output(SREG_2, Work);

	/* 中間調処理用フィルタ選択 */
	Work = (Input(SREG_3) & ~IP_HFMS);
	if (CHK_HalfToneSwitch()) {
		Work |= IP_HFMS;
	}
	Output(SREG_3, Work);

	/* 中間調強調係数 */
	Work = Input(SREG_2) & ~(IP_HFMX|IP_HFMY);
	if (GrayFilter) {
		Work |= (CHK_Hfmx() | CHK_Hfmy());
	}
	Output(SREG_2, Work);
}


#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/02 */
/***********************************************************************
 *	filter(LC821033仕様)
 ***********************************************************************/
/*************************************************************************
	module		:[二次元強調フィルタを設定]
	function	:[]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[二次元強調フィルタを設定]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SCN]
	date		:[2003/09/02]
	author		:[加納 義彦]
*************************************************************************/
void	Set2DFilter_LC821033(UBYTE scan_mode, UBYTE scan_density)
{
	UBYTE	filter;
	UBYTE	work;

	filter = 0;

	if ((scan_mode == SYS_NORMAL) || (scan_mode == SYS_FINE) || (scan_mode == SYS_SFINE)) {
		switch (scan_density) {
		case SYS_LIGHT_DENSITY:
		/* 西岡さんからの依頼 元に戻します。2004/03/22 */
			filter = FILTER1_1;		/* 強調フィルタ1、×1.0 */
			break;
		case SYS_NORMAL_DENSITY:
 #if (0)	/* 西岡さんからの依頼 2004/02/09 */
			filter = FILTER1_4;
 #else
			filter = FILTER1_1;		/* 強調フィルタ1、×1.0 */
 #endif
			break;
		case SYS_DARK_DENSITY:
 #if (0)	/* 西岡さんからの依頼 2004/02/09 */
			filter = FILTER1_2;		/* <- FILTER1_3 by M.Maeda 2001/07/23 */
 #else
			filter = FILTER1_HALF;	/* 強調フィルタ1、×0.5 */
 #endif
			break;
		default:
 #if (0)	/* 西岡さんからの依頼 2004/02/09 */
			filter = FILTER1_2;
 #else
			filter = FILTER1_1;		/* 強調フィルタ1、×1.0 */
 #endif
			break;
		}
		if (CHK_2ChiEmphasizeFilter()) {
			filter = CHK_2ChiEmphasizeFilter();
		}
	}
	else { /* ERR_DISPERSION */
		filter = FILTER2_1; /* ← FILTER_THOUGH ← FILTER_AVERAGE by M.Maeda 2001/08/06 ← 2001/07/25 */
		if (CHK_GrayEmphasizeFilter()) {
			filter = CHK_GrayEmphasizeFilter();
		}
	}

	/* 二次元フィルタの設定 */
	LC821033_Set2DFilter((UWORD)filter);
}
#endif	/* End of defined(HINOKI2) */

/***********************************************************************
 *	中間調処理
 ***********************************************************************/
/*
 *	Name:	Set Gray Scale Mode
 *	Create:	Wed Jan 22 17:19:04 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		SetGrayScaleMode(void);
 *	Description:
 *		中間調モードを設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetGrayScaleMode(void)
{
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/01 */
	if (!SYB_LC821033_Flg) {				/* LC821033対応フラグがOFF Y.Kano 2003/12/01 */
		/* 誤差拡散モード */
		Work = (Input(SREG_3) & ~IP_ERRM); /* 固定マトリックス */
		if (CHK_GosaMoveMatrix()) {
			Work |= IP_ERRM;		/* 移動マトリックス */
		}
		Output(SREG_3, Work);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 誤差拡散モード */
	Work = (Input(SREG_3) & ~IP_ERRM); /* 固定マトリックス */
	if (CHK_GosaMoveMatrix()) {
		Work |= IP_ERRM;		/* 移動マトリックス */
	}
	Output(SREG_3, Work);
#endif	/* End of defined(HINOKI2) */

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/01 */
	if (SYB_LC821033_Flg) {				/* LC821033対応フラグ Y.Kano 2003/12/01 */
		/* 重みマトリックス */
		Work = (Input(SREG_10) & ~IP_WVAL_LC33);
		Work |= (CHK_WeightValue() << 4);
		Output(SREG_10, Work);
	}
	else {	/* LC82103仕様 */
		/* 重みマトリックス */
		Work = (Input(SREG_10) & ~IP_WVAL);
		Work |= (CHK_WeightValue() << 4);
		Output(SREG_10, Work);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 重みマトリックス */
	Work = (Input(SREG_10) & ~IP_WVAL);
	Work |= (CHK_WeightValue() << 4);
	Output(SREG_10, Work);
#endif	/* End of defined(HINOKI2) */
}

/***********************************************************************
 *	二値化部
 ***********************************************************************/
/*
 *	Name:	Set 2Chi Parameter
 *	Create:	Wed Jan 22 17:19:04 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		Set2ChiParameter(void);
 *	Description:
 *		二値化パラメーター(TH, ATB)を設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	Set2ChiParamater(UBYTE Density, UBYTE Mode)
{
	WORD	Work;

	Work = SYB_MachineParameter[M_PARA_SW_C3] & 0x3f;
	if(!Work){
		switch (Density) {
		case SYS_LIGHT_DENSITY:
			Work = BinaryThresholdLevelValue[0][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H0], 4)];
			break;
		case SYS_NORMAL_DENSITY:
			Work = BinaryThresholdLevelValue[1][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H1], 4)];
			break;
		case SYS_DARK_DENSITY:
			Work = BinaryThresholdLevelValue[2][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H2], 4)];
			break;
		}
		/*
		** Ｎｏｒｍａｌ送信時の、濃度補正処理 RDC-D86-001 項目1.
		** 1999/06/29 by T.Soneoka
		*/
		if ((Mode == SYS_NORMAL)
		&& ((SYS_DocumentStoreItem == SYS_MEM_TX_FILE) || (SYS_DocumentStoreItem == SYS_MEM_FILE_EMPTY))) { /* モードがＮｏｒｍでかつメモリ送信かスキャナ送信のとき */
#if (0) /* 下記マシンパラメータ調整のデフォルトを＋５とします 1999/07/08 by T.Soneoka */
**			Work += 5;
#endif
			/*
			** ガンマ補正データをマシンパラメータから取得する場合は下記補正をしないようにする
			** 1999/07/08 by T.Soneoka
			*/
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
			if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/28 */
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
				if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
					if (SYS_IsRedShading == TRUE) {
						/* 朱色読み取り時はＧを見る 2002/03/23 T.Takagi */
						if (!((SYB_MachineParameter[M_PARA_SW_G2] & GAMMA_DATA_TEST_GRAY_FOR_RED)
						||    (SYB_MachineParameter[M_PARA_SW_G2] & GAMMA_DATA_TEST_FOR_RED_SCAN))) {
							Work += CHK_SliceLevelForNormTx();
						}
					}
					else {
						if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
						||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
							Work += CHK_SliceLevelForNormTx();
						}
					}
				}
				else {
					if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
					||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
						Work += CHK_SliceLevelForNormTx();
					}
				}
  #else
				if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
				||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
					Work += CHK_SliceLevelForNormTx();
				}
  #endif
  			}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
  #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
			if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
				if (SYS_IsRedShading == TRUE) {
					/* 朱色読み取り時はＧを見る 2002/03/23 T.Takagi */
					if (!((SYB_MachineParameter[M_PARA_SW_G2] & GAMMA_DATA_TEST_GRAY_FOR_RED)
					||    (SYB_MachineParameter[M_PARA_SW_G2] & GAMMA_DATA_TEST_FOR_RED_SCAN))) {
						Work += CHK_SliceLevelForNormTx();
					}
				}
				else {
					if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
					||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
						Work += CHK_SliceLevelForNormTx();
					}
				}
			}
			else {
				if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
				||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
					Work += CHK_SliceLevelForNormTx();
				}
			}
  #else
			if (!((SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY)
			||    (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST))) {
				Work += CHK_SliceLevelForNormTx();
			}
  #endif
#endif	/* End of defined(HINOKI2) */
		}
		if (Work < 0) {
			Work = 0;
		}
	}
	
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Work |= (Input(SREG_A) & ~IP_TH_LC33);
		Output(SREG_A, (UBYTE)Work);

		/* 二値化処理方法設定 */
		Work = (Input(SREG_0) & ~(IP_FLG_LC33 | IP_ATB_LC33));
		if (CHK_BinaryThresholdMethod()) {
			Work |= IP_ATB_LC33;
		}
	}
	else {	/* LC82103仕様 */
		Work |= (Input(SREG_A) & ~IP_TH);
		Output(SREG_A, (UBYTE)Work);

		/* 二値化処理方法設定 */
		Work = (Input(SREG_0) & ~(IP_FLG | IP_ATB));
		if (CHK_BinaryThresholdMethod()) {
			Work |= IP_ATB;
		}
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work |= (Input(SREG_A) & ~IP_TH);
	Output(SREG_A, (UBYTE)Work);

	/* 二値化処理方法設定 */
	Work = (Input(SREG_0) & ~(IP_FLG | IP_ATB));
	if (CHK_BinaryThresholdMethod()) {
		Work |= IP_ATB;
	}
#endif	/* End of defined(HINOKI2) */
	Output(SREG_0, Work);
}

/***********************************************************************
 *	像域分離処理
 ***********************************************************************/
/*
 *	Name:	Set Gray Scale Mode
 *	Create:	Wed Jan 22 17:19:04 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		SetZouikiBunri(
 *			UBYTE	ScanMode)	// 送信モード(doc.h)
 *	Description:
 *		像域分離パラメータを設定
 *		二値化モードで必要な設定も行うため必ずコールすること
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetZouikiBunri(
	UBYTE	ScanMode)					/* 送信モード(doc.h) */
{
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		/* 二値化処理モード設定 */
		Work = (Input(SREG_0) & ~(IP_FLG_LC33 | IP_BM_LC33));
		switch (ScanMode) {
		case SYS_NORMAL:
		case SYS_FINE:
		case SYS_SFINE:
		case SYS_HFINE:
			Work |= IP_BM_2CHI_LC33;
			break;
			/* no break */
		default:
			Work |= IP_BM_GRAY_LC33;
			break;
		}
	}
	else {	/* LC82103仕様 */
		/* エッジ検出レベル（像域分離パラメータ/文字領域用濃度差設定） */
		Work = (Input(SREG_D) & ~IP_XSL);
		Work |= CHK_EdgeDetectLevel();
		Output(SREG_D, Work);

		/* 文字領域判定サイズ設定 */
		Work = (Input(SREG_E) & ~IP_SDW);
		if (CHK_CharAreaWindowExtend()) {
			Work |= IP_SDW;
		}
		Output(SREG_E, Work);

		/* 網点検出処理 ON/OFF */
		Work = (Input(SREG_D) & ~IP_AON);
		if (CHK_AmitenDetect()) {
			Work |= IP_AON;
		}
		Output(SREG_D, Work);

		/* 網点スライスレベル */
		Work = (Input(SREG_E) & ~IP_ET);
		Work |= CHK_AmitenThresholdLevel();
		Output(SREG_E, Work);

		/* 網点領域用エッジペア設定 */
		Work = (Input(SREG_F) & ~IP_EP);
		Work |= CHK_AmitenEdgePare();
		Output(SREG_F, Work);

		/* 二値化処理モード設定 */
		Work = (Input(SREG_0) & ~(IP_FLG | IP_BM));
		switch (ScanMode) {
		case SYS_NORMAL:
		case SYS_FINE:
		case SYS_SFINE:
		case SYS_HFINE:
			Work |= IP_BM_2CHI;
			break;
			/* no break */
		default:
			if (CHK_ZouikiBunri()) {
				if (CHK_ZouikiSelector()) {
					Work |= IP_BM_SELECTOR;
				} else {
					Work |= IP_BM_FILTER;
				}
			} else {
				Work |= IP_BM_GRAY;
			}
			break;
		}
	}
#else	/* LC82103旧ﾊﾞｰｼﾞｮﾝ */
	/* エッジ検出レベル（像域分離パラメータ/文字領域用濃度差設定） */
	Work = (Input(SREG_D) & ~IP_XSL);
	Work |= CHK_EdgeDetectLevel();
	Output(SREG_D, Work);

	/* 文字領域判定サイズ設定 */
	Work = (Input(SREG_E) & ~IP_SDW);
	if (CHK_CharAreaWindowExtend()) {
		Work |= IP_SDW;
	}
	Output(SREG_E, Work);

	/* 網点検出処理 ON/OFF */
	Work = (Input(SREG_D) & ~IP_AON);
	if (CHK_AmitenDetect()) {
		Work |= IP_AON;
	}
	Output(SREG_D, Work);

	/* 網点スライスレベル */
	Work = (Input(SREG_E) & ~IP_ET);
	Work |= CHK_AmitenThresholdLevel();
	Output(SREG_E, Work);

	/* 網点領域用エッジペア設定 */
	Work = (Input(SREG_F) & ~IP_EP);
	Work |= CHK_AmitenEdgePare();
	Output(SREG_F, Work);

	/* 二値化処理モード設定 */
	Work = (Input(SREG_0) & ~(IP_FLG | IP_BM));
	switch (ScanMode) {
	case SYS_NORMAL:
	case SYS_FINE:
	case SYS_SFINE:
	case SYS_HFINE:
		Work |= IP_BM_2CHI;
		break;
		/* no break */
	default:
		if (CHK_ZouikiBunri()) {
			if (CHK_ZouikiSelector()) {
				Work |= IP_BM_SELECTOR;
			} else {
				Work |= IP_BM_FILTER;
			}
		} else {
			Work |= IP_BM_GRAY;
		}
		break;
	}
#endif	/* End of defined(HINOKI2) */
	Output(SREG_0, Work);
}
	
/***********************************************************************
 *	二値縮小処理部
 ***********************************************************************/
/*
 *	Name:	Set Scanner Reduction
 *	Create:	Wed Jan 23 20:08:04 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		SetScannerReduction(
 *			UBYTE	HReductionRate,	// 主走査方向縮小率
 *			UBYTE	VReductionRate);	// 副走査方向縮小率(IP_SUBM_*)
 *	Description:
 *		縮小設定を行う
 *		縮小するときのみコールすること
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetScannerReduction(
	UBYTE	HReductionRate,				/* 主走査方向縮小率 */
	UBYTE	VReductionRate)				/* 副走査方向縮小率(IP_SUBM_*) */
{
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_C, HReductionRate);

		/* 副走査方向縮小設定 */
		Work = (Input(SREG_1) & ~IP_SUBM_LC33);
		Work |= VReductionRate;
		Output(SREG_1, Work);
		Work = (Input(SREG_B) & ~IP_STHM_LC33);
		if (CHK_VReductionMethod()) {
			Work |= IP_STHM_LC33;			/* 単純間引き */
		}
		Output(SREG_B, Work);
	}
	else {	/* LC82103仕様 */
		/* 主走査方向縮小設定 */
		Work = (Input(SREG_B) & ~(IP_NRC|IP_RM));
		if (HReductionRate == 0) {
			/* 縮小しない */
			Work |= IP_NRC;
		} else {
			/* Uniq Switch の示すモードで縮小 */
			Work |= CHK_HReductionMethod();
		}
		Output(SREG_B, Work);
		Output(SREG_C, HReductionRate);

		/* 副走査方向縮小設定 */
		Work = (Input(SREG_1) & ~IP_SUBM);
		Work |= VReductionRate;
		Output(SREG_1, Work);
		Work = (Input(SREG_B) & ~IP_STHM);
		if (CHK_VReductionMethod()) {
			Work |= IP_STHM;				/* 単純間引き */
		}
		Output(SREG_B, Work);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 主走査方向縮小設定 */
	Work = (Input(SREG_B) & ~(IP_NRC|IP_RM));
	if (HReductionRate == 0) {
		/* 縮小しない */
		Work |= IP_NRC;
	} else {
		/* Uniq Switch の示すモードで縮小 */
		Work |= CHK_HReductionMethod();
	}
	Output(SREG_B, Work);
	Output(SREG_C, HReductionRate);

	/* 副走査方向縮小設定 */
	Work = (Input(SREG_1) & ~IP_SUBM);
	Work |= VReductionRate;
	Output(SREG_1, Work);
	Work = (Input(SREG_B) & ~IP_STHM);
	if (CHK_VReductionMethod()) {
		Work |= IP_STHM;				/* 単純間引き */
	}
	Output(SREG_B, Work);
#endif	/* End of defined(HINOKI2) */
}


/***********************************************************************
 *	白画素変換処理部
 ***********************************************************************/
/*
 *	Name:	Set White Change
 *	Create:	 1998/09/03 by T.Soneoka
 *	Synopsis:
 *		#include	"lc82103.h"
 *		SetWhiteChange(void)
 *	Description:
 *		白画素変換処理設定を行う
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetWhiteChange(void)
{
	UBYTE	Work;
	UBYTE	WhiteChangeValue;
	
#if (0) /* 直値やめます 1999/01/21 by T.Soneoka */
**	WhiteChangeValue = ((SYB_MachineParameter[22] & 0x06) >> 1); /* Ｃ：２－１～２ ゴミ判定(Reg5:0-1) */
#else
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
	if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
		if (SYS_IsRedShading == TRUE) {
			WhiteChangeValue = ((SYB_MachineParameter[M_PARA_SW_G2] & 0x06) >> 1); /* 朱色読み取り時はＧを見る 2002/03/23 T.Takagi */
 		}
		else {
			WhiteChangeValue = ((SYB_MachineParameter[M_PARA_SW_C2] & 0x06) >> 1); /* Ｃ：２－１～２ ゴミ判定(Reg5:0-1) */
		}
	}
	else {
		WhiteChangeValue = ((SYB_MachineParameter[M_PARA_SW_C2] & 0x06) >> 1); /* Ｃ：２－１～２ ゴミ判定(Reg5:0-1) */
	}
 #else
	WhiteChangeValue = ((SYB_MachineParameter[M_PARA_SW_C2] & 0x06) >> 1); /* Ｃ：２－１～２ ゴミ判定(Reg5:0-1) */
 #endif
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		if (WhiteChangeValue) {
			/* 白画素変換設定 */
			Work = (Input(SREG_B) & ~IP_WCHG_LC33);
			Work |= IP_WCHG_LC33;
			Output(SREG_B, Work);

			/* ゴミ判定設定 */
			Work = (Input(SREG_5) & ~IP_DSTC_LC33);
			Work |= WhiteChangeValue;
			Output(SREG_5, Work);
		}
	}
	else {	/* LC82103仕様 */
		if (WhiteChangeValue) {
			/* 白画素変換設定 */
			Work = (Input(SREG_B) & ~IP_WCHG);
			Work |= IP_WCHG;
			Output(SREG_B, Work);

			/* ゴミ判定設定 */
			Work = (Input(SREG_5) & ~IP_DSTC);
			Work |= WhiteChangeValue;
			Output(SREG_5, Work);
		}
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	if (WhiteChangeValue) {
		/* 白画素変換設定 */
		Work = (Input(SREG_B) & ~IP_WCHG);
		Work |= IP_WCHG;
		Output(SREG_B, Work);

		/* ゴミ判定設定 */
		Work = (Input(SREG_5) & ~IP_DSTC);
		Work |= WhiteChangeValue;
		Output(SREG_5, Work);
	}
#endif	/* End of defined(HINOKI2) */
}


/***********************************************************************
 *	Scanning Line
 ***********************************************************************/
/*
 *	Name:	ScanExecFlagOn
 *	Create:	Wed Jan 28 14:40:39 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	ScanExecFlagOn(void);
 *	Description:
 *		lc82103 の FLG(0:7) を ON する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScanExecFlagOn(void)
{
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Work = (Input(SREG_0) & ~IP_FLG_LC33);
		Work |= IP_FLG_LC33;
	}
	else {	/* LC82103仕様 */
		Work = (Input(SREG_0) & ~IP_FLG);
		Work |= IP_FLG;
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work = (Input(SREG_0) & ~IP_FLG);
	Work |= IP_FLG;
#endif	/* End of defined(HINOKI2) */

	Output(SREG_0, Work);
}

/*
 *	Name:	ScanExecFlagOff
 *	Create:	Wed Jan 28 14:40:39 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	ScanExecFlagOff(void);
 *	Description:
 *		lc82103 の FLG(0:7) を OFF する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScanExecFlagOff(void)
{
	UBYTE	Work;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Work = (Input(SREG_0) & ~IP_FLG_LC33);
	}
	else {	/* LC82103仕様 */
		Work = (Input(SREG_0) & ~IP_FLG);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work = (Input(SREG_0) & ~IP_FLG);
#endif	/* End of defined(HINOKI2) */

	Output(SREG_0, Work);
}

/*
 *	Name:	QueryScanExecFlag
 *	Create:	Wed Jan 28 14:40:39 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		BOOL	QueryScanExecFlag(void);
 *	Description:
 *		lc82103 の FLG(0:7) を調べる
 *	Return Value:
 *		TRUE:	FLG == 1
 *		FALSE:	FLG == 0
 *	Change Log:
 *		
 */
BOOL	QueryScanExecFlag(void)
{
	return	(Input(SREG_0) & IP_FLG) ? TRUE : FALSE;
}

/*
 *	Name:	Set 2 Chi Processing Mode
 *	Create:	Fri Apr 24 12:47:52 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	Set2ChiProcessingMode(void);
 *	Description:
 *		補正処理、二値化処理モードに処理モードを設定
 *		こうしないと、SDE が出力されない。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	Set2ChiProcessingMode(void)
{
	BOOL	CurrentScanInt;
	
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;

	WaitIflgOff();						/* 念のため IP_FLG Off を入れる必要があるかは、要検討 */
#if (0) /* 1998/09/04 by T.Soneoka ここでFLGをOnすると先頭１ラインに全白がでずにゴミがでます */
**	Output(SREG_0, (IP_FLG | IP_PM_2CHI));
#endif
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		Output(SREG_0, IP_PM_2CHI_LC33);
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, IP_PM_2CHI);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, IP_PM_2CHI);
#endif	/* End of defined(HINOKI2) */

	wai_tsk(1);						/* 念のため１ライン以上のウェイト */
	
	EnableScannerInt = CurrentScanInt;
}

void	WaitScanLineInt(void)
{
	CheckScanLineInt = FALSE;
	while (!CheckScanLineInt) {
	}
}

		
/*
 *	Name:	Set Image Processor for Scan
 *	Create:	Fri May 08 11:02:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	SetImageProcessor4Scan(
 *			struct ScanPageAtr	*Page)			// see feeder.h
 *	Description:
 *		読取りのため画処理 IC を設定する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetImageProcessor4Scan(
	struct ScanPageAtr	*Page)			/* see feeder.h */
{
	UBYTE	Work;
	UBYTE	clamp_point;
	Set2ChiProcessingMode();

	/* Set Digital Clamp */
#if (0) /* 直値やめます 1999/01/21 by T.Soneoka */
**	clamp_point = SYB_MachineParameter[24]; /* マシンパラメータ Ｃ４：０～７ */
#else
	clamp_point = SYB_MachineParameter[M_PARA_SW_C4]; /* マシンパラメータ Ｃ４：０～７ */
#endif
	if (!clamp_point) {
		clamp_point = ScanClampPoint;
	}
	SetClamp(ScanClampMode, clamp_point);

	if (Page->Size == SYS_DOCUMENT_A4_SIZE) {
		/* A4 設定 */
		Output(SREG_19, ScanSesA4);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, ScanSelA4);			/* 補正有効期間長(SEL) */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/01 */
		if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/12/01 */
			Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
		}
		else {	/* LC82103仕様 */
			Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
		}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
#endif	/* End of defined(HINOKI2) */
		Work |= (UBYTE)((ScanPesA4 >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(ScanPesA4 & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, ScanPelA4);			/* 処理有効期間長(PEL) */
	} else {
		/* B4 設定 */
		Output(SREG_19, ScanSesB4);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, ScanSelB4);			/* 補正有効期間長(SEL) */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/01 */
		if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/12/01 */
			Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
		}
		else {	/* LC82103仕様 */
			Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
		}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
#endif	/* End of defined(HINOKI2) */
		Work |= (UBYTE)((ScanPesB4 >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(ScanPesB4 & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, ScanPelB4);			/* 処理有効期間長(PEL) */
	}
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/27 */
		/* 多値解像度変換設定 */
		SetResolutionTrasnfrom();
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 多値解像度変換設定 */
	SetResolutionTrasnfrom();
#endif	/* End of defined(HINOKI2) */

	/* ガンマ補正テーブルセット */
	SetGammaCorrection(Page->Mode, Page->Density);
	
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/12/01 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/12/01 */
		/* 二次元強調フィルタを設定 */
		Set2DFilter_LC821033(Page->Mode,Page->Density);
	}
	else {	/* LC82103仕様 */
		/* 二次元強調フィルタを設定 */
		Set2DFilter(Page->Mode);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	/* 二次元強調フィルタを設定 */
	Set2DFilter(Page->Mode);
#endif	/* End of defined(HINOKI2) */

	/* 中間調モードを設定 */
	if (Page->Mode == SYS_GRAY64) {
		SetGrayScaleMode();
	}
	
	/* 二値化パラメーター(TH, ATB)を設定 */
/*
** Ｎｏｒｍ送信のときスライスレベルの補正を行なう RDC-D86-001 項目1.
** 1999/06/29 by T.Soneoka
*/
#if (0)
**	Set2ChiParamater(Page->Density);
#else
	Set2ChiParamater(Page->Density, Page->Mode);
#endif
	
	/*
	 * 像域分離パラメータを設定
	 * 二値化モードで必要な設定も行うため必ずコールすること
	 */
	SetZouikiBunri(Page->Mode);

	/* 縮小設定 */
	SetScannerReduction(Page->HolzReduction, Page->VertReduction);

	/* 白画素変換設定 */
	if (Page->Mode != SYS_GRAY64) {
		SetWhiteChange();
	}
}

/*----------------------------------------------------------------------------
 *	Thermistor Control
 *----------------------------------------------------------------------------*/
/*
 *	Name:	Initialize Thermistor Reference Voltage
 *	Create:	Mon Jun 01 15:08:12 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		void	InzTermistorRef(void);
 *	Description:
 *		Termistor A/D の Reference 電圧を設定する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzThermistorRef(void)
{
	Output(SREG_14, IP_DAHT_MAX);		/* 温度信号期間 A/D ハイリファレンス用 D/A 値(DAHT) 最大値 */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2004/03/31 */
	if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/27 */
		Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
#endif	/* End of defined(HINOKI2) */
}


/*
 *	Name:	Read Thermistor A/D Value
 *	Create:	Mon Jun 01 15:16:28 1998	by	ishiyama
 *	Synopsis:
 *		#include	"lc82103.h"
 *		UBYTE	ReadThermistor(void);
 *	Description:
 *		Thermistor 8bit A/D 変換後のの値を返す
 *	Return Value:
 *		UBYTE	0-255
 *	Change Log:
 *		
 */
UBYTE	ReadThermistor(void)
{
	return (AD_Thermistor());
}



UBYTE 	QueryCalPos(UBYTE Data, UBYTE Max)
{
	UBYTE Work;

	Work = Data & 0x7f;
	/* 保険 入力範囲制限チェック */
	if (Work > Max) {
		Work = Max;
	}
#if (0) /* テーブル取得の計算が間違っている 1999/1/22 by T.Soneoka */
**	/* 配列の位置を求る */
**	if (Data & 0x80) {
**		Work -= (Max-Work);
**	}
**	else {
**		Work += (Max+Work);
**	}
#else
	/* 配列の位置を求る */
	if (Data & 0x80) {
		Work = (Max-Work);
	}
	else {
		Work = (Max+Work);
	}
#endif
	return(Work);
}

/*
** ソフト直線補完処理に変更します RDC-D86-001 項目3.
** 1999/06/28 by T.Soneoka
*/
void MakeDirectGammmaData(UBYTE DataMin, UBYTE DataMax, UBYTE DataSample, UBYTE *Buf)
{
	UBYTE i;
	UWORD rate;
	
	rate = (UWORD)(((DataMax-DataMin)*100)/DataSample);
	for (i = 0; i < DataSample; i++) {
		*Buf = (UBYTE)(((rate*i)/100)+DataMin);
		Buf++;
	}
}

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/11 T.Takagi */
#if defined(HINOKI3)	/* 朱色原稿読み取り 2002/03/11 T.Takagi */ /* ＨＩＮＯＫＩ３は朱色読取り対応します。by Y.Kano 2005/01/24 */
void	MakeShadingDataForRedScan(void)
{
	UBYTE	*SrcPtr;
	UBYTE	*DestPtr;
	WORD	Counter;
	WORD	Wcr1Stat;	/* insert 98.09.18 M.IIDA */
	UBYTE	Work;
	BOOL	CurrentScanInt;
	UBYTE	MaxdSmpl[10];
	UBYTE	MindSmpl[10];
	UDWORD	SrcAdr;
	UDWORD	DestAdr;
	UWORD	i;
	UBYTE	daa;
	UBYTE	add_ref;
	UBYTE	maxd;
	UBYTE	mind;

	UBYTE	int_enable;
	UBYTE	data_high;
	UBYTE	data_low;
	int		Index;
	UDWORD	shading_avr;	/* 黒シェーディング平均値 by Y.Kano 2004/01/27 */

	
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		CurrentScanInt = EnableScannerInt;
		EnableScannerInt = FALSE;
		SYS_IsRedShading = TRUE;	/* 2002/03/23 T.Takagi */

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */

		SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

		if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
			HaltClockOn();
			wai_tsk(1); 				/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
			SubResetOff();
			SYS_HaltClock = TRUE;		/* クロックが供給されていることを示すフラグ */
		}

		InzImageProcessorForRedScan();	/* LC821033レジスタ初期化 */
 #endif

		/* ガンマ補正 */
		SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

		/* シェーディング処理開始位置、期間設定 */
		Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */

		/* 処理開始位置、期間設定 */
		Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(AgcPes & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

		/* クランプ設定 */
		SetClamp(AgcClampMode, 0x19);/* Set Digital Clamp */

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
 #endif
		/* 歪み補正:白補正データ作成 */
		LampOn();
		wai_tsk(250);

		/* MAXD測定 TH算出用 */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MaxdSmpl[Index] = Input(SREG_7);
		}
		maxd = CalcCenterAverage(MaxdSmpl);

		/* AGC設定 三洋の指示どおりにします */
		daa = 0x35;
		add_ref = 0x02;			/* リファレンス電圧 */
		while (1) {
			LC821033_SetTMPR(ENABLE);
			LC821033_SetDAHA(daa);
			wai_tsk(1);
			Work = (UBYTE)LC821033_CheckFF();
			if (Work == 0x0f) {
				LC821033_SetTMPR(ENABLE);
				LC821033_SetDAHA((UBYTE)(daa + add_ref));
			 	/* リファレンスを分けないとゴミが出る */
				SYB_AgcDaHighReferenceForRedSCN = daa + add_ref;
				break;
			}
			else {
				daa--;
				if (!daa) {
					break;
				}
			}
		}

		/* 歪み補正:白データ作成 */
		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			WaitImflgOff();		/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_WHITE_LC33));
			ScanExecFlagOff();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			wai_tsk(1);
			ScanExecFlagOn();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			WaitIflgOn();		/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			wai_tsk(1);			/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
			ScanExecFlagOff();	/* LC821033仕様の為、追加 by Y.Kano 2003/07/08 */
		}
		WaitIflgOff();

		/* 白選択 */
		WaitIflgOff();
		WaitImflgOff();
		LC821033_SetMSEL(SCN_SD_WHITE);
		LC821033_SetMFLG(ENABLE);
		WaitImflgOn();
		CMN_DisableInterrupt();
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_WhiteShadingRAM_ForRedScan[0];

		Wcr1Stat = SH__WCR1; 		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		/* データをSRAMに保存 8bit */
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		SH__WCR1 = Wcr1Stat;		/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		WaitIflgOff();
		LC821033_SetMFLG(DISABLE);
		CMN_EnableInterrupt();
		WaitImflgOff();

		/* ランプ消灯 */
		LampOff();
		wai_tsk(250);

		/* MIND測定 TH算出用 */
		for (Index = 0; Index < 10; Index++) {
			/* 3)１ライン以上のウェイト */
			wai_tsk(1);

			/* 4)レジスタ読取り */
			MindSmpl[Index] = Input(SREG_8);
		}
		mind = CalcCenterAverage(MindSmpl);

		/* 歪み補正:黒データ作成 */
		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			WaitImflgOff();
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_BLACK_LC33));
			ScanExecFlagOff();
			wai_tsk(1);
			ScanExecFlagOn();
			WaitIflgOn();
			wai_tsk(1);
			ScanExecFlagOff();
		}
		WaitIflgOff();

		/* 黒選択 */
		WaitIflgOff();
		WaitImflgOff();
		LC821033_SetMSEL(SCN_SD_BLACK);
		LC821033_SetMFLG(ENABLE);
		WaitImflgOn();
		CMN_DisableInterrupt();
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_BlackShadingRAM_ForRedScan[0];
 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
		shading_avr = 0;
 #endif

		Wcr1Stat = SH__WCR1; 			/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;	/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

		/* データをSRAMに保存 8bit */
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
			shading_avr += *SrcPtr;
 #endif
			*DestPtr++ = *SrcPtr++;
		}
		SH__WCR1 = Wcr1Stat;			/* データ書き込み時のタイミング合わせに使用していた 削除 by Y.Kano 2003/07/09 */

 #if (1)	/* 黒シェーディングの全画素平均を取る。 by Y.Kano 2004/01/27 */
		shading_avr /= SYS_SHADING_MAX;
		DestPtr = &SYB_BlackShadingRAM_ForRedScan[0];

		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = (UBYTE)shading_avr;
		}
		
/*		for (Counter = 0; Counter < 9; Counter++) {*/	/* 画処理テスト用 by Y.Kano 2004/03/30 */
/*			SYB_MachineParameter[M_PARA_SW_I1 + Counter] = SYB_BlackShadingRAM[Counter];
		}*/
 #endif
		WaitIflgOff();
		LC821033_SetMFLG(DISABLE);
		CMN_EnableInterrupt();
		WaitImflgOff();

		Output(SREG_A, (IP_RSTB_LC33 | (LC821033_IniSreg[0x0a] & IP_TH_LC33)));

		/* 白Shading Data 孤立点除去 */
		if (SCN_WHITE_THRESHOLD != 0) {
			DestPtr = &SYB_WhiteShadingRAM_ForRedScan[0];
			for (Counter = SYS_SHADING_MAX; Counter > 2; Counter--) {
				DestPtr++;
				if (*(DestPtr - 1) > *DestPtr) {
					data_low = (*(DestPtr - 1) - *DestPtr);
				}
				else {
					data_low = (*DestPtr - *(DestPtr - 1));
				}

				if (*DestPtr > *(DestPtr + 1)) {
					data_high = (*DestPtr - *(DestPtr + 1));
				}
				else {
					data_high = (*(DestPtr + 1) - *DestPtr);
				}

				if (data_low < data_high) {
					if (data_low >= SCN_WHITE_THRESHOLD) {
						*DestPtr = *(DestPtr - 1);
					}
				}
				else {
					if (data_high >= SCN_WHITE_THRESHOLD) {
						*DestPtr = *(DestPtr + 1);
					}
				}
			}
		}

		/* 黒Shading Data 孤立点除去 */
		if (SCN_BLACK_THRESHOLD != 0) {
			DestPtr = &SYB_BlackShadingRAM_ForRedScan[0];
			for (Counter = SYS_SHADING_MAX; Counter > 2; Counter--) {
				DestPtr++;
				if (*(DestPtr - 1) > *DestPtr) {
					data_low = (*(DestPtr - 1) - *DestPtr);
				}
				else {
					data_low = (*DestPtr - *(DestPtr - 1));
				}

				if (*DestPtr > *(DestPtr + 1)) {
					data_high = (*DestPtr - *(DestPtr + 1));
				}
				else {
					data_high = (*(DestPtr + 1) - *DestPtr);
				}

				if (data_low < data_high) {
					if (data_low >= SCN_BLACK_THRESHOLD) {
						*DestPtr = *(DestPtr - 1);
					}
				}
				else {
					if (data_high >= SCN_BLACK_THRESHOLD) {
						*DestPtr = *(DestPtr + 1);
					}
				}
			}
		}

		/* 白シェーディング調整 by M.Maeda 2001/07/25 */
		DestPtr = &SYB_WhiteShadingRAM_ForRedScan[0];
		for (Counter = 0; Counter < SYS_SHADING_MAX; Counter++) {
			if (Counter % 2) {	/* 奇数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			else {				 /* 偶数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			DestPtr++;
		}

		/* 黒シェーディング調整 by M.Maeda 2001/07/25 */
		DestPtr = &SYB_BlackShadingRAM_ForRedScan[0];
		for (Counter = 0; Counter < SYS_SHADING_MAX; Counter++) {
			if (Counter % 2) {	/* 奇数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			else {				 /* 偶数番目 */
				if (*DestPtr > 0) {
					*DestPtr = *DestPtr - (0);
				}
				else {
					*DestPtr = 0;
				}
			}
			DestPtr++;
		}
		SYS_IsRedShading = FALSE;	/* 2002/03/23 T.Takagi */

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
 #endif

		EnableScannerInt = CurrentScanInt;
	}
	else {	/* LC82103仕様 */

		CurrentScanInt = EnableScannerInt;
		EnableScannerInt = FALSE;

		SYS_IsRedShading = TRUE;	/* 2002/03/23 T.Takagi */

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */

		SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

		if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
			HaltClockOn();
			wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
			SubResetOff();
			SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
		}

		InzImageProcessorForRedScan();	/* LC821033レジスタ初期化 */

 #endif

		/* ガンマ補正 */
		SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

		/* ゲインコントロール */
 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
 #endif
		LampOn();

		/*
		** ＣＳＤＲ Ｎｏ１３０ ＣＣＤ調整モード
		** テストの終了は電源OFF/ONとする。
		*/
		if (CHK_UNI_ShadingTest()) {
			wai_tsk(0xffff);
		}

		SetAgc();

		/* 歪み補正:黒データ作成 */
		LampOff();
		wai_tsk(10);

		SetClamp(ScanClampMode, ScanClampPoint);	/* Set Digital Clamp */	

		Output(SREG_19, ScanSesB4);			/* 補正有効期間スタート(SES) */
		Output(SREG_1A, ScanSelB4);			/* 補正有効期間長(SEL) */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
		Work |= (UBYTE)((ScanPesB4 >> 8) & 0x00ff);
		Output(SREG_1B, Work);
		Work = (UBYTE)(ScanPesB4 & 0x00ff);
		Output(SREG_1C, Work);
		Output(SREG_1D, ScanPelB4);			/* 処理有効期間長(PEL) */

		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			Output(SREG_0, (IP_FLG | IP_PM_BLACK));
			wai_tsk(1);
			Output(SREG_0, IP_PM_BLACK);
		}
		WaitIflgOff();
		SYB_BlackCorrectionData = Input(SREG_9);

 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
		PC_24V_On();
 #endif
		/* 歪み補正:白補正データ作成 */
		LampOn();
		/*
		** 光量安定待ちを１００ｍｓから１ｓに伸ばします
		** 1999/03/15 by T.Soneoka
		*/
		wai_tsk(100);

		for (Counter = 0; Counter < 5; Counter++) {
			WaitIflgOff();
			Output(SREG_0, (IP_FLG | IP_PM_WHITE));
			wai_tsk(1);
			Output(SREG_0, IP_PM_WHITE);
		}
		WaitIflgOff();
	
		SrcPtr = &Lc82103Ram[0];
		DestPtr = &SYB_ShadingRAM[0];
		Wcr1Stat = SH__WCR1; 
		SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;
		Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
		WaitScanLineInt();
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
		SH__WCR1 = Wcr1Stat;
 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
 #endif

		EnableScannerInt = CurrentScanInt;
	}
}
#elif defined(HINOKI2)	/* defined(HINOKI2) */
void	MakeShadingDataForRedScan(void)
{
	UBYTE	*SrcPtr;
	UBYTE	*DestPtr;
	WORD	Counter;
	WORD	Wcr1Stat;	/* insert 98.09.18 M.IIDA */
	UBYTE	Work;
	BOOL	CurrentScanInt;
	
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;

	SYS_IsRedShading = TRUE;	/* 2002/03/23 T.Takagi */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */

	SYS_MakingShadingData = TRUE;		/* シェーディングデータ作成中 */

	if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて */
		HaltClockOn();
		wai_tsk(1); 					/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
	}

	InzImageProcessor();	/* LC82103レジスタ初期化 */

#endif

	/* ガンマ補正 */
	SetGammaCorrection(SYS_NORMAL, SYS_NORMAL_DENSITY);

	/* ゲインコントロール */
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();

	/*
	** ＣＳＤＲ Ｎｏ１３０ ＣＣＤ調整モード
	** テストの終了は電源OFF/ONとする。
	*/
	if (CHK_UNI_ShadingTest()) {
		wai_tsk(0xffff);
	}

	SetAgcForRedScan();	/* 朱色用 */

	/* 歪み補正:黒データ作成 */
	LampOff();
	wai_tsk(10);

	SetClamp(ScanClampMode, ScanClampPoint);	/* Set Digital Clamp */	

	Output(SREG_19, ScanSesB4);			/* 補正有効期間スタート(SES) */
	Output(SREG_1A, ScanSelB4);			/* 補正有効期間長(SEL) */
#if defined(HINOKI2)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
	}
	else {	/* LC82103仕様 */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
#endif	/* End of defined(HINOKI2) */
	Work |= (UBYTE)((ScanPesB4 >> 8) & 0x00ff);
	Output(SREG_1B, Work);
	Work = (UBYTE)(ScanPesB4 & 0x00ff);
	Output(SREG_1C, Work);
	Output(SREG_1D, ScanPelB4);			/* 処理有効期間長(PEL) */

	for (Counter = 0; Counter < 5; Counter++) {
		WaitIflgOff();
#if defined(HINOKI2)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
		if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_BLACK_LC33));
			wai_tsk(1);
			Output(SREG_0, IP_PM_BLACK_LC33);
		}
		else {	/* LC82103仕様 */
			Output(SREG_0, (IP_FLG | IP_PM_BLACK));
			wai_tsk(1);
			Output(SREG_0, IP_PM_BLACK);
		}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
		Output(SREG_0, (IP_FLG | IP_PM_BLACK));
		wai_tsk(1);
		Output(SREG_0, IP_PM_BLACK);
#endif	/* End of defined(HINOKI2) */
	}
	WaitIflgOff();
#if defined(HINOKI2)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/27 */
		SYB_BLK_CorrectionDataForRedSCN = Input(SREG_9);	/* 朱色用 */
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	SYB_BLK_CorrectionDataForRedSCN = Input(SREG_9);	/* 朱色用 */
#endif	/* End of defined(HINOKI2) */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	/* 歪み補正:白補正データ作成 */
	LampOn();
	/*
	** 光量安定待ちを１００ｍｓから１ｓに伸ばします
	** 1999/03/15 by T.Soneoka
	*/
	wai_tsk(100);

	for (Counter = 0; Counter < 5; Counter++) {
		WaitIflgOff();
#if defined(HINOKI2)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
		if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
			Output(SREG_0, (IP_FLG_LC33 | IP_PM_WHITE_LC33));
			wai_tsk(1);
			Output(SREG_0, IP_PM_WHITE_LC33);
		}
		else {	/* LC82103仕様 */
			Output(SREG_0, (IP_FLG | IP_PM_WHITE));
			wai_tsk(1);
			Output(SREG_0, IP_PM_WHITE);
		}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
		Output(SREG_0, (IP_FLG | IP_PM_WHITE));
		wai_tsk(1);
		Output(SREG_0, IP_PM_WHITE);
#endif	/* End of defined(HINOKI2) */
	}
	WaitIflgOff();
	
	SrcPtr = &Lc82103Ram[0];
	DestPtr = &SYB_ShadingRAM_ForRedScan[0];	/* 朱色用 */

	Wcr1Stat = SH__WCR1; 
	SH__WCR1 = SH__WCR1_DATA_FOR_IMAGE_LSI;
#if defined(HINOKI2)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_A, (IP_RSTB_LC33 | (LC821033_IniSreg[0x0a] & IP_TH_LC33)));
		WaitScanLineInt();
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		Output(SREG_A, (IP_RSTB_LC33 | (LC821033_IniSreg[0x0a] & IP_TH_LC33)));
	}
	else {	/* LC82103仕様 */
		Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
		WaitScanLineInt();
		for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
			*DestPtr++ = *SrcPtr++;
		}
		Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_A, (IP_RSTB | IP_SDSEL | (IniSreg[0x0a] & IP_TH)));
	WaitScanLineInt();
	for (Counter = SYS_SHADING_MAX; Counter > 0; Counter--) {
		*DestPtr++ = *SrcPtr++;
	}
	Output(SREG_A, (IP_RSTB | (IniSreg[0x0a] & IP_TH)));
#endif	/* End of defined(HINOKI2) */

	SH__WCR1 = Wcr1Stat;

	SYS_IsRedShading = FALSE;	/* 2002/03/23 T.Takagi */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
	SYS_MakingShadingData = FALSE;		/* シェーディングデータ作成終了 */
#endif

	EnableScannerInt = CurrentScanInt;
}
#endif	/* End of defined(HINOKI3) */

void	SetAgcForRedScan(void)
{
	UBYTE	Work;
	UBYTE	Maxd;
	UBYTE	Mind;
	BOOL	CurrentScanInt;
	UBYTE	MaxdSmpl[10];
	UBYTE	MindSmpl[10];
	int	Index;
	
	CurrentScanInt = EnableScannerInt;
	EnableScannerInt = FALSE;
	
	/* 1)初期設定 */
	SetClamp(AgcClampMode, AgcClampPoint);/* Set Digital Clamp */

	Output(SREG_13, IP_DAHA_MAX);		/* センサ信号期間 A/D ハイリファレンス用 D/A 値(DAHA) 最大値 */
	Output(SREG_14, IP_DAHT_MAX);		/* 温度信号期間 A/D ハイリファレンス用 D/A 値(DAHT) 最大値 */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/28 */
		Output(SREG_11, IP_DALA_MIN);		/* センサ信号期間 A/D ローレファレンス用 D/A 値(DALA) 最小値 */
		Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_11, IP_DALA_MIN);		/* センサ信号期間 A/D ローレファレンス用 D/A 値(DALA) 最小値 */
	Output(SREG_12, IP_DALT_MIN);		/* 温度信号期間 A/D ローリファレンス用 D/A 値(DALT) 最小値 */
#endif	/* End of defined(HINOKI2) */

	Output(SREG_19, AgcSes);			/* 補正有効期間スタート(SES) */
	Output(SREG_1A, AgcSel);			/* 補正有効期間長(SEL) */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		Work = (Input(SREG_1B) & ~IP_PES_H_LC33); /* 処理有効期間スタート(PES) */
	}
	else {	/* LC82103仕様 */
		Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Work = (Input(SREG_1B) & ~IP_PES_H); /* 処理有効期間スタート(PES) */
#endif	/* End of defined(HINOKI2) */

	Work |= (UBYTE)((AgcPes >> 8) & 0x00ff);
	Output(SREG_1B, Work);
	Work = (UBYTE)(AgcPes & 0x00ff);
	Output(SREG_1C, Work);
	Output(SREG_1D, AgcPel);			/* 処理有効期間長(PEL) */

	/* 2)白基準読込み */
	WaitIflgOff();
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		Output(SREG_0, IP_PM_2CHI_LC33);
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, IP_PM_2CHI);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, IP_PM_2CHI);
#endif	/* End of defined(HINOKI2) */

	/* MIND 作成 */
	LampOff();
	wai_tsk(5);						/* 光量安定待ち */
	for (Index = 0; Index < 10; Index++) {
		/* 3)１ライン以上のウェイト */
		wai_tsk(1);
		
		/* 4)レジスタ読取り */
		MindSmpl[Index] = Input(SREG_8);
	}
	Mind = CalcCenterAverage(MindSmpl);

	/* MAXD 作成 */

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
	PC_24V_On();
#endif
	LampOn();

	/*
	** 光量安定待ちを５０ｍｓから１ｓに伸ばします
	** 1999/03/15 by T.Soneoka
	*/
	wai_tsk(100);						/* 光量安定待ち */

	for (Index = 0; Index < 10; Index++) {
		/* 3)１ライン以上のウェイト */
		wai_tsk(1);
		
		/* 4)レジスタ読取り */
		MaxdSmpl[Index] = Input(SREG_7);
	}
	Maxd = CalcCenterAverage(MaxdSmpl);

	/* 5)AGC 設定値演算 */
	/* 6)レジスタ設定 */
	/* Work = (64 * (InMax - DAHRL))/(DAHRH - DAHRL); */
	/*
	 *	8bit A/D のHight Reference が 4.2v, Low Reference が 0.8v
	 *	6bit D/A のHight Reference が 5.0v, Low Reference が 0.0v
	 *	(((4.2v-0.8v)/256) * maxd +0.8v)/((5v-0v)/64) = 0.17
	 *	Offset 0x0b,0x0a は、
	 *	6bit D/A (Hight Reference:5.0v, Low Reference:0.0v)で、
	 *	0.8v を出力するために設定
	 */
	SYB_AgcDaHighReferenceForRedSCN = (UBYTE)((((UWORD)Maxd * 17) / 100) + 0x0b);	/* 朱色用 */
	SYB_AgcDaHighReferenceForRedSCN -= 3;
	SYB_AgcDaHighReferenceForRedSCN += CHK_AgcHighRefOffsetForRedScan(); /* 朱色用のマシンパラメータから持ってくる 2002/03/23 T.Takagi */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/28 */
		Work = SYB_AgcDaHighReferenceForRedSCN & 0x3f;
		Output(SREG_13, Work);
	}
	else {	/* LC82103仕様 */
		Output(SREG_13, SYB_AgcDaHighReferenceForRedSCN);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_13, SYB_AgcDaHighReferenceForRedSCN);
#endif	/* End of defined(HINOKI2) */

	SYB_AgcDaLowReferenceForRedSCN  = (UBYTE)((((UWORD)Mind * 17) / 100) + 0x0a);

	/*
	** ＤＡＬＡオフセット＋１ 並川からの依頼 
	** 1999/02/08 by T.Soneoka 
	*/
	SYB_AgcDaLowReferenceForRedSCN += 1;

	SYB_AgcDaLowReferenceForRedSCN  += CHK_QueryAgcLowRefOffset();
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
	if (!SYB_LC821033_Flg) {					/* LC821033対応フラグがOFF Y.Kano 2003/11/28 */
		Output(SREG_11, SYB_AgcDaLowReferenceForRedSCN);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_11, SYB_AgcDaLowReferenceForRedSCN);
#endif	/* End of defined(HINOKI2) */

	/* Restore Interrupt */
	EnableScannerInt = CurrentScanInt;
}

/* 画処理LSI初期化 朱色読み取りの各ページ前処理でコール 2002/03/29 T.Takagi */
void	InzImageProcessorForRedScan(void)
{
	UBYTE	MaskAdj;
	UBYTE	Work;

  #if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		Output(SREG_0, LC821033_IniSreg[0]);
		Output(SREG_1, LC821033_IniSreg[1]);
		Output(SREG_2, LC821033_IniSreg[2]);
		Output(SREG_3, LC821033_IniSreg[3]);
		Output(SREG_4, LC821033_IniSreg[4]);
		Output(SREG_5, LC821033_IniSreg[5]);
		Output(SREG_6, LC821033_IniSreg[6]);
		Output(SREG_7, LC821033_IniSreg[7]);
		Output(SREG_8, LC821033_IniSreg[8]);
		Output(SREG_9, LC821033_IniSreg[9]);
		Output(SREG_A, LC821033_IniSreg[0x0a]);
		if (CHK_SP_Test()) {
			Work = LC821033_IniSreg[0x0b];
			Work &= ~IP_SP_LC33;
			Work |= CHK_SP_Test();
			Output(SREG_B, Work);
		} else {
			Output(SREG_B, LC821033_IniSreg[0x0b]);
		}
		Output(SREG_C, LC821033_IniSreg[0x0c]);
		Output(SREG_D, LC821033_IniSreg[0x0d]);
		Output(SREG_E, LC821033_IniSreg[0x0e]);
		Output(SREG_F, LC821033_IniSreg[0x0f]);
		Output(SREG_10, LC821033_IniSreg[0x10]);
		Output(SREG_11, LC821033_IniSreg[0x11]);
		Output(SREG_12, LC821033_IniSreg[0x12]);
    #if defined(HINOKI3)		/* 朱色読み取りなので、朱色用の変数に置き換えます。by Y.Kano 2005/01/24 */
		Work = SYB_AgcDaHighReferenceForRedSCN & 0x3f;
    #else
		Work = SYB_AgcDaHighReference & 0x3f;
    #endif
		Output(SREG_13, Work);
		Output(SREG_14, LC821033_IniSreg[0x14]);
		Output(SREG_15, LC821033_IniSreg[0x15]);
		Output(SREG_18, LC821033_IniSreg[0x18]);
		Output(SREG_19, LC821033_IniSreg[0x19]);
		Output(SREG_1A, LC821033_IniSreg[0x1a]);
		Work = (LC821033_IniSreg[0x1b] & ~IP_PES_H_LC33);
		Work >>= 3;
		/*
		** 原稿読取り幅1部/全部の処理を追加します
		** 1999/02/03 by T.Soneoka
		*/
		if (CHK_DocumentWidthFull()) {
			Work = 0;
		} else {
			MaskAdj = CHK_QueryScanMaskAdjust();
			if (MaskAdj & 0x80) {
				Work += (MaskAdj & 0x1f);
				if (Work > 0x1f) {
					Work = 0x1f;
				}
			} else {
				if (Work > (MaskAdj & 0x1f)) {
					Work -= (MaskAdj & 0x1f);
				} else {
					Work = 0;
				}
			}
		}
		Work <<= 3;
		Work |= (LC821033_IniSreg[0x1b] & IP_PES_H_LC33);
		Output(SREG_1B, Work);

		Output(SREG_1C, LC821033_IniSreg[0x1c]);
		Output(SREG_1D, LC821033_IniSreg[0x1d]);
	}
	else {	/* LC82103仕様 */
		Output(SREG_0, IniSreg[0]);
		Output(SREG_1, IniSreg[1]);
		Output(SREG_2, IniSreg[2]);
		Output(SREG_3, IniSreg[3]);
		Output(SREG_4, IniSreg[4]);
		Output(SREG_5, IniSreg[5]);
		Output(SREG_6, IniSreg[6]);
		Output(SREG_7, IniSreg[7]);
		Output(SREG_8, IniSreg[8]);
		Output(SREG_9, SYB_BLK_CorrectionDataForRedSCN);
		Output(SREG_A, IniSreg[0x0a]);
		if (CHK_SP_Test()) {
			Work = IniSreg[0x0b];
			Work &= ~IP_SP;
			Work |= CHK_SP_Test();
			Output(SREG_B, Work);
		} else {
			Output(SREG_B, IniSreg[0x0b]);
		}
		Output(SREG_C, IniSreg[0x0c]);
		Output(SREG_D, IniSreg[0x0d]);
		Output(SREG_E, IniSreg[0x0e]);
		Output(SREG_F, IniSreg[0x0f]);
		Output(SREG_10, IniSreg[0x10]);
		Output(SREG_11, SYB_AgcDaLowReferenceForRedSCN);
		Output(SREG_12, IniSreg[0x12]);
		Output(SREG_13, SYB_AgcDaHighReferenceForRedSCN);
		Output(SREG_14, IniSreg[0x14]);
		Output(SREG_15, IniSreg[0x15]);
		/* Output(SREG_16, IniSreg[0x16]); */		/* Port として使用のためパワーオンでのみ初期化 */
		/* Output(SREG_17, IniSreg[0x17]); */		/* Port として使用のためパワーオンでのみ初期化 */
		Output(SREG_18, IniSreg[0x18]);
		Output(SREG_19, IniSreg[0x19]);
		Output(SREG_1A, IniSreg[0x1a]);
		Work = (IniSreg[0x1b] & ~IP_PES_H);
		Work >>= 3;
		/*
		** 原稿読取り幅1部/全部の処理を追加します
		** 1999/02/03 by T.Soneoka
		*/
		if (CHK_DocumentWidthFull()) {
			Work = 0;
		} else {
			MaskAdj = CHK_QueryScanMaskAdjust();
			if (MaskAdj & 0x80) {
				Work += (MaskAdj & 0x1f);
				if (Work > 0x1f) {
					Work = 0x1f;
				}
			} else {
				if (Work > (MaskAdj & 0x1f)) {
					Work -= (MaskAdj & 0x1f);
				} else {
					Work = 0;
				}
			}
		}
		Work <<= 3;
		Work |= (IniSreg[0x1b] & IP_PES_H);
		Output(SREG_1B, Work);

		Output(SREG_1C, IniSreg[0x1c]);
		Output(SREG_1D, IniSreg[0x1d]);
	}
  #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	Output(SREG_0, IniSreg[0]);
	Output(SREG_1, IniSreg[1]);
	Output(SREG_2, IniSreg[2]);
	Output(SREG_3, IniSreg[3]);
	Output(SREG_4, IniSreg[4]);
	Output(SREG_5, IniSreg[5]);
	Output(SREG_6, IniSreg[6]);
	Output(SREG_7, IniSreg[7]);
	Output(SREG_8, IniSreg[8]);
	Output(SREG_9, SYB_BLK_CorrectionDataForRedSCN);
	Output(SREG_A, IniSreg[0x0a]);
	if (CHK_SP_Test()) {
		Work = IniSreg[0x0b];
		Work &= ~IP_SP;
		Work |= CHK_SP_Test();
		Output(SREG_B, Work);
	} else {
		Output(SREG_B, IniSreg[0x0b]);
	}
	Output(SREG_C, IniSreg[0x0c]);
	Output(SREG_D, IniSreg[0x0d]);
	Output(SREG_E, IniSreg[0x0e]);
	Output(SREG_F, IniSreg[0x0f]);
	Output(SREG_10, IniSreg[0x10]);
	Output(SREG_11, SYB_AgcDaLowReferenceForRedSCN);
	Output(SREG_12, IniSreg[0x12]);
	Output(SREG_13, SYB_AgcDaHighReferenceForRedSCN);
	Output(SREG_14, IniSreg[0x14]);
	Output(SREG_15, IniSreg[0x15]);
	/* Output(SREG_16, IniSreg[0x16]); */		/* Port として使用のためパワーオンでのみ初期化 */
	/* Output(SREG_17, IniSreg[0x17]); */		/* Port として使用のためパワーオンでのみ初期化 */
	Output(SREG_18, IniSreg[0x18]);
	Output(SREG_19, IniSreg[0x19]);
	Output(SREG_1A, IniSreg[0x1a]);
	Work = (IniSreg[0x1b] & ~IP_PES_H);
	Work >>= 3;
	/*
	** 原稿読取り幅1部/全部の処理を追加します
	** 1999/02/03 by T.Soneoka
	*/
	if (CHK_DocumentWidthFull()) {
		Work = 0;
	} else {
		MaskAdj = CHK_QueryScanMaskAdjust();
		if (MaskAdj & 0x80) {
			Work += (MaskAdj & 0x1f);
			if (Work > 0x1f) {
				Work = 0x1f;
			}
		} else {
			if (Work > (MaskAdj & 0x1f)) {
				Work -= (MaskAdj & 0x1f);
			} else {
				Work = 0;
			}
		}
	}
	Work <<= 3;
	Work |= (IniSreg[0x1b] & IP_PES_H);
	Output(SREG_1B, Work);

	Output(SREG_1C, IniSreg[0x1c]);
	Output(SREG_1D, IniSreg[0x1d]);
  #endif	/* End of defined(HINOKI2) */
}

#endif	/* end of RED_SCAN */
