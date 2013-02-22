#ifndef _KCC_UTIL_H_
#define _KCC_UTIL_H_
/** 
 * ģ����					ͨ��ǰ��
 * �ļ���					kcc_util.h
 * �ļ�ʵ�ֹ���				����һЩ���ܺ���
 * ����						����
 * �汾						V0.1
 * ����						2005-08-18
 * ��ע
 * $Id$
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a>b?b:a) 

#define kcc_write_log kcc_get_pos(__FILE__,__LINE__),kcc_log_msg

	// common function
	/** 
	 * @brief ��ȡ��ǰ�ļ���������Ϣ���浽��־������ȥ
	 * 
	 * @param filename - �ļ���
	 * @param lineno - �к�
	 */
	void kcc_get_pos(char * filename,int lineno);
	/** 
	 * @brief ��¼������Ϣ������ exit_code ֵ�˳�����
	 * 
	 * @param exit_code - �˳�ֵ
	 * @param fmt - ��ϢFormat �� �� sprintf
	 * @param ... - �䳤����
	 */
	void kcc_die(int exit_code,const char * fmt,...);

	/** 
	 * @brief ��¼��־
	 * 
	 * @param err_level - ��־���� �� �� syslog �����ļ���
	 * @param fmt - format �ַ������� sprintf
	 * @param ... - �䳤����
	 */
	void kcc_log_msg(int err_level,const char * fmt,...);

	/** 
	 * @brief �������
	 */
	void kcc_show_help();

	// mem util
	/** 
	 * @brief memory copy ������ͬ memcpy
	 * 
	 * @param dest - Ŀ��
	 * @param src - Դ
	 * @param len - ��������
	 */
	void kcc_memcpy(void * dest,void * src,int len);

	/** 
	 * @brief memory set ������ͬ memset
	 * 
	 * @param src - Ŀ��
	 * @param value - ÿ�� Byte ��ֵ
	 * @param len - ��С
	 */
	void kcc_memset(void * src,int value,int len);

	/** 
	 * @brief memory compare ������ͬ memcmp
	 * 
	 * @param src - Ŀ��
	 * @param dest - Դ
	 * @param len - ��С 
	 * 
	 * @return - 0 ��ʾ��ȣ�-1 ��ʾ src < dest , 1 ��ʾ src > dest
	 */
	int kcc_memcmp(void* src,void *dest,int len);

	/** 
	 * @brief ��һ���ڴ�����
	 * 
	 * @param src - Ŀ���ڴ�ָ��
	 * @param len - �ڴ���С
	 */
	void kcc_memclr(void* src,int len);

	// mem alloc func
	/** 
	 * @brief ���� size ��С���ڴ�ռ䣬�� malloc
	 * 
	 * @param size - �ڴ�ռ��С
	 * 
	 * @return - ����������ڴ��ַָ��
	 */
	void * kcc_alloc(size_t size);

	/** 
	 * @brief �ͷ��� kcc_alloc ������ڴ�ռ䣬�� free
	 * 
	 * @param p - Ҫ�ͷŵ��ڴ��ַָ��
	 */
	void kcc_free(void * p);

	/** 
	 * @brief - ���µ����ڴ�ռ�Ĵ�С���� realloc
	 * 
	 * @param p - ���������ڴ�ռ��ָ��
	 * @param size - ���������ڴ��С
	 * 
	 * @return - ���ص�������ڴ�ռ�ָ��
	 */
	void * kcc_realloc(void *p,size_t size);

	// string util
	/** 
	 * @brief ȡ���ַ������ȣ� �� strlen
	 * 
	 * @param src - Ŀ���ַ���ָ��
	 * 
	 * @return - �ַ�������
	 */
	int kcc_strlen(const char * src); 

	/** 
	 * @brief �ַ��������� ͬ strcpy
	 * 
	 * @param dest - Ŀ���ַ���
	 * @param src - Դ�ַ���
	 * 
	 * @return - ����Ŀ���ַ���ָ��
	 */
	char* kcc_strcpy(char* dest,const char* src);

	/** 
	 * @brief �ַ���������ͬ strncpy
	 * 
	 * @param dest - Ŀ���ַ���
	 * @param src - Դ�ַ���
	 * @param len - �����ĳ���
	 * 
	 * @return - ����Ŀ���ַ���ָ��
	 */
	char* kcc_strncpy(char* dest,const char* src,int len);

	/** 
	 * @brief �ַ����Ƚϣ�ͬ strcmp
	 * 
	 * @param src - Ŀ���ַ���
	 * @param dest - Ŀ���ַ��� 2
	 * 
	 * @return - src == dest ���� 0
	 *			 src > dest ���� 1
	 *			 src < dest ���� -1
	 */
	int kcc_strcmp(const char* src,const char* dest);

	/** 
	 * @brief �ַ����Ƚϣ�ͬ strncmp����� len <=0 ���� 0
	 * 
	 * @param src - Ŀ���ַ���
	 * @param dest - Ŀ���ַ��� 2 
	 * @param len - �Ƚϳ���
	 * 
	 * @return - src == dest ���� 0
	 *			 src > dest ���� 1
	 *			 src < dest ���� -1
	 */
	int kcc_strncmp(const char* src,const char* dest,int len); 

	/** 
	 * @brief �ַ������� ��ͬ strdup
	 * 
	 * @param src - Դ�ַ���
	 * 
	 * @return - ���ظ��ƺ���ַ�����ָ�룬ʧ�ܷ��� NULL
	 */
	char* kcc_strdup(const char* src);

	/** 
	 * @brief �ַ������ӣ� ͬ strcat
	 * 
	 * @param dest - Ŀ���ַ���
	 * @param src - Դ�ַ���
	 * 
	 * @return - ����Ŀ���ַ���ָ��
	 */
	char* kcc_strcat(char* dest,const char* src);

	/** 
	 * @brief Trim �ַ���
	 * 
	 * @param src - Դ�ַ���
	 * @param dest - Trim�����ַ�����ָ��
	 * @param trim - Ҫ trim ���ַ���trim�����е��ַ�
	 */
	void kcc_str_trim(char* src,char* dest,char* trim);

	/** 
	 * @brief �Ƚ������ַ����Ƿ����
	 * 
	 * @param src - Ŀ���ַ���
	 * @param dest - Ŀ���ַ��� 2
	 * 
	 * @return - ��ȷ��� 1 �����򷵻� 0
	 */
	int kcc_str_equals(const char* src,const char* dest);

	/** 
	 * @brief �ַ�ת���ɴ�д��ͬ toupper
	 * 
	 * @param c - �ַ�
	 * 
	 * @return - ���� ��д�ַ�
	 */
	int kcc_toupper(int c);

	/** 
	 * @brief ���ַ���ת���ɴ�д
	 * 
	 * @param src - Ҫת�����ַ���
	 */
	void kcc_toupper_str(char* src);
	
	/** 
	 * @brief �ַ���ת����������ͬ atoi
	 * 
	 * @param src - Ŀ���ַ��������ΪNULL ������ 0
	 * 
	 * @return - �����ַ�����ʾ������ֵ
	 */
	int kcc_atoi(const char* src);

	/** 
	 * @brief ���ַ���ÿ���ַ�ת���� Hex ֵ�ַ���
	 * 
	 * @param src - Դ�ַ���
	 * @param len - ����
	 * @param value - [out]��� HEX ֵ
	 */
	void kcc_hex2src(const char* src,int len,char* value);

	/** 
	* @brief ���ַ����� delimit �ָ�,ͬ strtok
	* 
	* @param token - Ҫ�ָ���ַ���
	* @param delimit - �ָ��
	* 
	* @return - �򵽷����ַ���ָ��
	*/
	char* kcc_strtok(char* token,const char* delimit);

	/** 
	* @brief ͬ strtoul
	* 
	* @param begin - �ַ�����ʼָ��
	* @param end - �ַ�����βָ���ַ
	* @param base - ����
	* 
	* @return - ת���Ľ��
	*/
	unsigned long kcc_strtoul(const char* begin,char** end,int base);

	// sysutil

	/** 
	 * @brief ������������
	 * 
	 * @param seconds - ����ʱ�� ��λΪ ��
	 */
	void kcc_sleep(int seconds);

	/** 
	 * @brief �� buffer �ж�ȡһ�У����� \n ��β��buffer ������ '\0'����λ
	 * 
	 * @param buf - buffer
	 * @param pos - ��ʼλ��
	 * 
	 * @return - �ҵ�һ�е��ַ�����ָ�룬�ڴ��ɸú������䣬��ʹ�ú����ͷ�
	 */
	char* kcc_str_readline(char* buf,unsigned int pos);

	/** 
	 * @brief ��ȡһ���ļ��� buffer �С�
	 * 
	 * @param fp - FILE ָ��
	 * 
	 * @return - ���� buffer �������ļ����ݣ����ַ����� '\0' ������
	 *			�ڴ��ɸú������룬��ʹ�ú����ͷ�
	 */
	char* kcc_read_file_str(FILE * fp);

	// file descriptor util
	/** 
	 * @brief ���ļ�����������Ϊ ������ģʽ
	 * 
	 * @param fd - �ļ�������
	 */
	void kcc_activate_nonblock(int fd);

	/** 
	 * @brief ���ļ�����������Ϊ����ģʽ
	 * 
	 * @param fd - �ļ�������
	 */
	void kcc_deactivate_nonblock(int fd);

	// 
	/** 
	 * @brief ���·�����Ƿ�Ϊ�ָ�������û�о�����
	 * 
	 * @param path - [in out] ·���ַ���
	 * @param len - ·���ַ�������
	 * 
	 * @return - �����·���ַ����ĳ���
	 */
	int kcc_add_path_sep(char * path,int len);

	/** 
	 * @brief ���·�����Ƿ��зָ��������о�ɾ��
	 * 
	 * @param path - [in out] ·���ַ���
	 * @param len - ·���ַ����ĳ���
	 * 
	 * @return - ���ش�����·���ַ����ĳ���
	 */
	int kcc_trim_path_sep(char * path,int len);


	/** 
	* @brief ȡ�þ�ȷ�������ʱ��
	* 
	* @return - ʱ��
	*/
	long kcc_get_tick_count();

	// socket util
	/** 
	 * @brief ����������� TCP ����
	 * 
	 * @param ip - IP ��ַ��hostname
	 * @param port - �˿�
	 * 
	 * @return - ���ӵ� socket, ���ɹ����� -1
	 */
	int kcc_sock_connect_to(char * ip,int port);

	// md5 util
	/** 
	 * @brief ���� buffer �� MD5
	 * 
	 * @param buf - Ҫ���� MD5 ��buffer
	 * @param len - buffer �ĳ���
	 * @param md5 - [out]�������MD5ֵ������Ϊ 16 ���ֽ�
	 */
	void kcc_md5(const char * buf,int len,char * md5);

	/** 
	* @brief �����ļ���MD5
	* 
	* @param fp - �ļ�ָ��
	* @param md5 - [out] ��������MD5,16�ֽ�
	* 
	* @return - �ɹ�����0,ʧ�ܷ��� -1
	*/
	int kcc_get_file_md5(FILE * fp,char * md5);

	/** 
	 * @brief ����ϵͳ sigprocmask
	 * 
	 * @param oldset - ԭ����sigset_t
	 * @param how - ����sigprocmask��ģʽ����sigprocmask�ֲ�
	 * @param ... - �ɱ��������Ҫ���õ��ź�ֵ
	 * 
	 * @return 
	 */
	int kcc_sigprocmask(sigset_t * oldset,int how,...);

	/** 
	* @brief ��ָ���ļ������ļ�����
	* 
	* @param filename - ���������ļ���
	* @param function - �����������־���� lockf
	* 
	* @return - �ɹ�����0 �� ʧ�ܷ��� -1
	*/
	int kcc_lock_file(const char * filename,int function);

	/** 
	* @brief �����Ƿ����Ϊָ�����ļ�����
	* 
	* @param filename - �ļ���
	* 
	* @return - ���Է���0,ʧ�ܷ��� -1
	*/
	int kcc_test_lock_file(const char* filename);
	/** 
	* @brief ȡ���ļ�����չ��
	* 
	* @param filename - �ļ���
	* @param ext - [out] �����չ��, �� \0 ����
	* @param extlen - [out] �����չ������,���ΪNULL,���������չ������
	* 
	* @return - �ɹ��������� 0 ,ʧ�ܷ��� -1
	*/
	int kcc_get_file_ext(const char* filename,char * ext,int * extlen);
	/** 
	* @brief �����źŴ�����
	* 
	* @param signum - �źű�־
	* @param handler - �������ľ��
	* 
	*/
	void kcc_set_signal(int signum,void (*handler)(int n));

	/** 
	* @brief ���ļ����д����
	* 
	* @param fd - �ļ����
	* @param buf - ��Ҫд������
	* @param len - Buffer �ĳ��� 
	* 
	* @return - ����д�ɹ����ֽ���,ʧ�ܷ��� -1
	*/
	int kcc_write_buf(int fd,void * buf,int len);
	/** 
	* @brief ���ļ����������
	* 
	* @param fd  - �ļ����
	* @param buf - [out] ��ȡ������ݴ������� Buffer ��
	* @param len - Buffer ���������
	* 
	* @return - �ɹ����ض�ȡ�����ݵĳ��� ,ʧ�ܷ��� -1
	*/
	int kcc_read_buf(int fd,void * buf,int len);

	/** 
	 * @brief ʹ���Զ����Alarm ����
	 */
	void kcc_setup_alarm_handle();
#ifdef __cplusplus
}
#endif
#endif // _KCC_UTIL_H_
