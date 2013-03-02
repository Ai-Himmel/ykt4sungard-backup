
// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Winsock2.h>
// TODO: 在此处引用程序要求的附加头文件
#endif

#ifdef GCU3_EXPORTS
#define GCU3_API __declspec(dllexport)
#else
#define GCU3_API __declspec(dllimport)
#endif



GCU3_API int __stdcall hrReadRelayStatus (HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,int *iReadValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrReadSensorStatus (HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,int *iReadValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrReadTime (HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,char *cDate,char *cTime,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrReadReaderStatus (HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,int *iReadValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrReadMiare(HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,long *iReadValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrReadInfo(HANDLE hComm,int iGCUID,int iDeviceID,int iReadTimeOut,unsigned char * cReadBuff,int * iReturnCode,unsigned int iTimeout);

GCU3_API int __stdcall hrWriteSensor (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iWriteValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteDoorRelay (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iActionMode,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteAlarmRelay (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iActionMode,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteReaderStatus (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iWriteValue,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteRelayPulseTime(HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iRelay,int iSecond,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteTime (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,char *cDate,char *cTime,int * iReturnCode,unsigned int iTimeout);
GCU3_API int __stdcall hrWriteDoorSensorTime (HANDLE hComm,int iGCUID,int iDeviceID,int iWriteTimeOut,int iSecond,int * iReturnCode,unsigned int iTimeout);


