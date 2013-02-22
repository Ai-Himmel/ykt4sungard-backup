

//---------------USB
#define PackDataLen     4102            //包数据的最大
#define PackHeadLen     8               //包头大小
#define USBPCMaxSize    4096            //USB传输过程中，最大传输的数据量
//-------------------------

#define _MaxPackLen    	600
#define ID_TIMER    		101

#define CRC_PATTERN  0x1021

#define _WriteReq       1
#define _ReadReq        2
#define _ListReq        3
#define _DeleReq        4
#define _SnoReq         5
#define _FreeReq        6
#define _SetDir         7
#define _ReadDir        8
#define _MkDir          9
#define _ListDir        10
#define _SetTime        11
#define _ReadInfo       12
#define _ReadLogo       13
#define _ExitHTSevr     14
#define _Ht26xxFm       15


#define _4Read        	0
#define _4Write        	1
#define _4Update        2  
#define _ROMINDEXMAX    1969

#define ACCEPT_ID       'a'
#define REJECT_ID       'r'
#define EXF_RDY_ID      'R'
#define EXF_HOF_ID      'H'
#define EXF_DOF_ID      'D'
#define EXF_ACK_ID      'A'
#define EXF_NAK_ID      'N'
#define EXF_PAU_ID      'P'
#define EXF_WAIT_ID     'W'
#define EXF_BYE_ID      'B'
#define EXF_CAN_ID      'C'

#define MAX_WRITE_BUFFER        1024
#define MAX_READ_BUFFER         1024

#define  Ver "V2.01"
#define  Modidate "2007.01.22"

typedef struct
{
char 	        FileName[8];
char 	        FileType[3];
unsigned char	FileAttr;
unsigned long 	FileTime;
unsigned long	FileDate;
unsigned long 	FileSize;
unsigned long   ValidSerialNo;
} HOFBuff;

typedef struct
{
unsigned int    TxMark;
unsigned int  	TxSNo;
char 		    TxType;
char 		    TxID;
unsigned int  	TxLength;
char 		    TxDataPtr[_MaxPackLen];
unsigned int  	TxCRC;
} TxHdBuffer;


typedef struct
{
unsigned int    AckMark;
unsigned int   	AckSNo;
unsigned char  	AckType;
unsigned char  	AckID;
unsigned int   	AckLength;
unsigned int   	AckCRC;
} TxHd;

void Inithtcomm(HINSTANCE hld);

// -----------串口通信的功能函数-------------
extern  "C" {
__declspec( dllexport ) int WINAPI   OpenCommPort(char cComPort);
__declspec( dllexport ) int WINAPI   CloseCommPort(void);
__declspec( dllexport ) int WINAPI   SetComMode(long BaudRate,char ByteSize,	char Parity, char StopBits);
__declspec( dllexport ) int WINAPI   PutPack(char * TxData, unsigned int TxLen,	unsigned int TxCount);
__declspec( dllexport ) int WINAPI   GetPack(char * RxData);
__declspec( dllexport ) long  WINAPI SendClientReq(int ReqType ,char * ExFileName);
__declspec( dllexport ) int WINAPI   OpenExFile(int OpenType ,char * HOF);
__declspec( dllexport ) int WINAPI   ReadExFile(char * RxBuff);
__declspec( dllexport ) int WINAPI   CloseExFile(int CloseType);
__declspec( dllexport ) int WINAPI   WriteExFile(char * RxBuff, int iRLen);
__declspec( dllexport ) void WINAPI  ErrorString(int iErrCode, char * cErrMsg);
__declspec( dllexport ) int WINAPI   GetRetry(void);
__declspec( dllexport ) int WINAPI MkDir(char *filepath,unsigned int iPort, long iBaud);         //创建目录            参数:文件名，端口，波特率
__declspec( dllexport ) int WINAPI SetDir(char *filepath,unsigned int iPort, long iBaud);        //设置机器当前的目录  参数:路径，端口，波特率
__declspec( dllexport ) int WINAPI SetHtTime(unsigned int iPort, long iBaud);//设置HT设备的时间为系统当前时间,返回0表示设置成功

}
//以下功能必须抄表器在文件服务上
__declspec( dllexport ) long WINAPI CreateConnect(long iBaud,int iPort,int iSerialNo,int iDelay,int IsNew);
__declspec( dllexport ) void WINAPI DisConnect(long Handle);
__declspec( dllexport ) int  WINAPI ExFGet(char PCFile[], char HTFile[], unsigned int iPort, long iBaud, unsigned iSerialNo);//上装文件 参数: 电脑文件  ,掌上电脑文件 ,端口 ,波特率 ,0
__declspec( dllexport ) int  WINAPI ExFPut(char PCFile[], char HTFile[], unsigned int iPort, long iBaud, unsigned iSerialNo);//下传文件 参数: 电脑文件（支持路径）,掌上电脑文件,端口 ,波特率 ,0
__declspec( dllexport ) long WINAPI wSetDateTime(char szDate[],char szTime[],unsigned int iPort,long iBaud);//设机器的日期和时间 
__declspec( dllexport ) long WINAPI wGetDateTime(char *szDate, char *szTime,unsigned int iPort,long iBaud); //取得机器的日期和时间  日期格式: 20020312 时间格式:13:12:02
__declspec( dllexport ) long WINAPI HTMessage(char *iserial,char *itpye,unsigned int iPort,long iBaud);     //取得机器的机身号和类型  例如 00002002，2800，
__declspec( dllexport ) long WINAPI GetHtFile(char *filebuff,unsigned int iPort,long iBaud);                //取得HT 的文件放在FILEBUFF 中 每个文件的长度不超过12字节，返回是文件的数目
__declspec( dllexport ) long WINAPI DelHtFile(char filename[],unsigned int iPort,long iBaud);               //删除文件  FILE 文件名 ，0 返回成功
__declspec( dllexport ) long WINAPI GetHtSN(unsigned int iPort, long iBaud);                                //取机器的序号 返回是序列号  iBaud 波特率 iPort端口
__declspec( dllexport ) long WINAPI ExitHTSevr(unsigned int iPort, long iBaud);                             //退出文件服务器
__declspec( dllexport ) long WINAPI HTTest(unsigned int iPort, long iBaud);                                 //检查机器是否存在,   存在返回0
__declspec( dllexport ) void WINAPI GetDllInfo(char *ver,char *modidate);                                   //取得版本和修改日前 如 "V1.0" ,"2003.12.01" 
__declspec( dllexport ) long WINAPI HT26XXFM(unsigned int iPort, long iBaud);                               //格式化26系列，返回是0 表示命令正常发出去







