/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\NCU_CNST.h */
#ifndef ncu_cnst_def_h
    #define ncu_cnst_def_h

#define    MIN                              1
#define    MAX_MIN                          2
#define    OFF_TIME                         3

#define    OFF                              0
#define    ON                               1

/*
#define    INTER_CI_NOT_DETECT              0
#define    INTER_CI_ON_TIME                 1
#define    INTER_CI_OFF_TIME                2
*/
#define    HOLD_TIME_MAX                    5
#define	   GENERAL_RING_OFF_HOOK_MAX        5

#define	   DETECT_OH_CHANGE_DELAY_MAX       2	/* 5	Changed by TH92115 1995/01/09 */
#define    LINE_VOLT_CATACLYSM_CYCLE      100	/* NOT USE */
#define	   DETECT_INTER_CI_DELAY_MAX        3	/* NOT USE */	/* 2	Changed by TH92115 1994/09/09 */

/* #if (PRO_CPU == V53) || (PRO_CPU == SH704X) || (PRO_CPU == SH7034) */
#if (PRO_CPU == SH7043)
#define    DRAW_LINE_LEVEL                  6	/* NOT USE */
#else
#define    DRAW_LINE_LEVEL                  8	/* NOT USE */	/* 3	Changed by TH92115 1994/08/11 */
#endif

#define    LINE_LEVEL_MAX                 100	/* Add by TH92115 1995/01/17 */

#define	   BRC_OH_COUNTER_MAX              89	/* Add by TH92115 1995/01/07 */

#define	   BRC_CI_PROTECT                0x01	/* Add by TH92115 1995/03/03 */
#define	   BRC_TRNS_PROTECT              0x02	/* Add by TH92115 1995/03/10 */
/*										 0x04						  未使用 */
#define	   BRC_TRNS_PBX                  0x08	/* Add by TH92115 1995/03/31 */

#define    TIME_UP                          0

#define    SILENT_TIME_UP                   1
#define    CNG_SILENT_TIME_UP               2
#define    CNG_TIME_UP                      3

#define    DTMF_MAX                         5
#define    INTER_DTMF_MAX                   2

#define    DIAL_IN_UNMATCH          		0
#define    DIAL_IN_FAX              		1
#define	   DIAL_IN_TEL1						2
#define    DIAL_IN_TEL2						3
#define	   DIAL_IN_OFF_HOOK					4
#define    DIAL_IN_TEL_TIMEU        		5
#define    DIAL_IN_TEL1_TEL2				6	/* QAT1 1994/07/14 by TH92115 */
#define    DIAL_IN_STOP						7	/* '94,07,27 By N.S. */
#define    DIAL_IN_CLASS1_CALL				8	/* ダイヤルイン対応 PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
 #define    DIAL_IN_FAX_FOR_DOC_STORE		9	/* 原稿蓄積中に２次応答を待たせる added by H.Hirao 1998/12/28 */
#endif
#define    BUFF_MAX                         10		/* '96,03,22 By N.S. */
/*#define    BUFF_MAX                         6		   '96,03,22 By N.S. */

#define    ALL_TEL_RINGING					0
#define    TEL1_RINGING						1
#define    TEL2_RINGING						2
#define    DEFAULT							3

#define    FCM_TxRx							0
#define    TRNS_RX							1

/* ナンバーディスプレイ用 */
#define 	NCU_CAR_TO_1ST_RESPONSE_TIMER	(600 - 20) /* 情報端末起動信号開始から一次応答までのタイマー  by H.Kubo 1998/10/15 */
#define		NCU_ND_DATA_TIMER				500 /* 一次応答からのタイマー 5 秒 by H.Kubo 1998/10/06 */
#define		NCU_ND_DIALIN_DATA_TIMER		800 /* 一次応答からのタイマー 8 秒 by H.Kubo 1998/10/06 */

#define		ND_DATA_END_TO_2ND_RES_TIME		(60 + 20)  /* V23 データ終了から二次応答までの時間 by H.Kubo 1998/10/06 */
#define 	ND_ACC_TO_2ND_RES_TIME			(30 + 20)  /* 受信応答送出からから二次応答までの時間 by H.Kubo 1998/10/06 */

#define		ND_RX_RESPONSE_TIMER			(700 - 20) /* V23 信号終了から V23 受信完了信号を送出するまでの最大時間 */
#define		ND_DIALIN_RX_RESPONSE_TIMER		(200 - 20) /* V23 信号終了から V23 受信完了信号を送出するまでの最大時間 */

#define		ND_IR_STOP_DETECTION_TIMER		250		/* ND 情報受信後の呼出し音の停止検出タイマー */
#endif
