
#ifndef _WBPY_CODE_H
#define _WBPY_CODE_H

#include <windows.h>
#include <stdio.h>

#define WB_CODE_MAX_LEN 4
#define WB_HZ_MAX_LEN 20

static const char GlobalFileName[] = "CASH_WBPY_DLL_TABLE";

const unsigned long BufLen = 735000;

static HANDLE hGlobalFile;


#ifndef __WIN32__

#define WORD unsigned short

#undefine MAKEWORD

#define MAKEWORD( low,high) ( (unsigned short)(high) << 8 | (byte)(low) )
#endif __WIN32__

#ifdef __cplusplus
extern "C" {
#endif

#define CONVERT_ALL                 0x7
#define CONVERT_NO_LETTER_DIGEST    0x1
#define CONVERT_NO_SPACE_TAB        0x2
#define CONVERT_NO_HZ_CHAR          0x4
#define CONVERT_NO_ASCII            0x3

typedef struct __tagWBCodeTable {
    char szCode[WB_CODE_MAX_LEN];
    char szHz[WB_HZ_MAX_LEN];
} WBCodeTable , * PWBCodeTable;

PWBCodeTable HeadWB , TailWB;

void __declspec(dllexport) __stdcall LoadWbCodeTable(const char * TablePath);

void __declspec(dllexport) __stdcall GetWbCoden(const char * value,
     char * code ,WORD ctype, int len);

void __declspec(dllexport) __stdcall GetWbCode(const char * value,
     char * code,WORD ctype);

void __declspec(dllexport) __stdcall GetPyCode(const char * value,
    char * code,WORD ctype);

void __declspec(dllexport) __stdcall GetPyCoden(const char * value,
    char * code,WORD ctype, int len);

int __declspec(dllexport) __stdcall findInGBK(WORD hz , char * py);

BOOL __declspec(dllexport) __stdcall ReleaseWbCodeTable();

LPVOID __stdcall AllocateMemory(DWORD size);

LPVOID __stdcall GetMemoryAddress();

void __stdcall readline(FILE * fp , char * buf , int maxlen);

void __stdcall ParseLine(PWBCodeTable lpTbl , const char * line);

#ifdef __cplusplus
}
#endif

#endif // _WBPY_CODE_H
 
