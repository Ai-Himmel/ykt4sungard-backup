#pragma once

#include <string>
#include <map>
#include "kbclt.h"

typedef std::map<std::string,std::string> FIELDMAP;

class CKdbc
{
public:
	
	static int s_init_ok;
	static void kdbc_uninit();

	CKdbc(void);
	~CKdbc(void);
	void SetReqNo(int reqNo)
	{
		m_reqNo = reqNo;
	}
	void SetReqField(FIELDMAP *reqMap)
	{
		m_reqMap = reqMap;
	}
	int GetReqValue(FIELDMAP *resMap,int tryFlag = 0);
private:
	char eMsg[1024];  // 注意尽量给出缓存为 >=1024字节
	char fvalue[1024]; // 注意必须给出缓存为 >=1024字节
	KBDCHandle ch;
	int m_reqNo;
	FIELDMAP *m_reqMap;

	static CRITICAL_SECTION s_handle_lock;
	static int alloc_new_handle(CKdbc * kdbc);
	static int free_handle(CKdbc *kdbc);
	static int kdbc_init();
	
};
