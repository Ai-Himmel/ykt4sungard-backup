/*
**	%W%
**	File Name:	\prj\Eva\src\inc\cmnuni_e.h
**	Create:	1998/01/05	by Masahiro,IIDA
**	Description:
**		機種固有スイッチEの設定状態を獲得する関数
**		随時追加していってください 1998/09/30 by T.Soneoka
**	Changes:
**
*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
#include "\src\atlanta\ext_v\sys_data.h"
#endif

/* プリンタ関係マシンパラメータ */
UBYTE	CHK_PrinterTopMergin(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_B5]);
}
UBYTE	CHK_PrinterMask(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_B6]);
}

UBYTE	CHK_PrinterBottomMergin(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_B8]);
}
UBYTE	CHK_PrinterMaskWhite(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_B9]);
}


/*
 *	二値で強調フィルタを使う？
 *	戻り値	LC821033仕様	二値強調フィルタ
 			LC82103仕様		TRUE:	強調フィルタを使う
 *							FALSE:	使わない
 */
BOOL	CHK_2ChiEmphasizeFilter(void)
{
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		return ((UBYTE)(SYB_MachineParameter[M_PARA_SW_F7] & NICHI_EMPASIZE_FILTER));
	}
	else {	/* LC82103仕様 */
		return	(SYB_MachineParameter[M_PARA_SW_F0] & BIN_EMPASIZE_FILTER) ? TRUE : FALSE;
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	return	(SYB_MachineParameter[M_PARA_SW_F0] & BIN_EMPASIZE_FILTER) ? TRUE : FALSE;
#endif	/* End of defined(HINOKI2) */
}
/*
 *	中間調で強調フィルタを使う？
 *	戻り値	LC821033仕様	中間調強調フィルタ
 			LC82103仕様		TRUE:	強調フィルタを使う
 *							FALSE:	使わない
 */
BOOL	CHK_GrayEmphasizeFilter(void)
{
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		return ((UBYTE)(SYB_MachineParameter[M_PARA_SW_F7] & GRAY_EMPASIZE_FILTER_DATA) >> 4);
	}
	else {	/* LC82103仕様 */
		return	(SYB_MachineParameter[M_PARA_SW_F0] & GRAY_EMPASIZE_FILTER) ? TRUE : FALSE;
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	return	(SYB_MachineParameter[M_PARA_SW_F0] & GRAY_EMPASIZE_FILTER) ? TRUE : FALSE;
#endif	/* End of defined(HINOKI2) */
}

/*
 *	誤差拡散モード
 *	戻り値	TRUE:	移動マトリックス
 *			FALSE:	固定マトリックス
 */
BOOL	CHK_GosaMoveMatrix(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F0] & GOSA_MOVE_MATRIX) ? TRUE : FALSE;
}

/*
 *	中間調重みマトリックス
 *	戻り値	0-7 中間調処理における重みマトリックスによる重み付け値
 */
UBYTE	CHK_WeightValue(void)
{
	return	((SYB_MachineParameter[M_PARA_SW_F0] & WEIGHT_VALUE) >> 3);
}

/*
 *	像域分離するか/しないか
 *	戻り値	TURE:	像域分離する
 *			FALSE:	像域分離しない
 */
BOOL	CHK_ZouikiBunri(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F1] & ZOUIKIBUNRI) ? TRUE : FALSE;
}

/*
 *	像域分離の方式
 *	戻り値　TURE:	セレクタ方式
 *			FALSE:	フィルタ方式
 *	像域分離処理には、フィルタ制御とセレクタ制御があり、
 *	フィルタ制御では、二値化処理モードは中間調処理で行い、
 *	フィルタの強調度を文字領域は単純二値化処理の強調度を使用し、
 *	写真領域では中間調処理用の強調度または、平滑を使用して処理を行う。
 *	セレクタ制御では、文字領域では単純二値化処理を、
 *	それ以外の領域では中間調処理を行う。
 */
BOOL	CHK_ZouikiSelector(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F1] & ZOUIKI_SELECTOR) ? TRUE : FALSE;
}

/*
 *	文字領域判定領域設定
 *	戻り値:	TURE	拡張サイズ
 *			FALSE:	標準サイズ
 */
