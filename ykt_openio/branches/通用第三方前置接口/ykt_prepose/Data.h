// Data.h: interface for the CData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__5E41CAB0_5E9F_11D7_BD21_0000E8345FDC__INCLUDED_)
#define AFX_DATA_H__5E41CAB0_5E9F_11D7_BD21_0000E8345FDC__INCLUDED_



#define	STX1	0xC0
#define	ETX1	0xC1
#define	STX2	0xC2
#define	ETX2	0xC3

class CData  
{
public:
	byte	m_clock[20];
public:
	int PackData(int Addr,int Port,unsigned char *Buffer,int Len);
	int BuildData(unsigned char MacNum,int Flag,unsigned char *commision,unsigned char CommByte,int InDataLen,unsigned char * InData,unsigned char *OutData,int Level,unsigned char *Level_Array);
	void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);
	void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
	int CRC_CCITT(unsigned char len,unsigned char *in,BYTE* out);
	CData();
	bool GetDataBasePara( char* ServiceName,char* UserID,char* Pwd,char* DataBaseName);
	char *SetIPAddrToID( char * cAddrIP);
	BYTE* AscToBcd(BYTE* ascbuf, int ascbuf_len, BYTE* bcdbuf);
	BYTE* BcdToAsc(BYTE* bcdbuf, int bcdbuf_len,BYTE* ascbuf );
	char* IntToHex(int data,char* buf);
	char* ltrim(char* str);
	char* rtrim(char* str);
	char* trim(char* str);
	char* HeadAddStr(char* str, int num, char type);
	BOOL CheckStrHex(char* str );
	int  HexToInt(unsigned char* HexData,  int len);
	BYTE* GetSysTime();
	BYTE* GetSysTimeHex();
	int   GetSysWeek();
	char* GetCurPath();
	bool FileIsExist(char* pszFileName);
	bool SetCardKind( byte *nCardKind,int nCardNo );
	void SmartEncrypt(BYTE E_number,BYTE* ID, BYTE* Plain)
	{
		Plain[0] = (Plain[0] ^ (ID[0] + E_number))  +1;
		Plain[1] = (Plain[1] ^ (ID[1] + E_number))  +2;
		Plain[2] = (Plain[2] ^ (ID[2] + E_number))  +3;
		Plain[3] = (Plain[3] ^ (ID[3] + E_number))  +4;
		Plain[4] = (Plain[4] ^ (~ID[0] + E_number)) +5;
		Plain[5] = (Plain[5] ^ (~ID[1] + E_number)) +6;
		Plain[6] = (Plain[6] ^ (~ID[2] + E_number)) +7;
		Plain[7] = (Plain[7] ^ (~ID[3] + E_number)) +8;
		Plain[8] = (Plain[8] ^ (ID[0] + ID[1] + ID[2] + ID[3] + E_number)) +9;
		return;
	}
	int GetWeek();
	char* GetColValues( char* InData);
	virtual ~CData();
};
#endif 
