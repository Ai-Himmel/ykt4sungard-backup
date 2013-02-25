/********************************************************************
	created:	2003/10/21
	created:	21:10:2003   11:08
	filename: 	E:\linux\ksappsvr\comstru.h
	file path:	E:\linux\ksappsvr
	file base:	comstru
	file ext:	h
	author:		CHENYH

	purpose:	用于前台、应用框架和业务处理之间相关的一些数据结构定义
*********************************************************************/

#ifndef _COMSTRUCT_
#define _COMSTRUCT_

//#define BU_VERSION  20040322      // 第一个版本编码
#define BU_VERSION 20050909         // 支持共享内存版本
#define MAXBUGRPID 12               // BU组的ID长度＋1
#define INTSOURCENO 0xFFFE          // 如果在PushData/ExtCall等表示采用RA推送或调用, 而非明确的外调或外推。

#ifndef EXITMSGTYPE
#define EXITMSGTYPE      999         /* 系统退出的消息类型 */
#define JOBSTATUSMSGTYPE 998
#define WRITEAPPINFO     997   /* qbin 20031229 写入主功能号信息到数据库中*/
#define WAKEUPMSGTYPE    990
#endif

/* ****** Updated by CHENYH at 2006-7-14 16:11:09 ******
在AIX的VAC下编译，会出现问题的，并且BCC架构下再也没有用了
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
//#define MAXMSG 8192  // 针对证券集中交易的；
#define MAXMSG 8192  // 和证券集中交易统一，定义为8192 2003-10-21 by greenyard
#endif

#define MAXROW      100


#define MAXROUTERCOUNT  6  /*路由级数*/
//#define MAXDATASIZE 8192
#define MAXDATASIZE 8192  // 和证券集中交易统一，定义为8192 2003-10-21 by greenyard


#define SHM_EXITCODE 20031015




