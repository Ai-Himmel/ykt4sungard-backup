// YCTReaderInterface.h: interface for the CYCTReaderInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YCTREADERINTERFACE_H__608128ED_9496_4823_B15F_38D6034EC41E__INCLUDED_)
#define AFX_YCTREADERINTERFACE_H__608128ED_9496_4823_B15F_38D6034EC41E__INCLUDED_

#include <Windows.h>


#define		PICC_REQALL 0x52 
#define		PICC_REQSTD 0x26
#define		MOC_ERROR_CARD_SELECT	0x81		//ѡ��ʧ��

#define		SEND_DATA_ERROR			0x91   //���ݷ��ʹ�
#define		RECV_DATA_ERROR			0x92   //�������ݴ���


//1.========================================��ȫ�㷨===============
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );

/*=================================================================
* Function ID : YCT_VerifyPurchaseMac1
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
unsigned char *sKey,			//16�ֽڵ���������Կ
unsigned char *sRandom,			//���ѳ�ʼ���ɹ����ص�4�ֽ�α�����
unsigned long lCardInvoiceNo,	//���ѳ�ʼ������2�ֽڵ��ѻ��������				
unsigned long lPurchMoney,		//��Ҫ���ѵĽ��	
unsigned char *TerminalNo,      //�ն˺�			
* Output      : void
unsigned char *sMac1
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : ��������MAC1
*=================================================================*/
unsigned long YCT_VerifyPurchaseMac1( 
									 unsigned char *sAppNo,
									 unsigned char *sKey,
									 unsigned char *sRandom,
									 unsigned long lCardInvoiceNo,
									 unsigned long lPurchMoney,
									 unsigned char *TerminalNo,
									 unsigned char *sMac1);

/*=================================================================
* Function ID : YCT_VerifyLoadMac1
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
				unsigned char *sKey,			//16�ֽڵ�Ȧ������Կ
				unsigned char *sRandom,			//Ȧ���ʼ���ɹ����ص�4�ֽ�α�����
				unsigned long lCardInvoiceNo,	//Ȧ���ʼ���ɹ����ص�2�ֽڵĽ������
				unsigned long lCardBal,			//Ȧ���ʼ���ɹ����ص�Ǯ������ǰ���
				unsigned long lAddMoney,		//��Ҫ��ֵ�Ľ��
				unsigned char *TerminalNo,		//6�ֽڵ��ն˻����
				unsigned cha  *sMac1			//Ȧ���ʼ���ɹ����ص�4�ֽ�MAC1
* Output      : void
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : У��Ȧ���ʼ��ʱ�����ص�MAC1��������֤�û����ĺϷ���
*=================================================================*/
unsigned long YCT_VerifyLoadMac1( unsigned char *sAppNo,
								 unsigned char *sKey,
								 unsigned char *sRandom,
								 unsigned long lCardInvoiceNo,
								 unsigned long lCardBal,
								 unsigned long lAddMoney,
								 unsigned char *TerminalNo,
								 unsigned char *sMac1);
/*=================================================================
* Function ID : YCT_CalLoadMac2
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
				unsigned char *sKey,			//16�ֽڵ�Ȧ������Կ
				unsigned char *sRandom,			//Ȧ���ʼ���ɹ����ص�4�ֽ�α�����
				unsigned long lCardInvoiceNo,	//Ȧ���ʼ���ɹ����ص�2�ֽڵĽ������			
				unsigned long lAddMoney,		//��Ҫ��ֵ�Ľ��
				unsigned char *TerminalNo,		//6�ֽڵ��ն˻����
				unsigned char *sDate,			//4�ֽڽ�������(YYYYMMDD)
				unsigned char *sTime			//3�ֽڽ���ʱ��(HHMMSS)
* Output      : unsigned char *sMac2			//4�ֽڵ�MAC2
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : ����Ȧ��MAC2
*=================================================================*/
unsigned long YCT_CalLoadMac2( unsigned char *sAppNo,
							  unsigned char *sKey,
							  unsigned char *sRandom,
							  unsigned long lCardInvoiceNo,
							  unsigned long lAddMoney,
							  unsigned char *TerminalNo,
							  unsigned char *sDate,
							  unsigned char *sTime,
							  unsigned char *sMac2);

