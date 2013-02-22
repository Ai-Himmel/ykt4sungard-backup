

//---------------USB
#define PackDataLen     4102            //�����ݵ����
#define PackHeadLen     8               //��ͷ��С
#define USBPCMaxSize    4096            //USB��������У�������������
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

// -----------����ͨ�ŵĹ��ܺ���-------------
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
__declspec( dllexport ) int WINAPI MkDir(char *filepath,unsigned int iPort, long iBaud);         //����Ŀ¼            ����:�ļ������˿ڣ�������
__declspec( dllexport ) int WINAPI SetDir(char *filepath,unsigned int iPort, long iBaud);        //���û�����ǰ��Ŀ¼  ����:·�����˿ڣ�������
__declspec( dllexport ) int WINAPI SetHtTime(unsigned int iPort, long iBaud);//����HT�豸��ʱ��Ϊϵͳ��ǰʱ��,����0��ʾ���óɹ�

}
//���¹��ܱ��볭�������ļ�������
__declspec( dllexport ) long WINAPI CreateConnect(long iBaud,int iPort,int iSerialNo,int iDelay,int IsNew);
__declspec( dllexport ) void WINAPI DisConnect(long Handle);
__declspec( dllexport ) int  WINAPI ExFGet(char PCFile[], char HTFile[], unsigned int iPort, long iBaud, unsigned iSerialNo);//��װ�ļ� ����: �����ļ�  ,���ϵ����ļ� ,�˿� ,������ ,0
__declspec( dllexport ) int  WINAPI ExFPut(char PCFile[], char HTFile[], unsigned int iPort, long iBaud, unsigned iSerialNo);//�´��ļ� ����: �����ļ���֧��·����,���ϵ����ļ�,�˿� ,������ ,0
__declspec( dllexport ) long WINAPI wSetDateTime(char szDate[],char szTime[],unsigned int iPort,long iBaud);//����������ں�ʱ�� 
__declspec( dllexport ) long WINAPI wGetDateTime(char *szDate, char *szTime,unsigned int iPort,long iBaud); //ȡ�û��������ں�ʱ��  ���ڸ�ʽ: 20020312 ʱ���ʽ:13:12:02
__declspec( dllexport ) long WINAPI HTMessage(char *iserial,char *itpye,unsigned int iPort,long iBaud);     //ȡ�û����Ļ���ź�����  ���� 00002002��2800��
__declspec( dllexport ) long WINAPI GetHtFile(char *filebuff,unsigned int iPort,long iBaud);                //ȡ��HT ���ļ�����FILEBUFF �� ÿ���ļ��ĳ��Ȳ�����12�ֽڣ��������ļ�����Ŀ
__declspec( dllexport ) long WINAPI DelHtFile(char filename[],unsigned int iPort,long iBaud);               //ɾ���ļ�  FILE �ļ��� ��0 ���سɹ�
__declspec( dllexport ) long WINAPI GetHtSN(unsigned int iPort, long iBaud);                                //ȡ��������� ���������к�  iBaud ������ iPort�˿�
__declspec( dllexport ) long WINAPI ExitHTSevr(unsigned int iPort, long iBaud);                             //�˳��ļ�������
__declspec( dllexport ) long WINAPI HTTest(unsigned int iPort, long iBaud);                                 //�������Ƿ����,   ���ڷ���0
__declspec( dllexport ) void WINAPI GetDllInfo(char *ver,char *modidate);                                   //ȡ�ð汾���޸���ǰ �� "V1.0" ,"2003.12.01" 
__declspec( dllexport ) long WINAPI HT26XXFM(unsigned int iPort, long iBaud);                               //��ʽ��26ϵ�У�������0 ��ʾ������������ȥ







