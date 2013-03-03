



/*********************************************************************************************
 * PRIVATE DEFINITION
*********************************************************************************************/

#define		ND_HISTORY_ANSWERED		0x01 /* 着信した */
#define		ND_HISTORY_FAX			0x02 /* FAX 通信をしたか */
#define		ND_HISTORY_TEL1			0x04 /* TEL1 でとったか */
#define		ND_HISTORY_TEL2			0x08 /* TEL2 でとったか */
#define		ND_HISTORY_AGGREGATED	0x10 /* 集約情報か */

struct SYS_ND_CallerInformation_t {
	UBYTE		id;
	UBYTE		kind;
	union SYS_ND_InformationContent_t info;
} SYB_ND_CallerInformation[SYS_ND_CALLER_INFO_MAX];


/*********************************************************************************************
 * PUBLIC DEFINITION AND DECLARATION
*********************************************************************************************/


/*******************************************************************************************
	title 		:[ナンバーディスプレイ履歴で個々の着信前情報を記憶する構造体]
	name 		:	union SYS_ND_InformationContent_t;
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[SYS]
	date		:[1998/09/04]
	author		:[久保博]
*******************************************************************************************/

/* 	発信電話番号 
*/
struct SYS_ND_Number_t {
	UBYTE	length;
	UBYTE	number[20];
};

/* 	発信電話番号拡張情報、
	転送元電話番号拡張情報
*/
struct SYS_ND_ExtraInfoOfNumber_t {
	UBYTE	type_of_number;
	UBYTE	number_plan_identifier[2];
};

/* 	転送元電話番号
*/

struct SYS_ND_TransfererNumber_t {
	UBYTE	reason[2];
	UBYTE	length;
	UBYTE	number[20];
};

/*	メッセージ表示情報
*/

struct SYS_ND_MessageInformation_t {
	UBYTE	message_status[5];
	UBYTE	length;
	UBYTE	text[28];
};

/*	月日時分情報
*/
struct SYS_ND_Time_t {
	UBYTE	month[2];
	UBYTE	day[2];
	UBYTE	hour[2];
	UBYTRE	minute[2];
};

/*	発信企業名情報
	公衆電話情報
*/
struct SYS_ND_Text_t {
	length;
	text[20];
};

/*	発信電話番号非通知理由
	発信企業名非通知理由
*/
struct SYS_ND_Reason_t {
	UBYTE	reason;
};


union SYS_ND_InformationContent_t {
	struct SYS_ND_Number_t				number;
	struct SYS_ND_ExtraNumber_t 		extra_number;
	struct SYS_ND_TransfererNumber_t 	transferer_number;
	struct SYS_ND_MessageInformation_t 	message_info;
	struct SYS_ND_Time_t 				time;
	struct SYS_ND_Text_t 				text;
	struct SYS_ND_Reason_t 				reason;
};

#define		ND_INFO_CALLER_NUMBER			0x02
#define		ND_INFO_CALLER_EXTRA			0x21
#define		ND_INFO_CALLER_NUMBER_REASON	0x04
#define		ND_INFO_DIALIN_NUMBER			0x09
#define		ND_INFO_DIALIN_EXTRA			0x22
#define		ND_INFO_TRANSFERER_NUMBER		0x0B
#define		ND_INFO_TRANSFERER_EXTRA		0x23
#define		ND_INFO_MESSAGE					0x13
#define		ND_INFO_TIME					0x01
#define		ND_INFO_CALLER_NAME				0x07
#define		ND_INFO_CALLER_NAME_REASON		0x08
#define		ND_INFO_PUBLIC_PHONE			0x14


typedef UBYTE	SYS_ND_HistoryHandle_t;
#define 	SYS_ND_INVALID_HANDLE	0xffff


#define		ND_HISTORY_OPEN_EMPTY 				1
#define		ND_HISTORY_OPEN_NEWEST				2
#define		ND_HISTORY_OPEN_OLDEST				3

#define		ND_HISTORY_GET_NEWER_HANDLE			1
#define		ND_HISTORY_GET_OLDER_HANDLE			2

#define		ND_HISTORY_CLOSE_PRESERVE			1
#define		ND_HISTORY_CLOSE_DESTROY			2

/**************************************************************
	
	サンプルプログラム

**************************************************************/



#if 0 	/* An example */

int sample()
{
	SYS_ND_HistoryHandle_t handle;
	
	if ((handle = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_NEWEST)) == SYS_ND_INVALID_HANDLE) {
		return 0;
	}
	
	while (handle != SYS_ND_INVALID_HANDLE) {
		if (CMN_ND_HistoryCheckKind(handle, ND_INFO_CALLER_NUMBER) {
			printf("%20s\n", CMN_ND_HistoryGetRecord(handle, ND_INFO_CALLER_NUMBER)->number.number);
		}
		else if (CMN_ND_HistoryCheckKind(handle, ND_INFO_CALLER_NUMBER_REASON) {
			switch (CMN_ND_HistoryGetRecord(handle, ND_INFO_CALLER_NUMBER)->reason.reason) {
			case 'P':
				printf("The caller denies showing his/her number.\n");
				break;
			case 'O':
				printf("The number-display service is not available.\n");
				break;
			case 'C':
				printf("The call is from public phone.\n");
				break;
			case 'S':
				printf("Services are conflicting.\n");
				break;
			default:
				printf("No reason for not showing caller number is available.\n");
				break;
			}
		else {
			printf("No reason for not showing caller number is available.\n");
		}
		handle = CMN_ND_GetNextHistory(handle, ND_HISTORY_GET_OLDER_HANDLE);
	}
	CMN_ND_HistoryClose(handle, ND_HISTORY_CLOSE_PRESERVE);  /* 最後は無効なハンドルになっているが、それでもクローズ処理する */
}
#endif /* 0 */
