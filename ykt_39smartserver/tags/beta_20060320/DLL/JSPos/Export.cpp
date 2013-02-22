#include "stdafx.h"
#include "JSPos.h"
#include "ConfigDlg.h"

long TaskBufferProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskBufferProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskBufferProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);



//add by lina 20050309  上传时钟
long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
/////////////

//add by lina 20050316 设置每日累计消费金额上限
long TaskBufferProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 初始化LPORT端口参数
long TaskBufferProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 设置终端管理员密码
long TaskBufferProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 获取端口参数
long TaskBufferProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by dengjun 20050830 计时宝广播下传白名单
long TaskBufferProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 计时宝下传/删除白名单
long TaskBufferProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 上传计时宝版本
long TaskBufferProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 下传计时宝版本
long TaskBufferProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 上传计时宝节假日
long TaskBufferProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 下传计时宝节假日
long TaskBufferProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 上传计时宝时间段
long TaskBufferProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 下传计时宝时间段
long TaskBufferProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050831 下传计时宝时间段
long TaskBufferProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050831 下传计时宝主参数
long TaskBufferProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050901 采集计时宝历史流水
long TaskBufferProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050901 计时宝主参数
long TaskBufferProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050926 更改设备参数或增加设备
long TaskBufferProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);


//功能程序入口
static TaskFunction TaskFunc[] = 
{
	3,  "上传时钟",     TaskBufferProc03, TaskProc03,
	60, "下传补助名单", TaskBufferProc60, TaskProc60, 
	61, "上传补助名单", TaskBufferProc61, TaskProc61, 
	62, "设置补助开关", TaskBufferProc62, TaskProc62, 
	63, "读取补助开关", TaskBufferProc63, TaskProc63, 	
	80, "设置主参数",		 TaskBufferProc80, TaskProc80, 
	81, "校对主参数",		 TaskBufferProc81, TaskProc81, 
	101, "校对时钟",		 TaskBufferProc101, TaskProc101, 
	102, "下传大额消费限额", TaskBufferProc102, TaskProc102, 
	103, "网络检测",		 TaskBufferProc103, TaskProc103, 
	104, "设置消费编号及版本",TaskBufferProc104, TaskProc104, 
	105, "设置消费快捷编号", TaskBufferProc105, TaskProc105, 
	106, "设置机器ID",		 TaskBufferProc106, TaskProc106, 
	107, "设置消费时间段参数", TaskBufferProc107, TaskProc107, 
	108, "设置注册号",		 TaskBufferProc108, TaskProc108, 

	110, "防火状态设置",	 TaskBufferProc110, TaskProc110, 
	111, "防盗状态设置",	 TaskBufferProc111, TaskProc111, 
	112, "从防火防盗状态恢复正常运行状态", TaskBufferProc112, TaskProc112, 

	120, "下传搭伙费比率",	 TaskBufferProc120, TaskProc120, 
	130, "设置签到开关",     TaskBufferProc130, TaskProc130, 
	131, "设置每日累计消费限额",TaskBufferProc131, TaskProc131,
	132, "初始化LPORT端口参数",TaskBufferProc132, TaskProc132,
	133, "设置终端管理员密码",TaskBufferProc133, TaskProc133,
	134, "获取端口参数",	TaskBufferProc134, TaskProc134,
	136, "计时宝下传/删除白名单",	TaskBufferProc136, TaskProc136,	
	137, "上传计时宝版本",			TaskBufferProc137, TaskProc137,	
	138, "下传计时宝版本",			TaskBufferProc138, TaskProc138,	
	139, "上传计时宝节假日",		TaskBufferProc139, TaskProc139,	
	140, "下传计时宝节假日",		TaskBufferProc140, TaskProc140,	
	141, "上传计时宝时间段",		TaskBufferProc141, TaskProc141,	
	142, "下传计时宝时间段",		TaskBufferProc142, TaskProc142,	
	143, "门禁机开关控制",			TaskBufferProc143, TaskProc143,	
	144, "下传计时宝主参数",		TaskBufferProc144, TaskProc144,	
	145, "采集计时宝历史流水",		TaskBufferProc145, TaskProc145,	
	146, "计时宝主参数",			TaskBufferProc146, TaskProc146,	
	147, "更改设备参数或增加设备",	TaskBufferProc147, TaskProc147,	
	148, "下传补助名单",			TaskBufferProc148, TaskProc148,	
	149, "上传黑名单版本",			TaskBufferProc149, TaskProc149,	
	-1,  "", NULL, NULL 
};

//*=================================================================================
//*原型: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      lpKeyBuffer, 授权字符串(保留)
//*      dwFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*====================================================================================
extern "C" long __stdcall ReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*原型: long ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*功能: 释放设备档案信息
//*参数: 
//*      pSmartDoc -- 设备档案内存
//*返回: 
//*      =  RET_OK:  成功
//*      <> RET_OK:  失败
//*====================================================================================
extern "C" long __stdcall ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*原型: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      pFunction, 传入服务器的API地址
//*      pSupport,  传回本DLL支持的所有任务及机型
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall InitModuleDLL(TSSmartFunction *pFunction, TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//支持所有机型
    pSupport->nMacCount = 0 ;

	//支待的任务
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "60");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "61");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "62");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "63");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "80");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "81");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "100");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "101");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "102");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "103");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "104");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "105");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "106");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "107");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "108");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "110");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "111");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "112");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "120");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "130");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "131");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "132");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "133");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "134");
//	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "135"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "136"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "137"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "138"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "139"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "140"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "141"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "142"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "143"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "144"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "145"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "146"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "147"); //add by dengjun 20050926
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "148"); //add by dengjun 20050926
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "149"); //add by dengjun 20051115

	//服务器提供的API
	GetDBHandle = pFunction->fnGetDBHandle;
	FreeDBHandle = pFunction->fnFreeDBHandle;
	ExecuteQuery = pFunction->fnExecuteQuery;
	CloseRecHandle = pFunction->fnCloseRecHandle;
	IsOpen = pFunction->fnIsOpen;
	IsBOF = pFunction->fnIsBOF;
	IsEOF = pFunction->fnIsEOF;
	MoveFirst = pFunction->fnMoveFirst;
	MoveLast = pFunction->fnMoveLast;
	MoveNext = pFunction->fnMoveNext;
	MovePrev = pFunction->fnMovePrev;
	GetFieldCount = pFunction->fnGetFieldCount;
	GetRecordCount = pFunction->fnGetRecordCount;
	GetFieldName = pFunction->fnGetFieldName;
	GetFieldStringValue = pFunction->fnGetFieldStringValue;
	GetFieldStringValueEx = pFunction->fnGetFieldStringValueEx;
	GetFieldLongValue = pFunction->fnGetFieldLongValue;
	GetFieldLongValueEx = pFunction->fnGetFieldLongValueEx;
	GetFieldFloatValue = pFunction->fnGetFieldFloatValue;
	GetFieldFloatValueEx = pFunction->fnGetFieldFloatValueEx;
	GetFieldDoubleValue = pFunction->fnGetFieldDoubleValue;
	GetFieldDoubleValueEx = pFunction->fnGetFieldDoubleValueEx;
	Locate = pFunction->fnLocate;
	ExecuteSQL = pFunction->fnExecuteSQL;
	SendRequest = pFunction->fnSendRequest;
	BroadData = pFunction->fnBroadData;
	AddNewSmartDoc = pFunction->fnAddNewSmartDoc;
	DelSmartDoc = pFunction->fnDelSmartDoc;
	BroadMessage = pFunction->fnBroadMessage;
	BroadcastPro = pFunction->fnBroadcastPro;

	SendDataEx = pFunction->fnSendData;
	RecvDataEx = pFunction->fnRecvData;
	OutputRealData = pFunction->fnOutputRealData;
	GetParameter = pFunction->fnGetParam;
	ReportTaskResult = pFunction->fnReportTaskResult;

    TCHAR  szPath[MAX_PATH];
	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szDataLogPath,  "%s终端数据", szPath);
		wsprintf(szOperPath,  "%s设备日志", szPath);
	}
	else
	{
		wsprintf(szDataLogPath,  "%s\\终端数据", szPath);
		wsprintf(szOperPath,  "%s\\设备日志", szPath);
	}

	//CreateDirectory(szDataLogPath, NULL);
	CreateDirectory(szOperPath, NULL);

	return RET_OK;
}

