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
int F240012(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
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
int F820111(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820112(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820113(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820114(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820122(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820123(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820124(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820131(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820132(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820133(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820134(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820141(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820142(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820143(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820144(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820151(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820152(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820153(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820154(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820303(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820304(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820311(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820312(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820321(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820322(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820341(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820342(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820352(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820353(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820354(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820355(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820356(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820402(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820403(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820404(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820405(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820501(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820502(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820511(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820512(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820516(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820521(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820522(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820704(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F820705(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841303(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841304(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841305(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841306(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841307(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841601(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841602(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841603(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F841604(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
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
int F842002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842501(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842502(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842503(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842504(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F842505(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843337(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843338(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843339(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843340(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843341(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843342(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843350(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843352(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843353(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843354(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
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
int F843372(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843373(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843374(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843375(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843376(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F843377(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847106(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847107(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847108(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847109(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847110(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847111(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847115(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847116(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847118(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847119(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847120(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847122(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847123(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847124(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847125(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847126(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847130(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847131(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847132(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847151(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847152(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847153(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847154(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847155(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847156(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847159(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847160(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847161(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847162(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847163(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847164(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847165(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847166(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847168(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847170(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847171(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847172(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847173(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847174(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847180(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847181(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847182(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847183(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847184(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847185(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847190(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847191(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847192(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847193(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847195(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847196(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847197(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847198(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847220(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847221(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847222(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847223(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847224(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847225(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847226(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847227(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847228(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847229(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847230(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847231(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847232(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847233(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847234(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847304(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847306(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847310(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847311(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847312(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847313(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847315(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847316(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847317(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847318(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847322(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847325(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847326(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847327(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847328(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
/*
int F848001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F848003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848012(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848013(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848014(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848015(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848016(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848017(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848018(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
*/

/* 门禁后台功能号定义 */
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
int F848264(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848265(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848266(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848267(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848268(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848269(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848270(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848271(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848272(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F848273(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
/**************************************************************************/
int F849003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F849021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900088(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900120(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900122(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900130(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900140(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900170(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900171(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900172(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900173(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900174(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900175(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900176(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900210(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900212(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900220(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900230(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900240(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900250(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900260(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900270(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900272(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900273(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900274(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900280(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900281(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900285(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900290(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900291(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900300(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900310(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F900320(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930012(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930013(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930014(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930015(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930016(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930017(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930018(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930019(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930022(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930030(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930032(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930033(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930034(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930035(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930036(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930037(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930038(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930039(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930040(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930041(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930042(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930045(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930046(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930047(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930051(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930052(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930053(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930054(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930055(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930056(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930057(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930058(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930060(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930061(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930062(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930063(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930064(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930065(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930066(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930067(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930070(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930071(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930098(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930099(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F940001(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940002(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940003(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940004(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940005(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940010(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int F940011(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930106(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930109(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930110(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930113(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930114(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930118(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930120(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930122(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930123(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930124(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930201(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930202(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F930203(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
// 通用前置机功能
int F950001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950029(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950040(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950041(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950043(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950080(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950099(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950100(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950998(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F950999(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

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
	INSERT_FUNCTION(240012 ,F240012, "xxx", "lx", 1)
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
	INSERT_FUNCTION(820111 ,F820111, "xxx", "wj", 1)
	INSERT_FUNCTION(820112 ,F820112, "xxx", "wj", 1)
	INSERT_FUNCTION(820113 ,F820113, "xxx", "wj", 1)
	INSERT_FUNCTION(820114 ,F820114, "xxx", "wj", 1)
	INSERT_FUNCTION(820121 ,F820121, "设备物理信息表注册", "hxz", 1)
	INSERT_FUNCTION(820122 ,F820122, "设备物理信息表修改", "hxz", 1)
	INSERT_FUNCTION(820123 ,F820123, "设备物理信息表删除", "hxz", 1)
	INSERT_FUNCTION(820124 ,F820124, "设备物理信息表关键字查询", "hxz", 1)
	INSERT_FUNCTION(820131 ,F820131, "卡物理结构信息表注册", "hxz", 1)
	INSERT_FUNCTION(820132 ,F820132, "卡物理结构信息表修改", "hxz", 1)
	INSERT_FUNCTION(820133 ,F820133, "卡物理结构信息表删除", "hxz", 1)
	INSERT_FUNCTION(820134 ,F820134, "卡物理结构信息表关键字查询", "hxz", 1)
	INSERT_FUNCTION(820141 ,F820141, "卡物理结构信息表注册", "hxz", 1)
	INSERT_FUNCTION(820142 ,F820142, "卡物理结构信息表修改", "hxz", 1)
	INSERT_FUNCTION(820143 ,F820143, "卡物理结构信息表删除", "hxz", 1)
	INSERT_FUNCTION(820144 ,F820144, "卡物理结构信息表关键字查询", "hxz", 1)
	INSERT_FUNCTION(820151 ,F820151, "卡物理结构信息表注册", "hxz", 1)
	INSERT_FUNCTION(820152 ,F820152, "卡物理结构信息表修改", "hxz", 1)
	INSERT_FUNCTION(820153 ,F820153, "卡物理结构信息表删除", "hxz", 1)
	INSERT_FUNCTION(820154 ,F820154, "卡物理结构信息表关键字查询", "hxz", 1)
	INSERT_FUNCTION(820301 ,F820301, "xxx", "wj", 1)
	INSERT_FUNCTION(820302 ,F820302, "xxx", "wj", 1)
	INSERT_FUNCTION(820303 ,F820303, "xxx", "wj", 1)
	INSERT_FUNCTION(820304 ,F820304, "xxx", "wj", 1)
	INSERT_FUNCTION(820311 ,F820311, "xxx", "wj", 1)
	INSERT_FUNCTION(820312 ,F820312, "xxx", "wj", 1)
	INSERT_FUNCTION(820321 ,F820321, "xxx", "wj", 1)
	INSERT_FUNCTION(820322 ,F820322, "xxx", "wj", 1)
	INSERT_FUNCTION(820331 ,F820331, "xxx", "wj", 1)
	INSERT_FUNCTION(820332 ,F820332, "xxx", "wj", 1)
	INSERT_FUNCTION(820341 ,F820341, "xxx", "wj", 1)
	INSERT_FUNCTION(820342 ,F820342, "xxx", "wj", 1)
	INSERT_FUNCTION(820351 ,F820351, "xxx", "wj", 1)
	INSERT_FUNCTION(820352 ,F820352, "xxx", "wj", 1)
	INSERT_FUNCTION(820353 ,F820353, "xxx", "wj", 1)
	INSERT_FUNCTION(820354 ,F820354, "xxx", "tc", 1)
	INSERT_FUNCTION(820355 ,F820355, "xxx", "tc", 1)
	INSERT_FUNCTION(820356 ,F820356, "xxx", "tc", 1)
	INSERT_FUNCTION(820401 ,F820401, "xxx", "wj", 1)
	INSERT_FUNCTION(820402 ,F820402, "xxx", "wj", 1)
	INSERT_FUNCTION(820403 ,F820403, "xxx", "wj", 1)
	INSERT_FUNCTION(820404 ,F820404, "xxx", "wj", 1)
	INSERT_FUNCTION(820405 ,F820405, "xxx", "wj", 1)
	INSERT_FUNCTION(820501 ,F820501, "xxx", "wj", 1)
	INSERT_FUNCTION(820502 ,F820502, "xxx", "wj", 1)
	INSERT_FUNCTION(820511 ,F820511, "xxx", "wj", 1)
	INSERT_FUNCTION(820512 ,F820512, "xxx", "wj", 1)
	INSERT_FUNCTION(820516 ,F820516, "xxx", "wj", 1)
	INSERT_FUNCTION(820521 ,F820521, "xxx", "wj", 1)
	INSERT_FUNCTION(820522 ,F820522, "xxx", "wj", 1)
	INSERT_FUNCTION(820601 ,F820601, "xxx", "gg", 1)
	INSERT_FUNCTION(820704 ,F820704, "xxx", "wj", 1)
	INSERT_FUNCTION(820705 ,F820705, "xxx", "wj", 1)
	INSERT_FUNCTION(841001 ,F841001, "xxx", "wj", 1)
	INSERT_FUNCTION(841003 ,F841003, "xxx", "wj", 1)
	INSERT_FUNCTION(841004 ,F841004, "xxx", "wj", 1)
	INSERT_FUNCTION(841005 ,F841005, "xxx", "wj", 1)
	INSERT_FUNCTION(841006 ,F841006, "xxx", "wj", 1)
	INSERT_FUNCTION(841007 ,F841007, "xxx", "wj", 1)
	INSERT_FUNCTION(841301 ,F841301, "xxx", "wj", 1)
	INSERT_FUNCTION(841303 ,F841303, "xxx", "wj", 1)
	INSERT_FUNCTION(841304 ,F841304, "xxx", "wj", 1)
	INSERT_FUNCTION(841305 ,F841305, "xxx", "wj", 1)
	INSERT_FUNCTION(841306 ,F841306, "xxx", "wj", 1)
	INSERT_FUNCTION(841307 ,F841307, "xxx", "wj", 1)
	INSERT_FUNCTION(841601 ,F841601, "xxx", "wj", 1)
	INSERT_FUNCTION(841602 ,F841602, "xxx", "wj", 1)
	INSERT_FUNCTION(841603 ,F841603, "xxx", "wj", 1)
	INSERT_FUNCTION(841604 ,F841604, "xxx", "wj", 1)
	INSERT_FUNCTION(841605 ,F841605, "xxx", "wj", 1)
	INSERT_FUNCTION(841606 ,F841606, "xxx", "wj", 1)
	INSERT_FUNCTION(841607 ,F841607, "xxx", "wj", 1)
	INSERT_FUNCTION(841608 ,F841608, "xxx", "wj", 1)
	INSERT_FUNCTION(841611 ,F841611, "xxx", "wj", 1)
	INSERT_FUNCTION(841612 ,F841612, "xxx", "wj", 1)
	INSERT_FUNCTION(841613 ,F841613, "xxx", "wj", 1)
	INSERT_FUNCTION(841614 ,F841614, "xxx", "wj", 1)
	INSERT_FUNCTION(841700 ,F841700, "xxx", "lx", 1)
	INSERT_FUNCTION(842001 ,F842001, "xxx", "wj", 1)
	INSERT_FUNCTION(842002 ,F842002, "xxx", "wj", 1)
	INSERT_FUNCTION(842003 ,F842003, "xxx", "wj", 1)
	INSERT_FUNCTION(842004 ,F842004, "xxx", "wj", 1)
	INSERT_FUNCTION(842005 ,F842005, "xxx", "wj", 1)
	INSERT_FUNCTION(842501 ,F842501, "xxx", "wj", 1)
	INSERT_FUNCTION(842502 ,F842502, "xxx", "wj", 1)
	INSERT_FUNCTION(842503 ,F842503, "xxx", "wj", 1)
	INSERT_FUNCTION(842504 ,F842504, "xxx", "wj", 1)
	INSERT_FUNCTION(842505 ,F842505, "xxx", "wj", 1)
	INSERT_FUNCTION(843335 ,F843335, "xxx", "wj", 1)
	INSERT_FUNCTION(843336 ,F843336, "xxx", "wj", 1)
	INSERT_FUNCTION(843337 ,F843337, "xxx", "wj", 1)
	INSERT_FUNCTION(843338 ,F843338, "xxx", "wj", 1)
	INSERT_FUNCTION(843339 ,F843339, "xxx", "wj", 1)
	INSERT_FUNCTION(843340 ,F843340, "xxx", "wj", 1)
	INSERT_FUNCTION(843341 ,F843341, "xxx", "wj", 1)
	INSERT_FUNCTION(843342 ,F843342, "xxx", "wj", 1)
	INSERT_FUNCTION(843350 ,F843350, "xxx", "wj", 1)
	INSERT_FUNCTION(843351 ,F843351, "xxx", "wj", 1)
	INSERT_FUNCTION(843352 ,F843352, "xxx", "wj", 1)
	INSERT_FUNCTION(843353 ,F843353, "xxx", "wj", 1)
	INSERT_FUNCTION(843354 ,F843354, "xxx", "wj", 1)
	INSERT_FUNCTION(843355 ,F843355, "xxx", "wj", 1)
	INSERT_FUNCTION(843356 ,F843356, "xxx", "wj", 1)	
	INSERT_FUNCTION(843357 ,F843357, "xxx", "wj", 1)
	INSERT_FUNCTION(843358 ,F843358, "xxx", "wj", 1)
	INSERT_FUNCTION(843359 ,F843359, "xxx", "wj", 1)
	INSERT_FUNCTION(843360 ,F843360, "xxx", "wj", 1)
	INSERT_FUNCTION(843361 ,F843361, "xxx", "wj", 1)
	INSERT_FUNCTION(843362 ,F843362, "xxx", "wj", 1)
	INSERT_FUNCTION(843363 ,F843363, "xxx", "wj", 1)
	INSERT_FUNCTION(843364 ,F843364, "xxx", "wj", 1)
	INSERT_FUNCTION(843368 ,F843368, "xxx", "wj", 1)
	INSERT_FUNCTION(843369 ,F843369, "xxx", "wj", 1)
	INSERT_FUNCTION(843370 ,F843370, "xxx", "wj", 1)
	INSERT_FUNCTION(843371 ,F843371, "xxx", "wj", 1)
	INSERT_FUNCTION(843372 ,F843372, "xxx", "wj", 1)
	INSERT_FUNCTION(843373 ,F843373, "xxx", "wj", 1)
	INSERT_FUNCTION(843374 ,F843374, "xxx", "wj", 1)
	INSERT_FUNCTION(843375 ,F843375, "xxx", "wj", 1)
	INSERT_FUNCTION(843376 ,F843376, "xxx", "wj", 1)
	INSERT_FUNCTION(843377 ,F843377, "xxx", "wj", 1)
	INSERT_FUNCTION(847101 ,F847101, "xxx", "wj", 1)
	INSERT_FUNCTION(847102 ,F847102, "xxx", "wj", 1)
	INSERT_FUNCTION(847103 ,F847103, "xxx", "wj", 1)
	INSERT_FUNCTION(847104 ,F847104, "xxx", "wj", 1)
	INSERT_FUNCTION(847105 ,F847105, "xxx", "wj", 1)
	INSERT_FUNCTION(847106 ,F847106, "xxx", "wj", 1)
	INSERT_FUNCTION(847107 ,F847107, "xxx", "wj", 1)
	INSERT_FUNCTION(847108 ,F847108, "xxx", "wj", 1)
	INSERT_FUNCTION(847109 ,F847109, "xxx", "wj", 1)
	INSERT_FUNCTION(847110 ,F847110, "xxx", "wj", 1)
	INSERT_FUNCTION(847111 ,F847111, "xxx", "wj", 1)
	INSERT_FUNCTION(847115 ,F847115, "xxx", "wj", 1)
	INSERT_FUNCTION(847116 ,F847116, "xxx", "wj", 1)
	INSERT_FUNCTION(847117 ,F847117, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847118 ,F847118, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847119 ,F847119, "xxx", "wj", 1)
	INSERT_FUNCTION(847120 ,F847120, "xxx", "wj", 1)
	INSERT_FUNCTION(847121 ,F847121, "xxx", "wj", 1)
	INSERT_FUNCTION(847122 ,F847122, "xxx", "wj", 1)
	INSERT_FUNCTION(847123 ,F847123, "xxx", "wj", 1)
	INSERT_FUNCTION(847124 ,F847124, "xxx", "wj", 1)
	INSERT_FUNCTION(847125 ,F847125, "xxx", "wj", 1)
	INSERT_FUNCTION(847126 ,F847126, "xxx", "wj", 1)
	INSERT_FUNCTION(847127 ,F847127, "xxx", "wj", 1)
	INSERT_FUNCTION(847130 ,F847130, "xxx", "wj", 1)
	INSERT_FUNCTION(847131 ,F847131, "xxx", "wj", 1)
	INSERT_FUNCTION(847132 ,F847132, "xxx", "wj", 1)
	INSERT_FUNCTION(847150 ,F847150, "xxx", "wj", 1)
	INSERT_FUNCTION(847151 ,F847151, "xxx", "wj", 1)
	INSERT_FUNCTION(847152 ,F847152, "xxx", "wj", 1)
	INSERT_FUNCTION(847153 ,F847153, "xxx", "wj", 1)
	INSERT_FUNCTION(847154 ,F847154, "xxx", "wj", 1)
	INSERT_FUNCTION(847155 ,F847155, "xxx", "wj", 1)
	INSERT_FUNCTION(847156 ,F847156, "xxx", "wj", 1)
	INSERT_FUNCTION(847159 ,F847159, "xxx", "wj", 1)
	INSERT_FUNCTION(847160 ,F847160, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847161 ,F847161, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847162 ,F847162, "xxx", "wj", 1)
	INSERT_FUNCTION(847163 ,F847163, "xxx", "wj", 1)
	INSERT_FUNCTION(847164 ,F847164, "xxx", "wj", 1)
	INSERT_FUNCTION(847165 ,F847165, "xxx", "wj", 1)
	INSERT_FUNCTION(847166 ,F847166, "xxx", "wj", 1)
	INSERT_FUNCTION(847168 ,F847168, "xxx", "wj", 1)
	INSERT_FUNCTION(847170 ,F847170, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847171 ,F847171, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847172 ,F847172, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847173 ,F847173, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847174 ,F847174, "取系统日期", "hxz", 1)
	INSERT_FUNCTION(847180 ,F847180, "xxx", "hxz", 1)
	INSERT_FUNCTION(847181 ,F847181, "xxx", "hxz", 1)
	INSERT_FUNCTION(847182 ,F847182, "xxx", "hxz", 1)
	INSERT_FUNCTION(847183 ,F847183, "xxx", "hxz", 1)
	INSERT_FUNCTION(847184 ,F847184, "xxx", "hxz", 1)
	INSERT_FUNCTION(847185 ,F847185, "xxx", "hxz", 1)
	INSERT_FUNCTION(847190 ,F847190, "xxx", "hxz", 1)
	INSERT_FUNCTION(847191 ,F847191, "xxx", "hxz", 1)
	INSERT_FUNCTION(847192 ,F847192, "xxx", "hxz", 1)
	INSERT_FUNCTION(847193 ,F847193, "xxx", "hxz", 1)
	INSERT_FUNCTION(847195 ,F847195, "xxx", "hxz", 1)
	INSERT_FUNCTION(847196 ,F847196, "xxx", "hxz", 1)
	INSERT_FUNCTION(847197 ,F847197, "xxx", "hxz", 1)
	INSERT_FUNCTION(847198 ,F847198, "xxx", "hxz", 1)
	INSERT_FUNCTION(847220 ,F847220, "xxx", "tc", 1)
	INSERT_FUNCTION(847221 ,F847221, "xxx", "tc", 1)
	INSERT_FUNCTION(847222 ,F847222, "xxx", "tc", 1)
	INSERT_FUNCTION(847223 ,F847223, "xxx", "tc", 1)
	INSERT_FUNCTION(847224 ,F847224, "xxx", "tc", 1)
	INSERT_FUNCTION(847225 ,F847225, "xxx", "tc", 1)
	INSERT_FUNCTION(847226 ,F847226, "xxx", "tc", 1)
	INSERT_FUNCTION(847227 ,F847227, "xxx", "tc", 1)
	INSERT_FUNCTION(847228 ,F847228, "xxx", "tc", 1)
	INSERT_FUNCTION(847229 ,F847229, "xxx", "tc", 1)
	INSERT_FUNCTION(847230 ,F847230, "xxx", "tc", 1)
	INSERT_FUNCTION(847231 ,F847231, "xxx", "tc", 1)
	INSERT_FUNCTION(847232 ,F847232, "xxx", "tc", 1)
	INSERT_FUNCTION(847233 ,F847233, "xxx", "tc", 1)
	INSERT_FUNCTION(847234 ,F847234, "xxx", "tc", 1)
	INSERT_FUNCTION(847301 ,F847301, "水控转账", "lx", 1)
	INSERT_FUNCTION(847302 ,F847302, "转账失败", "lx", 1)
	INSERT_FUNCTION(847304 ,F847304, "转账写卡失败", "lx", 1)
	INSERT_FUNCTION(847306 ,F847306, "水控汇总金额入账", "lx", 1)
	INSERT_FUNCTION(847310 ,F847310, "xxx", "tc", 1)
	INSERT_FUNCTION(847311 ,F847311, "xxx", "tc", 1)
	INSERT_FUNCTION(847312 ,F847312, "xxx", "hxz", 1)
	INSERT_FUNCTION(847313 ,F847313, "xxx", "hxz", 1)
	INSERT_FUNCTION(847315 ,F847315, "xxx", "hxz", 1)
	INSERT_FUNCTION(847316 ,F847316, "xxx", "hlq", 1)
	INSERT_FUNCTION(847317 ,F847317, "xxx", "hlq", 1)
	INSERT_FUNCTION(847318 ,F847318, "xxx", "tc", 1)
	INSERT_FUNCTION(847322 ,F847322, "xxx", "hlq", 1)
	INSERT_FUNCTION(847325 ,F847325, "xxx", "lx", 1)
	INSERT_FUNCTION(847326 ,F847326, "xxx", "lx", 1)
	INSERT_FUNCTION(847327 ,F847327, "xxx", "lx", 1)
	INSERT_FUNCTION(847328 ,F847328, "xxx", "lx", 1)
	INSERT_FUNCTION(847331 ,F847331, "xxx", "lx", 1)
	INSERT_FUNCTION(847332 ,F847332, "xxx", "lx", 1)
	/*
	INSERT_FUNCTION(848001 ,F848001, "xxx", "tc", 1)
	INSERT_FUNCTION(848002 ,F848002, "xxx", "tc", 1)
	INSERT_FUNCTION(848003 ,F848003, "xxx", "hxz", 1)
	INSERT_FUNCTION(848004 ,F848004, "xxx", "hxz", 1)
	INSERT_FUNCTION(848005 ,F848005, "xxx", "tc", 1)
	INSERT_FUNCTION(848006 ,F848006, "xxx", "hxz", 1)
	INSERT_FUNCTION(848007 ,F848007, "xxx", "hxz", 1)
	INSERT_FUNCTION(848008 ,F848008, "xxx", "hxz", 1)
	INSERT_FUNCTION(848009 ,F848009, "xxx", "tc", 1)
	INSERT_FUNCTION(848010 ,F848010, "xxx", "tc", 1)
	INSERT_FUNCTION(848011 ,F848011, "xxx", "tc", 1)
	INSERT_FUNCTION(848012 ,F848012, "xxx", "tc", 1)
	INSERT_FUNCTION(848013 ,F848013, "xxx", "tc", 1)
	INSERT_FUNCTION(848014 ,F848014, "xxx", "tc", 1)
	INSERT_FUNCTION(848015 ,F848015, "xxx", "tc", 1)
	INSERT_FUNCTION(848016 ,F848016, "xxx", "tc", 1)
	INSERT_FUNCTION(848017 ,F848017, "xxx", "tc", 1)
	INSERT_FUNCTION(848018 ,F848018, "xxx", "tc", 1)
	INSERT_FUNCTION(848020 ,F848020, "xxx", "tc", 1)
	*/
	/* 门禁功能号定义 */
	INSERT_FUNCTION(848250 ,F848250, "xxx", "tc", 1)
	INSERT_FUNCTION(848251 ,F848251, "xxx", "tc", 1)
	INSERT_FUNCTION(848252 ,F848252, "xxx", "tc", 1)
	INSERT_FUNCTION(848254 ,F848254, "xxx", "tc", 1)
	INSERT_FUNCTION(848255 ,F848255, "xxx", "tc", 1)
	INSERT_FUNCTION(848256 ,F848256, "xxx", "tc", 1)
	INSERT_FUNCTION(848257 ,F848257, "xxx", "tc", 1)
	INSERT_FUNCTION(848258 ,F848258, "xxx", "tc", 1)
	INSERT_FUNCTION(848259 ,F848259, "xxx", "tc", 1)
	INSERT_FUNCTION(848260 ,F848260, "xxx", "tc", 1)
	INSERT_FUNCTION(848264 ,F848264, "xxx", "tc", 1)
	INSERT_FUNCTION(848265 ,F848265, "xxx", "tc", 1)
	INSERT_FUNCTION(848266 ,F848266, "xxx", "tc", 1)
	INSERT_FUNCTION(848267 ,F848267, "xxx", "tc", 1)
	INSERT_FUNCTION(848268 ,F848268, "xxx", "tc", 1)
	INSERT_FUNCTION(848269, F848269, "xxx", "tc", 1)
	INSERT_FUNCTION(848270, F848270, "xxx", "tc", 1)
	INSERT_FUNCTION(848271, F848271, "xxx", "tc", 1)
	INSERT_FUNCTION(848272, F848272, "xxx", "tc", 1)
	INSERT_FUNCTION(848273, F848273, "xxx", "tc", 1)
	/********************************/
	INSERT_FUNCTION(849003 ,F849003, "xxx", "tc", 1)
	INSERT_FUNCTION(849004 ,F849004, "xxx", "tc", 1)
	INSERT_FUNCTION(849005 ,F849005, "xxx", "tc", 1)
	INSERT_FUNCTION(849006 ,F849006, "xxx", "tc", 1)
	INSERT_FUNCTION(849007 ,F849007, "xxx", "tc", 1)
	INSERT_FUNCTION(849008 ,F849008, "xxx", "tc", 1)
	INSERT_FUNCTION(849009 ,F849009, "xxx", "tc", 1)
	INSERT_FUNCTION(849010 ,F849010, "xxx", "tc", 1)
	INSERT_FUNCTION(849020 ,F849020, "xxx", "tc", 1)
	INSERT_FUNCTION(849021 ,F849021, "xxx", "tc", 1)
	INSERT_FUNCTION(900088 ,F900088, "xxx", "wj", 1)
	INSERT_FUNCTION(900120 ,F900120, "xxx", "wj", 1)
	INSERT_FUNCTION(900121 ,F900121, "xxx", "wj", 1)
	INSERT_FUNCTION(900122 ,F900122, "xxx", "wj", 1)
	INSERT_FUNCTION(900130 ,F900130, "xxx", "wj", 1)
	INSERT_FUNCTION(900140 ,F900140, "xxx", "wj", 1)
	INSERT_FUNCTION(900150 ,F900150, "xxx", "wj", 1)
	INSERT_FUNCTION(900170 ,F900170, "xxx", "wj", 1)
	INSERT_FUNCTION(900171 ,F900171, "xxx", "wj", 1)
	INSERT_FUNCTION(900172 ,F900172, "songjiang", "tc", 1)
	INSERT_FUNCTION(900173 ,F900173, "songjiang", "tc", 1)
	INSERT_FUNCTION(900174 ,F900174, "songjiang", "tc", 1)
	INSERT_FUNCTION(900175 ,F900175, "songjiang", "tc", 1)
	INSERT_FUNCTION(900176 ,F900176, "songjiang", "tc", 1)
	INSERT_FUNCTION(900210 ,F900210, "xxx", "wj", 1)
	INSERT_FUNCTION(900212 ,F900212, "xxx", "wj", 1)
	INSERT_FUNCTION(900220 ,F900220, "xxx", "wj", 1)
	INSERT_FUNCTION(900230 ,F900230, "xxx", "wj", 1)
	INSERT_FUNCTION(900240 ,F900240, "xxx", "wj", 1)
	INSERT_FUNCTION(900250 ,F900250, "xxx", "wj", 1)
	INSERT_FUNCTION(900260 ,F900260, "xxx", "wj", 1)
	INSERT_FUNCTION(900270 ,F900270, "xxx", "wj", 1)
	INSERT_FUNCTION(900272 ,F900272, "xxx", "wj", 1)
	INSERT_FUNCTION(900273 ,F900273, "xxx", "wj", 1)
	INSERT_FUNCTION(900274 ,F900274, "xxx", "wj", 1)
	INSERT_FUNCTION(900280 ,F900280, "xxx", "wj", 1)
	INSERT_FUNCTION(900281 ,F900281, "xxx", "wj", 1)
	INSERT_FUNCTION(900285 ,F900285, "xxx", "wj", 1)
	INSERT_FUNCTION(900290 ,F900290, "xxx", "wj", 1)
	INSERT_FUNCTION(900291 ,F900291, "xxx", "wj", 1)
	INSERT_FUNCTION(900300 ,F900300, "xxx", "wj", 1)
	INSERT_FUNCTION(900310 ,F900310, "xxx", "wj", 1)
	INSERT_FUNCTION(900320 ,F900320, "xxx", "wj", 1)
	INSERT_FUNCTION(930001 ,F930001, "xxx", "wj", 1)
	INSERT_FUNCTION(930002 ,F930002, "xxx", "wj", 1)
	INSERT_FUNCTION(930003 ,F930003, "xxx", "wj", 1)
	INSERT_FUNCTION(930004 ,F930004, "xxx", "wj", 1)
	INSERT_FUNCTION(930005 ,F930005, "xxx", "wj", 1)
	INSERT_FUNCTION(930006 ,F930006, "xxx", "wj", 1)
	INSERT_FUNCTION(930007 ,F930007, "xxx", "wj", 1)
	INSERT_FUNCTION(930008 ,F930008, "xxx", "wj", 1)
	INSERT_FUNCTION(930009 ,F930009, "xxx", "wj", 1)
	INSERT_FUNCTION(930010 ,F930010, "xxx", "wj", 1)
	INSERT_FUNCTION(930011 ,F930011, "xxx", "wj", 1)
	INSERT_FUNCTION(930012 ,F930012, "xxx", "wj", 1)
	INSERT_FUNCTION(930013 ,F930013, "xxx", "wj", 1)
	INSERT_FUNCTION(930014 ,F930014, "xxx", "wj", 1)
	INSERT_FUNCTION(930015 ,F930015, "xxx", "wj", 1)
	INSERT_FUNCTION(930016 ,F930016, "xxx", "wj", 1)
	INSERT_FUNCTION(930017 ,F930017, "xxx", "wj", 1)
	INSERT_FUNCTION(930018 ,F930018, "xxx", "wj", 1)
	INSERT_FUNCTION(930019 ,F930019, "xxx", "wj", 1)
	INSERT_FUNCTION(930020 ,F930020, "xxx", "wj", 1)
	INSERT_FUNCTION(930021 ,F930021, "xxx", "wj", 1)
	INSERT_FUNCTION(930022 ,F930022, "xxx", "wj", 1)
	INSERT_FUNCTION(930030 ,F930030, "xxx", "lx", 1)
	INSERT_FUNCTION(930031 ,F930031, "xxx", "wj", 1)
	INSERT_FUNCTION(930032 ,F930032, "xxx", "wj", 1)
	INSERT_FUNCTION(930033 ,F930033, "xxx", "wj", 1)
	INSERT_FUNCTION(930034 ,F930034, "xxx", "wj", 1)
	INSERT_FUNCTION(930035 ,F930035, "xxx", "wj", 1)
	INSERT_FUNCTION(930036 ,F930036, "xxx", "wj", 1)
	INSERT_FUNCTION(930037 ,F930037, "xxx", "wj", 1)
	INSERT_FUNCTION(930038 ,F930038, "xxx", "wj", 1)
	INSERT_FUNCTION(930039 ,F930039, "xxx", "wj", 1)
	INSERT_FUNCTION(930040 ,F930040, "xxx", "wj", 1)
	INSERT_FUNCTION(930041 ,F930041, "xxx", "wj", 1)
	INSERT_FUNCTION(930042 ,F930042, "xxx", "wj", 1)
	INSERT_FUNCTION(930045 ,F930045, "xxx", "wj", 1)
	INSERT_FUNCTION(930046 ,F930046, "xxx", "wj", 1)
	INSERT_FUNCTION(930047 ,F930047, "xxx", "wj", 1)
	INSERT_FUNCTION(930051 ,F930051, "xxx", "wj", 1)
	INSERT_FUNCTION(930052 ,F930052, "xxx", "wj", 1)
	INSERT_FUNCTION(930053 ,F930053, "xxx", "wj", 1)
	INSERT_FUNCTION(930054 ,F930054, "xxx", "wj", 1)
	INSERT_FUNCTION(930055 ,F930055, "xxx", "wj", 1)
	INSERT_FUNCTION(930056 ,F930056, "xxx", "wj", 1)
	INSERT_FUNCTION(930057 ,F930057, "xxx", "wj", 1)
	INSERT_FUNCTION(930058 ,F930058, "xxx", "wj", 1)
	INSERT_FUNCTION(930060 ,F930060, "xxx", "wj", 1)
	INSERT_FUNCTION(930061 ,F930061, "xxx", "wj", 1)
	INSERT_FUNCTION(930062 ,F930062, "xxx", "wj", 1)
	INSERT_FUNCTION(930063 ,F930063, "xxx", "wj", 1)
	INSERT_FUNCTION(930064 ,F930064, "xxx", "wj", 1)
	INSERT_FUNCTION(930065 ,F930065, "xxx", "tc", 1)
	INSERT_FUNCTION(930066 ,F930066, "xxx", "tc", 1)
	INSERT_FUNCTION(930067 ,F930067, "xxx", "tc", 1)
	INSERT_FUNCTION(930070 ,F930070, "xxx", "tc", 1)
	INSERT_FUNCTION(930071 ,F930071, "xxx", "tc", 1)
	INSERT_FUNCTION(930098 ,F930098, "xxx", "wj", 1)
	INSERT_FUNCTION(930099 ,F930099, "xxx", "wj", 1)
	INSERT_FUNCTION(940001	,F940001, "xxx", "tc", 1)
	INSERT_FUNCTION(940002	,F940002, "xxx", "tc", 1)
	INSERT_FUNCTION(940003	,F940003, "xxx", "tc", 1)
	INSERT_FUNCTION(940004	,F940004, "xxx", "tc", 1)
	INSERT_FUNCTION(940005	,F940005, "xxx", "tc", 1)
	INSERT_FUNCTION(940010	,F940010, "xxx", "lx", 1)
	INSERT_FUNCTION(940011	,F940011, "xxx", "lx", 1)
	
	INSERT_FUNCTION(930101 ,F930101, "door", "wj", 1)
	INSERT_FUNCTION(930102 ,F930102, "door", "wj", 1)
	INSERT_FUNCTION(930103 ,F930103, "door", "wj", 1)
	INSERT_FUNCTION(930104 ,F930104, "door", "wj", 1)
	INSERT_FUNCTION(930105 ,F930105, "door", "wj", 1)
	INSERT_FUNCTION(930106 ,F930106, "door", "wj", 1)
	INSERT_FUNCTION(930109 ,F930109, "door", "wj", 1)
	INSERT_FUNCTION(930110 ,F930110, "door", "wj", 1)
	INSERT_FUNCTION(930113 ,F930113, "door", "wj", 1)
	INSERT_FUNCTION(930114 ,F930114, "door", "wj", 1)
	INSERT_FUNCTION(930117 ,F930117, "door", "wj", 1)
	INSERT_FUNCTION(930118 ,F930118, "door", "wj", 1)
	INSERT_FUNCTION(930120 ,F930120, "door", "wj", 1)
	INSERT_FUNCTION(930121 ,F930121, "door", "tc", 1)
	INSERT_FUNCTION(930122 ,F930122, "door", "tc", 1)
	INSERT_FUNCTION(930123 ,F930123, "door", "tc", 1)
	INSERT_FUNCTION(930124 ,F930124, "sj", "tc", 1)
	INSERT_FUNCTION(930201 ,F930201, "door", "tc", 1)
	INSERT_FUNCTION(930202 ,F930202, "door", "tc", 1)
	INSERT_FUNCTION(930203 ,F930203, "door", "tc", 1)
	INSERT_FUNCTION(950001 ,F950001, "gw", "tc", 1)
	INSERT_FUNCTION(950002 ,F950002, "gw", "tc", 1)
	INSERT_FUNCTION(950003 ,F950003, "gw", "tc", 1)
	INSERT_FUNCTION(950004 ,F950004, "gw", "lx", 1)
	INSERT_FUNCTION(950005 ,F950005, "gw", "tc", 1)
	INSERT_FUNCTION(950006 ,F950006, "gw", "tc", 1)
	INSERT_FUNCTION(950007 ,F950007, "gw", "tc", 1)
	INSERT_FUNCTION(950008 ,F950008, "gw", "tc", 1)
	INSERT_FUNCTION(950009 ,F950009, "gw", "tc", 1)
	INSERT_FUNCTION(950010 ,F950010, "gw", "tc", 1)
	INSERT_FUNCTION(950029 ,F950029, "xxx", "tc", 1)
	INSERT_FUNCTION(950031 ,F950031, "gw", "tc", 1)
	INSERT_FUNCTION(950040 ,F950040, "gw", "tc", 1)
	INSERT_FUNCTION(950041 ,F950041, "gw", "tc", 1)
	INSERT_FUNCTION(950043 ,F950043, "gw", "tc", 1)
	INSERT_FUNCTION(950080 ,F950080, "gw", "tc", 1)
	INSERT_FUNCTION(950099 ,F950099, "gw", "tc", 1)
	INSERT_FUNCTION(950100 ,F950100, "gw", "tc", 1)
	INSERT_FUNCTION(950101 ,F950101, "gw", "tc", 1)
	INSERT_FUNCTION(950998 ,F950998, "download", "tc", 1)
	INSERT_FUNCTION(950999 ,F950999, "upload", "tc", 1)

	INSERT_FUNCTION(0,NULL,"END BPFunctions List","CYH Marked",0)  // the last mark line，Don't remove this line
};
#endif
