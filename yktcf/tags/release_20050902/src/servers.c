/** 
 * ģ����			һ��ͨͨ��ǰ��
 * �ļ���			servers.c
 * �ļ�ʵ�ֹ���		���������̺���
 * ����				����
 * �汾				V0.2
 * ����				2005-07-06
 * ��ע
 * $Id: servers.c 27 2005-09-02 08:21:27Z cheng.tang $
 *
 * �޸�ʱ��		�汾	����	˵��
 * 2005-9-2		V0.2	����	�����˼�����Կ���ܳ��ֵ�Bug,
 *								��������������������DRTP��Bug
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>
#include <signal.h>
#include <time.h>
#include <netinet/in.h>

#include "servers.h"
#include "def.h"
#include "kcc_conf.h"
#include "kcc_util.h"
#include "drtp.h"
#include "drtpcall.h"
#include "rijndael-api-fst.h"

#define MAXPROCESS 100
#define CPACK_BUF_LEN 1024 << 3
#define MAX_PACK_LEN 30
#define MODULE_EXT "so"

static int server_is_running = 0;
static time_t gs_load_module_time;
/** 
* @brief ȫ�ֵ� DRTP ���,�ɸ�����ʹ��,�ӽ��̲�Ҫʹ��
*/
static int gs_drtp_handle = -1;

static struct pid_module_server_struct
{
	pid_t pid;
	kcc_module_list * m;
	kcc_server_config * svr;
	char magic[16];				// ͨ����ǰ��ϵͳIP��MAC
								// ModuleName �������MD5
}DO_PROCESS_MODULE[MAXPROCESS];

struct cpack_buffer_info
{
	int handle;				// drtp handle
	int index;				// pack index
	int nextflag;			// �Ƿ��к�����
	int buflen;				// buffer ����󳤶�
	char * buf;				// buffer ָ��
	int readlen;			// ʵ�ʶ����ĳ���
	int packcount;			// ���ɵİ���¼����
	int bepad;				// ��������Ǽ��ܵģ����Ƿ��Ǳ���λ�������Ϊ 1 ,����Ϊ 0
	ST_CPACK rpack;			// �����CPACK ��
	ST_CPACK apack;			// Ӧ�� CPACK ��
	ST_PACK apackarray[MAX_PACK_LEN];// ����Ӧ�����ݰ��� PACK ����
	int sendflag;
};
/*
static void do_main_process_alarm(int signum)
{
	alarm(0);	
	
}
*/
static int do_get_drtp_handle()
{
	if(gs_drtp_handle <= 0)
	{
		gs_drtp_handle = kcc_drtp_connect();
	}
	return gs_drtp_handle;
}
static void do_release_drtp_handle()
{
	if(gs_drtp_handle > 0)
	{
		kcc_drtp_close(gs_drtp_handle);
		gs_drtp_handle = 0;
	}
}
static int do_lock_module_process(struct kcc_module_list *m,
								  struct kcc_server_config * svr)
{
	char filename[100] = "";
	char tmp[50] = "";
	kcc_strncpy(filename,g_app_home_path,sizeof(filename));
	kcc_add_path_sep(filename,kcc_strlen(filename));
	kcc_strcat(filename,"pid");
	kcc_add_path_sep(filename,kcc_strlen(filename));

	sprintf(tmp,"%.6d",svr->server_no);
	kcc_strcat(filename,tmp);
	sprintf(tmp,"%.3d",m->index);
	kcc_strcat(filename,tmp);
	kcc_strcat(filename,".pid");
	kcc_write_log(LOG_DEBUG,"gen lock pid file [%s]",filename);
	return kcc_lock_file(filename,F_LOCK);
}
/** 
 * @brief ɾ��ȫ�������е�������ϵͳ
 * 
 * @param config - ȫ����ϵͳ����
 */
void kcc_release_server_list()
{
	struct kcc_server_config * p = g_server_list;
	struct kcc_server_config * config;
	while (p != NULL)
	{
		config = p->pnext;
		kcc_write_log(LOG_DEBUG,"release server[%d]",p->server_no);
		kcc_free(p);
		p = config;
	}
}
static void do_add_server_config(struct kcc_server_config *svr)
{
	kcc_server_config * p = g_server_list;
	while(NULL != p && NULL != p->pnext)
	{
		p = p->pnext;
	}
	if(p == NULL)
	{
		p = svr;
		g_server_list = svr;
	}
	else
	{
		p->pnext = svr;
	}
	kcc_write_log(LOG_DEBUG,"server [%d][%s:%d][%s]",
				  svr->server_no,svr->conf.ip,svr->conf.port,svr->conf.mac);
}
/** 
 * @brief ��ʼ����ϵͳ����
 * 
 * @return - �ɹ����� 0 �������� -1
 */
