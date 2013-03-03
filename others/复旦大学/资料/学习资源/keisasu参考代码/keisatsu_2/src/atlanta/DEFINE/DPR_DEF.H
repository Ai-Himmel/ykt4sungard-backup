/*
 *  dpr_def.h  1995/11/06  By M.Kotani	-> 1997/06/10 Y.M メンテ
 *  Dual Port RAM 定数定義
 *    最大値定義.....................DPR_MAX_WORD_xxx
 *    状態定義.......................DPR_STATUS_xxx
 *    オプションボード識別ＩＤ定義...DPR_ID_xxx
 *    転送データ種別番号定義.........DPR_TYPE_xxx
 *    関数番号定義...................DPR_COM_xxx
 *                                   DPR_MDM_xxx
 *  Dual Port RAM 型定義
 *    メモリブロック定義.............struct DPR_MemoryBlk_t
 */
#ifndef	dpr_def_h
	#define	dpr_def_h

#include "\src\atlanta\define\product.h"
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
#include "\src\atlanta\define\mem_def.h"
#endif
/************************************************************************
*               BY:  M.Kotani
*             DATE:  97/02/24
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  ATLANTA用Ｉ／Ｏアドレス定義
************************************************************************/
#if 0	/* 1997/10/20 Y.Murata */
//#if defined(ANZU_L)
//#define	DPR_ADDRESS		0x00400000		/**  ＤＰＲＡＭ実装先頭アドレス */
//#else
//#define	DPR_ADDRESS		0x00420000		/**  ＤＰＲＡＭ実装先頭アドレス */
//#endif
#endif
#define	DPR_ADDRESS		0x00420000		/**  ＤＰＲＡＭ実装先頭アドレス */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/06
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  ＤＰＲＡＭ最大値定義
************************************************************************/
#define	DPR_MAX_SLAVE				(UWORD)8
#define	DPR_MAX_WORD_CAPACITY		(UWORD)2048								/**ＤＰＲＡＭ容量ワード数（４Ｋバイト）*/
#define	DPR_MAX_WORD_DATA_AREA		(UWORD)((DPR_MAX_WORD_CAPACITY/2) - 9)	/**データエリアワード数*/
#define	DPR_MAX_WORD_INTERRUPT_AREA	(UWORD)2								/**割り込み発生エリアワード数*/
#define	DPR_WORD_ENABLE_DATA_AREA 	DPR_MAX_WORD_DATA_AREA - DPR_MAX_WORD_INTERRUPT_AREA	/**使用可能データエリアワード数*/
#define	DPR_WORD_DATA_BUF			(UWORD)512	/**ＤＰＲＡＭでの画データ転送時の１回の転送量*/
#define	DPR_MAX_WAIT				(UWORD)500	/**転送先ボードがレディになるまで最大３秒待つ*/
#define	DPR_MAX_WAIT_SEC_MESSAGE	(UWORD)5	/**転送先ボードのレスポンスが来るまでの最大待ち時間５秒*/
#define	DPR_MAX_WAIT_SEC_RESULT		(UWORD)3	/**レスポンスをコマンド発行したタスクにハンドリングする最大待ち時間３秒*/
#define	DPR_MDM_ORANGE				(UWORD)1
#define	DPR_MDM_ROCKWELL			(UWORD)0
#define	DPR_ECM_BUFFER_TRANSFER_UNIT	(UWORD)1024	/**※必ず２５６の倍数にすること！。桐のＥＣＭバッファのデータをグレープのＥＣＭバッファに転送する時の、１回当たりのデータバイト数*/
#define	DPR_MAX_SAMPLING			(UWORD)30	/**ＤＰＲＡＭによる通信の履歴の最大数*/

/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/06
*             TYPE:  define
*      VAR TO HOLD:  DPR_OnBoardUpLoadMemory.Status
*                    DPR_OnBoardDownLoadMemory.Status
*                    DPR_SlaveBoardUpLoadMemory.Status
*                    DPR_SlaveBoardDownLoadMemory.Status
*      DESCRIPTION:  ＤＰＲＡＭ状態定義
************************************************************************/
#define	DPR_STATUS_RX_READY				(UWORD)0x0000		/**使用可能*/
#define	DPR_STATUS_TX_COMPLETE			(UWORD)0x0001		/**最終データ転送中*/
#define	DPR_STATUS_TX_CONTINUE			(UWORD)0x0002		/**連続データ転送中*/
#define	DPR_STATUS_RX_NOT_READY			(UWORD)0xFFFF		/**使用不可能*/

#define DPR_STATUS_DPRAM_TEST			(UWORD)0x5A5A		/** テスト中 1997/04/09 H.Yoshikawa */

/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/10
*             TYPE:  define
*      VAR TO HOLD:  DPR_OnBoardUpLoadMemory.Identification
*                    DPR_OnBoardDownLoadMemory.Identification
*                    DPR_SlaveBoardUpLoadMemory.Identification
*                    DPR_SlaveBoardDownLoadMemory.Identification
*      DESCRIPTION:  オプションボード識別ＩＤ定義
*                    オレンジモデム用ＩＤ追加 By O.Kimoto 1997/06/14
************************************************************************/
#define	DPR_ID_COM		(UWORD)0	/**不特定（共通）ユニット*/
#define	DPR_ID_MDM		(UWORD)1	/**モデム(R288F)ユニット*/
#define	DPR_ID_SCN		(UWORD)2	/**スキャナーユニット*/
#define	DPR_ID_PRN		(UWORD)3	/**プリンタユニット*/
#define	DPR_ID_ROT		(UWORD)4	/**画データ回転ユニット*/
#define	DPR_ID_G4		(UWORD)5	/**G4モデムユニット*/
#define	DPR_ID_ORG_MDM	(UWORD)6	/**モデム(オレンジ)ユニット*//* Add By O.Kimoto 1997/06/14 */
#define DPR_ID_ESS_FX	(UWORD)12	/**ゼロックスのESSユニット接続用 2000/03/17 M.Kotani*/
#define	DPR_ID_ERR		(UWORD)0xFFFF	/**ＤＰＲエラー発生緊急通信情報*/


/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/10
*             TYPE:  define
*      VAR TO HOLD:  DPR_OnBoardUpLoadMemory.DataType
*                    DPR_OnBoardDownLoadMemory.DataType
*                    DPR_SlaveBoardUpLoadMemory.DataType
*                    DPR_SlaveBoardDownLoadMemory.DataType
*      DESCRIPTION:  転送データ種別番号定義
************************************************************************/
#define	DPR_TYPE_FUNCTION_COMMAND	(UWORD)1	/**リモート関数*/
#define	DPR_TYPE_FUNCTION_RESULT	(UWORD)2	/**リモート関数リターン値*/
#define	DPR_TYPE_DATA_COMMAND		(UWORD)3	/**データ転送*/
#define	DPR_TYPE_DATA_RESULT		(UWORD)4	/**データ転送結果*/
#define	DPR_TYPE_AT_COMMAND			(UWORD)5	/**ＡＴコマンド*/
#define	DPR_TYPE_AT_RESULT			(UWORD)6	/**ＡＴリザルトコード*/


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/1/8
*             TYPE:  define
*      VAR TO HOLD:  DPR_OnBoardUpLoadMemory.Unit
*                    DPR_OnBoardDownLoadMemory.Unit
*                    DPR_SlaveBoardUpLoadMemory.Unit
*                    DPR_SlaveBoardDownLoadMemory.Unit
*      DESCRIPTION:  ＤＰＲＡＭデータ単位定義
************************************************************************/
#define	DPR_UNIT_BYTE		(UWORD)0x0001		/**バイトデータ*/
#define	DPR_UNIT_WORD		(UWORD)0x0002		/**ワードデータ*/
#define	DPR_UNIT_DWORD		(UWORD)0x0004		/**ダブルワードデータ*/


