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
//�򿪴���
	int OpenPort(int port,int band);
	//������Э��ָ��
	int  SendCommand(const byte *sbuff,short slen,byte * rbuff,short *rlen,int timeout=2000);
	//�ϵ縴λ
	int PowerOn();
	//Ѱ��
	int RequestCard(char CardPhyID[17]);
	//�µ�
	int PowerOff();
	//CPU��ֱָͨ��
	int Apdu(const byte *sSendData, byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen);
	int Apdu4Hex(const char *sSendData, byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen);
	//��ȡ������Ϣ
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