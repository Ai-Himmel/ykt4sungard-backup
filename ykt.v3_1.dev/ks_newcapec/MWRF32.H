// Mwrf32.h : main header file for the MWRF32 DLL
//

#if !defined CMWRF32APP_H
#define CMWRF32APP_H

typedef void* HANDLE;

class CMwrf32App 
{
public:
	int rf_select(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
	int rf_HL_writehex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
	int rf_HL_write(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
	int rf_HL_readhex(HANDLE icdev, char _Mode, unsigned char _Adr, unsigned long _Snr, unsigned char *_Data, unsigned long *_NSnr);
	int rf_HL_read(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
	int set_host_check(unsigned char mode);
	int rf_comm_check(HANDLE icdev,unsigned char mode);
	int rf_authentication(int icdev,unsigned char _Mode,unsigned char _SecNr);
	int rf_get_status(HANDLE icdev,unsigned char *_Status);
	int rf_write_hex(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	int rf_write(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	int rf_read_hex(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	int rf_read(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	int rf_halt(HANDLE icdev);
	int rf_load_key_hex(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey);
	int rf_load_key(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
	int rf_request(HANDLE icdev,unsigned char _Mode,unsigned int *TagType);
	int rf_card(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
	void rf_exit(HANDLE icdev);
	HANDLE rf_init(int port,long baud);
	int rf_beep(HANDLE icdev,unsigned int _Msec);
	int GetDevVersion(unsigned char *Ver);
};

#endif