int kcc_init_server_list()
{
	int drtp_handle = -1;
	int retval = -1;
	int rows;
	int i;
	ST_CPACK rpack,apack;
	// ���100����ϵͳ
	ST_PACK apackarray[100];
	kcc_server_config * svr;
	if (g_server_list != NULL)
	{
		kcc_release_server_list();	
		g_server_list = NULL;
	}
	drtp_handle = do_get_drtp_handle();
	if( drtp_handle > 0 )
	{
		kcc_init_cpack(&rpack,1,g_get_svr_list_func,
					   sizeof(apackarray)/sizeof(apackarray[0]));
		if(kcc_drtp_send_cpack(drtp_handle,&rpack) == 0)
		{
			rows = kcc_drtp_recv_cpack(drtp_handle,&apack,apackarray,
								   sizeof(apackarray)/sizeof(apackarray[0]));
			if( rows < 0 )
			{
				kcc_write_log(LOG_ERR,"get pack error!\n");
			}
			for(i = 0;i < rows ;++i)
			{
				svr = (kcc_server_config*)kcc_alloc(sizeof(kcc_server_config));
				if(NULL == svr)
				{
					kcc_write_log(LOG_DEBUG,"alloc memory error!");
					retval = -1;
					goto L_END;
				}
				kcc_memclr(svr,sizeof(kcc_server_config));
				svr->enc_type = -1;
				svr->server_no = apackarray[i].lvol1;
				kcc_strncpy(svr->conf.ip,apackarray[i].sname,
							sizeof(svr->conf.ip));
				kcc_strncpy(svr->conf.mac,apackarray[i].sname2,
							sizeof(svr->conf.mac));
				kcc_write_log(LOG_DEBUG,"server mac[%s]",svr->conf.mac);
				svr->conf.port = apackarray[i].lvol2;
				// ���û�����ü����㷨��ʹ��ϵͳ��Ĭ�ϼ����㷨
				// TODO: ��ȡ���ܱ�־�� CPACK
				svr->enc_type = apackarray[i].lvol3;
				if(-1 == svr->enc_type)
				{
					svr->enc_type = g_default_enc_type;
				}
				kcc_write_log(LOG_DEBUG,"add subsystem id [%d]",svr->server_no);
				do_add_server_config(svr);
			}
		}
		else
			kcc_write_log(LOG_ERR,"send function error!\n");
	}
	else
	{
		return -1;
	}
L_END:
	retval = 0;
	return retval;
}

/** 
 * @brief ɾ����ǰϵͳ�����е�ģ��
 */
void kcc_clear_modules()
{
	int ret;
	struct kcc_module_list * p = g_module_list;
	struct kcc_module_list * q;
	g_module_list = NULL;
	while(p != NULL)
	{
		if(p->module.kcc_m_unload != NULL)
		{
			ret = p->module.kcc_m_unload(); 
			if(ret)
			{
				kcc_write_log(LOG_INFO,"unload module [%s] success!",
							  p->module.module_name);
			}
			else
			{
				kcc_write_log(LOG_ERR,
							  "unload module [%s] failed! error code[%d]",
							  p->module.module_name,ret);
			}
		}
		dlclose(p->handle);
		q = p;
		p = p->pnext;
		kcc_free(q);
	}
}

/** 
 * @brief ��ʾģ����Ϣ
 * 
 * @param mentry - Module ָ��
 */
static void do_show_module_info(struct kcc_module_list * mentry)
{
	char md5str[33] = "";
	kcc_module_config * m = &mentry->module;
	kcc_hex2src(mentry->md5str,sizeof(mentry->md5str),md5str);
	kcc_write_log(LOG_INFO,"=========================module name[%s].",
				  m->module_name);
	kcc_write_log(LOG_INFO,"module version [%d].[%d] build[%s]",
				  m->major,m->minor,m->build);
	kcc_write_log(LOG_INFO,"module date[%s].",m->date);
	kcc_write_log(LOG_INFO,"module md5[%s].",md5str);
	kcc_write_log(LOG_INFO,"=========================================");
}
/** 
 * @brief ��ģ�� struct ���ӵ�ģ���β
 * 
 * @param m - module struct
 */
static void do_add_to_module_list(kcc_module_list * m)
{
	kcc_module_list * p = g_module_list;
	int i;

	for(i = 0; p != NULL &&  p->pnext != NULL ;p = p->pnext,++i)
		;
	m->pnext = NULL;
	m->index = i;
	if(p == NULL)
		g_module_list = m;
	else
		p->pnext = m;
	do_show_module_info(m);
}

/** 
 * @brief ���ģ���ǲ��ṩ��������Ҫ�Ľӿ�
 * 
 * @param module - ģ��ṹ
 * 
 * @return - 0 ��ʾ��ȷ��-1 ��ʾ����
 */
static int do_validate_module(const struct kcc_module_config * module)
{
	if(
	   (module->kcc_m_request_cpack == NULL)||
	   (module->kcc_m_format_header == NULL)||
	   (module->kcc_m_format_cpack == NULL)||
	   (module->kcc_m_format_tail == NULL)||
	   (module->kcc_m_make_return_cpack == NULL)||
	   (module->kcc_m_get_func_no == NULL)||
	   (module->kcc_m_get_module_type == NULL)
	  )
	{
		return -1;
	}
	return 0;
}
/** 
 * @brief ͨ��ָ���� path ���ز����������سɹ��ͼ��뵽ȫ�ֵ�ģ��������
 * 
 * @param path - ���·��
 */
static int do_load_module(const char * path,struct kcc_module_list* m)
{
	struct stat info;
	FILE* fp;
	dlhandle handle;
	lpkcc_get_module_info get_module_info;
	if( stat(path,&info) != -1 )
	{
		if(!S_ISREG(info.st_mode))
		{
			// ��������ļ�����
			return -1;
		}
		if(m->handle != NULL)
		{
			dlclose(m->handle);
			m->handle = NULL;
		}
		if((handle = dlopen(path,RTLD_LAZY)) == NULL)
		{
			kcc_write_log(LOG_ERR,"open dl error[%s].",path);
			return -1;
		}
		get_module_info = (lpkcc_get_module_info)
			dlsym(handle,"kcc_get_module_info");
		if(get_module_info == NULL)
		{
			kcc_write_log(LOG_ERR,"get module entry error![%s]",
						  path);
			return -1;
		}
		m->get_module_info = get_module_info;
		if(m->get_module_info(&m->module) != 0)
		{
			kcc_write_log(LOG_ERR,"registe module error![%s]",path);
			dlclose(handle);
			return -1;
		}
		if(do_validate_module(&m->module))
		{
			kcc_write_log(LOG_ERR,"module not support all interface.[%s]",
						  path);
			dlclose(handle);
			return -1;
		}
		m->handle = handle;
		if(m->module.kcc_m_load != NULL && 
		   m->module.kcc_m_load())
		{
			kcc_write_log(LOG_INFO,"load module success![%s]",path);
		}
		if((fp = fopen(path,"r")) != NULL)
		{
			if(kcc_get_file_md5(fp,m->md5str) == 0)
			{
				kcc_write_log(LOG_INFO,"initialize module success[%s]",path);
				fclose(fp);
				return 0;
			}
		}
		fclose(fp);
		return -1;
	}
	else
		kcc_write_log(LOG_ERR,"load module [%s] error!",path);
	return -1;
}

