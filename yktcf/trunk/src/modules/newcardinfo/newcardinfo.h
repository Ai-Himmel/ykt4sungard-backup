#ifndef _NEW_CARD_INFO_H_
#define _NEW_CARD_INFO_H_
/** 
 * 模块名					查询卡信息
 * 文件名					newcardinfo.h
 * 文件实现功能				查询卡信息名单头文件
 * 作者						李翔
 * 版本						V0.1
 * 日期						2007-06-05
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
