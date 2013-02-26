/********************************************************************
	created:	2003/10/21
	created:	21:10:2003   11:08
	filename: 	E:\linux\ksappsvr\comstru.h
	file path:	E:\linux\ksappsvr
	file base:	comstru
	file ext:	h
	author:		CHENYH
	
	purpose:	����ǰ̨��Ӧ�ÿ�ܺ�ҵ����֮����ص�һЩ���ݽṹ����
*********************************************************************/

#ifndef _COMSTRUCT_
#define _COMSTRUCT_

//#define BU_VERSION  20040322      // ��һ���汾����
#define BU_VERSION 20050909         // ֧�ֹ����ڴ�汾
#define MAXBUGRPID 12               // BU���ID���ȣ�1
#define INTSOURCENO 0xFFFE          // �����PushData/ExtCall�ȱ�ʾ����RA���ͻ����, ������ȷ����������ơ�

#ifndef EXITMSGTYPE
   #define EXITMSGTYPE      999         /* ϵͳ�˳�����Ϣ���� */
   #define JOBSTATUSMSGTYPE 998
   #define WRITEAPPINFO     997   /* qbin 20031229 д�������ܺ���Ϣ�����ݿ���*/
   #define WAKEUPMSGTYPE    990         
#endif

/* ****** Updated by CHENYH at 2006-7-14 16:11:09 ****** 
��AIX��VAC�±��룬���������ģ�����BCC�ܹ�����Ҳû������
#ifndef IPC_NOWAIT
#define IPC_NOWAIT 1
#endif
#ifndef IPC_WAIT
#define IPC_WAIT   0
#endif
#ifndef MSG_W
#define MSG_W 0000200
#endif
#ifndef MSG_R
#define MSG_R 0000400
#endif
*******************************************************/

#define MSGHEADLEN 50

#ifndef MAXMSG
//#define MAXMSG 8192  // ���֤ȯ���н��׵ģ�
#define MAXMSG 8192  // ��֤ȯ���н���ͳһ������Ϊ8192 2003-10-21 by greenyard
#endif

#define MAXROW      100


#define MAXROUTERCOUNT  6  /*·�ɼ���*/
//#define MAXDATASIZE 8192
#define MAXDATASIZE 8192  // ��֤ȯ���н���ͳһ������Ϊ8192 2003-10-21 by greenyard


#define SHM_EXITCODE 20031015   




