/** 
 * ģ����				ͨ��ǰ��
 * �ļ���				kcc_conf.c
 * �ļ�ʵ�ֹ���			ȫ�ֳ����Ķ���
 * ����					����
 * �汾					V0.1
 * ����					2005-07-05
 * ��ע
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
///// ����ȫϵͳ����
/** 
 * @brief ϵͳ�Ƿ�Ϊ daemon ���̣�1 ��ʾ�ǣ�0 ��ʾ����
 */
long g_run_as_daemon = 0;

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
 * @brief ����DRTP��ʱʱ��
 */
long g_drtp_timeout = 30;
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
 * @brief ������DRTP ������IP��ַ��Ĭ�ϱ���
 */
char g_des_drtp_svr_ip[21] = "";

/** 
 * @brief ������DRTP �����������ܺ�
 */
long g_des_drtp_func_no = 7010;

/** 
 * @brief ������DRTP �������˿ںţ�Ĭ�� 4000
 */
long g_des_drtp_svr_port = 4000;

/** 
 * @brief ������DRTP �������ڵ��
 */
long g_des_drtp_svr_id = 0;

/** 
 * @brief ���͵������������ܺ� 
 */
long g_des_main_func = 847351;


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

/** 
* @brief ��ϵͳĬ��ʹ�õļ��ܷ�ʽ
*/
long g_default_enc_type = ENC_TYPE_AES128;

///////////////////////////////////////////////////////////////////////
//// function
