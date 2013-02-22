
#include "stdafx.h"
#include "Application.h"

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
	return theApp.ReadSmartDoc(pSmartDoc, nDocCount);
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
	return theApp.ReleaseSmartDoc(pSmartDoc);
}

//*=================================================================================
//*原型: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      pFunction, 传入服务器的API地址
//*      nFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall InitModuleDLL(TSSmartFunction *pFunction, TSSmartSupport *pSupport)
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
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0248");

	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "01");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "02");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "09");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "12");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "16");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "18");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "70");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "71");	
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "72");	
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "73");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "74");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "75");

	return theApp.ImportFunc(pFunction);
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
	return theApp.CreateTaskBuffer(pDocEx, pTask, pBuffer);
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
	return theApp.SmartTaskProcess(pDocEx, pTask, pBuffer);
}

extern "C" long __stdcall DLLSupportInfo(TSSmartSupport *pSupport)
{
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
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0248");
	
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "01");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "02");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "09");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "12");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "16");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "18");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "70");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "71");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "72");//白名单及版本下传
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "73");//白名单批量下载下传任务
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "74");//心跳
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "75");//设备状态监控
	return RET_OK;
}