#ifdef __cplusplus
extern "C" {
#endif


/* ���´����������ֽڶ���ʹ�õ� */
   /* ���´����������ֽڶ���ʹ�õ� */
   #ifdef WIN32
      #define __PACKED__ 
      #pragma pack(push,1)
   #else
      #ifdef __GNUC__
         #define __PACKED__	__attribute__ ((packed))
         //#pragma pack(push,1)
      #else
         #ifdef HP_UX
            #define __PACKED__
            #pragma pack 1
         #else
            #define __PACKED__
            #pragma options align=packed
         #endif
      #endif
   #endif

#define LMSGID 0x0128   // ������ͨѶЭ��ʶ����
#define RMSGID 0x2801   // �����ͨѶЭ��ʶ����

typedef struct
{
   short msgid;  // 0x0128 - ��Ϊ����ϵͳ�Խӵ�ר��Э���ʶ�룬ͬʱ����ʶ��Է��������Ƿ�ͱ�����ͬ
   short msgtype;  
   unsigned short len;  // ����Ϣ�������ݰ����ȣ��������������ݳ���
} __PACKED__ MSGHEAD;

typedef struct 
{
   MSGHEAD head;
   char data[1];
} __PACKED__ MSGBUF;




/* ****** Updated by CHENYH at 2003-9-26 11:22:18 ****** 
   Ϊ���¾�ϵͳ�ļ��ݣ���Ҫ���½ṹ����Ϊ����������ݷ��͵����ݣ�������ԭ����APPHANDLE
*/
/*������ ��������:2000.6.12 */
typedef struct _SYS_HEAD   /*�������ݰ�ͷ Ver=2 */
{
	unsigned char     Ver;	/*�������ݰ��汾��,��1��ʼ,4.0�汾��Ϊ1*/
							/*5.0ϵͳ�汾��Ϊ2 */ 
	unsigned char     MessageType;   	/*��Ϣ���ͣ�����ϵͳ��Ӧ����Ϣ */
							/*Ӧ�ù���ע��	1 */
							/*Ӧ�ù���ע�� 	2 */
							/*��ѯ����״̬ 	3 */
							/*��ѯ������־	4 */
							/*�û���������Ŀ������ 	5 */
							/*�û�����Ŀ�����ؽ�� 	6 */
							/*����Ự��Կ 7	 ����Public Key */
							/*���ػỰ��Կ 8	Session Key ��Public Key���ܺ������ */
							/*���ĻỰ��Կ 9 �µĻỰ��Կ�ļ������ϴλỰ��Կ */
							/*10 */
							/*11 */
	unsigned char     CompressFlag;	/*ѹ����ǣ���������USER_BLOCK */
							/*0-  ����û��ѹ�� */
							/*1-  ����ѹ��	   */
	unsigned char     RouterIndex;	/*���ݰ�����·�ɵ���ţ����͵����ݰ�ÿ����һ��*/
							/*·�ɾͼ�һ�����ص����ݰ�ÿ����һ��·�ɾͼ�һ��*/
							/*·����ྭ��6����������Ϊ�Ѱ����� */
	unsigned char	   RouterDesignate;/*·��ָ����� */
							/*0�ǲ�ָ���������ܺ����� */
							/*1ָ�����ܣ����ϴ�����·������Ŀ�ĵ� */
	unsigned char	   FunctionPriority;/*���ܺ����ȼ�,0Ϊȱʡ����0Ϊ�û��Զ��� */
							/*1Ϊ���ȼ����ڱ�׼ */
							/*2Ϊ��׼���ȼ�		*/
							/*3Ϊ���ȼ����ڱ�׼	*/
	unsigned short 	Function; 	    /*�����ܺţ�Ӧ����·��ֻע�������ܺ� */
							/*�ӹ��ܺ���Ӧ�ø������	*/
							/*�罻����Ϊ1��ʵʱ��ѯΪ2����ѯ��ʷΪ3 */
/*	unsigned short    SourceNo; */
	unsigned short    DestNo;/*Ŀ�����ر�ţ�Ӫҵ�����룩 */
	unsigned short    UserDataSize;   /*���ݱ�ͷ���ŵ�Ӧ������USER_BLOCK���� */
	unsigned short    UserDataRealSize;/*Ӧ�����ݵ���ʵ���ȣ����ݼӽ��ܻ�ѹ��ǰ�ĳ��� */
	unsigned short 	RouterIn[MAXROUTERCOUNT];	/*·����Ϣ����·�� */
	unsigned short    RouterOut[MAXROUTERCOUNT];  /*·����Ϣ���·�� */
	int	 			   LastConnectTime;/*ʱ����,��Ч���ݰ���ʱ��Ӧ�ñ�CONNECT��ʱ��� */
							/*�ͻ�CONNECTʱ����,��λΪ*/
	unsigned int      CRC;           /*���ݰ�ͷSYS_HEAD��32λcrcֵ */
} __PACKED__ SYS_HEAD;


typedef struct _RECEIVEDATA/*���ա��������ݽṹ*/
{
	unsigned short len;              // ʵ�ʵ�buf����
	unsigned short SourceNo;         // ͨѶƽ̨�ı��
	SYS_HEAD syshead;                // ͨѶƽ̨ʹ�õ������շ����ݣ�ҵ�����ֲ�Ҫ�����ڲ����ݣ�ֻҪ���Ƽ���
	unsigned char buf[MAXDATASIZE];  // ʵ����ǰ̨�շ������ݣ�����ΪST_CPACK���������
} __PACKED__ RECEIVEDATA,*LPRECEIVEDATA;

/////////////////////////////////////////////////////////////////////////
// MT_LINKBEGIN:
#ifdef WIN32
typedef DWORD PROCID;
#else
typedef pid_t PROCID;
#endif

#define MT_LINKBEGIN    0x0032      // ҵ��Ԫ��������ķ���������ӵ���������
typedef struct
{
   short bu1;        // ҵ��Ԫ�˵�(short)1
   char  szBUGroupID[12];  // ��ҵ����Ԫ���
   char  iDefaultAM;       // ��ҵ��Ԫ��ȱʡӦ��ģʽ��ÿ��ҵ����֮ǰ��ϵͳ�Զ��ָ�����ģʽ
   int   iBUVersion;       // BU���ĵİ汾�ţ�������BCC���ӵ�ʱ����BCC֪���ð汾�Ĵ���ģʽ
} __PACKED__ RP_LINKBEGIN_OLD; // ����BU��BCC������������ݰ�


typedef struct
{
   short bu1;        // ҵ��Ԫ�˵�(short)1
   char  szBUGroupID[12];  // ��ҵ����Ԫ���
   char  iDefaultAM;       // ��ҵ��Ԫ��ȱʡӦ��ģʽ��ÿ��ҵ����֮ǰ��ϵͳ�Զ��ָ�����ģʽ
   int   iBUVersion;       // BU���ĵİ汾�ţ�������BCC���ӵ�ʱ����BCC֪���ð汾�Ĵ���ģʽ
   PROCID dwProcID;        // BU��process id��  2005-9-1 19:42:37 ��ע���������
   char  bUseMQ;           // 2007-11-22 14:23:07 �Ƿ�ʹ��MsgQueue
} __PACKED__ RP_LINKBEGIN; // ҵ��Ԫ����ҵ��������Ķ˷��͵�����������������

typedef struct
{
   short bc1;  // ҵ��������Ķ˵�(short)1
   int   bu_number;  // ҵ��������Ķ˷����ҵ��Ԫ�ı��
   int   basefuncno; // ���ӵ�BCC��ͨѶ���ܺ�
   int   bccid;      // ��BCC�ı��ID
   char  szmsg[1];
} __PACKED__ AP_LINKBEGIN; // ҵ��������Ķ˸�ҵ��Ԫ�˵�����ȷ��Ӧ������

#define MT_GETREQ       0x1111      // ҵ��Ԫ��������ķ����ȡҵ�����������Ϣ
typedef struct
{
   unsigned char iGRFrame;
   unsigned int iLastReqType;      // �ϴδ��������  0 - ��ʾ�ſ�ʼ��>0��ʾ�����������
   unsigned int iLastRetCode;      // �ϴδ���Ľ���룬��ʾ�ɹ�ʧ��
} __PACKED__ RP_REQUEST;

// MT_GETREQ:
typedef struct
{
   unsigned char  iGRFrame;   // ��Է���MT_GETREQ�е��Ǹ�����֡��
   unsigned short SourceNo;
   SYS_HEAD syshead;
   unsigned short len;        // ������ŵ����ݰ�����
} __PACKED__ AP_REQUEST;

#define MT_SETCOL       0x1001
//unsigned char ParmBits[PARMBYTES];
#define MT_PUTROWDATA   0x1002
#define MT_ANSDATA      0x1003
typedef struct
{
   unsigned short SourceNo;
   SYS_HEAD syshead;
   unsigned char nextflag;
   unsigned int n_retcode;
   char szmsg[1];
} __PACKED__ RP_ANSDATA;

#define MT_ANSDATAEX    0x1004
typedef struct
{
   unsigned short SourceNo;
   SYS_HEAD syshead;
   //unsigned char encodebuf[MAXDATASIZE];
} __PACKED__ RP_ANSDATAEXH;


#define MT_PUSHDATA     0x1005
typedef struct 
{
   unsigned short SourceNo;         /* ��ʼ����ͨѶƽ̨�ı�� ���μ�TRUSERID::SourceNo��*/
   unsigned short DestNo;           /* ����Ŀ����ͨѶƽ̨��� */
   unsigned short FuncNo;           /* ����Ŀ���ע���ͨѶ���ܺ� */
   int            BatchNo;          /* ��Ŀ�������κ� */
} __PACKED__ TPUSHDESTN;

typedef struct
{
   char pushmode;  // ����ģʽ
   unsigned int acktime;   // ȷ�ϵȴ���ʱ��
   unsigned short dcount;   // ����Ŀ���ĸ���
} __PACKED__ RP_PUSHDATAH;

#define MT_PUTROW    0x1006  // Ϊ����ԭ���н���ϵͳ����
typedef struct
{
   unsigned short SourceNo;
   SYS_HEAD syshead;
   unsigned int n_retcode;
} __PACKED__ RP_PUTROW;

#define MT_DATADONE   0x1007   // �����������  �õ���RP_ANSDATA
typedef struct
{
   unsigned int iLastReqType;      // ��ɵ������ܺ�
   unsigned int n_retcode;
   char szmsg[1];   
} __PACKED__ RP_DATADONE; 

#define MT_CMDCANCEL  0x1008   // BCC->BU�����ֹͣ��ǰ����

#define MT_BCCLOG     0x1009   // BU->BCC: �ύ��BCCҪ���¼����־
   #define LT_MSG   'C'    // ������־
   #define LT_CPACK 'P'    // CPACK���������־
   #define LT_UDATA 'U'    // �û����ж���������־
typedef struct
{
   char logtype;   // ��LT_xxxx
   int logid;
   unsigned short textlen;
   char logtext[1];
} __PACKED__ RP_BCCLOG;

#define MT_SETAMODE  0x100A    // BU->BCC: ���õ�ǰAnswerMode

#define MT_SETMAXROWS 0x100B   // BU->BCC: ���õ�ǰ��������¼��

#define MT_SETERROR   0x100C   // BU->BCC: BU���ִ������ȫ���������⣬��Ὣ�����Ա������뷴����ǰ̨

#define MT_SETTIMEOUT 0x100D   // BU->BCC: ���Ʊ�ҵ����ÿ��Ӧ�����ݵĳ�ʱʱ�䣬������ƣ�

#define MT_RESETANSWER 0x100E  // BU->BCC: ȡ��ԭ������������Ӧ������

typedef struct
{
   unsigned int iErrorCode;
   char szmsg[1];
} __PACKED__ RP_SETERROR; 



/* ****** Updated by CHENYH at 2005-7-1 15:45:45 ****** 
����Ϊ�����ڴ�ģʽ�Ľӿڣ�
*******************************************************/
#define MT_SMOPEN    0x1020

#define SM_MAXNAMELEN   12

typedef struct 
{
   unsigned int length;
   char name[SM_MAXNAMELEN];
} __PACKED__ RP_SMOPEN;

#define MT_SMWRITE   0x1021
typedef struct 
{
   int handle;
   unsigned int offset;
   unsigned int length;
   unsigned char lock;
} __PACKED__ RP_SMWRITE;

#define MT_SMREAD    0x1022


#define MT_SMINTADD  0x1023
typedef struct 
{
   int handle;
   unsigned int offset;
   int increment;
} __PACKED__ RP_SMINTADD;
#define SMIA_ERR     0x80000000
#define SMIA_BADP    0x80000001

#define MT_SMLOCK   0x1024
#define MT_SMTRYLOCK   0x1025
#define MT_SMUNLOCK 0x1026
// �ͷ���ID�͹����������

#define MT_SETUSERID 0x1027 

// 2005-9-7 22:49:30
#define MT_REGFUNC   0x1100
typedef struct 
{
   unsigned int reqtype;
   char rtname[80];
   char programmer[20];
   int  priority;
   bool bStop;
} __PACKED__ RP_REGFUNC;


// 2005-9-9 11:40:33
#define MT_INTCALL 0x2000
typedef struct  
{
   unsigned int waittime;     // �ȴ�Ӧ��ʱ��
   char szBUGroupID[MAXBUGRPID];   // �����ʹ��BU���
} __PACKED__ RP_INTCALLH;

#define MT_INTTRANSFER 0x2001
typedef struct  
{
   char szBUGroupID[MAXBUGRPID];
} __PACKED__ RP_INTTRANSFER;

#define MT_EXTTRANSFER 0x2002
typedef struct
{
   //unsigned short SourceNo;
   unsigned short DestNo;
   unsigned short FuncNo;
} __PACKED__ RP_EXTTRANSFER;

/////////////////////////////////////////////////////////////////////////
#define MT_TESTLINK  0x20FF
#define MT_TESTLINKEX 0x40FF

   #ifdef WIN32
      #pragma pack(pop)
   #else
      #ifdef __GNUC__
      #else
         #ifdef HP_UX
            #pragma pack 0
         #else
            #pragma options align=reset
         #endif
      #endif
   #endif
   #undef __PACKED__

#ifdef __cplusplus
}
#endif



#endif

