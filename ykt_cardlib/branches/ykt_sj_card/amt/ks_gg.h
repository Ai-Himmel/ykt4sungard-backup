#ifndef __KS_GG_H_
#define __KS_GG_H_

#include "stdlib.h"
#include "stdio.h"

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef WORD
#define WORD short
#endif

//#include "string.h"

//extern void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
//extern void hex2dec(char *sHex,unsigned char * sDec,int dec_len);
//extern int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);
//extern int  bcd2dec(unsigned char *sBcdStr,int bcd_len,char *sDecStr);

// 串口设备描述符
#define COMM_DEVFD 4
// M1卡射频活动模式
#define ACTIVE_MODE 0

int Rc_OpenComm();
void Rc_CloseComm();
int GetMFLastErr();
int MF_ReadSeriesNo(unsigned char *serial);
int SMT_RequestCardExist(unsigned char ucSerialNo[4], unsigned char ucType[1]);
int SMT_LoadDll();
int SMT_ControlBuzzer();
int SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect);
int SMT_ConnectMF280(int port, int baud);
int SMT_CloseMF280();
int SMT_WriteBlock(int Sector, int BlockNo, unsigned char *BlockBuf);
int SMT_ReadBlock(int Sector, int BlockNo, unsigned char *BlockBuf);
int SMT_SleepCard();
int SMT_GetDllVersion(char *ks_ver_no, char *ks_ver_dcb);

#endif
