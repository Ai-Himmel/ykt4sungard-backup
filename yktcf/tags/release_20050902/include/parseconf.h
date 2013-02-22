#ifndef _KCC_PARSE_CONF_H_
#define _KCC_PARSE_CONF_H_
/** 
 * ģ����					ͨ��ǰ��
 * �ļ���					parseconf.h
 * �ļ�ʵ�ֹ���				���������ļ�
 * ����						����
 * �汾						V0.1
 * ����						2005-08-18
 * ��ע
 * $Id$
 */

/** 
 * @brief ����ϵͳ���ã��ú���ͨ����ȡ�������� YKTCF_HOME ��ȷ����ʼĿ¼��
 *			Ȼ���ȡ ��ʼĿ¼�µ� kccconf.ini �ļ�
 *        �����ļ�ÿ�г������ 500 ���ַ�
 */
void kcc_load_server_conf();
/** 
 * @brief ��ָ�����ļ���������
 * 
 * @param filename - �ļ�·��
 * 
 * @return - �ɹ����� 0 �����򷵻� -1
 */
int kcc_parse_config_file(const char *filename);

#endif // _KCC_PARSE_CONF_H_