#ifdef __cplusplus
extern "C" {
#endif


    /* 以下代码是用来字节对齐使用的 */
    /* 以下代码是用来字节对齐使用的 */
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

#define LMSGID 0x0128   // 本机的通讯协议识别码
#define RMSGID 0x2801   // 反序的通讯协议识别码

    typedef struct {
        short msgid;  // 0x0128 - 作为两个系统对接的专用协议标识码，同时用于识别对方的字序是否和本机相同
        short msgtype;
        unsigned short len;  // 本消息后续数据包长度，不包括本段数据长度
    } __PACKED__ MSGHEAD;

    typedef struct {
        MSGHEAD head;
        char data[1];
    } __PACKED__ MSGBUF;




    /* ****** Updated by CHENYH at 2003-9-26 11:22:18 ******
       为了新旧系统的兼容，需要如下结构，作为存放请求数据发送的内容，类似于原来的APPHANDLE
    */
    /*潘卫东 更改日期:2000.6.12 */
    typedef struct _SYS_HEAD { /*网络数据包头 Ver=2 */
        unsigned char     Ver;	/*网络数据包版本号,从1开始,4.0版本号为1*/
        /*5.0系统版本号为2 */
        unsigned char     MessageType;   	/*消息类型，区分系统和应用消息 */
        /*应用功能注册	1 */
        /*应用功能注销 	2 */
        /*查询网关状态 	3 */
        /*查询网关日志	4 */
        /*用户请求连接目的网关 	5 */
        /*用户连接目的网关结果 	6 */
        /*申请会话密钥 7	 发送Public Key */
        /*返回会话密钥 8	Session Key 经Public Key加密后的密文 */
        /*更改会话密钥 9 新的会话密钥的加密用上次会话密钥 */
        /*10 */
        /*11 */
        unsigned char     CompressFlag;	/*压缩标记，数据内容USER_BLOCK */
        /*0-  数据没有压缩 */
        /*1-  数据压缩	   */
        unsigned char     RouterIndex;	/*数据包经过路由的序号，发送的数据包每经过一个*/
        /*路由就加一，返回的数据包每经过一个路由就减一。*/
        /*路由最多经过6级，超过作为费包处理 */
        unsigned char	   RouterDesignate;/*路由指定标记 */
        /*0是不指定，按功能号搜索 */
        /*1指定功能，按上次搜索路径到达目的地 */
        unsigned char	   FunctionPriority;/*功能号优先级,0为缺省，非0为用户自定义 */
        /*1为优先级高于标准 */
        /*2为标准优先级		*/
        /*3为优先级低于标准	*/
        unsigned short 	Function; 	    /*主功能号，应用向路由只注册主功能号 */
        /*子功能号由应用负责管理	*/
        /*如交易类为1，实时查询为2，查询历史为3 */
        /*	unsigned short    SourceNo; */
        unsigned short    DestNo;/*目的网关编号（营业部代码） */
        unsigned short    UserDataSize;   /*数据报头接着的应用数据USER_BLOCK长度 */
        unsigned short    UserDataRealSize;/*应用数据的真实长度，数据加解密或压缩前的长度 */
        unsigned short 	RouterIn[MAXROUTERCOUNT];	/*路由信息表入路径 */
        unsigned short    RouterOut[MAXROUTERCOUNT];  /*路由信息表出路径 */
        int	 			   LastConnectTime;/*时间标记,有效数据包的时间应该比CONNECT的时间大 */
        /*客户CONNECT时更新,单位为*/
        unsigned int      CRC;           /*数据包头SYS_HEAD的32位crc值 */
    } __PACKED__ SYS_HEAD;


    typedef struct _RECEIVEDATA { /*接收、发送数据结构*/
        unsigned short len;              // 实际的buf长度
        unsigned short SourceNo;         // 通讯平台的编号
        SYS_HEAD syshead;                // 通讯平台使用的用于收发数据，业务处理部分不要关心内部数据，只要复制即可
        unsigned char buf[MAXDATASIZE];  // 实际与前台收发的数据，常常为ST_CPACK打包的数据
    } __PACKED__ RECEIVEDATA,*LPRECEIVEDATA;

/////////////////////////////////////////////////////////////////////////
// MT_LINKBEGIN:
#ifdef WIN32
    typedef DWORD PROCID;
#else
    typedef pid_t PROCID;
#endif

#define MT_LINKBEGIN    0x0032      // 业务单元向调度中心发起初试连接的请求类型
    typedef struct {
        short bu1;        // 业务单元端的(short)1
        char  szBUGroupID[12];  // 本业务处理单元组别
        char  iDefaultAM;       // 本业务单元的缺省应答模式，每个业务处理之前，系统自动恢复到本模式
        int   iBUVersion;       // BU核心的版本号，用于与BCC连接的时候，让BCC知道该版本的处理模式
        PROCID dwProcID;        // BU的process id号  2005-9-1 19:42:37 但注意兼容问题
    } __PACKED__ RP_LINKBEGIN; // 业务单元端向业务调度中心端发送的连接启动请求数据

    typedef struct {
        short bc1;  // 业务调度中心端的(short)1
        int   bu_number;  // 业务调度中心端分配给业务单元的编号
        int   basefuncno; // 连接的BCC的通讯功能号
        int   bccid;      // 本BCC的编号ID
        char  szmsg[1];
    } __PACKED__ AP_LINKBEGIN; // 业务调度中心端给业务单元端的连接确认应答数据

#define MT_GETREQ       0x1111      // 业务单元向调度中心发起获取业务处理请求的消息
    typedef struct {
        unsigned char iGRFrame;
        unsigned int iLastReqType;      // 上次处理的请求  0 - 表示才开始，>0表示处理过该请求
        unsigned int iLastRetCode;      // 上次处理的结果码，表示成功失败
    } __PACKED__ RP_REQUEST;

// MT_GETREQ:
    typedef struct {
        unsigned char  iGRFrame;   // 针对发送MT_GETREQ中的那个请求帧号
        unsigned short SourceNo;
        SYS_HEAD syshead;
        unsigned short len;        // 后面跟着的数据包长度
    } __PACKED__ AP_REQUEST;

#define MT_SETCOL       0x1001
//unsigned char ParmBits[PARMBYTES];
#define MT_PUTROWDATA   0x1002
#define MT_ANSDATA      0x1003
    typedef struct {
        unsigned short SourceNo;
        SYS_HEAD syshead;
        unsigned char nextflag;
        unsigned int n_retcode;
        char szmsg[1];
    } __PACKED__ RP_ANSDATA;

#define MT_ANSDATAEX    0x1004
    typedef struct {
        unsigned short SourceNo;
        SYS_HEAD syshead;
        //unsigned char encodebuf[MAXDATASIZE];
    } __PACKED__ RP_ANSDATAEXH;


#define MT_PUSHDATA     0x1005
    typedef struct {
        unsigned short SourceNo;         /* 起始发送通讯平台的编号 （参见TRUSERID::SourceNo）*/
        unsigned short DestNo;           /* 推送目标点的通讯平台编号 */
        unsigned short FuncNo;           /* 推送目标点注册的通讯功能号 */
        int            BatchNo;          /* 该目标点的批次号 */
    } __PACKED__ TPUSHDESTN;

    typedef struct {
        char pushmode;  // 推送模式
        unsigned int acktime;   // 确认等待的时间
        unsigned short dcount;   // 推送目标点的个数
    } __PACKED__ RP_PUSHDATAH;

#define MT_PUTROW    0x1006  // 为了与原集中交易系统兼容
    typedef struct {
        unsigned short SourceNo;
        SYS_HEAD syshead;
        unsigned int n_retcode;
    } __PACKED__ RP_PUTROW;

#define MT_DATADONE   0x1007   // 处理结束命令  用的是RP_ANSDATA
    typedef struct {
        unsigned int iLastReqType;      // 完成的请求功能号
        unsigned int n_retcode;
        char szmsg[1];
    } __PACKED__ RP_DATADONE;

#define MT_CMDCANCEL  0x1008   // BCC->BU的命令，停止当前处理

#define MT_BCCLOG     0x1009   // BU->BCC: 提交给BCC要求记录的日志
#define LT_MSG   'C'    // 文字日志
#define LT_CPACK 'P'    // CPACK打包数据日志
#define LT_UDATA 'U'    // 用户自行定义数据日志
    typedef struct {
        char logtype;   // 见LT_xxxx
        int logid;
        unsigned short textlen;
        char logtext[1];
    } __PACKED__ RP_BCCLOG;

#define MT_SETAMODE  0x100A    // BU->BCC: 设置当前AnswerMode

#define MT_SETMAXROWS 0x100B   // BU->BCC: 设置当前返回最大记录数

#define MT_SETERROR   0x100C   // BU->BCC: BU出现错误，如果全部都有问题，则会将请求以本错误码反馈给前台

#define MT_SETTIMEOUT 0x100D   // BU->BCC: 控制本业务功能每个应答数据的超时时间，（毫秒计）

#define MT_RESETANSWER 0x100E  // BU->BCC: 取消原来发送上来的应答数据

    typedef struct {
        unsigned int iErrorCode;
        char szmsg[1];
    } __PACKED__ RP_SETERROR;



    /* ****** Updated by CHENYH at 2005-7-1 15:45:45 ******
    下面为共享内存模式的接口：
    *******************************************************/
#define MT_SMOPEN    0x1020

#define SM_MAXNAMELEN   12

    typedef struct {
        unsigned int length;
        char name[SM_MAXNAMELEN];
    } __PACKED__ RP_SMOPEN;

#define MT_SMWRITE   0x1021
    typedef struct {
        int handle;
        unsigned int offset;
        unsigned int length;
        unsigned char lock;
    } __PACKED__ RP_SMWRITE;

#define MT_SMREAD    0x1022


#define MT_SMINTADD  0x1023
    typedef struct {
        int handle;
        unsigned int offset;
        int increment;
    } __PACKED__ RP_SMINTADD;
#define SMIA_ERR     0x80000000
#define SMIA_BADP    0x80000001

#define MT_SMLOCK   0x1024
#define MT_SMTRYLOCK   0x1025
#define MT_SMUNLOCK 0x1026
// 就发送ID和共享块句柄即可

#define MT_SETUSERID 0x1027

// 2005-9-7 22:49:30
#define MT_REGFUNC   0x1100
    typedef struct {
        unsigned int reqtype;
        char rtname[80];
        char programmer[20];
        int  priority;
        bool bStop;
    } __PACKED__ RP_REGFUNC;


// 2005-9-9 11:40:33
#define MT_INTCALL 0x2000
    typedef struct {
        unsigned int waittime;     // 等待应答时间
        char szBUGroupID[MAXBUGRPID];   // 请求送达的BU组号
    } __PACKED__ RP_INTCALLH;

#define MT_INTTRANSFER 0x2001
    typedef struct {
        char szBUGroupID[MAXBUGRPID];
    } __PACKED__ RP_INTTRANSFER;

#define MT_EXTTRANSFER 0x2002
    typedef struct {
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

