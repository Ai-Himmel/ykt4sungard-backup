#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_
#pragma once 

#define CHARGE_TERMINAL			0x01			// 收费终端
#define MANAGE_CENTER			(0x01 << 1)		// 管理中心
#define SAVING_POS				(0x01 << 2)		// 充值终端
#define DOOR_DEVICE				(0x01 << 3)		// 门禁
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// 认证终端
#define AREA_CONTROL			(0x01 << 5)		// 区域控制
#define REMAIN_BIT_SEVEN		0				// 保留
#define REMAIN_BIT_EIGHT		0				// 保留

#define  CARDSTAT_TYPE_REG	 		0     	//卡状态:挂失1-正常2-挂失
#define  CARDSTAT_TYPE_LOST	 		1     	//卡状态:挂失0-正常1-挂失
#define  CARDSTAT_TYPE_FREEZE		2     	//卡状态 冻结0-正常1-冻结
#define  CARDSTAT_TYPE_WFAIL 		3  		//卡状态:写卡失败0-正常1-写卡失败

#define  CARDFLAG_SHOWID	 				1     	// 显示卡号
#define  CARDFLAG_DEALID	 				2     	// 交易卡号
#define  CARDFLAG_SEPID						3     	// 学工号
#define  CARDFLAG_CUTID						4  		// 客户号
#define  CARDFLAG_PHYSICALID				5  		// 物理卡号

#endif	_GLOBAL_DEF_H_