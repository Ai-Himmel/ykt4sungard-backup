//*---------------------------------------------------------------------
//* 文件名称:  ModuleDef.h
//* 实现功能:  外挂的插件, 业务库, 协议解释说明
//* 版权说明:  三九智慧电子有限公司  .  2004.02 - 03 
//* 说    明:
//*            1. 定义所有的业务库的接口
//*            2. 定义服务器提供给业务库的API
//*            3. 定义公共的结构及数据
//*            4. 定义终端打包库的接口
//*            5. 定义协议接口
//*---------------------------------------------------------------------
#ifndef __MODULE_DEF_H__
#define __MODULE_DEF_H__

#pragma once

//返回信息
#define RET_SUCCESS       0		//成功返回
#define RET_ERROR        -1		//失败返回
#define RET_TIMEOUT      -2     //超时返回
#define RET_TERMINATE    -3     //执行被中断返回
#define RET_END_OK       -10    //任务成功并结束
#define RET_END_NG       -11    //任务失败并结束

//定义插件类型
#define MODULE_TYPE_APPLAYER		0x01			//业务处理
#define MODULE_TYPE_PROTOCOL        0x02            //协议处理
#define MODULE_TYPE_DRIVER          0x03            //设备处理
#define MODULE_TYPE_TASK            0x04            //任务管理操作

//定义插件版本信息
struct TSPlusInVersion
{
	char   szCompany[128];			//公司名称
	char   szMajorVersion[16];		//主版本
	char   szMinorVersion[16];		//次版本
	char   szAuthor[32];			//作者
	char   szCreateDate[24];		//生成日期
	char   szModifyDate[24];		//最近修改日期
	char   szFunction[128];        //实现的功能
};

//************************************************************************************
//*名称: TSSmartFixInfo
//*功能: 业务模块传入到服务器的系统固定信息
//************************************************************************************
struct TSSmartFixInfo
{
	char  cHeadFlag;		//包头字符
	char  cEndFlag;			//包尾字符
	long  nPacketSize;      //包的长度
	long  nScanTask;		//调用任务包的周期(毫秒), 默认为1000
	long  nSmartDocSize;    //设备档案结构大小
	long  nTaskDocSize;     //任务结构大小
	char  sReserved1[64];   //保留1
	char  sReserved2[64];   //保留2
	char  sReserved3[64];   //保留3
	long  nReserved1;       //保留1
	long  nReserved2;       //保留2
	long  nReserved3;       //保留3
};


//************************************************************************************
//*名称: TSSmartDoc
//*功能: 999终端属性
//************************************************************************************
struct TSSmartDoc
{
	char	m_szMacCode[8];				//终端机型号代码
	char	m_szMacCard[64];			//可用IC卡卡型
	char	m_szMacModle[8];			//终端机型号
	char	m_szMacType[24];			//机型名称

	long    m_nAuthID;					//授权号
	char	m_szDeviceID[16];			//设备ID
	char	m_szRegister[16];			//注册号
	long	m_nMachineNo;				//机号	
	char	m_szVersion[8];				//设备版本号
	char	m_szPassword[8];			//系统员密码

	char	m_szPort[32];				//通讯端口
	long	m_nBaudRate;				//波特率
	long	m_nConnType;				//通讯方式(主/被)

	long	m_nPortCount;				//服务器端口总数
	long	m_nSMTPort;					//服务器端口号

	long	m_nCommMode;				//链路模式
	long	m_nOnNet;					//是否在网
	long	m_nOnline;					//是否联机交易

//----------以下为统计信息--------------------------//
	char	m_szStartTime[24];			//打开时间
	char	m_szStopTime[24];			//停止时间
	int     m_nCurStatus;				//当前状态
	long    m_nReadBytes;				//读入字节
	long    m_nWriteBytes;				//写入字节
	long    m_nReadError;				//读错误次数
	long	m_nWriteError;				//写错误次数
	long	m_nTimeError;				//时钟异常次数
	long    m_nRate;					//速度字节/秒, (保留)
};

//新建任务时调用
struct TSSmartBuffer
{
	long    m_nTaskType;					//任务类型
	long	m_nBufferSize;					//返回的缓冲区内容长度
	char    m_lpBuffer;						//返回的缓冲区内容
	char	m_lpCmdBuffer;					//返回的命令字
	bool	m_bFirstWrite;					//首次是否为发送
	long	m_nStepLevel;					//命令分为几步(暂时未用,要待讨论)
};

//回调返回信息
struct TSSmartCallInfo
{
	bool	bSaveToDB;				//是否保存到数据库
	char	szSQL[1024];			//SQL语句
	bool	bMark;					//是否做标记
	char	pszMarkBuffer;			//做标记的命令行
	long	nMarkLength;			//标记命令行的长度
	bool	bEndOperFlag;			//结束操作标记
};

