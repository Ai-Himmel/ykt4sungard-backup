#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：
//#ifdef __cplusplus
//extern "C" {
//#endif

// 功能号函数原型声明, 便于BU回调
///////////////////////////////////////////////////////////////////////////////////
int F3001(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);
int F3002(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg);

///////////////////////////////////////////////////////////////////////////////////

//#ifdef __cplusplus
//}
//#endif

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_XBDefines[]=
{
	INSERT_FUNCTION(3001 ,F3001, "网络转账帐户查询合法性", "hlq", 1)
	INSERT_FUNCTION(3002 ,F3002, "网费充值", "hlq", 1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
