#ifndef _MODULE_BLK_H_
#define _MODULE_BLK_H_
/** 
 * 模块名					更新客户信息名单
 * 文件名					newcard.h
 * 文件实现功能				更新客户信息名单头文件
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-09-05
 * 备注
 * $Id$
 */

#include "kcc_module.h"
#include "kcchead.h"

#ifdef __cplusplus
extern "C" {
#endif

	int kcc_get_module_info(struct kcc_module_config * c);

#ifdef __cplusplus
}
#endif
#endif // _MODULE_BLK_H_
