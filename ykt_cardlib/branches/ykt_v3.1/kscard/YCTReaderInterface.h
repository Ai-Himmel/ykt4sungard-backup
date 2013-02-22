// YCTReaderInterface.h: interface for the CYCTReaderInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YCTREADERINTERFACE_H__608128ED_9496_4823_B15F_38D6034EC41E__INCLUDED_)
#define AFX_YCTREADERINTERFACE_H__608128ED_9496_4823_B15F_38D6034EC41E__INCLUDED_

#include <Windows.h>


#define		PICC_REQALL 0x52 
#define		PICC_REQSTD 0x26
#define		MOC_ERROR_CARD_SELECT	0x81		//选择卡失败

#define		SEND_DATA_ERROR			0x91   //数据发送错
#define		RECV_DATA_ERROR			0x92   //接收数据错误


//1.========================================安全算法===============
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );

/*=================================================================
* Function ID : YCT_VerifyPurchaseMac1
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
unsigned char *sKey,			//16字节的消费主密钥
unsigned char *sRandom,			//消费初始化成功返回的4字节伪随机数
unsigned long lCardInvoiceNo,	//消费初始化返回2字节的脱机交易序号				
unsigned long lPurchMoney,		//需要消费的金额	
unsigned char *TerminalNo,      //终端号			
* Output      : void
unsigned char *sMac1
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 计算消费MAC1
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
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
				unsigned char *sKey,			//16字节的圈存主密钥
				unsigned char *sRandom,			//圈存初始化成功返回的4字节伪随机数
				unsigned long lCardInvoiceNo,	//圈存初始化成功返回的2字节的交易序号
				unsigned long lCardBal,			//圈存初始化成功返回的钱包交易前余额
				unsigned long lAddMoney,		//需要充值的金额
				unsigned char *TerminalNo,		//6字节的终端机编号
				unsigned cha  *sMac1			//圈存初始化成功返回的4字节MAC1
* Output      : void
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 校验圈存初始化时卡返回的MAC1，用于认证用户卡的合法性
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
* Input       : unsigned char *sAppNo,			//应用序列号后8字节
				unsigned char *sKey,			//16字节的圈存主密钥
				unsigned char *sRandom,			//圈存初始化成功返回的4字节伪随机数
				unsigned long lCardInvoiceNo,	//圈存初始化成功返回的2字节的交易序号			
				unsigned long lAddMoney,		//需要充值的金额
				unsigned char *TerminalNo,		//6字节的终端机编号
				unsigned char *sDate,			//4字节交易日期(YYYYMMDD)
				unsigned char *sTime			//3字节交易时间(HHMMSS)
* Output      : unsigned char *sMac2			//4字节的MAC2
* Return	  : 0=成功,其它值=失败(请参照PBOC错误码)
* Description : 计算圈存MAC2
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

//安全报文MAC
unsigned char* CalSecure_MAC(
							 unsigned char *key,
							 unsigned char *random, 
							 int len,
							 unsigned char *input_data,
							 unsigned char *out_data);


//*---------------------------------------------------------------------------
//*名称: CComSmart
//*功能: 串口通讯类
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