//*=================================================================================
//*功能: 清除业务功能模块, 退出DLL时调用
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DestoryModuleDLL()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return RET_OK;
}

//*=================================================================================
//*功能: 在运行一个任务时调用, 此时它生成任务的命令包
//*参数: 
//*       pSmartDoc:     终端信息
//*       pDocArray:     终端级联数组
//*       nArrayLength:  数组项数
//*       pSmartBuffer:  返回的信息
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	long nRet = RET_NG ;
	long i=0; 

	while( TaskFunc[i].nTaskID > 0 )
	{
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{
			nRet = TaskFunc[i].fnTaskBufferProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}
	return nRet;
}

//*=================================================================================
//*功能: 从终端接收数据后的处理(实现解包, 生成SQL等)
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{ 
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	long nRet = RET_NG ;
	long i=0; 

 	while( TaskFunc[i].nTaskID > 0 )
	{
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{
			nRet = TaskFunc[i].fnTaskProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}

	return nRet;
}

//*=================================================================================
//*功能: 业务库所支持的信息
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DLLSupportInfo(TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");

	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "60");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "61");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "62");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "63");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "80");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "81");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "100");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "101");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "102");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "103");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "104");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "105");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "106");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "107");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "108");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "110");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "111");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "112");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "120");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "130");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "131");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "132");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "133");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "134");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "136"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "137"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "138"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "139"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "140"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "141"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "142"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "143"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "144"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "145"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "146"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "147"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "148"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "149"); //add by dengjun

	return RET_OK;
}

//*=================================================================================
//*功能: 业务库设置界面(现在没有使用)
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DLLSetup()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CConfigDlg  dlg;
	dlg.DoModal();

	return RET_OK;
}

long GetMemoNumber(int nIndex, char *pszText)
{
	char  szText[256];
	int   k = 0;

	memset(szText, 0, sizeof(szText));
	for(int i=0; i<(int)strlen(pszText); i++)
	{
		if( szText[i] == ' ' )
		{
			if( k++ == nIndex ) 
				break;
		}
		else
		{
			szText[i] = pszText[i];
		}
	}
	return atoi(szText);
}

long GetMemoString(int nIndex, char *pszText, char *pszResult)
{
	char  szText[256];
	int   k = 0;

	memset(szText, 0, sizeof(szText));
	for(int i=0; i<(int)strlen(pszText); i++)
	{
		if( szText[i] == ' ' )
		{
			if( k++ == nIndex ) 
			{
				strcpy(pszResult,  szText);
				break;
			}
		}
	}
	return atoi(szText);
}


long UnPassword(char *pszPass, char cFlag, unsigned char *pResult)
{
	typedef void (__stdcall *lpfnUserDes)(unsigned char *pIn, unsigned char *pOut, char cFlag);
    TCHAR  szPath[MAX_PATH];
	TCHAR  szFileName[MAX_PATH];
	lpfnUserDes  UserDes = NULL ;

	GetCurPath(szPath);
	wsprintf(szFileName, "%s\\smart_userdes.dll", szPath);

	HMODULE hInstance = LoadLibrary(szFileName);
	if( hInstance == NULL )
	{
		return RET_SYSERROR;
	}

	UserDes = (lpfnUserDes)GetProcAddress(hInstance, "Smart_UserDes");
	if( UserDes == NULL )
	{
		FreeLibrary(hInstance);
		return RET_SYSERROR;
	}

	unsigned char szInBuffer[16];

	ZeroMemory(szInBuffer, sizeof(szInBuffer));
	ZeroMemory(pResult, 16);

	if( cFlag == 'e' || cFlag == 'E' )
	{
		for(int i=0; i< (int)strlen(pszPass); i++)
			szInBuffer[i] = pszPass[i];
	    UserDes(szInBuffer, pResult, cFlag);
	}
	else
	{
		SVC_DSP_2_HEX((unsigned char*)pszPass, szInBuffer, 8);
	    UserDes(szInBuffer, pResult, cFlag);
	}

	FreeLibrary(hInstance);
	return RET_OK;
}

//波特率对照表
int GetBaudRatecode(int nBaud)
{
	int nResult = 0 ;
	switch(nBaud)
	{
	case 19200: nResult=0 ; break;
    case 9600: nResult=1 ; break;
    case 600: nResult=2 ; break;
    case 1200: nResult=3 ; break;
    case 2400: nResult=4 ; break;
    case 4800: nResult=5 ; break;
    case 14400: nResult=6 ; break;
    case 57600: nResult=7 ; break;
	default:break;
	}
	return nResult;
}

int GetBaudRatecodeEx(int nBaud)
{
	int nResult = 19200 ;
	switch(nBaud)
	{
	case 0: nResult=19200 ; break;
    case 1: nResult=9600 ; break;
    case 2: nResult=600 ; break;
    case 3: nResult=1200; break;
    case 4: nResult=24004 ; break;
    case 5: nResult=48005 ; break;
    case 6: nResult=144006 ; break;
    case 7: nResult=57600 ; break;
	default:break;
	}
	return nResult;
}


unsigned char GetInt(unsigned char *pszString, int Len)
{
   char  sBuffer[8];

   memset(sBuffer, 0, sizeof(sBuffer));
   for(int i=0; i<Len&&i<8; i++)
   {
	   sBuffer[i] = pszString[i];
   }

   return (unsigned char)atoi(sBuffer);
}


void GetNowTime(char *pszDateTime, bool bBool)
{
	SYSTEMTIME   SysTime;

	ZeroMemory(&SysTime, sizeof(SysTime));
	GetLocalTime(&SysTime);

	if( !bBool )
	{
		sprintf(pszDateTime, "%02d%02d%02d%02d%02d%02d",
			SysTime.wYear, SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	}
	else
	{
		sprintf(pszDateTime, "%02d%02d%02d", 
			SysTime.wYear, SysTime.wMonth, SysTime.wDay);
	}

	return ;
}

long OpenQuery(long nDatabase, CString strSQL)
{
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		return RET_DBQUERYERROR;
	}

	if( MoveFirst(nRec) != RET_OK )
	{
		CloseRecHandle(nRec);
		return RET_DBQUERYERROR;
	}

	return nRec;
}


CString GetSmartCardSQL(CString strDate1, CString strDate2)
{
	CString strSQL;


	return strSQL;
}

//操作是否成功
long UnMakeDeviceBufferEx(TSCmdBuffer *pBuffer)
{
	long nResult = UnMakeDeviceBuffer(pBuffer);
	if( nResult == RET_OK )
	{
		int nMark = pBuffer->pBuffer[2];
		if( nMark != 0x00 )
			nResult = nMark; 
		else
			nResult = RET_OK;
	}
	return nResult;
}

char sBlockVersion[32];   //黑名单的最新版本
char sBlockExpire[32];    //黑名单有效期
int  nBlackExpire;
int  nBlackCount = 0 ;

