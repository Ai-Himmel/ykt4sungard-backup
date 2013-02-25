#ifndef _SUBSYSTEM_H_
#define _SUBSYSTEM_H_
/** 
 * 模块名			一卡通子系统
 * 文件名			subsystem.h
 * 文件实现功能		子系统定义
 * 作者				汤成
 * 版本				V1.0
 * 日期				2005-07-21
 * 备注
 * $Id: subsystem.h 15 2005-08-22 02:39:12Z cash $
 */

//{{{ 系统配置
#define INI_SVR_SECT "SERVER"
#define INI_SVR_PORT "PORT"
#define INI_SVR_BINDIP "BINDIP"
#define INI_MODULE_SECT "MODULE"
#define INI_MODULE_PATH "PATH"
#define INI_CONNECT_SECT "CONNECT"
#define INI_CONNECT_IP	"ALLOWIP"
#define INI_CONNECT_COUNT "COUNT"
//}}}

// 加密算法
// 不加密
#define ENC_TYPE_NONE	0
// 使用 AES 128 算法加密
#define ENC_TYPE_AES128 1


/* 以下代码是用来字节对齐使用的 */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#else	// __GNUC__
#define __PACKED__	__attribute__ ((packed))
#endif	// __GNUC__
#else	// WIN32
#define __PACKED__ 
#endif	// WIN32

// 以下的定义的包会字节对齐
#if defined(WIN32) || defined(__GNUC__)
#pragma pack(push,1)
#else
#pragma options align=packed
#endif

//{{{ 报文结构
struct ksf_card_info
{
	long length;					// 数据段长度
	int func_no;					// 功能号
	int pack_index;					// 包的序号 从 0 开始
	long count;						// 数据段中包含的 CARD 信息个数
	int next_pack;					// 后继数据包数量，如果为 0 表示没有后继包
	char enc_type;					// 加密算法，0 表示无加密,1 表示128位AES
	char padded;					// 如果是加密，表示是否被补位，1:是 0:不是
	char CRC[CRC_LEN];				// CRC 校验代码
	char data[1];					// 数据段，数据段的内容是加密的
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

#endif // _SUBSYSTEM_H_
