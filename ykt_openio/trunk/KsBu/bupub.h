/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2004-2-7 15:36:16
  版本: V1.00 
  说明: 与各个sqc程序相关的全局变量和函数定义
 ***********************************************************************************/
#ifndef _PUPUB_H
#define _PUPUB_H

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENDFIELD
// 为了在
#define ENDFIELD -1
#endif


/* ****** Updated by CHENYH at 2004-2-7 17:54:49 ****** 
以下定义SQC等中需要的各全局数据
*/

typedef struct
{
   unsigned char buf[48];
} SYSHEAD;

typedef struct
{
   unsigned short SourceNo;         /* 本请求接受在服务端的通讯平台编号 */
   SYSHEAD syshead;                 /* 请求接受时作为服务端的通讯标记块，业务代码部分不要修改，只是在特殊情况下可以记录到数据库中，作为二阶段提交时候使用 */
} TRUSERID;    /* 请求端作为在通讯平台中的标识 */

typedef struct
{
   unsigned short SourceNo;         /* 起始发送通讯平台的编号 （参见TRUSERID::SourceNo）*/
   unsigned short DestNo;           /* 推送目标点的通讯平台编号 */
   unsigned short FuncNo;           /* 推送目标点注册的通讯功能号 */
   unsigned int   BatchNo;          /* 针对该目标点的批次号 */
} TPUSHDEST;     /* 推送目标点的定义 */


typedef struct
{
   //bool bReverse;     // 当前业务处理单元的字节顺序是否需要作倒序处理，主要是CPACK字段等处理的时候识别用

   char szSvrIP[20];  // 上级服务处理调度中心的IP地址
   int  iSvrPort;     // 上级服务处理调度中心的开放端口号
   int  iHBInterval;  // 向上级服务处理调度中心发送空闲等待信息的间隔，以毫秒计

   char  szBUGroupID[12];  // 本业务处理单元组别
   //int iBUnitGourpID; // 本业务处理单元组别

   //TRUSERID *pUserID;  // 当前调用功能的请求客户句柄
   void *pSvrLink;     // 用于指向与BCC的连接，由于这个头文件用于.sqc，所以不能用CSvrLink的指针

} ST_BUNIT;  // 对本处理子系统实际只有一个实例，但是为了未来统一处理，定义了一个结构，也是为了兼容将来能够处理多业务处理单元

extern ST_BUNIT g_BUnit;  // 本系统由于ESQL缘故，只有一个处理单元实例


// 函数名: SetCol
// 编程  : 陈永华 2004-2-8 23:26:38
// 描述  : 重置输出的CPACK报文记录为0，设置将要输出的对应字段
// 返回  : int 
// 参数  : void *handle － 暂时就对应的 TRUSERID *, 在本系统没有意义，因为单线程的缘故
// 参数  : ...  用 F_XXXXX 定义的相关字段列表，用END_FIELD表示结束
BUPUB_API int SetCol(TRUSERID *handle,...);


// 函数名: PutRowData
// 编程  : 陈永华 2004-2-8 23:30:07
// 描述  : 在输出的CPACK报文中增加一条ST_PACK报体记录，实际对之前用SetCol定义的字段有效，没有定义的无效
//         注意尽量使用PutRow，而不使用本函数
// 返回  : int 
// 参数  : ST_PACK *pdata  － 增加的ST_PACK存放数据
BUPUB_API int PutRowData(ST_PACK *pdata);



// 函数名: AnswerData
// 编程  : 陈永华 2004-2-8 23:32:42
// 描述  : 向ruserid的客户端，发送由SetCol和PutRow设置的应答返回的数据
//          注意：当AnswerMode（参见SetAnswerMode()函数说明）为AM_AUTO时候，不需要调用本函数
//          除非因为后面还有许多处理，但是和客户端应答无关的话，则可以调用一下，
//          以免让客户端长时间等待
// 返回  : int 
// 参数  : TRUSERID *ruserid  目标客户端的标识
// 参数  : int retcode 应答数据的返回码 对应ST_CPACK的头中的RetCode
// 参数  : char *szmsg 如果为NULL或“”，则应答数据中，就不包括vsmess字段数据
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg);