long GetParam(long nDatabase)
{
	CString strSQL;

	memset(sBlockVersion, 0, sizeof(sBlockVersion));
	memset(sBlockExpire, 0, sizeof(sBlockExpire));

	nBlackExpire = 24 ;

	//黑名单的最新版本
	strSQL = "select smt_content from smart_setup where smt_systemid = 93 and smt_param='StdBlackVer' ";
	long nRec = OpenQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		GetNowTime(sBlockVersion, false);
	}
	else
	{
		if( GetFieldStringValueEx(nRec, "smt_content", sBlockVersion) != RET_OK )
			GetNowTime(sBlockVersion, false);
		CloseRecHandle(nRec);
	}

	//黑名单有效期
	strSQL = "select smt_content from smart_setup where smt_systemid = 85 and smt_param='Tx_Black_Yx' ";
	nRec = OpenQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		strcpy(sBlockExpire, "");
	}
	else
	{
		if( GetFieldStringValueEx(nRec, "smt_content", sBlockExpire) != RET_OK )
			strcpy(sBlockExpire, "");
		CloseRecHandle(nRec);
	}

	if( strlen(sBlockExpire) > 0 )
	{
		char   sDateTime[24];
		char   sTemp[32];

		memset(sTemp, 0, sizeof(sTemp));

		//黑名单有效期为每天的固定时间
		if( strlen(sBlockExpire) == 6 )
		{
			GetNowTime(sDateTime, true);

			nBlackExpire = -1;
			sprintf(sTemp, "%s%s", sDateTime, sBlockExpire);
			strcpy(sBlockExpire, sTemp);
		}
		//黑名单有效期为一个固定的日期时间
		else if( strlen(sBlockExpire) >= 12 && strlen(sBlockExpire) <= 14 )
		{
			nBlackExpire = -1;

			if( strlen(sBlockExpire) == 14 )
			{
				strncpy(sTemp, &sBlockExpire[2], 12);
				strcpy(sBlockExpire, sTemp);
			}
		}
		//黑名单有效期以小时计算
		else
		{
			try
			{
				nBlackExpire = atoi(sBlockExpire);
			}
			catch(...)
			{
				nBlackExpire = 99999 ;
			}
		}
	}
	else
	{
		nBlackExpire = -1;
		strcpy(sBlockExpire, "990101010101");
	}

	return RET_OK;
}

//下载黑名单
long DownCardID(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int n, long nRec, char* strLastVer, long nCardID)
{
	const int MaxBlacknum = 1;
	const int Maxwhitenum = 1;

	long nLastList;
	long nBlacknum=0, nWhitenum=0;
	char strFirstVer[32];
	char strBlackListVer[32];
	char strEndCode[64];

	unsigned char szWhiteBuffer[256];
	unsigned char szBlackBuffer[256];

	strcpy(strLastVer, "");

	if( MoveFirst(nRec) != RET_OK )
		return RET_SYSERROR;

    nLastList = nCardID;
	GetFieldStringValueEx(nRec, "smt_blacklistver", strFirstVer);

	while( IsEOF(nRec) != RET_OK )
	{
		nWhitenum = 0 ;
		nBlacknum = 0 ;

		GetFieldLongValueEx(nRec, "smt_cardID", &nCardID);
		GetFieldStringValueEx(nRec, "smt_blacklistver", strBlackListVer);
		GetFieldStringValueEx(nRec, "smt_EndCode", strEndCode);

        //如果上次校对黑名单失败，并且有多个相同黑名版本号，则上一个校对失败的名单开始。
		if( nCardID < nLastList && !strcmp(strBlackListVer, strFirstVer) )
		{
			printf("Card ID is Error!\n");
			MoveNext(nRec);
			continue;
		}

		//白名单
		if( strEndCode[0] == '0' )
		{
			szWhiteBuffer[nWhitenum*3] = (nCardID/256/256)%256;
			szWhiteBuffer[nWhitenum*3+1] = (nCardID/256)%256;
			szWhiteBuffer[nWhitenum*3+2] = nCardID%256;
			nWhitenum++;
		}
		else
		{
			szBlackBuffer[nBlacknum*3] = (nCardID/256/256)%256;
			szBlackBuffer[nBlacknum*3+1] = (nCardID/256)%256;
			szBlackBuffer[nBlacknum*3+2] = nCardID%256;
			nBlacknum++;
		}

		MoveNext(nRec);

		//每次下传或删除最多60条名单
		if( nBlacknum == MaxBlacknum || nWhitenum == Maxwhitenum || 
			IsEOF(nRec) != RET_OK )
		{
			//下传黑名单
			if( nBlacknum )
			{
				nCardID = szBlackBuffer[0]*256*256+szBlackBuffer[1]*256+szBlackBuffer[2];
				bool bResult = false;

				for(long i=0; i<3; i++)
				{
					MakeBuf_DownBlackCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBlackBuffer);
					pBuffer->nTimeOut1 = 1000;
					pBuffer->nTimeOut2 = 1000;
					if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
					{
						long iResult = UnMakeDeviceBufferEx(pBuffer);
						if( iResult == RET_OK )
						{
							printf("Blacknum download is ok..............\n");
							bResult = true;
							break;
						}
						else
						{
							printf("Blacknum download is error...mark=%d...card:%d..\n", iResult, nCardID);
						}
					}
				}

				if( !bResult )
				{
					CloseRecHandle(nRec);
					return RET_SYSERROR;
				}
			}

			//删除黑名单
			if( nWhitenum )
			{
				printf("Loop..next ..nWhitenum......\n");

				nCardID = szWhiteBuffer[0]*256*256+szWhiteBuffer[1]*256+szWhiteBuffer[2];
				GetFieldStringValueEx(nRec, "smt_blacklistver", strBlackListVer);

	            //如果是新机，就不用册除黑名单
				if( strcmp(strBlackListVer, "000000000000") )
				{
					bool bResult = false;

					for(long i=0; i<3; i++)
					{
						MakeBuf_DelOneBlackCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szWhiteBuffer);
						pBuffer->nTimeOut1 = 1000;
						pBuffer->nTimeOut2 = 1000;
						if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
						{
							long iResult = UnMakeDeviceBufferEx(pBuffer);
							if( iResult == RET_OK )
							{
								printf("nWhitenum download is ok..............\n");
								bResult = true;
								break;
							}
							else
							{
								printf("Blacknum download is error...mark=%d...card:%d..\n", iResult, nCardID);
							}
						}
					}

					if( !bResult )
					{
						CloseRecHandle(nRec);
						return RET_SYSERROR;
					}
				}
			}
		}

		GetFieldStringValueEx(nRec, "smt_blacklistver", strLastVer);
	}

	return RET_OK;
}

//校对黑名单的有效期
long CheckBlackExpire(long nDatabase, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long n)
{
	char  sNow[24];
	char  sTemp[32];
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	char *pExpire = pDoc->m_sBlackExpire;

	GetNowTime(sNow, false);

	if( (strcmp(pExpire, "02070100") < 0 || strcmp(pExpire, sNow) > 0)
		&& strcmp(pExpire, "") )
	{
		return RET_OK;
	}

	memset(sTemp, 0, sizeof(sTemp));

	if( nBlackExpire == -1 )
	{
		strcpy(sTemp, sBlockExpire);
	}
	else
	{
		 char sDateTime[24];
	     SYSTEMTIME   SysTime;

	     ZeroMemory(&SysTime, sizeof(SysTime));
	     GetLocalTime(&SysTime);

	     sprintf(sDateTime, "%02d%02d%02d%02d%02d%02d",
		     SysTime.wYear, SysTime.wMonth, SysTime.wDay+nBlackExpire/24,
			 SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
		 sprintf(sTemp, "%s", sDateTime);
	}

	char sTmp[3];
	char sBuffer[32];

	memset(sBuffer, 0, sizeof(sBuffer));

	for(int i=0; i<6; i++)
	{
		memset(sTmp, 0, sizeof(sTmp));

		sTmp[0] = sTemp[i*2];
		sTmp[1] = sTemp[i*2+1]; 
		sBuffer[i] = atoi(sTmp);
	}

	bool bResult = false;

	for(i=0; i<3; i++)
	{
		MakeBuf_SetBlackUsefulLife(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, (unsigned char*)sBuffer);
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBufferEx(pBuffer) == RET_OK )
			{
				bResult = true;
				break;
			}
		}
	}

	if( !bResult )
	{
		return RET_SYSERROR;
	}

	//修改数据库中的黑名单有效期
	CString strSQL;
	strSQL.Format("update smart_commrec set smt_blackexpire='%s' where smt_authno=%d ", sTemp, pDoc->m_nAuthID);
	ExecuteSQL(nDatabase, strSQL.GetBuffer(0));

	strcpy(pExpire, sTemp);

	return RET_OK;
}

