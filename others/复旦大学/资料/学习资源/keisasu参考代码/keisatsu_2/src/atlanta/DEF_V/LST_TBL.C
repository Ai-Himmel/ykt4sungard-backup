/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TBL.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 帳票関係固定ﾃﾞｰﾀ
*	Maintenance	:
*	By Y.Suzuki 1998/10/15：イチョウにあわせて特殊文字のフォントを改良した。
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\std.h"



#if (PRO_MODEM == R288F)
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
	#endif
#endif
#if (PRO_MODEM == MN195006)
	#include	"\src\atlanta\mdm\pana\define\mdm_def.h"
#endif

#if defined(HINOKI3)
#include "\src\atlanta\ext_v\lst_tbl.h"
#endif

CONST UBYTE Disp_IndexTable[]			  = "MEM_IndexTable[   ] :";
CONST UBYTE Disp_FATArea[]				  = "MEM_FATArea :";
CONST UBYTE Disp_TopEmptyBlock[]		  = "MEM_TopEmptyBlock          :";
CONST UBYTE Disp_TotalStoreBlockCounter[] = "MEM_TotalStoreBlockCounter :";
CONST UBYTE Disp_EndBlock[]				  = "MEM_EndBlock               :";
CONST UBYTE Disp_MultiProgramOpenIndexNo[]= "MEM_MultiProgramOpenIndexNo:";

#if ( PRO_MAKER == FX )
const unsigned char far Disp_MultiProgramOpenIndexNo[]= "MEM_MultiProgramOpenIndexNo:";	/*FXのみ*/
#endif
/***********************************************************************
*	T30モニタデータ
************************************************************************/
CONST UBYTE P_Frm_N_Name[LST_FRAME_N_MAX][8] = {	/*通常ﾌﾚｰﾑ ﾒｲ*/
			 "PPS","EOR","NSF","DIS","CSI"				/* 0*/
			,"NSS","DCS","TSI","NSC","DTC"				/* 5*/
			,"CIG","CFR","FTT","EOP","EOM"				/*10*/
			,"MPS","PRI-EOP","PRI-EOM","PRI-MPS","MCF"	/*15*/
			,"RTP","RTN","PIP","PIN","CRP"				/*20*/
			,"DCN","CTC","CTR","ERR","PPR"				/*25*/
			,"RCP","RNR","RR ","FCD","NUL"				/*30*/
			,"CM ","JM ","PWD","PWD","SEP"				/*35*/
			,"SUB"
};

CONST UBYTE P_Frm_N_Cd[LST_FRAME_N_MAX] = {			/*通常ﾌﾚｰﾑ ｺｰﾄﾞ*/
			 PPS_F,EOR_F,NSF_F,DIS_F,CSI_F				/* 0*/
			,NSS_F,DCS_F,TSI_F,NSC_F,DTC_F				/* 5*/
			,CIG_F,CFR_F,FTT_F,EOP_F,EOM_F				/*10*/
			,MPS_F,PRI_EOP_F,PRI_EOM_F,PRI_MPS_F,MCF_F	/*15*/
			,RTP_F,RTN_F,PIP_F,PIN_F,CRP_F				/*20*/
			,DCN_F,CTC_F,CTR_F,ERR_F,PPR_F				/*25*/
			,RCP_F,RNR_F,RR_F,FCD_F,NULL_FF				/*30*/
			,CM_F,JM_F,T_PWD_F,P_PWD_F,SEP_F			/*35*/
			,SUB_F
};

CONST UBYTE P_Frm_N_Msk[LST_FRAME_N_MAX] = {		/*ﾌﾚｰﾑﾏｽｸ*/
			 X_BIT,X_BIT,0,0,0							/* 0*/
			,X_BIT,X_BIT,X_BIT,0,0						/* 5*/
			,0,X_BIT,X_BIT,X_BIT,X_BIT					/*10*/
			,X_BIT,X_BIT,X_BIT,X_BIT,X_BIT				/*15*/
			,X_BIT,X_BIT,X_BIT,X_BIT,X_BIT				/*20*/
			,X_BIT,X_BIT,X_BIT,X_BIT,X_BIT				/*25*/
			,0,X_BIT,X_BIT,0,X_BIT						/*30*/
			,0,0,X_BIT,0,0								/*35*/
			,X_BIT
};

#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) /* 1996/12/17 Y.Murata *//* 1998/09/17 By M.Kuwahara */
	CONST UBYTE P_Frm_S_Name[6][4] = { "TCF","PIX","CJ ","CI ","ANS","CED" };		/*特殊ﾌﾚｰﾑ*/
#else
	CONST UBYTE P_Frm_S_Name[2][4] = { "TCF","PIX" };		/*特殊ﾌﾚｰﾑ*/
#endif
#if ( (PRO_MULTI_LINE == ENABLE)	|| (PRO_MODEM == R288F)) /* 1996/12/17 Y.Murata */ /* R288F is added by H.Kubo 1998/02/17 */
	CONST UBYTE P_Sym_Rate[6][5] = { "2400","2800","3000","3200","3429","    " };		/*特殊ﾌﾚｰﾑ*/
	CONST UBYTE P_Data_Rate[9][4] = { "168","192","216","240","264","288","312","336","   " };		/*特殊ﾌﾚｰﾑ*/

/* 以下の２つのテーブルは、Ｒ２８８Ｆステータスプリント用ワーディングです。
** 本来は、ワーディングファイルにいれるべきですが、サイズが厳しいので、
** ここに置いておきます。
** By O.Kimoto 1996/05/23
*/
 CONST UBYTE MonitorHead[66] = "TX  RX  DTR RTS CTS PDT PSC FED RLSD DMY H/S    ABORT Time(ms)   ";

#if defined(HINOKI)	|| defined(HINOKI2) || defined (HINOKI3)	|| defined(SATSUKI2) || defined(STOCKHM2) /* For DEBUG by O.Kimoto 1998/12/01 */ /* HINOKI2 2001/11/13 T.Takagi */ 
 CONST UBYTE T30Message[MODE_NULL+1][7] = {
	"TX_FSK",
	"TX_ECM",
	"TX_G3 ",
	"TX_TCF",
	"RX_FSK",
	"RX_ECM",
	"RX_G3 ",
	"RX_TCF",
	"RX_CL1",
	"CC RET",
	"PC RET",
	"TX_ND ",
	"RX_ND ",
	"CC OFF",
	"PC OFF",
	"      "
 };
#else
 CONST UBYTE T30Message[12][7] = {
	"TX_FSK",
	"TX_ECM",
	"TX_G3 ",
	"TX_TCF",
	"RX_FSK",
	"RX_ECM",
	"RX_G3 ",
	"RX_TCF",
	"RX_CL1",
	"CC RET",
	"PC RET",
	"      "
 };
#endif

#endif

/***********************************************************************
* 機器設定リスト用定義 	　97/06/27	by M.Kuwahara
***********************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* POPLAR_B と POPLAR_L を分けました。97/11/14 T.Fukumoto */
CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
	LST_PRM_SECUREDOCHOLD,			/* 親展受信記憶期間			*/
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_TXRXTYPE,				/* 送信・受信				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_LINETYPE,				/* 回線タイプ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
	LST_PRM_REDUCTIONRATE,			/* ﾌﾟﾘﾝﾄ縮小率				*/
	LST_PRM_ROTATEMARGIN,			/* 回転ﾏｰｼﾞﾝ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_PAGECOMPOUND,			/* ﾍﾟｰｼﾞ合成				*/
	LST_PRM_COPYREDUCTION,			/* ｺﾋﾟｰ縮小率				*//*  By M.Kuwahara 1997/10/08 */
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
	LST_PRM_CLOSEDNETWORK,			/* 閉域通信					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
	LST_PRM_BLOCKJUNKFAX,			/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
	LST_PRM_PIN_ACCESSMODE,			/* PINｱｸｾｽ					*/
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
	LST_PRM_PAPERSIZE,				/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
	LST_PRM_RS232C,					/* RS232C					*//* RS232Cの場所をかえました 1997/09/25 Y.Matsukuma */
	LST_PRM_COMPAGES,				/* 枚数						*/
	NULL							/**/
};
#endif	/* POPLAR_B */

#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* 設定順に並び替え 97/11/14 T.Fukumoto */
CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* I:発信元名				*/
	LST_PRM_SECUREDOCHOLD,			/*   親展受信記憶期間		*/
	LST_PRM_JOURNALAUTOPRT,			/*   通信管理記録自動		*/
	LST_PRM_CONFREPORT,				/*   通信証					*/
	LST_PRM_PHONETYPE,				/*   通信回線				*/
	LST_PRM_RECEIVEMODE,			/*   受信ﾓｰﾄﾞ				*/
	LST_PRM_SCANNERWIDTH,			/* J:読取ｻｲｽﾞ				*/
	LST_PRM_PRIMARYMODE,			/*   優先文字ｻｲｽﾞ			*/
	LST_PRM_CONTRAST,				/*   優先原稿濃度			*/
	LST_PRM_REDUCTIONRATE,			/*   ﾌﾟﾘﾝﾄ縮小率			*/
	LST_PRM_PAGECOMPOUND,			/*   ﾍﾟｰｼﾞ合成				*/
	LST_PRM_COPYPROTECT,			/*   ｺﾋﾟｰ禁止				*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_SORTCOPY,				/*   ｿｰﾃｨﾝｸﾞｺﾋﾟｰ			*//*  By T.Fukumoto 1997/11/13 */
	LST_PRM_COPYREDUCTION,			/*   ｺﾋﾟｰ縮小率				*//*  By M.Kuwahara 1997/10/08 */
	LST_PRM_DIALINGPAUSE,			/*   ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/*   呼出ﾍﾞﾙ回数			*/
	LST_PRM_REDIALTIMES,			/*   ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/*   ECMﾓｰﾄﾞ				*/
	LST_PRM_PASSCODE,				/*   ﾊﾟｽｺｰﾄﾞ				*/
	LST_PRM_CLOSEDNETWORK,			/*   閉域通信				*/
	LST_PRM_SECURITYTX,				/*   ﾊﾟｽﾜｰﾄﾞ送信			*/
	LST_PRM_BLOCKJUNKFAX,			/*   ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/*   ﾘﾓｰﾄ診断				*/
	LST_PRM_MEMORYTX,				/*   ﾒﾓﾘ送信				*/
	LST_PRM_STAMP,					/*   済ｽﾀﾝﾌﾟ				*/
	LST_PRM_DIALIN,					/*   ﾀﾞｲﾔﾙｲﾝ				*/
	LST_PRM_PIN_ACCESSMODE,			/*   PINｱｸｾｽ				*/
	LST_PRM_OPERATIONPROTECT,		/*   ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_HOLDMELODY,				/*   保留メロディ			*//* 追加 97/11/07 T.Fukumoto */
 #if (PRO_REMOTE_RX == ENABLE)
	LST_PRM_REMOTE_RX,				/*   リモート受信			*//* 追加 9/03/13 T.Fukumoto */
 #endif
 #if (PRO_ONHOOK_RX_SWITCH == ENABLE)
	LST_PRM_ONHOOK_RX,				/*   オンフック受信			*//* 追加 9/03/13 T.Fukumoto */
 #endif
	LST_PRM_MESAGETRANS,			/* K:ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_DEPARTMENT,				/* M:部門管理ｾｯﾄ			*/
	LST_PRM_DEPARTMENTPROTECT,		/*   部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* O:ｾｷｭﾘﾃｨ受信				*/
	NULL							/**/
};
#endif	/* POPLAR_L */