/** 
 * @brief ���浱ǰģ��Ŀ¼������޸�ʱ��
 * 
 * @param path - ģ��Ŀ¼��·��
 */
static void do_set_module_directory_time(const char* path)
{
	struct stat info;
	if( stat(path,&info) == -1 )
	{
		kcc_write_log(LOG_ERR,"get module dirctory time error!");
		return;
	}
	gs_load_module_time = info.st_mtime;
}
/** 
 * @brief �ӿں��� - ��ʼ����
 * 
 * @return -  �ɹ����� 0 �����ɹ� �˳�����
 */
int kcc_init_modules()
{
	char dirname[128] = "";
	char fullpath[160] = "";
	char ext[10] = "";
	DIR * dirptr;
	struct dirent * pent;
	struct kcc_module_list* m;
	kcc_clear_modules();
	g_module_list = NULL;
	kcc_strcpy(dirname,g_app_home_path);
	// TODO : load modules path from config file
	kcc_add_path_sep(dirname,kcc_strlen(dirname));
	kcc_strcat(dirname,"modules");
	kcc_add_path_sep(dirname,kcc_strlen(dirname));
	if( (dirptr = opendir(dirname)) == NULL )
	{
		kcc_write_log(LOG_ERR,"open module dir error![%s]",dirname);
		return -1;
	}
	do_set_module_directory_time(dirname);
	while((pent = readdir(dirptr)) != NULL)
	{
		if(kcc_get_file_ext(pent->d_name,ext,NULL) == -1)
		{
			continue;
		}
		if(!kcc_str_equals(ext,MODULE_EXT))
		{
			continue;
		}
		if(kcc_str_equals(pent->d_name,".")||
		   kcc_str_equals(pent->d_name,".."))
		{
			continue;
		}
		kcc_strcpy(fullpath,dirname);
		kcc_strcat(fullpath,pent->d_name);
		m = (struct kcc_module_list*)kcc_alloc(sizeof(struct kcc_module_list));
		kcc_memclr(m,sizeof(struct kcc_module_list));
		if(NULL == m)
		{
			kcc_die(2,"allocate module memory error!");
		}
		if(do_load_module(fullpath,m) == 0)
		{
			kcc_strcpy(m->file,pent->d_name);
			do_add_to_module_list(m);
		}
		else
		{
			kcc_free(m);
		}
	}
	closedir(dirptr);
	return 0;
}

/** 
 * @brief ����һ���µ�ģ��
 * 
 * @param fullpath - ģ��������·��
 * @param filename - ģ����ļ���
 * 
 * @return - 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
static int do_add_new_module(const char* fullpath,const char* filename)
{
	struct kcc_module_list* m;
	m = (struct kcc_module_list*)kcc_alloc(sizeof(struct kcc_module_list));
	if(NULL == m)
	{
		return -1;
	}
	kcc_memclr(m,sizeof(struct kcc_module_list));
	kcc_strcpy(m->file,filename);
	if(do_load_module(fullpath,m) == 0)
	{
		do_add_to_module_list(m);
		return 0;
	}
	kcc_free(m);
	return -1;
}
/** 
 * @brief ����ģ�飬���¼���
 * 
 * @param fullpath - ģ������·��
 * @param filename - ģ���ļ���
 * 
 * @return - 0 ��ʾ���³ɹ���-1 ��ʾ����ʧ��
 */
static int do_update_module(const char* fullpath,const char* filename)
{
	struct stat info;
	struct kcc_module_list* m;
	FILE* fp;
	char md5[16] = "";
	if(stat(fullpath,&info) == -1)
	{
		return -1;
	}
	m = g_module_list;
	while(m != NULL)
	{
		if(kcc_str_equals(m->file,filename))
		{
			break;
		}
		m = m->pnext;
	}
	if(m == NULL)
	{
		return do_add_new_module(fullpath,filename);
	}
	// ��־Ϊ����״̬
	m->status = 0;
	if((fp = fopen(fullpath,"r")) == NULL)
	{
		kcc_write_log(LOG_ERR,"load file error");
		return -1;
	}
	kcc_get_file_md5(fp,md5);
	// ����Ҫ���¼���
	if(kcc_memcmp(m->md5str,md5,sizeof(md5)) == 0)
	{
		fclose(fp);
		return 0;
	}
	kcc_memcpy(m->md5str,md5,sizeof(md5));
	fclose(fp);
	if(do_load_module(fullpath,m) == -1)
	{
		// ���¼���ʧ�ܱ�־Ϊɾ��
		m->status = -1;
		return -1;
	}
	return 0;
}

/** 
 * @brief �ͷű�־Ϊɾ����ģ��
 * 
 * @return - �ɹ����� 0�� ʧ�ܷ��� -1
 */