//------USB通信的功能函数-----------------
extern  "C" {	
__declspec( dllexport ) int WINAPI   OpenUSB(unsigned long mIndex);
__declspec( dllexport ) void WINAPI   CloseUSB(unsigned long mIndex);
__declspec( dllexport ) int WINAPI   Usb_PutPack(char * TxData, unsigned int TxLen,	unsigned int TxCount);
__declspec( dllexport ) int WINAPI   Usb_GetPack(char * RxData);
__declspec( dllexport ) long  WINAPI Usb_SendClientReq(int ReqType ,char * ExFileName);
__declspec( dllexport ) int WINAPI   Usb_OpenExFile(int OpenType ,char * HOF);
__declspec( dllexport ) int WINAPI   Usb_ReadExFile(char * RxBuff);
__declspec( dllexport ) int WINAPI   Usb_CloseExFile(int CloseType);
__declspec( dllexport ) int WINAPI   Usb_WriteExFile(char * RxBuff, int iRLen);
__declspec( dllexport )  int WINAPI Usb_MkDir(unsigned int Port,char *Filename );              //创建目录            参数:，设备地址(默认为0)，文件名
__declspec( dllexport )  int WINAPI Usb_SetDir(unsigned int Port,char *Filename );             //设置机器当前的目录  参数:  设备地址(默认为0)，路径
}
//以下功能必须抄表器在文件服务上
__declspec( dllexport ) long WINAPI Usb_CreateConnect(unsigned long mIndex,int iSerialNo);
__declspec( dllexport ) void WINAPI Usb_DisConnect(unsigned long mIndex);
__declspec( dllexport ) int  WINAPI Usb_ExFGet(char PCFile[], char HTFile[], unsigned iSerialNo);//上装文件 参数: 电脑文件, 掌上电脑文件, 0
__declspec( dllexport ) int  WINAPI Usb_ExFPut(char PCFile[], char HTFile[], unsigned iSerialNo);//下传文件 参数: 电脑文件（支持路径）,掌上电脑文件 ,0
__declspec( dllexport ) long WINAPI Usb_wSetDateTime(char szDate[],char szTime[] ,unsigned long mIndex,unsigned TxSerialNo);//设机器的日期和时间 
__declspec( dllexport ) long WINAPI Usb_wGetDateTime(char *szDate, char *szTime,unsigned long mIndex, unsigned TxSerialNo ); //取得机器的日期和时间  日期格式: 20020312 时间格式:13:12:02
__declspec( dllexport ) long WINAPI Usb_HTMessage(char *iserial,char *itpye ,unsigned long mIndex);   //取得机器的机身号和类型  例如 00002002，2800，
__declspec( dllexport ) long WINAPI Usb_GetHtFile(char *filebuff,unsigned long mIndex);               //取得HT 的文件放在FILEBUFF 中 每个文件的长度不超过12字节，返回是文件的数目
__declspec( dllexport ) long WINAPI Usb_DelHtFile(char filename[],unsigned long mIndex);              //删除文件  FILE 文件名 ，0 返回成功
__declspec( dllexport )  long WINAPI Usb_GetHtSN(unsigned long mIndex);                               //取机器的序号 返回是序列号 
__declspec( dllexport ) long WINAPI Usb_ExitHTSevr(unsigned long mIndex);                            //退出文件服务器
__declspec( dllexport )  long WINAPI Usb_HTTest(unsigned long mIndex);                                 //检查机器是否存在,   存在返回0                                 //取得版本和修改日前 如 "V1.0" ,"2003.12.01" 
__declspec( dllexport )  long WINAPI Usb_HT26XXFM(unsigned long mIndex);                             //格式化26系列，返回是0 表示命令正常发出去

/*错误代码标志
"通讯超时.",    		   //-1
"链路错误.",               //-2
"数据包过长.",             //-3
"通讯口未打开.",           //-4
"通信连接失败.",             //-5
"通讯被取消.",             //-6
"外部文件名不匹配.",       //-7
"外部文件未打开.",         //-8
"外部文件被截断.",         //-9
"外部文件已经被打开.",     //-10
"非法文件名.",             //-11
"打开通讯口错误.", 		   //-12
"错误.",	 			   //-13
"读文件错误.", 			   //-14
"写文件错误.",			   //-15
"请输入源文件名."          //-16
"设置日期错误",			   //-17	
"设置时间错误",                        //-18
"",                        //-19
"",                        //-20 
"读通讯口状态错误."        //-21
"读通讯口xxxxxxxx."        //-22
*/
