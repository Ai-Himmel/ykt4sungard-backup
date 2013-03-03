/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\timer10.h */
#ifndef timer10_h
    #define timer10_h
/***********************************************************************
*          BY:   H.Yoshikawa
*        DATE:   Nov.01,1993
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   ﾀｲﾏｰﾀｽｸとのﾒｯｾｰｼﾞ送信／受信時のﾒｯｾ-ｼﾞの型
************************************************************************/
struct Timer10msData_t {
    UWORD Time;
    UWORD SendMBX;
    WORD  ReturnValue;
};
/***********************************************************************
*          BY:   A.Okumura
*        DATE:   Apr.13,1994
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   ﾀｲﾑｱｯﾌﾟ後にﾀｲﾏｰﾀｽｸが発生するｲﾍﾞﾝﾄの型
************************************************************************/
struct Timer10msEventData_t {
    UWORD Time;
    WORD  Event;
};
/***********************************************************************
*          BY:   T.Nose
*        DATE:   1996/11/19
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   複数のタイマーを管理するキューテーブル
************************************************************************/
struct Timer10msQueueData_t {
    UWORD	Time;
    UWORD	SendMBX;
    WORD	ReturnValue;
	UBYTE	Link;
	UBYTE	*TimerID;
};
#endif