#if ( PRO_KEYPANEL == PANEL_POPLAR_H )
CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
	LST_PRM_SECUREDOCHOLD,			/* 親展受信記憶期間			*/
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_TXRXTYPE,				/* 送信・受信				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_LINETYPE,				/* 回線タイプ				*//*  By O.Kimoto 1997/07/09 */
 #if (PRO_MULTI_TTI == ENABLE)	/* By H.Fujimura 1998/07/07 */
	LST_PRM_MULTI_TTI_ID,			/* 発信元名(ｶﾅID)			*/
 #endif
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
 #if (PRO_DIALIN_SW == DISABLE) /* By H.Fujimura 2002/07/11 */
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
 #endif
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
	LST_PRM_REDUCTIONRATE,			/* ﾌﾟﾘﾝﾄ縮小率				*/
	LST_PRM_ROTATEMARGIN,			/* 回転ﾏｰｼﾞﾝ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_PAGECOMPOUND,			/* ﾍﾟｰｼﾞ合成				*/
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
	LST_PRM_CLOSEDNETWORK,			/* 閉域通信					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
	LST_PRM_BLOCKJUNKFAX,			/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
 #if (PRO_DIALIN_SW == ENABLE) /* By H.Fujimura 2002/07/11 */
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
 #endif
	LST_PRM_HOLDMELODY,				/* 保留メロディー			*//* 追加 97/11/07 T.Fukumoto */
	LST_PRM_RELAYED_RELAY_TX,		/* 中々継					*/	/* Add By O.Kimoto 1998/03/02 */
	LST_PRM_PIN_ACCESSMODE,			/* PINｱｸｾｽ					*/
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
	LST_PRM_PAPERSIZE,				/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
	LST_PRM_RS232C,					/* RS232C					*//* RS232Cの場所をかえました 1997/09/25 Y.Matsukuma */
	LST_PRM_COMPAGES,				/* 枚数						*/
	NULL							/**/
};
#endif	/* POPLAR_H */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
/* オペレーションの順番に並べ替えました 1997/10/08 Y.Matsukuma */
CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
	LST_PRM_SECUREDOCHOLD,			/* 親展受信記憶期間			*/
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_TXRXTYPE,				/* 送信・受信				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_LINETYPE,				/* 回線タイプ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
	LST_PRM_REDUCTIONRATE,			/* ﾌﾟﾘﾝﾄ縮小率				*/
	LST_PRM_ROTATEMARGIN,			/* 回転ﾏｰｼﾞﾝ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_PAGECOMPOUND,			/* ﾍﾟｰｼﾞ合成				*/
	LST_PRM_COPYREDUCTION,			/* ｺﾋﾟｰ縮小率				*/
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_PAPERSIZE,				/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
	LST_PRM_CLOSEDNETWORK,			/* 閉域通信					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
	LST_PRM_BLOCKJUNKFAX,			/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_PIN_ACCESSMODE,			/* PINｱｸｾｽ					*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
	LST_PRM_RS232C,					/* RS232C					*//* RS232Cの場所をかえました 1997/09/25 Y.Matsukuma */
	LST_PRM_COMPAGES,				/* 枚数						*/
	NULL							/**/
};
/* F-101専用 リストテーブル 1997/12/25 Y.Matsukuma */
CONST UBYTE List_ParameterTable_Category2[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_TXRXTYPE,				/* 送信・受信				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_LINETYPE,				/* 回線タイプ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
	LST_PRM_REDUCTIONRATE,			/* ﾌﾟﾘﾝﾄ縮小率				*/
	LST_PRM_ROTATEMARGIN,			/* 回転ﾏｰｼﾞﾝ				*//*  By O.Kimoto 1997/07/09 */
	LST_PRM_PAGECOMPOUND,			/* ﾍﾟｰｼﾞ合成				*/
	LST_PRM_COPYREDUCTION,			/* ｺﾋﾟｰ縮小率				*/
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_PAPERSIZE,				/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_PIN_ACCESSMODE,			/* PINｱｸｾｽ					*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
	LST_PRM_RS232C,					/* RS232C					*//* RS232Cの場所をかえました 1997/09/25 Y.Matsukuma */
	LST_PRM_COMPAGES,				/* 枚数						*/
	NULL							/**/
};
#endif	/* ANZU_L */

#if ( PRO_KEYPANEL == PANEL_SAKAKI )
CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
	LST_PRM_SECUREDOCHOLD,			/* 親展受信記憶期間			*/
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
 #if (PRO_DIALIN_SW == DISABLE) /* 2002/08/30 By M.Maeda */
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
 #endif
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
	LST_PRM_CLOSEDNETWORK,			/* 閉域通信					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
	LST_PRM_BLOCKJUNKFAX,			/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
 #if (PRO_DIALIN_SW == ENABLE) /* 2002/08/30 By M.Maeda */
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
 #endif
	LST_PRM_HOLDMELODY,				/* 保留メロディー			*//* 追加 97/11/07 T.Fukumoto */
	LST_PRM_RELAYED_RELAY_TX,		/* 中々継					*/	/* Add By O.Kimoto 1998/03/02 */
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_PAPERTYPE,				/* 記録紙ﾀｲﾌﾟ				*/
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
	LST_PRM_PAPERSIZE,				/* 記録紙ﾍﾟｰﾊﾟｰｻｲｽﾞ			*/
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
	LST_PRM_WARP,					/* ﾜｰﾌﾟ機能					*/
	LST_PRM_NUMBERDISPLAY,			/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ			*/
	NULL							/**/
};

#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if ( PRO_KEYPANEL == PANEL_HINOKI )*/
#if ( PRO_KEYPANEL == PANEL_HINOKI ) || ( PRO_KEYPANEL == PANEL_SATSUKI2 )  || (PRO_KEYPANEL == PANEL_STOCKHM2)

CONST UBYTE List_ParameterTable[]	= {
	LST_PRM_TTI_ID,					/* 発信元名					*/
 #if (PRO_MULTI_TTI == ENABLE)	/* By H.Fujimura 1999/03/17 */
	LST_PRM_MULTI_TTI_ID,			/* 発信元名(ｶﾅID)			*/
 #endif
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (親展受信記憶期間を消去です) Modify by SMuratec L.Z.W 2003/10/10 */
	LST_PRM_SECUREDOCHOLD,			/* 親展受信記憶期間			*/
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	LST_PRM_JOURNALAUTOPRT,			/* 通信管理記録自動			*/
	LST_PRM_CONFREPORT,				/* 通信証					*/
#if defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/07/21 */
	LST_PRM_PHONETYPE_EXT,			/* 警電通信回線				*/
	LST_PRM_PHONETYPE,				/* 加入通信回線				*/
#else
	LST_PRM_PHONETYPE,				/* 通信回線					*/
	LST_PRM_RECEIVEMODE,			/* 受信ﾓｰﾄﾞ					*/
#endif
	LST_PRM_SCANNERWIDTH,			/* 読取ｻｲｽﾞ					*/
	LST_PRM_PRIMARYMODE,			/* 優先文字ｻｲｽﾞ				*/
	LST_PRM_CONTRAST,				/* 優先原稿濃度				*/
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2004/06/25 */
	LST_PRM_REDUCTIONRATE,			/* ﾌﾟﾘﾝﾄ縮小率				*/
	LST_PRM_COPYREDUCTION,			/* ｺﾋﾟｰ縮小率				*/
#endif /* End of  (PRO_KEYPANEL == PANEL_STOCKHM2) */
	LST_PRM_COPYPROTECT,			/* ｺﾋﾟｰ禁止					*//*  by M.Kuwahara 1997/08/26 */
	LST_PRM_DIALINGPAUSE,			/* ﾎﾟｰｽﾞ時間				*/
#if defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/07/21 */
	LST_PRM_RINGGINGTIMES_EXT,		/* 警電回線側呼出ベル回数	*/
#endif
	LST_PRM_RINGGINGTIMES,			/* 呼出ﾍﾞﾙ回数				*/
	LST_PRM_REDIALTIMES,			/* ﾘﾀﾞｲﾔﾙ回数				*/
	LST_PRM_ECMMODE,				/* ECMﾓｰﾄﾞ					*/
	LST_PRM_REMOTEDIAGNOSTIC,		/* ﾘﾓｰﾄ診断					*/
#if defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/07/21 */
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
#else
	LST_PRM_PASSCODE,				/* ﾊﾟｽｺｰﾄﾞ					*/
 #if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (ﾊﾟｽﾜｰﾄﾞ送信を消去して、ﾊﾟｽｺｰﾄﾞをrestoreです) Modify by SMuratec L.Z.W 2003/10/10 */
	LST_PRM_CLOSEDNETWORK,			/* 閉域通信					*/
	LST_PRM_SECURITYTX,				/* ﾊﾟｽﾜｰﾄﾞ送信				*/
 #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	LST_PRM_BLOCKJUNKFAX,			/* ﾀﾞｲﾚｸﾄﾒｰﾙ				*/
	LST_PRM_MEMORYTX,				/* ﾒﾓﾘ送信					*/
 #if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2)/* Modify by SMuratec L.Z.W 2003/09/12 */
	LST_PRM_STAMP,					/* 済ｽﾀﾝﾌﾟ					*/
 #endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
 #if (PRO_KEYPANEL != PANEL_STOCKHM2) /* DVT : Mod by SMuratec C.P 200/10/07 */
	LST_PRM_DIALIN,					/* ﾀﾞｲﾔﾙｲﾝ					*/
 #endif /* End of (PRO_KEYPANEL != PANEL_STOCKHM2) */
 #if defined(HINOKI2) && defined(JPNNTT)	/* オペレーションの順番と機器設定リストの順番が食い違っている by O.Kimoto 2002/11/14 */
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_HOLDMELODY,				/* 保留メロディー			*//* 追加 97/11/07 T.Fukumoto */
 #else
	LST_PRM_HOLDMELODY,				/* 保留メロディー			*//* 追加 97/11/07 T.Fukumoto */
	LST_PRM_OPERATIONPROTECT,		/* ｵﾍﾟﾚｰｼｮﾝﾌﾟﾛﾃｸﾄ			*/
 #endif
#endif	/* KEISATSU */
	LST_PRM_MESAGETRANS,			/* ﾒｯｾｰｼﾞ送信				*/
 #if (0) /* ＨＩＮＯＫＩはサイレントオペレーションの機能がないので削除。By H.Fujimura 1999/04/07 */
 **	LST_PRM_SILENTOPERATION,		/* ｻｲﾚﾝﾄｵﾍﾟﾚｰｼｮﾝ			*/
 #endif
	LST_PRM_DEPARTMENT,				/* 部門管理ｾｯﾄ				*/
	LST_PRM_DEPARTMENTPROTECT,		/* 部門管理ﾌﾟﾛﾃｸﾄ			*/
	LST_PRM_REMOTESECURITYRX,		/* ｾｷｭﾘﾃｨ受信				*/
	LST_PRM_DAYLIGHTSAVING,			/* 夏時間自動切換え			*/
	LST_PRM_RINGMASTR,				/* ﾘﾝｸﾞﾏｽﾀｾｯﾄ				*/
	LST_PRM_RXALARM,				/* 受信完了ｱﾗｰﾑ				*//* ﾏｰｷｭﾘｰﾎﾟｰｽﾞと場所を入れ替えました */
	LST_PRM_MERCURYPAUSE,			/* ﾏｰｷｭﾘｰﾎﾟｰｽﾞ				*//* 1997/09/25 Y.Matsukuma */
 #if (PRO_CLASS1 == ENABLE)
	LST_PRM_RS232C,					/* RS232C					*//* added by H.Hirao 1999/01/13 */
 #endif
#if !defined (KEISATSU) /* 警察FAX 05/10/04 石橋正和 */
	LST_PRM_WARP,					/* ﾜｰﾌﾟ機能					*/
#endif
	LST_PRM_NUMBERDISPLAY,			/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ			*/
 #if defined(STOCKHM2)	/* Added by SMuratec 夏 2004/7/14 */
	LST_PRM_MERCURYNUMBER,			/* ﾏｰｷｭﾘｰﾅﾝﾊﾞｰ				*/  /* Added by SMuratec C.P 2004/07/08 for prefix */
	LST_PRM_DIALTONE,				/*ダイヤルトーン検出 		*/
 #endif	
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE) && (!defined (KEISATSU))	/* By H.Fujimura 1999/01/07 */
  #if (PRO_KEYPANEL != PANEL_STOCKHM2) /* DVT : Mod by SMuratec C.P 200/10/07 */
	LST_PRM_ND_WARP,				/* ＮＤワープ				*/
  #endif /* End of (PRO_KEYPANEL != PANEL_STOCKHM2) */
 #endif
 #if defined(HINOKI3)	/* Add by Y.kano 2004/12/08 */
	LST_PRM_MERCURYNUMBER,			/* ﾏｰｷｭﾘｰﾅﾝﾊﾞｰ				*/
