#ifndef _KCC_MODULE_H_
#define _KCC_MODULE_H_
/** 
 * 模块名				通用前置
 * 文件名				kcc_module.h
 * 文件实现功能			定义通用前置模块结构
 * 作者					汤成
 * 版本					V0.1
 * 日期					2005-08-18
 * 备注
 * $Id$
 */

#include "drtp.h"
#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif
	/** 
	 * @brief 模块类型枚举变量
	 */
	typedef enum {
		KMT_COMMON = 0,  // 通用模块
		KMT_PER_SVR		 // 每个子系统需要单独处理的模块
	}kcc_module_type;

	/** 
	 * @brief 模块结构
	 */
	struct kcc_module_config
	{
		/** 
		 * @brief 主版本号
		 */
		int major;
		/** 
		 * @brief 次版本号
		 */
		int minor;
		/** 
		* @brief Build 号
		*/
		char build[15];
		/** 
		 * @brief 模块发布日期
		 */
		char date[9];
		/** 
		 * @brief 模块名称
		 */
		char module_name[50 + 1];
		/** 
		 * @brief 加载模块的接口函数，可以为NULL
		 * 
		 */
		int (*kcc_m_load)();
		/** 
		 * @brief 卸载模块的接口函数，可以为NULL
		 * 
		 */
		int (*kcc_m_unload)();
		/** 
		 * @brief 取得模块的在通用前置的功能号
		 * @return - 功能号
		 */
		long (*kcc_m_get_func_no)();
		/** 
		 * @brief 生成请求的 CPACK 包的接口
		 * 
		 * @param svr - 当前子系统结构
		 * @param rpack - [in out]CPACK 结构
		 *
		 * @return - 成功返回 0 ，失败返回 -1
		 */
		int (*kcc_m_request_cpack)(struct kcc_server_config* svr,
								   ST_CPACK* rpack);
		/** 
		 * @brief 生成数据包头接口函数，如 XML 头
		 * 
		 * @param svr - 当前子系统结构
		 * @param buf - [out] 输出的buffer
		 * @param len - buffer 的长度
		 *
		 * @return - 成功返回buffer的长度，失败返回 -1
		 */
		int (*kcc_m_format_header)(struct kcc_server_config* svr,
								   char* buf,int len);
		/** 
		 * @brief 生成数据包的结尾接口
		 * 
		 * @param svr - 当前子系统结构
		 * @param buf - [out] 输出的buffer
		 * @param len - buffer 可容纳的字节数
		 *
		 * @return - 成功返回buffer中的长度，失败返回 -1
		 */
		int (*kcc_m_format_tail)(struct kcc_server_config * svr,
								 char *buf,int len);

        /** 
		 * @brief 发送数据包给第三方接口
		 * 
		 * @param svr - 当前子系统结构
		 * @param buf - [in out] CPACK 结构
		 *
		 * @return - 成功返回 0 ，失败返回 -1
		 */
        int (*kcc_send_third_part_cpack)(struct kcc_server_config* svr,								 
                                         ST_CPACK* rpack, ST_PACK *tmp_pack);

        /** 
		 * @brief 通过 子系统 返回的值生成 CPACK包
		 * 
		 * @param rpack - CPACK 包
		 * @param svr - 子系统结构
		 * @param ret - 子系统 返回结果结构
		 *
		 * @return - 成功返回 0 ，失败返回 -1
		 */
        int (*kcc_recv_third_part_cpack)(ST_CPACK* rpack, struct kcc_server_config* svr,								 
                                         ksf_card_result* ret);
		/** 
		 * @brief 从返回的CPACK数据包，生成数据包
		 * 
		 * @param svr - 当前子系统结构
		 * @param pack - CPACK 数据包
		 * @param buf - [out] 输出的buffer
		 * @param len - buffer 最大容量，（字节数）
		 * 
		 * @return - 成功返回buffer中实际字节数，失败返回 -1
		 */
		int (*kcc_m_format_cpack)(struct kcc_server_config * svr,
								  ST_PACK* pack, char* buf,int len);
		/** 
		 * @brief 通过 子系统 返回的值生成 CPACK包
		 * 
		 * @param rpack - CPACK 包
		 * @param svr - 子系统结构
		 * @param ret - 子系统 返回结果结构
		 *
		 * @return - 成功返回 0 ，失败返回 -1
		 */
		int (*kcc_m_make_return_cpack)(ST_CPACK* rpack,
									   struct kcc_server_config* svr,
									   ksf_card_result* ret);
		/** 
		 * @brief 取得模块类型
		 * 
		 * @return - 返回模块类型
		 */
		kcc_module_type (*kcc_m_get_module_type)();
	};


#ifdef __cplusplus
}
#endif

#endif // _KCC_MODULE_H_