////////////////////////////////////////////////////////////////////////////////////
//以下为SmartService架构提供的API
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//原型:  long GetDBHandle(long nTimeOut)
//*功能: 得到一个空闲的数据库句柄
//*参数: 
//*      nTimeOut:   超时时间(如果在指定的nTimeOut内无空闲的数据库,则返回错误
//*返回: 
//*      < 0 :    失败
//*      = 0 :    超时(无空闲的连接,请稍后再试)
//*=================================================================================
typedef long (*lpfnGetDBHandle)(long nTimeOut);

//*=================================================================================
//原型:  void FreeDBHandle(long nHandle)
//*功能: 释放一个占用的数据库句柄
//*参数: 
//*      nHandle: 数据库句柄.  由GetDBHandle()返回的值
//*返回: 
//*      无
//*=================================================================================
typedef void (*lpfnFreeDBHandle)(long nHandle);

//*=================================================================================
//原型:  long ExecuteQuery(long nHandle, char *pszSQL);
//*功能: 查询数据库
//*参数: 
//*      nHandle:  数据库句柄
//*      pszSQL:   SQL语句
//*返回: 
//*      > 0 :    记录集句柄
//*      <=0 :    查询失败
//*=================================================================================
typedef long (*lpfnExecuteQuery)(long nHandle, char *pszSQL);

//*=================================================================================
//原型:  void CloseRecHandle(long nHandle, long nRecHandle)
//*功能: 释放一个打开的记录集句柄
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      无
//*=================================================================================
typedef void (*lpfnCloseRecHandle)(long nHandle, long nRecHandle);


//*=================================================================================
//原型:  int IsOpen(long nHandle, long nRecHandle)
//*功能: 记录集是否打开
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  已打开
//*      <=0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsOpen)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int IsBOF(long nHandle, long nRecHandle)
//*功能: 光标是否在记录集首
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  是
//*      =0  :  不是
//*      < 0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsBOF)(long nHandle, long nRecHandle);


//*=================================================================================
//原型:  int IsEOF(long nHandle, long nRecHandle)
//*功能: 光标是否在记录集尾
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  是
//*      =0  :  不是
//*      < 0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsEOF)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int MoveFirst(long nHandle, long nRecHandle);
//*功能: 光标移到记录集首
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveFirst)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int MoveLast(long nHandle, long nRecHandle);
//*功能: 光标移到记录集尾
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveLast)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int MoveNext(long nHandle, long nRecHandle);
//*功能: 光标下移一条记录
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveNext)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int MovePrev(long nHandle, long nRecHandle);
//*功能: 光标上移一条记录
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMovePrev)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  int GetFieldCount(long nHandle, long nRecHandle)
//*功能: 得到字段数
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  字段数
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldCount)(long nHandle, long nRecHandle);

//*=================================================================================
//原型:  long GetRecordCount(long nHandle, long nRecHandle)
//*功能: 得到记录数
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      >= 0 :  记录数
//*      < 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef long (*lpfnGetRecordCount)(long nHandle, long nRecHandle);


//*=================================================================================
//原型:  int GetFieldName(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldName)
//*功能: 得到字段名
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      nIndex:     字段的索引.  
//*      pszRetFieldName:  返回的字段名称
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldName)(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldName);

//*=================================================================================
//原型:  int GetFieldValue(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldValue);
//*功能: 得到字符型字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      nIndex:     字段的索引.  
//*      pszRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldStringValue)(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldValue);

//*=================================================================================
//原型:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到字符型字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      pszRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldStringValueEx)(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);


//*=================================================================================
//原型:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到整型,布尔型, 字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldLongValue)(long nHandle, long nRecHandle, int nIndex, long *nRetFieldValue);
typedef int (*lpfnGetFieldLongValueEx)(long nHandle, long nRecHandle, char *sFieldName, long *nRetFieldValue);


//*=================================================================================
//原型:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到单精度, 金额, 字段的值.
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldFloatValue)(long nHandle, long nRecHandle, int nIndex, float *nRetFieldValue);
typedef int (*lpfnGetFieldFloatValueEx)(long nHandle, long nRecHandle, char *sFieldName, float *nRetFieldValue);

//*=================================================================================
//原型:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到高精度字段的值. 如小数位较高的字段
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldDoubleValue)(long nHandle, long nRecHandle, int nIndex, double *nRetFieldValue);
typedef int (*lpfnGetFieldDoubleValueEx)(long nHandle, long nRecHandle, char *sFieldName, double *nRetFieldValue);

//定位到当前字段
typedef int (*lpfnLocate)(long nHandle, long nRecHandle, char *sFieldName, char *sValue);