//下传补助名单
long TaskBufferProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	BYTE Buffer[128],*pt=NULL;
	int	 nTmp=0;
	TSSystemParam *pHead;
	int  n = pDocEx->nPortNo;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSSystemParam*)pTask->pData;
	nTmp=pHead->nParameter4;//卡号
	pt=(BYTE*)&nTmp;
	Buffer[0]=*(pt+2);
	Buffer[1]=*(pt+1);
	Buffer[2]=*(pt+0);
	nTmp=pHead->nParameter2;//批次号
	Buffer[3]=*(pt+1);
	Buffer[4]=*(pt+0);
	nTmp=pHead->nParameter3; //金额
	Buffer[5]=*(pt+0);
	Buffer[6]=*(pt+1);
	Buffer[7]=pHead->szParameter3[0];		
	MakeBuf_SetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, Buffer);	
	return RET_OK;
}

//下传补助名单
long TaskProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传补助名单", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "下传补助名单", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//上传补助名单
long TaskBufferProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int Cardno=0;
	unsigned char *pt=NULL;
	int n = pDocEx->nPortNo ;
	
	Cardno=atol(pTask->szMemo);
	pt=(unsigned char*)&Cardno;
	pBuffer->pBuffer[0]=*(pt+2);
	pBuffer->pBuffer[1]=*(pt+1);
	pBuffer->pBuffer[2]=*(pt+0);
	return MakeBuf_GetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	
}

//上传补助名单
long TaskProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传补助名单", "");
		return nResult;
	}
	memcpy(pTask->szMemo,pBuffer->pBuffer,8);
	ReportLog(pDocEx, pTask, RET_OK, "上传补助名单", "");
	return RET_OK;
}

//设置补助开关
long TaskBufferProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;

	if( !strcmp(pTask->szMemo, "1") )
		pDocEx->pChildDoc[n]->m_nSwitch = 1 ;
	else
		pDocEx->pChildDoc[n]->m_nSwitch = 0 ;

	if( pDocEx->pChildDoc[n]->m_nSwitch )
	{
		ReportLog(pDocEx, pTask, RET_OK, "设置补助开关开启", "");
		return MakeBuf_SetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0X00);
	}
	else
	{
		ReportLog(pDocEx, pTask, RET_OK, "设置补助开关关闭", "");
		return MakeBuf_SetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0XFF);
	}
}

//设置补助开关
long TaskProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置补助开关", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "设置补助开关", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}

//读取补助开关
long TaskBufferProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	return MakeBuf_GetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//读取补助开关
long TaskProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "读取补助开关", "");
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "读取补助开关", "");

	return RET_OK;
}



//设置主参数
long TaskBufferProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;

	int n = pDocEx->nPortNo ;
	unsigned char szBuffer[128];
	long nResult = RET_OK;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	memset(szBuffer, 0, sizeof(szBuffer));

	//收费机系统主参数
	if( !strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0226") ) //收费机
	{
		szBuffer[0] = (unsigned char)pData->nValue3;
		szBuffer[1] = (unsigned char)pData->nValue9;

		szBuffer[2] = ((pData->nValue4)/256)%256;
		szBuffer[3] = ((pData->nValue4))%256;

		SVC_DSP_2_HEX((unsigned char*)pData->sValue7, &szBuffer[4], 2);

		szBuffer[6] = (pData->nValue5)%256;
		szBuffer[7] = ((pData->nValue5)/256)%256;
		szBuffer[8] = ((pData->nValue5)/256/256)%256;

		szBuffer[9] = (pData->nValue8)%256;
		szBuffer[10] = ((pData->nValue8)/256)%256;
		szBuffer[11] = ((pData->nValue8)/256/256)%256;

		szBuffer[12] = (pData->nValue6)%256;
		szBuffer[13] = ((pData->nValue6)/256)%256;
		szBuffer[14] = ((pData->nValue6)/256/256)%256;

		szBuffer[15] = (pData->nValue7)%256;
		szBuffer[16] = ((pData->nValue7)/256)%256;
		szBuffer[17] = ((pData->nValue7)/256/256)%256;

		SVC_DSP_2_HEX((unsigned char*)pData->sValue8, &szBuffer[18], 1);

		szBuffer[19] = GetBaudRatecode(pData->nValue2);
		szBuffer[20] = atoi(pData->sValue6);

		SVC_DSP_2_HEX((unsigned char*)pData->sValue3, &szBuffer[21], 4);

		if( !strcmp(pData->sValue4, "") )
		{
			strcpy(pData->sValue4, "00000000");
		}

		SVC_DSP_2_HEX((unsigned char*)pData->sValue4, &szBuffer[25], 2);

		szBuffer[27] = atoi(pData->sValue5);

		if( szBuffer[27] == 0x65 )
			strcpy(pTask->szMemo, "65");
	}
	else
	{
		ReportLog(pDocEx, pTask, nResult, "计时宝系统主参数", "");
		strcpy(data.sMsg, "此功能暂不支持!");
		ReportTaskResult(pTask, RET_NG, &data);
	}

	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);

	MakeBuf_SetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);
 	pBuffer->nTimeOut1 = 1000 ;
	pBuffer->nTimeOut2 = 2000 ;

	return RET_ERRORCALL;
}

