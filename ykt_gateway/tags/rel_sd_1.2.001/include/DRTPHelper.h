#ifndef _DRTPHELPER_H_
#define _DRTPHELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include <string>
#include <exception>
#include "mytypes.h"
#include "CPack.h"
#include "drtplib.h"
#include <ace/Log_Msg.h>

class CDRTPHelper
{
private:
	//<! DRTP 服务器Ip
	char m_serverIP[32];
	//<! DRTP 服务器端口号
	int m_serverPort;
	//<! DRTP 主功能号
	int m_funcNo;
	int m_drtpNo;
	//<! 请求功能号
	int m_requestType;
	//<! 错误信息
	char m_errmsg[512];
	//<! DRTP Handle
	int m_drtpHandle;
	//<! DRTP 请求的 CPACK 包
	ST_CPACK m_requestPack;
	//<! DRTP 应答的 CPACK 包
	ST_CPACK m_responsePack;
	//<! DRTP 缓存 buffer
	BYTE m_drtpBuf[8192];
	//<! DRTP 返回时保存的 CPACK 数组
	ST_PACK	m_dataArray[100];
	//<! 游标指针
	ST_PACK* m_currRecord;
	//<! 当前的游标的 index
	int m_currIndex;
	//<! DRTP 返回记录数
	int m_currRecordCount;
	//<! DRTP 操作的超时时间
	int m_timeout;
	//<! 错误代码
	int m_errcode;
	//! 初始化取后继数据包请求的CPACK包
	void SetNextRequest();
	//<! 日志输出 DRTP 错误信息
	void logDrtpErrMsg()
	{
		ACE_DEBUG((LM_ERROR,"DRTP请求失败，返回码[%d]信息[%s]",m_errcode
			,m_errmsg));
	}
	int testDrtpHandle();
public:
	//! constructor
	/*
	 \param ip DRTP 服务器IP
	 \param prot DRTP 服务器端口
	 \param funcno DRTP 服务主功能号
	 */
	CDRTPHelper(const char* ip,int port,int funcno,int drtp_no);
	//! destructor
	~CDRTPHelper(void);
	//! 申请Drtp连接
	int Connect(void);
	//! 重置
	void Reset(void);
	//! 设置请求包头信息
	void SetRequestHeader(int funcno, int first = 1);
	//! 设置 CPACK 字段值
	void AddField(int field,const char * value,int len = -1);
	void AddField(int field,int value);
	void AddField(int field,long value);
	void AddField(int field,unsigned long value);
	void AddField(int field,float value);
	void AddField(int field,double value);
	//! 发送请求，并接收返回信息
	/*!
	 \param timeout 超时时间，单位为毫秒, 默认为 100
	 */
	int SendRequest(int timeout = 100);
	//! DRTP 调用的错误信息
	std::string GetErrMsg();
	//! DRTP 调用后由应用服务器返回的错误码
	int GetReturnCode();
	//! DRTP 调用后由应用服务器返回的信息
	std::string GetReturnMsg();
	//! 判断是否有更多 CPACK 包
	bool HasMoreRecord();
	//! 取得当前游标指向的 CPACK ，然后指向下一条CPACK
	ST_PACK* GetNextRecord();
	//! 关闭 DRTP 连接
	void Close();
	//////////////////////////////////////////////////////////////////////////
	//! 初始化 DRTP 资源
	static int InitDrtp();
	//! 释放DRTP 资源
	static void UninitDrtp(); 
};

class DrtpConnectException : public std::exception
{

};
#endif // _DRTPHELPER_H_