//------USBͨ�ŵĹ��ܺ���-----------------
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
__declspec( dllexport )  int WINAPI Usb_MkDir(unsigned int Port,char *Filename );              //����Ŀ¼            ����:���豸��ַ(Ĭ��Ϊ0)���ļ���
__declspec( dllexport )  int WINAPI Usb_SetDir(unsigned int Port,char *Filename );             //���û�����ǰ��Ŀ¼  ����:  �豸��ַ(Ĭ��Ϊ0)��·��
}
//���¹��ܱ��볭�������ļ�������
__declspec( dllexport ) long WINAPI Usb_CreateConnect(unsigned long mIndex,int iSerialNo);
__declspec( dllexport ) void WINAPI Usb_DisConnect(unsigned long mIndex);
__declspec( dllexport ) int  WINAPI Usb_ExFGet(char PCFile[], char HTFile[], unsigned iSerialNo);//��װ�ļ� ����: �����ļ�, ���ϵ����ļ�, 0
__declspec( dllexport ) int  WINAPI Usb_ExFPut(char PCFile[], char HTFile[], unsigned iSerialNo);//�´��ļ� ����: �����ļ���֧��·����,���ϵ����ļ� ,0
__declspec( dllexport ) long WINAPI Usb_wSetDateTime(char szDate[],char szTime[] ,unsigned long mIndex,unsigned TxSerialNo);//����������ں�ʱ�� 
__declspec( dllexport ) long WINAPI Usb_wGetDateTime(char *szDate, char *szTime,unsigned long mIndex, unsigned TxSerialNo ); //ȡ�û��������ں�ʱ��  ���ڸ�ʽ: 20020312 ʱ���ʽ:13:12:02
__declspec( dllexport ) long WINAPI Usb_HTMessage(char *iserial,char *itpye ,unsigned long mIndex);   //ȡ�û����Ļ���ź�����  ���� 00002002��2800��
__declspec( dllexport ) long WINAPI Usb_GetHtFile(char *filebuff,unsigned long mIndex);               //ȡ��HT ���ļ�����FILEBUFF �� ÿ���ļ��ĳ��Ȳ�����12�ֽڣ��������ļ�����Ŀ
__declspec( dllexport ) long WINAPI Usb_DelHtFile(char filename[],unsigned long mIndex);              //ɾ���ļ�  FILE �ļ��� ��0 ���سɹ�
__declspec( dllexport )  long WINAPI Usb_GetHtSN(unsigned long mIndex);                               //ȡ��������� ���������к� 
__declspec( dllexport ) long WINAPI Usb_ExitHTSevr(unsigned long mIndex);                            //�˳��ļ�������
__declspec( dllexport )  long WINAPI Usb_HTTest(unsigned long mIndex);                                 //�������Ƿ����,   ���ڷ���0                                 //ȡ�ð汾���޸���ǰ �� "V1.0" ,"2003.12.01" 
__declspec( dllexport )  long WINAPI Usb_HT26XXFM(unsigned long mIndex);                             //��ʽ��26ϵ�У�������0 ��ʾ������������ȥ

/*��������־
"ͨѶ��ʱ.",    		   //-1
"��·����.",               //-2
"���ݰ�����.",             //-3
"ͨѶ��δ��.",           //-4
"ͨ������ʧ��.",             //-5
"ͨѶ��ȡ��.",             //-6
"�ⲿ�ļ�����ƥ��.",       //-7
"�ⲿ�ļ�δ��.",         //-8
"�ⲿ�ļ����ض�.",         //-9
"�ⲿ�ļ��Ѿ�����.",     //-10
"�Ƿ��ļ���.",             //-11
"��ͨѶ�ڴ���.", 		   //-12
"����.",	 			   //-13
"���ļ�����.", 			   //-14
"д�ļ�����.",			   //-15
"������Դ�ļ���."          //-16
"�������ڴ���",			   //-17	
"����ʱ�����",                        //-18
"",                        //-19
"",                        //-20 
"��ͨѶ��״̬����."        //-21
"��ͨѶ��xxxxxxxx."        //-22
*/