// 函数名: PutRow
// 编程  : 陈永华 2004-2-20 10:03:04
// 描述  : 一次性完成PutRowData 和 AnswerData, 但是并不马上发送 （为了与大集中版本兼容）
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : ST_PACK *pdata
// 参数  : int *pRetCode   有可能被cpack头中的retCode返回给客户端
// 参数  : char *rtnMsg
BUPUB_API int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg);

#define ADP_ROWS  50
// 函数名: AnswerDataPart
// 编程  : 陈永华 2004-2-12 12:12:09
// 描述  : 与AnswerData类似，但是用于通知客户端，还有更多的数据返回
//         常用于将有大批量数据返回，尽管数据项相同但是为了不让客户端长时间等待
//         先发送部分数据。如已经有100条记录需要返回，但还有记录将要返回，则首次累计ADP_ROWS条就调用本请求
//         注意调用过这个后，对同一个用户端，不需要再调用AnswerData或AnswerDataPart了，
//         因为取后续数据和本业务模块无关了，BCC会自动与用户端交换后续数据，当然，调用模块必须有足够速度通过
//         PutRow返回后续数据
//   注意：因为提供了SetMaxRow()函数，所以，不用调用这个函数而是通过SetMaxRow()函数即可。
// 返回  : int 
// 参数  : TRUSERID *ruserid
// 参数  : int retcode
// 参数  : char *szmsg
BUPUB_API int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg);

// 函数名: AnswerDataEx
// 编程  : 陈永华 2004-2-8 23:37:00
// 描述  : 向ruserid的客户端，发送apack和pArrays组成应答返回的数据
//     注意：本函数专门用于向一个非本功能请求方发送结果的时候使用，如银证通业务模式的时候
// 返回  : int 
// 参数  : TRUSERID *ruserid  目标客户端的标识
// 参数  : ST_CPACK *apack  应答数据头和首报体
// 参数  : ST_PACK *pArrays 后续数据报体，当apack->head.RetCount<=1时候，无效 可以填写为NULL
// 参数  : int retcode 应答数据的返回码 对应ST_CPACK的头中的RetCode
// 参数  : char *szmsg 如果为NULL或“”，则应答数据中，就不包括vsmess字段数据
BUPUB_API int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg);

// 下面为推送数据的时候，pushmode选用的参数： 在mypub.h中定义了
//#ifndef PM_INACK 
//   #define PM_REMOVE 'X'
//   #define PM_INACK  '0'  /* 非可靠推送 */
//   #define PM_ACK    '1'  /* 可靠推送,需要对方接收后必须有接收确认回单 */
//   #define PM_ANSWER '2'  /* 在特殊情况下使用，作为请求发送给目标点，外部处理结束后应答返回的时候，需要再次提交给原始的BUNIT */
//#endif
// 函数名: PushData
// 编程  : 陈永华 2004-2-8 23:43:01
// 描述  : 向一个作为服务方式注册的目标点，推送数据 
// 返回  : int 
// 参数  : int sourceno  推送数据使用的通讯平台的编号，参见TRUSERID::SourceNo
// 参数  : int destno    推送数据的目标通讯平台编号
// 参数  : int funcno    目标服务端在通讯平台上注册的通讯功能号
// 参数  : int batchno   针对该目标点会话批次号
// 参数  : ST_CPACK *ppack  推送的数据包，ppack->head.RetCount<=1，即推送数据不能超过1条报体记录
// 参数  : char pushmode  推送模式，见上述定义的PM_xxx
// 参数  : int acktime   确认回答的期限，以秒计，对于PM_ACK ,PM_ANSWER 有效  
BUPUB_API int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime);


