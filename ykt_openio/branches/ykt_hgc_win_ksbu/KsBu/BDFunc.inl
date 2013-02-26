#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：
#ifdef __cplusplus
extern "C" {
#endif
int FTestIReply(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
int FTestBCCShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmMultiRows(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FTestBUShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmGetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
int FBCCShmSetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// 函数名: FTestBCCIntCall
// 编程  : 陈永华 2005-9-22 11:07:44
// 描述  : 用功能号1013测试BCC的IntCall/IntCallNext、RACall/RACallNext的功能
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack：vsmess=外调的ＢＵ组号，空则调用RACall/RACallNext
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCIntCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// 函数名: FTestBCCIntTransfer
// 编程  : 陈永华 2005-9-23 15:42:19
// 描述  : 用功能号1013测试BCC的IntTransfer、RATransfer的功能
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack: vsmess=外调的ＢＵ组号，空则调用RATransfer
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCIntTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// 函数名: FTestBCCExtCall
// 编程  : 陈永华 2005-9-24 12:28:40
// 描述  : 用1013功能测试外调功能
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack : lvol0-sourceno; lvol1-destno; lvol2-funcno; vsmess-BCCSHMWrite的记录数
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCExtCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// 函数名: FTestBCCExtTransfer
// 编程  : 陈永华 2005-9-24 12:31:15
// 描述  : 用1013功能测试外部转发请求
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack : lvol1-destno; lvol2-funcno; vsmess-BCCSHMWrite的记录数
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCExtTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// 函数名: FTestPushData
// 编程  : 陈永华 2005-9-25 11:30:31
// 描述  : 用1010功能来测试推送功能的各种情况
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack:lvol0=sourceno,lvol1=destno,lvol2=funcno
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestPushData(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);

// 函数名: FTestBURunTime
// 编程  : 陈永华 2005-9-27 15:06:29
// 描述  : 为了测试BCC中对BU组中的MAXRUNTIME是否如说明起作用
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack : vsmess-hold time in second
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBURunTime(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);
/*
int FTestProc(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
int FTestMultiRows(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FTestExtCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FTestMultiCols(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);
*/


// 函数名: FGetFile
// 编程  : 陈永华 2005-10-19 10:30:34
// 描述  : 从BU端下载文件
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack : vsmess - 带相对或绝对路径的文件
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FGetFile(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);



// 函数名: FPTestExtCall
// 编程  : 陈永华 2005-10-25 14:45:42
// 描述  : 用1010测试ExtCall的速度
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack : lvol0 - sno; lvol1 - dno; lvol2 - fno
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FPTestExtCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// 函数名: FPTestIntCall
// 编程  : 陈永华 2005-10-25 14:47:31
// 描述  : 用1010测试IntCall/RACall的速度
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack: vsmess - 内部调用BU组ID；空表示用RACall
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FPTestIntCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// 函数名: FPTestExtTransfer
// 编程  : 陈永华 2005-10-25 14:49:29
// 描述  : 用1010测试ExtTransfer的速度
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack: lvol1-dno, lvol2-fno
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FPTestExtTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);



// 函数名: FPTestIntTransfer
// 编程  : 陈永华 2005-10-25 14:51:13
// 描述  : 用1010测试IntTransfer/RATransfer的速度
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack: vsmess - 内部调用BU组ID；空表示用RATransfer
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FPTestIntTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg);


// 函数名: FGetBaseOperTimes
// 编程  : 陈永华 2005-10-29 1:51:40
// 描述  : 
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack：vsmess - loops
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FGetBaseOperTimes(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg);


// 功能号函数原型声明, 便于BU回调
///////////////////////////////////////////////////////////////////////////////////
int F847307(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847308(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847350(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847351(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847352(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847355(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847356(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847357(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847360(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F847361(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
///////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(847307 ,F847307, "网络收费帐户查询", "lx", 1)
	INSERT_FUNCTION(847308 ,F847308, "网络收费帐户转账", "lx", 1)
	INSERT_FUNCTION(847350 ,F847350, "上海理工人员信息对接", "lx", 1)
	INSERT_FUNCTION(847351 ,F847351, "数据库名单信息对接", "lx", 1)
	INSERT_FUNCTION(847352 ,F847352, "公安专科水控转帐对接", "lx", 1)
	INSERT_FUNCTION(847355 ,F847355, "海事大学电控测试数据库连接", "lx", 1)
	INSERT_FUNCTION(847356 ,F847356, "海事大学电控转帐查询", "lx", 1)
	INSERT_FUNCTION(847357 ,F847357, "海事大学电控转帐对接", "lx", 1)
	INSERT_FUNCTION(847360 ,F847360, "哈工程网络转帐查询", "lx", 1)
	INSERT_FUNCTION(847361 ,F847361, "哈工程网络转帐", "lx", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
