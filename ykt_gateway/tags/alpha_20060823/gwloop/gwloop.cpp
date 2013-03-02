// gwloop.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "gwloop.h"
#include <stdio.h>


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

GWLOOP_API int __stdcall Initialize()
{
	return 0;
}
//! �ͷ���Դ����,ϵͳ�����˳�ʱ�Զ�����,��ϵͳ�ڲ������˳�ʱ��һ������.
GWLOOP_API int __stdcall Uninitialize()
{
	return 0;
}
//! ����������
GWLOOP_API int __stdcall ProcessRequest(int request_no,request_pack * pack)
{
	/*
	pack->outdatalen = 0;
	return 0;
	*/
	int ret;
	if(request_no == 847205)
	{
		pack->outdatalen = sprintf(pack->outdata,"%s",
			"<YKT_DATA><DORM_NAME>����10��¥116��</DORM_NAME></YKT_DATA>");
		ret = 0;
	}
	else if(request_no == 847206)
	{
		pack->outdatalen = sprintf(pack->outdata,"%s"
			,"<YKT_DATA><DORM_NAME>����10��¥116��</DORM_NAME></YKT_DATA>");
		ret = 0;
	}
	else
	{
		ret = -1;
	}
	return ret;
}