#ifndef _DRTPHELPER_H_
#define _DRTPHELPER_H_

#pragma once


#include "CPack.h"

class CDRTPHelper
{
private:
	CString m_serverIP;
	int m_serverPort;
	int m_funcNo;
	int m_requestType;
	char m_errmsg[512];
	HANDLE m_drtpHandle;
	ST_CPACK m_requestPack;
	BYTE m_drtpBuf[8192];
	ST_PACK	m_dataArray[100];
	ST_PACK* m_currRecord;
	int m_currIndex;
	int m_currRecordCount;
	int m_timeout;
	void SetNextRequest();
public:
	CDRTPHelper(CString ip,int port,int funcno);
	~CDRTPHelper(void);
	// 申请Drtp连接
	int Connect(void);
	// 重置
	void Reset(void);
	// 设置请求包头信息
	void SetRequestHeader(int funcno, int first);
	void AddField(int field,char * value);
	void AddField(int field,int value);
	void AddField(int field,float value);
	void AddField(int field,double value);
	int SendRequest(int timeout = 10);
	CString GetErrMsg();
	int GetReturnCode();
	CString GetReturnMsg();
	bool HasMoreRecord();
	ST_PACK* GetNextRecord();
	void Close();
	//////////////////////////////////////////////////////////////////////////
	
	static int InitDrtp();
	static void UninitDrtp(); 
};

#endif // _DRTPHELPER_H_