// TSmartPacket.h: interface for the TSmartPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTPACKET_H__8B6E46CE_6565_45AF_A372_35F82DD2C7B0__INCLUDED_)
#define AFX_TSMARTPACKET_H__8B6E46CE_6565_45AF_A372_35F82DD2C7B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int MAX_PACKET_SIZE = 1024;
//*---------------------------------------------------------------------------
//*名称: TSmartPacket
//*功能: 协议包头
//*---------------------------------------------------------------------------
class TSmartPacket
{
public:
	char            m_Buffer[MAX_PACKET_SIZE];
	long            m_nLength;

protected:
	virtual void Encrypt(char *pInBuffer, char *pOutBuffer, long& nSize) { };
	virtual void Uncrypt(char *pInBuffer, char *pOutBuffer, long& nSize) { };

public:
	TSmartPacket();
	virtual ~TSmartPacket();

	void CreateNotify(int nType, TSSmartDoc *pDoc, void *pvoid, long nLen);
	void Create(char *pCmd, long nSID);

	void SetResult(long nResult);

	void AddItem(char *pItem, int nLen);
	void AddItem(long nItem);
	void AddItem(int nItem);
	void AddItem(float nItem);
	void AddEnd();

	long GetItemCount();
	bool GetItem(long nIndex, char *pItem);
	bool GetItem(long nIndex, long& nItem);
	bool GetItem(long nIndex, int& nItem);
	bool GetItem(long nIndex, float& nItem);

	char* GetBuffer() const { return (char*)m_Buffer; }
	char* GetDataBuffer();
	long  GetLength() const { return m_nLength; }
	long  GetDataLength();
	long  GetSID();
	char* GetCmd();
	bool IsValid(long nLength);
};

#endif // !defined(AFX_TSMARTPACKET_H__8B6E46CE_6565_45AF_A372_35F82DD2C7B0__INCLUDED_)
