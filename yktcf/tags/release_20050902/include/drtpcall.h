#ifndef _DRTP_CALL_H_
#define _DRTP_CALL_H_
/** 
 * 模块名				通用前置
 * 文件名				drtpcall.h
 * 文件实现功能			封装DRTP库
 * 作者					汤成
 * 版本					V0.1
 * 日期					2005-08-18
 * 备注
 * $Id$
 */

#include "drtp.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** 
	 * @brief 取得 drtp 请求最后一次 Error Code
	 * 
	 * @return - error code 值
	 */
	int kcc_drtp_get_last_err();
	/** 
	 * @brief 取得 drtp 请求最后一次 error message
	 * 
	 * @param msg - message buffer 最大 512 个字节
	 */
	void kcc_drtp_get_last_err_msg(char * msg);

	/** 
	 * @brief 设置调用 DRTP 的主功能号
	 * 
	 * @param mainfunc - 主功能号。如果为 0 ，使用全局变量 g_drtp_func_no
	 *					 的值，该值可以在系统配置中配置
	 */
	void kcc_drtp_set_main_func(long mainfunc);
	/** 
	 * @brief 初始化 drtp 
	 * 
	 * @return 成功返回 0 ， 失败返回 -1
	 */
	int kcc_drtp_init();
	/** 
	 * @brief 连接 DRTP 服务器
	 * 
	 * @return - 返回连接句柄，失败返回 -1
	 */
	int kcc_drtp_connect();
	/** 
	 * @brief 关闭 DRTP 连接
	 * 
	 * @param handle - 连接句柄
	 * 
	 * @return - 成功返回 0 ，失败返回 -1
	 */
	int kcc_drtp_close(int handle);
	/** 
	 * @brief 释放 DRTP 资源
	 * 
	 * @return - 成功返回 0 ，失败返回 -1
	 */
	int kcc_drtp_uninit();
	/** 
	 * @brief 重新连接 DRTP 句柄
	 * 
	 * @param handle - DRTP连接句柄
	 * 
	 * @return - 成功返回 0 ，失败返回 -1
	 */
	int kcc_drtp_reconnect(int handle);
	/** 
	 * @brief 发送 DRTP Buffer
	 * 
	 * @param handle - DRTP 连接句柄
	 * @param buf - 被发送的 Buffer 
	 * @param len - 被发送的 Buffer 的长度
	 * @param mainfunc - DRTP 主功能号
	 * 
	 * @return - 成功返回 0，失败返回 -1
	 */
	int kcc_drtp_send(int handle,char * buf,int len,int mainfunc);
	/** 
	 * @brief 接收 DRTP Buffer
	 * 
	 * @param handle - DRTP 连接句柄
	 * @param buf - 接收的Buffer
	 * @param len - 接收的Buffer最大容量
	 * @param timeout - 超时时间
	 * 
	 * @return - 成功返回接收后 buffer 长度，失败返回 -1
	 */
	int kcc_drtp_receive(int handle,char * buf,int len,int timeout);
	/** 
	 * @brief 设置CPACK字段的值
	 * 
	 * @param head - CPACK包头
	 * @param pack - CPACK数据包
	 * @param ids - CPACK 字段标识
	 * @param data - CPACK 字段值
	 */
	void kcc_drtp_set_value(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data);

	/** 
	 * @brief initialize CPACK struct
	 * 
	 * @param rpack - cpack struct
	 * @param rec_count - cpack record count
	 * @param req_no - cpack request type
	 * @param max_rec - cpack max record count per pack
	 */
	void kcc_init_cpack(ST_CPACK * rpack,int rec_count,int req_no,int max_rec);

	/** 
	 * @brief 发送 CPACK 请求，只支持单包发送,发送时以上次调用
	 * kcc_drtp_set_main_func 设置的主功能号发送包
	 *						 发送之后就主功能号就被设置成为全局默认主功能号
	 * 
	 * @param handle - DRTP 连接句柄
	 * @param rpack - CPACK 包
	 * 
	 * @return - 成功返回 0 ，失败返回 -1
	 */
	int kcc_drtp_send_cpack(int handle,ST_CPACK * rpack);
	
	/** 
	 * @brief 接收 CPACK 请求，最多接收100个包
	 * 
	 * @param handle -DRTP 连接句柄
	 * @param apack - CPACK 包
	 * @param apackarray - 后续数据包 PACK
	 * @param pa_len - apackarray 的长度，有多少个 PACK
	 * 
	 * @return - 成功返回接收的包数量，失败返回 -1
	 */
	int kcc_drtp_recv_cpack(int handle,ST_CPACK * apack,
							ST_PACK * apackarray,int pa_len);
	/** 
	 * @brief 接收 CPACK 请求的后续包，最多接收100个包.
	 * 
	 * @param handle - DRTP 连接句柄
	 * @param req_no - 请求功能号
	 * @param apack - 上次接收后返回的CPACK 包
	 * @param apackarray - 后续数据包 PACK
	 * 
	 * @return - 成功返回接收的数据包的长度，失败返回 -1，
	 *			 如果没有后续包返回 0
	 */
	int kcc_drtp_recv_next_cpack(int handle,int req_no,
								 ST_CPACK *apack,ST_PACK * apackarray);
	/** 
	 * @brief 判断接收的CPACK的头的返回信息
	 * 
	 * @param rpack - 接收的CPACK包
	 * 
	 * @return - 正确包返回 0 
	 *			 无此功能号 -1
	 *			 有错误     1
	 */
	int kcc_drtp_valid_cpack(ST_CPACK * rpack);

#ifdef __cplusplus
}
#endif

#endif // _DRTP_CALL_H_
