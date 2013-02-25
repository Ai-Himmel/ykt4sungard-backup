#ifndef _DEF_H_
#define _DEF_H_

/** 
 * @file def.h
 * @brief 通用前置数据结构定义
 * @author 汤成
 * @date 2005-06-28
 * $Id: def.h 27 2005-09-06 08:52:48Z cheng.tang $
 */
//{{{ define constants
#define IP_LEN  15
#define MAC_LEN	18
#define CRC_LEN 16
#define MODULE_NAME_LEN 256
#define MAX_PATH_LEN 1024
//}}}

#ifdef WIN32
#define MODULE_EXPORT __declspec(dllexport)
#else
#define MODULE_EXPORT
#endif
//{{{ 子系统结构 
struct ksf_server_conf
{
	char ip[IP_LEN + 1];			// IP 
	char mac[MAC_LEN + 1];			// MAC 地址	
	int port;						// 端口
};
//}}}

/* {{{ 协议报文的 XML 格式
 	
 	<!DOCTYPE	card-info[
 		<!ELEMENT	card-info(card)*>
 		<!ELEMENT	card(phy-id,cardid,stuempno?,blk-version,flag)>
 		<!ELEMENT	flag(0|1)>	
 	]>
 	
	<card-info>
   		<card>
   			<phy-id>卡物理ID</phy-id>
   			<cardid>交易卡号</cardid>
   			<stuempno>学工号</stuempno>
   			<blk-version>版本号</blk-version>
   			<flag>标志</flag>
   		</card>
   		...
   		...
	</card-info>
}}}*/

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

//{{{ 报文解密后的结构
struct ksf_xml_data
{
	long length;					// 数据段长度
	int func_no;					// 功能号
	long count;						// 数据段中包含的 CARD 信息个数
	char data[1];					// 数据段，内容为解密后的内容,以 '\0' 作为结尾符
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

//{{{ 返回处理结果结构
typedef enum {RET_OK = 1,RET_FAILD} ksf_ret_result;
struct ksf_card_result
{
	ksf_ret_result ret;
	int pack_index;				// 处理的包的 index
};
//}}}

#ifdef CALLBACK_API
#undef CALLBACK_API
#endif
#define CALLBACK_API WINAPI
//{{{ 子系统 Plugin 结构
typedef int (CALLBACK_API* lp_module_init)(void);
typedef int (CALLBACK_API* lp_module_release)(void);
typedef int (CALLBACK_API* lp_module_receive)(ksf_server_conf *,
										   ksf_xml_data * ,
										   ksf_card_result *);
struct ksf_plugin_module
{
	char module_name[MODULE_NAME_LEN +1];			// 模块名称
	char module_path[MAX_PATH_LEN + 1];					// 模块路径
	char date[9];									// 日期
	char author[256];								// 发行人
	short major_ver,minor_ver;						// 主版本号、次版本号
	lp_module_init module_init;						// 模块初始化函数指针
	lp_module_release module_release;				// 模块释放函数指针
	lp_module_receive module_receive;	// 模块主功能函数，用与保存数据
};
//}}}

#define def(r,name,arg) \
	typedef r (WINAPI *lp##name) arg; \
	static lp##name name; 

#define load(dll,name) \
	name = (lp##name)GetProcAddress(dll,#name); \
	if( !name ) \
		err_code = true;

#endif // _DEF_H_