/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/07
*             TYPE:  struct
*      VAR TO HOLD:  DPR_OnBoardUpLoadMemory
*                    DPR_OnBoardDownLoadMemory
*                    DPR_SlaveBoardUpLoadMemory
*                    DPR_SlaveBoardDownLoadMemory
*      DESCRIPTION:  ＤＰＲＡＭ用 メモリブロック
*                    送信、受信おのおの独立しているため
*                    最大容量の１／２を越えないようにすること
*                    ※変更するときは、初期化ルーチンも変更すること
************************************************************************/
struct DPR_MemoryBlk_t {
	UWORD	Status;								/*データの状態 (To see DPR_STATUS)*/
	UWORD	StackNumber;						/*何枚目のボードかを識別するための変数*/
	UWORD	Identification;						/*オプションボードの種類を示します*/
	UWORD	Priority;							/*転送データが競合したときの優先順位 ※通常は最低の０ｘＦＦＦＦ*/
	UWORD	DataType;							/*転送するデータの種別です*/
	UWORD	CommandNumber;						/*関数番号ｏｒデータシンボル番号です*/
	UWORD	PacketNumber;						/*大きなデータを何度も転送するときの何番目のデータかどうか*/
	UWORD	Length;								/*データエリアの中の有効データ長*/
	UWORD	Unit;								/*データエリアの中のデータ単位（Ｗｏｒｄ ｏｒ Ｂｙｔｅ）*/
	UWORD	DataArea[DPR_MAX_WORD_DATA_AREA];	/*データエリア*/
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/12/02
*             TYPE:  struct
*      VAR TO HOLD:  ローカルスタック
*      DESCRIPTION:  ＤＰＲＡＭを使った通信を行うときの
*                    セットアップパラメータを集めた構造体
************************************************************************/
struct DPR_SetUpParameter_t {
	UWORD	Status;								/*データの状態 (To see DPR_STATUS)*/
	UWORD	StackNumber;						/*何枚目のボードかを識別するための変数*/
	UWORD	Identification;						/*オプションボードの種類を示します*/
	UWORD	DataType;							/*転送するデータの種別です*/
	UWORD	CommandNumber;						/*関数番号ｏｒデータシンボル番号です*/
	UWORD	PacketNumber;						/*大きなデータを何度も転送するときの何番目のデータかどうか*/
	UWORD	Offset;								/*ＤＰＲＡＭにセットアップするときのオフセット*/
	UWORD	Length;								/*有効データ長*/
	UWORD	Unit;								/*データ単位（Ｗｏｒｄ ｏｒ Ｂｙｔｅ）*/
	UWORD	*Argument;							/*引数の先頭アドレス*/
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  95/11/10
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  関数番号定義
************************************************************************/
/*オプションボード側関数*/
	/*全てのIDに対して有効*/
		#define	DPR_COM_INITIALIZE					(UWORD)0x0001	/**ボード初期化*/
		#define	DPR_COM_CHECK_RESOURCE				(UWORD)0x0002	/**ボードのリソースをチェック*/
		#define	DPR_COM_GET_RESORCE					(UWORD)0x0003	/**ボードのリソースを獲得*/
		#define	DPR_COM_RELEASE_RESORCE				(UWORD)0x0004	/**ボードのリソースを解放*/
		#define	DPR_COM_AFC_COMMAND					(UWORD)0x0005	/**アナログファンクションチェッカ用コマンド*/
		#define	DPR_COM_LOOPBACKTEST				(UWORD)0x0006	/**ＤＰＲＡＭ信頼性テスト（ループバックテスト）*/
		#define	DPR_COM_LOOPBACKRESPONSE			(UWORD)0x0007	/**ＤＰＲＡＭ信頼性テスト（ループバックテスト）*/

	/*DPR_ID_MDMに対して有効*/
		#define	DPR_AUTOFAX							(UWORD)0x3000
		#define	DPR_MANUALTRANSMIT					(UWORD)0x3001
		#define	DPR_MANUALRECEIVE					(UWORD)0x3002
		#define	DPR_AUTOCALLED						(UWORD)0x3003
		#define	DPR_FIPFAXCOM						(UWORD)0x3004
		#define	DPR_MANUALPOLLINGRECEIVE			(UWORD)0x3005
		#define	DPR_STARTTXECM_BUFFER				(UWORD)0x3006
		#define	DPR_SETBITSTOPFAXCOM				(UWORD)0x3007
		#define	DPR_MODEMINITIALIZE					(UWORD)0x3008
		#define	DPR_FCM_WWDETECTSTARTGO				(UWORD)0x3009
		#define	DPR_FCM_WWDETECTSTOP				(UWORD)0x300A
		#define	DPR_SENDFACTORYFUNCTIONDATA			(UWORD)0x300B
		#define	DPR_NCU_DETECTHOOKKEYINPUT			(UWORD)0x300C
		#define	DPR_NCU_DETECTHOLDKEYINPUT			(UWORD)0x300D
		#define	DPR_NCU_DETECTSTOPKEYINPUT			(UWORD)0x300E
		#define	DPR_NCU_TRANSFERINPUTTELNUMBER		(UWORD)0x300F
		#define	DPR_NCU_INSTRUCTINPUTTELNUMBER		(UWORD)0x3010
		#define	DPR_CHANGEDSRAM_PARAMETER			(UWORD)0x3011
		#define	DPR_CHECKVOICEACCEPTED				(UWORD)0x3012
		#define	DPR_NCU_RINGMASTER_TEACHING_ON		(UWORD)0x3013
		#define	DPR_TRANSFERCALLED					(UWORD)0x3014
		#define	DPR_CL1_DETECTRXENABLEFLGCHANGE		(UWORD)0x3015
		#define	DPR_CL1_DETECTSTATUSCHANGE			(UWORD)0x3016
		#define	DPR_CL1_DETSTATUSRXENABLECHANGE		(UWORD)0x3017
		#define DPR_CL1_ATD_AUTODIAL				(UWORD)0x3018
		#define DPR_CL1_DETECT_CLASS1INITVAR		(UWORD)0x3019
		#define DPR_CL1_DETCT_INIT_AT_COMMAND		(UWORD)0x301A
		#define DPR_CL1_DETECT_INIT_S_REGISTER		(UWORD)0x301B
		#define DPR_CL1_DIALABORT					(UWORD)0x301C
		#define DPR_CL1_SELECTDIALPUSE				(UWORD)0x301D
		#define DPR_CL1_FCL							(UWORD)0x301E
		#define DPR_CL1_SETSREGISTER				(UWORD)0x301F
		#define DPR_CL1_CALLED						(UWORD)0x3020
		#define DPR_CL1_ONLINE_REQ					(UWORD)0x3021
		#define DPR_CL1_ONLINE_EXIT					(UWORD)0x3022
		#define DPR_CL1_RING_TIMEOUT				(UWORD)0x3023
		#define DPR_NCU_DETECTNOISE					(UWORD)0x3024
		#define DPR_NCU_DETECTNOISEEXIT				(UWORD)0x3025
		#define DPR_DIALREADPOINTER					(UWORD)0x3026
		#define DPR_CL1_DATARECEIVE					(UWORD)0x3027
		#define DPR_CL1_HDLCRECEIVE					(UWORD)0x3028
		#define DPR_CL1_DUMMYDATATX					(UWORD)0x3029
		#define DPR_CL1_MODEMWRITEOPEN				(UWORD)0x302A
		#define DPR_CL1_SETMODEMWRITEADDRESS		(UWORD)0x302B
		#define DPR_CL1_MODEMWRITE					(UWORD)0x302C
		#define DPR_CL1_MODEMWRITEALL				(UWORD)0x302D
		#define DPR_CL1_MODEMWRITEABORT				(UWORD)0x302E
		#define DPR_CL1_MODEMWRITECLOSE				(UWORD)0x302F
		#define DPR_CL1_MODEMREADOPEN				(UWORD)0x3030
		#define DPR_CL1_MODEMREADCLOSE				(UWORD)0x3031
		#define DPR_CL1_PASECANDCHAIN				(UWORD)0x3032
		#define DPR_CL1_EQUALIZER					(UWORD)0x3033
		#define DPR_CL1_BUFFERDATA					(UWORD)0x3034
		#define DPR_CL1_HDLCRECEIVEEXIT				(UWORD)0x3035
		#define DPR_CL1_DATARECEIVEEXIT				(UWORD)0x3036
		#define DPR_CL1_DUMMYRECEIVEEXIT			(UWORD)0x3037
		#define DPR_CL1_GOONHOOK					(UWORD)0x3038
		#define DPR_CL1_MONITORSPEAKEROFF			(UWORD)0x3039
		#define DPR_CL1_TXFSKWRITE					(UWORD)0x303A
		#define DPR_CL1_TXECMWRITE					(UWORD)0x303B
		#define DPR_CL1_TXG3WRITE					(UWORD)0x303C
		#define DPR_CL1_GETUSEDCOUNT				(UWORD)0x303D
		#define DPR_CL1_SENDRXPHASE					(UWORD)0x303E
		#define DPR_CL1_SETCL1RTCGETFLAG			(UWORD)0x303F

		#define	DPR_TX_RX_TEST						(UWORD)0x3FFF

	/*DPR_ID_MDMに対して有効なデータ転送*/
		#define	DPR_GETT30BUFFER				(UWORD)0x4000
		#define	DPR_GETINTERNALSTATUS			(UWORD)0x4001
		#define	DPR_GETROMREVISION				(UWORD)0x4002
		#define	DPR_GETMONITORDATA				(UWORD)0x4003
		#define	DPR_GETMONITORSTACK				(UWORD)0x4004
		#define	DPR_GETMONITORTCB				(UWORD)0x4005
		#define	DPR_GETRESETADDRESS				(UWORD)0x4006
		#define	DPR_GETUPTXDPRAMMONITOR			(UWORD)0x4007
		#define	DPR_GETDOWNRXDPRAMMONITOR		(UWORD)0x4008
		#define	DPR_GETUPTXDPRAMRESETMONITOR	(UWORD)0x4009
		#define	DPR_GETDOWNRXDPRAMRESETMONITOR	(UWORD)0x400A
		#define	DPR_GETPAT_JOURNALIMAGEDATA		(UWORD)0x400B

