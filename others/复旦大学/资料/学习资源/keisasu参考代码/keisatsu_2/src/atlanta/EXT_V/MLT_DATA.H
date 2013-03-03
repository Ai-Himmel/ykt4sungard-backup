/*------------------------------------------------------------------*/
/* オプションボード用ＲＡＭ定義										*/
/* 領域は、ＰＡＴ用ＳＲＡＭにマッピングします						*/
/* よって、セグメントが従来のＳＲＡＭと異なりますので				*/
/* Ｆａｒアクセスとなります。注意してください。						*/
/* By O.Kimoto 1996/11/15											*/
/*------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdial.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\sysjrnl.h"
#include "\src\atlanta\define\dpr_def.h"

/************************************************************************
 * T30モニタ(オプションボード用Ｔ３０モニターバッファ)					*
 * "\src\atlanta\define\syst30.h"										*
 * 1996/11/15															*
 * 木元　修																*
 ************************************************************************/
extern struct	SYS_T30MonitorData_t SYS_OptionT30Monitor;

/* 以下はＲ２８８Ｆの内部ステータスプリント用バッファです。
** By O.Kimoto 1996/04/19
*/
extern struct ModemInternalStatusTable_def R288F_InternalStatus[MODEM_STATUS_TABLE_MAX];
extern struct DPR_ModemInternalStatusTable_t OPT_InternalStatus[MODEM_STATUS_TABLE_MAX];

/************************************************************************
 * 電話番号展開用バッファー												*
 * 96/12/1																*
 * O.Kimoto																*
 ************************************************************************/
extern struct	DialingData_t   OPT_DialingNumber;

/************************************************************************
 * 回線選択処理に使用するテンポラリーバッファ							*
 * 96/12/2																*
 * O.Kimoto																*
 ************************************************************************/
 extern UBYTE OPT_JugdeLineElement[SYS_OPTION_BOARD_MAX+1];

/************************************************************************
 * オプションモデムデータ転送用バッファ									*
 * \src\atlanta\define\SYS_OPT.h: struct SYS_OptionModemData			*
 * 96/12/09																*
 * Y.Murata																*
 ************************************************************************/
extern struct SYS_OptionModemData_t SYS_Opt[SYS_OPTION_BOARD_MAX];

/************************************************************************
 * オプションモデムＰＡＴジャーナルイメージ展開用バッファ				*
 * 1996/12/16															*
 * Y.Murata																*
 ************************************************************************/
extern UBYTE PAT_Journal2ndImageBuffer[16][80];
extern struct SYS_JournalData_t	PAT_Journal2ndWorkFile;
extern struct SYS_OptionModemTimeData_t SYS_OptionModemTime[SYS_OPTION_BOARD_MAX];

/*----------------------------------------*/
/* マルチ回線用Ｔ３０インデックス／タイプ */
/*----------------------------------------*/
extern UBYTE MLT_T30Index[SYS_OPTION_BOARD_MAX];
extern UBYTE MLT_T30Type[SYS_OPTION_BOARD_MAX];

/************************************************************************
 * オプションモデムＰＡＴジャーナルイメージ展開用バッファ				*
 * 1997/04/13															*
 * Y.Murata																*
 ************************************************************************/
extern UBYTE PAT_Journal2ndImageToMH_Buf[16][80];

/* 1998/02/03 Y.Murata	CHAR_JOURNAL
 * キャラクタジャーナル記載用
*/
extern struct SYS_OptionModemData2_t SYS_Opt2[SYS_OPTION_BOARD_MAX];

