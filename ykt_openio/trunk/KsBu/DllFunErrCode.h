#ifndef _DLL_FUN_ERR_H_
#define _DLL_FUN_ERR_H_

#pragma once

#define DLLFUN_ERR_NO_DLL						-1011
#define DLLFUN_ERR_NO_FUNADDRESS				-1012
#define DLLFUN_ERR_TRANSFER_FAIL				109190		// 水控转账失败
#define DLLFUN_ERR_TRANSFER_THIRD_PART_FAIL		109191		// 水控转账和第三方交互失败
#define DLLFUN_ERR_CONNECT_ELEC					109200		// 电控转账连接数据库失败
#define DLLFUN_ERR_GET_ELEC_PRICE				109201		// 电控转账获取单价失败
#define DLLFUN_ERR_GET_ROOM_NAME				109202		// 电控转账获取房间名称失败
#define DLLFUN_ERR_TRANSFER_ELEC				109203		// 电控转账失败
#define DLLFUN_ERR_GET_ROOM_BALANCE				109204		// 电控余额

#endif