/*
 *ʹ��˵��
 *ʹ��ʱֱ�Ӱ�����ͷ�ļ�������.APP�ļ��Ŀ�ʼ������SetExceptionFiler()����
 *��������Ϊ�쳣����ʱ�Զ��ڵ�ǰĿ¼�����ɣ�������+ʱ��.dup�ļ���
*/
#ifndef _DUMPDLL_H_
#define _DUMPDLL_H_
#define DLLPORT _declspec(dllexport)

extern "C"
{
	LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);
	//DLLPORT void SetExceptionFilter();
	//DLLPORT void UnSetExceptionFilter();
}

#endif //_DUMPDLL_H_