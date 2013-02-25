extern "C" 
{
typedef struct TypeStructISO7816
{
    unsigned char cla;
	unsigned char ins;
	unsigned char p1;
	unsigned char p2;
	unsigned char lc;
	unsigned char le;
    unsigned char sw1;
    unsigned char sw2;
	unsigned char datainbuff[300];
	unsigned char dataoutbuff[300];
	unsigned char rece_length;
} StructISO7816;


typedef struct TypeStructCPUPBOC
{
    unsigned char moneyid;
	unsigned char psamid;
	char psamno[13];
	char uid[21];
	char cardid[21];
	long purchasemoney;
	char purchasetime[15];
	unsigned long balance;
	unsigned int purchasetimes;
	unsigned char keyno;
    unsigned char algorithmmark;
	char cardrandomdata[9];
	unsigned long eepid;
	char psamrecordno[7];
	char mac1[9];
	char mac2[9];
	char tac[9];

} StructCPUPBOC;


/****************************************************************************************
功能：	打开读卡器
输入：  "COM1","COM2","COM3","COM4","COM5"代表要打开的端口
返回:	小于0为打开端口失败;
   	    大于0为成功的打开的端口描述符,用于读写卡操作函数的句柄
****************************************************************************************/
HANDLE  _stdcall Open_Reader(char* cPort);


/****************************************************************************************
功能：	关闭读卡器
输入：  先前打开的串口句柄
****************************************************************************************/
unsigned int  _stdcall 	Close_Reader(HANDLE hPort);



unsigned int _stdcall BELL_BEEP(HANDLE icdev, int beep_time);
unsigned int _stdcall LED_DISPLAY(HANDLE icdev, char *disp_data,int disp_time);


unsigned int _stdcall GET_HARDWARE_VER(HANDLE icdev, char *H_ver,char *cErrMsg);
unsigned int _stdcall GET_SOFTWARE_VER(HANDLE icdev, char *S_ver,char *cErrMsg);


unsigned int _stdcall REQ_14443_CARD(HANDLE icdev, unsigned char mode ,char *tag_type,char *uid,char *cErrMsg);
unsigned int _stdcall ATS_14443_CARD(HANDLE icdev,char *ats,char *cErrMsg);
unsigned int _stdcall MIFS_AUTH(HANDLE icdev,unsigned char sector,unsigned char keymode, char *sectorkey,char *cErrMsg);
unsigned int _stdcall MIFS_READ(HANDLE icdev,unsigned char sector,unsigned char block, char *blockdata,char *cErrMsg);
unsigned int _stdcall MIFS_WRITE(HANDLE icdev,unsigned char sector,unsigned char block, char *blockdata,char *cErrMsg);
unsigned int _stdcall MIFS_HALT(HANDLE icdev,char *cErrMsg);
unsigned int _stdcall CPUCARD_APDU(HANDLE icdev,char *datain,char *dataout,char *cErrMsg);



unsigned int _stdcall SAMCAR1_POWER_ON(HANDLE icdev,char *ATR,char *cErrMsg);
unsigned int _stdcall SAMCAR1_POWER_OFF(HANDLE icdev,char *cErrMsg);
unsigned int _stdcall SAMCAR1_APDU(HANDLE icdev,char *datain,char *dataout,char *cErrMsg);


unsigned int _stdcall SAMCAR2_POWER_ON(HANDLE icdev,char *ATR,char *cErrMsg);
unsigned int _stdcall SAMCAR2_POWER_OFF(HANDLE icdev,char *cErrMsg);
unsigned int _stdcall SAMCAR2_APDU(HANDLE icdev,char *datain,char *dataout,char *cErrMsg);


unsigned int _stdcall REQ_RFSIM_CARD(HANDLE icdev,unsigned char mode,char *uid,char *cErrMsg);
unsigned int _stdcall RFSIM_HALT(HANDLE icdev,char *cErrMsg);
unsigned int _stdcall RFSIMCARD_APDU(HANDLE icdev,char *datain,char *dataout,char *cErrMsg);


}

