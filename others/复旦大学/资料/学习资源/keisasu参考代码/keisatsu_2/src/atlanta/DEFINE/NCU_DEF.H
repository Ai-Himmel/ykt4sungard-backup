/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\ncu_def.h */
#ifndef ncu_data_h
    #define ncu_data_h

#include	"\src\atlanta\define\ncu_cnst.h"

struct RingData_t {
    UWORD MaxCycle;
    UWORD MinCycle;
    UWORD MinOnTime;
    UWORD MaxOffTime;
    UWORD DetectTime;
    UWORD ContinueTime;
    UWORD DoubleDetect;
};

/* @if (PRO_RING_MASTER == ENABLE)	1996/06/11 By N.Sakamoto */
struct RingMaster_t {
	UWORD RingMinCycle[BUFF_MAX];	/*BUFF_MAX=10 '96,03,22 ByN.S. */
	UWORD RingMaxCycle[BUFF_MAX];
};
	#if (0) /* '96,03,22 By N.S. */
struct RingMaster_t {
	UWORD RingMinCycle[6];
	UWORD RingMaxCycle[6];
};
	#endif /* '96,03,22 By N.S. */
/*	@endif								1996/06/11 By N.Sakamoto */

struct NoiseData_t {
    UWORD  SendMBX;
    WORD   ReturnValue;
};

struct BranchTelephoneData_t {
    UBYTE OnOffHookLevel;
    UBYTE CurrentLoopLevel;
    UBYTE CiInputLevel;
    UBYTE TADOffHookLevel;
};

/**********************************************************************************
*             BY: N.Sakamoto
*           DATE: Fri. 24 Jun. 1994
*           TYPE:   STRUCT DEFINE
*    Module Name: 擬似ベル鳴動データ
*           NOTE:
***********************************************************************************/
struct GenerateRingData_t {
	WORD 		SendMBX;
	UWORD		StartTime;
	UWORD		RingingTel;
};
/**********************************************************************************
*             BY: N.Sakamoto
*           DATE: Wen. 19 Jan. 1994
*           TYPE:   STRUCT DEFINE
*    Module Name: 擬似リング・バックトーン鳴動パターン
*           NOTE:
*                 RBT Off期間を変更する場合は、ncudata.c を変更
*
*	              DoubleRingOnTimeCount / DoubleRingOffTimeCountの値に付いて
*
*                     ModulatedFrequencyFlag = 1 の場合　60msec単位のｶｳﾝﾄ数で入力
*                     ModulatedFrequencyFlag = 0 の場合　msec単位の時間で入力
*
***********************************************************************************/
struct RingBackToneData_t {
	WORD     OnTime;                  /**         RBT  On  期間           **/
	WORD     OffTime;                 /**         RBT  Off 期間           **/
	BYTE     ModulatedFrequencyFlag;  /**        16Hz 変調の有無          **/
	BYTE     DoubleRingFlag;          /**       Double Ringの有無         **/
	WORD     DoubleRingOnTimeCount;   /** Double Ring On 期間内の On 期間 **/
	WORD     DoubleRingOffTimeCount;  /** Double Ring On 期間内の Off期間 **/
};


/*********************************************************************************
*             BY: H.Kubo
*           DATE: 1998/07/23
*           TYPE:   STRUCT DEFINE
*    Module Name: ナンバーディスプレイ・着信前情報通知の CAR 信号の検知パターン
*           NOTE:
*********************************************************************************/


struct NCU_ND_CarPattern_t {
	UBYTE	MinOnTime;			/* オン期間の下限値*/
	UBYTE	MaxOnTime;			/* オン期間の上限値*/
	UBYTE	MinOffTime;			/* オフ期間の下限値*/
	UBYTE	MaxOffTime;			/* オフ期間の上限値*/
	UBYTE	MinOnOffTime;		/* オンオフ合わせた期間の下限値 */
	UBYTE	MaxOnOffTime;		/* オンオフ合わせた期間の上限値 */
};

#endif
