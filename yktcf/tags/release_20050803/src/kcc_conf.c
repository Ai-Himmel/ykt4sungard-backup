/** 
 * @file kcc_conf.c
 * @brief ϵͳȫ�ֲ�������
 * @author ����
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
///// ����ȫϵͳ����
/** 
 * @brief ϵͳ�Ƿ�Ϊ daemon ���̣�1 ��ʾ�ǣ�0 ��ʾ����
 */
int g_run_as_daemon = 0;

/** 
 * @brief ϵͳ�ڽ����� g_reload_timeval ֮�����¼������ã�
 *		Ĭ��Ϊ 3 ��
 */
long g_reload_timeval = 259200L;

/** 
 * @brief DRTP ������IP��ַ��Ĭ�ϱ���
 */
char * g_drtp_svr_ip = "127.0.0.1";
/** 
 * @brief DRTP �������˿ںţ�Ĭ�� 4000
 */
long g_drtp_svr_port = 4000;
/** 
 * @brief DRTP �����������ܺ�
 */
long g_drtp_func_no = 8000;
/** 
 * @brief DRTP �������ڵ��
 */
long g_drtp_svr_id = 0;
/** 
 * @brief ϵͳ������һ��ҵ�񣬵ȴ���ʱ��
 */
long g_sleep_timeval = 10;

/** 
 * @brief �Ƿ��Զ����¼�����ϵͳ��Ϣ
 */
int g_auto_reload = 0;

/** 
* @brief ������ϵͳ��ʱʱ��,��λΪ��
*/
long g_connect_timeout = 5;
/** 
* @brief ������������ȴ��ĳ�ʱʱ��,��λΪ��
*/
long g_transfer_timeout = 30;
/** 
* @brief ���͵����� XML ��Encoding
*/
char * g_xml_encoding = "gb2312";
/** 
 * @brief ϵͳ���Լ���
 * 5 �����ϻ���CPACK ����Ϣ
 */
long g_debug_level = 9;

/** 
 * @brief ȫ����ϵͳ�ṹ����
 */
struct kcc_server_config * g_server_list = NULL;

/** 
 * @brief ȫ��ϵͳ Module ����
 */
struct kcc_module_list * g_module_list = NULL;

/** 
* @brief ϵͳ��·��
*/
char * g_app_home_path = NULL;
///////////////////////////////////////////////////////////////////////
/// function

/** 
 * @brief ϵͳ��ȡ��ϵͳ DRTP �Ĺ��ܺ�
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