// 函数名: PushDataEx
// 编程  : 陈永华 2004-2-9 0:10:53
// 描述  : 向pushdests定义的作为服务方式注册目标点推送数据
// 返回  : int 
// 参数  : TPUSHDEST *pushdests 定义的目标点列表
// 参数  : int pdcount  目标点的个数
// 参数  : ST_CPACK *ppack 推送的不超过一条记录的数据包 注意包头上的ppack->head.userdata=batchno(批次号)
// 参数  : char pushmode 推送模式，见上述定义的PM_xxx
// 参数  : int acktime  确认回答的期限，以秒计，对于PM_ACK ,PM_ANSWER 有效 
BUPUB_API int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime);


// 函数名: ExtCall
// 编程  : 陈永华 2004-3-6 17:47:14
// 描述  : 向另外一个服务点发送请求，要求对方处理应答返回，本功能常常用于不同系统之间的对接，如要求其他外围系统服务
// 返回  : int >=0:成功，返回的为应答数据包体记录数；<0:错误；-2:等待接收应答超时；-1:其他通讯错误
// 参数  : int sourceno  使用的通讯平台的编号，参见TRUSERID::SourceNo
// 参数  : int destno    目标通讯平台编号
// 参数  : int funcno    目标服务端在通讯平台上注册的通讯功能号
// 参数  : int batchno   该目标点会话批次号 (如果确认针对该目标点，不会有其他的推送模式，则可以直接填写为0)
// 参数  : int acktime   该请求的有效时间，以秒计
// 参数  : ST_CPACK *rpack  请求包数据
// 参数  : ST_CPACK *apack  目标点应答的数据返回
// 参数  : ST_PACK *pArrays 应答数据后续包数据
BUPUB_API int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays);

// 函数名: ExtCallNext
// 编程  : 陈永华 2004-3-8 17:31:47
// 描述  : 在调用ExtCall之后，发现对方尚有数据还没有取回来，则用本功能获取后续数据
// 返回  : int >=0:成功，返回的为应答数据包体记录数；<0:错误；-2:等待接收应答超时；-1:其他通讯错误；-3:已经取完了后续数据
// 参数  : int acktime
// 参数  : ST_CPACK *apack
// 参数  : ST_PACK *pArrays
BUPUB_API int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays);



// 函数名: ResetNormalCPack
// 编程  : 陈永华 2004-3-11 20:30:59
// 描述  : 根据本业务请求包，设置一个CPACK包头，位图和数据都被清空了
// 返回  : void 
// 参数  : ST_CPACK *pack
BUPUB_API void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount);

// 函数名: CheckProcCancel
// 编程  : 陈永华 2004-3-10 15:44:20
// 描述  : 检查是否本处理请求，前台是否要求停止。注意：这个由于要检查连接上是否有该停止命令而会导致等1毫秒，而使得处理效率降低
// 返回  : int 1:表示前台有要求停止的命令；0:没有
BUPUB_API int CheckProcCancel();

// 函数名: CT_ERR_DEAL
// 编程  : 陈永华 2004-2-22 16:39:51
// 描述  : 清除原来准备的应答信息，并且在运行时跟踪文件中记录（错误）信息（为了与集中交易兼容）
// 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
// 参数  : char *msg
// 参数  : int retcode
BUPUB_API int CT_ERR_DEAL(char *msg,int retcode);


// 函数名: Error_Deal
// 编程  : 陈永华 2004-2-22 16:43:34
// 描述  : 清除原来准备的应答信息，并且在运行时跟踪文件中记录（错误）信息 建议新系统使用本函数替代原来的ERR_DEAL
//         合并了原来需要用sprintf生成omsg
// 返回  : int SendMsg返回信息
// 参数  : int retcode
// 参数  : char *omsg  OUT
// 参数  : char *pFormat IN
// 参数  : ... IN
BUPUB_API int Error_Deal(int retcode,char *omsg,char *pFormat,...);

