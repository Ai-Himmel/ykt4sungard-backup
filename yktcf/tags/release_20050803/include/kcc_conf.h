#ifndef _KCC_CONF_H_
#define _KCC_CONF_H_

#include "def.h"
#include "servers.h"

#define KCC_VERSION "1.0"
#define KCC_NAME "yktcf"
#define KCC_HOME_PATH "YKTCF_HOME"
#define KCC_SERVER_CONF_FILE "kccconf.ini"
#define KCC_MODULE_PATH "modules"

#ifdef WIN32
#define FILE_SEPERATOR '\\'
#else
#define FILE_SEPERATOR '/'
#endif


// 服务参数
extern int g_run_as_daemon;
extern long g_reload_timeval;
extern char * g_drtp_svr_ip;
extern long g_drtp_svr_port;
extern long g_drtp_func_no;
extern long g_drtp_svr_id;
extern int g_auto_reload;
extern long g_sleep_timeval;
extern long g_connect_timeout;
extern char * g_xml_encoding;
extern long g_transfer_timeout;
extern struct kcc_server_config * g_server_list;

extern long g_get_svr_list_func;

extern char * g_app_home_path;

extern long g_debug_level;
extern struct kcc_module_list * g_module_list;

/// server function

#endif // _KCC_CONF_H_
