#include    "\src\atlanta\define\product.h"
#include    "\src\atlanta\define\ncu_def.h"
#include    "\src\atlanta\define\sysmax.h"

/*--------------------------------------------------------------------------------------------------------*/
/*  呼出信号検出パターン                                                                                  */
/*                                                                                                        */
/*	struct RingData_t {																					  */
/*		UWORD    MaxCycle;     CI最大周期				（単位　msec.  ）                         */
/*		UWORD    MinCycle;     CI最少周期				（単位　msec.  ）                         */
/*		UWORD    MinOnTime;    CI許容最少ON期間		（単位　10msec.）                         */
/*		UWORD    MaxOffTime;   CI許容最大OFF期間		（単位　10msec.）                         */
/*		UWORD    DetectTime;   信号監視期間			（単位　10msec.）                         */
/*		UWORD    ContinueTime; 連続ベル着信許可時間	（単位　10msec.）                         */
/*		UWORD    DoubleDetect; ダブルリング許容OFF期間（単位　10msec.）                         */
/*	};                                                                                                    */
/*--------------------------------------------------------------------------------------------------------*/
extern	struct	RingData_t	far	RingTime[];

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/07/02 */
extern CONST struct NCU_ND_CarPattern_t  NCU_ND_CarPattern;
extern CONST struct RingData_t 	NCU_ND_CarTime;
extern CONST UBYTE	NCU_ND_CarCounterThreshold;
#endif

/*	@if (PRO_RING_MASTER == ENABLE)		1996/06/11 By N.Sakamoto */
/*--------------------------------------------------------------------------------------------------------*/
/*	リングマスター呼出信号パターン                                                                        */
/*                                                                                                        */
/*	struct RingMaster_t {                                                                                   */
/*		UWORD		RingMinCycle[6--->10];		CI最小ON/OFF期間(単位 10msec)                             */
/*		UWORD		RingMaxCycle[6--->10];		CI最大ON/OFF期間(単位 10msec)                             */
/*	};                                                                                                    */
/*	                                                                                                      */
/*	RING_MASTER_PATTERN_A:		  80,    40,    80,   100,     0,     0                                   */
/*	RING_MASTER_PATTERN_D:		  40,    20,    40,    20,    80,   100                                   */
/*	RING_MASTER_PATTERN_B:		  30,    20,   100,    20,    30,   100                                   */
/*	RING_MASTER_PATTERN_C:		 100,    50,   100,    50,     0,     0                                   */
/*	RING_MASTER_PATTERN_E:		  50,    50,    50,    50,   100,     0                                   */
/*	RING_MASTER_PATTERN_F:		  50,    50,   100,    50,    50,     0                                   */
/*	RING_MASTER_PATTERN_G:		 150,    50,   150,   250,     0,     0                                   */
/*	RING_MASTER_PATTERN_H:		 150,    50,    50,   350,     0,     0                                   */
/*                                                                                                        */
/*--------------------------------------------------------------------------------------------------------*/
extern	struct	RingMaster_t	far	RingPattern[];
/*	@endif								1996/06/11 By N.Sakamoto */
/*--------------------------------------------------------------------------------------------------------*/
/*	ラベンダー擬似ベルON時間                                                                              */
/*                                                                                                        */
/*	char				BuzzerOnTime;		擬似ベル鳴動ON期間（単位 10msec）                                     */
/*                                                                                                        */
/*--------------------------------------------------------------------------------------------------------*/
extern char far	BuzzerOnTime;
/*--------------------------------------------------------------------------------------------------------*/
/*	外付ＴＡＤ 検出ノイズの無視する個数                                                                   */
/*                                                                                                        */
/*	unsigned	char	NoiseLimit;			無視するノイズの個数                                          */
/*                                                                                                        */
/*--------------------------------------------------------------------------------------------------------*/
extern unsigned char far NoiseLimit;
/*--------------------------------------------------------------------------------------------------------*/
/*	擬似ＲＢＴ送出パターン                                                                                */
/*                                                                                                        */
/*	struct RingBackToneData_t {                                                                             */
/*		WORD     OnTime;                  擬似RBT  ON  期間                                                */
/*		WORD     OffTime;                 擬似RBT  OFF 期間                                                */
/*		char    ModulatedFrequencyFlag;  16Hz 変調  の有(1)無(0)                                          */
/*		char    DoubleRingFlag;          Double Ringの有(1)無(0)                                          */
/*		WORD     DoubleRingOnTimeCount;   Double Ring ON 期間内の ON 期間                                  */
/*		WORD     DoubleRingOffTimeCount;  Double Ring ON 期間内の OFF期間                                  */
/*	};                                                                                                    */
/*--------------------------------------------------------------------------------------------------------*/
extern 	struct	RingBackToneData_t	far	RBT;


/* REMOTE_RX_FUNC オンフック転送ROMスイッチ 2003/01/28 by T.Soneoka */
extern 	CONST BYTE	 EnableRemoteTransferOnHook;