// 函数名: SQLDebugLog
// 编程  : 陈永华 2004-3-4 17:45:16
// 描述  : 专门为了SQC使用（在C中使用的）记录信息到本地LOG日志中
// 返回  : void 
// 参数  : int errorcode
// 参数  : char *pFormat
// 参数  : ...
BUPUB_API void SQLDebugLog(int errorcode,char *pFormat,...);


// 函数名: TextLogOut
// 编程  : 陈永华 2006-1-5 15:35:24
// 描述  : 将已经格式化好的文本信息输出到日志文件中，这种方法对于这种模式下，要比SQLDebugLog快一点
// 返回  : void 
// 参数  : int errorcode [IN]: 信息编码号
// 参数  : char *textlog [IN]: 文本信息
BUPUB_API void TextLogOut(int errorcode, char *textlog);

/* ****** Updated by CHENYH at 2004-2-7 20:06:13 ****** 
   If your project does not include a .sqc file that includes a main() or WinMain() function, 
   you must explicitly declare SQLCODE in one of your modules. 
   Explicit SQLCODE declarations can occur either inside 
   or outside of a host variable declaration block.
*/
/* ****** Updated by CHENYH at 2004-3-10 13:02:41 ****** 
// 设置BCC应答数据处理模式，见CBULinkThread/CSvrLink中的iAnswerMode
*/
#ifndef AM_AUTO
   #define AM_AUTO     'A'   // 一旦有数据就打包自动发送给请求客户端
   #define AM_CONFIRM  'C'   // 有数据只有在业务处理要求才发送给请求客户端,需要用AnswerData或AnswerDataPart才发送
#endif
extern char iDefaultAnswerMode;   // 本系统缺省的应答模式


// 函数名: SetAnswerMode
// 编程  : 陈永华 2004-3-10 18:48:18
// 描述  : 更改应答模式，见AM_xxxx的定义 这往往用于特殊功能的情况下使用
// 返回  : int 
// 参数  : char iAnswerMode 见AM_xxxx的定义
BUPUB_API int SetAnswerMode(char iAnswerMode);


// 函数名: BCCMsgLogOut
// 编程  : 陈永华 2004-3-10 19:31:25
// 描述  : 由BCC集中输出本BU的文本日志信息
// 返回  : int 
// 参数  : int logid ：本日志的ID号
// 参数  : char *pFormat ：文本日志的格式定义
// 参数  : ... ：以pFormat定义的输出参数
BUPUB_API int BCCMsgLogOut(int logid,char *pFormat,...);


// 函数名: SetMaxRow
// 编程  : 陈永华 2004-3-22 11:41:26
// 描述  : 设置本次功能处理时候，每个应答包返回的最大记录数，只对本次功能处理有效
// 返回  : int 
// 参数  : int maxrows
BUPUB_API int SetMaxRow(int maxrows);

// 函数名: SetBUError
// 编程  : 陈永华 2004-3-22 11:42:37
// 描述  : 设置本BU出错信息，用于提供给前端程序
// 返回  : int 
// 参数  : int errcode
// 参数  : char *pFormat
// 参数  : ...
BUPUB_API int SetBUError(int errcode,char *pFormat,...);


// 函数名: SetAnswerTimeout
// 编程  : 陈永华 2004-3-22 12:49:02
// 描述  : 设定本业务每个应答包的超时时间，以毫秒计，常用于如批结算时候特殊的处理
// 返回  : int 
// 参数  : unsigned int atimeout  指定的超时时间（以毫秒计）
BUPUB_API int SetAnswerTimeout(unsigned int atimeout);


// 函数名: ResetAnswerData
// 编程  : 陈永华 2004-3-24 22:16:17
// 描述  : 重置清除已经提交的应答数据，常用于重新执行一个处理，比如因为程序死锁后Retry
// 返回  : int 
BUPUB_API int ResetAnswerData();


#ifdef __cplusplus
}
#endif

#undef BUPUB_API

#endif
