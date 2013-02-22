#ifndef KS_DEF_H
#define KS_DEF_H
#pragma  once 

#define KS_ERR_LOADLIBRARY		  1001			// 加载动态库失败
#define KS_ERR_LOADFUNC_ADDRESS	  1002			// 加载动态库函数失败
#define KS_ERR_GETVERSION		  1003			// 获得动态库版本出错
#define KS_ERR_NOINITFILE		  1004			// 无配置文件可读

#define DCLR_KSFUNC(r,name,arg) \
	typedef r (__stdcall* LP##name) arg; 
//	extern LP##name name;

#define DEF_KSFUNC(name) \
	LP##name name = NULL; \
	
#define LOAD_KSFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if(NULL == name) \
	{ \
		::FreeLibrary(handle); \
		handle = NULL; \
		return KS_ERR_LOADFUNC_ADDRESS; \
	}

#endif