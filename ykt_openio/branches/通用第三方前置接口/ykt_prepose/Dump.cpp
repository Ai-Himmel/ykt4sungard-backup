#include "stdafx.h"
#include "Dump.h"
#include <dbghelp.h>
//#include <afx.h>
//#include <atlstr.h>
//#include <windows.h>
#pragma comment(lib, "DbgHelp.Lib")

#pragma data_seg("Shared")
LPTOP_LEVEL_EXCEPTION_FILTER gFilter = NULL;
#pragma data_seg()
LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)

{
	HANDLE lhDumpFile = CreateFile(_T("d:\\DumpFile.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);
    MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;
    loExceptionInfo.ExceptionPointers = ExceptionInfo;
    loExceptionInfo.ThreadId = GetCurrentThreadId();
    loExceptionInfo.ClientPointers = TRUE;
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile, MiniDumpNormal, &loExceptionInfo, NULL, NULL);
    CloseHandle(lhDumpFile);
    return EXCEPTION_EXECUTE_HANDLER;
}


/*
BOOL CreateDumpFile(PEXCEPTION_POINTERS pep, CString csName)
{
	HANDLE hFile = CreateFile(csName, GENERIC_READ | GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != NULL && hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION meinfo;
		meinfo.ThreadId = GetCurrentThreadId();
		meinfo.ExceptionPointers = pep;
		meinfo.ClientPointers = FALSE;
		
		BOOL bRet = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != NULL) ? &meinfo : 0, NULL, NULL);
		if(bRet == NULL)
		{
			CloseHandle(hFile);

			return FALSE;
		}

		CloseHandle(hFile);
		
		return TRUE;
	}

	return FALSE;
}

LONG WINAPI CreateExceptionDump(PEXCEPTION_POINTERS pep)
{
	CString csTemp;
    CString csFileName;
    CTime tm = CTime::GetCurrentTime();
	char ch[MAX_PATH];
	GetModuleFileName(NULL, ch, MAX_PATH);
	CString str(ch);
	str = str.Left(str.Find('.') - 1);
	
	if(!CreateDumpFile(pep, str + "_" + tm.Format("%Y%m%d_%H%M%S.dmp")))
	{
		OutputDebugString("create DUMP file error!");
//		return EXCEPTION_CONTINUE_EXECUTION;
	}
	
	return EXCEPTION_EXECUTE_HANDLER;
}

void SetExceptionFilter()
{
	gFilter = SetUnhandledExceptionFilter(CreateExceptionDump);
}

void UnSetExceptionFilter()
{
	SetUnhandledExceptionFilter(gFilter);
}
*/