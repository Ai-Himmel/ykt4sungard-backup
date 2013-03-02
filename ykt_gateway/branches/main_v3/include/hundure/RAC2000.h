//---------------------------------------------------------------------------
/****************************************************************************
* Name ...........RAC2000 DLL
* Parameter.......
* Author .........Edgar Hu (humingfei@hotmail.com,13701974214)
* Date ...........2006/02/01
* Company ........HUNDURE TECHNOLOGY CO.,LTD.USA
****************************************************************************/

#ifdef RAC2000_EXPORTS
#define RAC2000_API __declspec(dllexport)
#else
#define RAC2000_API __declspec(dllimport)
#endif

typedef struct stPollList
{
	char cEventCode[5];	//Event Code
	char cDateTime[20];	//Date Time
	char cCard[20];		//Card Number
	char cDeviceID[10];	//Device ID
	char cReaderID[10];	//Reader ID
} stPollList;

//Reserve for multithread
class RAC2000_API CRAC2000 {
public:
	CRAC2000(void);
};

extern RAC2000_API int nRAC2000;
RAC2000_API int fnRAC2000(void);


#ifdef __cplusplus
extern "C" {
#endif

	RAC2000_API int __stdcall hacOpenChannelEX(char *sComm,unsigned int iPort,int iCheckStatus,HANDLE *hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacOpenChannel(char *sComm,unsigned int iPort,HANDLE *hComm);
	RAC2000_API int __stdcall hacCloseChannel(HANDLE hComm);
	RAC2000_API int __stdcall hacReadData(unsigned char *cBuffer,int *iDataLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacWriteData(unsigned char *cBuffer,int iDataLen,int *iWrittenLen,HANDLE hComm);
	RAC2000_API int __stdcall hacClearBuffer(HANDLE hComm);
	RAC2000_API int __stdcall hacHWReadCommand(int iNodeID,int iIndex,unsigned char *cSendData,int iSendDataLen,
					unsigned char *cReceiveData,int *iReceiveLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacHWWriteCommand(int iNodeID,int iIndex,unsigned char *cSendData,int iSendDataLen,
					unsigned char *cReceiveData,int *iReceiveLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacHWReadCommandEX(int iNodeID,int iIndex,unsigned char *cSendData,int iSendDataLen,
					unsigned char *cReceiveData,int *iReceiveLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacPollingCommand (int iNodeID,int iPrevRecord,int iMode,unsigned char *cReceiveData,
					int *iReceiveLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacPolling (int iNodeID,int iPrevRecord,stPollList *stRecord,
					int *iRecord,HANDLE hComm,unsigned int iTimeout,int iCardType);
	RAC2000_API int __stdcall hacGetDateTime (int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetDateTime (int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetEEData (int iNodeID,unsigned char *cEEData,int *iReceiveDataLen,
					unsigned int iEEAddr,int iEELen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetEEData (int iNodeID,unsigned char *cEEData,unsigned int iEEAddr,int iEELen,
					HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetVersion (int iNodeID,char *cData,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetSensor(int iNodeID,int *iSensor,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacRelayAction(int iNodeID,char cAction,char cMask,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddCard (int iNodeID,char *cCardNo,int iCardLen,char *cPassword,
					int iPassLen,int iTimeZone,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelCard (int iNodeID,char *cCardNo,int iCardLen,HANDLE hComm,
					unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddZCard (int iNodeID,char *cCardNo,int iCardLen,char *cPassword,
					int iPassLen,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelZCard (int iNodeID,char *cCardNo,int iCardLen,HANDLE hComm,
					unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetRAMData (int iNodeID,unsigned char *cRAMData,int *iReceiveDataLen,
					unsigned int iRAMAddr,int iRAMLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetRAMData (int iNodeID,unsigned char *cRAMData,unsigned int iRAMAddr,int iRAMLen,
					HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddVisitorCard (int iNodeID,char *cCardNo,int iCardStart,int iCardLen,
					char *cStartDate,char *cStartTime,char * cEndDate,char * cEndTime,int iWeek,int iTimes,int iSerial,
				int iAnti,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelVisitorCard (int iNodeID,int iSerial,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetLanMode(int iNodeID,char cMode,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetReader(int iNodeID,int iReaderID,int iIndex,unsigned char *cSendData,int iSendDataLen,
					HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacRestart(int iNodeID,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacPxrGetDateTime(int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacPxrSetDateTime (int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);

	RAC2000_API int __stdcall hac34Polling (int iNodeID,int iPrevRecord,stPollList *stRecord,
				int *iRecord,HANDLE hComm,unsigned int iTimeout,int iCardType);
	RAC2000_API int __stdcall hac34GetDateTime(int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34SetDateTime (int iNodeID,char *cDate,char *cTime,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34GetEEData (int iNodeID,unsigned char *cEEData,int *iReceiveDataLen,int iEEArea,unsigned int iEEAddr,
				int iEELen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34SetEEData (int iNodeID,unsigned char *cEEData,int iEEArea,unsigned int iEEAddr,int iEELen,
				HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34GetVersion (int iNodeID,char *cData,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34AddCard (int iNodeID,char *cCardNo,int iCardLen,char *cPassword,int iPassLen,
				int iTimeZone,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34DelCard (int iNodeID,char *cCardNo,int iCardLen,HANDLE hComm,
				unsigned int iTimeout);
	RAC2000_API int __stdcall hac34DelAllCard (int iNodeID,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34GetReadCardParameter(int iNodeID,int *iKeyType,int *iBlock,
				int *iStartDigit,int *iDigitLength,int *iCompact,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hac34SetReadCardParameter(int iNodeID,int iKeyType,int iBlock,
				int iStartDigit,int iDigitLength,int iCompact,unsigned char *cKeyValue,HANDLE hComm,unsigned int iTimeout);
	//RAC940,RAC960
	RAC2000_API int __stdcall hacGetFlashData (int iNodeID,unsigned char *cFlashData,int *iReceiveDataLen,unsigned int iFlashAddr,
				int iFlashLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetFlashData (int iNodeID,unsigned char *cFlashData,unsigned int iFlashAddr,int iFlashLen,
				HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetParaData (int iNodeID,unsigned char *cFlashData,int *iReceiveDataLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetParaData (int iNodeID,unsigned char *cFlashData,int iFlashLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetSysParaData (int iNodeID,unsigned char *cFlashData,int *iReceiveDataLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetSysParaData (int iNodeID,unsigned char *cFlashData,int iFlashLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetMifare(int iNodeID,int *iKeyType,int *iBlock,
				int *iStartDigit,int *iDigitLength,int *iCompact,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetMifare(int iNodeID,int iKeyType,int iBlock,
				int iStartDigit,int iDigitLength,int iCompact,unsigned char *cKeyValue,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddCardEX(int iNodeID,char *cCardNo,int iCardLen,char *cPassword,int iPassLen,
				char *cName,int iNameLen,int iTimeZone,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacHWRWCommand(int iNodeID,int iIndex,unsigned char *cSendData,int iSendDataLen,
				unsigned char *cReceiveData,int *iReceiveLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacInitial(int iNodeID,int iDeviceType,int iClearFlag,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetAgentCode(int iNodeID,unsigned char *cAgentData,int iAgentDataLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetAgentCode (int iNodeID,unsigned char *cAgentData,int *iAgentDataLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelAllCard (int iNodeID,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetCardCount (int iNodeID,HANDLE hComm,int iCount,unsigned int iTimeout);


#ifdef __cplusplus
}
#endif

