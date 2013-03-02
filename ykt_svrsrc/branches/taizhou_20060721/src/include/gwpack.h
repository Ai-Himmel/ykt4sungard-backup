#ifndef _GW_PACK_H_
#define _GW_PACK_H_

#define MAX_DATALEN	8192 + 1
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
struct KSG_GW_PACK_t
{
	int length;					// 数据段长度
	int func_no;					// 功能号
	int pack_index;					// 包的序号 从 0 开始
	long retcode;					// 返回响应码
	int next_pack;					// 后继数据包数量，如果为 0 表示没有后继包
	char enc_type;					// 加密算法，0 表示无加密,1 表示128位AES
	char padded;					// 如果是加密，表示是否被补位，1:是 0:不是
	unsigned char CRC[16];				// CRC 校验代码
	char data[1];					// 数据段，数据段的内容是加密的
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

#include "tcp.h"

#define IP_MAX_LEN	18

typedef struct 
{
	char server_ip[IP_MAX_LEN+1];
	short server_port;
	CTcpSocket* sock;
}gw_server_info_t;

int SendToServer(gw_server_info_t* svr,int funcno,const char* data);
int RecvFromServer(gw_server_info_t* svr,KSG_GW_PACK_t** resp);

#endif // _GW_PACK_H_

