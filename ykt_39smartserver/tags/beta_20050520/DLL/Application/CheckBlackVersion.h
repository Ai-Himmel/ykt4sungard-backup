// CheckBlackVersion.h: interface for the CCheckBlackVersion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKBLACKVERSION_H__8985021C_B0E8_4C10_86C9_BACCC3AB71A5__INCLUDED_)
#define AFX_CHECKBLACKVERSION_H__8985021C_B0E8_4C10_86C9_BACCC3AB71A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCheckBlackVersion
{
public:
	static char sBlockVersion[32];   //黑名单的最新版本
	static char sBlockExpire[32];    //黑名单有效期
	static int  nBlackExpire;
	static int  nBlackCount;

protected:
	long CheckBlackExpire(long nDatabase, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long n);
	long DownCardID(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int n, long nRec, char* strLastVer, long& nCardID);
	long GetParam(long nDatabase);
	CString GetSmartCardSQL(CString strDate1, CString strDate2);

public:
	CCheckBlackVersion();
	virtual ~CCheckBlackVersion();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessCheck(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long SignInDown(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	static unsigned char GetInt(unsigned char *pszString, int Len);
	static long UnMakeDeviceBufferEx(TSCmdBuffer *pBuffer);
	static long OpenQuery(long nDatabase, CString strSQL);
	static void GetNowTime(char *pszDateTime, bool bBool);

};

#endif // !defined(AFX_CHECKBLACKVERSION_H__8985021C_B0E8_4C10_86C9_BACCC3AB71A5__INCLUDED_)