static int do_release_bad_modules()
{
	struct kcc_module_list * module;
	struct kcc_module_list ** p;
	int i;
	for(p = &g_module_list;(module = *p) != NULL;)
	{
		if(module->status == 0)
		{
			p = &module->pnext;
			continue;
		}
		*p = module->pnext;
		if(module->handle)
		{
			dlclose(module->handle);
		}
		kcc_free(module);
	}
	module = g_module_list;
	i = 0;
	while(module != NULL)
	{
		module->index = i++;
		module = module->pnext;
	}
	return 0;
}
/** 
 * @brief ���¼��ؼ������ģ��
 * 
 * @return - �ɹ����� 0��ʧ�ܷ��� -1
 */
static int do_reload_modules()
{
	char dirname[128] = "";
	char fullpath[256] = "";
	char ext[10] = "";
	DIR * dirptr;
	struct dirent * pent;
	struct stat info;
	struct kcc_module_list *m;
	kcc_strcpy(dirname,g_app_home_path);
	// TODO : load modules path from config file
	kcc_add_path_sep(dirname,kcc_strlen(dirname));
	kcc_strcat(dirname,"modules");
	if(stat(dirname,&info) == -1)
	{
		kcc_write_log(LOG_ERR,"load module directory error!");
		return -1;
	}
	// ���ʱ����ͬ�򷵻�
	if(difftime(info.st_mtime,gs_load_module_time) <= 0 )
	{
		return 0;
	}
	gs_load_module_time = info.st_mtime;
	if( (dirptr = opendir(dirname)) == NULL )
	{
		kcc_write_log(LOG_ERR,"open module dir error![%s]",dirname);
		return -1;
	}
	// ��������ģ���״̬Ϊɾ��
	m = g_module_list;
	while(NULL != m)
	{
		m->status = -1;
		m = m->pnext;
	}
	while((pent = readdir(dirptr)) != NULL)
	{
		if(kcc_get_file_ext(pent->d_name,ext,NULL) == -1)
		{
			continue;
		}
		if(!kcc_str_equals(ext,MODULE_EXT))
		{
			continue;
		}
		if(kcc_str_equals(pent->d_name,".")||
		   kcc_str_equals(pent->d_name,".."))
		{
			continue;
		}
		kcc_strcpy(fullpath,dirname);
		kcc_add_path_sep(fullpath,kcc_strlen(fullpath));
		kcc_strcat(fullpath,pent->d_name);
		do_update_module(fullpath,pent->d_name);
	}
	closedir(dirptr);
	do_release_bad_modules();
	return 0;
}
/** 
 * @brief ���ɷ��͵���������
 * 
 * @param m  - module struct
 * @param svr - server struct
 * @param buf - [out] �������ɵ���������
 * @param buflen - [out] buf �ĳ���
 * 
 * @return - buf �е�����ʵ�ʳ��� ��0 ��ʾ����ʧ��
 */
static int do_format_request_buffer(struct kcc_module_list *m,
									struct kcc_server_config * svr,
									struct cpack_buffer_info * pack)
{
	ST_CPACK* rpack;
	ST_CPACK* apack;
	int handle;					// DRTP handle	
	int ret_rows;				// ����CPACK ������
	int i;					
	int readlen;				// 
	int buflen;					// buffer ����󳤶�
	int reqType;
	char * buf;					// buffer

	// ��ʼ��
	handle = pack->handle;
	buf = pack->buf;
	buflen = pack->buflen;
	pack->readlen = 0;
	pack->packcount = 0;
	rpack = &pack->rpack;
	apack = &pack->apack;
	// format cpack
	if(pack->sendflag && apack->head.nextflag)
	{
		// ��̰�
		reqType = rpack->head.RequestType;
		kcc_memclr(rpack,sizeof(ST_CPACK));
		rpack->head.firstflag = 0;
		rpack->head.nextflag = 1;
		// ʹ���ϴ�����ʱ�������ܺ�
		rpack->head.RequestType = reqType;
		kcc_memcpy(&rpack->head.hook,&apack->head.hook,
				   sizeof(rpack->head.hook));
		// ���������̰�ʹ�õ������ܺ�
		kcc_drtp_set_main_func(atol(apack->head.hook.hostname));
	}
	else
	{
		// һ��ֻ���� 30 ��
		kcc_init_cpack(rpack,1,0,MAX_PACK_LEN);
		m->module.kcc_m_request_cpack(svr,rpack);
		// ��һ�η����������÷��ͱ�־λ
		pack->sendflag = 1;
	}
	if(kcc_drtp_send_cpack(handle,rpack) != 0)
	{
		kcc_write_log(LOG_ERR,"module send cpack error!module[%d]",m->index);
		return -1;
	}
	// ��ȡ���ݰ�
	ret_rows = kcc_drtp_recv_cpack(handle,apack,
								   pack->apackarray,MAX_PACK_LEN);
	kcc_write_log(LOG_DEBUG,"format cpack rows[%d]\n",ret_rows);
	if(ret_rows <= 0)
	{
		kcc_write_log(LOG_ERR,"receive cpack data error.module[%d]",
					  m->index);
		return -1;
	}
	pack->readlen = sprintf(buf,"<?xml version=\"1.0\" encoding=\"%s\"?>",
				  g_xml_encoding);
	if(pack->readlen < 0 )
	{
		return -1;
	}
	buf += pack->readlen;
	readlen = m->module.kcc_m_format_header(svr, buf,buflen-pack->readlen);
	if(readlen < 0)
	{
		return -1;
	}
	pack->readlen += readlen;
	buf += readlen;
	for(i = 0;i < ret_rows;++i)
	{
		readlen = m->module.kcc_m_format_cpack(svr,&pack->apackarray[i],
											   buf,buflen - pack->readlen);
		if(readlen < 0)
		{
			// ���� buffer �����󣬻����������ز��ܴ��� cpack
			kcc_write_log(LOG_ERR,"format result buf error");
			return -1;
		}
		// �������Ϊ0����ʾ����Ҫ����,���Ըð�
		if(readlen > 0)
		{
			pack->packcount++;
			pack->readlen += readlen;
			buf += readlen;
		}
	}
	readlen = m->module.kcc_m_format_tail(svr,buf,buflen-pack->readlen);
	if( readlen < 0 )
	{
		return -1;
	}
	// �������ֵ
	pack->readlen += readlen;
	pack->nextflag = apack->head.nextflag;
	return 0;
}

