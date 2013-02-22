#ifndef _KCC_PARSE_CONF_H_
#define _KCC_PARSE_CONF_H_
/** 
 * 模块名					通用前置
 * 文件名					parseconf.h
 * 文件实现功能				分析配置文件
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-18
 * 备注
 * $Id$
 */

/** 
 * @brief 加载系统配置，该函数通过读取环境变量 YKTCF_HOME 来确定起始目录，
 *			然后读取 起始目录下的 kccconf.ini 文件
 *        配置文件每行长度最多 500 个字符
 */
void kcc_load_server_conf();
/** 
 * @brief 从指定的文件分析配置
 * 
 * @param filename - 文件路径
 * 
 * @return - 成功返回 0 ，否则返回 -1
 */
int kcc_parse_config_file(const char *filename);

#endif // _KCC_PARSE_CONF_H_
