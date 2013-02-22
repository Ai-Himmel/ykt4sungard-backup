/** 
 * @file kcc_conf.c
 * @brief 系统全局参数定义
 * @author 汤成
 * @date 2005-07-05
 * $Id: kcc_conf.c 4 2005-08-03 10:36:46Z cash $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "parseconf.h"
#include "kcc_conf.h"
#include "kcc_util.h"
#include "servers.h"
///// 定义全系统参数
/** 
 * @brief 系统是否为 daemon 进程，1 表示是，0 表示不是
 */
int g_run_as_daemon = 0;

/** 
 * @brief 系统在进行了 g_reload_timeval 之后重新加载配置，
 *		默认为 3 天
 */
long g_reload_timeval = 259200L;

/** 
 * @brief DRTP 服务器IP地址，默认本机
 */
char * g_drtp_svr_ip = "127.0.0.1";
/** 
 * @brief DRTP 服务器端口号，默认 4000
 */
long g_drtp_svr_port = 4000;
/** 
 * @brief DRTP 服务器主功能号
 */
long g_drtp_func_no = 8000;
/** 
 * @brief DRTP 服务器节点号
 */
long g_drtp_svr_id = 0;
/** 
 * @brief 系统处理完一次业务，等待的时间
 */
long g_sleep_timeval = 10;

/** 
 * @brief 是否自动重新加载子系统信息
 */
int g_auto_reload = 0;

/** 
* @brief 连接子系统超时时间,单位为秒
*/
long g_connect_timeout = 5;
/** 
* @brief 发送数据允许等待的超时时间,单位为秒
*/
long g_transfer_timeout = 30;
/** 
* @brief 发送的数据 XML 的Encoding
*/
char * g_xml_encoding = "gb2312";
/** 
 * @brief 系统调试级别，
 * 5 级以上会打出CPACK 包信息
 */
long g_debug_level = 9;

/** 
 * @brief 全局子系统结构链表
 */
struct kcc_server_config * g_server_list = NULL;

/** 
 * @brief 全局系统 Module 链表
 */
struct kcc_module_list * g_module_list = NULL;

/** 
* @brief 系统根路径
*/
char * g_app_home_path = NULL;
///////////////////////////////////////////////////////////////////////
/// function

/** 
 * @brief 系统读取子系统 DRTP 的功能号
 */
long g_get_svr_list_func = -1;

///////////////////////////////////////////////////////////////////////
//// function
/*
void kcc_load_server_conf()
{
	char * pwd,file_path[256] = "";
	pwd = getenv(KCC_HOME_PATH);
	if(!pwd)
	{
		kcc_die(1,"get current dir error");	
	}
	kcc_strncpy(file_path,pwd,strlen(pwd));
	if(file_path[strlen(pwd)-1] != FILE_SEPERATOR)
	{
		file_path[strlen(pwd)] = FILE_SEPERATOR;
		file_path[strlen(pwd)+1] = '\0';
	}
	kcc_strcat(file_path,KCC_SERVER_CONF_FILE);
	kcc_write_log(LOG_DEBUG,"config file %s",file_path);
	kcc_parse_config_file(file_path);
	// free buffer
	kcc_free(pwd);
}
*/
