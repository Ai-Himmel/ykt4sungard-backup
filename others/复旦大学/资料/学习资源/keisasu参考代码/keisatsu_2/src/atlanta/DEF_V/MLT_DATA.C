/*------------------------------------------------------------------*/
/* オプションボード用ＲＡＭ定義										*/
/* 領域は、ＰＡＴ用ＳＲＡＭにマッピングします						*/
/* よって、セグメントが従来のＳＲＡＭと異なりますので				*/
/* Ｆａｒアクセスとなります。注意してください。						*/
/* By O.Kimoto 1996/11/15											*/
/*------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\sysdial.h"
#include "\src\atlanta\define\sysjrnl.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\dpr_def.h"


#pragma section MULTI_DATA

/************************************************************************
 * T30モニタ(オプションボード用Ｔ３０モニターバッファ)					*
 * "\src\atlanta\define\syst30.h"										*
 * 1996/11/15															*
 * 木元　修																*
 ************************************************************************/
struct	SYS_T30MonitorData_t SYS_OptionT30Monitor = {0};

/* 以下はＲ２８８Ｆの内部ステータスプリント用バッファです。
** By O.Kimoto 1996/04/19
*/
struct	ModemInternalStatusTable_def R288F_InternalStatus[MODEM_STATUS_TABLE_MAX] = {0};	/** モデム内部遷移ステータス用テーブル **/
struct	DPR_ModemInternalStatusTable_t OPT_InternalStatus[MODEM_STATUS_TABLE_MAX] = {0};

/************************************************************************
 * 電話番号展開用バッファー												*
 * 96/12/1																*
 * O.Kimoto																*
 ************************************************************************/
struct	DialingData_t   OPT_DialingNumber = {0};

/************************************************************************
 * 回線選択処理に使用するテンポラリーバッファ							*
 * 96/12/2																*
 * O.Kimoto																*
 ************************************************************************/
 UBYTE OPT_JugdeLineElement[SYS_OPTION_BOARD_MAX] = {0};

/************************************************************************
 * オプションモデムデータ転送用バッファ									*
 * \src\atlanta\define\SYS_OPT.h: struct SYS_OptionModemData			*
 * 96/12/09																*
 * Y.Murata																*
 ************************************************************************/
struct SYS_OptionModemData_t SYS_Opt[SYS_OPTION_BOARD_MAX] = {0};

/************************************************************************
 * オプションモデムＰＡＴジャーナルイメージ展開用バッファ				*
 * 1996/12/16															*
 * Y.Murata																*
 ************************************************************************/
UBYTE PAT_Journal2ndImageBuffer[16][80] = {0};
struct SYS_JournalData_t	PAT_Journal2ndWorkFile = {0};
struct SYS_OptionModemTimeData_t SYS_OptionModemTime[SYS_OPTION_BOARD_MAX] = {0};

/*----------------------------------------*/
/* マルチ回線用Ｔ３０インデックス／タイプ */
/*----------------------------------------*/
UBYTE MLT_T30Index[SYS_OPTION_BOARD_MAX] = {0};
UBYTE MLT_T30Type[SYS_OPTION_BOARD_MAX] = {0};

/************************************************************************
 * オプションモデムＰＡＴジャーナルイメージ展開用バッファ				*
 * 1997/04/13															*
 * Y.Murata																*
 ************************************************************************/
UBYTE PAT_Journal2ndImageToMH_Buf[16][80] = {0};

/* 1998/02/03 Y.Murata	CHAR_JOURNAL
 * キャラクタジャーナル記載用
*/
struct SYS_OptionModemData2_t SYS_Opt2[SYS_OPTION_BOARD_MAX] = {0};


/* End Of File */
#pragma section
