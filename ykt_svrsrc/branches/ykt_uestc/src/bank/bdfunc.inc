#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：
int F900077(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
#ifdef __cplusplus
extern "C" {
#endif
// 日结过程，提供给前台一个button：
#ifdef __cplusplus
}
#endif

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_BDefines[]=
{
// {功能号,过程函数   ,"功能描述"                                     ,"编程人员姓名"    ,优先级,false,0,0,0,0,0},
   
   {900077,F900077,"转帐服务程序" ,"hhd",1,false,0,0,0,0,0},
   {0,NULL,"END BPFunctions List","CYH Marked",0,false,0,0,0,0,0},  // the last mark line，Don't remove this line
};
#endif
