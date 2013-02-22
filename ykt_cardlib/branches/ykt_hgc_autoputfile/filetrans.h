#ifndef _KSG_FILE_TRANS_H_
#define _KSG_FILE_TRANS_H_

#ifndef KSG_File_Handle
#define KSG_File_Handle void *
#endif // KSG_File_Handle

#define KSG_SUCCESS 0 /* 成功 */
#define KSG_ERR_INITBCCCLT 1001 /* 初始化 bccclt 失败 */
#define KSG_ERR_CONNECT_DRTP 1002 /* 连接通讯平台失败 */
#define KSG_ERR_ALREADY_INIT 1003 /* bccclt 已经初始化了 */
#define KSG_ERR_BCC_HANDLE 1004 /* 申请 bccclt 句柄失败 */
#define KSG_ERR_MEMORY		1005 /* 申请内存失败 */
#define KSG_ERR_REQUEST		1006 /* 请求后台失败 */
#define KSG_ERR_WRITEFILE	1007 /* 写文件失败 */
#define KSG_ERR_READFILE	1008 /* 读文件失败 */
#define KSG_ERR_GET_DATA	1009 /* 获取返回数据失败 */
#define KSG_ERR_RET_PACK	1010 /* 返回数据包错误 */
#define KSG_ERR_FILE_CRC	1011 /* 文件校验失败 */
#define KSG_ERR_FILESIZE_EXCEED 1012 /* 文件大小超过限制 */


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
