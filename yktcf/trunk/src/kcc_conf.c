/** 
 * 模块名				通用前置
 * 文件名				kcc_conf.c
 * 文件实现功能			全局常量的定义
 * 作者					汤成
 * 版本					V0.1
 * 日期					2005-07-05
 * 备注
 * $Id: kcc_conf.c 54 2007-07-25 05:37:07Z xiang.li $
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
long g_run_as_daemon = 0;

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
 * @brief 连接DRTP超时时间
 */
long g_drtp_timeout = 30;
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
 * @brief 第三方DRTP 服务器IP地址，默认本机
 */
char g_des_drtp_svr_ip[21] = "";

/** 
 * @brief 第三方DRTP 服务器主功能号
 */
long g_des_drtp_func_no = 7010;

/** 
 * @brief 第三方DRTP 服务器端口号，默认 4000
 */
long g_des_drtp_svr_port = 4000;

/** 
 * @brief 第三方DRTP 服务器节点号
 */
long g_des_drtp_svr_id = 0;

/** 
 * @brief 发送到第三方服务功能号 
 */
long g_des_main_func = 847351;


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

/** 
* @brief 子系统默认使用的加密方式
*/
long g_default_enc_type = ENC_TYPE_AES128;

///////////////////////////////////////////////////////////////////////
//// function