	/*DPR_ID_PRNに対して有効なデータ転送*/
		#define	DPR_PCR_DATA_TX_RX_TEST			(UWORD)0x7000

/*ホストファクス側関数*/
	/*全てのIDに対して有効*/
	/*DPR_ID_MDMに対して有効*/
		#define	DPR_CHECKRELAYEDBROADCASTGROUP			(UWORD)0x1000
		#define	DPR_RXCHECKOWNDIALANDID					(UWORD)0x1001
		#define	DPR_CHECKPOLLINGDOCUMENTS				(UWORD)0x1002
		#define	DPR_CHECKDATABASEPOLLINGDOC				(UWORD)0x1003
		#define	DPR_GETDATASIGNALINGRATE				(UWORD)0x1004
		#define	DPR_GETCOMMANDFILENO					(UWORD)0x1005
		#define	DPR_GETCONFIRMATIONREPORT				(UWORD)0x1006
		#define	DPR_SENDBACKCOMMANDFILE					(UWORD)0x1007
		#define	DPR_SENDBACKCLEARCOMMANDFILENO			(UWORD)0x1008
		#define	DPR_SENDBACKMAILBOX						(UWORD)0x1009
		#define	DPR_SENDBACKEXECQUEUE					(UWORD)0x100A
		#define	DPR_SENDBACKMANUALFAXCOMERRREQ			(UWORD)0x100B
		#define	DPR_SENDBACKONETOUCHDIALDATA			(UWORD)0x100C
		#define	DPR_SENDBACKSPEEDDIALDATA				(UWORD)0x100D
		#define	DPR_SENDBACKT30PRINTREQ					(UWORD)0x100E
		#define	DPR_OVERWRITET30BUFFER					(UWORD)0x100F
		#define	DPR_MEM_CHECKSTORECODE					(UWORD)0x1011
		#define	DPR_MEM_CHECKSTOREMODE					(UWORD)0x1012
		#define	DPR_MEM_CHECKSTORESIZE					(UWORD)0x1013
		#define	DPR_MEM_CHECKMILLIINCH					(UWORD)0x1014
		#define	DPR_MEM_CHECKSTORELINECOUNT				(UWORD)0x1015
		#define	DPR_MEM_CHECKINDEXNO					(UWORD)0x1016
		#define	DPR_MEM_CHECKMOSTSMALLPAGE				(UWORD)0x1017
		#define	DPR_MEM_CHECKSTOREDOC					(UWORD)0x1018
		#define	DPR_MEM_CHECKUSEINDEX					(UWORD)0x1019
		#define	DPR_MEM_CLEARALL						(UWORD)0x101A
		#define	DPR_MEM_CLEARALLINDEXAREA				(UWORD)0x101B
		#define	DPR_MEM_CLEARPAGEANDFATAREA				(UWORD)0x101C
		#define	DPR_MEM_CLEARPAGE						(UWORD)0x101D
		#define	DPR_MEM_CLEARDOCANDFATAREA				(UWORD)0x101E
		#define	DPR_MEM_CLEARDOC						(UWORD)0x101F
		#define	DPR_MEM_CLEARBREAK						(UWORD)0x1020
		#define	DPR_MEM_CLEARPOWERDOWN					(UWORD)0x1021
		#define	DPR_MEM_COUNTTOTALPAGE					(UWORD)0x1022
		#define	DPR_MEM_COUNTTOTALEMPTYPAGE				(UWORD)0x1023
		#define	DPR_MEM_COUNTTOTALSTOREPAGE				(UWORD)0x1024
		#define	DPR_MEM_COUNTTOTALBLOCK					(UWORD)0x1025
		#define	DPR_MEM_COUNTPAGEBLOCK					(UWORD)0x1026
		#define	DPR_MEM_COUNTTOTALEMPTYBLOCK			(UWORD)0x1027
		#define	DPR_MEM_COUNTTOTALSTOREBLOCK			(UWORD)0x1028
		#define	DPR_MEM_COUNTUSEBLOCKRATE				(UWORD)0x1029
		#define	DPR_MEM_COUNTEMPTYBLOCKRATE				(UWORD)0x102A
		#define	DPR_MEM_COUNTTOTALCAPACITY				(UWORD)0x102B
		#define	DPR_MEM_DUALCLOSE						(UWORD)0x102C
		#define	DPR_MEM_READGETNEXTBLOCKNO				(UWORD)0x102D
		#define	DPR_MEM_WRITE							(UWORD)0x102E
		#define	DPR_MEM_MULTIWRITECLOSE					(UWORD)0x102F
		#define	DPR_MEM_WRITECLOSE						(UWORD)0x1030
		#define	DPR_GETDOCUMENTSCANSIZE					(UWORD)0x1031
		#define	DPR_SETGLOBALDATA						(UWORD)0x1032
		#define	DPR_SENDMESSAGE							(UWORD)0x2015
		#define	DPR_SETPATJOURNALDATAATAUTOFAX			(UWORD)0x1034
		#define	DPR_SETPATJOURNALATMANUALTX				(UWORD)0x1035
		#define	DPR_SETPATJOURNALATMANUALRX				(UWORD)0x1036
		#define	DPR_SETPATJOURNALATAUTOCALLED			(UWORD)0x1037
		#define	DPR_SETPATJOURNALATPOLLAUTOCALL			(UWORD)0x1038
		#define	DPR_SETPATJOURNALATMANULAPOLL			(UWORD)0x1039
		#define	DPR_SETPATJOURNALATAFTER				(UWORD)0x103A
		#define	DPR_SETJOURNAL							(UWORD)0x103B
		#define	DPR_OVERWRITENONSTANDARDID				(UWORD)0x103C
		#define	DPR_OVERWRITESTANDARDID					(UWORD)0x103D
		#define	DPR_OVERWRITEBACKUPSTANDARDID			(UWORD)0x103E
		#define	DPR_OVERWRITEDIPLAYDATA					(UWORD)0x103F
		#define	DPR_SCN_STOPMOTOR						(UWORD)0x1040
		#define	DPR_LAMPON								(UWORD)0x1041
		#define	DPR_LAMPOFF								(UWORD)0x1042
		#define	DPR_CMN_EVACUATESTAMPSETTING			(UWORD)0x1043
		#define	DPR_CHECKMEMRXCONTINUEFORVOICE			(UWORD)0x1044
		#define	DPR_GETMEMORYBLOCKSIZE					(UWORD)0x1045
		#define	DPR_CHECKMEMORYRECEIVEENABLE			(UWORD)0x1046
		#define	DPR_GETMEMORYRXPRINTWRITEPOINT			(UWORD)0x1047
		#define	DPR_GETDS1_ON							(UWORD)0x1048
		#define	DPR_GETCOVERSCANNEROPEN					(UWORD)0x1049
		#define	DPR_GETSCANNERLAMPERROR					(UWORD)0x104A
		#define	DPR_CMN_PUSHSTAMP						(UWORD)0x104B
		#define	DPR_FCM_SCANNERTXMANAGEMENT				(UWORD)0x104C
		#define	DPR_FCM_SCANNERCLOSEMANAGEMENT			(UWORD)0x104D
		#define	DPR_FCM_SCN_DECIDEREDUCPATTERN			(UWORD)0x104E
		#define	DPR_FCM_GETSYS_TXTOTALCOUNT				(UWORD)0x104F
		#define	DPR_FCM_GETSYS_RXTOTALCOUNT				(UWORD)0x1050
		#define	DPR_DIAG_JUDGEPROTECTADDRESS			(UWORD)0x1051
		#define	DPR_DIAG_WRITEFIF_DIAGNSS				(UWORD)0x1052
		#define	DPR_SETTXRESPONSEDRTN_PAGESIGN			(UWORD)0x1053
		#define	DPR_SCANFIRSTBLOCK						(UWORD)0x1054
		#define	DPR_SCANNEXTBLOCK						(UWORD)0x1055
		#define	DPR_MDM_BREAKTXTASK						(UWORD)0x1056
		#define	DPR_SETINTERNALSTATUS					(UWORD)0x1057
		#define	DPR_CHECKTXSYSTEMERROR					(UWORD)0x1058
		#define	DPR_FCM_SETWWDETECT2100HZ				(UWORD)0x1059
		#define	DPR_SETRESETADDRESS						(UWORD)0x105A
		#define	DPR_SETROMREVISION						(UWORD)0x105B
		#define DPR_SCNTXBETWEENPAGEMANAGEMENT			(UWORD)0x105C
		#define DPR_GETCODECSIZE						(UWORD)0x105D
		#define DPR_OVERWRITESTARTDATA					(UWORD)0x105E
		#define DPR_OVERWRITEPAGEDATA					(UWORD)0x105F
		#define DPR_OVERWRITEENDDATA					(UWORD)0x1060
		#define DPR_SETFACTORYFUNCTIONRESPONSE			(UWORD)0x1061
		#define DPR_CHECKREMOTODIAG						(UWORD)0x1062
		#define DPR_GETMONITORSPEAKEROUTLEVEL			(UWORD)0x1063
		#define DPR_SNDBACKDIAGPASSCODENUMBER			(UWORD)0x1064
		#define	DPR_SENDBACKCONTINUOUSPOLLING			(UWORD)0x1065
		#define DPR_CL1_MDMBUFFERINIT					(UWORD)0x1066
		#define DPR_CL1_MDMBUFFERINITG3					(UWORD)0x1067
		#define DPR_CL1_TRANSFERMODEMBUFFER				(UWORD)0x1068
		#define	DPR_ERASETXMEMORYPAGE					(UWORD)0x1069	/*送信済みメモリの消去*/
		#define	DPR_MEM_COUNTFINALPAGE					(UWORD)0x106A	/*送信済みメモリの消去*/
		#define	DPR_CHECKJUNKFAX						(UWORD)0x106B	/*新ﾀﾞｲﾚｸﾄﾒｰﾙ、ﾓｰﾄﾞ編*/
		#define	DPR_SETCOSTDATA							(UWORD)0x106C
		#define	DPR_SETFAXCOMERRMONITOR					(UWORD)0x106D
		#define	DPR_GETCIPHERBOXNO						(UWORD)0x106E
		#define	DPR_SENDBACKCIPHERSTATUS				(UWORD)0x106F
		#define	DPR_FCM_SETUPREMOTEID					(UWORD)0x1070
		#define	DPR_FCM_TXFCODESTATUSSET				(UWORD)0x1071
		#define	DPR_CHECKSELECTPOLLDOCUMENT				(UWORD)0x1072
		#define	DPR_CHECKSUBADDRESSBOX					(UWORD)0x1073
		#define	DPR_SETRXSUBADDRESSBOX					(UWORD)0x1074
		#define	DPR_SETTXSUBADDRESSBOX					(UWORD)0x1075
		#define	DPR_CHECKMAILBOXSTATUS					(UWORD)0x1076

