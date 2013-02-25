#ifndef _C_WBPY_UTIL_H
#define _C_WBPY_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define WB_CODE_MAX_LEN 4
#define WB_HZ_MAX_LEN 20

#define CWB_PY_CONVERT              10
#define CONVERT_ALL                 CWB_PY_CONVERT + 1
#define CONVERT_NO_LETTER           CWB_PY_CONVERT + 2
#define CONVERT_NO_SPACE_TAB        CWB_PY_CONVERT + 3
#define CONVERT_NO_HZ_CHAR          CWB_PY_CONVERT + 4

typedef struct __tagWBCodeTable {
    char szCode[WB_CODE_MAX_LEN];
    char szHz[WB_HZ_MAX_LEN];
} WBCodeTable , * PWBCodeTable;

#define CONVERT_ALL                 0x7

#define CONVERT_NO_LETTER_DIGEST    0x1
#define CONVERT_NO_SPACE_TAB        0x2
#define CONVERT_NO_HZ_CHAR          0x4
#define CONVERT_NO_ASCII            0x3

void __declspec(dllimport) __stdcall LoadWbCodeTable(const char * TablePath);

void __declspec(dllimport) __stdcall GetWbCoden(const char * value,
     char * code,WORD ctype, int len);

void __declspec(dllimport) __stdcall GetWbCode(const char * value,
     char * code,WORD ctype);

void __declspec(dllimport) __stdcall GetPyCode(const char * value,
    char * code,WORD ctype);

void __declspec(dllimport) __stdcall GetPyCoden(const char * value,
    char * code,WORD ctype, int len);

int __declspec(dllimport) __stdcall findInGBK(WORD hz , char * py);

BOOL __declspec(dllimport) __stdcall ReleaseWbCodeTable();


typedef void (__stdcall * LFLoadWbCodeTableC)(const char * TablePath);
typedef void (__stdcall * LFGetWbCodeC)(const char * value,char * code);
typedef void (__stdcall * LFGetPyCodeC)(const char * value,char * code);

typedef void (__stdcall * LFReleaseWbCodeTableC)();

extern LFLoadWbCodeTableC LoadWbCodeTableC;
extern LFGetWbCodeC GetWbCodeC;
extern LFGetPyCodeC GetPyCodeC;
extern LFReleaseWbCodeTableC ReleaseWbCodeTableC;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _C_WBPY_UTIL_H
 
