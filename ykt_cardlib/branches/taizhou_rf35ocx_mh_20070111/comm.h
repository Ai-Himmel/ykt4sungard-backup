#ifndef _COMM_CARD
#define _COMM_CARD

#define	STX1	0xC0
#define	ETX1	0xC1
#define	STX2	0xC2
#define	ETX2	0xC3

extern HANDLE  hCommDev;
extern int ErrorCode;
extern BYTE Dll_RetData[500];
extern int Dll_CommByte;
extern int Dll_bps;
extern BYTE Dll_MacNo;
extern COMMTIMEOUTS CommTimeOuts;
extern int nAutoFlag;

extern bool Calc_crc16(int len,unsigned char *in,unsigned char *out);
extern int ExeCommand(unsigned char *Buffer,int Len);
extern int	SendData(unsigned char *PacketBuffer,int PacketLen);
extern int	ReceiveData(int lWaitTime,unsigned char *PacketBuffer);
extern int CommIntilialize(char* ComStr,int BaudRate);
extern void des_code(unsigned char *dkey,unsigned char *jmdata,unsigned char *result,unsigned char k);
extern void Cal_Key(unsigned char *SOURCEDATA,unsigned char *KEY);
extern void TriDes(unsigned char *dkey, unsigned char *jmdata, unsigned char *result, unsigned char k);
extern int  en_key(unsigned char* mtext,unsigned char* text);
int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);
int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);
#endif