//设置主参数
long TaskProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( pBuffer == NULL )
	{
		ReportLog(pDocEx, pTask, RET_TERME_NOANSWER, "设置主参数", "");
		GetResultMessage(RET_TERME_NOANSWER, data.sMsg);
		ReportTaskResult(pTask, RET_TERME_NOANSWER, &data);

		return RET_TERME_NOANSWER;
	}
	
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置主参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	printf("-------设置主参数.........\n");

	//65类卡必须下载新的密码方可使用
	if( !strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0121") )
	{
		long iResult = RET_SYSERROR;
		char szPass[128];

		memset(szPass, 0, sizeof(szPass));
		unsigned char szBuffer[32];
		unsigned char szID[32];
		memset(szBuffer, 0, sizeof(szBuffer));

		SVC_DSP_2_HEX((unsigned char*)szPass, szBuffer, 9);
		SVC_DSP_2_HEX((unsigned char*)pDocEx->pChildDoc[n]->m_szDeviceID, szID, 4);

		SmartEncrypt(1, szID, szBuffer);
		MakeBuf_SetWorkingKey(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, (unsigned char*)szBuffer, 1);

		for(int i=0; i< 3; i++)
		{
			pBuffer->nTimeOut1 = 500 ;
			pBuffer->nTimeOut1 = 1000 ;
			if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
			{
				iResult = UnMakeDeviceBufferEx(pBuffer);
				if( iResult == RET_OK )
				{
					break;
				}
			}
			else
			{
				Sleep(2000);
			}
		}

		if( iResult != RET_OK )
		{
			ReportLog(pDocEx, pTask, iResult, "设置主参数", "设置计时宝密钥失败");
			return iResult;
		}
		else
		{
			ReportLog(pDocEx, pTask, iResult, "设置主参数", "设置计时宝密钥成功!");
		}
	}

	//65类卡必须下载新的密码方可使用
	if( !strcmp(pTask->szMemo, "65") )
	{
		//strSQL = "select smt_content from smart_setup where smt_systemid='93' and upper(smt_param)='DWMM1' ";
		unsigned char szBuffer[32];
		char  szPass[32];
		memset(szBuffer, 0, sizeof(szBuffer));

		TSSystemParam  Parameter;

		ZeroMemory(&Parameter, sizeof(Parameter));
		GetParameter(0, &Parameter);

		strcpy(szPass, Parameter.szParameter3);

		UnPassword(szPass, 'd', szBuffer);

		int k = atoi((char*)szBuffer);
		szBuffer[0] = k%256;
		szBuffer[1] = (k/256)%256;

		MakeBuf_SetV10Password(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);

		for(int i=0; i< 3; i++)
		{
			pBuffer->nTimeOut1 = 500 ;
			pBuffer->nTimeOut1 = 1000 ;
			if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
			{
				long iResult = UnMakeDeviceBufferEx(pBuffer);
				if( iResult == RET_OK )
				{
					ReportLog(pDocEx, pTask, iResult, "设置主参数", "");
					return iResult;
				}
			}
			else
			{
				Sleep(2000);
			}
		}

		ReportLog(pDocEx, pTask, nResult, "设置主参数", "设置V10卡公司密码失败");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "收费机系统主参数", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}

//校对主参数
long TaskBufferProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_GetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//校对主参数
long TaskProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "校对主参数", "");

		ReportLog(pDocEx, pTask, nResult, "收费机系统主参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	

	//收费机系统主参数
	if( strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0121") )
	{
		unsigned char *pHardBuffer = pBuffer->pBuffer+4;
		TSResultData  data;

		ZeroMemory(&data, sizeof(data));

		strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID);
		SVC_HEX_2_DSP(&pHardBuffer[0], (unsigned char*)data.sValue2, 4); //授权号
		data.nValue1 = pHardBuffer[4]; //机号		
		data.nValue3 = pHardBuffer[5]; //密码开关(初始化为0x00)
		data.nValue9 = pHardBuffer[6]; //收费方式
		data.nValue4 = pHardBuffer[7]*256+pHardBuffer[8]; //卡片最大使用次数
		sprintf(data.sValue7, "%.2X%.2X", pHardBuffer[9], pHardBuffer[10]); // 允许消费卡类别
		data.nValue5 = pHardBuffer[11]+pHardBuffer[12]*256+pHardBuffer[13]*65536; //钱包存款最高限额
		data.nValue8 = pHardBuffer[14]+pHardBuffer[15]*256+pHardBuffer[16]*65536; //每次存取款限额
		data.nValue6 = pHardBuffer[17]+pHardBuffer[18]*256+pHardBuffer[19]*65536; //钱包余款最低限额
		data.nValue7 = pHardBuffer[20]+pHardBuffer[21]*256+pHardBuffer[22]*65536; //存取款定值额
		sprintf(data.sValue8, "%.2X", pHardBuffer[23]);  //消费类型
		data.nValue2 = GetBaudRatecodeEx(pHardBuffer[24]); //通信波特率
		sprintf(data.sValue6, "%d", pHardBuffer[25]);   //钱包属性
		SVC_HEX_2_DSP(&pHardBuffer[26], (unsigned char*)data.sValue3, 4); //个人密码密钥前四个字节
		sprintf(data.sValue4, "%.2X%.2X", pHardBuffer[30], pHardBuffer[31]);   //钱包属性
		sprintf(data.sValue5, "%d", pHardBuffer[32]);

		ReportLog(pDocEx, pTask, RET_OK, "收费机系统主参数", "");
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);
	}
	else
	{
		ReportLog(pDocEx, pTask, nResult, "计时宝系统主参数", "");
		strcpy(data.sMsg, "此功能暂不支持!");
		ReportTaskResult(pTask, RET_NG, &data);
	}

	return RET_OK;
}

//校对时钟
long TaskBufferProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//校对时钟
long TaskProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];

	CString strTime = pTask->szMemo;

	CTime  tm(2000+atoi(strTime.Left(2).GetBuffer(0)), 
			atoi(strTime.Mid(2,2).GetBuffer(0)), 
			atoi(strTime.Mid(4,2).GetBuffer(0)), 
			atoi(strTime.Mid(6,2).GetBuffer(0)), 
			atoi(strTime.Mid(8,2).GetBuffer(0)), 
			atoi(strTime.Mid(10,2).GetBuffer(0)));

	unsigned char Buffer[32];
	memset(Buffer, 0, sizeof(Buffer));

	Buffer[0] = tm.GetYear()-2000;
	Buffer[1] = tm.GetMonth();
	Buffer[2] = tm.GetDay();
	Buffer[3] = tm.GetHour();
	Buffer[4] = tm.GetMinute();
	Buffer[5] = tm.GetSecond();
	Buffer[6] = tm.GetDayOfWeek();

	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	MakeBuf_SetClock(&pDoc->DeviceInfo, pBuffer, Buffer);
	if( SendRequest(pDoc, pBuffer) != RET_OK )
	{
		GetResultMessage(RET_SEND_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_SEND_ERROR, &data);

		ReportLog(pDoc, pTask, RET_SEND_ERROR, "校对时钟", "");
		return RET_SEND_ERROR;
	}

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult == RET_OK )
	{
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);

		ReportLog(pDoc, pTask, RET_OK, "校对时钟", "校对时钟成功!");
		return RET_OK;
	}
	else
	{
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		ReportLog(pDoc, pTask, nResult, "校对时钟", "");
		return nResult;
	}
}

//下传大额消费限额
long TaskBufferProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	long nValue = 10000;
	//modified by lina
	
	/*
	try
	{
		long nValue = atoi(pTask->szMemo);
	}
	catch(...)
	{

	}*/
	
	nValue = atoi(pTask->szMemo);
	if(nValue < 0)
		nValue = 10000;


	//if( nValue < 0 )
	//	nValue = 36000 ;

	unsigned char sMoney[32];
	memset(sMoney, 0, sizeof(sMoney));

	sMoney[0] = nValue%256;
	sMoney[1] = (nValue/256)%256;
	sMoney[2] = (nValue/256/256)%256;

	return MakeBuf_SetLargeConsumeMoney(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, sMoney);
}
	
//下传大额消费限额处理
long TaskProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传大额消费限额", "");

		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "下传大额消费限额", "");

	return RET_OK;
}

//网络检测
long TaskBufferProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	MakeBuf_CollectData(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
	return RET_ERRORCALL;
}

long ToDec(long nHex)
{
	return (nHex/16*10) + (nHex%16);
}
	
//网络检测
long TaskProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//设置消费编号及版本
long TaskBufferProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//设置消费编号及版本
long TaskProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	int *pArray = (int*)pHead->pData;

	if( strcmp(pDoc->m_sWorkMode, "2") )
	{
		ReportLog(pDocEx, pTask, RET_TASKWHERE_ERROR, "设置消费编号及版本", "终端机不是编号模式!");

		GetResultMessage(RET_TASKWHERE_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_TASKWHERE_ERROR, &data);

		return RET_TASKWHERE_ERROR;
	}

	unsigned char sArray[100][3];
	int  i=0, iCount = 0 ;
	long nValue = 0 ;

	//读入数据, 格式定义见收费机时间段格式 
	memset(sArray, 0, sizeof(sArray));

	while( iCount < pHead->nCount )
	{
		nValue = pArray[iCount];

		sArray[i][0] = nValue%256;
		sArray[i][1] = (nValue/256)%256;
		sArray[i++][2] = (nValue/256/256)%256;

		if( i >= 50 || iCount >= pHead->nCount-1 )
		{
			if( iCount <= 50 )
				MakeBuf_SetSFJConsumeNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0, i, &sArray[0][0]);
			else
				MakeBuf_SetSFJConsumeNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 1, i, &sArray[0][0]);

			nValue = RET_SYSERROR;
			for(int k=0; k<3; k++)
			{
				if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
				{
					nValue = UnMakeDeviceBufferEx(pBuffer);
					if( nValue == RET_OK )
					{
						break;
					}
				}
			}

			if( nValue != RET_OK )
			{
				ReportLog(pDocEx, pTask, nValue, "设置消费编号及版本", "不能设置消费编号!");
				GetResultMessage(nValue, data.sMsg);
				ReportTaskResult(pTask, nValue, &data);
				return nValue;
			}
			i=0; 
			memset(sArray, 0, sizeof(sArray));
		}
		iCount++;
	}

	unsigned char sValue[64];
	unsigned char sBuffer[16];

	char szTmp[8];

	memset(sValue, 0, sizeof(sValue));
	memset(sBuffer, 0, sizeof(sBuffer));

	strcpy((char*)sValue, pHead->szValue);

	printf("现在设置消费编号及版本, 版本 = %s\n", sValue);

	if( strlen((char*)sValue) < 12 ) 
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "设置消费编号及版本", "表Smart_commrec中的消费编号及版本字段数据不正确!");

		GetResultMessage(RET_VALIDPACKET, data.sMsg);
		ReportTaskResult(pTask, RET_VALIDPACKET, &data);

		return RET_DBQUERYERROR;
	}

	memset(szTmp, 0, sizeof(szTmp));

	szTmp[0] = sValue[0]; szTmp[1] = sValue[1]; 
	sBuffer[0] = atoi(szTmp);

	szTmp[0] = sValue[2]; szTmp[1] = sValue[3]; 
	sBuffer[1] = atoi(szTmp);

	szTmp[0] = sValue[4]; szTmp[1] = sValue[5]; 
	sBuffer[2] = atoi(szTmp);

	szTmp[0] = sValue[6]; szTmp[1] = sValue[7]; 
	sBuffer[3] = atoi(szTmp);

	szTmp[0] = sValue[8]; szTmp[1] = sValue[9]; 
	sBuffer[4] = atoi(szTmp);

	szTmp[0] = sValue[10]; szTmp[1] = sValue[11]; 
	sBuffer[5] = atoi(szTmp);

	Sleep(1000);

	MakeBuf_SetSFJComsumeVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, sBuffer);
	for(int k=0; k<3; k++)
	{
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			nValue = UnMakeDeviceBufferEx(pBuffer);
			if( nValue == RET_OK )
			{
				break;
			}
		}
	}

	ReportLog(pDocEx, pTask, nValue, "设置消费编号及版本", "");

	GetResultMessage(nValue, data.sMsg);
	ReportTaskResult(pTask, nValue, &data);

	return nValue;
}

