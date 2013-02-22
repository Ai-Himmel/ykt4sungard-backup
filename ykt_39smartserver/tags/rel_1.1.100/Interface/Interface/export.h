#ifndef __EXPOERT_H__
#define __EXPOERT_H__

#include "..\..\include\common.h"

long __stdcall InitChannels(int nServer, int nFunc);
long __stdcall DestoryChannels();
long __stdcall ConnectToCenter(char *pszHost, int nPort, int nEncode);
long __stdcall DisConnect();
long __stdcall CreateNotify(char *pszBind, int nPort);
long __stdcall CloseNotify();
long __stdcall SendDataPro(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
long __stdcall RecvDataPro(char *pszBuffer, int nLen, int nTimeOut);
long __stdcall SendData(HANDLE& hHandle, int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
long __stdcall RecvData(HANDLE& hHandle, char *pszBuffer, int nLen, int nTimeOut);
long __stdcall SmartSignIn();
long __stdcall SmartSignOut();
long __stdcall SmartRegister();
long __stdcall SendDeviceTick(TSSmartDoc *pDoc);
long __stdcall ReadCardGSInfo(int nflag, TSGSJRecord *pRecord);
long __stdcall SignIn(TSSmartDoc *pDoc);
long __stdcall SignOut(TSSmartDoc *pDoc);
long __stdcall DownloadBlackCard(TSSmartDoc *pDoc, int nFlag, char *pszFileName);
long __stdcall OutputBlackCard(TSSmartDoc *pDoc, TSBlackCard *pCard);

#endif //__EXPOERT_H__