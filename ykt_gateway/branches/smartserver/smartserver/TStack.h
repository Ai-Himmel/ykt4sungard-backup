// TStack.h: interface for the TStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSTACK_H__8EB71A2D_FCF1_4F4E_AE57_1ABAD00DAD96__INCLUDED_)
#define AFX_TSTACK_H__8EB71A2D_FCF1_4F4E_AE57_1ABAD00DAD96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//************************************************************************************
//*名称: TStackNode
//*功能: 栈结点
//************************************************************************************
class TStackNode
{
public:
	TStackNode  *m_pNext;
	void        *m_pData;

public:
	TStackNode(void *pData, TStackNode  *pNext);
	virtual ~TStackNode();

};

//************************************************************************************
//*名称: TStackNode
//*功能: 栈结构
//************************************************************************************
class TStack
{
protected:
	TLock    m_lock;
	int      m_nMaxPos;
	int      m_nCurPos;

	TStackNode  *m_pHead;

public:
	TStack();
	virtual ~TStack();

	void* Pop();
	long Push(void *pData);

	bool IsEmpty() ;
	bool IsFull() ;

	void Release();
};

//************************************************************************************
//*名称: TQueueNode
//*功能: 队列节点
//************************************************************************************
class TQueueNode
{
public:
	void       *pData;
	TQueueNode *pNext;
	TQueueNode *pPrve;

public:
	TQueueNode()
	{
		pData = NULL ;
		pNext = NULL ;
		pPrve = NULL ;
	}

	virtual ~TQueueNode() { }
};

//************************************************************************************
//*名称: TQueue
//*功能: 队列
//************************************************************************************
class TQueue
{
public:
	TQueueNode   *pHead;
	TQueueNode   *pTail;
	TLock         lock;
	long          nCount;

public:
	TQueue();
	virtual ~TQueue();

	void Release();

	void* Get();
	long Put(void *pvoid);

	bool IsEmpty() const ;
	bool IsFull() const ;
};

#endif // !defined(AFX_TSTACK_H__8EB71A2D_FCF1_4F4E_AE57_1ABAD00DAD96__INCLUDED_)