#if defined(KEISATSU)	/* 警察FAX Added by SMuratec K.W.Q 2005/10/10 */
	LST_PRM_DIALTONE_KEIDEN,		/* 警電ダイヤルトーン検出 	*/
#endif 
	LST_PRM_DIALTONE,				/*ダイヤルトーン検出 		*/
 #endif
#if defined(KEISATSU)	/* 警察FAX対応 Added by SMuratec 夏 2005/07/21 */
	LST_PRM_SETTING_LINE,			/* 優先通信回線 			*/
	LST_PRM_SETTING_FAXMODE,		/* 優先通信方式 			*/
	LST_PRM_SCRAMBLE_KEIDEN,		/* 警電回線側スクランブル	*/
	LST_PRM_SCRAMBLE_KANYU,			/* 加入回線側スクランブル	*/
	LST_PRM_REMOTE_NUM_ISSEI,		/* 一斉通信のリモート特番	*/
	LST_PRM_REMOTE_NUM_KOBETSU,		/* 個別通信のリモート特番	*/
#endif 
	NULL							/**/
};

#endif

/***********************************************************************
* 消耗品発注票モデル名変換用定義 	　97/09/19	by M.Kuwahara
***********************************************************************/
CONST struct LST_ModelChange_t	LST_ModelChangeTable[] = {
	/* ﾊﾞｰｼﾞｮﾝ名	変換ﾓﾃﾞﾙ名 */
#if defined(JPN)	/* 日本 */
	{"V930 ",		"ﾑﾗﾃｯｸ V-930"},
	{"V850 ", 		"ﾑﾗﾃｯｸ V-850"},	/* Remane By O.Kimoto 1998/01/22 */
	{"V730 ", 		"ﾑﾗﾃｯｸ V-730"},	/* 1998/02/16  By T.Yamaguchi */
	{"K7312", 		"Konica7312 "},	/* V930 ｺﾆｶ OEM By M.Tachibana 1998/06/18  */
	{"M2610", 		"MF2610     "},	/* V730 ﾐﾉﾙﾀ OEM By M.Tachibana 1998/06/18  */
	{"L400 ", 		"L400       "},	/* L400 By Y.Suzuki 1998/06/19  */
	{"TC751", 		"TC751      "},	/* V730 FX OEM By M.Tachibana 1998/07/09 */
	{"SF790", 		"SPF-790    "},	/* V730 三洋 OEM By M.Tachibana 1998/07/09 */
 #if defined(POPLAR_F)
	{"L400A", 		"NTTFAX L400"},	/* L400後継 2000/1/24 Y.Murata */
	{"V740 ", 		"ﾑﾗﾃｯｸ V-740"},	/* V730後継 2000/1/24 Y.Murata */
	{"M2620", 		"MF2620     "},	/* V740 ﾐﾉﾙﾀ OEM 2000/6/28 Y.Murata */
 #endif
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 By H.Fujimura 2002/08/26 */
	{"V851 ", 		"ﾑﾗﾃｯｸ V-851"},
 #endif
	{"\0", 			"\0"}
#elif defined(US1)					/* orderbythonda1998/11/11 */
	{"1500 ",		"PB 4100"},
#elif defined(USA)					/* JPN,USA,その他に条件を分ける By S.Fukui Mar.31,1998 */
	{"1500 ",		"MFX-1500"},
	{"D71_H", 		"V-850   "},
	{"D71_L", 		"V-730   "},
	{"\0", 			"\0"}
#else
/* ＯＥＭ先毎に機種名が変更する為、モデル名はＤ品番とする。(輸出/技管/CS統括 確認済) By S.Fukui June 11,1998 */
	{"D71B ",		"D71B          "},
	{"D71_H", 		"D71_H         "},
	{"D71_L", 		"D71_L         "},
	{"OO120",       "OKIOFFICE 120 "},  /* ＯＫＩ用モデル名追加  S.Fukui Jul.9,1998 */
	{"\0", 			"\0"}
#endif
};

#if defined(US1)
/***********************************************************************
* 消耗品発注票発注先データ			orderbythonda1998/11/11
***********************************************************************/
CONST UBYTE DistributorName[] = "Pitney Bowes Office Systems";		/* 発注先名 */
CONST UBYTE ToCompanyFaxNumber[] = "1-800-832-1869";				/* 発注先Fax No. */
CONST UBYTE ToCompanyTelNumber[] = "1-800-462-6797";				/* 発注先Tel No. */
#endif

#if (PRO_SGP_TEST_ROM == ENABLE)
/****************************************************
 ** シンガポール市場調査レポート By S. Wang 98/07/25
 ****************************************************/
 CONST UBYTE SgpReportHead[80] = " No.  Location             Maker         Modem Code Size STime Mode Ecm Result  ";
 CONST UBYTE SgpReportMaker[15][12] = {
	"Muratec     ",	  /* 村田機械   	*/
	"Brother	 ",	  /* ﾌﾞﾗｻﾞｰ工業 	*/
	"Cannon1	 ",	  /* Ｃａｎｏｎ １	*/
	"Cannon2	 ",	  /* Ｃａｎｏｎ ２	*/
	"Oki		 ",	  /* 沖電気			*/
	"Cannon3	 ",	  /* ｷｬﾉﾝ			*/
	"Sanyo		 ",   /* 三洋電機		*/
	"Sharp		 ",   /* ｼｬｰﾌﾟ			*/
	"NEC		 ",	  /* 日本電気(NEC)	*/
	"Xerox		 ",   /* 富士ｾﾞﾛｯｸｽ		*/
	"Pana		 ",   /* 松下電気		*/
	"Densou		 ",   /* 松下電送		*/
	"Mitsubishi	 ",   /* 三菱電気		*/
	"Ricoh		 ",   /* ﾘｺｰ			*/
	"TEC		 "	  /* 東京電気(TEC)	*/
};


#endif

/***********************************************************************
*	フォントを横に２倍するためのデータ
************************************************************************/
CONST UBYTE TwiceData[16] = {
			0x00, 0x03, 0x0C, 0x0F,
			0x30, 0x33, 0x3C, 0x3F,
			0xC0, 0xC3, 0xCC, 0xCF,
			0xF0, 0xF3, 0xFC, 0xFF
};

/***********************************************************************
*	網掛けフォント
************************************************************************/
CONST UBYTE PrintMeshData[16] = {
			0x88, 0x00, 0x00, 0x22,
			0x00, 0x00, 0x88, 0x00,
			0x00, 0x22, 0x00, 0x00,
			0x88, 0x00, 0x00, 0x22
};

