#ifndef KSCARDINTERFACE_H
#define KSCARDINTERFACE_H
int __stdcall KS_OpenPort(int port, int baud);
//打开通讯端口
int __stdcall KS_OpenCommPort();
int __stdcall KS_ClosePort();
//交易成功提示，声音较短
void __stdcall KS_Beep();
//出现错误时，可以使用该函数使读卡器长鸣一声
void _stdcall KS_BeepErr();
void __stdcall KS_GetLastErrMsg(char *sMsg);
int __stdcall KS_Init();
int __stdcall KS_RequestCard(char *sCardPhyID);
void __stdcall KS_Reset();
void __stdcall KS_SetReadFieldName(char *sFieldName);
int __stdcall KS_GetFieldVal(char *sFieldName,char *sFieldVal);
int __stdcall KS_ReadCard();
int __stdcall KS_CheckCardStatus();
int __stdcall KS_Halt();
int __stdcall KS_LoadCardKeys(const char *pwd);
//KS_Login后续版本已不用，使用KS_SignIn代替
int __stdcall KS_Login(int& nShopID,char sShopName[61]);
//KS_Pay后续版本已不用，使用KS_PayProcess代替
int __stdcall KS_Pay(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac);
int __stdcall KS_PayCancel(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefNo,char *sMac);
//取错误消息
char* __stdcall KS_GetErrMsg(char *msg);
//签到
int __stdcall KS_SignIn(int* nShopID,char sShopName[61]);
//自助设备用户签到
int __stdcall KS_UserSignIn(const char *user,const char* passwd);
//扣费预处理
int __stdcall KS_PayPrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefno,char *sMac);
//加卡余额
int __stdcall KS_CardBalanceInc(char* cGetProveFlag);
//扣卡余额
int __stdcall KS_CardBalanceDec(char* cGetProveFlag);
//取交易确认
int __stdcall KS_GetProve(char* cReWriteCardFlag);
//交易确认失败处理,如果扣款出现中途拔卡,而卡没有读到,则调用一下函数处理
int __stdcall KS_UnProveProcess();
//正式提交交易请求
int __stdcall KS_PayProcess();
//消费冲正
int __stdcall KS_PayCancelProcess(const char *sRefNo,const char *sMac,const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt);
//获取卡状态
int __stdcall KS_GetCardStatus(int cardno,char *statuscode,char *statusinfo);

//充值预处理
int __stdcall KS_RechangePrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefno,char *sMac);
//自助系统充值
int __stdcall KS_RechangeProcess(int nRechangeAmt);
#endif

