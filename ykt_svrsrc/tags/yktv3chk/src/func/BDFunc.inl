#ifndef BDFUNC_INC
#define BDFUNC_INC
/*  在每个业务处理过程中必须有如下这样一行：详细各项表示的含义，见BDefine.h中的描述：
   {1000     ,FTestProc   ,"Demo for SQC 业务处理函数编写样板"             ,"CYH Demo"          ,1     ,false,0,0,0,0,0},
   {功能号   ,过程函数>    ,"功能描述"                                     ,"编程人员姓名"       ,优先级,false,0,0,0,0,0},
*/
// 下面列出所有合法的业务处理过程函数列表：

///////////////////////////////////////////////////////////////////////////////////
int F240157(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F700000(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F700001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F700002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800202(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800203(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800701(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800703(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800704(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800742(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800751(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800761(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800772(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800782(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800783(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F800785(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820106(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820108(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820110(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820111(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820112(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820113(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820114(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820303(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820304(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820311(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820321(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820341(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820350(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820352(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820353(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820354(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820355(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820356(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820402(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820405(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820501(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820502(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820511(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820516(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820521(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820522(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820704(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820705(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841605(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841606(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841607(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841608(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841611(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841612(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841613(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841614(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841700(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842501(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843340(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843341(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843342(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843355(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843356(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843357(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843358(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843359(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843360(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843361(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843362(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843363(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843364(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843368(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843369(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843370(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843371(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843373(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
//==============卡库存管理======================
int F846101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846106(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846107(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846201(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846202(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846203(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846204(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846303(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846305(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846307(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846308(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846309(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846310(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846312(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846314(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846315(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846316(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846317(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846333(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846334(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846337(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846338(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846402(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846403(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846501(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846502(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846600(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846602(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846603(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846605(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F846606(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847110(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847111(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847130(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847131(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847132(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847166(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847173(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847185(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847198(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847226(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847227(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847228(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847229(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847230(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847231(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848250(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848251(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848252(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848254(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848255(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848256(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848257(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848258(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848259(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848260(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847232(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F940005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
/*

*/

/* 门禁后台功能号定义 */
/**************************************************************************/
int F849021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);


// 通用前置机功能

//int FGetFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

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
	
	INSERT_FUNCTION(240157 ,F240157, "xxx", "wj", 1)
	INSERT_FUNCTION(240001 ,F240001, "xxx", "wj", 1)
	INSERT_FUNCTION(240002 ,F240002, "xxx", "wj", 1)
	INSERT_FUNCTION(240003 ,F240003, "xxx", "wj", 1)
	INSERT_FUNCTION(240004 ,F240004, "xxx", "wj", 1)
	INSERT_FUNCTION(240005 ,F240005, "xxx", "wj", 1)
	INSERT_FUNCTION(240006 ,F240006, "xxx", "wj", 1)
	INSERT_FUNCTION(240007 ,F240007, "xxx", "wj", 1)
	INSERT_FUNCTION(240008 ,F240008, "xxx", "wj", 1)
	INSERT_FUNCTION(240009 ,F240009, "xxx", "wj", 1)
	INSERT_FUNCTION(240010 ,F240010, "xxx", "wj", 1)
	INSERT_FUNCTION(240011 ,F240011, "xxx", "wj", 1)
	INSERT_FUNCTION(700000 ,F700000, "xxx", "wj", 1)
	INSERT_FUNCTION(700001 ,F700001, "xxx", "wj", 1)
	INSERT_FUNCTION(700002 ,F700002, "xxx", "wj", 1)
	INSERT_FUNCTION(800202 ,F800202, "xxx", "wj", 1)
	INSERT_FUNCTION(800203 ,F800203, "xxx", "wj", 1)
	INSERT_FUNCTION(800701 ,F800701, "xxx", "wj", 1)
	INSERT_FUNCTION(800703 ,F800703, "xxx", "wj", 1)
	INSERT_FUNCTION(800704 ,F800704, "xxx", "wj", 1)
	INSERT_FUNCTION(800742 ,F800742, "xxx", "wj", 1)
	INSERT_FUNCTION(800751 ,F800751, "xxx", "wj", 1)
	INSERT_FUNCTION(800761 ,F800761, "xxx", "wj", 1)
	INSERT_FUNCTION(800772 ,F800772, "xxx", "wj", 1)
	INSERT_FUNCTION(800782 ,F800782, "xxx", "wj", 1)
	INSERT_FUNCTION(800783 ,F800783, "xxx", "wj", 1)
	INSERT_FUNCTION(800785 ,F800785, "xxx", "wj", 1)
	INSERT_FUNCTION(820001 ,F820001, "xxx", "wj", 1)
	INSERT_FUNCTION(820002 ,F820002, "xxx", "wj", 1)
	INSERT_FUNCTION(820003 ,F820003, "xxx", "wj", 1)
	INSERT_FUNCTION(820004 ,F820004, "xxx", "wj", 1)
	INSERT_FUNCTION(820005 ,F820005, "xxx", "wj", 1)
	INSERT_FUNCTION(820101 ,F820101, "xxx", "wj", 1)
	INSERT_FUNCTION(820102 ,F820102, "xxx", "wj", 1)
	INSERT_FUNCTION(820103 ,F820103, "xxx", "wj", 1)
	INSERT_FUNCTION(820104 ,F820104, "xxx", "wj", 1)
	INSERT_FUNCTION(820105 ,F820105, "xxx", "wj", 1)
	INSERT_FUNCTION(820106 ,F820106, "xxx", "wj", 1)
	INSERT_FUNCTION(820108 ,F820108, "xxx", "wj", 1)
	INSERT_FUNCTION(820110 ,F820110, "设备文件导入", "wj", 1)
	INSERT_FUNCTION(820111 ,F820111, "xxx", "wj", 1)
	INSERT_FUNCTION(820112 ,F820112, "xxx", "wj", 1)
	INSERT_FUNCTION(820113 ,F820113, "xxx", "wj", 1)
	INSERT_FUNCTION(820114 ,F820114, "xxx", "wj", 1)
	INSERT_FUNCTION(820301 ,F820301, "xxx", "wj", 1)
	INSERT_FUNCTION(820302 ,F820302, "xxx", "wj", 1)
	INSERT_FUNCTION(820303 ,F820303, "xxx", "wj", 1)
	INSERT_FUNCTION(820304 ,F820304, "xxx", "wj", 1)
	INSERT_FUNCTION(820311 ,F820311, "xxx", "wj", 1)
	INSERT_FUNCTION(820321 ,F820321, "操作员站点设置", "wj", 1)
	INSERT_FUNCTION(820331 ,F820331, "xxx", "wj", 1)
	INSERT_FUNCTION(820332 ,F820332, "xxx", "wj", 1)
	INSERT_FUNCTION(820341 ,F820341, "xxx", "wj", 1)
	INSERT_FUNCTION(820350 ,F820350, "前台注册", "wj", 1)
	INSERT_FUNCTION(820351 ,F820351, "xxx", "wj", 1)
	INSERT_FUNCTION(820352 ,F820352, "xxx", "wj", 1)
	INSERT_FUNCTION(820353 ,F820353, "xxx", "wj", 1)
	INSERT_FUNCTION(820354 ,F820354, "xxx", "tc", 1)
	INSERT_FUNCTION(820355 ,F820355, "xxx", "tc", 1)
	INSERT_FUNCTION(820356 ,F820356, "xxx", "tc", 1)
	INSERT_FUNCTION(820402 ,F820402, "全局参数修改", "wj", 1)
	INSERT_FUNCTION(820405 ,F820405, "全局参数查询", "wj", 1)
	INSERT_FUNCTION(820501 ,F820501, "xxx", "wj", 1)
	INSERT_FUNCTION(820502 ,F820502, "xxx", "wj", 1)
	INSERT_FUNCTION(820511 ,F820511, "xxx", "wj", 1)
	INSERT_FUNCTION(820516 ,F820516, "xxx", "wj", 1)
	INSERT_FUNCTION(820521 ,F820521, "xxx", "wj", 1)
	INSERT_FUNCTION(820522 ,F820522, "xxx", "wj", 1)
	INSERT_FUNCTION(820601 ,F820601, "xxx", "gg", 1)
	INSERT_FUNCTION(820704 ,F820704, "xxx", "wj", 1)
	INSERT_FUNCTION(820705 ,F820705, "xxx", "wj", 1)
	INSERT_FUNCTION(841601 ,F841601, "xxx", "wj", 1)
	INSERT_FUNCTION(841605 ,F841605, "银行卡绑定", "wj", 1)
	INSERT_FUNCTION(841606 ,F841606, "xxx", "wj", 1)
	INSERT_FUNCTION(841607 ,F841607, "xxx", "wj", 1)
	INSERT_FUNCTION(841608 ,F841608, "xxx", "wj", 1)
	INSERT_FUNCTION(841611 ,F841611, "xxx", "wj", 1)
	INSERT_FUNCTION(841612 ,F841612, "xxx", "wj", 1)
	INSERT_FUNCTION(841613 ,F841613, "xxx", "wj", 1)
	INSERT_FUNCTION(841614 ,F841614, "xxx", "wj", 1)
	INSERT_FUNCTION(841700 ,F841700, "xxx", "lx", 1)
	INSERT_FUNCTION(842001 ,F842001, "部门信息设置", "wj", 1)
	INSERT_FUNCTION(842501 ,F842501, "xxx", "wj", 1)
	INSERT_FUNCTION(843335 ,F843335, "xxx", "wj", 1)
	INSERT_FUNCTION(843340 ,F843340, "xxx", "wj", 1)
	INSERT_FUNCTION(843341 ,F843341, "xxx", "wj", 1)
	INSERT_FUNCTION(843342 ,F843342, "xxx", "wj", 1)
	INSERT_FUNCTION(843351 ,F843351, "充值商户存款", "wj", 1)
	INSERT_FUNCTION(843355 ,F843355, "充值商户设备添加", "wj", 1)
	INSERT_FUNCTION(843356 ,F843356, "充值商户设备删除", "wj", 1)
	INSERT_FUNCTION(843357 ,F843357, "充值商户设备查询", "wj", 1)
	INSERT_FUNCTION(843358 ,F843358, "充值操作员添加", "wj", 1)
	INSERT_FUNCTION(843359 ,F843359, "充值操作员修改", "wj", 1)
	INSERT_FUNCTION(843360 ,F843360, "充值操作员删除", "wj", 1)
	INSERT_FUNCTION(843361 ,F843361, "充值操作员查询", "wj", 1)
	INSERT_FUNCTION(843362 ,F843362, "充值操作员设备添加", "wj", 1)
	INSERT_FUNCTION(843363 ,F843363, "充值操作员设备删除", "wj", 1)
	INSERT_FUNCTION(843364 ,F843364, "充值操作员设备查询", "wj", 1)
	INSERT_FUNCTION(843370 ,F843370, "设备商户文件导入管理", "wj", 1)
	INSERT_FUNCTION(843371 ,F843371, "设备商户查询", "wj", 1)
	INSERT_FUNCTION(843373 ,F843373, "客户类别设置", "wj", 1)
	//===================卡库存管理(846***)==========
	INSERT_FUNCTION(846101 ,F846101, "xxx", "lx", 1)
	INSERT_FUNCTION(846102 ,F846102, "xxx", "lx", 1)
	INSERT_FUNCTION(846103 ,F846103, "xxx", "lx", 1)
	INSERT_FUNCTION(846104 ,F846104, "xxx", "lx", 1)
	INSERT_FUNCTION(846105 ,F846105, "xxx", "lx", 1)
	INSERT_FUNCTION(846201 ,F846201, "xxx", "lx", 1)
	INSERT_FUNCTION(846202 ,F846202, "xxx", "lx", 1)
	INSERT_FUNCTION(846106 ,F846106, "xxx", "lx", 1)
	INSERT_FUNCTION(846107 ,F846107, "操作员当前显示卡号查询", "闻剑", 1)
	INSERT_FUNCTION(846203 ,F846203, "xxx", "lx", 1)
	INSERT_FUNCTION(846204 ,F846204, "xxx", "lx", 1)
	INSERT_FUNCTION(846501 ,F846501, "网点设置", "wj", 1)
	INSERT_FUNCTION(846502 ,F846502, "交易收费配置", "wj", 1)
	INSERT_FUNCTION(846600 ,F846600, "开户客户信息查询", "wj", 1)
	INSERT_FUNCTION(846601 ,F846601, "手续费查询", "wj", 1)
	INSERT_FUNCTION(846602 ,F846602, "已开户客户信息查询", "wj", 1)
	INSERT_FUNCTION(846603 ,F846603, "电子钱包已开户客户信息查询", "wj", 1)
	INSERT_FUNCTION(846605 ,F846605, "卡交易流水查询", "wj", 1)
	INSERT_FUNCTION(846606 ,F846606, "帐户交易明细查询", "wj", 1)
	INSERT_FUNCTION(846301 ,F846301, "一卡通开户", "wj", 1)
	INSERT_FUNCTION(846302 ,F846302, "一卡通开户冲正", "wj", 1)
	INSERT_FUNCTION(846303 ,F846303, "一卡通销户", "wj", 1)
	INSERT_FUNCTION(846305 ,F846305, "一卡通补办", "wj", 1)
	INSERT_FUNCTION(846307 ,F846307, "一卡通挂失解挂", "wj", 1)
	INSERT_FUNCTION(846308 ,F846308, "一卡通冻结解冻", "wj", 1)
	INSERT_FUNCTION(846309 ,F846309, "一卡通坏卡登记", "wj", 1)
	INSERT_FUNCTION(846310 ,F846310, "一卡通回收卡", "wj", 1)
	INSERT_FUNCTION(846312 ,F846312, "柜台充值", "wj", 1)
	INSERT_FUNCTION(846314 ,F846314, "柜台支取", "wj", 1)
	INSERT_FUNCTION(846315 ,F846315, "交易冲正", "wj", 1)
	INSERT_FUNCTION(846316 ,F846316, "充值冲正", "wj", 1)
	INSERT_FUNCTION(846317 ,F846317, "消费冲正", "wj", 1)
	INSERT_FUNCTION(846331 ,F846331, "电子帐户开户", "wj", 1)
	INSERT_FUNCTION(846332 ,F846332, "电子帐户销户", "wj", 1)
	INSERT_FUNCTION(846333 ,F846333, "电子帐户充值", "wj", 1)
	INSERT_FUNCTION(846334 ,F846334, "电子帐户取款", "wj", 1)
	INSERT_FUNCTION(846335 ,F846335, "电子帐户止付解付", "wj", 1)
	INSERT_FUNCTION(846336 ,F846336, "电子钱包转账", "wj", 1)
	INSERT_FUNCTION(846337 ,F846337, "电子钱包密码修改", "wj", 1)
	INSERT_FUNCTION(846338 ,F846338, "电子钱包密码重置", "wj", 1)
	INSERT_FUNCTION(846401 ,F846401, "POS流水文件导入", "wj", 1)
	INSERT_FUNCTION(846402 ,F846402, "POS流水录入增删改查", "wj", 1)	
	INSERT_FUNCTION(846403 ,F846403, "POS流水录入审核", "wj", 1)	
	INSERT_FUNCTION(847110 ,F847110, "卡信息更新查询", "wj", 1)
	INSERT_FUNCTION(847111 ,F847111, "卡密码修改", "wj", 1)
	INSERT_FUNCTION(847127 ,F847127, "手工借贷", "wj", 1)
	INSERT_FUNCTION(847130 ,F847130, "补助信息导入", "wj", 1)
	INSERT_FUNCTION(847131 ,F847131, "补助信息查询", "wj", 1)
	INSERT_FUNCTION(847150 ,F847150, "帐户查询", "wj", 1)
	INSERT_FUNCTION(847132 ,F847132, "下发补助", "wj", 1)
	INSERT_FUNCTION(847166 ,F847166, "消费机与LANPORT查询", "wj", 1)
	INSERT_FUNCTION(847173 ,F847173, "卡信息查询", "wj", 1)
	INSERT_FUNCTION(847185 ,F847185, "圈存补帐", "wj", 1)
	INSERT_FUNCTION(847198 ,F847198, "收费类别配置", "wj", 1)
	INSERT_FUNCTION(847226 ,F847226, "发行授权卡", "wj", 1)
	INSERT_FUNCTION(847227 ,F847227, "回收授权卡", "wj", 1)
	INSERT_FUNCTION(847228 ,F847228, "回收授权卡", "wj", 1)
	INSERT_FUNCTION(847229 ,F847229, "回收授权卡", "wj", 1)
	INSERT_FUNCTION(847230 ,F847230, "回收授权卡", "wj", 1)
	INSERT_FUNCTION(847231 ,F847231, "回收授权卡", "wj", 1)
	INSERT_FUNCTION(848250 ,F848250, "门禁时间段管理", "wj", 1)
	INSERT_FUNCTION(848251 ,F848251, "门禁时间段管理", "wj", 1)
	INSERT_FUNCTION(848252 ,F848252, "门禁时间段管理", "wj", 1)
	INSERT_FUNCTION(848254 ,F848254, "门禁时间段明细查询", "wj", 1)
	INSERT_FUNCTION(848255 ,F848255, "门禁节假日管理", "wj", 1)
	INSERT_FUNCTION(848256 ,F848256, "门禁时间段管理", "wj", 1)
	INSERT_FUNCTION(848257 ,F848257, "门禁组管理", "wj", 1)
	INSERT_FUNCTION(848258 ,F848258, "门禁组门禁机管理", "wj", 1)
	INSERT_FUNCTION(847232 ,F847232, "通用前置机参数设置", "wj", 1)
	INSERT_FUNCTION(849020 ,F849020, "客户银行卡绑定设置", "wj", 1)
	INSERT_FUNCTION(849021 ,F849021, "客户银行卡文件导入", "wj", 1)
	INSERT_FUNCTION(940005 ,F940005, "子系统名单同步查询", "wj", 1)
	//===============================================
	/*
	*/
	/* 门禁功能号定义 */
	/********************************/
//	INSERT_FUNCTION(849020 ,F849020, "xxx", "tc", 1)
//	INSERT_FUNCTION(849021 ,F849021, "xxx", "tc", 1)
	

	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
