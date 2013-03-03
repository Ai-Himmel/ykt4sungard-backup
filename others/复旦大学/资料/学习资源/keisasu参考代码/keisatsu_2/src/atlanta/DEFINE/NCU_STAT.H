#ifndef ncu_stat_h
    #define ncu_stat_h

/**************************************************************************************************
*          BY:   N.Sakamoto
*        DATE:   Tue. 19 Oct. 1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int SYS_NCUStatus
* DESCRIPTION:   回線監視モジュールの状態を示します。（但し留守番電話の状態を除く）
*                
*                
***************************************************************************************************/
#define    TELEPHONE1_OFF_HOOK         0x0001 /*           TEL1が OFF HOOK状態          */
#define    TELEPHONE2_OFF_HOOK         0x0002 /*           TEL2が OFF HOOK状態          */
#define    HOOK_KEY_ON_STATE           0x0004 /*         ON HOOK KEYにて電話状態        */
#define    HOOKING_STATE               0x0008 /*              ﾌｯｷﾝｸﾞ動作中              */
#define    DIALING_STATE               0x0010 /*                 ﾀﾞｲﾔﾙ中                */
#define    HOLD_STATE                  0x0020 /*                保留状態                */
#define    DETECT_CI_STATE             0x0040 /*             着信(CI)検出中　　　       */
#define    DETECT_CALL                 0x0080 /*                 着信                   */
#define    TRANSFER_RECIVE             0x0100 /*               転送受信                 */
#define    BRANCH_OFF_HOOK             0x0200 /*          BRC TEL OFF HOOK状態          */
#define    BRANCH_TRNS_RCV             0x0400 /*          BRC TEL より転送受信          */
#define    INTER_CALL_HOLD_TRNS        0x0800 /*           内線呼出／保留転送           */
#define    INTER_COMMUNICATION         0x1000 /*               内線通話                 */
#define    DETECT_INTER_CI_STATE       0x2000 /* 内線通話中でＤＳＥにより着信(CI)検出中 */
#define    THREE_PARTIES_COM           0x4000 /*               ３者通話                 */
#define    DIALIN_RECEIVE_STATE        0x8000 /*         　 ﾀﾞｲﾔﾙ･ｲﾝ仮着信中          　*/

/**************************************************************************************************
*          BY:   N.Sakamoto
*        DATE:   Sat. 11 Dec. 1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int TADStatus
* DESCRIPTION:   回線監視モジュールの状態の内、留守番電話の状態を示します。
*                
*                
***************************************************************************************************/
#define    FAX_TAD_STATE               0x0001 /*　       留守番電話機能動作中         */
#define    REMOTE_FAX_COMMAND_RCV      0x0002 /* リモートFAX取出DTMF検出(内蔵TAD以外）*/
#define    BUILDIN_TAD_OPERATION       0x0004 /*         内蔵TADローカル使用中        */
#define    REMOTE_TAD_REVERSE          0x0008 /*            遠隔留守切替　　　 　　　 */
#define    REMOTE_RECEIVE              0x0010 /* リモート受信起動  1998/01/26  By T.Yamaguchi */

/**************************************************************************************************
*          BY:   N.Sakamoto
*        DATE:   Mon. 10 Jan. 1994
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned char OhPortStatus
* DESCRIPTION:   付属／外付／ブランチ電話のＯＨの状態を示します。（機種間差違を除く為）
*                
*                
***************************************************************************************************/
#define    TEL1_OFF_HOOK               0x01   /* TEL1が OFF HOOK状態                      */
#define    TEL2_OFF_HOOK               0x02   /* TEL2が OFF HOOK状態                      */
#define    BRC_OFF_HOOK                0x04   /* BRC が OFF HOOK状態                      */
#define	   INTER_COM_CI_DETECT         0x08   /*　内線通話中にＣＩ検出                    */
/* #define  未使用                     0x10                                               */
/* #define  未使用                     0x20                                               */
/* #define  未使用                     0x40                                               */
#define    NO_LINE                     0x80   /* 回線抜け状態    '94,11,29 By N.S.        */

/**************************************************************************************************
*          BY:   N.Sakamoto
*        DATE:   Mon. 17 Jan. 1994
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int RingStatus
* DESCRIPTION:   NCU_RING所属の子ﾀｽｸがdel_evt()した際にｾｯﾄする値
*                着信検出モジュールの発生状態を示します。
*                優先順位がついています
***************************************************************************************************/
#define    RING_STATUS_INITIAL         0x0000   /** ｽﾃｰﾀｽのｲﾆｼｬﾗｲｽﾞ    */
#define    CI_DETECT_TIMEUP            0x0001   /** 検出期間ﾀｲﾑｵｰﾊﾞｰ   */
#define    CI_CYCLE_TIMEUP             0x0002   /** ｻｲｸﾙ期間ﾀｲﾑｵｰﾊﾞｰ   */
#define    CI_ON                       0x0004   /** CI検出             */
#define    F_NET_CALLED_SIGNAL         0x0008   /** Fﾈｯﾄ着信           */
#define    CI_STD_LINE                 0x0010   /** 疑似２回線仕様、標準ライン側CI検出中 by T.Soneoka 1997/11/20 */
#define    CI_EXT_LINE                 0x0020   /** 疑似２回線仕様、拡張ライン側CI検出中 by T.Soneoka 1997/11/20 */

