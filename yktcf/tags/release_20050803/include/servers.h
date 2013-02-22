#ifndef _SERVERS_H_
#define _SERVERS_H_

#include <dlfcn.h>
#include <sys/types.h>
#include "def.h"
#include "kcchead.h"
#include "kcc_module.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** 
	* @brief 删除子系统列表
	* 
	*/
	void kcc_release_server_list();
	/** 
	 * @brief 初始化子系统链表的函数
	 * 
	 * @return - 返回 0 表示成功，返回 -1 表示失败
	 */
	int kcc_init_server_list();

	/** 
	 * @brief 主函数
	 */
	void kcc_do_main();

	/** 
	 * @brief 清除当前系统的所有模块
	 */
	void kcc_clear_modules();

	/** 
	 * @brief 加载模块，在加载之前该函数会调用 kcc_clear_modules 函数
	 * 
	 * @return 0 表示加载成功，-1 表示加载失败
	 */
	int kcc_init_modules();

	/** 
	* @brief 将子进程从运行子进程列表中删除
	* 
	* @param pid 
	*/
	void kcc_remove_pid_from_process(pid_t pid);
	/** 
	* @brief 停止服务程序
	*/
	void kcc_stop_server();
#ifdef __cplusplus
}
#endif

#endif // _SERVERS_H_
