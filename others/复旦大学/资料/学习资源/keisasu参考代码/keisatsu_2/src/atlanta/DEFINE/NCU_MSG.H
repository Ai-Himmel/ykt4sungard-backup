#ifndef ncu_msg_h
    #define ncu_msg_h

/*****************************************************/
/** NCU_MAIN/NCU_TEL/NCU_D_IN  Main Receive Message **/
/*****************************************************/
/*
#define	FROM_NCU_MAIN			16
#define	FROM_NCU_TEL			17
#define	FROM_NCU_D_IN			18
*/
        #define    OK_EXIT                           1
        #define    OK_CONT                           2

    #define    FROM__NCU_SUB     1

        #define    DETECT_TEL1_OFF_HOOK              3
        #define    DETECT_TEL2_OFF_HOOK              4
        #define    DETECT_BRC_TEL_OFF_HOOK           5
        #define    DETECT_TEL1_ONHOOK                6
        #define    DETECT_TEL2_ONHOOK                7
        #define    DETECT_BRC_TEL_ONHOOK             8
        #define    DETECT_INPUT_HOOK_KEY             9
        #define    DETECT_INPUT_HOLD_KEY            10
        #define    DETECT_INPUT_STOP_KEY            11
        #define    DETECT_INPUT_TEL_NO              12
        #define    DETECT_INTER_CI                  13
        #define    DETECT_INTER_CI_TIMEUP           14
        #define    DETECT_INTER_CI_CALLED_REQUEST   15
        #define    DETECT_TEL2_INTER_CALLING_START  16
        #define    DETECT_TEL2_HOLD_TRANSFER_START  17
        #define	   DETECT_D_IN_DTMF_RCV				18
		#define    DETECT_D_IN_UNMATCH              19
		#define    DETECT_D_IN_FAX                  20
		#define	   DETECT_D_IN_TEL1					21
		#define	   DETECT_D_IN_TEL2					22
		#define	   DETECT_D_IN_TEL1_TEL2			23	/* QAT1 1994/07/14 by TH92115 */
		#define	   DETECT_REMOTE_RX_SIGNAL			55	/* 1998/01/24  By T.Yamaguchi */
		#define    DETECT_D_IN_PC					58  /* PRO_CL1_TELFAX_LAN 対応 S.Fukui Jun 19,1998 */
		#define	   DETECT_ND_OH_1ST_RESPONSE		66  /* ナンバーディスプレイ外付け ND 電話の一次応答検出 by H.Kubo 1998/10/22 */
		#define	   IGNORE_ND_INFO_ARRIVAL			67 /*ナンバーディスプレイ情報受信するも無視して応答ださず。 by H.Kubo 1998/11/21 */