#if defined(JPN) || (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_SAKAKI)
/* JPN_TOP */
/***********************************************************************
*	半角フォント 日本語用
************************************************************************/
CONST unsigned char far ByteFont[256][16] = {
{			/*  SPC 00    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 01    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 02    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 03    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 04    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S(短縮用) */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/* G(ｸﾞﾙｰﾌﾟ用)*/
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 07    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x08 */
{			/*  SUN       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x09 */
{			/*  MON       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0A */
{			/*  TUE       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x92,	/*  10010010  */
	0x92,	/*  10010010  */
	0x92,	/*  10010010  */
	0x92,	/*  10010010  */
	0x10,	/*  00010000  */
	0x28,	/*  00101000  */
	0x28,	/*  00101000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x82,	/*  10000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0B */
{			/*  WED       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x12,	/*  00010010  */
	0xF4,	/*  11110100  */
	0x38,	/*  00111000  */
	0x58,	/*  01011000  */
	0x54,	/*  01010100  */
	0x94,	/*  10010100  */
	0x12,	/*  00010010  */
	0x10,	/*  00010000  */
	0x30,	/*  00110000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0C */
{			/*  THU       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x38,	/*  00111000  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x92,	/*  10010010  */
	0x92,	/*  10010010  */
	0x92,	/*  10010010  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0D*/
{			/*  FRI       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x28,	/*  00101000  */
	0x44,	/*  01000100  */
	0xFE,	/*  11111110  */
	0x92,	/*  10010010  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x54,	/*  01010100  */
	0x38,	/*  00111000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0E */
{			/*  SAT       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x0F */
{			/*  YEAR      */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x7E,	/*  01111110  */
	0x88,	/*  10001000  */
	0x08,	/*  00001000  */
	0x7C,	/*  01111100  */
	0x08,	/*  00001000  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0xFE,	/*  11111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 10    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x77,	/*  01110111  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00, 	/*  00000000  */
	0x00 	/*  00000000  */
},
{			/*  SPC 11    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 12    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF	/*  11111111  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{			/*  SPC       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  !         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  "         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  #         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
#if (defined(POPLAR_H) && defined(JP0)) /* V851 パネル表記と違う By H.Fujimura 2002/08/23 */
{			/*  $         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x49,	/*  01001001  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x3E,	/*  00111110  */
	0x09,	/*  00001001  */
	0x09,	/*  00001001  */
	0x49,	/*  01001001  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
#else
{			/*  $         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x3E,	/*  00111110  */
	0x55,	/*  01010101  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x3E,	/*  00111110  */
	0x15,	/*  00010101  */
	0x15,	/*  00010101  */
	0x55,	/*  01010101  */
	0x3E,	/*  00111110  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
#endif
{			/*  %         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x49,	/*  01001001  */
	0x32,	/*  00110010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x26,	/*  00100110  */
	0x49,	/*  01001001  */
	0x09,	/*  00001001  */
	0x06,	/*  00000110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  &         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x38,	/*  00111000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x28,	/*  00101000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x45,	/*  01000101  */
	0x42,	/*  01000010  */
	0x25,	/*  00100101  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  '         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  (         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  )         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0		  /*  00000000  */
},
{			/*  *         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x2A,	/*  00101010  */
	0x49,	/*  01001001  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  +         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ,         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  -         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  .         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x30,	/*  00110000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  /         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  0         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  1         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  2         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  3         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  4         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x0A,	/*  00001010  */
	0x0A,	/*  00001010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  5         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  6         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  7         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  8         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  9         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x23,	/*  00100011  */
	0x1D,	/*  00011101  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  :         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ;         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  <         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  =         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  >         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ?         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  @         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x19,	/*  00011001  */
	0x29,	/*  00101001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  A         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  B         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x3E,	/*  00111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  C         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  D         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x22,	/*  00100010  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x22,	/*  00100010  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  E         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  F         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  G         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  H         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  I         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  J         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1F,	/*  00011111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38,	/*  00111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  K         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x60,	/*  01100000  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  L         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  M         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x63,	/*  01100011  */
	0x55,	/*  01010101  */
	0x55,	/*  01010101  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  N         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x61,	/*  01100001  */
	0x51,	/*  01010001  */
	0x51,	/*  01010001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x45,	/*  01000101  */
	0x43,	/*  01000011  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  O         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  P         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Q         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x22,	/*  00100010  */
	0x1D,	/*  00011101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  R         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  T         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  U         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  V         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  W         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  X         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Y         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Z         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  [         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  \         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ]         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ^         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  _         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  `         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  a         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  b         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  c         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  d         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  e         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  f         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x12,	/*  00010010  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  g         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C	/*  00111100  */
},
{			/*  h         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  i         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  j         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  k         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x70,	/*  01110000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  l         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  m         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  n         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  o         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  p         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40	/*  01000000  */
},
{			/*  q         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x01	/*  00000001  */
},
{			/*  r         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  s         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x30,	/*  00110000  */
	0x0C,	/*  00001100  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  t         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x12,	/*  00010010  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  u         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  v         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  w         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  x         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  y         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  z         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  {         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  |         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  }         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x06,	/*  00000110  */
	0x7F,	/*  01111111  */
	0x06,	/*  00000110  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x30,	/*  00110000  */
	0x7F,	/*  01111111  */
	0x30,	/*  00110000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},

/*--------------------------*/
/* 0x80 ～ 0x9F 未使用		*/
/* 全てスペース				*/
/*--------------------------*/
/* 0x80 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x81 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x82 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x83 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x84 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x85 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x86 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x87 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x88 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x89 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8A */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8B */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8C */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8D */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8E */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8F */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x90 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x91 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x92 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x93 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x94 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x95 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0X96 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x97 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x98 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x99 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9A */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9B */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9C */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9D */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9E */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9F */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA0  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA1  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x60,	/*  01100000  */
	0x90,	/*  10010000  */
	0x90,	/*  10010000  */
	0x60,	/*  01100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA2  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA3  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0xFC,	/*  11111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA4  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x80,	/*  10000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA5  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA6   ｦ*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA7   ｧ*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x04,	/*  00000100  */
	0x24,	/*  00100100  */
	0x28,	/*  00101000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA8   ｨ*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x30,	/*  00110000  */
	0x50,	/*  01010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA9  */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x44,	/*  01000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x38,	/*  00111000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x7C,	/*  01111100  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x48,	/*  01001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x7C,	/*  01111100  */
	0x24,	/*  00100100  */
	0x28,	/*  00101000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x38,	/*  00111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x7C,	/*  01111100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x14,	/*  00010100  */
	0x18,	/*  00011000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x80,	/*  10000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x30,	/*  00110000  */
	0x50,	/*  01010000  */
	0x90,	/*  10010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x30,	/*  00110000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFE,	/*  11111110  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x28,	/*  00101000  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x88,	/*  10001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0xFE,	/*  11111110  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x88,	/*  10001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x82,	/*  10000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0xC0,	/*  11000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB9 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7E,	/*  01111110  */
	0x84,	/*  10000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0xFE,	/*  11111110  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xE0,	/*  11100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xE0,	/*  11100000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0xE0,	/*  11100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x14,	/*  00010100  */
	0x24,	/*  00100100  */
	0x42,	/*  01000010  */
	0x82,	/*  10000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0xFE,	/*  11111110  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x82,	/*  10000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x60,	/*  01100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x22,	/*  00100010  */
	0x62,	/*  01100010  */
	0x92,	/*  10010010  */
	0x0A,	/*  00001010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0xF0,	/*  11110000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x80,	/*  10000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x30,	/*  00110000  */
	0x28,	/*  00101000  */
	0x24,	/*  00100100  */
	0x22,	/*  00100010  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0xC8,	/*  11001000  */
	0x28,	/*  00101000  */
	0x10,	/*  00010000  */
	0x18,	/*  00011000  */
	0x24,	/*  00100100  */
	0x42,	/*  01000010  */
	0x82,	/*  10000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x34,	/*  00110100  */
	0xD2,	/*  11010010  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC9 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0xC0,	/*  11000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x82,	/*  10000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0xFE,	/*  11111110  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x40,	/*  01000000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x88,	/*  10001000  */
	0x84,	/*  10000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0xFE,	/*  11111110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x54,	/*  01010100  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x92,	/*  10010010  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x50,	/*  01010000  */
	0x30,	/*  00110000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x80,	/*  10000000  */
	0x60,	/*  01100000  */
	0x18,	/*  00011000  */
	0x86,	/*  10000110  */
	0x60,	/*  01100000  */
	0x18,	/*  00011000  */
	0x06,	/*  00000110  */
	0x80,	/*  10000000  */
	0x60,	/*  01100000  */
	0x18,	/*  00011000  */
	0x06,	/*  00000110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x48,	/*  01001000  */
	0x84,	/*  10000100  */
	0x82,	/*  10000010  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x24,	/*  00100100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x40,	/*  01000000  */
	0x80,	/*  10000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0xFE,	/*  11111110  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0xFE,	/*  11111110  */
	0x22,	/*  00100010  */
	0x24,	/*  00100100  */
	0x28,	/*  00101000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD9 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x50,	/*  01010000  */
	0x50,	/*  01010000  */
	0x50,	/*  01010000  */
	0x50,	/*  01010000  */
	0x50,	/*  01010000  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x52,	/*  01010010  */
	0x54,	/*  01010100  */
	0x58,	/*  01011000  */
	0x90,	/*  10010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x80,	/*  10000000  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x84,	/*  10000100  */
	0x88,	/*  10001000  */
	0x90,	/*  10010000  */
	0xA0,	/*  10100000  */
	0xC0,	/*  11000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0xFE,	/*  11111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFE,	/*  11111110  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x82,	/*  10000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xE0,	/*  11100000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0xE0,	/*  11100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xA0,	/*  10100000  */
	0x50,	/*  01010000  */
	0x28,	/*  00101000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xDF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/*0xE0*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x31,	/*  00110001  */
	0x4A,	/*  01001010  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x4A,	/*  01001010  */
	0x31,	/*  00110001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  00100010  */
	0x42,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE2*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x24,	/*  00100100  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x58,	/*  01011000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x4C,	/*  01001100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40	/*  01000000  */
},
/* 0xE3 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3E,	/* 00111110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x3C,	/* 00111100 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x3E,	/* 00111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xE4 */
{
/* ﾌｫﾝﾄが15ﾊﾞｲﾄしかなかったのを修正（IBM_FONT[]を参照） by K.Watanabe 1999/03/11 */
#if (0)
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x3D,	/*  00111101  */
//	0x20,	/*  00100000  */
//	0x20,	/*  00100000  */
//	0x20,	/*  00100000  */
//	0x40	/*  01000000  */
#endif
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x3D,	/*  00111101  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40	/*  01000000  */
},
/*0xE5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE6 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x0E,	/* 00001110 */
	0x11,	/* 00010001 */
	0x21,	/* 00100001 */
	0x61,	/* 01100001 */
	0x5E,	/* 01011110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xE7 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3F,	/* 00111111 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x3F,	/* 00111111 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x02,	/* 00000010 */
	0x7C	/* 01111100 */
},
/*0xE8*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x48,	/*  01001000  */
	0x28,	/*  00101000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE9 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x7A,	/* 01111010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEA */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x42,	/* 01000010 */
	0x44,	/* 01000100 */
	0x38	/* 00111000 */
},
/* 0xEB */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x44,	/* 01000100 */
	0x28,	/* 00101000 */
	0x10,	/* 00010000 */
	0x28,	/* 00101000 */
	0x44,	/* 01000100 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEC */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x3E,	/* 00111110 */
	0x48,	/* 01001000 */
	0x48,	/* 01001000 */
	0x49,	/* 01001001 */
	0x3E,	/* 00111110 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xED */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x7C,	/* 01111100 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x7C,	/* 01111100 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x3F,	/* 00111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEE */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x5C,	/* 01011100 */
	0x62,	/* 01100010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00 	/* 00000000 */
},
/* 0xEF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF0 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x40,	/* 01000000 */
	0x5E,	/* 01011110 */
	0x61,	/* 01100001 */
	0x61,	/* 01100001 */
	0x60,	/* 01100001 */
	0x5E,	/* 01011110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40	/* 01000000 */
},
/* 0xF1 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000001 */
	0x3D,	/* 00111101 */
	0x43,	/* 01000011 */
	0x43,	/* 01000011 */
	0x43,	/* 01000011 */
	0x3D,	/* 00111101 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01	/* 00000001 */
},
/* 0xF2*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x3E,	/*  00111110  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00 	/*  00000000  */
},
/* 0xF3*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF4*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x55,	/*  01010101  */
	0x77,	/*  01110111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF5 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x3D,	/* 00111101 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xF6*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF7*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3F,	/*  00111111  */
	0x52 ,	/*  01010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF8*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x41,	/* 01000001 */
	0x22,	/* 00100010 */
	0x14,	/* 00010100 */
	0x08,	/* 00001000 */
	0x14,	/* 00010100 */
	0x22,	/* 00100010 */
	0x41,	/* 01000001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xF9*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x3F,	/* 00111111 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x02,	/* 00000010 */
	0x7C 	/* 01111100 */
},
/* 0xFA*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x01,	/* 00000001 */
	0x02,	/* 00000010 */
	0x7C,	/* 01111100 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x7F,	/* 01111111 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFB*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x10,	/* 00010000 */
	0x10,	/* 00010000 */
	0x10,	/* 00010000 */
	0x1F,	/* 00011111 */
	0x11,	/* 00010001 */
	0x11,	/* 00010001 */
	0x11,	/* 00010001 */
	0x11,	/* 00010001 */
	0x22,	/* 00100010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFC*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x49,	/* 01001001 */
	0x49,	/* 01001001 */
	0x49,	/* 01001001 */
	0x49,	/* 01001001 */
	0x7F,	/* 01111111 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFD*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00, 	/* 00000000 */
	0x18,	/* 00011000 */
	0x24,	/* 00100100 */
	0x24,	/* 00100100 */
	0x18,	/* 00011000 */
	0x00,	/* 00000000 */
	0x7E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x18,	/* 00011000 */
	0x24,	/* 00100100 */
	0x24,	/* 00100100 */
	0x18,	/* 00011000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFE*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFF*/
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
}};

#else

 /* 移植 by SMuratec K.W.Q 2003/07/23 */
 /*#if (PRO_KEYPANEL == PANEL_HINOKI)*/	/* Add by O.Kimoto 1999/02/03 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by O.Kimoto 1999/02/03 */

/*** USA_TOP */
/***********************************************************************
*	半角フォント JPN以外
************************************************************************/
CONST unsigned char far ByteFont[256][16] = {
{			/*  SPC 00    *//* 00 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 01    *//* 01 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 02    *//* 02 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 03    *//* 03 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 04    *//* 04 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S(短縮用) *//* 05 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/* G(ｸﾞﾙｰﾌﾟ用)*//* 06 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 07    *//* 07 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 08    *//* 08 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 09    *//* 09 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0A    *//* 0A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0B    *//* 0B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0C    *//* 0C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0D    *//* 0D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0E    *//* 0E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0F    *//* 0F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 10    *//* 10 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x77,	/*  01110111  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00, 	/*  00000000  */
	0x00 	/*  00000000  */
},
{			/*  SPC 11    *//* 11 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 12    *//* 12 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 13 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 14 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF	/*  11111111  */
},
{							/* 15 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 16 */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 17 */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 18 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 19 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 1A */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 1B */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 1C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 1D */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{							/* 1E */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 1F */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{			/*  SPC       *//* 20 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  !         *//* 21 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  "         *//* 22 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  #         *//* 23 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  $         *//* 24 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x3E,	/*  00111110  */
	0x55,	/*  01010101  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x3E,	/*  00111110  */
	0x15,	/*  00010101  */
	0x15,	/*  00010101  */
	0x55,	/*  01010101  */
	0x3E,	/*  00111110  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  %         *//* 25 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x49,	/*  01001001  */
	0x32,	/*  00110010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x26,	/*  00100110  */
	0x49,	/*  01001001  */
	0x09,	/*  00001001  */
	0x06,	/*  00000110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  &         *//* 26 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x38,	/*  00111000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x28,	/*  00101000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x45,	/*  01000101  */
	0x42,	/*  01000010  */
	0x25,	/*  00100101  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  '         *//* 27 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  (         *//* 28 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  )         *//* 29 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  *         *//* 2A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x2A,	/*  00101010  */
	0x49,	/*  01001001  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  +         *//* 2B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ,         *//* 2C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  -         *//* 2D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  .         *//* 2E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x30,	/*  00110000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  /         *//* 2F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  0         *//* 30 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  1         *//* 31 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  2         *//* 32 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  3         *//* 33 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  4         *//* 34 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x0A,	/*  00001010  */
	0x0A,	/*  00001010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  5         *//* 35 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  6         *//* 36 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  7         *//* 37 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  8         *//* 38 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  9         *//* 39 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x23,	/*  00100011  */
	0x1D,	/*  00011101  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  :         *//* 3A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ;         *//* 3B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  <         *//* 3C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  =         *//* 3D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  >         *//* 3E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ?         *//* 3F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  @         *//* 40 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x19,	/*  00011001  */
	0x29,	/*  00101001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  A         *//* 41 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  B         *//* 42 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x3E,	/*  00111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  C         *//* 43 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  D         *//* 44 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x22,	/*  00100010  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x22,	/*  00100010  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  E         *//* 45 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  F         *//* 46 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  G         *//* 47 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  H         *//* 48 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  I         *//* 49 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  J         *//* 4A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1F,	/*  00011111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38,	/*  00111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  K         *//* 4B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x60,	/*  01100000  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  L         *//* 4C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  M         *//* 4D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x63,	/*  01100011  */
	0x55,	/*  01010101  */
	0x55,	/*  01010101  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  N         *//* 4E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x61,	/*  01100001  */
	0x51,	/*  01010001  */
	0x51,	/*  01010001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x45,	/*  01000101  */
	0x43,	/*  01000011  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  O         *//* 4F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  P         *//* 50 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Q         *//* 51 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x22,	/*  00100010  */
	0x1D,	/*  00011101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  R         *//* 52 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S         *//* 53 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  T         *//* 54 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  U         *//* 55 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  V         *//* 56 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  W         *//* 57 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  X         *//* 58 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Y         *//* 59 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Z         *//* 5A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  [         *//* 5B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  \         *//* 5C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ]         *//* 5D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ^         *//* 5E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  _         *//* 5F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  `         *//* 60 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  a         *//* 61 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  b         *//* 62 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  c         *//* 63 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  d         *//* 64 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  e         *//* 65 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  f         *//* 66 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x12,	/*  00010010  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  g         *//* 67 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C	/*  00111100  */
},
{			/*  h         *//* 68 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  i         *//* 69 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  j         *//* 6A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  k         *//* 6B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x70,	/*  01110000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  l         *//* 6C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  m         *//* 6D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  n         *//* 6E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  o         *//* 6F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  p         *//* 70 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40	/*  01000000  */
},
{			/*  q         *//* 71 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x01	/*  00000001  */
},
{			/*  r         *//* 72 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  s         *//* 73 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x30,	/*  00110000  */
	0x0C,	/*  00001100  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  t         *//* 74 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x12,	/*  00010010  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  u         *//* 75 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  v         *//* 76 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  w         *//* 77 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  x         *//* 78 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  y         *//* 79 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  z         *//* 7A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  {         *//* 7B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  |         *//* 7C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  }         *//* 7D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            *//* 7E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x06,	/*  00000110  */
	0x7F,	/*  01111111  */
	0x06,	/*  00000110  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            *//* 7F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x30,	/*  00110000  */
	0x7F,	/*  01111111  */
	0x30,	/*  00110000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},

{							/* 0x80 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00	/*  00000000  */
},
{							/* 0x81 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x82 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x83 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x84 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x85 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x86 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x87 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00	/*  00000000  */
},
{							/* 0x88 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x89 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x8F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x90 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x38,	/*  00111000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x91 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3F,	/*  00111111  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x3F,	/*  00111111  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x3F,	/*  00111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x92 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x07,	/*  00000111  */
	0x0C,	/*  00001100  */
	0x14,	/*  00010100  */
	0x24,	/*  00100100  */
	0x44,	/*  01000100  */
	0x7F,	/*  01111111  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x47,	/*  01000111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x93 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x94 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x95 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x96 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x97 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x98 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{							/* 0x99 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9A */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9B */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3F,	/*  00111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x3F,	/*  00111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9C */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x30,	/*  00110000  */
	0x51,	/*  01010001  */
	0x2E,	/*  00101110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9D */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9E */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x78,	/*  01111000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x78,	/*  01111000  */
	0x44,	/*  01000100  */
	0x5F,	/*  01011111  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0x9F */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x0A,	/*  00001010  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x28,	/*  00101000  */
	0x10,	/*  00010000  */
	0x00	/*  00000000  */
},
/*--------------------------*/
/* 0xA0 ～ 0xDF 未使用		*/
/* 全てスペース				*/
/*--------------------------*/
{							/* 0xA0 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA1 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA2 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA3 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA4 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA5 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA6 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA7 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA8 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xA9 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAA */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAB */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAC */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAD */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAE */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xAF */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB0 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB1 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB2 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB3 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB4 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB5 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB6 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB7 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB8 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xB9 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBA */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBB */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBC */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBD */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBE */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xBF */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC0 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC1 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC2 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC3 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC4 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC5 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC6 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC7 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC8 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xC9 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCA */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCB */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCC */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCD */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCE */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xCF */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD0 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD1 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD2 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD3 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD4 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD5 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD6 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD7 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD8 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xD9 */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDA */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDB */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDC */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDD */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDE */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xDF */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{							/* 0xE0 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x3C,      /*  00111100  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x3E,      /*  00111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x3D,      /*  00111101  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE1 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x18,      /*  00011000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE2 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE3 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x39,      /*  00111001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE4 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x30,      /*  00110000  */
   0x49,      /*  01001001  */
   0x06,      /*  00000110  */
   0x00,      /*  00000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE5 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x30,      /*  00110000  */
   0x49,      /*  01001001  */
   0x06,      /*  00000110  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x61,      /*  01100001  */
   0x51,      /*  01010001  */
   0x49,      /*  01001001  */
   0x45,      /*  01000101  */
   0x43,      /*  01000011  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE6 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x2A,      /*  00101010  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x2A,      /*  00101010  */
   0x1C,      /*  00011100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE7 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x2A,      /*  00101010  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x2A,      /*  00101010  */
   0x1C,      /*  00011100  */
   0x08,      /*  00001000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE8 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xE9 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x18,      /*  00011000  */
   0x24,      /*  00100100  */
   0x42,      /*  01000010  */
   0x44,      /*  01000100  */
   0x58,      /*  01011000  */
   0x44,      /*  01000100  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x4C,      /*  01001100  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40      /*  01000000  */
},
{							/* 0xEA */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xEB */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3E,      /*  00111110  */
   0x41,      /*  01000001  */
   0x40,      /*  01000000  */
   0x3E,      /*  00111110  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x3E,      /*  00111110  */
   0x01,      /*  00000001  */
   0x41,      /*  01000001  */
   0x3E,      /*  00111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xEC */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x7F,      /*  01111111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xED */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xEE */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xEF */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xF0 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x7E,      /*  01111110  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x7E,      /*  01111110  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x7E,      /*  01111110  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF1 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x7E,      /*  01111110  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x7E,      /*  01111110  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x7E,      /*  01111110  */ 
   0x42,      /*  01000010  */ 
   0x42,      /*  01000010  */ 
   0x82,      /*  10000010  */ 
   0x82,      /*  10000010  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF2 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x10,      /*  00010000  */ 
   0x92,      /*  10010010  */ 
   0x92,      /*  10010010  */ 
   0x92,      /*  10010010  */ 
   0x92,      /*  10010010  */ 
   0x10,      /*  00010000  */ 
   0x28,      /*  00101000  */ 
   0x28,      /*  00101000  */ 
   0x44,      /*  01000100  */ 
   0x44,      /*  01000100  */ 
   0x82,      /*  10000010  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF3 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x12,      /*  00010010  */ 
   0xF4,      /*  11110100  */ 
   0x38,      /*  00111000  */ 
   0x58,      /*  01011000  */ 
   0x54,      /*  01010100  */ 
   0x94,      /*  10010100  */ 
   0x12,      /*  00010010  */ 
   0x10,      /*  00010000  */ 
   0x30,      /*  00110000  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF4 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0xFE,      /*  11111110  */ 
   0x38,      /*  00111000  */ 
   0x54,      /*  01010100  */ 
   0x54,      /*  01010100  */ 
   0x92,      /*  10010010  */ 
   0x92,      /*  10010010  */ 
   0x92,      /*  10010010  */ 
   0x10,      /*  00010000  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF5 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x10,      /*  00010000  */ 
   0x28,      /*  00101000  */ 
   0x44,      /*  01000100  */ 
   0xFE,      /*  11111110  */ 
   0x92,      /*  10010010  */ 
   0x10,      /*  00010000  */ 
   0x7C,      /*  01111100  */ 
   0x10,      /*  00010000  */ 
   0x54,      /*  01010100  */ 
   0x38,      /*  00111000  */ 
   0xFE,      /*  11111110  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF6 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x7C,      /*  01111100  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0x10,      /*  00010000  */ 
   0xFE,      /*  11111110  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF7 */
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x40,      /*  01000000  */ 
   0x7E,      /*  01111110  */ 
   0x88,      /*  10001000  */ 
   0x08,      /*  00001000  */ 
   0x7C,      /*  01111100  */ 
   0x08,      /*  00001000  */ 
   0x48,      /*  01001000  */ 
   0x48,      /*  01001000  */ 
   0xFE,      /*  11111110  */ 
   0x08,      /*  00001000  */ 
   0x08,      /*  00001000  */ 
   0x00,      /*  00000000  */ 
   0x00,      /*  00000000  */ 
   0x00      /*  00000000  */ 
},
{							/* 0xF8 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x2C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xF9 */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x60,      /*  01100000  */
   0x90,      /*  10010000  */
   0x90,      /*  10010000  */
   0x60,      /*  01100000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFA */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x80,      /*  01000000  */
   0x40,      /*  00100000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFB */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x3E,      /*  00111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFC */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x32,      /*  00110010  */
   0x4C,      /*  01001100  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFD */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x32,      /*  00110010  */
   0x4C,      /*  01001100  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x7F,      /*  01111111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFE */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{							/* 0xFF */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x7f,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
}};
 #else
/*** USA_TOP */
/***********************************************************************
*	半角フォント JPN以外
************************************************************************/
CONST unsigned char far ByteFont[256][16] = {
{			/*  SPC 00    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 01    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 02    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 03    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 04    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S(短縮用) */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/* G(ｸﾞﾙｰﾌﾟ用)*/
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 07    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 08    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 09    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0A    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0B    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0C    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0D    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0E    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 0F    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 10    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x77,	/*  01110111  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00, 	/*  00000000  */
	0x00 	/*  00000000  */
},
{			/*  SPC 11    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  SPC 12    */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF	/*  11111111  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x0F,	/*  00001111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xFF,	/*  11111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0xF8,	/*  11111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
{			/*  SPC       */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  !         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  "         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  #         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x7F,	/*  01111111  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  $         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x14,	/*  00010100  */
	0x3E,	/*  00111110  */
	0x55,	/*  01010101  */
	0x54,	/*  01010100  */
	0x54,	/*  01010100  */
	0x3E,	/*  00111110  */
	0x15,	/*  00010101  */
	0x15,	/*  00010101  */
	0x55,	/*  01010101  */
	0x3E,	/*  00111110  */
	0x14,	/*  00010100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  %         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x49,	/*  01001001  */
	0x32,	/*  00110010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x26,	/*  00100110  */
	0x49,	/*  01001001  */
	0x09,	/*  00001001  */
	0x06,	/*  00000110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  &         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x38,	/*  00111000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x28,	/*  00101000  */
	0x30,	/*  00110000  */
	0x48,	/*  01001000  */
	0x45,	/*  01000101  */
	0x42,	/*  01000010  */
	0x25,	/*  00100101  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  '         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  (         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  )         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  *         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x2A,	/*  00101010  */
	0x49,	/*  01001001  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  +         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ,         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  -         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  .         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x30,	/*  00110000  */
	0x30,	/*  00110000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  /         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  0         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  1         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  2         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  3         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  4         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x0A,	/*  00001010  */
	0x0A,	/*  00001010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x7F,	/*  01111111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  5         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  6         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  7         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  8         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  9         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x23,	/*  00100011  */
	0x1D,	/*  00011101  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  :         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ;         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x0C,	/*  00001100  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  <         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  =         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  >         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ?         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  @         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x01,	/*  00000001  */
	0x19,	/*  00011001  */
	0x29,	/*  00101001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x2A,	/*  00101010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  A         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  B         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x3E,	/*  00111110  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  C         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  D         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x22,	/*  00100010  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x21,	/*  00100001  */
	0x22,	/*  00100010  */
	0x7C,	/*  01111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  E         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  F         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  G         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x4F,	/*  01001111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  H         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  I         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  J         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1F,	/*  00011111  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38,	/*  00111000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  K         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x60,	/*  01100000  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  L         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  M         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x63,	/*  01100011  */
	0x55,	/*  01010101  */
	0x55,	/*  01010101  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  N         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x61,	/*  01100001  */
	0x51,	/*  01010001  */
	0x51,	/*  01010001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x45,	/*  01000101  */
	0x43,	/*  01000011  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  O         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  P         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Q         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x22,	/*  00100010  */
	0x1D,	/*  00011101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  R         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7C,	/*  01111100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x42,	/*  01000010  */
	0x7C,	/*  01111100  */
	0x50,	/*  01010000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  S         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x1C,	/*  00011100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  T         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  U         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  V         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  W         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  X         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Y         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  Z         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x01,	/*  00000001  */
	0x01,	/*  00000001  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  [         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x1E,	/*  00011110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  \         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x7f,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ]         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  ^         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  _         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  `         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  a         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  b         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  c         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  d         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  e         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  f         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x12,	/*  00010010  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  g         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C	/*  00111100  */
},
{			/*  h         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  i         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  j         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x00,	/*  00000000  */
	0x06,	/*  00000110  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  k         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x48,	/*  01001000  */
	0x50,	/*  01010000  */
	0x70,	/*  01110000  */
	0x48,	/*  01001000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  l         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  m         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  n         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  o         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  p         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x62,	/*  01100010  */
	0x5C,	/*  01011100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40	/*  01000000  */
},
{			/*  q         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3A,	/*  00111010  */
	0x46,	/*  01000110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x01	/*  00000001  */
},
{			/*  r         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  s         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x30,	/*  00110000  */
	0x0C,	/*  00001100  */
	0x02,	/*  00000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  t         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x12,	/*  00010010  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  u         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  v         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  w         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  x         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  y         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
{			/*  z         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x40,	/*  01000000  */
	0x7E,	/*  01111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  {         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x0C,	/*  00001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  |         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*  }         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x06,	/*  00000110  */
	0x7F,	/*  01111111  */
	0x06,	/*  00000110  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
{			/*            */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x30,	/*  00110000  */
	0x7F,	/*  01111111  */
	0x30,	/*  00110000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},

/*--------------------------*/
/* 0x80 ～ 0x9F 未使用		*/
/* 全てスペース				*/
/*--------------------------*/
/* 0x80 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x81 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x82 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x83 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x84 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x85 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x86 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x87 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x88 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x89 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8A */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8B */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8C */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8D */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8E */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x8F */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x90 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x91 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x92 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x93 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x94 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x95 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0X96 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x97 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x98 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x99 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9A */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9B */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9C */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9D */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9E */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0x9F */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1E,	/*  00011110  */
	0x21,	/*  00100001  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x21,	/*  00100001  */
	0x1E,	/*  00011110  */
	0x0C,	/*  00001100  */
	0x02,	/*  00000010  */
	0x12,	/*  00010010  */
	0x0C	/*  00001100  */
},
/* 0xA1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x18,	/*  00011000  */
	0x04,	/*  00000100  */
	0x24,	/*  00100100  */
	0x18	/*  00011000  */
},
/* 0xA8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xA9 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAE */
{
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xAF */
{
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB0 */
{
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7C,	/*  01111100  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x09,	/*  00001001  */
	0x09,	/*  00001001  */
	0x3E,	/*  00111110  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x18,	/*  00011000  */
	0x28,	/*  00101000  */
	0x48,	/*  01001000  */
	0x4F,	/*  01001111  */
	0x48,	/*  01001000  */
	0x78,	/*  01111000  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x4F,	/*  01001111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB3 */
{
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB4 *//*小文字のｏ（ウムラウト）*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB5 */
{
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xB8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x3A,	/*  00111010  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x44,	/*  01000100  */
	0x38	/*  00111000  */
},
/* 0xB9 *//*大文字のＯ（ウムラウト）*/
{
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3E,	/*  00111110  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x3E,	/*  00111110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBA */
{
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBB */
{
#if (0)	/* ＬＣＤのフォントに合わせます（このフォントは、ＩＣＨＯとは別になります） by K.Watanabe 1998/11/04 */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x04,	/*  00000100  */
//	0x04,	/*  00000100  */
//	0x3C,	/*  00111100  */
//	0x4A,	/*  01001010  */
//	0x48,	/*  01001000  */
//	0x48,	/*  01001000  */
//	0x50,	/*  01010000  */
//	0x52,	/*  01010010  */
//	0x3C,	/*  00111100  */
//	0x20,	/*  00100000  */
//	0x20,	/*  00100000  */
//	0x00	/*  00000000  */
#endif
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3C,	/*  00111100  */
	0x4A,	/*  01001010  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x48,	/*  01001000  */
	0x4A,	/*  01001010  */
	0x3C,	/*  00111100  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00	/*  00000000  */
},
/* 0xBC */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x7C,	/*  01111100  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x30,	/*  00110000  */
	0x51,	/*  01010001  */
	0x2E,	/*  00101110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x7F,	/*  01111111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x78,	/*  01111000  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x78,	/*  01111000  */
	0x42,	/*  01000010  */
	0x47,	/*  01000111  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xBF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x0A,	/*  00001010  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x3E,	/*  00111110  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x28,	/*  00101000  */
	0x10,	/*  00010000  */
	0x00	/*  00000000  */
},
/* 0xC0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x60,	/*  01100000  */
	0x90,	/*  10010000  */
	0x90,	/*  10010000  */
	0x60,	/*  01100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7E,	/*  01111110  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0xFC,	/*  11111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x80,	/*  10000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},

/* 0xC5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC6 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x41,	/* 01000001 */
	0x21,	/* 00100001 */
	0x11,	/* 00010001 */
	0x7F,	/* 01111111 */
	0x11,	/* 00010001 */
	0x21,	/* 00100001 */
	0x41,	/* 01000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xC7 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x41,	/* 01000001 */
	0x42,	/* 01000010 */
	0x44,	/* 01000100 */
	0x7F,	/* 01111111 */
	0x44,	/* 01000100 */
	0x42,	/* 01000010 */
	0x41,	/* 01000001 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xC8 */
{			/*  \         */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x40,	/*  01000000  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x04,	/*  00000100  */
	0x02,	/*  00000010  */
	0x01,	/*  00000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xC9 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x05,	/* 00000101 */
	0x0A,	/* 00001010 */
	0x14,	/* 00010100 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xCA */
{			/*  Φ        */
/* 特に要求はありませんがイチョウにあわせます。*/
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x01,	/*  00000001  */
	0x3E,	/*  00111110  */
	0x43,	/*  01000011  */
	0x45,	/*  01000101  */
	0x45,	/*  01000101  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x51,	/*  01010001  */
	0x51,	/*  01010001  */
	0x61,	/*  01100001  */
	0x3E,	/*  00111110  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCB */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x3C,	/*  00111100  */
	0x46,	/*  01000110  */
	0x4A,	/*  01001010  */
	0x4A,	/*  01001010  */
	0x52,	/*  01010010  */
	0x62,	/*  01100010  */
	0x3C,	/*  00111100  */
	0x40,	/*  01000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCC */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x03,	/* 00000011 */
	0x05,	/* 00000101 */
	0x09,	/* 00001001 */
	0x11,	/* 00010001 */
	0x21,	/* 00100001 */
	0x41,	/* 01000001 */
	0x21,	/* 00100001 */
	0x11,	/* 00010001 */
	0x09,	/* 00001001 */
	0x05,	/* 00000101 */
	0x03,	/* 00000011 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00 	/* 00000000 */
},
/* 0xCD */
{
#if (0)	/* フォント修正（下端の定義間違いを修正 0x80 -> 0x60） by K.Watanabe 1998/10/21 */
//	0x00,	/* 00000000 */
//	0x00,	/* 00000000 */
//	0x60,	/* 01100000 */
//	0x50,	/* 01010000 */
//	0x48,	/* 01001000 */
//	0x44,	/* 01000100 */
//	0x42,	/* 01000010 */
//	0x41,	/* 01000001 */
//	0x42,	/* 01000010 */
//	0x44,	/* 01000100 */
//	0x48,	/* 01001000 */
//	0x50,	/* 01010000 */
//	0x80,	/* 01100000 */
//	0x00,	/* 00000000 */
//	0x00,	/* 00000000 */
//	0x00	/* 00000000 */
#endif
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x60,	/* 01100000 */
	0x50,	/* 01010000 */
	0x48,	/* 01001000 */
	0x44,	/* 01000100 */
	0x42,	/* 01000010 */
	0x41,	/* 01000001 */
	0x42,	/* 01000010 */
	0x44,	/* 01000100 */
	0x48,	/* 01001000 */
	0x50,	/* 01010000 */
	0x60,	/* 01100000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xCE */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0xA0,	/*  10100000  */
	0x50,	/*  01010000  */
	0x28,	/*  00101000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xCF */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x24,	/*  00100100  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD0 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x08,	/* 00001000 */
	0x1C,	/* 00011100 */
	0x2A,	/* 00101010 */
	0x49,	/* 01001001 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xD1 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x49,	/* 01001001 */
	0x2A,	/* 00101010 */
	0x1C,	/* 00011100 */
	0x08,	/* 00001000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xD2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x1C,	/*  00011100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD4 */
{
#if (0)	/* このフォントは小文字なので、元に戻します by K.Watanabe 1998/11/13 */
//#if (PRO_OKI == ENABLE)	/* フォント修正 by K.Watanabe 1998/10/20 */
//	0x02,	/*  00000010  */
//	0x04,	/*  00000100  */
//	0x08,	/*  00001000  */
//	0x3E,	/*  00111110  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x41,	/*  01000001  */
//	0x3E,	/*  00111110  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00	/*  00000000  */
//#else
#endif
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3C,	/*  00111100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
#if (0)	/* このフォントは小文字なので、元に戻します by K.Watanabe 1998/11/13 */
//#endif
#endif
},
/* 0xD5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x02,	/*  00000010  */
	0x04,	/*  00000100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x46,	/*  01000110  */
	0x39,	/*  00111001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x32,	/*  00110010  */
	0x4C,	/*  01001100  */
	0x00,	/*  00000000  */
	0x5C,	/*  01011100  */
	0x62,	/*  01100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD7 */
{
	0x32,	/*  00110010  */
	0x4C,	/*  01001100  */
	0x00,	/*  00000000  */
	0x41,	/*  01000001  */
	0x61,	/*  01100001  */
	0x51,	/*  01010001  */
	0x51,	/*  01010001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x45,	/*  01000101  */
	0x45,	/*  01000101  */
	0x43,	/*  01000011  */
	0x41,	/*  01000001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xD8 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3C,	/* 00111100 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x3E,	/* 00111110 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x3D,	/* 00111101 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xD9 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3C,	/* 00111100 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x3C,	/* 00111100 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xDA */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x1C	/*  00011100  */
},
/* 0xDB */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xDC */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xDD */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08	/*  00001000  */
},
/* 0xDE */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x05,	/* 00000101 */
	0x0A,	/* 00001010 */
	0x14,	/* 00010100 */
	0x28,	/* 00101000 */
	0x50,	/* 01010000 */
	0x28,	/* 00101000 */
	0x14,	/* 00010100 */
	0x0A,	/* 00001010 */
	0x05,	/* 00000101 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xDF */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x50,	/* 01010000 */
	0x28,	/* 00101000 */
	0x14,	/* 00010100 */
	0x0A,	/* 00001010 */
	0x05,	/* 00000101 */
	0x0A,	/* 00001010 */
	0x14,	/* 00010100 */
	0x28,	/* 00101000 */
	0x50,	/* 01010000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xE0 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x31,	/*  00110001  */
	0x4A,	/*  01001010  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x44,	/*  01000100  */
	0x4A,	/*  01001010  */
	0x31,	/*  00110001  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
},
/* 0xE1 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x42,	/*  00100010  */
	0x42,	/*  00100010  */
	0x00,	/*  00000000  */
	0x3C,	/*  00111100  */
	0x02,	/*  00000010  */
	0x02,	/*  00000010  */
	0x3E,	/*  00111110  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x3D,	/*  00111101  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE2*/
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x18,	/*  00011000  */
	0x24,	/*  00100100  */
	0x42,	/*  01000010  */
	0x44,	/*  01000100  */
	0x58,	/*  01011000  */
	0x44,	/*  01000100  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x4C,	/*  01001100  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE3 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3E,	/* 00111110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x3C,	/* 00111100 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x3E,	/* 00111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xE4 */
{
/* ﾌｫﾝﾄが15ﾊﾞｲﾄしかなかったのを修正（IBM_FONT[]を参照） by K.Watanabe 1999/03/11 */
#if (0)
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x00,	/*  00000000  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x22,	/*  00100010  */
//	0x3D,	/*  00111101  */
//	0x20,	/*  00100000  */
//	0x20,	/*  00100000  */
//	0x20,	/*  00100000  */
//	0x40,	/*  01000000  */
#endif
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x3D,	/*  00111101  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x20,	/*  00100000  */
	0x40	/*  01000000  */
},
/* 0xE5 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0C,	/*  00001100  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04,	/*  00000100  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x42,	/*  01000010  */
	0x24,	/*  00100100  */
	0x18,	/*  00011000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE6 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x0E,	/* 00001110 */
	0x11,	/* 00010001 */
	0x21,	/* 00100001 */
	0x61,	/* 01100001 */
	0x5E,	/* 01011110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xE7 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3F,	/* 00111111 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41 ,	/* 01000001 */
	0x41,	/* 01000001 */
	0x41,	/* 01000001 */
	0x3F,	/* 00111111 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x02,	/* 00000010 */
	0x7C,	/* 01111100 */
},
/* 0xE8 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x0F,	/*  00001111  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x08,	/*  00001000  */
	0x48,	/*  01001000  */
	0x28,	/*  00101000  */
	0x18,	/*  00011000  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xE9 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x7A,	/* 01111010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEA */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x00,	/* 00000000 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x02,	/* 00000010 */
	0x42,	/* 01000010 */
	0x44,	/* 01000100 */
	0x38	/* 00111000 */
},
/* 0xEB */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x44,	/* 01000100 */
	0x28,	/* 00101000 */
	0x10,	/* 00010000 */
	0x28,	/* 00101000 */
	0x44,	/* 01000100 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEC */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x3E,	/* 00111110 */
	0x48,	/* 01001000 */
	0x48,	/* 01001000 */
	0x49,	/* 01001001 */
	0x3E ,	/* 00111110 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x08,	/* 00001000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xED */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x7C,	/* 01111100 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x7C,	/* 01111100 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x20,	/* 00100000 */
	0x3F,	/* 00111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xEE */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x5C,	/* 01011100 */
	0x62,	/* 01100010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00 	/* 00000000 */
},
/* 0xEF */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x22,	/* 00100010 */
	0x22,	/* 00100010 */
	0x00,	/* 00000000 */
	0x22,	/* 00100010 */
	0x22,	/* 00100010 */
	0x00,	/* 00000000 */
	0x22,	/* 00100010 */
	0x22,	/* 00100010 */
	0x00,	/* 00000000 */
	0x22,	/* 00100010 */
	0x22,	/* 00100010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xF0 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x40,	/* 01000000 */
	0x5E,	/* 01011110 */
	0x61,	/* 01100001 */
	0x61,	/* 01100001 */
	0x60,	/* 01100001 */
	0x5E,	/* 01011110 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40,	/* 01000000 */
	0x40	/* 01000000 */
},
/* 0xF1 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000001 */
	0x3D,	/* 00111101 */
	0x43,	/* 01000011 */
	0x43,	/* 01000011 */
	0x43,	/* 01000011 */
	0x3D,	/* 00111101 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01,	/* 00000001 */
	0x01	/* 00000001 */
},
/* 0xF2 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x08,	/*  00001000  */
	0x14,	/*  00010100  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22 ,	/*  00100010  */
	0x3E,	/*  00111110  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x08,	/*  00001000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00 	/*  00000000  */
},
/* 0xF3 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x36,	/*  00110110  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x49,	/*  01001001  */
	0x36,	/*  00110110  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF4 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x1C,	/*  00011100  */
	0x22,	/*  00100010  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x41,	/*  01000001  */
	0x22,	/*  00100010  */
	0x14,	/*  00010100  */
	0x55,	/*  01010101  */
	0x77,	/*  01110111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF5 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x42,	/* 01000010 */
	0x3D,	/* 00111101 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xF6 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x7F,	/*  01111111  */
	0x41,	/*  01000001  */
	0x20,	/*  00100000  */
	0x10,	/*  00010000  */
	0x08,	/*  00001000  */
	0x04 ,	/*  00000100  */
	0x08,	/*  00001000  */
	0x10,	/*  00010000  */
	0x20,	/*  00100000  */
	0x41,	/*  01000001  */
	0x7F,	/*  01111111  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF7 */
{
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x3F,	/*  00111111  */
	0x52 ,	/*  01010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x12,	/*  00010010  */
	0x00,	/*  00000000  */
	0x00,	/*  00000000  */
	0x00	/*  00000000  */
},
/* 0xF8 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x3F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x41,	/* 01000001 */
	0x22,	/* 00100010 */
	0x14,	/* 00010100 */
	0x08,	/* 00001000 */
	0x14,	/* 00010100 */
	0x22,	/* 00100010 */
	0x41,	/* 01000001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xF9 */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x70,	/* 01110000 */
	0x70,	/* 01110000 */
	0x70,	/* 01110000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00 	/* 00000000 */
},
/* 0xFA */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x07,	/* 00000111 */
	0x07,	/* 00000111 */
	0x07,	/* 00000111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFB */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x70,	/* 01110000 */
	0x70,	/* 01110000 */
	0x70,	/* 01110000 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFC */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x07,	/* 00000111 */
	0x07,	/* 00000111 */
	0x07,	/* 00000111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFD */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00, 	/* 00000000 */
	0x18,	/* 00011000 */
	0x24,	/* 00100100 */
	0x24,	/* 00100100 */
	0x18,	/* 00011000 */
	0x00,	/* 00000000 */
	0x7E,	/* 01111110 */
	0x00,	/* 00000000 */
	0x18,	/* 00011000 */
	0x24,	/* 00100100 */
	0x24,	/* 00100100 */
	0x18,	/* 00011000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFE */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x21,	/* 00100001 */
	0x11,	/* 00010001 */
	0x09,	/* 00001001 */
	0x05,	/* 00000101 */
	0x03,	/* 00000011 */
	0x7F,	/* 01111111 */
	0x03,	/* 00000011 */
	0x05,	/* 00000101 */
	0x09,	/* 00001001 */
	0x11,	/* 00010001 */
	0x21,	/* 00100001 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
},
/* 0xFF */
{
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x7F,	/* 01111111 */
	0x00,	/* 00000000 */
	0x00,	/* 00000000 */
	0x00	/* 00000000 */
}};
 #endif
#endif

CONST UBYTE IBM_FONT[32*16*4] = {
/********************************************************************/
/* FIP FONT_TABLE 4													*/
/* 90/11/16															*/
/*																	*/
/* char far		ASC4_IBM[32*16] = [									*/
/********************************************************************/
			/*  80			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1E,	/*  00011110	*/
	0x21,	/*  00100001	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x21,	/*  00100001	*/
	0x1E,	/*  00011110	*/
	0x0C,	/*  00001100	*/
	0x02,	/*  00000010	*/
	0x12,	/*  00010010	*/
	0x0C,	/*  00001100	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x18,	/*  00011000	*/
	0x04,	/*  00000100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
#endif
			/*  81			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  82			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  83			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x1C,	/*  00011100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  84			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  85			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x40,	/*  01000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  86			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  87			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x18,	/*  00011000	*/
	0x04,	/*  00000100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x18,	/*  00011000	*/
	0x04,	/*  00000100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
#endif
			/*  88			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  89			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  8A			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x7E,	/*  01111110	*/
	0x40,	/*  01000000	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  8B			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  8C			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  8D			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  8E			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x7F,	/*  01111111	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x7F,	/*  01111111	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  8F			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x7F,	/*  01111111	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x7F,	/*  01111111	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  90			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x7F,	/*  01111111	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x7C,	/*  01111100	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x7E,	/*  01111110	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x38,	/*  00111000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x7E,	/*  01111110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  91			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x36,	/*  00110110	*/
	0x09,	/*  00001001	*/
	0x09,	/*  00001001	*/
	0x3E,	/*  00111110	*/
	0x48,	/*  01001000	*/
	0x48,	/*  01001000	*/
	0x36,	/*  00110110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3F,	/*  00111111	*/
	0x04,	/*  00000100	*/
	0x04,	/*  00000100	*/
	0x3F,	/*  00111111	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x3F,	/*  00111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  92			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x0F,	/*  00001111	*/
	0x18,	/*  00011000	*/
	0x28,	/*  00101000	*/
	0x48,	/*  01001000	*/
	0x4F,	/*  01001111	*/
	0x48,	/*  01001000	*/
	0x78,	/*  01111000	*/
	0x48,	/*  01001000	*/
	0x48,	/*  01001000	*/
	0x4F,	/*  01001111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x07,	/*  00000111	*/
	0x0C,	/*  00001100	*/
	0x14,	/*  00010100	*/
	0x24,	/*  00100100	*/
	0x44,	/*  01000100	*/
	0x7F,	/*  01111111	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x47,	/*  01000111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  93			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  94			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  95			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x40,	/*  01000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  96			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  97			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x40,	/*  01000000	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  98			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x3A,	/*  00111010	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x44,	/*  01000100	*/
	0x38,	/*  00111000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x3A,	/*  00111010	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x44,	/*  01000100	*/
	0x38,	/*  00111000	*/
#endif
			/*  99			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  9A			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x22,	/*  00100010	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x22,	/*  00100010	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  9B			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x04,	/*  00000100	*/
	0x04,	/*  00000100	*/
	0x3C,	/*  00111100	*/
	0x4A,	/*  01001010	*/
	0x48,	/*  01001000	*/
	0x48,	/*  01001000	*/
	0x50,	/*  01010000	*/
	0x52,	/*  01010010	*/
	0x3C,	/*  00111100	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x3F,	/*  00111111	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x3F,	/*  00111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  9C			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x10,	/*  00010000	*/
	0x10,	/*  00010000	*/
	0x7C,	/*  01111100	*/
	0x10,	/*  00010000	*/
	0x10,	/*  00010000	*/
	0x10,	/*  00010000	*/
	0x30,	/*  00110000	*/
	0x51,	/*  01010001	*/
	0x2E,	/*  00101110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  9D			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x22,	/*  00100010	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x7F,	/*  01111111	*/
	0x08,	/*  00001000	*/
	0x7F,	/*  01111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  9E			*/
#if (PRO_OKI == ENABLE)	/* フォント修正 By Y.Suzuki 1998/10/15 */
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x78,	/*  01111000	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x78,	/*  01111000	*/
	0x42,	/*  01000010	*/
	0x47,	/*  01000111	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#else
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x78,	/*  01111000	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x78,	/*  01111000	*/
	0x44,	/*  01000100	*/
	0x5F,	/*  01011111	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
#endif
			/*  9F			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x04,	/*  00000100	*/
	0x0A,	/*  00001010	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x3E,	/*  00111110	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x28,	/*  00101000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
/********************************************************************/
/* FIP FONT_TABLE 5													*/
/* 90/11/16															*/
/*																	*/
/* char far		ASC5_IBM[32*16] = [									*/
/********************************************************************/
			/*  A0			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A1			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A2			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A3			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x46,	/*  01000110	*/
	0x39,	/*  00111001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A4			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x30,	/*  00110000	*/
	0x49,	/*  01001001	*/
	0x06,	/*  00000110	*/
	0x00,	/*  00000000	*/
	0x5C,	/*  01011100	*/
	0x62,	/*  01100010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A5			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x41,	/*  01000001	*/
	0x61,	/*  01100001	*/
	0x51,	/*  01010001	*/
	0x49,	/*  01001001	*/
	0x45,	/*  01000101	*/
	0x43,	/*  01000011	*/
	0x41,	/*  01000001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A6			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x3E,	/*  00111110	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3D,	/*  00111101	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A7			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3C,	/*  00111100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7E,	/*  01111110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A8			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x10,	/*  00010000	*/
	0x20,	/*  00100000	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x22,	/*  00100010	*/
	0x1C,	/*  00011100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  A9			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3F,	/*  00111111	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AA			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7E,	/*  01111110	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AB			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x40,	/*  01000000	*/
	0x41,	/*  01000001	*/
	0x42,	/*  01000010	*/
	0x44,	/*  01000100	*/
	0x48,	/*  01001000	*/
	0x56,	/*  01010110	*/
	0x29,	/*  00101001	*/
	0x41,	/*  01000001	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x0F,	/*  00001111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AC			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x40,	/*  01000000	*/
	0x41,	/*  01000001	*/
	0x42,	/*  01000010	*/
	0x44,	/*  01000100	*/
	0x48,	/*  01001000	*/
	0x52,	/*  01010010	*/
	0x26,	/*  00100110	*/
	0x4A,	/*  01001010	*/
	0x12,	/*  00010010	*/
	0x1F,	/*  00011111	*/
	0x02,	/*  00000010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AD			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AE			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x09,	/*  00001001	*/
	0x12,	/*  00010010	*/
	0x24,	/*  00100100	*/
	0x48,	/*  01001000	*/
	0x24,	/*  00100100	*/
	0x12,	/*  00010010	*/
	0x09,	/*  00001001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  AF			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x48,	/*  01001000	*/
	0x24,	/*  00100100	*/
	0x12,	/*  00010010	*/
	0x09,	/*  00001001	*/
	0x12,	/*  00010010	*/
	0x24,	/*  00100100	*/
	0x48,	/*  01001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  B0			*/
	0x49,	/*  01001001	*/
	0x00,	/*  00000000	*/
	0x92,	/*  10010010	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x49,	/*  01001001	*/
	0x00,	/*  00000000	*/
	0x92,	/*  10010010	*/
	0x00,	/*  00000000	*/
	0x24,	/*  00100100	*/
	0x00,	/*  00000000	*/
	0x49,	/*  01001001	*/
	0x00,	/*  00000000	*/
	0x92,	/*  10010010	*/
	0x00,	/*  00000000	*/
			/*  B1			*/
	0x49,	/*  01001001	*/
	0x24,	/*  00100100	*/
	0x92,	/*  10010010	*/
	0x49,	/*  01001001	*/
	0x24,	/*  00100100	*/
	0x92,	/*  10010010	*/
	0x49,	/*  01001001	*/
	0x24,	/*  00100100	*/
	0x92,	/*  10010010	*/
	0x49,	/*  01001001	*/
	0x24,	/*  00100100	*/
	0x92,	/*  10010010	*/
	0x49,	/*  01001001	*/
	0x24,	/*  00100100	*/
	0x92,	/*  10010010	*/
	0x49,	/*  01001001	*/
			/*  B2			*/
	0x66,	/*  01100110	*/
	0x33,	/*  00110011	*/
	0x99,	/*  10011001	*/
	0xCC,	/*  11001100	*/
	0x66,	/*  01100110	*/
	0x33,	/*  00110011	*/
	0x99,	/*  10011001	*/
	0xCC,	/*  11001100	*/
	0x66,	/*  01100110	*/
	0x33,	/*  00110011	*/
	0x99,	/*  10011001	*/
	0xCC,	/*  11001100	*/
	0x66,	/*  01100110	*/
	0x33,	/*  00110011	*/
	0x99,	/*  10011001	*/
	0xCC,	/*  11001100	*/
			/*  B3			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  B4			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  B5			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  B6			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xF4,	/*  11110100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  B7			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFC,	/*  11111100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  B8			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  B9			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xF4,	/*  11110100	*/
	0x04,	/*  00000100	*/
	0xF4,	/*  11110100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  BA			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  BB			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFC,	/*  11111100	*/
	0x04,	/*  00000100	*/
	0xF4,	/*  11110100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  BC			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xF4,	/*  11110100	*/
	0x04,	/*  00000100	*/
	0xFC,	/*  11111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  BD			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xFC,	/*  11111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  BE			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  BF			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xF8,	/*  11111000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
/********************************************************************/
/* FIP FONT_TABLE 6													*/
/* 90/11/16															*/
/*																	*/
/* char far		ASC6_IBM[32*16] = [									*/
/********************************************************************/
			/*  C0			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  C1			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  C2			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  C3			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  C4			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  C5			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xFF,	/*  11111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  C6			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  C7			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x17,	/*  00010111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  C8			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x17,	/*  00010111	*/
	0x10,	/*  00010000	*/
	0x1F,	/*  00011111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  C9			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1F,	/*  00011111	*/
	0x10,	/*  00010000	*/
	0x17,	/*  00010111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  CA			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xF7,	/*  11110111	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  CB			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0xF7,	/*  11110111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  CC			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x17,	/*  00010111	*/
	0x10,	/*  00010000	*/
	0x17,	/*  00010111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  CD			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  CE			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xF7,	/*  11110111	*/
	0x00,	/*  00000000	*/
	0xF7,	/*  11110111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  CF			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  D0			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  D1			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  D2			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  D3			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x1F,	/*  00011111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  D4			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  D5			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  D6			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1F,	/*  00011111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  D7			*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0xFF,	/*  11111111	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
	0x14,	/*  00010100	*/
			/*  D8			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xFF,	/*  11111111	*/
	0x08,	/*  00001000	*/
	0xFF,	/*  11111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  D9			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0xF8,	/*  11111000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  DA			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  DB			*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
			/*  DC			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
			/*  DD			*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
	0xF0,	/*  11110000	*/
			/*  DE			*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
	0x0F,	/*  00001111	*/
			/*  DF			*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0xFF,	/*  11111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
/********************************************************************/
/* FIP FONT_TABLE 7													*/
/* 90/11/16															*/
/*																	*/
/* char far		ASC7_IBM[32*16] = [									*/
/********************************************************************/
			/*  E0			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x31,	/*  00110001	*/
	0x4A,	/*  01001010	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x44,	/*  01000100	*/
	0x4A,	/*  01001010	*/
	0x31,	/*  00110001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E1			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x24,	/*  00100100	*/
	0x42,	/*  01000010	*/
	0x44,	/*  01000100	*/
	0x58,	/*  01011000	*/
	0x44,	/*  01000100	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x4C,	/*  01001100	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
			/*  E2			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x21,	/*  00100001	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x70,	/*  01110000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E3			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x3F,	/*  00111111	*/
	0x52,	/*  01010010	*/
	0x12,	/*  00010010	*/
	0x12,	/*  00010010	*/
	0x12,	/*  00010010	*/
	0x12,	/*  00010010	*/
	0x12,	/*  00010010	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E4			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x41,	/*  01000001	*/
	0x20,	/*  00100000	*/
	0x10,	/*  00010000	*/
	0x08,	/*  00001000	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x10,	/*  00010000	*/
	0x20,	/*  00100000	*/
	0x41,	/*  01000001	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E5			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x02,	/*  00000010	*/
	0x04,	/*  00000100	*/
	0x3C,	/*  00111100	*/
	0x52,	/*  01010010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x3C,	/*  00111100	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E6			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x3D,	/*  00111101	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x20,	/*  00100000	*/
	0x40,	/*  01000000	*/
			/*  E7			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x03,	/*  00000011	*/
	0x34,	/*  00110100	*/
	0x48,	/*  01001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E8			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x2A,	/*  00101010	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x2A,	/*  00101010	*/
	0x1C,	/*  00011100	*/
	0x08,	/*  00001000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  E9			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x14,	/*  00010100	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x3E,	/*  00111110	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x14,	/*  00010100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  EA			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x41,	/*  01000001	*/
	0x22,	/*  00100010	*/
	0x14,	/*  00010100	*/
	0x55,	/*  01010101	*/
	0x77,	/*  01110111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  EB			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x0C,	/*  00001100	*/
	0x10,	/*  00010000	*/
	0x08,	/*  00001000	*/
	0x04,	/*  00000100	*/
	0x1C,	/*  00011100	*/
	0x22,	/*  00100010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x42,	/*  01000010	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  EC			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x36,	/*  00110110	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x36,	/*  00110110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  ED			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x04,	/*  00000100	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x2A,	/*  00101010	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x2A,	/*  00101010	*/
	0x1C,	/*  00011100	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x10,	/*  00010000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  EE			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1F,	/*  00011111	*/
	0x20,	/*  00100000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x7F,	/*  01111111	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x40,	/*  01000000	*/
	0x20,	/*  00100000	*/
	0x1F,	/*  00011111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  EF			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x5C,	/*  01011100	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x22,	/*  00100010	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x02,	/*  00000010	*/
	0x00,	/*  00000000	*/
			/*  F0			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F1			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x7F,	/*  01111111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F2			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x60,	/*  01100000	*/
	0x18,	/*  00011000	*/
	0x06,	/*  00000110	*/
	0x01,	/*  00000001	*/
	0x06,	/*  00000110	*/
	0x18,	/*  00011000	*/
	0x60,	/*  01100000	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F3			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x03,	/*  00000011	*/
	0x0C,	/*  00001100	*/
	0x30,	/*  00110000	*/
	0x40,	/*  01000000	*/
	0x30,	/*  00110000	*/
	0x0C,	/*  00001100	*/
	0x03,	/*  00000011	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x7F,	/*  01111111	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F4			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x06,	/*  00000110	*/
	0x09,	/*  00001001	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
			/*  F5			*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x48,	/*  01001000	*/
	0x30,	/*  00110000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F6			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
	0x7E,	/*  01111110	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F7			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x30,	/*  00110000	*/
	0x49,	/*  01001001	*/
	0x06,	/*  00000110	*/
	0x00,	/*  00000000	*/
	0x30,	/*  00110000	*/
	0x49,	/*  01001001	*/
	0x06,	/*  00000110	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F8			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x24,	/*  00100100	*/
	0x24,	/*  00100100	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  F9			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x08,	/*  00001000	*/
	0x1C,	/*  00011100	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FA			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x18,	/*  00011000	*/
	0x18,	/*  00011000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FB			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x0F,	/*  00001111	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x08,	/*  00001000	*/
	0x48,	/*  01001000	*/
	0x28,	/*  00101000	*/
	0x18,	/*  00011000	*/
	0x08,	/*  00001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FC			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x50,	/*  01010000	*/
	0x68,	/*  01101000	*/
	0x48,	/*  01001000	*/
	0x48,	/*  01001000	*/
	0x48,	/*  01001000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FD			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x30,	/*  00110000	*/
	0x48,	/*  01001000	*/
	0x10,	/*  00010000	*/
	0x20,	/*  00100000	*/
	0x78,	/*  01111000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FE			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x38,	/*  00111000	*/
	0x38,	/*  00111000	*/
	0x38,	/*  00111000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
			/*  FF			*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x1C,	/*  00011100	*/
	0x02,	/*  00000010	*/
	0x31,	/*  00110001	*/
	0x09,	/*  00001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x49,	/*  01001001	*/
	0x00,	/*  00000000	*/
	0x00,	/*  00000000	*/
	0x00	/*  00000000	*/
};
