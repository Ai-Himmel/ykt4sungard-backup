#include "filetrans.h"
#include "bccclt.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <windows.h>
#endif // WIN32

#ifndef MAX_PATH
#define MAX_PATH 1025
#endif // MAX_PATH

#ifndef MAX_REQ_FILE_PACK 
#define MAX_REQ_FILE_PACK 99
#define REQ_PACK_LEN 4096
#endif // MAX_REQ_FILE_PACK


typedef struct _t_Request_Handle
{
	int mainfunc_;
	XDHANDLE xhandle_;
	FILE *out_filep_;
	char src_file_[MAX_PATH];
	char dest_file_[MAX_PATH];
	char session_[128];
	long timeout_;
	int retcode_;
	char retmsg_[256];
	int is_upload_;
	char file_crc_[33];
	size_t file_size_;
	transfer_callback p_callback_;
	_t_Request_Handle *next_handle_;
}Request_Handle;


static int g_drtp_no = -1;
static int g_mainfunc = 0;
static int g_lasterrno = KSG_SUCCESS;
static Request_Handle g_head_handle;
static char g_module_path[MAX_PATH];
static char g_errormsg[512];

#ifndef src2dest
#define src2dest(x,y) do{ memset(y,0,sizeof(y)); strncpy(y,(const char*)x,sizeof(y)-1); }while(0)
#endif // src2dest

#ifndef DO_TEST_DRTP
#define DO_TEST_DRTP do{ if(g_drtp_no == -1) return KSG_ERR_CONNECT_DRTP;}while(0)
#endif // DO_TEST_DRTP

#ifndef GET_STR
#define GET_STR(h,r,n,v) do { GetStringFieldByName(h,r,n,v,sizeof(v) - 1); }while(0)
#endif // GET_STR

/**
 \brief 初始化环境
 */
static int do_init_dll()
{
	memset(g_module_path, 0, sizeof g_module_path);
#ifdef WIN32
	DWORD ret = GetModuleFileName(NULL, g_module_path, sizeof(g_module_path) - 1);
	if (ret > 0)
	{
		g_module_path[ret] = '\0';
		char *pend;
		// 取出路径
		if ((pend = strrchr(g_module_path, '\\')) != NULL)
		{
			*(pend + 1) = '\0';
			return 0;
		}
	}
	return -1;
#else

#endif // WIN32
}

static int g_init_ = do_init_dll();

/**
 \brief 初始化 bccclt
 \param ip - 通讯平台 IP
 \param port - 通讯平台端口
 \param mainfunc - 后台主功能号
 \return 0 初始化成功 失败返回错误码
 */
int __stdcall KSG_init(const char *ip, int port, int mainfunc)
{
	if (g_drtp_no > -1)
		return KSG_ERR_ALREADY_INIT;
	if (!BCCCLTInit(1))
		return KSG_ERR_INITBCCCLT;
	else if (!XPackInit(1))
		return KSG_ERR_INITBCCCLT;
	else if ((g_drtp_no = AddDrtpNode((char*)ip, port)) < 0)
	{
		return KSG_ERR_CONNECT_DRTP;
	}
	g_head_handle.next_handle_ = NULL;
	g_mainfunc = mainfunc;
	return KSG_SUCCESS;
}

/**
 \brief 释放 bccclt 资源
 */
void __stdcall KSG_uninit()
{
	Request_Handle *p = g_head_handle.next_handle_;
	Request_Handle *q;
	while (p != NULL)
	{
		if (p->xhandle_)
			DeleteXpackHandle(p->xhandle_);
		q = p;
		p = p->next_handle_;
		delete q;
	}
	g_head_handle.next_handle_ = NULL;
}

/**
 \brief - 获取错误码
 \return - 错误码
 */
int __stdcall KSG_last_error()
{
	return g_lasterrno;
}

/**
 \brief - 获取错误信息
 \return - 错误信息内容
 */
