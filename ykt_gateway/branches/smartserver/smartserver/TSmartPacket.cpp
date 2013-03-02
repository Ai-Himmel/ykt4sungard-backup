// TSmartPacket.cpp: implementation of the TSmartPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartPacket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSmartPacket::TSmartPacket()
{
	m_nLength = 0 ;
	ZeroMemory(m_Buffer, sizeof(m_Buffer));
}

TSmartPacket::~TSmartPacket()
{

}

void TSmartPacket::CreateNotify(int nType, TSSmartDoc *pDoc, void *pvoid, long nLen)
{
	if( nType == MSG_WARNING )
		Create(PACKET_CMD_WARNING, SERVER_SID);
	else if( nType == MSG_ERROR )
		Create(PACKET_CMD_ERROR, SERVER_SID);
	else
		Create(PACKET_CMD_DATA, SERVER_SID);

	if( pDoc == NULL )
		AddItem(0);
	else
		AddItem(pDoc->m_nAuthID);

	AddItem((char*)pvoid, nLen);
	AddEnd();
}

void TSmartPacket::Create(char *pCmd, long nSID)
{
	ZeroMemory(m_Buffer, sizeof(m_Buffer));

	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	pPacket->Begin = PACKET_BEGIN ;
	strcpy(pPacket->Version, "10");

	sprintf(pPacket->SID, "%8d", nSID);
	sprintf(pPacket->Cmd, "%8s", pCmd);
	sprintf(pPacket->Length, "%08d", 0);
	sprintf(pPacket->Result, "%08d", 0);

	m_nLength = sizeof(TSSmartPacket);
}

void TSmartPacket::SetResult(long nResult)
{
	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	sprintf(pPacket->Result, "%08d", nResult);
}

void TSmartPacket::AddItem(char *pItem, int nLen)
{
	if( (m_nLength + nLen + 1) > MAX_PACKET_SIZE )
		return ; //throw TException("通讯包超长!");

	strcat(m_Buffer+m_nLength, pItem);
	m_nLength += nLen ;

	m_Buffer[m_nLength++] = PACKET_SPLITTER;
	m_Buffer[m_nLength] = 0 ;

	int k=0;
	char szTemp[16];
	long nDataLength = m_nLength - 1 - sizeof(TSSmartPacket);
	sprintf(szTemp, "%08d", nDataLength);
	for(int i= 19 ; i< 19+8; i++ )
	{
		m_Buffer[i] = szTemp[k++];
	}
}

void TSmartPacket::AddItem(long nItem)
{
	char  sItem[32];

	sprintf(sItem, "%d", nItem);
	AddItem(sItem, strlen(sItem));
}

void TSmartPacket::AddItem(int nItem)
{
	char  sItem[32];

	sprintf(sItem, "%d", nItem);
	AddItem(sItem, strlen(sItem));
}

void TSmartPacket::AddItem(float nItem)
{
	char  sItem[32];

	sprintf(sItem, "%f", nItem);
	AddItem(sItem, strlen(sItem));
}

void TSmartPacket::AddEnd()
{
	if( m_nLength == sizeof(TSSmartPacket) )
	{
		m_Buffer[m_nLength++] = PACKET_END;
		m_Buffer[m_nLength] = 0 ;
	}
	else
	{
		if( m_Buffer[m_nLength-1] == PACKET_SPLITTER )
		{
			m_Buffer[m_nLength-1] = PACKET_END;
			m_Buffer[m_nLength] = 0 ;
		}
		else
		{
			m_Buffer[m_nLength-1] = PACKET_END;
			m_Buffer[m_nLength] = 0 ;
		}
	}
}

long TSmartPacket::GetDataLength()
{
	static char szCmd[9];
	memset(szCmd, 0, sizeof(szCmd));

	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	strncpy(szCmd, pPacket->Length, 8);
	return atoi(szCmd);
}

long TSmartPacket::GetSID()
{
	static char szCmd[9];
	memset(szCmd, 0, sizeof(szCmd));

	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	strncpy(szCmd, pPacket->SID, 8);
	return atoi(szCmd);
}

char* TSmartPacket::GetCmd()
{
	static char szCmd[8];

	memset(szCmd, 0, sizeof(szCmd));

	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	int k=0;
	for(int i=0; i< 8; i++)
	{
		if( pPacket->Cmd[i] != ' ' ) 
		{
			szCmd[k] = pPacket->Cmd[i];
			if( szCmd[k++] == '\0' )
				break;
		}
	}

	return szCmd;
}

char* TSmartPacket::GetDataBuffer()
{
	return (char*)(m_Buffer+sizeof(TSSmartPacket));
}

bool TSmartPacket::IsValid(long nLength)
{
	if( nLength < sizeof(TSSmartPacket)+1 )
		return false;

	//包版本及开始符.结束符不对
	TSSmartPacket *pPacket = (TSSmartPacket*)m_Buffer;
	if( pPacket->Begin != PACKET_BEGIN || 
		m_Buffer[nLength-1] != PACKET_END || 
		pPacket->Version[0] < '1' )
	{
		return false;
	}

	//包长度错
	long nPackLen = GetDataLength()+sizeof(TSSmartPacket)+1;
	if( nPackLen != nLength )
		return false;

	m_nLength = nLength;

	return true;
}

long TSmartPacket::GetItemCount()
{
	if( m_nLength == sizeof(TSSmartPacket) + 1 )
		return 0L;

	long nPos = sizeof(TSSmartPacket);
	long nCount = 0 ;

	while( nPos < m_nLength )
	{
		if( m_Buffer[nPos] ==  PACKET_SPLITTER || 
			m_Buffer[nPos] ==  PACKET_END )
		{
			nCount++;
		}
		nPos++;
	}

	return nCount;
}

bool TSmartPacket::GetItem(long nIndex, char *pItem)
{
	if( nIndex < 0 || nIndex >= GetItemCount() )
		return false;

	long nPos = sizeof(TSSmartPacket);
	long nCount = 0 ;
	long i = 0 ;

	while( m_Buffer[nPos] != PACKET_END && 
		   nPos < MAX_PACKET_SIZE && 
		   nCount <= nIndex )
	{
		if( m_Buffer[nPos] ==  PACKET_SPLITTER || 
			m_Buffer[nPos] ==  PACKET_END )
		{
			nCount++;
		}
		else
		{
			if( nCount == nIndex )
			{
				pItem[i++] = m_Buffer[nPos];
			}
		}
		nPos++;
	}

	pItem[i] = 0 ;

	return true;
}

bool TSmartPacket::GetItem(long nIndex, long& nItem)
{
	char  sItem[32];

	memset(sItem, 0, sizeof(sItem));
	if( GetItem(nIndex, sItem) )
	{
		nItem = atoi(sItem);
		return true;
	}
	return false;
}

bool TSmartPacket::GetItem(long nIndex, int& nItem)
{
	char  sItem[32];

	memset(sItem, 0, sizeof(sItem));
	if( GetItem(nIndex, sItem) )
	{
		nItem = atoi(sItem);
		return true;
	}
	return false;
}

bool TSmartPacket::GetItem(long nIndex, float& nItem)
{
	char  sItem[32];

	memset(sItem, 0, sizeof(sItem));

	if( GetItem(nIndex, sItem) )
	{
		nItem = (float)atof(sItem);
		return true;
	}
	return false;
}