/** 
 * @brief ͨ�� Socket ����ϵͳ��������
 * 
 * @param sock - ����ϵͳ���ӵ� socket
 * @param m - module struct
 * @param svr - server struct
 * @param buf - ���ݻ���
 * @param len - ���泤��
 * @param ret - ��ϵͳ������
 * 
 * @return - 0 ��ʾ����ɹ���-1 ��ʾ����ʧ��
 */
static int do_socket_process(int sock,struct kcc_module_list *m,
							 struct kcc_server_config * svr,
							 void * buf,int len,
							 ksf_card_result * ret)
{
	// �ȴ�д����
	// write bytes
	ksf_card_info *info = (ksf_card_info*)buf;
	info->length = htonl(info->length);
	info->pack_index = htonl(info->pack_index);
	info->func_no = htonl(info->func_no);
	info->count = htonl(info->count);
	info->next_pack = htonl(info->next_pack);
	kcc_write_log(LOG_DEBUG,"send to server!buf len[%d]",len);
	alarm(g_transfer_timeout);
	if(kcc_write_buf(sock,buf,len) < len )
	{
		alarm(0);
		kcc_write_log(LOG_DEBUG,"send data error!");
		return -1;
	}
	// read bytes
	alarm(0);
	alarm(g_transfer_timeout);
	if(kcc_read_buf(sock,(void*)ret,sizeof(ksf_card_result)) <
	   (int)sizeof(ksf_card_result))
	{
		alarm(0);
		kcc_write_log(LOG_ERR,"read data error!");
		return -1;
	}
	alarm(0);
	ret->pack_index = ntohl(ret->pack_index);
	ret->ret = (ksf_ret_result)ntohl(ret->ret);
	return 0;
}

/** 
 * @brief ����ϵͳ���������ݷ��ظ� drtp 
 * 
 * @param m  - ģ�� struct
 * @param svr  - ��ϵͳ struct
 * @param ret  - ����ֵ struct
 * 
 * @return - 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
static int do_response_to_drtp(struct kcc_module_list * m,
							   struct kcc_server_config * svr,
							   struct cpack_buffer_info * pack,
							   ksf_card_result * ret)
{
	ST_CPACK rpack;
	ST_CPACK apack;
	ST_PACK apackarray[10];
	int retval= -1;
	kcc_init_cpack(&rpack,1,0,1);
	if(m->module.kcc_m_make_return_cpack(&rpack,svr,ret) != 0)
	{
		kcc_write_log(LOG_ERR,"format return pack error!sever[%d]",
					  svr->server_no);
		return -1;
	}
	if(kcc_drtp_send_cpack(pack->handle,&rpack) == 0)
	{
		retval = 0;
		kcc_drtp_recv_cpack(pack->handle,&apack,apackarray,10);
	}
	else
	{
		retval = -1;
		kcc_write_log(LOG_ERR,"send request result error!");
	}
	return retval;
}
/** 
 * @brief ���� kcc pack ��С
 * 
 * @param info - ksf_card_info struct
 * 
 * @return - ���ظ�ֵ��� pack ���ȣ���� info Ϊ NULL ���� 0
 */
static int do_get_kcc_pack_length(ksf_card_info * info)
{
	if(info == NULL)
		return 0;

	return (sizeof(ksf_card_info) - sizeof(info->data) + info->length);
}
/** 
 * @brief ��ʹ�ü����㷨
 * 
 * @param svr - ��ϵͳ
 * @param info - ��������ݰ�
 * @param pack - ��������ݰ�
 * @param enc_type - �����㷨
 * 
 * @return - 0 ��ʾ���ܳɹ���-1 ��ʾ����ʧ��
 */
static int do_encrypt_none(struct kcc_server_config * svr,
						   ksf_card_info * info,
						   struct cpack_buffer_info * pack)
{
	// �����κδ���
	pack->bepad = 0;
	return 0;
}
/** 
 * @brief ʹ�� AES �㷨�������ݼ���,��Կ����Ϊ128λ.��Կͨ����ϵͳ��IP��ַ
 *		  MAC��ַ,�˿ںż��㡣��ϵͳ��ͬ�����㷨������Լ�����Կ��Ȼ���
 *		  ���ݽ��н��ܡ�
 * 
 * @param svr - ��ϵͳ
 * @param info - ��������ݰ�
 * @param pack - ��������ݰ�
 * @param enc_type - �����㷨
 * 
 * @return - 0 ��ʾ���ܳɹ���-1 ��ʾ����ʧ��
 */
