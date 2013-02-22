#ifndef KSCARDINTERFACE_H
#define KSCARDINTERFACE_H
int __stdcall KS_OpenPort(int port, int baud);
int __stdcall KS_ClosePort();
void __stdcall KS_Beep();
void __stdcall KS_GetLastErrMsg(char *sMsg);
int __stdcall KS_Init();
int __stdcall KS_RequestCard(char *sCardPhyID);
void __stdcall KS_Reset();
void __stdcall KS_SetReadFieldName(char *sFieldName);
int __stdcall KS_GetFieldVal(char *sFieldName,char *sFieldVal);
int __stdcall KS_ReadCard();
int __stdcall KS_CheckCardStatus();
int __stdcall KS_Login(int& nShopID,char sShopName[61]);
int __stdcall KS_Pay(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac);
int __stdcall KS_PayCancel(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefNo,char *sMac);
#endif