const char * __stdcall KSG_get_errmsg()
{
	return g_errormsg;
}
/**
 \brief 开始请求
 \return 放回请求句柄, 失败返回 NULL
 */
KSG_File_Handle __stdcall KSG_begin_request()
{

	Request_Handle *handle = new Request_Handle;
	if (!handle)
	{
		g_lasterrno = KSG_ERR_MEMORY;
		return NULL;
	}
	memset(handle,0,sizeof(Request_Handle));
	char xpack_path[MAX_PATH+128];
	sprintf(xpack_path, "%s%s", g_module_path, "cpack.dat");
	handle->mainfunc_ = g_mainfunc;
	handle->xhandle_ = NewXpackHandle(xpack_path);
	if (handle->xhandle_)
	{
		// 加入链表
		Request_Handle *p = g_head_handle.next_handle_;
		Request_Handle *pre;

		pre = &g_head_handle;
		while ( p != NULL )
		{
			pre = p;
			p = p->next_handle_;
		}
		pre->next_handle_ = handle;
		handle->next_handle_ = NULL;
		handle->timeout_ = 10000;

		return (KSG_File_Handle)handle;
	}
	// 申请句柄失败,删除
	delete handle;
	g_lasterrno = KSG_ERR_BCC_HANDLE;
	return NULL;
}

/**
 \brief 释放请求句柄
 \param handle - 句柄
 */
void __stdcall KSG_free_request(KSG_File_Handle handle)
{

	Request_Handle *pre, *p;
	p = g_head_handle.next_handle_;
	pre = &g_head_handle;
	while (p != NULL && p != handle)
	{
		pre = p;
		p = p->next_handle_;
	}
	if (!p)
	{
		// 不在链表中, 直接返回
		return;
	}
	pre->next_handle_ = p->next_handle_;
	if (p->xhandle_)
		DeleteXpackHandle(p->xhandle_);
	delete p;
}
// 下载文件
static int do_writefile(Request_Handle *req)
{
	int ret, row, rec_count, errcode;
	long total_len;
	char raw_data[8192];
	if ((ret = fseek(req->out_filep_, SEEK_SET, 0L)) != 0)
	{
		return KSG_ERR_WRITEFILE;
	}
	if (GetXPackType(req->xhandle_) == 1)
		GetRecordCount(req->xhandle_, &rec_count);
	row = 0;
	total_len = 0;
	do
	{
		// 如果记录已取完
		if (row >= rec_count)
		{
			// 如果没有后续包
			if (!HaveNextPack(req->xhandle_))
			{
				return KSG_ERR_RET_PACK;
			}
			// 发送取后续包请求
			if (!CallNext(req->xhandle_, req->timeout_, &errcode, raw_data))
			{
				return KSG_ERR_REQUEST;
			}
			if (GetXPackType(req->xhandle_) == 0)
			{
				// 最后一个包是校验信息
				// 只有取得最后一个包才表示下载文件成功
				GET_STR(req->xhandle_,0,"vsmess",req->file_crc_);
				GetIntFieldByName(req->xhandle_,0,"lvol0",(int*)&req->file_size_);
				break;
			}
			GetRecordCount(req->xhandle_, &rec_count);
			row = 0;
			continue;
		}
		// 写数据到文件中
		ret = GetRawRecord(req->xhandle_, row, raw_data, sizeof raw_data);
		if (ret > 0)
		{
			total_len += ret;
			if(req->p_callback_)
				req->p_callback_(total_len,ret);
			fwrite(raw_data, (size_t)ret, 1, req->out_filep_);
			row++;
		}
		else if (ret == 0)
		{
			// 数据包没有类容
			return KSG_ERR_RET_PACK;
		}
		else
			return KSG_ERR_GET_DATA;
	}
	while (1);
	return KSG_SUCCESS;
}
// 处理下载文件的请求
static int do_download_file(Request_Handle *req)
{
	int errcode, ret;
	char msg[512] = "";

	SetStringFieldByName(req->xhandle_, 0, "vsmess", req->src_file_);
	SetStringFieldByName(req->xhandle_, 0, "sbankname", req->session_);
	
	SetRequestType(req->xhandle_, 950998);

	if (!CallRequest(req->xhandle_, g_drtp_no, 0,
	                 req->mainfunc_, req->timeout_, &errcode, msg))
	{
		sprintf(g_errormsg, "%d:%s", errcode, msg);
		return KSG_ERR_REQUEST;
	}
	else
	{
		GetRetCode(req->xhandle_, &req->retcode_);
		// 请求失败
		if (req->retcode_)
		{
			memset(req->retmsg_, 0, sizeof(req->retmsg_));
			GET_STR(req->xhandle_, 0, "vsmess", req->retmsg_);
			sprintf(g_errormsg, "%d:%s", req->retcode_);
			return KSG_ERR_REQUEST;
		}
		// 请求成功
		req->out_filep_ = fopen(req->dest_file_, "wb");
		if (!req->out_filep_)
		{
			return KSG_ERR_READFILE;
		}
		ret = do_writefile(req);
		fclose(req->out_filep_);
		req->out_filep_ = NULL;
		if (ret)
			return ret;
		// 校验文件的完整性
		struct stat fst;
		memset(&fst,0,sizeof fst);
		ret = stat(req->dest_file_,&fst);
		if(ret)
			return KSG_ERR_READFILE;
		// 校验文件的长度
		if(fst.st_size == req->file_size_)
			return KSG_SUCCESS;
		return KSG_ERR_FILE_CRC;
	}
}

