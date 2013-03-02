// XPData.h: interface for the CBCXPData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPDATA_H__62E1F7F5_3989_4665_AD1A_588CD603F9F6__INCLUDED_)
#define AFX_XPDATA_H__62E1F7F5_3989_4665_AD1A_588CD603F9F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "XPack.h"
#include "cxpack.h"

#define MAXERRMSGLENGTH 1024
#define MAXENCODEBUFSIZE 8192
#define MAXROWS 100

class CBCXPData  
{
public:
   //int m_xpno;   // 为XPack数组的编号 -1:表示本实例没有被使用
   CXPack *    m_pXPack; 
   ST_PACKHEAD m_head;
   ST_PACK     m_packs[MAXROWS+1];
   ST_HOOK     m_lasthook;  // 为了保存上次请求的上下文关联数据
   unsigned int m_userdata;  // 为了保证接收到的应答和请求对应上。2008-3-6 16:41:55

#define XPD_CLTID 20060823
   int m_iClassID;   // 作为本类的标识

private:
   int m_drtpno;
   int m_branchno;
   int m_funcno;

public:
	bool IsValidColumn(char *fieldname);
	bool SetRawRecord(int row,void * RawData, unsigned short RawDataLength);
	bool Broad(int drtpno, int destno, int funcno, int &errcode, char *errmsg);
	int EmulateMaxRows();
	bool GetFieldInfo(int col, char *name,int &type,int &length);
	bool CallNext(int timeout, int &errcode, char *errmsg);
	bool CallRequest(int drtpno, int branchno, int function, int timeout, int &errcode, char *errmsg);
	bool HaveNextPack();
	int GetFieldColumn(char *fieldname);
	bool IsValidColumn(int col);
	int GetMaxColumn();
	ST_SDPACK * GetRawRecord(int row);
	bool SetRawRecord(int row, ST_SDPACK *psd);
	int GetXPackType();
	bool SetMaxRetCount(int maxretcount);
	bool ResetPackHead();
	bool SetRecordCount(int recordcount);
	int GetBranchNoForNext();
	int GetPrivateFunctionForNext();
	bool DecodeXPack(const char *buf, int buflen);
	int EncodeXPackForNext(char *buf, int bufsize);
	int EncodeXPackForRequest(char *buf, int bufsize);
	long GetRetCode();
	int GetRecordCount();
	bool IsEof();
	bool SetRequestType(int reqtype);
	bool SetStringField(int row, const char *fieldname, const char *value);
	bool SetStringField(int row, int col, const char *value);
	bool SetDoubleField(int row, const char *fieldname, double value);
	bool SetDoubleField(int row, int col, double value);
	bool SetIntField(int row, const char *fieldname, long value);
	bool SetIntField(int row, int col, long value);
	bool GetStringField(int row, const char *fieldname, char *value);
	bool GetDoubleField(int row, const char *fieldname,double *value);
	bool GetIntField(int row, const char *fieldname,long *value);
	bool GetStringField(int row,int col,char *value);
	bool GetDoubleField(int row,int col,double *value);
	bool GetIntField(int row, int col, long *value);
	int GetFieldType(char *fieldname);
	int GetFieldType(int Col);
	CXPack * GetXPack();
	void Reset();
	CBCXPData();
	virtual ~CBCXPData();

private:
	int CLISendReceive(int drtpno,int branchno,int function,int timeout,char *buf,int buflen,char *errmsg);

};

typedef CBCXPData * BCHANDLE;
#endif // !defined(AFX_XPDATA_H__62E1F7F5_3989_4665_AD1A_588CD603F9F6__INCLUDED_)
