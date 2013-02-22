
#include "stdafx.h"
//#include "NL8900.h"
//#include "8900RfCard.h"
//#include "UseCom.h"

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif
#define STX 0x02
#define ETX 0x03
#define ACK 0x06
#define DLE 0x10
#define NAK 0x15
/* 以下是系统响应码
 * rsTimeOut:		命令超时
 * rsUnknowCmd:		未知命令
 * rsTransErr:		传输错误	
 */
#define rsSuccess		 1
#define rsTimeOut		-1
#define rsUnknowCmd		-2
#define rsTransErr		-3
#define rsUnknowResp	-4
/*以下是rf_20的响应
rrERR_FORMAT           发送命令参数错误
rrERR_DATAFORMAT       发送的数据格式错误
//       未初始化(卡中的数据不适合作加减运算)
rrERR_LENGTH           接收的数据长度错误
rrERR_READ             读错误
rrERR_WRITE            写错误
rrERR_LESS             
rrERR_BCC              校验错误 
*/

#define rrERR_FORMAT       -4001
#define rrERR_DATAFORMAT   -4002
#define rrERR_LENGTH       -4003
#define rrERR_READ         -4004
#define rrERR_WRITE        -4005
#define rrERR_LESS         -4006
#define rrERR_BCC          -4007
/*COM */
#define	_COM_NOT_AVAILABLE			-0x10
#define _COM_SETUP_FAILED			-0x11
#define _COM_READ_TIMEOUT			-0x12
#define _COM_READ_LEN_FAILED		-0x13
#define _COM_READ_ENDCODE_FAILED	-0x14
#define _COM_WRITE_FAILED			-0x15
#define _COM_WRITE_TIMEOUT			-0x16

//enum { Sync,Asyn,RS485,RS232 };	
/***/
typedef int (*FunTypeOne)(unsigned char*);
typedef int (*FunTypeTwo)(unsigned char,unsigned char,unsigned long ,unsigned long ,unsigned long *,unsigned long *);
typedef int (*FunTypeThree)(void);
typedef int (*FunTypeFoura)(unsigned char,unsigned char,unsigned char );
typedef int (*FunTypeFourc)(unsigned char,unsigned char,char *);
typedef int (*FunTypeFive)(unsigned char,unsigned char,unsigned long,unsigned long*);
typedef int (*FunTypeSix)(unsigned char*,unsigned char*);
typedef int (*FunTypeSeven)(char*,int);
typedef int (*FunTypeEighta)(unsigned char,unsigned char,unsigned long *,unsigned char *);
typedef int (*FunTypeEightb)(unsigned char,unsigned char,unsigned long ,unsigned char *,unsigned long *_NSnr);
typedef const char *(*FunTypeNine)(int);
typedef int (*FunTypeTen)(int,unsigned char*);
typedef int (*FunTypeSixa)(unsigned char,unsigned long *);