	/*DPR_ID_PRNに対して有効*/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
		#define	DPR_MEM_COUNTTOTALPRINTPAGE				(UWORD)0x5000	/* ﾒﾓﾘ内の原稿でﾌﾟﾘﾝﾄしようとしているﾍﾟｰｼﾞ数 */
		#define	DPR_PCR_PRINTJOBTRANSSTART				(UWORD)0x5001	/* PC転送ｽﾀｰﾄ(ｼﾞｮﾌﾞ毎)                       */
		#define	DPR_PCR_PRINTPAGETRANSEND				(UWORD)0x5002	/* 1ﾍﾟｰｼﾞﾌﾟﾘﾝﾄﾃﾞｰﾀ転送終了                   */
		#define	DPR_PCR_PRINTJOBTRANSEND				(UWORD)0x5003	/* 1ｼﾞｮﾌﾞﾌﾟﾘﾝﾄﾃﾞｰﾀ転送終了                   */
		#define	DPR_PCR_PRINTTESTSTART					(UWORD)0x5004	/* ﾃｽﾄﾌﾟﾘﾝﾄ開始要求                          */
		#define	DPR_PCR_PRINTPAGETRANSABORT				(UWORD)0x5005	/* ﾃﾞｰﾀ転送ｱﾎﾞｰﾄ                             */
		#define	DPR_PCR_PRINTPAGEFILECLEAR				(UWORD)0x5006	/* 転送ﾃﾞｰﾀ消去                              */
		#define	DPR_PCR_JAMRECOGNIZE					(UWORD)0x5007	/* ﾌﾟﾘﾝﾄﾏﾈｰｼﾞｬ ｼﾞｬﾑ認識 By J.Miyazaki 1997/03/28*/
#endif
#if (PRO_ROTATE == ENABLE)
		#define	DPR_STARTROTATE							(UWORD)0x8000
		#define	DPR_ENDROTATE							(UWORD)0x8001
		#define	DPR_ROT_INITIALIZE						(UWORD)0x8002
		#define	DPR_ROT_TEST							(UWORD)0x8003
#endif
	/*DPR_ID_MDMに対して有効なデータ転送*/
		#define	DPR_MEM_DUALOPEN						(UWORD)0x2000
		#define	DPR_MEM_READOPEN						(UWORD)0x2001
		#define	DPR_MEM_READ							(UWORD)0x2002
		#define	DPR_MEM_WRITEOPEN						(UWORD)0x2003
		#define	DPR_MEM_MULTIWRITEOPEN					(UWORD)0x2004
		#define	DPR_MEM_WRITEGETNEXTBLOCKNO				(UWORD)0x1031
		#define	DPR_GETMACHINEPARAMETER					(UWORD)0x2005
		#define	DPR_GETMEMORYSWITCH						(UWORD)0x2006
		#define	DPR_GETSETTINGSTATUS					(UWORD)0x2007
		#define	DPR_GETPAPERSIZE						(UWORD)0x2008
		#define	DPR_GETTTI_BUFFER						(UWORD)0x2009
		#define	DPR_GETID_BUFFER						(UWORD)0x200A
		#define	DPR_GETPASSCODENUMBER					(UWORD)0x200B
		#define	DPR_GETSECUREMAILBOX					(UWORD)0x200C
		#define	DPR_GETONETOUCHDIALDATAALL				(UWORD)0x200D
		#define	DPR_GETSPEEDDIALDATAALL					(UWORD)0x200E
		#define	DPR_GETONETOUCHDIALDATAONE				(UWORD)0x200F
		#define	DPR_GETSPEEDDIALDATAONE					(UWORD)0x2010
		#define	DPR_GETSUBDIALALL						(UWORD)0x2011
		#define	DPR_GETCOMMANDFILE						(UWORD)0x2012
		#define	DPR_GETEXECQUEUEFILE					(UWORD)0x2013
		#define	DPR_GETGLOBALDATA						(UWORD)0x2014
		#define	DPR_LST_SETTTI_IMAGE					(UWORD)0x2016
		#define	DPR_LST_SETCOVERPAGE_IMAGE				(UWORD)0x2017
		#define	DPR_LST_SETRCR_IMAGE					(UWORD)0x2018
		#define	DPR_DIAG_READFIF_DIAGNSS				(UWORD)0x2019
		#define	DPR_GETBATCHFILE						(UWORD)0x201A
		#define	DPR_GETSTXENCODEECM_BUFFER				(UWORD)0x201B
		#define	DPR_GETSTXCODECPAGESTATUS				(UWORD)0x201C
		#define	DPR_GETMACHINEUNIQSWITCH				(UWORD)0x201D
		#define	DPR_GETMAINTENANCESWITCH				(UWORD)0x201E
		#define	DPR_GETMACHINEPERFORMANCE				(UWORD)0x201F
		#define	DPR_GETOPTIONBOAUDFUNCTION				(UWORD)0x2020
		#define	DPR_TXPIXREDUCTIONSET					(UWORD)0x2021
		#define	DPR_PAT_AUTOFAX							(UWORD)0x2022
		#define	DPR_PAT_MANULATRANSMIT					(UWORD)0x2023
		#define	DPR_PAT_MANULARECEIVE					(UWORD)0x2024
		#define	DPR_PAT_AUTOCALLED						(UWORD)0x2025
		#define	DPR_PAT_POLLINGTRANSMIT					(UWORD)0x2026
		#define	DPR_PAT_LAST							(UWORD)0x2027
		#define	DPR_GETHOSTROM_REVISION					(UWORD)0x2028
		#define DPR_GETPSTN_ACCESS_NUMBER				(UWORD)0x2029
		#define DPR_GETDIAGPASSCODENUMBER				(UWORD)0x202A
		#define	DPR_GETCONTINUOUSPOLLING				(UWORD)0x202B
		#define DPR_GETCLASS1BUFFER						(UWORD)0x202C
		#define DPR_GETMERCURYDIALBUFFER				(UWORD)0x202D
		#define DPR_GETCOMMANDFILEFCODENUMBER			(UWORD)0x202E
		#define	DPR_FCM_RXFCODESTATUSSET				(UWORD)0x202F
		#define	DPR_FCM_COMPFCODEBOX					(UWORD)0x2030
		#define	DPR_FCM_TXFCODEFILESET					(UWORD)0x2031
		#define DPR_GETCIL_IMAGE						(UWORD)0x2032	/* #if (PRO_DATE_SET_RXDOC_CHK == ENABLE) 1998/06/15 Y.Murata */


