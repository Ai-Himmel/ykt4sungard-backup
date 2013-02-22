/** 
 * ģ����				һ��ͨͨ��ǰ��ϵͳ 
 * �ļ���				parseconf.c
 * �ļ�ʵ�ֹ���			�������������ļ�
 * ����					����
 * �汾					V0.1
 * ����					2005-07-05
 * ��ע
 * $Id: parseconf.c 22 2005-08-16 03:14:06Z cash $
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

#include "kcc_conf.h"
#include "kcc_util.h"
#include "parseconf.h"

/** 
 * @brief ϵͳ�����е� ���� ����
 */
static struct kcc_bool_setting_conf
{
	char * conf_name;
	int * conf_value;
}
parse_bool_conf_ary[]=
{
	{"autoreload",&g_auto_reload},
	{NULL,NULL}
};

/** 
 * @brief ϵͳ�����е��ַ�������
 */
static struct kcc_string_setting_conf
{
	char * conf_name;
	char ** conf_value;
}
parse_string_conf_ary[] =
{
	{"drtpip",&g_drtp_svr_ip},
	{"xmlencoding",&g_xml_encoding},
	{NULL,NULL}
};

/** 
 * @brief ϵͳ�����еĳ����α��� 
 */
static struct kcc_uint_setting_conf
{
	char * conf_name;
	long * conf_value;
}
parse_uint_conf_ary[] =
{
	{"drtpfuncno",&g_drtp_func_no},
	{"drtpsvrport",&g_drtp_svr_port},
	{"reloadtimeval",&g_reload_timeval},
	{"drtpsvrid",&g_drtp_svr_id},
	{"get_svr_list_func",&g_get_svr_list_func},
	{"debuglevel",&g_debug_level},
	{"sleep_timeval",&g_sleep_timeval},
	{"connecttimeout",&g_connect_timeout},
	{"trasfertimeout",&g_transfer_timeout},
	{"defaultenctype",&g_default_enc_type},
	{NULL,NULL}
};

/** 
 * @brief ���ַ���ͨ�� spe �ָ������
 * 
 * @param line - [in out]���ָ���ַ����������� '\0' ����,
 *						�ָ���һ����Ҳ���ڸ�ָ��λ��
 * @param value - [out] �ָ��ĵڶ����֣��� '\0' ���� 
 * @param spe - �ָ��ַ�
 * 
 * @return - �ɹ����� 0 �����ɹ����� -1
 */
static int splite_line(char * line,char *value,char spe)
{
	int pos = 0;
	while(line[pos] != '\0' && line[pos] != spe) 
		pos++;
	if(line[pos] == '\0')
		return -1;
	kcc_strcpy(value,line+pos+1);
	kcc_str_trim(value,value," \t");
	line[pos] = '\0';
	kcc_str_trim(line,line," \t");
	return 0;
}

/** 
 * @brief ����һ������
 * 
 * @param line - �������ݣ��� '\0' ����
 */
static void handle_option_line(char * line)
{
	char value[512] = "";
	if(!splite_line(line,value,'='))
	{
		const struct kcc_bool_setting_conf * p_bool_config = 
			parse_bool_conf_ary;
		while(p_bool_config->conf_name != NULL)
		{
			if(kcc_str_equals(p_bool_config->conf_name,line))
			{
				kcc_toupper_str(value);
				if(kcc_str_equals("TRUE",value)||
				   kcc_str_equals("1",value))
					*(p_bool_config->conf_value) = 1;
				else if(kcc_str_equals("FALSE",value)||
						kcc_str_equals("0",value))
					*(p_bool_config->conf_value) = 0;
				else
					kcc_die(2,"bad bool value!");

			}
			p_bool_config++;
		}
		const struct kcc_uint_setting_conf * p_uint_config = 
			parse_uint_conf_ary;
		while(p_uint_config->conf_name != NULL)
		{
			if(kcc_str_equals(p_uint_config->conf_name,line))
			{
				*(p_uint_config->conf_value) = atol((const char*)value);
			}
			p_uint_config++;
		}
		const struct kcc_string_setting_conf * p_string_config = 
			parse_string_conf_ary;
		while(p_string_config->conf_name != NULL)
		{
			if(kcc_str_equals(p_string_config->conf_name,line))
			{
				if( kcc_strlen(value) == 0 )
				{
					continue;
				}
				*(p_string_config->conf_value) = kcc_strdup((const char*)value);
			}
			p_string_config++;
		}
	}
}

/** 
 * @brief ����ϵͳ����
 */
void kcc_load_server_conf()
{
	char file_path[256] = "";
	kcc_strncpy(file_path,g_app_home_path,
				kcc_strlen(g_app_home_path));
	kcc_add_path_sep(file_path,kcc_strlen(file_path));
	kcc_strcat(file_path,KCC_SERVER_CONF_FILE);
	kcc_write_log(LOG_DEBUG,"config file %s",file_path);
	kcc_parse_config_file(file_path);
	// free buffer
	//kcc_free(pwd);
}

int kcc_parse_config_file(const char *filename)
{
	FILE * fp;
	char * buf = NULL;
	char * line = NULL;
	unsigned int pos,file_len;
	if(!(fp = fopen(filename,"r")))
	{
		kcc_die(1,"load config file error!");
	}
	buf = kcc_read_file_str(fp);
	file_len = kcc_strlen(buf);
	pos = 0;
	while(pos < file_len
		&&(line = kcc_str_readline(buf,pos)) != 0)
	{
		if(line == NULL)
			break;
		pos += kcc_strlen(line) + 1;
		kcc_str_trim(line,line," \t");
		// if it is a comment line
		if(line[0] != '#' && kcc_strlen(line) > 1)
			handle_option_line(line);
		kcc_free(line);
	}
	kcc_free(buf);
	fclose(fp);
	return 0;
}