static int do_encrypt_with_AES_128(struct kcc_server_config * svr,
							 ksf_card_info * info,
							 struct cpack_buffer_info * pack)
{
	BYTE bin_key[MAXKC<<2] = "";
	char key_meterial[320] = "";
	BYTE md5[16];
	char * p;
	char tmp[4] = "";
	char tokentmp[30]="";
	int i,j;
	int key_length = 128;
	cipherInstance cipher_inst;
	keyInstance key_inst;
	i = 0;
	/***********************************************
	 ����Key ���㷨
	 IP��ַ����λ��Ϊ 0 ~ 3 λ
	 MAC ��ַ��λ��Ϊ 4 ~ 9 λ
	 10 ~ 15 λΪ0 ,Ȼ�����MD5[16Bytes]
	 ��0 ~ 15λ��λȡ���
	*************************************************/
	kcc_memclr(bin_key,sizeof(bin_key));
	// IP
	kcc_strcpy(tokentmp,svr->conf.ip);
	p = kcc_strtok(tokentmp,".");
	while(p != NULL)
	{
		kcc_strncpy(tmp,p,sizeof(tmp));
		bin_key[i++] = (BYTE)kcc_strtoul(tmp,NULL,10);
		p = kcc_strtok(NULL,".");
	}
	if (i != 4)
	{
		kcc_write_log(LOG_ERR,"gen server key error!ip[%s]",
					  svr->conf.ip);
		return -1;
	}
	// MAC
	kcc_strcpy(tokentmp,svr->conf.mac);
	p = kcc_strtok(tokentmp,"-");
	kcc_memclr(tmp,sizeof(tmp));
	while(p != NULL)
	{
		kcc_strncpy(tmp,p,sizeof(tmp));
		bin_key[i++] = (BYTE)kcc_strtoul(tmp,NULL,16);
		p = kcc_strtok(NULL,"-");
	}
	if (i != 10)
	{
		kcc_write_log(LOG_ERR,"gen server key error!MAC[%s]",
					  svr->conf.mac);
		return -1;
	}
	kcc_md5((const char*)bin_key,16,(char*)md5);
	i = 0;
	for(j = 0;j < key_length/8;++j)
	{
		bin_key[j] ^= md5[j];
		i += sprintf(key_meterial+i,"%02X",bin_key[j]);
	}
	key_meterial[key_length/4] = '\0';
	// ����Key���
	//kcc_write_log(LOG_DEBUG,"gen key [%s] server[%d]",
	//			  key_meterial,svr->server_no);
	if(!makeKey(&key_inst,DIR_ENCRYPT,key_length,key_meterial))
	{
		kcc_write_log(LOG_DEBUG,"calc AES 128 key error!");
		return -1;
	}
	if(!cipherInit(&cipher_inst,MODE_ECB,NULL))
	{
		kcc_write_log(LOG_DEBUG,"init cipher [AES 128] error!");
		return -1;
	}

	// �� buf �н��м���
	if( pack->readlen % 16 != 0 )
	{
		// ������� 16 ���ֽڵ�����������Ҫ��
		i = padEncrypt(&cipher_inst,&key_inst,(BYTE*)pack->buf,
					   pack->readlen,(BYTE*)pack->buf);
		if( i > 0 )
		{
			pack->readlen = i;
			pack->bepad = 1;
			return 0;
		}
	}
	else
	{
		if(blockEncrypt(&cipher_inst,&key_inst,(BYTE*)pack->buf,
						pack->readlen << 3,(BYTE*)pack->buf) > 0)
		{
			pack->bepad = 0;
			return 0;
		}
	}
	return -1;
}
/** 
 * @brief ʹ�� AES �㷨�������ݼ���,��Կ����Ϊ128λ.��Կͨ����ϵͳ��IP��ַ
 *		  MAC��ַ,�˿ںż��㡣��ϵͳ��ͬ�����㷨������Լ�����Կ��Ȼ���
 *		  ���ݽ��н��ܡ�
 * 
 * @param svr - ��ϵͳ
 * @param info - ��������ݰ�
 * @param pack - ��������ݰ�
 * @param enc_type - �����㷨
 * 
 * @return - 0 ��ʾ���ܳɹ���-1 ��ʾ����ʧ��
 */
static int do_encrypt_buffer(struct kcc_server_config * svr,
							 ksf_card_info * info,
							 struct cpack_buffer_info * pack,
							 int enc_type)
{
	int ret = -1;
	switch(enc_type)
	{
	default:
	case ENC_TYPE_NONE:
		ret = do_encrypt_none(svr,info,pack);
		break;
	case ENC_TYPE_AES128:
		ret = do_encrypt_with_AES_128(svr,info,pack);
		break;
	}
	// reduce warning
	return ret;
}

/** 
 * @brief ���ɷ��͵����ݰ��ṹ
 * 
 * @param svr - ��ϵͳ struct
 * @param buf - ��������
 * @param len - ���ݳ���
 * @param index - ��ǰ���ı�ţ��� 0 ��ʼ
 * @param next_pack_count - ʣ���������
 * 
 * @return - ���� ksf_card_info ��,������ɹ����� NULL
 * �ð����ڴ��ɸú������룬��ʹ��֮������ͷ�
 */
