/** 
 * 模块名			一卡通通用前置
 * 文件名			servers.c
 * 文件实现功能		主功能流程函数
 * 作者				汤成
 * 版本				V0.3
 * 日期				2005-07-06
 * 备注
 * $Id: servers.c 55 2009-10-11 09:32:03Z tc $
 *
 * 修改时间		版本	作者	说明
 * 2005-9-2		V0.2	汤成	修正了计算密钥可能出现的Bug,
 *								修正了在生产环境连接DRTP的Bug
 * 2005-9-14	V0.3	汤成	增加了对子系统端口的检验
 * 2005-10-22	V0.4	汤成	修正Sleep时间的Bug
 * 2007-06-14   V0.5    李翔    修改了对接第三方以DRTP方式传送数据给KSBCC, KBU. 
 *                              KBU发送数据给第三方提供的dll.
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
* @brief 全局的 DRTP 句柄,由父进程使用,子进程不要使用
*/
static int gs_drtp_handle = -1;

static struct pid_module_server_struct
{
	pid_t pid;
	kcc_module_list * m;
	kcc_server_config * svr;
	char magic[16];				// 通过当前子系统IP与MAC
								// ModuleName 计算出的MD5
}DO_PROCESS_MODULE[MAXPROCESS];

struct cpack_buffer_info
{
	int handle;				// drtp handle
	int index;				// pack index
	int nextflag;			// 是否有后续包
	int buflen;				// buffer 的最大长度
	char * buf;				// buffer 指针
	int readlen;			// 实际读到的长度
	int packcount;			// 生成的包记录条数
	int bepad;				// 如果数据是加密的，则看是否是被补位，如果是为 1 ,否则为 0
	ST_CPACK rpack;			// 请求的CPACK 包
	ST_CPACK apack;			// 应答 CPACK 包
	ST_PACK apackarray[MAX_PACK_LEN];// 保存应答数据包的 PACK 数组
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
 * @brief 删除全局链表中的所有子系统
 * 
 * @param config - 全局子系统链表
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
 * @brief 初始化子系统链表
 * 
 * @return - 成功返回 0 ，不返回 -1
 */
int kcc_init_server_list()
{
	int drtp_handle = -1;
	int retval = -1;
	int rows;
	int i;
	ST_CPACK rpack,apack;
	// 最多100个子系统
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
		char tmp[128] = "400004";
		kcc_drtp_set_value(&rpack.head,&rpack.pack,F_LVOL0,tmp);
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
				if( apackarray[i].lvol2 < 0 ||
					apackarray[i].lvol2 >= 65535 )
				{
					kcc_write_log(LOG_ERR,"server port error[%s][%d]",
								  apackarray[i].sname,apackarray[i].lvol2);
					continue;
				}
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
				svr->des_bcc_func = apackarray[i].lvol4;
				svr->des_port = apackarray[i].lvol5;
				svr->des_drtp_node = apackarray[i].lvol6;
				svr->des_main_func = apackarray[i].lvol7;
				kcc_strncpy(svr->des_ip,apackarray[i].scust_auth,
							sizeof(svr->des_ip));
				// 如果没有设置加密算法，使用系统的默认加密算法
				// TODO: 读取加密标志从 CPACK
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
 * @brief 删除当前系统中所有的模块
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
 * @brief 显示模块信息
 * 
 * @param mentry - Module 指针
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
 * @brief 将模块 struct 增加到模块结尾
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
	{
		p->pnext = m;
		m->index++;
	}
	do_show_module_info(m);
}

/** 
 * @brief 检查模块是不提供了所有需要的接口
 * 
 * @param module - 模块结构
 * 
 * @return - 0 表示正确，-1 表示错误
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
	   (module->kcc_send_third_part_cpack == NULL)||
	   (module->kcc_recv_third_part_cpack == NULL)||
	   (module->kcc_m_get_module_type == NULL)
	  )
	{
		return -1;
	}
	return 0;
}
/** 
 * @brief 通过指定的 path 加载插件，如果加载成功就加入到全局的模块链表中
 * 
 * @param path - 插件路径
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
			// 如果不是文件返回
			return -1;
		}
		if(m->handle != NULL)
		{
			dlclose(m->handle);
			m->handle = NULL;
		}
		if((handle = dlopen(path,RTLD_LAZY)) == NULL)       // linux打开so动态库  
		{
			kcc_write_log(LOG_ERR,"open dl error[%s].",path);
			return -1;
		}
		get_module_info = (lpkcc_get_module_info)
			dlsym(handle,"kcc_get_module_info");          // linux加载函数地址
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
 * @brief 保存当前模块目录的最后修改时间
 * 
 * @param path - 模块目录的路径
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
 * @brief 接口函数 - 初始化子
 * 
 * @return -  成功返回 0 ，不成功 退出程序
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
		if(kcc_str_equals(pent->d_name,".")||
		   kcc_str_equals(pent->d_name,".."))
		{
			continue;
		}
		if(kcc_get_file_ext(pent->d_name,ext,NULL) == -1)
		{
			continue;
		}
		if(!kcc_str_equals(ext,MODULE_EXT))
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
 * @brief 增加一个新的模块
 * 
 * @param fullpath - 模块完整的路径
 * @param filename - 模块的文件名
 * 
 * @return - 0 表示成功，-1 表示失败
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
 * @brief 更新模块，重新加载
 * 
 * @param fullpath - 模块完整路径
 * @param filename - 模块文件名
 * 
 * @return - 0 表示更新成功，-1 表示更新失败
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
	// 标志为正常状态
	m->status = 0;
	if((fp = fopen(fullpath,"r")) == NULL)
	{
		kcc_write_log(LOG_ERR,"load file error");
		return -1;
	}
	kcc_get_file_md5(fp,md5);
	// 不需要重新加载
	if(kcc_memcmp(m->md5str,md5,sizeof(md5)) == 0)
	{
		fclose(fp);
		return 0;
	}
	kcc_memcpy(m->md5str,md5,sizeof(md5));
	fclose(fp);
	if(do_load_module(fullpath,m) == -1)
	{
		// 重新加载失败标志为删除
		m->status = -1;
		return -1;
	}
	return 0;
}

/** 
 * @brief 释放标志为删除的模块
 * 
 * @return - 成功返回 0， 失败返回 -1
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
 * @brief 重新加载检查所有模块
 * 
 * @return - 成功返回 0，失败返回 -1
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
	// 如果时间相同则返回
	if(difftime(info.st_mtime,gs_load_module_time) <= 0 )
	{
		return 0;
	}
	kcc_write_log(LOG_INFO,"reload modules================================");
	gs_load_module_time = info.st_mtime;
	if( (dirptr = opendir(dirname)) == NULL )
	{
		kcc_write_log(LOG_ERR,"open module dir error![%s]",dirname);
		return -1;
	}
	// 更新所有模块的状态为删除
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
	kcc_write_log(LOG_INFO,"finish reload modules================================");
	return 0;
}
/** 
 * @brief 生成发送的数据内容
 * 
 * @param m  - module struct
 * @param svr - server struct
 * @param buf - [out] 计算生成的数据内容
 * @param buflen - [out] buf 的长度
 * 
 * @return - buf 中的数据实际长度 ，0 表示处理失败
 */
static int do_format_request_buffer(struct kcc_module_list *m,
									struct kcc_server_config * svr,
									struct cpack_buffer_info * pack)
{
	ST_CPACK* rpack;
	ST_CPACK* apack;
	int handle;					// DRTP handle	
	int ret_rows;				// 返回CPACK 包行数
//	int i;					
//	int readlen;				// 
	int buflen;					// buffer 的最大长度
	int reqType;
	char * buf;					// buffer

