#ifndef _KSG_LOCALINTERFACE_H_
#define _KSG_LOCALINTERFACE_H_

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
// 使用字节对齐后,结构体大小为 16394 个字节
// 否则结构体按4字节对齐后大小为 16396 个字节,为保证各语言与平台的一致性,故使用字节对齐
struct t_request_pack 
{
	int datalen;  // 数据段长度，字节数
	char data[MAX_DATALEN]; // 数据包内容
	int outdatalen; // 输出数据长度，字节数
	char outdata[MAX_DATALEN]; // 输出数据内容,如果失败保存错误信息.
}__PACKED__;

typedef struct t_request_pack request_pack;

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif


#endif // _KSG_LOCALINTERFACE_H_
