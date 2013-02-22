// ConnectPool.cpp: implementation of the CConnectPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"
#include "ConnectPool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CConnectPool ConnectPool;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConnectPool::CConnectPool()
{
	strcpy(m_szHost, "");
	m_nPort = 0 ;
	m_nEncode = 0 ;
	for(int i=0;i<128;i++)
	{
		m_Node[i].hHandle = NULL;
		m_Node[i].nStatus = DRTP_CLOSE;
	}
}

CConnectPool::~CConnectPool()
{
	DestroyPool();
}

//*********************************************************************
//*����: bool CConnectPool::Initialized(long nConnect, char *pszHost, int nPort, int nEncode)
//*����: ��ʼ���������. 
//*���: pszHost  ---  ������ַIP
//*      nPort    ---  SOCKET�˿�
//*      nEncode  ---  EndCode��
//*      nConnect ---  ��������
//*����: �ɹ����
//*����: 2004-10-15  zhangwei
//*********************************************************************
bool CConnectPool::Initialized(long nConnect, char *pszHost, int nPort, int nEncode)
{
	strcpy(m_szHost, pszHost);
	m_nPort = nPort;
	m_nEncode = nEncode;
	m_nConnectNo = nConnect;
	printf("------��ʼ׼������˴�ͨ��ƽ̨��������------\n");
	for(int i=0; i<nConnect; i++)
	{
		printf("����ǰ�ó�������˴�ͨ��ƽ̨������%d������------n",i+1);
		m_Node[i].hHandle = DRTPConnect(pszHost, (WORD)nPort, (WORD)nEncode);
		if( m_Node[i].hHandle == NULL )
		{
			printf("ʧ��!\n");
			printf("ǰ�ó����޷���������,����ϵ ϵͳ����Ա!!!!!\n");
			DestroyPool();
			return false;
		}
		else
		{
			printf("�ɹ�!\n");
			m_Node[i].nStatus = DRTP_FREE ;
		}
	}

	return true;
}



//*********************************************************************
//*����: void CConnectPool::DestroyPool()
//*����: �������ӳ�
//*���: ��
//*����: ��
//*����: 2004-10-15  zhangwei
//*˵��: �˳�ʱ����
//*********************************************************************
void CConnectPool::DestroyPool()
{
	//for(;;)
	//{
		//printf("���ԶϿ�����˴�ͨ��ƽ̨������-------\n");
		m_hSection.Lock();
		for(int i=0;i<m_nConnectNo;i++)
		{
			//m_Node[i].hSection.Lock();
			if(m_Node[i].hHandle  !=  NULL )
					DRTPClose(m_Node[i].hHandle);
			//m_Node[i].hSection.Unlock();
		}
		m_hSection.Unlock();
	//}
}

//*********************************************************************
//*����: bool CConnectPool::ReConnect(HANDLE& hHandle)
//*����: ��ָ������������
//*���: ��
//*����: �ɹ����
//*����: 2004-10-15  zhangwei
//*˵��: ������Ͽ�ʱ����, ����������û������ǩ��!!!
//*********************************************************************
bool CConnectPool::ReConnect(HANDLE& hHandle)
{
	if( hHandle == NULL )
		return false;

	HANDLE hOld = hHandle;

	//����
	hHandle = DRTPConnect(m_szHost, (WORD)m_nPort, (WORD)m_nEncode);
	
	if( hHandle == NULL )
	{
		hHandle = hOld;
		WriteLog("�Զ�������ʧ��!!!!.\n");
		return false;
	}
	else
	{
		//�رվɾ��
		if( hOld != NULL )
		{
			DRTPClose(hOld);
		}
	}

	return true;
}

//*********************************************************************
//*����: bool CConnectPool::ReConnect()
//*����: �Ͽ�����
//*���: ��
//*����: �ɹ����
//*����: 2004-10-15  zhangwei
//*˵��: ������Ͽ�ʱ����, ����������û������ǩ��!!!
//*********************************************************************
bool CConnectPool::ReConnect()
{
	printf("----����ǰ�ó����������˴�ͨ��ƽ̨----\n");
	m_hSection.Lock();
	for(int i=0; i<m_nConnectNo; i++)
	{
		//m_Node[i].hSection.Lock();
		if( m_Node[i].hHandle != NULL )
		{
				DRTPClose(m_Node[i].hHandle);
				m_Node[i].hHandle = NULL ;
		
				m_Node[i].hHandle = DRTPConnect(m_szHost, (WORD)m_nPort, (WORD)m_nEncode);
				if( m_Node[i].hHandle == NULL )
				{
					m_Node[i].nStatus = DRTP_CLOSE;
					printf("��������ʧ��!\n");
					//m_Node[i].hSection.Unlock();
					m_hSection.Unlock();
					return false;
				}
			}
	}
	m_hSection.Unlock();

	return true;
}

//*********************************************************************
//*����: HANDLE CConnectPool::Alloc(int nTime)
//*����: �����ӹ�����з���һ������
//*���: nTime -- ʧ�����Դ���
//*����: ���Ӿ��
//*����: 2004-10-15  zhangwei
//*˵��: ��
//*********************************************************************
HANDLE CConnectPool::Alloc(int nTime)
{
	m_hSection.Lock();
	for(int i=0;i<m_nConnectNo;i++)
	{
		//m_Node[i].hSection.Lock();
		if(m_Node[i].hHandle != NULL && m_Node[i].nStatus == DRTP_FREE)
		{
			m_Node[i].nStatus = DRTP_ALLOC;
			//m_Node[i].hSection.Unlock();
			m_hSection.Unlock();
			return m_Node[i].hHandle;
		}
		//m_Node[i].hSection.Lock();

	}
	m_hSection.Unlock();
	return NULL;
}

//*********************************************************************
//*����: HANDLE CConnectPool::AllocEx(BOOL bMonitor)
//*����: �����ӹ�����з���һ������
//*���: bMonitor -- TRUE: �ǴӼ�������з��䣬FALSE:�ӹ��������з���
//*����: ���Ӿ��
//*����: 2004-10-15  zhangwei
//*˵��: ��
//*********************************************************************
HANDLE CConnectPool::AllocEx(BOOL bMonitor)
{
	return NULL;
}

//*********************************************************************
//*����: void CConnectPool::Free(HANDLE hHandle)
//*����: �ͷ�һ�����ӵ����ӹ����
//*���: hHandle -- ���Ӿ��
//*����: ��
//*����: 2004-10-15  zhangwei
//*˵��: ��
//*********************************************************************
void CConnectPool::Free(HANDLE hHandle)
{
	m_hSection.Lock();
	for(int i=0; i< 128; i++)
	{
		//m_Node[i].hSection.Lock();
		if( m_Node[i].hHandle != NULL && m_Node[i].hHandle == hHandle )
		{
			m_Node[i].nStatus  = DRTP_FREE;
			//m_Node[i].hSection.Unlock();
			m_hSection.Unlock();
			return;
		}
		//m_Node[i].hSection.Unlock();
	}
	m_hSection.Unlock();

}