	// 初始化
	handle = pack->handle;
	buf = pack->buf;
	buflen = pack->buflen;
//	pack->readlen = 0;
	pack->packcount = 0;
	rpack = &pack->rpack;
	apack = &pack->apack;
	// format cpack
	if (pack->sendflag)
	{
		if ( apack->head.nextflag && (pack->index >= pack->readlen))
		{
			// 后继包, 并且上一批包已经发送完成
			reqType = rpack->head.RequestType;
			kcc_memclr(rpack,sizeof(ST_CPACK));
			rpack->head.firstflag = 0;
			rpack->head.nextflag = 1;
			// 使用上次请求时的主功能号
			rpack->head.RequestType = reqType;
			kcc_memcpy(&rpack->head.hook,&apack->head.hook,
					   sizeof(rpack->head.hook));
			// 设置请求后继包使用的主功能号
			kcc_drtp_set_main_func(atol(apack->head.hook.hostname));
            // 设置还原点, 可以从数据库继续取后续包
			pack->index = -1;
//			pack->sendflag = 1;
		}
		else if (pack->index < pack->readlen)
		{
			// 当前一批包未有传输完
			return 0;
		}
		else // 没有后继包，且数据取完了
		{
		    return -1;
		}
	}
	else
	{
		// 一次只请求 30 行
		kcc_init_cpack(rpack,1,0,MAX_PACK_LEN);
		m->module.kcc_m_request_cpack(svr,rpack);
		// 第一次发送请求设置发送标志位
		pack->sendflag = 1;
		pack->index = -1;
	}