//��ȫ����MAC
unsigned char* CalSecure_MAC(
							 unsigned char *key,
							 unsigned char *random, 
							 int len,
							 unsigned char *input_data,
							 unsigned char *out_data);


//*---------------------------------------------------------------------------
//*����: CComSmart
//*����: ����ͨѶ��
//*---------------------------------------------------------------------------

class CComSmart
{
public:
	bool	m_bComStatus;
	char	m_sCom[10];
	long	m_nRecvLen;
protected:
	HANDLE   m_handle;		
protected:
	bool ClearComm(DWORD dwMask);
	bool SetEventMask(DWORD dwMask);
	bool SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut);
	bool GetEventMask(DWORD& dwMask);
	bool SetState(int nBaud, char cParity, int nDataBit, int nStopBit);
	bool GetState(DCB *pDCB);
	bool ClearError();	
public:
	CComSmart();
	~CComSmart();
	bool Open(char *sCom, int nBaudRate);
	void Close();		
	bool PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	bool PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);	
};

class CYCTReaderInterface  : public CComSmart
{
public:
	CYCTReaderInterface();
	virtual ~CYCTReaderInterface();
	BYTE* AscToBcd(BYTE* ascbuf, int ascbuf_len, BYTE* bcdbuf);
	BYTE* BcdToAsc(BYTE* bcdbuf, int bcdbuf_len,BYTE* ascbuf );
	char* trim(char* str);
public:
	bool  CPU_Open(char *sCom, int nBaudRate);
	void  CPU_Close();
	bool  CPU_PowerOn();
	bool  SAM_PowerOn();
	bool  CPU_PowerOff();		
	bool  SAM_PowerOff();	
	bool  CPU_RequestCard();
	bool  CPU_SelectCard(char sType,char* sSerialNo);		
	int   CPU_APDU_Cmd( unsigned char *sSendData, unsigned char nSendDatalen, unsigned char* sRespData,unsigned char &nRespDatalen );
	int   SAM_APDU_Cmd(int nSamSlot, unsigned char *sSendData, unsigned char nSendDatalen,unsigned char* sRespData,unsigned char &nRespDatalen );
	char* CPU_GetErrorCode(char *sMsg);
	char* Get_ErrorInfo( int nErrCode,char *sErrInfo );
public:
	int YCT_SelectMFDir(byte *ucRes);
	int YCT_SelectBankDir(byte *ucRes);
	int YCT_SelectSchoolPacketDir(byte *ucRes);
	int YCT_SelectPacketOneDir(byte *ucRes);
	int YCT_VerifyPin( char* cPin);
	int YCT_ChangePin( char* coldPin, char* cnewPin);
	int YCT_ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData);
	int YCT_ReadRecordFile(byte ucSFI,
								byte ucRecordNo,
								byte ucLength,
								byte *ucData);
	int SMT_MAC_UpdateBinaryFile(  byte ucSFI,
		byte ucOffset,
		byte ucLength,
		byte *ccAppSerailNo,
		byte *ucData );
								
private:
	BYTE  XOR( unsigned char *sBuf,int nBufLen );
	char* ltrim(char* str);
	char* rtrim(char* str);
	
	int   SendReaderCommand(char *ComPort,unsigned char Cmd,unsigned char *SendData,unsigned  char SendDataLen,unsigned char *RetCode,unsigned char *RecvData,unsigned char* RecvDataLen);
private:
	unsigned	char SendData[256];
	unsigned	char SendDataLen;
	unsigned	char RetCode[10];
	unsigned	char RecvData[256];
	unsigned	char RecvDataLen;
};

#endif // !defined(AFX_YCTREADERINTERFACE_H__608128ED_9496_4823_B15F_38D6034EC41E__INCLUDED_)