BOOL	CHK_CharAreaWindowExtend(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F1] & CHAR_AREA_WIND_EXT) ? TRUE : FALSE;
}
 

/*
 *	網点検出処理
 *	戻り値:	TURE:	網点検出オン
 *			FALSE:	網点検出オフ
 */
BOOL	CHK_AmitenDetect(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F1] & AMITEN_DETECT) ? TRUE : FALSE;
}

/*
 *	中間調処理用フィルター選択
 *	戻り値:	TURE:	平滑フィルタ
 *			FALSE:	強調フィルタ
 */
BOOL	CHK_HalfToneSwitch(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F1] & HALFTONE_MODE_SWITCH) ? TRUE : FALSE;
}


/*
 *	多値解像度変換処理 X 方向強調フィルタ
 *	戻り値 IP_MFMX_* (see lc82103.h)
 */
UBYTE	CHK_PreFilter(void)
{
	UBYTE	rtn;

	switch (SYB_MachineParameter[M_PARA_SW_F2] & PRE_FILTER) {
	case 1:
		rtn = IP_MFMX_X1;
		break;
	case 2:
		rtn = IP_MFMX_X2;
		break;
	case 3:
		rtn = IP_MFMX_X4;
		break;
	case 0:
	default:
		rtn = IP_MFMX_NON;
		break;
	}
	return	rtn;
}

/*
 *	主操作方向多値解像度変換
 *	戻り値 IP_RES_* (see lc82103.h)
 */
UBYTE	CHK_Transform(void)
{
	UBYTE	rtn;

	switch ((SYB_MachineParameter[M_PARA_SW_F2] & TRANSFORM) >> 2) {
	case 1:
		rtn = IP_RES_1_2;
		break;
	case 2:
		rtn = IP_RES_2_3;
		break;
	case 3:
		rtn = IP_RES_3_2;
		break;
	case 4:
		rtn = IP_RES_2_1;
		break;
	case 0:
	default:
		rtn = IP_RES_NON;
		break;
	}
	return(rtn);
}

/*
 *	主走査方向縮小方法
 *	戻り値:	IP_RM_* (see lc82103.h)
 */
UBYTE	CHK_HReductionMethod(void)
{
	return	((SYB_MachineParameter[M_PARA_SW_F2] & H_REDUCTION_METHOD) >> 5);
}

/*
 *	副走査方向縮小方法
 *	戻り値:	TRUE:	単純間引き
 *			FALSE:	細線保持
 */
BOOL	CHK_VReductionMethod(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F2] & V_REDUCTION_METHOD) ? TRUE : FALSE;
}
	
/*
 *	中間調処理用Ｙ方向強調フィルタ
 *	戻り値 IP_HFMY_* (see lc82103.h)
 */
UBYTE	CHK_Hfmy(void)
{
	UBYTE	rtn;

	switch (SYB_MachineParameter[M_PARA_SW_F3] & HFMY_MASK) {
	case 1:
		rtn = IP_HFMY_X1;
		break;
	case 2:
		rtn = IP_HFMY_X2;
		break;
	case 3:
		rtn = IP_HFMY_X4;
		break;
	case 0:
	default:
		rtn = IP_HFMY_NON;
		break;
	}
	return	rtn;
}
/*
 *	中間調処理用Ｘ方向強調フィルタ
 *	戻り値 IP_HFMX_* (see lc82103.h)
 */
UBYTE	CHK_Hfmx(void)
{
	UBYTE	rtn;

	switch ((SYB_MachineParameter[M_PARA_SW_F3] & HFMX_MASK) >> 2) {
	case 1:
		rtn = IP_HFMX_X1;
		break;
	case 2:
		rtn = IP_HFMX_X2;
		break;
	case 3:
		rtn = IP_HFMX_X4;
		break;
	case 0:
	default:
		rtn = IP_HFMX_NON;
		break;
	}
	return	rtn;
}

/*
 *	単純二値化用Ｙ方向強調フィルタ
 *	戻り値 IP_BFMY_* (see lc82103.h)
 */