//设置消费快捷编号
long TaskBufferProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	printf("--------设置消费快捷编号-------------------\n");
	//TSResultData  data;
	//ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	//TSAttachData *pHead = (TSAttachData*)pTask->pData;
	//int *pArray = (int*)pHead->pData;

	/*if( strcmp(pDoc->m_sWorkMode, "2") )
	{
		ReportLog(pDocEx, pTask, RET_TASKWHERE_ERROR, "设置消费快捷编号", "终端机不是编号模式!");

		GetResultMessage(RET_TASKWHERE_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_TASKWHERE_ERROR, &data);

		return RET_TASKWHERE_ERROR;
	}*/
	printf("传递参数pTask->szMemo=%s\n", pTask->szMemo);
	char temp[256];
	sprintf(temp,"");
	temp[0] = pTask->szMemo[0];
	temp[1] = pTask->szMemo[1];
	int i,j,k;
	unsigned char sArray[100][3];
	long nValue;
	memset(sArray, 0, sizeof(sArray));
	
	i = atoi(temp); 
	printf("快捷方式总条数=%d\n",i);
	
	for(j=0;j<i;j++)
	{
		sprintf(temp,"");
		for(k=0;k<4;k++)
		{
			temp[k] = pTask->szMemo[2+j*4+k];
		}
		nValue = atoi(temp);
		printf("nValue = %d\n",nValue);
		sArray[j][0] = nValue%256;
		sArray[j][1] = (nValue/256)%256;
		sArray[j][2] = (nValue/256/256)%256;
	}

/*	unsigned char sArray[100][3];
	//int  i=0;
	long nValue;

	//读入数据, 格式定义见收费机时间段格式 
	memset(sArray, 0, sizeof(sArray));
	while( i < 100 && i< pHead->nCount  )
	{
		nValue = pArray[i];

		sArray[i][0] = nValue%256;
		sArray[i][1] = (nValue/256)%256;
		sArray[i][2] = (nValue/256/256)%256;

		i++;
	}
	*/
	return MakeBuf_SetSFJFastNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, i, &sArray[0][0]);
}
	
//设置消费快捷编号
long TaskProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置消费快捷编号", "");

		GetResultMessage(nResult, data.sMsg);
		printf(" ------向设置消费快捷编号失败-----\n");
		ReportTaskResult(pTask, nResult, &data);
		
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "设置消费快捷编号", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	printf("------向设置消费快捷编号成功-----\n");
	return RET_OK;
}

//设置机器ID
long TaskBufferProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	return RET_OK;
}
	
//设置机器ID处理
long TaskProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置机器ID", "");
		return nResult;
	}

	strcpy(pDocEx->pChildDoc[n]->m_szDeviceID, pTask->szMemo);

	ReportLog(pDocEx, pTask, RET_OK, "设置ID号", "");

	return RET_OK;
}

//设置消费时间段参数
long TaskBufferProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSXFTimePara *pPara = (TSXFTimePara*)pHead->pData;

	unsigned char sArray[320][10];
	int  i=0;
	long nValue;
	unsigned char sValue[64];
	char sTmp[16];
	long nTry = 0 ;

	//读入数据, 格式定义见收费机时间段格式 
	memset(sArray, 0, sizeof(sArray));
	while( i< pHead->nCount && i < 16 )
	{
		memset(sTmp, 0, sizeof(sTmp));

		strcpy((char*)sValue, pPara[i].szBeginTime);
		sTmp[0] = sValue[0]; sTmp[1] = sValue[1];
		sArray[i][0] = atoi(sTmp);

		sTmp[0] = sValue[3]; sTmp[1] = sValue[4];
		sArray[i][1] = atoi(sTmp);

		strcpy((char*)sValue, pPara[i].szEndTime);
		sTmp[0] = sValue[0]; sTmp[1] = sValue[1];
		sArray[i][2] = atoi(sTmp);

		sTmp[0] = sValue[3]; sTmp[1] = sValue[4];
		sArray[i][3] = atoi(sTmp);

		strcpy((char*)sValue, pPara[i].szClass);
		int nBin = GetBinaryValue((char*)sValue);
		sArray[i][4] = (nBin/256)%256;
		sArray[i][5] = nBin%256;


		nValue = pPara[i].nMoney;
		sArray[i][6] = nValue%256;
		sArray[i][7] = (nValue/256)%256;
		sArray[i][8] = (nValue/256/256)%256;

		nValue = pPara[i].nTimes;
		sArray[i][9] = (unsigned char)nValue ;
		if( nTry < nValue )
			nTry = nValue ;

		i++;
	}

	return MakeBuf_SetSFJ_TimePhase(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,i, nTry, &sArray[0][0]);
}
	
//设置消费时间段参数
long TaskProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置消费时间段参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "设置消费时间段参数", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//设置注册号
long TaskBufferProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}
	
//设置注册号
long TaskProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//防火状态设置
long TaskBufferProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetFireState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//防火状态设置
long TaskProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置防火状态", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "防火状态设置", "");

	return RET_OK;
}

//防盗状态设置
long TaskBufferProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetTheftState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//防盗状态设置
long TaskProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;

	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置防盗状态", "");

		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "防盗状态设置", "");

	return RET_OK;
}

//从防火防盗状态恢复正常运行状态
long TaskBufferProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetNormalState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//从防火防盗状态恢复正常运行状态
long TaskProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "恢复正常运行状态", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "恢复正常运行状态", "");

	return RET_OK;
}

//下传搭伙费比率
long TaskBufferProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	unsigned char *pt=NULL;
	int n = pDocEx->nPortNo ;
	TSAttachData *pHead = (TSAttachData*)pTask->pData ;

	pt = (unsigned char*)&pHead->nValue ;
	unsigned char nClass = *(pt+0);
	pt = (unsigned char*)&pHead->nCount ;
	unsigned char nRate  = *(pt+0);
	MakeBuf_SetIncFeeRate(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, nClass, nRate);
	printf("下传搭伙费比率:<<<<<<<<<<卡类: %ld, 费率:%ld.........\n", nClass, nRate);	
	return RET_OK;
}

//下传搭伙费比率
long TaskProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;

	TSAttachData *pHead = (TSAttachData*)pTask->pData ;

	int nClass = pHead->nValue ;
	int nRate  = pHead->nCount ;

	data.nValue1 = nClass ;
	data.nValue2 = nRate ;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传搭伙费比率", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	ReportLog(pDocEx, pTask, RET_OK, "下传搭伙费比率", NULL);

	return RET_OK;
}

