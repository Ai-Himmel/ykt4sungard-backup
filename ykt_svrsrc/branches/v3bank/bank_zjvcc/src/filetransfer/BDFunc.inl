#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：

///////////////////////////////////////////////////////////////////////////////////
/*

*/

/* 门禁后台功能号定义 */
/**************************************************************************/


// 通用前置机功能

//int FGetFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int FPutFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

///////////////////////////////////////////////////////////////////////////////////

// 下面数据表为本业务处理单元能处理的所有合法业务处理过程及其相关参数
TBDefine g_XBDefines[]=
{
	/*
	INSERT_FUNCTION(1010,FTestIReply,"最快速的处理，用于测试速度","CYH Demo",1)
	INSERT_FUNCTION(1011,FTestBCCShm,"用于测试BCCSHM速度","CYH Demo",1)
	INSERT_FUNCTION(1012,FTestBUShm,"用于测试BUSHM速度","CYH Demo",1)
	INSERT_FUNCTION(1013,FBCCShmMultiRows,"用于测试BCCSHM的多包返回及其工作","CYH Demo",1)
	INSERT_FUNCTION(1014,FBCCShmGetRecord,"读取BCCSHM共享内存中的数据","CYH Demo",1)
	INSERT_FUNCTION(1015,FBCCShmSetRecord,"读取共享内存中的数据返回给客户端，将请求包中的值设置到共享内存中","CYH Demo",1)
	INSERT_FUNCTION(1016,FTestBCCIntCall,"用功能号1013测试BCC的IntCall/IntCallNext、RACall/RACallNext的功能","CYH Demo",1)
	INSERT_FUNCTION(1017,FTestBCCIntTransfer,"用功能号1013测试BCC的IntTransfer、RATransfer的功能","CYH Demo",1)
	INSERT_FUNCTION(1018,FTestBCCExtCall,"用1013功能测试外调功能ExtCall/ExtCallNext","CYH Demo",1)
	INSERT_FUNCTION(1019,FTestBCCExtTransfer,"用1013功能测试外部转发请求ExtTransfer","CYH Demo",1)
	INSERT_FUNCTION(1020,FTestPushData,"用1010功能来测试推送功能PushData","CYH Demo",2)
	INSERT_FUNCTION(1021,FTestBURunTime,"测试BCC中对BU组中的MAXRUNTIME是否如说明起作用","CYH Demo",3)
	INSERT_FUNCTION(1025,FGetBaseOperTimes,"检查1013中在不同平台下各个操作的耗时分时时间","CYH TEST",3)
	INSERT_FUNCTION(1030,FPTestExtCall,"用1010测试ExtCall的速度","CYH Demo",1)
	INSERT_FUNCTION(1031,FPTestIntCall,"用1010测试IntCall/RACall的速度","CYH Demo",1)
	INSERT_FUNCTION(1032,FPTestExtTransfer,"用1010测试ExtTransfer的速度","CYH Demo",1)
	INSERT_FUNCTION(1033,FPTestIntTransfer,"用1010测试IntTransfer/RATransfer的速度","CYH Demo",1)
	INSERT_FUNCTION(9990,FGetFile,"从BU端下载文件","CYH Demo",3)
  */
	
	

	INSERT_FUNCTION(2000,FPutFile,"下传文件","wenjian",1)
	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