//*=================================================================================
//原型:  int ExecuteSQL(long nHandle, char *pszSQL);
//*功能: 执行DDL SQL语句
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      pszSQL:    SQL语句
//*返回: 
//*      > 0 :  成功
//*      <=0 :  失败
//*=================================================================================
typedef int (* lpfnExecuteSQL)(long nHandle, char *pszSQL);

//*===========================================================================================================================
//*原型: long SmartExecute(long nAuthID, unsigned char *pszCmdBuffer, 
//*             long  nCmdBufferSize, unsigned char *pszRetBuffer, 
//*             long* nRetSize, long  nTimeOut);
//*功能: 执行一个设备命令,并得到返回结果
//*参数: 
//*      nAuthID:        设备ID标识
//*      pszCmdBuffer:   发出的命令数据
//*      nCmdBufferSize: 发出的命令数据长度
//*      pszRetBuffer:   返回的结果
//*      nRetSize:       返回结果的长度
//*      nTimeOut:       命令执行的超时时间
//*返回: 
//*      >  0 :   执行成功
//*      <= 0 :   执行失败
//*=================================================================================
typedef long (*lpfnSmartExecute)(
				long nAuthID, 
				unsigned char *pszCmdBuffer, 
				long  nCmdBufferSize, 
				unsigned char *pszRetBuffer,
				long* nRetSize, 
				long  nTimeOut);


//*===========================================================================================================================
//*名称: TSSmartFunction
//*功能: SmartService提供给业务接口层的API集
//*===========================================================================================================================
struct TSSmartFunction
{
	lpfnGetDBHandle				fnGetDBHandle;
	lpfnFreeDBHandle			fnFreeDBHandle;
	lpfnExecuteQuery			fnExecuteQuery;
	lpfnCloseRecHandle			fnCloseRecHandle;
	lpfnIsOpen					fnIsOpen;
	lpfnIsBOF					fnIsBOF;
	lpfnIsEOF					fnIsEOF;
	lpfnMoveFirst				fnMoveFirst;
	lpfnMoveLast				fnMoveLast;
	lpfnMoveNext				fnMoveNext;
	lpfnMovePrev				fnMovePrev;
	lpfnGetFieldCount			fnGetFieldCount;
	lpfnGetRecordCount			fnGetRecordCount;
	lpfnGetFieldName			fnGetFieldName;
	lpfnGetFieldStringValue		fnGetFieldStringValue;
	lpfnGetFieldStringValueEx	fnGetFieldStringValueEx;
	lpfnGetFieldLongValue		fnGetFieldLongValue;
	lpfnGetFieldLongValueEx		fnGetFieldLongValueEx;
	lpfnGetFieldFloatValue		fnGetFieldFloatValue;
	lpfnGetFieldFloatValueEx	fnGetFieldFloatValueEx;
	lpfnGetFieldDoubleValue		fnGetFieldDoubleValue;
	lpfnGetFieldDoubleValueEx	fnGetFieldDoubleValueEx;
	lpfnLocate					fnLocate;
	lpfnExecuteSQL				fnExecuteSQL;
	lpfnSmartExecute			fnSmartExecute;
};

////////////////////////////////////////////////////////////////////////////////////
//以下为业务功能回调原型
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//*原型: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      pFunction, 传入服务器的API地址
//*      pSmartFixInfo,  传回的服务器参数
//*      nFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (* lpfnInitModule)(TSSmartFunction *pFunction, TSSmartFixInfo *pSmartFixInfo, long *nFlag);


//*=================================================================================
//*原型: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      lpKeyBuffer, 授权字符串(保留)
//*      dwFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (* lpfnReadSmartDocInfo)(void **pSmartDoc, long *nDocCount);

//*=================================================================================
//*功能: 清除业务功能模块, 退出DLL时调用
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef LONG (* lpfnDestoryModule)();

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
typedef LONG (* lpfnCreateTaskBuffer)(TSSmartDoc *pSmartDoc, TSSmartDoc *pDocArray[], LONG nArrayLength, TSSmartBuffer  *pSmartBuffer);

//*=================================================================================
//*功能: 从终端接收数据后的处理(实现解包, 生成SQL等)
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef LONG (*lpfnRecvProcess)(
				TSSmartDoc *pSmartDoc,	 //终端信息
				TSSmartDoc *pDocArray[], //终端级联数组
				LONG nArrayLength,		 //数组项数
				LONG nTaskType,			 //任务类型
				LPTSTR pszBuffer,		 //接收的数据内容, 需返回解包后的内容体
				DWORD *dwBufferSize,	 //接收的数据长度, 解包后其长度需返回
				TSSmartCallInfo *pSmartInfo);


//*=================================================================================
//*功能: 协议的解包,封包
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================





#endif //__MODULE_DEF_H__
