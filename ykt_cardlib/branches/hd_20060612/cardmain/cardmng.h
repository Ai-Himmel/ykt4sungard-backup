#ifndef CARDMNG_H
#define CARDMNG_H
/** 
 * ģ����					������ģ��
 * �ļ���					cardmng.h
 * �ļ�ʵ�ֹ���				д��DLLͷ����
 * ����						����
 * �汾						V0.1
 * ����						2005-06-25
 * ��ע
 * $Id: cardmng.h 10 2005-08-25 02:25:34Z cheng.tang $
 */

#ifdef CARDMNG_EXPORT
#define CARD_API __declspec(dllexport)
#pragma message("export dll info")
#else
#define CARD_API __declspec(dllimport)
#pragma message("import dll info")
#endif // CARDMNG_EXPORT

#ifndef BYTE 
#define BYTE unsigned char
#endif	// BYTE

#define E_COM_NOT_OPEN 10001
#define E_COM_NOT_CLOSE 10002

#define E_READ_CARD_ID_ERROR 10005
#define E_GEN_CARD_KEY_A_ERROR 10006
#define E_GEN_CARD_KEY_B_ERROR 10007

#define E_READ_CARD_ERROR 10010
#define E_CARD_LOGIN_ERROR 10011
#define E_MAIN_KEY_ERROR 10012
#define E_CARD_WRITE_ERROR 10020

#define E_INVALID_CARD 10030
//////////////////////////////////////////////////////////////////////////
// ��ȡ�����ļ�
void GetIniFile(char *FilePathBuf);
//////////////////////////////////////////////////////////////////////////

typedef struct _tagCardKeyData
{
	long flag;
	BYTE key[7];
} CardKeyData,* PCardKeyData;

typedef int (*PWriteDataFunc)(long sect,CardKeyData * keya 
							  ,CardKeyData * keyb ,BYTE * card_type
							  ,CardKeyData * login_key);

typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf
							   ,BYTE *key,long flag);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	// �ص�����
	typedef void (CALLBACK * LPProcessCallBack)(int step);
/*
	CARD_API int __stdcall ResetMainKey();
	CARD_API int __stdcall InitNewCard(int * err_code);
	CARD_API int __stdcall ReadCardMainKey(BYTE * main_key);
	CARD_API int __stdcall RefineCard(int *err_code);
	CARD_API int __stdcall OpenCOM(int port,long band);
	CARD_API int __stdcall CloseCOM();
*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CARDMNG_H