	/*DPR_ID_PRNに対して有効なデータ転送*/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
		#define	DPR_PCR_GETPRINTERSTATUS				(UWORD)0x6000	/* ﾌﾟﾘﾝﾀ動作状況/状態要求                    */
		#define	DPR_PCR_GETSETTINGPAPERSIZE				(UWORD)0x6001	/* ｶｾｯﾄｻｲｽﾞ/手差しｾｯﾄ記録紙ｻｲｽﾞ要求          */
		#define	DPR_PCR_GETDATATRANSFERSIZE				(UWORD)0x6002	/* 印字可能領域･左右白付加ﾄﾞｯﾄｻｲｽﾞ(X,Y)      */
		#define	DPR_PCR_GETPRINTERENGINESPEC			(UWORD)0x6003	/* ﾌﾟﾘﾝﾀ設定情報要求                         */
		#define	DPR_PCR_GETLIFEMONITOR					(UWORD)0x6004	/* 印字枚数要求(ﾄｰﾀﾙ/ﾄﾞﾗﾑ毎)                 */
		#define	DPR_PCR_GETPRINTERENGINEID				(UWORD)0x6005	/* ﾌﾟﾘﾝﾀ識別ID要求                           */
#endif


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/1/19
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  大域変数番号定義
************************************************************************/
#define DPR_SYS_JOURNALPOINT				(UWORD)0x0003
#define DPR_SYS_TXJOURNALNUMBER				(UWORD)0x0004
#define DPR_SYS_RXJOURNALNUMBER				(UWORD)0x0005
#define DPR_SYS_MULTICOPYPOINT				(UWORD)0x0006
#define DPR_MEMORYRXPRINTWRITEPOINT			(UWORD)0x0007
#define DPR_MEMORYRXPRINTREADPOINT			(UWORD)0x0008
#define DPR_SYS_POLLINGDOCUMENTSTATUS		(UWORD)0x0009
#define DPR_SYS_DB_POLLINGDOCUMENTSTAT		(UWORD)0x000A
#define DPR_SYS_WORDINGNUMBER				(UWORD)0x000C
#define DPR_SYS_RXMODESWITCH				(UWORD)0x000D
#define DPR_SYS_MODESW						(UWORD)0x000E
#define DPR_SYS_DENSITYSW					(UWORD)0x000F
#define DPR_SYS_TXTOTALCOUNT				(UWORD)0x0010
#define DPR_SYS_RXTOTALCOUNT				(UWORD)0x0011
#define DPR_SYS_CONFIRMATIONREPORTSW		(UWORD)0x0012
#define DPR_SYS_JOURNALAUTOSTATUS			(UWORD)0x0013
#define DPR_SYS_AUTOJOURNALCOUNTER			(UWORD)0x0014
#define DPR_SYS_REMOTEFAXMEMORYOVERFLAG		(UWORD)0x0016
#define DPR_SYS_POWERDOWNLISTSTATUS			(UWORD)0x0017
#define DPR_SYS_DOCUMENTSTOREITEM			(UWORD)0x0018
#define DPR_SYS_DOCUMENTSTORENO				(UWORD)0x0019
#define DPR_SYS_DOCUMENTSTOREPAGE			(UWORD)0x001A
#define DPR_SYS_DOCUMENTPRINTCLASS			(UWORD)0x001B
#define DPR_SYS_DOCUMENTPRINTITEM			(UWORD)0x001C
#define DPR_SYS_DOCUMENTPRINTNO				(UWORD)0x001D
#define DPR_SYS_DOCUMENTPRINTPAGENO			(UWORD)0x001E
#define DPR_SYS_FAXCOMTYPE					(UWORD)0x001F
#define DPR_SYS_FAXCOMTXTYPE				(UWORD)0x0020
#define DPR_SYS_RXRECEIPTREQUESTFLAG		(UWORD)0x0021
#define DPR_SYS_RXMEMORYFILEITEM			(UWORD)0x0022
#define DPR_SYS_RXMEMORYFILENO				(UWORD)0x0023
#define DPR_SYS_RXMEMORYFILEPAGE			(UWORD)0x0024
#define DPR_SYS_RXPRINTFILEPAGE				(UWORD)0x0025
#define DPR_SYS_RXPRINTFILENO				(UWORD)0x0026
#define DPR_SYS_RXPRINTFILEITEM				(UWORD)0x0027
#define DPR_SYS_MULTIPRINTCOUNT				(UWORD)0x0028
#define DPR_SYS_VOICECALLACCEPTED			(UWORD)0x0029
#define DPR_SYS_VOICESWITCH					(UWORD)0x002A
#define DPR_SYS_GENERALTIMER				(UWORD)0x002B
#define DPR_SYS_PAPER2SIZE					(UWORD)0x002E
#define DPR_SYS_PAPER1SIZE 					(UWORD)0x002F
#define DPR_SYS_HOOKKEYINPUTFLAG			(UWORD)0x0030
#define DPR_SYS_HOLDKEYINPUTFLAG			(UWORD)0x0031
#define DPR_SYS_TXTOTALPAGE					(UWORD)0x0032
#define DPR_SYS_RXTOTALPAGE					(UWORD)0x0033
#define DPR_SYS_FAXCOMMSTAGE				(UWORD)0x0034
#define DPR_SYS_PIXSTOPFLAG					(UWORD)0x0035
#define DPR_SYS_DOCUMENTWIDTHFULLFLAG		(UWORD)0x0036
#define DPR_SYS_DOCUMENTLENGTHLIMITFLAG		(UWORD)0x0037
#define DPR_SYS_DOCUMENTSCANSIZE			(UWORD)0x0038
#define DPR_SYS_DOCUMENTPRINTSIZE			(UWORD)0x0039
#define DPR_SYS_SINGLECOPYPRINTNUMBER		(UWORD)0x003A
#define DPR_SYS_TXDETECTFLAG				(UWORD)0x003C
#define DPR_SYS_RXDETECTFLAG				(UWORD)0x003D
#define DPR_SYS_CURRENTEXECQUEUENO			(UWORD)0x003E
#define DPR_SYS_MEMORYRXERASEREPORTP		(UWORD)0x003F
#define DPR_FAXCOMPATIBLEERRORCODE			(UWORD)0x0040
#define DPR_FAXCOMTXORRX_SIGN				(UWORD)0x0041
#define DPR_TXMODE							(UWORD)0x0042
#define DPR_RXMODE							(UWORD)0x0043
#define DPR_TXMEMORYFILEITEM				(UWORD)0x0044
#define DPR_FAXCOMRESULT					(UWORD)0x0045
#define DPR_BACKUPFAXCOMRESULT				(UWORD)0x0046
#define DPR_SCN_MOTORSPEEDCONTROL			(UWORD)0x0047
#define DPR_SCN_MOTORSTOPREQUEST			(UWORD)0x0048
#define DPR_AD_RESULT						(UWORD)0x0049
#define DPR_GRAYMODEFLAG					(UWORD)0x004A
#define DPR_MDM_TXSTOPSWFLAG				(UWORD)0x004B
#define DPR_CL1_MDMERROR					(UWORD)0x004C
#define DPR_CL1_MDMCARRIERDOWN				(UWORD)0x004D
#define DPR_CL1_DECODELINES					(UWORD)0x004E
#define DPR_MERCURYPAUSETIME				(UWORD)0x004F


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/09/05
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  エラーコード定義
************************************************************************/
#define DPRD_ERRORUPLOADID				(UWORD)0x0001
#define DPRD_ERRORUPLOADDATATYPE		(UWORD)0x0002
#define DPRD_ERRORUPLOADMODEMFUNCCOM	(UWORD)0x0003
#define DPRD_ERRORSETDOWNLOADTXAREA		(UWORD)0x0004
#define DPRD_ERROROPENDOWNLOADTX		(UWORD)0x0005
#define DPRD_ERRORFUNCTIONARGUMENT		(UWORD)0x0006
#define DPRD_ERRORCLOSEDOWNLOADTX		(UWORD)0x0007
#define DPRD_ERRORRECEIVEDATARESULT		(UWORD)0x0008
#define DPRD_ERRORUPMODEMFUNCRESULT		(UWORD)0x0009
#define DPRD_ERRORUPMODEMDATARESULT		(UWORD)0x000A
#define DPRD_ERRORRECEIVEFUNCTIONRESULT	(UWORD)0x000B
#define DPRD_ERRORFUNCRECEIVEMESSAGE	(UWORD)0x000C
#define DPRD_ERRORDATARECEIVEMESSAGE	(UWORD)0x000D
#define DPRD_ERRORFUNCSENDMESSAGE		(UWORD)0x000E
#define DPRD_ERRORDATASENDMESSAGE		(UWORD)0x000F
#define DPRD_ERRORUPLOADRXINTERRUPT		(UWORD)0x0010


/* スワップするかしないかの定義 */
#define DPR_SWAP_DISABLE	(UWORD)0
#define DPR_SWAP_ENABLE		(UWORD)1

/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/5
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  コマンドファイル転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
#define DPR_DIRECT_DIAL_MAX			21	/* 直接ダイヤル番号40桁+NULL */
#define	DPR_FXSPEED_DIAL_MAX		2	/* FX短縮4桁 */

/* 通信予約ダイヤル数ＵＰ追加 by T.Soneoka 1996/07/03 */
#define DPR_COM_DIRECT_DIAL_MAX		5	/* 1通信あたりの直接ダイヤル最大宛先 */
#define DPR_ONETOUCH_BIT_FIELD_MAX	5	/* ワンタッチダイヤル数４０件分のビットフィールド */
#define	DPR_SPEED_BIT_FIELD_MAX		20	/* 短縮ダイヤル数１６０件分のビットフィールド */
#define	DPR_PIN_MAX					4


/* 通信予約ダイヤル数ＵＰ変更 by T.Soneoka 1996/07/03
** 一括送信時のダイヤルデータ（前のstruct DPR_DialDataと同じ）
*/
/* ＳＨでは、構造体のメモリの配置に空きがでるので、型を変換します。
*/
struct DPR_BatchTxDialData_t {
	UWORD Item; /*ダイヤル種別*/
	UBYTE PIN_Number[DPR_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
	union {
		UBYTE Direct[DPR_DIRECT_DIAL_MAX-1];	/*直接ダイヤル番号ＢＣＤ*/
		UBYTE Onetouch;							/*ワンタッチ番号*/
		UWORD Speed;							/*短縮番号*/
		UWORD Group;							/*グループ番号*/
		UBYTE FxSpeed[DPR_FXSPEED_DIAL_MAX];	/*ゼロックス短縮番号*/
	} FaxNumber;
};


/* 通信予約ダイヤル数ＵＰ変更 by T.Soneoka 1996/07/03
** 一括送信以外のダイヤルデータ（新規）
*/
/** ＳＨでは、構造体のメモリメモリの配置に空きがでるので、型を変換します。
*** By Hirao 1997/06/04
**/
struct DPR_DialData_t {
	UBYTE PIN_Number[DPR_COM_DIRECT_DIAL_MAX][DPR_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。*/
	UBYTE Direct[DPR_COM_DIRECT_DIAL_MAX][DPR_DIRECT_DIAL_MAX];
	UBYTE Onetouch[DPR_ONETOUCH_BIT_FIELD_MAX];
	UBYTE Speed[DPR_SPEED_BIT_FIELD_MAX];
	UWORD Group_L;
	UWORD Group_H;
};


#define	DPR_SRC_ID_MAX			21	/* 中継配信時の親機の発信元番号20桁+NULL*/
#define	DPR_DATA_BASE_MAX		11	/* 検索ポーリング時のファイル数10+ -1*/
struct DPR_OptionData_t	{
	UWORD Item;											/*通信種別*/
	union {
		UWORD SecureNumber;								/*親展番号*/
		UWORD RelayGroupNumber[2];						/*中継指示グループ番号*/
		UBYTE RelaySourceID[DPR_SRC_ID_MAX];			/*中継配信親機の発信元番号*/
		UWORD DatabaseNumber[DPR_DATA_BASE_MAX];		/*検索ポーリングファイル番号*/
	} OptionNumber;
	UWORD ConfirmationReport;							/*通信証*/
};

/*###構造体をさわる時は注意！！ DPRD_CopyCommandFile()のサイズも要チェック！！ ###*/
#define	DPR_COM_DIAL_MAX		10	/* 1通信当たりの最大宛先数 */
struct DPR_CommandData_t {
	UWORD Status;										/*コマンドファイルの使用状況*/
#if (0) /* 通信予約ダイヤル数ＵＰ変更 by T.Soneoka 1996/07/04 */
	struct DPR_DialData DialNumber[DPR_COM_DIAL_MAX];	/*電話番号*/
#endif
	struct DPR_DialData_t DialNumber;					/*電話番号*/
	UWORD ExecTime_L;									/*発信時間*/
	UWORD ExecTime_H;									/*発信時間*/
	struct DPR_OptionData_t Option;						/*応用通信機能*/
	UWORD DepartmentCode;								/*部門管理コード*/
	UWORD Type;											/*送受信一体型時の送受の識別*/
	UWORD TitleMessage;									/*タイトルメッセージ*/
	UWORD Page;											/*ページ数*/
	UWORD Ability;										/*付加属性*/
	UBYTE PIN_AccessMode;		   /** ＰＩＮアクセスモード。コマンド登録時のSYS_SettingStatusに値 */
	UBYTE PIN_Number[DPR_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。*/
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/7
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  ExecQueue転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
struct	DPR_ExecDialData_t	{
	UWORD Item;				/* ダイヤル種別 */
	union {
		UWORD Command;		/* 通信予約番号 */
		UWORD Onetouch;		/* ワンタッチ番号 */
		UWORD Speed;		/* 短縮番号 */
	} ExecNumber;
};


#define	DPR_ERROR_PAGE		6
struct DPR_ExecQueueData_t {
	UWORD Status;						/* 使用状況 */
	UWORD Kind;							/* 予約種別 */
	union {
		UWORD Command;					/* 通信予約番号  SYB_CommandFile[]の配列オフセット値 */
		UWORD Batch;					/* 一括送信番号  SYB_BatchTxFile[]の配列オフセット値 */
		UWORD ContPolling;				/* 連続ポーリング番号 */
	} Number;
	UWORD RedialCount;					/* リダイヤル回数 */
	UWORD RedialTime;					/* リダイヤル間隔 */
	UWORD Result;						/* 通信結果 */
	UWORD Page;							/* 通信ページ */
	struct DPR_ExecDialData_t	ExecDial;	/* 電話番号 */
	UWORD ErrorPage[DPR_ERROR_PAGE];	/* 画質不良ページ */
	UWORD Option;						/* 付加機能 */
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/7
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  短縮ダイヤル転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
#define DPR_TEL_2DIGIT_MAX	21	/* 短縮ダイヤル40桁+NULL */
#define DPR_DIAL_NAME_MAX	17	/* 相手先名16文字+NULL */
struct DPR_SpeedDialData_t {
	UBYTE Dial[DPR_TEL_2DIGIT_MAX];	/* 電話番号 */
	UBYTE Name[DPR_DIAL_NAME_MAX];	/* 相手先名(NULL含む) */
	UBYTE PIN_Number[DPR_PIN_MAX]; /** PIN番号登録ＢＣＤコードで８桁まで。 By S.K Sep.21,1995 ANZU */
	UWORD SubDialPosition;					/* 転送先 */
	UBYTE CostPosition;						/* 料金テーブル */
	UBYTE Group_LL;							/* グループ番号 */
	UBYTE Group_L;							/* グループ番号 */
	UBYTE Group_H;							/* グループ番号 */
	UBYTE Group_HH;							/* グループ番号 */
	UBYTE Attribute1_L;						/* 属性1 */
	UBYTE Attribute1_H;						/* 属性1 */
	UBYTE Attribute2_L;						/* 属性2 */
	UBYTE Attribute2_H;						/* 属性2 */
	UBYTE Attribute3_L;						/* 属性3 */
	UBYTE Attribute3_H;						/* 属性3 */
	UBYTE Attribute4_L;						/* 属性4 */
	UBYTE Attribute4_H;						/* 属性4 */
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/7
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  ワンタッチダイヤル転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
#define DPR_JOB_MAX				6	/* 1キー当たりの最大ジョフ゛数+-1 */
struct DPR_OnetouchDialData_t {
	UWORD Status;							/* 登録状態 */
	union {
		struct DPR_SpeedDialData_t Onetouch;	/* 短縮ダイヤルと同じ */
		/*何かしらんけど、通信予約は4の倍数ｱﾄﾞﾚｽからとられてしまい空きがでる。でも使わないからはずす */
		/*struct DPR_CommandData_t Program;*/		/* 通信予約と同じ */
		UBYTE Job[DPR_JOB_MAX];		/* ジョブメモリ */
	} DialData;
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/7
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  親展ボックス転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
#define DPR_MAILBOX_MAX		10	/* 最大親展受信ボックス数 */
#define DPR_REMOTE_NAME_MAX	21	/* 親展受信相手先名20文字+NULL */
#define DPR_BOX_NAME_MAX	17	/* 親展者名16文字+NULL */

/*
** ＳＨでは、構造体のメモリの配置に空きがでるので、型を変換します。
*/
struct DPR_MailBoxData_t {
	UWORD Status;									/* 親展受信状態 */
	UWORD MessageStatus;							/* メッセージ出力状態 */
	unsigned char RemoteName[DPR_REMOTE_NAME_MAX];	/* 親展受信相手先名(NULL含む) */
	unsigned char BoxName[DPR_BOX_NAME_MAX];		/* 親展者名(NULL含む) */
	UWORD PassCode;									/* パスコード(暗証番号) */
	UWORD ErasedTime_L;								/* 消去時間 */
	UWORD ErasedTime_H;								/* 消去時間 */
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/11
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  一括送信構造体転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
************************************************************************/
#define	DPR_BATCH_NAME_MAX	17	/* 宛先名16文字+NULL */
#define	DPR_BATCH_INDEX_MAX	40	/* 最大原稿登録回数 */

/*
** ＳＨでは、構造体のメモリの配置に空きがでるので、型を変換します。
*/
struct DPR_BatchTxData_t {
	UWORD Status;								/* 使用状況 */
#if (0) /* 通信予約ダイヤル数ＵＰ変更 by T.Soneoka 1996/07/03 */
	struct DPR_DialData_t DialNumber[1];			/* 電話番号 */
#endif
	struct DPR_BatchTxDialData_t DialNumber[1];	/* 電話番号 */
	UBYTE Dummy;
	UBYTE ExecTime_LL;					/* 発信時刻 */
	UBYTE ExecTime_L;					/* 発信時刻 */
	UBYTE ExecTime_H;					/* 発信時刻 */
	UBYTE ExecTime_HH;					/* 発信時刻 */
	UBYTE ProgramTime_LL;				/* 発信指定時刻 */
	UBYTE ProgramTime_L;				/* 発信指定時刻 */
	UBYTE ProgramTime_H;				/* 発信指定時刻 */
	UBYTE ProgramTime_HH;				/* 発信指定時刻 */
	UBYTE Page_L;						/* 送信ページ数 */
	UBYTE Page_H;						/* 送信ページ数 */
	UBYTE Name[DPR_BATCH_NAME_MAX];		/* 宛先名(NULL含む) */
	UWORD IndexNo[DPR_BATCH_INDEX_MAX];	/* 送信原稿番号 */
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/3/18
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  ＬＣＤ表示更新データ転送用バッファ定義
************************************************************************/
#define DPR_TTI_ID_MAX			17
#define DPR_ID_MAX				21
struct DPR_FCM_DisplayData_t {
	UWORD SYS_FaxCommStage;							/* 通信遷移状態 define */
	UWORD SYS_CurrentExecQueueNo;					/* Grape実行ExecQueueの番号 */
	UWORD SYS_DocBlock_Src_Size;					/* 元原稿パラメータ define */
	UWORD SYS_DocBlock_Src_Mode;					/* 元原稿パラメータ define */
	UWORD SYS_DocBlock_Dst_Size;					/* 先原稿パラメータ define */
	UWORD SYS_DocBlock_Dst_Mode;					/* 先原稿パラメータ define */
	UWORD GrayModeFlag;								/* ファイン、中間調の場合--YES yes/no */
	UWORD FaxComTXorRX_Sign;						/* 送信／受信識別フラグ　送信、受信、リモート診断識別 define */
	UWORD SYS_FaxComType;							/* 交信種別 define */
	UWORD SYS_FaxComTxType;							/* 送信原稿種別 define */
	UWORD TxBaudRate;								/* 確定送信ボーレイト define */
	UWORD RxBaudRate;								/* 確定受信ボーレイト define */
	UWORD TxECM_Mode;								/* 確定ＥＣＭ送信指定 yes/no */
	UWORD RxECM_Mode;								/* 確定ＥＣＭ受信指定 yes/no */
	UWORD FinalRxMode;								/* 確定受信モード define */
	UWORD SYS_TxTotalPage;							/* 全送信ページ数 */
	UWORD SYS_RxTotalPage;							/* 全受信ページ数 */
	UWORD TxMemoryFilePage;							/* メモリ送信を行う原稿のファイルページ */
	UWORD MDM_RxTotalLine;							/* 受信トータルライン */
	UWORD MDM_RxErrorTotalLine;						/* 受信エラートータルライン */
	UWORD BatchTxFinishPage;						/* 一括送信送信済み頁数 */
	UBYTE NonStandardID[DPR_TTI_ID_MAX];	/* 交信相手機の村田ＩＤ */
	UBYTE StandardID[DPR_ID_MAX];			/* 交信相手機の標準ＩＤ */
	UWORD SYS_RxMemoryFileItem;						/* メモリ受信原稿種別 */
	UWORD SYS_RxMemoryFileNo;						/* メモリ受信原稿ナンバー */
	UWORD CommandFilePage;							/* 送信総枚数 */
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/4/22
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  通信起動時に必要な大域変数構造体
************************************************************************/
#define DPR_REDIAL_BUF_MAX		41

struct DPR_FCM_StartData_t {
	UBYTE SYS_RedialBuffer[DPR_REDIAL_BUF_MAX];
	UWORD	CompaileDammy;
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/4/22
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  ページ間に必要な大域変数構造体
************************************************************************/
struct DPR_FCM_PageData_t {
	UWORD	TxMemoryFileItem;
	UWORD	CompaileDammy;
};


/************************************************************************
*               BY:  M.Kotani
*             DATE:  96/4/22
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  通信終了時に必要な大域変数構造体
************************************************************************/
#define	DPR_ERROR_PAGE			6

struct DPR_FCM_EndData_t {
	UWORD SYS_FaxCommStage;
	UWORD SYS_FaxComType;
	UWORD SYS_FaxComTxType;
	UWORD SYS_TxTotalPage;
	UWORD SYS_RxTotalPage;
	UWORD SYS_RxMemoryFileItem;
	UWORD TxMemoryFileItem;
	UWORD RxMode;
	UWORD TxMode;
	UWORD FaxComTXorRX_Sign;
	UWORD FaxCompatibleErrorCode;
	UWORD FaxComResult;
	UWORD SYS_VoiceCallAccepted;
	UWORD SYS_TensouJushinFlag;
	UWORD FirstTxMode;
	UWORD SYS_V34ProcedureExecutingFlag;
	UWORD JournalTxTotalCount;
	UWORD JournalRxTotalCount;
	UBYTE TxResponsedRTN_PageSign[DPR_ERROR_PAGE];
	UBYTE NonStandardID[DPR_TTI_ID_MAX];
	UBYTE StandardID[DPR_ID_MAX];
	UWORD	CompaileDammy;
};


/************************************************************************
*               BY:  Y.Murata
*             DATE:  96/12/09
*             TYPE:  DEFINE
*      VAR TO HOLD:
*      DESCRIPTION:  回線テスト定義
************************************************************************/
struct DPR_SYS_FactoryOptModemData_t {
	UWORD	Item;			/* ﾘﾚｰﾃｽﾄ、ﾄｰﾅﾙﾃｽﾄ、DTMFﾃｽﾄ */
	UWORD	Kind;			/* ﾃｽﾄ項目種別 */
	UWORD	BaudRate;		/* PIX Symbol Rate */
	UWORD	DataRate;		/* PIX Speed */
	UWORD	PIX_Pattern;	/* PIX のﾊﾟﾀｰﾝ V17以下のみ有効 */
	UWORD	StackNumber;	/* ｽﾀｯｸﾅﾝﾊﾞｰ */
};


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/07/22
*             TYPE:  define
*      VAR TO HOLD:  DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  プリンターステータス
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
/* 基本ステータス */
#define	DPR_PCR_STAT_PRINTER_READY		(UWORD)0x0000	/** Ｒｅａｄｙ状態                         */
#define	DPR_PCR_STAT_PRINTER_WARMUP		(UWORD)0x0001	/** ウォームアップ中                       */
#define	DPR_PCR_STAT_PRINTING			(UWORD)0x0002	/** プリント中                             */
#define	DPR_PCR_STAT_PC_PRINTING		(UWORD)0x0004	/** ＰＣプリント中                         */
#define	DPR_PCR_STAT_PRINTER_PAUSE		(UWORD)0x0008	/** 休止状態                               */
#define	DPR_PCR_STAT_PRINTER_ERROR		(UWORD)0x0010	/** プリンターエラー                       */

/* カバーステータス */
#define	DPR_PCR_STAT_PRINTER_OPEN		(UWORD)0x0002	/** プリンターカバーオープン               */
#define	DPR_PCR_STAT_CASSETTE1_OPEN		(UWORD)0x0004	/** カセット１オープン                     */
#define	DPR_PCR_STAT_CASSETTE2_OPEN		(UWORD)0x0008	/** カセット２オープン                     */
#define	DPR_PCR_STAT_CASSETTE3_OPEN		(UWORD)0x0010	/** カセット３オープン                     */
#define	DPR_PCR_STAT_CASSETTE4_OPEN		(UWORD)0x0020	/** カセット４オープン                     */
#define	DPR_PCR_STAT_1JAM_OPEN			(UWORD)0x0040	/** ジャム１処理カバーオープン             */
#define	DPR_PCR_STAT_2JAM_OPEN			(UWORD)0x0080	/** ジャム２処理カバーオープン             */
#define	DPR_PCR_STAT_3JAM_OPEN			(UWORD)0x0100	/** ジャム３処理カバーオープン             */
#define	DPR_PCR_STAT_4JAM_OPEN			(UWORD)0x0200	/** ジャム４処理カバーオープン             */

/* プリンターステータス１ */
#define	DPR_PCR_STAT_ERROR_MANUAL		(UWORD)0x0001	/** 手差しでエラー発生の為プリント不可     */
#define	DPR_PCR_STAT_ERROR_CASSETTE1	(UWORD)0x0002	/** カセット１でエラー発生の為プリント不可 */
#define	DPR_PCR_STAT_ERROR_CASSETTE2	(UWORD)0x0004	/** カセット２でエラー発生の為プリント不可 */
#define	DPR_PCR_STAT_ERROR_CASSETTE3	(UWORD)0x0008	/** カセット３でエラー発生の為プリント不可 */
#define	DPR_PCR_STAT_ERROR_CASSETTE4	(UWORD)0x0010	/** カセット４でエラー発生の為プリント不可 */

/*-------------------------------------------------------------------------
** 自動カセット選択時に用紙なしとなった時に、用紙補給してほしいカセット
** 1997/08/10 H.Yoshikawa ICHOUをコピー By M.Tachibana 1997/09/19
*/
#define	DPR_PCR_STAT_AUTO_NO_M_PAPER	(UWORD)0x0100	/** 手差し記録紙無し（自動カセット選択時）		*/
#define	DPR_PCR_STAT_AUTO_NO_PAPER1		(UWORD)0x0200	/** カセット１記録紙無し（自動カセット選択時）  */
#define	DPR_PCR_STAT_AUTO_NO_PAPER2		(UWORD)0x0400	/** カセット２記録紙無し（自動カセット選択時）  */
#define	DPR_PCR_STAT_AUTO_NO_PAPER3		(UWORD)0x0800	/** カセット３記録紙無し（自動カセット選択時）  */
#define	DPR_PCR_STAT_AUTO_NO_PAPER4		(UWORD)0x1000	/** カセット４記録紙無し（自動カセット選択時）	*/

/* プリンターステータス２ */
#define	DPR_PCR_STAT_NO_MANUAL_PAPER	(UWORD)0x0001	/** 手差し記録紙無し                       */
#define	DPR_PCR_STAT_NO_PAPER1			(UWORD)0x0002	/** カセット１記録紙無し                   */
#define	DPR_PCR_STAT_NO_PAPER2			(UWORD)0x0004	/** カセット２記録紙無し                   */
#define	DPR_PCR_STAT_NO_PAPER3			(UWORD)0x0008	/** カセット３記録紙無し                   */
#define	DPR_PCR_STAT_NO_PAPER4			(UWORD)0x0010	/** カセット４記録紙無し                   */
#define	DPR_PCR_STAT_NO_CARTRIDGE		(UWORD)0x0020	/** ドラム／トナーカートリッジ無し         */
#define	DPR_PCR_STAT_NO_INK				(UWORD)0x0040	/** トナーエンプティorトナー残量規定量以下 */
#define	DPR_PCR_STAT_NO_INK_STOP		(UWORD)0x0080	/** トナーエンプティ（プリント禁止）       */
#define	DPR_PCR_STAT_END_DRUM			(UWORD)0x0100	/** ドラム交換                             */
#define	DPR_PCR_STAT_USEDTONERNEARFULL	(UWORD)0x0200	/** 廃トナーニアフル（プリント可）         */
#define	DPR_PCR_STAT_USED_TONER_FULL	(UWORD)0x0400	/** 廃トナーニアフル（プリント不可）       */
#define	DPR_PCR_STAT_CHANGE_BATTERY		(UWORD)0x0800	/** 帯電器交換                             */
#define	DPR_PCR_STAT_END_DRUM_STOP		(UWORD)0x0800	/** ドラム交換（プリント禁止）             *//* By M.Tachibana 1998/01/30 */
#define	DPR_PCR_STAT_NO_TONAR			(UWORD)0x1000	/** トナーカートリッジ無し                 */
#define	DPR_PCR_STAT_NO_DRUM			(UWORD)0x2000	/** ドラムカートリッジ無し                 */

/* プリンターステータス３ */
#define	DPR_PCR_STAT_PAPER_JAM			(UWORD)0x0001	/** いづれかのジャムが発生                 */
#define	DPR_PCR_STAT_MISS_FEED_JAM		(UWORD)0x0002	/** 給紙ジャム                             */
#define	DPR_PCR_STAT_1ST_FEED_JAM		(UWORD)0x0004	/** カセット１給紙ジャム                   */
#define	DPR_PCR_STAT_2ND_FEED_JAM		(UWORD)0x0008	/** カセット２給紙ジャム                   */
#define	DPR_PCR_STAT_3RD_FEED_JAM		(UWORD)0x0010	/** カセット３給紙ジャム                   */
#define	DPR_PCR_STAT_4TH_FEED_JAM		(UWORD)0x0020	/** カセット４給紙ジャム                   */
#define	DPR_PCR_STAT_MANUAL_FEED_JAM	(UWORD)0x0040	/** 手差し給紙ジャム                       */
#define	DPR_PCR_STAT_REG_JAM			(UWORD)0x0080	/** 搬送部付近or感光体付近でジャム発生     */
#define	DPR_PCR_STAT_EXIT_JAM			(UWORD)0x0100	/** 定着器付近でジャム発生                 */
#define	DPR_PCR_STAT_SIZE_ERROR			(UWORD)0x0200	/** サイズエラー                           */

/* プリンターステータス４ */
#define	DPR_PCR_STAT_UNIT_ERROR			(UWORD)0x0001	/** 定着器の異常                           */
#define	DPR_PCR_STAT_SCANNING_ERROR		(UWORD)0x0002	/** ポリゴンスキャナ／スキャナモータの異常 */
#define	DPR_PCR_STAT_HSYNC_ERROR		(UWORD)0x0004	/** レーザーの異常                         */
#define	DPR_PCR_STAT_MOTOR_ERROR		(UWORD)0x0008	/** メインモータの異常                     */
#define	DPR_PCR_STAT_INSIDE_FAN_ERROR	(UWORD)0x0010	/** 機内冷却ファンの異常                   */
#define	DPR_PCR_STAT_PS_FAN_ERROR		(UWORD)0x0020	/** 電源冷却ファン／ファンモータの異常     */
#define	DPR_PCR_STAT_SERIAL_ERROR		(UWORD)0x0040	/** ＳＥＲＩＡＬエラー                     */
#define	DPR_PCR_STAT_NO_COUNTER			(UWORD)0x0080	/** トータルカウンタ抜け                   */
#define	DPR_PCR_STAT_RESET_ERROR		(UWORD)0x0100	/** プリンタ初期化エラー                   */
#define	DPR_PCR_STAT_COPY_ERROR			(UWORD)0x0200	/** 転写器異常                             */
#define	DPR_PCR_STAT_DRUM_ERROR			(UWORD)0x0400	/** ドラム異常 By M.Tachibana 1997/09/19   */
#endif


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/08/08
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  記録紙データフォーマットテーブル
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
struct DPR_PCR_PAPER_DATA_FORMAT_t {
	UWORD	LeftWhiteAddDot;		/* 左白付加ドット数   */
	UWORD	ValidDataDot;			/* 有効データドット数 */
	UWORD	RightWhiteAddDot;		/* 右白付加ドット数   */
	UWORD	ValidDataLine;			/* 有効データライン数 */
};
#endif

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/08/10
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  メモリ・ライト・オープン
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
#define	DPR_PCR_MANUAL_CASSETTE		0		/* 手差し     */
#define	DPR_PCR_CASSETTE1			1		/* カセット１ */
#define	DPR_PCR_CASSETTE2			2		/* カセット２ */
#define	DPR_PCR_CASSETTE3			3		/* カセット３ */
#define	DPR_PCR_CASSETTE4			4		/* カセット４ */
#define	DPR_PCR_AUTO_CASSETTE		5		/* 自動選択   */
#if (PRO_PRINT_TYPE == LASER)
#define	DPR_PCR_MAX_CASSETTE_UNIT	DPR_PCR_CASSETTE1	/* 最大接続カセット数 */
#endif
#if (PRO_PRINT_TYPE == LED)
#define	DPR_PCR_MAX_CASSETTE_UNIT	DPR_PCR_CASSETTE3	/* 最大接続カセット数 */
#endif

/*#define	MEM_OK						0			/* １ブロック獲得                         */
#define	DPR_PCR_CASSETTE_OK			MEM_OK		/* 指定カセットに指定記録紙あり           */
/*#define	MEM_BLOCK_OVER				0xFFFE		/* 獲得不可（メモリオーバー）             */
#define	DPR_PCR_UNIT_NOTHING		0xFFFD		/* 指定カセット（手差し）ユニットなし     */
#define	DPR_PCR_CASSETTE_OPEN		0xFFFC		/* 指定カセットオープン                   */
#define	DPR_PCR_NO_PAPER			0xFFFB		/* 指定カセット（手差し）に記録紙なし     */
#define	DPR_PCR_DIFFERENT_PAPER		0xFFFA		/* 指定カセット（手差し）に指定記録紙なし */
#endif


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/09/13
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  プリンタ識別ＩＤの長さ
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
/* とりあえずここに定義しておきます */
 #if (PRO_PRINT_TYPE == LASER)
/*#define	DPR_PCR_DEVICE_ID_LENGTH	0x32 */	/* DPR_PCR_DeviceID[]の長さ */
#define	DPR_PCR_DEVICE_ID_LENGTH	0x34	/* DEVICE ID 1997/12/27 *//* DPR_PCR_DeviceID[]の長さ */
 #else
#define	DPR_PCR_DEVICE_ID_LENGTH	0x3A	/* DPR_PCR_DeviceID[]の長さ 0x32 -> 0x3A By M.Tachibana 1997/12/04 */
 #endif
#endif


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/09/20
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  ＰＣ受信原稿プリント情報
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
struct DPR_PCR_PcRxPrintData_t {
	UBYTE	PrintDensity;	/* 印字濃度         */
	UBYTE	TonarSaveMode;	/* トナーセーブ設定 */
	UBYTE	ReserveNumber;	/* プリント部数     */
	UBYTE	JamRecovery;	/* JAM リカバリ有無 By J.Miyazaki 1996/10/29 */
	UBYTE	InchData;		/* 転送データインチorミリ By J.Miyazaki 1996/11/27 */
	UBYTE	OHPMode;		/* ＯＨＰ印刷設定 By J.Miyazaki 1997/02/03 */
};
#endif


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/09/25
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  プリンタエンジン情報テーブル定義数
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
#define	DPR_PCR_ENGINE_SPEC_NO		6
#endif


/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/10/01
*             TYPE:  define
*      VAR TO HOLD:
*      DESCRIPTION:  メモリ容量
************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 */
#define	DPR_PCR_MEMORY_CAPACITY		1024	/* 1024 Kbyte */
 #if (PRO_PRINT_TYPE == LED)
#define	DPR_PCR_STANDARD_MEMORY		1888	/* 1896 */
#define	DPR_PCR_SCRAMBLE_MEMORY		452		/* 460 */
 #else
/* #define	DPR_PCR_STANDARD_MEMORY		804		868 */
#define	DPR_PCR_STANDARD_MEMORY		((MEM_FAT_AREA_STANDARD - 5) * 4)		/*((458-5(by Y.Murata))*4)デファインから参照するように変更 M.Kotani1997/12/18*/
 #endif
#endif


/************************************************************************
*               BY:  Y.Matsukuma
*             DATE:  97/2/24
*             TYPE:  struct
*      VAR TO HOLD:  DPR_SlaveBoardUpLoadMemory.DataArea
*                    DPR_SlaveBoardDownLoadMemory.DataArea
*      DESCRIPTION:  連続ポーリング構造体転送用バッファ定義
*                    各メンバーの詳細は、大機能SYS_??????を参照のこと
*				注： 電話番号のタグ名が一括送信のものになっているが、
*					 SYS_???で使っていたコマンドファイル用のタグが変更され、
*					 使えなくなり、この様になった。
*					 構造的には、問題なし。
************************************************************************/
struct DPR_ContinuousPollingData_t {
		UWORD	Status;			/* 使用状況 （コマンドファイルの使用状況と同じ値がはいる) */
		UWORD	StartTime_L;	/* 連続ポーリング開始時刻 (1992年1月1日0時0分0秒からの累積秒数) */
		UWORD	StartTime_H;	/* 連続ポーリング開始時刻 (1992年1月1日0時0分0秒からの累積秒数) */
		UWORD	EndTime_L;		/* 連続ポーリング終了時刻 (1992年1月1日0時0分0秒からの累積秒数) */
		UWORD	EndTime_H;		/* 連続ポーリング終了時刻 (1992年1月1日0時0分0秒からの累積秒数) */
		struct	DPR_BatchTxDialData_t	Dial[DPR_COM_DIAL_MAX]; /* 電話番号 */
		UBYTE	Dummy[DPR_COM_DIAL_MAX];
		UBYTE	DepartmentCode_L;	/* 部門コード */
		UBYTE	DepartmentCode_H;	/* 部門コード */
		UBYTE	PIN_AccessMode;	/*  コマンド登録時のＰＩＮアクセスモード */
		UBYTE	PIN_AccessNumber[DPR_PIN_MAX]; /* ＰＩＮ番号 BCDで８桁まで*/
};


/*Ｒ２８８Ｆステータス転送用*/
struct	DPR_ModemInternalStatusTable_t	{
	UWORD	Data[3];
	UWORD	Timer_L;
	UWORD	Timer_H;
};

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  97/10/27
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  回転基盤セルフチェックレスポンス
************************************************************************/
#if (PRO_ROTATE == ENABLE)
		#define	ROT_TEST_OK							0
		#define	ROT_TEST_ONBOARD_DPRAM_NG			1
		#define	ROT_TEST_SRAM_NG					2
		#define	ROT_TEST_DRAM_NG					3
		#define	ROT_TEST_SLAVEBOARD_DPRAM_NG		4
#endif

#endif	/* end of file */