static ksf_card_info * do_format_kcc_pack(struct kcc_module_list *m,
										  struct kcc_server_config * svr,
										  struct cpack_buffer_info * pack)
{
	ksf_card_info * info = NULL;
	unsigned char md5[16];
	int mlen;
	// ����ǰ�ȼ��� MD5
	kcc_md5(pack->buf,pack->readlen,(char*)md5);
	// TODO : ���Ӷ����ݼ����㷨 
	if(do_encrypt_buffer(svr,info,pack,svr->enc_type) == 0)
	{
		mlen = sizeof(ksf_card_info) + pack->readlen - sizeof(char[1]);
		if((info = (ksf_card_info*)kcc_alloc(mlen)) == NULL)
		{
			kcc_write_log(LOG_ERR,"alloc kcc pack error!");
			return NULL;
		}
		kcc_memcpy(info->CRC,md5,sizeof(info->CRC));
		info->length = pack->readlen;
		info->pack_index = pack->index;
		info->count = pack->packcount;
		info->next_pack = pack->nextflag;
		info->func_no = m->module.kcc_m_get_func_no();
		// ���� copy �Ŀ鲻�ᳬ�� data ����
		info->enc_type = (char)svr->enc_type;
		// �Ƿ�λ
		info->padded = pack->bepad;
		kcc_memcpy(info->data,pack->buf,pack->readlen);
		return info;
	}
	// ����ʧ�ܷ��� NULL
	kcc_write_log(LOG_ERR,"encrypt data buffer error!server[%d]",
				  svr->server_no);
	return NULL;
}
/** 
 * @brief �ӽ��̵��øú�������ָ��ģ�飬ָ������ϵͳ
 * 
 * @param m - ģ�� struct
 * @param svr - ��ϵͳ struct
 */
static int do_child_module_process(struct kcc_module_list *m,
									struct kcc_server_config * svr)
{
	struct cpack_buffer_info pack;
	char buf[CPACK_BUF_LEN] = "";
	int packlen;
	int sock;
	int exit_code;
	int drtp_handle;
	int retval;
	ksf_card_result ret;
	ksf_card_info * info = NULL;
	kcc_memclr(&pack,sizeof(cpack_buffer_info));
	kcc_setup_alarm_handle();
	// ������ϵͳ socket
	if((sock = kcc_sock_connect_to(svr->conf.ip,svr->conf.port))== -1)
	{
		return 4;
	}
	//drtp_handle = kcc_drtp_connect();
	drtp_handle = do_get_drtp_handle();
	if( drtp_handle <= 0 )
	{
		kcc_write_log(LOG_ERR,"get drtp handle error!");
		exit_code = 4;
		goto L_SOCK_END;
	}
	pack.index = 0;
	pack.buf = buf;
	pack.buflen = sizeof(buf);
	pack.handle = drtp_handle;
	pack.sendflag = 0;
	// ���� buf
	while(1)
	{
		// ���û�а�����ѭ��
		if(do_format_request_buffer(m,svr,&pack) == -1)
		{
			kcc_write_log(LOG_ERR,"no data was get!");
			exit_code = 0;
			goto L_DRTP_END;
		}
		// ���� kcc ���ݰ�
		if((info = do_format_kcc_pack(m,svr,&pack)) == NULL)
		{
			kcc_write_log(LOG_ERR,"format kcc pack error!");
			exit_code = 4;
			goto L_DRTP_END;
		}
		packlen = do_get_kcc_pack_length(info);
		// ���� socket ���ݰ�����ȡ��Ӧ��
		kcc_memclr(&ret,sizeof(ret));
		retval = do_socket_process(sock,m,svr,info,packlen,&ret);
		// �˴�һ��Ҫ�ͷ��ڴ�
		kcc_free(info);
		if( retval == 0)
		{
			kcc_write_log(LOG_INFO,"send server[%s] return[%d]",
						  svr->conf.ip,ret.ret);
			exit_code = 0;
			if(ret.ret != RET_OK)
			{
				// �����һ����û�д���ɹ�������ѭ��
				kcc_write_log(LOG_INFO,"server do request return failed.pack [%d]",
							  pack.index);
				exit_code = 3;
				goto L_DRTP_END;
			}
			if(do_response_to_drtp(m,svr,&pack,&ret) == -1)
			{
				kcc_write_log(LOG_INFO,"response to drtp error!pack[%d]",
							  pack.index);
				// �����̨����ʧ�ܷ���
				exit_code = 3;
				goto L_DRTP_END;
			}
		}
		else
		{
			// �������ݰ�����ϵͳʧ�ܣ���Ϊ���������⣬����ѭ��
			kcc_write_log(LOG_INFO,"send server[%s] error!",svr->conf.ip);
			exit_code = 4;
			goto L_DRTP_END;
		}
		pack.index++;
	}
L_DRTP_END:
	//
	do_release_drtp_handle();
L_SOCK_END:
	// �ر� socket
	// ���Socket��Ч,���� g_connect_timeout ֮���˳�
	close(sock);
	// success
	return exit_code;
}

/** 
 * @brief ���Դ���ǰ�ӵ�ϵͳ��ģ���Ƿ��ڽ���
 * 
 * @param m - ģ��
 * @param svr - ��ϵͳ
 * 
 * @return - ����0 ��ʾδ���У�-1��ʾ������
 */
static int do_test_lock_module_process(struct kcc_module_list* m,
									   struct kcc_server_config* svr)
{
	char filename[100] = "";
	char tmp[50] = "";
	kcc_strncpy(filename,g_app_home_path,sizeof(filename));
	kcc_add_path_sep(filename,kcc_strlen(filename));
	kcc_strcat(filename,"pid");
	kcc_add_path_sep(filename,kcc_strlen(filename));

	sprintf(tmp,"%.6d",svr->server_no);
	kcc_strcat(filename,tmp);
	sprintf(tmp,"%.3d",m->index);
	kcc_strcat(filename,tmp);
	kcc_strcat(filename,".pid");
	kcc_write_log(LOG_DEBUG,"gen lock pid file [%s]",filename);
	return kcc_test_lock_file(filename);
}
/** 
 * @brief �����Ҫ�������ݵ���ϵͳ
 * 
 * @param m - ģ��ṹ
 * 
 * @return - �ɹ�������0��ʧ�ܷ��� -1
 */