UBYTE	CHK_Bfmy(void)
{
	UBYTE	rtn;

	switch ((SYB_MachineParameter[M_PARA_SW_F3] & BFMY_MASK) >> 4) {
	case 1:
		rtn = IP_BFMY_X1;
		break;
	case 2:
		rtn = IP_BFMY_X2;
		break;
	case 3:
		rtn = IP_BFMY_X4;
		break;
	case 0:
	default:
		rtn = IP_BFMY_NON;
		break;
	}
	return	rtn;
}
/*
 *	単純二値化用Ｘ方向強調フィルタ
 *	戻り値 IP_BFMX_* (see lc82103.h)
 */
UBYTE	CHK_Bfmx(void)
{
	UBYTE	rtn;

	switch ((SYB_MachineParameter[M_PARA_SW_F3] & BFMX_MASK) >> 6) {
	case 1:
		rtn = IP_BFMX_X1;
		break;
	case 2:
		rtn = IP_BFMX_X2;
		break;
	case 3:
		rtn = IP_BFMX_X4;
		break;
	case 0:
	default:
		rtn = IP_BFMX_NON;
		break;
	}
	return	rtn;
}

/*
 *	エッジ検出レベル（像域分離パラメータ/文字領域用濃度差設定）
 */
UBYTE	CHK_EdgeDetectLevel(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F4] & EDGE_DETECT_LEVEL);
}

/*
 *	網点スライスレベル(網点領域用濃度差設定）
 */
UBYTE	CHK_AmitenThresholdLevel(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F5] & AMI_THRESHOLD);
}

/*
 *	網点領域用エッジペア判定値
 */
UBYTE	CHK_AmitenEdgePare(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F6] & AMI_EDGE_PARE);
}

/*
 *	二値化処理方法
 *	戻り値:	TRUE:	周辺濃度適応閾値
 *			FALSE:	固定閾値
 */
BOOL	CHK_BinaryThresholdMethod(void)
{
	return	(SYB_MachineParameter[M_PARA_SW_F8] & BIN_THRESHOLD_METHOD) ? TRUE : FALSE;
}
	
/*
 *	Name:	Query Gamma Value
 *	Create:	Thu Jul 02 12:45:59 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		UBYTE	QueryGammaValue(BOOL Gray, UBYTE Point);
 *	Description:
 *		ガンマ補正テーブルの値を返す
 *	Return Value:
 *		UBYTE
 *	Change Log:
 *		
 */
