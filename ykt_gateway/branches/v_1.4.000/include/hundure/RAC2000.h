//---------------------------------------------------------------------------
/****************************************************************************
* Name ...........RAC2000 DLL
* Parameter.......
* Author .........Edgar Hu (humingfei@hotmail.com,13701974214)
* Date ...........2006/02/01
* Company ........HUNDURE TECHNOLOGY CO.,LTD.USA
****************************************************************************/
#ifndef _RAC2000_H_
#define _RAC2000_H_

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

	RAC2000_API int __stdcall hacOpenChannel(const char *sComm,unsigned int iPort,HANDLE *hComm);
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
	RAC2000_API int __stdcall hacPollingCommand (int iNodeID,int iPrevRecord,unsigned char *cReceiveData,
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
	RAC2000_API int __stdcall hacAddCard (int iNodeID,const char *cCardNo,int iCardLen,const char *cPassword,
					int iPassLen,int iTimeZone,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelCard (int iNodeID,const char *cCardNo,int iCardLen,HANDLE hComm,
					unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddZCard (int iNodeID,const char *cCardNo,int iCardLen,char *cPassword,
					int iPassLen,char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelZCard (int iNodeID,const char *cCardNo,int iCardLen,HANDLE hComm,
					unsigned int iTimeout);
	RAC2000_API int __stdcall hacGetRAMData (int iNodeID,unsigned char *cRAMData,int *iReceiveDataLen,
					unsigned int iRAMAddr,int iRAMLen,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacSetRAMData (int iNodeID,unsigned char *cRAMData,unsigned int iRAMAddr,int iRAMLen,
					HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacAddVisitorCard (int iNodeID,char *cCardNo,int iCardLen,char *cPassword,int iPassLen,
				char *cStartDate,char *cStartTime,char * cEndDate,char * cEndTime,int iWeek,int iTimes,int iSerial,
				char cStatus,HANDLE hComm,unsigned int iTimeout);
	RAC2000_API int __stdcall hacDelVisitorCard (int iNodeID,int iSerial,HANDLE hComm,unsigned int iTimeout);

#ifdef __cplusplus
}
#endif
#endif // _RAC2000_H_