//设置签到开关
long TaskBufferProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;

	if( !strcmp(pTask->szMemo, "1") )
		pDocEx->pChildDoc[n]->m_nSwitch = 1 ;
	else
		pDocEx->pChildDoc[n]->m_nSwitch = 0 ;

//	if( pDocEx->pChildDoc[n]->m_nSwitch ==1 )
//	{
//		ReportLog(pDocEx, pTask, RET_OK, "设置签到开关开启", "");
//		return MakeBuf_SetComsumeFlag(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0);
//	}
//	else
//	{
		ReportLog(pDocEx, pTask, RET_OK, "设置签到开关关闭", "");
		return MakeBuf_SetComsumeFlag(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0);
//	}
}

//设置签到开关
long TaskProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		printf("----设置%.8X签退失败,代码为%d\n",pDocEx->pChildDoc[n]->m_nAuthID,
			nResult);

		ReportLog(pDocEx, pTask, nResult, "设置签到开关", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	printf("----设置%.8X签退成功\n",pDocEx->pChildDoc[n]->m_nAuthID);	
	ReportLog(pDocEx, pTask, RET_OK, "设置签到开关", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//上传时钟
long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetClock(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	   
	return RET_OK;
}

//上传设备时钟
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传设备时钟", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)data.sValue1,6);
	//SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)pTask->szMemo,6);

	ReportLog(pDocEx, pTask, RET_OK, "上传设备时钟", "");	
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//设置每日累计消费金额
long TaskBufferProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	int  nMoney = atoi(pTask->szMemo);
	unsigned char ucBuffer[4];
	if(nMoney <= 0)
		nMoney = 3000;
	ucBuffer[0] = nMoney%256;
	ucBuffer[1] = nMoney/256;
	ucBuffer[2] = nMoney/256/256;
	ucBuffer[3] = nMoney/256/256/256;
	MakeBuf_SetDayLargeComsumeMoney(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,ucBuffer);
	return RET_OK;
}

//设置每日累计消费金额
long TaskProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置每日累计消费限额", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "设置每日累计消费限额", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//初始化LPORT端口参数
long TaskBufferProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	int  nMoney = atoi(pTask->szMemo);
	long nResult;

	for(long k=0; k<3; k++)
	{
		MakeBuf_ClearPortData(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, nMoney);
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			if( (nResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				break;
			else
				Sleep(1000);
		}
	}
	Sleep(1000);
	
	MakeBuf_SetPortToFactorySetting(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,nMoney);
	
	return RET_OK;
}

//初始化LPORT端口参数
long TaskProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "初始化LPORT端口参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "初始化LPORT端口参数", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//设置终端管理员密码
long TaskBufferProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	unsigned char ucPassword[3];
	SVC_DSP_2_HEX((unsigned char *)pTask->szMemo,ucPassword,3); 
	MakeBuf_SetManagePassword(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,ucPassword);
	return RET_OK;
}

//设置终端管理员密码
long TaskProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置终端管理员密码", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "设置终端管理员密码", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//获取端口参数
long TaskBufferProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	
	MakeBuf_GetPortPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,atoi(pTask->szMemo));
	return RET_OK;
}

long TaskProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "获取端口参数", "");

		ReportLog(pDocEx, pTask, nResult, "获取端口参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	for(int i=0; i< pBuffer->nCmdSize; i++) 
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");

	//获取端口参数
	
		unsigned char *pHardBuffer = pBuffer->pBuffer+4;
	//	TSResultData  data;

		ZeroMemory(&data, sizeof(data));
		sprintf(data.sValue1,"%.2X%.2X%.2X%.2X",pHardBuffer[0],pHardBuffer[1],pHardBuffer[2],pHardBuffer[3]); //ID号
		data.nValue1 = pHardBuffer[4];//机号
		sprintf(data.sValue2,"%.2X%.2X",pHardBuffer[5],pHardBuffer[6]);//类型
		sprintf(data.sValue3,"%.2X%.2X%.2X%.2X",pHardBuffer[7],pHardBuffer[8],pHardBuffer[9],pHardBuffer[10]);//程序版本
		sprintf(data.sValue4,"%.2X%.2X%.2X%.2X",pHardBuffer[11],
			                                     pHardBuffer[12],
												 pHardBuffer[13],
												 pHardBuffer[14]);//注册号

		ReportLog(pDocEx, pTask, RET_OK, "获取端口参数", "");
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);
	

	return RET_OK;
}


/**************************dengjun 20050830********************/

#if 1
//广播下传白名单
long TaskBufferProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)     
{
	int ret=0;
	if(pTask==NULL)	   return -1;
	if(pDocEx==NULL)   return -1;
	if(pBuffer==NULL)  return -1;
	
	int n = pDocEx->nPortNo ;
	printf("------广播白名单成功------\n");		
	unsigned char buffer[80];
	unsigned char version[6];
	bool bResult= false; 

	memset(buffer, 0, sizeof(buffer));

	memcpy(buffer,pTask->szMemo,3);
	memcpy(version,pTask->szMemo+3,6);	
   TSSmartDoc *pDoc = pDocEx->pChildDoc[0];
	pBuffer->nBufferSize = MakeBuf_BoardWhiteNo(pBuffer->pBuffer, (unsigned char*)version, buffer);			
	ret=SendRequest(pDoc, pBuffer);
	memset(buffer, 0, sizeof(buffer));
	SVC_HEX_2_DSP((unsigned char*)pBuffer->pBuffer,buffer,pBuffer->nBufferSize);
	ReportLog(pDocEx, pTask, RET_OK, "广播白名单成功", "");	
	return RET_OK;
}

#endif

//广播下传白名单
long TaskProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "广播下传白名单", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "广播下传白名单", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//下传/删除白名单
long TaskBufferProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	BYTE  CardNo[6],*pt=NULL;
	int	  count=0,flag=0;
	unsigned long  cardno=0;
	long		ret=0;

	int n = pDocEx->nPortNo ;

	memset(CardNo, 0x00, sizeof CardNo );
	
	TSAttachData *pHead = (TSAttachData*)pTask->pData ;
	count=pHead->nCount;  //条数
	flag = pHead->nValue;  //标识
	cardno = atol(pHead->szValue);
	pt = (BYTE*)&cardno;
	CardNo[0]= *(pt+2);
	CardNo[1]= *(pt+1);
	CardNo[2]= *(pt+0);

	if( flag == 0 ) //下传一条白名单
	{		
		ret =MakeBuf_DownWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,10,(BYTE*)CardNo);	
	}
	else if( flag == 1 ) //删除一条白名单
	{
		ret =MakeBuf_DelWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, CardNo);	
	}
	else if( flag == 2 ) //删除所有白名单
	{
		ret =MakeBuf_DelAllWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
	}
	printf("下传或删除白名单");

	return ret;	
}

//下传/删除白名单
long TaskProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传/删除白名单", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}	
	ReportLog(pDocEx, pTask, RET_OK, "下传/删除白名单", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930113
//下传计时宝白名单版本
long TaskBufferProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	BYTE   date1[12];

	memset(date1, 0x00, sizeof date1 );
	SVC_DSP_2_HEX((BYTE*)pTask->szMemo,date1,6);	
	return MakeBuf_SetWhiteVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,date1);
}

//下传计时宝白名单版本
long TaskProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传计时宝白名单版本", "");

		ReportLog(pDocEx, pTask, nResult, "下传计时宝白名单版本", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}	
	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //设备ID	
	ReportLog(pDocEx, pTask, RET_OK, "下传计时宝白名单版本", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}




//930114
//上传计时宝白名单版本
long TaskBufferProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;	
	return MakeBuf_GetWhiteVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	
}

