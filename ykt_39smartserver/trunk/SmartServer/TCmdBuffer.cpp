// TCmdBuffer.cpp: implementation of the TCmdBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCmdBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCmdBuffer::TCmdBuffer()
{
	m_nRecvBytes = 0  ;
	m_nCmdType = SMART_CMD_SENDRECV;

	nBufferSize  = CMD_BUFFER_SIZE ;
	m_nRetBuffer = CMD_BUFFER_SIZE ;

	pBuffer = (BYTE*)new char[nBufferSize];
	m_pRetBuffer = (BYTE*)new char[m_nRetBuffer];

	nCmdSize  = 0 ;
	nTimeOut1 = 50 ;
	nTimeOut2 = 100 ;

	if( pBuffer == NULL || m_pRetBuffer == NULL )
		throw TException("内存不足!", GetLastError());

	ZeroInBuffer();
	ZeroOutBuffer();
}

TCmdBuffer::~TCmdBuffer()
{
	Release();
}

void TCmdBuffer::Release()
{
	if( pBuffer != NULL )
	{
		delete [] pBuffer;
		pBuffer = NULL ;
	}
}

void TCmdBuffer::ZeroOutBuffer()
{
	ZeroMemory(pBuffer, nBufferSize);
}

void TCmdBuffer::ZeroInBuffer()
{
	ZeroMemory(m_pRetBuffer, m_nRetBuffer);
}

bool TCmdBuffer::IsValid() const
{
	return false;
}

bool TCmdBuffer::IsMustRecv() const
{
	return (m_nCmdType==SMART_CMD_SEND?false:true);
}

void TCmdBuffer::CopyTo(TSCmdBuffer *pCmdBuffer)
{
	memcpy(pCmdBuffer->pBuffer, m_pRetBuffer, nBufferSize);
	pCmdBuffer->nCmdSize = m_nRecvBytes;
}

void TCmdBuffer::CopyBy(TSCmdBuffer *pCmdBuffer)
{
	ZeroInBuffer();
	ZeroOutBuffer();

	memcpy(pBuffer, pCmdBuffer->pBuffer, nBufferSize);
	nCmdSize = pCmdBuffer->nCmdSize ;
	nTimeOut1 = pCmdBuffer->nTimeOut1;
	nTimeOut2 = pCmdBuffer->nTimeOut2;
}

void TCmdBuffer::CopyOut(DWORD dwSize)
{
	ZeroOutBuffer();
	nCmdSize = (int)dwSize ;
	if(nCmdSize>CMD_BUFFER_SIZE) 
	{
		memcpy(pBuffer, m_pRetBuffer, CMD_BUFFER_SIZE);
	}
	else memcpy(pBuffer, m_pRetBuffer, nCmdSize);
}

void TCmdBuffer::ZeroBuffer()
{
	m_nRecvBytes = 0 ;
	nCmdSize = 0 ;
	nTimeOut1 = 0 ;
	nTimeOut2 = 0 ;

	m_nTick1 = 0 ;
	m_nTick2 = 0 ;

	ZeroInBuffer();
	ZeroOutBuffer();
}

bool TCmdBuffer::CheckInPacket()
{
	if( m_nRecvBytes < (long)SmartProtocol.nMinPKSize || 
		m_nRecvBytes > (long)SmartProtocol.nMaxPKSize )
	{
		return false;
	}

	if( m_pRetBuffer[0] != SmartProtocol.PTHead[0] || 
		m_pRetBuffer[m_nRecvBytes-1] != SmartProtocol.PTTail[0] ) 
	{
		return false;
	}

	return true;
}

//检测包头长度
long TCmdBuffer::GetPackSize()
{
	int nPos = SmartProtocol.nLenOffset + 1;
	if( nPos > m_nRecvBytes )
		return -1;

 	return m_pRetBuffer[nPos-1];
}

bool TCmdBuffer::IsTimeOutC1()
{
	if( nTimeOut1 <= 0 ) nTimeOut1 = 50 ;
	DWORD i = GetTickCount() - m_nTick1 - 2 ;
	if( (long)i > nTimeOut1 )
	{
		return true ;
	}
	return false;
}

bool TCmdBuffer::IsTimeOutC2()
{
	if( nTimeOut2 <= 0 ) nTimeOut2 = 1000 ;
	DWORD i = GetTickCount() - m_nTick2 - 2 ;
	if( (long)i > nTimeOut2 )
	{
		return true ;
	}
	return false;
}

bool TCmdBuffer::IsValidHead()
{
	if( m_nRecvBytes < SmartProtocol.PTHeadLen ) 
	{
		m_nRecvBytes = 0 ;
		return false;
	}

	if( m_pRetBuffer[0] != SmartProtocol.PTHead[0] )
	{
		m_nRecvBytes = 0 ;
		return false;
	}

	return true;
}

void TCmdBuffer::FormatPacket()
{
	if( !IsValidHead() )
	{
		unsigned char sBuffer[CMD_BUFFER_SIZE];
		long k=0;
		bool bFlag = false ;

		memcpy(sBuffer, m_pRetBuffer, m_nRetBuffer);
		memset(m_pRetBuffer, 0, m_nRetBuffer);

		for(long i=0; i< m_nRecvBytes; i++)
		{
			if( sBuffer[i] == SmartProtocol.PTHead[0] ) 
				bFlag = true ;

			if( bFlag )
			{
				m_pRetBuffer[k] = sBuffer[i];
				if( m_pRetBuffer[k++] == SmartProtocol.PTTail[0] ) 
					break;
			}
		}

		m_nRecvBytes = k ;
	}
	return ;
}