UBYTE	CHK_QueryGammaValue(
	BOOL	Gray,						/* Gray Scale or not */
	UBYTE	Density,					/* 濃度設定  1998/07/20 by T.Soneoka */
	UBYTE	Point)						/* 00h-ffh */
{
	UBYTE	Value;

/*
** ガンマ曲線テストモード指定方法変更
** ２値と中間調で別々で設定できるように変更する  RDC-D86-001 項目2.
** 1999/06/29 by T.Soneoka
*/
#if (0)
**	if(SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST){	/* ガンマ補正データをマシンパラメータから取得する場合 */
**		Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
**	}
**	else {
**		if (Gray) {
**			switch (Density) {
**			case SYS_LIGHT_DENSITY:
**				Value = GrayGammaValue[0][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H3], 4)][Point];
**				break;
**			case SYS_NORMAL_DENSITY:
**				Value = GrayGammaValue[1][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H4], 4)][Point];
**				break;
**			case SYS_DARK_DENSITY:
**				Value = GrayGammaValue[2][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H5], 4)][Point];
**				break;
**			}
**		}
**		else {
**			Value = BinGammaValue[Point];
**		}
**	}
#else
	if (Gray) {
		if (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST_GRAY) {	/* ガンマ補正データをマシンパラメータから取得する場合 */
			Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
		}
		else {
			switch (Density) {
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/01/21 */
			case SYS_LIGHT_DENSITY:
				if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
					Value = LC821033_GrayGammaValue[0][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H3], 4)][Point];
				}
				else {	/* LC82103仕様 */
					Value = GrayGammaValue[0][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H3], 4)][Point];
				}
				break;
			case SYS_NORMAL_DENSITY:
				if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
					Value = LC821033_GrayGammaValue[1][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H4], 4)][Point];
				}
				else {	/* LC82103仕様 */
					Value = GrayGammaValue[1][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H4], 4)][Point];
				}
				break;
			case SYS_DARK_DENSITY:
				if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
					Value = LC821033_GrayGammaValue[2][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H5], 4)][Point];
				}
				else {	/* LC82103仕様 */
					Value = GrayGammaValue[2][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H5], 4)][Point];
				}
				break;
 #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
			case SYS_LIGHT_DENSITY:
				Value = GrayGammaValue[0][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H3], 4)][Point];
				break;
			case SYS_NORMAL_DENSITY:
				Value = GrayGammaValue[1][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H4], 4)][Point];
				break;
			case SYS_DARK_DENSITY:
				Value = GrayGammaValue[2][QueryCalPos(SYB_MachineParameter[M_PARA_SW_H5], 4)][Point];
				break;
 #endif	/* End of defined(HINOKI2) */
			}
		}
	} else {
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
		if (CHK_UNI_RedScanModeEnable()) {	/* 朱色読み取りのユニークスイッチがたっていて */
			if (SYS_IsRedShading == TRUE) {	/* 朱色読み取りの時はＧを見る 2002/03/23 T.Takagi */
				if (SYB_MachineParameter[M_PARA_SW_G2] & GAMMA_DATA_TEST_FOR_RED_SCAN) {	/* ガンマ補正データをマシンパラメータから取得する場合 */
					Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
				}
				else {
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/04/02 */
					if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
  #if defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2005/01/11 */
						if (CHK_CarBinGammaValue()) {
							if (Density == SYS_LIGHT_DENSITY) {
								Value = CarBinGammaValue[Point];
							}
							else {
   #if (1)	/* 朱色読取り用２値ガンマ補正テーブルを参照する。by Y.Kano 2005/01/24 */
								Value = LC821033_BinGammaValue_ForRedScan[Point];
   #else
								Value = LC821033_BinGammaValue[Point];
   #endif
							}
						}
						else {
   #if (1)	/* 朱色読取り用２値ガンマ補正テーブルを参照する。by Y.Kano 2005/01/24 */
							Value = LC821033_BinGammaValue_ForRedScan[Point];
   #else
							Value = LC821033_BinGammaValue[Point];
   #endif
						}
					}
					else {	/* LC82103仕様 */
						Value = BinGammaValue[Point];
					}
  #else
						Value = LC821033_BinGammaValue[Point];
					}
					else {	/* LC82103仕様 */
						Value = BinGammaValue[Point];
					}
  #endif	/* End of defined(HINOKI3) */
 #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
					Value = BinGammaValue[Point];
 #endif	/* End of defined(HINOKI2) || defined(HINOKI3) */
				}
			}
			else {
				if (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST) {	/* ガンマ補正データをマシンパラメータから取得する場合 */
					Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
				}
				else {
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/04/02 */
					if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
  #if defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2005/01/11 */
						if (CHK_CarBinGammaValue()) {
							if (Density == SYS_LIGHT_DENSITY) {
								Value = CarBinGammaValue[Point];
							}
							else {
								Value = LC821033_BinGammaValue[Point];
							}
						}
						else {
							Value = LC821033_BinGammaValue[Point];
						}
					}
					else {	/* LC82103仕様 */
						Value = BinGammaValue[Point];
					}
  #else
						Value = LC821033_BinGammaValue[Point];
					}
					else {	/* LC82103仕様 */
						Value = BinGammaValue[Point];
					}
  #endif	/* End of defined(HINOKI3) */
 #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
					Value = BinGammaValue[Point];
 #endif	/* End of defined(HINOKI2) || defined(HINOKI3) */
				}
			}
		}
		else {
			if (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST) {	/* ガンマ補正データをマシンパラメータから取得する場合 */
				Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
			}
			else {
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/04/02 */
				if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
  #if defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2005/01/11 */
					if (CHK_CarBinGammaValue()) {
						if (Density == SYS_LIGHT_DENSITY) {
							Value = CarBinGammaValue[Point];
						}
						else {
							Value = LC821033_BinGammaValue[Point];
						}
					}
					else {
						Value = LC821033_BinGammaValue[Point];
					}
				}
				else {	/* LC82103仕様 */
					Value = BinGammaValue[Point];
				}
  #else
					Value = LC821033_BinGammaValue[Point];
				}
				else {	/* LC82103仕様 */
					Value = BinGammaValue[Point];
				}
  #endif	/* End of defined(HINOKI3) */
 #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
				Value = BinGammaValue[Point];
 #endif	/* End of defined(HINOKI2) || defined(HINOKI3) */
			}
		}
 #else
		if (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_TEST) {	/* ガンマ補正データをマシンパラメータから取得する場合 */
			Value = SYB_MachineParameter[M_PARA_SW_D0 + Point];	/* Ｄ：０～Ｅ：６ */
		}
		else {
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/04/02 */
			if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
  #if defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2005/01/11 */
				if (CHK_CarBinGammaValue()) {
					if (Density == SYS_LIGHT_DENSITY) {
						Value = CarBinGammaValue[Point];
					}
					else {
						Value = LC821033_BinGammaValue[Point];
					}
				}
				else {
					Value = LC821033_BinGammaValue[Point];
				}
			}
			else {	/* LC82103仕様 */
				Value = BinGammaValue[Point];
			}
  #else
				Value = LC821033_BinGammaValue[Point];
			}
			else {	/* LC82103仕様 */
				Value = BinGammaValue[Point];
			}
  #endif	/* End of defined(HINOKI3) */
 #else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
			Value = BinGammaValue[Point];
 #endif	/* End of defined(HINOKI2) || defined(HINOKI3) */
		}
 #endif
	}