static int do_send_request(Request_Handle *req)
{
	int errcode;
	char msg[512] = "";
 	if (!CallRequest(req->xhandle_, g_drtp_no, 0,
	                 req->mainfunc_, req->timeout_, &errcode, msg))
	{
		sprintf(g_errormsg, "%d:%s", errcode, msg);
		return KSG_ERR_REQUEST;
	}
	else
	{
		GetRetCode(req->xhandle_,&req->retcode_);
		if(req->retcode_)
		{
			memset(req->retmsg_, 0, sizeof(req->retmsg_));
			GET_STR(req->xhandle_, 0, "vsmess", req->retmsg_);
			sprintf(g_errormsg, "%d:%s", req->retcode_);
			return KSG_ERR_REQUEST;
		}
	}
	return KSG_SUCCESS;
}

static int do_send_finish_pack(Request_Handle *req)
{
	ResetPackHandle(req->xhandle_);
	SetRequestType(req->xhandle_, 950999);
	/*
	raw_data[head_len-1] = (char)0xFF; // 结束标志
	SetRawRecord(req->xhandle_,0,raw_data,head_len);
	*/
	SetIntFieldByName(req->xhandle_,0,"lvol0",req->file_size_);
	SetStringFieldByName(req->xhandle_,0,"vsmess",req->dest_file_);
	SetStringFieldByName(req->xhandle_,0,"scust_limit",req->session_);
	SetIntFieldByName(req->xhandle_,0,"lvol1",0xFF); // 结束标志
	return do_send_request(req);
}
static int do_read_file(Request_Handle *req)
{
	char raw_data[REQ_PACK_LEN];
	int len,total_len,errcode,head_len;
	int row;
	row = 0;
	total_len = 0;
	// 包头长
	head_len = strlen(req->session_)+5;
	// 内容长
	sprintf(raw_data,"%04X",head_len);
	// 文件名
	strncpy(raw_data+4,req->session_,strlen(req->session_));

	while(!feof(req->out_filep_))
	{
		// 读取文件内容
		len = fread(raw_data+head_len,1,sizeof(raw_data)-head_len,req->out_filep_);
		if(len > 0)
		{
			total_len += len;
			if(req->p_callback_)
				req->p_callback_(total_len,len);
			ResetPackHandle(req->xhandle_);
			SetRequestType(req->xhandle_, 950999);
			raw_data[head_len-1] = (char)0x01; // 正常内容标志
			SetRawRecord(req->xhandle_,0,raw_data,len+head_len);
		}
		else if(len == 0)
		{
			if(req->p_callback_)
				req->p_callback_(total_len,len);
			return do_send_finish_pack(req);	
		}
		else
			return KSG_ERR_READFILE;
		// 发送请求
		errcode = do_send_request(req);
		if(errcode)
			return errcode;
	}
	return do_send_finish_pack(req);
	//return KSG_SUCCESS;
}
// 上传文件
static int do_upload_file(Request_Handle *req)
{
	// TODO: 等待完成
	int ret;
	struct stat fst;
	memset(&fst,0,sizeof fst);
	ret = stat(req->src_file_,&fst);
	if(ret)
		return KSG_ERR_READFILE;
	// 记录文件大小
	req->file_size_ = fst.st_size;
	//if(req->file_size_ > REQ_PACK_LEN * MAX_REQ_FILE_PACK)
	//	return KSG_ERR_FILESIZE_EXCEED;
	
	SetRequestType(req->xhandle_, 950999);
	SetStringFieldByName(req->xhandle_,0,"vsmess",req->dest_file_);
	SetIntFieldByName(req->xhandle_,0,"lvol0",req->file_size_);
	ret = do_send_request(req);
	if(ret)
		return ret;
	GET_STR(req->xhandle_,0,"vsmess",req->dest_file_);
	GET_STR(req->xhandle_,0,"scust_limit",req->session_);
	req->out_filep_ = fopen(req->src_file_,"rb");
	ret = do_read_file(req);
	fclose(req->out_filep_);
	return ret;
}

