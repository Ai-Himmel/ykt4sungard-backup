//---------------------------------------------------------------------------
/****************************************************************************
* Name ...........GCU3 DLL
* Parameter.......
* Author .........Edgar Hu (humingfei@hotmail.com,13701974214)
* Date ...........2006/02/01
* Company ........HUNDURE TECHNOLOGY CO.,LTD.USA
****************************************************************************/
#ifndef _GCU3_H_
#define _GCU3_H_

#ifdef HAS_HUNDURE_SUPPORT

#ifdef GCU3_EXPORTS
#define GCU3_API __declspec(dllexport)
#else
#define GCU3_API __declspec(dllimport)
#endif

typedef struct struct_CardFormat
{
	int iType;
	int iCompressed;
	int iCardLen;
	char cCardNo[20];
	int iPassLen;
	char cPassword[10];
	int iDisplayLen;
    int iDisplayType;
	int iDisplayID;
	char cDisplayText[64];
	int iLimitDate;
	char cStartDate[10];
	char cEndDate[10];
	int iHoliday;
	int iGroupType;
    int iGroup;
	int iDoors;
	unsigned char cTimeZone[64];
} struct_CardFormat;

typedef struct stPollRecord
{
	char cEventCode[10];	//Event Code
	char cDateTime[20];		//Date Time
	char cCard[20];			//Card Number
	char cDeviceID[10];		//Device ID
	char cStatusCode[10];	//Status Code
} stPollList_GCU;

//Reserve for multithread
class GCU3_API CGCU3 {
public:
	CGCU3(void);
};

extern GCU3_API int nGCU3;
GCU3_API int fnGCU3(void);

#ifdef __cplusplus
extern "C" {
#endif

	GCU3_API int __stdcall hsGCUOpenChannel(HANDLE *hComm,const char *sComm,unsigned int iPort);
	GCU3_API int __stdcall hsGCUCloseChannel(HANDLE hComm);
	GCU3_API int __stdcall hsGCUReadData(HANDLE hComm,unsigned char *cBuffer,int *iDataLen,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteData(HANDLE hComm,unsigned char *cBuffer,int iDataLen,int *iWrittenLen,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUClearBuffer(HANDLE hComm);
	GCU3_API int __stdcall hsGCURead (HANDLE hComm,unsigned char *cReceiveData,int * iReceiveLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUSet(HANDLE hComm,int iGCUID, int iFunction,unsigned char *cSendData,int iSendLen,
					unsigned char *cReceiveData,int * iReceiveLen,int * iReturnCode,unsigned int iTimeout);

	GCU3_API int __stdcall hsGCUPollingCommand(HANDLE hComm,int iGCUID,int iPrevRecord,unsigned char *cReceiveData,
				int *iReceiveLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUPolling(HANDLE hComm,int iGCUID,int iPrevRecord,stPollList_GCU *stRecord,
					int *iRecord,int iCardType,int iCodeType,int * iReturnCode,unsigned int iTimeout);

	GCU3_API int __stdcall hsGCUReadTable(HANDLE hComm,int iGCUID,int iTable,unsigned char *cTableData,int *iTableLen,
					int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUMatrixReadTable (HANDLE hComm,int iGCUID,unsigned char *cAddrData,int iAddrLen,
					unsigned char *cTableData,int *iTableLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteTable(HANDLE hComm,int iGCUID,int iTable,unsigned char *cTableData,int iTableLen,
					int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUMatrixWriteTable(HANDLE hComm,int iGCUID,unsigned char *cTableData,int iTableLen,int * iReturnCode,unsigned int iTimeout);

	GCU3_API int __stdcall hsConstructRecord(int iType ,int iCompressed,int iCardLen,char *cCardNo,int iPassLen,char *cPassword,
					int iDisplayLen,int iDisplayType,int iDisplayID,char * cDisplayText,int iLimitDate,char * cStartDate,char * cEndDate,
					int iHoliday,int iGroupType,int iGroup,int iDoors,unsigned char *cTimeZone,unsigned char *cRecordBin,int *iRecordLen);

	GCU3_API int __stdcall hsGCUDeleteUserRecord(HANDLE hComm,int iGCUID,int iCompressed,const char *cCardNo,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUQueryUserRecord(HANDLE hComm,int iGCUID,int iCompressed,const char *cCardNo,unsigned char * cCardFormatData,
					int * iCardFormatLen,int * iReturnCode,unsigned int iTimeout);

	GCU3_API int __stdcall hsGCUInsertMultiUserRecord(HANDLE hComm,int iGCUID,int iRecord,struct_CardFormat * stRecord,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUDeleteAllUserRecord(HANDLE hComm,int iGCUID,int * iReturnCode,unsigned int iTimeout);

	GCU3_API int __stdcall hsGCUReadParamenter(HANDLE hComm,int iGCUID,unsigned char *cParaData,int *iParaLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadOtherParamenter(HANDLE hComm,int iGCUID,unsigned char *cAddrData,int iAddrLen,
					unsigned char *cParaData,int *iParaLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteParamenter(HANDLE hComm,int iGCUID,unsigned char *cParaData,int iParaLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteOtherParamenter(HANDLE hComm,int iGCUID,unsigned char *cParaData,int iParaLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadPollingID(HANDLE hComm,int iGCUID,unsigned char *cPollData,int *iPollLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWritePollingID(HANDLE hComm,int iGCUID,unsigned char *cPollData,int iPollLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUInitial(HANDLE hComm,int iGCUID,char cInitFlag,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteAnti(HANDLE hComm,int iGCUID,int iAntiFlag,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadAnti(HANDLE hComm,int iGCUID,int *iAntiFlag,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadDevice(HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,int iIndex,unsigned char *cReadData,
					int *iReadLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteDevice(HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iIndex,unsigned char *cSendData,
					int iSendLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadTime(HANDLE hComm,int iGCUID,char *cDate,char *cTime,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWriteTime (HANDLE hComm,int iGCUID,char *cDate,char *cTime,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUGetInfo(HANDLE hComm,int iGCUID,unsigned char *cInfoData,int *iInfoLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUWritePollingIDTimeout(HANDLE hComm,int iGCUID,int iPollTimeOut,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadPollingIDTimeout (HANDLE hComm,int iGCUID,int *iPollTimeOut,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUReadDeviceType(HANDLE hComm,int iGCUID,unsigned char *cTypeData,int *iTypeLen,int * iReturnCode,unsigned int iTimeout);
	GCU3_API int __stdcall hsGCUSearchDevice(HANDLE hComm,int iGCUID,int iStartID,int iEndID,unsigned char *cTypeData,
					int *iTypeLen,int * iReturnCode,unsigned int iTimeout);

#ifdef __cplusplus
}
#endif

#endif

#endif
