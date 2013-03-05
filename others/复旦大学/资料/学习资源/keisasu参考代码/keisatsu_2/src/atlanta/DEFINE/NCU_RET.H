#ifndef ncu_rslt_h
    #define ncu_rslt_h

/*********************************************************************/
/*           ＲＩＣＥ　回線監視(NCU) 関数リターン値定義              */
/*                                                                   */
/*                                                                   */
/*                          1993/12/22                               */
/*                           坂本直史                                */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/* File :InternalCalling()                                           */
/*********************************************************************/
#define    CALL_STOP      				0
#define    COM_START      				1

/*********************************************************************/
/* File :DailInCompareDTMF()                                         */
/* File :InterCallCompareDTMF()                                      */
/*********************************************************************/
#define    D_IN_UNMATCH					0	/* D_IN */
#define    NO_MATCH_DTMF         		0	/* Inter*/ 
#define    D_IN_FAX						1	/* D_IN */
#define	   D_IN_TEL1					2	/* D_IN */
#define	   D_IN_TEL2					3	/* D_IN */
#define    INTER_CALL_DTMF       		4	/* Inter*/
#define    HOLD_TRNS_DTMF       	 	5	/* Inter*/
#define	   D_IN_TEL1_TEL2				6	/* D_IN */

/*********************************************************************/
/* File :CompareRingTone()                                           */
/*********************************************************************/
#define    NG_RING                      0
#define    OK_RING                      1

/*********************************************************************/
/* File :DetectRingTone()                                            */
/*********************************************************************/
#define    RING_NOT_AVAILABLE           0
#define    CALLED_REQUEST               1
#define    DETECT_F_NET                 2
#define    CALLED_REQUEST_EXT           3	/* 疑似２回線仕様 拡張ライン着信 by T.Soneoka 1997/11/21 */
#define    DETECT_CAR                   4	/* ナンバーディスプレイ対応 by H.Kubo 1998/07/23 */
#define    DETECT_FIRST_RING            5   /* ナンバーディスプレイ用 by H.Kubo 1998/09/18 */
#define    DETECT_IR_STOP               6   /* ナンバーディスプレイ対応 呼出音停止検出 by H.Kubo 1998/07/23 */

#define    NO_MATCH_RING                1



/*********************************************************************/
/* File :BRC_OnToOffHookLevelCheck()                                 */
/* File :BRC_OffToOnHookLevelCheck()                                 */
/* File :BRC_CMLAndOffHookLevelCheck()                               */
/*********************************************************************/
#define    NOISE                        0
#define    RELAY_ALL_OFF                1
#define    RELAY_ONE_ON                 2
#define    RELAY_TWO_ON                 3
#define    INTER_COM_DETECT_CI          4

/*********************************************************************/
/* File :GRS_DetectStopKeyInput()                                    */
/*********************************************************************/
#define    STOP                         0
#define    NOT_STOP                     1


/*----------------------------------------------------
#define    TELEPHONE_ONHOOK_END         0
#define    TELEPHONE_TO_FAX_TRANSFER    1
#define    TELEPHONE_HOLD_TIME          6000
#define    TELEPHONE_CML_OFF_TIME       100
#define    DIAL_IN_BELL_INTERVAL_TIME   3
#define    DIAL_IN_DTMF_RCV             0x0040
#define    DIAL_IN_DTMF_TIMEUP          0x0080
#define    DIAL_IN_BELL_TIMEUP          0x0100
#define    DIAL_IN_BELL_INTERVAL_TIMEUP 0x0200
#define    TEL_HOLD_SET                 0x0002
#define    SWITCH_OFF_HOOK              0x0004
#define    TEL_HOLD_RESET               0x0008
#define    TEL_HOOKING_SET              0x0010
#define    TEL_SWITCH_AFTER_HOOK        0x0020
#define    TEL_CML_OFF_TIMEUP           0x0040
#define    TEL_INPUT_DETECT             0x0080
#define    TEL_ONHOOKTEL_TIMEUP         0x1000
#define    TEL_ONHOOKTRANSFER_TIMEUP    0x2000
-------------------------------------------------------*/


/* ナンバーディスプレイ受信用  by H.Kubo 1998/10/21 */
#define 		ND_V23_DATA_RECEIVED			1
#define 		ND_V23_TONE_NOT_DETECTED		2
#define 		ND_V23_ABORT					3
#define 		ND_V23_RECEIVE_ERROR			5
#define 		ND_V23_ILLEGAL_FORMAT			4
#define			ND_V23_TONE_WITH_NO_DATA		6
#endif
