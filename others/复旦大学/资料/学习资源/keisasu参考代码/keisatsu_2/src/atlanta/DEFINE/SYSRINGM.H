/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\sysringm.h */
#ifndef sysringm_h
	#define sysringm_h

#include	"\src\atlanta\define\ncu_cnst.h"

/************************************************************************
 * リングマスターパターン自動検出機能									*
 * 95/5/25																*
 * T.Hiraoka															*
 ************************************************************************/
struct SubRingMaster_t {
	UWORD RingMinCycle[BUFF_MAX];		/* 検出したリングの最少パターン */	/*BUFF_MAX=10 '96,03,22 ByN.S. */
	UWORD RingMaxCycle[BUFF_MAX];		/* 検出したリングの最大パターン */
};

#if (0) /* '96,03,22 By N.S. */
struct SubRingMaster_t {
	UWORD RingMinCycle[6];		/* 検出したリングの最少パターン */
	UWORD RingMaxCycle[6];		/* 検出したリングの最大パターン */
};
#endif	/* '96,03,22 By N.S. */

#endif
