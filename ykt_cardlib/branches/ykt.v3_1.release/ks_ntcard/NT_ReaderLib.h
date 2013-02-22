#ifndef NT_READERLIB_H_
#define NT_READERLIB_H_
#include "nt_comm.h"

#ifdef _CLASSINDLL 
	#define CLASSINDLL_CLASS_DECL     __declspec(dllexport) 
#else 
	#define CLASSINDLL_CLASS_DECL     __declspec(dllimport) 
#endif 
class CLASSINDLL_CLASS_DECL CNTReader  : public CComSmart
{
public:
	CNTReader();
	~CNTReader();
public:
//打开串口
	int OpenPort(int port,int band);
	//读卡器协议指令
	int  SendCommand(const byte *sbuff,short slen,byte * rbuff,short *rlen,int timeout=2000);
	//上电复位
	int PowerOn();
	//寻卡
	int RequestCard(char CardPhyID[17]);
	//下电
	int PowerOff();
	//CPU卡直通指令
	int Apdu(const byte *sSendData, byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen);
	int Apdu4Hex(const char *sSendData, byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen);
	//读取错误信息
	char* GetErrMsg(int retcode, char *sMsg=NULL);
private:
	char	m_szErrMsg[256];
// 	unsigned	char SendData[256];
// 	unsigned	char SendDataLen;
// 	unsigned	char RetCode[10];
// 	unsigned	char RecvData[256];
// 	unsigned	char RecvDataLen;
// 	unsigned	char m_TimeData[30];
};
#endif