/**************************************************************************************************
*          BY:   N.Sakamoto
*        DATE:   Wen. 31 Aug. 1994
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned char FreqStatus
* DESCRIPTION:   
***************************************************************************************************/
#define    WITHIN_MIN_CYCLE             0x00    /** 予想されるCI割込最少間隔がまだ経過していない期間                     */
#define    OK_CI_CYCLE                  0x01    /** CI割込が発生した後、次のCI割込発生が予想される期間                   */
#define    OVER_MAX_CYCLE               0x02    /** CI割込が発生した後、次のCI割込発生が予想される期間を経過した後の期間 */

/**************************************************************************************************
	FLASH KEY,MERCURY KEYで使用		原田　'94.3.22
***************************************************************************************************/
#define		DIAL_STATUS_AUTODIAL		0
#define		DIAL_STATUS_HOOK_KEY		1
#define		DIAL_STATUS_OFFHOOK1		2
#define		DIAL_STATUS_OFFHOOK2		3

/**************************************************************************************************
*          BY:   平岡徹
*        DATE:   1995/01/07
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned char NCUStatusChangeDetectFlag
* DESCRIPTION:   ブランチ電話のポート検出状況
*
***************************************************************************************************/
#define    DETECT_DISABLE				0		/** ブランチ電話のポート検出禁止 */
#define    DETECT_WAIT_WAIT				1		/** 回線電圧の安定待ち           */
#define    DETECT_WAIT					2		/** 検出開始までのタイムラグ待ち */
#define	   DETECT_ENABLE				3		/** ブランチ電話のポート検出許可 */

/**************************************************************************************************
*          BY:   久保博
*        DATE:   1998/07/02
*        TYPE:   DEFINE
* VAR TO HOLD:   UWORD	NCU_ND_Status
* DESCRIPTION:   ナンバーディスプレイ通信状況
*
***************************************************************************************************/
#define		ND_WAIT_FOR_CAR				0x0001
#define		ND_WAIT_FOR_IR				0x0002
#define		ND_WAIT_FOR_CAR_AND_IR		(ND_WAIT_FOR_CAR | ND_WAIT_FOR_IR)
#define		ND_SUSPICIOUS_CI_DETECTED	0x0004
#define		ND_CI_SEQUENCE_DETECTED		0x0008
#define		ND_CAR_DETECTED				0x0010
#define		ND_BEFORE_INFO_RECEIVED		(ND_WAIT_FOR_CAR_AND_IR | ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED)
#define		ND_INFO_RECEIVED			0x0020
#define		ND_SLEEP_AFTER_ACK_RESPONSE	0x0040 /* 受信完了応答後、二次応答できない期間 added by H.Kubo 1998/11/25 */
#define		ND_DETECT_CI_AFTER_RX_RES	0x0080
#define		ND_WAIT_FOR_2ND_RING		0x0100
#define		ND_COUNTING_2ND_RING		0x0200
#define		ND_CALL_ACCEPTED			0x0400
#define		ND_MODEM_DIALIN_FAX_DIAL	0x1000
#define		ND_MODEM_DIALIN_TEL1_DIAL	0x2000
#define		ND_MODEM_DIALIN_TEL2_DIAL	0x4000
#define		ND_MODEM_DIALIN_DIAL		(ND_MODEM_DIALIN_FAX_DIAL | ND_MODEM_DIALIN_TEL1_DIAL | ND_MODEM_DIALIN_TEL2_DIAL)

/**************************************************************************************************
*          BY:   SMratec 李
*        DATE:   2005/06/21
*        TYPE:   DEFINE
* VAR TO HOLD:   UBYTE	NCU_LineStatus
* DESCRIPTION:   回線状態
*
***************************************************************************************************/
#define STD_LINE_STATUS		0X07	/* 標準回線状態 */	
 #define STD_NOT_USE		0X00	/* 未使用 */
 #define STD_CI_IN			0X01	/* 受話中 */
 #define STD_TEL_RECEIVE	0X02	/* 受話中 */
 #define STD_TEL_TRANSMIT	0X03	/* 送話中 */
 #define STD_IN_USE			0X04	/* 本体使用中 */
 #define STD_COM_IN_USE		0X05	/* 通信中 */

#define STD_HDST_OFFHOOK	0X08	/* 標準回線のハンドセットOFFHOOK状態 */	

#define EXT_LINE_STATUS		0X70	/* 拡張回線状態 */	
 #define EXT_NOT_USE		0X00	/* 未使用 */
 #define EXT_CI_IN			0X10	/* 受話中 */
 #define EXT_TEL_RECEIVE	0X20	/* 受話中 */
 #define EXT_TEL_TRANSMIT	0X30	/* 送話中 */
 #define EXT_IN_USE			0X40	/* 本体使用中 */
 #define EXT_COM_IN_USE		0X50	/* 通信中 */
 
#define EXT_HDST_OFFHOOK	0X80	/* 拡張回線のハンドセットOFFHOOK状態 */	

#endif
