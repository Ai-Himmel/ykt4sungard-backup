#ifndef evttomsg_h
    #define evttomsg_h
/***********************************************************************
*          BY:   H.Yoshikawa
*        DATE:   Mar.28,1994
*        TYPE:   STRUCT DEFINE
* VAR TO HOLD:
* DESCRIPTION:   イベントをメッセージに変換するタスクとのメッセージ型
************************************************************************/
struct EventToMessageData_t {
    UWORD DetEventNo;
    UWORD SendMBX;
    WORD  ReturnValue;
};
#endif