#endif

	return	Value;
}

/*
 *	Name:	Query Scanner AGC High Refference Offset
 *	Create:	Thu Jul 02 14:18:01 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		BYTE	QueryAgcHighRefOffset(void);
 *	Description:
 *		スキャナ AGC D/A の High Refference に対するオフセット値
 *	Return Value:
 *		BYTE
 *	Change Log:
 *		
 */
BYTE	CHK_QueryAgcHighRefOffset(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_C1] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_C1] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_C1] & 0x7F);
	}
	return	Rslt;
}

/*
 *	Name:	Query Scanner AGC Low Refference Offset
 *	Create:	Thu Jul 02 14:18:01 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		BYTE	QueryAgcLowRefOffset(void);
 *	Description:
 *		スキャナ AGC D/A の Low Refference に対するオフセット値
 *	Return Value:
 *		BYTE
 *	Change Log:
 *		
 */
BYTE	CHK_QueryAgcLowRefOffset(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_C0] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_C0] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_C0] & 0x7F);
	}
	return	Rslt;
}


/*
 *	Name:	Scan Top Adjust
 *	Create:	Wed Jun 17 19:38:39 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		UBYTE	QueryScanTopAdjust(void);
 *	Description:
 *		先端読取り位置の微調整値
 *	Return Value:
 *		UBYTE
 *	Change Log:
 *		
 */
#if (0) /* 1999/02/23 by T.Soneoka */
**WORD	CHK_QueryScanTopAdjust(void)
**{
**	WORD	Margin;
**	
**	Margin = 0;
**	Margin += (WORD)(SYB_MachineParameter[M_PARA_SW_A3] - 0x80);
**	
**	return	Margin;
**}
#else
WORD	CHK_QueryScanTopAdjust(void)
{
	return	((WORD)SYB_MachineParameter[M_PARA_SW_A3]);
}
#endif

/*
 *	Name:	Scan End Adjust
 *	Create:	Wed Jun 17 19:40:53 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		UBYTE	QueryScanEndAdjust(void);
 *	Description:
 *		後端読取り終了位置微調整
 *	Return Value:
 *		UBYTE
 *	Change Log:
 *		
 */
#if (0) /* 1999/02/23 by T.Soneoka */
**WORD	CHK_QueryScanEndAdjust(void)
**{
**
**	WORD	Margin;
**	
**	Margin = 0;
**	Margin += (WORD)(SYB_MachineParameter[M_PARA_SW_A4] - 0x80);
**	
**	return	Margin;
**}
#else
WORD	CHK_QueryScanEndAdjust(void)
{
	return  (WORD)(SYB_MachineParameter[M_PARA_SW_A4]);
}
#endif
/*
 *	Name:	Query Scan Mask width Adjust
 *	Create:	Fri Jun 19 20:32:33 1998	by	ishiyama
 *	Synopsis:
 *		#include	"m_param.h"
 *		UBYTE	QueryScanMaskAdjust(void);
 *	Description:
 *		読取り両端白マスク幅微調整値
 *	Return Value:
 *		UBYTE
 *	Change Log:
 *		
 */
