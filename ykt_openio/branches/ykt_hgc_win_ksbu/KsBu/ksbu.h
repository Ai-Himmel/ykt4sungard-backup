#ifndef _KSBU_H_
#define _KSBU_H_
#ifdef __cplusplus
extern "C" {
#endif

CLogFile g_LogFile;		// 被移到SvrLink.cpp中，作为系统必要的属性
ST_PACK *g_pArrays;		// 多包时使用
int ERR_DEAL(char *msg,int retcode);

typedef struct _ini_pack_para
{
	int flash_dealy;
	int dynamic_load_flag;
	int sysjones_func;
	char third_part_dll_name[50];
	char user_id[33];
	char pwd[20];
	int port;
	char ip[20];
	char des_dll_name[50];
	int des_flag;
	char encrypt_pwd[20];
	int debug_log;
}ini_pack_para;

ini_pack_para g_ini_para;

#ifdef __cplusplus
}
#endif

#endif // _KSBU_H_