/*
    #define    FROM_MAIN         2
*/
    #define    FROM__NCU_RING    3

        #define    DETECT_CI                        24
        #define    DETECT_CI_TIMEUP                 25
        #define    DETECT_CALLED_REQUEST            26
        #define    DETECT_F_NET_CALLED_SIGNAL       27
        #define    DETECT_RING                      50	/* For CLASS1 Add By Y.Tanimoto 96.04.08 */
        #define    DETECT_CALLED_REQUEST_EXT        51	/* 疑似２回線 拡張ライン着信 by T.Soneoka 1997/11/21 */
        #define    DETECT_F_NET_CALLED_SIGNAL_EXT   52	/* 疑似２回線 拡張ラインF網着信 by T.Soneoka 1997/11/21 */
        #define    IGNORE_RING                      57	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
		#define    DETECT_ND_CAR_CALLED_SIGNAL		59	/* ナンバーディスプレイ情報受信端末起動信号検出 by H.Kubo 1998/06/30 */
		#define    DETECT_ND_NUMBER			        60	  /* ナンバーディスプレイの発信者番号検出 by H.Kubo 1998/10/12 */
		#define    DETECT_2ND_RING					61  /* ナンバーディスプレイ情報受信後呼び出し音検出 by H.Kubo 1998/10/12 */
		#define    FAIL_ND_NUMBER_RX				62
		#define    DETECT_2ND_RING_TIMEUP			63
		#define    MADE_ND_RX_RESPONSE				64 /* ナンバーディスプレイ情報受信応答終了 by H.Kubo 1998/10/13 */
		#define    DETECT_MODEM_DIALIN_FAX_CALL		65 /* モデムダイヤルイン着信  by H.Kubo 1998/10/14 */
		#define	   DETECT_CALLED_REQUEST_ND			68 /* ナンバーディスプレイで着信検出 by H.Kubo 1999/02/26 */

    #define    FROM__NCU_TEL     4

        #define    DETECT_TRANSFER_RECEIVE          28
        #define    DETECT_TRANSFER66                29
        #define    DETECT_HOLD_1_SEC_PASS           30
        #define    DETECT_HOLD_TIMEUP               31
        #define    DETECT_ON_HOOK_MANAGE_END        32
        #define    DETECT_BRN_ON_HOOK_MANAGE_END    33
        #define    DETECT_INTER_CALLING_STOP        34
        #define    DETECT_INTER_COM_START           35
        #define    DETECT_INTER_COM_END             36
        #define    DETECT_THREE_PARTIES_COM_END     37
        #define    DETECT_TRANSFER_RECEIVE1         53	/* 疑似２回線 拡張ライン着信 by T.Soneoka 1997/11/29 */
        #define    DETECT_TRANSFER_RECEIVE2         54	/* 疑似２回線 拡張ライン着信 by T.Soneoka 1997/11/29 */

	#define    FROM__NCU_D_IN	 5

		#define	   DETECT_D_IN_DSE					38

    #define    FROM__NCU_TAD     6

        #define    DETECT_TAD_CNG_OR_SILENT        	39
        #define    DETECT_TAD_TIMEUP          		40
        #define    DETECT_SILENT                    41
        #define    DETECT_REMOTE_DTMF               42

/*
#define	FROM_BUILTIN_TAD			19
*/
        #define    BUILTIN_TAD_OPR_END              43
        #define    BUILTIN_TAD_COM_END              44
        #define    BUILTIN_TAD_COM_END_FAX          45
        #define    BUILTIN_TAD_COM_END_RMTFAX       46
        #define    BUILTIN_TAD_LCD_CHANGE			47
        
/*
#define FROM_10MS_TIMER				27
*/
		#define	   DETECT_D_IN_DTMF_RCV_TIMEUP      48
		#define	   DETCTT_D_IN_TEL_TIMEUP			49
		#define	   DETECT_F_NET_TIMEOUT				56	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

/****************************************/
/** TelephoneExecute() Receive Message **/
/****************************************/
/*
    #define    FROM__NCU_TEL     4
        #define    OK_EXIT                           1
        #define    OK_CONT                           2
*/
        #define    NOTICE_INPUT_HOOK_KEY             3
        #define    NOTICE_INPUT_HOLD_KEY             4
        #define    NOTICE_INPUT_DIAL_KEY             5
        #define    NOTICE_TEL1_OFF_HOOK              6
        #define    NOTICE_TEL2_OFF_HOOK              7
        #define    NOTICE_TEL1_ON_HOOK               8
        #define    NOTICE_TEL2_ON_HOOK               9
        #define    NOTICE_HOLD_1_SEC_PASS           10
        #define    NOTICE_BRC_TEL_OFF_HOOK          11
        #define    NOTICE_INPUT_STOP_KEY            12
        #define    NOTICE_INTER_CALLING_START       13
		#define	   NOTICE_TEL_CML_OFF_TIMEUP		14

/****************************************/
/** DetectSilentTask() Receive Message **/
/****************************************/

		#define    DET_NOISE                         1

/********************************************/
/** NCU_DetectCalledTask() Receive Message **/
/********************************************/
/*
    #define    FROM__NCU_RING    3
        #define    OK_EXIT                           1
        #define    OK_CONT                           2
*/
        #define    DET_CI_TIMEUP                 	 3
        #define    DET_CALLED_REQUEST            	 4

#endif
