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
 \brief ��ʼ������
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
		// ȡ��·��
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
 \brief ��ʼ�� bccclt
 \param ip - ͨѶƽ̨ IP
 \param port - ͨѶƽ̨�˿�
 \param mainfunc - ��̨�����ܺ�
 \return 0 ��ʼ���ɹ� ʧ�ܷ��ش�����
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
 \brief �ͷ� bccclt ��Դ
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
 \brief - ��ȡ������
 \return - ������
 */
int __stdcall KSG_last_error()
{
	return g_lasterrno;
}

/**
 \brief - ��ȡ������Ϣ
 \return - ������Ϣ����
 */
const char * __stdcall KSG_get_errmsg()
{
	return g_errormsg;
}
/**
 \brief ��ʼ����
 \return �Ż�������, ʧ�ܷ��� NULL
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
		// ��������
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
	// ������ʧ��,ɾ��
	delete handle;
	g_lasterrno = KSG_ERR_BCC_HANDLE;
	return NULL;
}

/**
 \brief �ͷ�������
 \param handle - ���
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
		// ����������, ֱ�ӷ���
		return;
	}
	pre->next_handle_ = p->next_handle_;
	if (p->xhandle_)
		DeleteXpackHandle(p->xhandle_);
	delete p;
}
// �����ļ�
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
		// �����¼��ȡ��
		if (row >= rec_count)
		{
			// ���û�к�����
			if (!HaveNextPack(req->xhandle_))
			{
				return KSG_ERR_RET_PACK;
			}
			// ����ȡ����������
			if (!CallNext(req->xhandle_, req->timeout_, &errcode, raw_data))
			{
				return KSG_ERR_REQUEST;
			}
			if (GetXPackType(req->xhandle_) == 0)
			{
				// ���һ������У����Ϣ
				// ֻ��ȡ�����һ�����ű�ʾ�����ļ��ɹ�
				GET_STR(req->xhandle_,0,"vsmess",req->file_crc_);
				GetIntFieldByName(req->xhandle_,0,"lvol0",(int*)&req->file_size_);
				break;
			}
			GetRecordCount(req->xhandle_, &rec_count);
			row = 0;
			continue;
		}
		// д���ݵ��ļ���
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
			// ���ݰ�û������
			return KSG_ERR_RET_PACK;
		}
		else
			return KSG_ERR_GET_DATA;
	}
	while (1);
	return KSG_SUCCESS;
}
// ���������ļ�������
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
		// ����ʧ��
		if (req->retcode_)
		{
			memset(req->retmsg_, 0, sizeof(req->retmsg_));
			GET_STR(req->xhandle_, 0, "vsmess", req->retmsg_);
			sprintf(g_errormsg, "%d:%s", req->retcode_);
			return KSG_ERR_REQUEST;
		}
		// ����ɹ�
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
		// У���ļ���������
		struct stat fst;
		memset(&fst,0,sizeof fst);
		ret = stat(req->dest_file_,&fst);
		if(ret)
			return KSG_ERR_READFILE;
		// У���ļ��ĳ���
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
	raw_data[head_len-1] = (char)0xFF; // ������־
	SetRawRecord(req->xhandle_,0,raw_data,head_len);
	*/
	SetIntFieldByName(req->xhandle_,0,"lvol0",req->file_size_);
	SetStringFieldByName(req->xhandle_,0,"vsmess",req->dest_file_);
	SetStringFieldByName(req->xhandle_,0,"scust_limit",req->session_);
	SetIntFieldByName(req->xhandle_,0,"lvol1",0xFF); // ������־
	return do_send_request(req);
}
static int do_read_file(Request_Handle *req)
{
	char raw_data[REQ_PACK_LEN];
	int len,total_len,errcode,head_len;
	int row;
	row = 0;
	total_len = 0;
	// ��ͷ��
	head_len = strlen(req->session_)+5;
	// ���ݳ�
	sprintf(raw_data,"%04X",head_len);
	// �ļ���
	strncpy(raw_data+4,req->session_,strlen(req->session_));

	while(!feof(req->out_filep_))
	{
		// ��ȡ�ļ�����
		len = fread(raw_data+head_len,1,sizeof(raw_data)-head_len,req->out_filep_);
		if(len > 0)
		{
			total_len += len;
			if(req->p_callback_)
				req->p_callback_(total_len,len);
			ResetPackHandle(req->xhandle_);
			SetRequestType(req->xhandle_, 950999);
			raw_data[head_len-1] = (char)0x01; // �������ݱ�־
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
		// ��������
		errcode = do_send_request(req);
		if(errcode)
			return errcode;
	}
	return do_send_finish_pack(req);
	//return KSG_SUCCESS;
}
// �ϴ��ļ�
static int do_upload_file(Request_Handle *req)
{
	// TODO: �ȴ����
	int ret;
	struct stat fst;
	memset(&fst,0,sizeof fst);
	ret = stat(req->src_file_,&fst);
	if(ret)
		return KSG_ERR_READFILE;
	// ��¼�ļ���С
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
 \brief ִ������
 \param handle - ������
 \return ִ�гɹ����� 0 ,ʧ�ܷŻش�����
 */
int __stdcall KSG_send_request(KSG_File_Handle handle)
{
	DO_TEST_DRTP;
	
	Request_Handle *req = (Request_Handle*)handle;
	if (req->xhandle_ == NULL)
		return KSG_ERR_BCC_HANDLE;
	
	// �ϴ��ļ�
	if(req->is_upload_)
		return do_upload_file(req);
	else /* �����ļ� */
		return do_download_file(req);
}

/**
 \brief �����������
 \param handle - ������
 \param param_name - ������
 \param value - ����ֵ
 \param len - ����ֵ���� (�ֽ�)
 \return ���� 0 ��ʾ�ɹ�, -1 ��ʾ����������

 param_name ˵��:
	upload : �Ƿ��ϴ��ļ�, 1 ��ʾ�ϴ�,0 ��ʾ����, Ĭ��ֵΪ 0
	src_filename :  ���ص��ļ���
	dest_filename : ���غ󱣴���ļ�ȫ·����
	sessionid : ���� sessionid ��
	timeout : ����ʱʱ�� ,Ĭ�� 10000 ����
	callback : �ص�����
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
 \brief �������� cpack �ֶε�ֵ
 \param handle - ������
 \param field - cpack �ֶ���
 \param value - �ֶ�ֵ
 \param len - �ֶ�ֵ����(�ֽ�)
 \return ���� 0 ��ʾ�ɹ�,-1 ��ʾʧ��
 */
int __stdcall KSG_set_request_field(KSG_File_Handle handle, const char *field, void *value, size_t len)
{
	return -1;
}
