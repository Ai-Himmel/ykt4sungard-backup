/** 
 * 模块名				一卡通通用前置系统 
 * 文件名				parseconf.c
 * 文件实现功能			分析处理配置文件
 * 作者					汤成
 * 版本					V0.1
 * 日期					2005-07-05
 * 备注
 * $Id: parseconf.c 22 2005-08-16 03:14:06Z cash $
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

#include "kcc_conf.h"
#include "kcc_util.h"
#include "parseconf.h"

/** 
 * @brief 系统配置中的 开关 变量
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
 * @brief 系统配置中的字符串变量
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
 * @brief 系统配置中的长整形变量 
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
 * @brief 将字符串通过 spe 分割成两块
 * 
 * @param line - [in out]被分割的字符串，必须以 '\0' 结束,
 *						分割后第一部分也放在该指针位置
 * @param value - [out] 分割后的第二部分，以 '\0' 结束 
 * @param spe - 分割字符
 * 
 * @return - 成功返回 0 ，不成功返回 -1
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
 * @brief 处理一行配置
 * 
 * @param line - 配置内容，以 '\0' 结束
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
 * @brief 加载系统配置
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
