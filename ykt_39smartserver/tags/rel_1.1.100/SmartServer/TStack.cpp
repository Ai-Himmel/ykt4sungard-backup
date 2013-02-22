// TStack.cpp: implementation of the TStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TStack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TStackNode::TStackNode(void *pData, TStackNode  *pNext)
{
	m_pNext = pNext ;
	m_pData = pData ;
}

TStackNode::~TStackNode()
{

}


TStack::TStack()
{
	m_nCurPos = 0 ;
	m_nMaxPos = 200 ;
	m_pHead = NULL ;
}

TStack::~TStack()
{
	Release();
}

void TStack::Release()
{
	m_lock.Lock();

	TStackNode *pNode = m_pHead ;
	while( pNode )
	{
		delete pNode;
		m_pHead = m_pHead->m_pNext ;
		pNode = m_pHead ; 
	}

	m_nCurPos = 0 ;
	m_pHead = NULL ;

	m_lock.Unlock();
}

void* TStack::Pop()
{
	if( IsEmpty() )
		return NULL ;

	m_lock.Lock();

	TStackNode *pNode = m_pHead;
	void *pData = pNode->m_pData ;

	m_pHead = m_pHead->m_pNext ;
	delete pNode;
	m_nCurPos--;

	m_lock.Unlock();

	return pData;
}

long TStack::Push(void *pData)
{
	if( IsFull() )
		return -1 ;

	m_lock.Lock();
	m_pHead = new TStackNode(pData, m_pHead);
	m_nCurPos++ ;
	m_lock.Unlock();

	return m_nCurPos;
}

bool TStack::IsEmpty()
{
	m_lock.Lock();

	if( m_pHead == NULL ) 
	{
		m_lock.Unlock();
		return true ;
	}
	else
	{
		m_lock.Unlock();
		return false;
	}
}

bool TStack::IsFull()
{
	bool bRet;

	m_lock.Lock();
	if( m_nCurPos <  m_nMaxPos )
		bRet = false ;
	else
		bRet = true ;

	m_lock.Unlock();

	return bRet;
}


TQueue::TQueue()
{
	pHead = NULL ;
	pTail = NULL ;
	nCount = 0 ;
}

TQueue::~TQueue()
{
	Release();
}

void TQueue::Release()
{
	lock.Lock();

	TQueueNode *pNode = pHead; 
	while( pNode )
	{
		delete pNode ;
		pHead = pHead->pNext ;
		pNode = pHead ;
	}
	nCount = 0 ;
	pTail = NULL ;
	lock.Unlock();
}

void* TQueue::Get()
{
	lock.Lock();

	if( pHead == NULL )
	{
		lock.Unlock();
		return NULL;
	}
	else
	{
		TQueueNode *pNode = pHead ;
		pHead = pHead->pNext ;
		nCount--;
		lock.Unlock();
		return pNode;
	}
}

long TQueue::Put(void *pvoid)
{
	if( IsFull() )
		return -1 ;

	lock.Lock();
	if( pHead == pTail )
	{
		pTail = new TQueueNode;
		pTail->pData = pvoid ;
		pTail->pNext = NULL ;
		pTail->pPrve = NULL ;
		pHead = pTail ;
	}
	else
	{
		TQueueNode *pNode = new TQueueNode ;
		pNode->pData = pvoid ;
		pNode->pNext = NULL ;
		pNode->pPrve = pTail ;
		pTail = pNode ;
	}
	nCount++ ;
	lock.Unlock();

	return 0L;
}

bool TQueue::IsEmpty() const
{
	if( nCount == 0 )
		return true;
	return false;
}

bool TQueue::IsFull() const
{
	lock.Lock();

	if( nCount >= MAX_QUEUE_SIZE )
	{
		lock.Unlock();
		return true ;
	}
	else
	{
		lock.Unlock();
		return false;
	}
}
