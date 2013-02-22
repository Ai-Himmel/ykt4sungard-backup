#ifndef _KSG_FILE_TRANS_H_
#define _KSG_FILE_TRANS_H_

#ifndef KSG_File_Handle
#define KSG_File_Handle void *
#endif // KSG_File_Handle

#define KSG_SUCCESS 0 /* �ɹ� */
#define KSG_ERR_INITBCCCLT 1001 /* ��ʼ�� bccclt ʧ�� */
#define KSG_ERR_CONNECT_DRTP 1002 /* ����ͨѶƽ̨ʧ�� */
#define KSG_ERR_ALREADY_INIT 1003 /* bccclt �Ѿ���ʼ���� */
#define KSG_ERR_BCC_HANDLE 1004 /* ���� bccclt ���ʧ�� */
#define KSG_ERR_MEMORY		1005 /* �����ڴ�ʧ�� */
#define KSG_ERR_REQUEST		1006 /* �����̨ʧ�� */
#define KSG_ERR_WRITEFILE	1007 /* д�ļ�ʧ�� */
#define KSG_ERR_READFILE	1008 /* ���ļ�ʧ�� */
#define KSG_ERR_GET_DATA	1009 /* ��ȡ��������ʧ�� */
#define KSG_ERR_RET_PACK	1010 /* �������ݰ����� */
#define KSG_ERR_FILE_CRC	1011 /* �ļ�У��ʧ�� */
#define KSG_ERR_FILESIZE_EXCEED 1012 /* �ļ���С�������� */


#ifdef WIN32
#ifdef FILETRANS_EXPORTS
#pragma message (" export dll lib")
#define KSG_API __declspec(dllexport)
#else
#define KSG_API __declspec(dllimport)
#endif // FILETRANS_EXPORTS
#else
#define KSG_API
#endif // WIN32

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void (__stdcall *  transfer_callback)(int total_len,int pack_len);
KSG_API int __stdcall KSG_init(const char *ip, int port, int mainfunc);
KSG_API void __stdcall KSG_uninit();
KSG_API int __stdcall KSG_last_error();
KSG_API KSG_File_Handle __stdcall KSG_begin_request();
KSG_API void __stdcall KSG_free_request(KSG_File_Handle handle);
KSG_API int __stdcall KSG_send_request(KSG_File_Handle handle);
KSG_API int __stdcall KSG_set_param(KSG_File_Handle handle, const char *param_name, 
							void *value, size_t len);
KSG_API	const char * __stdcall KSG_get_errmsg();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _KSG_FILE_TRANS_H_
