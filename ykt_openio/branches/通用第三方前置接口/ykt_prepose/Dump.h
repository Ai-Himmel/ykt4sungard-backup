/*
 *使用说明
 *使用时直接包含该头文件，并在.APP文件的开始出调用SetExceptionFiler()函数
 *当程序因为异常崩溃时自动在当前目录下生成：程序名+时间.dup文件。
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