FunTypeOne Rf_GetStatus,Rf_GetSerial;
FunTypeTwo Rf_HL_Decrement,Rf_HL_Increment;
FunTypeThree Rf_ComClose;
FunTypeFoura Rf_LoadKey;
FunTypeFourc Rf_StoreKey;
FunTypeFive Rf_HL_Initval;
FunTypeSeven Rf_ComInit;
FunTypeEighta Rf_HL_Write;
FunTypeEightb Rf_HL_Read;
FunTypeNine Rf_GetErrMsg;
FunTypeSixa Rf_request,Rf_anticoll;
/***/
/*
typedef int (*FunTypeOne)(unsigned char*);
typedef int (*FunTypeTwo)(unsigned char,unsigned char,unsigned long ,unsigned long ,unsigned long *,unsigned long *);
typedef int (*FunTypeThree)(void);
typedef int (*FunTypeFoura)(unsigned char,unsigned char,unsigned char *);
typedef int (*FunTypeFourb)(unsigned char,unsigned char,char *);
typedef int (*FunTypeFive)(unsigned char,unsigned char,unsigned long,unsigned long*);
typedef int (*FunTypeSix)(unsigned char*,unsigned char*);
typedef int (*FunTypeSeven)(char*,int);
typedef int (*FunTypeEighta)(unsigned char,unsigned char,unsigned long *,unsigned char *);
typedef int (*FunTypeEightb)(unsigned char,unsigned char,unsigned long ,unsigned char *,unsigned long *_NSnr);
typedef const char *(*FunTypeNine)(int);
typedef int (*FunTypeTen)(int,unsigned char*);



FunTypeOne Rf_GetStatus;
FunTypeTwo Rf_HL_Decrement,Rf_HL_Increment;
FunTypeThree Rf_ComClose;
FunTypeFoura Rf_LoadKey;
FunTypeFourb Rf_LoadKeyHex;
FunTypeFive Rf_HL_Initval;
FunTypeSeven Rf_ComInit;
FunTypeEighta Rf_HL_Write;
FunTypeEightb Rf_HL_Read;
FunTypeNine Rf_GetErrMsg;
*/

typedef int (*icFunTypeOne)(char *);
typedef int (*icFunTypeFive)(char *,unsigned char *);
typedef int (*icFunTypeTwo)(int);
typedef int (*icFunTypeThree)(void);
typedef BYTE (*icFunTypeThree_b)(void);
typedef int (*icFunTypeFour)(char *);
typedef int (*icFunTypeThree_a)(unsigned char *);
//typedef int (*icFunTypeFive)(CString, int);
typedef int (*icFunTypeSix)(char *, int, int);
typedef int (*icFunTypeSeven)(char *, int );
typedef int (*icFunTypeSeven_a)(char *, int);
typedef int (*icFunTypeEight)(char *, char *);
typedef int (*icFunTypeNine)(char *, char *,int,int);
typedef int (*icFunTypeTen)(int,char *, char *);
typedef void(*icFunTypeNine_a)(char *,int);
typedef void(*icFunTypeNine_b)(BOOL);

icFunTypeOne	    IC_SelectCard,IC_Powerdown;
//icFunTypeOne_a	    IC_ReadRandom,IC_Powerup;
icFunTypeTwo	    IC_setWaitTime,ICMag_ErrorJudge,ICMag_OutError,SelectIcCardType;
icFunTypeThree	    ICMag_CloseCom,ICMag_OpenCom,IC_StopOper	;
icFunTypeThree_a	IC_ReadState,ICMag_ReadEdition;
icFunTypeFour		IC_SoftRest;
icFunTypeFive		IC_Powerup,IC_ReadRandom;
icFunTypeSeven		ICMag_ComInit;
icFunTypeEight		IC_ReadCmd;
icFunTypeNine		Mag_ReadCard;
icFunTypeNine_a		ICMag_GetErrMsg;
icFunTypeNine_b		ICMag_SetEscValue;
icFunTypeTen        IC_IcCRW;
icFunTypeFour		IC_getReceData;
icFunTypeThree_b	IC_getCdType;
icFunTypeThree	    IC_getReceLen	;
 
//icFunTypeTwo	    IC_setTrackNum;
//icFunTypeSeven_a	IC_ReadAndWrite;
//icFunTypeFive		IC_readTrack2,IC_readTrack3,IC_readTrack23;		
//icFunTypeSix		IC_ReadPowerup;
/*钩子函数定义*/
typedef BOOL (*gFunTypeOne)(HWND hwnd);
typedef BOOL (*gFunTypeTwo)(void);
typedef BOOL (*gFunTypeThree)(char *action,char *msg=NULL,int timeout=0,int bForce=0);
typedef void (*gFunTypeFour)(void);
gFunTypeOne InitStatusDetect;
gFunTypeTwo ExitStatusDetect;
gFunTypeThree ShutDownSys;
gFunTypeFour LockKey,UnLockKey;