static int do_get_need_process_server(struct kcc_module_list *m)
{
	struct kcc_server_config * p = g_server_list;
	ST_CPACK rpack;
	ST_CPACK apack;
	ST_PACK apackarray[100];
	int handle;
	char tmp[10] = "";
	int rows;
	int i;
	while(p!= NULL)
	{
		p->needsend = 0;
		p = p->pnext;
	}
	handle = do_get_drtp_handle();
	kcc_init_cpack(&rpack,1,g_get_svr_list_func,100);	
	sprintf(tmp,"%ld",m->module.kcc_m_get_func_no());
	kcc_drtp_set_value(&rpack.head,&rpack.pack,F_LVOL0,tmp);
	if(kcc_drtp_send_cpack(handle,&rpack) == 0)
	{
		rows = kcc_drtp_recv_cpack(handle,&apack,
							   apackarray,sizeof(apackarray));
		if( rows > 0)
		{
			for(i = 0;i < rows ;++i)
			{
				p = g_server_list;
				while(p != NULL)
				{
					if( p->server_no == apackarray[i].lvol1 )
					{
						p->needsend = 1;
						p->enc_type = apackarray[i].lvol3;
						kcc_write_log(LOG_DEBUG,"server[%d] need send",
							p->server_no);
						break;
					}
					p = p->pnext;
				}
			}
		}
		return 0;
	}
	return -1;
}
/** 
 * @brief ����ģ���Ӧ��������ϵͳ
 * 
 * @param m - �����ģ�� struct
 */
static void do_process_per_svr_module(struct kcc_module_list *m)
{
	struct kcc_server_config * svr = g_server_list;
	pid_t pid;
	int ret;
	do_get_need_process_server(m);
	while(svr != NULL)
	{
		if( !svr->needsend )
		{
			goto L_CONTINUE;
		}
		if(do_test_lock_module_process(m,svr) == -1)
		{
			goto L_CONTINUE;
		}
		pid = fork();
		if(pid > 0)
		{
			kcc_write_log(LOG_DEBUG,"module[%d]server[%d]",
				m->index,svr->server_no);
			// ������ 
			goto L_CONTINUE;
		}
		else if(pid == 0)
		{
			// ��Ϊ�ӽ��̼̳��˸����̵���Ϣ����,����ر�
			kcc_sigprocmask(NULL,SIG_UNBLOCK,SIGINT,SIGQUIT);
			// �ӽ��̣��������֮���˳�
			if( do_lock_module_process(m,svr) == -1 )
			{
				kcc_write_log(LOG_ERR,"module[%s]server[%d] maybe run",
							  m->module.module_name,svr->server_no);
				exit(1);
			}
			do_release_drtp_handle();
			ret = do_child_module_process(m,svr);
			kcc_write_log(LOG_INFO,"child process[%d] exit with code[%d]",
						  getpid(),ret);
			exit(ret);
		}
		else
		{
			kcc_write_log(LOG_ERR,"fork child error!");
			return;
		}
L_CONTINUE:
		svr = svr->pnext;
	}
}
/** 
 * @brief ����ͨ��ģ�飬����ģ�鲻�������ض�����ϵͳ
 * 
 * @param m - ģ��ָ�� 
 */
static void do_process_common_module(struct kcc_module_list *m)
{
	//TODO: ��дͨ��ģ�鴦�����

}
/** 
 * @brief ����ģ����д���
 * 
 * @param m - ģ������ͷָ��
 */
static void do_process_module(struct kcc_module_list * m)
{
	switch(m->module.kcc_m_get_module_type())
	{
	case KMT_PER_SVR:
		do_process_per_svr_module(m);
		break;
	case KMT_COMMON:
		do_process_common_module(m);
		break;
	default:
		break;
	}
}

/** 
 * @brief ���÷������б�־Ϊ0
 */
void kcc_stop_server()
{
	server_is_running = 0;
}
/** 
 * @brief �����ܺ���
 */
void kcc_do_main()
{
	struct kcc_module_list * p;
	unsigned long long start_tick,current_tick;
	sigset_t oldsig;
	kcc_memclr(DO_PROCESS_MODULE,sizeof(DO_PROCESS_MODULE));
	server_is_running = 1;
	start_tick = kcc_get_tick_count();
	// ������ʹ��Ĭ�� ALARM ������
	kcc_set_signal(SIGALRM,SIG_DFL);
	while(server_is_running)
	{
		// ���� SIGINT , SIGQUIT �ź�
		kcc_sigprocmask(&oldsig,SIG_BLOCK,SIGINT,SIGQUIT);
		current_tick = kcc_get_tick_count();
		if( g_auto_reload )
		{
			do_reload_modules();
			if( (current_tick - start_tick)/1000 > 
				(unsigned long long)g_reload_timeval )
			{
				start_tick = current_tick;
				kcc_write_log(LOG_INFO,"reload server info!!");
				if(kcc_init_server_list() == -1)
				{
					kcc_write_log(LOG_ERR,"get server list error");
					return;
				}
			}
		}
		kcc_write_log(LOG_INFO,"do main process===================[%lld]!",
			current_tick);
		p = g_module_list;
		while(p != NULL)
		{
			do_process_module(p);
			p = p->pnext;
		}
		kcc_write_log(LOG_INFO,"finished do main process===================[%lld]!",
			kcc_get_tick_count());
		// ������ SIGINT , SIGQUIT
		kcc_sigprocmask(&oldsig,SIG_UNBLOCK,SIGINT,SIGQUIT);
		sleep(g_sleep_timeval);
	}
	do_release_drtp_handle();
}
