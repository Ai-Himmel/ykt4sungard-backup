#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：

///////////////////////////////////////////////////////////////////////////////////
int F2401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900077(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F250006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F260006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950996(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
///////////////////////////////////////////////////////////////////////////////////

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(2401 ,F2401, "xxx", "wyb", 1)
	INSERT_FUNCTION(900077 ,F900077, "xxx", "wj", 1)
	INSERT_FUNCTION(250001 ,F250001, "xxx", "wj", 1)
	INSERT_FUNCTION(250002 ,F250002, "xxx", "hlq", 1)
	INSERT_FUNCTION(250003 ,F250003, "xxx", "hlq", 1)
	INSERT_FUNCTION(250004 ,F250004, "xxx", "hlq", 1)
	INSERT_FUNCTION(250006 ,F250006, "xxx", "hlq", 1)
	INSERT_FUNCTION(260001 ,F260001, "xxx", "lx", 1)
	INSERT_FUNCTION(260002 ,F260002, "xxx", "lx", 1)
	INSERT_FUNCTION(260006 ,F260006, "xxx", "lx", 1)
	INSERT_FUNCTION(270001 ,F270001, "银行卡绑定", "wj", 1)
	INSERT_FUNCTION(950996 ,F950996, "xxx", "hlq", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
