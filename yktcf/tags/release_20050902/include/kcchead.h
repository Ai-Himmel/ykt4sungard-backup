#ifndef _KCC_HEAD_H_
#define _KCC_HEAD_H_
/** 
 * 模块名					通用前置
 * 文件名					kcchead.h
 * 文件实现功能				定义子系统结构
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-18
 * 备注
 * $Id$
 */


#include <dlfcn.h>
#include "def.h"
#include "kcc_module.h"

//#define ip conf.ip
//#define mac conf.mac
//#define port conf.port

#ifdef __cplusplus
extern "C" {
#endif
	/** 
	 * @brief 子系统定义结构
	 */
	struct kcc_server_config 
	{
		/** 
		 * @brief 子系统编号
		 */
		int server_no;
		/** 
		* @brief 当前子系统是否需要处理,0 表示不需要,1表示需要
		*/
		int needsend;
		/** 
		* @brief 当前子系统使用的加密算法
		*/
		int enc_type;
		/** 
		 * @brief 子系统结构
		 */
		ksf_server_conf conf;
		/** 
		 * @brief 指向下一个子系统结构
		 */
		struct kcc_server_config * pnext;
	};


	/** 
	 * @brief 模块接口函数
	 */
	typedef int (*lpkcc_get_module_info)(struct kcc_module_config * config);

	/** 
	 * @brief dl 句柄定义
	 */
	typedef void * dlhandle;

	/** 
	 * @brief 模块链表结构
	 */
	struct kcc_module_list
	{
		/** 
		* @brief 模块文件名
		*/
		char file[128];
		/** 
		 * @brief 指向下一个模块的指针
		 */
		struct kcc_module_list * pnext;
		/** 
		 * @brief 模块索引号
		 */
		int index;
		/** 
		 * @brief 模块结构
		 */
		struct kcc_module_config module;
		/** 
		* @brief 当前MODULE的MD5
		*/
		char md5str[16];
		/** 
		* @brief 模块状态,0 表示有效,-1表示无效
		*/
		int status;
		/** 
		 * @brief 模块 dl 句柄
		 */
		dlhandle handle;
		/** 
		 * @brief 模块接口函数指针
		 */
		lpkcc_get_module_info get_module_info;
	};


#ifdef __cplusplus
}
#endif

#endif // _KCC_HEAD_H_