	if (kcc_drtp_send_cpack(handle, rpack) != 0)
	{
		kcc_write_log(LOG_ERR,"module send cpack error!module[%d]",m->index);
		return -1;
	}
	// 收取数据包
	ret_rows = kcc_drtp_recv_cpack(handle,apack,
								   pack->apackarray,MAX_PACK_LEN);

    
	kcc_write_log(LOG_DEBUG,"format cpack rows[%d]\n",ret_rows);

	if (ret_rows <= 0)
	{
		kcc_write_log(LOG_ERR,"receive cpack data error.module[%d]",
					  m->index);
		return -1;
	}

	pack->readlen = ret_rows;
	/*
	pack->readlen = sprintf(buf,"<?xml version=\"1.0\" encoding=\"%s\"?>",
				  g_xml_encoding);
	*/
	/*
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
	*/
	/*
	for(i = 0;i < ret_rows;++i)
	{
		readlen = m->module.kcc_m_format_cpack(svr,&pack->apackarray[i],
											   buf,buflen - pack->readlen);
		if(readlen < 0)
		{
			// 可能 buffer 不够大，或者其它因素不能处理 cpack
			kcc_write_log(LOG_ERR,"format result buf error");
			return -1;
		}
		// 如果返回为0，表示不需要发送,忽略该包
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
	*/
	// 设置输出值
//	pack->readlen += readlen;
	pack->nextflag = apack->head.nextflag;
	return 0;
}

/** 
 * @brief 通过 Socket 与子系统传输数据
 * 
 * @param sock - 与子系统连接的 socket
 * @param m - module struct
 * @param svr - server struct
 * @param buf - 数据缓存
 * @param len - 缓存长度
 * @param ret - 子系统处理结果
 * 
 * @return - 0 表示处理成功，-1 表示处理失败
 */
static int do_socket_process(int sock,struct kcc_module_list *m,
							 struct kcc_server_config * svr,
							 void * buf,int len,
							 ksf_card_result * ret)
{
	// 等待写数据
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
 * @brief 将子系统处理后的数据返回给 drtp 
 * 
 * @param m  - 模块 struct
 * @param svr  - 子系统 struct
 * @param ret  - 返回值 struct
 * 
 * @return - 0 表示成功，-1 表示失败
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
 * @brief 计算 kcc pack 大小
 * 
 * @param info - ksf_card_info struct
 * 
 * @return - 返回赋值后的 pack 长度，如果 info 为 NULL 返回 0
 */
static int do_get_kcc_pack_length(ksf_card_info * info)
{
	if(info == NULL)
		return 0;

	return (sizeof(ksf_card_info) - sizeof(info->data) + info->length);
}
/** 
 * @brief 不使用加密算法
 * 
 * @param svr - 子系统
 * @param info - 输出的数据包
 * @param pack - 输入的数据包
 * @param enc_type - 加密算法
 * 
 * @return - 0 表示加密成功，-1 表示加密失败
 */
static int do_encrypt_none(struct kcc_server_config * svr,
						   ksf_card_info * info,
						   struct cpack_buffer_info * pack)
{
	// 不做任何处理
	pack->bepad = 0;
	return 0;
}
/** 
 * @brief 使用 AES 算法进行数据加密,密钥长度为128位.密钥通过子系统的IP地址
 *		  MAC地址,端口号计算。子系统以同样的算法计算出自己的密钥，然后对
 *		  数据进行解密。
 * 
 * @param svr - 子系统
 * @param info - 输出的数据包
 * @param pack - 输入的数据包
 * @param enc_type - 加密算法
 * 
 * @return - 0 表示加密成功，-1 表示加密失败
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
	 生成Key 的算法
	 IP地址的四位作为 0 ~ 3 位
	 MAC 地址五位作为 4 ~ 9 位
	 10 ~ 15 位为0 ,然后计算MD5[16Bytes]
	 与0 ~ 15位近位取异或
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
	// 生成Key完成
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

	// 在 buf 中进行加密
	if( pack->readlen % 16 != 0 )
	{
		// 如果不是 16 个字节的整数倍则需要补
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
 * @brief 使用 AES 算法进行数据加密,密钥长度为128位.密钥通过子系统的IP地址
 *		  MAC地址,端口号计算。子系统以同样的算法计算出自己的密钥，然后对
 *		  数据进行解密。
 * 
 * @param svr - 子系统
 * @param info - 输出的数据包
 * @param pack - 输入的数据包
 * @param enc_type - 加密算法
 * 
 * @return - 0 表示加密成功，-1 表示加密失败
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
 * @brief 生成发送的数据包结构
 * 
 * @param svr - 子系统 struct
 * @param buf - 数据内容
 * @param len - 数据长度
 * @param index - 当前包的编号，从 0 开始
 * @param next_pack_count - 剩余包的数量
 * 
 * @return - 返回 ksf_card_info 包,如果不成功返回 NULL
 * 该包的内存由该函数申请，在使用之后必须释放
 */
static ksf_card_info * do_format_kcc_pack(struct kcc_module_list *m,
										  struct kcc_server_config * svr,
										  struct cpack_buffer_info * pack)
{
	ksf_card_info * info = NULL;
	unsigned char md5[16];
	int mlen;
	// 加密前先计算 MD5
	kcc_md5(pack->buf,pack->readlen,(char*)md5);
	// TODO : 增加对数据加密算法 
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
		// 保存 copy 的块不会超过 data 长度
		info->enc_type = (char)svr->enc_type;
		// 是否补位
		info->padded = pack->bepad;
		kcc_memcpy(info->data,pack->buf,pack->readlen);
		return info;
	}
	// 加密失败返回 NULL
	kcc_write_log(LOG_ERR,"encrypt data buffer error!server[%d]",
				  svr->server_no);
	return NULL;
}

/** 
 * @brief 往第三方DRTP发送数据
 * 
 * @param m  - module struct
 * @param svr - server struct
 * @param pack - [in] 从后台获取的pack包
 * 
 * @return 0表示处理成功, 否则表示处理失败
 */
static int do_process_third_part_cpack(struct kcc_module_list *m,
									struct kcc_server_config * svr,
									struct cpack_buffer_info * pack,
									int drtp_handle)
{
	ST_CPACK rpack;
	ST_CPACK apack;
    ST_PACK apackarray[100];
	int handle;					// DRTP handle	
	int rows;				    // 返回CPACK 包行数
//	int i;					
//	int readlen;				 
//	int buflen;					// buffer 的最大长度
//	int reqType;
//	char * buf;					// buffer
    char tmp[21] = ""; 

//	handle = kcc_des_drtp_connect();
    handle = drtp_handle;
	kcc_init_cpack(&rpack, 1, g_des_main_func, 100);

    if (pack->index >= pack->readlen)           // 当前的一批包已经发送完毕
    	    return 1010;
    	    
    if (pack->index == -1)
    {
        // 当前第一包发送，第一包保存在apack里面, 其余放到array里面
        if(m->module.kcc_send_third_part_cpack(svr, &rpack, &(pack->apack.pack)) != 0)
    	{
    		kcc_write_log(LOG_ERR,"format return pack error!sever[%d]",
    					  svr->server_no);
    		return -1;
    	}
    	pack->index = 1;
    }
    else
    {
        if(m->module.kcc_send_third_part_cpack(svr, &rpack, &(pack->apackarray[pack->index])) != 0)
    	{
    		kcc_write_log(LOG_ERR,"format return pack error!sever[%d]",
    					  svr->server_no);
    		return -1;
    	}
    	pack->index++;
    }
	
	if (kcc_des_drtp_send_cpack(handle, &rpack) == 0)
	{
	    kcc_memclr(&apack,sizeof apack);		
	    kcc_memclr(&apackarray,sizeof apackarray);		
	    kcc_write_log(LOG_DEBUG,"waiting receive drpt [%d][%s]",g_des_main_func,tmp);		
	    rows = kcc_drtp_recv_cpack(handle, &apack, apackarray, sizeof(apackarray));
        if (rows == 1)
        {
            if (apack.pack.lvol10 == 10)            // 当前数据发送成功
                return 0;               
            else 
                return 1001;                         // 当前数据未有发送成功
        }
	    /*
        if (rows == 0)
        {
            return 1001;             // 没有数据返回，可能超时或者其他原因
        }
        else if (rows == 1)
        {
            if (apack.pack.lvol10 == 10)    // 正确返回
                return 0;
        }
        else
        {
            return 1000;                // 暂时不做处理
        }
        */
	}
	return -1;
}

/** 
 * @brief 子进程调用该函数处理指定模块，指定的子系统
 * 
 * @param m - 模块 struct
 * @param svr - 子系统 struct
 */
static int do_child_module_process(struct kcc_module_list *m,
									struct kcc_server_config * svr)
{
	struct cpack_buffer_info pack;
	char buf[CPACK_BUF_LEN] = "";
//	int packlen;
//	int sock;
	int exit_code;
	int drtp_handle;
	int drtp_third_part_handle;
	int retval;
	ksf_card_result ret;
//	ksf_card_info * info = NULL;
	kcc_memclr(&pack,sizeof(cpack_buffer_info));
	kcc_setup_alarm_handle();           
	// 连接子系统 drtp
	drtp_third_part_handle = kcc_des_drtp_connect();
	if (drtp_third_part_handle <= 0)
	{
		kcc_write_log(LOG_ERR,"get des drtp handle error!");
		exit_code = 4;
		goto L_SOCK_END;
	}
	/*
	if((sock = kcc_sock_connect_to(svr->conf.ip,svr->conf.port))== -1)
	{
		return 4;
	}
	*/
//	drtp_handle = kcc_drtp_connect();
	do_release_drtp_handle();
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
	pack.readlen = 0;
	// 生成 buf
	while(1)
	{
		// 如果没有包跳出循环
		if (do_format_request_buffer(m,svr,&pack) == -1)
		{
			kcc_write_log(LOG_ERR,"no data was get!");
			exit_code = 0;
			goto L_DRTP_END;
		}
		/*
		if( pack.readlen == 0 )
		{
			// 没有收到数据包返回
			exit_code = 0;
			goto L_DRTP_END;
		}
		*/
		// 生成 ksbcc 数据包, 能够往windows平台bu上发送数据包
        if ((retval = do_process_third_part_cpack(m, svr, &pack, drtp_third_part_handle)) == -1)
        {
            kcc_write_log(LOG_ERR,"no data was get!");
			exit_code = 0;
			goto L_DRTP_END;    
        }

        if (retval == 1010)
            continue;

        if (retval == 1001)
        {
            pack.index--;
            continue;
        }

		/*
		if((info = do_format_kcc_pack(m,svr,&pack)) == NULL)
		{
			kcc_write_log(LOG_ERR,"format kcc pack error!");
			exit_code = 4;
			goto L_DRTP_END;
		}
		*/
		
//		packlen = do_get_kcc_pack_length(info);
		// 发送 socket 数据包，并取得应答
//		kcc_memclr(&ret,sizeof(ret));
//		retval = do_socket_process(sock,m,svr,info,packlen,&ret);
		// 此处一定要释放内存
//		kcc_free(info);
//      retval = do_recv_third_part_cpack();
		if (retval == 0)
		{
			kcc_write_log(LOG_INFO,"send server[%s] return[%d]",
						  svr->conf.ip,ret.ret);
			exit_code = 0;
			/*
			if(ret.ret != RET_OK)
			{
				// 如果上一个包没有处理成功，跳出循环
				kcc_write_log(LOG_INFO,"server do request return failed.pack [%d]",
							  pack.index);
				exit_code = 3;
				goto L_DRTP_END;
			}
			*/
			
			if(do_response_to_drtp(m, svr, &pack, &ret) == -1)
			{
				kcc_write_log(LOG_INFO,"response to drtp error!pack[%d]",
							  pack.index);
				// 如果后台处理失败返回
				exit_code = 3;
				goto L_DRTP_END;
			}
		}
		else
		{
			// 发送数据包到子系统失败，认为网络有问题，跳出循环
			kcc_write_log(LOG_INFO,"send server[%s] error!",svr->conf.ip);
			exit_code = 4;
			goto L_DRTP_END;
		}
//		pack.index++;
	}
L_DRTP_END:
	//
	do_release_drtp_handle();
	kcc_drtp_close(drtp_third_part_handle);
L_SOCK_END:
	// 关闭 socket
	// 如果Socket无效,则在 g_connect_timeout 之后退出
//	close(sock);
	// success
	return exit_code;
}

/** 
 * @brief 测试处理当前子的系统的模块是否还在进行
 * 
 * @param m - 模块
 * @param svr - 子系统
 * 
 * @return - 返回0 表示未运行，-1表示已运行
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
 * @brief 检查需要发送数据的子系统
 * 
 * @param m - 模块结构
 * 
 * @return - 成功处理返回0，失败返回 -1
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
	//do_release_drtp_handle();
	handle = do_get_drtp_handle();
	kcc_init_cpack(&rpack,1,g_get_svr_list_func,100);	
	sprintf(tmp,"%ld",m->module.kcc_m_get_func_no());
	kcc_drtp_set_value(&rpack.head,&rpack.pack,F_LVOL0,tmp);
	if(kcc_drtp_send_cpack(handle,&rpack) == 0)
	{
		kcc_memclr(&apack,sizeof apack);
		kcc_memclr(&apackarray,sizeof apackarray);
		kcc_write_log(LOG_DEBUG,"waiting receive drpt [%d][%s]"
					  ,g_get_svr_list_func,tmp);
		rows = kcc_drtp_recv_cpack(handle,&apack,
								   apackarray,sizeof(apackarray));
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
					p->des_bcc_func = apackarray[i].lvol4;
				    p->des_port = apackarray[i].lvol5;
				    p->des_drtp_node = apackarray[i].lvol6;
				    p->des_main_func = apackarray[i].lvol7;
				    kcc_strncpy(p->des_ip,apackarray[i].scust_auth,
							sizeof(p->des_ip));
					break;
				}
				p = p->pnext;
			}
		}
		return 0;
	}
	return -1;
}
/** 
 * @brief 处理模块对应的所有子系统
 * 
 * @param m - 处理的模块 struct
 */
static void do_process_per_svr_module(struct kcc_module_list *m)
{
	struct kcc_server_config * svr = g_server_list;
	pid_t pid;
	int ret;
	//do_release_drtp_handle();
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
		    /*
			g_des_drtp_func_no = svr->des_bcc_func;
	        g_des_drtp_svr_port = svr->des_port;
	        g_des_drtp_svr_id = svr->des_drtp_node;
	        g_des_main_func = svr->des_main_func;
            kcc_strncpy(g_des_drtp_svr_ip, svr->des_ip, sizeof(g_des_drtp_svr_ip));
			ret = do_child_module_process(m,svr);
			exit(ret);
			*/
			// 父进程 
			goto L_CONTINUE;
		}
		else if(pid == 0)
		{
			// 因为子进程继承了父进程的信息处理,必须关闭
			kcc_sigprocmask(NULL,SIG_UNBLOCK,SIGINT,SIGQUIT);   
			// 子进程，处理完成之后退出
			if( do_lock_module_process(m,svr) == -1 )
			{
				kcc_write_log(LOG_ERR,"module[%s]server[%d] maybe run",
							  m->module.module_name,svr->server_no);
				exit(1);
			}
			//do_release_drtp_handle();
			//kcc_drtp_uninit();
			/*
			if(kcc_drtp_init() !=0)
			{
				kcc_die(1,"init drpt error!");
			}
			*/
			g_des_drtp_func_no = svr->des_bcc_func;
	        g_des_drtp_svr_port = svr->des_port;
	        g_des_drtp_svr_id = svr->des_drtp_node;
	        g_des_main_func = svr->des_main_func;
            kcc_strncpy(g_des_drtp_svr_ip, svr->des_ip, sizeof(g_des_drtp_svr_ip));
			ret = do_child_module_process(m,svr);
			kcc_write_log(LOG_INFO,"child process[%d] exit with code[%d]",
						  getpid(),ret);
			//kcc_drtp_uninit();
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
 * @brief 处理通用模块，这种模块不依赖于特定的子系统
 * 
 * @param m - 模块指针 
 */
static void do_process_common_module(struct kcc_module_list *m)
{
	//TODO: 编写通用模块处理代码

}
/** 
 * @brief 遍历模块进行处理
 * 
 * @param m - 模块链表头指针
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
 * @brief 设置服务运行标志为0
 */
void kcc_stop_server()
{
	server_is_running = 0;
}
/** 
 * @brief 主功能函数
 */
void kcc_do_main()
{
	struct kcc_module_list * p;
	unsigned long long start_tick,current_tick;
	kcc_memclr(DO_PROCESS_MODULE,sizeof(DO_PROCESS_MODULE));
	server_is_running = 1;
	start_tick = kcc_get_tick_count();
	// 主进程使用默认 ALARM 处理函数
	kcc_set_signal(SIGALRM,SIG_DFL);
	while(server_is_running)
	{
		// 阻塞 SIGINT , SIGQUIT 信号
		//kcc_sigprocmask(&oldsig,SIG_BLOCK,SIGINT,SIGQUIT);
		current_tick = kcc_get_tick_count();
		/*
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
		*/
		kcc_write_log(LOG_INFO,"do main process===================[%ld]!",
			current_tick);
		p = g_module_list;
		while(p != NULL)
		{
			kcc_write_log(LOG_INFO,"do modules[%d][%s]"
						  ,p->index,p->module.module_name);
			do_process_module(p);
			p = p->pnext;
			kcc_sleep(1);
		}
		kcc_write_log(LOG_INFO,"finished do main process===================[%ld][%d]!",
			kcc_get_tick_count(),g_sleep_timeval);
		// 当有子进程退出后，父进程处理 SIGCHLD, 则 sleep 将被中断
		// 根据 sleep 返回的值大于0 判断是否要继续 sleep
		kcc_sleep(g_sleep_timeval);
	}
	do_release_drtp_handle();
}