//上传计时宝白名单版本
long TaskProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传计时宝白名单版本", "");

		ReportLog(pDocEx, pTask, nResult, "上传计时宝白名单版本", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}	
	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //设备ID	
	unsigned char *pHardBuffer = pBuffer->pBuffer+4;
	ReportLog(pDocEx, pTask, RET_OK, "上传计时宝白名单版本", "");
	GetResultMessage(RET_OK, data.sMsg);
	SVC_HEX_2_DSP(pHardBuffer,(BYTE*)data.ssValue1,6);	
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}



//930110
//上传计时宝节假日
long TaskBufferProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetMode3Holiday(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);		
	return RET_OK;
}

//上传计时宝节假日
long TaskProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	TSResultData  data;
	memset(&data, 0x00, sizeof(TSResultData));
	
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;	
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传计时宝节假日", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	//假日数	
	data.nValue1=pHardBuffer[0];
	memcpy(data.ssValue1,pHardBuffer+1,data.nValue1*2);	
	ReportLog(pDocEx, pTask, RET_OK, "上传计时宝节假日", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);	
	return RET_OK;
}

//930109
//下传计时宝节假日
long TaskBufferProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int No=0;
	BYTE Buffer[240];
	memset(Buffer, 0x00, sizeof Buffer );
	TSAttachData *pHead =(TSAttachData*)pTask->pData;
	int  n = pDocEx->nPortNo;	
	No = pHead->nCount;
	memcpy(Buffer,pHead->szValue,No*2);
	MakeBuf_SetMode3Holiday(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,No,Buffer);	
	printf("count=%ld   %02ld%02ld%02ld%02ld%02ld\n",No,Buffer[0],Buffer[1],Buffer[2],Buffer[3],Buffer[4]);
	return RET_OK;
}

//下传计时宝节假日
long TaskProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	
	ZeroMemory(&data, sizeof(data));	

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传计时宝节假日", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "下传计时宝节假日", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930106
//上传计时宝时间段
long TaskBufferProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int WeekInfo=0;
	WeekInfo = atol(pTask->szMemo);
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetMode3TimePhaseInfo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,WeekInfo);		
	return RET_OK;
}

//上传计时宝时间段
long TaskProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	int		count=0;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;

	ZeroMemory(&data, sizeof(data));
	count = (int)pHardBuffer[0];

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传计时宝时间段", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	//时间段数
	data.nValue1 = pHardBuffer[0];	
	memcpy(data.ssValue1,pHardBuffer+1,data.nValue1*8);
	ReportLog(pDocEx, pTask, RET_OK, "上传计时宝时间段", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);	
	return RET_OK;
}


//930105
//下传计时宝时间段
long TaskBufferProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int WeekInfo=0;
	int No=0;
	BYTE Buffer[128];
	TSAttachData *pHead;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSAttachData*)pTask->pData;
	WeekInfo = pHead->nCount;		//星期
	No		 = pHead->nValue;		//时间段条数
	memcpy(Buffer,pHead->szValue,No*8);	
	int  n = pDocEx->nPortNo;	
	MakeBuf_SetMode3TimePhaseInfo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,WeekInfo,No,Buffer);	
	return RET_OK;
}

//下传计时宝时间段
long TaskProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传计时宝时间段", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "下传计时宝时间段", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930120
//门禁机开关控制
long TaskBufferProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int flag = 0;	
	int  n = pDocEx->nPortNo;		

	flag = atol(pTask->szMemo);
	if( flag == 1 )
	{
		MakeBuf_SetFireState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// 功能：设置为防火状态
	}
	else if( flag == 2 )
	{
	
		MakeBuf_SetTheftState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// 功能：设置为防盗状态
	}	
	else if( flag == 3 )
	{
		MakeBuf_SetNormalState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// 功能：恢复正常
	}
	return RET_OK;
}

//门禁机开关控制
long TaskProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "门禁开关", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "门禁开关", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930103
//设置计时宝主参数
long TaskBufferProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	unsigned char szBuffer[128];
	long nResult = RET_OK;
	TSResultData  data;

	memset(&data,    0x00, sizeof(data)    );
	memset(szBuffer, 0x00, sizeof(szBuffer));
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(szBuffer,pTask->szMemo,28);
	MakeBuf_SetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);	
 	pBuffer->nTimeOut1 = 1000 ;
	pBuffer->nTimeOut2 = 2000 ;
	return RET_ERRORCALL;
}

//设置计时宝主参数
long TaskProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( pBuffer == NULL )
	{
		ReportLog(pDocEx, pTask, RET_TERME_NOANSWER, "设置计时宝主参数", "");
		GetResultMessage(RET_TERME_NOANSWER, data.sMsg);
		ReportTaskResult(pTask, RET_TERME_NOANSWER, &data);
		return RET_TERME_NOANSWER;
	}
	
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "设置计时宝主参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "设置计时宝主参数", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930102
//采集计时宝历史流水
long TaskBufferProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	int  n = pDocEx->nPortNo;			
	unsigned char SerialNo[5],*pt=NULL;
	unsigned long  serial=0;
	memset(SerialNo, 0x00, sizeof SerialNo );

	serial = atol(pTask->szMemo);
	pt=(unsigned char*)&serial;
	SerialNo[0]=*(pt+1);
	SerialNo[1]=*(pt+0);
	MakeBuf_CollectDataBySerialNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,SerialNo);
	return RET_OK;
}

////采集计时宝历史流水
long TaskProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "采集计时宝历史流水", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "采集计时宝历史流水", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer+4,(int)pBuffer->pBuffer[3]);
	data.nValue1=(int)pBuffer->pBuffer[3];
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//930104
//上传计时宝主参数
long TaskBufferProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_GetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//上传930104主参数
long TaskProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传计时宝主参数", "");

		ReportLog(pDocEx, pTask, nResult, "上传计时宝主参数", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}
	unsigned char *pHardBuffer = pBuffer->pBuffer+4;

	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //设备ID		
	memcpy(data.ssValue1,pHardBuffer,33);	//主参数
	ReportLog(pDocEx, pTask, RET_OK, "上传计时宝主参数", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}



//930021
//修改POS参数或增加POS
long TaskBufferProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//修改POS参数或增加POS
long TaskProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	if( pTask->szMemo[0] == '0' )
	{
		ReportLog(pDocEx, pTask, RET_PARAMETER_ERROR2, "修改POS参数或增加POS", "");
		GetResultMessage(RET_PARAMETER_ERROR2, data.sMsg);
		memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
		data.nValue1 = pBuffer->nBufferSize;
		ReportTaskResult(pTask, RET_PARAMETER_ERROR2, &data);
		return RET_PARAMETER_ERROR2;
	}
	ReportLog(pDocEx, pTask, RET_OK, "修改POS参数或增加POS", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//下传补助名单
long TaskBufferProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	BYTE Buffer[128],*pt=NULL;
	int	 nTmp=0;
	TSSystemParam *pHead;
	int  n = pDocEx->nPortNo;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSSystemParam*)pTask->pData;
	nTmp=pHead->nParameter4;//卡号
	pt=(BYTE*)&nTmp;
	Buffer[0]=*(pt+2);
	Buffer[1]=*(pt+1);
	Buffer[2]=*(pt+0);
	nTmp=pHead->nParameter2;//批次号
	Buffer[3]=*(pt+1);
	Buffer[4]=*(pt+0);
	nTmp=pHead->nParameter3; //金额
	Buffer[5]=*(pt+0);
	Buffer[6]=*(pt+1);
	SVC_DSP_2_HEX((BYTE*)pHead->szParameter2,&Buffer[7], 1);
	MakeBuf_SetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, Buffer);	
	return RET_OK;
}


//下传补助名单
long TaskProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "下传补助名单", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "下传补助名单", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//上传黑名单版本
long TaskBufferProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;		
	MakeBuf_GetBlackVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	   
	return RET_OK;
}

//上传黑名单版本
long TaskProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;
	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "上传黑名单版本", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)data.sValue1,6);
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)pTask->szMemo,6);
	
	ReportLog(pDocEx, pTask, RET_OK, "上传黑名单版本", "");	
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}