UBYTE	CHK_QueryScanMaskAdjust(void)
{
	return	SYB_MachineParameter[M_PARA_SW_B2];
}


/*
 *	Ａ／Ｄサンプリングポイント調整
 */
UBYTE	CHK_SP_Test(void)
{
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
	if (SYB_LC821033_Flg) {					/* LC821033対応フラグ Y.Kano 2003/11/27 */
		if (SYB_MachineParameter[M_PARA_SW_C5] & SP_FLAG) {
			return	(SYB_MachineParameter[M_PARA_SW_C5] & SP_TEST_LC33);
		}
		else {
			return	(0);
		}
	}
	else {	/* LC82103仕様 */
		return	(SYB_MachineParameter[M_PARA_SW_C5] & SP_TEST);
	}
#else	/* HINOKI2旧ﾊﾞｰｼﾞｮﾝ */
	return	(SYB_MachineParameter[M_PARA_SW_C5] & SP_TEST);
#endif	/* End of defined(HINOKI2) */
}

/*
** ガンマ補正データ ソフト補完データ調整
** 1999/06/29 by T.Soneoka
*/
BYTE	CHK_GammaShift(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_C9] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_C9] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_C9] & 0x7F);
	}
	return	Rslt;
}


/*
** 特殊ガンマ曲線
** アドレス０ｘ００～０ｘ９ｆ：００
** アドレス０ｘＡ０～０ｘｆｆ：ＦＦ
** 1999/06/29 by T.Soneoka
*/
UBYTE	CHK_QueryGammaDataSpecial(void)
{
	return (SYB_MachineParameter[M_PARA_SW_C2] & GAMMA_DATA_SPECIAL);	/* コンパイルエラーがわざとでるようにしています */
}

/*
** Ｎｏｒｍａｌ送信時のスライスレベル補正
** 1999/06/29 by T.Soneoka
*/
BYTE	CHK_SliceLevelForNormTx(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_C8] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_C8] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_C8] & 0x7F);
	}
	return	Rslt;
}

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/23 T.Takagi */
/*	朱色読み取り時 スキャナ AGC D/A の High Refference に対するオフセット値 */
BYTE	CHK_AgcHighRefOffsetForRedScan(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_G1] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_G1] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_G1] & 0x7F);
	}
	return	Rslt;
}

/*
 *	単純二値化用Ｙ方向強調フィルタ
 *	戻り値 IP_BFMY_* (see lc82103.h)
 */
UBYTE	CHK_BfmyForRedScan(void)
{
	UBYTE	rtn;

	switch (SYB_MachineParameter[M_PARA_SW_G3] & BFMY_MASK_FOR_RED_SCAN) {
	case 1:
		rtn = IP_BFMY_X1;
		break;
	case 2:
		rtn = IP_BFMY_X2;
		break;
	case 3:
		rtn = IP_BFMY_X4;
		break;
	case 0:
	default:
		rtn = IP_BFMY_NON;
		break;
	}
	return	rtn;
}
/*
 *	単純二値化用Ｘ方向強調フィルタ
 *	戻り値 IP_BFMX_* (see lc82103.h)
 */
UBYTE	CHK_BfmxForRedScan(void)
{
	UBYTE	rtn;

	switch ((SYB_MachineParameter[M_PARA_SW_G3] & BFMX_MASK_FOR_RED_SCAN) >> 2) {
	case 1:
		rtn = IP_BFMX_X1;
		break;
	case 2:
		rtn = IP_BFMX_X2;
		break;
	case 3:
		rtn = IP_BFMX_X4;
		break;
	case 0:
	default:
		rtn = IP_BFMX_NON;
		break;
	}
	return	rtn;
}

