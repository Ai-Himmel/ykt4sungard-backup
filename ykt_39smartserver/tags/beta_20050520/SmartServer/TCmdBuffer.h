// TCmdBuffer.h: interface for the TCmdBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCMDBUFFER_H__6190A635_CD4D_47EC_9002_BF1A7225B2AA__INCLUDED_)
#define AFX_TCMDBUFFER_H__6190A635_CD4D_47EC_9002_BF1A7225B2AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const CMD_BUFFER_SIZE = 320 ;

enum 
{
	SMART_CMD_SEND ,
	SMART_CMD_RECV ,
	SMART_CMD_SENDRECV
};

//*------------------------------------------------------------------------------------
//*名称: TCmdBuffer
//*功能: 终端设备的命令信息
//*------------------------------------------------------------------------------------
class TCmdBuffer : public TSCmdBuffer
{
public:
	TLock    m_lock;
	int      m_nCmdType;

	int             m_nRecvBytes;
	unsigned char  *m_pRetBuffer;
	int             m_nRetBuffer;

	DWORD           m_nTick1;
	DWORD           m_nTick2;

	bool            m_bFormat;

public:
	TCmdBuffer();
	virtual ~TCmdBuffer();

	void Release();
	void ZeroOutBuffer();
	void ZeroInBuffer();

	bool IsValid() const ;
	bool IsMustRecv() const;

	void CopyTo(TSCmdBuffer *pBuffer);
	void CopyBy(TSCmdBuffer *pCmdBuffer);
	void CopyOut(DWORD dwSize);

	void ZeroBuffer();

	bool CheckInPacket();
	long GetPackSize();

	void SetTick();
	bool IsTimeOutC1();
	bool IsTimeOutC2();

	bool IsValidHead() ;
	void FormatPacket();
};

#endif // !defined(AFX_TCMDBUFFER_H__6190A635_CD4D_47EC_9002_BF1A7225B2AA__INCLUDED_)