/**
 \brief 执行请求
 \param handle - 请求句柄
 \return 执行成功返回 0 ,失败放回错误码
 */
int __stdcall KSG_send_request(KSG_File_Handle handle)
{
	DO_TEST_DRTP;
	
	Request_Handle *req = (Request_Handle*)handle;
	if (req->xhandle_ == NULL)
		return KSG_ERR_BCC_HANDLE;
	
	// 上传文件
	if(req->is_upload_)
		return do_upload_file(req);
	else /* 下载文件 */
		return do_download_file(req);
}

/**
 \brief 设置请求参数
 \param handle - 请求句柄
 \param param_name - 参数名
 \param value - 参数值
 \param len - 参数值长度 (字节)
 \return 返回 0 表示成功, -1 表示参数不存在

 param_name 说明:
	upload : 是否上传文件, 1 表示上传,0 表示下载, 默认值为 0
	src_filename :  下载的文件名
	dest_filename : 下载后保存的文件全路径名
	sessionid : 请求 sessionid 号
	timeout : 请求超时时间 ,默认 10000 毫秒
	callback : 回调函数
 */
int __stdcall KSG_set_param(KSG_File_Handle handle, const char *param_name,
                            void *value, size_t len)
{
	Request_Handle *req = (Request_Handle*)handle;
	if (strcmp(param_name, "src_filename") == 0)
	{
		src2dest(value, req->src_file_);
	}
	else if (strcmp(param_name, "dest_filename") == 0)
	{
		src2dest(value, req->dest_file_);
	}
	else if (strcmp(param_name, "sessionid") == 0)
	{
		src2dest(value, req->session_);
	}
	else if (strcmp(param_name, "timeout") == 0)
	{
		req->timeout_ = atoi((const char*)value);
	}
	else if (strcmp(param_name, "upload") == 0)
	{
		req->is_upload_ = atoi((const char*)value);
	}
	else if(strcmp(param_name,"callback") == 0)
	{
		req->p_callback_ = (transfer_callback)value;
	}
	else
		return -1;
	return 0;
}

/**
 \brief 设置请求 cpack 字段的值
 \param handle - 请求句柄
 \param field - cpack 字段名
 \param value - 字段值
 \param len - 字段值长度(字节)
 \return 返回 0 表示成功,-1 表示失败
 */
int __stdcall KSG_set_request_field(KSG_File_Handle handle, const char *field, void *value, size_t len)
{
	return -1;
}