BYTE	CHK_GammaShiftForRedScan(void)
{
	BYTE	Rslt;

	Rslt = 0;
	if (SYB_MachineParameter[M_PARA_SW_G9] & 0x80) {
		/* マイナス */
		Rslt -= (BYTE)(SYB_MachineParameter[M_PARA_SW_G9] & 0x7F);
	} else {
		Rslt += (BYTE)(SYB_MachineParameter[M_PARA_SW_G9] & 0x7F);
	}
	return	Rslt;
}
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
/**************************************************************************************************/
/**
	@brief		スクランブラの有効/無効を取得する
	
	@li			
	@param		
	@return		TRUE:	スクランブル有効
				FALSE:	スクランブル無効
	@note		
	@date		2005/06/17 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL CHK_ScrambleAvailabe(void)
{
	BOOL bret;
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & SCRAMBLER_AVAILABLE) {
		bret = TRUE;
	}
	else {
		bret = FALSE;
	}
	
	return bret;
}

/**************************************************************************************************/
/**
	@brief		S1をバイパスするか否かを取得する
	
	@li			
	@param		
	@return		TRUE:	S1をバイパスする
				FALSE:	S1をバイパスしない
	@note		
	@date		2005/11/17 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL CHK_BypassS1(void)
{
	BOOL bret;
	
	if (SYB_MachineParameter[M_PARA_SW_I1] & BYPASS_S1) {
		bret = TRUE;
	}
	else {
		bret = FALSE;
	}
	
	return bret;
}

/**************************************************************************************************/
/**
	@brief		S1エラーを無視するか否かを取得する
	
	@li			
	@param		
	@return		TRUE:	S1エラーを無視する(表示しない)
				FALSE:	S1エラーを無視しない(表示する)
	@note		
	@date		2005/11/30 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL CHK_IgnoreS1Error(void)
{
	BOOL bret;
	
	if (SYB_MachineParameter[M_PARA_SW_I1] & IGNORE_S1_ERROR) {
		bret = TRUE;
	}
	else {
		bret = FALSE;
	}
	
	return bret;
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信の通信速度を得る
	
	@li			
	@param		
	@return		通信速度
	@note		
	@date		2005/07/04 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE CHK_IsseiSpeed(void)
{
	UBYTE speed;
	
	switch (SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_SPEED_MASK) {
	case ISSEI_SPEED_2400: /* 2400bps */
		speed = BPS2400_V27;
		break;
	case ISSEI_SPEED_4800: /* 4800bps */
		speed = BPS4800_V27;
		break;
	case ISSEI_SPEED_9600: /* 9600bps */
		speed = BPS9600_V29;
		break;
	case ISSEI_SPEED_7200: /* 7200bps */
		speed = BPS7200_V29;
		break;
	default:
		speed = BPS4800_V27;
		break;
	}
	
	return speed;
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信の符号化方式を得る
	
	@li			
	@param		
	@return		通信速度
	@note		
	@date		2005/07/04 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE CHK_IsseiCodingMethod(void)
{
	UBYTE coding;
	
	if (SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_CODE_MR) {
		coding = SYS_MR_CODE;
	}
	else {
		coding = SYS_MH_CODE;
	}
	
	return coding;
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信の最小伝送時間を得る
	
	@li			
	@param		
	@return		通信速度
	@note		
	@date		2005/07/04 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE CHK_IsseiMinimumScanningTime(void)
{
	UBYTE time;
	
	switch (SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_MIN_SCAN_LINE_TIME_MASK) {
	case ISSEI_MIN_SCAN_LINE_TIME_20: /* 20ms */
		time = SCAN_MINIMUM_TIME20;
		break;
	case ISSEI_MIN_SCAN_LINE_TIME_10: /* 10ms */
		time = SCAN_MINIMUM_TIME10;
		break;
	case ISSEI_MIN_SCAN_LINE_TIME_20_2: /* 20ms/10ms */
		time = SCAN_MINIMUM_TIME20_2;
		break;
	default:
		time = SCAN_MINIMUM_TIME10;
		break;
	}
	
	return time;
}

/**************************************************************************************************/
/**
	@brief		一斉指令受信のタイムアウト時間を得る
	
	@li			
	@param		
	@return		タイムアウト時間[秒]
	@note		
	@date		2005/07/04 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UWORD CHK_IsseiRxTimeout(void)
{
	UWORD timeout;
	
	timeout = (UWORD)(60 * SYB_MachineParameter[M_PARA_SW_I4]);
	
	return timeout;
}

#endif /* defined (KEISATSU) */
