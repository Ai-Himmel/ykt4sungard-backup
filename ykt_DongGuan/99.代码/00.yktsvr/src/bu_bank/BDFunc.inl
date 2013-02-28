#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：


#define DEF_FUNC(x) int F##x(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
#define NEW_FUNC(x,m,a) {x,F##x,m,a,1,false,0,0,0,0,0}
#define NEW_FUNC_NO(n,x,m,a) {n,F##x,m,a,1,false,0,0,0,0,0}

///////////////////////////////////////////////////////////////////////////////////
DEF_FUNC(5000);
DEF_FUNC(5001);
DEF_FUNC(5002);
DEF_FUNC(5003);
DEF_FUNC(5004);
DEF_FUNC(5005);
DEF_FUNC(5101);
DEF_FUNC(5102);
///////////////////////////////////////////////////////////////////////////////////

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_XBDefines[]=
{
    NEW_FUNC_NO(50000,5000,"圈存服务状态查询","tc"),
    NEW_FUNC_NO(50001,5001,"圈存前置机签到","tc"),
    NEW_FUNC_NO(50002,5002,"圈存初始化","tc"),
    NEW_FUNC_NO(50003,5003,"圈存确认","tc"),
    NEW_FUNC_NO(50004,5004,"圈存结果验证","tc"),
    NEW_FUNC_NO(50005,5005,"圈存补写","tc"),
    NEW_FUNC_NO(50101,5101,"查询圈存明细","tc"),
    NEW_FUNC_NO(50102,5102,"查询消费明细","tc"),
	{0,NULL,"END BPFunctions List","CYH Marked",0} // the last mark line，Don't remove this line
};
#endif

