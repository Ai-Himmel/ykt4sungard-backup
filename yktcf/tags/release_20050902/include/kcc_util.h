#ifndef _KCC_UTIL_H_
#define _KCC_UTIL_H_
/** 
 * 模块名					通用前置
 * 文件名					kcc_util.h
 * 文件实现功能				定义一些功能函数
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-18
 * 备注
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
	 * @brief 获取当前文件名与行信息保存到日志变量中去
	 * 
	 * @param filename - 文件名
	 * @param lineno - 行号
	 */
	void kcc_get_pos(char * filename,int lineno);
	/** 
	 * @brief 记录错误信息，并以 exit_code 值退出程序
	 * 
	 * @param exit_code - 退出值
	 * @param fmt - 信息Format ， 见 sprintf
	 * @param ... - 变长参数
	 */
	void kcc_die(int exit_code,const char * fmt,...);

	/** 
	 * @brief 记录日志
	 * 
	 * @param err_level - 日志级别 ， 见 syslog 函数的级别
	 * @param fmt - format 字符串，见 sprintf
	 * @param ... - 变长参数
	 */
	void kcc_log_msg(int err_level,const char * fmt,...);

	/** 
	 * @brief 输出帮助
	 */
	void kcc_show_help();

	// mem util
	/** 
	 * @brief memory copy 函数，同 memcpy
	 * 
	 * @param dest - 目标
	 * @param src - 源
	 * @param len - 拷贝长度
	 */
	void kcc_memcpy(void * dest,void * src,int len);

	/** 
	 * @brief memory set 函数，同 memset
	 * 
	 * @param src - 目标
	 * @param value - 每个 Byte 的值
	 * @param len - 大小
	 */
	void kcc_memset(void * src,int value,int len);

	/** 
	 * @brief memory compare 函数，同 memcmp
	 * 
	 * @param src - 目标
	 * @param dest - 源
	 * @param len - 大小 
	 * 
	 * @return - 0 表示相等，-1 表示 src < dest , 1 表示 src > dest
	 */
	int kcc_memcmp(void* src,void *dest,int len);

	/** 
	 * @brief 将一块内存清零
	 * 
	 * @param src - 目标内存指针
	 * @param len - 内存块大小
	 */
	void kcc_memclr(void* src,int len);

	// mem alloc func
	/** 
	 * @brief 申请 size 大小的内存空间，见 malloc
	 * 
	 * @param size - 内存空间大小
	 * 
	 * @return - 返回申请的内存地址指针
	 */
	void * kcc_alloc(size_t size);

	/** 
	 * @brief 释放由 kcc_alloc 申请的内存空间，见 free
	 * 
	 * @param p - 要释放的内存地址指针
	 */
	void kcc_free(void * p);

	/** 
	 * @brief - 重新调整内存空间的大小，见 realloc
	 * 
	 * @param p - 被调整的内存空间的指针
	 * @param size - 调整到的内存大小
	 * 
	 * @return - 返回调整后的内存空间指针
	 */
	void * kcc_realloc(void *p,size_t size);

	// string util
	/** 
	 * @brief 取得字符串长度， 见 strlen
	 * 
	 * @param src - 目标字符串指针
	 * 
	 * @return - 字符串长度
	 */
	int kcc_strlen(const char * src); 

	/** 
	 * @brief 字符串拷贝， 同 strcpy
	 * 
	 * @param dest - 目标字符串
	 * @param src - 源字符串
	 * 
	 * @return - 返回目标字符串指针
	 */
	char* kcc_strcpy(char* dest,const char* src);

	/** 
	 * @brief 字符串拷贝，同 strncpy
	 * 
	 * @param dest - 目标字符串
	 * @param src - 源字符串
	 * @param len - 拷贝的长度
	 * 
	 * @return - 返回目标字符串指针
	 */
	char* kcc_strncpy(char* dest,const char* src,int len);

	/** 
	 * @brief 字符串比较，同 strcmp
	 * 
	 * @param src - 目标字符串
	 * @param dest - 目标字符串 2
	 * 
	 * @return - src == dest 返回 0
	 *			 src > dest 返回 1
	 *			 src < dest 返回 -1
	 */
	int kcc_strcmp(const char* src,const char* dest);

	/** 
	 * @brief 字符串比较，同 strncmp，如果 len <=0 返回 0
	 * 
	 * @param src - 目标字符串
	 * @param dest - 目标字符串 2 
	 * @param len - 比较长度
	 * 
	 * @return - src == dest 返回 0
	 *			 src > dest 返回 1
	 *			 src < dest 返回 -1
	 */
	int kcc_strncmp(const char* src,const char* dest,int len); 

	/** 
	 * @brief 字符串复制 ，同 strdup
	 * 
	 * @param src - 源字符串
	 * 
	 * @return - 返回复制后的字符串的指针，失败返回 NULL
	 */
	char* kcc_strdup(const char* src);

	/** 
	 * @brief 字符串增加， 同 strcat
	 * 
	 * @param dest - 目标字符串
	 * @param src - 源字符串
	 * 
	 * @return - 返回目标字符串指针
	 */
	char* kcc_strcat(char* dest,const char* src);

	/** 
	 * @brief Trim 字符串
	 * 
	 * @param src - 源字符串
	 * @param dest - Trim后存放字符串的指针
	 * @param trim - 要 trim 的字符，trim中所有的字符
	 */
	void kcc_str_trim(char* src,char* dest,char* trim);

	/** 
	 * @brief 比较两个字符串是否相等
	 * 
	 * @param src - 目标字符串
	 * @param dest - 目标字符串 2
	 * 
	 * @return - 相等返回 1 ，否则返回 0
	 */
	int kcc_str_equals(const char* src,const char* dest);

	/** 
	 * @brief 字符转换成大写，同 toupper
	 * 
	 * @param c - 字符
	 * 
	 * @return - 返回 大写字符
	 */
	int kcc_toupper(int c);

	/** 
	 * @brief 将字符串转换成大写
	 * 
	 * @param src - 要转换的字符串
	 */
	void kcc_toupper_str(char* src);
	
	/** 
	 * @brief 字符串转换成整数，同 atoi
	 * 
	 * @param src - 目标字符串，如果为NULL ，返回 0
	 * 
	 * @return - 返回字符串表示的整数值
	 */
	int kcc_atoi(const char* src);

	/** 
	 * @brief 将字符串每个字符转换成 Hex 值字符串
	 * 
	 * @param src - 源字符串
	 * @param len - 长度
	 * @param value - [out]输出 HEX 值
	 */
	void kcc_hex2src(const char* src,int len,char* value);

	/** 
	* @brief 将字符串用 delimit 分割,同 strtok
	* 
	* @param token - 要分割的字符串
	* @param delimit - 分割符
	* 
	* @return - 打到返回字符串指针
	*/
	char* kcc_strtok(char* token,const char* delimit);

	/** 
	* @brief 同 strtoul
	* 
	* @param begin - 字符串起始指针
	* @param end - 字符串结尾指针地址
	* @param base - 进制
	* 
	* @return - 转换的结果
	*/
	unsigned long kcc_strtoul(const char* begin,char** end,int base);

	// sysutil

	/** 
	 * @brief 函数进程休眠
	 * 
	 * @param seconds - 休眠时间 单位为 秒
	 */
	void kcc_sleep(int seconds);

	/** 
	 * @brief 从 buffer 中读取一行，行以 \n 结尾，buffer 必须有 '\0'结束位
	 * 
	 * @param buf - buffer
	 * @param pos - 起始位置
	 * 
	 * @return - 找到一行的字符串的指针，内存由该函数分配，在使用后请释放
	 */
	char* kcc_str_readline(char* buf,unsigned int pos);

	/** 
	 * @brief 读取一个文件到 buffer 中。
	 * 
	 * @param fp - FILE 指针
	 * 
	 * @return - 返回 buffer 保存了文件内容，该字符串以 '\0' 结束，
	 *			内存由该函数申请，在使用后请释放
	 */
	char* kcc_read_file_str(FILE * fp);

	// file descriptor util
	/** 
	 * @brief 将文件描述符设置为 非阻塞模式
	 * 
	 * @param fd - 文件描述符
	 */
	void kcc_activate_nonblock(int fd);

	/** 
	 * @brief 将文件描述符设置为阻塞模式
	 * 
	 * @param fd - 文件描述符
	 */
	void kcc_deactivate_nonblock(int fd);

	// 
	/** 
	 * @brief 检查路径后是否为分割符，如果没有就增加
	 * 
	 * @param path - [in out] 路径字符串
	 * @param len - 路径字符串长度
	 * 
	 * @return - 处理后路径字符串的长度
	 */
	int kcc_add_path_sep(char * path,int len);

	/** 
	 * @brief 检查路径后是否有分割符，如果有就删除
	 * 
	 * @param path - [in out] 路径字符串
	 * @param len - 路径字符串的长度
	 * 
	 * @return - 返回处理后的路径字符串的长度
	 */
	int kcc_trim_path_sep(char * path,int len);


	/** 
	* @brief 取得精确到毫秒的时间
	* 
	* @return - 时间
	*/
	long kcc_get_tick_count();

	// socket util
	/** 
	 * @brief 与服务器建立 TCP 连接
	 * 
	 * @param ip - IP 地址或hostname
	 * @param port - 端口
	 * 
	 * @return - 连接的 socket, 不成功返回 -1
	 */
	int kcc_sock_connect_to(char * ip,int port);

	// md5 util
	/** 
	 * @brief 计算 buffer 的 MD5
	 * 
	 * @param buf - 要计算 MD5 的buffer
	 * @param len - buffer 的长度
	 * @param md5 - [out]计算出的MD5值，长度为 16 个字节
	 */
	void kcc_md5(const char * buf,int len,char * md5);

	/** 
	* @brief 计算文件的MD5
	* 
	* @param fp - 文件指针
	* @param md5 - [out] 保存计算的MD5,16字节
	* 
	* @return - 成功返回0,失败返回 -1
	*/
	int kcc_get_file_md5(FILE * fp,char * md5);

	/** 
	 * @brief 调用系统 sigprocmask
	 * 
	 * @param oldset - 原来找sigset_t
	 * @param how - 调用sigprocmask的模式，见sigprocmask手册
	 * @param ... - 可变参数，需要设置的信号值
	 * 
	 * @return 
	 */
	int kcc_sigprocmask(sigset_t * oldset,int how,...);

	/** 
	* @brief 给指定文件名的文件加锁
	* 
	* @param filename - 被加锁的文件名
	* @param function - 加锁或解锁标志，见 lockf
	* 
	* @return - 成功返回0 ， 失败返回 -1
	*/
	int kcc_lock_file(const char * filename,int function);

	/** 
	* @brief 测试是否可以为指定的文件加锁
	* 
	* @param filename - 文件名
	* 
	* @return - 可以返回0,失败返回 -1
	*/
	int kcc_test_lock_file(const char* filename);
	/** 
	* @brief 取得文件的扩展名
	* 
	* @param filename - 文件名
	* @param ext - [out] 输出扩展名, 以 \0 结束
	* @param extlen - [out] 输出扩展名长度,如果为NULL,将不输出扩展名长度
	* 
	* @return - 成功分析返回 0 ,失败返回 -1
	*/
	int kcc_get_file_ext(const char* filename,char * ext,int * extlen);
	/** 
	* @brief 设置信号处理函数
	* 
	* @param signum - 信号标志
	* @param handler - 处理函数的句柄
	* 
	*/
	void kcc_set_signal(int signum,void (*handler)(int n));

	/** 
	* @brief 向文件句柄写数据
	* 
	* @param fd - 文件句柄
	* @param buf - 需要写的数据
	* @param len - Buffer 的长度 
	* 
	* @return - 返回写成功的字节数,失败返回 -1
	*/
	int kcc_write_buf(int fd,void * buf,int len);
	/** 
	* @brief 从文件句柄读数据
	* 
	* @param fd  - 文件句柄
	* @param buf - [out] 读取后的数据存放在这个 Buffer 中
	* @param len - Buffer 的最大容量
	* 
	* @return - 成功返回读取的数据的长度 ,失败返回 -1
	*/
	int kcc_read_buf(int fd,void * buf,int len);

	/** 
	 * @brief 使用自定义的Alarm 函数
	 */
	void kcc_setup_alarm_handle();
#ifdef __cplusplus
}
#endif
#endif // _KCC_UTIL_H_
