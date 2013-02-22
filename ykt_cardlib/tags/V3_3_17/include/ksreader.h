#ifndef KS_READER_H_
#define KS_READER_H_
class  CReader
{
public:
	CReader();
	~CReader();
public:
//�򿪴���
	int OpenPort(int port,int band);
	//������Э��ָ��
	int SendCommand(const byte *sbuff,short slen,byte * rbuff,short *rlen,int timeout=2000);
	//�ϵ縴λ
	int PowerOn();
	//Ѱ��
	int RequestCard(char CardPhyID[17]);
	//�µ�
	int PowerOff();
	//CPU��ֱָͨ��
	int Apdu(const byte *sSendData, byte nSendDatalen, byte *sRespData,byte &nRespDatalen);
	int Apdu4Hex(const char *sSendData, byte nSendDatalen, byte *sRespData,byte &nRespDatalen);
	//��ȡ������Ϣ
	char* GetErrMsg(int retcode, char *sMsg);
	
private:
	unsigned	char SendData[256];
	unsigned	char SendDataLen;
	unsigned	char RetCode[10];
	unsigned	char RecvData[256];
	unsigned	char RecvDataLen;
	unsigned	char m_TimeData[30];
};
#endif