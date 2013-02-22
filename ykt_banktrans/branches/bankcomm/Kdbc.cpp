#include "StdAfx.h"
#include ".\kdbc.h"

int CKdbc::s_init_ok = CKdbc::kdbc_init();
CRITICAL_SECTION CKdbc::s_handle_lock;
//char CKdbc::eMsg[] = "";

int CKdbc::kdbc_init()
{
	char msg[1024] = "";
#ifdef _DEBUG
	if (KBDCInit(1,"",msg)<0)
#else
	if (KBDCInit(0,"",msg)<0)
#endif
	{
		printf("KBDCInit Error:%s\n",msg);
		return -1;
	}
	InitializeCriticalSection(&s_handle_lock);
	return 0;
}

void CKdbc::kdbc_uninit()
{
	if(s_init_ok)
		return;
	DeleteCriticalSection(&s_handle_lock);
	KBDCExit();
}
int CKdbc::alloc_new_handle(CKdbc * kdbc)
{
	int ret = -1;
	if( s_init_ok )
		return -1;

	EnterCriticalSection(&s_handle_lock);
	kdbc->ch = KBDCNewHandle(kdbc->eMsg);

	if (kdbc->ch==NULL)
		printf("KBDCNewHandle Error:%s\n",kdbc->eMsg);	
	else
		ret = 0;

	LeaveCriticalSection(&s_handle_lock);
	return ret;
}
int CKdbc::free_handle(CKdbc *kdbc)
{
	if( s_init_ok)
		return -1;
	if(kdbc->ch == NULL) 
		return 0;

	EnterCriticalSection(&s_handle_lock);
	KBDCDeleteHandle(kdbc->ch);
	LeaveCriticalSection(&s_handle_lock);
	return 0;
}
CKdbc::CKdbc(void):ch(NULL),m_reqNo(0),m_reqMap(NULL)
{
	///////////////////////////////// Begin1 //////////////////////////////////////
	// 以下这个函数必须在主线程内，启用其他函数之前调用，并且必须为成功才行
	alloc_new_handle(this);
}

CKdbc::~CKdbc(void)
{
	free_handle(this);
}

int CKdbc::GetReqValue(FIELDMAP *resMap,int tryFlag)
{
	int trycnt = 3,ret = 0;
	if (m_reqMap == NULL || resMap ==NULL || m_reqNo <= 0)
		return -1;
	if(ch == NULL)
	{
		if(alloc_new_handle(this))
			return -1;
	}
	
	if(KBDCBeginRequest(ch,m_reqNo,eMsg) < 0)
	{
		printf("KBDCBeginRequest Error :%s",eMsg);
		return -1;
	}
	
	FIELDMAP::iterator mapIter;
	for (mapIter = m_reqMap->begin();mapIter != m_reqMap->end();mapIter++)
	{
		KBDCSetFieldValue(ch,mapIter->first.c_str(),mapIter->second.c_str()); 
	}	
	
	if (tryFlag)			//可以重试
	{	
		while(trycnt--)
		{
			if((ret = KBDCCallSvr(ch,5000,eMsg))>=0)
				break;
		}
		if(trycnt<= 0 && ret <0)
		{
			printf("KBDCCallSvr Error:%s\n",eMsg);
			free_handle(this);
			ch = NULL;
			return -1;
		}
	}
	else
	{
		if(KBDCCallSvr(ch,5000,eMsg)<0)
		{
			printf("KBDCCallSvr Error:%s\n",eMsg);
			free_handle(this);
			ch = NULL;
			return -1;
		}
	}
	
	do {
		if (KBDCGetFieldValue(ch,"vsmess",fvalue,eMsg)<0)
		{
			printf("KBDCGetFieldValue Fail : %s\n",eMsg);
			return -1;  // 一般是因为字段名错，或 无指定的应答记录数据
		}
		if(KBDCGetRetCode(ch))
			return -1;
		for (mapIter = resMap->begin();mapIter != resMap->end();mapIter++)
		{
			KBDCGetFieldValue(ch,mapIter->first.c_str(),fvalue,eMsg);
			mapIter->second = fvalue;
		}
				
	} while(KBDCNextRetRecord(ch,eMsg)>=0);

	return 0;	
}
